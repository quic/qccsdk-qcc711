/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_timer.h
   @brief Timer services interface definition.
*/

/** @addtogroup qapi_peripherals_timer

   This module provides a timer for driver and application use.

   qapi_TMR_Init() should be called to initialize the module before any other
   timer functions.
   
   @note
   If the timer module is to be used across the shutdown state, the HFCLK source
   must be switched to HFXTAL, before qapi_TMR_Init() is called.

   There are twelve different comparators that can be independently configured
   and used. The timer comparators are microsecond resolution comparators that
   can be programmed to match and generate interrupts at a future time value.

   To use timer comparators, qapi_TMR_Comp_Init() must be called first to
   take a free comparator and register a user callback function. qapi_TMR_Comp_Start() 
   can then be called to start the comparator and set the
   compare value to be matched at a future time. When a comparator matches, the
   user registered callback functions are called directly from the timer
   IRQ handle. qapi_TMR_Comp_Stop() is called to stop the comparator. If the
   timer comparator is not needed anymore, call qapi_TMR_Comp_Deinit()
   to free the comparator for other use.

   Timers can also be initialized as deferable. Deferable timers function the
   same as normal timers when the system is active but will not wake the system
   from shutdown.  This can be useful to signal processes that need to occur
   periodically but aren't critical enough to wake the system from shutdown.

   All user registered timer callback functions should do minimal processing.
 */
 
#ifndef __QAPI_TIMER_H__
#define __QAPI_TIMER_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_timer
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QAPI_TMR_ERROR_COMP_IMPROPER_STATE __QAPI_ERROR(QAPI_MOD_TMR, 1) /**< Comparator is in improper state. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of the comparator information type.
*/
typedef enum
{
    QAPI_TMR_COMP_INFO_ABS_EXPIRY_E, /**< The comparator absolute expiry value. */
    QAPI_TMR_COMP_INFO_DURATION_E,   /**< The total duration of the comparator. */
    QAPI_TMR_COMP_INFO_REMAINING_E   /**< The remaining duration of the comparator. */
} qapi_TMR_Comp_Info_t;

/**
   Type representing the timer comparator instance.
*/
typedef uint8_t qapi_TMR_Comp_Instance_t;

/**
   @brief Prototype for a function called when the timer comparator expires.

   This function is called directly from the timer ISR. Users should do minimal
   processing in this function.

   @param[in] UserParam  User-specified parameter provided when the callback
                         is registered.
*/
typedef void (*qapi_TMR_Comp_CB_t)(void *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize timer module.

   This function should be called before any other timer functions.

   @note
   If the timer module is to be used across the shutdown state, the HFCLK source
   must be switched to HFXTAL, before this function is called.

   @return
   QAPI_OK -- The timer module is initialized successfully. \n
   QAPI_ERR_NO_RESOURCE -- Resource allocation error.
*/
qapi_Status_t qapi_TMR_Init();

/**
   @brief Get the current timer value.

   @return
   Current timer value in microseconds.
*/
uint64_t qapi_TMR_Get_Current_Time();

/**
   @brief Delay for some time in microseconds.

   It will loop here until the delayed time expires.

   @param[in] UsDelay  The delay time in microseconds.
*/
void qapi_TMR_Delay_Us(uint32_t UsDelay);

/**
   @brief Initialize a comparator.

   This function should be called before starting a comparator. It takes a
   free comparator and registers a user callback function for the comparator.

   @param[out] Comp        Pointer to return the comparator instance.
   @param[in]  CompCB      The callback function when timer comparator expires.
   @param[in]  UserParam   User specified parameter for callback function.
   @param[in]  Deferrable  Determines if the timer should be deferrable.  If
                           true, the timer will not wake APSS from shutdown 
                           when it expires.

   @return
   QAPI_OK -- The comparator is initialized successfully. \n
   QAPI_ERROR -- Timer module is not initialized yet. \n
   QAPI_ERR_INVALID_PARAM -- One or more parameters are invalid. \n
   QAPI_ERR_NO_MEMORY -- Memory allocation error. \n
   QAPI_ERR_NO_RESOURCE -- There is no free comparator.
*/
qapi_Status_t qapi_TMR_Comp_Init(qapi_TMR_Comp_Instance_t *Comp, qapi_TMR_Comp_CB_t CompCB, void *UserParam, qbool_t Deferrable);

/**
   @brief Deinitialize a comparator.

   This function stops the comparator and unregisters the user callback. It should
   be called to free the comparator for other usage when it is not needed anymore.

   @param[in] Comp  Specify a comparator to free.

   @return
   QAPI_OK -- The comparator is deinitialized successfully. \n
   QAPI_ERR_INVALID_PARAM -- One or more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Comp_Deinit(qapi_TMR_Comp_Instance_t Comp);

/**
   @brief Start a comparator to expire after a specified period.

   @param[in] Comp     Specify a comparator to start.
   @param[in] Timeout  The timeout value in microseconds.
   @param[in] Repeat   Repeat the comparator after the comparator expires, or not.
                       TRUE: repeat the comparator, FALSE: run only once.

   @return
   QAPI_OK -- The comparator started successfully. \n
   QAPI_ERR_INVALID_PARAM -- One or more parameters are invalid. \n
   QAPI_ERR_NOT_SUPPORTED -- Timeout value is too small to be supported. \n
   QAPI_TMR_ERROR_COMP_IMPROPER_STATE -- The comparator is in an improper state.
*/
qapi_Status_t qapi_TMR_Comp_Start(qapi_TMR_Comp_Instance_t Comp, uint64_t Timeout, qbool_t Repeat);

/**
   @brief Stop a comparator.

   @param[in] Comp  Specify a comparator to stop.

   @return
   QAPI_OK -- The comparator is stopped successfully. \n
   QAPI_ERR_INVALID_PARAM -- One or more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Comp_Stop(qapi_TMR_Comp_Instance_t Comp);

/**
   @brief Get comparator information.

   @param[in]  Comp  Specify a comparator.
   @param[in]  Info  Specify the type of information needed from the comparator.
   @param[out] Data  Data associated with the information.

   @return
   QAPI_OK -- The comparator information is obtained successfully. \n
   QAPI_ERROR -- Get comparator information failed. \n
   QAPI_ERR_INVALID_PARAM -- One or more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Get_Comp_Info(qapi_TMR_Comp_Instance_t Comp, qapi_TMR_Comp_Info_t Info, uint64_t *Data);

/** @} */ /* end_addtogroup qapi_peripherals_timer */

#endif

