/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_ex_interface.h
 * @brief IPC's BTSS Specific interfaces for TME-FW Crypto Service.Defines
 *        structures for the following crypto requests :
 *        <br>Get Random ECC Field value
 *        <br>ECC Multiply point by generator
 *        <br>ECC Multiply point by value
 *        <br>Extended AES Encryption
 *        <br>Extended AES Decryption
 *        <br>Get license status
 */
#ifndef TME_CRYPTO_EX_INTERFACE_H
#define TME_CRYPTO_EX_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/*! ESL license feature bit shift */
#define ESL_LICENSE_FEATURE_BIT_SHIFT (0)

/*! ESL license feature mask */
#define ESL_LICENSE_FEATURE_MASK (1)

/*! ESL license feature mask */
#define ESL_LICENSE_FEATURE_BITMASK (ESL_LICENSE_FEATURE_MASK << ESL_LICENSE_FEATURE_BIT_SHIFT)

/*! TME license status */
typedef UINT32 TMEFeatureLicenseStatus;

/*! TME Feature mask */
typedef UINT32 TMEFeatureMask;

/*****************************************************************************
 Generation of Shared Secret by BTSS will involve invocation of 3 TME-FW APIs
 1. Generate Random ECC Field Value i.e. Private Key for an EC Curve
 2. Multiply ECC Value by Generator Value to get Public Key
 3. Multiply ECC value by Point to get Shared Secret from Private and Public 
    key for given EC Curve
 *****************************************************************************/

/****************************************************************
 *  ECC Random Field Value Request/Response Structure Definitions
 ****************************************************************/

/*!
 * @struct TMEGetRandomECCFieldValueRequest
 * @brief Input structure of generate random ECC field value message.
 */

typedef struct PACKED_PREFIX tme_get_random_ecc_field_value_request_s
{
    TMEECCCurve  curve; /*!< The elliptic curve for which the random field value
                             needs to be generated.*/
} TMEGetRandomECCFieldValueRequest;

/*!
 * @struct TMEGetRandomECCFieldValueResponse
 * @brief Output structure of generate random ECC field value message.
 */

typedef struct PACKED_PREFIX tme_get_random_ecc_field_value_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with the 
                                      generated random ECC field value.Memory for the
                                      containing buffer is to be allocated by the 
                                      calling subsystem. And the calling sub system 
                                      will set the length accordingly.*/
} TMEGetRandomECCFieldValueResponse;

/*!
 * @struct TMEGetRandomECCFieldValueMessage
 * @brief Structure of generate random ECC field value message.
 */

typedef struct PACKED_PREFIX tme_get_random_ecc_field_value_message_s
{
    TMEGetRandomECCFieldValueRequest   input;  /*!< Generate random ECC field 
                                                    value message's request */
    TMEGetRandomECCFieldValueResponse  output; /*!< Generate random ECC field 
                                                    value message's response */
} TMEGetRandomECCFieldValueMessage;

/************************************************************************
 * ECC Multiplication by generator Request/Response Structure Definitions
 ************************************************************************/

/*!
 * @struct TMEECCMultiplyPointByGeneratorMessageRequest
 * @brief Input structure of multiply ECC value by generator message.
 */

typedef struct PACKED_PREFIX
    tme_ecc_multiply_point_by_generator_message_request_s
{
    TMEECCCurve  curve;      /*!< The elliptic curve whose value will be multiplied
                                  by generator value to extract public key */
    TMECBuffer   privateKey; /*!< Input Buffer containing private key. The calling
                                  subsystem will allocate memory and fill the 
                                  buffer with the private key along with setting
                                  the length */
} TMEECCMultiplyPointByGeneratorMessageRequest;

/*!
 * @struct TMEECCMultiplyPointByGeneratorMessageResponse
 * @brief Output structure of multiply ECC value by generator message.
 */

typedef struct PACKED_PREFIX
    tme_ecc_multiply_point_by_generator_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with the product
                                      of multiplication. Memory for the containing buffer
                                      is to be allocated by the calling subsystem. And 
                                      the calling sub system will set the length 
                                      accordingly */
} TMEECCMultiplyPointByGeneratorMessageResponse;

