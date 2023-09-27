/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_macchiato_interface.h
 * @brief Ziggy token related interfaces to TME-FW.
          Defines structures for the following Ziggy token usecases.
 *        <br>Ziggy Authentication. 
 *        <br>Ziggy Remote Attestation.
 *        <br>Ziggy Secure Onboarding.
 *        <br>Ziggy Authentic Token Management.
 *        <br>Ziggy Confidential Token Management.
 */
#ifndef TME_MACCHIATO_INTERFACE_H
#define TME_MACCHIATO_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/***************************************************************
 *  Ziggy Authentication Request/Response Structure Definitions.
 ***************************************************************/

/*!
 * @struct TMEGetAuthTokenMessageResponse.
 * @brief Output structure of get authentication token message.
 */

typedef struct PACKED_PREFIX tme_get_auth_token_message_response_s
{
    TMEStatus          status;   /*!< Status of the response. */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with
                                      authentication token. Memory for the
                                      response buffer is to be allocated by the
                                      calling subsystem. The calling subsystem
                                      will set the length accordingly. */
} TMEGetAuthTokenMessageResponse;

/*!
 * @struct TMEGetAuthTokenMessage.
 * @brief Structure of get authentication token message.
 */

typedef struct PACKED_PREFIX tme_get_auth_token_message_s
{
    TMEGetAuthTokenMessageResponse output; /*!< Get authentication token message's response. */
} TMEGetAuthTokenMessage;

/*******************************************************************
 *  Ziggy Remote Attestation Request/Response Structure Definitions.
 *******************************************************************/

/*!
 * @struct TMEGetAttestationTokenMessageRequest.
 * @brief Input structure of get attestation token message.
 */

typedef struct PACKED_PREFIX tme_get_attestation_token_message_request_s
{
    TMECBuffer token;     /*!< Input buffer containing request attestation token.
                               The calling subsystem will allocate memory
                               and fill the buffer with request attestation
                               token along with setting the length. */
    TMECBuffer appData;   /*!< Input buffer containing application data.
                               The calling subsystem will allocate memory
                               and fill the buffer with the application
                               data along with setting the length. The
                               maximum allowed length is 32 bytes */
    TMECBuffer publicKey; /*!< Input buffer containing OEM public key. The calling
                               subsystem will allocate memory and fill the
                               buffer with the OEM public key along with
                               setting the length. */
} TMEGetAttestationTokenMessageRequest;

/*!
 * @struct TMEGetAttestationTokenMessageResponse.
 * @brief Output structure of get attestation token message.
 */

typedef struct PACKED_PREFIX tme_get_attestation_token_message_response_s
{
    TMEStatus          status;     /*!< Status of the response. */
    TMEResponseCBuffer response;   /*!< Response buffer to be filled by TME with
                                        attestation token. Memory for the
                                        response buffer is to be allocated by the
                                        calling subsystem. The calling subsystem
                                        will set the length accordingly. */
} TMEGetAttestationTokenMessageResponse;

/*!
 * @struct TMEGetAttestationTokenMessage.
 * @brief Structure of get attestation token message.
 */

typedef struct PACKED_PREFIX tme_get_attestation_token_message_s
{
    TMEGetAttestationTokenMessageRequest  input;  /*!< Get attestation token message's request. */
    TMEGetAttestationTokenMessageResponse output; /*!< Get attestation token message's response. */
} TMEGetAttestationTokenMessage;

/******************************************************************
 *  Ziggy Secure Onboarding Request/Response Structure Definitions.
 ******************************************************************/

/*!
 * @struct TMEProcessOnboardTokenMessageRequest.
 * @brief Input structure of process onboard token message.
 */

typedef struct PACKED_PREFIX tme_process_onboard_token_message_request_s
{
    TMECBuffer token;        /*!< Input buffer containing request onboarding
                                  token. The calling subsystem will allocate
                                  memory and fill the buffer with request 
                                  onboarding token along with setting the 
                                  length. */
    TMECBuffer oemPublicKey; /*!< Input buffer containing OEM public key. The
                                  calling subsystem will allocate memory and
                                  fill the buffer with the OEM public key 
                                  along with setting the length. */
} TMEProcessOnboardTokenMessageRequest;

/*!
 * @struct TMEProcessOnboardTokenResponse.
 * @brief Output structure of process onboard token message.
 */

