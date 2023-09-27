#ifndef __HWIO_TME_IPC_H__
#define __HWIO_TME_IPC_H__
/*
===========================================================================
*/
/**
  @file hwio_tme_ipc.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    TMELITE_IPC_EXTERNAL

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['TMELITE_IPC_EXTERNAL'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_tme_ipc.h',
    'header': '#include "HALhwio.h"\n#include "hwio_base.h"',
    'output_fvals': True}
*/
/*
  ===========================================================================

  Copyright (c) 2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

#include "HALhwio.h"
#include "hwio_base.h"

/*----------------------------------------------------------------------------
 * MODULE: TMELITE_IPC_EXTERNAL
 *--------------------------------------------------------------------------*/

#define TMELITE_IPC_EXTERNAL_REG_BASE          (TMELITE_IPC_EXTERNAL_BASE      + 0x00000000)
#define TMELITE_IPC_EXTERNAL_REG_BASE_SIZE     0x2000
#define TMELITE_IPC_EXTERNAL_REG_BASE_USED     0x101c

#define HWIO_IN_MBOX_WORDw_ADDR(w)             (TMELITE_IPC_EXTERNAL_REG_BASE      + 0x00000000 + 0x4 * (w))
#define HWIO_IN_MBOX_WORDw_RMSK                0xffffffff
#define HWIO_IN_MBOX_WORDw_MAXw                         7
#define HWIO_IN_MBOX_WORDw_INI(w)        \
        in_dword_masked(HWIO_IN_MBOX_WORDw_ADDR(w), HWIO_IN_MBOX_WORDw_RMSK)
#define HWIO_IN_MBOX_WORDw_INMI(w,mask)    \
        in_dword_masked(HWIO_IN_MBOX_WORDw_ADDR(w), mask)
#define HWIO_IN_MBOX_WORDw_OUTI(w,val)    \
        out_dword(HWIO_IN_MBOX_WORDw_ADDR(w),val)
#define HWIO_IN_MBOX_WORDw_OUTMI(w,mask,val) \
        out_dword_masked_ns(HWIO_IN_MBOX_WORDw_ADDR(w),mask,val,HWIO_IN_MBOX_WORDw_INI(w))
#define HWIO_IN_MBOX_WORDw_DATA_BMSK           0xffffffff
#define HWIO_IN_MBOX_WORDw_DATA_SHFT                  0x0

#define HWIO_OUT_MBOX_WORDw_ADDR(w)            (TMELITE_IPC_EXTERNAL_REG_BASE      + 0x00001000 + 0x4 * (w))
#define HWIO_OUT_MBOX_WORDw_RMSK               0xffffffff
#define HWIO_OUT_MBOX_WORDw_MAXw                        7
#define HWIO_OUT_MBOX_WORDw_INI(w)        \
        in_dword_masked(HWIO_OUT_MBOX_WORDw_ADDR(w), HWIO_OUT_MBOX_WORDw_RMSK)
#define HWIO_OUT_MBOX_WORDw_INMI(w,mask)    \
        in_dword_masked(HWIO_OUT_MBOX_WORDw_ADDR(w), mask)
#define HWIO_OUT_MBOX_WORDw_DATA_BMSK          0xffffffff
#define HWIO_OUT_MBOX_WORDw_DATA_SHFT                 0x0


#endif /* __HWIO_TME_IPC_H__ */
