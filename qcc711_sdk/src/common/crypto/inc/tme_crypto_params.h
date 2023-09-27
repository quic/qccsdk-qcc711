/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_params.h
 * @brief The definitions of crypto parameters to be used across TME-FW.
 *
 */
#ifndef TME_CRYPTO_TYPES_H
#define TME_CRYPTO_TYPES_H

#include "packed.h"
#include "tme_types.h"

#define TME_DALG_BASE                (0x10000000) /*!<Base value for SHA Algos Enum */
#define TME_SALG_BASE                (0x11000000) /*!<Base value for AES Algos Enum */
#define TME_ECC_CURVE_BASE           (0x12000000) /*!<Base value for ECC Curves Enum */
#define TME_KEY_CONFIG_BASE          (0x13000000) /*!<Base value for Key Config Enum */
#define TME_KEY_DERIVATION_ALGO_BASE (0x14000000) /*!<Base value for key derivation Algos Enum */

/** TME Key Handle*/
typedef UINT32 TMEKeyHandle;

/*!
 * @enum TMEKeyConfig
 * @brief Represents the list of Key configurations supported by TME-FW.
 */

typedef enum tme_key_config_e
{
    TME_KEY_CONFIG_AES_GCM_128 = TME_KEY_CONFIG_BASE, /*!<AES128-GCM key config */
    TME_KEY_CONFIG_AES_GCM_256,                       /*!<AES256-GCM key config */
    TME_KEY_CONFIG_AES_CBC_128,                       /*!<AES128-CBC key config */
    TME_KEY_CONFIG_AES_CBC_256,                       /*!<AES256-CBC key config */
    TME_KEY_CONFIG_AES_CTR_128,                       /*!<AES128-CTR key config */
    TME_KEY_CONFIG_AES_CTR_256,                       /*!<AES256-CTR key config */
    TME_KEY_CONFIG_AES_ECB_128,                       /*!<AES128-ECB key config */
    TME_KEY_CONFIG_AES_ECB_256,                       /*!<AES256-ECB key config */
    TME_KEY_CONFIG_SHA_HMAC_256,                      /*!<SHA256-HMAC key config */
    TME_KEY_CONFIG_HKDF_128,                          /*!<HKDF-128 key config */
    TME_KEY_CONFIG_HKDF_256,                          /*!<HKDF-256 key config */
    TME_KEY_CONFIG_ECDSA_256,                         /*!<ECDSA 256 key config */
    TME_KEY_CONFIG_ECDSA_521,                         /*!<ECDSA 521 key config */
    TME_KEY_CONFIG_ECDH_256,                          /*!<ECDH 256 key config */
    TME_KEY_CONFIG_ECDH_384,                          /*!<ECDH 384 key config */
    TME_KEY_CONFIG_ECDH_521                           /*!<ECDH 521 key config */
} TMEKeyConfig;

/*!
 * @enum TMEDigestAlgo
 * @brief Represents the list of SHA Digest Algorithms supported by TME-FW.
 */

typedef enum tme_digest_algo_e
{
    TME_DALG_SHA256 = TME_DALG_BASE, /*!< SHA-256 Algorithm */
    TME_DALG_SHA384,                 /*!< SHA-384 Algorithm */
    TME_DALG_SHA512                  /*!< SHA-512 Algorithm */
} TMEDigestAlgo;

/*!
 * @enum TMEAESAlgo
 * @brief Represents the list of AES Algorithms supported by TME-FW.
 */

typedef enum tme_aes_algo_e
{
    TME_SALG_AES128_GCM = TME_SALG_BASE, /*!< AES128-GCM Algorithm*/
    TME_SALG_AES256_GCM,                 /*!< AES256-GCM Algorithm*/
    TME_SALG_AES128_CBC,                 /*!< AES128-CBC Algorithm*/
    TME_SALG_AES256_CBC,                 /*!< AES256-CBC Algorithm*/
    TME_SALG_AES128_CTR,                 /*!< AES128-CTR Algorithm*/
    TME_SALG_AES256_CTR,                 /*!< AES256-CTR Algorithm*/
    // Following are the algos to be used by BTSS specifically
    // TBD : To expose them separately from the above mentioned APPS
    //       related AES Algos.
    TME_SALG_AES128_ECB,                 /*!< AES128-ECB Algorithm*/
    TME_SALG_AES256_ECB                  /*!< AES256-ECB Algorithm*/
} TMEAESAlgo;

