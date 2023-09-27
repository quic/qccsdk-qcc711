/*
 * Copyright (c) 2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================

                    Fuse Interface Source File

=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Tmecom.h"
#include "qapi_fuse.h"
#include "TmecomClient.h"
#include "TmeFuseClient.h"
#include "TmeErrorCodes.h"
#include "TmeMessagesUids.h"
#include "TmeFusePlatformApis.h"

/*----------------------------------------------------------------*
 *                        Pre-Defined MACROS                      *
 *----------------------------------------------------------------*/
#if defined(__ICCARM__)
   #define PACKED_PREFIX                  __packed
#else
   #define PACKED_PREFIX                  __attribute__((__packed__))
#endif

#define OTP_MTP_ADDR_ALIGN_MASK              0x3
#define FUSE_ADDR_UNALIGN(addr)              ((addr) & OTP_MTP_ADDR_ALIGN_MASK)


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
 * @struct TmeFuseInterfaceMessageFmt_t
 * @brief Common structure for all Fuse service request messages.
 */
typedef PACKED_PREFIX struct TmeFuseInterfaceMessageFmt_s
{
    uint32_t  status;          /**< status of the response */
    uint32_t  params[];        /**< Place holder for all remainning params. */
} TmeFuseInterfaceMessageFmt_t;


/**
 * @struct TmeFuseSingleRdWrMessage_t
 * @brief Structure of fuse read/write request message.
 */
typedef PACKED_PREFIX struct TmeFuseSingleRdWrMessage_s
{
    uint32_t  status;          /**< status of the response */
    uint32_t  fuseAddr;        /**< Address of OTP/MTP to be written OR to read */
    uint32_t  fuseVal;         /**< Value to be written in the OTP/MTP for write request, for
                                    read request val get populated with contents of OTP/MTP */
} TmeFuseSingleRdWrMessage_t;

/**
 * @struct TmeFuseMultipleWrMessage_t
 * @brief Structure for fuse write request message.
 */
typedef PACKED_PREFIX struct TmeFuseMultipleWrMessage_s
{
    uint32_t  status;                          /**< status of the response */
    TmeMsgParamTypeBufIn_t  fuseWrData;        /**< Fuse write request buffer containing array of [addr, val] */
} TmeFuseMultipleWrMessage_t;

typedef TmeFuseMultipleWrMessage_t TmeFuseSecureWrMessage_t;

/**
 * @struct TmeFuseMultipleRdMessage_t
 * @brief Structure for fuse read request message.
 */
typedef PACKED_PREFIX struct TmeFuseMultipleRdMessage_s
{
    uint32_t  status;                             /**< status of the response */
    TmeMsgParamTypeBufInOut_t  fuseRdData;        /**< Fuse read request buffer containing array of [addr, val] */
} TmeFuseMultipleRdMessage_t;

/*=============================================================================

                     STATIC FUNCTION DEFINITION

=============================================================================*/
/**
   @brief API to convert tmecom layer response to TME error types.
   
   @param[in] status            TMECOM layer response.

   @note This API majorly used when Tmecom & Tme error need to return through single status
         Tmecom layer response checked first before checking TME response.
*/
static TME_ERROR convertToTmeError(TmecomResponse_t status)
{
  if (TMECOM_RSP_FAILURE_BUSY == status) {
    return TME_ERROR_TME_BUSY;
  } else if (TMECOM_RSP_SUCCESS != status) {
    return TME_ERROR_TMECOM_FAILURE;
  }
  return TME_SUCCESS;
}

/**
   @brief API to convert TME error types to QAPI error types.

   @param[in] tmeError     TME Error.

   @note This API majorly used when Tme fuse error need to return through single QAPI status
*/
static qapi_Status_t convertToQapiError(TME_ERROR tmeError)
{
  return (TME_SUCCESS == tmeError) ? QAPI_OK : QAPI_ERROR;
}

