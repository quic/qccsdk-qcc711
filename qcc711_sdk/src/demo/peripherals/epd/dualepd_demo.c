/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include "qapi_heap.h"
#include "qapi_types.h"
#include "qcli_api.h"
#include "qapi_gpio.h"
#include "qapi_spi.h"
#include "qapi_task.h"
#include "epd_demo.h"
#include "qapi_flash.h"
#include "qapi_timer.h"
#include "image.h"

/*-------------------------------------------------------------------------
 * Preprocessor DefinitIons and Constants
 *-----------------------------------------------------------------------*/

/** EPD portable part */
#define EPD_MAX_CLK_RATE_KHZ 10000

/** epd demo part. */
#define EINK_DBG
#ifdef EINK_DBG
#define EINK_PRINTF(...)     QCLI_Printf(QCLI_Eink_Handle, __VA_ARGS__)
#else
#define EINK_PRINTF(x, ...)
#endif

#define EPD_SPI_INSTANCE QAPI_SPI_INSTANCE_SE0_E

#define EPD_DEFAULT_CLK_KHZ  1000

#define EPD_ROUNDDOWN(s, n)  ((s) - ((s) % (n)))
#define EPD_ROUNDUP(s, n)    (EPD_ROUNDDOWN(((s) + (n)- 1), (n)))

#define EPD_TAG_NUM				(4)
#define EPD_TAG_MONO_HALF_SIZE	(40320)
#define EPD_FLASH_TAG_SIZE		(EPD_TAG_MONO_HALF_SIZE * 2 * EPD_TAG_NUM * 2)
#define EPD_FLASH_BLOCK_NUM   ((EPD_ROUNDUP(EPD_FLASH_TAG_SIZE, 4096)) / 4096)

#define EPD_FLASH_START_BLOCK (0)
#define EPD_FLASH_START_ADDR  (0)

#define TAG_LOOP_SIZE  32
/*-------------------------------------------------------------------------
 * Type DeclaratIons
 *-----------------------------------------------------------------------*/
/** List of supported displays.
 */
typedef enum
{
	EPD_TAG_BLACK,
	EPD_TAG_WHITE,
	EPD_TAG_RED
} EPD_TagColor_t;

typedef enum
{
    EPD_MODEL_E2266FS093,  /**< 2.66",  152 * 296, Spectra (E4) black/red. */
	EPD_MODEL_WAVESHARE4_2,
} EPD_ModelType_t;

/** Types of step in the Command Sequence. */
typedef enum
{
    EPD_STEP_TYPE_DATA,         /**< An EPD Data code. */
    EPD_STEP_TYPE_COMMAND,      /**< An EPD Command code. */
    EPD_STEP_TYPE_CMDDATA,      /**< An EPD Command and Data code. */
    EPD_STEP_TYPE_DELAY,        /**< Delay in ms. */
    EPD_STEP_TYPE_END,          /**< There must be one of these at the End of Sequence. */
    EPD_STEP_TYPE_FRAME,        /**< Frame data. */
    EPD_STEP_TYPE_RESET,        /**< Change the state of the Reset PIO. */
    EPD_STEP_TYPE_STOP1,        /**< First part of the stop Sequence. */
    EPD_STEP_TYPE_STOP2,        /**< Second part of the stop Sequence. */
    EPD_STEP_TYPE_TEMP,         /**< Send Temperature. */
    EPD_STEP_TYPE_WAIT_BUSY,    /**< Wait for the busy PIO to raise. */
} EPD_StepType_t;

typedef struct
{
	uint32_t RamStart;
	uint32_t RamSize;
	uint32_t FlashStartSet;
	uint32_t FlashSize;
	uint32_t EraseStart;
	uint32_t EraseNum;
} EPD_FlashRegionMap_t;

/** An EPD Command and Data , 1 byte for Command. */
typedef struct
{
    uint8_t DataBytes;          /**< Number of data bytes, including both command and data bytes */
    uint8_t Buffer[4];          /**< Spi command and Data, for most epd the size of command is 1 byte */
} EPD_StepCmdData_t;

/** An EPD Command register, only 1 byte for now. */
typedef struct
{
    uint8_t DataBytes;          /**< Number of data bytes for this Command . */
    uint8_t Buffer[4];          /**< Spi command, for most epd the size of command is 1 byte */
} EPD_StepCommand_t;

/** An EPD Command data part, less than 4 byte for now. */
typedef struct
{
    uint8_t DataBytes;          /**< Number of data bytes for this data . */
    uint8_t Buffer[4];          /**< data following the command */
} EPD_StepData_t;

/** Delay before the next step. */
typedef struct
{
    uint16_t DelayMs;           /**< Delay in ms (can be zero). */
} EPD_StepDelay_t;

/** There must be one of these at the end of sequence. */
typedef struct
{
	uint32_t Reserve;
} EPD_StepEnd_t;

/** Send Frame start Command and call the app Frame callback. */
typedef struct
{
    uint8_t FrameId;            /**< Frame id to send to the callback. */
} EPD_StepFrame_t;

/** Set the epd->Reset pin to the required Level. */
typedef struct
{
    qbool_t GpIoLevel;          /**< Required logic Level , true=high, false = low. */
} EPD_StepReset_t;

/** Shut down and set all pins to low. */
typedef struct
{
	uint32_t Reserve;
} EPD_StepStop1_t;

/** Part 2 of stop (after a Delay). */
typedef struct
{
	uint32_t Reserve;
} EPD_StepStop2_t;

/** Send Temperature. */
typedef struct
{
    uint8_t Command[2];         /**< 1 byte for Command and 1byte for uint8 Temp data. */
} EPD_StepTemp_t;

/** Wait for the busy pin.
 * Give up after Delay_ms_max ms.  Timeout if the busy pin is not connected.
 */
