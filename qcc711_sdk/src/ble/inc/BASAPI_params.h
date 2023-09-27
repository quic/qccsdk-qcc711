/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __BASAPI_PARAMS_H__
#define __BASAPI_PARAMS_H__

#include "qapi_ble_bas.h"
typedef struct _tagBAS_Initialize_Service_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
    uint32_t *ServiceID;
} BAS_Initialize_Service_Params_t;

#define BAS_INITIALIZE_SERVICE_PARAMS_SIZE sizeof(BAS_Initialize_Service_Params_t)

typedef struct _tagBAS_Initialize_Service_Handle_Range_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
    uint32_t *ServiceID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange;
} BAS_Initialize_Service_Handle_Range_Params_t;

#define BAS_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE sizeof(BAS_Initialize_Service_Handle_Range_Params_t)

typedef struct _tagBAS_Cleanup_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
} BAS_Cleanup_Service_Params_t;

#define BAS_CLEANUP_SERVICE_PARAMS_SIZE sizeof(BAS_Cleanup_Service_Params_t)

typedef struct _tagBAS_Battery_Level_Read_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t BatteryLevel;
} BAS_Battery_Level_Read_Request_Response_Params_t;

#define BAS_BATTERY_LEVEL_READ_REQUEST_RESPONSE_PARAMS_SIZE sizeof(BAS_Battery_Level_Read_Request_Response_Params_t)

typedef struct _tagBAS_Battery_Level_Read_Request_Error_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} BAS_Battery_Level_Read_Request_Error_Response_Params_t;

#define BAS_BATTERY_LEVEL_READ_REQUEST_ERROR_RESPONSE_PARAMS_SIZE sizeof(BAS_Battery_Level_Read_Request_Error_Response_Params_t)

typedef struct _tagBAS_Query_Characteristic_Presentation_Format_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat;
} BAS_Query_Characteristic_Presentation_Format_Params_t;

#define BAS_QUERY_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE sizeof(BAS_Query_Characteristic_Presentation_Format_Params_t)

typedef struct _tagBAS_Set_Characteristic_Presentation_Format_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat;
} BAS_Set_Characteristic_Presentation_Format_Params_t;

#define BAS_SET_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE sizeof(BAS_Set_Characteristic_Presentation_Format_Params_t)

typedef struct _tagBAS_Read_Client_Configuration_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint16_t Client_Configuration;
} BAS_Read_Client_Configuration_Response_Params_t;

#define BAS_READ_CLIENT_CONFIGURATION_RESPONSE_PARAMS_SIZE sizeof(BAS_Read_Client_Configuration_Response_Params_t)

typedef struct _tagBAS_Notify_Battery_Level_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t ConnectionID;
    uint8_t BatteryLevel;
} BAS_Notify_Battery_Level_Params_t;

#define BAS_NOTIFY_BATTERY_LEVEL_PARAMS_SIZE sizeof(BAS_Notify_Battery_Level_Params_t)

typedef struct _tagBAS_Decode_Characteristic_Presentation_Format_Params_t
{
    uint32_t ValueLength;
    uint8_t *Value;
    qapi_BLE_BAS_Presentation_Format_Data_t *CharacteristicPresentationFormat;
} BAS_Decode_Characteristic_Presentation_Format_Params_t;

#define BAS_DECODE_CHARACTERISTIC_PRESENTATION_FORMAT_PARAMS_SIZE sizeof(BAS_Decode_Characteristic_Presentation_Format_Params_t)


#endif /* __BASAPI_PARAMS_H__ */
