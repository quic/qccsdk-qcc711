/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>
#include "qcc710.h"
#include "core_cm3.h"
#include "hwio_tlmm.h"
#include "qapi_timer.h"
#include "qup_api.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QUP_POLL_TIME_DEFAULT_US    4096000
#define QUP_CANCEL_TIME_DEFAULT_US  100000
#define QUP_POLL_INTERVAL_US        5
#define QUP_BITS_IN_BYTE            8
#define QUP_TASK_EVENT              1

#define QUP_FIFO_M_ERROR_MASK (FLD_SET(SE0_GENI_M_IRQ_STATUS, RX_FIFO_RD_ERR, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, RX_FIFO_WR_ERR, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, TX_FIFO_RD_ERR, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, TX_FIFO_WR_ERR, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, M_CMD_OVERRUN, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, M_CMD_CANCEL, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, M_CMD_ABORT, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, M_ILLEGAL_CMD, 1) |\
                               FLD_SET(SE0_GENI_M_IRQ_STATUS, M_CMD_FAILURE, 1))

#define QUP_FIFO_S_ERROR_MASK  (FLD_SET(SE0_GENI_S_IRQ_STATUS, RX_FIFO_RD_ERR, 1) |\
                                FLD_SET(SE0_GENI_S_IRQ_STATUS, S_CMD_OVERRUN, 1) |\
                                FLD_SET(SE0_GENI_S_IRQ_STATUS, S_CMD_CANCEL, 1) |\
                                FLD_SET(SE0_GENI_S_IRQ_STATUS, S_CMD_ABORT, 1) |\
                                FLD_SET(SE0_GENI_S_IRQ_STATUS, S_ILLEGAL_CMD, 1) |\
                                FLD_SET(SE0_GENI_S_IRQ_STATUS, S_CMD_FAILURE, 1))

#define QUP_DMA_TX_ERROR_MASK  (FLD_SET(SE0_DMA_TX_IRQ_STAT, SBE, 1) |\
                                FLD_SET(SE0_DMA_TX_IRQ_STAT, GENI_CMD_FAILURE, 1) |\
                                FLD_SET(SE0_DMA_TX_IRQ_STAT, GENI_CANCEL_IRQ, 1) |\
                                FLD_SET(SE0_DMA_TX_IRQ_STAT, RESET_DONE, 1))

#define QUP_DMA_RX_ERROR_MASK  (FLD_SET(SE0_DMA_RX_IRQ_STAT, SBE, 1) |\
                                FLD_SET(SE0_DMA_RX_IRQ_STAT, GENI_CMD_FAILURE, 1) |\
                                FLD_SET(SE0_DMA_RX_IRQ_STAT, GENI_CANCEL_IRQ, 1) |\
                                FLD_SET(SE0_DMA_RX_IRQ_STAT, RESET_DONE, 1))

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

QUP_BusCtxt_t *QUP_BusCtxt[QUP_INSTANCE_MAX];

const QUP_HwInfo_t QUP_HwInfo[QUP_INSTANCE_MAX] = {
    {
        .CommonBase = PERIPH_QUPV3_COMMON_REG_BASE,
        .SeCoreBase = PERIPH_SE0_REG_BASE,
        .CoreFastClk = 32000000,    /* 32MHz */
        .CoreSlowClk = 32000,       /* 32KHz */
        .GeniSeMode = QUP_GENI_SE_FW,
        .BusMask = (BIT(QUP_BUS_SPI_MASTER_3WIRE_9BIT) | BIT(QUP_BUS_SPI_MASTER_4WIRE_8BIT) |
                    BIT(QUP_BUS_SPI_MASTER) | BIT(QUP_BUS_SPI_SLAVE) | BIT(QUP_BUS_I2C_MASTER) |
                    BIT(QUP_BUS_UART) | BIT(QUP_BUS_UART_9BIT_SW) | BIT(QUP_BUS_UART_9BIT_HW) |
                    BIT(QUP_BUS_UART_TX_INVERT)),
    },
    {
        .CommonBase = PERIPH_QUPV3_COMMON_REG_BASE,
        .SeCoreBase = PERIPH_SE1_REG_BASE,
        .CoreFastClk = 32000000,    /* 32MHz */
        .CoreSlowClk = 32000,       /* 32KHz */
        .GeniSeMode = QUP_GENI_SE_FW,
        .BusMask = (BIT(QUP_BUS_SPI_MASTER_3WIRE_9BIT) | BIT(QUP_BUS_SPI_MASTER_4WIRE_8BIT) |
                    BIT(QUP_BUS_SPI_MASTER) | BIT(QUP_BUS_SPI_SLAVE) | BIT(QUP_BUS_I2C_MASTER) |
                    BIT(QUP_BUS_UART) | BIT(QUP_BUS_UART_9BIT_SW) | BIT(QUP_BUS_UART_9BIT_HW) |
                    BIT(QUP_BUS_UART_TX_INVERT)),
    },
    {
        .CommonBase = PERIPH_QUPV3_COMMON_REG_BASE,
        .SeCoreBase = PERIPH_SE2_REG_BASE,
        .CoreFastClk = 32000000,    /* 32MHz */
        .CoreSlowClk = 32000,       /* 32KHz */
        .GeniSeMode = QUP_GENI_SE_MINICORE,
        .BusMask = (BIT(QUP_BUS_I2C_MASTER) | BIT(QUP_BUS_UART) | BIT(QUP_BUS_M2MDMA)),
    },
    {
        .CommonBase = PERIPH_QUPV3_COMMON_REG_BASE,
        .SeCoreBase = PERIPH_SE3_REG_BASE,
        .CoreFastClk = 32000000,    /* 32MHz */
        .CoreSlowClk = 32000,       /* 32KHz */
        .GeniSeMode = QUP_GENI_SE_MINICORE,
        .BusMask = (BIT(QUP_BUS_I2C_MASTER) | BIT(QUP_BUS_M2MDMA)),
    }
};

uint32_t Qup_AssertLoop = 0;
uint32_t Qup_ClkEn = 0;
/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

static void QUP_BusWriteToFifo(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t I = 0;
    uint32_t BytesToWrite = XferCtxt->TxLen - XferCtxt->TxCnt;
    uint8_t TxFifoWidth = BusCtxt->TxFifoWidth >> 3;
    uint32_t UnsentFifoEntries = REG_INF(SeCoreBase + GENI4_DATA_REG_BASE,
                               SE0_GENI_TX_FIFO_STATUS, TX_FIFO_WC);

    uint32_t FreeFifoEntries = (BusCtxt->TxFifoDepth - UnsentFifoEntries) * TxFifoWidth;
    BytesToWrite = BytesToWrite > FreeFifoEntries ? FreeFifoEntries : BytesToWrite;

    while (I < BytesToWrite)
    {
        uint32_t J;
        volatile uint32_t Data;
        uint8_t *FifoByte = (uint8_t *)&Data;

        for (J = 0, Data = 0; J < TxFifoWidth && I < BytesToWrite; J++)
        {
            FifoByte[J] = XferCtxt->TxBuf[I++];
        }

        REG_OUTI(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_FIFOn, 0, Data);
    }

    XferCtxt->TxBuf += BytesToWrite;
    XferCtxt->TxCnt += BytesToWrite;

    if (XferCtxt->TxCnt == XferCtxt->TxLen)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_WATERMARK_REG,
            FLD_SET(SE0_GENI_TX_WATERMARK_REG, TX_WATERMARK, 0));
    }
}

static void QUP_BusReadFromFifo(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t Word, I;
    uint8_t BytesInLastWord;
    uint32_t RxFifoStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFO_STATUS);
    uint32_t ValidFifoBytes = FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_FIFO_WC) << 2;
    uint32_t BytesToRead = XferCtxt->RxLen - XferCtxt->RxCnt;

    if (FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_LAST))
    {
        BytesInLastWord = FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_LAST_BYTE_VALID);
        if(BytesInLastWord != 0)
        {
            ValidFifoBytes = (ValidFifoBytes - 4) + BytesInLastWord;
        }
    }

    BytesToRead = BytesToRead > ValidFifoBytes ? ValidFifoBytes : BytesToRead;

    for (I = 0; I < BytesToRead; I++)
    {
        if ((I & 0x3) == 0)
        {
            Word = REG_INI(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFOn, 0);
        }

        /* workaround for SPI slave to flush the RX FIFO when XferCtxt->RxBuf is null */
        if (XferCtxt->RxBuf)
        {
            XferCtxt->RxBuf[XferCtxt->RxCnt++] = (Word >> ((I & 0x3) << 3)) & 0xFF;
        }
    }

    if((XferCtxt->RxCnt == XferCtxt->RxLen) && XferCtxt->RxBuf && XferCtxt->TxBuf)
    {
        if(BusCtxt->BusType == QUP_BUS_SPI_MASTER_3WIRE_9BIT || 
            BusCtxt->BusType == QUP_BUS_SPI_MASTER_4WIRE_8BIT)
        {
            /* the operation will set CS idle after operation is done */
            /* start bus command execution */
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_CMD0,
                FLD_SET(SE0_GENI_M_CMD0, OPCODE, 9) /* |
                FLD_SET(SE0_GENI_M_CMD0, PARAM, CmdParam)*/);
        }
    }
}

/**
   @brief Prepare The Serial Engine for DMA Receiving.

   @param[in] SeBaseAddr    The Configured Serial Engine Register Base Adddress
   @param[in/out] RxBuf     Pointer to the RX buffer.
   @param[in] RxLen         Length of the RX buffer.
*/
static void QUP_RxDmaPrepare(uint32_t SeCoreBase, void *RxBuf, uint32_t RxLen)
{
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_L, QUP_SRAM_MAP_TO_DMA(RxBuf));
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_H, 0);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_ATTR, 0);

    __DSB();
    __ISB();
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_LENGTH, RxLen);
}

/**
   @brief Prepare The Serial Engine for DMA Transmitting.

   @param[in] SeCoreBase    The Configured Serial Engine Register Base Adddress
   @param[in] TxBuf         Pointer to the TX buffer.
   @param[in] TxLen         Length of the TX buffer.
*/
static void QUP_TxDmaPrepare(uint32_t SeCoreBase, void *TxBuf, uint32_t TxLen)
{
    if (QUP_ADDRESS_SRAM_RANGE(TxBuf))
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_L, QUP_SRAM_MAP_TO_DMA(TxBuf));
    else
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_L, TxBuf);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_H, 0);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_ATTR, 1);

    __DSB();
    __ISB();
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_LENGTH, TxLen);
}

/**
   @brief Reset DMA

   @param[in] Instance      Serial Engine index specified by #QUP_Instance_t
   @param[in] Tx            DMA TX, 1: TX, 0: RX.
*/
void QUP_DmaFsmReset(QUP_Instance_t Instance, qbool_t Tx)
{
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    uint32_t TimeoutUs = QUP_POLL_TIME_DEFAULT_US;

    NVIC_DisableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance));

    if (Tx)
    {
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_FSM_RST, 1);

        while (TimeoutUs != 0)
        {
            if (REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_STAT, RESET_DONE))
            {
                break;
            }
            qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
            TimeoutUs -= QUP_POLL_INTERVAL_US;
        }
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_L, 0);
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_H, 0);
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_ATTR, 0);
    }
    else
    {
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_FSM_RST, 1);

        while (TimeoutUs != 0)
        {
            if (REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_STAT, RESET_DONE))
            {
                break;
            }
            qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
            TimeoutUs -= QUP_POLL_INTERVAL_US;
        }
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_L, 0);
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_H, 0);
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_ATTR, 0);
    }
}

void QUP_RxFiFoFlush(QUP_Instance_t Instance)
{
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    uint32_t RxFifoStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFO_STATUS);

    while(RxFifoStatus)
    {
        /* Flush FIFO with read only, assign the value to RxFifoStatus to avoid build warning */
        RxFifoStatus = REG_INI(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFOn, 0);
        RxFifoStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFO_STATUS);
    }
}

static void QUP_StartMCmd(uint32_t SeCoreBase, uint32_t CmdOpcode, uint32_t CmdParam)
{
    __DSB();
    __ISB();

    /* start bus command execution */
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_CMD0,
        FLD_SET(SE0_GENI_M_CMD0, OPCODE, CmdOpcode) |
        FLD_SET(SE0_GENI_M_CMD0, PARAM, CmdParam));
}

