/*
 * Copyright (c) 2020-2021, 2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*=============================================================================

                    GLink API Source File

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
=============================================================================*/

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "glink.h"
#include "glink_os_utils.h"
#include "glink_internal.h"
#include "xport_qmp.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/
glink_os_cs_type        glink_cmn_cs;
glink_transport_if_type *glink_transports[GLINK_CFG_MAX_REMOTE_HOSTS];
glink_link_notify_type  glink_link_notifies[GLINK_CFG_MAX_NOTIFY_CBS];

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*=============================================================================
                     LOCAL FUNCTION DECLARATIONS
=============================================================================*/

/*=============================================================================

                     LOCAL FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
FUNCTION      glinki_find_xport_if_by_name
=============================================================================*/
/**
*/
/*===========================================================================*/
glink_transport_intf_type *glinki_find_xport_by_name(const char *remote_ss)
{
  glink_transport_if_type *if_ptr = NULL;
  uint32                  indx;

  GLINK_OS_LOG_DBG("glinki_find_xport_by_name enter input:%s.", remote_ss, 0);

  glink_os_cs_acquire(&glink_cmn_cs);

  for (indx = 0;
       (indx < GLINK_CFG_MAX_REMOTE_HOSTS) && glink_transports[indx] != NULL;
       indx++)
  {
      GLINK_OS_LOG_DBG("glinki_find_xport_by_name input:%s, curr:%s", remote_ss, glink_transports[indx]->remote_ss);

    if (glink_os_strcmp(glink_transports[indx]->remote_ss, remote_ss) == 0)
    {
      if_ptr = glink_transports[indx];
      break;
    }
  }

  glink_os_cs_release(&glink_cmn_cs);

  GLINK_OS_LOG_DBG("glinki_find_xport_by_name exit input:%s, if_ptr:0x%X.", remote_ss, if_ptr);

  return if_ptr;
}

/*=============================================================================
FUNCTION      glink_link_state_notify
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_link_state_notify
(
  const char            *remote_ss,
  glink_link_state_type link_state
)
{
  glink_link_notify_type *link;
  glink_link_info_type   link_info;
  uint32                 indx;

  glink_os_cs_acquire(&glink_cmn_cs);

  link_info.remote_ss  = remote_ss;
  link_info.link_state = link_state;

  for (indx = 0; indx < GLINK_CFG_MAX_NOTIFY_CBS; indx++)
  {
    link = &glink_link_notifies[indx];
    if ((link->link_notifier == NULL) || (link->link_state == link_state))
    {
      continue;
    }

    if ((link->remote_ss == NULL) ||
        (!glink_os_strcmp(link->remote_ss, remote_ss)))
    {
      glink_link_state_notif_cb notif_cb = link->link_notifier;
      void *notif_cb_priv = link->priv;

      link->link_state = link_state;

      /* Release the lock before calling client callback */
      glink_os_cs_release(&glink_cmn_cs);

      /* Notify client */
      notif_cb(&link_info, notif_cb_priv);

      /* Acquire lock again to process remaining notif_cb */
      glink_os_cs_acquire(&glink_cmn_cs);
    }
  }

  glink_os_cs_release(&glink_cmn_cs);
}

