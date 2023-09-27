/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_l2cap.h"
#include "L2CAPAPI_params.h"
#include "L2CAPAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Un_Register_Fixed_Channel(uint32_t BluetoothStackID, uint16_t FCID)
{
    L2CA_Un_Register_Fixed_Channel_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_UN_REGISTER_FIXED_CHANNEL_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->FCID = FCID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_UN_REGISTER_FIXED_CHANNEL, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_L2CAPAPI, CALLBACK_ID_L2CA_EVENT_CALLBACK_T, FCID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Connect_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t LE_PSM, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter)
{
    L2CA_LE_Connect_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_CONNECT_REQUEST_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(L2CA_LE_CONNECT_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->LE_PSM = LE_PSM;
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
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_CONNECT_REQUEST, MessageSize, (uint8_t *)Params);

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

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Disconnect_Request(uint32_t BluetoothStackID, uint16_t LCID)
{
    L2CA_LE_Disconnect_Request_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_DISCONNECT_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->LCID = LCID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_DISCONNECT_REQUEST, MessageSize, (uint8_t *)Params);

        if(ret_val < 0)
            Callback_UnregisterByKey(FILE_ID_L2CAPAPI, CALLBACK_ID_L2CA_EVENT_CALLBACK_T, LCID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Disconnect_Response(uint32_t BluetoothStackID, uint16_t LCID)
{
    L2CA_LE_Disconnect_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_DISCONNECT_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->LCID = LCID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_DISCONNECT_RESPONSE, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_L2CAPAPI, CALLBACK_ID_L2CA_EVENT_CALLBACK_T, LCID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Fixed_Channel_Data_Write(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, uint16_t Data_Length, uint8_t *Data)
{
    L2CA_Fixed_Channel_Data_Write_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Data_Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(L2CA_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->FCID = FCID;
        Params->Data_Length = Data_Length;
        if(Data != NULL)
        {
            Params->Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Data_Length));
            memscpy(Params->Data, (sizeof(uint8_t) * Data_Length), Data, (sizeof(uint8_t) * Data_Length));
        }
        else
        {
            Params->Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_FIXED_CHANNEL_DATA_WRITE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Enhanced_Fixed_Channel_Data_Write(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data)
{
    L2CA_Enhanced_Fixed_Channel_Data_Write_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_ENHANCED_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_L2CA_Queueing_Parameters_t)) + ALIGN32((sizeof(uint8_t) * Data_Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(L2CA_ENHANCED_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->FCID = FCID;
        if(QueueingParameters != NULL)
        {
            Params->QueueingParameters = (qapi_BLE_L2CA_Queueing_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_L2CA_Queueing_Parameters_t));
            memscpy(Params->QueueingParameters, sizeof(qapi_BLE_L2CA_Queueing_Parameters_t), QueueingParameters, sizeof(qapi_BLE_L2CA_Queueing_Parameters_t));
        }
        else
        {
            Params->QueueingParameters = NULL;
        }
        Params->Data_Length = Data_Length;
        if(Data != NULL)
        {
            Params->Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Data_Length));
            memscpy(Params->Data, (sizeof(uint8_t) * Data_Length), Data, (sizeof(uint8_t) * Data_Length));
        }
        else
        {
            Params->Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_ENHANCED_FIXED_CHANNEL_DATA_WRITE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Enhanced_Dynamic_Channel_Data_Write(uint32_t BluetoothStackID, uint16_t LCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data)
{
    L2CA_Enhanced_Dynamic_Channel_Data_Write_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_ENHANCED_DYNAMIC_CHANNEL_DATA_WRITE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_L2CA_Queueing_Parameters_t)) + ALIGN32((sizeof(uint8_t) * Data_Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(L2CA_ENHANCED_DYNAMIC_CHANNEL_DATA_WRITE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->LCID = LCID;
        if(QueueingParameters != NULL)
        {
            Params->QueueingParameters = (qapi_BLE_L2CA_Queueing_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_L2CA_Queueing_Parameters_t));
            memscpy(Params->QueueingParameters, sizeof(qapi_BLE_L2CA_Queueing_Parameters_t), QueueingParameters, sizeof(qapi_BLE_L2CA_Queueing_Parameters_t));
        }
        else
        {
            Params->QueueingParameters = NULL;
        }
        Params->Data_Length = Data_Length;
        if(Data != NULL)
        {
            Params->Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Data_Length));
            memscpy(Params->Data, (sizeof(uint8_t) * Data_Length), Data, (sizeof(uint8_t) * Data_Length));
        }
        else
        {
            Params->Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_ENHANCED_DYNAMIC_CHANNEL_DATA_WRITE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Flush_Channel_Data(uint32_t BluetoothStackID, uint16_t CID)
{
    L2CA_LE_Flush_Channel_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_FLUSH_CHANNEL_DATA_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CID = CID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_FLUSH_CHANNEL_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Grant_Credits(uint32_t BluetoothStackID, uint16_t CID, uint16_t CreditsToGrant)
{
    L2CA_LE_Grant_Credits_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_LE_GRANT_CREDITS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CID = CID;
        Params->CreditsToGrant = CreditsToGrant;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_LE_GRANT_CREDITS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Connection_Parameter_Update_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t IntervalMin, uint16_t IntervalMax, uint16_t SlaveLatency, uint16_t TimeoutMultiplier)
{
    L2CA_Connection_Parameter_Update_Request_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_CONNECTION_PARAMETER_UPDATE_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->IntervalMin = IntervalMin;
        Params->IntervalMax = IntervalMax;
        Params->SlaveLatency = SlaveLatency;
        Params->TimeoutMultiplier = TimeoutMultiplier;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_CONNECTION_PARAMETER_UPDATE_REQUEST, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Connection_Parameter_Update_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Result)
{
    L2CA_Connection_Parameter_Update_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(L2CA_CONNECTION_PARAMETER_UPDATE_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Result = Result;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_L2CAPAPI, FUNCTION_ID_L2CA_CONNECTION_PARAMETER_UPDATE_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

