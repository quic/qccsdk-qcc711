/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_keys_interface.h
 * @brief IPC's key management related interfaces for TME-FW Crypto Service.
          Defines structures for the following crypto requests
 *        <br>Import Key
 *        <br>Clear Key
 *        <br>Derive Key
 *        <br>Generate Key
 */
#ifndef TME_CRYPTO_KEYS_INTERFACE_H
#define TME_CRYPTO_KEYS_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/****************************************************
 *  Import Key Request/Response Structure Definitions
 ****************************************************/

/*!
 * @struct TMEImportKeyRequest
 * @brief Input structure of import key message.
 */

typedef struct PACKED_PREFIX tme_import_key_message_request_s
{
    TMECBuffer   keyMaterial; /*!< Input Buffer containing key to be imported in
                                   TME. The calling subsystem will allocate memory 
                                   and fill the buffer with the key along with 
                                   setting the length */
    TMEKeyConfig keyConfig;   /*!< Key Config of the key to be imported. */
} TMEImportKeyRequest;

/*!
 * @struct TMEImportKeyResponse
 * @brief Output structure of import key message.
 */

typedef struct PACKED_PREFIX tme_import_key_message_response_s
{
    TMEStatus    status;    /*!< Status of the response */
    TMEKeyHandle keyHandle; /*!< TME Handle of the imported key. */
} TMEImportKeyResponse;

/*!
 * @struct TMEImportKeyMessage
 * @brief Structure of Import Key message.
 */

typedef struct PACKED_PREFIX tme_import_key_message_s
{
    TMEImportKeyRequest  input;  /*!< Import Key message's request */
    TMEImportKeyResponse output; /*!< Import Key message's response */
} TMEImportKeyMessage;

/****************************************************
 *  Clear Key Request/Response Structure Definitions
 ****************************************************/

/*!
 * @struct TMEClearKeyRequest
 * @brief Input structure of clear key message.
 */

typedef struct PACKED_PREFIX tme_clear_key_message_request_s
{
    TMEKeyHandle  keyHandle; /*!< Handle of the key stored in TME which needs 
                                  to be cleared.*/
} TMEClearKeyRequest;

/*!
 * @struct TMEClearKeyResponse
 * @brief Output structure of clear key message.
 */

typedef struct PACKED_PREFIX tme_clear_key_message_response_s
{
    TMEStatus status; /*!< Status of the response */
} TMEClearKeyResponse;

/*!
 * @struct TMEClearKeyMessage
 * @brief Structure of Clear Key message.
 */

typedef struct PACKED_PREFIX tme_clear_key_message_s
{
    TMEClearKeyRequest  input;  /*!< Clear Key message's request */
    TMEClearKeyResponse output; /*!< Clear Key message's response */
} TMEClearKeyMessage;

/*!
 * @struct TMEDeriveKeyRequest
 * @brief Input structure of derive key message.
 */

typedef struct PACKED_PREFIX tme_derive_key_message_request_s
{
    TMECBuffer           nonce;             /*!< Nonce to be used for key derivation. It can
                                                 be of maximum 32 bytes. */
    TMEKeyDerivationAlgo keyDerivationAlgo; /*!< Algorithm to be used for key derivation */
    TMEKeyConfig         keyConfig;         /*!< Key config data signifying key type, length, 
                                                 algorithm of key to be derived */
    TMEKeyHandle         inKey;             /*!< The key to be used as input key for deriving 
                                                 key */
    TMECBuffer           label;             /*!< Label to be used for key derivation. It can
                                                 be of maximum 32 bytes. */
} TMEDeriveKeyRequest;

/*!
 * @struct TMEDeriveKeyResponse
 * @brief Output structure of derive key message.
 */

typedef struct PACKED_PREFIX tme_derive_key_message_response_s
{
    TMEStatus    status;     /*!< Status of the response */
    TMEKeyHandle derivedKey; /*!< Handle of the derived key */
} TMEDeriveKeyResponse;

/*!
 * @struct TMEDeriveKeyMessage
 * @brief Structure of derive key message.
 */

typedef struct PACKED_PREFIX tme_derive_key_messsage_s
{
    TMEDeriveKeyRequest  input;  /*!< Derive key message's request*/
    TMEDeriveKeyResponse output; /*!< Derive key message's response*/
} TMEDeriveKeyMessage;

/*******************************************************
 *  Generate Key Request/Response Structure Definitions
 *******************************************************/

/*!
 * @struct TMEGenerateKeyRequest
 * @brief Input structure of generate key message.
 */

typedef struct PACKED_PREFIX tme_generate_key_message_request_s
{
    TMEKeyConfig keyConfig;   /*!< Key Config of the key to be generated. */
} TMEGenerateKeyRequest;

/*!
 * @struct TMEGenerateKeyResponse
 * @brief Output structure of generate key message.
 */

typedef struct PACKED_PREFIX tme_generate_key_message_response_s
{
    TMEStatus    status;    /*!< Status of the response */
    TMEKeyHandle keyHandle; /*!< TME Handle of the generated key. */
} TMEGenerateKeyResponse;

/*!
 * @struct TMEGenerateKeyMessage
 * @brief Structure of generate key message.
 */

typedef struct PACKED_PREFIX tme_generate_key_message_s
{
    TMEGenerateKeyRequest  input;  /*!< Generate Key message's request */
    TMEGenerateKeyResponse output; /*!< Generate Key message's response */
} TMEGenerateKeyMessage;

// clang-format on
#endif /* TME_CRYPTO_KEYS_INTERFACE_H */