/**
   @brief Callback function invoked when TME response arrives.
          This is used when requester wants to continue execution
          after sending messages.
   
   @param[in] status            TMECOM layer response.
   @param[in] cbData            Callback data passed by TMECOM.

   @note Except status all other parameter received during TME request
         through TmecomClientSendMessage() api and those copied back.
*/
static void tmecomCallBack(TmecomResponse_t status,
                           TmecomCallbackData_t *cbData)
{

  TME_ERROR tmeRet = TME_ERROR_GENERIC;
  TmeFuseCallBackData_t        *fuseCbData = NULL;
  TmeFuseInterfaceMessageFmt_t *msg        = NULL;

  if ((NULL == cbData) || (NULL == cbData->userData) || (NULL == cbData->genericPayload)) {
    // TODO: Fatal Error
    while(1);
  }

  fuseCbData = (TmeFuseCallBackData_t*)(cbData->userData);

  msg = (TmeFuseInterfaceMessageFmt_t*)(cbData->genericPayload);

  if (status != TMECOM_RSP_SUCCESS) {
    /* There is an error from IPC transport layer */
    tmeRet = TME_ERROR_TMECOM_FAILURE; 
    goto exit;
  }
  else {
    /* Use return value from TME Fuse IPC handler */
    tmeRet = msg->status;
    goto exit;
  }

exit:

  /* Call user call back if it was registered */
  if(fuseCbData && fuseCbData->cbApi) {
    TmeFuseOsHandleCallBack(fuseCbData, convertToQapiError(tmeRet));
  }

  if(cbData->userData)
  {
    TmecomOsMemFree((void **)&(cbData->userData));
  }

  if(msg)
  {
    TmecomOsMemFree((void **)&msg);
  }
}
/*=============================================================================

                     PUBLIC FUNCTION DEFINITION

=============================================================================*/
/**
   @brief Read single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to read.
   @param [out]    fuseVal      Read data from OTP/MTP.

   @return
           - TME_SUCCESS if the data read from fuse (OTP/MTP) successful.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.
*/
TME_ERROR TmeFuseRead(uint32_t  fuseAddr,
                      uint32_t  *fuseVal)
{
  TmeFuseSingleRdWrMessage_t msg = {
    .status = TME_ERROR_GENERIC,
    .fuseAddr = fuseAddr,
  };
  TME_ERROR ret = TME_ERROR_GENERIC;
  TmeFuseOpAccessType_t access = TME_FUSE_OP_DISALLOWED;

  if ((NULL == fuseVal) || FUSE_ADDR_UNALIGN(fuseAddr)) {
    ret = TME_ERROR_BAD_PARAMETER; 
    goto exit;
  }

  access = TmeFuseGetAccessType(fuseAddr, TME_FUSE_OP_READ);
  if (TME_FUSE_OP_VIA_IPC == access) {
    TmecomResponse_t tmecomRet = TmecomClientSendMessage(TME_MSG_UID_FUSE_READ_SINGLE,
                                     TME_MSG_UID_FUSE_READ_SINGLE_PARAM_ID,
                                     true /*isBlocking*/, TMECOM_DEFAULT_TIMEOUT,
                                     &msg, sizeof(msg),
                                     NULL /*cbApi*/, NULL /*userData*/);

    ret = convertToTmeError(tmecomRet);
    if ( (TME_SUCCESS == ret) && (TME_SUCCESS != msg.status) ) {
      ret = msg.status; 
      goto exit;
    }
    *fuseVal = msg.fuseVal;
  } else if (TME_FUSE_OP_DIRECTLY == access) {
    *fuseVal = *(volatile uint32_t*)fuseAddr;
    ret = TME_SUCCESS;
  } else {
    /* Read not allowed. */
    ret = TME_ERROR_BAD_PARAMETER; 
  }

exit:
    return ret;
}

