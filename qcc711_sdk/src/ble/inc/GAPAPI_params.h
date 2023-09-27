/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GAPAPI_PARAMS_H__
#define __GAPAPI_PARAMS_H__

#include "qapi_ble_gap.h"
typedef struct _tagGAP_Query_Local_BD_ADDR_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t *BD_ADDR;
} GAP_Query_Local_BD_ADDR_Params_t;

#define GAP_QUERY_LOCAL_BD_ADDR_PARAMS_SIZE sizeof(GAP_Query_Local_BD_ADDR_Params_t)

typedef struct _tagGAP_LE_Create_Connection_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t ScanInterval;
    uint32_t ScanWindow;
    qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy;
    qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType;
    qapi_BLE_BD_ADDR_t *RemoteDevice;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters;
    unsigned long CallbackParameter;
} GAP_LE_Create_Connection_Params_t;

#define GAP_LE_CREATE_CONNECTION_PARAMS_SIZE sizeof(GAP_LE_Create_Connection_Params_t)

typedef struct _tagGAP_LE_Cancel_Create_Connection_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Cancel_Create_Connection_Params_t;

#define GAP_LE_CANCEL_CREATE_CONNECTION_PARAMS_SIZE sizeof(GAP_LE_Cancel_Create_Connection_Params_t)

typedef struct _tagGAP_LE_Disconnect_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
} GAP_LE_Disconnect_Params_t;

#define GAP_LE_DISCONNECT_PARAMS_SIZE sizeof(GAP_LE_Disconnect_Params_t)

typedef struct _tagGAP_LE_Read_Remote_Features_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
} GAP_LE_Read_Remote_Features_Params_t;

#define GAP_LE_READ_REMOTE_FEATURES_PARAMS_SIZE sizeof(GAP_LE_Read_Remote_Features_Params_t)

typedef struct _tagGAP_LE_Perform_Scan_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Scan_Type_t ScanType;
    uint32_t ScanInterval;
    uint32_t ScanWindow;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;
    boolean_t FilterDuplicates;
    unsigned long CallbackParameter;
} GAP_LE_Perform_Scan_Params_t;

#define GAP_LE_PERFORM_SCAN_PARAMS_SIZE sizeof(GAP_LE_Perform_Scan_Params_t)

typedef struct _tagGAP_LE_Cancel_Scan_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Cancel_Scan_Params_t;

#define GAP_LE_CANCEL_SCAN_PARAMS_SIZE sizeof(GAP_LE_Cancel_Scan_Params_t)

typedef struct _tagGAP_LE_Set_Advertising_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t Length;
    qapi_BLE_Advertising_Data_t *Advertising_Data;
} GAP_LE_Set_Advertising_Data_Params_t;

#define GAP_LE_SET_ADVERTISING_DATA_PARAMS_SIZE sizeof(GAP_LE_Set_Advertising_Data_Params_t)

typedef struct _tagGAP_LE_Convert_Advertising_Data_Params_t
{
    qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data;
    qapi_BLE_Advertising_Data_t *Advertising_Data;
} GAP_LE_Convert_Advertising_Data_Params_t;

#define GAP_LE_CONVERT_ADVERTISING_DATA_PARAMS_SIZE sizeof(GAP_LE_Convert_Advertising_Data_Params_t)

typedef struct _tagGAP_LE_Parse_Advertising_Data_Params_t
{
    qapi_BLE_Advertising_Data_t *Advertising_Data;
    qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data;
} GAP_LE_Parse_Advertising_Data_Params_t;

#define GAP_LE_PARSE_ADVERTISING_DATA_PARAMS_SIZE sizeof(GAP_LE_Parse_Advertising_Data_Params_t)

typedef struct _tagGAP_LE_Set_Scan_Response_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t Length;
    qapi_BLE_Scan_Response_Data_t *Scan_Response_Data;
} GAP_LE_Set_Scan_Response_Data_Params_t;

#define GAP_LE_SET_SCAN_RESPONSE_DATA_PARAMS_SIZE sizeof(GAP_LE_Set_Scan_Response_Data_Params_t)

typedef struct _tagGAP_LE_Convert_Scan_Response_Data_Params_t
{
    qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data;
    qapi_BLE_Scan_Response_Data_t *Scan_Response_Data;
} GAP_LE_Convert_Scan_Response_Data_Params_t;

#define GAP_LE_CONVERT_SCAN_RESPONSE_DATA_PARAMS_SIZE sizeof(GAP_LE_Convert_Scan_Response_Data_Params_t)

typedef struct _tagGAP_LE_Parse_Scan_Response_Data_Params_t
{
    qapi_BLE_Scan_Response_Data_t *Scan_Response_Data;
    qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data;
} GAP_LE_Parse_Scan_Response_Data_Params_t;

