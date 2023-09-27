/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
*  @file qapi_crypto.h
*  @brief Crypto APIs, types and definitions.

    This module enables the usage of the crypto hardware on the SoC to perform
    operations like digest, HMAC, message signing, verification etc.

    These APIs provide high level interfaces for cryptographic operations, and
    support blocking and non-blocking modes of operation. The supplied callback
    is used only in case of non-blocking modes.
    Note: Callback is executed in interrupt context, and should be released immediately. 
    Calling other QAPIs from the callback is not supported.

    The flow for a typical blocking operation is shown below:

    @msc
    arcgradient = 0, width="1000";
    Application, Crypto_Module;
    Application => Crypto_Module [label="Import/DeriveKey"];
    Crypto_Module => Application [label="Key handle"];
    |||;
    |||;
    Application => Crypto_Module [label="Perform operation (e.g. HMAC, encrypt, ECDSA sign) using key handle"];
    Crypto_Module => Application [label="Operation result"];
    |||;
    |||;
    Application => Crypto_Module [label="Clear key"];
    Crypto_Module => Application [label="Resources released"];
    |||;
    |||;
    @endmsc

*/

#ifndef __QAPI_CRYPTO_H__
#define __QAPI_CRYPTO_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"
#include "qapi_crypto_common.h"

/** @addtogroup qapi_platform_crypto
@{ */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Enumeration of supported key configurations, expressed as algorithm and key lengths. */
typedef enum
{
   QAPI_CRPT_KEY_ALGO_AES_GCM_128_E,  /**< AES-GCM 128-bit. */
   QAPI_CRPT_KEY_ALGO_AES_GCM_256_E,  /**< AES-GCM 256-bit. */
   QAPI_CRPT_KEY_ALGO_AES_CBC_128_E,  /**< AES-CBC 128-bit. */
   QAPI_CRPT_KEY_ALGO_AES_CBC_256_E,  /**< AES-CBC 256-bit. */
   QAPI_CRPT_KEY_ALGO_AES_CTR_128_E,  /**< AES-CTR 128-bit. */
   QAPI_CRPT_KEY_ALGO_AES_CTR_256_E,  /**< AES-CTR 256-bit. */
   QAPI_CRPT_KEY_ALGO_SHA_HMAC_256_E, /**< SHA-HMAC 256-bit. */
   QAPI_CRPT_KEY_ALGO_HKDF_128_E,     /**< HKDF (Pseudo Random Function-HMAC256) 128-bit. */
   QAPI_CRPT_KEY_ALGO_HKDF_256_E,     /**< HKDF (Pseudo Random Function-HMAC256) 256-bit. */
   QAPI_CRPT_KEY_ALGO_ECDSA_256_E,    /**< NIST P-256 based ECDSA. */
   QAPI_CRPT_KEY_ALGO_ECDSA_521_E,    /**< NIST P-521 based ECDSA. */
   QAPI_CRPT_KEY_ALGO_ECDH_256_E,     /**< NIST P-256 based ECDH. */
   QAPI_CRPT_KEY_ALGO_ECDH_521_E      /**< NIST P-521 based ECDH. */
} qapi_CRPT_Key_Algo_t;

/** Enumeration of supported crypto operations. */
typedef enum
{
   QAPI_CRPT_OPERATION_IMPORT_KEY_E,          /**< Import key. */
   QAPI_CRPT_OPERATION_CLEAR_KEY_E,           /**< Clear key. */
   QAPI_CRPT_OPERATION_DERIVE_KEY_E,          /**< Derive key. */
   QAPI_CRPT_OPERATION_DIGEST_E,              /**< Message hash. */
   QAPI_CRPT_OPERATION_ENCRYPT_E,             /**< Encryption. */
   QAPI_CRPT_OPERATION_DECRYPT_E,             /**< Decryption. */
   QAPI_CRPT_OPERATION_RNG_E,                 /**< Random number generation. */
   QAPI_CRPT_OPERATION_HMAC_E,                /**< Hashed MAC. */
   QAPI_CRPT_OPERATION_GENERATE_KEY_PAIR_E,   /**< Generate key pair. */
   QAPI_CRPT_OPERATION_ECC_GET_PUBLIC_KEY_E,  /**< Get ECC public key. */
   QAPI_CRPT_OPERATION_ECDH_SHARED_SECRET_E,  /**< ECDH shared secret. */
   QAPI_CRPT_OPERATION_ECDSA_SIGN_DIGEST_E,   /**< ECDSA sign digest. */
   QAPI_CRPT_OPERATION_ECDSA_VERIFY_DIGEST_E, /**< ECDSA verify digest. */
   QAPI_CRPT_OPERATION_ECDSA_SIGN_MESSAGE_E,  /**< ECDSA sign message. */
   QAPI_CRPT_OPERATION_ECDSA_VERIFY_MESSAGE_E /**< ECDSA verify message. */
} qapi_CRPT_Operation_t;

