/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef GLINK_OS_UTILS_H
#define GLINK_OS_UTILS_H

/*===========================================================================

                      GLink OS Specific types/functions

===========================================================================*/


/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.sdc/4.0/mproc/glink/inc/glink_os_utils.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/22/16    dks     Initial version.
===========================================================================*/


/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stringl.h>
#include "glink.h"
#if defined(FEATURE_SIMULATOR_WIN32) || defined(FEATURE_SIMULATOR_LINUX)
#include "SimDefs.h"
#endif

/*===========================================================================
                        MACRO DEFINITIONS
===========================================================================*/
#ifndef TRUE
#define TRUE                       1
#endif

#ifndef FALSE
#define FALSE                      0
#endif

#define ROUNDUP64(d) (((d) + 7) & (~7))
#define ROUNDUP32(d) (((d) + 3) & (~3))

#define ALIGNED32(d) ((d&0x3) == 0)
#define ALIGNED64(d) ((d&0x7) == 0)
#define ALIGNED(x,d) (ALIGNED##x(d))

#ifndef ASSERT
#define ASSERT(cond) \
  do { \
    if (!(cond)) \
    { \
    } \
  } while(0)
#endif

#define GLINK_OS_ARG_NOT_USED(arg) \
    do {(arg) = (arg);} while(0)

/** Logging */
#define GLINK_OS_LOG_LEVEL_DBG     0
#define GLINK_OS_LOG_LEVEL_INFO    1
#define GLINK_OS_LOG_LEVEL_ERR     2
#define GLINK_OS_LOG_LEVEL_FATAL   3

#ifdef GLINK_OS_LOG
#define GLINK_OS_LOG_DBG(fmt_str, arg0, arg1)    \
          glink_os_log(GLINK_OS_LOG_LEVEL_DBG, fmt_str, (uint32)arg0, (uint32)arg1)

#define GLINK_OS_LOG_INFO(fmt_str, arg0, arg1)    \
          glink_os_log(GLINK_OS_LOG_LEVEL_INFO, fmt_str, (uint32)arg0, (uint32)arg1)

#define GLINK_OS_LOG_ERR(fmt_str, arg0, arg1)    \
          glink_os_log(GLINK_OS_LOG_LEVEL_ERR, fmt_str, (uint32)arg0, (uint32)arg1)

#define GLINK_OS_LOG_FATAL(fmt_str, arg0, arg1)    \
        glink_os_log(GLINK_OS_LOG_LEVEL_FATAL, fmt_str, (uint32)arg0, (uint32)arg1)
#else
#define GLINK_OS_LOG_DBG(fmt_str, arg0, arg1)

#define GLINK_OS_LOG_INFO(fmt_str, arg0, arg1)  

#define GLINK_OS_LOG_ERR(fmt_str, arg0, arg1)

#define GLINK_OS_LOG_FATAL(fmt_str, arg0, arg1)
#endif


#define glink_os_malloc(size) malloc(size)

#define glink_os_free(ptr) free(ptr)

#define glink_os_mem_copy(dst, dst_len, src, copy_len) \
            memscpy(dst, dst_len, src, copy_len)

#define glink_os_mem_set(ptr, value, size) \
            memset(ptr, value, size)

#define glink_os_strcmp(str1, str2) \
            strcmp(str1, str2)

/*===========================================================================
                           TYPE DEFINITIONS
===========================================================================*/
typedef struct os_ipc_intr_struct
{
  void   *trig_reg_addr;      /* Trigger interrupt register address        */
  uint32 trig_reg_mask;       /* Trigger interrupt register mask           */
  void   *clr_reg_addr;       /* Incoming interrupt clear register address */
  uint32 clr_reg_mask;        /* Incoming interrupt clear register mask    */
  uint32 irq_in;              /* Incoming interrupt number                 */
} glink_os_ipc_intr_type;

typedef void ( *glink_os_isr_cb_fn )( void *cb_data );
typedef void* glink_os_cs_type;

/*===========================================================================
                    EXTERNAL VARIABLE DEFINITIONS
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
void glink_os_init(void);

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
boolean glink_os_cs_init( glink_os_cs_type *cs );

/*===========================================================================
  FUNCTION      glink_os_cs_init
===========================================================================*/
/**
  Initializes a Critical Section

  @param[in]  cs   pointer to critical section object allocated by caller.

  @return
  TRUE if critical section was de-initialized, FALSE otherwise
*/
/*=========================================================================*/
boolean glink_os_cs_deinit( glink_os_cs_type *cs );

/*===========================================================================
  FUNCTION      glink_os_cs_acquire
===========================================================================*/
/**
  Lock a critical section

  @param[in]  cs   Pointer the the critical section

  @return     None.
*/
/*=========================================================================*/
void glink_os_cs_acquire( glink_os_cs_type *cs );

/*===========================================================================
  FUNCTION      glink_os_cs_release
===========================================================================*/
/**
  Unlock a critical section

  @param[in]  cs   Pointer the the critical section

  @return     None.
*/
/*=========================================================================*/
void glink_os_cs_release( glink_os_cs_type *cs );

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
);

/*===========================================================================
  FUNCTION      glink_os_deregister_isr
===========================================================================*/
/**
  De-registers ISR with the interrupt controller

  @param[in]  intr    Interrupt to deregister for

  @return     TRUE if de-registration was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_deregister_isr(const glink_os_ipc_intr_type *intr);

/*===========================================================================
  FUNCTION      glink_os_enable_interrupt
===========================================================================*/
/**
  Enables the interrupt in the interrupt controller

  @param[in]  intr      Interrupt to enable

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_enable_interrupt(const glink_os_ipc_intr_type *intr);

/*===========================================================================
  FUNCTION      glink_os_disable_interrupt
===========================================================================*/
/**
  Disables the interrupt in the interrupt controller

  @param[in]  intr    Interrupt to disable

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_disable_interrupt(const glink_os_ipc_intr_type *intr);

/*===========================================================================
  FUNCTION      glink_os_send_interrupt
===========================================================================*/
/**
  Triggers an IPC interrupt

  @param[in]  irq_out   Interrupt descriptor

  @return     None.
*/
/*=========================================================================*/
boolean glink_os_send_interrupt(const glink_os_ipc_intr_type *intr);

/*===========================================================================
  FUNCTION      glink_os_clear_interrupt
===========================================================================*/
/**
  Clear the interrupt

  @param[in]  irq_in    Interrupt data

  @return     TRUE if operation was successful, FALSE otherwise.
*/
/*=========================================================================*/
boolean glink_os_clear_interrupt(const glink_os_ipc_intr_type *intr);

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
);

#endif /* GLINK_OS_UTILS_H */
