/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_l2cap.h"
#include "L2CAPAPI_params.h"
#include "L2CAPAPI_cb_m3.h"
#include "L2CAPAPI_mnl_util.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Register_LE_PSM(uint32_t BluetoothStackID, uint16_t LE_PSM, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter)
{
    L2CA_Register_LE_PSM_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;

    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(L2CA_REGISTER_LE_PSM_PARAMS_SIZE))))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->LE_PSM = LE_PSM;
        Params->CallbackParameter = CallbackParameter;

        if(L2CA_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_L2CAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_L2CA_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)L2CA_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((L2CA_Event_Callback == NULL) || (Callback_Register(&CBHandle, L2CA_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_REGISTER_LE_PSM, L2CA_REGISTER_LE_PSM_PARAMS_SIZE, (uint8_t *)Params);

            if(L2CA_Event_Callback != NULL)
            {
                if(!(ret_val > 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
                else
                {
                    /* Flag this as a PSM entry. */
                    Callback_UpdateKey(CBHandle, (uintptr_t)(ret_val | L2CAP_CALLBACK_KEY_TYPE_PSMID));
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Un_Register_LE_PSM(uint32_t BluetoothStackID, uint32_t L2CAP_PSMID)
{
    L2CA_Un_Register_LE_PSM_Params_t *Params;
    int ret_val = -1;

    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(L2CA_UN_REGISTER_LE_PSM_PARAMS_SIZE))))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->L2CAP_PSMID = L2CAP_PSMID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_UN_REGISTER_LE_PSM, L2CA_UN_REGISTER_LE_PSM_PARAMS_SIZE, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_L2CAPAPI, CALLBACK_ID_L2CA_EVENT_CALLBACK_T, (L2CAP_PSMID | L2CAP_CALLBACK_KEY_TYPE_PSMID));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Connect_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t Identifier, uint16_t LCID, uint16_t Result, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters)
{
    L2CA_LE_Connect_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_CONNECT_RESPONSE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(L2CA_LE_CONNECT_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Identifier = Identifier;
        Params->LCID = LCID;
        Params->Result = Result;
        if(ChannelParameters != NULL)
        {
            Params->ChannelParameters = (qapi_BLE_L2CA_LE_Channel_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t));
            memscpy(Params->ChannelParameters, sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t), ChannelParameters, sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t));
        }
        else
        {
            Params->ChannelParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_CONNECT_RESPONSE, MessageSize, (uint8_t *)Params);

        /* NOTE: There is an assumption being made here that a failure to this call does not delete the callback in the stack.
         *       That assumption holds under reasonable circumstances, but is not necessarily guaranteed. Unfortuantely, there
         *       is not a way to tell with certainty as the error code is not indicative of what specifically happened. */
        if((ret_val == 0) && (Result != QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_SUCCESSFUL))
        {
            Callback_UnregisterByKey(FILE_ID_L2CAPAPI, CALLBACK_ID_L2CA_EVENT_CALLBACK_T, LCID);
        }

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Register_Fixed_Channel(uint32_t BluetoothStackID, uint16_t FixedChannel, void *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter)
{
    L2CA_Register_Fixed_Channel_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;

    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(L2CA_REGISTER_FIXED_CHANNEL_PARAMS_SIZE))))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->FixedChannel = FixedChannel;
        Params->CallbackParameter = CallbackParameter;

        /* This appears to be ignored by the stack, and has no real utility without an associated length? */
        Params->ChannelParameters = NULL;

        if(L2CA_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_L2CAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_L2CA_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)L2CA_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((L2CA_Event_Callback == NULL) || (Callback_Register(&CBHandle, L2CA_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_REGISTER_FIXED_CHANNEL, L2CA_REGISTER_FIXED_CHANNEL_PARAMS_SIZE, (uint8_t *)Params);

            if(L2CA_Event_Callback != NULL)
            {
                if(!(ret_val > 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
                else
                {
                    Callback_UpdateKey(CBHandle, (uintptr_t)ret_val);
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}
