#ifndef __HWIO_NVM_H__
#define __HWIO_NVM_H__
/*
===========================================================================
*/
/**
  @file hwio_nvm.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    NVM.*

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['NVM.*'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_nvm.h',
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
 * MODULE: NVM
 *--------------------------------------------------------------------------*/

#define NVM_REG_BASE                                          (NVM_BASE      + 0x00000000)
#define NVM_REG_BASE_SIZE                                     0x1000
#define NVM_REG_BASE_USED                                     0x828

#define HWIO_ACCESS_0_ADDR                                    (NVM_REG_BASE      + 0x00000000)
#define HWIO_ACCESS_0_RMSK                                      0x373737
#define HWIO_ACCESS_0_IN          \
        in_dword(HWIO_ACCESS_0_ADDR)
#define HWIO_ACCESS_0_INM(m)      \
        in_dword_masked(HWIO_ACCESS_0_ADDR, m)
#define HWIO_ACCESS_0_OUT(v)      \
        out_dword(HWIO_ACCESS_0_ADDR,v)
#define HWIO_ACCESS_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_0_ADDR,m,v,HWIO_ACCESS_0_IN)
#define HWIO_ACCESS_0_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_0_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_0_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_0_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_0_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_0_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_0_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_0_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_0_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_0_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_0_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_0_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_1_ADDR                                    (NVM_REG_BASE      + 0x00000004)
#define HWIO_ACCESS_1_RMSK                                      0x373737
#define HWIO_ACCESS_1_IN          \
        in_dword(HWIO_ACCESS_1_ADDR)
#define HWIO_ACCESS_1_INM(m)      \
        in_dword_masked(HWIO_ACCESS_1_ADDR, m)
#define HWIO_ACCESS_1_OUT(v)      \
        out_dword(HWIO_ACCESS_1_ADDR,v)
#define HWIO_ACCESS_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_1_ADDR,m,v,HWIO_ACCESS_1_IN)
#define HWIO_ACCESS_1_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_1_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_1_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_1_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_1_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_1_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_1_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_1_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_1_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_1_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_1_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_1_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_2_ADDR                                    (NVM_REG_BASE      + 0x00000008)
#define HWIO_ACCESS_2_RMSK                                      0x373737
#define HWIO_ACCESS_2_IN          \
        in_dword(HWIO_ACCESS_2_ADDR)
#define HWIO_ACCESS_2_INM(m)      \
        in_dword_masked(HWIO_ACCESS_2_ADDR, m)
#define HWIO_ACCESS_2_OUT(v)      \
        out_dword(HWIO_ACCESS_2_ADDR,v)
#define HWIO_ACCESS_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_2_ADDR,m,v,HWIO_ACCESS_2_IN)
#define HWIO_ACCESS_2_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_2_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_2_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_2_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_2_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_2_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_2_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_2_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_2_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_2_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_2_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_2_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_3_ADDR                                    (NVM_REG_BASE      + 0x0000000c)
#define HWIO_ACCESS_3_RMSK                                      0x373737
#define HWIO_ACCESS_3_IN          \
        in_dword(HWIO_ACCESS_3_ADDR)
#define HWIO_ACCESS_3_INM(m)      \
        in_dword_masked(HWIO_ACCESS_3_ADDR, m)
#define HWIO_ACCESS_3_OUT(v)      \
        out_dword(HWIO_ACCESS_3_ADDR,v)
#define HWIO_ACCESS_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_3_ADDR,m,v,HWIO_ACCESS_3_IN)
#define HWIO_ACCESS_3_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_3_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_3_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_3_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_3_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_3_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_3_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_3_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_3_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_3_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_3_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_3_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_4_ADDR                                    (NVM_REG_BASE      + 0x00000010)
#define HWIO_ACCESS_4_RMSK                                      0x373737
#define HWIO_ACCESS_4_IN          \
        in_dword(HWIO_ACCESS_4_ADDR)
#define HWIO_ACCESS_4_INM(m)      \
        in_dword_masked(HWIO_ACCESS_4_ADDR, m)
#define HWIO_ACCESS_4_OUT(v)      \
        out_dword(HWIO_ACCESS_4_ADDR,v)
#define HWIO_ACCESS_4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_4_ADDR,m,v,HWIO_ACCESS_4_IN)
#define HWIO_ACCESS_4_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_4_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_4_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_4_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_4_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_4_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_4_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_4_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_4_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_4_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_4_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_4_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_5_ADDR                                    (NVM_REG_BASE      + 0x00000014)
#define HWIO_ACCESS_5_RMSK                                      0x373737
#define HWIO_ACCESS_5_IN          \
        in_dword(HWIO_ACCESS_5_ADDR)
#define HWIO_ACCESS_5_INM(m)      \
        in_dword_masked(HWIO_ACCESS_5_ADDR, m)
#define HWIO_ACCESS_5_OUT(v)      \
        out_dword(HWIO_ACCESS_5_ADDR,v)
#define HWIO_ACCESS_5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_5_ADDR,m,v,HWIO_ACCESS_5_IN)
#define HWIO_ACCESS_5_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_5_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_5_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_5_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_5_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_5_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_5_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_5_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_5_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_5_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_5_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_5_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_6_ADDR                                    (NVM_REG_BASE      + 0x00000018)
#define HWIO_ACCESS_6_RMSK                                      0x373737
#define HWIO_ACCESS_6_IN          \
        in_dword(HWIO_ACCESS_6_ADDR)
#define HWIO_ACCESS_6_INM(m)      \
        in_dword_masked(HWIO_ACCESS_6_ADDR, m)
#define HWIO_ACCESS_6_OUT(v)      \
        out_dword(HWIO_ACCESS_6_ADDR,v)
#define HWIO_ACCESS_6_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_6_ADDR,m,v,HWIO_ACCESS_6_IN)
#define HWIO_ACCESS_6_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_6_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_6_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_6_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_6_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_6_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_6_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_6_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_6_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_6_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_6_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_6_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_7_ADDR                                    (NVM_REG_BASE      + 0x0000001c)
#define HWIO_ACCESS_7_RMSK                                      0x373737
#define HWIO_ACCESS_7_IN          \
        in_dword(HWIO_ACCESS_7_ADDR)
#define HWIO_ACCESS_7_INM(m)      \
        in_dword_masked(HWIO_ACCESS_7_ADDR, m)
#define HWIO_ACCESS_7_OUT(v)      \
        out_dword(HWIO_ACCESS_7_ADDR,v)
#define HWIO_ACCESS_7_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_7_ADDR,m,v,HWIO_ACCESS_7_IN)
#define HWIO_ACCESS_7_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_7_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_7_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_7_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_7_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_7_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_7_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_7_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_7_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_7_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_7_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_7_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_8_ADDR                                    (NVM_REG_BASE      + 0x00000020)
#define HWIO_ACCESS_8_RMSK                                      0x373737
#define HWIO_ACCESS_8_IN          \
        in_dword(HWIO_ACCESS_8_ADDR)
#define HWIO_ACCESS_8_INM(m)      \
        in_dword_masked(HWIO_ACCESS_8_ADDR, m)
