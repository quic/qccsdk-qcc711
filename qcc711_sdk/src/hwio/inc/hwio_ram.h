#ifndef __HWIO_RAM_H__
#define __HWIO_RAM_H__
/*
===========================================================================
*/
/**
  @file hwio_ram.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    SHARED_RAM.*
    SRM_CSR

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['SHARED_RAM.*', 'SRM_CSR'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_ram.h',
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
 * MODULE: SRM_CSR
 *--------------------------------------------------------------------------*/

#define SRM_CSR_REG_BASE                                           (SRM_CSR_BASE      + 0x00000000)
#define SRM_CSR_REG_BASE_SIZE                                      0x10000
#define SRM_CSR_REG_BASE_USED                                      0x120

#define HWIO_SRM_REGION_OWNER_MASTER_1_ADDR                        (SRM_CSR_REG_BASE      + 0x00000000)
#define HWIO_SRM_REGION_OWNER_MASTER_1_RMSK                            0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_MASTER_1_ADDR)
#define HWIO_SRM_REGION_OWNER_MASTER_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_MASTER_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_MASTER_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_MASTER_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_MASTER_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_MASTER_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_MASTER_1_IN)
#define HWIO_SRM_REGION_OWNER_MASTER_1_REGION_OWNER_BMSK               0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_1_REGION_OWNER_SHFT                  0x0

#define HWIO_SRM_REGION_OWNER_MASTER_2_ADDR                        (SRM_CSR_REG_BASE      + 0x00000004)
#define HWIO_SRM_REGION_OWNER_MASTER_2_RMSK                            0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_MASTER_2_ADDR)
#define HWIO_SRM_REGION_OWNER_MASTER_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_MASTER_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_MASTER_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_MASTER_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_MASTER_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_MASTER_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_MASTER_2_IN)
#define HWIO_SRM_REGION_OWNER_MASTER_2_REGION_OWNER_BMSK               0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_2_REGION_OWNER_SHFT                  0x0

#define HWIO_SRM_REGION_OWNER_MASTER_3_ADDR                        (SRM_CSR_REG_BASE      + 0x00000008)
#define HWIO_SRM_REGION_OWNER_MASTER_3_RMSK                            0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_MASTER_3_ADDR)
#define HWIO_SRM_REGION_OWNER_MASTER_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_MASTER_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_MASTER_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_MASTER_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_MASTER_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_MASTER_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_MASTER_3_IN)
#define HWIO_SRM_REGION_OWNER_MASTER_3_REGION_OWNER_BMSK               0xffff
#define HWIO_SRM_REGION_OWNER_MASTER_3_REGION_OWNER_SHFT                  0x0

#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_ADDR                        (SRM_CSR_REG_BASE      + 0x0000000c)
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_RMSK                               0x1
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_IN          \
        in_dword(HWIO_SRM_MASTER_0_LIMIT_ACCESS_ADDR)
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_INM(m)      \
        in_dword_masked(HWIO_SRM_MASTER_0_LIMIT_ACCESS_ADDR, m)
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_OUT(v)      \
        out_dword(HWIO_SRM_MASTER_0_LIMIT_ACCESS_ADDR,v)
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_MASTER_0_LIMIT_ACCESS_ADDR,m,v,HWIO_SRM_MASTER_0_LIMIT_ACCESS_IN)
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_ACCESS_LIMIT_BMSK                  0x1
#define HWIO_SRM_MASTER_0_LIMIT_ACCESS_ACCESS_LIMIT_SHFT                  0x0

#define HWIO_SRM_INTERRUPT_ENABLES_ADDR                            (SRM_CSR_REG_BASE      + 0x00000010)
#define HWIO_SRM_INTERRUPT_ENABLES_RMSK                                   0xf
#define HWIO_SRM_INTERRUPT_ENABLES_IN          \
        in_dword(HWIO_SRM_INTERRUPT_ENABLES_ADDR)
#define HWIO_SRM_INTERRUPT_ENABLES_INM(m)      \
        in_dword_masked(HWIO_SRM_INTERRUPT_ENABLES_ADDR, m)
#define HWIO_SRM_INTERRUPT_ENABLES_OUT(v)      \
        out_dword(HWIO_SRM_INTERRUPT_ENABLES_ADDR,v)
#define HWIO_SRM_INTERRUPT_ENABLES_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_INTERRUPT_ENABLES_ADDR,m,v,HWIO_SRM_INTERRUPT_ENABLES_IN)
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_3_BMSK                          0x8
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_3_SHFT                          0x3
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_2_BMSK                          0x4
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_2_SHFT                          0x2
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_1_BMSK                          0x2
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_1_SHFT                          0x1
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_0_BMSK                          0x1
#define HWIO_SRM_INTERRUPT_ENABLES_MASTER_0_SHFT                          0x0

