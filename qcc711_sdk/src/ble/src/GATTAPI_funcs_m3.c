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

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Register_Connection_Events(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Event_Callback_t ConnectionEventCallback, unsigned long CallbackParameter)
{
    GATT_Register_Connection_Events_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_REGISTER_CONNECTION_EVENTS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
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
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_REGISTER_CONNECTION_EVENTS, MessageSize, (uint8_t *)Params);

            if(ConnectionEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Un_Register_Connection_Events(uint32_t BluetoothStackID, uint32_t EventCallbackID)
{
    GATT_Un_Register_Connection_Events_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_UN_REGISTER_CONNECTION_EVENTS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->EventCallbackID = EventCallbackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_UN_REGISTER_CONNECTION_EVENTS, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_GATTAPI, CALLBACK_ID_GATT_CONNECTION_EVENT_CALLBACK_T, EventCallbackID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Connection_Request_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t AcceptConnection)
{
    GATT_Connection_Request_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_CONNECTION_REQUEST_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->AcceptConnection = *((boolean_t *)&AcceptConnection);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_CONNECTION_REQUEST_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

void QAPI_BLE_BTPSAPI qapi_BLE_GATT_Un_Register_Service(uint32_t BluetoothStackID, uint32_t ServiceID)
{
    GATT_Un_Register_Service_Params_t *Params;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_UN_REGISTER_SERVICE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ServiceID = ServiceID;

        IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_UN_REGISTER_SERVICE, MessageSize, (uint8_t *)Params);

        Callback_UnregisterByKey(FILE_ID_GATTAPI, CALLBACK_ID_GATT_SERVER_EVENT_CALLBACK_T, ServiceID);

        IPC_FreeSharedMemory(Params);
    }
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint32_t DataLength, uint8_t *Data)
{
    GATT_Read_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_READ_RESPONSE_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * DataLength));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_READ_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        Params->DataLength = DataLength;
        if(Data != NULL)
        {
            Params->Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * DataLength));
            memscpy(Params->Data, (sizeof(uint8_t) * DataLength), Data, (sizeof(uint8_t) * DataLength));
        }
        else
        {
            Params->Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_READ_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Response(uint32_t BluetoothStackID, uint32_t TransactionID)
{
    GATT_Write_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_WRITE_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_WRITE_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Execute_Write_Response(uint32_t BluetoothStackID, uint32_t TransactionID)
{
    GATT_Execute_Write_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_EXECUTE_WRITE_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_EXECUTE_WRITE_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Error_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint16_t AttributeOffset, uint8_t ErrorCode)
{
    GATT_Error_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_ERROR_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        Params->AttributeOffset = AttributeOffset;
        Params->ErrorCode = ErrorCode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_ERROR_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Indication(uint32_t BluetoothStackID, uint32_t ServiceID, uint32_t ConnectionID, uint16_t AttributeOffset, uint16_t AttributeValueLength, uint8_t *AttributeValue)
{
    GATT_Handle_Value_Indication_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_HANDLE_VALUE_INDICATION_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * AttributeValueLength));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_HANDLE_VALUE_INDICATION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ServiceID = ServiceID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeOffset = AttributeOffset;
        Params->AttributeValueLength = AttributeValueLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * AttributeValueLength));
            memscpy(Params->AttributeValue, (sizeof(uint8_t) * AttributeValueLength), AttributeValue, (sizeof(uint8_t) * AttributeValueLength));
        }
        else
        {
            Params->AttributeValue = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_HANDLE_VALUE_INDICATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Notification(uint32_t BluetoothStackID, uint32_t ServiceID, uint32_t ConnectionID, uint16_t AttributeOffset, uint16_t AttributeValueLength, uint8_t *AttributeValue)
{
    GATT_Handle_Value_Notification_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_HANDLE_VALUE_NOTIFICATION_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * AttributeValueLength));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_HANDLE_VALUE_NOTIFICATION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ServiceID = ServiceID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeOffset = AttributeOffset;
        Params->AttributeValueLength = AttributeValueLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * AttributeValueLength));
            memscpy(Params->AttributeValue, (sizeof(uint8_t) * AttributeValueLength), AttributeValue, (sizeof(uint8_t) * AttributeValueLength));
        }
        else
        {
            Params->AttributeValue = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_HANDLE_VALUE_NOTIFICATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GATT_Verify_Signature(uint32_t BluetoothStackID, uint32_t ServiceID, uint16_t AttributeOffset, uint32_t AttributeValueLength, uint8_t *AttributeValue, qapi_BLE_ATT_Authentication_Signature_t *ReceivedSignature, qapi_BLE_Encryption_Key_t *CSRK)
{
    GATT_Verify_Signature_Params_t *Params;
    boolean_t ret_val = false;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_VERIFY_SIGNATURE_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * AttributeValueLength)) + ALIGN32(sizeof(qapi_BLE_ATT_Authentication_Signature_t)) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_VERIFY_SIGNATURE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ServiceID = ServiceID;
        Params->AttributeOffset = AttributeOffset;
        Params->AttributeValueLength = AttributeValueLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * AttributeValueLength));
            memscpy(Params->AttributeValue, (sizeof(uint8_t) * AttributeValueLength), AttributeValue, (sizeof(uint8_t) * AttributeValueLength));
        }
        else
        {
            Params->AttributeValue = NULL;
        }
        if(ReceivedSignature != NULL)
        {
            Params->ReceivedSignature = (qapi_BLE_ATT_Authentication_Signature_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_ATT_Authentication_Signature_t));
            memscpy(Params->ReceivedSignature, sizeof(qapi_BLE_ATT_Authentication_Signature_t), ReceivedSignature, sizeof(qapi_BLE_ATT_Authentication_Signature_t));
        }
        else
        {
            Params->ReceivedSignature = NULL;
        }
        if(CSRK != NULL)
        {
            Params->CSRK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->CSRK, sizeof(qapi_BLE_Encryption_Key_t), CSRK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->CSRK = NULL;
        }

        ret_val = (boolean_t)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_VERIFY_SIGNATURE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data)
{
    GATT_Service_Changed_Read_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_SERVICE_CHANGED_READ_RESPONSE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_Service_Changed_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_SERVICE_CHANGED_READ_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        if(Service_Changed_Data != NULL)
        {
            Params->Service_Changed_Data = (qapi_BLE_GATT_Service_Changed_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Service_Changed_Data_t));
            memscpy(Params->Service_Changed_Data, sizeof(qapi_BLE_GATT_Service_Changed_Data_t), Service_Changed_Data, sizeof(qapi_BLE_GATT_Service_Changed_Data_t));
        }
        else
        {
            Params->Service_Changed_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_SERVICE_CHANGED_READ_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_CCCD_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint16_t CCCD)
{
    GATT_Service_Changed_CCCD_Read_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_SERVICE_CHANGED_CCCD_READ_RESPONSE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        Params->CCCD = CCCD;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_SERVICE_CHANGED_CCCD_READ_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_Indication(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data)
{
    GATT_Service_Changed_Indication_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_SERVICE_CHANGED_INDICATION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_Service_Changed_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_SERVICE_CHANGED_INDICATION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(Service_Changed_Data != NULL)
        {
            Params->Service_Changed_Data = (qapi_BLE_GATT_Service_Changed_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Service_Changed_Data_t));
            memscpy(Params->Service_Changed_Data, sizeof(qapi_BLE_GATT_Service_Changed_Data_t), Service_Changed_Data, sizeof(qapi_BLE_GATT_Service_Changed_Data_t));
        }
        else
        {
            Params->Service_Changed_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_SERVICE_CHANGED_INDICATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_Database_Hash(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_Encrypted_Data_t *Database_Hash)
{
    GATT_Query_Connection_Database_Hash_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_CONNECTION_DATABASE_HASH_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encrypted_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_CONNECTION_DATABASE_HASH_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(Database_Hash != NULL)
        {
            Params->Database_Hash = (qapi_BLE_Encrypted_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encrypted_Data_t));
        }
        else
        {
            Params->Database_Hash = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_CONNECTION_DATABASE_HASH, MessageSize, (uint8_t *)Params);

        if(Database_Hash != NULL)
            memscpy(Database_Hash, sizeof(qapi_BLE_Encrypted_Data_t), Params->Database_Hash, sizeof(qapi_BLE_Encrypted_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Database_Hash(uint32_t BluetoothStackID, qapi_BLE_Encrypted_Data_t *Database_Hash)
{
    GATT_Query_Database_Hash_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_DATABASE_HASH_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encrypted_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_DATABASE_HASH_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(Database_Hash != NULL)
        {
            Params->Database_Hash = (qapi_BLE_Encrypted_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encrypted_Data_t));
        }
        else
        {
            Params->Database_Hash = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_DATABASE_HASH, MessageSize, (uint8_t *)Params);

        if(Database_Hash != NULL)
            memscpy(Database_Hash, sizeof(qapi_BLE_Encrypted_Data_t), Params->Database_Hash, sizeof(qapi_BLE_Encrypted_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Lock_Database(uint32_t BluetoothStackID)
{
    GATT_Lock_Database_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_LOCK_DATABASE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_LOCK_DATABASE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_UnLock_Database(uint32_t BluetoothStackID)
{
    GATT_UnLock_Database_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_UNLOCK_DATABASE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_UNLOCK_DATABASE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Exchange_MTU_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t RequestedMTU, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Exchange_MTU_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_EXCHANGE_MTU_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->RequestedMTU = RequestedMTU;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_EXCHANGE_MTU_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Services(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t StartingHandle, uint16_t EndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Discover_Services_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_DISCOVER_SERVICES_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->StartingHandle = StartingHandle;
        Params->EndingHandle = EndingHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_DISCOVER_SERVICES, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Services_By_UUID(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t StartingHandle, uint16_t EndingHandle, qapi_BLE_GATT_UUID_t *UUID, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Discover_Services_By_UUID_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_DISCOVER_SERVICES_BY_UUID_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_UUID_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_DISCOVER_SERVICES_BY_UUID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->StartingHandle = StartingHandle;
        Params->EndingHandle = EndingHandle;
        if(UUID != NULL)
        {
            Params->UUID = (qapi_BLE_GATT_UUID_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_UUID_t));
            memscpy(Params->UUID, sizeof(qapi_BLE_GATT_UUID_t), UUID, sizeof(qapi_BLE_GATT_UUID_t));
        }
        else
        {
            Params->UUID = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_DISCOVER_SERVICES_BY_UUID, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Included_Services(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t ServiceStartingHandle, uint16_t ServiceEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Discover_Included_Services_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_DISCOVER_INCLUDED_SERVICES_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->ServiceStartingHandle = ServiceStartingHandle;
        Params->ServiceEndingHandle = ServiceEndingHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_DISCOVER_INCLUDED_SERVICES, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Characteristics(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t ServiceStartingHandle, uint16_t ServiceEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Discover_Characteristics_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_DISCOVER_CHARACTERISTICS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->ServiceStartingHandle = ServiceStartingHandle;
        Params->ServiceEndingHandle = ServiceEndingHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_DISCOVER_CHARACTERISTICS, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Characteristic_Descriptors(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t CharacteristicStartingHandle, uint16_t CharacteristicEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Discover_Characteristic_Descriptors_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->CharacteristicStartingHandle = CharacteristicStartingHandle;
        Params->CharacteristicEndingHandle = CharacteristicEndingHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Value_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Read_Value_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_READ_VALUE_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_READ_VALUE_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Long_Value_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeOffset, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Read_Long_Value_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_READ_LONG_VALUE_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->AttributeOffset = AttributeOffset;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_READ_LONG_VALUE_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Value_By_UUID_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_UUID_t *AttributeUUID, uint16_t ServiceStartHandle, uint16_t ServiceEndHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Read_Value_By_UUID_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_READ_VALUE_BY_UUID_REQUEST_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_UUID_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_READ_VALUE_BY_UUID_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(AttributeUUID != NULL)
        {
            Params->AttributeUUID = (qapi_BLE_GATT_UUID_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_UUID_t));
            memscpy(Params->AttributeUUID, sizeof(qapi_BLE_GATT_UUID_t), AttributeUUID, sizeof(qapi_BLE_GATT_UUID_t));
        }
        else
        {
            Params->AttributeUUID = NULL;
        }
        Params->ServiceStartHandle = ServiceStartHandle;
        Params->ServiceEndHandle = ServiceEndHandle;
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_READ_VALUE_BY_UUID_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Multiple_Values_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t NumberOfHandles, uint16_t *AttributeHandleList, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Read_Multiple_Values_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_READ_MULTIPLE_VALUES_REQUEST_PARAMS_SIZE) + ALIGN32((sizeof(uint16_t) * NumberOfHandles));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_READ_MULTIPLE_VALUES_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->NumberOfHandles = NumberOfHandles;
        if(AttributeHandleList != NULL)
        {
            Params->AttributeHandleList = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint16_t) * NumberOfHandles));
            memscpy(Params->AttributeHandleList, (sizeof(uint16_t) * NumberOfHandles), AttributeHandleList, (sizeof(uint16_t) * NumberOfHandles));
        }
        else
        {
            Params->AttributeHandleList = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_READ_MULTIPLE_VALUES_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, void *AttributeValue, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Write_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_WRITE_REQUEST_PARAMS_SIZE) + ALIGN32(AttributeLength);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_WRITE_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->AttributeLength = AttributeLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (void *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + AttributeLength);
            memscpy(Params->AttributeValue, AttributeLength, AttributeValue, AttributeLength);
        }
        else
        {
            Params->AttributeValue = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_WRITE_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Without_Response_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, void *AttributeValue)
{
    GATT_Write_Without_Response_Request_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_WRITE_WITHOUT_RESPONSE_REQUEST_PARAMS_SIZE) + ALIGN32(AttributeLength);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_WRITE_WITHOUT_RESPONSE_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->AttributeLength = AttributeLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (void *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + AttributeLength);
            memscpy(Params->AttributeValue, AttributeLength, AttributeValue, AttributeLength);
        }
        else
        {
            Params->AttributeValue = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_WRITE_WITHOUT_RESPONSE_REQUEST, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Signed_Write_Without_Response(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint32_t SignCounter, uint16_t AttributeLength, void *AttributeValue, qapi_BLE_Encryption_Key_t *CSRK)
{
    GATT_Signed_Write_Without_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_SIGNED_WRITE_WITHOUT_RESPONSE_PARAMS_SIZE) + ALIGN32(AttributeLength) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_SIGNED_WRITE_WITHOUT_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->SignCounter = SignCounter;
        Params->AttributeLength = AttributeLength;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (void *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + AttributeLength);
            memscpy(Params->AttributeValue, AttributeLength, AttributeValue, AttributeLength);
        }
        else
        {
            Params->AttributeValue = NULL;
        }
        if(CSRK != NULL)
        {
            Params->CSRK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->CSRK, sizeof(qapi_BLE_Encryption_Key_t), CSRK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->CSRK = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_SIGNED_WRITE_WITHOUT_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Prepare_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, uint16_t AttributeValueOffset, void *AttributeValue, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Prepare_Write_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_PREPARE_WRITE_REQUEST_PARAMS_SIZE) + ALIGN32(AttributeLength);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_PREPARE_WRITE_REQUEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->AttributeHandle = AttributeHandle;
        Params->AttributeLength = AttributeLength;
        Params->AttributeValueOffset = AttributeValueOffset;
        if(AttributeValue != NULL)
        {
            Params->AttributeValue = (void *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + AttributeLength);
            memscpy(Params->AttributeValue, AttributeLength, AttributeValue, AttributeLength);
        }
        else
        {
            Params->AttributeValue = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_PREPARE_WRITE_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Execute_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, boolean_t CancelWrite, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter)
{
    GATT_Execute_Write_Request_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_EXECUTE_WRITE_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->CancelWrite = *((boolean_t *)&CancelWrite);
        Params->CallbackParameter = CallbackParameter;

        if(ClientEventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)ClientEventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ClientEventCallback == NULL) || (Callback_Register(&CBHandle, GATT_Client_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_EXECUTE_WRITE_REQUEST, MessageSize, (uint8_t *)Params);

            if(ClientEventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Confirmation(uint32_t BluetoothStackID, uint32_t ConnectionID, uint32_t TransactionID)
{
    GATT_Handle_Value_Confirmation_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_HANDLE_VALUE_CONFIRMATION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->TransactionID = TransactionID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_HANDLE_VALUE_CONFIRMATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Start_Service_Discovery(uint32_t BluetoothStackID, uint32_t ConnectionID, uint32_t NumberOfUUID, qapi_BLE_GATT_UUID_t *UUIDList, qapi_BLE_GATT_Service_Discovery_Event_Callback_t ServiceDiscoveryCallback, unsigned long CallbackParameter)
{
    GATT_Start_Service_Discovery_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_START_SERVICE_DISCOVERY_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_START_SERVICE_DISCOVERY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        Params->NumberOfUUID = NumberOfUUID;
        if(UUIDList != NULL)
        {
            Params->UUIDList = (qapi_BLE_GATT_UUID_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));
            memscpy(Params->UUIDList, (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID), UUIDList, (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));
        }
        else
        {
            Params->UUIDList = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ServiceDiscoveryCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_SERVICE_DISCOVERY_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = ConnectionID;
            CBInfo.AppFunction = (void *)ServiceDiscoveryCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ServiceDiscoveryCallback == NULL) || (Callback_Register(&CBHandle, GATT_Service_Discovery_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_START_SERVICE_DISCOVERY, MessageSize, (uint8_t *)Params);

            if(ServiceDiscoveryCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Start_Service_Discovery_Handle_Range(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Attribute_Handle_Group_t *DiscoveryHandleRange, uint32_t NumberOfUUID, qapi_BLE_GATT_UUID_t *UUIDList, qapi_BLE_GATT_Service_Discovery_Event_Callback_t ServiceDiscoveryCallback, unsigned long CallbackParameter)
{
    GATT_Start_Service_Discovery_Handle_Range_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_START_SERVICE_DISCOVERY_HANDLE_RANGE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t)) + ALIGN32((sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_START_SERVICE_DISCOVERY_HANDLE_RANGE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(DiscoveryHandleRange != NULL)
        {
            Params->DiscoveryHandleRange = (qapi_BLE_GATT_Attribute_Handle_Group_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
            memscpy(Params->DiscoveryHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), DiscoveryHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
        }
        else
        {
            Params->DiscoveryHandleRange = NULL;
        }
        Params->NumberOfUUID = NumberOfUUID;
        if(UUIDList != NULL)
        {
            Params->UUIDList = (qapi_BLE_GATT_UUID_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));
            memscpy(Params->UUIDList, (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID), UUIDList, (sizeof(qapi_BLE_GATT_UUID_t) * NumberOfUUID));
        }
        else
        {
            Params->UUIDList = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(ServiceDiscoveryCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_GATTAPI;
            CBInfo.CallbackID = CALLBACK_ID_GATT_SERVICE_DISCOVERY_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = ConnectionID;
            CBInfo.AppFunction = (void *)ServiceDiscoveryCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((ServiceDiscoveryCallback == NULL) || (Callback_Register(&CBHandle, GATT_Service_Discovery_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_START_SERVICE_DISCOVERY_HANDLE_RANGE, MessageSize, (uint8_t *)Params);

            if(ServiceDiscoveryCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Stop_Service_Discovery(uint32_t BluetoothStackID, uint32_t ConnectionID)
{
    GATT_Stop_Service_Discovery_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_STOP_SERVICE_DISCOVERY_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_STOP_SERVICE_DISCOVERY, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_GATTAPI, CALLBACK_ID_GATT_SERVICE_DISCOVERY_EVENT_CALLBACK_T, ConnectionID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Cancel_Transaction(uint32_t BluetoothStackID, uint32_t TransactionID)
{
    GATT_Cancel_Transaction_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_CANCEL_TRANSACTION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_CANCEL_TRANSACTION, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_GATTAPI, CALLBACK_ID_GATT_CLIENT_EVENT_CALLBACK_T, TransactionID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Maximum_Supported_MTU(uint32_t BluetoothStackID, uint16_t *MTU)
{
    GATT_Query_Maximum_Supported_MTU_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_MAXIMUM_SUPPORTED_MTU_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_MAXIMUM_SUPPORTED_MTU_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(MTU != NULL)
        {
            Params->MTU = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->MTU = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_MAXIMUM_SUPPORTED_MTU, MessageSize, (uint8_t *)Params);

        if(MTU != NULL)
            memscpy(MTU, sizeof(uint16_t), Params->MTU, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Change_Maximum_Supported_MTU(uint32_t BluetoothStackID, uint16_t MTU)
{
    GATT_Change_Maximum_Supported_MTU_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_CHANGE_MAXIMUM_SUPPORTED_MTU_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->MTU = MTU;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_CHANGE_MAXIMUM_SUPPORTED_MTU, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_MTU(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t *MTU)
{
    GATT_Query_Connection_MTU_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_CONNECTION_MTU_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_CONNECTION_MTU_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionID = ConnectionID;
        if(MTU != NULL)
        {
            Params->MTU = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->MTU = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_CONNECTION_MTU, MessageSize, (uint8_t *)Params);

        if(MTU != NULL)
            memscpy(MTU, sizeof(uint16_t), Params->MTU, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_ID(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Type_t ConnectionType, qapi_BLE_BD_ADDR_t BD_ADDR, uint32_t *ConnectionID)
{
    GATT_Query_Connection_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_CONNECTION_ID_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_CONNECTION_ID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ConnectionType = ConnectionType;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(ConnectionID != NULL)
        {
            Params->ConnectionID = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->ConnectionID = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_CONNECTION_ID, MessageSize, (uint8_t *)Params);

        if(ConnectionID != NULL)
            memscpy(ConnectionID, sizeof(uint32_t), Params->ConnectionID, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Transaction_Opcode(uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t *Opcode)
{
    GATT_Query_Transaction_Opcode_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_TRANSACTION_OPCODE_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_TRANSACTION_OPCODE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TransactionID = TransactionID;
        if(Opcode != NULL)
        {
            Params->Opcode = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->Opcode = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_TRANSACTION_OPCODE, MessageSize, (uint8_t *)Params);

        if(Opcode != NULL)
            memscpy(Opcode, sizeof(uint8_t), Params->Opcode, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Set_Queuing_Parameters(uint32_t BluetoothStackID, uint32_t MaximumNumberDataPackets, uint32_t QueuedDataPacketsThreshold, boolean_t DiscardOldest)
{
    GATT_Set_Queuing_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_SET_QUEUING_PARAMETERS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->MaximumNumberDataPackets = MaximumNumberDataPackets;
        Params->QueuedDataPacketsThreshold = QueuedDataPacketsThreshold;
        Params->DiscardOldest = *((boolean_t *)&DiscardOldest);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_SET_QUEUING_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Get_Queuing_Parameters(uint32_t BluetoothStackID, uint32_t *MaximumNumberDataPackets, uint32_t *QueuedDataPacketsThreshold, boolean_t *DiscardOldest)
{
    GATT_Get_Queuing_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_GET_QUEUING_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(boolean_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_GET_QUEUING_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(MaximumNumberDataPackets != NULL)
        {
            Params->MaximumNumberDataPackets = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->MaximumNumberDataPackets = NULL;
        }
        if(QueuedDataPacketsThreshold != NULL)
        {
            Params->QueuedDataPacketsThreshold = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->QueuedDataPacketsThreshold = NULL;
        }
        if(DiscardOldest != NULL)
        {
            Params->DiscardOldest = (boolean_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(boolean_t));
        }
        else
        {
            Params->DiscardOldest = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_GET_QUEUING_PARAMETERS, MessageSize, (uint8_t *)Params);

        if(MaximumNumberDataPackets != NULL)
            memscpy(MaximumNumberDataPackets, sizeof(uint32_t), Params->MaximumNumberDataPackets, sizeof(uint32_t));

        if(QueuedDataPacketsThreshold != NULL)
            memscpy(QueuedDataPacketsThreshold, sizeof(uint32_t), Params->QueuedDataPacketsThreshold, sizeof(uint32_t));

        if(DiscardOldest != NULL)
            memscpy(DiscardOldest, sizeof(boolean_t), Params->DiscardOldest, sizeof(boolean_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Service_Range_Availability(uint32_t BluetoothStackID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroup)
{
    GATT_Query_Service_Range_Availability_Params_t *Params;
    boolean_t ret_val = false;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GATT_QUERY_SERVICE_RANGE_AVAILABILITY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GATT_QUERY_SERVICE_RANGE_AVAILABILITY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(ServiceHandleGroup != NULL)
        {
            Params->ServiceHandleGroup = (qapi_BLE_GATT_Attribute_Handle_Group_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
            memscpy(Params->ServiceHandleGroup, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), ServiceHandleGroup, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));
        }
        else
        {
            Params->ServiceHandleGroup = NULL;
        }

        ret_val = (boolean_t)IPC_SendFunctionCall(FILE_ID_GATTAPI, FUNCTION_ID_GATT_QUERY_SERVICE_RANGE_AVAILABILITY, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

