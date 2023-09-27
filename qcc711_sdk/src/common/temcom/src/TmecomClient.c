/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================

                    TME COM Client API Source File

=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
//#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "stringl.h"

#include "Tmecom.h"
#include "TmeMessagesUids.h"
#include "TmecomClient.h"
#include "glink.h"

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
/*----------------------------------------------------------------------------
 * Rx states.
 * -------------------------------------------------------------------------*/
typedef enum {
    TMECOM_RX_NONE = 0,
    TMECOM_RX_PENDING = 1,
    TMECOM_RX_IN_PROGRESS = 2,
    TMECOM_RX_DONE = 3,
    TMECOM_RX_MAX = 0xFFFFFFFF,
} TmecomRxState_t;

/*----------------------------------------------------------------------------
 * Tx states.
 * -------------------------------------------------------------------------*/
typedef enum {
    TMECOM_TX_NONE = 0,
    TMECOM_TX_ABORT = 1,
    TMECOM_TX_DONE = 2,
    TMECOM_TX_IN_PROGRESS = 3,
    TMECOM_TX_MAX = 0xFFFFFFFF,
} TmecomTxState_t;

/*----------------------------------------------------------------------------
 * User call back APIs and data.
 * -------------------------------------------------------------------------*/
typedef struct {
    pTmecomNotifyRxCallBack cbAfterRx;
    TmecomCallbackData_t cbData;
    uint32_t paramID;
} TmecomUserCbData_t;

/*----------------------------------------------------------------------------
 * Client context in which the channel is getting created.
 * -------------------------------------------------------------------------*/
typedef struct {
    const TmecomGlinkCfg_t *cfg;
    glink_handle_type chHandle;
    bool tmecomBlocking;
    bool linkUp;
    bool sessionStarted;
    glink_link_id_type linkId;
    glink_channel_event_type glinkState;
    TmecomTxState_t txState;
    TmecomRxState_t rxState;
    TmecomResponse_t remoteRsp;
    TmecomResponse_t errStatus;
    TmecomUserCbData_t userData;
} TmecomGlinkCtx_t;

/*=============================================================================
                       GLOBAL DATA DECLARATIONS
=============================================================================*/

static TmecomGlinkCtx_t glinkCtx;

static TmecomMboxIpcPkt_t gIpcMailbox;
static uint32_t *gSramPayloadDataMalloc = NULL;
static uint32_t *gSramPayloadData = NULL;
static volatile uint32_t gTmecomLock;

/* default max time (microseconds) TMECOM should wait for response from TME */
/* For debugging set this to 0 */
uint32_t gIpcWaitTimeout = TMECOM_DEFAULT_TIMEOUT_US;

/*=============================================================================
                     LOCAL FUNCTION DECLARATIONS
=============================================================================*/

static TmecomResponse_t TmecomChannelOpen(TmecomGlinkCtx_t *ctx);

/*=============================================================================

                     LOCAL FUNCTION DEFINITIONS

=============================================================================*/
/**
 * @brief Get default timeout value.
 */
uint32_t TmecomClientGetTimeout(void) { return gIpcWaitTimeout; }

/**
   @brief Parse paramID and populate sramBufList variable with all srambuffers of given param type.

   @param[in]  paramID          Describe no. of parameter & there types in genericPayLoad.
   @param[in]  payload          Reference to a genericPayLoad. Payload can have 0 to 14 parameter.
                                Each parameter is 4Byte(fixed size).
   @param[in]  inParamType      Type of param, SRAM buffers of this type will be returned.
   @param[out] sramBufList      Pointer to buffer list which will be populated with SRAM addresses
                                and corresponding length. List is assumed to be large enough to hold
                                required number of buffer entries.
   @param[out] listOutSize      Number of SRAM buffer entries populated into srambufList.

   @return A response of type TmecomResponse_t.

*/
static TmecomResponse_t TmecomClientGetBuffList(uint32_t paramID,
                                                const uint32_t *payload,
                                                uint32_t inParamType,
                                                TmecomSramBuf_t *sramBufList,
                                                size_t *listOutSize)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    size_t nArgs = 0;
    size_t paramIdx = 0;
    uint32_t paramType = 0;
    uint32_t numBufs = 0;

    nArgs = TME_MSG_PARAM_ID_GET_NARGS(paramID);
    CHECK_COND_ERR((nArgs > TMECOM_MAX_PARAM_IN_PARAM_ID), TMECOM_RSP_FAILURE_INVALID_ARGS);

    for(size_t i=0; i<nArgs; ++i)
    {
        paramType = TME_MSG_PARAM_ID_GET_PARAM_TYPEi(paramID, i);

        /* TME_MSG_PARAM_TYPE_BUF_OUT and TME_MSG_PARAM_TYPE_BUF_IN_OUT are similar handle as a one type */
        paramType = ((paramType == TME_MSG_PARAM_TYPE_BUF_OUT) ? TME_MSG_PARAM_TYPE_BUF_IN_OUT : paramType);

        if(paramType == inParamType)
        {
            sramBufList[numBufs].addr = (uint8_t *)payload[paramIdx];
            sramBufList[numBufs++].size = payload[paramIdx+1];
        }
        switch(paramType) {
            case TME_MSG_PARAM_TYPE_BUF_IN:
                paramIdx+=2; //buf, bufLen
                break;
            case TME_MSG_PARAM_TYPE_BUF_IN_OUT:
                paramIdx+=3; //buf, bufLen, bufOutLen
                break;
            case TME_MSG_PARAM_TYPE_VAL:
                paramIdx++; //value
                break;
            default: break;
        }
    }
