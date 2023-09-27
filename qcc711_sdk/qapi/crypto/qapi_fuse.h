/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_fuse.h
   @brief Fuse (OTP & MTP) related APIs and definitions.

   This module provides OTP & MTP related APIs and definitions.
*/

#ifndef __QAPI_FUSE_H__
#define __QAPI_FUSE_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_fuse
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/* TODO: Add error code defs for #QAPI_MOD_FUSE. */


typedef struct
{
  uint32_t  addr;   /**< Address of OTP/MTP to be written OR to read.
                         Address need to be 4 Byte aligned. */
  uint32_t  val;    /**< Value to be written in the OTP/MTP for write request, for
                         read request val get populated with contents of OTP/MTP */
} qapi_Fuse_t;

/** Enumeration of Fuse operations. */
typedef enum
{
   QAPI_FUSE_WRITE_SECURE_FUSE_E  /**< Write data into fuses securely. */
} qapi_FUSE_Operation_t;

/** Structure representing the parameters required to write fuse securely. */
typedef struct qapi_Fuse_Write_Secure_Params_s
{
   uint8_t   *signedWriteSequence;    /**< Signed write command for Secure OTP write. */
   uint32_t   signedWriteSequenceLen; /**< Byte length of signedWriteSequence. */
} qapi_Fuse_Write_Secure_Params_t;

/** Structure representing the fuse event data as received in callback. */
typedef struct qapi_FUSE_Operation_Event_Data_s
{
  qapi_FUSE_Operation_t operation;  /**< Operation type */
  union {
    qapi_Fuse_Write_Secure_Params_t fuseWriteSecureParams; /**< Fuse write secure parameters */
  } Data;      /**< Event data */
} qapi_Fuse_Operation_Event_Data_t;

/** 
   @brief Prototype for a function called after non-blocking fuse operation is complete.
   @param[in] status     Fuse operation result.
   @param[in] eventData  Event Data for fuse operation.
   @param[in] userParam  User-specified parameter provided when the callback is registered.
*/
typedef void (*qapi_Fuse_Operation_CB_t)(qapi_Status_t                     status, 
                                         qapi_Fuse_Operation_Event_Data_t *eventData, 
                                         void                             *userParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Read single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to read.
   @param [out]    fuseVal      Read data from OTP/MTP.

   @return
   QAPI_OK -- If the data read from fuse (OTP/MTP) successfully.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.
*/
qapi_Status_t qapi_Fuse_Read(uint32_t  fuseAddr,
                             uint32_t  *fuseVal);

/**
   @brief  Reads multiple OTP/MTP presented by an array of [addr, val]

   @param [in,out] fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
   QAPI_OK -- If the blocking operation completed successfully, and all fuse
              reads successful, or a non-blocking call was successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
qapi_Status_t qapi_Fuse_Read_Multiple(qapi_Fuse_t              *fuseArray,
                                      size_t                    fuseArraySz,
                                      qapi_Fuse_Operation_CB_t  fuseOpCB,
                                      void                     *userParam);

/**
   @brief Writes single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to write to.
   @param [in]     fuseVal      Data to write to OTP/MTP.

   @return
   QAPI_OK -- If the data was successfully written to Fuse (OTP/MTP).\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.
*/
qapi_Status_t qapi_Fuse_Write(uint32_t  fuseAddr,
                              uint32_t  fuseVal);

/**
   @brief  Writes multiple OTP/MTP presented by an array of [addr, val]

   @param [in]     fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
   QAPI_OK -- If the blocking operation completed successfully, and all fuse
              writes successful, or a non-blocking call was successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
*/
qapi_Status_t qapi_Fuse_Write_Multiple(qapi_Fuse_t              *fuseArray,
                                       size_t                    fuseArraySz,
                                       qapi_Fuse_Operation_CB_t  fuseOpCB,
                                       void                     *userParam);

/**
   @brief  Writes to the secure OTP.

   @param [in]     signedWriteSequence    Signed write command for Secure OTP write.
   @param [in]     signedWriteSequenceLen Byte length of signedWriteSequence.
   @param [in]     fuseOpCB               Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param [in]     userParam              User parameter, returned as-is in callback.
 
   @return
   QAPI_OK -- If blocking operation completed successfully, and secure fuse
              write successful, or a non-blocking call was successfully accepted.\n
   QAPI_ERR_BUSY -- Indicating non-blocking operation is ongoing.\n
   Error code -- Of the form QAPI_ERR_XXX defined in qapi_status.h.

   \attention The input parameter SecureFuseParams should be in heap or a static
              buffer. TME will access the buffer.

*/
qapi_Status_t qapi_Fuse_Write_Secure_Fuse(uint8_t                   *signedWriteSequence,
                                          uint32_t                   signedWriteSequenceLen,
                                          qapi_Fuse_Operation_CB_t   fuseOpCB,
                                          void                      *userParam);


/** @} */  /* end_addtogroup qapi_platform_fuse */

#endif