typedef struct
{
    uint16_t DelayMsInc;        /**< How often to check. */
    uint16_t DelayMsMax;        /**< Give up waiting after this many ms. */
} EPD_StepWaitBusy_t;

/** Each step in the Command Sequence. */
typedef struct
{
    EPD_StepType_t StepType;
    union {
        EPD_StepData_t    Data;
        EPD_StepCommand_t Command;
		EPD_StepCmdData_t CmdData;
        EPD_StepDelay_t Delay;
        EPD_StepEnd_t End;
        EPD_StepFrame_t Frame;
        EPD_StepReset_t Reset;
        EPD_StepStop1_t Stop1;
        EPD_StepStop2_t Stop2;
        EPD_StepTemp_t Temp;
        EPD_StepWaitBusy_t WaitBusy;
    } u;
} EPD_Step_t;

/** Map driver and data to a Model. */
typedef struct
{
    EPD_ModelType_t Model;
    EPD_Step_t *Sequence;
	uint16_t SeqNum;
    uint16_t Width;
    uint16_t Height;
    uint16_t Frames;        /* Number of colours (not including base colour). */
} EPD_ModeData_t;

/** epd core aprt. */
typedef enum 
{
    EPD_OK,
    EPD_ERR,
    EPD_MALLOC_FAIL,
    EPD_PARAM_ERR,
    EPD_TSK_CREATE_FAIL,
} EPD_Ret_t;

typedef enum 
{
    EPD_SPI_DONE,
    EPD_SPI_FAIL,
} EPD_SpiResultStatus_t;

typedef enum 
{
    EPD_TAG_SOURCE_RRAM,
    EPD_TAG_SOURCE_FLASH,
} EPD_TagSource_t;

/**
    EPD setting by user.
*/
typedef struct 
{
    qbool_t Valid; /**< 0-user not set,using default setting, 1-using user's setting */
    qbool_t Mode;
    qbool_t Blocking;
    qbool_t Dma;   /**< 0-disable, 1-enable */
    uint32_t ClkRateKhz;
} EPD_UserSet_t ;

/**
    EPD Spi Handle and config.
*/
typedef struct 
{
    uint32_t Handle;
    qbool_t Mode;           /**< see qapi_SPI_Mode_t */
    qbool_t Blocking;       /**< If using Spi polling or interrupt Mode */
    qbool_t Dma;            /**< If enable Dma Mode */
    qapi_SPI_CB_t CallBack; /**< callback when enbale Spi non-Blocking Mode */
    uint16_t ClkRateKhz; 
} EPD_Spi_t;

/**
    EPD Frame configuratIon.
*/
typedef struct 
{
    uint16_t Width;
    uint16_t Height;
    uint16_t FrameNum;
} EPD_Frame_t;

/**
    EPD GPIO pin configuratIon.
*/
typedef struct 
{
    qapi_GPIO_Id_t Busy;		/**< Indicate if the eink is busy */
    qapi_GPIO_Id_t Reset;		/**< Reset the inside eink register */
	qapi_GPIO_Id_t BusSelect;	/**< Low - 4wire8bit, High - 3wire9bit */
	qapi_GPIO_Id_t En;			/**< Enable the eink, low level valid */
} EPD_GpIo_t;

typedef struct 
{
    uint32_t Offset;	/**< Offset of tag data in address space */
    uint32_t Source;    /**< 0:read from RRAM, 1:read from flash  */
    uint32_t TagNum;    /**< which Tag will be display */
} EPD_TagStorage_t;

/**
    EPD configuratIon.  An instance of this is required for each display.
*/
typedef struct 
{
    EPD_Spi_t Spi;
    EPD_Step_t *Sequence; /**< Sequence of steps. */
	uint32_t SeqNum;	  /**< Sequence step number */
    EPD_Frame_t Frame;
    EPD_GpIo_t  Io;
    EPD_TagStorage_t Tag;
    void * StepTaskHandle;
    uint16_t StepId;
    uint16_t WaitBusyDelayMs;  /**< record how much time has been added up */
    uint8_t Temp;       /**< Temperature for eink calibratIon */ 
} EPD_t;

/*-------------------------------------------------------------------------
 * FunctIon DeclaratIons
 *-----------------------------------------------------------------------*/
