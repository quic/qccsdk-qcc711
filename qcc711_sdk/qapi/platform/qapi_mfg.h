/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_MFG_H__
#define __QAPI_MFG_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/** @addtogroup qapi_platform_mfg
@{ */

/* Definitions for the low frequency clock's course trim. */
#define QAPI_MFG_MIN_LFCLK_COARSE_TRIM          (0)   /**< Minimum coarse trim for LF clock. */
#define QAPI_MFG_MAX_LFCLK_COARSE_TRIM          (511) /**< Maximum coarse trim for LF clock. */


/* Suggested initial trim values for following capacitive
   loads. */
#define QAPI_MFG_INIT_LFCLK_COARSE_TRIM_4PF     (320) /**< Recommended initial trim value for crystal matching load cap (4). */
#define QAPI_MFG_INIT_LFCLK_COARSE_TRIM_6PF     (370) /**< Recommended initial trim value for crystal matching load cap (6). */
#define QAPI_MFG_INIT_LFCLK_COARSE_TRIM_7PF     (400) /**< Recommended initial trim value for crystal matching load cap (7). */
#define QAPI_MFG_INIT_LFCLK_COARSE_TRIM_9PF     (450) /**< Recommended initial trim value for crystal matching load cap (9). */
#define QAPI_MFG_INIT_LFCLK_COARSE_TRIM_12_5PF  (50)  /**< Recommended initial trim value for crystal matching load cap (12.5). */


/* Definitions for the high frequency clock's course trim. */
#define QAPI_MFG_MIN_HFCLK_COURSE_TRIM          (0)  /**< Minimum coarse trim for HF clock. */
#define QAPI_MFG_MAX_HFCLK_COURSE_TRIM          (31) /**< Maximum coarse trim for HF clock. */


/* Definitions for the low frequency clock's fine trim. */
#define QAPI_MFG_MIN_HFCLK_FINE_TRIM            (-16) /**< Minimum fine trim for HF clock. */
#define QAPI_MFG_MAX_HFCLK_FINE_TRIM            (15)  /**< Maximum fine trim for HF clock. */


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/* Enumeration of clock type. */
typedef enum
{
   QAPI_MFG_CLOCK_LFCLK_E, /**< Low frequency clock (32 KHz). */
   QAPI_MFG_CLOCK_HFCLK_E  /**< High frequency clock (32 MHz). */
} qapi_MFG_Clock_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Enable/disables clock output.

   If QAPI_MFG_CLOCK_LFCLK_E is specified for the Clock parameter, and
   the output is disabled, then QAPI_GPIO_ID13_E is set to input (no pull).

   If QAPI_MFG_CLOCK_HFCLK_E is specified for the Clock parameter, and
   the output is disabled, then QAPI_GPIO_ID11_E is set to input (no pull).

   @param[in] Clock       Identifies the clock.
   @param[in] Enable      Enables/disables clock output.

   @return
   QAPI_OK -- If successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_MFG_Enable_CLK_Output(qapi_MFG_Clock_t Clock, qbool_t Enable);

/**
   @brief Updates the coarse trim in real time for the specified clock.

   To store the trim persistently, the qapi_MFG_Store_CLK_Trim() function
   may be used.

   @param[in] Clock       Identifies the clock.
   @param[in] Trim        Specifies the coarse trim.

   @return
   QAPI_OK -- If successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_MFG_Update_CLK_Coarse_Trim(qapi_MFG_Clock_t Clock, uint16_t Trim);

/**
   @brief Updates the fine trim in real time for the specified clock.

   QAPI_MFG_CLOCK_LFCLK_E may not be specified for the Clock parameter
   since the fine trim for the low frequency clock is not supported.

   To store the trim persistently, the qapi_MFG_Store_CLK_Trim() function
   may be used.

   @param[in] Clock Identifies the clock.

   @param[in] Trim Specifies the fine trim.

   @return
   QAPI_OK -- If successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_MFG_Update_CLK_Fine_Trim(qapi_MFG_Clock_t Clock, int16_t Trim);

/**
   @brief Persistently stores the specified clock trim.

   The FineTrim parameter is ignored if QAPI_MFG_CLOCK_LFCLK_E is
   specified for the Clock parameter, because fine trim is not supported
   by the low frequency clock.

   @param[in] Clock       Identifies the clock.
   @param[in] CoarseTrim  Specifies the coarse trim.
   @param[in] FineTrim    Specifies the fine trim.

   @return
   QAPI_OK -- If successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_MFG_Store_CLK_Trim(qapi_MFG_Clock_t Clock, uint16_t CoarseTrim, int16_t FineTrim);

/** @} */ /* end_addtogroup qapi_platform_mfg */

#endif

