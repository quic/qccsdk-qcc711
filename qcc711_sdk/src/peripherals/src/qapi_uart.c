/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "qapi_uart.h"
#include "qapi_task.h"
#include "qup_api.h"

#ifdef __QAPI_UART_H__

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define UART_TX_BUF_SIZE            128
#define UART_RX_BUF_SIZE            256
#define UART_BUF_COUNT           2

#define UART_MIN_NUM(A, B)          (A < B ? A : B)
#define UART_BUF_IDX_INC(Idx)       {Idx++; if(Idx >= UART_BUF_COUNT) Idx = 0;}
#define UART_BUF_IDX_DEC(Idx)       {Idx--; if(Idx < 0) Idx = 1;}
#define UART_IN_RANG(A, Min, Max)        ((A >= Min && A <= Max) ? true : false)

#define UART_ErrorMap(Status)       (Status > 0 ? __QAPI_ERROR(QAPI_MOD_UART, Status) : Status)

enum
{
    UART_OPCODE_TX = 1,
    UART_OPCODE_RX = UART_OPCODE_TX,
    UART_OPCODE_START_BREAK = 4,
    UART_OPCODE_STOP_BREAK = 5,
} UART_Opcode_t;

typedef struct
{
   uint32_t BitRate;
   uint32_t Divider;
} UART_ClockSetting_t;

typedef struct UART_Buf_s
{
    uint8_t* Buf;
    uint32_t Len;
}UART_Buf_t;

typedef struct UART_BufDMA_s
{
    UART_Buf_t BufDma[UART_BUF_COUNT];
    int8_t IdxTrans;                    /**< index for read/write. */
    int8_t IdxFree;
}UART_BufDMA_t;

typedef struct UART_XferBufs_s
{
    union
    {
        QUP_CircBuf_t TxCircBuf;      /**< for FIFO mode. */
        UART_BufDMA_t TxDMABuf;       /**< for DMA mode. */
    } TxBuf;
    union
    {
        QUP_CircBuf_t RxCircBuf;      /**< for FIFO mode. */
        UART_BufDMA_t RxDMABuf;       /**< for DMA mode. */
    } RxBuf;
    uint8_t RxBufStarving;            /**< no available Rx buffer for driver. */

}UART_XferBufs_t;

typedef struct UART_HwCtxt_s
{
    qapi_UART_Instance_t Instance;

    qbool_t Master;
    QUP_XferMode_t XferMode;
    QUP_BusType_t BusType;
    uint16_t TxBufSize;
    uint16_t RxBufSize;
    uint32_t TxRemaining;

    qapi_UART_CB_t TxCbFunc;
    qapi_UART_CB_t RxCbFunc;
    void *CbCtxt;

    QUP_XferCtxt_t *XferCtxt;
} UART_HwCtxt_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
UART_XferBufs_t UART_XferBufs[QAPI_UART_INSTANCE_MAX];
static const UART_ClockSetting_t BaudTable[] =
{
    {2400, 833}, {4800, 416}, {9600, 208}, {19200, 104}, {28800, 69},
    {38400, 52}, {57600, 34}, {76800, 26}, {115200, 17}, {125000, 16},
    {250000, 8}, {500000, 4}, {1000000, 2}, {2000000, 1}, {0, 0}
};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static int32_t UART_GetClockDivider(uint32_t BaudRate);
static qapi_Status_t UART_BufInit(UART_XferBufs_t* XferBuf, QUP_XferMode_t XferMode, uint16_t TxSize, uint16_t RxSize);
static void UART_BufFree(UART_XferBufs_t* XferBuf, QUP_XferMode_t XferMode);
static void UART_GeniRxCallback(uint32_t Status, void *CallbackCtxt);
static void UART_GeniTxCallback(uint32_t Status, void *CallbackCtxt);
static int8_t UART_GetFreeBufIdx(UART_BufDMA_t* DMABuf);
static qapi_Status_t UART_HandleTx(UART_HwCtxt_t *HwCtxt);
static qapi_Status_t UART_HandleRx(UART_HwCtxt_t *HwCtxt);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the UART controller.

   Opens the UART controller and configures the corresponding clocks, interrupts, and GPIO. In any
   operating mode, this function should be called before calling any other UART controller API.

   @param[in] Instance  UART instance specified by #qapi_UART_Instance_t.
   @param[in] Config    Structure that holds all configuration data.

   @return
   - QAPI_OK                        UART instance open successfully.
   - QAPI_UART_ERROR_INVALID_PARAM  Invalid instance or handle parameter.
   - QAPI_UART_ERROR_MEM_ALLOC      Could not allocate space for driver structures.
