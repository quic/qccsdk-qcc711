/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "stringl.h"
#include "qapi_power.h"
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_timer.h"
#include "qapi_mtp.h"
#include "qapi_wdog.h"
#include "qapi_nvm.h"
#include "ram.h"
#include "qcc710.h"
#include "HALhwio.h"
#include "hwio_aon.h"
#include "hwio_gcc.h"
#include "hwio_pmu.h"
#include "hwio_tlmm.h"
#include "cmsis_compiler.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
extern const size_t __RetnRAMStart;       /**< Linker symbol for the start of the retained RAM.  */
extern const size_t __RetnRAMEnd;         /**< Linker symbol for the end of the retained RAM. */
extern const size_t __VectorTableStart;   /**< Linker symbol for the star of the ROM vector table.  */
extern const size_t __VectorTableEnd;     /**< Linker symbol for the end of the ROM vector table.  */

#define RETN_RAM_START                                                  ((void *)&__RetnRAMStart)                                     /**< Start of retained RAM. */
#define RETN_RAM_END                                                    ((void *)&__RetnRAMEnd)                                       /**< End of retained RAM. */
#define RETN_RAM_SIZE                                                   ((uint32_t)&__RetnBssEnd - (uint32_t)&__RetnRAMStart)         /**< Size of retained RAM. */
#define VECTOR_TABLE_START                                              ((void *)&__VectorTableStart)                                 /**< Start of ROM vector table. */
#define VECTOR_TABLE_END                                                ((void *)&__VectorTableEnd)                                   /**< End of ROM vector table. */
#define VECTOR_TABLE_SIZE                                               ((uint32_t)&__VectorTableEnd - (uint32_t)&__VectorTableStart) /**< Size of ROM vector table. */

#ifdef __ICCARM__

#pragma section = ".bss.retain"
#pragma section = ".bss.retain_init"
#pragma section = ".retained.text"
#pragma section = ".retained.text_init"

#define RETN_BSS_START                                                  ((void *)__section_begin(".bss.retain"))                      /**< Start of the retained bss region. */
#define RETN_BSS_END                                                    ((void *)__section_end(".bss.retain"))                        /**< Start of the retained bss region. */
#define RETN_BSS_SIZE                                                   ((uint32_t)__section_size(".bss.retain"))                     /**< Size of the retained bss region. */
#define RETN_TEXT_START                                                 ((void *)__section_begin(".retained.text"))                   /**< Start of the retained text region. */
#define RETN_TEXT_END                                                   ((void *)__section_end(".retained.text"))                     /**< Start of the retained text region. */
#define RETN_TEXT_LOAD                                                  ((void *)__section_begin(".retained.text_init"))              /**< Start of the retained text load region. */
#define RETN_TEXT_SIZE                                                  ((uint32_t)__section_size(".retained.text"))                  /**< Size of the retained text region. */

#else

extern const size_t __RetnTextStart;      /**< Linker symbol for the start of the retained text region. */
extern const size_t __RetnTextEnd;        /**< Linker symbol for the end of the retained text region. */
extern const size_t __rtext;              /**< Linker symbol for the start of the retained text load region. */
extern const size_t __RetnBssStart;       /**< Linker symbol for the start of the retained bss region. */
extern const size_t __RetnBssEnd;         /**< Linker symbol for the end of the retained bss region. */

#define RETN_BSS_START                                                  ((void *)&__RetnBssStart)                                     /**< Start of the retained bss region. */
#define RETN_BSS_END                                                    ((void *)&__RetnBssEnd)                                       /**< End of the retained bss region. */
#define RETN_BSS_SIZE                                                   ((uint32_t)&__RetnBssEnd - (uint32_t)&__RetnBssStart)         /**< Size of the retained bss region. */
#define RETN_TEXT_START                                                 ((void *)&__RetnTextStart)                                    /**< Start of the retained text region. */
#define RETN_TEXT_END                                                   ((void *)&__RetnTextEnd)                                      /**< End of the retained text region. */
#define RETN_TEXT_LOAD                                                  ((void *)&__rtext)                                            /**< Start of the retained text load region. */
#define RETN_TEXT_SIZE                                                  ((uint32_t)&__RetnTextEnd - (uint32_t)&__RetnTextStart)       /**< Size of the retained text region. */

#endif

#define BALLOT_LIST_SIZE                                                ((QAPI_PWR_MAX_BALLOTS + 31) / 32)

#define SYS_WAKEUP_TIME                                                 (40)         /**< System wakeup time in units of 64us. */

#ifndef MINIMUM_SHUTDOWN_TIME
   #define MINIMUM_SHUTDOWN_TIME                                        (5000)       /** Minimum time to wake in microseconds where the shutdown state will be
                                                                                         entered. */
#endif

#define TIME_IN_PAST_THRESHOLD                                          (0xFFF00000) /** Threshold used to determine if a wake time is in the past. */

#define PWR_INDEX_TO_BALLOT(_index_)                                    ((qapi_PWR_Ballot_t)((_index_) + 1))
#define PWR_BALLOT_TO_INDEX(_ballot_)                                   ((uint32_t)((_ballot_) - 1))

#define PWR_VLP_VOUT_MAX                                                (9000)
#define PWR_VLP_VOUT_INCREMENT                                          (125)
#define PWR_VLP_VOUT_OFFSET                                             (PWR_VLP_VOUT_MAX / PWR_VLP_VOUT_INCREMENT)

/* RAM Retention register definitions. */
#define HWIO_AON_PME_RAM_RETN_MASK                                      (0x03)
#define HWIO_AON_PME_RAM_RETN_OFF                                       (0x00)
#define HWIO_AON_PME_RAM_RETN_RETAINED                                  (0x01)
#define HWIO_AON_PME_RAM_RETN_ACTIVE                                    (0x03)

#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_SHIFT                        (4)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_MASK                         (HWIO_AON_PME_RAM_RETN_MASK     << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_OFF                          (HWIO_AON_PME_RAM_RETN_OFF      << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_RETAINED                     (HWIO_AON_PME_RAM_RETN_RETAINED << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_ACTIVE                       (HWIO_AON_PME_RAM_RETN_ACTIVE   << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_SHIFT)

#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_SHIFT                        (6)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_MASK                         (HWIO_AON_PME_RAM_RETN_MASK     << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_OFF                          (HWIO_AON_PME_RAM_RETN_OFF      << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_RETAINED                     (HWIO_AON_PME_RAM_RETN_RETAINED << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_SHIFT)
#define HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_ACTIVE                       (HWIO_AON_PME_RAM_RETN_ACTIVE   << HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_SHIFT)

/* Reset register definitions. */
#define HWIO_AON_PME_APPS_RESET_SUBSYSTEM_RESET                         (0x00b4eb4e)
#define HWIO_AON_PME_APPS_RESET_SOC_COLD_RESET                          (0x00d1ed1e)

/* Reset reason register definitions. */
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_POWER_ON_RESET             (0x0)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_VDIO_EVENT      (0x1)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_SOFTWARE        (0x2)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_BROWNOUT        (0x3)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_LONG_PRESS_MFP  (0x4)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_ROT_WATCHDOG    (0x5)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_BT_WATCHDOG     (0x6)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_APSS_WATCHDOG   (0x7)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_SOFTWARE        (0x8)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_ROT_WATCHDOG    (0x9)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_BT_WATCHDOG     (0xA)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_APSS_WATCHDOG   (0xB)
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_SUBSYSTEM_RESET            (0xF)

/* Subsystem request state definitions. */
#define HWIO_AON_PME_REQ_STATE_SHUTDOWN                                 (0)
#define HWIO_AON_PME_REQ_STATE_ACTIVE                                   (3)
#define HWIO_AON_PME_REQ_STATE_BMSK                                     (3)

/* LFCLK source definitions. */
#define HWIO_AON_PME_SOC_CONTROL_SOSC                                   (0)
#define HWIO_AON_PME_SOC_CONTROL_LFXTAL                                 (1)
#define HWIO_AON_PME_SOC_CONTROL_SOSC2                                  (2)
#define HWIO_AON_PME_SOC_CONTROL_GPIO                                   (3)

/* GTMR  definitions. */
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_CAPT_BMSK                       (0x000000001)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_COMP_FIRED_BMSK                      (0x000000001)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_COMP_EARLY_BMSK                      (0x000000002)

/* Remap Register Definitions. */
#define HWIO_AON_PME_APPS_REMAP_OFFSET_RAM_START                        ((((uint32_t)RETN_RAM_START) - 0x20000000) >> 13)
#define HWIO_AON_PME_APPS_REMAP_OFFSET_NVM_START                        ((((uint32_t)QAPI_NVM_APSS_START) - 0x10200000) >> 13)
#define HWIO_AON_PME_APPS_REMAP_SEL_NVM                                 (0x0)
#define HWIO_AON_PME_APPS_REMAP_SEL_RAM                                 (0x1)

/* Number of cycles to loop when VDIO fault occurs. */
#define VDIO_FAULT_BUSYWAIT_CYCLES                                      (32000000/24)


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of the states for turning on the LFXTAL.
*/
typedef enum
{
   lxsTurningOn,
   lxsStabalizing
} LFXTAL_State_t;

/**
   Callback context information used when turning on the XTAL
*/
typedef struct LFXTAL_CallbackContext_s
{
   qapi_PWR_LFXTAL_Enabled_CB_t  Callback;  /**< Function to call when the XTAL is on. */
   void                         *UserParam; /**< User specified callback parameter. */
   LFXTAL_State_t                State;     /**< Current state of the function. */
   uint32_t                      XtalConf;  /**< APSS_XTAL_CONF register settings. */
   qapi_TMR_Comp_Instance_t      Timer;     /**< Handle to a timer comparator. */
   uint32_t                      Delay;     /**< Delay used for turning on the XTAL*/
} LFXTAL_CallbackContext_t;


/**
   Single entry in the callback list.  This list is double-linked as it needs to
   be traversed both forwards and backwards.
*/
typedef struct PWR_CallbackEntry_s
{
   struct PWR_CallbackEntry_s *Next;       /**< Next entry in the list. */
   struct PWR_CallbackEntry_s *Prev;       /**< Prev entry in the list. */
   qapi_PWR_Shutdown_CB_t      ShutdownCB; /**< Function to be called when the system is shutting down. */
   qapi_PWR_Wakeup_CB_t        WakeupCB;   /**< Function to be called when the system is waking up. */
   void                       *UserParam;  /**< User specified callback parameter. */
   uint8_t                     Priority;   /**< Priority of the callback entry. */
} PWR_CallbackEntry_t;

/**
   Structure representing the callback information for an AON interrupt.
*/
typedef struct PWR_AON_Interrupt_s
{
   qapi_PWR_Aon_Int_Handler_CB_t  Callback;  /**< Callback registered for the interrupt or NULL if no callback is registered. */
   void                          *UserParam; /**< User defined callback parameter. */
} PWR_AON_Interrupt_t;

/**
   Format of the fault handler.
*/
typedef void (*PWR_FaultHandler_t)(void);

/**
   Retained context structure for the qapi_power module.
*/
typedef struct PWR_RetainedContext_s
{
   qbool_t               Initialized;                     /**< Flag indicating the qapi_power module is initialized. */
   qbool_t               ShutdownInvoked;                 /**< Flag indicating the power module actually invoked. */
   uint8_t               VMA_Count;                       /**< Count of how many times the LDO has been requested. */
   uint8_t               LFCLK_Count;                     /**< Count of how many times the 32K XTAL has been requested. */
   uint8_t               HFCLK_Count;                     /**< Count of how many times the 32M XTAL has been requested. */
   uint16_t              ShutdownRetn;                    /**< Value of the retained RAM register when the subystem is shutdown. */
   PWR_CallbackEntry_t  *CallbackListHead;                /**< Head of the callback list. */
   PWR_CallbackEntry_t  *CallbackListTail;                /**< Tail of the callback list. */
   qapi_PWR_Election_t   Ballots;                         /**< Bitmask of ballots which are in use. */
   uint32_t              WakeTime[QAPI_PWR_MAX_BALLOTS];  /**< List of wake times corresponding to each ballot. */
   qapi_PWR_Election_t   WakeValid;                       /**< Determines if the wake time for the corresponding ballot is valid. */
   qapi_PWR_Election_t   ElectLocal;                      /**< Elections for the APSS module state. */
   PWR_AON_Interrupt_t   AON_Int[QAPI_PWR_AON_INT_COUNT]; /**< Callback information for the AON interrupts. */
#ifndef DISABLE_VDIO_FAULT_HANDLER
   PWR_FaultHandler_t    FaultHandler;
#endif
} PWR_RetainedContext_t;

