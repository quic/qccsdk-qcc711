/*
 * Copyright (c) 2015-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "qcc710.h"

#include "qapi_types.h"
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_uart.h"
#include "qapi_gpio.h"
#include "qapi_power.h"
#include "qapi_timer.h"

#include "qcli.h"
#include "qcli_util.h"
#include "qcli_pal.h"

#include "ipc.h"

#ifdef PAL_USE_RTT_CONSOLE
#include "SEGGER_RTT.h"
#else
#include "qapi_uart.h"
#endif

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define PAL_CONSOLE_INSTANCE     QAPI_UART_INSTANCE_SE2_E
#define INPUT_BUFFER_SIZE        (256)

#ifdef PAL_USE_RTT_CONSOLE
#define QCLI_TSK_WAIT_TIME       (50)
#else
#define QCLI_TSK_WAIT_TIME       (QAPI_TSK_INFINITE_WAIT)
#endif

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Context information for the PAL module.
*/
typedef struct PAL_Context_s
{
   QCLI_Group_Handle_t  QCLI_Handle;                    /**< QCLI handle for printing to the console. */

   qapi_TSK_Handle_t    QCLI_Task;                      /**< Task for QCLI processing. */
   uint8_t              LockCount;                      /**< Number of times the lock has been taken. */

#ifndef PAL_USE_RTT_CONSOLE
   qapi_UART_Instance_t ConsoleUART;
#endif

   char                 InputBuffer[INPUT_BUFFER_SIZE]; /**< Buffer for data read from the console. */
   uint32_t             InputInIndex;                   /**< Current input buffer index for storing data read from the console. */
   uint32_t             InputOutIndex;                  /**< Current input buffer index for reading data to send to QCLI. */
   volatile uint32_t    InputByteCount;                 /**< Current number of bytes in the input buffer. */

   qbool_t              AbortShutdown;
} PAL_Context_t;

typedef struct PAL_RetainedContext_s
{
   void              *PwrCallbacks; /**< Handle for registered power callbacks. */
   qapi_PWR_Ballot_t  PwrBallot;    /**< Ballot of power voting. */
   qapi_PWR_Ballot_t  UartBallot;   /**< Ballot of power voting. */

   /* Variables to demonstrate the power callbacks. */
   volatile uint32_t  ShutdownCount; /**< Number of times shutdown was entered. */
   volatile uint32_t  WakeCount;     /**< Number of times APSS has woken from shutdown. */
} PAL_RetainedContext_t;


/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

static PAL_Context_t         PAL_Context;
static PAL_RetainedContext_t PAL_RetainedContext __attribute__((section (".bss.retain")));