*/
qapi_Status_t qapi_UART_Open(qapi_UART_Instance_t Instance, qapi_UART_Config_t* Config)
{
    uint32_t Status;
    QUP_BusConfig_t UartConfig;
    QUP_Instance_t QUP_Instance;
    UART_HwCtxt_t *HwCtxt;
    int32_t ClkDivider;

    if ( !Config || Instance >= QAPI_UART_INSTANCE_MAX ||
          (Config->TxBufSize < 64) ||  (Config->RxBufSize < 64))
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(Config->RxStaleCnt < 1 || Config->RxStaleCnt > 1023)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    QUP_Instance = (QUP_Instance_t)Instance;

    if(Config->BitsPerChar >= QAPI_UART_5_BITS_PER_CHAR_E && Config->BitsPerChar <= QAPI_UART_8_BITS_PER_CHAR_E)
    {
        if(Config->TxInvert && Config->BitsPerChar == QAPI_UART_8_BITS_PER_CHAR_E)
        {
            UartConfig.BusType = QUP_BUS_UART_TX_INVERT;
        }
        else
        {
            UartConfig.BusType = QUP_BUS_UART;
        }
    }
    else if(Config->BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_SW_E)
    {
        UartConfig.BusType = QUP_BUS_UART_9BIT_SW;
        Config->BitsPerChar = QAPI_UART_9_BITS_PER_CHAR_SW_E;
    }
    else if(Config->BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_HW_E)
    {
        UartConfig.BusType = QUP_BUS_UART_9BIT_HW;
        Config->BitsPerChar = QAPI_UART_8_BITS_PER_CHAR_E;
    }
    else
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    UartConfig.Blocking = 0;
    if(Config->Dma)
    {
        UartConfig.XferMode = QUP_XFER_DMA;
        Config->TxBufSize = Config->TxBufSize >> 1;
        Config->RxBufSize = Config->RxBufSize >> 1; /* 2 dma buffer share the total size */
    }
    else
    {
        UartConfig.XferMode = QUP_XFER_FIFO;
    }

    if(UartConfig.BusType == QUP_BUS_UART_9BIT_SW)
    {
        /* In 9-bit SW mode, make sure the buffer size is 2*n */
        if(Config->TxBufSize%2)
            Config->TxBufSize = Config->TxBufSize - 1;
        if(Config->RxBufSize%2)
            Config->RxBufSize = Config->RxBufSize - 1;
    }
    else if(UartConfig.XferMode == QUP_XFER_FIFO)
    {
        Config->TxBufSize = Config->TxBufSize + 1;
        Config->RxBufSize = Config->RxBufSize + 1; 
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (HwCtxt)
    {
        if (HwCtxt->BusType!= UartConfig.BusType ||
            HwCtxt->XferMode != UartConfig.XferMode)
        {
            return QAPI_UART_ERROR_INVALID_PARAM;
        }

        return QAPI_OK;
    }

    Status = QUP_BusOpen(QUP_Instance, &UartConfig, sizeof(UART_HwCtxt_t));
    if (!Status)
    {
        HwCtxt = QUP_BusPrivGet(QUP_Instance);
        if (!HwCtxt)
        {
            Status = QUP_ERROR;
            goto Exit;
        }
        HwCtxt->Instance = Instance;
        HwCtxt->XferMode = UartConfig.XferMode;
        HwCtxt->BusType = UartConfig.BusType;
        HwCtxt->TxBufSize = Config->TxBufSize;
        HwCtxt->RxBufSize = Config->RxBufSize;
        HwCtxt->RxCbFunc = Config->RxCbFunc;
        HwCtxt->TxCbFunc = Config->TxCbFunc;
        HwCtxt->CbCtxt= Config->CallbackCtxt;
        HwCtxt->XferCtxt = QUP_XferCtxtGet(QUP_Instance);
        if (!HwCtxt->XferCtxt)
        {
            Status = QUP_ERROR;
            goto Exit;
        }
        HwCtxt->XferCtxt->CFn = UART_GeniRxCallback;
        HwCtxt->XferCtxt->TxCFn = UART_GeniTxCallback;
        HwCtxt->XferCtxt->CCtxt = HwCtxt;
        HwCtxt->XferCtxt->XferInfo.Uart.BitsPerChar = Config->BitsPerChar;
        HwCtxt->XferCtxt->XferInfo.Uart.Parity = Config->ParityMode;
        HwCtxt->XferCtxt->XferInfo.Uart.NumStopBits = Config->NumStopBits;
        HwCtxt->XferCtxt->XferInfo.Uart.Loopback = Config->EnableLoopback;
        HwCtxt->XferCtxt->XferInfo.Uart.FlowCtrl = Config->EnableFlowCtrl;
        HwCtxt->XferCtxt->XferInfo.Uart.RxStaleCnt = Config->RxStaleCnt;

        ClkDivider = UART_GetClockDivider(Config->BaudRate);
        if (ClkDivider < 0)
        {
            Status = QUP_ERROR_INVALID_PARAM;
            goto Exit;
        }
        else
            HwCtxt->XferCtxt->XferInfo.Uart.ClkDivider = ClkDivider;

        QUP_UartXferConfig((QUP_Instance_t)Instance, HwCtxt->XferCtxt);

        Status = UART_BufInit(&(UART_XferBufs[Instance]), HwCtxt->XferMode, HwCtxt->TxBufSize, HwCtxt->RxBufSize);

        if(Status != QAPI_OK)
            goto Exit;

        if(HwCtxt->BusType != QUP_BUS_UART_9BIT_HW)
        {
            /* Start Uart Rx */
            UART_HandleRx(HwCtxt);
        }
    }

Exit:
    if(Status != QAPI_OK)
    {
        QUP_BusClose(QUP_Instance);
    }
    return UART_ErrorMap(Status);
}

/**
   @brief Closes the UART controller.

   Releases clock, interrupt, and GPIO handles related to this UART and
   cancels any pending transfers.

   @param[in] Instance  UART instance opened by qapi_UART_Open().

   @return
   - QAPI_OK                        UART instance close successful.
   - QAPI_UART_ERROR_INVALID_PARAM  Invalid instance parameter.
*/
qapi_Status_t qapi_UART_Close(qapi_UART_Instance_t Instance)
{
    UART_HwCtxt_t *HwCtxt;
    uint32_t Status;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    if (Instance >= QAPI_UART_INSTANCE_MAX)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);

    if (!HwCtxt)
    {
        return QAPI_OK;
    }

    QUP_BusMCancelSync(QUP_Instance);
    QUP_BusSCancelSync(QUP_Instance);

    UART_BufFree(&UART_XferBufs[Instance], HwCtxt->XferMode);

    Status = QUP_BusClose(QUP_Instance);

    return UART_ErrorMap(Status);
}

