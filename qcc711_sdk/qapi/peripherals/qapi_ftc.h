/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_ftc.h
   @brief Flexible Timer/Counter Interface (FTC)

   FTC is similar to PWM (Pulse Width Modulation). It used to
   control analog elements in the system using a digital signal. Common examples
   of such elements are LEDs and vibrators. The difference between FTC and PWM,
   is that in addition to clock counting, FTC also supports input signal edge
   counting. The FTC module has four blocks, where each block has three channels.

   Typical usage:
   qapi_FTC_Inital()            - Set the FTC configuration.
   qapi_FTC_Uninitialize()      - Clear the FTC configuration.
   qapi_FTC_Enable()            - Start/stop the FTC function.
   qapi_FTC_EnableInterrupt()   - Register the FTC interrupt when the counter
                                  overflows.
   qapi_FTC_DisableInterrupt()  - Unregister the FTC interrupt.
*/

/** @addtogroup qapi_peripherals_ftc
   The FTC module provides similar functionality to pulse width modulation (PWM).
   It controls analog system elements using a digital signal. Common examples
   of these elements are light-emitting diodes (LEDs) and vibrators. The difference
   between flexible timer and counter (FTC) and PWM, is that 
   in addition to clock counting, FTC also supports input signal edge counting.
   The FTC module has four blocks; where each block has three channels.
*/

#ifndef __QAPI_FTC_H__
#define __QAPI_FTC_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qapi_status.h"

/** @addtogroup qapi_peripherals_ftc
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
/**
   @brief ID to identify an FTC instance.
*/
typedef enum
{
  QAPI_FTC_INSTANCE_0_E,        /**< Hardware instance 0 16&nbsp;Bits. */
  QAPI_FTC_INSTANCE_1_E,        /**< Hardware instance 1 16&nbsp;Bits. */
  QAPI_FTC_INSTANCE_2_E,        /**< Hardware instance 2 16&nbsp;Bits. */
  QAPI_FTC_INSTANCE_3_E,        /**< Hardware instance 3 16&nbsp;Bits. */
  QAPI_FTC_INSTANCE_CASCADED_E  /**< Hardware instance 0+1 32&nbsp;Bits. */
} qapi_FTC_Instance_t;

/**
   @brief Each FTC instance has 3 channels.
*/
typedef enum
{
  QAPI_FTC_CHANNEL_0_E,     /**< Channel 0. */
  QAPI_FTC_CHANNEL_1_E,     /**< Channel 1. */
  QAPI_FTC_CHANNEL_2_E,     /**< Channel 2. */
  QAPI_FTC_CHANNEL_MAX_E    /**< Channel Max. */
} qapi_FTC_Channel_t;

/**
   @brief There are 4 physical inputs to the FTC module.
*/
typedef enum
{
  QAPI_FTC_INPUT0_E,    /**< Input 0. */
  QAPI_FTC_INPUT1_E,    /**< Input 1. */
  QAPI_FTC_INPUT2_E,    /**< Input 2. */
  QAPI_FTC_INPUT3_E     /**< Input 3. */
} qapi_FTC_Input_t;

/**
   @brief Clock source to be used for FTC filter.
*/
typedef enum
{
  QAPI_FTC_FILTER_CLOCK_DEFAULT_E,  /**< CLK_FTC default clk. */
  QAPI_FTC_FILTER_CLOCK_PSC_E       /**< CLK_PSC pre-scaler clk. */
} qapi_FTC_Filter_Clock_Source_t;

/**
   @brief Divider to be used for the sampling filter clock.
*/
typedef enum
{
  QAPI_FTC_FILTER_CLOCK_DIVIDE_BY2_E,   /**< Divide by 2. */
  QAPI_FTC_FILTER_CLOCK_DIVIDE_BY4_E,   /**< Divide by 4. */
  QAPI_FTC_FILTER_CLOCK_DIVIDE_BY8_E,   /**< Divide by 8. */
  QAPI_FTC_FILTER_CLOCK_NO_DIVIDE_E     /**< Bypass, default. */
} qapi_FTC_Filter_Clock_Divide_t;

/**
   @brief The Edge detector could be configured to trigger on any of the
          following edges.
*/
typedef enum
{
  QAPI_FTC_INPUT_EDGE_POSITIVE_E,     /**< Rising edge. */
  QAPI_FTC_INPUT_EDGE_NEGATIVE_E,     /**< Falling mode. */
  QAPI_FTC_INPUT_EDGE_BOTH_E          /**< Either of the above. */
} qapi_FTC_Input_Edge_t;

