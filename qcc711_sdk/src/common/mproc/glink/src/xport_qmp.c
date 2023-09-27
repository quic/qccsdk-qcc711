/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*=============================================================================

              GLink QMP Transport Source File

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
#include "xport_qmp_config.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/


/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/


/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/
xport_qmp_ctx_type xport_qmp_ctxs[GLINK_CFG_MAX_REMOTE_HOSTS];

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
FUNCTION      xport_qmp_intr_send
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_intr_send(xport_qmp_ctx_type *ctx)
{
  volatile uint32 readback;
  volatile uint32 *shared_local_desc  = (volatile uint32 *)ctx->shared_local_desc;
  uint32 *local_desc  = (uint32 *)&ctx->local_desc;
#ifdef GLINK_OS_LOG
  volatile uint32 *shared_remote_desc = (volatile uint32 *)ctx->shared_remote_desc;
  uint32 *remote_desc = (uint32 *)&ctx->remote_desc;
#endif


  /* local_desc copy to shared local_desc */
  *shared_local_desc = *local_desc;

  readback = *shared_local_desc;

  GLINK_OS_LOG_DBG("INT SEND(%s): State:%d ", ctx->cfg->remote_ss, ctx->state);
  GLINK_OS_LOG_DBG("INT SEND: Local:0x%08X(0x%08X).", *shared_local_desc, *local_desc);
  GLINK_OS_LOG_DBG("INT SEND: Remote:0x%08X(0x%08X).", *shared_remote_desc, *remote_desc);

  glink_os_send_interrupt(ctx->intr);
}

/*=============================================================================
FUNCTION      xport_qmp_mailbox_write
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_mailbox_write
(
  xport_qmp_ctx_type *ctx,
  const uint8        *buf,
  uint32             size
)
{
  uint32 size_remainder    = size % 4;
  uint32 size_rounddown    = size - size_remainder;
  const uint8 *src_ptr     = buf;
  const uint8 *src_ptr_end = src_ptr + size_rounddown;
  volatile uint32 *dst_ptr = ctx->shared_local_mailbox;
  uint32 data;

  /* Write in 32bit increments */
  while (src_ptr < src_ptr_end)
  {
    glink_os_mem_copy(&data, sizeof(uint32), src_ptr, sizeof(uint32));
    *dst_ptr++ = data;
    src_ptr += sizeof(uint32);
  }

  if (size_remainder)
  {
    data = 0;
    glink_os_mem_copy(&data, sizeof(uint32), src_ptr, size_remainder);
    *dst_ptr++ = data;
  }
}

/*=============================================================================
FUNCTION      xport_qmp_mailbox_read
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_mailbox_read
(
  xport_qmp_ctx_type *ctx,
  uint8              *buf,
  uint32              size
)
{
  uint32 size_remainder    = size % 4;
  uint32 size_rounddown    = size - size_remainder;
  volatile uint32 *src_ptr = ctx->shared_remote_mailbox;
  uint8  *dst_ptr          = (uint8 *)buf;
  uint8  *dst_ptr_end      = dst_ptr + size_rounddown;
  uint32 data;

  /* Read in 32bit increments */
  while (dst_ptr < dst_ptr_end)
  {
    data = *src_ptr++;
    glink_os_mem_copy(dst_ptr, sizeof(uint32), &data, sizeof(uint32));
    dst_ptr += sizeof(uint32);
  }

  if (size_remainder)
  {
    data = *src_ptr;
    glink_os_mem_copy(dst_ptr, size_remainder, &data, size_remainder);
  }
}

