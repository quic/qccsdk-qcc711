/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

// Common qapi headers
#include "qapi_types.h"

// crypto headers
#include "qapi_crypto.h"

// TME utility headers
#include "tme_ipc_utils.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Provides a random number of a specified length.

   @param[in,out] RNGParams  RNG operation parameters.
   @param[in]     CryptoCB   Callback function, only used in non-blocking mode.
                             NULL for blocking mode.
   @param[in]     UserParam  User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter RNGParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_RNG(qapi_CRPT_RNG_Params_t   *RNGParams,
                            qapi_CRPT_Operation_CB_t  CryptoCB,
                            void                     *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_GET_RANDOM,
                                 TME_MSG_UID_CRYPTO_GET_RANDOM_PARAM_ID,
                                 RNGParams,
                                 (void *)CryptoCB,
                                 UserParam);
}

/**
   @brief Generates digest for the specified message.

   @param[in,out] DigestParams  Digest operation parameters.
   @param[in]     CryptoCB      Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param[in]     UserParam     User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter DigestParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_CRPT_Digest(qapi_CRPT_Digest_Params_t *DigestParams,
                               qapi_CRPT_Operation_CB_t   CryptoCB,
                               void                      *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_CRYPTO_DIGEST,
                                 TME_MSG_UID_CRYPTO_DIGEST_PARAM_ID,
                                 DigestParams,
                                 (void *)CryptoCB,
                                 UserParam);
}


