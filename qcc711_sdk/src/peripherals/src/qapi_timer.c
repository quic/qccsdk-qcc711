/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "timer.h"
#include "qapi_timer.h"
#include "qapi_heap.h"
#include "qapi_power.h"
#include "qapi_task.h"
#include "hwio_aon.h"
#include "HALhwio.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define GBLTMR_MSB_VAL_BMSK                      0xFFF
#define HWIO_AON_CTMR_CMPR_STAT_LATE_DET_BMSK    0x80000000

#define INVALID_EXPIRE_VALUE                     0xFFFFFFFFFFFFFFFF  /**< Invalid expire value. */
#define MAX_BIG_COMP_VALUE                       0xFFFFFFF           /**< Max big comparator value, range [27:0]. */
#define MAX_SMALL_COMP_VALUE                     0x1FFFFF            /**< Max small comparator value, range [20:0]. */
#define MAX_BIG_COMP_RANGE                       (0xFF00000 - 1)     /**< Max big comparator range that is valid .*/
#define MAX_SMALL_COMP_RANGE                     (0x180000 - 1)      /**< Max small comparator range that is valid .*/
#define MAX_HUGE_COMP_RANGE                      (0xFFF00000 - 1)    /**< Max GTMR huge comparator range that is valid .*/

#define MAX_USABLE_COMPARATORS                   12    /**< The number of total comparators. */
#define SMALL_COMPARATOR0_ID                     4     /**< Small comparator 0 ID. */

#define TMR_COMPARATOR_DISABLE                   0x0  /**< Disable timer comparator. */
#define TMR_COMPARATOR_ENABLE_ONCE               0x1  /**< Enable timer comparator generate one interrupt. */
#define TMR_COMPARATOR_ENABLE_REPEATE            0x2  /**< Enable timer comparator generate interrupts repeately. */

#define TMR_COMPARATOR_TOLERANCE_IN_US           10   /**< How much time will be advanced in case expire is in the past. */
#define TMR_COMPARATOR_MAX_TOLERANCE_IN_US       500  /**< Max tolerance that will be tried if compare value is late. */
#define TMR_COMPARATOR_DURATION_ALLOW_SHUTDOWN   5000 /**< If comparator duration is less than this value, keep system in active. */

#define TMR_SHUDOWN_CALLBACK_PRIORITY            (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT - 0x11) /**< Timer shutdown callback priority. */

#define TMR_COMPINFO_FLAG_DEFERRABLE             (0x0001) /**< If this bit is set, the comparator is deferrable */

#define TMR_TIMEOUT_IN_RANGE                     0
#define TMR_TIMEOUT_OUT_OF_RANGE                 1
#define TMR_TIMEOUT_CLOSE_TO_NOW                 2

#define TMR_CHECK_LATE(_addr_)                   (in_dword_masked((_addr_), HWIO_AON_CTMR_CMPR_STAT_LATE_DET_BMSK))

#define TMR_SET_COMP_VALUE(_cmd_, _max_, _stat_) {                                           \
        do {                                                                                 \
            out_dword((_cmd_), (MatchValue & (_max_)));                                      \
            if (Range == TMR_TIMEOUT_CLOSE_TO_NOW)                                           \
            {                                                                                \
                /* If timeout value is too small. */                                         \
                MatchValue += TMR_COMPARATOR_TOLERANCE_IN_US;                                \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                /* If timeout value is close to MAX_RANGE. */                                \
                MatchValue -= TMR_COMPARATOR_TOLERANCE_IN_US;                                \
            }                                                                                \
            Tolerance += TMR_COMPARATOR_TOLERANCE_IN_US;                                     \
        }while(TMR_CHECK_LATE((_stat_)) && Tolerance <= TMR_COMPARATOR_MAX_TOLERANCE_IN_US); \
    }

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of the comparator state.
*/
typedef enum
{
    TMR_COMP_STATE_INIT_E,                 /**< Timer comparator is inited. */
    TMR_COMP_STATE_RUN_ONCE_E,             /**< Timer comparator is running to generate one interrupt. */
    TMR_COMP_STATE_RUN_REPEATE_AUTO_E,     /**< Timer comparator is running repeatedly with auto reload. */
    TMR_COMP_STATE_RUN_REPEATE_SEMIAUTO_E, /**< Timer comparator is running repeatedly with manual load for the first time, then auto load. */
    TMR_COMP_STATE_RUN_REPEATE_MANUAL_E,   /**< Timer comparator is running repeatedly with manual reload. */
    TMR_COMP_STATE_EXPIRE_E,               /**< Timer comparator is expired. */
    TMR_COMP_STATE_STOP_E                  /**< Timer comparator is stopped. */
} TMR_CompState_t;

