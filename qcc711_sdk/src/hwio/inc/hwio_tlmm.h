#ifndef __HWIO_TLMM_H__
#define __HWIO_TLMM_H__
/*
===========================================================================
*/
/**
  @file hwio_tlmm.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    TLMM

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['TLMM'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_tlmm.h',
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
 * MODULE: TLMM_RELOC
 *--------------------------------------------------------------------------*/

#define TLMM_RELOC_REG_BASE                                        (TLMM_BASE      + 0x00000000)
#define TLMM_RELOC_REG_BASE_SIZE                                   0x100
#define TLMM_RELOC_REG_BASE_USED                                   0xc4

#define HWIO_TLMM_GPIO_CFGm_ADDR(m)                                (TLMM_RELOC_REG_BASE      + 0x00000000 + 0x4 * (m))
#define HWIO_TLMM_GPIO_CFGm_RMSK                                       0x1dff
#define HWIO_TLMM_GPIO_CFGm_MAXm                                           25
#define HWIO_TLMM_GPIO_CFGm_INI(m)        \
        in_dword_masked(HWIO_TLMM_GPIO_CFGm_ADDR(m), HWIO_TLMM_GPIO_CFGm_RMSK)
#define HWIO_TLMM_GPIO_CFGm_INMI(m,mask)    \
        in_dword_masked(HWIO_TLMM_GPIO_CFGm_ADDR(m), mask)
#define HWIO_TLMM_GPIO_CFGm_OUTI(m,val)    \
        out_dword(HWIO_TLMM_GPIO_CFGm_ADDR(m),val)
#define HWIO_TLMM_GPIO_CFGm_OUTMI(m,mask,val) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_CFGm_ADDR(m),mask,val,HWIO_TLMM_GPIO_CFGm_INI(m))
#define HWIO_TLMM_GPIO_CFGm_PO_BMSK                                    0x1000
#define HWIO_TLMM_GPIO_CFGm_PO_SHFT                                       0xc
#define HWIO_TLMM_GPIO_CFGm_IS_BMSK                                     0x800
#define HWIO_TLMM_GPIO_CFGm_IS_SHFT                                       0xb
#define HWIO_TLMM_GPIO_CFGm_POE_BMSK                                    0x400
#define HWIO_TLMM_GPIO_CFGm_POE_SHFT                                      0xa
#define HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_BMSK                           0x1c0
#define HWIO_TLMM_GPIO_CFGm_DRV_STRENGTH_SHFT                             0x6
#define HWIO_TLMM_GPIO_CFGm_FUNC_SEL_BMSK                                0x3c
#define HWIO_TLMM_GPIO_CFGm_FUNC_SEL_SHFT                                 0x2
#define HWIO_TLMM_GPIO_CFGm_GPIO_PULL_BMSK                                0x3
#define HWIO_TLMM_GPIO_CFGm_GPIO_PULL_SHFT                                0x0

#define HWIO_TLMM_GPIO_OE_ADDR                                     (TLMM_RELOC_REG_BASE      + 0x00000068)
#define HWIO_TLMM_GPIO_OE_RMSK                                      0x3ffffff
#define HWIO_TLMM_GPIO_OE_IN          \
        in_dword(HWIO_TLMM_GPIO_OE_ADDR)
#define HWIO_TLMM_GPIO_OE_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OE_ADDR, m)
#define HWIO_TLMM_GPIO_OE_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OE_ADDR,v)
#define HWIO_TLMM_GPIO_OE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OE_ADDR,m,v,HWIO_TLMM_GPIO_OE_IN)
#define HWIO_TLMM_GPIO_OE_DATA_BMSK                                 0x3ffffff
#define HWIO_TLMM_GPIO_OE_DATA_SHFT                                       0x0

#define HWIO_TLMM_GPIO_OUT_ADDR                                    (TLMM_RELOC_REG_BASE      + 0x0000006c)
#define HWIO_TLMM_GPIO_OUT_RMSK                                     0x3ffffff
#define HWIO_TLMM_GPIO_OUT_IN          \
        in_dword(HWIO_TLMM_GPIO_OUT_ADDR)
#define HWIO_TLMM_GPIO_OUT_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_OUT_ADDR, m)
#define HWIO_TLMM_GPIO_OUT_OUT(v)      \
        out_dword(HWIO_TLMM_GPIO_OUT_ADDR,v)