#define HWIO_SRM_INTERRUPT_CLEAR_ADDR                              (SRM_CSR_REG_BASE      + 0x00000014)
#define HWIO_SRM_INTERRUPT_CLEAR_RMSK                                     0xf
#define HWIO_SRM_INTERRUPT_CLEAR_IN          \
        in_dword(HWIO_SRM_INTERRUPT_CLEAR_ADDR)
#define HWIO_SRM_INTERRUPT_CLEAR_INM(m)      \
        in_dword_masked(HWIO_SRM_INTERRUPT_CLEAR_ADDR, m)
#define HWIO_SRM_INTERRUPT_CLEAR_OUT(v)      \
        out_dword(HWIO_SRM_INTERRUPT_CLEAR_ADDR,v)
#define HWIO_SRM_INTERRUPT_CLEAR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_INTERRUPT_CLEAR_ADDR,m,v,HWIO_SRM_INTERRUPT_CLEAR_IN)
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_3_BMSK                            0x8
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_3_SHFT                            0x3
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_2_BMSK                            0x4
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_2_SHFT                            0x2
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_1_BMSK                            0x2
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_1_SHFT                            0x1
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_0_BMSK                            0x1
#define HWIO_SRM_INTERRUPT_CLEAR_MASTER_0_SHFT                            0x0

#define HWIO_SRM_INTERRUPT_STATUS_ADDR                             (SRM_CSR_REG_BASE      + 0x00000018)
#define HWIO_SRM_INTERRUPT_STATUS_RMSK                                   0xff
#define HWIO_SRM_INTERRUPT_STATUS_IN          \
        in_dword(HWIO_SRM_INTERRUPT_STATUS_ADDR)
#define HWIO_SRM_INTERRUPT_STATUS_INM(m)      \
        in_dword_masked(HWIO_SRM_INTERRUPT_STATUS_ADDR, m)
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_3_RAM_STATE_BMSK                0x80
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_3_RAM_STATE_SHFT                 0x7
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_2_RAM_STATE_BMSK                0x40
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_2_RAM_STATE_SHFT                 0x6
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_1_RAM_STATE_BMSK                0x20
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_1_RAM_STATE_SHFT                 0x5
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_0_RAM_STATE_BMSK                0x10
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_0_RAM_STATE_SHFT                 0x4
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_3_AD_BMSK                        0x8
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_3_AD_SHFT                        0x3
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_2_AD_BMSK                        0x4
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_2_AD_SHFT                        0x2
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_1_AD_BMSK                        0x2
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_1_AD_SHFT                        0x1
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_0_AD_BMSK                        0x1
#define HWIO_SRM_INTERRUPT_STATUS_MASTER_0_AD_SHFT                        0x0

#define HWIO_SRM_RAM_BANK_STATUS_ADDR                              (SRM_CSR_REG_BASE      + 0x0000001c)
#define HWIO_SRM_RAM_BANK_STATUS_RMSK                                  0xffff
#define HWIO_SRM_RAM_BANK_STATUS_IN          \
        in_dword(HWIO_SRM_RAM_BANK_STATUS_ADDR)
#define HWIO_SRM_RAM_BANK_STATUS_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_BANK_STATUS_ADDR, m)
#define HWIO_SRM_RAM_BANK_STATUS_BANK_STATE_BMSK                       0xffff
#define HWIO_SRM_RAM_BANK_STATUS_BANK_STATE_SHFT                          0x0