typedef struct PWR_Context_s
{
   qbool_t Initialized;
   qbool_t IsColdBoot;
} PWR_Context_t;


/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static PWR_RetainedContext_t PWR_RetainedContext __attribute__((section (".bss.retain")));
static PWR_Context_t PWR_Context;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static void PWR_LFXTAL_TimerCallback(void *UserParam);
static qbool_t PWR_CallShutdownCallbacks(void);
static void PWR_CallWakeupCallbacks(PWR_CallbackEntry_t *CallbackEntry, qbool_t ShutdownAborted);
static qapi_PWR_Election_t PWR_VerifyBallot(qapi_PWR_Ballot_t Ballot);
static qbool_t PWR_ConfigureWakeup(uint32_t WakeTime);
static uint32_t PWR_Get_Time_Now(void);
static void PWR_DisableLFXTAL(void);
static void PWR_Apply_LDO_Adjustments(void);
static qbool_t PWR_IsColdBoot(void);


/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Timer callback for handling LFXTAL startup.

   @param[in] UserParam  User specified callback paramter.  This is the callback
                         context for the LFXTAL startup.

   @return true if shutdown can be entered or false if the shutdown was aborted.
*/
static void PWR_LFXTAL_TimerCallback(void *UserParam)
{
   LFXTAL_CallbackContext_t *CallbackContext;
   qapi_Status_t             Result;
   qbool_t                   Done;

   CallbackContext = (LFXTAL_CallbackContext_t *)UserParam;

   if(CallbackContext->State == lxsTurningOn)
   {
      /* Set the XTAL configuration back to nominal and wait for the clock to
         stabalize. */
      HWIO_APSS_XTAL_CONF_OUT(CallbackContext->XtalConf);
      CallbackContext->State = lxsStabalizing;

      /* Re-start the timer. */
      Result = qapi_TMR_Comp_Start(CallbackContext->Timer, CallbackContext->Delay * 1000, false);
      Done   = (qbool_t)(Result != QAPI_OK);
   }
   else
   {
      /* Signal the 32K clock is stable. */
      HWIO_APSS_XTAL_32K_OK_OUTM(HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_BMSK, HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_BMSK);

      /* Switch to the 32K XTAL. */
      HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK, HWIO_AON_PME_SOC_CONTROL_LFXTAL << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT);

      Result = QAPI_OK;
      Done = true;
   }

   if(Done)
   {
      if (Result != QAPI_OK)
      {
         /* Decrement the LFCLK count.                                  */
         if(PWR_RetainedContext.LFCLK_Count != 0)
         {
            PWR_RetainedContext.LFCLK_Count--;
         }

         /* If LFCLK count is 0 disable the XTAL.                       */
         if(PWR_RetainedContext.LFCLK_Count == 0)
         {
            /* Abort the XTAL start. */
            PWR_DisableLFXTAL();
         }
      }

      /* Make the user callback. */
      (*CallbackContext->Callback)(Result, CallbackContext->UserParam);

      /* Cleanup. */
      qapi_TMR_Comp_Deinit(CallbackContext->Timer);
      qapi_Free(CallbackContext);
   }
}

/**
   @brief Calls the shutown callback for entries in the callback list in
          reverse order.

   This function must be called with interrupts disabled.

   The shutdown callback function for all entries in the callback list will be
   called unless one of them returns an abort.  If a callback signals shutdown
   should be aborted, no further shutdown callbacks will be called and the
   wakup callback will be called with ShutdownAborted = true for any entries
   whose shutdown callback had already been called (except the one that returned
   the abort).

   @return true if shutdown can be entered or false if the shutdown was aborted.
*/
static qbool_t PWR_CallShutdownCallbacks(void)
{
   qbool_t              RetVal;
   PWR_CallbackEntry_t *CallbackEntry;

   /* Flag Power module is actually invoking a shutdown. */
   PWR_RetainedContext.ShutdownInvoked = true;

   RetVal        = true;
   CallbackEntry = PWR_RetainedContext.CallbackListTail;
   while(CallbackEntry != NULL)
   {
      RetVal = ((*(CallbackEntry->ShutdownCB))(CallbackEntry->UserParam));
      if(RetVal)
      {
         CallbackEntry = CallbackEntry->Prev;
      }
      else
      {
         /* Shutdown aborted. */
         PWR_CallWakeupCallbacks(CallbackEntry->Next, true);
         break;
      }
   }

   return(RetVal);
}

/**
   @brief Calls the wakeup callback for entries in the callback list, starting
          at the specified callback entry.

   This function must be called with interrupts disabled.

   @param[in] CallbackEntry    The first callback enrty to call.  This provides a
                               means for PWR_CallShutdownCallbacks() to specify
                               what callbacks need to be called.
                               CallbackListHead should be specified if all
                               entries need to be called.
   @param[in] ShutdownAborted  Flag to use for the Shutdown aborted parameter of
                               the callback functions.  This should be set to
                               true if the calls are made because a shutdown
                               function returned abort or if the system woke
                               before being shutdown.
*/
static void PWR_CallWakeupCallbacks(PWR_CallbackEntry_t *CallbackEntry, qbool_t ShutdownAborted)
{
   /* Flag Power module is no longer invoking a shutdown. */
   PWR_RetainedContext.ShutdownInvoked = false;

   while(CallbackEntry != NULL)
   {
      (*(CallbackEntry->WakeupCB))(ShutdownAborted, CallbackEntry->UserParam);
      CallbackEntry = CallbackEntry->Next;
   }
}

/**
   @brief Verifies the provided ballot is in use and returns its bitmask.

   @param[in] Ballot  Ballot provided by the user.

   @return The bitmask for the ballot or zero if the ballot is invalid.
*/
static qapi_PWR_Election_t PWR_VerifyBallot(qapi_PWR_Ballot_t Ballot)
{
   qapi_PWR_Election_t RetVal;

   if((Ballot > 0) && (Ballot < QAPI_PWR_MAX_BALLOTS))
   {
      RetVal = (qapi_PWR_Election_t)(1 << PWR_BALLOT_TO_INDEX(Ballot));
   }
   else
   {
      RetVal = (qapi_PWR_Election_t)0;
   }

   return(RetVal);
}

/**
   @brief Configure to GTMR to wakeup the system.

   @param[in] AbsTime  Sleep duraiton after which system should be wakeup.

   @return true if the timer was setup successfully or false if the time was in
           the past.
*/
static qbool_t PWR_ConfigureWakeup(uint32_t AbsTime)
{
   /* Unmask HUGE_Comparator_0 on-time and early-while-waking interrupt. */
   HWIO_AON_GBLTMR_SLV_INT_UNMASK_OUT(HWIO_AON_GBLTMR_SLV_SWCAPT_COMP_FIRED_BMSK | HWIO_AON_GBLTMR_SLV_SWCAPT_COMP_EARLY_BMSK);

   /* Clear interrupt status and enable the gtmr interrupt. */
   HWIO_AON_GBLTMR_SLV_INT_CLR_OUT(HWIO_AON_GBLTMR_INT_CLR_CLR_BMSK);
   HWIO_AON_GBLTMR_SLV_INT_CTRL_OUT(1);

   /* Enable HUGE-Comparator run once. */
   HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_OUT(1);

   /* Set Compare value. */
   HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_OUT(AbsTime & HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_CMPR_VAL_BMSK);

   /* Make sure the time wasn't late. */
   return((qbool_t)(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_INM(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_LATE_DET_BMSK) == 0));
}

/**
   @brief Provides the current time as a reference for the wake time.

   @return current tick in microseconds.
*/
static uint32_t PWR_Get_Time_Now(void)
{
   uint32_t RetVal;

   /* Capture the timer value. */
   HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(1);
   while(!HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_INM(HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_CAPT_BMSK));
   RetVal = HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_IN;
   HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(0);

   return(RetVal);
}

/**
   @brief Disables the LFXTAL.
*/
static void PWR_DisableLFXTAL(void)
{
   HWIO_APSS_XTAL_32K_OK_OUT(0);
   HWIO_APSS_XTAL_CTRL_OUT(0);
   HWIO_APSS_XTAL_CONF_OUTM(HWIO_APSS_XTAL_CONF_XTAL_SPEEDUP_EN_BMSK, 0);
}

/**
   @brief Reads LDO values from MTP and applies them to the LDO registers.
*/
static void PWR_Apply_LDO_Adjustments(void)
{
    const uint8_t LDO_DIG_SIGN_MASK = 0x8;
    const uint8_t LDO_DIG_VALUE_MASK = 0x7;

    const uint8_t VOUT_BASE_VALUE = 0x13;

    uint8_t ldo_dig_offset;
    uint32_t vout_adj;

    /* Write the LDO_VMA_SEL_PT bit if present in MTP. */
    if (QAPI_MTP_APSS_RW_PTR->Xtal32kCfg_LdoVmaSelPt & QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_BITMASK)
    {
        HWIO_APSS_LDO_VMA_AON_CONF_OUTM(HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_PT_BMSK, HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_PT_BMSK);
    }
    else
    {
        HWIO_APSS_LDO_VMA_AON_CONF_OUTM(HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_PT_BMSK, 0);
    }

    /* Calculate the right value based on LDO_DIG_OFFSET and write it to the correct registers. */
    ldo_dig_offset = QAPI_MTP_APSS_RO_PTR->LdoDigOffset;

    /* LDO_DIG_OFFSET is a 4 bit value where the upper bit is a sign bit, but not in 2s-complement.
       If this bit is set, it means the lower 3 bits are subtracted instead of added. */
    if (ldo_dig_offset & LDO_DIG_SIGN_MASK)
    {
        vout_adj = VOUT_BASE_VALUE - (ldo_dig_offset & LDO_DIG_VALUE_MASK);
    }
    else
    {
        vout_adj = VOUT_BASE_VALUE + (ldo_dig_offset & LDO_DIG_VALUE_MASK);
    }

    HWIO_APSS_PLA_CONFIG_0_OUTM(HWIO_APSS_PLA_CONFIG_0_VDIG_PLA_SEL_VOUT_BMSK, vout_adj << HWIO_APSS_PLA_CONFIG_0_VDIG_PLA_SEL_VOUT_SHFT);
    HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_OUTM(HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_SEL_VOUT_TARGET_BMSK, vout_adj << HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_SEL_VOUT_TARGET_SHFT);
}

/**
   @brief Determine if this is a cold boot before the power module is
          intialized.

   @return True if this is a cold boot or false if it is a warm boot.
*/
static qbool_t PWR_IsColdBoot(void)
{
   qbool_t  RetVal;
   uint32_t RegValue;

   RetVal   = true;
   RegValue = HWIO_AON_PME_APPS_RAM_RETN_IN;
   /* Check if some memory was retained. */
   if((RegValue & (HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_MASK | HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_MASK)) != 0)
   {
      /* RAM was retained, make sure the power module was initialized and the
         retention register matches the expected value that was stored away. */
      if((PWR_RetainedContext.Initialized) && (PWR_RetainedContext.ShutdownRetn == RegValue))
      {
         /* Finally make sure that the power module invoked the shutdown.*/
         if(PWR_RetainedContext.ShutdownInvoked)
         {
            RetVal = false;
         }
      }
   }

   return(RetVal);
}

