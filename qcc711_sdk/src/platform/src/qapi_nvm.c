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
#include "qapi_nvm.h"
#include "hwio_nvm.h"

// TME IPC headers
#include "tme_ipc_utils.h"
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/

#define NVM_ACCESS_CONTROL_APSS_SHIFT                       (HWIO_ACCESS_0_RWX_0_SHFT)
#define NVM_ACCESS_CONTROL_BTSS_SHIFT                       (HWIO_ACCESS_0_RWX_1_SHFT)
#define NVM_ACCESS_CONTROL_ROT_SHIFT                        (HWIO_ACCESS_0_RWX_2_SHFT)

#define NVM_ACCESS_CONTROL_ENTRY_MASK                       (HWIO_ACCESS_0_ID_0_BMSK | HWIO_ACCESS_0_RWX_0_BMSK)
#define NVM_ACCESS_CONTROL_APSS_BITMASK                     (NVM_ACCESS_CONTROL_ENTRY_MASK << NVM_ACCESS_CONTROL_APSS_SHIFT)
#define NVM_ACCESS_CONTROL_BTSS_BITMASK                     (NVM_ACCESS_CONTROL_ENTRY_MASK << NVM_ACCESS_CONTROL_BTSS_SHIFT)
#define NVM_ACCESS_CONTROL_ROT_BITMASK                      (NVM_ACCESS_CONTROL_ENTRY_MASK << NVM_ACCESS_CONTROL_ROT_SHIFT)

#define NVM_QUEUE_DEPTH                                     (8)
#define NVM_QUEUE_SIZE_BYTES                                (sizeof(uint64_t) * NVM_QUEUE_DEPTH)

#define NVM_SECTOR_SIZE                                     (512 / sizeof(uint64_t))
#define NVM_SECTOR_ADDRESS_MASK                             (NVM_SECTOR_SIZE - 1)

#define HWIO_TABLE_CMD_IDLE                                 (0x00)
#define HWIO_TABLE_CMD_READ                                 (0x01)
#define HWIO_TABLE_CMD_LOAD                                 (0x02)
#define HWIO_TABLE_CMD_WRITE                                (0x03)
#define HWIO_TABLE_CMD_CLEAR_LOAD                           (0x04)

#define HWIO_SUBSYSTEM_ROT                                  (0)
#define HWIO_SUBSYSTEM_APSS                                 (1)
#define HWIO_SUBSYSTEM_BTSS                                 (2)

#define HWIO_ACCESS_CONTROL_ID_APSS                         (0)
#define HWIO_ACCESS_CONTROL_ID_ROT                          (1)
#define HWIO_ACCESS_CONTROL_ID_BTSS                         (2)

#define HWIO_ACCESS_IDLE                                    (0)
#define HWIO_ACCESS_WRITE                                   (1)
#define HWIO_ACCESS_READ                                    (2)

#define HWIO_ACCESS_CONTROL_EXECUTE_BITMASK                 (0x01)
#define HWIO_ACCESS_CONTROL_WRITE_BITMASK                   (0x02)
#define HWIO_ACCESS_CONTROL_READ_BITMASK                    (0x04)

#define NVM_MAIN_OFFSET                                     (0x10200000)
#define NVM_INFO_OFFSET                                     (0x50040800)

/**
   Reads an unaligned Little Endian 32-bit integer.

   @param[in] __addr__  Address of the integer to read.

   @return A 64-bit integer value.
*/
#define READ_UNALIGNED_LITTLE_ENDIAN_UINT32(__addr__)        \
   ((((uint32_t)(((const uint8_t *)(__addr__))[3])) << 24) | \
    (((uint32_t)(((const uint8_t *)(__addr__))[2])) << 16) | \
    (((uint32_t)(((const uint8_t *)(__addr__))[1])) << 8)  | \
     ((uint32_t)(((const uint8_t *)(__addr__))[0])))

typedef struct NVM_Context_s
{
   qbool_t WriteRequested;
} NVM_Context_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

NVM_Context_t NVM_Context;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static qbool_t NVM_VerifyAddress(const void *Address, uint32_t Length);
static qapi_Status_t NVM_WriteAligned(const uint64_t *Address, const uint8_t *Buffer, uint32_t Length);
static qapi_Status_t NVM_WriteUnaligned(const uint8_t *Address, const uint8_t *Buffer, uint32_t *Length);

