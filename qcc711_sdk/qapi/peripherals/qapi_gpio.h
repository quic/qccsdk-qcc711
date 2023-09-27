/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_gpio.h
   @brief General Purpose Input/Output interface (GPIO)
*/

/** @addtogroup qapi_peripherals_gpio
  The GPIO module provides access to general-purpose input/output (GPIO)
  pins the value of which consist of one of two voltage settings (high or
  low) and the behavior of which can be programmed using software.

  Typical usage:
  - qapi_GPIO_Config()                   -- Config GPIO parameters, include
                                            function, direction, pull-type,
                                            and drive strength.
  - qapi_GPIO_Set()                      -- Set the GPIO output value.
  - qapi_GPIO_Get()                      -- Get the GPIO input value.
  - qapi_GPIO_Enable_Interrupt()         -- Register and enable GPIO input
                                            interrupt.
  - qapi_GPIO_Disable_Interrupt()        -- Unregister the GPIO interrupt
                                            function.
  - qapi_GPIO_Enable_Sleep_Interrupt()   -- Register and enable GPIO input
                                            interrupt for Deep Sleep mode.
  - qapi_GPIO_Disable_Sleep_Interrupt()  -- Unregister the GPIO interrupt
                                            function for Deep Sleep mode.

  @note1hang If calling qapi_GPIO_Enable_Sleep_Interrupt(), after detection,
             toggle the GPIO input signal, the chip wakes up and calls the
             callback functions.

  @note1hang Before using GPIO APIs, qapi_PWR_Set_Module_State
             (#QAPI_PWR_MODULE_GPIO_E, #QAPI_PWR_STATE_ACTIVE_E,
             #QAPI_PWR_STATE_ACTIVE_E) must be called.
*/

#ifndef __QAPI_GPIO_H__
#define __QAPI_GPIO_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qapi_status.h"

/** @addtogroup qapi_peripherals_gpio
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief GPIO pin number.
*/
typedef enum
{ 
  QAPI_GPIO_ID0_E,    /**< GPIO 0. */
  QAPI_GPIO_ID1_E,    /**< GPIO 1. */
  QAPI_GPIO_ID2_E,    /**< GPIO 2. */
  QAPI_GPIO_ID3_E,    /**< GPIO 3. */
  QAPI_GPIO_ID4_E,    /**< GPIO 4. */
  QAPI_GPIO_ID5_E,    /**< GPIO 5. */
  QAPI_GPIO_ID6_E,    /**< GPIO 6. */
  QAPI_GPIO_ID7_E,    /**< GPIO 7. */
  QAPI_GPIO_ID8_E,    /**< GPIO 8. */
  QAPI_GPIO_ID9_E,    /**< GPIO 9. */
  QAPI_GPIO_ID10_E,   /**< GPIO 10. */
  QAPI_GPIO_ID11_E,   /**< GPIO 11. */
  QAPI_GPIO_ID12_E,   /**< GPIO 12. */
  QAPI_GPIO_ID13_E,   /**< GPIO 13. */
  QAPI_GPIO_ID14_E,   /**< GPIO 14. */
  QAPI_GPIO_ID15_E,   /**< GPIO 15. */
  QAPI_GPIO_ID16_E,   /**< GPIO 16. */
  QAPI_GPIO_ID17_E,   /**< GPIO 17. */
  QAPI_GPIO_ID18_E,   /**< GPIO 18. */
  QAPI_GPIO_ID19_E,   /**< GPIO 19. */
  QAPI_GPIO_ID20_E,   /**< GPIO 20. */
  QAPI_GPIO_ID21_E,   /**< GPIO 21. */
  QAPI_GPIO_ID22_E,   /**< GPIO 22. */
  QAPI_GPIO_ID23_E,   /**< GPIO 23. */
  QAPI_GPIO_ID24_E,   /**< GPIO 24. */
  QAPI_GPIO_ID25_E,   /**< GPIO 25. */
  QAPI_GPIO_MAX_ID_E  /**< Maximum GPIO. */
} qapi_GPIO_Id_t;

