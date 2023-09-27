/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_i2c.h
   @brief Inter-Integrated Circuit (I²C).
*/

/** @addtogroup qapi_peripherals_I2C
  The I²C module uses an inter-integrated circuit interface (I²C) 2-wire bus
  to connect low-speed peripherals to a processor or a microcontroller.
  Common I²C peripherals include touch screen controllers, accelerometers,
  gyros, ambient light, and temperature sensors.

  The 2-wire bus comprises a data line, a clock line, and basic START,
  STOP, and acknowledge signals to drive transfers on the bus. An I²C
  peripheral is also referred to as an I²C slave. The processor or
  microcontroller implements the I²C master as defined in the I²C
  specification. This documentation provides the software interface to
  access the I²C master implementation.

  @note1hang Before using module APIs, qapi_PWR_Set_Module_State
             (#QAPI_PWR_MODULE_PERIPHERAL_E, #QAPI_PWR_STATE_ACTIVE_E,
             #QAPI_PWR_STATE_ACTIVE_E) must be called.
*/

#ifndef __QAPI_I2C_H__
#define __QAPI_I2C_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_peripherals_I2C
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/** Error codes returned by the I²C Master controller API */
#define QAPI_I2CM_ERROR                                          __QAPI_ERROR(QAPI_MOD_I2C, 1)   /**< Common error */
#define QAPI_I2CM_ERROR_INVALID_PARAM                            __QAPI_ERROR(QAPI_MOD_I2C, 2)   /**< Invalid input parameters. */
#define QAPI_I2CM_ERROR_MEM_ALLOC                                __QAPI_ERROR(QAPI_MOD_I2C, 3)   /**< Alloc memory failed. */
#define QAPI_I2CM_ERROR_TRANSFER_BUSY                            __QAPI_ERROR(QAPI_MOD_I2C, 4)   /**< Transaction busy. */
#define QAPI_I2CM_ERROR_TRANSFER_TIMEOUT                         __QAPI_ERROR(QAPI_MOD_I2C, 5)   /**< Transaction timeout in blocking mode. */
#define QAPI_I2CM_ERROR_INPUT_FIFO_UNDER_RUN                     __QAPI_ERROR(QAPI_MOD_I2C, 6)   /**< Software reads from an empty Rx FIFO. */
#define QAPI_I2CM_ERROR_INPUT_FIFO_OVER_RUN                      __QAPI_ERROR(QAPI_MOD_I2C, 7)   /**< Hardware writes to a full Rx FIFO. */
#define QAPI_I2CM_ERROR_OUTPUT_FIFO_UNDER_RUN                    __QAPI_ERROR(QAPI_MOD_I2C, 8)   /**< Software reads a new word from an empty Tx FIFO. */
#define QAPI_I2CM_ERROR_OUTPUT_FIFO_OVER_RUN                     __QAPI_ERROR(QAPI_MOD_I2C, 9)   /**< Software writes a new word to a full Tx FIFO. */
#define QAPI_I2CM_ERROR_COMMAND_OVER_RUN                         __QAPI_ERROR(QAPI_MOD_I2C, 10)  /**< A new command is initialized before the previous one is complete. */
#define QAPI_I2CM_ERROR_TRANSFER_FORCE_TERMINATED                __QAPI_ERROR(QAPI_MOD_I2C, 11)  /**< Command abort, or cancel request by software. */
#define QAPI_I2CM_ERROR_COMMAND_ILLEGAL                          __QAPI_ERROR(QAPI_MOD_I2C, 12)  /**< Command with an illegal opcode. */
#define QAPI_I2CM_ERROR_COMMAND_FAIL                             __QAPI_ERROR(QAPI_MOD_I2C, 13)  /**< Command execution has been completed with a failure. */
#define QAPI_I2CM_ERROR_BUS_CLK_ENABLE_FAIL                      __QAPI_ERROR(QAPI_MOD_I2C, 14)  /**< Setting the clock failed. */
#define QAPI_I2CM_ERROR_BUS_GPIO_ENABLE_FAIL                     __QAPI_ERROR(QAPI_MOD_I2C, 15)  /**< Setting the GPIO failed. */
#define QAPI_I2CM_ERROR_DMA_TX_BUS_ERROR                         __QAPI_ERROR(QAPI_MOD_I2C, 16)  /**< Bus error during DMA Tx transaction. */
#define QAPI_I2CM_ERROR_DMA_RX_BUS_ERROR                         __QAPI_ERROR(QAPI_MOD_I2C, 17)  /**< Bus error during DMA Rx transaction. */
#define QAPI_I2CM_DMA_TX_RESET_DONE                              __QAPI_ERROR(QAPI_MOD_I2C, 18)  /**< DMA TX reset done. */
#define QAPI_I2CM_DMA_RX_RESET_DONE                              __QAPI_ERROR(QAPI_MOD_I2C, 19)  /**< DMA RX reset done. */
#define QAPI_I2CM_CANCEL_TRANSFER_COMPLETED                      __QAPI_ERROR(QAPI_MOD_I2C, 20)  /**< Transfer complete when canceled. */
#define QAPI_I2CM_CANCEL_TRANSFER_INVALID                        __QAPI_ERROR(QAPI_MOD_I2C, 21)  /**< No transfer to be canceled.  */


