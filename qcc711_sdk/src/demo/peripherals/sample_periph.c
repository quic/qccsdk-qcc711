/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qcli_pal.h"

#include "flash_demo.h"
#include "timer_demo.h"
#include "epd_demo.h"
#include "ftc_demo.h"
#include "gpio_demo.h"
#include "i2c_demo.h"
#include "m2mdma_demo.h"
#include "smps_demo.h"
#include "spi_demo.h"
#include "uart_demo.h"
#include "wdog_demo.h"
#include "mfp_demo.h"
#include "appi2c_demo.h"
#include "sensor_duc_demo.h"
#include "qapi_power.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializing the individual sample applications.
*/
void Initialize_Samples(void)
{
    Initialize_Flash_Demo();
    Initialize_Timer_Demo();
    Initialize_FTC_Demo();
    Initialize_GPIO_Demo();
    Initialize_WDOG_Demo();
    Initialize_MFP_Demo();
    Initialize_APPI2C_Demo();

#ifdef ENABLE_PERIPHERAL_I2C
    Initialize_I2CM_Demo();
#endif
#ifdef ENABLE_PERIPHERAL_M2MDMA
    Initialize_M2MDMA_Demo();
#endif
#ifdef ENABLE_PERIPHERAL_SPI
    Initialize_Eink_Demo();
    Initialize_Spi_Demo();
#endif
#ifdef ENABLE_PERIPHERAL_UART
    Initialize_Uart_Demo();
#endif

    Initialize_Sensor_Duc_Demo();
    Initialize_SMPS_Demo();
}

/**
   @brief Cleanup the individual sample applications before exitting.
*/
void Cleanup_Samples(void)
{
}

