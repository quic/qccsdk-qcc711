/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file TmeFuseClient.h
   @brief Fuse (OTP & MTP) related APIs and definitions.

   This module provides OTP & MTP related APIs and definitions.
*/

#ifndef __TME_FUSE_CLIENT_H__
#define __TME_FUSE_CLIENT_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>

#include "qapi_fuse.h"
#include "TmeErrorCodes.h"

/** @addtogroup tme_fuse_interfaces
@{
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

typedef struct
{
  uint32_t  addr;   /**< Address of OTP/MTP to be written OR to read.
                         Address need to be 4 Byte aligned. */
  uint32_t  val;    /**< Value to be written in the OTP/MTP for write request, for
                         read request val get populated with contents of OTP/MTP */
} TmeFuse_t;

/** 
   @brief Prototype for a function called after non-blocking fuse operation is complete.
   @param[in] status     Fuse operation result.
   @param[in] userParam  User specified parameter provided when the callback is registered.
*/
typedef void (*TmeFuseOperationCB_t)(TME_ERROR status, void *userParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Read single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to read.
   @param [out]    fuseVal      Read data from OTP/MTP.

   @return
           - TME_SUCCESS if the data read from fuse (OTP/MTP) successful.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.
*/
TME_ERROR TmeFuseRead(uint32_t  fuseAddr,
                      uint32_t  *fuseVal);

/**
   @brief  Reads multiple OTP/MTP presented by an array of [addr, val]

   @param [in,out] fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and all fuse read successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
TME_ERROR TmeFuseReadMultiple(TmeFuse_t             *fuseArray,
                              size_t                fuseArraySz,
                              TmeFuseOperationCB_t  fuseOpCB,
                              void                  *userParam);

/**
   @brief Writes single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to write to.
   @param [in]     fuseVal      Data to write to OTP/MTP.

   @return
           - TME_SUCCESS if the data was successfully written to Fuse (OTP/MTP).
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.
*/
TME_ERROR TmeFuseWrite(uint32_t  fuseAddr,
                       uint32_t  fuseVal);

/**
   @brief  Writes multiple OTP/MTP presented by an array of [addr, val]

   @param [in]     fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and all fuse writes successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
TME_ERROR TmeFuseWriteMultiple(TmeFuse_t             *fuseArray,
                               size_t                fuseArraySz,
                               TmeFuseOperationCB_t  fuseOpCB,
                               void                  *userParam);

/**
   @brief  Writes to the secure OTP.

   @param [in]     signedWriteSequence    Signed write command for Secure OTP write.
   @param [in]     signedWriteSequenceLen Byte length of signedWriteSequence.
   @param [in]     fuseOpCB               Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param [in]     userParam              User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and secure fuse write successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter SecureFuseParams should be in heap or a static
              buffer. TME will access the buffer.
*/
TME_ERROR TmeFuseWriteSecureFuse(uint8_t               *signedWriteSequence,
                                 uint32_t               signedWriteSequenceLen,
                                 TmeFuseOperationCB_t   fuseOpCB,
                                 void                  *userParam);

/** @} */

#endif

