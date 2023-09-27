#ifndef __HWIO_SYSFABRIC_H__
#define __HWIO_SYSFABRIC_H__
/*
===========================================================================
*/
/**
  @file hwio_sysfabric.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    SYS_FABRIC_SYS_FABRIC_CSR

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['SYS_FABRIC_SYS_FABRIC_CSR'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_sysfabric.h',
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
 * MODULE: SYS_FABRIC_SYS_FABRIC_CSR
 *--------------------------------------------------------------------------*/

#define SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE                                                     (SYS_FABRIC_SYS_FABRIC_CSR_BASE      + 0x00000000)
#define SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE_SIZE                                                0x1000
#define SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE_USED                                                0x84

#define HWIO_SYS_FABRIC_CONTROL_ADDR                                                           (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000000)
#define HWIO_SYS_FABRIC_CONTROL_RMSK                                                               0xff3f
#define HWIO_SYS_FABRIC_CONTROL_IN          \
        in_dword(HWIO_SYS_FABRIC_CONTROL_ADDR)
#define HWIO_SYS_FABRIC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_CONTROL_ADDR, m)
#define HWIO_SYS_FABRIC_CONTROL_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_CONTROL_ADDR,v)
#define HWIO_SYS_FABRIC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_CONTROL_ADDR,m,v,HWIO_SYS_FABRIC_CONTROL_IN)
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_VAL_BMSK                                                   0xff00
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_VAL_SHFT                                                      0x8
#define HWIO_SYS_FABRIC_CONTROL_CLKGATE_DISABLE_BMSK                                                 0x20
#define HWIO_SYS_FABRIC_CONTROL_CLKGATE_DISABLE_SHFT                                                  0x5
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_ERR_INTR_EN_BMSK                                             0x10
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_ERR_INTR_EN_SHFT                                              0x4
#define HWIO_SYS_FABRIC_CONTROL_DECODE_ERR_INTR_EN_BMSK                                               0x8
#define HWIO_SYS_FABRIC_CONTROL_DECODE_ERR_INTR_EN_SHFT                                               0x3
#define HWIO_SYS_FABRIC_CONTROL_SLV_ERR_INTR_EN_BMSK                                                  0x4
#define HWIO_SYS_FABRIC_CONTROL_SLV_ERR_INTR_EN_SHFT                                                  0x2
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_EN_BMSK                                                       0x2
#define HWIO_SYS_FABRIC_CONTROL_TIMEOUT_EN_SHFT                                                       0x1
#define HWIO_SYS_FABRIC_CONTROL_ERR_MON_EN_BMSK                                                       0x1
#define HWIO_SYS_FABRIC_CONTROL_ERR_MON_EN_SHFT                                                       0x0

#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000004)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_RMSK                                                 0x1ff
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_ADDR)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_ADDR,m,v,HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_IN)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_BMSK                         0x100
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_SHFT                           0x8
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_BMSK                   0x80
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_SHFT                    0x7
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_BMSK                   0x40
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_SHFT                    0x6
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_BMSK                        0x20
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_SHFT                         0x5
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_BMSK                         0x10
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_SHFT                          0x4
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_BMSK                     0x8
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_SHFT                     0x3
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_BMSK                   0x4
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_SHFT                   0x2
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_BMSK                   0x2
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_SHFT                   0x1
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_BMSK                           0x1
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_SHFT                           0x0

#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000008)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_RMSK                                                 0x1ff
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_ADDR)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_TME_M0_ERROR_BMSK                                    0x100
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_TME_M0_ERROR_SHFT                                      0x8
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_BMSK                              0x80
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_SHFT                               0x7
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_BMSK                              0x40
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_SHFT                               0x6
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_DEBUG_M0_ERROR_BMSK                                   0x20
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_DEBUG_M0_ERROR_SHFT                                    0x5
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_BTSS_M0_ERROR_BMSK                                    0x10
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_BTSS_M0_ERROR_SHFT                                     0x4
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_BMSK                                0x8
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_SHFT                                0x3
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_BMSK                              0x4
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_SHFT                              0x2
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_BMSK                              0x2
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_SHFT                              0x1
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_AON_M0_ERROR_BMSK                                      0x1
#define HWIO_SYS_FABRIC_APPSS_INTERRUPT_STATUS_AON_M0_ERROR_SHFT                                      0x0

