/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_spi.h
   @brief Serial Peripheral Interface (SPI)
*/

/** @addtogroup qapi_peripherals_spi

  The SPI module uses an SPI full-duplex communication bus to interface
  peripherals in several communication modes configured by the client
  software. The SPI driver API provides a high level interface to expose the
  capabilities of the SPI.

  Typical usage:
  - qapi_SPI_Open()      -- Opens an SPI instance for master or slave.
  - qapi_SPI_Transfer()  -- Generic transfer API to perform a transfer on the
                            SPI bus.
  - qapi_SPI_Close()     -- Destroys all objects for a specified instance.

  SPI transfers:
  - SPI transfers support blocking and nonblocking modes, and can enable or
    disable DMA for both modes.
  - For nonblocking mode, buffers passed by the client must be resident.
    Therefore, buffers can only be freed when the client specified callback is
    invoked.
  - If the DMA is enabled, both Tx and Rx buffers should be uncached RAM
    addresses. There is no address or length alignment requirement.
  - The SPI master supports all four SPI modes. This can be changed per open
    instance.
  - The driver supports parallel transfers on different SPI instances.

  @note1hang The QUP SPI Slave implements a generic SPI slave interface without
             data flow or data integrity checks. HLOS requires implementation
             of a robust protocol on the SPI slave interface.

  @note1hang Before using module APIs, qapi_PWR_Set_Module_State
              (#QAPI_PWR_MODULE_PERIPHERAL_E, #QAPI_PWR_STATE_ACTIVE_E,
              #QAPI_PWR_STATE_ACTIVE_E) must be called.
*/

#ifndef __QAPI_SPI_H__
#define __QAPI_SPI_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_spi
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QAPI_SPI_FREQ_MIN            1        /**< 1&nbsp;Hz. */
#define QAPI_SPI_FREQ_MAX            16000000 /**< 16&nbsp;MHz. */
#define QAPI_SPI_BITSPERWORD_MIN     4        /**< 4&nbsp;bits. */
#define QAPI_SPI_BITSPERWORD_MAX     32       /**< 32&nbsp;bits. */
#define QAPI_SPI_SLAVES_MAX          2        /**< 2&nbsp;slaves. */


/** SPI Master only transaction flags */
#define QAPI_SPI_XFER_LOOPBACK         (1 << 0) /**< Loopback test - should not be enabled in Mission mode. */
#define QAPI_SPI_XFER_CPOL             (1 << 1) /**< CPOL determines the polarity of the clock. */
#define QAPI_SPI_XFER_CPHA             (1 << 2) /**< CPHA determines the timing of the data bits relative to clock pulses. */
#define QAPI_SPI_XFER_CSPOLARITY       (1 << 3) /**< During idle state, CS line is held high, default low. */
#define QAPI_SPI_XFER_CSTOGGLE         (1 << 4) /**< CS line toggles between consecutive data frames. */
#define QAPI_SPI_XFER_FWORD_COMMAND    (1 << 5) /**< First word is command, only used in 3-wire 9-bit, and 4-wire 8-bit mode. */
#define QAPI_SPI_XFER_RWORD_COMMAND    (1 << 6) /**< Remaining word is command, only used in 3-wire 9-bit, and 4-wire 8-bit mode. */
#define QAPI_SPI_XFER_LSB_FIRST        (1 << 7) /**< Direction of bits-on-wire. */
#define QAPI_SPI_XFER_LOW_RATE         (1 << 8) /**< Indicates a low bit rate. Valid when Tx only, nonblocking, frequency < 64, and BitsPerWord is 8. */
#define QAPI_SPI_XFER_NWIRE_MUL_CS     (1 << 9) /**< Multiple cs. Only valid for 3wire9bit or 4wire8bit mode */

#define QAPI_SPI_XFER_MODE0            0                                          /**< SPI transfer mode 0. */
#define QAPI_SPI_XFER_MODE1            (QAPI_SPI_XFER_CPHA)                       /**< SPI transfer mode 1. */
#define QAPI_SPI_XFER_MODE2            (QAPI_SPI_XFER_CPOL)                       /**< SPI transfer mode 2. */
#define QAPI_SPI_XFER_MODE3            (QAPI_SPI_XFER_CPOL | QAPI_SPI_XFER_CPHA)  /**< SPI transfer mode 3. */

