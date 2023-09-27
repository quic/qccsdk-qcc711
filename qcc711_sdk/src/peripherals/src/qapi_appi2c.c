/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include "qcc710.h"
#include <stdlib.h>
#include "qapi_task.h"
#include "qapi_appi2c.h"
#include "hwio_periph.h"
#include "qapi_timer.h"
#include "hwio_periph.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define APPI2C_REGISTER_BASE	  PERIPH_APP_I2C_REG_BASE                                                         

#define FLD_BMSK(reg, field) HWIO_PERIPH_##reg##_##field##_BMSK

#define FLD_SHFT(reg, field) HWIO_PERIPH_##reg##_##field##_SHFT

#define FLD_SET(reg, field, data) \
    (((uint32_t) (data) << (uint32_t) FLD_SHFT(reg, field)) & (uint32_t) FLD_BMSK(reg, field))

#define FLD_GET(data, reg, field) \
    (((data) & FLD_BMSK(reg, field)) >> FLD_SHFT(reg, field))

#define APPI2C_MASK_IS_SET(mode, mask, value)  ((value) == ((mask) & (mode)))
#define REGFLD_IS_SET(reg, field, data, value)  ((value) == FLD_GET(data, reg, field))

#define APPI2C_FIFO_LEN					(16)

#define ROUND_DOWN(v, n)				((v) - ((v) % (n)))
#define ROUND_UP(v, n)					(ROUND_DONW((v) + (n) - 1))

#define MIN(a, b)						(((a) > (b)) ? (b) : (a))
#define MAX(a, b)						(((a) < (b)) ? (b) : (a))

#define APPI2C_FIFO_RECEIVE_WATERMARK   (12)
#define APPI2C_TSK_EVENT_STATUS_STEP	(1)

#define APPI2C_ZIGGY_FREQUEN			(32000000UL)
#define APPI2C_DATARATE_STANDARD		(100000)
#define APPI2C_DATARATE_FAST			(400000)
#define APPI2C_DATARATE_FAST_PLUS		(1000000)
#define APPI2C_DATARATE_MAX				APPI2C_DATARATE_FAST_PLUS

#define APPI2C_POLL_TIME_DEFAULT_US		(4096000)
#define APPI2C_POLL_INTERVAL_US			(5)
/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
/*  Hal data structure define. */
typedef struct APPI2C_DataCtxt_s
{
	/* I2c can only do either transmission or reception at one time. */
	/*  So only one buf and index is enough */
	uint8_t *Buf;				/*  transfer buf */
	uint32_t Size;				/*  total size need to transfer */
	uint32_t ByteInFifo;		/*  size of bytes transfered on the air one time */
	uint32_t Index;				/*  current sent index */
	uint32_t *ReturnSize;		/*  return finally size. */
} APPI2C_DataCtxt_t;

typedef enum
{
	APPI2C_MSTATUS_IDLE,
	APPI2C_MSTATUS_WAIT_FOR_TRANSMIT,
	APPI2C_MSTATUS_TRANMITING,
	APPI2C_MSTATUS_WAIT_FOR_RECEIVE,
	APPI2C_MSTATUS_RECEIVING,
	APPI2C_MSTATUS_STOP
} APPI2C_MainStatus_t;

typedef enum 
{
	APPI2C_STATUS_NODATA,
	APPI2C_STATUS_ADDRESSREAD,
	APPI2C_STATUS_ADDRESSWRITE,
	APPI2C_STATUS_GNCALL,
	APPI2C_STATUS_FIFO_SEND_RELOAD,
	APPI2C_STATUS_FIFO_SEND_DONE,
	APPI2C_STATUS_FIFO_RECEIVE_FETCH,
	APPI2C_STATUS_FIFO_RECEIVE_NEAR_FULL,
	APPI2C_STATUS_FIFO_RECEIVE_DONE,
	APPI2C_STATUS_STOP,
	APPI2C_STATUS_TIMEOUT,
	APPI2C_STATUS_NACK,
	APPI2C_STATUS_TRANSFER_DNOE
} APPI2C_SubStatus_t;

typedef enum
{
	APPI2C_GNCALL_SOFT_RESET_E,
	APPI2C_GNCALL_WRITE_PROGRAM_E,
	APPI2C_GNCALL_HARDWARE_GNCALL_E
} APPI2C_GNCALL_TYPE_t;

typedef struct
{
	qbool_t AppI2cEnable;
	void * I2cTskHandle;
	uint32_t Mode;
	uint32_t AddrMode;
	uint32_t SlaveAddr;
	APPI2C_MainStatus_t PreMainStatus;
	APPI2C_MainStatus_t MainStatus;
	APPI2C_SubStatus_t SubStatus;	
	APPI2C_DataCtxt_t Data;
	qapi_APPI2C_CB_t UserCallBack;
	qapi_APPI2C_UserCallBackParam_t UserCbParam;
} APPI2C_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
static APPI2C_t AppI2c = {
		.AppI2cEnable = false,
};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static qbool_t APPI2C_ConfigCheck(qapi_APPI2C_Config_t *Config);
static APPI2C_SubStatus_t APPI2C_GetSubStatus(void);
static qapi_Status_t APPI2C_WriteBuf(uint8_t *Buf, uint32_t *Len);
static qapi_Status_t APPI2C_HandleGncall(uint8_t *Data, uint32_t *Len);
static uint32_t APPI2C_TransferTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);
static qapi_Status_t APPI2C_ReadBuf(uint8_t *Data, uint32_t *Len);
static uint32_t UserDataRate2I2cDataRate(uint32_t UserDataRate);
static void APPI2C_ResetStatus(void);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Initializes the APPI2C controller.

   This function initializes internal data structures and associated
   static data. In any operating mode, this function should be called before
   calling any other I2C controller API.

   @param[in] Config    APPI2C configuration specified by #qapi_APPI2C_Config_t.

   @return
   - QAPI_OK                                 --  Controller is initialized successfully.
   - QAPI_APPI2C_ERROR_INVALID_PARAM         --  Invalid instance or handle parameter.
   - QAPI_APPI2C_ERROR_MEM_ALLOC             --  Could not allocate space for driver structures.
