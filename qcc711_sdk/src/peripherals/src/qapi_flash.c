/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_task.h"
#include "qapi_heap.h"
#include "qapi_timer.h"
#include "qapi_flash.h"
#include "qspi.h"
#include "qspi_map.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QSPI_TRANS_MODE_BLOCKING          QSPI_DMA_POLL_MODE_E

#define PAGE_SIZE_IN_BYTES                256
#define BLOCK_SIZE_IN_BYTES               4096
#define FLASH_16MB_IN_BYTES               0x1000000

#define WRITE_STATUS_POLLING_USEC         100
#define WRITE_TIMEOUT                     5000000  /**< Time unit is usec. */
#define ERASE_STATUS_POLLING_MSEC         5
#define ERASE_TIMEOUT                     5000000  /**< Time unit is usec. */
#define READ_STATUS_POLLING_USEC          20
#define READ_STATUS_TIMEOUT               5000000  /**< Time unit is usec. */
#define CHIP_ERASE_STATUS_POLLING_MSEC    1000
#define CHIP_ERASE_TIMEOUT                500000000 /**< Time unit is usec. */

#define WRITE_ENABLE_CMD                  0x06
#define READ_STATUS_CMD                   0x05
#define READ_STATUS_2_CMD                 0x3F
#define READ_CFG_REG_CMD                  0x15
#define READ_CFG1_CMD                     0x35
#define WRITE_STATUS_CMD                  0x01
#define ENTER_4B_ADDR_CMD                 0xB7
#define WRITE_STATUS_2_CMD                0x3E
#define READ_IDENTIFICATION_CMD           0x9F

#define STATUS_WR_EN_MASK                 0x02
#define PROG_ERASE_WRITE_BUSY_BMSK        0x01
#define READ_STATUS_BUSY_MASK             0x01

#define FLASH_PID2VID(__pid__)            ((uint8_t)(__pid__))

/* Flash Manufacturer ID, from the lowest byte of device id */
#define MANUFACTURER_ID_MACRONIX          0xC2     /**< Macronix. */
#define MANUFACTURER_ID_WINBOND           0xEF     /**< Winbond. */
#define MANUFACTURER_ID_ISSI              0x9D     /**< ISSI. */

/* Winbond SPI Command */
#define WINBOND_READ_STATUS_2_CMD         0x35
#define WINBOND_READ_STATUS_3_CMD         0x15
#define WINBOND_WRITE_STATUS_2_CMD        0x31
#define WINBOND_WRITE_STATUS_3_CMD        0x11

/* Quad enable mode. */
#define ENABLE_QUAD_MODE_0                0x0
#define ENABLE_QUAD_MODE_1                0x1
#define ENABLE_QUAD_MODE_2                0x2
#define ENABLE_QUAD_MODE_3                0x3
#define ENABLE_QUAD_MODE_4                0x4
#define ENABLE_QUAD_MODE_5                0x5

#define BIT_1                             0x2
#define BIT_6                             0x40
#define BIT_7                             0x80

#define WRITE_OPERATION                   0x0
#define ERASE_OPERATION                   0x1
#define OTHER_OPERATION                   0x2

/* Flash state. */
#define FLASH_STATE_WRITE                 0x1
#define FLASH_STATE_READ                  0x2
#define FLASH_STATE_ERASE                 0x4
#define FLASH_STATE_WRITE_REG             0x8
#define FLASH_STATE_READ_REG              0x10
#define FLASH_STATE_NON_BLOCKING          0x80

/* Flash operation task event. */
#define FLASH_TSK_EVENT_TRANSFER_DONE     ((uint32_t)(1 << 0))
#define FLASH_TSK_EVENT_OPERATE_DONE      ((uint32_t)(1 << 1))
#define FLASH_TSK_EVENT_OPERATE_ERROR     ((uint32_t)(1 << 2))

#define FLASH_TSK_SHORT_WAIT              1  /**< Short wait of 1ms incase of polling timer started fail. */
#define NO_TIMER_COMPARATOR               0xFF

#define DIFF_TIME(__x__, __y__)           ((__x__) - (__y__))

#define VALID_RW_MODE(__mode__)           (((__mode__) >= QAPI_FLASH_RW_MODE_SDR_SINGLE && \
                                           (__mode__) <= QAPI_FLASH_RW_MODE_SDR_QUAD) || \
                                           ((__mode__) == QAPI_FLASH_RW_MODE_DDR_QUAD))

#define IS_QUAD_MODE(__mode__)            (((__mode__) & 0x3) == 0x3)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Structure representing flash non-blocking operation parameters.
*/
typedef struct FLASH_OperationParam_s
{
    qapi_FLASH_Operation_CB_t OperationCB; /**< The callback function for non-blocking flash operation. */
    void                     *UserParam;   /**< The user specified parameter for the callback function. */
    QSPI_Cmd_t                QspiCmd;     /**< The qspi cmd for read/writ/erase. */
    uint32_t                  Address;     /**< The start address for read/writ/erase. */
    uint32_t                  ByteCnt;     /**< The total number of data for read/write/erase. */
    uint32_t                  TriedCnt;    /**< The number of data tried to read/write/erase in last operation. */
    uint8_t                  *Buffer;      /**< The buffer pointer for read/write. */
} FLASH_OperationParam_t;