/**
   @brief Copy the received data from internal buffer to application buffer.
   This is an asynchronous call. the QAPI is none blocking.

   @param[in]     Instance     UART instance opened by qapi_UART_Open().
   @param[in]     Buf          Buffer to be filled with data.
   @param[in,out] BufSize      Input: length of the Buf, output: length of bytes has been read.
   @param[out]    BytesRemain  Bytes of data remain in the driver.

   @return
   - QAPI_OK                             -- UART transfer successfully.
   - QAPI_UART_ERROR_INVALID_PARAM       -- One ore more parameters are invalid.
   - QAPI_UART_ERROR_NO_DATA_TO_TRANSFER -- No data in the internal buffer for receive.
*/
qapi_Status_t qapi_UART_Receive(qapi_UART_Instance_t Instance, char* Buf, uint32_t* BufSize, uint32_t* BytesRemain)
{
    UART_HwCtxt_t *HwCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;
    uint16_t Idx2Rx, CopyLen=0, CntToEnd;
    int16_t Status = QUP_SUCCESS;

    *BytesRemain = 0;

    if (Instance >= QAPI_UART_INSTANCE_MAX)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }
    HwCtxt = QUP_BusPrivGet(QUP_Instance);

    if (!HwCtxt)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        UART_BufDMA_t* UartRxBuf = &(UART_XferBufs[HwCtxt->Instance].RxBuf.RxDMABuf);
        Idx2Rx = UartRxBuf->IdxTrans;
        CopyLen = UartRxBuf->BufDma[Idx2Rx].Len;

        if(CopyLen <= 0)
        {
            Status = QAPI_UART_ERROR_NO_DATA_TO_TRANSFER;
            goto handleRx;
        }

        if(*BufSize < CopyLen)
        {
            Status = QAPI_UART_ERROR_INVALID_PARAM;
            goto handleRx;
        }

        memcpy(Buf, UartRxBuf->BufDma[Idx2Rx].Buf, CopyLen);
        UartRxBuf->BufDma[Idx2Rx].Len = 0;

        UART_BUF_IDX_INC(Idx2Rx);
        UartRxBuf->IdxTrans = Idx2Rx;
        *BytesRemain = UartRxBuf->BufDma[Idx2Rx].Len;
    }
    else
    {
        QUP_CircBuf_t *CircBuf = &(UART_XferBufs[HwCtxt->Instance].RxBuf.RxCircBuf);

        CntToEnd = Qup_CircCntToEnd(CircBuf->Head, CircBuf->Tail, HwCtxt->RxBufSize);

        CopyLen = UART_MIN_NUM(CntToEnd, *BufSize);

        if(CopyLen == 0)
        {
            Status = QAPI_UART_ERROR_NO_DATA_TO_TRANSFER;
            goto handleRx;
        }

        memcpy(Buf, &CircBuf->Buf[CircBuf->Tail], CopyLen);
        CircBuf->Tail = (CircBuf->Tail + CopyLen) % (HwCtxt->RxBufSize);

        qapi_TSK_Enter_Critical();
        if(CircBuf->Tail == CircBuf->Head)
        {
            CircBuf->Tail = CircBuf->Head = 0;
        }
        qapi_TSK_Exit_Critical();

    }

