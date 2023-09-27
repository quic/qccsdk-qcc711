/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_gap.h"
#include "GAPAPI_params.h"
#include "GAPAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_Query_Local_BD_ADDR(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *BD_ADDR)
{
    GAP_Query_Local_BD_ADDR_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_QUERY_LOCAL_BD_ADDR_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_QUERY_LOCAL_BD_ADDR_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(BD_ADDR != NULL)
        {
            Params->BD_ADDR = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->BD_ADDR = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_QUERY_LOCAL_BD_ADDR, MessageSize, (uint8_t *)Params);

        if(BD_ADDR != NULL)
            memscpy(BD_ADDR, sizeof(qapi_BLE_BD_ADDR_t), Params->BD_ADDR, sizeof(qapi_BLE_BD_ADDR_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Create_Connection(uint32_t BluetoothStackID, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Create_Connection_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CREATE_CONNECTION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t)) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_CREATE_CONNECTION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->ScanInterval = ScanInterval;
        Params->ScanWindow = ScanWindow;
        Params->InitatorFilterPolicy = InitatorFilterPolicy;
        Params->RemoteAddressType = RemoteAddressType;
        if(RemoteDevice != NULL)
        {
            Params->RemoteDevice = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
            memscpy(Params->RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t), RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->RemoteDevice = NULL;
        }
        Params->LocalAddressType = LocalAddressType;
        if(ConnectionParameters != NULL)
        {
            Params->ConnectionParameters = (qapi_BLE_GAP_LE_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
            memscpy(Params->ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t), ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
        }
        else
        {
            Params->ConnectionParameters = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CREATE_CONNECTION, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Create_Connection(uint32_t BluetoothStackID)
{
    GAP_LE_Cancel_Create_Connection_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CANCEL_CREATE_CONNECTION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CANCEL_CREATE_CONNECTION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Disconnect(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR)
{
    GAP_LE_Disconnect_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_DISCONNECT_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_DISCONNECT, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Remote_Features(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR)
{
    GAP_LE_Read_Remote_Features_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_READ_REMOTE_FEATURES_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_READ_REMOTE_FEATURES, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Perform_Scan(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Scan_Type_t ScanType, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, boolean_t FilterDuplicates, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Perform_Scan_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_PERFORM_SCAN_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->ScanType = ScanType;
        Params->ScanInterval = ScanInterval;
        Params->ScanWindow = ScanWindow;
        Params->LocalAddressType = LocalAddressType;
        Params->FilterPolicy = FilterPolicy;
        Params->FilterDuplicates = *((boolean_t *)&FilterDuplicates);
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_PERFORM_SCAN, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Scan(uint32_t BluetoothStackID)
{
    GAP_LE_Cancel_Scan_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CANCEL_SCAN_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CANCEL_SCAN, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Advertising_Data(uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Advertising_Data_t *Advertising_Data)
{
    GAP_LE_Set_Advertising_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_ADVERTISING_DATA_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Advertising_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_ADVERTISING_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Length = Length;
        if(Advertising_Data != NULL)
        {
            Params->Advertising_Data = (qapi_BLE_Advertising_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Advertising_Data_t));
            memscpy(Params->Advertising_Data, sizeof(qapi_BLE_Advertising_Data_t), Advertising_Data, sizeof(qapi_BLE_Advertising_Data_t));
        }
        else
        {
            Params->Advertising_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_ADVERTISING_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data)
{
    GAP_LE_Set_Scan_Response_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_SCAN_RESPONSE_DATA_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Scan_Response_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_SCAN_RESPONSE_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Length = Length;
        if(Scan_Response_Data != NULL)
        {
            Params->Scan_Response_Data = (qapi_BLE_Scan_Response_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Scan_Response_Data_t));
            memscpy(Params->Scan_Response_Data, sizeof(qapi_BLE_Scan_Response_Data_t), Scan_Response_Data, sizeof(qapi_BLE_Scan_Response_Data_t));
        }
        else
        {
            Params->Scan_Response_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_SCAN_RESPONSE_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Advertising_Enable(uint32_t BluetoothStackID, boolean_t EnableScanResponse, qapi_BLE_GAP_LE_Advertising_Parameters_t *GAP_LE_Advertising_Parameters, qapi_BLE_GAP_LE_Connectability_Parameters_t *GAP_LE_Connectability_Parameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Advertising_Enable_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ADVERTISING_ENABLE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t)) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_ADVERTISING_ENABLE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->EnableScanResponse = *((boolean_t *)&EnableScanResponse);
        if(GAP_LE_Advertising_Parameters != NULL)
        {
            Params->GAP_LE_Advertising_Parameters = (qapi_BLE_GAP_LE_Advertising_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t));
            memscpy(Params->GAP_LE_Advertising_Parameters, sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t), GAP_LE_Advertising_Parameters, sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t));
        }
        else
        {
            Params->GAP_LE_Advertising_Parameters = NULL;
        }
        if(GAP_LE_Connectability_Parameters != NULL)
        {
            Params->GAP_LE_Connectability_Parameters = (qapi_BLE_GAP_LE_Connectability_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t));
            memscpy(Params->GAP_LE_Connectability_Parameters, sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t), GAP_LE_Connectability_Parameters, sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t));
        }
        else
        {
            Params->GAP_LE_Connectability_Parameters = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ADVERTISING_ENABLE, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Advertising_Disable(uint32_t BluetoothStackID)
{
    GAP_LE_Advertising_Disable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ADVERTISING_DISABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ADVERTISING_DISABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *NonResolvableAddress_Result)
{
    GAP_LE_Generate_Non_Resolvable_Address_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_GENERATE_NON_RESOLVABLE_ADDRESS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_GENERATE_NON_RESOLVABLE_ADDRESS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(NonResolvableAddress_Result != NULL)
        {
            Params->NonResolvableAddress_Result = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->NonResolvableAddress_Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_GENERATE_NON_RESOLVABLE_ADDRESS, MessageSize, (uint8_t *)Params);

        if(NonResolvableAddress_Result != NULL)
            memscpy(NonResolvableAddress_Result, sizeof(qapi_BLE_BD_ADDR_t), Params->NonResolvableAddress_Result, sizeof(qapi_BLE_BD_ADDR_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Static_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *StaticAddress_Result)
{
    GAP_LE_Generate_Static_Address_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_GENERATE_STATIC_ADDRESS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_GENERATE_STATIC_ADDRESS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(StaticAddress_Result != NULL)
        {
            Params->StaticAddress_Result = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->StaticAddress_Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_GENERATE_STATIC_ADDRESS, MessageSize, (uint8_t *)Params);

        if(StaticAddress_Result != NULL)
            memscpy(StaticAddress_Result, sizeof(qapi_BLE_BD_ADDR_t), Params->StaticAddress_Result, sizeof(qapi_BLE_BD_ADDR_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Resolvable_Address(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t *ResolvableAddress_Result)
{
    GAP_LE_Generate_Resolvable_Address_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_GENERATE_RESOLVABLE_ADDRESS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_GENERATE_RESOLVABLE_ADDRESS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(IRK != NULL)
        {
            Params->IRK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->IRK, sizeof(qapi_BLE_Encryption_Key_t), IRK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->IRK = NULL;
        }
        if(ResolvableAddress_Result != NULL)
        {
            Params->ResolvableAddress_Result = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->ResolvableAddress_Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_GENERATE_RESOLVABLE_ADDRESS, MessageSize, (uint8_t *)Params);

        if(ResolvableAddress_Result != NULL)
            memscpy(ResolvableAddress_Result, sizeof(qapi_BLE_BD_ADDR_t), Params->ResolvableAddress_Result, sizeof(qapi_BLE_BD_ADDR_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Resolve_Address(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t ResolvableAddress)
{
    GAP_LE_Resolve_Address_Params_t *Params;
    boolean_t ret_val = false;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_RESOLVE_ADDRESS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_RESOLVE_ADDRESS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(IRK != NULL)
        {
            Params->IRK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->IRK, sizeof(qapi_BLE_Encryption_Key_t), IRK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->IRK = NULL;
        }
        Params->ResolvableAddress = *((qapi_BLE_BD_ADDR_t *)&ResolvableAddress);

        ret_val = (boolean_t)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_RESOLVE_ADDRESS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Random_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t RandomAddress)
{
    GAP_LE_Set_Random_Address_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_RANDOM_ADDRESS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->RandomAddress = *((qapi_BLE_BD_ADDR_t *)&RandomAddress);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_RANDOM_ADDRESS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_White_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *AddedDeviceCount)
{
    GAP_LE_Add_Device_To_White_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ADD_DEVICE_TO_WHITE_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_ADD_DEVICE_TO_WHITE_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(WhiteListEntries != NULL)
        {
            Params->WhiteListEntries = (qapi_BLE_GAP_LE_White_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount));
            memscpy(Params->WhiteListEntries, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount), WhiteListEntries, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->WhiteListEntries = NULL;
        }
        if(AddedDeviceCount != NULL)
        {
            Params->AddedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->AddedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ADD_DEVICE_TO_WHITE_LIST, MessageSize, (uint8_t *)Params);

        if(AddedDeviceCount != NULL)
            memscpy(AddedDeviceCount, sizeof(uint32_t), Params->AddedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_White_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *RemovedDeviceCount)
{
    GAP_LE_Remove_Device_From_White_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_WHITE_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_WHITE_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(WhiteListEntries != NULL)
        {
            Params->WhiteListEntries = (qapi_BLE_GAP_LE_White_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount));
            memscpy(Params->WhiteListEntries, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount), WhiteListEntries, (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->WhiteListEntries = NULL;
        }
        if(RemovedDeviceCount != NULL)
        {
            Params->RemovedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->RemovedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REMOVE_DEVICE_FROM_WHITE_LIST, MessageSize, (uint8_t *)Params);

        if(RemovedDeviceCount != NULL)
            memscpy(RemovedDeviceCount, sizeof(uint32_t), Params->RemovedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_White_List_Size(uint32_t BluetoothStackID, uint32_t *WhiteListSize)
{
    GAP_LE_Read_White_List_Size_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_READ_WHITE_LIST_SIZE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_READ_WHITE_LIST_SIZE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(WhiteListSize != NULL)
        {
            Params->WhiteListSize = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->WhiteListSize = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_READ_WHITE_LIST_SIZE, MessageSize, (uint8_t *)Params);

        if(WhiteListSize != NULL)
            memscpy(WhiteListSize, sizeof(uint32_t), Params->WhiteListSize, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Pairability_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Pairability_Mode_t PairableMode)
{
    GAP_LE_Set_Pairability_Mode_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_PAIRABILITY_MODE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->PairableMode = PairableMode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_PAIRABILITY_MODE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Register_Remote_Authentication(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Register_Remote_Authentication_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REGISTER_REMOTE_AUTHENTICATION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 1;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REGISTER_REMOTE_AUTHENTICATION, MessageSize, (uint8_t *)Params);

            if(GAP_LE_Event_Callback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(uint32_t BluetoothStackID)
{
    GAP_LE_Un_Register_Remote_Authentication_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_UN_REGISTER_REMOTE_AUTHENTICATION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_UN_REGISTER_REMOTE_AUTHENTICATION, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_GAPAPI, CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T, 1);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Pair_Remote_Device(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Pairing_Capabilities_t *Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Pair_Remote_Device_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_PAIR_REMOTE_DEVICE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_PAIR_REMOTE_DEVICE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(Capabilities != NULL)
        {
            Params->Capabilities = (qapi_BLE_GAP_LE_Pairing_Capabilities_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t));
            memscpy(Params->Capabilities, sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t), Capabilities, sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t));
        }
        else
        {
            Params->Capabilities = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_PAIR_REMOTE_DEVICE, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Extended_Pair_Remote_Device_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_EXTENDED_PAIR_REMOTE_DEVICE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_EXTENDED_PAIR_REMOTE_DEVICE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(Extended_Capabilities != NULL)
        {
            Params->Extended_Capabilities = (qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));
            memscpy(Params->Extended_Capabilities, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t), Extended_Capabilities, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));
        }
        else
        {
            Params->Extended_Capabilities = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_EXTENDED_PAIR_REMOTE_DEVICE, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Authentication_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Information)
{
    GAP_LE_Authentication_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_AUTHENTICATION_RESPONSE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_AUTHENTICATION_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(GAP_LE_Authentication_Information != NULL)
        {
            Params->GAP_LE_Authentication_Information = (qapi_BLE_GAP_LE_Authentication_Response_Information_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t));
            memscpy(Params->GAP_LE_Authentication_Information, sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t), GAP_LE_Authentication_Information, sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t));
        }
        else
        {
            Params->GAP_LE_Authentication_Information = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_AUTHENTICATION_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Reestablish_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Security_Information_t *SecurityInformation, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Reestablish_Security_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REESTABLISH_SECURITY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Security_Information_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REESTABLISH_SECURITY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(SecurityInformation != NULL)
        {
            Params->SecurityInformation = (qapi_BLE_GAP_LE_Security_Information_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Security_Information_t));
            memscpy(Params->SecurityInformation, sizeof(qapi_BLE_GAP_LE_Security_Information_t), SecurityInformation, sizeof(qapi_BLE_GAP_LE_Security_Information_t));
        }
        else
        {
            Params->SecurityInformation = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REESTABLISH_SECURITY, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Request_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type, boolean_t MITM, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Request_Security_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REQUEST_SECURITY_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Bonding_Type = Bonding_Type;
        Params->MITM = *((boolean_t *)&MITM);
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REQUEST_SECURITY, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Request_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *ExtendedCapabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Extended_Request_Security_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_EXTENDED_REQUEST_SECURITY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_EXTENDED_REQUEST_SECURITY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(ExtendedCapabilities != NULL)
        {
            Params->ExtendedCapabilities = (qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));
            memscpy(Params->ExtendedCapabilities, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t), ExtendedCapabilities, sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t));
        }
        else
        {
            Params->ExtendedCapabilities = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_EXTENDED_REQUEST_SECURITY, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Fixed_Passkey(uint32_t BluetoothStackID, uint32_t *Fixed_Display_Passkey)
{
    GAP_LE_Set_Fixed_Passkey_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_FIXED_PASSKEY_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_FIXED_PASSKEY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(Fixed_Display_Passkey != NULL)
        {
            Params->Fixed_Display_Passkey = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
            memscpy(Params->Fixed_Display_Passkey, sizeof(uint32_t), Fixed_Display_Passkey, sizeof(uint32_t));
        }
        else
        {
            Params->Fixed_Display_Passkey = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_FIXED_PASSKEY, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(uint32_t BluetoothStackID)
{
    GAP_LE_Update_Local_P256_Public_Key_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_UPDATE_LOCAL_P256_PUBLIC_KEY_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_UPDATE_LOCAL_P256_PUBLIC_KEY, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Write_Secure_Connections_Debug_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t DebugMode)
{
    GAP_LE_Write_Secure_Connections_Debug_Mode_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_WRITE_SECURE_CONNECTIONS_DEBUG_MODE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->DebugMode = DebugMode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_WRITE_SECURE_CONNECTIONS_DEBUG_MODE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Secure_Connections_Debug_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t *DebugMode)
{
    GAP_LE_Query_Secure_Connections_Debug_Mode_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_SECURE_CONNECTIONS_DEBUG_MODE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_SECURE_CONNECTIONS_DEBUG_MODE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(DebugMode != NULL)
        {
            Params->DebugMode = (qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t));
        }
        else
        {
            Params->DebugMode = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_SECURE_CONNECTIONS_DEBUG_MODE, MessageSize, (uint8_t *)Params);

        if(DebugMode != NULL)
            memscpy(DebugMode, sizeof(qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t), Params->DebugMode, sizeof(qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Encryption_Mode(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_Encryption_Mode_t *GAP_Encryption_Mode)
{
    GAP_LE_Query_Encryption_Mode_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_ENCRYPTION_MODE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_Encryption_Mode_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_ENCRYPTION_MODE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(GAP_Encryption_Mode != NULL)
        {
            Params->GAP_Encryption_Mode = (qapi_BLE_GAP_Encryption_Mode_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Encryption_Mode_t));
        }
        else
        {
            Params->GAP_Encryption_Mode = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_ENCRYPTION_MODE, MessageSize, (uint8_t *)Params);

        if(GAP_Encryption_Mode != NULL)
            memscpy(GAP_Encryption_Mode, sizeof(qapi_BLE_GAP_Encryption_Mode_t), Params->GAP_Encryption_Mode, sizeof(qapi_BLE_GAP_Encryption_Mode_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Handle(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *Connection_Handle)
{
    GAP_LE_Query_Connection_Handle_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_CONNECTION_HANDLE_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_CONNECTION_HANDLE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(Connection_Handle != NULL)
        {
            Params->Connection_Handle = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->Connection_Handle = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_CONNECTION_HANDLE, MessageSize, (uint8_t *)Params);

        if(Connection_Handle != NULL)
            memscpy(Connection_Handle, sizeof(uint16_t), Params->Connection_Handle, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Addresses(uint32_t BluetoothStackID, uint16_t Connection_Handle, qapi_BLE_GAP_LE_Address_Pair_t *Addresses)
{
    GAP_LE_Query_Connection_Addresses_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_CONNECTION_ADDRESSES_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Address_Pair_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_CONNECTION_ADDRESSES_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Connection_Handle = Connection_Handle;
        if(Addresses != NULL)
        {
            Params->Addresses = (qapi_BLE_GAP_LE_Address_Pair_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Address_Pair_t));
        }
        else
        {
            Params->Addresses = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_CONNECTION_ADDRESSES, MessageSize, (uint8_t *)Params);

        if(Addresses != NULL)
            memscpy(Addresses, sizeof(qapi_BLE_GAP_LE_Address_Pair_t), Params->Addresses, sizeof(qapi_BLE_GAP_LE_Address_Pair_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Current_Connection_Parameters_t *Current_Connection_Parameters)
{
    GAP_LE_Query_Connection_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_CONNECTION_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_CONNECTION_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(Current_Connection_Parameters != NULL)
        {
            Params->Current_Connection_Parameters = (qapi_BLE_GAP_LE_Current_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t));
        }
        else
        {
            Params->Current_Connection_Parameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_CONNECTION_PARAMETERS, MessageSize, (uint8_t *)Params);

        if(Current_Connection_Parameters != NULL)
            memscpy(Current_Connection_Parameters, sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t), Params->Current_Connection_Parameters, sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Long_Term_Key(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, qapi_BLE_Long_Term_Key_t *LTK_Result, uint16_t *DIV_Result, uint16_t *EDIV_Result, qapi_BLE_Random_Number_t *Rand_Result)
{
    GAP_LE_Generate_Long_Term_Key_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_GENERATE_LONG_TERM_KEY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_Long_Term_Key_t)) + ALIGN32(sizeof(uint16_t)) + ALIGN32(sizeof(uint16_t)) + ALIGN32(sizeof(qapi_BLE_Random_Number_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_GENERATE_LONG_TERM_KEY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(DHK != NULL)
        {
            Params->DHK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->DHK, sizeof(qapi_BLE_Encryption_Key_t), DHK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->DHK = NULL;
        }
        if(ER != NULL)
        {
            Params->ER = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->ER, sizeof(qapi_BLE_Encryption_Key_t), ER, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->ER = NULL;
        }
        if(LTK_Result != NULL)
        {
            Params->LTK_Result = (qapi_BLE_Long_Term_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Long_Term_Key_t));
        }
        else
        {
            Params->LTK_Result = NULL;
        }
        if(DIV_Result != NULL)
        {
            Params->DIV_Result = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->DIV_Result = NULL;
        }
        if(EDIV_Result != NULL)
        {
            Params->EDIV_Result = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->EDIV_Result = NULL;
        }
        if(Rand_Result != NULL)
        {
            Params->Rand_Result = (qapi_BLE_Random_Number_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Random_Number_t));
        }
        else
        {
            Params->Rand_Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_GENERATE_LONG_TERM_KEY, MessageSize, (uint8_t *)Params);

        if(LTK_Result != NULL)
            memscpy(LTK_Result, sizeof(qapi_BLE_Long_Term_Key_t), Params->LTK_Result, sizeof(qapi_BLE_Long_Term_Key_t));

        if(DIV_Result != NULL)
            memscpy(DIV_Result, sizeof(uint16_t), Params->DIV_Result, sizeof(uint16_t));

        if(EDIV_Result != NULL)
            memscpy(EDIV_Result, sizeof(uint16_t), Params->EDIV_Result, sizeof(uint16_t));

        if(Rand_Result != NULL)
            memscpy(Rand_Result, sizeof(qapi_BLE_Random_Number_t), Params->Rand_Result, sizeof(qapi_BLE_Random_Number_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, uint16_t EDIV, qapi_BLE_Random_Number_t *Rand, qapi_BLE_Long_Term_Key_t *LTK_Result)
{
    GAP_LE_Regenerate_Long_Term_Key_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REGENERATE_LONG_TERM_KEY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_Random_Number_t)) + ALIGN32(sizeof(qapi_BLE_Long_Term_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REGENERATE_LONG_TERM_KEY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(DHK != NULL)
        {
            Params->DHK = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->DHK, sizeof(qapi_BLE_Encryption_Key_t), DHK, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->DHK = NULL;
        }
        if(ER != NULL)
        {
            Params->ER = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->ER, sizeof(qapi_BLE_Encryption_Key_t), ER, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->ER = NULL;
        }
        Params->EDIV = EDIV;
        if(Rand != NULL)
        {
            Params->Rand = (qapi_BLE_Random_Number_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Random_Number_t));
            memscpy(Params->Rand, sizeof(qapi_BLE_Random_Number_t), Rand, sizeof(qapi_BLE_Random_Number_t));
        }
        else
        {
            Params->Rand = NULL;
        }
        if(LTK_Result != NULL)
        {
            Params->LTK_Result = (qapi_BLE_Long_Term_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Long_Term_Key_t));
        }
        else
        {
            Params->LTK_Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REGENERATE_LONG_TERM_KEY, MessageSize, (uint8_t *)Params);

        if(LTK_Result != NULL)
            memscpy(LTK_Result, sizeof(qapi_BLE_Long_Term_Key_t), Params->LTK_Result, sizeof(qapi_BLE_Long_Term_Key_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Diversify_Function(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *Key, uint16_t DIn, uint16_t RIn, qapi_BLE_Encryption_Key_t *Result)
{
    GAP_LE_Diversify_Function_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_DIVERSIFY_FUNCTION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t)) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_DIVERSIFY_FUNCTION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(Key != NULL)
        {
            Params->Key = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->Key, sizeof(qapi_BLE_Encryption_Key_t), Key, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->Key = NULL;
        }
        Params->DIn = DIn;
        Params->RIn = RIn;
        if(Result != NULL)
        {
            Params->Result = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->Result = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_DIVERSIFY_FUNCTION, MessageSize, (uint8_t *)Params);

        if(Result != NULL)
            memscpy(Result, sizeof(qapi_BLE_Encryption_Key_t), Params->Result, sizeof(qapi_BLE_Encryption_Key_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Connection_Interval_Min, uint16_t Connection_Interval_Max, uint16_t Slave_Latency, uint16_t Supervision_Timeout)
{
    GAP_LE_Connection_Parameter_Update_Request_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Connection_Interval_Min = Connection_Interval_Min;
        Params->Connection_Interval_Max = Connection_Interval_Max;
        Params->Slave_Latency = Slave_Latency;
        Params->Supervision_Timeout = Supervision_Timeout;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CONNECTION_PARAMETER_UPDATE_REQUEST, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Accept, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters)
{
    GAP_LE_Connection_Parameter_Update_Response_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Accept = *((boolean_t *)&Accept);
        if(ConnectionParameters != NULL)
        {
            Params->ConnectionParameters = (qapi_BLE_GAP_LE_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
            memscpy(Params->ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t), ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
        }
        else
        {
            Params->ConnectionParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Update_Connection_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters)
{
    GAP_LE_Update_Connection_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_UPDATE_CONNECTION_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_UPDATE_CONNECTION_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(ConnectionParameters != NULL)
        {
            Params->ConnectionParameters = (qapi_BLE_GAP_LE_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
            memscpy(Params->ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t), ConnectionParameters, sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t));
        }
        else
        {
            Params->ConnectionParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_UPDATE_CONNECTION_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t AuthenticatedPayloadTimeout)
{
    GAP_LE_Set_Authenticated_Payload_Timeout_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_AUTHENTICATED_PAYLOAD_TIMEOUT_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->AuthenticatedPayloadTimeout = AuthenticatedPayloadTimeout;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_AUTHENTICATED_PAYLOAD_TIMEOUT, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *AuthenticatedPayloadTimeout)
{
    GAP_LE_Query_Authenticated_Payload_Timeout_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_AUTHENTICATED_PAYLOAD_TIMEOUT_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_AUTHENTICATED_PAYLOAD_TIMEOUT_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(AuthenticatedPayloadTimeout != NULL)
        {
            Params->AuthenticatedPayloadTimeout = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->AuthenticatedPayloadTimeout = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_AUTHENTICATED_PAYLOAD_TIMEOUT, MessageSize, (uint8_t *)Params);

        if(AuthenticatedPayloadTimeout != NULL)
            memscpy(AuthenticatedPayloadTimeout, sizeof(uint16_t), Params->AuthenticatedPayloadTimeout, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(uint32_t BluetoothStackID, uint32_t RPA_Timeout)
{
    GAP_LE_Set_Resolvable_Private_Address_Timeout_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->RPA_Timeout = RPA_Timeout;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(uint32_t BluetoothStackID, boolean_t EnableAddressResolution)
{
    GAP_LE_Set_Address_Resolution_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_ADDRESS_RESOLUTION_ENABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->EnableAddressResolution = *((boolean_t *)&EnableAddressResolution);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_ADDRESS_RESOLUTION_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *AddedDeviceCount)
{
    GAP_LE_Add_Device_To_Resolving_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ADD_DEVICE_TO_RESOLVING_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_ADD_DEVICE_TO_RESOLVING_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(ResolvingListEntries != NULL)
        {
            Params->ResolvingListEntries = (qapi_BLE_GAP_LE_Resolving_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount));
            memscpy(Params->ResolvingListEntries, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount), ResolvingListEntries, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->ResolvingListEntries = NULL;
        }
        if(AddedDeviceCount != NULL)
        {
            Params->AddedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->AddedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ADD_DEVICE_TO_RESOLVING_LIST, MessageSize, (uint8_t *)Params);

        if(AddedDeviceCount != NULL)
            memscpy(AddedDeviceCount, sizeof(uint32_t), Params->AddedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *RemovedDeviceCount)
{
    GAP_LE_Remove_Device_From_Resolving_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(ResolvingListEntries != NULL)
        {
            Params->ResolvingListEntries = (qapi_BLE_GAP_LE_Resolving_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount));
            memscpy(Params->ResolvingListEntries, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount), ResolvingListEntries, (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->ResolvingListEntries = NULL;
        }
        if(RemovedDeviceCount != NULL)
        {
            Params->RemovedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->RemovedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REMOVE_DEVICE_FROM_RESOLVING_LIST, MessageSize, (uint8_t *)Params);

        if(RemovedDeviceCount != NULL)
            memscpy(RemovedDeviceCount, sizeof(uint32_t), Params->RemovedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Resolving_List_Size(uint32_t BluetoothStackID, uint32_t *ResolvingListSize)
{
    GAP_LE_Read_Resolving_List_Size_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_READ_RESOLVING_LIST_SIZE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_READ_RESOLVING_LIST_SIZE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(ResolvingListSize != NULL)
        {
            Params->ResolvingListSize = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->ResolvingListSize = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_READ_RESOLVING_LIST_SIZE, MessageSize, (uint8_t *)Params);

        if(ResolvingListSize != NULL)
            memscpy(ResolvingListSize, sizeof(uint32_t), Params->ResolvingListSize, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, qapi_BLE_GAP_LE_Privacy_Mode_t PrivacyMode)
{
    GAP_LE_Set_Resolving_List_Privacy_Mode_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_RESOLVING_LIST_PRIVACY_MODE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Peer_Identity_Address_Type = Peer_Identity_Address_Type;
        Params->Peer_Identity_Address = *((qapi_BLE_BD_ADDR_t *)&Peer_Identity_Address);
        Params->PrivacyMode = PrivacyMode;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_RESOLVING_LIST_PRIVACY_MODE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Data_Length(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime)
{
    GAP_LE_Set_Data_Length_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_DATA_LENGTH_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->SuggestedTxPacketSize = SuggestedTxPacketSize;
        Params->SuggestedTxPacketTime = SuggestedTxPacketTime;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_DATA_LENGTH, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Data_Length(uint32_t BluetoothStackID, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime)
{
    GAP_LE_Set_Default_Data_Length_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_DEFAULT_DATA_LENGTH_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->SuggestedTxPacketSize = SuggestedTxPacketSize;
        Params->SuggestedTxPacketTime = SuggestedTxPacketTime;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_DEFAULT_DATA_LENGTH, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Default_Data_Length(uint32_t BluetoothStackID, uint16_t *SuggestedTxPacketSize, uint16_t *SuggestedTxPacketTime)
{
    GAP_LE_Query_Default_Data_Length_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_DEFAULT_DATA_LENGTH_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t)) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_DEFAULT_DATA_LENGTH_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(SuggestedTxPacketSize != NULL)
        {
            Params->SuggestedTxPacketSize = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->SuggestedTxPacketSize = NULL;
        }
        if(SuggestedTxPacketTime != NULL)
        {
            Params->SuggestedTxPacketTime = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->SuggestedTxPacketTime = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_DEFAULT_DATA_LENGTH, MessageSize, (uint8_t *)Params);

        if(SuggestedTxPacketSize != NULL)
            memscpy(SuggestedTxPacketSize, sizeof(uint16_t), Params->SuggestedTxPacketSize, sizeof(uint16_t));

        if(SuggestedTxPacketTime != NULL)
            memscpy(SuggestedTxPacketTime, sizeof(uint16_t), Params->SuggestedTxPacketTime, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Connection_PHY(uint32_t BluetoothStackID, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference)
{
    GAP_LE_Set_Default_Connection_PHY_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_DEFAULT_CONNECTION_PHY_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->TxPHYSPreference = TxPHYSPreference;
        Params->RxPHYSPreference = RxPHYSPreference;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_DEFAULT_CONNECTION_PHY, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_PHY(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference)
{
    GAP_LE_Set_Connection_PHY_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTION_PHY_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->TxPHYSPreference = TxPHYSPreference;
        Params->RxPHYSPreference = RxPHYSPreference;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTION_PHY, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_PHY(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_PHY_Type_t *TxPHY, qapi_BLE_GAP_LE_PHY_Type_t *RxPHY)
{
    GAP_LE_Query_Connection_PHY_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_CONNECTION_PHY_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_PHY_Type_t)) + ALIGN32(sizeof(qapi_BLE_GAP_LE_PHY_Type_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_CONNECTION_PHY_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        if(TxPHY != NULL)
        {
            Params->TxPHY = (qapi_BLE_GAP_LE_PHY_Type_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_PHY_Type_t));
        }
        else
        {
            Params->TxPHY = NULL;
        }
        if(RxPHY != NULL)
        {
            Params->RxPHY = (qapi_BLE_GAP_LE_PHY_Type_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_PHY_Type_t));
        }
        else
        {
            Params->RxPHY = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_CONNECTION_PHY, MessageSize, (uint8_t *)Params);

        if(TxPHY != NULL)
            memscpy(TxPHY, sizeof(qapi_BLE_GAP_LE_PHY_Type_t), Params->TxPHY, sizeof(qapi_BLE_GAP_LE_PHY_Type_t));

        if(RxPHY != NULL)
            memscpy(RxPHY, sizeof(qapi_BLE_GAP_LE_PHY_Type_t), Params->RxPHY, sizeof(qapi_BLE_GAP_LE_PHY_Type_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(uint32_t BluetoothStackID, uint32_t *MaximumAdvertisingDataLength)
{
    GAP_LE_Query_Maximum_Advertising_Data_Length_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_MAXIMUM_ADVERTISING_DATA_LENGTH_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_MAXIMUM_ADVERTISING_DATA_LENGTH_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(MaximumAdvertisingDataLength != NULL)
        {
            Params->MaximumAdvertisingDataLength = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->MaximumAdvertisingDataLength = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_MAXIMUM_ADVERTISING_DATA_LENGTH, MessageSize, (uint8_t *)Params);

        if(MaximumAdvertisingDataLength != NULL)
            memscpy(MaximumAdvertisingDataLength, sizeof(uint32_t), Params->MaximumAdvertisingDataLength, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(uint32_t BluetoothStackID, uint32_t *NumberSupportedSets)
{
    GAP_LE_Query_Number_Of_Advertising_Sets_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_NUMBER_OF_ADVERTISING_SETS_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_NUMBER_OF_ADVERTISING_SETS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(NumberSupportedSets != NULL)
        {
            Params->NumberSupportedSets = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->NumberSupportedSets = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_NUMBER_OF_ADVERTISING_SETS, MessageSize, (uint8_t *)Params);

        if(NumberSupportedSets != NULL)
            memscpy(NumberSupportedSets, sizeof(uint32_t), Params->NumberSupportedSets, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *AdvertisingParameters, int8_t *SelectedTxPower)
{
    GAP_LE_Set_Extended_Advertising_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t)) + ALIGN32(sizeof(int8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_EXTENDED_ADVERTISING_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        if(AdvertisingParameters != NULL)
        {
            Params->AdvertisingParameters = (qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t));
            memscpy(Params->AdvertisingParameters, sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t), AdvertisingParameters, sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t));
        }
        else
        {
            Params->AdvertisingParameters = NULL;
        }
        if(SelectedTxPower != NULL)
        {
            Params->SelectedTxPower = (int8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(int8_t));
        }
        else
        {
            Params->SelectedTxPower = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_EXTENDED_ADVERTISING_PARAMETERS, MessageSize, (uint8_t *)Params);

        if(SelectedTxPower != NULL)
            memscpy(SelectedTxPower, sizeof(int8_t), Params->SelectedTxPower, sizeof(int8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_BD_ADDR_t RandomAddress)
{
    GAP_LE_Set_Extended_Advertising_Random_Address_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_EXTENDED_ADVERTISING_RANDOM_ADDRESS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->RandomAddress = *((qapi_BLE_BD_ADDR_t *)&RandomAddress);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_EXTENDED_ADVERTISING_RANDOM_ADDRESS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Operation_Type_t Operation, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Advertising_Data)
{
    GAP_LE_Set_Extended_Advertising_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_EXTENDED_ADVERTISING_DATA_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_EXTENDED_ADVERTISING_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->Operation = Operation;
        Params->FragmentationPreference = FragmentationPreference;
        Params->Length = Length;
        if(Advertising_Data != NULL)
        {
            Params->Advertising_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length));
            memscpy(Params->Advertising_Data, (sizeof(uint8_t) * Length), Advertising_Data, (sizeof(uint8_t) * Length));
        }
        else
        {
            Params->Advertising_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_EXTENDED_ADVERTISING_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Scan_Response_Data)
{
    GAP_LE_Set_Extended_Scan_Response_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_EXTENDED_SCAN_RESPONSE_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->FragmentationPreference = FragmentationPreference;
        Params->Length = Length;
        if(Scan_Response_Data != NULL)
        {
            Params->Scan_Response_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length));
            memscpy(Params->Scan_Response_Data, (sizeof(uint8_t) * Length), Scan_Response_Data, (sizeof(uint8_t) * Length));
        }
        else
        {
            Params->Scan_Response_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_EXTENDED_SCAN_RESPONSE_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Extended_Advertising(uint32_t BluetoothStackID, boolean_t Enable, uint8_t NumberOfSets, uint8_t *AdvertisingHandleList, uint32_t *DurationList, uint8_t *MaxExtendedAdvertisingEventList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Enable_Extended_Advertising_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ENABLE_EXTENDED_ADVERTISING_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * NumberOfSets)) + ALIGN32((sizeof(uint32_t) * NumberOfSets)) + ALIGN32((sizeof(uint8_t) * NumberOfSets));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_ENABLE_EXTENDED_ADVERTISING_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Enable = *((boolean_t *)&Enable);
        Params->NumberOfSets = NumberOfSets;
        if(AdvertisingHandleList != NULL)
        {
            Params->AdvertisingHandleList = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * NumberOfSets));
            memscpy(Params->AdvertisingHandleList, (sizeof(uint8_t) * NumberOfSets), AdvertisingHandleList, (sizeof(uint8_t) * NumberOfSets));
        }
        else
        {
            Params->AdvertisingHandleList = NULL;
        }
        if(DurationList != NULL)
        {
            Params->DurationList = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint32_t) * NumberOfSets));
            memscpy(Params->DurationList, (sizeof(uint32_t) * NumberOfSets), DurationList, (sizeof(uint32_t) * NumberOfSets));
        }
        else
        {
            Params->DurationList = NULL;
        }
        if(MaxExtendedAdvertisingEventList != NULL)
        {
            Params->MaxExtendedAdvertisingEventList = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * NumberOfSets));
            memscpy(Params->MaxExtendedAdvertisingEventList, (sizeof(uint8_t) * NumberOfSets), MaxExtendedAdvertisingEventList, (sizeof(uint8_t) * NumberOfSets));
        }
        else
        {
            Params->MaxExtendedAdvertisingEventList = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ENABLE_EXTENDED_ADVERTISING, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Advertising_Sets(uint32_t BluetoothStackID, uint32_t NumberAdvertisingSetHandles, uint8_t *AdvertisingHandles, uint32_t *RemovedSetCount)
{
    GAP_LE_Remove_Advertising_Sets_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REMOVE_ADVERTISING_SETS_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * NumberAdvertisingSetHandles)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REMOVE_ADVERTISING_SETS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->NumberAdvertisingSetHandles = NumberAdvertisingSetHandles;
        if(AdvertisingHandles != NULL)
        {
            Params->AdvertisingHandles = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * NumberAdvertisingSetHandles));
            memscpy(Params->AdvertisingHandles, (sizeof(uint8_t) * NumberAdvertisingSetHandles), AdvertisingHandles, (sizeof(uint8_t) * NumberAdvertisingSetHandles));
        }
        else
        {
            Params->AdvertisingHandles = NULL;
        }
        if(RemovedSetCount != NULL)
        {
            Params->RemovedSetCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->RemovedSetCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REMOVE_ADVERTISING_SETS, MessageSize, (uint8_t *)Params);

        if(RemovedSetCount != NULL)
            memscpy(RemovedSetCount, sizeof(uint32_t), Params->RemovedSetCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t *PeriodicAdvertisingParameters)
{
    GAP_LE_Set_Periodic_Advertising_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        if(PeriodicAdvertisingParameters != NULL)
        {
            Params->PeriodicAdvertisingParameters = (qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t));
            memscpy(Params->PeriodicAdvertisingParameters, sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t), PeriodicAdvertisingParameters, sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t));
        }
        else
        {
            Params->PeriodicAdvertisingParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_PERIODIC_ADVERTISING_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, uint32_t Length, uint8_t *Advertising_Data)
{
    GAP_LE_Set_Periodic_Advertising_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_DATA_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->Length = Length;
        if(Advertising_Data != NULL)
        {
            Params->Advertising_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length));
            memscpy(Params->Advertising_Data, (sizeof(uint8_t) * Length), Advertising_Data, (sizeof(uint8_t) * Length));
        }
        else
        {
            Params->Advertising_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_PERIODIC_ADVERTISING_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Periodic_Advertising(uint32_t BluetoothStackID, boolean_t Enable, uint8_t AdvertisingHandle)
{
    GAP_LE_Enable_Periodic_Advertising_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ENABLE_PERIODIC_ADVERTISING_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Enable = *((boolean_t *)&Enable);
        Params->AdvertisingHandle = AdvertisingHandle;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ENABLE_PERIODIC_ADVERTISING, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, uint32_t NumberScanningPHYs, qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *ScanningParameterList)
{
    GAP_LE_Set_Extended_Scan_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_EXTENDED_SCAN_PARAMETERS_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t) * NumberScanningPHYs));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_EXTENDED_SCAN_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->LocalAddressType = LocalAddressType;
        Params->FilterPolicy = FilterPolicy;
        Params->NumberScanningPHYs = NumberScanningPHYs;
        if(ScanningParameterList != NULL)
        {
            Params->ScanningParameterList = (qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t) * NumberScanningPHYs));
            memscpy(Params->ScanningParameterList, (sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t) * NumberScanningPHYs), ScanningParameterList, (sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t) * NumberScanningPHYs));
        }
        else
        {
            Params->ScanningParameterList = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_EXTENDED_SCAN_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Extended_Scan(uint32_t BluetoothStackID, boolean_t Enable, qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t FilterDuplicates, uint32_t Duration, uint32_t Period, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Enable_Extended_Scan_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ENABLE_EXTENDED_SCAN_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Enable = *((boolean_t *)&Enable);
        Params->FilterDuplicates = FilterDuplicates;
        Params->Duration = Duration;
        Params->Period = Period;
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ENABLE_EXTENDED_SCAN, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Create_Connection(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, uint32_t NumberOfConnectionParameters, qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *ConnectionParameterList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Extended_Create_Connection_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_EXTENDED_CREATE_CONNECTION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t)) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t) * NumberOfConnectionParameters));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_EXTENDED_CREATE_CONNECTION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InitatorFilterPolicy = InitatorFilterPolicy;
        Params->RemoteAddressType = RemoteAddressType;
        if(RemoteDevice != NULL)
        {
            Params->RemoteDevice = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
            memscpy(Params->RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t), RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->RemoteDevice = NULL;
        }
        Params->LocalAddressType = LocalAddressType;
        Params->NumberOfConnectionParameters = NumberOfConnectionParameters;
        if(ConnectionParameterList != NULL)
        {
            Params->ConnectionParameterList = (qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t) * NumberOfConnectionParameters));
            memscpy(Params->ConnectionParameterList, (sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t) * NumberOfConnectionParameters), ConnectionParameterList, (sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t) * NumberOfConnectionParameters));
        }
        else
        {
            Params->ConnectionParameterList = NULL;
        }
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_EXTENDED_CREATE_CONNECTION, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Create_Periodic_Advertising_Synchronization(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Periodic_Filter_Policy_t FilterPolicy, boolean_t ReportingEnabled, uint8_t AdvertisingSID, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, uint16_t PeriodicSkipCount, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Create_Periodic_Advertising_Synchronization_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CREATE_PERIODIC_ADVERTISING_SYNCHRONIZATION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BD_ADDR_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_CREATE_PERIODIC_ADVERTISING_SYNCHRONIZATION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->FilterPolicy = FilterPolicy;
        Params->ReportingEnabled = *((boolean_t *)&ReportingEnabled);
        Params->AdvertisingSID = AdvertisingSID;
        Params->RemoteAddressType = RemoteAddressType;
        if(RemoteDevice != NULL)
        {
            Params->RemoteDevice = (qapi_BLE_BD_ADDR_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_BD_ADDR_t));
            memscpy(Params->RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t), RemoteDevice, sizeof(qapi_BLE_BD_ADDR_t));
        }
        else
        {
            Params->RemoteDevice = NULL;
        }
        Params->PeriodicSkipCount = PeriodicSkipCount;
        Params->SyncTimeout = SyncTimeout;
        Params->CTE_Type = CTE_Type;
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CREATE_PERIODIC_ADVERTISING_SYNCHRONIZATION, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Create_Periodic_Synchronization(uint32_t BluetoothStackID)
{
    GAP_LE_Cancel_Create_Periodic_Synchronization_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CANCEL_CREATE_PERIODIC_SYNCHRONIZATION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CANCEL_CREATE_PERIODIC_SYNCHRONIZATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Terminate_Periodic_Synchronization(uint32_t BluetoothStackID, uint16_t SyncHandle)
{
    GAP_LE_Terminate_Periodic_Synchronization_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_TERMINATE_PERIODIC_SYNCHRONIZATION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->SyncHandle = SyncHandle;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_TERMINATE_PERIODIC_SYNCHRONIZATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_Periodic_Advertising_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries, uint32_t *AddedDeviceCount)
{
    GAP_LE_Add_Device_To_Periodic_Advertising_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(PeriodicAdvertisingListEntries != NULL)
        {
            Params->PeriodicAdvertisingListEntries = (qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount));
            memscpy(Params->PeriodicAdvertisingListEntries, (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount), PeriodicAdvertisingListEntries, (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->PeriodicAdvertisingListEntries = NULL;
        }
        if(AddedDeviceCount != NULL)
        {
            Params->AddedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->AddedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_ADD_DEVICE_TO_PERIODIC_ADVERTISING_LIST, MessageSize, (uint8_t *)Params);

        if(AddedDeviceCount != NULL)
            memscpy(AddedDeviceCount, sizeof(uint32_t), Params->AddedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_Periodic_Advertising_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries, uint32_t *RemovedDeviceCount)
{
    GAP_LE_Remove_Device_From_Periodic_Advertising_List_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE) + ALIGN32((sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount)) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISING_LIST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->DeviceCount = DeviceCount;
        if(PeriodicAdvertisingListEntries != NULL)
        {
            Params->PeriodicAdvertisingListEntries = (qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount));
            memscpy(Params->PeriodicAdvertisingListEntries, (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount), PeriodicAdvertisingListEntries, (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t) * DeviceCount));
        }
        else
        {
            Params->PeriodicAdvertisingListEntries = NULL;
        }
        if(RemovedDeviceCount != NULL)
        {
            Params->RemovedDeviceCount = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->RemovedDeviceCount = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_REMOVE_DEVICE_FROM_PERIODIC_ADVERTISING_LIST, MessageSize, (uint8_t *)Params);

        if(RemovedDeviceCount != NULL)
            memscpy(RemovedDeviceCount, sizeof(uint32_t), Params->RemovedDeviceCount, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Periodic_Advertising_List_Size(uint32_t BluetoothStackID, uint32_t *PeriodicAdvertisingListSize)
{
    GAP_LE_Read_Periodic_Advertising_List_Size_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_READ_PERIODIC_ADVERTISING_LIST_SIZE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_READ_PERIODIC_ADVERTISING_LIST_SIZE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(PeriodicAdvertisingListSize != NULL)
        {
            Params->PeriodicAdvertisingListSize = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->PeriodicAdvertisingListSize = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_READ_PERIODIC_ADVERTISING_LIST_SIZE, MessageSize, (uint8_t *)Params);

        if(PeriodicAdvertisingListSize != NULL)
            memscpy(PeriodicAdvertisingListSize, sizeof(uint32_t), Params->PeriodicAdvertisingListSize, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(uint32_t BluetoothStackID, qapi_BLE_Secure_Connections_Randomizer_t *Randomizer, qapi_BLE_Secure_Connections_Confirmation_t *Confirmation)
{
    GAP_LE_Query_Local_Secure_Connections_OOB_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_LOCAL_SECURE_CONNECTIONS_OOB_DATA_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Secure_Connections_Randomizer_t)) + ALIGN32(sizeof(qapi_BLE_Secure_Connections_Confirmation_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_LOCAL_SECURE_CONNECTIONS_OOB_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(Randomizer != NULL)
        {
            Params->Randomizer = (qapi_BLE_Secure_Connections_Randomizer_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Secure_Connections_Randomizer_t));
        }
        else
        {
            Params->Randomizer = NULL;
        }
        if(Confirmation != NULL)
        {
            Params->Confirmation = (qapi_BLE_Secure_Connections_Confirmation_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Secure_Connections_Confirmation_t));
        }
        else
        {
            Params->Confirmation = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_LOCAL_SECURE_CONNECTIONS_OOB_DATA, MessageSize, (uint8_t *)Params);

        if(Randomizer != NULL)
            memscpy(Randomizer, sizeof(qapi_BLE_Secure_Connections_Randomizer_t), Params->Randomizer, sizeof(qapi_BLE_Secure_Connections_Randomizer_t));

        if(Confirmation != NULL)
            memscpy(Confirmation, sizeof(qapi_BLE_Secure_Connections_Confirmation_t), Params->Confirmation, sizeof(qapi_BLE_Secure_Connections_Confirmation_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, uint8_t CTE_Length, qapi_BLE_GAP_LE_CTE_Type_t CTE_Type, uint8_t CTE_Count, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs)
{
    GAP_LE_Set_Connectionless_CTE_Transmit_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * LengthOfSwitchingPattern));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->CTE_Length = CTE_Length;
        Params->CTE_Type = CTE_Type;
        Params->CTE_Count = CTE_Count;
        Params->LengthOfSwitchingPattern = LengthOfSwitchingPattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * LengthOfSwitchingPattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern), Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Enable(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, boolean_t CTE_Enable)
{
    GAP_LE_Set_Connectionless_CTE_Transmit_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->AdvertisingHandle = AdvertisingHandle;
        Params->CTE_Enable = *((boolean_t *)&CTE_Enable);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTIONLESS_CTE_TRANSMIT_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_IQ_Sampling_Enable(uint32_t BluetoothStackID, uint16_t SyncHandle, boolean_t SamplingEnable, qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType, uint8_t Max_Sampled_CTEs, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs)
{
    GAP_LE_Set_Connectionless_IQ_Sampling_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * LengthOfSwitchingPattern));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->SyncHandle = SyncHandle;
        Params->SamplingEnable = *((boolean_t *)&SamplingEnable);
        Params->SlotDurationsType = SlotDurationsType;
        Params->Max_Sampled_CTEs = Max_Sampled_CTEs;
        Params->LengthOfSwitchingPattern = LengthOfSwitchingPattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * LengthOfSwitchingPattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern), Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTIONLESS_IQ_SAMPLING_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_CTE_Receive_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t SamplingEnable, qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs)
{
    GAP_LE_Set_Connection_CTE_Receive_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * LengthOfSwitchingPattern));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->SamplingEnable = SamplingEnable;
        Params->SlotDurationsType = SlotDurationsType;
        Params->LengthOfSwitchingPattern = LengthOfSwitchingPattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * LengthOfSwitchingPattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern), Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTION_CTE_RECEIVE_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_CTE_Request_Enable(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Enable, uint16_t CTE_Request_Interval, uint8_t Requested_CTE_Length, qapi_BLE_GAP_LE_CTE_Type_t Requested_CTE_Type)
{
    GAP_LE_Connection_CTE_Request_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CONNECTION_CTE_REQUEST_ENABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Enable = *((boolean_t *)&Enable);
        Params->CTE_Request_Interval = CTE_Request_Interval;
        Params->Requested_CTE_Length = Requested_CTE_Length;
        Params->Requested_CTE_Type = Requested_CTE_Type;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CONNECTION_CTE_REQUEST_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_CTE_Transmit_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t CTE_Types, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs)
{
    GAP_LE_Set_Connection_CTE_Transmit_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * LengthOfSwitchingPattern));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->CTE_Types = CTE_Types;
        Params->LengthOfSwitchingPattern = LengthOfSwitchingPattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * LengthOfSwitchingPattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern), Antenna_IDs, (sizeof(uint8_t) * LengthOfSwitchingPattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_CONNECTION_CTE_TRANSMIT_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_CTE_Response_Enable(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Enable)
{
    GAP_LE_Connection_CTE_Response_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_CONNECTION_CTE_RESPONSE_ENABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Enable = *((boolean_t *)&Enable);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CONNECTION_CTE_RESPONSE_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Antenna_Information(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Antenna_Information_t *AntennaInfo)
{
    GAP_LE_Query_Antenna_Information_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_QUERY_ANTENNA_INFORMATION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_LE_Antenna_Information_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_QUERY_ANTENNA_INFORMATION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(AntennaInfo != NULL)
        {
            Params->AntennaInfo = (qapi_BLE_GAP_LE_Antenna_Information_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_LE_Antenna_Information_t));
        }
        else
        {
            Params->AntennaInfo = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_QUERY_ANTENNA_INFORMATION, MessageSize, (uint8_t *)Params);

        if(AntennaInfo != NULL)
            memscpy(AntennaInfo, sizeof(qapi_BLE_GAP_LE_Antenna_Information_t), Params->AntennaInfo, sizeof(qapi_BLE_GAP_LE_Antenna_Information_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Receive_Enable(uint32_t BluetoothStackID, uint16_t SyncHandle, boolean_t Enable)
{
    GAP_LE_Set_Periodic_Advertising_Receive_Enable_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->SyncHandle = SyncHandle;
        Params->Enable = *((boolean_t *)&Enable);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_PERIODIC_ADVERTISING_RECEIVE_ENABLE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t ServiceData, uint16_t SyncHandle)
{
    GAP_LE_Periodic_Advertising_Sync_Transfer_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->ServiceData = ServiceData;
        Params->SyncHandle = SyncHandle;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Periodic_Advertising_Set_Info_Transfer(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t ServiceData, uint8_t AdvertisingHandle)
{
    GAP_LE_Periodic_Advertising_Set_Info_Transfer_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->ServiceData = ServiceData;
        Params->AdvertisingHandle = AdvertisingHandle;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_PERIODIC_ADVERTISING_SET_INFO_TRANSFER, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode, uint16_t Skip, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->BD_ADDR = *((qapi_BLE_BD_ADDR_t *)&BD_ADDR);
        Params->Mode = Mode;
        Params->Skip = Skip;
        Params->SyncTimeout = SyncTimeout;
        Params->CTE_Type = CTE_Type;
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode, uint16_t Skip, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter)
{
    GAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Mode = Mode;
        Params->Skip = Skip;
        Params->SyncTimeout = SyncTimeout;
        Params->CTE_Type = CTE_Type;
        Params->CallbackParameter = CallbackParameter;

        if(GAP_LE_Event_Callback != NULL)
        {
            CBInfo.FileID = FILE_ID_GAPAPI;
            CBInfo.CallbackID = CALLBACK_ID_GAP_LE_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)GAP_LE_Event_Callback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((GAP_LE_Event_Callback == NULL) || (Callback_Register(&CBHandle, GAP_LE_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, true) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_DEFAULT_PERIODIC_ADVERTISING_SYNC_TRANSFER_PARAMETERS, MessageSize, (uint8_t *)Params);

        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

void *QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Initialize_AES_CMAC_Operation(qapi_BLE_Encryption_Key_t *Key, uint32_t MessageLength)
{
    GAP_LE_Initialize_AES_CMAC_Operation_Params_t *Params;
    void * ret_val = NULL;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_INITIALIZE_AES_CMAC_OPERATION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAP_LE_INITIALIZE_AES_CMAC_OPERATION_PARAMS_SIZE);
        if(Key != NULL)
        {
            Params->Key = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
            memscpy(Params->Key, sizeof(qapi_BLE_Encryption_Key_t), Key, sizeof(qapi_BLE_Encryption_Key_t));
        }
        else
        {
            Params->Key = NULL;
        }
        Params->MessageLength = MessageLength;

        ret_val = (void *)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_INITIALIZE_AES_CMAC_OPERATION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

