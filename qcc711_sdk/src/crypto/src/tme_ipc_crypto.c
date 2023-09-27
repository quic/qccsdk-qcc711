/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
// Global header
#include <string.h>
// QAPI headers
#include "qapi_status.h"
#include "qapi_heap.h"
#include "qapi_crypto.h"

// TME utility headers
#include "tme_crypto_params.h"
#include "tme_types.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_callback_utils.h"
#include "tme_ipc_crypto.h"
#include "tme_crypto_keys_interface.h"
#include "tme_crypto_ex_interface.h"
#include "tme_crypto_ecc_interface.h"
#include "tme_crypto_hmac_interface.h"

/*-------------------------------------------------------------------------
 * Macro Definitions
 *-----------------------------------------------------------------------*/
#define TME_INVALID_KEY_CONFIG            0xFFFFFFFF
#define TME_INVALID_AES_ALGO              0xFFFFFFFF

/*-------------------------------------------------------------------------
 * Static global function definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Function to convert Qapi key algo to corresponding TME key config.

   @param [in]  qapi_CRPT_Key_Algo_t   QAPI key algo.
   @param [out] TMEKeyConfig           Corresponding TME key config
                                       from input Qapi key algo,
                                       otherwise TME_INVALID_KEY_CONFIG.
 */
static TMEKeyConfig Tme_Key_Config_Mapping(qapi_CRPT_Key_Algo_t QapiKeyAlgo)
{
   TMEKeyConfig KeyConfig = (TMEKeyConfig) TME_INVALID_KEY_CONFIG;
   switch(QapiKeyAlgo)
   {
   case QAPI_CRPT_KEY_ALGO_AES_GCM_128_E:
     KeyConfig =  TME_KEY_CONFIG_AES_GCM_128;
     break;
   case QAPI_CRPT_KEY_ALGO_AES_GCM_256_E:
     KeyConfig = TME_KEY_CONFIG_AES_GCM_256;
     break;
   case QAPI_CRPT_KEY_ALGO_AES_CBC_128_E:
     KeyConfig = TME_KEY_CONFIG_AES_CBC_128;
     break;
   case QAPI_CRPT_KEY_ALGO_AES_CBC_256_E:
     KeyConfig = TME_KEY_CONFIG_AES_CBC_256;
     break;
   case QAPI_CRPT_KEY_ALGO_AES_CTR_128_E:
     KeyConfig = TME_KEY_CONFIG_AES_CTR_128;
     break;
   case QAPI_CRPT_KEY_ALGO_AES_CTR_256_E:
     KeyConfig = TME_KEY_CONFIG_AES_CTR_256;
     break;
   case QAPI_CRPT_KEY_ALGO_SHA_HMAC_256_E:
     KeyConfig = TME_KEY_CONFIG_SHA_HMAC_256;
     break;
   case QAPI_CRPT_KEY_ALGO_HKDF_128_E:
     KeyConfig = TME_KEY_CONFIG_HKDF_128;
     break;
   case QAPI_CRPT_KEY_ALGO_HKDF_256_E:
     KeyConfig = TME_KEY_CONFIG_HKDF_256;
     break;
   case QAPI_CRPT_KEY_ALGO_ECDSA_256_E:
     KeyConfig = TME_KEY_CONFIG_ECDSA_256;
     break;
   case QAPI_CRPT_KEY_ALGO_ECDSA_521_E:
     KeyConfig = TME_KEY_CONFIG_ECDSA_521;
     break;
   case QAPI_CRPT_KEY_ALGO_ECDH_256_E:
     KeyConfig = TME_KEY_CONFIG_ECDH_256;
     break;
   case  QAPI_CRPT_KEY_ALGO_ECDH_521_E:
     KeyConfig = TME_KEY_CONFIG_ECDH_521;
     break;
   default:
    KeyConfig = (TMEKeyConfig) TME_INVALID_KEY_CONFIG;
   }
   return KeyConfig;
};

/**
   @brief Function to convert Qapi aes algo to corresponding TME aes algo.

   @param [in]  qapi_CRPT_AES_Algo_t   QAPI aes algo.
   @param [out] TMEAESAlgo             Corresponding TME aes algo
                                       from input Qapi aes algo,
                                       otherwise TME_INVALID_AES_ALGO.

 */
static TMEAESAlgo Tme_AES_Algo_Mapping(qapi_CRPT_AES_Algo_t QapiAesAlgo)
{
   TMEAESAlgo AesAlgo = (TMEAESAlgo) TME_INVALID_AES_ALGO;
   switch(QapiAesAlgo)
   {
   case QAPI_CRPT_AES_ALGO_AES128_GCM_E:
     AesAlgo = TME_SALG_AES128_GCM;
     break;
   case QAPI_CRPT_AES_ALGO_AES256_GCM_E:
     AesAlgo = TME_SALG_AES256_GCM;
     break;
   case QAPI_CRPT_AES_ALGO_AES128_CBC_E:
     AesAlgo = TME_SALG_AES128_CBC;
     break;
   case QAPI_CRPT_AES_ALGO_AES256_CBC_E:
     AesAlgo = TME_SALG_AES256_CBC;
     break;
   case QAPI_CRPT_AES_ALGO_AES128_CTR_E:
     AesAlgo =  TME_SALG_AES128_CTR;
     break;
   case QAPI_CRPT_AES_ALGO_AES256_CTR_E:
     AesAlgo = TME_SALG_AES256_CTR;
     break;
   default:
     AesAlgo = (TMEAESAlgo) TME_INVALID_AES_ALGO;
   }
   return AesAlgo;
};