/** EPD portable part. */
static QCLI_Command_Status_t cmd_Epd_DualEinkConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Epd_DualEinkDisplayTag(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Epd_DualEinkShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Epd_DualEinkSetFlash(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Epd_DualEinkReadTest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
EPD_t *EPD_NewEpdInstance(EPD_UserSet_t *Set);
EPD_Ret_t EPD_HwInit(EPD_t *Epd);

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
/** Sequence of Delays, Commands etc. for driving the EPD. */
qapi_SPI_Transfer_t G_EPD_Transfer;
EPD_t *G_EPD_EpdHandle = NULL;
static qbool_t G_EPD_Finsh = true;
static qbool_t G_EPD_FlashIsMap = false;
static void *G_EPD_FlashHandler = NULL;

/** Map driver and data to a Model.  Array must be in EPD_ModelType_t order.
 * "Model" is to validate that the data is in the correct order.
 */
/** const EPD_ModeData_t G_EPD_ModelTab[] = */
/** { */
/**     {EPD_MODEL_E2266FS093, EPD_StepTab,  sizeof(EPD_StepTab)/sizeof(EPD_StepTab[0]), 152, 296, 2}, */
/**     {EPD_MODEL_WAVESHARE4_2, EPD_StepTab,  sizeof(EPD_StepTab)/sizeof(EPD_StepTab[0]), 400, 300, 2}, */
/** }; */

EPD_UserSet_t  G_EPD_UserSet = {
    .Valid = false,
    .Mode = QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E,
    .Blocking = true,
    .Dma = true,
    .ClkRateKhz = EPD_DEFAULT_CLK_KHZ,
};

QCLI_Group_Handle_t QCLI_Eink_Handle;  /* Handle for our QCLI Command Group. */

const QCLI_Command_t EPD_CMD_List[] =
{
    /* cmd_function              cmd_string    usage_string           description */
    {cmd_Epd_DualEinkConfig,     "Config",     "<Mode> <ClkRateKhz>", "set spi mode"},
    {cmd_Epd_DualEinkDisplayTag, "DisplayTag", "<Source> <TagNum>",   "display tag from RRAM or flash"},
    {cmd_Epd_DualEinkShowConfig, "ShowConfig", "",                    "show current config"},
    {cmd_Epd_DualEinkSetFlash,   "SetFlash",   "<Cnt>",               "write tag data from rram to flash and map to system address, or unset"},
    {cmd_Epd_DualEinkReadTest,   "Read",       "",                    "read the 80 bytes mtp data"}
};

const QCLI_Command_Group_t EPD_CMD_Group =
{
    "EPD",
    (sizeof(EPD_CMD_List) / sizeof(EPD_CMD_List[0])),
    EPD_CMD_List
};

/*-------------------------------------------------------------------------
 * FunctIon DefinitIons
 *-----------------------------------------------------------------------*/
/**
   @brief Config eink's Spi Mode.

   If not calling this functIon, eink will use a defualt setting.

*/
static QCLI_Command_Status_t cmd_Epd_DualEinkConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	if (true != G_EPD_Finsh) {
		EINK_PRINTF("Another eink demo not finished yet!\n");
		return QCLI_STATUS_ERROR_E;
	}
    if (Parameter_Count != 2) {
		EINK_PRINTF("Wrong usage!:\n"
					"config <mode> <kHz>\n\t"
					"mode: 0->3wire 9bit, 1->4wire 8bit\n\t"
					"Khz: frequence\n");
        return QCLI_STATUS_ERROR_E;
    }

    uint16_t ClkRateKhz = Parameter_List[1].Integer_Value;

    if (ClkRateKhz > EPD_MAX_CLK_RATE_KHZ) {
        EINK_PRINTF("[err]The setting freq:%x Khz is greater than epd max clk freq:%xKhz\n", ClkRateKhz, EPD_MAX_CLK_RATE_KHZ);
        return QCLI_STATUS_ERROR_E;
    }
    G_EPD_UserSet.Valid = true;
    G_EPD_UserSet.Mode = Parameter_List[0].Integer_Value == 1 ? QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E:QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E;
    G_EPD_UserSet.ClkRateKhz = ClkRateKhz;

	EINK_PRINTF("Config success!\n\t"
				"freq: %d KHz\n\t", ClkRateKhz);

    return QCLI_STATUS_SUCCESS_E;
}


static qbool_t	EPD_CheckConfig(EPD_UserSet_t *Set, uint32_t Source)
{
	if (EPD_TAG_SOURCE_FLASH == Source &&
			false == Set->Dma) 
	{
		return false;	
	}

	return true;
}

/**
   @brief Start eink and show Tags by number.

   The Tag images is storged in RRAM or flash

*/
#define Masterfm1        (uint8_t *)&Image_970_Masterfm_01
#define Masterfm2        (uint8_t *)&Image_970_Masterfm_02
#define Slavefm1         (uint8_t *)&Image_970_Slavefm_01
#define Slavefm2         (uint8_t *)&Image_970_Slavefm_02
#define RESET_PIN QAPI_GPIO_ID15_E
#define BUSY_PIN QAPI_GPIO_ID22_E
#define HIGH QAPI_GPIO_HIGH_VALUE_E
#define LOW QAPI_GPIO_LOW_VALUE_E

static void Epd_DigitalWrite(uint32_t pin, uint32_t val)
{
	qapi_GPIO_Set(pin, val);
}

static uint32_t Epd_DigitalRead(uint32_t pin)
{
	qapi_GPIO_Value_t val;
	qapi_GPIO_Get(pin, &val);
	return val;
}

static void Epd_Delay(uint32_t ms)
{
	qapi_TMR_Delay_Us(ms);
}

/* send command multiple cs client */
static void Epd_SendCmdMs(uint8_t data[], uint32_t n, uint32_t cs) {

	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = cs; // 0x01-master cs only, 0x02-slave cs only, 0x03-both cs

	G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
}

static void Epd_SendDataMs(uint8_t data[], uint32_t n, uint32_t cs) {

	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = cs; // 0x01-master cs only, 0x02-slave cs only, 0x03-both cs

	G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
}

static void Epd_SendData(uint8_t data[], uint32_t n) {

	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = 0x3; // both cs

	G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
}

static void Epd_SendIndexData(uint8_t cmd, uint8_t data[], uint32_t n) {

	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	uint8_t buf = cmd;

	G_EPD_Transfer.TxBuf = &buf;
	G_EPD_Transfer.TxLen = 1;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = 0x3; // both cs

	G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);

    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);


	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
}

static void Epd_SendIndexDataM(uint8_t  cmd, uint8_t data[], uint32_t n)
{
	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	uint8_t buf = cmd;

	G_EPD_Transfer.TxBuf = &buf;
	G_EPD_Transfer.TxLen = 1;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = 0x1; // master1 cs

	G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);

    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);


	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);

}