static void QUP_StartSCmd(uint32_t SeCoreBase, uint32_t SCmdOpcode, uint32_t SCmdParam)
{
    __DSB();
    __ISB();

    /* start bus command execution */
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_CMD0,
        FLD_SET(SE0_GENI_S_CMD0, OPCODE, SCmdOpcode) |
        FLD_SET(SE0_GENI_S_CMD0, PARAM, SCmdParam));
}

static void QUP_BusFreqUpdate(uint32_t SeCoreBase, uint32_t DfsIndex, uint32_t ClkDiv)
{
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CLK_SEL,
        FLD_SET(SE0_GENI_CLK_SEL, CLK_SEL, DfsIndex));

    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_SER_M_CLK_CFG,
        FLD_SET(SE0_GENI_SER_M_CLK_CFG, CLK_DIV_VALUE, ClkDiv) |
        FLD_SET(SE0_GENI_SER_M_CLK_CFG, SER_CLK_EN, 1));
}

static void QUP_GeniSeIrqClear(uint32_t SeCoreBase)
{
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_CLR, 0xffffffff);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_CLR, 0xffffffff);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_CLEAR, 0xffffffff);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_CLEAR, 0xffffffff);
}

static void QUP_GeniSeIrqEnClear(uint32_t SeCoreBase)
{
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_IRQ_EN, 0x0);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_EN_CLR, 0xffffffff);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_EN_CLR, 0xffffffff);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_CLEAR, 0xffffffff);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_EN_CLEAR, 0xffffffff);
}

static void QUP_GeniSeClkSet(uint32_t SeCoreBase, QUP_XferMode_t XferMode, qbool_t On)
{
    /* SE DMA initialization */
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_GENERAL_CFG,
        FLD_SET(SE0_DMA_GENERAL_CFG, AHB_SEC_SLV_CLK_CGC_ON, On) |
        FLD_SET(SE0_DMA_GENERAL_CFG, DMA_AHB_SLV_CLK_CGC_ON, On) |
        FLD_SET(SE0_DMA_GENERAL_CFG, DMA_TX_CLK_CGC_ON, On) |
        FLD_SET(SE0_DMA_GENERAL_CFG, DMA_RX_CLK_CGC_ON, On));

    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL,
        FLD_SET(SE0_GENI_CGC_CTRL, EXT_CLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, RX_CLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, TX_CLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, SCLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, DATA_AHB_CLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, CFG_AHB_WR_CLK_CGC_ON, On) |
        FLD_SET(SE0_GENI_CGC_CTRL, CFG_AHB_CLK_CGC_ON, On));
}

static void QUP_GeniSeIrqEnSet(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt)
{
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_IRQ_EN,
        FLD_SET(SE0_SE_IRQ_EN, GENI_M_IRQ_EN, 1) |
        FLD_SET(SE0_SE_IRQ_EN, DMA_TX_IRQ_EN, 1) |
        FLD_SET(SE0_SE_IRQ_EN, DMA_RX_IRQ_EN, 1));

    /* Enable GENI interrupts for all modes */
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
	    FLD_SET(SE0_GENI_M_IRQ_EN_SET, SEC_IRQ_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_OVERRUN_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_ILLEGAL_CMD_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_FAILURE_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_CANCEL_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_ABORT_EN_SET, 1) |
#if 0
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_TIMESTAMP_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, IO_DATA_ASSERT_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, IO_DATA_DEASSERT_EN_SET, 1) |
#endif
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_WR_ERR_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_RD_ERR_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, TX_FIFO_WR_ERR_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, TX_FIFO_RD_ERR_EN_SET, 1));

#if 0
    if (BusCtxt->BusType == QUP_BUS_I2C_MASTER)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
            FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_GP_IRQ_1_EN_SET, 1) |
            FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_GP_IRQ_3_EN_SET, 1) |
            FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_GP_IRQ_4_EN_SET, 1));
    }
#endif

    if (BusCtxt->IsUart)
    {
        REG_OUTF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_IRQ_EN, GENI_S_IRQ_EN, 1);

        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_EN_SET,
            //FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_CMD_OVERRUN_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_ILLEGAL_CMD_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_CMD_FAILURE_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_CMD_CANCEL_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_CMD_ABORT_EN_SET, 1) |
#if 0
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_GP_IRQ_0_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_GP_IRQ_1_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_GP_IRQ_2_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_GP_IRQ_3_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, S_GP_IRQ_4_EN_SET, 1) |
#endif
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_WR_ERR_EN_SET, 1) |
            FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_RD_ERR_EN_SET, 1));
    }

    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_EN_SET,
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, GENI_CMD_FAILURE_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, GENI_CANCEL_IRQ_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, RESET_DONE_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, SBE_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, DMA_DONE_EN_SET, 1));

        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_EN_SET,
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, GENI_CMD_FAILURE_EN_SET, 1) |
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, GENI_CANCEL_IRQ_EN_SET, 1) |
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, FLUSH_DONE_EN_SET, 1) |
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, RESET_DONE_EN_SET, 1) |
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, SBE_EN_SET, 1) |
            FLD_SET(SE0_DMA_RX_IRQ_EN_SET, DMA_DONE_EN_SET, 1));
    }
    else /* FIFO */
    {
        if (BusCtxt->IsUart)
        {
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_EN_SET,
                FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_WATERMARK_EN_SET, 1) |
                FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_LAST_EN_SET, 1));

            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_WATERMARK_EN_SET, 1) |
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_LAST_EN_SET, 1) |
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_DONE_EN_SET, 1));
        }
		else
        {
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_WATERMARK_EN_SET, 1) |
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, TX_FIFO_WATERMARK_EN_SET, 1) |
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_LAST_EN_SET, 1) |
                FLD_SET(SE0_GENI_M_IRQ_EN_SET, M_CMD_DONE_EN_SET, 1));
        }
    }
}

/**
   @brief Set the Packing Configuration of the Serial Engine

   @param[in] SeCoreBase    The Configured Serial Engine Register Base Adddress.
   @param[in] PackConfig    The Packing Configuration Array.
*/
static void QUP_BusPackingConfig(uint32_t SeCoreBase, QUP_PackingConfig_t *PackingConfig)
{
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE , SE0_GENI_TX_PACKING_CFG0,
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_1_START_INDEX, PackingConfig[1].Start) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_1_DIRECTION, PackingConfig[1].Direction) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_1_LENGTH, PackingConfig[1].Length) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_1_STOP, PackingConfig[1].Stop) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_0_START_INDEX, PackingConfig[0].Start) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_0_DIRECTION, PackingConfig[0].Direction) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_0_LENGTH, PackingConfig[0].Length) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG0, VEC_0_STOP, PackingConfig[0].Stop));

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE , SE0_GENI_TX_PACKING_CFG1,
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_3_START_INDEX, PackingConfig[3].Start) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_3_DIRECTION, PackingConfig[3].Direction) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_3_LENGTH, PackingConfig[3].Length) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_3_STOP, PackingConfig[3].Stop) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_2_START_INDEX, PackingConfig[2].Start) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_2_DIRECTION, PackingConfig[2].Direction) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_2_LENGTH, PackingConfig[2].Length) |
        FLD_SET(SE0_GENI_TX_PACKING_CFG1, VEC_2_STOP, PackingConfig[2].Stop));

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE , SE0_GENI_RX_PACKING_CFG0,
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_1_START_INDEX, PackingConfig[1].Start) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_1_DIRECTION, PackingConfig[1].Direction) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_1_LENGTH, PackingConfig[1].Length) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_1_STOP, PackingConfig[1].Stop) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_0_START_INDEX, PackingConfig[0].Start) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_0_DIRECTION, PackingConfig[0].Direction) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_0_LENGTH, PackingConfig[0].Length) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG0, VEC_0_STOP, PackingConfig[0].Stop));

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE , SE0_GENI_RX_PACKING_CFG1,
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_3_START_INDEX, PackingConfig[3].Start) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_3_DIRECTION, PackingConfig[3].Direction) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_3_LENGTH, PackingConfig[3].Length) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_3_STOP, PackingConfig[3].Stop) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_2_START_INDEX, PackingConfig[2].Start) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_2_DIRECTION, PackingConfig[2].Direction) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_2_LENGTH, PackingConfig[2].Length) |
        FLD_SET(SE0_GENI_RX_PACKING_CFG1, VEC_2_STOP, PackingConfig[2].Stop));
}

static void QUP_GetPackingConfig(uint32_t PackWords, uint32_t BitsPerWord, qbool_t MsbFirst,
                                 QUP_PackingConfig_t *PackingConfig)
{
    int32_t Ws = BitsPerWord;
    int32_t CWs = 0;
    int32_t RunUpWs = 0;
    int32_t Iter = 0;
    int32_t I, Idx, StartIdx;

    RunUpWs = (Ws & (QUP_BITS_IN_BYTE - 1)) ?
        ((Ws & ~(QUP_BITS_IN_BYTE - 1)) + QUP_BITS_IN_BYTE) : Ws;

    Iter = (RunUpWs * PackWords) >> 3;
    if (Iter > QUP_PACKING_CONFIG_NUM)
    {
        memset(PackingConfig, 0, sizeof(*PackingConfig) * QUP_PACKING_CONFIG_NUM);
        return;
    }

    StartIdx = MsbFirst ? (Ws - 1) : 0;
    Idx = StartIdx;
    CWs = Ws;

    for (I = 0; I < Iter; I++)
    {
        PackingConfig[I].Start = Idx;
        PackingConfig[I].Direction = MsbFirst;
        PackingConfig[I].Length = (CWs > QUP_BITS_IN_BYTE) ? (QUP_BITS_IN_BYTE - 1) : (CWs - 1);
        PackingConfig[I].Stop = 0;

        Idx = ((CWs - QUP_BITS_IN_BYTE) <= 0) ? ((I + 1) * QUP_BITS_IN_BYTE) + StartIdx :
                (MsbFirst ? Idx - QUP_BITS_IN_BYTE : Idx + QUP_BITS_IN_BYTE);

        CWs = ((CWs - QUP_BITS_IN_BYTE) <= 0) ? Ws : (CWs - QUP_BITS_IN_BYTE);
    }

    PackingConfig[I - 1].Stop = 1;
}

#ifdef ENABLE_PERIPHERAL_SPI
static QUP_Status_t QUP_SpiGpioCheck(QUP_Instance_t Instance, QUP_BusConfig_t *BusConfig)
{
    uint32_t Function;
    uint32_t GpioId;

    /* only check for SPI Master/Slave 3wires/4wires */
    if (BusConfig->BusType < QUP_BUS_I2C_MASTER)
    {
        for (GpioId=0; GpioId<26; GpioId++)
        {
            Function = HWIO_TLMM_GPIO_CFGm_INMI(GpioId, HWIO_TLMM_GPIO_CFGm_FUNC_SEL_BMSK)
                    >> HWIO_TLMM_GPIO_CFGm_FUNC_SEL_SHFT;
            /* SE0 will be mapped to the north side of the chip on GPIO 4, 5, 6, 7 & 8 */
            if ((Instance == QUP_INSTANCE_0) && (Function == 1))
            {
                if ((GpioId < 4) || (GpioId > 8))
                {
                    return QUP_ERROR_BUS_GPIO_ENABLE_FAIL;
                }
            }
            /* SE1 will be mapped to the south side of the chip on GPIO 16, 17, 18, 19 & 20 */
            else if ((Instance == QUP_INSTANCE_1) && (Function == 3))
            {
                if ((GpioId < 16) || (GpioId > 20))
                {
                    return QUP_ERROR_BUS_GPIO_ENABLE_FAIL;
                }
            }
        }
    }

    return QUP_SUCCESS;
}

