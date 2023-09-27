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
#include "qapi_crypto.h"

 // TME utility headers
#include "tme_crypto_params.h"
#include "tme_types.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_callback_utils.h"

// TME interface headers
#include "tme_crypto_digest_interface.h"
#include "tme_crypto_rng_interface.h"

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
/**
   @brief Validate QAPI parameters and create corresponding digest IPC message.

   @param[in]      QapiDigestParams  qapi digest parameters.
   @param[in, out] TMEIPCMsg         TME digest IPC message.
   @param[in, out] TMEIPCMsgLength   TME digest IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Digest_IPC_Msg(void *QapiDigestParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_Digest_Params_t *DigestParams = (qapi_CRPT_Digest_Params_t *)QapiDigestParams;
   if (DigestParams == NULL || DigestParams->Message == NULL || DigestParams->Digest == NULL ||
   	   QAPI_CRPT_GET_TME_DIGEST_ALGO(DigestParams->Algo) == 0 || DigestParams->DigestLen == 0)
   {
     return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEDigestMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEDigestMessage *DigestIPCMsg = (TMEDigestMessage *)(*TmeIPCMsg);
   DigestIPCMsg->input.algo = QAPI_CRPT_GET_TME_DIGEST_ALGO(DigestParams->Algo);
   DigestIPCMsg->input.input.pData = DigestParams->Message;
   DigestIPCMsg->input.input.length = DigestParams->MessageLen;
   DigestIPCMsg->output.response.pData  = DigestParams->Digest;
   DigestIPCMsg->output.response.length = DigestParams->DigestLen;
   return QAPI_OK;
}

/**
   @brief Process digest IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiDigestParams  qapi digest parameters.
   @param[in] TMEIPCMsg   TME digest IPC message.
   @param[in] Status      Tmecom return status.
   @param[in] CallBack    qapi callback function.
   @param[in] UserData    Placeholder for user data.   

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Process_Digest_IPC_Msg_Response(void *QapiDigestParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *CallBack,
                                              void *UserData)
{

   TMEDigestMessage *DigestIPCMsg = (TMEDigestMessage *)(TMEIPCMsg);
   qapi_CRPT_Digest_Params_t *DigestParams = (qapi_CRPT_Digest_Params_t *)QapiDigestParams;
   DigestParams->DigestLenUsed = DigestIPCMsg->output.response.lengthUsed;

   if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(DigestIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_DIGEST_E;
        EventData->Data.DigestParams = QapiDigestParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }
   return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding get random IPC message.

   @param[in]      QapiGetRandomParams   qapi get random parameters.
   @param[in, out] TMEIPCMsg             TME get random IPC message.
   @param[in, out] TMEIPCMsgLength       TME IPC message length.

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.
*/
qapi_Status_t Validate_And_Create_Get_Random_IPC_Msg(void *QapiGetRandomParams,
                                                     void **TmeIPCMsg,
                                                     uint32_t *TmeIPCMsgLength)
{
   qapi_CRPT_RNG_Params_t *GetRandomParams = (qapi_CRPT_RNG_Params_t *)QapiGetRandomParams;
   if (GetRandomParams == NULL || GetRandomParams->RandomNumberLen == 0 ||
       GetRandomParams->RandomNumber == NULL)
   {
      return QAPI_ERR_INVALID_PARAM;
   }

   *TmeIPCMsgLength = sizeof(TMEGetRandomMessage);
   *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
   if (*TmeIPCMsg == NULL)
   {
      return QAPI_ERR_NO_MEMORY;
   }

   TMEGetRandomMessage *GetRandomIPCMsg = (TMEGetRandomMessage *)(*TmeIPCMsg);

   GetRandomIPCMsg->input.length =  GetRandomParams->RandomNumberLen;
   GetRandomIPCMsg->output.response.pData = GetRandomParams->RandomNumber;
   GetRandomIPCMsg->output.response.length = GetRandomParams->RandomNumberLen;

   return QAPI_OK;
}

/**
   @brief Process get random IPC message response. Create event data for non-blocking call.
 
   @param[in] QapiGetRandomParams qapi get random  parameters.
   @param[in] TMEIPCMsg           TME ger random IPC message.
   @param[in] Status              Tmecom return status.
   @param[in] CallBack            qapi callback function.
   @param[in] UserData            Placeholder for user data.   

   @return QAPI_OK if completed successfully, or a negative
           value if there was an error.                  

*/
qapi_Status_t Process_Get_Random_IPC_Msg_Response(void *QapiGetRandomParams,
                                                  void *TMEIPCMsg,
                                                  qapi_Status_t Status,
                                                  void *CallBack,
                                                  void *UserData)
{

   TMEGetRandomMessage *GetRandomIPCMsg = (TMEGetRandomMessage *)(TMEIPCMsg);

    if(Status == QAPI_OK)
   {
      Status = qapi_Convert_Tme_Status(GetRandomIPCMsg->output.status);
   }

   // Only executed for Non blocking call, when CallBack is not null.
   if (CallBack != NULL)
   {
      qapi_CRPT_Operation_Event_Data_t *EventData;
      EventData = qapi_Malloc(sizeof(qapi_CRPT_Operation_Event_Data_t));
      if(EventData == NULL)
      {
        Status = QAPI_ERR_NO_MEMORY;
      }
      else
      {
        EventData->Operation = QAPI_CRPT_OPERATION_RNG_E;
        EventData->Data.RNGParams = QapiGetRandomParams;
        Status = Process_TME_Callback(Status, CRYPTO_EVENT_DATA, EventData, UserData, CallBack);
      }
   }
   return Status;
}
