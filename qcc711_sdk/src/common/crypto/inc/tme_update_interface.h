/*
 * Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_update_interface.h
 * @brief IPC related interfaces for update services. Defines
 *        structures for the following update requests
 *        <br>Verify firmware update
 *        <br>Apply firmware udpate
 */
#ifndef TME_UPDATE_INTERFACE_H
#define TME_UPDATE_INTERFACE_H

#include "packed.h"
#include "tme_types.h"

/*!
 * @enum TMEUpdateVerificationStatus
 * @brief Indicates the firmware update verification status returned by the TME-FW.
 */

typedef enum tme_update_verification_status_e
{
    TME_VERIFICATION_SUCCESS,                         /*!< Success */
    TME_VERIFICATION_FAILURE,                         /*!< Verification Failure */
    TME_VERIFICATION_INVALID_INPUT,                   /*!< Invalid Input */
    TME_VERIFICATION_IMAGE_OVERLAP,                   /*!< Image overlaps */
    TME_VERIFCIATIONS_STATUS_UNKNOWN = 0xFFFFFFFF     /*!< Unknown */
} TMEUpdateVerificationStatus;

/*******************************************************
 *  Verify update Request/Response Structure Definitions
 *******************************************************/

/*!
 * @struct TMEVerifyUpdateMessageRequest
 * @brief Input structure of verify update message.
 */

typedef struct PACKED_PREFIX tme_verify_update_message_request_s
{
    UINT32 address;    /*!< Address of update image on NVM */
    UINT32 size;       /*!< Image size on NVM in bytes */
    UINT32 verifyAll;  /*!< Non-zero if all the images i.e. both updated and non-updated need to
                            be verified irrespective of auth fuses values. Otherwise set 0 for 
                            verification to be done based on auth fuses. */
} TMEVerifyUpdateMessageRequest;

/*!
 * @struct TMEVerifyUpdateMessageResponse
 * @brief Output structure of verify update message. The verification status will contain
 *        information about verification being success or not.
 */

typedef struct PACKED_PREFIX tme_verify_udpate_message_response_s
{
    TMEStatus                    status;             /*!< Status of the response. Set to 
                                                          TME_STATUS_INVALID_INPUT for invalid input,
                                                          TME_STATUS_SUCCESS for successful invocation
                                                          of PBL verification function. */
    TMEUpdateVerificationStatus  verificationStatus; /*!< Respone verification status be filled by 
                                                          TME. */
} TMEVerifyUpdateMessageResponse;

/*!
 * @struct TMEVerifyUpdateMessage
 * @brief Structure of verify update message.
 */

typedef struct PACKED_PREFIX tme_verify_update_message_s
{
    TMEVerifyUpdateMessageRequest  input;  /*!< Verify update message's request */
    TMEVerifyUpdateMessageResponse output; /*!< Verify update message's response */
} TMEVerifyUpdateMessage;

/*******************************************************
 *  Apply update Request/Response Structure Definitions
 *******************************************************/

/*!
 * @struct TMEApplyUpdateMessageRequest
 * @brief Input structure of apply update message.
 */
typedef struct PACKED_PREFIX tme_apply_udpate_message_request_s
{
    UINT32  address; /*!< Address of update image on NVM */
    UINT32  size;    /*!< Image size on NVM in bytes */
    UINT32  debug;   /*!< If set to non-zero, then OEM M3 debugging capability will be locked. */
} TMEApplyUpdateMessageRequest;

/*!
 * @struct TMEApplyUpdateMessageResponse
 * @brief Output structure of apply update message.
 */

typedef struct PACKED_PREFIX tme_apply_update_message_response_s
{
    TMEStatus  status; /*!< Status of the response. Only set in case of IPC failure.
                            TME_STATUS_INVALID_INPUT for invalid input, 
                            TME_STATUS_FAILURE in case of PBL2 update API invocation fails. */
} TMEApplyUpdateMessageResponse;

/*!
 * @struct TMEApplyUpdateMessage
 * @brief Structure of apply update message.
 */

typedef struct PACKED_PREFIX tme_apply_update_message_s
{
    TMEApplyUpdateMessageRequest  input;  /*!< Apply update message's request */
    TMEApplyUpdateMessageResponse output; /*!< Apply update message's response */
} TMEApplyUpdateMessage;
// clang-format on
#endif /* TME_UPDATE_INTERFACE_H */
