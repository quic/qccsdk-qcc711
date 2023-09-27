/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "HALhwio.h"
#include "hwio_periph.h"
#include "qapi_led.h"
#include "qapi_task.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Enable LED.

   Enable LED drive sub-block outputs.

   @param[in] Instance_ID  LED instance ID.
   @param[in] Enable       Enable/Disable LED Output.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_LED_Enable(qapi_LED_Instance_t Instance_ID, qbool_t Enable)
{
    qapi_TSK_Enter_Critical();
    if (Enable)
    {
        HWIO_PERIPH_LED_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 1<<Instance_ID,
                                 1<<Instance_ID);
    }
    else
    {
        HWIO_PERIPH_LED_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 1<<Instance_ID,
                                 0<<Instance_ID);
    }
    qapi_TSK_Exit_Critical();

    return QAPI_OK;
}

/**
   @brief Select LED input source.

   Selects which of the QUP SE SPI MOSI outputs to use for code transmission.
   Or FTC outputs. Fixed to LED3. 

   @param[in] Source  Select input source. 

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_LED3_CodedData_Source_Select(qapi_LED_Source_t Source)
{
    uint8_t senum;

    qapi_TSK_Enter_Critical();
    if (Source == QAPI_LED_SOURCE_FTC_E)
    {
        HWIO_PERIPH_LED_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 
            HWIO_PERIPH_LED_CFG_LED_3_CODE_EN_BMSK, 
            0 << HWIO_PERIPH_LED_CFG_LED_3_CODE_EN_SHFT);
    }
    else
    {
        HWIO_PERIPH_LED_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 
            HWIO_PERIPH_LED_CFG_LED_3_CODE_EN_BMSK, 
            1 << HWIO_PERIPH_LED_CFG_LED_3_CODE_EN_SHFT);
        senum = Source - QAPI_LED_SOURCE_SE0_E;
        HWIO_PERIPH_LED_CFG_OUTM(PERIPH_MOD_CSR_REG_BASE, 
            HWIO_PERIPH_LED_CFG_SPI_MOSI_SEL_BMSK, 
            senum << HWIO_PERIPH_LED_CFG_SPI_MOSI_SEL_SHFT);
    }
    qapi_TSK_Exit_Critical();

  return QAPI_OK;
}