/**
   @brief SE port number.

   It includes 6 bits, the lower 3 bits indicate the SE port number,
   the higher 3 bits indicate the peripheral type:
   0 : default
   1 : UART
   2 : I2C
   3 : SPI M/SE
   4 : SPI 3/4 wires
*/
typedef enum
{
  SE_PORT_DEFAULT = 0,      /**< Default port */

  SE_UART_CTS_E = 0x8,      /**< SE port0 */
  SE_UART_RFR_E,            /**< SE port1 */
  SE_UART_TX_E,             /**< SE port2 */
  SE_UART_RX_E,             /**< SE port3 */
 
  SE_I2C_SDA_E = 0x10,      /**< SE port0 */
  SE_I2C_SCL_E,             /**< SE port1 */

  SE_SPI_MISO_E = 0x18,     /**< SE port0 */
  SE_SPI_MOSI_E,            /**< SE port1 */
  SE_SPI_SCLK_E,            /**< SE port2 */
  SE_SPI_CS0_E,             /**< SE port3 */
  SE_SPI_CS1_E,             /**< SE port4 */

  SE_SPI34_SDIN_E = 0x21,   /**< SE port1 */
  SE_SPI34_CLK_E,           /**< SE port2 */
  SE_SPI34_CS0_E,           /**< SE port3 */
  SE_SPI34_CS1_E            /**< SE port4 */
} SE_PORT_t;

/**
   @brief GPIO alternative configuration.

   This structure is used to specify the alternative configurations of GPIOs
   for different hardware designs.
*/
typedef struct qapi_GPIO_Alt_Config_s
{
  uint16_t  PIOFunc : 4;    /**< PIO function select. */
  uint16_t  Dir     : 1;    /**< Direction (input or output). */
  uint16_t  Pull    : 2;    /**< Pull value. */
  uint16_t  Drive   : 3;    /**< Drive strength. */
  uint16_t  se_port : 6;    /**< PIO function select. */
} qapi_GPIO_Alt_Config_t;

/** 
   @brief GPIO pin direction. 
*/
typedef enum
{ 
  QAPI_GPIO_INPUT_E,    /**< Specify the PIO as an INPUT to the SoC. */
  QAPI_GPIO_OUTPUT_E    /**< Specify the PIO as an OUTPUT from the SoC. */
} qapi_GPIO_Direction_t;

/** 
   @brief GPIO pin pull type.
*/
typedef enum
{
  QAPI_GPIO_NO_PULL_E,      /**< Specify no pull. @codeinline{Input + NO PULL} is equal to High-Z state. */
  QAPI_GPIO_PULL_DOWN_E,    /**< Pull the GPIO down. */
  QAPI_GPIO_PULL_UP_E       /**< Pull the GPIO up. */
} qapi_GPIO_Pull_t;

/**
   @brief GPIO pin drive strength. 
*/
typedef enum
{
  QAPI_GPIO_FAST_2MA_E,     /**< Specify a fast 2&nbsp; mA drive. */
  QAPI_GPIO_FAST_4MA_E,     /**< Specify a fast 4&nbsp;mA drive. */
  QAPI_GPIO_FAST_8MA_E,     /**< Specify a fast 8&nbsp;mA drive. */
  QAPI_GPIO_FAST_12MA_E,    /**< Specify a fast 12&nbsp;mA drive. */
  QAPI_GPIO_SLOW_2MA_E,     /**< Specify a slow 2&nbsp;mA drive. */
  QAPI_GPIO_SLOW_4MA_E,     /**< Specify a slow 4&nbsp;mA drive. */
  QAPI_GPIO_SLOW_8MA_E,     /**< Specify a slow 8&nbsp;mA drive. */
  QAPI_GPIO_SLOW_12MA_E     /**< Specify a slow 12&nbsp;mA drive. */
}qapi_GPIO_Drive_t;

/** 
   @brief GPIO output state specification.
*/
typedef enum
{
  QAPI_GPIO_LOW_VALUE_E,     /**< Drive the output LOW. */
  QAPI_GPIO_HIGH_VALUE_E     /**< Drive the output HIGH. */
}qapi_GPIO_Value_t;

