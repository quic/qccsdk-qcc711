#ifndef __HWIO_PMU_H__
#define __HWIO_PMU_H__
/*
===========================================================================
*/
/**
  @file hwio_pmu.h
  @brief Auto-generated HWIO interface include file.

  This file contains HWIO register definitions for the following bases:
    PMU_MTOP_02

  Excluded modules from above list:
    PMU_VLP_AON_REG
    PMU_CTRL_STATUS_VLP_AON_REG
    PMU_STATIC_ADDA_VLP_REG
    PMU_VLP_SD_REG
    PMU_CTRL_STATUS_VLP_SD_REG

  'Exclude' filters applied: DUMMY RESERVED 

  Generation parameters: 
  { 'bases': ['PMU_MTOP_02'],
    'exclude-no-doc': True,
    'exclude-reserved': True,
    'filename': 'inc/hwio_pmu.h',
    'header': '#include "HALhwio.h"\n#include "hwio_base.h"',
    'modules-exclude': [ 'PMU_VLP_AON_REG',
                         'PMU_CTRL_STATUS_VLP_AON_REG',
                         'PMU_STATIC_ADDA_VLP_REG',
                         'PMU_VLP_SD_REG',
                         'PMU_CTRL_STATUS_VLP_SD_REG'],
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
 * MODULE: PMU_VDIG_REG
 *--------------------------------------------------------------------------*/

#define PMU_VDIG_REG_REG_BASE (PMU_MTOP_02_BASE      + 0x00000000)
#define PMU_VDIG_REG_REG_BASE_SIZE 0xc0
#define PMU_VDIG_REG_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: PMU_CTRL_STATUS_VDIG_REG
 *--------------------------------------------------------------------------*/

#define PMU_CTRL_STATUS_VDIG_REG_REG_BASE                                              (PMU_MTOP_02_BASE      + 0x00000000)
#define PMU_CTRL_STATUS_VDIG_REG_REG_BASE_SIZE                                         0xc0
#define PMU_CTRL_STATUS_VDIG_REG_REG_BASE_USED                                         0xa8

#define HWIO_PMU_INT_APSS_OUT_ENA_ADDR                                                 (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000000)
#define HWIO_PMU_INT_APSS_OUT_ENA_RMSK                                                        0x1
#define HWIO_PMU_INT_APSS_OUT_ENA_IN          \
        in_dword(HWIO_PMU_INT_APSS_OUT_ENA_ADDR)
#define HWIO_PMU_INT_APSS_OUT_ENA_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_APSS_OUT_ENA_ADDR, m)
#define HWIO_PMU_INT_APSS_OUT_ENA_OUT(v)      \
        out_dword(HWIO_PMU_INT_APSS_OUT_ENA_ADDR,v)
#define HWIO_PMU_INT_APSS_OUT_ENA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_APSS_OUT_ENA_ADDR,m,v,HWIO_PMU_INT_APSS_OUT_ENA_IN)
#define HWIO_PMU_INT_APSS_OUT_ENA_APSS_INT_OUT_ENA_BMSK                                       0x1
#define HWIO_PMU_INT_APSS_OUT_ENA_APSS_INT_OUT_ENA_SHFT                                       0x0

#define HWIO_PMU_INT_APSS_MASK_ADDR                                                    (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000004)
#define HWIO_PMU_INT_APSS_MASK_RMSK                                                           0xf
#define HWIO_PMU_INT_APSS_MASK_IN          \
        in_dword(HWIO_PMU_INT_APSS_MASK_ADDR)
#define HWIO_PMU_INT_APSS_MASK_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_APSS_MASK_ADDR, m)
#define HWIO_PMU_INT_APSS_MASK_OUT(v)      \
        out_dword(HWIO_PMU_INT_APSS_MASK_ADDR,v)
#define HWIO_PMU_INT_APSS_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_APSS_MASK_ADDR,m,v,HWIO_PMU_INT_APSS_MASK_IN)
#define HWIO_PMU_INT_APSS_MASK_LDO_VMA_APSS_STARTUP_DONE_INT_MASK_BMSK                        0x8
#define HWIO_PMU_INT_APSS_MASK_LDO_VMA_APSS_STARTUP_DONE_INT_MASK_SHFT                        0x3
#define HWIO_PMU_INT_APSS_MASK_BIST_ADC_APSS_PENDING_LOCKED_INT_MASK_BMSK                     0x4
#define HWIO_PMU_INT_APSS_MASK_BIST_ADC_APSS_PENDING_LOCKED_INT_MASK_SHFT                     0x2
#define HWIO_PMU_INT_APSS_MASK_TS_APSS_REQ_DONE_INT_MASK_BMSK                                 0x2
#define HWIO_PMU_INT_APSS_MASK_TS_APSS_REQ_DONE_INT_MASK_SHFT                                 0x1
#define HWIO_PMU_INT_APSS_MASK_BIST_ADC_APSS_REQ_DONE_INT_MASK_BMSK                           0x1
#define HWIO_PMU_INT_APSS_MASK_BIST_ADC_APSS_REQ_DONE_INT_MASK_SHFT                           0x0

#define HWIO_PMU_INT_APSS_STATUS_ADDR                                                  (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000008)
#define HWIO_PMU_INT_APSS_STATUS_RMSK                                                         0xf
#define HWIO_PMU_INT_APSS_STATUS_IN          \
        in_dword(HWIO_PMU_INT_APSS_STATUS_ADDR)
#define HWIO_PMU_INT_APSS_STATUS_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_APSS_STATUS_ADDR, m)
#define HWIO_PMU_INT_APSS_STATUS_LDO_VMA_APSS_STARTUP_DONE_INT_STATUS_BMSK                    0x8
#define HWIO_PMU_INT_APSS_STATUS_LDO_VMA_APSS_STARTUP_DONE_INT_STATUS_SHFT                    0x3
#define HWIO_PMU_INT_APSS_STATUS_BIST_ADC_APSS_PENDING_LOCKED_INT_STATUS_BMSK                 0x4
#define HWIO_PMU_INT_APSS_STATUS_BIST_ADC_APSS_PENDING_LOCKED_INT_STATUS_SHFT                 0x2
#define HWIO_PMU_INT_APSS_STATUS_TS_APSS_REQ_DONE_INT_STATUS_BMSK                             0x2
#define HWIO_PMU_INT_APSS_STATUS_TS_APSS_REQ_DONE_INT_STATUS_SHFT                             0x1
#define HWIO_PMU_INT_APSS_STATUS_BIST_ADC_APSS_REQ_DONE_INT_STATUS_BMSK                       0x1
#define HWIO_PMU_INT_APSS_STATUS_BIST_ADC_APSS_REQ_DONE_INT_STATUS_SHFT                       0x0

#define HWIO_PMU_INT_APSS_CLR_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000000c)
#define HWIO_PMU_INT_APSS_CLR_RMSK                                                            0xf
#define HWIO_PMU_INT_APSS_CLR_OUT(v)      \
        out_dword(HWIO_PMU_INT_APSS_CLR_ADDR,v)
#define HWIO_PMU_INT_APSS_CLR_LDO_VMA_APSS_STARTUP_DONE_INT_CLR_BMSK                          0x8
#define HWIO_PMU_INT_APSS_CLR_LDO_VMA_APSS_STARTUP_DONE_INT_CLR_SHFT                          0x3
#define HWIO_PMU_INT_APSS_CLR_BIST_ADC_APSS_PENDING_LOCKED_INT_CLR_BMSK                       0x4
#define HWIO_PMU_INT_APSS_CLR_BIST_ADC_APSS_PENDING_LOCKED_INT_CLR_SHFT                       0x2
#define HWIO_PMU_INT_APSS_CLR_TS_APSS_REQ_DONE_INT_CLR_BMSK                                   0x2
#define HWIO_PMU_INT_APSS_CLR_TS_APSS_REQ_DONE_INT_CLR_SHFT                                   0x1
#define HWIO_PMU_INT_APSS_CLR_BIST_ADC_APSS_REQ_DONE_INT_CLR_BMSK                             0x1
#define HWIO_PMU_INT_APSS_CLR_BIST_ADC_APSS_REQ_DONE_INT_CLR_SHFT                             0x0

#define HWIO_PMU_INT_APSS_SET_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000010)
#define HWIO_PMU_INT_APSS_SET_RMSK                                                            0xf
#define HWIO_PMU_INT_APSS_SET_OUT(v)      \
        out_dword(HWIO_PMU_INT_APSS_SET_ADDR,v)
#define HWIO_PMU_INT_APSS_SET_LDO_VMA_APSS_STARTUP_DONE_INT_SET_BMSK                          0x8
#define HWIO_PMU_INT_APSS_SET_LDO_VMA_APSS_STARTUP_DONE_INT_SET_SHFT                          0x3
#define HWIO_PMU_INT_APSS_SET_BIST_ADC_APSS_PENDING_LOCKED_INT_SET_BMSK                       0x4
#define HWIO_PMU_INT_APSS_SET_BIST_ADC_APSS_PENDING_LOCKED_INT_SET_SHFT                       0x2
#define HWIO_PMU_INT_APSS_SET_TS_APSS_REQ_DONE_INT_SET_BMSK                                   0x2
#define HWIO_PMU_INT_APSS_SET_TS_APSS_REQ_DONE_INT_SET_SHFT                                   0x1
#define HWIO_PMU_INT_APSS_SET_BIST_ADC_APSS_REQ_DONE_INT_SET_BMSK                             0x1
#define HWIO_PMU_INT_APSS_SET_BIST_ADC_APSS_REQ_DONE_INT_SET_SHFT                             0x0

#define HWIO_PMU_APSS_REQ_ADDR                                                         (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000014)
#define HWIO_PMU_APSS_REQ_RMSK                                                               0xff
#define HWIO_PMU_APSS_REQ_OUT(v)      \
        out_dword(HWIO_PMU_APSS_REQ_ADDR,v)
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_DISABLE_REQ_BMSK                              0x80
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_DISABLE_REQ_SHFT                               0x7
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_ENABLE_REQ_BMSK                               0x40
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_AUTO_ON_ENABLE_REQ_SHFT                                0x6
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_RELEASE_REQ_BMSK                                      0x20
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_RELEASE_REQ_SHFT                                       0x5
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_HOLD_REQ_BMSK                                         0x10
#define HWIO_PMU_APSS_REQ_LDO_VMA_APSS_HOLD_REQ_SHFT                                          0x4
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_START_REQ_BMSK                                        0x8
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_START_REQ_SHFT                                        0x3
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_RELEASE_REQ_BMSK                                      0x4
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_RELEASE_REQ_SHFT                                      0x2
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_LOCK_REQ_BMSK                                         0x2
#define HWIO_PMU_APSS_REQ_BIST_ADC_APSS_LOCK_REQ_SHFT                                         0x1
#define HWIO_PMU_APSS_REQ_TS_APSS_START_REQ_BMSK                                              0x1
#define HWIO_PMU_APSS_REQ_TS_APSS_START_REQ_SHFT                                              0x0

#define HWIO_PMU_APSS_STATUS_ADDR                                                      (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000018)
#define HWIO_PMU_APSS_STATUS_RMSK                                                          0x3fff
#define HWIO_PMU_APSS_STATUS_IN          \
        in_dword(HWIO_PMU_APSS_STATUS_ADDR)
#define HWIO_PMU_APSS_STATUS_INM(m)      \
        in_dword_masked(HWIO_PMU_APSS_STATUS_ADDR, m)
#define HWIO_PMU_APSS_STATUS_EXT_BD_EN_STATUS_BMSK                                         0x2000
#define HWIO_PMU_APSS_STATUS_EXT_BD_EN_STATUS_SHFT                                            0xd
#define HWIO_PMU_APSS_STATUS_BD_COMP_UNMAKSED_BMSK                                         0x1000
#define HWIO_PMU_APSS_STATUS_BD_COMP_UNMAKSED_SHFT                                            0xc
#define HWIO_PMU_APSS_STATUS_DU_COMP_UNMAKSED_BMSK                                          0x800
#define HWIO_PMU_APSS_STATUS_DU_COMP_UNMAKSED_SHFT                                            0xb
#define HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_AUTO_ON_STATUS_BMSK                               0x400
#define HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_AUTO_ON_STATUS_SHFT                                 0xa
#define HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_HOLD_STATUS_BMSK                                  0x200
#define HWIO_PMU_APSS_STATUS_LDO_VMA_APSS_HOLD_STATUS_SHFT                                    0x9
#define HWIO_PMU_APSS_STATUS_LDO_VMA_STARTUP_BUSY_BMSK                                      0x100
#define HWIO_PMU_APSS_STATUS_LDO_VMA_STARTUP_BUSY_SHFT                                        0x8
#define HWIO_PMU_APSS_STATUS_LDO_VMA_OK_BMSK                                                 0x80
#define HWIO_PMU_APSS_STATUS_LDO_VMA_OK_SHFT                                                  0x7
#define HWIO_PMU_APSS_STATUS_BIST_ADC_LOCKED_BMSK                                            0x40
#define HWIO_PMU_APSS_STATUS_BIST_ADC_LOCKED_SHFT                                             0x6
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_COMP_VALID_BMSK                                   0x20
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_COMP_VALID_SHFT                                    0x5
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_COMP_BMSK                                         0x10
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_COMP_SHFT                                          0x4
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_BUSY_BMSK                                          0x8
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_BUSY_SHFT                                          0x3
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_LOCK_REQ_PEND_BMSK                                 0x4
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_LOCK_REQ_PEND_SHFT                                 0x2
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_LOCKED_BMSK                                        0x2
#define HWIO_PMU_APSS_STATUS_BIST_ADC_APSS_LOCKED_SHFT                                        0x1
#define HWIO_PMU_APSS_STATUS_TS_APSS_BUSY_BMSK                                                0x1
#define HWIO_PMU_APSS_STATUS_TS_APSS_BUSY_SHFT                                                0x0

#define HWIO_PMU_TS_APSS_ANA_CONF_ADDR                                                 (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000001c)
#define HWIO_PMU_TS_APSS_ANA_CONF_RMSK                                                        0x1
#define HWIO_PMU_TS_APSS_ANA_CONF_IN          \
        in_dword(HWIO_PMU_TS_APSS_ANA_CONF_ADDR)
#define HWIO_PMU_TS_APSS_ANA_CONF_INM(m)      \
        in_dword_masked(HWIO_PMU_TS_APSS_ANA_CONF_ADDR, m)
#define HWIO_PMU_TS_APSS_ANA_CONF_OUT(v)      \
        out_dword(HWIO_PMU_TS_APSS_ANA_CONF_ADDR,v)
#define HWIO_PMU_TS_APSS_ANA_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_TS_APSS_ANA_CONF_ADDR,m,v,HWIO_PMU_TS_APSS_ANA_CONF_IN)
#define HWIO_PMU_TS_APSS_ANA_CONF_TS_APSS_ANA_FORCE_EN_BMSK                                   0x1
#define HWIO_PMU_TS_APSS_ANA_CONF_TS_APSS_ANA_FORCE_EN_SHFT                                   0x0

#define HWIO_PMU_TS_RESULT_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000020)
#define HWIO_PMU_TS_RESULT_RMSK                                                             0x1ff
#define HWIO_PMU_TS_RESULT_IN          \
        in_dword(HWIO_PMU_TS_RESULT_ADDR)
#define HWIO_PMU_TS_RESULT_INM(m)      \
        in_dword_masked(HWIO_PMU_TS_RESULT_ADDR, m)
#define HWIO_PMU_TS_RESULT_TS_RESULT_BMSK                                                   0x1ff
#define HWIO_PMU_TS_RESULT_TS_RESULT_SHFT                                                     0x0

#define HWIO_BIST_ADC_APSS_CONF_ADDR                                                   (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000024)
#define HWIO_BIST_ADC_APSS_CONF_RMSK                                                        0x7ff
#define HWIO_BIST_ADC_APSS_CONF_IN          \
        in_dword(HWIO_BIST_ADC_APSS_CONF_ADDR)
#define HWIO_BIST_ADC_APSS_CONF_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_APSS_CONF_ADDR, m)
#define HWIO_BIST_ADC_APSS_CONF_OUT(v)      \
        out_dword(HWIO_BIST_ADC_APSS_CONF_ADDR,v)
#define HWIO_BIST_ADC_APSS_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_ADC_APSS_CONF_ADDR,m,v,HWIO_BIST_ADC_APSS_CONF_IN)
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SUB_STATE_MAX_BMSK                            0x7c0
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SUB_STATE_MAX_SHFT                              0x6
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_LPF_BMSK                                   0x20
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_LPF_SHFT                                    0x5
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_REF_BMSK                                   0x10
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_REF_SHFT                                    0x4
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_FLIP_BMSK                                   0x8
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_FLIP_SHFT                                   0x3
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_10BIT_BMSK                                  0x4
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_10BIT_SHFT                                  0x2
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_DAC_BMSK                                    0x2
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_SEL_DAC_SHFT                                    0x1
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_AUTO_FLIP_BMSK                                  0x1
#define HWIO_BIST_ADC_APSS_CONF_BIST_ADC_APSS_AUTO_FLIP_SHFT                                  0x0

#define HWIO_BIST_APSS_CONF0_ADDR                                                      (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000028)
#define HWIO_BIST_APSS_CONF0_RMSK                                                          0x7fff
#define HWIO_BIST_APSS_CONF0_IN          \
        in_dword(HWIO_BIST_APSS_CONF0_ADDR)
#define HWIO_BIST_APSS_CONF0_INM(m)      \
        in_dword_masked(HWIO_BIST_APSS_CONF0_ADDR, m)
#define HWIO_BIST_APSS_CONF0_OUT(v)      \
        out_dword(HWIO_BIST_APSS_CONF0_ADDR,v)
