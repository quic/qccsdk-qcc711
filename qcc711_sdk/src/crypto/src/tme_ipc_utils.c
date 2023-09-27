/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

// QAPI headers
#include "qapi_status.h"
#include "qapi_heap.h"

// TME utility headers
#include "tme_crypto_params.h"
#include "tme_types.h"
#include "tme_ipc_crypto_common.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_msg_uid_mapping.h"
#include "tme_ipc_callback_utils.h"

// TMECOM headers
#include "TmecomClient.h"
#include "TmeMessagesUids.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
/* timeout(in microseconds) for tmecom non-blocking call. */ 
static uint32_t TmecomTimeout = TMECOM_DEFAULT_TIMEOUT;

/*!
 * @struct TMEQapiParams
 * @brief Structure containing qapi parameters.
 */
typedef struct PACKED_PREFIX tme_qapi_params_s
{
    void         *params;   /*!< QAPI parameters. */
    void         *userData; /*!< QAPI user data. */
    void         *callback; /*!< QAPI callback. */
} TMEQapiParams;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static void TmecomCallback(TmecomResponse_t Status, TmecomCallbackData_t *cbData);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Convert tmecom status to qapi status

   @param[in] Status   TMECOM status.

   @return Corresponding qapi status will be returned.
*/
qapi_Status_t qapi_Convert_Tmecom_Status(TmecomResponse_t Status)
{
   qapi_Status_t qapi_status;
   switch(Status)
   {
      case TMECOM_RSP_SUCCESS:
         qapi_status = QAPI_OK;
         break;
      case TMECOM_RSP_FAILURE:
         qapi_status = QAPI_ERROR;
         break;
      case TMECOM_RSP_FAILURE_INVALID_ARGS:
         qapi_status = QAPI_ERR_INVALID_PARAM;
         break;
      case TMECOM_RSP_FAILURE_BAD_ADDR:
         qapi_status = QAPI_ERR_BAD_PAYLOAD;
         break;
      case TMECOM_RSP_FAILURE_BUSY:
         qapi_status = QAPI_ERR_BUSY;
         break;
      default:
         qapi_status = QAPI_ERROR;
   }
   return qapi_status;
}

/**
   @brief Convert tme status to qapi status

   @param[in] Status   TMEStatus status.

   @return Corresponding qapi status will be returned.
*/
qapi_Status_t qapi_Convert_Tme_Status(TMEStatus Status)
{
   qapi_Status_t qapi_status;
   switch(Status)
   {
      case TME_STATUS_SUCCESS:
         qapi_status = QAPI_OK;
         break;
      case TME_STATUS_FAILURE:
         qapi_status = QAPI_ERROR;
         break;
      case TME_STATUS_INVALID_INPUT:
         qapi_status = QAPI_ERR_INVALID_PARAM;
         break;
      case TME_STATUS_MALFORMED_TOKEN:
         qapi_status = QAPI_ERROR;
         break;
      case TME_STATUS_NOT_IMPLEMENTED:
         qapi_status = QAPI_ERR_NOT_SUPPORTED;  
         break;
      default:
         qapi_status = QAPI_ERROR;
   }
   return qapi_status;
}

/**
   @brief Callback function invoked when TME response arrives.
          This is used when requester wants to continue execution
          after sending messages.
   
   @param[in] status            TMECOM layer response.
   @param[in] cbData            UserData passed to caller.

   @note Except status all other parameter received during TME request
         through TmecomClientSendMessage() API and those copied back..
*/
static void TmecomCallback(TmecomResponse_t Status,
                           TmecomCallbackData_t *cbData)
{
   if (cbData == NULL)
   {
      return;
   }

   TMEQapiParams *QapiParams = (TMEQapiParams *)(cbData->userData);
   if ((QapiParams != NULL) && (cbData->genericPayload != NULL) &&
       (cbData->genericPayloadLen != 0))
   {
      TMEIPCQapiMapping *TmeMessageMapping =  Get_TME_Message_Mapping(cbData->tmeMsgUid);
      qapi_Status_t qapiStatus = qapi_Convert_Tmecom_Status(Status);
      
      if (TmeMessageMapping != NULL) 
      {
         TmeMessageMapping->processIPCMsgResponse(QapiParams->params, cbData->genericPayload,
                                                  qapiStatus, QapiParams->callback,
                                                  QapiParams->userData);
      }  
   }

   // Free the heap memory allocated to IPCMsg while invoking TME IPC
   if (cbData->genericPayload != NULL)
   {
      qapi_Free(cbData->genericPayload);
   }

   // Free the heap memory allocated to QapiParams while invoking TME IPC
   if (cbData->userData != NULL)
   {
      qapi_Free(cbData->userData);
   }
}

