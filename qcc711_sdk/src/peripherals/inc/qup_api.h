/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qup_api.h
    @brief Qualcomm Universal Peripheral for low-speed protocols (QUPv3)

    QUPv3 is a highly-flexible & programmable module for supporting a wide
    range of serial interfaces (I2C, SPI, UART, etc.).

    A single QUPv3 module can provide up to 4 Serial Interfaces, using its
    internal Serial Engines. The actual configuration is determined by the
    target platform configuration. For the Serial Engine 0&1, the protocol
    supported by each Interface is determined by the firmware loaded to the
    Serial Engine. But for Serial Engine 2&3, which designed as minicore,
    no such firmare loading.

    QUPv3 supports accesses from multiple HW entities in the system. Each
    entity has its own “execution environment” (EE) – a separated address
    space and interrupt line.

    This module provides a unified API for all serial interfaces, which
    wraps for accessing various hardware resource (FIFO, DMA, CLOCK, etc.).
*/

#ifndef __QUP_API_H__
#define __QUP_API_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qapi_status.h"
#include "qapi_task.h"
#include "qapi_heap.h"
#include "qup_hwio.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define BIT(n)                  (1 << (n))

#define QUP_PACKING_CONFIG_NUM   4

/* Return count in buffer.  */
#define QUP_CIRC_CNT(Head, Tail, Size) ((Head - Tail + Size) % Size)

/* Return space available, 0..size-1.  We always leave one free char
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#define QUP_CIRC_SPACE(Head, Tail, Size) QUP_CIRC_CNT((Tail), (Head+1), (Size))

#define QUP_ADDRESS_SRAM_RANGE(Address) \
    ((((uint32_t)Address) > 0x20010000) && (((uint32_t)Address) < 0x20020000))
#define QUP_SRAM_MAP_TO_DMA(Address) ((uint32_t)(Address)-0x7e00000)

#ifdef ENABLE_QUP_FW_COMPRESS
#ifdef ENABLE_PERIPHERAL_I2C
extern const uint16_t  Qup_GeniI2CFw_Len;
#endif
#ifdef ENABLE_PERIPHERAL_SPI
extern const uint16_t Qup_GeniSPIMasterFw_Len;
extern const uint16_t Qup_GeniSPINwireFw_Len;
extern const uint16_t Qup_GeniSPISlaveFw_Len;
#endif
#ifdef ENABLE_PERIPHERAL_UART
extern const uint16_t Qup_GeniUart9bitFw_Len;
extern const uint16_t  Qup_GeniUartFw_Len;
#endif
#define QUP_FW_DECOMPRESS_BUFFER_LEN_MAX 2400
#endif

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
#ifdef ENABLE_QUP_FW_COMPRESS
extern int __iar_lz77_init_single3(void*);
#endif

typedef void (*QUP_Callback_t) (uint32_t Status, void *CallbackCtxt);

typedef enum
{
    QUP_SUCCESS,
    QUP_ERROR,
    QUP_ERROR_INVALID_PARAM,            /**< Invalid input parameters */
    QUP_ERROR_MEM_ALLOC,                /**< Alloc memory failed */
    QUP_ERROR_TRANSFER_BUSY,            /**< Transaction busy */
    QUP_ERROR_TRANSFER_TIMEOUT,         /**< Transaction timeout in blocking mode */
    QUP_ERROR_INPUT_FIFO_UNDER_RUN,     /**< SW reads from an empty RX FIFO */
    QUP_ERROR_INPUT_FIFO_OVER_RUN,      /**< HW writes to a full RX FIFO */
    QUP_ERROR_OUTPUT_FIFO_UNDER_RUN,    /**< SW reads a new word from an empty TX FIFO */
    QUP_ERROR_OUTPUT_FIFO_OVER_RUN,     /**< SW writes a new word into a full TX FIFO */
    QUP_ERROR_COMMAND_OVER_RUN,         /**< A new command is initialized before the previous one done */
    QUP_ERROR_TRANSFER_FORCE_TERMINATED,/**< Command abort or cancel request by SW */
    QUP_ERROR_COMMAND_ILLEGAL,          /**< Command with illegal opcode */
    QUP_ERROR_COMMAND_FAIL,             /**< Command execution has been completed with failure */
    QUP_ERROR_BUS_CLK_ENABLE_FAIL,      /**< Set Clock failed */
    QUP_ERROR_BUS_GPIO_ENABLE_FAIL,     /**< Set GPIO failed */
    QUP_ERROR_DMA_TX_BUS_ERROR,         /**< Bus error during DMA Tx transaction */
    QUP_ERROR_DMA_RX_BUS_ERROR,         /**< Bus error during DMA Rx transaction */
    QUP_ERROR_DMA_TX_RESET_DONE,        /**< Indicates DMA Tx reset completion */
    QUP_ERROR_DMA_RX_RESET_DONE,        /**< Indicates DMA Rx reset completion */
    QUP_ERROR_RX_FIFO_RX_UNDER_READ,    /**< Rx FIFO buffer need read, while there is no free buffer */
} QUP_Status_t;