#define QAPI_SPI_ERROR                              __QAPI_ERROR(QAPI_MOD_SPI, 1)  /**< Common error. */
#define QAPI_SPI_ERROR_INVALID_PARAM                __QAPI_ERROR(QAPI_MOD_SPI, 2)  /**< Invalid input parameters. */
#define QAPI_SPI_ERROR_MEM_ALLOC                    __QAPI_ERROR(QAPI_MOD_SPI, 3)  /**< No enough memory. */
#define QAPI_SPI_ERROR_TRANSFER_BUSY                __QAPI_ERROR(QAPI_MOD_SPI, 4)  /**< Transaction bus busy. */
#define QAPI_SPI_ERROR_TRANSFER_TIMEOUT             __QAPI_ERROR(QAPI_MOD_SPI, 5)  /**< Transaction timeout in Blocking mode. */
#define QAPI_SPI_ERROR_INPUT_FIFO_UNDER_RUN         __QAPI_ERROR(QAPI_MOD_SPI, 6)  /**< Software reads from an empty Rx FIFO. */
#define QAPI_SPI_ERROR_INPUT_FIFO_OVER_RUN          __QAPI_ERROR(QAPI_MOD_SPI, 7)  /**< Hardware writes to a full Rx FIFO. */
#define QAPI_SPI_ERROR_OUTPUT_FIFO_UNDER_RUN        __QAPI_ERROR(QAPI_MOD_SPI, 8)  /**< Software reads a new word from an empty Tx FIFO. */
#define QAPI_SPI_ERROR_OUTPUT_FIFO_OVER_RUN         __QAPI_ERROR(QAPI_MOD_SPI, 9)  /**< Software writes a new word into a full Tx FIFO. */
#define QAPI_SPI_ERROR_COMMAND_OVER_RUN             __QAPI_ERROR(QAPI_MOD_SPI, 10) /**< A new command is initialized before the previous one is complete. */
#define QAPI_SPI_ERROR_TRANSFER_FORCE_TERMINATED    __QAPI_ERROR(QAPI_MOD_SPI, 11) /**< Command abort or cancel request by software. */
#define QAPI_SPI_ERROR_COMMAND_ILLEGAL              __QAPI_ERROR(QAPI_MOD_SPI, 12) /**< Command with illegal opcode. */
#define QAPI_SPI_ERROR_COMMAND_FAIL                 __QAPI_ERROR(QAPI_MOD_SPI, 13) /**< Command execution has been completed with a failure. */
#define QAPI_SPI_ERROR_BUS_CLK_ENABLE_FAIL          __QAPI_ERROR(QAPI_MOD_SPI, 14) /**< Set the clock failed. */
#define QAPI_SPI_ERROR_BUS_GPIO_ENABLE_FAIL         __QAPI_ERROR(QAPI_MOD_SPI, 15) /**< Set the GPIO failed. */
#define QAPI_SPI_ERROR_DMA_TX_BUS_ERROR             __QAPI_ERROR(QAPI_MOD_SPI, 16) /**< Bus error during a DMA Tx transaction. */
#define QAPI_SPI_ERROR_DMA_RX_BUS_ERROR             __QAPI_ERROR(QAPI_MOD_SPI, 17) /**< Bus error during a DMA Rx transaction. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
  @brief Prototype for the function called to signal transfer completion.

  This function is used to register a callback notification function.
  CallbackCtxt is a user-specified context object passed untouched by the
  SPI driver, to identify the transfer completion instance that is
  being signaled.

  @param[in] Status         Status of current transfer.
  @param[in] CallbackCtxt   User-specified parameter for the transfer callback.
*/
typedef void (*qapi_SPI_CB_t) (uint32_t Status, void *CallbackCtxt);