/**
   @brief FTC input signal configuration.
*/
typedef struct qapi_FTC_Input_Config_s
{
  qapi_FTC_Input_t   FtcInput;         /**< Actual FTC input, one of the 4
                                             inputs. */
  qapi_FTC_Filter_Clock_Source_t Sel;   /**< Select filter clock source. */
  qapi_FTC_Filter_Clock_Divide_t Div;   /**< Additional division option. */
  uint8_t SmpNum;                      /**< Sampling number. Valid values
                                             are: 0(default), 2 to 10. */
  qapi_FTC_Input_Edge_t    Edge;        /**< Edge of the signal to count. */
} qapi_FTC_Input_Config_t;

/**
   @brief FTC Configuration.

   Set the configuration to generate PWM signals, or start a timer.
*/
typedef struct qapi_FTC_Config_s
{
  int8_t Scale;                     /**< CLK_FTC is divided by 2^(scale+1).
                                         Valid values are:
                                         - 0 to 15 for internal pre-scaler clock.
                                         - -1 to disable the pre-scaler. */
  uint8_t NumCycles;               /**< Number of cycles the counter should
                                         count from. */
  qbool_t InputEnable;             /**< If enabled, count input signal edge.
                                         If disabled, count clock cycle. */
  qapi_FTC_Input_Config_t InputConfig;  /**< Input signal configuration. */
  uint32_t Period;                  /**< Period of the PWM in terms of count
                                         clock cycles. */
  qbool_t  OutputEnable[QAPI_FTC_CHANNEL_MAX_E]; /**< Enable/disable the output
                                                      channel. */
  uint16_t Pulse[QAPI_FTC_CHANNEL_MAX_E];   /**< Pulse-width of the PWM in 
                                                 terms of count clock cycles
                                                 for each channel. */
} qapi_FTC_Config_t;

/** 
   @brief FTC interrupt callback function definition.

   FTC interrupt clients pass a function pointer of this format into the
   registration API.

   @param[in] InstanceID  The FTC instance that generated the interrupt.
*/
typedef void (*qapi_FTC_User_CB_t)(qapi_FTC_Instance_t InstanceID);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
/**
   @brief Set FTC configuration for each instance.

   Set the configuration to generate the PWM signal, or start a timer. Use 
   Input_enable to choose the clock or input signal as a counter source.
   Input_config is used to configure the input signal. Output_enable is used
   to configure the output signal. For the timer function, it might not be
   necessary to output a signal.

   @param[in] InstanceID  FTC instance ID.
   @param[in] Config       FTC configurations.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_Initialize(qapi_FTC_Instance_t InstanceID, qapi_FTC_Config_t *Config);

/**
   @brief Clear the FTC configuration for each instance.

   Clear the configuration of the FTC module.

   @param[in] InstanceID  FTC instance ID.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_Uninitialize(qapi_FTC_Instance_t InstanceID);

/**
   @brief Enable/disable the FTC function.

   Enables/disables the output of the PWM signals for a given set of channels.
   Start/stop the FTC timer function.

   @param[in] InstanceID   FTC instance ID.
   @param[in] Enable       Start/stop the FTC function.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_Enable(qapi_FTC_Instance_t InstanceID, qbool_t Enable);

/**
   @brief Enable/disable the FTC function for LED.

   Enables/disables the output of the FTC signals for LED.

   @param[in] Enable       Start/stop the FTC function.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_LED_Enable(qbool_t Enable);

/**
   @brief Registers a callback for an FTC interrupt.

   Registers a callback function with the FTC interrupt controller, and enables
   the interrupt.

   @param[in] InstanceID   FTC instance ID.
   @param[in] Callback     Callback function when the interrupt occurs.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_Register_Interrupt(qapi_FTC_Instance_t InstanceID, qapi_FTC_User_CB_t Callback);

/**
   @brief Deregisters a callback for an FTC interrupt.

   Deregisters a callback function from the FTC interrupt controller, and
   disables the interrupt.

   @param[in] InstanceID   FTC instance ID.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_FTC_Unregister_Interrupt(qapi_FTC_Instance_t InstanceID);

/** @} */ /* end_addtogroup qapi_peripherals_ftc */

#endif