/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "GATTAPI_cb_params.h"
#include "GATTAPI_cb_m3.h"
#include "callback.h"

void GATT_Connection_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    GATT_Connection_Event_Callback_Params_t *Params = (GATT_Connection_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(GATT_Connection_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_GATT_Connection_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->GATT_Connection_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

void GATT_Server_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    GATT_Server_Event_Callback_Params_t *Params = (GATT_Server_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(GATT_Server_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_GATT_Server_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->GATT_Server_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

