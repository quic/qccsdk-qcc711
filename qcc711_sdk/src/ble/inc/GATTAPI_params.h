/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GATTAPI_PARAMS_H__
#define __GATTAPI_PARAMS_H__

#include "qapi_ble_gatt.h"
typedef struct _tagGATT_Initialize_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long Flags;
    unsigned long CallbackParameter;
} GATT_Initialize_Params_t;

#define GATT_INITIALIZE_PARAMS_SIZE sizeof(GATT_Initialize_Params_t)

typedef struct _tagGATT_Cleanup_Params_t
{
    uint32_t BluetoothStackID;
} GATT_Cleanup_Params_t;

#define GATT_CLEANUP_PARAMS_SIZE sizeof(GATT_Cleanup_Params_t)

typedef struct _tagGATT_Register_Connection_Events_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} GATT_Register_Connection_Events_Params_t;

#define GATT_REGISTER_CONNECTION_EVENTS_PARAMS_SIZE sizeof(GATT_Register_Connection_Events_Params_t)

typedef struct _tagGATT_Un_Register_Connection_Events_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t EventCallbackID;
} GATT_Un_Register_Connection_Events_Params_t;

#define GATT_UN_REGISTER_CONNECTION_EVENTS_PARAMS_SIZE sizeof(GATT_Un_Register_Connection_Events_Params_t)

typedef struct _tagGATT_Connection_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    boolean_t AcceptConnection;
} GATT_Connection_Request_Response_Params_t;

#define GATT_CONNECTION_REQUEST_RESPONSE_PARAMS_SIZE sizeof(GATT_Connection_Request_Response_Params_t)

typedef struct _tagGATT_Register_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t ServiceFlags;
    uint32_t NumberOfServiceAttributeEntries;
    qapi_BLE_GATT_Service_Attribute_Entry_t *ServiceTable;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroupResult;
    unsigned long CallbackParameter;
} GATT_Register_Service_Params_t;

#define GATT_REGISTER_SERVICE_PARAMS_SIZE sizeof(GATT_Register_Service_Params_t)

typedef struct _tagGATT_Un_Register_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ServiceID;
} GATT_Un_Register_Service_Params_t;

#define GATT_UN_REGISTER_SERVICE_PARAMS_SIZE sizeof(GATT_Un_Register_Service_Params_t)

typedef struct _tagGATT_Read_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint32_t DataLength;
    uint8_t *Data;
} GATT_Read_Response_Params_t;

#define GATT_READ_RESPONSE_PARAMS_SIZE sizeof(GATT_Read_Response_Params_t)

typedef struct _tagGATT_Write_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
} GATT_Write_Response_Params_t;

#define GATT_WRITE_RESPONSE_PARAMS_SIZE sizeof(GATT_Write_Response_Params_t)

typedef struct _tagGATT_Execute_Write_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
} GATT_Execute_Write_Response_Params_t;

#define GATT_EXECUTE_WRITE_RESPONSE_PARAMS_SIZE sizeof(GATT_Execute_Write_Response_Params_t)

typedef struct _tagGATT_Error_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint16_t AttributeOffset;
    uint8_t ErrorCode;
} GATT_Error_Response_Params_t;

#define GATT_ERROR_RESPONSE_PARAMS_SIZE sizeof(GATT_Error_Response_Params_t)

typedef struct _tagGATT_Handle_Value_Indication_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ServiceID;
    uint32_t ConnectionID;
    uint16_t AttributeOffset;
    uint16_t AttributeValueLength;
    uint8_t *AttributeValue;
} GATT_Handle_Value_Indication_Params_t;

#define GATT_HANDLE_VALUE_INDICATION_PARAMS_SIZE sizeof(GATT_Handle_Value_Indication_Params_t)

typedef struct _tagGATT_Handle_Value_Notification_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ServiceID;
    uint32_t ConnectionID;
    uint16_t AttributeOffset;
    uint16_t AttributeValueLength;
    uint8_t *AttributeValue;
} GATT_Handle_Value_Notification_Params_t;

#define GATT_HANDLE_VALUE_NOTIFICATION_PARAMS_SIZE sizeof(GATT_Handle_Value_Notification_Params_t)

