/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>

#include "qcc710.h"
#include "timer.h"

#include "qapi_task.h"
#include "qapi_heap.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define RESERVED_EVENT_MASK      (QAPI_TSK_EVENT_TIMEOUT | QAPI_TSK_EVENT_INIT |QAPI_TSK_EVENT_DELETE)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Link list entry containing the information for a single task.
*/
typedef struct TaskListEntry_s
{
   struct TaskListEntry_s  *Next;          /**< Pointer to the next task in the list. */
   qapi_TSK_Function_t      TaskFunction;  /**< Function for the task. */
   void                    *UserParam;     /**< User specified parameter for the task. */
   uint32_t                 EventMask;     /**< Mask of current events for the task. */
   uint32_t                 TimeRemaining; /**< Time remaining beore the task needs to be called. */
} TaskListEntry_t;

/**
   Context information for qapi_TSK module.
*/
typedef struct qapi_TSK_Context_s
{
   qapi_TSK_Signal_CB_t  Signal_CB;     /**< Callback function to signal that qapi_TSK_Process_Scheduler() needs to be called. */
   void                 *SignalParam;   /**< User parameters for the signal callback. */
   qbool_t               RunScheduler;  /**< Flag indicating the scheduler needs to be run. */
   TaskListEntry_t      *TaskList;      /**< List of tasks. */
   uint32_t              LastTickCount; /**< Tick count the last time the scheduler was run. */
   qbool_t               LockState;     /**< Previous state of the lock before it was taken by this module. */
   uint8_t               LockCount;     /**< Number of times the critical section lock has been taken. */
} qapi_TSK_Context_t;

/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

qapi_TSK_Context_t TSK_Context;


/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static void TSK_SignalScheduler(void);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Makes sure the scheduler is run.

   This function is called when an event occurs that requires the scheduler be
   run again. It will internally flag the scheduler needs to run again (in case
   it is already running) and inform the signal callback.
*/
static void TSK_SignalScheduler(void)
{
   TSK_Context.RunScheduler = true;

   if(TSK_Context.Signal_CB != NULL)
   {
      (*(TSK_Context.Signal_CB))(TSK_Context.SignalParam);
   }
}

/**
   @brief Creates a task and adds it to the scheduler.

   Upon creation, the task will immediately be set as pending and its function
   will be called the next time the scheduler runs.

   @param[in] TaskFunction  Function called to process the task.
   @param[in] UserParam     User specified parameter that will be provided to
                            the task function.

   @return The handle for the task or NULL if there was an error.
*/
qapi_TSK_Handle_t qapi_TSK_Create_Task(qapi_TSK_Function_t TaskFunction, void *UserParam)
{
   TaskListEntry_t *NewTask;
   TaskListEntry_t *CurrentTask;

   if(TaskFunction != NULL)
   {
      /* Create the task. */
      NewTask = qapi_Malloc(sizeof(TaskListEntry_t));
      if(NewTask != NULL)
      {
         /* Initialize the task. */
         memset(NewTask, 0, sizeof(TaskListEntry_t));
         NewTask->TaskFunction  = TaskFunction;
         NewTask->UserParam     = UserParam;
         NewTask->EventMask     = QAPI_TSK_EVENT_INIT;
         NewTask->TimeRemaining = QAPI_TSK_INFINITE_WAIT;

         /* Append the task to the task list. */
         qapi_TSK_Enter_Critical();

         if(TSK_Context.TaskList == NULL)
         {
            /* Update the current tick count when the first task is added. */
            TSK_Context.LastTickCount = qapi_TSK_Get_Tick_Count();

            TSK_Context.TaskList = NewTask;
         }
         else
         {
            CurrentTask = TSK_Context.TaskList;
            while(CurrentTask->Next != NULL)
            {
               CurrentTask = CurrentTask->Next;
            }

            CurrentTask->Next = NewTask;
         }

         qapi_TSK_Exit_Critical();

         /* Signal the scheduler to run. */
         TSK_SignalScheduler();
      }
   }
   else
   {
      NewTask = NULL;
   }

   return((qapi_TSK_Handle_t)NewTask);
}