*/
qapi_Status_t qapi_APPI2C_Open(qapi_APPI2C_Config_t *Config)
{
	uint32_t DivLow;
	uint32_t SelfAddr;
	uint32_t DivHigh;

	if (!APPI2C_ConfigCheck(Config))
	{
		return QAPI_APPI2C_ERROR_INVALID_PARAM;	
	}

	if (true == AppI2c.AppI2cEnable)
	{
		return 	QAPI_APPI2C_ERROR_I2C_HASBEEN_OPENED;
	}

	/*  0. Initialize data structure */
	APPI2C_ResetStatus();
	AppI2c.Mode = Config->Mode;
	AppI2c.AddrMode = Config->AddrMode;
	AppI2c.SlaveAddr = Config->SlaveAddr;

	/* 1. Clock div low and high */
	DivLow = APPI2C_ZIGGY_FREQUEN / UserDataRate2I2cDataRate(Config->FreqHz) / 2;
	DivHigh = DivLow;
	HWIO_PERIPH_APP_I2C_CDIV_LOW_OUT(PERIPH_APP_I2C_REG_BASE, DivLow);
	HWIO_PERIPH_APP_I2C_CDIV_HIGH_OUT(PERIPH_APP_I2C_REG_BASE, DivHigh);

	if ((DivHigh + DivLow) > 24)
	{
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ENABLE_FILTER_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ENABLE_FILTER_SHFT);
	} else {
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ENABLE_FILTER_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ENABLE_FILTER_SHFT);
	}

	/* enable i2c clk */
	/*  must be set to 1 by spec */
	HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_FIX_SL_SCL_LOGIC_EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_FIX_SL_SCL_LOGIC_EN_SHFT);
	
	/** HWIO_PERIPH_APP_I2C_CONTROL_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x3008); */

	qapi_TSK_Enter_Critical();
	HWIO_PERIPH_CLOCK_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, HWIO_PERIPH_CLOCK_CFG_I2C_CLK_EN_BMSK, HWIO_PERIPH_CLOCK_CFG_I2C_CLK_EN_BMSK);
	qapi_TSK_Exit_Critical();

	/*  2. Set slave self address */
	if (APPI2C_MASK_IS_SET(Config->Mode, QAPI_APPI2C_MODE_ROLE_MASK, QAPI_APPI2C_MODE_SLAVE))
	{
		SelfAddr = 0;
		if (QAPI_APPI2C_ADDR_10BIT_E == Config->AddrMode)
		{
			SelfAddr |= 1 << 10;	
			Config->SlaveAddr &= 0x3FF;
		} else {
			Config->SlaveAddr &= 0xFF;	
		}
		SelfAddr |= Config->SlaveAddr;
		HWIO_PERIPH_APP_I2C_SELF_ADDR_1_OUT(PERIPH_APP_I2C_REG_BASE, SelfAddr);

		/*  create task if non-blocking */
		if (APPI2C_MASK_IS_SET(Config->Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_INTERRUPT))
		{
			qapi_TSK_Handle_t I2cTskHandle;

			I2cTskHandle = qapi_TSK_Create_Task(APPI2C_TransferTask, (void *)&AppI2c);
			if (NULL == I2cTskHandle) 
			{
				/*  Disable interrupt */
				NVIC_DisableIRQ(APPI2C_IRQn);
				HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0);
				HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
				return QAPI_APPI2C_ERROR_TSK_CREATE_FAIL;
			}

			AppI2c.I2cTskHandle = (void *)I2cTskHandle;
		}
		/* enable i2c slave */
		/* note: must not unmask UNDEFINE bit or will creates persistent interruptions that cannot be eliminated */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0x01);
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		NVIC_EnableIRQ(APPI2C_IRQn);
	}

	AppI2c.AppI2cEnable = true;
	return QAPI_OK;
}

/**
   @brief Performs a data transmit to master as slave over the APPI2C bus.

   This function performs transfer from slave to master. Transmit can be blocking or interrupt.

   @param[in]		Data			User buf ready to transmit from slave to master
   @param[in/out]	Len				User buf length and the actual bytes transferred.
   @param[in]		UserCallBack	User non-blocking call back function. Will be ignored in blocking mode.

   @return
   - QAPI_OK                                 --  Transfer done.
   - QAPI_APPI2C_ERROR                       --  General error.
   - QAPI_APPI2C_ERROR_INVALID_PARAM         --  Invalid parameters.
   - QAPI_APPI2C_ERROR_TRANSFER_STOP         --  Receive the STOP signal from master.
   - QAPI_APPI2C_ERROR_TRANSFER_NACK         --  Receive the NACK signal from master.
   - QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT      --  Bus timeout.
*/
qapi_Status_t qapi_APPI2C_SlaveTransmit(uint8_t *Data, uint32_t *Len, qapi_APPI2C_CB_t UserCallBack)
{
	qapi_Status_t Res;
	int32_t TimeoutUs = APPI2C_POLL_TIME_DEFAULT_US;
	APPI2C_SubStatus_t AppStatus, SubAppStatus;

	if ((APPI2C_MASK_IS_SET(AppI2c.Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_INTERRUPT))
		&& (APPI2C_MSTATUS_IDLE != AppI2c.MainStatus)
		&& (APPI2C_MSTATUS_STOP != AppI2c.MainStatus))
	{
		return QAPI_APPI2C_ERROR_TRANSFER_BUSY;	
	}
	NVIC_DisableIRQ(APPI2C_IRQn);

	/*  Blocking waiting for address read. */
	/* Clear select bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_SHFT);
	/* clear fifo tx empty bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_SHFT);
	/* clear stop/timeout bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
	/* clear nack bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
	/* reset ack to 0 */
	HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);
	/* flush the FIFO in case the one byte left */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_SHFT);

	if (APPI2C_MASK_IS_SET(AppI2c.Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_BLOCKING))
	{
		AppI2c.MainStatus = APPI2C_MSTATUS_WAIT_FOR_TRANSMIT;
		/* note: must not unmask UNDEFINE bit or will creates persistent interruptions that cannot be eliminated */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0x5B);
		/*  enable i2c slave */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);

		while (0 < TimeoutUs)
		{
			AppStatus = APPI2C_GetSubStatus();
			if (APPI2C_STATUS_ADDRESSREAD == AppStatus)
			{
				if (AppI2c.AddrMode == QAPI_APPI2C_ADDR_7BIT_E)
				{
					break;	
				}
				else
				{
					/* For 10bit mode read it should has a write first then a read */
					AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
					NVIC_EnableIRQ(APPI2C_IRQn);
					return QAPI_APPI2C_ERROR_READWRITE_CORRUPT;
				}
			} 
			else if (APPI2C_STATUS_ADDRESSWRITE == AppStatus)
			{
				if (AppI2c.AddrMode == QAPI_APPI2C_ADDR_7BIT_E)
				{
					AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
					NVIC_EnableIRQ(APPI2C_IRQn);
					return QAPI_APPI2C_ERROR_READWRITE_CORRUPT;
				}
				else
				{
					uint32_t TempLen = ((*Len > APPI2C_FIFO_LEN)? APPI2C_FIFO_LEN : AppI2c.Data.Size);
					/* for 10bit mode, read operation will send a write signal firstly */
					HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (TempLen) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);
					HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
					while (0 < TimeoutUs)
					{
						SubAppStatus = APPI2C_GetSubStatus();
						if (APPI2C_STATUS_ADDRESSREAD == SubAppStatus)
						{
							/* flush the rx data FIFO */
							HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);
							break;		
						}
						qapi_TMR_Delay_Us(APPI2C_POLL_INTERVAL_US);
						TimeoutUs -= APPI2C_POLL_INTERVAL_US;
					}
					break;
				}
			}
			qapi_TMR_Delay_Us(APPI2C_POLL_INTERVAL_US);
			TimeoutUs -= APPI2C_POLL_INTERVAL_US;
		}

		if (0 >= TimeoutUs)
		{
			*Len = 0;
			AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
			NVIC_EnableIRQ(APPI2C_IRQn);
			return QAPI_APPI2C_ERROR_BLOCKING_TIMEOUT;
		}

		Res = APPI2C_WriteBuf(Data, Len);
		
		AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
		NVIC_EnableIRQ(APPI2C_IRQn);
		return Res;
	} else {	


		AppI2c.Data.Buf = Data;
		AppI2c.Data.Size = *Len;
		AppI2c.Data.Index = 0;
		AppI2c.Data.ByteInFifo = 0;
		/** AppI2c.Data.ReturnSize = Len; */

		AppI2c.UserCallBack = UserCallBack;
	
		AppI2c.MainStatus = APPI2C_MSTATUS_WAIT_FOR_TRANSMIT;
		AppI2c.SubStatus = APPI2C_STATUS_NODATA;

		/* note: must not unmask UNDEFINE bit or will creates persistent interruptions that cannot be eliminated */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0x5B);
		/*  enable i2c slave */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);

		NVIC_EnableIRQ(APPI2C_IRQn);
		/* wait for address read interrupt */
	}

	return QAPI_OK;
}