#define HWIO_TLMM_GPIO_OUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_GPIO_OUT_ADDR,m,v,HWIO_TLMM_GPIO_OUT_IN)
#define HWIO_TLMM_GPIO_OUT_DATA_BMSK                                0x3ffffff
#define HWIO_TLMM_GPIO_OUT_DATA_SHFT                                      0x0

#define HWIO_TLMM_GPIO_IN_ADDR                                     (TLMM_RELOC_REG_BASE      + 0x00000070)
#define HWIO_TLMM_GPIO_IN_RMSK                                      0x3ffffff
#define HWIO_TLMM_GPIO_IN_IN          \
        in_dword(HWIO_TLMM_GPIO_IN_ADDR)
#define HWIO_TLMM_GPIO_IN_INM(m)      \
        in_dword_masked(HWIO_TLMM_GPIO_IN_ADDR, m)
#define HWIO_TLMM_GPIO_IN_DATA_BMSK                                 0x3ffffff
#define HWIO_TLMM_GPIO_IN_DATA_SHFT                                       0x0

#define HWIO_SERIAL_ENGINE_0_1_ADDR                                (TLMM_RELOC_REG_BASE      + 0x00000074)
#define HWIO_SERIAL_ENGINE_0_1_RMSK                                0x3fffffff
#define HWIO_SERIAL_ENGINE_0_1_IN          \
        in_dword(HWIO_SERIAL_ENGINE_0_1_ADDR)
#define HWIO_SERIAL_ENGINE_0_1_INM(m)      \
        in_dword_masked(HWIO_SERIAL_ENGINE_0_1_ADDR, m)
#define HWIO_SERIAL_ENGINE_0_1_OUT(v)      \
        out_dword(HWIO_SERIAL_ENGINE_0_1_ADDR,v)
#define HWIO_SERIAL_ENGINE_0_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SERIAL_ENGINE_0_1_ADDR,m,v,HWIO_SERIAL_ENGINE_0_1_IN)
#define HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_BMSK                       0x3fff8000
#define HWIO_SERIAL_ENGINE_0_1_SEL_SE_1_SHFT                              0xf
#define HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_BMSK                           0x7fff
#define HWIO_SERIAL_ENGINE_0_1_SEL_SE_0_SHFT                              0x0

#define HWIO_SERIAL_ENGINE_2_3_ADDR                                (TLMM_RELOC_REG_BASE      + 0x00000078)
#define HWIO_SERIAL_ENGINE_2_3_RMSK                                0x3fffffff
#define HWIO_SERIAL_ENGINE_2_3_IN          \
        in_dword(HWIO_SERIAL_ENGINE_2_3_ADDR)
#define HWIO_SERIAL_ENGINE_2_3_INM(m)      \
        in_dword_masked(HWIO_SERIAL_ENGINE_2_3_ADDR, m)
#define HWIO_SERIAL_ENGINE_2_3_OUT(v)      \
        out_dword(HWIO_SERIAL_ENGINE_2_3_ADDR,v)
#define HWIO_SERIAL_ENGINE_2_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SERIAL_ENGINE_2_3_ADDR,m,v,HWIO_SERIAL_ENGINE_2_3_IN)
#define HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_BMSK                       0x3fff8000
#define HWIO_SERIAL_ENGINE_2_3_SEL_SE_3_SHFT                              0xf
#define HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_BMSK                           0x7fff
#define HWIO_SERIAL_ENGINE_2_3_SEL_SE_2_SHFT                              0x0

#define HWIO_CETIMER_DIR_INT_CTL_ADDR                              (TLMM_RELOC_REG_BASE      + 0x0000007c)
#define HWIO_CETIMER_DIR_INT_CTL_RMSK                                    0x7f
#define HWIO_CETIMER_DIR_INT_CTL_IN          \
        in_dword(HWIO_CETIMER_DIR_INT_CTL_ADDR)
#define HWIO_CETIMER_DIR_INT_CTL_INM(m)      \
        in_dword_masked(HWIO_CETIMER_DIR_INT_CTL_ADDR, m)
#define HWIO_CETIMER_DIR_INT_CTL_OUT(v)      \
        out_dword(HWIO_CETIMER_DIR_INT_CTL_ADDR,v)