static void QUP_SpiXferConfig(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint16_t CsPolarity;
    QUP_SpiXferInfo_t *SpiXferInfo = &XferCtxt->XferInfo.Spi;
    QUP_PackingConfig_t PackingConfig[QUP_PACKING_CONFIG_NUM];
    qbool_t MsbFirst = true;
    uint32_t PackWords, BitsPerWord, OldBitsPerWord, Granularity, BytesPerEntry;
    uint32_t TxWaterMark = XferCtxt->TxWaterMark;

    if (BusCtxt->BusType == QUP_BUS_SPI_SLAVE)
    {
        BitsPerWord = SpiXferInfo->Slave.BitsPerWord;
        OldBitsPerWord = REG_IN(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_SLAVE_WORD_LEN);

        if (BitsPerWord != OldBitsPerWord)
        {
            MsbFirst = !(SpiXferInfo->Slave.LsbFirst);
            REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_SLAVE_WORD_LEN, BitsPerWord);
        }

        if (XferCtxt->TxBuf)
        {
            TxWaterMark = BusCtxt->TxFifoDepth >> 1;
        }
    }
    else
    {
        QUP_SpiMXferInfo_t *MXferInfo = &SpiXferInfo->Master;

        if (XferCtxt->ClkChanged)
        {
            uint32_t CoreClk, ClkDiv, Instance = BusCtxt->Instance;
            uint32_t SclkSel;

            qapi_TSK_Enter_Critical();
            SclkSel = REG_INF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_SEL);
            if (MXferInfo->FreqHz >= QUP_HwInfo[Instance].CoreSlowClk)
            {
                /* QUP core fast clock */
                CoreClk = QUP_HwInfo[Instance].CoreFastClk;
                SclkSel &= ~BIT(Instance);

                REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_SEL, SclkSel);
            }
            else
            {
                /* QUP core slow clock */
                CoreClk = QUP_HwInfo[Instance].CoreSlowClk;
                SclkSel |= BIT(Instance);

                REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_SEL, SclkSel);
            }
            qapi_TSK_Exit_Critical();

            ClkDiv = CoreClk / MXferInfo->FreqHz;
            QUP_BusFreqUpdate(SeCoreBase, 0, ClkDiv);
        }

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_CPHA,
            FLD_SET(SE0_SPI_CPHA, CPHA, !!(MXferInfo->Flags & QUP_SPI_XFER_CPHA)));
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_CPOL,
            FLD_SET(SE0_SPI_CPOL, CPOL, !!(MXferInfo->Flags & QUP_SPI_XFER_CPOL)));

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_LOOPBACK_CFG,
            FLD_SET(SE0_SPI_LOOPBACK_CFG, LOOPBACK_MODE, !!(MXferInfo->Flags & QUP_SPI_XFER_LOOPBACK)));

		if (MXferInfo->Flags & QUP_SPI_XFER_MUL_CS) {
			uint8_t cs1, cs2;
			cs1 = MXferInfo->CsLine & 0x01? 0x03:0x0;
			cs2 = MXferInfo->CsLine & 0x02? 0x03:0x0;

			REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG80,
					 IO_MACRO_IO0_SEL, cs2);

			REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG80,
					IO_MACRO_IO3_SEL, cs1);

			REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CFG_SEQ_START,
				FLD_SET(SE0_GENI_CFG_SEQ_START, START_TRIGGER, 1));
		}
	   	else 
		{
			REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_DEMUX_SEL,
				FLD_SET(SE0_SPI_DEMUX_SEL, CS_DEMUX_SEL, MXferInfo->CsLine));
			
			if (BusCtxt->BusType == QUP_BUS_SPI_MASTER_3WIRE_9BIT || 
				BusCtxt->BusType == QUP_BUS_SPI_MASTER_4WIRE_8BIT)
			{
				REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_DEMUX_SEL, CS_DEMUX_FW_EN, 1);
			}
		}
		

        CsPolarity = ((!!(MXferInfo->Flags & QUP_SPI_XFER_CSPOLARITY)) << MXferInfo->CsLine) &
            FLD_BMSK(SE0_SPI_DEMUX_OUTPUT_INV, CS_DEMUX_OUTPUT_INV);
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_DEMUX_OUTPUT_INV,
            FLD_SET(SE0_SPI_DEMUX_OUTPUT_INV, CS_DEMUX_OUTPUT_INV, CsPolarity));

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_TRANS_CFG,
            FLD_SET(SE0_SPI_TRANS_CFG, SPI_CS_TOGGLE, !!(MXferInfo->Flags & QUP_SPI_XFER_CSTOGGLE)));

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_DELAYS_COUNTERS,
            FLD_SET(SE0_SPI_DELAYS_COUNTERS, SPI_CS_CLK_DLY, MXferInfo->CsClkDelay) |
            FLD_SET(SE0_SPI_DELAYS_COUNTERS, SPI_INTER_WORDS_DLY, MXferInfo->InterWordDelay));

        BitsPerWord = MXferInfo->BitsPerWord;
        OldBitsPerWord = REG_INF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_WORD_LEN, SPI_WORD_LEN);
        if (BitsPerWord != OldBitsPerWord)
        {
            REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_WORD_LEN,
                FLD_SET(SE0_SPI_WORD_LEN, SPI_WORD_LEN, (BitsPerWord - 4)));
            MsbFirst = !(MXferInfo->Flags & QUP_SPI_XFER_LSB_FIRST);
        }
    }

    if (BitsPerWord <= 8)
    {
        /* packing_mode: 4x8 */
        Granularity = QUP_BYTE_GRANULARITY_4x8;
        PackWords = 4;
        BytesPerEntry = 1;
    }
    else if (BitsPerWord <= 16)
    {
        /* packing_mode: 2x16 */
        Granularity = QUP_BYTE_GRANULARITY_2x16;
        PackWords = 2;
        BytesPerEntry = 2;
    }
    else
    {
        /* packing_mode: 1x32 */
        Granularity = QUP_BYTE_GRANULARITY_1x32;
        PackWords = 1;
        BytesPerEntry = 4;
    }

    if (BitsPerWord != OldBitsPerWord)
    {
        QUP_GetPackingConfig(PackWords, BitsPerWord, MsbFirst, PackingConfig);
        QUP_BusPackingConfig(SeCoreBase, PackingConfig);
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_BYTE_GRANULARITY, Granularity);
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_RX_BYTE_GRANULARITY, Granularity);
    }

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_RX_TRANS_LEN, XferCtxt->RxLen / BytesPerEntry);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_TX_TRANS_LEN, XferCtxt->TxLen / BytesPerEntry);

    if (BusCtxt->XferMode == QUP_XFER_FIFO)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_WATERMARK_REG,
            FLD_SET(SE0_GENI_TX_WATERMARK_REG, TX_WATERMARK, TxWaterMark));
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_WATERMARK_REG,
            FLD_SET(SE0_GENI_RX_WATERMARK_REG, RX_WATERMARK, XferCtxt->RxWaterMark));
    }

    if (BusCtxt->BusType == QUP_BUS_SPI_SLAVE)
    {
    	QUP_StartMCmd(SeCoreBase, XferCtxt->CmdOpcode, XferCtxt->CmdParam);

        if (XferCtxt->TxBuf && BusCtxt->XferMode == QUP_XFER_FIFO)
        {
            QUP_BusWriteToFifo(SeCoreBase, BusCtxt, XferCtxt);
        }
    }
}
#endif

#ifdef ENABLE_PERIPHERAL_I2C
static void QUP_I2cXferConfig(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    QUP_I2cXferInfo_t          *I2cXferCtxt = &(XferCtxt->XferInfo.I2c);
    uint32_t CoreSlowClk = QUP_HwInfo[BusCtxt->Instance].CoreSlowClk;

    if (BusCtxt->XferMode == QUP_XFER_FIFO)
    {
        if (XferCtxt->TxLen > 0)
        {
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_WATERMARK_REG,
                FLD_SET(SE0_GENI_TX_WATERMARK_REG, TX_WATERMARK, XferCtxt->TxWaterMark));
        }
        else if (XferCtxt->RxLen > 0)
        {
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_WATERMARK_REG,
                FLD_SET(SE0_GENI_RX_WATERMARK_REG, RX_WATERMARK, XferCtxt->RxWaterMark));

            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_RFR_WATERMARK_REG,
                FLD_SET(SE0_GENI_RX_RFR_WATERMARK_REG, RX_RFR_WATERMARK, (BusCtxt->RxFifoDepth - 2)));
         }
    }

    /* scl waveform conditioning */
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_I2C_SCL_COUNTERS,
        FLD_SET(SE0_I2C_SCL_COUNTERS, I2C_SCL_HIGH_COUNTER, I2cXferCtxt->THigh) |
        FLD_SET(SE0_I2C_SCL_COUNTERS, I2C_SCL_LOW_COUNTER, I2cXferCtxt->TLow)   |
        FLD_SET(SE0_I2C_SCL_COUNTERS, I2C_SCL_CYCLE_COUNTER, I2cXferCtxt->TCycle));

    /* Packing*/
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_TX_PACKING_CFG0, I2cXferCtxt->TxPackingCfg0);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_TX_PACKING_CFG1, I2cXferCtxt->TxPackingCfg1);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_RX_PACKING_CFG0, I2cXferCtxt->RxPackingCfg0);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_RX_PACKING_CFG1, I2cXferCtxt->RxPackingCfg1);


    /* clk divider */
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_SER_M_CLK_CFG,
        FLD_SET(SE0_GENI_SER_M_CLK_CFG, CLK_DIV_VALUE, I2cXferCtxt->ClkDiv) |
        FLD_SET(SE0_GENI_SER_M_CLK_CFG, SER_CLK_EN, 1));

    if (XferCtxt->RxLen)
    {
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_I2C_RX_TRANS_LEN, XferCtxt->RxLen);
    }
    else if(XferCtxt->TxLen)
    {
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_I2C_TX_TRANS_LEN, XferCtxt->TxLen);
    }

    if (I2cXferCtxt->Delay)
    {
        CoreSlowClk = QUP_HwInfo[BusCtxt->Instance].CoreSlowClk;
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_I2C_DELAY_COUNTER, I2cXferCtxt->Delay*CoreSlowClk);
    }
}
#endif

#ifdef ENABLE_PERIPHERAL_M2MDMA
void QUP_BusM2MDmaXferConfig(uint32_t SeCoreBase, QUP_XferCtxt_t *XferCtxt)
{
    XferCtxt->DmaRxDone = 0;
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_MEM2MEM_DMA, 1);

    if (QUP_ADDRESS_SRAM_RANGE(XferCtxt->RxBuf))
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_L, QUP_SRAM_MAP_TO_DMA(XferCtxt->RxBuf));
    else
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_PTR_L, XferCtxt->RxBuf);

    if (QUP_ADDRESS_SRAM_RANGE(XferCtxt->TxBuf))
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_L, QUP_SRAM_MAP_TO_DMA(XferCtxt->TxBuf));
    else
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_PTR_L, XferCtxt->TxBuf);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_LENGTH, XferCtxt->RxLen);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_LENGTH, XferCtxt->TxLen);
}
#endif

