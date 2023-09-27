/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"
#include "TmecomClient.h"
#include "tme_ipc_callback_utils.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
/* Timeout (in microseconds) TMECOM should wait for response from TME */
extern uint32_t gIpcWaitTimeout;

/* Maximum timeout in microseconds. */
#define TMECOM_IPC_WAIT_TIMEOUT (2 * 1000 * 1000)

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Start a session with RoT subsystem.

   Put a vote on RoT subsystem and make sure RoT is awake to service requests.
   Establish a channel with RoT.
   This API should be called before sending any service request to RoT SS.

   @return 
           - QAPI_OK if channel was established with RoT SS successfully.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

  @attention This API should be called only once during a session, QAPI will
             return a QAPI_ERR_XXX error if channel is already established with RoT.
             Any number of service requests can be sent to RoT during a RoT
             session i.e. after calling this and before calling qapi_ROT_Session_End.

*/
qapi_Status_t qapi_ROT_Session_Start(void)
{
    gIpcWaitTimeout = TMECOM_IPC_WAIT_TIMEOUT;
    qapi_Status_t return_value = ((TMECOM_RSP_SUCCESS == TmecomClientSessionStart()) ?
             QAPI_OK : QAPI_ERROR);
    // If RoT Session was created successfully and TME Call back is not
    // initialised then initialise it
    if((!is_tme_callback_initialized) && (return_value == QAPI_OK))
    {
      // Initialize the callback
      return_value = Initialize_TME_Callback();
      if(return_value != QAPI_OK)
      {
        TmecomClientSessionEnd();
      }
    }
    return return_value;
}

/**
   @brief End session with RoT subsystem

   Close channel with RoT SS, remove a vote on RoT SS. RoT can enter into low
   power mode post this.
   This API should be called after all service messages are completed.

   @return 
           - QAPI_OK if channel with RoT was closed successfully.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

  @attention This API should be called only once during a session, QAPI will
             return a QAPI_ERR_XXX error if there was no open channel with RoT.
*/
qapi_Status_t qapi_ROT_Session_End(void)
{
    qapi_Status_t return_value = ((TMECOM_RSP_SUCCESS == TmecomClientSessionEnd()) ?
             QAPI_OK : QAPI_ERROR);
    // If RoT Session was closed successfully then de-initialise callback
    if(return_value == QAPI_OK)
    {
      // Deinitialze the callback
      Deinitialize_TME_Callback();
    }
    return return_value;
}
