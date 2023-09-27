/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file timer.h
   @brief Timer internal Services Interface definition.

   This module provide timer internal APIs, types, and definitions.
*/
 
#ifndef __TIMER_H__
#define __TIMER_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup peripherals_timer
@{
*/

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
   @brief Enable CETimer and Sync CETimer with GLTimer.

   This function must be called after cold boot or warm boot.

   @return Current Global timer time value in microsecond.
*/
uint64_t TMR_Enable();

/**
   @brief Disable CETimer.
*/
void TMR_Disable();

/**
   @brief Get current timer value in millisecond.

   @return Current timer value in millisecond.
*/
uint32_t TMR_GetCurTimeMs();

/** @} */

#endif

