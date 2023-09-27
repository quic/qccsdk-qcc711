/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================

                    Platform Specific Fuse Config Source File

=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "qapi_nvm.h"
#include "qapi_fuse.h"
#include "qapi_heap.h"
#include "qapi_status.h"
#include "TmeFuseClient.h"
#include "TmeErrorCodes.h"
#include "TmeFusePlatformApis.h"
#include "tme_ipc_callback_utils.h"

/*----------------------------------------------------------------------------*
 *                   Pre-Defined MACROS                                       *
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 *                   Type Declarations                                        *
 *---------------------------------------------------------------------------*/

/*=============================================================================
                     STATIC FUNCTION DEFINITION
=============================================================================*/

/*=============================================================================
                     PUBLIC FUNCTION DEFINITION
=============================================================================*/
/**
   @brief Get access type for an operation on OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address.
   @param [in ]    opType       Operation type from TmeFuseOpType_t.

   @return
           - Access type allowed for the fuse operation.
*/
TmeFuseOpAccessType_t TmeFuseGetAccessType(uint32_t fuseAddr,
                                           TmeFuseOpType_t opType)
{
  TmeFuseOpAccessType_t access = TME_FUSE_OP_DISALLOWED;

  if (TME_FUSE_OP_READ == opType) {
    if (isOtp(fuseAddr) || isBtssMtp(fuseAddr)) {
      access = TME_FUSE_OP_VIA_IPC;
    } else if (isApssRoMtp(fuseAddr) || isApssRwMtp(fuseAddr)) {
      access = TME_FUSE_OP_DIRECTLY;
    }
  } else if (TME_FUSE_OP_WRITE == opType) {
    if (isOtp(fuseAddr) || isBtssMtp(fuseAddr)) {
      access = TME_FUSE_OP_VIA_IPC;
    } else if (isApssRwMtp(fuseAddr)) {
      access = TME_FUSE_OP_DIRECTLY;
    }
  }
  return access;
}

/**
   @brief Wrapper api for NVM Operation - request write.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmRequestWrite(void)
{
  if (QAPI_OK == qapi_NVM_Request_Write()){
    return TME_SUCCESS;
  }
  return TME_ERROR_GENERIC;
}

/**
   @brief Wrapper api for NVM Operation - release write.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmReleaseWrite(void)
{
  if (QAPI_OK == qapi_NVM_Release_Write()){
    return TME_SUCCESS;
  }
  return TME_ERROR_GENERIC;
}

/**
   @brief Wrapper api for NVM Operation - write.

   @param[in] addr   NVM address to write to.
   @param[in] buf    Data to write to NVM.
   @param[in] len    Length of the data to write to NVM.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmWrite(const void *addr, const void *buf, uint32_t len)
{
  if (QAPI_OK == qapi_NVM_Write(addr, buf, len)){
    return TME_SUCCESS;
  }
  return TME_ERROR_GENERIC;
}

/**
   @brief Fuse IPC call back handler. Based on OS environment call user call back
          to notify about completion of fuse operation.

   @param[in] fuseCbData   Fuse Call back Data.
   @param[in] status       Return value of fuse operation.

   @return - None.
*/
void TmeFuseOsHandleCallBack(TmeFuseCallBackData_t *fuseCbData, qapi_Status_t status)
{
  qapi_Fuse_Operation_Event_Data_t *eventData   = NULL;

  if(fuseCbData && fuseCbData->cbApi)
  {
      /* Allocate memory for eventData, will be freed inside Execute_TME_Callback() API */
      eventData = qapi_Malloc(sizeof(qapi_Fuse_Operation_Event_Data_t));
      if (NULL == eventData)
      {
          goto exit;
      }

      *eventData = fuseCbData->eventData;

      /* Enqueue callback in TME task(created during RoTSessionStart) queue and signal the task */
      Process_TME_Callback(status, FUSE_EVENT_DATA, eventData, fuseCbData->cbUserData, fuseCbData->cbApi);
  }

exit:
  return;
}