typedef struct PACKED_PREFIX tme_process_onboard_token_message_response_s
{
    TMEStatus          status;        /*!< Status of the response. */
    TMEResponseCBuffer eslInfo;       /*!< Input buffer containing esl config data.
                                           The calling subsystem will allocate memory
                                           and fill the buffer with application data
                                           along with setting the length. The maximum
                                           allowed length is 64 bytes */
    TMEResponseCBuffer MEPublicKey;   /*!< Input buffer containing information about
                                           ME Public Key. The calling subsystem will
                                           allocate memory along with setting the length. */
    TMEResponseCBuffer MECertParams ; /*!< Input buffer containing information about
                                           the parameters sent along with ME certificate.
                                           The calling subsystem will allocate memory
                                           along with setting the length. */
    TMEKeyHandle       sharedSecret;  /*!< KeyHandle of the shared secret. */
} TMEProcessOnboardTokenMessageResponse;

/*!
 * @struct TMEProcessSecureOnboardMessage.
 * @brief Structure of process secure onboard token message.
 */

typedef struct PACKED_PREFIX tme_process_onboard_token_messsage_s
{
    TMEProcessOnboardTokenMessageRequest  input;  /*!< Process onboard token message's request. */
    TMEProcessOnboardTokenMessageResponse output; /*!< Process onboard token message's response. */
} TMEProcessOnboardTokenMessage;

/*!
 * @struct TMEGetOnboardTokenConfirmationMessageRequest.
 * @brief Input structure of get onboard token confirmation message.
 */

typedef struct PACKED_PREFIX tme_get_onboard_token_confirmation_message_request_s
{
    TMEKeyHandle sharedSecret; /*!< KeyHandle of the shared secret. */
    TMECBuffer   appData;      /*!< Input buffer containing application data. 
                                    The calling subsystem will allocate memory
                                    and fill the buffer with application data
                                    along with setting the length. */
} TMEGetOnboardTokenConfirmationMessageRequest;

/*!
 * @struct TMEGetOnboardTokenConfirmationMessageResponse.
 * @brief Output structure of get onboard token confirmation message.
 */

typedef struct PACKED_PREFIX tme_get_onboard_token_confirmation_message_response_s
{
    TMEStatus          status;   /*!< Status of the response. */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with
                                      onboarding token. Memory for the response
                                      buffer is to be allocated by the calling
                                      subsystem. The calling subsystem will
                                      set the length accordingly. */
} TMEGetOnboardTokenConfirmationMessageResponse;

/*!
 * @struct TMEGetOnboardTokenConfirmationMessage.
 * @brief Structure of get onboard token confirmation message.
 */

typedef struct PACKED_PREFIX tme_get_onboard_token_confirmation_messsage_s
{
    TMEGetOnboardTokenConfirmationMessageRequest  input;  /*!< Get onboard token confirmation message's request. */
    TMEGetOnboardTokenConfirmationMessageResponse output; /*!< Get onboard token confirmation  message's response. */
} TMEGetOnboardTokenConfirmationMessage;

/*********************************************************************
 *  Ziggy Authentic Management Request/Response Structure Definitions.
 *********************************************************************/

/*!
 * @struct TMETokenAuthenticateMesssageRequest.
 * @brief Input structure of token authenticate message.
 */

typedef struct PACKED_PREFIX tme_token_authenticate_message_request_s
{
    TMECBuffer token;     /*!< Input buffer containing the request authentic
                               token. The calling subsystem will allocate
                               memory and fill the buffer with the request
                               authentic token along with setting the length. */
    TMECBuffer publicKey; /*!< Input buffer containing OEM public key. The calling
                               subsystem will allocate memory and fill the
                               buffer with the OEM public key along with setting
                               the length. */
} TMETokenAuthenticateMessageRequest;

/*!
 * @struct TMETokenAuthenticateMessageResponse.
 * @brief Output structure of token authenticate message.
 */

typedef struct PACKED_PREFIX tme_token_authenticate_message_response_s
{
    TMEStatus          status;     /*!< Status of the response. */
    TMEResponseCBuffer meData;     /*!< Response buffer containing ME data.
                                        The calling subsystem will allocate memory
                                        and fill the buffer with ME data along
                                        with setting the length. */
    UINT32             isVerified; /*!< 1 if the signature over input in
                                        tme_token_authenticate_message_request_s
                                        was verified successfully. */
} TMETokenAuthenticateMessageResponse;

/*!
 * @struct TMETokenAuthenticateMessage.
 * @brief Structure of token authenticate message.
 */

typedef struct PACKED_PREFIX tme_token_authenticate_messsage_s
{
    TMETokenAuthenticateMessageRequest  input;  /*!< Token authenticate message's request. */
    TMETokenAuthenticateMessageResponse output; /*!< Token authenticate message's response. */
} TMETokenAuthenticateMessage;