handleRx:
    *BufSize = CopyLen;

    if(UART_XferBufs[HwCtxt->Instance].RxBufStarving || HwCtxt->XferCtxt->UnReadFlag)
    {
        UART_HandleRx(HwCtxt);
    }
    
    if(HwCtxt->XferMode == QUP_XFER_FIFO)
    {
        /* in FIFO mode, QAPI MUST read data from FIFO directly when there is remain data in last ISR,
            as in this situatuin, Rx ISR will not be triggered until the FIFO data is read all out. */
        QUP_CircBuf_t *CircBuf = &(UART_XferBufs[HwCtxt->Instance].RxBuf.RxCircBuf);
        *BytesRemain = QUP_CIRC_CNT(CircBuf->Head, CircBuf->Tail, HwCtxt->RxBufSize);
    }

    return UART_ErrorMap(Status);
}

/**
   @brief Copy the application buffer to ring buffer. Then queues the ring
   buffer to DMA engine or write to FIFO. The QAPI is none-blocking.

   @param[in]  Instance   UART instance opened by qapi_UART_Open().
   @param[in]  Buf        Buffer with data for transmit.
   @param[in]  BytesToTx  Bytes of data to transmit.
   @param[out] BytesSent  Bytes of data already been sent.

   @return
   - QAPI_OK                             -- UART transfer successfully.
   - QAPI_UART_ERROR_INVALID_PARAM       -- One ore more parameters are invalid.
   - QAPI_UART_ERROR_NO_DATA_TO_TRANSFER -- No data to transmit.
   - QAPI_UART_ERROR_TRANSMIT_BUSY       -- Uart tansmit under going.
*/
qapi_Status_t qapi_UART_Transmit(qapi_UART_Instance_t Instance, char* Buf, uint32_t BytesToTx, uint32_t* BytesSent)
{
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;
    uint16_t BufLenToEnd, BufLen, CopyLen = 0;
    UART_HwCtxt_t *HwCtxt;
    int16_t Status = QUP_SUCCESS;

    if (Instance >= QAPI_UART_INSTANCE_MAX || !Buf)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);

    if (!HwCtxt)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        UART_BufDMA_t* UartTxBuf = &(UART_XferBufs[HwCtxt->Instance].TxBuf.TxDMABuf);
        int8_t IdxFree = UART_GetFreeBufIdx(UartTxBuf);

        if(IdxFree < 0)
        {
            Status = QAPI_UART_ERROR_NO_AVAILABLE_BUF;
            goto handleTx;
        }

        BufLen = HwCtxt->TxBufSize;
        CopyLen = UART_MIN_NUM(BufLen, BytesToTx);

        if(CopyLen > 0)
        {
            qapi_TSK_Enter_Critical();
            memcpy(UartTxBuf->BufDma[IdxFree].Buf, Buf, CopyLen);
            UartTxBuf->BufDma[IdxFree].Len = CopyLen;
            qapi_TSK_Exit_Critical();
        }
    }
    else
    {
        QUP_CircBuf_t *CircBuf = &(UART_XferBufs[Instance].TxBuf.TxCircBuf);
        BufLenToEnd = Qup_CircSpaceToEnd(CircBuf->Head, CircBuf->Tail, HwCtxt->TxBufSize);

        CopyLen = UART_MIN_NUM(BufLenToEnd, BytesToTx);

        if (CopyLen > 0)
        {
            qapi_TSK_Enter_Critical();
            memcpy(&(CircBuf->Buf[CircBuf->Head]), (uint8_t*)Buf, CopyLen);
            CircBuf->Head = (CircBuf->Head + CopyLen) % (HwCtxt->TxBufSize);
            qapi_TSK_Exit_Critical();
        }
    }