static int Epd_ReadOtp_Core(EPD_t *Epd, uint8_t Cs, uint8_t CsToggle, uint8_t *TxData, uint16_t TxLen, uint8_t *RxData, uint8_t RxLen)
{
    qapi_Status_t Res;
    EPD_Spi_t *Spi = &(Epd->Spi);

    if( Cs != 1 && Cs != 2 )
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if(!CsToggle)
    {
        G_EPD_Transfer.TxBuf = TxData;
        G_EPD_Transfer.TxLen = TxLen;
        G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_NWIRE_MUL_CS | QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
        G_EPD_Transfer.XferInfo.Master.CsLine = Cs;

        Res = qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
        if(Res != QAPI_OK)
        {
            G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_NWIRE_MUL_CS | QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
            G_EPD_Transfer.XferInfo.Master.CsLine = 0;
            return Res;
        }
        
        G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_NWIRE_MUL_CS | QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
        G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_NWIRE_MUL_CS);
        G_EPD_Transfer.XferInfo.Master.CsLine = Cs;
        G_EPD_Transfer.TxBuf = NULL;
        G_EPD_Transfer.TxLen = 0;
    }
    else
    {
        G_EPD_Transfer.TxBuf = TxData;
        G_EPD_Transfer.TxLen = TxLen;
        G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_NWIRE_MUL_CS | QAPI_SPI_XFER_FWORD_COMMAND);
        G_EPD_Transfer.XferInfo.Master.CsLine = Cs;
    }

    G_EPD_Transfer.RxBuf = RxData;
    G_EPD_Transfer.RxLen = RxLen;
    
    Res=qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
    G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_NWIRE_MUL_CS | QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    G_EPD_Transfer.XferInfo.Master.CsLine = 0;

    return Res;
}

static void Epd_ReadMtpM(void)
{
	qapi_Status_t Res;

	/* write read command before reading */
	uint8_t data1[] = {0x00, 0x00};
	Epd_SendIndexDataM(0xA1, data1, 1);

	data1[0]=0x80;
	Epd_SendIndexDataM(0xA7, data1, 1);

	data1[0]=0x00; data1[1]=0x40;
	Epd_SendIndexDataM(0xA3, data1, 2);

	uint8_t data=0xA8;
	/* mtp data include 1 dummy byte and 80 byte data */
	uint8_t mtp[81];
	memset(mtp, 0, 81);

	Res = Epd_ReadOtp_Core(G_EPD_EpdHandle, 1, 1, &data, 1, &(mtp[0]), 81);
	if (Res != QAPI_OK)
	{
		EINK_PRINTF("epd read command fail:%d\n", Res);
		return;
	}

	EINK_PRINTF("Reading the mtp memory data:\n");
	for(int i=0; i<81; i++) {
		EINK_PRINTF("0x%x, ", mtp[i]);
	}
}

static void Epd_SendIndexDataS(uint8_t  cmd, uint8_t data[], uint32_t n)
{

	EPD_Spi_t *Spi = &(G_EPD_EpdHandle->Spi);

	uint8_t buf = cmd;

	G_EPD_Transfer.TxBuf = &buf;
	G_EPD_Transfer.TxLen = 1;

	G_EPD_Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_NWIRE_MUL_CS;
	G_EPD_Transfer.XferInfo.Master.CsLine = 0x2; // master2 cs

	G_EPD_Transfer.XferInfo.Master.Flags |= (QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);

    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);


	G_EPD_Transfer.TxBuf = data;
	G_EPD_Transfer.TxLen = n;

	G_EPD_Transfer.XferInfo.Master.Flags &= ~(QAPI_SPI_XFER_FWORD_COMMAND | QAPI_SPI_XFER_RWORD_COMMAND);
    qapi_SPI_Transfer((qapi_SPI_Instance_t)(Spi->Handle), &G_EPD_Transfer);
}


static void SendMonoData(EPD_TagColor_t TagColor)
{
	uint8_t ColorM[TAG_LOOP_SIZE], Cm;
	uint8_t ColorS[TAG_LOOP_SIZE], Cs;
	uint8_t data3[] = { 0x3b, 0x00, 0x14 };         

	switch (TagColor) 
	{
		case EPD_TAG_BLACK: Cm=0xFF,Cs=0x0; break;
		case EPD_TAG_WHITE: Cm=0x0,Cs=0x0; break;
		case EPD_TAG_RED: Cm=0x0,Cs=0xFF; break;
	}

	memset(ColorM, Cm, TAG_LOOP_SIZE);
	memset(ColorS, Cs, TAG_LOOP_SIZE);

	Epd_SendIndexData( 0x12, data3, 3 );    //RAM_RW for Master
	Epd_SendIndexData(0x10, NULL, 0);
	for (int i=0; i<EPD_TAG_MONO_HALF_SIZE/TAG_LOOP_SIZE; i++)
	{
		Epd_SendData(ColorM, TAG_LOOP_SIZE); //First frame for Master
	}
	Epd_SendIndexData( 0x12, data3, 3 );    //RAM_RW for Master
	Epd_SendIndexData(0x11, NULL, 0);
	for (int i=0; i<EPD_TAG_MONO_HALF_SIZE/TAG_LOOP_SIZE; i++)
	{
		Epd_SendData(ColorS, TAG_LOOP_SIZE);   //Second frame for Master
	}
}