/**
   @brief Performs a data receive from master as slave over the APPI2C bus.

   This function performs data receive from master to slave. Receiving can be blocking or interrupt.

   @param[in]		Data			User buf ready to transmit from slave to master
   @param[in/out]	Len				User buf length and the actual bytes transferred.
   @param[in]		UserCallBack	User non-blocking call back function. Will be ignored in blocking mode.

   @return
   - QAPI_OK                                 --  Transfer done.
   - QAPI_APPI2C_ERROR                       --  General error.
   - QAPI_APPI2C_ERROR_INVALID_PARAM         --  Invalid parameters.
   - QAPI_APPI2C_ERROR_TRANSFER_STOP         --  Receive the STOP signal from master.
   - QAPI_APPI2C_ERROR_TRANSFER_NACK         --  Receive the NACK signal from master.
   - QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT      --  Bus timeout.
   - QAPI_APPI2C_ERROR_TRANSFER_GNCALL		 --  Receive the general call from master.
*/
qapi_Status_t qapi_APPI2C_SlaveReceive(uint8_t *Data, uint32_t *Len, qapi_APPI2C_CB_t UserCallBack)
{
	qapi_Status_t Res = QAPI_OK;
	qbool_t End = false;
	int32_t TimeoutUs = APPI2C_POLL_TIME_DEFAULT_US;
	APPI2C_SubStatus_t AppStatus;

	if ((APPI2C_MASK_IS_SET(AppI2c.Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_INTERRUPT))
		&& (APPI2C_MSTATUS_IDLE != AppI2c.MainStatus)
		&& (APPI2C_MSTATUS_STOP != AppI2c.MainStatus))
	{
		return QAPI_APPI2C_ERROR_TRANSFER_BUSY;	
	}


	NVIC_DisableIRQ(APPI2C_IRQn);

	/* Clear all interrupt bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F);
	HWIO_PERIPH_APP_I2C_CLEAR_FIFO_STATUS_OUT(PERIPH_APP_I2C_REG_BASE, 0x3);

	/* flush the rx data FIFO */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);
	HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);

	if (APPI2C_MASK_IS_SET(AppI2c.Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_BLOCKING))
	{
		/*  Blocking waiting for address read. */

		/* note: must not unmask UNDEFINE bit or will creates persistent interruptions that cannot be eliminated */
		/* gncall, nack, stop, rx full, select */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0x81D);
		/* kick start  */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		

		while (!End && (0 < TimeoutUs))
		{
			AppStatus = APPI2C_GetSubStatus();
			if (APPI2C_STATUS_ADDRESSWRITE == AppStatus)
			{
				Res = APPI2C_ReadBuf(Data, Len);
				End = true;
			} 
			else if (APPI2C_STATUS_ADDRESSREAD == AppStatus) 
			{
				AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
				NVIC_EnableIRQ(APPI2C_IRQn);
				return QAPI_APPI2C_ERROR_READWRITE_CORRUPT;
			    			
			} 
			else if (APPI2C_STATUS_GNCALL == AppStatus)
			{
				Res = APPI2C_HandleGncall(Data, Len);
				End = true;
			}

			qapi_TMR_Delay_Us(APPI2C_POLL_INTERVAL_US);
			TimeoutUs -= APPI2C_POLL_INTERVAL_US;
		}

		if (0 >= TimeoutUs)
		{
			*Len = 0;
			AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
			NVIC_EnableIRQ(APPI2C_IRQn);
			return QAPI_APPI2C_ERROR_BLOCKING_TIMEOUT;
		}
		
		AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
		NVIC_EnableIRQ(APPI2C_IRQn);
		return Res;

	} else {	
		
		AppI2c.Data.Buf = Data;
		AppI2c.Data.Size = *Len;
		AppI2c.Data.Index = 0;
		AppI2c.Data.ByteInFifo = 0;
		/** AppI2c.Data.ReturnSize = Len; */

		AppI2c.UserCallBack = UserCallBack;
	
		AppI2c.MainStatus = APPI2C_MSTATUS_WAIT_FOR_RECEIVE;
		AppI2c.SubStatus = APPI2C_STATUS_NODATA;
		

		/* use the normal receive full mode */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_RX2FULL_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_RX2FULL_SHFT);

		/* note: must not unmask UNDEFINE bit or will creates persistent interruptions that cannot be eliminated */
		/* gncall, nack, stop, rx full, select */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0x81D);
		// enable receive
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		NVIC_EnableIRQ(APPI2C_IRQn);
		/*  wait for address write interrupt */
	}

	return Res;
}