/*=============================================================================
FUNCTION      glink_rx_cmd_remote_close
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_rx_cmd_remote_close
(
  glink_core_xport_ctx_type *core_priv,
  glink_channel_ctx_type    *ch_ctx
)
{
  glink_state_notification_cb state_cb = NULL;
  glink_notify_tx_abort_cb    tx_abort_cb = NULL;
  const void                  *ch_priv = NULL;
  const void                  *pkt_priv = NULL;

  glink_os_cs_acquire(&core_priv->cs);

  if (ch_ctx->if_ptr == NULL)
  {
    glink_os_cs_release(&core_priv->cs);
    return;
  }

  ch_priv  = ch_ctx->priv;
  state_cb = ch_ctx->notify_state;

  if (ch_ctx->tx_pkt.data != NULL)
  {
    ch_ctx->tx_pkt.data = NULL;

    tx_abort_cb = ch_ctx->notify_tx_abort;
    pkt_priv    = ch_ctx->tx_pkt.pkt_priv;
  }

  glink_os_cs_release(&core_priv->cs);

  if (tx_abort_cb)
  {
    tx_abort_cb(ch_ctx, ch_priv, pkt_priv);
  }
  if (state_cb)
  {
    state_cb(ch_ctx, ch_priv, GLINK_REMOTE_DISCONNECTED);
  }
}

/*=============================================================================

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
FUNCTION      glink_init
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_init(void)
{
  static boolean glink_init_state = FALSE;

  if (glink_init_state != FALSE)
  {
    return;
  }
  glink_init_state = TRUE;

  glink_os_init();

  glink_os_cs_init(&glink_cmn_cs);
  
  xport_qmp_init();
}

/*=============================================================================
FUNCTION      glink_open
=============================================================================*/
/**
 * Opens a logical GLink based on the specified config params
 *
 * @param[in]    cfg_ptr  Pointer to the configuration structure for the
 *                        GLink. See glink.h
 * @param[out]   handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Allocates channel resources and informs remote host about
 *               channel open.
*/
/*===========================================================================*/
glink_err_type glink_open
(
  const glink_open_config_type *cfg_ptr,
  glink_handle_type            *handle
)
{
  glink_transport_if_type   *if_ptr;
  glink_core_xport_ctx_type *core_priv;
  glink_channel_ctx_type    *ch_ctx;
  glink_err_type            status = GLINK_STATUS_SUCCESS;

  GLINK_OS_LOG_DBG("glink_open enter cfg_ptr:0x%08X", cfg_ptr, 0);
  /* Param validation */
  if ((cfg_ptr == NULL) || (cfg_ptr->remote_ss == NULL) || /* TODO: Check channel name */
      (cfg_ptr->name == NULL) || (cfg_ptr->notify_state == NULL))
  {
    GLINK_OS_LOG_ERR("glink_open GLINK_STATUS_INVALID_PARAM.", 0, 0);
    return GLINK_STATUS_INVALID_PARAM;
  }
  GLINK_OS_LOG_DBG("glink_open ch%s, remote:%s.", cfg_ptr->name, cfg_ptr->remote_ss);

  /* Find transport */
  if_ptr = glinki_find_xport_by_name(cfg_ptr->remote_ss);
  if (if_ptr == NULL)
  {
    GLINK_OS_LOG_ERR("glink_open ch%s, remote:%s, GLINK_STATUS_NOT_INIT.", cfg_ptr->name, cfg_ptr->remote_ss);
    return GLINK_STATUS_NOT_INIT;
  }

  core_priv = &if_ptr->core_priv;

  glink_os_cs_acquire(&core_priv->cs);

  if (core_priv->status != GLINK_XPORT_LINK_UP)
  {
    GLINK_OS_LOG_ERR("glink_open remote:%s, link_state=%d, GLINK_STATUS_NOT_INIT.", cfg_ptr->remote_ss, core_priv->status);
    status = GLINK_STATUS_NOT_INIT;
    goto UNLOCK_RETURN;
  }

  ch_ctx = &core_priv->ch_ctx;

  /* Support only one channel per transport, check the transport channel */
  if ((ch_ctx->if_ptr != NULL) ||
      (glink_os_strcmp(if_ptr->ch_name, cfg_ptr->name)))
  {
    status = GLINK_STATUS_OUT_OF_RESOURCES;
    GLINK_OS_LOG_ERR("glink_open ch%s, remote:%s, GLINK_STATUS_OUT_OF_RESOURCES.", cfg_ptr->name, cfg_ptr->remote_ss);
    goto UNLOCK_RETURN;
  }

  /* Use channel name from transport as it support one one channel */
  ch_ctx->if_ptr    = if_ptr;
  ch_ctx->ch_name   = if_ptr->ch_name;
  ch_ctx->remote_ss = if_ptr->remote_ss;

  ch_ctx->notify_rx       = cfg_ptr->notify_rx;
  ch_ctx->notify_state    = cfg_ptr->notify_state;
  ch_ctx->notify_tx_done  = cfg_ptr->notify_tx_done;
  ch_ctx->notify_tx_abort = cfg_ptr->notify_tx_abort;
  ch_ctx->priv            = cfg_ptr->priv;

  *handle = ch_ctx;

  status = if_ptr->tx_cmd_ch_open(if_ptr);
  if (status != GLINK_STATUS_SUCCESS)
  {
    /* Clear channel transport if_ptr */
    ch_ctx->if_ptr = NULL;
    *handle        = NULL;
  }

UNLOCK_RETURN:
  glink_os_cs_release(&core_priv->cs);

  GLINK_OS_LOG_DBG("glink_open remote:%s, exit status=%d.", cfg_ptr->remote_ss, status);
  return status;
}