#define GAP_LE_PARSE_SCAN_RESPONSE_DATA_PARAMS_SIZE sizeof(GAP_LE_Parse_Scan_Response_Data_Params_t)

typedef struct _tagGAP_LE_Advertising_Enable_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t EnableScanResponse;
    qapi_BLE_GAP_LE_Advertising_Parameters_t *GAP_LE_Advertising_Parameters;
    qapi_BLE_GAP_LE_Connectability_Parameters_t *GAP_LE_Connectability_Parameters;
    unsigned long CallbackParameter;
} GAP_LE_Advertising_Enable_Params_t;

#define GAP_LE_ADVERTISING_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Advertising_Enable_Params_t)

typedef struct _tagGAP_LE_Advertising_Disable_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Advertising_Disable_Params_t;

#define GAP_LE_ADVERTISING_DISABLE_PARAMS_SIZE sizeof(GAP_LE_Advertising_Disable_Params_t)

typedef struct _tagGAP_LE_Generate_Non_Resolvable_Address_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t *NonResolvableAddress_Result;
} GAP_LE_Generate_Non_Resolvable_Address_Params_t;

#define GAP_LE_GENERATE_NON_RESOLVABLE_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Generate_Non_Resolvable_Address_Params_t)

typedef struct _tagGAP_LE_Generate_Static_Address_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t *StaticAddress_Result;
} GAP_LE_Generate_Static_Address_Params_t;

#define GAP_LE_GENERATE_STATIC_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Generate_Static_Address_Params_t)

typedef struct _tagGAP_LE_Generate_Resolvable_Address_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *IRK;
    qapi_BLE_BD_ADDR_t *ResolvableAddress_Result;
} GAP_LE_Generate_Resolvable_Address_Params_t;

#define GAP_LE_GENERATE_RESOLVABLE_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Generate_Resolvable_Address_Params_t)

typedef struct _tagGAP_LE_Resolve_Address_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *IRK;
    qapi_BLE_BD_ADDR_t ResolvableAddress;
} GAP_LE_Resolve_Address_Params_t;

#define GAP_LE_RESOLVE_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Resolve_Address_Params_t)

typedef struct _tagGAP_LE_Set_Random_Address_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t RandomAddress;
} GAP_LE_Set_Random_Address_Params_t;

#define GAP_LE_SET_RANDOM_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Set_Random_Address_Params_t)

typedef struct _tagGAP_LE_Add_Device_To_White_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries;
    uint32_t *AddedDeviceCount;
} GAP_LE_Add_Device_To_White_List_Params_t;

#define GAP_LE_ADD_DEVICE_TO_WHITE_LIST_PARAMS_SIZE sizeof(GAP_LE_Add_Device_To_White_List_Params_t)

typedef struct _tagGAP_LE_Remove_Device_From_White_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries;
    uint32_t *RemovedDeviceCount;
} GAP_LE_Remove_Device_From_White_List_Params_t;

#define GAP_LE_REMOVE_DEVICE_FROM_WHITE_LIST_PARAMS_SIZE sizeof(GAP_LE_Remove_Device_From_White_List_Params_t)

typedef struct _tagGAP_LE_Read_White_List_Size_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *WhiteListSize;
} GAP_LE_Read_White_List_Size_Params_t;

#define GAP_LE_READ_WHITE_LIST_SIZE_PARAMS_SIZE sizeof(GAP_LE_Read_White_List_Size_Params_t)

typedef struct _tagGAP_LE_Set_Pairability_Mode_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Pairability_Mode_t PairableMode;
} GAP_LE_Set_Pairability_Mode_Params_t;

#define GAP_LE_SET_PAIRABILITY_MODE_PARAMS_SIZE sizeof(GAP_LE_Set_Pairability_Mode_Params_t)

typedef struct _tagGAP_LE_Register_Remote_Authentication_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} GAP_LE_Register_Remote_Authentication_Params_t;

#define GAP_LE_REGISTER_REMOTE_AUTHENTICATION_PARAMS_SIZE sizeof(GAP_LE_Register_Remote_Authentication_Params_t)

typedef struct _tagGAP_LE_Un_Register_Remote_Authentication_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Un_Register_Remote_Authentication_Params_t;

#define GAP_LE_UN_REGISTER_REMOTE_AUTHENTICATION_PARAMS_SIZE sizeof(GAP_LE_Un_Register_Remote_Authentication_Params_t)

typedef struct _tagGAP_LE_Pair_Remote_Device_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Pairing_Capabilities_t *Capabilities;
    unsigned long CallbackParameter;
} GAP_LE_Pair_Remote_Device_Params_t;

#define GAP_LE_PAIR_REMOTE_DEVICE_PARAMS_SIZE sizeof(GAP_LE_Pair_Remote_Device_Params_t)

