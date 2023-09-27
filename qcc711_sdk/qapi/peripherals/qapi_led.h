/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_led.h
   @brief Light-Emitting Diode (LED)
*/

/** @addtogroup qapi_peripherals_led

   The LED module combines outputs from the FTC and QUP SPI MOSI.
   The logic of LED instance 0, 1, 2 is:
   LED0_ON = ~(FTC0_PWM[0] && FTC1_PWM[0] && FTC2_PWM[0] && LED0_EN)
   LED1_ON = ~(FTC0_PWM[1] && FTC1_PWM[0] && FTC2_PWM[0] && LED1_EN)
   LED2_ON = ~(FTC0_PWM[2] && FTC1_PWM[0] && FTC2_PWM[0] && LED2_EN)
   LEDX_ON is output of the LED X instance.
   FTCX_PWM[Y] is output from the FTC X instance Y channel.
   LEDX_EN is controlled by the function qapi_LED_Enable().
   The logic of LED instance 3:
   If FTC is chosen as input source, the output of LED3 is the same as LED0.
   If SPI MOSI is chosen as input source, the output of LED3 is the same as SPI
   MOSI output.

   Typical usage:
   qapi_LED_Enable()    - Enable/disable the LED output function.
   qapi_LED3_CodedData_Source_Select() - Choose the input source of LED3;
                                         either FTC or SPI MOSI.
*/

#ifndef __QAPI_LED_H__
#define __QAPI_LED_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qapi_status.h"

/** @addtogroup qapi_peripherals_led
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief LED Instance ID.
*/
typedef enum
{
  QAPI_LED_INSTANCE_0_E,      /**<LED instance 0. */
  QAPI_LED_INSTANCE_1_E,      /**<LED instance 1. */
  QAPI_LED_INSTANCE_2_E,      /**<LED instance 2. */
  QAPI_LED_INSTANCE_3_E       /**<LED instance 3. */
} qapi_LED_Instance_t;

/**
   @brief LED input source select.
*/
typedef enum
{
  QAPI_LED_SOURCE_FTC_E,    /**<PWM from FTC.*/
  QAPI_LED_SOURCE_SE0_E,    /**<SPI MOSI from SE&nbsp;#0. */
  QAPI_LED_SOURCE_SE1_E,    /**<SPI MOSI from SE&nbsp;#1. */
  QAPI_LED_SOURCE_SE2_E,    /**<SPI MOSI from SE&nbsp;#2. */
  QAPI_LED_SOURCE_SE3_E     /**<SPI MOSI from SE&nbsp;#3. */
} qapi_LED_Source_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Enable LED.

   Enable/disable LED drive sub-block outputs.

   @param[in] InstanceID  LED instance ID.
   @param[in] Enable       Enable/Disable LED function.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_LED_Enable(qapi_LED_Instance_t InstanceID, qbool_t Enable);

/**
   @brief Select LED input source.

   Selects which of the QUP SE SPI MOSI outputs to use for code transmission.
   Or FTC outputs. Fixed to LED instance 3. 

   @param[in] Source  Select input source. 

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_LED3_CodedData_Source_Select(qapi_LED_Source_t Source);

/** @} */ /* end_addtogroup qapi_peripherals_led */

#endif