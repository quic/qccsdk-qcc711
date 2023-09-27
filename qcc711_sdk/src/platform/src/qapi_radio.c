/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_radio.h"
#include "qapi_power.h"
#include "qapi_ble_bttypes.h"
#include "qapi_ble_hci.h"

#include "manual_ids.h"
#include "Radio_params.h"
#include "ipc.h"
#include "callback.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/
#define RADIO_WAKEUP_PRIORITY (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT + 10)

typedef struct qapi_Radio_Context_s
{
    void *ShutdownCBHandle;
    uint32_t CallbackHandle;
    qapi_Radio_Brownout_CB_t BrownoutCB;
} qapi_Radio_Context_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/
qapi_Radio_Context_t RadioContext __attribute__((section (".bss.retain")));

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
static void Radio_Brownout_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    /* We only allow a single brownout callback, so we can just assume the supplied CallbackInfo here is the correct one. */
    if((CallbackInfo) && (CallbackInfo->AppFunction) && (Buffer) && (BufferLength >= RADIO_BROWNOUT_CALLBACK_PARAMS_SIZE))
    {
        (*((qapi_Radio_Brownout_CB_t)(CallbackInfo->AppFunction)))(((Radio_Brownout_Callback_Params_t *)Buffer)->dBm);
    }
}

static qbool_t Radio_Shutdown_CB(void *UserParam)
{
    return true;
}

static void Radio_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam)
{
    CallbackInfo_t CBInfo;

    if(!ShutdownAborted && RadioContext.BrownoutCB != NULL)
    {
        /* Retore our callback coming out of shutdown. */
        CBInfo.FileID = FILE_ID_RADIO;
        CBInfo.CallbackID = CALLBACK_ID_RADIO_BROWNOUT;
        CBInfo.AppFunction = (void *)RadioContext.BrownoutCB;
        CBInfo.AppParam = 0;
        CBInfo.CallbackKey = 0;

        if(!Callback_SetByHandle(RadioContext.CallbackHandle, Radio_Brownout_Callback_Handler, &CBInfo))
            Callback_SetPersist(RadioContext.CallbackHandle, true);
    }
}

