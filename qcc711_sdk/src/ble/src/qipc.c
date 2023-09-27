/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdbool.h>
#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_task.h"
#include "qapi_power.h"
#include "ram.h"
#include "qipc.h"
#include "stringl.h"
#include "HALhwio.h"
#include "hwio_aon.h"
#include "qcc710.h"
#include "core_cm3.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QIPC_WAKEUP_CALLBACK_PRIORITY           (QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT - 0x10)

extern uint32_t __IPC_SharedStart;
extern uint32_t __IPC_SharedEnd;
extern uint32_t __IPC_APSS_InfoStart;

#define QIPC_TX_SHARED_START                    ((uint8_t *)&__IPC_SharedStart)
#define QIPC_TX_SHARED_END                      ((uint8_t *)&__IPC_SharedEnd - 1)
#define QIPC_TX_BUFFER_START                    (QIPC_TX_SHARED_START)
#define QIPC_TX_BUFFER_END                      ((uint8_t *)&__IPC_APSS_InfoStart - 1)
#define QIPC_TX_BUFFER_SIZE                     ((uint16_t)(QIPC_TX_BUFFER_END - QIPC_TX_BUFFER_START))

#define QIPC_TASK_EVENT_INT_SIGNALLED           0x01

/**
   @brief Macro to verify the information for the transmit buffer.

   @param[in] __data__  Pointer to a QIPC_BufferData_t structure containing the
                        transmit buffer information.

   @return True if the data is valid or false if it is invalid.
*/
#define QIPC_VERIFY_TX_BUFFER_DATA(__data__)    (((__data__)->Buffer == QIPC_TX_BUFFER_START) && ((__data__)->BufferSize == QIPC_TX_BUFFER_SIZE) && ((__data__)->InIndex < (__data__)->BufferSize) && ((__data__)->OutIndex < (__data__)->BufferSize))

/**
   @brief Macro to verify the information for the receive buffer.

   @param[in] __data__  Pointer to a QIPC_BufferData_t structure containing the
                        receive buffer information.

   @return True if the data is valid or false if it is invalid.
*/
#define QIPC_VERIFY_RX_BUFFER_DATA(__data__)    (((__data__)->Buffer != NULL) && ((__data__)->InIndex < (__data__)->BufferSize) && ((__data__)->OutIndex < (__data__)->BufferSize))

/**
   @brief Macro to calculate the space available in a buffer.

   @param[in] __data__  Pointer to a QIPC_BufferData_t structure containing the
                        buffer information.

   @return The amount of free space available in the buffer.
*/
#define QIPC_BUFFER_SPACE_AVAILABLE(__data__)   ((((__data__)->OutIndex <= (__data__)->InIndex) ? (__data__)->BufferSize : 0) + (__data__)->OutIndex - (__data__)->InIndex - 1)

/**
   @brief Macro to copy the conents of a buffer's information.

   This is mainly to copy the shared buffer information to a local copy.

   @param[out] __dest__  Pointer to a QIPC_BufferData_t structure to copy the
                         data to.
   @param[in]  __src__   Pointer to a QIPC_Buffer_Data_t structure to copy the
                         data from.
*/
#define QIPC_COPY_BUFFER_DATA(__dest__, __src__)      \
   do                                                 \
   {                                                  \
      (__dest__)->Buffer     = (__src__)->Buffer;     \
      (__dest__)->BufferSize = (__src__)->BufferSize; \
      (__dest__)->InIndex    = (__src__)->InIndex;    \
      (__dest__)->OutIndex   = (__src__)->OutIndex;   \
                                                      \
   }                                                  \
   while(0)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of QIPC states.
*/
typedef enum
{
   QIPC_STATE_CLOSED_E,  /**< Closed. */
   QIPC_STATE_OPEN_E     /**< Open and ready to send or receive data. */
} QIPC_State_t;