static QCLI_Command_Status_t cmd_Epd_DualEinkDisplayTag(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    EPD_Ret_t    Ret;
    EPD_t *EpdHandle;
    uint32_t Source;
	uint32_t Offset;
	uint32_t Start;

    if (Parameter_Count != 2) {
		EINK_PRINTF("Wrong usage:\nDisplay <source> <tagnum>\n\t"
				"source: 0: rram, 1: flash\n\t"
				"tagnum: 0~maxtagnum\n\n"
				"Note: If flash is used as tag source, it must be initialized first.\n\t"
				"For now it can be done in the FLASH demo submenu.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value == 0) {
        Source = EPD_TAG_SOURCE_RRAM; 
    } 
	else if (Parameter_List[0].Integer_Value == 1) 
	{
        Source = EPD_TAG_SOURCE_FLASH;
    } 
	else 
	{
        return QCLI_STATUS_ERROR_E; 
    }

    uint32_t TagNum = Parameter_List[1].Integer_Value;
	if (TagNum >= EPD_TAG_NUM)
	{
		EINK_PRINTF("Tag Index %d exceed maximum value: %d\n", TagNum, (EPD_TAG_NUM-1));
		return QCLI_STATUS_ERROR_E;
	}

    EpdHandle = EPD_NewEpdInstance(&G_EPD_UserSet);
    if (NULL == EpdHandle) 
	{
		EINK_PRINTF("Create new epd instance fail!\n");
        return  QCLI_STATUS_ERROR_E;
    }

    Ret = EPD_HwInit(EpdHandle);
    if (EPD_OK != Ret) 
	{
        return QCLI_STATUS_ERROR_E;
    }
    
    G_EPD_EpdHandle = EpdHandle;

	Epd_DigitalWrite( RESET_PIN, HIGH );       //RES# = 1
	Epd_Delay( 20 );                           //Delay 20ms
	Epd_DigitalWrite( RESET_PIN, LOW );        //RES# = 0
	Epd_Delay( 200 );                          //Delay 200ms
	Epd_DigitalWrite( RESET_PIN, HIGH );       //RES# = 1
	Epd_Delay( 200 );                           //Delay 200ms
	/** Epd_DigitalWrite( CS_PIN, HIGH );       //CS# = 1 */
	/** Epd_DigitalWrite( CSS_PIN, HIGH );       //CSS# = 1 */

	// Send image data
	uint8_t data1[] = { 0x00, 0x3b, 0x00, 0x00, 0x9f, 0x02 };         
	Epd_SendIndexData( 0x13, data1, 6 );    //DUW for Both Master and Slave
	uint8_t data2[] = { 0x00, 0x3b, 0x00, 0xa9 };         
	Epd_SendIndexData( 0x90, data2, 4 );    //DRFW for Both Master and Slave
	uint8_t data3[] = { 0x3b, 0x00, 0x14 };         

	if (EPD_TAG_SOURCE_RRAM == Source)
	{
		if (TagNum == 0)
		{
			Epd_SendIndexDataM( 0x12, data3, 3 );    //RAM_RW for Master
			Epd_SendIndexDataM( 0x10, Masterfm1, 40320 ); //First frame for Master
			Epd_SendIndexDataM( 0x12, data3, 3 );    //RAM_RW for Master
			Epd_SendIndexDataM( 0x11, Masterfm2, 40320 );   //Second frame for Master
			Epd_SendIndexDataS( 0x12, data3, 3 );    //RAM_RW for Slave
			Epd_SendIndexDataS( 0x10, Slavefm1, 40320 ); //First frame for Slave
			Epd_SendIndexDataS( 0x12, data3, 3 );    //RAM_RW for Slave
			Epd_SendIndexDataS( 0x11, Slavefm2, 40320 );   //Second frame for Slave
		}
		else
		{
			// mono color
			SendMonoData(TagNum - 1);
		}
	}
	else if (true == G_EPD_FlashIsMap)
	{
		qapi_FLASH_Get_Mapped_Address(EPD_FLASH_START_ADDR, &Start);
		Offset = Start + TagNum * EPD_TAG_MONO_HALF_SIZE * 4;
		Epd_SendIndexDataM( 0x12, data3, 3 );    //RAM_RW for Master
		Epd_SendIndexDataM( 0x10, (uint8_t *)Offset, 40320 ); //First frame for Master
		Epd_SendIndexDataM( 0x12, data3, 3 );    //RAM_RW for Master
		Epd_SendIndexDataM( 0x11, (uint8_t *)(Offset + 40320), 40320 );   //Second frame for Master
		Epd_SendIndexDataS( 0x12, data3, 3 );    //RAM_RW for Slave
		Epd_SendIndexDataS( 0x10, (uint8_t *)(Offset + 40320*2), 40320 ); //First frame for Slave
		Epd_SendIndexDataS( 0x12, data3, 3 );    //RAM_RW for Slave
		Epd_SendIndexDataS( 0x11, (uint8_t *)(Offset + 40320*3), 40320 );   //Second frame for Slave
	}
	else
	{
		EINK_PRINTF("Need map rram to flash first!\n");
		return QCLI_STATUS_ERROR_E;
	}

	EINK_PRINTF("0. frame transfer done!\n");

	//Initial COG
	uint8_t data4[] = { 0x7d};         
	Epd_SendIndexData( 0x05, data4, 1 );
	Epd_Delay(200);
	uint8_t data5[] = { 0x00};         
	Epd_SendIndexData( 0x05, data5, 1 );
	Epd_Delay( 10 );
	uint8_t data6[] = { 0x3f};         
	Epd_SendIndexData( 0xc2, data6, 1 );
	Epd_Delay( 1 );
	uint8_t data7[] = { 0x80};         
	Epd_SendIndexData( 0xd8, data7, 1 );    //MS_SYNC
	uint8_t data8[] = { 0x00};         
	Epd_SendIndexData( 0xd6, data8, 1 );    //BVSS
	uint8_t data9[] = { 0x10};         
	Epd_SendIndexData( 0xa7, data9, 1 );
	Epd_Delay( 100 );  
	Epd_SendIndexData( 0xa7, data5, 1 );
	Epd_Delay( 100 );
	uint8_t data10[] = { 0x00, 0x11 };         
	Epd_SendIndexData( 0x03, data10, 2 );    //OSC
	Epd_SendIndexDataM( 0x44, data5, 1 );  //Master  
	uint8_t data11[] = { 0x80 };         
	Epd_SendIndexDataM( 0x45, data11, 1 );    //Master 
	Epd_SendIndexDataM( 0xa7, data9, 1 );   //Master
	Epd_Delay( 100 );
	Epd_SendIndexDataM( 0xa7, data5, 1 );    //Master 
	Epd_Delay( 100 );
	uint8_t data12[] = { 0x06 };
	Epd_SendIndexDataM( 0x44, data12, 1 );     //Master 
	uint8_t data13[] = { 0x82 };
	Epd_SendIndexDataM( 0x45, data13, 1 );    //Temperature 0x82@25C
	Epd_SendIndexDataM( 0xa7, data9, 1 );    //Master 
	Epd_Delay( 100 );
	Epd_SendIndexDataM( 0xa7, data5, 1 );     //Master 
	Epd_Delay( 100 );

	Epd_SendIndexDataS( 0x44, data5, 1 );     //Slave
	Epd_SendIndexDataS( 0x45, data11, 1 );    //Slave
	Epd_SendIndexDataS( 0xa7, data9, 1 );    //Slave
	Epd_Delay( 100 );
	Epd_SendIndexDataS( 0xa7, data5, 1 );     //Slave 
	Epd_Delay( 100 );
	Epd_SendIndexDataS( 0x44, data12, 1 );    //Slave 
	Epd_SendIndexDataS( 0x45, data13, 1 );    //Temperature 0x82@25C for Slave
	Epd_SendIndexDataS( 0xa7, data9, 1 );     //Slave
	Epd_Delay( 100 );
	Epd_SendIndexDataS( 0xa7, data5, 1 );     //Master 
	Epd_Delay( 100 );

	uint8_t data14[] = { 0x25 };
	Epd_SendIndexData( 0x60, data14, 1 );    //TCON
	uint8_t data15[] = { 0x01 };
	Epd_SendIndexDataM( 0x61, data15, 1 );    //STV_DIR for Master
	uint8_t data16[] = { 0x00 };
	Epd_SendIndexData( 0x01, data16, 1 );    //DCTL
	uint8_t data17[] = { 0x00 };
	Epd_SendIndexData( 0x02, data17, 1 );    //VCOM

	//DCDC soft-start
	uint8_t  Index51_data[]={0x50,0x01,0x0a,0x01};
	Epd_SendIndexData( 0x51, &Index51_data[0], 2 );
	uint8_t  Index09_data[]={0x1f,0x9f,0x7f,0xff};
	///*
	for(int value=1;value<=4;value++){
	  Epd_SendIndexData(0x09,&Index09_data[0],1);
	  Index51_data[1]=value;
	  Epd_SendIndexData(0x51,&Index51_data[0],2);
	  Epd_SendIndexData(0x09,&Index09_data[1],1);
	  Epd_Delay(2);
	}
	//*
	for(int value=1;value<=10;value++){
	  Epd_SendIndexData(0x09,&Index09_data[0],1);
	  Index51_data[3]=value;
	  Epd_SendIndexData(0x51,&Index51_data[2],2);
	  Epd_SendIndexData(0x09,&Index09_data[1],1);
	  Epd_Delay(2);
	}
	for(int value=3;value<=10;value++){
	  Epd_SendIndexData(0x09,&Index09_data[2],1);
	  Index51_data[3]=value;
	  Epd_SendIndexData(0x51,&Index51_data[2],2);
	  Epd_SendIndexData(0x09,&Index09_data[3],1);
	  Epd_Delay(2);
	}
	for(int value=9;value>=2;value--){
	Epd_SendIndexData(0x09,&Index09_data[2],1);
	Index51_data[2]=value;
	Epd_SendIndexData(0x51,&Index51_data[2],2);
	Epd_SendIndexData(0x09,&Index09_data[3],1);
	Epd_Delay(2);
	}
	Epd_SendIndexData(0x09,&Index09_data[3],1);
	Epd_Delay(10);
	/** Serial.println("3"); */

	//Display Refresh Start 
	while( Epd_DigitalRead( BUSY_PIN ) != HIGH );
	uint8_t data18[] = { 0x3c };
	Epd_SendIndexData( 0x15, data18, 1 );    //Display Refresh
	Epd_Delay( 5 );

	EINK_PRINTF("1. refresh done!\n");
	// DCDC off
	while( Epd_DigitalRead( BUSY_PIN ) != HIGH );
	uint8_t data19[] = { 0x7f };
	Epd_SendIndexData( 0x09, data19, 1 );    
	uint8_t data20[] = { 0x7d };
	Epd_SendIndexData( 0x05, data20, 1 ); 
	Epd_SendIndexData( 0x09, data5, 1 );
	Epd_Delay(200);       
	while( Epd_DigitalRead( BUSY_PIN ) != HIGH );
	/** Epd_DigitalWrite( DC_PIN, LOW ); */
	/** Epd_DigitalWrite( CS_PIN, LOW ); */
	/** Epd_DigitalWrite( CSS_PIN, LOW ); */
	/** Epd_DigitalWrite( SDA_PIN, LOW ); */
	/** Epd_DigitalWrite( SCL_PIN, LOW ); */
	/** Epd_DigitalWrite( RESET_PIN, LOW ); */
	/** Serial.println("4"); */
	EINK_PRINTF("2. all eink done!\n");

    /* close Spi */
    qapi_SPI_Close((qapi_SPI_Instance_t)(EpdHandle->Spi.Handle));

    /* release Epd */
    qapi_Free(EpdHandle); 

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Epd_DualEinkShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    EINK_PRINTF("Eink config setting:\n");
    EINK_PRINTF("Spi mode:%s\n", G_EPD_UserSet.Mode == QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E?"4 wire 8bit":"3 wire 9bit");
    EINK_PRINTF("Spi clk rate:%d khz\n", G_EPD_UserSet.ClkRateKhz);

    if (G_EPD_EpdHandle) {
        EINK_PRINTF("Tag source:%s\n", G_EPD_EpdHandle->Tag.Source == EPD_TAG_SOURCE_RRAM?"rram":"flash");
        EINK_PRINTF("Tag offset:%x\n", G_EPD_EpdHandle->Tag.Offset);
        EINK_PRINTF("Tag num:%d\n", G_EPD_EpdHandle->Tag.TagNum);
    }

    return QCLI_STATUS_SUCCESS_E;
}

static void Epd_FillMono2Flash(uint32_t TagNum)
{
	uint8_t ColorM[TAG_LOOP_SIZE], Cm=0xFF;
	uint8_t ColorS[TAG_LOOP_SIZE], Cs=0x0;
	uint32_t Base = EPD_FLASH_START_ADDR + EPD_TAG_MONO_HALF_SIZE * 4 * (TagNum + 1);
	uint32_t LoopTime = EPD_TAG_MONO_HALF_SIZE / TAG_LOOP_SIZE;

	switch (TagNum) 
	{
		case EPD_TAG_BLACK: Cm=0xFF,Cs=0x0; break;
		case EPD_TAG_WHITE: Cm=0x0,Cs=0x0; break;
		case EPD_TAG_RED: Cm=0x0,Cs=0xFF; break;
	}

	memset(ColorM, Cm, TAG_LOOP_SIZE);
	memset(ColorS, Cs, TAG_LOOP_SIZE);

	for (int i=0; i<LoopTime; i++)     // Master first frame
	{
		qapi_FLASH_Write(Base + i*TAG_LOOP_SIZE,  TAG_LOOP_SIZE, \
							ColorM, NULL, NULL );
	}

	Base += EPD_TAG_MONO_HALF_SIZE;
	for (int i=0; i<LoopTime; i++)     // Master second frame
	{
		qapi_FLASH_Write(Base + i*TAG_LOOP_SIZE,  TAG_LOOP_SIZE, \
							ColorS, NULL, NULL );
	}
	
	Base += EPD_TAG_MONO_HALF_SIZE;
	for (int i=0; i<LoopTime; i++)    // Slave first frame
	{
		qapi_FLASH_Write(Base + i*TAG_LOOP_SIZE,  TAG_LOOP_SIZE, \
							ColorM, NULL, NULL );
	}

	Base += EPD_TAG_MONO_HALF_SIZE;
	for (int i=0; i<LoopTime; i++)   // Slave second frame
	{
		qapi_FLASH_Write(Base + i*TAG_LOOP_SIZE,  TAG_LOOP_SIZE, \
							ColorS, NULL, NULL );
	}

}

static uint32_t Epd_FillTag2Flash(void)
{
    qapi_Status_t         FlashStatus;
	uint8_t *TagArray[4] = {Masterfm1, Masterfm2, Slavefm1, Slavefm2};

	for (int i=0; i<4; i++)
	{
		FlashStatus = qapi_FLASH_Write(EPD_FLASH_START_ADDR + EPD_TAG_MONO_HALF_SIZE*i, \
					EPD_TAG_MONO_HALF_SIZE, (uint8_t *)TagArray[i], NULL, NULL );
		if (QAPI_OK != FlashStatus)
		{
			EINK_PRINTF("Flash write array %d fail, errno:%d\n", i, FlashStatus);
			return -1;
		}
	}


	for (int i=0; i<3; i++)
	{
		Epd_FillMono2Flash(i);
	}
	return 0;

}

static QCLI_Command_Status_t cmd_Epd_DualEinkSetFlash(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t         FlashStatus;

    if (Parameter_Count != 1 && Parameter_Count != 4) 
	{
		EINK_PRINTF("Wrong usage!\n"
					"SetFlash <Cnt> \n"
					"\tCnt: 0->unset, 1->set\n"
					"Note: If flash is used as tag source, it must be initialized first.\n"
					"\tFor now it can be done in the FLASH demo submenu.\n");
        return QCLI_STATUS_ERROR_E;
    }

	if (Parameter_List[0].Integer_Value == 1
		&& true == G_EPD_FlashIsMap) 
	{
		EINK_PRINTF("Flash has been mapped. It need to be unmap before remap.\n"
				    "\tSetFlash 0\n");
		return QCLI_STATUS_ERROR_E;
	}

    if (Parameter_List[0].Integer_Value == 0) 
	{  // unset
		if (false == G_EPD_FlashIsMap) 
		{
			EINK_PRINTF("Flash not be maped yet\n");
			return QCLI_STATUS_ERROR_E;
		}
		else 
		{
			FlashStatus = qapi_FLASH_Memory_Unmap(G_EPD_FlashHandler);
			if (QAPI_OK != FlashStatus) 
			{
				EINK_PRINTF("Flash unmaped failed!, errno:%d \n", FlashStatus);
				return QCLI_STATUS_ERROR_E;
			}
			G_EPD_FlashHandler = NULL;
		}
		G_EPD_FlashIsMap = false;
		EINK_PRINTF("Flash unset successed!\n");
		return QCLI_STATUS_SUCCESS_E;
	}

	// set flash
    FlashStatus = qapi_FLASH_Init(NULL);
    if (FlashStatus != QAPI_OK)
    {
        EINK_PRINTF("Error, Flash uninitialized, please set Flash first in Flash menu\n\n"
					"Note: If flash is used as tag source, it must be initialized first.\n\t"
					"For now it can be done in the FLASH demo submenu.\n");
        return QCLI_STATUS_ERROR_E;
    }
	////
	uint32_t FlashIndex = 0;
	uint32_t FlashBlockIndex = 0;

	FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E,  EPD_FLASH_START_BLOCK, EPD_FLASH_BLOCK_NUM, NULL, NULL);
	if (QAPI_OK != FlashStatus)
	{
		EINK_PRINTF("Flash erase fail, errno:%d\n", FlashStatus);
		return QCLI_STATUS_ERROR_E;
	}

	// fill all tag 
	if (Epd_FillTag2Flash())
	{
		return QCLI_STATUS_ERROR_E;
	}

	FlashStatus = qapi_FLASH_Memory_Map(EPD_FLASH_START_ADDR, EPD_ROUNDUP(EPD_FLASH_TAG_SIZE, 4096), &G_EPD_FlashHandler);
	if (QAPI_OK != FlashStatus)
	{
		EINK_PRINTF("Flash map fail, errno:%d\n", FlashStatus);
		return QCLI_STATUS_ERROR_E;
	}

	EINK_PRINTF("Flash set successed!\n");
	G_EPD_FlashIsMap = true;

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Epd_DualEinkReadTest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    EPD_Ret_t    Ret;
    EPD_t *EpdHandle;

	if ((G_EPD_UserSet.Mode != QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E)
            || (!G_EPD_UserSet.Blocking))
	{
		EINK_PRINTF("eink read must in 4 wire and blocking mode!\n");
		return QCLI_STATUS_ERROR_E;
	}

    EpdHandle = EPD_NewEpdInstance(&G_EPD_UserSet);
    if (NULL == EpdHandle) 
	{
		EINK_PRINTF("Create new epd instance fail!\n");
        return  QCLI_STATUS_ERROR_E;
    }

    Ret = EPD_HwInit(EpdHandle);
    if (EPD_OK != Ret) 
	{
        return QCLI_STATUS_ERROR_E;
    }

	/* reset */
	qapi_GPIO_Set(EpdHandle->Io.Reset, QAPI_GPIO_HIGH_VALUE_E);
	qapi_TMR_Delay_Us(5);
	qapi_GPIO_Set(EpdHandle->Io.Reset, QAPI_GPIO_LOW_VALUE_E);
	qapi_TMR_Delay_Us(5);
	qapi_GPIO_Set(EpdHandle->Io.Reset, QAPI_GPIO_HIGH_VALUE_E);
	qapi_TMR_Delay_Us(50);

	Epd_ReadMtpM();

    /* close Spi */
    qapi_SPI_Close((qapi_SPI_Instance_t)(EpdHandle->Spi.Handle));

    /* release Epd */
    qapi_Free(EpdHandle); 

	return QCLI_STATUS_SUCCESS_E;
}

