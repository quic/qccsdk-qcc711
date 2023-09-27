/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __BASAPI_CB_PARAMS_H__
#define __BASAPI_CB_PARAMS_H__

#include "qapi_ble_bas.h"

typedef struct _tagBAS_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_BAS_Event_Data_t *BAS_Event_Data;
    unsigned long CallbackParameter;
} BAS_Event_Callback_Params_t;

#define BAS_EVENT_CALLBACK_PARAMS_SIZE sizeof(BAS_Event_Callback_Params_t)


#endif /* __BASAPI_CB_PARAMS_H__ */
