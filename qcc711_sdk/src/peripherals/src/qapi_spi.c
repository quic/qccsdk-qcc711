/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "qapi_task.h"
#include "qapi_spi.h"
#include "qup_api.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define SPI_TRANSFER_NUM_MAX    4
#define SPI_TRANSFER_LEN_MAX	((1 << 24) - 1)
#define SPI_ErrorMap(Status)    (Status ? __QAPI_ERROR(QAPI_MOD_SPI, Status) : QAPI_OK)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

enum
{
    SPI_OPCODE_INVALID = 0,
    SPI_OPCODE_TX_ONLY = 1,
    SPI_OPCODE_RX_ONLY = 2,
    SPI_OPCODE_FULL_DUPLEX = 3,
    SPI_OPCODE_TX_THEN_RX = 7,
    SPI_OPCODE_CS_ASSERT = 8,
    SPI_OPCODE_CS_DEASSERT = 9,
    SPI_OPCODE_SCK_ONLY = 10
} SPI_Opcode_t;

enum
{
    SPI_PARAM_PRE_COMMAND_DELAY = 1 << 0,
    SPI_PARAM_TIMESTAMP_BEFORE = 1 << 1,
    SPI_PARAM_FRAGMENTATION = 1 << 2,
    SPI_PARAM_TIMESTAMP_AFTER = 1 << 3,
    SPI_PARAM_POST_COMMAND_DELAY = 1 << 4,
    SPI_PARAM_TPM_COMMAND = 1 << 5,
    SPI_PARAM_CS_TOGGLE = 1 << 6,          /**< CS TOGGLE between TX to RX command */
    SPI_PARAM_CLOCK_TOGGLE = 1 << 7,       /**< Clock toggle until cancel, when set with opcode 10 */
    SPI_PARAM_RWORD_DATA = 1 << 11,        /**< Remaining word is data */
    SPI_PARAM_FWORD_DATA = 1 << 12,        /**< First word is data */
    SPI_PARAM_4WIRE_8BIT_MODE = 1 << 13    /**< 4 wire 8 bit mode */
} SPI_Param_t;

typedef struct SPI_HwCtxt_s
{
    qapi_SPI_Instance_t Instance;
    uint32_t CurFreqHz;

    qbool_t Blocking;
    qbool_t Master;
    qbool_t Dma;
    qapi_SPI_Mode_t Mode;

    qapi_SPI_CB_t CFn;    /**< Callback of current transfer */
    void *CCtxt;

    QUP_XferCtxt_t *XferCtxt;

    uint32_t TransferNum;
    qapi_SPI_Transfer_t *TransferPool[SPI_TRANSFER_NUM_MAX];

    void *LowRateTxBuf;
} SPI_HwCtxt_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

qapi_Status_t SPI_Transfer(qapi_SPI_Instance_t Instance, qapi_SPI_Transfer_t *Transfer);
static void SPI_GeniCallback(uint32_t Status, void *CallbackCtxt);
static void SPI_FlushXferPool(SPI_HwCtxt_t *HwCtxt);
static void *SPI_LowRateFixup(qapi_SPI_Transfer_t *Transfer, uint32_t Scale, qbool_t Lsb);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the SPI controller.

   This function initializes internal data structures along with associated
   static data. In any operating mode, this function should be called before
   calling any other SPI controller API.

   @param[in]  Instance  SPI instance specified by #qapi_SPI_Instance_t.
   @param[in]  Config    SPI config specified by #qapi_SPI_Config_t.

   @return
   QAPI_OK                              --  Module was initialized successfully.
   QAPI_SPI_ERROR_INVALID_PARAM         --  Invalid instance or handle parameter.
   QAPI_SPI_ERROR_MEM_ALLOC             --  Could not allocate space for driver structures.
