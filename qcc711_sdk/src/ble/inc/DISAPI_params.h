/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __DISAPI_PARAMS_H__
#define __DISAPI_PARAMS_H__

#include "qapi_ble_dis.h"
typedef struct _tagDIS_Initialize_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *ServiceID;
} DIS_Initialize_Service_Params_t;

#define DIS_INITIALIZE_SERVICE_PARAMS_SIZE sizeof(DIS_Initialize_Service_Params_t)

typedef struct _tagDIS_Initialize_Service_Handle_Range_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *ServiceID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange;
} DIS_Initialize_Service_Handle_Range_Params_t;

#define DIS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE sizeof(DIS_Initialize_Service_Handle_Range_Params_t)

typedef struct _tagDIS_Cleanup_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
} DIS_Cleanup_Service_Params_t;

#define DIS_CLEANUP_SERVICE_PARAMS_SIZE sizeof(DIS_Cleanup_Service_Params_t)

typedef struct _tagDIS_Set_Manufacturer_Name_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *ManufacturerName;
} DIS_Set_Manufacturer_Name_Params_t;

#define DIS_SET_MANUFACTURER_NAME_PARAMS_SIZE sizeof(DIS_Set_Manufacturer_Name_Params_t)

typedef struct _tagDIS_Query_Manufacturer_Name_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *ManufacturerName;
} DIS_Query_Manufacturer_Name_Params_t;

#define DIS_QUERY_MANUFACTURER_NAME_PARAMS_SIZE sizeof(DIS_Query_Manufacturer_Name_Params_t)

typedef struct _tagDIS_Set_Model_Number_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *ModelNumber;
} DIS_Set_Model_Number_Params_t;

#define DIS_SET_MODEL_NUMBER_PARAMS_SIZE sizeof(DIS_Set_Model_Number_Params_t)

typedef struct _tagDIS_Query_Model_Number_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *ModelNumber;
} DIS_Query_Model_Number_Params_t;

#define DIS_QUERY_MODEL_NUMBER_PARAMS_SIZE sizeof(DIS_Query_Model_Number_Params_t)

typedef struct _tagDIS_Set_Serial_Number_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *SerialNumber;
} DIS_Set_Serial_Number_Params_t;

#define DIS_SET_SERIAL_NUMBER_PARAMS_SIZE sizeof(DIS_Set_Serial_Number_Params_t)

typedef struct _tagDIS_Query_Serial_Number_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *SerialNumber;
} DIS_Query_Serial_Number_Params_t;

#define DIS_QUERY_SERIAL_NUMBER_PARAMS_SIZE sizeof(DIS_Query_Serial_Number_Params_t)

typedef struct _tagDIS_Set_Hardware_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *Hardware_Revision;
} DIS_Set_Hardware_Revision_Params_t;

#define DIS_SET_HARDWARE_REVISION_PARAMS_SIZE sizeof(DIS_Set_Hardware_Revision_Params_t)

typedef struct _tagDIS_Query_Hardware_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *Hardware_Revision;
} DIS_Query_Hardware_Revision_Params_t;

#define DIS_QUERY_HARDWARE_REVISION_PARAMS_SIZE sizeof(DIS_Query_Hardware_Revision_Params_t)

typedef struct _tagDIS_Set_Firmware_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *FirmwareRevision;
} DIS_Set_Firmware_Revision_Params_t;

#define DIS_SET_FIRMWARE_REVISION_PARAMS_SIZE sizeof(DIS_Set_Firmware_Revision_Params_t)

typedef struct _tagDIS_Query_Firmware_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *FirmwareRevision;
} DIS_Query_Firmware_Revision_Params_t;

#define DIS_QUERY_FIRMWARE_REVISION_PARAMS_SIZE sizeof(DIS_Query_Firmware_Revision_Params_t)

typedef struct _tagDIS_Set_Software_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *SoftwareRevision;
} DIS_Set_Software_Revision_Params_t;

#define DIS_SET_SOFTWARE_REVISION_PARAMS_SIZE sizeof(DIS_Set_Software_Revision_Params_t)

typedef struct _tagDIS_Query_Software_Revision_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *SoftwareRevision;
} DIS_Query_Software_Revision_Params_t;

#define DIS_QUERY_SOFTWARE_REVISION_PARAMS_SIZE sizeof(DIS_Query_Software_Revision_Params_t)

typedef struct _tagDIS_Set_System_ID_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_DIS_System_ID_Value_t *SystemID;
} DIS_Set_System_ID_Params_t;

#define DIS_SET_SYSTEM_ID_PARAMS_SIZE sizeof(DIS_Set_System_ID_Params_t)

typedef struct _tagDIS_Query_System_ID_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_DIS_System_ID_Value_t *SystemID;
} DIS_Query_System_ID_Params_t;

#define DIS_QUERY_SYSTEM_ID_PARAMS_SIZE sizeof(DIS_Query_System_ID_Params_t)

typedef struct _tagDIS_Set_IEEE_Certification_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t Length;
    uint8_t *IEEE_Certification_Data;
} DIS_Set_IEEE_Certification_Data_Params_t;

#define DIS_SET_IEEE_CERTIFICATION_DATA_PARAMS_SIZE sizeof(DIS_Set_IEEE_Certification_Data_Params_t)

typedef struct _tagDIS_Query_IEEE_Certification_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint8_t *IEEE_Certification_Data;
} DIS_Query_IEEE_Certification_Data_Params_t;

#define DIS_QUERY_IEEE_CERTIFICATION_DATA_PARAMS_SIZE sizeof(DIS_Query_IEEE_Certification_Data_Params_t)

typedef struct _tagDIS_Set_PNP_ID_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data;
} DIS_Set_PNP_ID_Params_t;

#define DIS_SET_PNP_ID_PARAMS_SIZE sizeof(DIS_Set_PNP_ID_Params_t)

typedef struct _tagDIS_Query_PNP_ID_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data;
} DIS_Query_PNP_ID_Params_t;

#define DIS_QUERY_PNP_ID_PARAMS_SIZE sizeof(DIS_Query_PNP_ID_Params_t)

typedef struct _tagDIS_Decode_PNP_ID_Params_t
{
    uint32_t ValueLength;
    uint8_t *Value;
    qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data;
} DIS_Decode_PNP_ID_Params_t;

#define DIS_DECODE_PNP_ID_PARAMS_SIZE sizeof(DIS_Decode_PNP_ID_Params_t)


#endif /* __DISAPI_PARAMS_H__ */
