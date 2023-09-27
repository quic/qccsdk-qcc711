#ifndef __HWIO_GCC_H__
#define __HWIO_GCC_H__
/*
===========================================================================
*/
/**
  @file hwio_gcc.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    GCC_REG

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['GCC_REG'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_gcc.h',
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
 * MODULE: GCC_REG
 *--------------------------------------------------------------------------*/

#define GCC_REG_REG_BASE                                                      (GCC_REG_BASE      + 0x00000000)
#define GCC_REG_REG_BASE_SIZE                                                 0x1000
#define GCC_REG_REG_BASE_USED                                                 0xa0

#define HWIO_APPSS_CBCR_ADDR                                                  (GCC_REG_REG_BASE      + 0x00000000)
#define HWIO_APPSS_CBCR_RMSK                                                  0x80000007
#define HWIO_APPSS_CBCR_IN          \
        in_dword(HWIO_APPSS_CBCR_ADDR)
#define HWIO_APPSS_CBCR_INM(m)      \
        in_dword_masked(HWIO_APPSS_CBCR_ADDR, m)
#define HWIO_APPSS_CBCR_OUT(v)      \
        out_dword(HWIO_APPSS_CBCR_ADDR,v)
#define HWIO_APPSS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APPSS_CBCR_ADDR,m,v,HWIO_APPSS_CBCR_IN)
#define HWIO_APPSS_CBCR_CLK_OFF_BMSK                                          0x80000000
#define HWIO_APPSS_CBCR_CLK_OFF_SHFT                                                0x1f
#define HWIO_APPSS_CBCR_CLK_ARES_BMSK                                                0x4
#define HWIO_APPSS_CBCR_CLK_ARES_SHFT                                                0x2
#define HWIO_APPSS_CBCR_HW_CTL_BMSK                                                  0x2
#define HWIO_APPSS_CBCR_HW_CTL_SHFT                                                  0x1
#define HWIO_APPSS_CBCR_CLK_ENABLE_BMSK                                              0x1
#define HWIO_APPSS_CBCR_CLK_ENABLE_SHFT                                              0x0

#define HWIO_E21CPU_CBCR_ADDR                                                 (GCC_REG_REG_BASE      + 0x00000004)
#define HWIO_E21CPU_CBCR_RMSK                                                 0x80000007
#define HWIO_E21CPU_CBCR_IN          \
        in_dword(HWIO_E21CPU_CBCR_ADDR)
#define HWIO_E21CPU_CBCR_INM(m)      \
        in_dword_masked(HWIO_E21CPU_CBCR_ADDR, m)
#define HWIO_E21CPU_CBCR_OUT(v)      \
        out_dword(HWIO_E21CPU_CBCR_ADDR,v)
#define HWIO_E21CPU_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_E21CPU_CBCR_ADDR,m,v,HWIO_E21CPU_CBCR_IN)
#define HWIO_E21CPU_CBCR_CLK_OFF_BMSK                                         0x80000000
#define HWIO_E21CPU_CBCR_CLK_OFF_SHFT                                               0x1f
#define HWIO_E21CPU_CBCR_CLK_ARES_BMSK                                               0x4
#define HWIO_E21CPU_CBCR_CLK_ARES_SHFT                                               0x2
#define HWIO_E21CPU_CBCR_HW_CTL_BMSK                                                 0x2
#define HWIO_E21CPU_CBCR_HW_CTL_SHFT                                                 0x1
#define HWIO_E21CPU_CBCR_CLK_ENABLE_BMSK                                             0x1
#define HWIO_E21CPU_CBCR_CLK_ENABLE_SHFT                                             0x0

#define HWIO_TMEL_DBG_CBCR_ADDR                                               (GCC_REG_REG_BASE      + 0x00000008)
#define HWIO_TMEL_DBG_CBCR_RMSK                                               0x80000007
#define HWIO_TMEL_DBG_CBCR_IN          \
        in_dword(HWIO_TMEL_DBG_CBCR_ADDR)
#define HWIO_TMEL_DBG_CBCR_INM(m)      \
        in_dword_masked(HWIO_TMEL_DBG_CBCR_ADDR, m)
#define HWIO_TMEL_DBG_CBCR_OUT(v)      \
        out_dword(HWIO_TMEL_DBG_CBCR_ADDR,v)
#define HWIO_TMEL_DBG_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TMEL_DBG_CBCR_ADDR,m,v,HWIO_TMEL_DBG_CBCR_IN)
#define HWIO_TMEL_DBG_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_TMEL_DBG_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_TMEL_DBG_CBCR_CLK_ARES_BMSK                                             0x4
#define HWIO_TMEL_DBG_CBCR_CLK_ARES_SHFT                                             0x2
#define HWIO_TMEL_DBG_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_TMEL_DBG_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_TMEL_DBG_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_TMEL_DBG_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_SYS_FABRIC_CBCR_ADDR                                             (GCC_REG_REG_BASE      + 0x0000000c)
#define HWIO_SYS_FABRIC_CBCR_RMSK                                             0x80000006
#define HWIO_SYS_FABRIC_CBCR_IN          \
        in_dword(HWIO_SYS_FABRIC_CBCR_ADDR)
#define HWIO_SYS_FABRIC_CBCR_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_CBCR_ADDR, m)
#define HWIO_SYS_FABRIC_CBCR_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_CBCR_ADDR,v)
#define HWIO_SYS_FABRIC_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_CBCR_ADDR,m,v,HWIO_SYS_FABRIC_CBCR_IN)
#define HWIO_SYS_FABRIC_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_SYS_FABRIC_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_SYS_FABRIC_CBCR_CLK_ARES_BMSK                                           0x4
#define HWIO_SYS_FABRIC_CBCR_CLK_ARES_SHFT                                           0x2
#define HWIO_SYS_FABRIC_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_SYS_FABRIC_CBCR_HW_CTL_SHFT                                             0x1

#define HWIO_BTSS_CBCR_ADDR                                                   (GCC_REG_REG_BASE      + 0x00000010)
#define HWIO_BTSS_CBCR_RMSK                                                   0x80000007
#define HWIO_BTSS_CBCR_IN          \
        in_dword(HWIO_BTSS_CBCR_ADDR)
#define HWIO_BTSS_CBCR_INM(m)      \
        in_dword_masked(HWIO_BTSS_CBCR_ADDR, m)
#define HWIO_BTSS_CBCR_OUT(v)      \
        out_dword(HWIO_BTSS_CBCR_ADDR,v)