/**
   @brief Function to validate the received QAPI key algo.

   @param [in] qapi_CRPT_Key_Algo_t   QAPI key algo to be validated.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
 */
static qapi_Status_t Qapi_Validate_Crypt_Key_Algo(qapi_CRPT_Key_Algo_t qapi_crpt_key_algo)
{
  qapi_Status_t RetStatus = QAPI_ERR_INVALID_PARAM;
  if (qapi_crpt_key_algo >=  QAPI_CRPT_KEY_ALGO_AES_GCM_128_E &&
      qapi_crpt_key_algo <= QAPI_CRPT_KEY_ALGO_ECDH_521_E)
  {
    RetStatus = QAPI_OK;
  }
  return RetStatus;
}

/**
   @brief Function to validate the received QAPI AES algo.

   @param [in] qapi_CRPT_AES_Algo_t   QAPI AES algo to be validated.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
 */
static qapi_Status_t Qapi_Validate_Crypt_Aes_Algo(qapi_CRPT_AES_Algo_t qapi_crpt_aes_algo)
{
  qapi_Status_t RetStatus = QAPI_ERR_INVALID_PARAM;
  if (qapi_crpt_aes_algo >=  QAPI_CRPT_AES_ALGO_AES128_GCM_E &&
      qapi_crpt_aes_algo <= QAPI_CRPT_AES_ALGO_AES256_CTR_E)
  {
    RetStatus = QAPI_OK;
  }
  return RetStatus;
}