/*!
 * @struct TMEECCMultiplyPointByGeneratorMessage
 * @brief Structure of extended ecc get public key message having 
 * key in plain text as input.
 */

typedef struct PACKED_PREFIX tme_ecc_multiply_point_by_generator_message_s
{
    TMEECCMultiplyPointByGeneratorMessageRequest  input;  /*!< Multiply ECC value
                                                               by generator 
                                                               message's request */
    TMEECCMultiplyPointByGeneratorMessageResponse output; /*!< Multiply ECC value
                                                               by generator 
                                                               message's response */
} TMEECCMultiplyPointByGeneratorMessage;

/*********************************************************************
 *  ECC Multiplication by value Request/Response Structure Definitions
 *********************************************************************/

/*!
 * @struct TMEECCMultiplyPointByValueMessageRequest
 * @brief Input structure of multiply ECC value by point message
 */

typedef struct PACKED_PREFIX tme_ecc_multiply_point_by_value_message_request_s
{
    TMEECCCurve curve;      /*!< The elliptic curve whose value will be multiplied
                                 by point to get shared secret */
    TMECBuffer  privateKey; /*!< Input Buffer containing private key. The calling
                                 subsystem will allocate memory and fill the 
                                 buffer with the private key along with setting
                                 the length */
    TMECBuffer  publicKey;  /*!< Input Buffer containing public key. The calling 
                                 subsystem will allocate memory and fill the 
                                 buffer with the public key along with setting 
                                 the length */
} TMEECCMultiplyPointByValueMessageRequest;

/*!
 * @struct TMEECCMultiplyPointByValueMessageResponse
 * @brief Output structure of multiply ECC value by point message.
 */

typedef struct PACKED_PREFIX tme_ecc_multiply_point_by_value_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with the product
                                      of multiplication. Memory for the containing buffer
                                      is to be allocated by the calling subsystem. And 
                                      the calling sub system will set the length 
                                      accordingly */
} TMEECCMultiplyPointByValueMessageResponse;

/*!
 * @struct TMEECCMultiplyPointByValueMessage
 * @brief Structure of multiply ECC value by point message
 */

typedef struct PACKED_PREFIX tme_ecc_multiply_point_by_value_message_s
{
    TMEECCMultiplyPointByValueMessageRequest  input;  /*!< Multiply ECC value by
                                                           point message's 
                                                           request */
    TMEECCMultiplyPointByValueMessageResponse output; /*!< Multiply ECC value by
                                                           point message's 
                                                           response */
} TMEECCMultiplyPointByValueMessage;

/**************************************************************************
 * AES Encryption Request/Response Structure Definitions for plain text key
 **************************************************************************/

/*!
 * @struct TMEAESEncryptionExMessageRequest
 * @brief Input structure of AES encryption message.When a valid key handle is 
 *        provided, then the key buffer is expected to be set to NULL with key 
 *        length set as 0. And in case valid key buffer containing bytes of valid
 *        plain text key is provided then key handle will not be considered 
 *        irrespective of it value.
 */

typedef struct PACKED_PREFIX tme_aes_encryption_ex_message_request_s
{
    TMECBuffer                        key;       /*!< Input Buffer containing 
                                                      key to be used in encryption.
                                                      The calling subsystem will 
                                                      allocate memory and fill 
                                                      the buffer with the key 
                                                      along with setting the 
                                                      length. To be used by 
                                                      BTSS only*/
    TMEKeyHandle                      keyHandle; /*!< Handle of the key stored
                                                      in TME to be used for
                                                      decryption. To be used by 
                                                      APSS only */
    TMEAESEncryptionRequestParameters reqParams; /*!< AES Encryption request 
                                                      parameters */
} TMEAESEncryptionExMessageRequest;

/*!
 * @struct TMEAESEncryptionExMessageResponse
 * @brief Output structure of AES Encryption message with plain text key.
 */

typedef struct PACKED_PREFIX tme_aes_encryption_ex_message_response_s
{
    TMEStatus status;                             /*!< Status of the response */
    TMEAESEncryptionResponseParameters rspParams; /*!< AES Encryption response 
                                                       parameters.*/
} TMEAESEncryptionExMessageResponse;

