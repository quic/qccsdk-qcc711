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

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Manufacturer_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName)
{
    DIS_Set_Manufacturer_Name_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(ManufacturerName)
    {
        StringLength = (strlen(ManufacturerName) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_MANUFACTURER_NAME_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_MANUFACTURER_NAME_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(ManufacturerName != NULL)
        {
            Params->ManufacturerName = (char *)(((uint8_t *)Params) + Offset);
            memscpy(Params->ManufacturerName, StringLength, ManufacturerName, StringLength);
        }
        else
        {
            Params->ManufacturerName = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_MANUFACTURER_NAME, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Manufacturer_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName)
{
    DIS_Query_Manufacturer_Name_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_MANUFACTURER_NAME_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_MANUFACTURER_NAME_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(ManufacturerName != NULL)
        {
            Params->ManufacturerName = (char *)(((uint8_t *)Params) + Offset);
        }
        else
        {
            Params->ManufacturerName = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_MANUFACTURER_NAME, MessageSize, (uint8_t *)Params);

        if(ManufacturerName != NULL)
            memscpy(ManufacturerName, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->ManufacturerName, (strlen(Params->ManufacturerName) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Model_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber)
{
    DIS_Set_Model_Number_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(ModelNumber)
    {
        StringLength = (strlen(ModelNumber) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_MODEL_NUMBER_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_MODEL_NUMBER_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(ModelNumber != NULL)
        {
            Params->ModelNumber = (char *)(((uint8_t *)Params) + Offset);
            memscpy(Params->ModelNumber, StringLength, ModelNumber, StringLength);
        }
        else
        {
            Params->ModelNumber = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_MODEL_NUMBER, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Model_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber)
{
    DIS_Query_Model_Number_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_MODEL_NUMBER_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_MODEL_NUMBER_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(ModelNumber != NULL)
        {
            Params->ModelNumber = (char *)(((uint8_t *)Params) + Offset);
        }
        else
        {
            Params->ModelNumber = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_MODEL_NUMBER, MessageSize, (uint8_t *)Params);

        if(ModelNumber != NULL)
            memscpy(ModelNumber, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->ModelNumber, (strlen(Params->ModelNumber) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Serial_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber)
{
    DIS_Set_Serial_Number_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(SerialNumber)
    {
        StringLength = (strlen(SerialNumber) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_SERIAL_NUMBER_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_SERIAL_NUMBER_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SerialNumber != NULL)
        {
            Params->SerialNumber = (char *)(((uint8_t *)Params) + Offset);
            memscpy(Params->SerialNumber, StringLength, SerialNumber, StringLength);
        }
        else
        {
            Params->SerialNumber = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_SERIAL_NUMBER, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Serial_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber)
{
    DIS_Query_Serial_Number_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_SERIAL_NUMBER_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_SERIAL_NUMBER_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SerialNumber != NULL)
        {
            Params->SerialNumber = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
        }
        else
        {
            Params->SerialNumber = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_SERIAL_NUMBER, MessageSize, (uint8_t *)Params);

        if(SerialNumber != NULL)
            memscpy(SerialNumber, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->SerialNumber, (strlen(Params->SerialNumber) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Hardware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision)
{
    DIS_Set_Hardware_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(Hardware_Revision)
    {
        StringLength = (strlen(Hardware_Revision) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_HARDWARE_REVISION_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_HARDWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(Hardware_Revision != NULL)
        {
            Params->Hardware_Revision = (char *)(((uint8_t *)Params) + Offset);
            memscpy(Params->Hardware_Revision, StringLength, Hardware_Revision, StringLength);
        }
        else
        {
            Params->Hardware_Revision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_HARDWARE_REVISION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Hardware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision)
{
    DIS_Query_Hardware_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_HARDWARE_REVISION_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_HARDWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(Hardware_Revision != NULL)
        {
            Params->Hardware_Revision = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
        }
        else
        {
            Params->Hardware_Revision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_HARDWARE_REVISION, MessageSize, (uint8_t *)Params);

        if(Hardware_Revision != NULL)
            memscpy(Hardware_Revision, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->Hardware_Revision, (strlen(Params->Hardware_Revision) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Firmware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision)
{
    DIS_Set_Firmware_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(FirmwareRevision)
    {
        StringLength = (strlen(FirmwareRevision) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_FIRMWARE_REVISION_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_FIRMWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(FirmwareRevision != NULL)
        {
            Params->FirmwareRevision = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
            memscpy(Params->FirmwareRevision, StringLength, FirmwareRevision, StringLength);
        }
        else
        {
            Params->FirmwareRevision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_FIRMWARE_REVISION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Firmware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision)
{
    DIS_Query_Firmware_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_FIRMWARE_REVISION_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_FIRMWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(FirmwareRevision != NULL)
        {
            Params->FirmwareRevision = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
        }
        else
        {
            Params->FirmwareRevision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_FIRMWARE_REVISION, MessageSize, (uint8_t *)Params);

        if(FirmwareRevision != NULL)
            memscpy(FirmwareRevision, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->FirmwareRevision, (strlen(Params->FirmwareRevision) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Software_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision)
{
    DIS_Set_Software_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;
    uint32_t StringLength;

    if(SoftwareRevision)
    {
        StringLength = (strlen(SoftwareRevision) + 1);
    }
    else
    {
        StringLength = 0;
    }

    MessageSize = ALIGN32(DIS_SET_SOFTWARE_REVISION_PARAMS_SIZE) + StringLength;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_SET_SOFTWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SoftwareRevision != NULL)
        {
            Params->SoftwareRevision = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
            memscpy(Params->SoftwareRevision, StringLength, SoftwareRevision, StringLength);
        }
        else
        {
            Params->SoftwareRevision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_SET_SOFTWARE_REVISION, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Software_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision)
{
    DIS_Query_Software_Revision_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_SOFTWARE_REVISION_PARAMS_SIZE) + (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_SOFTWARE_REVISION_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(SoftwareRevision != NULL)
        {
            Params->SoftwareRevision = (char *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(char));
        }
        else
        {
            Params->SoftwareRevision = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_SOFTWARE_REVISION, MessageSize, (uint8_t *)Params);

        if(SoftwareRevision != NULL)
            memscpy(SoftwareRevision, (QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING + 1), Params->SoftwareRevision, (strlen(Params->SoftwareRevision) + 1));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_IEEE_Certification_Data(uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *IEEE_Certification_Data)
{
    DIS_Query_IEEE_Certification_Data_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(DIS_QUERY_IEEE_CERTIFICATION_DATA_PARAMS_SIZE) + QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING;

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(DIS_QUERY_IEEE_CERTIFICATION_DATA_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(IEEE_Certification_Data != NULL)
        {
            Params->IEEE_Certification_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->IEEE_Certification_Data = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_DISAPI, FUNCTION_ID_DIS_QUERY_IEEE_CERTIFICATION_DATA, MessageSize, (uint8_t *)Params);

        if(IEEE_Certification_Data != NULL)
            memscpy(IEEE_Certification_Data, QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING, Params->IEEE_Certification_Data, QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

