/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
// QAPI headers
#include "qapi_status.h"
#include "qapi_heap.h"

 // TME utility headers
#include "tme_types.h"
#include "tme_ipc_utils.h"

// TME interface headers
#include "tme_access_control_interface.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

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
                                                              uint32_t *TmeIPCMsgLength)
{
    if (TmeIPCMsgLength == NULL || QapiParams == NULL ||
        TmeIPCMsg == NULL)
    {
      return QAPI_ERR_INVALID_PARAM;
    }

    *TmeIPCMsgLength = sizeof(TMENVMRegisterAccessMessage);
    *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
    if (*TmeIPCMsg == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    TMENVMRegisterAccessMessage *AccessIPCMsg = (TMENVMRegisterAccessMessage*)(*TmeIPCMsg);
    AccessIPCMsg->input.provideAccess = *(qbool_t *)QapiParams;
    return QAPI_OK;
}

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
                                                           void          *UserData)
{
    TMENVMRegisterAccessMessage *AccessIPCMsg = (TMENVMRegisterAccessMessage*)(TMEIPCMsg);
    if(Status == QAPI_OK)
    {
        Status = qapi_Convert_Tme_Status(AccessIPCMsg->output.status);
    }
    return Status;
}