/*=============================================================================
FUNCTION      xport_qmp_pkt_send
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_pkt_send(xport_qmp_ctx_type *ctx)
{
  glink_core_tx_pkt_type *pkt_ctx = ctx->tx_pkt_ctx;
  uint32                 cur_frag_size;
  uint32                 rem_frags_cnt;

  if (pkt_ctx->size_remaining <= ctx->cfg_local_mailbox_size)
  {
    cur_frag_size = pkt_ctx->size_remaining;
    rem_frags_cnt = 0;
  }
  else
  {
    cur_frag_size  = ctx->cfg_local_mailbox_size;
    rem_frags_cnt  = (pkt_ctx->size_remaining / ctx->cfg_local_mailbox_size) - 1;
    rem_frags_cnt += ((pkt_ctx->size_remaining % ctx->cfg_local_mailbox_size) != 0) ? 1 : 0;
  }

  /* Write to shared payload memory */
  xport_qmp_mailbox_write(ctx, ((uint8 *)(pkt_ctx->data) +
                pkt_ctx->size - pkt_ctx->size_remaining), cur_frag_size);

  /* Decrease the remaining buffer size */
  pkt_ctx->size_remaining -= cur_frag_size;

  /* Update the TX sizes */
  ctx->local_desc.cur_frag_size = cur_frag_size;
  ctx->local_desc.rem_frags_cnt = rem_frags_cnt;

  /* Toggle TX to indicate there is a packet fragment */
  XPORT_QMP_LOCAL_FLAG_TOGGLE(ctx, tx);
}

/*=============================================================================
FUNCTION      xport_qmp_state_ch_flags_clr
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_state_ch_flags_clr(xport_qmp_ctx_type *ctx)
{
  /* Clear channel state flags */
  XPORT_QMP_LOCAL_FLAG_CLR(ctx, ch_state);
  XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, ch_state);

  /* TX and RX flags */
  XPORT_QMP_LOCAL_FLAG_CLR(ctx, tx);
  XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, tx);

  XPORT_QMP_LOCAL_FLAG_CLR(ctx, rx_done);
  XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, rx_done);

  XPORT_QMP_LOCAL_FLAG_CLR(ctx, read_int);
  XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, read_int);

  ctx->local_desc.cur_frag_size = 0;
  ctx->local_desc.rem_frags_cnt = 0;

  ctx->tx_pkt_ctx = NULL;
  ctx->rx_pkt_buf = NULL;
  ctx->rx_pkt_size = 0;
  ctx->rx_pkt_read_size = 0;
}

