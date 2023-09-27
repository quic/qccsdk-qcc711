/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_debug.h"
#include "HALhwio.h"
#include "hwio_aon.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Determines if a debugger is currently attached.

   @return True if a debugger is attached or false if it is not.
*/
qbool_t qapi_DBG_Debugger_Attached(void)
{
   return ((qbool_t)(HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_DEBUG_MODE_BMSK) != 0));
}