#define HWIO_CETIMER_DIR_INT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_CETIMER_DIR_INT_CTL_ADDR,m,v,HWIO_CETIMER_DIR_INT_CTL_IN)
#define HWIO_CETIMER_DIR_INT_CTL_MASK_BMSK                               0x40
#define HWIO_CETIMER_DIR_INT_CTL_MASK_SHFT                                0x6
#define HWIO_CETIMER_DIR_INT_CTL_INT_SRC_SEL_BMSK                        0x3e
#define HWIO_CETIMER_DIR_INT_CTL_INT_SRC_SEL_SHFT                         0x1
#define HWIO_CETIMER_DIR_INT_CTL_POLARITY_BMSK                            0x1
#define HWIO_CETIMER_DIR_INT_CTL_POLARITY_SHFT                            0x0

#define HWIO_TLMM_AON_CTRL_ADDR                                    (TLMM_RELOC_REG_BASE      + 0x00000080)
#define HWIO_TLMM_AON_CTRL_RMSK                                           0xf
#define HWIO_TLMM_AON_CTRL_IN          \
        in_dword(HWIO_TLMM_AON_CTRL_ADDR)
#define HWIO_TLMM_AON_CTRL_INM(m)      \
        in_dword_masked(HWIO_TLMM_AON_CTRL_ADDR, m)
#define HWIO_TLMM_AON_CTRL_OUT(v)      \
        out_dword(HWIO_TLMM_AON_CTRL_ADDR,v)
#define HWIO_TLMM_AON_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_AON_CTRL_ADDR,m,v,HWIO_TLMM_AON_CTRL_IN)
#define HWIO_TLMM_AON_CTRL_EXT_GPIO_SLOW_CLK_ENABLE_BMSK                  0x8
#define HWIO_TLMM_AON_CTRL_EXT_GPIO_SLOW_CLK_ENABLE_SHFT                  0x3
#define HWIO_TLMM_AON_CTRL_DEEPSLEEP_DEBUG_BUS_SEL_BMSK                   0x6
#define HWIO_TLMM_AON_CTRL_DEEPSLEEP_DEBUG_BUS_SEL_SHFT                   0x1
#define HWIO_TLMM_AON_CTRL_PMU_STATUS_CHECK_BYPASS_BMSK                   0x1
#define HWIO_TLMM_AON_CTRL_PMU_STATUS_CHECK_BYPASS_SHFT                   0x0

#define HWIO_BTSS_DIR_INT_CTL_ADDR                                 (TLMM_RELOC_REG_BASE      + 0x00000084)
#define HWIO_BTSS_DIR_INT_CTL_RMSK                                       0x7f
#define HWIO_BTSS_DIR_INT_CTL_IN          \
        in_dword(HWIO_BTSS_DIR_INT_CTL_ADDR)
#define HWIO_BTSS_DIR_INT_CTL_INM(m)      \
        in_dword_masked(HWIO_BTSS_DIR_INT_CTL_ADDR, m)
#define HWIO_BTSS_DIR_INT_CTL_OUT(v)      \
        out_dword(HWIO_BTSS_DIR_INT_CTL_ADDR,v)
#define HWIO_BTSS_DIR_INT_CTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BTSS_DIR_INT_CTL_ADDR,m,v,HWIO_BTSS_DIR_INT_CTL_IN)
#define HWIO_BTSS_DIR_INT_CTL_MASK_BMSK                                  0x40
#define HWIO_BTSS_DIR_INT_CTL_MASK_SHFT                                   0x6
#define HWIO_BTSS_DIR_INT_CTL_INT_SRC_SEL_BMSK                           0x3e
#define HWIO_BTSS_DIR_INT_CTL_INT_SRC_SEL_SHFT                            0x1
#define HWIO_BTSS_DIR_INT_CTL_POLARITY_BMSK                               0x1
#define HWIO_BTSS_DIR_INT_CTL_POLARITY_SHFT                               0x0

#define HWIO_APPSS_MASK_ADDR                                       (TLMM_RELOC_REG_BASE      + 0x00000088)
#define HWIO_APPSS_MASK_RMSK                                        0x3ffffff
#define HWIO_APPSS_MASK_IN          \
        in_dword(HWIO_APPSS_MASK_ADDR)
#define HWIO_APPSS_MASK_INM(m)      \
        in_dword_masked(HWIO_APPSS_MASK_ADDR, m)
