/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_bas.h"
#include "BASAPI_params.h"
#include "BASAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Initialize_Service(uint32_t BluetoothStackID, qapi_BLE_BAS_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID)
{
    BAS_Initialize_Service_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_INITIALIZE_SERVICE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BAS_INITIALIZE_SERVICE_PARAMS_SIZE);
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
            CBInfo.FileID = FILE_ID_BASAPI;
            CBInfo.CallbackID = CALLBACK_ID_BAS_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)EventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((EventCallback == NULL) || (Callback_Register(&CBHandle, BAS_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_INITIALIZE_SERVICE, MessageSize, (uint8_t *)Params);

            if(ServiceID != NULL)
                memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

            if(EventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, qapi_BLE_BAS_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange)
{
    BAS_Initialize_Service_Handle_Range_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BAS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE);
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
            CBInfo.FileID = FILE_ID_BASAPI;
            CBInfo.CallbackID = CALLBACK_ID_BAS_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)EventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((EventCallback == NULL) || (Callback_Register(&CBHandle, BAS_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_INITIALIZE_SERVICE_HANDLE_RANGE, MessageSize, (uint8_t *)Params);

            if(ServiceID != NULL)
                memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

            if(ServiceHandleRange != NULL)
                memscpy(ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), Params->ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

            if(EventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID)
{
    BAS_Cleanup_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_CLEANUP_SERVICE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_CLEANUP_SERVICE, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_BASAPI, CALLBACK_ID_BAS_EVENT_CALLBACK_T, InstanceID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

unsigned int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Query_Number_Attributes(void)
{
    unsigned int ret_val = -1;

    ret_val = (unsigned int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_QUERY_NUMBER_ATTRIBUTES, 0, NULL);


    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Battery_Level_Read_Request_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t BatteryLevel)
{
    BAS_Battery_Level_Read_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_BATTERY_LEVEL_READ_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        Params->BatteryLevel = BatteryLevel;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_BATTERY_LEVEL_READ_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Battery_Level_Read_Request_Error_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t ErrorCode)
{
    BAS_Battery_Level_Read_Request_Error_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_BATTERY_LEVEL_READ_REQUEST_ERROR_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_BATTERY_LEVEL_READ_REQUEST_ERROR_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Query_Characteristic_Presentation_Format(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat)
{
    BAS_Query_Characteristic_Presentation_Format_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_QUERY_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BAS_QUERY_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(CharacteristicPresentationFormat != NULL)
        {
            Params->CharacteristicPresentationFormat = (qapi_BLE_BAS_Presentation_Format_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));
        }
        else
        {
            Params->CharacteristicPresentationFormat = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_QUERY_CHARACTERISTIC_PRESENTATION_FORMAT, MessageSize, (uint8_t *)Params);

        if(CharacteristicPresentationFormat != NULL)
            memscpy(CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t), Params->CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Set_Characteristic_Presentation_Format(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat)
{
    BAS_Set_Characteristic_Presentation_Format_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_SET_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BAS_SET_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(CharacteristicPresentationFormat != NULL)
        {
            Params->CharacteristicPresentationFormat = (qapi_BLE_BAS_Presentation_Format_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));
            memscpy(Params->CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t), CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));
        }
        else
        {
            Params->CharacteristicPresentationFormat = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_SET_CHARACTERISTIC_PRESENTATION_FORMAT, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Read_Client_Configuration_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t Client_Configuration)
{
    BAS_Read_Client_Configuration_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_READ_CLIENT_CONFIGURATION_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->TransactionID = TransactionID;
        Params->Client_Configuration = Client_Configuration;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_READ_CLIENT_CONFIGURATION_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Notify_Battery_Level(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, uint8_t BatteryLevel)
{
    BAS_Notify_Battery_Level_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_NOTIFY_BATTERY_LEVEL_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->ConnectionID = ConnectionID;
        Params->BatteryLevel = BatteryLevel;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_NOTIFY_BATTERY_LEVEL, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BAS_Decode_Characteristic_Presentation_Format(uint32_t ValueLength, uint8_t *Value, qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat)
{
    BAS_Decode_Characteristic_Presentation_Format_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BAS_DECODE_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * ValueLength)) + ALIGN32(sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BAS_DECODE_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE);
        Params->ValueLength = ValueLength;
        if(Value != NULL)
        {
            Params->Value = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * ValueLength));
            memscpy(Params->Value, (sizeof(uint8_t) * ValueLength), Value, (sizeof(uint8_t) * ValueLength));
        }
        else
        {
            Params->Value = NULL;
        }
        if(CharacteristicPresentationFormat != NULL)
        {
            Params->CharacteristicPresentationFormat = (qapi_BLE_BAS_Presentation_Format_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));
        }
        else
        {
            Params->CharacteristicPresentationFormat = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BASAPI, FUNCTION_ID_BAS_DECODE_CHARACTERISTIC_PRESENTATION_FORMAT, MessageSize, (uint8_t *)Params);

        if(CharacteristicPresentationFormat != NULL)
            memscpy(CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t), Params->CharacteristicPresentationFormat, sizeof(qapi_BLE_BAS_Presentation_Format_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