/**
   @brief Verifies if the given NVM address range is valid for an NVM write
          operation.

   @param[in] Address  Start address for the NVM write operation.
   @param[in] Length   Number of bytes to be written.

   @return true if the address range is valid or false if it is not.
*/
static qbool_t NVM_VerifyAddress(const void *Address, uint32_t Length)
{
   qbool_t retVal;

   if (((uint32_t)Address >= (uint32_t)QAPI_NVM_APSS_START) &&
       ((uint32_t)Address <= (uint32_t)QAPI_NVM_APSS_END) &&
       ((((uint32_t)QAPI_NVM_APSS_END - (uint32_t)Address) + 1) >= Length))
   {
      /* Main NVM region. */
      retVal = true;
   }
   else if (((uint32_t)Address >= (uint32_t)QAPI_NVM_APSS_INFO_START) &&
            ((uint32_t)Address <= (uint32_t)QAPI_NVM_APSS_INFO_END) &&
            ((((uint32_t)QAPI_NVM_APSS_INFO_END - (uint32_t)Address) + 1) >= Length))
   {
      /* INFO block region.  */
      retVal = true;
   }
   else
   {
      /* Invalid address and/or length. */
      retVal = false;
   }

   return (retVal);
}

/**
   @brief Writes an aligned data buffer into NVM (RRAM).

   @param[in] Address  64-bit aligned address to write data to.
   @param[in] Buffer   64-bit aligned buffer of data to write.
   @param[in] Length   Number of 64-bit words to write.

   @return QAPI_OK if the write was successful or a negative value if there was
           an error.
*/
static qapi_Status_t NVM_WriteAligned(const uint64_t *Address, const uint8_t *Buffer, uint32_t Length)
{
   qapi_Status_t  RetVal;
   uint32_t       Index;
   uint32_t       DestAddr;

   /* Initialize for an NVM write operation. */
   if (((uint32_t)Address >= (uint32_t)QAPI_NVM_APSS_INFO_START) &&
            ((uint32_t)Address <= (uint32_t)QAPI_NVM_APSS_INFO_END))
   {
      /* Write to INFO region. */
      DestAddr = (uint32_t)Address - NVM_INFO_OFFSET;
      HWIO_INFO_BLOCK_OUT(1);
   }
   else
   {
      /* Write to main NVM. */
      DestAddr = (uint32_t)Address;
      HWIO_INFO_BLOCK_OUT(0);
   }

   /* Convert the address into what the LOAD_BUFFER register expects. */
   DestAddr = (DestAddr >> 3) & HWIO_LOAD_BUFFER_ADDRESS_ADDR_BMSK;

   /* Loop until all data is written or there is an error. */
   RetVal = QAPI_OK;
   while((RetVal == QAPI_OK) && (Length != 0))
   {
      /* Clear the write error and load table before proceeding. */
      HWIO_NVM_STATUS_ERROR_CLEAR_OUT(HWIO_NVM_STATUS_ERROR_CLEAR_RMSK);
      HWIO_TABLE_OUT(HWIO_TABLE_CMD_CLEAR_LOAD);
      while(!(HWIO_NVM_STATUS_INM(HWIO_NVM_STATUS_CMD_DONE_BMSK))) {}

      /* Loop until queue is filled, all data is queued, the end of the sector
         is reached or there is an error. */
      for(Index = 0; (Index < NVM_QUEUE_DEPTH) && (Length != 0) && (RetVal == QAPI_OK); Index ++)
      {
         /* Load the data and address. */
         HWIO_LOAD_BUFFER_LSB_OUT(READ_UNALIGNED_LITTLE_ENDIAN_UINT32(Buffer));
         Buffer += sizeof(uint32_t);
         HWIO_LOAD_BUFFER_MSB_OUT(READ_UNALIGNED_LITTLE_ENDIAN_UINT32(Buffer));
         Buffer += sizeof(uint32_t);
         HWIO_LOAD_BUFFER_ADDRESS_OUT(DestAddr);

         /* Issue the load command and wait for it to complete. */
         HWIO_TABLE_OUT(HWIO_TABLE_CMD_LOAD);
         while(!(HWIO_NVM_STATUS_INM(HWIO_NVM_STATUS_CMD_DONE_BMSK))) {}

         /* Check if there is an access control error. */
         if(!HWIO_NVM_STATUS_ERROR_IN)
         {
            DestAddr++;
            Length--;
         }
         else
         {
            RetVal = QAPI_NVM_ACCESS_CONTROL_ERROR;
         }

         /* Break out early if the end of the sector has been reached. */
         if((DestAddr & NVM_SECTOR_ADDRESS_MASK) == 0)
         {
            break;
         }
      }

      if(RetVal == QAPI_OK)
      {
         /* Issue the write command and wait for it to complete. */
         HWIO_TABLE_OUT(HWIO_TABLE_CMD_WRITE);
         while(!HWIO_NVM_STATUS_INM(HWIO_NVM_STATUS_CMD_DONE_BMSK)) {}

         /* Check status of the write operation. */
         if(HWIO_NVM_STATUS_ERROR_INM(HWIO_NVM_STATUS_ERROR_WRITE_ERROR_BMSK))
         {
            RetVal = QAPI_NVM_WRITE_FAILURE;
         }
      }
   }

   HWIO_INFO_BLOCK_OUT(0);

   return RetVal;
}