#define HWIO_APPSS_MASK_OUT(v)      \
        out_dword(HWIO_APPSS_MASK_ADDR,v)
#define HWIO_APPSS_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APPSS_MASK_ADDR,m,v,HWIO_APPSS_MASK_IN)
#define HWIO_APPSS_MASK_INTERRUPT_BMSK                              0x3ffffff
#define HWIO_APPSS_MASK_INTERRUPT_SHFT                                    0x0

#define HWIO_APPSS_CLR_ADDR                                        (TLMM_RELOC_REG_BASE      + 0x0000008c)
#define HWIO_APPSS_CLR_RMSK                                         0x3ffffff
#define HWIO_APPSS_CLR_OUT(v)      \
        out_dword(HWIO_APPSS_CLR_ADDR,v)
#define HWIO_APPSS_CLR_INTERRUPT_BMSK                               0x3ffffff
#define HWIO_APPSS_CLR_INTERRUPT_SHFT                                     0x0

#define HWIO_APPSS_SET_ADDR                                        (TLMM_RELOC_REG_BASE      + 0x00000090)
#define HWIO_APPSS_SET_RMSK                                         0x3ffffff
#define HWIO_APPSS_SET_IN          \
        in_dword(HWIO_APPSS_SET_ADDR)
#define HWIO_APPSS_SET_INM(m)      \
        in_dword_masked(HWIO_APPSS_SET_ADDR, m)
#define HWIO_APPSS_SET_OUT(v)      \
        out_dword(HWIO_APPSS_SET_ADDR,v)
#define HWIO_APPSS_SET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APPSS_SET_ADDR,m,v,HWIO_APPSS_SET_IN)
#define HWIO_APPSS_SET_INTERRUPT_BMSK                               0x3ffffff
#define HWIO_APPSS_SET_INTERRUPT_SHFT                                     0x0

#define HWIO_APPSS_SUM_ADDR                                        (TLMM_RELOC_REG_BASE      + 0x00000094)
#define HWIO_APPSS_SUM_RMSK                                               0x1
#define HWIO_APPSS_SUM_IN          \
        in_dword(HWIO_APPSS_SUM_ADDR)
#define HWIO_APPSS_SUM_INM(m)      \
        in_dword_masked(HWIO_APPSS_SUM_ADDR, m)
#define HWIO_APPSS_SUM_INTERRUPT_BMSK                                     0x1
#define HWIO_APPSS_SUM_INTERRUPT_SHFT                                     0x0

#define HWIO_APPSS_STAT_ADDR                                       (TLMM_RELOC_REG_BASE      + 0x00000098)
#define HWIO_APPSS_STAT_RMSK                                        0x3ffffff
#define HWIO_APPSS_STAT_IN          \
        in_dword(HWIO_APPSS_STAT_ADDR)
#define HWIO_APPSS_STAT_INM(m)      \
        in_dword_masked(HWIO_APPSS_STAT_ADDR, m)
#define HWIO_APPSS_STAT_INTERRUPT_BMSK                              0x3ffffff
#define HWIO_APPSS_STAT_INTERRUPT_SHFT                                    0x0

#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_ADDR                     (TLMM_RELOC_REG_BASE      + 0x0000009c)
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_RMSK                      0x3ffffff
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_IN          \
        in_dword(HWIO_APPSS_INT_SEL_RISE_FALL_STAT_ADDR)
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_INM(m)      \
        in_dword_masked(HWIO_APPSS_INT_SEL_RISE_FALL_STAT_ADDR, m)
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_OUT(v)      \
        out_dword(HWIO_APPSS_INT_SEL_RISE_FALL_STAT_ADDR,v)
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APPSS_INT_SEL_RISE_FALL_STAT_ADDR,m,v,HWIO_APPSS_INT_SEL_RISE_FALL_STAT_IN)
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_DATA_BMSK                 0x3ffffff
#define HWIO_APPSS_INT_SEL_RISE_FALL_STAT_DATA_SHFT                       0x0

#define HWIO_APPSS_INT_SEL_DUAL_STAT_ADDR                          (TLMM_RELOC_REG_BASE      + 0x000000a0)
#define HWIO_APPSS_INT_SEL_DUAL_STAT_RMSK                           0x3ffffff
#define HWIO_APPSS_INT_SEL_DUAL_STAT_IN          \
        in_dword(HWIO_APPSS_INT_SEL_DUAL_STAT_ADDR)