typedef enum
{
    QUP_INSTANCE_0,                 /**< QUP serial engine 0 */
    QUP_INSTANCE_1,                 /**< QUP serial engine 1 */
    QUP_INSTANCE_2,                 /**< QUP serial engine 2 */
    QUP_INSTANCE_3,                 /**< QUP serial engine 3 */
    QUP_INSTANCE_MAX,
} QUP_Instance_t;

typedef enum
{
   QUP_GENI_SE_FW,                  /**< GENI firmware mode */
   QUP_GENI_SE_MINICORE,            /**< GENI minicore mode */
   QUP_GENI_SE_MAX
} QUP_GeniSeMode_t;

typedef enum
{
    QUP_BUS_SPI_MASTER_3WIRE_9BIT,  /**< SPI master 3 wire 9 bit mode */
    QUP_BUS_SPI_MASTER_4WIRE_8BIT,  /**< SPI master 4 wire 8 bit mode */
    QUP_BUS_SPI_MASTER,             /**< SPI master mode */
    QUP_BUS_SPI_SLAVE,              /**< SPI slave mode */
    QUP_BUS_I2C_MASTER,             /**< I2C master mode */
    QUP_BUS_UART,                   /**< Uart mode */
    QUP_BUS_UART_TX_INVERT,         /**< Uart Tx Signal Invert mode */
    QUP_BUS_UART_9BIT_SW,           /**< Uart 9bit SW mode */
    QUP_BUS_UART_9BIT_HW,           /**< Uart 9bit HW mode */
    QUP_BUS_M2MDMA,                 /**< M2MDMA mode */
    QUP_BUS_MAX,
} QUP_BusType_t;

typedef enum
{
    QUP_XFER_FIFO,                  /**< FIFO mode */
    QUP_XFER_DMA,                   /**< DMA mode */
    QUP_XFER_MAX,
} QUP_XferMode_t;

typedef enum
{
    QUP_XFER_UART_NONE,
    QUP_XFER_UART_TX,               /**< UART TX */
    QUP_XFER_UART_RX,               /**< UART RX */
    QUP_UART_TX_ISR,
    QUP_UART_RX_ISR,
    QUP_XFER_UART_MAX,
} QUP_XferDirection_t;

typedef enum
{
    QUP_BYTE_GRANULARITY_4x8,
    QUP_BYTE_GRANULARITY_2x16,
    QUP_BYTE_GRANULARITY_1x32,
} QUP_ByteGranularity_t;

typedef struct __attribute__ ((packed)) QUP_FwHdr_s
{
    uint32_t Magic;                 /**< = 'SEFW' */
    uint32_t Version;               /**< Structure version number */
    uint32_t CoreVersion;           /**< QUPV3_HW_VERSION */
    uint16_t SerialProtocol;        /**< Programmed into QUP_FW_REVISION */
    uint16_t FwVersion;             /**< Programmed into QUP_FW_REVISION */
    uint16_t CfgVersion;            /**< Programmed into QUP_INIT_CFG_REVISION */
    uint16_t FwSizeInItems;         /**< Number of (uint32_t) QUP_FW_RAM words */
    uint16_t FwOffset;              /**< Byte offset of QUP_FW_RAM array */
    uint16_t CfgSizeInItems;        /**< Number of QUP_FW_CFG index/value pairs */
    uint16_t CfgIdxOffset;          /**< Byte offset of QUP_FW_CFG indexes array */
    uint16_t CfgValOffset;          /**< Byte offset of QUP_FW_CFG values array */
} QUP_FwHdr_t;

typedef struct QUP_PackingConfig_s
{
    uint8_t Start;
    uint8_t Direction;
    uint8_t Length;
    uint8_t Stop;
} QUP_PackingConfig_t;

typedef struct QUP_HwInfo_s
{
    uint32_t CommonBase;            /**< Start address of QUP COMMON */
    uint32_t SeCoreBase;            /**< Start address of QUP serial engine */
    uint32_t CoreFastClk;           /**< Fast frequency of serial clock source */
    uint32_t CoreSlowClk;           /**< Slow frequency of serial clock source */
    uint16_t BusMask;               /**< Bitmap of supported protocol */
    QUP_GeniSeMode_t GeniSeMode;    /**< #QUP_GeniSeMode_t */
} QUP_HwInfo_t;