/**
   Structure used to specify the comparator information.
*/
typedef struct TMR_CompInfo_s
{
    uint8_t             CompState;  /**< Comparator state. */
    uint16_t            Flags;      /**< Flags. */
    qapi_TMR_Comp_CB_t  CompCB;     /**< Callback function when comparator expires. */
    void               *CompParam;  /**< User specified parameter for callback function. */
    uint64_t            Duration;   /**< Comparator duration before expiration. */
    uint64_t            Expire;     /**< Comparator absolute expire time. */
} TMR_CompInfo_t;

/**
   Structure used to specify the retained timer context information.
*/
typedef struct TMR_RetnContext_s
{
    qbool_t            RetnInit;         /**< Flag indicates retained info is initialized or not. */
    uint32_t           CurTimeHi;        /**< Absolute time high 32-bit since boot. */
    uint32_t           CurTimeLo;        /**< Absolute time low 32-bit since boot. */
    qapi_PWR_Ballot_t  Ballot;           /**< Ballot for power voting. */
    void              *ShutdownCBHandle; /**< Handle for the registered shutdown callbacks. */
    TMR_CompInfo_t    *CompInfo[MAX_USABLE_COMPARATORS]; /**< Pointer to comp info. */
} TMR_RetnContext_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static qbool_t TMRInitDone = false;

static TMR_RetnContext_t TMR_RetnContext __attribute__((section (".bss.retain")));

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static qapi_Status_t TMR_Init();

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Get current timer value.

   @return Current timer value in microseconds.
*/
static uint64_t TMR_GetCurTime()
{
    uint32_t TimeLow;

    qapi_TSK_Enter_Critical();

    TimeLow = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
    if (TimeLow < TMR_RetnContext.CurTimeLo)
    {
        TMR_RetnContext.CurTimeHi++;
    }

    TMR_RetnContext.CurTimeLo = TimeLow;

    qapi_TSK_Exit_Critical();

    return ((((uint64_t)(TMR_RetnContext.CurTimeHi)) << 32) + TMR_RetnContext.CurTimeLo);
}

/**
   @brief Calculate the real compare value for the comparator.

   The comparator has a valid compare range. If the timeout value is out
   of the valid range. The match value must set to the max valid range.

   @param[in]  Comp        Specify a comparator.
   @param[in]  Now         The current time.
   @param[in]  Timeout     The timeout value for the comparator.
   @param[out] MatchValue  The real match value for the comparator.

   @return The real match value of the comparator.
*/
static uint8_t TMR_CompCalculateMatchValue(qapi_TMR_Comp_Instance_t Comp, uint64_t Now, uint64_t Timeout, uint32_t *MatchValue)
{
    uint32_t MaxCompRange;
    uint8_t  Range = TMR_TIMEOUT_IN_RANGE;

    if (Comp >= SMALL_COMPARATOR0_ID)
    {
        MaxCompRange = MAX_SMALL_COMP_RANGE;
    }
    else
    {
        MaxCompRange = MAX_BIG_COMP_RANGE;
    }

    if (Timeout > MaxCompRange)
    {
        Timeout = MaxCompRange;
        Range = TMR_TIMEOUT_OUT_OF_RANGE;
    }
    else if (Timeout < TMR_COMPARATOR_MAX_TOLERANCE_IN_US)
    {
        /* The compare value may be late if the timeout value is too small. */ 
        Range = TMR_TIMEOUT_CLOSE_TO_NOW;
    }

    *MatchValue = (uint32_t)(Now + Timeout);

    return Range;
}

