/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_debug.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack Debugging API
 * Type Definitions, Constants, and Prototypes.
 *
 */

#ifndef __QAPI_BLE_DEBUG_H__
#define __QAPI_BLE_DEBUG_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */

   /** @name Error Return Codes

      BTPS Debug module Error Codes.
      @{ */
#define QAPI_BLE_BTPS_DEBUG_ERROR_INVALID_STACK_ID             (-1)
/**< Invalid Bluetooth stack ID. */
#define QAPI_BLE_BTPS_DEBUG_ERROR_INVALID_PARAMETER            (-2)
/**< Invalid parameter. */
#define QAPI_BLE_BTPS_DEBUG_ERROR_INITIALIZING_DEBUG           (-4)
/**< Error Initializing Debug. */
#define QAPI_BLE_BTPS_DEBUG_ERROR_INVALID_DEBUG_ID             (-5)
/**< Invalid Debug ID. */
#define QAPI_BLE_BTPS_DEBUG_ERROR_UNKNOWN                      (-6)
/**< Unknown error. */

#define BTPS_DEBUG_FLAGS_APPEND_FILE                  0x00000001
#define BTPS_DEBUG_FLAGS_PREPEND_BLUETOOTH_ADDRESS    0x00000002

/** @} */ /* end namegroup */

/**
 * Enumeration of the valid Debug Types that may be in a
 * qapi_BLE_BTPS_Debug_Parameters_t structure.
 */
typedef enum
{
   QAPI_BLE_DT_LOG_FILE_E,
   /**< Output to a text log file. */
   QAPI_BLE_DT_DEBUG_TERMINAL_E,
   /**< Output to a debug terminal. */
   QAPI_BLE_DT_FTS_E
   /**< Output in binary BTSnoop format. */
} qapi_BLE_BTPS_Debug_Type_t;

/**
 * Structure which specifies information that is required to setup the debug option.
 */
typedef struct qapi_BLE_BTPS_Debug_Parameters_s
{
   /**
    * The type of debugging to be enabled.
    */
   qapi_BLE_BTPS_Debug_Type_t DebugType;

   /**
    * Flags to control debugging options.
    */
   unsigned long DebugFlags;

   /**
    * Parameter to be passed to the debugging type.
    * <br>
    * For QAPI_BLE_DT_LOG_FILE_E and QAPI_BLE_DT_FTS_E,
    * this is the file name to use. For QAPI_BLE_DT_DEBUG_TERMINAL_E,
    * this should not be used.
    */
   char *ParameterString;
} qapi_BLE_BTPS_Debug_Parameters_t;

#define QAPI_BLE_BTPS_DEBUG_FLAGS_APPEND_FILE                  0x00000001
#define QAPI_BLE_BTPS_DEBUG_FLAGS_PREPEND_BLUETOOTH_ADDRESS    0x00000002

/**
 * @brief
 * Initialize Bluetooth HCI Debugging.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  DebugParameters      The parameters which control what options 
 *                                  are to be used for the debugging instance.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the Debug ID of the debugging instance that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used to clean up the debug instance.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_BTPS_Debug_Initialize(uint32_t BluetoothStackID, qapi_BLE_BTPS_Debug_Parameters_t *DebugParameters);

/**
 * @brief
 * Cleans up Bluetooth HCI Debugging.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BTPSDebugID          The Debug ID that was created via a successful
 *                                  call tp qapu_BLE_BTPS_Debug_Initialize(). 
 *
 * @return    None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_BTPS_Debug_Cleanup(uint32_t BluetoothStackID, uint32_t BTPSDebugID);

#endif