#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_ADDR                                             (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000000c)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_RMSK                                                  0x1ff
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_IN          \
        in_dword(HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_ADDR)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_ADDR,m,v,HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_IN)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_BMSK                          0x100
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_SHFT                            0x8
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_BMSK                    0x80
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_SHFT                     0x7
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_BMSK                    0x40
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_SHFT                     0x6
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_BMSK                         0x20
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_SHFT                          0x5
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_BMSK                          0x10
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_SHFT                           0x4
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_BMSK                      0x8
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_SHFT                      0x3
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_BMSK                    0x4
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_SHFT                    0x2
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_BMSK                    0x2
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_SHFT                    0x1
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_BMSK                            0x1
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_SHFT                            0x0

#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_ADDR                                             (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000010)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_RMSK                                                  0x1ff
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_ADDR)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_TME_M0_ERROR_BMSK                                     0x100
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_TME_M0_ERROR_SHFT                                       0x8
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_BMSK                               0x80
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_SHFT                                0x7
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_BMSK                               0x40
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_SHFT                                0x6
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_DEBUG_M0_ERROR_BMSK                                    0x20
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_DEBUG_M0_ERROR_SHFT                                     0x5
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_BTSS_M0_ERROR_BMSK                                     0x10
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_BTSS_M0_ERROR_SHFT                                      0x4
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_BMSK                                 0x8
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_SHFT                                 0x3
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_BMSK                               0x4
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_SHFT                               0x2
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_BMSK                               0x2
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_SHFT                               0x1
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_AON_M0_ERROR_BMSK                                       0x1
#define HWIO_SYS_FABRIC_BTSS_INTERRUPT_STATUS_AON_M0_ERROR_SHFT                                       0x0

#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000014)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_RMSK                                                 0x1ff
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_IN          \
        in_dword(HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_ADDR)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_ADDR, m)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_ADDR,v)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_ADDR,m,v,HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_IN)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_BMSK                         0x100
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_TME_M0_INTERRUPT_ENABLE_SHFT                           0x8
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_BMSK                   0x80
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_PERIPH_DMA_M1_INTERRUPT_ENABLE_SHFT                    0x7
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_BMSK                   0x40
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_PERIPH_DMA_M0_INTERRUPT_ENABLE_SHFT                    0x6
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_BMSK                        0x20
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_DEBUG_M0_INTERRUPT_ENABLE_SHFT                         0x5
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_BMSK                         0x10
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_BTSS_M0_INTERRUPT_ENABLE_SHFT                          0x4
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_BMSK                     0x8
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_SYS_M2_INTERRUPT_ENABLE_SHFT                     0x3
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_BMSK                   0x4
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_ICODE_M0_INTERRUPT_ENABLE_SHFT                   0x2
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_BMSK                   0x2
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_APPSS_DCODE_M1_INTERRUPT_ENABLE_SHFT                   0x1
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_BMSK                           0x1
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_ENABLE_AON_M0_INTERRUPT_ENABLE_SHFT                           0x0