/**
   @brief Deinitialize the APPI2C controller.

   This function deinitializes internal data structures and associated
   static data. This function should be called to close APPI2C bus.

   @return
   - QAPI_OK                                 --  Controller is closed successfully.
   - QAPI_APPI2C_ERROR_TRANSFER_BUSY		 --  Controller is in transmission.
   - QAPI_APPI2C_ERROR_I2C_HASBEEN_CLOSED	 --  Controller has been closed already.
*/
qapi_Status_t qapi_APPI2C_Close()
{
	/*  0. Check for repeat close */
	/* i2c should close at any situation except this */
	if (false == AppI2c.AppI2cEnable)
	{
		return QAPI_APPI2C_ERROR_I2C_HASBEEN_CLOSED;
	}

	/*  1. Disable interrupt */
	NVIC_DisableIRQ(APPI2C_IRQn);
	HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0);
	HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);

	/*  2. Release resource */
	if (NULL != AppI2c.I2cTskHandle)
	{
		qapi_TSK_Delete_Task(AppI2c.I2cTskHandle);
	}

	/*  3. Unset data structure and flag */
	APPI2C_ResetStatus();

	AppI2c.AppI2cEnable = false;

	return QAPI_OK;
}

static void APPI2C_ResetStatus(void)
{
	/*  Unset data structure and flag */
	AppI2c.I2cTskHandle = NULL;
	AppI2c.Mode = 0;
	AppI2c.AddrMode = 0;
	AppI2c.SlaveAddr = 0;
	AppI2c.PreMainStatus = APPI2C_MSTATUS_IDLE;
	AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;
	AppI2c.SubStatus = APPI2C_STATUS_NODATA;
	AppI2c.Data.Buf = NULL;
	AppI2c.Data.Size = 0;
	AppI2c.Data.ByteInFifo = 0;
	AppI2c.Data.Index = 0;
	AppI2c.UserCallBack = NULL;
}

static uint32_t APPI2C_StepWriteBuf(APPI2C_DataCtxt_t *Data)
{
	uint32_t SentLen = 0;
	uint32_t StartIndex;
	uint32_t Index;

	SentLen = Data->Index + Data->ByteInFifo;
	Data->Index = SentLen;

	/* clear the interrupt */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_SHFT);
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
	/* flush the FIFO in case the one byte left */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_SHFT);

	/* transfer done */
	if (SentLen == Data->Size)
	{
		Data->ByteInFifo = 0;
		return SentLen;	
	}

	Index = Data->Index;
	StartIndex = Index;
	if (Data->Index < ROUND_DOWN(Data->Size, APPI2C_FIFO_LEN))
	{

		for (; Index < StartIndex + APPI2C_FIFO_LEN; Index += 2)
		{
			HWIO_PERIPH_APP_I2C_TX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, *(uint16_t *)(Data->Buf + Index));
		}

	} 
	else 
	{
		for (; Index < ROUND_DOWN(Data->Size, 2); Index+=2)	
		{
			HWIO_PERIPH_APP_I2C_TX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, *(uint16_t *)(Data->Buf + Index));
		}

		if (Data->Size % 2)
		{
			HWIO_PERIPH_APP_I2C_TX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, (uint16_t)(*(Data->Buf + Index)));
			Index++;
		}

	}

	Data->ByteInFifo = Index - StartIndex;
	/* Send bytes = register value + 1 */
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_TXVLBY_BMSK, ((Index - StartIndex - 1)) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_TXVLBY_SHFT);
	return SentLen;
}


qbool_t APPI2C_FifoDone(APPI2C_SubStatus_t *Status)
{
	*Status = APPI2C_GetSubStatus();

	/*  These substatus mean a fifo operation is done or abort. */
	if ((APPI2C_STATUS_FIFO_SEND_DONE == *Status)			  /*  fifo send ok */
		|| (APPI2C_STATUS_FIFO_RECEIVE_DONE == *Status)       /*  fifo receive ok */
		|| (APPI2C_STATUS_STOP == *Status)					  /*  stop */
		|| (APPI2C_STATUS_TIMEOUT == *Status)				  /*  timeout */
		|| (APPI2C_STATUS_NACK == *Status))					  /*  nack */
	{
		return true;	
	}

	/* nodata or fifo operation is not done. */
	return false;
}

static qapi_Status_t APPI2C_SubStatus2ApiReturnValue(APPI2C_SubStatus_t Status)
{
	qapi_Status_t Res;
	switch(Status)
	{
		case APPI2C_STATUS_STOP: 
			Res = QAPI_APPI2C_ERROR_TRANSFER_STOP; 
			break;
		case APPI2C_STATUS_NACK: 
			Res = QAPI_APPI2C_ERROR_TRANSFER_NACK; 
			break;
		case APPI2C_STATUS_TIMEOUT: 
			Res = QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT; 
			break;
		default: 
			Res = QAPI_APPI2C_ERROR; 
			break;
	}

	return Res;
}

static qapi_APPI2C_Status_t  APPI2C_SubStatus2ApiStatus(APPI2C_SubStatus_t Status)
{
	qapi_APPI2C_Status_t Res;
	switch(Status)
	{
		case APPI2C_STATUS_STOP: 
		case APPI2C_STATUS_NACK: 
			Res = QAPI_APPI2C_STATUS_ABORT_E; 
			break;
		case APPI2C_STATUS_TIMEOUT: 
			Res = QAPI_APPI2C_STATUS_TIMEOUT; 
			break;
		case APPI2C_STATUS_TRANSFER_DNOE:
			Res = QAPI_APPI2C_STATUS_DONE_E;
			break;
		case APPI2C_STATUS_GNCALL:
			Res = QAPI_APPI2C_STATUS_GNCALL_E;
			break;
		default: 
			Res = QAPI_APPI2C_STATUS_DONE_E; 
			break;
	}

	return Res;
}

