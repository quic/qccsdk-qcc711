/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_ecc_interface.h
 * @brief IPC's ECC operations' related interfaces for TME-FW Crypto Service.
 *        Defines structures for the following crypto requests
 *        <br>Generate Key pair
 *        <br>Get Public Key
 *        <br>Get ECDH Shared Secret
 *        <br>ECDSA Sign Digest
 *        <br>ECDSA Verify Digest
 *        <br>ECDSA Sign Message
 *        <br>ECDSA Verify Message
 */
#ifndef TME_CRYPTO_ECC_INTERFACE_H
#define TME_CRYPTO_ECC_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/*****************************************************************
 *  ECC Key Pair Generation Request/Response Structure Definitions
 *****************************************************************/

/*!
 * @struct TMEGenerateKeyPairMessageRequest
 * @brief Input structure of generate key pair message
 */

typedef struct PACKED_PREFIX tme_generate_key_pair_message_request_s
{
    TMEKeyConfig keyConfig; /*!< Key Config of the key pair's private key signifying its usage.
                                 Only ECDH and ECDSA related key config are allowed*/
} TMEGenerateKeyPairMessageRequest;

/*!
 * @struct TMEGenerateKeyPairMessageResponse
 * @brief Output structure of generate key pair message.
 */

typedef struct PACKED_PREFIX tme_generate_key_pair_message_response_s
{
    TMEStatus          status;           /*!< Status of the response */
    TMEResponseCBuffer publicKey;        /*!< Respone buffer to be filled by TME with
                                              the generated public key. Memory for the 
                                              containing buffer is to be allocated by
                                              the calling subsystem. And the calling sub
                                              system will set the length accordingly */
    TMEKeyHandle       privateKeyHandle; /*!< Key Handle of the generated private Key 
                                              stored in TME*/
} TMEGenerateKeyPairMessageResponse;

/*!
 * @struct TMEGenerateKeyPairMessage
 * @brief Structure of Generate Key pair message
 */

typedef struct PACKED_PREFIX tme_generate_key_pair_message_s
{
    TMEGenerateKeyPairMessageRequest  input;  /*!< Generate Key pair message's 
                                                   request */
    TMEGenerateKeyPairMessageResponse output; /*!< Generate Key pair message's 
                                                   response */
} TMEGenerateKeyPairMessage;

/*************************************************************
 *  ECC Get Public Key Request/Response Structure Definitions
 *************************************************************/

/*!
 * @struct TMEECCGetPublicKeyMessageRequest
 * @brief Input structure of ecc get public key message.
 */

typedef struct PACKED_PREFIX tme_ecc_get_public_key_message_request_s
{
    TMEECCCurve  curve;     /*!< The elliptic curve to be used */
    TMEKeyHandle keyHandle; /*!< Key Handle of the Private Key provided by TME */
} TMEECCGetPublicKeyMessageRequest;

/*!
 * @struct TMEECCGetPublicKeyMessageResponse
 * @brief Output structure of eccget public key message.
 */

typedef struct PACKED_PREFIX tme_ecc_get_public_key_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the public
                                      key. Memory for the containing buffer is to be 
                                      allocated by the calling subsystem. And the 
                                      calling sub system will set the length 
                                      accordingly */
} TMEECCGetPublicKeyMessageResponse;

/*!
 * @struct TMEECCGetPublicKeyMessage
 * @brief Structure of ecc get public key messaage.
 */

typedef struct PACKED_PREFIX tme_ecc_get_public_key_message_s
{
    TMEECCGetPublicKeyMessageRequest  input;  /*!< Get Public key message's 
                                                   request */
    TMEECCGetPublicKeyMessageResponse output; /*!< Get Public key message's 
                                                   response */
} TMEECCGetPublicKeyMessage;

/************************************************************
 *  ECDH Shared Secret Request/Response Structure Definitions
 ************************************************************/

/*!
 * @struct TMEECDHSharedSecretMessageRequest
 * @brief Input structure of generate ECDH shared secret message
 */