*/
qapi_Status_t qapi_SPI_Open(qapi_SPI_Instance_t Instance, qapi_SPI_Config_t *Config)
{
    uint32_t Status;
    QUP_BusConfig_t SpiConfig;
    QUP_Instance_t QUP_Instance;
    SPI_HwCtxt_t *HwCtxt;

    if (!Config || Instance >= QAPI_SPI_INSTANCE_MAX_E ||
        Config->Mode >= QAPI_SPI_MODE_MAX_E)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    switch (Config->Mode)
    {
        case QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E:
            SpiConfig.BusType = QUP_BUS_SPI_MASTER_3WIRE_9BIT;
            break;
        case QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E:
            SpiConfig.BusType = QUP_BUS_SPI_MASTER_4WIRE_8BIT;
            break;
        case QAPI_SPI_MODE_MASTER_E:
            SpiConfig.BusType = QUP_BUS_SPI_MASTER;
            break;
        case QAPI_SPI_MODE_SLAVE_E:
        default:
            SpiConfig.BusType = QUP_BUS_SPI_SLAVE;
            break;
    }

    QUP_Instance = (QUP_Instance_t)Instance;
    SpiConfig.Blocking = !!Config->Blocking;
    SpiConfig.XferMode = (QUP_XferMode_t)!!Config->Dma;
    SpiConfig.ExtraData = NULL;
    SpiConfig.NoMuxPriority = !!Config->NoMuxPriority;

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (HwCtxt)
    {
        if (HwCtxt->Mode != Config->Mode ||
            HwCtxt->Blocking != SpiConfig.Blocking ||
            HwCtxt->Dma != SpiConfig.XferMode)
        {
            return QAPI_SPI_ERROR_INVALID_PARAM;
        }

        return QAPI_OK;
    }

    Status = QUP_BusOpen(QUP_Instance, &SpiConfig, sizeof(SPI_HwCtxt_t));
    if (!Status)
    {
        SPI_HwCtxt_t *HwCtxt;

        HwCtxt = QUP_BusPrivGet(QUP_Instance);
        if (!HwCtxt)
        {
            QUP_BusClose(QUP_Instance);
            return QAPI_SPI_ERROR_MEM_ALLOC;
        }
        HwCtxt->Instance = Instance;
        HwCtxt->TransferNum = 0;
        HwCtxt->Blocking = SpiConfig.Blocking;
        HwCtxt->Dma = SpiConfig.XferMode;
        HwCtxt->Mode = Config->Mode;
        HwCtxt->XferCtxt = QUP_XferCtxtGet(QUP_Instance);

        if (Config->Mode != QAPI_SPI_MODE_SLAVE_E)
        {
            HwCtxt->Master = true;
        }
    }

    return SPI_ErrorMap(Status);
}

/**
   @brief Performs a data transfer over the SPI bus.

   This function performs transfer over the SPI bus. Transfers can be one-directional
   or bi-directional. If the callback is set, it will be invoked when transfer
   completion.

   @param[in] Instance    The instance enabled by qapi_SPI_Enable().
   @param[in] Transfer    Pointer to the SPI tranfer structure

   @return
   QAPI_OK                                  --  SPI master transfer successfully.
   QAPI_SPI_ERROR_INVALID_PARAM             --  One ore more parameters are invalid.
   QAPI_SPI_ERROR_TRANSFER_BUSY             --  SPI core is busy.
   QAPI_SPI_ERROR_TRANSFER_TIMEOUT          --  Transfer timed out.
   QAPI_SPI_ERROR_INPUT_FIFO_UNDER_RUN      --  SW reads from an empty RX FIFO.
   QAPI_SPI_ERROR_INPUT_FIFO_OVER_RUN       --  HW writes to a full RX FIFO.
   QAPI_SPI_ERROR_OUTPUT_FIFO_UNDER_RUN     --  SW reads a new word from an empty TX FIFO.
   QAPI_SPI_ERROR_OUTPUT_FIFO_OVER_RUN      --  SW writes a new word into a full TX FIFO.
   QAPI_SPI_ERROR_COMMAND_OVER_RUN          --  A new command is initialized before the previous one done.
   QAPI_SPI_ERROR_TRANSFER_FORCE_TERMINATED --  Command abort or cancel request by SW.
   QAPI_SPI_ERROR_COMMAND_ILLEGAL           --  Command with illegal opcode.
   QAPI_SPI_ERROR_COMMAND_FAIL              --  Command execution has been completed with failure.
   QAPI_SPI_ERROR_DMA_TX_BUS_ERROR          --  Bus error during DMA Tx transaction.
   QAPI_SPI_ERROR_DMA_RX_BUS_ERROR          --  Bus error during DMA Rx transaction.
*/
qapi_Status_t qapi_SPI_Transfer(qapi_SPI_Instance_t Instance, qapi_SPI_Transfer_t *Transfer)
{
    if (Instance >= QAPI_SPI_INSTANCE_MAX_E || !Transfer)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    return SPI_Transfer(Instance, Transfer);
}

