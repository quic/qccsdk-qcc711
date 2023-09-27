 /*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __FWUP_DEMO_H__
#define __FWUP_DEMO_H__

#include "qcli_api.h"

/**
   @brief Initialize FWUP demo.

   @param[in] Parent_Group Parent group handle.
*/
void Initialize_FWUP_Demo(QCLI_Group_Handle_t Parent_Group);

/**
   @brief Cleans up resources used by the FWUP demo.
*/
void Cleanup_FWUP_Demo(void);

#endif // __FWUP_DEMO_H__