/**
   @brief Reload compare value for the comparator when expiry.

   @param[in]  Comp        Specify a comparator.
   @param[in]  Now         The current time.
   @param[in]  Timeout     The timeout value for the comparator.
*/
static void TMR_CompReload(qapi_TMR_Comp_Instance_t Comp, uint64_t Now, uint64_t Timeout)
{
    uint8_t  Range;
    uint32_t MatchValue;
    uint32_t Tolerance = 0;

    Range = TMR_CompCalculateMatchValue(Comp, Now, Timeout, &MatchValue);

    if (Comp >= SMALL_COMPARATOR0_ID)
    {
        /* Set small comparator compare value. */
        TMR_SET_COMP_VALUE((HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID)),
                           MAX_SMALL_COMP_VALUE,
                           (HWIO_AON_CTMR_SMALL_CMPR0_STAT_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID)));
    }
    else
    {
        /* Set big comparator compare value. */
        TMR_SET_COMP_VALUE((HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR + 0x10 * Comp),
                           MAX_BIG_COMP_VALUE,
                           (HWIO_AON_CTMR_BIG_CMPR0_STAT_ADDR + 0x10 * Comp));
    }
}

/**
   @brief Start a comparator.

   @param[in] Comp      Specify a comparator.
   @param[in] Now       The current time.
   @param[in] Timeout   The timeout value for the comparator.
   @param[in] Repeat    Repeat the comparator after comparator expiry or not.
                        true: repeat the comparator. false: run only once.
   @param[in] Duration  The comparator period if it will repeate after expiry .

   @return True if the timeout value is in comparator valid range or false if
           it is out of the comparator valid range.
*/
static qbool_t TMR_CompStart(qapi_TMR_Comp_Instance_t Comp, uint64_t Now, uint64_t Timeout, qbool_t Repeat, uint64_t Duration)
{
    uint32_t Tolerance = 0;
    uint32_t MatchValue;
    uint8_t  Range;

    Range = TMR_CompCalculateMatchValue(Comp, Now, Timeout, &MatchValue);

    /* Clear interrupt events. */
    HWIO_AON_CTMR_INT_CLR_OUT((0x1 << (HWIO_AON_CTMR_INT_CLR_CLR_BIG_CMPR_FIRED_SHFT + Comp))); 

    if (Comp >= SMALL_COMPARATOR0_ID)
    {
        /* Enable small compartor. */
        out_dword(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID),
                  TMR_COMPARATOR_ENABLE_ONCE);

        /* Set small comparator compare value. */
        TMR_SET_COMP_VALUE((HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID)),
                           MAX_SMALL_COMP_VALUE,
                           (HWIO_AON_CTMR_SMALL_CMPR0_STAT_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID)));
    }
    else
    {
        if (Repeat && (Range != TMR_TIMEOUT_OUT_OF_RANGE))
        {   /* Enable the timer-comparator interrupt source to REPEATEDLY
               generate interrupts. First when the compare value equals this
               timer value. Then when the INCREMENTED compare vlaue equals
               the timer value. Only Big comparators have this mode. */
            out_dword(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR + 0x10 * Comp, TMR_COMPARATOR_ENABLE_REPEATE);
            /* Set the INCREMENT value. Only supported by Big comparators. */
            out_dword(HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR + 0x10 * Comp, (uint32_t)Duration);
        }
        else
        {
            /* Enable big comparator to run once. */
            out_dword(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR + 0x10 * Comp, TMR_COMPARATOR_ENABLE_ONCE);
        }

        /* Set big comparator compare value. */
        TMR_SET_COMP_VALUE((HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR + 0x10 * Comp),
                           MAX_BIG_COMP_VALUE,
                           (HWIO_AON_CTMR_BIG_CMPR0_STAT_ADDR + 0x10 * Comp));
    }

    return (Range == TMR_TIMEOUT_OUT_OF_RANGE);
}

/**
   @brief Stop the comparator.

   @param[in]  Comp        Specify a comparator.
*/
static void TMR_CompStop(qapi_TMR_Comp_Instance_t Comp)
{
    /* Disable comparator. */
    if (Comp >= SMALL_COMPARATOR0_ID)
    {
        out_dword(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR + 0x10 * (Comp - SMALL_COMPARATOR0_ID),
                  TMR_COMPARATOR_DISABLE);
    }
    else
    {
        out_dword(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR + 0x10 * Comp, TMR_COMPARATOR_DISABLE);
    }
}

