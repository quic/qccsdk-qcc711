/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GATTAPI_CB_PARAMS_H__
#define __GATTAPI_CB_PARAMS_H__

#include "qapi_ble_gatt.h"

typedef struct _tagGATT_Connection_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Connection_Event_Data_t *GATT_Connection_Event_Data;
    unsigned long CallbackParameter;
} GATT_Connection_Event_Callback_Params_t;

#define GATT_CONNECTION_EVENT_CALLBACK_PARAMS_SIZE sizeof(GATT_Connection_Event_Callback_Params_t)

typedef struct _tagGATT_Server_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Server_Event_Data_t *GATT_Server_Event_Data;
    unsigned long CallbackParameter;
} GATT_Server_Event_Callback_Params_t;

#define GATT_SERVER_EVENT_CALLBACK_PARAMS_SIZE sizeof(GATT_Server_Event_Callback_Params_t)

typedef struct _tagGATT_Client_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data;
    unsigned long CallbackParameter;
} GATT_Client_Event_Callback_Params_t;

#define GATT_CLIENT_EVENT_CALLBACK_PARAMS_SIZE sizeof(GATT_Client_Event_Callback_Params_t)

typedef struct _tagGATT_Service_Discovery_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data;
    unsigned long CallbackParameter;
} GATT_Service_Discovery_Event_Callback_Params_t;

#define GATT_SERVICE_DISCOVERY_EVENT_CALLBACK_PARAMS_SIZE sizeof(GATT_Service_Discovery_Event_Callback_Params_t)


#endif /* __GATTAPI_CB_PARAMS_H__ */
