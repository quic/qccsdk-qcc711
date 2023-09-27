/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_task.h"
#include "qapi_power.h"
#include "hwio_aon.h"
#include "HALhwio.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define CTMR_EXTERN_TMR_SYNC_BMSK           0x2
#define GBLTMR_SWCAPT_STAT_CAPT_BMSK        0x1
#define GBLTMR_USEC_SHFT                    4
#define GBLTMR_MSB_SHFT                     36
#define GBLTMR_USEC_RANGE                   32

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/
 
static qbool_t TMRSyncDone = false;
static uint32_t TMR_LastTimeLo = 0;
static uint32_t TMR_LastTimeHi = 0;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Enable CETimer and Sync CETimer with GLTimer.

   This function must be called after cold boot or warm boot.

   @return Current Global timer time value in microsecond.
*/
uint64_t TMR_Enable()
{
    uint64_t GlobalTimerVal = 0;
    uint64_t CentralTimerVal = 0;
    uint64_t DeltaTime = 0;

    if (!TMRSyncDone)
    {
        /* Select Global timer clock source as HFCLK. */
        qapi_PWR_Set_TCLK_Source(true);

        /* Enable Global timer external capture for timer sync. */
        HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_OUTM(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_SYNC_BMSK,
                                            HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_SYNC_BMSK);
        /* Clear the Global timer captured system time and status. */
        HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(0);

        /* Enable Central timer and external time capture synchronization module. */
        HWIO_AON_CTMR_MAIN_CTRL_OUT(HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_BMSK|HWIO_AON_CTMR_MAIN_CTRL_EXT_IF_SYNC_EN_BMSK);
        /* Enable Central timer external capture for timer sync. */
        HWIO_AON_CTMR_EXTCAPT0_CFG_OUTM(HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_TMR_SYNC_BMSK,
                                        HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_TMR_SYNC_BMSK);
        /* Clear Central timer captured system time and status. */
        HWIO_AON_CTMR_EXTCAPT0_CAPT_OUT(0);

        /* Generate system-level timer sync pulse. */
        HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_OUT(0x1);

        /* Wait for Central timer status to be properly updated. */
        while(!(HWIO_AON_CTMR_EXTCAPT0_STAT_IN & CTMR_EXTERN_TMR_SYNC_BMSK));

        /* Read back captured Global timer value. */
        GlobalTimerVal = HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_INM(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_TIME_BMSK);
        GlobalTimerVal |= ((uint64_t)HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_IN << GBLTMR_USEC_SHFT);
        GlobalTimerVal |= ((uint64_t)HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_INM(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_TIME_BMSK) << GBLTMR_MSB_SHFT);

        /* Read back captured Central timer value. */
        CentralTimerVal = HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_INM(HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_TIME_BMSK);
        CentralTimerVal |= ((uint64_t)HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_IN << GBLTMR_USEC_SHFT);

        /* Calculate delta between captured Global tiemr and captured Central timer value. */
        DeltaTime = GlobalTimerVal - CentralTimerVal + 1;
        /* Update Central timer value. */
        HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_OUT((uint32_t)(DeltaTime >> GBLTMR_USEC_SHFT));
        HWIO_AON_CTMR_TMR_UPDATE_OUT((1 << HWIO_AON_CTMR_TMR_UPDATE_MODE_SHFT) |
                                     ((uint32_t)(DeltaTime & HWIO_AON_CTMR_TMR_UPDATE_FRAC_TIME_BMSK)));

        /* Disable Central timer external capture for timer sync. */
        HWIO_AON_CTMR_EXTCAPT0_CFG_OUTM(HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_TMR_SYNC_BMSK, 0);
        /* Disable external time capture synchronization module to save power. */
        HWIO_AON_CTMR_MAIN_CTRL_OUTM(HWIO_AON_CTMR_MAIN_CTRL_EXT_IF_SYNC_EN_BMSK, 0);
        /* Disable Global timer external capture for timer sync. */
        HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_OUTM(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_SYNC_BMSK, 0);

        TMRSyncDone = true;
        GlobalTimerVal = (GlobalTimerVal >> GBLTMR_USEC_SHFT);
    }
    else
    {
        HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(1);
        while(!HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_INM(GBLTMR_SWCAPT_STAT_CAPT_BMSK));
        /* Read back captured Global timer value. */
        GlobalTimerVal = HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_IN;
        GlobalTimerVal |= ((uint64_t)HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_INM(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_TIME_BMSK) << GBLTMR_USEC_RANGE);
        HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(0);
    }

    return GlobalTimerVal;
}

/**
   @brief Disable CETimer.
*/
void TMR_Disable()
{
    /* Disable CETimer. */
    HWIO_AON_CTMR_MAIN_CTRL_OUT(0);

    TMRSyncDone = false;
}

/**
   @brief Get current timer value in millisecond.

   @return Current timer value in millisecond.
*/
uint32_t TMR_GetCurTimeMs()
{
    uint32_t CurTime;

    if (!TMRSyncDone)
    {
        (void)TMR_Enable();
    }

    qapi_TSK_Enter_Critical();

    CurTime = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
    if (CurTime < TMR_LastTimeLo)
    {
        TMR_LastTimeHi++;
    }

    TMR_LastTimeLo = CurTime;

    qapi_TSK_Exit_Critical();

    return (uint32_t)(((((uint64_t)TMR_LastTimeHi) << 32) + TMR_LastTimeLo) / 1000);
}