handleTx:
    *BytesSent = CopyLen;

    qapi_TSK_Enter_Critical();
    HwCtxt->TxRemaining += *BytesSent;
    qapi_TSK_Exit_Critical();

    UART_HandleTx(HwCtxt);

    return UART_ErrorMap(Status);
}

/**
   @brief Set transmit/receive address in 9-bit HW mode.

   @param[in] Instance  UART instance opened by qapi_UART_Open().
   @param[in] Dir       Transimit or receive direction.
   @param[in] Address   Address value.

   @return
   - QAPI_OK     				   -- Adress set was successful.
   - QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_UART_Set_TRAddress(qapi_UART_Instance_t Instance, qapi_UART_Tra_Direction_t Dir, uint8_t Address)
{
    UART_HwCtxt_t *HwCtxt;
    QUP_XferCtxt_t *XferCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    if (Instance >= QAPI_UART_INSTANCE_MAX)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);

    if (!HwCtxt)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(HwCtxt->BusType != QUP_BUS_UART_9BIT_HW)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    XferCtxt = HwCtxt->XferCtxt;
    if(Dir == QAPI_UART_TA_E)
    {
        XferCtxt->XferInfo.Uart.TxAddress = Address;
    }
    else if(Dir == QAPI_UART_RA_E)
    {
        XferCtxt->XferInfo.Uart.RxAddress = Address;

        UART_HandleRx(HwCtxt);
    }
    else
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    return QAPI_OK;
}

/**
   @brief Get transmit/receive address in 9-bit HW mode.

   @param[in]  Instance  UART instance opened by qapi_UART_Open().
   @param[in]  Dir       Transimit or receive direction.
   @param[out] Address   Address value.

   @return
   - QAPI_OK     				   -- Adress get was successful.
   - QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_UART_Get_TRAddress(qapi_UART_Instance_t Instance, qapi_UART_Tra_Direction_t Dir, uint8_t* Address)
{
    UART_HwCtxt_t *HwCtxt;
    QUP_XferCtxt_t *XferCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    if (Instance >= QAPI_UART_INSTANCE_MAX)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);

    if (!HwCtxt)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(HwCtxt->BusType != QUP_BUS_UART_9BIT_HW)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    XferCtxt = HwCtxt->XferCtxt;
    if(Dir == QAPI_UART_TA_E)
    {
        *Address = XferCtxt->XferInfo.Uart.TxAddress;
    }
    else if(Dir == QAPI_UART_RA_E)
    {
        *Address = XferCtxt->XferInfo.Uart.RxAddress;
    }
    else
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    return QAPI_OK;
}

volatile uint32_t error_count;
uint32_t qapi_UART_Get_Tx_Remaining(qapi_UART_Instance_t Instance)
{
    uint32_t TxRemaining;
    UART_HwCtxt_t *HwCtxt;

    HwCtxt = QUP_BusPrivGet((QUP_Instance_t)Instance);

    if (HwCtxt != NULL)
    {
        TxRemaining = HwCtxt->TxRemaining;
    }
    else
    {
        TxRemaining = 0;
    }

    return TxRemaining;
}

static int32_t UART_GetClockDivider(uint32_t BaudRate)
{
   const UART_ClockSetting_t *Entry;

    for(Entry = BaudTable; Entry->BitRate; Entry++)
    {
        if(Entry->BitRate == BaudRate)
            break;
    }

    if (Entry->Divider == 0)
    {
       return QAPI_UART_ERROR_INVALID_PARAM;
    }

    return Entry->Divider;
}

static qapi_Status_t UART_BufInit(UART_XferBufs_t* XferBuf, QUP_XferMode_t XferMode, uint16_t TxSize, uint16_t RxSize)
{
    uint8_t I;
    qapi_Status_t Status = QAPI_OK;

    if(XferMode == QUP_XFER_DMA)
    {
        for(I=0; I < UART_BUF_COUNT; I++)
        {
            if((XferBuf->TxBuf.TxDMABuf.BufDma[I].Buf = (uint8_t *)qapi_Malloc(TxSize)) == NULL)
            {
                Status = QAPI_UART_ERROR_MEM_ALLOC;
                goto Exit;
            }
            XferBuf->TxBuf.TxDMABuf.BufDma[I].Len = 0;

            if((XferBuf->RxBuf.RxDMABuf.BufDma[I].Buf = (uint8_t *)qapi_Malloc(RxSize)) == NULL)
            {
                Status = QAPI_UART_ERROR_MEM_ALLOC;
                goto Exit;
            }
            XferBuf->RxBuf.RxDMABuf.BufDma[I].Len = 0;
        }

        XferBuf->RxBuf.RxDMABuf.IdxTrans = 0;
        XferBuf->RxBuf.RxDMABuf.IdxFree = 0;
        XferBuf->TxBuf.TxDMABuf.IdxTrans = 0;
        XferBuf->TxBuf.TxDMABuf.IdxFree = 0;
    }
    else
    {
        if((XferBuf->TxBuf.TxCircBuf.Buf = (uint8_t *)qapi_Malloc(TxSize)) == NULL)
        {
            Status = QAPI_UART_ERROR_MEM_ALLOC;
            goto Exit;
        }

        XferBuf->TxBuf.TxCircBuf.Head = XferBuf->TxBuf.TxCircBuf.Tail = 0;
        XferBuf->TxBuf.TxCircBuf.Size = TxSize;

        if((XferBuf->RxBuf.RxCircBuf.Buf = (uint8_t *)qapi_Malloc(RxSize)) == NULL)
        {
            Status = QAPI_UART_ERROR_MEM_ALLOC;
            goto Exit;
        }

        XferBuf->RxBuf.RxCircBuf.Head = XferBuf->RxBuf.RxCircBuf.Tail = 0;
        XferBuf->RxBuf.RxCircBuf.Size = RxSize;
    }
    XferBuf->RxBufStarving = 0;

Exit:
    if(Status != QAPI_OK)
    {
        UART_BufFree(XferBuf, XferMode);
    }

    return Status;
}

static void UART_BufFree(UART_XferBufs_t* XferBuf, QUP_XferMode_t XferMode)
{
    uint8_t I;

    if(!XferBuf)
        return;

    if(XferMode == QUP_XFER_DMA)
    {
        for(I=0; I < UART_BUF_COUNT; I++)
        {
            if(XferBuf->TxBuf.TxDMABuf.BufDma[I].Buf)
            {
                qapi_Free(XferBuf->TxBuf.TxDMABuf.BufDma[I].Buf);
                XferBuf->TxBuf.TxDMABuf.BufDma[I].Len = 0;
            }

            if(XferBuf->RxBuf.RxDMABuf.BufDma[I].Buf)
            {
                qapi_Free(XferBuf->RxBuf.RxDMABuf.BufDma[I].Buf);
                XferBuf->RxBuf.RxDMABuf.BufDma[I].Len = 0;
            }
        }

        XferBuf->TxBuf.TxDMABuf.IdxTrans = -1;
        XferBuf->TxBuf.TxDMABuf.IdxFree = -1;
        XferBuf->RxBuf.RxDMABuf.IdxTrans = -1;
        XferBuf->RxBuf.RxDMABuf.IdxFree = -1;
    }
    else
    {
        qapi_Free(XferBuf->TxBuf.TxCircBuf.Buf);
        XferBuf->TxBuf.TxCircBuf.Head = 0;
        XferBuf->TxBuf.TxCircBuf.Tail = 0;
        XferBuf->TxBuf.TxCircBuf.Size = 0;

        qapi_Free(XferBuf->RxBuf.RxCircBuf.Buf);
        XferBuf->RxBuf.RxCircBuf.Head = 0;
        XferBuf->RxBuf.RxCircBuf.Tail = 0;
        XferBuf->RxBuf.RxCircBuf.Size = 0;
    }
    XferBuf->RxBufStarving = 0;
}

static int8_t UART_GetFreeBufIdx(UART_BufDMA_t* DMABuf)
{
    int8_t I, StartI, TempI, Idx = -1;

    StartI = DMABuf->IdxFree;
    for(I=StartI; I < (UART_BUF_COUNT+StartI); I++)
    {
        TempI = I%UART_BUF_COUNT;
        if((DMABuf->BufDma[TempI].Len) == 0)
        {
            Idx = TempI;
            DMABuf->IdxFree = Idx;
            break;
        }
    }

    return Idx;
}

static qapi_Status_t UART_HandleTx(UART_HwCtxt_t *HwCtxt)
{
    QUP_XferCtxt_t *XferCtxt = HwCtxt->XferCtxt;
    uint16_t XmitSize;
    qapi_Status_t Status = QAPI_OK;

    if(XferCtxt->TxBusy)
    {
        return QAPI_UART_ERROR_TRANSMIT_BUSY;
    }

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        UART_BufDMA_t* UartTxBuf = &(UART_XferBufs[HwCtxt->Instance].TxBuf.TxDMABuf);
        int8_t Idx2Tx = UartTxBuf->IdxTrans;
        XmitSize = UartTxBuf->BufDma[Idx2Tx].Len;

        if (!XmitSize)
        {
            UART_BUF_IDX_INC(Idx2Tx);
            XmitSize = UartTxBuf->BufDma[Idx2Tx].Len;
            if(!XmitSize)
            {
                return QAPI_UART_ERROR_NO_DATA_TO_TRANSFER;
            }
        }
        XferCtxt->TxBuf = UartTxBuf->BufDma[Idx2Tx].Buf;
        XferCtxt->TxLen = XmitSize;
        UartTxBuf->IdxTrans = Idx2Tx;
    }
    else
    {
        QUP_CircBuf_t *CircBuf = &(UART_XferBufs[HwCtxt->Instance].TxBuf.TxCircBuf);
        HwCtxt->XferCtxt->TxCircBuf = CircBuf;

        XmitSize = QUP_CIRC_CNT(CircBuf->Head, CircBuf->Tail, HwCtxt->TxBufSize);

        if(XmitSize > (HwCtxt->TxBufSize - CircBuf->Tail))
        {
            XmitSize = HwCtxt->TxBufSize- CircBuf->Tail;
        }
        if (!XmitSize)
        {
            return QAPI_UART_ERROR_NO_DATA_TO_TRANSFER;
        }

        if(HwCtxt->BusType == QUP_BUS_UART_9BIT_SW && (XmitSize%2))
        {
            XmitSize = XmitSize - 1;
        }

        XferCtxt->TxLen = XmitSize;
    }
    /* set TX buf & size to QUP, QUP will send data out */
    XferCtxt->CmdOpcode = UART_OPCODE_TX;
    Status = QUP_UartStartTx((QUP_Instance_t)HwCtxt->Instance, XferCtxt);

    return Status;
}