/**
   Structure representing context for flash module.
*/
typedef struct FLASH_Context_s
{
    uint8_t                 State;           /**< Flash state. */
    qapi_FLASH_Config_t    *Config;          /**< Flash specific configurations. */
    qapi_TSK_Handle_t       OperationTask;   /**< Flash operation task. */
    FLASH_OperationParam_t *OperationParam;  /**< Flash operation parameters. */
    uint8_t                 TimerComparator; /**< Flash timer comparator. */
    uint64_t                PollingStart;    /**< Record the start time of polling flash operation status. */
} FLASH_Context_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static FLASH_Context_t     FLASH_Context;
static qbool_t             FlashInitDone = false;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Read flash registers.

   @param[in]  RegOpcode  Operation code.
   @param[in]  Len        The length of register value to be read.
   @param[out] RegValue   The read out value.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t FLASH_ReadReg( uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue)
{
    QSPI_Cmd_t QspiReadReg;

    if (Len > 0 && RegValue == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    (void)QSPI_SetCmd(&QspiReadReg, RegOpcode, 0, 0, 
                      QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, false);

    if (QSPI_Cmd(&QspiReadReg, 0, RegValue, Len, QSPI_TRANS_MODE_BLOCKING))
    {
        return QAPI_OK;
    }
    else
    {
        return QAPI_ERROR;
    }
}

/**
   @brief Check flash operation error

   @param[in] OperationType  Flash operation type, WRITE_OPERATION,
                             ERASE_OPERATION, or OTHER_OPERATION.

   @return QAPI_OK on success operation or an error code on failure.
*/
static qapi_Status_t FLASH_CheckError(uint8_t OperationType)
{
    uint8_t       StatusMask = 0;
    uint8_t       ErrStatusRegister = 0;
    uint8_t       QspiStatus = 0;
    qapi_Status_t Status = QAPI_OK;
    
    switch (OperationType)
    {
        case WRITE_OPERATION:
            StatusMask = FLASH_Context.Config->WriteErrBmsk;
            ErrStatusRegister = FLASH_Context.Config->WriteErrStatusReg;
            break;

        case ERASE_OPERATION:
            StatusMask = FLASH_Context.Config->EraseErrBmsk;
            ErrStatusRegister = FLASH_Context.Config->EraseErrStatusReg;
            break;

        default:
            break;
    }

    if (ErrStatusRegister == 0)
    {
        return Status;
    }

    Status = FLASH_ReadReg(ErrStatusRegister, 1, &QspiStatus);
    if ((Status == QAPI_OK) && (QspiStatus & StatusMask))
    {
        Status = QAPI_ERROR;
    }

    return Status;
}

/**
   @brief Check flash operation status.

   @param[in] Timeout            The total time can be used for status check.
   @param[in] StatusPollingUsec  The status polling period.
   @param[in] Operation          Flash operation, WRITE_OPERATION, or
                                 ERASE_OPERATION, or OTHER_OPERATION.
   @param[in] Bmask              The bits of the status register to be checked.
   @param[in] StatusValue        The expected value for the checked status bits.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_WaitOperationDone(uint32_t Timeout, uint32_t StatusPollingUsec,
                                             uint8_t Operation, uint8_t Bmask, uint8_t StatusValue)
{
    qapi_Status_t Status = QAPI_ERROR;
    uint8_t       Result = 0;

    while (Timeout)
    {
        (void)FLASH_ReadReg(READ_STATUS_CMD, 1, &Result);
        if ((Result & Bmask) == StatusValue)
        {
            Status = FLASH_CheckError(Operation);
            break;
        }
        qapi_TMR_Delay_Us(StatusPollingUsec);
        Timeout -= StatusPollingUsec;
    }

    return Status;
}

/**
   @brief Flash write enable.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_WriteEnable()
{
    qapi_Status_t Status;
    QSPI_Cmd_t    QspiWriteEnable;

    (void)QSPI_SetCmd(&QspiWriteEnable, WRITE_ENABLE_CMD, 0, 0, 
                      QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, false);

    QSPI_Cmd(&QspiWriteEnable, 0, NULL, 0, QSPI_TRANS_MODE_BLOCKING);

    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC, 
                                     OTHER_OPERATION, STATUS_WR_EN_MASK, STATUS_WR_EN_MASK);
    return Status;
}

/**
   @brief Write flash registers.

   @param[in]  RegOpcode  Operation code.
   @param[in]  Len        The length of register value to be written.
   @param[out] RegValue   The written value.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t FLASH_WriteReg(uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue)
{
    qapi_Status_t Status;
    QSPI_Cmd_t    QspiWriteReg;

    if (Len > 0 && RegValue == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    (void)QSPI_SetCmd(&QspiWriteReg, RegOpcode, 0, 0, 
                      QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, true);

    Status = FLASH_WriteEnable();
    if (Status != QAPI_OK)
    {
        return Status;
    }

    if (QSPI_Cmd(&QspiWriteReg, 0, RegValue, Len, QSPI_TRANS_MODE_BLOCKING))
    {
        return QAPI_OK;
    }
    else
    {
        return QAPI_ERROR;
    }
}

/**
   @brief Flash power up.

   Some flash support "Deep power down" mode, this function release flash from
   power down if it has entered into such mode.
*/
static void FLASH_PowerUp()
{
    QSPI_Cmd_t QspiPowerUp;

    if (FLASH_Context.Config->PowerUpOpcode)
    {
        (void)QSPI_SetCmd(&QspiPowerUp, FLASH_Context.Config->PowerUpOpcode, 0, 0, 
                          QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, false);
        
        QSPI_Cmd(&QspiPowerUp, 0, NULL, 0, QSPI_TRANS_MODE_BLOCKING);
    }
}

/**
   @brief Set flash high performance mode.

   @return Returns QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_SetHighPerformanceMode()
{
    qapi_Status_t Status;
    uint8_t       Temp[3];

    memset(&Temp[0], 0 , sizeof(Temp));
    FLASH_ReadReg(READ_STATUS_CMD, 1, &Temp[0]);
    FLASH_ReadReg(READ_CFG_REG_CMD, 2, &Temp[1]);

    Temp[2] |= FLASH_Context.Config->HighPerformanceModeBmask;

    Status = FLASH_WriteReg(WRITE_STATUS_CMD, 3, &Temp[0]);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                     OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);

    return Status;
}

/**
   @brief Quad enable mode 1, 4, 5.

   Mode 1: QE is bit 1 of status register 2. It is set via Write Status with
   two data bytes where bit 1 of the second byte is one. It is cleared via
   Write status with two data bytes where bit 1 of the second byte is zero.
   Writing only one byte to the status register has the side-effect of clearing
   status register 2, including the QE bit. The 100b code is used if writing
   one byte to the status register does not modify status register 2.
   Mode 4: QE is bit 1 of status register 2. It is set via Write Status with
   two data byte where bit 1 of the second byte is one. It is cleared via
   Write Status with two data bytes where bit 1 of the second byte is zeor.
   In constrast to the ENABLE_QUAD_MODE_1, writing one byte to the status
   register does not modify status register 2.
   Mode 5: QE is bit 1 of the status register 2. Status register 1 is read
   using instruction 05h. Status register 2 is read using instruction 35h.
   QE is set via Write Status instruction 01h with two data bytes where bit 1
   of the second byte is one. It is cleared via Write Status with two data
   bytes where bit 1 of the second byte is zero.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_EnableQuadMode145()
{
    qapi_Status_t Status = QAPI_OK;
    uint8_t       StatusReg1 = 0;
    uint8_t       StatusReg2 = 0;
    uint8_t       Temp[2];

    Status = FLASH_ReadReg(READ_STATUS_CMD, 1, &StatusReg1);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = FLASH_ReadReg(READ_CFG1_CMD, 1, &StatusReg2);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    if (StatusReg2 & BIT_1)
    {
        return Status;
    }

    StatusReg2 |= BIT_1;
    Temp[0] = StatusReg1;
    Temp[1] = StatusReg2;

    Status = FLASH_WriteReg(WRITE_STATUS_CMD, 2, &Temp[0]);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                     OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);

    return Status;
}

/**
   @brief Quad enable mode 2.

   QE is bit 6 of status register 1. It is set via Write Status with one data
   byte where bit 6 is one. It is cleared via Write Status with one data byte
   where bit 6 is zero.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_EnableQuadMode2()
{
    qapi_Status_t Status = QAPI_OK;
    uint8_t       StatusReg = 0;

    Status = FLASH_ReadReg(READ_STATUS_CMD, 1, &StatusReg);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    /* In mode 2, Bit 6 of status register is used to enable Quad mode */
    if (StatusReg & BIT_6)
    {
        return Status;
    }

    StatusReg |= BIT_6;
    Status = FLASH_WriteReg(WRITE_STATUS_CMD, 1, &StatusReg);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                     OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);

    return Status;  
}

/**
   @brief Quad enable mode 3.

   QE is bit 7 of status register 2. It is set via Write status register 2
   instruction 3Eh with one data byte where bit 7 is one. It is cleared via
   Write status register 2 instruction 3Eh with one data byte where bit 7 is
   zero. The status register 2 is read using instruction 3Fh.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_EnableQuadMode3()
{
    qapi_Status_t Status = QAPI_OK;
    uint8_t       Status2Reg = 0;

    /* Read 1 byte Status 2 register with instruction 3Fh */
    Status = FLASH_ReadReg(READ_STATUS_2_CMD, 1, &Status2Reg);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    /* In mode 3, Bit 7 of status 2 register is used to enable Quad mode. */
    if (Status2Reg & BIT_7)
    {
        return Status;
    }

    Status2Reg |= BIT_7;
    Status = FLASH_WriteReg(WRITE_STATUS_2_CMD, 1, &Status2Reg);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                     OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);

    return Status; 
}

/**
   @brief Enable flash quad mode.

   @param[in] QuadMode  The quad enable mode for flash, as defined in the
                        JEDEC Standard No. 216A Document, Quad Enable
                        Requirements in 15th word.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_EnableQuadMode(uint8_t QuadMode)
{
    qapi_Status_t Status = QAPI_OK;

    switch (QuadMode)
    {
        case ENABLE_QUAD_MODE_0:
            /* For mode 0, Device does not have a QE bit. Device detects 
               1-1-4 and 1-4-4 reads based on instruction. */
            break;

        case ENABLE_QUAD_MODE_1:
        case ENABLE_QUAD_MODE_4:
        case ENABLE_QUAD_MODE_5:
            Status = FLASH_EnableQuadMode145();
            break;

        case ENABLE_QUAD_MODE_2:
            Status = FLASH_EnableQuadMode2();
            break;

        case ENABLE_QUAD_MODE_3:
            Status = FLASH_EnableQuadMode3();
            break;

        default:
              Status = QAPI_ERROR;
              break;
    }

    return Status;
}

