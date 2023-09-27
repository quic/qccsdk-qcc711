/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_ipc_crypto.h
 * @brief The utility functions related to crypto module.
 */
#ifndef TME_IPC_CRYPTO_H
#define TME_IPC_CRYPTO_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validate QAPI parameters and create corresponding digest IPC message.

   @param[in]      QapiParams       qapi digest parameters.
   @param[in, out] TMEIPCMsg        TME digest IPC message.
   @param[in, out] TMEIPCMsgLength  TME digest IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Digest_IPC_Msg(void *QapiParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength);

/**
   @brief Validate digest IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiParams  qapi digest parameters.
   @param[in] TMEIPCMsg   TME digest IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    qapi callback function.
   @param[in] UserData    Placeholder for user data. 

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Digest_IPC_Msg_Response(void *QapiParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *Callback,
                                              void *Userdata);

/**
   @brief Validate QAPI parameters and create corresponding get random IPC message.

   @param[in]      QapiGetRandomParams   qapi get random parameters.
   @param[in, out] TMEIPCMsg             TME get random IPC message.
   @param[in, out] TMEIPCMsgLength       TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Get_Random_IPC_Msg(void *QapiGetRandomParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength);

/**
   @brief Process get random IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiGetRandomParams qapi get random  parameters.
   @param[in] TMEIPCMsg           TME ger random IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data.     

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                

*/
qapi_Status_t Process_Get_Random_IPC_Msg_Response(void *QapiGetRandomParams,
                                                  void *TMEIPCMsg, 
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData);

// clang-format on
#endif /* TME_IPC_CRYPTO_H */