/*=============================================================================
FUNCTION      glink_close
=============================================================================*/
/**
 * Closes the GLink logical channel specified by the handle.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Closes local end of the channel and informs remote host
*/
/*===========================================================================*/
glink_err_type glink_close
(
  glink_handle_type handle
)
{
  glink_channel_ctx_type    *ch_ctx = (glink_channel_ctx_type*)handle;
  glink_core_xport_ctx_type *core_priv;
  glink_transport_if_type   *if_ptr;
  glink_err_type            status;

  if ((ch_ctx == NULL) || (ch_ctx->if_ptr == NULL))
  {
    return GLINK_STATUS_INVALID_PARAM;
  }

  if_ptr    = ch_ctx->if_ptr;
  core_priv = &if_ptr->core_priv;

  glink_os_cs_acquire(&core_priv->cs);

  if (core_priv->status == GLINK_XPORT_LINK_UP)
  {
    status = if_ptr->tx_cmd_ch_close(if_ptr);
    glink_os_cs_release(&core_priv->cs);
  }
  else
  {
    /* Release lock before calling core function, as it already acquire lock */
    glink_os_cs_release(&core_priv->cs);
    glink_core_rx_cmd_ch_close_ack(if_ptr);
    status = GLINK_STATUS_SUCCESS;
  }
  return status;
}

/*=============================================================================
FUNCTION      glink_tx
=============================================================================*/
/**
 * Transmit the provided buffer over GLink.
 *
 * @param[in]    handle    GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv  Per packet private data
 *
 * @param[in]   *data      Pointer to the data buffer to be transmitted
 *
 * @param[in]   size       Size of buffer
 *
 * @param[in]   req_intent Whether to block and request for remote rx intent in
 *                         case it is not available for this pkt tx
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Causes remote host to wake-up and process rx pkt
*/
/*===========================================================================*/
glink_err_type glink_tx
(
  glink_handle_type handle,
  const void        *pkt_priv,
  const void        *data,
  size_t            size,
  uint32            options
)
{
  glink_channel_ctx_type    *ch_ctx = (glink_channel_ctx_type*)handle;
  glink_core_xport_ctx_type *core_priv;
  glink_transport_if_type   *if_ptr;
  glink_core_tx_pkt_type    *tx_pkt;
  glink_err_type            status;


  GLINK_OS_LOG_DBG("glink_tx handle:0x%08X, size:%d.", handle, size);
  GLINK_OS_ARG_NOT_USED(options);

  if ((ch_ctx == NULL) || (ch_ctx->if_ptr == NULL) ||
      (data == NULL) || (size == 0))
  {
    GLINK_OS_LOG_ERR("glink_tx handle:0x%08X, size:%d. GLINK_STATUS_INVALID_PARAM", data, size);
    return GLINK_STATUS_INVALID_PARAM;
  }

  if_ptr    = ch_ctx->if_ptr;
  core_priv = &if_ptr->core_priv;

  glink_os_cs_acquire(&core_priv->cs);

  tx_pkt = &ch_ctx->tx_pkt;

  /* Supports one packet at a time */
  if (tx_pkt->data != NULL)
  {
#if !defined(GLINK_FEATURE_SIMULATOR)
    status = GLINK_STATUS_CH_TX_BUSY;
#else
    status = GLINK_STATUS_SUCCESS;
#endif
  }
  else
  {
    tx_pkt->data           = data;
    tx_pkt->pkt_priv       = pkt_priv;
    tx_pkt->size           = size;
    tx_pkt->size_remaining = size;

    status = if_ptr->tx_data(if_ptr, tx_pkt);
    GLINK_OS_LOG_DBG(" glink_tx tx_data handle:0x%08X, status:%d", handle, status);
    if (status != GLINK_STATUS_SUCCESS)
    {
      tx_pkt->data = NULL;
    }
  }

  glink_os_cs_release(&core_priv->cs);
  GLINK_OS_LOG_DBG("glink_tx exit handle:0x%08X, status:%d", handle, status);
  return status;
}

