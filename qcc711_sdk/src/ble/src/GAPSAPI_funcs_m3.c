/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_gaps.h"
#include "GAPSAPI_params.h"
#include "GAPSAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Initialize_Service(uint32_t BluetoothStackID, uint32_t *ServiceID)
{
    GAPS_Initialize_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_INITIALIZE_SERVICE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_INITIALIZE_SERVICE_PARAMS_SIZE);
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

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_INITIALIZE_SERVICE, MessageSize, (uint8_t *)Params);

        if(ServiceID != NULL)
            memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange)
{
    GAPS_Initialize_Service_Handle_Range_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE) + ALIGN32(sizeof(uint32_t)) + ALIGN32(sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE);
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

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_INITIALIZE_SERVICE_HANDLE_RANGE, MessageSize, (uint8_t *)Params);

        if(ServiceID != NULL)
            memscpy(ServiceID, sizeof(uint32_t), Params->ServiceID, sizeof(uint32_t));

        if(ServiceHandleRange != NULL)
            memscpy(ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t), Params->ServiceHandleRange, sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID)
{
    GAPS_Cleanup_Service_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_CLEANUP_SERVICE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_CLEANUP_SERVICE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

unsigned int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Number_Attributes(void)
{
    unsigned int ret_val = -1;

    ret_val = (unsigned int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_QUERY_NUMBER_ATTRIBUTES, 0, NULL);


    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Device_Appearance(uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t DeviceAppearance)
{
    GAPS_Set_Device_Appearance_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_SET_DEVICE_APPEARANCE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->DeviceAppearance = DeviceAppearance;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_SET_DEVICE_APPEARANCE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Device_Appearance(uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t *DeviceAppearance)
{
    GAPS_Query_Device_Appearance_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_QUERY_DEVICE_APPEARANCE_PARAMS_SIZE) + ALIGN32(sizeof(uint16_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_QUERY_DEVICE_APPEARANCE_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(DeviceAppearance != NULL)
        {
            Params->DeviceAppearance = (uint16_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint16_t));
        }
        else
        {
            Params->DeviceAppearance = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_QUERY_DEVICE_APPEARANCE, MessageSize, (uint8_t *)Params);

        if(DeviceAppearance != NULL)
            memscpy(DeviceAppearance, sizeof(uint16_t), Params->DeviceAppearance, sizeof(uint16_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Preferred_Connection_Parameters(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters)
{
    GAPS_Set_Preferred_Connection_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_SET_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_SET_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(PreferredConnectionParameters != NULL)
        {
            Params->PreferredConnectionParameters = (qapi_BLE_GAP_Preferred_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));
            memscpy(Params->PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t), PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));
        }
        else
        {
            Params->PreferredConnectionParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_SET_PREFERRED_CONNECTION_PARAMETERS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Preferred_Connection_Parameters(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters)
{
    GAPS_Query_Preferred_Connection_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_QUERY_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_QUERY_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(PreferredConnectionParameters != NULL)
        {
            Params->PreferredConnectionParameters = (qapi_BLE_GAP_Preferred_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));
        }
        else
        {
            Params->PreferredConnectionParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_QUERY_PREFERRED_CONNECTION_PARAMETERS, MessageSize, (uint8_t *)Params);

        if(PreferredConnectionParameters != NULL)
            memscpy(PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t), Params->PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Central_Address_Resolution(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t CentralAddressResolution)
{
    GAPS_Set_Central_Address_Resolution_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_SET_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        Params->CentralAddressResolution = CentralAddressResolution;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_SET_CENTRAL_ADDRESS_RESOLUTION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Central_Address_Resolution(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution)
{
    GAPS_Query_Central_Address_Resolution_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_QUERY_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_QUERY_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(CentralAddressResolution != NULL)
        {
            Params->CentralAddressResolution = (qapi_BLE_GAP_Central_Address_Resolution_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));
        }
        else
        {
            Params->CentralAddressResolution = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_QUERY_CENTRAL_ADDRESS_RESOLUTION, MessageSize, (uint8_t *)Params);

        if(CentralAddressResolution != NULL)
            memscpy(CentralAddressResolution, sizeof(qapi_BLE_GAP_Central_Address_Resolution_t), Params->CentralAddressResolution, sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Decode_Preferred_Connection_Parameters(uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters)
{
    GAPS_Decode_Preferred_Connection_Parameters_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_DECODE_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * ValueLength)) + ALIGN32(sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_DECODE_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE);
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
        if(PreferredConnectionParameters != NULL)
        {
            Params->PreferredConnectionParameters = (qapi_BLE_GAP_Preferred_Connection_Parameters_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));
        }
        else
        {
            Params->PreferredConnectionParameters = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_DECODE_PREFERRED_CONNECTION_PARAMETERS, MessageSize, (uint8_t *)Params);

        if(PreferredConnectionParameters != NULL)
            memscpy(PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t), Params->PreferredConnectionParameters, sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Decode_Central_Address_Resolution(uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution)
{
    GAPS_Decode_Central_Address_Resolution_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAPS_DECODE_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * ValueLength)) + ALIGN32(sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(GAPS_DECODE_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE);
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
        if(CentralAddressResolution != NULL)
        {
            Params->CentralAddressResolution = (qapi_BLE_GAP_Central_Address_Resolution_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));
        }
        else
        {
            Params->CentralAddressResolution = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_DECODE_CENTRAL_ADDRESS_RESOLUTION, MessageSize, (uint8_t *)Params);

        if(CentralAddressResolution != NULL)
            memscpy(CentralAddressResolution, sizeof(qapi_BLE_GAP_Central_Address_Resolution_t), Params->CentralAddressResolution, sizeof(qapi_BLE_GAP_Central_Address_Resolution_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

