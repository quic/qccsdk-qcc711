#ifndef TMEMESSAGESUIDS_H
#define TMEMESSAGESUIDS_H

/**
   @file TmeMessagesUids.h
   @brief Defines all TME messages unique identifiers & their parameters.
*/

/*==============================================================================
     Copyright (c) 2020 - 2023 QUALCOMM Technologies Incorporated.
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*----------------------------------------------------------------------------
 * Documentation
 * -------------------------------------------------------------------------*/

/*     TME Messages Unique Identifiers bit layout
    _____________________________________
   |           |            |           |
   | 31------16| 15-------8 | 7-------0 |
   | Reserved  |messageType | actionID  |
   |___________|____________|___________|
               \___________  ___________/
                           \/
                      TME_MSG_UID
*/

/*   TME Messages Unique Identifiers Parameter ID bit layout
_________________________________________________________________________________________
|     |     |     |     |     |     |     |     |     |     |     |    |    |    |       |
|31-30|29-28|27-26|25-24|23-22|21-20|19-18|17-16|15-14|13-12|11-10|9--8|7--6|5--4|3-----0|
| p14 | p13 | p12 | p11 | p10 | p9  | p8  | p7  | p6  | p5  | p4  | p3 | p2 | p1 | nargs |
|type |type |type |type |type |type |type |type |type |type |type |type|type|type|       |
|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|____|____|____|_______|

*/

/** General helper macro to create a bitmask from bits low to high. */
#define MASK_BITS_FROM_UINT32(h,l)     ((0xffffffff >> (32 - ((h - l) + 1))) << l)

/**
   Macro used to define unique TME Message Identifier based on
   message type and action identifier.
*/
#define TME_MSG_UID_CREATE(m, a) \
  ((uint32_t)(((m & 0xff) << 8) | (a & 0xff)))

/** Helper macro to extract the messageType from TME_MSG_UID. */
#define TME_MSG_UID_MSG_TYPE(v)      ((v & MASK_BITS_FROM_UINT32(15,8)) >> 8)

/** Helper macro to extract the actionID from TME_MSG_UID. */
#define TME_MSG_UID_ACTION_ID(v)     (v & MASK_BITS_FROM_UINT32(7,0))


/**
   Helper Macros to create paramID for every unique TME Message Identifier.
*/
/** A parameter of type value. TME receive data as part of request, can also use to send respose. */
#define TME_MSG_PARAM_TYPE_VAL                0x0
/**
   A parameter of type input only. TME receive data through buffer as part of request,
   doesn't send response through it. It consist of 2 actual uint32_t param (ipBufAddr & ipBufLen)
   ipBufAddr  - Address of the buffer. TME should't change it.
   ipBufLen   - Byte length of input data to be consumed by TME. TME shouldn't change it.
*/
#define TME_MSG_PARAM_TYPE_BUF_IN             0x1
/**
   A parameter of type output only. TME doesn't receive data through buffer as part of request,
   instead use this buffer to send response.
   It consist of 3 actual uint32_t param (outBufAddr, outBufLen & outBufOutLen).
   outBufAddr   - Address of the buffer. TME shouldn't change it.
   outBufLen    - Indiactes actual/allocated size of the buffer, TME shouldn't change it.
   outBufOutLen - TME update to actual out data length in byte.
*/
#define TME_MSG_PARAM_TYPE_BUF_OUT            0x2
/**
   A parameter of type both input & output. TME can receive data through the buffer,
   as well can use this buffer to send response.
   It consist of 3 actual uint32_t param (inOutBufAddr, inOutBufLen & inOutBufInOutLen).
   inOutBufAddr     - Address of the buffer. TME shouldn't change it.
   inOutBufLen      - Indiactes actual/allocated size of the buffer, TME shouldn't change it.
   inOutBufInOutLen - can hold actual input data length during request
                      & TME update to actual out data length in byte for a response.
*/
#define TME_MSG_PARAM_TYPE_BUF_IN_OUT         0x3

/** Parameter ID nargs bitmask. */
#define TME_MSG_PARAM_ID_NARGS_MASK        MASK_BITS_FROM_UINT32(3,0)
/** Parameter ID parameter type bitmask. */
#define TME_MSG_PARAM_ID_PARAM_TYPE_MASK   MASK_BITS_FROM_UINT32(1,0)