#define HWIO_SRM_REGION_OWNER_0_SHARE_1_ADDR                       (SRM_CSR_REG_BASE      + 0x00000020)
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_SHARE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_SHARE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_SHARE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_SHARE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_SHARE_1_IN)
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_1_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_0_SHARE_2_ADDR                       (SRM_CSR_REG_BASE      + 0x00000024)
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_SHARE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_SHARE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_SHARE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_SHARE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_SHARE_2_IN)
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_2_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_0_SHARE_3_ADDR                       (SRM_CSR_REG_BASE      + 0x00000028)
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_SHARE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_SHARE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_SHARE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_SHARE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_SHARE_3_IN)
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_0_SHARE_3_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR                       (SRM_CSR_REG_BASE      + 0x0000002c)
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_SHARE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_SHARE_0_IN)
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_0_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR                       (SRM_CSR_REG_BASE      + 0x00000030)
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_SHARE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_SHARE_2_IN)
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_2_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_1_SHARE_3_ADDR                       (SRM_CSR_REG_BASE      + 0x00000034)
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_SHARE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_SHARE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_SHARE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_SHARE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_SHARE_3_IN)
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_1_SHARE_3_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_2_SHARE_0_ADDR                       (SRM_CSR_REG_BASE      + 0x00000038)
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_SHARE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_SHARE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_SHARE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_SHARE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_SHARE_0_IN)
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_0_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_2_SHARE_1_ADDR                       (SRM_CSR_REG_BASE      + 0x0000003c)
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_SHARE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_SHARE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_SHARE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_SHARE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_SHARE_1_IN)
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_1_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_2_SHARE_3_ADDR                       (SRM_CSR_REG_BASE      + 0x00000040)
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_SHARE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_SHARE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_SHARE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_SHARE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_SHARE_3_IN)
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_2_SHARE_3_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_3_SHARE_0_ADDR                       (SRM_CSR_REG_BASE      + 0x00000044)
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_SHARE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_SHARE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_SHARE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_SHARE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_SHARE_0_IN)
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_0_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_3_SHARE_1_ADDR                       (SRM_CSR_REG_BASE      + 0x00000048)
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_SHARE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_SHARE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_SHARE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_SHARE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_SHARE_1_IN)
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_1_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_3_SHARE_2_ADDR                       (SRM_CSR_REG_BASE      + 0x0000004c)
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_RMSK                       0xffffffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_SHARE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_SHARE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_SHARE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_SHARE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_SHARE_2_IN)
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_WRITABLE_BMSK              0xffff0000
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_WRITABLE_SHFT                    0x10
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_SHAREABLE_BMSK                 0xffff
#define HWIO_SRM_REGION_OWNER_3_SHARE_2_SHAREABLE_SHFT                    0x0

#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_ADDR                     (SRM_CSR_REG_BASE      + 0x00000050)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_EXECUTE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_EXECUTE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_EXECUTE_1_IN)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_1_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_ADDR                     (SRM_CSR_REG_BASE      + 0x00000054)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_EXECUTE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_EXECUTE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_EXECUTE_2_IN)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_2_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_ADDR                     (SRM_CSR_REG_BASE      + 0x00000058)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_0_EXECUTE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_0_EXECUTE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_0_EXECUTE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_0_EXECUTE_3_IN)
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_0_EXECUTE_3_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_ADDR                     (SRM_CSR_REG_BASE      + 0x0000005c)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_EXECUTE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_EXECUTE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_EXECUTE_0_IN)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_0_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_ADDR                     (SRM_CSR_REG_BASE      + 0x00000060)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_EXECUTE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_EXECUTE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_EXECUTE_2_IN)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_2_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_ADDR                     (SRM_CSR_REG_BASE      + 0x00000064)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_1_EXECUTE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_1_EXECUTE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_1_EXECUTE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_1_EXECUTE_3_IN)
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_1_EXECUTE_3_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_ADDR                     (SRM_CSR_REG_BASE      + 0x00000068)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_EXECUTE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_EXECUTE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_EXECUTE_0_IN)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_0_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_ADDR                     (SRM_CSR_REG_BASE      + 0x0000006c)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_EXECUTE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_EXECUTE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_EXECUTE_1_IN)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_1_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_ADDR                     (SRM_CSR_REG_BASE      + 0x00000070)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_3_ADDR)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_2_EXECUTE_3_ADDR, m)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_2_EXECUTE_3_ADDR,v)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_2_EXECUTE_3_ADDR,m,v,HWIO_SRM_REGION_OWNER_2_EXECUTE_3_IN)
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_2_EXECUTE_3_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_ADDR                     (SRM_CSR_REG_BASE      + 0x00000074)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_0_ADDR)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_EXECUTE_0_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_0_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_EXECUTE_0_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_EXECUTE_0_IN)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_0_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_ADDR                     (SRM_CSR_REG_BASE      + 0x00000078)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_1_ADDR)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_EXECUTE_1_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_1_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_EXECUTE_1_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_EXECUTE_1_IN)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_1_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_ADDR                     (SRM_CSR_REG_BASE      + 0x0000007c)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_RMSK                         0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_IN          \
        in_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_2_ADDR)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_INM(m)      \
        in_dword_masked(HWIO_SRM_REGION_OWNER_3_EXECUTE_2_ADDR, m)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_OUT(v)      \
        out_dword(HWIO_SRM_REGION_OWNER_3_EXECUTE_2_ADDR,v)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_REGION_OWNER_3_EXECUTE_2_ADDR,m,v,HWIO_SRM_REGION_OWNER_3_EXECUTE_2_IN)
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_EXECUTABLE_BMSK              0xffff
#define HWIO_SRM_REGION_OWNER_3_EXECUTE_2_EXECUTABLE_SHFT                 0x0