/** I²C transfer flags */
#define QAPI_I2C_FLAG_START                                      0x00000001  /**< Specifies that the transfer begins with a START bit - S. */
#define QAPI_I2C_FLAG_STOP                                       0x00000002  /**< Specifies that the transfer ends with a STOP bit - P. */
#define QAPI_I2C_FLAG_WRITE                                      0x00000004  /**< Must be set to indicate a WRITE transfer. */
#define QAPI_I2C_FLAG_READ                                       0x00000008  /**< Must be set to indicate a READ transfer. */


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Instance of the I²C Master core that the client wants to use. This instance
    is passed in qapi_I2CM_Open(). */
typedef enum
{
    QAPI_I2C_INSTANCE_SE0_E,  /**< GENI I²C controller 0. */
    QAPI_I2C_INSTANCE_SE1_E,  /**< GENI I²C controller 1. */
    QAPI_I2C_INSTANCE_SE2_E,  /**< GENI I²C controller 2. */
    QAPI_I2C_INSTANCE_SE3_E  /**< GENI I²C controller 3. */
} qapi_I2CM_Instance_t;

/** I²C Master configuration parameters. */
typedef struct qapi_I2CM_Config_s
{
    qbool_t Blocking;  /**< 1: Blocking mode, 0: Nonblocking mode. */
    qbool_t Dma;       /**< TRUE: DMA, FALSE: FIFO. */
} qapi_I2CM_Config_t;

/** I²C Master client configuration parameters that the client uses to communicate
  to an I²C slave. */
typedef struct qapi_I2CM_Transfer_Config_s
{
    uint32_t BusFreqKHz;              /**< I²C Master bus speed in kHz. */
    uint32_t SlaveAddress;            /**< 7-bit I²C slave address. */
    uint32_t SlaveMaxClockStretchUs;  /**< Maximum slave clock stretch in µs.*/
    uint32_t Delay;                   /**< Delay before the start and at the end of a command. Recommended 0.*/
    uint32_t NoiseReject;             /**< Noise reject. Recommended 0. */
} qapi_I2CM_Transfer_Config_t;

/** I²C Master transfer descriptor. */
typedef struct qapi_I2CM_Descriptor_s
{
    uint8_t  *Buffer;      /**< Buffer for the data transfer. */
    uint32_t Length;       /**< Length of the data to be transferred in bytes. */
    uint32_t Transferred;  /**< Number of bytes transferred. */
    uint32_t Flags;        /**< I²C Master flags for the transfer. */
} qapi_I2CM_Descriptor_t;

/**
   @brief Prototype for a function called when the data is completely transferred
   on the bus, or when the transfer ends due to an error or cancellation.
   Clients pass the callback function pointer and the callback context to the
   driver in the qapi_I2CM_Transfer() API.

   @note
   The callback is called in the I²C Master driver context. Calling any of the
   I²C Master QAPIs defined in this file in the callback is forbidden.

   @param[out] Status        The completion status of the transfer.

   @param[out] CallbackCtxt  The callback context that was passed in the call
                             to qapi_I2CM_Transfer().
*/
typedef void (*qapi_I2CM_Transfer_CB_t)(uint32_t Status, void *CallbackCtxt);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize the respective I²C Master instance.

   The API allocates resources for use by the client handle and the I²C Master
   instance, and enables power to the I²C hardware instance.

   @param[in] Instance  I²C Master instance that the client intends to initialize.

   @param[in] Config    I²C Master configuration.

   @return
   QAPI_OK -- Module was initialized successfully.\n
   QAPI_I2CM_ERROR_INVALID_PARAM -- Invalid instance or handle parameter.\n
   QAPI_I2CM_ERROR_MEM_ALLOC -- Could not allocate space for driver structures.\n
   QAPI_I2CM_ERROR_INTERRUPT_REGISTER -- Could not register for an interrupt.
*/
qapi_Status_t qapi_I2CM_Open(qapi_I2CM_Instance_t Instance, qapi_I2CM_Config_t *Config);

