/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_patch_version_interface.h
 * @brief IPC related interface for patch version. Defines
 *        structures for the following update requests
 *        <br>Get patch version
 */
 
#ifndef TME_PATCH_VERSION_INTERFACE_H
#define TME_PATCH_VERSION_INTERFACE_H

#include "packed.h"
#include "tme_types.h"

/***********************************************************
 *  Get patch version Request/Response Structure Definitions
 ***********************************************************/

/*!
 * @struct TMEGetPatchVersionMessageResponse
 * @brief Output structure of get patch version message.
 */

typedef struct PACKED_PREFIX tme_get_patch_version_message_response_s
{
    TMEStatus          status;   /*!< Status of the response. */
    TMEResponseCBuffer response; /*!< Response buffer to be filled by TME with the 
                                      patch version. Memory for the containing buffer
                                      is to be allocated by the calling subsystem
                                      And the calling sub system will set the length 
                                      accordingly. */
                            
} TMEGetPatchVersionMessageResponse;

/*!
 * @struct TMEGetPatchVersionMessage
 * @brief Structure of get patch version message.
 */

typedef struct PACKED_PREFIX tme_get_patch_version_message_s
{
    TMEGetPatchVersionMessageResponse output; /*!< Get patch version message's response */
} TMEGetPatchVersionMessage;
// clang-format on
#endif /* TME_PATCH_VERSION_INTERFACE_H */
