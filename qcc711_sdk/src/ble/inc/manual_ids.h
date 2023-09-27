/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __MANUAL_IDS_H__
#define __MANUAL_IDS_H__

/* Manually create File IDs for non-autogen IPC communication. */
#define FILE_ID_RADIO 0x8000

#define FUNCTION_ID_RADIO_REGISTER_BROWNOUT_CALLBACK    0
#define FUNCTION_ID_RADIO_UN_REGISTER_BROWNOUT_CALLBACK 1
#define FUNCTION_ID_RADIO_SUSPEND                       2
#define FUNCTION_ID_RADIO_RESUME                        3
#define FUNCTION_ID_RADIO_SET_MAX_TX_POWER              4

#define CALLBACK_ID_RADIO_BROWNOUT                      0

#endif /* __MANUAL_IDS_H__ */
