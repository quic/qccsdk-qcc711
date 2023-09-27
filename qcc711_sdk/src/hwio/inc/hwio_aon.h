#ifndef __HWIO_AON_H__
#define __HWIO_AON_H__
/*
===========================================================================
*/
/**
  @file hwio_aon.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    AON.*
    NAON.*

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['AON.*', 'NAON.*'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_aon.h',
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
 * MODULE: AON_TCSR_TCSR_RELOC
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_RELOC_REG_BASE                (AON_TCSR_TCSR_BASE      + 0x00000000)
#define AON_TCSR_TCSR_RELOC_REG_BASE_SIZE           0x100
#define AON_TCSR_TCSR_RELOC_REG_BASE_USED           0x0

#define HWIO_AON_TCSR_NAON_DBG_ADDR                 (AON_TCSR_TCSR_RELOC_REG_BASE      + 0x00000000)
#define HWIO_AON_TCSR_NAON_DBG_RMSK                        0xf
#define HWIO_AON_TCSR_NAON_DBG_IN          \
        in_dword(HWIO_AON_TCSR_NAON_DBG_ADDR)
#define HWIO_AON_TCSR_NAON_DBG_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_NAON_DBG_ADDR, m)
#define HWIO_AON_TCSR_NAON_DBG_OUT(v)      \
        out_dword(HWIO_AON_TCSR_NAON_DBG_ADDR,v)
#define HWIO_AON_TCSR_NAON_DBG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_NAON_DBG_ADDR,m,v,HWIO_AON_TCSR_NAON_DBG_IN)
#define HWIO_AON_TCSR_NAON_DBG_SOURCE_BMSK                 0xf
#define HWIO_AON_TCSR_NAON_DBG_SOURCE_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_TCSR_TCSR_TME
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_TME_REG_BASE                                        (AON_TCSR_TCSR_BASE      + 0x00000100)
#define AON_TCSR_TCSR_TME_REG_BASE_SIZE                                   0x100
#define AON_TCSR_TCSR_TME_REG_BASE_USED                                   0x50

#define HWIO_AON_TCSR_IPC_TME_TO_BT_ADDR                                  (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000000)
#define HWIO_AON_TCSR_IPC_TME_TO_BT_RMSK                                         0x1
#define HWIO_AON_TCSR_IPC_TME_TO_BT_IN          \
        in_dword(HWIO_AON_TCSR_IPC_TME_TO_BT_ADDR)
#define HWIO_AON_TCSR_IPC_TME_TO_BT_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_IPC_TME_TO_BT_ADDR, m)
#define HWIO_AON_TCSR_IPC_TME_TO_BT_OUT(v)      \
        out_dword(HWIO_AON_TCSR_IPC_TME_TO_BT_ADDR,v)
#define HWIO_AON_TCSR_IPC_TME_TO_BT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_IPC_TME_TO_BT_ADDR,m,v,HWIO_AON_TCSR_IPC_TME_TO_BT_IN)
#define HWIO_AON_TCSR_IPC_TME_TO_BT_EVENT_BMSK                                   0x1
#define HWIO_AON_TCSR_IPC_TME_TO_BT_EVENT_SHFT                                   0x0

#define HWIO_AON_TCSR_IPC_TME_TO_APPS_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000004)
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_RMSK                                       0x1
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_IN          \
        in_dword(HWIO_AON_TCSR_IPC_TME_TO_APPS_ADDR)
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_IPC_TME_TO_APPS_ADDR, m)
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_OUT(v)      \
        out_dword(HWIO_AON_TCSR_IPC_TME_TO_APPS_ADDR,v)
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_IPC_TME_TO_APPS_ADDR,m,v,HWIO_AON_TCSR_IPC_TME_TO_APPS_IN)
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_EVENT_BMSK                                 0x1
#define HWIO_AON_TCSR_IPC_TME_TO_APPS_EVENT_SHFT                                 0x0

#define HWIO_AON_TCSR_AC_RSTORE_CSR_ADDR                                  (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000008)
#define HWIO_AON_TCSR_AC_RSTORE_CSR_RMSK                                       0x1ff
#define HWIO_AON_TCSR_AC_RSTORE_CSR_IN          \
        in_dword(HWIO_AON_TCSR_AC_RSTORE_CSR_ADDR)
#define HWIO_AON_TCSR_AC_RSTORE_CSR_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_AC_RSTORE_CSR_ADDR, m)
#define HWIO_AON_TCSR_AC_RSTORE_CSR_OUT(v)      \
        out_dword(HWIO_AON_TCSR_AC_RSTORE_CSR_ADDR,v)
#define HWIO_AON_TCSR_AC_RSTORE_CSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_AC_RSTORE_CSR_ADDR,m,v,HWIO_AON_TCSR_AC_RSTORE_CSR_IN)
#define HWIO_AON_TCSR_AC_RSTORE_CSR_BUSY_BMSK                                  0x100
#define HWIO_AON_TCSR_AC_RSTORE_CSR_BUSY_SHFT                                    0x8
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AHB_ERROR_BMSK                              0x80
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AHB_ERROR_SHFT                               0x7
#define HWIO_AON_TCSR_AC_RSTORE_CSR_CLR_ERROR_BMSK                              0x40
#define HWIO_AON_TCSR_AC_RSTORE_CSR_CLR_ERROR_SHFT                               0x6
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_RESTORE_CLR_DONE_BMSK                 0x20
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_RESTORE_CLR_DONE_SHFT                  0x5
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_RESTORE_DONE_BMSK                     0x10
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_RESTORE_DONE_SHFT                      0x4
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_SW_START_BMSK                          0x8
#define HWIO_AON_TCSR_AC_RSTORE_CSR_VTRIM_SW_START_SHFT                          0x3
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_RESTORE_CLR_DONE_BMSK                     0x4
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_RESTORE_CLR_DONE_SHFT                     0x2
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_RESTORE_DONE_BMSK                         0x2
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_RESTORE_DONE_SHFT                         0x1
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_SW_START_BMSK                             0x1
#define HWIO_AON_TCSR_AC_RSTORE_CSR_AC_SW_START_SHFT                             0x0

#define HWIO_AON_TCSR_AC_CTRL_ADDR                                        (AON_TCSR_TCSR_TME_REG_BASE      + 0x0000000c)
#define HWIO_AON_TCSR_AC_CTRL_RMSK                                               0x3
#define HWIO_AON_TCSR_AC_CTRL_IN          \
        in_dword(HWIO_AON_TCSR_AC_CTRL_ADDR)
#define HWIO_AON_TCSR_AC_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_AC_CTRL_ADDR, m)
#define HWIO_AON_TCSR_AC_CTRL_OUT(v)      \
        out_dword(HWIO_AON_TCSR_AC_CTRL_ADDR,v)
#define HWIO_AON_TCSR_AC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_AC_CTRL_ADDR,m,v,HWIO_AON_TCSR_AC_CTRL_IN)
#define HWIO_AON_TCSR_AC_CTRL_SECURITY_EVT_CLR_BMSK                              0x2
#define HWIO_AON_TCSR_AC_CTRL_SECURITY_EVT_CLR_SHFT                              0x1
#define HWIO_AON_TCSR_AC_CTRL_SECURITY_EVT_EN_BMSK                               0x1
#define HWIO_AON_TCSR_AC_CTRL_SECURITY_EVT_EN_SHFT                               0x0

#define HWIO_AON_TCSR_AC_STATUS_ADDR                                      (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000010)
#define HWIO_AON_TCSR_AC_STATUS_RMSK                                         0x7ffff
#define HWIO_AON_TCSR_AC_STATUS_IN          \
        in_dword(HWIO_AON_TCSR_AC_STATUS_ADDR)
#define HWIO_AON_TCSR_AC_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_AC_STATUS_ADDR, m)
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_VIOL_MID_BMSK                       0x60000
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_VIOL_MID_SHFT                          0x11
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_VIOL_ADDR_BMSK                      0x1fffe
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_VIOL_ADDR_SHFT                          0x1
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_STATUS_BMSK                             0x1
#define HWIO_AON_TCSR_AC_STATUS_SECURITY_STATUS_SHFT                             0x0

#define HWIO_AON_TCSR_CLK_ENABLE_TME_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000014)
#define HWIO_AON_TCSR_CLK_ENABLE_TME_RMSK                                        0x3
#define HWIO_AON_TCSR_CLK_ENABLE_TME_IN          \
        in_dword(HWIO_AON_TCSR_CLK_ENABLE_TME_ADDR)
#define HWIO_AON_TCSR_CLK_ENABLE_TME_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_CLK_ENABLE_TME_ADDR, m)
#define HWIO_AON_TCSR_CLK_ENABLE_TME_OUT(v)      \
        out_dword(HWIO_AON_TCSR_CLK_ENABLE_TME_ADDR,v)
#define HWIO_AON_TCSR_CLK_ENABLE_TME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_CLK_ENABLE_TME_ADDR,m,v,HWIO_AON_TCSR_CLK_ENABLE_TME_IN)
#define HWIO_AON_TCSR_CLK_ENABLE_TME_ACRESTORE_BMSK                              0x2
#define HWIO_AON_TCSR_CLK_ENABLE_TME_ACRESTORE_SHFT                              0x1
#define HWIO_AON_TCSR_CLK_ENABLE_TME_EFUSE_BMSK                                  0x1
#define HWIO_AON_TCSR_CLK_ENABLE_TME_EFUSE_SHFT                                  0x0

#define HWIO_AON_TCSR_ACC_CTRL_TCSR_ADDR                                  (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000018)
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_RMSK                                         0x3
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_TCSR_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_TCSR_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_TCSR_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_TCSR_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_TCSR_IN)
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_DATA_BMSK                                    0x3
#define HWIO_AON_TCSR_ACC_CTRL_TCSR_DATA_SHFT                                    0x0

#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_ADDR                               (AON_TCSR_TCSR_TME_REG_BASE      + 0x0000001c)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_RMSK                               0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_IN)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_DATA_BMSK                          0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_0_DATA_SHFT                                 0x0

#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_ADDR                               (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000020)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_RMSK                                      0xf
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_IN)
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_DATA_BMSK                                 0xf
#define HWIO_AON_TCSR_ACC_CTRL_EFUSE_1_DATA_SHFT                                 0x0

#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000024)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_0_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_GCC_0_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_0_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_GCC_0_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_GCC_0_IN)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_0_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000028)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_1_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_GCC_1_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_1_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_GCC_1_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_GCC_1_IN)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_1_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x0000002c)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_RMSK                                    0x3ffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_2_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_GCC_2_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_GCC_2_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_GCC_2_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_GCC_2_IN)
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_DATA_BMSK                               0x3ffff
#define HWIO_AON_TCSR_ACC_CTRL_GCC_2_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000030)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_RMSK                                0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_0_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_TLMM_0_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_0_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_TLMM_0_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_TLMM_0_IN)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_DATA_BMSK                           0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_0_DATA_SHFT                                  0x0

#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000034)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_RMSK                                0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_1_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_TLMM_1_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_1_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_TLMM_1_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_TLMM_1_IN)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_DATA_BMSK                           0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_1_DATA_SHFT                                  0x0

#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000038)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_RMSK                                0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_2_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_TLMM_2_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_2_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_TLMM_2_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_TLMM_2_IN)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_DATA_BMSK                           0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_2_DATA_SHFT                                  0x0

#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x0000003c)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_RMSK                                      0xff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_3_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_TLMM_3_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_TLMM_3_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_TLMM_3_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_TLMM_3_IN)
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_DATA_BMSK                                 0xff
#define HWIO_AON_TCSR_ACC_CTRL_TLMM_3_DATA_SHFT                                  0x0

#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000040)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_0_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_PMU_0_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_0_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_PMU_0_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_PMU_0_IN)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_0_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000044)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_1_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_PMU_1_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_1_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_PMU_1_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_PMU_1_IN)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_1_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000048)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_2_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_PMU_2_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_2_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_PMU_2_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_PMU_2_IN)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_2_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_ADDR                                 (AON_TCSR_TCSR_TME_REG_BASE      + 0x0000004c)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_RMSK                                 0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_IN          \
        in_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_3_ADDR)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_ACC_CTRL_PMU_3_ADDR, m)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_OUT(v)      \
        out_dword(HWIO_AON_TCSR_ACC_CTRL_PMU_3_ADDR,v)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_ACC_CTRL_PMU_3_ADDR,m,v,HWIO_AON_TCSR_ACC_CTRL_PMU_3_IN)
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_DATA_BMSK                            0xffffffff
#define HWIO_AON_TCSR_ACC_CTRL_PMU_3_DATA_SHFT                                   0x0

#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_ADDR                                (AON_TCSR_TCSR_TME_REG_BASE      + 0x00000050)
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_RMSK                                       0x1
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_IN          \
        in_dword(HWIO_AON_TCSR_GTMR_COUNT_CTRL_ADDR)
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_GTMR_COUNT_CTRL_ADDR, m)
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_OUT(v)      \
        out_dword(HWIO_AON_TCSR_GTMR_COUNT_CTRL_ADDR,v)
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_GTMR_COUNT_CTRL_ADDR,m,v,HWIO_AON_TCSR_GTMR_COUNT_CTRL_IN)
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_GRAY_CODE_COV_DISABLE_BMSK                 0x1
#define HWIO_AON_TCSR_GTMR_COUNT_CTRL_GRAY_CODE_COV_DISABLE_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_TCSR_TCSR_BT
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_BT_REG_BASE (AON_TCSR_TCSR_BASE      + 0x00000400)
#define AON_TCSR_TCSR_BT_REG_BASE_SIZE 0x100
#define AON_TCSR_TCSR_BT_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_TCSR_TCSR_APPS
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_APPS_REG_BASE                       (AON_TCSR_TCSR_BASE      + 0x00000800)
#define AON_TCSR_TCSR_APPS_REG_BASE_SIZE                  0x100
#define AON_TCSR_TCSR_APPS_REG_BASE_USED                  0x8

#define HWIO_AON_TCSR_IPC_APPS_TO_BT_ADDR                 (AON_TCSR_TCSR_APPS_REG_BASE      + 0x00000000)
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_RMSK                        0x1
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_IN          \
        in_dword(HWIO_AON_TCSR_IPC_APPS_TO_BT_ADDR)
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_IPC_APPS_TO_BT_ADDR, m)
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_OUT(v)      \
        out_dword(HWIO_AON_TCSR_IPC_APPS_TO_BT_ADDR,v)
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_IPC_APPS_TO_BT_ADDR,m,v,HWIO_AON_TCSR_IPC_APPS_TO_BT_IN)
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_EVENT_BMSK                  0x1
#define HWIO_AON_TCSR_IPC_APPS_TO_BT_EVENT_SHFT                  0x0

#define HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR                (AON_TCSR_TCSR_APPS_REG_BASE      + 0x00000004)
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_RMSK                       0x1
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_IN          \
        in_dword(HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR)
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR, m)
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_OUT(v)      \
        out_dword(HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR,v)
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_IPC_APPS_TO_TME_ADDR,m,v,HWIO_AON_TCSR_IPC_APPS_TO_TME_IN)
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_EVENT_BMSK                 0x1
#define HWIO_AON_TCSR_IPC_APPS_TO_TME_EVENT_SHFT                 0x0

#define HWIO_AON_TCSR_CLK_ENABLE_APPS_ADDR                (AON_TCSR_TCSR_APPS_REG_BASE      + 0x00000008)
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_RMSK                       0x2
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_IN          \
        in_dword(HWIO_AON_TCSR_CLK_ENABLE_APPS_ADDR)
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_CLK_ENABLE_APPS_ADDR, m)
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_OUT(v)      \
        out_dword(HWIO_AON_TCSR_CLK_ENABLE_APPS_ADDR,v)
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_CLK_ENABLE_APPS_ADDR,m,v,HWIO_AON_TCSR_CLK_ENABLE_APPS_IN)
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_CETMR_BMSK                 0x2
#define HWIO_AON_TCSR_CLK_ENABLE_APPS_CETMR_SHFT                 0x1

/*----------------------------------------------------------------------------
 * MODULE: AON_TCSR_TCSR_ALL
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_ALL_REG_BASE                         (AON_TCSR_TCSR_BASE      + 0x00000c00)
#define AON_TCSR_TCSR_ALL_REG_BASE_SIZE                    0x100
#define AON_TCSR_TCSR_ALL_REG_BASE_USED                    0x10

#define HWIO_AON_TCSR_CLK_ENABLE_ALL_ADDR                  (AON_TCSR_TCSR_ALL_REG_BASE      + 0x00000000)
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_RMSK                         0x2
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_IN          \
        in_dword(HWIO_AON_TCSR_CLK_ENABLE_ALL_ADDR)
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_CLK_ENABLE_ALL_ADDR, m)
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_OUT(v)      \
        out_dword(HWIO_AON_TCSR_CLK_ENABLE_ALL_ADDR,v)
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_CLK_ENABLE_ALL_ADDR,m,v,HWIO_AON_TCSR_CLK_ENABLE_ALL_IN)
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_LPOCAL_BMSK                  0x2
#define HWIO_AON_TCSR_CLK_ENABLE_ALL_LPOCAL_SHFT                  0x1

#define HWIO_AON_TCSR_LPOCAL_CONTROL_ADDR                  (AON_TCSR_TCSR_ALL_REG_BASE      + 0x00000004)
#define HWIO_AON_TCSR_LPOCAL_CONTROL_RMSK                      0xffff
#define HWIO_AON_TCSR_LPOCAL_CONTROL_IN          \
        in_dword(HWIO_AON_TCSR_LPOCAL_CONTROL_ADDR)
#define HWIO_AON_TCSR_LPOCAL_CONTROL_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_LPOCAL_CONTROL_ADDR, m)
#define HWIO_AON_TCSR_LPOCAL_CONTROL_OUT(v)      \
        out_dword(HWIO_AON_TCSR_LPOCAL_CONTROL_ADDR,v)
#define HWIO_AON_TCSR_LPOCAL_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_LPOCAL_CONTROL_ADDR,m,v,HWIO_AON_TCSR_LPOCAL_CONTROL_IN)
#define HWIO_AON_TCSR_LPOCAL_CONTROL_DATA_BMSK                 0xffff
#define HWIO_AON_TCSR_LPOCAL_CONTROL_DATA_SHFT                    0x0

#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_ADDR                 (AON_TCSR_TCSR_ALL_REG_BASE      + 0x00000008)
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_RMSK                   0x3fffff
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_IN          \
        in_dword(HWIO_AON_TCSR_LPOCAL_COUNTVAL_ADDR)
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_LPOCAL_COUNTVAL_ADDR, m)
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_OUT(v)      \
        out_dword(HWIO_AON_TCSR_LPOCAL_COUNTVAL_ADDR,v)
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_LPOCAL_COUNTVAL_ADDR,m,v,HWIO_AON_TCSR_LPOCAL_COUNTVAL_IN)
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_DATA_BMSK              0x3fffff
#define HWIO_AON_TCSR_LPOCAL_COUNTVAL_DATA_SHFT                   0x0

#define HWIO_AON_TCSR_LPOCAL_COMPLETE_ADDR                 (AON_TCSR_TCSR_ALL_REG_BASE      + 0x0000000c)
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_RMSK                        0x1
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_IN          \
        in_dword(HWIO_AON_TCSR_LPOCAL_COMPLETE_ADDR)
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_LPOCAL_COMPLETE_ADDR, m)
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_OUT(v)      \
        out_dword(HWIO_AON_TCSR_LPOCAL_COMPLETE_ADDR,v)
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_TCSR_LPOCAL_COMPLETE_ADDR,m,v,HWIO_AON_TCSR_LPOCAL_COMPLETE_IN)
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_DATA_BMSK                   0x1
#define HWIO_AON_TCSR_LPOCAL_COMPLETE_DATA_SHFT                   0x0

#define HWIO_AON_TCSR_EFUSE_SENSED_ADDR                    (AON_TCSR_TCSR_ALL_REG_BASE      + 0x00000010)
#define HWIO_AON_TCSR_EFUSE_SENSED_RMSK                      0x7fffff
#define HWIO_AON_TCSR_EFUSE_SENSED_IN          \
        in_dword(HWIO_AON_TCSR_EFUSE_SENSED_ADDR)
#define HWIO_AON_TCSR_EFUSE_SENSED_INM(m)      \
        in_dword_masked(HWIO_AON_TCSR_EFUSE_SENSED_ADDR, m)
#define HWIO_AON_TCSR_EFUSE_SENSED_VTRIM_BMSK                0x7c0000
#define HWIO_AON_TCSR_EFUSE_SENSED_VTRIM_SHFT                    0x12
#define HWIO_AON_TCSR_EFUSE_SENSED_TEMP_TRIM_BMSK             0x3ffff
#define HWIO_AON_TCSR_EFUSE_SENSED_TEMP_TRIM_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_PME_PME_AC
 *--------------------------------------------------------------------------*/

#define AON_PME_PME_AC_REG_BASE                                       (AON_PME_PME_AC_BASE      + 0x00000000)
#define AON_PME_PME_AC_REG_BASE_SIZE                                  0x1000
#define AON_PME_PME_AC_REG_BASE_USED                                  0xc20

#define HWIO_AON_PME_BT_STATUS_ADDR                                   (AON_PME_PME_AC_REG_BASE      + 0x00000400)
#define HWIO_AON_PME_BT_STATUS_RMSK                                        0x7ff
#define HWIO_AON_PME_BT_STATUS_IN          \
        in_dword(HWIO_AON_PME_BT_STATUS_ADDR)
#define HWIO_AON_PME_BT_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_STATUS_ADDR, m)
#define HWIO_AON_PME_BT_STATUS_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_STATUS_ADDR,v)
#define HWIO_AON_PME_BT_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_STATUS_ADDR,m,v,HWIO_AON_PME_BT_STATUS_IN)
#define HWIO_AON_PME_BT_STATUS_TRANSITION_PENDING_BMSK                     0x400
#define HWIO_AON_PME_BT_STATUS_TRANSITION_PENDING_SHFT                       0xa
#define HWIO_AON_PME_BT_STATUS_APPS_OPERATIVE_BMSK                         0x200
#define HWIO_AON_PME_BT_STATUS_APPS_OPERATIVE_SHFT                           0x9
#define HWIO_AON_PME_BT_STATUS_BT_OPERATIVE_BMSK                           0x100
#define HWIO_AON_PME_BT_STATUS_BT_OPERATIVE_SHFT                             0x8
#define HWIO_AON_PME_BT_STATUS_ROT_OPERATIVE_BMSK                           0x80
#define HWIO_AON_PME_BT_STATUS_ROT_OPERATIVE_SHFT                            0x7
#define HWIO_AON_PME_BT_STATUS_ACTIVATE_BMSK                                0x40
#define HWIO_AON_PME_BT_STATUS_ACTIVATE_SHFT                                 0x6
#define HWIO_AON_PME_BT_STATUS_RESET_CAUSE_BMSK                             0x3c
#define HWIO_AON_PME_BT_STATUS_RESET_CAUSE_SHFT                              0x2
#define HWIO_AON_PME_BT_STATUS_OPERATIVE_BMSK                                0x2
#define HWIO_AON_PME_BT_STATUS_OPERATIVE_SHFT                                0x1
#define HWIO_AON_PME_BT_STATUS_UPDATE_PENDING_BMSK                           0x1
#define HWIO_AON_PME_BT_STATUS_UPDATE_PENDING_SHFT                           0x0

#define HWIO_AON_PME_BT_DEPEND_ACTIVE_ADDR                            (AON_PME_PME_AC_REG_BASE      + 0x00000404)
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_RMSK                                 0xfff
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_IN          \
        in_dword(HWIO_AON_PME_BT_DEPEND_ACTIVE_ADDR)
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_DEPEND_ACTIVE_ADDR, m)
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_DEPEND_ACTIVE_ADDR,v)
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_DEPEND_ACTIVE_ADDR,m,v,HWIO_AON_PME_BT_DEPEND_ACTIVE_IN)
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_TLMM_BMSK                            0xc00
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_TLMM_SHFT                              0xa
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_PER_BMSK                             0x300
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_PER_SHFT                               0x8
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_NVM_BMSK                              0xc0
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_NVM_SHFT                               0x6
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_ROT_BMSK                              0x30
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_ROT_SHFT                               0x4
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_APPS_BMSK                              0xc
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_APPS_SHFT                              0x2
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_BT_BMSK                                0x3
#define HWIO_AON_PME_BT_DEPEND_ACTIVE_BT_SHFT                                0x0