#ifdef ENABLE_PERIPHERAL_UART
void QUP_UartXferConfig(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt)
{
    QUP_BusCtxt_t *BusCtxt = QUP_BusCtxt[Instance];
    uint32_t SeCoreBase = QUP_HwInfo[BusCtxt->Instance].SeCoreBase;

    QUP_UartXferInfo_t *UartXferInfo = &XferCtxt->XferInfo.Uart;
    uint32_t TxTransCfg = 0, RxTransCfg = 0;
    uint32_t TxParityCfg = 0, RxParityCfg = 0;
    uint32_t Granularity;
    QUP_PackingConfig_t PackingConfig[QUP_PACKING_CONFIG_NUM];

    /* UART TX CLK is: SER_CLK/2*CLK_DIV_VALUE */
    QUP_BusFreqUpdate(SeCoreBase, 0, UartXferInfo->ClkDivider);

    /* UART RX CLK */
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_SER_S_CLK_CFG,
        FLD_SET(SE0_GENI_SER_S_CLK_CFG, CLK_DIV_VALUE, UartXferInfo->ClkDivider) |
        FLD_SET(SE0_GENI_SER_S_CLK_CFG, SER_CLK_EN, 1));

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_WORD_LEN,
        FLD_SET(SE0_UART_TX_WORD_LEN, UART_TX_WORD_LEN, UartXferInfo->BitsPerChar));

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_RX_WORD_LEN,
        FLD_SET(SE0_UART_RX_WORD_LEN, UART_RX_WORD_LEN, UartXferInfo->BitsPerChar));

    if(!UartXferInfo->Parity)
    {
        TxTransCfg &= FLD_SET(SE0_UART_TX_TRANS_CFG, UART_PARITY_EN, 0);
        RxTransCfg &= FLD_SET(SE0_UART_RX_TRANS_CFG, UART_PARITY_EN, 0);

        TxParityCfg &= FLD_SET(SE0_UART_TX_PARITY_CFG, TX_PAR_CALC_EN, 0);
        RxParityCfg &= FLD_SET(SE0_UART_RX_PARITY_CFG, RX_PAR_CALC_EN, 0);
    }
    else
    {
        TxTransCfg |= FLD_SET(SE0_UART_TX_TRANS_CFG, UART_PARITY_EN, 1);
        RxTransCfg |= FLD_SET(SE0_UART_RX_TRANS_CFG, UART_PARITY_EN, 1);

        TxParityCfg |= FLD_SET(SE0_UART_TX_PARITY_CFG, TX_PAR_CALC_EN, 1);
        RxParityCfg |= FLD_SET(SE0_UART_RX_PARITY_CFG, RX_PAR_CALC_EN, 1);

        TxParityCfg |= FLD_SET(SE0_UART_TX_PARITY_CFG, TX_PAR_MODE, (UartXferInfo->Parity-1));
        RxParityCfg |= FLD_SET(SE0_UART_RX_PARITY_CFG, RX_PAR_MODE, (UartXferInfo->Parity-1));
    }

    /* flow control, clear the CTS_MASK bit if using flow control. */
    if (UartXferInfo->FlowCtrl)
    {
        TxTransCfg &= FLD_SET(SE0_UART_TX_TRANS_CFG, UART_CTS_MASK, 0);
    }
    else
    {
        TxTransCfg |= FLD_SET(SE0_UART_TX_TRANS_CFG, UART_CTS_MASK, 1);
    }

    if(BusCtxt->BusType == QUP_BUS_UART_9BIT_HW)
    {
        REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_GENERAL_CFG,
            FLD_SET(SE0_GENI_GENERAL_CFG, CHAR_HUNT_SR_MSB_LSB, 0x1));
    }

    /* SE0_GENI_CFG_REG87 is same with SE0_UART_TX_TRANS_CFG, keep the value of bit 5 */
    TxTransCfg |= REG_IN(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG87);

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_TRANS_CFG, TxTransCfg);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_PARITY_CFG, TxParityCfg);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_RX_TRANS_CFG, RxTransCfg);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_RX_PARITY_CFG, RxParityCfg);

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_STOP_BIT_LEN,
        FLD_SET(SE0_UART_TX_STOP_BIT_LEN, UART_TX_STOP_BIT_LEN, UartXferInfo->NumStopBits));

    if(UartXferInfo->Loopback)
    {
        /* loopback between RX & TX and CTS & RFR lines */
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_LOOPBACK_CFG,
            FLD_SET(SE0_UART_LOOPBACK_CFG, LOOPBACK_MODE, 0x3));
    }
    else
    {
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_LOOPBACK_CFG,
            FLD_SET(SE0_UART_LOOPBACK_CFG, LOOPBACK_MODE, 0));
    }

    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_RX_STALE_CNT,
        FLD_SET(SE0_UART_RX_STALE_CNT, UART_RX_STALE_CNT, UartXferInfo->RxStaleCnt));

    if(BusCtxt->BusType == QUP_BUS_UART || BusCtxt->BusType == QUP_BUS_UART_9BIT_HW
        || BusCtxt->BusType == QUP_BUS_UART_TX_INVERT)
    {
        Granularity = QUP_BYTE_GRANULARITY_4x8;
        UartXferInfo->BytesPerWord = 1;
        QUP_GetPackingConfig(4, UartXferInfo->BitsPerChar, false, PackingConfig);
    }
    else
    {
        UartXferInfo->BytesPerWord = 2;
        Granularity = QUP_BYTE_GRANULARITY_2x16;
        QUP_GetPackingConfig(2, UartXferInfo->BitsPerChar, false, PackingConfig);
    }

    QUP_BusPackingConfig(SeCoreBase, PackingConfig);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_BYTE_GRANULARITY, Granularity);
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_RX_BYTE_GRANULARITY, Granularity);

    if (BusCtxt->XferMode == QUP_XFER_FIFO)
    {
        /*
	      Set RFR (Flow off) to FIFO_DEPTH - 2.
	      RX WM level at 50% RX_FIFO_DEPTH.
	      TX WM level at 10% TX_FIFO_DEPTH.
	     */

        XferCtxt->RxWaterMark = BusCtxt->RxFifoDepth >> 1;
        XferCtxt->TxWaterMark = 4;

        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_WATERMARK_REG,
            FLD_SET(SE0_GENI_TX_WATERMARK_REG, TX_WATERMARK, XferCtxt->TxWaterMark));

        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_WATERMARK_REG,
            FLD_SET(SE0_GENI_RX_WATERMARK_REG, RX_WATERMARK, XferCtxt->RxWaterMark));

        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_RFR_WATERMARK_REG,
            FLD_SET(SE0_GENI_RX_RFR_WATERMARK_REG, RX_RFR_WATERMARK, (BusCtxt->RxFifoDepth - 2)));
    }
}

void QUP_BusUartWriteToFifo(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t I = 0;
    uint32_t BytesToWrite = XferCtxt->TxLen - XferCtxt->TxCnt;
    uint8_t TxFifoWidth = BusCtxt->TxFifoWidth >> 3;
    uint32_t UnsentFifoEntries = REG_INF(SeCoreBase + GENI4_DATA_REG_BASE,
                               SE0_GENI_TX_FIFO_STATUS, TX_FIFO_WC);

    uint32_t FreeFifoEntries = (BusCtxt->TxFifoDepth - UnsentFifoEntries) * TxFifoWidth;
    BytesToWrite = BytesToWrite > FreeFifoEntries ? FreeFifoEntries : BytesToWrite;

    while (I < BytesToWrite)
    {
        uint32_t J, Data;
        uint8_t *FifoByte = (uint8_t *)&Data;

        for (J = 0, Data = 0; J < TxFifoWidth && I < BytesToWrite; J++)
        {
            FifoByte[J] = XferCtxt->TxCircBuf->Buf[XferCtxt->TxCircBuf->Tail++];
            if(XferCtxt->TxCircBuf->Tail == XferCtxt->TxCircBuf->Size)
                XferCtxt->TxCircBuf->Tail = 0;
            I++;
        }
        REG_OUTI(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_FIFOn, 0, Data);
    }

    XferCtxt->TxCnt += BytesToWrite;

    if(XferCtxt->TxCnt == XferCtxt->TxLen)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_CLEAR,
            FLD_SET(SE0_GENI_M_IRQ_EN_CLEAR, TX_FIFO_WATERMARK_EN_CLEAR, 1));
    }
    else
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
            FLD_SET(SE0_GENI_M_IRQ_EN_SET, TX_FIFO_WATERMARK_EN_SET, 1));
    }
}

static void QUP_BusUartReadFromFifo(uint32_t SeCoreBase, QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t Word, I;
    uint8_t BytesInLastWord, BytesToRead;
    uint32_t RxFifoStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFO_STATUS);
    uint32_t ValidFifoBytes = FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_FIFO_WC) << 2;
    uint32_t IrqStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_STATUS);
    XferCtxt->RxCnt = 0;

    if (FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_LAST))
    {
        BytesInLastWord = FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_LAST_BYTE_VALID);
        if(BytesInLastWord != 0)
        {
            ValidFifoBytes = (ValidFifoBytes - 4) + BytesInLastWord;
        }
    }

    if (ValidFifoBytes > XferCtxt->RxLen)
    {
       BytesToRead = (XferCtxt->RxLen >> 2) * 4;

       if (FLD_GET(RxFifoStatus, SE0_GENI_RX_FIFO_STATUS, RX_LAST))
       {
            XferCtxt->UnReadFlag = 1;
       }
    }
    else
    {
        XferCtxt->UnReadFlag = 0;
        /* If you are definitely going to read till the LAST byte, clear the interrupt.
           The RX LAST STATUS is not a level source to the secondary engine interrupt register
           This will result in RX getting stuck as clearing the interrupt without any reading
           the last byte will cause the interrupt to be permanently lost.*/
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_CLEAR,
            FLD_GET(IrqStatus, SE0_GENI_S_IRQ_CLEAR, RX_FIFO_LAST_CLEAR));
        BytesToRead = ValidFifoBytes;
    }

    for (I = 0; I < BytesToRead; I++)
    {
        if ((I & 0x3) == 0)
        {
            Word = REG_INI(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_FIFOn, 0);
        }

        XferCtxt->RxCircBuf->Buf[XferCtxt->RxCircBuf->Head++] = (Word >> ((I & 0x3) << 3)) & 0xFF;
        if(XferCtxt->RxCircBuf->Head == XferCtxt->RxCircBuf->Size)
            XferCtxt->RxCircBuf->Head = 0;
        XferCtxt->RxCnt++;
    }
}

void QUP_UartEnableRxIrq(QUP_Instance_t Instance)
{
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;

    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_EN_SET,
        FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_WATERMARK_EN_SET, 1) |
        FLD_SET(SE0_GENI_S_IRQ_EN_SET, RX_FIFO_LAST_EN_SET, 1));

    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_SET,
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_WATERMARK_EN_SET, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_SET, RX_FIFO_LAST_EN_SET, 1));
}

void QUP_UartClearRxIrq(QUP_Instance_t Instance)
{
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;

    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_EN_CLEAR,
        FLD_SET(SE0_GENI_S_IRQ_EN_CLEAR, RX_FIFO_WATERMARK_EN_CLEAR, 1) |
        FLD_SET(SE0_GENI_S_IRQ_EN_CLEAR, RX_FIFO_LAST_EN_CLEAR, 1));

    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_EN_CLEAR,
        FLD_SET(SE0_GENI_M_IRQ_EN_CLEAR, RX_FIFO_WATERMARK_EN_CLEAR, 1) |
        FLD_SET(SE0_GENI_M_IRQ_EN_CLEAR, RX_FIFO_LAST_EN_CLEAR, 1));
}

static void QUP_UartSetupTx(uint32_t SeCoreBase, QUP_XferCtxt_t *XferCtxt)
{
    uint8_t BytesPerWord = XferCtxt->XferInfo.Uart.BytesPerWord;

    /* Specifies a number of words to transmit in FIFO mode - max 2^24-1 */
    REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_TRANS_LEN, XferCtxt->TxLen/BytesPerWord);

    QUP_StartMCmd(SeCoreBase, XferCtxt->CmdOpcode, XferCtxt->CmdParam);
}

QUP_Status_t QUP_UartStartTx(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt)
{
    QUP_Status_t Status = QUP_SUCCESS;
    QUP_BusCtxt_t *BusCtxt = QUP_BusCtxt[Instance];
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    IRQn_Type IRQn = (IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance);
    uint32_t GeniIos;

    if (&BusCtxt->XferCtxt != XferCtxt)
    {
        Status = QUP_ERROR_INVALID_PARAM;
        goto exit;
    }

    /*PERIPH_SE0_GENI_M_CMD0
        UART:
        Start TX = 1
        Start Break = 4
        Stop Break = 5
    */

    if((BusCtxt->XferMode == QUP_XFER_FIFO) &&
        FLD_GET(Status, SE0_GENI_STATUS, M_GENI_CMD_ACTIVE))
    {
        Status = QUP_ERROR_COMMAND_OVER_RUN;
        goto exit;
    }

    if(BusCtxt->BusType == QUP_BUS_UART_9BIT_HW)
    {
        XferCtxt->CmdParam = XferCtxt->XferInfo.Uart.TxAddress << 1;
    }

    NVIC_DisableIRQ(IRQn);
    XferCtxt->TxBusy = 1;

    if(BusCtxt->XferMode == QUP_XFER_DMA)
    {
        QUP_UartSetupTx(SeCoreBase, XferCtxt);

        /* Enable interrupts */
        REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_EN_SET,
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, SBE_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, EOT_EN_SET, 1) |
            FLD_SET(SE0_DMA_TX_IRQ_EN_SET, DMA_DONE_EN_SET, 1));

        QUP_TxDmaPrepare(SeCoreBase, XferCtxt->TxBuf, XferCtxt->TxLen);
    }
    else if(BusCtxt->XferMode == QUP_XFER_FIFO)
    {

        QUP_UartSetupTx(SeCoreBase, XferCtxt);

        QUP_BusUartWriteToFifo(SeCoreBase, BusCtxt, XferCtxt);
    }

    NVIC_EnableIRQ(IRQn);