/** Enumeration of supported digest algorithms. */
typedef enum
{
   QAPI_CRPT_DIGEST_ALGO_SHA256_E, /**< SHA-256 algorithm. */
   QAPI_CRPT_DIGEST_ALGO_SHA512_E  /**< SHA-512 algorithm. */
} qapi_CRPT_Digest_Algo_t;

/** Enumeration of supported AES algorithms. */
typedef enum
{
   QAPI_CRPT_AES_ALGO_AES128_GCM_E, /**< AES128-GCM algorithm. */
   QAPI_CRPT_AES_ALGO_AES256_GCM_E, /**< AES256-GCM algorithm. */
   QAPI_CRPT_AES_ALGO_AES128_CBC_E, /**< AES128-CBC algorithm. */
   QAPI_CRPT_AES_ALGO_AES256_CBC_E, /**< AES256-CBC algorithm. */
   QAPI_CRPT_AES_ALGO_AES128_CTR_E, /**< AES128-CTR algorithm. */
   QAPI_CRPT_AES_ALGO_AES256_CTR_E  /**< AES256-CTR algorithm. */
} qapi_CRPT_AES_Algo_t;

/** Enumeration of supported ECC curves. */
typedef enum
{
   QAPI_CRPT_ECC_CURVE_NIST_P256_E, /**< NIST-P256 curve. */
   QAPI_CRPT_ECC_CURVE_NIST_P521_E  /**< NIST-P521 curve. */
} qapi_CRPT_ECC_Curve_t;

/** Fixed key handle for batch secret. This handle can only be used as a base key handle in the API qapi_CRPT_Derive_Key(). */
#define BATCH_SECRET_HANDLE   ((qapi_CRPT_Key_Handle_t)(113))

/** Structure representing the parameters required to perform the import key operation. */
typedef struct qapi_CRPT_Import_Key_Params_s
{
   uint32_t                KeyLen;    /**< Length of the key to be imported, in bytes. */
   uint8_t                *Key;       /**< Key to be imported. */
   qapi_CRPT_Key_Algo_t    KeyAlgo;   /**< Algorithm to be associated with this key. */
   qapi_CRPT_Key_Handle_t  KeyHandle; /**< Handle for the imported key(out). */
} qapi_CRPT_Import_Key_Params_t;

/** Structure representing the parameters required to perform the clear key operation. */
typedef struct qapi_CRPT_Clear_Key_Params_s
{
   qapi_CRPT_Key_Handle_t KeyHandle; /**< Handle for the key to be cleared. */
} qapi_CRPT_Clear_Key_Params_t;

/** Structure representing the parameters required to perform the derive key operation. */
typedef struct qapi_CRPT_Derive_Key_Params_s
{
   qapi_CRPT_Key_Algo_t    KeyAlgo;          /**< Algorithm to be associated with the derived key. */
   qapi_CRPT_Key_Handle_t  BaseKeyHandle;    /**< Handle for the base key to be used for key derivation. */
   uint32_t                NonceLen;         /**< Nonce length in bytes. Allowed length is 32 bytes. */
   uint8_t                *Nonce;            /**< Optional Nonce(a random number). */
   char                   *Label;            /**< Optional free form label, such as <em>FW Update</em>.
                                                  The maximum allowed length of the string (including the NULL 
                                                  character is 32 bytes). */
   qapi_CRPT_Key_Handle_t  DerivedKeyHandle; /**< Handle for the derived key(out). */
}  qapi_CRPT_Derive_Key_Params_t;

/** Structure representing the parameters required to perform the random number generation operation. */
typedef struct qapi_CRPT_RNG_Params_s
{
   uint32_t  RandomNumberLen; /**< Length of the random number to be generated, in bytes.
                                   The allowed range is from 1 to 64 bytes. */
   uint8_t  *RandomNumber;    /**< Buffer allocated by the application for placing
                                   output random number. This should be of the same size
                                   as RandomNumberLen. */
} qapi_CRPT_RNG_Params_t;

/** Structure representing the parameters required to perform the digest operation. */
typedef struct qapi_CRPT_Digest_Params_s
{
   qapi_CRPT_Digest_Algo_t  Algo;          /**< Digest algorithm. */
   uint32_t                 MessageLen;    /**< Message length in bytes. */
   uint8_t                 *Message;       /**< Message to calculate digest on. */
   uint32_t                 DigestLen;     /**< Digest buffer length in bytes. */
   uint8_t                 *Digest;        /**< Buffer allocated by the application for
                                                placing output digest. */
   uint32_t                 DigestLenUsed; /**< Digest buffer length used in bytes. */
} qapi_CRPT_Digest_Params_t;

