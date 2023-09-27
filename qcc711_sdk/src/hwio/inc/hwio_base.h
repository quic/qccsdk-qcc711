#ifndef __HWIO_BASE_H__
#define __HWIO_BASE_H__
/*
===========================================================================
*/
/**
  @file hwio_base.h
  @brief Auto-generated HWIO base include file.
*/
/*
  ===========================================================================

  Copyright (c) 2021 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_NVM_RRAM_REMAP
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_NVM_RRAM_REMAP_BASE                              0x00000000
#define SHARED_RAM_NVM_RRAM_REMAP_BASE_SIZE                         0x100000000
#define SHARED_RAM_NVM_RRAM_REMAP_BASE_PHYS                         0x00000000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S0
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S0_BASE                                     0x00000000
#define SHARED_RAM_SRAM_S0_BASE_SIZE                                0x100000000
#define SHARED_RAM_SRAM_S0_BASE_PHYS                                0x00000000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S0
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S0_BASE                               0x00000000
#define SHARED_RAM_UPPER_SRAM_S0_BASE_SIZE                          0x100000000
#define SHARED_RAM_UPPER_SRAM_S0_BASE_PHYS                          0x00000000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S0_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S0_END_BASE                                 0x0000ffff
#define SHARED_RAM_SRAM_S0_END_BASE_SIZE                            0x100000000
#define SHARED_RAM_SRAM_S0_END_BASE_PHYS                            0x0000ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S0_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S0_END_BASE                           0x0000ffff
#define SHARED_RAM_UPPER_SRAM_S0_END_BASE_SIZE                      0x100000000
#define SHARED_RAM_UPPER_SRAM_S0_END_BASE_PHYS                      0x0000ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S0_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S0_SIZE_BASE                                0x00010000
#define SHARED_RAM_SRAM_S0_SIZE_BASE_SIZE                           0x100000000
#define SHARED_RAM_SRAM_S0_SIZE_BASE_PHYS                           0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S1
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S1_BASE                                     0x00010000
#define SHARED_RAM_SRAM_S1_BASE_SIZE                                0x100000000
#define SHARED_RAM_SRAM_S1_BASE_PHYS                                0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S1_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S1_SIZE_BASE                                0x00010000
#define SHARED_RAM_SRAM_S1_SIZE_BASE_SIZE                           0x100000000
#define SHARED_RAM_SRAM_S1_SIZE_BASE_PHYS                           0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S0_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S0_SIZE_BASE                          0x00010000
#define SHARED_RAM_UPPER_SRAM_S0_SIZE_BASE_SIZE                     0x100000000
#define SHARED_RAM_UPPER_SRAM_S0_SIZE_BASE_PHYS                     0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S1
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S1_BASE                               0x00010000
#define SHARED_RAM_UPPER_SRAM_S1_BASE_SIZE                          0x100000000
#define SHARED_RAM_UPPER_SRAM_S1_BASE_PHYS                          0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S1_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S1_SIZE_BASE                          0x00010000
#define SHARED_RAM_UPPER_SRAM_S1_SIZE_BASE_SIZE                     0x100000000
#define SHARED_RAM_UPPER_SRAM_S1_SIZE_BASE_PHYS                     0x00010000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SRAM_S1_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SRAM_S1_END_BASE                                 0x0001ffff
#define SHARED_RAM_SRAM_S1_END_BASE_SIZE                            0x100000000
#define SHARED_RAM_SRAM_S1_END_BASE_PHYS                            0x0001ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SRAM_S1_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SRAM_S1_END_BASE                           0x0001ffff
#define SHARED_RAM_UPPER_SRAM_S1_END_BASE_SIZE                      0x100000000
#define SHARED_RAM_UPPER_SRAM_S1_END_BASE_PHYS                      0x0001ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_SIZE_BASE                                        0x00020000
#define SHARED_RAM_SIZE_BASE_SIZE                                   0x100000000
#define SHARED_RAM_SIZE_BASE_PHYS                                   0x00020000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_SIZE_BASE                                  0x00020000
#define SHARED_RAM_UPPER_SIZE_BASE_SIZE                             0x100000000
#define SHARED_RAM_UPPER_SIZE_BASE_PHYS                             0x00020000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_NVM_RRAM_REMAP_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_NVM_RRAM_REMAP_END_BASE                          0x0007ffff
#define SHARED_RAM_NVM_RRAM_REMAP_END_BASE_SIZE                     0x100000000
#define SHARED_RAM_NVM_RRAM_REMAP_END_BASE_PHYS                     0x0007ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_NVM_RRAM_REMAP_SIZE
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_NVM_RRAM_REMAP_SIZE_BASE                         0x00080000
#define SHARED_RAM_NVM_RRAM_REMAP_SIZE_BASE_SIZE                    0x100000000
#define SHARED_RAM_NVM_RRAM_REMAP_SIZE_BASE_PHYS                    0x00080000

/*----------------------------------------------------------------------------
 * BASE: NVM_RRAM_SIZE
 *--------------------------------------------------------------------------*/