/**
   @brief Vote for the shutdown state of the timer module.
*/
static void TMR_VoteLocalState()
{
    uint8_t          i;
    uint64_t         MiniumExpire = INVALID_EXPIRE_VALUE;
    uint64_t         Now;
    uint32_t         WakeTime = QAPI_PWR_NO_WAKE;
    qapi_PWR_State_t Vote = QAPI_PWR_STATE_SHUTDOWN_E;

    /* Get closest in time non-deferrable comparator. */
    for (i = 0; i < MAX_USABLE_COMPARATORS; i++)
    {
        if (TMR_RetnContext.CompInfo[i] != NULL &&
            TMR_RetnContext.CompInfo[i]->CompState >= TMR_COMP_STATE_RUN_ONCE_E &&
            TMR_RetnContext.CompInfo[i]->CompState <= TMR_COMP_STATE_RUN_REPEATE_MANUAL_E &&
            !(TMR_RetnContext.CompInfo[i]->Flags & TMR_COMPINFO_FLAG_DEFERRABLE))
        {
            if (TMR_RetnContext.CompInfo[i]->Duration <= TMR_COMPARATOR_DURATION_ALLOW_SHUTDOWN)
            {
                Vote = QAPI_PWR_STATE_ACTIVE_E;
                goto TMR_VOTE;
            }

            if (TMR_RetnContext.CompInfo[i]->Expire < MiniumExpire)
            {
                MiniumExpire = TMR_RetnContext.CompInfo[i]->Expire;
            }
        }
    }

    if (MiniumExpire != INVALID_EXPIRE_VALUE)
    {
        Now = TMR_GetCurTime();

        if (MiniumExpire - Now > MAX_HUGE_COMP_RANGE)
        {
            WakeTime = MAX_HUGE_COMP_RANGE;
        }
        else
        {
            WakeTime = (uint32_t)(MiniumExpire - Now);
        }

        /* Convert to time to milliseconds. */
        WakeTime /= 1000;
    }

TMR_VOTE:
    qapi_PWR_Vote_Local_State(TMR_RetnContext.Ballot, Vote, WakeTime);
}

/**
   @brief Timer shutdown callback function before going to deep sleep.

   @param[in] UserParam  User specified parameter provided when the callback
                         is registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t TMR_ShutdownCallback(void *UserParam)
{
    /* Disable timer. */
    TMR_Disable();
    TMRInitDone = false;

    return true;
}

/**
   @brief Timer wakeup callback function when wakeup from deep sleep or
          shutdown is aborted.

   @param[in] ShutdownAborted  Flag indicating if this function is called because
                               a shutdown was aborted (true) or because the
                               subsystem woke from shutdown (false).
   @param[in] UserParam        User specified parameter provided when the callback
                               is registered.
*/
static void TMR_WakeupCallback(qbool_t ShutdownAborted, void *UserParam)
{
    qbool_t  Repeat;
    uint64_t Now;
    uint64_t Timeout;
    uint8_t  i;

    /* Timer sync and int. */
    TMR_Init();

    /* Restart comparator. */
    for (i = 0; i < MAX_USABLE_COMPARATORS; i++)
    {
        if (TMR_RetnContext.CompInfo[i] != NULL &&
            TMR_RetnContext.CompInfo[i]->CompState >= TMR_COMP_STATE_RUN_ONCE_E &&
            TMR_RetnContext.CompInfo[i]->CompState <= TMR_COMP_STATE_RUN_REPEATE_MANUAL_E)
        {
            if (TMR_RetnContext.CompInfo[i]->CompState == TMR_COMP_STATE_RUN_REPEATE_AUTO_E)
            {
                Repeat = true;
            }
            else
            {
                Repeat = false;
            }

            Now = TMR_GetCurTime();
            if (TMR_RetnContext.CompInfo[i]->Expire >= (Now + TMR_COMPARATOR_TOLERANCE_IN_US))
            {
                Timeout = TMR_RetnContext.CompInfo[i]->Expire - Now;
            }
            else
            {
                Timeout = TMR_COMPARATOR_TOLERANCE_IN_US;
                /* If expire, start big comparator once for the first time. Because autoload will
                   result in the big comparator actual expire time later than expect expire time
                   every cycle. */
                if (TMR_RetnContext.CompInfo[i]->CompState == TMR_COMP_STATE_RUN_REPEATE_AUTO_E)
                {
                    TMR_RetnContext.CompInfo[i]->CompState = TMR_COMP_STATE_RUN_REPEATE_SEMIAUTO_E;
                    Repeat = false;
                }
            }

            (void)TMR_CompStart(i, Now, Timeout, Repeat, TMR_RetnContext.CompInfo[i]->Duration);
        }
    }

    TMR_VoteLocalState();
}