/** Structure representing the parameters required to perform the HMAC operation. */
typedef struct qapi_CRPT_HMAC_256_Params_s
{
   qapi_CRPT_Key_Handle_t   KeyHandle;   /**< Handle for the key to be used for HMAC. */
   uint32_t                 MessageLen;  /**< Message length in bytes. */
   uint8_t                 *Message;     /**< Message to calculate HMAC on. */
   uint32_t                 HMACLen;     /**< HMAC buffer length in bytes. */
   uint8_t                 *HMAC;        /**< Buffer allocated by the application for placing output HMAC. */
   uint32_t                 HMACLenUsed; /**< HMAC buffer length used in bytes. */
} qapi_CRPT_HMAC_256_Params_t;

/** Structure representing the parameters required to perform the AES decryption. */
typedef struct qapi_CRPT_AES_Decryption_Params_s
{
   qapi_CRPT_AES_Algo_t    Algo;             /**< AES algorithm. */
   qapi_CRPT_Key_Handle_t  KeyHandle;        /**< Handle for the key to be used for decryption. */
   uint32_t                EncryptedDataLen; /**< Encrypted data length in bytes. */
   uint8_t                *EncryptedData;    /**< Encrypted data. */
   uint32_t                IVLen;            /**< Initialisation vector length in bytes. 
                                                  IV length for various AES modes is listed below.
                                                  QAPI_CRPT_AES_ALGO_AES128_GCM_E: 12 bytes
                                                  QAPI_CRPT_AES_ALGO_AES256_GCM_E: 12 bytes
                                                  QAPI_CRPT_AES_ALGO_AES128_CBC_E: 16 bytes
                                                  QAPI_CRPT_AES_ALGO_AES256_CBC_E: 16 bytes
                                                  QAPI_CRPT_AES_ALGO_AES128_CTR_E: 16 bytes
                                                  QAPI_CRPT_AES_ALGO_AES256_CTR_E: 16 bytes
                                                  Set to 0, if IV is not applicable. */
   uint8_t                *IV;               /**< Initialisation vector. Not applicable for ECB. Set to NULL,
                                                  if not applicable. */
   uint32_t                AADLen;           /**< AAD length in bytes. Set to 0, if AAD is not applicable. */
   uint8_t                *AAD;              /**< Optional Additional Authentication Data(AAD). Applicable only for GCM. 
                                                  Set to NULL, if not applicable. */
   uint32_t                TagLen;           /**< Authentication tag length in bytes. Set to 0, if Tag is not applicable. */
   uint8_t                *Tag;              /**< Authentication tag. Applicable only in GCM. Set to NULL, if not applicable. */
   uint32_t                PlainTextLen;     /**< PlainText length in bytes. Maximum size supported is 4096 bytes.*/
   uint8_t                *PlainText;        /**< Buffer allocated by the application for placing output plain text. */
   uint32_t                PlainTextLenUsed; /**< PlainText length used in bytes. */
} qapi_CRPT_AES_Decryption_Params_t;

/** Structure representing the parameters required to perform the AES encryption. */
typedef struct qapi_CRPT_AES_Encryption_Params_s
{
   qapi_CRPT_AES_Algo_t    Algo;                 /**< AES algorithm */
   qapi_CRPT_Key_Handle_t  KeyHandle;            /**< Handle for the key to be used for encryption.*/
   uint32_t                PlainTextLen;         /**< Plain text length in bytes. */
   uint8_t                *PlainText;            /**< Data(plaintext) to be encrypted. For encryption using CBC mode,
                                                      length should be a multiple of 16 bytes.*/
   uint32_t                AADLen;               /**< AAD length in bytes. Set to 0, if AAD is not applicable. */
   uint8_t                *AAD;                  /**< Optional Additional Authentication Data(AAD). Applicable only for GCM.
                                                      Set to NULL, if not applicable. */
   uint32_t                EncryptedDataLen;     /**< Encrypted buffer length in bytes. Maximum size supported is 4096 bytes.*/
   uint8_t                *EncryptedData;        /**< Buffer allocated by the application for placing output encrypted data. */
   uint32_t                EncryptedDataLenUsed; /**< Encrypted buffer length used in bytes. */
   uint32_t                IVLen;                /**< Initialisation vector length in bytes. Set to 0, if IV is not applicable. */
   uint8_t                *IV;                   /**< Buffer allocated by the application for placing output IV.
                                                      Not applicable for ECB. Set to NULL, if not applicable. */
   uint32_t                IVLenUsed;            /**< Initialisation vector length used in bytes. Set to 0, if IV is not applicable. */
   uint32_t                TagLen;               /**< Tag(authentication) length in bytes. */
   uint8_t                *Tag;                  /**< Buffer allocated by the application for placing authentication tag.
                                                      Applicable only for GCM. For encryption using GCM mode, a tag of 
                                                      length 4 bytes is supported. */
   uint32_t                TagLenUsed;           /**< Tag(authentication) length used in bytes. */
} qapi_CRPT_AES_Encryption_Params_t;