typedef struct _tagGAP_LE_Extended_Pair_Remote_Device_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Capabilities;
    unsigned long CallbackParameter;
} GAP_LE_Extended_Pair_Remote_Device_Params_t;

#define GAP_LE_EXTENDED_PAIR_REMOTE_DEVICE_PARAMS_SIZE sizeof(GAP_LE_Extended_Pair_Remote_Device_Params_t)

typedef struct _tagGAP_LE_Authentication_Response_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Information;
} GAP_LE_Authentication_Response_Params_t;

#define GAP_LE_AUTHENTICATION_RESPONSE_PARAMS_SIZE sizeof(GAP_LE_Authentication_Response_Params_t)

typedef struct _tagGAP_LE_Reestablish_Security_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Security_Information_t *SecurityInformation;
    unsigned long CallbackParameter;
} GAP_LE_Reestablish_Security_Params_t;

#define GAP_LE_REESTABLISH_SECURITY_PARAMS_SIZE sizeof(GAP_LE_Reestablish_Security_Params_t)

typedef struct _tagGAP_LE_Request_Security_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type;
    boolean_t MITM;
    unsigned long CallbackParameter;
} GAP_LE_Request_Security_Params_t;

#define GAP_LE_REQUEST_SECURITY_PARAMS_SIZE sizeof(GAP_LE_Request_Security_Params_t)

typedef struct _tagGAP_LE_Extended_Request_Security_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *ExtendedCapabilities;
    unsigned long CallbackParameter;
} GAP_LE_Extended_Request_Security_Params_t;

#define GAP_LE_EXTENDED_REQUEST_SECURITY_PARAMS_SIZE sizeof(GAP_LE_Extended_Request_Security_Params_t)

typedef struct _tagGAP_LE_Set_Fixed_Passkey_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *Fixed_Display_Passkey;
} GAP_LE_Set_Fixed_Passkey_Params_t;

#define GAP_LE_SET_FIXED_PASSKEY_PARAMS_SIZE sizeof(GAP_LE_Set_Fixed_Passkey_Params_t)

typedef struct _tagGAP_LE_Update_Local_P256_Public_Key_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Update_Local_P256_Public_Key_Params_t;

#define GAP_LE_UPDATE_LOCAL_P256_PUBLIC_KEY_PARAMS_SIZE sizeof(GAP_LE_Update_Local_P256_Public_Key_Params_t)

typedef struct _tagGAP_LE_Write_Secure_Connections_Debug_Mode_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t DebugMode;
} GAP_LE_Write_Secure_Connections_Debug_Mode_Params_t;

#define GAP_LE_WRITE_SECURE_CONNECTIONS_DEBUG_MODE_PARAMS_SIZE sizeof(GAP_LE_Write_Secure_Connections_Debug_Mode_Params_t)

typedef struct _tagGAP_LE_Query_Secure_Connections_Debug_Mode_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t *DebugMode;
} GAP_LE_Query_Secure_Connections_Debug_Mode_Params_t;

#define GAP_LE_QUERY_SECURE_CONNECTIONS_DEBUG_MODE_PARAMS_SIZE sizeof(GAP_LE_Query_Secure_Connections_Debug_Mode_Params_t)

typedef struct _tagGAP_LE_Query_Encryption_Mode_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_Encryption_Mode_t *GAP_Encryption_Mode;
} GAP_LE_Query_Encryption_Mode_Params_t;

#define GAP_LE_QUERY_ENCRYPTION_MODE_PARAMS_SIZE sizeof(GAP_LE_Query_Encryption_Mode_Params_t)

typedef struct _tagGAP_LE_Query_Connection_Handle_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t *Connection_Handle;
} GAP_LE_Query_Connection_Handle_Params_t;

#define GAP_LE_QUERY_CONNECTION_HANDLE_PARAMS_SIZE sizeof(GAP_LE_Query_Connection_Handle_Params_t)

typedef struct _tagGAP_LE_Query_Connection_Addresses_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t Connection_Handle;
    qapi_BLE_GAP_LE_Address_Pair_t *Addresses;
} GAP_LE_Query_Connection_Addresses_Params_t;

#define GAP_LE_QUERY_CONNECTION_ADDRESSES_PARAMS_SIZE sizeof(GAP_LE_Query_Connection_Addresses_Params_t)

typedef struct _tagGAP_LE_Query_Connection_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Current_Connection_Parameters_t *Current_Connection_Parameters;
} GAP_LE_Query_Connection_Parameters_Params_t;

#define GAP_LE_QUERY_CONNECTION_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Query_Connection_Parameters_Params_t)