/**
   @brief Clear Specific bits of the flash registers.

   @param[in] RegReadOpcode   Register read operation code.
   @param[in] RegWriteOpcode  Register write operation code.
   @param[in] BitsMask        The bits mask of the register that need to be cleared.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_ClearSpiBits(uint8_t RegReadOpcode, uint8_t RegWriteOpcode, uint8_t BitsMask)
{
    uint8_t       ReadRet = 0;
    uint8_t       ReadBack = 0;
    qapi_Status_t Status = QAPI_OK;

    if(!BitsMask)
    {
        return Status;  /* Not set bits_mask, skip */
    }

    /* Get value and check */
    Status = FLASH_ReadReg(RegReadOpcode, 1, &ReadRet);
    if((!(ReadRet & BitsMask)) || Status != QAPI_OK)
    {
        return Status;  /* Bits are cleared already, skip */
    }

    /* Clear bits_mask of value */
    ReadRet &= ~BitsMask;
    Status = FLASH_WriteReg(RegWriteOpcode, 1, &ReadRet);
    if(Status != QAPI_OK)
    {
        return Status;
    }

    /* Delay till complete */
    Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                     OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);
    if(Status != QAPI_OK)
    {
      return Status;
    }

    /* Verify the result */
    Status = FLASH_ReadReg(RegReadOpcode, 1, &ReadBack);
    if ((ReadBack & BitsMask) || (Status != QAPI_OK))
    {
        return QAPI_ERROR;  /* Bits are not cleared yet, return fail */
    }

    return Status;
}

/**
   @brief Clear a list of Specific bits of the flash registers.

   @param[in] RegReadOpcode   Register read operation code list.
   @param[in] RegWriteOpcode  Fegister write operation code list.
   @param[in] BitsMask        The list of register bits that need to be cleared.
   @param[in] Cnt             The count of the list.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_ClearSpiBitsList(const uint8_t* RegReadOpcodes, const uint8_t* RegWriteOpcode,
                                            const uint8_t* BitsMasks, uint8_t Cnt)
{
    uint8_t       i = 0;
    qapi_Status_t Status = QAPI_OK;

    for(i = 0; i < Cnt; i++)
    {
        Status = FLASH_ClearSpiBits(RegReadOpcodes[i], RegWriteOpcode[i], BitsMasks[i]);
        if(Status != QAPI_OK)
        {
            return Status;
        }
    }

    return Status;
}

/**
   @brief Clear flash write protection, so that flash can be written and erased.

   For different flash types, the registers and protect bits may be different.
   They should be handled differently.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_ClearWriteProtection()
{
    uint8_t       FlashVid = FLASH_PID2VID(FLASH_Context.Config->DeviceId);
    uint32_t      SrMask = FLASH_Context.Config->WriteProtectBmask;
    qapi_Status_t Status = QAPI_OK;

    if(MANUFACTURER_ID_WINBOND == FlashVid)
    {
        /* Status Register Format is as described below for Winbond Flash part.
           Winbond Status-1 Register Format:
           =======================
           bit7     bit6    bit5      bit4    bit3    bit2  bit1    bit0
           SRP      SEC      TB       BP2     BP1     BP0   WEL     BUSY
           (Status  (Sector  (TOP/    (Block protect Bits)  (Write  (Erase/write
           register protect) bottom                         enable  in progress)
           protect)          protect)                       latch)  

           Winbond Status-2 Register Format:
           =======================
           bit15    bit14   bit13     bit12   bit11   bit10 bit9    bit8
           SUS      CMP     LB3       LB2     LB1     (R)   QE      SRL
                    (Coplement                                      (Status register)
                    protect)                                        lock)
     
           Expect WriteProtectBmask has {0xFC, 0x41, 0x04} for W25Q32JVZPIQ */
        uint8_t WbWriteProtectionBits[] = {(uint8_t)(SrMask), (uint8_t)(SrMask>>8), (uint8_t)(SrMask>>16)};
        uint8_t WbReadCmdList[] = {READ_STATUS_CMD, WINBOND_READ_STATUS_2_CMD, WINBOND_READ_STATUS_3_CMD};
        uint8_t WbWriteCmdList[] = {WRITE_STATUS_CMD, WINBOND_WRITE_STATUS_2_CMD, WINBOND_WRITE_STATUS_3_CMD};
        Status = FLASH_ClearSpiBitsList((const uint8_t*)WbReadCmdList, (const uint8_t*)WbWriteCmdList,
                                        (const uint8_t*)WbWriteProtectionBits, sizeof(WbWriteProtectionBits));
    }
    else if(MANUFACTURER_ID_MACRONIX == FlashVid || MANUFACTURER_ID_ISSI == FlashVid)
    {
        /* WORKAROUND: On some Macronix parts, the block write protection,
           non-volatile bits of status register i.e. BP3-BP0 (bit5-bit2) are
           spuriously set thereby causing erase/write operation on Flash to fail.
          
           This is a temporary WORKAROUND to recover from this situation until
           the actual reason of how these bits are set is uncovered.
           TODO: Need to revisit once the actual problem is root caused.

           Status Register Format is as described below for Macronix Flash part.
           Macronix Status Register Format:
           =======================
           bit7     bit6    bit5    bit4    bit3    bit2    bit1    bit0
           SRWD     QE      BP3     BP2     BP1     BP0     WEL     WIP
           (Status  (Quad   (---"---Level of                (Write  (Write
           register Enable)         Protected Block--"---)  enable  in
           write                                            latch)  progress)
           protect)
          
           1=status 1=Quad                                  1=write 1=write
           register Enable                                  enable  operation
           write    0=not                                   0=not   0=not in
           disable  Quad                                    write   write
                    Enable                                  enable  operation
          
           (--------"-------Non-volatile bits----"-------)  (-"-Volatile bits-"-)
          
           reserved_3 for Macronix parts is defaulted to 0xBC in OEM modifiable
           flash_config stored in AON region and considered as a mask to detect
           whether these bits are set. If set then auto-clear these bits.

           Expect reserved_3 has {0xBC, 0x00, 0x00} for MX25 */
        Status = FLASH_ClearSpiBits(READ_STATUS_CMD, WRITE_STATUS_CMD, (uint8_t)(SrMask));
    }
    return Status;
}

/**
   @brief Set flash operation parameters.

   @param[in] OperationCB  Flash operation callback.
   @param[in] UserParam    User specified parameter for flash operation callback.
   @param[in] QspiCmd      QSPI command for the operation.
   @param[in] Address      Flash start address for current operation.
   @param[in] ByteCnt      The total number of data for the operation.
   @param[in] TriedCnt     Trie number of bytes in current operation.
   @param[in] Buffer       The data buffer for current operation.
*/
static void FLASH_SetOperationParam(qapi_FLASH_Operation_CB_t OperationCB, void *UserParam, QSPI_Cmd_t *QspiCmd,
                                    uint32_t Address, uint32_t ByteCnt, uint32_t TriedCnt, uint8_t *Buffer)
{
    memset(FLASH_Context.OperationParam, 0, sizeof(FLASH_OperationParam_t));
    FLASH_Context.OperationParam->OperationCB = OperationCB;
    FLASH_Context.OperationParam->UserParam = UserParam;
    if (QspiCmd != NULL)
    {
        memcpy(&(FLASH_Context.OperationParam->QspiCmd), QspiCmd, sizeof(QSPI_Cmd_t));
    }
    FLASH_Context.OperationParam->Address = Address;
    FLASH_Context.OperationParam->ByteCnt = ByteCnt;
    FLASH_Context.OperationParam->TriedCnt = TriedCnt;
    FLASH_Context.OperationParam->Buffer = Buffer;
}