/**
   @brief Write the next block of data to NVM, accounting for the address not
          being aligned to an 8-byte block or the amount of data remaining
          being less than a full block.

   This function will also update the provided pointers and lengths
   accordingly.

   @param[in]     Address  NVM address to write to.
   @param[in]     Buffer   Data to write to NVM.
   @param[in,out] Length   As an input, this is the maximum amount of data to
                           write.  As an output, this is the actual amount of
                           data written.

   @return QAPI_OK if the write was successful or a negative value if there was
           an error.
*/
static qapi_Status_t NVM_WriteUnaligned(const uint8_t *Address, const uint8_t *Buffer, uint32_t *Length)
{
   qapi_Status_t RetVal;
   uint8_t       Offset;
   uint32_t      BytesWritten;

   union
   {
      uint64_t ULL;
      uint8_t  Bytes[sizeof(uint64_t)];
   } DataToWrite;

   /* Determine the offset for data to start in the 8-byte block and align the
      address. */
   Offset   = (uint32_t)Address & 0x7;
   Address -= Offset;

   /* Read the current data from NVM. */
   DataToWrite.ULL = *(const uint64_t *)Address;

   /* Overwrite the NVM data with the data from the buffer, starting at the
      offset determined above and going until it reaches the end of the 8-byte
      block or all data was consumed. */
   BytesWritten = 0;
   while((Offset < sizeof(uint64_t)) && (*Length != 0))
   {
      DataToWrite.Bytes[Offset] = *Buffer;

      Buffer++;
      Offset++;
      BytesWritten++;
      (*Length)--;
   }

   /* Go ahead and update the length to the number of bytes that will be
      written. */
   *Length = BytesWritten;

   /* Write the data. */
   RetVal = NVM_WriteAligned((const uint64_t *)Address, DataToWrite.Bytes, 1);

   return(RetVal);
}

/**
   @brief Converts an address range to a bitmask of blocks.

   @param[in] Start Start of the address range to check.
   @param[in] End   End of the address range to check.

   @return Bitmask of blocks covered by the provided address range.
*/
uint16_t qapi_NVM_Address_Range_To_Blocks(const void *Start, const void *End)
{
   uint16_t RetVal;
   uint32_t StartBit;
   uint32_t EndBit;
   uint16_t StartMask;
   uint16_t EndMask;

   if(Start < QAPI_NVM_APSS_START)
   {
      Start = QAPI_NVM_APSS_START;
   }

   if(End > QAPI_NVM_APSS_END)
   {
      End = QAPI_NVM_APSS_END;
   }

   /* Determine the bitmask for the RAM blocks. */
   if(End >= Start)
   {
      StartBit  = ((uint32_t)Start - (uint32_t)NVM_MAIN_OFFSET) / QAPI_NVM_BLOCK_SIZE;
      EndBit    = ((uint32_t)End   - (uint32_t)NVM_MAIN_OFFSET) / QAPI_NVM_BLOCK_SIZE;
      StartMask = (1 << StartBit) - 1;
      EndMask   = (1 << (EndBit + 1)) - 1;
      RetVal    = ~StartMask & EndMask;
   }
   else
   {
      RetVal = 0;
   }

   return(RetVal);
}