typedef struct _tagGAP_LE_Generate_Long_Term_Key_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *DHK;
    qapi_BLE_Encryption_Key_t *ER;
    qapi_BLE_Long_Term_Key_t *LTK_Result;
    uint16_t *DIV_Result;
    uint16_t *EDIV_Result;
    qapi_BLE_Random_Number_t *Rand_Result;
} GAP_LE_Generate_Long_Term_Key_Params_t;

#define GAP_LE_GENERATE_LONG_TERM_KEY_PARAMS_SIZE sizeof(GAP_LE_Generate_Long_Term_Key_Params_t)

typedef struct _tagGAP_LE_Regenerate_Long_Term_Key_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *DHK;
    qapi_BLE_Encryption_Key_t *ER;
    uint16_t EDIV;
    qapi_BLE_Random_Number_t *Rand;
    qapi_BLE_Long_Term_Key_t *LTK_Result;
} GAP_LE_Regenerate_Long_Term_Key_Params_t;

#define GAP_LE_REGENERATE_LONG_TERM_KEY_PARAMS_SIZE sizeof(GAP_LE_Regenerate_Long_Term_Key_Params_t)

typedef struct _tagGAP_LE_Diversify_Function_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Encryption_Key_t *Key;
    uint16_t DIn;
    uint16_t RIn;
    qapi_BLE_Encryption_Key_t *Result;
} GAP_LE_Diversify_Function_Params_t;

#define GAP_LE_DIVERSIFY_FUNCTION_PARAMS_SIZE sizeof(GAP_LE_Diversify_Function_Params_t)

typedef struct _tagGAP_LE_Connection_Parameter_Update_Request_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t Connection_Interval_Min;
    uint16_t Connection_Interval_Max;
    uint16_t Slave_Latency;
    uint16_t Supervision_Timeout;
} GAP_LE_Connection_Parameter_Update_Request_Params_t;

#define GAP_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_PARAMS_SIZE sizeof(GAP_LE_Connection_Parameter_Update_Request_Params_t)

typedef struct _tagGAP_LE_Connection_Parameter_Update_Response_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    boolean_t Accept;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters;
} GAP_LE_Connection_Parameter_Update_Response_Params_t;

#define GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_PARAMS_SIZE sizeof(GAP_LE_Connection_Parameter_Update_Response_Params_t)

typedef struct _tagGAP_LE_Update_Connection_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters;
} GAP_LE_Update_Connection_Parameters_Params_t;

#define GAP_LE_UPDATE_CONNECTION_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Update_Connection_Parameters_Params_t)

typedef struct _tagGAP_LE_Set_Authenticated_Payload_Timeout_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t AuthenticatedPayloadTimeout;
} GAP_LE_Set_Authenticated_Payload_Timeout_Params_t;

#define GAP_LE_SET_AUTHENTICATED_PAYLOAD_TIMEOUT_PARAMS_SIZE sizeof(GAP_LE_Set_Authenticated_Payload_Timeout_Params_t)

typedef struct _tagGAP_LE_Query_Authenticated_Payload_Timeout_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t *AuthenticatedPayloadTimeout;
} GAP_LE_Query_Authenticated_Payload_Timeout_Params_t;

#define GAP_LE_QUERY_AUTHENTICATED_PAYLOAD_TIMEOUT_PARAMS_SIZE sizeof(GAP_LE_Query_Authenticated_Payload_Timeout_Params_t)

typedef struct _tagGAP_LE_Set_Resolvable_Private_Address_Timeout_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t RPA_Timeout;
} GAP_LE_Set_Resolvable_Private_Address_Timeout_Params_t;

#define GAP_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_PARAMS_SIZE sizeof(GAP_LE_Set_Resolvable_Private_Address_Timeout_Params_t)

typedef struct _tagGAP_LE_Set_Address_Resolution_Enable_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t EnableAddressResolution;
} GAP_LE_Set_Address_Resolution_Enable_Params_t;

#define GAP_LE_SET_ADDRESS_RESOLUTION_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Set_Address_Resolution_Enable_Params_t)

typedef struct _tagGAP_LE_Add_Device_To_Resolving_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries;
    uint32_t *AddedDeviceCount;
} GAP_LE_Add_Device_To_Resolving_List_Params_t;

#define GAP_LE_ADD_DEVICE_TO_RESOLVING_LIST_PARAMS_SIZE sizeof(GAP_LE_Add_Device_To_Resolving_List_Params_t)

typedef struct _tagGAP_LE_Remove_Device_From_Resolving_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries;
    uint32_t *RemovedDeviceCount;
} GAP_LE_Remove_Device_From_Resolving_List_Params_t;

#define GAP_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_PARAMS_SIZE sizeof(GAP_LE_Remove_Device_From_Resolving_List_Params_t)

typedef struct _tagGAP_LE_Read_Resolving_List_Size_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *ResolvingListSize;
} GAP_LE_Read_Resolving_List_Size_Params_t;