/**
   @brief Check if flash operation is complete.
 
   @param[in] Operation    Flash operation, WRITE_OPERATION, or
                           ERASE_OPERATION, or OTHER_OPERATION.
   @param[in] Bmask        The bits of the status register to be checked.
   @param[in] StatusValue  The expected value for the checked status bits.

   @return QAPI_OK on success, QAPI_ERR_BUSY on flash busy operation, or
           other negative value on failure.
*/
static qapi_Status_t FLASH_CheckOperationStatus(uint8_t Operation, uint8_t Bmask, uint8_t StatusValue)
{
    qapi_Status_t Status = QAPI_ERR_BUSY;
    uint8_t       Result = 0;

    Status = FLASH_ReadReg(READ_STATUS_CMD, 1, &Result);
    if (Status == QAPI_OK)
    {
        if ((Result & Bmask) == StatusValue)
        {
            Status = FLASH_CheckError(Operation);
        }
        else
        {
            Status = QAPI_ERR_BUSY;
        }
    }

    return Status;
}

/**
   @brief Flash timer callback function.

   @param[in] Data  User specified parameter for the timer callback function.
*/
static void FLASH_TimerCallBack(void *UserParam)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      EventMask = FLASH_TSK_EVENT_OPERATE_ERROR;
    uint64_t      Timeout = 0;

    if (FLASH_STATE_WRITE == FLASH_Context.State)
    {
        Status = FLASH_CheckOperationStatus(WRITE_OPERATION, PROG_ERASE_WRITE_BUSY_BMSK, 0);
        Timeout = WRITE_TIMEOUT;
    }
    else if (FLASH_STATE_WRITE_REG == FLASH_Context.State)
    {
        Status = FLASH_CheckOperationStatus(OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);
        Timeout = READ_STATUS_TIMEOUT;
    }

    if ((Status != QAPI_ERR_BUSY) || 
        (DIFF_TIME(qapi_TMR_Get_Current_Time(), FLASH_Context.PollingStart) >= Timeout))
    {
        qapi_TMR_Comp_Deinit(FLASH_Context.TimerComparator);
        FLASH_Context.TimerComparator = NO_TIMER_COMPARATOR;

        if (Status == QAPI_OK)
        {
            EventMask = FLASH_TSK_EVENT_OPERATE_DONE;
        }
        qapi_TSK_Signal_Task(FLASH_Context.OperationTask, EventMask);
    }
}

/**
   @brief Start flash time to polling busy status.

   @param[in] State      Current flash state.
   @param[in] EventMask  Specify the pointer to the current event mask.

   @return Current task wait time to run again.
*/
static uint32_t FLASH_StartPollingTimer(uint8_t State, uint32_t *EventMask)
{
    uint32_t                 TskWaitTime = QAPI_TSK_INFINITE_WAIT;
    uint32_t                 NewEventMask = 0;
    qapi_Status_t            Status = QAPI_OK;
    qapi_TMR_Comp_Instance_t Comp;
    uint64_t                 TimeDuration = 0;
    uint64_t                 Timeout = 0;

    if (FLASH_STATE_WRITE == State)
    {
        Status = FLASH_CheckOperationStatus(WRITE_OPERATION, PROG_ERASE_WRITE_BUSY_BMSK, 0);
        TimeDuration = WRITE_STATUS_POLLING_USEC;
        Timeout = WRITE_TIMEOUT;
    }
    else if (FLASH_STATE_WRITE_REG == State)
    {
        Status = FLASH_CheckOperationStatus(OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);
        TimeDuration = READ_STATUS_POLLING_USEC;
        Timeout = READ_STATUS_TIMEOUT;
    }
        
    if (Status == QAPI_OK)
    {
        NewEventMask |= FLASH_TSK_EVENT_OPERATE_DONE;
    }
    else if (Status == QAPI_ERROR)
    {
        NewEventMask |= FLASH_TSK_EVENT_OPERATE_ERROR;
    }
    else if (Status == QAPI_ERR_BUSY)
    {
        /* Record start polling time when tranferring done. */
        if ((*EventMask) & FLASH_TSK_EVENT_TRANSFER_DONE)
        {
            FLASH_Context.PollingStart = qapi_TMR_Get_Current_Time();
        }

        if (DIFF_TIME(qapi_TMR_Get_Current_Time(), FLASH_Context.PollingStart) < Timeout)
        {
            /* Start timer comparator to polling the write busy status. */
            Status = qapi_TMR_Comp_Init(&Comp, FLASH_TimerCallBack, NULL, false);
            if (Status == QAPI_OK)
            {
                FLASH_Context.TimerComparator = Comp;
                Status = qapi_TMR_Comp_Start(Comp, TimeDuration, true);
            }

            if (Status != QAPI_OK)
            {
                if (FLASH_Context.TimerComparator != NO_TIMER_COMPARATOR)
                {
                    qapi_TMR_Comp_Deinit(FLASH_Context.TimerComparator);
                    FLASH_Context.TimerComparator = NO_TIMER_COMPARATOR;
                }
                
                /* If starting timer comparator failed, return task quickly to try again. */
                TskWaitTime = FLASH_TSK_SHORT_WAIT;
            }
        }
        else
        {
            /* Check operation and try starting timer compartor timeout. */
            NewEventMask |= FLASH_TSK_EVENT_OPERATE_ERROR;
        }
    }

    *EventMask |= NewEventMask;

    return TskWaitTime;
}

/**
   @brief Call user registered callback to indicate flash non-blocking
          operation complete.

   @param[in] Status          Flash operation status.
   @param[in] OperationParam  Flash operation parameters.
*/
static void FLASH_CallOperationCallback(qapi_Status_t Status, FLASH_OperationParam_t *OperationParam)
{
    if (FLASH_Context.State == FLASH_STATE_WRITE || FLASH_Context.State == FLASH_STATE_ERASE)
    {
        (void)QSPI_MAP_SetProgramEraseState(false);
    }
    
    FLASH_Context.State = 0;
    if (OperationParam->OperationCB)
    {
        OperationParam->OperationCB(Status, OperationParam->UserParam);
    }
}

/**
   @brief The task for flash non-blocking write or writereg.

   @param[in] TaskHandle  Handle of the operation task.
   @param[in] EventMask   Mask of all events that triggered since last
                          call to the task.
   @param[in] UserParam   User specified parameter for the task.

   @return The time in milliseconds before this function needs to be called again.
*/
static uint32_t FLASH_WriteDataRegTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    uint32_t                TskWaitTime = QAPI_TSK_INFINITE_WAIT;
    qapi_Status_t           Status = QAPI_OK;
    FLASH_OperationParam_t *OperationParam = (FLASH_OperationParam_t *)UserParam;
    uint32_t                Limit = PAGE_SIZE_IN_BYTES;

    /* Get transfer done from DMA interrupt, check if write inside flash is complete or not. */
    if (EventMask & (FLASH_TSK_EVENT_TRANSFER_DONE | QAPI_TSK_EVENT_TIMEOUT))
    {
        TskWaitTime = FLASH_StartPollingTimer(FLASH_Context.State, &EventMask);
    }

    if (EventMask & FLASH_TSK_EVENT_OPERATE_DONE)
    {
        OperationParam->ByteCnt -= OperationParam->TriedCnt;

        if (OperationParam->ByteCnt > 0)
        {
            OperationParam->Address += OperationParam->TriedCnt;
            OperationParam->Buffer += OperationParam->TriedCnt;
            
            if (OperationParam->Address % PAGE_SIZE_IN_BYTES)
            {
                OperationParam->TriedCnt = PAGE_SIZE_IN_BYTES - (OperationParam->Address % PAGE_SIZE_IN_BYTES);
                if (OperationParam->TriedCnt > OperationParam->ByteCnt)
                {
                    OperationParam->TriedCnt = OperationParam->ByteCnt;
                }
            }
            else
            {
                OperationParam->TriedCnt = (OperationParam->ByteCnt > Limit) ? Limit : OperationParam->ByteCnt;
            }

            Status = FLASH_WriteEnable();
            if (Status != QAPI_OK)
            {
                FLASH_CallOperationCallback(Status, OperationParam);
                return TskWaitTime;
            }

            FLASH_Context.State |= FLASH_STATE_NON_BLOCKING;
            QSPI_Cmd(&(OperationParam->QspiCmd), OperationParam->Address, OperationParam->Buffer,
                     OperationParam->TriedCnt, QSPI_DMA_INT_MODE_E);
        }
        else
        {
            FLASH_CallOperationCallback(QAPI_OK, OperationParam);
        }
        
    }

    if (EventMask & FLASH_TSK_EVENT_OPERATE_ERROR)
    {
        FLASH_CallOperationCallback(QAPI_ERROR, OperationParam);
    }

    return TskWaitTime;
}

