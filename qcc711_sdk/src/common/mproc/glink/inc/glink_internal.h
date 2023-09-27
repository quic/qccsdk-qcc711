/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef GLINK_INTERNAL_H
#define GLINK_INTERNAL_H

/*=============================================================================

              Glink Internal Header File

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

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/* forward declaration */
struct glink_transport_if;
typedef struct glink_transport_if   glink_transport_if_type;

/* glink_transport_*if*_type name interfere with patching tool when used
   as return type. Creating another alias.*/
typedef glink_transport_if_type   glink_transport_intf_type;


/** TX packet  */
typedef struct
{
  const void *data;          /* Pointer to the data buffer to be transmitted */
  const void *pkt_priv;      /* Per packet private data */
  size_t     size;           /* Size of data buffer */
  size_t     size_remaining; /* Size left to transmit */
} glink_core_tx_pkt_type;

typedef struct
{
  const void *data;          /* Pointer to the data buffer to be transmitted */
  size_t     size;           /* Size of data buffer */
} glink_core_rx_pkt_type;

/* Logical channel conext */
typedef struct {
  /** Remote subsystem name */
  const char                  *remote_ss;

  /** Logical channel name */
  const char                  *ch_name;

  /** Private data for client to maintain context. Supplied on glink_open and
      is passed back to client in the notification callbacks */
  const void                  *priv;

  /** Data receive notification callback. Optional if notify_rxv is provided */
  glink_rx_notification_cb    notify_rx;

  /** Data transmit notification callback */
  glink_tx_notification_cb    notify_tx_done;

  /** GLink channel state notification callback */
  glink_state_notification_cb notify_state;

  /** tx abort notification. This callback would be invoked if client
  *   had queued a tx buffer with glink and it had not been transmitted i.e.
  *   tx_done callback has not been called for this buffer and remote side
  *   or local side closed the port. Optional */
  glink_notify_tx_abort_cb    notify_tx_abort;

  /** TX packet details */
  glink_core_tx_pkt_type      tx_pkt;

  /** RX packet details */
  glink_core_rx_pkt_type      rx_pkt;

  /** Transport */
  glink_transport_if_type     *if_ptr;

} glink_channel_ctx_type;

/** Sends OPEN command to transport for transport to do whatever it deems
 *  necessary to open a GLink logical channel.
 *  GLink Core expects glink_transport_if_type::rx_cmd_ch_open_ack to be called
 *  as a result of channel opening. */
typedef glink_err_type (*tx_cmd_ch_open_fn)
(
  glink_transport_if_type *if_ptr /* Pointer to the interface instance */
);

/** Sends CLOSE command to transport for transport to do whatever it deems
 *  necessary to close the specified GLink logical channel.
 *  GLink Core expects glink_transport_if_type::rx_cmd_ch_close_ack to be
 *  called as a result of channel closing. */
typedef glink_err_type (*tx_cmd_ch_close_fn)
(
  glink_transport_if_type *if_ptr /* Pointer to the interface instance */
);

/** Send receive done command for an intent for the specified channel */
typedef glink_err_type (*tx_cmd_local_rx_done_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  const void              *ptr     /* RX buffer pointer */
);

/** Send a data packet to the transport to be transmitted over the specified
 *  channel */
typedef glink_err_type (*tx_data_fn)
(
  glink_transport_if_type *if_ptr, /* Pointer to the interface instance */
  glink_core_tx_pkt_type  *pkt_ctx /* Packet to be transmitted */
);


/**  Core calls this transport interface function when remote subsystem is up */
typedef void (*remote_ss_up)
(
  glink_transport_if_type *if_ptr /* Pointer to the interface instance */
);

/**  Core calls this transport interface function when remote subsystem is going down */
typedef void (*remote_ss_down)
(
  glink_transport_if_type *if_ptr /* Pointer to the interface instance */
);

/**
 * Transport status */
typedef enum {
  GLINK_XPORT_LINK_DOWN = 0,
  GLINK_XPORT_LINK_UP   = 1,
} glink_transport_status_type;



typedef struct
{
  /** Lock */
  glink_os_cs_type            cs;

  /** Keeps track of the current status of the transport */
  glink_transport_status_type status;

  /** Channel context connected over transport */
  glink_channel_ctx_type      ch_ctx;

} glink_core_xport_ctx_type;

struct glink_transport_if
{

  /** Remote subsystem name */
  const char                         *remote_ss;

  /** Logical channel name */
  const char                         *ch_name;

  /** Sends OPEN command to transport for transport to do whatever it deems
   *  necessary to open a GLink logical channel.
   *  GLink Core expects glink_transport_if_type::rx_cmd_ch_open_ack to be
   *  called as a result of channel opening. */
  tx_cmd_ch_open_fn                  tx_cmd_ch_open;

  /** Sends CLOSE command to transport for transport to do whatever it deems
   *  necessary to close the specified GLink logical channel.
   *  GLink Core expects glink_transport_if_type::rx_cmd_ch_close_ack to be
   *  called as a result of channel closing. */
  tx_cmd_ch_close_fn                 tx_cmd_ch_close;

  /** Send receive done command for an intent for the specified channel */
  tx_cmd_local_rx_done_fn            tx_cmd_local_rx_done;

  /** Send a data packet to the transport to be transmitted over the specified
   *  channel */
  tx_data_fn                         tx_data;

  /**  Core calls this transport interface function when remote subsystem is up */
  remote_ss_up                       remote_up;

  /**  Core calls this transport interface function when remote subsystem is going down */
  remote_ss_down                     remote_down;


  /** Transport specific data that transport may choose fill in
   * with some data */
  glink_core_xport_ctx_type          core_priv;
};

typedef struct
{
  const char                *remote_ss;    /* Remote subsystem, use client pointer  */
  glink_link_state_notif_cb link_notifier; /* Notification callback                 */
  void                      *priv;         /* Notification callback private context */
  glink_link_state_type     link_state;    /* Link state notified to client         */
} glink_link_notify_type;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*=============================================================================

                     CORE FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
FUNCTION      glink_core_register_transport
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_register_transport(glink_transport_if_type *if_ptr);

/*=============================================================================
FUNCTION      glink_core_rx_cmd_link_up
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_link_up(glink_transport_if_type *if_ptr);

/*=============================================================================
FUNCTION      glink_core_rx_cmd_link_down
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_link_down(glink_transport_if_type *if_ptr);

/*=============================================================================
FUNCTION      glink_core_rx_cmd_remote_open
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_remote_open(glink_transport_if_type *if_ptr);

/*=============================================================================
FUNCTION      glink_core_rx_cmd_remote_close
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_remote_close(glink_transport_if_type *if_ptr);

/*=============================================================================
FUNCTION      glink_core_rx_cmd_ch_close_ack
=============================================================================*/
/**
*/
/*===========================================================================*/
void glink_core_rx_cmd_ch_close_ack(glink_transport_if_type *if_ptr);

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
);

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
);


/*=============================================================================

                        CORE INTERNAL FUNCTION 

=============================================================================*/
glink_transport_intf_type *glinki_find_xport_by_name(const char *remote_ss);
void glink_link_state_notify(const char *remote_ss, glink_link_state_type link_state);
void glink_rx_cmd_remote_close(glink_core_xport_ctx_type *core_priv, glink_channel_ctx_type *ch_ctx);

#endif /* GLINK_INTERNAL_H */
