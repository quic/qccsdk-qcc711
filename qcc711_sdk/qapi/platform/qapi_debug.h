/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_debug.h
   @brief Debug related APIs, types, and definitions.

*/

#ifndef __QAPI_DBG_H__
#define __QAPI_DBG_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_dbg
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Determines if a debugger is currently attached.

   @return
   TRUE -- If a debugger is attached. \n
   FALSE -- If a debugger is not attached.
*/
qbool_t qapi_DBG_Debugger_Attached(void);

/** @} */  /* end_addtogroup qapi_platform_dbg */

#endif

