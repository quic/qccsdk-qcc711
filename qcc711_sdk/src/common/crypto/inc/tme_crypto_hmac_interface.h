/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_crypto_hmac_interface.h
 * @brief IPC's HMAC related interfaces for TME-FW Crypto Service. Defines
          structures for the following crypto requests
 *        <br>Get HMAC
 */
#ifndef TME_CRYPTO_HMAC_INTERFACE_H
#define TME_CRYPTO_HMAC_INTERFACE_H

#include "packed.h"
#include "tme_types.h"
#include "tme_crypto_params.h"

/**********************************************
 *  HMAC Request/Response Structure Definitions
 **********************************************/

/*!
 * @struct TMEHMACMessageRequest
 * @brief Input structure of HMAC message.
 */

typedef struct PACKED_PREFIX tme_hmac_message_request_s
{
    TMEDigestAlgo algo;       /*!< Algorithm to be used for calculating MAC  */
    TMECBuffer    input;      /*!< Input Buffer containing message whose MAC 
                                   is required.The calling subsystem will
                                   allocate memory and fill the buffer with 
                                   the message along with setting the length */
    TMECBuffer    initialMac; /*!< The MAC returned by the previous invocation
                                   in a sequence,otherwise empty.*/
    TMEKeyHandle  keyHandle;  /*!< Key Handle of the key present in TME to be 
                                   used for calculating HMAC */
} TMEHMACMessageRequest;

/*!
 * @struct TMEHMACMessageResponse
 * @brief Output structure of HMAC message.
 */

typedef struct PACKED_PREFIX tme_hmac_message_response_s
{
    TMEStatus          status;   /*!< Status of the response */
    TMEResponseCBuffer response; /*!< Respone buffer to be filled by TME with the 
                                      calculated MAC. Memory for the containing buffer
                                      is to be allocated by the calling subsystem. And
                                      the calling sub system will set the length 
                                      accordingly. */
} TMEHMACMessageResponse;

/*!
 * @struct TMEHMACMessage
 * @brief Structure of HMAC message.
 */

typedef struct PACKED_PREFIX tme_hmac_message_s
{
    TMEHMACMessageRequest  input;  /*!< HMAC message's request */
    TMEHMACMessageResponse output; /*!< HMAC message's response */
} TMEHMACMessage;
// clang-format on
#endif /* TME_CRYPTO_HMAC_INTERFACE_H */
