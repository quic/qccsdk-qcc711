/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_sense.h
    @brief Sensor interface definition.
*/

/** @addtogroup qapi_peripherals_sense
   
    The temperature sensor monitors the temperature of the SoC using an on-die
    analog sensor. Users can get the temperature by calling qapi_SENS_Get_Temp().
    
    The voltage sensor monitors the voltage of several different sources using
    a 10-bit SAR ADC. The sources can be inputs from external PIOs or battery voltage.

    To measure VBAT:
    - the sensor must be enabled using qapi_SENS_Voltage_Sensor_Enable()
    - the user can then select different loads using
      qapi_SENS_Vbat_Load_Cell_Enable() and enable VBAT monitoring using
      qapi_SENS_Vbat_Monitor_Enable()
    - after the state is stable use qapi_SENS_Get_Voltage() several times to
      get VBAT
    - when VBAT measurement is complete, disable the load on the cell using
      qapi_SENS_Vbat_Load_Cell_Enable()
    - disable VBAT monitoring using qapi_SENS_Vbat_Monitor_Enable()
    - disable the sensor using qapi_SENS_Voltage_Sensor_Enable()

    To measure PIO voltage:
    - the PIO must be configured with an input direction and have no pull
    - enable the voltage sensor using qapi_SENS_Voltage_Sensor_Enable()
    - select the PIO to ADC routing using qapi_SENS_Pio_Switch_Enable() -- 
      there are options for a divided down signal, connection direction, and
      a 10 k or 100 k ohm pull up resistor
    - get the voltage using qapi_SENS_Get_Voltage()
    - when the measurement is complete, return the ADC routing to its default
      condition using qapi_SENS_Pio_Switch_Enable()
    - disable the sensor using qapi_SENS_Voltage_Sensor_Enable().
*/
 
#ifndef __QAPI_SENSE_H__
#define __QAPI_SENSE_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_sense
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of input sources for voltage measurement.
*/
typedef enum
{
    QAPI_SENS_VOLTAGE_SOURCE_VBAT_E,           /**< Input source is VBAT. */
    QAPI_SENS_VOLTAGE_SOURCE_PIO0_E,           /**< Input source is PIO[0]: GPIO22. */
    QAPI_SENS_VOLTAGE_SOURCE_PIO1_E,           /**< Input source is PIO[1]: GPIO23. */
    QAPI_SENS_VOLTAGE_SOURCE_PIO2_E,           /**< Input source is PIO[2]: GPIO24. */
    QAPI_SENS_VOLTAGE_SOURCE_PIO3_E            /**< Input source is PIO[3]: GPIO25. */
} qapi_SENS_Voltage_Source_t;

/**
   Enumeration of load cells for VBAT measurement.
*/
typedef enum
{
    QAPI_SENS_VBAT_LOAD_CELL1_E,               /**< VBAT measured with a 5&nbsp;mA load cell1. */
    QAPI_SENS_VBAT_LOAD_CELL2_E                /**< VBAT measured with a 5&nbsp;mA load cell2. */
} qapi_SENS_Vbat_Load_t;

/**
   Enumeration of PIO input sources with different dividers.
*/
typedef enum
{
    QAPI_SENS_PIO_SOURCE_PIO0_DIVIDE_BY2_E,    /**< Select input from PIO[0]: GPIO22. The PIO voltage sent to the sensor is divided
                                                    by 2. It can be used for input voltage with a range of 1.8&nbsp;V ~ 3.6&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO1_DIVIDE_BY2_E,    /**< Select input from PIO[1]: GPIO23. The PIO voltage sent to the sensor is divided
                                                    by 2. It can be used for input voltage with a range of 1.8&nbsp;V ~ 3.6&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO2_DIVIDE_BY2_E,    /**< Select input from PIO[2]: GPIO24. The PIO voltage sent to the sensor is divided
                                                    by 2. It can be used for input voltage with a range of 1.8&nbsp;V ~ 3.6&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO3_DIVIDE_BY2_E,    /**< Select input from PIO[3]: GPIO25. The PIO voltage sent to the sensor is divided
                                                    by 2. It can be used for input voltage with a range of 1.8&nbsp;V ~ 3.6&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO0_NO_DIVIDE_E,     /**< Select input from PIO[0]: GPIO22. The PIO voltage sent to the sensor is not
                                                    divided. It can be used for input voltage with a range of 0&nbsp;V ~ 1.8&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO1_NO_DIVIDE_E,     /**< Select input from PIO[1]: GPIO23. The PIO voltage sent to the sensor is not
                                                    divided. It can be used for input voltage with a range of 0&nbsp;V ~ 1.8&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO2_NO_DIVIDE_E,     /**< Select input from PIO[2]: GPIO24. The PIO voltage sent to the sensor is not
                                                    divided. It can be used for input voltage with a range of 0&nbsp;V ~ 1.8&nbsp;V. */
    QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E,   /**< Select input from PIO[0]: GPIO22. It also provides a 100&nbsp;kiloOhm internal pull
                                                    up resistor. */
    QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_10K_E,    /**< Select input from PIO[0]: GPIO22. It also provides a 10&nbsp;kiloOhm internal pull
                                                    up resistor. */
    QAPI_SENS_PIO_SOURCE_PIO1_PULLUP_100K_E,   /**< Select input from PIO[1]: GPIO23. It also provides a 100&nbsp;kiloOhm internal pull
                                                    up resistor. */
    QAPI_SENS_PIO_SOURCE_PIO1_PULLUP_10K_E,    /**< Select input from PIO[1]: GPIO23. It also provides a 10&nbsp;kiloOhm internal pull
                                                    up resistor. */
    QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_100K_E,   /**< Select input from PIO[2]: GPIO24. It also provides a 100&nbsp;kiloOhm internal pull
                                                    up resistor. */
    QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_10K_E     /**< Select input from PIO[2]: GPIO24. It also provides a 10&nbsp;kiloOhm internal pull
                                                    up resistor. */
} qapi_SENS_PIO_Source_t;