#define HWIO_APPSS_INT_SEL_DUAL_STAT_INM(m)      \
        in_dword_masked(HWIO_APPSS_INT_SEL_DUAL_STAT_ADDR, m)
#define HWIO_APPSS_INT_SEL_DUAL_STAT_OUT(v)      \
        out_dword(HWIO_APPSS_INT_SEL_DUAL_STAT_ADDR,v)
#define HWIO_APPSS_INT_SEL_DUAL_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APPSS_INT_SEL_DUAL_STAT_ADDR,m,v,HWIO_APPSS_INT_SEL_DUAL_STAT_IN)
#define HWIO_APPSS_INT_SEL_DUAL_STAT_DATA_BMSK                      0x3ffffff
#define HWIO_APPSS_INT_SEL_DUAL_STAT_DATA_SHFT                            0x0

#define HWIO_TAD_SUM_INT_ADDR                                      (TLMM_RELOC_REG_BASE      + 0x000000a4)
#define HWIO_TAD_SUM_INT_RMSK                                       0x3ffffff
#define HWIO_TAD_SUM_INT_IN          \
        in_dword(HWIO_TAD_SUM_INT_ADDR)
#define HWIO_TAD_SUM_INT_INM(m)      \
        in_dword_masked(HWIO_TAD_SUM_INT_ADDR, m)
#define HWIO_TAD_SUM_INT_OUT(v)      \
        out_dword(HWIO_TAD_SUM_INT_ADDR,v)
#define HWIO_TAD_SUM_INT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TAD_SUM_INT_ADDR,m,v,HWIO_TAD_SUM_INT_IN)
#define HWIO_TAD_SUM_INT_MASK_BMSK                                  0x3ffffff
#define HWIO_TAD_SUM_INT_MASK_SHFT                                        0x0

#define HWIO_TAD_INT_ADDR                                          (TLMM_RELOC_REG_BASE      + 0x000000a8)
#define HWIO_TAD_INT_RMSK                                           0x3ffffff
#define HWIO_TAD_INT_IN          \
        in_dword(HWIO_TAD_INT_ADDR)
#define HWIO_TAD_INT_INM(m)      \
        in_dword_masked(HWIO_TAD_INT_ADDR, m)
#define HWIO_TAD_INT_OUT(v)      \
        out_dword(HWIO_TAD_INT_ADDR,v)
#define HWIO_TAD_INT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TAD_INT_ADDR,m,v,HWIO_TAD_INT_IN)
#define HWIO_TAD_INT_CLR_BMSK                                       0x3ffffff
#define HWIO_TAD_INT_CLR_SHFT                                             0x0

#define HWIO_TAD_FALL_ADDR                                         (TLMM_RELOC_REG_BASE      + 0x000000ac)
#define HWIO_TAD_FALL_RMSK                                          0x3ffffff
#define HWIO_TAD_FALL_IN          \
        in_dword(HWIO_TAD_FALL_ADDR)
#define HWIO_TAD_FALL_INM(m)      \
        in_dword_masked(HWIO_TAD_FALL_ADDR, m)
#define HWIO_TAD_FALL_STATUS_BMSK                                   0x3ffffff
#define HWIO_TAD_FALL_STATUS_SHFT                                         0x0

#define HWIO_TAD_RISE_ADDR                                         (TLMM_RELOC_REG_BASE      + 0x000000b0)
#define HWIO_TAD_RISE_RMSK                                          0x3ffffff
#define HWIO_TAD_RISE_IN          \
        in_dword(HWIO_TAD_RISE_ADDR)
#define HWIO_TAD_RISE_INM(m)      \
        in_dword_masked(HWIO_TAD_RISE_ADDR, m)
#define HWIO_TAD_RISE_STATUS_BMSK                                   0x3ffffff
#define HWIO_TAD_RISE_STATUS_SHFT                                         0x0

#define HWIO_JTAG_MUX_CTRL_ADDR                                    (TLMM_RELOC_REG_BASE      + 0x000000b8)
#define HWIO_JTAG_MUX_CTRL_RMSK                                         0x3ff
#define HWIO_JTAG_MUX_CTRL_IN          \
        in_dword(HWIO_JTAG_MUX_CTRL_ADDR)
