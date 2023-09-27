/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_crypto.h"

#include "qcli_pal.h"
#include "qcli.h"
#include "qapi_heap.h"
#include "qcli_api.h"
#include "qcli_util.h"

#include "crypto_demo.h"
#include "rot_demo_utils.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/**
   By default, using blocking operation for all crypto command execution.
   For non-blocking execution of crypto QAPI, set this macro to false.
*/
#define CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE  true

/** Maximum length of random number. */
#define CRYPTO_MAX_RANDOM_NUMBER_LENGTH (64)

/** Description to be printed on qcli for supported algorithms and curve.*/
#define MENU_CURVE              "Supported Curve:\n0. NIST_P256\n1. NIST_P521"
#define MENU_IMPORT_KEY_ALGO    "Supported KeyAlgo and respective KeyLen in bytes {KeyAlgo, KeyLen, KeyHexString description}:\n0.  AES_GCM128, 16\n1.  AES_GCM256, 32\n2.  AES_CBC128, 16\n3.  AES_CBC256, 32\n4.  AES_CTR128, 16\n5.  AES_CTR256, 32\n6.  HMAC256,    32\n7.  HKDF128,    16\n8.  HKDF256,    32\n9.  ECDSA256,   32, If required little-endian 0-padded.\n10. ECDSA521,   68, If required little-endian 0-padded.\n11. ECDH256,    32, If required little-endian 0-padded.\n12. ECDH521,    68, If required little-endian 0-padded."
#define MENU_KEY_ALGO           "Supported KeyAlgo:\n0.  AES_GCM128\n1.  AES_GCM256\n2.  AES_CBC128\n3.  AES_CBC256\n4.  AES_CTR128\n5.  AES_CTR256\n6.  HMAC256\n7.  HKDF128\n8.  HKDF256\n9.  ECDSA256\n10. ECDSA521\n11. ECDH256\n12. ECDH521"
#define MENU_KEY_PAIR_ALGO      "Supported PrivateKeyAlgo:\n9.  ECDSA256\n10. ECDSA521\n11. ECDH256\n12. ECDH521"
#define MENU_DIGEST_ALGO        "Supported DigestAlgo: \n0. SHA256\n1. SHA512"
#define MENU_AES_ALGO           "Supported AESAlgo:\n0. AES128_GCM\n1. AES256_GCM\n2. AES128_CBC\n3. AES256_CBC\n4. AES128_CTR\n5. AES256_CTR"
#define MENU_CURVE_PUB_KEY      "Supported Curve & respective PublicKeyLen in bytes {Curve, PublicKeyLen, PublicKeyHexString description}:\n0. NIST_P256, 64,  If required x and y coordinates should be little-endian 0-padded.\n1. NIST_P521, 136, If required x and y coordinates should be little-endian 0-padded."
#define MENU_CURVE_PUB_KEY_SIGN "Supported Curve & respective PublicKeyLen & SignLen in bytes {Curve, PublicKeyLen, PublicKeyHexString description, SignLen, SignatureHexString description}:\n0. NIST_P256, 64,  If required x and y coordinates should be little-endian 0-padded., 64,  If required r and s components should be little-endian 0-padded\n1. NIST_P521, 136, If required x and y coordinates should be little-endian 0-padded., 136, If required r and s components should be little-endian 0-padded."

/** Description of IV length used in AES Decryption */
#define MENU_IV_LEN      "Supported IVLen: 12 bytes for AES_GCM and 16 bytes for AES_CBC and AES_CTR."

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Crypto_Handle;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
/* Internal result printing functions. */
static void Crypto_Print_ImportKey_Result(qapi_Status_t Status, qapi_CRPT_Import_Key_Params_t *ImportKeyParams);
static void Crypto_Print_ClearKey_Result(qapi_Status_t Status, qapi_CRPT_Clear_Key_Params_t *ClearKeyParams);
static void Crypto_Print_DeriveKey_Result(qapi_Status_t Status, qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams);
static void Crypto_Print_RNG_Result(qapi_Status_t Status, qapi_CRPT_RNG_Params_t *RNGParams);
static void Crypto_Print_Digest_Result(qapi_Status_t Status, qapi_CRPT_Digest_Params_t *DigestParams);
static void Crypto_Print_HMAC_Result(qapi_Status_t Status, qapi_CRPT_HMAC_256_Params_t *HMACParams);
static void Crypto_Print_Encrypt_Result(qapi_Status_t Status, qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams);
static void Crypto_Print_Decrypt_Result(qapi_Status_t Status, qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams);
static void Crypto_Print_GenerateKeyPair_Result(qapi_Status_t Status, qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams);
static void Crypto_Print_ECCGetPublicKey_Result(qapi_Status_t Status, qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams);
static void Crypto_Print_ECDHSharedSecret_Result(qapi_Status_t Status, qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams);
static void Crypto_Print_ECDSASignDigest_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams);
static void Crypto_Print_ECDSAVerifyDigest_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams);
static void Crypto_Print_ECDSASignMessage_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams);
static void Crypto_Print_ECDSAVerifyMessage_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams);

/* Resources release related functions. */
static void Crypto_Release_ImportKey(qapi_CRPT_Import_Key_Params_t *ImportKeyParams);
static void Crypto_Release_DeriveKey(qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams);
static void Crypto_Release_RNG(qapi_CRPT_RNG_Params_t *RNGParams);
static void Crypto_Release_Digest(qapi_CRPT_Digest_Params_t *DigestParams);
static void Crypto_Release_HMAC(qapi_CRPT_HMAC_256_Params_t *HMACParams);
static void Crypto_Release_Encrypt(qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams);
static void Crypto_Release_Decrypt(qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams);
static void Crypto_Release_GenerateKeyPair(qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams);
static void Crypto_Release_ECCGetPublicKey(qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams);
static void Crypto_Release_ECDHSharedSecret(qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams);
static void Crypto_Release_ECDSASignDigest(qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams);
static void Crypto_Release_ECDSAVerifyDigest(qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams);
static void Crypto_Release_ECDSASignMessage(qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams);
static void Crypto_Release_ECDSAVerifyMessage(qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams);

/* Callback function. */
static void Crypto_CmdOperationCB(qapi_Status_t Status, qapi_CRPT_Operation_Event_Data_t *EventData, void *UserParam);

