/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

#ifndef TME_IPC_ACCESS_CONTROL_COMMON_H
#define TME_IPC_ACCESS_CONTROL_COMMON_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validate QAPI parameters and create corresponding NVM register access IPC message.

   @param[in]      QapiParams       QAPI NVM access parameters.
   @param[in, out] TMEIPCMsg        TME NVM access IPC message.
   @param[in, out] TMEIPCMsgLength  TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_NVM_Register_Access_IPC_Msg(void     *QapiParams,
                                                              void    **TmeIPCMsg,
                                                              uint32_t *TmeIPCMsgLength);

/**
   @brief Validate NVM register access IPC message response.

   @param[in] QapiParams  QAPI NVM access parameters.
   @param[in] TMEIPCMsg   TME NVM access IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    QAPI callback function.
   @param[in] UserData    Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_NVM_Register_Access_IPC_Msg_Response(void          *QapiParams,
                                                           void          *TMEIPCMsg,
                                                           qapi_Status_t  Status,
                                                           void          *Callback,
                                                           void          *UserData);

#endif //TME_IPC_ACCESS_CONTROL_COMMON_H