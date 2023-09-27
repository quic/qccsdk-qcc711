/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_task.h"
#include "qapi_timer.h"
#include "qapi_heap.h"
#include "qapi_power.h"
#include "qcli_api.h"
#include "qcli_util.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define TMR_DBG
#ifdef TMR_DBG
#define TMR_PRINTF(...)                       QCLI_Printf(QCLI_Tmr_Handle, __VA_ARGS__)
#else
#define TMR_PRINTF(x, ...)
#endif

#define TMR_DEMO_SHUDOWN_CALLBACK_PRIORITY    (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT - 1)
#define MAX_COMPARATOR_NUMBER                 12
#define ABORT_SHUTDOWN_CALLBACK_PRIORITY      (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT - 0x12)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of time unit types.
*/
typedef enum
{
    TMR_UNIT_USEC_E,    /**< Time unit is microsecond. */
    TMR_UNIT_MSEC_E,    /**< Time unit is millisecond. */
    TMR_UNIT_SEC_E,     /**< Time unit is second. */
    TMR_UNIT_MIN_E,     /**< Time unit is minute. */
    TMR_UNIT_HOUR_E     /**< Time unit is hour. */
} TMR_DemoTimeUnit_t;

/**
   Structure representing the retained timer demo context information.
*/
typedef struct TMR_DemoRetnContext_s
{
    uint8_t                   UsedCompNum;                      /**< The number of inused comparators. */
    void                     *ShutdownCBHandle;                 /**< Handle for the registered shutdown callbacks. */
    qapi_TMR_Comp_Instance_t *CompParam[MAX_COMPARATOR_NUMBER]; /**< User specified parator for comparators. */
} TMR_DemoRetnContext_t;

/**
   Structure representing the timer demo context information.
*/
typedef struct TMR_DemoContext_s
{
    qapi_TSK_Handle_t  TaskHandle;  /**< Timer demo task handle. */
    void              *TimePtr;     /**< Pointer that records time. */
    uint32_t           WakeComp;    /**< Comparators that times out right after wakeup. */
    void              *AbortShutCB; /**< Handler for the power callback which is specific to abort shutdown. */
    qapi_PWR_Ballot_t  TmrBallot;   /**< Ballot of timer voting. */
} TMR_DemoContext_t;

/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

