/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_uart.h
   @brief Universal Asynchronous Receiver/Transmitter (UART).
   
*/

/** @addtogroup qapi_peripherals_uart
  The UART module provides access to a universal asynchronous receiver
  transmitter (UART) hardware communication device where data format and
  transmission speeds are configurable. The Qualcomm UART API provides a
  high-level interface to expose the capabilities of the UART.

  Typical usage:
  - qapi_UART_Open()          -- Opens a UART instance.
  - qapi_UART_Transmit()      -- Transmits data from a given buffer.
  - qapi_UART_Receive()       -- Receives data from UART driver.
  - qapi_UART_Set_TRAddress() -- Sets the transmit/receive address, and is only
                                 available in 9-bit hardware mode.
  - qapi_UART_Get_TRAddress() -- Gets the transmit/receive address, and is only
                                 available in 9-bit hardware mode.
  - qapi_UART_Close()         -- Destroys all objects for a specified instance.

  @note1hang Before using module APIs, qapi_PWR_Set_Module_State
             (#QAPI_PWR_MODULE_PERIPHERAL_E, #QAPI_PWR_STATE_ACTIVE_E,
             #QAPI_PWR_STATE_ACTIVE_E) must be called.
*/

#ifndef __QAPI_UART_H__
#define __QAPI_UART_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_uart
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QAPI_UART_ERROR                              __QAPI_ERROR(QAPI_MOD_UART, 1)  /**< A common error. */
#define QAPI_UART_ERROR_INVALID_PARAM                __QAPI_ERROR(QAPI_MOD_UART, 2)  /**< Invalid input parameters. */
#define QAPI_UART_ERROR_MEM_ALLOC                    __QAPI_ERROR(QAPI_MOD_UART, 3)  /**< Not enough memory. */
#define QAPI_UART_ERROR_TRANSMIT_BUSY                __QAPI_ERROR(QAPI_MOD_UART, 4)  /**< UART transmit is ongoing. */
#define QAPI_UART_ERROR_INPUT_FIFO_UNDER_RUN         __QAPI_ERROR(QAPI_MOD_UART, 6)  /**< Software is reading from an empty Rx FIFO. */
#define QAPI_UART_ERROR_INPUT_FIFO_OVER_RUN          __QAPI_ERROR(QAPI_MOD_UART, 7)  /**< Hardware is writing to a full Rx FIFO. */
#define QAPI_UART_ERROR_OUTPUT_FIFO_UNDER_RUN        __QAPI_ERROR(QAPI_MOD_UART, 8)  /**< Software is reading a new word from an empty Tx FIFO. */
#define QAPI_UART_ERROR_OUTPUT_FIFO_OVER_RUN         __QAPI_ERROR(QAPI_MOD_UART, 9)  /**< Software is writing a new word to a full Tx FIFO. */
#define QAPI_UART_ERROR_COMMAND_OVER_RUN             __QAPI_ERROR(QAPI_MOD_UART, 10) /**< A new command was initialized before the previous command was completed. */
#define QAPI_UART_ERROR_TRANSFER_FORCE_TERMINATED    __QAPI_ERROR(QAPI_MOD_UART, 11) /**< A command abort or cancel request by software. */
#define QAPI_UART_ERROR_COMMAND_ILLEGAL              __QAPI_ERROR(QAPI_MOD_UART, 12) /**< A command with an illegal opcode. */
#define QAPI_UART_ERROR_COMMAND_FAIL                 __QAPI_ERROR(QAPI_MOD_UART, 13) /**< Command execution has completed with failure/s. */
#define QAPI_UART_ERROR_BUS_CLK_ENABLE_FAIL          __QAPI_ERROR(QAPI_MOD_UART, 14) /**< Setting the clock failed. */
#define QAPI_UART_ERROR_BUS_GPIO_ENABLE_FAIL         __QAPI_ERROR(QAPI_MOD_UART, 15) /**< Setting the GPIO failed. */
#define QAPI_UART_ERROR_DMA_TX_BUS_ERROR             __QAPI_ERROR(QAPI_MOD_UART, 16) /**< A bus error occured during a DMA Tx transaction. */
#define QAPI_UART_ERROR_DMA_RX_BUS_ERROR             __QAPI_ERROR(QAPI_MOD_UART, 17) /**< A bus error occured during a DMA Rx transaction. */
#define QAPI_UART_ERROR_DMA_TX_RESET_DONE            __QAPI_ERROR(QAPI_MOD_UART, 18) /**< Indicates DMA Tx reset completion. */
#define QAPI_UART_ERROR_DMA_RX_RESET_DONE            __QAPI_ERROR(QAPI_MOD_UART, 19) /**< Indicates DMA Rx reset completion. */
#define QAPI_UART_ERROR_NO_DATA_TO_TRANSFER          __QAPI_ERROR(QAPI_MOD_UART, 20) /**< No data is available to transmit or receive. */
#define QAPI_UART_ERROR_NO_AVAILABLE_BUF             __QAPI_ERROR(QAPI_MOD_UART, 21) /**< No internal buffer is available for data. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
  @brief UART transmit/receive operation callback type.

  This callback notification function is registered in qapi_UART_Open().
  The callback is called when a transmit/receive operation is complete. The Tx
  callback could be missed if it is not necessary. The Rx callback notifies the user task
  to receive data.

  @param[in] Status        Result of the current Tx/Rx operation.
                           Supported values:
                           - #QAPI_OK
                           - #QAPI_UART_ERROR_INPUT_FIFO_UNDER_RUN
                           - #QAPI_UART_ERROR_INPUT_FIFO_OVER_RUN
                           - #QAPI_UART_ERROR_OUTPUT_FIFO_OVER_RUN
                           - #QAPI_UART_ERROR_OUTPUT_FIFO_UNDER_RUN
                           - #QAPI_UART_ERROR_COMMAND_OVER_RUN
                           - #QAPI_UART_ERROR_COMMAND_ILLEGAL
                           - #QAPI_UART_ERROR_COMMAND_FAIL
                           - #QAPI_UART_ERROR_DMA_TX_BUS_ERROR
                           - #QAPI_UART_ERROR_DMA_RX_BUS_ERROR
                           - #QAPI_UART_ERROR_DMA_TX_RESET_DONE
                           - #QAPI_UART_ERROR_DMA_RX_RESET_DONE
                           - #QAPI_UART_ERROR_TRANSFER_FORCE_TERMINATED @vertspace{-26}
  @param[in] Length        Transmit data length or received data length.
  @param[in] CallbackCtxt  User-specified parameter.

  @newpage