/**
   @brief Deletes a task.

   When called, the specified task will be marked to be deleted.  Its function
   will be called the next time its scheduler runs and upon its return, the task
   will be removed from the scheduler and deleted.

   @param[in] TaskHandle  Handle of the task.
*/
void qapi_TSK_Delete_Task(qapi_TSK_Handle_t TaskHandle)
{
   TaskListEntry_t *Task;

   if(TaskHandle != NULL)
   {
      Task = (TaskListEntry_t *)TaskHandle;

      /* Flag the task to be deleted. */
      qapi_TSK_Enter_Critical();
      Task->EventMask |= QAPI_TSK_EVENT_DELETE;
      qapi_TSK_Exit_Critical();

      /* Signal the scheduler to run. */
      TSK_SignalScheduler();
   }
}

/**
   @brief Signals that a task needs to run.

   This function will set the task to pending and its function will be called
   the next time the scheduler is run.

   This function can be called from an interrupt context.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of events that need to be signaled to the task.
                          The meaning of these bits is up to the user but at
                          least one but must be set.  Also note that the values
                          defined by the QAPI_TSK_EVENT_* are reserved and
                          cannot be set by this function.  This mask will be
                          or'ed with the current event mask for the task.

   @return QAPI_OK if the task was signaled successfully or a negative value if
           there was an error.
*/
qapi_Status_t qapi_TSK_Signal_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask)
{
   qapi_Status_t    RetVal;
   TaskListEntry_t *Task;

   EventMask &= ~RESERVED_EVENT_MASK;
   if ((TaskHandle != NULL) && (EventMask != 0))
   {
      Task = (TaskListEntry_t *)TaskHandle;

      /* Flag the task to be deleted. */
      qapi_TSK_Enter_Critical();
      Task->EventMask |= EventMask;
      qapi_TSK_Exit_Critical();

      /* Signal the scheduler to run. */
      TSK_SignalScheduler();

      RetVal = QAPI_OK;
   }
   else
   {
      RetVal = QAPI_ERR_INVALID_PARAM;
   }

   return(RetVal);
}

/**
   @brief Get the current system tick count.

   @return Current millisecond tick count.
*/
uint32_t qapi_TSK_Get_Tick_Count(void)
{
   return TMR_GetCurTimeMs();
}

/**
   @brief Enters a critical section.

   This function supports entering crytical sections recursively.  Interrupts
   will only be re-enabled when the number of calls to qapi_TSK_Exit_Critical()
   matches the number of times qapi_TSK_Enter_Critical() has been called.

   @return True if this is the first time the lock was taken or false if it was
           not.
*/
qbool_t qapi_TSK_Enter_Critical(void)
{
   qbool_t LockState;
   qbool_t RetVal;

   /* Get the state of the PRIMASK and make sure interupts are disabled. */
   LockState = (qbool_t)(__get_PRIMASK() != 0);
   __set_PRIMASK(1);

   if(TSK_Context.LockCount == 0)
   {
      /* This is the first time the critical section was entered so store the
         previous state. */
      TSK_Context.LockState = LockState;
      RetVal = true;
   }
   else
   {
      RetVal = false;
   }

   TSK_Context.LockCount ++;

   return(RetVal);
}

/**
   @brief Exits a critical section.

   Interrupts will only be re-enabled when the number of calls to
   qapi_TSK_Exit_Critical() matches the number of times qapi_TSK_Enter_Critical()
   has been called.

   @return True if this is the last time the lock needs to be released (and
           previous interrupt state was restored) or false if it is expected to
           be released again or it was released too many times.
*/
qbool_t qapi_TSK_Exit_Critical(void)
{
   qbool_t RetVal;

   RetVal = false;
   if(TSK_Context.LockCount != 0)
   {
      TSK_Context.LockCount--;

      if(TSK_Context.LockCount == 0)
      {
         /* Restore the previous interrupt state. */
         if(!(TSK_Context.LockState))
         {
            __set_PRIMASK(0);
            RetVal = true;
         }
      }
   }

   return(RetVal);
}

