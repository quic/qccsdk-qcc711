/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_gatt.h"
#include "GATTAPI_params.h"
#include "GATTAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

typedef struct GATT_RetainedContext_s
{
    qapi_BLE_GATT_Connection_Event_Callback_t InitEventCallback;
    unsigned long CallbackParameter;
    uint32_t InitEventCallbackHandle;
} GATT_RetainedContext_t;

static GATT_RetainedContext_t GATT_RetainedContext __attribute__((section (".bss.retain")));

static const uint32_t SERVICE_ATTRIBUTE_ENTRY_LENGTHS[] =
{
   ALIGN32(QAPI_BLE_GATT_PRIMARY_SERVICE_16_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_PRIMARY_SERVICE_128_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_SECONDARY_SERVICE_16_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_SECONDARY_SERVICE_128_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_INCLUDE_DEFINITION_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_16_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_128_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_VALUE_16_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_VALUE_128_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_16_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_128_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_PRIMARY_SERVICE_32_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_SECONDARY_SERVICE_32_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_32_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_VALUE_32_ENTRY_DATA_SIZE),
   ALIGN32(QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_32_ENTRY_DATA_SIZE)
};

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Initialize(uint32_t BluetoothStackID, unsigned long Flags, qapi_BLE_GATT_Connection_Event_Callback_t ConnectionEventCallback, unsigned long CallbackParameter)
{
    GATT_Initialize_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_INITIALIZE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Flags = Flags;
        Params->CallbackParameter = CallbackParameter;

        if(ConnectionEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CONNECTION_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ConnectionEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ConnectionEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Connection_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_INITIALIZE, MessageSize, (uint8_t *)Params);

            if(ConnectionEventCallback != NULL)
            {
                if(!(ret_val == 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
                else
                {
                    GATT_RetainedContext.InitEventCallbackHandle = CBHandle;
                    GATT_RetainedContext.InitEventCallback = ConnectionEventCallback;
                    GATT_RetainedContext.CallbackParameter = CallbackParameter;
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Cleanup(uint32_t BluetoothStackID)
{
    GATT_Cleanup_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_CLEANUP_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_CLEANUP, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_GATTAPI, CALLBACK_ID_GATT_CONNECTION_EVENT_CALLBACK_T, 0);

        IPC_FreeSharedMemory(Params);
    }

    GATT_RetainedContext.InitEventCallback = NULL;

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Register_Service(uint32_t BluetoothStackID, uint8_t ServiceFlags, uint32_t NumberOfServiceAttributeEntries, qapi_BLE_GATT_Service_Attribute_Entry_t *ServiceTable, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroupResult, qapi_BLE_GATT_Server_Event_Callback_t ServerEventCallback, unsigned long CallbackParameter)
{
    GATT_Register_Service_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;
    uint32_t Index;
    uint8_t *MessagePtr;
    uint32_t EntriesSize = 0;
    uint32_t DataSize = 0;
    uint8_t *DataPtr;
    uint32_t CopyLen;

    MessageSize = ALIGN32(GATT_REGISTER_SERVICE_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t) * NumberOfServiceAttributeEntries)) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if((NumberOfServiceAttributeEntries > 0 ) && (ServiceTable))
    {
        for(Index = 0; Index < NumberOfServiceAttributeEntries; Index++)
        {
            EntriesSize += SERVICE_ATTRIBUTE_ENTRY_LENGTHS[ServiceTable[Index].Attribute_Entry_Type];

            if((ServiceTable[Index].Attribute_Entry_Type == QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E) && (ServiceTable[Index].Attribute_Value != NULL) && (QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_EXTENDED_PROPERTIES_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_UUID)))
            {
                /* This special descriptor MUST have its value supplied to the stack. */
                DataSize += ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_Length;
            }
        }
    }

    MessageSize += EntriesSize + DataSize;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        MessagePtr = (((uint8_t *)Params) + GATT_REGISTER_SERVICE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ServiceFlags = ServiceFlags;
        Params->NumberOfServiceAttributeEntries = NumberOfServiceAttributeEntries;
        if(ServiceTable != NULL)
        {
            Params->ServiceTable = (qapi_BLE_GATT_Service_Attribute_Entry_t *)MessagePtr;
            memscpy(Params->ServiceTable, (sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t) * NumberOfServiceAttributeEntries), ServiceTable, (sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t) * NumberOfServiceAttributeEntries));
            MessagePtr += ALIGN32(sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t) * NumberOfServiceAttributeEntries);
        }
        else
        {
            Params->ServiceTable = NULL;
        }
        if(ServiceHandleGroupResult != NULL)
        {
            Params->ServiceHandleGroupResult = (qapi_BLE_GATT_Attribute_Handle_Group_t *)MessagePtr;
            memscpy(Params->ServiceHandleGroupResult, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), ServiceHandleGroupResult, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
            MessagePtr += ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
        }
        else
        {
            Params->ServiceHandleGroupResult = NULL;
        }

        if(ServiceTable)
        {
            DataPtr = MessagePtr + EntriesSize;

            for(Index = 0; Index < NumberOfServiceAttributeEntries; Index++)
            {
                if(ServiceTable[Index].Attribute_Value)
                {
                    CopyLen = SERVICE_ATTRIBUTE_ENTRY_LENGTHS[ServiceTable[Index].Attribute_Entry_Type];

                    Params->ServiceTable[Index].Attribute_Value = (void *)MessagePtr;
                    memscpy(MessagePtr, CopyLen, ServiceTable[Index].Attribute_Value, CopyLen);
                    MessagePtr += CopyLen;

                    /* Extra handling for some types. */
                    switch(ServiceTable[Index].Attribute_Entry_Type)
                    {
                        case QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E:
                            /* These are app-specific values and don't need to be passed over IPC. */
                            ((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value = NULL;
                            ((qapi_BLE_GATT_Characteristic_Value_16_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value_Length = 0;
                            break;
                        case QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E:
                            /* These are app-specific values and don't need to be passed over IPC. */
                            ((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value = NULL;
                            ((qapi_BLE_GATT_Characteristic_Value_128_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value_Length = 0;
                            break;
                        case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E:
                            /* For this special descriptor, we need to actually pass the value over IPC for the stack to use. */
                            if(QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_EXTENDED_PROPERTIES_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_UUID))
                            {
                                if(((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor != NULL)
                                {
                                    CopyLen = ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_Length;
                                    ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor = DataPtr;
                                    memscpy(DataPtr, CopyLen, ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor, CopyLen);
                                    DataPtr += CopyLen;
                                }
                            }
                            else
                            {
                                /* These are app-specific values, so NULL them out over IPC. */
                                ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor = NULL;
                                ((qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_Length = 0;;
                            }
                            break;
                        case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E:
                            /* These are app-specific values and don't need to be passed over IPC. */
                            ((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor = NULL;
                            ((qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_Length = 0;;
                            break;
                        case QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E:
                            /* These are app-specific values and don't need to be passed over IPC. */
                            ((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value = NULL;
                            ((qapi_BLE_GATT_Characteristic_Value_32_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Value_Length = 0;
                            break;
                        case QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E:
                            /* These are app-specific values and don't need to be passed over IPC. */
                            ((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor = NULL;
                            ((qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t *)Params->ServiceTable[Index].Attribute_Value)->Characteristic_Descriptor_Length = 0;;
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        Params->CallbackParameter = CallbackParameter;

        if(ServerEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_SERVER_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ServerEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ServerEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Server_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_REGISTER_SERVICE, MessageSize, (uint8_t *)Params);

            if(ServiceHandleGroupResult != NULL)
                memscpy(ServiceHandleGroupResult, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), Params->ServiceHandleGroupResult, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

            if(ServerEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Bonded_Client_Data_Request_Response(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Bonded_Client_Data_t *Bonded_Client_Data)
{
    GATT_Bonded_Client_Data_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;

    uint32_t MessageSize = ALIGN32(GATT_BONDED_CLIENT_DATA_REQUEST_RESPONSE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_Bonded_Client_Data_t)) + ((Bonded_Client_Data == NULL) ? 0 : Bonded_Client_Data->Client_Supported_Features_Length);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_BONDED_CLIENT_DATA_REQUEST_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(Bonded_Client_Data != NULL)
        {
            Params->Bonded_Client_Data = (qapi_BLE_GATT_Bonded_Client_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Bonded_Client_Data_t));
            memscpy(Params->Bonded_Client_Data, sizeof(qapi_BLE_GATT_Bonded_Client_Data_t), Bonded_Client_Data, sizeof(qapi_BLE_GATT_Bonded_Client_Data_t));

            if(Bonded_Client_Data->Client_Supported_Features != NULL)
            {
                Params->Bonded_Client_Data->Client_Supported_Features = (((uint8_t *)Params) + Offset);
                memscpy(Params->Bonded_Client_Data->Client_Supported_Features, Params->Bonded_Client_Data->Client_Supported_Features_Length, Bonded_Client_Data->Client_Supported_Features, Bonded_Client_Data->Client_Supported_Features_Length);
            }
        }
        else
        {
            Params->Bonded_Client_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_BONDED_CLIENT_DATA_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int qapi_BLE_GATT_RestoreConnectionEventCallback(void)
{
    int ret_val = -1;
    CallbackInfo_t CBInfo;

    if(GATT_RetainedContext.InitEventCallback != NULL)
    {
        CBInfo.FileID = FILE_ID_GATTAPI;
        CBInfo.CallbackID = CALLBACK_ID_GATT_CONNECTION_EVENT_CALLBACK_T;
        CBInfo.AppFunction = (void *)GATT_RetainedContext.InitEventCallback;
        CBInfo.AppParam = GATT_RetainedContext.CallbackParameter;
        CBInfo.CallbackKey = 0;


        ret_val = Callback_SetByHandle(GATT_RetainedContext.InitEventCallbackHandle, GATT_Connection_Event_Callback_Handler, &CBInfo);

        if(ret_val != 0)
        {
            GATT_RetainedContext.InitEventCallback = NULL;
        }
    }

    return ret_val;
}