#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000018)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_RMSK                                                 0x1ff
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_ADDR)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_TME_M0_ERROR_BMSK                                    0x100
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_TME_M0_ERROR_SHFT                                      0x8
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_BMSK                              0x80
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_PERIPH_DMA_M1_ERROR_SHFT                               0x7
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_BMSK                              0x40
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_PERIPH_DMA_M0_ERROR_SHFT                               0x6
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_DEBUG_M0_ERROR_BMSK                                   0x20
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_DEBUG_M0_ERROR_SHFT                                    0x5
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_BTSS_M0_ERROR_BMSK                                    0x10
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_BTSS_M0_ERROR_SHFT                                     0x4
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_BMSK                                0x8
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_SYS_M2_ERROR_SHFT                                0x3
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_BMSK                              0x4
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_ICODE_M0_ERROR_SHFT                              0x2
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_BMSK                              0x2
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_APPSS_DCODE_M1_ERROR_SHFT                              0x1
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_AON_M0_ERROR_BMSK                                      0x1
#define HWIO_SYS_FABRIC_TMESS_INTERRUPT_STATUS_AON_M0_ERROR_SHFT                                      0x0

#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000001c)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_RMSK                                                 0x307
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_HAUSER_BMSK                                          0x300
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_HAUSER_SHFT                                            0x8
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_HWRITE_BMSK                                            0x4
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_HWRITE_SHFT                                            0x2
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_TYPE_BMSK                                              0x3
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME1_TYPE_SHFT                                              0x0

#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000020)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_RMSK                                            0xffffffff
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_HADDR_BMSK                                      0xffffffff
#define HWIO_SYS_FABRIC_AON_M0_ERROR_SYNDROME2_HADDR_SHFT                                             0x0

#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_ADDR                                               (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000024)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_RMSK                                                    0x7e7
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_BMSK                       0x400
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_SHFT                         0xa
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                       0x200
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                         0x9
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                       0x100
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                         0x8
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_BMSK                      0x80
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_SHFT                       0x7
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_BMSK                         0x40
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_SHFT                          0x6
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_BMSK                         0x20
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_SHFT                          0x5
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_BMSK                          0x4
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_SHFT                          0x2
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                                  0x2
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                                  0x1
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                                     0x1
#define HWIO_SYS_FABRIC_AON_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                                     0x0

#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_ADDR                                    (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000028)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_RMSK                                         0x307
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_HAUSER_BMSK                                  0x300
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_HAUSER_SHFT                                    0x8
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_HWRITE_BMSK                                    0x4
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_HWRITE_SHFT                                    0x2
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_TYPE_BMSK                                      0x3
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME1_TYPE_SHFT                                      0x0

#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_ADDR                                    (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000002c)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_RMSK                                    0xffffffff
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_HADDR_BMSK                              0xffffffff
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_SYNDROME2_HADDR_SHFT                                     0x0

#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_ADDR                                       (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000030)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_RMSK                                            0x313
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK               0x200
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                 0x9
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK               0x100
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                 0x8
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_BMSK                 0x10
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_SHFT                  0x4
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                          0x2
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                          0x1
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                             0x1
#define HWIO_SYS_FABRIC_APPSS_DCODE_M1_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                             0x0

#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_ADDR                                    (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000034)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_RMSK                                         0x307
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_HAUSER_BMSK                                  0x300
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_HAUSER_SHFT                                    0x8
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_HWRITE_BMSK                                    0x4
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_HWRITE_SHFT                                    0x2
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_TYPE_BMSK                                      0x3
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME1_TYPE_SHFT                                      0x0

#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_ADDR                                    (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000038)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_RMSK                                    0xffffffff
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_HADDR_BMSK                              0xffffffff
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_SYNDROME2_HADDR_SHFT                                     0x0

#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_ADDR                                       (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000003c)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_RMSK                                            0x313
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK               0x200
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                 0x9
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK               0x100
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                 0x8
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_BMSK                 0x10
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_SHFT                  0x4
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                          0x2
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                          0x1
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                             0x1
#define HWIO_SYS_FABRIC_APPSS_ICODE_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                             0x0

#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_ADDR                                      (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000040)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_RMSK                                           0x307
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_HAUSER_BMSK                                    0x300
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_HAUSER_SHFT                                      0x8
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_HWRITE_BMSK                                      0x4
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_HWRITE_SHFT                                      0x2
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_TYPE_BMSK                                        0x3
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME1_TYPE_SHFT                                        0x0