#define HWIO_SRM_OWNER_0_SUB_SHARE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000080)
#define HWIO_SRM_OWNER_0_SUB_SHARE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_0_SUB_SHARE_IN          \
        in_dword(HWIO_SRM_OWNER_0_SUB_SHARE_ADDR)
#define HWIO_SRM_OWNER_0_SUB_SHARE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_0_SUB_SHARE_ADDR, m)
#define HWIO_SRM_OWNER_0_SUB_SHARE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_0_SUB_SHARE_ADDR,v)
#define HWIO_SRM_OWNER_0_SUB_SHARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_0_SUB_SHARE_ADDR,m,v,HWIO_SRM_OWNER_0_SUB_SHARE_IN)
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_2_BMSK                 0xff00
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_2_SHFT                    0x8
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_1_BMSK                   0xff
#define HWIO_SRM_OWNER_0_SUB_SHARE_SHARE_MASTER_1_SHFT                    0x0

#define HWIO_SRM_OWNER_0_SUB_WRITE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000084)
#define HWIO_SRM_OWNER_0_SUB_WRITE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_0_SUB_WRITE_IN          \
        in_dword(HWIO_SRM_OWNER_0_SUB_WRITE_ADDR)
#define HWIO_SRM_OWNER_0_SUB_WRITE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_0_SUB_WRITE_ADDR, m)
#define HWIO_SRM_OWNER_0_SUB_WRITE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_0_SUB_WRITE_ADDR,v)
#define HWIO_SRM_OWNER_0_SUB_WRITE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_0_SUB_WRITE_ADDR,m,v,HWIO_SRM_OWNER_0_SUB_WRITE_IN)
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_2_BMSK                 0xff00
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_2_SHFT                    0x8
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_1_BMSK                   0xff
#define HWIO_SRM_OWNER_0_SUB_WRITE_WRITE_MASTER_1_SHFT                    0x0

#define HWIO_SRM_OWNER_1_SUB_SHARE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000088)
#define HWIO_SRM_OWNER_1_SUB_SHARE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_1_SUB_SHARE_IN          \
        in_dword(HWIO_SRM_OWNER_1_SUB_SHARE_ADDR)
#define HWIO_SRM_OWNER_1_SUB_SHARE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_1_SUB_SHARE_ADDR, m)
#define HWIO_SRM_OWNER_1_SUB_SHARE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_1_SUB_SHARE_ADDR,v)
#define HWIO_SRM_OWNER_1_SUB_SHARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_1_SUB_SHARE_ADDR,m,v,HWIO_SRM_OWNER_1_SUB_SHARE_IN)
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_2_BMSK                 0xff00
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_2_SHFT                    0x8
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_1_SUB_SHARE_SHARE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_OWNER_1_SUB_WRITE_ADDR                            (SRM_CSR_REG_BASE      + 0x0000008c)
#define HWIO_SRM_OWNER_1_SUB_WRITE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_1_SUB_WRITE_IN          \
        in_dword(HWIO_SRM_OWNER_1_SUB_WRITE_ADDR)
#define HWIO_SRM_OWNER_1_SUB_WRITE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_1_SUB_WRITE_ADDR, m)
#define HWIO_SRM_OWNER_1_SUB_WRITE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_1_SUB_WRITE_ADDR,v)
#define HWIO_SRM_OWNER_1_SUB_WRITE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_1_SUB_WRITE_ADDR,m,v,HWIO_SRM_OWNER_1_SUB_WRITE_IN)
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_2_BMSK                 0xff00
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_2_SHFT                    0x8
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_1_SUB_WRITE_WRITE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_OWNER_2_SUB_SHARE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000090)
#define HWIO_SRM_OWNER_2_SUB_SHARE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_2_SUB_SHARE_IN          \
        in_dword(HWIO_SRM_OWNER_2_SUB_SHARE_ADDR)
#define HWIO_SRM_OWNER_2_SUB_SHARE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_2_SUB_SHARE_ADDR, m)
#define HWIO_SRM_OWNER_2_SUB_SHARE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_2_SUB_SHARE_ADDR,v)
#define HWIO_SRM_OWNER_2_SUB_SHARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_2_SUB_SHARE_ADDR,m,v,HWIO_SRM_OWNER_2_SUB_SHARE_IN)
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_1_BMSK                 0xff00
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_1_SHFT                    0x8
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_2_SUB_SHARE_SHARE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_OWNER_2_SUB_WRITE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000094)
#define HWIO_SRM_OWNER_2_SUB_WRITE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_2_SUB_WRITE_IN          \
        in_dword(HWIO_SRM_OWNER_2_SUB_WRITE_ADDR)
