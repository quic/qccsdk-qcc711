/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __HCIAPI_CB_PARAMS_H__
#define __HCIAPI_CB_PARAMS_H__

#include "qapi_ble_hci.h"

typedef struct _tagHCI_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_HCI_Event_Data_t *HCI_Event_Data;
    unsigned long CallbackParameter;
} HCI_Event_Callback_Params_t;

#define HCI_EVENT_CALLBACK_PARAMS_SIZE sizeof(HCI_Event_Callback_Params_t)

typedef struct _tagHCI_ACL_Data_Callback_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t Connection_Handle;
    uint16_t Flags;
    uint16_t ACLDataLength;
    uint8_t *ACLData;
    unsigned long CallbackParameter;
} HCI_ACL_Data_Callback_Params_t;

#define HCI_ACL_DATA_CALLBACK_PARAMS_SIZE sizeof(HCI_ACL_Data_Callback_Params_t)


#endif /* __HCIAPI_CB_PARAMS_H__ */
