/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __BSCAPI_CB_M3_H__
#define __BSCAPI_CB_M3_H__

#include "callback.h"

void BSC_Timer_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

void BSC_Debug_Callback_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

void BSC_AsynchronousCallbackFunction_Handler(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);


#endif /* __BSCAPI_CB_M3_H__ */