/** Internal helper macro for __TME_MSG_CREATE_PARAM_ID. */
#define _TME_MSG_CREATE_PARAM_ID(nargs, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, ...) \
  (((nargs)& TME_MSG_PARAM_ID_NARGS_MASK)+ \
  (((p1) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<4)+  \
  (((p2) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<6)+  \
  (((p3) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<8)+  \
  (((p4) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<10)+ \
  (((p5) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<12)+ \
  (((p6) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<14)+ \
  (((p7) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<16)+ \
  (((p8) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<18)+ \
  (((p9) & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<20)+ \
  (((p10)& TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<22)+ \
  (((p11)& TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<24)+ \
  (((p12)& TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<26)+ \
  (((p13)& TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<28)+ \
  (((p14)& TME_MSG_PARAM_ID_PARAM_TYPE_MASK)<<30))

/** Internal helper macro to get nargs from paramID */
#define TME_MSG_PARAM_ID_GET_NARGS(v)      (v & TME_MSG_PARAM_ID_NARGS_MASK)

/** Internal helper macro to get ith parameter from paramID */
#define TME_MSG_PARAM_ID_GET_PARAM_TYPEi(v, i)   ((v>>((2*i)+4))  & TME_MSG_PARAM_ID_PARAM_TYPE_MASK)

/** Internal helper macro for TME_MSG_CREATE_PARAM_ID_X */
#define __TME_MSG_CREATE_PARAM_ID(...) \
  _TME_MSG_CREATE_PARAM_ID(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

/** Macro used to create a parameter ID with no arguments. */
#define TME_MSG_CREATE_PARAM_ID_0 \
  __TME_MSG_CREATE_PARAM_ID(0)
/** Macro used to create a parameter ID with one argument. */
#define TME_MSG_CREATE_PARAM_ID_1(p1) \
  __TME_MSG_CREATE_PARAM_ID(1, p1)
/** Macro used to create a parameter ID with two arguments. */
#define TME_MSG_CREATE_PARAM_ID_2(p1, p2) \
  __TME_MSG_CREATE_PARAM_ID(2, p1, p2)
/** Macro used to create a parameter ID with three arguments. */
#define TME_MSG_CREATE_PARAM_ID_3(p1, p2, p3) \
  __TME_MSG_CREATE_PARAM_ID(3, p1, p2, p3)
/** Macro used to create a parameter ID with four arguments. */
#define TME_MSG_CREATE_PARAM_ID_4(p1, p2, p3, p4) \
  __TME_MSG_CREATE_PARAM_ID(4, p1, p2, p3, p4)
/** Macro used to create a parameter ID with five arguments. */
#define TME_MSG_CREATE_PARAM_ID_5(p1, p2, p3, p4, p5) \
  __TME_MSG_CREATE_PARAM_ID(5, p1, p2, p3, p4, p5)
/** Macro used to create a parameter ID with six arguments. */
#define TME_MSG_CREATE_PARAM_ID_6(p1, p2, p3, p4, p5, p6) \
  __TME_MSG_CREATE_PARAM_ID(6, p1, p2, p3, p4, p5, p6)
/** Macro used to create a parameter ID with seven arguments. */
#define TME_MSG_CREATE_PARAM_ID_7(p1, p2, p3, p4, p5, p6, p7) \
  __TME_MSG_CREATE_PARAM_ID(7, p1, p2, p3, p4, p5, p6, p7)
/** Macro used to create a parameter ID with eight arguments. */
#define TME_MSG_CREATE_PARAM_ID_8(p1, p2, p3, p4, p5, p6, p7, p8) \
  __TME_MSG_CREATE_PARAM_ID(8, p1, p2, p3, p4, p5, p6, p7, p8)
/** Macro used to create a parameter ID with nine arguments. */
#define TME_MSG_CREATE_PARAM_ID_9(p1, p2, p3, p4, p5, p6, p7, p8, p9) \
  __TME_MSG_CREATE_PARAM_ID(9, p1, p2, p3, p4, p5, p6, p7, p8, p9)
/** Macro used to create a parameter ID with ten arguments. */
#define TME_MSG_CREATE_PARAM_ID_10(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
  __TME_MSG_CREATE_PARAM_ID(10, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
/** Macro used to create a parameter ID with eleven arguments. */
#define TME_MSG_CREATE_PARAM_ID_11(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
  __TME_MSG_CREATE_PARAM_ID(11, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
/** Macro used to create a parameter ID with twelve arguments. */
#define TME_MSG_CREATE_PARAM_ID_12(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
  __TME_MSG_CREATE_PARAM_ID(12, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)
/** Macro used to create a parameter ID with thirteen arguments. */
#define TME_MSG_CREATE_PARAM_ID_13(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13) \
  __TME_MSG_CREATE_PARAM_ID(13, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13)
/** Macro used to create a parameter ID with fourteen arguments. */
#define TME_MSG_CREATE_PARAM_ID_14(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14) \
  __TME_MSG_CREATE_PARAM_ID(14, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14)


/****************************************************************************
 *
 * All definitions of supported messageType's.
 *
 * 0x00 -> 0xF0 messageType used for production use cases.
 * 0xF1 -> 0xFF messageType reserved(can be used for test puprposes).
 *
 * <Template> : TME_MSG_<MSGTYPE_NAME>
 * **************************************************************************/
#define TME_MSG_SECBOOT                 0x00
#define TME_MSG_CRYPTO                  0x01
#define TME_MSG_MC3                     0x02
#define TME_MSG_FUSE                    0x03
#define TME_MSG_ACCESS_CONTROL          0x04
#define TME_MSG_ATTESTATION             0x05
#define TME_MSG_ONBOARDING              0x06
#define TME_MSG_KEY                     0x07
#define TME_MSG_FWUP                    0x08
#define TME_MSG_LOG                     0x09
#define TME_MSG_FEATURE_QUERY           0x0A
#define TME_MSG_GENERIC                 0x0B

/* Test use-cases */
#define TME_MSG_LOOPBACK_TEST           0xFF

/****************************************************************************
 *
 * All definitions of action ID's per messageType.
 *
 * 0x00 -> 0xBF actionID used for production use cases.
 * 0xC0 -> 0xFF messageType must be reserved for test use cases.
 *
 * NOTE: Test ID's shouldn't appear in this file.
 *
 * <Template> : TME_ACTION_<MSGTYPE_NAME>_<ACTIONID_NAME>
 * **************************************************************************/

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_SECBOOT
 *-------------------------------------------------------------------------*/
#define TME_ACTION_SECBOOT_REQ                          0x01
#define TME_ACTION_SECBOOT_BT_PATCH_AUTH                0x02
#define TME_ACTION_SECBOOT_OEM_MRC_STATE_UPDATE         0x03

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_CRYPTO
 *-------------------------------------------------------------------------*/
#define TME_ACTION_CRYPTO_INVALID                       0x00
#define TME_ACTION_CRYPTO_GET_RANDOM                    0x01
#define TME_ACTION_CRYPTO_GET_RANDOM_ECC_VALUE          0x02
#define TME_ACTION_CRYPTO_ECC_PUB_EXTRACT               0x03
#define TME_ACTION_CRYPTO_MULTIPLY_ECC_VALUE            0x04
#define TME_ACTION_CRYPTO_DIGEST                        0x05
#define TME_ACTION_CRYPTO_DIGEST_EX                     0x06
#define TME_ACTION_CRYPTO_GENERATE_KEYPAIR              0x07
#define TME_ACTION_CRYPTO_KEY_IMPORT                    0x08
#define TME_ACTION_CRYPTO_KEY_CLEAR                     0x09
#define TME_ACTION_CRYPTO_HMAC                          0x0A
#define TME_ACTION_CRYPTO_AES_ENCRYPT_EX                0x0B
#define TME_ACTION_CRYPTO_AES_DECRYPT_EX                0x0C
#define TME_ACTION_CRYPTO_ECDSA_SIGN_BUFFER             0x0D
#define TME_ACTION_CRYPTO_ECDSA_VERIFY_BUFFER           0x0E
#define TME_ACTION_CRYPTO_ECDSA_SIGN_DIGEST             0x0F
#define TME_ACTION_CRYPTO_ECDSA_VERIFY_DIGEST           0x10
#define TME_ACTION_CRYPTO_ECC_GET_PUBLIC_KEY            0x11
#define TME_ACTION_CRYPTO_GENERATE_KEY                  0x12
#define TME_ACTION_CRYPTO_DERIVE_SHARED_SECRET          0x13
#define TME_ACTION_CRYPTO_ECC_MUL_POINT_BY_GEN          0x14
#define TME_ACTION_CRYPTO_DERIVE_KEY                    0x15

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_MC3
 *-------------------------------------------------------------------------*/
#define TME_ACTION_MC3_INVALID                          0x00
#define TME_ACTION_MC3_AUTHENTICATION_REQ               0x01
#define TME_ACTION_MC3_ATTESTATION_REQ                  0x02
#define TME_ACTION_MC3_ONBOARDING_REQ                   0x03
#define TME_ACTION_MC3_ONBOARDING_CONFIRMATION          0x04
#define TME_ACTION_MC3_DECRYPT_MESSAGE_REQ              0x05
#define TME_ACTION_MC3_DECRYPT_MESSAGE_CONFIRMATION     0x06
#define TME_ACTION_MC3_AUTHENTICATE_MSG_REQ             0x07
#define TME_ACTION_MC3_AUTHENTICATE_MSG_CONFIRMATION    0x08

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_FUSE
 *-------------------------------------------------------------------------*/
#define TME_ACTION_FUSE_READ_SINGLE                     0x00
#define TME_ACTION_FUSE_READ_MULTIPLE                   0x01
#define TME_ACTION_FUSE_WRITE_SINGLE                    0x02
#define TME_ACTION_FUSE_WRITE_MULTIPLE                  0x03
#define TME_ACTION_FUSE_WRITE_SECURE                    0x04

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_ACCESS_CONTROL
 *-------------------------------------------------------------------------*/
#define TME_ACTION_ACCESS_CONTROL_INVALID               0x00
#define TME_ACTION_ACCESS_CONTROL_NVM_REGISTER          0x01

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_FWUP
 *-------------------------------------------------------------------------*/
#define TME_ACTION_FWUP_VERIFY_UPDATE                   0x01
#define TME_ACTION_FWUP_APPLY_UPDATE           	        0x02

/*----------------------------------------------------------------------------
  Action ID's for TME_MSG_LOG
 *-------------------------------------------------------------------------*/
#define TME_ACTION_LOG_SET_CONFIG                       0x00
#define TME_ACTION_LOG_GET_CONFIG                       0x01
#define TME_ACTION_LOG_GET                              0x02

/*--------------------------------------------------------------------------
  Action ID's for TME_MSG_FEATURE_QUERY
 *-------------------------------------------------------------------------*/
#define TME_ACTION_FEATURE_LICENSE_BTSS                 0x00
#define TME_ACTION_FEATURE_PATCH_VERSION                0x01

/*--------------------------------------------------------------------------
  Action ID's for TME_MSG_GENERIC
 *-------------------------------------------------------------------------*/
#define TME_ACTION_MSG_GENERIC_INVALID                0x00
#define TME_ACTION_MSG_GENERIC_NVM_WRITE_EX           0x01
#define TME_ACTION_MSG_GENERIC_NVM_READ_EX            0x02

/****************************************************************************
 *
 * All definitions of TME Message UID's (messageType | actionID) and paramID
 * for each UID.
 *
 * <Template> : TME_MSG_UID_<MSGTYPE_NAME>_<ACTIONID_NAME>
 * <Template> : TME_MSG_UID_<MSGTYPE_NAME>_<ACTIONID_NAME>_PARAM_ID
 * *************************************************************************/

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_SECBOOT
 *-------------------------------------------------------------------------*/
/*
 * BT patch Authentication Request.
 * param_id (Elfhdr pointer, program header pointer, hash table pointer, response)
 */
#define TME_MSG_UID_SECBOOT_BT_PATCH_AUTH  TME_MSG_UID_CREATE(TME_MSG_SECBOOT,\
                                            TME_ACTION_SECBOOT_BT_PATCH_AUTH)

#define TME_MSG_UID_SECBOOT_BT_PATCH_AUTH_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4(\
                                                    TME_MSG_PARAM_TYPE_BUF_IN,\
                                                    TME_MSG_PARAM_TYPE_BUF_IN,\
                                                    TME_MSG_PARAM_TYPE_BUF_IN,\
                                                    TME_MSG_PARAM_TYPE_VAL)

/*
 * OEM MRC Update Request
 * param_id (MRC activation VAl, MRC Revocation Val and response Val)
 */
#define TME_MSG_UID_SECBOOT_OEM_MRC_STATE_UPDATE    TME_MSG_UID_CREATE(TME_MSG_SECBOOT,\
                                                        TME_ACTION_SECBOOT_OEM_MRC_STATE_UPDATE)

#define TME_MSG_UID_SECBOOT_OEM_MRC_STATE_UPDATE_PARAM_ID  TME_MSG_CREATE_PARAM_ID_3(\
                                                            TME_MSG_PARAM_TYPE_VAL, \
                                                            TME_MSG_PARAM_TYPE_VAL, \
                                                            TME_MSG_PARAM_TYPE_VAL)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_CRYPTO
 *-------------------------------------------------------------------------*/

/*
 * Generate Random Data.
 * @param_id (length, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_GET_RANDOM    TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                             TME_ACTION_CRYPTO_GET_RANDOM)

#define TME_MSG_UID_CRYPTO_GET_RANDOM_PARAM_ID    TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL,\
                                                      TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Generate Random ECC.
 * @param_id (curve, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_GET_RANDOM_ECC_VALUE      TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_GET_RANDOM_ECC_VALUE)
#define TME_MSG_UID_CRYPTO_GET_RANDOM_ECC_VALUE_PARAM_ID    TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL,\
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Generate ECC Pub.
 * @param_id (curve, pvtKeyBuf, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_ECC_PUB_EXTRACT           TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECC_PUB_EXTRACT)
#define TME_MSG_UID_CRYPTO_ECC_PUB_EXTRACT_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Multiply ECC value by point message
 * @param_id (curve, pvtKeyBuf, pubKeyBuf, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_MULTIPLY_ECC_VALUE        TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_MULTIPLY_ECC_VALUE)
#define TME_MSG_UID_CRYPTO_MULTIPLY_ECC_VALUE_PARAM_ID   TME_MSG_CREATE_PARAM_ID_5( TME_MSG_PARAM_TYPE_VAL, \
                                                             TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                             TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Digest
 * @param_id (algo, inBuf, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_DIGEST                    TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_DIGEST)
#define TME_MSG_UID_CRYPTO_DIGEST_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Digest_Ex
 * @param_id (algo, numInputs, inBuf, status, rspBuf)
 */
#define TME_MSG_UID_CRYPTO_DIGEST_EX                 TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_DIGEST_EX)
#define TME_MSG_UID_CRYPTO_DIGEST_EX_PARAM_ID   TME_MSG_CREATE_PARAM_ID_5( TME_MSG_PARAM_TYPE_VAL, \
                                                    TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                    TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Generate KeyPair
 * @param_id (curve, status, pubKeyBuf, pvtKeyHandle)
 */
#define TME_MSG_UID_CRYPTO_GENERATE_KEYPAIR          TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_GENERATE_KEYPAIR)
#define TME_MSG_UID_CRYPTO_GENERATE_KEYPAIR_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                          TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                          TME_MSG_PARAM_TYPE_BUF_OUT, TME_MSG_PARAM_TYPE_VAL)

/*
 * Import Key
 * @param_id (keyMaterialBuf, keyConfig, status, keyHandle)
 */
#define TME_MSG_UID_CRYPTO_KEY_IMPORT                TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_KEY_IMPORT)
#define TME_MSG_UID_CRYPTO_KEY_IMPORT_PARAM_ID       TME_MSG_CREATE_PARAM_ID_4( \
                                                          TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                          TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * Clear Key
 * @param_id (keyHandle, status)
 */
#define TME_MSG_UID_CRYPTO_KEY_CLEAR                 TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_KEY_CLEAR)
#define TME_MSG_UID_CRYPTO_KEY_CLEAR_PARAM_ID        TME_MSG_CREATE_PARAM_ID_2( \
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * HMAC
 * @param_id (algo, inBuf, initialMac, keyHandle, status, response)
 */
#define TME_MSG_UID_CRYPTO_HMAC                      TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_HMAC)
#define TME_MSG_UID_CRYPTO_HMAC_PARAM_ID             TME_MSG_CREATE_PARAM_ID_6( \
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * AES Encryption Ex
 * @param_id (keyBuf, keyHandle, algo, ptBuf, aadBuf, status, ctBuf, ivBuf, tagBuf)
 */
#define TME_MSG_UID_CRYPTO_AES_ENCRYPT_EX            TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_AES_ENCRYPT_EX)
#define TME_MSG_UID_CRYPTO_AES_ENCRYPT_EX_PARAM_ID   TME_MSG_CREATE_PARAM_ID_9( \
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                         TME_MSG_PARAM_TYPE_VAL,TME_MSG_PARAM_TYPE_BUF_IN,\
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                         TME_MSG_PARAM_TYPE_BUF_OUT, TME_MSG_PARAM_TYPE_BUF_OUT,\
                                                         TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * AES Decryption Ex
 * @param_id (keyBuf, keyHandle, algo, ctBuf, ivBuf, aadBuf, tagBuf, status, response)
 */
#define TME_MSG_UID_CRYPTO_AES_DECRYPT_EX            TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_AES_DECRYPT_EX)
#define TME_MSG_UID_CRYPTO_AES_DECRYPT_EX_PARAM_ID   TME_MSG_CREATE_PARAM_ID_9( \
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                         TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                         TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                         TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * ECDSA Signature
 * @param_id (algo, keyHandle, curve, ptBuf,  status, response)
 */
#define TME_MSG_UID_CRYPTO_ECDSA_SIGN_BUFFER             TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                             TME_ACTION_CRYPTO_ECDSA_SIGN_BUFFER)
#define TME_MSG_UID_CRYPTO_ECDSA_SIGN_BUFFER_PARAM_ID    TME_MSG_CREATE_PARAM_ID_6( \
                                                             TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                             TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                             TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * ECDSA Verify
 * @param_id (algo, pubKeyBuf, curve, ptBuf, sigBuf, status)
 */
#define TME_MSG_UID_CRYPTO_ECDSA_VERIFY_BUFFER       TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECDSA_VERIFY_BUFFER)
#define TME_MSG_UID_CRYPTO_ECDSA_VERIFY_BUFFER_PARAM_ID    TME_MSG_CREATE_PARAM_ID_6( \
                                                               TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                               TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                               TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL)

/*
 * ECDSA Signature Digest
 * @param_id (keyHandle, curve, digestBuf,  status, response)
 */
#define TME_MSG_UID_CRYPTO_ECDSA_SIGN_DIGEST         TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECDSA_SIGN_DIGEST)
#define TME_MSG_UID_CRYPTO_ECDSA_SIGN_DIGEST_PARAM_ID   TME_MSG_CREATE_PARAM_ID_5( \
                                                            TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                            TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                            TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * ECDSA Verify Digest
 * @param_id (pubkeyBuf, curve, digestBuf,  sigBuf, status)
 */
#define TME_MSG_UID_CRYPTO_ECDSA_VERIFY_DIGEST       TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECDSA_VERIFY_DIGEST)
#define TME_MSG_UID_CRYPTO_ECDSA_VERIFY_DIGEST_PARAM_ID    TME_MSG_CREATE_PARAM_ID_5( \
                                                               TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                               TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                               TME_MSG_PARAM_TYPE_VAL)

/*
 * ECC Get Public Key
 * @param_id (curve, keyHandle, status, response)
 */
#define TME_MSG_UID_CRYPTO_ECC_GET_PUBLIC_KEY        TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECC_GET_PUBLIC_KEY)
#define TME_MSG_UID_CRYPTO_ECC_GET_PUBLIC_KEY_PARAM_ID    TME_MSG_CREATE_PARAM_ID_4( \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Generate Key
 * @param_id (keyConfig, status, keyHandle)
 */
#define TME_MSG_UID_CRYPTO_GENERATE_KEY              TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_GENERATE_KEY)
#define TME_MSG_UID_CRYPTO_GENERATE_KEY_PARAM_ID    TME_MSG_CREATE_PARAM_ID_3( TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * Derive Shared Secret
 * @param_id (curve, keyHandle, pubKeyBuf, status, keyHandle)
 */
#define TME_MSG_UID_CRYPTO_DERIVE_SHARED_SECRET      TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_DERIVE_SHARED_SECRET)
#define TME_MSG_UID_CRYPTO_DERIVE_SHARED_SECRET_PARAM_ID    TME_MSG_CREATE_PARAM_ID_6( \
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                                TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,\
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * ECC Extended Public Key
 * @param_id (curve, pvtKeyBuf, status, response)
 */
#define TME_MSG_UID_CRYPTO_ECC_MUL_POINT_BY_GEN      TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_ECC_MUL_POINT_BY_GEN)
#define TME_MSG_UID_CRYPTO_ECC_MUL_POINT_BY_GEN_PARAM_ID    TME_MSG_CREATE_PARAM_ID_4( \
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Derive Key
 * @param_id (nonceBuf, algo, keyCfg, inKey, labelBuf, status, derivedKey)
 */
#define TME_MSG_UID_CRYPTO_DERIVE_KEY                TME_MSG_UID_CREATE(TME_MSG_CRYPTO,\
                                                         TME_ACTION_CRYPTO_DERIVE_KEY)
#define TME_MSG_UID_CRYPTO_DERIVE_KEY_PARAM_ID   TME_MSG_CREATE_PARAM_ID_7( \
                                                     TME_MSG_PARAM_TYPE_BUF_IN,\
                                                     TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL,\
                                                     TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN,\
                                                     TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_MC3
 *-------------------------------------------------------------------------*/
/*
 * MC3 Authentication
 * @param_id (appDataBuf, status, resposeBuf)
 */
#define TME_MSG_UID_MC3_AUTHENTICATION_REQ          TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                        TME_ACTION_MC3_AUTHENTICATION_REQ)
#define TME_MSG_UID_MC3_AUTHENTICATION_REQ_PARAM_ID TME_MSG_CREATE_PARAM_ID_2( \
                                                        TME_MSG_PARAM_TYPE_VAL, \
                                                        TME_MSG_PARAM_TYPE_BUF_OUT)
/*
 * MC3 Attestation Token construction
 * @param_id (tokenBuf, appDataBuf, publicKeyBuf, status, responseBuf)
 */
#define TME_MSG_UID_MC3_ATTESTATION_REQ           TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                      TME_ACTION_MC3_ATTESTATION_REQ)

#define TME_MSG_UID_MC3_ATTESTATION_REQ_PARAM_ID  TME_MSG_CREATE_PARAM_ID_5( \
                                                      TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN, \
                                                      TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL,    \
                                                      TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * MC3 Onboarding request
 * @param_id (tokenBuf, publicKeyBuf, status, appDataBuf, MECertificateBuf, MECertParamsBuf, sharedSecret)
 */
#define TME_MSG_UID_MC3_ONBOARDING_REQ              TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                        TME_ACTION_MC3_ONBOARDING_REQ)

#define TME_MSG_UID_MC3_ONBOARDING_REQ_PARAM_ID     TME_MSG_CREATE_PARAM_ID_7( \
                                                        TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN, \
                                                        TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT, \
                                                        TME_MSG_PARAM_TYPE_BUF_OUT, TME_MSG_PARAM_TYPE_BUF_OUT, \
                                                        TME_MSG_PARAM_TYPE_VAL)

/*
 * MC3 Onboarding Confirmation
 * @param_id (sharedSecret, appDataBuf, status, responseBuf)
 */
#define TME_MSG_UID_MC3_ONBOARDING_CONFIRMATION    TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                       TME_ACTION_MC3_ONBOARDING_CONFIRMATION)

#define TME_MSG_UID_MC3_ONBOARDING_CONFIRMATION_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN, \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * MC3 Decryption request
 * @param_id (tokenBuf, status, responseBuf, sharedSecret)
 */
#define TME_MSG_UID_MC3_DECRYPT_MESSAGE_REQ        TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                       TME_ACTION_MC3_DECRYPT_MESSAGE_REQ)

#define TME_MSG_UID_MC3_DECRYPT_MESSAGE_REQ_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                          TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL, \
                                                          TME_MSG_PARAM_TYPE_BUF_OUT, TME_MSG_PARAM_TYPE_VAL)

/*
 * MC3 Decryption confirmation request
 * @param_id (sharedSecret, appDataBuf, status, responseBuf)
 */
#define TME_MSG_UID_MC3_DECRYPT_MESSAGE_CONFIRMATION  TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                          TME_ACTION_MC3_DECRYPT_MESSAGE_CONFIRMATION)

#define TME_MSG_UID_MC3_DECRYPT_MESSAGE_CONFIRMATION_PARAM_ID  TME_MSG_CREATE_PARAM_ID_4( \
                                                                   TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_IN, \
                                                                   TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * MC3 Authenticate request
 * @param_d (tokenBuf, publicKeyBuf, status, responseBuf, isVerified)
 */
#define TME_MSG_UID_MC3_AUTHENTICATE_MSG_REQ           TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                           TME_ACTION_MC3_AUTHENTICATE_MSG_REQ)

#define TME_MSG_UID_MC3_AUTHENTICATE_MSG_REQ_PARAM_ID   TME_MSG_CREATE_PARAM_ID_5( \
                                                            TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_BUF_IN, \
                                                            TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT, \
                                                            TME_MSG_PARAM_TYPE_VAL)

/*
 * MC3 Authentication msg confirmation request
 * @param_d (appData, status, responseBuf)
 */
#define TME_MSG_UID_MC3_AUTHENTICATE_MSG_CONFIRMATION            TME_MSG_UID_CREATE(TME_MSG_MC3,\
                                                                     TME_ACTION_MC3_AUTHENTICATE_MSG_CONFIRMATION)

#define TME_MSG_UID_MC3_AUTHENTICATE_MSG_CONFIRMATION_PARAM_ID   TME_MSG_CREATE_PARAM_ID_3( \
                                                                     TME_MSG_PARAM_TYPE_BUF_IN, \
                                                                     TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_BUF_OUT)


/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_FUSE
 *-------------------------------------------------------------------------*/

/*
 * Read single fuse
 * @param_d (status, fuseAddr, fuseVal)
 */
#define TME_MSG_UID_FUSE_READ_SINGLE               TME_MSG_UID_CREATE(TME_MSG_FUSE,\
                                                       TME_ACTION_FUSE_READ_SINGLE)
#define TME_MSG_UID_FUSE_READ_SINGLE_PARAM_ID      TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL,\
                                                       TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)
/*
 * Read multiple fuses
 * @param_d (status, fuseRdData)
 */
#define TME_MSG_UID_FUSE_READ_MULTIPLE             TME_MSG_UID_CREATE(TME_MSG_FUSE,\
                                                       TME_ACTION_FUSE_READ_MULTIPLE)