/**
  @brief SPI instance enumeration.

  This enumeration lists the possible SPI instances, indicating the hardware SPI
  controller used for the current SPI transaction.
*/
typedef enum
{
    QAPI_SPI_INSTANCE_SE0_E, /**< SPI controller 0. */
    QAPI_SPI_INSTANCE_SE1_E, /**< SPI controller 1. */
    QAPI_SPI_INSTANCE_MAX_E  /**< SPI controller maximum instance. */
} qapi_SPI_Instance_t;

/**
  @brief SPI mode enumeration.

  This enumeration lists the possible SPI mode, including standard 4-wire SPI
  mode, and non-standard 3-wire mode. These modes introduce an extra 'D/C#' pin
  (for 4-wire 8-bit mode) or an extra bit (for 3-wire 9-bit mode) to indicate the
  transaction is data or a command.
*/
typedef enum
{
    QAPI_SPI_MODE_MASTER_3WIRE_9BIT_E, /**< 3 wire 9-bit Master mode, SE0 only. */
    QAPI_SPI_MODE_MASTER_4WIRE_8BIT_E, /**< 4 wire 8-bit Master mode, SE0 only. */
    QAPI_SPI_MODE_MASTER_E,            /**< Master mode. */
    QAPI_SPI_MODE_SLAVE_E,             /**< Slave mode.  */
    QAPI_SPI_MODE_MAX_E                /**< Maximum mode.  */
} qapi_SPI_Mode_t;

/** Configurations needed by qapi_SPI_Open(). */
typedef struct qapi_SPI_Config_s
{
    qapi_SPI_Mode_t Mode;           /**< #qapi_SPI_Mode_t. */
    qbool_t         Blocking;       /**< TRUE: blocking mode, FALSE: nonblocking mode. */
    qbool_t         Dma;            /**< TRUE: DMA, FALSE: FIFO. */
    qbool_t         NoMuxPriority;  /**< TRUE: enable SPI Mux Priority, FALSE: disable Mux Priority. */
} qapi_SPI_Config_t;

/**
  @brief SPI Master only transfer configurations.

  This structure defines the Master only transfer configurations for different
  slaves. One Master may connect to multiple Slaves, which have their own
  configurations.
*/
typedef struct qapi_SPI_MXferInfo_s
{
    uint16_t Flags;          /**< Master transaction flags: QAPI_SPI_XFER_XXX. */
    uint8_t CsLine;          /**< Slave select line. Up to 2 slaves. */
    uint8_t BitsPerWord;     /**< Selects the data frame length. Valid range from 4 to 32. */
    uint16_t CsClkDelay;     /**< Number of clock cycles to wait after asserting CS, before starting a transfer. */
    uint16_t InterWordDelay; /**< Number of clock cycles to wait between SPI words. */
    uint32_t FreqHz;         /**< SPI clock frequency. Valid rang from 1&nbsp;Hz to 16&nbsp;MHz, and must be a factor of 32&nbsp;K or 32&nbsp;M. */
} qapi_SPI_MXferInfo_t;

/** SPI Slave only transfer configurations. */
typedef struct qapi_SPI_SXferInfo_s
{
    uint8_t LsbFirst;     /**< Direction of the bits-on-wire. */
    uint32_t BitsPerWord; /**< Selects the data frame length. Valid range from 4 to 32. */
} qapi_SPI_SXferInfo_t;

/** This union structure wraps the transfer configurations for Master and Slave. */
typedef union qapi_SPI_XferInfo_s
{
    qapi_SPI_MXferInfo_t Master; /**< #qapi_SPI_MXferInfo_t. */
    qapi_SPI_SXferInfo_t Slave;  /**< #qapi_SPI_SXferInfo_t. */
} qapi_SPI_XferInfo_t;