/*=============================================================================
FUNCTION      xport_qmp_state_handler
=============================================================================*/
/**
*/
/*===========================================================================*/
boolean xport_qmp_state_handler(xport_qmp_ctx_type *ctx)
{
  glink_transport_if_type *xport_if = &ctx->xport_if;
  boolean ret                       = TRUE;
  boolean core_notify_linkup        = FALSE;
  boolean core_notify_remote_close  = FALSE;
  boolean core_notify_remote_open   = FALSE;
  boolean core_notify_close_ack     = FALSE;

  /* Check for Remote Link down first */
  if ((ctx->state >= LINK_UP) && (!XPORT_QMP_REMOTE_FLAG_GET(ctx, link_state)))
  {
    ctx->state = LINK_NEGOTIATION;

    /* Release the lock before calling Core functions */
    glink_os_cs_release(&ctx->cs);

    glink_core_rx_cmd_link_down(xport_if);

    /* Acquire the lock again as this function is called by holding the lock */
    glink_os_cs_acquire(&ctx->cs);

    XPORT_QMP_LOCAL_ACK_UPDATE(ctx, link_state);

    return ret;
  }

  switch (ctx->state)
  {
    case LINK_DOWN:
    {
      /* Check for remote Acked for earlier change */
      if (!XPORT_QMP_REMOTE_ACKED_CHECK(ctx, link_state))
      {
        XPORT_QMP_LOCAL_ACK_UPDATE(ctx, link_state);
        break;
      }

      /* Check if it is LOCAL SSR case */
      if (XPORT_QMP_LOCAL_FLAG_GET(ctx, link_state))
      {
        /* Local SSR, inform the down event first to remote */
        XPORT_QMP_LOCAL_FLAG_CLR(ctx, link_state);
        break;
      }

      /* Set the local link up state */
      XPORT_QMP_LOCAL_FLAG_SET(ctx, link_state);
      ctx->state = LINK_NEGOTIATION;
      break;
    }

    case LINK_NEGOTIATION:
    {
      /* Check for remote Acked for earlier change */
      if (!XPORT_QMP_REMOTE_ACKED_CHECK(ctx, link_state))
      {
        XPORT_QMP_LOCAL_ACK_UPDATE(ctx, link_state);
        break;
      }

      /* Check if remote is link up */
      if (!XPORT_QMP_REMOTE_FLAG_GET(ctx, link_state))
      {
        ret = FALSE;
        break;
      }

      /* Clear all the channel and tx/rx flags */
      xport_qmp_state_ch_flags_clr(ctx);

      /* Ack to remote link up */
      XPORT_QMP_LOCAL_ACK_UPDATE(ctx, link_state);
      ctx->state = LINK_UP;

      /* Notify Link up to the Code */
      core_notify_linkup = TRUE;
      break;
    }

    case LINK_UP:
    {
      /* No need to Ack remote channel open until local opens */
      ret = FALSE;
      break;
    }

    case LOCAL_CONNECTING:
    {
      /* Ack remote ch_state change */
      XPORT_QMP_LOCAL_ACK_UPDATE(ctx, ch_state);

      /* Check if remote is Acked for channel up */
      if (!XPORT_QMP_REMOTE_ACKED_CHECK(ctx, ch_state))
      {
        break;
      }

      if (!XPORT_QMP_REMOTE_FLAG_GET(ctx, ch_state))
      {
        break;
      }
      ctx->state = E2ECONNECTED;
      core_notify_remote_open = TRUE;
      break;
    }

    case E2ECONNECTED:
    {
      /* Check for remote channel down */
      if (!XPORT_QMP_REMOTE_FLAG_GET(ctx, ch_state))
      {
        ctx->state = LOCAL_CONNECTING;

        XPORT_QMP_LOCAL_ACK_UPDATE(ctx, ch_state);
        core_notify_remote_close = TRUE;
        break;
      }
      ret = FALSE;
      break;
    }

    case LOCAL_DISCONNECTING:
    {
      /* Check for remote channel down */
      if (!XPORT_QMP_REMOTE_FLAG_GET(ctx, ch_state) &&
          !XPORT_QMP_LOCAL_ACKED_CHECK(ctx, ch_state))
      {
        XPORT_QMP_LOCAL_ACK_UPDATE(ctx, ch_state);
        /* Local channel in progress, not need info remote close */
        /* core_notify_remote_close = TRUE; */
      }

      /* Check if remote is Acked for channel up */
      if (!XPORT_QMP_REMOTE_ACKED_CHECK(ctx, ch_state))
      {
        ret = FALSE;
        break;
      }

      /* Clear all the channel and tx/rx flags */
      xport_qmp_state_ch_flags_clr(ctx);

      ctx->state = LINK_UP;
      core_notify_close_ack = TRUE;
      break;
    }

    default:
    {
      ret = FALSE;
      break;
    }
  }

  /* Release the lock before calling Core functions */
  glink_os_cs_release(&ctx->cs);

  if (core_notify_close_ack)
  {
    glink_core_rx_cmd_ch_close_ack(xport_if);
  }

  if (core_notify_remote_open)
  {
    glink_core_rx_cmd_remote_open(xport_if);
  }

  if (core_notify_remote_close)
  {
    glink_core_rx_cmd_remote_close(xport_if);
  }

  if (core_notify_linkup)
  {
    glink_core_rx_cmd_link_up(xport_if);
  }

  /* Acquire the lock again as this function is called by holding the lock */
  glink_os_cs_acquire(&ctx->cs);

  return ret;
}

/*=============================================================================
FUNCTION      xport_qmp_tx_handler
=============================================================================*/
/**
*/
/*===========================================================================*/
boolean xport_qmp_tx_handler(xport_qmp_ctx_type *ctx)
{
  glink_core_tx_pkt_type *pkt_ctx = ctx->tx_pkt_ctx;
  boolean                ret = FALSE;

  if ((pkt_ctx == NULL) || (pkt_ctx->data == NULL))
  {
    return ret;
  }

  GLINK_OS_LOG_DBG("xport_qmp_tx_handler entry ctx:0x%08X, size_remaining:0x%08X.", ctx, pkt_ctx->size_remaining);
  /* Check if TX packet in progress */
  if (pkt_ctx->size_remaining != 0)
  {
    /* Send remaining fragment of TX data */
    if (XPORT_QMP_REMOTE_ACKED_CHECK(ctx, tx))
    {
      xport_qmp_pkt_send(ctx);
      ret = TRUE;
    }
  }
  /* Check if remote did RX Done */
  else if (XPORT_QMP_REMOTE_FLAG_TOGGLED_CHECK(ctx, rx_done))
  {
    /* Ack to remote */
    XPORT_QMP_LOCAL_ACK_UPDATE(ctx, rx_done);

    ctx->tx_pkt_ctx = NULL;

    /* Release the lock before calling Core functions */
    glink_os_cs_release(&ctx->cs);

    /* Inform Core TX Done */
    glink_core_rx_cmd_tx_done(&ctx->xport_if, pkt_ctx);

    /* Acquire the lock again as this function is called by holding the lock */
    glink_os_cs_acquire(&ctx->cs);

    ret = TRUE;
  }

  return ret;
}