#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_ADDR                                      (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000044)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_RMSK                                      0xffffffff
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_HADDR_BMSK                                0xffffffff
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_SYNDROME2_HADDR_SHFT                                       0x0

#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_ADDR                                         (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000048)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_RMSK                                              0xfd7
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_TME_S0_TIMEOUT_ERROR_STATUS_BMSK                  0x800
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_TME_S0_TIMEOUT_ERROR_STATUS_SHFT                    0xb
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_BMSK                 0x400
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_SHFT                   0xa
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                 0x200
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                   0x9
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                 0x100
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                   0x8
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_BMSK                0x80
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_SHFT                 0x7
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_BMSK                   0x40
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_SHFT                    0x6
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_BMSK                   0x10
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_NVM_S1_TIMEOUT_ERROR_STATUS_SHFT                    0x4
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_BMSK                    0x4
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_SHFT                    0x2
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                            0x2
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                            0x1
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                               0x1
#define HWIO_SYS_FABRIC_APPSS_SYS_M2_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                               0x0

#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_ADDR                                           (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000004c)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_RMSK                                                0x307
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_HAUSER_BMSK                                         0x300
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_HAUSER_SHFT                                           0x8
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_HWRITE_BMSK                                           0x4
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_HWRITE_SHFT                                           0x2
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_TYPE_BMSK                                             0x3
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME1_TYPE_SHFT                                             0x0

#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_ADDR                                           (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000050)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_RMSK                                           0xffffffff
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_HADDR_BMSK                                     0xffffffff
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_SYNDROME2_HADDR_SHFT                                            0x0

#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_ADDR                                              (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000054)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_RMSK                                                   0xfcf
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_TME_S0_TIMEOUT_ERROR_STATUS_BMSK                       0x800
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_TME_S0_TIMEOUT_ERROR_STATUS_SHFT                         0xb
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_BMSK                      0x400
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_SHFT                        0xa
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                      0x200
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                        0x9
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                      0x100
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                        0x8
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_BMSK                     0x80
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_SHFT                      0x7
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_BMSK                        0x40
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_SHFT                         0x6
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_NVM_S0_TIMEOUT_ERROR_STATUS_BMSK                         0x8
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_NVM_S0_TIMEOUT_ERROR_STATUS_SHFT                         0x3
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_BMSK                         0x4
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_SHFT                         0x2
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                                 0x2
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                                 0x1
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                                    0x1
#define HWIO_SYS_FABRIC_BTSS_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                                    0x0

#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_ADDR                                          (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000058)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_RMSK                                               0x307
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_HAUSER_BMSK                                        0x300
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_HAUSER_SHFT                                          0x8
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_HWRITE_BMSK                                          0x4
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_HWRITE_SHFT                                          0x2
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_TYPE_BMSK                                            0x3
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME1_TYPE_SHFT                                            0x0

#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_ADDR                                          (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000005c)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_RMSK                                          0xffffffff
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_HADDR_BMSK                                    0xffffffff
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_SYNDROME2_HADDR_SHFT                                           0x0

