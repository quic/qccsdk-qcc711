/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_nvm_rot.h
    @brief NVM related APIs and definitions.

   This module provides mechanisms to perform operations on the NVM shared by the RoT
   subsystem.
   Make sure that the #qapi_ROT_Session_Start() API is called before using these APIs.

   If the APSS has acquired NVM access, then access must be released to
   perform read/write operations in shared NVM.
*/

#ifndef __QAPI_NVM_ROT_H__
#define __QAPI_NVM_ROT_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_nvm_rot
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/* Definition for NVM size available for the APSS to perform write/read operation. */
#define QAPI_NVM_ROT_SIZE    (0x3000) /**< Size of shared NVM available to the APSS. */

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief  Writes the provided buffer to the specified offset in NVM (RRAM)
   allocated to the RoT.
   
   Valid offset range is from 0 to (#QAPI_NVM_ROT_SIZE-1).

   Writes to NVM will block NVM reads, therefore this function blocks until the NVM
   write has completed.

   The caller should be aware that writing to RRAM can block other cores
   (namely the BTSS) and very long writes may affect performance.

   @param[in] Offset   Offset at which data to write.
   @param[in] Buffer   Data to write to NVM.
   @param[in] Length   Length of the data to write to NVM.

   @return
   QAPI_OK -- If the data was successfully written to NVM.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Write_ROT(uint32_t Offset, const void *Buffer, uint32_t Length);

/**
   @brief Reads NVM (RRAM) data from the specified offset to the provided buffer.
   Valid offset range is from 0 to (#QAPI_NVM_ROT_SIZE-1).
   
   @param[in] Offset   Offset from data to read.
   @param[in] Buffer   Buffer to save read NVM data.
   @param[in] Length   Length of the data to read from NVM.

   @return
   QAPI_OK -- If the data was successfully written to NVM.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Read_ROT(uint32_t Offset, void *Buffer, uint32_t Length);

/** @} */ /* end_addtogroup qapi_platform_nvm_rot */

#endif //__QAPI_NVM_ROT_H__