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
   @brief Validate QAPI parameters and create corresponding import key IPC message.

   @param[in]      QapiImportKeyParams  qapi import key parameters.
   @param[in, out] TMEIPCMsg            TME import key IPC message.
   @param[in, out] TMEIPCMsgLength      TME import key IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Import_Key_IPC_Msg(void *QapiImportKeyParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength);

/**
   @brief Process import key IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiImportKeyParams qapi import key parameters.
   @param[in] TMEIPCMsg           TME import key IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                     

*/
qapi_Status_t Process_Import_Key_IPC_Msg_Response(void *QapiImportKeyParams,
                                                  void *TMEIPCMsg,
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding clear key IPC message.

   @param[in]      QapiClearKeyParams       qapi clear key parameters.
   @param[in, out] TMEIPCMsg                TME clear key IPC message.
   @param[in, out] TMEIPCMsgLength          TME clear key IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Clear_Key_IPC_Msg(void *QapiClearKeyParams,
                                                    void **TmeIPCMsg,
                                                    uint32_t *TmeIPCMsgLength);

/**
   @brief Process clear key IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiClearKeyParams  qapi clear key parameters.
   @param[in] TMEIPCMsg           TME clear key IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data.

    @return QAPI_OK if completed successfully, or a negative
           value if there was an error.

*/
qapi_Status_t Process_Clear_Key_IPC_Msg_Response(void *QapiClearKeyParams,
                                                 void *TMEIPCMsg,
                                                 qapi_Status_t Status,
                                                 void *CallBack,
                                                 void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding derive key IPC message.

   @param[in]      QapiDeriveKeyParams       qapi derive key parameters.
   @param[in, out] TMEIPCMsg                 TME derive key IPC message.
   @param[in, out] TMEIPCMsgLength           TME derive key IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Derive_Key_IPC_Msg(void *QapiDeriveKeyParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength);

/**
   @brief Process derive key IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiDeriveKeyParams        qapi derive key  parameters.
   @param[in] TMEIPCMsg                  TME derive key IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.                     

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Derive_Key_IPC_Msg_Response(void *QapiDeriveKeyParams,
                                                  void *TMEIPCMsg,
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding HMAC-256 IPC message.

   @param[in]      QapiHMACParams       qapi HMAC-256  parameters.
   @param[in, out] TMEIPCMsg            TME HMAC-256 IPC message.
   @param[in, out] TMEIPCMsgLength      TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_HMAC_256_IPC_Msg(void *QapiHMACParams,
                                                   void **TmeIPCMsg,
                                                   uint32_t *TmeIPCMsgLength);                                                       

/**
   @brief Validate HMAC-256 IPC message response. Create event data for non-blocking call.
 
   @param[in] Qapi                Params qapi HMAC-256  parameters.
   @param[in] TMEIPCMsg           TME HMAC-256 IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data. 

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                    

*/
qapi_Status_t Process_HMAC_256_IPC_Msg_Response(void *QapiHMACParams,
                                                void *TMEIPCMsg,
                                                qapi_Status_t Status,
                                                void *CallBack,
                                                void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding generate key pair IPC message.

   @param[in]      QapiGenerateKeyPairParams  qapi generate key pair parameters.
   @param[in, out] TMEIPCMsg                  TME generate key pair IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Generate_Key_Pair_IPC_Msg(void *QapiGenerateKeyPairParams,
                                                            void **TmeIPCMsg,
                                                            uint32_t *TmeIPCMsgLength);

/**
   @brief Process generate key pair IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiGenerateParams  qapi generate key pair  parameters.
   @param[in] TMEIPCMsg           TME generate key pair IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data. 

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                    

*/
qapi_Status_t Process_Generate_Key_Pair_IPC_Msg_Response(void *QapiGenerateKeyPairParams,
                                                         void *TMEIPCMsg,
                                                         qapi_Status_t Status,
                                                         void *CallBack,
                                                         void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding ECC get public key IPC message.

   @param[in]      QapiECCGetPublicKeyParams  qapi ECC get public key parameters.
   @param[in, out] TMEIPCMsg                  TME ECC get public key IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
 qapi_Status_t Validate_And_Create_ECC_Get_Public_Key_IPC_Msg(void *QapiECCGetPublicKeyParams,
                                                              void **TmeIPCMsg,
                                                              uint32_t *TmeIPCMsgLength);

/**
   @brief Process ECC get public key IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECCGetPublicKeyParams  qapi ECC get public key  parameters.
   @param[in] TMEIPCMsg                  TME ECC get public key IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.                     

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_ECC_Get_Public_Key_IPC_Msg_Response(void *QapiECCGetPublicKeyParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding   IPC message.

   @param[in]      QapiECDHSharedSecretParams  qapi ECDH shared secret parameters.
   @param[in, out] TMEIPCMsg                   TME ECDH shared secret IPC message.
   @param[in, out] TMEIPCMsgLength             TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDH_Shared_Secret_IPC_Msg(void *QapiECDHSharedSecretParams,
                                                             void **TmeIPCMsg,
                                                             uint32_t *TmeIPCMsgLength);
/**
   @brief Process ECDH shared secret IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECDHSharedSecretParams qapi ECDH shared secret parameters.
   @param[in] TMEIPCMsg                  TME ECDH shared secret IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.                     

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_ECDH_Shared_Secret_IPC_Msg_Response(void *QapiECDHSharedSecretParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding ECSDA sign digest IPC message.

   @param[in]      QapiECDSASignDigestParams  qapi ECDSA sign digest parameters.
   @param[in, out] TMEIPCMsg                  TME ECDSA sign digest IPC message.
   @param[in, out] TMEIPCMsgLength            TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Sign_Digest_IPC_Msg(void *QapiECDSASignDigestParams,
                                                            void **TmeIPCMsg,
                                                            uint32_t *TmeIPCMsgLength);

/**
   @brief Process ECDSA sign digest IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECDSASignDigestParams  qapi ECSDA sign digest parameters.
   @param[in] TMEIPCMsg                  TME ECDSA sign digest IPC message.
   @param[in] Status                     Tmecom return status.
   @param[in] CallBack                   qapi callback function.
   @param[in] UserData                   Placeholder for user data.  

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                   

*/
qapi_Status_t Process_ECDSA_Sign_Digest_IPC_Msg_Response(void *QapiECDSASignDigestParams,
                                                         void *TMEIPCMsg,
                                                         qapi_Status_t Status,
                                                         void *CallBack,
                                                         void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding ECDSA verify digest IPC message.

   @param[in]      QapiECDSAVerifyDigestParams  qapi ECDSA verify digest parameters.
   @param[in, out] TMEIPCMsg                    TME CSDA verify digest IPC message.
   @param[in, out] TMEIPCMsgLength              TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Verify_Digest_IPC_Msg(void *QapiECDSAVerifyDigestParams,
                                                              void **TmeIPCMsg,
                                                              uint32_t *TmeIPCMsgLength);

/**
   @brief Process ECDSA verify digest IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECDSAVerifyDigestParams   qapi ECDSA verify digest  parameters.
   @param[in] TMEIPCMsg                     TME ECDSA verify digest IPC message.
   @param[in] Status                        Tmecom return status.
   @param[in] CallBack                      qapi callback function.
   @param[in] UserData                      Placeholder for user data.                     

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_ECDSA_Verify_Digest_IPC_Msg_Response(void *QapiECDSAVerifyDigestParams,
                                                           void *TMEIPCMsg,
                                                           qapi_Status_t Status,
                                                           void *CallBack,
                                                           void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding   IPC message.

   @param[in]      QapiECDSASignParams  qapi ECDSA sign  parameters.
   @param[in, out] TMEIPCMsg            TME ECDSA sign message IPC message.
   @param[in, out] TMEIPCMsgLength      TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Sign_Message_IPC_Msg(void *QapiECDSASignParams,
                                                             void **TmeIPCMsg,
                                                             uint32_t *TmeIPCMsgLength);

/**
   @brief Process ECSDA sign IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECDSASignParams qapi ECDSA sign parameters.
   @param[in] TMEIPCMsg           TME ECSDA sign IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data. 

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                    

*/
qapi_Status_t Process_ECDSA_Sign_Message_IPC_Msg_Response(void *QapiECDSASignParams,
                                                          void *TMEIPCMsg,
                                                          qapi_Status_t Status,
                                                          void *CallBack,
                                                          void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding ECSDA verify IPC message.

   @param[in]      QapiECDSAVerifyParams   qapi ECDSA verify parameters.
   @param[in, out] TMEIPCMsg               TME ECDSA verify IPC message.
   @param[in, out] TMEIPCMsgLength         TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_ECDSA_Verify_Message_IPC_Msg(void *QapiECDSAVerifyParams,
                                                               void **TmeIPCMsg,
                                                               uint32_t *TmeIPCMsgLength);

/**
   @brief Process ECDSA verify IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiECDSAVerifyParams  qapi ECDSA verify  parameters.
   @param[in] TMEIPCMsg              TME ECDSA verify IPC message.
   @param[in] Status                 Tmecom return status.
   @param[in] CallBack               qapi callback function.
   @param[in] UserData               Placeholder for user data. 

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                    

*/
qapi_Status_t Process_ECDSA_Verify_Message_IPC_Msg_Response(void *QapiECDSAVerifyParams,
                                                            void *TMEIPCMsg,
                                                            qapi_Status_t Status,
                                                            void *CallBack,
                                                            void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding AES encryption IPC message.

   @param[in]      QapiAESEncryptionParams   qapi AES encryption parameters.
   @param[in, out] TMEIPCMsg                 TME  IPC message.
   @param[in, out] TMEIPCMsgLength           TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_AES_Encryption_IPC_Msg(void *QapiAESEncryptionParams,
                                                         void **TmeIPCMsg,
                                                         uint32_t *TmeIPCMsgLength);

/**
   @brief Process AES encryption IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiAESEncryptionParams  qapi AES encryption parameters.
   @param[in] TMEIPCMsg                TME AES encryption IPC message.
   @param[in] Status                   Tmecom return status.
   @param[in] CallBack                 qapi callback function.
   @param[in] UserData                 Placeholder for user data.  

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                   

*/
qapi_Status_t Process_AES_Encryption_IPC_Msg_Response(void *QapiAESEncryptionParams,
                                                      void *TMEIPCMsg,
                                                      qapi_Status_t Status,
                                                      void *CallBack,
                                                      void *UserData);

/**
   @brief Validate QAPI parameters and create corresponding AES decryption IPC message.

   @param[in]      QapiAESDecryptionParams  qapi AES decryption parameters.
   @param[in, out] TMEIPCMsg                TME AES decryption IPC message.
   @param[in, out] TMEIPCMsgLength          TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_AES_Decryption_IPC_Msg(void *QapiAESDecryptionParams,
                                                         void **TmeIPCMsg,
                                                         uint32_t *TmeIPCMsgLength);

/**
   @brief Process AES decryption IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiAESDecryptionParams qapi AES decryption parameters.
   @param[in] TMEIPCMsg               TME AES decryption IPC message.
   @param[in] Status                  Tmecom return status.
   @param[in] CallBack                qapi callback function.
   @param[in] UserData                Placeholder for user data.  

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                   

*/
qapi_Status_t Process_AES_Decryption_IPC_Msg_Response(void *QapiAESDecryptionParams,
                                                      void *TMEIPCMsg,
                                                      qapi_Status_t Status,
                                                      void *CallBack,
                                                      void *UserData);
                                                            
// clang-format on
#endif /* TME_IPC_CRYPTO_H */
