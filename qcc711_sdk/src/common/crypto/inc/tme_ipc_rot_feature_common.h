/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

#ifndef TME_IPC_ROT_FEATURE_COMMON_H
#define TME_IPC_ROT_FEATURE_COMMON_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validate QAPI parameters and create corresponding patch version IPC message.

   @param[in]      QapiGetPatchVersionParams  qapi get RoT patch version parameters.
   @param[in, out] TMEIPCMsg                  TME patch version IPC message.
   @param[in, out] TMEIPCMsgLength            TME patch version IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Patch_Version_IPC_Msg(void *QapiGetPatchVersionParams,
                                                        void **TmeIPCMsg,
                                                        uint32_t *TmeIPCMsgLength);

/**
   @brief Process Patch_Version IPC message response. 
          Create event data for non-blocking call.
 
   @param[in] QapiGetPatchVersionParams  qapi get patch version parameters.
   @param[in] TMEIPCMsg                  TME patch version IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.   

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Patch_Version_IPC_Msg_Response(void *QapiGetPatchVersionParams,
                                                     void *TMEIPCMsg,
                                                     qapi_Status_t Status,
                                                     void *CallBack,
                                                     void *UserData);

#endif //TME_IPC_ROT_FEATURE_COMMON_H