/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_duc.h"
#include "qapi_power.h"
#include "hwio_pmu.h"
#include "hwio_aon.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define DUC_CHK_DLY_TIMER    1  /**< Delay setting to mask DU comparator's output glitch at the time it is being truned on. */
#define DUC_STARTUP_TIMEOUT  750 /**< DUC startup time to achieve comparator's DC accuracy. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static qapi_DUC_CB_t DUC_Callback;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief DUC interrupt Callback.

   Should do minimal processing here.

   @param[in] Interrupt  Interrupt that the callback should handle as defined by
                         QAPI_PWR_AON_INTERRUPT_TYPE_*.  Only one bit will be
                         set.
   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.
*/
static void DUC_IntHandler(uint32_t Interrupt, void *UserParam)
{
    if (DUC_Callback)
    {
        DUC_Callback(UserParam);
    }
}

/**
   @brief Enable DU comparator.

   If battery voltage is below a specified threshold for a certain amount of time, DU
   comparator is triggered. A callback is registered in order to notify this situation
   has occured.

   @param[in] Threshold  DU comparator threshold setting.
   @param[in] Callback   Callback function that will be called when DU comparator is triggered.
                         If Callback is not NULL, DU comparator interrupt will be enabled.
                         Else DU comparator interrupt will not be enabled.
   @param[in] UserParam  User specified parameter for the callback function.
   
   @return QAPI_OK on success, or an error code on failure.
*/
qapi_Status_t qapi_DUC_Enable(qapi_DUC_Threshold_t Threshold, qapi_DUC_CB_t Callback, void* UserParam)
{
    qapi_Status_t Status = QAPI_OK;
    uint32_t      ThreshValue;
    uint32_t      Now;

    /* Check if DU comparator was already enabled. */
    if (HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_DU_COMP_UNMAKSED_BMSK))
    {
        return QAPI_ERR_BUSY;
    }

    if (Threshold > QAPI_DUC_THRESHOLD_3P0V_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (Threshold < QAPI_DUC_THRESHOLD_2P3V_E)
    {
        ThreshValue = (uint32_t)(QAPI_DUC_THRESHOLD_3P0V_E - QAPI_DUC_THRESHOLD_2P3V_E + 1 + Threshold);
    }
    else
    {
        ThreshValue = (uint32_t)(Threshold - QAPI_DUC_THRESHOLD_2P3V_E);
    }

    /* DU comparator configuration. */
    HWIO_PMU_DU_COMP_CONF_OUTM((HWIO_PMU_DU_COMP_CONF_DU_COMP_THRESHOLD_BMSK |
                              HWIO_PMU_DU_COMP_CONF_DU_COMP_OUT_PT_ENA_BMSK |
                              HWIO_PMU_DU_COMP_CONF_DU_COMP_CHK_DLY_TIMER_VAL_BMSK),
                              (((ThreshValue << HWIO_PMU_DU_COMP_CONF_DU_COMP_THRESHOLD_SHFT) &
                              HWIO_PMU_DU_COMP_CONF_DU_COMP_THRESHOLD_BMSK) |
                              (0 << HWIO_PMU_DU_COMP_CONF_DU_COMP_OUT_PT_ENA_SHFT) |
                              (DUC_CHK_DLY_TIMER << HWIO_PMU_DU_COMP_CONF_DU_COMP_CHK_DLY_TIMER_VAL_SHFT)));
    
    /* Enable DU comparator. */
    HWIO_PMU_DU_COMP_CTRL_OUTM(HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_BMSK, (1 << HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_SHFT));

    /* Enable CTMR. */
    HWIO_AON_CTMR_MAIN_CTRL_OUTM(HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_BMSK, (1 << HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_SHFT));

    /* Wait 750us to achieve comparator's DC accuracy. */
    Now = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
    while(HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN - Now < DUC_STARTUP_TIMEOUT);
    if (!HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_DU_COMP_UNMAKSED_BMSK))
    {
        Status = QAPI_ERR_TIMEOUT;
        goto DUC_ENABLE_END;
    }
    
    /* Register interrupt callback and enable interrupt. */
    if (Callback != NULL)
    {
        DUC_Callback = Callback;
        Status = qapi_PWR_Register_AON_Interrupt(QAPI_PWR_AON_INT_DISPLAY, DUC_IntHandler, UserParam);
        if (Status != QAPI_OK)
        {
            qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_DISPLAY);
            DUC_Callback = NULL;
            goto DUC_ENABLE_END;
        }
    }

DUC_ENABLE_END:
    if (Status != QAPI_OK)
    {
        HWIO_PMU_DU_COMP_CTRL_OUTM(HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_BMSK, (0 << HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_SHFT));
    }
    
    return Status;
}

/**
   @brief Disable DU comparator.
*/
void qapi_DUC_Disable()
{
    /* Disable DU comparator. */
    HWIO_PMU_DU_COMP_CTRL_OUTM(HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_BMSK, (0 << HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_SHFT));
    
    /* Unregister callback function and disable interrupt. */
    qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_DISPLAY);
    DUC_Callback = NULL;

    /* Clear the interrupt (in case it is already pending). */
    qapi_PWR_Clear_AON_Int_Pending(QAPI_PWR_AON_INT_DISPLAY);
}

/**
   @brief Check if battery voltage is below DU comparator threshold.

   This function should be called after DU Comparator is enabled.

   @return True if battery voltage is below the thresold, or false if it is not
           or DU Comparator is not enabled.
*/
qbool_t qapi_DUC_Is_Below_Threshold()
{
    return HWIO_DU_STATUS_INM(HWIO_DU_STATUS_DU_COMP_OUT_BMSK);
}