#define HWIO_SRM_OWNER_2_SUB_WRITE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_2_SUB_WRITE_ADDR, m)
#define HWIO_SRM_OWNER_2_SUB_WRITE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_2_SUB_WRITE_ADDR,v)
#define HWIO_SRM_OWNER_2_SUB_WRITE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_2_SUB_WRITE_ADDR,m,v,HWIO_SRM_OWNER_2_SUB_WRITE_IN)
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_3_BMSK               0xff0000
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_3_SHFT                   0x10
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_1_BMSK                 0xff00
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_1_SHFT                    0x8
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_2_SUB_WRITE_WRITE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_OWNER_3_SUB_SHARE_ADDR                            (SRM_CSR_REG_BASE      + 0x00000098)
#define HWIO_SRM_OWNER_3_SUB_SHARE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_3_SUB_SHARE_IN          \
        in_dword(HWIO_SRM_OWNER_3_SUB_SHARE_ADDR)
#define HWIO_SRM_OWNER_3_SUB_SHARE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_3_SUB_SHARE_ADDR, m)
#define HWIO_SRM_OWNER_3_SUB_SHARE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_3_SUB_SHARE_ADDR,v)
#define HWIO_SRM_OWNER_3_SUB_SHARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_3_SUB_SHARE_ADDR,m,v,HWIO_SRM_OWNER_3_SUB_SHARE_IN)
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_2_BMSK               0xff0000
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_2_SHFT                   0x10
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_1_BMSK                 0xff00
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_1_SHFT                    0x8
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_3_SUB_SHARE_SHARE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_OWNER_3_SUB_WRITE_ADDR                            (SRM_CSR_REG_BASE      + 0x0000009c)
#define HWIO_SRM_OWNER_3_SUB_WRITE_RMSK                              0xffffff
#define HWIO_SRM_OWNER_3_SUB_WRITE_IN          \
        in_dword(HWIO_SRM_OWNER_3_SUB_WRITE_ADDR)
#define HWIO_SRM_OWNER_3_SUB_WRITE_INM(m)      \
        in_dword_masked(HWIO_SRM_OWNER_3_SUB_WRITE_ADDR, m)
#define HWIO_SRM_OWNER_3_SUB_WRITE_OUT(v)      \
        out_dword(HWIO_SRM_OWNER_3_SUB_WRITE_ADDR,v)
#define HWIO_SRM_OWNER_3_SUB_WRITE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_OWNER_3_SUB_WRITE_ADDR,m,v,HWIO_SRM_OWNER_3_SUB_WRITE_IN)
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_2_BMSK               0xff0000
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_2_SHFT                   0x10
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_1_BMSK                 0xff00
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_1_SHFT                    0x8
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_0_BMSK                   0xff
#define HWIO_SRM_OWNER_3_SUB_WRITE_WRITE_MASTER_0_SHFT                    0x0

#define HWIO_SRM_RAM_MASK_RGN0_CTRL_ADDR                           (SRM_CSR_REG_BASE      + 0x000000a0)
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RMSK                               0xffff
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN0_CTRL_ADDR)
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN0_CTRL_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN0_CTRL_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN0_CTRL_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN0_CTRL_IN)
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET7_EN_BMSK               0x8000
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET7_EN_SHFT                  0xf
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET6_EN_BMSK               0x4000
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET6_EN_SHFT                  0xe
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET5_EN_BMSK               0x2000
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET5_EN_SHFT                  0xd
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET4_EN_BMSK               0x1000
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET4_EN_SHFT                  0xc
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET3_EN_BMSK                0x800
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET3_EN_SHFT                  0xb
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET2_EN_BMSK                0x400
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET2_EN_SHFT                  0xa
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET1_EN_BMSK                0x200
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET1_EN_SHFT                  0x9
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET0_EN_BMSK                0x100
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_RD_DET0_EN_SHFT                  0x8
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK7_EN_BMSK                0x80
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK7_EN_SHFT                 0x7
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK6_EN_BMSK                0x40
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK6_EN_SHFT                 0x6
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK5_EN_BMSK                0x20
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK5_EN_SHFT                 0x5
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK4_EN_BMSK                0x10
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK4_EN_SHFT                 0x4
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK3_EN_BMSK                 0x8
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK3_EN_SHFT                 0x3
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK2_EN_BMSK                 0x4
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK2_EN_SHFT                 0x2
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK1_EN_BMSK                 0x2
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK1_EN_SHFT                 0x1
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK0_EN_BMSK                 0x1
#define HWIO_SRM_RAM_MASK_RGN0_CTRL_RGN0_WR_MASK0_EN_SHFT                 0x0

