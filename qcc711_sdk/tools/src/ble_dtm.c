/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_task.h"
#include "qapi_uart.h"
#include "qapi_gpio.h"
#include "qapi_power.h"
#include "qapi_timer.h"
#include "qapi_uart.h"
#include "qapi_ble_dtm.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define DTM_UART_INSTANCE        (QAPI_UART_INSTANCE_SE2_E)
#define DTM_UART_TX_BUFFER_SIZE  (1024)
#define DTM_UART_RX_BUFFER_SIZE  (1024)
#define DTM_INPUT_BUFFER_SIZE    (260)

#define DTM_Task_EVENT_RX_DATA   (0x01)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef struct DTM_Context_s
{
   qapi_TSK_Handle_t Task;
   qapi_PWR_Ballot_t Ballot;
   uint8_t           InputBuffer[DTM_INPUT_BUFFER_SIZE];
} DTM_Context_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

static DTM_Context_t DTM_Context;

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

static void Uart_Init(void);
static void Uart_Tx_CB(uint32_t Status, uint32_t Length, void *CallbackCtxt);
static void Uart_Rx_CB(uint32_t Status, uint32_t Length, void *CbCtxt);
static void DTM_Callback(uint32_t Length, uint8_t *Data, unsigned long CallbackParameter);
static uint32_t DTM_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize the UART.

   @return true if the UART was initailized successfully or false if there was
           an error.
*/
static void Uart_Init(void)
{
   qapi_UART_Config_t Uart_Config;

   Uart_Config.Dma            = false;
   Uart_Config.BaudRate       = 115200;
   Uart_Config.ParityMode     = QAPI_UART_NO_PARITY_E;
   Uart_Config.NumStopBits    = QAPI_UART_1_0_STOP_BITS_E;
   Uart_Config.BitsPerChar    = QAPI_UART_8_BITS_PER_CHAR_E;
   Uart_Config.EnableLoopback = false;
   Uart_Config.EnableFlowCtrl = true;
   Uart_Config.RxBufSize      = DTM_UART_RX_BUFFER_SIZE;
   Uart_Config.TxBufSize      = DTM_UART_TX_BUFFER_SIZE;
   Uart_Config.RxStaleCnt     = 10;
   Uart_Config.TxCbFunc       = Uart_Tx_CB;
   Uart_Config.RxCbFunc       = Uart_Rx_CB;

   qapi_UART_Open(QAPI_UART_INSTANCE_SE2_E, &Uart_Config);
}

/**
  @brief UART transmit operation callback type.

  @param[in] Status        Result of current Tx/Rx.
  @param[in] Length        Transmit data length or received data length.
  @param[in] CallbackCtxt  User-specified parameter.
*/
static void Uart_Tx_CB(uint32_t Status, uint32_t Length, void *CallbackCtxt)
{
   /* Nothing to do. */
}

/**
  @brief UART receive operation callback type.

  @param[in] Status        Result of current Tx/Rx.
  @param[in] Length        Transmit data length or received data length.
  @param[in] CallbackCtxt  User-specified parameter.
*/
static void Uart_Rx_CB(uint32_t Status, uint32_t Length, void *CbCtxt)
{
   qapi_TSK_Signal_Task(DTM_Context.Task, DTM_Task_EVENT_RX_DATA);
}

/**
  @brief DTM callback for data to send.

  @param[in] Length             Length of the data buffer.
  @param[in] Data               Event data to send.
  @param[in] CallbackParameter  User-defined parameter that was defined in the
                                callback registration.

  @return
  None.
*/
static void DTM_Callback(uint32_t Length, uint8_t *Data, unsigned long CallbackParameter)
{
   uint32_t Sent = 0;

   if((Length != 0) && (Data != NULL))
   {
      do
      {
         /* Transmit the data. */
         if(qapi_UART_Transmit(QAPI_UART_INSTANCE_SE2_E, (char *)Data, Length, &Sent) == QAPI_OK)
         {
            Length -= Sent;
            Data   += Sent;
         }
      } while(Length);
   }
}

/**
   @brief Task for processing received data.

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
static uint32_t DTM_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
   uint32_t      Length;
   uint32_t      Remain_Length;
   qapi_Status_t Result;

   if(EventMask & DTM_Task_EVENT_RX_DATA)
   {
      do
      {
         Length = DTM_INPUT_BUFFER_SIZE;
         Result = qapi_UART_Receive(QAPI_UART_INSTANCE_SE2_E, (char *)(DTM_Context.InputBuffer), &Length, &Remain_Length);
         if(Result == QAPI_OK)
         {
            Result = qapi_BLE_DTM_Receive(Length, DTM_Context.InputBuffer);
         }
      } while((Result == QAPI_OK) && (Remain_Length != 0));
   }

   return(QAPI_TSK_INFINITE_WAIT);
}

/**
   Main program entry point.
*/
int main(void)
{
   uint32_t WaitTime;
   qbool_t  IsColdBoot;
   qbool_t  Running;

   /* Initialize the power and task modules. */
   qapi_TSK_Init(NULL, NULL);
   qapi_PWR_Initialize(&IsColdBoot);

   /* Take out votes to make sure peripherals and GPIO are active. */
   qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_PERIPHERAL_E, QAPI_PWR_STATE_ACTIVE_E);
   qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_GPIO_E, QAPI_PWR_STATE_ACTIVE_E);

   /* Take out a vote to keep the system active. */
   DTM_Context.Ballot = qapi_PWR_Acquire_Ballot();
   qapi_PWR_Vote_Local_State(DTM_Context.Ballot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);

   /* Select the accurate HFCLK. */
   qapi_PWR_Set_HFCLK_Source(true);

   /* Initialize the timer and GPIO modules. */
   qapi_TMR_Init();
   qapi_GPIO_Initialize(Alternative_GPIO_Config);

   memset(&DTM_Context, 0, sizeof(DTM_Context_t));

   /* Create a task and signal for QCLI to use. */
   DTM_Context.Task = qapi_TSK_Create_Task(DTM_Task, NULL);

   /* Initialize the DTM interface. */
   qapi_BLE_DTM_Initialize(DTM_Callback, 0);

   /* Initialize the UART. */
   Uart_Init();

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

