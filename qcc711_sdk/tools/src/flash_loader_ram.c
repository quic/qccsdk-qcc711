/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

//------------------------------------------------------------------------------
//
// Copyright (c) 2008-2015 IAR Systems
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// $Revision: 38952 $
//
//------------------------------------------------------------------------------
#include <string.h>
#include "flash_loader.h"
#include "flash_loader_extra.h"
#include "qcc710.h"
#include "qapi_power.h"
#include "qapi_timer.h"
#include "qapi_rot.h"
#include "qapi_nvm.h"
#include "qapi_heap.h"
#include "HALhwio.h"
#include "hwio_aon.h"

/* Enable support for chip erase. This isn't necessary for RRAM but may be    */
/* desired for other reasons.                                                 */
#define SUPPORT_ERASE 1

/* Memory initialization */
extern void __iar_data_init3(void);

uint32_t FlashInit(void *base_of_flash, uint32_t image_size, uint32_t link_address, uint32_t flags, int argc, char const *argv[])
{
   qapi_Status_t Result;
   uint32_t      RetVal;

   /* Signal that APSS is running. */   
   HWIO_AON_PME_APPS_STATUS_OUTM(HWIO_AON_PME_APPS_STATUS_OPERATIVE_BMSK, HWIO_AON_PME_APPS_STATUS_OPERATIVE_BMSK);

   /* Initialize memory. */
   __iar_data_init3();
   
   /* Configure the interrupt vector. */
   SCB->VTOR = 0x20010000;
   
   RetVal = RESULT_ERROR;
   Result = qapi_PWR_Initialize(NULL);
   if (Result == QAPI_OK)
   {
      Result = qapi_TMR_Init();
      if (Result == QAPI_OK)
      { 
         /* Connect to ROT. */
         Result = qapi_ROT_Session_Start();
         if (Result == QAPI_OK)
         {
            /* Request NVM write operation. */
            Result = qapi_NVM_Request_Write();
            if (Result == QAPI_OK)
            {
               /*  Set the accces control registers*/
               qapi_NVM_Set_Permissions(QAPI_NVM_APSS_BLOCKS_BITMASK, QAPI_NVM_PERMISSIONS_READ_WRITE_E);
               RetVal = RESULT_OK;
            }
         }
      }
   }
   return(RetVal);
}

uint32_t FlashWrite(void *block_start, uint32_t offset_into_block, uint32_t count, char const *buffer)
{
   qapi_Status_t  Result;
   void          *DstAddress;

   DstAddress = (uint8_t *)block_start + offset_into_block;

   Result = qapi_NVM_Write(DstAddress, buffer, count);

   return((Result == QAPI_OK) ? RESULT_OK : RESULT_ERROR);
}

uint32_t FlashErase(void *block_start, uint32_t block_size)
{
#if SUPPORT_ERASE

   qapi_Status_t  Result;

   Result = qapi_NVM_Erase(block_start, block_size);

   return((Result == QAPI_OK) ? RESULT_OK : RESULT_ERROR);
#else
   return(RESULT_OK);
#endif
}

OPTIONAL_CHECKSUM
uint32_t FlashChecksum(void const *begin, uint32_t count)
{
  return(Crc16((uint8_t const *)begin, count));
}

OPTIONAL_SIGNOFF
uint32_t FlashSignoff(void)
{
   /* Return the control of read write registers to ROT. */
   qapi_NVM_Set_Permissions(QAPI_NVM_APSS_BLOCKS_BITMASK, QAPI_NVM_PERMISSIONS_READ_EXECUTE_E);
   qapi_NVM_Release_Write();
   qapi_ROT_Session_End();

   return(RESULT_OK);
}

void main(void)
{
}