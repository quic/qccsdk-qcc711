/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef XPORT_QMP_H
#define XPORT_QMP_H

/*=============================================================================

              GLink QMP Transport Header File

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
#include"glink_os_utils.h"
#include"glink_internal.h"
#include"xport_qmp_config.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
/* Helper macros used for shared descriptor state/flags */
#define XPORT_QMP_FLAG_GET(ctx, place, flag) \
  ((ctx)->place##_desc.local_##flag)

#define XPORT_QMP_FLAG_SET(ctx, place, flag) \
  do {(ctx)->place##_desc.local_##flag = 1;}while(0)

#define XPORT_QMP_FLAG_CLR(ctx, place, flag) \
  do {(ctx)->place##_desc.local_##flag = 0;}while(0)

#define XPORT_QMP_LOCAL_FLAG_TOGGLE(ctx, flag) \
  do{(ctx)->local_desc.local_##flag = !((ctx)->local_desc.local_##flag);}while(0)

#define XPORT_QMP_LOCAL_FLAG_GET(ctx, flag)    XPORT_QMP_FLAG_GET(ctx, local, flag)
#define XPORT_QMP_LOCAL_FLAG_SET(ctx, flag)    XPORT_QMP_FLAG_SET(ctx, local, flag)
#define XPORT_QMP_LOCAL_FLAG_CLR(ctx, flag)    XPORT_QMP_FLAG_CLR(ctx, local, flag)

#define XPORT_QMP_LOCAL_FLAG_ACK_CLR(ctx, flag)  \
  do {(ctx)->local_desc.remote_##flag##_ack = 0;} while(0)

#define XPORT_QMP_REMOTE_FLAG_GET(ctx, flag)   XPORT_QMP_FLAG_GET(ctx, remote, flag)

#define XPORT_QMP_REMOTE_ACKED_CHECK(ctx, flag) \
  ((ctx)->local_desc.local_##flag == (ctx)->remote_desc.remote_##flag##_ack)

#define XPORT_QMP_LOCAL_ACKED_CHECK(ctx, flag) \
  ((ctx)->remote_desc.local_##flag == (ctx)->local_desc.remote_##flag##_ack)

#define XPORT_QMP_LOCAL_ACK_UPDATE(ctx, flag) \
  do{(ctx)->local_desc.remote_##flag##_ack = (ctx)->remote_desc.local_##flag;}while(0)

#define XPORT_QMP_REMOTE_FLAG_TOGGLED_CHECK(ctx, flag) \
   ((ctx)->remote_desc.local_##flag != (ctx)->local_desc.remote_##flag##_ack)

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
typedef enum
{
  LINK_DOWN            = 0,
  LINK_NEGOTIATION     = 1,
  LINK_UP              = 2,
  LOCAL_CONNECTING     = 3,
  LOCAL_CONNECTED      = 4,
  E2ECONNECTED         = 5,
  LOCAL_DISCONNECTING  = 6,
} xport_qmp_state_type;

typedef struct
{
  uint32 local_link_state:1;
  uint32 remote_link_state_ack:1;

  uint32 local_ch_state:1;
  uint32 remote_ch_state_ack:1;

  uint32 local_tx:1;
  uint32 remote_tx_ack:1;

  uint32 local_rx_done:1;
  uint32 remote_rx_done_ack:1;

  uint32 local_read_int:1;
  uint32 remote_read_int_ack:1;

  uint32 reserved:6;

  uint32 cur_frag_size:8;
  uint32 rem_frags_cnt:8;
} xport_qmp_desc_type;

typedef struct
{
  glink_transport_if_type      xport_if;

  const xport_qmp_config_type  *cfg;
  glink_os_cs_type             cs;

  const glink_os_ipc_intr_type *intr;

  xport_qmp_state_type         state;

  xport_qmp_desc_type local_desc;
  xport_qmp_desc_type remote_desc;

  glink_core_tx_pkt_type       *tx_pkt_ctx;

  uint8                        *rx_pkt_buf;
  uint32                       rx_pkt_size;
  uint32                       rx_pkt_read_size;

  volatile xport_qmp_desc_type *shared_local_desc;
  volatile xport_qmp_desc_type *shared_remote_desc;

  volatile uint32              *shared_local_mailbox;
  volatile uint32              *shared_remote_mailbox;

  uint32                       cfg_local_mailbox_size;
  uint32                       cfg_tx_max_pkt_size;

  uint32                       cfg_remote_mailbox_size;
  uint32                       cfg_rx_max_pkt_size;
} xport_qmp_ctx_type;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*===============================================================================

                     PUBLIC FUNCTION DEFINATION

===============================================================================*/

/*===============================================================================
FUNCTION      xport_qmp_init
===============================================================================*/
/**
*/
/*===============================================================================*/
void xport_qmp_init(void);

/*=============================================================================

                        XPORT QMP INTERNAL FUNCTION 

=============================================================================*/
void xport_qmp_intr_send(xport_qmp_ctx_type *ctx);
void xport_qmp_mailbox_write(xport_qmp_ctx_type *ctx, const uint8 *buf, uint32 size);
void xport_qmp_mailbox_read(xport_qmp_ctx_type *ctx, uint8 *buf, uint32 size);
void xport_qmp_pkt_send(xport_qmp_ctx_type *ctx);
void xport_qmp_state_ch_flags_clr(xport_qmp_ctx_type *ctx);
boolean xport_qmp_state_handler(xport_qmp_ctx_type *ctx);
boolean xport_qmp_tx_handler(xport_qmp_ctx_type *ctx);
boolean xport_qmp_rx_handler(xport_qmp_ctx_type *ctx);
void xport_qmp_isr(void *isr_ctx);
glink_err_type xport_qmp_tx_cmd_ch_open(glink_transport_if_type *xport_if);
glink_err_type xport_qmp_tx_cmd_ch_close(glink_transport_if_type *xport_if);
glink_err_type xport_qmp_tx_cmd_local_rx_done(glink_transport_if_type *xport_if, const void *ptr);
glink_err_type xport_qmp_tx_data(glink_transport_if_type *xport_if, glink_core_tx_pkt_type *pkt_ctx);

#endif /* XPORT_QMP_H */