#define HWIO_BTSS_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BTSS_CBCR_ADDR,m,v,HWIO_BTSS_CBCR_IN)
#define HWIO_BTSS_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_BTSS_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_BTSS_CBCR_CLK_ARES_BMSK                                                 0x4
#define HWIO_BTSS_CBCR_CLK_ARES_SHFT                                                 0x2
#define HWIO_BTSS_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_BTSS_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_BTSS_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_BTSS_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_DEBUG_DAP_CBCR_ADDR                                              (GCC_REG_REG_BASE      + 0x00000014)
#define HWIO_DEBUG_DAP_CBCR_RMSK                                              0x80000006
#define HWIO_DEBUG_DAP_CBCR_IN          \
        in_dword(HWIO_DEBUG_DAP_CBCR_ADDR)
#define HWIO_DEBUG_DAP_CBCR_INM(m)      \
        in_dword_masked(HWIO_DEBUG_DAP_CBCR_ADDR, m)
#define HWIO_DEBUG_DAP_CBCR_OUT(v)      \
        out_dword(HWIO_DEBUG_DAP_CBCR_ADDR,v)
#define HWIO_DEBUG_DAP_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DEBUG_DAP_CBCR_ADDR,m,v,HWIO_DEBUG_DAP_CBCR_IN)
#define HWIO_DEBUG_DAP_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_DEBUG_DAP_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_DEBUG_DAP_CBCR_CLK_ARES_BMSK                                            0x4
#define HWIO_DEBUG_DAP_CBCR_CLK_ARES_SHFT                                            0x2
#define HWIO_DEBUG_DAP_CBCR_HW_CTL_BMSK                                              0x2
#define HWIO_DEBUG_DAP_CBCR_HW_CTL_SHFT                                              0x1

#define HWIO_SMM_AHB_CBCR_ADDR                                                (GCC_REG_REG_BASE      + 0x00000018)
#define HWIO_SMM_AHB_CBCR_RMSK                                                0x80000007
#define HWIO_SMM_AHB_CBCR_IN          \
        in_dword(HWIO_SMM_AHB_CBCR_ADDR)
#define HWIO_SMM_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_SMM_AHB_CBCR_ADDR, m)
#define HWIO_SMM_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_SMM_AHB_CBCR_ADDR,v)
#define HWIO_SMM_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SMM_AHB_CBCR_ADDR,m,v,HWIO_SMM_AHB_CBCR_IN)
#define HWIO_SMM_AHB_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_SMM_AHB_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_SMM_AHB_CBCR_CLK_ARES_BMSK                                              0x4
#define HWIO_SMM_AHB_CBCR_CLK_ARES_SHFT                                              0x2
#define HWIO_SMM_AHB_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_SMM_AHB_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_SMM_AHB_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_SMM_AHB_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_TLMM_CBCR_ADDR                                                   (GCC_REG_REG_BASE      + 0x0000001c)
#define HWIO_TLMM_CBCR_RMSK                                                   0x80000007
#define HWIO_TLMM_CBCR_IN          \
        in_dword(HWIO_TLMM_CBCR_ADDR)
#define HWIO_TLMM_CBCR_INM(m)      \
        in_dword_masked(HWIO_TLMM_CBCR_ADDR, m)
#define HWIO_TLMM_CBCR_OUT(v)      \
        out_dword(HWIO_TLMM_CBCR_ADDR,v)
#define HWIO_TLMM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TLMM_CBCR_ADDR,m,v,HWIO_TLMM_CBCR_IN)
#define HWIO_TLMM_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_TLMM_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_TLMM_CBCR_CLK_ARES_BMSK                                                 0x4
#define HWIO_TLMM_CBCR_CLK_ARES_SHFT                                                 0x2
#define HWIO_TLMM_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_TLMM_CBCR_HW_CTL_SHFT                                                   0x1
#define HWIO_TLMM_CBCR_CLK_ENABLE_BMSK                                               0x1
#define HWIO_TLMM_CBCR_CLK_ENABLE_SHFT                                               0x0

#define HWIO_PERIPH_AHB_CBCR_ADDR                                             (GCC_REG_REG_BASE      + 0x00000020)
#define HWIO_PERIPH_AHB_CBCR_RMSK                                             0x80000007
#define HWIO_PERIPH_AHB_CBCR_IN          \
        in_dword(HWIO_PERIPH_AHB_CBCR_ADDR)
#define HWIO_PERIPH_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_PERIPH_AHB_CBCR_ADDR, m)
#define HWIO_PERIPH_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_PERIPH_AHB_CBCR_ADDR,v)
#define HWIO_PERIPH_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PERIPH_AHB_CBCR_ADDR,m,v,HWIO_PERIPH_AHB_CBCR_IN)
#define HWIO_PERIPH_AHB_CBCR_CLK_OFF_BMSK                                     0x80000000
#define HWIO_PERIPH_AHB_CBCR_CLK_OFF_SHFT                                           0x1f
#define HWIO_PERIPH_AHB_CBCR_CLK_ARES_BMSK                                           0x4
#define HWIO_PERIPH_AHB_CBCR_CLK_ARES_SHFT                                           0x2
#define HWIO_PERIPH_AHB_CBCR_HW_CTL_BMSK                                             0x2
#define HWIO_PERIPH_AHB_CBCR_HW_CTL_SHFT                                             0x1
#define HWIO_PERIPH_AHB_CBCR_CLK_ENABLE_BMSK                                         0x1
#define HWIO_PERIPH_AHB_CBCR_CLK_ENABLE_SHFT                                         0x0

#define HWIO_PERIPH_CORE_CBCR_ADDR                                            (GCC_REG_REG_BASE      + 0x00000024)
#define HWIO_PERIPH_CORE_CBCR_RMSK                                            0x80000007
#define HWIO_PERIPH_CORE_CBCR_IN          \
        in_dword(HWIO_PERIPH_CORE_CBCR_ADDR)
#define HWIO_PERIPH_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_PERIPH_CORE_CBCR_ADDR, m)
#define HWIO_PERIPH_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_PERIPH_CORE_CBCR_ADDR,v)
#define HWIO_PERIPH_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PERIPH_CORE_CBCR_ADDR,m,v,HWIO_PERIPH_CORE_CBCR_IN)
#define HWIO_PERIPH_CORE_CBCR_CLK_OFF_BMSK                                    0x80000000
#define HWIO_PERIPH_CORE_CBCR_CLK_OFF_SHFT                                          0x1f
#define HWIO_PERIPH_CORE_CBCR_CLK_ARES_BMSK                                          0x4
#define HWIO_PERIPH_CORE_CBCR_CLK_ARES_SHFT                                          0x2
#define HWIO_PERIPH_CORE_CBCR_HW_CTL_BMSK                                            0x2
#define HWIO_PERIPH_CORE_CBCR_HW_CTL_SHFT                                            0x1
#define HWIO_PERIPH_CORE_CBCR_CLK_ENABLE_BMSK                                        0x1
#define HWIO_PERIPH_CORE_CBCR_CLK_ENABLE_SHFT                                        0x0

