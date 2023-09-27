/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __CTESAPI_CB_PARAMS_H__
#define __CTESAPI_CB_PARAMS_H__

#include "qapi_ble_ctes.h"

typedef struct _tagCTES_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_CTES_Event_Data_t *CTES_Event_Data;
    unsigned long CallbackParameter;
} CTES_Event_Callback_Params_t;

#define CTES_EVENT_CALLBACK_PARAMS_SIZE sizeof(CTES_Event_Callback_Params_t)


#endif /* __CTESAPI_CB_PARAMS_H__ */
