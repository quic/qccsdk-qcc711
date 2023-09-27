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
#include "tme_ipc_crypto.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/* Structure with conversion function of QAPI to IPC message and vice-versa, based on message ID. */
TMEIPCQapiMapping TmeMessageMapping[] =
{
   {TME_MSG_UID_CRYPTO_KEY_IMPORT, Validate_And_Create_Import_Key_IPC_Msg, Process_Import_Key_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_KEY_CLEAR, Validate_And_Create_Clear_Key_IPC_Msg, Process_Clear_Key_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_DERIVE_KEY, Validate_And_Create_Derive_Key_IPC_Msg, Process_Derive_Key_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_HMAC, Validate_And_Create_HMAC_256_IPC_Msg, Process_HMAC_256_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_GENERATE_KEYPAIR, Validate_And_Create_Generate_Key_Pair_IPC_Msg, Process_Generate_Key_Pair_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_ECC_GET_PUBLIC_KEY, Validate_And_Create_ECC_Get_Public_Key_IPC_Msg, Process_ECC_Get_Public_Key_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_DERIVE_SHARED_SECRET, Validate_And_Create_ECDH_Shared_Secret_IPC_Msg, Process_ECDH_Shared_Secret_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_ECDSA_SIGN_DIGEST, Validate_And_Create_ECDSA_Sign_Digest_IPC_Msg, Process_ECDSA_Sign_Digest_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_ECDSA_VERIFY_DIGEST, Validate_And_Create_ECDSA_Verify_Digest_IPC_Msg, Process_ECDSA_Verify_Digest_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_ECDSA_SIGN_BUFFER, Validate_And_Create_ECDSA_Sign_Message_IPC_Msg, Process_ECDSA_Sign_Message_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_ECDSA_VERIFY_BUFFER, Validate_And_Create_ECDSA_Verify_Message_IPC_Msg, Process_ECDSA_Verify_Message_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_AES_DECRYPT_EX, Validate_And_Create_AES_Decryption_IPC_Msg, Process_AES_Decryption_IPC_Msg_Response},
   {TME_MSG_UID_CRYPTO_AES_ENCRYPT_EX, Validate_And_Create_AES_Encryption_IPC_Msg, Process_AES_Encryption_IPC_Msg_Response}
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
 
/**
   @brief Get TME IPC mapping for APSS exclusive qapi.
 
   @param[in] TmeMsgUid  TME message ID.

   @return TMEIPCQapiMapping  Tme message mapping corresponding to
           TmeMsgUid will be returned if found, else NULL.
*/
TMEIPCQapiMapping* Get_IPC_QAPI_Mapping(uint32_t TmeMsgUid)
{
  uint32_t MapLength = ARRAY_ELEMENTS(TmeMessageMapping);

  for(uint32_t index = 0; index < MapLength; index++)
   {
      if(TmeMessageMapping[index].messageId == TmeMsgUid)
      {
         return (&TmeMessageMapping[index]);         
      }
   }

  return NULL;
}