/**
   @brief AON Interrupt handler.
*/
void AON_IntHandler(void)
{
   int32_t  Interrupt;
   uint32_t Pending;
   uint32_t Enabled;

   /* Read the pending interrupts and mask it off with what is enabled. */
   Enabled = HWIO_AON_PME_APPS_IRQ_EN_IN;
   Pending = HWIO_AON_PME_APPS_IRQ_PENDING_INM(Enabled);

   /* Loop through and call the callback for any pending interrupts. Process the
      list in reverse order so the CETMR is handled first. */
   for(Interrupt = QAPI_PWR_AON_INT_COUNT - 1; Interrupt >= 0; Interrupt --)
   {
      /* Determine which interrupts are pending. */
      if(Pending & (1 << Interrupt))
      {
         /* Clear the interrupt. */
         qapi_PWR_Clear_AON_Int_Pending(Interrupt);

         if(PWR_RetainedContext.AON_Int[Interrupt].Callback != NULL)
         {
            /* Call the registered function. */
            (*(PWR_RetainedContext.AON_Int[Interrupt].Callback))((uint32_t)Interrupt, PWR_RetainedContext.AON_Int[Interrupt].UserParam);
         }
      }
   }
}

#ifndef DISABLE_VDIO_FAULT_HANDLER

/**
   @brief VDIO Fault handler.
*/
__attribute__((section (".retained.text"))) void VdioFaultHandler(void)
{
   volatile int32_t busywait_cycles;

   /* Check for a VDIO Error */
   if(HWIO_AON_PME_APPS_IRQ_PENDING_IN & HWIO_AON_PME_APPS_IRQ_PENDING_VDIO_BMSK)
   {
      /* Select SOSC as the clock source. */
      HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK, (HWIO_AON_PME_SOC_CONTROL_SOSC << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT));

      /* Wait for roughly 500 ms and then reset the SoC when the VDIO
       * interrupt is pending */
      for(busywait_cycles = VDIO_FAULT_BUSYWAIT_CYCLES; busywait_cycles > 0; busywait_cycles--) {}

      HWIO_AON_PME_APPS_RESET_OUT(HWIO_AON_PME_APPS_RESET_SOC_COLD_RESET);

      while(1) {}
   }

   PWR_RetainedContext.FaultHandler();
}

#endif

/**
   @brief Initializes the power module.

   This function is expected to be called first thing in the boot process. It
   will detect if this is a warm or cold boot and initialize the subsystem
   accordingly.

   For a cold boot, the retained RAM region will be initialized. For warm boot,
   all registered wakeup functions will be called to restore the state of the
   subsystem.

   @param[out] IsColdBoot  Set to true of this is a cold boot or false for a
                           warm boot.

   @return QAPI_OK if initialization was successful or a negative value if there
           was an error.
*/
qapi_Status_t qapi_PWR_Initialize(qbool_t *IsColdBoot)
{
   qapi_Status_t RetVal;
   uint32_t      StartTime;
   uint32_t      PME_GTMR_REQUEST_IRQ_MASK = HWIO_AON_PME_APPS_IRQ_EN_GTMR_BMSK | HWIO_AON_PME_APPS_IRQ_EN_REQUEST_BMSK;

#ifndef DISABLE_VDIO_FAULT_HANDLER

   PME_GTMR_REQUEST_IRQ_MASK |= HWIO_AON_PME_APPS_IRQ_EN_VDIO_BMSK;

#endif

   /* Use the RAM retention register to determine if this is a warm or cold boot. */
   PWR_Context.IsColdBoot = PWR_IsColdBoot();

   if(IsColdBoot != NULL)
   {
      *IsColdBoot = PWR_Context.IsColdBoot;
   }

   PWR_Context.Initialized = true;

   /* Initialize the main heap. */
   RetVal = qapi_Initialize_Heap();

   if(RetVal == QAPI_OK)
   {
      if(PWR_Context.IsColdBoot)
      {
         /* Start the switch for the GTMR to use the HFCLK. */
         qapi_PWR_Set_TCLK_Source(true);

         /* Enable TLMM_AON_CTRL.PMU_STATUS_CHECK_BYPASS. */
         HWIO_TLMM_AON_CTRL_OUTM(HWIO_TLMM_AON_CTRL_PMU_STATUS_CHECK_BYPASS_BMSK, HWIO_TLMM_AON_CTRL_PMU_STATUS_CHECK_BYPASS_BMSK);

         /* Make sure AON_PME_SOC_CONTROL.TLMM_ACTIVE bit is zero. */
         HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_TLMM_ACTIVE_BMSK, 0);

         /* Enable the AON GTMR and IPC (REQUEST) interrupt. */
         HWIO_AON_PME_APPS_IRQ_EN_OUTM(PME_GTMR_REQUEST_IRQ_MASK, PME_GTMR_REQUEST_IRQ_MASK);

         /* Apply any needed adjustments to LDO settings. */
         PWR_Apply_LDO_Adjustments();

         /* Verify the blocks the retention memory is valid. */
         if((RETN_RAM_START < RETN_RAM_END) && (RETN_RAM_START >= RAM_APSS_BLOCK_0_START) && (RETN_RAM_END <= RAM_APSS_BLOCK_1_END))
         {
            /* Intialize the retained BSS region and heap. */
            memset(RETN_BSS_START, 0, RETN_BSS_SIZE);

            RetVal = qapi_Initialize_Retain_Heap();

#ifndef DISABLE_VDIO_FAULT_HANDLER

            /* Intialize the retained text region. */
            memscpy(RETN_TEXT_START, RETN_TEXT_SIZE, RETN_TEXT_LOAD, RETN_TEXT_SIZE);

            /* Copy the vector table into the beginning of RAM. */
            memscpy(RETN_RAM_START, VECTOR_TABLE_SIZE, QAPI_NVM_APSS_START, VECTOR_TABLE_SIZE);

            /* Save the default hard fault handler. */
            PWR_RetainedContext.FaultHandler = (PWR_FaultHandler_t)NVIC_GetVector(HardFault_IRQn);

            /* Remap the vector table to beginning of RAM by using the AON
               register, which will retain the table through shutdown. */
            HWIO_AON_PME_APPS_REMAP_OUT((HWIO_AON_PME_APPS_REMAP_OFFSET_RAM_START << HWIO_AON_PME_APPS_REMAP_OFFSET_SHFT) | (HWIO_AON_PME_APPS_REMAP_SEL_RAM << HWIO_AON_PME_APPS_REMAP_SEL_SHFT));

            /* Install the VDIO fault handler in the retained RAM vector table. */
            NVIC_SetVector(HardFault_IRQn, (uint32_t)VdioFaultHandler);

#endif

            /* Determine the expected value of the retention register. */
            if(RETN_RAM_START <= RAM_APSS_BLOCK_0_END)
            {
               if(RETN_RAM_END >= RAM_APSS_BLOCK_1_START)
               {
                  PWR_RetainedContext.ShutdownRetn = HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_RETAINED | HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_RETAINED;
               }
               else
               {
                  PWR_RetainedContext.ShutdownRetn = HWIO_AON_PME_RAM_RETN_APSS_BLOCK_0_RETAINED;
               }
            }
            else
            {
               PWR_RetainedContext.ShutdownRetn = HWIO_AON_PME_RAM_RETN_APSS_BLOCK_1_RETAINED;
            }

            HWIO_AON_PME_APPS_RAM_RETN_OUT(PWR_RetainedContext.ShutdownRetn);

            /* Set system wakeup duration. */
            HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_OUTM(HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_DUR_BMSK, SYS_WAKEUP_TIME);

            if(HWIO_AON_PME_APPS_DEPEND_CLOCKS_INM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK) != 0)
            {
               /* HFXTAL is already enabled so add a vote for the VMA LDO. */
               PWR_RetainedContext.VMA_Count   = 1;
               PWR_RetainedContext.HFCLK_Count = 1;
            }

            if(HWIO_AON_PME_SOC_CONTROL_INM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK) == (HWIO_AON_PME_SOC_CONTROL_LFXTAL << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT))
            {
               /* LFXTAL is already enabled so set the count to 1. */
               PWR_RetainedContext.LFCLK_Count = 1;
            }
            else if(HWIO_APSS_XTAL_CTRL_INM(HWIO_APSS_XTAL_CTRL_XTAL_EN_BMSK))
            {
               /* LFXTAL was only partially enabled so just disable it. */
               StartTime = PWR_Get_Time_Now();
               while((PWR_Get_Time_Now() - StartTime) < 300000) {}

               PWR_DisableLFXTAL();
            }

            /* Flag the power module is initialized. */
            PWR_RetainedContext.Initialized = true;
         }
         else
         {
            RetVal = QAPI_ERR_BOUNDS;
         }
      }
      else
      {
         /* Call the wake functions. */
         qapi_TSK_Enter_Critical();
         PWR_CallWakeupCallbacks(PWR_RetainedContext.CallbackListHead, false);
         qapi_TSK_Exit_Critical();
      }
   }

   /* Clear the GTMR in case we woke for another reason. */
   HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_OUT(0);
   HWIO_AON_GBLTMR_SLV_INT_CLR_OUT(HWIO_AON_GBLTMR_SLV_INT_CLR_CLR_BMSK);

   /* Set the default request state to active. */
   HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_ACTIVE);

   /* Make sure AON interrupts are enabled. */
   __NVIC_EnableIRQ(Aon_IRQn);

   return(RetVal);
}

/**
   @brief Indicates the system is idle.

   This function will evaluate the sleep votes made via
   qapi_PWR_Vote_Local_State() and enter appropriate sleep state. When entering
   the shutdown state, the times specified to qapi_PWR_Vote_Local_State() will
   be combined with SleepTime to set a wakeup timer for the subsystem.

   @param[in] WakeTime  Maximum time in milliseconds for the subsystem to sleep.
                        Use QAPI_PWR_NO_WAKE if this time shouldn't be used to
                        set a wakeup. If WakeTime is greater than
                        QAPI_PWR_MAX_WAKE_TIME, QAPI_PWR_MAX_WAKE_TIME will be
                        used instead.
*/
void qapi_PWR_System_Idle(uint32_t WakeTime)
{
   uint32_t TimeNow;
   uint32_t AbsTime;
   uint32_t TempWake;
   uint32_t TempAbs;
   uint32_t Index;
   qbool_t  Sleep;
   qbool_t  Shutdown;
   uint8_t  WdogConfig;

   if(PWR_RetainedContext.Initialized)
   {
      TimeNow = PWR_Get_Time_Now();

      /* Convert the WakeTime to microseconds. */
      if(WakeTime != QAPI_PWR_NO_WAKE)
      {
         if(WakeTime > QAPI_PWR_MAX_WAKE_TIME)
         {
            WakeTime = QAPI_PWR_MAX_WAKE_TIME;
         }

         WakeTime *= 1000;

         AbsTime = TimeNow + WakeTime;
      }
      else
      {
         AbsTime = 0;
      }

      qapi_TSK_Enter_Critical();

      /* Make sure the scheduler doesn't have any events pending. */
      if(qapi_TSK_Check_Idle())
      {
         WdogConfig = 0;

         if(PWR_RetainedContext.ElectLocal)
         {
            HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_ACTIVE);

            Sleep    = true;
            Shutdown = false;
         }
         else
         {
            /* Determine the wake time based on the votes. */
            for(Index = 0; (Index < QAPI_PWR_MAX_BALLOTS); Index ++)
            {
               if(PWR_RetainedContext.WakeValid & (1 << Index))
               {
                  /* Get the time remaining until the waketime. */
                  TempAbs  = PWR_RetainedContext.WakeTime[Index];
                  TempWake = TempAbs - TimeNow;

                  if(TempWake < TIME_IN_PAST_THRESHOLD)
                  {
                     if((WakeTime == QAPI_PWR_NO_WAKE) || (WakeTime > TempWake))
                     {
                        WakeTime = TempWake;
                        AbsTime   = TempAbs;
                     }
                  }
                  else
                  {
                     WakeTime = TIME_IN_PAST_THRESHOLD;
                     break;
                  }
               }
            }

            /* Get the minimum wake time from all the registered ballots. */
            if((WakeTime != QAPI_PWR_NO_WAKE) && (WakeTime >= TIME_IN_PAST_THRESHOLD))
            {
               /* Waketime is in the past so don't try to sleep. */
               Shutdown = false;
               Sleep    = false;
            }
            else if(WakeTime <= MINIMUM_SHUTDOWN_TIME)
            {
               /* Waketime is too close to the current time so don't enter
                  shutdown. */
               Shutdown = false;
               Sleep    = true;
            }
            else
            {
               /* Notify the callbacks that we are entering shutdown. */
               Shutdown = PWR_CallShutdownCallbacks();
               Sleep    = Shutdown;
            }

            if(Shutdown)
            {
               WdogConfig = qapi_WDOG_GetConfig();
               if(WdogConfig != 0)
               {
                  qapi_WDOG_Configure(0);
               }

               /* Prepare to enter the shutdown state. */
               HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_SHUTDOWN);
            }
            else
            {
               /* Failed to enter shutdown for some reason so just stay active. */
               HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_ACTIVE);
            }
         }

         if((Sleep) && (WakeTime != QAPI_PWR_NO_WAKE))
         {
            /* Configure the timer for the shutdown wake time. */
            Sleep = PWR_ConfigureWakeup(AbsTime);
         }

         if(Sleep)
         {
            /* Enter sleep. */
            __WFI();

            if (WakeTime != QAPI_PWR_NO_WAKE)
            {
               /* Clear the GTMR in case we woke for another reason. */
               HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_OUT(0);
               HWIO_AON_GBLTMR_SLV_INT_CLR_OUT(HWIO_AON_GBLTMR_SLV_INT_CLR_CLR_BMSK);
            }
         }

         /* Set the request state back to active in case a WFI is used elsewhere. */
         HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_ACTIVE);

         if(Shutdown)
         {
            if(WdogConfig != 0)
            {
               qapi_WDOG_Configure(WdogConfig);
            }

            /* Call the wakeup callbacks to signal the shutdown was aborted. */
            PWR_CallWakeupCallbacks(PWR_RetainedContext.CallbackListHead, true);
         }
      }

      qapi_TSK_Exit_Critical();
   }
}