#define TME_MSG_UID_FUSE_READ_MULTIPLE_PARAM_ID    TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL,\
                                                       TME_MSG_PARAM_TYPE_BUF_IN_OUT)

/*
 * Write single fuse
 * @param_d (status, fuseAddr, fuseVal)
 */
#define TME_MSG_UID_FUSE_WRITE_SINGLE              TME_MSG_UID_CREATE(TME_MSG_FUSE,\
                                                       TME_ACTION_FUSE_WRITE_SINGLE)
#define TME_MSG_UID_FUSE_WRITE_SINGLE_PARAM_ID     TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL,\
                                                       TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * Write multiple fuses
 * @param_d (status, fuseWrData)
 */
#define TME_MSG_UID_FUSE_WRITE_MULTIPLE            TME_MSG_UID_CREATE(TME_MSG_FUSE,\
                                                       TME_ACTION_FUSE_WRITE_MULTIPLE)
#define TME_MSG_UID_FUSE_WRITE_MULTIPLE_PARAM_ID   TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL,\
                                                       TME_MSG_PARAM_TYPE_BUF_IN)

/*
 * Write secure fuse
 * @param_d (status, fuseWrData)
 */
#define TME_MSG_UID_FUSE_WRITE_SECURE               TME_MSG_UID_CREATE(TME_MSG_FUSE,\
                                                        TME_ACTION_FUSE_WRITE_SECURE)