/**
   @brief Sets the permissions for a section of NVM.

   @param[in] BlockMask    Bitmask of blocks to set permissions on.
   @param[in] Permissions  Permissions to set.

   @return Bitmask of blocks whose permissions were set.
*/
uint16_t qapi_NVM_Set_Permissions(uint16_t BlockMask, qapi_NVM_Permissions_t Permissions)
{
   uint16_t           RetVal;
   uint32_t           Index;
   uint32_t           RegValue;
   volatile uint32_t *AccessReg;

   /* Parse the parameters. */
   switch(Permissions)
   {
      case QAPI_NVM_PERMISSIONS_READ_ONLY_E:
         RegValue = HWIO_ACCESS_CONTROL_READ_BITMASK;
         break;

      case QAPI_NVM_PERMISSIONS_READ_WRITE_E:
         RegValue = HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_WRITE_BITMASK;
         break;

      case QAPI_NVM_PERMISSIONS_READ_EXECUTE_E:
         RegValue = HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_EXECUTE_BITMASK;
         break;

      case QAPI_NVM_PERMISSIONS_READ_WRITE_EXECUTE_E:
         RegValue = HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_WRITE_BITMASK | HWIO_ACCESS_CONTROL_EXECUTE_BITMASK;
         break;

      default:
         /* Invalid permission, don't process any blocks. */
         BlockMask = 0;
         RegValue  = 0;
         break;
   }

   /* Finish formatting the value that will be written to all registers. */
   RegValue |= (HWIO_SUBSYSTEM_APSS << HWIO_ACCESS_0_ID_0_SHFT);
   RegValue = RegValue << NVM_ACCESS_CONTROL_APSS_SHIFT;

   AccessReg = (volatile uint32_t *)HWIO_ACCESS_0_ADDR;
   RetVal    = 0;
   for(Index = QAPI_NVM_BLOCK_OFFSET; Index < (QAPI_NVM_BLOCK_OFFSET + QAPI_NVM_BLOCK_COUNT); Index ++)
   {
      /* See if this block is requested to be set and we have permissions for
         the block. */
      if(BlockMask & (1 << Index))
      {
         /* Set the NVM permissions and update the return value. */
         AccessReg[Index] = (AccessReg[Index] & ~NVM_ACCESS_CONTROL_APSS_BITMASK) | RegValue;
         RetVal |= (1 << Index);
      }
   }

   return(RetVal);
}

/**
   @brief Gets the permissions for an address in NVM.

   @param[in] Address  Address to get permissions for.

   @return Permission level of the selected address.
*/
qapi_NVM_Permissions_t qapi_NVM_Get_Permissions(const void *Address)
{
   qapi_NVM_Permissions_t  RetVal;
   volatile uint32_t      *AccessReg;
   uint32_t                Block;
   uint32_t                RegValue;

   if(((uint32_t)Address >= (uint32_t)QAPI_NVM_APSS_START) && ((uint32_t)Address <= (uint32_t)QAPI_NVM_APSS_END))
   {
      /* Read the permission register. */
      Block = ((uint32_t)Address - (uint32_t)NVM_MAIN_OFFSET) / QAPI_NVM_BLOCK_SIZE;
      AccessReg = (volatile uint32_t *)HWIO_ACCESS_0_ADDR;
      RegValue = (AccessReg[Block] & NVM_ACCESS_CONTROL_APSS_BITMASK) >> NVM_ACCESS_CONTROL_APSS_SHIFT;

      /* Translate the register value to the enum. */
      switch(RegValue & HWIO_ACCESS_0_RWX_0_BMSK)
      {
         case HWIO_ACCESS_CONTROL_READ_BITMASK:
            RetVal = QAPI_NVM_PERMISSIONS_READ_ONLY_E;
            break;

         case (HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_EXECUTE_BITMASK):
            RetVal = QAPI_NVM_PERMISSIONS_READ_EXECUTE_E;
            break;

         case (HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_WRITE_BITMASK):
            RetVal = QAPI_NVM_PERMISSIONS_READ_WRITE_E;
            break;

         case (HWIO_ACCESS_CONTROL_READ_BITMASK | HWIO_ACCESS_CONTROL_WRITE_BITMASK | HWIO_ACCESS_CONTROL_EXECUTE_BITMASK):
            RetVal = QAPI_NVM_PERMISSIONS_READ_WRITE_EXECUTE_E;
            break;

         default:
            RetVal = QAPI_NVM_PERMISSIONS_NONE_E;
            break;
      }
   }
   else
   {
      RetVal = QAPI_NVM_PERMISSIONS_NONE_E;
   }

   return(RetVal);
}