/**
   @brief Attempts to turn off the local subsystem.

   This function will imidiately try to turn off the local subsystem,
   regardless of any outstanding votes.  This process is similar to entering
   the shutdown state except no memory will be retained and the next time
   the subsystem starts, it will behave as a cold boot.

   This function is intended to enter the lowest power state when only APSS is
   being used and should not be used when BTSS or TME are active.

   This function doesn't return unless another subsytem is active.

   @param[in] WakeTime  Time in milliseconds for the subsystem to sleep. Use
                        #QAPI_PWR_NO_WAKE to not wake on a timer.  If WakeTime
                        is greater than #QAPI_PWR_MAX_WAKE_TIME,
                        #QAPI_PWR_MAX_WAKE_TIME is used instead.
*/
void qapi_PWR_Subsystem_Off(uint32_t WakeTime)
{
   qbool_t Sleep;
   /* Make sure TME and BTSS are in shutdown. */
   if(HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_ROT_BMSK | HWIO_AON_PME_SOC_STATUS_BT_BMSK) == 0)
   {
      if(WakeTime != QAPI_PWR_NO_WAKE)
      {
         /* Cap the WakeTime to the maximum allowed. */
         if(WakeTime > QAPI_PWR_MAX_WAKE_TIME)
         {
            WakeTime = QAPI_PWR_MAX_WAKE_TIME;
         }

         /* Configure the wakeup time. */
         Sleep = PWR_ConfigureWakeup(PWR_Get_Time_Now() + (WakeTime * 1000));
      }
      else
      {
         Sleep = true;
      }

      if(Sleep)
      {
         /* If the power module is initialized, clear out its state. */
         if(PWR_RetainedContext.Initialized)
         {
            PWR_RetainedContext.Initialized = 0;
            PWR_RetainedContext.ShutdownRetn = 0;
         }

#ifndef DISABLE_VDIO_FAULT_HANDLER

         /* Remap the vector table back to NVM since the RAM that holds
            the vector table will no longer be retained. */
         HWIO_AON_PME_APPS_REMAP_OUT((HWIO_AON_PME_APPS_REMAP_OFFSET_NVM_START << HWIO_AON_PME_APPS_REMAP_OFFSET_SHFT) | (HWIO_AON_PME_APPS_REMAP_SEL_NVM << HWIO_AON_PME_APPS_REMAP_SEL_SHFT));

#endif

         /* Clear the vote for retained RAM. */
         HWIO_AON_PME_APPS_RAM_RETN_OUT(0);

         /* Try to enter shutdown. */
         HWIO_AON_PME_APPS_REQ_STATE_OUT(HWIO_AON_PME_REQ_STATE_SHUTDOWN);
         __WFI();
      }

      /* Failed to enter shutdown, force a subsystem reset instead. */
      HWIO_AON_PME_APPS_RESET_OUT(HWIO_AON_PME_APPS_RESET_SUBSYSTEM_RESET);
   }
}

/**
   @brief Registers callback functions to be called before the subsystem enters
          the shutdown state and after it resumes.

   The priority specified is used to determine the order functions are called
   when entering or exiting the shutdown state. When entering shutdown, the
   highest priority function will be called first.  On wakeup, the order
   functions are called will be reversed (lowest priority first).

   @param[in] ShutdownCB  Function that will be called before the subsystem
                          enters the shutdown state.
   @param[in] WakeupCB    Function that will be called after the subsystem exits
                          sleep.
   @param[in] Priority    Used to determine the order that functions will be
                          called when entering or exitting the shutdown state.
                          QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT should be
                          used if it doesn't matter when these functions are
                          called.
   @param[in] UserParam   User specified parameter for the callback functions.

   @return A handle for the registered callback functions. This can be used to
           unregister the callback.
*/
void *qapi_PWR_Register_Shutdown_Callbacks(qapi_PWR_Shutdown_CB_t ShutdownCB, qapi_PWR_Wakeup_CB_t WakeupCB, uint8_t Priority, void *UserParam)
{
   PWR_CallbackEntry_t *CurrentEntry;
   PWR_CallbackEntry_t *NewEntry;

   /* Verify the parameters. */
   if((PWR_RetainedContext.Initialized) && (ShutdownCB != NULL) && (WakeupCB != NULL))
   {
      /* Initialize the new entry. */
      NewEntry = (PWR_CallbackEntry_t *)qapi_Malloc_Retain(sizeof(PWR_CallbackEntry_t));

      if(NewEntry != NULL)
      {
         NewEntry->ShutdownCB = ShutdownCB;
         NewEntry->WakeupCB   = WakeupCB;
         NewEntry->Priority   = Priority;
         NewEntry->UserParam  = UserParam;
         NewEntry->Next       = NULL;
         NewEntry->Prev       = NULL;

         qapi_TSK_Enter_Critical();

         if(PWR_RetainedContext.CallbackListTail == NULL)
         {
            /* List is empty. */
            PWR_RetainedContext.CallbackListHead = NewEntry;
            PWR_RetainedContext.CallbackListTail = NewEntry;
         }
         else
         {
            /* Walk from the end of the list, looking for the first entry thats
               not a higher priority.  This search is done in reverse as its
               assumed most callbacks will have the same priority. */
            CurrentEntry = PWR_RetainedContext.CallbackListTail;
            while((CurrentEntry != NULL) && (CurrentEntry->Priority > Priority))
            {
               CurrentEntry = CurrentEntry->Prev;
            }

            if(CurrentEntry == NULL)
            {
               /* First entry in List. */
               NewEntry->Next = PWR_RetainedContext.CallbackListHead;
               NewEntry->Prev = NULL;
               PWR_RetainedContext.CallbackListHead->Prev = NewEntry;
               PWR_RetainedContext.CallbackListHead = NewEntry;
            }
            else
            {
               NewEntry->Next     = CurrentEntry->Next;
               NewEntry->Prev     = CurrentEntry;
               CurrentEntry->Next = NewEntry;

               if(NewEntry->Next != NULL)
               {
                  NewEntry->Next->Prev = NewEntry;
               }
               else
               {
                  /* Tail of the list. */
                  PWR_RetainedContext.CallbackListTail = NewEntry;
               }
            }
         }

         qapi_TSK_Exit_Critical();
      }
   }
   else
   {
      NewEntry = NULL;
   }

   return(NewEntry);
}

/**
   @brief Unregisters callbacks registered with qapi_PWR_RegisterCallbacks().


   @param[in] CallbackHandle  Handle for the registered callbacks.

   @return The newly acquired ballot or zero if bollot acquisition failed.
*/
void qapi_PWR_Unregister_Callback(void *CallbackHandle)
{
   PWR_CallbackEntry_t *CurrentEntry;

   if((PWR_RetainedContext.Initialized) && (CallbackHandle != NULL))
   {
      qapi_TSK_Enter_Critical();

      /* Walk the list looking for the callback specified. */
      CurrentEntry = PWR_RetainedContext.CallbackListHead;
      while((CurrentEntry != NULL) && (CurrentEntry != CallbackHandle))
      {
         CurrentEntry = CurrentEntry->Next;
      }

      if(CurrentEntry != NULL)
      {
         /* Remove the entry from the list. */
         if(CurrentEntry->Prev != NULL)
         {
            CurrentEntry->Prev->Next = CurrentEntry->Next;
         }
         else
         {
             PWR_RetainedContext.CallbackListHead = CurrentEntry->Next;
         }

         if(CurrentEntry->Next != NULL)
         {
            CurrentEntry->Next->Prev = CurrentEntry->Prev;
         }
         else
         {
             PWR_RetainedContext.CallbackListTail = CurrentEntry->Prev;
         }

         /* Free the entry. */
         qapi_Free(CurrentEntry);
      }

      qapi_TSK_Exit_Critical();
   }
}

/**
   @brief Acquires for a ballot that can be used with the power voting APIs.

   @return The newly acquired ballot or zero if bollot acquisition failed.
*/
qapi_PWR_Ballot_t qapi_PWR_Acquire_Ballot(void)
{
   uint32_t Index;
   uint32_t RetVal;

   RetVal = (qapi_PWR_Ballot_t)0;

   if(PWR_RetainedContext.Initialized)
   {
      qapi_TSK_Enter_Critical();

      /* Walk the ballot mask looking for one that's avaible. */
      for(Index = 0; Index < QAPI_PWR_MAX_BALLOTS; Index++)
      {
         if(!(PWR_RetainedContext.Ballots & (1 << Index)))
         {
            /* Availale entry found. */
            PWR_RetainedContext.Ballots |= (1 << Index);
            PWR_RetainedContext.WakeTime[Index] = QAPI_TSK_INFINITE_WAIT;
            RetVal = PWR_INDEX_TO_BALLOT(Index);
            break;
         }
      }

      qapi_TSK_Exit_Critical();
   }

   return(RetVal);
}

/**
   @brief Releases a ballot and cancels all votes associated with it.

   @param[in] Ballot  Ballot to release.
*/
void qapi_PWR_Release_Ballot(qapi_PWR_Ballot_t Ballot)
{
   uint32_t BallotMask;

   /* Verify the ballot. */
   if((PWR_RetainedContext.Initialized) && (Ballot > 0) && (Ballot <= QAPI_PWR_MAX_BALLOTS))
   {
      BallotMask = 1 << (Ballot - 1);
      qapi_TSK_Enter_Critical();

      /* See if the ballot is actually in use. */
      if(PWR_RetainedContext.Ballots & BallotMask)
      {
         /* Clear the ballot. */
         PWR_RetainedContext.Ballots   &= ~BallotMask;
         PWR_RetainedContext.WakeValid &= ~BallotMask;

         /* Cancel any oustanding votes for the ballot. */
         PWR_RetainedContext.ElectLocal &= ~BallotMask;
      }

      qapi_TSK_Exit_Critical();
   }
}

