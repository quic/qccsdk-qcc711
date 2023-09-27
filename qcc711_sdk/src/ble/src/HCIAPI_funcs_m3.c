/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_hci.h"
#include "HCIAPI_params.h"
#include "HCIAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Version_Supported(uint32_t BluetoothStackID, qapi_BLE_HCI_Version_t *HCI_Version)
{
    HCI_Version_Supported_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_VERSION_SUPPORTED_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_HCI_Version_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_VERSION_SUPPORTED_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(HCI_Version != NULL)
        {
            Params->HCI_Version = (qapi_BLE_HCI_Version_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_HCI_Version_t));
        }
        else
        {
            Params->HCI_Version = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_VERSION_SUPPORTED, MessageSize, (uint8_t *)Params);

        if(HCI_Version != NULL)
            memscpy(HCI_Version, sizeof(qapi_BLE_HCI_Version_t), Params->HCI_Version, sizeof(qapi_BLE_HCI_Version_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Register_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_HCI_Event_Callback_t HCI_EventCallback, unsigned long CallbackParameter)
{
    HCI_Register_Event_Callback_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_REGISTER_EVENT_CALLBACK_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;

        if(HCI_EventCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_HCIAPI;
            CBInfo.CallbackID = CALLBACK_ID_HCI_EVENT_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)HCI_EventCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((HCI_EventCallback == NULL) || (Callback_Register(&CBHandle, HCI_Event_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_REGISTER_EVENT_CALLBACK, MessageSize, (uint8_t *)Params);

            if(HCI_EventCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Register_ACL_Data_Callback(uint32_t BluetoothStackID, qapi_BLE_HCI_ACL_Data_Callback_t HCI_ACLDataCallback, unsigned long CallbackParameter)
{
    HCI_Register_ACL_Data_Callback_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_REGISTER_ACL_DATA_CALLBACK_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;

        if(HCI_ACLDataCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_HCIAPI;
            CBInfo.CallbackID = CALLBACK_ID_HCI_ACL_DATA_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)HCI_ACLDataCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((HCI_ACLDataCallback == NULL) || (Callback_Register(&CBHandle, HCI_ACL_Data_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_REGISTER_ACL_DATA_CALLBACK, MessageSize, (uint8_t *)Params);

            if(HCI_ACLDataCallback != NULL)
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

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Un_Register_Callback(uint32_t BluetoothStackID, uint32_t CallbackID)
{
    HCI_Un_Register_Callback_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_UN_REGISTER_CALLBACK_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackID = CallbackID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_UN_REGISTER_CALLBACK, MessageSize, (uint8_t *)Params);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_HCIAPI, CALLBACK_ID_HCI_EVENT_CALLBACK_T, CallbackID);

        if(ret_val == 0)
            Callback_UnregisterByKey(FILE_ID_HCIAPI, CALLBACK_ID_HCI_ACL_DATA_CALLBACK_T, CallbackID);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Send_ACL_Data(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Flags, uint16_t ACLDataLength, uint8_t *ACLData)
{
    HCI_Send_ACL_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_SEND_ACL_DATA_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * ACLDataLength));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_SEND_ACL_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Connection_Handle = Connection_Handle;
        Params->Flags = Flags;
        Params->ACLDataLength = ACLDataLength;
        if(ACLData != NULL)
        {
            Params->ACLData = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * ACLDataLength));
            memscpy(Params->ACLData, (sizeof(uint8_t) * ACLDataLength), ACLData, (sizeof(uint8_t) * ACLDataLength));
        }
        else
        {
            Params->ACLData = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_SEND_ACL_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Reset(uint32_t BluetoothStackID, uint8_t *StatusResult)
{
    HCI_Reset_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_RESET_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_RESET_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_RESET, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Receiver_Test(uint32_t BluetoothStackID, uint8_t RX_Frequency, uint8_t *StatusResult)
{
    HCI_LE_Receiver_Test_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_RECEIVER_TEST_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_RECEIVER_TEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->RX_Frequency = RX_Frequency;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_RECEIVER_TEST, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Transmitter_Test(uint32_t BluetoothStackID, uint8_t TX_Frequency, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t *StatusResult)
{
    HCI_LE_Transmitter_Test_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_TRANSMITTER_TEST_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_TRANSMITTER_TEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TX_Frequency = TX_Frequency;
        Params->Length_Of_Test_Data = Length_Of_Test_Data;
        Params->Packet_Payload = Packet_Payload;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_TRANSMITTER_TEST, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Test_End(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *Number_Of_PacketsResult)
{
    HCI_LE_Test_End_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_TEST_END_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t)) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_TEST_END_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }
        if(Number_Of_PacketsResult != NULL)
        {
            Params->Number_Of_PacketsResult = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->Number_Of_PacketsResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_TEST_END, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        if(Number_Of_PacketsResult != NULL)
            memscpy(Number_Of_PacketsResult, sizeof(uint16_t), Params->Number_Of_PacketsResult, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Enhanced_Receiver_Test(uint32_t BluetoothStackID, uint8_t RX_Channel, uint8_t PHY, uint8_t Modulation_Index, uint8_t *StatusResult)
{
    HCI_LE_Enhanced_Receiver_Test_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_ENHANCED_RECEIVER_TEST_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_ENHANCED_RECEIVER_TEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->RX_Channel = RX_Channel;
        Params->PHY = PHY;
        Params->Modulation_Index = Modulation_Index;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_ENHANCED_RECEIVER_TEST, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(uint32_t BluetoothStackID, uint8_t TX_Channel, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t PHY, uint8_t *StatusResult)
{
    HCI_LE_Enhanced_Transmitter_Test_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_ENHANCED_TRANSMITTER_TEST_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_ENHANCED_TRANSMITTER_TEST_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TX_Channel = TX_Channel;
        Params->Length_Of_Test_Data = Length_Of_Test_Data;
        Params->Packet_Payload = Packet_Payload;
        Params->PHY = PHY;
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_ENHANCED_TRANSMITTER_TEST, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Receiver_Test_V3(uint32_t BluetoothStackID, uint8_t RX_Channel, uint8_t PHY, uint8_t Modulation_Index, uint8_t Expected_CTE_Length, uint8_t Expected_CTE_Type, uint8_t Slot_Durations, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult)
{
    HCI_LE_Receiver_Test_V3_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_RECEIVER_TEST_V3_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length_Of_Switching_Pattern)) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_RECEIVER_TEST_V3_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->RX_Channel = RX_Channel;
        Params->PHY = PHY;
        Params->Modulation_Index = Modulation_Index;
        Params->Expected_CTE_Length = Expected_CTE_Length;
        Params->Expected_CTE_Type = Expected_CTE_Type;
        Params->Slot_Durations = Slot_Durations;
        Params->Length_Of_Switching_Pattern = Length_Of_Switching_Pattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length_Of_Switching_Pattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * Length_Of_Switching_Pattern), Antenna_IDs, (sizeof(uint8_t) * Length_Of_Switching_Pattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_RECEIVER_TEST_V3, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Transmitter_Test_V3(uint32_t BluetoothStackID, uint8_t TX_Channel, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t PHY, uint8_t CTE_Length, uint8_t CTE_Type, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult)
{
    HCI_LE_Transmitter_Test_V3_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(HCI_LE_TRANSMITTER_TEST_V3_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length_Of_Switching_Pattern)) + ALIGN32(sizeof(uint8_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_LE_TRANSMITTER_TEST_V3_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->TX_Channel = TX_Channel;
        Params->Length_Of_Test_Data = Length_Of_Test_Data;
        Params->Packet_Payload = Packet_Payload;
        Params->PHY = PHY;
        Params->CTE_Length = CTE_Length;
        Params->CTE_Type = CTE_Type;
        Params->Length_Of_Switching_Pattern = Length_Of_Switching_Pattern;
        if(Antenna_IDs != NULL)
        {
            Params->Antenna_IDs = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length_Of_Switching_Pattern));
            memscpy(Params->Antenna_IDs, (sizeof(uint8_t) * Length_Of_Switching_Pattern), Antenna_IDs, (sizeof(uint8_t) * Length_Of_Switching_Pattern));
        }
        else
        {
            Params->Antenna_IDs = NULL;
        }
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_LE_TRANSMITTER_TEST_V3, MessageSize, (uint8_t *)Params);

        if(StatusResult != NULL)
            memscpy(StatusResult, sizeof(uint8_t), Params->StatusResult, sizeof(uint8_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