typedef struct QUP_BusConfig_s
{
    QUP_BusType_t BusType;          /**< #QUP_BusType_t */
    qbool_t Blocking;               /**< true: blocking mode, false: nonblocking mode */
    QUP_XferMode_t XferMode;        /**< #QUP_XferMode_t */
    void *ExtraData;                /**< Extra data for private config */
    qbool_t NoMuxPriority;             /**< Disable SPI Mux priority */
} QUP_BusConfig_t;

/** Master mode only configurations, should same as #qapi_SPI_MXferInfo_s */
typedef struct QUP_SpiMXferInfo_s
{
    uint16_t Flags;          /**< Master transaction flags */
#define QUP_SPI_XFER_LOOPBACK       BIT(0) /**< Loopback test, should not enabled in mission mode */
#define QUP_SPI_XFER_CPOL           BIT(1) /**< CPOL determines the polarity of the clock */
#define QUP_SPI_XFER_CPHA           BIT(2) /**< CPHA determines the timing of the data bits relative to the clock pulses */
#define QUP_SPI_XFER_CSPOLARITY     BIT(3) /**< During idle state CS line is held high, default low */
#define QUP_SPI_XFER_CSTOGGLE       BIT(4) /**< CS line will toggle between consecutive data frames */
#define QUP_SPI_XFER_FWORD_COMMAND  BIT(5) /**< First word is command, only used in 3-wire 9-bit and 4-wire 8-bit mode */
#define QUP_SPI_XFER_RWORD_COMMAND  BIT(6) /**< Remaining word is command, only used in 3-wire 9-bit and 4-wire 8-bit mode */
#define QUP_SPI_XFER_LSB_FIRST      BIT(7) /**< Direction of bits-on-wire */
#define QUP_SPI_XFER_MUL_CS         BIT(9) /**< Multiple cs line for 3wire/4wire mode */
    uint8_t CsLine;          /**< Slave select line, up to 2 slaves */
    uint8_t BitsPerWord;     /**< Selects the data frame length, valid range from 4 to 32 */
    uint16_t CsClkDelay;     /**< Num of clk cycles to wait after asserting CS before starting transfer */
    uint16_t InterWordDelay; /**< Num of clk cycles to wait between SPI words */
    uint32_t FreqHz;         /**< SPI clock frequency, 1Hz ~ 16MHz */
} QUP_SpiMXferInfo_t;

/** Slave mode only configurations, should same as #qapi_SPI_SXferInfo_s */
typedef struct QUP_SpiSXferInfo_s
{
    uint8_t LsbFirst;     /**< Direction of bits-on-wire */
    uint32_t BitsPerWord; /**< Selects the data frame lenght, valid range from 4 to 32 */
} QUP_SpiSXferInfo_t;

typedef union QUP_SpiXferInfo_s
{
    QUP_SpiMXferInfo_t Master;
    QUP_SpiSXferInfo_t Slave;
} QUP_SpiXferInfo_t;

typedef struct QUP_I2cXferInfo_s
{
    uint8_t ClkDiv;
    uint8_t THigh;
    uint8_t TLow;
    uint8_t TCycle;
    uint32_t SlaveAddress;
    uint32_t SlaveMaxClockStretchUs;
    uint32_t NoiseReject;
    uint32_t DescFlags;
    uint32_t Delay;
    uint32_t TxPackingCfg0;
    uint32_t TxPackingCfg1;
    uint32_t RxPackingCfg0;
    uint32_t RxPackingCfg1;
} QUP_I2cXferInfo_t;

typedef struct QUP_UartXferInfo_s
{
    //TODO add UART Xfer information here
    uint32_t BitsPerChar:4;
    uint32_t Parity:4;
    uint32_t NumStopBits:4;
    uint32_t Loopback:1;
    uint32_t FlowCtrl:1;

    uint32_t RxStaleCnt;
    uint32_t ClkDivider;
    uint8_t RxAddress;
    uint8_t TxAddress;
    uint8_t BytesPerWord;
} QUP_UartXferInfo_t;

typedef struct QUP_CircBuf_s
{
    uint8_t* Buf;
    int32_t Head;
    int32_t Tail;
    int32_t Size;
}QUP_CircBuf_t;

