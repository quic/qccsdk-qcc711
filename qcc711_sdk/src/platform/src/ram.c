/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"
#include "ram.h"
#include "HALhwio.h"
#include "hwio_ram.h"

/*
   Shared RAM master IDs are as follows:
    - 0: ROT
    - 1: APSS
    - 2: BTSS
    - 3: Debug
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static Variables
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Converts an address range to a bitmask of blocks.

   @param[in] Start         Start of the address range to check.
   @param[in] End           End of the address range to check.

   @return Bitmask of blocks covered by the provided address range.
*/
uint32_t RAM_AddressRangeToBlocks(const void *Start, const void *End)
{
   uint32_t    RetVal;
   const void *StartAddr;
   const void *EndAddr;
   uint32_t    StartBit;
   uint32_t    EndBit;
   uint32_t    StartMask;
   uint32_t    EndMask;

   StartAddr = Start;
   EndAddr   = End;

   /* Verify the address range covers only valid RAM addresses. */
   if((StartAddr <= EndAddr) && (StartAddr >= RAM_START) && (EndAddr <= RAM_END))
   {
      /* Determine the bitmask for the RAM blocks. */
      StartBit  = ((uintptr_t)StartAddr - (uintptr_t)RAM_START) / RAM_BLOCK_SIZE;
      EndBit    = ((uintptr_t)EndAddr - (uintptr_t)RAM_START) / RAM_BLOCK_SIZE;
      EndMask   = (1 << (EndBit + 1)) - 1;
      StartMask = (1 << StartBit) - 1;
      RetVal    = (~StartMask & EndMask);

      if(RetVal & RAM_BTSS_BLOCK_7_BITMASK)
      {
         if(StartAddr < RAM_BTSS_BLOCK_7_SUBBLOCK_0_START)
         {
            StartAddr = RAM_BTSS_BLOCK_7_SUBBLOCK_0_START;
         }

         if(EndAddr > RAM_BTSS_BLOCK_7_SUBBLOCK_7_END)
         {
            EndAddr = RAM_BTSS_BLOCK_7_SUBBLOCK_7_END;
         }

         /* Determine the bitmask for the BTSS subblocks. */
         StartBit   = ((uintptr_t)StartAddr - (uintptr_t)RAM_BTSS_BLOCK_7_SUBBLOCK_0_START) / RAM_SUBBLOCK_SIZE;
         EndBit     = ((uintptr_t)EndAddr - (uintptr_t)RAM_BTSS_BLOCK_7_SUBBLOCK_0_START) / RAM_SUBBLOCK_SIZE;
         EndMask    = (1 << (EndBit + 1)) - 1;
         StartMask  = (1 << StartBit) - 1;
         RetVal     = (~StartMask & EndMask) << 16;
         RetVal    &= ~RAM_BTSS_BLOCK_7_BITMASK;
      }

      /* Check if the subdividable APSS RAM block can be split into
         subblocks. */
      if(RetVal & RAM_APSS_BLOCK_7_BITMASK)
      {
         StartAddr = Start;
         if(StartAddr < RAM_APSS_BLOCK_7_SUBBLOCK_0_START)
         {
            StartAddr = RAM_APSS_BLOCK_7_SUBBLOCK_0_START;
         }

         EndAddr = End;
         if(EndAddr > RAM_APSS_BLOCK_7_SUBBLOCK_7_END)
         {
            EndAddr = RAM_APSS_BLOCK_7_SUBBLOCK_7_END;
         }

         /* Determine the bitmask for the APSS subblocks. */
         StartBit   = ((uintptr_t)StartAddr - (uintptr_t)RAM_APSS_BLOCK_7_SUBBLOCK_0_START) / RAM_SUBBLOCK_SIZE;
         EndBit     = ((uintptr_t)EndAddr - (uintptr_t)RAM_APSS_BLOCK_7_SUBBLOCK_0_START) / RAM_SUBBLOCK_SIZE;
         EndMask    = (1 << (EndBit + 1)) - 1;
         StartMask  = (1 << StartBit) - 1;
         RetVal     = (~StartMask & EndMask) << 24;
         RetVal    &= ~RAM_APSS_BLOCK_7_BITMASK;
      }
   }
   else
   {
      RetVal = 0;
   }

   return RetVal;
}