typedef struct PACKED_PREFIX tme_ecdh_shared_secret_message_request_s
{
    TMEECCCurve  curve;     /*!< The elliptic curve to be used */
    TMEKeyHandle keyHandle; /*!< Key handle of the private key provided by TME */
    TMECBuffer   publicKey; /*!< Input Buffer containing public key. The calling
                                 subsystem will allocate memory and fill the 
                                 buffer with the public key along with setting 
                                 the length */
    TMEKeyConfig keyConfig; /*!< Key Config of the shared secret to be generated
                                 signifying the key usage etc. */
} TMEECDHSharedSecretMessageRequest;

/*!
 * @struct TMEECDHSharedSecretMessageResponse
 * @brief Output structure of generate ECDH shared secret message.
 */

typedef struct PACKED_PREFIX tme_ecdh_shared_secret_message_response_s
{
    TMEStatus    status;    /*!< Status of the response */
    TMEKeyHandle keyHandle; /*!< Key handle of the shared secret provided by TME */

} TMEECDHSharedSecretMessageResponse;

/*!
 * @struct TMEECDHSharedSecretMessage
 * @brief Structure of generate ECDH Shared Secret message
 */

typedef struct PACKED_PREFIX tme_ecdh_shared_secret_message_s
{
    TMEECDHSharedSecretMessageRequest  input;  /*!< Generate Shared Secret 
                                                    message's request */
    TMEECDHSharedSecretMessageResponse output; /*!< Generate Shared Secret 
                                                    message's response */
} TMEECDHSharedSecretMessage;

/*************************************************************************
 *  ECDSA Signature calculation Request/Response Structure definitions for 
 *  a digest
 *************************************************************************/

/*!
 * @struct TMEECDSASignDigestMessageRequest
 * @brief Message's input structure to do ECDSA sign of a digest
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_digest_message_request_s
{
    TMEKeyHandle keyHandle; /*!< Key handle of the key provided by TME to be used
                                 for calculating signature*/
    TMEECCCurve  curve;     /*!< The elliptic curve to be used for calculating 
                                 signature */
    TMECBuffer   digest;    /*!< Input Buffer containing digest whose signature
                                 needs to be calculated. The calling subsystem 
                                 will allocate memory and fill the buffer with 
                                 the digest along with setting the length */
} TMEECDSASignDigestMessageRequest;

/*!
 * @struct TMEECDSASignDigestMessageResponse
 * @brief Message's output structure to do ECDSA sign of a digest
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_digest_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the 
                                      calculated signature. Memory for the containing 
                                      buffer is to be allocated by the calling subsystem. 
                                      And the calling sub system will set the length 
                                      accordingly */
} TMEECDSASignDigestMessageResponse;

/*!
 * @struct TMEECDSASignDigestMessage
 * @brief Message structure to do ECDSA sign of a digest.
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_digest_message_s
{
    TMEECDSASignDigestMessageRequest  input;  /*!< ECDSA sign digest message's
                                                   request */
    TMEECDSASignDigestMessageResponse output; /*!< ECDSA sign digest message's
                                                   response */
} TMEECDSASignDigestMessage;

/*****************************************************************************
 *  Digest ECDSA Signature verification Request/Response Structure definitions
 *****************************************************************************/

/*!
 * @struct TMEECDSAVerifyDigestMessageRequest
 * @brief Message's input structure to do ECDSA verification of a digest.
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_digest_message_request_s
{
    TMECBuffer  publicKey; /*!< Input Buffer containing the public key used for 
                                verifying signature. The calling subsystem will
                                allocate memory and fill the buffer with the 
                                public key along with setting the length */
    TMEECCCurve curve;     /*!< The elliptic curve to be used for calculating 
                                signature */
    TMECBuffer  digest;    /*!< Input Buffer containing digest whose signature 
                                needs to be calculated. The calling subsystem 
                                will allocate memory and fill the buffer with 
                                the digest along with setting the length */
    TMECBuffer  signature; /*!< Input Buffer containing the provided signature 
                                which needs to be verified. The calling subsystem
                                will allocate memory and fill the buffer with the
                                signature along with setting the length */
} TMEECDSAVerifyDigestMessageRequest;

/*!
 * @struct TMEECDSAVerifyDigestMessageResponse
 * @brief Message's output structure to do ECDSA verification of a digest.
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_digest_message_response_s
{
    TMEStatus status; /*!< Status of the response */
} TMEECDSAVerifyDigestMessageResponse;