#define HWIO_ACCESS_8_OUT(v)      \
        out_dword(HWIO_ACCESS_8_ADDR,v)
#define HWIO_ACCESS_8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_8_ADDR,m,v,HWIO_ACCESS_8_IN)
#define HWIO_ACCESS_8_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_8_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_8_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_8_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_8_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_8_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_8_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_8_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_8_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_8_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_8_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_8_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_9_ADDR                                    (NVM_REG_BASE      + 0x00000024)
#define HWIO_ACCESS_9_RMSK                                      0x373737
#define HWIO_ACCESS_9_IN          \
        in_dword(HWIO_ACCESS_9_ADDR)
#define HWIO_ACCESS_9_INM(m)      \
        in_dword_masked(HWIO_ACCESS_9_ADDR, m)
#define HWIO_ACCESS_9_OUT(v)      \
        out_dword(HWIO_ACCESS_9_ADDR,v)
#define HWIO_ACCESS_9_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_9_ADDR,m,v,HWIO_ACCESS_9_IN)
#define HWIO_ACCESS_9_ID_2_BMSK                                 0x300000
#define HWIO_ACCESS_9_ID_2_SHFT                                     0x14
#define HWIO_ACCESS_9_RWX_2_BMSK                                 0x70000
#define HWIO_ACCESS_9_RWX_2_SHFT                                    0x10
#define HWIO_ACCESS_9_ID_1_BMSK                                   0x3000
#define HWIO_ACCESS_9_ID_1_SHFT                                      0xc
#define HWIO_ACCESS_9_RWX_1_BMSK                                   0x700
#define HWIO_ACCESS_9_RWX_1_SHFT                                     0x8
#define HWIO_ACCESS_9_ID_0_BMSK                                     0x30
#define HWIO_ACCESS_9_ID_0_SHFT                                      0x4
#define HWIO_ACCESS_9_RWX_0_BMSK                                     0x7
#define HWIO_ACCESS_9_RWX_0_SHFT                                     0x0

#define HWIO_ACCESS_10_ADDR                                   (NVM_REG_BASE      + 0x00000028)
#define HWIO_ACCESS_10_RMSK                                     0x373737
#define HWIO_ACCESS_10_IN          \
        in_dword(HWIO_ACCESS_10_ADDR)
#define HWIO_ACCESS_10_INM(m)      \
        in_dword_masked(HWIO_ACCESS_10_ADDR, m)
#define HWIO_ACCESS_10_OUT(v)      \
        out_dword(HWIO_ACCESS_10_ADDR,v)
#define HWIO_ACCESS_10_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_10_ADDR,m,v,HWIO_ACCESS_10_IN)
#define HWIO_ACCESS_10_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_10_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_10_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_10_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_10_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_10_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_10_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_10_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_10_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_10_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_10_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_10_RWX_0_SHFT                                    0x0

#define HWIO_ACCESS_11_ADDR                                   (NVM_REG_BASE      + 0x0000002c)
#define HWIO_ACCESS_11_RMSK                                     0x373737
#define HWIO_ACCESS_11_IN          \
        in_dword(HWIO_ACCESS_11_ADDR)
#define HWIO_ACCESS_11_INM(m)      \
        in_dword_masked(HWIO_ACCESS_11_ADDR, m)
#define HWIO_ACCESS_11_OUT(v)      \
        out_dword(HWIO_ACCESS_11_ADDR,v)
#define HWIO_ACCESS_11_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_11_ADDR,m,v,HWIO_ACCESS_11_IN)
#define HWIO_ACCESS_11_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_11_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_11_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_11_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_11_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_11_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_11_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_11_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_11_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_11_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_11_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_11_RWX_0_SHFT                                    0x0

#define HWIO_ACCESS_12_ADDR                                   (NVM_REG_BASE      + 0x00000030)
#define HWIO_ACCESS_12_RMSK                                     0x373737
#define HWIO_ACCESS_12_IN          \
        in_dword(HWIO_ACCESS_12_ADDR)
#define HWIO_ACCESS_12_INM(m)      \
        in_dword_masked(HWIO_ACCESS_12_ADDR, m)
#define HWIO_ACCESS_12_OUT(v)      \
        out_dword(HWIO_ACCESS_12_ADDR,v)
#define HWIO_ACCESS_12_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_12_ADDR,m,v,HWIO_ACCESS_12_IN)
#define HWIO_ACCESS_12_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_12_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_12_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_12_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_12_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_12_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_12_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_12_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_12_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_12_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_12_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_12_RWX_0_SHFT                                    0x0

#define HWIO_ACCESS_13_ADDR                                   (NVM_REG_BASE      + 0x00000034)
#define HWIO_ACCESS_13_RMSK                                     0x373737
#define HWIO_ACCESS_13_IN          \
        in_dword(HWIO_ACCESS_13_ADDR)
#define HWIO_ACCESS_13_INM(m)      \
        in_dword_masked(HWIO_ACCESS_13_ADDR, m)
#define HWIO_ACCESS_13_OUT(v)      \
        out_dword(HWIO_ACCESS_13_ADDR,v)
#define HWIO_ACCESS_13_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_13_ADDR,m,v,HWIO_ACCESS_13_IN)
#define HWIO_ACCESS_13_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_13_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_13_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_13_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_13_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_13_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_13_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_13_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_13_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_13_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_13_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_13_RWX_0_SHFT                                    0x0

#define HWIO_ACCESS_14_ADDR                                   (NVM_REG_BASE      + 0x00000038)
#define HWIO_ACCESS_14_RMSK                                     0x373737
#define HWIO_ACCESS_14_IN          \
        in_dword(HWIO_ACCESS_14_ADDR)
#define HWIO_ACCESS_14_INM(m)      \
        in_dword_masked(HWIO_ACCESS_14_ADDR, m)
#define HWIO_ACCESS_14_OUT(v)      \
        out_dword(HWIO_ACCESS_14_ADDR,v)
#define HWIO_ACCESS_14_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_14_ADDR,m,v,HWIO_ACCESS_14_IN)
#define HWIO_ACCESS_14_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_14_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_14_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_14_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_14_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_14_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_14_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_14_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_14_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_14_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_14_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_14_RWX_0_SHFT                                    0x0

#define HWIO_ACCESS_15_ADDR                                   (NVM_REG_BASE      + 0x0000003c)
#define HWIO_ACCESS_15_RMSK                                     0x373737
#define HWIO_ACCESS_15_IN          \
        in_dword(HWIO_ACCESS_15_ADDR)
#define HWIO_ACCESS_15_INM(m)      \
        in_dword_masked(HWIO_ACCESS_15_ADDR, m)
#define HWIO_ACCESS_15_OUT(v)      \
        out_dword(HWIO_ACCESS_15_ADDR,v)
#define HWIO_ACCESS_15_OUTM(m,v) \
        out_dword_masked_ns(HWIO_ACCESS_15_ADDR,m,v,HWIO_ACCESS_15_IN)