/**
   Retained QIPC context information.
*/
typedef struct QIPC_RetnContext_s
{
   QIPC_State_t       State;            /**< Current State of the QIPC interface. */
   QIPC_Callback_t    Callback;         /**< Registered event callback function. */
   void              *CallbackParam;    /**< User specified callback parameter. */
   qapi_PWR_Ballot_t  Ballot;           /**< Ballot for power voting. */
   void              *ShutdownCBHandle; /**< Handle for the registered shutdown callbacks. */
   void              *SharedRAMHandle;  /**< Handle for the shared RAM block. */
   uint32_t           SharedBlocks;     /**< RAM blocks that need to be shared. */
   volatile bool      RxAvailable;      /**< Denotes an interrupt has been received and Rx Data is available. */
} QIPC_RetnContext_t;

/**
   Retained QIPC context information.
*/
typedef struct QPIC_Context_s
{
   qapi_TSK_Handle_t TaskHandle;
   uint16_t          LastOutIndex;
} QPIC_Context_t;

/**
   Information for a shared buffer.
*/
typedef struct QIPC_BufferData_s
{
   uint8_t  *Buffer;     /**< Pointer to the location of the buffer. */
   uint16_t  BufferSize; /**< Size of the buffer. */
   uint16_t  InIndex;    /**< Next location that will be written in the buffer. */
   uint16_t  OutIndex;   /**< Next location that will be read from the buffer. */
} QIPC_BufferData_t;


/*-------------------------------------------------------------------------
 * Static Variables
 *-----------------------------------------------------------------------*/

static QPIC_Context_t             QIPC_Context;     /**< QIPC context information that isn't retained. */
static QIPC_RetnContext_t         QIPC_RetnContext __attribute__((section (".bss.retain"))); /**< Retained QIPC context information. */

extern volatile QIPC_BufferData_t QIPC_TxData;      /**< Information shared by the local subsystem.  It is expected for this symbol
                                                         to be provided by the linker. */
extern volatile QIPC_BufferData_t QIPC_RxData;      /**< Information shared by the remote subsystem.  It is expected for this symbol
                                                         to be provided by the linker. */

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static qbool_t QIPC_Shutdown_CB_t(void *UserParam);
static void QIPC_Wakeup_CB_t(qbool_t ShutdownAborted, void *UserParam);
static void QIPC_GenerateTxEvent(uint16_t BytesFree);
static void QIPC_GenerateRxEvent(void);
static qapi_Status_t QIPC_SignalRemoteIPC(bool VoteLocal);
static uint32_t QIPC_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);
void IPC_IntHandler(void);


/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Callback indicating the subsystem is entering shutdown.

   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.

   @return True if shutdown can be entered or false if shutdown needs to be
           aborted.
*/
static qbool_t QIPC_Shutdown_CB_t(void *UserParam)
{
   /* Nothing to do. */
   return(true);
}

/**
   @brief Callback indicating the subsystem is waking from shutdown or a
          shutdown was aborted.

   This function is called with interrupts disabled and must not re-enable
   interrupts.

   @param[in] Aborted    Flag indicating if this function is called because a
                         shutdown was aborted (true) or because the subsystem
                         woke from shutdown (false).
   @param[in] UserParam  User specified parameter provided when the callback is
                         registered.

   @return True if shutdown can be entered or false if shutdown can be aborted.
*/
static void QIPC_Wakeup_CB_t(qbool_t ShutdownAborted, void *UserParam)
{
   if((!ShutdownAborted) && (QIPC_RetnContext.State == QIPC_STATE_OPEN_E))
   {
      /* Create the task. */
      QIPC_Context.TaskHandle = qapi_TSK_Create_Task(QIPC_Task, NULL);
      if(QIPC_Context.TaskHandle != NULL)
      {
         /* Re-initialize the tx buffer. */
         memset((void *)&QIPC_TxData, 0, sizeof(QIPC_BufferData_t));
         QIPC_TxData.Buffer        = QIPC_TX_BUFFER_START;
         QIPC_TxData.BufferSize    = QIPC_TX_BUFFER_SIZE;
         QIPC_Context.LastOutIndex = 0;

         /* Re-share the tx buffer. */
         RAM_Share(RAM_SUBSYSTEM_BTSS_E, QIPC_RetnContext.SharedBlocks, RAM_PERM_READ_WRITE_E);

         /* Enable interrupts. */
         NVIC_EnableIRQ(BTSS_IPC_IRQn);
      }
      else
      {
         /* ERROR: Failed to recreate the task. */
         QIPC_RetnContext.State = QIPC_STATE_CLOSED_E;
      }
   }
}