/**
   @brief Alternative GPIO global configuration.
*/
static qapi_GPIO_Alt_Config_t Alternative_GPIO_Config[QAPI_GPIO_MAX_ID_E] =
{
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO0  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO1  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO2  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO3  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO4  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO5  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO6  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO7  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO8  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO9  */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO10 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO11 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO12 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO13 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO14 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO15 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO16 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO17 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO18 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO19 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO20 */
    {2, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO21 */
    {2, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO22 */
    {2, QAPI_GPIO_OUTPUT_E, QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO23 */
    {2, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_UP_E,   QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO24 */
    {0, QAPI_GPIO_INPUT_E,  QAPI_GPIO_PULL_DOWN_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO25 */
};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

#ifndef PAL_USE_RTT_CONSOLE
static void Uart_Tx_CB(uint32_t Status, uint32_t Length, void *CallbackCtxt);
static void Uart_Rx_CB(uint32_t Status, uint32_t Length, void *CbCtxt);
#endif

static qbool_t PAL_Shutdown_CB(void *UserParam);
static void PAL_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam);
static void PAL_Init_Power(qbool_t IsColdBoot);
static uint32_t QCLI_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);
static QCLI_Command_Status_t PAL_Cmd_Shutdown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t PAL_Cmd_List[] =
{
   /* cmd_function    cmd_string  usage_string                        description */
   {PAL_Cmd_Shutdown, "Shutdown", "[WakeTime ms] [Abort (optional)]", "Enter shutdown."}
};

const QCLI_Command_Group_t PAL_Cmd_Group = {"", sizeof(PAL_Cmd_List) / sizeof(QCLI_Command_t), PAL_Cmd_List};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

#ifndef PAL_USE_RTT_CONSOLE
/**
  @brief UART transmit operation callback type.

  @param[in] Status        Result of current Tx/Rx.
  @param[in] Length        Transmit data length or received data length.
  @param[in] CallbackCtxt  User-specified parameter.
*/
static void Uart_Tx_CB(uint32_t Status, uint32_t Length, void *CallbackCtxt)
{
   if(qapi_UART_Get_Tx_Remaining(PAL_Context.ConsoleUART) == 0)
   {
      /* All data has been sent so cancel the UART vote to keep the system
         active. */
      qapi_PWR_Vote_Local_State(PAL_RetainedContext.UartBallot, QAPI_PWR_STATE_SHUTDOWN_E, QAPI_PWR_NO_WAKE);
   }
}

/**
  @brief UART receive operation callback type.

  @param[in] Status        Result of current Tx/Rx.
  @param[in] Length        Transmit data length or received data length.
  @param[in] CallbackCtxt  User-specified parameter.
*/
static void Uart_Rx_CB(uint32_t Status, uint32_t Length, void *CbCtxt)
{
   qapi_TSK_Signal_Task(PAL_Context.QCLI_Task, 1);
}
#endif

/**
   @brief Callback function called before the subsystem enters the shutdown
          state.

   This function is called with interrupts disabled and the interrupts must not
   be re-enabled.

   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t PAL_Shutdown_CB(void *UserParam)
{
   qbool_t Shutdown;

   Shutdown = !(PAL_Context.AbortShutdown);
   PAL_Context.AbortShutdown = false;

   if(Shutdown)
   {
      /* Note PAL_Wakeup_CB will not be called if its paired fucntion
         (PAL_Shutdown_CB()) causes the abort. */
      PAL_RetainedContext.ShutdownCount++;

#ifndef PAL_USE_RTT_CONSOLE
      /* Turn off the UART. */
   PAL_Uart_Deinit();
#endif
   }
   else
   {
      /* Vote for APSS to stay active. */
      qapi_PWR_Vote_Local_State(PAL_RetainedContext.PwrBallot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
   }

   return(Shutdown);
}

/**
   @brief Callback function called when shutdown wakes from shutdown or a
          shutdown is aborted.

   This function is called with interrupts disabled and the interrupts must not
   be re-enabled.

   @param[in] ShutdownAborted  Flag indicating if this function is called
                               because a shutdown was aborted (true) or because
                               the subsystem woke up from shutdown (false).
   @param[in] UserParam        User specified parameter provided when the
                               callback is registered.
*/
static void PAL_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam)
{
   if(ShutdownAborted)
   {
      PAL_RetainedContext.ShutdownCount--;

#ifndef PAL_USE_RTT_CONSOLE
      /* Reinitialize the UART if the shutdown was aborted. */
      PAL_Uart_Init(PAL_CONSOLE_INSTANCE);
#endif
   }
   else
   {
      PAL_RetainedContext.WakeCount++;
   }
}

/**
   @brief Initialize the power related items.

   @param[in] IsColdBoot  Indicates if this is a warm or cold boot.
*/
static void PAL_Init_Power(qbool_t IsColdBoot)
{
   if(IsColdBoot)
   {
      /* Aquire a power ballot and register the shutdown callbacks. Note these
      are retained across warm boot. */
      PAL_RetainedContext.PwrBallot    = qapi_PWR_Acquire_Ballot();
      PAL_RetainedContext.UartBallot   = qapi_PWR_Acquire_Ballot();
      PAL_RetainedContext.PwrCallbacks = qapi_PWR_Register_Shutdown_Callbacks(PAL_Shutdown_CB, PAL_Wakeup_CB, QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT, NULL);

      /* Take out votes to make sure peripherals and GPIO are active. */
      qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_PERIPHERAL_E, QAPI_PWR_STATE_ACTIVE_E);
      qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_GPIO_E, QAPI_PWR_STATE_ACTIVE_E);

      /* Select the accurate HFCLK. */
      qapi_PWR_Set_HFCLK_Source(true);
   }
   else
   {
      /* Wait for the switch to the HFXTAL. */
      while(!qapi_PWR_Get_HFCLK_Source()) {}
   }

   /* Take out a vote to keep APSS active. */
   qapi_PWR_Vote_Local_State(PAL_RetainedContext.PwrBallot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
}