#define HWIO_BIST_APSS_CONF0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_APSS_CONF0_ADDR,m,v,HWIO_BIST_APSS_CONF0_IN)
#define HWIO_BIST_APSS_CONF0_APSS_LDR_MEAS_SUPPLY_SEL_BMSK                                 0x6000
#define HWIO_BIST_APSS_CONF0_APSS_LDR_MEAS_SUPPLY_SEL_SHFT                                    0xd
#define HWIO_BIST_APSS_CONF0_APSS_LOAD_CELL_SEL_BMSK                                       0x1800
#define HWIO_BIST_APSS_CONF0_APSS_LOAD_CELL_SEL_SHFT                                          0xb
#define HWIO_BIST_APSS_CONF0_APSS_VBAT_MON_EN_BMSK                                          0x400
#define HWIO_BIST_APSS_CONF0_APSS_VBAT_MON_EN_SHFT                                            0xa
#define HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_BMSK                          0x380
#define HWIO_BIST_APSS_CONF0_BIST_APSS_LCD_PADS_AIO_SWITCH_EN_SHFT                            0x7
#define HWIO_BIST_APSS_CONF0_BIST_APSS_PIO_AMUX_EN_BMSK                                      0x78
#define HWIO_BIST_APSS_CONF0_BIST_APSS_PIO_AMUX_EN_SHFT                                       0x3
#define HWIO_BIST_APSS_CONF0_BIST_ADC_APSS_MUXSEL_BMSK                                        0x7
#define HWIO_BIST_APSS_CONF0_BIST_ADC_APSS_MUXSEL_SHFT                                        0x0

#define HWIO_BIST_APSS_CONF1_ADDR                                                      (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000002c)
#define HWIO_BIST_APSS_CONF1_RMSK                                                          0xffff
#define HWIO_BIST_APSS_CONF1_IN          \
        in_dword(HWIO_BIST_APSS_CONF1_ADDR)
#define HWIO_BIST_APSS_CONF1_INM(m)      \
        in_dword_masked(HWIO_BIST_APSS_CONF1_ADDR, m)
#define HWIO_BIST_APSS_CONF1_OUT(v)      \
        out_dword(HWIO_BIST_APSS_CONF1_ADDR,v)
#define HWIO_BIST_APSS_CONF1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_APSS_CONF1_ADDR,m,v,HWIO_BIST_APSS_CONF1_IN)
#define HWIO_BIST_APSS_CONF1_BIST_APSS_BIST_MUX_CTRL_BMSK                                  0xffff
#define HWIO_BIST_APSS_CONF1_BIST_APSS_BIST_MUX_CTRL_SHFT                                     0x0

#define HWIO_BIST_ADC_APSS_DAC_LEVEL_ADDR                                              (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000030)
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_RMSK                                                   0x3ff
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_IN          \
        in_dword(HWIO_BIST_ADC_APSS_DAC_LEVEL_ADDR)
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_APSS_DAC_LEVEL_ADDR, m)
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_OUT(v)      \
        out_dword(HWIO_BIST_ADC_APSS_DAC_LEVEL_ADDR,v)
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_ADC_APSS_DAC_LEVEL_ADDR,m,v,HWIO_BIST_ADC_APSS_DAC_LEVEL_IN)
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_BIST_ADC_APSS_DAC_LEVEL_BMSK                           0x3ff
#define HWIO_BIST_ADC_APSS_DAC_LEVEL_BIST_ADC_APSS_DAC_LEVEL_SHFT                             0x0

#define HWIO_BIST_ADC_APSS_DATA_ADDR                                                   (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000034)
#define HWIO_BIST_ADC_APSS_DATA_RMSK                                                        0x3ff
#define HWIO_BIST_ADC_APSS_DATA_IN          \
        in_dword(HWIO_BIST_ADC_APSS_DATA_ADDR)
#define HWIO_BIST_ADC_APSS_DATA_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_APSS_DATA_ADDR, m)
#define HWIO_BIST_ADC_APSS_DATA_BIST_ADC_APSS_DATA_BMSK                                     0x3ff
#define HWIO_BIST_ADC_APSS_DATA_BIST_ADC_APSS_DATA_SHFT                                       0x0

#define HWIO_PMU_INT_TME_OUT_ENA_ADDR                                                  (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000038)
#define HWIO_PMU_INT_TME_OUT_ENA_RMSK                                                         0x1
#define HWIO_PMU_INT_TME_OUT_ENA_IN          \
        in_dword(HWIO_PMU_INT_TME_OUT_ENA_ADDR)
#define HWIO_PMU_INT_TME_OUT_ENA_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_TME_OUT_ENA_ADDR, m)
#define HWIO_PMU_INT_TME_OUT_ENA_OUT(v)      \
        out_dword(HWIO_PMU_INT_TME_OUT_ENA_ADDR,v)
#define HWIO_PMU_INT_TME_OUT_ENA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_TME_OUT_ENA_ADDR,m,v,HWIO_PMU_INT_TME_OUT_ENA_IN)
#define HWIO_PMU_INT_TME_OUT_ENA_TME_INT_OUT_ENA_BMSK                                         0x1
#define HWIO_PMU_INT_TME_OUT_ENA_TME_INT_OUT_ENA_SHFT                                         0x0

#define HWIO_PMU_INT_TME_MASK_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000003c)
#define HWIO_PMU_INT_TME_MASK_RMSK                                                          0x3ff
#define HWIO_PMU_INT_TME_MASK_IN          \
        in_dword(HWIO_PMU_INT_TME_MASK_ADDR)
#define HWIO_PMU_INT_TME_MASK_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_TME_MASK_ADDR, m)
#define HWIO_PMU_INT_TME_MASK_OUT(v)      \
        out_dword(HWIO_PMU_INT_TME_MASK_ADDR,v)
#define HWIO_PMU_INT_TME_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_TME_MASK_ADDR,m,v,HWIO_PMU_INT_TME_MASK_IN)
#define HWIO_PMU_INT_TME_MASK_FOSC_STARTUP_DONE_INT_MASK_BMSK                               0x200
#define HWIO_PMU_INT_TME_MASK_FOSC_STARTUP_DONE_INT_MASK_SHFT                                 0x9
#define HWIO_PMU_INT_TME_MASK_LDO_PA_STARTUP_DONE_INT_MASK_BMSK                             0x100
#define HWIO_PMU_INT_TME_MASK_LDO_PA_STARTUP_DONE_INT_MASK_SHFT                               0x8
#define HWIO_PMU_INT_TME_MASK_LDO_RF_STARTUP_DONE_INT_MASK_BMSK                              0x80
#define HWIO_PMU_INT_TME_MASK_LDO_RF_STARTUP_DONE_INT_MASK_SHFT                               0x7
#define HWIO_PMU_INT_TME_MASK_LDO_VMA_QC_STARTUP_DONE_INT_MASK_BMSK                          0x40
#define HWIO_PMU_INT_TME_MASK_LDO_VMA_QC_STARTUP_DONE_INT_MASK_SHFT                           0x6
#define HWIO_PMU_INT_TME_MASK_BIST_ADC_QC_PENDING_LOCKED_INT_MASK_BMSK                       0x20
#define HWIO_PMU_INT_TME_MASK_BIST_ADC_QC_PENDING_LOCKED_INT_MASK_SHFT                        0x5
#define HWIO_PMU_INT_TME_MASK_SOSC_ERR_INT_MASK_BMSK                                         0x10
#define HWIO_PMU_INT_TME_MASK_SOSC_ERR_INT_MASK_SHFT                                          0x4
#define HWIO_PMU_INT_TME_MASK_FOSC_ERR_INT_MASK_BMSK                                          0x8
#define HWIO_PMU_INT_TME_MASK_FOSC_ERR_INT_MASK_SHFT                                          0x3
#define HWIO_PMU_INT_TME_MASK_LDO_DIG_VOL_RAMP_DONE_INT_MASK_BMSK                             0x4
#define HWIO_PMU_INT_TME_MASK_LDO_DIG_VOL_RAMP_DONE_INT_MASK_SHFT                             0x2
#define HWIO_PMU_INT_TME_MASK_TS_QC_REQ_DONE_INT_MASK_BMSK                                    0x2
#define HWIO_PMU_INT_TME_MASK_TS_QC_REQ_DONE_INT_MASK_SHFT                                    0x1
#define HWIO_PMU_INT_TME_MASK_BIST_ADC_QC_REQ_DONE_INT_MASK_BMSK                              0x1
#define HWIO_PMU_INT_TME_MASK_BIST_ADC_QC_REQ_DONE_INT_MASK_SHFT                              0x0

#define HWIO_PMU_INT_BTSS_OUT_ENA_ADDR                                                 (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000040)
#define HWIO_PMU_INT_BTSS_OUT_ENA_RMSK                                                        0x1
#define HWIO_PMU_INT_BTSS_OUT_ENA_IN          \
        in_dword(HWIO_PMU_INT_BTSS_OUT_ENA_ADDR)
#define HWIO_PMU_INT_BTSS_OUT_ENA_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_BTSS_OUT_ENA_ADDR, m)
#define HWIO_PMU_INT_BTSS_OUT_ENA_OUT(v)      \
        out_dword(HWIO_PMU_INT_BTSS_OUT_ENA_ADDR,v)
#define HWIO_PMU_INT_BTSS_OUT_ENA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_BTSS_OUT_ENA_ADDR,m,v,HWIO_PMU_INT_BTSS_OUT_ENA_IN)
#define HWIO_PMU_INT_BTSS_OUT_ENA_BTSS_INT_OUT_ENA_BMSK                                       0x1
#define HWIO_PMU_INT_BTSS_OUT_ENA_BTSS_INT_OUT_ENA_SHFT                                       0x0

#define HWIO_PMU_INT_BTSS_MASK_ADDR                                                    (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000044)
#define HWIO_PMU_INT_BTSS_MASK_RMSK                                                         0x3ff
#define HWIO_PMU_INT_BTSS_MASK_IN          \
        in_dword(HWIO_PMU_INT_BTSS_MASK_ADDR)
#define HWIO_PMU_INT_BTSS_MASK_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_BTSS_MASK_ADDR, m)
#define HWIO_PMU_INT_BTSS_MASK_OUT(v)      \
        out_dword(HWIO_PMU_INT_BTSS_MASK_ADDR,v)
#define HWIO_PMU_INT_BTSS_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_INT_BTSS_MASK_ADDR,m,v,HWIO_PMU_INT_BTSS_MASK_IN)
#define HWIO_PMU_INT_BTSS_MASK_FOSC_STARTUP_DONE_INT_MASK_BMSK                              0x200
#define HWIO_PMU_INT_BTSS_MASK_FOSC_STARTUP_DONE_INT_MASK_SHFT                                0x9
#define HWIO_PMU_INT_BTSS_MASK_LDO_PA_STARTUP_DONE_INT_MASK_BMSK                            0x100
#define HWIO_PMU_INT_BTSS_MASK_LDO_PA_STARTUP_DONE_INT_MASK_SHFT                              0x8
#define HWIO_PMU_INT_BTSS_MASK_LDO_RF_STARTUP_DONE_INT_MASK_BMSK                             0x80
#define HWIO_PMU_INT_BTSS_MASK_LDO_RF_STARTUP_DONE_INT_MASK_SHFT                              0x7
#define HWIO_PMU_INT_BTSS_MASK_LDO_VMA_QC_STARTUP_DONE_INT_MASK_BMSK                         0x40
#define HWIO_PMU_INT_BTSS_MASK_LDO_VMA_QC_STARTUP_DONE_INT_MASK_SHFT                          0x6
#define HWIO_PMU_INT_BTSS_MASK_BIST_ADC_QC_PENDING_LOCKED_INT_MASK_BMSK                      0x20
#define HWIO_PMU_INT_BTSS_MASK_BIST_ADC_QC_PENDING_LOCKED_INT_MASK_SHFT                       0x5
#define HWIO_PMU_INT_BTSS_MASK_SOSC_ERR_INT_MASK_BMSK                                        0x10
#define HWIO_PMU_INT_BTSS_MASK_SOSC_ERR_INT_MASK_SHFT                                         0x4
#define HWIO_PMU_INT_BTSS_MASK_FOSC_ERR_INT_MASK_BMSK                                         0x8
#define HWIO_PMU_INT_BTSS_MASK_FOSC_ERR_INT_MASK_SHFT                                         0x3
#define HWIO_PMU_INT_BTSS_MASK_LDO_DIG_VOL_RAMP_DONE_INT_MASK_BMSK                            0x4
#define HWIO_PMU_INT_BTSS_MASK_LDO_DIG_VOL_RAMP_DONE_INT_MASK_SHFT                            0x2
#define HWIO_PMU_INT_BTSS_MASK_TS_QC_REQ_DONE_INT_MASK_BMSK                                   0x2
#define HWIO_PMU_INT_BTSS_MASK_TS_QC_REQ_DONE_INT_MASK_SHFT                                   0x1
#define HWIO_PMU_INT_BTSS_MASK_BIST_ADC_QC_REQ_DONE_INT_MASK_BMSK                             0x1
#define HWIO_PMU_INT_BTSS_MASK_BIST_ADC_QC_REQ_DONE_INT_MASK_SHFT                             0x0

#define HWIO_PMU_INT_QC_STATUS_ADDR                                                    (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000048)
#define HWIO_PMU_INT_QC_STATUS_RMSK                                                         0x3ff
#define HWIO_PMU_INT_QC_STATUS_IN          \
        in_dword(HWIO_PMU_INT_QC_STATUS_ADDR)
#define HWIO_PMU_INT_QC_STATUS_INM(m)      \
        in_dword_masked(HWIO_PMU_INT_QC_STATUS_ADDR, m)
#define HWIO_PMU_INT_QC_STATUS_FOSC_STARTUP_DONE_INT_STATUS_BMSK                            0x200
#define HWIO_PMU_INT_QC_STATUS_FOSC_STARTUP_DONE_INT_STATUS_SHFT                              0x9
#define HWIO_PMU_INT_QC_STATUS_LDO_PA_STARTUP_DONE_INT_STATUS_BMSK                          0x100
#define HWIO_PMU_INT_QC_STATUS_LDO_PA_STARTUP_DONE_INT_STATUS_SHFT                            0x8
#define HWIO_PMU_INT_QC_STATUS_LDO_RF_STARTUP_DONE_INT_STATUS_BMSK                           0x80
#define HWIO_PMU_INT_QC_STATUS_LDO_RF_STARTUP_DONE_INT_STATUS_SHFT                            0x7
#define HWIO_PMU_INT_QC_STATUS_LDO_VMA_QC_STARTUP_DONE_INT_STATUS_BMSK                       0x40
#define HWIO_PMU_INT_QC_STATUS_LDO_VMA_QC_STARTUP_DONE_INT_STATUS_SHFT                        0x6
#define HWIO_PMU_INT_QC_STATUS_BIST_ADC_QC_PENDING_LOCKED_INT_STATUS_BMSK                    0x20
#define HWIO_PMU_INT_QC_STATUS_BIST_ADC_QC_PENDING_LOCKED_INT_STATUS_SHFT                     0x5
#define HWIO_PMU_INT_QC_STATUS_SOSC_ERR_INT_STATUS_BMSK                                      0x10
#define HWIO_PMU_INT_QC_STATUS_SOSC_ERR_INT_STATUS_SHFT                                       0x4
#define HWIO_PMU_INT_QC_STATUS_FOSC_ERR_INT_STATUS_BMSK                                       0x8
#define HWIO_PMU_INT_QC_STATUS_FOSC_ERR_INT_STATUS_SHFT                                       0x3
#define HWIO_PMU_INT_QC_STATUS_LDO_DIG_VOL_RAMP_DONE_INT_STATUS_BMSK                          0x4
#define HWIO_PMU_INT_QC_STATUS_LDO_DIG_VOL_RAMP_DONE_INT_STATUS_SHFT                          0x2
#define HWIO_PMU_INT_QC_STATUS_TS_QC_REQ_DONE_INT_STATUS_BMSK                                 0x2
#define HWIO_PMU_INT_QC_STATUS_TS_QC_REQ_DONE_INT_STATUS_SHFT                                 0x1
#define HWIO_PMU_INT_QC_STATUS_BIST_ADC_QC_REQ_DONE_INT_STATUS_BMSK                           0x1
#define HWIO_PMU_INT_QC_STATUS_BIST_ADC_QC_REQ_DONE_INT_STATUS_SHFT                           0x0

#define HWIO_PMU_INT_QC_CLR_ADDR                                                       (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000004c)
#define HWIO_PMU_INT_QC_CLR_RMSK                                                            0x3ff
#define HWIO_PMU_INT_QC_CLR_OUT(v)      \
        out_dword(HWIO_PMU_INT_QC_CLR_ADDR,v)
#define HWIO_PMU_INT_QC_CLR_FOSC_STARTUP_DONE_INT_CLR_BMSK                                  0x200
#define HWIO_PMU_INT_QC_CLR_FOSC_STARTUP_DONE_INT_CLR_SHFT                                    0x9
#define HWIO_PMU_INT_QC_CLR_LDO_PA_STARTUP_DONE_INT_CLR_BMSK                                0x100
#define HWIO_PMU_INT_QC_CLR_LDO_PA_STARTUP_DONE_INT_CLR_SHFT                                  0x8
#define HWIO_PMU_INT_QC_CLR_LDO_RF_STARTUP_DONE_INT_CLR_BMSK                                 0x80
#define HWIO_PMU_INT_QC_CLR_LDO_RF_STARTUP_DONE_INT_CLR_SHFT                                  0x7
#define HWIO_PMU_INT_QC_CLR_LDO_VMA_QC_STARTUP_DONE_INT_CLR_BMSK                             0x40
#define HWIO_PMU_INT_QC_CLR_LDO_VMA_QC_STARTUP_DONE_INT_CLR_SHFT                              0x6
#define HWIO_PMU_INT_QC_CLR_BIST_ADC_QC_PENDING_LOCKED_INT_CLR_BMSK                          0x20
#define HWIO_PMU_INT_QC_CLR_BIST_ADC_QC_PENDING_LOCKED_INT_CLR_SHFT                           0x5
#define HWIO_PMU_INT_QC_CLR_SOSC_ERR_INT_CLR_BMSK                                            0x10
#define HWIO_PMU_INT_QC_CLR_SOSC_ERR_INT_CLR_SHFT                                             0x4
#define HWIO_PMU_INT_QC_CLR_FOSC_ERR_INT_CLR_BMSK                                             0x8
#define HWIO_PMU_INT_QC_CLR_FOSC_ERR_INT_CLR_SHFT                                             0x3
#define HWIO_PMU_INT_QC_CLR_LDO_DIG_VOL_RAMP_DONE_INT_CLR_BMSK                                0x4
#define HWIO_PMU_INT_QC_CLR_LDO_DIG_VOL_RAMP_DONE_INT_CLR_SHFT                                0x2
#define HWIO_PMU_INT_QC_CLR_TS_QC_REQ_DONE_INT_CLR_BMSK                                       0x2
#define HWIO_PMU_INT_QC_CLR_TS_QC_REQ_DONE_INT_CLR_SHFT                                       0x1
#define HWIO_PMU_INT_QC_CLR_BIST_ADC_QC_REQ_DONE_INT_CLR_BMSK                                 0x1
#define HWIO_PMU_INT_QC_CLR_BIST_ADC_QC_REQ_DONE_INT_CLR_SHFT                                 0x0

