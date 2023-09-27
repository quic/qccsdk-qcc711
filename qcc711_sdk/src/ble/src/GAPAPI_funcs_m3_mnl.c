/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_gap.h"
#include "qapi_ble_errors.h"
#include "GAPAPI_params.h"
#include "GAPAPI_cb_m3.h"
#include "GAPAPI_mnl_util.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include "qapi_heap.h"
#include <string.h>
#include "stringl.h"
#include "ram.h"

   /* Defines the valid APSS memory blocks that may be returned from    */
   /* RAM_AddressRangeToBlocks().                                       */
#define APSS_RAM_BLOCK_TOTAL_BITMASK   (RAM_APSS_BLOCKS_BITMASK | RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK)

   /* Defines the valid BTSS memory blocks that may be returned from    */
   /* RAM_AddressRangeToBlocks().                                       */
#define BTSS_RAM_BLOCK_TOTAL_BITMASK   (RAM_BTSS_BLOCKS_BITMASK | RAM_BTSS_BLOCK_7_SUBBLOCKS_BITMASK)

   /* Stores information on a buffer requested by upper layer to be     */
   /* shared with the m3.                                               */
typedef struct
{
   uint32_t   BlockMask;
   uint16_t   Ext_Reference_Count;
   uint8_t    ESL_Use_Count;
} APSS_RAM_Block_t;

   /* Local variables.                                                  */
static boolean_t        ESLObjectWriteActive;
static APSS_RAM_Block_t BufferEntries[] =
{
   { RAM_APSS_BLOCK_0_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_1_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_2_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_3_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_4_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_5_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_6_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_7_BITMASK,            0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_0_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_1_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_2_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_3_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_4_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_5_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_6_BITMASK, 0, 0 },
   { RAM_APSS_BLOCK_7_SUBBLOCK_7_BITMASK, 0, 0 },
};

#define TOTAL_NUMBER_BUFFER_ENTRIES    (sizeof(BufferEntries)/sizeof(APSS_RAM_Block_t))

unsigned int CountAdvertisingDataRecords(unsigned int Advertising_Data_Length, uint8_t *Advertising_Data)
{
    int NumRecords = 0;
    uint8_t Length;
    unsigned int Index = 0;

    if(Advertising_Data_Length && Advertising_Data)
    {
        while(Index < Advertising_Data_Length)
        {
            Length = Advertising_Data[Index++];

            if((Length > 0) && (Index + Length <= Advertising_Data_Length))
            {
                ++NumRecords;
                Index += Length;
            }
            else
            {
                break;
            }
        }
    }

    return NumRecords;
}

unsigned int ParseAdvertisingData(unsigned int Advertising_Data_Length, uint8_t *Advertising_Data, qapi_BLE_GAP_LE_Advertising_Data_t *ParsedData)
{
    unsigned int ParsedRecords = 0;
    unsigned int NumRecords;
    uint8_t Length;
    unsigned int Index;
    bool error = false;

    if((Advertising_Data_Length) && (Advertising_Data) && (ParsedData))
    {
        NumRecords = CountAdvertisingDataRecords(Advertising_Data_Length, Advertising_Data);

        if(ParsedData->Number_Data_Entries >= NumRecords)
        {
            Index = 0;

            while(Index < Advertising_Data_Length && ParsedRecords < NumRecords && !error)
            {
                Length = Advertising_Data[Index++];

                if((Length > 0) && (Length + Index <= Advertising_Data_Length))
                {
                    ParsedData->Data_Entries[ParsedRecords].AD_Data_Buffer = qapi_Malloc(Length);

                    if(ParsedData->Data_Entries[ParsedRecords].AD_Data_Buffer != NULL)
                    {
                        ParsedData->Data_Entries[ParsedRecords].AD_Data_Length = Length-1;
                        ParsedData->Data_Entries[ParsedRecords].AD_Type = Advertising_Data[Index++];
                        memscpy(ParsedData->Data_Entries[ParsedRecords].AD_Data_Buffer, Length-1, &Advertising_Data[Index], Length-1);

                        /* Match Bluetopia behavior of null-terminating AD buffers. */
                        ParsedData->Data_Entries[ParsedRecords].AD_Data_Buffer[Length-1] = 0;

                        ++ParsedRecords;
                        Index += Length-1;
                    }
                    else
                    {
                        error = true;
                    }
                }
                else
                {
                    error = true;
                }
            }

            if(error)
            {
                for(Index=0; Index<ParsedRecords; Index++)
                {
                    qapi_Free(ParsedData->Data_Entries[Index].AD_Data_Buffer);
                    ParsedData->Data_Entries[Index].AD_Data_Buffer = NULL;
                }

                ParsedRecords = 0;
            }
        }
    }

    if(ParsedData)
    {
        ParsedData->Number_Data_Entries = ParsedRecords;
    }

    return ParsedRecords;
}

   /* Called when a write request event is received.                    */
