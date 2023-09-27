/*=============================================================================

                    Fuse Interface Source File


   Copyright (c) 2021 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Qualcomm Technologies, Inc. Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "qapi_status.h"
#include "qapi_types.h"
#include "qapi_fuse.h"
#include "TmeFuseClient.h"
#include "TmeErrorCodes.h"
#include "tme_ipc_callback_utils.h"

/*=============================================================================

                     PUBLIC FUNCTION DEFINITION

=============================================================================*/
/**
   @brief Read single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to read.
   @param [out]    fuseVal      Read data from OTP/MTP.

   @return
           - QAPI_OK if the data read from fuse (OTP/MTP) successful.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.
*/
qapi_Status_t qapi_Fuse_Read(uint32_t  fuseAddr,
                             uint32_t  *fuseVal)
{
  TME_ERROR ret = TmeFuseRead(fuseAddr, fuseVal);

  if (ret != TME_SUCCESS) {
    return QAPI_ERROR;
  }
  return QAPI_OK;
}

/**
   @brief  Reads multiple OTP/MTP presented by an array of [addr, val]

   @param [in,out] fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - QAPI_OK if blocking operation completed successfully and all fuse read successful
             or a non-blocking call was successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
qapi_Status_t qapi_Fuse_Read_Multiple(qapi_Fuse_t               *fuseArray,
                                      size_t                    fuseArraySz,
                                      qapi_Fuse_Operation_CB_t  fuseOpCB,
                                      void                      *userParam)
{
  TME_ERROR ret = TmeFuseReadMultiple((TmeFuse_t*)fuseArray,
                                      fuseArraySz,
                                      (TmeFuseOperationCB_t)fuseOpCB,
                                      userParam);

  if (TME_ERROR_TME_BUSY == ret) {
    return QAPI_ERR_BUSY;
  } else if (ret != TME_SUCCESS) {
    return QAPI_ERROR;
  }

  return QAPI_OK;
}

/**
   @brief Writes single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to write to.
   @param [in]     fuseVal      Data to write to OTP/MTP.

   @return
           - QAPI_OK if the data was successfully written to Fuse (OTP/MTP).
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.
*/
qapi_Status_t qapi_Fuse_Write(uint32_t  fuseAddr,
                              uint32_t  fuseVal)
{
  TME_ERROR ret = TmeFuseWrite(fuseAddr, fuseVal);

  if (ret != TME_SUCCESS) {
    return QAPI_ERROR;
  }
  return QAPI_OK;
}

/**
   @brief  Writes multiple OTP/MTP presented by an array of [addr, val]

   @param [in]     fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - QAPI_OK if blocking operation completed successfully and all fuse writes successful
             or a non-blocking call was successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
qapi_Status_t qapi_Fuse_Write_Multiple(qapi_Fuse_t               *fuseArray,
                                       size_t                    fuseArraySz,
                                       qapi_Fuse_Operation_CB_t  fuseOpCB,
                                       void                      *userParam)
{
  TME_ERROR ret = TmeFuseWriteMultiple((TmeFuse_t*)fuseArray,
                                       fuseArraySz,
                                       (TmeFuseOperationCB_t)fuseOpCB,
                                       userParam);

  if (TME_ERROR_TME_BUSY == ret) {
    return QAPI_ERR_BUSY;
  } else if (ret != TME_SUCCESS) {
    return QAPI_ERROR;
  }

  return QAPI_OK;
}

/**
   @brief  Writes to the secure OTP.

   @param [in]     signedWriteSequence    Signed write command for Secure OTP write.
   @param [in]     signedWriteSequenceLen Byte length of signedWriteSequence.
   @param [in]     fuseOpCB               Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param [in]     userParam              User parameter, returned as-is in callback.
 
   @return
           - QAPI_OK if blocking operation completed successfully and secure fuse write successful
             or a non-blocking call was successfully accepted.
           - QAPI_ERR_BUSY indicating non-blocking operation was ongoing.
           - Any error code of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter SecureFuseParams should be in heap or a static
              buffer. TME will access the buffer.

*/
qapi_Status_t qapi_Fuse_Write_Secure_Fuse(uint8_t                   *signedWriteSequence,
                                          uint32_t                   signedWriteSequenceLen,
                                          qapi_Fuse_Operation_CB_t   fuseOpCB,
                                          void                      *userParam)
{
  if(NULL != fuseOpCB)
  {
    /* For non-blocking mode, check if execution of any user callback is pending */
    if(Is_Callback_Pending())
    {
      return QAPI_ERR_BUSY;
    }
  }

  TME_ERROR ret = TmeFuseWriteSecureFuse(signedWriteSequence,
                                         signedWriteSequenceLen,
                                         (TmeFuseOperationCB_t)fuseOpCB,
                                         userParam);

  if (TME_ERROR_TME_BUSY == ret) {
    return QAPI_ERR_BUSY;
  } else if (ret != TME_SUCCESS) {
    return QAPI_ERROR;
  }

  return QAPI_OK;
}