/**
   @brief Generates a transmit event callback.

   @param[in] BytesFree  Bytes available in the transmit buffer.
*/
static void QIPC_GenerateTxEvent(uint16_t BytesFree)
{
   QIPC_Event_t Event;

   Event.Type = QIPC_EVENT_TYPE_SENT_E;
   Event.Data.Sent.BytesFree = BytesFree;

   if(QIPC_RetnContext.Callback != NULL)
       (*(QIPC_RetnContext.Callback))(&Event, QIPC_RetnContext.CallbackParam);
}

/**
   @brief Generates a receive event callback.

   @param[in] Buffer  Bytes available in the transmit buffer.
   @param[in] Length  Bytes available in the transmit buffer.
*/
static void QIPC_GenerateRxEvent(void)
{
   QIPC_Event_t Event;

   Event.Type = QIPC_EVENT_TYPE_RECEIVED_E;

   if(QIPC_RetnContext.Callback != NULL)
       (*(QIPC_RetnContext.Callback))(&Event, QIPC_RetnContext.CallbackParam);
}

static qapi_Status_t QIPC_SignalRemoteIPC(bool VoteLocal)
{
   qapi_Status_t RetVal = QAPI_OK;
   uint32_t      Tick;

   /* Cast the votes and make sure the IPC is awake. */
   if(VoteLocal)
       qapi_PWR_Vote_Local_State(QIPC_RetnContext.Ballot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
   qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_BTSS_E, QAPI_PWR_STATE_ACTIVE_E);

   /* Wait for the BTSS to become active and operative. This ensures that BTSS is able to process
    * the interrupt (notably, it will not clear it on boot before it is processes).
    */
   Tick = qapi_TSK_Get_Tick_Count();
   while(((HWIO_AON_PME_APPS_STATUS_INM(HWIO_AON_PME_APPS_STATUS_BT_OPERATIVE_BMSK | HWIO_AON_PME_APPS_STATUS_UPDATE_PENDING_BMSK) != HWIO_AON_PME_APPS_STATUS_BT_OPERATIVE_BMSK) ||
         ((HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_BT_BMSK) >> HWIO_AON_PME_SOC_STATUS_BT_SHFT) < 3)) &&
         ((qapi_TSK_Get_Tick_Count() - Tick) < 1500))
   {
   }

   /* If BTSS is up. */
   if((HWIO_AON_PME_APPS_STATUS_INM(HWIO_AON_PME_APPS_STATUS_BT_OPERATIVE_BMSK)) && ((HWIO_AON_PME_SOC_STATUS_INM(HWIO_AON_PME_SOC_STATUS_BT_BMSK) >> HWIO_AON_PME_SOC_STATUS_BT_SHFT) == 3))
   {
      /* Signal the IPC interrupt. */
      HWIO_AON_TCSR_IPC_APPS_TO_BT_OUT(1);
      HWIO_AON_TCSR_IPC_APPS_TO_BT_OUT(0);
   }
   else
   {
      qapi_PWR_Vote_Local_State(QIPC_RetnContext.Ballot, QAPI_PWR_STATE_SHUTDOWN_E, QAPI_PWR_NO_WAKE);
      RetVal = QAPI_ERR_TIMEOUT;
   }

   qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_BTSS_E, QAPI_PWR_STATE_SHUTDOWN_E);

   return(RetVal);
}

