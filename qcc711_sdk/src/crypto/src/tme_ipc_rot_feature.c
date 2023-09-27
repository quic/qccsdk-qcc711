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
#include "qapi_rot.h"

 // TME utility headers
#include "tme_crypto_params.h"
#include "tme_types.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_callback_utils.h"

// TME interface headers
#include "tme_patch_version_interface.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
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
                                                        uint32_t *TmeIPCMsgLength)
{

   qapi_ROT_Get_Patch_Version_Params_t *GetPatchVersionParams =
                            (qapi_ROT_Get_Patch_Version_Params_t *)QapiGetPatchVersionParams;
   if (GetPatchVersionParams == NULL || GetPatchVersionParams->PatchVersion == NULL ||
       GetPatchVersionParams->PatchVersionLen == 0)
   {
     return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEGetPatchVersionMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEGetPatchVersionMessage *GetPatchVersionIPCMsg = (TMEGetPatchVersionMessage *)(*TmeIPCMsg);
   GetPatchVersionIPCMsg->output.response.pData  = GetPatchVersionParams->PatchVersion;
   GetPatchVersionIPCMsg->output.response.length = GetPatchVersionParams->PatchVersionLen;
   return QAPI_OK;
}

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
                                                     void *UserData)
{

   TMEGetPatchVersionMessage *GetPatchVersionIPCMsg = (TMEGetPatchVersionMessage *)(TMEIPCMsg);
   qapi_ROT_Get_Patch_Version_Params_t *GetPatchVersionParams =
                     (qapi_ROT_Get_Patch_Version_Params_t *)QapiGetPatchVersionParams;
   
   GetPatchVersionParams->PatchVersionLenUsed = GetPatchVersionIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(GetPatchVersionIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_ROT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_ROT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_ROT_GET_PATCH_VERSION_E;
        EventData->Data.GetPatchVersionParams = QapiGetPatchVersionParams;
        Status = Process_TME_Callback(Status, ROT_EVENT_DATA, EventData, UserData, CallBack);
      }
   }
   return Status;
}