#define HWIO_PMU_INT_QC_SET_ADDR                                                       (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000050)
#define HWIO_PMU_INT_QC_SET_RMSK                                                            0x3ff
#define HWIO_PMU_INT_QC_SET_OUT(v)      \
        out_dword(HWIO_PMU_INT_QC_SET_ADDR,v)
#define HWIO_PMU_INT_QC_SET_FOSC_STARTUP_DONE_INT_SET_BMSK                                  0x200
#define HWIO_PMU_INT_QC_SET_FOSC_STARTUP_DONE_INT_SET_SHFT                                    0x9
#define HWIO_PMU_INT_QC_SET_LDO_PA_STARTUP_DONE_INT_SET_BMSK                                0x100
#define HWIO_PMU_INT_QC_SET_LDO_PA_STARTUP_DONE_INT_SET_SHFT                                  0x8
#define HWIO_PMU_INT_QC_SET_LDO_RF_STARTUP_DONE_INT_SET_BMSK                                 0x80
#define HWIO_PMU_INT_QC_SET_LDO_RF_STARTUP_DONE_INT_SET_SHFT                                  0x7
#define HWIO_PMU_INT_QC_SET_LDO_VMA_QC_STARTUP_DONE_INT_SET_BMSK                             0x40
#define HWIO_PMU_INT_QC_SET_LDO_VMA_QC_STARTUP_DONE_INT_SET_SHFT                              0x6
#define HWIO_PMU_INT_QC_SET_BIST_ADC_QC_PENDING_LOCKED_INT_SET_BMSK                          0x20
#define HWIO_PMU_INT_QC_SET_BIST_ADC_QC_PENDING_LOCKED_INT_SET_SHFT                           0x5
#define HWIO_PMU_INT_QC_SET_SOSC_ERR_INT_SET_BMSK                                            0x10
#define HWIO_PMU_INT_QC_SET_SOSC_ERR_INT_SET_SHFT                                             0x4
#define HWIO_PMU_INT_QC_SET_FOSC_ERR_INT_SET_BMSK                                             0x8
#define HWIO_PMU_INT_QC_SET_FOSC_ERR_INT_SET_SHFT                                             0x3
#define HWIO_PMU_INT_QC_SET_LDO_DIG_VOL_RAMP_DONE_INT_SET_BMSK                                0x4
#define HWIO_PMU_INT_QC_SET_LDO_DIG_VOL_RAMP_DONE_INT_SET_SHFT                                0x2
#define HWIO_PMU_INT_QC_SET_TS_QC_REQ_DONE_INT_SET_BMSK                                       0x2
#define HWIO_PMU_INT_QC_SET_TS_QC_REQ_DONE_INT_SET_SHFT                                       0x1
#define HWIO_PMU_INT_QC_SET_BIST_ADC_QC_REQ_DONE_INT_SET_BMSK                                 0x1
#define HWIO_PMU_INT_QC_SET_BIST_ADC_QC_REQ_DONE_INT_SET_SHFT                                 0x0

#define HWIO_PMU_QC_REQ_ADDR                                                           (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000054)
#define HWIO_PMU_QC_REQ_RMSK                                                               0x7fff
#define HWIO_PMU_QC_REQ_OUT(v)      \
        out_dword(HWIO_PMU_QC_REQ_ADDR,v)
#define HWIO_PMU_QC_REQ_SMPS_ANA_CLK_UPDATE_REQ_BMSK                                       0x4000
#define HWIO_PMU_QC_REQ_SMPS_ANA_CLK_UPDATE_REQ_SHFT                                          0xe
#define HWIO_PMU_QC_REQ_LDO_DIG_VOL_RAMP_REQ_BMSK                                          0x2000
#define HWIO_PMU_QC_REQ_LDO_DIG_VOL_RAMP_REQ_SHFT                                             0xd
#define HWIO_PMU_QC_REQ_LDO_RF_PA_STAGGERED_ON_REQ_BMSK                                    0x1000
#define HWIO_PMU_QC_REQ_LDO_RF_PA_STAGGERED_ON_REQ_SHFT                                       0xc
#define HWIO_PMU_QC_REQ_LDO_PA_OFF_REQ_BMSK                                                 0x800
#define HWIO_PMU_QC_REQ_LDO_PA_OFF_REQ_SHFT                                                   0xb
#define HWIO_PMU_QC_REQ_LDO_PA_ON_REQ_BMSK                                                  0x400
#define HWIO_PMU_QC_REQ_LDO_PA_ON_REQ_SHFT                                                    0xa
#define HWIO_PMU_QC_REQ_LDO_RF_OFF_REQ_BMSK                                                 0x200
#define HWIO_PMU_QC_REQ_LDO_RF_OFF_REQ_SHFT                                                   0x9
#define HWIO_PMU_QC_REQ_LDO_RF_ON_REQ_BMSK                                                  0x100
#define HWIO_PMU_QC_REQ_LDO_RF_ON_REQ_SHFT                                                    0x8
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_AUTO_ON_DISABLE_REQ_BMSK                                  0x80
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_AUTO_ON_DISABLE_REQ_SHFT                                   0x7
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_AUTO_ON_ENABLE_REQ_BMSK                                   0x40
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_AUTO_ON_ENABLE_REQ_SHFT                                    0x6
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_RELEASE_REQ_BMSK                                          0x20
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_RELEASE_REQ_SHFT                                           0x5
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_HOLD_REQ_BMSK                                             0x10
#define HWIO_PMU_QC_REQ_LDO_VMA_QC_HOLD_REQ_SHFT                                              0x4
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_START_REQ_BMSK                                            0x8
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_START_REQ_SHFT                                            0x3
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_RELEASE_REQ_BMSK                                          0x4
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_RELEASE_REQ_SHFT                                          0x2
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_LOCK_REQ_BMSK                                             0x2
#define HWIO_PMU_QC_REQ_BIST_ADC_QC_LOCK_REQ_SHFT                                             0x1
#define HWIO_PMU_QC_REQ_TS_QC_START_REQ_BMSK                                                  0x1
#define HWIO_PMU_QC_REQ_TS_QC_START_REQ_SHFT                                                  0x0

#define HWIO_PMU_CLK_FAST_CONFIG_ADDR                                                  (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000058)
#define HWIO_PMU_CLK_FAST_CONFIG_RMSK                                                         0x1
#define HWIO_PMU_CLK_FAST_CONFIG_IN          \
        in_dword(HWIO_PMU_CLK_FAST_CONFIG_ADDR)
#define HWIO_PMU_CLK_FAST_CONFIG_INM(m)      \
        in_dword_masked(HWIO_PMU_CLK_FAST_CONFIG_ADDR, m)
#define HWIO_PMU_CLK_FAST_CONFIG_OUT(v)      \
        out_dword(HWIO_PMU_CLK_FAST_CONFIG_ADDR,v)
#define HWIO_PMU_CLK_FAST_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_CLK_FAST_CONFIG_ADDR,m,v,HWIO_PMU_CLK_FAST_CONFIG_IN)
#define HWIO_PMU_CLK_FAST_CONFIG_CLK_FAST_SRC_SEL_BMSK                                        0x1
#define HWIO_PMU_CLK_FAST_CONFIG_CLK_FAST_SRC_SEL_SHFT                                        0x0

#define HWIO_PMU_QC_STATUS_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000005c)
#define HWIO_PMU_QC_STATUS_RMSK                                                            0xffff
#define HWIO_PMU_QC_STATUS_IN          \
        in_dword(HWIO_PMU_QC_STATUS_ADDR)
#define HWIO_PMU_QC_STATUS_INM(m)      \
        in_dword_masked(HWIO_PMU_QC_STATUS_ADDR, m)
#define HWIO_PMU_QC_STATUS_SOSC_OK_BMSK                                                    0x8000
#define HWIO_PMU_QC_STATUS_SOSC_OK_SHFT                                                       0xf
#define HWIO_PMU_QC_STATUS_FOSC_OK_BMSK                                                    0x4000
#define HWIO_PMU_QC_STATUS_FOSC_OK_SHFT                                                       0xe
#define HWIO_PMU_QC_STATUS_AHM_DEBOUNCING_EXT_CLK_STATUS_BMSK                              0x2000
#define HWIO_PMU_QC_STATUS_AHM_DEBOUNCING_EXT_CLK_STATUS_SHFT                                 0xd
#define HWIO_PMU_QC_STATUS_VLP_RAMP_UP_BUSY_BMSK                                           0x1000
#define HWIO_PMU_QC_STATUS_VLP_RAMP_UP_BUSY_SHFT                                              0xc
#define HWIO_PMU_QC_STATUS_EXT_BD_EN_STATUS_BMSK                                            0x800
#define HWIO_PMU_QC_STATUS_EXT_BD_EN_STATUS_SHFT                                              0xb
#define HWIO_PMU_QC_STATUS_BD_COMP_UNMAKSED_BMSK                                            0x400
#define HWIO_PMU_QC_STATUS_BD_COMP_UNMAKSED_SHFT                                              0xa
#define HWIO_PMU_QC_STATUS_DU_COMP_UNMAKSED_BMSK                                            0x200
#define HWIO_PMU_QC_STATUS_DU_COMP_UNMAKSED_SHFT                                              0x9
#define HWIO_PMU_QC_STATUS_LDO_VMA_QC_AUTO_ON_STATUS_BMSK                                   0x100
#define HWIO_PMU_QC_STATUS_LDO_VMA_QC_AUTO_ON_STATUS_SHFT                                     0x8
#define HWIO_PMU_QC_STATUS_LDO_VMA_QC_HOLD_STATUS_BMSK                                       0x80
#define HWIO_PMU_QC_STATUS_LDO_VMA_QC_HOLD_STATUS_SHFT                                        0x7
#define HWIO_PMU_QC_STATUS_BIST_ADC_LOCKED_BMSK                                              0x40
#define HWIO_PMU_QC_STATUS_BIST_ADC_LOCKED_SHFT                                               0x6
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_COMP_VALID_BMSK                                       0x20
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_COMP_VALID_SHFT                                        0x5
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_COMP_BMSK                                             0x10
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_COMP_SHFT                                              0x4
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_BUSY_BMSK                                              0x8
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_BUSY_SHFT                                              0x3
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_LOCK_REQ_PEND_BMSK                                     0x4
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_LOCK_REQ_PEND_SHFT                                     0x2
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_LOCKED_BMSK                                            0x2
#define HWIO_PMU_QC_STATUS_BIST_ADC_QC_LOCKED_SHFT                                            0x1
#define HWIO_PMU_QC_STATUS_TS_QC_BUSY_BMSK                                                    0x1
#define HWIO_PMU_QC_STATUS_TS_QC_BUSY_SHFT                                                    0x0

#define HWIO_PLA_LDO_STATUS_ADDR                                                       (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000060)
#define HWIO_PLA_LDO_STATUS_RMSK                                                            0xfff
#define HWIO_PLA_LDO_STATUS_IN          \
        in_dword(HWIO_PLA_LDO_STATUS_ADDR)
#define HWIO_PLA_LDO_STATUS_INM(m)      \
        in_dword_masked(HWIO_PLA_LDO_STATUS_ADDR, m)
#define HWIO_PLA_LDO_STATUS_LDO_DIG_VOL_STATUS_BMSK                                         0xf80
#define HWIO_PLA_LDO_STATUS_LDO_DIG_VOL_STATUS_SHFT                                           0x7
#define HWIO_PLA_LDO_STATUS_LDO_DIG_VOL_RAMP_BUSY_BMSK                                       0x40
#define HWIO_PLA_LDO_STATUS_LDO_DIG_VOL_RAMP_BUSY_SHFT                                        0x6
#define HWIO_PLA_LDO_STATUS_LDO_PA_STARTUP_BUSY_BMSK                                         0x20
#define HWIO_PLA_LDO_STATUS_LDO_PA_STARTUP_BUSY_SHFT                                          0x5
#define HWIO_PLA_LDO_STATUS_LDO_RF_STARTUP_BUSY_BMSK                                         0x10
#define HWIO_PLA_LDO_STATUS_LDO_RF_STARTUP_BUSY_SHFT                                          0x4
#define HWIO_PLA_LDO_STATUS_LDO_VMA_STARTUP_BUSY_BMSK                                         0x8
#define HWIO_PLA_LDO_STATUS_LDO_VMA_STARTUP_BUSY_SHFT                                         0x3
#define HWIO_PLA_LDO_STATUS_LDO_PA_OK_BMSK                                                    0x4
#define HWIO_PLA_LDO_STATUS_LDO_PA_OK_SHFT                                                    0x2
#define HWIO_PLA_LDO_STATUS_LDO_RF_OK_BMSK                                                    0x2
#define HWIO_PLA_LDO_STATUS_LDO_RF_OK_SHFT                                                    0x1
#define HWIO_PLA_LDO_STATUS_LDO_VMA_OK_BMSK                                                   0x1
#define HWIO_PLA_LDO_STATUS_LDO_VMA_OK_SHFT                                                   0x0

#define HWIO_PMU_FOSC_CTRL_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000064)
#define HWIO_PMU_FOSC_CTRL_RMSK                                                               0x3
#define HWIO_PMU_FOSC_CTRL_OUT(v)      \
        out_dword(HWIO_PMU_FOSC_CTRL_ADDR,v)
#define HWIO_PMU_FOSC_CTRL_FOSC_OFF_REQ_BMSK                                                  0x2
#define HWIO_PMU_FOSC_CTRL_FOSC_OFF_REQ_SHFT                                                  0x1
#define HWIO_PMU_FOSC_CTRL_FOSC_ON_REQ_BMSK                                                   0x1
#define HWIO_PMU_FOSC_CTRL_FOSC_ON_REQ_SHFT                                                   0x0

#define HWIO_PMU_BD_COMP_CTRL_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000068)
#define HWIO_PMU_BD_COMP_CTRL_RMSK                                                            0x1
#define HWIO_PMU_BD_COMP_CTRL_IN          \
        in_dword(HWIO_PMU_BD_COMP_CTRL_ADDR)
#define HWIO_PMU_BD_COMP_CTRL_INM(m)      \
        in_dword_masked(HWIO_PMU_BD_COMP_CTRL_ADDR, m)
#define HWIO_PMU_BD_COMP_CTRL_OUT(v)      \
        out_dword(HWIO_PMU_BD_COMP_CTRL_ADDR,v)
#define HWIO_PMU_BD_COMP_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_BD_COMP_CTRL_ADDR,m,v,HWIO_PMU_BD_COMP_CTRL_IN)
#define HWIO_PMU_BD_COMP_CTRL_BD_COMP_EN_BMSK                                                 0x1
#define HWIO_PMU_BD_COMP_CTRL_BD_COMP_EN_SHFT                                                 0x0

#define HWIO_PMU_BD_COMP_CONF_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000006c)
#define HWIO_PMU_BD_COMP_CONF_RMSK                                                           0xff
#define HWIO_PMU_BD_COMP_CONF_IN          \
        in_dword(HWIO_PMU_BD_COMP_CONF_ADDR)
#define HWIO_PMU_BD_COMP_CONF_INM(m)      \
        in_dword_masked(HWIO_PMU_BD_COMP_CONF_ADDR, m)
#define HWIO_PMU_BD_COMP_CONF_OUT(v)      \
        out_dword(HWIO_PMU_BD_COMP_CONF_ADDR,v)
#define HWIO_PMU_BD_COMP_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_BD_COMP_CONF_ADDR,m,v,HWIO_PMU_BD_COMP_CONF_IN)
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_CHK_DLY_TIMER_VAL_BMSK                                 0xe0
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_CHK_DLY_TIMER_VAL_SHFT                                  0x5
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_OUT_PT_ENA_BMSK                                        0x10
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_OUT_PT_ENA_SHFT                                         0x4
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_EXT_CTRL_ENA_BMSK                                       0x8
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_EXT_CTRL_ENA_SHFT                                       0x3
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_THRESHOLD_BMSK                                          0x7
#define HWIO_PMU_BD_COMP_CONF_BD_COMP_THRESHOLD_SHFT                                          0x0

#define HWIO_PMU_DU_COMP_CTRL_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000070)
#define HWIO_PMU_DU_COMP_CTRL_RMSK                                                            0x1
#define HWIO_PMU_DU_COMP_CTRL_IN          \
        in_dword(HWIO_PMU_DU_COMP_CTRL_ADDR)
#define HWIO_PMU_DU_COMP_CTRL_INM(m)      \
        in_dword_masked(HWIO_PMU_DU_COMP_CTRL_ADDR, m)
#define HWIO_PMU_DU_COMP_CTRL_OUT(v)      \
        out_dword(HWIO_PMU_DU_COMP_CTRL_ADDR,v)
