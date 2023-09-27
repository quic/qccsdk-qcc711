/*
 * Copyright (c) 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_nvm_rot.h"

/* IPC headers*/ 
#include "tme_ipc_utils.h"
#include "TmeMessagesUids.h"
#include "tme_ipc_nvm_common.h"

/**
   @brief Writes the provided buffer to the specified offset in NVM (RRAM)
   allocated to ROT.
   
   Valid offset range is from 0 to (QAPI_NVM_ROT_SIZE-1).

   Writes to NVM will block NVM reads so this function blocks until the NVM
   write has completed.

   Also, the caller should be aware that writing to RRAM can block other cores
   (namely BTSS) and very long writes may affect performance.

   @param[in] Offset   Offset at which data to write.
   @param[in] Buffer   Data to write to NVM.
   @param[in] Length   Length of the data to write to NVM.

   @return
   QAPI_OK -- If the data was successfully written to NVM.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Write_ROT(uint32_t Offset, const void *Buffer, uint32_t Length)
{
   qapi_NVM_Write_Rot_Params_t NVMWriteParams;

   NVMWriteParams.Offset = Offset;
   NVMWriteParams.Buffer = Buffer;
   NVMWriteParams.BufferLen = Length;
   
   return qapi_Perform_Operation(TME_MSG_UID_GENERIC_NVM_WRITE_EX, TME_MSG_UID_GENERIC_NVM_WRITE_EX_PARAM_ID, &NVMWriteParams, NULL, NULL);
}

/**
   @brief Reads NVM (RRAM) data from the specified offset to provided buffer.
   Valid offset range is from 0 to (QAPI_NVM_ROT_SIZE-1).
   
   @param[in] Offset   Offset from data to read.
   @param[in] Buffer   Buffer to save read NVM data.
   @param[in] Length   Length of the data to read from NVM.

   @return
   QAPI_OK -- If the data was successfully written to NVM.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Read_ROT(uint32_t Offset, void *Buffer, uint32_t Length)
{
   qapi_NVM_Read_Rot_Params_t NVMReadParams;
   
   NVMReadParams.Offset = Offset;
   NVMReadParams.Buffer = Buffer;
   NVMReadParams.BufferLen = Length;
   
   return qapi_Perform_Operation(TME_MSG_UID_GENERIC_NVM_READ_EX, TME_MSG_UID_GENERIC_NVM_READ_EX_PARAM_ID, &NVMReadParams, NULL, NULL);
}