#define HWIO_ACCESS_15_ID_2_BMSK                                0x300000
#define HWIO_ACCESS_15_ID_2_SHFT                                    0x14
#define HWIO_ACCESS_15_RWX_2_BMSK                                0x70000
#define HWIO_ACCESS_15_RWX_2_SHFT                                   0x10
#define HWIO_ACCESS_15_ID_1_BMSK                                  0x3000
#define HWIO_ACCESS_15_ID_1_SHFT                                     0xc
#define HWIO_ACCESS_15_RWX_1_BMSK                                  0x700
#define HWIO_ACCESS_15_RWX_1_SHFT                                    0x8
#define HWIO_ACCESS_15_ID_0_BMSK                                    0x30
#define HWIO_ACCESS_15_ID_0_SHFT                                     0x4
#define HWIO_ACCESS_15_RWX_0_BMSK                                    0x7
#define HWIO_ACCESS_15_RWX_0_SHFT                                    0x0

#define HWIO_INFO_BLOCK_ACCESS_0_ADDR                         (NVM_REG_BASE      + 0x00000400)
#define HWIO_INFO_BLOCK_ACCESS_0_RMSK                         0xffffffff
#define HWIO_INFO_BLOCK_ACCESS_0_IN          \
        in_dword(HWIO_INFO_BLOCK_ACCESS_0_ADDR)
#define HWIO_INFO_BLOCK_ACCESS_0_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_ACCESS_0_ADDR, m)
#define HWIO_INFO_BLOCK_ACCESS_0_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_ACCESS_0_ADDR,v)
#define HWIO_INFO_BLOCK_ACCESS_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_ACCESS_0_ADDR,m,v,HWIO_INFO_BLOCK_ACCESS_0_IN)
#define HWIO_INFO_BLOCK_ACCESS_0_ID_3_7_BMSK                  0xc0000000
#define HWIO_INFO_BLOCK_ACCESS_0_ID_3_7_SHFT                        0x1e
#define HWIO_INFO_BLOCK_ACCESS_0_RW_3_7_BMSK                  0x30000000
#define HWIO_INFO_BLOCK_ACCESS_0_RW_3_7_SHFT                        0x1c
#define HWIO_INFO_BLOCK_ACCESS_0_ID_3_6_BMSK                   0xc000000
#define HWIO_INFO_BLOCK_ACCESS_0_ID_3_6_SHFT                        0x1a
#define HWIO_INFO_BLOCK_ACCESS_0_RW_3_6_BMSK                   0x3000000
#define HWIO_INFO_BLOCK_ACCESS_0_RW_3_6_SHFT                        0x18
#define HWIO_INFO_BLOCK_ACCESS_0_ID_2_5_BMSK                    0xc00000
#define HWIO_INFO_BLOCK_ACCESS_0_ID_2_5_SHFT                        0x16
#define HWIO_INFO_BLOCK_ACCESS_0_RW_2_5_BMSK                    0x300000
#define HWIO_INFO_BLOCK_ACCESS_0_RW_2_5_SHFT                        0x14
#define HWIO_INFO_BLOCK_ACCESS_0_ID_2_4_BMSK                     0xc0000
#define HWIO_INFO_BLOCK_ACCESS_0_ID_2_4_SHFT                        0x12
#define HWIO_INFO_BLOCK_ACCESS_0_RW_2_4_BMSK                     0x30000
#define HWIO_INFO_BLOCK_ACCESS_0_RW_2_4_SHFT                        0x10
#define HWIO_INFO_BLOCK_ACCESS_0_ID_1_3_BMSK                      0xc000
#define HWIO_INFO_BLOCK_ACCESS_0_ID_1_3_SHFT                         0xe
#define HWIO_INFO_BLOCK_ACCESS_0_RW_1_3_BMSK                      0x3000
#define HWIO_INFO_BLOCK_ACCESS_0_RW_1_3_SHFT                         0xc
#define HWIO_INFO_BLOCK_ACCESS_0_ID_1_2_BMSK                       0xc00
#define HWIO_INFO_BLOCK_ACCESS_0_ID_1_2_SHFT                         0xa
#define HWIO_INFO_BLOCK_ACCESS_0_RW_1_2_BMSK                       0x300
#define HWIO_INFO_BLOCK_ACCESS_0_RW_1_2_SHFT                         0x8
#define HWIO_INFO_BLOCK_ACCESS_0_ID_0_1_BMSK                        0xc0
#define HWIO_INFO_BLOCK_ACCESS_0_ID_0_1_SHFT                         0x6
#define HWIO_INFO_BLOCK_ACCESS_0_RW_0_1_BMSK                        0x30
#define HWIO_INFO_BLOCK_ACCESS_0_RW_0_1_SHFT                         0x4
#define HWIO_INFO_BLOCK_ACCESS_0_ID_0_0_BMSK                         0xc
#define HWIO_INFO_BLOCK_ACCESS_0_ID_0_0_SHFT                         0x2
#define HWIO_INFO_BLOCK_ACCESS_0_RW_0_0_BMSK                         0x3
#define HWIO_INFO_BLOCK_ACCESS_0_RW_0_0_SHFT                         0x0

#define HWIO_INFO_BLOCK_ACCESS_1_ADDR                         (NVM_REG_BASE      + 0x00000404)
#define HWIO_INFO_BLOCK_ACCESS_1_RMSK                         0xffffffff
#define HWIO_INFO_BLOCK_ACCESS_1_IN          \
        in_dword(HWIO_INFO_BLOCK_ACCESS_1_ADDR)