exit:
    *listOutSize = numBufs;
    return result;
}


/**
   @brief Parse paramID and validate each parameter passed.
          If require share buffer addresses with TME with appropriate access permissions.

   @param[in] tmeMsgParamID     Describe no. of parameter & there types in genericPayLoad.
   @param[in] payload           Reference to a genericPayLoad. Payload can have 0 to 14 parameter.
                                Each parameter is 4Byte(fixed size).
   @param[in] payloadLen        Byte length of genericPayLoad.
   @param[in] ipcComplete       To differentite whether this is API is called before or after
                                IPC message is send to TME. In exit path we should revoke
                                RAM access permissions given to the TME.

   @return A response of type TmecomResponse_t.

   NOTE: OS specific RAM share API may not take care of retaining previously shared state of a block.
         To prevent change of permissions if IN and OUT params fall into same block, make RO call
         first for IN params and then RW call for OUT params. While revoking permissions all params
         can be unshared at once.
*/
static TmecomResponse_t TmecomClientPrepareParams(uint32_t paramID,
                                                  const uint32_t *payload,
                                                  size_t payloadLen,
                                                  bool ipcComplete)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    TmecomSramBuf_t sramBufList[TMECOM_MAX_PARAM_IN_PARAM_ID];
    size_t numBufs = 0;
    size_t totalSramBufs = 0;

    memset(sramBufList, 0, sizeof(sramBufList));
    if(!ipcComplete)
    {
        /* Get list of IN param sram buffers */
        CALL_N_CHECK(TmecomClientGetBuffList(paramID, payload, TME_MSG_PARAM_TYPE_BUF_IN, &sramBufList[0], &numBufs));

        /* Share IN param type SRAM buffers first with TME */
        if(numBufs)
            CALL_N_CHECK(TmecomOsShareMemoryWithTme(sramBufList, numBufs, TMECOM_MEM_PERM_READ_ONLY));

        /* Get list of OUT/IN_OUT param sram buffers */
        CALL_N_CHECK(TmecomClientGetBuffList(paramID, payload, TME_MSG_PARAM_TYPE_BUF_IN_OUT, &sramBufList[0], &numBufs));

        /* Now share OUT/IN_OUT param type SRAM buffers with TME */
        if(numBufs)
            CALL_N_CHECK(TmecomOsShareMemoryWithTme(sramBufList, numBufs, TMECOM_MEM_PERM_READ_WRITE));
    }
    else
    {
        /* Get list of IN param sram buffers first */
        CALL_N_CHECK(TmecomClientGetBuffList(paramID, payload, TME_MSG_PARAM_TYPE_BUF_IN, &sramBufList[0], &numBufs));

        totalSramBufs = numBufs;

        /* Now get list of OUT/IN_OUT param sram buffers and append to prvious IN param list */
        CALL_N_CHECK(TmecomClientGetBuffList(paramID, payload, TME_MSG_PARAM_TYPE_BUF_IN_OUT, &sramBufList[numBufs], &numBufs));

        totalSramBufs += numBufs;
        CHECK_COND_ERR((totalSramBufs > TMECOM_MAX_PARAM_IN_PARAM_ID), TMECOM_RSP_FAILURE_INVALID_ARGS);

        /* Revoke SRAM buffer access permissions given to TME */
        if(totalSramBufs)
            CALL_N_CHECK(TmecomOsShareMemoryWithTme(sramBufList, totalSramBufs, TMECOM_MEM_PERM_NO_ACCESS));
    }