/**
   Enumeration of the ADC internal pullup resistors.
*/
typedef enum
{
    QAPI_SENS_PULLUP_RESISTOR_100K_E,          /**< Internal pullup resistor of 100&nbsp;kiloOhm. */
    QAPI_SENS_PULLUP_RESISTOR_10K_E            /**< Internal pullup resistor of 10&nbsp;kiloOhm. */
} qapi_SENS_Pullup_Resistor_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Get the temperature.

   This function requests temperature sensing and returns the temperature
   in 1/100th degrees Celsius.

   @param[out] Temperature  Temperature in 1/100th degrees Celsius reported
                            by the sensor.

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Temp(int32_t *Temperature);

/**
   @brief Enable or disable the voltage sensor.

   This function should be called to enable the voltage sensor before other
   voltage sensor functions. It should be called to disable the voltage sensor
   if the sensor is not used any more.

   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_SENS_Voltage_Sensor_Enable(qbool_t Enable);

/**
   @brief Enable or disable the load cell for VBAT measurement.

   @param[in]  Load        Load cell selection for VBAT measurement.
   @param[in]  Enable      Set to TRUE to enable or FALSE to disable the load cell.
   @param[out] Resistance  Resistance of the selected load in Ohms.

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Vbat_Load_Cell_Enable(qapi_SENS_Vbat_Load_t Load, qbool_t Enable, uint32_t *Resistance);

/**
   @brief Enable or disable the VBAT monitor.

   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Vbat_Monitor_Enable(qbool_t Enable);

/**
   @brief Enable or disable the PIO switch for a specified PIO source.

   The related PIO should be configured to be an input and the pulls are
   disabled, prior to enabling its PIO switch.

   The PIO source can be selected based on the PIO input voltage range or
   PIO usage. If the:
   - Input PIO voltage is 1.8&nbsp;V ~ 3.6&nbsp;V -- an enumerator
   QAPI_SENS_PIO_SOURCE_PIO[X]_DIVIDE_BY2_E must be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_DIVIDE_BY2_E).
   - Input PIO voltage is 0&nbsp;V ~ 1.8&nbsp;V -- an enumerator 
   QAPI_SENS_PIO_SOURCE_PIO[X]_NO_DIVIDE_E can be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_NO_DIVIDE_E).
   - PIO usage is to measure external load like LDR -- 
   QAPI_SENS_PIO_SOURCE_PIO[X]_PULLUP_[X]K_E can be selected (for example
   #QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E).

   @param[in] Source  The input PIO source.
   @param[in] Enable  Set to TRUE to enable or FALSE to disable.

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Pio_Switch_Enable(qapi_SENS_PIO_Source_t Source, qbool_t Enable);

/**
   @brief Gets the voltage of the specified input source.

   This function requests voltage measurement of the selected source and returns
   the voltage. The input source should be enabled before
   getting the voltage using this function.

   @param[in]  Source   The input source for the sensor to measure the voltage.
   @param[out] Voltage  The measured voltage of the selected input source in
                        microvolts (1e-6).

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Voltage(qapi_SENS_Voltage_Source_t Source, uint32_t *Voltage);

/**
   @brief Gets the resistance of internal pull up resistor.

   @param[in]  Resistor    Specify the internal pull up resistor.
   @param[out] Resistance  Resistance of the selected internal resistor in Ohms.

   @return
   QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_SENS_Get_Pullup_Resistance(qapi_SENS_Pullup_Resistor_t Resistor, uint32_t *Resistance);

/** @} */ /* end_addtogroup qapi_peripherals_sense */

#endif