#define HWIO_PMU_DU_COMP_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_DU_COMP_CTRL_ADDR,m,v,HWIO_PMU_DU_COMP_CTRL_IN)
#define HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_BMSK                                                 0x1
#define HWIO_PMU_DU_COMP_CTRL_DU_COMP_EN_SHFT                                                 0x0

#define HWIO_PMU_DU_COMP_CONF_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000074)
#define HWIO_PMU_DU_COMP_CONF_RMSK                                                           0xff
#define HWIO_PMU_DU_COMP_CONF_IN          \
        in_dword(HWIO_PMU_DU_COMP_CONF_ADDR)
#define HWIO_PMU_DU_COMP_CONF_INM(m)      \
        in_dword_masked(HWIO_PMU_DU_COMP_CONF_ADDR, m)
#define HWIO_PMU_DU_COMP_CONF_OUT(v)      \
        out_dword(HWIO_PMU_DU_COMP_CONF_ADDR,v)
#define HWIO_PMU_DU_COMP_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_DU_COMP_CONF_ADDR,m,v,HWIO_PMU_DU_COMP_CONF_IN)
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_CHK_DLY_TIMER_VAL_BMSK                                 0xe0
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_CHK_DLY_TIMER_VAL_SHFT                                  0x5
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_OUT_PT_ENA_BMSK                                        0x10
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_OUT_PT_ENA_SHFT                                         0x4
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_THRESHOLD_BMSK                                          0xf
#define HWIO_PMU_DU_COMP_CONF_DU_COMP_THRESHOLD_SHFT                                          0x0

#define HWIO_PMU_TS_QC_ANA_CONF_ADDR                                                   (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000078)
#define HWIO_PMU_TS_QC_ANA_CONF_RMSK                                                          0x1
#define HWIO_PMU_TS_QC_ANA_CONF_IN          \
        in_dword(HWIO_PMU_TS_QC_ANA_CONF_ADDR)
#define HWIO_PMU_TS_QC_ANA_CONF_INM(m)      \
        in_dword_masked(HWIO_PMU_TS_QC_ANA_CONF_ADDR, m)
#define HWIO_PMU_TS_QC_ANA_CONF_OUT(v)      \
        out_dword(HWIO_PMU_TS_QC_ANA_CONF_ADDR,v)
#define HWIO_PMU_TS_QC_ANA_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_TS_QC_ANA_CONF_ADDR,m,v,HWIO_PMU_TS_QC_ANA_CONF_IN)
#define HWIO_PMU_TS_QC_ANA_CONF_TS_QC_ANA_FORCE_EN_BMSK                                       0x1
#define HWIO_PMU_TS_QC_ANA_CONF_TS_QC_ANA_FORCE_EN_SHFT                                       0x0

#define HWIO_PMU_TS_TIMING_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000007c)
#define HWIO_PMU_TS_TIMING_RMSK                                                            0x3fff
#define HWIO_PMU_TS_TIMING_IN          \
        in_dword(HWIO_PMU_TS_TIMING_ADDR)
#define HWIO_PMU_TS_TIMING_INM(m)      \
        in_dword_masked(HWIO_PMU_TS_TIMING_ADDR, m)
#define HWIO_PMU_TS_TIMING_OUT(v)      \
        out_dword(HWIO_PMU_TS_TIMING_ADDR,v)
#define HWIO_PMU_TS_TIMING_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_TS_TIMING_ADDR,m,v,HWIO_PMU_TS_TIMING_IN)
#define HWIO_PMU_TS_TIMING_TS_T_LATCH_AZ_BMSK                                              0x2000
#define HWIO_PMU_TS_TIMING_TS_T_LATCH_AZ_SHFT                                                 0xd
#define HWIO_PMU_TS_TIMING_TS_T_LATCH_BMSK                                                 0x1000
#define HWIO_PMU_TS_TIMING_TS_T_LATCH_SHFT                                                    0xc
#define HWIO_PMU_TS_TIMING_TS_T_RESET_LATCH_BMSK                                            0x800
#define HWIO_PMU_TS_TIMING_TS_T_RESET_LATCH_SHFT                                              0xb
#define HWIO_PMU_TS_TIMING_TS_T_RESET_BIT_BMSK                                              0x400
#define HWIO_PMU_TS_TIMING_TS_T_RESET_BIT_SHFT                                                0xa
#define HWIO_PMU_TS_TIMING_TS_T_RESET_BMSK                                                  0x200
#define HWIO_PMU_TS_TIMING_TS_T_RESET_SHFT                                                    0x9
#define HWIO_PMU_TS_TIMING_TS_T_AZ_LOW_RESET_BMSK                                           0x100
#define HWIO_PMU_TS_TIMING_TS_T_AZ_LOW_RESET_SHFT                                             0x8
#define HWIO_PMU_TS_TIMING_TS_T_AZ_BMSK                                                      0xe0
#define HWIO_PMU_TS_TIMING_TS_T_AZ_SHFT                                                       0x5
#define HWIO_PMU_TS_TIMING_TS_T_RESET_LOW_AZ_BMSK                                            0x10
#define HWIO_PMU_TS_TIMING_TS_T_RESET_LOW_AZ_SHFT                                             0x4
#define HWIO_PMU_TS_TIMING_TS_SEL_AZ_BMSK                                                     0x8
#define HWIO_PMU_TS_TIMING_TS_SEL_AZ_SHFT                                                     0x3
#define HWIO_PMU_TS_TIMING_TS_PRESCALER_RATIO_BMSK                                            0x7
#define HWIO_PMU_TS_TIMING_TS_PRESCALER_RATIO_SHFT                                            0x0

#define HWIO_BIST_ADC_COMMON_CONF_ADDR                                                 (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000080)
#define HWIO_BIST_ADC_COMMON_CONF_RMSK                                                       0x1f
#define HWIO_BIST_ADC_COMMON_CONF_IN          \
        in_dword(HWIO_BIST_ADC_COMMON_CONF_ADDR)
#define HWIO_BIST_ADC_COMMON_CONF_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_COMMON_CONF_ADDR, m)
#define HWIO_BIST_ADC_COMMON_CONF_OUT(v)      \
        out_dword(HWIO_BIST_ADC_COMMON_CONF_ADDR,v)
#define HWIO_BIST_ADC_COMMON_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_ADC_COMMON_CONF_ADDR,m,v,HWIO_BIST_ADC_COMMON_CONF_IN)
#define HWIO_BIST_ADC_COMMON_CONF_BIST_ADC_SUB_STATE_MAX_BMSK                                0x1f
#define HWIO_BIST_ADC_COMMON_CONF_BIST_ADC_SUB_STATE_MAX_SHFT                                 0x0

#define HWIO_BIST_ADC_QC_CONF_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000084)
#define HWIO_BIST_ADC_QC_CONF_RMSK                                                           0x3f
#define HWIO_BIST_ADC_QC_CONF_IN          \
        in_dword(HWIO_BIST_ADC_QC_CONF_ADDR)
#define HWIO_BIST_ADC_QC_CONF_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_QC_CONF_ADDR, m)
#define HWIO_BIST_ADC_QC_CONF_OUT(v)      \
        out_dword(HWIO_BIST_ADC_QC_CONF_ADDR,v)
#define HWIO_BIST_ADC_QC_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_ADC_QC_CONF_ADDR,m,v,HWIO_BIST_ADC_QC_CONF_IN)
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_LPF_BMSK                                       0x20
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_LPF_SHFT                                        0x5
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_REF_BMSK                                       0x10
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_REF_SHFT                                        0x4
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_FLIP_BMSK                                       0x8
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_FLIP_SHFT                                       0x3
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_10BIT_BMSK                                      0x4
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_10BIT_SHFT                                      0x2
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_DAC_BMSK                                        0x2
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_SEL_DAC_SHFT                                        0x1
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_AUTO_FLIP_BMSK                                      0x1
#define HWIO_BIST_ADC_QC_CONF_BIST_ADC_QC_AUTO_FLIP_SHFT                                      0x0

#define HWIO_BIST_QC_CONF0_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000088)
#define HWIO_BIST_QC_CONF0_RMSK                                                            0x1fff
#define HWIO_BIST_QC_CONF0_IN          \
        in_dword(HWIO_BIST_QC_CONF0_ADDR)
#define HWIO_BIST_QC_CONF0_INM(m)      \
        in_dword_masked(HWIO_BIST_QC_CONF0_ADDR, m)
#define HWIO_BIST_QC_CONF0_OUT(v)      \
        out_dword(HWIO_BIST_QC_CONF0_ADDR,v)
#define HWIO_BIST_QC_CONF0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_QC_CONF0_ADDR,m,v,HWIO_BIST_QC_CONF0_IN)
#define HWIO_BIST_QC_CONF0_QC_LOAD_CELL_SEL_BMSK                                           0x1800
#define HWIO_BIST_QC_CONF0_QC_LOAD_CELL_SEL_SHFT                                              0xb
#define HWIO_BIST_QC_CONF0_QC_VBAT_MON_EN_BMSK                                              0x400
#define HWIO_BIST_QC_CONF0_QC_VBAT_MON_EN_SHFT                                                0xa
#define HWIO_BIST_QC_CONF0_BIST_QC_LCD_PADS_AIO_SWITCH_EN_BMSK                              0x380
#define HWIO_BIST_QC_CONF0_BIST_QC_LCD_PADS_AIO_SWITCH_EN_SHFT                                0x7
#define HWIO_BIST_QC_CONF0_BIST_QC_PIO_AMUX_EN_BMSK                                          0x78
#define HWIO_BIST_QC_CONF0_BIST_QC_PIO_AMUX_EN_SHFT                                           0x3
#define HWIO_BIST_QC_CONF0_BIST_ADC_QC_MUXSEL_BMSK                                            0x7
#define HWIO_BIST_QC_CONF0_BIST_ADC_QC_MUXSEL_SHFT                                            0x0

#define HWIO_BIST_QC_CONF1_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000008c)
#define HWIO_BIST_QC_CONF1_RMSK                                                            0xffff
#define HWIO_BIST_QC_CONF1_IN          \
        in_dword(HWIO_BIST_QC_CONF1_ADDR)
#define HWIO_BIST_QC_CONF1_INM(m)      \
        in_dword_masked(HWIO_BIST_QC_CONF1_ADDR, m)
#define HWIO_BIST_QC_CONF1_OUT(v)      \
        out_dword(HWIO_BIST_QC_CONF1_ADDR,v)
#define HWIO_BIST_QC_CONF1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_QC_CONF1_ADDR,m,v,HWIO_BIST_QC_CONF1_IN)
#define HWIO_BIST_QC_CONF1_BIST_QC_BIST_MUX_CTRL_BMSK                                      0xffff
#define HWIO_BIST_QC_CONF1_BIST_QC_BIST_MUX_CTRL_SHFT                                         0x0

#define HWIO_BIST_ADC_QC_DAC_LEVEL_ADDR                                                (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000090)
#define HWIO_BIST_ADC_QC_DAC_LEVEL_RMSK                                                     0x3ff
#define HWIO_BIST_ADC_QC_DAC_LEVEL_IN          \
        in_dword(HWIO_BIST_ADC_QC_DAC_LEVEL_ADDR)
#define HWIO_BIST_ADC_QC_DAC_LEVEL_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_QC_DAC_LEVEL_ADDR, m)
#define HWIO_BIST_ADC_QC_DAC_LEVEL_OUT(v)      \
        out_dword(HWIO_BIST_ADC_QC_DAC_LEVEL_ADDR,v)
#define HWIO_BIST_ADC_QC_DAC_LEVEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_ADC_QC_DAC_LEVEL_ADDR,m,v,HWIO_BIST_ADC_QC_DAC_LEVEL_IN)
#define HWIO_BIST_ADC_QC_DAC_LEVEL_BIST_ADC_QC_DAC_LEVEL_BMSK                               0x3ff
#define HWIO_BIST_ADC_QC_DAC_LEVEL_BIST_ADC_QC_DAC_LEVEL_SHFT                                 0x0

#define HWIO_BIST_ADC_QC_DATA_ADDR                                                     (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000094)
#define HWIO_BIST_ADC_QC_DATA_RMSK                                                          0x3ff
#define HWIO_BIST_ADC_QC_DATA_IN          \
        in_dword(HWIO_BIST_ADC_QC_DATA_ADDR)
#define HWIO_BIST_ADC_QC_DATA_INM(m)      \
        in_dword_masked(HWIO_BIST_ADC_QC_DATA_ADDR, m)
#define HWIO_BIST_ADC_QC_DATA_BIST_ADC_QC_DATA_BMSK                                         0x3ff
#define HWIO_BIST_ADC_QC_DATA_BIST_ADC_QC_DATA_SHFT                                           0x0

#define HWIO_PLA_SW_OVR_EN_ADDR                                                        (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x00000098)
#define HWIO_PLA_SW_OVR_EN_RMSK                                                               0x7
#define HWIO_PLA_SW_OVR_EN_IN          \
        in_dword(HWIO_PLA_SW_OVR_EN_ADDR)
#define HWIO_PLA_SW_OVR_EN_INM(m)      \
        in_dword_masked(HWIO_PLA_SW_OVR_EN_ADDR, m)
#define HWIO_PLA_SW_OVR_EN_OUT(v)      \
        out_dword(HWIO_PLA_SW_OVR_EN_ADDR,v)
#define HWIO_PLA_SW_OVR_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PLA_SW_OVR_EN_ADDR,m,v,HWIO_PLA_SW_OVR_EN_IN)
#define HWIO_PLA_SW_OVR_EN_LDO_PA_OVR_EN_BMSK                                                 0x4
#define HWIO_PLA_SW_OVR_EN_LDO_PA_OVR_EN_SHFT                                                 0x2
#define HWIO_PLA_SW_OVR_EN_LDO_RF_OVR_EN_BMSK                                                 0x2
#define HWIO_PLA_SW_OVR_EN_LDO_RF_OVR_EN_SHFT                                                 0x1
#define HWIO_PLA_SW_OVR_EN_LDO_VMA_OVR_EN_BMSK                                                0x1
#define HWIO_PLA_SW_OVR_EN_LDO_VMA_OVR_EN_SHFT                                                0x0

#define HWIO_PLA_SW_OVR_VAL_ADDR                                                       (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x0000009c)
#define HWIO_PLA_SW_OVR_VAL_RMSK                                                            0x1ff
#define HWIO_PLA_SW_OVR_VAL_IN          \
        in_dword(HWIO_PLA_SW_OVR_VAL_ADDR)
#define HWIO_PLA_SW_OVR_VAL_INM(m)      \
        in_dword_masked(HWIO_PLA_SW_OVR_VAL_ADDR, m)
#define HWIO_PLA_SW_OVR_VAL_OUT(v)      \
        out_dword(HWIO_PLA_SW_OVR_VAL_ADDR,v)
#define HWIO_PLA_SW_OVR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PLA_SW_OVR_VAL_ADDR,m,v,HWIO_PLA_SW_OVR_VAL_IN)
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_SELB_ILIM_OVR_VAL_BMSK                                   0x180
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_SELB_ILIM_OVR_VAL_SHFT                                     0x7
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_SELB_SOFTSTART_OVR_VAL_BMSK                               0x40
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_SELB_SOFTSTART_OVR_VAL_SHFT                                0x6
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_EN_OVR_VAL_BMSK                                           0x20
#define HWIO_PLA_SW_OVR_VAL_LDO_PA_EN_OVR_VAL_SHFT                                            0x5
#define HWIO_PLA_SW_OVR_VAL_LDO_RF_SELB_ILIM_OVR_VAL_BMSK                                    0x18
#define HWIO_PLA_SW_OVR_VAL_LDO_RF_SELB_ILIM_OVR_VAL_SHFT                                     0x3
#define HWIO_PLA_SW_OVR_VAL_LDO_RF_EN_OVR_VAL_BMSK                                            0x4
#define HWIO_PLA_SW_OVR_VAL_LDO_RF_EN_OVR_VAL_SHFT                                            0x2
#define HWIO_PLA_SW_OVR_VAL_LDO_VMA_SELB_SOFTSTART_OVR_VAL_BMSK                               0x2
#define HWIO_PLA_SW_OVR_VAL_LDO_VMA_SELB_SOFTSTART_OVR_VAL_SHFT                               0x1
#define HWIO_PLA_SW_OVR_VAL_LDO_VMA_EN_OVR_VAL_BMSK                                           0x1
#define HWIO_PLA_SW_OVR_VAL_LDO_VMA_EN_OVR_VAL_SHFT                                           0x0

#define HWIO_PLA_LDO_STARTUP_DLY_CONF_ADDR                                             (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x000000a0)
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_RMSK                                                 0xffff
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_IN          \
        in_dword(HWIO_PLA_LDO_STARTUP_DLY_CONF_ADDR)
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_INM(m)      \
        in_dword_masked(HWIO_PLA_LDO_STARTUP_DLY_CONF_ADDR, m)
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_OUT(v)      \
        out_dword(HWIO_PLA_LDO_STARTUP_DLY_CONF_ADDR,v)
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PLA_LDO_STARTUP_DLY_CONF_ADDR,m,v,HWIO_PLA_LDO_STARTUP_DLY_CONF_IN)
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_STAGGERED_ON_DLY_CNT_BMSK                        0xf000
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_STAGGERED_ON_DLY_CNT_SHFT                           0xc
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_PA_STARTUP_DLY_CNT_BMSK                           0xfc0
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_PA_STARTUP_DLY_CNT_SHFT                             0x6
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_RF_STARTUP_DLY_CNT_BMSK                            0x3f
#define HWIO_PLA_LDO_STARTUP_DLY_CONF_LDO_RF_STARTUP_DLY_CNT_SHFT                             0x0

#define HWIO_PMU_FAST_CLK_GATING_CTRL_ADDR                                             (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x000000a4)
#define HWIO_PMU_FAST_CLK_GATING_CTRL_RMSK                                                    0x1
#define HWIO_PMU_FAST_CLK_GATING_CTRL_IN          \
        in_dword(HWIO_PMU_FAST_CLK_GATING_CTRL_ADDR)