#define HWIO_NVM_BCR_ADDR                                                     (GCC_REG_REG_BASE      + 0x00000028)
#define HWIO_NVM_BCR_RMSK                                                            0x1
#define HWIO_NVM_BCR_IN          \
        in_dword(HWIO_NVM_BCR_ADDR)
#define HWIO_NVM_BCR_INM(m)      \
        in_dword_masked(HWIO_NVM_BCR_ADDR, m)
#define HWIO_NVM_BCR_OUT(v)      \
        out_dword(HWIO_NVM_BCR_ADDR,v)
#define HWIO_NVM_BCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_BCR_ADDR,m,v,HWIO_NVM_BCR_IN)
#define HWIO_NVM_BCR_BLK_ARES_BMSK                                                   0x1
#define HWIO_NVM_BCR_BLK_ARES_SHFT                                                   0x0

#define HWIO_NVM_CBCR_ADDR                                                    (GCC_REG_REG_BASE      + 0x0000002c)
#define HWIO_NVM_CBCR_RMSK                                                    0x80000007
#define HWIO_NVM_CBCR_IN          \
        in_dword(HWIO_NVM_CBCR_ADDR)
#define HWIO_NVM_CBCR_INM(m)      \
        in_dword_masked(HWIO_NVM_CBCR_ADDR, m)
#define HWIO_NVM_CBCR_OUT(v)      \
        out_dword(HWIO_NVM_CBCR_ADDR,v)
#define HWIO_NVM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_CBCR_ADDR,m,v,HWIO_NVM_CBCR_IN)
#define HWIO_NVM_CBCR_CLK_OFF_BMSK                                            0x80000000
#define HWIO_NVM_CBCR_CLK_OFF_SHFT                                                  0x1f
#define HWIO_NVM_CBCR_CLK_ARES_BMSK                                                  0x4
#define HWIO_NVM_CBCR_CLK_ARES_SHFT                                                  0x2
#define HWIO_NVM_CBCR_HW_CTL_BMSK                                                    0x2
#define HWIO_NVM_CBCR_HW_CTL_SHFT                                                    0x1
#define HWIO_NVM_CBCR_CLK_ENABLE_BMSK                                                0x1
#define HWIO_NVM_CBCR_CLK_ENABLE_SHFT                                                0x0

#define HWIO_NVM_AHB_CBCR_ADDR                                                (GCC_REG_REG_BASE      + 0x00000030)
#define HWIO_NVM_AHB_CBCR_RMSK                                                0x80000007
#define HWIO_NVM_AHB_CBCR_IN          \
        in_dword(HWIO_NVM_AHB_CBCR_ADDR)
#define HWIO_NVM_AHB_CBCR_INM(m)      \
        in_dword_masked(HWIO_NVM_AHB_CBCR_ADDR, m)
#define HWIO_NVM_AHB_CBCR_OUT(v)      \
        out_dword(HWIO_NVM_AHB_CBCR_ADDR,v)
#define HWIO_NVM_AHB_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_AHB_CBCR_ADDR,m,v,HWIO_NVM_AHB_CBCR_IN)
#define HWIO_NVM_AHB_CBCR_CLK_OFF_BMSK                                        0x80000000
#define HWIO_NVM_AHB_CBCR_CLK_OFF_SHFT                                              0x1f
#define HWIO_NVM_AHB_CBCR_CLK_ARES_BMSK                                              0x4
#define HWIO_NVM_AHB_CBCR_CLK_ARES_SHFT                                              0x2
#define HWIO_NVM_AHB_CBCR_HW_CTL_BMSK                                                0x2
#define HWIO_NVM_AHB_CBCR_HW_CTL_SHFT                                                0x1
#define HWIO_NVM_AHB_CBCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_NVM_AHB_CBCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_NVM_RRAM_CBCR_ADDR                                               (GCC_REG_REG_BASE      + 0x00000034)
#define HWIO_NVM_RRAM_CBCR_RMSK                                               0x80000007
#define HWIO_NVM_RRAM_CBCR_IN          \
        in_dword(HWIO_NVM_RRAM_CBCR_ADDR)
#define HWIO_NVM_RRAM_CBCR_INM(m)      \
        in_dword_masked(HWIO_NVM_RRAM_CBCR_ADDR, m)
#define HWIO_NVM_RRAM_CBCR_OUT(v)      \
        out_dword(HWIO_NVM_RRAM_CBCR_ADDR,v)
#define HWIO_NVM_RRAM_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_RRAM_CBCR_ADDR,m,v,HWIO_NVM_RRAM_CBCR_IN)
#define HWIO_NVM_RRAM_CBCR_CLK_OFF_BMSK                                       0x80000000
#define HWIO_NVM_RRAM_CBCR_CLK_OFF_SHFT                                             0x1f
#define HWIO_NVM_RRAM_CBCR_CLK_ARES_BMSK                                             0x4
#define HWIO_NVM_RRAM_CBCR_CLK_ARES_SHFT                                             0x2
#define HWIO_NVM_RRAM_CBCR_HW_CTL_BMSK                                               0x2
#define HWIO_NVM_RRAM_CBCR_HW_CTL_SHFT                                               0x1
#define HWIO_NVM_RRAM_CBCR_CLK_ENABLE_BMSK                                           0x1
#define HWIO_NVM_RRAM_CBCR_CLK_ENABLE_SHFT                                           0x0

#define HWIO_NAON_CBCR_ADDR                                                   (GCC_REG_REG_BASE      + 0x00000038)
#define HWIO_NAON_CBCR_RMSK                                                   0x80000006
#define HWIO_NAON_CBCR_IN          \
        in_dword(HWIO_NAON_CBCR_ADDR)
#define HWIO_NAON_CBCR_INM(m)      \
        in_dword_masked(HWIO_NAON_CBCR_ADDR, m)
#define HWIO_NAON_CBCR_OUT(v)      \
        out_dword(HWIO_NAON_CBCR_ADDR,v)
#define HWIO_NAON_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NAON_CBCR_ADDR,m,v,HWIO_NAON_CBCR_IN)
#define HWIO_NAON_CBCR_CLK_OFF_BMSK                                           0x80000000
#define HWIO_NAON_CBCR_CLK_OFF_SHFT                                                 0x1f
#define HWIO_NAON_CBCR_CLK_ARES_BMSK                                                 0x4
#define HWIO_NAON_CBCR_CLK_ARES_SHFT                                                 0x2
#define HWIO_NAON_CBCR_HW_CTL_BMSK                                                   0x2
#define HWIO_NAON_CBCR_HW_CTL_SHFT                                                   0x1