exit:
    return result;
}

/*----------------------------------------------------------------------------
 * Helper callback functions.
 * -------------------------------------------------------------------------*/

/**
   @brief Checks if underlying link with TME is connected or not.

   @param[in] ctx        Tmecomclient's glink context

   @return True if link is connected wlse False.
 */
bool isServerConnected(TmecomGlinkCtx_t *ctx)
{

    if (!ctx)
        return false;

    if (!(ctx->linkUp))
        return false;

    if (!(ctx->chHandle))
        return false;

    if (ctx->glinkState != GLINK_CONNECTED)
        return false;

    return true;
}

/**
   @brief Callbck API to call when there is a message in mailbox.
          If it's not a blocking call, then reads IPC message status and calls the
          callback function with status and user data.

   @param[in] handle        glink handle
   @param[in] priv          private pointer passed to glink core
   @param[in] pktPriv       per packet private data
   @param[in] ptr           pointer to received data
   @param[in] size          size of data received
   @param[in] intentsUsed   size of the mailbox

   @return None.
 */

static void TmecomNotifyRx(glink_handle_type handle, const void *priv,
                      const void *pktPriv, const void *ptr, size_t size,
                      size_t intentsUsed)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    TmecomUserCbData_t outUserData = {0};
    pTmecomNotifyRxCallBack sendRspCb = NULL;
    TmecomResponse_t tmeRsp = TMECOM_RSP_FAILURE;
    TmecomIpcHeader_t *msgHdr = &(gIpcMailbox.msgHdr);
    TmecomMboxIpcPayload_t *ipcPayload = &(gIpcMailbox.payload);
    TmecomIpc_t ipcType = TMECOM_IPC_TYPE_MBOX_ONLY;
    TmecomSramBuf_t sramPayloadBuf;
    size_t userPayloadLen = 0;
    void *userPayload = NULL;
    void *payloadData = NULL;

    CHECK_PTR(ptr);
    memset(&sramPayloadBuf, 0, sizeof(TmecomSramBuf_t));

    memscpy(&outUserData, sizeof(outUserData), &glinkCtx.userData, sizeof(glinkCtx.userData));
    userPayload = outUserData.cbData.genericPayload;
    userPayloadLen = outUserData.cbData.genericPayloadLen;
    CHECK_PTR(userPayload);
    
    /* Copy mailbox data locally */
    memscpy(&gIpcMailbox, sizeof(TmecomMboxIpcPkt_t), ptr, size);
    
    /* Extract response from message data. */
    glinkCtx.remoteRsp = (TmecomResponse_t)(msgHdr->response);
    tmeRsp = glinkCtx.remoteRsp;

    ipcType = (TmecomIpc_t)msgHdr->ipcType;

    /* Copy back generic payload from mailbox */
    if (TMECOM_IPC_TYPE_MBOX_ONLY == ipcType) {
        payloadData = &(ipcPayload->mailboxPayload.param);
        memscpy(userPayload, userPayloadLen, payloadData, sizeof(TmecomMboxIpcPkt_t));
    }
    else if(TMECOM_IPC_TYPE_MBOX_SRAM == ipcType) {
        payloadData = ipcPayload->sramPayload.payloadPtr;
        CHECK_PTR(payloadData);
        memscpy(userPayload, userPayloadLen, payloadData, TMECOM_SRAM_IPC_MAX_BUF_SIZE);
    }

    /* Set global rx state to RX_IN_PROGRESS. */
    glinkCtx.rxState = TMECOM_RX_IN_PROGRESS;

    /* Call rx_done, Set global rx_state to RX_DONE */
    glink_rx_done(glinkCtx.chHandle, ptr, false);
    glinkCtx.rxState = TMECOM_RX_DONE;

    if (!glinkCtx.tmecomBlocking) {
        /* Revoke the access permissions given to TME for use-case SRAM buffers */
        CALL_N_CHECK(TmecomClientPrepareParams(outUserData.paramID, userPayload,
                     userPayloadLen, true), "Param Validation failed");
        if(TMECOM_IPC_TYPE_MBOX_SRAM == ipcType)
        {
            /* Revoke sramPayloadBuf access given to TME */
            sramPayloadBuf.addr = (uint8_t *)gSramPayloadData;
            sramPayloadBuf.size = TMECOM_SRAM_IPC_MAX_BUF_SIZE;
            CALL_N_CHECK(TmecomOsShareMemoryWithTme(&sramPayloadBuf, 1, TMECOM_MEM_PERM_NO_ACCESS));
        }
        sendRspCb = outUserData.cbAfterRx;
        CHECK_PTR(sendRspCb);

        /* Inform caller about IPC completion by calling user passed call back API */
        sendRspCb(tmeRsp, &outUserData.cbData);

        glinkCtx.errStatus = result;

        /** Release lock*/
        TmecomOsFreeLock(&gTmecomLock);

        return; 
    }