#define HWIO_PMU_FAST_CLK_GATING_CTRL_INM(m)      \
        in_dword_masked(HWIO_PMU_FAST_CLK_GATING_CTRL_ADDR, m)
#define HWIO_PMU_FAST_CLK_GATING_CTRL_OUT(v)      \
        out_dword(HWIO_PMU_FAST_CLK_GATING_CTRL_ADDR,v)
#define HWIO_PMU_FAST_CLK_GATING_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_FAST_CLK_GATING_CTRL_ADDR,m,v,HWIO_PMU_FAST_CLK_GATING_CTRL_IN)
#define HWIO_PMU_FAST_CLK_GATING_CTRL_VDIG_FAST_CLK_FORCE_ON_BMSK                             0x1
#define HWIO_PMU_FAST_CLK_GATING_CTRL_VDIG_FAST_CLK_FORCE_ON_SHFT                             0x0

#define HWIO_PMU_DEBUG_CONF_ADDR                                                       (PMU_CTRL_STATUS_VDIG_REG_REG_BASE      + 0x000000a8)
#define HWIO_PMU_DEBUG_CONF_RMSK                                                             0x7f
#define HWIO_PMU_DEBUG_CONF_IN          \
        in_dword(HWIO_PMU_DEBUG_CONF_ADDR)
#define HWIO_PMU_DEBUG_CONF_INM(m)      \
        in_dword_masked(HWIO_PMU_DEBUG_CONF_ADDR, m)
#define HWIO_PMU_DEBUG_CONF_OUT(v)      \
        out_dword(HWIO_PMU_DEBUG_CONF_ADDR,v)
#define HWIO_PMU_DEBUG_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_PMU_DEBUG_CONF_ADDR,m,v,HWIO_PMU_DEBUG_CONF_IN)
#define HWIO_PMU_DEBUG_CONF_DEBUG_MUX_SEL_BMSK                                               0x78
#define HWIO_PMU_DEBUG_CONF_DEBUG_MUX_SEL_SHFT                                                0x3
#define HWIO_PMU_DEBUG_CONF_SMPS_ANA_CLK_EXT_SEL_EN_BMSK                                      0x4
#define HWIO_PMU_DEBUG_CONF_SMPS_ANA_CLK_EXT_SEL_EN_SHFT                                      0x2
#define HWIO_PMU_DEBUG_CONF_TS_HW_REQ_EN_BMSK                                                 0x2
#define HWIO_PMU_DEBUG_CONF_TS_HW_REQ_EN_SHFT                                                 0x1
#define HWIO_PMU_DEBUG_CONF_BIST_ADC_HW_REQ_EN_BMSK                                           0x1
#define HWIO_PMU_DEBUG_CONF_BIST_ADC_HW_REQ_EN_SHFT                                           0x0

/*----------------------------------------------------------------------------
 * MODULE: PMU_STATIC_ADDA_VDIG_REG
 *--------------------------------------------------------------------------*/

#define PMU_STATIC_ADDA_VDIG_REG_REG_BASE                                  (PMU_MTOP_02_BASE      + 0x000000c0)
#define PMU_STATIC_ADDA_VDIG_REG_REG_BASE_SIZE                             0x40
#define PMU_STATIC_ADDA_VDIG_REG_REG_BASE_USED                             0x30

#define HWIO_LDO_RF_SEL_VOUT_ADDR                                          (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000000)
#define HWIO_LDO_RF_SEL_VOUT_RMSK                                                 0x7
#define HWIO_LDO_RF_SEL_VOUT_IN          \
        in_dword(HWIO_LDO_RF_SEL_VOUT_ADDR)
#define HWIO_LDO_RF_SEL_VOUT_INM(m)      \
        in_dword_masked(HWIO_LDO_RF_SEL_VOUT_ADDR, m)
#define HWIO_LDO_RF_SEL_VOUT_OUT(v)      \
        out_dword(HWIO_LDO_RF_SEL_VOUT_ADDR,v)
#define HWIO_LDO_RF_SEL_VOUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LDO_RF_SEL_VOUT_ADDR,m,v,HWIO_LDO_RF_SEL_VOUT_IN)
#define HWIO_LDO_RF_SEL_VOUT_LDO_RF_SEL_VOUT_BMSK                                 0x7
#define HWIO_LDO_RF_SEL_VOUT_LDO_RF_SEL_VOUT_SHFT                                 0x0

#define HWIO_LDO_RF_CONF_ADDR                                              (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000004)
#define HWIO_LDO_RF_CONF_RMSK                                                     0x7
#define HWIO_LDO_RF_CONF_IN          \
        in_dword(HWIO_LDO_RF_CONF_ADDR)
#define HWIO_LDO_RF_CONF_INM(m)      \
        in_dword_masked(HWIO_LDO_RF_CONF_ADDR, m)
#define HWIO_LDO_RF_CONF_OUT(v)      \
        out_dword(HWIO_LDO_RF_CONF_ADDR,v)
#define HWIO_LDO_RF_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LDO_RF_CONF_ADDR,m,v,HWIO_LDO_RF_CONF_IN)
#define HWIO_LDO_RF_CONF_LDO_RF_SEL_PT_BMSK                                       0x4
#define HWIO_LDO_RF_CONF_LDO_RF_SEL_PT_SHFT                                       0x2
#define HWIO_LDO_RF_CONF_LDO_RF_DISCHARGE_BMSK                                    0x2
#define HWIO_LDO_RF_CONF_LDO_RF_DISCHARGE_SHFT                                    0x1
#define HWIO_LDO_RF_CONF_LDO_RF_SEL_TEST_BMSK                                     0x1
#define HWIO_LDO_RF_CONF_LDO_RF_SEL_TEST_SHFT                                     0x0

#define HWIO_LDO_PA_SEL_VOUT_ADDR                                          (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000008)
#define HWIO_LDO_PA_SEL_VOUT_RMSK                                                 0x7
#define HWIO_LDO_PA_SEL_VOUT_IN          \
        in_dword(HWIO_LDO_PA_SEL_VOUT_ADDR)
#define HWIO_LDO_PA_SEL_VOUT_INM(m)      \
        in_dword_masked(HWIO_LDO_PA_SEL_VOUT_ADDR, m)
#define HWIO_LDO_PA_SEL_VOUT_OUT(v)      \
        out_dword(HWIO_LDO_PA_SEL_VOUT_ADDR,v)
#define HWIO_LDO_PA_SEL_VOUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LDO_PA_SEL_VOUT_ADDR,m,v,HWIO_LDO_PA_SEL_VOUT_IN)
#define HWIO_LDO_PA_SEL_VOUT_LDO_PA_SEL_VOUT_BMSK                                 0x7
#define HWIO_LDO_PA_SEL_VOUT_LDO_PA_SEL_VOUT_SHFT                                 0x0

#define HWIO_LDO_PA_CONF_ADDR                                              (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x0000000c)
#define HWIO_LDO_PA_CONF_RMSK                                                     0x7
#define HWIO_LDO_PA_CONF_IN          \
        in_dword(HWIO_LDO_PA_CONF_ADDR)
#define HWIO_LDO_PA_CONF_INM(m)      \
        in_dword_masked(HWIO_LDO_PA_CONF_ADDR, m)
#define HWIO_LDO_PA_CONF_OUT(v)      \
        out_dword(HWIO_LDO_PA_CONF_ADDR,v)
#define HWIO_LDO_PA_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LDO_PA_CONF_ADDR,m,v,HWIO_LDO_PA_CONF_IN)
#define HWIO_LDO_PA_CONF_LDO_PA_DISCHARGE_BMSK                                    0x4
#define HWIO_LDO_PA_CONF_LDO_PA_DISCHARGE_SHFT                                    0x2
#define HWIO_LDO_PA_CONF_LDO_PA_SEL_TEST_BMSK                                     0x2
#define HWIO_LDO_PA_CONF_LDO_PA_SEL_TEST_SHFT                                     0x1
#define HWIO_LDO_PA_CONF_LDO_PA_SEL_PT_BMSK                                       0x1
#define HWIO_LDO_PA_CONF_LDO_PA_SEL_PT_SHFT                                       0x0

#define HWIO_LDO_VMA_CONF_ADDR                                             (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000010)
#define HWIO_LDO_VMA_CONF_RMSK                                                    0x3
#define HWIO_LDO_VMA_CONF_IN          \
        in_dword(HWIO_LDO_VMA_CONF_ADDR)
#define HWIO_LDO_VMA_CONF_INM(m)      \
        in_dword_masked(HWIO_LDO_VMA_CONF_ADDR, m)
#define HWIO_LDO_VMA_CONF_OUT(v)      \
        out_dword(HWIO_LDO_VMA_CONF_ADDR,v)
#define HWIO_LDO_VMA_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LDO_VMA_CONF_ADDR,m,v,HWIO_LDO_VMA_CONF_IN)
#define HWIO_LDO_VMA_CONF_LDO_VMA_DISCHARGE_BMSK                                  0x2
#define HWIO_LDO_VMA_CONF_LDO_VMA_DISCHARGE_SHFT                                  0x1
#define HWIO_LDO_VMA_CONF_LDO_VMA_SEL_TEST_BMSK                                   0x1
#define HWIO_LDO_VMA_CONF_LDO_VMA_SEL_TEST_SHFT                                   0x0

#define HWIO_BIST_MUX_QC_CTRL_ADDR                                         (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000014)
#define HWIO_BIST_MUX_QC_CTRL_RMSK                                               0x3f
#define HWIO_BIST_MUX_QC_CTRL_IN          \
        in_dword(HWIO_BIST_MUX_QC_CTRL_ADDR)
#define HWIO_BIST_MUX_QC_CTRL_INM(m)      \
        in_dword_masked(HWIO_BIST_MUX_QC_CTRL_ADDR, m)
#define HWIO_BIST_MUX_QC_CTRL_OUT(v)      \
        out_dword(HWIO_BIST_MUX_QC_CTRL_ADDR,v)
#define HWIO_BIST_MUX_QC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_MUX_QC_CTRL_ADDR,m,v,HWIO_BIST_MUX_QC_CTRL_IN)
#define HWIO_BIST_MUX_QC_CTRL_BIST_RF_MUX_PULLDOWN_BMSK                          0x20
#define HWIO_BIST_MUX_QC_CTRL_BIST_RF_MUX_PULLDOWN_SHFT                           0x5
#define HWIO_BIST_MUX_QC_CTRL_BIST_GBL_MUX_PULLDOWN_BMSK                         0x10
#define HWIO_BIST_MUX_QC_CTRL_BIST_GBL_MUX_PULLDOWN_SHFT                          0x4
#define HWIO_BIST_MUX_QC_CTRL_BIST_GBL_AMUX_EN_BMSK                               0xe
#define HWIO_BIST_MUX_QC_CTRL_BIST_GBL_AMUX_EN_SHFT                               0x1
#define HWIO_BIST_MUX_QC_CTRL_BIST_MUX_PULLDOWN_BMSK                              0x1
#define HWIO_BIST_MUX_QC_CTRL_BIST_MUX_PULLDOWN_SHFT                              0x0

#define HWIO_BIST_MUX_BUS_SEL_ADDR                                         (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000018)
#define HWIO_BIST_MUX_BUS_SEL_RMSK                                             0x7fff
#define HWIO_BIST_MUX_BUS_SEL_IN          \
        in_dword(HWIO_BIST_MUX_BUS_SEL_ADDR)
#define HWIO_BIST_MUX_BUS_SEL_INM(m)      \
        in_dword_masked(HWIO_BIST_MUX_BUS_SEL_ADDR, m)
#define HWIO_BIST_MUX_BUS_SEL_OUT(v)      \
        out_dword(HWIO_BIST_MUX_BUS_SEL_ADDR,v)
#define HWIO_BIST_MUX_BUS_SEL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_BIST_MUX_BUS_SEL_ADDR,m,v,HWIO_BIST_MUX_BUS_SEL_IN)
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_BMSK                       0x7c00
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS7_SEL_SHFT                          0xa
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS6_SEL_BMSK                        0x3e0
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS6_SEL_SHFT                          0x5
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS4_SEL_BMSK                         0x1f
#define HWIO_BIST_MUX_BUS_SEL_BIST_PMU_MUX_BUS4_SEL_SHFT                          0x0

#define HWIO_TS_TRIM0_ADDR                                                 (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x0000001c)
#define HWIO_TS_TRIM0_RMSK                                                     0x3fff
#define HWIO_TS_TRIM0_IN          \
        in_dword(HWIO_TS_TRIM0_ADDR)
#define HWIO_TS_TRIM0_INM(m)      \
        in_dword_masked(HWIO_TS_TRIM0_ADDR, m)
#define HWIO_TS_TRIM0_OUT(v)      \
        out_dword(HWIO_TS_TRIM0_ADDR,v)
#define HWIO_TS_TRIM0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TS_TRIM0_ADDR,m,v,HWIO_TS_TRIM0_IN)
#define HWIO_TS_TRIM0_TS_DVBE_GAIN_TRIM_BMSK                                   0x3c00
#define HWIO_TS_TRIM0_TS_DVBE_GAIN_TRIM_SHFT                                      0xa
#define HWIO_TS_TRIM0_TS_ADC_OFFSET_TRIM_BMSK                                   0x3e0
#define HWIO_TS_TRIM0_TS_ADC_OFFSET_TRIM_SHFT                                     0x5
#define HWIO_TS_TRIM0_TS_ADC_GAIN_TRIM_BMSK                                      0x1f
#define HWIO_TS_TRIM0_TS_ADC_GAIN_TRIM_SHFT                                       0x0

#define HWIO_TS_TRIM1_ADDR                                                 (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000020)
#define HWIO_TS_TRIM1_RMSK                                                        0xf
#define HWIO_TS_TRIM1_IN          \
        in_dword(HWIO_TS_TRIM1_ADDR)
#define HWIO_TS_TRIM1_INM(m)      \
        in_dword_masked(HWIO_TS_TRIM1_ADDR, m)
#define HWIO_TS_TRIM1_OUT(v)      \
        out_dword(HWIO_TS_TRIM1_ADDR,v)
#define HWIO_TS_TRIM1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TS_TRIM1_ADDR,m,v,HWIO_TS_TRIM1_IN)
#define HWIO_TS_TRIM1_TS_DVBE_OFFSET_TRIM_BMSK                                    0xf
#define HWIO_TS_TRIM1_TS_DVBE_OFFSET_TRIM_SHFT                                    0x0

#define HWIO_TS_TEST_ADDR                                                  (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000024)
#define HWIO_TS_TEST_RMSK                                                        0x1f
#define HWIO_TS_TEST_IN          \
        in_dword(HWIO_TS_TEST_ADDR)
#define HWIO_TS_TEST_INM(m)      \
        in_dword_masked(HWIO_TS_TEST_ADDR, m)
#define HWIO_TS_TEST_OUT(v)      \
        out_dword(HWIO_TS_TEST_ADDR,v)
#define HWIO_TS_TEST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_TS_TEST_ADDR,m,v,HWIO_TS_TEST_IN)
#define HWIO_TS_TEST_TS_TST_MODE_BMSK                                            0x1e
#define HWIO_TS_TEST_TS_TST_MODE_SHFT                                             0x1
#define HWIO_TS_TEST_TS_SEL_ADC_TEST_BMSK                                         0x1
#define HWIO_TS_TEST_TS_SEL_ADC_TEST_SHFT                                         0x0

#define HWIO_BD_STATUS_ADDR                                                (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000028)
#define HWIO_BD_STATUS_RMSK                                                       0x1
#define HWIO_BD_STATUS_IN          \
        in_dword(HWIO_BD_STATUS_ADDR)
#define HWIO_BD_STATUS_INM(m)      \
        in_dword_masked(HWIO_BD_STATUS_ADDR, m)
#define HWIO_BD_STATUS_BD_COMP_OUT_BMSK                                           0x1
#define HWIO_BD_STATUS_BD_COMP_OUT_SHFT                                           0x0

#define HWIO_DU_STATUS_ADDR                                                (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x0000002c)
#define HWIO_DU_STATUS_RMSK                                                       0x1
#define HWIO_DU_STATUS_IN          \
        in_dword(HWIO_DU_STATUS_ADDR)
#define HWIO_DU_STATUS_INM(m)      \
        in_dword_masked(HWIO_DU_STATUS_ADDR, m)
#define HWIO_DU_STATUS_DU_COMP_OUT_BMSK                                           0x1
#define HWIO_DU_STATUS_DU_COMP_OUT_SHFT                                           0x0

#define HWIO_LCD_PADS_SWITCH_EN_CTRL_ADDR                                  (PMU_STATIC_ADDA_VDIG_REG_REG_BASE      + 0x00000030)
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_RMSK                                         0x3
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_IN          \
        in_dword(HWIO_LCD_PADS_SWITCH_EN_CTRL_ADDR)
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_INM(m)      \
        in_dword_masked(HWIO_LCD_PADS_SWITCH_EN_CTRL_ADDR, m)
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_OUT(v)      \
        out_dword(HWIO_LCD_PADS_SWITCH_EN_CTRL_ADDR,v)
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_LCD_PADS_SWITCH_EN_CTRL_ADDR,m,v,HWIO_LCD_PADS_SWITCH_EN_CTRL_IN)
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_LCD_PADS_RRAM_SWITCH_EN_BMSK                 0x3
#define HWIO_LCD_PADS_SWITCH_EN_CTRL_LCD_PADS_RRAM_SWITCH_EN_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APSS_PMU_VLP_AON_REG
 *--------------------------------------------------------------------------*/

#define APSS_PMU_VLP_AON_REG_REG_BASE (PMU_MTOP_02_BASE      + 0x00000800)
#define APSS_PMU_VLP_AON_REG_REG_BASE_SIZE 0x100
#define APSS_PMU_VLP_AON_REG_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: APSS_PMU_CTRL_STATUS_VLP_AON_REG
 *--------------------------------------------------------------------------*/