/* Crypto operation functions. */
static QCLI_Command_Status_t cmd_Crypto_Import_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Clear_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Derive_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_RNG(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_HMAC(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Encrypt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Decrypt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_Generate_Key_pair(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECC_Get_Public_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECDH_Shared_Secret(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Sign_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Verify_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Sign_Message(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Verify_Message(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Crypto response handler function. */
static void Crypto_Handle_Response(qapi_Status_t Status, qapi_CRPT_Operation_t Operation, void *CryptoParam);

/* Command list for the crypto demo. */
const QCLI_Command_t Crypto_CMD_List[] =
{
    /* cmd_function                    cmd_string            usage_string                                                                                                                 description                                                                             */
    { cmd_Crypto_Import_Key,           "ImportKey",          "<KeyLen> <KeyHexString> <KeyAlgo>",                                                                                         "Import key.\n" MENU_IMPORT_KEY_ALGO                                                    },
    { cmd_Crypto_Clear_Key,            "ClearKey",           "<KeyHandle>",                                                                                                               "Clear key."                                                                            },
    { cmd_Crypto_Derive_Key,           "DeriveKey",          "<KeyAlgo> <BaseKeyHandle> <NonceLen> <NonceHexString> <LabelString>",                                                       "Derive key.\n" MENU_KEY_ALGO                                                           },
    { cmd_Crypto_RNG,                  "RandomNumber",       "<RandomNumberLength>",                                                                                                      "Generate random number."                                                               },
    { cmd_Crypto_Digest,               "Digest",             "<DigestAlgo> <MsgLen> <MsgHexString>",                                                                                      "Calculate Digest.\n" MENU_DIGEST_ALGO                                                  },
    { cmd_Crypto_HMAC,                 "HMAC",               "<KeyHandle> <MsgLen> <MsgHexString>",                                                                                       "Calculate HMAC-SHA256."                                                                },
    { cmd_Crypto_Encrypt,              "Encrypt",            "<Algo> <KeyHandle> <PlainTextLen> <PlainTextHexString> <AADLen> <AADHexString>",                                            "AES Encrypt.\n" MENU_AES_ALGO                                                          },
    { cmd_Crypto_Decrypt,              "Decrypt",            "<Algo> <KeyHandle> <EncryptLen> <EncryptHexString> <IVLen> <IVHexString> <TagLen> <TAGHexString> <AADLen> <AADHexString>",  "AES Decrypt.\n" MENU_AES_ALGO "\n" MENU_IV_LEN                                         },
    { cmd_Crypto_Generate_Key_pair,    "GenerateKeyPair",    "<PrivateKeyAlgo>",                                                                                                          "Generate key pair.\n" MENU_KEY_PAIR_ALGO                                               },
    { cmd_Crypto_ECC_Get_Public_Key,   "ECCGetPublicKey",    "<Curve> <PrivateKeyHandle>",                                                                                                "ECC get public key.\n" MENU_CURVE                                                      },
    { cmd_Crypto_ECDH_Shared_Secret,   "ECDHSharedSecret",   "<Curve> <PrivateKeyHandle> <PublicKeyLen> <PublicKeyHexString>",                                                            "ECDH shared secret handle.\n" MENU_CURVE_PUB_KEY                                       },
    { cmd_Crypto_ECDSA_Sign_Digest,    "ECDSASignDigest",    "<Curve> <PrivateKeyHandle> <DigestLen> <DigestHexstring>",                                                                  "ECDSA signature of digest.\n" MENU_CURVE                                               },
    { cmd_Crypto_ECDSA_Verify_Digest,  "ECDSAVerifyDigest",  "<Curve> <PublicKeyLen> <PublicKeyHexString> <DigestLen> <DigestHexString> <SignLen> <SignatureHexString>",                  "ECDSA digest signature verification.\n" MENU_CURVE_PUB_KEY_SIGN                        },
    { cmd_Crypto_ECDSA_Sign_Message,   "ECDSASignMessage",   "<Curve> <DigestAlgo> <PrivateKeyHandle> <MsgLen> <MsgHexString>",                                                           "ECDSA signature of message.\n" MENU_CURVE "\n" MENU_DIGEST_ALGO                        },
    { cmd_Crypto_ECDSA_Verify_Message, "ECDSAVerifyMessage", "<Curve> <DigestAlgo> <PublicKeyLen> <PublicKeyHexstring> <MsgLen> <MsgHexString> <SignLen> <SignatureHexString>",           "ECDSA message signature verification.\n" MENU_CURVE_PUB_KEY_SIGN "\n" MENU_DIGEST_ALGO }
};

const QCLI_Command_Group_t Crypto_CMD_Group =
{
    "Crypto",
    (sizeof(Crypto_CMD_List) / sizeof(Crypto_CMD_List[0])),
    Crypto_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize crypto demo.

   @param[in] Parent_Group Parent group handle.
*/
void Initialize_Crypto_Demo(QCLI_Group_Handle_t Parent_Group)
{
    /* Attempt to register the Command Groups with the qcli framework.*/
    QCLI_Crypto_Handle = QCLI_Register_Command_Group(Parent_Group, &Crypto_CMD_Group);
    if (QCLI_Crypto_Handle)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "Crypto registered.\n");
    }
}

/**
   @brief Cleans up resources used by the crypto demo.
*/
void Cleanup_Crypto_Demo(void)
{
    if (QCLI_Crypto_Handle)
    {
        QCLI_Unregister_Command_Group(QCLI_Crypto_Handle);
        QCLI_Crypto_Handle = NULL;
    }
}

/**
   @brief Print import key result.

   @param[in] Status           Crypto operation status.
   @param[in] ImportKeyParams  Import key params.
*/
static void Crypto_Print_ImportKey_Result(qapi_Status_t Status, qapi_CRPT_Import_Key_Params_t *ImportKeyParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ImportKey Success, KeyHandle:%d.\n", ImportKeyParams->KeyHandle);
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ImportKey Failed.\n");
    }
}

/**
   @brief Release resources used by import key operation.

   @param[in] ImportKeyParams  Import key params.
*/
static void Crypto_Release_ImportKey(qapi_CRPT_Import_Key_Params_t *ImportKeyParams)
{
    FREE_IF (ImportKeyParams->Key);
}

/**
   @brief Print clear key result.

   @param[in] Status           Crypto operation status.
   @param[in] ClearKeyParams   Clear key params.
*/
static void Crypto_Print_ClearKey_Result(qapi_Status_t Status, qapi_CRPT_Clear_Key_Params_t *ClearKeyParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ClearKey Success, KeyHandle:%d.\n",ClearKeyParams->KeyHandle);
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ClearKey Failed.\n");
    }
}

/**
   @brief Print derive key result.

   @param[in] Status           Crypto operation status.
   @param[in] DeriveKeyParams  Derive key params.
*/
static void Crypto_Print_DeriveKey_Result(qapi_Status_t Status, qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "DeriveKey Success, KeyHandle %d.\n", DeriveKeyParams->DerivedKeyHandle);
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "DeriveKey Failed.\n");
    }
}

