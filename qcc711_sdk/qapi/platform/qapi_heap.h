/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_heap.h
   @brief Task scheduler interface definition.

   This module provides standard malloc and free APIs for both general RAM and
   retention RAM.

*/

#ifndef __QAPI_HEAP_H__
#define __QAPI_HEAP_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_heap
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Structure representing the available heap statistics. */
typedef struct qapi_HeapStatistics_s
{
   uint32_t HeapSize;            /**< Total size of the heap. */
   uint32_t CurrentHeapUsed;     /**< Amount of the heap that is currently in use. */
   uint32_t MaximumHeapUsed;     /**< Maximum amount of the heap that has been used at one time. */
   uint32_t AllocatedBlockCount; /**< Number of allocated blocks in the heap. */
   uint32_t FreeBlockCount;      /**< Number of unallocated blocks in the heap. */
   uint32_t LargestFreeBlock;    /**< Size of the largest unallocated block. */
} qapi_Heap_Statistics_t;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the main heap.

   @return
   QAPI_OK -- If the heap was initialized successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_Initialize_Heap(void);

/**
   @brief Initializes the retained heap.

   This function is typically called by the qapi_power module on cold boot.

   @return
   QAPI_OK -- If the heap was initialized successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_Initialize_Retain_Heap(void);

/**
   @brief Allocates a block of memory from the heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return
   A pointer to the allocated memory, or NULL if there was an error.
*/
void *qapi_Malloc(size_t Size);

/**
   @brief Allocates a block of memory from the retained heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return
   A pointer to the allocated memory, or NULL if there was an error.
*/
void *qapi_Malloc_Retain(size_t Size);

/**
   @brief Frees a block of memory from either heap.

   @param[in] Address  Pointer to the block that was returned by a call to
                       qapi_Malloc() or qapi_Malloc_Retain().
*/
void qapi_Free(void *Address);

/**
   @brief Gets the current statistics for the heaps.

   @param[out] MainHeapStats     Pointer to where the statistics for the main
                                 heap should be written.
   @param[out] RetainHeapStats   Pointer to where the statistics for the
                                 retained heap should be written.

   @return
   QAPI_OK -- If the statistics were queried successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_Get_Heap_Statistics(qapi_Heap_Statistics_t *MainHeapStats, qapi_Heap_Statistics_t *RetainHeapStats);

/** @} */ /* end_addtogroup qapi_platform_heap */

#endif