/**
   @brief Votes for the sleep state of the local subsystem.

   This state will be entered the next time a WFI is executed.  If the vote is
   QAPI_PWR_STATE_SHUTDOWN_E, the WakeValid and WakeTime indicate when the
   caller needs the subsystem to wake up.

   @param[in] Ballot    Ballot acquired by a call to qapi_PWR_Acquire_Ballot().
   @param[in] Vote      State to vote.
   @param[in] WakeTime  Time that the voter will need the system to wake up in
                        milliseconds relative to the current time. Use
                        QAPI_PWR_NO_WAKE if this time shouldn't be used to set a
                        wakeup. If SleepTime is greater than
                        QAPI_PWR_MAX_WAKE_TIME, QAPI_PWR_MAX_WAKE_TIME will be
                        used instead.
   @return QAPI_OK if the vote was cast successfully or a negative value if
           there was an error.
*/
qapi_Status_t qapi_PWR_Vote_Local_State(qapi_PWR_Ballot_t Ballot, qapi_PWR_State_t Vote, uint32_t WakeTime)
{
   qapi_Status_t       RetVal;
   qapi_PWR_Election_t BallotMask;

   if(PWR_RetainedContext.Initialized)
   {
      /* Verify the parameters. */
      BallotMask = PWR_VerifyBallot(Ballot);
      if((BallotMask != 0) && (Vote >= QAPI_PWR_STATE_SHUTDOWN_E) && (Vote <= QAPI_PWR_STATE_ACTIVE_E))
      {
         if(Vote == QAPI_PWR_STATE_SHUTDOWN_E)
         {
            /* Update the wake time for this vote. */
            if(WakeTime != QAPI_PWR_NO_WAKE)
            {
               /* Cap the wake-time to the maximum allowed value. */
               if(WakeTime > QAPI_PWR_MAX_WAKE_TIME)
               {
                  WakeTime = QAPI_PWR_MAX_WAKE_TIME;
               }

               /* Convert the waketime to an absoluste time.  Note the timer
                  uses microseconds. */
               WakeTime = PWR_Get_Time_Now() + (WakeTime * 1000);

               /* Store the wake time and flag it is valid. */
               PWR_RetainedContext.WakeTime[PWR_BALLOT_TO_INDEX(Ballot)] = WakeTime;
               PWR_RetainedContext.WakeValid |= BallotMask;
            }
            else
            {
               /* Flag the ballot's time isn't valid. */
               PWR_RetainedContext.WakeValid &= ~BallotMask;
            }

            /* Clear the current vote for the ballot. */
            PWR_RetainedContext.ElectLocal &= ~BallotMask;
         }
         else
         {
            /* Vote for the active state. */
            PWR_RetainedContext.ElectLocal |= BallotMask;
         }

         RetVal = QAPI_OK;
      }
      else
      {
         RetVal = QAPI_ERR_INVALID_PARAM;
      }
   }
   else
   {
      RetVal = QAPI_ERROR;
   }

   return(RetVal);
}

/**
   @brief Sets the state of another subsystem.

   This API is used to set state of a remote subsystem.  This sets the state of
   the hardware vote for the subystem and the actual state of the subsystem may be
   different.

   @param[in] Module  Module whose state will to be set.
   @param[in] State   State to select.

   @return QAPI_OK if the vote was cast successfully or a negative value if
           there was an error.
*/
qapi_Status_t qapi_PWR_Set_Module_State(qapi_PWR_Module_t Module, qapi_PWR_State_t State)
{
   qapi_Status_t RetVal;
   uint32_t      RegShift;
   uint32_t      RegValue;

   RetVal = QAPI_OK;
   switch(State)
   {
      case QAPI_PWR_STATE_ACTIVE_E:
         RegValue = HWIO_AON_PME_REQ_STATE_ACTIVE;
         break;

      case QAPI_PWR_STATE_SHUTDOWN_E:
         RegValue = HWIO_AON_PME_REQ_STATE_SHUTDOWN;
         break;

      default:
         RegValue = 0;
         RetVal   = QAPI_ERR_INVALID_PARAM;
   }

   if(RetVal == QAPI_OK)
   {
      /* Determine which module is being voted for. */
      switch(Module)
      {
         case QAPI_PWR_MODULE_BTSS_E:
            RegShift = HWIO_AON_PME_APPS_DEPEND_ACTIVE_BT_SHFT;
            break;

         case QAPI_PWR_MODULE_ROT_E:
            RegShift = HWIO_AON_PME_APPS_DEPEND_ACTIVE_ROT_SHFT;
            break;

         case QAPI_PWR_MODULE_PERIPHERAL_E:
            RegShift = HWIO_AON_PME_APPS_DEPEND_ACTIVE_PER_SHFT;
            break;

         case QAPI_PWR_MODULE_GPIO_E:
            RegShift = HWIO_AON_PME_APPS_DEPEND_ACTIVE_TLMM_SHFT;
            break;

         case QAPI_PWR_MODULE_NVM_E:
            /* Setting the NVM power state while active is not supported as
               this is managed automatically. */
            RetVal   = QAPI_ERR_NOT_SUPPORTED;
            RegShift = 0;
            break;

         default:
            RetVal   = QAPI_ERR_INVALID_PARAM;
            RegShift = 0;
            break;
      }

      if(RetVal == QAPI_OK)
      {
         HWIO_AON_PME_APPS_DEPEND_ACTIVE_OUTM(HWIO_AON_PME_REQ_STATE_BMSK << RegShift, RegValue << RegShift);
      }
   }

   return(RetVal);
}

/**
   @brief Reads the state of one of the subsystems or modules.

   @param[in] Module  Module state to read.

   @return state of the specified module.
*/
qapi_PWR_State_t qapi_PWR_Get_Module_State(qapi_PWR_Module_t Module)
{
   qapi_PWR_State_t RetVal;
   uint32_t         RegVal;

   RetVal = QAPI_PWR_STATE_SHUTDOWN_E;

   /* Determine which module is being voted for. */
   switch(Module)
   {
      case QAPI_PWR_MODULE_APSS_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_APPS_BMSK) >> HWIO_AON_PME_SOC_STATUS_APPS_SHFT;
         break;

      case QAPI_PWR_MODULE_BTSS_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_BT_BMSK) >> HWIO_AON_PME_SOC_STATUS_BT_SHFT;
         break;

      case QAPI_PWR_MODULE_ROT_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_ROT_BMSK) >> HWIO_AON_PME_SOC_STATUS_ROT_SHFT;
         break;

      case QAPI_PWR_MODULE_NVM_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_NVM_BMSK) >> HWIO_AON_PME_SOC_STATUS_NVM_SHFT;
         break;

      case QAPI_PWR_MODULE_PERIPHERAL_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_PER_BMSK) >> HWIO_AON_PME_SOC_STATUS_PER_SHFT;
         break;

      case QAPI_PWR_MODULE_GPIO_E:
         RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_TLMM_BMSK) >> HWIO_AON_PME_SOC_STATUS_TLMM_SHFT;
         break;

      default:
         RegVal = 0;
         break;
   }

   switch(RegVal)
   {
      case HWIO_AON_PME_REQ_STATE_ACTIVE:
         RetVal = QAPI_PWR_STATE_ACTIVE_E;
         break;

      case HWIO_AON_PME_REQ_STATE_SHUTDOWN:
      default:
         RetVal = QAPI_PWR_STATE_SHUTDOWN_E;
         break;
   }

   return(RetVal);
}

/**
   @brief Requests the VMA LDO.

   This function will track the number of outstanding requests for the LDO and
   only disable the LDO when the number of calls with Enable=false matches the
   number of calls with Enable=true.

   This function will block until the LDO has stabalized.

   @param[in] Enable  Flag indicating if the VMA LDO should be enabled (true) or
                      disabled (false).
*/
void qapi_PWR_Set_VMA_LDO(qbool_t Enable)
{
   if(Enable)
   {
      if(PWR_RetainedContext.VMA_Count == 0)
      {
         /* Turn on the VMA LDO. */
         HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_LDO_VMA_APSS_HOLD_REQ_BMSK | HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_ENABLE_REQ_BMSK);

         while(!HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_LDO_VMA_OK_BMSK)) {}
      }

      PWR_RetainedContext.VMA_Count++;
   }
   else
   {
      if(PWR_RetainedContext.VMA_Count != 0)
      {
         PWR_RetainedContext.VMA_Count--;

         if(PWR_RetainedContext.VMA_Count == 0)
         {
            /* Turn off the VMA LDO. */
            HWIO_PMU_APSS_REQ_OUT(HWIO_PMU_APSS_REQ_LDO_VMA_APSS_RELEASE_REQ_BMSK | HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_DISABLE_REQ_BMSK);
         }
      }
   }
}

/**
   @brief Reads the configuration of the HFCLK Source.

   @return True if the VMA LDO is enabled or false if it is not.
*/
qbool_t qapi_PWR_Get_VMA_LDO(void)
{
   return (HWIO_PMU_APSS_STATUS_INM(HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_HOLD_STATUS_BMSK | HWIO_PMU_APSS_STATUS_LDO_VMA_OK_BMSK) == (HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_HOLD_STATUS_BMSK | HWIO_PMU_APSS_STATUS_LDO_VMA_OK_BMSK));
}

