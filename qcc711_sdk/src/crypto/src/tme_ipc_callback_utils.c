/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
 #include "string.h"

 // QAPI headers
#include "qapi_rot.h"
#include "qapi_fuse.h"
#include "qapi_task.h"
#include "qapi_heap.h"
#include "qapi_status.h"
#include "qapi_crypto.h"
#include "qapi_firmware_update.h"

// TME utility headers
#include "tme_ipc_callback_utils.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
/*!
 * @struct TmeQapiCallbackContext
 * @brief Structure defining QAPI callback context.
 */
typedef struct tme_qapi_callback_context_s
{
    qapi_Status_t            status;
    TMW_Event_Data_Type_t    eventDataType;
    void                    *eventData;
    void                    *userData;
    void                    *callBack;
} TmeQapiCallbackContext;

static TmeQapiCallbackContext *QapiCallbackContext;
static qapi_TSK_Handle_t tme_task_handle;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief: Execute callback data received from user. It will invoke the correct event data for the 
           callback function.
*/
static void Execute_TME_Callback(void)
{
    if(QapiCallbackContext != NULL)
    {
      TMW_Event_Data_Type_t event_data_type = QapiCallbackContext->eventDataType;
      switch(event_data_type)
      {
        case CRYPTO_EVENT_DATA:
        {
          qapi_CRPT_Operation_CB_t cryptoCallback = (qapi_CRPT_Operation_CB_t)
              QapiCallbackContext->callBack;
          cryptoCallback(QapiCallbackContext->status, 
          (qapi_CRPT_Operation_Event_Data_t *) QapiCallbackContext->eventData, 
           QapiCallbackContext->userData);
          break;
        }
        case FIRMWARE_EVENT_DATA:
        {
          qapi_FWUP_Operation_CB_t fwCallback = (qapi_FWUP_Operation_CB_t) 
              QapiCallbackContext->callBack;
          fwCallback(QapiCallbackContext->status, 
          (qapi_FWUP_Operation_Event_Data_t *) QapiCallbackContext->eventData, 
           QapiCallbackContext->userData);
          break;
        }
        case ROT_EVENT_DATA:
        {
          qapi_ROT_Operation_CB_t rotCallback = (qapi_ROT_Operation_CB_t) 
              QapiCallbackContext->callBack;
          rotCallback(QapiCallbackContext->status, 
          (qapi_ROT_Operation_Event_Data_t *) QapiCallbackContext->eventData, 
           QapiCallbackContext->userData);
          break;
        }
        case FUSE_EVENT_DATA:
        {
          qapi_Fuse_Operation_CB_t fuseCallback = (qapi_Fuse_Operation_CB_t)
              QapiCallbackContext->callBack;
          fuseCallback(QapiCallbackContext->status,
          (qapi_Fuse_Operation_Event_Data_t *) QapiCallbackContext->eventData,
           QapiCallbackContext->userData);
          break;
        }
        default:
          break;
       }
      /* 
       * Once the callback is processed need to free the allocated heap memory of both
       * Event Data which contains TME response and the context in which callback is stored.
       */
      qapi_Free(QapiCallbackContext->eventData);
      qapi_Free(QapiCallbackContext);
      QapiCallbackContext = NULL;
    }
}

 /**
   @brief: The function to be invoked by the TME task
 */
static uint32_t QAPI_Callback_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    Execute_TME_Callback();
    return QAPI_TSK_INFINITE_WAIT;
}

/**
   @brief: Function to create a TME Task to be scheduled

   @return QAPI_OK if the callback was processed successfully or error if there was an error.
*/
static qapi_Status_t Create_TME_Task(void)
{
    qapi_Status_t ret_val = QAPI_ERROR;
    tme_task_handle = qapi_TSK_Create_Task(QAPI_Callback_Task, NULL);
    if(tme_task_handle != NULL)
    {
      ret_val = QAPI_OK;
    }
    return ret_val;
}

/**
   Delete the last created TME Task
*/
static void Delete_TME_Task(void)
{
    qapi_TSK_Delete_Task(tme_task_handle);
    tme_task_handle = NULL;
}

/**
   @brief: Initializes the callback module.

   The function creates the task which will parse the context and execute
   the stored callback

   @return the status result of the callback initialization.
*/
qapi_Status_t Initialize_TME_Callback(void)
{
    /* Create the task which will extract the callback from as and when triggered 
     * and execute it.
     */
    qapi_Status_t ret_val = Create_TME_Task();
    if(ret_val == QAPI_OK)
    {
      is_tme_callback_initialized = true;
    }
    else
    {
      is_tme_callback_initialized = false;
    }
    return ret_val;
}

/**
   @brief: Process a callback function with the provided information.

   Primarily it will add the callback to the context so that it can be executed by the task.

   @param Status        Status returned by QAPI
   @param EventDataType Type of Event data
   @param EventData     Event Data of QAPI.
   @param UserParam     Parameter provided by user
   @param CallBack      The call back function

   @return QAPI_OK if the callback was processed successfully or error if there was an error.
*/
qapi_Status_t Process_TME_Callback(qapi_Status_t Status, TMW_Event_Data_Type_t EventDataType,
                                           void *EventData, void *UserParam, void *CallBack)
{

    qapi_Status_t ret_val = QAPI_ERROR;
    /* Verify the parameters are valid and then proceed accordingly */
    if((is_tme_callback_initialized) && (EventData != NULL) && (CallBack != NULL))
    {
      //Initialise the context
      QapiCallbackContext = qapi_Malloc(sizeof(TmeQapiCallbackContext));
      if(QapiCallbackContext == NULL)
      {
        ret_val = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        // Set the callback in the context
        QapiCallbackContext->status = Status;
        QapiCallbackContext->eventDataType = EventDataType;
        QapiCallbackContext->eventData = EventData;
        QapiCallbackContext->userData = UserParam;
        QapiCallbackContext->callBack = CallBack;
        // Signal the task to be executed in next available slot
        ret_val = qapi_TSK_Signal_Task(tme_task_handle, 1);
      }
    }
    else
    {
      ret_val = QAPI_ERR_INVALID_PARAM;
    }

    // In case of failure free the allocated heap memory of both Event Data which contains 
    // TME response and the context in which callback is stored if they have been initialized
    if(ret_val != QAPI_OK)
    {
      if(EventData != NULL)
      {
        qapi_Free(EventData);
      }

      if(QapiCallbackContext != NULL)
      {
        qapi_Free(QapiCallbackContext);
        QapiCallbackContext = NULL;
      }
    }
    return ret_val;
}

/**
   @brief: De-Initializes the callback module.

   The function marks the task TO BE DELETED so that scheduler can remove it. 
*/
void Deinitialize_TME_Callback(void)
{
    // Set the initialize flag to false
    is_tme_callback_initialized = false;
    // Delete the created task
    Delete_TME_Task();
}

/**
   @brief: Function to determine whether a callback is pending or not.

   @return true if pending or false otherwise
*/
qbool_t Is_Callback_Pending(void)
{
   return (QapiCallbackContext != NULL);
}