exit:
    GeniIos = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_IOS);
    if(!FLD_GET(GeniIos, SE0_GENI_IOS, IO2_DATA_IN))
    {
        /* do something for UART sw flow ctrl */
        return QUP_ERROR_TRANSFER_BUSY;
    }
    return Status;
}

QUP_Status_t QUP_UartStartRx(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt)
{
    QUP_Status_t Status = QUP_SUCCESS;
    uint32_t GeniStatus = 0, FreeSize=0;
    QUP_BusCtxt_t *BusCtxt = QUP_BusCtxt[Instance];
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    IRQn_Type IRQn = (IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance);

    if (&BusCtxt->XferCtxt != XferCtxt)
    {
        Status = QUP_ERROR_INVALID_PARAM;
        goto exit;
    }

    XferCtxt->Busy = 1;
    if(BusCtxt->BusType == QUP_BUS_UART_9BIT_HW)
    {
        /* enable HW address matching */
        XferCtxt->SCmdParam = 1;

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG94,
            XferCtxt->XferInfo.Uart.RxAddress);
    }

    if (BusCtxt->XferMode == QUP_XFER_FIFO)
    {
        NVIC_DisableIRQ(IRQn);
        if(XferCtxt->UnReadFlag)
        {
            QUP_BusUartReadFromFifo(SeCoreBase, BusCtxt, XferCtxt);
            FreeSize = QUP_CIRC_SPACE(XferCtxt->RxCircBuf->Head, XferCtxt->RxCircBuf->Tail, XferCtxt->RxCircBuf->Size);
            XferCtxt->RxLen = FreeSize;
            if(XferCtxt->RxLen < 4)
            {
               XferCtxt->RxLen = 0;
            }
        }

        QUP_UartEnableRxIrq(Instance);
        NVIC_EnableIRQ(IRQn);
    }

    GeniStatus = REG_IN(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_STATUS);
    if((BusCtxt->XferMode == QUP_XFER_FIFO) &&
        (FLD_GET(GeniStatus, SE0_GENI_STATUS, S_GENI_CMD_ACTIVE)))
    {
        /* secondary sequencer is executing a command */
        Status = QUP_ERROR_TRANSFER_BUSY;
        goto exit;
    }

    NVIC_DisableIRQ(IRQn);

    QUP_StartSCmd(SeCoreBase, XferCtxt->SCmdOpcode, XferCtxt->SCmdParam);

    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        QUP_RxDmaPrepare(SeCoreBase, XferCtxt->RxBuf, XferCtxt->RxLen);
    }
    NVIC_EnableIRQ(IRQn);

exit:
    return Status;
}

inline static uint32_t QUP_FifoSErrorGet(uint32_t IrqStatus, QUP_BusCtxt_t *BusCtxt)
{
#ifdef BUS_ERROR_STATS
    BusCtxt->ErrStats.FifoSErrs++;
#endif
    if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_RD_ERR))
    {
        return QUP_ERROR_INPUT_FIFO_UNDER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_WR_ERR))
    {
        return QUP_ERROR_INPUT_FIFO_OVER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_CMD_OVERRUN))
    {
        return QUP_ERROR_COMMAND_OVER_RUN;
    }
    else if ((FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_CMD_CANCEL)) ||
        (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_CMD_ABORT)))
    {
        return QUP_ERROR_TRANSFER_FORCE_TERMINATED;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_ILLEGAL_CMD))
    {
        return QUP_ERROR_COMMAND_ILLEGAL;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_CMD_FAILURE))
    {
        return QUP_ERROR_COMMAND_FAIL;
    }
#if 0
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_GP_IRQ_0))
    {
        /* TODO UART: Parity Error */
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.ParityErr++;
        #endif
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_GP_IRQ_1))
    {
        /* TODO UART: Framing Error */
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.FrameErr++;
        #endif
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_GP_IRQ_2))
    {
        /* TODO UART: Break Start */
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.Break++;
        #endif
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_GP_IRQ_3))
    {
        /* TODO UART: Break End */
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, S_GP_IRQ_4))
    {
        /* TODO UART: Char Hunt detect */
    }
#endif

    return QUP_SUCCESS;
}

/* GENI seconday frame engine interrupt process */
static QUP_Status_t QUP_BusFifoSIsrProcess(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt,
                                           uint32_t SeCoreBase, uint32_t IrqStatus)
{
    QUP_Status_t RetStatus = QUP_SUCCESS;

    /* S_IRQ_STATUS is only for UART RX */
    if(!BusCtxt->IsUart)
    {
        Qup_AssertFunc();
    }

    if (IrqStatus & QUP_FIFO_S_ERROR_MASK)
    {
        RetStatus = (QUP_Status_t)QUP_FifoSErrorGet(IrqStatus, BusCtxt);
    }

    if (RetStatus != QUP_SUCCESS)
    {
        //XferCtxt->Busy = 0;
        //goto exit;
    }

    if (XferCtxt->RxLen && XferCtxt->RxCircBuf &&(FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_WATERMARK)
        || FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_LAST)))
    {
        QUP_BusUartReadFromFifo(SeCoreBase, BusCtxt, XferCtxt);
        XferCtxt->Busy = 0;
        XferCtxt->CFn(RetStatus, XferCtxt->CCtxt);
    }
    else if((XferCtxt->RxLen == 0) && (FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_LAST)
	    || FLD_GET(IrqStatus, SE0_GENI_S_IRQ_STATUS, RX_FIFO_WATERMARK)))
    {
        QUP_UartClearRxIrq((QUP_Instance_t)BusCtxt->Instance);
        XferCtxt->UnReadFlag = 1;
        RetStatus = QUP_ERROR_RX_FIFO_RX_UNDER_READ;
        XferCtxt->CFn(RetStatus, XferCtxt->CCtxt);
    }

    return RetStatus;
}
#endif

inline static QUP_Status_t QUP_FifoMErrorGet(uint32_t IrqStatus, QUP_BusCtxt_t *BusCtxt)
{
#ifdef BUS_ERROR_STATS
    BusCtxt->ErrStats.FifoMErrs++;
#endif
    if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, RX_FIFO_RD_ERR))
    {
        return QUP_ERROR_INPUT_FIFO_UNDER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, RX_FIFO_WR_ERR))
    {
        return QUP_ERROR_INPUT_FIFO_OVER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, TX_FIFO_RD_ERR))
    {
        return QUP_ERROR_OUTPUT_FIFO_UNDER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, TX_FIFO_WR_ERR))
    {
        return QUP_ERROR_OUTPUT_FIFO_OVER_RUN;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_OVERRUN))
    {
        return QUP_ERROR_COMMAND_OVER_RUN;
    }
    else if ((FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_CANCEL)) ||
        (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_ABORT)))
    {
        return QUP_ERROR_TRANSFER_FORCE_TERMINATED;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_ILLEGAL_CMD))
    {
        return QUP_ERROR_COMMAND_ILLEGAL;
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_FAILURE))
    {
        return QUP_ERROR_COMMAND_FAIL;
    }
#if 0
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, IO_DATA_ASSERT))
    {
        /* TODO Asserted only in UART protocol when CTS gets asserted. */
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, IO_DATA_DEASSERT))
    {
        /* TODO Asserted only in UART protocol when CTS gets de-asserted. */
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_GP_IRQ_1))
    {
        /* TODO I2C: Slave NACK IRQ */
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_GP_IRQ_3))
    {
        /* TODO I2C: Protocol error on I2C bus*/
    }
    else if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_GP_IRQ_4))
    {
        /* TODO I2C: Arbitration Lost */
    }
#endif

    return QUP_SUCCESS;
}

/* GENI main frame engine interrupt process */
static QUP_Status_t QUP_BusFifoMIsrProcess(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt,
                                           uint32_t SeCoreBase, uint32_t IrqStatus)
{
    QUP_Status_t RetStatus = QUP_SUCCESS;

    if (IrqStatus & QUP_FIFO_M_ERROR_MASK)
    {
        RetStatus = QUP_FifoMErrorGet(IrqStatus, BusCtxt);
    }

    if (RetStatus != QUP_SUCCESS && !BusCtxt->IsUart)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_TX_WATERMARK_REG,
                FLD_SET(SE0_GENI_TX_WATERMARK_REG, TX_WATERMARK, 0));
        XferCtxt->Busy = 0;
        goto exit;
    }

#ifdef ENABLE_PERIPHERAL_UART
    /* M_IRQ_STATUS is only for UART TX */
    if(BusCtxt->IsUart)
    {
        if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_DONE))
        {
            /* call the uart tx callback and update the ring buffer status */
            XferCtxt->TxBusy = 0;
            XferCtxt->TxCnt = 0;
            XferCtxt->TxedLen = REG_IN(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_TRANS_LEN) *
                XferCtxt->XferInfo.Uart.BytesPerWord;
            XferCtxt->TxCFn(RetStatus, XferCtxt->CCtxt);
        }
        else if(XferCtxt->TxCnt && FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, TX_FIFO_WATERMARK))
        {
            QUP_BusUartWriteToFifo(SeCoreBase, BusCtxt, XferCtxt);
        }
    }
    else
#endif
    {
        if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, M_CMD_DONE))
        {
            XferCtxt->Busy = 0;

            /* If the M_CMD_DONE flag is set, check whether there is some data to be read
               from the FIFO, only when the read transactions are requested by the client.
             */
            if (XferCtxt->RxBuf)
            {
               QUP_BusReadFromFifo(SeCoreBase, BusCtxt, XferCtxt);
            }
        }
        else
        {
            /* Otherwise check for Tx/Rx watermark status for further writing/reading
               to/from FIFO respectively.
             */
           if (XferCtxt->TxBuf && FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, TX_FIFO_WATERMARK))
            {
                QUP_BusWriteToFifo(SeCoreBase, BusCtxt, XferCtxt);
            }

            if (FLD_GET(IrqStatus, SE0_GENI_M_IRQ_STATUS, RX_FIFO_WATERMARK))
            {
                QUP_BusReadFromFifo(SeCoreBase, BusCtxt, XferCtxt);
            }
        }
    }

exit:
    return RetStatus;
}

static QUP_Status_t QUP_BusFifoIsrProcess(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t SeCoreBase = QUP_HwInfo[BusCtxt->Instance].SeCoreBase;
    uint32_t MIrqStatus, SIrqStatus;
    QUP_Status_t Status = QUP_SUCCESS;

    MIrqStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_STATUS);
    SIrqStatus = REG_IN(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_STATUS);

#ifdef BUS_ERROR_STATS
    if(!MIrqStatus && !SIrqStatus)
    {
        BusCtxt->ErrStats.IsrErr++;
    }
#endif

    if(MIrqStatus)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_CLEAR, MIrqStatus);
        Status = QUP_BusFifoMIsrProcess(BusCtxt, XferCtxt, SeCoreBase, MIrqStatus);
    }

#ifdef ENABLE_PERIPHERAL_UART
    if(BusCtxt->IsUart && SIrqStatus)
    {
        REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_CLEAR, SIrqStatus);
        /* UART RX, seconday interrupt status register */
        Status = QUP_BusFifoSIsrProcess(BusCtxt, XferCtxt, SeCoreBase, SIrqStatus);
    }
#endif

    return Status;
}

inline static QUP_Status_t QUP_DmaTxErrorGet(uint32_t TxIrqStatus, QUP_BusCtxt_t *BusCtxt)
{
    if (FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, SBE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.TxDmaSbe++;
        #endif
        return QUP_ERROR_DMA_TX_BUS_ERROR;
    }
    else if (FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, GENI_CMD_FAILURE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.DmaCmdFail++;
        #endif
        return QUP_ERROR_COMMAND_FAIL;
    }
    else if (FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, GENI_CANCEL_IRQ))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.OtherDmaErr++;
        #endif
        return QUP_ERROR_TRANSFER_FORCE_TERMINATED;
    }
    else if (FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, RESET_DONE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.TxDmaRst++;
        #endif
        return QUP_ERROR_DMA_TX_RESET_DONE;
    }

#ifdef BUS_ERROR_STATS
    BusCtxt->ErrStats.TxDmaErrs++;
#endif
    return QUP_SUCCESS;
}