/**
   @brief The task for flash non-blocking erase.

   @param[in] TaskHandle  Handle of the operation task.
   @param[in] EventMask   Mask of all events that triggered since last
                          call to the task.
   @param[in] UserParam   User specified parameter for the task.

   @return The time in milliseconds before this function needs to be called again.
*/
static uint32_t FLASH_EraseTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    uint32_t                TskWaitTime = QAPI_TSK_INFINITE_WAIT;
    FLASH_OperationParam_t *OperationParam = (FLASH_OperationParam_t *)UserParam;
    qapi_Status_t           Status;
    uint32_t                ErasePolling;
    uint32_t                EraseTimeout;

    if (OperationParam->TriedCnt == FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES)
    {
        EraseTimeout = CHIP_ERASE_TIMEOUT;
        ErasePolling = CHIP_ERASE_STATUS_POLLING_MSEC;
    }
    else
    {
        EraseTimeout = ERASE_TIMEOUT;
        ErasePolling = ERASE_STATUS_POLLING_MSEC;
    }

    /* First erase command is transferred, check erase status after 5ms. */
    if (EventMask & FLASH_TSK_EVENT_TRANSFER_DONE)
    {
        FLASH_Context.PollingStart = qapi_TMR_Get_Current_Time();
        TskWaitTime = ErasePolling;
    }

    /* 5ms timeout, check if erase inside flash is done. */
    if (EventMask & QAPI_TSK_EVENT_TIMEOUT)
    {
        Status = FLASH_CheckOperationStatus(ERASE_OPERATION, PROG_ERASE_WRITE_BUSY_BMSK, 0);
        if (Status == QAPI_OK)
        {
            OperationParam->ByteCnt -= OperationParam->TriedCnt;
            if (OperationParam->ByteCnt > 0)
            {
                OperationParam->Address += OperationParam->TriedCnt;
                
                Status = FLASH_WriteEnable();
                if (Status != QAPI_OK)
                {
                    FLASH_CallOperationCallback(Status, OperationParam);
                    return TskWaitTime;
                }

                QSPI_Cmd(&(OperationParam->QspiCmd), OperationParam->Address, 
                         NULL, 0, QSPI_TRANS_MODE_BLOCKING);
                FLASH_Context.PollingStart = qapi_TMR_Get_Current_Time();
                TskWaitTime = ErasePolling;
            }
            else
            {
                FLASH_CallOperationCallback(QAPI_OK, OperationParam);
            }
        }
        else
        {
            if (Status == QAPI_ERR_BUSY &&
                (DIFF_TIME(qapi_TMR_Get_Current_Time(), FLASH_Context.PollingStart) < EraseTimeout))
            {
                TskWaitTime = ErasePolling;
            }
            else
            {
                FLASH_CallOperationCallback(QAPI_ERROR, OperationParam);
            }
        }
    }

    return TskWaitTime;
}

/**
   @brief The task for flash non-blocking read/write/erase.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of all events that triggered since last
                          call to this function.
   @param[in] UserParam   User specified parameter for the task function.

   @return The time in milliseconds before this function needs to be called again.
*/
static uint32_t FLASH_OperationTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    uint32_t TskWaitTime = QAPI_TSK_INFINITE_WAIT;

    if (FLASH_Context.State == FLASH_STATE_WRITE || FLASH_Context.State == FLASH_STATE_WRITE_REG)
    {
        TskWaitTime = FLASH_WriteDataRegTask(TaskHandle, EventMask, UserParam);
    }
    else if (FLASH_Context.State == FLASH_STATE_ERASE)
    {
        TskWaitTime = FLASH_EraseTask(TaskHandle, EventMask, UserParam);
    }
    else if (FLASH_Context.State == FLASH_STATE_READ)
    {
        /* Get transfer done from DMA interrupt, read is done. */
        if (EventMask & FLASH_TSK_EVENT_TRANSFER_DONE)
        {
            FLASH_CallOperationCallback(QAPI_OK, (FLASH_OperationParam_t *)UserParam);
        }
    }
    
    return TskWaitTime;
}

/**
   @brief Flash transfer callback function in QSPI ISR.

   This function is called in QSPI ISR. It should do minimal processing.

   @param[in] Status     The interrupt status.
   @param[in] UserParam  User specified parameter provided when the
                         callback is registered.
*/
static void FLASH_TransferCallback(uint32_t Status, void *UserParam)
{
    if (FlashInitDone && (FLASH_Context.State & FLASH_STATE_NON_BLOCKING))
    {
        FLASH_Context.State &= ~FLASH_STATE_NON_BLOCKING;
        qapi_TSK_Signal_Task(FLASH_Context.OperationTask, FLASH_TSK_EVENT_TRANSFER_DONE);
    }
}

/**
   @brief Initialize flash context info.

   @param[in] Config  Configuration data for the flash device.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_InfoInit(const qapi_FLASH_Config_t *Config)
{
    qapi_Status_t Status = QAPI_OK;
    
    memset(&FLASH_Context, 0, sizeof(FLASH_Context_t));
    
    FLASH_Context.Config = qapi_Malloc(sizeof(qapi_FLASH_Config_t));
    if (FLASH_Context.Config == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    memcpy(FLASH_Context.Config, Config, sizeof(qapi_FLASH_Config_t));

    FLASH_Context.OperationParam = qapi_Malloc(sizeof(FLASH_OperationParam_t));
    if (FLASH_Context.OperationParam == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }
    memset(FLASH_Context.OperationParam, 0, sizeof(FLASH_OperationParam_t));
    
    /* Create operation task. */
    FLASH_Context.OperationTask = qapi_TSK_Create_Task(FLASH_OperationTask, (void *)FLASH_Context.OperationParam);

    FLASH_Context.TimerComparator= NO_TIMER_COMPARATOR;

    return Status;
}

/**
   @brief Initialize the flash controller HW.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t FLASH_ControllerInit()
{
    QSPI_MasterConfig_t QspiCfg;

    memset(&QspiCfg, 0, sizeof(QSPI_MasterConfig_t));
    /* Only 1 chip select. */
    QspiCfg.ChipSelect = 0;
    /* Set SPI mode 0. */
    QspiCfg.ClkPolarity = false;
    QspiCfg.ClkPhase = false;
    
    /* Set clock frequency. */
    if (FLASH_Context.Config->ReadCmdMode == QAPI_FLASH_RW_MODE_DDR_QUAD || FLASH_Context.Config->ReadAddrMode == QAPI_FLASH_RW_MODE_DDR_QUAD || 
        FLASH_Context.Config->ReadDataMode == QAPI_FLASH_RW_MODE_DDR_QUAD || FLASH_Context.Config->WriteCmdMode == QAPI_FLASH_RW_MODE_DDR_QUAD || 
        FLASH_Context.Config->WriteAddrMode == QAPI_FLASH_RW_MODE_DDR_QUAD || FLASH_Context.Config->WriteDataMode == QAPI_FLASH_RW_MODE_DDR_QUAD)
    {
        QspiCfg.ClkFreq = QSPI_SBL_CLOCK_FREQUENCY;
    }
    else
    {
        QspiCfg.ClkFreq = QSPI_PBL_CLOCK_FREQUENCY;
    }
    
    QspiCfg.IsrCB = FLASH_TransferCallback;
    QspiCfg.UserParam = NULL;

    if (QSPI_Init(&QspiCfg))
    {
        return QAPI_OK;
    }

    return QAPI_ERROR;
}

