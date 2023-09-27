/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __GAPAPI_CB_PARAMS_H__
#define __GAPAPI_CB_PARAMS_H__

#include "qapi_ble_gap.h"

typedef struct _tagGAP_LE_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_GAP_LE_Event_Data_t *GAP_LE_Event_Data;
    unsigned long CallbackParameter;
} GAP_LE_Event_Callback_Params_t;

#define GAP_LE_EVENT_CALLBACK_PARAMS_SIZE sizeof(GAP_LE_Event_Callback_Params_t)


#endif /* __GAPAPI_CB_PARAMS_H__ */