/**
   @brief De-initialize the I²C Master instance.

   The API releases any resources allocated by the qapi_I2CM_Open() API, and
   disables the power to the instance. In this API, the transfers that have 
   not been completed are canceled and the transfer call back function
   is called.

   @param[in] Instance  The I²C Master instance to be closed.
   
   @return
   QAPI_OK -- I²C Master driver was closed successfully.\n
   QAPI_I2CM_ERROR_INVALID_PARAM -- Invalid instance parameter.
*/
qapi_Status_t qapi_I2CM_Close(qapi_I2CM_Instance_t Instance);

/**
   @brief Perform an I²C Master transfer.

   In case a transfer is already in progress by another client, this call 
   queues the transfer. If the transfer returns a failure, the transfer
   has not been queued and no callback will occur. If the transfer returns
   QAPI_OK, the transfer has been queued and a further status of the 
   transfer is only obtainable when the callback is called in non-blocking
   mode.
   
   @note
   In general, if the client wants to queue multiple transfers, it could
   use an array of descriptors of type #qapi_I2CM_Descriptor_t instead of 
   calling the API multiple times. Although the I²C Master driver supports 
   queuing multiple transfers in non-blocking mode.

   @param[in] Instance     The I²C Master instance.
   @param[in] Config       Transfer configuration.
   @param[in] Desc         I²C Master transfer descriptor. This can be an
                           array of descriptors.
   @param[in] NumDesc      Number of descriptors in the descriptor array.
   @param[in] CBFunction   The callback function that is called at the
                           completion of the transfer, occurs in non-blocking
                           mode. The call must do minimal processing and must
                           not call any API defined in this file. It should 
                           be NULL in blocking mode.
   @param[in] CBParameter  The context that the client passes here, is
                           returned as is, in the callback function. It should
                           be NULL in blocking mode.

   @return
   QAPI_OK -- I²C Master transfer successful.\n
   QAPI_I2CM_ERROR_INVALID_PARAM -- One or more parameters are invalid.\n
   QAPI_I2CM_ERROR_TRANSFER_BUSY -- I²C Master core is busy.\n
   QAPI_I2CM_ERROR_TRANSFER_TIMEOUT -- Transfer timed out.\n
   QAPI_I2CM_ERROR_INPUT_FIFO_UNDER_RUN -- Software reads from an empty Rx FIFO.\n
   QAPI_I2CM_ERROR_INPUT_FIFO_OVER_RUN -- Hardware writes to a full Rx FIFO.\n
   QAPI_I2CM_ERROR_OUTPUT_FIFO_UNDER_RUN -- Software reads a new word from an empty Tx FIFO.\n
   QAPI_I2CM_ERROR_OUTPUT_FIFO_OVER_RUN -- Software writes a new word to a full Tx FIFO.\n
   QAPI_I2CM_ERROR_COMMAND_OVER_RUN -- A new command is initialized before the previous one is complete.\n
   QAPI_I2CM_ERROR_TRANSFER_FORCE_TERMINATED -- Command abort or cancel request by software.\n
   QAPI_I2CM_ERROR_COMMAND_ILLEGAL -- Command with illegal opcode.\n
   QAPI_I2CM_ERROR_COMMAND_FAIL -- Command execution has been completed with failure.\n
   QAPI_I2CM_ERROR_DMA_TX_BUS_ERROR -- Bus error during DMA Tx transaction.\n
   QAPI_I2CM_ERROR_DMA_RX_BUS_ERROR -- Bus error during DMA Rx transaction.\n
*/
qapi_Status_t qapi_I2CM_Transfer(qapi_I2CM_Instance_t Instance, qapi_I2CM_Transfer_Config_t *Config, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc, qapi_I2CM_Transfer_CB_t CBFunction, void *CBParameter);

/**
   @brief Cancels a transfer.

   A transfer that has been initiated successfully by calling qapi_I2CM_Transfer()
   may be canceled. Based on the internal state of the transfer, this function
   either immediately cancels the transfer or ends the transfer at a later time.

   @param[in] Instance  The I²C Master instance.
   
   @return
   QAPI_OK -- Transfer is cancelled successfully.\n
   QAPI_I2CM_ERROR_INVALID_PARAM -- One or more parameters are invalid.\n
   QAPI_I2CM_CANCEL_TRANSFER_INVALID -- Transfer completed before cancelling.\n
   QAPI_I2CM_ERROR_TRANSFER_FORCE_TERMINATED -- Transfer aborted on the bus.
*/
qapi_Status_t qapi_I2CM_Cancel_Transfer(qapi_I2CM_Instance_t Instance);

/** @} */ /* end_addtogroup qapi_peripherals_I2C */

#endif

