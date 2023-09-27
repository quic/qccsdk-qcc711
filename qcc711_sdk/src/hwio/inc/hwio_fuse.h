#ifndef __HWIO_FUSE_H__
#define __HWIO_FUSE_H__
/*
===========================================================================
*/
/**
  @file hwio_fuse.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP'],
    'exclude-no-doc': False,
    'exclude-reserved': True,
    'filename': 'inc/hwio_fuse.h',
    'header': '#include "HALhwio.h"\n#include "hwio_base.h"',
    'output_fvals': True}
*/
/*
  ===========================================================================

  Copyright (c) 2023 Qualcomm Technologies, Inc.
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
 * MODULE: OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP
 *--------------------------------------------------------------------------*/

#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_BASE      + 0x00000000)
#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE_SIZE                                        0x800
#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE_USED                                        0x7fc

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000000)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_CHIP_RAND_BASE_KEY_31_0_BMSK                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_LSB_CHIP_RAND_BASE_KEY_31_0_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000004)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_CHIP_RAND_BASE_KEY_63_32_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW0_MSB_CHIP_RAND_BASE_KEY_63_32_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000008)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_CHIP_RAND_BASE_KEY_95_64_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_LSB_CHIP_RAND_BASE_KEY_95_64_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000000c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_CHIP_RAND_BASE_KEY_127_96_BMSK                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW1_MSB_CHIP_RAND_BASE_KEY_127_96_SHFT                          0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000010)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_CHIP_RAND_BASE_KEY_159_128_BMSK                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_LSB_CHIP_RAND_BASE_KEY_159_128_SHFT                         0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000014)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_CHIP_RAND_BASE_KEY_191_160_BMSK                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW2_MSB_CHIP_RAND_BASE_KEY_191_160_SHFT                         0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000018)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_CHIP_RAND_BASE_KEY_223_192_BMSK                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_LSB_CHIP_RAND_BASE_KEY_223_192_SHFT                         0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000001c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_CHIP_RAND_BASE_KEY_255_224_BMSK                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1A_ROW3_MSB_CHIP_RAND_BASE_KEY_255_224_SHFT                         0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000020)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_OTP_TME_1_31_24_BMSK                                   0xff000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_OTP_TME_1_31_24_SHFT                                         0x18
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_QC_SECURITY_POLICY_BMSK                                  0xff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_QC_SECURITY_POLICY_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_RTL_PROV_KEY_STATE_VECTOR_BMSK                             0xff00
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_RTL_PROV_KEY_STATE_VECTOR_SHFT                                0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_OTP_TME_1_7_1_BMSK                                           0xfe
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_OTP_TME_1_7_1_SHFT                                            0x1
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_EXT_INST_FETCH_DISABLE_BMSK                                   0x1
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_LSB_EXT_INST_FETCH_DISABLE_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000024)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_OTP_TME_1_63_32_BMSK                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1_MSB_OTP_TME_1_63_32_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000028)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_TME_ROM_PATCH_1_ADDR_BMSK                        0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_TME_ROM_PATCH_1_ADDR_SHFT                              0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_TME_ROM_PATCH_0_ADDR_BMSK                            0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_LSB_TME_ROM_PATCH_0_ADDR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000002c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_TME_ROM_PATCH_3_ADDR_BMSK                        0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_TME_ROM_PATCH_3_ADDR_SHFT                              0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_TME_ROM_PATCH_2_ADDR_BMSK                            0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW0_MSB_TME_ROM_PATCH_2_ADDR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000030)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_TME_ROM_PATCH_5_ADDR_BMSK                        0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_TME_ROM_PATCH_5_ADDR_SHFT                              0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_TME_ROM_PATCH_4_ADDR_BMSK                            0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_LSB_TME_ROM_PATCH_4_ADDR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000034)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_TME_ROM_PATCH_7_ADDR_BMSK                        0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_TME_ROM_PATCH_7_ADDR_SHFT                              0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_TME_ROM_PATCH_6_ADDR_BMSK                            0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW1_MSB_TME_ROM_PATCH_6_ADDR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000038)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_TME_ROM_PATCH_9_ADDR_BMSK                        0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_TME_ROM_PATCH_9_ADDR_SHFT                              0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_TME_ROM_PATCH_8_ADDR_BMSK                            0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_LSB_TME_ROM_PATCH_8_ADDR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000003c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_TME_ROM_PATCH_11_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_TME_ROM_PATCH_11_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_TME_ROM_PATCH_10_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW2_MSB_TME_ROM_PATCH_10_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000040)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_TME_ROM_PATCH_13_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_TME_ROM_PATCH_13_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_TME_ROM_PATCH_12_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_LSB_TME_ROM_PATCH_12_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000044)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_TME_ROM_PATCH_15_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_TME_ROM_PATCH_15_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_TME_ROM_PATCH_14_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW3_MSB_TME_ROM_PATCH_14_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000048)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_TME_ROM_PATCH_17_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_TME_ROM_PATCH_17_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_TME_ROM_PATCH_16_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_LSB_TME_ROM_PATCH_16_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000004c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_TME_ROM_PATCH_19_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_TME_ROM_PATCH_19_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_TME_ROM_PATCH_18_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW4_MSB_TME_ROM_PATCH_18_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000050)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_TME_ROM_PATCH_21_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_TME_ROM_PATCH_21_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_TME_ROM_PATCH_20_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_LSB_TME_ROM_PATCH_20_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000054)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_TME_ROM_PATCH_23_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_TME_ROM_PATCH_23_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_TME_ROM_PATCH_22_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW5_MSB_TME_ROM_PATCH_22_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000058)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_TME_ROM_PATCH_25_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_TME_ROM_PATCH_25_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_TME_ROM_PATCH_24_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_LSB_TME_ROM_PATCH_24_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000005c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_TME_ROM_PATCH_27_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_TME_ROM_PATCH_27_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_TME_ROM_PATCH_26_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW6_MSB_TME_ROM_PATCH_26_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000060)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_TME_ROM_PATCH_29_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_TME_ROM_PATCH_29_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_TME_ROM_PATCH_28_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_LSB_TME_ROM_PATCH_28_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000064)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_TME_ROM_PATCH_31_ADDR_BMSK                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_TME_ROM_PATCH_31_ADDR_SHFT                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_TME_ROM_PATCH_30_ADDR_BMSK                           0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW7_MSB_TME_ROM_PATCH_30_ADDR_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000068)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_TME_ROM_PATCH_0_DATA_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_LSB_TME_ROM_PATCH_0_DATA_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000006c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_TME_ROM_PATCH_1_DATA_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW8_MSB_TME_ROM_PATCH_1_DATA_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000070)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_TME_ROM_PATCH_2_DATA_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_LSB_TME_ROM_PATCH_2_DATA_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000074)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_TME_ROM_PATCH_3_DATA_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW9_MSB_TME_ROM_PATCH_3_DATA_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000078)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_TME_ROM_PATCH_4_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_LSB_TME_ROM_PATCH_4_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000007c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_TME_ROM_PATCH_5_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW10_MSB_TME_ROM_PATCH_5_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000080)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_TME_ROM_PATCH_6_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_LSB_TME_ROM_PATCH_6_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000084)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_TME_ROM_PATCH_7_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW11_MSB_TME_ROM_PATCH_7_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000088)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_TME_ROM_PATCH_8_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_LSB_TME_ROM_PATCH_8_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000008c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_TME_ROM_PATCH_9_DATA_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW12_MSB_TME_ROM_PATCH_9_DATA_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000090)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_TME_ROM_PATCH_10_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_LSB_TME_ROM_PATCH_10_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000094)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_TME_ROM_PATCH_11_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW13_MSB_TME_ROM_PATCH_11_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000098)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_TME_ROM_PATCH_12_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_LSB_TME_ROM_PATCH_12_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000009c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_TME_ROM_PATCH_13_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW14_MSB_TME_ROM_PATCH_13_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000a0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_TME_ROM_PATCH_14_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_LSB_TME_ROM_PATCH_14_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000a4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_TME_ROM_PATCH_15_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW15_MSB_TME_ROM_PATCH_15_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000a8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_TME_ROM_PATCH_16_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_LSB_TME_ROM_PATCH_16_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000ac)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_TME_ROM_PATCH_17_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW16_MSB_TME_ROM_PATCH_17_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000b0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_TME_ROM_PATCH_18_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_LSB_TME_ROM_PATCH_18_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000b4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_TME_ROM_PATCH_19_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW17_MSB_TME_ROM_PATCH_19_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000b8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_TME_ROM_PATCH_20_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_LSB_TME_ROM_PATCH_20_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000bc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_TME_ROM_PATCH_21_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW18_MSB_TME_ROM_PATCH_21_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000c0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_TME_ROM_PATCH_22_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_LSB_TME_ROM_PATCH_22_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000c4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_TME_ROM_PATCH_23_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW19_MSB_TME_ROM_PATCH_23_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000c8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_TME_ROM_PATCH_24_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_LSB_TME_ROM_PATCH_24_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000cc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_TME_ROM_PATCH_25_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW20_MSB_TME_ROM_PATCH_25_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000d0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_TME_ROM_PATCH_26_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_LSB_TME_ROM_PATCH_26_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000d4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_TME_ROM_PATCH_27_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW21_MSB_TME_ROM_PATCH_27_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000d8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_TME_ROM_PATCH_28_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_LSB_TME_ROM_PATCH_28_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000dc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_TME_ROM_PATCH_29_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW22_MSB_TME_ROM_PATCH_29_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000e0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_TME_ROM_PATCH_30_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_LSB_TME_ROM_PATCH_30_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000e4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_TME_ROM_PATCH_31_DATA_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW23_MSB_TME_ROM_PATCH_31_DATA_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000e8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_31_ENABLE_BMSK                    0x80000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_31_ENABLE_SHFT                          0x1f
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_30_ENABLE_BMSK                    0x40000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_30_ENABLE_SHFT                          0x1e
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_29_ENABLE_BMSK                    0x20000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_29_ENABLE_SHFT                          0x1d
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_28_ENABLE_BMSK                    0x10000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_28_ENABLE_SHFT                          0x1c
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_27_ENABLE_BMSK                     0x8000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_27_ENABLE_SHFT                          0x1b
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_26_ENABLE_BMSK                     0x4000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_26_ENABLE_SHFT                          0x1a
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_25_ENABLE_BMSK                     0x2000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_25_ENABLE_SHFT                          0x19
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_24_ENABLE_BMSK                     0x1000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_24_ENABLE_SHFT                          0x18
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_23_ENABLE_BMSK                      0x800000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_23_ENABLE_SHFT                          0x17
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_22_ENABLE_BMSK                      0x400000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_22_ENABLE_SHFT                          0x16
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_21_ENABLE_BMSK                      0x200000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_21_ENABLE_SHFT                          0x15
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_20_ENABLE_BMSK                      0x100000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_20_ENABLE_SHFT                          0x14
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_19_ENABLE_BMSK                       0x80000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_19_ENABLE_SHFT                          0x13
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_18_ENABLE_BMSK                       0x40000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_18_ENABLE_SHFT                          0x12
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_17_ENABLE_BMSK                       0x20000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_17_ENABLE_SHFT                          0x11
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_16_ENABLE_BMSK                       0x10000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_16_ENABLE_SHFT                          0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_15_ENABLE_BMSK                        0x8000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_15_ENABLE_SHFT                           0xf
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_14_ENABLE_BMSK                        0x4000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_14_ENABLE_SHFT                           0xe
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_13_ENABLE_BMSK                        0x2000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_13_ENABLE_SHFT                           0xd
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_12_ENABLE_BMSK                        0x1000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_12_ENABLE_SHFT                           0xc
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_11_ENABLE_BMSK                         0x800
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_11_ENABLE_SHFT                           0xb
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_10_ENABLE_BMSK                         0x400
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_10_ENABLE_SHFT                           0xa
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_9_ENABLE_BMSK                          0x200
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_9_ENABLE_SHFT                            0x9
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_8_ENABLE_BMSK                          0x100
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_8_ENABLE_SHFT                            0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_7_ENABLE_BMSK                           0x80
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_7_ENABLE_SHFT                            0x7
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_6_ENABLE_BMSK                           0x40
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_6_ENABLE_SHFT                            0x6
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_5_ENABLE_BMSK                           0x20
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_5_ENABLE_SHFT                            0x5
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_4_ENABLE_BMSK                           0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_4_ENABLE_SHFT                            0x4
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_3_ENABLE_BMSK                            0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_3_ENABLE_SHFT                            0x3
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_2_ENABLE_BMSK                            0x4
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_2_ENABLE_SHFT                            0x2
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_1_ENABLE_BMSK                            0x2
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_1_ENABLE_SHFT                            0x1
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_0_ENABLE_BMSK                            0x1
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_LSB_TME_ROM_PATCH_0_ENABLE_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000ec)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_OTP_TME_1D_BMSK                                 0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1D_ROW24_MSB_OTP_TME_1D_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000f0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_TME_ROM_PATCH_VERSION_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_LSB_TME_ROM_PATCH_VERSION_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000f4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_OTP_TME_1Z_BMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_1Z_MSB_OTP_TME_1Z_SHFT                                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000f8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_OEM_MRC_HASH_31_0_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_LSB_OEM_MRC_HASH_31_0_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000000fc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_OEM_MRC_HASH_63_32_BMSK                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW0_MSB_OEM_MRC_HASH_63_32_SHFT                                  0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000100)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_OEM_MRC_HASH_95_64_BMSK                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_LSB_OEM_MRC_HASH_95_64_SHFT                                  0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000104)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_OEM_MRC_HASH_127_96_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW1_MSB_OEM_MRC_HASH_127_96_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000108)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_OEM_MRC_HASH_159_128_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_LSB_OEM_MRC_HASH_159_128_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000010c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_OEM_MRC_HASH_191_160_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW2_MSB_OEM_MRC_HASH_191_160_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000110)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_OEM_MRC_HASH_223_192_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_LSB_OEM_MRC_HASH_223_192_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000114)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_OEM_MRC_HASH_255_224_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW3_MSB_OEM_MRC_HASH_255_224_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000118)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_OEM_MRC_HASH_287_256_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_LSB_OEM_MRC_HASH_287_256_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000011c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_OEM_MRC_HASH_319_288_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW4_MSB_OEM_MRC_HASH_319_288_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000120)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_OEM_MRC_HASH_351_320_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_LSB_OEM_MRC_HASH_351_320_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000124)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_OEM_MRC_HASH_383_352_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW5_MSB_OEM_MRC_HASH_383_352_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000128)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_OEM_MRC_HASH_415_384_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_LSB_OEM_MRC_HASH_415_384_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000012c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_OEM_MRC_HASH_447_416_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW6_MSB_OEM_MRC_HASH_447_416_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000130)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_OEM_MRC_HASH_479_448_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_LSB_OEM_MRC_HASH_479_448_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000134)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_OEM_MRC_HASH_511_480_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW7_MSB_OEM_MRC_HASH_511_480_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000138)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_OEM_ID_BMSK                                       0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_OEM_ID_SHFT                                             0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_DEBUG_DISABLE_VECTOR_BMSK                             0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_LSB_DEBUG_DISABLE_VECTOR_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000013c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OTP_TME_2_BMSK                                    0xfe000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OTP_TME_2_SHFT                                          0x19
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OPINT_FORCE_BTSS_AUTH_BMSK                         0x1000000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OPINT_FORCE_BTSS_AUTH_SHFT                              0x18
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OEM_SECURITY_POLICY_BMSK                            0xff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OEM_SECURITY_POLICY_SHFT                                0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OEM_PRODUCT_ID_BMSK                                   0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2_ROW8_MSB_OEM_PRODUCT_ID_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000140)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_CHIP_UNIQUE_ID_31_0_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_LSB_CHIP_UNIQUE_ID_31_0_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000144)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_CHIP_UNIQUE_ID_63_32_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2A_MSB_CHIP_UNIQUE_ID_63_32_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000148)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_SKP2_SIGNATURE_31_0_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_LSB_SKP2_SIGNATURE_31_0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000014c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_SKP2_SIGNATURE_63_32_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW0_MSB_SKP2_SIGNATURE_63_32_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000150)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_SKP2_SIGNATURE_95_64_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_LSB_SKP2_SIGNATURE_95_64_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000154)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_SKP2_SIGNATURE_127_96_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW1_MSB_SKP2_SIGNATURE_127_96_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000158)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_SKP2_SIGNATURE_159_128_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_LSB_SKP2_SIGNATURE_159_128_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000015c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_SKP2_SIGNATURE_191_160_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW2_MSB_SKP2_SIGNATURE_191_160_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000160)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_SKP2_SIGNATURE_223_192_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_LSB_SKP2_SIGNATURE_223_192_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000164)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_SKP2_SIGNATURE_255_224_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW3_MSB_SKP2_SIGNATURE_255_224_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000168)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_SKP2_SIGNATURE_287_256_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_LSB_SKP2_SIGNATURE_287_256_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000016c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_SKP2_SIGNATURE_319_288_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW4_MSB_SKP2_SIGNATURE_319_288_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000170)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_SKP2_SIGNATURE_351_320_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_LSB_SKP2_SIGNATURE_351_320_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000174)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_SKP2_SIGNATURE_383_352_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW5_MSB_SKP2_SIGNATURE_383_352_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000178)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_SKP2_SIGNATURE_415_384_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_LSB_SKP2_SIGNATURE_415_384_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000017c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_SKP2_SIGNATURE_447_416_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW6_MSB_SKP2_SIGNATURE_447_416_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000180)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_SKP2_SIGNATURE_479_448_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_LSB_SKP2_SIGNATURE_479_448_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000184)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_SKP2_SIGNATURE_511_480_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2B_ROW7_MSB_SKP2_SIGNATURE_511_480_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000188)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_OEM_PRODUCT_SEED_31_0_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_LSB_OEM_PRODUCT_SEED_31_0_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000018c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_OEM_PRODUCT_SEED_63_32_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW0_MSB_OEM_PRODUCT_SEED_63_32_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000190)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_OEM_PRODUCT_SEED_95_64_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_LSB_OEM_PRODUCT_SEED_95_64_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000194)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_OEM_PRODUCT_SEED_127_96_BMSK                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW1_MSB_OEM_PRODUCT_SEED_127_96_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000198)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_OEM_PRODUCT_SEED_159_128_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_LSB_OEM_PRODUCT_SEED_159_128_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000019c)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_OEM_PRODUCT_SEED_191_160_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW2_MSB_OEM_PRODUCT_SEED_191_160_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001a0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_OEM_PRODUCT_SEED_223_192_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_LSB_OEM_PRODUCT_SEED_223_192_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001a4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_OEM_PRODUCT_SEED_255_224_BMSK                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_2C_ROW3_MSB_OEM_PRODUCT_SEED_255_224_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001a8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_OTP_TME_3_31_8_BMSK                                    0xffffff00
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_OTP_TME_3_31_8_SHFT                                           0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_OEM_LIFE_CYCLE_STATE_BMSK                                    0xff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_LSB_OEM_LIFE_CYCLE_STATE_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001ac)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_OTP_TME_3_63_32_BMSK                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_3_MSB_OTP_TME_3_63_32_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001b0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_OTP_TME_4_31_16_BMSK                                   0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_OTP_TME_4_31_16_SHFT                                         0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_QC_ROOT_STATE_VECTOR_BMSK                                  0xff00
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_QC_ROOT_STATE_VECTOR_SHFT                                     0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_OEM_MRC_STATE_VECTOR_BMSK                                    0xff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_LSB_OEM_MRC_STATE_VECTOR_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001b4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_OTP_TME_4_63_32_BMSK                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4_MSB_OTP_TME_4_63_32_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001b8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_IMAGE_VERSIONS_31_0_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_LSB_IMAGE_VERSIONS_31_0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001bc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_IMAGE_VERSIONS_63_32_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW0_MSB_IMAGE_VERSIONS_63_32_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001c0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_IMAGE_VERSIONS_95_64_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_LSB_IMAGE_VERSIONS_95_64_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001c4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_IMAGE_VERSIONS_127_96_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4A_ROW1_MSB_IMAGE_VERSIONS_127_96_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001c8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_OTP_TME_4Z_31_8_BMSK                                  0xffffff00
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_OTP_TME_4Z_31_8_SHFT                                         0x8
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_RTL_SVCS_KEY_STATE_VECTOR_BMSK                              0xff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_LSB_RTL_SVCS_KEY_STATE_VECTOR_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_ADDR                                                  (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001cc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_RMSK                                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_OTP_TME_4Z_63_32_BMSK                                 0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_4Z_MSB_OTP_TME_4Z_63_32_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001d0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_OTP_TME_5_31_16_BMSK                                   0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_OTP_TME_5_31_16_SHFT                                         0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_DEBUG_RE_ENABLE_VECTOR_BMSK                                0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_LSB_DEBUG_RE_ENABLE_VECTOR_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001d4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_OTP_TME_5_63_32_BMSK                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_5_MSB_OTP_TME_5_63_32_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001d8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_OTP_TME_6_31_0_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_LSB_OTP_TME_6_31_0_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001dc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_OTP_TME_6_63_32_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW0_MSB_OTP_TME_6_63_32_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001e0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_OTP_TME_6_95_64_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_LSB_OTP_TME_6_95_64_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001e4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_OTP_TME_6_127_96_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW1_MSB_OTP_TME_6_127_96_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001e8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_OTP_TME_6_159_128_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_LSB_OTP_TME_6_159_128_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001ec)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_OTP_TME_6_191_160_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW2_MSB_OTP_TME_6_191_160_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001f0)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_OTP_TME_6_223_192_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_LSB_OTP_TME_6_223_192_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001f4)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_OTP_TME_6_255_224_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_6_ROW3_MSB_OTP_TME_6_255_224_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001f8)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_INDV_READ_DISABLE_BMSK                                 0xffff0000
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_INDV_READ_DISABLE_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_GRP_WRITE_DISABLE_BMSK                                     0xffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_LSB_GRP_WRITE_DISABLE_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_ADDR                                                   (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000001fc)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_RMSK                                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_OTP_TME_0_BMSK                                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_OTP_TME_0_MSB_OTP_TME_0_SHFT                                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000200)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_UPDATE_ADDRESS_BMSK                                 0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_LSB_UPDATE_ADDRESS_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000204)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_UPDATE_SIZE_BMSK                                    0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW0_MSB_UPDATE_SIZE_SHFT                                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000208)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_UPDATE_FLAGS_BMSK                                   0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_LSB_UPDATE_FLAGS_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000020c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_MTP_TME_127_96_BMSK                                 0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW1_MSB_MTP_TME_127_96_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000210)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_MTP_TME_159_BMSK                                    0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_MTP_TME_159_SHFT                                          0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_AUX_WARM_CTRL0_SET1_BMSK                            0x7fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_AUX_WARM_CTRL0_SET1_SHFT                                  0x10
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_MTP_TME_143_BMSK                                        0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_MTP_TME_143_SHFT                                           0xf
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_AUX_WARM_CTRL0_SET0_BMSK                                0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_LSB_AUX_WARM_CTRL0_SET0_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000214)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_MTP_TME_191_BMSK                                    0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_MTP_TME_191_SHFT                                          0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL5_SET1_BMSK                            0x70000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL5_SET1_SHFT                                  0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL1_SET1_BMSK                             0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL1_SET1_SHFT                                  0x10
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_MTP_TME_175_BMSK                                        0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_MTP_TME_175_SHFT                                           0xf
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL5_SET0_BMSK                                0x7000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL5_SET0_SHFT                                   0xc
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL1_SET0_BMSK                                 0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW2_MSB_AUX_WARM_CTRL1_SET0_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000218)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_AUX_WARM_DRV_BMSK                                   0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_AUX_WARM_DRV_SHFT                                         0x10
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_MTP_TME_207_BMSK                                        0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_MTP_TME_207_SHFT                                           0xf
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_AUX_WARM_CTRL2_BMSK                                     0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_LSB_AUX_WARM_CTRL2_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000021c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_MTP_TME_255_254_BMSK                                0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_MTP_TME_255_254_SHFT                                      0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL8_BMSK                                 0x3fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL8_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_MTP_TME_239_BMSK                                        0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_MTP_TME_239_SHFT                                           0xf
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL7_BMSK                                     0x7fc0
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL7_SHFT                                        0x6
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL6_SET1_BMSK                                  0x38
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL6_SET1_SHFT                                   0x3
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL6_SET0_BMSK                                   0x7
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW3_MSB_AUX_WARM_CTRL6_SET0_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000220)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_MTP_TME_287_286_BMSK                                0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_MTP_TME_287_286_SHFT                                      0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_AUX_WARM_CTRL9_BMSK                                 0x3fc00000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_AUX_WARM_CTRL9_SHFT                                       0x16
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_MTP_TME_277_BMSK                                      0x200000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_MTP_TME_277_SHFT                                          0x15
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_AUX_WARM_DRV_CTRL_BMSK                                0x1fffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_LSB_AUX_WARM_DRV_CTRL_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000224)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_MTP_TME_319_318_BMSK                                0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_MTP_TME_319_318_SHFT                                      0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_AUX_WARM_TMUX_CTRL0_BMSK                            0x3ff00000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_AUX_WARM_TMUX_CTRL0_SHFT                                  0x14
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_MTP_TME_307_305_BMSK                                   0xe0000
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_MTP_TME_307_305_SHFT                                      0x11
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_AUX_WARM_GHMIEHR_OR_XTLCL_BMSK                         0x1ffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW4_MSB_AUX_WARM_GHMIEHR_OR_XTLCL_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000228)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_MTP_TME_351_328_BMSK                                0xffffff00
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_MTP_TME_351_328_SHFT                                       0x8
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_PMU_FOSC_TRIM_FOUT_BMSK                                   0xff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_LSB_PMU_FOSC_TRIM_FOUT_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000022c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_MTP_TME_383_352_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW5_MSB_MTP_TME_383_352_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000230)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_MTP_TME_415_384_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_LSB_MTP_TME_415_384_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000234)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_MTP_TME_447_416_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW6_MSB_MTP_TME_447_416_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000238)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_MTP_TME_479_448_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_LSB_MTP_TME_479_448_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000023c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_MTP_TME_511_480_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW7_MSB_MTP_TME_511_480_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000240)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_MTP_TME_543_512_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_LSB_MTP_TME_543_512_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000244)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_MTP_TME_575_544_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW8_MSB_MTP_TME_575_544_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000248)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_MTP_TME_607_576_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_LSB_MTP_TME_607_576_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_ADDR                                                (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000024c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_RMSK                                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_MTP_TME_639_608_BMSK                                0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW9_MSB_MTP_TME_639_608_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000250)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_MTP_TME_671_640_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_LSB_MTP_TME_671_640_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000254)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_MTP_TME_703_672_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW10_MSB_MTP_TME_703_672_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000258)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_MTP_TME_735_704_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_LSB_MTP_TME_735_704_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000025c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_MTP_TME_767_736_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW11_MSB_MTP_TME_767_736_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000260)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_MTP_TME_799_768_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_LSB_MTP_TME_799_768_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000264)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_MTP_TME_831_800_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW12_MSB_MTP_TME_831_800_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000268)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_MTP_TME_863_832_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_LSB_MTP_TME_863_832_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000026c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_MTP_TME_895_864_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW13_MSB_MTP_TME_895_864_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000270)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_MTP_TME_927_896_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_LSB_MTP_TME_927_896_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000274)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_MTP_TME_959_928_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW14_MSB_MTP_TME_959_928_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000278)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_MTP_TME_991_960_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_LSB_MTP_TME_991_960_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000027c)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_MTP_TME_1023_992_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_TME_ROW15_MSB_MTP_TME_1023_992_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000280)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_MTP_BTSS_31_1_BMSK                                 0xfffffffe
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_MTP_BTSS_31_1_SHFT                                        0x1
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_DEBUG_DISABLE_BMSK                                        0x1
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_LSB_DEBUG_DISABLE_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000284)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_MTP_BTSS_63_62_BMSK                                0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_MTP_BTSS_63_62_SHFT                                      0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_1V0_CODE_1_BMSK                        0x3ff00000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_1V0_CODE_1_SHFT                              0x14
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_0V9_CODE_2_BMSK                           0xffc00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_0V9_CODE_2_SHFT                               0xa
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_0V9_CODE_1_BMSK                             0x3ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW0_MSB_RF_BIST_ADC_0V9_CODE_1_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000288)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_MTP_BTSS_95_94_BMSK                                0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_MTP_BTSS_95_94_SHFT                                      0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V1_CODE_2_BMSK                        0x3ff00000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V1_CODE_2_SHFT                              0x14
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V1_CODE_1_BMSK                           0xffc00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V1_CODE_1_SHFT                               0xa
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V0_CODE_2_BMSK                             0x3ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_LSB_RF_BIST_ADC_1V0_CODE_2_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000028c)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_RF_BIST_RESISTOR_100K_BMSK                         0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_RF_BIST_RESISTOR_100K_SHFT                               0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_RF_BIST_RESISTOR_15K_BMSK                              0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW1_MSB_RF_BIST_RESISTOR_15K_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000290)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_MTP_BTSS_159_158_BMSK                              0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_MTP_BTSS_159_158_SHFT                                    0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_ADC_1V0_TRIM_BMSK                          0x3f000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_ADC_1V0_TRIM_SHFT                                0x18
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_MTP_BTSS_151_150_BMSK                                0xc00000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_MTP_BTSS_151_150_SHFT                                    0x16
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_ADC_0V9_TRIM_BMSK                            0x3f0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_ADC_0V9_TRIM_SHFT                                0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_RESISTOR_500K_BMSK                             0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_LSB_RF_BIST_RESISTOR_500K_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000294)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_3_BMSK                    0xff000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_3_SHFT                          0x18
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_1_BMSK                      0xff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_1_SHFT                          0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_2_BMSK                        0xff00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_2_SHFT                           0x8
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_0_BMSK                          0xff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW2_MSB_RX_IQ_CORR_COEF_CROSS_GM_0_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000298)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_7_BMSK                    0xff000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_7_SHFT                          0x18
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_5_BMSK                      0xff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_5_SHFT                          0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_6_BMSK                        0xff00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_6_SHFT                           0x8
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_4_BMSK                          0xff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_LSB_RX_IQ_CORR_COEF_CROSS_GM_4_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000029c)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_MTP_BTSS_255_246_BMSK                              0xffc00000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_MTP_BTSS_255_246_SHFT                                    0x16
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_RF_BIST_ADC_1V1_TRIM_BMSK                            0x3f0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_RF_BIST_ADC_1V1_TRIM_SHFT                                0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_IQ_IMB_QUADRATURE_ANALOG_CORR_BMSK                     0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_IQ_IMB_QUADRATURE_ANALOG_CORR_SHFT                        0xc
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_IQ_IMB_IN_PHASE_ANALOG_CORR_BMSK                        0xf00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_IQ_IMB_IN_PHASE_ANALOG_CORR_SHFT                          0x8
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_RX_IQ_CORR_COEF_CROSS_GM_8_BMSK                          0xff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW3_MSB_RX_IQ_CORR_COEF_CROSS_GM_8_SHFT                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002a0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_MTP_BTSS_287_BMSK                                  0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_MTP_BTSS_287_SHFT                                        0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RF_BT5_DI_PMU_VREG_GP_TRIM_HV_BMSK                 0x7e000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RF_BT5_DI_PMU_VREG_GP_TRIM_HV_SHFT                       0x19
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RX_IQ_CORR_COEF_DIAG_GM_1_BMSK                      0x1ff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RX_IQ_CORR_COEF_DIAG_GM_1_SHFT                           0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_MTP_BTSS_271_BMSK                                      0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_MTP_BTSS_271_SHFT                                         0xf
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RF_BT5_DI_PMU_TRIM_VREF_SV_BMSK                        0x7e00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RF_BT5_DI_PMU_TRIM_VREF_SV_SHFT                           0x9
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RX_IQ_CORR_COEF_DIAG_GM_0_BMSK                          0x1ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_LSB_RX_IQ_CORR_COEF_DIAG_GM_0_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002a4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_ANA_IQ_TRIM_VALID_BMSK                             0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_ANA_IQ_TRIM_VALID_SHFT                                   0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RF_BT5_DI_LO_LF_VREG_TRIM_HV_BMSK                  0x7e000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RF_BT5_DI_LO_LF_VREG_TRIM_HV_SHFT                        0x19
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RX_IQ_CORR_COEF_DIAG_GM_3_BMSK                      0x1ff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RX_IQ_CORR_COEF_DIAG_GM_3_SHFT                           0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_MTP_BTSS_303_BMSK                                      0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_MTP_BTSS_303_SHFT                                         0xf
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RF_BT5_DI_LO_VCO_VREG_TRIM_HV_BMSK                     0x7e00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RF_BT5_DI_LO_VCO_VREG_TRIM_HV_SHFT                        0x9
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RX_IQ_CORR_COEF_DIAG_GM_2_BMSK                          0x1ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW4_MSB_RX_IQ_CORR_COEF_DIAG_GM_2_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002a8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_MTP_BTSS_351_BMSK                                  0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_MTP_BTSS_351_SHFT                                        0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RF_BT5_DI_RXBB_VREG_TRIM_HV_BMSK                   0x7e000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RF_BT5_DI_RXBB_VREG_TRIM_HV_SHFT                         0x19
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RX_IQ_CORR_COEF_DIAG_GM_5_BMSK                      0x1ff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RX_IQ_CORR_COEF_DIAG_GM_5_SHFT                           0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_MTP_BTSS_335_BMSK                                      0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_MTP_BTSS_335_SHFT                                         0xf
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RF_BT5_DI_LO_DIVIDERS_VREG_TRIM_HV_BMSK                0x7e00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RF_BT5_DI_LO_DIVIDERS_VREG_TRIM_HV_SHFT                   0x9
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RX_IQ_CORR_COEF_DIAG_GM_4_BMSK                          0x1ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_LSB_RX_IQ_CORR_COEF_DIAG_GM_4_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002ac)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_MTP_BTSS_383_BMSK                                  0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_MTP_BTSS_383_SHFT                                        0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RF_BT5_DI_LODIST_VREG_TRIM_HV_BMSK                 0x7e000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RF_BT5_DI_LODIST_VREG_TRIM_HV_SHFT                       0x19
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RX_IQ_CORR_COEF_DIAG_GM_7_BMSK                      0x1ff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RX_IQ_CORR_COEF_DIAG_GM_7_SHFT                           0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_MTP_BTSS_367_BMSK                                      0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_MTP_BTSS_367_SHFT                                         0xf
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RF_BT5_DI_RF_RX_VREG_RXFE_TRIM_HV_BMSK                 0x7e00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RF_BT5_DI_RF_RX_VREG_RXFE_TRIM_HV_SHFT                    0x9
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RX_IQ_CORR_COEF_DIAG_GM_6_BMSK                          0x1ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW5_MSB_RX_IQ_CORR_COEF_DIAG_GM_6_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002b0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_415_414_BMSK                              0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_415_414_SHFT                                    0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RF_BT5_DI_RF_TX_VREG_TXDIG_TRIM_HV_BMSK            0x3f000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RF_BT5_DI_RF_TX_VREG_TXDIG_TRIM_HV_SHFT                  0x18
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_407_406_BMSK                                0xc00000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_407_406_SHFT                                    0x16
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RF_BT5_DI_RF_TX_VREG_DRV_TRIM_HV_BMSK                0x3f0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RF_BT5_DI_RF_TX_VREG_DRV_TRIM_HV_SHFT                    0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_399_393_BMSK                                  0xfe00
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_MTP_BTSS_399_393_SHFT                                     0x9
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RX_IQ_CORR_COEF_DIAG_GM_8_BMSK                          0x1ff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_LSB_RX_IQ_CORR_COEF_DIAG_GM_8_SHFT                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002b4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_RING_OSC_FREQ_MHZ_BMSK                             0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_RING_OSC_FREQ_MHZ_SHFT                                   0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_MTP_BTSS_431_416_BMSK                                  0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW6_MSB_MTP_BTSS_431_416_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002b8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_BD_ADDR_31_0_BMSK                                  0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_LSB_BD_ADDR_31_0_SHFT                                         0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002bc)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_SKU_ID_BMSK                                        0xff000000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_SKU_ID_SHFT                                              0x18
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_P_CODE_BMSK                                          0xff0000
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_P_CODE_SHFT                                              0x10
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_BD_ADDR_47_32_BMSK                                     0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW7_MSB_BD_ADDR_47_32_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002c0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_MTP_BTSS_543_512_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_LSB_MTP_BTSS_543_512_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002c4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_MTP_BTSS_575_544_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW8_MSB_MTP_BTSS_575_544_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002c8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_MTP_BTSS_607_576_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_LSB_MTP_BTSS_607_576_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_ADDR                                               (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002cc)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_RMSK                                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_MTP_BTSS_639_608_BMSK                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW9_MSB_MTP_BTSS_639_608_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002d0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_MTP_BTSS_671_640_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_LSB_MTP_BTSS_671_640_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002d4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_MTP_BTSS_703_672_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW10_MSB_MTP_BTSS_703_672_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002d8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_MTP_BTSS_735_704_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_LSB_MTP_BTSS_735_704_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002dc)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_MTP_BTSS_767_736_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW11_MSB_MTP_BTSS_767_736_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002e0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_MTP_BTSS_799_768_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_LSB_MTP_BTSS_799_768_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002e4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_MTP_BTSS_831_800_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW12_MSB_MTP_BTSS_831_800_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002e8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_MTP_BTSS_863_832_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_LSB_MTP_BTSS_863_832_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002ec)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_MTP_BTSS_895_864_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW13_MSB_MTP_BTSS_895_864_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002f0)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_MTP_BTSS_927_896_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_LSB_MTP_BTSS_927_896_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002f4)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_MTP_BTSS_959_928_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW14_MSB_MTP_BTSS_959_928_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002f8)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_MTP_BTSS_991_960_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_LSB_MTP_BTSS_991_960_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_ADDR                                              (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000002fc)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_RMSK                                              0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_MTP_BTSS_1023_992_BMSK                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_BTSS_ROW15_MSB_MTP_BTSS_1023_992_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000300)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_MTP_APSS_R_31_BMSK                               0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_MTP_APSS_R_31_SHFT                                     0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_AUX_COLD_CTRL0_SET1_BMSK                         0x7fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_AUX_COLD_CTRL0_SET1_SHFT                               0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_MTP_APSS_R_15_BMSK                                   0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_MTP_APSS_R_15_SHFT                                      0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_AUX_COLD_CTRL0_SET0_BMSK                             0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_LSB_AUX_COLD_CTRL0_SET0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000304)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_MTP_APSS_R_63_BMSK                               0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_MTP_APSS_R_63_SHFT                                     0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL5_SET1_BMSK                         0x70000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL5_SET1_SHFT                               0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL1_SET1_BMSK                          0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL1_SET1_SHFT                               0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_MTP_APSS_R_47_BMSK                                   0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_MTP_APSS_R_47_SHFT                                      0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL5_SET0_BMSK                             0x7000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL5_SET0_SHFT                                0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL1_SET0_BMSK                              0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW0_MSB_AUX_COLD_CTRL1_SET0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000308)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_AUX_COLD_DRV_BMSK                                0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_AUX_COLD_DRV_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_MTP_APSS_R_79_BMSK                                   0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_MTP_APSS_R_79_SHFT                                      0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_AUX_COLD_CTRL2_BMSK                                  0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_LSB_AUX_COLD_CTRL2_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000030c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_MTP_APSS_R_127_126_BMSK                          0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_MTP_APSS_R_127_126_SHFT                                0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL8_BMSK                              0x3fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL8_SHFT                                    0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_MTP_APSS_R_111_BMSK                                  0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_MTP_APSS_R_111_SHFT                                     0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL7_BMSK                                  0x7fc0
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL7_SHFT                                     0x6
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL6_SET1_BMSK                               0x38
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL6_SET1_SHFT                                0x3
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL6_SET0_BMSK                                0x7
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW1_MSB_AUX_COLD_CTRL6_SET0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000310)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_MTP_APSS_R_159_158_BMSK                          0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_MTP_APSS_R_159_158_SHFT                                0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_AUX_COLD_CTRL9_BMSK                              0x3fc00000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_AUX_COLD_CTRL9_SHFT                                    0x16
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_MTP_APSS_R_149_BMSK                                0x200000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_MTP_APSS_R_149_SHFT                                    0x15
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_AUX_COLD_DRV_CTRL_BMSK                             0x1fffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_LSB_AUX_COLD_DRV_CTRL_SHFT                                  0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000314)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_MTP_APSS_R_191_190_BMSK                          0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_MTP_APSS_R_191_190_SHFT                                0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_AUX_COLD_TMUX_CTRL0_BMSK                         0x3ff00000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_AUX_COLD_TMUX_CTRL0_SHFT                               0x14
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_MTP_APSS_R_179_177_BMSK                             0xe0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_MTP_APSS_R_179_177_SHFT                                0x11
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_AUX_COLD_GHMIEHR_OR_XTLCL_BMSK                      0x1ffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW2_MSB_AUX_COLD_GHMIEHR_OR_XTLCL_SHFT                          0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000318)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_BIST_ADC_HIGH_BMSK                               0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_BIST_ADC_HIGH_SHFT                                     0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_BIST_ADC_LOW_BMSK                                    0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_LSB_BIST_ADC_LOW_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000031c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_BIST_MUX_100K_BMSK                               0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_BIST_MUX_100K_SHFT                                     0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_BIST_MUX_10K_BMSK                                    0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW3_MSB_BIST_MUX_10K_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000320)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_MTP_APSS_R_287_286_BMSK                          0xc0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_MTP_APSS_R_287_286_SHFT                                0x1e
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_9_BMSK                          0x30000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_9_SHFT                                0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_9_BMSK                            0x8000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_9_SHFT                                 0x1b
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_8_BMSK                           0x6000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_8_SHFT                                0x19
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_8_BMSK                            0x1000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_8_SHFT                                 0x18
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_7_BMSK                            0xc00000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_7_SHFT                                0x16
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_7_BMSK                             0x200000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_7_SHFT                                 0x15
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_6_BMSK                            0x180000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_6_SHFT                                0x13
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_6_BMSK                              0x40000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_6_SHFT                                 0x12
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_5_BMSK                             0x30000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_5_SHFT                                0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_5_BMSK                               0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_5_SHFT                                  0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_4_BMSK                              0x6000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_4_SHFT                                 0xd
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_4_BMSK                               0x1000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_4_SHFT                                  0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_3_BMSK                               0xc00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_3_SHFT                                 0xa
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_3_BMSK                                0x200
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_3_SHFT                                  0x9
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_2_BMSK                               0x180
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_2_SHFT                                 0x7
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_2_BMSK                                 0x40
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_2_SHFT                                  0x6
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_1_BMSK                                0x30
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_1_SHFT                                 0x4
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_1_BMSK                                  0x8
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_1_SHFT                                  0x3
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_0_BMSK                                 0x6
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_VAL_0_SHFT                                 0x1
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_0_BMSK                                  0x1
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_LSB_SMPS_CLK_DIV_EN_0_SHFT                                  0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000324)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_319_316_BMSK                          0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_319_316_SHFT                                0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_LDO_DIG_OFFSET_BMSK                               0xf000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_LDO_DIG_OFFSET_SHFT                                    0x18
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_311_BMSK                                0x800000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_311_SHFT                                    0x17
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_2_BMSK                                0x7f0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_2_SHFT                                    0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_303_BMSK                                  0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_303_SHFT                                     0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_1_BMSK                                  0x7f00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_1_SHFT                                     0x8
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_295_BMSK                                    0x80
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_MTP_APSS_R_295_SHFT                                     0x7
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_0_BMSK                                    0x7f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW4_MSB_SMPS_SEL_TON_0_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000328)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_TS_GRADIENT_BMSK                                 0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_TS_GRADIENT_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_TS_CAL_TEMPERATURE_BMSK                              0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_LSB_TS_CAL_TEMPERATURE_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000032c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_TRIM0_DEFAULT_BMSK                            0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_TRIM0_DEFAULT_SHFT                                  0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_TRIM1_DEFAULT_BMSK                                0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_TRIM1_DEFAULT_SHFT                                   0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_GRADIENT_QUAD_BMSK                                 0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW5_MSB_TS_GRADIENT_QUAD_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000330)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_VBAT_LOAD_CELL_2_BMSK                            0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_VBAT_LOAD_CELL_2_SHFT                                  0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_VBAT_LOAD_CELL_1_BMSK                                0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_LSB_VBAT_LOAD_CELL_1_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000334)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_447_BMSK                              0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_447_SHFT                                    0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_TEMP_1_BMSK                             0x7f000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_TEMP_1_SHFT                                   0x18
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_439_BMSK                                0x800000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_439_SHFT                                    0x17
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_TEMP_0_BMSK                               0x7f0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_TEMP_0_SHFT                                   0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_431_BMSK                                  0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_MTP_APSS_R_431_SHFT                                     0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_2_BMSK                                0x7c00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_2_SHFT                                   0xa
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_1_BMSK                                 0x3e0
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_1_SHFT                                   0x5
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_0_BMSK                                  0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW6_MSB_XTAL_32K_ITFAC_0_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000338)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_MTP_APSS_R_479_472_BMSK                          0xff000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_MTP_APSS_R_479_472_SHFT                                0x18
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_VBAT_SENSE_RATIO_BMSK                              0xff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_VBAT_SENSE_RATIO_SHFT                                  0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_MTP_APSS_R_463_458_BMSK                              0xfc00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_MTP_APSS_R_463_458_SHFT                                 0xa
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_PMU_BIST_ADC_0D6V_REF_BMSK                            0x3ff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_LSB_PMU_BIST_ADC_0D6V_REF_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000033c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_MTP_APSS_R_511_480_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW7_MSB_MTP_APSS_R_511_480_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000340)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_MTP_APSS_R_543_512_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_LSB_MTP_APSS_R_543_512_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000344)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_MTP_APSS_R_575_544_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW8_MSB_MTP_APSS_R_575_544_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000348)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_MTP_APSS_R_607_576_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_LSB_MTP_APSS_R_607_576_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_ADDR                                             (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000034c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_RMSK                                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_MTP_APSS_R_639_608_BMSK                          0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW9_MSB_MTP_APSS_R_639_608_SHFT                                 0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000350)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_MTP_APSS_R_671_640_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_LSB_MTP_APSS_R_671_640_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000354)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_MTP_APSS_R_703_672_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW10_MSB_MTP_APSS_R_703_672_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000358)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_MTP_APSS_R_735_704_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_LSB_MTP_APSS_R_735_704_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000035c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_MTP_APSS_R_767_736_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW11_MSB_MTP_APSS_R_767_736_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000360)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_MTP_APSS_R_799_768_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_LSB_MTP_APSS_R_799_768_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000364)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_MTP_APSS_R_831_800_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW12_MSB_MTP_APSS_R_831_800_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000368)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_MTP_APSS_R_863_832_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_LSB_MTP_APSS_R_863_832_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000036c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_MTP_APSS_R_895_864_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW13_MSB_MTP_APSS_R_895_864_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000370)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_VERSION_NUMBER_BMSK                          0xffe00000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_VERSION_NUMBER_SHFT                                0x15
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_SITE_BMSK                                      0x1f8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_SITE_SHFT                                           0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_YEAR_BMSK                                        0x7e00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_YEAR_SHFT                                           0x9
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_MONTH_BMSK                                        0x1e0
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_MONTH_SHFT                                          0x5
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_DAY_BMSK                                           0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_LSB_FT_DAY_SHFT                                            0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000374)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_WAFER_LOT_31_0_BMSK                             0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW14_MSB_WAFER_LOT_31_0_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000378)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_WAFER_ID_BMSK                                   0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_WAFER_ID_SHFT                                         0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_WAFER_LOT_47_32_BMSK                                0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_LSB_WAFER_LOT_47_32_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000037c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_WAFER_Y_BMSK                                    0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_WAFER_Y_SHFT                                          0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_WAFER_X_BMSK                                        0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_R_ROW15_MSB_WAFER_X_SHFT                                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000380)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_BD_ADDR_31_0_BMSK                               0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_LSB_BD_ADDR_31_0_SHFT                                      0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000384)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_LDO_VMA_SEL_PT_BMSK                             0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_LDO_VMA_SEL_PT_SHFT                                   0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_XTAL_32K_GAIN_BMSK                              0x7e000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_XTAL_32K_GAIN_SHFT                                    0x19
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_XTAL_32K_TRIM_CL_BMSK                            0x1ff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_XTAL_32K_TRIM_CL_SHFT                                 0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_BD_ADDR_47_32_BMSK                                  0xffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW0_MSB_BD_ADDR_47_32_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000388)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_MTP_APSS_RW_95_BMSK                             0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_MTP_APSS_RW_95_SHFT                                   0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_AUX_OEM_DRV_T1_BMSK                             0x7fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_AUX_OEM_DRV_T1_SHFT                                   0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_MTP_APSS_RW_79_BMSK                                 0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_MTP_APSS_RW_79_SHFT                                    0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_AUX_OEM_CTRL3_BMSK                                  0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_LSB_AUX_OEM_CTRL3_SHFT                                     0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000038c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_MTP_APSS_RW_127_124_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_MTP_APSS_RW_127_124_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_AUX_OEM_CTRL4_SET1_BMSK                          0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_AUX_OEM_CTRL4_SET1_SHFT                               0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_MTP_APSS_RW_111_108_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_MTP_APSS_RW_111_108_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_AUX_OEM_CTRL4_SET0_BMSK                              0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW1_MSB_AUX_OEM_CTRL4_SET0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000390)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_MTP_APSS_RW_159_BMSK                            0x80000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_MTP_APSS_RW_159_SHFT                                  0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_AUX_OEM_DRV_T4_BMSK                             0x7fff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_AUX_OEM_DRV_T4_SHFT                                   0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_MTP_APSS_RW_143_BMSK                                0x8000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_MTP_APSS_RW_143_SHFT                                   0xf
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_AUX_OEM_DRV_T3_BMSK                                 0x7fff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_LSB_AUX_OEM_DRV_T3_SHFT                                    0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000394)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_MTP_APSS_RW_191_188_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_MTP_APSS_RW_191_188_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_GPIO_CFG_1_BMSK                                  0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_GPIO_CFG_1_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_MTP_APSS_RW_175_172_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_MTP_APSS_RW_175_172_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_GPIO_CFG_0_BMSK                                      0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW2_MSB_GPIO_CFG_0_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000398)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_MTP_APSS_RW_223_220_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_MTP_APSS_RW_223_220_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_GPIO_CFG_3_BMSK                                  0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_GPIO_CFG_3_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_MTP_APSS_RW_207_204_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_MTP_APSS_RW_207_204_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_GPIO_CFG_2_BMSK                                      0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_LSB_GPIO_CFG_2_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000039c)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_MTP_APSS_RW_255_252_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_MTP_APSS_RW_255_252_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_GPIO_CFG_5_BMSK                                  0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_GPIO_CFG_5_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_MTP_APSS_RW_239_236_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_MTP_APSS_RW_239_236_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_GPIO_CFG_4_BMSK                                      0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW3_MSB_GPIO_CFG_4_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003a0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_MTP_APSS_RW_287_284_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_MTP_APSS_RW_287_284_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_GPIO_CFG_7_BMSK                                  0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_GPIO_CFG_7_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_MTP_APSS_RW_271_268_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_MTP_APSS_RW_271_268_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_GPIO_CFG_6_BMSK                                      0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_LSB_GPIO_CFG_6_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003a4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_MTP_APSS_RW_319_316_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_MTP_APSS_RW_319_316_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_GPIO_CFG_9_BMSK                                  0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_GPIO_CFG_9_SHFT                                       0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_MTP_APSS_RW_303_300_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_MTP_APSS_RW_303_300_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_GPIO_CFG_8_BMSK                                      0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW4_MSB_GPIO_CFG_8_SHFT                                        0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003a8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_MTP_APSS_RW_351_348_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_MTP_APSS_RW_351_348_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_GPIO_CFG_11_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_GPIO_CFG_11_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_MTP_APSS_RW_335_332_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_MTP_APSS_RW_335_332_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_GPIO_CFG_10_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_LSB_GPIO_CFG_10_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003ac)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_MTP_APSS_RW_383_380_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_MTP_APSS_RW_383_380_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_GPIO_CFG_13_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_GPIO_CFG_13_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_MTP_APSS_RW_367_364_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_MTP_APSS_RW_367_364_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_GPIO_CFG_12_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW5_MSB_GPIO_CFG_12_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003b0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_MTP_APSS_RW_415_412_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_MTP_APSS_RW_415_412_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_GPIO_CFG_15_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_GPIO_CFG_15_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_MTP_APSS_RW_399_396_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_MTP_APSS_RW_399_396_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_GPIO_CFG_14_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_LSB_GPIO_CFG_14_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003b4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_MTP_APSS_RW_447_444_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_MTP_APSS_RW_447_444_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_GPIO_CFG_17_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_GPIO_CFG_17_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_MTP_APSS_RW_431_428_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_MTP_APSS_RW_431_428_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_GPIO_CFG_16_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW6_MSB_GPIO_CFG_16_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003b8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_MTP_APSS_RW_479_476_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_MTP_APSS_RW_479_476_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_GPIO_CFG_19_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_GPIO_CFG_19_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_MTP_APSS_RW_463_460_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_MTP_APSS_RW_463_460_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_GPIO_CFG_18_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_LSB_GPIO_CFG_18_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003bc)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_MTP_APSS_RW_511_508_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_MTP_APSS_RW_511_508_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_GPIO_CFG_21_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_GPIO_CFG_21_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_MTP_APSS_RW_495_492_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_MTP_APSS_RW_495_492_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_GPIO_CFG_20_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW7_MSB_GPIO_CFG_20_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003c0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_MTP_APSS_RW_543_540_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_MTP_APSS_RW_543_540_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_GPIO_CFG_23_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_GPIO_CFG_23_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_MTP_APSS_RW_527_524_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_MTP_APSS_RW_527_524_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_GPIO_CFG_22_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_LSB_GPIO_CFG_22_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003c4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_MTP_APSS_RW_575_572_BMSK                        0xf0000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_MTP_APSS_RW_575_572_SHFT                              0x1c
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_GPIO_CFG_25_BMSK                                 0xfff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_GPIO_CFG_25_SHFT                                      0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_MTP_APSS_RW_559_556_BMSK                            0xf000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_MTP_APSS_RW_559_556_SHFT                               0xc
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_GPIO_CFG_24_BMSK                                     0xfff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW8_MSB_GPIO_CFG_24_SHFT                                       0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003c8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_MTP_APSS_RW_607_602_BMSK                        0xfc000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_MTP_APSS_RW_607_602_SHFT                              0x1a
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_GPIO_OE_BMSK                                     0x3ffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_LSB_GPIO_OE_SHFT                                           0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_ADDR                                            (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003cc)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_RMSK                                            0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_MTP_APSS_RW_639_634_BMSK                        0xfc000000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_MTP_APSS_RW_639_634_SHFT                              0x1a
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_GPIO_OUT_BMSK                                    0x3ffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW9_MSB_GPIO_OUT_SHFT                                          0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003d0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_CYCLE_COUNT_BMSK                      0xffff0000
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_CYCLE_COUNT_SHFT                            0x10
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_CYCLE_COUNT_TEMPERATURE_BMSK              0xff00
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_CYCLE_COUNT_TEMPERATURE_SHFT                 0x8
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_MTP_APSS_RW_647_645_BMSK                             0xe0
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_MTP_APSS_RW_647_645_SHFT                              0x5
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_DELAY_BMSK                                  0x1f
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_LSB_XTAL_32K_DELAY_SHFT                                   0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003d4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_MTP_APSS_RW_703_672_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW10_MSB_MTP_APSS_RW_703_672_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003d8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_MTP_APSS_RW_735_704_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_LSB_MTP_APSS_RW_735_704_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003dc)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_MTP_APSS_RW_767_736_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW11_MSB_MTP_APSS_RW_767_736_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003e0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_OEM_MTP_DATA_31_0_BMSK                         0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_LSB_OEM_MTP_DATA_31_0_SHFT                                0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003e4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_OEM_MTP_DATA_63_32_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW12_MSB_OEM_MTP_DATA_63_32_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003e8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_OEM_MTP_DATA_95_64_BMSK                        0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_LSB_OEM_MTP_DATA_95_64_SHFT                               0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003ec)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_OEM_MTP_DATA_127_96_BMSK                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW13_MSB_OEM_MTP_DATA_127_96_SHFT                              0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003f0)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_OEM_MTP_DATA_159_128_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_LSB_OEM_MTP_DATA_159_128_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003f4)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_OEM_MTP_DATA_191_160_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW14_MSB_OEM_MTP_DATA_191_160_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003f8)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_OEM_MTP_DATA_223_192_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_LSB_OEM_MTP_DATA_223_192_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_ADDR                                           (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000003fc)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_RMSK                                           0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_OEM_MTP_DATA_255_224_BMSK                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_MTP_APSS_RW_ROW15_MSB_OEM_MTP_DATA_255_224_SHFT                             0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000400)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_REGISTER_RESTORE_31_0_BMSK                 0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_LSB_REGISTER_RESTORE_31_0_SHFT                        0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000404)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_REGISTER_RESTORE_63_32_BMSK                0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW0_MSB_REGISTER_RESTORE_63_32_SHFT                       0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000408)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_REGISTER_RESTORE_95_64_BMSK                0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_LSB_REGISTER_RESTORE_95_64_SHFT                       0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000040c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_REGISTER_RESTORE_127_96_BMSK               0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW1_MSB_REGISTER_RESTORE_127_96_SHFT                      0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000410)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_REGISTER_RESTORE_159_128_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_LSB_REGISTER_RESTORE_159_128_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000414)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_REGISTER_RESTORE_191_160_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW2_MSB_REGISTER_RESTORE_191_160_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000418)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_REGISTER_RESTORE_223_192_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_LSB_REGISTER_RESTORE_223_192_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000041c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_REGISTER_RESTORE_255_224_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW3_MSB_REGISTER_RESTORE_255_224_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000420)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_REGISTER_RESTORE_287_256_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_LSB_REGISTER_RESTORE_287_256_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000424)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_REGISTER_RESTORE_319_288_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW4_MSB_REGISTER_RESTORE_319_288_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000428)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_REGISTER_RESTORE_351_320_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_LSB_REGISTER_RESTORE_351_320_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000042c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_REGISTER_RESTORE_383_352_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW5_MSB_REGISTER_RESTORE_383_352_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000430)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_REGISTER_RESTORE_415_384_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_LSB_REGISTER_RESTORE_415_384_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000434)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_REGISTER_RESTORE_447_416_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW6_MSB_REGISTER_RESTORE_447_416_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000438)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_REGISTER_RESTORE_479_448_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_LSB_REGISTER_RESTORE_479_448_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000043c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_REGISTER_RESTORE_511_480_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW7_MSB_REGISTER_RESTORE_511_480_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000440)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_REGISTER_RESTORE_543_512_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_LSB_REGISTER_RESTORE_543_512_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000444)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_REGISTER_RESTORE_575_544_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW8_MSB_REGISTER_RESTORE_575_544_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000448)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_REGISTER_RESTORE_607_576_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_LSB_REGISTER_RESTORE_607_576_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_ADDR                                       (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000044c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_RMSK                                       0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_REGISTER_RESTORE_639_608_BMSK              0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW9_MSB_REGISTER_RESTORE_639_608_SHFT                     0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000450)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_REGISTER_RESTORE_671_640_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_LSB_REGISTER_RESTORE_671_640_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000454)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_REGISTER_RESTORE_703_672_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW10_MSB_REGISTER_RESTORE_703_672_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000458)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_REGISTER_RESTORE_735_704_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_LSB_REGISTER_RESTORE_735_704_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000045c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_REGISTER_RESTORE_767_736_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW11_MSB_REGISTER_RESTORE_767_736_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000460)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_REGISTER_RESTORE_799_768_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_LSB_REGISTER_RESTORE_799_768_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000464)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_REGISTER_RESTORE_831_800_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW12_MSB_REGISTER_RESTORE_831_800_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000468)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_REGISTER_RESTORE_863_832_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_LSB_REGISTER_RESTORE_863_832_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000046c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_REGISTER_RESTORE_895_864_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW13_MSB_REGISTER_RESTORE_895_864_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000470)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_REGISTER_RESTORE_927_896_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_LSB_REGISTER_RESTORE_927_896_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000474)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_REGISTER_RESTORE_959_928_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW14_MSB_REGISTER_RESTORE_959_928_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000478)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_REGISTER_RESTORE_991_960_BMSK             0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_LSB_REGISTER_RESTORE_991_960_SHFT                    0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000047c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_REGISTER_RESTORE_1023_992_BMSK            0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW15_MSB_REGISTER_RESTORE_1023_992_SHFT                   0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000480)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_REGISTER_RESTORE_1055_1024_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_LSB_REGISTER_RESTORE_1055_1024_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000484)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_REGISTER_RESTORE_1087_1056_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW16_MSB_REGISTER_RESTORE_1087_1056_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000488)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_REGISTER_RESTORE_1119_1088_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_LSB_REGISTER_RESTORE_1119_1088_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000048c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_REGISTER_RESTORE_1151_1120_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW17_MSB_REGISTER_RESTORE_1151_1120_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000490)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_REGISTER_RESTORE_1183_1152_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_LSB_REGISTER_RESTORE_1183_1152_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000494)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_REGISTER_RESTORE_1215_1184_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW18_MSB_REGISTER_RESTORE_1215_1184_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000498)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_REGISTER_RESTORE_1247_1216_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_LSB_REGISTER_RESTORE_1247_1216_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000049c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_REGISTER_RESTORE_1279_1248_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW19_MSB_REGISTER_RESTORE_1279_1248_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004a0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_REGISTER_RESTORE_1311_1280_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_LSB_REGISTER_RESTORE_1311_1280_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004a4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_REGISTER_RESTORE_1343_1312_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW20_MSB_REGISTER_RESTORE_1343_1312_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004a8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_REGISTER_RESTORE_1375_1344_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_LSB_REGISTER_RESTORE_1375_1344_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004ac)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_REGISTER_RESTORE_1407_1376_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW21_MSB_REGISTER_RESTORE_1407_1376_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004b0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_REGISTER_RESTORE_1439_1408_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_LSB_REGISTER_RESTORE_1439_1408_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004b4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_REGISTER_RESTORE_1471_1440_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW22_MSB_REGISTER_RESTORE_1471_1440_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004b8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_REGISTER_RESTORE_1503_1472_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_LSB_REGISTER_RESTORE_1503_1472_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004bc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_REGISTER_RESTORE_1535_1504_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW23_MSB_REGISTER_RESTORE_1535_1504_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004c0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_REGISTER_RESTORE_1567_1536_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_LSB_REGISTER_RESTORE_1567_1536_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004c4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_REGISTER_RESTORE_1599_1568_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW24_MSB_REGISTER_RESTORE_1599_1568_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004c8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_REGISTER_RESTORE_1631_1600_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_LSB_REGISTER_RESTORE_1631_1600_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004cc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_REGISTER_RESTORE_1663_1632_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW25_MSB_REGISTER_RESTORE_1663_1632_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004d0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_REGISTER_RESTORE_1695_1664_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_LSB_REGISTER_RESTORE_1695_1664_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004d4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_REGISTER_RESTORE_1727_1696_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW26_MSB_REGISTER_RESTORE_1727_1696_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004d8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_REGISTER_RESTORE_1759_1728_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_LSB_REGISTER_RESTORE_1759_1728_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004dc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_REGISTER_RESTORE_1791_1760_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW27_MSB_REGISTER_RESTORE_1791_1760_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004e0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_REGISTER_RESTORE_1823_1792_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_LSB_REGISTER_RESTORE_1823_1792_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004e4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_REGISTER_RESTORE_1855_1824_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW28_MSB_REGISTER_RESTORE_1855_1824_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004e8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_REGISTER_RESTORE_1887_1856_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_LSB_REGISTER_RESTORE_1887_1856_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004ec)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_REGISTER_RESTORE_1919_1888_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW29_MSB_REGISTER_RESTORE_1919_1888_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004f0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_REGISTER_RESTORE_1951_1920_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_LSB_REGISTER_RESTORE_1951_1920_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004f4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_REGISTER_RESTORE_1983_1952_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW30_MSB_REGISTER_RESTORE_1983_1952_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004f8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_REGISTER_RESTORE_2015_1984_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_LSB_REGISTER_RESTORE_2015_1984_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000004fc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_REGISTER_RESTORE_2047_2016_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW31_MSB_REGISTER_RESTORE_2047_2016_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000500)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_REGISTER_RESTORE_2079_2048_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_LSB_REGISTER_RESTORE_2079_2048_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000504)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_REGISTER_RESTORE_2111_2080_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW32_MSB_REGISTER_RESTORE_2111_2080_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000508)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_REGISTER_RESTORE_2143_2112_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_LSB_REGISTER_RESTORE_2143_2112_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000050c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_REGISTER_RESTORE_2175_2144_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW33_MSB_REGISTER_RESTORE_2175_2144_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000510)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_REGISTER_RESTORE_2207_2176_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_LSB_REGISTER_RESTORE_2207_2176_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000514)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_REGISTER_RESTORE_2239_2208_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW34_MSB_REGISTER_RESTORE_2239_2208_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000518)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_REGISTER_RESTORE_2271_2240_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_LSB_REGISTER_RESTORE_2271_2240_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000051c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_REGISTER_RESTORE_2303_2272_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW35_MSB_REGISTER_RESTORE_2303_2272_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000520)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_REGISTER_RESTORE_2335_2304_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_LSB_REGISTER_RESTORE_2335_2304_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000524)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_REGISTER_RESTORE_2367_2336_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW36_MSB_REGISTER_RESTORE_2367_2336_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000528)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_REGISTER_RESTORE_2399_2368_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_LSB_REGISTER_RESTORE_2399_2368_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000052c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_REGISTER_RESTORE_2431_2400_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW37_MSB_REGISTER_RESTORE_2431_2400_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000530)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_REGISTER_RESTORE_2463_2432_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_LSB_REGISTER_RESTORE_2463_2432_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000534)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_REGISTER_RESTORE_2495_2464_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW38_MSB_REGISTER_RESTORE_2495_2464_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000538)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_REGISTER_RESTORE_2527_2496_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_LSB_REGISTER_RESTORE_2527_2496_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000053c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_REGISTER_RESTORE_2559_2528_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW39_MSB_REGISTER_RESTORE_2559_2528_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000540)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_REGISTER_RESTORE_2591_2560_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_LSB_REGISTER_RESTORE_2591_2560_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000544)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_REGISTER_RESTORE_2623_2592_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW40_MSB_REGISTER_RESTORE_2623_2592_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000548)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_REGISTER_RESTORE_2655_2624_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_LSB_REGISTER_RESTORE_2655_2624_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000054c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_REGISTER_RESTORE_2687_2656_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW41_MSB_REGISTER_RESTORE_2687_2656_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000550)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_REGISTER_RESTORE_2719_2688_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_LSB_REGISTER_RESTORE_2719_2688_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000554)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_REGISTER_RESTORE_2751_2720_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW42_MSB_REGISTER_RESTORE_2751_2720_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000558)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_REGISTER_RESTORE_2783_2752_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_LSB_REGISTER_RESTORE_2783_2752_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000055c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_REGISTER_RESTORE_2815_2784_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW43_MSB_REGISTER_RESTORE_2815_2784_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000560)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_REGISTER_RESTORE_2847_2816_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_LSB_REGISTER_RESTORE_2847_2816_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000564)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_REGISTER_RESTORE_2879_2848_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW44_MSB_REGISTER_RESTORE_2879_2848_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000568)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_REGISTER_RESTORE_2911_2880_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_LSB_REGISTER_RESTORE_2911_2880_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000056c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_REGISTER_RESTORE_2943_2912_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW45_MSB_REGISTER_RESTORE_2943_2912_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000570)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_REGISTER_RESTORE_2975_2944_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_LSB_REGISTER_RESTORE_2975_2944_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000574)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_REGISTER_RESTORE_3007_2976_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW46_MSB_REGISTER_RESTORE_3007_2976_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000578)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_REGISTER_RESTORE_3039_3008_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_LSB_REGISTER_RESTORE_3039_3008_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000057c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_REGISTER_RESTORE_3071_3040_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW47_MSB_REGISTER_RESTORE_3071_3040_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000580)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_REGISTER_RESTORE_3103_3072_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_LSB_REGISTER_RESTORE_3103_3072_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000584)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_REGISTER_RESTORE_3135_3104_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW48_MSB_REGISTER_RESTORE_3135_3104_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000588)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_REGISTER_RESTORE_3167_3136_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_LSB_REGISTER_RESTORE_3167_3136_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000058c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_REGISTER_RESTORE_3199_3168_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW49_MSB_REGISTER_RESTORE_3199_3168_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000590)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_REGISTER_RESTORE_3231_3200_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_LSB_REGISTER_RESTORE_3231_3200_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000594)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_REGISTER_RESTORE_3263_3232_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW50_MSB_REGISTER_RESTORE_3263_3232_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000598)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_REGISTER_RESTORE_3295_3264_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_LSB_REGISTER_RESTORE_3295_3264_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000059c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_REGISTER_RESTORE_3327_3296_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW51_MSB_REGISTER_RESTORE_3327_3296_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005a0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_REGISTER_RESTORE_3359_3328_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_LSB_REGISTER_RESTORE_3359_3328_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005a4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_REGISTER_RESTORE_3391_3360_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW52_MSB_REGISTER_RESTORE_3391_3360_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005a8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_REGISTER_RESTORE_3423_3392_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_LSB_REGISTER_RESTORE_3423_3392_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005ac)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_REGISTER_RESTORE_3455_3424_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW53_MSB_REGISTER_RESTORE_3455_3424_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005b0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_REGISTER_RESTORE_3487_3456_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_LSB_REGISTER_RESTORE_3487_3456_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005b4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_REGISTER_RESTORE_3519_3488_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW54_MSB_REGISTER_RESTORE_3519_3488_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005b8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_REGISTER_RESTORE_3551_3520_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_LSB_REGISTER_RESTORE_3551_3520_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005bc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_REGISTER_RESTORE_3583_3552_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW55_MSB_REGISTER_RESTORE_3583_3552_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005c0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_REGISTER_RESTORE_3615_3584_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_LSB_REGISTER_RESTORE_3615_3584_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005c4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_REGISTER_RESTORE_3647_3616_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW56_MSB_REGISTER_RESTORE_3647_3616_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005c8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_REGISTER_RESTORE_3679_3648_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_LSB_REGISTER_RESTORE_3679_3648_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005cc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_REGISTER_RESTORE_3711_3680_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW57_MSB_REGISTER_RESTORE_3711_3680_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005d0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_REGISTER_RESTORE_3743_3712_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_LSB_REGISTER_RESTORE_3743_3712_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005d4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_REGISTER_RESTORE_3775_3744_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW58_MSB_REGISTER_RESTORE_3775_3744_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005d8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_REGISTER_RESTORE_3807_3776_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_LSB_REGISTER_RESTORE_3807_3776_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005dc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_REGISTER_RESTORE_3839_3808_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW59_MSB_REGISTER_RESTORE_3839_3808_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005e0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_REGISTER_RESTORE_3871_3840_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_LSB_REGISTER_RESTORE_3871_3840_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005e4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_REGISTER_RESTORE_3903_3872_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW60_MSB_REGISTER_RESTORE_3903_3872_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005e8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_REGISTER_RESTORE_3935_3904_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_LSB_REGISTER_RESTORE_3935_3904_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005ec)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_REGISTER_RESTORE_3967_3936_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW61_MSB_REGISTER_RESTORE_3967_3936_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005f0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_REGISTER_RESTORE_3999_3968_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_LSB_REGISTER_RESTORE_3999_3968_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005f4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_REGISTER_RESTORE_4031_4000_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW62_MSB_REGISTER_RESTORE_4031_4000_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005f8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_REGISTER_RESTORE_4063_4032_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_LSB_REGISTER_RESTORE_4063_4032_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000005fc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_REGISTER_RESTORE_4095_4064_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW63_MSB_REGISTER_RESTORE_4095_4064_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000600)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_REGISTER_RESTORE_4127_4096_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_LSB_REGISTER_RESTORE_4127_4096_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000604)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_REGISTER_RESTORE_4159_4128_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW64_MSB_REGISTER_RESTORE_4159_4128_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000608)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_REGISTER_RESTORE_4191_4160_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_LSB_REGISTER_RESTORE_4191_4160_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000060c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_REGISTER_RESTORE_4223_4192_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW65_MSB_REGISTER_RESTORE_4223_4192_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000610)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_REGISTER_RESTORE_4255_4224_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_LSB_REGISTER_RESTORE_4255_4224_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000614)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_REGISTER_RESTORE_4287_4256_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW66_MSB_REGISTER_RESTORE_4287_4256_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000618)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_REGISTER_RESTORE_4319_4288_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_LSB_REGISTER_RESTORE_4319_4288_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000061c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_REGISTER_RESTORE_4351_4320_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW67_MSB_REGISTER_RESTORE_4351_4320_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000620)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_REGISTER_RESTORE_4383_4352_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_LSB_REGISTER_RESTORE_4383_4352_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000624)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_REGISTER_RESTORE_4415_4384_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW68_MSB_REGISTER_RESTORE_4415_4384_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000628)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_REGISTER_RESTORE_4447_4416_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_LSB_REGISTER_RESTORE_4447_4416_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000062c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_REGISTER_RESTORE_4479_4448_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW69_MSB_REGISTER_RESTORE_4479_4448_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000630)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_REGISTER_RESTORE_4511_4480_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_LSB_REGISTER_RESTORE_4511_4480_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000634)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_REGISTER_RESTORE_4543_4512_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW70_MSB_REGISTER_RESTORE_4543_4512_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000638)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_REGISTER_RESTORE_4575_4544_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_LSB_REGISTER_RESTORE_4575_4544_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000063c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_REGISTER_RESTORE_4607_4576_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW71_MSB_REGISTER_RESTORE_4607_4576_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000640)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_REGISTER_RESTORE_4639_4608_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_LSB_REGISTER_RESTORE_4639_4608_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000644)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_REGISTER_RESTORE_4671_4640_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW72_MSB_REGISTER_RESTORE_4671_4640_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000648)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_REGISTER_RESTORE_4703_4672_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_LSB_REGISTER_RESTORE_4703_4672_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000064c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_REGISTER_RESTORE_4735_4704_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW73_MSB_REGISTER_RESTORE_4735_4704_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000650)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_REGISTER_RESTORE_4767_4736_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_LSB_REGISTER_RESTORE_4767_4736_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000654)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_REGISTER_RESTORE_4799_4768_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW74_MSB_REGISTER_RESTORE_4799_4768_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000658)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_REGISTER_RESTORE_4831_4800_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_LSB_REGISTER_RESTORE_4831_4800_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000065c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_REGISTER_RESTORE_4863_4832_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW75_MSB_REGISTER_RESTORE_4863_4832_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000660)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_REGISTER_RESTORE_4895_4864_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_LSB_REGISTER_RESTORE_4895_4864_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000664)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_REGISTER_RESTORE_4927_4896_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW76_MSB_REGISTER_RESTORE_4927_4896_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000668)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_REGISTER_RESTORE_4959_4928_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_LSB_REGISTER_RESTORE_4959_4928_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000066c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_REGISTER_RESTORE_4991_4960_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW77_MSB_REGISTER_RESTORE_4991_4960_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000670)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_REGISTER_RESTORE_5023_4992_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_LSB_REGISTER_RESTORE_5023_4992_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000674)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_REGISTER_RESTORE_5055_5024_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW78_MSB_REGISTER_RESTORE_5055_5024_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000678)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_REGISTER_RESTORE_5087_5056_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_LSB_REGISTER_RESTORE_5087_5056_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000067c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_REGISTER_RESTORE_5119_5088_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW79_MSB_REGISTER_RESTORE_5119_5088_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000680)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_REGISTER_RESTORE_5151_5120_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_LSB_REGISTER_RESTORE_5151_5120_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000684)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_REGISTER_RESTORE_5183_5152_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW80_MSB_REGISTER_RESTORE_5183_5152_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000688)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_REGISTER_RESTORE_5215_5184_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_LSB_REGISTER_RESTORE_5215_5184_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000068c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_REGISTER_RESTORE_5247_5216_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW81_MSB_REGISTER_RESTORE_5247_5216_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000690)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_REGISTER_RESTORE_5279_5248_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_LSB_REGISTER_RESTORE_5279_5248_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000694)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_REGISTER_RESTORE_5311_5280_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW82_MSB_REGISTER_RESTORE_5311_5280_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000698)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_REGISTER_RESTORE_5343_5312_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_LSB_REGISTER_RESTORE_5343_5312_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000069c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_REGISTER_RESTORE_5375_5344_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW83_MSB_REGISTER_RESTORE_5375_5344_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006a0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_REGISTER_RESTORE_5407_5376_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_LSB_REGISTER_RESTORE_5407_5376_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006a4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_REGISTER_RESTORE_5439_5408_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW84_MSB_REGISTER_RESTORE_5439_5408_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006a8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_REGISTER_RESTORE_5471_5440_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_LSB_REGISTER_RESTORE_5471_5440_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006ac)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_REGISTER_RESTORE_5503_5472_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW85_MSB_REGISTER_RESTORE_5503_5472_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006b0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_REGISTER_RESTORE_5535_5504_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_LSB_REGISTER_RESTORE_5535_5504_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006b4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_REGISTER_RESTORE_5567_5536_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW86_MSB_REGISTER_RESTORE_5567_5536_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006b8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_REGISTER_RESTORE_5599_5568_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_LSB_REGISTER_RESTORE_5599_5568_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006bc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_REGISTER_RESTORE_5631_5600_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW87_MSB_REGISTER_RESTORE_5631_5600_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006c0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_REGISTER_RESTORE_5663_5632_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_LSB_REGISTER_RESTORE_5663_5632_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006c4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_REGISTER_RESTORE_5695_5664_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW88_MSB_REGISTER_RESTORE_5695_5664_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006c8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_REGISTER_RESTORE_5727_5696_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_LSB_REGISTER_RESTORE_5727_5696_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006cc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_REGISTER_RESTORE_5759_5728_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW89_MSB_REGISTER_RESTORE_5759_5728_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006d0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_REGISTER_RESTORE_5791_5760_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_LSB_REGISTER_RESTORE_5791_5760_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006d4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_REGISTER_RESTORE_5823_5792_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW90_MSB_REGISTER_RESTORE_5823_5792_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006d8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_REGISTER_RESTORE_5855_5824_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_LSB_REGISTER_RESTORE_5855_5824_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006dc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_REGISTER_RESTORE_5887_5856_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW91_MSB_REGISTER_RESTORE_5887_5856_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006e0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_REGISTER_RESTORE_5919_5888_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_LSB_REGISTER_RESTORE_5919_5888_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006e4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_REGISTER_RESTORE_5951_5920_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW92_MSB_REGISTER_RESTORE_5951_5920_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006e8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_REGISTER_RESTORE_5983_5952_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_LSB_REGISTER_RESTORE_5983_5952_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006ec)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_REGISTER_RESTORE_6015_5984_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW93_MSB_REGISTER_RESTORE_6015_5984_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006f0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_REGISTER_RESTORE_6047_6016_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_LSB_REGISTER_RESTORE_6047_6016_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006f4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_REGISTER_RESTORE_6079_6048_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW94_MSB_REGISTER_RESTORE_6079_6048_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006f8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_REGISTER_RESTORE_6111_6080_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_LSB_REGISTER_RESTORE_6111_6080_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000006fc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_REGISTER_RESTORE_6143_6112_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW95_MSB_REGISTER_RESTORE_6143_6112_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000700)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_REGISTER_RESTORE_6175_6144_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_LSB_REGISTER_RESTORE_6175_6144_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000704)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_REGISTER_RESTORE_6207_6176_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW96_MSB_REGISTER_RESTORE_6207_6176_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000708)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_REGISTER_RESTORE_6239_6208_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_LSB_REGISTER_RESTORE_6239_6208_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000070c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_REGISTER_RESTORE_6271_6240_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW97_MSB_REGISTER_RESTORE_6271_6240_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000710)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_REGISTER_RESTORE_6303_6272_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_LSB_REGISTER_RESTORE_6303_6272_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000714)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_REGISTER_RESTORE_6335_6304_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW98_MSB_REGISTER_RESTORE_6335_6304_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000718)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_REGISTER_RESTORE_6367_6336_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_LSB_REGISTER_RESTORE_6367_6336_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_ADDR                                      (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000071c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_RMSK                                      0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_REGISTER_RESTORE_6399_6368_BMSK           0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW99_MSB_REGISTER_RESTORE_6399_6368_SHFT                  0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000720)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_REGISTER_RESTORE_6431_6400_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_LSB_REGISTER_RESTORE_6431_6400_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000724)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_REGISTER_RESTORE_6463_6432_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW100_MSB_REGISTER_RESTORE_6463_6432_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000728)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_REGISTER_RESTORE_6495_6464_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_LSB_REGISTER_RESTORE_6495_6464_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000072c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_REGISTER_RESTORE_6527_6496_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW101_MSB_REGISTER_RESTORE_6527_6496_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000730)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_REGISTER_RESTORE_6559_6528_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_LSB_REGISTER_RESTORE_6559_6528_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000734)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_REGISTER_RESTORE_6591_6560_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW102_MSB_REGISTER_RESTORE_6591_6560_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000738)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_REGISTER_RESTORE_6623_6592_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_LSB_REGISTER_RESTORE_6623_6592_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000073c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_REGISTER_RESTORE_6655_6624_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW103_MSB_REGISTER_RESTORE_6655_6624_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000740)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_REGISTER_RESTORE_6687_6656_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_LSB_REGISTER_RESTORE_6687_6656_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000744)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_REGISTER_RESTORE_6719_6688_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW104_MSB_REGISTER_RESTORE_6719_6688_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000748)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_REGISTER_RESTORE_6751_6720_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_LSB_REGISTER_RESTORE_6751_6720_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000074c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_REGISTER_RESTORE_6783_6752_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW105_MSB_REGISTER_RESTORE_6783_6752_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000750)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_REGISTER_RESTORE_6815_6784_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_LSB_REGISTER_RESTORE_6815_6784_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000754)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_REGISTER_RESTORE_6847_6816_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW106_MSB_REGISTER_RESTORE_6847_6816_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000758)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_REGISTER_RESTORE_6879_6848_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_LSB_REGISTER_RESTORE_6879_6848_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000075c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_REGISTER_RESTORE_6911_6880_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW107_MSB_REGISTER_RESTORE_6911_6880_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000760)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_REGISTER_RESTORE_6943_6912_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_LSB_REGISTER_RESTORE_6943_6912_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000764)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_REGISTER_RESTORE_6975_6944_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW108_MSB_REGISTER_RESTORE_6975_6944_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000768)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_REGISTER_RESTORE_7007_6976_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_LSB_REGISTER_RESTORE_7007_6976_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000076c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_REGISTER_RESTORE_7039_7008_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW109_MSB_REGISTER_RESTORE_7039_7008_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000770)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_REGISTER_RESTORE_7071_7040_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_LSB_REGISTER_RESTORE_7071_7040_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000774)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_REGISTER_RESTORE_7103_7072_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW110_MSB_REGISTER_RESTORE_7103_7072_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000778)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_REGISTER_RESTORE_7135_7104_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_LSB_REGISTER_RESTORE_7135_7104_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000077c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_REGISTER_RESTORE_7167_7136_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW111_MSB_REGISTER_RESTORE_7167_7136_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000780)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_REGISTER_RESTORE_7199_7168_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_LSB_REGISTER_RESTORE_7199_7168_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000784)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_REGISTER_RESTORE_7231_7200_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW112_MSB_REGISTER_RESTORE_7231_7200_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000788)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_REGISTER_RESTORE_7263_7232_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_LSB_REGISTER_RESTORE_7263_7232_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000078c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_REGISTER_RESTORE_7295_7264_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW113_MSB_REGISTER_RESTORE_7295_7264_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000790)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_REGISTER_RESTORE_7327_7296_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_LSB_REGISTER_RESTORE_7327_7296_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000794)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_REGISTER_RESTORE_7359_7328_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW114_MSB_REGISTER_RESTORE_7359_7328_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x00000798)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_REGISTER_RESTORE_7391_7360_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_LSB_REGISTER_RESTORE_7391_7360_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x0000079c)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_REGISTER_RESTORE_7423_7392_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW115_MSB_REGISTER_RESTORE_7423_7392_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007a0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_REGISTER_RESTORE_7455_7424_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_LSB_REGISTER_RESTORE_7455_7424_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007a4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_REGISTER_RESTORE_7487_7456_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW116_MSB_REGISTER_RESTORE_7487_7456_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007a8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_REGISTER_RESTORE_7519_7488_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_LSB_REGISTER_RESTORE_7519_7488_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007ac)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_REGISTER_RESTORE_7551_7520_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW117_MSB_REGISTER_RESTORE_7551_7520_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007b0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_REGISTER_RESTORE_7583_7552_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_LSB_REGISTER_RESTORE_7583_7552_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007b4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_REGISTER_RESTORE_7615_7584_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW118_MSB_REGISTER_RESTORE_7615_7584_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007b8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_REGISTER_RESTORE_7647_7616_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_LSB_REGISTER_RESTORE_7647_7616_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007bc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_REGISTER_RESTORE_7679_7648_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW119_MSB_REGISTER_RESTORE_7679_7648_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007c0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_REGISTER_RESTORE_7711_7680_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_LSB_REGISTER_RESTORE_7711_7680_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007c4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_REGISTER_RESTORE_7743_7712_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW120_MSB_REGISTER_RESTORE_7743_7712_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007c8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_REGISTER_RESTORE_7775_7744_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_LSB_REGISTER_RESTORE_7775_7744_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007cc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_REGISTER_RESTORE_7807_7776_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW121_MSB_REGISTER_RESTORE_7807_7776_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007d0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_REGISTER_RESTORE_7839_7808_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_LSB_REGISTER_RESTORE_7839_7808_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007d4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_REGISTER_RESTORE_7871_7840_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW122_MSB_REGISTER_RESTORE_7871_7840_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007d8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_REGISTER_RESTORE_7903_7872_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_LSB_REGISTER_RESTORE_7903_7872_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007dc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_REGISTER_RESTORE_7935_7904_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW123_MSB_REGISTER_RESTORE_7935_7904_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007e0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_REGISTER_RESTORE_7967_7936_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_LSB_REGISTER_RESTORE_7967_7936_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007e4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_REGISTER_RESTORE_7999_7968_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW124_MSB_REGISTER_RESTORE_7999_7968_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007e8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_REGISTER_RESTORE_8031_8000_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_LSB_REGISTER_RESTORE_8031_8000_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007ec)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_REGISTER_RESTORE_8063_8032_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW125_MSB_REGISTER_RESTORE_8063_8032_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007f0)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_REGISTER_RESTORE_8095_8064_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_LSB_REGISTER_RESTORE_8095_8064_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007f4)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_REGISTER_RESTORE_8127_8096_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW126_MSB_REGISTER_RESTORE_8127_8096_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007f8)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_REGISTER_RESTORE_8159_8128_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_LSB_REGISTER_RESTORE_8159_8128_SHFT                 0x0

#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_ADDR                                     (OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_REG_BASE      + 0x000007fc)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_RMSK                                     0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_IN          \
        in_dword(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_ADDR)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_INM(m)      \
        in_dword_masked(HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_ADDR, m)
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_REGISTER_RESTORE_8191_8160_BMSK          0xffffffff
#define HWIO_OTP_QFPROM_CORR_REGISTER_RESTORE_ROW127_MSB_REGISTER_RESTORE_8191_8160_SHFT                 0x0


#endif /* __HWIO_FUSE_H__ */