#define APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE                                    (PMU_MTOP_02_BASE      + 0x00000800)
#define APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE_SIZE                               0x80
#define APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE_USED                               0x44

#define HWIO_APSS_ULPBG_TRIM_ADDR                                                    (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000000)
#define HWIO_APSS_ULPBG_TRIM_RMSK                                                          0x1f
#define HWIO_APSS_ULPBG_TRIM_IN          \
        in_dword(HWIO_APSS_ULPBG_TRIM_ADDR)
#define HWIO_APSS_ULPBG_TRIM_INM(m)      \
        in_dword_masked(HWIO_APSS_ULPBG_TRIM_ADDR, m)
#define HWIO_APSS_ULPBG_TRIM_OUT(v)      \
        out_dword(HWIO_APSS_ULPBG_TRIM_ADDR,v)
#define HWIO_APSS_ULPBG_TRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_ULPBG_TRIM_ADDR,m,v,HWIO_APSS_ULPBG_TRIM_IN)
#define HWIO_APSS_ULPBG_TRIM_ULPBG_TRIM_BMSK                                               0x1f
#define HWIO_APSS_ULPBG_TRIM_ULPBG_TRIM_SHFT                                                0x0

#define HWIO_APSS_PLA_CONFIG_0_ADDR                                                  (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000004)
#define HWIO_APSS_PLA_CONFIG_0_RMSK                                                        0x7f
#define HWIO_APSS_PLA_CONFIG_0_IN          \
        in_dword(HWIO_APSS_PLA_CONFIG_0_ADDR)
#define HWIO_APSS_PLA_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_APSS_PLA_CONFIG_0_ADDR, m)
#define HWIO_APSS_PLA_CONFIG_0_OUT(v)      \
        out_dword(HWIO_APSS_PLA_CONFIG_0_ADDR,v)
#define HWIO_APSS_PLA_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PLA_CONFIG_0_ADDR,m,v,HWIO_APSS_PLA_CONFIG_0_IN)
#define HWIO_APSS_PLA_CONFIG_0_VLP_PLA_SEL_VOUT_SEL_BMSK                                   0x60
#define HWIO_APSS_PLA_CONFIG_0_VLP_PLA_SEL_VOUT_SEL_SHFT                                    0x5
#define HWIO_APSS_PLA_CONFIG_0_VDIG_PLA_SEL_VOUT_BMSK                                      0x1f
#define HWIO_APSS_PLA_CONFIG_0_VDIG_PLA_SEL_VOUT_SHFT                                       0x0

#define HWIO_APSS_PLA_CONFIG_1_ADDR                                                  (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000008)
#define HWIO_APSS_PLA_CONFIG_1_RMSK                                                         0x7
#define HWIO_APSS_PLA_CONFIG_1_IN          \
        in_dword(HWIO_APSS_PLA_CONFIG_1_ADDR)
#define HWIO_APSS_PLA_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_APSS_PLA_CONFIG_1_ADDR, m)
#define HWIO_APSS_PLA_CONFIG_1_OUT(v)      \
        out_dword(HWIO_APSS_PLA_CONFIG_1_ADDR,v)
#define HWIO_APSS_PLA_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PLA_CONFIG_1_ADDR,m,v,HWIO_APSS_PLA_CONFIG_1_IN)
#define HWIO_APSS_PLA_CONFIG_1_SMPS_ANA_CLK_PLA_DIV_RATIO_SEL_BMSK                          0x6
#define HWIO_APSS_PLA_CONFIG_1_SMPS_ANA_CLK_PLA_DIV_RATIO_SEL_SHFT                          0x1
#define HWIO_APSS_PLA_CONFIG_1_SMPS_ANA_CLK_PLA_32M_SEL_BMSK                                0x1
#define HWIO_APSS_PLA_CONFIG_1_SMPS_ANA_CLK_PLA_32M_SEL_SHFT                                0x0

#define HWIO_APSS_PL1_PL0_CONFIG_0_ADDR                                              (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x0000000c)
#define HWIO_APSS_PL1_PL0_CONFIG_0_RMSK                                                    0xff
#define HWIO_APSS_PL1_PL0_CONFIG_0_IN          \
        in_dword(HWIO_APSS_PL1_PL0_CONFIG_0_ADDR)
#define HWIO_APSS_PL1_PL0_CONFIG_0_INM(m)      \
        in_dword_masked(HWIO_APSS_PL1_PL0_CONFIG_0_ADDR, m)
#define HWIO_APSS_PL1_PL0_CONFIG_0_OUT(v)      \
        out_dword(HWIO_APSS_PL1_PL0_CONFIG_0_ADDR,v)
#define HWIO_APSS_PL1_PL0_CONFIG_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PL1_PL0_CONFIG_0_ADDR,m,v,HWIO_APSS_PL1_PL0_CONFIG_0_IN)
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_RAMP_DN_ON_BMSK                                     0x80
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_RAMP_DN_ON_SHFT                                      0x7
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_RAMP_UP_ON_BMSK                                     0x40
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_RAMP_UP_ON_SHFT                                      0x6
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_BMSK                               0x3f
#define HWIO_APSS_PL1_PL0_CONFIG_0_VLP_PL1_PL0_SEL_VOUT_SHFT                                0x0

#define HWIO_APSS_PL1_PL0_CONFIG_1_ADDR                                              (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000010)
#define HWIO_APSS_PL1_PL0_CONFIG_1_RMSK                                                    0xff
#define HWIO_APSS_PL1_PL0_CONFIG_1_IN          \
        in_dword(HWIO_APSS_PL1_PL0_CONFIG_1_ADDR)
#define HWIO_APSS_PL1_PL0_CONFIG_1_INM(m)      \
        in_dword_masked(HWIO_APSS_PL1_PL0_CONFIG_1_ADDR, m)
#define HWIO_APSS_PL1_PL0_CONFIG_1_OUT(v)      \
        out_dword(HWIO_APSS_PL1_PL0_CONFIG_1_ADDR,v)
#define HWIO_APSS_PL1_PL0_CONFIG_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PL1_PL0_CONFIG_1_ADDR,m,v,HWIO_APSS_PL1_PL0_CONFIG_1_IN)
#define HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_RATIO_BMSK                     0xc0
#define HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_RATIO_SHFT                      0x6
#define HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_DIV_EN_BMSK                    0x20
#define HWIO_APSS_PL1_PL0_CONFIG_1_PL1_PL0_SMPS_ULP_ANA_CLK_DIV_EN_SHFT                     0x5
#define HWIO_APSS_PL1_PL0_CONFIG_1_VDIG_STARTUP_SEL_VOUT_BMSK                              0x1f
#define HWIO_APSS_PL1_PL0_CONFIG_1_VDIG_STARTUP_SEL_VOUT_SHFT                               0x0

#define HWIO_APSS_SW_OVR_EN_ADDR                                                     (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000014)
#define HWIO_APSS_SW_OVR_EN_RMSK                                                           0x7f
#define HWIO_APSS_SW_OVR_EN_IN          \
        in_dword(HWIO_APSS_SW_OVR_EN_ADDR)
#define HWIO_APSS_SW_OVR_EN_INM(m)      \
        in_dword_masked(HWIO_APSS_SW_OVR_EN_ADDR, m)
#define HWIO_APSS_SW_OVR_EN_OUT(v)      \
        out_dword(HWIO_APSS_SW_OVR_EN_ADDR,v)
#define HWIO_APSS_SW_OVR_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SW_OVR_EN_ADDR,m,v,HWIO_APSS_SW_OVR_EN_IN)
#define HWIO_APSS_SW_OVR_EN_IREFGEN_OVR_EN_BMSK                                            0x40
#define HWIO_APSS_SW_OVR_EN_IREFGEN_OVR_EN_SHFT                                             0x6
#define HWIO_APSS_SW_OVR_EN_FOSC_EN_OVR_EN_BMSK                                            0x20
#define HWIO_APSS_SW_OVR_EN_FOSC_EN_OVR_EN_SHFT                                             0x5
#define HWIO_APSS_SW_OVR_EN_LDO_DIG_OVR_EN_BMSK                                            0x10
#define HWIO_APSS_SW_OVR_EN_LDO_DIG_OVR_EN_SHFT                                             0x4
#define HWIO_APSS_SW_OVR_EN_LDO_AUX_OVR_EN_BMSK                                             0x8
#define HWIO_APSS_SW_OVR_EN_LDO_AUX_OVR_EN_SHFT                                             0x3
#define HWIO_APSS_SW_OVR_EN_LDO_VLP_OVR_EN_BMSK                                             0x4
#define HWIO_APSS_SW_OVR_EN_LDO_VLP_OVR_EN_SHFT                                             0x2
#define HWIO_APSS_SW_OVR_EN_LDO_VLA_OVR_EN_BMSK                                             0x2
#define HWIO_APSS_SW_OVR_EN_LDO_VLA_OVR_EN_SHFT                                             0x1
#define HWIO_APSS_SW_OVR_EN_VDIG_SWITCH_OVR_EN_BMSK                                         0x1
#define HWIO_APSS_SW_OVR_EN_VDIG_SWITCH_OVR_EN_SHFT                                         0x0

#define HWIO_APSS_SW_OVR_VAL_ADDR                                                    (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000018)
#define HWIO_APSS_SW_OVR_VAL_RMSK                                                         0x3ff
#define HWIO_APSS_SW_OVR_VAL_IN          \
        in_dword(HWIO_APSS_SW_OVR_VAL_ADDR)
#define HWIO_APSS_SW_OVR_VAL_INM(m)      \
        in_dword_masked(HWIO_APSS_SW_OVR_VAL_ADDR, m)
#define HWIO_APSS_SW_OVR_VAL_OUT(v)      \
        out_dword(HWIO_APSS_SW_OVR_VAL_ADDR,v)
#define HWIO_APSS_SW_OVR_VAL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SW_OVR_VAL_ADDR,m,v,HWIO_APSS_SW_OVR_VAL_IN)
#define HWIO_APSS_SW_OVR_VAL_FOSC_EN_OVR_VAL_BMSK                                         0x200
#define HWIO_APSS_SW_OVR_VAL_FOSC_EN_OVR_VAL_SHFT                                           0x9
#define HWIO_APSS_SW_OVR_VAL_IREFGEN_EN_OVR_VAL_BMSK                                      0x100
#define HWIO_APSS_SW_OVR_VAL_IREFGEN_EN_OVR_VAL_SHFT                                        0x8
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_DISCHARGE_OVR_VAL_BMSK                                0x80
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_DISCHARGE_OVR_VAL_SHFT                                 0x7
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_SELB_SOFTSTART_OVR_VAL_BMSK                           0x40
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_SELB_SOFTSTART_OVR_VAL_SHFT                            0x6
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_DISABLE_OVR_VAL_BMSK                                  0x20
#define HWIO_APSS_SW_OVR_VAL_LDO_DIG_DISABLE_OVR_VAL_SHFT                                   0x5
#define HWIO_APSS_SW_OVR_VAL_LDO_AUX_EN_OVR_VAL_BMSK                                       0x10
#define HWIO_APSS_SW_OVR_VAL_LDO_AUX_EN_OVR_VAL_SHFT                                        0x4
#define HWIO_APSS_SW_OVR_VAL_LDO_VLP_EN_OVR_VAL_BMSK                                        0x8
#define HWIO_APSS_SW_OVR_VAL_LDO_VLP_EN_OVR_VAL_SHFT                                        0x3
#define HWIO_APSS_SW_OVR_VAL_LDO_VLA_SELB_SOFTSTART_OVR_VAL_BMSK                            0x4
#define HWIO_APSS_SW_OVR_VAL_LDO_VLA_SELB_SOFTSTART_OVR_VAL_SHFT                            0x2
#define HWIO_APSS_SW_OVR_VAL_VDIG_SWITCH_EN_STRONG_OVR_VAL_BMSK                             0x2
#define HWIO_APSS_SW_OVR_VAL_VDIG_SWITCH_EN_STRONG_OVR_VAL_SHFT                             0x1
#define HWIO_APSS_SW_OVR_VAL_VDIG_SWITCH_EN_WEAK_OVR_VAL_BMSK                               0x1
#define HWIO_APSS_SW_OVR_VAL_VDIG_SWITCH_EN_WEAK_OVR_VAL_SHFT                               0x0

#define HWIO_APSS_PL_DLY_CONF0_ADDR                                                  (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x0000001c)
#define HWIO_APSS_PL_DLY_CONF0_RMSK                                                      0x3fff
#define HWIO_APSS_PL_DLY_CONF0_IN          \
        in_dword(HWIO_APSS_PL_DLY_CONF0_ADDR)
#define HWIO_APSS_PL_DLY_CONF0_INM(m)      \
        in_dword_masked(HWIO_APSS_PL_DLY_CONF0_ADDR, m)
#define HWIO_APSS_PL_DLY_CONF0_OUT(v)      \
        out_dword(HWIO_APSS_PL_DLY_CONF0_ADDR,v)
#define HWIO_APSS_PL_DLY_CONF0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PL_DLY_CONF0_ADDR,m,v,HWIO_APSS_PL_DLY_CONF0_IN)
#define HWIO_APSS_PL_DLY_CONF0_LDO_DIG_DISCHARGE_DLY_CNT_BMSK                            0x3f80
#define HWIO_APSS_PL_DLY_CONF0_LDO_DIG_DISCHARGE_DLY_CNT_SHFT                               0x7
#define HWIO_APSS_PL_DLY_CONF0_VDIG_SW_EN_STRONG_DLY_SEL_BMSK                              0x40
#define HWIO_APSS_PL_DLY_CONF0_VDIG_SW_EN_STRONG_DLY_SEL_SHFT                               0x6
#define HWIO_APSS_PL_DLY_CONF0_VDIG_SW_EN_WEAK_DLY_SEL_BMSK                                0x20
#define HWIO_APSS_PL_DLY_CONF0_VDIG_SW_EN_WEAK_DLY_SEL_SHFT                                 0x5
#define HWIO_APSS_PL_DLY_CONF0_LDO_DIG_POST_RAMP_DLY_SEL_BMSK                              0x1c
#define HWIO_APSS_PL_DLY_CONF0_LDO_DIG_POST_RAMP_DLY_SEL_SHFT                               0x2
#define HWIO_APSS_PL_DLY_CONF0_PLC_VDIG_RAMP_STEP_RATE_SEL_BMSK                             0x3
#define HWIO_APSS_PL_DLY_CONF0_PLC_VDIG_RAMP_STEP_RATE_SEL_SHFT                             0x0

#define HWIO_APSS_PL_DLY_CONF1_ADDR                                                  (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000020)
#define HWIO_APSS_PL_DLY_CONF1_RMSK                                                      0x1fff
#define HWIO_APSS_PL_DLY_CONF1_IN          \
        in_dword(HWIO_APSS_PL_DLY_CONF1_ADDR)
#define HWIO_APSS_PL_DLY_CONF1_INM(m)      \
        in_dword_masked(HWIO_APSS_PL_DLY_CONF1_ADDR, m)
#define HWIO_APSS_PL_DLY_CONF1_OUT(v)      \
        out_dword(HWIO_APSS_PL_DLY_CONF1_ADDR,v)
#define HWIO_APSS_PL_DLY_CONF1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PL_DLY_CONF1_ADDR,m,v,HWIO_APSS_PL_DLY_CONF1_IN)
#define HWIO_APSS_PL_DLY_CONF1_LDO_VMA_STARTUP_DLY_CNT_BMSK                              0x1f80
#define HWIO_APSS_PL_DLY_CONF1_LDO_VMA_STARTUP_DLY_CNT_SHFT                                 0x7
#define HWIO_APSS_PL_DLY_CONF1_VLP_RAMP_DLY_SEL_BMSK                                       0x70
#define HWIO_APSS_PL_DLY_CONF1_VLP_RAMP_DLY_SEL_SHFT                                        0x4
#define HWIO_APSS_PL_DLY_CONF1_FOSC_STARTUP_DLY_SEL_BMSK                                    0xc
#define HWIO_APSS_PL_DLY_CONF1_FOSC_STARTUP_DLY_SEL_SHFT                                    0x2
#define HWIO_APSS_PL_DLY_CONF1_LDO_AUX_STARTUP_DLY_SEL_BMSK                                 0x3
#define HWIO_APSS_PL_DLY_CONF1_LDO_AUX_STARTUP_DLY_SEL_SHFT                                 0x0

#define HWIO_APSS_SMPS_SEL_TON_CONF_ADDR                                             (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000024)
#define HWIO_APSS_SMPS_SEL_TON_CONF_RMSK                                                 0x7f7f
#define HWIO_APSS_SMPS_SEL_TON_CONF_IN          \
        in_dword(HWIO_APSS_SMPS_SEL_TON_CONF_ADDR)
#define HWIO_APSS_SMPS_SEL_TON_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_SEL_TON_CONF_ADDR, m)
#define HWIO_APSS_SMPS_SEL_TON_CONF_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_SEL_TON_CONF_ADDR,v)
#define HWIO_APSS_SMPS_SEL_TON_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_SEL_TON_CONF_ADDR,m,v,HWIO_APSS_SMPS_SEL_TON_CONF_IN)
#define HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_PFM_BMSK                                0x7f00
#define HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_PFM_SHFT                                   0x8
#define HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_ULP_BMSK                                  0x7f
#define HWIO_APSS_SMPS_SEL_TON_CONF_SMPS_SEL_TON_ULP_SHFT                                   0x0

#define HWIO_APSS_LDO_VMA_AON_CONF_ADDR                                              (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000028)
#define HWIO_APSS_LDO_VMA_AON_CONF_RMSK                                                     0xf
#define HWIO_APSS_LDO_VMA_AON_CONF_IN          \
        in_dword(HWIO_APSS_LDO_VMA_AON_CONF_ADDR)
