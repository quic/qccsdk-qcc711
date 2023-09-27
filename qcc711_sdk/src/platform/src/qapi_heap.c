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
#include "qapi_heap.h"
#include "qapi_task.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/

extern size_t __MainHeapStart; /**< Linker symbol for the start of the main heap. */
extern size_t __MainHeapEnd;   /**< Linker symbol for the end of the main heap. */
extern size_t __RetnHeapStart; /**< Linker symbol for the start of the retained heap. */
extern size_t __RetnHeapEnd;   /**< Linker symbol for the end of the retained heap. */

#define MAIN_HEAP_START                                                 ((void *)&__MainHeapStart)                                           /**< Start of the main heap. */
#define MAIN_HEAP_END                                                   ((void *)&__MainHeapEnd)                                             /**< End of the main heap. */
#define MAIN_HEAP_SIZE                                                  ((uint32_t)((uint8_t *)MAIN_HEAP_END - (uint8_t *)MAIN_HEAP_START)) /**< Size of the main heap. */
#define RETN_HEAP_START                                                 ((void *)&__RetnHeapStart)                                           /**< Start of the retained heap. */
#define RETN_HEAP_END                                                   ((void *)&__RetnHeapEnd)                                             /**< End of the retained heap. */
#define RETN_HEAP_SIZE                                                  ((uint32_t)((uint8_t *)RETN_HEAP_END - (uint8_t *)RETN_HEAP_START)) /**< Size of the retained heap. */

/** Type that is used for memory alignment. */
typedef uint32_t Alignment_t;

#define ALIGNMENT_SIZE                                                  (sizeof(Alignment_t)) /**< Size of the heap alignment. */

/**
   Converts a size in bytes to size in units of ALIGNMENT_SIZE, rounding up.

   @param[in] _size_   Size in bytes.

   @return Size in units of ALIGNMENT_SIZE.
*/
#define BYTES_TO_ALIGNMENT_SIZE(_size_)                                 (((_size_) + sizeof(Alignment_t) - 1) / sizeof(Alignment_t))

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Header for a memory block. */
typedef struct _tagBlockHeader_t
{
   uint16_t    PrevSize; /**< Size of the previous block in terms of sizeof(Alignment_t). */
   uint16_t    Size;     /**< Size of the previous block in terms of sizeof(Alignment_t). The upper bit of
                              this field indicates if the field is allocated. */
   Alignment_t Data[1];  /**< Data for the block. */
} BlockHeader_t;

#define BLOCK_HEADER_SIZE                                               (BYTES_TO_ALIGNMENT_SIZE(sizeof(BlockHeader_t)) - 1) /**< Size of the block header in units of ALIGNMENT_SIZE. */

#define BLOCK_HEADER_SIZE_BITMASK                                       ((uint16_t)(((uint16_t)-1) >> 1))                    /**< Bitmask of the block size in the size field of the block header. */
#define BLOCK_HEADER_ALLOCATED_BITMASK                                  ((uint16_t)(~BLOCK_HEADER_SIZE_BITMASK))             /**< Bitmask of the allocated flag in the size field of the block header. */

#define MINIMUM_BLOCK_SIZE                                              (BLOCK_HEADER_SIZE + 1)                              /**< Minimum size of a block in units of ALIGNMENT_SIZE. */
#define MAXIMUM_BLOCK_SIZE                                              (BLOCK_HEADER_SIZE_BITMASK)                          /**< Maximum size of a block in units of ALIGNMENT_SIZE. */

/**
   Provides the previous block.

   @param[in] _block_   Current block.

   @return The block before the current block.
*/
#define PREV_BLOCK(_block_)                                             ((BlockHeader_t *)(((Alignment_t *)(_block_)) - ((_block_)->PrevSize)))

/**
   Provides the next block.

   @param[in] _block_   Current block.

   @return The block after the current block.
*/
#define NEXT_BLOCK(_block_)                                             ((BlockHeader_t *)(((Alignment_t *)(_block_)) + ((_block_)->Size & BLOCK_HEADER_SIZE_BITMASK)))

/** Header information for a heap. */
typedef struct _tagHeapHeader_t
{
   uint32_t       CurrentHeapUsed; /**< Current usage of the heap in units of ALIGNMENT_SIZE. Used for statistics
                                        gathering. */
   uint32_t       MaximumHeapUsed; /**< Maximum usage of the heap in units of ALIGNMENT_SIZE. Used for statistics
                                        gathering. */
   BlockHeader_t *HeapTail;        /**< Pointer to the tail of the heap.  This is the address immmididately
                                        following the last byte of the heap. */
   BlockHeader_t  HeapHead[1];     /**< Start of the heap data. */
} HeapHeader_t;