#define NVM_RRAM_SIZE_BASE                                          0x00080000
#define NVM_RRAM_SIZE_BASE_SIZE                                     0x100000000
#define NVM_RRAM_SIZE_BASE_PHYS                                     0x00080000

/*----------------------------------------------------------------------------
 * BASE: NVM_RRAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define NVM_RRAM_START_ADDRESS_BASE                                 0x10200000
#define NVM_RRAM_START_ADDRESS_BASE_SIZE                            0x100000000
#define NVM_RRAM_START_ADDRESS_BASE_PHYS                            0x10200000

/*----------------------------------------------------------------------------
 * BASE: NVM_RRAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define NVM_RRAM_END_ADDRESS_BASE                                   0x1027ffff
#define NVM_RRAM_END_ADDRESS_BASE_SIZE                              0x100000000
#define NVM_RRAM_END_ADDRESS_BASE_PHYS                              0x1027ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_START_ADDRESS
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_START_ADDRESS_BASE                               0x18200000
#define SHARED_RAM_START_ADDRESS_BASE_SIZE                          0x100000000
#define SHARED_RAM_START_ADDRESS_BASE_PHYS                          0x18200000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_END_ADDRESS
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_END_ADDRESS_BASE                                 0x1821ffff
#define SHARED_RAM_END_ADDRESS_BASE_SIZE                            0x100000000
#define SHARED_RAM_END_ADDRESS_BASE_PHYS                            0x1821ffff

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_BASE                                       0x20000000
#define SHARED_RAM_UPPER_BASE_SIZE                                  0x100000000
#define SHARED_RAM_UPPER_BASE_PHYS                                  0x20000000

/*----------------------------------------------------------------------------
 * BASE: SHARED_RAM_UPPER_END
 *--------------------------------------------------------------------------*/

#define SHARED_RAM_UPPER_END_BASE                                   0x2001ffff
#define SHARED_RAM_UPPER_END_BASE_SIZE                              0x100000000
#define SHARED_RAM_UPPER_END_BASE_PHYS                              0x2001ffff

/*----------------------------------------------------------------------------
 * BASE: TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_BASE                                                   0x50000000
#define TLMM_BASE_SIZE                                              0x00001000
#define TLMM_BASE_PHYS                                              0x50000000

/*----------------------------------------------------------------------------
 * BASE: GCC_REG
 *--------------------------------------------------------------------------*/

#define GCC_REG_BASE                                                0x50002000
#define GCC_REG_BASE_SIZE                                           0x00001000
#define GCC_REG_BASE_PHYS                                           0x50002000

/*----------------------------------------------------------------------------
 * BASE: PMU_MTOP_02
 *--------------------------------------------------------------------------*/

#define PMU_MTOP_02_BASE                                            0x50004000
#define PMU_MTOP_02_BASE_SIZE                                       0x00001000
#define PMU_MTOP_02_BASE_PHYS                                       0x50004000

/*----------------------------------------------------------------------------
 * BASE: AON_PME_PME_AC
 *--------------------------------------------------------------------------*/

#define AON_PME_PME_AC_BASE                                         0x50006000
#define AON_PME_PME_AC_BASE_SIZE                                    0x00001000
#define AON_PME_PME_AC_BASE_PHYS                                    0x50006000

/*----------------------------------------------------------------------------
 * BASE: AON_GBLTMR_HZ_GL_TMR
 *--------------------------------------------------------------------------*/

#define AON_GBLTMR_HZ_GL_TMR_BASE                                   0x50008400
#define AON_GBLTMR_HZ_GL_TMR_BASE_SIZE                              0x00000400
#define AON_GBLTMR_HZ_GL_TMR_BASE_PHYS                              0x50008400

/*----------------------------------------------------------------------------
 * BASE: AON_GBLTMR_SLV_HZ_GL_TMR_SLV
 *--------------------------------------------------------------------------*/

#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_BASE                           0x50008800
#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_BASE_SIZE                      0x00000400
#define AON_GBLTMR_SLV_HZ_GL_TMR_SLV_BASE_PHYS                      0x50008800

/*----------------------------------------------------------------------------
 * BASE: AON_CTMR_HZ_CE_TMR
 *--------------------------------------------------------------------------*/

