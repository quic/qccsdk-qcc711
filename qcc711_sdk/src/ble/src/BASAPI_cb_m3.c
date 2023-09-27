/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "BASAPI_cb_params.h"
#include "BASAPI_cb_m3.h"
#include "callback.h"

void BAS_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    BAS_Event_Callback_Params_t *Params = (BAS_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(BAS_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_BAS_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->BAS_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