void ESLD_Write_Request_Event_Received(void)
{
   /* Flag that a write is active.                                      */
   ESLObjectWriteActive = TRUE;
}

   /* Called when a write stopped event is received.                    */
void ESLD_Write_Stopped_Event_Received(void)
{
   uint32_t     BlockMask;
   unsigned int Index;

   /* Flag that a write stopped has been received.                      */
   ESLObjectWriteActive = FALSE;

   /* Revoke access for all currently shared blocks.                    */
   for(Index=0,BlockMask=0;Index<TOTAL_NUMBER_BUFFER_ENTRIES;Index++)
   {
      /* Check to see if ESL is using this block.                       */
      if(BufferEntries[Index].ESL_Use_Count)
      {
         /* Clear the ESL use count.                                    */
         BufferEntries[Index].ESL_Use_Count = 0;

         /* If nobody else is using the block un-share it.              */
         if(BufferEntries[Index].Ext_Reference_Count == 0)
         {
            /* Add block to list of blocks whose BTSS memory acess will */
            /* be revoked.                                              */
            BlockMask |= BufferEntries[Index].BlockMask;
         }
      }
   }

   if(BlockMask != 0)
      RAM_Share(RAM_SUBSYSTEM_BTSS_E, BlockMask, RAM_PERM_NO_ACCESS_E);
}

   /* The following function handles buffer access to M3 memory that is */
   /* needed by the ESL module.                                         */