exit:
    if (!glinkCtx.tmecomBlocking && sendRspCb) {

        /* Error case, return tmecom error to non-blocking call back API */
        sendRspCb(result, &outUserData.cbData);

        /** Error case, release lock */
        TmecomOsFreeLock(&gTmecomLock);
    }

    glinkCtx.errStatus = result;

    return;
}

/**
  @brief Notification callback for TX completed from glink core.

  @param[in] handle        glink handle
  @param[in] priv          private pointer passed to glink core
  @param[in] pktpriv       per packet private data
  @param[in] ptr           pointer to received data
  @param[in] size          size of data received

  @return None
**/

static void TmecomNotifyTxDone(glink_handle_type handle, const void *priv,
                           const void *pktPriv, const void *ptr, size_t size)
{
    TMECOM_UNUSED(handle);
    TMECOM_UNUSED(priv);
    TMECOM_UNUSED(pktPriv);
    TMECOM_UNUSED(ptr);
    TMECOM_UNUSED(size);

    /* Set global tx state to TX_DONE. */
    glinkCtx.txState = TMECOM_TX_DONE;
}

/**
  @brief Notification callback for TX abort from glink core.

  @param[in] handle        glink handle
  @param[in] priv          private pointer passed to glink core
  @param[in] pktPriv       per packet private data

  @return None
**/

static void TmecomNotifyTxAbort(glink_handle_type handle, const void *priv,
                            const void *pktPriv)
{
    TMECOM_UNUSED(handle);
    TMECOM_UNUSED(priv);
    TMECOM_UNUSED(pktPriv);

    /* Ongoing transmission has been aborted, set gloal tx state to TX_ABORT. */
    glinkCtx.txState = TMECOM_TX_ABORT;
}

/**
  @brief Notification callback when channel state changes.
         Need to update the glinkstate based on the event types.

  @param[in] handle        glink handle
  @param[in] priv          private pointer passed to glink core
  @param[in] event         new state of channel

  @return None
**/
static void TmecomNotifyChannelStateIsr(glink_handle_type handle, const void *priv,
                                  glink_channel_event_type event)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    TmecomGlinkCtx_t *ctx = (TmecomGlinkCtx_t *)priv;

    TMECOM_UNUSED(handle);

    CHECK_PTR(ctx);
    switch (event) {
    case GLINK_LOCAL_DISCONNECTED: {
        ctx->chHandle = NULL;
        ctx->glinkState = GLINK_LOCAL_DISCONNECTED;
        break;
    }

    case GLINK_CONNECTED: {
        ctx->glinkState = GLINK_CONNECTED;
        break;
    }

    case GLINK_REMOTE_DISCONNECTED: {
        ctx->glinkState = GLINK_REMOTE_DISCONNECTED;
        glink_close(ctx->chHandle);
        break;
    }

    default: { break; }
    }

exit:
    TMECOM_UNUSED(result);
    return;
}

/**
  @brief Notification callback when underlying link state changes(UP/DOWN).

  @param[in] linkInfo      Link state info structure
  @param[in] priv          private pointer passed to glink core

  @return None
**/
static void TmecomNotifyLinkStateIsr(glink_link_info_type *linkInfo, void *priv)
{
    TmecomGlinkCtx_t *ctx = (TmecomGlinkCtx_t *)priv;
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;

    CHECK_PTR(ctx);
    CHECK_PTR(linkInfo);
    if (linkInfo->link_state == GLINK_LINK_STATE_UP) {
        TMECOM_LOG_INFO("Link up called. remote:%s.", ctx->cfg->remote);

        CHECK_COND_ERR((ctx->chHandle != NULL), TMECOM_RSP_FAILURE,
                       "Channel is not completely closed!: %p", ctx->chHandle);

        ctx->linkUp = true;

        /*Request for opening the channel.*/
        CALL_N_CHECK(TmecomChannelOpen(ctx), "glink_channel_open failed, result:%d", result);

    } else if (linkInfo->link_state == GLINK_LINK_STATE_DOWN) {
        TMECOM_LOG_ERR("Link down called.");
        ctx->linkUp = false;
    }

exit:
    return;
}