#define HWIO_APSS_LDO_VMA_AON_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_VMA_AON_CONF_ADDR, m)
#define HWIO_APSS_LDO_VMA_AON_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_VMA_AON_CONF_ADDR,v)
#define HWIO_APSS_LDO_VMA_AON_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_VMA_AON_CONF_ADDR,m,v,HWIO_APSS_LDO_VMA_AON_CONF_IN)
#define HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_PT_BMSK                                      0x8
#define HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_PT_SHFT                                      0x3
#define HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_VOUT_BMSK                                    0x7
#define HWIO_APSS_LDO_VMA_AON_CONF_LDO_VMA_SEL_VOUT_SHFT                                    0x0

#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_ADDR                                    (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x0000002c)
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_RMSK                                          0x3f
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_IN          \
        in_dword(HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_ADDR)
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_ADDR, m)
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_ADDR,v)
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_ADDR,m,v,HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_IN)
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_VLA_SELB_ILIM_BMSK                        0x30
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_VLA_SELB_ILIM_SHFT                         0x4
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_VMA_SELB_ILIM_BMSK                         0xc
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_VMA_SELB_ILIM_SHFT                         0x2
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_DIG_SELB_ILIM_BMSK                         0x3
#define HWIO_APSS_LDO_ILIM_POST_STARTUP_CONF_LDO_DIG_SELB_ILIM_SHFT                         0x0

#define HWIO_APSS_XTAL_CTRL_ADDR                                                     (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000030)
#define HWIO_APSS_XTAL_CTRL_RMSK                                                            0x1
#define HWIO_APSS_XTAL_CTRL_IN          \
        in_dword(HWIO_APSS_XTAL_CTRL_ADDR)
#define HWIO_APSS_XTAL_CTRL_INM(m)      \
        in_dword_masked(HWIO_APSS_XTAL_CTRL_ADDR, m)
#define HWIO_APSS_XTAL_CTRL_OUT(v)      \
        out_dword(HWIO_APSS_XTAL_CTRL_ADDR,v)
#define HWIO_APSS_XTAL_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_XTAL_CTRL_ADDR,m,v,HWIO_APSS_XTAL_CTRL_IN)
#define HWIO_APSS_XTAL_CTRL_XTAL_EN_BMSK                                                    0x1
#define HWIO_APSS_XTAL_CTRL_XTAL_EN_SHFT                                                    0x0

#define HWIO_APSS_XTAL_32K_OK_ADDR                                                   (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000034)
#define HWIO_APSS_XTAL_32K_OK_RMSK                                                          0x1
#define HWIO_APSS_XTAL_32K_OK_IN          \
        in_dword(HWIO_APSS_XTAL_32K_OK_ADDR)
#define HWIO_APSS_XTAL_32K_OK_INM(m)      \
        in_dword_masked(HWIO_APSS_XTAL_32K_OK_ADDR, m)
#define HWIO_APSS_XTAL_32K_OK_OUT(v)      \
        out_dword(HWIO_APSS_XTAL_32K_OK_ADDR,v)
#define HWIO_APSS_XTAL_32K_OK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_XTAL_32K_OK_ADDR,m,v,HWIO_APSS_XTAL_32K_OK_IN)
#define HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_BMSK                                      0x1
#define HWIO_APSS_XTAL_32K_OK_XTAL_32K_OK_CONFIRM_SHFT                                      0x0

#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_ADDR                                      (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000038)
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_RMSK                                             0x7
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_IN          \
        in_dword(HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_ADDR)
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_ADDR, m)
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_OUT(v)      \
        out_dword(HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_ADDR,v)
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_ADDR,m,v,HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_IN)
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_DS_DEBUG_MUX_SEL_BMSK                            0x7
#define HWIO_APSS_PMU_DEEPSLEEP_DEBUG_CONF_DS_DEBUG_MUX_SEL_SHFT                            0x0

#define HWIO_APSS_PMU_COLD_RST_CONF_ADDR                                             (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x0000003c)
#define HWIO_APSS_PMU_COLD_RST_CONF_RMSK                                                   0x1f
#define HWIO_APSS_PMU_COLD_RST_CONF_IN          \
        in_dword(HWIO_APSS_PMU_COLD_RST_CONF_ADDR)
#define HWIO_APSS_PMU_COLD_RST_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_PMU_COLD_RST_CONF_ADDR, m)
#define HWIO_APSS_PMU_COLD_RST_CONF_OUT(v)      \
        out_dword(HWIO_APSS_PMU_COLD_RST_CONF_ADDR,v)
#define HWIO_APSS_PMU_COLD_RST_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PMU_COLD_RST_CONF_ADDR,m,v,HWIO_APSS_PMU_COLD_RST_CONF_IN)
#define HWIO_APSS_PMU_COLD_RST_CONF_COLD_RST_VLP_RAMP_DLY_SEL_BMSK                         0x1c
#define HWIO_APSS_PMU_COLD_RST_CONF_COLD_RST_VLP_RAMP_DLY_SEL_SHFT                          0x2
#define HWIO_APSS_PMU_COLD_RST_CONF_COLD_RST_LDO_DIG_DISCHARGE_DLY_SEL_BMSK                 0x3
#define HWIO_APSS_PMU_COLD_RST_CONF_COLD_RST_LDO_DIG_DISCHARGE_DLY_SEL_SHFT                 0x0

#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_ADDR                                     (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000040)
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_RMSK                                            0x1
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_IN          \
        in_dword(HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_ADDR)
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_ADDR, m)
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_OUT(v)      \
        out_dword(HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_ADDR,v)
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_ADDR,m,v,HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_IN)
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_APSS_VLP_REG_ACC_DISABLE_BMSK                   0x1
#define HWIO_APSS_PMU_APSS_VLP_REG_ACC_CONF_APSS_VLP_REG_ACC_DISABLE_SHFT                   0x0

#define HWIO_APSS_PMU_SPARE_REG_ADDR                                                 (APSS_PMU_CTRL_STATUS_VLP_AON_REG_REG_BASE      + 0x00000044)
#define HWIO_APSS_PMU_SPARE_REG_RMSK                                                        0x7
#define HWIO_APSS_PMU_SPARE_REG_IN          \
        in_dword(HWIO_APSS_PMU_SPARE_REG_ADDR)
#define HWIO_APSS_PMU_SPARE_REG_INM(m)      \
        in_dword_masked(HWIO_APSS_PMU_SPARE_REG_ADDR, m)
#define HWIO_APSS_PMU_SPARE_REG_OUT(v)      \
        out_dword(HWIO_APSS_PMU_SPARE_REG_ADDR,v)
#define HWIO_APSS_PMU_SPARE_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_PMU_SPARE_REG_ADDR,m,v,HWIO_APSS_PMU_SPARE_REG_IN)
#define HWIO_APSS_PMU_SPARE_REG_SPARE_REG_BMSK                                              0x7
#define HWIO_APSS_PMU_SPARE_REG_SPARE_REG_SHFT                                              0x0

/*----------------------------------------------------------------------------
 * MODULE: APSS_PMU_STATIC_ADDA_VLP_REG
 *--------------------------------------------------------------------------*/

#define APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE                       (PMU_MTOP_02_BASE      + 0x00000880)
#define APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE_SIZE                  0x80
#define APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE_USED                  0x48

#define HWIO_APSS_LDO_AUX_SEL_VOUT_ADDR                             (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000000)
#define HWIO_APSS_LDO_AUX_SEL_VOUT_RMSK                                    0x3
#define HWIO_APSS_LDO_AUX_SEL_VOUT_IN          \
        in_dword(HWIO_APSS_LDO_AUX_SEL_VOUT_ADDR)
#define HWIO_APSS_LDO_AUX_SEL_VOUT_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_AUX_SEL_VOUT_ADDR, m)
#define HWIO_APSS_LDO_AUX_SEL_VOUT_OUT(v)      \
        out_dword(HWIO_APSS_LDO_AUX_SEL_VOUT_ADDR,v)
#define HWIO_APSS_LDO_AUX_SEL_VOUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_AUX_SEL_VOUT_ADDR,m,v,HWIO_APSS_LDO_AUX_SEL_VOUT_IN)
#define HWIO_APSS_LDO_AUX_SEL_VOUT_LDO_AUX_SEL_VOUT_BMSK                   0x3
#define HWIO_APSS_LDO_AUX_SEL_VOUT_LDO_AUX_SEL_VOUT_SHFT                   0x0

#define HWIO_APSS_LDO_AUX_CONF_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000004)
#define HWIO_APSS_LDO_AUX_CONF_RMSK                                        0x3
#define HWIO_APSS_LDO_AUX_CONF_IN          \
        in_dword(HWIO_APSS_LDO_AUX_CONF_ADDR)
#define HWIO_APSS_LDO_AUX_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_AUX_CONF_ADDR, m)
#define HWIO_APSS_LDO_AUX_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_AUX_CONF_ADDR,v)
#define HWIO_APSS_LDO_AUX_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_AUX_CONF_ADDR,m,v,HWIO_APSS_LDO_AUX_CONF_IN)
#define HWIO_APSS_LDO_AUX_CONF_LDO_AUX_DISCHARGE_BMSK                      0x2
#define HWIO_APSS_LDO_AUX_CONF_LDO_AUX_DISCHARGE_SHFT                      0x1
#define HWIO_APSS_LDO_AUX_CONF_LDO_AUX_SEL_TEST_BMSK                       0x1
#define HWIO_APSS_LDO_AUX_CONF_LDO_AUX_SEL_TEST_SHFT                       0x0

#define HWIO_APSS_LDO_DIG_CONF_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000008)
#define HWIO_APSS_LDO_DIG_CONF_RMSK                                        0x1
#define HWIO_APSS_LDO_DIG_CONF_IN          \
        in_dword(HWIO_APSS_LDO_DIG_CONF_ADDR)
#define HWIO_APSS_LDO_DIG_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_DIG_CONF_ADDR, m)
#define HWIO_APSS_LDO_DIG_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_DIG_CONF_ADDR,v)
#define HWIO_APSS_LDO_DIG_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_DIG_CONF_ADDR,m,v,HWIO_APSS_LDO_DIG_CONF_IN)
#define HWIO_APSS_LDO_DIG_CONF_LDO_DIG_SEL_TEST_BMSK                       0x1
#define HWIO_APSS_LDO_DIG_CONF_LDO_DIG_SEL_TEST_SHFT                       0x0

#define HWIO_APSS_VLA_SRC_CTRL_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x0000000c)
#define HWIO_APSS_VLA_SRC_CTRL_RMSK                                       0x1f
#define HWIO_APSS_VLA_SRC_CTRL_IN          \
        in_dword(HWIO_APSS_VLA_SRC_CTRL_ADDR)
#define HWIO_APSS_VLA_SRC_CTRL_INM(m)      \
        in_dword_masked(HWIO_APSS_VLA_SRC_CTRL_ADDR, m)
#define HWIO_APSS_VLA_SRC_CTRL_OUT(v)      \
        out_dword(HWIO_APSS_VLA_SRC_CTRL_ADDR,v)
#define HWIO_APSS_VLA_SRC_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_VLA_SRC_CTRL_ADDR,m,v,HWIO_APSS_VLA_SRC_CTRL_IN)
#define HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BMSK                               0x10
#define HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_SHFT                                0x4
#define HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BIAS_BMSK                           0x8
#define HWIO_APSS_VLA_SRC_CTRL_SMPS_EN_BIAS_SHFT                           0x3
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_ENABLE_BMSK                   0x4
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_ENABLE_SHFT                   0x2
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_DISABLE_BMSK                  0x2
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_FORCE_DISABLE_SHFT                  0x1
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_EN_BMSK                             0x1
#define HWIO_APSS_VLA_SRC_CTRL_LDO_VLA_EN_SHFT                             0x0

#define HWIO_APSS_LDO_VLA_SEL_VOUT_ADDR                             (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000010)
#define HWIO_APSS_LDO_VLA_SEL_VOUT_RMSK                                    0x7
#define HWIO_APSS_LDO_VLA_SEL_VOUT_IN          \
        in_dword(HWIO_APSS_LDO_VLA_SEL_VOUT_ADDR)
#define HWIO_APSS_LDO_VLA_SEL_VOUT_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_VLA_SEL_VOUT_ADDR, m)
#define HWIO_APSS_LDO_VLA_SEL_VOUT_OUT(v)      \
        out_dword(HWIO_APSS_LDO_VLA_SEL_VOUT_ADDR,v)
#define HWIO_APSS_LDO_VLA_SEL_VOUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_VLA_SEL_VOUT_ADDR,m,v,HWIO_APSS_LDO_VLA_SEL_VOUT_IN)
#define HWIO_APSS_LDO_VLA_SEL_VOUT_LDO_VLA_SEL_VOUT_BMSK                   0x7
#define HWIO_APSS_LDO_VLA_SEL_VOUT_LDO_VLA_SEL_VOUT_SHFT                   0x0

#define HWIO_APSS_LDO_VLA_CONF_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000014)
#define HWIO_APSS_LDO_VLA_CONF_RMSK                                        0x7
#define HWIO_APSS_LDO_VLA_CONF_IN          \
        in_dword(HWIO_APSS_LDO_VLA_CONF_ADDR)
#define HWIO_APSS_LDO_VLA_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_VLA_CONF_ADDR, m)
#define HWIO_APSS_LDO_VLA_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_VLA_CONF_ADDR,v)
#define HWIO_APSS_LDO_VLA_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_VLA_CONF_ADDR,m,v,HWIO_APSS_LDO_VLA_CONF_IN)
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_SEL_PT_BMSK                         0x4
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_SEL_PT_SHFT                         0x2
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_DISCHARGE_BMSK                      0x2
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_DISCHARGE_SHFT                      0x1
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_SEL_TEST_BMSK                       0x1
#define HWIO_APSS_LDO_VLA_CONF_LDO_VLA_SEL_TEST_SHFT                       0x0

#define HWIO_APSS_LDO_DEBUG_STATUS_ADDR                             (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000018)
#define HWIO_APSS_LDO_DEBUG_STATUS_RMSK                                    0x1
#define HWIO_APSS_LDO_DEBUG_STATUS_IN          \
        in_dword(HWIO_APSS_LDO_DEBUG_STATUS_ADDR)
#define HWIO_APSS_LDO_DEBUG_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_DEBUG_STATUS_ADDR, m)
#define HWIO_APSS_LDO_DEBUG_STATUS_LDO_VLA_OK_BMSK                         0x1
#define HWIO_APSS_LDO_DEBUG_STATUS_LDO_VLA_OK_SHFT                         0x0

#define HWIO_APSS_SMPS_CONF_ADDR                                    (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x0000001c)
#define HWIO_APSS_SMPS_CONF_RMSK                                        0x7fff
#define HWIO_APSS_SMPS_CONF_IN          \
        in_dword(HWIO_APSS_SMPS_CONF_ADDR)
#define HWIO_APSS_SMPS_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_CONF_ADDR, m)
#define HWIO_APSS_SMPS_CONF_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_CONF_ADDR,v)
#define HWIO_APSS_SMPS_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_CONF_ADDR,m,v,HWIO_APSS_SMPS_CONF_IN)
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_NONOV_TIME_BMSK                    0x7000
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_NONOV_TIME_SHFT                       0xc
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_TON_BMSK                      0xc00
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_TON_SHFT                        0xa
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_COMP_VALID_BMSK               0x300
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_COMP_VALID_SHFT                 0x8
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_COMP_BIAS_BMSK                 0xc0
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_DELAY_COMP_BIAS_SHFT                  0x6
#define HWIO_APSS_SMPS_CONF_SMPS_DIS_ESD_BMSK                             0x20
#define HWIO_APSS_SMPS_CONF_SMPS_DIS_ESD_SHFT                              0x5
#define HWIO_APSS_SMPS_CONF_SMPS_EN_TEST_BUFF_BMSK                        0x10
#define HWIO_APSS_SMPS_CONF_SMPS_EN_TEST_BUFF_SHFT                         0x4
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_SLEW_NMOS_BMSK                        0x8
#define HWIO_APSS_SMPS_CONF_SMPS_SEL_SLEW_NMOS_SHFT                        0x3
#define HWIO_APSS_SMPS_CONF_SMPS_SELB_SLEW_PMOS_BMSK                       0x4
#define HWIO_APSS_SMPS_CONF_SMPS_SELB_SLEW_PMOS_SHFT                       0x2
#define HWIO_APSS_SMPS_CONF_SMPS_DIS_DCM_BMSK                              0x2
#define HWIO_APSS_SMPS_CONF_SMPS_DIS_DCM_SHFT                              0x1
#define HWIO_APSS_SMPS_CONF_SMPS_EN_TON_FVIN_BMSK                          0x1
#define HWIO_APSS_SMPS_CONF_SMPS_EN_TON_FVIN_SHFT                          0x0

#define HWIO_APSS_SMPS_SEL_VOUT_ADDR                                (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000020)
#define HWIO_APSS_SMPS_SEL_VOUT_RMSK                                       0x7
#define HWIO_APSS_SMPS_SEL_VOUT_IN          \
        in_dword(HWIO_APSS_SMPS_SEL_VOUT_ADDR)
#define HWIO_APSS_SMPS_SEL_VOUT_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_SEL_VOUT_ADDR, m)
#define HWIO_APSS_SMPS_SEL_VOUT_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_SEL_VOUT_ADDR,v)
#define HWIO_APSS_SMPS_SEL_VOUT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_SEL_VOUT_ADDR,m,v,HWIO_APSS_SMPS_SEL_VOUT_IN)
#define HWIO_APSS_SMPS_SEL_VOUT_SMPS_SEL_VOUT_BMSK                         0x7
#define HWIO_APSS_SMPS_SEL_VOUT_SMPS_SEL_VOUT_SHFT                         0x0

#define HWIO_APSS_SMPS_TRIM_ADDR                                    (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000024)
#define HWIO_APSS_SMPS_TRIM_RMSK                                         0xfff
#define HWIO_APSS_SMPS_TRIM_IN          \
        in_dword(HWIO_APSS_SMPS_TRIM_ADDR)
