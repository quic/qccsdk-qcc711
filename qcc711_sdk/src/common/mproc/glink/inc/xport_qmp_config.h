/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
/*=============================================================================

            GLink QMP Transport Configuration Structures

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header:  $

when       who     what, where, why
--------   ---     ------------------------------------------------------------
=============================================================================*/

#ifndef XPORT_QMP_CONFIG_H
#define XPORT_QMP_CONFIG_H

/*=============================================================================
                           INCLUDE FILES
=============================================================================*/
#include "glink.h"
#include "glink_os_utils.h"
#include "glink_internal.h"

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
#define XPORT_QMP_CONFIG_MBOX_HEADER_SIZE       0x04 /* sizeof(xport_qmp_desc_type) */

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/
/* Glink QMP Configuration */
typedef struct
{
  const char             *version;               /* Version                   */
  const char             *remote_ss;             /* Remote host name          */
  const char             *ch_name;               /* Logical channel name      */
  uint32                 local_shared_mem_size;  /* Local shared memory size  */
  volatile uint32        *local_shared_mem;      /* Local shared memory base  */
  uint32                 remote_shared_mem_size; /* Remote shared memory size */
  volatile uint32        *remote_shared_mem;     /* Remote shared memory base */
  uint32                 tx_max_pkt_size;        /* TX Max packet size        */
  uint32                 rx_max_pkt_size;        /* RX Max packet size        */
  void                   *rx_pkt_static_buf;     /* RX packet static buffer   */
  glink_os_ipc_intr_type intr;                   /* IPC Interrupt             */
} xport_qmp_config_type;

/*=============================================================================
                       GLOBAL DATA DEFINATION
=============================================================================*/

/*=============================================================================
                     PUBLIC FUNCTION DEFINATION
=============================================================================*/
/*=============================================================================
FUNCTION      xport_qmp_get_config
=============================================================================*/
/**
*/
/*===========================================================================*/
const xport_qmp_config_type* xport_qmp_get_config(uint32 ind);

#endif /* XPORT_QMP_CONFIG_H */