inline static QUP_Status_t QUP_DmaRxErrorGet(uint32_t RxIrqStatus, QUP_BusCtxt_t *BusCtxt)
{
    if (FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, SBE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.RxDmaSbe++;
        #endif
        return QUP_ERROR_DMA_RX_BUS_ERROR;
    }
    else if (FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, GENI_CMD_FAILURE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.DmaCmdFail++;
        #endif
        return QUP_ERROR_COMMAND_FAIL;
    }
    else if (FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, GENI_CANCEL_IRQ))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.OtherDmaErr++;
        #endif
        return QUP_ERROR_TRANSFER_FORCE_TERMINATED;
    }
    else if (FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, RESET_DONE))
    {
        #ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.RxDmaRst++;
        #endif
        return QUP_ERROR_DMA_RX_RESET_DONE;
    }

#ifdef BUS_ERROR_STATS
        BusCtxt->ErrStats.RxDmaErrs++;
#endif
    return QUP_SUCCESS;
}

static QUP_Status_t QUP_BusDmaIsrProcess(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    uint32_t SeCoreBase = QUP_HwInfo[BusCtxt->Instance].SeCoreBase;
    uint32_t TxIrqStatus, RxIrqStatus;
    QUP_Status_t RetStatus = QUP_SUCCESS;

    TxIrqStatus = REG_IN(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_STAT);
    RxIrqStatus = REG_IN(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_STAT);

    if (TxIrqStatus & QUP_DMA_TX_ERROR_MASK)
    {
        RetStatus = QUP_DmaTxErrorGet(TxIrqStatus, BusCtxt);
    }

    if (RxIrqStatus & QUP_DMA_RX_ERROR_MASK)
    {
        RetStatus = QUP_DmaRxErrorGet(RxIrqStatus, BusCtxt);
    }

    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_CLR, TxIrqStatus);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_CLR, RxIrqStatus);

    if (RetStatus != QUP_SUCCESS)
    {
        XferCtxt->Busy = 0;
        goto exit;
    }

#ifdef ENABLE_PERIPHERAL_UART
    if(BusCtxt->IsUart)
    {
        if (FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, DMA_DONE))
        {
            XferCtxt->DmaTxDone = 1;
            XferCtxt->TxBusy = 0;
            XferCtxt->TxedLen = REG_IN(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_UART_TX_TRANS_LEN)*
                XferCtxt->XferInfo.Uart.BytesPerWord;
            XferCtxt->TxCFn(RetStatus, XferCtxt->CCtxt);
        }

        if (FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, DMA_DONE))
        {
            XferCtxt->DmaRxDone = 1;

            XferCtxt->Busy = 0;
			/* HPG section 3.7.2.1 Step 6 */
            XferCtxt->RxCnt = REG_IN(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_LENGTH_IN);
            #ifdef BUS_ERROR_STATS
            if(XferCtxt->RxCnt == 0)
                BusCtxt->ErrStats.RxDmaCntErr++;
            #endif
            XferCtxt->CFn(RetStatus, XferCtxt->CCtxt);
        }
        goto exit;
    }
#endif

    if (BusCtxt->BusType != QUP_BUS_M2MDMA && XferCtxt->TxBuf &&
        FLD_GET(TxIrqStatus, SE0_DMA_TX_IRQ_STAT, DMA_DONE))
    {
        XferCtxt->DmaTxDone = 1;
        XferCtxt->TxCnt = XferCtxt->TxLen;
    }

    if (XferCtxt->RxBuf && FLD_GET(RxIrqStatus, SE0_DMA_RX_IRQ_STAT, DMA_DONE))
    {
        XferCtxt->DmaRxDone = 1;
        XferCtxt->RxCnt = XferCtxt->RxLen;
    }

    if (XferCtxt->DmaRxDone && (XferCtxt->DmaTxDone || BusCtxt->BusType == QUP_BUS_M2MDMA))
    {
        XferCtxt->Busy = 0;

        if(BusCtxt->BusType == QUP_BUS_SPI_MASTER_3WIRE_9BIT || 
            BusCtxt->BusType == QUP_BUS_SPI_MASTER_4WIRE_8BIT)
        {
            /* the operation will set CS idle after operation is done */
            /* start bus command execution */
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_CMD0,
                        FLD_SET(SE0_GENI_M_CMD0, OPCODE, 9) /* |
                        FLD_SET(SE0_GENI_M_CMD0, PARAM, CmdParam)*/);
        }
    }

exit:
    return RetStatus;
}

static QUP_Status_t QUP_BusIsrProcess(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    QUP_Status_t Status;

    if(BusCtxt->IsUart)
    {
        uint32_t SeCoreBase = QUP_HwInfo[BusCtxt->Instance].SeCoreBase;

        if (REG_INF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_STATUS, RX_FIFO_WR_ERR))
        {
            /* HW writes to a full RX FIFO */
            #ifdef BUS_ERROR_STATS
            BusCtxt->ErrStats.RxFifoWr++;
            #endif
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_CLEAR,
                FLD_SET(SE0_GENI_S_IRQ_CLEAR, RX_FIFO_WR_ERR_CLEAR, 1));
            REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_CLEAR,
                FLD_SET(SE0_GENI_M_IRQ_CLEAR, RX_FIFO_WR_ERR_CLEAR, 1));
        }
    }

    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        Status = QUP_BusDmaIsrProcess(BusCtxt, XferCtxt);
    }
    else
    {
        Status = QUP_BusFifoIsrProcess(BusCtxt, XferCtxt);
    }

    if(!BusCtxt->IsUart)
    {
        if (!XferCtxt->Busy && XferCtxt->CFn)
        {
            XferCtxt->Status = Status;
            qapi_TSK_Signal_Task(BusCtxt->Task, QUP_TASK_EVENT);
        }

        if (XferCtxt->Busy)
        {
           NVIC_EnableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)BusCtxt->Instance));
        }
    }

    return Status;
}

static uint32_t QUP_BusTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    QUP_BusCtxt_t *BusCtxt = (QUP_BusCtxt_t *)UserParam;
    QUP_XferCtxt_t *XferCtxt = &BusCtxt->XferCtxt;

    if (EventMask & QUP_TASK_EVENT)
    {
        XferCtxt->CFn(XferCtxt->Status, XferCtxt->CCtxt);
    }

    return QAPI_TSK_INFINITE_WAIT;
}

void QUP_BusXferConfig(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt)
{
    QUP_BusCtxt_t *BusCtxt = QUP_BusCtxt[Instance];
    uint32_t SeCoreBase = QUP_HwInfo[BusCtxt->Instance].SeCoreBase;

    QUP_GeniSeIrqClear(SeCoreBase);

    switch (BusCtxt->BusType)
    {
#ifdef ENABLE_PERIPHERAL_SPI
        case QUP_BUS_SPI_MASTER_3WIRE_9BIT:
        case QUP_BUS_SPI_MASTER_4WIRE_8BIT:
        case QUP_BUS_SPI_MASTER:
        case QUP_BUS_SPI_SLAVE:
            QUP_SpiXferConfig(SeCoreBase, BusCtxt, XferCtxt);
            break;
#endif
#ifdef ENABLE_PERIPHERAL_I2C
        case QUP_BUS_I2C_MASTER:
            QUP_I2cXferConfig(SeCoreBase, BusCtxt, XferCtxt);
            break;
#endif
#ifdef ENABLE_PERIPHERAL_M2MDMA
        case QUP_BUS_M2MDMA:
            QUP_BusM2MDmaXferConfig(SeCoreBase, XferCtxt);
            return;
#endif
        default:
            break;
    }

    if (BusCtxt->BusType != QUP_BUS_SPI_SLAVE)
    {
    	QUP_StartMCmd(SeCoreBase, XferCtxt->CmdOpcode, XferCtxt->CmdParam);
    }

    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        if (XferCtxt->RxBuf)
        {
            QUP_RxDmaPrepare(SeCoreBase, XferCtxt->RxBuf, XferCtxt->RxLen);
        }
        else
        {
            XferCtxt->DmaRxDone = 1;
        }

        if (XferCtxt->TxBuf)
        {
            QUP_TxDmaPrepare(SeCoreBase, XferCtxt->TxBuf, XferCtxt->TxLen);
        }
        else
        {
            XferCtxt->DmaTxDone = 1;
        }
    }
}

static void QUP_StartSerialEngine(uint32_t SeCoreBase, qbool_t Start)
{
    REG_OUTF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, PROG_RAM_SCLK_OFF, 1);
    REG_OUTF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, PROG_RAM_HCLK_OFF, 1);

    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_GENI_CLK_CTRL, SER_CLK_SEL, Start);

    REG_OUTF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, PROG_RAM_SCLK_OFF, 0);
    REG_OUTF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, PROG_RAM_HCLK_OFF, 0);
}

static void QUP_StartGeni(QUP_BusCtxt_t *BusCtxt, uint32_t SeCoreBase)
{
    uint32_t RxFifoDepth =  REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE,
                                    SE0_SE_HW_PARAM_1, RX_FIFO_DEPTH);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_RX_RFR_WATERMARK_REG, RxFifoDepth - 2);
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_FORCE_DEFAULT_REG, 1);

    /* Enable GENI FW */
    QUP_StartSerialEngine(SeCoreBase, true);

#ifdef ENABLE_PERIPHERAL_SPI
    if (!BusCtxt->NoMuxPriority)
    {
        if (BusCtxt->BusType < QUP_BUS_I2C_MASTER)
        {
            if (BusCtxt->Instance == QUP_INSTANCE_0)
            {
                HWIO_SE_0_PRIORITY_MUX_OUT(HWIO_SE_0_PRIORITY_MUX_FB_CLK_EN_BMSK
                                        | HWIO_SE_0_PRIORITY_MUX_SELECT_BMSK);
            }
            else if (BusCtxt->Instance == QUP_INSTANCE_1)
            {
                HWIO_SE_1_PRIORITY_MUX_OUT(HWIO_SE_1_PRIORITY_MUX_FB_CLK_EN_BMSK
                                        | HWIO_SE_1_PRIORITY_MUX_SELECT_BMSK);
            }
        }
    }

    if (BusCtxt->BusType == QUP_BUS_SPI_SLAVE)
    {
        uint32_t SeqStatus, TimeoutUs = 40000;

        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_SPI_SLAVE_EN, 1);
        REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_OUTPUT_CTRL, 1);
        /* Propagate slave_mode_en to IO macro */
        REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CFG_SEQ_START,
            FLD_SET(SE0_GENI_CFG_SEQ_START, START_TRIGGER, 1));

        SeqStatus = REG_INF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CFG_STATUS, CFG_SEQ_DONE);
        while ((SeqStatus == 0) && (TimeoutUs != 0))
        {
            SeqStatus = REG_INF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CFG_STATUS, CFG_SEQ_DONE);

            qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
            TimeoutUs -= QUP_POLL_INTERVAL_US;
        }
    }
    else
#endif
    {
        REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_OUTPUT_CTRL, 0x7f);
    }

    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_DMA_MODE_EN, GENI_DMA_MODE_EN, 1);
        REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_DMA_IF_EN, DMA_IF_EN, 1);
        REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_FIFO_IF_DISABLE, FIFO_IF_DISABLE, 1);
    }
    else /* FIFO */
    {
        REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_DMA_MODE_EN, GENI_DMA_MODE_EN, 0);
        REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_DMA_IF_EN, DMA_IF_EN, 0);
        REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_FIFO_IF_DISABLE, FIFO_IF_DISABLE, 0);
    }

    BusCtxt->TxFifoDepth = REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_HW_PARAM_0, TX_FIFO_DEPTH);
    BusCtxt->RxFifoDepth = REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_HW_PARAM_1, RX_FIFO_DEPTH);
    BusCtxt->TxFifoWidth = REG_INF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_SE_HW_PARAM_0, TX_FIFO_WIDTH);

    QUP_GeniSeIrqClear(SeCoreBase);
    QUP_GeniSeIrqEnSet(SeCoreBase, BusCtxt);
}

static void QUP_StopGeni(QUP_BusCtxt_t *BusCtxt, uint32_t SeCoreBase)
{
#ifdef ENABLE_PERIPHERAL_SPI
    if (BusCtxt->BusType < QUP_BUS_I2C_MASTER)
    {
        if (BusCtxt->Instance == QUP_INSTANCE_0)
        {
            HWIO_SE_0_PRIORITY_MUX_OUT(0);
        }
        else if (BusCtxt->Instance == QUP_INSTANCE_1)
        {
            HWIO_SE_1_PRIORITY_MUX_OUT(0);
        }
    }
#endif

    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_GENI_CLK_CTRL, SER_CLK_SEL, 0);
}

