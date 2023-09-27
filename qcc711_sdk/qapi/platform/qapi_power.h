/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_power.h
   @brief Power control APIs, types, and definitions.

   This module provides power related APIs and definitions. This covers voting
   for various system states, registering for shutdown callbacks, and other
   power related utility functions.

   In order to cast a vote, the user must first acquire a ballot via
   qapi_PWR_Acquire_Ballot(). This ballot can then be used with
   qapi_PWR_Vote_Local_State(). If qapi_PWR_Release_Ballot() is called, all
   oustanding votes for that vote are canceled (returned to their default
   state) and the ballot is then invalid.

   Note that casting a vote for a specific state does not mean this state will
   be entered. The module will consolidate all outstanding votes and choose the
   state accordingly. The state may also be affected by votes on other
   subsystems.

   If a module needs to perform any actions before and/or after the system
   enters the shutdown state, it can register its callback functions using
   qapi_PWR_Register_Shutdown_Callbacks(). These callbacks are called
   immediately before the shutdown state is entered and immediately after
   waking from deep sleep (when qapi_PWR_Initialize() is called). If multiple
   callbacks are registered, the priority passes to
   qapi_PWR_Register_Shutdown_Callbacks(), which determine the order they are
   called. Lower priority callbacks are called last before entering shutdown
   and first when exiting shutdown. If multiple callbacks have the same
   priority, they may be called in any order, although the order is always
   reversed between enter and exit.

   APIs and definitions are also provided to configure different clock sources.
   
   @note
   When setting the LFCLK source to LFXTAL, the callback mechanism can
   only be used after the timer module is initialized by qapi_TMR_Init(). The
   blocking mechanism can be used anywhere.

   Utility functions are also provided to initiate a software reset, to
   determine the reason for the last reset, and to configure interrupts from
   the AON hardware block.
*/