/**
   @brief Task for QIPC.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of all events that triggered since the last call
                          to this function.  This may include bits set by a call
                          to qapi_TSK_Signal_Task() or events generated by this
                          module (see the QAPI_TSK_EVENT_* definitions).
   @param[in] UserParam   User-specified parameter for the task function.

   @return The time in milliseconds before this function needs to be called
           again.  If QAPI_TSK_NO_WAIT is returned, the task will be set to
           pending immediately. If QAPI_TSK_INFINITE_WAIT is returned, the
           task will only become pending when the task is signaled or is set to
           be  deleted.
*/
static uint32_t QIPC_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
   QIPC_BufferData_t LocalData;

   /* Cleanup and skip processing any signals if delete bit is set. */
   if(EventMask & QAPI_TSK_EVENT_DELETE)
   {
       qapi_PWR_Unregister_Callback(QIPC_RetnContext.ShutdownCBHandle);
       qapi_PWR_Release_Ballot(QIPC_RetnContext.Ballot);
       memset(&QIPC_RetnContext, 0, sizeof(QIPC_RetnContext_t));
   }
   /* Only process data if the interrupt was signalled. */
   else if(EventMask & QIPC_TASK_EVENT_INT_SIGNALLED)
   {
      /* Check for consumed transmit data. */
      QIPC_COPY_BUFFER_DATA(&LocalData, &QIPC_TxData);
      if(QIPC_VERIFY_TX_BUFFER_DATA(&LocalData) && (LocalData.OutIndex != QIPC_Context.LastOutIndex))
      {
        QIPC_Context.LastOutIndex = LocalData.OutIndex;

         /* Some transmit data has been consumed so notify the application. */
         QIPC_GenerateTxEvent(QIPC_BUFFER_SPACE_AVAILABLE(&LocalData));

         qapi_TSK_Enter_Critical();

         /* Check if all data has been sent. */
         if(LocalData.OutIndex == LocalData.InIndex)
         {
            qapi_PWR_Vote_Local_State(QIPC_RetnContext.Ballot, QAPI_PWR_STATE_SHUTDOWN_E, QAPI_PWR_NO_WAKE);
         }

         qapi_TSK_Exit_Critical();
      }

      /* Check for data to receive. */
      QIPC_COPY_BUFFER_DATA(&LocalData, &QIPC_RxData);
      if(QIPC_VERIFY_RX_BUFFER_DATA(&LocalData) && (LocalData.InIndex != LocalData.OutIndex))
      {
         /* Signal the callback that more data has been received. */
         QIPC_GenerateRxEvent();
      }
   }

   return(QAPI_TSK_INFINITE_WAIT);
}

/**
   @brief Handler for the IPC interrupt from the remote subsystem.
*/
void BTSS_IPC_IntHandler(void)
{
   QIPC_BufferData_t LocalData;

   QIPC_COPY_BUFFER_DATA(&LocalData, &QIPC_RxData);
   if(QIPC_VERIFY_RX_BUFFER_DATA(&LocalData) && (LocalData.InIndex != LocalData.OutIndex))
   {
      QIPC_RetnContext.RxAvailable = true;
   }
   /* Check if Rx Data is available. We need to flag this in the interrupt
    * context so that a polling thread is able to determine that an interrupt
    * occurred and the Rx context is valid for reading. */

   /* Signal the IPC task. */
   qapi_TSK_Signal_Task(QIPC_Context.TaskHandle, QIPC_TASK_EVENT_INT_SIGNALLED);
}