#define HWIO_SRM_RAM_MASK_RGN1_CTRL_ADDR                           (SRM_CSR_REG_BASE      + 0x000000a4)
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RMSK                                 0x3f
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_CTRL_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_CTRL_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_CTRL_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_CTRL_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_CTRL_IN)
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET2_EN_BMSK                 0x20
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET2_EN_SHFT                  0x5
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET1_EN_BMSK                 0x10
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET1_EN_SHFT                  0x4
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET0_EN_BMSK                  0x8
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_RD_DET0_EN_SHFT                  0x3
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK2_EN_BMSK                 0x4
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK2_EN_SHFT                 0x2
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK1_EN_BMSK                 0x2
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK1_EN_SHFT                 0x1
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK0_EN_BMSK                 0x1
#define HWIO_SRM_RAM_MASK_RGN1_CTRL_RGN1_WR_MASK0_EN_SHFT                 0x0

#define HWIO_SRM_RAM_MASK_STAT0_ADDR                               (SRM_CSR_REG_BASE      + 0x000000a8)
#define HWIO_SRM_RAM_MASK_STAT0_RMSK                                      0x3
#define HWIO_SRM_RAM_MASK_STAT0_IN          \
        in_dword(HWIO_SRM_RAM_MASK_STAT0_ADDR)
#define HWIO_SRM_RAM_MASK_STAT0_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_STAT0_ADDR, m)
#define HWIO_SRM_RAM_MASK_STAT0_RGN0_RD_ACCS_BMSK                         0x2
#define HWIO_SRM_RAM_MASK_STAT0_RGN0_RD_ACCS_SHFT                         0x1
#define HWIO_SRM_RAM_MASK_STAT0_RGN0_WR_ACCS_BMSK                         0x1
#define HWIO_SRM_RAM_MASK_STAT0_RGN0_WR_ACCS_SHFT                         0x0

#define HWIO_SRM_RAM_MASK_STAT1_ADDR                               (SRM_CSR_REG_BASE      + 0x000000ac)
#define HWIO_SRM_RAM_MASK_STAT1_RMSK                                      0x3
#define HWIO_SRM_RAM_MASK_STAT1_IN          \
        in_dword(HWIO_SRM_RAM_MASK_STAT1_ADDR)
#define HWIO_SRM_RAM_MASK_STAT1_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_STAT1_ADDR, m)
#define HWIO_SRM_RAM_MASK_STAT1_RGN1_RD_ACCS_BMSK                         0x2
#define HWIO_SRM_RAM_MASK_STAT1_RGN1_RD_ACCS_SHFT                         0x1
#define HWIO_SRM_RAM_MASK_STAT1_RGN1_WR_ACCS_BMSK                         0x1
#define HWIO_SRM_RAM_MASK_STAT1_RGN1_WR_ACCS_SHFT                         0x0

#define HWIO_SRM_RAM_MASK_STAT0_CLR_ADDR                           (SRM_CSR_REG_BASE      + 0x000000b0)
#define HWIO_SRM_RAM_MASK_STAT0_CLR_RMSK                                  0x1
#define HWIO_SRM_RAM_MASK_STAT0_CLR_IN          \
        in_dword(HWIO_SRM_RAM_MASK_STAT0_CLR_ADDR)
#define HWIO_SRM_RAM_MASK_STAT0_CLR_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_STAT0_CLR_ADDR, m)
#define HWIO_SRM_RAM_MASK_STAT0_CLR_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_STAT0_CLR_ADDR,v)
#define HWIO_SRM_RAM_MASK_STAT0_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_STAT0_CLR_ADDR,m,v,HWIO_SRM_RAM_MASK_STAT0_CLR_IN)
#define HWIO_SRM_RAM_MASK_STAT0_CLR_EN_BMSK                               0x1
#define HWIO_SRM_RAM_MASK_STAT0_CLR_EN_SHFT                               0x0

#define HWIO_SRM_RAM_MASK_STAT1_CLR_ADDR                           (SRM_CSR_REG_BASE      + 0x000000b4)
#define HWIO_SRM_RAM_MASK_STAT1_CLR_RMSK                                  0x1
#define HWIO_SRM_RAM_MASK_STAT1_CLR_IN          \
        in_dword(HWIO_SRM_RAM_MASK_STAT1_CLR_ADDR)