/*!
 * @struct TMEAESEncryptionExMessage
 * @brief Structure of AES Encryption message with plain text key.
 */

typedef struct PACKED_PREFIX tme_aes_encryption_ex_message_s
{
    TMEAESEncryptionExMessageRequest  input;  /*!< AES Encryption message's 
                                                   request with plain text 
                                                   key */
    TMEAESEncryptionExMessageResponse output; /*!< AES Encryption message's 
                                                   response with plain text 
                                                   key */
} TMEAESEncryptionExMessage;

/***************************************************************************
 *  AES Decryption Request/Response Structure Definitions for plain text key
 ***************************************************************************/

/*!
 * @struct TMEAESDecryptionExMessageRequest
 * @brief Input structure of AES Decryption message.When a valid key handle is 
 *        provided, then the key buffer is expected to be set to NULL with key 
 *        length set as 0. And in case valid key buffer containing bytes of valid
 *        plain text key is provided then key handle will not be considered 
 *        irrespective of it value.
 */

typedef struct PACKED_PREFIX tme_aes_decryption_ex_message_request_s
{
    TMECBuffer                        key;       /*!< Input Buffer containing 
                                                      key to be used in 
                                                      decryption. The calling 
                                                      subsystem will allocate 
                                                      memory and fill the 
                                                      buffer with the key along
                                                      with setting the length.
                                                      To be used by BTSS only. */
    TMEKeyHandle                      keyHandle; /*!< Handle of the key stored
                                                      in TME to be used for 
                                                      decryption. To be used 
                                                      by APSS only. */
    TMEAESDecryptionRequestParameters reqParams; /*!< AES Decryption Request 
                                                      Parameter */
} TMEAESDecryptionExMessageRequest;

/*!
 * @struct TMEAESDecryptionExMessageResponse
 * @brief Output structure of AES Decryption message with plain text key.
 */

typedef struct PACKED_PREFIX tme_aes_decryption_ex_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with the 
                                      decrypted plain text. Memory for the containing
                                      buffer is to be allocated by the calling 
                                      subsystem. And the calling sub system will set 
                                      the length accordingly */
} TMEAESDecryptionExMessageResponse;

/*!
 * @struct TMEAESDecryptionExMessage
 * @brief Structure of AES Decryption message with plain text key.
 */

typedef struct PACKED_PREFIX tme_aes_decryption_ex_messsage_s
{
    TMEAESDecryptionExMessageRequest  input;  /*!< AES Decryption message's
                                                   request with plain text 
                                                   key */
    TMEAESDecryptionExMessageResponse output; /*!< AES Decryption message's 
                                                   response with plain text 
                                                   key*/
} TMEAESDecryptionExMessage;

/*************************************************************
 *  Get license status request/response structure definitions
 *************************************************************/

/*!
 * @struct TMEGetLicenseStatusMessageRequest
 * @brief Input structure of get license status message.
 */

typedef struct PACKED_PREFIX tme_get_license_status_message_request_s
{
  TMEFeatureMask featureMask;  /*!< Feature bit mask, each bit represents
                                    a feature */
} TMEGetLicenseStatusMessageRequest;

/*!
 * @struct TMEGetLicenseStatusMessageResponse
 * @brief Output structure of get license status message.
 */

typedef struct PACKED_PREFIX tme_get_license_status_message_response_s
{
  TMEStatus               status;        /*!< Status of the message */
  TMEFeatureLicenseStatus licenseStatus; /*!< License status to be filled by
                                              TME from AON_PME_ROT_SCRATCHPAD
                                              register */
} TMEGetLicenseStatusMessageResponse;

/*!
 * @struct TMEGetLicenseStatusMessage
 * @brief Structure of get license status message.
 */

typedef struct PACKED_PREFIX tme_get_license_status_message_s
{
  TMEGetLicenseStatusMessageRequest  input;  /*!< Get license status message's
                                                  request */
  TMEGetLicenseStatusMessageResponse output; /*!< Get license status message's
                                                  response */
} TMEGetLicenseStatusMessage;

// clang-format on
#endif /* TME_CRYPTO_EX_INTERFACE_H */