#define HWIO_INFO_BLOCK_ACCESS_1_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_ACCESS_1_ADDR, m)
#define HWIO_INFO_BLOCK_ACCESS_1_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_ACCESS_1_ADDR,v)
#define HWIO_INFO_BLOCK_ACCESS_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_ACCESS_1_ADDR,m,v,HWIO_INFO_BLOCK_ACCESS_1_IN)
#define HWIO_INFO_BLOCK_ACCESS_1_ID_7_7_BMSK                  0xc0000000
#define HWIO_INFO_BLOCK_ACCESS_1_ID_7_7_SHFT                        0x1e
#define HWIO_INFO_BLOCK_ACCESS_1_RW_7_7_BMSK                  0x30000000
#define HWIO_INFO_BLOCK_ACCESS_1_RW_7_7_SHFT                        0x1c
#define HWIO_INFO_BLOCK_ACCESS_1_ID_7_6_BMSK                   0xc000000
#define HWIO_INFO_BLOCK_ACCESS_1_ID_7_6_SHFT                        0x1a
#define HWIO_INFO_BLOCK_ACCESS_1_RW_7_6_BMSK                   0x3000000
#define HWIO_INFO_BLOCK_ACCESS_1_RW_7_6_SHFT                        0x18
#define HWIO_INFO_BLOCK_ACCESS_1_ID_6_5_BMSK                    0xc00000
#define HWIO_INFO_BLOCK_ACCESS_1_ID_6_5_SHFT                        0x16
#define HWIO_INFO_BLOCK_ACCESS_1_RW_6_5_BMSK                    0x300000
#define HWIO_INFO_BLOCK_ACCESS_1_RW_6_5_SHFT                        0x14
#define HWIO_INFO_BLOCK_ACCESS_1_ID_6_4_BMSK                     0xc0000
#define HWIO_INFO_BLOCK_ACCESS_1_ID_6_4_SHFT                        0x12
#define HWIO_INFO_BLOCK_ACCESS_1_RW_6_4_BMSK                     0x30000
#define HWIO_INFO_BLOCK_ACCESS_1_RW_6_4_SHFT                        0x10
#define HWIO_INFO_BLOCK_ACCESS_1_ID_5_3_BMSK                      0xc000
#define HWIO_INFO_BLOCK_ACCESS_1_ID_5_3_SHFT                         0xe
#define HWIO_INFO_BLOCK_ACCESS_1_RW_5_3_BMSK                      0x3000
#define HWIO_INFO_BLOCK_ACCESS_1_RW_5_3_SHFT                         0xc
#define HWIO_INFO_BLOCK_ACCESS_1_ID_5_2_BMSK                       0xc00
#define HWIO_INFO_BLOCK_ACCESS_1_ID_5_2_SHFT                         0xa
#define HWIO_INFO_BLOCK_ACCESS_1_RW_5_2_BMSK                       0x300
#define HWIO_INFO_BLOCK_ACCESS_1_RW_5_2_SHFT                         0x8
#define HWIO_INFO_BLOCK_ACCESS_1_ID_4_1_BMSK                        0xc0
#define HWIO_INFO_BLOCK_ACCESS_1_ID_4_1_SHFT                         0x6
#define HWIO_INFO_BLOCK_ACCESS_1_RW_4_1_BMSK                        0x30
#define HWIO_INFO_BLOCK_ACCESS_1_RW_4_1_SHFT                         0x4
#define HWIO_INFO_BLOCK_ACCESS_1_ID_4_0_BMSK                         0xc
#define HWIO_INFO_BLOCK_ACCESS_1_ID_4_0_SHFT                         0x2
#define HWIO_INFO_BLOCK_ACCESS_1_RW_4_0_BMSK                         0x3
#define HWIO_INFO_BLOCK_ACCESS_1_RW_4_0_SHFT                         0x0

#define HWIO_INFO_BLOCK_ACCESS_2_ADDR                         (NVM_REG_BASE      + 0x00000408)
#define HWIO_INFO_BLOCK_ACCESS_2_RMSK                         0xffffffff
#define HWIO_INFO_BLOCK_ACCESS_2_IN          \
        in_dword(HWIO_INFO_BLOCK_ACCESS_2_ADDR)
#define HWIO_INFO_BLOCK_ACCESS_2_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_ACCESS_2_ADDR, m)
#define HWIO_INFO_BLOCK_ACCESS_2_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_ACCESS_2_ADDR,v)
#define HWIO_INFO_BLOCK_ACCESS_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_ACCESS_2_ADDR,m,v,HWIO_INFO_BLOCK_ACCESS_2_IN)
#define HWIO_INFO_BLOCK_ACCESS_2_ID_11_7_BMSK                 0xc0000000
#define HWIO_INFO_BLOCK_ACCESS_2_ID_11_7_SHFT                       0x1e
#define HWIO_INFO_BLOCK_ACCESS_2_RW_11_7_BMSK                 0x30000000
#define HWIO_INFO_BLOCK_ACCESS_2_RW_11_7_SHFT                       0x1c
#define HWIO_INFO_BLOCK_ACCESS_2_ID_11_6_BMSK                  0xc000000
#define HWIO_INFO_BLOCK_ACCESS_2_ID_11_6_SHFT                       0x1a
#define HWIO_INFO_BLOCK_ACCESS_2_RW_11_6_BMSK                  0x3000000
#define HWIO_INFO_BLOCK_ACCESS_2_RW_11_6_SHFT                       0x18
#define HWIO_INFO_BLOCK_ACCESS_2_ID_10_5_BMSK                   0xc00000
#define HWIO_INFO_BLOCK_ACCESS_2_ID_10_5_SHFT                       0x16
#define HWIO_INFO_BLOCK_ACCESS_2_RW_10_5_BMSK                   0x300000
#define HWIO_INFO_BLOCK_ACCESS_2_RW_10_5_SHFT                       0x14
#define HWIO_INFO_BLOCK_ACCESS_2_ID_10_4_BMSK                    0xc0000
#define HWIO_INFO_BLOCK_ACCESS_2_ID_10_4_SHFT                       0x12
#define HWIO_INFO_BLOCK_ACCESS_2_RW_10_4_BMSK                    0x30000
#define HWIO_INFO_BLOCK_ACCESS_2_RW_10_4_SHFT                       0x10
#define HWIO_INFO_BLOCK_ACCESS_2_ID_9_3_BMSK                      0xc000
#define HWIO_INFO_BLOCK_ACCESS_2_ID_9_3_SHFT                         0xe
#define HWIO_INFO_BLOCK_ACCESS_2_RW_9_3_BMSK                      0x3000
#define HWIO_INFO_BLOCK_ACCESS_2_RW_9_3_SHFT                         0xc
#define HWIO_INFO_BLOCK_ACCESS_2_ID_9_2_BMSK                       0xc00
#define HWIO_INFO_BLOCK_ACCESS_2_ID_9_2_SHFT                         0xa
#define HWIO_INFO_BLOCK_ACCESS_2_RW_9_2_BMSK                       0x300
#define HWIO_INFO_BLOCK_ACCESS_2_RW_9_2_SHFT                         0x8
#define HWIO_INFO_BLOCK_ACCESS_2_ID_8_1_BMSK                        0xc0
#define HWIO_INFO_BLOCK_ACCESS_2_ID_8_1_SHFT                         0x6
#define HWIO_INFO_BLOCK_ACCESS_2_RW_8_1_BMSK                        0x30
#define HWIO_INFO_BLOCK_ACCESS_2_RW_8_1_SHFT                         0x4
#define HWIO_INFO_BLOCK_ACCESS_2_ID_8_0_BMSK                         0xc
#define HWIO_INFO_BLOCK_ACCESS_2_ID_8_0_SHFT                         0x2
#define HWIO_INFO_BLOCK_ACCESS_2_RW_8_0_BMSK                         0x3
#define HWIO_INFO_BLOCK_ACCESS_2_RW_8_0_SHFT                         0x0

#define HWIO_INFO_BLOCK_ACCESS_3_ADDR                         (NVM_REG_BASE      + 0x0000040c)
#define HWIO_INFO_BLOCK_ACCESS_3_RMSK                         0xffffffff
#define HWIO_INFO_BLOCK_ACCESS_3_IN          \
        in_dword(HWIO_INFO_BLOCK_ACCESS_3_ADDR)