/**
   @brief Closes the SPI controller.

   This function will cancel all pending transfers, frees all internal data
   structures and closes the SPI master interface.

   @param[in] Instance  The instance opened by qapi_SPI_Open().

   @return
   QAPI_OK                          --  SPI driver was closed successfully.
   QAPI_SPI_ERROR_INVALID_PARAM     --  Invalid instance parameter.
*/
qapi_Status_t qapi_SPI_Close(qapi_SPI_Instance_t Instance)
{
    uint32_t Status;
    SPI_HwCtxt_t *HwCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    if (Instance > QAPI_SPI_INSTANCE_MAX_E)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (!HwCtxt)
    {
        return QAPI_OK;
    }

    QUP_BusMCancelSync(QUP_Instance);

    if (!HwCtxt->Blocking)
    {
        SPI_FlushXferPool(HwCtxt);
    }

    Status = QUP_BusClose(QUP_Instance);

    return SPI_ErrorMap(Status);
}

static inline qapi_Status_t SPI_TransferCheck(qapi_SPI_Transfer_t *Transfer, SPI_HwCtxt_t *HwCtxt)
{
    uint32_t BitsPerWord;

    /* Invalid buffers */
    if (!Transfer->TxBuf && !Transfer->RxBuf)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    /* Max 2^24 - 1 */
    if ((Transfer->TxBuf && Transfer->TxLen > SPI_TRANSFER_LEN_MAX) ||
        (Transfer->RxBuf && Transfer->RxLen > SPI_TRANSFER_LEN_MAX))
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    /* Callback function must be set in nonblocking mode */
    if (!HwCtxt->Blocking && !Transfer->CallbackFn)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    if (HwCtxt->Master)
    {
        qapi_SPI_MXferInfo_t *MXferInfo = &Transfer->XferInfo.Master;

        if (((MXferInfo->CsLine >= QAPI_SPI_SLAVES_MAX) && !(MXferInfo->Flags & QAPI_SPI_XFER_NWIRE_MUL_CS)) ||
            MXferInfo->FreqHz < QAPI_SPI_FREQ_MIN ||
            MXferInfo->FreqHz > QAPI_SPI_FREQ_MAX)
        {
            return QAPI_SPI_ERROR_INVALID_PARAM;
        }

        /* Should have same tx and rx buffer in loopback test mode */
        if ((MXferInfo->Flags & QAPI_SPI_XFER_LOOPBACK) && (!Transfer->TxBuf ||
            !Transfer->RxBuf || Transfer->TxLen != Transfer->RxLen))
        {
            return QAPI_SPI_ERROR_INVALID_PARAM;
        }

        if ((MXferInfo->Flags & QAPI_SPI_XFER_LOW_RATE) &&
            (HwCtxt->Blocking || MXferInfo->BitsPerWord != 8 || Transfer->RxBuf ||
             MXferInfo->FreqHz >= 64))
        {
            return QAPI_SPI_ERROR_INVALID_PARAM;
        }

        BitsPerWord = MXferInfo->BitsPerWord;
    }
    else
    {
        BitsPerWord = Transfer->XferInfo.Slave.BitsPerWord;
    }

    /* Valid data frame size is from 4 to 32 */
    if (BitsPerWord < QAPI_SPI_BITSPERWORD_MIN ||
        BitsPerWord > QAPI_SPI_BITSPERWORD_MAX)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    return QAPI_OK;
}