static void QUP_GeniSeFwLoad(QUP_BusCtxt_t *BusCtxt, uint32_t SeCoreBase)
{
    uint32_t Instance = BusCtxt->Instance;
    uint32_t Protocol = 0;
    QUP_FwHdr_t *FwHdr = NULL;
    uint32_t i;
    
    #if ENABLE_QUP_FW_COMPRESS
    uint32_t decomporessedLen;
    uint32_t decompress_param[3];
    char *dst=qapi_Malloc(QUP_FW_DECOMPRESS_BUFFER_LEN_MAX);
    if(!dst)
    {
        Qup_AssertFunc();
    }
    memset(dst, 0, QUP_FW_DECOMPRESS_BUFFER_LEN_MAX);
    #endif

    /* Disable GENI FW */
    QUP_StartSerialEngine(SeCoreBase, false);

    switch (BusCtxt->BusType)
    {
#ifdef ENABLE_PERIPHERAL_SPI
        case QUP_BUS_SPI_MASTER_3WIRE_9BIT:
        case QUP_BUS_SPI_MASTER_4WIRE_8BIT:
            Protocol = 0xa;
            FwHdr = Qup_GeniGetSPINwireFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniSPINwireFw_Len;
            #endif
            break;
        case QUP_BUS_SPI_MASTER:
            Protocol = 1;
            FwHdr = Qup_GeniGetSPIMasterFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniSPIMasterFw_Len;
            #endif
            break;
        case QUP_BUS_SPI_SLAVE:
            Protocol = 5;
            FwHdr = Qup_GeniGetSPISlaveFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniSPISlaveFw_Len;
            #endif
            break;
#endif
#ifdef ENABLE_PERIPHERAL_I2C
        case QUP_BUS_I2C_MASTER:
            Protocol = 3;
            FwHdr = Qup_GeniGetI2CFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniI2CFw_Len;
            #endif
            break;
#endif
#ifdef ENABLE_PERIPHERAL_UART
        case QUP_BUS_UART:
        case QUP_BUS_UART_9BIT_SW:
        case QUP_BUS_UART_TX_INVERT:
            Protocol = 2;
            FwHdr = Qup_GeniGetUartFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniUartFw_Len;
            #endif
            break;
        case QUP_BUS_UART_9BIT_HW:
            Protocol = 0xb;
            FwHdr = Qup_GeniGetUart9bitFw();
            #if ENABLE_QUP_FW_COMPRESS
            decomporessedLen = Qup_GeniUart9bitFw_Len;
            #endif
            break;
#endif
        default:
            return;
    }

    #if ENABLE_QUP_FW_COMPRESS
    decompress_param[0]=(uint32_t)FwHdr - (uint32_t)decompress_param;;
    decompress_param[1]=decomporessedLen*2;
    decompress_param[2]=(uint32_t)dst;
    __iar_lz77_init_single3(decompress_param);
    
    FwHdr = (QUP_FwHdr_t *)dst;
    #endif

    if (QUP_HwInfo[Instance].GeniSeMode == QUP_GENI_SE_MINICORE)
    {
        REG_OUTF(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_FW_REVISION, PROTOCOL, Protocol);
    }

    const uint32_t *FwValArr = (const uint32_t *)((uint8_t *)FwHdr + FwHdr->FwOffset);
    const uint8_t *CfgIdxArr = (const uint8_t *)FwHdr + FwHdr->CfgIdxOffset;
    const uint32_t *CfgValArr = (const uint32_t *)((uint8_t *)FwHdr + FwHdr->CfgValOffset);

    if (QUP_HwInfo[Instance].GeniSeMode == QUP_GENI_SE_FW)
    {
        REG_OUT(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_FW_REVISION,
            FLD_SET(SE0_GENI_FW_REVISION, PROTOCOL, FwHdr->SerialProtocol) |
            FLD_SET(SE0_GENI_FW_REVISION, VERSION, FwHdr->FwVersion));

        REG_OUT(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_S_FW_REVISION,
            FLD_SET(SE0_GENI_S_FW_REVISION, PROTOCOL, FwHdr->SerialProtocol) |
            FLD_SET(SE0_GENI_S_FW_REVISION, VERSION, FwHdr->FwVersion));

        for (i = 0; i < FwHdr->FwSizeInItems; i++)
        {
            REG_OUTI(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_CFG_RAMn, i, FwValArr[i]);
        }
    }

    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_INIT_CFG_REVISION,
        FLD_SET(SE0_GENI_INIT_CFG_REVISION, VERSION, FwHdr->CfgVersion));

    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_S_INIT_CFG_REVISION,
        FLD_SET(SE0_GENI_S_INIT_CFG_REVISION, VERSION, FwHdr->CfgVersion));

    for (i = 0; i < FwHdr->CfgSizeInItems; i++)
    {
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE + CfgIdxArr[i] * sizeof(uint32_t),
            SE0_GENI_CFG_REG0, CfgValArr[i]);
    }

#ifdef ENABLE_PERIPHERAL_UART
    if(BusCtxt->BusType == QUP_BUS_UART_TX_INVERT)
    {
        /* enable the TX invert mode */
        REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG87, M_SW_COMP5, 0x1);

        /* change the default state of the lanes (32'h0941C6A8 ) */
        REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG67, TX_DEFAULT_SOUT_VALUE, 0x0);

        /* to invert the data bits (32'h00000001) */
        REG_OUT(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG76,
            FLD_SET(SE0_GENI_CFG_REG76, TX_ENGINE_INV_EN, 0x1));

        REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_FORCE_DEFAULT_REG,
            FLD_SET(SE0_GENI_FORCE_DEFAULT_REG, FORCE_DEFAULT, 0x1));
    }
#endif
    #if ENABLE_QUP_FW_COMPRESS
    qapi_Free(dst);
    dst = NULL;
    #endif
}

static void QUP_GeniSeInit(QUP_BusCtxt_t *BusCtxt, uint32_t CommonBase, uint32_t SeCoreBase)
{
    REG_OUTF(CommonBase, QUPV3_COMMON_CFG, FAST_SWITCH_TO_HIGH_DISABLE, 1);

    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_OUTPUT_CTRL, 0);

    /* DFS interface initialization */
    REG_OUTF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_DFS_IF_CFG, DFS_IF_EN, 0);

    /* QUPv3 CGC initialization */
    REG_OUTF(CommonBase, QUPV3_SE_AHB_M_CFG, AHB_M_CLK_CGC_ON, 1);
    REG_OUTF(CommonBase, QUPV3_COMMON_CGC_CTRL, COMMON_CSR_SLV_CLK_CGC_ON, 1);

    QUP_GeniSeClkSet(SeCoreBase, (QUP_XferMode_t)BusCtxt->XferMode, true);
}

#ifdef ENABLE_PERIPHERAL_M2MDMA
static void QUP_HwM2mdmaInit(uint32_t SeCoreBase)
{
    REG_OUTF(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_FW_REVISION, PROTOCOL, 0);

    QUP_GeniSeIrqClear(SeCoreBase);

    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_EN_SET,
        FLD_SET(SE0_DMA_TX_IRQ_EN_SET, SBE_EN_SET, 1) |
        FLD_SET(SE0_DMA_TX_IRQ_EN_SET, DMA_DONE_EN_SET, 1));
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_EN_SET,
        FLD_SET(SE0_DMA_RX_IRQ_EN_SET, SBE_EN_SET, 1) |
        FLD_SET(SE0_DMA_RX_IRQ_EN_SET, DMA_DONE_EN_SET, 1));
    REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG86, GENI_DMA_MODE_EN, 1);
    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_DMA_IF_EN, DMA_IF_EN, 1);
    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_FIFO_IF_DISABLE, FIFO_IF_DISABLE, 1);
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, 0x7F);

    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_MAX_BURST_SIZE, 0x2);
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_MAX_BURST_SIZE, 0x2);
    REG_OUTF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_ATTR, DMA_OPERATION, 0x0);
    REG_OUTF(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_ATTR, DMA_OPERATION, 0x0);
}

static void QUP_HwM2mdmaDeInit(uint32_t SeCoreBase)
{
    REG_OUTF(SeCoreBase + GENI4_IMAGE_REG_BASE, SE0_GENI_FW_REVISION, PROTOCOL, 0);
    REG_OUT(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_MEM2MEM_DMA, 0);

    QUP_GeniSeIrqClear(SeCoreBase);

    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_TX_IRQ_EN_CLR,
        FLD_SET(SE0_DMA_TX_IRQ_EN_CLR, SBE_EN_CLR, 1) |
        FLD_SET(SE0_DMA_TX_IRQ_EN_CLR, DMA_DONE_EN_CLR, 1));
    REG_OUT(SeCoreBase + QUPV3_SE_DMA_REG_BASE, SE0_DMA_RX_IRQ_EN_CLR,
        FLD_SET(SE0_DMA_RX_IRQ_EN_CLR, SBE_EN_CLR, 1) |
        FLD_SET(SE0_DMA_RX_IRQ_EN_CLR, DMA_DONE_EN_CLR, 1));
    REG_OUTF(SeCoreBase + GENI4_IMAGE_REGS_REG_BASE, SE0_GENI_CFG_REG86, GENI_DMA_MODE_EN, 0);
    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_DMA_IF_EN, DMA_IF_EN, 0);
    REG_OUTF(SeCoreBase + QUPV3_SEC_REG_BASE, SE0_FIFO_IF_DISABLE, FIFO_IF_DISABLE, 0);
    REG_OUT(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_CGC_CTRL, 0x0);
}
#endif

static void QUP_HwInit(QUP_BusCtxt_t *BusCtxt)
{
    uint32_t Instance = BusCtxt->Instance;
    uint32_t SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    uint32_t CommonBase = QUP_HwInfo[Instance].CommonBase;

#ifdef ENABLE_PERIPHERAL_M2MDMA
    if (BusCtxt->BusType == QUP_BUS_M2MDMA)
    {
        QUP_HwM2mdmaInit(SeCoreBase);
    }
    else
#endif
    {
        /*CFG config must be before SeInit*/
        QUP_GeniSeFwLoad(BusCtxt, SeCoreBase);
        QUP_GeniSeInit(BusCtxt, CommonBase, SeCoreBase);
        QUP_StartGeni(BusCtxt, SeCoreBase);
    }
}

static QUP_Status_t QUP_BusPollingTransfer(QUP_BusCtxt_t *BusCtxt, QUP_XferCtxt_t *XferCtxt)
{
    QUP_Status_t Status = QUP_ERROR_TRANSFER_TIMEOUT;
    uint32_t TimeoutUs = QUP_POLL_TIME_DEFAULT_US;

    while (XferCtxt->Busy && (TimeoutUs != 0))
    {
        if (BusCtxt->IntPending)
        {
            BusCtxt->IntPending = 0;

            Status = QUP_BusIsrProcess(BusCtxt, XferCtxt);
            if (Status != QUP_SUCCESS)
            {
                return Status;
            }
        }

        qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
        TimeoutUs -= QUP_POLL_INTERVAL_US;
    }

    if ((TimeoutUs == 0) && XferCtxt->Busy)
    {
        QUP_BusMCancelSync((QUP_Instance_t)BusCtxt->Instance);
        Status = QUP_ERROR_TRANSFER_TIMEOUT;
    }

    return Status;
}

/**
   @brief Performs a data transfer over the serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt  --  Transfer configuration specified by #QUP_XferCtxt_t

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
   QUP_ERROR_TRANSFER_TIMEOUT
   QUP_ERROR_INPUT_FIFO_UNDER_RUN
   QUP_ERROR_INPUT_FIFO_OVER_RUN
   QUP_ERROR_OUTPUT_FIFO_UNDER_RUN
   QUP_ERROR_OUTPUT_FIFO_OVER_RUN
   QUP_ERROR_COMMAND_OVER_RUN
   QUP_ERROR_TRANSFER_FORCE_TERMINATED
   QUP_ERROR_COMMAND_ILLEGAL
   QUP_ERROR_COMMAND_FAIL
   QUP_ERROR_DMA_TX_BUS_ERROR
   QUP_ERROR_DMA_RX_BUS_ERROR
*/
QUP_Status_t QUP_BusTransfer(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt)
{
    QUP_BusCtxt_t *BusCtxt;

    if (Instance >= QUP_INSTANCE_MAX || !QUP_BusCtxt[Instance])
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    BusCtxt = QUP_BusCtxt[Instance];
    if (&BusCtxt->XferCtxt != XferCtxt)
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    XferCtxt->Busy = 1;

    QUP_BusXferConfig(Instance, XferCtxt);

    NVIC_EnableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance));

    if (BusCtxt->Blocking)
    {
        return QUP_BusPollingTransfer(BusCtxt, XferCtxt);
    }

    return QUP_SUCCESS;
}

