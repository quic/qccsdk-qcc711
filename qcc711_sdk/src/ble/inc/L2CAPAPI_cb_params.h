/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __L2CAPAPI_CB_PARAMS_H__
#define __L2CAPAPI_CB_PARAMS_H__

#include "qapi_ble_l2cap.h"

typedef struct _tagL2CA_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_L2CA_Event_Data_t *L2CA_Event_Data;
    unsigned long CallbackParameter;
} L2CA_Event_Callback_Params_t;

#define L2CA_EVENT_CALLBACK_PARAMS_SIZE sizeof(L2CA_Event_Callback_Params_t)


#endif /* __L2CAPAPI_CB_PARAMS_H__ */