/** Transfer data and configurations, prepared by protocol layer */
typedef struct QUP_XferCtxt_s
{
    uint8_t *TxBuf;                 /**< Tx buffer */
    uint32_t TxLen;                 /**< Tx data length */
    uint32_t TxedLen;               /**< Txed data length for uart tx callback */
    uint32_t TxCnt;                 /**< Tx byte counter */
    uint8_t *RxBuf;                 /**< Rx buffer */
    uint32_t RxLen;                 /**< Rx data length */
    uint32_t RxCnt;                 /**< Rx byte counter */
    uint32_t UnReadFlag;            /**< In Uart FIFO mode, the ISR will not triggered until read all data */
    QUP_CircBuf_t *RxCircBuf;       /**< Circle rx buffer for UART FIFO mode */
    QUP_CircBuf_t *TxCircBuf;       /**< Circle tx buffer for UART */

    uint16_t TxWaterMark;           /**< TxWaterMark */
    uint16_t RxWaterMark;           /**< RxWaterMark */
    uint32_t CmdOpcode;             /**< Opcode for PERIPH_SEn_GENI_M_CMD0 */
    uint32_t CmdParam;              /**< Param for PERIPH_SEn_GENI_M_CMD0 */
    uint32_t SCmdOpcode;            /**< Opcode for PERIPH_SEn_GENI_S_CMD0 */
    uint32_t SCmdParam;             /**< Param for PERIPH_SEn_GENI_S_CMD0 */

    uint32_t ClkChanged:1;          /**< Set when transfer rate is changed */
    uint32_t DmaTxDone:1;           /**< Indicate DMA Tx done */
    uint32_t DmaRxDone:1;           /**< Indicate DMA Rx done */
    uint32_t Busy:1;                /**< Clear once the whole transfer is finished */
    uint32_t TxBusy:1;              /**< Indicate Uart is in tx state */

    union
    {
#ifdef ENABLE_PERIPHERAL_SPI
        QUP_SpiXferInfo_t  Spi;     /**< SPI transfer configurations */
#endif
#ifdef ENABLE_PERIPHERAL_I2C
        QUP_I2cXferInfo_t  I2c;     /**< I2C transfer configurations */
#endif
#ifdef ENABLE_PERIPHERAL_UART
        QUP_UartXferInfo_t Uart;    /**< UART transfer configurations */
#endif
    } XferInfo;

    QUP_Status_t Status;            /**< Transfer result */
    QUP_Callback_t CFn;             /**< callback, registered from protocol layer */
    QUP_Callback_t TxCFn;           /**< tx callback for uart*/
    void *CCtxt;                    /**< Context of the callback */
} QUP_XferCtxt_t;

//#define BUS_ERROR_STATS
#ifdef BUS_ERROR_STATS
typedef struct QUP_BusErrorStat_s
{
    uint32_t  FrameErr;
    uint32_t  ParityErr;
    uint32_t  Break;
    uint32_t  CmdOverRun;
    uint32_t  RxFifoWr;
    uint32_t  FifoSErrs;            /**< total errors count in main interrupt status */
    uint32_t  FifoMErrs;            /**< total errors count in seconday interrupt status */
    uint32_t  IsrErr;

    uint32_t  RxDmaSbe;
    uint32_t  RxDmaRst;
    uint32_t  RxDmaCntErr;
    uint32_t  TxDmaSbe;
    uint32_t  TxDmaRst;
    uint32_t  DmaCmdFail;
    uint32_t  OtherDmaErr;
    uint32_t  RxDmaErrs;            /**< total errors count in Rx DMA status */
    uint32_t  TxDmaErrs;            /**< total errors count in Tx DMA status */

}QUP_BusErrorStat_t;
#endif

typedef struct QUP_BusCtxt_s
{
    uint8_t Instance;               /**< Serial Engine index, #QUP_Instance_t */
    uint8_t BusType;                /**< Protocol, #QUP_BusType_t */
    uint8_t IsUart;                 /**< Serial Engine work as Uart */
    uint8_t XferMode;               /**< Transfer mode, #QUP_XferMode_t */
    uint8_t Blocking;               /**< 1: blocking mode, 0: nonblocking mode */
    uint8_t NoMuxPriority;          /**< Disable SPI Mux priority */

    uint8_t TxFifoDepth;            /**< Number of Tx FIFO entries */
    uint8_t RxFifoDepth;            /**< Number of Rx FIFO entries */
    uint8_t TxFifoWidth;            /**< Width of each Tx FIFO entry */

    uint8_t IntPending;             /**< Interrupt pending if non-zero  */

    QUP_XferCtxt_t XferCtxt;        /**< Current transfer context */

    qapi_TSK_Handle_t Task;         /**< Task for Tx/Rx */
#ifdef BUS_ERROR_STATS
    QUP_BusErrorStat_t ErrStats;    /**< Bus error statistics */
#endif
    char priv[0];                   /**< private structure for protocol layer */
} QUP_BusCtxt_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

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
QUP_Status_t QUP_BusOpen(QUP_Instance_t Instance, QUP_BusConfig_t *BusConfig, uint32_t PrivSize);

