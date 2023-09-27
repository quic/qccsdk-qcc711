/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_rng_interface.h
 * @brief IPC's RNG related interfaces for TME-FW Crypto Service. Defines
          structures for the following crypto requests
 *        <br>Get Random value
 */
#ifndef TME_CRYPTO_RNG_INTERFACE_H
#define TME_CRYPTO_RNG_INTERFACE_H

#include "packed.h"
#include "tme_types.h"

/************************************************
 *  PRNG Request/Response Structure Definitions
 ***********************************************/

/*!
 * @struct TMEGetRandomMessageRequest
 * @brief Input structure of generate random number message.
 */

typedef struct PACKED_PREFIX tme_get_random_message_request_s
{
    UINT32 length; /*!< Requisite length of generated random number. The maximum
                        allowed length is 64.*/
} TMEGetRandomMessageRequest;

/*!
 * @struct TMEGetRandomMessageResponse
 * @brief Output structure of generate random number message.
 */

typedef struct PACKED_PREFIX tme_get_random_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the 
                                      generated random number.Memory for the 
                                      containing buffer is to be allocated by the calling
                                      subsystem. And the calling sub system will set the
                                      length accordingly.*/
} TMEGetRandomMessageResponse;

/*!
 * @struct TMEGetRandomMessage
 * @brief Structure of generate random number message.
 */

typedef struct PACKED_PREFIX tme_get_random_message_s
{
    TMEGetRandomMessageRequest  input;  /*!< Generate random number message's 
                                             request */
    TMEGetRandomMessageResponse output; /*!< Generate random number message's 
                                             response */
} TMEGetRandomMessage;
// clang-format on
#endif /* TME_CRYPTO_RNG_INTERFACE_H */