/**
   @brief Timer interrupt Callback.

   Should do minimal processing here.

   @param[in] Interrupt  Interrupt that the callback should handle as defined by
                         QAPI_PWR_AON_INTERRUPT_TYPE_*.  Only one bit will be
                         set.
   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.
*/
static void TMR_IntHandler(uint32_t Interrupt, void *UserParam)
{
    uint32_t Int0Status;
    uint32_t i;
    uint64_t Now;

    Int0Status = HWIO_AON_CTMR_INT0_MAPPED_STAT_IN;
    /* Clear interrupt status. */
    HWIO_AON_CTMR_INT_CLR_OUT(Int0Status);

    Now = TMR_GetCurTime();

    for (i = 0; i < MAX_USABLE_COMPARATORS; i++)
    {
        /* On-time comparator interrupt occured. */
        if ((Int0Status & (1 << i)))
        {
            if (TMR_RetnContext.CompInfo[i]->CompState >= TMR_COMP_STATE_RUN_ONCE_E &&
                TMR_RetnContext.CompInfo[i]->CompState <= TMR_COMP_STATE_RUN_REPEATE_MANUAL_E)
            {
                if (TMR_RetnContext.CompInfo[i]->Expire <= Now)
                {
                    if (TMR_RetnContext.CompInfo[i]->CompState == TMR_COMP_STATE_RUN_ONCE_E)
                    {
                        TMR_RetnContext.CompInfo[i]->CompState = TMR_COMP_STATE_EXPIRE_E;
                        TMR_RetnContext.CompInfo[i]->Duration = 0;
                        TMR_RetnContext.CompInfo[i]->Expire = 0;
                    }
                    else
                    {
                        TMR_RetnContext.CompInfo[i]->Expire += TMR_RetnContext.CompInfo[i]->Duration;

                        /* If the timer is deferrable, Expire may be far in the 
                           past.  We have to round it up to the next multiple reload periods. */
                        if (TMR_RetnContext.CompInfo[i]->Expire <= Now)
                        {
                            TMR_RetnContext.CompInfo[i]->Expire = Now + TMR_RetnContext.CompInfo[i]->Duration - ((Now - TMR_RetnContext.CompInfo[i]->Expire) % TMR_RetnContext.CompInfo[i]->Duration);
                        }

                        if (TMR_RetnContext.CompInfo[i]->CompState == TMR_COMP_STATE_RUN_REPEATE_MANUAL_E)
                        {
                            TMR_CompReload(i, Now, TMR_RetnContext.CompInfo[i]->Expire - Now);
                        }
                        else if (TMR_RetnContext.CompInfo[i]->CompState == TMR_COMP_STATE_RUN_REPEATE_SEMIAUTO_E)
                        {
                            (void)TMR_CompStart(i, Now, TMR_RetnContext.CompInfo[i]->Expire - Now, true, TMR_RetnContext.CompInfo[i]->Duration);
                            TMR_RetnContext.CompInfo[i]->CompState = TMR_COMP_STATE_RUN_REPEATE_AUTO_E;
                        }
                    }

                    /* Call user registered callback. */
                    if (TMR_RetnContext.CompInfo[i]->CompCB)
                    {
                        TMR_RetnContext.CompInfo[i]->CompCB(TMR_RetnContext.CompInfo[i]->CompParam);
                    }

                    TMR_VoteLocalState();
                }
                else
                {
                    /* Its duration is out of range, reload comp value. */
                    TMR_CompReload(i, Now, TMR_RetnContext.CompInfo[i]->Expire - Now);
                }
            }
        }
    }
}