/**
   @brief Task for QCLI processing.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of all events that triggered since the last call
                          to this function.
   @param[in] UserParam   User-specified parameter for the task function.

   @return The time in milliseconds before this function needs to be called
           again.  If QAPI_TSK_NO_WAIT is returned, the task will be set to
           pending immediately. If QAPI_TSK_INFINITE_WAIT is returned, the
           task will only become pending when the task is signaled or is set to
           be  deleted.
*/
static uint32_t QCLI_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
#ifdef PAL_USE_RTT_CONSOLE
   uint8_t RTT_Read_Bytes;
#else
   uint32_t Length;
   uint32_t Remain_Len = 0;
#endif

   if(EventMask & QAPI_TSK_EVENT_INIT)
   {
      /* Initialize Task. */
   }

#ifdef PAL_USE_RTT_CONSOLE
   if (EventMask & QAPI_TSK_EVENT_TIMEOUT)
   {
      do
      {
         RTT_Read_Bytes = SEGGER_RTT_Read(0, PAL_Context.InputBuffer, INPUT_BUFFER_SIZE);
         if (RTT_Read_Bytes != 0)
         {
            QCLI_Process_Input_Data(RTT_Read_Bytes, PAL_Context.InputBuffer);
         }
      } while (RTT_Read_Bytes != 0);
   }

#else

   if(EventMask & 1)
   {
      do
      {
         Length = INPUT_BUFFER_SIZE;
         if(QAPI_OK == qapi_UART_Receive(PAL_Context.ConsoleUART, PAL_Context.InputBuffer, &Length, &Remain_Len))
         {
            PAL_Context.InputByteCount = Length;
            QCLI_Process_Input_Data(PAL_Context.InputByteCount, PAL_Context.InputBuffer);
         }
      } while(Remain_Len);
   }
#endif

   if(EventMask & QAPI_TSK_EVENT_DELETE)
   {
      /* Cleanup Task. */
   }
   return(QCLI_TSK_WAIT_TIME);
}

