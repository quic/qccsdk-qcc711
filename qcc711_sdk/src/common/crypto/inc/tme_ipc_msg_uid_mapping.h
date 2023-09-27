/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_ipc_msg_uid_mapping.h
 * @brief The utility structures, arrays and function related to TME IPC.                    
 */
#ifndef TME_IPC_MSG_UID_MAPPING_H
#define TME_IPC_MSG_UID_MAPPING_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "packed.h"
#include "qapi_status.h"
#include "qapi_types.h"

/*!
 * @brief Prototype for a function to validate qapi parameters and allocate IPC message. 
 *  @param[in] qapiParams      qapi parameters.
 *  @param[in] tmeIPCMsg       Address for allocation of TME IPC message.
 *  @param[in] tmeIPCMsgLength Address to hold the TME IPC message length.
 *
 *  @return QAPI_OK if operation completed successfully, or a corresponding error.
 */
typedef qapi_Status_t (*tme_validate_and_create_ipc_msg)(void *qapiParams, void **tmeIPCMsg, uint32_t *tmeIPCMsgLength);

/*!
 * @brief Prototype for a function to set qapi parameters from IPC message. 
 *  @param[in] qapiParams       qapi parameters.
 *  @param[in] tmeIPCMsg        Pointer to allocated TME IPC message
 *  @param[in] eventData        Pointer to event data, used in non-blocking call.
 *
 *  @return QAPI_OK if operation completed successfully, or a corresponding error.
 */
typedef qapi_Status_t (*tme_process_ipc_msg_response)(void *qapiParams, void *tmeIPCMsg, qapi_Status_t status  , void* callBack, void* userData);

/*!
 * @struct TMEIPCQapiMapping
 * @brief Structure containing message Id, validation function for request and response.
 */
typedef struct PACKED_PREFIX tme_ipc_qapi_mapping_s
{
    uint32_t                        messageId;               /*!< Message identifier. */
    tme_validate_and_create_ipc_msg validateAndCreateIPCMsg; /*!< Pointer to function for validation of 
                                                                  qapi parameters and create IPC
                                                                  message. */
    tme_process_ipc_msg_response   processIPCMsgResponse;  /*!<   Pointer to function for validation of 
                                                                  IPC message response. */

} TMEIPCQapiMapping;

/**
   @brief Get TME IPC mapping corresponding to the given 
          TmeMsgUid for APSS or BTSS exclusive qapi if found, 
          else return NULL
 
   @param[in] TMEMsgUid     TME message identifier.
  
   @return TMEIPCQapiMapping  Tme message mapping corresponding to
           TmeMsgUid will be returned if found, else NULL.
*/
TMEIPCQapiMapping *Get_IPC_QAPI_Mapping(uint32_t MapLength);

/**
   @brief Get TMEIPCQapiMapping corresponding to the given 
          TmeMsgUid, else return NULL
 
   @param[in] TMEMsgUid     TME message identifier.
  
   @return TMEIPCQapiMapping  Tme message mapping corresponding to
           TmeMsgUid will be returned if found, else NULL.
*/
TMEIPCQapiMapping* Get_TME_Message_Mapping(uint32_t TmeMsgUid);

// clang-format on
#endif /* TME_IPC_MSG_UID_MAPPING_H */