#define GAP_LE_READ_RESOLVING_LIST_SIZE_PARAMS_SIZE sizeof(GAP_LE_Read_Resolving_List_Size_Params_t)

typedef struct _tagGAP_LE_Set_Resolving_List_Privacy_Mode_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Address_Type_t Peer_Identity_Address_Type;
    qapi_BLE_BD_ADDR_t Peer_Identity_Address;
    qapi_BLE_GAP_LE_Privacy_Mode_t PrivacyMode;
} GAP_LE_Set_Resolving_List_Privacy_Mode_Params_t;

#define GAP_LE_SET_RESOLVING_LIST_PRIVACY_MODE_PARAMS_SIZE sizeof(GAP_LE_Set_Resolving_List_Privacy_Mode_Params_t)

typedef struct _tagGAP_LE_Set_Data_Length_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t SuggestedTxPacketSize;
    uint16_t SuggestedTxPacketTime;
} GAP_LE_Set_Data_Length_Params_t;

#define GAP_LE_SET_DATA_LENGTH_PARAMS_SIZE sizeof(GAP_LE_Set_Data_Length_Params_t)

typedef struct _tagGAP_LE_Set_Default_Data_Length_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t SuggestedTxPacketSize;
    uint16_t SuggestedTxPacketTime;
} GAP_LE_Set_Default_Data_Length_Params_t;

#define GAP_LE_SET_DEFAULT_DATA_LENGTH_PARAMS_SIZE sizeof(GAP_LE_Set_Default_Data_Length_Params_t)

typedef struct _tagGAP_LE_Query_Default_Data_Length_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t *SuggestedTxPacketSize;
    uint16_t *SuggestedTxPacketTime;
} GAP_LE_Query_Default_Data_Length_Params_t;

#define GAP_LE_QUERY_DEFAULT_DATA_LENGTH_PARAMS_SIZE sizeof(GAP_LE_Query_Default_Data_Length_Params_t)

typedef struct _tagGAP_LE_Set_Default_Connection_PHY_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TxPHYSPreference;
    uint32_t RxPHYSPreference;
} GAP_LE_Set_Default_Connection_PHY_Params_t;

#define GAP_LE_SET_DEFAULT_CONNECTION_PHY_PARAMS_SIZE sizeof(GAP_LE_Set_Default_Connection_PHY_Params_t)

typedef struct _tagGAP_LE_Set_Connection_PHY_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint32_t TxPHYSPreference;
    uint32_t RxPHYSPreference;
} GAP_LE_Set_Connection_PHY_Params_t;

#define GAP_LE_SET_CONNECTION_PHY_PARAMS_SIZE sizeof(GAP_LE_Set_Connection_PHY_Params_t)

typedef struct _tagGAP_LE_Query_Connection_PHY_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_PHY_Type_t *TxPHY;
    qapi_BLE_GAP_LE_PHY_Type_t *RxPHY;
} GAP_LE_Query_Connection_PHY_Params_t;

#define GAP_LE_QUERY_CONNECTION_PHY_PARAMS_SIZE sizeof(GAP_LE_Query_Connection_PHY_Params_t)

typedef struct _tagGAP_LE_Query_Maximum_Advertising_Data_Length_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *MaximumAdvertisingDataLength;
} GAP_LE_Query_Maximum_Advertising_Data_Length_Params_t;

#define GAP_LE_QUERY_MAXIMUM_ADVERTISING_DATA_LENGTH_PARAMS_SIZE sizeof(GAP_LE_Query_Maximum_Advertising_Data_Length_Params_t)

typedef struct _tagGAP_LE_Query_Number_Of_Advertising_Sets_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *NumberSupportedSets;
} GAP_LE_Query_Number_Of_Advertising_Sets_Params_t;

#define GAP_LE_QUERY_NUMBER_OF_ADVERTISING_SETS_PARAMS_SIZE sizeof(GAP_LE_Query_Number_Of_Advertising_Sets_Params_t)

typedef struct _tagGAP_LE_Set_Minimum_Encryption_Key_Size_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t  EncryptionKeySize;
} GAP_LE_Set_Minimum_Encryption_Key_Size_Params_t;

#define GAP_LE_SET_MINIMUM_ENCRYPTION_KEY_SIZE_PARAMS_SIZE sizeof(GAP_LE_Set_Minimum_Encryption_Key_Size_Params_t)

typedef struct _tagGAP_LE_Set_Extended_Advertising_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *AdvertisingParameters;
    int8_t *SelectedTxPower;
} GAP_LE_Set_Extended_Advertising_Parameters_Params_t;

#define GAP_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Extended_Advertising_Parameters_Params_t)