#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_ADDR                                             (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000060)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_RMSK                                                  0x7e7
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_BMSK                     0x400
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_SHFT                       0xa
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                     0x200
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                       0x9
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                     0x100
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                       0x8
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_BMSK                    0x80
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_SHFT                     0x7
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_BMSK                       0x40
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_SHFT                        0x6
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_BMSK                       0x20
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_SHFT                        0x5
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_BMSK                        0x4
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_SHFT                        0x2
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                                0x2
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                                0x1
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                                   0x1
#define HWIO_SYS_FABRIC_DEBUG_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                                   0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_ADDR                                     (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000064)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_RMSK                                          0x307
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_HAUSER_BMSK                                   0x300
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_HAUSER_SHFT                                     0x8
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_HWRITE_BMSK                                     0x4
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_HWRITE_SHFT                                     0x2
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_TYPE_BMSK                                       0x3
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME1_TYPE_SHFT                                       0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_ADDR                                     (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000068)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_RMSK                                     0xffffffff
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_HADDR_BMSK                               0xffffffff
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_SYNDROME2_HADDR_SHFT                                      0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_ADDR                                        (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000006c)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_RMSK                                             0x323
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                0x200
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                  0x9
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                0x100
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                  0x8
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_BMSK                  0x20
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_SHFT                   0x5
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                           0x2
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                           0x1
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                              0x1
#define HWIO_SYS_FABRIC_PERIPH_DMA_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                              0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_ADDR                                     (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000070)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_RMSK                                          0x307
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_HAUSER_BMSK                                   0x300
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_HAUSER_SHFT                                     0x8
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_HWRITE_BMSK                                     0x4
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_HWRITE_SHFT                                     0x2
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_TYPE_BMSK                                       0x3
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME1_TYPE_SHFT                                       0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_ADDR                                     (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000074)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_RMSK                                     0xffffffff
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_HADDR_BMSK                               0xffffffff
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_SYNDROME2_HADDR_SHFT                                      0x0

#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_ADDR                                        (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000078)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_RMSK                                             0x323
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                0x200
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                  0x9
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                0x100
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                  0x8
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_BMSK                  0x20
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_SHFT                   0x5
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                           0x2
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                           0x1
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                              0x1
#define HWIO_SYS_FABRIC_PERIPH_DMA_M1_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                              0x0

#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x0000007c)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_RMSK                                                 0x307
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_IN          \
        in_dword(HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_ADDR)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_ADDR, m)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_HAUSER_BMSK                                          0x300
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_HAUSER_SHFT                                            0x8
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_HWRITE_BMSK                                            0x4
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_HWRITE_SHFT                                            0x2
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_TYPE_BMSK                                              0x3
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME1_TYPE_SHFT                                              0x0

#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_ADDR                                            (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000080)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_RMSK                                            0xffffffff
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_IN          \
        in_dword(HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_ADDR)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_ADDR, m)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_HADDR_BMSK                                      0xffffffff
#define HWIO_SYS_FABRIC_TME_M0_ERROR_SYNDROME2_HADDR_SHFT                                             0x0

#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_ADDR                                               (SYS_FABRIC_SYS_FABRIC_CSR_REG_BASE      + 0x00000084)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_RMSK                                                    0x7e7
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_IN          \
        in_dword(HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_ADDR)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_ADDR, m)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_OUT(v)      \
        out_dword(HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_ADDR,v)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_ADDR,m,v,HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_IN)
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_BMSK                       0x400
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S2_TIMEOUT_ERROR_STATUS_SHFT                         0xa
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_BMSK                       0x200
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S1_TIMEOUT_ERROR_STATUS_SHFT                         0x9
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_BMSK                       0x100
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SRAM_S0_TIMEOUT_ERROR_STATUS_SHFT                         0x8
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_BMSK                      0x80
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_PERIPH_S0_TIMEOUT_ERROR_STATUS_SHFT                       0x7
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_BMSK                         0x40
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_NVM_S3_TIMEOUT_ERROR_STATUS_SHFT                          0x6
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_BMSK                         0x20
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_NVM_S2_TIMEOUT_ERROR_STATUS_SHFT                          0x5
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_BMSK                          0x4
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_AON_S0_TIMEOUT_ERROR_STATUS_SHFT                          0x2
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_DECODE_ERROR_STATUS_BMSK                                  0x2
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_DECODE_ERROR_STATUS_SHFT                                  0x1
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SLV_ERROR_STATUS_BMSK                                     0x1
#define HWIO_SYS_FABRIC_TME_M0_ERROR_STATUS_SLV_ERROR_STATUS_SHFT                                     0x0


#endif /* __HWIO_SYSFABRIC_H__ */