static qapi_Status_t APPI2C_RefetchFifo(uint8_t *Buf, uint32_t Start, uint32_t Size, uint32_t *Len)
{
	uint32_t Index = Start;
	uint32_t Num;
	APPI2C_SubStatus_t Status;
	int32_t TimeoutUs = APPI2C_POLL_TIME_DEFAULT_US;

	if (Size == 0)
	{
		*Len = 0;
		return QAPI_OK;	
	}

	/* Once a maximum of APPI2C_FIFO_LEN at a time */
	Size = Size % (APPI2C_FIFO_LEN + 1);

	// use normal receive full method
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (Size - 1) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);
	// kick start receive
	HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);


	/*wait for interrupt */
	while(!APPI2C_FifoDone(&Status)
			&& (0 < TimeoutUs))
	{
		qapi_TMR_Delay_Us(APPI2C_POLL_INTERVAL_US);
		TimeoutUs -= APPI2C_POLL_INTERVAL_US;
	}

	if (0 >= TimeoutUs)
	{
		/*  Disable interrupt */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		return QAPI_APPI2C_ERROR_BLOCKING_TIMEOUT;
	}

	if (Status == APPI2C_STATUS_FIFO_RECEIVE_DONE)
	{
		Num = Size;	
	}
	else
	{
		Num = HWIO_PERIPH_APP_I2C_RX_FIFO_STATUS_INM(PERIPH_APP_I2C_REG_BASE, HWIO_PERIPH_APP_I2C_RX_FIFO_STATUS_RX_FIFO_LEVEL_BMSK) >> HWIO_PERIPH_APP_I2C_RX_FIFO_STATUS_RX_FIFO_LEVEL_SHFT;
		Num = MIN(Size, Num);
	}

	for (int i=0; i<ROUND_DOWN(Num, 2); i+=2)		
	{
		*(uint16_t *)(Buf + Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE);
		Index += 2;
		/* need to write to rx data register to increase the fifo index. */
		HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);
	}

	if (Num % 2)
	{
		/* the last one byte needn't to write to increase the index by HPG */
		*(Buf + Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE);
		Index += 1;
		HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);
	}
	
	/* clear receive interrupt */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_SHFT);
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
	/* clear nack bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
	/* flush the rx data FIFO */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);

	switch(Status)
	{
		case APPI2C_STATUS_FIFO_RECEIVE_DONE: 
			*Len = Num;
			break;
		case APPI2C_STATUS_TIMEOUT:
		case APPI2C_STATUS_STOP:
		case APPI2C_STATUS_NACK:
			*Len = Num;
			return APPI2C_SubStatus2ApiReturnValue(Status);
			break;
		/* shouldn't happen */
		default: 
			*Len = 0;
			return QAPI_APPI2C_ERROR;
	}

	return QAPI_OK;
}

static qapi_Status_t APPI2C_ReadBuf(uint8_t *Buf, uint32_t *Len)
{
	uint32_t Index = 0;
	uint32_t Size = *Len;
	uint32_t SizeOnAir;
	qapi_Status_t Res;


	while (Index < ROUND_DOWN(Size, APPI2C_FIFO_LEN))
	{
		Res = APPI2C_RefetchFifo(Buf, Index, APPI2C_FIFO_LEN, &SizeOnAir);
		Index += SizeOnAir;

		if (QAPI_OK != Res)
		{
			*Len = Index;
			return Res;	
		}
	}

	if (APPI2C_FIFO_LEN > (Size - Index))
	{
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);
	}

	Res = APPI2C_RefetchFifo(Buf, Index, Size - Index, &SizeOnAir);
	Index += SizeOnAir;
	*Len = Index;


	return Res;	
}

static qbool_t APPI2C_IsHardWareGncall(uint8_t Byte)
{
	if (Byte & 0x01)
	{
		return true;	
	} 
	
	return false;	
}

static qapi_Status_t APPI2C_HandleGncall(uint8_t *Data, uint32_t *Len)
{
	APPI2C_SubStatus_t Status;
	uint32_t Index = 0;

	/* only receive the second byte */
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);
	HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);

	while(!APPI2C_FifoDone(&Status));
	
	if (Status == APPI2C_STATUS_FIFO_RECEIVE_DONE)
	{
		*Data = (uint8_t)(HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE) & 0xFF);
		Index++;
		// need to write to rx data register to increase the fifo index.
		HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);

		/* send NACK to release the sck */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);
		HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,   HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<   HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
	} else if (Status == APPI2C_STATUS_STOP)
	{
		return QAPI_APPI2C_ERROR;	
	}

	if (APPI2C_IsHardWareGncall(*Data))
	{
		/* TODO not support	 */
	} else {
		*Len = 1;
		switch(*Data)
		{
			case APPI2C_GNCALL_SOFT_RESET_E: 
			{
				/* TODO */
				break;
			}	
			case APPI2C_GNCALL_WRITE_PROGRAM_E:
			{
				/* TODO */
				break;	
			}
			default : 
				break;	/*TODO */
		}
	}

	return QAPI_APPI2C_ERROR_TRANSFER_GNCALL;
}

static qbool_t APPI2C_ConfigCheck(qapi_APPI2C_Config_t *Config)
{
	if ((Config->FreqHz > APPI2C_DATARATE_MAX)
		|| (Config->AddrMode > QAPI_APPI2C_ADDR_MAX_E)
		|| ((~QAPI_APPI2C_MODEBIT_NUM_MSK) & (Config->Mode)))
	{
		return false;	
	}

	return true;
}

static uint32_t UserDataRate2I2cDataRate(uint32_t UserDataRate)
{
	if (APPI2C_DATARATE_STANDARD > UserDataRate)
	{
		return APPI2C_DATARATE_STANDARD;	
	} else if (APPI2C_DATARATE_FAST > UserDataRate)
	{
		return APPI2C_DATARATE_FAST;	
	} else if (APPI2C_DATARATE_FAST_PLUS > UserDataRate)
	{
		return APPI2C_DATARATE_FAST_PLUS;	
	}

	/* this shouldn't happen because the parameters should be check before this function. */
	return APPI2C_DATARATE_FAST_PLUS;
}