static void QUP_BusMAbortSync(uint32_t SeCoreBase)
{
    uint32_t TimeoutUs = QUP_CANCEL_TIME_DEFAULT_US;

    REG_OUTF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_CMD_CTRL_REG, M_GENI_CMD_ABORT, 1);

    while (TimeoutUs != 0)
    {
        if (REG_INF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_STATUS, M_CMD_ABORT))
        {
            break;
        }

        qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
        TimeoutUs -= QUP_POLL_INTERVAL_US;
    }
}

static void QUP_BusSAbortSync(uint32_t SeCoreBase)
{
    uint32_t TimeoutUs = QUP_CANCEL_TIME_DEFAULT_US;

    REG_OUTF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_CMD_CTRL_REG, S_GENI_CMD_ABORT, 1);

    while (TimeoutUs != 0)
    {
        if (REG_INF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_STATUS, S_CMD_ABORT))
        {
            break;
        }

        qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
        TimeoutUs -= QUP_POLL_INTERVAL_US;
    }
}

/**
   @brief Cancel main command.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusMCancelSync(QUP_Instance_t Instance)
{
    uint32_t SeCoreBase;
    QUP_BusCtxt_t *BusCtxt;
    uint32_t TimeoutUs = QUP_CANCEL_TIME_DEFAULT_US;

    if (Instance >= QUP_INSTANCE_MAX)
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    BusCtxt = QUP_BusCtxt[Instance];

    if (BusCtxt->BusType < QUP_BUS_SPI_SLAVE)
    {
        uint32_t SclkSel;
        qapi_TSK_Enter_Critical();
        SclkSel = REG_INF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_SEL);
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_SEL, SclkSel & (~BIT(Instance)));
        qapi_TSK_Exit_Critical();
        QUP_BusFreqUpdate(SeCoreBase, 0, 4);
    }

    if (REG_INF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_STATUS, M_GENI_CMD_ACTIVE))
    {
        NVIC_DisableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance));
        BusCtxt->IntPending = 0;
        BusCtxt->XferCtxt.Busy = 0;

        if (BusCtxt->BusType != QUP_BUS_SPI_SLAVE)
        {
            REG_OUTF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_CMD_CTRL_REG, M_GENI_CMD_CANCEL, 1);

            while (TimeoutUs != 0)
            {
                if (REG_INF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_M_IRQ_STATUS, M_CMD_CANCEL))
                {
                    goto done;
                }

                qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
                TimeoutUs -= QUP_POLL_INTERVAL_US;
            }
        }

        QUP_BusMAbortSync(SeCoreBase);
    }

done:
    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        if(BusCtxt->IsUart)
        {
            QUP_DmaFsmReset(Instance, 1);
        }
        else
        {
            QUP_DmaFsmReset(Instance, 1);
            QUP_DmaFsmReset(Instance, 0);
        }
    }

    QUP_GeniSeIrqClear(SeCoreBase);

    return QUP_SUCCESS;
}

/**
   @brief Cancel secondary command.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusSCancelSync(QUP_Instance_t Instance)
{
    uint32_t SeCoreBase;
    QUP_BusCtxt_t *BusCtxt;
    uint32_t TimeoutUs = QUP_CANCEL_TIME_DEFAULT_US;

    if (Instance >= QUP_INSTANCE_MAX)
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    BusCtxt = QUP_BusCtxt[Instance];

    if (REG_INF(SeCoreBase + GENI4_CFG_REG_BASE, SE0_GENI_STATUS, S_GENI_CMD_ACTIVE))
    {
        NVIC_DisableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance));
        BusCtxt->IntPending = 0;
        BusCtxt->XferCtxt.Busy = 0;

        REG_OUTF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_CMD_CTRL_REG, S_GENI_CMD_CANCEL, 1);

        while (TimeoutUs != 0)
        {
            if (REG_INF(SeCoreBase + GENI4_DATA_REG_BASE, SE0_GENI_S_IRQ_STATUS, S_CMD_CANCEL))
            {
                goto done;
            }

            qapi_TMR_Delay_Us(QUP_POLL_INTERVAL_US);
            TimeoutUs -= QUP_POLL_INTERVAL_US;
        }

        QUP_BusSAbortSync(SeCoreBase);
    }

done:
    if (BusCtxt->XferMode == QUP_XFER_DMA)
    {
        QUP_DmaFsmReset(Instance, 0);
    }
    else if(BusCtxt->IsUart)
    {
        /* For uart, need read all data out from Rx FIFO */
        QUP_RxFiFoFlush(Instance);
    }
    QUP_GeniSeIrqClear(SeCoreBase);

    return QUP_SUCCESS;
}

/**
   @brief Initializes the Serial Engine for a serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] BusConfig --  Bus configuration specified by #QUP_BusConfig_t
   @param[in] PrivSize  --  Bus private structure size

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
   QUP_ERROR_MEM_ALLOC
*/
QUP_Status_t QUP_BusOpen(QUP_Instance_t Instance, QUP_BusConfig_t *BusConfig, uint32_t PrivSize)
{
    QUP_BusCtxt_t *BusCtxt;
    uint32_t Size;

    if (!BusConfig || Instance >= QUP_INSTANCE_MAX)
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    if (BusConfig->BusType >= QUP_BUS_MAX ||
        BusConfig->XferMode >= QUP_XFER_MAX ||
        !(BIT(BusConfig->BusType) & QUP_HwInfo[Instance].BusMask))
    {
        return QUP_ERROR_INVALID_PARAM;
    }

#ifdef ENABLE_PERIPHERAL_SPI
    if (QUP_SpiGpioCheck(Instance, BusConfig) != QUP_SUCCESS)
    {
        return QUP_ERROR_BUS_GPIO_ENABLE_FAIL;
    }
#endif

    BusCtxt = QUP_BusCtxt[Instance];
    if (BusCtxt)
    {
        if ((BusCtxt->BusType != BusConfig->BusType)
            || (BusCtxt->Blocking != BusConfig->Blocking)
            || (BusCtxt->XferMode != BusConfig->XferMode)
            || (BusCtxt->NoMuxPriority != BusConfig->NoMuxPriority))
            return QUP_ERROR_INVALID_PARAM;
        else
        	return QUP_SUCCESS;
    }

    Size = sizeof(QUP_BusCtxt_t) + PrivSize;
    BusCtxt = qapi_Malloc(Size);
    if (!BusCtxt)
    {
        return QUP_ERROR_MEM_ALLOC;
    }

    memset(BusCtxt, 0, Size);
    BusCtxt->Instance = Instance;
    BusCtxt->BusType = BusConfig->BusType;
    BusCtxt->XferMode = BusConfig->XferMode;
    BusCtxt->Blocking = !!BusConfig->Blocking;
    BusCtxt->NoMuxPriority = !!BusConfig->NoMuxPriority;
    BusCtxt->IsUart = (BusCtxt->BusType == QUP_BUS_UART
                        || BusCtxt->BusType == QUP_BUS_UART_TX_INVERT
                        || BusCtxt->BusType == QUP_BUS_UART_9BIT_HW
                        || BusCtxt->BusType == QUP_BUS_UART_9BIT_SW);

    QUP_BusCtxt[Instance] = BusCtxt;

    qapi_TSK_Enter_Critical();
    if (Qup_ClkEn == 0)
    {
        /* Enable QUP HCLK, SCLK and CORE CLK. */
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_EN, 0xF);
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_HCLK_EN, 0x1);
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_CORE_CLK_EN, 0x1);
    }
    Qup_ClkEn |= (1 << Instance);
    qapi_TSK_Exit_Critical();

    QUP_HwInit(BusCtxt);

    if (!BusCtxt->Blocking)
    {
        /*Uart interrupts will be processed in ISR intead of TASK */
        if(!BusCtxt->IsUart)
        {
            BusCtxt->Task = qapi_TSK_Create_Task(QUP_BusTask, BusCtxt);
            if (!BusCtxt->Task)
            {
                QUP_BusClose(Instance);
                return QUP_ERROR_MEM_ALLOC;
            }
        }
    }

    return QUP_SUCCESS;
}

/**
   @brief Close the Serial Engine for a serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusClose(QUP_Instance_t Instance)
{
    QUP_BusCtxt_t *BusCtxt;
    uint32_t SeCoreBase;

    if (Instance >= QUP_INSTANCE_MAX || !QUP_BusCtxt[Instance])
    {
        return QUP_ERROR_INVALID_PARAM;
    }

    NVIC_DisableIRQ((IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance));

    BusCtxt = QUP_BusCtxt[Instance];
    SeCoreBase = QUP_HwInfo[Instance].SeCoreBase;
    if (BusCtxt->BusType != QUP_BUS_M2MDMA) {
        QUP_GeniSeIrqEnClear(SeCoreBase);
        QUP_GeniSeIrqClear(SeCoreBase);
        QUP_GeniSeClkSet(SeCoreBase, (QUP_XferMode_t)BusCtxt->XferMode, false);
        QUP_StopGeni(BusCtxt, SeCoreBase);
#ifdef ENABLE_PERIPHERAL_M2MDMA
    } else {
        QUP_HwM2mdmaDeInit(SeCoreBase);
#endif
    }

    if (!BusCtxt->Blocking && BusCtxt->Task)
    {
        qapi_TSK_Delete_Task(BusCtxt->Task);
    }

    qapi_Free(BusCtxt);
    QUP_BusCtxt[Instance] = NULL;

    qapi_TSK_Enter_Critical();
    Qup_ClkEn &= ~(1 << Instance);
    if (Qup_ClkEn == 0)
    {
        /* Disable QUP HCLK and SCLK. */
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_SCLK_EN, 0);
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_HCLK_EN, 0);
        REG_OUTF(PERIPH_MOD_CSR_REG_BASE, CLOCK_CFG, QUP_CORE_CLK_EN, 0);
    }
    qapi_TSK_Exit_Critical();

    return QUP_SUCCESS;
}

/**
   @brief Get the pointer of private structure

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
void *QUP_BusPrivGet(QUP_Instance_t Instance)
{
    return QUP_BusCtxt[Instance] ? QUP_BusCtxt[Instance]->priv : NULL;
}

/**
   @brief Get the pointer of transfer context

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
QUP_XferCtxt_t *QUP_XferCtxtGet(QUP_Instance_t Instance)
{
    return QUP_BusCtxt[Instance] ? &QUP_BusCtxt[Instance]->XferCtxt : NULL;
}

/**
   @brief Get the pointer of private structure

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
QUP_BusCtxt_t *QUP_BusCxtGet(QUP_Instance_t Instance)
{
    return QUP_BusCtxt[Instance];
}

void QUP_IntDispatch(QUP_Instance_t Instance)
{
    QUP_BusCtxt_t *BusCtxt = QUP_BusCtxt[Instance];
    IRQn_Type IRQn = (IRQn_Type)(SE0_IRQn + (IRQn_Type)Instance);


    NVIC_DisableIRQ(IRQn);

    if (!BusCtxt || (!BusCtxt->XferCtxt.Busy && !BusCtxt->IsUart))
    {
        QUP_GeniSeIrqClear(QUP_HwInfo[Instance].SeCoreBase);
    }
    else if (BusCtxt->Blocking)
    {
        BusCtxt->IntPending = 1;
    }
    else
    {
        QUP_BusIsrProcess(BusCtxt, &BusCtxt->XferCtxt);
    }

    if(BusCtxt && BusCtxt->IsUart)
    {
        NVIC_EnableIRQ(IRQn);
    }
}

void SE0_IntHandler(void)
{
    QUP_IntDispatch(QUP_INSTANCE_0);
}

void SE1_IntHandler(void)
{
    QUP_IntDispatch(QUP_INSTANCE_1);
}

void SE2_IntHandler(void)
{
    QUP_IntDispatch(QUP_INSTANCE_2);
}

void SE3_IntHandler(void)
{
    QUP_IntDispatch(QUP_INSTANCE_3);
}

void Qup_AssertFunc()
{
    while(1) {
        Qup_AssertLoop ++;
    }
}