/**
   @brief  Reads multiple OTP/MTP presented by an array of [addr, val]

   @param [in,out] fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and all fuse read successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
              non-blocking mode not supported currently.
*/
TME_ERROR TmeFuseReadMultiple(TmeFuse_t             *fuseArray,
                              size_t                fuseArraySz,
                              TmeFuseOperationCB_t  fuseOpCB,
                              void                  *userParam)
{
  TME_ERROR ret = TME_ERROR_GENERIC;
  bool isBlocking = true;
  bool singleIpcRequired = true;

  /* TODO: Add support for non-blocking mode. */
  if (NULL != fuseOpCB) {
    ret = TME_ERROR_NOT_SUPPORTED;
    goto exit;
  }

  if (NULL == fuseArray || 0 == fuseArraySz) {
    ret = TME_ERROR_BAD_PARAMETER; 
    goto exit;
  }

  /* Check if complete request can be send to TME or not. */
  for (size_t i=0; i<fuseArraySz; i++) {
    TmeFuseOpAccessType_t access = TmeFuseGetAccessType(fuseArray[i].addr, TME_FUSE_OP_READ);
    if (TME_FUSE_OP_DISALLOWED == access) {
      ret = TME_ERROR_BAD_PARAMETER; 
      goto exit;
    } else if (TME_FUSE_OP_VIA_IPC != access) {
      singleIpcRequired = false;
      break;
    }
  }

  if (singleIpcRequired) {
    /* Read all via TME IPC. */
    TmeFuseMultipleRdMessage_t msg = {
      .status = TME_ERROR_GENERIC,
      .fuseRdData.pBuffer = fuseArray,
      .fuseRdData.bufLen  = fuseArraySz * sizeof(TmeFuse_t),
      .fuseRdData.bufOutLen = 0x0,
    };
    TmecomResponse_t tmecomRet = TmecomClientSendMessage(TME_MSG_UID_FUSE_READ_MULTIPLE,
                                     TME_MSG_UID_FUSE_READ_MULTIPLE_PARAM_ID,
                                     isBlocking, TMECOM_DEFAULT_TIMEOUT,
                                     &msg, sizeof(msg),
                                     NULL /*cbApi*/, NULL /*userData*/);

    ret = convertToTmeError(tmecomRet);
    if ( (TME_SUCCESS == ret) && (TME_SUCCESS != msg.status) ) {
      ret = msg.status; 
      goto exit;
    }
  } else {
    /* Read one by one. */
    for (size_t i=0; i<fuseArraySz; i++) {
      ret = TmeFuseRead(fuseArray[i].addr, &fuseArray[i].val);
      if (TME_SUCCESS != ret){
        goto exit;
      }
    }
    ret = TME_SUCCESS;
  }

exit:
    return ret;
}

/**
   @brief Writes single OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address to write to.
   @param [in]     fuseVal      Data to write to OTP/MTP.

   @return
           - TME_SUCCESS if the data was successfully written to Fuse (OTP/MTP).
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.
*/
TME_ERROR TmeFuseWrite(uint32_t  fuseAddr,
                       uint32_t  fuseVal)
{
  TME_ERROR ret = TME_ERROR_GENERIC;
  bool nvmReqWrite = false;
  TmeFuseOpAccessType_t access = TmeFuseGetAccessType(fuseAddr, TME_FUSE_OP_WRITE);

  if (TME_FUSE_OP_VIA_IPC == access) {
    TmeFuseSingleRdWrMessage_t msg = {
      .status = TME_ERROR_GENERIC,
      .fuseAddr = fuseAddr,
      .fuseVal  = fuseVal,
    };
    TmecomResponse_t tmecomRet = TmecomClientSendMessage(TME_MSG_UID_FUSE_WRITE_SINGLE,
                                     TME_MSG_UID_FUSE_WRITE_SINGLE_PARAM_ID,
                                     true /*isBlocking*/, TMECOM_DEFAULT_TIMEOUT,
                                     &msg, sizeof(msg),
                                     NULL /*cbApi*/, NULL /*userData*/);

    ret = convertToTmeError(tmecomRet);
    if ( (TME_SUCCESS == ret) && (TME_SUCCESS != msg.status) ) {
      ret = msg.status;
      goto exit;
    }
  } else if (TME_FUSE_OP_DIRECTLY == access) {
    if (TME_SUCCESS != (ret = TmeFuseNvmRequestWrite())) {
      goto exit;
    }
    nvmReqWrite = true;
    if (TME_SUCCESS != (ret = TmeFuseNvmWrite((void *)fuseAddr, &fuseVal, sizeof(fuseVal)))) {
      goto exit; 
    }
    ret = TME_SUCCESS;
  } else {
    /* Write not allowed to the address. */
    ret = TME_ERROR_BAD_PARAMETER; 
  }

exit:
    if (nvmReqWrite) {
      if (TME_SUCCESS != TmeFuseNvmReleaseWrite()) {
        ret = TME_ERROR_GENERIC;
      }
    }
    return ret;
}