#define HWIO_JTAG_MUX_CTRL_INM(m)      \
        in_dword_masked(HWIO_JTAG_MUX_CTRL_ADDR, m)
#define HWIO_JTAG_MUX_CTRL_OUT(v)      \
        out_dword(HWIO_JTAG_MUX_CTRL_ADDR,v)
#define HWIO_JTAG_MUX_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_JTAG_MUX_CTRL_ADDR,m,v,HWIO_JTAG_MUX_CTRL_IN)
#define HWIO_JTAG_MUX_CTRL_TAPS_LOCK_NO_SCAN_BMSK                       0x200
#define HWIO_JTAG_MUX_CTRL_TAPS_LOCK_NO_SCAN_SHFT                         0x9
#define HWIO_JTAG_MUX_CTRL_SWD_LOCK_NO_SCAN_BMSK                        0x100
#define HWIO_JTAG_MUX_CTRL_SWD_LOCK_NO_SCAN_SHFT                          0x8
#define HWIO_JTAG_MUX_CTRL_DFLT_JTAG_DISABLE_NO_SCAN_BMSK                0x80
#define HWIO_JTAG_MUX_CTRL_DFLT_JTAG_DISABLE_NO_SCAN_SHFT                 0x7
#define HWIO_JTAG_MUX_CTRL_JTAG_OVRD_EN_NO_SCAN_BMSK                     0x40
#define HWIO_JTAG_MUX_CTRL_JTAG_OVRD_EN_NO_SCAN_SHFT                      0x6
#define HWIO_JTAG_MUX_CTRL_JTAG_MUX_SEL_BMSK                             0x20
#define HWIO_JTAG_MUX_CTRL_JTAG_MUX_SEL_SHFT                              0x5
#define HWIO_JTAG_MUX_CTRL_SWJDP_MUX_SEL_BMSK                            0x10
#define HWIO_JTAG_MUX_CTRL_SWJDP_MUX_SEL_SHFT                             0x4
#define HWIO_JTAG_MUX_CTRL_JTAG_AP_PORT_SEL_BMSK                          0x8
#define HWIO_JTAG_MUX_CTRL_JTAG_AP_PORT_SEL_SHFT                          0x3
#define HWIO_JTAG_MUX_CTRL_DAISY_CHAIN_SEL_BMSK                           0x4
#define HWIO_JTAG_MUX_CTRL_DAISY_CHAIN_SEL_SHFT                           0x2
#define HWIO_JTAG_MUX_CTRL_JTAG_OR_SWJDPN_BMSK                            0x2
#define HWIO_JTAG_MUX_CTRL_JTAG_OR_SWJDPN_SHFT                            0x1
#define HWIO_JTAG_MUX_CTRL_ALT_JTAG_SEL_BMSK                              0x1
#define HWIO_JTAG_MUX_CTRL_ALT_JTAG_SEL_SHFT                              0x0

#define HWIO_SE_0_PRIORITY_MUX_ADDR                                (TLMM_RELOC_REG_BASE      + 0x000000bc)
#define HWIO_SE_0_PRIORITY_MUX_RMSK                                       0x3
#define HWIO_SE_0_PRIORITY_MUX_IN          \
        in_dword(HWIO_SE_0_PRIORITY_MUX_ADDR)
#define HWIO_SE_0_PRIORITY_MUX_INM(m)      \
        in_dword_masked(HWIO_SE_0_PRIORITY_MUX_ADDR, m)
#define HWIO_SE_0_PRIORITY_MUX_OUT(v)      \
        out_dword(HWIO_SE_0_PRIORITY_MUX_ADDR,v)
#define HWIO_SE_0_PRIORITY_MUX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SE_0_PRIORITY_MUX_ADDR,m,v,HWIO_SE_0_PRIORITY_MUX_IN)
#define HWIO_SE_0_PRIORITY_MUX_FB_CLK_EN_BMSK                             0x2
#define HWIO_SE_0_PRIORITY_MUX_FB_CLK_EN_SHFT                             0x1
#define HWIO_SE_0_PRIORITY_MUX_SELECT_BMSK                                0x1
#define HWIO_SE_0_PRIORITY_MUX_SELECT_SHFT                                0x0