static qapi_Status_t UART_HandleRx(UART_HwCtxt_t *HwCtxt)
{
    qapi_Status_t Status = QAPI_OK;
    QUP_XferCtxt_t *XferCtxt = HwCtxt->XferCtxt;

    if(HwCtxt->BusType == QUP_BUS_UART_9BIT_HW && XferCtxt->XferInfo.Uart.RxAddress == 0)
    {
        return QAPI_UART_ERROR_INVALID_PARAM;
    }

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        int8_t IdxFree;
        IdxFree = UART_GetFreeBufIdx(&(UART_XferBufs[HwCtxt->Instance].RxBuf.RxDMABuf));
        if(IdxFree < 0)
        {
            UART_XferBufs[HwCtxt->Instance].RxBufStarving = 1;
            /* no available buffer now, the rx buffer will be provided in qapi_Uart_Receive.*/
            return QAPI_UART_ERROR_NO_AVAILABLE_BUF;
        }
        else
        {
            UART_XferBufs[HwCtxt->Instance].RxBufStarving = 0;
            XferCtxt->RxBuf = UART_XferBufs[HwCtxt->Instance].RxBuf.RxDMABuf.BufDma[IdxFree].Buf;
            XferCtxt->RxLen = HwCtxt->RxBufSize;
        }
    }
    else
    {
        QUP_CircBuf_t *CircBuf = &(UART_XferBufs[HwCtxt->Instance].RxBuf.RxCircBuf);
        uint16_t FreeSize = 0;

        FreeSize = QUP_CIRC_SPACE(CircBuf->Head, CircBuf->Tail, HwCtxt->RxBufSize);
        if(FreeSize < 4)
        {
            UART_XferBufs[HwCtxt->Instance].RxBufStarving = 1;
            /* no available buffer now, the rx buffer will be provided in qapi_Uart_Receive.
               need disable the fifo wm and stale interrupts */
            QUP_UartClearRxIrq((QUP_Instance_t)(HwCtxt->Instance));
            HwCtxt->XferCtxt->RxLen = 0;
            return QAPI_UART_ERROR_NO_AVAILABLE_BUF;
        }
        UART_XferBufs[HwCtxt->Instance].RxBufStarving = 0;
        HwCtxt->XferCtxt->RxLen = FreeSize;
        HwCtxt->XferCtxt->RxCircBuf = CircBuf;
    }

    HwCtxt->XferCtxt->SCmdOpcode = UART_OPCODE_RX;

    Status = QUP_UartStartRx((QUP_Instance_t)HwCtxt->Instance, XferCtxt);

    return Status;
}