/**
   @brief Initialize timer module.

   This function must be called after cold boot or warm boot.

   @return
   - QAPI_OK              -- The timer module is initialized successfully.
   - QAPI_ERR_NO_RESOURCE -- Resource allocation error.
*/
static qapi_Status_t TMR_Init()
{
    uint64_t      CurTime;
    qapi_Status_t Status;

    if (TMRInitDone)
    {
        return QAPI_OK;
    }

    /* Sync timer after cold boot and deep sleep. */
    CurTime = TMR_Enable();

    /* Map ON-TIME BIG Comparator0/1/2/3 to INT0. */
    HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_OUT(0x0);
    /* Map ON-TIME SMALL Comparator0/1/2/3/4/5/6/7 to INT0. */
    HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_OUT(0x0);
    /* Clear interrupt status. */
    HWIO_AON_CTMR_INT_CLR_OUT(HWIO_AON_CTMR_INT_CLR_RMSK);
    /* Enable INT0. */
    HWIO_AON_CTMR_INT0_CTRL_OUT(0x1);

    if (!TMR_RetnContext.RetnInit)
    {
        /* Acquire ballot. */
        TMR_RetnContext.Ballot = qapi_PWR_Acquire_Ballot();

        /* Register shutdown callback and wakeup callback. */
        TMR_RetnContext.ShutdownCBHandle = qapi_PWR_Register_Shutdown_Callbacks(TMR_ShutdownCallback, TMR_WakeupCallback, TMR_SHUDOWN_CALLBACK_PRIORITY, NULL);

        Status = qapi_PWR_Register_AON_Interrupt(QAPI_PWR_AON_INT_CETMR, TMR_IntHandler, NULL);

        if (TMR_RetnContext.Ballot == 0 || TMR_RetnContext.ShutdownCBHandle == NULL || Status != QAPI_OK)
        {
            if (TMR_RetnContext.Ballot != 0)
            {
                qapi_PWR_Release_Ballot(TMR_RetnContext.Ballot);
                TMR_RetnContext.Ballot = 0;
            }

            if (TMR_RetnContext.ShutdownCBHandle != NULL)
            {
                qapi_PWR_Unregister_Callback(TMR_RetnContext.ShutdownCBHandle);
                TMR_RetnContext.ShutdownCBHandle = NULL;
            }

            if (Status == QAPI_OK)
            {
                qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_CETMR);
            }

            return QAPI_ERR_NO_RESOURCE;
        }

        TMR_RetnContext.CurTimeHi = (uint32_t)(CurTime >> 32);
        TMR_RetnContext.CurTimeLo = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;
        TMR_RetnContext.RetnInit = true;
    }
    else
    {
         /* Restore current time. */
        if ((((uint64_t)((TMR_RetnContext.CurTimeHi) & GBLTMR_MSB_VAL_BMSK) << 32) | (TMR_RetnContext.CurTimeLo)) > CurTime)
        {
            TMR_RetnContext.CurTimeHi += (GBLTMR_MSB_VAL_BMSK + 1);
        }

        TMR_RetnContext.CurTimeLo = (uint32_t)CurTime;
        TMR_RetnContext.CurTimeHi = ((TMR_RetnContext.CurTimeHi & (~GBLTMR_MSB_VAL_BMSK)) | ((uint32_t)(CurTime >> 32)));
    }

    TMRInitDone = true;

    return QAPI_OK;
}

#ifdef TMR_DEINIT
/**
   @brief De-initialize timer module.
*/
static void TMR_Deinit()
{
    uint8_t i;

    if (!TMRInitDone)
    {
        return;
    }

    /* Stop the running comparators. */
    for (i = 0; i < MAX_USABLE_COMPARATORS; i++)
    {
        if (TMR_RetnContext.CompInfo[i] != NULL)
        {
            TMR_CompStop(i);

            qapi_Free(TMR_RetnContext.CompInfo[i]);
            TMR_RetnContext.CompInfo[i] = NULL;
        }
    }

    TMR_VoteLocalState();

    qapi_PWR_Unregister_Callback(TMR_RetnContext.ShutdownCBHandle);
    qapi_PWR_Release_Ballot(TMR_RetnContext.Ballot);
    memset(&TMR_RetnContext, 0, sizeof(TMR_RetnContext_t));

    qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_CETMR);
    /* Disable INT0. */
    HWIO_AON_CTMR_INT0_CTRL_OUT(0);
    /* Disable CETimer. */
    TMR_Disable();

    TMRInitDone = false;
}
#endif

/**
   @brief Initialize timer module.

   This function should be called before any other timer functions.

   Note that if timer module is to be used cross shutdown state, HFCLK source
   must be switched to HFXTAL before this function is called.

   @return
   - QAPI_OK              -- The timer module is initialized successfully.
   - QAPI_ERR_NO_RESOURCE -- Resource allocation error.
*/
qapi_Status_t qapi_TMR_Init()
{
    return TMR_Init();
}