/**
   @brief Release resources used by Derive key operation.

   @param[in] DeriveKeyParams Derive key params.
*/
static void Crypto_Release_DeriveKey(qapi_CRPT_Derive_Key_Params_t *DeriveKeyParams)
{
    FREE_IF (DeriveKeyParams->Nonce);
    FREE_IF (DeriveKeyParams->Label);
}

/**
   @brief Print random number generation result.

   @param[in] Status     Crypto operation status.
   @param[in] RNGParams  Random number generation params.
*/
static void Crypto_Print_RNG_Result(qapi_Status_t Status, qapi_CRPT_RNG_Params_t *RNGParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "RandomNumber ", RNGParams->RandomNumberLen, RNGParams->RandomNumber);
        QCLI_Printf(QCLI_Crypto_Handle, "\nRandomNumber Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "RandomNumber Failed.\n");
    }
}

/**
   @brief Release resources used by Random number generation operation.

   @param[in] RNGParams Random number generation params.
*/
static void Crypto_Release_RNG(qapi_CRPT_RNG_Params_t *RNGParams)
{
    FREE_IF (RNGParams->RandomNumber);
}

/**
   @brief Print digest result.

   @param[in] Status        Crypto operation status.
   @param[in] DigestParams  Digest params.
*/
static void Crypto_Print_Digest_Result(qapi_Status_t Status, qapi_CRPT_Digest_Params_t *DigestParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "Digest ", DigestParams->DigestLenUsed, DigestParams->Digest);
        QCLI_Printf(QCLI_Crypto_Handle, "\nDigest Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "Digest Failed.\n");
    }
}

/**
   @brief Release resources used by Digest operation.

   @param[in] DigestParams  Digest params.
*/
static void Crypto_Release_Digest(qapi_CRPT_Digest_Params_t *DigestParams)
{
    FREE_IF (DigestParams->Digest);
    FREE_IF (DigestParams->Message);
}

/**
   @brief Print HMAC result.

   @param[in] Status      Crypto operation status.
   @param[in] HMACParams  HMAC params.
*/
static void Crypto_Print_HMAC_Result(qapi_Status_t Status, qapi_CRPT_HMAC_256_Params_t *HMACParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "HMAC ", HMACParams->HMACLenUsed, HMACParams->HMAC);
        QCLI_Printf(QCLI_Crypto_Handle, "\nHMAC Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "HMAC Failed.\n");
    }
}

/**
   @brief Release resources used by HMAC operation.

   @param[in] HMACParams HMAC params.
*/
static void Crypto_Release_HMAC(qapi_CRPT_HMAC_256_Params_t *HMACParams)
{
    FREE_IF (HMACParams->Message);
    FREE_IF (HMACParams->HMAC);
}

/**
   @brief Print AES encryption result.

   @param[in] Status               Crypto operation status.
   @param[in] AESEncryptionParams  AES encryption params.
*/
static void Crypto_Print_Encrypt_Result(qapi_Status_t Status, qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "Encrypt ", AESEncryptionParams->EncryptedDataLen, AESEncryptionParams->EncryptedData);

        if (AESEncryptionParams->IVLen != 0)
        {
            QCLI_Dump_Data(QCLI_Crypto_Handle, "IV ", AESEncryptionParams->IVLen, AESEncryptionParams->IV);
        }

        if (AESEncryptionParams->TagLen != 0)
        {
            QCLI_Dump_Data(QCLI_Crypto_Handle, "Tag ", AESEncryptionParams->TagLen, AESEncryptionParams->Tag);
        }

        QCLI_Printf(QCLI_Crypto_Handle, "\nEncrypt Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "Encrypt Failed.\n");
    }
}

/**
   @brief Release resources used by AES encryption operation.

   @param[in] AESEncryptionParams AES encryption params.
*/
static void Crypto_Release_Encrypt(qapi_CRPT_AES_Encryption_Params_t *AESEncryptionParams)
{
    FREE_IF (AESEncryptionParams->PlainText);
    FREE_IF (AESEncryptionParams->AAD);
    FREE_IF (AESEncryptionParams->EncryptedData);
    FREE_IF (AESEncryptionParams->IV);
    FREE_IF (AESEncryptionParams->Tag);
}

/**
   @brief Print AES decryption result.

   @param[in] Status               Crypto operation status.
   @param[in] AESDecryptionParams  AES decryption params.
*/
static void Crypto_Print_Decrypt_Result(qapi_Status_t Status, qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "Decrypt ", AESDecryptionParams->PlainTextLenUsed, AESDecryptionParams->PlainText);
        QCLI_Printf(QCLI_Crypto_Handle, "\nDecrypt Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "Decrypt Failed.\n");
    }
}

/**
   @brief Release resources used by AES decryption operation.

   @param[in] AESDecryptionParams AES decryption params.
*/
static void Crypto_Release_Decrypt(qapi_CRPT_AES_Decryption_Params_t *AESDecryptionParams)
{
    FREE_IF (AESDecryptionParams->PlainText);
    FREE_IF (AESDecryptionParams->AAD);
    FREE_IF (AESDecryptionParams->EncryptedData);
    FREE_IF (AESDecryptionParams->IV);
    FREE_IF (AESDecryptionParams->Tag);
}

/**
   @brief Print generate key pair result.

   @param[in] Status                 Crypto operation status.
   @param[in] GenerateKeyPairParams  Generate key pair params.
*/
static void Crypto_Print_GenerateKeyPair_Result(qapi_Status_t Status, qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "PublicKey ", GenerateKeyPairParams->PublicKeyLenUsed, GenerateKeyPairParams->PublicKey);
        QCLI_Printf(QCLI_Crypto_Handle, "\nPrivateKeyHandle: %d\n", GenerateKeyPairParams->PrivateKeyHandle);
        QCLI_Printf(QCLI_Crypto_Handle, "GenerateKeyPair Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "GenerateKeyPair Failed.\n");
    }
}

/**
   @brief Release resources used by Generate key pair operation.

   @param[in] GenerateKeyPairParams Generate key pair params.
*/
static void Crypto_Release_GenerateKeyPair(qapi_CRPT_Generate_Key_Pair_Params_t *GenerateKeyPairParams)
{
    FREE_IF (GenerateKeyPairParams->PublicKey);
}

/**
   @brief Print ECC get public key result.

   @param[in] Status                 Crypto operation status.
   @param[in] ECCGetPublicKeyParams  ECC get public key params.
*/
static void Crypto_Print_ECCGetPublicKey_Result(qapi_Status_t Status, qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "PublicKey ", ECCGetPublicKeyParams->PublicKeyLen, ECCGetPublicKeyParams->PublicKey);
        QCLI_Printf(QCLI_Crypto_Handle, "\nECCGetPublicKey Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECCGetPublicKey Failed.\n");
    }
}