/*=============================================================================
FUNCTION      xport_qmp_rx_handler
=============================================================================*/
/**
*/
/*===========================================================================*/
boolean xport_qmp_rx_handler(xport_qmp_ctx_type *ctx)
{
  uint32 cur_frag_size;
  uint32 rem_frags_cnt;
  boolean ret = FALSE;

  /* Check if there is any change in remote */
  if (!XPORT_QMP_REMOTE_FLAG_TOGGLED_CHECK(ctx, tx))
  {
    return ret;
  }
  /* Read RX packet details */
  cur_frag_size = ctx->remote_desc.cur_frag_size;
  rem_frags_cnt = ctx->remote_desc.rem_frags_cnt;

  GLINK_OS_LOG_DBG("xport_qmp_rx_handler entry cur_frag_size:0x%08X, rem_frags_cnt:0x%08X.", cur_frag_size, rem_frags_cnt);

  if ((cur_frag_size == 0) || (cur_frag_size > ctx->cfg_remote_mailbox_size))
  {
    GLINK_OS_LOG_ERR("RX fragment size(%d) more than mailbox size(%d).",
            cur_frag_size, ctx->cfg_remote_mailbox_size);
    return ret;
  }

  /* Check if it is new rx packet */
  if ((ctx->rx_pkt_size == 0) && (ctx->rx_pkt_read_size == 0))
  {
    /* Max RX packet size */
    ctx->rx_pkt_size = cur_frag_size + rem_frags_cnt * ctx->cfg_remote_mailbox_size;

    if (ctx->rx_pkt_size > ctx->cfg_rx_max_pkt_size)
    {
      GLINK_OS_LOG_ERR("Max RX size(%d) more than max pkt size(%d).",
              ctx->rx_pkt_size, ctx->cfg_rx_max_pkt_size);
    }
    else
    {
      ctx->rx_pkt_buf = ctx->cfg->rx_pkt_static_buf;
      ctx->rx_pkt_read_size = cur_frag_size;

      /* Read shared payload memory */
      if ((volatile uint32 *)ctx->cfg->rx_pkt_static_buf != ctx->shared_remote_mailbox)
      {
        xport_qmp_mailbox_read(ctx, ctx->rx_pkt_buf, cur_frag_size);
      }

      /* Do TX ack to remote */
      XPORT_QMP_LOCAL_ACK_UPDATE(ctx, tx);

      ret = TRUE;

      if (ctx->rx_pkt_size == ctx->rx_pkt_read_size)
      {
        /* Release the lock before calling Core functions */
        glink_os_cs_release(&ctx->cs);

        glink_core_rx_cmd_data(&ctx->xport_if, ctx->rx_pkt_buf, ctx->rx_pkt_size);

        /* Acquire the lock again as this function is called by holding the lock */
        glink_os_cs_acquire(&ctx->cs);
      }
    }
  }
  else if ((ctx->rx_pkt_size != 0) && (ctx->rx_pkt_read_size != ctx->rx_pkt_size))
  {
    if ((ctx->rx_pkt_read_size + cur_frag_size +
        (rem_frags_cnt * ctx->cfg_remote_mailbox_size)) > ctx->rx_pkt_size)
    {
      GLINK_OS_LOG_ERR("RX size more than pkt size! cur_frag_size:%d, rem_frags_cnt:%d",
              cur_frag_size, rem_frags_cnt);
      GLINK_OS_LOG_ERR("RX size more than pkt size! rx_pkt_read_size:%d, rx_pkt_size:%d.",
              ctx->rx_pkt_read_size, ctx->rx_pkt_size);
    }
    else
    {
      /* Read shared payload memory */
      xport_qmp_mailbox_read(ctx, &ctx->rx_pkt_buf[ctx->rx_pkt_read_size], cur_frag_size);
      ctx->rx_pkt_read_size += cur_frag_size;

      /* Do TX ack to remote */
      XPORT_QMP_LOCAL_ACK_UPDATE(ctx, tx);

      ret = TRUE;

      if (rem_frags_cnt == 0)
      {
        if ((ctx->rx_pkt_size - ctx->rx_pkt_read_size) <= ctx->cfg_remote_mailbox_size)
        {
          /* Update the actual packet size */
          ctx->rx_pkt_size = ctx->rx_pkt_read_size;

          /* Release the lock before calling Core functions */
          glink_os_cs_release(&ctx->cs);

          glink_core_rx_cmd_data(&ctx->xport_if, ctx->rx_pkt_buf, ctx->rx_pkt_size);

          /* Acquire the lock again as this function is called by holding the lock */
          glink_os_cs_acquire(&ctx->cs);
        }
      }
    }
  }

  return ret;
}

