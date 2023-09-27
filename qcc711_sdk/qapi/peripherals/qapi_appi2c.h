/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_appi2c.h
   @brief Inter-Integrated Circuit (I2C) interface. 
*/

/** @addtogroup qapi_peripherals_appi2c

   APPI2C transfers:
   APPI2C transfers implement the standard I2C protocol on the APPI2C ip core.

   Note about APPI2C slave:
   For now the slave support the following features:
   - Clock strtching
   - Suppport general call and software reset
   - Slave-ID configuration(7-bit and 10-bt addressing options)
   - Support standard mode(0-100 kpbs), fast mode(0-400 kbps) and fast plus
     mode(0~1Mbps)

   Note about APPI2C master:
   For now only APPI2C slave is implemented. The qup I2C can be used as master.

   Typical usage for slave:
   qapi_APPI2C_Open()                  - Initialize the AppI2c handler and set as master or slave (slave only for now).
   qapi_APPI2C_SlaveTransmit()         - Transmit data to master as slave, can be blocking or interrupted.
   qapi_APPI2C_SlaveReceive()          - Receive data from master as slave, can be blocking or interrupted.
   qapi_APPI2C_Close()                 - Deinitialize the APPI2C handler and close the APPI2C bus.
*/

#ifndef __QAPI_APPI2C_H__
#define __QAPI_APPI2C_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_appi2c
@{
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/** Common error. */
#define QAPI_APPI2C_ERROR                              __QAPI_ERROR(QAPI_MOD_APPI2C, 1)

/** Invalid input parameters. */
#define QAPI_APPI2C_ERROR_INVALID_PARAM                __QAPI_ERROR(QAPI_MOD_APPI2C, 2)

/** No enough memory. */
#define QAPI_APPI2C_ERROR_MEM_ALLOC                    __QAPI_ERROR(QAPI_MOD_APPI2C, 3)

/** Transaction bus busy. */
#define QAPI_APPI2C_ERROR_TRANSFER_BUSY                __QAPI_ERROR(QAPI_MOD_APPI2C, 4)

/** Transaction timeout. */
#define QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT             __QAPI_ERROR(QAPI_MOD_APPI2C, 5)

/** Transaction nack. */
#define QAPI_APPI2C_ERROR_TRANSFER_NACK                __QAPI_ERROR(QAPI_MOD_APPI2C, 6)

/** Transaction stop. */
#define QAPI_APPI2C_ERROR_TRANSFER_STOP                __QAPI_ERROR(QAPI_MOD_APPI2C, 7)

/** Receive general call. */
#define QAPI_APPI2C_ERROR_TRANSFER_GNCALL              __QAPI_ERROR(QAPI_MOD_APPI2C, 8)

/** Controller has been opened. */
#define QAPI_APPI2C_ERROR_I2C_HASBEEN_OPENED           __QAPI_ERROR(QAPI_MOD_APPI2C, 9)

/** Controller has been closed. */
#define QAPI_APPI2C_ERROR_I2C_HASBEEN_CLOSED           __QAPI_ERROR(QAPI_MOD_APPI2C, 10)

/** Set the clock failed. */
#define QAPI_APPI2C_ERROR_BUS_CLK_ENABLE_FAIL          __QAPI_ERROR(QAPI_MOD_APPI2C, 11)

/** Set the clock failed. */
#define QAPI_APPI2C_ERROR_TSK_CREATE_FAIL              __QAPI_ERROR(QAPI_MOD_APPI2C, 12)

/** Timeout in blocking mode. */
#define QAPI_APPI2C_ERROR_BLOCKING_TIMEOUT             __QAPI_ERROR(QAPI_MOD_APPI2C, 13)

/** Timeout in blocking mode. */
#define QAPI_APPI2C_ERROR_READWRITE_CORRUPT            __QAPI_ERROR(QAPI_MOD_APPI2C, 14)

/** Error map status. */
#define APPI2C_ErrorMap(Status) (Status == QAPI_OK) ? QAPI_OK :__QAPI_ERROR(QAPI_MOD_APPI2C, Status)

/* I2C config mode bit */
#define QAPI_APPI2C_MODE_MASTER            (0 << 0)                                    /**< Master mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_SLAVE             (1 << 0)                                    /**< Slave mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_ROLE_MASK         (1 << 0)                                    /**< Role mask mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_BLOCKING          (0 << 1)                                    /**< Blocking mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_INTERRUPT         (1 << 1)                                    /**< Interrupt mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_BLOCKING_MASK     (1 << 1)                                    /**< Blocking mask mode - I2C config mode bit. */
#define QAPI_APPI2C_MODE_BIT_NUM           (2)                                         /**< Bit Number mode - I2C config mode bit. */
#define QAPI_APPI2C_MODEBIT_NUM_MSK        (((1) << (QAPI_APPI2C_MODE_BIT_NUM)) - (1)) /**< Bit Number mask mode - I2C config mode bit. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
/**
  @brief APPI2C address mode.

*/
typedef enum
{
    QAPI_APPI2C_ADDR_7BIT_E,                            /**< 7 bit address - APPI2C address mode. */
    QAPI_APPI2C_ADDR_10BIT_E,                           /**< 10 bit address - APPI2C address mode. */
    QAPI_APPI2C_ADDR_MAX_E = QAPI_APPI2C_ADDR_10BIT_E,  /**< Maximum address size = 10 bit address - APPI2C address mode. */
} qapi_APPI2C_Addr_t;

/**
  @brief APPI2C configuration structure.

*/
typedef struct
{
    uint32_t FreqHz;            /**< APPI2c clock frequency. Valid rang from
                                     0~100kbp(standard mode), 0~400kbps(fast mode)
                                     or 0~1Mbps(fast plus mode) */
    uint32_t SlaveAddr;         /**< APPI2C slave address, can be 7-bit and 10 bit. */
    uint32_t AddrMode;          /**< One of the qapi_APPI2C_Addr_t */
    uint32_t Mode;              /**< APPI2C mode */
} qapi_APPI2C_Config_t;

/**
  @brief APPI2C bus status.

  This status can be polling checked to decide whether to transmit/receive data from
  the bus, to handle a general call, or just wait(idle state).

*/
typedef enum
{
    QAPI_APPI2C_STATUS_DONE_E,         /**< Done - APPI2C bus status. */
    QAPI_APPI2C_STATUS_IDEL_E,         /**< Idle - APPI2C bus status. */
    QAPI_APPI2C_STATUS_RECEIVING_E,    /**< Receiving - APPI2C bus status. */
    QAPI_APPI2C_STATUS_TRANSMITING_E,  /**< Transmitting - APPI2C bus status. */
    QAPI_APPI2C_STATUS_GNCALL_E,       /**< General call - APPI2C bus status. */
    QAPI_APPI2C_STATUS_ABORT_E,        /**< Abort - APPI2C bus status. */
    QAPI_APPI2C_STATUS_TIMEOUT,        /**< Timeout - APPI2C bus status. */
} qapi_APPI2C_Status_t;

/**
  @brief APPI2C user callback paramaters structure.

*/
typedef struct
{
    uint8_t *Buf;                   /**< Pointer to buffer for APPI2C user callback parameters */
    uint32_t UserSize;              /**< Size of user parameter buffer. */
    uint32_t ActualSize;            /**< Actual size of user parameters */
    qbool_t  IsGnCall;              /**< Is GN called. */
} qapi_APPI2C_UserCallBackParam_t;

/**
  @brief User defined callback when specific condition is triggered in non-blocking mode.

  This callback is used for some user defined behaviors when specific condition is
  triggered. These conditions include transfer done, transfer abort by NACK,
  timeout error and others which defined in the qapi_APPI2C_CallbackId_t.

  @param[in] Status         Current i2c status.
  @param[in] UserParam      User define parameters.

*/
typedef void (*qapi_APPI2C_CB_t) (qapi_APPI2C_Status_t Status, qapi_APPI2C_UserCallBackParam_t UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
/**
   @brief Initializes the APPI2C controller.

   This function initializes internal data structures and associated
   static data. In any operating mode, this function should be called before
   calling any other I2C controller API.

   @param[in] Config    APPI2C configuration specified by #qapi_APPI2C_Config_t.

   @return
   QAPI_OK -- Controller is initialized successfully.\n
   QAPI_APPI2C_ERROR_INVALID_PARAM -- Invalid instance or handle parameter.\n
   QAPI_APPI2C_ERROR_MEM_ALLOC -- Could not allocate space for driver structures.
*/
qapi_Status_t qapi_APPI2C_Open(qapi_APPI2C_Config_t *Config);

/**
   @brief Performs a data transmit to master as slave over the APPI2C bus.

   This function performs transfer from slave to master. Transmit can be
   blocking or interrupt.

   @param[in]      Data          User buffer ready to transmit from slave to master.
   @param[in,out]  Len           User buffer length, and the actual bytes transferred.
   @param[in]      UserCallBack  User non-blocking call back function. Is ignored in blocking mode.

   @return
   QAPI_OK -- Transfer done.\n
   QAPI_APPI2C_ERROR -- General error.\n
   QAPI_APPI2C_ERROR_INVALID_PARAM -- Invalid parameters.\n
   QAPI_APPI2C_ERROR_TRANSFER_STOP -- Receive the STOP signal from master.\n
   QAPI_APPI2C_ERROR_TRANSFER_NACK -- Receive the NACK signal from master.\n
   QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT -- Bus timeout.
*/
qapi_Status_t qapi_APPI2C_SlaveTransmit(uint8_t *Data, uint32_t *Len, qapi_APPI2C_CB_t UserCallBack);

/**
   @brief Performs a data receive from master as slave over the APPI2C bus.

   This function performs data receive from master to slave. Receiving can
   be blocking or interrupt.

   @param[in]       Data          User buffer ready to transmit from slave to master.
   @param[in,out]   Len           User buffer length, and the actual bytes transferred.
   @param[in]       UserCallBack  User non-blocking call-back function. Is ignored in blocking mode.

   @return
   QAPI_OK -- Transfer done.\n
   QAPI_APPI2C_ERROR -- General error.\n
   QAPI_APPI2C_ERROR_INVALID_PARAM -- Invalid parameters.\n
   QAPI_APPI2C_ERROR_TRANSFER_STOP -- Receive the STOP signal from master.\n
   QAPI_APPI2C_ERROR_TRANSFER_NACK -- Receive the NACK signal from master.\n
   QAPI_APPI2C_ERROR_TRANSFER_TIMEOUT -- Bus timeout.\n
   QAPI_APPI2C_ERROR_TRANSFER_GNCALL -- Receive the general call from master.
*/
qapi_Status_t qapi_APPI2C_SlaveReceive(uint8_t *Data, uint32_t *Len, qapi_APPI2C_CB_t UserCallBack);

/**
   @brief Deinitialize the APPI2C controller.

   This function deinitializes internal data structures and associated
   static data. This function should be called to close APPI2C bus.

   @return
   QAPI_OK -- Controller is closed successfully.\n
   QAPI_APPI2C_ERROR_TRANSFER_BUSY -- Controller is in transmission.\n
   QAPI_APPI2C_ERROR_I2C_HASBEEN_CLOSED -- Controller has been closed already.
*/
qapi_Status_t qapi_APPI2C_Close(void);
/** @} */ /* end_addtogroup qapi_peripherals_appi2c */

#endif