#define HWIO_AON_PME_BT_DEPEND_STOPPED_ADDR                           (AON_PME_PME_AC_REG_BASE      + 0x00000408)
#define HWIO_AON_PME_BT_DEPEND_STOPPED_RMSK                                0xfff
#define HWIO_AON_PME_BT_DEPEND_STOPPED_IN          \
        in_dword(HWIO_AON_PME_BT_DEPEND_STOPPED_ADDR)
#define HWIO_AON_PME_BT_DEPEND_STOPPED_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_DEPEND_STOPPED_ADDR, m)
#define HWIO_AON_PME_BT_DEPEND_STOPPED_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_DEPEND_STOPPED_ADDR,v)
#define HWIO_AON_PME_BT_DEPEND_STOPPED_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_DEPEND_STOPPED_ADDR,m,v,HWIO_AON_PME_BT_DEPEND_STOPPED_IN)
#define HWIO_AON_PME_BT_DEPEND_STOPPED_TLMM_BMSK                           0xc00
#define HWIO_AON_PME_BT_DEPEND_STOPPED_TLMM_SHFT                             0xa
#define HWIO_AON_PME_BT_DEPEND_STOPPED_PER_BMSK                            0x300
#define HWIO_AON_PME_BT_DEPEND_STOPPED_PER_SHFT                              0x8
#define HWIO_AON_PME_BT_DEPEND_STOPPED_NVM_BMSK                             0xc0
#define HWIO_AON_PME_BT_DEPEND_STOPPED_NVM_SHFT                              0x6
#define HWIO_AON_PME_BT_DEPEND_STOPPED_ROT_BMSK                             0x30
#define HWIO_AON_PME_BT_DEPEND_STOPPED_ROT_SHFT                              0x4
#define HWIO_AON_PME_BT_DEPEND_STOPPED_APPS_BMSK                             0xc
#define HWIO_AON_PME_BT_DEPEND_STOPPED_APPS_SHFT                             0x2
#define HWIO_AON_PME_BT_DEPEND_STOPPED_BT_BMSK                               0x3
#define HWIO_AON_PME_BT_DEPEND_STOPPED_BT_SHFT                               0x0

#define HWIO_AON_PME_BT_DEPEND_CLOCKS_ADDR                            (AON_PME_PME_AC_REG_BASE      + 0x00000410)
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_RMSK                                   0x3
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_IN          \
        in_dword(HWIO_AON_PME_BT_DEPEND_CLOCKS_ADDR)
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_DEPEND_CLOCKS_ADDR, m)
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_DEPEND_CLOCKS_ADDR,v)
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_DEPEND_CLOCKS_ADDR,m,v,HWIO_AON_PME_BT_DEPEND_CLOCKS_IN)
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_TCLK_BMSK                              0x2
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_TCLK_SHFT                              0x1
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_HFCLK_BMSK                             0x1
#define HWIO_AON_PME_BT_DEPEND_CLOCKS_HFCLK_SHFT                             0x0

#define HWIO_AON_PME_BT_RAM_RETN_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x00000414)
#define HWIO_AON_PME_BT_RAM_RETN_RMSK                                       0xff
#define HWIO_AON_PME_BT_RAM_RETN_IN          \
        in_dword(HWIO_AON_PME_BT_RAM_RETN_ADDR)
#define HWIO_AON_PME_BT_RAM_RETN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_RAM_RETN_ADDR, m)
#define HWIO_AON_PME_BT_RAM_RETN_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_RAM_RETN_ADDR,v)
#define HWIO_AON_PME_BT_RAM_RETN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_RAM_RETN_ADDR,m,v,HWIO_AON_PME_BT_RAM_RETN_IN)
#define HWIO_AON_PME_BT_RAM_RETN_RAM_BMSK                                   0xff
#define HWIO_AON_PME_BT_RAM_RETN_RAM_SHFT                                    0x0

#define HWIO_AON_PME_BT_REQ_STATE_ADDR                                (AON_PME_PME_AC_REG_BASE      + 0x00000418)
#define HWIO_AON_PME_BT_REQ_STATE_RMSK                                       0x3
#define HWIO_AON_PME_BT_REQ_STATE_IN          \
        in_dword(HWIO_AON_PME_BT_REQ_STATE_ADDR)
#define HWIO_AON_PME_BT_REQ_STATE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_REQ_STATE_ADDR, m)
#define HWIO_AON_PME_BT_REQ_STATE_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_REQ_STATE_ADDR,v)
#define HWIO_AON_PME_BT_REQ_STATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_REQ_STATE_ADDR,m,v,HWIO_AON_PME_BT_REQ_STATE_IN)
#define HWIO_AON_PME_BT_REQ_STATE_STATE_BMSK                                 0x3
#define HWIO_AON_PME_BT_REQ_STATE_STATE_SHFT                                 0x0

#define HWIO_AON_PME_BT_IRQ_EN_ADDR                                   (AON_PME_PME_AC_REG_BASE      + 0x0000041c)
#define HWIO_AON_PME_BT_IRQ_EN_RMSK                                       0x2ffb
#define HWIO_AON_PME_BT_IRQ_EN_IN          \
        in_dword(HWIO_AON_PME_BT_IRQ_EN_ADDR)
#define HWIO_AON_PME_BT_IRQ_EN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_IRQ_EN_ADDR, m)
#define HWIO_AON_PME_BT_IRQ_EN_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_IRQ_EN_ADDR,v)
#define HWIO_AON_PME_BT_IRQ_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_IRQ_EN_ADDR,m,v,HWIO_AON_PME_BT_IRQ_EN_IN)
#define HWIO_AON_PME_BT_IRQ_EN_BAD_FOSC_BMSK                              0x2000
#define HWIO_AON_PME_BT_IRQ_EN_BAD_FOSC_SHFT                                 0xd
#define HWIO_AON_PME_BT_IRQ_EN_VDIO_BMSK                                   0x800
#define HWIO_AON_PME_BT_IRQ_EN_VDIO_SHFT                                     0xb
#define HWIO_AON_PME_BT_IRQ_EN_DISPLAY_BMSK                                0x400
#define HWIO_AON_PME_BT_IRQ_EN_DISPLAY_SHFT                                  0xa
#define HWIO_AON_PME_BT_IRQ_EN_BROWNOUT_BMSK                               0x200
#define HWIO_AON_PME_BT_IRQ_EN_BROWNOUT_SHFT                                 0x9
#define HWIO_AON_PME_BT_IRQ_EN_GTMR_BMSK                                   0x100
#define HWIO_AON_PME_BT_IRQ_EN_GTMR_SHFT                                     0x8
#define HWIO_AON_PME_BT_IRQ_EN_REQUEST_BMSK                                 0x80
#define HWIO_AON_PME_BT_IRQ_EN_REQUEST_SHFT                                  0x7
#define HWIO_AON_PME_BT_IRQ_EN_MFP_EDGE_BMSK                                0x40
#define HWIO_AON_PME_BT_IRQ_EN_MFP_EDGE_SHFT                                 0x6
#define HWIO_AON_PME_BT_IRQ_EN_MFP_SHORT_BMSK                               0x20
#define HWIO_AON_PME_BT_IRQ_EN_MFP_SHORT_SHFT                                0x5
#define HWIO_AON_PME_BT_IRQ_EN_PIO_BMSK                                     0x10
#define HWIO_AON_PME_BT_IRQ_EN_PIO_SHFT                                      0x4
#define HWIO_AON_PME_BT_IRQ_EN_PMU_BMSK                                      0x8
#define HWIO_AON_PME_BT_IRQ_EN_PMU_SHFT                                      0x3
#define HWIO_AON_PME_BT_IRQ_EN_HFXTAL_TIMEOUT_BMSK                           0x2
#define HWIO_AON_PME_BT_IRQ_EN_HFXTAL_TIMEOUT_SHFT                           0x1
#define HWIO_AON_PME_BT_IRQ_EN_HFXTAL_STABLE_BMSK                            0x1
#define HWIO_AON_PME_BT_IRQ_EN_HFXTAL_STABLE_SHFT                            0x0

#define HWIO_AON_PME_BT_IRQ_PENDING_ADDR                              (AON_PME_PME_AC_REG_BASE      + 0x00000420)
#define HWIO_AON_PME_BT_IRQ_PENDING_RMSK                                  0x2ffb
#define HWIO_AON_PME_BT_IRQ_PENDING_IN          \
        in_dword(HWIO_AON_PME_BT_IRQ_PENDING_ADDR)
#define HWIO_AON_PME_BT_IRQ_PENDING_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_IRQ_PENDING_ADDR, m)
#define HWIO_AON_PME_BT_IRQ_PENDING_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_IRQ_PENDING_ADDR,v)
#define HWIO_AON_PME_BT_IRQ_PENDING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_IRQ_PENDING_ADDR,m,v,HWIO_AON_PME_BT_IRQ_PENDING_IN)
#define HWIO_AON_PME_BT_IRQ_PENDING_BAD_FOSC_BMSK                         0x2000
#define HWIO_AON_PME_BT_IRQ_PENDING_BAD_FOSC_SHFT                            0xd
#define HWIO_AON_PME_BT_IRQ_PENDING_VDIO_BMSK                              0x800
#define HWIO_AON_PME_BT_IRQ_PENDING_VDIO_SHFT                                0xb
#define HWIO_AON_PME_BT_IRQ_PENDING_DISPLAY_BMSK                           0x400
#define HWIO_AON_PME_BT_IRQ_PENDING_DISPLAY_SHFT                             0xa
#define HWIO_AON_PME_BT_IRQ_PENDING_BROWNOUT_BMSK                          0x200
#define HWIO_AON_PME_BT_IRQ_PENDING_BROWNOUT_SHFT                            0x9
#define HWIO_AON_PME_BT_IRQ_PENDING_GTMR_BMSK                              0x100
#define HWIO_AON_PME_BT_IRQ_PENDING_GTMR_SHFT                                0x8
#define HWIO_AON_PME_BT_IRQ_PENDING_REQUEST_BMSK                            0x80
#define HWIO_AON_PME_BT_IRQ_PENDING_REQUEST_SHFT                             0x7
#define HWIO_AON_PME_BT_IRQ_PENDING_MFP_EDGE_BMSK                           0x40
#define HWIO_AON_PME_BT_IRQ_PENDING_MFP_EDGE_SHFT                            0x6
#define HWIO_AON_PME_BT_IRQ_PENDING_MFP_SHORT_BMSK                          0x20
#define HWIO_AON_PME_BT_IRQ_PENDING_MFP_SHORT_SHFT                           0x5
#define HWIO_AON_PME_BT_IRQ_PENDING_PIO_BMSK                                0x10
#define HWIO_AON_PME_BT_IRQ_PENDING_PIO_SHFT                                 0x4
#define HWIO_AON_PME_BT_IRQ_PENDING_PMU_BMSK                                 0x8
#define HWIO_AON_PME_BT_IRQ_PENDING_PMU_SHFT                                 0x3
#define HWIO_AON_PME_BT_IRQ_PENDING_HFXTAL_TIMEOUT_BMSK                      0x2
#define HWIO_AON_PME_BT_IRQ_PENDING_HFXTAL_TIMEOUT_SHFT                      0x1
#define HWIO_AON_PME_BT_IRQ_PENDING_HFXTAL_STABLE_BMSK                       0x1
#define HWIO_AON_PME_BT_IRQ_PENDING_HFXTAL_STABLE_SHFT                       0x0

#define HWIO_AON_PME_BT_REMAP_ADDR                                    (AON_PME_PME_AC_REG_BASE      + 0x00000424)
#define HWIO_AON_PME_BT_REMAP_RMSK                                           0x1
#define HWIO_AON_PME_BT_REMAP_IN          \
        in_dword(HWIO_AON_PME_BT_REMAP_ADDR)
#define HWIO_AON_PME_BT_REMAP_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_REMAP_ADDR, m)
#define HWIO_AON_PME_BT_REMAP_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_REMAP_ADDR,v)
#define HWIO_AON_PME_BT_REMAP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_REMAP_ADDR,m,v,HWIO_AON_PME_BT_REMAP_IN)
#define HWIO_AON_PME_BT_REMAP_SEL_BMSK                                       0x1
#define HWIO_AON_PME_BT_REMAP_SEL_SHFT                                       0x0

#define HWIO_AON_PME_BT_RESET_ADDR                                    (AON_PME_PME_AC_REG_BASE      + 0x00000428)
#define HWIO_AON_PME_BT_RESET_RMSK                                    0xffffffff
#define HWIO_AON_PME_BT_RESET_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_RESET_ADDR,v)
#define HWIO_AON_PME_BT_RESET_CODE_BMSK                               0xffffffff
#define HWIO_AON_PME_BT_RESET_CODE_SHFT                                      0x0

#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_ADDR                         (AON_PME_PME_AC_REG_BASE      + 0x0000042c)
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_RMSK                               0x1f
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_IN          \
        in_dword(HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_ADDR)
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_ADDR, m)
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_ADDR,v)
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_ADDR,m,v,HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_IN)
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_TIME_BMSK                          0x1f
#define HWIO_AON_PME_BT_GTMR_WAKEUP_HOLD_TIME_SHFT                           0x0

#define HWIO_AON_PME_BT_PROC_REQ_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x000007fc)
#define HWIO_AON_PME_BT_PROC_REQ_RMSK                                        0x3
#define HWIO_AON_PME_BT_PROC_REQ_IN          \
        in_dword(HWIO_AON_PME_BT_PROC_REQ_ADDR)
#define HWIO_AON_PME_BT_PROC_REQ_INM(m)      \
        in_dword_masked(HWIO_AON_PME_BT_PROC_REQ_ADDR, m)
#define HWIO_AON_PME_BT_PROC_REQ_OUT(v)      \
        out_dword(HWIO_AON_PME_BT_PROC_REQ_ADDR,v)
#define HWIO_AON_PME_BT_PROC_REQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_BT_PROC_REQ_ADDR,m,v,HWIO_AON_PME_BT_PROC_REQ_IN)
#define HWIO_AON_PME_BT_PROC_REQ_ACK_BMSK                                    0x2
#define HWIO_AON_PME_BT_PROC_REQ_ACK_SHFT                                    0x1
#define HWIO_AON_PME_BT_PROC_REQ_REQ_BMSK                                    0x1
#define HWIO_AON_PME_BT_PROC_REQ_REQ_SHFT                                    0x0

#define HWIO_AON_PME_APPS_STATUS_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x00000800)
#define HWIO_AON_PME_APPS_STATUS_RMSK                                      0x7ff
#define HWIO_AON_PME_APPS_STATUS_IN          \
        in_dword(HWIO_AON_PME_APPS_STATUS_ADDR)
#define HWIO_AON_PME_APPS_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_STATUS_ADDR, m)
#define HWIO_AON_PME_APPS_STATUS_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_STATUS_ADDR,v)
#define HWIO_AON_PME_APPS_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_STATUS_ADDR,m,v,HWIO_AON_PME_APPS_STATUS_IN)
#define HWIO_AON_PME_APPS_STATUS_TRANSITION_PENDING_BMSK                   0x400
#define HWIO_AON_PME_APPS_STATUS_TRANSITION_PENDING_SHFT                     0xa
#define HWIO_AON_PME_APPS_STATUS_APPS_OPERATIVE_BMSK                       0x200
#define HWIO_AON_PME_APPS_STATUS_APPS_OPERATIVE_SHFT                         0x9
#define HWIO_AON_PME_APPS_STATUS_BT_OPERATIVE_BMSK                         0x100
#define HWIO_AON_PME_APPS_STATUS_BT_OPERATIVE_SHFT                           0x8
#define HWIO_AON_PME_APPS_STATUS_ROT_OPERATIVE_BMSK                         0x80
#define HWIO_AON_PME_APPS_STATUS_ROT_OPERATIVE_SHFT                          0x7
#define HWIO_AON_PME_APPS_STATUS_ACTIVATE_BMSK                              0x40
#define HWIO_AON_PME_APPS_STATUS_ACTIVATE_SHFT                               0x6
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_BMSK                           0x3c
#define HWIO_AON_PME_APPS_STATUS_RESET_CAUSE_SHFT                            0x2
#define HWIO_AON_PME_APPS_STATUS_OPERATIVE_BMSK                              0x2
#define HWIO_AON_PME_APPS_STATUS_OPERATIVE_SHFT                              0x1
#define HWIO_AON_PME_APPS_STATUS_UPDATE_PENDING_BMSK                         0x1
#define HWIO_AON_PME_APPS_STATUS_UPDATE_PENDING_SHFT                         0x0

#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_ADDR                          (AON_PME_PME_AC_REG_BASE      + 0x00000804)
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_RMSK                               0xfff
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_IN          \
        in_dword(HWIO_AON_PME_APPS_DEPEND_ACTIVE_ADDR)
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_DEPEND_ACTIVE_ADDR, m)
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_DEPEND_ACTIVE_ADDR,v)
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_DEPEND_ACTIVE_ADDR,m,v,HWIO_AON_PME_APPS_DEPEND_ACTIVE_IN)
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_TLMM_BMSK                          0xc00
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_TLMM_SHFT                            0xa
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_PER_BMSK                           0x300
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_PER_SHFT                             0x8
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_NVM_BMSK                            0xc0
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_NVM_SHFT                             0x6
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_ROT_BMSK                            0x30
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_ROT_SHFT                             0x4
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_APPS_BMSK                            0xc
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_APPS_SHFT                            0x2
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_BT_BMSK                              0x3
#define HWIO_AON_PME_APPS_DEPEND_ACTIVE_BT_SHFT                              0x0

#define HWIO_AON_PME_APPS_DEPEND_STOPPED_ADDR                         (AON_PME_PME_AC_REG_BASE      + 0x00000808)
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_RMSK                              0xfff
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_IN          \
        in_dword(HWIO_AON_PME_APPS_DEPEND_STOPPED_ADDR)
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_DEPEND_STOPPED_ADDR, m)
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_DEPEND_STOPPED_ADDR,v)
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_DEPEND_STOPPED_ADDR,m,v,HWIO_AON_PME_APPS_DEPEND_STOPPED_IN)
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_TLMM_BMSK                         0xc00
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_TLMM_SHFT                           0xa
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_PER_BMSK                          0x300
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_PER_SHFT                            0x8
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_NVM_BMSK                           0xc0
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_NVM_SHFT                            0x6
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_ROT_BMSK                           0x30
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_ROT_SHFT                            0x4
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_APPS_BMSK                           0xc
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_APPS_SHFT                           0x2
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_BT_BMSK                             0x3
#define HWIO_AON_PME_APPS_DEPEND_STOPPED_BT_SHFT                             0x0

#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_ADDR                          (AON_PME_PME_AC_REG_BASE      + 0x00000810)
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_RMSK                                 0x3
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_IN          \
        in_dword(HWIO_AON_PME_APPS_DEPEND_CLOCKS_ADDR)
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_DEPEND_CLOCKS_ADDR, m)
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_DEPEND_CLOCKS_ADDR,v)
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_DEPEND_CLOCKS_ADDR,m,v,HWIO_AON_PME_APPS_DEPEND_CLOCKS_IN)
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_TCLK_BMSK                            0x2
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_TCLK_SHFT                            0x1
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_BMSK                           0x1
#define HWIO_AON_PME_APPS_DEPEND_CLOCKS_HFCLK_SHFT                           0x0

#define HWIO_AON_PME_APPS_RAM_RETN_ADDR                               (AON_PME_PME_AC_REG_BASE      + 0x00000814)
#define HWIO_AON_PME_APPS_RAM_RETN_RMSK                                     0xff
#define HWIO_AON_PME_APPS_RAM_RETN_IN          \
        in_dword(HWIO_AON_PME_APPS_RAM_RETN_ADDR)
#define HWIO_AON_PME_APPS_RAM_RETN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_RAM_RETN_ADDR, m)
#define HWIO_AON_PME_APPS_RAM_RETN_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_RAM_RETN_ADDR,v)
#define HWIO_AON_PME_APPS_RAM_RETN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_RAM_RETN_ADDR,m,v,HWIO_AON_PME_APPS_RAM_RETN_IN)
#define HWIO_AON_PME_APPS_RAM_RETN_RAM_BMSK                                 0xff
#define HWIO_AON_PME_APPS_RAM_RETN_RAM_SHFT                                  0x0

#define HWIO_AON_PME_APPS_REQ_STATE_ADDR                              (AON_PME_PME_AC_REG_BASE      + 0x00000818)
#define HWIO_AON_PME_APPS_REQ_STATE_RMSK                                     0x3
#define HWIO_AON_PME_APPS_REQ_STATE_IN          \
        in_dword(HWIO_AON_PME_APPS_REQ_STATE_ADDR)
#define HWIO_AON_PME_APPS_REQ_STATE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_REQ_STATE_ADDR, m)
#define HWIO_AON_PME_APPS_REQ_STATE_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_REQ_STATE_ADDR,v)
#define HWIO_AON_PME_APPS_REQ_STATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_REQ_STATE_ADDR,m,v,HWIO_AON_PME_APPS_REQ_STATE_IN)
#define HWIO_AON_PME_APPS_REQ_STATE_STATE_BMSK                               0x3
#define HWIO_AON_PME_APPS_REQ_STATE_STATE_SHFT                               0x0

#define HWIO_AON_PME_APPS_IRQ_EN_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x0000081c)
#define HWIO_AON_PME_APPS_IRQ_EN_RMSK                                     0x3ffb
#define HWIO_AON_PME_APPS_IRQ_EN_IN          \
        in_dword(HWIO_AON_PME_APPS_IRQ_EN_ADDR)
#define HWIO_AON_PME_APPS_IRQ_EN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_IRQ_EN_ADDR, m)
#define HWIO_AON_PME_APPS_IRQ_EN_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_IRQ_EN_ADDR,v)
#define HWIO_AON_PME_APPS_IRQ_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_IRQ_EN_ADDR,m,v,HWIO_AON_PME_APPS_IRQ_EN_IN)
#define HWIO_AON_PME_APPS_IRQ_EN_BAD_FOSC_BMSK                            0x2000
#define HWIO_AON_PME_APPS_IRQ_EN_BAD_FOSC_SHFT                               0xd
#define HWIO_AON_PME_APPS_IRQ_EN_CETMR_BMSK                               0x1000
#define HWIO_AON_PME_APPS_IRQ_EN_CETMR_SHFT                                  0xc
#define HWIO_AON_PME_APPS_IRQ_EN_VDIO_BMSK                                 0x800
#define HWIO_AON_PME_APPS_IRQ_EN_VDIO_SHFT                                   0xb
#define HWIO_AON_PME_APPS_IRQ_EN_DISPLAY_BMSK                              0x400
#define HWIO_AON_PME_APPS_IRQ_EN_DISPLAY_SHFT                                0xa
#define HWIO_AON_PME_APPS_IRQ_EN_BROWNOUT_BMSK                             0x200
#define HWIO_AON_PME_APPS_IRQ_EN_BROWNOUT_SHFT                               0x9
#define HWIO_AON_PME_APPS_IRQ_EN_GTMR_BMSK                                 0x100
#define HWIO_AON_PME_APPS_IRQ_EN_GTMR_SHFT                                   0x8
#define HWIO_AON_PME_APPS_IRQ_EN_REQUEST_BMSK                               0x80
#define HWIO_AON_PME_APPS_IRQ_EN_REQUEST_SHFT                                0x7
#define HWIO_AON_PME_APPS_IRQ_EN_MFP_EDGE_BMSK                              0x40
#define HWIO_AON_PME_APPS_IRQ_EN_MFP_EDGE_SHFT                               0x6
#define HWIO_AON_PME_APPS_IRQ_EN_MFP_SHORT_BMSK                             0x20
#define HWIO_AON_PME_APPS_IRQ_EN_MFP_SHORT_SHFT                              0x5
#define HWIO_AON_PME_APPS_IRQ_EN_PIO_BMSK                                   0x10
#define HWIO_AON_PME_APPS_IRQ_EN_PIO_SHFT                                    0x4
#define HWIO_AON_PME_APPS_IRQ_EN_PMU_BMSK                                    0x8
#define HWIO_AON_PME_APPS_IRQ_EN_PMU_SHFT                                    0x3
#define HWIO_AON_PME_APPS_IRQ_EN_HFXTAL_TIMEOUT_BMSK                         0x2
#define HWIO_AON_PME_APPS_IRQ_EN_HFXTAL_TIMEOUT_SHFT                         0x1
#define HWIO_AON_PME_APPS_IRQ_EN_HFXTAL_STABLE_BMSK                          0x1
#define HWIO_AON_PME_APPS_IRQ_EN_HFXTAL_STABLE_SHFT                          0x0