typedef struct _tagGAP_LE_Set_Extended_Advertising_Random_Address_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    qapi_BLE_BD_ADDR_t RandomAddress;
} GAP_LE_Set_Extended_Advertising_Random_Address_Params_t;

#define GAP_LE_SET_EXTENDED_ADVERTISING_RANDOM_ADDRESS_PARAMS_SIZE sizeof(GAP_LE_Set_Extended_Advertising_Random_Address_Params_t)

typedef struct _tagGAP_LE_Set_Extended_Advertising_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Advertising_Operation_Type_t Operation;
    qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference;
    uint32_t Length;
    uint8_t *Advertising_Data;
} GAP_LE_Set_Extended_Advertising_Data_Params_t;

#define GAP_LE_SET_EXTENDED_ADVERTISING_DATA_PARAMS_SIZE sizeof(GAP_LE_Set_Extended_Advertising_Data_Params_t)

typedef struct _tagGAP_LE_Set_Extended_Scan_Response_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference;
    uint32_t Length;
    uint8_t *Scan_Response_Data;
} GAP_LE_Set_Extended_Scan_Response_Data_Params_t;

#define GAP_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_PARAMS_SIZE sizeof(GAP_LE_Set_Extended_Scan_Response_Data_Params_t)

typedef struct _tagGAP_LE_Enable_Extended_Advertising_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t Enable;
    uint8_t NumberOfSets;
    uint8_t *AdvertisingHandleList;
    uint32_t *DurationList;
    uint8_t *MaxExtendedAdvertisingEventList;
    unsigned long CallbackParameter;
} GAP_LE_Enable_Extended_Advertising_Params_t;

#define GAP_LE_ENABLE_EXTENDED_ADVERTISING_PARAMS_SIZE sizeof(GAP_LE_Enable_Extended_Advertising_Params_t)

typedef struct _tagGAP_LE_Remove_Advertising_Sets_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t NumberAdvertisingSetHandles;
    uint8_t *AdvertisingHandles;
    uint32_t *RemovedSetCount;
} GAP_LE_Remove_Advertising_Sets_Params_t;

#define GAP_LE_REMOVE_ADVERTISING_SETS_PARAMS_SIZE sizeof(GAP_LE_Remove_Advertising_Sets_Params_t)

typedef struct _tagGAP_LE_Set_Periodic_Advertising_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t *PeriodicAdvertisingParameters;
} GAP_LE_Set_Periodic_Advertising_Parameters_Params_t;

#define GAP_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Periodic_Advertising_Parameters_Params_t)

typedef struct _tagGAP_LE_Set_Periodic_Advertising_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    uint32_t Length;
    uint8_t *Advertising_Data;
} GAP_LE_Set_Periodic_Advertising_Data_Params_t;

#define GAP_LE_SET_PERIODIC_ADVERTISING_DATA_PARAMS_SIZE sizeof(GAP_LE_Set_Periodic_Advertising_Data_Params_t)

typedef struct _tagGAP_LE_Enable_Periodic_Advertising_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t Enable;
    uint8_t AdvertisingHandle;
} GAP_LE_Enable_Periodic_Advertising_Params_t;

#define GAP_LE_ENABLE_PERIODIC_ADVERTISING_PARAMS_SIZE sizeof(GAP_LE_Enable_Periodic_Advertising_Params_t)

typedef struct _tagGAP_LE_Set_Extended_Scan_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy;
    uint32_t NumberScanningPHYs;
    qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *ScanningParameterList;
} GAP_LE_Set_Extended_Scan_Parameters_Params_t;

#define GAP_LE_SET_EXTENDED_SCAN_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Extended_Scan_Parameters_Params_t)

typedef struct _tagGAP_LE_Enable_Extended_Scan_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t Enable;
    qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t FilterDuplicates;
    uint32_t Duration;
    uint32_t Period;
    unsigned long CallbackParameter;
} GAP_LE_Enable_Extended_Scan_Params_t;

#define GAP_LE_ENABLE_EXTENDED_SCAN_PARAMS_SIZE sizeof(GAP_LE_Enable_Extended_Scan_Params_t)

typedef struct _tagGAP_LE_Extended_Create_Connection_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy;
    qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType;
    qapi_BLE_BD_ADDR_t *RemoteDevice;
    qapi_BLE_GAP_LE_Address_Type_t LocalAddressType;
    uint32_t NumberOfConnectionParameters;
    qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *ConnectionParameterList;
    unsigned long CallbackParameter;
} GAP_LE_Extended_Create_Connection_Params_t;

#define GAP_LE_EXTENDED_CREATE_CONNECTION_PARAMS_SIZE sizeof(GAP_LE_Extended_Create_Connection_Params_t)