#define HWIO_SRM_RAM_MASK_STAT1_CLR_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_STAT1_CLR_ADDR, m)
#define HWIO_SRM_RAM_MASK_STAT1_CLR_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_STAT1_CLR_ADDR,v)
#define HWIO_SRM_RAM_MASK_STAT1_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_STAT1_CLR_ADDR,m,v,HWIO_SRM_RAM_MASK_STAT1_CLR_IN)
#define HWIO_SRM_RAM_MASK_STAT1_CLR_EN_BMSK                               0x1
#define HWIO_SRM_RAM_MASK_STAT1_CLR_EN_SHFT                               0x0

#define HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000b8)
#define HWIO_SRM_RAM_MASK_RGN07_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN07_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN07_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN07_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN07_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN07_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN07_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000bc)
#define HWIO_SRM_RAM_MASK_RGN06_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN06_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN06_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN06_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN06_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN06_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN06_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000c0)
#define HWIO_SRM_RAM_MASK_RGN05_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN05_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN05_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN05_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN05_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN05_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN05_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000c4)
#define HWIO_SRM_RAM_MASK_RGN04_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN04_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN04_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN04_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN04_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN04_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN04_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000c8)
#define HWIO_SRM_RAM_MASK_RGN03_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN03_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN03_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN03_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN03_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN03_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN03_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000cc)
#define HWIO_SRM_RAM_MASK_RGN02_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN02_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN02_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN02_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN02_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN02_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN02_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000d0)
#define HWIO_SRM_RAM_MASK_RGN01_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN01_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN01_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN01_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN01_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN01_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN01_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000d4)
#define HWIO_SRM_RAM_MASK_RGN00_BASE_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN00_BASE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN00_BASE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN00_BASE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN00_BASE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN00_BASE_IN)
#define HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN00_BASE_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN07_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000d8)
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN07_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN07_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN07_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN07_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN07_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN07_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN06_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000dc)
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN06_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN06_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN06_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN06_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN06_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN06_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN05_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000e0)
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN05_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN05_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN05_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN05_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN05_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN05_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN04_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000e4)
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN04_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN04_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN04_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN04_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN04_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN04_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN03_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000e8)
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN03_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN03_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN03_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN03_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN03_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN03_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN02_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000ec)
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN02_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN02_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN02_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN02_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN02_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN02_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN01_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000f0)
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN01_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN01_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN01_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN01_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN01_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN01_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN00_BYTE_ADDR                          (SRM_CSR_REG_BASE      + 0x000000f4)
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_RMSK                                 0xf
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN00_BYTE_ADDR)
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN00_BYTE_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN00_BYTE_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN00_BYTE_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN00_BYTE_IN)
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_MASK_BMSK                            0xf
#define HWIO_SRM_RAM_MASK_RGN00_BYTE_MASK_SHFT                            0x0

#define HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR                          (SRM_CSR_REG_BASE      + 0x000000f8)
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_BASE2_IN)
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE2_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR                          (SRM_CSR_REG_BASE      + 0x000000fc)
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_BASE1_IN)
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE1_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR                          (SRM_CSR_REG_BASE      + 0x00000100)
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_BASE0_IN)
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_BASE0_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR                          (SRM_CSR_REG_BASE      + 0x00000104)
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_LAST2_IN)
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST2_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR                          (SRM_CSR_REG_BASE      + 0x00000108)
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_LAST1_IN)
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST1_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR                          (SRM_CSR_REG_BASE      + 0x0000010c)
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_RMSK                             0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR,v)
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR,m,v,HWIO_SRM_RAM_MASK_RGN1_LAST0_IN)
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR_BMSK                        0x1fffc
#define HWIO_SRM_RAM_MASK_RGN1_LAST0_ADDR_SHFT                            0x2

#define HWIO_SRM_RAM_MASK_RGN0_AHB_ADDR                            (SRM_CSR_REG_BASE      + 0x00000110)
#define HWIO_SRM_RAM_MASK_RGN0_AHB_RMSK                              0x1fffff
#define HWIO_SRM_RAM_MASK_RGN0_AHB_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN0_AHB_ADDR)
#define HWIO_SRM_RAM_MASK_RGN0_AHB_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN0_AHB_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN0_AHB_ACCS_ADDR_BMSK                    0x1fffff
#define HWIO_SRM_RAM_MASK_RGN0_AHB_ACCS_ADDR_SHFT                         0x0

#define HWIO_SRM_RAM_MASK_RGN1_AHB_ADDR                            (SRM_CSR_REG_BASE      + 0x00000114)
#define HWIO_SRM_RAM_MASK_RGN1_AHB_RMSK                              0x1fffff
#define HWIO_SRM_RAM_MASK_RGN1_AHB_IN          \
        in_dword(HWIO_SRM_RAM_MASK_RGN1_AHB_ADDR)