/**
   @brief Sets the voltage of the low power digital LDO.

   @param[in] Voltage  Requested voltage of the LDO in millivolts.  The actual
                       value programmed will be rounded up to the next 12.5mV
                       increment.  See QAPI_PWR_VLP_LDO_VOLTAGE_xxx for the 
                       valid range of values.

   @return True if the voltage was set or false if the specified voltage was
           invalid.
*/
qbool_t qapi_PWR_Set_VLP_Voltage(uint32_t Voltage)
{
   qbool_t  RetVal;
   uint32_t RegVal;

   if((Voltage >= QAPI_PWR_VLP_VOLTAGE_MIN) && (Voltage <= QAPI_PWR_VLP_VOLTAGE_MAX))
   {
      /* Calculate the register setting, rounding up to the next voltage. Note
         that a higher value is a lower voltage. */
      Voltage *= 10;
      RegVal = PWR_VLP_VOUT_OFFSET - ((Voltage + (PWR_VLP_VOUT_INCREMENT - 1)) / PWR_VLP_VOUT_INCREMENT);

      HWIO_APSS_PL1_PL0_CONFIG_0_OUTM(HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_BMSK, RegVal << HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_SHFT);

      RetVal = true;
   }
   else
   {
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Reads the configured voltage of the low power digital LDO.

   @return The voltage of the LDO in millivolts (rounded down).
*/
uint32_t qapi_PWR_Get_VLP_Voltage(void)
{
   uint32_t RetVal;

   RetVal = HWIO_APSS_PL1_PL0_CONFIG_0_INM(HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_BMSK) >> HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_SHFT;

   RetVal = (PWR_VLP_VOUT_OFFSET - RetVal) * PWR_VLP_VOUT_INCREMENT;

   return(RetVal / 10);
}

/**
   @brief Sets the source of the 32MHz HFCLK. The VMA LDO will automatically be
          enabled if required.

   This function sets the HW vote for the source of the HFCLK and the actual
   source HW selects may be different.

   @param[in] Accurate  Flag indicating if an accurate HFCLK is required (true)
                        or can use an inaccurate, low power HFCLK (false).
*/
void qapi_PWR_Set_HFCLK_Source(qbool_t Accurate)
{
   if(Accurate)
   {
      /* Check to see if the vote count for the HFCLK is zero.  If it is*/
      /* zero we need to turn on the clock hardware.                    */
      if(PWR_RetainedContext.HFCLK_Count == 0)
      {
         /* Check to see if the APSS is already holding a vote for the clock. */
         if(HWIO_AON_PME_APPS_DEPEND_CLOCKS_INM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK) == 0)
         {
            qapi_PWR_Set_VMA_LDO(true);

            /* Configure the AUX registers. */
            HWIO_AUX_ANA_CTRL0_SET0_OUT(QAPI_MTP_APSS_RO_PTR->AuxCtrl0Set0);
            HWIO_AUX_ANA_CTRL0_SET1_OUT(QAPI_MTP_APSS_RO_PTR->AuxCtrl0Set1);
            HWIO_AUX_ANA_CTRL1_SET0_OUT((QAPI_MTP_APSS_RO_PTR->AuxCtrl1Set0_Ctrl5Set0 >> QAPI_MTP_AUX_CTRL1_SET_N_SHIFT) & QAPI_MTP_AUX_CTRL1_SET_N_MASK);
            HWIO_AUX_ANA_CTRL5_SET0_OUT((QAPI_MTP_APSS_RO_PTR->AuxCtrl1Set0_Ctrl5Set0 >> QAPI_MTP_AUX_CTRL5_SET_N_SHIFT) & QAPI_MTP_AUX_CTRL5_SET_N_MASK);
            HWIO_AUX_ANA_CTRL1_SET1_OUT((QAPI_MTP_APSS_RO_PTR->AuxCtrl1Set1_Ctrl5Set1 >> QAPI_MTP_AUX_CTRL1_SET_N_SHIFT) & QAPI_MTP_AUX_CTRL1_SET_N_MASK);
            HWIO_AUX_ANA_CTRL5_SET1_OUT((QAPI_MTP_APSS_RO_PTR->AuxCtrl1Set1_Ctrl5Set1 >> QAPI_MTP_AUX_CTRL5_SET_N_SHIFT) & QAPI_MTP_AUX_CTRL5_SET_N_MASK);
            HWIO_AUX_ANA_CTRL2_REG_OUT(QAPI_MTP_APSS_RO_PTR->AuxCtrl2);
            HWIO_AUX_ANA_CTRL3_REG_OUT(QAPI_MTP_APSS_RW_PTR->AuxCtrl3);
            HWIO_AUX_ANA_CTRL4_SET0_OUT(QAPI_MTP_APSS_RW_PTR->AuxCtrl4Set0);
            HWIO_AUX_ANA_CTRL4_SET1_OUT(QAPI_MTP_APSS_RW_PTR->AuxCtrl4Set1);
            HWIO_AUX_ANA_CTRL6_SET0_OUT(((QAPI_MTP_APSS_RO_PTR->AuxCtrl6_Ctrl7 >> QAPI_MTP_AUX_CTRL6_SET0_SHIFT) & QAPI_MTP_AUX_CTRL6_SET0_MASK) << HWIO_AUX_ANA_CTRL6_SET0_AUX_ANA_XTAL_EN_LOW_NOISE_REG_SHFT);
            HWIO_AUX_ANA_CTRL6_SET1_OUT(((QAPI_MTP_APSS_RO_PTR->AuxCtrl6_Ctrl7 >> QAPI_MTP_AUX_CTRL6_SET1_SHIFT) & QAPI_MTP_AUX_CTRL6_SET1_MASK) << HWIO_AUX_ANA_CTRL6_SET1_AUX_ANA_XTAL_EN_LOW_NOISE_REG_SHFT);
            HWIO_AUX_ANA_CTRL7_REG_OUT((QAPI_MTP_APSS_RO_PTR->AuxCtrl6_Ctrl7 >> QAPI_MTP_AUX_CTRL7_SHIFT) & QAPI_MTP_AUX_CTRL7_MASK);
            HWIO_AUX_ANA_CTRL8_REG_OUT(QAPI_MTP_APSS_RO_PTR->AuxCtrl8);
            HWIO_AUX_DRV_CTRL_OUT((QAPI_MTP_APSS_RO_PTR->AuxDrvCtrl_Ctrl9 >> QAPI_MTP_AUX_DRV_CTRL_SHIFT) & QAPI_MTP_AUX_DRV_CTRL_MASK);
            HWIO_AUX_ANA_CTRL9_REG_OUT((QAPI_MTP_APSS_RO_PTR->AuxDrvCtrl_Ctrl9 >> QAPI_MTP_AUX_CTRL9_SHIFT) & QAPI_MTP_AUX_CTRL9_MASK);
            HWIO_AUX_DRV_T1_OUT(QAPI_MTP_APSS_RW_PTR->AuxDrvT1);
            HWIO_AUX_DRV_OUT(QAPI_MTP_APSS_RO_PTR->AuxDrv);
            HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_OUT((QAPI_MTP_APSS_RO_PTR->AuxGhmiehr_TmuxCtrl0 >> QAPI_MTP_AUX_GHMIEHR_SHIFT) & QAPI_MTP_AUX_GHMIEHR_MASK);
            HWIO_AUX_ANA_TMUX_CTRL0_REG_OUT(((QAPI_MTP_APSS_RO_PTR->AuxGhmiehr_TmuxCtrl0 >> QAPI_MTP_AUX_TMUX_CTRL0_SHIFT) & QAPI_MTP_AUX_TMUX_CTRL0_MASK) << HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_PLL_SEL_REF_SHFT);
            HWIO_AUX_DRV_T3_OUT(QAPI_MTP_APSS_RW_PTR->AuxDrvT3);
            HWIO_AUX_DRV_T4_OUT(QAPI_MTP_APSS_RW_PTR->AuxDrvT4);

            /* Vote for the clock. */
            HWIO_AON_PME_APPS_DEPEND_CLOCKS_OUTM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK, HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK);

            /* Wait for the clock to lock. */
            while(!HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_HFCLK_BMSK)) {}

            /* Enable HFCLK early wake. */
            HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_HFXTAL_CONST_OVRD_BMSK, HWIO_AON_PME_SOC_CONTROL_HFXTAL_CONST_OVRD_BMSK);
         }
      }

      /* Increase the vote count.                                       */
      PWR_RetainedContext.HFCLK_Count++;
   }
   else
   {
      /* Check to see if the HFCLK vote count is non-zero.              */
      if(PWR_RetainedContext.HFCLK_Count != 0)
      {
         /* Decrement the vote count.                                   */
         PWR_RetainedContext.HFCLK_Count--;
      }

      /* When last vote is removed disable the hardware.                */
      if(PWR_RetainedContext.HFCLK_Count == 0)
      {
         if(HWIO_AON_PME_APPS_DEPEND_CLOCKS_INM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK) != 0)
         {
            HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_HFXTAL_CONST_OVRD_BMSK, 0);
            HWIO_AON_PME_APPS_DEPEND_CLOCKS_OUTM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK, 0);
            qapi_PWR_Set_VMA_LDO(false);
         }
      }
   }
}

/**
   @brief Reads the configuration of the HFCLK Source.

   @return true if the HFCLK is configured with an accurate clock source or
           false if it is the low power source.
*/
qbool_t qapi_PWR_Get_HFCLK_Source(void)
{
   return((qbool_t)(HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_HFCLK_BMSK) != 0));
}

/**
   @brief Sets the source of the GTMR clock.

   This function sets the HW vote for the source of the GTMR clock and the
   actual source HW selects may be different.

   @param[in] HFCLK  Flag indicating if the 32MHz HFCLK source is needed (true)
                     or if the the 32KHz LFCLK can be used (false).
*/
void qapi_PWR_Set_TCLK_Source(qbool_t HFCLK)
{
   HWIO_AON_PME_APPS_DEPEND_CLOCKS_OUTM(HWIO_AON_PME_APPS_DEPEND_CLOCKS_TCLK_BMSK, (HFCLK ? HWIO_AON_PME_APPS_DEPEND_CLOCKS_TCLK_BMSK : 0));
}

/**
   @brief Reads the configuration of the GTMR clock.

   @return true if GTMR uses the HFCLK or false if it uses the LFCLK.
*/
qbool_t qapi_PWR_Get_TCLK_Source(void)
{
   return((qbool_t)(HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_TCLK_BMSK) != 0));
}

/**
   @brief Configures the source of the LFCLK.

   Note that the callback mechanism can only be used after timer module is
   initialized by qapi_TMR_Init(). The blocking mechanism can be used anywhere.

   @param[in] Source       Source for the LFCLK.
   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp(). This
                           parameter is only used if Source is
                           QAPI_PWR_LFCLK_SOURCE_LFXTAL.
   @param[in] Callback     Function that is called when the LFXTAL has been
                           enabled. If NULL, this function blocks until the
                           LFXTAL is enabled. This parameter is only used if
                           Source is QAPI_PWR_LFCLK_SOURCE_LFXTAL.
   @param[in] UserParam    User-specified parameter for the callback functions.

   @return QAPI_OK if the clock was configured successfully or a negative value
           if there was an error.
*/
qapi_Status_t qapi_PWR_Set_LFCLK_Source(qapi_PWR_LFCLK_Source_t Source, int32_t Temperature, qapi_PWR_LFXTAL_Enabled_CB_t Callback, void *UserParam)
{
   qapi_Status_t             RetVal;
   uint32_t                  XtalConf;
   uint32_t                  Gain;
   uint32_t                  StartTime;
   uint32_t                  StartDelayUs;
   LFXTAL_CallbackContext_t *CallbackContext;

   if(Source == QAPI_PWR_LFCLK_SOURCE_LFXTAL)
   {
      /* Check to see if the XTAL is already enabled.                   */
      if(PWR_RetainedContext.LFCLK_Count == 0)
      {
         /* Calibrate the XTAL to the current temperature. */
         qapi_PWR_Calibrate_LFXTAL(Temperature);

         /* Check if the LFXTAL is already enabled. */
         XtalConf = HWIO_APSS_XTAL_CONF_IN;
         if(!HWIO_APSS_XTAL_CTRL_INM(HWIO_APSS_XTAL_CTRL_XTAL_EN_BMSK))
         {
            /* Set the Gain to twice the nominal value and set the speed-up enable. */
            Gain = (XtalConf & HWIO_APSS_XTAL_CONF_XTAL_GAIN_SET_BMSK) * 2;
            if(Gain > 63)
            {
               Gain = 63;
            }

            HWIO_APSS_XTAL_CONF_OUT((XtalConf & ~HWIO_APSS_XTAL_CONF_XTAL_GAIN_SET_BMSK) | HWIO_APSS_XTAL_CONF_XTAL_SPEEDUP_EN_BMSK | Gain);

            /* Turn on the XTAL and wait 300 ms. */
            HWIO_APSS_XTAL_CTRL_OUT(HWIO_APSS_XTAL_CTRL_XTAL_EN_BMSK);

            StartDelayUs = ((uint32_t)QAPI_MTP_APSS_RW_PTR->Xtal32kDelay) * 100000;
            if(Callback == NULL)
            {
               StartTime = PWR_Get_Time_Now();
               while((PWR_Get_Time_Now() - StartTime) < 300000) {}

               /* Set the XTAL configuration back to nominal and wait for the clock to
                  stabalize. */
               HWIO_APSS_XTAL_CONF_OUT(XtalConf);

               StartTime = PWR_Get_Time_Now();
               while((PWR_Get_Time_Now() - StartTime) < StartDelayUs) {}

               /* Signal the 32K clock is stable. */
               HWIO_APSS_XTAL_32K_OK_OUTM(HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_BMSK, HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_BMSK);

               /* Switch to the 32K XTAL. */
               HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK, HWIO_AON_PME_SOC_CONTROL_LFXTAL << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT);
               RetVal = QAPI_OK;
            }
            else
            {
               /* Allocate and initialize the callback context. */
               CallbackContext = qapi_Malloc(sizeof(LFXTAL_CallbackContext_t));
               if(CallbackContext != NULL)
               {
                  CallbackContext->State     = lxsTurningOn;
                  CallbackContext->Callback  = Callback;
                  CallbackContext->UserParam = UserParam;
                  CallbackContext->Delay     = ((StartDelayUs/1000) == 0) ? 1 : (StartDelayUs/1000);
                  CallbackContext->XtalConf  = XtalConf;

                  RetVal = qapi_TMR_Comp_Init(&(CallbackContext->Timer), PWR_LFXTAL_TimerCallback, CallbackContext, false);
                  if(RetVal == QAPI_OK)
                  {
                     /* Start a timer for the 32K clock to start. */
                     RetVal = qapi_TMR_Comp_Start(CallbackContext->Timer, 300000, false);

                     if (RetVal != QAPI_OK)
                     {
                        qapi_TMR_Comp_Deinit(CallbackContext->Timer);
                     }
                  }

                  if(RetVal != QAPI_OK)
                  {
                     /* Failed to start the timer so just free the callback context
                        and abort the start process. */
                     qapi_Free(CallbackContext);
                  }
               }
               else
               {
                  RetVal = QAPI_ERR_NO_MEMORY;
               }

               if(RetVal != QAPI_OK)
               {
                  /* Failed to start the XTAL, abort the process. */
                  PWR_DisableLFXTAL();
               }
            }
         }
         else
         {
            /* This shouldn't happen as it indicates the count is out of sync
               with the state of the regiters. */
            RetVal = QAPI_ERROR;
         }
      }
      else
      {
         if(HWIO_AON_PME_SOC_CONTROL_INM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK) == (HWIO_AON_PME_SOC_CONTROL_LFXTAL << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT))
         {
            /* LFXTAL is already enabled. */
            RetVal = QAPI_ERR_EXISTS;
         }
         else
         {
            /* Haven't yet switched to using the LFXTAL so the transition must
               be in progress. */
            RetVal = QAPI_ERR_BUSY;
         }
      }

      /* If we were successfull go ahead and increment the vote count.  */
      if((RetVal == QAPI_OK) || (RetVal == QAPI_ERR_EXISTS) || (RetVal == QAPI_ERR_BUSY))
      {
         PWR_RetainedContext.LFCLK_Count++;
      }
   }
   else
   {
      /* Verify vote count is non-zero.                                 */
      if(PWR_RetainedContext.LFCLK_Count != 0)
      {
         /* Decrement the vote.                                         */
         PWR_RetainedContext.LFCLK_Count--;
      }

      /* When vote count reaches 0 then we can disable the XTAL.        */
      if(PWR_RetainedContext.LFCLK_Count == 0)
      {
         if(Source == QAPI_PWR_LFCLK_SOURCE_SOSC)
         {
            HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK, HWIO_AON_PME_SOC_CONTROL_SOSC << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT);
            RetVal = QAPI_OK;
         }
         else if(Source == QAPI_PWR_LFCLK_SOURCE_GPIO)
         {
            HWIO_AON_PME_SOC_CONTROL_OUTM(HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK, HWIO_AON_PME_SOC_CONTROL_GPIO << HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT);
            RetVal = QAPI_OK;
         }
         else
         {
            RetVal = QAPI_ERR_INVALID_PARAM;
         }

         if((RetVal == QAPI_OK) && (HWIO_APSS_XTAL_CTRL_INM(HWIO_APSS_XTAL_CTRL_XTAL_EN_BMSK)))
         {
            StartTime = PWR_Get_Time_Now();
            while((PWR_Get_Time_Now() - StartTime) < 300000) {}

            /* Turn off the XTAL. */
            PWR_DisableLFXTAL();
         }
      }
      else
      {
         RetVal = QAPI_OK;
      }
   }

   return(RetVal);
}