/*=============================================================================
FUNCTION      glink_rx_done
=============================================================================*/
/**
 * Client uses this to signal to GLink layer that it is done with the received
 * data buffer. This API should be called to free up the receive buffer, which,
 * in zero-copy mode is actually remote-side's transmit buffer.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @param[in]   *ptr      Pointer to the received buffer
 *
 * @param[in]   reuse    Reuse intent. Ignored on micro-cores.
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  GLink XAL frees the Rx buffer
*/
/*===========================================================================*/
glink_err_type glink_rx_done
(
  glink_handle_type handle,
  const void        *ptr,
  boolean           reuse
)
{
  glink_channel_ctx_type    *ch_ctx = (glink_channel_ctx_type*)handle;
  glink_core_xport_ctx_type *core_priv;
  glink_transport_if_type   *if_ptr;
  glink_err_type            status;

  GLINK_OS_ARG_NOT_USED(reuse);

  if ((ch_ctx == NULL) || (ch_ctx->if_ptr == NULL) || (ptr == NULL))
  {
    return GLINK_STATUS_INVALID_PARAM;
  }

  if_ptr    = ch_ctx->if_ptr;
  core_priv = &if_ptr->core_priv;

  glink_os_cs_acquire(&core_priv->cs);

  if (ch_ctx->rx_pkt.data == ptr)
  {
    ch_ctx->rx_pkt.data = NULL;
    status = if_ptr->tx_cmd_local_rx_done(if_ptr, ptr);
  }
  else
  {
    status = GLINK_STATUS_INVALID_PARAM;
  }

  glink_os_cs_release(&core_priv->cs);

  return status;
}