static APPI2C_SubStatus_t APPI2C_GetSubStatus(void)
{
	uint32_t Reg1;
		
	Reg1 = HWIO_PERIPH_APP_I2C_SL_STATUS_1_IN(PERIPH_APP_I2C_REG_BASE);

	if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, GNCALL, Reg1, 1))
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_GNCALL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_GNCALL_SHFT);
		return APPI2C_STATUS_GNCALL;
	}	
	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SLSEL1, Reg1, 1))
	{
		/* clear interrupt */
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_SHFT);
		if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SRDWR, Reg1, 1))
		{
			return APPI2C_STATUS_ADDRESSREAD;					/* Master read to slave */
		} else 
		{
			return APPI2C_STATUS_ADDRESSWRITE;					/* Master write from slave */
		}
	
	}	
	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SLNAST, Reg1, 1)) /* NACK */
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
		return APPI2C_STATUS_NACK;
	} 
	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SLTRCP, Reg1, 1)) /* stop */
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
		return APPI2C_STATUS_STOP;	
	}
   	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SLTXEP, Reg1, 1))  /* fifo send ok */
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_SHFT);
		return APPI2C_STATUS_FIFO_SEND_DONE;
	} 
	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SLRXFL, Reg1, 1))	/* fifo receive ok */
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_SHFT);
		return APPI2C_STATUS_FIFO_RECEIVE_DONE;	
	} 
	else if (REGFLD_IS_SET(APP_I2C_SL_STATUS_1, SL_TOST, Reg1, 1))	/* timeout */
	{
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTOST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTOST_SHFT);
		return APPI2C_STATUS_TIMEOUT;
	} 
	else 
	{
		/** HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F); */
		return APPI2C_STATUS_NODATA;	
	}
}

static qapi_Status_t APPI2C_ReloadFifo(uint8_t *Buf, uint32_t Start, uint32_t Size, uint32_t *Len)
{
	uint32_t Index = Start;
	uint32_t LastLen;
	APPI2C_SubStatus_t Status;
	int32_t TimeoutUs = APPI2C_POLL_TIME_DEFAULT_US;

	if (Size == 0) 
	{
		*Len = 0;
		return QAPI_OK;	
	}
	/* Once a maximum of APPI2C_FIFO_LEN at a time */
	Size = Size > APPI2C_FIFO_LEN ? APPI2C_FIFO_LEN : Size;
	/** Size = Size % (APPI2C_FIFO_LEN + 1); */
	for (;Index < ROUND_DOWN(Start + Size, 2); Index += 2)
	{
		HWIO_PERIPH_APP_I2C_TX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, *(uint16_t *)(Buf + Index));
	}

	if (Size % 2)
	{
		HWIO_PERIPH_APP_I2C_TX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, (uint16_t)(*(Buf + Index)));
		Index++;
	}
	
	/* Send bytes = register value + 1 */
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_TXVLBY_BMSK, (Size - 1) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_TXVLBY_SHFT);
	HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
	
	while(!APPI2C_FifoDone(&Status)
			&& (0 < TimeoutUs))
	{
		qapi_TMR_Delay_Us(APPI2C_POLL_INTERVAL_US);
		TimeoutUs -= APPI2C_POLL_INTERVAL_US;
	}

	if (0 >= TimeoutUs)
	{
		/*  Disable interrupt */
		HWIO_PERIPH_APP_I2C_SL_MASK_OUT(PERIPH_APP_I2C_REG_BASE, 0);			
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		return QAPI_APPI2C_ERROR_BLOCKING_TIMEOUT;
	}
	/* clear the interrupt */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_SHFT);
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
	/* flush the FIFO in case the one byte left */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_SHFT);

	switch(Status)
	{
		case APPI2C_STATUS_STOP:
		case APPI2C_STATUS_NACK:
		case APPI2C_STATUS_FIFO_SEND_DONE: 
			*Len = Size; 
			break;
		case APPI2C_STATUS_TIMEOUT:
			LastLen = HWIO_PERIPH_APP_I2C_SL_STATUS_2_INM(PERIPH_APP_I2C_REG_BASE, HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYRE_BMSK) >> HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYTR_SHFT;
			*Len = LastLen;
			return APPI2C_SubStatus2ApiReturnValue(Status);
		default: 
			*Len = 0; 
			return QAPI_APPI2C_ERROR;
	}

	return QAPI_OK;
}
static qapi_Status_t APPI2C_WriteBuf(uint8_t *Buf, uint32_t *Len)
{
	uint32_t Index = 0;
	uint32_t Size = *Len;
	uint32_t SizeDone;
	qapi_Status_t Res;

	while (Index < ROUND_DOWN(Size, APPI2C_FIFO_LEN))
	{
		Res = APPI2C_ReloadFifo(Buf, Index, APPI2C_FIFO_LEN, &SizeDone);
		Index += SizeDone;

		if (QAPI_OK != Res)
		{
			*Len = Index;
			return Res;	
		}

	}


	Res = APPI2C_ReloadFifo(Buf, Index, Size - Index, &SizeDone);
	Index += SizeDone;
	*Len = Index;

	return Res;	
}


static uint32_t APPI2C_GetFifoRemainNum(APPI2C_MainStatus_t Status)
{
	uint32_t Len;

	if (APPI2C_MSTATUS_TRANMITING == Status)
	{
		Len = HWIO_PERIPH_APP_I2C_SL_STATUS_2_INM(PERIPH_APP_I2C_REG_BASE, HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYTR_BMSK) >> HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYTR_SHFT;
	} else 
	{
		Len = HWIO_PERIPH_APP_I2C_SL_STATUS_2_INM(PERIPH_APP_I2C_REG_BASE, HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYRE_BMSK) >> HWIO_PERIPH_APP_I2C_SL_STATUS_2_SLXBYRE_SHFT;
	}

	return Len;
}

static uint32_t APPI2C_StepReceiveBufStart(APPI2C_DataCtxt_t *Data)
{
	uint32_t Num;
	
	/* Clear select bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLSEL1_SHFT);
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_SHFT);
	/* flush the rx data FIFO */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);
	HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);
	
	Num = MIN(Data->Size, APPI2C_FIFO_LEN);

	Data->ByteInFifo = Num;

	// use normal receive full method
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (Num -1) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);

	return Num;
}

static uint32_t APPI2C_StepReceiveBuf(APPI2C_DataCtxt_t *Data)
{
	uint32_t Index;
	uint32_t Num;


	Index = Data->Index;
	for (int i=0; i<ROUND_DOWN(Data->ByteInFifo, 2); i+=2)		
	{
		*(uint16_t *)(Data->Buf + Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE);
		Index += 2;
		// need to write to rx data register to increase the fifo index.
		HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0); 
	}

	if (Data->ByteInFifo % 2)
	{
		*(Data->Buf + Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE) & 0xFF;
		Index += 1;
		// the last one byte needn't to write to increase the index by HPG
		// TODO but seems it still need to do a rewrite operation
		// need to write to rx data register to increase the fifo index.
		HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);
	}
		

	/** Data->ByteInFifo = Index - Data->Index; */
	Data->Index += Data->ByteInFifo;
	Num = MIN(APPI2C_FIFO_LEN, Data->Size - Data->Index);
	Data->ByteInFifo = Num;

	/* clear receive interrupt */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_SHFT);
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
	/* clear nack bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
	/* flush the rx data FIFO */
	HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);

	if (Num == 0)
	{
		return Data->Size;	
	}
	// use normal receive full method
	HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (Num - 1) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);
	return Data->Index;
}