#define HWIO_AON_PME_APPS_IRQ_PENDING_ADDR                            (AON_PME_PME_AC_REG_BASE      + 0x00000820)
#define HWIO_AON_PME_APPS_IRQ_PENDING_RMSK                                0x3ffb
#define HWIO_AON_PME_APPS_IRQ_PENDING_IN          \
        in_dword(HWIO_AON_PME_APPS_IRQ_PENDING_ADDR)
#define HWIO_AON_PME_APPS_IRQ_PENDING_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_IRQ_PENDING_ADDR, m)
#define HWIO_AON_PME_APPS_IRQ_PENDING_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_IRQ_PENDING_ADDR,v)
#define HWIO_AON_PME_APPS_IRQ_PENDING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_IRQ_PENDING_ADDR,m,v,HWIO_AON_PME_APPS_IRQ_PENDING_IN)
#define HWIO_AON_PME_APPS_IRQ_PENDING_BAD_FOSC_BMSK                       0x2000
#define HWIO_AON_PME_APPS_IRQ_PENDING_BAD_FOSC_SHFT                          0xd
#define HWIO_AON_PME_APPS_IRQ_PENDING_CETMR_BMSK                          0x1000
#define HWIO_AON_PME_APPS_IRQ_PENDING_CETMR_SHFT                             0xc
#define HWIO_AON_PME_APPS_IRQ_PENDING_VDIO_BMSK                            0x800
#define HWIO_AON_PME_APPS_IRQ_PENDING_VDIO_SHFT                              0xb
#define HWIO_AON_PME_APPS_IRQ_PENDING_DISPLAY_BMSK                         0x400
#define HWIO_AON_PME_APPS_IRQ_PENDING_DISPLAY_SHFT                           0xa
#define HWIO_AON_PME_APPS_IRQ_PENDING_BROWNOUT_BMSK                        0x200
#define HWIO_AON_PME_APPS_IRQ_PENDING_BROWNOUT_SHFT                          0x9
#define HWIO_AON_PME_APPS_IRQ_PENDING_GTMR_BMSK                            0x100
#define HWIO_AON_PME_APPS_IRQ_PENDING_GTMR_SHFT                              0x8
#define HWIO_AON_PME_APPS_IRQ_PENDING_REQUEST_BMSK                          0x80
#define HWIO_AON_PME_APPS_IRQ_PENDING_REQUEST_SHFT                           0x7
#define HWIO_AON_PME_APPS_IRQ_PENDING_MFP_EDGE_BMSK                         0x40
#define HWIO_AON_PME_APPS_IRQ_PENDING_MFP_EDGE_SHFT                          0x6
#define HWIO_AON_PME_APPS_IRQ_PENDING_MFP_SHORT_BMSK                        0x20
#define HWIO_AON_PME_APPS_IRQ_PENDING_MFP_SHORT_SHFT                         0x5
#define HWIO_AON_PME_APPS_IRQ_PENDING_PIO_BMSK                              0x10
#define HWIO_AON_PME_APPS_IRQ_PENDING_PIO_SHFT                               0x4
#define HWIO_AON_PME_APPS_IRQ_PENDING_PMU_BMSK                               0x8
#define HWIO_AON_PME_APPS_IRQ_PENDING_PMU_SHFT                               0x3
#define HWIO_AON_PME_APPS_IRQ_PENDING_HFXTAL_TIMEOUT_BMSK                    0x2
#define HWIO_AON_PME_APPS_IRQ_PENDING_HFXTAL_TIMEOUT_SHFT                    0x1
#define HWIO_AON_PME_APPS_IRQ_PENDING_HFXTAL_STABLE_BMSK                     0x1
#define HWIO_AON_PME_APPS_IRQ_PENDING_HFXTAL_STABLE_SHFT                     0x0

#define HWIO_AON_PME_APPS_REMAP_ADDR                                  (AON_PME_PME_AC_REG_BASE      + 0x00000824)
#define HWIO_AON_PME_APPS_REMAP_RMSK                                        0x7f
#define HWIO_AON_PME_APPS_REMAP_IN          \
        in_dword(HWIO_AON_PME_APPS_REMAP_ADDR)
#define HWIO_AON_PME_APPS_REMAP_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_REMAP_ADDR, m)
#define HWIO_AON_PME_APPS_REMAP_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_REMAP_ADDR,v)
#define HWIO_AON_PME_APPS_REMAP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_REMAP_ADDR,m,v,HWIO_AON_PME_APPS_REMAP_IN)
#define HWIO_AON_PME_APPS_REMAP_OFFSET_BMSK                                 0x7e
#define HWIO_AON_PME_APPS_REMAP_OFFSET_SHFT                                  0x1
#define HWIO_AON_PME_APPS_REMAP_SEL_BMSK                                     0x1
#define HWIO_AON_PME_APPS_REMAP_SEL_SHFT                                     0x0

#define HWIO_AON_PME_APPS_RESET_ADDR                                  (AON_PME_PME_AC_REG_BASE      + 0x00000828)
#define HWIO_AON_PME_APPS_RESET_RMSK                                  0xffffffff
#define HWIO_AON_PME_APPS_RESET_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_RESET_ADDR,v)
#define HWIO_AON_PME_APPS_RESET_CODE_BMSK                             0xffffffff
#define HWIO_AON_PME_APPS_RESET_CODE_SHFT                                    0x0

#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_ADDR                       (AON_PME_PME_AC_REG_BASE      + 0x0000082c)
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_RMSK                             0x1f
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_IN          \
        in_dword(HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_ADDR)
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_ADDR, m)
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_ADDR,v)
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_ADDR,m,v,HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_IN)
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_TIME_BMSK                        0x1f
#define HWIO_AON_PME_APPS_GTMR_WAKEUP_HOLD_TIME_SHFT                         0x0

#define HWIO_AON_PME_APPS_PROC_REQ_ADDR                               (AON_PME_PME_AC_REG_BASE      + 0x00000bfc)
#define HWIO_AON_PME_APPS_PROC_REQ_RMSK                                      0x3
#define HWIO_AON_PME_APPS_PROC_REQ_IN          \
        in_dword(HWIO_AON_PME_APPS_PROC_REQ_ADDR)
#define HWIO_AON_PME_APPS_PROC_REQ_INM(m)      \
        in_dword_masked(HWIO_AON_PME_APPS_PROC_REQ_ADDR, m)
#define HWIO_AON_PME_APPS_PROC_REQ_OUT(v)      \
        out_dword(HWIO_AON_PME_APPS_PROC_REQ_ADDR,v)
#define HWIO_AON_PME_APPS_PROC_REQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_APPS_PROC_REQ_ADDR,m,v,HWIO_AON_PME_APPS_PROC_REQ_IN)
#define HWIO_AON_PME_APPS_PROC_REQ_ACK_BMSK                                  0x2
#define HWIO_AON_PME_APPS_PROC_REQ_ACK_SHFT                                  0x1
#define HWIO_AON_PME_APPS_PROC_REQ_REQ_BMSK                                  0x1
#define HWIO_AON_PME_APPS_PROC_REQ_REQ_SHFT                                  0x0

#define HWIO_AON_PME_ROT_STATUS_ADDR                                  (AON_PME_PME_AC_REG_BASE      + 0x00000000)
#define HWIO_AON_PME_ROT_STATUS_RMSK                                     0xf07ff
#define HWIO_AON_PME_ROT_STATUS_IN          \
        in_dword(HWIO_AON_PME_ROT_STATUS_ADDR)
#define HWIO_AON_PME_ROT_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_STATUS_ADDR, m)
#define HWIO_AON_PME_ROT_STATUS_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_STATUS_ADDR,v)
#define HWIO_AON_PME_ROT_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_STATUS_ADDR,m,v,HWIO_AON_PME_ROT_STATUS_IN)
#define HWIO_AON_PME_ROT_STATUS_VDIO_RESET_EN_BMSK                       0x80000
#define HWIO_AON_PME_ROT_STATUS_VDIO_RESET_EN_SHFT                          0x13
#define HWIO_AON_PME_ROT_STATUS_BROWNOUT_RESET_EN_BMSK                   0x40000
#define HWIO_AON_PME_ROT_STATUS_BROWNOUT_RESET_EN_SHFT                      0x12
#define HWIO_AON_PME_ROT_STATUS_CONFIG_DONE_BMSK                         0x20000
#define HWIO_AON_PME_ROT_STATUS_CONFIG_DONE_SHFT                            0x11
#define HWIO_AON_PME_ROT_STATUS_RESTORE_ERROR_BMSK                       0x10000
#define HWIO_AON_PME_ROT_STATUS_RESTORE_ERROR_SHFT                          0x10
#define HWIO_AON_PME_ROT_STATUS_TRANSITION_PENDING_BMSK                    0x400
#define HWIO_AON_PME_ROT_STATUS_TRANSITION_PENDING_SHFT                      0xa
#define HWIO_AON_PME_ROT_STATUS_APPS_OPERATIVE_BMSK                        0x200
#define HWIO_AON_PME_ROT_STATUS_APPS_OPERATIVE_SHFT                          0x9
#define HWIO_AON_PME_ROT_STATUS_BT_OPERATIVE_BMSK                          0x100
#define HWIO_AON_PME_ROT_STATUS_BT_OPERATIVE_SHFT                            0x8
#define HWIO_AON_PME_ROT_STATUS_ROT_OPERATIVE_BMSK                          0x80
#define HWIO_AON_PME_ROT_STATUS_ROT_OPERATIVE_SHFT                           0x7
#define HWIO_AON_PME_ROT_STATUS_ACTIVATE_BMSK                               0x40
#define HWIO_AON_PME_ROT_STATUS_ACTIVATE_SHFT                                0x6
#define HWIO_AON_PME_ROT_STATUS_RESET_CAUSE_BMSK                            0x3c
#define HWIO_AON_PME_ROT_STATUS_RESET_CAUSE_SHFT                             0x2
#define HWIO_AON_PME_ROT_STATUS_OPERATIVE_BMSK                               0x2
#define HWIO_AON_PME_ROT_STATUS_OPERATIVE_SHFT                               0x1
#define HWIO_AON_PME_ROT_STATUS_UPDATE_PENDING_BMSK                          0x1
#define HWIO_AON_PME_ROT_STATUS_UPDATE_PENDING_SHFT                          0x0

#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_ADDR                           (AON_PME_PME_AC_REG_BASE      + 0x00000004)
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_RMSK                                0xfff
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_IN          \
        in_dword(HWIO_AON_PME_ROT_DEPEND_ACTIVE_ADDR)
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_DEPEND_ACTIVE_ADDR, m)
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_DEPEND_ACTIVE_ADDR,v)
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_DEPEND_ACTIVE_ADDR,m,v,HWIO_AON_PME_ROT_DEPEND_ACTIVE_IN)
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_TLMM_BMSK                           0xc00
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_TLMM_SHFT                             0xa
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_PER_BMSK                            0x300
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_PER_SHFT                              0x8
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_NVM_BMSK                             0xc0
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_NVM_SHFT                              0x6
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_ROT_BMSK                             0x30
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_ROT_SHFT                              0x4
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_APPS_BMSK                             0xc
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_APPS_SHFT                             0x2
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_BT_BMSK                               0x3
#define HWIO_AON_PME_ROT_DEPEND_ACTIVE_BT_SHFT                               0x0

#define HWIO_AON_PME_ROT_DEPEND_STOPPED_ADDR                          (AON_PME_PME_AC_REG_BASE      + 0x00000008)
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_RMSK                               0xfff
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_IN          \
        in_dword(HWIO_AON_PME_ROT_DEPEND_STOPPED_ADDR)
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_DEPEND_STOPPED_ADDR, m)
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_DEPEND_STOPPED_ADDR,v)
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_DEPEND_STOPPED_ADDR,m,v,HWIO_AON_PME_ROT_DEPEND_STOPPED_IN)
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_TLMM_BMSK                          0xc00
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_TLMM_SHFT                            0xa
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_PER_BMSK                           0x300
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_PER_SHFT                             0x8
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_NVM_BMSK                            0xc0
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_NVM_SHFT                             0x6
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_ROT_BMSK                            0x30
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_ROT_SHFT                             0x4
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_APPS_BMSK                            0xc
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_APPS_SHFT                            0x2
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_BT_BMSK                              0x3
#define HWIO_AON_PME_ROT_DEPEND_STOPPED_BT_SHFT                              0x0

#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_ADDR                           (AON_PME_PME_AC_REG_BASE      + 0x00000010)
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_RMSK                                  0x3
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_IN          \
        in_dword(HWIO_AON_PME_ROT_DEPEND_CLOCKS_ADDR)
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_DEPEND_CLOCKS_ADDR, m)
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_DEPEND_CLOCKS_ADDR,v)
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_DEPEND_CLOCKS_ADDR,m,v,HWIO_AON_PME_ROT_DEPEND_CLOCKS_IN)
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_TCLK_BMSK                             0x2
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_TCLK_SHFT                             0x1
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_HFCLK_BMSK                            0x1
#define HWIO_AON_PME_ROT_DEPEND_CLOCKS_HFCLK_SHFT                            0x0

#define HWIO_AON_PME_ROT_REQ_STATE_ADDR                               (AON_PME_PME_AC_REG_BASE      + 0x00000018)
#define HWIO_AON_PME_ROT_REQ_STATE_RMSK                                      0x3
#define HWIO_AON_PME_ROT_REQ_STATE_IN          \
        in_dword(HWIO_AON_PME_ROT_REQ_STATE_ADDR)
#define HWIO_AON_PME_ROT_REQ_STATE_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_REQ_STATE_ADDR, m)
#define HWIO_AON_PME_ROT_REQ_STATE_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_REQ_STATE_ADDR,v)
#define HWIO_AON_PME_ROT_REQ_STATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_REQ_STATE_ADDR,m,v,HWIO_AON_PME_ROT_REQ_STATE_IN)
#define HWIO_AON_PME_ROT_REQ_STATE_STATE_BMSK                                0x3
#define HWIO_AON_PME_ROT_REQ_STATE_STATE_SHFT                                0x0

#define HWIO_AON_PME_ROT_IRQ_EN_ADDR                                  (AON_PME_PME_AC_REG_BASE      + 0x0000001c)
#define HWIO_AON_PME_ROT_IRQ_EN_RMSK                                  0xe00020fb
#define HWIO_AON_PME_ROT_IRQ_EN_IN          \
        in_dword(HWIO_AON_PME_ROT_IRQ_EN_ADDR)
#define HWIO_AON_PME_ROT_IRQ_EN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_IRQ_EN_ADDR, m)
#define HWIO_AON_PME_ROT_IRQ_EN_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_IRQ_EN_ADDR,v)
#define HWIO_AON_PME_ROT_IRQ_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_IRQ_EN_ADDR,m,v,HWIO_AON_PME_ROT_IRQ_EN_IN)
#define HWIO_AON_PME_ROT_IRQ_EN_ACC_ERR_BMSK                          0x80000000
#define HWIO_AON_PME_ROT_IRQ_EN_ACC_ERR_SHFT                                0x1f
#define HWIO_AON_PME_ROT_IRQ_EN_PMU_ERR_BMSK                          0x40000000
#define HWIO_AON_PME_ROT_IRQ_EN_PMU_ERR_SHFT                                0x1e
#define HWIO_AON_PME_ROT_IRQ_EN_DEBUG_BMSK                            0x20000000
#define HWIO_AON_PME_ROT_IRQ_EN_DEBUG_SHFT                                  0x1d
#define HWIO_AON_PME_ROT_IRQ_EN_BAD_FOSC_BMSK                             0x2000
#define HWIO_AON_PME_ROT_IRQ_EN_BAD_FOSC_SHFT                                0xd
#define HWIO_AON_PME_ROT_IRQ_EN_REQUEST_BMSK                                0x80
#define HWIO_AON_PME_ROT_IRQ_EN_REQUEST_SHFT                                 0x7
#define HWIO_AON_PME_ROT_IRQ_EN_MFP_EDGE_BMSK                               0x40
#define HWIO_AON_PME_ROT_IRQ_EN_MFP_EDGE_SHFT                                0x6
#define HWIO_AON_PME_ROT_IRQ_EN_MFP_SHORT_BMSK                              0x20
#define HWIO_AON_PME_ROT_IRQ_EN_MFP_SHORT_SHFT                               0x5
#define HWIO_AON_PME_ROT_IRQ_EN_PIO_BMSK                                    0x10
#define HWIO_AON_PME_ROT_IRQ_EN_PIO_SHFT                                     0x4
#define HWIO_AON_PME_ROT_IRQ_EN_PMU_BMSK                                     0x8
#define HWIO_AON_PME_ROT_IRQ_EN_PMU_SHFT                                     0x3
#define HWIO_AON_PME_ROT_IRQ_EN_HFXTAL_TIMEOUT_BMSK                          0x2
#define HWIO_AON_PME_ROT_IRQ_EN_HFXTAL_TIMEOUT_SHFT                          0x1
#define HWIO_AON_PME_ROT_IRQ_EN_HFXTAL_STABLE_BMSK                           0x1
#define HWIO_AON_PME_ROT_IRQ_EN_HFXTAL_STABLE_SHFT                           0x0

#define HWIO_AON_PME_ROT_IRQ_PENDING_ADDR                             (AON_PME_PME_AC_REG_BASE      + 0x00000020)
#define HWIO_AON_PME_ROT_IRQ_PENDING_RMSK                             0xe00020fb
#define HWIO_AON_PME_ROT_IRQ_PENDING_IN          \
        in_dword(HWIO_AON_PME_ROT_IRQ_PENDING_ADDR)
#define HWIO_AON_PME_ROT_IRQ_PENDING_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_IRQ_PENDING_ADDR, m)
#define HWIO_AON_PME_ROT_IRQ_PENDING_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_IRQ_PENDING_ADDR,v)
#define HWIO_AON_PME_ROT_IRQ_PENDING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_IRQ_PENDING_ADDR,m,v,HWIO_AON_PME_ROT_IRQ_PENDING_IN)
#define HWIO_AON_PME_ROT_IRQ_PENDING_ACC_ERR_BMSK                     0x80000000
#define HWIO_AON_PME_ROT_IRQ_PENDING_ACC_ERR_SHFT                           0x1f
#define HWIO_AON_PME_ROT_IRQ_PENDING_PMU_ERR_BMSK                     0x40000000
#define HWIO_AON_PME_ROT_IRQ_PENDING_PMU_ERR_SHFT                           0x1e
#define HWIO_AON_PME_ROT_IRQ_PENDING_DEBUG_BMSK                       0x20000000
#define HWIO_AON_PME_ROT_IRQ_PENDING_DEBUG_SHFT                             0x1d
#define HWIO_AON_PME_ROT_IRQ_PENDING_BAD_FOSC_BMSK                        0x2000
#define HWIO_AON_PME_ROT_IRQ_PENDING_BAD_FOSC_SHFT                           0xd
#define HWIO_AON_PME_ROT_IRQ_PENDING_REQUEST_BMSK                           0x80
#define HWIO_AON_PME_ROT_IRQ_PENDING_REQUEST_SHFT                            0x7
#define HWIO_AON_PME_ROT_IRQ_PENDING_MFP_EDGE_BMSK                          0x40
#define HWIO_AON_PME_ROT_IRQ_PENDING_MFP_EDGE_SHFT                           0x6
#define HWIO_AON_PME_ROT_IRQ_PENDING_MFP_SHORT_BMSK                         0x20
#define HWIO_AON_PME_ROT_IRQ_PENDING_MFP_SHORT_SHFT                          0x5
#define HWIO_AON_PME_ROT_IRQ_PENDING_PIO_BMSK                               0x10
#define HWIO_AON_PME_ROT_IRQ_PENDING_PIO_SHFT                                0x4
#define HWIO_AON_PME_ROT_IRQ_PENDING_PMU_BMSK                                0x8
#define HWIO_AON_PME_ROT_IRQ_PENDING_PMU_SHFT                                0x3
#define HWIO_AON_PME_ROT_IRQ_PENDING_HFXTAL_TIMEOUT_BMSK                     0x2
#define HWIO_AON_PME_ROT_IRQ_PENDING_HFXTAL_TIMEOUT_SHFT                     0x1
#define HWIO_AON_PME_ROT_IRQ_PENDING_HFXTAL_STABLE_BMSK                      0x1
#define HWIO_AON_PME_ROT_IRQ_PENDING_HFXTAL_STABLE_SHFT                      0x0

#define HWIO_AON_PME_ROT_RESET_ADDR                                   (AON_PME_PME_AC_REG_BASE      + 0x00000028)
#define HWIO_AON_PME_ROT_RESET_RMSK                                   0xffffffff
#define HWIO_AON_PME_ROT_RESET_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_RESET_ADDR,v)
#define HWIO_AON_PME_ROT_RESET_CODE_BMSK                              0xffffffff
#define HWIO_AON_PME_ROT_RESET_CODE_SHFT                                     0x0

#define HWIO_AON_PME_ROT_SCRATCHPAD_ADDR                              (AON_PME_PME_AC_REG_BASE      + 0x00000030)
#define HWIO_AON_PME_ROT_SCRATCHPAD_RMSK                              0xffffffff
#define HWIO_AON_PME_ROT_SCRATCHPAD_IN          \
        in_dword(HWIO_AON_PME_ROT_SCRATCHPAD_ADDR)
#define HWIO_AON_PME_ROT_SCRATCHPAD_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_SCRATCHPAD_ADDR, m)
#define HWIO_AON_PME_ROT_SCRATCHPAD_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_SCRATCHPAD_ADDR,v)
#define HWIO_AON_PME_ROT_SCRATCHPAD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_SCRATCHPAD_ADDR,m,v,HWIO_AON_PME_ROT_SCRATCHPAD_IN)
#define HWIO_AON_PME_ROT_SCRATCHPAD_DATA_BMSK                         0xffffffff
#define HWIO_AON_PME_ROT_SCRATCHPAD_DATA_SHFT                                0x0

#define HWIO_AON_PME_ROT_PROC_REQ_ADDR                                (AON_PME_PME_AC_REG_BASE      + 0x000003fc)
#define HWIO_AON_PME_ROT_PROC_REQ_RMSK                                       0x3
#define HWIO_AON_PME_ROT_PROC_REQ_IN          \
        in_dword(HWIO_AON_PME_ROT_PROC_REQ_ADDR)
#define HWIO_AON_PME_ROT_PROC_REQ_INM(m)      \
        in_dword_masked(HWIO_AON_PME_ROT_PROC_REQ_ADDR, m)
#define HWIO_AON_PME_ROT_PROC_REQ_OUT(v)      \
        out_dword(HWIO_AON_PME_ROT_PROC_REQ_ADDR,v)
#define HWIO_AON_PME_ROT_PROC_REQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_ROT_PROC_REQ_ADDR,m,v,HWIO_AON_PME_ROT_PROC_REQ_IN)
#define HWIO_AON_PME_ROT_PROC_REQ_ACK_BMSK                                   0x2
#define HWIO_AON_PME_ROT_PROC_REQ_ACK_SHFT                                   0x1
#define HWIO_AON_PME_ROT_PROC_REQ_REQ_BMSK                                   0x1
#define HWIO_AON_PME_ROT_PROC_REQ_REQ_SHFT                                   0x0

#define HWIO_AON_PME_SOC_STATUS_ADDR                                  (AON_PME_PME_AC_REG_BASE      + 0x00000c00)
#define HWIO_AON_PME_SOC_STATUS_RMSK                                    0x7fffff
#define HWIO_AON_PME_SOC_STATUS_IN          \
        in_dword(HWIO_AON_PME_SOC_STATUS_ADDR)
