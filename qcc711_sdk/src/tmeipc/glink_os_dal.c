
/*===========================================================================

                    GLink DAL OS Abstraction

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

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include <stdlib.h>
#include "glink_os_utils.h"
#include "qcc710.h"
#include "hwio_aon.h"
#include "core_cm3.h"
#include "qapi_task.h"

/*===========================================================================
                           MACRO DEFINITIONS
===========================================================================*/

/*===========================================================================
                           TYPE DEFINITIONS
===========================================================================*/

/*===========================================================================
                        GLOBAL DATA DECLARATIONS
===========================================================================*/
static glink_os_isr_cb_fn glink_os_isr_fn = NULL;
static void*              glink_os_isr_ctx = NULL;
static uint32             glink_os_irq_in = 0;

/*===========================================================================
                    LOCAL FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
                    EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
  FUNCTION      glink_os_init
===========================================================================*/
/**
*/
/*=========================================================================*/
void glink_os_init(void)
{
}

/*===========================================================================
  FUNCTION      TME_Lite_IntHandler
===========================================================================*/
/**
*/
/*=========================================================================*/
void TME_Lite_IntHandler(void)
{
  if (glink_os_isr_fn != NULL)
  {
    glink_os_isr_fn(glink_os_isr_ctx);
  }
}

/*===========================================================================
  FUNCTION      glink_os_cs_init
===========================================================================*/
/**
  Initializes a Critical Section

  @param[in]  cs   pointer to critical section object allocated by caller.

  @return
  TRUE if critical section was initialized, FALSE otherwise
*/
/*=========================================================================*/
boolean glink_os_cs_init( glink_os_cs_type *cs )
{
  GLINK_OS_ARG_NOT_USED(cs);

  return ( TRUE );
}

/*===========================================================================
  FUNCTION  glink_os_cs_deinit
===========================================================================*/
/**
  This function de-initializes a critical section.

  @param[in]  cs         Pointer to the critical section to be de-initialized.

  @return
  TRUE if critical section was initialized, FALSE otherwise

*/
/*=========================================================================*/
boolean glink_os_cs_deinit( glink_os_cs_type *cs )
{
  GLINK_OS_ARG_NOT_USED(cs);
  return ( TRUE );
}

/*===========================================================================
FUNCTION      glink_os_cs_acquire
===========================================================================*/
/**
  Lock a critical section

  @param[in]  cs   Pointer the the critical section

  @return     None.
*/
/*=========================================================================*/
void glink_os_cs_acquire( glink_os_cs_type *cs )
{
  GLINK_OS_ARG_NOT_USED(cs);

  qapi_TSK_Enter_Critical();
}

/*===========================================================================
FUNCTION      glink_os_cs_release
===========================================================================*/
/**
  Unlock a critical section

  @param[in]  cs   Pointer the the critical section

  @return     None.
*/
/*=========================================================================*/
void glink_os_cs_release( glink_os_cs_type *cs )
{
  GLINK_OS_ARG_NOT_USED(cs);

  qapi_TSK_Exit_Critical();
}

