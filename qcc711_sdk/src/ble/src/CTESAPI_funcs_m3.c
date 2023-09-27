/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_ctes.h"
#include "CTESAPI_params.h"
#include "CTESAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Initialize_Service(uint32_t BluetoothStackID, qapi_BLE_CTES_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID)
{
    CTES_Initialize_Service_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_INITIALIZE_SERVICE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(CTES_INITIALIZE_SERVICE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;
        if(ServiceID != NULL)
        {
            Params->ServiceID = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->ServiceID = NULL;
        }

        if(EventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_CTESAPI;
            CBInfo.CallbackID = CALLBACK_ID_CTES_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)EventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((EventCallback == NULL) || (Callback_Register(&CBHandle, CTES_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_INITIALIZE_SERVICE, MessageSize, (uint8_t *)Params);

            if(ServiceID != NULL)
                memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

            if(EventCallback != NULL)
            {
                if(!(ret_val == 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, qapi_BLE_CTES_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange)
{
    CTES_Initialize_Service_Handle_Range_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(CTES_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;
        if(ServiceID != NULL)
        {
            Params->ServiceID = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->ServiceID = NULL;
        }
        if(ServiceHandleRange != NULL)
        {
            Params->ServiceHandleRange = (qapi_BLE_GATT_Attribute_Handle_Group_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
            memscpy(Params->ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
        }
        else
        {
            Params->ServiceHandleRange = NULL;
        }

        if(EventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_CTESAPI;
            CBInfo.CallbackID = CALLBACK_ID_CTES_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)EventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((EventCallback == NULL) || (Callback_Register(&CBHandle, CTES_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_INITIALIZE_SERVICE_HANDLE_RANGE, MessageSize, (uint8_t *)Params);

            if(ServiceID != NULL)
                memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

            if(ServiceHandleRange != NULL)
                memscpy(ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), Params->ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

            if(EventCallback != NULL)
            {
                if(!(ret_val == 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID)
{
    CTES_Cleanup_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_CLEANUP_SERVICE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_CLEANUP_SERVICE, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_CTESAPI, CALLBACK_ID_CTES_EVENT_CALLBACK_T, InstanceID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

unsigned int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Query_Number_Attributes(void)
{
    unsigned int ret_val = -1;

    ret_val = (unsigned int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_QUERY_NUMBER_ATTRIBUTES, 0, NULL);


    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_CTE_Enable_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_CTE_Enable_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_CTE_ENABLE_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_CTE_ENABLE_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_CTE_Minimum_Length_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_CTE_Minimum_Length_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_CTE_MINIMUM_LENGTH_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_CTE_MINIMUM_LENGTH_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_Advertising_CTE_Transmit_Duration_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_Advertising_CTE_Transmit_Duration_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_Advertising_CTE_Interval_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_Advertising_CTE_Interval_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_CTES_Write_Advertising_CTE_PHY_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode)
{
    CTES_Write_Advertising_CTE_PHY_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(CTES_WRITE_ADVERTISING_CTE_PHY_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_CTESAPI, FUNCTION_ID_CTES_WRITE_ADVERTISING_CTE_PHY_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