/**
   @brief Perform operation based on message ID.

   @param[in] TmeMsgUid         TME request identifier.
   @param[in] TmeMsgParamID     TME message param ID.
   @param[in] QapiCryptoParams  qapi crypto parameters.
   @param[in] Callback          qapi callback function.
   @param[in] UserData          Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.

*/
qapi_Status_t qapi_Perform_Operation(uint32_t     TmeMsgUid,
                                     uint32_t     TmeMsgParamID,
                                     void        *QapiCryptoParams,
                                     void        *Callback,
                                     void        *UserParam)
{
   void *IPCMsg = NULL;
   uint32_t IPCMsgLength = 0;
   qapi_Status_t qret = QAPI_ERROR;
   TmecomResponse_t ret = TMECOM_RSP_FAILURE;
   TMEIPCQapiMapping *TmeMessageMapping = NULL;

   if (QapiCryptoParams == NULL)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   // Verify whether TME is busy or there any Callback pending
   // Accordingly return Busy error
   if((IsTmecomClientBusy() != TMECOM_RSP_SUCCESS) || (Callback != NULL && Is_Callback_Pending()))
   {
     return QAPI_ERR_BUSY;
   }

   TmeMessageMapping = Get_TME_Message_Mapping(TmeMsgUid);
   if (TmeMessageMapping == NULL || TmeMessageMapping->validateAndCreateIPCMsg == NULL
       || TmeMessageMapping->processIPCMsgResponse == NULL)
   {
      return qret;
   }
  
   qret = TmeMessageMapping->validateAndCreateIPCMsg(QapiCryptoParams, &IPCMsg, &IPCMsgLength);
   if (qret != QAPI_OK)
   {
      if (IPCMsg != NULL)
      { 
         qapi_Free(IPCMsg);
      }
      
      return qret;    
   }

   TMEQapiParams *QapiParams = NULL;
   if (Callback != NULL)
   {
      QapiParams = qapi_Malloc(sizeof(TMEQapiParams));
      if(QapiParams == NULL)
      {
         if(IPCMsg != NULL) qapi_Free(IPCMsg);
         return QAPI_ERR_NO_MEMORY;
      }
   
      QapiParams->params   = QapiCryptoParams;
      QapiParams->callback = Callback;
      QapiParams->userData = UserParam;
   }

   // Send message to TME
   ret = TmecomClientSendMessage(TmeMsgUid,
                                 TmeMsgParamID,
                                 (Callback == NULL),
                                 TmecomTimeout,
                                 IPCMsg,
                                 IPCMsgLength,
                                 TmecomCallback,
                                 QapiParams);

   qret = qapi_Convert_Tmecom_Status(ret);

   // For blocking mode, memory allocated for IPCMsg will be released.
   if (Callback == NULL)
   {
      if(qret == QAPI_OK)
      {
         qret = TmeMessageMapping->processIPCMsgResponse(QapiCryptoParams, IPCMsg, qret,
                                                         Callback, UserParam);
      }
      if(IPCMsg != NULL)
      {
         qapi_Free(IPCMsg);
      }   
   }

   // For Non blocking mode, memory allocated for IPCMsg and QapiParams
   // will only be released if failure is returned from TmecomClientSendMessage().
   // In case of success, the memory will be released inside TmecomCallback().
   else if (Callback != NULL && qret != QAPI_OK) 
   {
      if(IPCMsg != NULL)
      {
         qapi_Free(IPCMsg);
      }

      if (QapiParams != NULL) 
      {
         qapi_Free(QapiParams);
      }
   }

   return qret;
}