#define HWIO_AON_PME_SOC_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_STATUS_ADDR, m)
#define HWIO_AON_PME_SOC_STATUS_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_STATUS_ADDR,v)
#define HWIO_AON_PME_SOC_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_STATUS_ADDR,m,v,HWIO_AON_PME_SOC_STATUS_IN)
#define HWIO_AON_PME_SOC_STATUS_BAD_XTAL_BMSK                           0x400000
#define HWIO_AON_PME_SOC_STATUS_BAD_XTAL_SHFT                               0x16
#define HWIO_AON_PME_SOC_STATUS_BAD_FOSC_BMSK                           0x200000
#define HWIO_AON_PME_SOC_STATUS_BAD_FOSC_SHFT                               0x15
#define HWIO_AON_PME_SOC_STATUS_RAM_PARAMS_WR_PENDING_BMSK              0x100000
#define HWIO_AON_PME_SOC_STATUS_RAM_PARAMS_WR_PENDING_SHFT                  0x14
#define HWIO_AON_PME_SOC_STATUS_TEST_MODE_BMSK                           0x80000
#define HWIO_AON_PME_SOC_STATUS_TEST_MODE_SHFT                              0x13
#define HWIO_AON_PME_SOC_STATUS_LFCLK_WR_PENDING_BMSK                    0x40000
#define HWIO_AON_PME_SOC_STATUS_LFCLK_WR_PENDING_SHFT                       0x12
#define HWIO_AON_PME_SOC_STATUS_DEBUG_START_PENDING_BMSK                 0x20000
#define HWIO_AON_PME_SOC_STATUS_DEBUG_START_PENDING_SHFT                    0x11
#define HWIO_AON_PME_SOC_STATUS_DEBUG_MODE_BMSK                          0x10000
#define HWIO_AON_PME_SOC_STATUS_DEBUG_MODE_SHFT                             0x10
#define HWIO_AON_PME_SOC_STATUS_LFCLK_BMSK                                0xc000
#define HWIO_AON_PME_SOC_STATUS_LFCLK_SHFT                                   0xe
#define HWIO_AON_PME_SOC_STATUS_TCLK_BMSK                                 0x2000
#define HWIO_AON_PME_SOC_STATUS_TCLK_SHFT                                    0xd
#define HWIO_AON_PME_SOC_STATUS_HFCLK_BMSK                                0x1000
#define HWIO_AON_PME_SOC_STATUS_HFCLK_SHFT                                   0xc
#define HWIO_AON_PME_SOC_STATUS_TLMM_BMSK                                  0xc00
#define HWIO_AON_PME_SOC_STATUS_TLMM_SHFT                                    0xa
#define HWIO_AON_PME_SOC_STATUS_PER_BMSK                                   0x300
#define HWIO_AON_PME_SOC_STATUS_PER_SHFT                                     0x8
#define HWIO_AON_PME_SOC_STATUS_NVM_BMSK                                    0xc0
#define HWIO_AON_PME_SOC_STATUS_NVM_SHFT                                     0x6
#define HWIO_AON_PME_SOC_STATUS_ROT_BMSK                                    0x30
#define HWIO_AON_PME_SOC_STATUS_ROT_SHFT                                     0x4
#define HWIO_AON_PME_SOC_STATUS_APPS_BMSK                                    0xc
#define HWIO_AON_PME_SOC_STATUS_APPS_SHFT                                    0x2
#define HWIO_AON_PME_SOC_STATUS_BT_BMSK                                      0x3
#define HWIO_AON_PME_SOC_STATUS_BT_SHFT                                      0x0

#define HWIO_AON_PME_SOC_CONTROL_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x00000c04)
#define HWIO_AON_PME_SOC_CONTROL_RMSK                                   0x1fffff
#define HWIO_AON_PME_SOC_CONTROL_IN          \
        in_dword(HWIO_AON_PME_SOC_CONTROL_ADDR)
#define HWIO_AON_PME_SOC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_CONTROL_ADDR, m)
#define HWIO_AON_PME_SOC_CONTROL_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_CONTROL_ADDR,v)
#define HWIO_AON_PME_SOC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_CONTROL_ADDR,m,v,HWIO_AON_PME_SOC_CONTROL_IN)
#define HWIO_AON_PME_SOC_CONTROL_TME_RESET_BMSK                         0x180000
#define HWIO_AON_PME_SOC_CONTROL_TME_RESET_SHFT                             0x13
#define HWIO_AON_PME_SOC_CONTROL_TEST_MODE_SHUTDOWN_EN_BMSK              0x40000
#define HWIO_AON_PME_SOC_CONTROL_TEST_MODE_SHUTDOWN_EN_SHFT                 0x12
#define HWIO_AON_PME_SOC_CONTROL_HFXTAL_CONST_OVRD_BMSK                  0x20000
#define HWIO_AON_PME_SOC_CONTROL_HFXTAL_CONST_OVRD_SHFT                     0x11
#define HWIO_AON_PME_SOC_CONTROL_TLMM_ACTIVE_BMSK                        0x10000
#define HWIO_AON_PME_SOC_CONTROL_TLMM_ACTIVE_SHFT                           0x10
#define HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_BMSK                   0x8000
#define HWIO_AON_PME_SOC_CONTROL_MFP_LONG_RESET_EN_SHFT                      0xf
#define HWIO_AON_PME_SOC_CONTROL_RTO_NORTH_EN_BMSK                        0x4000
#define HWIO_AON_PME_SOC_CONTROL_RTO_NORTH_EN_SHFT                           0xe
#define HWIO_AON_PME_SOC_CONTROL_RTO_SOUTH_EN_BMSK                        0x2000
#define HWIO_AON_PME_SOC_CONTROL_RTO_SOUTH_EN_SHFT                           0xd
#define HWIO_AON_PME_SOC_CONTROL_PME_DEEP_SLP_DBG_BMSK                    0x1000
#define HWIO_AON_PME_SOC_CONTROL_PME_DEEP_SLP_DBG_SHFT                       0xc
#define HWIO_AON_PME_SOC_CONTROL_DBG_NOWAKE_GTM_SEL_BMSK                   0xc00
#define HWIO_AON_PME_SOC_CONTROL_DBG_NOWAKE_GTM_SEL_SHFT                     0xa
#define HWIO_AON_PME_SOC_CONTROL_DBG_NOWAKE_PERIOD_BMSK                    0x3e0
#define HWIO_AON_PME_SOC_CONTROL_DBG_NOWAKE_PERIOD_SHFT                      0x5
#define HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_BMSK                       0x10
#define HWIO_AON_PME_SOC_CONTROL_MFP_NEGEDGE_DET_SHFT                        0x4
#define HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_BMSK                        0x8
#define HWIO_AON_PME_SOC_CONTROL_MFP_POSEDGE_DET_SHFT                        0x3
#define HWIO_AON_PME_SOC_CONTROL_CLR_DBG_PEND_BMSK                           0x4
#define HWIO_AON_PME_SOC_CONTROL_CLR_DBG_PEND_SHFT                           0x2
#define HWIO_AON_PME_SOC_CONTROL_LFCLK_BMSK                                  0x3
#define HWIO_AON_PME_SOC_CONTROL_LFCLK_SHFT                                  0x0

#define HWIO_AON_PME_SOC_RAM_ACK_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x00000c0c)
#define HWIO_AON_PME_SOC_RAM_ACK_RMSK                                     0xffff
#define HWIO_AON_PME_SOC_RAM_ACK_IN          \
        in_dword(HWIO_AON_PME_SOC_RAM_ACK_ADDR)
#define HWIO_AON_PME_SOC_RAM_ACK_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_RAM_ACK_ADDR, m)
#define HWIO_AON_PME_SOC_RAM_ACK_ACK_BMSK                                 0xffff
#define HWIO_AON_PME_SOC_RAM_ACK_ACK_SHFT                                    0x0

#define HWIO_AON_PME_SOC_DEBUG_ADDR                                   (AON_PME_PME_AC_REG_BASE      + 0x00000c10)
#define HWIO_AON_PME_SOC_DEBUG_RMSK                                        0x3ff
#define HWIO_AON_PME_SOC_DEBUG_IN          \
        in_dword(HWIO_AON_PME_SOC_DEBUG_ADDR)
#define HWIO_AON_PME_SOC_DEBUG_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_DEBUG_ADDR, m)
#define HWIO_AON_PME_SOC_DEBUG_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_DEBUG_ADDR,v)
#define HWIO_AON_PME_SOC_DEBUG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_DEBUG_ADDR,m,v,HWIO_AON_PME_SOC_DEBUG_IN)
#define HWIO_AON_PME_SOC_DEBUG_SEL1_BMSK                                   0x3e0
#define HWIO_AON_PME_SOC_DEBUG_SEL1_SHFT                                     0x5
#define HWIO_AON_PME_SOC_DEBUG_SEL0_BMSK                                    0x1f
#define HWIO_AON_PME_SOC_DEBUG_SEL0_SHFT                                     0x0

#define HWIO_AON_PME_SOC_NVM_CFG_ADDR                                 (AON_PME_PME_AC_REG_BASE      + 0x00000c14)
#define HWIO_AON_PME_SOC_NVM_CFG_RMSK                                      0x3ff
#define HWIO_AON_PME_SOC_NVM_CFG_IN          \
        in_dword(HWIO_AON_PME_SOC_NVM_CFG_ADDR)
#define HWIO_AON_PME_SOC_NVM_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_NVM_CFG_ADDR, m)
#define HWIO_AON_PME_SOC_NVM_CFG_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_NVM_CFG_ADDR,v)
#define HWIO_AON_PME_SOC_NVM_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_NVM_CFG_ADDR,m,v,HWIO_AON_PME_SOC_NVM_CFG_IN)
#define HWIO_AON_PME_SOC_NVM_CFG_COMP_DELAY_BMSK                           0x3c0
#define HWIO_AON_PME_SOC_NVM_CFG_COMP_DELAY_SHFT                             0x6
#define HWIO_AON_PME_SOC_NVM_CFG_OFFSET_DELAY_BMSK                          0x38
#define HWIO_AON_PME_SOC_NVM_CFG_OFFSET_DELAY_SHFT                           0x3
#define HWIO_AON_PME_SOC_NVM_CFG_VD_DELAY_BMSK                               0x7
#define HWIO_AON_PME_SOC_NVM_CFG_VD_DELAY_SHFT                               0x0

#define HWIO_AON_PME_SOC_OVERRIDES_EN_ADDR                            (AON_PME_PME_AC_REG_BASE      + 0x00000c08)
#define HWIO_AON_PME_SOC_OVERRIDES_EN_RMSK                              0x7ff7fb
#define HWIO_AON_PME_SOC_OVERRIDES_EN_IN          \
        in_dword(HWIO_AON_PME_SOC_OVERRIDES_EN_ADDR)
#define HWIO_AON_PME_SOC_OVERRIDES_EN_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_OVERRIDES_EN_ADDR, m)
#define HWIO_AON_PME_SOC_OVERRIDES_EN_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_OVERRIDES_EN_ADDR,v)
#define HWIO_AON_PME_SOC_OVERRIDES_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_OVERRIDES_EN_ADDR,m,v,HWIO_AON_PME_SOC_OVERRIDES_EN_IN)
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_ROM_SD_BMSK                    0x400000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_ROM_SD_SHFT                        0x16
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_ROM_SD_BMSK                   0x200000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_ROM_SD_SHFT                       0x15
#define HWIO_AON_PME_SOC_OVERRIDES_EN_VDIO_BMSK                         0x100000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_VDIO_SHFT                             0x14
#define HWIO_AON_PME_SOC_OVERRIDES_EN_DISPLAY_BMSK                       0x80000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_DISPLAY_SHFT                          0x13
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BROWNOUT_BMSK                      0x40000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BROWNOUT_SHFT                         0x12
#define HWIO_AON_PME_SOC_OVERRIDES_EN_TLMM_ARESET_BMSK                   0x20000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_TLMM_ARESET_SHFT                      0x11
#define HWIO_AON_PME_SOC_OVERRIDES_EN_TLMM_HF_CLK_EN_BMSK                0x10000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_TLMM_HF_CLK_EN_SHFT                   0x10
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SHMEM_ARESET_BMSK                   0x8000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SHMEM_ARESET_SHFT                      0xf
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SHMEM_HF_CLK_EN_BMSK                0x4000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SHMEM_HF_CLK_EN_SHFT                   0xe
#define HWIO_AON_PME_SOC_OVERRIDES_EN_PERIPH_ARESET_BMSK                  0x2000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_PERIPH_ARESET_SHFT                     0xd
#define HWIO_AON_PME_SOC_OVERRIDES_EN_PERIPH_HF_CLK_EN_BMSK               0x1000
#define HWIO_AON_PME_SOC_OVERRIDES_EN_PERIPH_HF_CLK_EN_SHFT                  0xc
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_ARESET_BMSK                      0x400
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_ARESET_SHFT                        0xa
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_HF_CLK_EN_BMSK                   0x200
#define HWIO_AON_PME_SOC_OVERRIDES_EN_ROT_HF_CLK_EN_SHFT                     0x9
#define HWIO_AON_PME_SOC_OVERRIDES_EN_APPS_ARESET_BMSK                     0x100
#define HWIO_AON_PME_SOC_OVERRIDES_EN_APPS_ARESET_SHFT                       0x8
#define HWIO_AON_PME_SOC_OVERRIDES_EN_APPS_HF_CLK_EN_BMSK                   0x80
#define HWIO_AON_PME_SOC_OVERRIDES_EN_APPS_HF_CLK_EN_SHFT                    0x7
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_ARESET_BMSK                        0x40
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_ARESET_SHFT                         0x6
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_HF_CLK_EN_BMSK                     0x20
#define HWIO_AON_PME_SOC_OVERRIDES_EN_BT_HF_CLK_EN_SHFT                      0x5
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SOSC_REQ_BMSK                         0x10
#define HWIO_AON_PME_SOC_OVERRIDES_EN_SOSC_REQ_SHFT                          0x4
#define HWIO_AON_PME_SOC_OVERRIDES_EN_RTO_BMSK                               0x8
#define HWIO_AON_PME_SOC_OVERRIDES_EN_RTO_SHFT                               0x3
#define HWIO_AON_PME_SOC_OVERRIDES_EN_LFCLK_BMSK                             0x2
#define HWIO_AON_PME_SOC_OVERRIDES_EN_LFCLK_SHFT                             0x1
#define HWIO_AON_PME_SOC_OVERRIDES_EN_HFCLK_BMSK                             0x1
#define HWIO_AON_PME_SOC_OVERRIDES_EN_HFCLK_SHFT                             0x0

#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ADDR                           (AON_PME_PME_AC_REG_BASE      + 0x00000c18)
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_RMSK                             0x7ff7ff
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_IN          \
        in_dword(HWIO_AON_PME_SOC_OVERRIDES_VAL_ADDR)
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_OVERRIDES_VAL_ADDR, m)
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_OVERRIDES_VAL_ADDR,v)
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_OVERRIDES_VAL_ADDR,m,v,HWIO_AON_PME_SOC_OVERRIDES_VAL_IN)
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_ROM_SD_BMSK                   0x400000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_ROM_SD_SHFT                       0x16
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_ROM_SD_BMSK                  0x200000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_ROM_SD_SHFT                      0x15
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_VDIO_BMSK                        0x100000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_VDIO_SHFT                            0x14
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_DISPLAY_BMSK                      0x80000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_DISPLAY_SHFT                         0x13
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BROWNOUT_BMSK                     0x40000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BROWNOUT_SHFT                        0x12
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_TLMM_ARESET_BMSK                  0x20000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_TLMM_ARESET_SHFT                     0x11
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_TLMM_HF_CLK_EN_BMSK               0x10000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_TLMM_HF_CLK_EN_SHFT                  0x10
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SHMEM_ARESET_BMSK                  0x8000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SHMEM_ARESET_SHFT                     0xf
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SHMEM_HF_CLK_EN_BMSK               0x4000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SHMEM_HF_CLK_EN_SHFT                  0xe
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_PERIPH_ARESET_BMSK                 0x2000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_PERIPH_ARESET_SHFT                    0xd
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_PERIPH_HF_CLK_EN_BMSK              0x1000
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_PERIPH_HF_CLK_EN_SHFT                 0xc
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_ARESET_BMSK                     0x400
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_ARESET_SHFT                       0xa
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_HF_CLK_EN_BMSK                  0x200
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_ROT_HF_CLK_EN_SHFT                    0x9
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_APPS_ARESET_BMSK                    0x100
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_APPS_ARESET_SHFT                      0x8
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_APPS_HF_CLK_EN_BMSK                  0x80
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_APPS_HF_CLK_EN_SHFT                   0x7
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_ARESET_BMSK                       0x40
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_ARESET_SHFT                        0x6
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_HF_CLK_EN_BMSK                    0x20
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_BT_HF_CLK_EN_SHFT                     0x5
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SOSC_REQ_BMSK                        0x10
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_SOSC_REQ_SHFT                         0x4
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_RTO_BMSK                              0x8
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_RTO_SHFT                              0x3
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_LFCLK_BMSK                            0x6
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_LFCLK_SHFT                            0x1
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_HFCLK_BMSK                            0x1
#define HWIO_AON_PME_SOC_OVERRIDES_VAL_HFCLK_SHFT                            0x0

#define HWIO_AON_PME_SOC_RAM_PARAMS_ADDR                              (AON_PME_PME_AC_REG_BASE      + 0x00000c1c)
#define HWIO_AON_PME_SOC_RAM_PARAMS_RMSK                                  0xffff
#define HWIO_AON_PME_SOC_RAM_PARAMS_IN          \
        in_dword(HWIO_AON_PME_SOC_RAM_PARAMS_ADDR)
#define HWIO_AON_PME_SOC_RAM_PARAMS_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_RAM_PARAMS_ADDR, m)
#define HWIO_AON_PME_SOC_RAM_PARAMS_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_RAM_PARAMS_ADDR,v)
#define HWIO_AON_PME_SOC_RAM_PARAMS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_RAM_PARAMS_ADDR,m,v,HWIO_AON_PME_SOC_RAM_PARAMS_IN)
#define HWIO_AON_PME_SOC_RAM_PARAMS_PL1_900MV_DELAY_BMSK                  0xff00
#define HWIO_AON_PME_SOC_RAM_PARAMS_PL1_900MV_DELAY_SHFT                     0x8
#define HWIO_AON_PME_SOC_RAM_PARAMS_PL0_900MV_DELAY_BMSK                    0xff
#define HWIO_AON_PME_SOC_RAM_PARAMS_PL0_900MV_DELAY_SHFT                     0x0

#define HWIO_AON_PME_SOC_DIAGNOSTIC_ADDR                              (AON_PME_PME_AC_REG_BASE      + 0x00000c20)
#define HWIO_AON_PME_SOC_DIAGNOSTIC_RMSK                              0x8fff03ff
#define HWIO_AON_PME_SOC_DIAGNOSTIC_IN          \
        in_dword(HWIO_AON_PME_SOC_DIAGNOSTIC_ADDR)
#define HWIO_AON_PME_SOC_DIAGNOSTIC_INM(m)      \
        in_dword_masked(HWIO_AON_PME_SOC_DIAGNOSTIC_ADDR, m)
#define HWIO_AON_PME_SOC_DIAGNOSTIC_OUT(v)      \
        out_dword(HWIO_AON_PME_SOC_DIAGNOSTIC_ADDR,v)
#define HWIO_AON_PME_SOC_DIAGNOSTIC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_PME_SOC_DIAGNOSTIC_ADDR,m,v,HWIO_AON_PME_SOC_DIAGNOSTIC_IN)
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_SUBSYS_SW_BMSK                  0x80000000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_SUBSYS_SW_SHFT                        0x1f
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_APPS_BMSK              0x8000000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_APPS_SHFT                   0x1b
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_BT_BMSK                0x4000000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_BT_SHFT                     0x1a
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_ROT_BMSK               0x2000000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_WDOG_ROT_SHFT                    0x19
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_SW_BMSK                     0x1000000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_WARM_SW_SHFT                          0x18
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_APPS_BMSK               0x800000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_APPS_SHFT                   0x17
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_BT_BMSK                 0x400000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_BT_SHFT                     0x16
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_ROT_BMSK                0x200000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_WDOG_ROT_SHFT                    0x15
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_MFB_BMSK                     0x100000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_MFB_SHFT                         0x14
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_BROWNOUT_BMSK                 0x80000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_BROWNOUT_SHFT                    0x13
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_SW_BMSK                       0x40000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_SW_SHFT                          0x12
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_VDIO_BMSK                     0x20000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_COLD_VDIO_SHFT                        0x11
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_POR_BATT_BMSK                      0x10000
#define HWIO_AON_PME_SOC_DIAGNOSTIC_R_POR_BATT_SHFT                         0x10
#define HWIO_AON_PME_SOC_DIAGNOSTIC_FSM_HFCLK_BMSK                         0x3c0
#define HWIO_AON_PME_SOC_DIAGNOSTIC_FSM_HFCLK_SHFT                           0x6
#define HWIO_AON_PME_SOC_DIAGNOSTIC_FSM_MAIN_BMSK                           0x3f
#define HWIO_AON_PME_SOC_DIAGNOSTIC_FSM_MAIN_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_GBLTMR_HZ_GL_TMR
 *--------------------------------------------------------------------------*/

#define AON_GBLTMR_HZ_GL_TMR_REG_BASE                                       (AON_GBLTMR_HZ_GL_TMR_BASE      + 0x00000000)
#define AON_GBLTMR_HZ_GL_TMR_REG_BASE_SIZE                                  0x400
#define AON_GBLTMR_HZ_GL_TMR_REG_BASE_USED                                  0x84

#define HWIO_AON_GBLTMR_MAIN_CTRL_ADDR                                      (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000000)
#define HWIO_AON_GBLTMR_MAIN_CTRL_RMSK                                             0x1
#define HWIO_AON_GBLTMR_MAIN_CTRL_IN          \
        in_dword(HWIO_AON_GBLTMR_MAIN_CTRL_ADDR)
#define HWIO_AON_GBLTMR_MAIN_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_MAIN_CTRL_ADDR, m)
#define HWIO_AON_GBLTMR_MAIN_CTRL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_MAIN_CTRL_ADDR,v)
#define HWIO_AON_GBLTMR_MAIN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_MAIN_CTRL_ADDR,m,v,HWIO_AON_GBLTMR_MAIN_CTRL_IN)
#define HWIO_AON_GBLTMR_MAIN_CTRL_GLTMR_BLK_EN_BMSK                                0x1
#define HWIO_AON_GBLTMR_MAIN_CTRL_GLTMR_BLK_EN_SHFT                                0x0

#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_ADDR                                (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000004)
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_RMSK                                     0x1ff
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_IN          \
        in_dword(HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_ADDR)
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_ADDR, m)
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_ADDR,v)
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_ADDR,m,v,HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_IN)
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_DUR_BMSK                                 0x1ff
#define HWIO_AON_GBLTMR_SYS_WAKEUP_TIME_DUR_SHFT                                   0x0

#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_ADDR                                  (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000008)
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_RMSK                                    0x3fffff
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_IN          \
        in_dword(HWIO_AON_GBLTMR_SYS_LPO_COUNT_ADDR)
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SYS_LPO_COUNT_ADDR, m)
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SYS_LPO_COUNT_ADDR,v)
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SYS_LPO_COUNT_ADDR,m,v,HWIO_AON_GBLTMR_SYS_LPO_COUNT_IN)
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_VAL_BMSK                                0x3fffff
#define HWIO_AON_GBLTMR_SYS_LPO_COUNT_VAL_SHFT                                     0x0

#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_ADDR                                   (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000000c)
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_RMSK                                          0x1
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_IN          \
        in_dword(HWIO_AON_GBLTMR_SYS_TMR_SYNC_ADDR)
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SYS_TMR_SYNC_ADDR, m)
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SYS_TMR_SYNC_ADDR,v)
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SYS_TMR_SYNC_ADDR,m,v,HWIO_AON_GBLTMR_SYS_TMR_SYNC_IN)
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_CAPT_BMSK                                     0x1
#define HWIO_AON_GBLTMR_SYS_TMR_SYNC_CAPT_SHFT                                     0x0

#define HWIO_AON_GBLTMR_SYS_STAT_ADDR                                       (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000010)
#define HWIO_AON_GBLTMR_SYS_STAT_RMSK                                       0x3fffffff
#define HWIO_AON_GBLTMR_SYS_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SYS_STAT_ADDR)
#define HWIO_AON_GBLTMR_SYS_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SYS_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SYS_STAT_REF_CLK_MODE_BMSK                          0x30000000
#define HWIO_AON_GBLTMR_SYS_STAT_REF_CLK_MODE_SHFT                                0x1c
#define HWIO_AON_GBLTMR_SYS_STAT_INT_OUTPUT_BMSK                             0x8000000
#define HWIO_AON_GBLTMR_SYS_STAT_INT_OUTPUT_SHFT                                  0x1b
#define HWIO_AON_GBLTMR_SYS_STAT_HUGE_CMPR0_STAT_BMSK                        0x7000000
#define HWIO_AON_GBLTMR_SYS_STAT_HUGE_CMPR0_STAT_SHFT                             0x18
#define HWIO_AON_GBLTMR_SYS_STAT_WAKEUP_REQ_BMSK                              0x800000
#define HWIO_AON_GBLTMR_SYS_STAT_WAKEUP_REQ_SHFT                                  0x17
#define HWIO_AON_GBLTMR_SYS_STAT_CLKS_ACTIVE_BMSK                             0x400000
#define HWIO_AON_GBLTMR_SYS_STAT_CLKS_ACTIVE_SHFT                                 0x16
#define HWIO_AON_GBLTMR_SYS_STAT_LPO_COUNT_VAL_BMSK                           0x3fffff
#define HWIO_AON_GBLTMR_SYS_STAT_LPO_COUNT_VAL_SHFT                                0x0

