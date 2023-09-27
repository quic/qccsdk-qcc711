/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef TMECOMCLIENT_H
#define TMECOMCLIENT_H
/**
   @file TmecomClient.h
   @brief Public api's shared with TME Clients to request TME services.
*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stdbool.h>

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
#define TMECOM_DEFAULT_TIMEOUT 0x0

#define SEC_TO_MS 1000                    /* Sec to Milli seconds; 10^3. */
#define SEC_TO_US (SEC_TO_MS * SEC_TO_MS) /* Sec to Micro seconds; 10^6. */

/** Default max time (microseconds) TMECOM should wait for response from TME. */
#define TMECOM_DEFAULT_TIMEOUT_US                                              \
    (3 * SEC_TO_US) /* 3sec (should be less than minimum of Apps/Btss and TME WDOG). */

/* -----------------------------------------------------------------------------------------
 * Used for parameters of type TME_MSG_PARAM_TYPE_BUF_IN
 * ---------------------------------------------------------------------------------------*/
typedef struct tme_msg_param_type_buf_in_s {
    void       *pBuffer;
    size_t      bufLen;
} TmeMsgParamTypeBufIn_t;

/*------------------------------------------------------------------------------------------
 * Used for parameters of type TME_MSG_PARAM_TYPE_BUF_OUT
 * ---------------------------------------------------------------------------------------*/
typedef struct tme_msg_param_type_buf_out_s {
    void       *pBuffer;
    size_t      bufLen;
    size_t      bufOutLen;
} TmeMsgParamTypeBufOut_t;

/*------------------------------------------------------------------------------------------
 * Used for parameters of type TME_MSG_PARAM_TYPE_BUF_IN_OUT
 * ---------------------------------------------------------------------------------------*/
typedef TmeMsgParamTypeBufOut_t TmeMsgParamTypeBufInOut_t;

/* -----------------------------------------------------------------------------------------
 * Struct to pack call-back data.
 * ---------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t  tmeMsgUid;
    void     *genericPayload;
    uint32_t  genericPayloadLen;
    void     *userData;
}TmecomCallbackData_t;

/*----------------------------------------------------------------------------
 * Defines TMECOM responses.
 * Maps TME communication layer responses to one of below error code. 
 * -------------------------------------------------------------------------*/
typedef enum {
  /* Definitions of Successful Returns. Any positive values within 0 to 127. */
  TMECOM_RSP_SUCCESS  = 0,

  TMECOM_RSP_SUCCESS_MAXVAL = 127,

  /* Definitions of Failure Returns. Any negative values within -32 to -128.
     Values from -1 to -31 are reserved for glink defined errors. */
  TMECOM_RSP_FAILURE = -32,
  TMECOM_RSP_FAILURE_BAD_ADDR = -33,
  TMECOM_RSP_FAILURE_INVALID_ARGS = -34,
  TMECOM_RSP_FAILURE_CHANNEL_ERR = -35,
  TMECOM_RSP_FAILURE_LINK_ERR = -36,
  TMECOM_RSP_FAILURE_TX_ERR = -37,
  TMECOM_RSP_FAILURE_RX_ERR = -38,
  TMECOM_RSP_FAILURE_TIMEOUT = -39,
  TMECOM_RSP_FAILURE_BUSY = -40,
  TMECOM_RSP_FAILURE_INVALID_MESSAGE = -41,
  TMECOM_RSP_SERVICE_API_RETURNED_ERR = -42,
  TMECOM_RSP_FAILURE_NOT_SUPPORTED = -43,
  TMECOM_RSP_HANDLE_CMD_FAILED = -44,

  /* Tmecom software specific error codes. */
  TMECOM_RSP_FAILURE_TX_FAILED = -100,
  TMECOM_RSP_FAILURE_TME_PWR_STATE_TIMEOUT = -101,
  TMECOM_RSP_FAILURE_TME_BOOT_STATE_TIMEOUT = -102,
  TMECOM_RSP_FAILURE_CHANNEL_CONNECT_ERR_TIMEOUT = -103,
  TMECOM_RSP_FAILURE_CHANNEL_DISCONNECT_ERR_TIMEOUT = -104,
  TMECOM_RSP_FAILURE_TX_DONE_TIMEOUT = -105,
  TMECOM_RSP_FAILURE_RX_DONE_TIMEOUT = -106,

  TMECOM_RSP_FAILURE_MAX = -128,
}TmecomResponse_t;

/*=============================================================================

                     PUBLIC FUNCTION DEFINITIONS

=============================================================================*/
/**
   @brief Callback function invoked when TME response arrives.
          This is used when requester wants to continue execution
          after sending messages.
   
   @param[in] status            TMECOM layer response.
   @param[in] cbData            Userdata passed to caller.

   @note Except status all other parameter received during TME request
         through TmecomClientSendMessage() api and those copied back.
*/
typedef void (*pTmecomNotifyRxCallBack)(TmecomResponse_t status,
                                        TmecomCallbackData_t *cbData);

/**
   @brief API to start a TME session.
          This API used for power control, bring TME online if it's
          in shutdown state. Also it establish transport layer link.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomClientSessionStart(void);

/**
   @brief API to end a TME session.
          This API used for power control, remove the vote placed
          during session start to keep TME Alive.
          It close transport layer link before taking out the vote.
   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomClientSessionEnd(void);

/**
   @brief API to send a message to TME used to request a service from TME. 

   @param[in] tmeMsgUid         TME request identifier. Defined at TmeMessagesUids.h
                                Consists of messageType(15:8) : actionID(7:0)
   @param[in] tmeMsgParamID     Describe no. of parameter & there types in genericPayLoad.
                                Defined at TmeMessagesUids.h along with Message UID.
                                Consists of paramType's(31:4) : paramCount(3:0)
   @param[in] isBlocking        Client notify if it will wait or continue execution after sending
                                message. If opt for not blocking, response notified with cbApi.
   @param[in] timeout           For a blocking call, client can set max time in microseconds it
                                can wait for response.
                                If there is no intended timeout then client should pass TMECOM_DEFAULT_TIMEOUT.
   @param[in] genericPayLoad    Reference to a genericPayLoad. Payload can have 0 to 14 parameter.
                                Each parameter is 4Byte(fixed size).
   @param[in] genericPayLoadLen Byte length of genericPayLoad.
   @param[in] cbApi             Callback function invoked when TME response arrives.
                                Not required if isBlocking=true.
   @param[in] userData          Placeholder for client data. Can be used to pass a context
                                to cbApi if required.

   @return A response of type TmecomResponse_t.
*/
TmecomResponse_t TmecomClientSendMessage(uint32_t                 tmeMsgUid,
                                         uint32_t                 tmeMsgParamID,
                                         bool                     isBlocking,
                                         uint32_t                 timeout,
                                         void                     *genericPayLoad,
                                         uint32_t                 genericPayLoadLen,
                                         pTmecomNotifyRxCallBack  cbApi,
                                         void                     *userData);

/**
   @brief API to check if TMECOM is busy in prcessing any IPC request.
          If any IPC request is going on then this API will return busy error,
          else if TMECOM is free to handle a new IPC request then will return success.

   @return TMECOM_RSP_SUCCESS if TMEOCM is free and new IPC request can be posted.
           TMECOM_RSP_FAILURE_BUSY if already there is an IPC request in transit.
*/
TmecomResponse_t IsTmecomClientBusy(void);

#endif // TMECOMCLIENT_H
