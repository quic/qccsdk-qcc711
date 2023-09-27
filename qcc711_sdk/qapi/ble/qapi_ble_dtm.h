/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_dtm.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack Direct Test Mode (DTM)
 * Profile API Type Definitions, Constants, and Prototypes.
 */

#ifndef __QAPI_BLE_DTM_H__
#define __QAPI_BLE_DTM_H__

#include "qapi_types.h"
#include "qapi_ble_btapityp.h"


/** @addtogroup qapi_ble_dtm
@{ */

/**
 * @brief
 * This declared type represents the prototype Function for a DTM callback.
 *
 * @details
 * This function will be called whenever event data needs to be sent.
 *
 * @param[in] Length              Length of the data buffer.
 *
 * @param[in] Data                Event data to send.
 *
 * @param[in] CallbackParameter   User-defined parameter that was defined in the
 *                                callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_DTM_Callback_t)(uint32_t Length, uint8_t *Data, unsigned long CallbackParameter);

/**
 * @brief
 * Initializes the Bluetooth Protocol Stack in BLE Direct Test Mode.
 *
 * As this module initializes the Bluetooth stack, it must not already be
 * initialized when this API is called.
 *
 * @param[in] Callback           Function called when event data needs to be
 *                               sent.
 *
 * @param[in] CallbackParameter  User-defined parameter passed to the callback
 *                               function.
 *
 * @return
 * Zero -- if initialization was successful.
 * Negative value -- That is an ErrorCode. Possible values are:
 *             @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_L2CAP_INITIALIZATION_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DTM_Initialize(qapi_BLE_DTM_Callback_t Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Exits Direct Test Mode and Shuts down the Bluetooth Protocol Stack.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_DTM_Shutdown(void);

/**
 * @brief
 * Pass recieved data into the DTM module.
 *
 * @param[in]  Length  Length of the data received.
 *
 * @param[in]  Data    Pointer to the recieved data.
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an Error occurred. Possible values are:
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DTM_Receive(uint32_t Length, uint8_t *Data);

/** @} */ /* end_addtogroup qapi_ble_dtm */

#endif