#define HWIO_AON_GBLTMR_TMR_UPDATE_ADDR                                     (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000014)
#define HWIO_AON_GBLTMR_TMR_UPDATE_RMSK                                          0x10f
#define HWIO_AON_GBLTMR_TMR_UPDATE_IN          \
        in_dword(HWIO_AON_GBLTMR_TMR_UPDATE_ADDR)
#define HWIO_AON_GBLTMR_TMR_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_TMR_UPDATE_ADDR, m)
#define HWIO_AON_GBLTMR_TMR_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_TMR_UPDATE_ADDR,v)
#define HWIO_AON_GBLTMR_TMR_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_TMR_UPDATE_ADDR,m,v,HWIO_AON_GBLTMR_TMR_UPDATE_IN)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MODE_BMSK                                     0x100
#define HWIO_AON_GBLTMR_TMR_UPDATE_MODE_SHFT                                       0x8
#define HWIO_AON_GBLTMR_TMR_UPDATE_FRAC_TIME_BMSK                                  0xf
#define HWIO_AON_GBLTMR_TMR_UPDATE_FRAC_TIME_SHFT                                  0x0

#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_ADDR                            (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000018)
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_RMSK                            0xffffffff
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_ADDR)
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_ADDR,v)
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_ADDR,m,v,HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_IN)
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_USEC_TIME_BMSK                  0xffffffff
#define HWIO_AON_GBLTMR_TMR_UPDATE_USEC_VAL_USEC_TIME_SHFT                         0x0

#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_ADDR                             (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000001c)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_RMSK                                  0xfff
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_ADDR)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_ADDR,v)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_ADDR,m,v,HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_IN)
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_MSB_TIME_BMSK                         0xfff
#define HWIO_AON_GBLTMR_TMR_UPDATE_MSB_VAL_MSB_TIME_SHFT                           0x0

#define HWIO_AON_GBLTMR_SWCAPT_CFG_ADDR                                     (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000020)
#define HWIO_AON_GBLTMR_SWCAPT_CFG_RMSK                                         0x1111
#define HWIO_AON_GBLTMR_SWCAPT_CFG_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_CFG_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_CFG_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_CFG_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SWCAPT_CFG_ADDR,v)
#define HWIO_AON_GBLTMR_SWCAPT_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SWCAPT_CFG_ADDR,m,v,HWIO_AON_GBLTMR_SWCAPT_CFG_IN)
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_HUGE_CMPR0_BMSK                      0x1000
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_HUGE_CMPR0_SHFT                         0xc
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_TMR_SYNC_BMSK                         0x100
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_TMR_SYNC_SHFT                           0x8
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_TMR_UPDATE_BMSK                        0x10
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_EN_TMR_UPDATE_SHFT                         0x4
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_HOLD_EN_BMSK                               0x1
#define HWIO_AON_GBLTMR_SWCAPT_CFG_CAPT_HOLD_EN_SHFT                               0x0

#define HWIO_AON_GBLTMR_SWCAPT_CAPT_ADDR                                    (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000024)
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_RMSK                                           0x1
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_CAPT_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_CAPT_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SWCAPT_CAPT_ADDR,v)
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SWCAPT_CAPT_ADDR,m,v,HWIO_AON_GBLTMR_SWCAPT_CAPT_IN)
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_MODE_BMSK                                      0x1
#define HWIO_AON_GBLTMR_SWCAPT_CAPT_MODE_SHFT                                      0x0

#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_ADDR                            (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000028)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_RMSK                                   0xf
#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_TIME_BMSK                              0xf
#define HWIO_AON_GBLTMR_SWCAPT_TMR_FRAC_VAL_TIME_SHFT                              0x0

#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_ADDR                            (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000002c)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_RMSK                            0xffffffff
#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_TIME_BMSK                       0xffffffff
#define HWIO_AON_GBLTMR_SWCAPT_TMR_USEC_VAL_TIME_SHFT                              0x0

#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_ADDR                             (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000030)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_RMSK                                  0xfff
#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_TIME_BMSK                             0xfff
#define HWIO_AON_GBLTMR_SWCAPT_TMR_MSB_VAL_TIME_SHFT                               0x0

#define HWIO_AON_GBLTMR_SWCAPT_STAT_ADDR                                    (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000038)
#define HWIO_AON_GBLTMR_SWCAPT_STAT_RMSK                                           0x7
#define HWIO_AON_GBLTMR_SWCAPT_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SWCAPT_STAT_ADDR)
#define HWIO_AON_GBLTMR_SWCAPT_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SWCAPT_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SWCAPT_STAT_STAT_BMSK                                      0x7
#define HWIO_AON_GBLTMR_SWCAPT_STAT_STAT_SHFT                                      0x0

#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_ADDR                                 (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000040)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_RMSK                                 0xffffffff
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_IN          \
        in_dword(HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_ADDR)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_ADDR, m)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_ADDR,v)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_ADDR,m,v,HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_IN)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_CMPR_VAL_BMSK                        0xffffffff
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CMD_CMPR_VAL_SHFT                               0x0

#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_ADDR                                 (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000044)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_RMSK                                        0x1
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_IN          \
        in_dword(HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_ADDR)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_ADDR, m)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_ADDR,v)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_ADDR,m,v,HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_IN)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_MODE_BMSK                                   0x1
#define HWIO_AON_GBLTMR_HUGE_CMPR0_CFG_MODE_SHFT                                   0x0

#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_ADDR                                (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000048)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_RMSK                                0xf0000001
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_ADDR)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_LATE_DET_BMSK                       0x80000000
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_LATE_DET_SHFT                             0x1f
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_STAT_BMSK                           0x70000000
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_STAT_SHFT                                 0x1c
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_WAKEUP_REQ_BMSK                            0x1
#define HWIO_AON_GBLTMR_HUGE_CMPR0_STAT_WAKEUP_REQ_SHFT                            0x0

#define HWIO_AON_GBLTMR_INT_CTRL_ADDR                                       (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000050)
#define HWIO_AON_GBLTMR_INT_CTRL_RMSK                                              0x1
#define HWIO_AON_GBLTMR_INT_CTRL_IN          \
        in_dword(HWIO_AON_GBLTMR_INT_CTRL_ADDR)
#define HWIO_AON_GBLTMR_INT_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_INT_CTRL_ADDR, m)
#define HWIO_AON_GBLTMR_INT_CTRL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_INT_CTRL_ADDR,v)
#define HWIO_AON_GBLTMR_INT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_INT_CTRL_ADDR,m,v,HWIO_AON_GBLTMR_INT_CTRL_IN)
#define HWIO_AON_GBLTMR_INT_CTRL_OUT_EN_BMSK                                       0x1
#define HWIO_AON_GBLTMR_INT_CTRL_OUT_EN_SHFT                                       0x0

#define HWIO_AON_GBLTMR_INT_CLR_ADDR                                        (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000054)
#define HWIO_AON_GBLTMR_INT_CLR_RMSK                                               0x7
#define HWIO_AON_GBLTMR_INT_CLR_IN          \
        in_dword(HWIO_AON_GBLTMR_INT_CLR_ADDR)
#define HWIO_AON_GBLTMR_INT_CLR_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_INT_CLR_ADDR, m)
#define HWIO_AON_GBLTMR_INT_CLR_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_INT_CLR_ADDR,v)
#define HWIO_AON_GBLTMR_INT_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_INT_CLR_ADDR,m,v,HWIO_AON_GBLTMR_INT_CLR_IN)
#define HWIO_AON_GBLTMR_INT_CLR_CLR_BMSK                                           0x7
#define HWIO_AON_GBLTMR_INT_CLR_CLR_SHFT                                           0x0

#define HWIO_AON_GBLTMR_INT_UNMASK_ADDR                                     (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000058)
#define HWIO_AON_GBLTMR_INT_UNMASK_RMSK                                            0x7
#define HWIO_AON_GBLTMR_INT_UNMASK_IN          \
        in_dword(HWIO_AON_GBLTMR_INT_UNMASK_ADDR)
#define HWIO_AON_GBLTMR_INT_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_INT_UNMASK_ADDR, m)
#define HWIO_AON_GBLTMR_INT_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_INT_UNMASK_ADDR,v)
#define HWIO_AON_GBLTMR_INT_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_INT_UNMASK_ADDR,m,v,HWIO_AON_GBLTMR_INT_UNMASK_IN)
#define HWIO_AON_GBLTMR_INT_UNMASK_UNMASK_BMSK                                     0x7
#define HWIO_AON_GBLTMR_INT_UNMASK_UNMASK_SHFT                                     0x0

#define HWIO_AON_GBLTMR_INT_RAW_STAT_ADDR                                   (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000005c)
#define HWIO_AON_GBLTMR_INT_RAW_STAT_RMSK                                          0x7
#define HWIO_AON_GBLTMR_INT_RAW_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_INT_RAW_STAT_ADDR)
#define HWIO_AON_GBLTMR_INT_RAW_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_INT_RAW_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_INT_RAW_STAT_STAT_BMSK                                     0x7
#define HWIO_AON_GBLTMR_INT_RAW_STAT_STAT_SHFT                                     0x0

#define HWIO_AON_GBLTMR_INT_MASKED_STAT_ADDR                                (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000060)
#define HWIO_AON_GBLTMR_INT_MASKED_STAT_RMSK                                       0x7
#define HWIO_AON_GBLTMR_INT_MASKED_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_INT_MASKED_STAT_ADDR)
#define HWIO_AON_GBLTMR_INT_MASKED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_INT_MASKED_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_INT_MASKED_STAT_STAT_BMSK                                  0x7
#define HWIO_AON_GBLTMR_INT_MASKED_STAT_STAT_SHFT                                  0x0

#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_ADDR                               (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000006c)
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_RMSK                                     0x13
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_IN          \
        in_dword(HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_ADDR)
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_ADDR, m)
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_ADDR,v)
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_ADDR,m,v,HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_IN)
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_OVRD_EN_BMSK                             0x10
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_OVRD_EN_SHFT                              0x4
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_MODE_BMSK                                 0x3
#define HWIO_AON_GBLTMR_DBG_REF_CLK_OVRD_MODE_SHFT                                 0x0

#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_ADDR                               (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000070)
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_RMSK                                0x1111011
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_IN          \
        in_dword(HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_ADDR)
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_ADDR, m)
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_ADDR,v)
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_ADDR,m,v,HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_IN)
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_SLEEP_BMSK           0x1000000
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_SLEEP_SHFT                0x18
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CAPT_BMSK             0x100000
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CAPT_SHFT                 0x14
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CMPR_BMSK              0x10000
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CMPR_SHFT                 0x10
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CNTR_BMSK               0x1000
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_FORCECLK_GLTMR_CNTR_SHFT                  0xc
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_SOFTRST_GLTMR_SYS_BMSK                   0x10
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_SOFTRST_GLTMR_SYS_SHFT                    0x4
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_SOFTRST_GLTMR_CNTR_BMSK                   0x1
#define HWIO_AON_GBLTMR_DBG_CLK_RST_OVRD_SOFTRST_GLTMR_CNTR_SHFT                   0x0

#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_ADDR                               (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000074)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_RMSK                                    0xf0f
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_IN          \
        in_dword(HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_ADDR)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_ADDR, m)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_ADDR,v)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_ADDR,m,v,HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_IN)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_BMSK                       0xf00
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_SHFT                         0x8
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_BMSK                         0xf
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_SHFT                         0x0

#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_ADDR                                 (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000078)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_RMSK                                 0xffffffff
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_IN          \
        in_dword(HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_ADDR)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_ADDR, m)
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_TMX_DBG_OUT_BMSK                     0xffffffff
#define HWIO_AON_GBLTMR_DBG_OUT_BUS_RB_TMX_DBG_OUT_SHFT                            0x0

#define HWIO_AON_GBLTMR_SPARE_0_ADDR                                        (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x0000007c)
#define HWIO_AON_GBLTMR_SPARE_0_RMSK                                               0xf
#define HWIO_AON_GBLTMR_SPARE_0_IN          \
        in_dword(HWIO_AON_GBLTMR_SPARE_0_ADDR)
#define HWIO_AON_GBLTMR_SPARE_0_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SPARE_0_ADDR, m)
#define HWIO_AON_GBLTMR_SPARE_0_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SPARE_0_ADDR,v)
#define HWIO_AON_GBLTMR_SPARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SPARE_0_ADDR,m,v,HWIO_AON_GBLTMR_SPARE_0_IN)
#define HWIO_AON_GBLTMR_SPARE_0_SPARE_REG_BMSK                                     0xf
#define HWIO_AON_GBLTMR_SPARE_0_SPARE_REG_SHFT                                     0x0

#define HWIO_AON_GBLTMR_SPARE_1_ADDR                                        (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000080)
#define HWIO_AON_GBLTMR_SPARE_1_RMSK                                               0xf
#define HWIO_AON_GBLTMR_SPARE_1_IN          \
        in_dword(HWIO_AON_GBLTMR_SPARE_1_ADDR)
#define HWIO_AON_GBLTMR_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SPARE_1_ADDR, m)
#define HWIO_AON_GBLTMR_SPARE_1_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SPARE_1_ADDR,v)
#define HWIO_AON_GBLTMR_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SPARE_1_ADDR,m,v,HWIO_AON_GBLTMR_SPARE_1_IN)
#define HWIO_AON_GBLTMR_SPARE_1_SPARE_REG_BMSK                                     0xf
#define HWIO_AON_GBLTMR_SPARE_1_SPARE_REG_SHFT                                     0x0

#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_ADDR                               (AON_GBLTMR_HZ_GL_TMR_REG_BASE      + 0x00000084)
#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_RMSK                                      0x1
#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_IN          \
        in_dword(HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_ADDR)
#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_ADDR, m)
#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_TP_COMB_RST_XOR_BMSK                      0x1
#define HWIO_AON_GBLTMR_DFT_SCAN_OBSERVE_TP_COMB_RST_XOR_SHFT                      0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_GBLTMR_SLV_HZ_GL_TMR_SLV
 *--------------------------------------------------------------------------*/

#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE                           (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_BASE      + 0x00000000)
#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE_SIZE                      0x400
#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE_USED                      0x78

#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_ADDR                        (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000004)
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_RMSK                             0x1ff
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_ADDR)
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_ADDR,m,v,HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_IN)
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_DUR_BMSK                         0x1ff
#define HWIO_AON_GBLTMR_SLV_SYS_WAKEUP_TIME_DUR_SHFT                           0x0

#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_ADDR                           (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x0000000c)
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_RMSK                                  0x1
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_ADDR)
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_ADDR,m,v,HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_IN)
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_CAPT_BMSK                             0x1
#define HWIO_AON_GBLTMR_SLV_SYS_TMR_SYNC_CAPT_SHFT                             0x0

#define HWIO_AON_GBLTMR_SLV_SYS_STAT_ADDR                               (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000010)
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_RMSK                               0x3fffffff
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SYS_STAT_ADDR)
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SYS_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_REF_CLK_MODE_BMSK                  0x30000000
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_REF_CLK_MODE_SHFT                        0x1c
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_INT_OUTPUT_BMSK                     0x8000000
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_INT_OUTPUT_SHFT                          0x1b
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_HUGE_CMPR0_STAT_BMSK                0x7000000
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_HUGE_CMPR0_STAT_SHFT                     0x18
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_WAKEUP_REQ_BMSK                      0x800000
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_WAKEUP_REQ_SHFT                          0x17
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_CLKS_ACTIVE_BMSK                     0x400000
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_CLKS_ACTIVE_SHFT                         0x16
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_LPO_COUNT_VAL_BMSK                   0x3fffff
#define HWIO_AON_GBLTMR_SLV_SYS_STAT_LPO_COUNT_VAL_SHFT                        0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_ADDR                             (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000020)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_RMSK                                 0x1111
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_ADDR,m,v,HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_IN)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_HUGE_CMPR0_BMSK              0x1000
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_HUGE_CMPR0_SHFT                 0xc
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_SYNC_BMSK                 0x100
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_SYNC_SHFT                   0x8
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_UPDATE_BMSK                0x10
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_EN_TMR_UPDATE_SHFT                 0x4
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_HOLD_EN_BMSK                       0x1
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CFG_CAPT_HOLD_EN_SHFT                       0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_ADDR                            (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000024)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_RMSK                                   0x1
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_ADDR,m,v,HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_IN)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_MODE_BMSK                              0x1
#define HWIO_AON_GBLTMR_SLV_SWCAPT_CAPT_MODE_SHFT                              0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_ADDR                    (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000028)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_RMSK                           0xf
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_TIME_BMSK                      0xf
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_FRAC_VAL_TIME_SHFT                      0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_ADDR                    (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x0000002c)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_RMSK                    0xffffffff
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_TIME_BMSK               0xffffffff
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_USEC_VAL_TIME_SHFT                      0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_ADDR                     (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000030)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_RMSK                          0xfff
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_TIME_BMSK                     0xfff
#define HWIO_AON_GBLTMR_SLV_SWCAPT_TMR_MSB_VAL_TIME_SHFT                       0x0

#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_ADDR                            (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000038)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_RMSK                                   0x7
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_ADDR)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_STAT_BMSK                              0x7
#define HWIO_AON_GBLTMR_SLV_SWCAPT_STAT_STAT_SHFT                              0x0

#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_ADDR                         (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000040)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_RMSK                         0xffffffff
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_ADDR)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_ADDR,m,v,HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_IN)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_CMPR_VAL_BMSK                0xffffffff
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CMD_CMPR_VAL_SHFT                       0x0

#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_ADDR                         (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000044)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_RMSK                                0x1
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_ADDR)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_ADDR,m,v,HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_IN)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_MODE_BMSK                           0x1
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_CFG_MODE_SHFT                           0x0

#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_ADDR                        (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000048)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_RMSK                        0xf0000001
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_ADDR)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_LATE_DET_BMSK               0x80000000
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_LATE_DET_SHFT                     0x1f
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_STAT_BMSK                   0x70000000
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_STAT_SHFT                         0x1c
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_WAKEUP_REQ_BMSK                    0x1
#define HWIO_AON_GBLTMR_SLV_HUGE_CMPR0_STAT_WAKEUP_REQ_SHFT                    0x0

#define HWIO_AON_GBLTMR_SLV_INT_CTRL_ADDR                               (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000050)
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_RMSK                                      0x1
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_INT_CTRL_ADDR)
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_INT_CTRL_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_INT_CTRL_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_INT_CTRL_ADDR,m,v,HWIO_AON_GBLTMR_SLV_INT_CTRL_IN)
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_OUT_EN_BMSK                               0x1
#define HWIO_AON_GBLTMR_SLV_INT_CTRL_OUT_EN_SHFT                               0x0

#define HWIO_AON_GBLTMR_SLV_INT_CLR_ADDR                                (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000054)
#define HWIO_AON_GBLTMR_SLV_INT_CLR_RMSK                                       0x7
#define HWIO_AON_GBLTMR_SLV_INT_CLR_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_INT_CLR_ADDR)
#define HWIO_AON_GBLTMR_SLV_INT_CLR_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_INT_CLR_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_INT_CLR_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_INT_CLR_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_INT_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_INT_CLR_ADDR,m,v,HWIO_AON_GBLTMR_SLV_INT_CLR_IN)
#define HWIO_AON_GBLTMR_SLV_INT_CLR_CLR_BMSK                                   0x7
#define HWIO_AON_GBLTMR_SLV_INT_CLR_CLR_SHFT                                   0x0

#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_ADDR                             (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000058)
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_RMSK                                    0x7
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_INT_UNMASK_ADDR)
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_INT_UNMASK_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_INT_UNMASK_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_INT_UNMASK_ADDR,m,v,HWIO_AON_GBLTMR_SLV_INT_UNMASK_IN)
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_UNMASK_BMSK                             0x7
#define HWIO_AON_GBLTMR_SLV_INT_UNMASK_UNMASK_SHFT                             0x0

#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_ADDR                           (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x0000005c)
#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_RMSK                                  0x7
#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_ADDR)
#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_STAT_BMSK                             0x7
#define HWIO_AON_GBLTMR_SLV_INT_RAW_STAT_STAT_SHFT                             0x0

#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_ADDR                        (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000060)
#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_RMSK                               0x7
#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_ADDR)
#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_STAT_BMSK                          0x7
#define HWIO_AON_GBLTMR_SLV_INT_MASKED_STAT_STAT_SHFT                          0x0

#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_ADDR                       (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000074)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_RMSK                            0xf0f
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_ADDR)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_OUT(v)      \
        out_dword(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_ADDR,v)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_ADDR,m,v,HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_IN)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_BMSK               0xf00
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_SHFT                 0x8
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_BMSK                 0xf
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_SHFT                 0x0

#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_ADDR                         (AON_GBLTMR_SLV_HZ_GL_TMR_SLV_REG_BASE      + 0x00000078)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_RMSK                         0xffffffff
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_IN          \
        in_dword(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_ADDR)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_INM(m)      \
        in_dword_masked(HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_ADDR, m)
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_TMX_DBG_OUT_BMSK             0xffffffff
#define HWIO_AON_GBLTMR_SLV_DBG_OUT_BUS_RB_TMX_DBG_OUT_SHFT                    0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_CTMR_HZ_CE_TMR
 *--------------------------------------------------------------------------*/

#define AON_CTMR_HZ_CE_TMR_REG_BASE                                      (AON_CTMR_HZ_CE_TMR_BASE      + 0x00000000)
#define AON_CTMR_HZ_CE_TMR_REG_BASE_SIZE                                 0x1000
#define AON_CTMR_HZ_CE_TMR_REG_BASE_USED                                 0x400

#define HWIO_AON_CTMR_MAIN_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000000)
#define HWIO_AON_CTMR_MAIN_CTRL_RMSK                                         0x1111
#define HWIO_AON_CTMR_MAIN_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_MAIN_CTRL_ADDR)
#define HWIO_AON_CTMR_MAIN_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_MAIN_CTRL_ADDR, m)
#define HWIO_AON_CTMR_MAIN_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_MAIN_CTRL_ADDR,v)
#define HWIO_AON_CTMR_MAIN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_MAIN_CTRL_ADDR,m,v,HWIO_AON_CTMR_MAIN_CTRL_IN)
#define HWIO_AON_CTMR_MAIN_CTRL_EXT_WBTMR_IF_EN_BMSK                         0x1000
#define HWIO_AON_CTMR_MAIN_CTRL_EXT_WBTMR_IF_EN_SHFT                            0xc
#define HWIO_AON_CTMR_MAIN_CTRL_EXT_IF_SYNC_EN_BMSK                           0x100
#define HWIO_AON_CTMR_MAIN_CTRL_EXT_IF_SYNC_EN_SHFT                             0x8
#define HWIO_AON_CTMR_MAIN_CTRL_BTC_CLKN_EN_BMSK                               0x10
#define HWIO_AON_CTMR_MAIN_CTRL_BTC_CLKN_EN_SHFT                                0x4
#define HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_BMSK                               0x1
#define HWIO_AON_CTMR_MAIN_CTRL_CETMR_BLK_EN_SHFT                               0x0

#define HWIO_AON_CTMR_TMR_UPDATE_ADDR                                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000010)
#define HWIO_AON_CTMR_TMR_UPDATE_RMSK                                         0x10f
#define HWIO_AON_CTMR_TMR_UPDATE_IN          \
        in_dword(HWIO_AON_CTMR_TMR_UPDATE_ADDR)
#define HWIO_AON_CTMR_TMR_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_TMR_UPDATE_ADDR, m)
#define HWIO_AON_CTMR_TMR_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_TMR_UPDATE_ADDR,v)
#define HWIO_AON_CTMR_TMR_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_TMR_UPDATE_ADDR,m,v,HWIO_AON_CTMR_TMR_UPDATE_IN)
#define HWIO_AON_CTMR_TMR_UPDATE_MODE_BMSK                                    0x100
#define HWIO_AON_CTMR_TMR_UPDATE_MODE_SHFT                                      0x8
#define HWIO_AON_CTMR_TMR_UPDATE_FRAC_TIME_BMSK                                 0xf
#define HWIO_AON_CTMR_TMR_UPDATE_FRAC_TIME_SHFT                                 0x0

#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_ADDR                           (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000014)
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_RMSK                           0xffffffff
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_ADDR,v)
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_ADDR,m,v,HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_IN)
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_USEC_TIME_BMSK                 0xffffffff
#define HWIO_AON_CTMR_TMR_UPDATE_USEC_VAL_USEC_TIME_SHFT                        0x0