#define HWIO_SE_1_PRIORITY_MUX_ADDR                                (TLMM_RELOC_REG_BASE      + 0x000000c0)
#define HWIO_SE_1_PRIORITY_MUX_RMSK                                       0x3
#define HWIO_SE_1_PRIORITY_MUX_IN          \
        in_dword(HWIO_SE_1_PRIORITY_MUX_ADDR)
#define HWIO_SE_1_PRIORITY_MUX_INM(m)      \
        in_dword_masked(HWIO_SE_1_PRIORITY_MUX_ADDR, m)
#define HWIO_SE_1_PRIORITY_MUX_OUT(v)      \
        out_dword(HWIO_SE_1_PRIORITY_MUX_ADDR,v)
#define HWIO_SE_1_PRIORITY_MUX_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SE_1_PRIORITY_MUX_ADDR,m,v,HWIO_SE_1_PRIORITY_MUX_IN)
#define HWIO_SE_1_PRIORITY_MUX_FB_CLK_EN_BMSK                             0x2
#define HWIO_SE_1_PRIORITY_MUX_FB_CLK_EN_SHFT                             0x1
#define HWIO_SE_1_PRIORITY_MUX_SELECT_BMSK                                0x1
#define HWIO_SE_1_PRIORITY_MUX_SELECT_SHFT                                0x0

#define HWIO_GPIO_MODE_NO_SCAN_ADDR                                (TLMM_RELOC_REG_BASE      + 0x000000c4)
#define HWIO_GPIO_MODE_NO_SCAN_RMSK                                      0x3f
#define HWIO_GPIO_MODE_NO_SCAN_IN          \
        in_dword(HWIO_GPIO_MODE_NO_SCAN_ADDR)
#define HWIO_GPIO_MODE_NO_SCAN_INM(m)      \
        in_dword_masked(HWIO_GPIO_MODE_NO_SCAN_ADDR, m)
#define HWIO_GPIO_MODE_NO_SCAN_OUT(v)      \
        out_dword(HWIO_GPIO_MODE_NO_SCAN_ADDR,v)
#define HWIO_GPIO_MODE_NO_SCAN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_GPIO_MODE_NO_SCAN_ADDR,m,v,HWIO_GPIO_MODE_NO_SCAN_IN)
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_25_BMSK                            0x20
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_25_SHFT                             0x5
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_24_BMSK                            0x10
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_24_SHFT                             0x4
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_23_BMSK                             0x8
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_23_SHFT                             0x3
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_22_BMSK                             0x4
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_22_SHFT                             0x2
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_21_BMSK                             0x2
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_21_SHFT                             0x1
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_20_BMSK                             0x1
#define HWIO_GPIO_MODE_NO_SCAN_ANALOG_20_SHFT                             0x0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_TME
 *--------------------------------------------------------------------------*/

#define TLMM_TME_REG_BASE    (TLMM_BASE      + 0x00000100)
#define TLMM_TME_REG_BASE_SIZE 0x100
#define TLMM_TME_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_BT
 *--------------------------------------------------------------------------*/

#define TLMM_BT_REG_BASE     (TLMM_BASE      + 0x00000400)
#define TLMM_BT_REG_BASE_SIZE 0x100
#define TLMM_BT_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_APPS
 *--------------------------------------------------------------------------*/

#define TLMM_APPS_REG_BASE   (TLMM_BASE      + 0x00000800)
#define TLMM_APPS_REG_BASE_SIZE 0x100
#define TLMM_APPS_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: TLMM_ALL
 *--------------------------------------------------------------------------*/

#define TLMM_ALL_REG_BASE                                          (TLMM_BASE      + 0x00000c00)
#define TLMM_ALL_REG_BASE_SIZE                                     0x100
#define TLMM_ALL_REG_BASE_USED                                     0xc

#define HWIO_TLMM_HW_REVISION_NUMBER_ADDR                          (TLMM_ALL_REG_BASE      + 0x00000000)
#define HWIO_TLMM_HW_REVISION_NUMBER_RMSK                          0xffffffff
#define HWIO_TLMM_HW_REVISION_NUMBER_IN          \
        in_dword(HWIO_TLMM_HW_REVISION_NUMBER_ADDR)