static qapi_SPI_Transfer_t *SPI_GetXferPoolHead(SPI_HwCtxt_t *HwCtxt)
{
    return HwCtxt->TransferPool[0];
}

static qapi_Status_t SPI_AddToXferPoolTail(qapi_SPI_Transfer_t *Transfer, SPI_HwCtxt_t *HwCtxt)
{
    if (HwCtxt->TransferNum >= SPI_TRANSFER_NUM_MAX)
    {
        return QAPI_SPI_ERROR_TRANSFER_BUSY;
    }
 
    HwCtxt->TransferPool[HwCtxt->TransferNum++] = Transfer;

    return QAPI_OK;
}

static qapi_SPI_Transfer_t *SPI_DelFromXferPoolHead(SPI_HwCtxt_t *HwCtxt)
{
    qapi_SPI_Transfer_t *Transfer = HwCtxt->TransferPool[0];

    if (HwCtxt->TransferNum < 1)
    {
        Qup_AssertFunc();
    }

    memcpy(&HwCtxt->TransferPool[0], &HwCtxt->TransferPool[1],
        (HwCtxt->TransferNum - 1) * sizeof(void *));
    HwCtxt->TransferNum--;

    return Transfer;
}

static void SPI_FlushXferPool(SPI_HwCtxt_t *HwCtxt)
{
    qapi_SPI_Transfer_t *Transfer;

    if (HwCtxt->LowRateTxBuf)
    {
        qapi_Free(HwCtxt->LowRateTxBuf);
        HwCtxt->LowRateTxBuf = NULL;
    }

    while (HwCtxt->TransferNum)
    {
        Transfer = SPI_DelFromXferPoolHead(HwCtxt);
        Transfer->CallbackFn((uint32_t)QAPI_SPI_ERROR_TRANSFER_FORCE_TERMINATED,
                             Transfer->CallbackCtxt);
    }
}