#define HWIO_SLOW_CORE_CBCR_ADDR                                              (GCC_REG_REG_BASE      + 0x0000003c)
#define HWIO_SLOW_CORE_CBCR_RMSK                                              0x80000005
#define HWIO_SLOW_CORE_CBCR_IN          \
        in_dword(HWIO_SLOW_CORE_CBCR_ADDR)
#define HWIO_SLOW_CORE_CBCR_INM(m)      \
        in_dword_masked(HWIO_SLOW_CORE_CBCR_ADDR, m)
#define HWIO_SLOW_CORE_CBCR_OUT(v)      \
        out_dword(HWIO_SLOW_CORE_CBCR_ADDR,v)
#define HWIO_SLOW_CORE_CBCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SLOW_CORE_CBCR_ADDR,m,v,HWIO_SLOW_CORE_CBCR_IN)
#define HWIO_SLOW_CORE_CBCR_CLK_OFF_BMSK                                      0x80000000
#define HWIO_SLOW_CORE_CBCR_CLK_OFF_SHFT                                            0x1f
#define HWIO_SLOW_CORE_CBCR_CLK_ARES_BMSK                                            0x4
#define HWIO_SLOW_CORE_CBCR_CLK_ARES_SHFT                                            0x2
#define HWIO_SLOW_CORE_CBCR_CLK_ENABLE_BMSK                                          0x1
#define HWIO_SLOW_CORE_CBCR_CLK_ENABLE_SHFT                                          0x0

#define HWIO_DEBUG_CLOCK_MUX_SEL_ADDR                                         (GCC_REG_REG_BASE      + 0x00000040)
#define HWIO_DEBUG_CLOCK_MUX_SEL_RMSK                                               0x3f
#define HWIO_DEBUG_CLOCK_MUX_SEL_IN          \
        in_dword(HWIO_DEBUG_CLOCK_MUX_SEL_ADDR)
#define HWIO_DEBUG_CLOCK_MUX_SEL_INM(m)      \
        in_dword_masked(HWIO_DEBUG_CLOCK_MUX_SEL_ADDR, m)
#define HWIO_DEBUG_CLOCK_MUX_SEL_OUT(v)      \
        out_dword(HWIO_DEBUG_CLOCK_MUX_SEL_ADDR,v)
#define HWIO_DEBUG_CLOCK_MUX_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_DEBUG_CLOCK_MUX_SEL_ADDR,m,v,HWIO_DEBUG_CLOCK_MUX_SEL_IN)
#define HWIO_DEBUG_CLOCK_MUX_SEL_DEBUG_CLK_STAGE1_MUX_SEL_BMSK                      0x38
#define HWIO_DEBUG_CLOCK_MUX_SEL_DEBUG_CLK_STAGE1_MUX_SEL_SHFT                       0x3
#define HWIO_DEBUG_CLOCK_MUX_SEL_DEBUG_CLK_STAGE0_MUX_SEL_BMSK                       0x7
#define HWIO_DEBUG_CLOCK_MUX_SEL_DEBUG_CLK_STAGE0_MUX_SEL_SHFT                       0x0

#define HWIO_SMM_CFG_CGCR_ADDR                                                (GCC_REG_REG_BASE      + 0x00000044)
#define HWIO_SMM_CFG_CGCR_RMSK                                                       0x1
#define HWIO_SMM_CFG_CGCR_IN          \
        in_dword(HWIO_SMM_CFG_CGCR_ADDR)
#define HWIO_SMM_CFG_CGCR_INM(m)      \
        in_dword_masked(HWIO_SMM_CFG_CGCR_ADDR, m)
#define HWIO_SMM_CFG_CGCR_OUT(v)      \
        out_dword(HWIO_SMM_CFG_CGCR_ADDR,v)
#define HWIO_SMM_CFG_CGCR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SMM_CFG_CGCR_ADDR,m,v,HWIO_SMM_CFG_CGCR_IN)
#define HWIO_SMM_CFG_CGCR_CLK_ENABLE_BMSK                                            0x1
#define HWIO_SMM_CFG_CGCR_CLK_ENABLE_SHFT                                            0x0

#define HWIO_AUX_ANA_TMUX_CTRL0_REG_ADDR                                      (GCC_REG_REG_BASE      + 0x00000048)
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_RMSK                                          0x3ff0
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_IN          \
        in_dword(HWIO_AUX_ANA_TMUX_CTRL0_REG_ADDR)
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_TMUX_CTRL0_REG_ADDR, m)
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_TMUX_CTRL0_REG_ADDR,v)
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_TMUX_CTRL0_REG_ADDR,m,v,HWIO_AUX_ANA_TMUX_CTRL0_REG_IN)
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_TST_SEL_EN_BMSK                       0x2000
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_TST_SEL_EN_SHFT                          0xd
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_TST_SEL_CLK_BMSK                      0x1000
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_TST_SEL_CLK_SHFT                         0xc
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_XTAL_TEST_CTRL_BMSK                    0xf00
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_XTAL_TEST_CTRL_SHFT                      0x8
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_PLL_TST_SEL_PLL_CLK_BMSK                0xc0
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_PLL_TST_SEL_PLL_CLK_SHFT                 0x6
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_PLL_SEL_REF_BMSK                        0x30
#define HWIO_AUX_ANA_TMUX_CTRL0_REG_AUX_ANA_PLL_SEL_REF_SHFT                         0x4

#define HWIO_AUX_ANA_CTRL0_SET0_ADDR                                          (GCC_REG_REG_BASE      + 0x0000004c)
#define HWIO_AUX_ANA_CTRL0_SET0_RMSK                                              0x7fff
#define HWIO_AUX_ANA_CTRL0_SET0_IN          \
        in_dword(HWIO_AUX_ANA_CTRL0_SET0_ADDR)
#define HWIO_AUX_ANA_CTRL0_SET0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL0_SET0_ADDR, m)
#define HWIO_AUX_ANA_CTRL0_SET0_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL0_SET0_ADDR,v)
#define HWIO_AUX_ANA_CTRL0_SET0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL0_SET0_ADDR,m,v,HWIO_AUX_ANA_CTRL0_SET0_IN)
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_ULP_BMSK                         0x4000
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_ULP_SHFT                            0xe
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_XTAL_BMSK                        0x2000
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_XTAL_SHFT                           0xd
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_TRIM_DUTY_BMSK                   0x1000
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_TRIM_DUTY_SHFT                      0xc
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_DUTY_DET_BMSK                     0x800
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_DUTY_DET_SHFT                       0xb
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_CLK_IO_BMSK                       0x400
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_CLK_IO_SHFT                         0xa
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_CLK_DET_BMSK                      0x200
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_CLK_DET_SHFT                        0x9
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_AMP_DET_BMSK                      0x100
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_SEL_AMP_DET_SHFT                        0x8
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_EN_BMSK                                0x80
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_EN_SHFT                                 0x7
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_SLEW_EN_B_BMSK                     0x40
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_SLEW_EN_B_SHFT                      0x6
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_PULL_UP_BMSK                       0x20
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_PULL_UP_SHFT                        0x5
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_PULL_STRENGTH_BMSK                 0x10
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_PULL_STRENGTH_SHFT                  0x4
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_EN_STICKY_BMSK                      0x8
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_EN_STICKY_SHFT                      0x3
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_EN_PULL_BMSK                        0x4
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_EN_PULL_SHFT                        0x2
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_DRIVE_STRENGTH_BMSK                 0x3
#define HWIO_AUX_ANA_CTRL0_SET0_AUX_ANA_XTAL_DRV_DRIVE_STRENGTH_SHFT                 0x0

