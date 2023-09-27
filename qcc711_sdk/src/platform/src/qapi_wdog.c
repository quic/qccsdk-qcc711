/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include "qcc710.h"
#include "core_cm3.h"
#include "hwio_aon.h"
#include "qapi_wdog.h"

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
   @brief Configures the watchdog timer.

   The watchdog bark will occur at the ExpireTime specified and will trigger the
   watchdog interrupt to occur if it has been enabled.
   The watchdog bite will occur at twice the ExpireTime specified and will
   trigger a SOC reset only if bit 12 of the debug_disable_vector OTP has been
   set.

   @param[in] ExpireTime  Bark time for the watchdog to expire in 0.1 second
                          intervals. Bite will occure after twice this time.
                          If zero is specified, the watchdog will be disabled.

   @return QAPI_OK if the watchdog was configured successfully or a negative
           value if there was an error.
*/
qapi_Status_t qapi_WDOG_Configure(uint8_t ExpireTime)
{
    uint8_t Val_15To8, Val_19To16;
    
    if (ExpireTime == 0)
    {
        HWIO_AON_WDOG_WDT_DISABLE_OUT(0x5A);
        HWIO_AON_WDOG_WDT_DISABLE_OUT(0xA5);
        HWIO_AON_WDOG_WDT_DISABLE_OUT(0x96);
        HWIO_AON_WDOG_WDT_DISABLE_OUT(0x69);
    }
    else
    {
        if (ExpireTime > 127)
        {
            return QAPI_ERR_INVALID_PARAM;
        }
        Val_19To16 = (uint8_t)ExpireTime / 20;
        Val_15To8 = (uint8_t)((ExpireTime * 256) / 20);
        HWIO_AON_WDOG_BARK_COUNT_15TO8_OUT(Val_15To8);   //0xFF is 2s
        HWIO_AON_WDOG_BARK_COUNT_19TO16_OUT(Val_19To16); //1 is 2s
        
        HWIO_AON_WDOG_DIVISOR_OUTM(HWIO_AON_WDOG_DIVISOR_VALUE_BMSK, ExpireTime*2);
        HWIO_AON_WDOG_CONTROL_OUTM(HWIO_AON_WDOG_CONTROL_WD_ACTIVE_BMSK | HWIO_AON_WDOG_CONTROL_FREEZE_IN_DBGACK_BMSK,
                                   HWIO_AON_WDOG_CONTROL_WD_ACTIVE_BMSK | HWIO_AON_WDOG_CONTROL_FREEZE_IN_DBGACK_BMSK);
    }

    return QAPI_OK;
}

/**
   @brief Gets the current watchdog configuration.

   @return The configured expire time of the watchdog in 0.1 second intervals or
           zero if the watchdog is disabled.
*/
uint8_t qapi_WDOG_GetConfig(void)
{
    uint8_t ExpireTime;

    if(HWIO_AON_WDOG_CONTROL_INM(HWIO_AON_WDOG_CONTROL_WD_ACTIVE_BMSK))
    {
        ExpireTime = HWIO_AON_WDOG_DIVISOR_INM(HWIO_AON_WDOG_DIVISOR_VALUE_BMSK) / 2;
    }
    else
    {
        ExpireTime = 0;
    }

    return(ExpireTime);
}

/**
   @brief Pets the watchdog, resetting its counters.
*/
void qapi_WDOG_Pet(void)
{
    HWIO_AON_WDOG_CONTROL_OUTM(HWIO_AON_WDOG_CONTROL_KICK_WD_BMSK,
        0x1<<HWIO_AON_WDOG_CONTROL_KICK_WD_SHFT);
}

/**
   @brief Enables an AON IRQ.

   This function only enables the bark interrupt in the NAON block and doesn't
   affect the NVIC.

   @param[in] Enable  Flag indicating if the interrupt should be enabled (true)
                      or disabled (false).

   @return QAPI_OK if the watchdog was configured successfully or a negative
           value if there was an error.
*/
qapi_Status_t qapi_WDOG_EnableIRQ(qbool_t Enable)
{
    if (Enable)
    {
        NVIC_EnableIRQ((IRQn_Type)WDogBark_IRQn);
        HWIO_AON_WDOG_BARK_INT_ENABLE_OUTM(
            HWIO_AON_WDOG_BARK_INT_ENABLE_VALUE_BMSK, 1);
    }
    else
    {
        HWIO_AON_WDOG_BARK_INT_ENABLE_OUTM(
            HWIO_AON_WDOG_BARK_INT_ENABLE_VALUE_BMSK, 0);
        NVIC_DisableIRQ((IRQn_Type)WDogBark_IRQn);
    }

    return QAPI_OK;
}

/**
   @brief Provides the interrupt status of the watchdog.

   This function also clear the interrupt status bit after read action.

   @return TURE if WDOG bark interrupt has be trigged
           FALSE if WDOG bark interrupt has not be trigged.
*/
qbool_t qapi_WDOG_GetIRQStatus(void)
{
    qbool_t Status;
  
    Status = HWIO_AON_WDOG_BARK_INT_STATUS_INM(
        HWIO_AON_WDOG_BARK_INT_STATUS_LEVEL_BMSK);
  
    HWIO_AON_WDOG_BARK_INT_STATUS_OUTM(
        HWIO_AON_WDOG_BARK_INT_STATUS_LEVEL_BMSK, 1);
  
    return Status;
}


