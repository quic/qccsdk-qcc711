/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __MFG_DEMO_H__
#define __MFG_DEMO_H__

#include "qcli_api.h"

/**
   @brief Initializes the Manufacturing demo application.

   @param[in] Parent_Group  QCLI handle for the parent group.
*/
qbool_t Initialize_Mfg_Demo(QCLI_Group_Handle_t Parent_Group);

/**
   @brief Cleans up the Manufacturing demo application.
*/
void Cleanup_Mfg_Demo(void);

#endif