#define HWIO_AUX_ANA_CTRL0_SET1_ADDR                                          (GCC_REG_REG_BASE      + 0x00000050)
#define HWIO_AUX_ANA_CTRL0_SET1_RMSK                                              0x7fff
#define HWIO_AUX_ANA_CTRL0_SET1_IN          \
        in_dword(HWIO_AUX_ANA_CTRL0_SET1_ADDR)
#define HWIO_AUX_ANA_CTRL0_SET1_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL0_SET1_ADDR, m)
#define HWIO_AUX_ANA_CTRL0_SET1_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL0_SET1_ADDR,v)
#define HWIO_AUX_ANA_CTRL0_SET1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL0_SET1_ADDR,m,v,HWIO_AUX_ANA_CTRL0_SET1_IN)
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_ULP_BMSK                         0x4000
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_ULP_SHFT                            0xe
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_XTAL_BMSK                        0x2000
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_XTAL_SHFT                           0xd
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_TRIM_DUTY_BMSK                   0x1000
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_TRIM_DUTY_SHFT                      0xc
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_DUTY_DET_BMSK                     0x800
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_DUTY_DET_SHFT                       0xb
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_CLK_IO_BMSK                       0x400
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_CLK_IO_SHFT                         0xa
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_CLK_DET_BMSK                      0x200
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_CLK_DET_SHFT                        0x9
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_AMP_DET_BMSK                      0x100
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_SEL_AMP_DET_SHFT                        0x8
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_EN_BMSK                                0x80
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_EN_SHFT                                 0x7
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_SLEW_EN_B_BMSK                     0x40
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_SLEW_EN_B_SHFT                      0x6
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_PULL_UP_BMSK                       0x20
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_PULL_UP_SHFT                        0x5
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_PULL_STRENGTH_BMSK                 0x10
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_PULL_STRENGTH_SHFT                  0x4
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_EN_STICKY_BMSK                      0x8
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_EN_STICKY_SHFT                      0x3
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_EN_PULL_BMSK                        0x4
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_EN_PULL_SHFT                        0x2
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_DRIVE_STRENGTH_BMSK                 0x3
#define HWIO_AUX_ANA_CTRL0_SET1_AUX_ANA_XTAL_DRV_DRIVE_STRENGTH_SHFT                 0x0

#define HWIO_AUX_ANA_CTRL1_SET0_ADDR                                          (GCC_REG_REG_BASE      + 0x00000054)
#define HWIO_AUX_ANA_CTRL1_SET0_RMSK                                               0xfff
#define HWIO_AUX_ANA_CTRL1_SET0_IN          \
        in_dword(HWIO_AUX_ANA_CTRL1_SET0_ADDR)
#define HWIO_AUX_ANA_CTRL1_SET0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL1_SET0_ADDR, m)
#define HWIO_AUX_ANA_CTRL1_SET0_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL1_SET0_ADDR,v)
#define HWIO_AUX_ANA_CTRL1_SET0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL1_SET0_ADDR,m,v,HWIO_AUX_ANA_CTRL1_SET0_IN)
#define HWIO_AUX_ANA_CTRL1_SET0_AUX_ANA_XTAL_SEL_OPTION_BMSK                       0xff0
#define HWIO_AUX_ANA_CTRL1_SET0_AUX_ANA_XTAL_SEL_OPTION_SHFT                         0x4
#define HWIO_AUX_ANA_CTRL1_SET0_AUX_ANA_XTAL_SEL_CLK_BMSK                            0xf
#define HWIO_AUX_ANA_CTRL1_SET0_AUX_ANA_XTAL_SEL_CLK_SHFT                            0x0

#define HWIO_AUX_ANA_CTRL1_SET1_ADDR                                          (GCC_REG_REG_BASE      + 0x00000058)
#define HWIO_AUX_ANA_CTRL1_SET1_RMSK                                               0xfff
#define HWIO_AUX_ANA_CTRL1_SET1_IN          \
        in_dword(HWIO_AUX_ANA_CTRL1_SET1_ADDR)
#define HWIO_AUX_ANA_CTRL1_SET1_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL1_SET1_ADDR, m)
#define HWIO_AUX_ANA_CTRL1_SET1_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL1_SET1_ADDR,v)
#define HWIO_AUX_ANA_CTRL1_SET1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL1_SET1_ADDR,m,v,HWIO_AUX_ANA_CTRL1_SET1_IN)
#define HWIO_AUX_ANA_CTRL1_SET1_AUX_ANA_XTAL_SEL_OPTION_BMSK                       0xff0
#define HWIO_AUX_ANA_CTRL1_SET1_AUX_ANA_XTAL_SEL_OPTION_SHFT                         0x4
#define HWIO_AUX_ANA_CTRL1_SET1_AUX_ANA_XTAL_SEL_CLK_BMSK                            0xf
#define HWIO_AUX_ANA_CTRL1_SET1_AUX_ANA_XTAL_SEL_CLK_SHFT                            0x0

#define HWIO_AUX_ANA_CTRL2_REG_ADDR                                           (GCC_REG_REG_BASE      + 0x0000005c)
#define HWIO_AUX_ANA_CTRL2_REG_RMSK                                               0x7fff
#define HWIO_AUX_ANA_CTRL2_REG_IN          \
        in_dword(HWIO_AUX_ANA_CTRL2_REG_ADDR)
#define HWIO_AUX_ANA_CTRL2_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL2_REG_ADDR, m)
#define HWIO_AUX_ANA_CTRL2_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL2_REG_ADDR,v)
#define HWIO_AUX_ANA_CTRL2_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL2_REG_ADDR,m,v,HWIO_AUX_ANA_CTRL2_REG_IN)
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_RES_BMSK                     0x7c00
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_RES_SHFT                        0xa
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_BIAS_BMSK                     0x3e0
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_BIAS_SHFT                       0x5
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_ULP_BIAS_BMSK                  0x1f
#define HWIO_AUX_ANA_CTRL2_REG_AUX_ANA_XTAL_TRIM_BUF_ULP_BIAS_SHFT                   0x0

