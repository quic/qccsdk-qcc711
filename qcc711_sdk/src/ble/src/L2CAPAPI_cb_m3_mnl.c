/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "L2CAPAPI_cb_params.h"
#include "L2CAPAPI_cb_m3.h"
#include "L2CAPAPI_mnl_util.h"
#include "callback.h"
#include "qapi_ble_hcitypes.h"

void L2CA_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer)
{
    L2CA_Event_Callback_Params_t *Params = (L2CA_Event_Callback_Params_t *)Buffer;
    CallbackInfo_t KeyedCBInfo;

    if(BufferLength >= sizeof(L2CA_Event_Callback_Params_t))
    {
        if(Callback_Retrieve((uint32_t)Params->CallbackParameter, &KeyedCBInfo) == 0)
        {
            /* Process a few events manually for callback deletion first. */
            switch(Params->L2CA_Event_Data->L2CA_Event_Type)
            {
                case QAPI_BLE_ET_LE_DISCONNECT_INDICATION_E:
                    /* Non-zero Reason indicates this event is due to something link link loss rather than an actuall Disconnect Request
                     * L2CAP message. In this case, the channel is immediately invalidated, so we should delete the callback. In the zero
                     * Reason case, we are expected the application to send a Disconnect Response still. */
                    if(Params->L2CA_Event_Data->Event_Data.L2CA_LE_Disconnect_Indication->Reason != QAPI_BLE_HCI_ERROR_CODE_NO_ERROR)
                    {
                        /* If this callback was registered via PSM registration, then it won't be deleted. */
                        if((KeyedCBInfo.CallbackKey & L2CAP_CALLBACK_KEY_TYPE_MASK) == L2CAP_CALLBACK_KEY_TYPE_CID)
                            Callback_UnregisterByHandle((uint32_t)Params->CallbackParameter);
                    }
                    break;
                case QAPI_BLE_ET_LE_DISCONNECT_CONFIRMATION_E:
                    /* If this callback was registered via PSM registration, then it won't be deleted. */
                    if((KeyedCBInfo.CallbackKey & L2CAP_CALLBACK_KEY_TYPE_MASK) == L2CAP_CALLBACK_KEY_TYPE_CID)
                        Callback_UnregisterByHandle((uint32_t)Params->CallbackParameter);
                    break;
                default:
                    break;
            }

            ((qapi_BLE_L2CA_Event_Callback_t)KeyedCBInfo.AppFunction)(Params->BluetoothStackID, Params->L2CA_Event_Data, KeyedCBInfo.AppParam);
        }
    }
}