#define HWIO_INFO_BLOCK_ACCESS_3_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_ACCESS_3_ADDR, m)
#define HWIO_INFO_BLOCK_ACCESS_3_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_ACCESS_3_ADDR,v)
#define HWIO_INFO_BLOCK_ACCESS_3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_ACCESS_3_ADDR,m,v,HWIO_INFO_BLOCK_ACCESS_3_IN)
#define HWIO_INFO_BLOCK_ACCESS_3_ID_15_7_BMSK                 0xc0000000
#define HWIO_INFO_BLOCK_ACCESS_3_ID_15_7_SHFT                       0x1e
#define HWIO_INFO_BLOCK_ACCESS_3_RW_15_7_BMSK                 0x30000000
#define HWIO_INFO_BLOCK_ACCESS_3_RW_15_7_SHFT                       0x1c
#define HWIO_INFO_BLOCK_ACCESS_3_ID_15_6_BMSK                  0xc000000
#define HWIO_INFO_BLOCK_ACCESS_3_ID_15_6_SHFT                       0x1a
#define HWIO_INFO_BLOCK_ACCESS_3_RW_15_6_BMSK                  0x3000000
#define HWIO_INFO_BLOCK_ACCESS_3_RW_15_6_SHFT                       0x18
#define HWIO_INFO_BLOCK_ACCESS_3_ID_14_5_BMSK                   0xc00000
#define HWIO_INFO_BLOCK_ACCESS_3_ID_14_5_SHFT                       0x16
#define HWIO_INFO_BLOCK_ACCESS_3_RW_14_5_BMSK                   0x300000
#define HWIO_INFO_BLOCK_ACCESS_3_RW_14_5_SHFT                       0x14
#define HWIO_INFO_BLOCK_ACCESS_3_ID_14_4_BMSK                    0xc0000
#define HWIO_INFO_BLOCK_ACCESS_3_ID_14_4_SHFT                       0x12
#define HWIO_INFO_BLOCK_ACCESS_3_RW_14_4_BMSK                    0x30000
#define HWIO_INFO_BLOCK_ACCESS_3_RW_14_4_SHFT                       0x10
#define HWIO_INFO_BLOCK_ACCESS_3_ID_13_3_BMSK                     0xc000
#define HWIO_INFO_BLOCK_ACCESS_3_ID_13_3_SHFT                        0xe
#define HWIO_INFO_BLOCK_ACCESS_3_RW_13_3_BMSK                     0x3000
#define HWIO_INFO_BLOCK_ACCESS_3_RW_13_3_SHFT                        0xc
#define HWIO_INFO_BLOCK_ACCESS_3_ID_13_2_BMSK                      0xc00
#define HWIO_INFO_BLOCK_ACCESS_3_ID_13_2_SHFT                        0xa
#define HWIO_INFO_BLOCK_ACCESS_3_RW_13_2_BMSK                      0x300
#define HWIO_INFO_BLOCK_ACCESS_3_RW_13_2_SHFT                        0x8
#define HWIO_INFO_BLOCK_ACCESS_3_ID_12_1_BMSK                       0xc0
#define HWIO_INFO_BLOCK_ACCESS_3_ID_12_1_SHFT                        0x6
#define HWIO_INFO_BLOCK_ACCESS_3_RW_12_1_BMSK                       0x30
#define HWIO_INFO_BLOCK_ACCESS_3_RW_12_1_SHFT                        0x4
#define HWIO_INFO_BLOCK_ACCESS_3_ID_12_0_BMSK                        0xc
#define HWIO_INFO_BLOCK_ACCESS_3_ID_12_0_SHFT                        0x2
#define HWIO_INFO_BLOCK_ACCESS_3_RW_12_0_BMSK                        0x3
#define HWIO_INFO_BLOCK_ACCESS_3_RW_12_0_SHFT                        0x0

#define HWIO_INFO_BLOCK_OTP_ADDR                              (NVM_REG_BASE      + 0x00000410)
#define HWIO_INFO_BLOCK_OTP_RMSK                                     0x1
#define HWIO_INFO_BLOCK_OTP_IN          \
        in_dword(HWIO_INFO_BLOCK_OTP_ADDR)
#define HWIO_INFO_BLOCK_OTP_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_OTP_ADDR, m)
#define HWIO_INFO_BLOCK_OTP_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_OTP_ADDR,v)
#define HWIO_INFO_BLOCK_OTP_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_OTP_ADDR,m,v,HWIO_INFO_BLOCK_OTP_IN)
#define HWIO_INFO_BLOCK_OTP_CTL_EN_BMSK                              0x1
#define HWIO_INFO_BLOCK_OTP_CTL_EN_SHFT                              0x0

#define HWIO_TRANSIENT_ADDR                                   (NVM_REG_BASE      + 0x00000414)
#define HWIO_TRANSIENT_RMSK                                       0x3fff
#define HWIO_TRANSIENT_IN          \
        in_dword(HWIO_TRANSIENT_ADDR)
#define HWIO_TRANSIENT_INM(m)      \
        in_dword_masked(HWIO_TRANSIENT_ADDR, m)
#define HWIO_TRANSIENT_OUT(v)      \
        out_dword(HWIO_TRANSIENT_ADDR,v)
#define HWIO_TRANSIENT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TRANSIENT_ADDR,m,v,HWIO_TRANSIENT_IN)
#define HWIO_TRANSIENT_WRITE_DISABLE_BMSK                         0x3fff
#define HWIO_TRANSIENT_WRITE_DISABLE_SHFT                            0x0

#define HWIO_OBLITERATE_ADDR                                  (NVM_REG_BASE      + 0x00000418)
#define HWIO_OBLITERATE_RMSK                                  0xffffffff
#define HWIO_OBLITERATE_OUT(v)      \
        out_dword(HWIO_OBLITERATE_ADDR,v)
#define HWIO_OBLITERATE_VALUE_BMSK                            0xffffffff
#define HWIO_OBLITERATE_VALUE_SHFT                                   0x0

#define HWIO_NVM_DBG_SEL_7LSB0_ADDR                           (NVM_REG_BASE      + 0x0000041c)
#define HWIO_NVM_DBG_SEL_7LSB0_RMSK                                  0xf
#define HWIO_NVM_DBG_SEL_7LSB0_IN          \
        in_dword(HWIO_NVM_DBG_SEL_7LSB0_ADDR)
#define HWIO_NVM_DBG_SEL_7LSB0_INM(m)      \
        in_dword_masked(HWIO_NVM_DBG_SEL_7LSB0_ADDR, m)
#define HWIO_NVM_DBG_SEL_7LSB0_OUT(v)      \
        out_dword(HWIO_NVM_DBG_SEL_7LSB0_ADDR,v)
#define HWIO_NVM_DBG_SEL_7LSB0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_DBG_SEL_7LSB0_ADDR,m,v,HWIO_NVM_DBG_SEL_7LSB0_IN)
#define HWIO_NVM_DBG_SEL_7LSB0_SEL_BMSK                              0xf
#define HWIO_NVM_DBG_SEL_7LSB0_SEL_SHFT                              0x0

#define HWIO_NVM_DBG_SEL_15LSB8_ADDR                          (NVM_REG_BASE      + 0x00000420)
#define HWIO_NVM_DBG_SEL_15LSB8_RMSK                                 0xf
#define HWIO_NVM_DBG_SEL_15LSB8_IN          \
        in_dword(HWIO_NVM_DBG_SEL_15LSB8_ADDR)
