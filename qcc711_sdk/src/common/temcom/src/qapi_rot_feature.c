/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

// Common qapi headers
#include "qapi_types.h"

// crypto headers
#include "qapi_rot.h"

// TME utility headers
#include "tme_ipc_utils.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Get RoT patch version.
   
   qapi_ROT_Session_Start() must be called before using API.

   @param[in,out] GetPatchVersionParams  Get patch version operation parameters.
   @param[in]     Callback               Callback function, only used in non-blocking mode.
                                         NULL for blocking mode.
   @param[in]     UserParam              User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter GetPatchVersionParams should be in heap or a static
              buffer for non-blocking read. @newpage
*/
qapi_Status_t qapi_ROT_Get_Patch_Version(qapi_ROT_Get_Patch_Version_Params_t   *GetPatchVersionParams,
                                         qapi_ROT_Operation_CB_t                Callback,
                                         void                                  *UserParam)
{
   return qapi_Perform_Operation(TME_MSG_UID_FEATURE_PATCH_VERSION,
                                 TME_MSG_UID_FEATURE_PATCH_VERSION_PARAM_ID,
                                 GetPatchVersionParams,
                                 (void *)Callback,
                                 UserParam);
}