#define HEAP_HEADER_SIZE                                                (sizeof(HeapHeader_t) - sizeof(BlockHeader_t)) /**< Size of the heap header. */

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

/** Flag indicating the main heap has been initialized. */
static qbool_t MainHeapInitialized;

/** Flag indicating the retained heap has been initialized. */
static qbool_t RetainHeapInitialized __attribute__((section (".bss.retain")));

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static qapi_Status_t HeapInit(void *Heap, uint32_t Size);
static void *HeapAlloc(void *Heap, uint32_t Size);
static void HeapFree(void *Heap, void *Address);
static qapi_Status_t HeapGetStatistics(void *Heap, qapi_Heap_Statistics_t *Statistics);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes a heap.

   @param[in] Heap  Pointer to the memory region to use for the heap.
   @param[in] Size  Size of the memory region to use for the heap.

   @return QAPI_OK if the heap was initialized successfully or a negative value
           if there was an error.
*/
static qapi_Status_t HeapInit(void *Heap, uint32_t Size)
{
   qbool_t       RetVal;
   HeapHeader_t *HeapHeader;

   HeapHeader = (HeapHeader_t *)Heap;

   /* Verify the parameters, including the projected size of the heap. */
   if((HeapHeader != NULL) && (Size >= sizeof(HeapHeader_t)))
   {
      Size = (Size - HEAP_HEADER_SIZE) / ALIGNMENT_SIZE;

      /* Make sure the size of the heap is below the limit. */
      if(Size > MAXIMUM_BLOCK_SIZE)
      {
         Size = MAXIMUM_BLOCK_SIZE;
      }

      /* Verify the region is big enough for at least one allocation. */
      if(Size >= MINIMUM_BLOCK_SIZE)
      {
         /* Initialize the Heap information. */
         memset(HeapHeader, 0, sizeof(HeapHeader_t));
         HeapHeader->HeapHead->Size     = Size;
         HeapHeader->HeapHead->PrevSize = Size;
         HeapHeader->HeapTail           = NEXT_BLOCK(HeapHeader->HeapHead);

         RetVal = QAPI_OK;
      }
      else
      {
         RetVal = QAPI_ERROR;
      }
   }
   else
   {
      RetVal = QAPI_ERROR;
   }

   return(RetVal);
}

/**
   @brief Allocates a block of memory from the specified heap.

   @param[in] Heap  Pointer to the heap to allocate from.
   @param[in] Size  Minimum size of the memory block to allocate.

   @return A pointer to the allocated memory or NULL if there was an error.
*/
static void *HeapAlloc(void *Heap, uint32_t Size)
{
   void          *RetVal;
   HeapHeader_t  *HeapHeader;
   BlockHeader_t *BlockHeader;
   uint16_t       RemainingSize;

   HeapHeader = (HeapHeader_t *)Heap;

   /* Convert the size to units of ALIGNMENT_SIZE and add the size of the block
      header. */
   Size   = BLOCK_HEADER_SIZE + BYTES_TO_ALIGNMENT_SIZE(Size);
   RetVal = NULL;

   /* Make sure the allocation size is at least the minimum. */
   if(Size < MINIMUM_BLOCK_SIZE)
   {
      Size = MINIMUM_BLOCK_SIZE;
   }

   /* Verify that the parameters are valid. */
   if((HeapHeader != NULL) && (Size <= MAXIMUM_BLOCK_SIZE))
   {
      BlockHeader = HeapHeader->HeapHead;

      /* Walk the heap looking for an unallocated block of sufficient size. */
      while(BlockHeader < HeapHeader->HeapTail)
      {
         if((BlockHeader->Size & BLOCK_HEADER_ALLOCATED_BITMASK) || (BlockHeader->Size < Size))
         {
            /* Block is already allocated or too small. */
            BlockHeader = NEXT_BLOCK(BlockHeader);
         }
         else
         {
            /* Get the address of the start of the allocated memory. */
            RetVal = (void *)(BlockHeader->Data);

            /* Suitable block found. Check if the block needs to be split. */
            RemainingSize = BlockHeader->Size - Size;
            if(RemainingSize >= MINIMUM_BLOCK_SIZE)
            {
               /* Re-size the current block and set it as allocated. */
               BlockHeader->Size = Size | BLOCK_HEADER_ALLOCATED_BITMASK;

               /* Initialize the new block. */
               BlockHeader = NEXT_BLOCK(BlockHeader);
               BlockHeader->PrevSize = Size;
               BlockHeader->Size     = RemainingSize;

               /* Adjust the previous size of the next block. */
               BlockHeader = NEXT_BLOCK(BlockHeader);
               if(BlockHeader < HeapHeader->HeapTail)
               {
                  BlockHeader->PrevSize = RemainingSize;
               }
               else
               {
                  /* This is the last block so adjust the previous size of the
                     first block instead. */
                  HeapHeader->HeapHead->PrevSize = RemainingSize;
               }
            }
            else
            {
               /* Update the allocated size to the entire block and flag the
                  block as allocated. */
               Size = BlockHeader->Size;
               BlockHeader->Size |= BLOCK_HEADER_ALLOCATED_BITMASK;
            }

            /* Adjust the memory statistics. */
            HeapHeader->CurrentHeapUsed += Size;
            if(HeapHeader->MaximumHeapUsed < HeapHeader->CurrentHeapUsed)
            {
               HeapHeader->MaximumHeapUsed = HeapHeader->CurrentHeapUsed;
            }

            break;
         }
      }
   }

   return(RetVal);
}