/*!
 * @enum TMEECCCurve
 * @brief Represents the list of ECC Curves supported by TME-FW.
 */

typedef enum tme_ecc_curve_e
{
    TME_ECC_CURVE_NIST_P256 = TME_ECC_CURVE_BASE, /*!< NIST-P256 Curve*/
    TME_ECC_CURVE_NIST_P384,                      /*!< NIST-P384 Curve*/
    TME_ECC_CURVE_NIST_P521                       /*!< NIST-P521 Curve*/
} TMEECCCurve;

/*!
 * @enum TMEKeyDerivationAlgo
 * @brief Represents the list of key derivation algorithm supported by TME-FW.
 */

typedef enum tme_key_derivation_algo_e
{
    TME_KEY_DERIVATION_ALGO_HKDF_128 =  TME_KEY_DERIVATION_ALGO_BASE, /*!< HKDF 128 algorithm*/
    TME_KEY_DERIVATION_ALGO_HKDF_256                                  /*!< HKDF 256 algorithm*/
} TMEKeyDerivationAlgo;

/*!
 * @struct TMEAESEncryptionRequestParameters
 * @brief Structure containing common AES Encryption request parameters.
 */

typedef struct PACKED_PREFIX tme_aes_encryption_request_parameters_s
{
    TMEAESAlgo algo;  /*!< AES Algorithm to be used in encryption. */
    TMECBuffer plain; /*!< Input Buffer containing the plain text to be encrypted.
                           The calling subsystem will allocate memory and fill 
                           the buffer with the plain text along with setting 
                           the length */
    TMECBuffer AAD;   /*!< Optional - Additional Authentication Data Buffer. 
                           Optional input buffer used only in AES-GCM.If used, 
                           the calling subsystem will allocate memory and fill
                           the buffer with the AAD along with setting the 
                           length */
} TMEAESEncryptionRequestParameters;

/*!
 * @struct TMEAESEncryptionResponseParameters
 * @brief Structure containing common AES Encryption response parameters.
 */

typedef struct PACKED_PREFIX tme_aes_encryption_response_parameters_s
{
    TMEResponseCBuffer  encrypted; /*!< Response buffer to be filled by TME with the 
                                        encrypted data. Memory for the containing buffer
                                        is to be allocated by the calling subsystem.
                                        And the calling sub system will set the length 
                                        accordingly.*/
    TMEResponseCBuffer  IV;        /*!< Optional - Randomly Generated Initialisation 
                                        Vector Buffer used for encryption in mode like 
                                        CBC, CCM, GCM, OFB, CTR etc. but not in ECB 
                                        If generated, the calling subsystem will 
                                        allocate memory and fill the buffer with the
                                        IV along with setting the length */
    TMEResponseCBuffer  tag;       /*!< Optional - Authentication Tag Buffer, generated
                                        in AES-GCM  If generated, the calling subsystem
                                        will allocate memory and fill the buffer with 
                                        the authentication tag along with setting the 
                                        length */
} TMEAESEncryptionResponseParameters;

/*!
 * @struct TMEAESDecryptionRequestParameters
 * @brief Structure containing common AES Decryption request parameters.
 */

typedef struct PACKED_PREFIX tme_aes_decryption_request_parameters_s
{
    TMEAESAlgo  algo;      /*!< AES Algorithm to be used in decryption */
    TMECBuffer  encrypted; /*!< Input Buffer containing the encrypted data to be
                                decrypted. The calling subsystem will allocate 
                                memory and fill the buffer with the encrypted 
                                data along with setting the length */
    TMECBuffer  IV;        /*!< Optional - Initialisation Vector Buffer used 
                                for encryption in mode like CBC, CCM, GCM, OFB,
                                CTR etc. but not in ECB. If used, the calling 
                                subsystem will allocate memory and fill the 
                                buffer with the IV along with setting the 
                                length */
    TMECBuffer  AAD;       /*!< Optional - Additional Authentication Data Buffer
                                Optional buffer used only in AES-GCM. If used,
                                the calling subsystem will allocate memory and 
                                fill the buffer with the AAD along with setting 
                                the length */
    TMECBuffer  tag;       /*!< Optional - Authentication Tag Buffer, generated
                                in AES-GCM Encryption. If used, the calling 
                                subsystem will allocate memory and fill the 
                                buffer with the tag along with setting the 
                                length */
} TMEAESDecryptionRequestParameters;
// clang-format on
#endif /* TME_CRYPTO_TYPES_H */