/*=============================================================================
FUNCTION      xport_qmp_isr
=============================================================================*/
/**
*/
/*===========================================================================*/
void xport_qmp_isr(void *isr_ctx)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)isr_ctx;
  boolean intr_send = FALSE;
  xport_qmp_state_type prv_state;

  if (ctx == NULL)
  {
    GLINK_OS_LOG_ERR("QMP ISR context is NULL.", 0, 0);
    return;
  }

  glink_os_cs_acquire(&ctx->cs);

  GLINK_OS_LOG_DBG("INT RECV(%s): State:%d.", ctx->cfg->remote_ss, ctx->state);
  GLINK_OS_LOG_DBG("INT RECV: Local:0x%08X(0x%08X).",
        (*((volatile uint32*)&ctx->shared_local_desc)),(*((uint32*)&ctx->local_desc)));
  GLINK_OS_LOG_DBG("INT RECV: Remote:0x%08X(0x%08X).",
        (*((volatile uint32*)&ctx->shared_remote_desc)), (*((uint32*)&ctx->remote_desc)));

  glink_os_clear_interrupt(ctx->intr);

  /* Read remote descriptor and process it */
  ctx->remote_desc = *ctx->shared_remote_desc;

  do
  {
    prv_state = ctx->state;

    intr_send |= xport_qmp_state_handler(ctx);
  } while (prv_state != ctx->state);

  if (ctx->state == E2ECONNECTED)
  {
    intr_send |= xport_qmp_tx_handler(ctx);
    intr_send |= xport_qmp_rx_handler(ctx);
  }

  if (intr_send)
  {
    xport_qmp_intr_send(ctx);
  }

  glink_os_cs_release(&ctx->cs);
}

/*===============================================================================

                     TRANSPORT FUNCTION DEFINATION

===============================================================================*/

/*===============================================================================
FUNCTION      xport_qmp_tx_cmd_ch_open
===============================================================================*/
/**
*/
/*===============================================================================*/
glink_err_type xport_qmp_tx_cmd_ch_open(glink_transport_if_type *xport_if)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;

  glink_os_cs_acquire(&ctx->cs);

#if !defined(GLINK_FEATURE_SIMULATOR)
  if (ctx->state != LINK_UP)
  {
    glink_os_cs_release(&ctx->cs);
    return GLINK_STATUS_NOT_INIT;
  }

  /* Update the local channel state */
  XPORT_QMP_LOCAL_FLAG_SET(ctx, ch_state);
  ctx->state = LOCAL_CONNECTING;

  xport_qmp_intr_send(ctx);
#endif

  glink_os_cs_release(&ctx->cs);

#if defined(GLINK_FEATURE_SIMULATOR)
  glink_core_rx_cmd_remote_open(xport_if);
#endif

  return GLINK_STATUS_SUCCESS;
}

/*===============================================================================
FUNCTION      xport_qmp_tx_cmd_ch_close
===============================================================================*/
/**
*/
/*===============================================================================*/
glink_err_type xport_qmp_tx_cmd_ch_close(glink_transport_if_type *xport_if)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;

  glink_os_cs_acquire(&ctx->cs);

#if !defined(GLINK_FEATURE_SIMULATOR)
  if ((ctx->state == LOCAL_CONNECTED)  ||
      (ctx->state == LOCAL_CONNECTING) ||
      (ctx->state == E2ECONNECTED))
  {
    /* Update the local channel state */
    XPORT_QMP_LOCAL_FLAG_CLR(ctx, ch_state);
    ctx->state = LOCAL_DISCONNECTING;

    xport_qmp_intr_send(ctx);
  }