/*===========================================================================
  FUNCTION      glink_os_register_isr
===========================================================================*/
/**
  Registers ISR with the interrupt controller

  @param[in]  intr      Interrupt to register for
  @param[in]  isr       Callback to be invoked when interrupt fires
  @param[in]  cb_data   Data to be provided to the callback

  @return     TRUE if registration was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_register_isr
(
  const glink_os_ipc_intr_type *intr,
  glink_os_isr_cb_fn           isr,
  void                         *cb_data
)
{
  if ((glink_os_isr_fn != NULL) || (isr == NULL) || (intr  == NULL))
  {
    return (FALSE);
  }

  glink_os_irq_in  = intr->irq_in;
  glink_os_isr_fn  = isr;
  glink_os_isr_ctx = cb_data;
  NVIC_EnableIRQ((IRQn_Type)glink_os_irq_in);

  return (TRUE);
}

/*===========================================================================
  FUNCTION      glink_os_deregister_isr
===========================================================================*/
/**
  De-registers ISR with the interrupt controller

  @param[in]  intr    Interrupt to deregister for

  @return     TRUE if de-registration was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_deregister_isr(const glink_os_ipc_intr_type *intr)
{
  if ( intr && (glink_os_irq_in == intr->irq_in))
  {
    NVIC_DisableIRQ((IRQn_Type)intr->irq_in);
    glink_os_irq_in  = 0;
    glink_os_isr_fn  = NULL;
    glink_os_isr_ctx = NULL;
    return (TRUE);
  }

  return (FALSE);
}

/*===========================================================================
  FUNCTION      glink_os_enable_interrupt
===========================================================================*/
/**
  Enables the interrupt in the interrupt controller

  @param[in]  irq_in    Interrupt to enable

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_enable_interrupt(const glink_os_ipc_intr_type *intr)
{

  if ( intr && (glink_os_irq_in == intr->irq_in))
  {
    NVIC_EnableIRQ((IRQn_Type)intr->irq_in);
    return ( TRUE );
  }
  
  return ( FALSE );
}

/*===========================================================================
  FUNCTION      glink_os_disable_interrupt
===========================================================================*/
/**
  Disables the interrupt in the interrupt controller

  @param[in]  irq_in    Interrupt to disable

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_disable_interrupt(const glink_os_ipc_intr_type *intr)
{
  if ( intr && (glink_os_irq_in == intr->irq_in))
  {
    NVIC_DisableIRQ((IRQn_Type)intr->irq_in);
    return ( TRUE );
  }
  
  return ( FALSE );
}

/*===========================================================================
FUNCTION      glink_os_send_interrupt
===========================================================================*/
/**
  Triggers an IPC interrupt

  @param[in]  intr   Interrupt descriptor

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_send_interrupt(const glink_os_ipc_intr_type *intr)
{
  volatile uint32 *reg_addr = NULL;
  volatile uint32 reg_val   = 0;
  volatile uint32 idx       = 0;
  uint32 reg_mask  = 0;

  if (intr && intr->trig_reg_addr)
  {
    reg_addr = (volatile uint32 *)intr->trig_reg_addr;
    reg_mask = intr->trig_reg_mask;

    /* Set interrupt register to fire interrupt */
    *reg_addr = *reg_addr | reg_mask;

    /* Busy loop */
    /* TODO: Replace with busywait function */
    for (idx = 0; idx < 100; idx++)
    {
      reg_val = *reg_addr;
    }

    /* Clear interrupt register */
    *reg_addr &= ~reg_mask;

    return (TRUE);
  }

  return (FALSE);
}

/*===========================================================================
  FUNCTION      glink_os_clear_interrupt
===========================================================================*/
/**
  Clear the interrupt

  @param[in]  intr    Interrupt descriptor

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_clear_interrupt(const glink_os_ipc_intr_type *intr)
{
  if (intr && intr->clr_reg_addr)
  {
    volatile uint32 *reg_addr = (volatile uint32 *)intr->clr_reg_addr;
    volatile uint32 reg_mask = intr->clr_reg_mask;

    /* Clear interrupt  */
    *reg_addr = ~(reg_mask);
    return (TRUE);
  }

  return (FALSE);
}

/*===========================================================================
  FUNCTION      glink_os_log
===========================================================================*/
/**
  Logging
*/
/*=========================================================================*/
void glink_os_log
(
  uint32 log_level,
  const char *fmt_str,
  uint32 arg0,
  uint32 arg1
)
{
  GLINK_OS_ARG_NOT_USED(log_level);
  GLINK_OS_ARG_NOT_USED(fmt_str);
  GLINK_OS_ARG_NOT_USED(arg0);
  GLINK_OS_ARG_NOT_USED(arg1);
}