/**
   @brief Release resources used by ECC get public key operation.

   @param[in] ECCGetPublicKeyParams ECC get public key params.
*/
static void Crypto_Release_ECCGetPublicKey(qapi_CRPT_ECC_Get_Public_Key_Params_t *ECCGetPublicKeyParams)
{
    FREE_IF (ECCGetPublicKeyParams->PublicKey);
}

/**
   @brief Print ECDH shared secret result.

   @param[in] Status                  Crypto operation status.
   @param[in] ECDHSharedSecretParams  ECDH shared secret params.
*/
static void Crypto_Print_ECDHSharedSecret_Result(qapi_Status_t Status, qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDHSharedSecret Success, SharedSecretHandle: %d\n", ECDHSharedSecretParams->SharedSecretHandle);
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDHSharedSecret Failed.\n");
    }
}

/**
   @brief Release resources used by ECDH shared secret operation.

   @param[in] ECDHSharedSecretParams ECDH shared secret params.
*/
static void Crypto_Release_ECDHSharedSecret(qapi_CRPT_ECDH_Shared_Secret_Params_t *ECDHSharedSecretParams)
{
    FREE_IF (ECDHSharedSecretParams->PublicKey);
}

/**
   @brief Print ECDSA sign digest result.

   @param[in] Status                 Crypto operation status.
   @param[in] ECDSASignDigestParams  ECDSA sign digest params.
*/
static void Crypto_Print_ECDSASignDigest_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "Signature ", ECDSASignDigestParams->SignatureLenUsed, ECDSASignDigestParams->Signature);
        QCLI_Printf(QCLI_Crypto_Handle, "\nECDSASignDigest Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDSASignDigest Failed.\n");
    }
}

/**
   @brief Release resources used by ECDSA sign digest operation.

   @param[in] ECDSASignDigestParams ECDSA sign digest params.
*/
static void Crypto_Release_ECDSASignDigest(qapi_CRPT_ECDSA_Sign_Digest_Params_t *ECDSASignDigestParams)
{
    FREE_IF (ECDSASignDigestParams->Digest);
    FREE_IF (ECDSASignDigestParams->Signature);
}

/**
   @brief Print ECDSA verify digest result.

   @param[in] Status                   Crypto operation status.
   @param[in] ECDSAVerifyDigestParams  ECDSA verify digest params.
*/
static void Crypto_Print_ECDSAVerifyDigest_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDSAVerifyDigest verification Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDSAVerifyDigest Failed.\n");
    }
}

/**
   @brief Release resources used by ECDSA verify digest operation.

   @param[in] ECDSAVerifyDigestParams ECDSA verify digest params.
*/
static void Crypto_Release_ECDSAVerifyDigest(qapi_CRPT_ECDSA_Verify_Digest_Params_t *ECDSAVerifyDigestParams)
{
    FREE_IF (ECDSAVerifyDigestParams->PublicKey);
    FREE_IF (ECDSAVerifyDigestParams->Digest);
    FREE_IF (ECDSAVerifyDigestParams->Signature);
}

/**
   @brief Print ECDSA sign message result.

   @param[in] Status                  Crypto operation status.
   @param[in] ECDSASignMessageParams  ECDSA sign message params.
*/
static void Crypto_Print_ECDSASignMessage_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Dump_Data(QCLI_Crypto_Handle, "Signature ", ECDSASignMessageParams->SignatureLenUsed, ECDSASignMessageParams->Signature);
        QCLI_Printf(QCLI_Crypto_Handle, "\nECDSASignMessage Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECDSASignMessage Failed.\n");
    }
}

/**
   @brief Release resources used by ECDSA sign message operation.

   @param[in] ECDSASignMessageParams ECDSA sign message.
*/
static void Crypto_Release_ECDSASignMessage(qapi_CRPT_ECDSA_Sign_Message_Params_t *ECDSASignMessageParams)
{
    FREE_IF (ECDSASignMessageParams->Message);
    FREE_IF (ECDSASignMessageParams->Signature);
}

/**
   @brief Print ECDSA verify message result.

   @param[in] Status                    Crypto operation status.
   @param[in] ECDSAVerifyMessageParams  ECDSA verify message params.
*/
static void Crypto_Print_ECDSAVerifyMessage_Result(qapi_Status_t Status, qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams)
{
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECSDAVerifyMessage verification Success.\n");
    }
    else
    {
        QCLI_Printf(QCLI_Crypto_Handle, "ECSDAVerifyMessage Failed.\n");
    }
}

/**
   @brief Release resources used by ECDSA verify message operation.

   @param[in] ECDSAVerifyMessageParams  ECDSA verify message params.
*/
static void Crypto_Release_ECDSAVerifyMessage(qapi_CRPT_ECDSA_Verify_Message_Params_t *ECDSAVerifyMessageParams)
{
    FREE_IF (ECDSAVerifyMessageParams->PublicKey);
    FREE_IF (ECDSAVerifyMessageParams->Message);
    FREE_IF (ECDSAVerifyMessageParams->Signature);
}