static qapi_Status_t SPI_PrepareGeniXferCtxt(SPI_HwCtxt_t *HwCtxt, qapi_SPI_Transfer_t *Transfer,
                                             QUP_XferCtxt_t *XferCtxt)
{
    QUP_SpiXferInfo_t *QupXferInfo = (QUP_SpiXferInfo_t *)&XferCtxt->XferInfo.Spi;
    qapi_SPI_XferInfo_t *XferInfo = &Transfer->XferInfo;
    uint32_t BitsPerWord;

    memset(XferCtxt, 0, sizeof (*XferCtxt));

    XferCtxt->TxWaterMark = 1;
    XferCtxt->RxWaterMark = 1;
    XferCtxt->TxBuf = Transfer->TxBuf;
    XferCtxt->RxBuf = Transfer->RxBuf;
    XferCtxt->TxLen = Transfer->TxLen;
    XferCtxt->RxLen = Transfer->RxLen;

    if (HwCtxt->Master)
    {
        qapi_SPI_MXferInfo_t *MXferInfo = &XferInfo->Master;
        QUP_SpiMXferInfo_t *QupMXferInfo = &QupXferInfo->Master;
    
        BitsPerWord = MXferInfo->BitsPerWord;
        QupMXferInfo->BitsPerWord = BitsPerWord;

        memcpy(QupMXferInfo, MXferInfo, sizeof(QUP_SpiMXferInfo_t));

        if (MXferInfo->Flags & QAPI_SPI_XFER_LOW_RATE)
        {
            uint32_t Scale = (MXferInfo->FreqHz == 1 ? 64 : (MXferInfo->FreqHz < 4 ? 32 : 16));
            void *NewTxBuf = SPI_LowRateFixup(Transfer, Scale, MXferInfo->Flags & QAPI_SPI_XFER_LSB_FIRST);

            if (!NewTxBuf)
            {
                return QAPI_SPI_ERROR_MEM_ALLOC;
            }

            QupMXferInfo->FreqHz *= Scale;
            XferCtxt->TxLen *= Scale;
            XferCtxt->TxBuf = NewTxBuf;
            HwCtxt->LowRateTxBuf = NewTxBuf;
        }

        if (QupMXferInfo->FreqHz != HwCtxt->CurFreqHz)
        {
            XferCtxt->ClkChanged = 1;
            HwCtxt->CurFreqHz = QupMXferInfo->FreqHz;
        }

        if (HwCtxt->Mode == QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E ||
            HwCtxt->Mode == QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E)
        {
            if (HwCtxt->Mode == QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E)
            {
                XferCtxt->CmdParam |= SPI_PARAM_4WIRE_8BIT_MODE;
            }
            if (!(MXferInfo->Flags & QAPI_SPI_XFER_FWORD_COMMAND))
            {
                XferCtxt->CmdParam |= SPI_PARAM_FWORD_DATA;
            }
            if (!(MXferInfo->Flags & QAPI_SPI_XFER_RWORD_COMMAND))
            {
                XferCtxt->CmdParam |= SPI_PARAM_RWORD_DATA;
            }
            if (Transfer->TxBuf && Transfer->RxBuf)
            {
	     	    XferCtxt->CmdParam |= SPI_PARAM_FRAGMENTATION;
            }
        }
    }
    else
    {
        qapi_SPI_SXferInfo_t *SXferInfo = &XferInfo->Slave;
        QUP_SpiSXferInfo_t *QupSXferInfo = &QupXferInfo->Slave;

        BitsPerWord = SXferInfo->BitsPerWord;
        memcpy(QupSXferInfo, SXferInfo, sizeof(QUP_SpiSXferInfo_t));
    }

    if (Transfer->TxBuf && Transfer->RxBuf)
    {
        XferCtxt->CmdOpcode = SPI_OPCODE_FULL_DUPLEX;
        if (HwCtxt->Mode == QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E ||
            HwCtxt->Mode == QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E)

        {
            XferCtxt->CmdOpcode = SPI_OPCODE_TX_THEN_RX;
        }
    }
    else if (Transfer->TxBuf)
    {
        XferCtxt->CmdOpcode = SPI_OPCODE_TX_ONLY;
        XferCtxt->RxLen = XferCtxt->TxLen;
    }
    else
    {
        /* 0 will prevent assertion of the interrupt bit */
        XferCtxt->TxWaterMark = 0;
        XferCtxt->CmdOpcode = SPI_OPCODE_RX_ONLY;
        XferCtxt->TxLen = XferCtxt->RxLen;
    }

    if (!HwCtxt->Blocking)
    {
        HwCtxt->CFn = Transfer->CallbackFn;
        HwCtxt->CCtxt = Transfer->CallbackCtxt;
        XferCtxt->CFn = SPI_GeniCallback;
        XferCtxt->CCtxt = HwCtxt;
    }

    return QAPI_OK;
}

static void SPI_GeniCallback(uint32_t Status, void *CallbackCtxt)
{
    SPI_HwCtxt_t *HwCtxt = (SPI_HwCtxt_t *)CallbackCtxt;
    QUP_Instance_t QUPInstance = (QUP_Instance_t)HwCtxt->Instance;

    if (HwCtxt->LowRateTxBuf)
    {
        qapi_Free(HwCtxt->LowRateTxBuf);
        HwCtxt->LowRateTxBuf = NULL;
    }

    HwCtxt->CFn(SPI_ErrorMap(Status), HwCtxt->CCtxt);
    SPI_DelFromXferPoolHead(HwCtxt);

    if (Status)
    {
        SPI_FlushXferPool(HwCtxt);
        goto err;
    }
            
    if (HwCtxt->TransferNum)
    {
        qapi_SPI_Transfer_t *Transfer;

        Transfer = SPI_GetXferPoolHead(HwCtxt);
        Status = SPI_PrepareGeniXferCtxt(HwCtxt, Transfer, HwCtxt->XferCtxt);
        if (!Status)
        {
            Status = SPI_ErrorMap(QUP_BusTransfer(QUPInstance, HwCtxt->XferCtxt));
        }

        if (Status)
        {
            HwCtxt->CFn(Status, HwCtxt->CCtxt);
            SPI_DelFromXferPoolHead(HwCtxt);
            SPI_FlushXferPool(HwCtxt);
            goto err;
        }
    }

    return;
err:
    QUP_BusMCancelSync(QUPInstance);
}