#define TME_MSG_UID_FUSE_WRITE_SECURE_PARAM_ID      TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL,\
                                                        TME_MSG_PARAM_TYPE_BUF_IN)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_ACCESS_CONTROL
 *-------------------------------------------------------------------------*/
/*
 * Provide or release NVM register access
 * @param_id (provideAccess, status)
 */
#define TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER            TME_MSG_UID_CREATE(TME_MSG_ACCESS_CONTROL,\
                                                              TME_ACTION_ACCESS_CONTROL_NVM_REGISTER)
#define TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER_PARAM_ID   TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL)


/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_FWUP
 *-------------------------------------------------------------------------*/
/*
 * Verify udpate manifest
 * @param_id (address, size, verifyAll, status, verificationStatus)
 */
#define TME_MSG_UID_FWUP_VERIFY_UPDATE           TME_MSG_UID_CREATE(TME_MSG_FWUP,\
                                                              TME_ACTION_FWUP_VERIFY_UPDATE)
#define TME_MSG_UID_FWUP_VERIFY_UPDATE_PARAM_ID  TME_MSG_CREATE_PARAM_ID_5(TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)
/*
 * Apply update
 * @param_id (address, size, debug, status)
 */
#define TME_MSG_UID_FWUP_APPLY_UPDATE            TME_MSG_UID_CREATE(TME_MSG_FWUP,\
                                                        TME_ACTION_FWUP_APPLY_UPDATE)