typedef struct _tagGAP_LE_Create_Periodic_Advertising_Synchronization_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Periodic_Filter_Policy_t FilterPolicy;
    boolean_t ReportingEnabled;
    uint8_t AdvertisingSID;
    qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType;
    qapi_BLE_BD_ADDR_t *RemoteDevice;
    uint16_t PeriodicSkipCount;
    uint32_t SyncTimeout;
    uint8_t CTE_Type;
    unsigned long CallbackParameter;
} GAP_LE_Create_Periodic_Advertising_Synchronization_Params_t;

#define GAP_LE_CREATE_PERIODIC_ADVERTISING_SYNCHRONIZATION_PARAMS_SIZE sizeof(GAP_LE_Create_Periodic_Advertising_Synchronization_Params_t)

typedef struct _tagGAP_LE_Cancel_Create_Periodic_Synchronization_Params_t
{
    uint32_t BluetoothStackID;
} GAP_LE_Cancel_Create_Periodic_Synchronization_Params_t;

#define GAP_LE_CANCEL_CREATE_PERIODIC_SYNCHRONIZATION_PARAMS_SIZE sizeof(GAP_LE_Cancel_Create_Periodic_Synchronization_Params_t)

typedef struct _tagGAP_LE_Terminate_Periodic_Synchronization_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t SyncHandle;
} GAP_LE_Terminate_Periodic_Synchronization_Params_t;

#define GAP_LE_TERMINATE_PERIODIC_SYNCHRONIZATION_PARAMS_SIZE sizeof(GAP_LE_Terminate_Periodic_Synchronization_Params_t)

typedef struct _tagGAP_LE_Add_Device_To_Periodic_Advertising_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries;
    uint32_t *AddedDeviceCount;
} GAP_LE_Add_Device_To_Periodic_Advertising_List_Params_t;

#define GAP_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE sizeof(GAP_LE_Add_Device_To_Periodic_Advertising_List_Params_t)

typedef struct _tagGAP_LE_Remove_Device_From_Periodic_Advertising_List_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t DeviceCount;
    qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries;
    uint32_t *RemovedDeviceCount;
} GAP_LE_Remove_Device_From_Periodic_Advertising_List_Params_t;

#define GAP_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE sizeof(GAP_LE_Remove_Device_From_Periodic_Advertising_List_Params_t)

typedef struct _tagGAP_LE_Read_Periodic_Advertising_List_Size_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *PeriodicAdvertisingListSize;
} GAP_LE_Read_Periodic_Advertising_List_Size_Params_t;

#define GAP_LE_READ_PERIODIC_ADVERTISING_LIST_SIZE_PARAMS_SIZE sizeof(GAP_LE_Read_Periodic_Advertising_List_Size_Params_t)

typedef struct _tagGAP_LE_Query_Local_Secure_Connections_OOB_Data_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_Secure_Connections_Randomizer_t *Randomizer;
    qapi_BLE_Secure_Connections_Confirmation_t *Confirmation;
} GAP_LE_Query_Local_Secure_Connections_OOB_Data_Params_t;

#define GAP_LE_QUERY_LOCAL_SECURE_CONNECTIONS_OOB_DATA_PARAMS_SIZE sizeof(GAP_LE_Query_Local_Secure_Connections_OOB_Data_Params_t)

typedef struct _tagGAP_LE_Set_Connectionless_CTE_Transmit_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    uint8_t CTE_Length;
    qapi_BLE_GAP_LE_CTE_Type_t CTE_Type;
    uint8_t CTE_Count;
    uint8_t LengthOfSwitchingPattern;
    uint8_t *Antenna_IDs;
} GAP_LE_Set_Connectionless_CTE_Transmit_Parameters_Params_t;

#define GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Connectionless_CTE_Transmit_Parameters_Params_t)

typedef struct _tagGAP_LE_Set_Connectionless_CTE_Transmit_Enable_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t AdvertisingHandle;
    boolean_t CTE_Enable;
} GAP_LE_Set_Connectionless_CTE_Transmit_Enable_Params_t;

#define GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Set_Connectionless_CTE_Transmit_Enable_Params_t)

typedef struct _tagGAP_LE_Set_Connectionless_IQ_Sampling_Enable_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t SyncHandle;
    boolean_t SamplingEnable;
    qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType;
    uint8_t Max_Sampled_CTEs;
    uint8_t LengthOfSwitchingPattern;
    uint8_t *Antenna_IDs;
} GAP_LE_Set_Connectionless_IQ_Sampling_Enable_Params_t;

#define GAP_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Set_Connectionless_IQ_Sampling_Enable_Params_t)

typedef struct _tagGAP_LE_Set_Connection_CTE_Receive_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint8_t SamplingEnable;
    qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType;
    uint8_t LengthOfSwitchingPattern;
    uint8_t *Antenna_IDs;
} GAP_LE_Set_Connection_CTE_Receive_Parameters_Params_t;