/**
   @brief Shares a section of NVM with another subsystem.

   The remote subsystem will be provided read-only permissions to this section of NVM.

   @param[in] BlockMask  Bitmask of blocks to set permissions on.
   @param[in] Subsystem  Subsystems to set permissions for.
   @param[in] Shared     Flag indicating the block(s) should be shared (true) or
                         not shared (false).

   @return Bitmask of blocks whose permissions were set.
*/
uint16_t qapi_NVM_Share(uint16_t BlockMask, qapi_NVM_Subsystem_t Subsystem, qbool_t Share)
{
   uint16_t           RetVal;
   uint32_t           Index;
   uint32_t           RegValue;
   uint32_t           RegMask;
   volatile uint32_t *AccessReg;

   /* Parse the parameters. */
   RegValue = Share ? HWIO_ACCESS_CONTROL_READ_BITMASK : 0;

   /* Determine the subsystem that is referenced. */
   switch(Subsystem)
   {
      case QAPI_NVM_SUBSYSTEM_ROT_E:
         RegValue |= (HWIO_SUBSYSTEM_ROT << HWIO_ACCESS_0_ID_0_SHFT);
         RegValue  = RegValue << NVM_ACCESS_CONTROL_ROT_SHIFT;
         RegMask   = NVM_ACCESS_CONTROL_ROT_BITMASK;
         break;

      case QAPI_NVM_SUBSYSTEM_BTSS_E:
         RegValue |= (HWIO_SUBSYSTEM_BTSS << HWIO_ACCESS_0_ID_0_SHFT);
         RegValue  = RegValue << NVM_ACCESS_CONTROL_BTSS_SHIFT;
         RegMask   = NVM_ACCESS_CONTROL_BTSS_BITMASK;
         break;

      default:
         BlockMask = 0;
         break;
   }

   RetVal    = 0;
   AccessReg = (volatile uint32_t *)HWIO_ACCESS_0_ADDR;
   for(Index = QAPI_NVM_BLOCK_OFFSET; Index < (QAPI_NVM_BLOCK_OFFSET + QAPI_NVM_BLOCK_COUNT); Index ++)
   {
      /* See if this block is requested to be set and we have permissions for
         the block. */
      if(BlockMask & (1 << Index))
      {
         /* Set the NVM permissions and update the return value. */
         AccessReg[Index] = (AccessReg[Index] & ~RegMask) | RegValue;
         RetVal |= (1 << Index);
      }
   }

   return(RetVal);
}

/**
   @brief Requests permissions to write to NVM.

   This must be called before any calls to qapi_NVM_Write().

   @return QAPI_OK if permissions were granted or a negative value if there was
           an error.
*/
qapi_Status_t qapi_NVM_Request_Write(void)
{
   qapi_Status_t RetVal;
   qbool_t       ProvideAccess;

   if(!NVM_Context.WriteRequested)
   {
      ProvideAccess = true;
      RetVal = qapi_Perform_Operation(TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER, TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER_PARAM_ID, &ProvideAccess, NULL, NULL);

      if(RetVal == QAPI_OK)
      {
         NVM_Context.WriteRequested = true;
      }
   }
   else
   {
      RetVal = QAPI_ERR_EXISTS;
   }

   return(RetVal);
}

/**
   @brief Releases a request for NVM write permissions.

   This allows other cores to write to NVM as needed and should be called once
   all outstanding NVM writes are complete.  Note calling this API may cause
   errors from other APIs that require another core to write to NVM.

   @return QAPI_OK if successfully or a negative value if there was an error.
*/
qapi_Status_t qapi_NVM_Release_Write(void)
{
   qapi_Status_t RetVal;
   qbool_t       ProvideAccess;

   if(NVM_Context.WriteRequested)
   {
      ProvideAccess = false;
      RetVal = qapi_Perform_Operation(TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER, TME_MSG_UID_ACCESS_CONTROL_NVM_REGISTER_PARAM_ID, &ProvideAccess, NULL, NULL);

      if(RetVal == QAPI_OK)
      {
         NVM_Context.WriteRequested = false;
      }
   }
   else
   {
      RetVal = QAPI_ERR_EXISTS;
   }

   return(RetVal);
}