/**
   @brief Get current timer value.

   @return Current timer value in microseconds.
*/
uint64_t qapi_TMR_Get_Current_Time()
{
    if (!TMRInitDone)
    {
        return 0;
    }

    return TMR_GetCurTime();
}

/**
   @brief Delay for some time in microseconds.

   It will loop here until the delayed time expires.

   @param[in] UsDelay  The delay time in microseconds.
*/
void qapi_TMR_Delay_Us(uint32_t UsDelay)
{
    uint32_t StartUs;

    if (!TMRInitDone)
    {
        return;
    }

    StartUs = HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN;

    while (HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN - StartUs < UsDelay);
}

/**
   @brief Initialize a comparator.

   This function should be called before starting a comparator. It takes a
   free comparator and registers user callback function for the comparator.

   @param[out] Comp        Pointer to return the comparator instance.
   @param[in]  CompCB      The callback function when timer comparator expires.
   @param[in]  UserParam   User specified parameter for callback function.
   @param[in]  Deferrable  Deterimines if the timer should be deferrable.  If 
                           true, the timer will not wake APSS from shutdown 
                           when it expires.

   @return
   - QAPI_OK                -- The comparator is initialized successfully.
   - QAPI_ERROR             -- Timer module is not initialized yet.
   - QAPI_ERR_INVALID_PARAM -- One ore more parameters are invalid.
   - QAPI_ERR_NO_MEMORY     -- Memory allocation error.
   - QAPI_ERR_NO_RESOURCE   -- There is no free comparator.
*/
qapi_Status_t qapi_TMR_Comp_Init(qapi_TMR_Comp_Instance_t *Comp, qapi_TMR_Comp_CB_t CompCB, void *UserParam, qbool_t Deferrable)
{
    uint8_t         i;
    TMR_CompInfo_t *Info;

    if (!TMRInitDone)
    {
        return QAPI_ERROR;
    }

    if (Comp == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    for (i = 0; i < MAX_USABLE_COMPARATORS; i++)
    {
        if (TMR_RetnContext.CompInfo[i] == NULL)
        {
            Info = qapi_Malloc_Retain(sizeof(TMR_CompInfo_t));
            if (Info == NULL)
            {
                return QAPI_ERR_NO_MEMORY;
            }

            memset(Info, 0, sizeof(TMR_CompInfo_t));
            Info->CompState = TMR_COMP_STATE_INIT_E;
            Info->CompCB = CompCB;
            Info->CompParam = UserParam;
            Info->Duration = 0;
            Info->Expire = 0;
            TMR_RetnContext.CompInfo[i] = Info;
            if (Deferrable)
            {
                Info->Flags |= TMR_COMPINFO_FLAG_DEFERRABLE;
            }

            *Comp = i;
            return QAPI_OK;
        }
    }

    return QAPI_ERR_NO_RESOURCE;
}

/**
   @brief Deinitialize a comparator.

   This function stops the comparator and unregisters user callback. It should
   be called to free the comparator for other usage when it is not needed anymore.

   @param[in] Comp  Specify a comparator to free.

   @return
   - QAPI_OK                -- The comparator is de-initialized successfully.
   - QAPI_ERR_INVALID_PARAM -- One ore more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Comp_Deinit(qapi_TMR_Comp_Instance_t Comp)
{
    if (Comp >= MAX_USABLE_COMPARATORS || TMR_RetnContext.CompInfo[Comp] == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    /* Disable comparator. */
    TMR_CompStop(Comp);

    qapi_Free(TMR_RetnContext.CompInfo[Comp]);
    TMR_RetnContext.CompInfo[Comp] = NULL;

    TMR_VoteLocalState();

    return QAPI_OK;
}