#define HWIO_TLMM_HW_REVISION_NUMBER_INM(m)      \
        in_dword_masked(HWIO_TLMM_HW_REVISION_NUMBER_ADDR, m)
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_BMSK               0xf0000000
#define HWIO_TLMM_HW_REVISION_NUMBER_VERSION_ID_SHFT                     0x1c
#define HWIO_TLMM_HW_REVISION_NUMBER_PROD_DEVICE_ID_BMSK            0xffff000
#define HWIO_TLMM_HW_REVISION_NUMBER_PROD_DEVICE_ID_SHFT                  0xc
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_BMSK               0xffe
#define HWIO_TLMM_HW_REVISION_NUMBER_QUALCOMM_MFG_ID_SHFT                 0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_BMSK                       0x1
#define HWIO_TLMM_HW_REVISION_NUMBER_START_BIT_SHFT                       0x0

#define HWIO_JTAG_ID_ADDR                                          (TLMM_ALL_REG_BASE      + 0x00000004)
#define HWIO_JTAG_ID_RMSK                                          0xffffffff
#define HWIO_JTAG_ID_IN          \
        in_dword(HWIO_JTAG_ID_ADDR)
#define HWIO_JTAG_ID_INM(m)      \
        in_dword_masked(HWIO_JTAG_ID_ADDR, m)
#define HWIO_JTAG_ID_VERSION_ID_BMSK                               0xf0000000
#define HWIO_JTAG_ID_VERSION_ID_SHFT                                     0x1c
#define HWIO_JTAG_ID_PROD_DEVICE_ID_BMSK                            0xffff000
#define HWIO_JTAG_ID_PROD_DEVICE_ID_SHFT                                  0xc
#define HWIO_JTAG_ID_QUALCOMM_MFG_ID_BMSK                               0xffe
#define HWIO_JTAG_ID_QUALCOMM_MFG_ID_SHFT                                 0x1
#define HWIO_JTAG_ID_START_BIT_BMSK                                       0x1
#define HWIO_JTAG_ID_START_BIT_SHFT                                       0x0

#define HWIO_TCSR_SOC_HW_VERSION_REG_ADDR                          (TLMM_ALL_REG_BASE      + 0x00000008)
#define HWIO_TCSR_SOC_HW_VERSION_REG_RMSK                          0xffffffff
#define HWIO_TCSR_SOC_HW_VERSION_REG_IN          \
        in_dword(HWIO_TCSR_SOC_HW_VERSION_REG_ADDR)
#define HWIO_TCSR_SOC_HW_VERSION_REG_INM(m)      \
        in_dword_masked(HWIO_TCSR_SOC_HW_VERSION_REG_ADDR, m)
#define HWIO_TCSR_SOC_HW_VERSION_REG_FAMILY_NUMBER_BMSK            0xf0000000
#define HWIO_TCSR_SOC_HW_VERSION_REG_FAMILY_NUMBER_SHFT                  0x1c
#define HWIO_TCSR_SOC_HW_VERSION_REG_DEVICE_NUMBER_BMSK             0xfff0000
#define HWIO_TCSR_SOC_HW_VERSION_REG_DEVICE_NUMBER_SHFT                  0x10
#define HWIO_TCSR_SOC_HW_VERSION_REG_MAJOR_VERSION_BMSK                0xff00
#define HWIO_TCSR_SOC_HW_VERSION_REG_MAJOR_VERSION_SHFT                   0x8
#define HWIO_TCSR_SOC_HW_VERSION_REG_MINOR_VERSION_BMSK                  0xff
#define HWIO_TCSR_SOC_HW_VERSION_REG_MINOR_VERSION_SHFT                   0x0

#define HWIO_INSTANCE_ID_ADDR                                      (TLMM_ALL_REG_BASE      + 0x0000000c)
#define HWIO_INSTANCE_ID_RMSK                                             0xf
#define HWIO_INSTANCE_ID_IN          \
        in_dword(HWIO_INSTANCE_ID_ADDR)
#define HWIO_INSTANCE_ID_INM(m)      \
        in_dword_masked(HWIO_INSTANCE_ID_ADDR, m)
#define HWIO_INSTANCE_ID_OUT(v)      \
        out_dword(HWIO_INSTANCE_ID_ADDR,v)
#define HWIO_INSTANCE_ID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INSTANCE_ID_ADDR,m,v,HWIO_INSTANCE_ID_IN)
#define HWIO_INSTANCE_ID_DATA_BMSK                                        0xf
#define HWIO_INSTANCE_ID_DATA_SHFT                                        0x0


#endif /* __HWIO_TLMM_H__ */
