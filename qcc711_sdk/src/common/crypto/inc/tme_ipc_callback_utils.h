/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_ipc_callback_utils.h
 * @brief The utility structures, functions and enums related to TME IPC Callback
 */
#ifndef TME_IPC_CALLBACK_UTILS_H
#define TME_IPC_CALLBACK_UTILS_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"

/** Variable for specifying whether TME Callback has been initialised or not */
static qbool_t is_tme_callback_initialized;

/** Enumeration of Event data type. */
typedef enum
{
   CRYPTO_EVENT_DATA = 1,  /**< qapi_CRPT_Operation_Event_Data_t.      */
   CRYPTO_EX_EVENT_DATA,   /**< qapi_CRPT_EX_Operation_Event_Data_t.   */
   TOKEN_EVENT_DATA,       /**< qapi_CRPT_TOKN_Operation_Event_Data_t. */
   FIRMWARE_EVENT_DATA,    /**< qapi_FWUP_Operation_Event_Data_t.      */
   ROT_EVENT_DATA,         /**< qapi_ROT_Operation_Event_Data_t        */
   LIC_EVENT_DATA,         /**< qapi_LIC_Operation_Event_Data_t        */
   FUSE_EVENT_DATA,        /**< qapi_FUSE_Operation_Event_Data_t       */
} TMW_Event_Data_Type_t;

/**
   @brief: Initializes the callback module.

   The function creates the task which will parse the context and execute
   the stored callback

   @return the status result of the callback initialization.
*/
qapi_Status_t Initialize_TME_Callback(void);

/**
   @brief: Process a callback function with the provided information.

   Primarily it will add the callback to the context so that it can be executed by the task.

   @param Status        Status returned by QAPI
   @param EventDataType Type of Event data
   @param EventData     Event Data of QAPI.
   @param UserParam     Parameter provided by user
   @param CallBack      The call back function

   @return QAPI_OK if the callback was processed successfully or error if there was an error.
*/
qapi_Status_t Process_TME_Callback(qapi_Status_t Status, TMW_Event_Data_Type_t EventDataType,
                                           void *EventData, void *UserParam, void *CallBack);

/**
   @brief: De-Initializes the callback module.

   The function marks the task TO BE DELETED so that scheduler can remove it. 
*/
void Deinitialize_TME_Callback(void);

/**
   @brief: Function to determine whether a callback is pending or not.

   @return true if pending or false otherwise
*/
qbool_t Is_Callback_Pending(void);

// clang-format on
#endif /* TME_IPC_CALLBACK_UTILS_H */
