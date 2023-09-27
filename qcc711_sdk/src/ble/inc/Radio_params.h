/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __RADIO_PARAMS_H__
#define __RADIO_PARAMS_H__

#include <stdint.h>

typedef struct Radio_Register_Brownout_Callback_Params_s
{
    uint32_t BluetoothStackID;
} Radio_Register_Brownout_Callback_Params_t;

#define RADIO_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE    (sizeof(Radio_Register_Brownout_Callback_Params_t))

typedef struct Radio_Un_Register_Brownout_Callback_Params_s
{
    uint32_t BluetoothStackID;
} Radio_Un_Register_Brownout_Callback_Params_t;

#define RADIO_UN_REGISTER_BROWNOUT_CALLBACK_PARAMS_SIZE (sizeof(Radio_Un_Register_Brownout_Callback_Params_t))

typedef struct Radio_Suspend_Params_s
{
    uint32_t BluetoothStackID;
} Radio_Suspend_Params_t;

#define RADIO_SUSPEND_PARAMS_SIZE (sizeof(Radio_Suspend_Params_t))

typedef struct Radio_Resume_Params_s
{
    uint32_t BluetoothStackID;
} Radio_Resume_Params_t;

#define RADIO_RESUME_PARAMS_SIZE (sizeof(Radio_Resume_Params_t))

typedef struct Radio_Set_Max_Tx_Power_Params_s
{
    uint32_t BluetoothStackID;
    int8_t dBm;
} Radio_Set_Max_Tx_Power_Params_t;

#define RADIO_SET_MAX_TX_POWER_PARAMS_SIZE (sizeof(Radio_Set_Max_Tx_Power_Params_t))

typedef struct Radio_Brownout_Callback_Params_s
{
    int8_t dBm;
} Radio_Brownout_Callback_Params_t;

#define RADIO_BROWNOUT_CALLBACK_PARAMS_SIZE (sizeof(Radio_Brownout_Callback_Params_t))

#endif /* __RADIO_PARAMS_H__ */