/**
   @brief Opens the IPC interface.

   @param[in] Callback   Function called to signal a QIPC event.
   @param[in] UserParam  User specified callback parameter.

   @return QAPI_OK if the module was initialized successfully or a negative
           value if there was an error.
*/
qapi_Status_t QIPC_Open(QIPC_Callback_t Callback, void *UserParam)
{
   qapi_Status_t RetVal;

   if(QIPC_RetnContext.State == QIPC_STATE_CLOSED_E)
   {
      /* Create a task and register the power ballot and callbacks. */
      QIPC_Context.TaskHandle           = qapi_TSK_Create_Task(QIPC_Task, NULL);
      QIPC_RetnContext.Ballot           = qapi_PWR_Acquire_Ballot();
      QIPC_RetnContext.ShutdownCBHandle = qapi_PWR_Register_Shutdown_Callbacks(QIPC_Shutdown_CB_t, QIPC_Wakeup_CB_t, QIPC_WAKEUP_CALLBACK_PRIORITY, NULL);
      QIPC_RetnContext.SharedBlocks     = RAM_AddressRangeToBlocks(QIPC_TX_BUFFER_START, QIPC_TX_SHARED_END);
      QIPC_RetnContext.Callback         = Callback;
      QIPC_RetnContext.CallbackParam    = UserParam;
      if((QIPC_Context.TaskHandle != NULL) && (QIPC_RetnContext.Ballot != 0) && (QIPC_RetnContext.ShutdownCBHandle != NULL) && (QIPC_RetnContext.SharedBlocks != 0))
      {
         memset((void *)&QIPC_TxData, 0, sizeof(QIPC_BufferData_t));
         QIPC_TxData.Buffer     = QIPC_TX_BUFFER_START;
         QIPC_TxData.BufferSize = QIPC_TX_BUFFER_SIZE;

         /* Share the RAM for the TX buffer. */
         RetVal = RAM_Share(RAM_SUBSYSTEM_BTSS_E, QIPC_RetnContext.SharedBlocks, RAM_PERM_READ_WRITE_E);

         if(RetVal == QAPI_OK)
         {
            NVIC_EnableIRQ(BTSS_IPC_IRQn);
            QIPC_RetnContext.State = QIPC_STATE_OPEN_E;
         }
      }
      else
      {
         if(QIPC_RetnContext.ShutdownCBHandle != NULL)
         {
            qapi_PWR_Unregister_Callback(QIPC_RetnContext.ShutdownCBHandle);
            QIPC_RetnContext.ShutdownCBHandle = NULL;
         }

         if(QIPC_RetnContext.Ballot != 0)
         {
            qapi_PWR_Release_Ballot(QIPC_RetnContext.Ballot);
            QIPC_RetnContext.Ballot = 0;
         }

         if(QIPC_Context.TaskHandle != NULL)
         {
            qapi_TSK_Delete_Task(QIPC_Context.TaskHandle);
            QIPC_Context.TaskHandle = NULL;
         }

         RetVal = QAPI_ERR_NO_RESOURCE;
      }
   }
   else
   {
      RetVal = QAPI_ERR_EXISTS;
   }

   return(RetVal);
}

/**
   @brief Closes the IPC interface.
*/
void QIPC_Close(void)
{
   NVIC_DisableIRQ(BTSS_IPC_IRQn);
   qapi_TSK_Delete_Task(QIPC_Context.TaskHandle);
}