#define HWIO_NVM_DBG_SEL_15LSB8_INM(m)      \
        in_dword_masked(HWIO_NVM_DBG_SEL_15LSB8_ADDR, m)
#define HWIO_NVM_DBG_SEL_15LSB8_OUT(v)      \
        out_dword(HWIO_NVM_DBG_SEL_15LSB8_ADDR,v)
#define HWIO_NVM_DBG_SEL_15LSB8_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_DBG_SEL_15LSB8_ADDR,m,v,HWIO_NVM_DBG_SEL_15LSB8_IN)
#define HWIO_NVM_DBG_SEL_15LSB8_SEL_BMSK                             0xf
#define HWIO_NVM_DBG_SEL_15LSB8_SEL_SHFT                             0x0

#define HWIO_NVM_DBG_SEL_23LSB16_ADDR                         (NVM_REG_BASE      + 0x00000424)
#define HWIO_NVM_DBG_SEL_23LSB16_RMSK                                0xf
#define HWIO_NVM_DBG_SEL_23LSB16_IN          \
        in_dword(HWIO_NVM_DBG_SEL_23LSB16_ADDR)
#define HWIO_NVM_DBG_SEL_23LSB16_INM(m)      \
        in_dword_masked(HWIO_NVM_DBG_SEL_23LSB16_ADDR, m)
#define HWIO_NVM_DBG_SEL_23LSB16_OUT(v)      \
        out_dword(HWIO_NVM_DBG_SEL_23LSB16_ADDR,v)
#define HWIO_NVM_DBG_SEL_23LSB16_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_DBG_SEL_23LSB16_ADDR,m,v,HWIO_NVM_DBG_SEL_23LSB16_IN)
#define HWIO_NVM_DBG_SEL_23LSB16_SEL_BMSK                            0xf
#define HWIO_NVM_DBG_SEL_23LSB16_SEL_SHFT                            0x0

#define HWIO_NVM_DBG_SEL_31LSB24_ADDR                         (NVM_REG_BASE      + 0x00000428)
#define HWIO_NVM_DBG_SEL_31LSB24_RMSK                                0xf
#define HWIO_NVM_DBG_SEL_31LSB24_IN          \
        in_dword(HWIO_NVM_DBG_SEL_31LSB24_ADDR)
#define HWIO_NVM_DBG_SEL_31LSB24_INM(m)      \
        in_dword_masked(HWIO_NVM_DBG_SEL_31LSB24_ADDR, m)
#define HWIO_NVM_DBG_SEL_31LSB24_OUT(v)      \
        out_dword(HWIO_NVM_DBG_SEL_31LSB24_ADDR,v)
#define HWIO_NVM_DBG_SEL_31LSB24_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_DBG_SEL_31LSB24_ADDR,m,v,HWIO_NVM_DBG_SEL_31LSB24_IN)
#define HWIO_NVM_DBG_SEL_31LSB24_SEL_BMSK                            0xf
#define HWIO_NVM_DBG_SEL_31LSB24_SEL_SHFT                            0x0

#define HWIO_NVM_ADDR                                         (NVM_REG_BASE      + 0x0000042c)
#define HWIO_NVM_RMSK                                               0x7f
#define HWIO_NVM_IN          \
        in_dword(HWIO_NVM_ADDR)
#define HWIO_NVM_INM(m)      \
        in_dword_masked(HWIO_NVM_ADDR, m)
#define HWIO_NVM_OUT(v)      \
        out_dword(HWIO_NVM_ADDR,v)
#define HWIO_NVM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_NVM_ADDR,m,v,HWIO_NVM_IN)
#define HWIO_NVM_MISC_BMSK                                          0x7f
#define HWIO_NVM_MISC_SHFT                                           0x0

#define HWIO_NVM_LRC_ADDR                                     (NVM_REG_BASE      + 0x00000430)
#define HWIO_NVM_LRC_RMSK                                          0x1ff
#define HWIO_NVM_LRC_IN          \
        in_dword(HWIO_NVM_LRC_ADDR)
#define HWIO_NVM_LRC_INM(m)      \
        in_dword_masked(HWIO_NVM_LRC_ADDR, m)
#define HWIO_NVM_LRC_FSM_STATE_BMSK                                0x1ff
#define HWIO_NVM_LRC_FSM_STATE_SHFT                                  0x0

#define HWIO_RRAM_ECC_ADDR                                    (NVM_REG_BASE      + 0x00000434)
#define HWIO_RRAM_ECC_RMSK                                        0x7fff
#define HWIO_RRAM_ECC_IN          \
        in_dword(HWIO_RRAM_ECC_ADDR)
#define HWIO_RRAM_ECC_INM(m)      \
        in_dword_masked(HWIO_RRAM_ECC_ADDR, m)
#define HWIO_RRAM_ECC_DATA_BMSK                                   0x7fff
#define HWIO_RRAM_ECC_DATA_SHFT                                      0x0

#define HWIO_REGION_MID_ADDR                                  (NVM_REG_BASE      + 0x00000438)
#define HWIO_REGION_MID_RMSK                                  0xffffffff
#define HWIO_REGION_MID_IN          \
        in_dword(HWIO_REGION_MID_ADDR)
#define HWIO_REGION_MID_INM(m)      \
        in_dword_masked(HWIO_REGION_MID_ADDR, m)
#define HWIO_REGION_MID_OUT(v)      \
        out_dword(HWIO_REGION_MID_ADDR,v)
#define HWIO_REGION_MID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_REGION_MID_ADDR,m,v,HWIO_REGION_MID_IN)
#define HWIO_REGION_MID_ID_15_BMSK                            0xc0000000
#define HWIO_REGION_MID_ID_15_SHFT                                  0x1e
#define HWIO_REGION_MID_ID_14_BMSK                            0x30000000
#define HWIO_REGION_MID_ID_14_SHFT                                  0x1c
#define HWIO_REGION_MID_ID_13_BMSK                             0xc000000
#define HWIO_REGION_MID_ID_13_SHFT                                  0x1a
#define HWIO_REGION_MID_ID_12_BMSK                             0x3000000
#define HWIO_REGION_MID_ID_12_SHFT                                  0x18
#define HWIO_REGION_MID_ID_11_BMSK                              0xc00000
#define HWIO_REGION_MID_ID_11_SHFT                                  0x16
#define HWIO_REGION_MID_ID_10_BMSK                              0x300000
#define HWIO_REGION_MID_ID_10_SHFT                                  0x14
#define HWIO_REGION_MID_ID_9_BMSK                                0xc0000
#define HWIO_REGION_MID_ID_9_SHFT                                   0x12
#define HWIO_REGION_MID_ID_8_BMSK                                0x30000
#define HWIO_REGION_MID_ID_8_SHFT                                   0x10
#define HWIO_REGION_MID_ID_7_BMSK                                 0xc000
#define HWIO_REGION_MID_ID_7_SHFT                                    0xe
#define HWIO_REGION_MID_ID_6_BMSK                                 0x3000
#define HWIO_REGION_MID_ID_6_SHFT                                    0xc
#define HWIO_REGION_MID_ID_5_BMSK                                  0xc00
#define HWIO_REGION_MID_ID_5_SHFT                                    0xa
#define HWIO_REGION_MID_ID_4_BMSK                                  0x300
#define HWIO_REGION_MID_ID_4_SHFT                                    0x8
#define HWIO_REGION_MID_ID_3_BMSK                                   0xc0
#define HWIO_REGION_MID_ID_3_SHFT                                    0x6
#define HWIO_REGION_MID_ID_2_BMSK                                   0x30
#define HWIO_REGION_MID_ID_2_SHFT                                    0x4
#define HWIO_REGION_MID_ID_1_BMSK                                    0xc
#define HWIO_REGION_MID_ID_1_SHFT                                    0x2
#define HWIO_REGION_MID_ID_0_BMSK                                    0x3
#define HWIO_REGION_MID_ID_0_SHFT                                    0x0

