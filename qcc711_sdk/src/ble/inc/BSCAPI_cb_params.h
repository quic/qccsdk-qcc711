/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __BSCAPI_CB_PARAMS_H__
#define __BSCAPI_CB_PARAMS_H__

#include "qapi_ble_bsc.h"

typedef struct _tagBSC_Timer_Callback_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t TimerID;
    unsigned long CallbackParameter;
} BSC_Timer_Callback_Params_t;

#define BSC_TIMER_CALLBACK_PARAMS_SIZE sizeof(BSC_Timer_Callback_Params_t)

typedef struct _tagBSC_Debug_Callback_Params_t
{
    uint32_t BluetoothStackID;
    boolean_t PacketSent;
    qapi_BLE_HCI_Packet_t *HCIPacket;
    unsigned long CallbackParameter;
} BSC_Debug_Callback_Params_t;

#define BSC_DEBUG_CALLBACK_PARAMS_SIZE sizeof(BSC_Debug_Callback_Params_t)

typedef struct _tagBSC_AsynchronousCallbackFunction_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} BSC_AsynchronousCallbackFunction_Params_t;

#define BSC_ASYNCHRONOUSCALLBACKFUNCTION_PARAMS_SIZE sizeof(BSC_AsynchronousCallbackFunction_Params_t)


#endif /* __BSCAPI_CB_PARAMS_H__ */