/**
   @brief Start a comparator to expire after a speficied period.

   @param[in] Comp     Specify a comparator to start.
   @param[in] Timeout  The timeout value in microseconds.
   @param[in] Repeat   Repeat the comparator after comparator expiry or not.
                       TRUE: repeat the comparator, FALSE: run only once.

   @return
   - QAPI_OK                            -- The comparator is started successfully.
   - QAPI_ERR_INVALID_PARAM             -- One ore more parameters are invalid.
   - QAPI_ERR_NOT_SUPPORTED             -- Timeout value is too small to be supported.
   - QAPI_TMR_ERROR_COMP_IMPROPER_STATE -- The comparator is in an improper state.
*/
qapi_Status_t qapi_TMR_Comp_Start(qapi_TMR_Comp_Instance_t Comp, uint64_t Timeout, qbool_t Repeat)
{
    TMR_CompInfo_t *CompInfo;
    qbool_t         OutOfRange;
    uint64_t        Now;

    if (Comp >= MAX_USABLE_COMPARATORS || TMR_RetnContext.CompInfo[Comp] == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (Timeout < TMR_COMPARATOR_TOLERANCE_IN_US)
    {
        return QAPI_ERR_NOT_SUPPORTED;
    }

    CompInfo = TMR_RetnContext.CompInfo[Comp];

    if (CompInfo->CompState >= TMR_COMP_STATE_RUN_ONCE_E &&
        CompInfo->CompState <= TMR_COMP_STATE_RUN_REPEATE_MANUAL_E)
    {
        return QAPI_TMR_ERROR_COMP_IMPROPER_STATE;
    }

    qapi_TSK_Enter_Critical();

    Now = TMR_GetCurTime();
    OutOfRange = TMR_CompStart(Comp, Now, Timeout, Repeat, Timeout);

    if (Repeat)
    {
        if ((Comp < SMALL_COMPARATOR0_ID) && (!OutOfRange))
        {
            CompInfo->CompState = TMR_COMP_STATE_RUN_REPEATE_AUTO_E;
        }
        else
        {
            CompInfo->CompState = TMR_COMP_STATE_RUN_REPEATE_MANUAL_E;
        }
    }
    else
    {
        CompInfo->CompState = TMR_COMP_STATE_RUN_ONCE_E;
    }

    CompInfo->Duration = Timeout;
    CompInfo->Expire = Now + Timeout;

    qapi_TSK_Exit_Critical();

    TMR_VoteLocalState();

    return QAPI_OK;
}

/**
   @brief Stop a comparator.

   @param[in] Comp  Specify a comparator to stop.

   @return
   - QAPI_OK                -- The comparator is stopped successfully.
   - QAPI_ERR_INVALID_PARAM -- One ore more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Comp_Stop(qapi_TMR_Comp_Instance_t Comp)
{
    TMR_CompInfo_t *CompInfo;

    if (Comp >= MAX_USABLE_COMPARATORS || TMR_RetnContext.CompInfo[Comp] == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    CompInfo = TMR_RetnContext.CompInfo[Comp];

    /* Disable comparator. */
    TMR_CompStop(Comp);

    CompInfo->Duration = 0;
    CompInfo->Expire = 0;
    CompInfo->CompState = TMR_COMP_STATE_STOP_E;

    TMR_VoteLocalState();

    return QAPI_OK;
}

/**
   @brief Get the comparator infomation.

   @param[in]  Comp  Specify a comparator.
   @param[in]  Info  Specify the type of information needed from the comparator.
   @param[out] Data  Data associated with the Info.

   @return
   - QAPI_OK                -- The comparator info is got successfully.
   - QAPI_ERROR             -- Get comparator info failed.
   - QAPI_ERR_INVALID_PARAM -- One ore more parameters are invalid.
*/
qapi_Status_t qapi_TMR_Get_Comp_Info(qapi_TMR_Comp_Instance_t Comp, qapi_TMR_Comp_Info_t Info, uint64_t *Data)
{
    TMR_CompInfo_t *CompInfo;
    uint64_t        Now;

    if (Comp >= MAX_USABLE_COMPARATORS || TMR_RetnContext.CompInfo[Comp] == NULL ||
        Info > QAPI_TMR_COMP_INFO_REMAINING_E || Data == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    CompInfo = TMR_RetnContext.CompInfo[Comp];

    if (CompInfo->CompState >= TMR_COMP_STATE_RUN_ONCE_E &&
        CompInfo->CompState <= TMR_COMP_STATE_RUN_REPEATE_MANUAL_E)
    {
        switch (Info)
        {
            case QAPI_TMR_COMP_INFO_ABS_EXPIRY_E:
                *Data = CompInfo->Expire;
                break;

            case QAPI_TMR_COMP_INFO_DURATION_E:
                *Data = CompInfo->Duration;
                break;

            case QAPI_TMR_COMP_INFO_REMAINING_E:
                Now = TMR_GetCurTime();
                *Data = CompInfo->Expire - Now;
                break;

            default:
                break;
        }

        return QAPI_OK;
    }

    return QAPI_ERROR;
}