#define HWIO_AUX_ANA_CTRL3_REG_ADDR                                           (GCC_REG_REG_BASE      + 0x00000060)
#define HWIO_AUX_ANA_CTRL3_REG_RMSK                                               0x7fff
#define HWIO_AUX_ANA_CTRL3_REG_IN          \
        in_dword(HWIO_AUX_ANA_CTRL3_REG_ADDR)
#define HWIO_AUX_ANA_CTRL3_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL3_REG_ADDR, m)
#define HWIO_AUX_ANA_CTRL3_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL3_REG_ADDR,v)
#define HWIO_AUX_ANA_CTRL3_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL3_REG_ADDR,m,v,HWIO_AUX_ANA_CTRL3_REG_IN)
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_BMSK                     0x7c00
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_FINE_SHFT                        0xa
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_BMSK                    0x3e0
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_CL_COARSE_SHFT                      0x5
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_DUTY_BMSK                          0x1f
#define HWIO_AUX_ANA_CTRL3_REG_AUX_ANA_XTAL_TRIM_DUTY_SHFT                           0x0

#define HWIO_AUX_ANA_CTRL4_SET0_ADDR                                          (GCC_REG_REG_BASE      + 0x00000064)
#define HWIO_AUX_ANA_CTRL4_SET0_RMSK                                               0xfff
#define HWIO_AUX_ANA_CTRL4_SET0_IN          \
        in_dword(HWIO_AUX_ANA_CTRL4_SET0_ADDR)
#define HWIO_AUX_ANA_CTRL4_SET0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL4_SET0_ADDR, m)
#define HWIO_AUX_ANA_CTRL4_SET0_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL4_SET0_ADDR,v)
#define HWIO_AUX_ANA_CTRL4_SET0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL4_SET0_ADDR,m,v,HWIO_AUX_ANA_CTRL4_SET0_IN)
#define HWIO_AUX_ANA_CTRL4_SET0_AUX_ANA_XTAL_TRIM_OSC_BIAS_BMSK                    0xfc0
#define HWIO_AUX_ANA_CTRL4_SET0_AUX_ANA_XTAL_TRIM_OSC_BIAS_SHFT                      0x6
#define HWIO_AUX_ANA_CTRL4_SET0_AUX_ANA_XTAL_TRIM_OSC_ULP_BIAS_BMSK                 0x3f
#define HWIO_AUX_ANA_CTRL4_SET0_AUX_ANA_XTAL_TRIM_OSC_ULP_BIAS_SHFT                  0x0

#define HWIO_AUX_ANA_CTRL4_SET1_ADDR                                          (GCC_REG_REG_BASE      + 0x00000068)
#define HWIO_AUX_ANA_CTRL4_SET1_RMSK                                               0xfff
#define HWIO_AUX_ANA_CTRL4_SET1_IN          \
        in_dword(HWIO_AUX_ANA_CTRL4_SET1_ADDR)
#define HWIO_AUX_ANA_CTRL4_SET1_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL4_SET1_ADDR, m)
#define HWIO_AUX_ANA_CTRL4_SET1_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL4_SET1_ADDR,v)
#define HWIO_AUX_ANA_CTRL4_SET1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL4_SET1_ADDR,m,v,HWIO_AUX_ANA_CTRL4_SET1_IN)
#define HWIO_AUX_ANA_CTRL4_SET1_AUX_ANA_XTAL_TRIM_OSC_BIAS_BMSK                    0xfc0
#define HWIO_AUX_ANA_CTRL4_SET1_AUX_ANA_XTAL_TRIM_OSC_BIAS_SHFT                      0x6
#define HWIO_AUX_ANA_CTRL4_SET1_AUX_ANA_XTAL_TRIM_OSC_ULP_BIAS_BMSK                 0x3f
#define HWIO_AUX_ANA_CTRL4_SET1_AUX_ANA_XTAL_TRIM_OSC_ULP_BIAS_SHFT                  0x0

#define HWIO_AUX_ANA_CTRL5_SET0_ADDR                                          (GCC_REG_REG_BASE      + 0x0000006c)
#define HWIO_AUX_ANA_CTRL5_SET0_RMSK                                                 0x7
#define HWIO_AUX_ANA_CTRL5_SET0_IN          \
        in_dword(HWIO_AUX_ANA_CTRL5_SET0_ADDR)
#define HWIO_AUX_ANA_CTRL5_SET0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL5_SET0_ADDR, m)
#define HWIO_AUX_ANA_CTRL5_SET0_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL5_SET0_ADDR,v)
#define HWIO_AUX_ANA_CTRL5_SET0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL5_SET0_ADDR,m,v,HWIO_AUX_ANA_CTRL5_SET0_IN)
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_BUFFER_BMSK                         0x4
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_BUFFER_SHFT                         0x2
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_CL_BMSK                             0x2
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_CL_SHFT                             0x1
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_GM_HIGH_R_BMSK                      0x1
#define HWIO_AUX_ANA_CTRL5_SET0_AUX_ANA_XTAL_SEL_GM_HIGH_R_SHFT                      0x0

#define HWIO_AUX_ANA_CTRL5_SET1_ADDR                                          (GCC_REG_REG_BASE      + 0x00000070)
#define HWIO_AUX_ANA_CTRL5_SET1_RMSK                                                 0x7
#define HWIO_AUX_ANA_CTRL5_SET1_IN          \
        in_dword(HWIO_AUX_ANA_CTRL5_SET1_ADDR)
#define HWIO_AUX_ANA_CTRL5_SET1_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL5_SET1_ADDR, m)
#define HWIO_AUX_ANA_CTRL5_SET1_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL5_SET1_ADDR,v)
#define HWIO_AUX_ANA_CTRL5_SET1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL5_SET1_ADDR,m,v,HWIO_AUX_ANA_CTRL5_SET1_IN)
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_BUFFER_BMSK                         0x4
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_BUFFER_SHFT                         0x2
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_CL_BMSK                             0x2
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_CL_SHFT                             0x1
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_GM_HIGH_R_BMSK                      0x1
#define HWIO_AUX_ANA_CTRL5_SET1_AUX_ANA_XTAL_SEL_GM_HIGH_R_SHFT                      0x0

#define HWIO_AUX_ANA_CTRL6_SET0_ADDR                                          (GCC_REG_REG_BASE      + 0x00000074)
#define HWIO_AUX_ANA_CTRL6_SET0_RMSK                                              0x7000
#define HWIO_AUX_ANA_CTRL6_SET0_IN          \
        in_dword(HWIO_AUX_ANA_CTRL6_SET0_ADDR)