#endif

  glink_os_cs_release(&ctx->cs);

  return GLINK_STATUS_SUCCESS;
}

/*=============================================================================
FUNCTION      xport_qmp_tx_cmd_local_rx_done
=============================================================================*/
/**
*/
/*===========================================================================*/
glink_err_type xport_qmp_tx_cmd_local_rx_done
(
  glink_transport_if_type *xport_if,
  const void              *ptr
)
{
  GLINK_OS_ARG_NOT_USED(ptr);
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;
  glink_err_type     status = GLINK_STATUS_SUCCESS;

  glink_os_cs_acquire(&ctx->cs);

#if !defined(GLINK_FEATURE_SIMULATOR)
  if (ctx->state != E2ECONNECTED)
  {
    status = GLINK_STATUS_CH_NOT_FULLY_OPENED;
    goto UNLOCK_RETURN;
  }

  if ((ctx->rx_pkt_buf != ptr) ||
      (ctx->rx_pkt_size == 0)   ||
      (ctx->rx_pkt_size != ctx->rx_pkt_read_size))
  {
    status = GLINK_STATUS_INVALID_PARAM;
    goto UNLOCK_RETURN;
  }

  /* Reset RX variable states */
  ctx->rx_pkt_size = 0;
  ctx->rx_pkt_buf = NULL;
  ctx->rx_pkt_read_size = 0;

  /* Update the local rx_done */
  XPORT_QMP_LOCAL_FLAG_TOGGLE(ctx, rx_done);

  xport_qmp_intr_send(ctx);
UNLOCK_RETURN:
#endif
  glink_os_cs_release(&ctx->cs);

  return status;
}

/*===============================================================================
FUNCTION      xport_qmp_tx_data
===============================================================================*/
/**
*/
/*===============================================================================*/
glink_err_type xport_qmp_tx_data
(
  glink_transport_if_type *xport_if,
  glink_core_tx_pkt_type  *pkt_ctx
)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;
  GLINK_OS_ARG_NOT_USED(ctx);
  GLINK_OS_ARG_NOT_USED(pkt_ctx);

#if !defined(GLINK_FEATURE_SIMULATOR)
  if (ctx->state != E2ECONNECTED)
  {
    return GLINK_STATUS_CH_NOT_FULLY_OPENED;
  }

  if (pkt_ctx->size > ctx->cfg_tx_max_pkt_size)
  {
    return GLINK_STATUS_OUT_OF_RESOURCES;
  }

  ctx->tx_pkt_ctx = pkt_ctx;

    /** Atomically write data to MBox to prevent pre-emption from rx_done_ack
     * interrupt of previous tx. */
    glink_os_disable_interrupt(ctx->intr);
    xport_qmp_pkt_send(ctx);
    xport_qmp_intr_send(ctx);
    glink_os_enable_interrupt(ctx->intr);
#endif
  return GLINK_STATUS_SUCCESS;
}

/*===============================================================================
FUNCTION      xport_qmp_remote_down
===============================================================================*/
/**
 * Transport should call this when remote SS is going DOWN .
*/
/*===============================================================================*/
static void xport_qmp_remote_down
(
  glink_transport_if_type *xport_if
)
{
  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;

  glink_os_cs_acquire(&ctx->cs);

  if (ctx->state == LINK_DOWN)
  {
    glink_os_disable_interrupt(ctx->intr);
    glink_os_cs_release(&ctx->cs);
    return;
  }


  /* Clear the channel state and link state */
  xport_qmp_state_ch_flags_clr(ctx);
  XPORT_QMP_LOCAL_FLAG_CLR(ctx, link_state);
  XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, link_state);

  ctx->state = LINK_DOWN;

  glink_os_disable_interrupt(ctx->intr);
  xport_qmp_intr_send(ctx);

  glink_os_cs_release(&ctx->cs);
}