/**
  @brief Open a channel with remote SS.

  @param[in] ctx     Cleint context

  @return TMECOM_RSP_SUCCESS - if channel created successfully.
          FAILURE code incase of any error.
**/
static TmecomResponse_t TmecomChannelOpen(TmecomGlinkCtx_t *ctx)
{
    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    glink_open_config_type chCfg;
    glink_err_type glinkRet = GLINK_STATUS_FAILURE;

    CHECK_PTR(ctx);
    CHECK_PTR(ctx->cfg);

    /* set glink open config parameters */
    chCfg.remote_ss = ctx->cfg->remote;
    chCfg.name = ctx->cfg->channel;
    chCfg.priv = ctx;
    chCfg.notify_state = TmecomNotifyChannelStateIsr;
    chCfg.notify_rx = TmecomNotifyRx;
    chCfg.notify_tx_done = TmecomNotifyTxDone;
    chCfg.notify_tx_abort = TmecomNotifyTxAbort;

    glinkRet = glink_open(&chCfg, &ctx->chHandle);
    if ((glinkRet != GLINK_STATUS_SUCCESS) || (ctx->chHandle == NULL)) {
        TMECOM_LOG_ERR("Channel open failed!  err=%d.", glinkRet);
        result = TMECOM_RSP_FAILURE_CHANNEL_ERR;
        ctx->chHandle = NULL;
    }

exit:
    return result;
}

/**
  @brief Initialize link context and register link state callbacks.

  @return TMECOM_RSP_SUCCESS - if channel created successfully.
          FAILURE code incase of any error.
**/
static TmecomResponse_t TmecomGlinkCtxInit(void)
{

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    glink_err_type glinkRet = GLINK_STATUS_FAILURE;

    glink_init();

    /* Get client glink configuration */
    glinkCtx.cfg = TmecomGetClientCfg();
    CHECK_PTR(glinkCtx.cfg);
    GLINK_LINK_ID_STRUCT_INIT(glinkCtx.linkId);
    glinkCtx.linkId.remote_ss = glinkCtx.cfg->remote;
    glinkCtx.linkId.link_notifier = (glink_link_state_notif_cb)TmecomNotifyLinkStateIsr;

    /* Registers a client specified callback to be invoked when the specified
     * transport (link) is up/down.
     */
    glinkRet = glink_register_link_state_cb(&glinkCtx.linkId, &glinkCtx);

    CHECK_COND_ERR((glinkRet != GLINK_STATUS_SUCCESS), TMECOM_RSP_FAILURE_LINK_ERR,
                    "Link state cb register failed! ret:%d", glinkRet);

    glink_remote_up(glinkCtx.cfg->remote);

exit:
    return result;
}

/*=============================================================================

                     PUBLIC FUNCTION DEFINITIONS

=============================================================================*/

/**
   @brief API to start a TME session.
          This API used for power control, bring TME online if it's
          in shutdown state. Also it establish transport layer link.

   @return A response of type TmecomResponse_t.
 */

TmecomResponse_t TmecomClientSessionStart(void)
{

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    volatile glink_channel_event_type *glinkState;
    uint64_t startTime = 0;
    uint64_t currTime = 0;

    TMECOM_UNUSED(startTime);
    TMECOM_UNUSED(currTime);

    /* IPC supports only one communication with TME at given time,
       TMECOM_RSP_FAILURE_BUSY will be returned to caller if any existing
       IPC communication is going on */

    if(true == glinkCtx.sessionStarted)
    {
        result = TMECOM_RSP_FAILURE_BUSY;
        goto error;
    }

    /* Acquire lock*/
    CALL_N_CHECK(TmecomOsTryLock(&gTmecomLock));

    /* Set TME state to active */
    CALL_N_CHECK(TmecomOsSetTmeState(true));

    glinkCtx.glinkState = GLINK_LOCAL_DISCONNECTED;

    if (glinkCtx.linkUp == false)
    {
        CALL_N_CHECK(TmecomGlinkCtxInit());
    }
    else
    {
        CALL_N_CHECK(TmecomChannelOpen(&glinkCtx));
    }

    /* Wait for Connect or remote disconnect  */
    glinkState = (volatile glink_channel_event_type *)(&glinkCtx.glinkState);
    WAIT_ON_CONDITION_TILL_TIMEOUT((*glinkState == GLINK_LOCAL_DISCONNECTED),
                                   TmecomClientGetTimeout(),
                                   TMECOM_RSP_FAILURE_CHANNEL_CONNECT_ERR_TIMEOUT);

    /* Make sure remote is connected */
    CHECK_COND_ERR((*glinkState == GLINK_REMOTE_DISCONNECTED), TMECOM_RSP_FAILURE_CHANNEL_ERR);

    /* Allocate gSramPayloadData for this session */
    CALL_N_CHECK(TmecomOsMemAlloc((void **)&gSramPayloadDataMalloc, TMECOM_SRAM_IPC_MAX_BUF_SIZE+3));
    gSramPayloadData = (uint32_t *)ALIGN_UP(uintptr_t, gSramPayloadDataMalloc, TMECOM_4_BYTE_ALIGNED);
    CHECK_ALIGNMENT(uintptr_t, gSramPayloadData, TMECOM_4_BYTE_ALIGNED);

    glinkCtx.sessionStarted = true;

exit:
    if(result)
    {
        if(gSramPayloadDataMalloc)
        {
            /** Error occurred revoke SRAM permissions given to TME and free
             * SRAM buffer */
            TmecomOsMemFree((void **)&gSramPayloadDataMalloc);
        }

        /* De-register client callbacks */
        glink_deregister_link_state_cb(glinkCtx.linkId.handle);

        /* Clear global Glink context of this session */
        memset(&glinkCtx, 0, sizeof(glinkCtx));
    }

    if (result != TMECOM_RSP_FAILURE_BUSY)
    {
        /** Release lock */
        TmecomOsFreeLock(&gTmecomLock);
    }

error:

    glinkCtx.errStatus = result;

    return result;
}

