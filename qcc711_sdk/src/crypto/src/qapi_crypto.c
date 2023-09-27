/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

// Common qapi headers
#include "qapi_types.h"

// crypto headers
#include "qapi_crypto.h"

// TME utility headers
#include "tme_ipc_utils.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Imports the provided key in the crypto module.

   A key imported using this API must be cleared by calling the qapi_CRPT_Clear_Key()
   API after use.

   @param[in,out] ImportKeyParams  Import key operation parameters.
   @param[in]     CryptoCB         Callback function, only used in non-blocking mode.
                                   NULL for blocking mode.
   @param[in]     UserParam        User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ImportKeyParams should be in heap or a static
              buffer for non-blocking read. 
*/
qapi_Status_t qapi_CRPT_Import_Key(qapi_CRPT_Import_Key_Params_t *ImportKeyParams,
                                   qapi_CRPT_Operation_CB_t       CryptoCB,
                                   void                          *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_KEY_IMPORT,
                                 TME_MSG_UID_CRYPTO_KEY_IMPORT_PARAM_ID,
                                 ImportKeyParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Releases the resources allocated for the key.

   @param[in,out] ClearkeyParams  Clear key operation parameters.
   @param[in]     CryptoCB        Callback function, only used in non-blocking mode.
                                  NULL for blocking mode.
   @param[in]     UserParam       User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ClearkeyParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_Clear_Key(qapi_CRPT_Clear_Key_Params_t *ClearkeyParams,
                                  qapi_CRPT_Operation_CB_t      CryptoCB,
                                  void                         *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_KEY_CLEAR,
                                 TME_MSG_UID_CRYPTO_KEY_CLEAR_PARAM_ID,
                                 ClearkeyParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Derives a key from a specified base key.

   A key derived using this API must be cleared by calling the qapi_CRPT_Op_Clear_Key() 
   API after use.

   @param[in,out] DeriveKeyParams  Derive key operation parameters.
   @param[in]     CryptoCB         Callback function, only used in non-blocking mode.
                                   NULL for blocking mode.
   @param[in]     UserParam        User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.
  
   \attention The input parameter DeriveKeyParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_Derive_Key(qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams,
                                   qapi_CRPT_Operation_CB_t       CryptoCB,
                                   void                          *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_DERIVE_KEY,
                                 TME_MSG_UID_CRYPTO_DERIVE_KEY_PARAM_ID,
                                 DeriveKeyParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates HMAC for the specified message.

   @param[in,out] HMACParams  HMAC operation parameters.
   @param[in]     CryptoCB    Callback function, only used in non-blocking mode.
                              NULL for blocking mode.
   @param[in]     UserParam   User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter HMACParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_HMAC_256(qapi_CRPT_HMAC_256_Params_t *HMACParams,
                                 qapi_CRPT_Operation_CB_t     CryptoCB,
                                 void                        *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_HMAC,
                                 TME_MSG_UID_CRYPTO_HMAC_PARAM_ID,
                                 HMACParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Performs AES decryption.

   @param[in,out] AESDecryptionParams  AES decryption operation parameters.
   @param[in]     CryptoCB             Callback function, only used in non-blocking mode.
                                       NULL for blocking mode.
   @param[in]     UserParam            User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter AESDecryptionParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_AES_Decryption(qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams,
                                       qapi_CRPT_Operation_CB_t           CryptoCB,
                                       void                              *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_AES_DECRYPT_EX,
                                 TME_MSG_UID_CRYPTO_AES_DECRYPT_EX_PARAM_ID,
                                 AESDecryptionParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Performs AES encryption.

   @param[in,out] AESEncryptionParams  AES encryption operation parameters.
   @param[in]     CryptoCB             Callback function, only used in non-blocking mode.
                                       NULL for blocking mode.
   @param[in]     UserParam            User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter AESEncryptionParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_AES_Encryption(qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams,
                                       qapi_CRPT_Operation_CB_t           CryptoCB,
                                       void                              *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_AES_ENCRYPT_EX,
                                 TME_MSG_UID_CRYPTO_AES_ENCRYPT_EX_PARAM_ID,
                                 AESEncryptionParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates an ECC key pair.

   @param[in,out] GenerateKeyPairParams  Generate key Pair Operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter GenerateKeyPairParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_Generate_Key_Pair(qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams,
                                          qapi_CRPT_Operation_CB_t              CryptoCB,
                                          void                                 *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_GENERATE_KEYPAIR,
                                 TME_MSG_UID_CRYPTO_GENERATE_KEYPAIR_PARAM_ID,
                                 GenerateKeyPairParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Extract public key.

   @param[in,out] ECCGetPublicKeyParams  Get ECC Public Key Operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECCGetPublicKeyParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECC_Get_Public_Key(qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_ECC_GET_PUBLIC_KEY,
                                 TME_MSG_UID_CRYPTO_ECC_GET_PUBLIC_KEY_PARAM_ID,
                                 ECCGetPublicKeyParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates shared secret.

   @param[in,out] ECDHSharedSecretParams  ECDH shared secret operation parameters.
   @param[in]     CryptoCB                Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param[in]     UserParam               User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDHSharedSecretParams should be in heap or
              a static buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDH_Shared_Secret(qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_DERIVE_SHARED_SECRET,
                                 TME_MSG_UID_CRYPTO_DERIVE_SHARED_SECRET_PARAM_ID,
                                 ECDHSharedSecretParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates signature over a digest.

   @param[in,out] ECDSASignDigestParams  ECDSA sign digest operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSASignDigestParams should be in heap or
              a static buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDSA_Sign_Digest(qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams,
                                          qapi_CRPT_Operation_CB_t              CryptoCB,
                                          void                                 *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_ECDSA_SIGN_DIGEST,
                                 TME_MSG_UID_CRYPTO_ECDSA_SIGN_DIGEST_PARAM_ID,
                                 ECDSASignDigestParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Verifies signature over a digest.

   @param[in,out] ECDSAVerifyDigestParams  ECDSA verify digest operation parameters.
   @param[in]     CryptoCB                 Callback function, only used in non-blocking mode.
                                           NULL for blocking mode.
   @param[in]     UserParam                User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSAVerifyDigestParams should be in heap or
              a static buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDSA_Verify_Digest(qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams,
                                            qapi_CRPT_Operation_CB_t                CryptoCB,
                                            void                                   *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_ECDSA_VERIFY_DIGEST,
                                 TME_MSG_UID_CRYPTO_ECDSA_VERIFY_DIGEST_PARAM_ID,
                                 ECDSAVerifyDigestParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates signature over a message.

   @param[in,out] ECDSASignMessageParams  ECDSA sign message operation parameters.
   @param[in]     CryptoCB                Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param[in]     UserParam               User parameter, returned as-is in callback.
  
   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.
  
   \attention The input parameter ECDSASignMessageParams should be in heap or a static buffer
              for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDSA_Sign_Message(qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_ECDSA_SIGN_BUFFER,
                                 TME_MSG_UID_CRYPTO_ECDSA_SIGN_BUFFER_PARAM_ID,
                                 ECDSASignMessageParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Verifies signature over a message.

   @param[in,out] ECDSAVerifyMessageParams  ECDSA verify message operation parameters.
   @param[in]     CryptoCB                  Callback function, only used in non-blocking mode.
                                            NULL for blocking mode.
   @param[in]     UserParam                 User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSAVerifyMessageParams should be in heap or a static buffer
              for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDSA_Verify_Message(qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams,
                                             qapi_CRPT_Operation_CB_t                 CryptoCB,
                                             void                                    *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_ECDSA_VERIFY_BUFFER,
                                 TME_MSG_UID_CRYPTO_ECDSA_VERIFY_BUFFER_PARAM_ID,
                                 ECDSAVerifyMessageParams,
                                 (void *)CryptoCB,
                                 UserParam);
}