qapi_Status_t SPI_Transfer(qapi_SPI_Instance_t Instance, qapi_SPI_Transfer_t *Transfer)
{
    SPI_HwCtxt_t *HwCtxt;
    QUP_XferCtxt_t *XferCtxt;
    QUP_Status_t Status;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;
    qapi_Status_t _Status;

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (!HwCtxt)
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    if (SPI_TransferCheck(Transfer, HwCtxt))
    {
        return QAPI_SPI_ERROR_INVALID_PARAM;
    }

    XferCtxt = HwCtxt->XferCtxt;

    if (!HwCtxt->Blocking)
    {
        if (SPI_AddToXferPoolTail(Transfer, HwCtxt))
        {
            return QAPI_SPI_ERROR_TRANSFER_BUSY;
        }

        if (XferCtxt->Busy)
        {
            return QAPI_OK;
        }
        else if (HwCtxt->TransferNum > 1)
        {
            Transfer = SPI_GetXferPoolHead(HwCtxt);
        }
    }

    if ((_Status = SPI_PrepareGeniXferCtxt(HwCtxt, Transfer, XferCtxt)))
    {
        return _Status;
    }

    Status = QUP_BusTransfer(QUP_Instance, XferCtxt);

    return SPI_ErrorMap(Status);
}

/**
   @brief Workaround for reducing initial delay.

   The SPI initial delay is too long in low bit rate. e.g. It takes 27s at 1Hz, 13.5s at 2Hz.
   So we use 64x, 32x or 16x clock frequency, and replicate the orignial pattern. e.g.

   1Hz: output 64-bit 0xffffffffffffffff for every 1 and 0x0000000000000000 for every 0 bit
   [2,3]Hz: output 32-bit 0xffffffff for every 1 and 0x00000000 for every 0 bit
   [4Hz,64Hz]: output 16-bit 0xffff for every 1 and 0x0000 for every 0 bit

   And the fix will reduce the initial delay up to 400ms.
*/
static void *SPI_LowRateFixup(qapi_SPI_Transfer_t *Transfer, uint32_t Scale, qbool_t Lsb)
{
    int i, j, k, NewBufLen, Step;
    uint8_t *OrigData, *NewBuf = NULL;
    uint16_t *NewData;

    NewBufLen = Transfer->TxLen * Scale;
    NewBuf = qapi_Malloc(NewBufLen);
    if (!NewBuf)
    {
        goto out;
    }

    Step = (Scale == 64 ? 4 : (Scale == 32 ? 2 : 1));

    memset(NewBuf, 0, NewBufLen);
    OrigData = (uint8_t *)Transfer->TxBuf;
    NewData = (uint16_t *)NewBuf;

    for (i = 0, k = 0; i < Transfer->TxLen; i++)
    {
        uint8_t Tmp = OrigData[i];

        for (j = 0; j < 8; j++)
        {
            if ((!Lsb && (Tmp & 0x80)) || (Lsb && (Tmp & 0x01)))
            {
                switch (Step)
                {
                    case 4:
                        NewData[k + 3] = ~0;
                        NewData[k + 2] = ~0;
                    case 2:
                        NewData[k + 1] = ~0;
                    case 1:
                        NewData[k + 0] = ~0;
                        break;
                }
            }

            k += Step;

            if (Lsb)
            {
                Tmp >>= 1;
            }
            else
            {
                Tmp <<= 1;
            }
        }
    }

out:
    return NewBuf;
}