int APSS_Buffer_Allow_Access_For_BTSS(uint32_t Buffer_Length, uint8_t *Buffer, boolean_t NonObjectWriteCall)
{
   int          ret_val;
   uint32_t     RAM_Blocks;
   uint32_t     BlockMask;
   unsigned int Index;

   /* Verify the buffers.                                               */
   if((Buffer_Length > 0) && (Buffer != NULL))
   {
      /* Make sure that a write is active.                              */
      if((ESLObjectWriteActive) || (NonObjectWriteCall))
      {
         /* Convert the buffer to a bitmask of blocks.                  */
         RAM_Blocks = RAM_AddressRangeToBlocks((const void *)Buffer, (const void *)&(Buffer[Buffer_Length - 1]));
         if(RAM_Blocks != 0)
         {
            /* Make sure only APSS memory blocks were specified.        */
            if((RAM_Blocks & (~APSS_RAM_BLOCK_TOTAL_BITMASK)) == 0)
            {
               /* Check to see if we have already enabled memory access */
               /* for the buffer.                                       */
               for(Index=0,BlockMask=0;Index<TOTAL_NUMBER_BUFFER_ENTRIES;Index++)
               {
                  /* Check to see if this RAM block is one of the ones  */
                  /* to be enabled by the user specified buffer.        */
                  if(BufferEntries[Index].BlockMask & RAM_Blocks)
                  {
                     /* Check to see if this entry is already use.      */
                     if((BufferEntries[Index].ESL_Use_Count == 0) && (BufferEntries[Index].Ext_Reference_Count == 0))
                     {
                        /* RAM block is not currently shared so go ahead*/
                        /* and at it to list of blocks to be shared.    */
                        BlockMask |= BufferEntries[Index].BlockMask;
                     }

                     /* Check to see which reference count to increment.*/
                     if(NonObjectWriteCall)
                     {
                        /* Block is already enabled for use.  If this is*/
                        /* a non-ESL use case we need to increment      */
                        /* reference counter.                           */
                        BufferEntries[Index].Ext_Reference_Count++;
                     }
                     else
                     {
                        /* Increment the ESL use count.                 */
                        BufferEntries[Index].ESL_Use_Count++;
                     }
                  }
               }

               /* Continue only if we have blocks to enable access for. */
               if(BlockMask != 0)
               {
                  /* Share the RAM block.                               */
                  if(RAM_Share(RAM_SUBSYSTEM_BTSS_E, BlockMask, RAM_PERM_READ_WRITE_E) == QAPI_OK)
                  {
                     /* Return OK to indicate that caller may send IPC  */
                     /* message to M0 to indicate buffer is ready for   */
                     /* use.                                            */
                     ret_val = GAP_ERROR_BUFFER_STATUS_OK;
                  }
                  else
                  {
                     /* Return an error.                                */
                     ret_val = GAP_ERROR_BUFFER_STATUS_UNKNOWN_ERROR;
                  }

                  /* Loop through list and increment appropriate        */
                  /* reference counter/boolean to indicate that this    */
                  /* block is currently shared (or not based on the     */
                  /* return value).                                     */
                  for(Index=0;Index<TOTAL_NUMBER_BUFFER_ENTRIES;Index++)
                  {
                     /* Check to see if this RAM block is one of the    */
                     /* ones to be enabled by the user specified buffer.*/
                     if(BufferEntries[Index].BlockMask & RAM_Blocks)
                     {
                        /* Check to see if this is a ESL or non-ESL     */
                        /* call.                                        */
                        if(NonObjectWriteCall)
                        {
                           /* Check for success or failure.             */
                           if(ret_val != GAP_ERROR_BUFFER_STATUS_OK)
                           {
                              /* We failed on non-ESL call.  Go ahead   */
                              /* and decrement all reference counts we  */
                              /* just incremented.                      */
                              if(BufferEntries[Index].Ext_Reference_Count)
                                 BufferEntries[Index].Ext_Reference_Count--;
                           }
                        }
                        else
                        {
                           /* Check for success or failure.             */
                           if(ret_val == GAP_ERROR_BUFFER_STATUS_OK)
                           {
                              /* ESL Use Count is not a proper count, so*/
                              /* just set it 1 to indicate block is in  */
                              /* use.                                   */
                              BufferEntries[Index].ESL_Use_Count = 1;
                           }
                           else
                           {
                              /* Failure, decrement the ESL Use Count.  */
                              if(BufferEntries[Index].ESL_Use_Count)
                                 BufferEntries[Index].ESL_Use_Count--;
                           }
                        }
                     }
                  }
               }
               else
               {
                  /* No blocks to enable access so just return success. */
                  ret_val = GAP_ERROR_BUFFER_STATUS_OK;
               }
            }
            else
            {
               /* BTSS blocks were specified.  verified that only BTSS  */
               /* blocks were specified.                                */
               if((RAM_Blocks & (~BTSS_RAM_BLOCK_TOTAL_BITMASK)) == 0)
               {
                  /* Caller specified BTSS buffers so we do not need to */
                  /* do anything to allow for BTSS access to that memory*/
                  /* and can just return success here.                  */
                  ret_val = GAP_ERROR_BUFFER_STATUS_OK;
               }
               else
               {
                  /* Caller specified buffer that crosses BTSS and APSS */
                  /* memory so return an error.                         */
                  ret_val = GAP_ERROR_BUFFER_STATUS_INVALID_PARAMETER;
               }
            }
         }
         else
            ret_val = GAP_ERROR_BUFFER_STATUS_INVALID_OPERATION;
      }
      else
         ret_val = GAP_ERROR_BUFFER_STATUS_INVALID_OPERATION;
   }
   else
      ret_val = GAP_ERROR_BUFFER_STATUS_INVALID_PARAMETER;

   return(ret_val);
}

   /* Revokes RAM block access (only to be called by external call).    */