/**
   @brief Registers a callback function for brownout notifications.

   A callback is registered in order to notify the application when the
   Bluetooth subsytem has detected a brownout condition. The Bluetooth
   subsystem will enter a Radio Suspend state after a brownout
   occurs, and it shall not resume radio activity until the application
   has issued a call to qapi_Radio_Resume(). The application has the
   opportunity to lower the maximum transmit power before resuming radio
   operations through a call to qapi_Radio_Set_Max_Power(). Only a single
   callback is allowed to be registered.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] BrownoutCB  Function that will be called when a brownout
                          condition occurs.

   @return
   - QAPI_OK         -- The callback was registered successfully.
   - QAPI_ERR_EXISTS -- A registered callback already exists.
*/
qapi_Status_t qapi_Radio_Register_Brownout_Callback(uint32_t BluetoothStackID, qapi_Radio_Brownout_CB_t BrownoutCB)
{
    Radio_Register_Brownout_Callback_Params_t *Params;
    qapi_Status_t ret_val;
    CallbackInfo_t CBInfo;

    if(BrownoutCB == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if(RadioContext.BrownoutCB != NULL)
    {
        return QAPI_ERR_EXISTS;
    }

    RadioContext.ShutdownCBHandle = qapi_PWR_Register_Shutdown_Callbacks(Radio_Shutdown_CB, Radio_Wakeup_CB, RADIO_WAKEUP_PRIORITY, NULL);

    if(RadioContext.ShutdownCBHandle == NULL)
    {
        return QAPI_ERR_NO_RESOURCE;
    }

    Params = IPC_GetSharedMemory(RADIO_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE);

    if(Params != NULL)
    {
        CBInfo.FileID = FILE_ID_RADIO;
        CBInfo.CallbackID = CALLBACK_ID_RADIO_BROWNOUT;
        CBInfo.CallbackKey = 0;
        CBInfo.AppFunction = (void *)BrownoutCB;
        Params->BluetoothStackID = BluetoothStackID;

        if(Callback_Register(&RadioContext.CallbackHandle, Radio_Brownout_Callback_Handler, &CBInfo, false) == 0)
        {
            Callback_SetPersist(RadioContext.CallbackHandle, true);

            ret_val = (qapi_Status_t)IPC_SendFunctionCall(FILE_ID_RADIO, FUNCTION_ID_RADIO_REGISTER_BROWNOUT_CALLBACK, RADIO_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE, (uint8_t *)Params);

            if(ret_val == 0)
            {
                RadioContext.BrownoutCB = BrownoutCB;
            }
            else
            {
                Callback_UnregisterByHandle(RadioContext.CallbackHandle);
                RadioContext.BrownoutCB = NULL;
                RadioContext.CallbackHandle = 0;

                ret_val = QAPI_ERROR;
            }
        }
        else
            ret_val = QAPI_ERR_NO_RESOURCE;

        IPC_FreeSharedMemory(Params);
    }
    else
        ret_val = QAPI_ERR_NO_MEMORY;

    if(ret_val != 0)
    {
        qapi_PWR_Unregister_Callback(RadioContext.ShutdownCBHandle);
        RadioContext.ShutdownCBHandle = NULL;
    }

    return ret_val;
}

/**
   @brief Unregisters the brownout callback.

   The previously registered brownout callback is unregistered upon
   successful completion

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] BrownoutCB        The previously registered Brownout CB.

   @return
   - QAPI_OK            --  The callback was unregistered successfully.
   - QAPI_ERROR         --  The callback was not unregistered successfully.
   - QAPI_ERR_NO_ENTRY  --  A callback was not previously registered.
*/
qapi_Status_t qapi_Radio_Unregister_Brownout_Callback(uint32_t BluetoothStackID, qapi_Radio_Brownout_CB_t BrownoutCB)
{
    qapi_Status_t RetVal;
    Radio_Un_Register_Brownout_Callback_Params_t *Params;

    if((RadioContext.BrownoutCB != NULL) && (BrownoutCB == RadioContext.BrownoutCB))
    {
        Params = IPC_GetSharedMemory(RADIO_UN_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE);

        if(Params != NULL)
        {
            Params->BluetoothStackID = BluetoothStackID;

            RetVal = (qapi_Status_t)IPC_SendFunctionCall(FILE_ID_RADIO, FUNCTION_ID_RADIO_UN_REGISTER_BROWNOUT_CALLBACK, RADIO_UN_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE, (uint8_t *)Params);

            if(RetVal == 0)
            {
                if(RadioContext.ShutdownCBHandle != NULL)
                {
                    qapi_PWR_Unregister_Callback(RadioContext.ShutdownCBHandle);
                    RadioContext.ShutdownCBHandle = NULL;
                }

                Callback_UnregisterByHandle(RadioContext.CallbackHandle);

                RadioContext.BrownoutCB = NULL;
            }

            IPC_FreeSharedMemory(Params);
        }
        else
            RetVal = QAPI_ERR_NO_MEMORY;
    }
    else
        RetVal = QAPI_ERR_NO_ENTRY;

    return RetVal;
}

/**
   @brief Suspends all radio activity.

   All radio activity is suspended upon successful completion. It is the
   caller's responsibility to resume radio activity in a timely manner in order
   to avoid timeout conditions that may occur with the Bluetooth subsystem.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().

   @return
   - QAPI_OK    -- Radio activity was successfully suspended.
   - QAPI_ERROR -- A failure occurred while suspending radio activity.
*/
qapi_Status_t qapi_Radio_Suspend(uint32_t BluetoothStackID)
{
    qapi_Status_t RetVal;
    Radio_Suspend_Params_t *Params;

    Params = IPC_GetSharedMemory(RADIO_SUSPEND_PARAMS_SIZE);

    if(Params != NULL)
    {
        Params->BluetoothStackID = BluetoothStackID;
        RetVal = (qapi_Status_t)IPC_SendFunctionCall(FILE_ID_RADIO, FUNCTION_ID_RADIO_SUSPEND, RADIO_SUSPEND_PARAMS_SIZE, (uint8_t *)Params);
        IPC_FreeSharedMemory(Params);
    }
    else
        RetVal = QAPI_ERR_NO_MEMORY;

    return RetVal;
}

/**
   @brief Resumes previously suspended radio activity.

   Previously suspended radio activity shall resume upon successful completion.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().

   @return
   - QAPI_OK    -- Radio activity was successfully resumed.
   - QAPI_ERROR -- Radio was not in the suspended state or a failure occurred
                 while resuming radio activity.
*/
qapi_Status_t qapi_Radio_Resume(uint32_t BluetoothStackID)
{
    qapi_Status_t RetVal;
    Radio_Resume_Params_t *Params;

    Params = IPC_GetSharedMemory(RADIO_RESUME_PARAMS_SIZE);

    if(Params != NULL)
    {
        Params->BluetoothStackID = BluetoothStackID;
        RetVal = (qapi_Status_t)IPC_SendFunctionCall(FILE_ID_RADIO, FUNCTION_ID_RADIO_RESUME, RADIO_RESUME_PARAMS_SIZE, (uint8_t *)Params);
        IPC_FreeSharedMemory(Params);
    }
    else
        RetVal = QAPI_ERR_NO_MEMORY;

    return RetVal;
}

/**
   @brief Sets the maximum transmit power that shall be allowed.

   Sets the maximum transmit power that shall be allowed by the radio.

   @param[in] BluetoothStackID  The StackID for an active Bluetooth Stack returned by qapi_BLE_BSC_Initialize().
   @param[in] dBm               The maximum transmit power (in dBm) that is allowed. This value must be between
                                -31 dBm and + 7dBm.

   @return
   - QAPI_OK    -- The maximum transmit power was successfully changed.
   - QAPI_ERROR -- A failure occurred while changing the maximum transmit power.
*/
qapi_Status_t qapi_Radio_Set_Max_Tx_Power(uint32_t BluetoothStackID, int8_t dBm)
{
    qapi_Status_t RetVal;
    Radio_Set_Max_Tx_Power_Params_t *Params;

    Params = IPC_GetSharedMemory(RADIO_SET_MAX_TX_POWER_PARAMS_SIZE);

    if(Params != NULL)
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->dBm = dBm;
        RetVal = (qapi_Status_t)IPC_SendFunctionCall(FILE_ID_RADIO, FUNCTION_ID_RADIO_SET_MAX_TX_POWER, RADIO_SET_MAX_TX_POWER_PARAMS_SIZE, (uint8_t *)Params);
        IPC_FreeSharedMemory(Params);
    }
    else
        RetVal = QAPI_ERR_NO_MEMORY;

    return RetVal;
}
