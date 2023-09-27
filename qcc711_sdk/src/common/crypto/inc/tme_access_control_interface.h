/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_access_control_interface.h
 * @brief IPC related interfaces for access control
 *        <br>NVM register access
 */
#ifndef TME_ACCESS_CONTROL_INTERFACE_H
#define TME_ACCESS_CONTROL_INTERFACE_H

#include "packed.h"
#include "tme_types.h"

/*************************************************************
 *  NVM register access Request/Response Structure Definitions
 *************************************************************/

/*!
 * @struct TMENVMRegisterAccessMessageRequest
 * @brief Input structure of NVM register access message.
 */

typedef struct PACKED_PREFIX tme_nvm_register_access_message_request_s
{
    UINT32 provideAccess; /*!< Set to non-zero to provide access for requesting
                               subsystem. Set to zero to release access for
                               requesting subsystem. */
} TMENVMRegisterAccessMessageRequest;

/*!
 * @struct TMENVMRegisterAccessMessageResponse
 * @brief Output structure of NVM register access message.
 */

typedef struct PACKED_PREFIX tme_nvm_register_access_message_response_s
{
    TMEStatus  status; /*!< Status of NVM register access operation. */
} TMENVMRegisterAccessMessageResponse;

/*!
 * @struct TMENVMRegisterAccessMessage
 * @brief Structure of NVM register access message.
 */

typedef struct PACKED_PREFIX tme_nvm_register_access_message_s
{
    TMENVMRegisterAccessMessageRequest  input;  /*!< NVM register access
                                                     message's request */
    TMENVMRegisterAccessMessageResponse output; /*!< NVM register access
                                                     message's response */
} TMENVMRegisterAccessMessage;

// clang-format on
#endif /* TME_ACCESS_CONTROL_INTERFACE_H */