typedef struct _tagGATT_Verify_Signature_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ServiceID;
    uint16_t AttributeOffset;
    uint32_t AttributeValueLength;
    uint8_t *AttributeValue;
    qapi_BLE_ATT_Authentication_Signature_t *ReceivedSignature;
    qapi_BLE_Encryption_Key_t *CSRK;
} GATT_Verify_Signature_Params_t;

#define GATT_VERIFY_SIGNATURE_PARAMS_SIZE sizeof(GATT_Verify_Signature_Params_t)

typedef struct _tagGATT_Service_Changed_Read_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data;
} GATT_Service_Changed_Read_Response_Params_t;

#define GATT_SERVICE_CHANGED_READ_RESPONSE_PARAMS_SIZE sizeof(GATT_Service_Changed_Read_Response_Params_t)

typedef struct _tagGATT_Service_Changed_CCCD_Read_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint16_t CCCD;
} GATT_Service_Changed_CCCD_Read_Response_Params_t;

#define GATT_SERVICE_CHANGED_CCCD_READ_RESPONSE_PARAMS_SIZE sizeof(GATT_Service_Changed_CCCD_Read_Response_Params_t)

typedef struct _tagGATT_Service_Changed_Indication_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data;
} GATT_Service_Changed_Indication_Params_t;

#define GATT_SERVICE_CHANGED_INDICATION_PARAMS_SIZE sizeof(GATT_Service_Changed_Indication_Params_t)

typedef struct _tagGATT_Bonded_Client_Data_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    qapi_BLE_GATT_Bonded_Client_Data_t *Bonded_Client_Data;
} GATT_Bonded_Client_Data_Request_Response_Params_t;

#define GATT_BONDED_CLIENT_DATA_REQUEST_RESPONSE_PARAMS_SIZE sizeof(GATT_Bonded_Client_Data_Request_Response_Params_t)

typedef struct _tagGATT_Query_Connection_Database_Hash_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    qapi_BLE_Encrypted_Data_t *Database_Hash;
} GATT_Query_Connection_Database_Hash_Params_t;

#define GATT_QUERY_CONNECTION_DATABASE_HASH_PARAMS_SIZE sizeof(GATT_Query_Connection_Database_Hash_Params_t)

typedef struct _tagGATT_Query_Database_Hash_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encrypted_Data_t *Database_Hash;
} GATT_Query_Database_Hash_Params_t;

#define GATT_QUERY_DATABASE_HASH_PARAMS_SIZE sizeof(GATT_Query_Database_Hash_Params_t)

typedef struct _tagGATT_Lock_Database_Params_t
{
    uint32_t BluetoothStackID;
} GATT_Lock_Database_Params_t;

#define GATT_LOCK_DATABASE_PARAMS_SIZE sizeof(GATT_Lock_Database_Params_t)

typedef struct _tagGATT_UnLock_Database_Params_t
{
    uint32_t BluetoothStackID;
} GATT_UnLock_Database_Params_t;

#define GATT_UNLOCK_DATABASE_PARAMS_SIZE sizeof(GATT_UnLock_Database_Params_t)

typedef struct _tagGATT_Exchange_MTU_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t RequestedMTU;
    unsigned long CallbackParameter;
} GATT_Exchange_MTU_Request_Params_t;

#define GATT_EXCHANGE_MTU_REQUEST_PARAMS_SIZE sizeof(GATT_Exchange_MTU_Request_Params_t)

typedef struct _tagGATT_Discover_Services_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t StartingHandle;
    uint16_t EndingHandle;
    unsigned long CallbackParameter;
} GATT_Discover_Services_Params_t;

#define GATT_DISCOVER_SERVICES_PARAMS_SIZE sizeof(GATT_Discover_Services_Params_t)

typedef struct _tagGATT_Discover_Services_By_UUID_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t StartingHandle;
    uint16_t EndingHandle;
    qapi_BLE_GATT_UUID_t *UUID;
    unsigned long CallbackParameter;
} GATT_Discover_Services_By_UUID_Params_t;

#define GATT_DISCOVER_SERVICES_BY_UUID_PARAMS_SIZE sizeof(GATT_Discover_Services_By_UUID_Params_t)

typedef struct _tagGATT_Discover_Included_Services_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t ServiceStartingHandle;
    uint16_t ServiceEndingHandle;
    unsigned long CallbackParameter;
} GATT_Discover_Included_Services_Params_t;

#define GATT_DISCOVER_INCLUDED_SERVICES_PARAMS_SIZE sizeof(GATT_Discover_Included_Services_Params_t)

