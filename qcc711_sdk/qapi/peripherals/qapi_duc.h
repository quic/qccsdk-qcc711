/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_duc.h
    @brief DU comparator interface definition.
*/

/** @addtogroup qapi_peripherals_duc
    This module provides APIs to notify the application that battery voltage
    is below a specified threshold.
*/
 
#ifndef __QAPI_DUC_H__
#define __QAPI_DUC_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_duc
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of DU comparator threshold setting.
*/
typedef enum
{
    QAPI_DUC_THRESHOLD_1P8V_E,  /**< DU comparator threshold setting 1.8&nbsp;V. */
    QAPI_DUC_THRESHOLD_1P9V_E,  /**< DU comparator threshold setting 1.9&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P0V_E,  /**< DU comparator threshold setting 2.0&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P1V_E,  /**< DU comparator threshold setting 2.1&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P2V_E,  /**< DU comparator threshold setting 2.2&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P3V_E,  /**< DU comparator threshold setting 2.3&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P4V_E,  /**< DU comparator threshold setting 2.4&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P5V_E,  /**< DU comparator threshold setting 2.5&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P6V_E,  /**< DU comparator threshold setting 2.6&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P7V_E,  /**< DU comparator threshold setting 2.7&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P8V_E,  /**< DU comparator threshold setting 2.8&nbsp;V. */
    QAPI_DUC_THRESHOLD_2P9V_E,  /**< DU comparator threshold setting 2.9&nbsp;V. */
    QAPI_DUC_THRESHOLD_3P0V_E   /**< DU comparator threshold setting 3.0&nbsp;V. */
} qapi_DUC_Threshold_t;

/**
   @brief Prototype for a function called when the DU comparator is triggered.

   @param[in] UserParam  User-specified parameter provided when the callback is
                         registered.
*/
typedef void (*qapi_DUC_CB_t)(void *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Enable DU comparator.

   If battery voltage is below a specified threshold for a certain amount of time, DU
   comparator is triggered. A callback is registered in order to notify this situation
   has occured.

   @param[in] Threshold  DU comparator threshold setting.
   @param[in] Callback   Callback function that will be called when DU comparator is
                         triggered. If Callback is not NULL, DU comparator interrupt
                         will be enabled. Else DU comparator interrupt will not
                         be enabled.
   @param[in] UserParam  User-specified parameter for the callback function.
   
   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_DUC_Enable(qapi_DUC_Threshold_t Threshold, qapi_DUC_CB_t Callback, void* UserParam);

/**
   @brief Disable DU comparator.
*/
void qapi_DUC_Disable();

/**
   @brief Check whether the battery voltage is below the DU comparator threshold.

   Call this function after the DU comparator is enabled.

   @return
   TRUE -- Battery voltage is below the threshold.\n
   FALSE -- Battery voltage is not below the threshold or the DU Comparator
            is not enabled.
*/
qbool_t qapi_DUC_Is_Below_Threshold();

/** @} */ /* end_addtogroup qapi_peripherals_duc */

#endif

