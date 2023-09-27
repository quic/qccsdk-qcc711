/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_firmware_update.h"

// TME utility headers
#include "tme_ipc_utils.h"
#include "tme_ipc_nvm_utils.h"

// TMECOM headers
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Verifies the update package.

   The verification status is provided as output for the update package.

   @param[in,out] VerifyUpdatePackageParams  Verify update package parameters.
   @param[in]     FwupCB                     Callback function, only used in non-blocking mode.
                                             NULL for blocking mode.
   @param[in]     UserParam                  User parameter, returned as-is in callback.

   @return 
           - QAPI_OK if blocking operation completed successfully or a non-blocking call was
             successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter VerifyUpdatePackageParams should be in heap or a static
              buffer for non-blocking read.
*/
qapi_Status_t qapi_FWUP_Verify_Update_Package(qapi_FWUP_Verify_Update_Package_t *VerifyUpdatePackageParams,
                                              qapi_FWUP_Operation_CB_t           FwupCB,
                                              void                              *UserParam)
{
   qapi_Status_t returnStatus  = qapi_Perform_Operation(TME_MSG_UID_FWUP_VERIFY_UPDATE,
                                                        TME_MSG_UID_FWUP_VERIFY_UPDATE_PARAM_ID,
                                                        VerifyUpdatePackageParams,
                                                        (void *)FwupCB,
                                                        UserParam);

   // Revoke TME Access of NVM Blocks in case of failure. In case of success or callback
   // the access will be revoked after QAPI is processed.
   if(returnStatus != QAPI_OK && returnStatus != QAPI_ERR_BUSY)
   {
     Revoke_TME_Access_Of_NVM();
   }

   return returnStatus;
}

/**
   @brief Applies the firmware update.

   This operation verifies the firmware update package and applies it. If the operation is successful,
   it triggers an SoC reset and does not return.

   All the software component images must be decrypted and placed in NVM before calling this API.
   If LockDebug is set TRUE, then APSS processor debugging capability will be locked.

   @param[in,out] ApplyUpdateParams  Apply update parameters.

   @return A negative value if there was an error.

   \attention All the software component images must exist on NVM in plaintext before applying update.

*/
qapi_Status_t qapi_FWUP_Apply_Update_Package(qapi_FWUP_Apply_Update_Package_t *ApplyUpdateParams)
{
   qapi_Status_t returnStatus  =  qapi_Perform_Operation(TME_MSG_UID_FWUP_APPLY_UPDATE,
                                                         TME_MSG_UID_FWUP_APPLY_UPDATE_PARAM_ID,
                                                         ApplyUpdateParams,
                                                         NULL, 
                                                         NULL);

   // Revoke TME Access of NVM Blocks in case of failure. In case of success or callback
   // the access will be revoked after QAPI is processed.
   if(returnStatus != QAPI_OK && returnStatus != QAPI_ERR_BUSY)
   {
     Revoke_TME_Access_Of_NVM();
   }

   return returnStatus;
}
