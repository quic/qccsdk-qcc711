/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_radio.h
    @brief Radio control definition.

    This module provides an interface to the BTSS that allows control over
    suspending and resuming radio activity, specifying a max transmit power
    level, and registering for brownout detection notifications.
*/

#ifndef __QAPI_RADIO_H__
#define __QAPI_RADIO_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_platform_radio
@{ */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Prototype for a function called when a brownout event occurs.

   @param[in] dBm  Power level (in dBm) of the transmit operation that caused
                   the brownout detector to trigger.
*/
typedef void(*qapi_Radio_Brownout_CB_t)(int8_t dBm);

/*==================================================================================================
                                        FUNCTION PROTOTYPES
==================================================================================================*/

/**
   @brief Registers a callback function for brownout notifications.

   A callback is registered in order to notify the application when the
   Bluetooth subsytem has detected a brownout condition. The Bluetooth
   subsystem will enter a Radio Suspend state after a brownout
   occurs, and it shall not resume radio activity until the application
   has issued a call to qapi_Radio_Resume(). The application has the
   opportunity to lower the maximum transmit power before resuming radio
   operations through a call to qapi_Radio_Set_Max_Tx_Power(). Only a single
   callback is allowed to be registered.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] BrownoutCB  Function that will be called when a brownout
                          condition occurs.

   @return
   QAPI_OK -- The callback was registered successfully. \n
   QAPI_ERR_EXISTS -- A registered callback already exists.
*/
qapi_Status_t qapi_Radio_Register_Brownout_Callback(uint32_t BluetoothStackID, qapi_Radio_Brownout_CB_t BrownoutCB);

/**
   @brief Unregisters the brownout callback.

   The previously registered brownout callback is unregistered upon
   successful completion

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] BrownoutCB        The previously registered Brownout CB.

   @return
   QAPI_OK --  The callback was unregistered successfully. \n
   QAPI_ERROR -- The callback was not unregistered successfully. \n
   QAPI_ERR_NO_ENTRY -- A callback was not previously registered.
*/
qapi_Status_t qapi_Radio_Unregister_Brownout_Callback(uint32_t BluetoothStackID, qapi_Radio_Brownout_CB_t BrownoutCB);

/**
   @brief Suspends all radio activity.

   All radio activity is suspended upon successful completion. It is the
   caller's responsibility to resume radio activity in a timely manner in order
   to avoid timeout conditions that may occur with the Bluetooth subsystem.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().

   @return
   QAPI_OK -- Radio activity was successfully suspended. \n
   QAPI_ERROR -- A failure occurred while suspending radio activity.
*/
qapi_Status_t qapi_Radio_Suspend(uint32_t BluetoothStackID);

/**
   @brief Resumes previously suspended radio activity.

   Previously suspended radio activity shall resume upon successful completion.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().

   @return
   QAPI_OK -- Radio activity was successfully resumed. \n
   QAPI_ERROR -- Radio was not in suspended state, or a failure occurred
                 while resuming radio activity.
*/
qapi_Status_t qapi_Radio_Resume(uint32_t BluetoothStackID);

/**
   @brief Sets the maximum transmit power that is allowed.

   Sets the maximum transmit power that is allowed by the radio.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] dBm               The maximum transmit power (in dBm) that is allowed. This value must be between
                                -31 dBm and + 7dBm.

   @return
   QAPI_OK  -- Maximum transmit power was successfully changed. \n
   QAPI_ERROR -- A failure occurred while changing maximum transmit power.
*/
qapi_Status_t qapi_Radio_Set_Max_Tx_Power(uint32_t BluetoothStackID, int8_t dBm);

/** @} */ /* end_addtogroup qapi_platform_radio */


#endif