/** 
    @brief GPIO interrupt trigger type enumeration for supported triggers.
*/
typedef enum {
  QAPI_GPIO_TRIGGER_LEVEL_HIGH_E,    /**< Level triggered active high. */
  QAPI_GPIO_TRIGGER_LEVEL_LOW_E,     /**< Level triggered active low. */
  QAPI_GPIO_TRIGGER_EDGE_RISING_E,   /**< Rising-edge triggered. */
  QAPI_GPIO_TRIGGER_EDGE_FALLING_E,  /**< Falling-edge triggered. */
  QAPI_GPIO_TRIGGER_EDGE_DUAL_E      /**< Dual-edge triggered. */
} qapi_GPIO_Trigger_t;

/** 
    @brief GPIO sleep interrupt trigger type enumeration.
*/
typedef enum {
  QAPI_GPIO_SLEEP_TRIGGER_EDGE_RISING_E,   /**< Rising-edge triggered. */
  QAPI_GPIO_SLEEP_TRIGGER_EDGE_FALLING_E,  /**< Falling-edge triggered. */
  QAPI_GPIO_SLEEP_TRIGGER_EDGE_DUAL_E      /**< Dual-edge triggered. */
} qapi_GPIO_Sleep_Trigger_t;

/**
   @brief GPIO configuration.

   This structure is used to specify the configuration for a GPIO on the SoC.
   The GPIO can be configured as an input or output that can be driven high or
   low by the software. The interface also allows the SoC PIOs to be configured
   for alternate functionality.
*/
typedef struct qapi_GPIO_Config_s
{
  uint8_t               PIOFunc;    /**< PIO function select. */
  qapi_GPIO_Direction_t Dir;        /**< Direction (input or output). */
  qapi_GPIO_Pull_t      Pull;       /**< Pull value. */
  qapi_GPIO_Drive_t     Drive;      /**< Drive strength. */
} qapi_GPIO_Config_t;

/** 
   @brief GPIO interrupt callback data type.

   This is the data type of the argument passed into the callback that is
   registered with the GPIO interrupt module. The value to pass is given
   by the client at registration time.
*/
typedef uint32_t qapi_GPIO_CB_Data_t;

/** 
   @brief GPIO interrupt callback function definition.

   GPIO interrupt clients pass a function pointer of this format into the
   registration API.

   @param[in] Data Callback data.
*/
typedef void (*qapi_GPIO_CB_t)(qapi_GPIO_CB_Data_t Data);

/**
   @brief GPIO interrupt callback list structure.

   This structure is used to store the GPIO pin interrupt callback function
   and parameter in a linked list.
*/
typedef struct qapi_GPIO_CB_List_s
{
  qapi_GPIO_Id_t GPIO_ID;               /**< GPIO pin number. */
  qapi_GPIO_CB_t Func;                  /**< GPIO callback function. */
  qapi_GPIO_CB_Data_t Data;             /**< GPIO callback parameter. */
  struct qapi_GPIO_CB_List_s *Next;     /**< Pointer to the next GPIO in the linked list callback structure. */
} qapi_GPIO_CB_List_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Changes the SoC PIO configuration.

   This function configures an SoC PIO based on a set of fields specified in
   the configuration structure reference passed in as a parameter.

   @param[in] GPIO_ID           GPIO number.
   @param[in] Config            PIO configuration to use.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *Config);