/**
   @brief API to end a TME session.
          This PI used for power control, remove the vote placed
          during session start to keep TME Alive.
          It close transport layer link before taking out the vote.
   @return A response of type TmecomResponse_t.
 */

TmecomResponse_t TmecomClientSessionEnd(void)
{

    TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    glink_err_type glinkRet = GLINK_STATUS_FAILURE;
    volatile glink_channel_event_type *glinkState;
    uint64_t startTime = 0;
    uint64_t currTime = 0;

    TMECOM_UNUSED(startTime);
    TMECOM_UNUSED(currTime);

    if(false == glinkCtx.sessionStarted)
    {
        result = TMECOM_RSP_FAILURE;
        goto error;
    }

    /* Acquire lock*/
    CALL_N_CHECK(TmecomOsTryLock(&gTmecomLock));

    glink_remote_down(glinkCtx.cfg->remote);

    /* Wait for GLINK_LOCAL_DISCONNECTED */
    glinkState = (volatile glink_channel_event_type *)(&glinkCtx.glinkState);
    WAIT_ON_CONDITION_TILL_TIMEOUT((*glinkState != GLINK_LOCAL_DISCONNECTED),
                                   TmecomClientGetTimeout(),
                                   TMECOM_RSP_FAILURE_CHANNEL_DISCONNECT_ERR_TIMEOUT);

    /* De-register client callbacks */
    glinkRet = glink_deregister_link_state_cb(glinkCtx.linkId.handle);

    CHECK_COND_ERR((glinkRet != GLINK_STATUS_SUCCESS), TMECOM_RSP_FAILURE_LINK_ERR,
                    "Link state cb de-register failed! ret:%d", glinkRet);


    /* Free gSramPayloadData buffer */
    CALL_N_CHECK(TmecomOsMemFree((void **)&gSramPayloadDataMalloc));

    /* Remove vote on TME  */
    CALL_N_CHECK(TmecomOsSetTmeState(false));

    /* Clear global Glink context of this session */
    memset(&glinkCtx, 0, sizeof(glinkCtx));

    glinkCtx.sessionStarted = false;

exit:

    if (result != TMECOM_RSP_FAILURE_BUSY)
    {
        /** Release lock */
        TmecomOsFreeLock(&gTmecomLock);
    }

    glinkCtx.errStatus = result;    

error:

    return result;
}

/**
   @brief API to send a message to TME used to request a service from TME.
          Verifies if the channle is connected or not.
          Prepares the IPC Packet.
          Performs the actual IPC write transaction for the prepared packet.
          Based On Blocking or non Blocking, decides whether to return or
          process further.

   @param[in] tmeMsgUid         TME request identifier. Defined at TmeMessagesUids.h
                                Consists of messageType(15:8) : actionID(7:0)
   @param[in] tmeMsgParamID     Describe no. of parameter & there types in genericPayLoad.
                                Defined at TmeMessagesUids.h along with Message UID.
                                Consists of paramType's(31:4) : paramCount(3:0)
   @param[in] isBlocking        Client notify if it will wait or continue execution after sending
                                message. If opt for not blocking, response notified with cbApi.
   @param[in] timeout           For a blocking call, client can set max time(microseconds)
                                it can wait for response.
   @param[in] genericPayLoad    Reference to a genericPayLoad. Payload can have 0 to 14 parameter.
                                Each parameter is 4Byte(fixed size).
   @param[in] genericPayLoadLen Byte length of genericPayLoad.
   @param[in] cbApi             Callback function invoked when TME response arrives.
                                Not required if isBlocking=true.
   @param[in] userData          Placeholder for client data. Can be used to pass a context
                                to cbApi if required.

   @return A response of type TmecomResponse_t.
*/