/**
   @brief Frees a block of memory from the specified heap.

   @param[in] Heap     Pointer to the heap to free to.
   @param[in] Address  Pointer to the allocated block that was returned from
                       qapi_Malloc().
*/
static void HeapFree(void *Heap, void *Address)
{
   HeapHeader_t  *HeapHeader;
   BlockHeader_t *BlockHeader;
   BlockHeader_t *TempBlockHeader;

   HeapHeader = (HeapHeader_t *)Heap;

   /* Verify that the parameters passed in appear valid. */
   if((HeapHeader != NULL) && (Address != NULL) && (Address >= (void *)(HeapHeader->HeapHead->Data)) && (Address < (void *)(HeapHeader->HeapTail)))
   {
      /* Get a pointer to the block header. */
      BlockHeader = (BlockHeader_t *)(((Alignment_t *)Address) - BLOCK_HEADER_SIZE);

      /* Verify that this block is allocated. */
      if(BlockHeader->Size & BLOCK_HEADER_ALLOCATED_BITMASK)
      {
         /* Set the current block as un-allocated and update the heap
            statistics. */
         BlockHeader->Size &= ~BLOCK_HEADER_ALLOCATED_BITMASK;
         HeapHeader->CurrentHeapUsed -= BlockHeader->Size;

         /* Try to combine this block with the previous block. */
         if(BlockHeader != HeapHeader->HeapHead)
         {
            TempBlockHeader = PREV_BLOCK(BlockHeader);

            if(!(TempBlockHeader->Size & BLOCK_HEADER_ALLOCATED_BITMASK))
            {
               /* Combine this block with the newly freed block. */
               TempBlockHeader->Size += BlockHeader->Size;
               BlockHeader = TempBlockHeader;
            }
         }

         /* Try to combine this block with the following block. */
         TempBlockHeader = NEXT_BLOCK(BlockHeader);
         if(TempBlockHeader < HeapHeader->HeapTail)
         {
            if(!(TempBlockHeader->Size & BLOCK_HEADER_ALLOCATED_BITMASK))
            {
               BlockHeader->Size += TempBlockHeader->Size;
            }
         }

         /* Update the previous size of the next block. */
         TempBlockHeader = NEXT_BLOCK(BlockHeader);
         if(TempBlockHeader < HeapHeader->HeapTail)
         {
            TempBlockHeader->PrevSize = BlockHeader->Size;
         }
         else
         {
            /* This is the last block so adjust the previous size of the first
               block instead. */
            HeapHeader->HeapHead->PrevSize = BlockHeader->Size;
         }
      }
   }
}

/**
   @brief Gets the current statistics for the heaps.

   @param[in]  Heap        Pointer to the heap to get statistics for.
   @param[out] Statistics  Pointer to where the heap statistics should be
                           stored.
*/
static qapi_Status_t HeapGetStatistics(void *Heap, qapi_Heap_Statistics_t *Statistics)
{
   int            RetVal;
   HeapHeader_t  *HeapHeader;
   BlockHeader_t *BlockHeader;
   uint16_t       Size;

   HeapHeader = (HeapHeader_t *)Heap;

   /* Verify that the parameters that were passed in appear valid. */
   if((HeapHeader != NULL) && (Statistics != NULL))
   {
      memset(Statistics, 0, sizeof(qapi_Heap_Statistics_t));

      /* Assign the basic heap statistics. */
      Statistics->HeapSize = (uint32_t)(((uint8_t *)(HeapHeader->HeapTail)) - ((uint8_t *)(HeapHeader->HeapHead)));
      Statistics->CurrentHeapUsed = HeapHeader->CurrentHeapUsed * ALIGNMENT_SIZE;
      Statistics->MaximumHeapUsed = HeapHeader->MaximumHeapUsed * ALIGNMENT_SIZE;

      /* Walk the heap and count the number of free blocks.  */
      BlockHeader = HeapHeader->HeapHead;

      while(BlockHeader < HeapHeader->HeapTail)
      {
         if(BlockHeader->Size & BLOCK_HEADER_ALLOCATED_BITMASK)
         {
            Statistics->AllocatedBlockCount++;
         }
         else
         {
            Statistics->FreeBlockCount++;

            Size = BlockHeader->Size & BLOCK_HEADER_SIZE_BITMASK;
            if (Statistics->LargestFreeBlock < Size)
            {
               Statistics->LargestFreeBlock = Size;
            }
         }

         /* Adjust the pointer to the next entry. */
         BlockHeader = NEXT_BLOCK(BlockHeader);
      }

      /* Convert the size of the largest free block to bytes. */
      Statistics->LargestFreeBlock *= ALIGNMENT_SIZE;

      RetVal = QAPI_OK;
   }
   else
   {
      RetVal = QAPI_ERROR;
   }

   return(RetVal);
}

