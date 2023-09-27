/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
*  @file qapi_rot.h
*  @brief RoT session management API definitions.
*/
/** @addtogroup qapi_platform_rot
    These APIs provide high level interfaces for RoT session management.
    qapi_ROT_Session_Start must be called before requesting any service to RoT
    and qapi_ROT_Session_End must be called once all requests are finished.
*/

#ifndef __QAPI_ROT_H__
#define __QAPI_ROT_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_platform_rot
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/** Maximum size for RoT patch version in bytes. */
#define QAPI_ROT_PATCH_VERSION_LEN       ((uint32_t)(10))

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
/** Enumeration of RoT patch version operations. */
typedef enum
{
   QAPI_ROT_GET_PATCH_VERSION_E  /**< Retrieve RoT patch version. */
} qapi_ROT_Operation_t;

/** Structure representing the parameters required to get RoT patch version. */
typedef struct qapi_ROT_Get_Patch_Version_Params_s
{
   uint32_t  PatchVersionLen;     /**< Length of patch version buffer.Should be
                                       at least #QAPI_ROT_PATCH_VERSION_LEN.*/
   uint8_t  *PatchVersion;        /**< Buffer allocated by the application for
                                       placing output RoT patch version. */
   uint32_t  PatchVersionLenUsed; /**< PatchVersion buffer length used in bytes. */
} qapi_ROT_Get_Patch_Version_Params_t;

/** 
   Structure representing the event data as received in callback.
 */
typedef struct qapi_ROT_Operation_Event_Data_s
{
  qapi_ROT_Operation_t Operation;  /**< Operation type */
  union {
    qapi_ROT_Get_Patch_Version_Params_t *GetPatchVersionParams; /**< Get patch version params */
  } Data;      /**< Event data */
} qapi_ROT_Operation_Event_Data_t;

/** 
   @brief Prototype for a function called after non-blocking get patch version operation is complete.
   @param[in] Status     Operation result.
   @param[in] EventData  Event Data for get patch version operation.
   @param[in] UserParam  User specified parameter provided when the callback is registered.
*/
typedef void (*qapi_ROT_Operation_CB_t)(qapi_Status_t                    Status, 
                                        qapi_ROT_Operation_Event_Data_t *EventData, 
                                        void                            *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Start a session with RoT subsystem.

   Put a vote on RoT SS and make sure RoT subsystem is awake to service requests.
   Establish a channel with RoT SS.

   @return
   QAPI_OK -- If channel was established with RoT successfully.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention This API should be called before sending any service request to RoT SS.
              API should be called only once during a session, QAPI will return a
              QAPI_ERR_XXX error if channel was already established with RoT.
              Any number of service requests can be sent to RoT during a RoT session
              i.e. after calling this and before calling qapi_ROT_Session_End.
*/
qapi_Status_t qapi_ROT_Session_Start(void);

/**
   @brief End a session with RoT subsystem.

   Close channel with RoT, remove a vote on RoT. RoT can enter into low
   power mode post this.

   @return
   QAPI_OK -- If channel with RoT was closed successfully.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention This API should be called after all service messages are completed.
              API should be called only once during a session, QAPI will return a
              QAPI_ERR_XXX error if there was no open channel with RoT.
*/
qapi_Status_t qapi_ROT_Session_End(void);

/**
   @brief Get RoT patch version.
   
   qapi_ROT_Session_Start() must be called before using API.

   @param[in,out] GetPatchVersionParams  Get patch version operation parameters.
   @param[in]     Callback               Callback function, only used in non-blocking
                                         mode. NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return
   QAPI_OK -- If blocking operation completed successfully, or a non-blocking call was successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating non-blocking operation was ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter GetPatchVersionParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_ROT_Get_Patch_Version(qapi_ROT_Get_Patch_Version_Params_t   *GetPatchVersionParams,
                                         qapi_ROT_Operation_CB_t                Callback,
                                         void                                  *UserParam);


/** @} */ /* end_addtogroup qapi_platform_rot */

#endif /* __QAPI_ROT_H__ */
