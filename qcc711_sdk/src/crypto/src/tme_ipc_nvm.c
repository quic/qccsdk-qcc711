/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
// QAPI headers
#include "qapi_status.h"
#include "qapi_heap.h"
#include "qapi_nvm_rot.h"

// TME utility headers
#include "tme_types.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_callback_utils.h"
#include "tme_ipc_nvm_common.h"

// TME interface headers
#include "tme_nvm_interface.h"

/**
   @brief Verifies if the given NVM offset is valid for a NVM read/write
          operation.

   @param[in] Offset   Start offset for the NVM read/write operation.
   @param[in] Length   Number of bytes to be read/written.

   @return true if the offset is valid or false if it is not.
*/
static qbool_t NVM_VerifyOffset(uint32_t Offset, uint32_t Length)
{
   qbool_t RetVal;

   /* Verify offset range and length. */
   if ((Offset >= 0) &&
       ((Offset + Length) <= QAPI_NVM_ROT_SIZE))
   {
      /* Valid values. */
      RetVal = true;
   }
   else
   {
      /* Invalid Offset and/or length. */
      RetVal = false;
   }
   return (RetVal);
}

/**
   @brief Validate QAPI parameters and create corresponding NVM write-ex IPC message.

   @param[in]      QapiParams       QAPI NVM write-ex parameters.
   @param[in, out] TMEIPCMsg        TME NVM write-ex IPC mesaage.
   @param[in, out] TMEIPCMsgLength  TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_NVM_Write_Ex_IPC_Msg(void     *QapiParams,
                                                       void    **TmeIPCMsg,
                                                       uint32_t *TmeIPCMsgLength)
{
    qapi_NVM_Write_Rot_Params_t *NVMWriteExParams =
                            (qapi_NVM_Write_Rot_Params_t *)QapiParams;
    if (NVMWriteExParams == NULL || NVMWriteExParams->Buffer == NULL ||
        NVMWriteExParams->BufferLen == 0)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (!NVM_VerifyOffset(NVMWriteExParams->Offset, NVMWriteExParams->BufferLen))
    {
        return QAPI_ERR_BOUNDS;
    }

    *TmeIPCMsgLength = sizeof(TMENVMWriteExMessage);
    *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength); 
    if (*TmeIPCMsg == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    TMENVMWriteExMessage *NVMWriteExIPCMsg = (TMENVMWriteExMessage *)(*TmeIPCMsg);
    NVMWriteExIPCMsg->input.offset = NVMWriteExParams->Offset;
    NVMWriteExIPCMsg->input.input.pData    = (UINT8 *)NVMWriteExParams->Buffer;
    NVMWriteExIPCMsg->input.input.length   = NVMWriteExParams->BufferLen;
    return QAPI_OK;
}

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
                                                    void          *UserData)
{
    TMENVMWriteExMessage *NVMWriteExIPCMsg = (TMENVMWriteExMessage *)(TMEIPCMsg);
    if(Status == QAPI_OK)
    {
        Status = qapi_Convert_Tme_Status(NVMWriteExIPCMsg->output.status);
    }
    return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding NVM read-ex IPC message.

   @param[in]      QapiParams       QAPI NVM read-ex parameters.
   @param[in, out] TMEIPCMsg        TME NVM read-ex IPC mesaage.
   @param[in, out] TMEIPCMsgLength  TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_NVM_Read_Ex_IPC_Msg(void     *QapiParams,
                                                      void    **TmeIPCMsg,
                                                      uint32_t *TmeIPCMsgLength)
{
    qapi_NVM_Read_Rot_Params_t *NVMReadExParams =
                            (qapi_NVM_Read_Rot_Params_t *)QapiParams;
    if (NVMReadExParams == NULL || NVMReadExParams->Buffer == NULL ||
        NVMReadExParams->BufferLen == 0)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (!NVM_VerifyOffset(NVMReadExParams->Offset, NVMReadExParams->BufferLen))
    {
        return QAPI_ERR_BOUNDS;
    }

    *TmeIPCMsgLength = sizeof(TMENVMReadExMessage);
    *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength); 
    if (*TmeIPCMsg == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    TMENVMReadExMessage *NVMReadExIPCMsg = (TMENVMReadExMessage *)(*TmeIPCMsg);
    NVMReadExIPCMsg->input.offset = NVMReadExParams->Offset;
    NVMReadExIPCMsg->output.output.pData   = NVMReadExParams->Buffer;
    NVMReadExIPCMsg->output.output.length  = NVMReadExParams->BufferLen;
    NVMReadExIPCMsg->output.output.lengthUsed  = 0;
    
    return QAPI_OK;
}

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
                                                   void          *UserData)
{
    TMENVMReadExMessage *NVMReadExIPCMsg = (TMENVMReadExMessage *)(TMEIPCMsg);
    if(Status == QAPI_OK)
    {
        Status = qapi_Convert_Tme_Status(NVMReadExIPCMsg->output.status);
    }
    return Status;
}