#define TME_MSG_UID_FWUP_APPLY_UPDATE_PARAM_ID   TME_MSG_CREATE_PARAM_ID_4(TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL, \
                                                              TME_MSG_PARAM_TYPE_VAL)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_LOG
 *-------------------------------------------------------------------------*/
/*
 * Set TME Log Config
 * @param_id (status, logConfigBuf)
 */
#define TME_MSG_UID_LOG_SET_CONFIG    TME_MSG_UID_CREATE(TME_MSG_LOG,\
                                             TME_ACTION_LOG_SET_CONFIG)
#define TME_MSG_UID_LOG_SET_CONFIG_PARAM_ID  TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL, \
                                                 TME_MSG_PARAM_TYPE_BUF_IN)

/*
 * Get TME Log Config
 * @param_id (status, logConfigBuf)
 */
#define TME_MSG_UID_LOG_GET_CONFIG    TME_MSG_UID_CREATE(TME_MSG_LOG,\
                                             TME_ACTION_LOG_GET_CONFIG)
#define TME_MSG_UID_LOG_GET_CONFIG_PARAM_ID  TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL, \
                                                 TME_MSG_PARAM_TYPE_BUF_OUT)

/*
 * Get TME Log
 * @param_id (status, logBuffer)
 */
#define TME_MSG_UID_LOG_GET           TME_MSG_UID_CREATE(TME_MSG_LOG,\
                                             TME_ACTION_LOG_GET)
