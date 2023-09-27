/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "GATTAPI_cb_params.h"
#include "GATTAPI_cb_m3.h"
#include "callback.h"

void GATT_Client_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    GATT_Client_Event_Callback_Params_t *Params = (GATT_Client_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(GATT_Client_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_GATT_Client_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->GATT_Client_Event_Data, KeyedCBInfo.AppParam);

            /* TODO Verify the reception of an event is always the end of a transaction. */
            Callback_UnregisterByHandle((uint32_t)Params->CallbackParameter);
        }
    }
}

void GATT_Service_Discovery_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    GATT_Service_Discovery_Event_Callback_Params_t *Params = (GATT_Service_Discovery_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(GATT_Service_Discovery_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            ((qapi_BLE_GATT_Service_Discovery_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->GATT_Service_Discovery_Event_Data, KeyedCBInfo.AppParam);

            /* Un-register the callback upon completion. */
            if(Params->GATT_Service_Discovery_Event_Data->Event_Data_Type == QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E)
            {
                Callback_UnregisterByHandle((uint32_t)Params->CallbackParameter);
            }
        }
    }
}

