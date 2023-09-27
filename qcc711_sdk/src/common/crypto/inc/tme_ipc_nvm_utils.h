/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

/*! \file tme_ipc_nvm_utils.h
 * @brief The utility related to NVM of various sub system.
 */
#ifndef TME_IPC_NVM_UTILS_H
#define TME_IPC_NVM_UTILS_H

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

#include "qapi_status.h"
#include "qapi_types.h"

/**
   @brief Validates whether the given address range falls in the subsystem NVM Blocks which
          can be used FW Updated related operations.

   @param[in] StartAddress   Start address.
   @param[in] Size           Number of bytes from start address.


   @return QAPI_OK if address range is valid, or a negative value if not.

*/
qapi_Status_t Validate_FW_Update_Address_Range(uint32_t StartAddress, uint32_t Size);

/**
   @brief Manage TME Read only Access (Share/Revoke) of subsystem' NVM block. Based on provided
          start address and size it will calculate the number of NVM's block impacted and 
          provide or revoke access according to NvmShare flag provided.

   @param[in] StartAddress   Start address from which access is to be managed.
   @param[in] Size           Number of bytes from start address whose access is to be managed.
   @param[in] ShareNvm       True if access is to given and False to revoke the access.


   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Manage_TME_Access_Of_NVM(uint32_t StartAddress, uint32_t Size, qbool_t ShareNvm);

/**
   @brief Give TME Access to all NMV Block of subsystem.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Give_TME_Access_Of_NVM(void);

/**
   @brief Revole TME Access from all NMV Block of subsystem.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.

*/
qapi_Status_t Revoke_TME_Access_Of_NVM(void);

#endif //TME_IPC_ACCESS_CONTROL_COMMON_H