/**
  @brief SPI transfer context.

  This structure wraps all elements for the current transfer. It may be queued if the SPI controller is busy, 
  therefore it should be memory resident in nonblocking Transaction mode.
*/
typedef struct qapi_SPI_Transfer_s
{
    void *TxBuf;                    /**< Data to be written, or NULL. TxBuf means it is a Tx only transfer.
                                         If TxBuf and RxBuf are both set, it is a full-duplex transfer. If TxBuf is
                                         a pointer to a Flash mapping address, it will only work with a 32-bit aligned
                                         address in DMA mode. */
    void *RxBuf;                    /**< Data to be read, or NULL. RxBuf means it is an Rx only transfer */
    uint32_t TxLen;                 /**< Size of TxBuf. Ignored if TxBuf is NULL. */
    uint32_t RxLen;                 /**< Size of RxBuf. Ignored if RxBuf is NULL. */

    qapi_SPI_XferInfo_t XferInfo;   /**< #qapi_SPI_XferInfo_t. */

    qapi_SPI_CB_t CallbackFn;       /**< Callback. Only used in nonblocking mode. */
    void *CallbackCtxt;             /**< Context of the callback. */
} qapi_SPI_Transfer_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the SPI controller.

   This function initializes internal data structures and associated
   static data. In any operating mode, this function should be called before
   calling any other SPI controller API.

   @param[in] Instance  SPI instance specified by #qapi_SPI_Instance_t.
   @param[in] Config    SPI configuration specified by #qapi_SPI_Config_t.

   @return
   QAPI_OK --  Module was initialized successfully. \n
   QAPI_SPI_ERROR_INVALID_PARAM --  Invalid instance or handle parameter. \n
   QAPI_SPI_ERROR_MEM_ALLOC --  Could not allocate space for driver structures.
*/
qapi_Status_t qapi_SPI_Open(qapi_SPI_Instance_t Instance, qapi_SPI_Config_t *Config);

/**
   @brief Performs a data transfer over the SPI bus.

   This function performs transfer over the SPI bus. Transfers can be one-directional
   or bi-directional. If the callback is set, it will be invoked on transfer
   completion.

   @param[in] Instance  The instance opened by qapi_SPI_Open().
   @param[in] Transfer  Pointer to the SPI transfer structure.

   @return
   QAPI_OK -- SPI master transfer successful. \n
   QAPI_SPI_ERROR_INVALID_PARAM -- One or more parameters are invalid. \n
   QAPI_SPI_ERROR_TRANSFER_BUSY -- SPI core is busy. \n
   QAPI_SPI_ERROR_TRANSFER_TIMEOUT -- Transfer timed out. \n
   QAPI_SPI_ERROR_INPUT_FIFO_UNDER_RUN -- Software reads from an empty Rx FIFO. \n
   QAPI_SPI_ERROR_INPUT_FIFO_OVER_RUN -- Hardware writes to a full Rx FIFO. \n
   QAPI_SPI_ERROR_OUTPUT_FIFO_UNDER_RUN -- Software reads a new word from an empty Tx FIFO. \n
   QAPI_SPI_ERROR_OUTPUT_FIFO_OVER_RUN -- Software writes a new word into a full Tx FIFO. \n
   QAPI_SPI_ERROR_COMMAND_OVER_RUN -- A new command is initialized before the previous one is complete. \n
   QAPI_SPI_ERROR_TRANSFER_FORCE_TERMINATED -- Command abort or cancel request by software. \n
   QAPI_SPI_ERROR_COMMAND_ILLEGAL -- Command with an illegal opcode. \n
   QAPI_SPI_ERROR_COMMAND_FAIL -- Command execution has been completed with a failure. \n
   QAPI_SPI_ERROR_DMA_TX_BUS_ERROR -- Bus error during a DMA Tx transaction. \n
   QAPI_SPI_ERROR_DMA_RX_BUS_ERROR -- Bus error during a DMA Rx transaction.
*/
qapi_Status_t qapi_SPI_Transfer(qapi_SPI_Instance_t Instance, qapi_SPI_Transfer_t *Transfer);

/**
   @brief Closes the SPI controller.

   This function cancels all pending transfers, frees all internal data
   structures, and closes the SPI master interface.

   @param[in] Instance  The instance opened by qapi_SPI_Open().

   @return
   QAPI_OK -- SPI driver closed successfully. \n
   QAPI_SPI_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_SPI_Close(qapi_SPI_Instance_t Instance);

/** @} */ /* end_addtogroup qapi_peripherals_spi */

#endif

