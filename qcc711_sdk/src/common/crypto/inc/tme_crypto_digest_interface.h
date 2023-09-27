/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_digest_interface.h
 * @brief IPC's digest related interfaces for TME-FW Crypto Service. Defines
 *        structures for the following crypto requests
 *        <br>Get Digest
 */
#ifndef TME_CRYPTO_DIGEST_INTERFACE_H
#define TME_CRYPTO_DIGEST_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/************************************************
 * Digest Request/Response Structure Definitions
 ************************************************/

/*!
 * @struct TMEDigestMessageRequest
 * @brief Digest message's input structure.
 */

typedef struct PACKED_PREFIX tme_digest_message_request_s
{
    TMEDigestAlgo algo;  /*!< Algorithm to be used for generating digest*/
    TMECBuffer    input; /*!< Input Buffer containing message whose digest need 
                              to be calculated. The calling subsystem will
                              allocate memory and fill the buffer with the 
                              message along with setting the length */
} TMEDigestMessageRequest;

/*!
 * @struct TMEDigestMessageResponse
 * @brief Digest message's output structure.
 */

typedef struct PACKED_PREFIX tme_digest_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the 
                                      generated digest. Memory for the containing buffer
                                      is to be allocated by the calling subsystem
                                      And the calling sub system will set the length 
                                      accordingly. */
} TMEDigestMessageResponse;

/*!
 * @struct TMEDigestMessage
 * @brief Digest message's structure.
 */

typedef struct PACKED_PREFIX tme_digest_message_s
{
    TMEDigestMessageRequest  input;  /*!< Digest message's request */
    TMEDigestMessageResponse output; /*!< Digest message's response */
} TMEDigestMessage;
// clang-format on
#endif /* TME_CRYPTO_DIGEST_INTERFACE_H */