/**
   @brief Sends data over the IPC interface.

   @param[in] Buffer  Pointer to the data to be sent.
   @param[in] Length  Amount of data to be sent.

   @return The amount of data that was sent if successfulor a negative
           value if there was an error.
*/
int32_t QIPC_Send(const uint8_t *Buffer, uint16_t Length)
{
   int32_t           RetVal;
   uint16_t          CopyLength;
   QIPC_BufferData_t LocalData;
   uint16_t          BackupInIndex;

   if((QIPC_RetnContext.State == QIPC_STATE_OPEN_E) && (Buffer != NULL) && (Length != 0))
   {
      QIPC_COPY_BUFFER_DATA(&LocalData, &QIPC_TxData);
      BackupInIndex = LocalData.InIndex;

      /* Verify the shared information to make sure it hasn't been modified. */
      if(QIPC_VERIFY_TX_BUFFER_DATA(&LocalData))
      {
         /* Determine the maximum amount that can be copied. */
         RetVal = QIPC_BUFFER_SPACE_AVAILABLE(&LocalData);
         if(RetVal > (int32_t)Length)
         {
            RetVal = (int32_t)Length;
         }
         else
         {
            Length = (uint16_t)RetVal;
         }

         CopyLength = LocalData.BufferSize - LocalData.InIndex;
         if(Length <= CopyLength)
         {
            /* Single Copy. */
            memscpy(&(LocalData.Buffer[LocalData.InIndex]), CopyLength, Buffer, Length);
            LocalData.InIndex += Length;
            if(LocalData.InIndex == LocalData.BufferSize)
            {
               LocalData.InIndex = 0;
            }
         }
         else
         {
            /* Copy in two parts. */
            memscpy(&(LocalData.Buffer[LocalData.InIndex]), CopyLength, Buffer, Length);
            Length -= CopyLength;
            Buffer += CopyLength;
            memscpy(&(LocalData.Buffer[0]), LocalData.BufferSize, Buffer, Length);
            LocalData.InIndex = Length;
         }

         qapi_TSK_Enter_Critical();

         /* Update the InIndex. */
         QIPC_TxData.InIndex = LocalData.InIndex;

         /* Don't take return value since it may overrite the amount
            of data written.*/
         if(QIPC_SignalRemoteIPC(true) != QAPI_OK)
         {
            /* Error while signalling BTSS. */
            QIPC_TxData.InIndex = BackupInIndex;
            RetVal              = QAPI_ERROR;
         }

         qapi_TSK_Exit_Critical();
      }
      else
      {
         RetVal = 0;
      }
   }
   else
   {
      RetVal = 0;
   }

   return RetVal;
}

qapi_Status_t QIPC_Receive(uint8_t *Buffer, uint16_t *Length)
{
   qapi_Status_t RetVal = QAPI_OK;
   uint16_t Available;
   QIPC_BufferData_t LocalData;

   if((Length != NULL) && (Buffer != NULL))
   {
      if(QIPC_RetnContext.RxAvailable)
      {
         QIPC_COPY_BUFFER_DATA(&LocalData, &QIPC_RxData);

         if(QIPC_VERIFY_RX_BUFFER_DATA(&LocalData))
         {
            /* Determine the amount of data available. If the data wraps around the end of the buffer,
             * the caller will need to make another call to complete it. */
            if(LocalData.OutIndex <= LocalData.InIndex)
            {
               Available = LocalData.InIndex - LocalData.OutIndex;
            }
            else
            {
               Available = LocalData.BufferSize - LocalData.OutIndex;
            }

            *Length = (*Length < Available)?*Length:Available;

            if(*Length > 0)
            {
               /* Copy the data into the receive buffer. */
               memscpy(Buffer, *Length, &LocalData.Buffer[LocalData.OutIndex], *Length);

               /* Update the index in the shared structure. */
               LocalData.OutIndex += *Length;

               if(LocalData.OutIndex == LocalData.BufferSize)
                  LocalData.OutIndex = 0;

               qapi_TSK_Enter_Critical();

               /* Re-check the current InIndex. */
               LocalData.InIndex = QIPC_RxData.InIndex;

               /* Flag if we have consumed all the data. */
               if(LocalData.OutIndex == LocalData.InIndex)
               {
                   QIPC_RetnContext.RxAvailable = false;
               }

               qapi_TSK_Exit_Critical();

               QIPC_RxData.OutIndex = LocalData.OutIndex;
               RetVal               = QIPC_SignalRemoteIPC(false);
            }
         }
         else
            *Length = 0;
      }
      else
         *Length = 0;
   }
   else
      RetVal = QAPI_ERR_INVALID_PARAM;


   return RetVal;
}