void APPI2C_IntHandler(void)
{
	uint32_t Len=0;

	NVIC_DisableIRQ(APPI2C_IRQn);

	if (APPI2C_MSTATUS_IDLE == AppI2c.MainStatus
		|| APPI2C_MSTATUS_STOP == AppI2c.MainStatus)
	{
		/* Clear all interrupt bit */
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F);

		/* disable-enable to release clk */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		
		NVIC_EnableIRQ(APPI2C_IRQn);
		return;	
	}

	/*  blocking mode don't need interrupt handler  */
	if (APPI2C_MASK_IS_SET(AppI2c.Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_BLOCKING))
	{
		/* Clear all interrupt bit */
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F);
		return;	
	}


	/** 1. transmit */
	AppI2c.SubStatus = APPI2C_GetSubStatus();
	/* Clear all interrupt bit */
	HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F);
	if (((APPI2C_MSTATUS_WAIT_FOR_TRANSMIT == AppI2c.MainStatus)
		&& (APPI2C_STATUS_ADDRESSREAD == AppI2c.SubStatus))
		|| ((APPI2C_MSTATUS_TRANMITING == AppI2c.MainStatus)
			&&(APPI2C_STATUS_FIFO_SEND_DONE == AppI2c.SubStatus))
		|| ((APPI2C_MSTATUS_WAIT_FOR_TRANSMIT == AppI2c.MainStatus)
			&& (APPI2C_STATUS_ADDRESSWRITE == AppI2c.SubStatus)
			&& (QAPI_APPI2C_ADDR_10BIT_E == AppI2c.AddrMode)))
	{
		/* 1.1 10bit transmit will first receive a addresswrite from master */
		if (QAPI_APPI2C_ADDR_10BIT_E == AppI2c.AddrMode
			&& APPI2C_STATUS_ADDRESSWRITE == AppI2c.SubStatus)
		{
			uint32_t TempLen = ((AppI2c.Data.Size > APPI2C_FIFO_LEN)? APPI2C_FIFO_LEN : AppI2c.Data.Size);
			/** uint32_t TempLen = 1; */
			/* for 10bit mode, read operation will send a write signal firstly */
			HWIO_PERIPH_APP_I2C_CONTROL_2_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_BMSK, (TempLen) <<  HWIO_PERIPH_APP_I2C_CONTROL_2_RXVLBY_SHFT);
			HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
			AppI2c.SubStatus = APPI2C_STATUS_NODATA;	
			NVIC_EnableIRQ(APPI2C_IRQn);
			return;
		}
		else if (QAPI_APPI2C_ADDR_10BIT_E == AppI2c.AddrMode
			&& APPI2C_STATUS_ADDRESSREAD == AppI2c.SubStatus)
		{
			/* flush the rx data FIFO */
			HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);
		}
		/* 1.2 normal transmit */
		/* return bytes which have been sent. */
		Len = APPI2C_StepWriteBuf(&(AppI2c.Data));
		AppI2c.SubStatus = APPI2C_STATUS_FIFO_SEND_RELOAD;
		if (APPI2C_MSTATUS_WAIT_FOR_TRANSMIT == AppI2c.MainStatus)
		{
			AppI2c.PreMainStatus = AppI2c.MainStatus;
			AppI2c.MainStatus = APPI2C_MSTATUS_TRANMITING;
		}

		/* All data send done. */
		if (AppI2c.Data.Size == Len)
		{
			AppI2c.PreMainStatus = AppI2c.MainStatus;
			AppI2c.MainStatus = APPI2C_MSTATUS_STOP;
			AppI2c.SubStatus = APPI2C_STATUS_TRANSFER_DNOE;

			AppI2c.UserCbParam.Buf = AppI2c.Data.Buf;
			AppI2c.UserCbParam.UserSize = AppI2c.Data.Size;
			AppI2c.UserCbParam.ActualSize = AppI2c.Data.Size;
			AppI2c.UserCbParam.IsGnCall = false;
			qapi_TSK_Signal_Task(AppI2c.I2cTskHandle, APPI2C_TSK_EVENT_STATUS_STEP);
			/** AppI2c.UserCallBack(QAPI_APPI2C_STATUS_DONE_E, AppI2c.UserCbParam); */

			AppI2c.PreMainStatus = AppI2c.MainStatus;
			AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;	
		}
	   	else
	   	{
			/* kick start send again. */
			HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
		}
	}
	/** 2. stop */
	else if ( APPI2C_STATUS_TIMEOUT == AppI2c.SubStatus
				|| APPI2C_STATUS_STOP == AppI2c.SubStatus
				|| APPI2C_STATUS_NACK == AppI2c.SubStatus)
	{
		if (QAPI_APPI2C_ADDR_10BIT_E == AppI2c.AddrMode
			&& APPI2C_MSTATUS_WAIT_FOR_TRANSMIT == AppI2c.MainStatus)
		{
			/* the restart will be get a stop signal */
			/* clear stop/timrout bit */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
			/* clear nack bit */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
			AppI2c.SubStatus = APPI2C_STATUS_NODATA;	
			NVIC_EnableIRQ(APPI2C_IRQn);
			return;
		}

		if ((APPI2C_MSTATUS_WAIT_FOR_TRANSMIT == AppI2c.MainStatus)
			|| (APPI2C_MSTATUS_TRANMITING == AppI2c.MainStatus))
		{
			AppI2c.Data.ByteInFifo = APPI2C_GetFifoRemainNum(APPI2C_MSTATUS_TRANMITING);
			AppI2c.Data.Index += AppI2c.Data.ByteInFifo;
			/* clear the interrupt */
			/* clear fifo tx empty bit */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTXEP_SHFT);
			/* clear stop/timrout bit */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
			/* clear nack bit */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLNAST_SHFT);
			/* flush the FIFO in case the one byte left */
			HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_TX_FIFO_FLUSH_SHFT);
		} else if ((APPI2C_MSTATUS_WAIT_FOR_RECEIVE == AppI2c.MainStatus)
				   || (APPI2C_MSTATUS_RECEIVING == AppI2c.MainStatus))
		{
			AppI2c.Data.ByteInFifo = APPI2C_GetFifoRemainNum(APPI2C_MSTATUS_RECEIVING);

			/* read remain data */
			for (int i=0; i<ROUND_DOWN(AppI2c.Data.ByteInFifo, 2); i+=2)		
			{
				*(uint16_t *)(AppI2c.Data.Buf + AppI2c.Data.Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE);
				AppI2c.Data.Index += 2;
				// need to write to rx data register to increase the fifo index.
				HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);
			}

			if (AppI2c.Data.ByteInFifo % 2)
			{
				*(AppI2c.Data.Buf + AppI2c.Data.Index) = HWIO_PERIPH_APP_I2C_RX_DATA_IN(PERIPH_APP_I2C_REG_BASE) & 0xFF;
				AppI2c.Data.Index += 1;
				// need to write to rx data register to increase the fifo index.
				HWIO_PERIPH_APP_I2C_RX_DATA_OUT(PERIPH_APP_I2C_REG_BASE, 0x0);
			}
			
			/* clear receive interrupt */
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLRXFL_SHFT);
			HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_CLEAR_SLTRCP_SHFT);
			/* flush the rx data FIFO */
			HWIO_PERIPH_APP_I2C_FIFO_CONTROL_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_FIFO_CONTROL_RX_FIFO_FLUSH_SHFT);
		}

		AppI2c.PreMainStatus = AppI2c.MainStatus;
		AppI2c.MainStatus = APPI2C_MSTATUS_STOP;

		AppI2c.UserCbParam.Buf = AppI2c.Data.Buf;
		AppI2c.UserCbParam.UserSize = AppI2c.Data.Size;
		AppI2c.UserCbParam.ActualSize = AppI2c.Data.Index;
		AppI2c.UserCbParam.IsGnCall = false;

		qapi_TSK_Signal_Task(AppI2c.I2cTskHandle, APPI2C_TSK_EVENT_STATUS_STEP);

	} 
	/** 3. receive */
	else if (((APPI2C_MSTATUS_WAIT_FOR_RECEIVE == AppI2c.MainStatus)
		&& (APPI2C_STATUS_ADDRESSWRITE == AppI2c.SubStatus))
		|| ((APPI2C_MSTATUS_RECEIVING == AppI2c.MainStatus)
			&&(APPI2C_STATUS_FIFO_RECEIVE_DONE == AppI2c.SubStatus)))
	{
		/* 2 slave receive */
		/* 2.1 general receive */

		if (APPI2C_MSTATUS_WAIT_FOR_RECEIVE == AppI2c.MainStatus)
		{
			APPI2C_StepReceiveBufStart(&(AppI2c.Data));
			AppI2c.PreMainStatus = AppI2c.MainStatus;
			AppI2c.MainStatus = APPI2C_MSTATUS_RECEIVING;	
		}
		else
		{
			Len = APPI2C_StepReceiveBuf(&(AppI2c.Data));
			AppI2c.SubStatus = APPI2C_STATUS_FIFO_RECEIVE_FETCH;
		}

		if ((APPI2C_FIFO_LEN > (AppI2c.Data.Size - Len))
			&& ((AppI2c.Data.Size - Len) > 0))
		{
			// send NACK
			HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_ACK_SHFT);
		}
		/* All data receive done. */
		if (AppI2c.Data.Size == Len)
		{

			AppI2c.PreMainStatus = AppI2c.MainStatus;
			AppI2c.MainStatus = APPI2C_MSTATUS_STOP;
			AppI2c.SubStatus = APPI2C_STATUS_TRANSFER_DNOE;

			AppI2c.UserCbParam.Buf = AppI2c.Data.Buf;
			AppI2c.UserCbParam.UserSize = AppI2c.Data.Size;
			AppI2c.UserCbParam.ActualSize = AppI2c.Data.Size;
			AppI2c.UserCbParam.IsGnCall = false;

			qapi_TSK_Signal_Task(AppI2c.I2cTskHandle, APPI2C_TSK_EVENT_STATUS_STEP);
		}
		else
		{
			// kick start receive
			HWIO_PERIPH_APP_I2C_CONTROL_3_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_3_SLCNFDN_SHFT);
		}
	} 
	/** 4. general call */
   	else if ((APPI2C_STATUS_GNCALL == AppI2c.SubStatus)
			   && (APPI2C_MSTATUS_WAIT_FOR_RECEIVE == AppI2c.MainStatus))
	{
		uint32_t ReturnSize;
		AppI2c.PreMainStatus = AppI2c.MainStatus;
		AppI2c.MainStatus = APPI2C_MSTATUS_RECEIVING;	

		/*  handler general call */
		APPI2C_HandleGncall(AppI2c.Data.Buf, &ReturnSize);

		AppI2c.UserCbParam.Buf = AppI2c.Data.Buf;
		AppI2c.UserCbParam.UserSize = AppI2c.Data.Size;
		AppI2c.UserCbParam.ActualSize = ReturnSize;
		AppI2c.UserCbParam.IsGnCall = true;
		qapi_TSK_Signal_Task(AppI2c.I2cTskHandle, APPI2C_TSK_EVENT_STATUS_STEP);

		AppI2c.PreMainStatus = AppI2c.MainStatus;
		AppI2c.MainStatus = APPI2C_MSTATUS_IDLE;	
	}
	else
	{
		/* Clear all interrupt bit */
		HWIO_PERIPH_APP_I2C_CLEAR_SL_STATUS_1_OUT(PERIPH_APP_I2C_REG_BASE, 0x85F);

		/* disable-enable to release clk */
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (0) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
		HWIO_PERIPH_APP_I2C_CONTROL_1_OUTM(PERIPH_APP_I2C_REG_BASE,  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_BMSK, (1) <<  HWIO_PERIPH_APP_I2C_CONTROL_1_SL1EN_SHFT);
	}

    NVIC_EnableIRQ(APPI2C_IRQn);
	return;
}

static uint32_t APPI2C_TransferTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
	APPI2C_t *I2c = (APPI2C_t *)(UserParam);
	
	/* only non-blocking mode need a task. */
	/* this shouldn't happened */
	if (APPI2C_MASK_IS_SET(I2c->Mode, QAPI_APPI2C_MODE_BLOCKING_MASK, QAPI_APPI2C_MODE_BLOCKING)) 
	{
		return QAPI_TSK_INFINITE_WAIT;
	}

	if (AppI2c.UserCallBack != NULL)
	{
		I2c->UserCallBack(APPI2C_SubStatus2ApiStatus(I2c->SubStatus), I2c->UserCbParam);

	}
	
	return QAPI_TSK_INFINITE_WAIT;	

}