#define HWIO_AUX_ANA_CTRL6_SET0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL6_SET0_ADDR, m)
#define HWIO_AUX_ANA_CTRL6_SET0_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL6_SET0_ADDR,v)
#define HWIO_AUX_ANA_CTRL6_SET0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL6_SET0_ADDR,m,v,HWIO_AUX_ANA_CTRL6_SET0_IN)
#define HWIO_AUX_ANA_CTRL6_SET0_AUX_ANA_XTAL_CLKDET_AMP_BMSK                      0x6000
#define HWIO_AUX_ANA_CTRL6_SET0_AUX_ANA_XTAL_CLKDET_AMP_SHFT                         0xd
#define HWIO_AUX_ANA_CTRL6_SET0_AUX_ANA_XTAL_EN_LOW_NOISE_REG_BMSK                0x1000
#define HWIO_AUX_ANA_CTRL6_SET0_AUX_ANA_XTAL_EN_LOW_NOISE_REG_SHFT                   0xc

#define HWIO_AUX_ANA_CTRL6_SET1_ADDR                                          (GCC_REG_REG_BASE      + 0x00000078)
#define HWIO_AUX_ANA_CTRL6_SET1_RMSK                                              0x7000
#define HWIO_AUX_ANA_CTRL6_SET1_IN          \
        in_dword(HWIO_AUX_ANA_CTRL6_SET1_ADDR)
#define HWIO_AUX_ANA_CTRL6_SET1_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL6_SET1_ADDR, m)
#define HWIO_AUX_ANA_CTRL6_SET1_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL6_SET1_ADDR,v)
#define HWIO_AUX_ANA_CTRL6_SET1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL6_SET1_ADDR,m,v,HWIO_AUX_ANA_CTRL6_SET1_IN)
#define HWIO_AUX_ANA_CTRL6_SET1_AUX_ANA_XTAL_CLKDET_AMP_BMSK                      0x6000
#define HWIO_AUX_ANA_CTRL6_SET1_AUX_ANA_XTAL_CLKDET_AMP_SHFT                         0xd
#define HWIO_AUX_ANA_CTRL6_SET1_AUX_ANA_XTAL_EN_LOW_NOISE_REG_BMSK                0x1000
#define HWIO_AUX_ANA_CTRL6_SET1_AUX_ANA_XTAL_EN_LOW_NOISE_REG_SHFT                   0xc

#define HWIO_AUX_ANA_CTRL7_REG_ADDR                                           (GCC_REG_REG_BASE      + 0x0000007c)
#define HWIO_AUX_ANA_CTRL7_REG_RMSK                                                0x1ff
#define HWIO_AUX_ANA_CTRL7_REG_IN          \
        in_dword(HWIO_AUX_ANA_CTRL7_REG_ADDR)
#define HWIO_AUX_ANA_CTRL7_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL7_REG_ADDR, m)
#define HWIO_AUX_ANA_CTRL7_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL7_REG_ADDR,v)
#define HWIO_AUX_ANA_CTRL7_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL7_REG_ADDR,m,v,HWIO_AUX_ANA_CTRL7_REG_IN)
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_AMP_DET_CAL_BMSK                       0x100
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_AMP_DET_CAL_SHFT                         0x8
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_TRIM_REG_BMSK                           0xf0
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_TRIM_REG_SHFT                            0x4
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_TRIM_BG_BMSK                             0xf
#define HWIO_AUX_ANA_CTRL7_REG_AUX_ANA_XTAL_TRIM_BG_SHFT                             0x0

#define HWIO_AUX_ANA_CTRL8_REG_ADDR                                           (GCC_REG_REG_BASE      + 0x00000080)
#define HWIO_AUX_ANA_CTRL8_REG_RMSK                                               0x3f4f
#define HWIO_AUX_ANA_CTRL8_REG_IN          \
        in_dword(HWIO_AUX_ANA_CTRL8_REG_ADDR)
#define HWIO_AUX_ANA_CTRL8_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL8_REG_ADDR, m)
#define HWIO_AUX_ANA_CTRL8_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL8_REG_ADDR,v)
#define HWIO_AUX_ANA_CTRL8_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL8_REG_ADDR,m,v,HWIO_AUX_ANA_CTRL8_REG_IN)
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_TST_SEL_XTAL_CLK_BMSK                      0x2000
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_TST_SEL_XTAL_CLK_SHFT                         0xd
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_REG_MON_BMSK                      0x1000
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_REG_MON_SHFT                         0xc
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_REG_EA_BMSK                        0x800
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_REG_EA_SHFT                          0xb
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_DIV_BMSK                           0x700
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_DIV_SHFT                             0x8
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_BG_EA_BMSK                          0x40
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_BG_EA_SHFT                           0x6
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_TEST_BYPASS_BMSK                         0xc
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_TEST_BYPASS_SHFT                         0x2
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_BIAS_BMSK                            0x3
#define HWIO_AUX_ANA_CTRL8_REG_AUX_ANA_XTAL_SEL_BIAS_SHFT                            0x0

#define HWIO_AUX_ANA_CTRL9_REG_ADDR                                           (GCC_REG_REG_BASE      + 0x00000084)
#define HWIO_AUX_ANA_CTRL9_REG_RMSK                                                 0xff
#define HWIO_AUX_ANA_CTRL9_REG_IN          \
        in_dword(HWIO_AUX_ANA_CTRL9_REG_ADDR)
#define HWIO_AUX_ANA_CTRL9_REG_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_CTRL9_REG_ADDR, m)
#define HWIO_AUX_ANA_CTRL9_REG_OUT(v)      \
        out_dword(HWIO_AUX_ANA_CTRL9_REG_ADDR,v)
#define HWIO_AUX_ANA_CTRL9_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_ANA_CTRL9_REG_ADDR,m,v,HWIO_AUX_ANA_CTRL9_REG_IN)
#define HWIO_AUX_ANA_CTRL9_REG_AUX_DI_XTL_SPARE_BMSK                                0xff
#define HWIO_AUX_ANA_CTRL9_REG_AUX_DI_XTL_SPARE_SHFT                                 0x0

#define HWIO_AUX_ANA_XTAL_STATUS0_ADDR                                        (GCC_REG_REG_BASE      + 0x00000088)
#define HWIO_AUX_ANA_XTAL_STATUS0_RMSK                                               0x1
#define HWIO_AUX_ANA_XTAL_STATUS0_IN          \
        in_dword(HWIO_AUX_ANA_XTAL_STATUS0_ADDR)
#define HWIO_AUX_ANA_XTAL_STATUS0_INM(m)      \
        in_dword_masked(HWIO_AUX_ANA_XTAL_STATUS0_ADDR, m)
