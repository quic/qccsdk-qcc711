/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

// TME utility headers
#include "tme_ipc_utils.h"
#include "tme_ipc_crypto_common.h"
#include "tme_ipc_fwup_common.h"
#include "tme_ipc_access_control_common.h"
#include "tme_ipc_rot_feature_common.h"
#include "tme_ipc_nvm.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/* Structure with conversion function of QAPI to IPC message and vice-versa, based on message ID. */
TMEIPCQapiMapping TmeMessageMappingCommon[] =
{
  {TME_MSG_UID_CRYPTO_DIGEST, Validate_And_Create_Digest_IPC_Msg, Process_Digest_IPC_Msg_Response},
  {TME_MSG_UID_CRYPTO_GET_RANDOM, Validate_And_Create_Get_Random_IPC_Msg, Process_Get_Random_IPC_Msg_Response},
  {TME_MSG_UID_FWUP_APPLY_UPDATE, Validate_And_Create_Firmware_Update_Apply_IPC_Msg, 
                                          Process_Firmware_Update_Apply_IPC_Msg_Response},
  {TME_MSG_UID_FWUP_VERIFY_UPDATE, Validate_And_Create_Firmware_Update_Verify_IPC_Msg, 
                                          Process_Firmware_Update_Verify_IPC_Msg_Response},
  {TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER, Validate_And_Create_NVM_Register_Access_IPC_Msg, 
                                          Process_NVM_Register_Access_IPC_Msg_Response},
  {TME_MSG_UID_FEATURE_PATCH_VERSION, Validate_And_Create_Patch_Version_IPC_Msg, 
                                          Process_Patch_Version_IPC_Msg_Response},
  {TME_MSG_UID_GENERIC_NVM_WRITE_EX, Validate_And_Create_NVM_Write_Ex_IPC_Msg,
                                          Process_NVM_Write_Ex_IPC_Msg_Response},
  {TME_MSG_UID_GENERIC_NVM_READ_EX, Validate_And_Create_NVM_Read_Ex_IPC_Msg,
                                          Process_NVM_Read_Ex_IPC_Msg_Response},
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
 
/**
    @brief Get TME IPC mapping corresponding to the given 
           TmeMsgUid for APSS or BTSS exclusive qapi, else return NULL

   @param[in] TMEMsgUid     TME message identifier.
  
   @return TMEIPCQapiMapping  Tme message mapping corresponding to
           TmeMsgUid will be returned if found, else NULL.
*/
static TMEIPCQapiMapping* Get_IPC_QAPI_Common_Mapping(uint32_t TmeMsgUid)
{
  uint32_t MapLength = ARRAY_ELEMENTS(TmeMessageMappingCommon);

  for(uint32_t index = 0; index < MapLength; index++)
   {
      if(TmeMessageMappingCommon[index].messageId == TmeMsgUid)
      {
         return (&TmeMessageMappingCommon[index]);   
      }
   }

  return NULL;
}

/**
   @brief Get TMEIPCQapiMapping corresponding to the given 
          TmeMsgUid, else return NULL
 
   @param[in] TMEMsgUid     TME message identifier.
  
   @return TMEIPCQapiMapping  Tme message mapping corresponding to
           TmeMsgUid will be returned if found, else NULL.
*/
TMEIPCQapiMapping *Get_TME_Message_Mapping(uint32_t TmeMsgUid)

{
   // TmeMessageMapping corresponding to TmeMsgUid is checked first in the common mapping 
   // used by both BTSS and APSS.  
   TMEIPCQapiMapping *TmeMessageMapping = Get_IPC_QAPI_Common_Mapping(TmeMsgUid);
   // if TmeMessageMapping is not found in the common mapping, then the BTSS or APSS
   // specific mapping is checked.
   if (TmeMessageMapping == NULL)
   {
      TmeMessageMapping = Get_IPC_QAPI_Mapping(TmeMsgUid);
   }

   return TmeMessageMapping;
}