#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_ADDR                             (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000020)
#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_RMSK                             0xffffffff
#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_TIME_BMSK                        0xffffffff
#define HWIO_AON_CTMR_LIVE_TMR_FRAC_VAL_TIME_SHFT                               0x0

#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_ADDR                             (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000024)
#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_RMSK                             0xffffffff
#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_TIME_BMSK                        0xffffffff
#define HWIO_AON_CTMR_LIVE_TMR_USEC_VAL_TIME_SHFT                               0x0

#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_ADDR                             (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000028)
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_RMSK                             0xffffffff
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_IN          \
        in_dword(HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_ADDR)
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_ADDR, m)
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_FRAC_MSB_BMSK                    0xf0000000
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_FRAC_MSB_SHFT                          0x1c
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_INTG_BMSK                         0xfffffff
#define HWIO_AON_CTMR_LIVE_BTC_CLKN_VAL_INTG_SHFT                               0x0

#define HWIO_AON_CTMR_SWCAPT0_CFG_ADDR                                   (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000030)
#define HWIO_AON_CTMR_SWCAPT0_CFG_RMSK                                   0xf7ff0f11
#define HWIO_AON_CTMR_SWCAPT0_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT0_CFG_ADDR)
#define HWIO_AON_CTMR_SWCAPT0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT0_CFG_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT0_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SWCAPT0_CFG_ADDR,v)
#define HWIO_AON_CTMR_SWCAPT0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SWCAPT0_CFG_ADDR,m,v,HWIO_AON_CTMR_SWCAPT0_CFG_IN)
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ3_BMSK             0x80000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ3_SHFT                   0x1f
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ2_BMSK             0x40000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ2_SHFT                   0x1e
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ1_BMSK             0x20000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ1_SHFT                   0x1d
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ0_BMSK             0x10000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_EXTINT_SWIRQ0_SHFT                   0x1c
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ2_BMSK                 0x4000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ2_SHFT                      0x1a
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ1_BMSK                 0x2000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ1_SHFT                      0x19
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ0_BMSK                 0x1000000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_INT_SWIRQ0_SHFT                      0x18
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR7_BMSK                 0x800000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR7_SHFT                     0x17
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR6_BMSK                 0x400000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR6_SHFT                     0x16
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR5_BMSK                 0x200000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR5_SHFT                     0x15
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR4_BMSK                 0x100000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR4_SHFT                     0x14
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR3_BMSK                  0x80000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR3_SHFT                     0x13
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR2_BMSK                  0x40000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR2_SHFT                     0x12
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR1_BMSK                  0x20000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR1_SHFT                     0x11
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR0_BMSK                  0x10000
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_SMALL_CMPR0_SHFT                     0x10
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR3_BMSK                      0x800
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR3_SHFT                        0xb
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR2_BMSK                      0x400
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR2_SHFT                        0xa
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR1_BMSK                      0x200
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR1_SHFT                        0x9
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR0_BMSK                      0x100
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_BIG_CMPR0_SHFT                        0x8
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_TMR_UPDATE_BMSK                      0x10
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_EN_TMR_UPDATE_SHFT                       0x4
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_HOLD_EN_BMSK                             0x1
#define HWIO_AON_CTMR_SWCAPT0_CFG_CAPT_HOLD_EN_SHFT                             0x0

#define HWIO_AON_CTMR_SWCAPT0_CAPT_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000034)
#define HWIO_AON_CTMR_SWCAPT0_CAPT_RMSK                                         0x1
#define HWIO_AON_CTMR_SWCAPT0_CAPT_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT0_CAPT_ADDR)
#define HWIO_AON_CTMR_SWCAPT0_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT0_CAPT_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT0_CAPT_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SWCAPT0_CAPT_ADDR,v)
#define HWIO_AON_CTMR_SWCAPT0_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SWCAPT0_CAPT_ADDR,m,v,HWIO_AON_CTMR_SWCAPT0_CAPT_IN)
#define HWIO_AON_CTMR_SWCAPT0_CAPT_MODE_BMSK                                    0x1
#define HWIO_AON_CTMR_SWCAPT0_CAPT_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_ADDR                          (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000038)
#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_RMSK                                 0xf
#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_TIME_BMSK                            0xf
#define HWIO_AON_CTMR_SWCAPT0_TMR_FRAC_VAL_TIME_SHFT                            0x0

#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_ADDR                          (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000003c)
#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_RMSK                          0xffffffff
#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_TIME_BMSK                     0xffffffff
#define HWIO_AON_CTMR_SWCAPT0_TMR_USEC_VAL_TIME_SHFT                            0x0

#define HWIO_AON_CTMR_SWCAPT0_STAT_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000040)
#define HWIO_AON_CTMR_SWCAPT0_STAT_RMSK                                        0x1f
#define HWIO_AON_CTMR_SWCAPT0_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT0_STAT_ADDR)
#define HWIO_AON_CTMR_SWCAPT0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT0_STAT_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT0_STAT_STAT_BMSK                                   0x1f
#define HWIO_AON_CTMR_SWCAPT0_STAT_STAT_SHFT                                    0x0

#define HWIO_AON_CTMR_SWCAPT1_CFG_ADDR                                   (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000050)
#define HWIO_AON_CTMR_SWCAPT1_CFG_RMSK                                   0xf7ff0f11
#define HWIO_AON_CTMR_SWCAPT1_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT1_CFG_ADDR)
#define HWIO_AON_CTMR_SWCAPT1_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT1_CFG_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT1_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SWCAPT1_CFG_ADDR,v)
#define HWIO_AON_CTMR_SWCAPT1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SWCAPT1_CFG_ADDR,m,v,HWIO_AON_CTMR_SWCAPT1_CFG_IN)
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ3_BMSK             0x80000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ3_SHFT                   0x1f
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ2_BMSK             0x40000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ2_SHFT                   0x1e
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ1_BMSK             0x20000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ1_SHFT                   0x1d
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ0_BMSK             0x10000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_EXTINT_SWIRQ0_SHFT                   0x1c
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ2_BMSK                 0x4000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ2_SHFT                      0x1a
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ1_BMSK                 0x2000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ1_SHFT                      0x19
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ0_BMSK                 0x1000000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_INT_SWIRQ0_SHFT                      0x18
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR7_BMSK                 0x800000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR7_SHFT                     0x17
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR6_BMSK                 0x400000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR6_SHFT                     0x16
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR5_BMSK                 0x200000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR5_SHFT                     0x15
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR4_BMSK                 0x100000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR4_SHFT                     0x14
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR3_BMSK                  0x80000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR3_SHFT                     0x13
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR2_BMSK                  0x40000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR2_SHFT                     0x12
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR1_BMSK                  0x20000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR1_SHFT                     0x11
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR0_BMSK                  0x10000
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_SMALL_CMPR0_SHFT                     0x10
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR3_BMSK                      0x800
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR3_SHFT                        0xb
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR2_BMSK                      0x400
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR2_SHFT                        0xa
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR1_BMSK                      0x200
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR1_SHFT                        0x9
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR0_BMSK                      0x100
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_BIG_CMPR0_SHFT                        0x8
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_TMR_UPDATE_BMSK                      0x10
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_EN_TMR_UPDATE_SHFT                       0x4
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_HOLD_EN_BMSK                             0x1
#define HWIO_AON_CTMR_SWCAPT1_CFG_CAPT_HOLD_EN_SHFT                             0x0

#define HWIO_AON_CTMR_SWCAPT1_CAPT_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000054)
#define HWIO_AON_CTMR_SWCAPT1_CAPT_RMSK                                         0x1
#define HWIO_AON_CTMR_SWCAPT1_CAPT_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT1_CAPT_ADDR)
#define HWIO_AON_CTMR_SWCAPT1_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT1_CAPT_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT1_CAPT_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SWCAPT1_CAPT_ADDR,v)
#define HWIO_AON_CTMR_SWCAPT1_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SWCAPT1_CAPT_ADDR,m,v,HWIO_AON_CTMR_SWCAPT1_CAPT_IN)
#define HWIO_AON_CTMR_SWCAPT1_CAPT_MODE_BMSK                                    0x1
#define HWIO_AON_CTMR_SWCAPT1_CAPT_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_ADDR                          (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000058)
#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_RMSK                                 0xf
#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_TIME_BMSK                            0xf
#define HWIO_AON_CTMR_SWCAPT1_TMR_FRAC_VAL_TIME_SHFT                            0x0

#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_ADDR                          (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000005c)
#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_RMSK                          0xffffffff
#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_TIME_BMSK                     0xffffffff
#define HWIO_AON_CTMR_SWCAPT1_TMR_USEC_VAL_TIME_SHFT                            0x0

#define HWIO_AON_CTMR_SWCAPT1_STAT_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000060)
#define HWIO_AON_CTMR_SWCAPT1_STAT_RMSK                                        0x1f
#define HWIO_AON_CTMR_SWCAPT1_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SWCAPT1_STAT_ADDR)
#define HWIO_AON_CTMR_SWCAPT1_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SWCAPT1_STAT_ADDR, m)
#define HWIO_AON_CTMR_SWCAPT1_STAT_STAT_BMSK                                   0x1f
#define HWIO_AON_CTMR_SWCAPT1_STAT_STAT_SHFT                                    0x0

#define HWIO_AON_CTMR_EXTCAPT0_CFG_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000070)
#define HWIO_AON_CTMR_EXTCAPT0_CFG_RMSK                                       0x311
#define HWIO_AON_CTMR_EXTCAPT0_CFG_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_CFG_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_CFG_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTCAPT0_CFG_ADDR,v)
#define HWIO_AON_CTMR_EXTCAPT0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTCAPT0_CFG_ADDR,m,v,HWIO_AON_CTMR_EXTCAPT0_CFG_IN)
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_GP_SYNC1_BMSK                      0x200
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_GP_SYNC1_SHFT                        0x9
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_GP_SYNC0_BMSK                      0x100
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_GP_SYNC0_SHFT                        0x8
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_TMR_SYNC_BMSK                       0x10
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_EN_TMR_SYNC_SHFT                        0x4
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_HOLD_EN_BMSK                            0x1
#define HWIO_AON_CTMR_EXTCAPT0_CFG_CAPT_HOLD_EN_SHFT                            0x0

#define HWIO_AON_CTMR_EXTCAPT0_CAPT_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000074)
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_RMSK                                        0x1
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_CAPT_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_CAPT_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTCAPT0_CAPT_ADDR,v)
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTCAPT0_CAPT_ADDR,m,v,HWIO_AON_CTMR_EXTCAPT0_CAPT_IN)
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_MODE_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTCAPT0_CAPT_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000078)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_RMSK                                0xf
#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_TIME_BMSK                           0xf
#define HWIO_AON_CTMR_EXTCAPT0_TMR_FRAC_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000007c)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_RMSK                         0xffffffff
#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_TIME_BMSK                    0xffffffff
#define HWIO_AON_CTMR_EXTCAPT0_TMR_USEC_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_ADDR                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000080)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_RMSK                        0x1fff
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_TIME_BMSK                   0x1fff
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_FRAC_VAL_TIME_SHFT                      0x0

#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_ADDR                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000084)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_RMSK                     0xfffffff
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_TIME_BMSK                0xfffffff
#define HWIO_AON_CTMR_EXTCAPT0_BTC_CLKN_INTG_VAL_TIME_SHFT                      0x0

#define HWIO_AON_CTMR_EXTCAPT0_STAT_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000088)
#define HWIO_AON_CTMR_EXTCAPT0_STAT_RMSK                                        0x7
#define HWIO_AON_CTMR_EXTCAPT0_STAT_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT0_STAT_ADDR)
#define HWIO_AON_CTMR_EXTCAPT0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT0_STAT_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT0_STAT_STAT_BMSK                                   0x7
#define HWIO_AON_CTMR_EXTCAPT0_STAT_STAT_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTCAPT1_CFG_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000090)
#define HWIO_AON_CTMR_EXTCAPT1_CFG_RMSK                                       0x311
#define HWIO_AON_CTMR_EXTCAPT1_CFG_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_CFG_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_CFG_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTCAPT1_CFG_ADDR,v)
#define HWIO_AON_CTMR_EXTCAPT1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTCAPT1_CFG_ADDR,m,v,HWIO_AON_CTMR_EXTCAPT1_CFG_IN)
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_GP_SYNC1_BMSK                      0x200
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_GP_SYNC1_SHFT                        0x9
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_GP_SYNC0_BMSK                      0x100
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_GP_SYNC0_SHFT                        0x8
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_TMR_SYNC_BMSK                       0x10
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_EN_TMR_SYNC_SHFT                        0x4
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_HOLD_EN_BMSK                            0x1
#define HWIO_AON_CTMR_EXTCAPT1_CFG_CAPT_HOLD_EN_SHFT                            0x0

#define HWIO_AON_CTMR_EXTCAPT1_CAPT_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000094)
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_RMSK                                        0x1
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_CAPT_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_CAPT_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTCAPT1_CAPT_ADDR,v)
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTCAPT1_CAPT_ADDR,m,v,HWIO_AON_CTMR_EXTCAPT1_CAPT_IN)
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_MODE_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTCAPT1_CAPT_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000098)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_RMSK                                0xf
#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_TIME_BMSK                           0xf
#define HWIO_AON_CTMR_EXTCAPT1_TMR_FRAC_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000009c)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_RMSK                         0xffffffff
#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_TIME_BMSK                    0xffffffff
#define HWIO_AON_CTMR_EXTCAPT1_TMR_USEC_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_ADDR                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000000a0)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_RMSK                        0x1fff
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_TIME_BMSK                   0x1fff
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_FRAC_VAL_TIME_SHFT                      0x0

#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_ADDR                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000000a4)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_RMSK                     0xfffffff
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_TIME_BMSK                0xfffffff
#define HWIO_AON_CTMR_EXTCAPT1_BTC_CLKN_INTG_VAL_TIME_SHFT                      0x0

#define HWIO_AON_CTMR_EXTCAPT1_STAT_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000000a8)
#define HWIO_AON_CTMR_EXTCAPT1_STAT_RMSK                                        0x7
#define HWIO_AON_CTMR_EXTCAPT1_STAT_IN          \
        in_dword(HWIO_AON_CTMR_EXTCAPT1_STAT_ADDR)
#define HWIO_AON_CTMR_EXTCAPT1_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTCAPT1_STAT_ADDR, m)
#define HWIO_AON_CTMR_EXTCAPT1_STAT_STAT_BMSK                                   0x7
#define HWIO_AON_CTMR_EXTCAPT1_STAT_STAT_SHFT                                   0x0

#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_ADDR                          (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000000f0)
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_RMSK                          0xffffffff
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_IN          \
        in_dword(HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_ADDR)
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_ADDR, m)
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_STAT_BMSK                     0xf0000000
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_STAT_SHFT                           0x1c
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_CMPR_VAL_BMSK                  0xfffffff
#define HWIO_AON_CTMR_CLOSEST_IN_TIME_STAT_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_BIG_CMPR0_STAT_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000100)
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_RMSK                                0xffffffff
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR0_STAT_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR0_STAT_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_LATE_DET_BMSK                       0x80000000
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_LATE_DET_SHFT                             0x1f
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_STAT_BMSK                           0x70000000
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_STAT_SHFT                                 0x1c
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_CUR_CMPR_VAL_BMSK                    0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR0_STAT_CUR_CMPR_VAL_SHFT                          0x0

#define HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000104)
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_RMSK                                        0x3
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR0_CFG_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR0_CFG_IN)
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_MODE_BMSK                                   0x3
#define HWIO_AON_CTMR_BIG_CMPR0_CFG_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR                            (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000108)
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_RMSK                             0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_IN)
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_TIME_BMSK                        0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR0_INCR_VAL_TIME_SHFT                              0x0

#define HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000010c)
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_RMSK                                  0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR0_CMD_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR0_CMD_IN)
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_CMPR_VAL_BMSK                         0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR0_CMD_CMPR_VAL_SHFT                               0x0

#define HWIO_AON_CTMR_BIG_CMPR1_STAT_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000110)
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_RMSK                                0xffffffff
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR1_STAT_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR1_STAT_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_LATE_DET_BMSK                       0x80000000
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_LATE_DET_SHFT                             0x1f
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_STAT_BMSK                           0x70000000
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_STAT_SHFT                                 0x1c
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_CUR_CMPR_VAL_BMSK                    0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR1_STAT_CUR_CMPR_VAL_SHFT                          0x0

#define HWIO_AON_CTMR_BIG_CMPR1_CFG_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000114)
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_RMSK                                        0x3
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR1_CFG_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR1_CFG_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR1_CFG_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR1_CFG_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR1_CFG_IN)
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_MODE_BMSK                                   0x3
#define HWIO_AON_CTMR_BIG_CMPR1_CFG_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_ADDR                            (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000118)
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_RMSK                             0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_IN)
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_TIME_BMSK                        0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR1_INCR_VAL_TIME_SHFT                              0x0

#define HWIO_AON_CTMR_BIG_CMPR1_CMD_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000011c)
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_RMSK                                  0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR1_CMD_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR1_CMD_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR1_CMD_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR1_CMD_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR1_CMD_IN)
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_CMPR_VAL_BMSK                         0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR1_CMD_CMPR_VAL_SHFT                               0x0

#define HWIO_AON_CTMR_BIG_CMPR2_STAT_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000120)
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_RMSK                                0xffffffff
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR2_STAT_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR2_STAT_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_LATE_DET_BMSK                       0x80000000
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_LATE_DET_SHFT                             0x1f
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_STAT_BMSK                           0x70000000
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_STAT_SHFT                                 0x1c
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_CUR_CMPR_VAL_BMSK                    0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR2_STAT_CUR_CMPR_VAL_SHFT                          0x0

#define HWIO_AON_CTMR_BIG_CMPR2_CFG_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000124)
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_RMSK                                        0x3
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR2_CFG_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR2_CFG_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR2_CFG_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR2_CFG_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR2_CFG_IN)
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_MODE_BMSK                                   0x3
#define HWIO_AON_CTMR_BIG_CMPR2_CFG_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_ADDR                            (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000128)
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_RMSK                             0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_IN)
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_TIME_BMSK                        0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR2_INCR_VAL_TIME_SHFT                              0x0

#define HWIO_AON_CTMR_BIG_CMPR2_CMD_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000012c)
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_RMSK                                  0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR2_CMD_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR2_CMD_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR2_CMD_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR2_CMD_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR2_CMD_IN)
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_CMPR_VAL_BMSK                         0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR2_CMD_CMPR_VAL_SHFT                               0x0

#define HWIO_AON_CTMR_BIG_CMPR3_STAT_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000130)
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_RMSK                                0xffffffff
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR3_STAT_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR3_STAT_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_LATE_DET_BMSK                       0x80000000
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_LATE_DET_SHFT                             0x1f
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_STAT_BMSK                           0x70000000
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_STAT_SHFT                                 0x1c
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_CUR_CMPR_VAL_BMSK                    0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR3_STAT_CUR_CMPR_VAL_SHFT                          0x0

#define HWIO_AON_CTMR_BIG_CMPR3_CFG_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000134)
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_RMSK                                        0x3
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR3_CFG_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR3_CFG_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR3_CFG_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR3_CFG_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR3_CFG_IN)
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_MODE_BMSK                                   0x3
#define HWIO_AON_CTMR_BIG_CMPR3_CFG_MODE_SHFT                                   0x0

#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_ADDR                            (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000138)
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_RMSK                             0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_IN)
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_TIME_BMSK                        0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR3_INCR_VAL_TIME_SHFT                              0x0

#define HWIO_AON_CTMR_BIG_CMPR3_CMD_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000013c)
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_RMSK                                  0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_IN          \
        in_dword(HWIO_AON_CTMR_BIG_CMPR3_CMD_ADDR)
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BIG_CMPR3_CMD_ADDR, m)
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BIG_CMPR3_CMD_ADDR,v)
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BIG_CMPR3_CMD_ADDR,m,v,HWIO_AON_CTMR_BIG_CMPR3_CMD_IN)
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_CMPR_VAL_BMSK                         0xfffffff
#define HWIO_AON_CTMR_BIG_CMPR3_CMD_CMPR_VAL_SHFT                               0x0

#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000180)
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR0_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR0_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR0_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000184)
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR0_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR0_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR0_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000188)
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR0_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR0_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR0_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000190)
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR1_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR1_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR1_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000194)
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR1_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR1_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR1_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR1_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR1_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR1_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000198)
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR1_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR1_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR1_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR1_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR1_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR1_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001a0)
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR2_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR2_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR2_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001a4)
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR2_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR2_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR2_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR2_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR2_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR2_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001a8)
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR2_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR2_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR2_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR2_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR2_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR2_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001b0)
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR3_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR3_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR3_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001b4)
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR3_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR3_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR3_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR3_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR3_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR3_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001b8)
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR3_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR3_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR3_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR3_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR3_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR3_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001c0)
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR4_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR4_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR4_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001c4)
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR4_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR4_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR4_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR4_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR4_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR4_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001c8)
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR4_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR4_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR4_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR4_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR4_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR4_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001d0)
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR5_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR5_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR5_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001d4)
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR5_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR5_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR5_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR5_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR5_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR5_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001d8)
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR5_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR5_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR5_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR5_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR5_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR5_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001e0)
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR6_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR6_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR6_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001e4)
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR6_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR6_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR6_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR6_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR6_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR6_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001e8)
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR6_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR6_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR6_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR6_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR6_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR6_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001f0)
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_RMSK                              0xf01fffff
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR7_STAT_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR7_STAT_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_LATE_DET_BMSK                     0x80000000
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_LATE_DET_SHFT                           0x1f
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_STAT_BMSK                         0x70000000
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_STAT_SHFT                               0x1c
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_CUR_CMPR_VAL_BMSK                   0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR7_STAT_CUR_CMPR_VAL_SHFT                        0x0

#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001f4)
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_RMSK                                      0x1
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR7_CFG_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR7_CFG_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR7_CFG_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR7_CFG_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR7_CFG_IN)
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_MODE_BMSK                                 0x1
#define HWIO_AON_CTMR_SMALL_CMPR7_CFG_MODE_SHFT                                 0x0

#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_ADDR                               (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000001f8)
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_RMSK                                 0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_IN          \
        in_dword(HWIO_AON_CTMR_SMALL_CMPR7_CMD_ADDR)
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SMALL_CMPR7_CMD_ADDR, m)
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SMALL_CMPR7_CMD_ADDR,v)
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SMALL_CMPR7_CMD_ADDR,m,v,HWIO_AON_CTMR_SMALL_CMPR7_CMD_IN)
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_CMPR_VAL_BMSK                        0x1fffff
#define HWIO_AON_CTMR_SMALL_CMPR7_CMD_CMPR_VAL_SHFT                             0x0

#define HWIO_AON_CTMR_INT_SWIRQ0_ADDR                                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000200)
#define HWIO_AON_CTMR_INT_SWIRQ0_RMSK                                           0x1
#define HWIO_AON_CTMR_INT_SWIRQ0_IN          \
        in_dword(HWIO_AON_CTMR_INT_SWIRQ0_ADDR)
#define HWIO_AON_CTMR_INT_SWIRQ0_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_SWIRQ0_ADDR, m)
#define HWIO_AON_CTMR_INT_SWIRQ0_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_SWIRQ0_ADDR,v)
#define HWIO_AON_CTMR_INT_SWIRQ0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_SWIRQ0_ADDR,m,v,HWIO_AON_CTMR_INT_SWIRQ0_IN)
#define HWIO_AON_CTMR_INT_SWIRQ0_TRIG_BMSK                                      0x1
#define HWIO_AON_CTMR_INT_SWIRQ0_TRIG_SHFT                                      0x0

#define HWIO_AON_CTMR_INT_SWIRQ1_ADDR                                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000204)
#define HWIO_AON_CTMR_INT_SWIRQ1_RMSK                                           0x1
#define HWIO_AON_CTMR_INT_SWIRQ1_IN          \
        in_dword(HWIO_AON_CTMR_INT_SWIRQ1_ADDR)
#define HWIO_AON_CTMR_INT_SWIRQ1_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_SWIRQ1_ADDR, m)
#define HWIO_AON_CTMR_INT_SWIRQ1_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_SWIRQ1_ADDR,v)
#define HWIO_AON_CTMR_INT_SWIRQ1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_SWIRQ1_ADDR,m,v,HWIO_AON_CTMR_INT_SWIRQ1_IN)
#define HWIO_AON_CTMR_INT_SWIRQ1_TRIG_BMSK                                      0x1
#define HWIO_AON_CTMR_INT_SWIRQ1_TRIG_SHFT                                      0x0