#define HWIO_AUX_ANA_XTAL_STATUS0_AUX_ANA_XTAL_STATUS_CLK_DET_BMSK                   0x1
#define HWIO_AUX_ANA_XTAL_STATUS0_AUX_ANA_XTAL_STATUS_CLK_DET_SHFT                   0x0

#define HWIO_AUX_DRV_T1_ADDR                                                  (GCC_REG_REG_BASE      + 0x0000008c)
#define HWIO_AUX_DRV_T1_RMSK                                                      0x7fff
#define HWIO_AUX_DRV_T1_IN          \
        in_dword(HWIO_AUX_DRV_T1_ADDR)
#define HWIO_AUX_DRV_T1_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_T1_ADDR, m)
#define HWIO_AUX_DRV_T1_OUT(v)      \
        out_dword(HWIO_AUX_DRV_T1_ADDR,v)
#define HWIO_AUX_DRV_T1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_T1_ADDR,m,v,HWIO_AUX_DRV_T1_IN)
#define HWIO_AUX_DRV_T1_VAL_BMSK                                                  0x7fff
#define HWIO_AUX_DRV_T1_VAL_SHFT                                                     0x0

#define HWIO_AUX_DRV_ADDR                                                     (GCC_REG_REG_BASE      + 0x00000090)
#define HWIO_AUX_DRV_RMSK                                                         0xffff
#define HWIO_AUX_DRV_IN          \
        in_dword(HWIO_AUX_DRV_ADDR)
#define HWIO_AUX_DRV_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_ADDR, m)
#define HWIO_AUX_DRV_OUT(v)      \
        out_dword(HWIO_AUX_DRV_ADDR,v)
#define HWIO_AUX_DRV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_ADDR,m,v,HWIO_AUX_DRV_IN)
#define HWIO_AUX_DRV_FOSC_TIME_OUT_VAL_BMSK                                       0xff00
#define HWIO_AUX_DRV_FOSC_TIME_OUT_VAL_SHFT                                          0x8
#define HWIO_AUX_DRV_AUX_TIME_OUT_VAL_BMSK                                          0xff
#define HWIO_AUX_DRV_AUX_TIME_OUT_VAL_SHFT                                           0x0

#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_ADDR                                    (GCC_REG_REG_BASE      + 0x00000094)
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_RMSK                                       0x1ffff
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_IN          \
        in_dword(HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_ADDR)
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_ADDR, m)
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_OUT(v)      \
        out_dword(HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_ADDR,v)
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_ADDR,m,v,HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_IN)
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_OVRD_EN_BMSK                               0x10000
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_OVRD_EN_SHFT                                  0x10
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_SEL_BMSK                                    0x8000
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_SEL_SHFT                                       0xf
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_WAIT_VAL_BMSK                               0x7fff
#define HWIO_AUX_DRV_GMHIEHR_OR_XTLCL_WAIT_VAL_SHFT                                  0x0

#define HWIO_AUX_DRV_T3_ADDR                                                  (GCC_REG_REG_BASE      + 0x00000098)
#define HWIO_AUX_DRV_T3_RMSK                                                      0x7fff
#define HWIO_AUX_DRV_T3_IN          \
        in_dword(HWIO_AUX_DRV_T3_ADDR)
#define HWIO_AUX_DRV_T3_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_T3_ADDR, m)
#define HWIO_AUX_DRV_T3_OUT(v)      \
        out_dword(HWIO_AUX_DRV_T3_ADDR,v)
#define HWIO_AUX_DRV_T3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_T3_ADDR,m,v,HWIO_AUX_DRV_T3_IN)
#define HWIO_AUX_DRV_T3_VAL_BMSK                                                  0x7fff
#define HWIO_AUX_DRV_T3_VAL_SHFT                                                     0x0

#define HWIO_AUX_DRV_T4_ADDR                                                  (GCC_REG_REG_BASE      + 0x0000009c)
#define HWIO_AUX_DRV_T4_RMSK                                                      0x7fff
#define HWIO_AUX_DRV_T4_IN          \
        in_dword(HWIO_AUX_DRV_T4_ADDR)
#define HWIO_AUX_DRV_T4_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_T4_ADDR, m)
#define HWIO_AUX_DRV_T4_OUT(v)      \
        out_dword(HWIO_AUX_DRV_T4_ADDR,v)
#define HWIO_AUX_DRV_T4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_T4_ADDR,m,v,HWIO_AUX_DRV_T4_IN)
#define HWIO_AUX_DRV_T4_VAL_BMSK                                                  0x7fff
#define HWIO_AUX_DRV_T4_VAL_SHFT                                                     0x0

#define HWIO_AUX_DRV_CTRL_ADDR                                                (GCC_REG_REG_BASE      + 0x000000a0)
#define HWIO_AUX_DRV_CTRL_RMSK                                                  0x1fffff
#define HWIO_AUX_DRV_CTRL_IN          \
        in_dword(HWIO_AUX_DRV_CTRL_ADDR)
#define HWIO_AUX_DRV_CTRL_INM(m)      \
        in_dword_masked(HWIO_AUX_DRV_CTRL_ADDR, m)
#define HWIO_AUX_DRV_CTRL_OUT(v)      \
        out_dword(HWIO_AUX_DRV_CTRL_ADDR,v)
#define HWIO_AUX_DRV_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AUX_DRV_CTRL_ADDR,m,v,HWIO_AUX_DRV_CTRL_IN)
#define HWIO_AUX_DRV_CTRL_AUX_OK_AUTO_BMSK                                      0x100000
#define HWIO_AUX_DRV_CTRL_AUX_OK_AUTO_SHFT                                          0x14
#define HWIO_AUX_DRV_CTRL_AUX_OK_CNT_VAL_BMSK                                    0xffff0
#define HWIO_AUX_DRV_CTRL_AUX_OK_CNT_VAL_SHFT                                        0x4
#define HWIO_AUX_DRV_CTRL_START_BMSK                                                 0x8
#define HWIO_AUX_DRV_CTRL_START_SHFT                                                 0x3
#define HWIO_AUX_DRV_CTRL_RST_BMSK                                                   0x4
#define HWIO_AUX_DRV_CTRL_RST_SHFT                                                   0x2
#define HWIO_AUX_DRV_CTRL_ENABLE_BMSK                                                0x2
#define HWIO_AUX_DRV_CTRL_ENABLE_SHFT                                                0x1
#define HWIO_AUX_DRV_CTRL_CLK_SWITCH_DISBALE_BMSK                                    0x1
#define HWIO_AUX_DRV_CTRL_CLK_SWITCH_DISBALE_SHFT                                    0x0


#endif /* __HWIO_GCC_H__ */