typedef struct _tagGATT_Discover_Characteristics_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t ServiceStartingHandle;
    uint16_t ServiceEndingHandle;
    unsigned long CallbackParameter;
} GATT_Discover_Characteristics_Params_t;

#define GATT_DISCOVER_CHARACTERISTICS_PARAMS_SIZE sizeof(GATT_Discover_Characteristics_Params_t)

typedef struct _tagGATT_Discover_Characteristic_Descriptors_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t CharacteristicStartingHandle;
    uint16_t CharacteristicEndingHandle;
    unsigned long CallbackParameter;
} GATT_Discover_Characteristic_Descriptors_Params_t;

#define GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS_PARAMS_SIZE sizeof(GATT_Discover_Characteristic_Descriptors_Params_t)

typedef struct _tagGATT_Read_Value_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    unsigned long CallbackParameter;
} GATT_Read_Value_Request_Params_t;

#define GATT_READ_VALUE_REQUEST_PARAMS_SIZE sizeof(GATT_Read_Value_Request_Params_t)

typedef struct _tagGATT_Read_Long_Value_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    uint16_t AttributeOffset;
    unsigned long CallbackParameter;
} GATT_Read_Long_Value_Request_Params_t;

#define GATT_READ_LONG_VALUE_REQUEST_PARAMS_SIZE sizeof(GATT_Read_Long_Value_Request_Params_t)

typedef struct _tagGATT_Read_Value_By_UUID_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    qapi_BLE_GATT_UUID_t *AttributeUUID;
    uint16_t ServiceStartHandle;
    uint16_t ServiceEndHandle;
    unsigned long CallbackParameter;
} GATT_Read_Value_By_UUID_Request_Params_t;

#define GATT_READ_VALUE_BY_UUID_REQUEST_PARAMS_SIZE sizeof(GATT_Read_Value_By_UUID_Request_Params_t)

typedef struct _tagGATT_Read_Multiple_Values_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t NumberOfHandles;
    uint16_t *AttributeHandleList;
    unsigned long CallbackParameter;
} GATT_Read_Multiple_Values_Request_Params_t;

#define GATT_READ_MULTIPLE_VALUES_REQUEST_PARAMS_SIZE sizeof(GATT_Read_Multiple_Values_Request_Params_t)

typedef struct _tagGATT_Write_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    uint16_t AttributeLength;
    void *AttributeValue;
    unsigned long CallbackParameter;
} GATT_Write_Request_Params_t;

#define GATT_WRITE_REQUEST_PARAMS_SIZE sizeof(GATT_Write_Request_Params_t)

typedef struct _tagGATT_Write_Without_Response_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    uint16_t AttributeLength;
    void *AttributeValue;
} GATT_Write_Without_Response_Request_Params_t;

#define GATT_WRITE_WITHOUT_RESPONSE_REQUEST_PARAMS_SIZE sizeof(GATT_Write_Without_Response_Request_Params_t)

typedef struct _tagGATT_Signed_Write_Without_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    uint32_t SignCounter;
    uint16_t AttributeLength;
    void *AttributeValue;
    qapi_BLE_Encryption_Key_t *CSRK;
} GATT_Signed_Write_Without_Response_Params_t;

#define GATT_SIGNED_WRITE_WITHOUT_RESPONSE_PARAMS_SIZE sizeof(GATT_Signed_Write_Without_Response_Params_t)

typedef struct _tagGATT_Prepare_Write_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t AttributeHandle;
    uint16_t AttributeLength;
    uint16_t AttributeValueOffset;
    void *AttributeValue;
    unsigned long CallbackParameter;
} GATT_Prepare_Write_Request_Params_t;

#define GATT_PREPARE_WRITE_REQUEST_PARAMS_SIZE sizeof(GATT_Prepare_Write_Request_Params_t)

typedef struct _tagGATT_Execute_Write_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    boolean_t CancelWrite;
    unsigned long CallbackParameter;
} GATT_Execute_Write_Request_Params_t;

#define GATT_EXECUTE_WRITE_REQUEST_PARAMS_SIZE sizeof(GATT_Execute_Write_Request_Params_t)

typedef struct _tagGATT_Handle_Value_Confirmation_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint32_t TransactionID;
} GATT_Handle_Value_Confirmation_Params_t;