/**
   @brief Validate QAPI parameters and create corresponding import key IPC message.

   @param[in]      QapiImportKeyParams       QAPI import key parameters.
   @param[in, out] TMEIPCMsg                 TME import key IPC message.
   @param[in, out] TMEIPCMsgLength           TME import key IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Import_Key_IPC_Msg(void *QapiImportKeyParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_Import_Key_Params_t *ImportKeyParams =
    (qapi_CRPT_Import_Key_Params_t *)QapiImportKeyParams;
   if (ImportKeyParams == NULL || ImportKeyParams->KeyLen == 0 || ImportKeyParams->Key == NULL ||
       Qapi_Validate_Crypt_Key_Algo(ImportKeyParams->KeyAlgo) != QAPI_OK)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEImportKeyMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEImportKeyMessage *ImportKeyIPCMsg = (TMEImportKeyMessage *)(*TmeIPCMsg);
   ImportKeyIPCMsg->input.keyMaterial.pData = ImportKeyParams->Key;
   ImportKeyIPCMsg->input.keyMaterial.length = ImportKeyParams->KeyLen;
   ImportKeyIPCMsg->input.keyConfig = Tme_Key_Config_Mapping(ImportKeyParams->KeyAlgo);

   return QAPI_OK;
}

/**
   @brief Process import key IPC message response. Create event data for non-blocking call.

   @param[in] QapiImportKeyParams QAPI import key parameters.
   @param[in] TMEIPCMsg           TME import key IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            QAPI callback function.
   @param[in] UserData            Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_Import_Key_IPC_Msg_Response(void *QapiImportKeyParams,
                                                  void *TMEIPCMsg,
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData)
{
   TMEImportKeyMessage *ImportKeyIPCMsg = (TMEImportKeyMessage *)(TMEIPCMsg);

   qapi_CRPT_Import_Key_Params_t *ImportKeyParams =
    (qapi_CRPT_Import_Key_Params_t *)QapiImportKeyParams;
   ImportKeyParams->KeyHandle = ImportKeyIPCMsg->output.keyHandle;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ImportKeyIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_IMPORT_KEY_E;
        EventData->Data.ImportKeyParams = QapiImportKeyParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding clear key IPC message.

   @param[in]      QapiClearKeyParams       QAPI clear key parameters.
   @param[in, out] TMEIPCMsg                TME clear key IPC message.
   @param[in, out] TMEIPCMsgLength          TME clear key IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Clear_Key_IPC_Msg(void *QapiClearKeyParams,
                                                    void **TmeIPCMsg,
                                                    uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_Clear_Key_Params_t *ClearKeyParams =
    (qapi_CRPT_Clear_Key_Params_t *)QapiClearKeyParams;
   if (ClearKeyParams == NULL)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEClearKeyMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEClearKeyMessage *ClearKeyIPCMsg = (TMEClearKeyMessage *)(*TmeIPCMsg);
   ClearKeyIPCMsg->input.keyHandle = ClearKeyParams->KeyHandle;
   return QAPI_OK;
}

/**
   @brief Process clear key IPC message response. Create event data for non-blocking call.

   @param[in] QapiClearKeyParams  QAPI clear key parameters.
   @param[in] TMEIPCMsg           TME clear key IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            QAPI callback function.
   @param[in] UserData            Placeholder for user data.

    @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_Clear_Key_IPC_Msg_Response(void *QapiClearKeyParams,
                                                 void *TMEIPCMsg,
                                                 qapi_Status_t Status,
                                                 void *CallBack,
                                                 void *UserData)
{

   TMEClearKeyMessage *ClearKeyIPCMsg = (TMEClearKeyMessage *)(TMEIPCMsg);

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ClearKeyIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_CLEAR_KEY_E;
        EventData->Data.ClearKeyParams = QapiClearKeyParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding derive key IPC message.

   @param[in]      QapiDeriveKeyParams       QAPI derive key parameters.
   @param[in, out] TMEIPCMsg                 TME derive key IPC message.
   @param[in, out] TMEIPCMsgLength           TME derive key IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Derive_Key_IPC_Msg(void *QapiDeriveKeyParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams =
    (qapi_CRPT_Derive_Key_Params_t *)QapiDeriveKeyParams;
   if (DeriveKeyParams == NULL || Qapi_Validate_Crypt_Key_Algo(DeriveKeyParams->KeyAlgo) != QAPI_OK)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEDeriveKeyMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEDeriveKeyMessage *DeriveKeyIPCMsg = (TMEDeriveKeyMessage *)(*TmeIPCMsg);
   DeriveKeyIPCMsg->input.nonce.pData = DeriveKeyParams->Nonce;
   DeriveKeyIPCMsg->input.nonce.length = DeriveKeyParams->NonceLen;
   DeriveKeyIPCMsg->input.keyDerivationAlgo = TME_KEY_DERIVATION_ALGO_HKDF_256;
   DeriveKeyIPCMsg->input.keyConfig = Tme_Key_Config_Mapping(DeriveKeyParams->KeyAlgo);
   DeriveKeyIPCMsg->input.inKey = DeriveKeyParams->BaseKeyHandle;
   DeriveKeyIPCMsg->input.label.length = (DeriveKeyParams->Label != NULL) ? strlen(DeriveKeyParams->Label) : 0;
   DeriveKeyIPCMsg->input.label.pData = (UINT8 *)DeriveKeyParams->Label;

   return QAPI_OK;
}

/**
   @brief Process derive key IPC message response. Create event data for non-blocking call.

   @param[in] QapiDeriveKeyParams        QAPI derive key  parameters.
   @param[in] TMEIPCMsg                  TME derive key IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   QAPI callback function.
   @param[in] UserData                   Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Process_Derive_Key_IPC_Msg_Response(void *QapiDeriveKeyParams,
                                                  void *TMEIPCMsg,
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData)
{

   TMEDeriveKeyMessage *DeriveKeyIPCMsg = (TMEDeriveKeyMessage *)(TMEIPCMsg);
   qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams =
    (qapi_CRPT_Derive_Key_Params_t *)QapiDeriveKeyParams;
   DeriveKeyParams->DerivedKeyHandle = DeriveKeyIPCMsg->output.derivedKey;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(DeriveKeyIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_DERIVE_KEY_E;
        EventData->Data.DeriveKeyParams = QapiDeriveKeyParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding HMAC-256 IPC message.

   @param[in]      QapiHMACParams       QAPI HMAC-256  parameters.
   @param[in, out] TMEIPCMsg            TME HMAC-256 IPC message.
   @param[in, out] TMEIPCMsgLength      TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_HMAC_256_IPC_Msg(void *QapiHMACParams,
                                                   void **TmeIPCMsg,
                                                   uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_HMAC_256_Params_t *HMACParams = (qapi_CRPT_HMAC_256_Params_t *)QapiHMACParams;
   if (HMACParams == NULL || HMACParams->MessageLen == 0 || HMACParams->Message == NULL ||
       HMACParams->HMAC == NULL || HMACParams->HMACLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEHMACMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEHMACMessage *HMACIPCMsg = (TMEHMACMessage *)(*TmeIPCMsg);

   HMACIPCMsg->input.input.pData = HMACParams->Message;
   HMACIPCMsg->input.input.length = HMACParams->MessageLen;
   HMACIPCMsg->input.algo = TME_DALG_SHA256;
   HMACIPCMsg->input.initialMac.pData = NULL;
   HMACIPCMsg->input.initialMac.length = 0;
   HMACIPCMsg->input.keyHandle = HMACParams->KeyHandle;
   HMACIPCMsg->output.response.pData = HMACParams->HMAC;
   HMACIPCMsg->output.response.length = HMACParams->HMACLen;
   return QAPI_OK;
}

/**
   @brief Validate HMAC-256 IPC message response. Create event data for non-blocking call.

   @param[in] QapiHMACParams      QAPI HMAC-256  parameters.
   @param[in] TMEIPCMsg           TME HMAC-256 IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            QAPI callback function.
   @param[in] UserData            Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_HMAC_256_IPC_Msg_Response(void *QapiHMACParams,
                                                void *TMEIPCMsg,
                                                qapi_Status_t Status,
                                                void *CallBack,
                                                void *UserData)
{

   TMEHMACMessage *HMACIPCMsg = (TMEHMACMessage *)(TMEIPCMsg);
   qapi_CRPT_HMAC_256_Params_t *HMACParams = (qapi_CRPT_HMAC_256_Params_t *)QapiHMACParams;
   HMACParams->HMACLenUsed = HMACIPCMsg->output.response.lengthUsed;

    if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(HMACIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_HMAC_E;
        EventData->Data.HMACParams = QapiHMACParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding generate key pair IPC message.

   @param[in]      QapiGenerateKeyPairParams  QAPI generate key pair parameters.
   @param[in, out] TMEIPCMsg                  TME generate key pair IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Generate_Key_Pair_IPC_Msg(void *QapiGenerateKeyPairParams,
                                                            void **TmeIPCMsg,
                                                            uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams =
    (qapi_CRPT_Generate_Key_Pair_Params_t *)QapiGenerateKeyPairParams;
   if (GenerateKeyPairParams == NULL || GenerateKeyPairParams->PublicKey == NULL ||
       GenerateKeyPairParams->PublicKeyLen == 0 ||
       Qapi_Validate_Crypt_Key_Algo(GenerateKeyPairParams->KeyAlgo) != QAPI_OK)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEGenerateKeyPairMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEGenerateKeyPairMessage *GenerateKeyPairIPCMsg = (TMEGenerateKeyPairMessage *)(*TmeIPCMsg);
   GenerateKeyPairIPCMsg->input.keyConfig = Tme_Key_Config_Mapping(GenerateKeyPairParams->KeyAlgo);
   GenerateKeyPairIPCMsg->output.publicKey.pData = GenerateKeyPairParams->PublicKey;
   GenerateKeyPairIPCMsg->output.publicKey.length = GenerateKeyPairParams->PublicKeyLen;
   return QAPI_OK;
}

/**
   @brief Process generate key pair IPC message response. Create event data for non-blocking call.

   @param[in] QapiGenerateParams  QAPI generate key pair  parameters.
   @param[in] TMEIPCMsg           TME generate key pair IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            QAPI callback function.
   @param[in] UserData            Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_Generate_Key_Pair_IPC_Msg_Response(void *QapiGenerateKeyPairParams,
                                                         void *TMEIPCMsg,
                                                         qapi_Status_t Status,
                                                         void *CallBack,
                                                         void *UserData)
{

   TMEGenerateKeyPairMessage *GenerateKeyPairIPCMsg = (TMEGenerateKeyPairMessage *)(TMEIPCMsg);
   qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams =
    (qapi_CRPT_Generate_Key_Pair_Params_t *)QapiGenerateKeyPairParams;
   GenerateKeyPairParams->PrivateKeyHandle = GenerateKeyPairIPCMsg->output.privateKeyHandle;
   GenerateKeyPairParams->PublicKeyLenUsed = GenerateKeyPairIPCMsg->output.publicKey.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(GenerateKeyPairIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_GENERATE_KEY_PAIR_E;
        EventData->Data.GenerateKeyPairParams = QapiGenerateKeyPairParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding ECC get public key IPC message.

   @param[in]      QapiECCGetPublicKeyParams  QAPI ECC get public key parameters.
   @param[in, out] TMEIPCMsg                  TME ECC get public key IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECC_Get_Public_Key_IPC_Msg(void *QapiECCGetPublicKeyParams,
                                                             void **TmeIPCMsg,
                                                             uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams =
    (qapi_CRPT_ECC_Get_Public_Key_Params_t *)QapiECCGetPublicKeyParams;
   if (ECCGetPublicKeyParams == NULL ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECCGetPublicKeyParams->Curve) == 0 ||
       ECCGetPublicKeyParams->PublicKey == NULL || ECCGetPublicKeyParams->PublicKeyLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECCGetPublicKeyMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECCGetPublicKeyMessage *ECCGetPublicKeyIPCMsg = (TMEECCGetPublicKeyMessage *)(*TmeIPCMsg);
   ECCGetPublicKeyIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECCGetPublicKeyParams->Curve);
   ECCGetPublicKeyIPCMsg->input.keyHandle = ECCGetPublicKeyParams->PrivateKeyHandle;
   ECCGetPublicKeyIPCMsg->output.response.pData = ECCGetPublicKeyParams->PublicKey;
   ECCGetPublicKeyIPCMsg->output.response.length = ECCGetPublicKeyParams->PublicKeyLen;
   return QAPI_OK;
}

/**
   @brief Process ECC get public key IPC message response. Create event data for non-blocking call.

   @param[in] QapiECCGetPublicKeyParams  QAPI ECC get public key  parameters.
   @param[in] TMEIPCMsg                  TME ECC get public key IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   QAPI callback function.
   @param[in] UserData                   Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Process_ECC_Get_Public_Key_IPC_Msg_Response(void *QapiECCGetPublicKeyParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData)
{

   TMEECCGetPublicKeyMessage *ECCGetPublicKeyIPCMsg = (TMEECCGetPublicKeyMessage *)(TMEIPCMsg);
   qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams =
    (qapi_CRPT_ECC_Get_Public_Key_Params_t *)QapiECCGetPublicKeyParams;
   ECCGetPublicKeyParams->PublicKeyLenUsed = ECCGetPublicKeyIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECCGetPublicKeyIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECC_GET_PUBLIC_KEY_E;
        EventData->Data.ECCGetPublicKeyParams = QapiECCGetPublicKeyParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding IPC message.

   @param[in]      QapiECDHSharedSecretParams  QAPI ECDH shared secret parameters.
   @param[in, out] TMEIPCMsg                   TME ECDH shared secret IPC message.
   @param[in, out] TMEIPCMsgLength             TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDH_Shared_Secret_IPC_Msg(void *QapiECDHSharedSecretParams,
                                                             void **TmeIPCMsg,
                                                             uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams =
    (qapi_CRPT_ECDH_Shared_Secret_Params_t *)QapiECDHSharedSecretParams;
   if (ECDHSharedSecretParams == NULL || ECDHSharedSecretParams->PublicKey == NULL ||
       ECDHSharedSecretParams->PublicKeyLen == 0 ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECDHSharedSecretParams->Curve) == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECDHSharedSecretMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECDHSharedSecretMessage *ECDHSharedSecretIPCMsg = (TMEECDHSharedSecretMessage *)(*TmeIPCMsg);
   ECDHSharedSecretIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECDHSharedSecretParams->Curve);
   ECDHSharedSecretIPCMsg->input.keyHandle = ECDHSharedSecretParams->PrivateKeyHandle;
   ECDHSharedSecretIPCMsg->input.publicKey.pData = ECDHSharedSecretParams->PublicKey;
   ECDHSharedSecretIPCMsg->input.publicKey.length = ECDHSharedSecretParams->PublicKeyLen;
   ECDHSharedSecretIPCMsg->input.keyConfig = TME_KEY_CONFIG_HKDF_256;

   return QAPI_OK;
}

/**
   @brief Process ECDH shared secret IPC message response. Create event data for non-blocking call.

   @param[in] QapiECDHSharedSecretParams QAPI ECDH shared secret parameters.
   @param[in] TMEIPCMsg                  TME ECDH shared secret IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   QAPI callback function.
   @param[in] UserData                   Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Process_ECDH_Shared_Secret_IPC_Msg_Response(void *QapiECDHSharedSecretParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData)
{

   TMEECDHSharedSecretMessage *ECDHSharedSecretIPCMsg = (TMEECDHSharedSecretMessage *)(TMEIPCMsg);

   qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams =
    (qapi_CRPT_ECDH_Shared_Secret_Params_t *)QapiECDHSharedSecretParams;
   ECDHSharedSecretParams->SharedSecretHandle = ECDHSharedSecretIPCMsg->output.keyHandle;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECDHSharedSecretIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECDH_SHARED_SECRET_E;
        EventData->Data.ECDHSharedSecretParams = QapiECDHSharedSecretParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding ECSDA sign digest IPC message.

   @param[in]      QapiECDSASignDigestParams  qapi ECDSA sign digest parameters.
   @param[in, out] TMEIPCMsg                  TME ECDSA sign digest IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Sign_Digest_IPC_Msg(void *QapiECDSASignDigestParams,
                                                            void **TmeIPCMsg,
                                                            uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams =
    (qapi_CRPT_ECDSA_Sign_Digest_Params_t *)QapiECDSASignDigestParams;
   if (ECDSASignDigestParams == NULL ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECDSASignDigestParams->Curve) == 0 ||
       ECDSASignDigestParams->Digest == NULL ||
       ECDSASignDigestParams->DigestLen == 0 ||
       ECDSASignDigestParams->Signature == NULL ||
       ECDSASignDigestParams->SignatureLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECDSASignDigestMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECDSASignDigestMessage *ECDSASignDigestIPCMsg = (TMEECDSASignDigestMessage *)(*TmeIPCMsg);
   ECDSASignDigestIPCMsg->input.keyHandle = ECDSASignDigestParams->PrivateKeyHandle;
   ECDSASignDigestIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECDSASignDigestParams->Curve);
   ECDSASignDigestIPCMsg->input.digest.pData = ECDSASignDigestParams->Digest;
   ECDSASignDigestIPCMsg->input.digest.length = ECDSASignDigestParams->DigestLen;
   ECDSASignDigestIPCMsg->output.response.pData = ECDSASignDigestParams->Signature;
   ECDSASignDigestIPCMsg->output.response.length = ECDSASignDigestParams->SignatureLen;
   return QAPI_OK;
}

/**
   @brief Process ECDSA sign digest IPC message response. Create event data for non-blocking call.

   @param[in] QapiECDSASignDigestParams  qapi ECSDA sign digest parameters.
   @param[in] TMEIPCMsg                  TME ECDSA sign digest IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_ECDSA_Sign_Digest_IPC_Msg_Response(void *QapiECDSASignDigestParams,
                                                         void *TMEIPCMsg,
                                                         qapi_Status_t Status,
                                                         void *CallBack,
                                                         void *UserData)
{

   TMEECDSASignDigestMessage *ECDSASignDigestIPCMsg = (TMEECDSASignDigestMessage *)(TMEIPCMsg);
   qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams =
    (qapi_CRPT_ECDSA_Sign_Digest_Params_t *)QapiECDSASignDigestParams;
   ECDSASignDigestParams->SignatureLenUsed = ECDSASignDigestIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECDSASignDigestIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECDSA_SIGN_DIGEST_E;
        EventData->Data.ECDSASignDigestParams = QapiECDSASignDigestParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding ECDSA verify digest IPC message.

   @param[in]      QapiECDSAVerifyDigestParams  qapi ECDSA verify digest parameters.
   @param[in, out] TMEIPCMsg                    TME CSDA verify digest IPC message.
   @param[in, out] TMEIPCMsgLength              TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Verify_Digest_IPC_Msg(void *QapiECDSAVerifyDigestParams,
                                                              void **TmeIPCMsg,
                                                              uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams =
    (qapi_CRPT_ECDSA_Verify_Digest_Params_t *)QapiECDSAVerifyDigestParams;
   if (ECDSAVerifyDigestParams == NULL ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECDSAVerifyDigestParams->Curve) == 0 ||
       ECDSAVerifyDigestParams->PublicKey == NULL ||
       ECDSAVerifyDigestParams->PublicKeyLen == 0 ||
       ECDSAVerifyDigestParams->Digest == NULL ||
       ECDSAVerifyDigestParams->DigestLen == 0 ||
       ECDSAVerifyDigestParams->Signature == NULL ||
       ECDSAVerifyDigestParams->SignatureLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECDSAVerifyDigestMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECDSAVerifyDigestMessage *ECDSAVerifyDigestIPCMsg = (TMEECDSAVerifyDigestMessage *)(*TmeIPCMsg);

   ECDSAVerifyDigestIPCMsg->input.publicKey.pData = ECDSAVerifyDigestParams->PublicKey;
   ECDSAVerifyDigestIPCMsg->input.publicKey.length = ECDSAVerifyDigestParams->PublicKeyLen;
   ECDSAVerifyDigestIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECDSAVerifyDigestParams->Curve);
   ECDSAVerifyDigestIPCMsg->input.digest.pData = ECDSAVerifyDigestParams->Digest;
   ECDSAVerifyDigestIPCMsg->input.digest.length = ECDSAVerifyDigestParams->DigestLen;
   ECDSAVerifyDigestIPCMsg->input.signature.pData = ECDSAVerifyDigestParams->Signature;
   ECDSAVerifyDigestIPCMsg->input.signature.length = ECDSAVerifyDigestParams->SignatureLen;

   return QAPI_OK;
}

/**
   @brief Process ECDSA verify digest IPC message response. Create event data for non-blocking call.

   @param[in] QapiECDSAVerifyDigestParams   qapi ECDSA verify digest  parameters.
   @param[in] TMEIPCMsg                     TME ECDSA verify digest IPC message.
   @param[in] Status                        Tmecom return status.
   @param[in] CallBack                      qapi callback function.
   @param[in] UserData                      Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Process_ECDSA_Verify_Digest_IPC_Msg_Response(void *QapiECDSAVerifyDigestParams,
                                                           void *TMEIPCMsg,
                                                           qapi_Status_t Status,
                                                           void *CallBack,
                                                           void *UserData)
{
   TMEECDSAVerifyDigestMessage *ECDSAVerifyDigestIPCMsg = (TMEECDSAVerifyDigestMessage *)(TMEIPCMsg);

    if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECDSAVerifyDigestIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECDSA_VERIFY_DIGEST_E;
        EventData->Data.ECDSAVerifyDigestParams = QapiECDSAVerifyDigestParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding IPC message.

   @param[in]      QapiECDSASignParams  qapi ECDSA sign  parameters.
   @param[in, out] TMEIPCMsg            TME ECDSA sign message IPC message.
   @param[in, out] TMEIPCMsgLength      TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Sign_Message_IPC_Msg(void *QapiECDSASignParams,
                                                             void **TmeIPCMsg,
                                                             uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams =
    (qapi_CRPT_ECDSA_Sign_Message_Params_t *)QapiECDSASignParams;
   if (ECDSASignMessageParams == NULL ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECDSASignMessageParams->Curve) == 0 ||
       QAPI_CRPT_GET_TME_DIGEST_ALGO(ECDSASignMessageParams->Algo) == 0 ||
       ECDSASignMessageParams->MessageLen == 0 ||
       ECDSASignMessageParams->Message == NULL ||
       ECDSASignMessageParams->Signature == NULL ||
       ECDSASignMessageParams->SignatureLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECDSASignBufferMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECDSASignBufferMessage *ECDSASignMessageIPCMsg = (TMEECDSASignBufferMessage *)(*TmeIPCMsg);
   ECDSASignMessageIPCMsg->input.keyHandle = ECDSASignMessageParams->PrivateKeyHandle;
   ECDSASignMessageIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECDSASignMessageParams->Curve);
   ECDSASignMessageIPCMsg->input.algo = QAPI_CRPT_GET_TME_DIGEST_ALGO(ECDSASignMessageParams->Algo);
   ECDSASignMessageIPCMsg->input.message.pData = ECDSASignMessageParams->Message;
   ECDSASignMessageIPCMsg->input.message.length = ECDSASignMessageParams->MessageLen;
   ECDSASignMessageIPCMsg->output.response.pData = ECDSASignMessageParams->Signature;
   ECDSASignMessageIPCMsg->output.response.length = ECDSASignMessageParams->SignatureLen;
   return QAPI_OK;
}

/**
   @brief Process ECSDA sign IPC message response. Create event data for non-blocking call.

   @param[in] QapiECDSASignParams qapi ECDSA sign parameters.
   @param[in] TMEIPCMsg           TME ECSDA sign IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_ECDSA_Sign_Message_IPC_Msg_Response(void *QapiECDSASignParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData)
{

   TMEECDSASignBufferMessage *ECDSASignMessageIPCMsg = (TMEECDSASignBufferMessage *)(TMEIPCMsg);
   qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams =
    (qapi_CRPT_ECDSA_Sign_Message_Params_t *)QapiECDSASignParams;
   ECDSASignMessageParams->SignatureLenUsed = ECDSASignMessageIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECDSASignMessageIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECDSA_SIGN_MESSAGE_E;
        EventData->Data.ECDSASignMessageParams = QapiECDSASignParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding ECSDA verify IPC message.

   @param[in]      QapiECDSAVerifyParams   qapi ECDSA verify parameters.
   @param[in, out] TMEIPCMsg               TME ECDSA verify IPC message.
   @param[in, out] TMEIPCMsgLength         TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Verify_Message_IPC_Msg(void *QapiECDSAVerifyParams,
                                                               void **TmeIPCMsg,
                                                               uint32_t *TmeIPCMsgLength)
{

   qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams =
    (qapi_CRPT_ECDSA_Verify_Message_Params_t *)QapiECDSAVerifyParams;
   if (ECDSAVerifyMessageParams == NULL ||
       QAPI_CRPT_GET_TME_ECC_CURVE(ECDSAVerifyMessageParams->Curve) == 0 ||
       QAPI_CRPT_GET_TME_DIGEST_ALGO(ECDSAVerifyMessageParams->Algo) == 0 ||
       ECDSAVerifyMessageParams->PublicKey == NULL ||
       ECDSAVerifyMessageParams->PublicKeyLen == 0 ||
       ECDSAVerifyMessageParams->Message == NULL ||
       ECDSAVerifyMessageParams->MessageLen == 0 ||
       ECDSAVerifyMessageParams->Signature == NULL ||
       ECDSAVerifyMessageParams->SignatureLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEECDSAVerifyBufferMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEECDSAVerifyBufferMessage *ECDSAVerifyMessageIPCMsg = (TMEECDSAVerifyBufferMessage *)(*TmeIPCMsg);

   ECDSAVerifyMessageIPCMsg->input.publicKey.pData = ECDSAVerifyMessageParams->PublicKey;
   ECDSAVerifyMessageIPCMsg->input.publicKey.length = ECDSAVerifyMessageParams->PublicKeyLen;
   ECDSAVerifyMessageIPCMsg->input.curve = QAPI_CRPT_GET_TME_ECC_CURVE(ECDSAVerifyMessageParams->Curve);
   ECDSAVerifyMessageIPCMsg->input.algo = QAPI_CRPT_GET_TME_DIGEST_ALGO(ECDSAVerifyMessageParams->Algo);
   ECDSAVerifyMessageIPCMsg->input.message.pData = ECDSAVerifyMessageParams->Message;
   ECDSAVerifyMessageIPCMsg->input.message.length = ECDSAVerifyMessageParams->MessageLen;
   ECDSAVerifyMessageIPCMsg->input.signature.pData = ECDSAVerifyMessageParams->Signature;
   ECDSAVerifyMessageIPCMsg->input.signature.length = ECDSAVerifyMessageParams->SignatureLen;

   return QAPI_OK;
}

/**
   @brief Process ECDSA verify IPC message response. Create event data for non-blocking call.

   @param[in] QapiECDSAVerifyParams  qapi ECDSA verify  parameters.
   @param[in] TMEIPCMsg              TME ECDSA verify IPC message.
   @param[in] Status                 Tmecom return status.
   @param[in] CallBack               qapi callback function.
   @param[in] UserData               Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_ECDSA_Verify_Message_IPC_Msg_Response(void *QapiECDSAVerifyParams,
                                                            void *TMEIPCMsg,
                                                            qapi_Status_t Status,
                                                            void *CallBack,
                                                            void *UserData)
{

   TMEECDSAVerifyBufferMessage *ECDSAVerifyMessageIPCMsg = (TMEECDSAVerifyBufferMessage *)(TMEIPCMsg);

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(ECDSAVerifyMessageIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ECDSA_VERIFY_MESSAGE_E;
        EventData->Data.ECDSAVerifyMessageParams = QapiECDSAVerifyParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding AES encryption IPC message.

   @param[in]      QapiAESEncryptionParams   qapi AES encryption parameters.
   @param[in, out] TMEIPCMsg                 TME  IPC message.
   @param[in, out] TMEIPCMsgLength           TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_AES_Encryption_IPC_Msg(void *QapiAESEncryptionParams,
                                                         void **TmeIPCMsg,
                                                         uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams =
    (qapi_CRPT_AES_Encryption_Params_t *)QapiAESEncryptionParams;
   if (AESEncryptionParams == NULL ||
       Qapi_Validate_Crypt_Aes_Algo(AESEncryptionParams->Algo) != QAPI_OK ||
       AESEncryptionParams->PlainText == NULL || AESEncryptionParams->PlainTextLen == 0 ||
       AESEncryptionParams->IVLen == 0 || AESEncryptionParams->IV == NULL ||
       AESEncryptionParams->EncryptedDataLen == 0 || AESEncryptionParams->EncryptedData == NULL)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEAESEncryptionExMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEAESEncryptionExMessage *AESEncryptionIPCMsg = (TMEAESEncryptionExMessage *)(*TmeIPCMsg);
   AESEncryptionIPCMsg->input.key.pData = NULL;
   AESEncryptionIPCMsg->input.key.length = 0;
   AESEncryptionIPCMsg->input.keyHandle = AESEncryptionParams->KeyHandle;
   AESEncryptionIPCMsg->input.reqParams.algo = Tme_AES_Algo_Mapping(AESEncryptionParams->Algo);
   AESEncryptionIPCMsg->input.reqParams.plain.pData = AESEncryptionParams->PlainText;
   AESEncryptionIPCMsg->input.reqParams.plain.length = AESEncryptionParams->PlainTextLen;
   AESEncryptionIPCMsg->input.reqParams.AAD.pData = AESEncryptionParams->AAD;
   AESEncryptionIPCMsg->input.reqParams.AAD.length = AESEncryptionParams->AADLen;
   AESEncryptionIPCMsg->output.rspParams.encrypted.pData = AESEncryptionParams->EncryptedData;
   AESEncryptionIPCMsg->output.rspParams.encrypted.length = AESEncryptionParams->EncryptedDataLen;
   AESEncryptionIPCMsg->output.rspParams.IV.pData = AESEncryptionParams->IV;
   AESEncryptionIPCMsg->output.rspParams.IV.length = AESEncryptionParams->IVLen;
   AESEncryptionIPCMsg->output.rspParams.tag.pData = AESEncryptionParams->Tag;
   AESEncryptionIPCMsg->output.rspParams.tag.length = AESEncryptionParams->TagLen;
   return QAPI_OK;
}

/**
   @brief Process AES encryption IPC message response. Create event data for non-blocking call.

   @param[in] QapiAESEncryptionParams  qapi AES encryption parameters.
   @param[in] TMEIPCMsg                TME AES encryption IPC message.
   @param[in] Status                   Tmecom return status.
   @param[in] CallBack                 qapi callback function.
   @param[in] UserData                 Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_AES_Encryption_IPC_Msg_Response(void *QapiAESEncryptionParams,
                                                      void *TMEIPCMsg,
                                                      qapi_Status_t Status,
                                                      void *CallBack,
                                                      void *UserData)
{

   TMEAESEncryptionExMessage *AESEncryptionIPCMsg = (TMEAESEncryptionExMessage *)(TMEIPCMsg);
   qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams =
    (qapi_CRPT_AES_Encryption_Params_t *)QapiAESEncryptionParams;
   AESEncryptionParams->TagLenUsed = AESEncryptionIPCMsg->output.rspParams.tag.lengthUsed;
   AESEncryptionParams->IVLenUsed = AESEncryptionIPCMsg->output.rspParams.IV.lengthUsed;
   AESEncryptionParams->EncryptedDataLenUsed = AESEncryptionIPCMsg->output.rspParams.encrypted.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(AESEncryptionIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_ENCRYPT_E;
        EventData->Data.AESEncryptionParams = QapiAESEncryptionParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding AES decryption IPC message.

   @param[in]      QapiAESDecryptionParams  qapi AES decryption parameters.
   @param[in, out] TMEIPCMsg                TME AES decryption IPC message.
   @param[in, out] TMEIPCMsgLength          TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_AES_Decryption_IPC_Msg(void *QapiAESDecryptionParams,
                                                         void **TmeIPCMsg,
                                                         uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams =
    (qapi_CRPT_AES_Decryption_Params_t *)QapiAESDecryptionParams;
   if (AESDecryptionParams == NULL ||
       Qapi_Validate_Crypt_Aes_Algo(AESDecryptionParams->Algo) != QAPI_OK ||
       AESDecryptionParams->EncryptedData == NULL || AESDecryptionParams->EncryptedDataLen == 0 ||
       AESDecryptionParams->IV == NULL || AESDecryptionParams->IVLen == 0 ||
       AESDecryptionParams->PlainText == NULL || AESDecryptionParams->PlainTextLen == 0)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEAESDecryptionExMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEAESDecryptionExMessage *AESDecryptionIPCMsg = (TMEAESDecryptionExMessage *)(*TmeIPCMsg);
   AESDecryptionIPCMsg->input.key.pData = NULL;
   AESDecryptionIPCMsg->input.key.length = 0;
   AESDecryptionIPCMsg->input.keyHandle = AESDecryptionParams->KeyHandle;
   AESDecryptionIPCMsg->input.reqParams.algo = Tme_AES_Algo_Mapping(AESDecryptionParams->Algo);
   AESDecryptionIPCMsg->input.reqParams.encrypted.pData = AESDecryptionParams->EncryptedData;
   AESDecryptionIPCMsg->input.reqParams.encrypted.length = AESDecryptionParams->EncryptedDataLen;
   AESDecryptionIPCMsg->input.reqParams.IV.pData = AESDecryptionParams->IV;
   AESDecryptionIPCMsg->input.reqParams.IV.length = AESDecryptionParams->IVLen;
   AESDecryptionIPCMsg->input.reqParams.AAD.pData = AESDecryptionParams->AAD;
   AESDecryptionIPCMsg->input.reqParams.AAD.length = AESDecryptionParams->AADLen;
   AESDecryptionIPCMsg->input.reqParams.tag.pData = AESDecryptionParams->Tag;
   AESDecryptionIPCMsg->input.reqParams.tag.length = AESDecryptionParams->TagLen;
   AESDecryptionIPCMsg->output.response.pData = AESDecryptionParams->PlainText;
   AESDecryptionIPCMsg->output.response.length = AESDecryptionParams->PlainTextLen;
   return QAPI_OK;
}

/**
   @brief Process AES decryption IPC message response. Create event data for non-blocking call.

   @param[in] QapiAESDecryptionParams qapi AES decryption parameters.
   @param[in] TMEIPCMsg               TME AES decryption IPC message.
   @param[in] Status                  Tmecom return status.
   @param[in] CallBack                qapi callback function.
   @param[in] UserData                Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Process_AES_Decryption_IPC_Msg_Response(void *QapiAESDecryptionParams,
                                                      void *TMEIPCMsg,
                                                      qapi_Status_t Status,
                                                      void *CallBack,
                                                      void *UserData)
{

   TMEAESDecryptionExMessage *AESDecryptionIPCMsg = (TMEAESDecryptionExMessage *)(TMEIPCMsg);
   qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams =
    (qapi_CRPT_AES_Decryption_Params_t *)QapiAESDecryptionParams;
   AESDecryptionParams->PlainTextLenUsed = AESDecryptionIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(AESDecryptionIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_DECRYPT_E;
        EventData->Data.AESDecryptionParams = QapiAESDecryptionParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }

   return Status;
}