/**
   @brief Reads the configuration of the LF clock source.

   @return The current configuration of the LF clock source.
*/
qapi_PWR_LFCLK_Source_t qapi_PWR_Get_LFCLK_Source(void)
{
   qapi_PWR_LFCLK_Source_t RetVal;
   uint32_t                RegVal;

   /* Read the control register. */
   RegVal = HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_LFCLK_BMSK) >> HWIO_AON_PME_SOC_STATUS_LFCLK_SHFT;

   switch(RegVal)
   {
      case HWIO_AON_PME_SOC_CONTROL_SOSC:
      case HWIO_AON_PME_SOC_CONTROL_SOSC2:
         RetVal = QAPI_PWR_LFCLK_SOURCE_SOSC;
         break;

      case HWIO_AON_PME_SOC_CONTROL_LFXTAL:
         RetVal = QAPI_PWR_LFCLK_SOURCE_LFXTAL;
         break;

      case HWIO_AON_PME_SOC_CONTROL_GPIO:
      default:
         RetVal = QAPI_PWR_LFCLK_SOURCE_GPIO;
         break;
   }

   return(RetVal);
}

/**
   @brief Calibrate the 32K XTAL.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
*/
void qapi_PWR_Calibrate_LFXTAL(int32_t Temperature)
{
   uint32_t Gain;

   /* Determine the ITFac to use. */
   Temperature /= 100;
   if(Temperature < QAPI_MTP_APSS_RO_PTR->Xtal32kTemp[0])
   {
      Gain = (QAPI_MTP_APSS_RO_PTR->Xtal32kItFac >> QAPI_MTP_XTAL_32K_ITFAC_SHIFT(0)) & QAPI_MTP_XTAL_32K_ITFAC_MASK;
   }
   else if(Temperature < QAPI_MTP_APSS_RO_PTR->Xtal32kTemp[1])
   {
      Gain = (QAPI_MTP_APSS_RO_PTR->Xtal32kItFac >> QAPI_MTP_XTAL_32K_ITFAC_SHIFT(1)) & QAPI_MTP_XTAL_32K_ITFAC_MASK;
   }
   else
   {
      Gain = (QAPI_MTP_APSS_RO_PTR->Xtal32kItFac >> QAPI_MTP_XTAL_32K_ITFAC_SHIFT(2)) & QAPI_MTP_XTAL_32K_ITFAC_MASK;
   }

   /* Calculate the gain. */
   Gain += 10;
   Gain *= (QAPI_MTP_APSS_RW_PTR->Xtal32kCfg_LdoVmaSelPt >> QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_SHIFT) & QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_MASK;
   Gain = (Gain + 15) / 16;
   if(Gain > 63)
   {
      Gain = 63;
   }

   /* Configure the XTAL registers. */
   HWIO_APSS_XTAL_CL_CONF_OUT((QAPI_MTP_APSS_RW_PTR->Xtal32kCfg_LdoVmaSelPt >> QAPI_MTP_XTAL_32K_CFG_TRIM_CL_SHIFT) & QAPI_MTP_XTAL_32K_CFG_TRIM_CL_MASK);
   HWIO_APSS_XTAL_CONF_OUTM(HWIO_APSS_XTAL_CONF_XTAL_GAIN_SET_BMSK, Gain);
}

/**
   @brief Reads the configuration of the LF clock source.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
   @param[in] Voltage      Voltage reading from qapi_SENS_Get_Voltage().
*/
void qapi_PWR_Enable_SMPS(int32_t Temperature, uint32_t Voltage)
{
   uint32_t StartTime;

   /* Apply the calibration first. */
   qapi_PWR_Calibrate_SMPS(Temperature, Voltage);

   if(!HWIO_APSS_VLA_SRC_CTRL_INM(HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BMSK))
   {
       /* Enable the Analog Clock. */
      HWIO_PMU_QC_REQ_OUT(HWIO_PMU_QC_REQ_SMPS_ANA_CLK_UPDATE_REQ_BMSK);

      /* Wait 1 clock cycle @ 32 kHz */
      StartTime = (uint32_t)qapi_TMR_Get_Current_Time();
      while(((uint32_t)qapi_TMR_Get_Current_Time() - StartTime) < 32) {}

      /* Enable the Bias. */
      HWIO_APSS_VLA_SRC_CTRL_OUTM(HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BIAS_BMSK, HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BIAS_BMSK);
      StartTime = (uint32_t)qapi_TMR_Get_Current_Time();
      while(((uint32_t)qapi_TMR_Get_Current_Time() - StartTime) < 300) {}

      /* Enable the SMPS. */
      HWIO_APSS_VLA_SRC_CTRL_OUTM(HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BMSK, HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BMSK);
      StartTime = qapi_TMR_Get_Current_Time();
      while(((uint32_t)qapi_TMR_Get_Current_Time() - StartTime) < 10) {}

      /* Disable the LDO. */
      HWIO_APSS_VLA_SRC_CTRL_OUTM(HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_DISABLE_BMSK, HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_DISABLE_BMSK);
   }
}

/**
   @brief Calibrate the SMPS.

   @param[in] Temperature  Current temperature from qapi_SENS_Get_Temp().
   @param[in] Voltage      Voltage reading from qapi_SENS_Get_Voltage().
*/
void qapi_PWR_Calibrate_SMPS(int32_t Temperature, uint32_t Voltage)
{
   uint32_t ClkDividerEn;
   uint32_t ClkDividerVal;
   uint32_t TempValue;
   uint32_t RegValue;
   int32_t  TempBin;

   /* Determine the temperature bin. Bins are separted based on thresholds
      from 30 degrees to 110 degrees in 10 degree increments. */
   TempBin = (Temperature - 2001) / 1000;
   if(TempBin > 9)
   {
      TempBin = 9;
   }
   else if(TempBin < 0)
   {
      TempBin = 0;
   }

   ClkDividerEn = (QAPI_MTP_APSS_RO_PTR->SmpsClkDiv >> QAPI_MTP_SMPS_CLK_DIVIDER_EN_SHIFT(TempBin)) & QAPI_MTP_SMPS_CLK_DIVIDER_EN_MASK;
   RegValue  = (ClkDividerEn << HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_DIV_EN_SHFT);
   ClkDividerVal = (QAPI_MTP_APSS_RO_PTR->SmpsClkDiv >> QAPI_MTP_SMPS_CLK_DIVIDER_VAL_SHIFT(TempBin)) & QAPI_MTP_SMPS_CLK_DIVIDER_VAL_MASK;
   RegValue |= (ClkDividerVal << HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_RATIO_SHFT);

   /* Update the ULP clock div register. */
   HWIO_APSS_PL1_PL0_CONFIG_1_OUTM(HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_RATIO_BMSK | HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_DIV_EN_BMSK, RegValue);

   /* Set the LDO DIG Discharge Delay value based on the chosen SMPS clock
      divider. */
   if((ClkDividerEn) && ((ClkDividerVal == QAPI_MTP_SMPS_CLK_DIVIDER_VAL_4_KHZ_VALUE) || (ClkDividerVal == QAPI_MTP_SMPS_CLK_DIVIDER_VAL_2_KHZ_VALUE)))
   {
      RegValue = (0x00 << HWIO_APSS_PL_DLY_CONF0_LDO_DIG_DISCHARGE_DLY_CNT_SHFT);
   }
   else
   {
      RegValue = (0x18 << HWIO_APSS_PL_DLY_CONF0_LDO_DIG_DISCHARGE_DLY_CNT_SHFT);
   }

   HWIO_APSS_PL_DLY_CONF0_OUTM(HWIO_APSS_PL_DLY_CONF0_LDO_DIG_DISCHARGE_DLY_CNT_BMSK, RegValue);

   /* Determine the TON settings. */
   if(Voltage <= 2000000)
   {
      TempValue = QAPI_MTP_APSS_RO_PTR->SmpsSelTon[0];
   }
   else if(Voltage <= 2500000)
   {
      TempValue = QAPI_MTP_APSS_RO_PTR->SmpsSelTon[1];
   }
   else
   {
      TempValue = QAPI_MTP_APSS_RO_PTR->SmpsSelTon[2];
   }

   RegValue  = TempValue << HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_PFM_SHFT;
   RegValue |= ((TempValue + 1)/ 2) << HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_ULP_SHFT;

   /* Update the TON settings. */
   HWIO_APSS_SMPS_SEL_TON_CONF_OUT(RegValue);
}