#define TME_MSG_UID_LOG_GET_PARAM_ID  TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL, \
                                                 TME_MSG_PARAM_TYPE_BUF_OUT)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_FEATURE_QUERY
 *-------------------------------------------------------------------------*/
/*
 * Get Feature License Status
 * @param_id (featureMask, status, licenseStatus)
 */
#define TME_MSG_UID_FEATURE_LICENSE_STATUS_BTSS             TME_MSG_UID_CREATE(TME_MSG_FEATURE_QUERY,\
                                                                TME_ACTION_FEATURE_LICENSE_BTSS)
#define TME_MSG_UID_FEATURE_LICENSE_STATUS_BTSS_PARAM_ID    TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL, \
                                                                TME_MSG_PARAM_TYPE_VAL, TME_MSG_PARAM_TYPE_VAL)

/*
 * Get RoT patch version
 * @param_id (responseBuf)
 */
#define TME_MSG_UID_FEATURE_PATCH_VERSION             TME_MSG_UID_CREATE(TME_MSG_FEATURE_QUERY,\
                                                                TME_ACTION_FEATURE_PATCH_VERSION)
#define TME_MSG_UID_FEATURE_PATCH_VERSION_PARAM_ID    TME_MSG_CREATE_PARAM_ID_2(TME_MSG_PARAM_TYPE_VAL, \
                                                                              TME_MSG_PARAM_TYPE_BUF_OUT)

