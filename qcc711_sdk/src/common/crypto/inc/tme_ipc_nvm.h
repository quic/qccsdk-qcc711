/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

#ifndef TME_IPC_NVM_H__
#define TME_IPC_NVM_H__

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validate QAPI parameters and create corresponding NVM write-ex IPC message.

   @param[in]      QapiParams       QAPI NVM write-ex parameters.
   @param[in, out] TMEIPCMsg        TME NVM write-ex IPC message.
   @param[in, out] TMEIPCMsgLength  TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_NVM_Write_Ex_IPC_Msg(void     *QapiParams,
                                                       void    **TmeIPCMsg,
                                                       uint32_t *TmeIPCMsgLength);

/**
   @brief Validate NVM write ex IPC message response.

   @param[in] QapiParams  QAPI NVM write-ex parameters.
   @param[in] TMEIPCMsg   TME NVM write-ex IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    QAPI callback function.
   @param[in] UserData    Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_NVM_Write_Ex_IPC_Msg_Response(void          *QapiParams,
                                                    void          *TMEIPCMsg,
                                                    qapi_Status_t  Status,
                                                    void          *Callback,
                                                    void          *UserData);

/**
   @brief Validate QAPI parameters and create corresponding NVM read-ex IPC message.

   @param[in]      QapiParams       QAPI NVM read-ex parameters.
   @param[in, out] TMEIPCMsg        TME NVM read-ex IPC message.
   @param[in, out] TMEIPCMsgLength  TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_NVM_Read_Ex_IPC_Msg(void     *QapiParams,
                                                      void    **TmeIPCMsg,
                                                      uint32_t *TmeIPCMsgLength);

/**
   @brief Validate NVM read-ex IPC message response.

   @param[in] QapiParams  QAPI NVM read-ex parameters.
   @param[in] TMEIPCMsg   TME NVM read-ex IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    QAPI callback function.
   @param[in] UserData    Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_NVM_Read_Ex_IPC_Msg_Response(void          *QapiParams,
                                                   void          *TMEIPCMsg,
                                                   qapi_Status_t  Status,
                                                   void          *Callback,
                                                   void          *UserData);
#endif //TME_IPC_NVM_H__