#define HWIO_AON_CTMR_INT_SWIRQ2_ADDR                                    (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000208)
#define HWIO_AON_CTMR_INT_SWIRQ2_RMSK                                           0x1
#define HWIO_AON_CTMR_INT_SWIRQ2_IN          \
        in_dword(HWIO_AON_CTMR_INT_SWIRQ2_ADDR)
#define HWIO_AON_CTMR_INT_SWIRQ2_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_SWIRQ2_ADDR, m)
#define HWIO_AON_CTMR_INT_SWIRQ2_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_SWIRQ2_ADDR,v)
#define HWIO_AON_CTMR_INT_SWIRQ2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_SWIRQ2_ADDR,m,v,HWIO_AON_CTMR_INT_SWIRQ2_IN)
#define HWIO_AON_CTMR_INT_SWIRQ2_TRIG_BMSK                                      0x1
#define HWIO_AON_CTMR_INT_SWIRQ2_TRIG_SHFT                                      0x0

#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_ADDR                        (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000220)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_RMSK                            0xffff
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_ADDR)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_IN)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR3_BMSK                      0xf000
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR3_SHFT                         0xc
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR2_BMSK                       0xf00
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR2_SHFT                         0x8
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR1_BMSK                        0xf0
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR1_SHFT                         0x4
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR0_BMSK                         0xf
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_FIRED_CMPR0_SHFT                         0x0

#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000224)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_RMSK                             0xffff
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_ADDR)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_IN)
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR3_BMSK                       0xf000
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR3_SHFT                          0xc
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR2_BMSK                        0xf00
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR2_SHFT                          0x8
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR1_BMSK                         0xf0
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR1_SHFT                          0x4
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR0_BMSK                          0xf
#define HWIO_AON_CTMR_INT_MAP_BIG_CMPR_LATE_CMPR0_SHFT                          0x0

#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_ADDR                      (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000228)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_RMSK                      0xffffffff
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_ADDR)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_IN)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR7_BMSK                0xf0000000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR7_SHFT                      0x1c
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR6_BMSK                 0xf000000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR6_SHFT                      0x18
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR5_BMSK                  0xf00000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR5_SHFT                      0x14
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR4_BMSK                   0xf0000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR4_SHFT                      0x10
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR3_BMSK                    0xf000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR3_SHFT                       0xc
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR2_BMSK                     0xf00
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR2_SHFT                       0x8
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR1_BMSK                      0xf0
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR1_SHFT                       0x4
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR0_BMSK                       0xf
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_FIRED_CMPR0_SHFT                       0x0

#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_ADDR                       (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000022c)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_RMSK                       0xffffffff
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_ADDR)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_IN)
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR7_BMSK                 0xf0000000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR7_SHFT                       0x1c
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR6_BMSK                  0xf000000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR6_SHFT                       0x18
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR5_BMSK                   0xf00000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR5_SHFT                       0x14
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR4_BMSK                    0xf0000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR4_SHFT                       0x10
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR3_BMSK                     0xf000
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR3_SHFT                        0xc
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR2_BMSK                      0xf00
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR2_SHFT                        0x8
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR1_BMSK                       0xf0
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR1_SHFT                        0x4
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR0_BMSK                        0xf
#define HWIO_AON_CTMR_INT_MAP_SMALL_CMPR_LATE_CMPR0_SHFT                        0x0

#define HWIO_AON_CTMR_INT_MAP_SWIRQ_ADDR                                 (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000230)
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_RMSK                                      0xfff
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_SWIRQ_ADDR)
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_SWIRQ_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_SWIRQ_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_SWIRQ_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_SWIRQ_IN)
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ2_BMSK                               0xf00
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ2_SHFT                                 0x8
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ1_BMSK                                0xf0
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ1_SHFT                                 0x4
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ0_BMSK                                 0xf
#define HWIO_AON_CTMR_INT_MAP_SWIRQ_SWIRQ0_SHFT                                 0x0

#define HWIO_AON_CTMR_INT_MAP_EXTERN_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000234)
#define HWIO_AON_CTMR_INT_MAP_EXTERN_RMSK                                      0xff
#define HWIO_AON_CTMR_INT_MAP_EXTERN_IN          \
        in_dword(HWIO_AON_CTMR_INT_MAP_EXTERN_ADDR)
#define HWIO_AON_CTMR_INT_MAP_EXTERN_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_MAP_EXTERN_ADDR, m)
#define HWIO_AON_CTMR_INT_MAP_EXTERN_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_MAP_EXTERN_ADDR,v)
#define HWIO_AON_CTMR_INT_MAP_EXTERN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_MAP_EXTERN_ADDR,m,v,HWIO_AON_CTMR_INT_MAP_EXTERN_IN)
#define HWIO_AON_CTMR_INT_MAP_EXTERN_GP_SYNC1_BMSK                             0xf0
#define HWIO_AON_CTMR_INT_MAP_EXTERN_GP_SYNC1_SHFT                              0x4
#define HWIO_AON_CTMR_INT_MAP_EXTERN_GP_SYNC0_BMSK                              0xf
#define HWIO_AON_CTMR_INT_MAP_EXTERN_GP_SYNC0_SHFT                              0x0

#define HWIO_AON_CTMR_INT_CLR_ADDR                                       (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000240)
#define HWIO_AON_CTMR_INT_CLR_RMSK                                       0x37ffffff
#define HWIO_AON_CTMR_INT_CLR_IN          \
        in_dword(HWIO_AON_CTMR_INT_CLR_ADDR)
#define HWIO_AON_CTMR_INT_CLR_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_CLR_ADDR, m)
#define HWIO_AON_CTMR_INT_CLR_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT_CLR_ADDR,v)
#define HWIO_AON_CTMR_INT_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT_CLR_ADDR,m,v,HWIO_AON_CTMR_INT_CLR_IN)
#define HWIO_AON_CTMR_INT_CLR_CLR_EXTERN_GP_SYNC_BMSK                    0x30000000
#define HWIO_AON_CTMR_INT_CLR_CLR_EXTERN_GP_SYNC_SHFT                          0x1c
#define HWIO_AON_CTMR_INT_CLR_CLR_SWIRQ_BMSK                              0x7000000
#define HWIO_AON_CTMR_INT_CLR_CLR_SWIRQ_SHFT                                   0x18
#define HWIO_AON_CTMR_INT_CLR_CLR_SMALL_CMPR_LATE_BMSK                     0xff0000
#define HWIO_AON_CTMR_INT_CLR_CLR_SMALL_CMPR_LATE_SHFT                         0x10
#define HWIO_AON_CTMR_INT_CLR_CLR_BIG_CMPR_LATE_BMSK                         0xf000
#define HWIO_AON_CTMR_INT_CLR_CLR_BIG_CMPR_LATE_SHFT                            0xc
#define HWIO_AON_CTMR_INT_CLR_CLR_SMALL_CMPR_FIRED_BMSK                       0xff0
#define HWIO_AON_CTMR_INT_CLR_CLR_SMALL_CMPR_FIRED_SHFT                         0x4
#define HWIO_AON_CTMR_INT_CLR_CLR_BIG_CMPR_FIRED_BMSK                           0xf
#define HWIO_AON_CTMR_INT_CLR_CLR_BIG_CMPR_FIRED_SHFT                           0x0

#define HWIO_AON_CTMR_INT_RAW_STAT_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000244)
#define HWIO_AON_CTMR_INT_RAW_STAT_RMSK                                  0xffffffff
#define HWIO_AON_CTMR_INT_RAW_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT_RAW_STAT_ADDR)
#define HWIO_AON_CTMR_INT_RAW_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT_RAW_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT_RAW_STAT_STAT_BMSK                             0xffffffff
#define HWIO_AON_CTMR_INT_RAW_STAT_STAT_SHFT                                    0x0

#define HWIO_AON_CTMR_INT0_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000250)
#define HWIO_AON_CTMR_INT0_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT0_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT0_CTRL_ADDR)
#define HWIO_AON_CTMR_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT0_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT0_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT0_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT0_CTRL_IN)
#define HWIO_AON_CTMR_INT0_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT0_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT0_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000254)
#define HWIO_AON_CTMR_INT0_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT0_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT0_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT0_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT0_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT0_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT0_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT1_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000260)
#define HWIO_AON_CTMR_INT1_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT1_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT1_CTRL_ADDR)
#define HWIO_AON_CTMR_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT1_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT1_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT1_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT1_CTRL_IN)
#define HWIO_AON_CTMR_INT1_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT1_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT1_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000264)
#define HWIO_AON_CTMR_INT1_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT1_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT1_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT1_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT1_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT1_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT1_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT2_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000270)
#define HWIO_AON_CTMR_INT2_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT2_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT2_CTRL_ADDR)
#define HWIO_AON_CTMR_INT2_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT2_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT2_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT2_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT2_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT2_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT2_CTRL_IN)
#define HWIO_AON_CTMR_INT2_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT2_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT2_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000274)
#define HWIO_AON_CTMR_INT2_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT2_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT2_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT2_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT2_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT2_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT2_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT3_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000280)
#define HWIO_AON_CTMR_INT3_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT3_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT3_CTRL_ADDR)
#define HWIO_AON_CTMR_INT3_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT3_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT3_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT3_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT3_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT3_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT3_CTRL_IN)
#define HWIO_AON_CTMR_INT3_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT3_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT3_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000284)
#define HWIO_AON_CTMR_INT3_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT3_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT3_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT3_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT3_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT3_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT3_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT4_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000290)
#define HWIO_AON_CTMR_INT4_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT4_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT4_CTRL_ADDR)
#define HWIO_AON_CTMR_INT4_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT4_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT4_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT4_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT4_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT4_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT4_CTRL_IN)
#define HWIO_AON_CTMR_INT4_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT4_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT4_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000294)
#define HWIO_AON_CTMR_INT4_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT4_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT4_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT4_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT4_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT4_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT4_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT5_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002a0)
#define HWIO_AON_CTMR_INT5_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT5_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT5_CTRL_ADDR)
#define HWIO_AON_CTMR_INT5_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT5_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT5_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT5_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT5_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT5_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT5_CTRL_IN)
#define HWIO_AON_CTMR_INT5_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT5_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT5_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002a4)
#define HWIO_AON_CTMR_INT5_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT5_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT5_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT5_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT5_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT5_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT5_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT6_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002b0)
#define HWIO_AON_CTMR_INT6_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT6_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT6_CTRL_ADDR)
#define HWIO_AON_CTMR_INT6_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT6_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT6_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT6_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT6_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT6_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT6_CTRL_IN)
#define HWIO_AON_CTMR_INT6_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT6_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT6_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002b4)
#define HWIO_AON_CTMR_INT6_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT6_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT6_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT6_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT6_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT6_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT6_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_INT7_CTRL_ADDR                                     (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002c0)
#define HWIO_AON_CTMR_INT7_CTRL_RMSK                                            0x1
#define HWIO_AON_CTMR_INT7_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_INT7_CTRL_ADDR)
#define HWIO_AON_CTMR_INT7_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT7_CTRL_ADDR, m)
#define HWIO_AON_CTMR_INT7_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_INT7_CTRL_ADDR,v)
#define HWIO_AON_CTMR_INT7_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_INT7_CTRL_ADDR,m,v,HWIO_AON_CTMR_INT7_CTRL_IN)
#define HWIO_AON_CTMR_INT7_CTRL_OUT_EN_BMSK                                     0x1
#define HWIO_AON_CTMR_INT7_CTRL_OUT_EN_SHFT                                     0x0

#define HWIO_AON_CTMR_INT7_MAPPED_STAT_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000002c4)
#define HWIO_AON_CTMR_INT7_MAPPED_STAT_RMSK                              0xffffffff
#define HWIO_AON_CTMR_INT7_MAPPED_STAT_IN          \
        in_dword(HWIO_AON_CTMR_INT7_MAPPED_STAT_ADDR)
#define HWIO_AON_CTMR_INT7_MAPPED_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_INT7_MAPPED_STAT_ADDR, m)
#define HWIO_AON_CTMR_INT7_MAPPED_STAT_STAT_BMSK                         0xffffffff
#define HWIO_AON_CTMR_INT7_MAPPED_STAT_STAT_SHFT                                0x0

#define HWIO_AON_CTMR_EXTINT0_CTRL_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000300)
#define HWIO_AON_CTMR_EXTINT0_CTRL_RMSK                                         0x3
#define HWIO_AON_CTMR_EXTINT0_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT0_CTRL_ADDR)
#define HWIO_AON_CTMR_EXTINT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT0_CTRL_ADDR, m)
#define HWIO_AON_CTMR_EXTINT0_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT0_CTRL_ADDR,v)
#define HWIO_AON_CTMR_EXTINT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT0_CTRL_ADDR,m,v,HWIO_AON_CTMR_EXTINT0_CTRL_IN)
#define HWIO_AON_CTMR_EXTINT0_CTRL_MODE_BMSK                                    0x3
#define HWIO_AON_CTMR_EXTINT0_CTRL_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_EXTINT0_UPDATE_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000304)
#define HWIO_AON_CTMR_EXTINT0_UPDATE_RMSK                                       0x1
#define HWIO_AON_CTMR_EXTINT0_UPDATE_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT0_UPDATE_ADDR)
#define HWIO_AON_CTMR_EXTINT0_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT0_UPDATE_ADDR, m)
#define HWIO_AON_CTMR_EXTINT0_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT0_UPDATE_ADDR,v)
#define HWIO_AON_CTMR_EXTINT0_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT0_UPDATE_ADDR,m,v,HWIO_AON_CTMR_EXTINT0_UPDATE_IN)
#define HWIO_AON_CTMR_EXTINT0_UPDATE_VAL_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTINT0_UPDATE_VAL_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTINT0_UNMASK_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000308)
#define HWIO_AON_CTMR_EXTINT0_UNMASK_RMSK                                     0xfff
#define HWIO_AON_CTMR_EXTINT0_UNMASK_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT0_UNMASK_ADDR)
#define HWIO_AON_CTMR_EXTINT0_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT0_UNMASK_ADDR, m)
#define HWIO_AON_CTMR_EXTINT0_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT0_UNMASK_ADDR,v)
#define HWIO_AON_CTMR_EXTINT0_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT0_UNMASK_ADDR,m,v,HWIO_AON_CTMR_EXTINT0_UNMASK_IN)
#define HWIO_AON_CTMR_EXTINT0_UNMASK_UNMASK_BMSK                              0xfff
#define HWIO_AON_CTMR_EXTINT0_UNMASK_UNMASK_SHFT                                0x0

#define HWIO_AON_CTMR_EXTINT1_CTRL_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000310)
#define HWIO_AON_CTMR_EXTINT1_CTRL_RMSK                                         0x3
#define HWIO_AON_CTMR_EXTINT1_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT1_CTRL_ADDR)
#define HWIO_AON_CTMR_EXTINT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT1_CTRL_ADDR, m)
#define HWIO_AON_CTMR_EXTINT1_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT1_CTRL_ADDR,v)
#define HWIO_AON_CTMR_EXTINT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT1_CTRL_ADDR,m,v,HWIO_AON_CTMR_EXTINT1_CTRL_IN)
#define HWIO_AON_CTMR_EXTINT1_CTRL_MODE_BMSK                                    0x3
#define HWIO_AON_CTMR_EXTINT1_CTRL_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_EXTINT1_UPDATE_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000314)
#define HWIO_AON_CTMR_EXTINT1_UPDATE_RMSK                                       0x1
#define HWIO_AON_CTMR_EXTINT1_UPDATE_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT1_UPDATE_ADDR)
#define HWIO_AON_CTMR_EXTINT1_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT1_UPDATE_ADDR, m)
#define HWIO_AON_CTMR_EXTINT1_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT1_UPDATE_ADDR,v)
#define HWIO_AON_CTMR_EXTINT1_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT1_UPDATE_ADDR,m,v,HWIO_AON_CTMR_EXTINT1_UPDATE_IN)
#define HWIO_AON_CTMR_EXTINT1_UPDATE_VAL_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTINT1_UPDATE_VAL_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTINT1_UNMASK_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000318)
#define HWIO_AON_CTMR_EXTINT1_UNMASK_RMSK                                     0xfff
#define HWIO_AON_CTMR_EXTINT1_UNMASK_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT1_UNMASK_ADDR)
#define HWIO_AON_CTMR_EXTINT1_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT1_UNMASK_ADDR, m)
#define HWIO_AON_CTMR_EXTINT1_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT1_UNMASK_ADDR,v)
#define HWIO_AON_CTMR_EXTINT1_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT1_UNMASK_ADDR,m,v,HWIO_AON_CTMR_EXTINT1_UNMASK_IN)
#define HWIO_AON_CTMR_EXTINT1_UNMASK_UNMASK_BMSK                              0xfff
#define HWIO_AON_CTMR_EXTINT1_UNMASK_UNMASK_SHFT                                0x0

#define HWIO_AON_CTMR_EXTINT2_CTRL_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000320)
#define HWIO_AON_CTMR_EXTINT2_CTRL_RMSK                                         0x3
#define HWIO_AON_CTMR_EXTINT2_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT2_CTRL_ADDR)
#define HWIO_AON_CTMR_EXTINT2_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT2_CTRL_ADDR, m)
#define HWIO_AON_CTMR_EXTINT2_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT2_CTRL_ADDR,v)
#define HWIO_AON_CTMR_EXTINT2_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT2_CTRL_ADDR,m,v,HWIO_AON_CTMR_EXTINT2_CTRL_IN)
#define HWIO_AON_CTMR_EXTINT2_CTRL_MODE_BMSK                                    0x3
#define HWIO_AON_CTMR_EXTINT2_CTRL_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_EXTINT2_UPDATE_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000324)
#define HWIO_AON_CTMR_EXTINT2_UPDATE_RMSK                                       0x1
#define HWIO_AON_CTMR_EXTINT2_UPDATE_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT2_UPDATE_ADDR)
#define HWIO_AON_CTMR_EXTINT2_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT2_UPDATE_ADDR, m)
#define HWIO_AON_CTMR_EXTINT2_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT2_UPDATE_ADDR,v)
#define HWIO_AON_CTMR_EXTINT2_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT2_UPDATE_ADDR,m,v,HWIO_AON_CTMR_EXTINT2_UPDATE_IN)
#define HWIO_AON_CTMR_EXTINT2_UPDATE_VAL_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTINT2_UPDATE_VAL_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTINT2_UNMASK_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000328)
#define HWIO_AON_CTMR_EXTINT2_UNMASK_RMSK                                     0xfff
#define HWIO_AON_CTMR_EXTINT2_UNMASK_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT2_UNMASK_ADDR)
#define HWIO_AON_CTMR_EXTINT2_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT2_UNMASK_ADDR, m)
#define HWIO_AON_CTMR_EXTINT2_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT2_UNMASK_ADDR,v)
#define HWIO_AON_CTMR_EXTINT2_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT2_UNMASK_ADDR,m,v,HWIO_AON_CTMR_EXTINT2_UNMASK_IN)
#define HWIO_AON_CTMR_EXTINT2_UNMASK_UNMASK_BMSK                              0xfff
#define HWIO_AON_CTMR_EXTINT2_UNMASK_UNMASK_SHFT                                0x0

#define HWIO_AON_CTMR_EXTINT3_CTRL_ADDR                                  (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000330)
#define HWIO_AON_CTMR_EXTINT3_CTRL_RMSK                                         0x3
#define HWIO_AON_CTMR_EXTINT3_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT3_CTRL_ADDR)
#define HWIO_AON_CTMR_EXTINT3_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT3_CTRL_ADDR, m)
#define HWIO_AON_CTMR_EXTINT3_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT3_CTRL_ADDR,v)
#define HWIO_AON_CTMR_EXTINT3_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT3_CTRL_ADDR,m,v,HWIO_AON_CTMR_EXTINT3_CTRL_IN)
#define HWIO_AON_CTMR_EXTINT3_CTRL_MODE_BMSK                                    0x3
#define HWIO_AON_CTMR_EXTINT3_CTRL_MODE_SHFT                                    0x0

#define HWIO_AON_CTMR_EXTINT3_UPDATE_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000334)
#define HWIO_AON_CTMR_EXTINT3_UPDATE_RMSK                                       0x1
#define HWIO_AON_CTMR_EXTINT3_UPDATE_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT3_UPDATE_ADDR)
#define HWIO_AON_CTMR_EXTINT3_UPDATE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT3_UPDATE_ADDR, m)
#define HWIO_AON_CTMR_EXTINT3_UPDATE_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT3_UPDATE_ADDR,v)
#define HWIO_AON_CTMR_EXTINT3_UPDATE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT3_UPDATE_ADDR,m,v,HWIO_AON_CTMR_EXTINT3_UPDATE_IN)
#define HWIO_AON_CTMR_EXTINT3_UPDATE_VAL_BMSK                                   0x1
#define HWIO_AON_CTMR_EXTINT3_UPDATE_VAL_SHFT                                   0x0

#define HWIO_AON_CTMR_EXTINT3_UNMASK_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000338)
#define HWIO_AON_CTMR_EXTINT3_UNMASK_RMSK                                     0xfff
#define HWIO_AON_CTMR_EXTINT3_UNMASK_IN          \
        in_dword(HWIO_AON_CTMR_EXTINT3_UNMASK_ADDR)
#define HWIO_AON_CTMR_EXTINT3_UNMASK_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_EXTINT3_UNMASK_ADDR, m)
#define HWIO_AON_CTMR_EXTINT3_UNMASK_OUT(v)      \
        out_dword(HWIO_AON_CTMR_EXTINT3_UNMASK_ADDR,v)
#define HWIO_AON_CTMR_EXTINT3_UNMASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_EXTINT3_UNMASK_ADDR,m,v,HWIO_AON_CTMR_EXTINT3_UNMASK_IN)
#define HWIO_AON_CTMR_EXTINT3_UNMASK_UNMASK_BMSK                              0xfff
#define HWIO_AON_CTMR_EXTINT3_UNMASK_UNMASK_SHFT                                0x0

#define HWIO_AON_CTMR_BTC_ALU_CMD_ADDR                                   (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000380)
#define HWIO_AON_CTMR_BTC_ALU_CMD_RMSK                                    0x377717f
#define HWIO_AON_CTMR_BTC_ALU_CMD_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_CMD_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_CMD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_CMD_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_CMD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BTC_ALU_CMD_ADDR,v)
#define HWIO_AON_CTMR_BTC_ALU_CMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BTC_ALU_CMD_ADDR,m,v,HWIO_AON_CTMR_BTC_ALU_CMD_IN)
#define HWIO_AON_CTMR_BTC_ALU_CMD_CONV_SAT_BMSK                           0x3000000
#define HWIO_AON_CTMR_BTC_ALU_CMD_CONV_SAT_SHFT                                0x18
#define HWIO_AON_CTMR_BTC_ALU_CMD_CONV_OPCODE_BMSK                         0x700000
#define HWIO_AON_CTMR_BTC_ALU_CMD_CONV_OPCODE_SHFT                             0x14
#define HWIO_AON_CTMR_BTC_ALU_CMD_OPCODE_0_BMSK                             0x70000
#define HWIO_AON_CTMR_BTC_ALU_CMD_OPCODE_0_SHFT                                0x10
#define HWIO_AON_CTMR_BTC_ALU_CMD_OPCODE_1_BMSK                              0x7000
#define HWIO_AON_CTMR_BTC_ALU_CMD_OPCODE_1_SHFT                                 0xc
#define HWIO_AON_CTMR_BTC_ALU_CMD_OP_BMSK                                     0x100
#define HWIO_AON_CTMR_BTC_ALU_CMD_OP_SHFT                                       0x8
#define HWIO_AON_CTMR_BTC_ALU_CMD_CAPT_CETMR_BMSK                              0x40
#define HWIO_AON_CTMR_BTC_ALU_CMD_CAPT_CETMR_SHFT                               0x6
#define HWIO_AON_CTMR_BTC_ALU_CMD_LD_RSLT_BMSK                                 0x20
#define HWIO_AON_CTMR_BTC_ALU_CMD_LD_RSLT_SHFT                                  0x5
#define HWIO_AON_CTMR_BTC_ALU_CMD_LD_CLKN_BMSK                                 0x10
#define HWIO_AON_CTMR_BTC_ALU_CMD_LD_CLKN_SHFT                                  0x4
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_27_2_BMSK                              0x8
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_27_2_SHFT                              0x3
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_1_BMSK                                 0x4
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_1_SHFT                                 0x2
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_0_BMSK                                 0x2
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_0_SHFT                                 0x1
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_FRAC_BMSK                              0x1
#define HWIO_AON_CTMR_BTC_ALU_CMD_UPDATE_FRAC_SHFT                              0x0