/**
   Handle for timer QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Tmr_Handle;

static TMR_DemoContext_t TMR_DemoContext;
static char Tmr_ISR_Check_Enable = 0; /* this flag is only used to test the related API. */
static char Tmr_ISR_Context_Count = 0;
static TMR_DemoRetnContext_t TMR_DemoRetnContext __attribute__((section (".bss.retain")));

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static QCLI_Command_Status_t cmd_Tmr_CompInit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_CompDeinit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_CompStart(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_CompStop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_GetCompInfo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_GetCurTime(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_Delay(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Tmr_AbortShutDown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t TMR_CMD_List[] =
{
    /* cmd_function         cmd_string       usage_string                        description */
    {cmd_Tmr_CompInit,      "CompInit",      "[Deferrable]",                     "Init a comparator"},
    {cmd_Tmr_CompDeinit,    "CompDeinit",    "<Comp>",                           "Deinit a comparator"},
    {cmd_Tmr_CompStart,     "CompStart",     "<Comp> <Timeout> <Unit> <Repeat>", "Start a comparator"},
    {cmd_Tmr_CompStop,      "CompStop",      "<Comp>",                           "Stop a comparator"},
    {cmd_Tmr_GetCompInfo,   "GetCompInfo",   "<Comp> <InfoType>",                "Get a comparator information"},
    {cmd_Tmr_GetCurTime,    "GetTime",       "",                                 "Get current time"},
    {cmd_Tmr_Delay,         "Delay",         "<Time>",                           "Delay for some time in millisecond"},
    {cmd_Tmr_AbortShutDown, "AbortShutDown", "<Abort>",                          "Abort shutdown"}
};

const QCLI_Command_Group_t TMR_CMD_Group =
{
    "TIMER",
    (sizeof(TMR_CMD_List) / sizeof(TMR_CMD_List[0])),
    TMR_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief initialize timer demo.
*/
void Initialize_Timer_Demo(void)
{
    uint8_t i;
    
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Tmr_Handle = QCLI_Register_Command_Group(NULL, &TMR_CMD_Group);
    if(QCLI_Tmr_Handle)
    {
        TMR_PRINTF("TIMER Registered \n");

        if (TMR_DemoContext.WakeComp)
        {
            for (i = 0; i < MAX_COMPARATOR_NUMBER; i++)
            {
                if ((TMR_DemoContext.WakeComp >> i) & 0x1)
                {
                    TMR_PRINTF("Comparator %d time out at %lluus\n", i, ((TMR_DemoContext.TimePtr) ? (*((uint64_t *)(TMR_DemoContext.TimePtr) + i)) : 0));
                }
            }
            TMR_DemoContext.WakeComp = 0;
        }
    }
}

/**
   @brief The task for timer demo.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of all events that triggered since last
                          call to this function.
   @param[in] UserParam   User specified parameter for the task function.

   @return The time in milliseconds before this function needs to be called again.
*/
static uint32_t Tmr_Task(qapi_TSK_Handle_t Handle, uint32_t EventMask, void *Param)
{
    uint8_t i;

    if(Tmr_ISR_Check_Enable)
    {
        TMR_PRINTF("TSK_ISR_State %d, ISR count %d\n", qapi_TSK_Check_Interrupt_Context(), Tmr_ISR_Context_Count);
    }
    if (EventMask & (~(0xFFFFFFFF << MAX_COMPARATOR_NUMBER)))
    {
        for (i = 0; i < MAX_COMPARATOR_NUMBER; i++)
        {
            if ((EventMask >> i) & 0x1)
            {
                if (QCLI_Tmr_Handle)
                {
                    TMR_PRINTF("Comparator %d time out at %lluus\n", i, ((TMR_DemoContext.TimePtr) ? (*((uint64_t *)(TMR_DemoContext.TimePtr) + i)) : 0));
                }
                else
                {
                    TMR_DemoContext.WakeComp |= (1 << i);
                }
            }
        }
    }

    return QAPI_TSK_INFINITE_WAIT;
}

/**
   @brief Compartor callback function.

   @param[in] UserParam  User specified parameter provided when the callback
                         is registered.
*/
static void Tmr_CompCallback(void *UserParam)
{
    qapi_TMR_Comp_Instance_t Comp;
    uint64_t                 Now;

    Now  = qapi_TMR_Get_Current_Time();
    Comp = *(qapi_TMR_Comp_Instance_t *)UserParam;
    
    if(Tmr_ISR_Check_Enable)
    {
        if(qapi_TSK_Check_Interrupt_Context())
            Tmr_ISR_Context_Count++;
    }
    if (TMR_DemoContext.TaskHandle != NULL) 
    {
        if (TMR_DemoContext.TimePtr != NULL)
        {
            *((uint64_t *)(TMR_DemoContext.TimePtr) + Comp) = Now;
        }
        qapi_TSK_Signal_Task(TMR_DemoContext.TaskHandle, (1 << Comp));
    }
}

/**
   @brief Timer demo shutdown callback function before going to deep sleep.

   @param[in] UserParam  User specified parameter provided when the callback
                         is registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t Tmr_ShutdownCallback(void *UserParam)
{
    /* Nothing to do. */
    return true;
}

/**
   @brief Timer demo wakeup callback function when wakeup from deep sleep or
          shutdown is aborted.

   @param[in] ShutdownAborted  Flag indicating if this function is called because
                               a shutdown was aborted (true) or because the
                               subsystem woke from shutdown (false).
   @param[in] UserParam        User specified parameter provided when the callback
                               is registered.
*/
static void Tmr_WakeupCallback(qbool_t ShutdownAborted, void *UserParam)
{
    if ((!ShutdownAborted) && (TMR_DemoRetnContext.UsedCompNum > 0))
    {
        TMR_DemoContext.TimePtr = qapi_Malloc(sizeof(uint64_t) * MAX_COMPARATOR_NUMBER);
        TMR_DemoContext.TaskHandle = qapi_TSK_Create_Task(Tmr_Task, NULL);
    }
}

/**
   @brief Callback function before going to deep sleep which will abort shutdown procedure.

   @param[in] UserParam  User specified parameter provided when the callback
                         is registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t Tmr_AbortShutDownCallback(void *UserParam)
{
    /* Vote for APSS to stay active. */
    qapi_PWR_Vote_Local_State(TMR_DemoContext.TmrBallot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
    return false;
}

/**
   @brief Callback function when shutdown is aborted.

   @param[in] ShutdownAborted  Flag indicating if this function is called because
                               a shutdown was aborted (true) or because the
                               subsystem woke from shutdown (false).
   @param[in] UserParam        User specified parameter provided when the callback
                               is registered.
*/
static void Tmr_AbortWakeupCallback(qbool_t ShutdownAborted, void *UserParam)
{
    /* Nothing to do. */
}

/**
   @brief Comparator init test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_CompInit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t  Comp;
    qapi_TMR_Comp_Instance_t *RetainedComp = NULL;
    qapi_Status_t             Status;
    qbool_t                   Deferrable;

    if (Parameter_Count > 1)
    {
        TMR_PRINTF("CompInit [Deferrable]\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count == 1)
    {
        Deferrable = (qbool_t)(Parameter_List[0].Integer_Value != 0);
    }
    else
    {
        Deferrable = false;
    }

    RetainedComp = qapi_Malloc_Retain(sizeof(qapi_TMR_Comp_Instance_t));
    if (RetainedComp == NULL)
    {
        TMR_PRINTF("ERROR: No enough memory\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    Status = qapi_TMR_Comp_Init(&Comp, Tmr_CompCallback, RetainedComp, Deferrable);
    if (Status == QAPI_OK)
    {
        if (TMR_DemoRetnContext.UsedCompNum == 0)
        {
            TMR_DemoContext.TimePtr = qapi_Malloc(sizeof(uint64_t) * MAX_COMPARATOR_NUMBER);
            TMR_DemoContext.TaskHandle = qapi_TSK_Create_Task(Tmr_Task, NULL);
            TMR_DemoRetnContext.ShutdownCBHandle = qapi_PWR_Register_Shutdown_Callbacks(Tmr_ShutdownCallback, Tmr_WakeupCallback, TMR_DEMO_SHUDOWN_CALLBACK_PRIORITY, NULL);
            
            if (TMR_DemoContext.TimePtr == NULL || TMR_DemoContext.TaskHandle == NULL || TMR_DemoRetnContext.ShutdownCBHandle == NULL)
            {
                if (TMR_DemoContext.TimePtr != NULL)
                {
                    qapi_Free(TMR_DemoContext.TimePtr);
                    TMR_DemoContext.TimePtr = NULL;
                }
                
                if (TMR_DemoContext.TaskHandle != NULL)
                {
                    qapi_TSK_Delete_Task(TMR_DemoContext.TaskHandle);
                    TMR_DemoContext.TaskHandle = NULL;
                }

                if (TMR_DemoRetnContext.ShutdownCBHandle != NULL)
                {
                    qapi_PWR_Unregister_Callback(TMR_DemoRetnContext.ShutdownCBHandle);
                    TMR_DemoRetnContext.ShutdownCBHandle = NULL;
                }

                (void)qapi_TMR_Comp_Deinit(Comp);
                qapi_Free(RetainedComp);
                TMR_PRINTF("ERROR: No resource\n");
                return QCLI_STATUS_ERROR_E;
            }
        }
        
        TMR_DemoRetnContext.UsedCompNum++;
        *RetainedComp = Comp;
        TMR_DemoRetnContext.CompParam[Comp] = RetainedComp;
        TMR_PRINTF("Comparator %d (%s) Init successfully\n", Comp, Deferrable ? "deferrable":"non-deferrable");
        return QCLI_STATUS_SUCCESS_E;
    }

    qapi_Free(RetainedComp);
    TMR_PRINTF("Comp init failed %d\n", Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Comparator deinit test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_CompDeinit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t Comp;
    qapi_Status_t            Status;
    
    if (Parameter_Count != 1 || Parameter_List == NULL)
    {
        TMR_PRINTF("CompDeinit <Comp>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Comp = Parameter_List[0].Integer_Value;

    Status = qapi_TMR_Comp_Deinit(Comp);
    if (Status == QAPI_OK)
    {
        qapi_Free(TMR_DemoRetnContext.CompParam[Comp]);
        TMR_DemoRetnContext.CompParam[Comp] = NULL;
        
        TMR_DemoRetnContext.UsedCompNum--;
        if (TMR_DemoRetnContext.UsedCompNum == 0)
        {
            qapi_Free(TMR_DemoContext.TimePtr);
            TMR_DemoContext.TimePtr = NULL;
                    
            qapi_TSK_Delete_Task(TMR_DemoContext.TaskHandle);
            TMR_DemoContext.TaskHandle = NULL;

            qapi_PWR_Unregister_Callback(TMR_DemoRetnContext.ShutdownCBHandle);
            TMR_DemoRetnContext.ShutdownCBHandle = NULL;
        }
        TMR_PRINTF("Comparator %d deinit successfully\n", Comp);
        return QCLI_STATUS_SUCCESS_E;
    }

    TMR_PRINTF("Comp deinit failed %d\n", Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Comparator start test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_CompStart(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t Comp;
    uint64_t                 Timeout;
    qbool_t                  Repeat;
    qapi_Status_t            Status;
    uint64_t                 CurTime;
    
    if (Parameter_Count != 4 || Parameter_List == NULL)
    {
        TMR_PRINTF("CompStart <Comp> <Timeout> <Unit> <Repeat>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[1].Integer_Value <= 0)
    {
        TMR_PRINTF("Timeout should be bigger than 0\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[2].Integer_Value < TMR_UNIT_USEC_E || Parameter_List[2].Integer_Value > TMR_UNIT_HOUR_E)
    {
        TMR_PRINTF("Time unit should be between %d and %d\n", TMR_UNIT_USEC_E, TMR_UNIT_HOUR_E);
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[3].Integer_Value != 0 && Parameter_List[3].Integer_Value != 1)
    {
        TMR_PRINTF("Repeat should be 0 or 1\n");
        return QCLI_STATUS_ERROR_E;
    }

    Comp = Parameter_List[0].Integer_Value;
    Timeout = (uint64_t)(Parameter_List[1].Integer_Value);
    switch (Parameter_List[2].Integer_Value)
    {
        case TMR_UNIT_HOUR_E:
        Timeout *= 60;

        case TMR_UNIT_MIN_E:
        Timeout *= 60;

        case TMR_UNIT_SEC_E:
        Timeout *= 1000;

        case TMR_UNIT_MSEC_E:
        Timeout *= 1000 ;

        case TMR_UNIT_USEC_E:
        default:
        break;
    }
    
    Repeat = (qbool_t)(Parameter_List[3].Integer_Value);

    Status = qapi_TMR_Comp_Start(Comp, Timeout, Repeat);
    if (Status == QAPI_OK)
    {
        CurTime = qapi_TMR_Get_Current_Time();
        TMR_PRINTF("Comparator %d started successfully at %lluus\n", Comp, CurTime);
        return QCLI_STATUS_SUCCESS_E;
    }

    TMR_PRINTF("Comparator %d started failed %d\n", Comp, Status);
    return QCLI_STATUS_ERROR_E; 
}

/**
   @brief Comparator stop test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_CompStop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t Comp;
    qapi_Status_t Status;
    
    if (Parameter_Count != 1 || Parameter_List == NULL)
    {
        TMR_PRINTF("CompStop <Comp>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Comp = Parameter_List[0].Integer_Value;

    Status = qapi_TMR_Comp_Stop(Comp);
    if (Status == QAPI_OK)
    {
        TMR_PRINTF("Comparator %d stopped successfully\n", Comp);
        return QCLI_STATUS_SUCCESS_E;
    }

    TMR_PRINTF("Comparator %d stopped failed\n", Comp);
    return QCLI_STATUS_ERROR_E; 
}

/**
   @brief Get comparator information test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_GetCompInfo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t Comp;
    qapi_TMR_Comp_Info_t     Info;
    uint64_t                 Data;
    qapi_Status_t            Status;
    
    if (Parameter_Count != 2 || Parameter_List == NULL)
    {
        TMR_PRINTF("GetCompInfo <Comp> <InfoType>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Comp = Parameter_List[0].Integer_Value;
    Info = (qapi_TMR_Comp_Info_t)Parameter_List[1].Integer_Value;

    Status = qapi_TMR_Get_Comp_Info(Comp, Info, &Data);
    if (Status == QAPI_OK)
    {
        TMR_PRINTF("Get comparator %d info successfully %lluus\n", Comp, Data);
        return QCLI_STATUS_SUCCESS_E;
    }

    TMR_PRINTF("Get comparator %d info failed %d\n", Comp, Status);
    return QCLI_STATUS_ERROR_E; 
}

/**
   @brief Get current time test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_GetCurTime(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint64_t CurTime;

    if (Parameter_Count != 0)
    {
        TMR_PRINTF("GetTime\n");
        return QCLI_STATUS_ERROR_E;
    }

    CurTime = qapi_TMR_Get_Current_Time();
    if (CurTime != 0)
    {
        TMR_PRINTF("Current time is %lluus\n", CurTime);
        return QCLI_STATUS_SUCCESS_E;
    }

    TMR_PRINTF("Get current time failed\n");
    return QCLI_STATUS_ERROR_E; 
}

/**
   @brief Timer delay test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_Delay(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t DelayTime;
    uint64_t StartTime;
    uint64_t EndTime;
    
    if (Parameter_Count != 1 || Parameter_List == NULL)
    {
        TMR_PRINTF("Delay <Time>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value <= 0)
    {
        TMR_PRINTF("Delay time should be bigger than 0\n");
        return QCLI_STATUS_ERROR_E;
    }

    DelayTime = (uint32_t)(Parameter_List[0].Integer_Value);

    StartTime = qapi_TMR_Get_Current_Time();
    qapi_TMR_Delay_Us(DelayTime);
    EndTime = qapi_TMR_Get_Current_Time();

    TMR_PRINTF("Timer delay finished, start %lluus, end %lluus\n", StartTime, EndTime);
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Abort shutdown procedure or not when shutdown callback is called.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Tmr_AbortShutDown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    if (Parameter_Count != 1 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid)
    {
        TMR_PRINTF("AbortShutDown <Abort>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value != 0 && Parameter_List[0].Integer_Value != 1)
    {
        TMR_PRINTF("Abort value should be 0 or 1\n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((Parameter_List[0].Integer_Value == 1) && (TMR_DemoContext.AbortShutCB == NULL))
    {
        TMR_DemoContext.AbortShutCB = qapi_PWR_Register_Shutdown_Callbacks(Tmr_AbortShutDownCallback, Tmr_AbortWakeupCallback, ABORT_SHUTDOWN_CALLBACK_PRIORITY, NULL);
        if (TMR_DemoContext.AbortShutCB == NULL)
        {
            TMR_PRINTF("Allow to abort shutdown failed\n");
            return QCLI_STATUS_ERROR_E;
        }
        TMR_DemoContext.TmrBallot = qapi_PWR_Acquire_Ballot();
    }
    else if ((Parameter_List[0].Integer_Value == 0) && (TMR_DemoContext.AbortShutCB != NULL))
    {
        qapi_PWR_Unregister_Callback(TMR_DemoContext.AbortShutCB);
        TMR_DemoContext.AbortShutCB = NULL;
        
        qapi_PWR_Vote_Local_State(TMR_DemoContext.TmrBallot, QAPI_PWR_STATE_SHUTDOWN_E, QAPI_PWR_NO_WAKE);
        qapi_PWR_Release_Ballot(TMR_DemoContext.TmrBallot);
        TMR_DemoContext.TmrBallot = 0;
    }

    TMR_PRINTF("%s to abort shutdown success\n", (Parameter_List[0].Integer_Value ? "Allow" : "Disallow"));
    return QCLI_STATUS_SUCCESS_E;
}