/**
   @brief Handles crypto response.

   It prints the crypto result and releases the acquired resources.

   @param[in] Status      crypto operation status.
   @param[in] Operation   Crypto operation type.
   @param[in] CryptoParam Crypto operation param.
*/
static void Crypto_Handle_Response(qapi_Status_t Status, qapi_CRPT_Operation_t Operation, void *CryptoParam)
{
    if (CryptoParam == NULL)
    {
        QCLI_Printf(QCLI_Crypto_Handle, "Invalid crypto parameter.\n");
        return;
    }

    switch(Operation)
    {
        case QAPI_CRPT_OPERATION_IMPORT_KEY_E:
            Crypto_Print_ImportKey_Result(Status, CryptoParam);
            Crypto_Release_ImportKey(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_CLEAR_KEY_E:
            Crypto_Print_ClearKey_Result(Status, CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_DERIVE_KEY_E:
            Crypto_Print_DeriveKey_Result(Status, CryptoParam);
            Crypto_Release_DeriveKey(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_RNG_E:
            Crypto_Print_RNG_Result(Status, CryptoParam);
            Crypto_Release_RNG(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_DIGEST_E:
            Crypto_Print_Digest_Result(Status, CryptoParam);
            Crypto_Release_Digest(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_HMAC_E:
            Crypto_Print_HMAC_Result(Status, CryptoParam);
            Crypto_Release_HMAC(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ENCRYPT_E:
            Crypto_Print_Encrypt_Result(Status, CryptoParam);
            Crypto_Release_Encrypt(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_DECRYPT_E:
            Crypto_Print_Decrypt_Result(Status, CryptoParam);
            Crypto_Release_Decrypt(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_GENERATE_KEY_PAIR_E:
            Crypto_Print_GenerateKeyPair_Result(Status, CryptoParam);
            Crypto_Release_GenerateKeyPair(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECC_GET_PUBLIC_KEY_E:
            Crypto_Print_ECCGetPublicKey_Result(Status, CryptoParam);
            Crypto_Release_ECCGetPublicKey(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECDH_SHARED_SECRET_E:
            Crypto_Print_ECDHSharedSecret_Result(Status, CryptoParam);
            Crypto_Release_ECDHSharedSecret(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECDSA_SIGN_DIGEST_E:
            Crypto_Print_ECDSASignDigest_Result(Status, CryptoParam);
            Crypto_Release_ECDSASignDigest(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECDSA_VERIFY_DIGEST_E:
            Crypto_Print_ECDSAVerifyDigest_Result(Status, CryptoParam);
            Crypto_Release_ECDSAVerifyDigest(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECDSA_SIGN_MESSAGE_E:
            Crypto_Print_ECDSASignMessage_Result(Status, CryptoParam);
            Crypto_Release_ECDSASignMessage(CryptoParam);
            break;
        case QAPI_CRPT_OPERATION_ECDSA_VERIFY_MESSAGE_E:
            Crypto_Print_ECDSAVerifyMessage_Result(Status, CryptoParam);
            Crypto_Release_ECDSAVerifyMessage(CryptoParam);
            break;
        default:
        {
            QCLI_Printf(QCLI_Crypto_Handle, "Invalid crypto operation type.\n");
        }
    }
}

/**
   @brief Crypto command non-blocking operation callback.

   This callback will be used only for non-blocking command execution. By default, all command
   execution are blocking call. To use callback for non-blocking execution set CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE
   to false.

   @param[in] Status     crypto operation status.
   @param[in] EventData  data specific to crypto operation.
   @param[in] UserParam  User specified parameter for the callback function.
*/
void Crypto_CmdOperationCB(qapi_Status_t Status, qapi_CRPT_Operation_Event_Data_t *EventData, void *UserParam)
{
    /* Crypto params in EventData are members of an union. Sending any union member(ImportKeyParams) 
    to access all the required crypto params corresponding to EventData->Operation. */
    Crypto_Handle_Response(Status, EventData->Operation, (void*)EventData->Data.ImportKeyParams);
}

/**
   @brief Execute ImportKey command.

   ImportKey command uses 3 parameters to execute.
   Parameter_List[0] indicates key length.
   Parameter_list[1] indicates key string.
   Parameter_List[2] indicates key algorithm.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Import_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_Import_Key_Params_t ImportKeyParams;

    memset(&ImportKeyParams, 0, sizeof(ImportKeyParams));

    do
    {
        if ((Parameter_Count != 3) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        ImportKeyParams.KeyLen  = Parameter_List[0].Integer_Value;
        ImportKeyParams.KeyAlgo = (qapi_CRPT_Key_Algo_t) Parameter_List[2].Integer_Value;

        ImportKeyParams.Key = GetArrayFromHexString(Parameter_List[1].String_Value, ImportKeyParams.KeyLen, QCLI_Crypto_Handle);
        if (ImportKeyParams.Key == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_Import_Key(&ImportKeyParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_IMPORT_KEY_E, &ImportKeyParams);
    }
    return CmdStatus;
}

/**
   @brief Execute ClearKey command.

   ClearKey command uses 1 parameter to execute.
   Parameter_List[0] indicates the key handle which needs to be cleared.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Clear_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_Clear_Key_Params_t ClearKeyParams;

    do
    {
        if ((Parameter_Count != 1) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        ClearKeyParams.KeyHandle = Parameter_List[0].Integer_Value;
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_Clear_Key(&ClearKeyParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_CLEAR_KEY_E, &ClearKeyParams);
    }

    return CmdStatus;
}

/**
   @brief Execute DeriveKey command.

   DeriveKey command uses 5 parameters to execute.
   Parameter_List[0] indicates algorithm of the key to be derived.
   Parameter_List[1] indicates base key handle.
   Parameter_list[2] and Parameter_list[3] indicates Nonce length and Nonce string respectively.
   Parameter_list[4] indicates optional label string.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Derive_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_Derive_Key_Params_t DeriveKeyParams;

    memset(&DeriveKeyParams, 0, sizeof(DeriveKeyParams));
    do
    {
        if ((Parameter_Count < 4) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        DeriveKeyParams.KeyAlgo       = (qapi_CRPT_Key_Algo_t) Parameter_List[0].Integer_Value;
        DeriveKeyParams.BaseKeyHandle = Parameter_List[1].Integer_Value;
        DeriveKeyParams.NonceLen      = Parameter_List[2].Integer_Value;
        uint32_t LabelLength          = 0;

        DeriveKeyParams.Nonce = GetArrayFromHexString(Parameter_List[3].String_Value, DeriveKeyParams.NonceLen, QCLI_Crypto_Handle);
        if (DeriveKeyParams.Nonce == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        if(Parameter_Count == 5)
        {
            LabelLength = strlen(Parameter_List[4].String_Value) + 1;
            DeriveKeyParams.Label = qapi_Malloc(LabelLength);
            if(DeriveKeyParams.Label == NULL)
            {
                QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
                CmdStatus = QCLI_STATUS_ERROR_E;
                break;
            }
            memset(DeriveKeyParams.Label, 0, LabelLength);
            memscpy(DeriveKeyParams.Label, LabelLength, Parameter_List[4].String_Value, LabelLength);
        }

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_Derive_Key(&DeriveKeyParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_DERIVE_KEY_E, &DeriveKeyParams);
    }
    return CmdStatus;
}

/**
   @brief Execute RandomNumber command.

   RandomNumber command uses 1 parameter to execute.
   Parameter_List[0] indicates length of random number to be generated.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_RNG(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_RNG_Params_t RNGParams;

    memset(&RNGParams, 0, sizeof(RNGParams));
    do
    {
        if ((Parameter_Count != 1) || (Parameter_List == NULL) ||
            !QCLI_Verify_Unsigned_Integer_Parameter(&Parameter_List[0], 1, CRYPTO_MAX_RANDOM_NUMBER_LENGTH))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        RNGParams.RandomNumberLen = Parameter_List[0].Integer_Value;
        RNGParams.RandomNumber = qapi_Malloc(RNGParams.RandomNumberLen);
        if (RNGParams.RandomNumber == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(RNGParams.RandomNumber, 0, RNGParams.RandomNumberLen);

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_RNG(&RNGParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_RNG_E, &RNGParams);
    }
    return CmdStatus;
}

/**
   @brief Execute Digest command.

   Digest command uses 3 parameters to execute.
   Parameter_List[0] indicates digest algorithm.
   Parameter_List[1] and Parameter_List[2] indicates message length and message string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_Digest_Params_t DigestParams;

    memset(&DigestParams, 0, sizeof(DigestParams));
    do
    {
        if ((Parameter_Count != 3) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        DigestParams.Algo       = (qapi_CRPT_Digest_Algo_t) Parameter_List[0].Integer_Value;
        DigestParams.MessageLen = Parameter_List[1].Integer_Value;

        DigestParams.Message = GetArrayFromHexString(Parameter_List[2].String_Value, DigestParams.MessageLen, QCLI_Crypto_Handle);
        if (DigestParams.Message == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        DigestParams.DigestLen = DigestParams.Algo == QAPI_CRPT_DIGEST_ALGO_SHA256_E ? 32 : 64;
        DigestParams.Digest = qapi_Malloc(DigestParams.DigestLen);
        if (DigestParams.Digest == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(DigestParams.Digest, 0, DigestParams.DigestLen);

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_Digest(&DigestParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_DIGEST_E, &DigestParams);
    }
    return CmdStatus;
}

/**
   @brief Execute HMAC command.

   HMAC command uses 3 parameters to execute.
   Parameter_List[0] indicates key handle acquired via import key.
   Parameter_List[1] and Parameter_List[2] indicates message length and message string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_HMAC(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_HMAC_256_Params_t HMACParams;

    memset(&HMACParams, 0, sizeof(HMACParams));
    do
    {
        if ((Parameter_Count != 3) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        HMACParams.KeyHandle  = Parameter_List[0].Integer_Value;
        HMACParams.MessageLen = Parameter_List[1].Integer_Value;

        HMACParams.Message = GetArrayFromHexString(Parameter_List[2].String_Value, HMACParams.MessageLen, QCLI_Crypto_Handle);
        if (HMACParams.Message == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        HMACParams.HMACLen = 32;
        HMACParams.HMAC    = qapi_Malloc(HMACParams.HMACLen);
        if (HMACParams.HMAC == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(HMACParams.HMAC, 0, HMACParams.HMACLen);

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_HMAC_256(&HMACParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_HMAC_E, &HMACParams);
    }
    return CmdStatus;
}

/**
   @brief Execute Encrypt command.

   Encrypt command uses 6 parameters to execute.
   Parameter_List[0] indicates AES algorithm.
   Parameter_List[1] indicates key handle acquired via ImportKey.
   Parameter_List[2] and Parameter_List[3] indicates plaintText length and PlainText string respectively.
   Parameter_List[4] and Parameter_List[5] indicates optional AAD length and AAD string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Encrypt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_AES_Encryption_Params_t AESEncryptionParams;
    memset(&AESEncryptionParams, 0, sizeof(qapi_CRPT_AES_Encryption_Params_t));

    do
    {
        if ((Parameter_Count < 4) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        AESEncryptionParams.Algo         = (qapi_CRPT_AES_Algo_t) Parameter_List[0].Integer_Value;
        AESEncryptionParams.KeyHandle    = Parameter_List[1].Integer_Value;
        AESEncryptionParams.PlainTextLen = Parameter_List[2].Integer_Value;

        if (Parameter_Count == 6)
        {
            AESEncryptionParams.AADLen = Parameter_List[4].Integer_Value;
        }

        AESEncryptionParams.PlainText = GetArrayFromHexString(Parameter_List[3].String_Value, AESEncryptionParams.PlainTextLen, QCLI_Crypto_Handle);
        if (AESEncryptionParams.PlainText == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        if (AESEncryptionParams.AADLen > 0)
        {
            AESEncryptionParams.AAD = GetArrayFromHexString(Parameter_List[5].String_Value, AESEncryptionParams.AADLen, QCLI_Crypto_Handle);
            if (AESEncryptionParams.AAD == NULL)
            {
                CmdStatus = QCLI_STATUS_USAGE_E;
                break;
            }
        }

        AESEncryptionParams.EncryptedDataLen = AESEncryptionParams.PlainTextLen;
        AESEncryptionParams.EncryptedData    = qapi_Malloc(AESEncryptionParams.EncryptedDataLen);
        if (AESEncryptionParams.EncryptedData == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(AESEncryptionParams.EncryptedData, 0, AESEncryptionParams.EncryptedDataLen);

        AESEncryptionParams.IVLen = 16;
        AESEncryptionParams.IV    = qapi_Malloc(AESEncryptionParams.IVLen);
        if (AESEncryptionParams.IV == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(AESEncryptionParams.IV, 0, AESEncryptionParams.IVLen);

        AESEncryptionParams.TagLen = 16;
        AESEncryptionParams.Tag    = qapi_Malloc(AESEncryptionParams.TagLen);
        if (AESEncryptionParams.Tag == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(AESEncryptionParams.Tag, 0, AESEncryptionParams.TagLen);

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_AES_Encryption(&AESEncryptionParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ENCRYPT_E, &AESEncryptionParams);
    }
    return CmdStatus;
}

/**
   @brief Execute Decrypt command.

   Decrypt command uses 10 parameters to execute.
   Parameter_List[0] indicates AES algorithm.
   Parameter_List[1] indicates key handle acquired via ImportKey.
   Parameter_List[2] and Parameter_List[3] indicates encrypted string length and encrypted string respectively.
   Parameter_List[4] and Parameter_List[5] indicates IV length and IV string respectively.
   Parameter_List[6] and Parameter_List[7] indicates TAG length and TAG string respectively.
   Parameter_List[8] and Parameter_List[9] indicates AAD length and AAD string respectively.


   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Decrypt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_AES_Decryption_Params_t AESDecryptionParams;

    memset(&AESDecryptionParams, 0, sizeof(qapi_CRPT_AES_Decryption_Params_t));
    do
    {
        if ((Parameter_Count < 6) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        AESDecryptionParams.Algo             = (qapi_CRPT_AES_Algo_t) Parameter_List[0].Integer_Value;
        AESDecryptionParams.KeyHandle        = Parameter_List[1].Integer_Value;
        AESDecryptionParams.EncryptedDataLen = Parameter_List[2].Integer_Value;
        AESDecryptionParams.IVLen            = Parameter_List[4].Integer_Value;

        if (Parameter_Count == 10)
        {
            AESDecryptionParams.TagLen = Parameter_List[6].Integer_Value;
            AESDecryptionParams.AADLen = Parameter_List[8].Integer_Value;
        }

        AESDecryptionParams.EncryptedData = GetArrayFromHexString(Parameter_List[3].String_Value, AESDecryptionParams.EncryptedDataLen, QCLI_Crypto_Handle);
        if (AESDecryptionParams.EncryptedData == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        AESDecryptionParams.IV = GetArrayFromHexString(Parameter_List[5].String_Value, AESDecryptionParams.IVLen, QCLI_Crypto_Handle);
        if (AESDecryptionParams.IV == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        if (AESDecryptionParams.TagLen > 0)
        {
            AESDecryptionParams.Tag = GetArrayFromHexString(Parameter_List[7].String_Value, AESDecryptionParams.TagLen, QCLI_Crypto_Handle);
            if (AESDecryptionParams.Tag == NULL)
            {
                CmdStatus = QCLI_STATUS_USAGE_E;
                break;
            }
        }

        if (AESDecryptionParams.AADLen > 0)
        {
            AESDecryptionParams.AAD = GetArrayFromHexString(Parameter_List[9].String_Value, AESDecryptionParams.AADLen, QCLI_Crypto_Handle);
            if (AESDecryptionParams.AAD == NULL)
            {
                CmdStatus = QCLI_STATUS_USAGE_E;
                break;
            }
        }

        AESDecryptionParams.PlainTextLen = AESDecryptionParams.EncryptedDataLen;
        AESDecryptionParams.PlainText    = qapi_Malloc(AESDecryptionParams.PlainTextLen);
        if (AESDecryptionParams.PlainText == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        memset(AESDecryptionParams.PlainText, 0, AESDecryptionParams.PlainTextLen);

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_AES_Decryption(&AESDecryptionParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_DECRYPT_E, &AESDecryptionParams);
    }
    return CmdStatus;
}

/**
   @brief Execute GenerateKeyPair command.

   GenerateKeyPair command uses 1 parameter to execute.
   Parameter_List[0] indicates curve for generating key pair.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_Generate_Key_pair(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_Generate_Key_Pair_Params_t GenerateKeyPairParams;

    memset(&GenerateKeyPairParams, 0, sizeof(GenerateKeyPairParams));
    do
    {
        if ((Parameter_Count != 1) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        GenerateKeyPairParams.KeyAlgo = (qapi_CRPT_Key_Algo_t) Parameter_List[0].Integer_Value;

        GenerateKeyPairParams.PublicKeyLen =
            GenerateKeyPairParams.KeyAlgo == QAPI_CRPT_KEY_ALGO_ECDSA_256_E ||
            GenerateKeyPairParams.KeyAlgo == QAPI_CRPT_KEY_ALGO_ECDH_256_E ? 64 : 136;
        GenerateKeyPairParams.PublicKey = qapi_Malloc(GenerateKeyPairParams.PublicKeyLen);
        if (GenerateKeyPairParams.PublicKey == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_Generate_Key_Pair(&GenerateKeyPairParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_GENERATE_KEY_PAIR_E, &GenerateKeyPairParams);
    }
    return CmdStatus;
}

/**
   @brief Execute ECCGetPublicKey command.

   ECCGetPublicKey command uses 2 parameters to execute.
   Parameter_List[0] indicates curve.
   Parameter_List[1] indicates private key handle.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECC_Get_Public_Key(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECC_Get_Public_Key_Params_t ECCGetPublicKeyParams;

    memset(&ECCGetPublicKeyParams, 0, sizeof(ECCGetPublicKeyParams));
    do
    {
        if ((Parameter_Count != 2) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        ECCGetPublicKeyParams.Curve            = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECCGetPublicKeyParams.PrivateKeyHandle = Parameter_List[1].Integer_Value;
        ECCGetPublicKeyParams.PublicKeyLen = ECCGetPublicKeyParams.Curve == QAPI_CRPT_ECC_CURVE_NIST_P256_E ? 64 : 136;
        ECCGetPublicKeyParams.PublicKey = qapi_Malloc(ECCGetPublicKeyParams.PublicKeyLen);
        if (ECCGetPublicKeyParams.PublicKey == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory. \n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECC_Get_Public_Key(&ECCGetPublicKeyParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECC_GET_PUBLIC_KEY_E, &ECCGetPublicKeyParams);
    }
    return CmdStatus;
}

/**
   @brief Execute ECDHSharedSecret command.

   ECDHSharedSecret command uses 4 parameters to execute.
   Parameter_List[0] indicates curve to be used.
   Parameter_List[1] indicates private key handle.
   Parameter_List[2] and Parameter_List[3] indicates public key length and public key string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECDH_Shared_Secret(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECDH_Shared_Secret_Params_t ECDHSharedSecretParams;

    memset(&ECDHSharedSecretParams, 0, sizeof(ECDHSharedSecretParams));
    do
    {
        if ((Parameter_Count != 4) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        ECDHSharedSecretParams.Curve            = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECDHSharedSecretParams.PrivateKeyHandle = Parameter_List[1].Integer_Value;
        ECDHSharedSecretParams.PublicKeyLen     = Parameter_List[2].Integer_Value;

        ECDHSharedSecretParams.PublicKey = GetArrayFromHexString(Parameter_List[3].String_Value, ECDHSharedSecretParams.PublicKeyLen, QCLI_Crypto_Handle);
        if (ECDHSharedSecretParams.PublicKey == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }

        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECDH_Shared_Secret(&ECDHSharedSecretParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECDH_SHARED_SECRET_E, &ECDHSharedSecretParams);
    }
    return CmdStatus;
}

/**
   @brief Execute ECDSASignDigest command.

   ECDSASignDigest command uses 4 parameters to execute.
   Parameter_List[0] indicates curve to be used.
   Parameter_List[1] indicates private key handle.
   Parameter_List[2] and Parameter_List[3] indicates digest length and digest string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Sign_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECDSA_Sign_Digest_Params_t ECDSASignDigestParams;

    memset(&ECDSASignDigestParams, 0, sizeof(ECDSASignDigestParams));
    do
    {
        if ((Parameter_Count != 4) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSASignDigestParams.Curve            = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECDSASignDigestParams.PrivateKeyHandle = Parameter_List[1].Integer_Value;
        ECDSASignDigestParams.DigestLen        = Parameter_List[2].Integer_Value;

        ECDSASignDigestParams.Digest = GetArrayFromHexString(Parameter_List[3].String_Value, ECDSASignDigestParams.DigestLen, QCLI_Crypto_Handle);
        if (ECDSASignDigestParams.Digest == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSASignDigestParams.SignatureLen = ECDSASignDigestParams.Curve == QAPI_CRPT_ECC_CURVE_NIST_P256_E ? 64 : 136;
        ECDSASignDigestParams.Signature = qapi_Malloc(ECDSASignDigestParams.SignatureLen);
        if (ECDSASignDigestParams.Signature == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECDSA_Sign_Digest(&ECDSASignDigestParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECDSA_SIGN_DIGEST_E, &ECDSASignDigestParams);
    }
    return CmdStatus;
}

/**
   @brief Execute ECDSAVerifyDigest command.

   ECDSAVerifyDigest command uses 7 parameters to execute.
   Parameter_List[0] indicates curve to be used.
   Parameter_List[1] and Parameter_List[2] indicates public key length and public key string respectively.
   Parameter_List[3] and Parameter_List[4] indicates digest length and digest string respectively.
   Parameter_List[5] and Parameter_List[6] indicates signature length and signature string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Verify_Digest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;
    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECDSA_Verify_Digest_Params_t ECDSAVerifyDigestParams;

    memset(&ECDSAVerifyDigestParams, 0, sizeof(ECDSAVerifyDigestParams));
    do
    {
        if ((Parameter_Count != 7) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyDigestParams.Curve        = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECDSAVerifyDigestParams.PublicKeyLen = Parameter_List[1].Integer_Value;
        ECDSAVerifyDigestParams.DigestLen    = Parameter_List[3].Integer_Value;
        ECDSAVerifyDigestParams.SignatureLen = Parameter_List[5].Integer_Value;

        ECDSAVerifyDigestParams.PublicKey = GetArrayFromHexString(Parameter_List[2].String_Value, ECDSAVerifyDigestParams.PublicKeyLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyDigestParams.PublicKey == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyDigestParams.Digest = GetArrayFromHexString(Parameter_List[4].String_Value, ECDSAVerifyDigestParams.DigestLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyDigestParams.Digest == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyDigestParams.Signature = GetArrayFromHexString(Parameter_List[6].String_Value, ECDSAVerifyDigestParams.SignatureLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyDigestParams.Signature == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECDSA_Verify_Digest(&ECDSAVerifyDigestParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECDSA_VERIFY_DIGEST_E, &ECDSAVerifyDigestParams);
    }
    return CmdStatus;
}

/**
   @brief Execute  ECDSASignMessage command.

   ECDSASignMessage command uses 5 parameters to execute.
   Parameter_List[0] indicates curve to be used.
   Parameter_List[1] indicates digest algorithm.
   Parameter_List[2] indicates private key handle.
   Parameter_List[3] and Parameter_List[4] indicates message length and message string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Sign_Message(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECDSA_Sign_Message_Params_t ECDSASignMessageParams;
    memset(&ECDSASignMessageParams, 0, sizeof(ECDSASignMessageParams));
    do
    {
        if ((Parameter_Count != 5) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSASignMessageParams.Curve            = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECDSASignMessageParams.Algo             = (qapi_CRPT_Digest_Algo_t) Parameter_List[1].Integer_Value;
        ECDSASignMessageParams.PrivateKeyHandle = Parameter_List[2].Integer_Value;
        ECDSASignMessageParams.MessageLen       = Parameter_List[3].Integer_Value;

        ECDSASignMessageParams.Message = GetArrayFromHexString(Parameter_List[4].String_Value, ECDSASignMessageParams.MessageLen, QCLI_Crypto_Handle);
        if (ECDSASignMessageParams.Message == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSASignMessageParams.SignatureLen = ECDSASignMessageParams.Curve == QAPI_CRPT_ECC_CURVE_NIST_P256_E ? 64 : 136;
        ECDSASignMessageParams.Signature = qapi_Malloc(ECDSASignMessageParams.SignatureLen);
        if (ECDSASignMessageParams.Signature == NULL)
        {
            QCLI_Printf(QCLI_Crypto_Handle, "ERROR: No enough memory.\n");
            CmdStatus = QCLI_STATUS_ERROR_E;
            break;
        }
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECDSA_Sign_Message(&ECDSASignMessageParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECDSA_SIGN_MESSAGE_E, &ECDSASignMessageParams);
    }

    return CmdStatus;
}

/**
   @brief Execute ECDSAVerifyMessage command.

   ECDSAVerifyMessage command uses 8 parameters to execute.
   Parameter_List[0] indicates curve to be used.
   Parameter_List[1] indicates digest algorithm.
   Parameter_List[2] and Parameter_List[3] indicates public key length and public key string respectively.
   Parameter_List[4] and Parameter_List[5] indicates message length and message string respectively.
   Parameter_List[6] and Parameter_List[7] indicates signature length and signature string respectively.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_Crypto_ECDSA_Verify_Message(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t            Status     = QAPI_ERROR;
    qbool_t                  IsBlocking = CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE;
    QCLI_Command_Status_t    CmdStatus  = QCLI_STATUS_ERROR_E;
    qapi_CRPT_Operation_CB_t Callback   = NULL;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_CRPT_ECDSA_Verify_Message_Params_t ECDSAVerifyMessageParams;
    memset(&ECDSAVerifyMessageParams, 0, sizeof(ECDSAVerifyMessageParams));

    do
    {
        if ((Parameter_Count != 8) || (Parameter_List == NULL))
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyMessageParams.Curve        = (qapi_CRPT_ECC_Curve_t) Parameter_List[0].Integer_Value;
        ECDSAVerifyMessageParams.Algo         = (qapi_CRPT_Digest_Algo_t) Parameter_List[1].Integer_Value;
        ECDSAVerifyMessageParams.PublicKeyLen = Parameter_List[2].Integer_Value;
        ECDSAVerifyMessageParams.MessageLen   = Parameter_List[4].Integer_Value;
        ECDSAVerifyMessageParams.SignatureLen = Parameter_List[6].Integer_Value;
        ECDSAVerifyMessageParams.PublicKey = GetArrayFromHexString(Parameter_List[3].String_Value, ECDSAVerifyMessageParams.PublicKeyLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyMessageParams.PublicKey == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyMessageParams.Message = GetArrayFromHexString(Parameter_List[5].String_Value, ECDSAVerifyMessageParams.MessageLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyMessageParams.Message == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        ECDSAVerifyMessageParams.Signature = GetArrayFromHexString(Parameter_List[7].String_Value, ECDSAVerifyMessageParams.SignatureLen, QCLI_Crypto_Handle);
        if (ECDSAVerifyMessageParams.Signature == NULL)
        {
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        }
        if (IsBlocking == false)
        {
            Callback = Crypto_CmdOperationCB;
        }
        Status = qapi_CRPT_ECDSA_Verify_Message(&ECDSAVerifyMessageParams, Callback, NULL);
        CmdStatus = GetQcliStatusFromQapiStatus(Status);
    } while (0);

    if ((IsBlocking) || (CmdStatus != QCLI_STATUS_SUCCESS_E))
    {
        Crypto_Handle_Response(Status, QAPI_CRPT_OPERATION_ECDSA_VERIFY_MESSAGE_E, &ECDSAVerifyMessageParams);
    }
    return CmdStatus;
}