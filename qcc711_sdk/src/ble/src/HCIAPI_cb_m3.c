/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "HCIAPI_cb_params.h"
#include "HCIAPI_cb_m3.h"
#include "callback.h"

void HCI_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    HCI_Event_Callback_Params_t *Params = (HCI_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(HCI_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_HCI_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->HCI_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

void HCI_ACL_Data_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    HCI_ACL_Data_Callback_Params_t *Params = (HCI_ACL_Data_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(HCI_ACL_Data_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_HCI_ACL_Data_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->Connection_Handle, Params->Flags, Params->ACLDataLength, Params->ACLData, KeyedCBInfo.AppParam);
        }
    }
}