static void UART_GeniRxCallback(uint32_t Status, void *CallbackCtxt)
{
    UART_HwCtxt_t *HwCtxt = (UART_HwCtxt_t *)CallbackCtxt;
    QUP_XferCtxt_t *XferCtxt = HwCtxt->XferCtxt;
    UART_BufDMA_t* UartRxBuf;
    int8_t IdxUsing = -1;

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        UartRxBuf = &(UART_XferBufs[HwCtxt->Instance].RxBuf.RxDMABuf);
        IdxUsing = UartRxBuf->IdxFree;

        if(!UART_IN_RANG(IdxUsing, 0 , 1))
        {
            Qup_AssertFunc();
        }
        UartRxBuf->BufDma[IdxUsing].Len = XferCtxt->RxCnt;
    }
    else if(Status == QUP_ERROR_RX_FIFO_RX_UNDER_READ)
    {
        goto callback;
    }
    UART_HandleRx(HwCtxt);

callback:
    HwCtxt->RxCbFunc(UART_ErrorMap(Status), XferCtxt->RxCnt, HwCtxt->CbCtxt);
    XferCtxt->RxCnt = 0;
}

static void UART_GeniTxCallback(uint32_t Status, void *CallbackCtxt)
{
    UART_HwCtxt_t *HwCtxt = (UART_HwCtxt_t *)CallbackCtxt;
    QUP_XferCtxt_t *XferCtxt = HwCtxt->XferCtxt;

    if(HwCtxt->XferMode == QUP_XFER_DMA)
    {
        UART_BufDMA_t* UartTxBuf = &(UART_XferBufs[HwCtxt->Instance].TxBuf.TxDMABuf);
        int8_t IdxUsing = UartTxBuf->IdxTrans;

        if(!UART_IN_RANG(IdxUsing, 0 , 1))
        {
            Qup_AssertFunc();
        }
        UartTxBuf->BufDma[IdxUsing].Len = 0;
    }
    else
    {
        if(HwCtxt->XferCtxt->TxCircBuf->Head == HwCtxt->XferCtxt->TxCircBuf->Tail)
        {
            HwCtxt->XferCtxt->TxCircBuf->Head = HwCtxt->XferCtxt->TxCircBuf->Tail = 0;
        }
    }

    HwCtxt->TxRemaining -= XferCtxt->TxedLen;

    UART_HandleTx(HwCtxt);

	if(HwCtxt->TxCbFunc)
    {
	    HwCtxt->TxCbFunc(UART_ErrorMap(Status), XferCtxt->TxedLen, HwCtxt->CbCtxt);
    }
}

#endif

