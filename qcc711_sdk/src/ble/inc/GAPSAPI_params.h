/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GAPSAPI_PARAMS_H__
#define __GAPSAPI_PARAMS_H__

#include "qapi_ble_gaps.h"
typedef struct _tagGAPS_Initialize_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *ServiceID;
} GAPS_Initialize_Service_Params_t;

#define GAPS_INITIALIZE_SERVICE_PARAMS_SIZE sizeof(GAPS_Initialize_Service_Params_t)

typedef struct _tagGAPS_Initialize_Service_Handle_Range_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t *ServiceID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange;
} GAPS_Initialize_Service_Handle_Range_Params_t;

#define GAPS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE sizeof(GAPS_Initialize_Service_Handle_Range_Params_t)

typedef struct _tagGAPS_Cleanup_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
} GAPS_Cleanup_Service_Params_t;

#define GAPS_CLEANUP_SERVICE_PARAMS_SIZE sizeof(GAPS_Cleanup_Service_Params_t)

typedef struct _tagGAPS_Set_Device_Name_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *DeviceName;
} GAPS_Set_Device_Name_Params_t;

#define GAPS_SET_DEVICE_NAME_PARAMS_SIZE sizeof(GAPS_Set_Device_Name_Params_t)

typedef struct _tagGAPS_Query_Device_Name_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    char *NameBuffer;
} GAPS_Query_Device_Name_Params_t;

#define GAPS_QUERY_DEVICE_NAME_PARAMS_SIZE sizeof(GAPS_Query_Device_Name_Params_t)

typedef struct _tagGAPS_Set_Device_Appearance_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint16_t DeviceAppearance;
} GAPS_Set_Device_Appearance_Params_t;

#define GAPS_SET_DEVICE_APPEARANCE_PARAMS_SIZE sizeof(GAPS_Set_Device_Appearance_Params_t)

typedef struct _tagGAPS_Query_Device_Appearance_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint16_t *DeviceAppearance;
} GAPS_Query_Device_Appearance_Params_t;

#define GAPS_QUERY_DEVICE_APPEARANCE_PARAMS_SIZE sizeof(GAPS_Query_Device_Appearance_Params_t)

typedef struct _tagGAPS_Set_Preferred_Connection_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters;
} GAPS_Set_Preferred_Connection_Parameters_Params_t;

#define GAPS_SET_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE sizeof(GAPS_Set_Preferred_Connection_Parameters_Params_t)

typedef struct _tagGAPS_Query_Preferred_Connection_Parameters_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters;
} GAPS_Query_Preferred_Connection_Parameters_Params_t;

#define GAPS_QUERY_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE sizeof(GAPS_Query_Preferred_Connection_Parameters_Params_t)

typedef struct _tagGAPS_Set_Central_Address_Resolution_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_GAP_Central_Address_Resolution_t CentralAddressResolution;
} GAPS_Set_Central_Address_Resolution_Params_t;

#define GAPS_SET_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE sizeof(GAPS_Set_Central_Address_Resolution_Params_t)

typedef struct _tagGAPS_Query_Central_Address_Resolution_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution;
} GAPS_Query_Central_Address_Resolution_Params_t;

#define GAPS_QUERY_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE sizeof(GAPS_Query_Central_Address_Resolution_Params_t)

typedef struct _tagGAPS_Decode_Preferred_Connection_Parameters_Params_t
{
    uint32_t ValueLength;
    uint8_t *Value;
    qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters;
} GAPS_Decode_Preferred_Connection_Parameters_Params_t;

#define GAPS_DECODE_PREFERRED_CONNECTION_PARAMETERS_PARAMS_SIZE sizeof(GAPS_Decode_Preferred_Connection_Parameters_Params_t)

typedef struct _tagGAPS_Decode_Central_Address_Resolution_Params_t
{
    uint32_t ValueLength;
    uint8_t *Value;
    qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution;
} GAPS_Decode_Central_Address_Resolution_Params_t;

#define GAPS_DECODE_CENTRAL_ADDRESS_RESOLUTION_PARAMS_SIZE sizeof(GAPS_Decode_Central_Address_Resolution_Params_t)


#endif /* __GAPSAPI_PARAMS_H__ */