/**
   @brief  Writes multiple OTP/MTP presented by an array of [addr, val]

   @param [in]     fuseArray    Pointer to an array of [addr, val]
   @param [in]     fuseArraySz  Number of elements of the array
   @param [in]     fuseOpCB     Callback function, only used in non-blocking mode.
                                NULL for blocking mode.
   @param [in]     userParam    User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and all fuse writes successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter fuseArray should be in heap or a static
              buffer. TME will access the buffer.
              non-blocking mode not supported currently.
*/
TME_ERROR TmeFuseWriteMultiple(TmeFuse_t             *fuseArray,
                               size_t                fuseArraySz,
                               TmeFuseOperationCB_t  fuseOpCB,
                               void                  *userParam)
{
  TME_ERROR ret = TME_ERROR_GENERIC;
  bool isBlocking = true;
  bool nvmReqWrite = false;
  bool singleIpcRequired = true;
  bool noIpcRequired = true;

  /* TODO: Add support for non-blocking mode. */
  if (NULL != fuseOpCB) {
    ret = TME_ERROR_NOT_SUPPORTED;
    goto exit;
  }

  if (NULL == fuseArray || 0 == fuseArraySz) {
    ret = TME_ERROR_BAD_PARAMETER; 
    goto exit;
  }

  /* Check if complete request can be send to TME or complete request can be served with out an IPC. */
  for (size_t i=0; i<fuseArraySz; i++) {
    TmeFuseOpAccessType_t access = TmeFuseGetAccessType(fuseArray[i].addr, TME_FUSE_OP_WRITE);
    if (TME_FUSE_OP_VIA_IPC != access){
      singleIpcRequired = false;
    }
    if (TME_FUSE_OP_VIA_IPC == access) {
      noIpcRequired = false;
    }
  }

  if (singleIpcRequired) {
    /* Write all via TME IPC. */
    TmeFuseMultipleWrMessage_t msg = {
      .status = TME_ERROR_GENERIC,
      .fuseWrData.pBuffer = fuseArray,
      .fuseWrData.bufLen  = fuseArraySz * sizeof(TmeFuse_t),
    };
    TmecomResponse_t tmecomRet = TmecomClientSendMessage(TME_MSG_UID_FUSE_WRITE_MULTIPLE,
                                     TME_MSG_UID_FUSE_WRITE_MULTIPLE_PARAM_ID,
                                     isBlocking, TMECOM_DEFAULT_TIMEOUT,
                                     &msg, sizeof(msg),
                                     NULL /*cbApi*/, NULL /*userData*/);

    ret = convertToTmeError(tmecomRet);
    if ( (TME_SUCCESS == ret) && (TME_SUCCESS != msg.status) ) {
      ret = msg.status; 
      goto exit;
    }
  } else if(noIpcRequired) {
    /* Write all directly. */
    if (TME_SUCCESS != (ret = TmeFuseNvmRequestWrite())) {
      goto exit;
    }
    nvmReqWrite = true;
    for (size_t i=0; i<fuseArraySz; i++) {
      if (TME_SUCCESS != (ret = TmeFuseNvmWrite((void *)fuseArray[i].addr,
                                               &fuseArray[i].val,
                                               sizeof(fuseArray[i].val)))) {
        goto exit; 
      }
    }
    ret = TME_SUCCESS;
  } else {
    /* Mix request, write one by one. */
    for (size_t i=0; i<fuseArraySz; i++) {
      ret = TmeFuseWrite(fuseArray[i].addr, fuseArray[i].val);
      if (TME_SUCCESS != ret){
        goto exit;
      }
    }
  }

exit:
  if (nvmReqWrite) {
    if (TME_SUCCESS != TmeFuseNvmReleaseWrite()) {
      ret = TME_ERROR_GENERIC;
    }
  }
  return ret;
}