/*----------------------------------------------------------------------------
  UID's & PARAM_ID's for TME_MSG_GENERIC
 *-------------------------------------------------------------------------*/
/*
 * Perform NVM write operation
 * @param_id (Offset, RequestBuf, Status)
 */
#define TME_MSG_UID_GENERIC_NVM_WRITE_EX            TME_MSG_UID_CREATE(TME_MSG_GENERIC,\
                                                                TME_ACTION_MSG_GENERIC_NVM_WRITE_EX)
#define TME_MSG_UID_GENERIC_NVM_WRITE_EX_PARAM_ID   TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL, \
                                                                TME_MSG_PARAM_TYPE_BUF_IN, TME_MSG_PARAM_TYPE_VAL)

/*
 * Perform NVM read operation
 * @param_id (Offset, ResponseBuf, Status)
 */
#define TME_MSG_UID_GENERIC_NVM_READ_EX                TME_MSG_UID_CREATE(TME_MSG_GENERIC,\
                                                                TME_ACTION_MSG_GENERIC_NVM_READ_EX)
#define TME_MSG_UID_GENERIC_NVM_READ_EX_PARAM_ID       TME_MSG_CREATE_PARAM_ID_3(TME_MSG_PARAM_TYPE_VAL, \
                                                                TME_MSG_PARAM_TYPE_BUF_OUT, TME_MSG_PARAM_TYPE_VAL)

#endif // TMEMESSAGESUIDS_H