/**
   @brief Provides the owner for a region of RAM or NVM.

   @param[in] Address  Address to read the owner of.

   @return Subsystem that owns the specified address or RAM_SUBYSTEM_UNKNOWN_E
           if the owner could not be determined.
*/
RAM_Subsystem_t RAM_GetOwner(const void *Address)
{
   uint32_t        Block;
   RAM_Subsystem_t RetVal;

   if((Address >= RAM_START) && (Address <= RAM_END))
   {
      Block   = ((uintptr_t)Address - (uintptr_t)RAM_START) / RAM_BLOCK_SIZE;

      if(HWIO_SRM_REGION_OWNER_MASTER_1_INM(Block))
      {
         RetVal = RAM_SUBSYSTEM_APSS_E;
      }
      else if(HWIO_SRM_REGION_OWNER_MASTER_2_INM(Block))
      {
         RetVal = RAM_SUBSYSTEM_BTSS_E;
      }
      else if(HWIO_SRM_REGION_OWNER_MASTER_3_INM(Block))
      {
         RetVal = RAM_SUBSYSTEM_UNKNOWN_E;
      }
      else
      {
         RetVal = RAM_SUBSYSTEM_ROT_E;
      }
   }
   else
   {
      RetVal = RAM_SUBSYSTEM_UNKNOWN_E;
   }

   return(RetVal);
}

/**
   @brief Shares RAM address blocks with another subsystem.

   Sharing is done in blocks and this API will affect all blocks covered by the
   provided address range.

   @param[in] Subsystem   Subsystem the memory is shared with.
   @param[in] BlockMask   Bitmask of blocks to share.
   @param[in] Permission  Permissions the subsystem will have to the shared
                          memory.

   @return QAPI_OK if the RAM was shared correctly or a negative value if
           there was an error.
*/
qapi_Status_t RAM_Share(RAM_Subsystem_t Subsystem, uint32_t BlockMask, RAM_Permission_t Permission)
{
   qapi_Status_t RetVal;
   uint32_t      RegAddr;
   uint32_t      RegShift;
   qbool_t       Read;
   qbool_t       Write;
   uint32_t      RegVal;
   uint32_t      RegMask;

   RetVal = QAPI_OK;

   /* Get the specifics for the subsystem. */
   switch(Subsystem)
   {
      case RAM_SUBSYSTEM_ROT_E:
         RegAddr  = HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR;
         RegShift = HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_0_SHFT;
         break;

      case RAM_SUBSYSTEM_BTSS_E:
         RegAddr  = HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR;
         RegShift = HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_2_SHFT;
         break;

      default:
         RegAddr  = 0;
         RegShift = 0;
         RetVal   = QAPI_ERR_INVALID_PARAM;
         break;
   }

   /* Parse the permission level. */
   switch(Permission)
   {
      case RAM_PERM_NO_ACCESS_E:
         Read  = false;
         Write = false;
         break;

      case RAM_PERM_READ_ONLY_E:
         Read  = true;
         Write = false;
         break;

      case RAM_PERM_READ_WRITE_E:
         Read  = true;
         Write = true;
         break;

      default:
         Read   = false;
         Write  = false;
         RetVal = QAPI_ERR_INVALID_PARAM;
         break;
   }

   /* Verify the parameters. */
   if((RetVal == QAPI_OK) && ((BlockMask & (RAM_APSS_BLOCKS_BITMASK | RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK)) != 0))
   {
      /* If the subdividable block was set, set all the subblocks instead. */
      if(BlockMask & RAM_APSS_BLOCK_7_BITMASK)
      {
         BlockMask |= RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK;
         BlockMask &= ~RAM_APSS_BLOCK_7_BITMASK;
      }

      /* Make sure only valid blocks were specified. */
      if((BlockMask & ~(RAM_APSS_BLOCKS_BITMASK | RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK)) == 0)
      {
         /* Share the RAM blocks. */
         RegMask = BlockMask & RAM_APSS_BLOCKS_BITMASK;
         if(RegMask != 0)
         {
            RegVal  = (Read ? (RegMask << HWIO_SRM_REGION_OWNER_1_SHARE_0_SHAREABLE_SHFT) : 0) | (Write ? (RegMask << HWIO_SRM_REGION_OWNER_1_SHARE_0_WRITABLE_SHFT) : 0);
            RegMask = ((RegMask << HWIO_SRM_REGION_OWNER_1_SHARE_0_SHAREABLE_SHFT) | (RegMask << HWIO_SRM_REGION_OWNER_1_SHARE_0_WRITABLE_SHFT));
            out_dword_masked_ns(RegAddr, RegMask, RegVal, in_dword(RegAddr));
         }

         /* Share the RAM subblocks. */
         RegMask = (BlockMask & RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK) >> (24 - RegShift);
         if(RegMask != 0)
         {
            HWIO_SRM_OWNER_1_SUB_SHARE_OUTM(RegMask, Read ? RegMask : 0);
            HWIO_SRM_OWNER_1_SUB_WRITE_OUTM(RegMask, Write ? RegMask : 0);
         }

         RetVal = QAPI_OK;
      }
      else
      {
         RetVal = QAPI_ERR_BOUNDS;
      }
   }

   return(RetVal);
}

