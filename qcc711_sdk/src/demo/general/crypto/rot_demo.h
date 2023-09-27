 /*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __ROT_DEMO_H__
#define __ROT_DEMO_H__

#include "qapi_types.h"

/**
   @brief Initializes the RoT demo application.

   @return true if RoT demo initialized successfully or false on failure.
*/
qbool_t Initialize_RoT_Demo(void);

/**
   @brief Cleans up the RoT demo application.
*/
void Cleanup_RoT_Demo(void);

#endif