/**
   @brief Sets the state of an SoC PIO configured as an output GPIO.

   This function drives the output of an SoC PIO that has been configured as a
   generic output GPIO to a specified value.

   @param[in] GPIO_ID  GPIO number.
   @param[in] Value    Output value.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Set(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Value_t Value);

/**
   @brief Reads the state of an SoC PIO.

   @param[in]  GPIO_ID  GPIO number.
   @param[out] Value    Input value.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Get(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Value_t *Value);

/**
   @brief Registers a callback for a GPIO interrupt.

   Registers a callback function with the GPIO interrupt controller, and enables
   the interrupt. This function configures and routes the interrupt accordingly,
   as well as enabling it in the underlying layers.

   @param[in] GPIO_ID   GPIO number.
   @param[in] Trigger   Trigger type for the interrupt.
   @param[in] Callback  Callback function pointer.
   @param[in] Data      Callback data.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Enable_Interrupt(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Trigger_t Trigger, qapi_GPIO_CB_t Callback, qapi_GPIO_CB_Data_t Data);

/**
   @brief Deregisters a callback for a GPIO interrupt.

   Deregisters a callback function from the GPIO interrupt controller, and
   disables the interrupt. This function deconfigures the interrupt
   accordingly, and disables it in the underlying layers.

   @param[in] GPIO_ID  GPIO number.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Disable_Interrupt(qapi_GPIO_Id_t GPIO_ID);

/**
   @brief Registers a callback for a GPIO interrupt in Deep Sleep mode.

   Registers a callback function with the GPIO interrupt controller, and enables
   the interrupt in Deep Sleep mode. This function configures and routes the 
   interrupt accordingly, and enables it in the underlying layers.

   @param[in] GPIO_ID   GPIO number.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Enable_Sleep_Interrupt(qapi_GPIO_Id_t GPIO_ID);

/**
   @brief Deregisters a callback for a GPIO interrupt in Deep Sleep mode.

   Deregisters a callback function from the GPIO interrupt controller, and
   disables the interrupt in Deep Sleep mode. This function deconfigures the
   interrupt accordingly, and disables it in the underlying layers.

   @param[in] GPIO_ID  GPIO number.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Disable_Sleep_Interrupt(qapi_GPIO_Id_t GPIO_ID);

/**
   @brief Clear sleep interrupt status.

   Each processor should clear the status of its own pre-configured GPIO after
   a sleep interrupt.

   @param[in] GPIO_ID  GPIO number.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Clear_Sleep_Interrupt_Status(qapi_GPIO_Id_t GPIO_ID);

/**
   @brief Get sleep interrupt status.

   This function is triggered by a rising or failing signal
   from GPIO input.

   @param[in]   GPIO_ID  GPIO number.
   @param[out]  Status   Interrupt status. 0: Fall, 1: Rise, 2: Both.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Get_Sleep_Interrupt_Status(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Sleep_Trigger_t *Status);

/**
   @brief Change the mapping of serial engine interface.

   Control the 5*5 mus in front of each Serial engine interface,
   to give flexipilty to serial engine PIO mapping on PADs.

   @param[in] SE_ID    Serial engine number.
   @param[in] GPIO_ID  GPIO number.
   @param[in] SE_PORT  Serial engine port number.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Port_Mapping(uint8_t SE_ID, qapi_GPIO_Id_t GPIO_ID, SE_PORT_t SE_PORT);

/**
   @brief Initialize the GPIO configuration.

   Initialize GPIO global parameters. Open the CPU interrupt for the GPIO
   module. Apply the alternative GPIO configuration to GPIO register.
   If not needed, set the parameter to NULL.

   @param[in] *AltConfig  Pointer to the alternative PIO configuration table.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Initialize(qapi_GPIO_Alt_Config_t *AltConfig);

/**
   @brief Enable/Disable debugger function.

   When disable debugger function, GPIO9,10,11,12 can be used as alternate
   functions. Otherwise they will be either mapped to SWD or JTAG according
   to the state of the chip. Default value is enabled.

   @param[in] Enable  Enable/Disable JTAG function.

   @return
   QAPI_OK -- On success.\n
   Error code -- On failure.
*/
qapi_Status_t qapi_GPIO_Debugger_Enable(qbool_t Enable);

/**
   @brief Set GPIO configuration to MTP.

   Set the GPIO configuration to the MTP, this function does not update GPIO
   registers.

   @param[in] GPIO_ID           GPIO number.
   @param[in] qapi_GPIO_Config  Pin configuration to use.
   @param[in] Value             Output value.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Set_MTP_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *qapi_GPIO_Config, qapi_GPIO_Value_t Value);

/**
   @brief Get GPIO configuration from MTP.

   Get the GPIO configuration from the MTP, the result may not match the current
   GPIO registers configuration.

   @param[in] GPIO_ID           GPIO number.
   @param[in] qapi_GPIO_Config  Pin configuration to use.
   @param[in] Value             Output value.

   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_GPIO_Get_MTP_Config(qapi_GPIO_Id_t GPIO_ID, qapi_GPIO_Config_t *qapi_GPIO_Config, qapi_GPIO_Value_t *Value);

/** @} */ /* end_addtogroup qapi_peripherals_gpio */

#endif