#define HWIO_SECURITY_CFG_ADDR                                (NVM_REG_BASE      + 0x0000043c)
#define HWIO_SECURITY_CFG_RMSK                                       0x3
#define HWIO_SECURITY_CFG_IN          \
        in_dword(HWIO_SECURITY_CFG_ADDR)
#define HWIO_SECURITY_CFG_INM(m)      \
        in_dword_masked(HWIO_SECURITY_CFG_ADDR, m)
#define HWIO_SECURITY_CFG_OUT(v)      \
        out_dword(HWIO_SECURITY_CFG_ADDR,v)
#define HWIO_SECURITY_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SECURITY_CFG_ADDR,m,v,HWIO_SECURITY_CFG_IN)
#define HWIO_SECURITY_CFG_EN_BMSK                                    0x2
#define HWIO_SECURITY_CFG_EN_SHFT                                    0x1
#define HWIO_SECURITY_CFG_CLR_BMSK                                   0x1
#define HWIO_SECURITY_CFG_CLR_SHFT                                   0x0

#define HWIO_SECURITY_INFO_ADDR                               (NVM_REG_BASE      + 0x00000440)
#define HWIO_SECURITY_INFO_RMSK                                0xfff0003
#define HWIO_SECURITY_INFO_IN          \
        in_dword(HWIO_SECURITY_INFO_ADDR)
#define HWIO_SECURITY_INFO_INM(m)      \
        in_dword_masked(HWIO_SECURITY_INFO_ADDR, m)
#define HWIO_SECURITY_INFO_ADDR_VIOL_BMSK                      0xfff0000
#define HWIO_SECURITY_INFO_ADDR_VIOL_SHFT                           0x10
#define HWIO_SECURITY_INFO_MID_VIOL_BMSK                             0x3
#define HWIO_SECURITY_INFO_MID_VIOL_SHFT                             0x0

#define HWIO_LBUF_ADDR                                        (NVM_REG_BASE      + 0x00000444)
#define HWIO_LBUF_RMSK                                               0xf
#define HWIO_LBUF_IN          \
        in_dword(HWIO_LBUF_ADDR)
#define HWIO_LBUF_INM(m)      \
        in_dword_masked(HWIO_LBUF_ADDR, m)
#define HWIO_LBUF_OUT(v)      \
        out_dword(HWIO_LBUF_ADDR,v)
#define HWIO_LBUF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LBUF_ADDR,m,v,HWIO_LBUF_IN)
#define HWIO_LBUF_DISABLES_BMSK                                      0xf
#define HWIO_LBUF_DISABLES_SHFT                                      0x0

#define HWIO_MASTER_ADDR                                      (NVM_REG_BASE      + 0x00000448)
#define HWIO_MASTER_RMSK                                             0x3
#define HWIO_MASTER_IN          \
        in_dword(HWIO_MASTER_ADDR)
#define HWIO_MASTER_INM(m)      \
        in_dword_masked(HWIO_MASTER_ADDR, m)
#define HWIO_MASTER_OUT(v)      \
        out_dword(HWIO_MASTER_ADDR,v)
#define HWIO_MASTER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MASTER_ADDR,m,v,HWIO_MASTER_IN)
#define HWIO_MASTER_ID_BMSK                                          0x3
#define HWIO_MASTER_ID_SHFT                                          0x0

#define HWIO_LOAD_BUFFER_LSB_ADDR                             (NVM_REG_BASE      + 0x00000800)
#define HWIO_LOAD_BUFFER_LSB_RMSK                             0xffffffff
#define HWIO_LOAD_BUFFER_LSB_OUT(v)      \
        out_dword(HWIO_LOAD_BUFFER_LSB_ADDR,v)
#define HWIO_LOAD_BUFFER_LSB_DATA_BMSK                        0xffffffff
#define HWIO_LOAD_BUFFER_LSB_DATA_SHFT                               0x0

#define HWIO_LOAD_BUFFER_MSB_ADDR                             (NVM_REG_BASE      + 0x00000804)
#define HWIO_LOAD_BUFFER_MSB_RMSK                             0xffffffff
#define HWIO_LOAD_BUFFER_MSB_OUT(v)      \
        out_dword(HWIO_LOAD_BUFFER_MSB_ADDR,v)
#define HWIO_LOAD_BUFFER_MSB_DATA_BMSK                        0xffffffff
#define HWIO_LOAD_BUFFER_MSB_DATA_SHFT                               0x0

#define HWIO_LOAD_BUFFER_ADDRESS_ADDR                         (NVM_REG_BASE      + 0x00000808)
#define HWIO_LOAD_BUFFER_ADDRESS_RMSK                             0xffff
#define HWIO_LOAD_BUFFER_ADDRESS_IN          \
        in_dword(HWIO_LOAD_BUFFER_ADDRESS_ADDR)
#define HWIO_LOAD_BUFFER_ADDRESS_INM(m)      \
        in_dword_masked(HWIO_LOAD_BUFFER_ADDRESS_ADDR, m)
#define HWIO_LOAD_BUFFER_ADDRESS_OUT(v)      \
        out_dword(HWIO_LOAD_BUFFER_ADDRESS_ADDR,v)
#define HWIO_LOAD_BUFFER_ADDRESS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LOAD_BUFFER_ADDRESS_ADDR,m,v,HWIO_LOAD_BUFFER_ADDRESS_IN)
#define HWIO_LOAD_BUFFER_ADDRESS_ADDR_BMSK                        0xffff
#define HWIO_LOAD_BUFFER_ADDRESS_ADDR_SHFT                           0x0

#define HWIO_TABLE_ADDR                                       (NVM_REG_BASE      + 0x0000080c)
#define HWIO_TABLE_RMSK                                              0xf
#define HWIO_TABLE_IN          \
        in_dword(HWIO_TABLE_ADDR)
#define HWIO_TABLE_INM(m)      \
        in_dword_masked(HWIO_TABLE_ADDR, m)
#define HWIO_TABLE_OUT(v)      \
        out_dword(HWIO_TABLE_ADDR,v)
