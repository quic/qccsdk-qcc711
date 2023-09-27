/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_m2mdma.h
   @brief Memory-to-memory DMA channel operation
   
*/
/** @addtogroup qapi_peripherals_m2mdma

   A memory-to-memory (M2M) operation is made using a DMA channel.
   
   Typical usage:
   qapi_M2MDMA_Chan_Open()  - Open a DMA channel for an M2M operation.
   qapi_M2MDMA_Copy()       - Generic transfer API to perform a transfer
                              on the DMA channel.
   qapi_M2MDMA_Chan_Close() - Destroy all objects for a specified DMA channel.

   M2M DMA transfers:
   M2M DMA transfers support blocking and nonblocking modes. For nonblocking
   mode, buffers passed by the client must be resident and can
   only be freed when a client specified callback is invoked. For this
   operation, the destination should be an SRAM address. The source can
   be an SRAM address, or an RRAM address. There is no address alignment
   requirement, but the copy length should be a multiple of 4 bytes.
   If one DMA engine is dedicated for the qapi_M2MDMA_Copy() function,
   after the DMA engine is open it can be kept open, and an application
   can use qapi_M2MDMA_Copy() without the need to call open again.
*/

#ifndef __QAPI_M2MDMA_H__
#define __QAPI_M2MDMA_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_m2mdma
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
  @brief M2M DMA copy operation callback function type.

  For nonblocking DMA copy operations, this callback function is
  registered in the DMA copy QAPI. The callback is called in a driver task
  scheduler context after the copy operation is done.

  @param[in] Status       The operation return status.
  @param[in] CallbackCtxt The client object passed by the application.
*/
typedef void (*qapi_M2MDMA_CB_t) (uint32_t Status, void *CallbackCtxt);

/**
  @brief DMA engine channel enumeration for the M2M DMA copy.

  This enumeration lists the possible DMA engine channel, indicating the
  hardware engine instance used for M2M DMA operation.
*/
typedef enum
{
    QAPI_M2MDMA_CHAN_SE2_E = 2,         /**< DMA hardware controller instance ID 2. */
    QAPI_M2MDMA_CHAN_SE3_E              /**< DMA hardware controller instance ID 3. */
} qapi_M2MDMA_Chan_t;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the M2M DMA channel.

   This function initializes internal data structures and associated
   static data. In any operating mode, call this function before
   any other DMA channel API.

   @param[in] Chan       DMA channel specified by #qapi_M2MDMA_Chan_t.
   @param[in] Callback   Callback function if in nonblocking mode. For
                         blocking mode, this should be set to NULL.

   @return
   QAPI_OK --  Module was initialized successfully.\n
   QAPI_ERR_INVALID_PARAM --  Invalid channel or handle parameter.\n
   QAPI_ERR_NO_MEMORY --  Could not allocate space for driver structures.
*/
qapi_Status_t qapi_M2MDMA_Chan_Open(qapi_M2MDMA_Chan_t Chan, qapi_M2MDMA_CB_t Callback);

/**
   @brief Performs a data copy over the DMA channel.

   This function performs transfer over the DMA channel.
   If the callback is set, it is invoked on transfer
   completion.

   @param[in]  Chan          The channel opened by qapi_M2MDMA_Chan_Open().
   @param[out] Dst           Pointer to the destination address.
   @param[in]  Src           Pointer to the source address.
   @param[in]  Length        The length of DMA buffer copy. The length
                             should be a multiple of 4 bytes.
   @param[in]  UserParam     User specific data passed by the application.

   @return
   QAPI_OK -- M2M DMA copy successful.\n
   QAPI_ERROR -- DMA copy failed.\n
   QAPI_ERR_INVALID_PARAM -- One or more parameters invalid.\n
   QAPI_ERR_TRANSFER_BUSY -- The DMA channel is busy.\n
   QAPI_ERR_TRANSFER_TIMEOUT -- Copy timed out.
*/
qapi_Status_t qapi_M2MDMA_Copy(qapi_M2MDMA_Chan_t Chan, void *Dst, const void *Src, size_t Length, void* UserParam);

/**
   @brief Closes the M2M DMA channel.

   This function frees all internal data structures and closes the M2M DMA
   channel. The handle returned by qapi_M2MDMA_Chan_Open() is rendered
   invalid. Any pending operation is canceled by using the close function call.

   @param[in] Chan  The channel opened by qapi_M2MDMA_Chan_Open().

   @return
   QAPI_OK -- M2M DMA driver was closed successfully.\n
   QAPI_ERR_INVALID_PARAM -- Invalid channel parameter.
*/
qapi_Status_t qapi_M2MDMA_Chan_Close(qapi_M2MDMA_Chan_t Chan);

/** @} */ /* end_addtogroup qapi_peripherals_m2mdma */

#endif
