/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_nvm_interface.h
 * @brief IPC related interfaces for nvm operation
 *        <br>NVM write
 *        <br>NVM read
 */
#ifndef TME_NVM_INTERFACE_H__
#define TME_NVM_INTERFACE_H__

#include "packed.h"
#include "tme_types.h"

/*************************************************************
 *  NVM write-ex Request/Response Structure Definitions
 *************************************************************/

/*!
 * @struct TMENVMWriteExMessageRequest
 * @brief Input structure of NVM write-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_write_ex_message_request_s
{
    UINT32     offset;  /*!< Offset from base address, to perform nvm
                             write operation.*/
    TMECBuffer input;   /*!< Input Buffer containing message to write to
                             NVM.The calling subsystem will allocate memory
                             and fill the buffer with the message along with
                             setting the length */
} TMENVMWriteExMessageRequest;

/*!
 * @struct TMENVMWriteExMessageResponse
 * @brief Output structure of NVM write-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_write_ex_message_response_s
{
    TMEStatus  status; /*!< Status of NVM write-ex operation. */
} TMENVMWriteExMessageResponse;

/*!
 * @struct TMENVMWriteExMessage
 * @brief Structure of NVM write-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_write_ex_message_s
{
    TMENVMWriteExMessageRequest  input;  /*!< NVM write-ex
                                              message's request */
    TMENVMWriteExMessageResponse output; /*!< NVM write-ex
                                              message's response */
} TMENVMWriteExMessage;

/*************************************************************
 *  NVM read-ex Request/Response Structure Definitions
 *************************************************************/

/*!
 * @struct TMENVMReadExMessageRequest
 * @brief Input structure of NVM read-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_read_ex_message_request_s
{
    UINT32      offset; /*!< Offset from base address, to perform nvm
                             read operation. */
} TMENVMReadExMessageRequest;

/*!
 * @struct TMENVMReadExMessageResponse
 * @brief Output structure of NVM read-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_read_ex_message_response_s
{
    TMEResponseCBuffer output;  /*!< Output buffer to save value read from offset.
                                     The calling subsystem will allocate memory
                                     and fill the buffer with the message along with
                                     setting the length */
    TMEStatus  status;          /*!< Status of NVM read-ex operation. */
} TMENVMReadExMessageResponse;

/*!
 * @struct TMENVMReadExMessage
 * @brief Structure of NVM read-ex message.
 */

typedef struct PACKED_PREFIX tme_nvm_read_ex_message_s
{
    TMENVMReadExMessageRequest  input;  /*!< NVM read-ex
                                             message's request */
    TMENVMReadExMessageResponse output; /*!< NVM read-ex
                                             message's response */
} TMENVMReadExMessage;

// clang-format on
#endif /* TME_NVM_INTERFACE_H__ */