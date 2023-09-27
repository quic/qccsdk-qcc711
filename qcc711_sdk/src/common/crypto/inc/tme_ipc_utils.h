/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_ipc_utils.h
 * @brief The utility structures, functions and enums related to TME IPC.                    
 */
#ifndef TME_IPC_UTILS_H
#define TME_IPC_UTILS_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"
#include "TmecomClient.h"
#include "tme_ipc_msg_uid_mapping.h"
#include "tme_types.h"

/* Buffer size in bytes. */
#define BUFFER_SIZE_32 32
#define BUFFER_SIZE_64 64

/*! Calculate the number of elements in array. */
#define ARRAY_ELEMENTS(arr) (sizeof(arr)/sizeof(arr[0]))

/* Get TME digest algo from QAPI digest algo. */
#define QAPI_CRPT_GET_TME_DIGEST_ALGO(algo)         (TMEDigestAlgo) \
      ((algo == QAPI_CRPT_DIGEST_ALGO_SHA256_E) ? TME_DALG_SHA256 : \
      ((algo == QAPI_CRPT_DIGEST_ALGO_SHA512_E) ? TME_DALG_SHA512 : 0))
      
/* Get TME ecc curve from QAPI ecc curve. */
#define QAPI_CRPT_GET_TME_ECC_CURVE(curve)                      (TMEECCCurve) \
      ((curve == QAPI_CRPT_ECC_CURVE_NIST_P256_E) ? TME_ECC_CURVE_NIST_P256 : \
      ((curve == QAPI_CRPT_ECC_CURVE_NIST_P521_E) ? TME_ECC_CURVE_NIST_P521 : 0))
/**
   @brief Convert tmecom status to qapi status

   @param[in] Status   TMECOM status.

   @return Corresponding qapi status will be returned.
*/
qapi_Status_t qapi_Convert_Tmecom_Status(TmecomResponse_t Status);

/**
   @brief Convert tme status to qapi status

   @param[in] Status   TMEStatus status.

   @return Corresponding qapi status will be returned.
*/
qapi_Status_t qapi_Convert_Tme_Status(TMEStatus Status);

/**
   @brief Perform operation based on message ID.

   @param[in] TmeMsgUid         TME request identifier.
   @param[in] TmeMsgParamID     TME message param ID.
   @param[in] QapiCryptoParams  qapi crypto parameters.
   @param[in] Callback          qapi callback function.
   @param[in] UserData          Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.

*/
qapi_Status_t qapi_Perform_Operation(uint32_t     TmeMsgUid,
                                     uint32_t     TmeMsgParamID,
                                     void        *QapiCryptoParams,
                                     void        *Callback,
                                     void        *UserParam);

// clang-format on
#endif /* TME_IPC_UTILS_H */
