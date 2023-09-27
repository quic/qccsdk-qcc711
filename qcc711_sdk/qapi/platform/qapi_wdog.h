/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_wdog.h
   @brief Watchdog APIs, types, and definitions.

*/

#ifndef __QAPI_WDOG_H__
#define __QAPI_WDOG_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_wdog
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
   @brief Configures the watchdog timer.

   The watchdog bark occurs at the ExpireTime specified, and triggers the
   watchdog interrupt (if it has been enabled).
   The watchdog bite occurs at twice the ExpireTime specified, and
   triggers a SOC reset only if bit 12 of the debug_disable_vector OTP has been
   set.

   @param[in] ExpireTime  Bark time for the watchdog to expire in 0.1 second
                          intervals. Bite occurs after twice this time.
                          If zero is specified, the watchdog will be disabled.

   @return
   QAPI_OK -- If the watchdog was configured successfully. \n
   Negative value -- If there is an error.
*/
qapi_Status_t qapi_WDOG_Configure(uint8_t ExpireTime);

/**
   @brief Gets the current watchdog configuration.

   @return The configured ExpireTime of the watchdog in 0.1 second intervals or
           zero if the watchdog is disabled.
*/
uint8_t qapi_WDOG_GetConfig(void);

/**
   @brief Pets the watchdog, resetting its counters.
*/
void qapi_WDOG_Pet(void);

/**
   @brief Enables an AON IRQ.

   This function only enables the bark interrupt in the NAON block and does not
   affect the NVIC.

   @param[in] Enable  Flag indicating if the interrupt should be enabled (TRUE)
                      or disabled (FALSE).

   @return
   QAPI_OK -- If the watchdog was configured successfully. \n
   Negative value -- If there is an error.

*/
qapi_Status_t qapi_WDOG_EnableIRQ(qbool_t Enable);

/**
   @brief Provides the interrupt status of the watchdog.

   This function also clears the interrupt status bit after a read action.

   @return
   TRUE -- Watchdog bark interrupt has been triggered. \n
   FALSE -- Watchdog bark interrupt has not been triggered.
*/
qbool_t qapi_WDOG_GetIRQStatus(void);


/** @} */ /* end_addtogroup qapi_platform_wdog */

#endif