/*===============================================================================
FUNCTION      xport_qmp_remote_up
===============================================================================*/
/**
 * Transport should call this when remote SS is UP.
*/
/*===============================================================================*/
static void xport_qmp_remote_up
(
  glink_transport_if_type *xport_if
)
{
  static boolean qmp_init_state = FALSE;

  xport_qmp_ctx_type *ctx = (xport_qmp_ctx_type *)xport_if;

  xport_qmp_isr(ctx);

  if (qmp_init_state == FALSE)
  {
    /* This is first time QMP is getting initialized, register the ISR */
    glink_os_register_isr(ctx->intr, xport_qmp_isr, ctx);
    qmp_init_state = TRUE;
  }
  else
  {
    /* SessionStart->SessionEnd->SessionStart case */
    /* QMP was already initialized and hence ISR was also registered, just enable interrupt now */
    glink_os_enable_interrupt(ctx->intr);
  }
}


/*===============================================================================

                     PUBLIC FUNCTION DEFINATION

===============================================================================*/

/*===============================================================================
FUNCTION      xport_qmp_init
===============================================================================*/
/**
*/
/*===============================================================================*/
void xport_qmp_init(void)
{
  uint32 ind;

  /* Initialize context */
  for (ind = 0; ind < GLINK_CFG_MAX_REMOTE_HOSTS; ind++)
  {
    xport_qmp_ctx_type      *ctx      = &xport_qmp_ctxs[ind];
    glink_transport_if_type *xport_if = &ctx->xport_if;
    const xport_qmp_config_type *cfg  = xport_qmp_get_config(ind);

    GLINK_OS_LOG_DBG("xport_qmp_init entry ctx:0x%08X, cfg:0x%08X", ctx, cfg);

    if (cfg == NULL)
    {
      continue;
    }
    ctx->cfg  = cfg;
    ctx->intr = &cfg->intr;

    GLINK_OS_LOG_DBG("xport_qmp_init ch:%s, remote:%s.", cfg->ch_name, cfg->remote_ss);

    glink_os_cs_init(&ctx->cs);

#if !defined(GLINK_FEATURE_SIMULATOR)
    ctx->state = LINK_DOWN;

    ctx->shared_local_desc      = (volatile xport_qmp_desc_type *)cfg->local_shared_mem;
    ctx->shared_local_mailbox   = cfg->local_shared_mem + (sizeof(xport_qmp_desc_type) / sizeof(uint32));
    ctx->cfg_local_mailbox_size = cfg->local_shared_mem_size - sizeof(xport_qmp_desc_type);
    ctx->cfg_tx_max_pkt_size    = cfg->tx_max_pkt_size;

    ctx->shared_remote_desc      = (volatile xport_qmp_desc_type *)cfg->remote_shared_mem;
    ctx->shared_remote_mailbox   = cfg->remote_shared_mem + (sizeof(xport_qmp_desc_type) / sizeof(uint32));
    ctx->cfg_remote_mailbox_size = cfg->remote_shared_mem_size - sizeof(xport_qmp_desc_type);
    ctx->cfg_rx_max_pkt_size     = cfg->rx_max_pkt_size;

    ctx->local_desc = *ctx->shared_local_desc;
#else
    ctx->state = LINK_UP;
#endif

    xport_if->remote_ss = cfg->remote_ss;
    xport_if->ch_name   = cfg->ch_name;

    xport_if->tx_cmd_ch_open       = xport_qmp_tx_cmd_ch_open;
    xport_if->tx_cmd_ch_close      = xport_qmp_tx_cmd_ch_close;
    xport_if->tx_cmd_local_rx_done = xport_qmp_tx_cmd_local_rx_done;
    xport_if->tx_data              = xport_qmp_tx_data;
    xport_if->remote_up            = xport_qmp_remote_up;
    xport_if->remote_down          = xport_qmp_remote_down;

    GLINK_OS_LOG_DBG("xport_qmp_init reg_xport ch:%s, remote:%s.", cfg->ch_name, cfg->remote_ss);
    glink_core_register_transport(xport_if);

#if defined(GLINK_FEATURE_SIMULATOR)
    GLINK_OS_LOG("xport_qmp_init link_up ch:%s, remote:%s.", cfg->ch_name, cfg->remote_ss);
    glink_core_rx_cmd_link_up(xport_if);
#endif
    GLINK_OS_LOG_DBG("xport_qmp_init exit ctx:0x%08X, cfg:0x%08X", ctx, cfg);
  }
}
