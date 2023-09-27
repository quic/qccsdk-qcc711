/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "BSCAPI_cb_params.h"
#include "BSCAPI_cb_m3.h"
#include "callback.h"

void BSC_Timer_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    BSC_Timer_Callback_Params_t *Params = (BSC_Timer_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(BSC_Timer_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_BSC_Timer_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->TimerID, KeyedCBInfo.AppParam);
        }
    }
}

void BSC_Debug_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    BSC_Debug_Callback_Params_t *Params = (BSC_Debug_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(BSC_Debug_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_BSC_Debug_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->PacketSent, Params->HCIPacket, KeyedCBInfo.AppParam);
        }
    }
}

void BSC_AsynchronousCallbackFunction_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    BSC_AsynchronousCallbackFunction_Params_t *Params = (BSC_AsynchronousCallbackFunction_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(BSC_AsynchronousCallbackFunction_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_BSC_AsynchronousCallbackFunction_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, KeyedCBInfo.AppParam);
        }
    }
}