#define AON_CTMR_HZ_CE_TMR_BASE                                     0x50009800
#define AON_CTMR_HZ_CE_TMR_BASE_SIZE                                0x00001000
#define AON_CTMR_HZ_CE_TMR_BASE_PHYS                                0x50009800

/*----------------------------------------------------------------------------
 * BASE: AON_WDOG_HZ_WATCHDOG
 *--------------------------------------------------------------------------*/

#define AON_WDOG_HZ_WATCHDOG_BASE                                   0x5000c800
#define AON_WDOG_HZ_WATCHDOG_BASE_SIZE                              0x00000100
#define AON_WDOG_HZ_WATCHDOG_BASE_PHYS                              0x5000c800

/*----------------------------------------------------------------------------
 * BASE: AON_TCSR_TCSR
 *--------------------------------------------------------------------------*/

#define AON_TCSR_TCSR_BASE                                          0x5000d000
#define AON_TCSR_TCSR_BASE_SIZE                                     0x00001000
#define AON_TCSR_TCSR_BASE_PHYS                                     0x5000d000

/*----------------------------------------------------------------------------
 * BASE: NAON_NAON_EFUSE_CSR
 *--------------------------------------------------------------------------*/

#define NAON_NAON_EFUSE_CSR_BASE                                    0x5000f000
#define NAON_NAON_EFUSE_CSR_BASE_SIZE                               0x00000100
#define NAON_NAON_EFUSE_CSR_BASE_PHYS                               0x5000f000

/*----------------------------------------------------------------------------
 * BASE: OTP_ZIGGY_V_2_0_QFPROM_RAW_FUSE_MAP
 *--------------------------------------------------------------------------*/

#define OTP_ZIGGY_V_2_0_QFPROM_RAW_FUSE_MAP_BASE                    0x50040000
#define OTP_ZIGGY_V_2_0_QFPROM_RAW_FUSE_MAP_BASE_SIZE               0x00000800
#define OTP_ZIGGY_V_2_0_QFPROM_RAW_FUSE_MAP_BASE_PHYS               0x50040000

/*----------------------------------------------------------------------------
 * BASE: OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP
 *--------------------------------------------------------------------------*/

#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_BASE                   0x50040800
#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_BASE_SIZE              0x00000800
#define OTP_ZIGGY_V_2_0_QFPROM_CORR_FUSE_MAP_BASE_PHYS              0x50040800

/*----------------------------------------------------------------------------
 * BASE: NVM
 *--------------------------------------------------------------------------*/

#define NVM_BASE                                                    0x50041000
#define NVM_BASE_SIZE                                               0x00001000
#define NVM_BASE_PHYS                                               0x50041000

/*----------------------------------------------------------------------------
 * BASE: SRM_CSR
 *--------------------------------------------------------------------------*/

#define SRM_CSR_BASE                                                0x50050000
#define SRM_CSR_BASE_SIZE                                           0x00010000
#define SRM_CSR_BASE_PHYS                                           0x50050000

/*----------------------------------------------------------------------------
 * BASE: SYS_FABRIC_SYS_FABRIC_CSR
 *--------------------------------------------------------------------------*/

#define SYS_FABRIC_SYS_FABRIC_CSR_BASE                              0x50060000
#define SYS_FABRIC_SYS_FABRIC_CSR_BASE_SIZE                         0x00001000
#define SYS_FABRIC_SYS_FABRIC_CSR_BASE_PHYS                         0x50060000

/*----------------------------------------------------------------------------
 * BASE: TMELITE_IPC_EXTERNAL
 *--------------------------------------------------------------------------*/

#define TMELITE_IPC_EXTERNAL_BASE                                   0x50070000
#define TMELITE_IPC_EXTERNAL_BASE_SIZE                              0x00002000
#define TMELITE_IPC_EXTERNAL_BASE_PHYS                              0x50070000

/*----------------------------------------------------------------------------
 * BASE: PERIPH_PERIPH_MOD
 *--------------------------------------------------------------------------*/

#define PERIPH_PERIPH_MOD_BASE                                      0x51000000
#define PERIPH_PERIPH_MOD_BASE_SIZE                                 0x00400000
#define PERIPH_PERIPH_MOD_BASE_PHYS                                 0x51000000

/*----------------------------------------------------------------------------
 * BASE: CORTEX_M3_CORTEX_M3
 *--------------------------------------------------------------------------*/

#define CORTEX_M3_CORTEX_M3_BASE                                    0xe0000000
#define CORTEX_M3_CORTEX_M3_BASE_SIZE                               0x00100000
#define CORTEX_M3_CORTEX_M3_BASE_PHYS                               0xe0000000


#endif /* __HWIO_BASE_H__ */