#ifndef __QAPI_POWER_H__
#define __QAPI_POWER_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_power
@{ */

#define QAPI_PWR_MAX_WAKE_TIME   (0xFFEFFFFF / 1000) /**< Maximum allowed wake up time for the QAPI power APIs. */
#define QAPI_PWR_NO_WAKE         ((uint32_t)-1)     /**< Indicates no wake time. */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/* Build time configurations for the QAPI PWR module. */
#define QAPI_PWR_MAX_BALLOTS                                            (32)   /**< Maximum number of ballots that can be simultaneously registered. */
#define QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT                     (0x80) /**< Default priority for shutdown callbacks that do not have to be called in a
                                                                                    specific order. */

/* Definitions for the address ranges of the RAM blocks that can be retained. */
#define QAPI_PWR_BTSS_RETAINED_RAM_BLOCK_0_START                        (0x20000000) /**< Start address of BTSS retained RAM block 0. */
#define QAPI_PWR_BTSS_RETAINED_RAM_BLOCK_0_END                          (0x20001FFF) /**< End address of BTSS retained RAM block 0. */
#define QAPI_PWR_BTSS_RETAINED_RAM_BLOCK_1_START                        (0x20002000) /**< Start address of BTSS retained RAM block 1. */
#define QAPI_PWR_BTSS_RETAINED_RAM_BLOCK_1_END                          (0x20003FFF) /**< End address of BTSS retained RAM block 1. */
#define QAPI_PWR_APSS_RETAINED_RAM_BLOCK_0_START                        (0x20010000) /**< Start address of APSS retained RAM block 0. */
#define QAPI_PWR_APSS_RETAINED_RAM_BLOCK_0_END                          (0x20011FFF) /**< End address of APSS retained RAM block 0. */
#define QAPI_PWR_APSS_RETAINED_RAM_BLOCK_1_START                        (0x20012000) /**< Start address of APSS retained RAM block 1. */
#define QAPI_PWR_APSS_RETAINED_RAM_BLOCK_1_END                          (0x20013FFF) /**< End address of APSS retained RAM block 1. */

/* Definitions of the AON interrupts. */
#define QAPI_PWR_AON_INT_HFXTAL_STABLE                                  (0)  /**< The 32MHz HFXTAL is stable. */
#define QAPI_PWR_AON_INT_HFXTAL_TIMEOUT                                 (1)  /**< The 32MHz HFXTAL failed to stabilize. */
#define QAPI_PWR_AON_INT_CFG_ERR                                        (2)  /**< A configuration error. This cannot be disabled. */
#define QAPI_PWR_AON_INT_PMU                                            (3)  /**< A PMU event. */
#define QAPI_PWR_AON_INT_PIO                                            (4)  /**< A PIO event. */
#define QAPI_PWR_AON_INT_MFB_SHORT                                      (5)  /**< Short pulse on the MFB was detected. */
#define QAPI_PWR_AON_INT_MFB_EDGE                                       (6)  /**< An edge detected on the MFB. */
#define QAPI_PWR_AON_INT_WAKEUP_REQUEST                                 (7)  /**< A wakeup signal from another subsystem. */
#define QAPI_PWR_AON_INT_GTMR                                           (8)  /**< Global timer events. */
#define QAPI_PWR_AON_INT_BROWNOUT                                       (9)  /**< Brownout events. */
#define QAPI_PWR_AON_INT_DISPLAY                                        (10) /**< A display voltage event. */
#define QAPI_PWR_AON_INT_VDIO                                           (11) /**< An RRAM voltage event. */
#define QAPI_PWR_AON_INT_CETMR                                          (12) /**< CE timer events. */
#define QAPI_PWR_AON_INT_COUNT                                          (13) /**< Number of AON interrupts available. */
/** Minimum voltage the VLP LDO can be set to. */
#define QAPI_PWR_VLP_VOLTAGE_MIN                                        (700)
/** Maximum voltage the VLP LDO can be set to. */
#define QAPI_PWR_VLP_VOLTAGE_MAX                                        (900)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Type representing a ballot can be used for voting for power states. A ballot
    acquired via qapi_PWR_Acquire_Ballot() can be used with any applicable power
    QAPI. */
typedef uint8_t qapi_PWR_Ballot_t;

/** Type representing the count that is used for determining what has voted for
    a particular power mode. */
typedef uint32_t qapi_PWR_Election_t;

/** Enumeration of module or subsystem states, both for the current subsystem
    and for other modules in the system. */
typedef enum
{
   QAPI_PWR_STATE_SHUTDOWN_E, /**< Module is in the shutdown state.  In the shutdown state, the module is
                                   held in reset and may be power collapsed. */
   QAPI_PWR_STATE_ACTIVE_E    /**< Module is in the active state. */
} qapi_PWR_State_t;

/** Enumeration of modules controlled by the power API. */
typedef enum
{
   QAPI_PWR_MODULE_BTSS_E,       /**< Bluetooth subsystem. */
   QAPI_PWR_MODULE_APSS_E,       /**< Application subsystem. */
   QAPI_PWR_MODULE_ROT_E,        /**< Root of trust. */
   QAPI_PWR_MODULE_NVM_E,        /**< NVM. */
   QAPI_PWR_MODULE_PERIPHERAL_E, /**< Peripherals. */
   QAPI_PWR_MODULE_GPIO_E        /**< GPIO. */
} qapi_PWR_Module_t;

/** Enumeration of the LF CLK sources. */
typedef enum
{
   QAPI_PWR_LFCLK_SOURCE_SOSC,   /**< Internal low power oscillator. */
   QAPI_PWR_LFCLK_SOURCE_LFXTAL, /**< Crystal oscillator. */
   QAPI_PWR_LFCLK_SOURCE_GPIO    /**< External GPIO clock. */
} qapi_PWR_LFCLK_Source_t;

/** Enumeration of reset types. */
typedef enum
{
   QAPI_PWR_RESET_TYPE_SUBSYSTEM_RESET_E, /**< Reset just the local subsystem. */
   QAPI_PWR_RESET_TYPE_SOC_COLD_RESET_E   /**< Cold reset the SOC. */
} qapi_PWR_Reset_Type_t;

/** Enumeration of reset reasons. */
typedef enum
{
   QAPI_PWR_RESET_REASON_POWER_ON_RESET_E,           /**< Power on reset. */
   QAPI_PWR_RESET_REASON_COLD_RESET_VDIO_EVENT_E,    /**< Cold reset caused VDIO RRAM Voltage Event Detection. */
   QAPI_PWR_RESET_REASON_COLD_RESET_SOFTWARE_E,      /**< Cold reset caused by software. */
   QAPI_PWR_RESET_REASON_COLD_RESET_BROWNOUT_E,      /**< Cold reset caused by the brownout circuit. */
   QAPI_PWR_RESET_REASON_COLD_RESET_MFB_E,           /**< Cold reset caused by a long press of the MFB. */
   QAPI_PWR_RESET_REASON_COLD_RESET_ROT_WATCHDOG_E,  /**< Cold reset caused by the ROT watchdog. */
   QAPI_PWR_RESET_REASON_COLD_RESET_BTSS_WATCHDOG_E, /**< Cold reset caused by the BTSS watchdog. */
   QAPI_PWR_RESET_REASON_COLD_RESET_APSS_WATCHDOG_E, /**< Cold reset caused by the APSS watchdog. */
   QAPI_PWR_RESET_REASON_WARM_RESET_SOFTWARE_E,      /**< Warm reset caused by software */
   QAPI_PWR_RESET_REASON_WARM_RESET_ROT_WATCHDOG_E,  /**< Warm reset caused by the ROT watchdog. */
   QAPI_PWR_RESET_REASON_WARM_RESET_BTSS_WATCHDOG_E, /**< Warm reset caused by the BTSS watchdog. */
   QAPI_PWR_RESET_REASON_WARM_RESET_APSS_WATCHDOG_E, /**< Warm reset caused by the APSS watchdog. */
   QAPI_PWR_RESET_REASON_SUBSYSTEM_RESET_SOFTWARE_E  /**< Subsystem reset caused by software. */
} qapi_PWR_Reset_Reason_t;

/** Enumeration of MFP edge detect types. */
typedef enum
{
   QAPI_PWR_MFP_EDGE_DETECT_NONE_E,     /**< Disable detection interrupt for APSS. */
   QAPI_PWR_MFP_EDGE_DETECT_POS_E,      /**< Rising-edge detection interrupt for APSS. */
   QAPI_PWR_MFP_EDGE_DETECT_NEG_E,      /**< Falling-edge detection interrupt for APSS. */
   QAPI_PWR_MFP_EDGE_DETECT_BOTH_E      /**< Dual-edge detection interrupt for APSS. */
} qapi_PWR_Mfp_Edge_Detect_type_t;

/** Structure for the MFP configuration. */
typedef struct qapi_PWR_MFP_Config_s
{
    qbool_t LongPressEnable;                        /**< Enable or disable a long press cold reset for APSS. */
    qapi_PWR_Mfp_Edge_Detect_type_t EdgeDetectType; /**< Edge detect types for APSS. */
} qapi_PWR_MFP_Config_t;

/** Structure for returning internal information on power votes. */
typedef struct qapi_PWR_Status_s
{
   qbool_t             ShutdownInvoked;                 /**< Flag indicating the power module actually invoked. */
   uint8_t             VMA_Count;                       /**< Count of how many times the LDO has been requested. */
   uint8_t             LFCLK_Count;                     /**< Count of how many times the 32K XTAL has been requested. */
   uint8_t             HFCLK_Count;                     /**< Count of how many times the 32M XTAL has been requested. */
   uint32_t            WakeTime[QAPI_PWR_MAX_BALLOTS];  /**< List of wake times corresponding to each ballot. */
   qapi_PWR_Election_t WakeValid;                       /**< Determines if the wake time for the corresponding ballot is valid. */
   qapi_PWR_Election_t ElectLocal;                      /**< Elections for the APSS module state. */
   uint32_t            SOCStatus;                       /**< Hardware SOC status. */
} qapi_PWR_Status_t;

/**
   @brief Prototype for a function called before the subsystem enters the
          shutdown state.

   This function is called with interrupts disabled and the interrupts
   must not be re-enabled.

   @param[in] UserParam  User-specified parameter provided when the callback is
                         registered.

   @return
   TRUE -- If shutdown can be entered. \n
   FALSE -- If shutdown needs to be aborted.
*/
typedef qbool_t (*qapi_PWR_Shutdown_CB_t)(void *UserParam);

/**
   @brief Prototype for a function called when shutdown wakes from shutdown or
          a shutdown is aborted.

   This function is called with interrupts disabled. The interrupts must not
   be re-enabled.

   @param[in] ShutdownAborted  Flag indicating if this function is called
                               because a shutdown was aborted (TRUE) or
                               because the subsystem woke from shutdown (FALSE).
   @param[in] UserParam        Pointer to the user-specified parameter provided
                               when the callback is registered.
*/
typedef void (*qapi_PWR_Wakeup_CB_t)(qbool_t ShutdownAborted, void *UserParam);

/**
   @brief Prototype for a function called when an AON interrupt occurs.

   @param[in] Interrupt  An interrupt that the callback should handle
                         as defined by QAPI_PWR_AON_INTERRUPT_TYPE_*.
                         Only one bit is set.
   @param[in] UserParam  Pointer to the user-specified parameter provided
                         when the callback is registered.
*/
typedef void (*qapi_PWR_Aon_Int_Handler_CB_t)(uint32_t Interrupt, void *UserParam);

/**
   @brief Callback indicating the LFXTAL has been enabled.

   @param[in] Result     Result of the LFXTAL start operation. QAPI_OK if the
                         process succeeded or a negative value if there was an
                         error.
   @param[in] UserParam  Pointer to the user-specified parameter provided when
                         the callback is registered.
*/
typedef void (*qapi_PWR_LFXTAL_Enabled_CB_t)(qapi_Status_t Result, void *UserParam);


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the power module.

   This function is expected to be called first in the boot process. It
   will detect if the boot is a warm or cold boot, and initialize the
   subsystem accordingly.

   For a cold boot, the retained RAM region is initialized. For warm boot,
   all registered wakeup functions are called to restore the state of the
   subsystem.

   @param[out] IsColdBoot  Set to TRUE for a cold boot, or FALSE for a
                           warm boot.

   @return
   QAPI_OK -- If initialization was successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_PWR_Initialize(qbool_t *IsColdBoot);

/**
   @brief Indicates the system is idle.

   This function evaluates the sleep votes made using
   qapi_PWR_Vote_Local_State(), and enters the appropriate sleep state. When
   entering the shutdown state, the times specified to
   qapi_PWR_Vote_Local_State() are combined with SleepTime to set a wakeup
   timer for the subsystem.

   @param[in] WakeTime  Maximum time in milliseconds for the subsystem to
                        sleep. Use #QAPI_PWR_NO_WAKE if this time should not
                        be used to set a wakeup. If WakeTime is greater than
                        #QAPI_PWR_MAX_WAKE_TIME, #QAPI_PWR_MAX_WAKE_TIME is
                        used instead.
*/
void qapi_PWR_System_Idle(uint32_t WakeTime);

/**
   @brief Attempts to turn off the local subsystem.

   This function will imidiately try to turn off the local subsystem,
   regardless of any outstanding votes.  This process is similar to entering
   the shutdown state except no memory will be retained and the next time
   the subsystem starts, it will behave as a cold boot.

   This function is intended to enter the lowest power state when only the APSS is
   being used, and should not be used when the BTSS or TME are active.

   This function does not return unless another subsytem is active.

   @param[in] WakeTime  Time in milliseconds for the subsystem to sleep. Use
                        #QAPI_PWR_NO_WAKE to not wake on a timer. If WakeTime
                        is greater than #QAPI_PWR_MAX_WAKE_TIME,
                        #QAPI_PWR_MAX_WAKE_TIME is used instead.
*/
void qapi_PWR_Subsystem_Off(uint32_t WakeTime);

/**
   @brief Registers callback functions to be called before the subsystem
          enters the shutdown state and after it resumes.

   The specified priority is used to determine the calling order of
   functions when entering or exiting the shutdown state. When entering
   shutdown, the highest priority function is called first. On wakeup,
   the function calling order is reversed (lowest priority first).

   @param[in] ShutdownCB  Function called before the subsystem
                          enters the shutdown state.
   @param[in] WakeupCB    Function called after the subsystem exits
                          sleep.
   @param[in] Priority    Used for determining the calling order of
                          functions when entering or exiting the shutdown state.
                          #QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT is
                          used if the calling order of the functions does not
                          matter.
   @param[in] UserParam   User-specified parameter for the callback functions.

   @return
   Handle for the registered callback functions. This can be used to unregister the callback.
*/
void *qapi_PWR_Register_Shutdown_Callbacks(qapi_PWR_Shutdown_CB_t ShutdownCB, qapi_PWR_Wakeup_CB_t WakeupCB, uint8_t Priority, void *UserParam);

/**
   @brief Unregisters callbacks registered with
          qapi_PWR_Register_Shutdown_Callbacks().

   @param[in] CallbackHandle  Handle for the registered callbacks.

   @return
   Newly acquired ballot. \n
   Zero -- If ballot acquisition failed.
*/
void qapi_PWR_Unregister_Callback(void *CallbackHandle);

/**
   @brief Acquires a ballot that can be used with the power voting APIs.

   @return
   Newly acquired ballot. \n
   Zero -- If ballot acquisition failed.
*/
qapi_PWR_Ballot_t qapi_PWR_Acquire_Ballot(void);

/**
   @brief Releases a ballot and cancels all votes associated with it.

   @param[in] Ballot  Ballot to release.
*/
void qapi_PWR_Release_Ballot(qapi_PWR_Ballot_t Ballot);

/**
   @brief Votes for the sleep state of the local subsystem.

   This state is entered the next time a WFI is executed. If the vote is
   QAPI_PWR_STATE_SHUTDOWN_E, the WakeValid and WakeTime indicate when the
   caller needs the subsystem to wake.

   @param[in] Ballot    Ballot acquired by a call to qapi_PWR_Acquire_Ballot().
   @param[in] Vote      State to vote.
   @param[in] WakeTime  Time that the voter requires the system to wake in
                        milliseconds relative to the current time. Use
                        #QAPI_PWR_NO_WAKE if this time is not to be used to set
                        a wakeup. If SleepTime is greater than
                        #QAPI_PWR_MAX_WAKE_TIME, #QAPI_PWR_MAX_WAKE_TIME is
                        used instead.
   @return
   QAPI_OK -- If the vote was cast successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_PWR_Vote_Local_State(qapi_PWR_Ballot_t Ballot, qapi_PWR_State_t Vote, uint32_t WakeTime);

/**
   @brief Sets the state of another subsystem.

   This API is used to set state of a remote subsystem. This sets the state of
   the hardware vote for the subystem. The actual state of the subsystem may
   be different.

   @param[in] Module  Module whose state is to be set.
   @param[in] State   State to select.

   @return
   QAPI_OK -- If the vote was cast successfully.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_PWR_Set_Module_State(qapi_PWR_Module_t Module, qapi_PWR_State_t State);

/**
   @brief Reads the state of one of the subsystems or modules.

   @param[in] Module  Module state to read.

   @return
   State of the specified module.
*/
qapi_PWR_State_t qapi_PWR_Get_Module_State(qapi_PWR_Module_t Module);

/**
   @brief Requests the VMA LDO.

   This function tracks the number of outstanding requests for the LDO and
   only disables the LDO when the number of calls with Enable=false matches the
   number of calls with Enable=true.

   This function blocks until the LDO has stabalized.

   @param[in] Enable  Flag indicating if the VMA LDO should be enabled (true),
                      or disabled (false).
*/
void qapi_PWR_Set_VMA_LDO(qbool_t Enable);

/**
   @brief Reads the configuration of the HFCLK Source.

   @return
   TRUE -- If the VMA LDO is enabled. \n
   FALSE -- If the VMA LDO is not enabled.
*/
qbool_t qapi_PWR_Get_VMA_LDO(void);

/**
   @brief Sets the voltage of the low power digital LDO.

   @param[in] Voltage  Requested voltage of the LDO in millivolts. The actual
                       value programmed is rounded up to the next 12.5 mV
                       increment. See QAPI_PWR_VLP_LDO_VOLTAGE_xxx for the 
                       valid range of values.

   @return True if the voltage was set or false if the specified voltage was
           invalid.
*/
qbool_t qapi_PWR_Set_VLP_Voltage(uint32_t Voltage);

/**
   @brief Reads the configured voltage of the low power digital LDO.

   @return The voltage of the LDO in millivolts (rounded down).
*/
uint32_t qapi_PWR_Get_VLP_Voltage(void);

/**
   @brief Sets the source of the 32 MHz HFCLK. The VMA LDO is automatically
          enabled if required.

   This function sets the hardware vote for the source of the HFCLK. The actual
   source hardware selects may be different.

   @param[in] Accurate  Flag indicating if an accurate HFCLK is required (TRUE),
                        or if an inaccurate low power HFCLK can be used (FALSE).
*/
void qapi_PWR_Set_HFCLK_Source(qbool_t Accurate);

/**
   @brief Reads the configuration of the HFCLK Source.

   @return
   TRUE -- If the HFCLK is configured with an accurate clock source. \n
   FALSE -- If using a low power source.
*/
qbool_t qapi_PWR_Get_HFCLK_Source(void);

/**
   @brief Sets the source of the GTMR clock.

   This function sets the hardware vote for the source of the GTMR clock and
   the actual source hardware selects may be different.

   @param[in] HFCLK  Flag indicating if the 32MHz HFCLK source is needed (TRUE)
                     or if the the 32KHz LFCLK can be used (FALSE).
*/
void qapi_PWR_Set_TCLK_Source(qbool_t HFCLK);

/**
   @brief Reads the configuration of the GTMR clock.

   @return
   TRUE -- If the GTMR uses the HFCLK. \n
   FALSE -- If the GTMR uses the LFCLK.
*/
qbool_t qapi_PWR_Get_TCLK_Source(void);

/**
   @brief Configures the source of the LFCLK.

   @note
   The callback mechanism can only be used after the timer module is
   initialized by qapi_TMR_Init(). The blocking mechanism can be used anywhere.

   @param[in] Source       Source for the LFCLK.
   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp(). This
                           parameter is only used if Source is
                           QAPI_PWR_LFCLK_SOURCE_LFXTAL.
   @param[in] Callback     Function that is called when the LFXTAL has been
                           enabled. If NULL, this function blocks until the
                           LFXTAL is enabled. This parameter is only used if
                           Source is QAPI_PWR_LFCLK_SOURCE_LFXTAL.
   @param[in] UserParam    User-specified parameter for the callback functions.

   @return
   QAPI_OK -- If the clock was configured successfully.\n
   Negative value - If there was an error.
*/
qapi_Status_t qapi_PWR_Set_LFCLK_Source(qapi_PWR_LFCLK_Source_t Source, int32_t Temperature, qapi_PWR_LFXTAL_Enabled_CB_t Callback, void *UserParam);

/**
   @brief Reads the configuration of the LF clock source.

   @return
   The current configuration of the LF clock source.
*/
qapi_PWR_LFCLK_Source_t qapi_PWR_Get_LFCLK_Source(void);

/**
   @brief Calibrate the 32K XTAL.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
*/
void qapi_PWR_Calibrate_LFXTAL(int32_t Temperature);

/**
   @brief Enable the SMPS.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
   @param[in] Voltage      Voltage reading from qapi_SENS_Get_Voltage().
*/
void qapi_PWR_Enable_SMPS(int32_t Temperature, uint32_t Voltage);

/**
   @brief Calibrate the SMPS.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
   @param[in] Voltage      Voltage reading from qapi_SENS_Get_Voltage().
*/
void qapi_PWR_Calibrate_SMPS(int32_t Temperature, uint32_t Voltage);

/**
   @brief Initiates a reset.

   @param[in] ResetType  Type of reset to initiate.
*/
void qapi_PWR_Reset(qapi_PWR_Reset_Type_t ResetType);

/**
   @brief Gets the reason for the last reset of the subsystem.

   @return
   The reset reason.
*/
qapi_PWR_Reset_Reason_t qapi_PWR_Get_Reset_Reason(void);

/**
   @brief Determines if the last boot was a cold boot or a resume from shutdown.

   This API can be called before qapi_PWR_Initialize() if required.

   @return
   TRUE - If the last boot was a cold boot. \n
   FALSE - If the last boot was a warm boot.
*/
qbool_t qapi_PWR_Is_Cold_Boot(void);

/**
   @brief Enables and registers a callback for an AON interrupt.

   Note that only one callback can be registered for a given interrupt at a
   time.

   @param[in] Interrupt    Interrupt to register a callback for as defined by
                           QAPI_PWR_AON_INT_*.
   @param[in] InterruptCB  Function that will be called when the interrupt
                           fires.
   @param[in] UserParam    User-specified parameter for the callback functions.

   @return
   QAPI_OK -- If the interrupt enable was changed successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_PWR_Register_AON_Interrupt(uint32_t Interrupt, qapi_PWR_Aon_Int_Handler_CB_t InterruptCB, void *UserParam);

/**
   @brief Disables and unregisters a callback for an AON interrupt.

   @param[in] Interrupt  Interrupt to disable as defined by QAPI_PWR_AON_INT_*.

   @return
   TRUE -- If an interrupt was previously registered. \n
   FALSE -- If an interrupt was not previously registered.
*/
qbool_t qapi_PWR_Unregister_AON_Interrupt(uint32_t Interrupt);

/**
   @brief Determines if an AON interrupt is pending.

   @param[in] Interrupt  Interrupt to check as defined by QAPI_PWR_AON_INT_*.

   @return
   TRUE -- If the interrupt is pending. \n
   FALSE -- If the interrupt is not pending.
*/
qbool_t qapi_PWR_Get_AON_Int_Pending(uint32_t Interrupt);

/**
   @brief Clears a pending AON interrupt.

   @param[in] Interrupt  Interrupt to clear as defined by QAPI_PWR_AON_INT_*.

   @return
   QAPI_OK -- If the interrupt enable was changed successfully. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_PWR_Clear_AON_Int_Pending(uint32_t Interrupt);

/** - see "either"
   @brief Set the MFP configuration.

   Edge detection description:
   The edge detection is sampled using the internal slow clock, the state is
   debounced and requires two consecutive clocks to register.
   If both (either) edges are selected there is no way to know which edge
   caused the MFP edge interrupt.
   If a long press is selected, edge detection is disabled to avoid spurious
   interrupts.
   Long press description: Asserting the MFP port high continuously for a period of 
   longer than 9 seconds and then releasing, triggers a cold reset event. If the
   assertion is longer than 32 seconds (1024 slow clock cycles) then the 
   internal-timer wraps; because of this, a high-duration before release (of between
   approximately 32 and 40 seconds) does not cause a reset event.
   Asserting the PMU port high continuously for a period of 8 seconds or
   shorter does not trigger a cold reset.
   Periods between 8 and 9 seconds are undefined; this is due to the natural
   variation of the internal clock.

   @param[in] Config  Structure of MFP configuration data.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_PWR_Set_MFP(qapi_PWR_MFP_Config_t *Config);

/**
   @brief Get the MFP current configuration.

   @param[in] Config  Structure of MFP configuration data.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_PWR_Get_MFP(qapi_PWR_MFP_Config_t *Config);

/**
   @brief Get the internal status.

   @param[out] Status  Structure to populate with the internal status.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_PWR_Get_Status(qapi_PWR_Status_t *Status);

/** @} */ /* end_addtogroup qapi_platform_power */

#endif