/*=============================================================================
FUNCTION      glink_register_link_state_cb
=============================================================================*/
/**
 * Registers a client specified callback to be invoked when the specified
 * transport (link) is up/down.
 *
 * @param[in]    link_id  Pointer to the configuration structure for the
 *                        xport(link) to be monitored. See glink.h
 * @param[in]    priv     Callback data returned to client when callback
 *                        is invoked.
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Puts the callback in a queue which gets scanned when a
 *               transport(link) comes up OR an SSR happnes.
*/
/*===========================================================================*/
glink_err_type glink_register_link_state_cb
(
  glink_link_id_type *link_id,
  void               *priv
)
{
  glink_link_notify_type  *link;
  glink_link_info_type    link_info;
  uint32                  indx;

  GLINK_OS_LOG_DBG("glink_register_link_state_cb Enter", link_id, priv);

  if ((link_id == NULL) || (link_id->link_notifier == NULL))
  {
    GLINK_OS_LOG_ERR("glink_register_link_state_cb GLINK_STATUS_INVALID_PARAM link_id:0x%08X", link_id, 0);
    return GLINK_STATUS_INVALID_PARAM;
  }

  GLINK_OS_LOG_DBG("glink_register_link_state_cb remote:%s, priv:0x%08X", link_id->remote_ss, priv);

  link_id->handle = NULL;

  glink_os_cs_acquire(&glink_cmn_cs);

  for (indx = 0; indx < GLINK_CFG_MAX_NOTIFY_CBS; indx++)
  {
    link = &glink_link_notifies[indx];
    if (link->link_notifier == NULL)
    {
      link->remote_ss     = link_id->remote_ss;
      link->link_notifier = link_id->link_notifier;
      link->priv          = priv;
      link->link_state    = GLINK_LINK_STATE_DOWN;
      link_id->handle     = link;
      break;
    }
  }

  if (link_id->handle == NULL)
  {
    glink_os_cs_release(&glink_cmn_cs);
    GLINK_OS_LOG_ERR("glink_register_link_state_cb remote:%s, GLINK_STATUS_OUT_OF_RESOURCES", 
                      link_id->remote_ss, priv);
    return GLINK_STATUS_OUT_OF_RESOURCES;
  }

  /* Notify the client if link is already up */
  for (indx = 0; indx < GLINK_CFG_MAX_REMOTE_HOSTS; indx++)
  {
        glink_transport_if_type *if_ptr;
        glink_transport_status_type status;

    if_ptr = glink_transports[indx];

    if (if_ptr == NULL)
    {
      continue;
    }

        glink_os_cs_acquire(&if_ptr->core_priv.cs);
        status = if_ptr->core_priv.status;
    glink_os_cs_release(&if_ptr->core_priv.cs);
        if (status != GLINK_XPORT_LINK_UP)
    {
      continue;
    }

    if ((link_id->remote_ss == NULL) ||
        (!glink_os_strcmp(link_id->remote_ss, if_ptr->remote_ss)))
    {
      link_info.remote_ss  = if_ptr->remote_ss;
      link_info.link_state = GLINK_LINK_STATE_UP;

      link->link_state = GLINK_LINK_STATE_UP;

      /* Release the lock before calling client callback */
      glink_os_cs_release(&glink_cmn_cs);

      /* Notify client */
      link_id->link_notifier(&link_info, priv);

      /* Acquire lock again to process remaining notif_cb */
      glink_os_cs_acquire(&glink_cmn_cs);
    }
  }

  glink_os_cs_release(&glink_cmn_cs);

  GLINK_OS_LOG_DBG("glink_register_link_state_cb remote:%s, GLINK_STATUS_SUCCESS", link_id->remote_ss, 0);
  return GLINK_STATUS_SUCCESS;
}

/*=============================================================================
FUNCTION      glink_deregister_link_state_cb
=============================================================================*/
/**
 * Deregister the link UP/DOWN notification callback associated with the
 * provided handle.
 *
 * @param[in]    handle  Callback handler returned by
 *                       glink_register_link_state_cb
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Removes the callback in a queue which gets scanned when a
 *               transport(link) comes up OR an SSR happnes.
*/
/*===========================================================================*/
glink_err_type glink_deregister_link_state_cb
(
  glink_link_handle_type handle
)
{
  glink_link_notify_type *link = (glink_link_notify_type*)handle;

  if ((link == NULL) || (link->link_notifier == NULL))
  {
    return GLINK_STATUS_INVALID_PARAM;
  }

  glink_os_cs_acquire(&glink_cmn_cs);

  link->link_notifier = NULL;

  glink_os_cs_release(&glink_cmn_cs);

  return GLINK_STATUS_SUCCESS;
}

