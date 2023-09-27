/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __NVM_DEMO_H__
#define __NVM_DEMO_H__

#include "qcli_api.h"

/**
   @brief Initializes the NVM demo application.

   @param[in] Parent_Group QCLI handle for the parent group.
*/
qbool_t Initialize_Nvm_Demo(QCLI_Group_Handle_t Parent_Group);

/**
   @brief Cleans up the NVM demo application.
*/
void Cleanup_Nvm_Demo(void);

#endif