/**
   @brief Initializes the main heap.

   @return QAPI_OK if the heap was initialized successfully or a negative value
           if there was an error.
*/
qapi_Status_t qapi_Initialize_Heap(void)
{
   qapi_Status_t RetVal;

   if(!MainHeapInitialized)
   {
      RetVal = HeapInit(MAIN_HEAP_START, MAIN_HEAP_SIZE);

      MainHeapInitialized = (qbool_t)(RetVal == QAPI_OK);
   }
   else
   {
      RetVal = QAPI_ERR_EXISTS;
   }

   return(RetVal);
}

/**
   @brief Initializes the retained heap.

   @return QAPI_OK if the heap was initialized successfully or a negative value
           if there was an error.
*/
qapi_Status_t qapi_Initialize_Retain_Heap(void)
{
   qapi_Status_t RetVal;

   if(!RetainHeapInitialized)
   {
      RetVal = HeapInit(RETN_HEAP_START, RETN_HEAP_SIZE);

      RetainHeapInitialized = (qbool_t)(RetVal == QAPI_OK);
   }
   else
   {
      RetVal = QAPI_ERR_EXISTS;
   }

   return(RetVal);
}

/**
   @brief Allocates a block of memory from the heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return A pointer to the allocated memory or NULL if there was an error.
*/
void *qapi_Malloc(size_t Size)
{
   void *RetVal;

   if(MainHeapInitialized)
   {
      qapi_TSK_Enter_Critical();
      RetVal = HeapAlloc(MAIN_HEAP_START, Size);
      qapi_TSK_Exit_Critical();
   }
   else
   {
      RetVal = NULL;
   }

   return(RetVal);
}

/**
   @brief Allocates a block of memory from the retained heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return A pointer to the allocated memory or NULL if there was an error.
*/
void *qapi_Malloc_Retain(size_t Size)
{
   void *RetVal;

   if(RetainHeapInitialized)
   {
      qapi_TSK_Enter_Critical();
      RetVal = HeapAlloc(RETN_HEAP_START, Size);
      qapi_TSK_Exit_Critical();
   }
   else
   {
      RetVal = NULL;
   }

   return(RetVal);
}

/**
   @brief Frees a block of memory from either heap.

   @param[in] Address  Pointer to the block that was returned by a call to
                       qapi_Malloc() or qapi_Malloc_Retain().
*/
void qapi_Free(void *Address)
{
   if((Address >= MAIN_HEAP_START) && (Address <= MAIN_HEAP_END))
   {
      if(MainHeapInitialized)
      {
         HeapFree(MAIN_HEAP_START, Address);
      }
   }
   else
   {
      if(RetainHeapInitialized)
      {
         HeapFree(RETN_HEAP_START, Address);
      }
   }
}

/**
   @brief Gets the current statistics for the heaps.

   @param[out] MainHeapStats  Pointer to where the statistics for the main heap
                              should be written.
   @param[out] RetnHeapStats  Pointer to where the statistics for the retained
                              heap should be written.

   @return QAPI_OK if the statistics were queried successfully or a negative
           value if there was an error.
*/
qapi_Status_t qapi_Get_Heap_Statistics(qapi_Heap_Statistics_t *MainHeapStats, qapi_Heap_Statistics_t *RetnHeapStats)
{
   qapi_Status_t RetVal;

   if(MainHeapStats != NULL)
   {
      if(MainHeapInitialized)
      {
         RetVal = HeapGetStatistics(MAIN_HEAP_START, MainHeapStats);
      }
      else
      {
         RetVal = QAPI_ERR_NO_ENTRY;
      }
   }
   else
   {
      RetVal = QAPI_OK;
   }

   if((RetnHeapStats != NULL) && (RetVal == QAPI_OK))
   {
      if(RetainHeapInitialized)
      {
         RetVal = HeapGetStatistics(RETN_HEAP_START, RetnHeapStats);
      }
      else
      {
         RetVal = QAPI_ERR_NO_ENTRY;
      }
   }

   return(RetVal);
}


