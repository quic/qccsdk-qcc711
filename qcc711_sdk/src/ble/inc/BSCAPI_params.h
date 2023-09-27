/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __BSCAPI_PARAMS_H__
#define __BSCAPI_PARAMS_H__

#include "qapi_ble_bsc.h"
typedef struct _tagBSC_Initialize_Params_t
{
    qapi_BLE_HCI_DriverInformation_t *HCI_DriverInformation;
    unsigned long Flags;
} BSC_Initialize_Params_t;

#define BSC_INITIALIZE_PARAMS_SIZE sizeof(BSC_Initialize_Params_t)

typedef struct _tagBSC_Shutdown_Params_t
{
    uint32_t BluetoothStackID;
} BSC_Shutdown_Params_t;

#define BSC_SHUTDOWN_PARAMS_SIZE sizeof(BSC_Shutdown_Params_t)

typedef struct _tagBSC_RegisterDebugCallback_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} BSC_RegisterDebugCallback_Params_t;

#define BSC_REGISTERDEBUGCALLBACK_PARAMS_SIZE sizeof(BSC_RegisterDebugCallback_Params_t)

typedef struct _tagBSC_UnRegisterDebugCallback_Params_t
{
    uint32_t BluetoothStackID;
} BSC_UnRegisterDebugCallback_Params_t;

#define BSC_UNREGISTERDEBUGCALLBACK_PARAMS_SIZE sizeof(BSC_UnRegisterDebugCallback_Params_t)

typedef struct _tagBSC_QueryStatistics_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BSC_Statistics_t *Statistics;
} BSC_QueryStatistics_Params_t;

#define BSC_QUERYSTATISTICS_PARAMS_SIZE sizeof(BSC_QueryStatistics_Params_t)

typedef struct _tagBSC_ClearStatistics_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t Flags;
} BSC_ClearStatistics_Params_t;

#define BSC_CLEARSTATISTICS_PARAMS_SIZE sizeof(BSC_ClearStatistics_Params_t)

#endif /* __BSCAPI_PARAMS_H__ */