TmecomResponse_t TmecomClientSendMessage(uint32_t tmeMsgUid, uint32_t tmeMsgParamID,
                                bool isBlocking, uint32_t timeout,
                                void *genericPayload,
                                uint32_t genericPayloadLen,
                                pTmecomNotifyRxCallBack cbApi, void *userData)
{

    volatile TmecomResponse_t result = TMECOM_RSP_SUCCESS;
    void *pktPriv = NULL; // context for the packet.
    uint32_t txFlags = 0; /*Don't use glink req intent*/
    uint32_t msgHeaderLen = sizeof(TmecomIpcHeader_t);
    uint64_t startTime = 0;
    uint64_t currTime = 0;
    TmecomUserCbData_t *inUserData = &glinkCtx.userData;
    TmecomIpcHeader_t *msgHdr = &(gIpcMailbox.msgHdr);
    TmecomMboxIpcPayload_t *ipcPayload = &(gIpcMailbox.payload);
    void *payloadData = NULL;
    volatile TmecomTxState_t *txState;
    volatile TmecomRxState_t *rxState;
    TmecomSramBuf_t sramPayloadBuf;

    TMECOM_UNUSED(startTime);
    TMECOM_UNUSED(currTime);

    CHECK_PTR(genericPayload);
    CHECK_SIZE(genericPayloadLen);
    memset(&sramPayloadBuf, 0, sizeof(TmecomSramBuf_t));

    /* Check if the channel is connected or not */
    CHECK_COND_ERR((!isServerConnected(&glinkCtx)), TMECOM_RSP_FAILURE,
                "Channel not available");

    /* For non-blocking calls call back API must be passed */
    CHECK_COND_ERR((!isBlocking && (NULL == cbApi)), TMECOM_RSP_FAILURE_INVALID_ARGS,
                    "cbApi is NULL for blocking IPC call");

    /* Acquire Lock*/
    CALL_N_CHECK(TmecomOsTryLock(&gTmecomLock));

    if (tmeMsgParamID != 0) {
        CALL_N_CHECK(TmecomClientPrepareParams(tmeMsgParamID, genericPayload,
                                               genericPayloadLen, false));
    }

    /*Initialize global state variables.*/
    glinkCtx.txState = TMECOM_TX_NONE;
    glinkCtx.rxState = TMECOM_RX_NONE;
    glinkCtx.errStatus = TMECOM_RSP_SUCCESS;

    /* Set cb_after_rx & cb_user_data */
    inUserData->cbAfterRx = cbApi;
    inUserData->cbData.userData = userData;
    inUserData->cbData.genericPayload = genericPayload;
    inUserData->cbData.genericPayloadLen = genericPayloadLen;
    inUserData->cbData.tmeMsgUid = tmeMsgUid;
    inUserData->paramID = tmeMsgParamID;
    glinkCtx.tmecomBlocking = isBlocking;

    CHECK_PTR(gSramPayloadData);

    /* Clear stale data from IPC packet and SRAM buffer */
    memset(&gIpcMailbox, 0, sizeof(TmecomMboxIpcPkt_t));
    memset(gSramPayloadData, 0, TMECOM_SRAM_IPC_MAX_BUF_SIZE);

    /*Prepare the Mailbox, with proper header and payload */
    if (msgHeaderLen + genericPayloadLen <= TMECOM_MBOX_IPC_PACKET_SIZE) {
        msgHdr->ipcType = TMECOM_IPC_TYPE_MBOX_ONLY;
        msgHdr->msgLen = genericPayloadLen;
        payloadData = &(ipcPayload->mailboxPayload.param);
        memscpy(payloadData, sizeof(TmecomMboxOnlyPayload_t), genericPayload, genericPayloadLen);
    }
    else if( TMECOM_SRAM_IPC_MAX_BUF_SIZE >= genericPayloadLen) {
        msgHdr->ipcType = TMECOM_IPC_TYPE_MBOX_SRAM;
        msgHdr->msgLen = 8;  /* genericPayLoadPtr + genericPayLoadLen */
        ipcPayload->sramPayload.payloadLen = genericPayloadLen;
        ipcPayload->sramPayload.payloadPtr = gSramPayloadData;

        /* Copy genericPayload data into SRAM buffer */
        memscpy(gSramPayloadData, TMECOM_SRAM_IPC_MAX_BUF_SIZE, genericPayload, genericPayloadLen);

        /* Share SramPayload Buffer  with TME */
        sramPayloadBuf.addr = (uint8_t *)gSramPayloadData;
        sramPayloadBuf.size = TMECOM_SRAM_IPC_MAX_BUF_SIZE;
        CALL_N_CHECK(TmecomOsShareMemoryWithTme(&sramPayloadBuf, 1, TMECOM_MEM_PERM_READ_WRITE));
    }
    else {
        CHECK_COND_ERR(true, TMECOM_RSP_FAILURE_INVALID_ARGS, "Invalid Payload length, genericPayloadLen %d", genericPayloadLen);
    }

    msgHdr->msgType = TME_MSG_UID_MSG_TYPE(tmeMsgUid);
    msgHdr->actionId = TME_MSG_UID_ACTION_ID(tmeMsgUid);

    /*Perform the IPC transaction*/
    glinkCtx.txState = TMECOM_TX_IN_PROGRESS;
    result = (TmecomResponse_t)glink_tx(glinkCtx.chHandle, pktPriv,
                                        &gIpcMailbox, sizeof(TmecomMboxIpcPkt_t), txFlags);
    CHECK_COND_ERR((result != (TmecomResponse_t)GLINK_STATUS_SUCCESS), TMECOM_RSP_FAILURE_TX_ERR, "glink_tx failed!");

    /* wait for the tx_done event and Poll on glinkCtx.tx_state variable. */
    txState = (volatile TmecomTxState_t*)(&glinkCtx.txState);
    WAIT_ON_CONDITION_TILL_TIMEOUT((*txState == TMECOM_TX_IN_PROGRESS),
                                   TmecomClientGetTimeout(),
                                   TMECOM_RSP_FAILURE_TX_DONE_TIMEOUT);

    if (glinkCtx.txState != TMECOM_TX_DONE)
    {
        result = TMECOM_RSP_FAILURE_TX_FAILED;
        goto exit;
    }

    if (isBlocking) {
        /* Wait till receiver is processing msg */
        rxState = (volatile TmecomRxState_t*)(&glinkCtx.rxState);
        if ( 0 == timeout)
        {
            timeout = TmecomClientGetTimeout();
        }

        WAIT_ON_CONDITION_TILL_TIMEOUT((*rxState != TMECOM_RX_DONE), timeout,
                TMECOM_RSP_FAILURE_RX_DONE_TIMEOUT);

        /* Revoke SRAM buffer permissions given to TME */
        CALL_N_CHECK(TmecomClientPrepareParams(tmeMsgParamID, genericPayload,
                                               genericPayloadLen, true));

        /* Revoke sramPayloadBuf access given to TME */
        if(TMECOM_IPC_TYPE_MBOX_SRAM == msgHdr->ipcType)
        {
            CALL_N_CHECK(TmecomOsShareMemoryWithTme(&sramPayloadBuf, 1, TMECOM_MEM_PERM_NO_ACCESS));
        }

        /* For blocking call return response received from remote,
           which rx_notify would have filled */
        result = glinkCtx.remoteRsp;
        TMECOM_LOG_INFO("Response received from TME: %d", result);

        /* Release lock*/
        TmecomOsFreeLock(&gTmecomLock);
    }

exit:
    if(result && (result != TMECOM_RSP_FAILURE_BUSY)) {
        /* Error case release lock */
        TmecomOsFreeLock(&gTmecomLock);
    }

    glinkCtx.errStatus = result;

    return result;
}

/**
   @brief API to check if TMECOM is busy in prcessing any IPC request.
          If any IPC request is going on then this API will return busy error,
          else if TMECOM is free to handle a new IPC request then will return success.

   @return TMECOM_RSP_SUCCESS if TMEOCM is free and new IPC request can be posted.
           TMECOM_RSP_FAILURE_BUSY if already there is an IPC request in transit.
*/
TmecomResponse_t IsTmecomClientBusy(void)
{
    /* check state of lock and return appropriate error */
    return TmecomOsIsLockFree(&gTmecomLock);
}
