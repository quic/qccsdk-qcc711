/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __CTESAPI_PARAMS_H__
#define __CTESAPI_PARAMS_H__

#include "qapi_ble_ctes.h"
typedef struct _tagCTES_Initialize_Service_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
    uint32_t *ServiceID;
} CTES_Initialize_Service_Params_t;

#define CTES_INITIALIZE_SERVICE_PARAMS_SIZE sizeof(CTES_Initialize_Service_Params_t)

typedef struct _tagCTES_Initialize_Service_Handle_Range_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
    uint32_t *ServiceID;
    qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange;
} CTES_Initialize_Service_Handle_Range_Params_t;

#define CTES_INITIALIZE_SERVICE_HANDLE_RANGE_PARAMS_SIZE sizeof(CTES_Initialize_Service_Handle_Range_Params_t)

typedef struct _tagCTES_Cleanup_Service_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
} CTES_Cleanup_Service_Params_t;

#define CTES_CLEANUP_SERVICE_PARAMS_SIZE sizeof(CTES_Cleanup_Service_Params_t)

typedef struct _tagCTES_Write_CTE_Enable_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_CTE_Enable_Request_Response_Params_t;

#define CTES_WRITE_CTE_ENABLE_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_CTE_Enable_Request_Response_Params_t)

typedef struct _tagCTES_Write_CTE_Minimum_Length_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_CTE_Minimum_Length_Request_Response_Params_t;

#define CTES_WRITE_CTE_MINIMUM_LENGTH_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_CTE_Minimum_Length_Request_Response_Params_t)

typedef struct _tagCTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response_Params_t;

#define CTES_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response_Params_t)

typedef struct _tagCTES_Write_Advertising_CTE_Transmit_Duration_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_Advertising_CTE_Transmit_Duration_Request_Response_Params_t;

#define CTES_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_Advertising_CTE_Transmit_Duration_Request_Response_Params_t)

typedef struct _tagCTES_Write_Advertising_CTE_Interval_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_Advertising_CTE_Interval_Request_Response_Params_t;

#define CTES_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_Advertising_CTE_Interval_Request_Response_Params_t)

typedef struct _tagCTES_Write_Advertising_CTE_PHY_Request_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t InstanceID;
    uint32_t TransactionID;
    uint8_t ErrorCode;
} CTES_Write_Advertising_CTE_PHY_Request_Response_Params_t;

#define CTES_WRITE_ADVERTISING_CTE_PHY_REQUEST_RESPONSE_PARAMS_SIZE sizeof(CTES_Write_Advertising_CTE_PHY_Request_Response_Params_t)


#endif /* __CTESAPI_PARAMS_H__ */