/**
   @brief  Writes to the secure OTP.

   @param [in]     signedWriteSequence    Signed write command for Secure OTP write.
   @param [in]     signedWriteSequenceLen Byte length of signedWriteSequence.
   @param [in]     fuseOpCB               Callback function, only used in non-blocking mode.
                                          NULL for blocking mode.
   @param [in]     userParam              User parameter, returned as-is in callback.
 
   @return
           - TME_SUCCESS if blocking operation completed successfully and secure fuse write successful
             or a non-blocking call was successfully accepted.
           - TME_ERROR_TME_BUSY indicating some other TME operation was ongoing.
           - Any error code of the form TME_ERROR_XXX defined in TmeErrorCodes.h.

   \attention The input parameter SecureFuseParams should be in heap or a static
              buffer. TME will access the buffer.
*/
TME_ERROR TmeFuseWriteSecureFuse(uint8_t               *signedWriteSequence,
                                 uint32_t               signedWriteSequenceLen,
                                 TmeFuseOperationCB_t   fuseOpCB,
                                 void                  *userParam)
{

  TME_ERROR ret = TME_ERROR_GENERIC;
  bool isBlocking = true;
  pTmecomNotifyRxCallBack tmecomCBApi = NULL;
  TmeFuseCallBackData_t *cbData = NULL;
  TmecomResponse_t tmecomRet = TMECOM_RSP_FAILURE;
  TmeFuseSecureWrMessage_t *msg = NULL;

  if (TMECOM_RSP_SUCCESS != TmecomOsMemAlloc((void**)&msg, sizeof(TmeFuseSecureWrMessage_t)))
  {
      ret = TME_ERROR_GENERIC; 
      goto exit;
  }

  /* Construct IPC message */
  msg->status = TME_ERROR_GENERIC;
  msg->fuseWrData.pBuffer = signedWriteSequence;
  msg->fuseWrData.bufLen  = signedWriteSequenceLen;

  if (NULL != fuseOpCB)
  {
    if (TMECOM_RSP_SUCCESS != TmecomOsMemAlloc((void**)&cbData, sizeof(TmeFuseCallBackData_t)))
    {
      ret = TME_ERROR_GENERIC; 
      goto exit;
    }
    cbData->cbApi  = (void *)fuseOpCB;
    cbData->cbUserData = userParam;
    cbData->eventData.operation = QAPI_FUSE_WRITE_SECURE_FUSE_E;
    cbData->eventData.Data.fuseWriteSecureParams.signedWriteSequence = signedWriteSequence;
    cbData->eventData.Data.fuseWriteSecureParams.signedWriteSequenceLen = signedWriteSequenceLen;
    tmecomCBApi = tmecomCallBack;
    isBlocking = false;
  }

  tmecomRet = TmecomClientSendMessage(TME_MSG_UID_FUSE_WRITE_SECURE,
                                   TME_MSG_UID_FUSE_WRITE_SECURE_PARAM_ID,
                                   isBlocking, TMECOM_DEFAULT_TIMEOUT,
                                   msg, sizeof(*msg),
                                   tmecomCBApi /*cbApi*/, cbData /*userData*/);

  ret = convertToTmeError(tmecomRet);

exit:
  if (!isBlocking) {
    if (TME_SUCCESS != ret) {
      /* Free allocated memory in case of failure,
         In case of sucess it will be freed inside tmecomCallback API */
      if(cbData)
      {
        TmecomOsMemFree((void **)&cbData);
      }

      if(msg)
      {
        TmecomOsMemFree((void **)&msg);
      }
    }
  } else {
    if ( (TME_SUCCESS == ret) && (TME_SUCCESS != msg->status) ) {
      ret = msg->status; 
    }

    if(msg)
    {
      TmecomOsMemFree((void **)&msg);
    }
  }

  return ret;
}