*/
typedef void(*qapi_UART_CB_t)(uint32_t Status, uint32_t Length, void *CallbackCtxt);

/** @brief Lists possible UART instances.

    This enumeration indicates which hardware engine instance is used for which
    UART operation. Following are the Serial Engine (SE) supported protocols where
    X  = supported protocol.

    @verbatim
    |--------|-------|-------|-------|-------|-------|------|-------|------|------|
    |SE Index|  SPI  |  SPI  |SPI Std|SPI Std|  I2C  | UART |UART Tx| UART | M2M  |
    |        |Master |Master |Master |Slave  |Master | UART |Invert |9-bit | DMA  |
    |        |3-wire |4-wire |       |       |       |      |       |      |      |
    |        | 9-bit | 8-bit |       |       |       |      |       |      |      |
    |--------|-------|-------|-------|-------|-------|------|-------|------|------|
    |   0    |   X   |   X   |   X   |   X   |   X   |  X   |   X   |  X   |  -   |
    |   1    |   -   |   -   |   X   |   X   |   X   |  X   |   X   |  X   |  -   |
    |   2    |   -   |   -   |   -   |   -   |   X   |  X   |   -   |  -   |  X   |
    |   3    |   -   |   -   |   -   |   -   |   X   |  -   |   -   |  -   |  X   |
    |--------|-------|-------|-------|-------|-------|------|-------|------|------|
    @endverbatim
*/
typedef enum
{
    QAPI_UART_INSTANCE_SE0_E, /**< GENI UART controller 0. */
    QAPI_UART_INSTANCE_SE1_E, /**< GENI UART controller 1. */
    QAPI_UART_INSTANCE_SE2_E, /**< GENI UART controller 2. */
    QAPI_UART_INSTANCE_MAX    /**< GENI UART maximum instance. */
} qapi_UART_Instance_t;