#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_ADDR                           (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000384)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_RMSK                               0x1fff
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_ADDR,v)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_ADDR,m,v,HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_IN)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_TIME_BMSK                          0x1fff
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_FRAC_TIME_SHFT                             0x0

#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_ADDR                           (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000388)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_RMSK                            0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_ADDR,v)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_ADDR,m,v,HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_IN)
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_TIME_BMSK                       0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_OPER_A_INTG_TIME_SHFT                             0x0

#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_ADDR                           (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000038c)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_RMSK                               0x1fff
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_ADDR,v)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_ADDR,m,v,HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_IN)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_TIME_BMSK                          0x1fff
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_FRAC_TIME_SHFT                             0x0

#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_ADDR                           (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000390)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_RMSK                            0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_OUT(v)      \
        out_dword(HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_ADDR,v)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_ADDR,m,v,HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_IN)
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_TIME_BMSK                       0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_OPER_B_INTG_TIME_SHFT                             0x0

#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000394)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_RMSK                             0x1fff
#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_TIME_BMSK                        0x1fff
#define HWIO_AON_CTMR_BTC_ALU_RSLT_FRAC_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_ADDR                         (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000398)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_RMSK                          0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_TIME_BMSK                     0xfffffff
#define HWIO_AON_CTMR_BTC_ALU_RSLT_INTG_VAL_TIME_SHFT                           0x0

#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_ADDR                        (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x0000039c)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_RMSK                               0xf
#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_TIME_BMSK                          0xf
#define HWIO_AON_CTMR_BTC_ALU_CETMR_FRAC_VAL_TIME_SHFT                          0x0

#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_ADDR                        (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003a0)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_RMSK                        0xffffffff
#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_TIME_BMSK                   0xffffffff
#define HWIO_AON_CTMR_BTC_ALU_CETMR_USEC_VAL_TIME_SHFT                          0x0

#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_ADDR                            (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003a4)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_RMSK                                   0x1
#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_IN          \
        in_dword(HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_ADDR)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_ADDR, m)
#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_CONV_SAT_BMSK                          0x1
#define HWIO_AON_CTMR_BTC_ALU_CETMR_STAT_CONV_SAT_SHFT                          0x0

#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003e0)
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_RMSK                              0x55111011
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_IN          \
        in_dword(HWIO_AON_CTMR_DBG_CLK_RST_OVRD_ADDR)
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_DBG_CLK_RST_OVRD_ADDR, m)
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_OUT(v)      \
        out_dword(HWIO_AON_CTMR_DBG_CLK_RST_OVRD_ADDR,v)
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_DBG_CLK_RST_OVRD_ADDR,m,v,HWIO_AON_CTMR_DBG_CLK_RST_OVRD_IN)
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_WBTMR_BMSK               0x40000000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_WBTMR_SHFT                     0x1e
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_BTC_ALU_BMSK             0x10000000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_BTC_ALU_SHFT                   0x1c
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_EXT_INT_BMSK              0x4000000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_EXT_INT_SHFT                   0x1a
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_INT_BMSK            0x1000000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_INT_SHFT                 0x18
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CAPT_BMSK            0x100000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CAPT_SHFT                0x14
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CMPR_BMSK             0x10000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CMPR_SHFT                0x10
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CNTR_BMSK              0x1000
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_FORCECLK_CETMR_CNTR_SHFT                 0xc
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_SOFTRST_CETMR_SYS_BMSK                  0x10
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_SOFTRST_CETMR_SYS_SHFT                   0x4
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_SOFTRST_CETMR_CNTR_BMSK                  0x1
#define HWIO_AON_CTMR_DBG_CLK_RST_OVRD_SOFTRST_CETMR_CNTR_SHFT                  0x0

#define HWIO_AON_CTMR_DBG_FSM_CLR_ADDR                                   (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003e4)
#define HWIO_AON_CTMR_DBG_FSM_CLR_RMSK                                         0x11
#define HWIO_AON_CTMR_DBG_FSM_CLR_IN          \
        in_dword(HWIO_AON_CTMR_DBG_FSM_CLR_ADDR)
#define HWIO_AON_CTMR_DBG_FSM_CLR_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_DBG_FSM_CLR_ADDR, m)
#define HWIO_AON_CTMR_DBG_FSM_CLR_OUT(v)      \
        out_dword(HWIO_AON_CTMR_DBG_FSM_CLR_ADDR,v)
#define HWIO_AON_CTMR_DBG_FSM_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_DBG_FSM_CLR_ADDR,m,v,HWIO_AON_CTMR_DBG_FSM_CLR_IN)
#define HWIO_AON_CTMR_DBG_FSM_CLR_CLR_FSM_WBTMR_BMSK                           0x10
#define HWIO_AON_CTMR_DBG_FSM_CLR_CLR_FSM_WBTMR_SHFT                            0x4
#define HWIO_AON_CTMR_DBG_FSM_CLR_CLR_FSM_CETMR_CIT_BMSK                        0x1
#define HWIO_AON_CTMR_DBG_FSM_CLR_CLR_FSM_CETMR_CIT_SHFT                        0x0

#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003f0)
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_RMSK                                  0x1f1f
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_IN          \
        in_dword(HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_ADDR)
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_ADDR, m)
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_OUT(v)      \
        out_dword(HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_ADDR,v)
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_ADDR,m,v,HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_IN)
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_BMSK                     0x1f00
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_TMX_OUT1_SEL_SHFT                        0x8
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_BMSK                       0x1f
#define HWIO_AON_CTMR_DBG_OUT_BUS_CTRL_TMX_OUT0_SEL_SHFT                        0x0

#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_ADDR                                (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003f4)
#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_RMSK                                0xffffffff
#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_IN          \
        in_dword(HWIO_AON_CTMR_DBG_OUT_BUS_RB_ADDR)
#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_DBG_OUT_BUS_RB_ADDR, m)
#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_TMX_DBG_OUT_BMSK                    0xffffffff
#define HWIO_AON_CTMR_DBG_OUT_BUS_RB_TMX_DBG_OUT_SHFT                           0x0

#define HWIO_AON_CTMR_SPARE_0_ADDR                                       (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003f8)
#define HWIO_AON_CTMR_SPARE_0_RMSK                                             0xff
#define HWIO_AON_CTMR_SPARE_0_IN          \
        in_dword(HWIO_AON_CTMR_SPARE_0_ADDR)
#define HWIO_AON_CTMR_SPARE_0_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SPARE_0_ADDR, m)
#define HWIO_AON_CTMR_SPARE_0_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SPARE_0_ADDR,v)
#define HWIO_AON_CTMR_SPARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SPARE_0_ADDR,m,v,HWIO_AON_CTMR_SPARE_0_IN)
#define HWIO_AON_CTMR_SPARE_0_SPARE_REG_BMSK                                   0xff
#define HWIO_AON_CTMR_SPARE_0_SPARE_REG_SHFT                                    0x0

#define HWIO_AON_CTMR_SPARE_1_ADDR                                       (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x000003fc)
#define HWIO_AON_CTMR_SPARE_1_RMSK                                             0xff
#define HWIO_AON_CTMR_SPARE_1_IN          \
        in_dword(HWIO_AON_CTMR_SPARE_1_ADDR)
#define HWIO_AON_CTMR_SPARE_1_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_SPARE_1_ADDR, m)
#define HWIO_AON_CTMR_SPARE_1_OUT(v)      \
        out_dword(HWIO_AON_CTMR_SPARE_1_ADDR,v)
#define HWIO_AON_CTMR_SPARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_CTMR_SPARE_1_ADDR,m,v,HWIO_AON_CTMR_SPARE_1_IN)
#define HWIO_AON_CTMR_SPARE_1_SPARE_REG_BMSK                                   0xff
#define HWIO_AON_CTMR_SPARE_1_SPARE_REG_SHFT                                    0x0

#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_ADDR                              (AON_CTMR_HZ_CE_TMR_REG_BASE      + 0x00000400)
#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_RMSK                                     0x1
#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_IN          \
        in_dword(HWIO_AON_CTMR_DFT_SCAN_OBSERVE_ADDR)
#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_INM(m)      \
        in_dword_masked(HWIO_AON_CTMR_DFT_SCAN_OBSERVE_ADDR, m)
#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_TP_COMB_RST_XOR_BMSK                     0x1
#define HWIO_AON_CTMR_DFT_SCAN_OBSERVE_TP_COMB_RST_XOR_SHFT                     0x0

/*----------------------------------------------------------------------------
 * MODULE: AON_WDOG_HZ_WATCHDOG
 *--------------------------------------------------------------------------*/

#define AON_WDOG_HZ_WATCHDOG_REG_BASE                        (AON_WDOG_HZ_WATCHDOG_BASE      + 0x00000000)
#define AON_WDOG_HZ_WATCHDOG_REG_BASE_SIZE                   0x100
#define AON_WDOG_HZ_WATCHDOG_REG_BASE_USED                   0x20

#define HWIO_AON_WDOG_DIVISOR_ADDR                           (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000000)
#define HWIO_AON_WDOG_DIVISOR_RMSK                                 0xff
#define HWIO_AON_WDOG_DIVISOR_IN          \
        in_dword(HWIO_AON_WDOG_DIVISOR_ADDR)
#define HWIO_AON_WDOG_DIVISOR_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_DIVISOR_ADDR, m)
#define HWIO_AON_WDOG_DIVISOR_OUT(v)      \
        out_dword(HWIO_AON_WDOG_DIVISOR_ADDR,v)
#define HWIO_AON_WDOG_DIVISOR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_DIVISOR_ADDR,m,v,HWIO_AON_WDOG_DIVISOR_IN)
#define HWIO_AON_WDOG_DIVISOR_VALUE_BMSK                           0xff
#define HWIO_AON_WDOG_DIVISOR_VALUE_SHFT                            0x0

#define HWIO_AON_WDOG_CONTROL_ADDR                           (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000004)
#define HWIO_AON_WDOG_CONTROL_RMSK                                 0x1f
#define HWIO_AON_WDOG_CONTROL_IN          \
        in_dword(HWIO_AON_WDOG_CONTROL_ADDR)
#define HWIO_AON_WDOG_CONTROL_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_CONTROL_ADDR, m)
#define HWIO_AON_WDOG_CONTROL_OUT(v)      \
        out_dword(HWIO_AON_WDOG_CONTROL_ADDR,v)
#define HWIO_AON_WDOG_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_CONTROL_ADDR,m,v,HWIO_AON_WDOG_CONTROL_IN)
#define HWIO_AON_WDOG_CONTROL_FREEZE_IN_DBGACK_BMSK                0x10
#define HWIO_AON_WDOG_CONTROL_FREEZE_IN_DBGACK_SHFT                 0x4
#define HWIO_AON_WDOG_CONTROL_FREEZE_IN_PAUSE_BMSK                  0x8
#define HWIO_AON_WDOG_CONTROL_FREEZE_IN_PAUSE_SHFT                  0x3
#define HWIO_AON_WDOG_CONTROL_WD_BITE_BMSK                          0x4
#define HWIO_AON_WDOG_CONTROL_WD_BITE_SHFT                          0x2
#define HWIO_AON_WDOG_CONTROL_KICK_WD_BMSK                          0x2
#define HWIO_AON_WDOG_CONTROL_KICK_WD_SHFT                          0x1
#define HWIO_AON_WDOG_CONTROL_WD_ACTIVE_BMSK                        0x1
#define HWIO_AON_WDOG_CONTROL_WD_ACTIVE_SHFT                        0x0

#define HWIO_AON_WDOG_COUNT3_ADDR                            (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000008)
#define HWIO_AON_WDOG_COUNT3_RMSK                                  0xff
#define HWIO_AON_WDOG_COUNT3_IN          \
        in_dword(HWIO_AON_WDOG_COUNT3_ADDR)
#define HWIO_AON_WDOG_COUNT3_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_COUNT3_ADDR, m)
#define HWIO_AON_WDOG_COUNT3_VALUE_BMSK                            0xff
#define HWIO_AON_WDOG_COUNT3_VALUE_SHFT                             0x0

#define HWIO_AON_WDOG_WDT_DISABLE_ADDR                       (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x0000000c)
#define HWIO_AON_WDOG_WDT_DISABLE_RMSK                             0xff
#define HWIO_AON_WDOG_WDT_DISABLE_OUT(v)      \
        out_dword(HWIO_AON_WDOG_WDT_DISABLE_ADDR,v)
#define HWIO_AON_WDOG_WDT_DISABLE_SEQUENCE_BMSK                    0xff
#define HWIO_AON_WDOG_WDT_DISABLE_SEQUENCE_SHFT                     0x0

#define HWIO_AON_WDOG_BARK_COUNT_19TO16_ADDR                 (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000010)
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_RMSK                        0xf
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_IN          \
        in_dword(HWIO_AON_WDOG_BARK_COUNT_19TO16_ADDR)
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_BARK_COUNT_19TO16_ADDR, m)
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_OUT(v)      \
        out_dword(HWIO_AON_WDOG_BARK_COUNT_19TO16_ADDR,v)
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_BARK_COUNT_19TO16_ADDR,m,v,HWIO_AON_WDOG_BARK_COUNT_19TO16_IN)
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_VALUE_BMSK                  0xf
#define HWIO_AON_WDOG_BARK_COUNT_19TO16_VALUE_SHFT                  0x0

#define HWIO_AON_WDOG_BARK_COUNT_15TO8_ADDR                  (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000014)
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_RMSK                        0xff
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_IN          \
        in_dword(HWIO_AON_WDOG_BARK_COUNT_15TO8_ADDR)
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_BARK_COUNT_15TO8_ADDR, m)
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_OUT(v)      \
        out_dword(HWIO_AON_WDOG_BARK_COUNT_15TO8_ADDR,v)
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_BARK_COUNT_15TO8_ADDR,m,v,HWIO_AON_WDOG_BARK_COUNT_15TO8_IN)
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_VALUE_BMSK                  0xff
#define HWIO_AON_WDOG_BARK_COUNT_15TO8_VALUE_SHFT                   0x0

#define HWIO_AON_WDOG_BARK_COUNT_7TO0_ADDR                   (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000018)
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_RMSK                         0xff
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_IN          \
        in_dword(HWIO_AON_WDOG_BARK_COUNT_7TO0_ADDR)
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_BARK_COUNT_7TO0_ADDR, m)
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_OUT(v)      \
        out_dword(HWIO_AON_WDOG_BARK_COUNT_7TO0_ADDR,v)
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_BARK_COUNT_7TO0_ADDR,m,v,HWIO_AON_WDOG_BARK_COUNT_7TO0_IN)
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_VALUE_BMSK                   0xff
#define HWIO_AON_WDOG_BARK_COUNT_7TO0_VALUE_SHFT                    0x0

#define HWIO_AON_WDOG_BARK_INT_STATUS_ADDR                   (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x0000001c)
#define HWIO_AON_WDOG_BARK_INT_STATUS_RMSK                          0x1
#define HWIO_AON_WDOG_BARK_INT_STATUS_IN          \
        in_dword(HWIO_AON_WDOG_BARK_INT_STATUS_ADDR)
#define HWIO_AON_WDOG_BARK_INT_STATUS_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_BARK_INT_STATUS_ADDR, m)
#define HWIO_AON_WDOG_BARK_INT_STATUS_OUT(v)      \
        out_dword(HWIO_AON_WDOG_BARK_INT_STATUS_ADDR,v)
#define HWIO_AON_WDOG_BARK_INT_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_BARK_INT_STATUS_ADDR,m,v,HWIO_AON_WDOG_BARK_INT_STATUS_IN)
#define HWIO_AON_WDOG_BARK_INT_STATUS_LEVEL_BMSK                    0x1
#define HWIO_AON_WDOG_BARK_INT_STATUS_LEVEL_SHFT                    0x0

#define HWIO_AON_WDOG_BARK_INT_ENABLE_ADDR                   (AON_WDOG_HZ_WATCHDOG_REG_BASE      + 0x00000020)
#define HWIO_AON_WDOG_BARK_INT_ENABLE_RMSK                          0x1
#define HWIO_AON_WDOG_BARK_INT_ENABLE_IN          \
        in_dword(HWIO_AON_WDOG_BARK_INT_ENABLE_ADDR)
#define HWIO_AON_WDOG_BARK_INT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_AON_WDOG_BARK_INT_ENABLE_ADDR, m)
#define HWIO_AON_WDOG_BARK_INT_ENABLE_OUT(v)      \
        out_dword(HWIO_AON_WDOG_BARK_INT_ENABLE_ADDR,v)
#define HWIO_AON_WDOG_BARK_INT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AON_WDOG_BARK_INT_ENABLE_ADDR,m,v,HWIO_AON_WDOG_BARK_INT_ENABLE_IN)
#define HWIO_AON_WDOG_BARK_INT_ENABLE_VALUE_BMSK                    0x1
#define HWIO_AON_WDOG_BARK_INT_ENABLE_VALUE_SHFT                    0x0

/*----------------------------------------------------------------------------
 * MODULE: NAON_NAON_EFUSE_CSR
 *--------------------------------------------------------------------------*/

#define NAON_NAON_EFUSE_CSR_REG_BASE                                                    (NAON_NAON_EFUSE_CSR_BASE      + 0x00000000)
#define NAON_NAON_EFUSE_CSR_REG_BASE_SIZE                                               0x100
#define NAON_NAON_EFUSE_CSR_REG_BASE_USED                                               0x30

#define HWIO_NAON_EFUSE_CTRL_ADDR                                                       (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x00000000)
#define HWIO_NAON_EFUSE_CTRL_RMSK                                                              0x3
#define HWIO_NAON_EFUSE_CTRL_IN          \
        in_dword(HWIO_NAON_EFUSE_CTRL_ADDR)
#define HWIO_NAON_EFUSE_CTRL_INM(m)      \
        in_dword_masked(HWIO_NAON_EFUSE_CTRL_ADDR, m)
#define HWIO_NAON_EFUSE_CTRL_OUT(v)      \
        out_dword(HWIO_NAON_EFUSE_CTRL_ADDR,v)
#define HWIO_NAON_EFUSE_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NAON_EFUSE_CTRL_ADDR,m,v,HWIO_NAON_EFUSE_CTRL_IN)
#define HWIO_NAON_EFUSE_CTRL_EFUSE_CTRL_CLEARDONE_BMSK                                         0x2
#define HWIO_NAON_EFUSE_CTRL_EFUSE_CTRL_CLEARDONE_SHFT                                         0x1
#define HWIO_NAON_EFUSE_CTRL_EFUSE_CTRL_START_BMSK                                             0x1
#define HWIO_NAON_EFUSE_CTRL_EFUSE_CTRL_START_SHFT                                             0x0

#define HWIO_NAON_EFUSE_PGMCTRLTOP_ADDR                                                 (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x00000004)
#define HWIO_NAON_EFUSE_PGMCTRLTOP_RMSK                                                     0xffff
#define HWIO_NAON_EFUSE_PGMCTRLTOP_IN          \
        in_dword(HWIO_NAON_EFUSE_PGMCTRLTOP_ADDR)
#define HWIO_NAON_EFUSE_PGMCTRLTOP_INM(m)      \
        in_dword_masked(HWIO_NAON_EFUSE_PGMCTRLTOP_ADDR, m)
#define HWIO_NAON_EFUSE_PGMCTRLTOP_OUT(v)      \
        out_dword(HWIO_NAON_EFUSE_PGMCTRLTOP_ADDR,v)
#define HWIO_NAON_EFUSE_PGMCTRLTOP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NAON_EFUSE_PGMCTRLTOP_ADDR,m,v,HWIO_NAON_EFUSE_PGMCTRLTOP_IN)
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_DISABLE_READ_BMSK                          0x8000
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_DISABLE_READ_SHFT                             0xf
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_SEL_SECURITY_NOT_PRIMARY_BMSK              0x4000
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_SEL_SECURITY_NOT_PRIMARY_SHFT                 0xe
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_READ_INSTRUCTION_BMSK                      0x2000
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_READ_INSTRUCTION_SHFT                         0xd
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_PGM_INSTRUCTION_BMSK                       0x1000
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_PGM_INSTRUCTION_SHFT                          0xc
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_VDDQ_RAMP_BMSK                              0xc00
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_VDDQ_RAMP_SHFT                                0xa
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_DISABLE_POST_READ_BMSK                      0x200
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_DISABLE_POST_READ_SHFT                        0x9
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_SCLK_WIDTH_BMSK                             0x1ff
#define HWIO_NAON_EFUSE_PGMCTRLTOP_EFUSE_PGMCTRL_SCLK_WIDTH_SHFT                               0x0

#define HWIO_NAON_EFUSE_STATUS_ADDR                                                     (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x00000008)
#define HWIO_NAON_EFUSE_STATUS_RMSK                                                            0x3
#define HWIO_NAON_EFUSE_STATUS_IN          \
        in_dword(HWIO_NAON_EFUSE_STATUS_ADDR)
#define HWIO_NAON_EFUSE_STATUS_INM(m)      \
        in_dword_masked(HWIO_NAON_EFUSE_STATUS_ADDR, m)
#define HWIO_NAON_EFUSE_STATUS_EFUSE_STATUS_PGM_SUCCESS_BMSK                                   0x2
#define HWIO_NAON_EFUSE_STATUS_EFUSE_STATUS_PGM_SUCCESS_SHFT                                   0x1
#define HWIO_NAON_EFUSE_STATUS_EFUSE_STATUS_DONE_BMSK                                          0x1
#define HWIO_NAON_EFUSE_STATUS_EFUSE_STATUS_DONE_SHFT                                          0x0

#define HWIO_NAON_PRGM_0_ADDR                                                           (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x0000000c)
#define HWIO_NAON_PRGM_0_RMSK                                                           0xffffffff
#define HWIO_NAON_PRGM_0_IN          \
        in_dword(HWIO_NAON_PRGM_0_ADDR)
#define HWIO_NAON_PRGM_0_INM(m)      \
        in_dword_masked(HWIO_NAON_PRGM_0_ADDR, m)
#define HWIO_NAON_PRGM_0_OUT(v)      \
        out_dword(HWIO_NAON_PRGM_0_ADDR,v)
#define HWIO_NAON_PRGM_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NAON_PRGM_0_ADDR,m,v,HWIO_NAON_PRGM_0_IN)
#define HWIO_NAON_PRGM_0_DATA_BMSK                                                      0xffffffff
#define HWIO_NAON_PRGM_0_DATA_SHFT                                                             0x0

#define HWIO_NAON_PRGM_1_ADDR                                                           (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x00000010)
#define HWIO_NAON_PRGM_1_RMSK                                                           0xffffffff
#define HWIO_NAON_PRGM_1_IN          \
        in_dword(HWIO_NAON_PRGM_1_ADDR)
#define HWIO_NAON_PRGM_1_INM(m)      \
        in_dword_masked(HWIO_NAON_PRGM_1_ADDR, m)
#define HWIO_NAON_PRGM_1_OUT(v)      \
        out_dword(HWIO_NAON_PRGM_1_ADDR,v)
#define HWIO_NAON_PRGM_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NAON_PRGM_1_ADDR,m,v,HWIO_NAON_PRGM_1_IN)
#define HWIO_NAON_PRGM_1_DATA_BMSK                                                      0xffffffff
#define HWIO_NAON_PRGM_1_DATA_SHFT                                                             0x0

#define HWIO_NAON_READ_0_ADDR                                                           (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x0000002c)
#define HWIO_NAON_READ_0_RMSK                                                           0xffffffff
#define HWIO_NAON_READ_0_IN          \
        in_dword(HWIO_NAON_READ_0_ADDR)
#define HWIO_NAON_READ_0_INM(m)      \
        in_dword_masked(HWIO_NAON_READ_0_ADDR, m)
#define HWIO_NAON_READ_0_DATA_BMSK                                                      0xffffffff
#define HWIO_NAON_READ_0_DATA_SHFT                                                             0x0

#define HWIO_NAON_READ_1_ADDR                                                           (NAON_NAON_EFUSE_CSR_REG_BASE      + 0x00000030)
#define HWIO_NAON_READ_1_RMSK                                                           0xffffffff
#define HWIO_NAON_READ_1_IN          \
        in_dword(HWIO_NAON_READ_1_ADDR)
#define HWIO_NAON_READ_1_INM(m)      \
        in_dword_masked(HWIO_NAON_READ_1_ADDR, m)
#define HWIO_NAON_READ_1_DATA_BMSK                                                      0xffffffff
#define HWIO_NAON_READ_1_DATA_SHFT                                                             0x0


#endif /* __HWIO_AON_H__ */
