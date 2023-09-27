/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __L2CAPAPI_PARAMS_H__
#define __L2CAPAPI_PARAMS_H__

#include "qapi_ble_l2cap.h"
typedef struct _tagL2CA_Register_LE_PSM_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t LE_PSM;
    unsigned long CallbackParameter;
} L2CA_Register_LE_PSM_Params_t;

#define L2CA_REGISTER_LE_PSM_PARAMS_SIZE sizeof(L2CA_Register_LE_PSM_Params_t)

typedef struct _tagL2CA_Un_Register_LE_PSM_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t L2CAP_PSMID;
} L2CA_Un_Register_LE_PSM_Params_t;

#define L2CA_UN_REGISTER_LE_PSM_PARAMS_SIZE sizeof(L2CA_Un_Register_LE_PSM_Params_t)

typedef struct _tagL2CA_Register_Fixed_Channel_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t FixedChannel;
    void *ChannelParameters;
    unsigned long CallbackParameter;
} L2CA_Register_Fixed_Channel_Params_t;

#define L2CA_REGISTER_FIXED_CHANNEL_PARAMS_SIZE sizeof(L2CA_Register_Fixed_Channel_Params_t)

typedef struct _tagL2CA_Un_Register_Fixed_Channel_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t FCID;
} L2CA_Un_Register_Fixed_Channel_Params_t;

#define L2CA_UN_REGISTER_FIXED_CHANNEL_PARAMS_SIZE sizeof(L2CA_Un_Register_Fixed_Channel_Params_t)

typedef struct _tagL2CA_LE_Connect_Request_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t LE_PSM;
    qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters;
    unsigned long CallbackParameter;
} L2CA_LE_Connect_Request_Params_t;

#define L2CA_LE_CONNECT_REQUEST_PARAMS_SIZE sizeof(L2CA_LE_Connect_Request_Params_t)

typedef struct _tagL2CA_LE_Connect_Response_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint8_t Identifier;
    uint16_t LCID;
    uint16_t Result;
    qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters;
} L2CA_LE_Connect_Response_Params_t;

#define L2CA_LE_CONNECT_RESPONSE_PARAMS_SIZE sizeof(L2CA_LE_Connect_Response_Params_t)

typedef struct _tagL2CA_LE_Disconnect_Request_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t LCID;
} L2CA_LE_Disconnect_Request_Params_t;

#define L2CA_LE_DISCONNECT_REQUEST_PARAMS_SIZE sizeof(L2CA_LE_Disconnect_Request_Params_t)

typedef struct _tagL2CA_LE_Disconnect_Response_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t LCID;
} L2CA_LE_Disconnect_Response_Params_t;

#define L2CA_LE_DISCONNECT_RESPONSE_PARAMS_SIZE sizeof(L2CA_LE_Disconnect_Response_Params_t)

typedef struct _tagL2CA_Fixed_Channel_Data_Write_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t FCID;
    uint16_t Data_Length;
    uint8_t *Data;
} L2CA_Fixed_Channel_Data_Write_Params_t;

#define L2CA_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE sizeof(L2CA_Fixed_Channel_Data_Write_Params_t)

typedef struct _tagL2CA_Enhanced_Fixed_Channel_Data_Write_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t FCID;
    qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters;
    uint16_t Data_Length;
    uint8_t *Data;
} L2CA_Enhanced_Fixed_Channel_Data_Write_Params_t;

#define L2CA_ENHANCED_FIXED_CHANNEL_DATA_WRITE_PARAMS_SIZE sizeof(L2CA_Enhanced_Fixed_Channel_Data_Write_Params_t)

typedef struct _tagL2CA_Enhanced_Dynamic_Channel_Data_Write_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t LCID;
    qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters;
    uint16_t Data_Length;
    uint8_t *Data;
} L2CA_Enhanced_Dynamic_Channel_Data_Write_Params_t;

#define L2CA_ENHANCED_DYNAMIC_CHANNEL_DATA_WRITE_PARAMS_SIZE sizeof(L2CA_Enhanced_Dynamic_Channel_Data_Write_Params_t)

typedef struct _tagL2CA_LE_Flush_Channel_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t CID;
} L2CA_LE_Flush_Channel_Data_Params_t;

#define L2CA_LE_FLUSH_CHANNEL_DATA_PARAMS_SIZE sizeof(L2CA_LE_Flush_Channel_Data_Params_t)

typedef struct _tagL2CA_LE_Grant_Credits_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t CID;
    uint16_t CreditsToGrant;
} L2CA_LE_Grant_Credits_Params_t;

#define L2CA_LE_GRANT_CREDITS_PARAMS_SIZE sizeof(L2CA_LE_Grant_Credits_Params_t)

typedef struct _tagL2CA_Connection_Parameter_Update_Request_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t IntervalMin;
    uint16_t IntervalMax;
    uint16_t SlaveLatency;
    uint16_t TimeoutMultiplier;
} L2CA_Connection_Parameter_Update_Request_Params_t;

#define L2CA_CONNECTION_PARAMETER_UPDATE_REQUEST_PARAMS_SIZE sizeof(L2CA_Connection_Parameter_Update_Request_Params_t)

typedef struct _tagL2CA_Connection_Parameter_Update_Response_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BD_ADDR_t BD_ADDR;
    uint16_t Result;
} L2CA_Connection_Parameter_Update_Response_Params_t;

#define L2CA_CONNECTION_PARAMETER_UPDATE_RESPONSE_PARAMS_SIZE sizeof(L2CA_Connection_Parameter_Update_Response_Params_t)


#endif /* __L2CAPAPI_PARAMS_H__ */
