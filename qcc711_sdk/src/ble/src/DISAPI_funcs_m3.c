/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_dis.h"
#include "DISAPI_params.h"
#include "DISAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Initialize_Service(uint32_t BluetoothStackID, uint32_t *ServiceID)
{
    DIS_Initialize_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_INITIALIZE_SERVICE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_INITIALIZE_SERVICE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(ServiceID != NULL)
        {
            Params->ServiceID = (uint32_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint32_t));
        }
        else
        {
            Params->ServiceID = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_INITIALIZE_SERVICE, MessageSize, (uint8_t *)Params);

        if(ServiceID != NULL)
            memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange)
{
    DIS_Initialize_Service_Handle_Range_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
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

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_INITIALIZE_SERVICE_HANDLE_RANGE, MessageSize, (uint8_t *)Params);

        if(ServiceID != NULL)
            memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

        if(ServiceHandleRange != NULL)
            memscpy(ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), Params->ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID)
{
    DIS_Cleanup_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_CLEANUP_SERVICE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_CLEANUP_SERVICE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

unsigned int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Number_Attributes(void)
{
    unsigned int ret_val = -1;

    ret_val = (unsigned int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_NUMBER_ATTRIBUTES, 0, NULL);


    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_System_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID)
{
    DIS_Set_System_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_SET_SYSTEM_ID_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_DIS_System_ID_Value_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_SYSTEM_ID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SystemID != NULL)
        {
            Params->SystemID = (qapi_BLE_DIS_System_ID_Value_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_DIS_System_ID_Value_t));
            memscpy(Params->SystemID, sizeof(qapi_BLE_DIS_System_ID_Value_t), SystemID, sizeof(qapi_BLE_DIS_System_ID_Value_t));
        }
        else
        {
            Params->SystemID = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_SYSTEM_ID, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_System_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID)
{
    DIS_Query_System_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_SYSTEM_ID_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_DIS_System_ID_Value_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_SYSTEM_ID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SystemID != NULL)
        {
            Params->SystemID = (qapi_BLE_DIS_System_ID_Value_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_DIS_System_ID_Value_t));
        }
        else
        {
            Params->SystemID = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_SYSTEM_ID, MessageSize, (uint8_t *)Params);

        if(SystemID != NULL)
            memscpy(SystemID, sizeof(qapi_BLE_DIS_System_ID_Value_t), Params->SystemID, sizeof(qapi_BLE_DIS_System_ID_Value_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_IEEE_Certification_Data(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t Length, uint8_t *IEEE_Certification_Data)
{
    DIS_Set_IEEE_Certification_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_SET_IEEE_CERTIFICATION_DATA_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Length));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_IEEE_CERTIFICATION_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->Length = Length;
        if(IEEE_Certification_Data != NULL)
        {
            Params->IEEE_Certification_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Length));
            memscpy(Params->IEEE_Certification_Data, (sizeof(uint8_t) * Length), IEEE_Certification_Data, (sizeof(uint8_t) * Length));
        }
        else
        {
            Params->IEEE_Certification_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_IEEE_CERTIFICATION_DATA, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_PNP_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data)
{
    DIS_Set_PNP_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_SET_PNP_ID_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_DIS_PNP_ID_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_PNP_ID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(PNP_ID_Data != NULL)
        {
            Params->PNP_ID_Data = (qapi_BLE_DIS_PNP_ID_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_DIS_PNP_ID_Data_t));
            memscpy(Params->PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t), PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t));
        }
        else
        {
            Params->PNP_ID_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_PNP_ID, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_PNP_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data)
{
    DIS_Query_PNP_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_PNP_ID_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_DIS_PNP_ID_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_PNP_ID_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(PNP_ID_Data != NULL)
        {
            Params->PNP_ID_Data = (qapi_BLE_DIS_PNP_ID_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_DIS_PNP_ID_Data_t));
        }
        else
        {
            Params->PNP_ID_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_PNP_ID, MessageSize, (uint8_t *)Params);

        if(PNP_ID_Data != NULL)
            memscpy(PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t), Params->PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Decode_PNP_ID(uint32_t ValueLength, uint8_t *Value, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data)
{
    DIS_Decode_PNP_ID_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_DECODE_PNP_ID_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * ValueLength)) + ALIGN32(sizeof(qapi_BLE_DIS_PNP_ID_Data_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_DECODE_PNP_ID_PARAMS_SIZE);
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
        if(PNP_ID_Data != NULL)
        {
            Params->PNP_ID_Data = (qapi_BLE_DIS_PNP_ID_Data_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_DIS_PNP_ID_Data_t));
        }
        else
        {
            Params->PNP_ID_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_DECODE_PNP_ID, MessageSize, (uint8_t *)Params);

        if(PNP_ID_Data != NULL)
            memscpy(PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t), Params->PNP_ID_Data, sizeof(qapi_BLE_DIS_PNP_ID_Data_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