void APSS_Buffer_Revoke_Access_From_BTSS(uint32_t Buffer_Length, uint8_t *Buffer)
{
   uint32_t     RAM_Blocks;
   uint32_t     BlockMask;
   unsigned int Index;

   /* Verify the buffers.                                               */
   if((Buffer_Length > 0) && (Buffer != NULL))
   {
      /* Convert the buffer to a bitmask of blocks.                     */
      RAM_Blocks = RAM_AddressRangeToBlocks((const void *)Buffer, (const void *)&(Buffer[Buffer_Length - 1]));
      if(RAM_Blocks != 0)
      {
         /* Make sure only APSS memory blocks were specified.           */
         if((RAM_Blocks & (~APSS_RAM_BLOCK_TOTAL_BITMASK)) == 0)
         {
            /* Check to see if we have already enabled memory access for*/
            /* the buffer.                                              */
            for(Index=0,BlockMask=0;Index<TOTAL_NUMBER_BUFFER_ENTRIES;Index++)
            {
               /* Check to see if this RAM block is one of the ones to  */
               /* be enabled by the user specified buffer.              */
               if(BufferEntries[Index].BlockMask & RAM_Blocks)
               {
                  /* Block is enabled by specified memory range,        */
                  /* decrement the reference count (should never be here*/
                  /* for ESL usage).                                    */
                  if(BufferEntries[Index].Ext_Reference_Count)
                  {
                     /* Decrement count.                                */
                     BufferEntries[Index].Ext_Reference_Count--;

                     /* Check to see if this memory block is already in */
                     /* use.                                            */
                     if((BufferEntries[Index].ESL_Use_Count == 0) && (BufferEntries[Index].Ext_Reference_Count == 0))
                     {
                        /* RAM block no needs to be shared.  Add it to  */
                        /* list of blocks to revoke access for.         */
                        BlockMask |= BufferEntries[Index].BlockMask;
                     }
                  }
               }
            }

            /* Continue only if we have blocks to enable access for.    */
            if(BlockMask != 0)
            {
               /* Revoke access for BTSS to access the specified RAM    */
               /* blocks.                                               */
               RAM_Share(RAM_SUBSYSTEM_BTSS_E, BlockMask, RAM_PERM_NO_ACCESS_E);
            }
         }
      }
   }
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Convert_Advertising_Data(qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Advertising_Data_t *Advertising_Data)
{
    int ret_val;
    uint8_t *Current;
    uint16_t RemainingLength;
    uint16_t Length;
    uint32_t Index;

    if((GAP_LE_Advertising_Data) && (GAP_LE_Advertising_Data->Number_Data_Entries) && (GAP_LE_Advertising_Data->Data_Entries) && (Advertising_Data))
    {
        Current = (uint8_t *)Advertising_Data;
        RemainingLength = (uint16_t)QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE;

        for(Index = 0; Index < GAP_LE_Advertising_Data->Number_Data_Entries; Index++)
        {
            Length = (uint16_t)GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Length + 2;

            if(Length <= RemainingLength)
            {
                Current[0] = Length - 1;
                Current[1] = GAP_LE_Advertising_Data->Data_Entries[Index].AD_Type;
                memscpy(&(Current[2]), Length - 2, GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Buffer, GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Length);

                Current += Length;
                RemainingLength -= Length;
            }
            else
            {
                break;
            }
        }

        ret_val = (int)Index;
        memset(Current, 0, RemainingLength);
    }
    else
        ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

    return ret_val;
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Parse_Advertising_Data(qapi_BLE_Advertising_Data_t *Advertising_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data)
{
    int ret_val;

    if((Advertising_Data) && ((!GAP_LE_Advertising_Data) || ((GAP_LE_Advertising_Data->Number_Data_Entries > 0) && (GAP_LE_Advertising_Data->Data_Entries))))
    {
        ret_val = (int)CountAdvertisingDataRecords((unsigned int)QAPI_BLE_ADVERTISING_DATA_SIZE, Advertising_Data->Advertising_Data);

        if(GAP_LE_Advertising_Data)
        {
            if(ret_val <= (int)GAP_LE_Advertising_Data->Number_Data_Entries)
            {
                ret_val = ParseAdvertisingData((unsigned int)QAPI_BLE_ADVERTISING_DATA_SIZE, Advertising_Data->Advertising_Data, GAP_LE_Advertising_Data);
            }
            else
            {
                ret_val = QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE;
            }
        }
    }
    else
        ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

    return ret_val;
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Convert_Scan_Response_Data(qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data)
{
    int ret_val;
    uint8_t *Current;
    uint16_t RemainingLength;
    uint16_t Length;
    uint32_t Index;

    if((GAP_LE_Advertising_Data) && (GAP_LE_Advertising_Data->Number_Data_Entries) && (GAP_LE_Advertising_Data->Data_Entries) && (Scan_Response_Data))
    {
        Current = (uint8_t *)Scan_Response_Data;
        RemainingLength = (uint16_t)QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE;

        for(Index = 0; Index < GAP_LE_Advertising_Data->Number_Data_Entries; Index++)
        {
            Length = (uint16_t)GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Length + 2;

            if(Length <= RemainingLength)
            {
                Current[0] = Length - 1;
                Current[1] = GAP_LE_Advertising_Data->Data_Entries[Index].AD_Type;
                memscpy(&(Current[2]), Length - 2, GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Buffer, GAP_LE_Advertising_Data->Data_Entries[Index].AD_Data_Length);

                Current += Length;
                RemainingLength -= Length;
            }
            else
            {
                break;
            }
        }

        ret_val = (int)Index;
        memset(Current, 0, RemainingLength);
    }
    else
        ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

    return ret_val;
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Parse_Scan_Response_Data(qapi_BLE_Scan_Response_Data_t *Scan_Response_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data)
{
    int ret_val;

    if((Scan_Response_Data) && ((!GAP_LE_Advertising_Data) || ((GAP_LE_Advertising_Data->Number_Data_Entries > 0) && (GAP_LE_Advertising_Data->Data_Entries))))
    {
        ret_val = (int)CountAdvertisingDataRecords((unsigned int)QAPI_BLE_ADVERTISING_DATA_SIZE, Scan_Response_Data->Scan_Response_Data);

        if(GAP_LE_Advertising_Data)
        {
            if(ret_val <= (int)GAP_LE_Advertising_Data->Number_Data_Entries)
            {
                ret_val = ParseAdvertisingData((unsigned int)QAPI_BLE_ADVERTISING_DATA_SIZE, Scan_Response_Data->Scan_Response_Data, GAP_LE_Advertising_Data);
            }
            else
            {
                ret_val = QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE;
            }
        }
    }
    else
        ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

    return ret_val;
}

void QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cleanup_AES_CMAC_Operation(void *GapleAesCmacContext)
{
    GAP_LE_Cleanup_AES_CMAC_Operation_Params_t *Params;

    if(NULL != (Params = IPC_GetSharedMemory(GAP_LE_CLEANUP_AES_CMAC_OPERATION_PARAMS_SIZE)))
    {
        /* The pointer here is simply a handle, so there is nothing associated with it to copy. */
        Params->GapleAesCmacContext = GapleAesCmacContext;

        IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_CLEANUP_AES_CMAC_OPERATION, GAP_LE_CLEANUP_AES_CMAC_OPERATION_PARAMS_SIZE, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Perform_AES_CMAC_Operation(uint32_t BluetoothStackID, void *GapleAesCmacContext, uint32_t BlockLength, uint8_t *BlockData, qapi_BLE_Encryption_Key_t *MACResult)
{
    GAP_LE_Perform_AES_CMAC_Operation_Params_t *Params;
    int ret_val;
    uint32_t Offset;

    /* Attempt to enable memory access to M0 for this memory blob.      */
    ret_val = APSS_Buffer_Allow_Access_For_BTSS(BlockLength,  BlockData, TRUE);
    if(ret_val == GAP_ERROR_BUFFER_STATUS_OK)
    {
       uint32_t MessageSize = ALIGN32(GAP_LE_PERFORM_AES_CMAC_OPERATION_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_Encryption_Key_t));

       if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
       {
           Offset = ALIGN32(GAP_LE_PERFORM_AES_CMAC_OPERATION_PARAMS_SIZE);
           Params->BluetoothStackID = BluetoothStackID;

           /* The pointer here is simply a handle, so there is nothing associated with it to copy. */
           Params->GapleAesCmacContext = GapleAesCmacContext;
           Params->BlockLength         = BlockLength;
           Params->BlockData           = BlockData;

           if(MACResult != NULL)
           {
               Params->MACResult = (qapi_BLE_Encryption_Key_t *)(((uint8_t *)Params) + Offset);
               Offset = ALIGN32(Offset + sizeof(qapi_BLE_Encryption_Key_t));
           }
           else
           {
               Params->MACResult = NULL;
           }

           ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_PERFORM_AES_CMAC_OPERATION, MessageSize, (uint8_t *)Params);

           if(MACResult != NULL)
               memscpy(MACResult, sizeof(qapi_BLE_Encryption_Key_t), Params->MACResult, sizeof(qapi_BLE_Encryption_Key_t));

           IPC_FreeSharedMemory(Params);
       }
       else
           ret_val = QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES;

       /* Regardless or return result, revoke access to APSS memory for */
       /* this block.                                                   */
       APSS_Buffer_Revoke_Access_From_BTSS(BlockLength,  BlockData);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Minimum_Encryption_Key_Size(uint32_t BluetoothStackID, uint8_t EncryptionKeySize)
{
    GAP_LE_Set_Minimum_Encryption_Key_Size_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(GAP_LE_SET_MINIMUM_ENCRYPTION_KEY_SIZE_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID  = BluetoothStackID;
        Params->EncryptionKeySize = EncryptionKeySize;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPAPI, FUNCTION_ID_GAP_LE_SET_MINIMUM_ENCRYPTION_KEY_SIZE, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}