#define HWIO_TABLE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TABLE_ADDR,m,v,HWIO_TABLE_IN)
#define HWIO_TABLE_CMD_BMSK                                          0xf
#define HWIO_TABLE_CMD_SHFT                                          0x0

#define HWIO_READ_LSB_ADDR                                    (NVM_REG_BASE      + 0x00000810)
#define HWIO_READ_LSB_RMSK                                    0xffffffff
#define HWIO_READ_LSB_IN          \
        in_dword(HWIO_READ_LSB_ADDR)
#define HWIO_READ_LSB_INM(m)      \
        in_dword_masked(HWIO_READ_LSB_ADDR, m)
#define HWIO_READ_LSB_DATA_BMSK                               0xffffffff
#define HWIO_READ_LSB_DATA_SHFT                                      0x0

#define HWIO_READ_MSB_ADDR                                    (NVM_REG_BASE      + 0x00000814)
#define HWIO_READ_MSB_RMSK                                    0xffffffff
#define HWIO_READ_MSB_IN          \
        in_dword(HWIO_READ_MSB_ADDR)
#define HWIO_READ_MSB_INM(m)      \
        in_dword_masked(HWIO_READ_MSB_ADDR, m)
#define HWIO_READ_MSB_DATA_BMSK                               0xffffffff
#define HWIO_READ_MSB_DATA_SHFT                                      0x0

#define HWIO_NVM_STATUS_ADDR                                  (NVM_REG_BASE      + 0x00000818)
#define HWIO_NVM_STATUS_RMSK                                         0x3
#define HWIO_NVM_STATUS_IN          \
        in_dword(HWIO_NVM_STATUS_ADDR)
#define HWIO_NVM_STATUS_INM(m)      \
        in_dword_masked(HWIO_NVM_STATUS_ADDR, m)
#define HWIO_NVM_STATUS_CMD_DONE_BMSK                                0x2
#define HWIO_NVM_STATUS_CMD_DONE_SHFT                                0x1
#define HWIO_NVM_STATUS_WRITE_IRQ_BMSK                               0x1
#define HWIO_NVM_STATUS_WRITE_IRQ_SHFT                               0x0

#define HWIO_NVM_STATUS_CLEAR_ADDR                            (NVM_REG_BASE      + 0x0000081c)
#define HWIO_NVM_STATUS_CLEAR_RMSK                                   0x1
#define HWIO_NVM_STATUS_CLEAR_OUT(v)      \
        out_dword(HWIO_NVM_STATUS_CLEAR_ADDR,v)
#define HWIO_NVM_STATUS_CLEAR_WRITE_IRQ_BMSK                         0x1
#define HWIO_NVM_STATUS_CLEAR_WRITE_IRQ_SHFT                         0x0

#define HWIO_NVM_STATUS_ERROR_ADDR                            (NVM_REG_BASE      + 0x00000820)
#define HWIO_NVM_STATUS_ERROR_RMSK                                  0x3f
#define HWIO_NVM_STATUS_ERROR_IN          \
        in_dword(HWIO_NVM_STATUS_ERROR_ADDR)
#define HWIO_NVM_STATUS_ERROR_INM(m)      \
        in_dword_masked(HWIO_NVM_STATUS_ERROR_ADDR, m)
#define HWIO_NVM_STATUS_ERROR_INVALID_CMD_BMSK                      0x20
#define HWIO_NVM_STATUS_ERROR_INVALID_CMD_SHFT                       0x5
#define HWIO_NVM_STATUS_ERROR_WRITE_ERROR_BMSK                      0x10
#define HWIO_NVM_STATUS_ERROR_WRITE_ERROR_SHFT                       0x4
#define HWIO_NVM_STATUS_ERROR_VDIO_OK_BMSK                           0x8
#define HWIO_NVM_STATUS_ERROR_VDIO_OK_SHFT                           0x3
#define HWIO_NVM_STATUS_ERROR_INFO_ACCESS_BMSK                       0x4
#define HWIO_NVM_STATUS_ERROR_INFO_ACCESS_SHFT                       0x2
#define HWIO_NVM_STATUS_ERROR_ACCESS_BMSK                            0x2
#define HWIO_NVM_STATUS_ERROR_ACCESS_SHFT                            0x1
#define HWIO_NVM_STATUS_ERROR_ERROR_IRQ_BMSK                         0x1
#define HWIO_NVM_STATUS_ERROR_ERROR_IRQ_SHFT                         0x0

#define HWIO_NVM_STATUS_ERROR_CLEAR_ADDR                      (NVM_REG_BASE      + 0x00000824)
#define HWIO_NVM_STATUS_ERROR_CLEAR_RMSK                            0x3f
#define HWIO_NVM_STATUS_ERROR_CLEAR_OUT(v)      \
        out_dword(HWIO_NVM_STATUS_ERROR_CLEAR_ADDR,v)
#define HWIO_NVM_STATUS_ERROR_CLEAR_INVALID_CMD_BMSK                0x20
#define HWIO_NVM_STATUS_ERROR_CLEAR_INVALID_CMD_SHFT                 0x5
#define HWIO_NVM_STATUS_ERROR_CLEAR_WRITE_ERROR_BMSK                0x10
#define HWIO_NVM_STATUS_ERROR_CLEAR_WRITE_ERROR_SHFT                 0x4
#define HWIO_NVM_STATUS_ERROR_CLEAR_VDIO_OK_BMSK                     0x8
#define HWIO_NVM_STATUS_ERROR_CLEAR_VDIO_OK_SHFT                     0x3
#define HWIO_NVM_STATUS_ERROR_CLEAR_INFO_ACCESS_BMSK                 0x4
#define HWIO_NVM_STATUS_ERROR_CLEAR_INFO_ACCESS_SHFT                 0x2
#define HWIO_NVM_STATUS_ERROR_CLEAR_ACCESS_BMSK                      0x2
#define HWIO_NVM_STATUS_ERROR_CLEAR_ACCESS_SHFT                      0x1
#define HWIO_NVM_STATUS_ERROR_CLEAR_ERROR_IRQ_BMSK                   0x1
#define HWIO_NVM_STATUS_ERROR_CLEAR_ERROR_IRQ_SHFT                   0x0

#define HWIO_INFO_BLOCK_ADDR                                  (NVM_REG_BASE      + 0x00000828)
#define HWIO_INFO_BLOCK_RMSK                                         0x1
#define HWIO_INFO_BLOCK_IN          \
        in_dword(HWIO_INFO_BLOCK_ADDR)
#define HWIO_INFO_BLOCK_INM(m)      \
        in_dword_masked(HWIO_INFO_BLOCK_ADDR, m)
#define HWIO_INFO_BLOCK_OUT(v)      \
        out_dword(HWIO_INFO_BLOCK_ADDR,v)
#define HWIO_INFO_BLOCK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_INFO_BLOCK_ADDR,m,v,HWIO_INFO_BLOCK_IN)
#define HWIO_INFO_BLOCK_IFREN_BMSK                                   0x1
#define HWIO_INFO_BLOCK_IFREN_SHFT                                   0x0


#endif /* __HWIO_NVM_H__ */