/**
   @brief Close the Serial Engine for a serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusClose(QUP_Instance_t Instance);

/**
   @brief Performs a data transfer over the serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt

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
QUP_Status_t QUP_BusTransfer(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt);

/**
   @brief Cancel main command.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusMCancelSync(QUP_Instance_t Instance);

/**
   @brief Cancel secondary command.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t

   @return
   QUP_SUCCESS
   QUP_ERROR
   QUP_ERROR_INVALID_PARAM
*/
QUP_Status_t QUP_BusSCancelSync(QUP_Instance_t Instance);

/**
   @brief Config the xfer parameters(interrupt, DMA/FIFO, related protocol configurations) for a serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt
*/
void QUP_BusXferConfig(QUP_Instance_t Instance,  QUP_XferCtxt_t *XferCtxt);

/**
   @brief Get the pointer of private structure

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
void *QUP_BusPrivGet(QUP_Instance_t Instance);

/**
   @brief Get the pointer of transfer contxt

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
QUP_XferCtxt_t *QUP_XferCtxtGet(QUP_Instance_t Instance);

/**
   @brief Get the pointer of a QUP Bus Context structure

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
QUP_BusCtxt_t *QUP_BusCxtGet(QUP_Instance_t Instance);

/**
   @brief Return count up to the end of the buffer.
*/
static  inline int32_t Qup_CircCntToEnd(int32_t Head, int32_t Tail, int32_t Size)
{
    int32_t End;
    int32_t N;

    End = Size - Tail;
    N   = (Head + End) % Size;

    return(N < End ? N : End);
}

/**
   @brief Return space available up to the end of the buffer.
*/
static inline int32_t Qup_CircSpaceToEnd(int32_t Head, int32_t Tail, int32_t Size)
{
    int32_t End;
    int32_t N;

    End = Size - 1 - Head;
    N  = ((End + Tail) % Size);

    return(N <= End ? N : End+1);
}

#ifdef ENABLE_PERIPHERAL_SPI
/**
   @brief Get the pointer of a QUP SPI Master FW image
*/
void *Qup_GeniGetSPIMasterFw(void);

/**
   @brief Get the pointer of a QUP SPI Slave FW image
*/
void *Qup_GeniGetSPISlaveFw(void);

/**
   @brief Get the pointer of a QUP SPI Nwire FW image
*/
void *Qup_GeniGetSPINwireFw(void);
#endif

#ifdef ENABLE_PERIPHERAL_I2C
/**
   @brief Get the pointer of a QUP I2C FW image
*/
void *Qup_GeniGetI2CFw(void);
#endif

#ifdef ENABLE_PERIPHERAL_UART
/**
   @brief Config the UART parameters, for uart, the configuration is one time set.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt
*/
void QUP_UartXferConfig(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt);

/**
   @brief Clear uart rx enable irq when there is no available buffer in FIFO mode.

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
*/
void QUP_UartClearRxIrq(QUP_Instance_t Instance);

/**
   @brief Setup uart data transmit over the serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
   QUP_ERROR_TRANSFER_BUSY

*/
QUP_Status_t QUP_UartStartTx(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt);

/**
   @brief Setup uart data transmit over the serial interface

   @param[in] Instance  --  Serial Engine index specified by #QUP_Instance_t
   @param[in] XferCtxt

   @return
   QUP_SUCCESS
   QUP_ERROR_INVALID_PARAM
   QUP_ERROR_TRANSFER_TIMEOUT
   QUP_ERROR_TRANSFER_BUSY
*/
QUP_Status_t QUP_UartStartRx(QUP_Instance_t Instance, QUP_XferCtxt_t *XferCtxt);

/**
   @brief Get the pointer of a QUP UART 9bit HW mode FW image
*/
void *Qup_GeniGetUart9bitFw(void);

/**
   @brief Get the pointer of a QUP UART Legacy, 9bit SW mode and Tx Invert FW image
*/
void *Qup_GeniGetUartFw(void);

#endif

/**
   @brief Reset DMA

   @param[in] Instance      Serial Engine index specified by #QUP_Instance_t
   @param[in] Tx            DMA TX, 1: TX, 0: RX.
*/
void QUP_DmaFsmReset(QUP_Instance_t Instance, qbool_t Tx);

/**
   @brief Qup Asseert Utility Function
*/
void Qup_AssertFunc();


#endif
