/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "CTESAPI_cb_params.h"
#include "CTESAPI_cb_m3.h"
#include "callback.h"

void CTES_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    CTES_Event_Callback_Params_t *Params = (CTES_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(CTES_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_CTES_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->CTES_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

