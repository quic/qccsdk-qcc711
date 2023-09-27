/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __HCIAPI_CB_M3_H__
#define __HCIAPI_CB_M3_H__

#include "callback.h"

void HCI_Event_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

void HCI_ACL_Data_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);


#endif /* __HCIAPI_CB_M3_H__ */