void Initialize_Eink_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
	QCLI_Eink_Handle = QCLI_Register_Command_Group(NULL, &EPD_CMD_Group);
	if(QCLI_Eink_Handle)
	{
		EINK_PRINTF("Eink Registered \n");
	}
}

EPD_Ret_t EPD_GpIoInit(EPD_t *Epd)
{
    qapi_GPIO_Config_t Config = {
        .PIOFunc = 0,
        .Dir = QAPI_GPIO_INPUT_E,
        .Pull = QAPI_GPIO_PULL_UP_E, 
        .Drive = QAPI_GPIO_FAST_2MA_E,
    };

    qapi_GPIO_Config(Epd->Io.Busy, &Config);
    Config.Dir = QAPI_GPIO_OUTPUT_E;
    qapi_GPIO_Config(Epd->Io.Reset, &Config);

    return EPD_OK;
}
/** static void EPD_SpiCallBack(uint32_t Status, void* Context) */
/** { */
/**     EPD_t *Epd =  (EPD_t *)Context; */
/**  */
/**     if (Status == EPD_SPI_DONE) { */
/**         EPD_ContinueStep(Epd); */
/**     } */
/**  */
/**     return; */
/** } */

EPD_Ret_t EPD_SpiInit(EPD_Spi_t *Spi)
{
    Spi->Handle = (uint32_t)EPD_SPI_INSTANCE;
    qapi_SPI_Config_t Config = {
        .Mode = (qapi_SPI_Mode_t)(Spi->Mode),
        .Blocking = Spi->Blocking,
        .Dma = Spi->Dma,
    };

   if (QAPI_OK != qapi_SPI_Open((qapi_SPI_Instance_t)(Spi->Handle), &Config)) {
        return EPD_ERR;
   }

   return EPD_OK;
}