/** Structure representing the parameters required to perform the generate key pair. */
typedef struct qapi_CRPT_Generate_Key_Pair_Params_s
{
   qapi_CRPT_Key_Algo_t    KeyAlgo;          /**< Algorithm to be associated with the private key.
                                                  Allowed algorithms are listed below:-
                                                  QAPI_CRPT_KEY_ALGO_ECDSA_256_E,
                                                  QAPI_CRPT_KEY_ALGO_ECDSA_521_E,
                                                  QAPI_CRPT_KEY_ALGO_ECDH_256_E,
                                                  QAPI_CRPT_KEY_ALGO_ECDH_521_E */
   uint32_t                PublicKeyLen;     /**< PublicKey length in bytes. */
   uint8_t                *PublicKey;        /**< Buffer allocated by the application for placing
                                                  output public key */
   uint32_t                PublicKeyLenUsed; /**< PublicKey length used in bytes. */
   qapi_CRPT_Key_Handle_t  PrivateKeyHandle; /**< Handle for the private key(out). */
}  qapi_CRPT_Generate_Key_Pair_Params_t;

/** Structure representing the parameters required to perform to get ECC public key operation. */
typedef struct qapi_CRPT_ECC_Get_Public_Key_Params_s
{
   qapi_CRPT_ECC_Curve_t   Curve;            /**< Elliptic curve. */
   qapi_CRPT_Key_Handle_t  PrivateKeyHandle; /**< Handle for the private key. */
   uint32_t                PublicKeyLen;     /**< PublicKey length in bytes. */
   uint8_t                *PublicKey;        /**< Buffer allocated by the application for placing
                                                  output public key. */
   uint32_t                PublicKeyLenUsed; /**< PublicKey length used in bytes. @newpagetable */
} qapi_CRPT_ECC_Get_Public_Key_Params_t;

/** Structure representing the parameters required to perform ECDH shared secret operation. */
typedef struct qapi_CRPT_ECDH_Shared_Secret_Params_s
{
   qapi_CRPT_ECC_Curve_t   Curve;              /**< Elliptic curve. */
   qapi_CRPT_Key_Handle_t  PrivateKeyHandle;   /**< Handle for the private key. */
   uint32_t                PublicKeyLen;       /**< PublicKey length in bytes. */
   uint8_t                *PublicKey;          /**< Pointer to the Public key. */
   qapi_CRPT_Key_Handle_t  SharedSecretHandle; /**< Handle for the shared secret(out). */
} qapi_CRPT_ECDH_Shared_Secret_Params_t;

/** Structure representing the parameters required to perform ECDSA signature over a digest. */
typedef struct qapi_CRPT_ECDSA_Sign_Digest_Params_s
{
   qapi_CRPT_ECC_Curve_t   Curve;            /**< Elliptic curve. */
   qapi_CRPT_Key_Handle_t  PrivateKeyHandle; /**< Handle for the private key. */
   uint32_t                DigestLen;        /**< Digest length in bytes. */
   uint8_t                *Digest;           /**< Digest to generate signature on. */
   uint32_t                SignatureLen;     /**< Signature length in bytes.  */
   uint8_t                *Signature;        /**< Buffer allocated by the application for placing
                                                  output signature. */
   uint32_t                SignatureLenUsed; /**< Signature length used in bytes.  */
} qapi_CRPT_ECDSA_Sign_Digest_Params_t;

/** Structure representing the parameters required to perform ECDSA verify for a digest. */
typedef struct qapi_CRPT_ECDSA_Verify_Digest_Params_s
{
   qapi_CRPT_ECC_Curve_t  Curve;        /**< Elliptic curve. */
   uint32_t               PublicKeyLen; /**< PublicKey length in bytes. */
   uint8_t               *PublicKey;    /**< Pointer to the Public key. */
   uint32_t               DigestLen;    /**< Digest length in bytes. */
   uint8_t               *Digest;       /**< Digest to verifying the signature on. */
   uint32_t               SignatureLen; /**< Signature length in bytes. */
   uint8_t               *Signature;    /**< Signature to be verified. */
} qapi_CRPT_ECDSA_Verify_Digest_Params_t;