#define HWIO_SRM_RAM_MASK_RGN1_AHB_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_RGN1_AHB_ADDR, m)
#define HWIO_SRM_RAM_MASK_RGN1_AHB_ACCS_ADDR_BMSK                    0x1fffff
#define HWIO_SRM_RAM_MASK_RGN1_AHB_ACCS_ADDR_SHFT                         0x0

#define HWIO_SRM_RAM_MASK_AHB_CLR_ADDR                             (SRM_CSR_REG_BASE      + 0x00000118)
#define HWIO_SRM_RAM_MASK_AHB_CLR_RMSK                                    0x1
#define HWIO_SRM_RAM_MASK_AHB_CLR_IN          \
        in_dword(HWIO_SRM_RAM_MASK_AHB_CLR_ADDR)
#define HWIO_SRM_RAM_MASK_AHB_CLR_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_MASK_AHB_CLR_ADDR, m)
#define HWIO_SRM_RAM_MASK_AHB_CLR_OUT(v)      \
        out_dword(HWIO_SRM_RAM_MASK_AHB_CLR_ADDR,v)
#define HWIO_SRM_RAM_MASK_AHB_CLR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_MASK_AHB_CLR_ADDR,m,v,HWIO_SRM_RAM_MASK_AHB_CLR_IN)
#define HWIO_SRM_RAM_MASK_AHB_CLR_EN_BMSK                                 0x1
#define HWIO_SRM_RAM_MASK_AHB_CLR_EN_SHFT                                 0x0

#define HWIO_SRM_RAM_EMA_SETTINGS_ADDR                             (SRM_CSR_REG_BASE      + 0x0000011c)
#define HWIO_SRM_RAM_EMA_SETTINGS_RMSK                                  0x3ff
#define HWIO_SRM_RAM_EMA_SETTINGS_IN          \
        in_dword(HWIO_SRM_RAM_EMA_SETTINGS_ADDR)
#define HWIO_SRM_RAM_EMA_SETTINGS_INM(m)      \
        in_dword_masked(HWIO_SRM_RAM_EMA_SETTINGS_ADDR, m)
#define HWIO_SRM_RAM_EMA_SETTINGS_OUT(v)      \
        out_dword(HWIO_SRM_RAM_EMA_SETTINGS_ADDR,v)
#define HWIO_SRM_RAM_EMA_SETTINGS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_RAM_EMA_SETTINGS_ADDR,m,v,HWIO_SRM_RAM_EMA_SETTINGS_IN)
#define HWIO_SRM_RAM_EMA_SETTINGS_EMAW_RETENTION_BMSK                   0x300
#define HWIO_SRM_RAM_EMA_SETTINGS_EMAW_RETENTION_SHFT                     0x8
#define HWIO_SRM_RAM_EMA_SETTINGS_EMA_RETENTION_BMSK                     0xe0
#define HWIO_SRM_RAM_EMA_SETTINGS_EMA_RETENTION_SHFT                      0x5
#define HWIO_SRM_RAM_EMA_SETTINGS_EMAW_NORMAL_BMSK                       0x18
#define HWIO_SRM_RAM_EMA_SETTINGS_EMAW_NORMAL_SHFT                        0x3
#define HWIO_SRM_RAM_EMA_SETTINGS_EMA_NORMAL_BMSK                         0x7
#define HWIO_SRM_RAM_EMA_SETTINGS_EMA_NORMAL_SHFT                         0x0

#define HWIO_SRM_DBG_SEL_ADDR                                      (SRM_CSR_REG_BASE      + 0x00000120)
#define HWIO_SRM_DBG_SEL_RMSK                                            0x1f
#define HWIO_SRM_DBG_SEL_IN          \
        in_dword(HWIO_SRM_DBG_SEL_ADDR)
#define HWIO_SRM_DBG_SEL_INM(m)      \
        in_dword_masked(HWIO_SRM_DBG_SEL_ADDR, m)
#define HWIO_SRM_DBG_SEL_OUT(v)      \
        out_dword(HWIO_SRM_DBG_SEL_ADDR,v)
#define HWIO_SRM_DBG_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SRM_DBG_SEL_ADDR,m,v,HWIO_SRM_DBG_SEL_IN)
#define HWIO_SRM_DBG_SEL_SEL_BMSK                                        0x1f
#define HWIO_SRM_DBG_SEL_SEL_SHFT                                         0x0


#endif /* __HWIO_RAM_H__ */