/** Enumeration to specify the address in the TX or RX direction. It is only 
    available in 9-bit mode. */
typedef enum
{
   QAPI_UART_RA_E, /**< Receive Address. */
   QAPI_UART_TA_E  /**< Transmit Address. */
}qapi_UART_Tra_Direction_t;

/** Enumeration to specify how many UART bits are to be used for each character 
    configuration. */
typedef enum
{
  QAPI_UART_5_BITS_PER_CHAR_E = 5,    /**< 5 bits per character. */
  QAPI_UART_6_BITS_PER_CHAR_E = 6,    /**< 6 bits per character. */
  QAPI_UART_7_BITS_PER_CHAR_E = 7,    /**< 7 bits per character. */
  QAPI_UART_8_BITS_PER_CHAR_E = 8,    /**< 8 bits per character. */
  QAPI_UART_9_BITS_PER_CHAR_SW_E = 9, /**< 9 bits per character, software processes the 9th bit. */
  QAPI_UART_9_BITS_PER_CHAR_HW_E = 10 /**< 9 bits per character, hardware processes the 9th bit. */
} qapi_UART_Bits_Per_Char_t;

/** Enumeration for the UART number of stop bits configuration. */
typedef enum
{
  QAPI_UART_1_0_STOP_BITS_E, /**< 1.0 stop bit. */  
  QAPI_UART_1_5_STOP_BITS_E, /**< 1.5 stop bits. */
  QAPI_UART_2_0_STOP_BITS_E, /**< 2.0 stop bits. */
  QAPI_UART_2_5_STOP_BITS_E, /**< 2.5 stop bits. */
  QAPI_UART_3_0_STOP_BITS_E  /**< 3.0 stop bits. */
} qapi_UART_Num_Stop_Bits_t;
 
/** Enumeration for the UART parity mode configuration. */
typedef enum
{
  QAPI_UART_NO_PARITY_E,    /**< No parity. */
  QAPI_UART_EVEN_PARITY_E,  /**< Even parity. */
  QAPI_UART_ODD_PARITY_E,   /**< Odd parity. */
  QAPI_UART_SPACE_PARITY_E, /**< Space parity, constant zero. */
  QAPI_UART_MARK_PARITY_E   /**< Mark parity, constant one. */ 
} qapi_UART_Parity_Mode_t;

/** Structure for the UART configuration. */
typedef struct qapi_UART_Config_s
{
   qbool_t                    Dma;            /**< TRUE: DMA, FALSE: FIFO. */
   qbool_t                    TxInvert;       /**< TRUE: Tx signal is low in idle state, FALSE: Tx signal is high in idle state. */
   uint16_t                   TxBufSize;      /**< Internal buffer size for transmission. */
   uint16_t                   RxBufSize;      /**< Internal buffer size for reception. */
   uint32_t                   BaudRate;       /**< Supported maximum baud rate. 2 Mbps. */
   qapi_UART_Parity_Mode_t    ParityMode;     /**< Parity mode. */
   qapi_UART_Num_Stop_Bits_t  NumStopBits;    /**< Number of stop bits. */
   qapi_UART_Bits_Per_Char_t  BitsPerChar;    /**< Bits per character. 5 to 9 bits are supported. */
   qbool_t                    EnableLoopback; /**< Enable loopback. */
   qbool_t                    EnableFlowCtrl; /**< Enable RTS/CTS flow control. */
   uint32_t                   RxStaleCnt;     /**< Firmware counts the Stale counter in UART bit time. 1 ~ 1023 are valid. */
   qapi_UART_CB_t             TxCbFunc;       /**< Transmit callback. */
   qapi_UART_CB_t             RxCbFunc;       /**< Receive callback. */
   void                       *CallbackCtxt;  /**< User-specified context of the Rx/Tx callback. */
}qapi_UART_Config_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the UART controller.

   Opens the UART controller and configures corresponding clocks,
   interrupts, and GPIO. In any operating mode, this function should
   be called before calling any other UART controller API.

   @param[in] Instance  UART instance specified by #qapi_UART_Instance_t.
   @param[in] Config    Structure that holds all configuration data.

   @return
   QAPI_OK -- UART instance open successfully. \n
   QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance or handle parameter. \n
   QAPI_UART_ERROR_MEM_ALLOC -- Could not allocate space for driver structures.