/** Structure representing the parameters required to perform ECDSA signature over a message. */
typedef struct qapi_CRPT_ECDSA_Sign_Message_Params_s
{
   qapi_CRPT_ECC_Curve_t    Curve;            /**< Elliptic curve. */
   qapi_CRPT_Digest_Algo_t  Algo;             /**< Digest algorithm. */
   qapi_CRPT_Key_Handle_t   PrivateKeyHandle; /**< Handle for the private key. */
   uint32_t                 MessageLen;       /**< Message length in bytes. */
   uint8_t                 *Message;          /**< Message to generate the signature on. */
   uint32_t                 SignatureLen;     /**< Signature length in bytes. */
   uint8_t                 *Signature;        /**< Buffer allocated by the application for placing output signature. */
   uint32_t                 SignatureLenUsed; /**< Signature length used in bytes. */
} qapi_CRPT_ECDSA_Sign_Message_Params_t;

/** Structure representing the parameters required to perform ECDSA verify for a message. */
typedef struct qapi_CRPT_ECDSA_Verify_Message_Params_s
{
   qapi_CRPT_ECC_Curve_t    Curve;        /**< Elliptic curve. */
   qapi_CRPT_Digest_Algo_t  Algo;         /**< Digest algorithm. */
   uint32_t                 PublicKeyLen; /**< PublicKey length in bytes. */
   uint8_t                 *PublicKey;    /**< Pointer to the Public key. */
   uint32_t                 MessageLen;   /**< Message length in bytes. */
   uint8_t                 *Message;      /**< Message to verify the signature on. */
   uint32_t                 SignatureLen; /**< Signature length in bytes. */
   uint8_t                 *Signature;    /**< Signature to be verified. */
} qapi_CRPT_ECDSA_Verify_Message_Params_t;

/** Structure representing the event data as received in callback. */
typedef struct qapi_CRPT_Operation_Event_Data_s
{
  qapi_CRPT_Operation_t Operation;                                     /**< Operation type */
  union {
    qapi_CRPT_Import_Key_Params_t           *ImportKeyParams;          /**< Import key parameters. */
    qapi_CRPT_Clear_Key_Params_t            *ClearKeyParams;           /**< Clear key parameters. */
    qapi_CRPT_Derive_Key_Params_t           *DeriveKeyParams;          /**< Derive key parameters. */
    qapi_CRPT_RNG_Params_t                  *RNGParams;                /**< RNG parameters. */
    qapi_CRPT_Digest_Params_t               *DigestParams;             /**< Digest parameters. */
    qapi_CRPT_HMAC_256_Params_t             *HMACParams;               /**< HMAC parameters. */
    qapi_CRPT_AES_Encryption_Params_t       *AESEncryptionParams;      /**< AES encryption parameters. */
    qapi_CRPT_AES_Decryption_Params_t       *AESDecryptionParams;      /**< AES decryption parameters. */
    qapi_CRPT_Generate_Key_Pair_Params_t    *GenerateKeyPairParams;    /**< Generate key pair parameters. */
    qapi_CRPT_ECC_Get_Public_Key_Params_t   *ECCGetPublicKeyParams;    /**< ECC get public key parameters. */
    qapi_CRPT_ECDH_Shared_Secret_Params_t   *ECDHSharedSecretParams;   /**< ECDH shared secret parameters. */
    qapi_CRPT_ECDSA_Sign_Digest_Params_t    *ECDSASignDigestParams;    /**< ECDSA sign digest parameters. */
    qapi_CRPT_ECDSA_Verify_Digest_Params_t  *ECDSAVerifyDigestParams;  /**< ECDSA verify digest parameters. */
    qapi_CRPT_ECDSA_Sign_Message_Params_t   *ECDSASignMessageParams;   /**< ECDSA sign message parameters. */
    qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams; /**< ECDSA verify message parameters. */
  }
   Data;      /**< Event data */
} qapi_CRPT_Operation_Event_Data_t;