/*=============================================================================

                     CORE FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
FUNCTION      glink_core_register_transport
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_register_transport(glink_transport_if_type *if_ptr)
{
  uint32 indx;

  glink_os_cs_acquire(&glink_cmn_cs);

  for (indx = 0; indx < GLINK_CFG_MAX_REMOTE_HOSTS; indx++)
  {
    if (glink_transports[indx] == NULL)
    {
      break;
    }
  }

  if (indx == GLINK_CFG_MAX_REMOTE_HOSTS)
  {
    GLINK_OS_LOG_FATAL("Transports exhausted %d", indx, 0);
  }
  else
  {
    glink_transports[indx] = if_ptr;
  }

  glink_os_cs_init(&if_ptr->core_priv.cs);

  glink_os_cs_release(&glink_cmn_cs);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_link_up
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_link_up(glink_transport_if_type *if_ptr)
{
  glink_core_xport_ctx_type *core_priv = &if_ptr->core_priv;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_link_up entry if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);

  glink_os_cs_acquire(&core_priv->cs);

  /* Update the link status */
  core_priv->status = GLINK_XPORT_LINK_UP;

  glink_os_cs_release(&core_priv->cs);

  /* Notify the clients */
  glink_link_state_notify(if_ptr->remote_ss, GLINK_LINK_STATE_UP);

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_link_up exit if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_link_down
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_link_down(glink_transport_if_type *if_ptr)
{
  glink_core_xport_ctx_type *core_priv = &if_ptr->core_priv;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_link_down entry if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
  glink_os_cs_acquire(&core_priv->cs);

  /* Update the link status */
  core_priv->status = GLINK_XPORT_LINK_DOWN;

  glink_os_cs_release(&core_priv->cs);

  /* Notify the clients */
  glink_link_state_notify(if_ptr->remote_ss, GLINK_LINK_STATE_DOWN);

  /* Remote close the channel */
  glink_rx_cmd_remote_close(core_priv, &core_priv->ch_ctx);
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_link_down exit if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_remote_open
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_remote_open(glink_transport_if_type *if_ptr)
{
  glink_core_xport_ctx_type   *core_priv = &if_ptr->core_priv;
  glink_channel_ctx_type      *ch_ctx = &core_priv->ch_ctx;
  glink_state_notification_cb state_cb = NULL;
  const void                  *ch_priv = NULL;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_remote_open entry if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
  glink_os_cs_acquire(&core_priv->cs);

  if (ch_ctx->if_ptr != NULL)
  {
    state_cb = ch_ctx->notify_state;
    ch_priv  = ch_ctx->priv;
  }

  glink_os_cs_release(&core_priv->cs);

  if (state_cb)
  {
    state_cb(ch_ctx, ch_priv, GLINK_CONNECTED);
  }
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_remote_open exit state_cb:0x%08X, remote_ss:%s", state_cb, if_ptr->remote_ss);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_remote_close
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_remote_close(glink_transport_if_type *if_ptr)
{
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_remote_close entry if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
  glink_rx_cmd_remote_close(&if_ptr->core_priv, &if_ptr->core_priv.ch_ctx);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_ch_close_ack
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_ch_close_ack(glink_transport_if_type *if_ptr)
{
  glink_core_xport_ctx_type   *core_priv = &if_ptr->core_priv;
  glink_channel_ctx_type      *ch_ctx = &core_priv->ch_ctx;
  glink_state_notification_cb state_cb = NULL;
  const void                  *ch_priv = NULL;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_ch_close_ack entry if_ptr:0x%08X, remote_ss:%s", if_ptr, if_ptr->remote_ss);
  glink_os_cs_acquire(&core_priv->cs);

  if (ch_ctx->if_ptr != NULL)
  {
    state_cb = ch_ctx->notify_state;
    ch_priv  = ch_ctx->priv;

    ch_ctx->if_ptr = NULL;
  }

  glink_os_cs_release(&core_priv->cs);

  if (state_cb)
  {
    state_cb(ch_ctx, ch_priv, GLINK_LOCAL_DISCONNECTED);
  }
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_ch_close_ack exit state_cb:0x%08X, remote_ss:%s", state_cb, if_ptr->remote_ss);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_tx_done
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_tx_done
(
  glink_transport_if_type *if_ptr,
  glink_core_tx_pkt_type  *tx_pkt
)
{
  glink_core_xport_ctx_type *core_priv = &if_ptr->core_priv;
  glink_channel_ctx_type    *ch_ctx = &core_priv->ch_ctx;
  glink_tx_notification_cb  tx_done_cb = NULL;
  const void                *ch_priv = NULL;
  const void                *pkt_priv;
  const void                *data;
  uint32                    size;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_tx_done entry if_ptr:0x%08X, tx_pkt:0x%08X", if_ptr, tx_pkt);
  glink_os_cs_acquire(&core_priv->cs);

  if ((ch_ctx->if_ptr == NULL) || (tx_pkt->data == NULL) ||
      (tx_pkt->size_remaining != 0))
  {
    glink_os_cs_release(&core_priv->cs);
    return;
  }

  ch_priv    = ch_ctx->priv;
  tx_done_cb = ch_ctx->notify_tx_done;
  pkt_priv   = tx_pkt->pkt_priv;
  data       = tx_pkt->data;
  size       = tx_pkt->size;

  tx_pkt->data = NULL;

  glink_os_cs_release(&core_priv->cs);

  if (tx_done_cb)
  {
    tx_done_cb(ch_ctx, ch_priv, pkt_priv, data, size);
  }
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_tx_done exit tx_done_cb:0x%08X, size:0x%08X", tx_done_cb, size);
}

/*=============================================================================
FUNCTION      glink_core_rx_cmd_data
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_data
(
  glink_transport_if_type *if_ptr, 
  void                    *ptr, 
  uint32                  size
)
{
  glink_core_xport_ctx_type *core_priv = &if_ptr->core_priv;
  glink_channel_ctx_type    *ch_ctx = &core_priv->ch_ctx;
  glink_rx_notification_cb  rx_cb = NULL;

  GLINK_OS_LOG_DBG("glink_core_rx_cmd_data entry if_ptr:0x%08X, size:0x%08X", if_ptr, size);
  glink_os_cs_acquire(&core_priv->cs);

  if ((ch_ctx->if_ptr == NULL) || (ptr == NULL) || (size == 0))
  {
    glink_os_cs_release(&core_priv->cs);
    return;
  }

  rx_cb   = ch_ctx->notify_rx;

  ch_ctx->rx_pkt.data = ptr;
  ch_ctx->rx_pkt.size = size;

  glink_os_cs_release(&core_priv->cs);

  if (rx_cb)
  {
    rx_cb(ch_ctx, ch_ctx->priv, &ch_ctx->rx_pkt, ptr, size, size);
  }
  GLINK_OS_LOG_DBG("glink_core_rx_cmd_data exit rx_cb:0x%08X, size:0x%08X", rx_cb, size);
}

/*=============================================================================
FUNCTION      glink_remote_down
=============================================================================*/
/**
 * Client should call this when remote SS is going down.
*/
/*===========================================================================*/
void glink_remote_down(const char *remote_ss)
{
  glink_transport_if_type *if_ptr;

  GLINK_OS_LOG_DBG("Glink remote subsystem down:%s.", remote_ss, 0);

  /* Find transport */
  if_ptr = glinki_find_xport_by_name(remote_ss);
  if (if_ptr == NULL)
  {
    GLINK_OS_LOG_ERR("Glink remote subsystem down:%s, no transport registered.", remote_ss, 0);
    return;
  }
  
  /* Inform transport that remote is down */
  if (if_ptr->remote_down)
  {
    if_ptr->remote_down(if_ptr);
  }
  
  glink_core_rx_cmd_link_down(if_ptr);
}


/*=============================================================================
FUNCTION      glink_remote_up
=============================================================================*/
/**
 * Client should call this when remote SS is up.
*/
/*===========================================================================*/
void glink_remote_up(const char *remote_ss)
{
  glink_transport_if_type *if_ptr;

  GLINK_OS_LOG_DBG("Glink remote subsystem up:%s.", remote_ss, 0);

  /* Find transport */
  if_ptr = glinki_find_xport_by_name(remote_ss);
  if (if_ptr == NULL)
  {
    GLINK_OS_LOG_ERR("Glink remote subsystem up:%s, no transport registered.", remote_ss, 0);
    return;
  }
  
  /* Inform transport that remote is up */
  if (if_ptr->remote_up)
  {
    if_ptr->remote_up(if_ptr);
  }
}