#define HWIO_APSS_SMPS_TRIM_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_TRIM_ADDR, m)
#define HWIO_APSS_SMPS_TRIM_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_TRIM_ADDR,v)
#define HWIO_APSS_SMPS_TRIM_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_TRIM_ADDR,m,v,HWIO_APSS_SMPS_TRIM_IN)
#define HWIO_APSS_SMPS_TRIM_SMPS_ZX_OFFSET_TRIM_BMSK                     0xc00
#define HWIO_APSS_SMPS_TRIM_SMPS_ZX_OFFSET_TRIM_SHFT                       0xa
#define HWIO_APSS_SMPS_TRIM_SMPS_ITRIM_TON_FVIN_BMSK                     0x3e0
#define HWIO_APSS_SMPS_TRIM_SMPS_ITRIM_TON_FVIN_SHFT                       0x5
#define HWIO_APSS_SMPS_TRIM_SMPS_ITRIM_TON_BMSK                           0x1f
#define HWIO_APSS_SMPS_TRIM_SMPS_ITRIM_TON_SHFT                            0x0

#define HWIO_APSS_SMPS_TEST0_ADDR                                   (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000028)
#define HWIO_APSS_SMPS_TEST0_RMSK                                       0xffff
#define HWIO_APSS_SMPS_TEST0_IN          \
        in_dword(HWIO_APSS_SMPS_TEST0_ADDR)
#define HWIO_APSS_SMPS_TEST0_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_TEST0_ADDR, m)
#define HWIO_APSS_SMPS_TEST0_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_TEST0_ADDR,v)
#define HWIO_APSS_SMPS_TEST0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_TEST0_ADDR,m,v,HWIO_APSS_SMPS_TEST0_IN)
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_DIS_NFET_BMSK                    0xf000
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_DIS_NFET_SHFT                       0xc
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_EN_NFET_BMSK                      0xf00
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_EN_NFET_SHFT                        0x8
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_DIS_PFET_BMSK                      0xf0
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_DIS_PFET_SHFT                       0x4
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_EN_PFET_BMSK                        0xf
#define HWIO_APSS_SMPS_TEST0_SMPS_TEST_EN_PFET_SHFT                        0x0

#define HWIO_APSS_SMPS_TEST1_ADDR                                   (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x0000002c)
#define HWIO_APSS_SMPS_TEST1_RMSK                                       0x1fff
#define HWIO_APSS_SMPS_TEST1_IN          \
        in_dword(HWIO_APSS_SMPS_TEST1_ADDR)
#define HWIO_APSS_SMPS_TEST1_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_TEST1_ADDR, m)
#define HWIO_APSS_SMPS_TEST1_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_TEST1_ADDR,v)
#define HWIO_APSS_SMPS_TEST1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_TEST1_ADDR,m,v,HWIO_APSS_SMPS_TEST1_IN)
#define HWIO_APSS_SMPS_TEST1_SMPS_TEST_ANA_IN_BMSK                      0x1f00
#define HWIO_APSS_SMPS_TEST1_SMPS_TEST_ANA_IN_SHFT                         0x8
#define HWIO_APSS_SMPS_TEST1_SMPS_TEST_DIG_IN_BMSK                        0xff
#define HWIO_APSS_SMPS_TEST1_SMPS_TEST_DIG_IN_SHFT                         0x0

#define HWIO_APSS_SMPS_STATUS_ADDR                                  (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000030)
#define HWIO_APSS_SMPS_STATUS_RMSK                                        0xff
#define HWIO_APSS_SMPS_STATUS_IN          \
        in_dword(HWIO_APSS_SMPS_STATUS_ADDR)
#define HWIO_APSS_SMPS_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_STATUS_ADDR, m)
#define HWIO_APSS_SMPS_STATUS_SMPS_TEST_DIG_OUT_BMSK                      0xff
#define HWIO_APSS_SMPS_STATUS_SMPS_TEST_DIG_OUT_SHFT                       0x0

#define HWIO_APSS_FOSC_CONF_ADDR                                    (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000034)
#define HWIO_APSS_FOSC_CONF_RMSK                                         0x7ff
#define HWIO_APSS_FOSC_CONF_IN          \
        in_dword(HWIO_APSS_FOSC_CONF_ADDR)
#define HWIO_APSS_FOSC_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_FOSC_CONF_ADDR, m)
#define HWIO_APSS_FOSC_CONF_OUT(v)      \
        out_dword(HWIO_APSS_FOSC_CONF_ADDR,v)
#define HWIO_APSS_FOSC_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_FOSC_CONF_ADDR,m,v,HWIO_APSS_FOSC_CONF_IN)
#define HWIO_APSS_FOSC_CONF_FOSC_TRIM_FOUT_BMSK                          0x7f8
#define HWIO_APSS_FOSC_CONF_FOSC_TRIM_FOUT_SHFT                            0x3
#define HWIO_APSS_FOSC_CONF_FOSC_CTRL_FOUT_BMSK                            0x7
#define HWIO_APSS_FOSC_CONF_FOSC_CTRL_FOUT_SHFT                            0x0

#define HWIO_APSS_ULPBG_CTRL_ADDR                                   (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000038)
#define HWIO_APSS_ULPBG_CTRL_RMSK                                         0x7f
#define HWIO_APSS_ULPBG_CTRL_IN          \
        in_dword(HWIO_APSS_ULPBG_CTRL_ADDR)
#define HWIO_APSS_ULPBG_CTRL_INM(m)      \
        in_dword_masked(HWIO_APSS_ULPBG_CTRL_ADDR, m)
#define HWIO_APSS_ULPBG_CTRL_OUT(v)      \
        out_dword(HWIO_APSS_ULPBG_CTRL_ADDR,v)
#define HWIO_APSS_ULPBG_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_ULPBG_CTRL_ADDR,m,v,HWIO_APSS_ULPBG_CTRL_IN)
#define HWIO_APSS_ULPBG_CTRL_ULPBG_EN_TEST_BMSK                           0x7f
#define HWIO_APSS_ULPBG_CTRL_ULPBG_EN_TEST_SHFT                            0x0

#define HWIO_APSS_ULPBG_SPARE_ADDR                                  (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x0000003c)
#define HWIO_APSS_ULPBG_SPARE_RMSK                                         0x1
#define HWIO_APSS_ULPBG_SPARE_IN          \
        in_dword(HWIO_APSS_ULPBG_SPARE_ADDR)
#define HWIO_APSS_ULPBG_SPARE_INM(m)      \
        in_dword_masked(HWIO_APSS_ULPBG_SPARE_ADDR, m)
#define HWIO_APSS_ULPBG_SPARE_OUT(v)      \
        out_dword(HWIO_APSS_ULPBG_SPARE_ADDR,v)
#define HWIO_APSS_ULPBG_SPARE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_ULPBG_SPARE_ADDR,m,v,HWIO_APSS_ULPBG_SPARE_IN)
#define HWIO_APSS_ULPBG_SPARE_ULPBG_SPARE_BMSK                             0x1
#define HWIO_APSS_ULPBG_SPARE_ULPBG_SPARE_SHFT                             0x0

#define HWIO_APSS_ULPBG_STATUS_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000040)
#define HWIO_APSS_ULPBG_STATUS_RMSK                                       0x3f
#define HWIO_APSS_ULPBG_STATUS_IN          \
        in_dword(HWIO_APSS_ULPBG_STATUS_ADDR)
#define HWIO_APSS_ULPBG_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_ULPBG_STATUS_ADDR, m)
#define HWIO_APSS_ULPBG_STATUS_NANOCORE_DTEST_BMSK                        0x3f
#define HWIO_APSS_ULPBG_STATUS_NANOCORE_DTEST_SHFT                         0x0

#define HWIO_APSS_XTAL_CONF_ADDR                                    (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000044)
#define HWIO_APSS_XTAL_CONF_RMSK                                         0x1ff
#define HWIO_APSS_XTAL_CONF_IN          \
        in_dword(HWIO_APSS_XTAL_CONF_ADDR)
#define HWIO_APSS_XTAL_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_XTAL_CONF_ADDR, m)
#define HWIO_APSS_XTAL_CONF_OUT(v)      \
        out_dword(HWIO_APSS_XTAL_CONF_ADDR,v)
#define HWIO_APSS_XTAL_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_XTAL_CONF_ADDR,m,v,HWIO_APSS_XTAL_CONF_IN)
#define HWIO_APSS_XTAL_CONF_XTAL_EN_TEST_IBIAS_BMSK                      0x100
#define HWIO_APSS_XTAL_CONF_XTAL_EN_TEST_IBIAS_SHFT                        0x8
#define HWIO_APSS_XTAL_CONF_XTAL_SPEEDUP_EN_BMSK                          0x80
#define HWIO_APSS_XTAL_CONF_XTAL_SPEEDUP_EN_SHFT                           0x7
#define HWIO_APSS_XTAL_CONF_XTAL_EN_AMPDET_BMSK                           0x40
#define HWIO_APSS_XTAL_CONF_XTAL_EN_AMPDET_SHFT                            0x6
#define HWIO_APSS_XTAL_CONF_XTAL_GAIN_SET_BMSK                            0x3f
#define HWIO_APSS_XTAL_CONF_XTAL_GAIN_SET_SHFT                             0x0

#define HWIO_APSS_XTAL_CL_CONF_ADDR                                 (APSS_PMU_STATIC_ADDA_VLP_REG_REG_BASE      + 0x00000048)
#define HWIO_APSS_XTAL_CL_CONF_RMSK                                      0x1ff
#define HWIO_APSS_XTAL_CL_CONF_IN          \
        in_dword(HWIO_APSS_XTAL_CL_CONF_ADDR)
#define HWIO_APSS_XTAL_CL_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_XTAL_CL_CONF_ADDR, m)
#define HWIO_APSS_XTAL_CL_CONF_OUT(v)      \
        out_dword(HWIO_APSS_XTAL_CL_CONF_ADDR,v)
#define HWIO_APSS_XTAL_CL_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_XTAL_CL_CONF_ADDR,m,v,HWIO_APSS_XTAL_CL_CONF_IN)
#define HWIO_APSS_XTAL_CL_CONF_XTAL_TRIM_CL_BMSK                         0x1ff
#define HWIO_APSS_XTAL_CL_CONF_XTAL_TRIM_CL_SHFT                           0x0

/*----------------------------------------------------------------------------
 * MODULE: APSS_PMU_VLP_SD_REG
 *--------------------------------------------------------------------------*/

#define APSS_PMU_VLP_SD_REG_REG_BASE (PMU_MTOP_02_BASE      + 0x00000900)
#define APSS_PMU_VLP_SD_REG_REG_BASE_SIZE 0x100
#define APSS_PMU_VLP_SD_REG_REG_BASE_USED 0x0

/*----------------------------------------------------------------------------
 * MODULE: APSS_PMU_CTRL_STATUS_VLP_SD_REG
 *--------------------------------------------------------------------------*/

#define APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE                                          (PMU_MTOP_02_BASE      + 0x00000900)
#define APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE_SIZE                                     0x80
#define APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE_USED                                     0x1c

#define HWIO_APSS_MTOP_ID_ADDR                                                            (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000000)
#define HWIO_APSS_MTOP_ID_RMSK                                                                  0xff
#define HWIO_APSS_MTOP_ID_IN          \
        in_dword(HWIO_APSS_MTOP_ID_ADDR)
#define HWIO_APSS_MTOP_ID_INM(m)      \
        in_dword_masked(HWIO_APSS_MTOP_ID_ADDR, m)
#define HWIO_APSS_MTOP_ID_MTOP_ID_BMSK                                                          0xff
#define HWIO_APSS_MTOP_ID_MTOP_ID_SHFT                                                           0x0

#define HWIO_APSS_MDIG_VER_ADDR                                                           (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000004)
#define HWIO_APSS_MDIG_VER_RMSK                                                               0xffff
#define HWIO_APSS_MDIG_VER_IN          \
        in_dword(HWIO_APSS_MDIG_VER_ADDR)
#define HWIO_APSS_MDIG_VER_INM(m)      \
        in_dword_masked(HWIO_APSS_MDIG_VER_ADDR, m)
#define HWIO_APSS_MDIG_VER_MDIG_VER_MINOR_BMSK                                                0xff00
#define HWIO_APSS_MDIG_VER_MDIG_VER_MINOR_SHFT                                                   0x8
#define HWIO_APSS_MDIG_VER_MDIG_VER_MAJOR_BMSK                                                  0xff
#define HWIO_APSS_MDIG_VER_MDIG_VER_MAJOR_SHFT                                                   0x0

#define HWIO_APSS_AHM_VER_ADDR                                                            (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000008)
#define HWIO_APSS_AHM_VER_RMSK                                                                0xffff
#define HWIO_APSS_AHM_VER_IN          \
        in_dword(HWIO_APSS_AHM_VER_ADDR)
#define HWIO_APSS_AHM_VER_INM(m)      \
        in_dword_masked(HWIO_APSS_AHM_VER_ADDR, m)
#define HWIO_APSS_AHM_VER_AHM_VER_MINOR_BMSK                                                  0xff00
#define HWIO_APSS_AHM_VER_AHM_VER_MINOR_SHFT                                                     0x8
#define HWIO_APSS_AHM_VER_AHM_VER_MAJOR_BMSK                                                    0xff
#define HWIO_APSS_AHM_VER_AHM_VER_MAJOR_SHFT                                                     0x0

#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_ADDR                                            (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x0000000c)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_RMSK                                                   0x7
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_IN          \
        in_dword(HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_ADDR)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_ADDR, m)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_OUT(v)      \
        out_dword(HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_ADDR,v)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_ADDR,m,v,HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_IN)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_SMPS_ANA_CLK_DIV_RATIO_SEL_BMSK                        0x6
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_SMPS_ANA_CLK_DIV_RATIO_SEL_SHFT                        0x1
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_SMPS_ANA_CLK_32M_SEL_BMSK                              0x1
#define HWIO_APSS_SMPS_PFM_ANA_CLK_CONFIG_SMPS_ANA_CLK_32M_SEL_SHFT                              0x0

#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_ADDR                                            (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000010)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_RMSK                                                   0x7
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_IN          \
        in_dword(HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_ADDR)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_INM(m)      \
        in_dword_masked(HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_ADDR, m)
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_SMPS_ANA_CLK_DIV_RATIO_SEL_STATUS_BMSK                 0x6
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_SMPS_ANA_CLK_DIV_RATIO_SEL_STATUS_SHFT                 0x1
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_SMPS_ANA_CLK_32M_SEL_STATUS_BMSK                       0x1
#define HWIO_APSS_SMPS_PFM_ANA_CLK_STATUS_SMPS_ANA_CLK_32M_SEL_STATUS_SHFT                       0x0

#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_ADDR                                              (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000014)
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_RMSK                                                    0xff
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_IN          \
        in_dword(HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_ADDR)
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_INM(m)      \
        in_dword_masked(HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_ADDR, m)
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_OUT(v)      \
        out_dword(HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_ADDR,v)
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_ADDR,m,v,HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_IN)
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_BYP_ENA_BMSK                                   0x80
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_BYP_ENA_SHFT                                    0x7
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_STEP_RATE_SEL_BMSK                             0x60
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_STEP_RATE_SEL_SHFT                              0x5
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_SEL_VOUT_TARGET_BMSK                           0x1f
#define HWIO_APSS_LDO_DIG_VOL_RAMP_CONF_VOL_RAMP_SEL_VOUT_TARGET_SHFT                            0x0

#define HWIO_APSS_PMU_SOSC_CTRL_ADDR                                                      (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x00000018)
#define HWIO_APSS_PMU_SOSC_CTRL_RMSK                                                             0xf
#define HWIO_APSS_PMU_SOSC_CTRL_OUT(v)      \
        out_dword(HWIO_APSS_PMU_SOSC_CTRL_ADDR,v)
#define HWIO_APSS_PMU_SOSC_CTRL_AHM_DEBOUCING_EXT_CLK_DISABLE_REQ_BMSK                           0x8
#define HWIO_APSS_PMU_SOSC_CTRL_AHM_DEBOUCING_EXT_CLK_DISABLE_REQ_SHFT                           0x3
#define HWIO_APSS_PMU_SOSC_CTRL_AHM_DEBOUCING_EXT_CLK_ENABLE_REQ_BMSK                            0x4
#define HWIO_APSS_PMU_SOSC_CTRL_AHM_DEBOUCING_EXT_CLK_ENABLE_REQ_SHFT                            0x2
#define HWIO_APSS_PMU_SOSC_CTRL_SOSC_REENABLE_REQ_BMSK                                           0x2
#define HWIO_APSS_PMU_SOSC_CTRL_SOSC_REENABLE_REQ_SHFT                                           0x1
#define HWIO_APSS_PMU_SOSC_CTRL_SOSC_FORCE_DISABLE_REQ_BMSK                                      0x1
#define HWIO_APSS_PMU_SOSC_CTRL_SOSC_FORCE_DISABLE_REQ_SHFT                                      0x0

#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_ADDR                                                 (APSS_PMU_CTRL_STATUS_VLP_SD_REG_REG_BASE      + 0x0000001c)
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_RMSK                                                        0x3
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_IN          \
        in_dword(HWIO_APSS_EFUSE_VDDQ_EN_CTRL_ADDR)
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_INM(m)      \
        in_dword_masked(HWIO_APSS_EFUSE_VDDQ_EN_CTRL_ADDR, m)
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_OUT(v)      \
        out_dword(HWIO_APSS_EFUSE_VDDQ_EN_CTRL_ADDR,v)
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_APSS_EFUSE_VDDQ_EN_CTRL_ADDR,m,v,HWIO_APSS_EFUSE_VDDQ_EN_CTRL_IN)
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_EFUSE_VDDQ_EXT_CTRL_ENA_BMSK                                0x2
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_EFUSE_VDDQ_EXT_CTRL_ENA_SHFT                                0x1
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_EFUSE_VDDQ_EN_BMSK                                          0x1
#define HWIO_APSS_EFUSE_VDDQ_EN_CTRL_EFUSE_VDDQ_EN_SHFT                                          0x0


#endif /* __HWIO_PMU_H__ */