*/
qapi_Status_t qapi_UART_Open(qapi_UART_Instance_t Instance, qapi_UART_Config_t* Config);

/**
   @brief Closes the UART controller.

   Releases clock, interrupt, and GPIO handles related to this UART and
   cancels any pending transfers.

   @param[in] Instance  UART instance opened by qapi_UART_Open().

   @return
   QAPI_OK  -- UART instance close successful. \n
   QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance parameter. @newpage
*/
qapi_Status_t qapi_UART_Close(qapi_UART_Instance_t Instance);

/**
   @brief Copy the received data from the internal buffer to the application buffer.
   This is an asynchronous call. The QAPI is none-blocking.
    
   @param[in]     Instance     The UART instance opened by qapi_UART_Open().
   @param[in]     Buf          Buffer to be filled with data.
   @param[in,out] BufSize      Input: the length of the Buffer, Output: the length of the bytes to be read.
   @param[out]    BytesRemain  Bytes of data remaining in the driver.
    
   @return 
   QAPI_OK -- UART transfer successful. \n
   QAPI_UART_ERROR_INVALID_PARAM -- One or more parameters are invalid. \n
   QAPI_UART_ERROR_NO_DATA_TO_TRANSFER -- No data in the internal buffer to receive.
*/
qapi_Status_t qapi_UART_Receive(qapi_UART_Instance_t Instance, char* Buf, uint32_t* BufSize, uint32_t* BytesRemain);

/**
   @brief Copy data from the application buffer to the internal buffer. The
   driver queues the write buffer to the DMA/FIFO engine. The QAPI is none-blocking.
   When transmit is completed, the TxCbFunc is called.

   @param[in]  Instance   UART instance opened by qapi_UART_Open().
   @param[in]  Buf        Buffer with data to transmit.
   @param[in]  BytesToTx  Bytes of data to transmit.
   @param[out] BytesSent  Bytes of data already sent.

   @return
   QAPI_OK -- UART transfer successful. \n
   QAPI_UART_ERROR_INVALID_PARAM -- One or more parameters are invalid. \n
   QAPI_UART_ERROR_NO_DATA_TO_TRANSFER -- No data to transmit. \n
   QAPI_UART_ERROR_TRANSMIT_BUSY -- UART transmit is ongoing. \n

*/
qapi_Status_t qapi_UART_Transmit(qapi_UART_Instance_t Instance, char* Buf, uint32_t BytesToTx, uint32_t* BytesSent);

/**
   @brief Set the transmit/receive address in 9-bit hardware mode.

   @param[in] Instance  UART instance opened by qapi_UART_Open().
   @param[in] Dir       Transmit or receive direction.
   @param[in] Address   Address value.

   @return
   QAPI_OK -- Address set was successful.\n
   QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_UART_Set_TRAddress(qapi_UART_Instance_t Instance, qapi_UART_Tra_Direction_t Dir, uint8_t Address);

/**
   @brief Get the transmit/receive address in 9-bit hardware mode.

   @param[in]  Instance  UART instance opened by qapi_UART_Open().
   @param[in]  Dir       Transmit or receive direction.
   @param[out] Address   Address value.

   @return
   QAPI_OK -- Address get was successful. \n
   QAPI_UART_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_UART_Get_TRAddress(qapi_UART_Instance_t Instance, qapi_UART_Tra_Direction_t Dir, uint8_t* Address);

/**
   @brief Get the number of bytes currently pending to be transmitted.

   @param[in]  Instance  UART instance opened by qapi_UART_Open().

   @return
   Number of bytes currently pending to be transmitted.
*/
uint32_t qapi_UART_Get_Tx_Remaining(qapi_UART_Instance_t Instance);

/** @} */ /* end_addtogroup qapi_peripherals_uart */

#endif

