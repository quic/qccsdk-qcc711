 /*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __CRYPTO_DEMO_H__
#define __CRYPTO_DEMO_H__

#include "qcli_api.h"

/**
   @brief Initialize crypto demo.

   @param[in] Parent_Group Parent group handle.
*/
void Initialize_Crypto_Demo(QCLI_Group_Handle_t Parent_Group);

/**
   @brief Cleans up resources used by the crypto demo.
*/
void Cleanup_Crypto_Demo(void);

#endif