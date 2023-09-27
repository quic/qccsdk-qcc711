/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

#ifndef TME_IPC_FWUP_COMMON_H
#define TME_IPC_FWUP_COMMON_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validate QAPI parameters and create corresponding apply firmware update IPC message.

   @param[in]      QapiParams       QAPI apply firmware update parameters.
   @param[in, out] TMEIPCMsg        TME apply firmware update IPC message.
   @param[in, out] TMEIPCMsgLength  TME apply firmware update IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Firmware_Update_Apply_IPC_Msg(void *QapiParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength);

/**
   @brief Validate apply firmware update IPC message response. Create event data for non-blocking call.

   @param[in] QapiParams  QAPI apply firmware update parameters.
   @param[in] TMEIPCMsg   TME apply firmware update IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    qapi callback function.
   @param[in] UserData    Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Firmware_Update_Apply_IPC_Msg_Response(void *QapiParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *Callback,
                                              void *Userdata);


/**
   @brief Validate QAPI parameters and create corresponding verify firmware update IPC message.

   @param[in]      QapiParams       QAPI verify firmware update parameters.
   @param[in, out] TMEIPCMsg        TME verify firmware update IPC message.
   @param[in, out] TMEIPCMsgLength  TME verify firmware update IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Firmware_Update_Verify_IPC_Msg(void *QapiParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength);

/**
   @brief Validate verify firmware update IPC message response. Create event data for non-blocking call.

   @param[in] QapiParams  QAPI verify firmware update parameters.
   @param[in] TMEIPCMsg   TME verify firmware update IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    qapi callback function.
   @param[in] UserData    Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Firmware_Update_Verify_IPC_Msg_Response(void *QapiParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *Callback,
                                              void *Userdata);

#endif //TME_IPC_FWUP_COMMON_H