/**
   @brief Initiate a reset.

   This function will only return if the parameter is invalid.

   @param[in] ResetType  Type of reset to initiate.
*/
void qapi_PWR_Reset(qapi_PWR_Reset_Type_t ResetType)
{
   switch(ResetType)
   {
      case QAPI_PWR_RESET_TYPE_SUBSYSTEM_RESET_E:
         HWIO_AON_PME_APPS_RESET_OUT(HWIO_AON_PME_APPS_RESET_SUBSYSTEM_RESET);

         while(true) {}
         break;

      case QAPI_PWR_RESET_TYPE_SOC_COLD_RESET_E:
         /* Override the LFXTAL count to force a switch to SOSC before reset. */
         PWR_RetainedContext.LFCLK_Count = 0;

         /* Switch the mux to SOSC. */
         qapi_PWR_Set_LFCLK_Source(QAPI_PWR_LFCLK_SOURCE_SOSC, 0, NULL, NULL);

         HWIO_AON_PME_APPS_RESET_OUT(HWIO_AON_PME_APPS_RESET_SOC_COLD_RESET);

         while(true) {}
         break;

      default:
         break;
   }
}

/**
   @brief Gets the reason for the last reset of the subsystem.

   @return The reset reason.
*/
qapi_PWR_Reset_Reason_t qapi_PWR_Get_Reset_Reason(void)
{
   qapi_PWR_Reset_Reason_t RetVal;
   uint32_t               RegVal;

   RegVal = HWIO_AON_PME_APPS_STATUS_INM(HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_BMSK) >> HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_SHFT;

   switch(RegVal)
   {
      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_POWER_ON_RESET:
      default:
         RetVal = QAPI_PWR_RESET_REASON_POWER_ON_RESET_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_VDIO_EVENT:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_VDIO_EVENT_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_SOFTWARE:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_SOFTWARE_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_BROWNOUT:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_BROWNOUT_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_LONG_PRESS_MFP:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_MFB_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_ROT_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_ROT_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_BT_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_BTSS_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_COLD_RESET_APSS_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_COLD_RESET_APSS_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_SOFTWARE:
         RetVal = QAPI_PWR_RESET_REASON_WARM_RESET_SOFTWARE_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_ROT_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_WARM_RESET_ROT_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_BT_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_WARM_RESET_BTSS_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_WARM_RESET_APSS_WATCHDOG:
         RetVal = QAPI_PWR_RESET_REASON_WARM_RESET_APSS_WATCHDOG_E;
         break;

      case HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_SUBSYSTEM_RESET:
         RetVal = QAPI_PWR_RESET_REASON_SUBSYSTEM_RESET_SOFTWARE_E;
         break;
   }

   return(RetVal);
}

/**
   @brief Determines if the last boot was a cold boot or a resume from shutdown.

   This API can be called before qapi_PWR_Initialize if required.

   @return True if the last boot was a cold boot or false if it was a warm boot.
*/
qbool_t qapi_PWR_Is_Cold_Boot(void)
{
   qbool_t RetVal;

   if(PWR_Context.Initialized)
   {
      RetVal = PWR_Context.IsColdBoot;
   }
   else
   {
      RetVal = PWR_IsColdBoot();
   }

   return(RetVal);
}

/**
   @brief Enables and registers a callback for an AON interrupt.

   Note that only one callback can be registered for a given interrupt at a
   time.

   @param[in] Interrupt    Interrupt to register a callback for as defined by
                           QAPI_PWR_AON_INT_*.
   @param[in] InterruptCB  Function that will be called when the interrupt
                           fires.
   @param[in] UserParam    User specified parameter for the callback functions.

   @return QAPI_OK if the interrupt enable was changed successfully or a
           negative value if there was an error.
*/
qapi_Status_t qapi_PWR_Register_AON_Interrupt(uint32_t Interrupt, qapi_PWR_Aon_Int_Handler_CB_t InterruptCB, void *UserParam)
{
   qapi_Status_t RetVal;

   if((Interrupt >= QAPI_PWR_AON_INT_HFXTAL_STABLE) && (Interrupt <= QAPI_PWR_AON_INT_CETMR) && (InterruptCB != NULL))
   {
      /* Make sure the interrupt isn't already registered. */
      if(PWR_RetainedContext.AON_Int[Interrupt].Callback == NULL)
      {
         qapi_TSK_Enter_Critical();

         /* Set the callback information. */
         PWR_RetainedContext.AON_Int[Interrupt].Callback  = InterruptCB;
         PWR_RetainedContext.AON_Int[Interrupt].UserParam = UserParam;

         /* Clear the interrupt (in case it is already pending) and enable it. */
         qapi_PWR_Clear_AON_Int_Pending(Interrupt);
         HWIO_AON_PME_APPS_IRQ_EN_OUTM(1 << Interrupt, 1 << Interrupt);
         qapi_TSK_Exit_Critical();

         RetVal = QAPI_OK;
      }
      else
      {
         RetVal = QAPI_ERR_EXISTS;
      }
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Disables and unregisters a callback for an AON interrupt.

   @param[in] Interrupt  Interrupt to disable as defined by QAPI_PWR_AON_INT_*.

   @return true if an interrupt was previously registered or false if it wasn't.
*/
qbool_t qapi_PWR_Unregister_AON_Interrupt(uint32_t Interrupt)
{
   qapi_Status_t RetVal;

   if((Interrupt >= QAPI_PWR_AON_INT_HFXTAL_STABLE) && (Interrupt <= QAPI_PWR_AON_INT_CETMR))
   {
      RetVal = (qbool_t)(PWR_RetainedContext.AON_Int[Interrupt].Callback != NULL);

      /* Disable the interrupt and invalidate the callback information. */
      qapi_TSK_Enter_Critical();

#ifndef DISABLE_VDIO_FAULT_HANDLER
      /* The VDIO interrupt must remain enabled even when a callback is not
         registered in order for the VDIO Fault Handler to recognize that the
         VDIO error has occurred. */
      if(Interrupt != QAPI_PWR_AON_INT_VDIO)
#endif
      {
         HWIO_AON_PME_APPS_IRQ_EN_OUTM(1 << Interrupt, 0);
      }

      PWR_RetainedContext.AON_Int[Interrupt].Callback  = NULL;
      PWR_RetainedContext.AON_Int[Interrupt].UserParam = NULL;
      qapi_TSK_Exit_Critical();
   }
   else
   {
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Determines if an AON interrupt is pending.

   @param[in] Interrupt  Interrupt to check as defined by QAPI_PWR_AON_INT_*.

   @return true if the interrupt is pending or false if it isn't.
*/
qbool_t qapi_PWR_Get_AON_Int_Pending(uint32_t Interrupt)
{
   qapi_Status_t RetVal;

   if((Interrupt >= QAPI_PWR_AON_INT_HFXTAL_STABLE) && (Interrupt <= QAPI_PWR_AON_INT_CETMR))
   {
      RetVal = (qbool_t)(HWIO_AON_PME_APPS_IRQ_PENDING_INM(1 << Interrupt) != 0);
   }
   else
   {
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Clears a pending AON interrupt.

   @param[in] Interrupt  Interrupt to clear as defined by QAPI_PWR_AON_INT_*.

   @return QAPI_OK if the interrupt enable was changed successfully or a
           negative value if there was an error.
*/
qapi_Status_t qapi_PWR_Clear_AON_Int_Pending(uint32_t Interrupt)
{
   qapi_Status_t RetVal;

   if((Interrupt >= QAPI_PWR_AON_INT_HFXTAL_STABLE) && (Interrupt <= QAPI_PWR_AON_INT_CETMR))
   {
      HWIO_AON_PME_APPS_IRQ_PENDING_OUT(1 << Interrupt);
      RetVal = QAPI_OK;
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Set the MFP configuration.

   Edge detection description:
   The edge detection is sampled using the internal slow clock, the state is
   debounced and requires two consecutive clocks to register.
   If both (either) edges are selected there is no way to know which edge
   caused the MFP edge interrupt.
   If long press is selected the edge detection disabled to avoid spurious
   interrupts.
   Long press description:
   Asserting the MFP port high continuously for a period longer than 9 seconds
   will trigger a cold reset.
   Asserting PMU port high continuously for a period of 8 seconds or shorter
   will not trigger a cold reset.
   Periods between 8 and 9 seconds are undefined; this is due to the natural
   variation of the internal clock.

   @param[in] Config  Structure of MFP configuration data.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_PWR_Set_MFP(qapi_PWR_MFP_Config_t *Config)
{
    qapi_Status_t RetVal;
    uint32_t Mask, Val;

    if ((Config != NULL) && ((!Config->LongPressEnable) ||
        (Config->EdgeDetectType == QAPI_PWR_MFP_EDGE_DETECT_NONE_E)))
    {
        Mask = 0;
        Val = 0;

        Mask |= HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_BMSK |
                HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_BMSK |
                HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_BMSK;

        if (Config->LongPressEnable)
        {
            Val |= 0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_SHFT;
        }
        else
        {
            Val &= ~(0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_SHFT);
        }

        switch (Config->EdgeDetectType)
        {
            case QAPI_PWR_MFP_EDGE_DETECT_NONE_E:
                Val &= ~(0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_SHFT);
                Val &= ~(0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_SHFT);
                break;

            case QAPI_PWR_MFP_EDGE_DETECT_POS_E:
                Val |= 0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_SHFT;
                Val &= ~(0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_SHFT);
                break;

            case QAPI_PWR_MFP_EDGE_DETECT_NEG_E:
                Val &= ~(0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_SHFT);
                Val |= 0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_SHFT;
                break;

            case QAPI_PWR_MFP_EDGE_DETECT_BOTH_E:
                Val |= 0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_SHFT;
                Val |= 0x01 << HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_SHFT;
                break;

            default:
                break;
        }

        HWIO_AON_PME_SOC_CONTROL_OUTM(Mask, Val);
        RetVal = QAPI_OK;
    }
    else
    {
        RetVal = QAPI_ERR_INVALID_PARAM;
    }

    return(RetVal);
}

/**
   @brief Get the MFP current configuration.

   @param[in] Config  Structure of MFP configuration data.

   @return QAPI_OK on success or an error code on failure.
*/
qapi_Status_t qapi_PWR_Get_MFP(qapi_PWR_MFP_Config_t *Config)
{
    qapi_Status_t RetVal;
    uint32_t Val;

    if (Config == NULL)
    {
        RetVal = QAPI_ERR_INVALID_PARAM;
    }
    else
    {
        Val = HWIO_AON_PME_SOC_CONTROL_IN;

        Config->LongPressEnable = (qbool_t)((Val&HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_BMSK)!=0);

        if ((Val & HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_BMSK) &&
            (Val & HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_BMSK))
        {
            Config->EdgeDetectType = QAPI_PWR_MFP_EDGE_DETECT_BOTH_E;
        }
        else if (Val & HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_BMSK)
        {
            Config->EdgeDetectType = QAPI_PWR_MFP_EDGE_DETECT_POS_E;
        }
        else if (Val & HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_BMSK)
        {
            Config->EdgeDetectType = QAPI_PWR_MFP_EDGE_DETECT_NEG_E;
        }
        else
        {
            Config->EdgeDetectType = QAPI_PWR_MFP_EDGE_DETECT_NONE_E;
        }

        RetVal = QAPI_OK;
    }

    return(RetVal);
}

/**
   @brief Get the internal status.

   @param[out] Status  Structure to populate with internal status.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_PWR_Get_Status(qapi_PWR_Status_t *Status)
{
   qapi_Status_t RetVal;
   unsigned int  Index;

   if (Status == NULL)
   {
       RetVal = QAPI_ERR_INVALID_PARAM;
   }
   else
   {
      Status->ShutdownInvoked = PWR_RetainedContext.ShutdownInvoked;
      Status->VMA_Count       = PWR_RetainedContext.VMA_Count;
      Status->LFCLK_Count     = PWR_RetainedContext.LFCLK_Count;
      Status->HFCLK_Count     = PWR_RetainedContext.HFCLK_Count;
      Status->WakeValid       = PWR_RetainedContext.WakeValid;
      Status->ElectLocal      = PWR_RetainedContext.ElectLocal;
      Status->SOCStatus       = HWIO_AON_PME_SOC_STATUS_IN;

      for(Index=0;Index<QAPI_PWR_MAX_BALLOTS;Index++)
      {
         Status->WakeTime[Index] = PWR_RetainedContext.WakeTime[Index];
      }

      RetVal = QAPI_OK;
   }

   return(RetVal);
}

