/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
// QAPI headers
#include "qapi_nvm.h"

 // TME utility headers
#include "tme_ipc_nvm_utils.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Validates whether the given address range falls in the subsystem NVM Blocks which
          can be used FW Updated related operations.

   @param[in] StartAddress   Start address.
   @param[in] Size           Number of bytes from start address.


   @return QAPI_OK if address range is valid, or a negative value if not.

*/
qapi_Status_t Validate_FW_Update_Address_Range(uint32_t StartAddress, uint32_t Size)
{
    // Validate the address range falls within allowed NVM Address Range along with size
    if (Size > (uint32_t)QAPI_NVM_APSS_SIZE || StartAddress < (uint32_t)QAPI_NVM_APSS_START ||
        StartAddress > ((uint32_t)QAPI_NVM_APSS_END - Size))
    {
       return QAPI_ERR_INVALID_PARAM;
    }
    else
    {
       return QAPI_OK;
    }
}

/**
   @brief Manage TME Read only Access (Share/Revoke) of subsystem' NVM block. Based on provided
          start address and size it will calculate the number of NVM's block impacted and 
          provide or revoke access according to NvmShare flag provided.

   @param[in] StartAddress   Start address from which access is to be managed.
   @param[in] Size           Number of bytes from start address whose access is to be managed.
   @param[in] ShareNvm       True if access is to given and False to revoke the access.


   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Manage_TME_Access_Of_NVM(uint32_t StartAddress, uint32_t Size, qbool_t ShareNvm)
{
    if(StartAddress == 0 || Size == 0)
    {
      return QAPI_ERR_INVALID_PARAM;
    }
    uint16_t nvmBlocks = 0;
    uint16_t nvmRet = 0;
    qapi_Status_t returnStatus = QAPI_ERROR;

    /* Get block bitmask for provided address */
    nvmBlocks = qapi_NVM_Address_Range_To_Blocks((const void *)StartAddress, (const void *)(StartAddress + Size));

    if(nvmBlocks)
    {
      /* Share NVM buffers with TME; qapi_NVM_Share() will provide rad-only access to TME */
      nvmRet = qapi_NVM_Share(nvmBlocks, QAPI_NVM_SUBSYSTEM_ROT_E, ShareNvm);
    }

    if(nvmBlocks != 0 && nvmBlocks == nvmRet)
    {
      returnStatus = QAPI_OK;
    }

    return returnStatus;
}

/**
   @brief Give TME Access to all NMV Block of subsystem.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Give_TME_Access_Of_NVM(void)
{
    uint32_t nvmSize = (uint32_t)((uint32_t)QAPI_NVM_APSS_END - (uint32_t)QAPI_NVM_APSS_START);
    return Manage_TME_Access_Of_NVM((uint32_t)QAPI_NVM_APSS_START, nvmSize, true);
}

/**
   @brief Revole TME Access from all NMV Block of subsystem.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Revoke_TME_Access_Of_NVM(void)
{
    uint32_t nvmSize = (uint32_t)((uint32_t)QAPI_NVM_APSS_END - (uint32_t)QAPI_NVM_APSS_START);
    return Manage_TME_Access_Of_NVM((uint32_t)QAPI_NVM_APSS_START, nvmSize, false);
}