/**
   @brief Executes the "Exit" command to quit the application.

   Parameter_List[0]  Time to sleep in milliseconds.

   @param[in] Parameter_Count  Number of elements in Parameter_List.
   @param[in] Parameter_List   List of parsed arguments associate with this
                               command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command was executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command failed to execute.
    - QCLI_STATUS_USAGE_E indicates a parameter was invalid.
*/
static QCLI_Command_Status_t PAL_Cmd_Shutdown(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;

   if((Parameter_Count >= 1) && (Parameter_List[0].Integer_Is_Valid))
   {
      /* Change the vote for APSS to be shutdown. */
      Result = PAL_Vote_Local_Power_State(true, (uint32_t)(Parameter_List[0].Integer_Value));
      if(Result == QAPI_OK)
      {
         QCLI_Printf(PAL_Context.QCLI_Handle, "Entering Shutdown...\n");

         if((Parameter_Count >= 2) && (Parameter_List[1].Integer_Is_Valid) && (Parameter_List[1].Integer_Value != 0))
         {
            QCLI_Printf(PAL_Context.QCLI_Handle, "...will abort.\n");
            PAL_Context.AbortShutdown = true;
         }
         else
         {
            PAL_Context.AbortShutdown = false;
         }
      }
      else
      {
         QCLI_Display_Function_Status(PAL_Context.QCLI_Handle, "qapi_PWR_Vote_Local_State", Result);
      }

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Initialize the UART used by the demo.

   @return true if the UART was initailized successfully or false if there was
           an error.
*/
qbool_t PAL_Uart_Init(uint32_t Instance)
{
#ifndef PAL_USE_RTT_CONSOLE
   qapi_UART_Config_t  Uart_Config;
   uint8_t             Ret_Val;

   Uart_Config.Dma            = false;
   Uart_Config.BaudRate       = 115200;
   Uart_Config.ParityMode     = QAPI_UART_NO_PARITY_E;
   Uart_Config.NumStopBits    = QAPI_UART_1_0_STOP_BITS_E;
   Uart_Config.BitsPerChar    = QAPI_UART_8_BITS_PER_CHAR_E;
   Uart_Config.EnableLoopback = false;
   Uart_Config.EnableFlowCtrl = false;
   Uart_Config.RxBufSize      = Uart_Config.TxBufSize = 256;
   Uart_Config.RxStaleCnt     = 10;
   Uart_Config.TxInvert       = false;
   Uart_Config.TxCbFunc       = Uart_Tx_CB;
   Uart_Config.RxCbFunc       = Uart_Rx_CB;
   PAL_Context.ConsoleUART    = (qapi_UART_Instance_t)Instance;

   if(qapi_UART_Open(PAL_Context.ConsoleUART, &Uart_Config) == QAPI_OK)
   {
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
#else
   return(false);
#endif
}

int32_t PAL_Uart_Instance_Get(void)
{
#ifndef PAL_USE_RTT_CONSOLE
   return PAL_CONSOLE_INSTANCE;
#else
   return(-1);
#endif
}

/**
   @brief Turns off the UART used by the demo.

   @return true if the UART was deinitailized successfully or false if there was
           an error.
*/
qbool_t PAL_Uart_Deinit(void)
{
#ifndef PAL_USE_RTT_CONSOLE
   return(qapi_UART_Close(PAL_Context.ConsoleUART));
#else
   return(false);
#endif
}

/**
   @brief Writes a buffer to the console.

   All data from this buffer will be written to the console or buffered locally
   before this function returns.

   @param Length[in]  Length of the data to be written.
   @param Buffer[in]  Buffer to be written to the console.
*/
void PAL_Console_Write(uint32_t Length, const char *Buffer)
{
#ifndef PAL_USE_RTT_CONSOLE
   uint32_t Sent = 0;
#endif

   if((Length != 0) && (Buffer != NULL))
   {
#ifdef PAL_USE_RTT_CONSOLE
      SEGGER_RTT_Write(0, Buffer, Length);
#else
      /* Take out a vote to keep the system active. */
      qapi_PWR_Vote_Local_State(PAL_RetainedContext.UartBallot, QAPI_PWR_STATE_ACTIVE_E, 0);

      do
      {
         /* Transmit the data. */
         if(qapi_UART_Transmit(PAL_Context.ConsoleUART, (char *)Buffer, Length, &Sent) == QAPI_OK)
         {
            Length -= Sent;
            Buffer += Sent;
         }
      } while (Length);
#endif
   }
}

/**
   @brief Allocates a block of memory from the heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return A pointer to the allocated memory or NULL if there was an error.
*/
void *PAL_Malloc(size_t Length)
{
   return qapi_Malloc(Length);
}

/**
   @brief Frees a block of memory from the heap.

   @param[in] Pointer  Block to free as returned by a call to PAL_Malloc().
*/
void PAL_Free(void *Pointer)
{
   qapi_Free(Pointer);
}

/**
   @brief Takes a PAL_RELEASE_LOCK() for re-entrancy protection for the QCLI module.

   This module expects the PAL_RELEASE_LOCK() to behave like a mutex. It should support
   recursively taking the PAL_RELEASE_LOCK() and, for threaded platforms, block until the PAL_RELEASE_LOCK()
   can be taken as applicable.

   @return
    - true if the PAL_RELEASE_LOCK() was taken successfully
    - false if the PAL_RELEASE_LOCK() was not taken successfully
*/
qbool_t PAL_Take_Lock(void)
{
   /* Not required for non-threaded. */
   return(true);
}

/**
   @brief Releases a PAL_RELEASE_LOCK() taken with PAL_Take_Lock().

   @param[in] Taken  Flag indicating the lock was taken in the corresponding
                     call to PAL_Take_Lock();
    - true if the PAL_RELEASE_LOCK() was taken successfully
    - false if the PAL_RELEASE_LOCK() was not taken successfully
*/
void PAL_Release_Lock(void)
{
   /* Not required for non-threaded. */
}

/**
   @brief Votes for local power state using PAL ballot.

   This state is entered the next time a WFI is executed. If the vote is
   shutdown (EnableShutdown is true), the WakeTime indicate when the
   caller needs the subsystem to wake.

   @param[in] EnableShutdown  TRUE if shutdown should be enabled, FALSE if shutdown
                              should be disabled.
   @param[in] WakeTime  Time that the voter requires the system to wake in
                        milliseconds relative to the current time. Use
                        #QAPI_PWR_NO_WAKE if this time is not to be used to set
                        a wakeup. If SleepTime is greater than
                        #QAPI_PWR_MAX_WAKE_TIME, #QAPI_PWR_MAX_WAKE_TIME is
                        used instead.

   @return QAPI_OK if the vote was cast successfully, or a negative value if
           there was an error.
*/
qapi_Status_t PAL_Vote_Local_Power_State(qbool_t EnableShutdown, uint32_t WakeTime)
{
   qapi_Status_t Result;

   /* Change the vote for APSS to be shutdown.                          */
   if(EnableShutdown)
   {
      /* Vote to enable shutdown.                                       */
      Result = qapi_PWR_Vote_Local_State(PAL_RetainedContext.PwrBallot, QAPI_PWR_STATE_SHUTDOWN_E, WakeTime);
   }
   else
   {
      /* Vote to disable shutdown.                                      */
      Result = qapi_PWR_Vote_Local_State(PAL_RetainedContext.PwrBallot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
   }

   return(Result);
}

/**
   Main program entry point.
*/
int main(void)
{
   uint32_t WaitTime;
   qbool_t  IsColdBoot;
   qbool_t  Running;

   /* Initialize the power, GPIO, and task modules. */
   qapi_TSK_Init(NULL, NULL);
   qapi_PWR_Initialize(&IsColdBoot);
   PAL_Init_Power(IsColdBoot);
   qapi_TMR_Init();
   qapi_GPIO_Initialize(Alternative_GPIO_Config);

   memset(&PAL_Context, 0, sizeof(PAL_Context));

   /* Create a task and signal for QCLI to use. */
   PAL_Context.QCLI_Task = qapi_TSK_Create_Task(QCLI_Task, NULL);

   /* Initialize the console. */
#ifdef PAL_USE_RTT_CONSOLE
   SEGGER_RTT_Init();
#else
   PAL_Uart_Init(PAL_CONSOLE_INSTANCE);
#endif

   /* Initialize the QCLI framework and all the samples. */
   PAL_Context.QCLI_Handle = QCLI_Initialize(&PAL_Cmd_Group);
   Initialize_Samples();
   QCLI_Display_Command_List();

   Running  = true;
   while(Running)
   {
      /* Run the scheduler. */
      WaitTime = qapi_TSK_Process_Scheduler();

      if(WaitTime != 0)
      {
         /* If the scheduler doesn't need to run immidiately, try to enter
            sleep. */
         qapi_PWR_System_Idle(WaitTime);
      }
   }

   return(0);
}