/** 
   @brief Prototype for a function called after non-blocking crypto operation is complete.
   @param[in] Status     Crypto operation result.
   @param[in] EventData  Event Data for the crypto operation.
   @param[in] UserParam  User-specified parameter provided when the callback is registered.
*/
typedef void (*qapi_CRPT_Operation_CB_t)(qapi_Status_t Status, qapi_CRPT_Operation_Event_Data_t *EventData, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Imports the provided key in the crypto module.

   Handle to the key is provided as output and stored in KeyHandle of ImportKeyParams.
   This handle is subsequently used for relevant crypto operations like HMAC, Encrypt etc.

   For asymmetric operations like shared secret generation, public key retrieval, signature 
   creation, or keypair generation, the private key to be imported must be aligned 
   to the nearest word boundary i.e. 32 bits, and 0-padded (on the LSB, least-significant-bits)
   if required. The following input length alignment for each curve is required:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes for the imported key.
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes for the imported key.

   A key imported using this API must be cleared by calling the qapi_CRPT_Clear_Key()
   API after use.

   @param[in,out] ImportKeyParams  Import key operation parameters.
   @param[in]     CryptoCB         Callback function, only used in non-blocking mode.
                                   NULL for blocking mode.
   @param[in]     UserParam        User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ImportKeyParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_Import_Key(qapi_CRPT_Import_Key_Params_t *ImportKeyParams,
                                   qapi_CRPT_Operation_CB_t       CryptoCB,
                                   void                          *UserParam);

/**
   @brief Releases the resources allocated for the key.

   @param[in,out] ClearkeyParams  Clear key operation parameters.
   @param[in]     CryptoCB        Callback function, only used in non-blocking mode.
                                  NULL for blocking mode.
   @param[in]     UserParam       User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ClearkeyParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_Clear_Key(qapi_CRPT_Clear_Key_Params_t *ClearkeyParams,
                                  qapi_CRPT_Operation_CB_t      CryptoCB,
                                  void                         *UserParam);

/**
   @brief Derives a key from a specified base key.

   Nonce(a random number) and a free form label(such as, "FW Update") are used to
   derive a key from a given base key.
   Key handle for the derived key is provided as output and stored in DerivedKeyHandle
   of DeriveKeyParams.

   Before performing derive key operation, base key handle(BaseKeyHandle) used in
   qapi_CRPT_Derive_Key_Params_t must be imported with the algorithm specified as
   QAPI_CRPT_KEY_ALGO_HKDF_256_E.

   A key derived using this API must be cleared by calling the qapi_CRPT_Clear_Key() API after use.

   @param[in,out] DeriveKeyParams  Derive key operation parameters.
   @param[in]     CryptoCB         Callback function, only used in non-blocking mode.
                                   NULL for blocking mode.
   @param[in]     UserParam        User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.
  
   \attention The input parameter DeriveKeyParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_Derive_Key(qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams,
                                   qapi_CRPT_Operation_CB_t       CryptoCB,
                                   void                          *UserParam);

/**
   @brief Provides a random number of a specified length.

   The generated random number is provided as output and stored in RandomNumber buffer having
   RandomNumberLen bytes of data.
   The size allocated for random buffer(RandomNumber) output must be able to store requested
   length of data.

   @param[in,out] RNGParams  RNG operation parameters.
   @param[in]     CryptoCB   Callback function, only used in non-blocking mode.
                             NULL for blocking mode.
   @param[in]     UserParam  User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter RNGParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_RNG(qapi_CRPT_RNG_Params_t   *RNGParams,
                            qapi_CRPT_Operation_CB_t  CryptoCB,
                            void                     *UserParam);

/**
   @brief Generates digest for the specified message.

   The generated digest is provided as output and the number of bytes consumed by digest
   is provided in DigestLenUsed.
   The minimum size of the digest buffer must be provided as per the provided digest algorithm.
   For #QAPI_CRPT_DIGEST_ALGO_SHA256_E, the minimum size of the digest buffer must be 32 bytes.
   For #QAPI_CRPT_DIGEST_ALGO_SHA512_E, the minimum size of the digest buffer must be 64 bytes.

   @param[in,out] DigestParams  Digest operation parameters.
   @param[in]     CryptoCB      Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param[in]     UserParam     User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter DigestParams should be in heap, or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_Digest(qapi_CRPT_Digest_Params_t *DigestParams,
                               qapi_CRPT_Operation_CB_t   CryptoCB,
                               void                      *UserParam);

/**
   @brief Generates HMAC for the specified message.

   The generated HMAC is provided as output and the number of bytes consumed by
   HMAC is provided in HMACLenUsed.
   The minimum size allocated for output HMAC buffer must be able to store 32 bytes of data.

   @param[in,out] HMACParams  HMAC operation parameters.
   @param[in]     CryptoCB    Callback function, only used in non-blocking mode.
                              NULL for blocking mode.
   @param[in]     UserParam   User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter HMACParams should be in heap, or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_HMAC_256(qapi_CRPT_HMAC_256_Params_t  *HMACParams,
                                 qapi_CRPT_Operation_CB_t      CryptoCB,
                                 void                         *UserParam);

/**
   @brief Performs AES decryption.

   The generated plaintext is provided as output and the number of bytes consumed by
   plaintext is provided in PlainTextLenUsed.
   The minimum size of the plaintext buffer(PlainText) must be equal to the provided
   encrypted text(EncryptedData).

   @param[in,out] AESDecryptionParams  AES decryption operation parameters.
   @param[in]     CryptoCB             Callback function, only used in non-blocking mode.
                                       NULL for blocking mode.
   @param[in]     UserParam            User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter AESDecryptionParams should be in heap, or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_AES_Decryption(qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams,
                                       qapi_CRPT_Operation_CB_t           CryptoCB,
                                       void                              *UserParam);

/**
   @brief Performs AES encryption.

   The generated encrypted data is provided as output and the number of bytes consumed by 
   encrypted data is provided in EncryptedDataLenUsed.
   IV is provided as output for all AES algorithms except ECB.
   TAG is provided as output for GCM AES algorithm.
   The minimum size of the encrypted data buffer(EncryptedData) must be equal to the
   provided plain text(PlainText).

   @param[in,out] AESEncryptionParams  AES encryption operation parameters.
   @param[in]     CryptoCB             Callback function, only used in non-blocking mode.
                                       NULL for blocking mode.
   @param[in]     UserParam            User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter AESEncryptionParams should be in heap, or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_AES_Encryption(qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams,
                                       qapi_CRPT_Operation_CB_t           CryptoCB,
                                       void                              *UserParam);

/**
   @brief Generates an ECC key pair.

   The public key(PublicKey) and handle to the generated private key(PrivateKeyHandle) are provided as output.
   The number of bytes consumed by the public key is provided as PublicKeyLenUsed.

   The minimum size of the public key buffer must be as per the KeyAlgo specified.
   For algos #QAPI_CRPT_KEY_ALGO_ECDSA_256_E and #QAPI_CRPT_KEY_ALGO_ECDH_256_E, the minimum size of
   the public key buffer must be 64 bytes.
   For algos #QAPI_CRPT_KEY_ALGO_ECDSA_521_E and #QAPI_CRPT_KEY_ALGO_ECDH_521_E, the minimum size of
   the public key buffer must be 136 bytes.

   The output public key aligns its x and y coordinates to the nearest word boundary, that is 32 bits,
   and 0-pads the LSB (least-significant-bits). The resulting output buffer holds the public key in
   one of the following formats:
   - #QAPI_CRPT_KEY_ALGO_ECDSA_256_E and #QAPI_CRPT_KEY_ALGO_ECDH_256_E: 32 bytes per coordinate,
     or 32*2=64 total bytes for public key buffer
   - #QAPI_CRPT_KEY_ALGO_ECDSA_521_E and #QAPI_CRPT_KEY_ALGO_ECDH_521_E: 68 bytes per coordinate,
     or 68*2=136 total bytes for public key buffer

   In case of algos #QAPI_CRPT_KEY_ALGO_ECDSA_521_E and #QAPI_CRPT_KEY_ALGO_ECDH_521_E, the x and y 
   coordinates of public key are little-endian 0-padded up to 68 bytes each, although the 
   coordinate itself only takes upto 66 bytes.

   @param[in,out] GenerateKeyPairParams  Generate key Pair Operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter GenerateKeyPairParams should be in heap, or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_Generate_Key_Pair(qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams,
                                          qapi_CRPT_Operation_CB_t              CryptoCB,
                                          void                                 *UserParam);

/**
   @brief Extract public key.

   Retrieves public key from the specified private key handle.

   The public key is provided as output and the number of bytes consumed by the public key is 
   provided as PublicKeyLenUsed. 

   The minimum size of the public key buffer must be as per the ECC curve specified.
   For #QAPI_CRPT_ECC_CURVE_NIST_P256_E, the minimum size of the public key buffer must be 64 bytes.
   For #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the minimum size of the public key buffer must be 136 bytes.

   The output public key aligns its x and y coordinates to the nearest word boundary, that is 32 bits,
   and 0-pads the LSB (least-significant-bits). The resulting output buffer holds the public key in 
   one of the following formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per coordinate, or 32*2=64 total bytes for public key buffer
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per coordinate, or 68*2=136 total bytes for public key buffer

   In case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the x and y coordinates of public key are little-endian 
   0-padded up to 68 bytes each, although the coordinate itself only takes upto 66 bytes.

   @param[in,out] ECCGetPublicKeyParams  Get ECC Public Key Operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECCGetPublicKeyParams should be in heap, or a static
   n          buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_ECC_Get_Public_Key(qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam);

/**
   @brief Generates shared secret.

   The generated shared secret handle is the real part of multiplication of provided public and private
   key. Generated handle will be stored in SharedSecretHandle.

   The generated shared secret handle can only be used for HKDF crypto operation

   The other entities, public key and the private key handle provided must be using the same ECC curve.

   The x and y coordinates of the input public key must align to the nearest word boundary i.e. 32 
   bits, and LSB (least-significant-bits) 0-padded if required. Hence the public key buffer must be 
   in one of the following formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per coordinate, or 32*2=64 total bytes for input public key
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per coordinate, or 68*2=136 total bytes for input public key

   In case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the x and y coordinates of public key should be little-endian 
   0-padded up to 68 bytes each, although the component itself only takes up 66 bytes.

   @param[in,out] ECDHSharedSecretParams  ECDH shared secret operation parameters.
   @param[in]     CryptoCB                Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param[in]     UserParam               User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDHSharedSecretParams should be in heap, or
              a static buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_ECDH_Shared_Secret(qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam);

/**
   @brief Generates signature over a digest.

   The generated signature is provided as output and the number of bytes consumed by signature 
   is provided in SignatureLenUsed.

   The minimum size of the signature buffer must be as per the ECC curve specified.
   For #QAPI_CRPT_ECC_CURVE_NIST_P256_E, the minimum size of the signature buffer must be 64 bytes.
   For #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the minimum size of the signature buffer must be 136 bytes.

   The generated signature aligns each r and s component to the nearest word boundary i.e 32 bits,
   and 0-pads the LSB (least-significant-bits). The resulting output buffer holds the signature in 
   one of the following formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per component, or 32*2=64 total bytes for the signature
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per component, or 68*2=136 total bytes for the signature

   In the case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the r and s components of generated signature are 
   little-endian 0-padded up to 68 bytes each, although the component itself only takes up 66 bytes.

   @param[in,out] ECDSASignDigestParams  ECDSA sign digest operation Parameters.
   @param[in]     CryptoCB               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSASignDigestParams should be in heap or
              a static buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_ECDSA_Sign_Digest(qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams,
                                          qapi_CRPT_Operation_CB_t              CryptoCB,
                                          void                                 *UserParam);

/**
   @brief Verifies signature over a digest.

   The input signature's r and s component must be aligned to the nearest word boundary i.e 32 bits,
   and LSB (least-significant-bits) 0-padded if required. Hence the signature must be in the following
   formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per component, or 32*2=64 total bytes of the signature
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per component, or 68*2=136 total bytes of the signature

   In the case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the r and s components of input signature 
   should be little-endian 0-padded up to 68 bytes each, although the component itself only takes
   up 66 bytes.

   @param[in,out] ECDSAVerifyDigestParams  ECDSA verify digest operation parameters.
   @param[in]     CryptoCB                 Callback function, only used in non-blocking mode.
                                           NULL for blocking mode.
   @param[in]     UserParam                User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSAVerifyDigestParams should be in heap, or
              a static buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_ECDSA_Verify_Digest(qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams,
                                            qapi_CRPT_Operation_CB_t                CryptoCB,
                                            void                                   *UserParam);

/**
   @brief Generates signature over a message.

   The generated signature is provided as output and the number of bytes consumed by signature
   is provided in SignatureLenUsed.

   The minimum size of the signature buffer must be as per the ECC curve specified.
   For #QAPI_CRPT_ECC_CURVE_NIST_P256_E, the minimum size of the signature buffer must be 64 bytes.
   For #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the minimum size of the signature buffer must be 136 bytes.

   The generated signature aligns each r and s component to the nearest word boundary i.e 32 bits,
   and 0-pads the LSB (least-significant-bits). The resulting output buffer holds the signature in 
   one of the following formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per component, or 32*2=64 total bytes for the signature
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per component, or 68*2=136 total bytes for the signature

   In the case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the r and s components of generated signature are 
   little-endian 0-padded up to 68 bytes each, although the component itself only takes up 66 bytes.

   @param[in,out] ECDSASignMessageParams  ECDSA sign message operation parameters.
   @param[in]     CryptoCB                Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param[in]     UserParam               User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSASignMessageParams should be in heap or a static buffer
              for non-blocking read. @newpage
*/
qapi_Status_t qapi_CRPT_ECDSA_Sign_Message(qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams,
                                           qapi_CRPT_Operation_CB_t               CryptoCB,
                                           void                                  *UserParam);

/**
   @brief Verifies signature over a message.

   The input signature's r and s component must be aligned to the nearest word boundary i.e. 32 bits,
   and LSB (least-significant-bits) 0-padded if required. Hence the signature must be in the following
   formats:
   - #QAPI_CRPT_ECC_CURVE_NIST_P256_E: 32 bytes per component, or 32*2=64 total bytes of the signature
   - #QAPI_CRPT_ECC_CURVE_NIST_P521_E: 68 bytes per component, or 68*2=136 total bytes of the signature

   In the case of #QAPI_CRPT_ECC_CURVE_NIST_P521_E, the r and s components of input signature 
   should be little-endian 0-padded up to 68 bytes each, although the component itself only takes
   up 66 bytes.

   @param[in,out] ECDSAVerifyMessageParams  ECDSA verify message operation parameters.
   @param[in]     CryptoCB                  Callback function, only used in non-blocking mode.
                                            NULL for blocking mode.
   @param[in]     UserParam                 User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If the blocking operation completed successfully, or a non-blocking call is successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating a non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter ECDSAVerifyMessageParams should be in heap or a static buffer
              for non-blocking read.
*/
qapi_Status_t qapi_CRPT_ECDSA_Verify_Message(qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams,
                                             qapi_CRPT_Operation_CB_t                 CryptoCB,
                                             void                                    *UserParam);

/** @} */ /* end_addtogroup qapi_platform_crypto */

#endif