/*!
 * @struct TMETokenAuthenticationConfirmRequest.
 * @brief Input structure of token authentication confirm message.
 */

typedef struct PACKED_PREFIX tme_token_authentication_confirm_message_request_s
{
   TMECBuffer appData; /*!< Input buffer containing application data.
                            The calling subsystem will allocate memory
                            and fill the buffer with application data along
                            with setting the length. */
} TMETokenAuthenticationConfirmMessageRequest;

/*!
 * @struct TMETokenAuthenticationConfirmResponse.
 * @brief Output structure of token authentication confirm message.
 */

typedef struct PACKED_PREFIX tme_token_authentication_confirm_message_response_s
{
    TMEStatus          status;   /*!< Status of the response. */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with
                                      authentic management token. Memory for the
                                      response buffer is to be allocated by the
                                      calling subsystem. The calling subsystem
                                      will set the length accordingly. */
} TMETokenAuthenticationConfirmMessageResponse;

/*!
 * @struct TMETokenAuthenticationConfirmMessage.
 * @brief Structure of token authentication confirm message.
 */

typedef struct PACKED_PREFIX tme_token_authentication_confirm_messsage_s
{
    TMETokenAuthenticationConfirmMessageRequest  input;  /*!< Token authentication confirm message's request. */
    TMETokenAuthenticationConfirmMessageResponse output; /*!< Token authentication confirm message's response. */
} TMETokenAuthenticationConfirmMessage;

/***********************************************************************
 *  Ziggy Confidential Management Request/Response Structure Definitions.
 ***********************************************************************/

/*!
 * @struct TMETokenDecryptMesssageRequest.
 * @brief Input structure of token decrypt message.
 */

typedef struct PACKED_PREFIX tme_token_decrypt_message_request_s
{
    TMECBuffer token; /*!< Input buffer containing the request
                           confidential token. The calling subsystem
                           will allocate memory and fill the buffer
                           with request confidential token along
                           with setting the length. */
} TMETokenDecryptMessageRequest;

/*!
 * @struct TMETokenDecryptMessageResponse.
 * @brief Output structure of token decrypt message.
 */

typedef struct PACKED_PREFIX tme_token_decrypt_message_response_s
{
    TMEStatus          status;       /*!< Status of the response. */
    TMEResponseCBuffer meData;       /*!< Response buffer containing ME data.
                                         The calling subsystem will allocate memory
                                         and fill the buffer with ME data along
                                         with setting the length. */
    TMEKeyHandle       sharedSecret; /*!< Key handle of the shared secret (out). */
} TMETokenDecryptMessageResponse;

/*!
 * @struct TMETokenDecryptMessage.
 * @brief Structure of token decrypt message.
 */

typedef struct PACKED_PREFIX tme_token_decrypt_messsage_s
{
    TMETokenDecryptMessageRequest  input;  /*!< Token decrypt message's request. */
    TMETokenDecryptMessageResponse output; /*!< Token decrypt message's response. */
} TMETokenDecryptMessage;

/*!
 * @struct TMETokenDecryptionConfirmMessageRequest.
 * @brief Input structure of token decryption confirm message.
 */

typedef struct PACKED_PREFIX tme_token_decryption_confirm_message_request_s
{
    TMEKeyHandle sharedSecret; /*!< KeyHandle of the shared secret. */
    TMECBuffer   appData;      /*!< Input buffer containing application data.
                                    The calling subsystem will allocate memory
                                    and fill the buffer with the application
                                    data along with setting the length. */
} TMETokenDecryptionConfirmMessageRequest;

/*!
 * @struct TMEQapiTokenDecryptionConfirmMessageResponse.
 * @brief Output structure of token decryption confirm message.
 */

typedef struct PACKED_PREFIX tme_token_decryption_confirm_message_response_s
{
    TMEStatus          status;   /*!< Status of the response. */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with
                                      response confidential token. Memory for the
                                      response buffer is to be allocated by the
                                      calling subsystem. The calling subsystem
                                      will set the length accordingly. */
} TMETokenDecryptionConfirmMessageResponse;

/*!
 * @struct TMETokenDecryptionConfirmMessage.
 * @brief Structure of token decryption confirm message.
 */

typedef struct PACKED_PREFIX tme_token_decryption_confirm_messsage_s
{
    TMETokenDecryptionConfirmMessageRequest  input;  /*!< Token decryption confirm message's request. */
    TMETokenDecryptionConfirmMessageResponse output; /*!< Token decryption confirm message's response. */
} TMETokenDecryptionConfirmMessage;
// clang-format on
#endif /* TME_MACCHIATO_INTERFACE_H */