/**
   @brief Writes the provided buffer to the specified address in NVM (RRAM).

   Writes to NVM will block NVM reads so this function blocks until the NVM
   write has completed.

   Also, the caller should be aware that writing to RRAM can block other cores
   (namely BTSS) and very long writes may affect performance.

   @param[in] Address  NVM address to write to.
   @param[in] Buffer   Data to write to NVM.
   @param[in] Length   Length of the data to write to NVM.

   @return QAPI_OK if the data was successfully written to NVM or a negative
           value if there was an error.
*/
qapi_Status_t qapi_NVM_Write(const void *Address, const void *Buffer, uint32_t Length)
{
   qapi_Status_t  RetVal;
   const uint8_t *SrcAddress;
   const uint8_t *DstAddress;
   uint32_t       WriteLength;

   /* Verify the address and size are valid. */
   if(NVM_VerifyAddress(Address, Length))
   {
      /* Make sure that write has been requested. */
      if(NVM_Context.WriteRequested)
      {
         /* Use a local variable for the addresses to make the math simpler. */
         DstAddress = (const uint8_t *)Address;
         SrcAddress = (const uint8_t *)Buffer;

         if((uint32_t)DstAddress & 0x7)
         {
            WriteLength = Length;

            /* DstAddress isn't 8-byte aligned so use NVM_WriteUnaligned to write
               the first part of the data. */
            RetVal = NVM_WriteUnaligned(DstAddress, SrcAddress, &WriteLength);

            DstAddress += WriteLength;
            SrcAddress += WriteLength;
            Length     -= WriteLength;
         }
         else
         {
            RetVal = QAPI_OK;
         }

         /* Write all the data that consumes a full 64-bit block. */
         WriteLength = Length / sizeof(uint64_t);
         if((RetVal == QAPI_OK) && (WriteLength != 0))
         {
            RetVal = NVM_WriteAligned((const uint64_t *)DstAddress, SrcAddress, WriteLength);

            WriteLength *= sizeof(uint64_t);

            DstAddress += WriteLength;
            SrcAddress += WriteLength;
            Length     -= WriteLength;
         }

         if((RetVal == QAPI_OK) && (Length != 0))
         {
            /* Less than 8-bytes remains to be written so use NVM_WriteUnaligned to
               write the remainder of the data. */
            RetVal = NVM_WriteUnaligned(DstAddress, SrcAddress, &Length);
         }
      }
      else
      {
         RetVal = QAPI_NVM_ACCESS_CONTROL_ERROR;
      }
   }
   else
   {
      RetVal = QAPI_ERR_BOUNDS;
   }

   return RetVal;
}

/**
   @brief Erases a section of NVM (RRAM).

   Writes to NVM will block NVM reads so this function blocks until the NVM
   write has completed.

   Also, the caller should be aware that writing to RRAM can block other cores
   (namely BTSS) and very long writes may affect performance.

   @param[in] Address  NVM address to erase.
   @param[in] Length   Length of the data to erase.

   @return QAPI_OK if the data was successfully erase or a negative value if
           there was an error.
*/
qapi_Status_t qapi_NVM_Erase(const void *Address, uint32_t Length)
{
   qapi_Status_t  RetVal;
   const uint8_t *DstAddress;
   uint32_t       EraseLength;
   uint64_t       EraseBuffer[NVM_QUEUE_DEPTH];

   /* Verify the address and size are valid. */
   if(NVM_VerifyAddress(Address, Length))
   {
      /* Make sure that write has been requested. */
      if(NVM_Context.WriteRequested)
      {
         memset(EraseBuffer, 0xFF, sizeof(EraseBuffer));

         /* Use a local variable for the address to make the math simpler. */
         DstAddress = (const uint8_t *)Address;

         if((uint32_t)DstAddress & 0x7)
         {
            /* Perform a small erase at the beginning to align the erase operation. */
            EraseLength = (NVM_QUEUE_SIZE_BYTES <= Length) ? NVM_QUEUE_SIZE_BYTES : Length;

            RetVal = NVM_WriteUnaligned(DstAddress, (const uint8_t *)EraseBuffer, &EraseLength);

            DstAddress += EraseLength;
            Length     -= EraseLength;
         }
         else
         {
            RetVal = QAPI_OK;
         }

         /* Erase the remaining data. */
         while((RetVal == QAPI_OK) && (Length != 0))
         {
            EraseLength = (NVM_QUEUE_SIZE_BYTES <= Length) ? NVM_QUEUE_SIZE_BYTES : Length;

            /* Call NVM_Write to write the remaining data (as this will
               also handle the remaining length being unaligned). */
            RetVal = qapi_NVM_Write(DstAddress, EraseBuffer, EraseLength);

            /* Adjust the pointers. */
            DstAddress += EraseLength;
            Length     -= EraseLength;
         }
      }
      else
      {
         RetVal = QAPI_NVM_ACCESS_CONTROL_ERROR;
      }
   }
   else
   {
      RetVal = QAPI_ERR_BOUNDS;
   }

   return RetVal;
}