/**
   @brief Initializes this module.

   This function must be called before any other function in this module.

   @param[in] Signal_CB  Function called to signal that the scheduler needs to
                         be run.  This parameter may be NULL if the signal
                         callback isn't required for the platform.
   @param[in] UserParam  User specified parameter that will be provided to the
                         Signal_CB.  This is ignored if Signal_CB is NULL.
*/
void qapi_TSK_Init(qapi_TSK_Signal_CB_t Signal_CB, void *UserParam)
{
   memset(&TSK_Context, 0, sizeof(qapi_TSK_Context_t));
   TSK_Context.Signal_CB     = Signal_CB;
   TSK_Context.SignalParam   = UserParam;
}

/**
   @brief Processes the scheduler and executes all pending tasks.

   @return The time in milliseconds until this function needs to be called
           again (this value can be used as a system wake timer).  If
           TSK_INFINITE_WAIT is returned, this function doesn't need to be
           called until an asynchronous event occurs.
*/
uint32_t qapi_TSK_Process_Scheduler(void)
{
   uint32_t         WaitTime;
   uint32_t         CurrentTicks;
   uint32_t         ElapsedTicks;
   uint32_t         EventMask;
   TaskListEntry_t *PreviousTask;
   TaskListEntry_t *CurrentTask;


   /* Run the scheduler until nothing more needs to be done. */
   CurrentTicks = qapi_TSK_Get_Tick_Count();
   ElapsedTicks = CurrentTicks - TSK_Context.LastTickCount;
   do
   {
      WaitTime = QAPI_TSK_INFINITE_WAIT;
      TSK_Context.RunScheduler = false;
      TSK_Context.LastTickCount = CurrentTicks;

      PreviousTask = NULL;
      CurrentTask  = TSK_Context.TaskList;
      while(CurrentTask != NULL)
      {
         qapi_TSK_Enter_Critical();

         /* Check the time remaining for the task. */
         if(CurrentTask->TimeRemaining <= ElapsedTicks)
         {
            CurrentTask->EventMask |= QAPI_TSK_EVENT_TIMEOUT;
         }
         else if(CurrentTask->TimeRemaining != QAPI_TSK_INFINITE_WAIT)
         {
            CurrentTask->TimeRemaining -= ElapsedTicks;
         }

         /* Call the task if any events are left. */
         EventMask = CurrentTask->EventMask;
         CurrentTask->EventMask = 0;

         qapi_TSK_Exit_Critical();

         if(EventMask != 0)
         {
            CurrentTask->TimeRemaining = (*(CurrentTask->TaskFunction))((qapi_TSK_Handle_t)CurrentTask, EventMask, CurrentTask->UserParam);
         }

         qapi_TSK_Enter_Critical();

         /* Check if the task needs to be deleted. */
         if(EventMask & QAPI_TSK_EVENT_DELETE)
         {
            /* Remove the task from the scheduler. */
            if(PreviousTask == NULL)
            {
               TSK_Context.TaskList = CurrentTask->Next;
               qapi_Free(CurrentTask);
               CurrentTask = TSK_Context.TaskList;
            }
            else
            {
               PreviousTask->Next = CurrentTask->Next;
               qapi_Free(CurrentTask);
               CurrentTask = PreviousTask->Next;
            }
         }
         else
         {
            /* Apply the time remaining for the task to the overall wait time. */
            if(WaitTime > CurrentTask->TimeRemaining)
            {
               WaitTime = CurrentTask->TimeRemaining;
            }

            /* Advance to the next task. */
            PreviousTask = CurrentTask;
            CurrentTask  = CurrentTask->Next;
         }

         qapi_TSK_Exit_Critical();
      }

      /* Update the local elapsed ticks to see if we need to run the scheduler
         again. */
      CurrentTicks = qapi_TSK_Get_Tick_Count();
      ElapsedTicks = CurrentTicks - TSK_Context.LastTickCount;
   }
   while ((TSK_Context.RunScheduler) || (WaitTime <= ElapsedTicks));

   return(WaitTime);
}

/**
   @brief Checks if any tasks have an event pending. This will not catch task
          timeouts.

   @return True if a scheduler is idle or false if an event is pending.
*/
qbool_t qapi_TSK_Check_Idle(void)
{
   return (!TSK_Context.RunScheduler);
}

/**
   @brief Get current context, task or interrupt.

   @return
   0 -- task level. \n
   non-0 -- interrupt level.
*/
qbool_t qapi_TSK_Check_Interrupt_Context(void)
{
    return (qbool_t)__get_IPSR();
}