EPD_Ret_t EPD_HwInit(EPD_t *Epd)
{
    /** EPD_GpIoInit(Epd); */
	Epd->Io.Reset = QAPI_GPIO_ID15_E;
	Epd->Io.Busy = QAPI_GPIO_ID22_E;
	Epd->Io.BusSelect = QAPI_GPIO_ID21_E;
	Epd->Io.En = QAPI_GPIO_ID16_E;

	if (G_EPD_UserSet.Mode == QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E) {
	     qapi_GPIO_Set(Epd->Io.BusSelect, QAPI_GPIO_HIGH_VALUE_E);
	 } else {
	     qapi_GPIO_Set(Epd->Io.BusSelect, QAPI_GPIO_LOW_VALUE_E);
	}

	/** 0. Enable and select bus */
	qapi_GPIO_Set(Epd->Io.En, QAPI_GPIO_LOW_VALUE_E);

    EPD_SpiInit(&Epd->Spi);

    /** temperature's unit is degree of Celsius. 0x19 represent 25 C. */
    /** And it use a fixed value cause of no available temperature sensor. */
    /** It just have tiny effect on epd. */
    Epd->Temp = 0x19;

    return EPD_OK;
}

EPD_t *EPD_NewEpdInstance(EPD_UserSet_t *Set)
{
    EPD_t *Epd;

	Epd = qapi_Malloc(sizeof(EPD_t));
	if (NULL != Epd) 
	{
		memset(Epd, 0, sizeof(EPD_t));

		Epd->Spi.Mode = Set->Mode;
		Epd->Spi.Blocking = Set->Blocking;
		Epd->Spi.Dma = Set->Dma;
		Epd->Spi.ClkRateKhz = Set->ClkRateKhz;

		Epd->StepId = 0;

		memset(&G_EPD_Transfer, 0, sizeof(qapi_SPI_Transfer_t));
		G_EPD_Transfer.XferInfo.Master.BitsPerWord = 8;
		G_EPD_Transfer.XferInfo.Master.FreqHz = Set->ClkRateKhz * 1000;
		G_EPD_Transfer.CallbackCtxt = (void *)Epd;
		return Epd;
	} 
	else 
	{
		EINK_PRINTF("Malloc fail! \n");
	}

    return NULL;
}