#define GAP_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Connection_CTE_Receive_Parameters_Params_t)

typedef struct _tagGAP_LE_Connection_CTE_Request_Enable_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    boolean_t Enable;
    uint16_t CTE_Request_Interval;
    uint8_t Requested_CTE_Length;
    qapi_BLE_GAP_LE_CTE_Type_t Requested_CTE_Type;
} GAP_LE_Connection_CTE_Request_Enable_Params_t;

#define GAP_LE_CONNECTION_CTE_REQUEST_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Connection_CTE_Request_Enable_Params_t)

typedef struct _tagGAP_LE_Set_Connection_CTE_Transmit_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint8_t CTE_Types;
    uint8_t LengthOfSwitchingPattern;
    uint8_t *Antenna_IDs;
} GAP_LE_Set_Connection_CTE_Transmit_Parameters_Params_t;

#define GAP_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Connection_CTE_Transmit_Parameters_Params_t)

typedef struct _tagGAP_LE_Connection_CTE_Response_Enable_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    boolean_t Enable;
} GAP_LE_Connection_CTE_Response_Enable_Params_t;

#define GAP_LE_CONNECTION_CTE_RESPONSE_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Connection_CTE_Response_Enable_Params_t)

typedef struct _tagGAP_LE_Query_Antenna_Information_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Antenna_Information_t *AntennaInfo;
} GAP_LE_Query_Antenna_Information_Params_t;

#define GAP_LE_QUERY_ANTENNA_INFORMATION_PARAMS_SIZE sizeof(GAP_LE_Query_Antenna_Information_Params_t)

typedef struct _tagGAP_LE_Set_Periodic_Advertising_Receive_Enable_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t SyncHandle;
    boolean_t Enable;
} GAP_LE_Set_Periodic_Advertising_Receive_Enable_Params_t;

#define GAP_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE_PARAMS_SIZE sizeof(GAP_LE_Set_Periodic_Advertising_Receive_Enable_Params_t)

typedef struct _tagGAP_LE_Periodic_Advertising_Sync_Transfer_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t ServiceData;
    uint16_t SyncHandle;
} GAP_LE_Periodic_Advertising_Sync_Transfer_Params_t;

#define GAP_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMS_SIZE sizeof(GAP_LE_Periodic_Advertising_Sync_Transfer_Params_t)

typedef struct _tagGAP_LE_Periodic_Advertising_Set_Info_Transfer_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t ServiceData;
    uint8_t AdvertisingHandle;
} GAP_LE_Periodic_Advertising_Set_Info_Transfer_Params_t;

#define GAP_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER_PARAMS_SIZE sizeof(GAP_LE_Periodic_Advertising_Set_Info_Transfer_Params_t)

typedef struct _tagGAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode;
    uint16_t Skip;
    uint32_t SyncTimeout;
    uint8_t CTE_Type;
    unsigned long CallbackParameter;
} GAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters_Params_t;

#define GAP_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters_Params_t)

typedef struct _tagGAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode;
    uint16_t Skip;
    uint32_t SyncTimeout;
    uint8_t CTE_Type;
    unsigned long CallbackParameter;
} GAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters_Params_t;

#define GAP_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_PARAMS_SIZE sizeof(GAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters_Params_t)

typedef struct _tagGAP_LE_Initialize_AES_CMAC_Operation_Params_t
{
    qapi_BLE_Encryption_Key_t *Key;
    uint32_t MessageLength;
} GAP_LE_Initialize_AES_CMAC_Operation_Params_t;

#define GAP_LE_INITIALIZE_AES_CMAC_OPERATION_PARAMS_SIZE sizeof(GAP_LE_Initialize_AES_CMAC_Operation_Params_t)

typedef struct _tagGAP_LE_Cleanup_AES_CMAC_Operation_Params_t
{
    void *GapleAesCmacContext;
} GAP_LE_Cleanup_AES_CMAC_Operation_Params_t;

#define GAP_LE_CLEANUP_AES_CMAC_OPERATION_PARAMS_SIZE sizeof(GAP_LE_Cleanup_AES_CMAC_Operation_Params_t)

typedef struct _tagGAP_LE_Perform_AES_CMAC_Operation_Params_t
{
    uint32_t BluetoothStackID;
    void *GapleAesCmacContext;
    uint32_t BlockLength;
    uint8_t *BlockData;
    qapi_BLE_Encryption_Key_t *MACResult;
} GAP_LE_Perform_AES_CMAC_Operation_Params_t;

#define GAP_LE_PERFORM_AES_CMAC_OPERATION_PARAMS_SIZE sizeof(GAP_LE_Perform_AES_CMAC_Operation_Params_t)


#endif /* __GAPAPI_PARAMS_H__ */