/**
   @brief Initialize the flash module.

   This function must be called before any other flash functions.

   @param[in] Config  Configuration data for the flash device.

   @return 
   QAPI_OK -- On success, or an error code on failure.
*/
qapi_Status_t qapi_FLASH_Init(const qapi_FLASH_Config_t *Config)
{
    qapi_Status_t Status   = QAPI_OK;
    uint32_t      DeviceId = 0;
    
    if (FlashInitDone)
    {
        return QAPI_OK;
    }

    if (Config == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Status = FLASH_InfoInit(Config);
    if (Status != QAPI_OK)
    {
        goto FLASH_INIT_END;
    }

    /* Initialize QSPI driver. */
    Status = FLASH_ControllerInit();
    if (Status != QAPI_OK)
    {
        goto FLASH_INIT_END;
    }

    /* power up flash */
    FLASH_PowerUp();

    qapi_TMR_Delay_Us(100 * FLASH_Context.Config->PowerOnDelayIn100us);

    /* Check device id. */
    Status = FLASH_ReadReg(READ_IDENTIFICATION_CMD, 3, (uint8_t *)&DeviceId);
    if (DeviceId != FLASH_Context.Config->DeviceId)
    {
        if (Status == QAPI_OK)
        {
            Status = QAPI_ERROR;
        }
        goto FLASH_INIT_END;
    }

    /* Clear write protection */
    Status = FLASH_ClearWriteProtection();
    if (Status != QAPI_OK)
    {
        goto FLASH_INIT_END;
    }
    
    /* high performance mode */
    if (FLASH_Context.Config->HighPerformanceModeBmask)
    {
        Status = FLASH_SetHighPerformanceMode();
        if (Status != QAPI_OK)
        {
            goto FLASH_INIT_END;
        }
    }

    /* Check rw mode. */
    if (!VALID_RW_MODE(FLASH_Context.Config->ReadCmdMode) || !VALID_RW_MODE(FLASH_Context.Config->ReadAddrMode) ||
        !VALID_RW_MODE(FLASH_Context.Config->ReadDataMode) || !VALID_RW_MODE(FLASH_Context.Config->WriteCmdMode) ||
        !VALID_RW_MODE(FLASH_Context.Config->WriteAddrMode) || !VALID_RW_MODE(FLASH_Context.Config->WriteDataMode))
    {
        Status = QAPI_ERR_INVALID_PARAM;
        goto FLASH_INIT_END;
    }
  
    /* Set quard mode */
    if (IS_QUAD_MODE(FLASH_Context.Config->ReadCmdMode) || IS_QUAD_MODE(FLASH_Context.Config->ReadAddrMode) ||
        IS_QUAD_MODE(FLASH_Context.Config->ReadDataMode) || IS_QUAD_MODE(FLASH_Context.Config->WriteCmdMode) ||
        IS_QUAD_MODE(FLASH_Context.Config->WriteAddrMode) || IS_QUAD_MODE(FLASH_Context.Config->WriteDataMode))
    {
        Status = FLASH_EnableQuadMode(FLASH_Context.Config->QuadEnableMode);
        if (Status != QAPI_OK)
        {
            goto FLASH_INIT_END;
        }
    }
    
    /* Set address mode */
    if ((FLASH_Context.Config->AddrBytes == 4) &&
        (FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES > FLASH_16MB_IN_BYTES))
    {
        Status = FLASH_WriteReg(ENTER_4B_ADDR_CMD, 0, NULL);
        if (Status != QAPI_OK)
        {
            goto FLASH_INIT_END;
        }
    }

    FlashInitDone = true;

 FLASH_INIT_END:
    /* If there is an error, free the memory. */
    if (Status != QAPI_OK)
    {
        if (FLASH_Context.Config != NULL)
        {
            qapi_Free(FLASH_Context.Config);
        }
        if (FLASH_Context.OperationTask != NULL)
        {
            qapi_TSK_Delete_Task(FLASH_Context.OperationTask);
        }
        if (FLASH_Context.OperationParam != NULL)
        {
           qapi_Free(FLASH_Context.OperationParam); 
        }
    }
    
    return Status; 
}

/**
   @brief Read data from the flash.

   This function returns when the read is done, if it is blocking. If it is non-blocking,
   it returns with #QAPI_FLASH_STATUS_PENDING, indicating that the read is
   performed in the background.

   A callback function indicates when the non-blocking operation
   is complete. Because read is ongoing after this function returns,
   the input buffer for storing read data should not be freed. All
   other operations that must run after flash read and should not be performed
   before the callback function is called.

   @param[in]  Address    The flash address to start to read from.
   @param[in]  ByteCnt    Number of bytes to read.
   @param[out] Buffer     Data buffer for a flash read operation; it should
                          be in heap, or a static buffer for a non-blocking read.
   @param[in]  ReadCB     Flash read callback function for a non-blocking
                          read. After a read is done, the ReadCB is
                          called to inform about the completion; it should
                          be NULL for a blocking read.
   @param[in]  UserParam  The user specified parameter for the callback function.

   @return 
   QAPI_OK -- If a blocking read completed successfully, or a negative value if there was an error.
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking read is ongoing.
*/
qapi_Status_t qapi_FLASH_Read(uint32_t Address, uint32_t ByteCnt, uint8_t *Buffer, qapi_FLASH_Operation_CB_t ReadCB, void *UserParam)
{
    qapi_Status_t Status = QAPI_OK;
    QSPI_Cmd_t    QspiReadCmd;

    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (FLASH_Context.State != 0)
    {
        return QAPI_ERR_BUSY;
    }

    FLASH_Context.State = FLASH_STATE_READ;

    if (Buffer == NULL || ByteCnt == 0 || ((Address + ByteCnt) < Address) ||
        ((Address + ByteCnt) > FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES))
    {
        Status = QAPI_ERR_INVALID_PARAM;
        goto FLASH_READ_END;
    }

    (void)QSPI_SetCmd(&QspiReadCmd, FLASH_Context.Config->ReadOpcode, FLASH_Context.Config->AddrBytes, FLASH_Context.Config->ReadWaitState,
                      (QSPI_Mode_t)FLASH_Context.Config->ReadCmdMode, (QSPI_Mode_t)FLASH_Context.Config->ReadAddrMode, 
                      (QSPI_Mode_t)FLASH_Context.Config->ReadDataMode, false);

    if (ReadCB == NULL)
    {
        if (!QSPI_Cmd(&QspiReadCmd, Address, Buffer, ByteCnt, QSPI_TRANS_MODE_BLOCKING))
        {
            Status = QAPI_ERROR;
        }
    }
    else
    {
        FLASH_SetOperationParam(ReadCB, UserParam, &QspiReadCmd,
                                Address, ByteCnt, ByteCnt, Buffer);
        FLASH_Context.State |= FLASH_STATE_NON_BLOCKING;

        if (!QSPI_Cmd(&QspiReadCmd, Address, Buffer, ByteCnt, QSPI_DMA_INT_MODE_E))
        {
            Status = QAPI_ERROR;
        }
        else
        {
            return QAPI_FLASH_STATUS_PENDING;
        }
    }

FLASH_READ_END:
    FLASH_Context.State = 0;
    return Status;
}

/**
   @brief Write data to the flash.

   This function returns when the write is done, if it is blocking. If it is non-blocking,
   it returns with #QAPI_FLASH_STATUS_PENDING, indicating that the write is
   performed in the background.

   A callback function indicates when the non-blocking operation
   is complete. Because write is ongoing after this function returns,
   the input buffer for storing write data should not be freed. All
   other operations that must run after flash write, should not be performed
   before the callback function is called.

   @param[in] Address    The flash address to start to write to.
   @param[in] ByteCnt    Number of bytes to write.
   @param[in] Buffer     Data buffer containing data to be written; it should
                         be in heap, or a static buffer for a non-blocking write.
   @param[in] WriteCB    Flash write callback function for non-blocking
                         write. After write is done, the WriteCB is
                         called to inform about the completion; it should
                         be NULL for a blocking write.
   @param[in] UserParam  The user specified parameter for the callback function.

   @return
   QAPI_OK -- If blocking write completed successfully, or a negative value if there was an error.
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking write is ongoing.
*/
qapi_Status_t qapi_FLASH_Write(uint32_t Address, uint32_t ByteCnt, uint8_t *Buffer, qapi_FLASH_Operation_CB_t WriteCB, void *UserParam)
{
    qapi_Status_t Status = QAPI_OK;
    QSPI_Cmd_t    QspiPageWriteCmd;
    uint32_t      TransferSize = 0;
    uint32_t      Limit = PAGE_SIZE_IN_BYTES;
    
    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (FLASH_Context.State != 0)
    {
        return QAPI_ERR_BUSY;
    }

    FLASH_Context.State = FLASH_STATE_WRITE;

    if (Buffer == NULL || ByteCnt == 0 || ((Address + ByteCnt) < Address) ||
        ((Address + ByteCnt) > FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES))
    {
        Status = QAPI_ERR_INVALID_PARAM;
        goto FLASH_WRITE_END;
    }

    (void)QSPI_SetCmd(&QspiPageWriteCmd, FLASH_Context.Config->WriteOpcode, FLASH_Context.Config->AddrBytes, 0,
                      (QSPI_Mode_t)FLASH_Context.Config->WriteCmdMode, (QSPI_Mode_t)FLASH_Context.Config->WriteAddrMode,
                      (QSPI_Mode_t)FLASH_Context.Config->WriteDataMode, true);

    if (WriteCB != NULL)
    {
        FLASH_SetOperationParam(WriteCB, UserParam, &QspiPageWriteCmd,
                                Address, ByteCnt, 0, Buffer);
    }

    /* Signle the HW write operation is ongoing. Needed for XIP. */
    if (FLASH_Context.Config->SuspendProgramOpcode > 0 && FLASH_Context.Config->ResumeProgramOpcode > 0)
    {
        (void)QSPI_MAP_SetProgramEraseState(true);
        (void)QSPI_MAP_ConfigSuspendResume(FLASH_Context.Config->SuspendProgramDelayInUs,
                                           FLASH_Context.Config->SuspendProgramOpcode,
                                           FLASH_Context.Config->ResumeProgramDelayInUs,
                                           FLASH_Context.Config->ResumeProgramOpcode);
    }

    while (ByteCnt)
    {
        if (Address % PAGE_SIZE_IN_BYTES)
        {
            TransferSize = PAGE_SIZE_IN_BYTES - (Address % PAGE_SIZE_IN_BYTES);
            if (TransferSize > ByteCnt)
            {
                TransferSize = ByteCnt;
            }
        }
        else
        {
            TransferSize = (ByteCnt > Limit) ? (Limit) : (ByteCnt);
        }

        Status = FLASH_WriteEnable();
        if (Status != QAPI_OK)
        {
            goto FLASH_WRITE_END;
        }

        if (WriteCB == NULL)
        {
            QSPI_Cmd(&QspiPageWriteCmd, Address, Buffer, TransferSize, QSPI_TRANS_MODE_BLOCKING);
        }
        else
        {
            FLASH_Context.OperationParam->TriedCnt = TransferSize;
            FLASH_Context.State |= FLASH_STATE_NON_BLOCKING;
            QSPI_Cmd(&QspiPageWriteCmd, Address, Buffer, TransferSize, QSPI_DMA_INT_MODE_E);
            return QAPI_FLASH_STATUS_PENDING;
        }

        Status = FLASH_WaitOperationDone(WRITE_TIMEOUT, WRITE_STATUS_POLLING_USEC,
                                         WRITE_OPERATION, PROG_ERASE_WRITE_BUSY_BMSK, 0);
        if (Status != QAPI_OK)
        {
            goto FLASH_WRITE_END;
        }

        Address += TransferSize;
        Buffer += TransferSize;
        ByteCnt -= TransferSize;
    }

FLASH_WRITE_END:
    (void)QSPI_MAP_SetProgramEraseState(false);
    FLASH_Context.State = 0;
    return Status;
}

/**
   @brief Erase the given flash blocks or bulks, or the whole chip.

   This function returns when the erase is done, if it is blocking. If it is non-blocking, it
   returns with #QAPI_FLASH_STATUS_PENDING, indicating that the erase is
   performed in the background.

   A callback function indicates when the non-blocking operation
   is complete. Because erase is ongoing after this function returns,
   other operations that must run after flash erase, should not be performed
   before the callback function is called.

   @param[in] EraseType  Specify the erase type.
   @param[in] Start      For block erase - the starting block of a
                         number of blocks to erase.
                         For bulk erase - the starting bulk of a number
                         of bulks to erase.
                         For chip erase, it should be 0.
   @param[in] Cnt        For block erase - the number of blocks to erase.
                         For bulk erase - the number of bulks to erase.
                         For chip erase, it should be 1.
   @param[in] EraseCB    Flash erase callback function for non-blocking
                         erase. After erase is done, the EraseCB is
                         called to inform about the completion; it should be
                         NULL for a blocking erase.
   @param[in] UserParam  The user specified parameter for the callback function.

   @return
   QAPI_OK -- If blocking erase completed successfully, or a negative value if there was an error.
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking erase is ongoing.
*/
qapi_Status_t qapi_FLASH_Erase(qapi_FLASH_Erase_Type_t EraseType, uint32_t Start, uint32_t Cnt, qapi_FLASH_Operation_CB_t EraseCB, void *UserParam)
{
    qapi_Status_t Status = QAPI_OK;
    QSPI_Cmd_t    QspiEraseCmd;
    uint32_t      Address;
    uint32_t      Size = 0;
    uint32_t      EraseTimeout = ERASE_TIMEOUT;
    uint32_t      ErasePolling = ERASE_STATUS_POLLING_MSEC;
    uint8_t       Opcode;
    uint8_t       AddrBytes = FLASH_Context.Config->AddrBytes;

    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (FLASH_Context.State != 0)
    {
        return QAPI_ERR_BUSY;
    }

    FLASH_Context.State = FLASH_STATE_ERASE;

    if (EraseType == QAPI_FLASH_BLOCK_ERASE_E)
    {
        if (FLASH_Context.Config->Erase4kbOpcode == 0)
        {
            return QAPI_ERR_INVALID_PARAM;
        }
        Size = BLOCK_SIZE_IN_BYTES;
        Opcode = FLASH_Context.Config->Erase4kbOpcode;
    }
    else if (EraseType == QAPI_FLASH_BULK_ERASE_E)
    {
        if (FLASH_Context.Config->BulkEraseSizeIn4KB == 0 || FLASH_Context.Config->BulkEraseOpcode == 0)
        {
            return QAPI_ERR_INVALID_PARAM;
        }
        Size = FLASH_Context.Config->BulkEraseSizeIn4KB * BLOCK_SIZE_IN_BYTES;
        Opcode = FLASH_Context.Config->BulkEraseOpcode;
    }
    else if (EraseType == QAPI_FLASH_CHIP_ERASE_E)
    {
        if (FLASH_Context.Config->ChipEraseOpcode == 0)
        {
            return QAPI_ERR_INVALID_PARAM;
        }
        Size = FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES;
        Opcode = FLASH_Context.Config->ChipEraseOpcode;
        AddrBytes = 0;
        EraseTimeout = CHIP_ERASE_TIMEOUT;
        ErasePolling = CHIP_ERASE_STATUS_POLLING_MSEC;
    }
    else
    {
        Status = QAPI_ERR_INVALID_PARAM;
        goto FLASH_ERASE_END;
    }

    Address = Start * Size;
    if (Cnt == 0 || ((Start + Cnt) * Size < Address) ||
        ((Start + Cnt) * Size > FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES))
    {
        Status = QAPI_ERR_INVALID_PARAM;
        goto FLASH_ERASE_END;
    }

    (void)QSPI_SetCmd(&QspiEraseCmd, Opcode, AddrBytes, 0, 
                      QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, QSPI_SDR_1BIT_E, false);

    /* Signle the HW write operation is ongoing. Needed for XIP. */
    if (FLASH_Context.Config->SuspendEraseOpcode > 0 && FLASH_Context.Config->ResumeEraseOpcode > 0)
    {
        (void)QSPI_MAP_SetProgramEraseState(true);
        (void)QSPI_MAP_ConfigSuspendResume(FLASH_Context.Config->SuspendEraseDelayInUs,
                                           FLASH_Context.Config->SuspendEraseOpcode,
                                           FLASH_Context.Config->ResumeEraseDelayInUs,
                                           FLASH_Context.Config->ResumeEraseOpcode);
    }

    while (Cnt)
    {
        Status = FLASH_WriteEnable();
        if (Status != QAPI_OK)
        {
            goto FLASH_ERASE_END;
        }

        QSPI_Cmd(&QspiEraseCmd, Address, NULL, 0, QSPI_TRANS_MODE_BLOCKING);

        if (EraseCB != NULL)
        {
            FLASH_SetOperationParam(EraseCB, UserParam, &QspiEraseCmd,
                                    Address, (Cnt * Size), Size, NULL);
            qapi_TSK_Signal_Task(FLASH_Context.OperationTask, FLASH_TSK_EVENT_TRANSFER_DONE);
            return QAPI_FLASH_STATUS_PENDING;
        }

        Status = FLASH_WaitOperationDone(EraseTimeout, ErasePolling * 1000,
                                         ERASE_OPERATION, PROG_ERASE_WRITE_BUSY_BMSK, 0);
        if (Status != QAPI_OK)
        {
            goto FLASH_ERASE_END;
        }

        Address += Size;
        Cnt--;
    }

FLASH_ERASE_END:
    (void)QSPI_MAP_SetProgramEraseState(false);
    FLASH_Context.State = 0;
    return Status;
}

/**
   @brief Read flash registers.

   @param[in]  RegOpcode  Operation code.
   @param[in]  Len        The length of register value to be read.
   @param[out] RegValue   The read out value.

   @return
   QAPI_OK -- On success, or an error code on failure.
*/
qapi_Status_t qapi_FLASH_Read_Reg(uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue)
{
    qapi_Status_t Status;

    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (FLASH_Context.State != 0)
    {
        return QAPI_ERR_BUSY;
    }

    FLASH_Context.State = FLASH_STATE_READ_REG;

    Status = FLASH_ReadReg(RegOpcode, Len, RegValue);
    
    FLASH_Context.State = 0;
    return Status;
}

/**
   @brief Write flash registers.

   This function returns when the writereg is done, if it is blocking. If it is non-blocking, it
   returns with #QAPI_FLASH_STATUS_PENDING, indicating that the writereg is
   performed in the background.

   A callback function indicates when the non-blocking operation
   is complete. Because writereg is ongoing after this function returns,
   other operations that must run after flash writereg, should not be performed
   before the callback function is called.

   @param[in] RegOpcode   Operation code.
   @param[in] Len         The length of register value to be written.
   @param[in] RegValue    The written value.
   @param[in] WriteRegCB  Flash writereg callback function for a non-blocking
                          writereg. After writereg is done, the WriteRegCB
                          is called to inform about the completion; it
                          should be NULL for a blocking operation.
   @param[in] UserParam   The user specified parameter for the callback function.

   @return
   QAPI_OK -- If blocking writereg completed successfully, or a negative value if there was an error.
   QAPI_FLASH_STATUS_PENDING -- Indicating non-blocking writereg is ongoing.
*/
qapi_Status_t qapi_FLASH_Write_Reg(uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue, qapi_FLASH_Operation_CB_t WriteRegCB, void *UserParam)
{
    qapi_Status_t Status;

    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (FLASH_Context.State != 0)
    {
        return QAPI_ERR_BUSY;
    }

    FLASH_Context.State = FLASH_STATE_WRITE_REG;

    Status = FLASH_WriteReg(RegOpcode, Len, RegValue);
    if (Status != QAPI_OK)
    {
        goto FLASH_WRITEREG_END;
    }

    if (WriteRegCB == NULL)
    {
        Status = FLASH_WaitOperationDone(READ_STATUS_TIMEOUT, READ_STATUS_POLLING_USEC,
                                         OTHER_OPERATION, READ_STATUS_BUSY_MASK, 0);
    }
    else
    {
        FLASH_SetOperationParam(WriteRegCB, UserParam, NULL,
                                0, Len, Len, NULL);
        qapi_TSK_Signal_Task(FLASH_Context.OperationTask, FLASH_TSK_EVENT_TRANSFER_DONE);
        return QAPI_FLASH_STATUS_PENDING;
    }

FLASH_WRITEREG_END:
    FLASH_Context.State = 0;
    return Status;
}

/**
   @brief Map part of flash memory to a specific part of system memory.

   This function allows QUP DMA to directly read flash contents from a specific
   system address which is mapped with flash memory.
   
   To use this feature, the flash read mode should be single mode or quad
   mode. Dual-read mode is not supported.
   It allows at most 3 different parts of flash memory to be mapped to 3
   different parts of system memory; while each part can support up to 16&nbsp;Mbytes. 
   The different parts of flash memory cannot be overlapped with each
   other on the block.

   @param[in]  Address    Flash start address to be mapped.
   @param[in]  Size       The size of flash memory to be mapped.
   @param[out] MapHandle  Handle to flash mapped memory.

   @return
   QAPI_OK -- If mapping was successful, or a negative value if there was an error.
*/
qapi_Status_t qapi_FLASH_Memory_Map(uint32_t Address, uint32_t Size, qapi_FLASH_Map_Handle_t *MapHandle)
{
    qapi_Status_t           Status;
    QSPI_MAP_MemMapConfig_t Config;

    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }

    if (Size == 0 || ((Address + Size) < Address) || 
        ((Address + Size) > FLASH_Context.Config->DensityInBlocks * BLOCK_SIZE_IN_BYTES))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Config.CmdMode = FLASH_Context.Config->ReadCmdMode;
    Config.AddrMode = FLASH_Context.Config->ReadAddrMode;
    Config.DataMode = FLASH_Context.Config->ReadDataMode;
    Config.ReadOpcode = FLASH_Context.Config->ReadOpcode;
    Config.AddrBytes = FLASH_Context.Config->AddrBytes;
    Config.DummyCycles = FLASH_Context.Config->ReadWaitState;

    Status = QSPI_MAP_MemoryMap(Address, Size, &Config, MapHandle);
    return Status;
}

/**
   @brief Unmap the part of flash memory from system memory.

   This function disallows QUP DMA to directly read flash contents from system
   address.

   @param[in] MapHandle  Handle to flash mapped memory.

   @return
   QAPI_OK -- If unmapping was successful, or a negative value if there was an error.
*/
qapi_Status_t qapi_FLASH_Memory_Unmap(qapi_FLASH_Map_Handle_t MapHandle)
{
    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }
    
    return QSPI_MAP_MemoryUnmap(MapHandle);
}

/**
   @brief Get the mapped system address of a specific flash address.

   This function must be called before QUP DMA reading from flash. It converts
   the flash address to its mapped system address. QUP DMA can then directly read
   flash contents from the system address.

   @param[in]  Address        Flash physical address.
   @param[out] MappedAddress  The mapped system address.

   @return
   QAPI_OK -- If the address is obtained successfully, or a negative value if there is an error.
*/
qapi_Status_t qapi_FLASH_Get_Mapped_Address(uint32_t Address, uint32_t *MappedAddress)
{
    if (!FlashInitDone)
    {
        return QAPI_ERROR;
    }
    
    return QSPI_MAP_GetMappedAddress(Address, MappedAddress);
}