#define GATT_HANDLE_VALUE_CONFIRMATION_PARAMS_SIZE sizeof(GATT_Handle_Value_Confirmation_Params_t)

typedef struct _tagGATT_Start_Service_Discovery_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint32_t NumberOfUUID;
    qapi_BLE_GATT_UUID_t *UUIDList;
    unsigned long CallbackParameter;
} GATT_Start_Service_Discovery_Params_t;

#define GATT_START_SERVICE_DISCOVERY_PARAMS_SIZE sizeof(GATT_Start_Service_Discovery_Params_t)

typedef struct _tagGATT_Start_Service_Discovery_Handle_Range_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *DiscoveryHandleRange;
    uint32_t NumberOfUUID;
    qapi_BLE_GATT_UUID_t *UUIDList;
    unsigned long CallbackParameter;
} GATT_Start_Service_Discovery_Handle_Range_Params_t;

#define GATT_START_SERVICE_DISCOVERY_HANDLE_RANGE_PARAMS_SIZE sizeof(GATT_Start_Service_Discovery_Handle_Range_Params_t)

typedef struct _tagGATT_Stop_Service_Discovery_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
} GATT_Stop_Service_Discovery_Params_t;

#define GATT_STOP_SERVICE_DISCOVERY_PARAMS_SIZE sizeof(GATT_Stop_Service_Discovery_Params_t)

typedef struct _tagGATT_Cancel_Transaction_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
} GATT_Cancel_Transaction_Params_t;

#define GATT_CANCEL_TRANSACTION_PARAMS_SIZE sizeof(GATT_Cancel_Transaction_Params_t)

typedef struct _tagGATT_Query_Maximum_Supported_MTU_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t *MTU;
} GATT_Query_Maximum_Supported_MTU_Params_t;

#define GATT_QUERY_MAXIMUM_SUPPORTED_MTU_PARAMS_SIZE sizeof(GATT_Query_Maximum_Supported_MTU_Params_t)

typedef struct _tagGATT_Change_Maximum_Supported_MTU_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t MTU;
} GATT_Change_Maximum_Supported_MTU_Params_t;

#define GATT_CHANGE_MAXIMUM_SUPPORTED_MTU_PARAMS_SIZE sizeof(GATT_Change_Maximum_Supported_MTU_Params_t)

typedef struct _tagGATT_Query_Connection_MTU_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ConnectionID;
    uint16_t *MTU;
} GATT_Query_Connection_MTU_Params_t;

#define GATT_QUERY_CONNECTION_MTU_PARAMS_SIZE sizeof(GATT_Query_Connection_MTU_Params_t)

typedef struct _tagGATT_Query_Connection_ID_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Connection_Type_t ConnectionType;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint32_t *ConnectionID;
} GATT_Query_Connection_ID_Params_t;

#define GATT_QUERY_CONNECTION_ID_PARAMS_SIZE sizeof(GATT_Query_Connection_ID_Params_t)

typedef struct _tagGATT_Query_Transaction_Opcode_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t *Opcode;
} GATT_Query_Transaction_Opcode_Params_t;

#define GATT_QUERY_TRANSACTION_OPCODE_PARAMS_SIZE sizeof(GATT_Query_Transaction_Opcode_Params_t)

typedef struct _tagGATT_Set_Queuing_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t MaximumNumberDataPackets;
    uint32_t QueuedDataPacketsThreshold;
    boolean_t DiscardOldest;
} GATT_Set_Queuing_Parameters_Params_t;

#define GATT_SET_QUEUING_PARAMETERS_PARAMS_SIZE sizeof(GATT_Set_Queuing_Parameters_Params_t)

typedef struct _tagGATT_Get_Queuing_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *MaximumNumberDataPackets;
    uint32_t *QueuedDataPacketsThreshold;
    boolean_t *DiscardOldest;
} GATT_Get_Queuing_Parameters_Params_t;

#define GATT_GET_QUEUING_PARAMETERS_PARAMS_SIZE sizeof(GATT_Get_Queuing_Parameters_Params_t)

typedef struct _tagGATT_Query_Service_Range_Availability_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroup;
} GATT_Query_Service_Range_Availability_Params_t;

#define GATT_QUERY_SERVICE_RANGE_AVAILABILITY_PARAMS_SIZE sizeof(GATT_Query_Service_Range_Availability_Params_t)


#endif /* __GATTAPI_PARAMS_H__ */