/*!
 * @struct TMEECDSAVerifyDigestMessage
 * @brief Message structure to do ECDSA verification of a digest.
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_digest_message_s
{
    TMEECDSAVerifyDigestMessageRequest  input;  /*!< ECDSA verify digest message's
                                                    request */
    TMEECDSAVerifyDigestMessageResponse output; /*!< ECDSA verify digest message's
                                                     response */
} TMEECDSAVerifyDigestMessage;

/*************************************************************************
 *  ECDSA Signature calculation Request/Response Structure definitions for 
 *  a message
 *************************************************************************/

/*!
 * @struct TMEECDSASignBufferMessageRequest
 * @brief Message's input structure to do ECDSA sign of a buffer.
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_buffer_message_request_s
{
    TMEDigestAlgo algo;      /*!< Digest algorithm to be used for calculating 
                                  signature */
    TMEKeyHandle  keyHandle; /*!< Key Handle of the key provided by TME to be 
                                  used for calculating signature*/
    TMEECCCurve   curve;     /*!< The elliptic curve to be used for calculating 
                                  signature */
    TMECBuffer    message;   /*!< Input Buffer containing message whose signature
                                  needs to be calculated. The calling subsystem 
                                  will allocate memory and fill the buffer with
                                  the message along with setting the length */
} TMEECDSASignBufferMessageRequest;

/*!
 * @struct TMEECDSASignBufferMessageResponse
 * @brief Message's output structure to do ECDSA sign of a buffer.
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_buffer_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the 
                                      calculated signature. Memory for the containing 
                                      buffer is to be allocated by the calling subsystem.
                                      And the calling sub system will set the length 
                                      accordingly */
} TMEECDSASignBufferMessageResponse;

/*!
 * @struct TMEECDSASignBufferMessage
 * @brief Message structure to do ECDSA sign of a buffer.
 */

typedef struct PACKED_PREFIX tme_ecdsa_sign_buffer_message_s
{
    TMEECDSASignBufferMessageRequest  input;  /*!< ECDSA sign buffer message's
                                                   request */
    TMEECDSASignBufferMessageResponse output; /*!< ECDSA sign buffer message's 
                                                   response */
} TMEECDSASignBufferMessage;

/******************************************************************************
 *  Message ECDSA Signature verification Request/Response Structure definitions
 ******************************************************************************/

/*!
 * @struct TMEECDSAVerifyBufferMessageRequest
 * @brief Message's input structure to do ECDSA verification of a buffer
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_buffer_message_request_s
{
    TMEDigestAlgo algo;      /*!< Digest algorithm to be used for verifying 
                                  signature */
    TMECBuffer    publicKey; /*!< Input Buffer containing the public key used for
                                  verifying signature.The calling subsystem will
                                  allocate memory and fill the buffer with the 
                                  public key along with setting the length */
    TMEECCCurve   curve;     /*!< The elliptic curve to be used for calculating
                                  signature */
    TMECBuffer    message;   /*!< Input Buffer containing message whose signature
                                  needs to be calculated.The calling subsystem 
                                  will allocate memory and fill the buffer with
                                  the message along with setting the length */
    TMECBuffer    signature; /*!< Input Buffer containing the provided signature
                                  which needs to be verified.The calling subsystem
                                  will allocate memory and fill the buffer with 
                                  the signature along with setting the length */
} TMEECDSAVerifyBufferMessageRequest;

/*!
 * @struct TMEECDSAVerifyBufferMessageResponse
 * @brief Message's output structure to do ECDSA verification of a buffer.
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_buffer_message_response_s
{
    TMEStatus status; /*!< Status of the response */
} TMEECDSAVerifyBufferMessageResponse;

/*!
 * @struct TMEECDSAVerifyBufferMessage
 * @brief Message structure to do ECDSA verification of a buffer.
 */

typedef struct PACKED_PREFIX tme_ecdsa_verify_buffer_message_message_s
{
    TMEECDSAVerifyBufferMessageRequest  input;  /*!< ECDSA verify buffer message's
                                                     request */
    TMEECDSAVerifyBufferMessageResponse output; /*!< ECDSA verify buffer message's
                                                     response. */
} TMEECDSAVerifyBufferMessage;
// clang-format on
#endif /* TME_CRYPTO_ECC_INTERFACE_H */
