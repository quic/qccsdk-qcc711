/*=============================================================================

              GLink QMP Transport Configuration


   Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Qualcomm Technologies, Inc. Confidential and Proprietary.
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
#include "xport_qmp_config.h"
#include "hwio_tme_ipc.h"
#include "hwio_aon.h"
#include "qcc710.h"   //TME_Lite_IRQn

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
#define XPORT_QMP_CONFIG_MBOX_SIZE                 0x20

/*=============================================================================
                         TYPE DEFINITIONS
=============================================================================*/

/*=============================================================================
                       LOCAL DATA DECLARATIONS
=============================================================================*/
static xport_qmp_config_type xport_qmp_config[GLINK_CFG_MAX_REMOTE_HOSTS] =
{
  {
    /* APPS -> TME-L */
    NULL,                                                            /* Version                   */
    "tme",                                                           /* Remote SS name            */
    "tmeRequest",                                                    /* Logical Channel name      */
    XPORT_QMP_CONFIG_MBOX_SIZE,                                      /* Local shared memory size  */
    (void *)HWIO_IN_MBOX_WORDw_ADDR(0),                              /* Local shared memory base  */
    XPORT_QMP_CONFIG_MBOX_SIZE,                                      /* Remote shared memory size */
    (void *)HWIO_OUT_MBOX_WORDw_ADDR(0),                             /* Remote shared memory base */
    XPORT_QMP_CONFIG_MBOX_SIZE - XPORT_QMP_CONFIG_MBOX_HEADER_SIZE,  /* TX Max packet size        */
    XPORT_QMP_CONFIG_MBOX_SIZE - XPORT_QMP_CONFIG_MBOX_HEADER_SIZE,  /* RX Max packet size        */
    (void *)HWIO_OUT_MBOX_WORDw_ADDR(1),                             /* RX packet static buffer   */
    {
       (void *)HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR,                   /* Outgoing interrupt register address       */
       HWIO_AON_TCSR_IPC_APPS_TO_TME_EVENT_BMSK,                     /* Outgoing interrupt mask                  */
       NULL,                                                         /* Incoming interrupt clear register address */
       0,                                                            /* Incoming interrupt clear mask             */
       TME_Lite_IRQn                                                 /* Incoming interrupt = 1                   */
    }
  }
};

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

                     PUBLIC FUNCTION DEFINATION

=============================================================================*/

/*=============================================================================
FUNCTION      xport_qmp_get_config
=============================================================================*/
/**
*/
/*===========================================================================*/
const xport_qmp_config_type* xport_qmp_get_config(uint32 ind)
{
  xport_qmp_config_type *config;

  if (ind >= GLINK_CFG_MAX_REMOTE_HOSTS)
  {
    return NULL;
  }
  config = &xport_qmp_config[ind];
  
  config->version = "Glink QMP V1.0 : " __DATE__ " : " __TIME__;

  return config;
}
