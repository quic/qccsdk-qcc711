/*--------------------------------------------------------------------------*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *--------------------------------------------------------------------------*/

/** @file qapi_mtp.h
   @brief APSS MTP APIs, types, and definitions.
*/

/** @addtogroup qapi_platform_mtp
    This chapter provides APSS MTP APIs, types, and definitions.
*/

#ifndef __QAPI_MTP_H__
#define __QAPI_MTP_H__

/** @addtogroup qapi_platform_mtp
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/* Indicates the starting address of the APSS MTP. */
#define QAPI_MTP_APSS_RO_START_ADDRESS                  (0x50040B00)  /**< Read only start address of APSS MTP. */
#define QAPI_MTP_APSS_RW_START_ADDRESS                  (0x50040B80)  /**< Read/write start address of APSS MTP. */

/* Aux Field definitions. */
#define QAPI_MTP_AUX_CTRL1_SET_N_MASK                   (0x0FFF)  /**< Ctrl1 set n mask - aux. */
#define QAPI_MTP_AUX_CTRL1_SET_N_SHIFT                  (0)       /**< Ctrl1 set n shift - aux. */
#define QAPI_MTP_AUX_CTRL1_SET_N_BITMASK                (QAPI_MTP_AUX_CTRL1_SET_N_MASK << QAPI_MTP_AUX_CTRL1_SET_N_SHIFT)  /**< Ctrl1 set n bitmask - aux. */
#define QAPI_MTP_AUX_CTRL5_SET_N_MASK                   (0x0007)  /**< Ctrl5 set n mask - aux. */
#define QAPI_MTP_AUX_CTRL5_SET_N_SHIFT                  (12)      /**< Ctrl5 set n shift - aux. */
#define QAPI_MTP_AUX_CTRL5_SET_N_BITMASK                (QAPI_MTP_AUX_CTRL5_SET_N_MASK << QAPI_MTP_AUX_CTRL5_SET_N_SHIFT)  /**< Ctrl5 set n bitmask - aux. */

#define QAPI_MTP_AUX_CTRL6_SET0_MASK                    (0x0007)  /**< Ctrl6 set0 mask - aux. */
#define QAPI_MTP_AUX_CTRL6_SET0_SHIFT                   (0)       /**< Ctrl6 set0 shift - aux. */
#define QAPI_MTP_AUX_CTRL6_SET0_BITMASK                 (QAPI_MTP_AUX_CTRL6_SET0_MASK << QAPI_MTP_AUX_CTRL6_SET0_SHIFT)    /**< Ctrl6 set0 bitmask - aux. */
#define QAPI_MTP_AUX_CTRL6_SET1_MASK                    (0x0007)  /**< Ctrl6 set1 mask - aux. */
#define QAPI_MTP_AUX_CTRL6_SET1_SHIFT                   (3)       /**< Ctrl6 set1 shift - aux. */
#define QAPI_MTP_AUX_CTRL6_SET1_BITMASK                 (QAPI_MTP_AUX_CTRL6_SET1_MASK << QAPI_MTP_AUX_CTRL6_SET1_SHIFT)    /**< Ctrl6 set1 bitmask - aux. */
#define QAPI_MTP_AUX_CTRL7_MASK                         (0x01FF)  /**< Ctrl7 mask - aux. */
#define QAPI_MTP_AUX_CTRL7_SHIFT                        (6)       /**< Ctrl7 shift - aux. */
#define QAPI_MTP_AUX_CTRL7_BITMASK                      (QAPI_MTP_AUX_CTRL7_MASK << QAPI_MTP_AUX_CTRL7_SHIFT)              /**< Ctrl7 bitmask - aux. */

#define QAPI_MTP_AUX_DRV_CTRL_MASK                      (0x001FFFFF)  /**< Drv ctrl mask - aux. */
#define QAPI_MTP_AUX_DRV_CTRL_SHIFT                     (0)           /**< Drv ctrl shift - aux. */
#define QAPI_MTP_AUX_DRV_CTRL_BITMASK                   (QAPI_MTP_AUX_DRV_CTRL_MASK << QAPI_MTP_AUX_DRV_CTRL_SHIFT)  /**< Drv ctrl bitmask - aux. */
#define QAPI_MTP_AUX_CTRL9_MASK                         (0x000000FF)  /**< Ctrl9 mask - aux. */
#define QAPI_MTP_AUX_CTRL9_SHIFT                        (22)          /**< Ctrl9 shift - aux. */
#define QAPI_MTP_AUX_CTRL9_BITMASK                      (QAPI_MTP_AUX_CTRL9_MASK << QAPI_MTP_AUX_CTRL9_SHIFT)  /**< Ctrl9 bitmask - aux. */

#define QAPI_MTP_AUX_GHMIEHR_MASK                       (0x0001FFFF)  /**< Ghmiehr mask - aux. */
#define QAPI_MTP_AUX_GHMIEHR_SHIFT                      (0)           /**< Ghmiehr shift - aux. */
#define QAPI_MTP_AUX_GHMIEHR_BITMASK                    (QAPI_MTP_AUX_GHMIEHR_MASK << QAPI_MTP_AUX_GHMIEHR_SHIFT)  /**< Ghmiehr bitmask - aux. */
#define QAPI_MTP_AUX_TMUX_CTRL0_MASK                    (0x000003FF)  /**< Tmux ctrl0 mask - aux. */
#define QAPI_MTP_AUX_TMUX_CTRL0_SHIFT                   (20)          /**< Tmux ctrl0 shift - aux. */
#define QAPI_MTP_AUX_TMUX_CTRL0_BITMASK                 (QAPI_MTP_AUX_TMUX_CTRL0_MASK << QAPI_MTP_AUX_TMUX_CTRL0_SHIFT)  /**< Tmux ctrl0 bitmask - aux. */

/* 32K field definitions. */
#define QAPI_MTP_XTAL_32K_ITFAC_MASK                    (0x001F)     /**< Itfac mask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_ITFAC_SHIFT(_x_)              ((_x_) * 5)  /**< Itfac shift - 32K xtal. */
#define QAPI_MTP_XTAL_32K_ITFAC_BITMASK(_x_)            (QAPI_MTP_XTAL_32K_ITFAC_MASK << QAPI_MTP_XTAL_32K_ITFAC_SHIFT(_x_))  /**< Itfac bitmask - 32K xtal. */

#define QAPI_MTP_XTAL_32K_CFG_TRIM_CL_MASK              (0x001FF)  /**< CFG trim cl mask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_TRIM_CL_SHIFT             (0)        /**< CFG trim cl shift - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_TRIM_CL_BITMASK           (QAPI_MTP_XTAL_32K_CFG_TRIM_CL_MASK << QAPI_MTP_XTAL_32K_CFG_TRIM_CL_SHIFT)  /**< CFG trim cl bitmask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_MASK            (0x003F)  /**< CFG gain init mask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_SHIFT           (9)       /**< CFG gain init shift - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_BITMASK         (QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_MASK << QAPI_MTP_XTAL_32K_CFG_GAIN_INIT_SHIFT)  /**< CFG gain init bitmask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_MASK       (0x0001)  /**< CFG ldo vma sel pt mask - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_SHIFT      (15)      /**< CFG ldo vma sel pt shift - 32K xtal. */
#define QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_BITMASK    (QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_MASK << QAPI_MTP_XTAL_32K_CFG_LDO_VMA_SEL_PT_SHIFT)  /**< CFG ldo vma sel pt bitmask - 32K xtal. */

/* SMPS field definitions. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_EN_MASK               (0x1)              /**< En mask - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_EN_SHIFT(_x_)         (((_x_) * 3) + 0)  /**< En shift - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_EN_BITMASK(_x_)       (QAPI_MTP_SMPS_CLK_DIVIDER_EN_MASK << QAPI_MTP_SMPS_CLK_DIVIDER_EN_SHIFT(_bin_))  /**< En bitmask - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_MASK              (0x3)              /**< Val mask - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_16_KHZ_VALUE      (0x0)              /**< Val 16 KHz - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_8_KHZ_VALUE       (0x1)              /**< Val 8 KHz - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_4_KHZ_VALUE       (0x2)              /**< Val 4 KHz - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_2_KHZ_VALUE       (0x3)              /**< Val 2 KHz - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_SHIFT(_x_)        (((_x_) * 3) + 1)  /**< Val shift - SMPS clk.divider. */
#define QAPI_MTP_SMPS_CLK_DIVIDER_VAL_BITMASK(_x_)      (QAPI_MTP_SMPS_CLK_DIVIDER_VAL_MASK << QAPI_MTP_SMPS_CLK_DIVIDER_VAL0_SHIFT(_bin_))  /**< Val bitmask - SMPS clk.divider. */

/* TS Field definitions. */
#define QAPI_MTP_TS_GRADIENT_QUAD_SHIFT                 (0)       /**< Gradient quad shift - TS. */
#define QAPI_MTP_TS_GRADIENT_QUAD_MASK                  (0x0FFF)  /**< Gradient quad mask - TS. */
#define QAPI_MTP_TS_GRADIENT_QUAD_BITMASK               (QAPI_MTP_TS_GRADIENT_QUAD_MASK << QAPI_MTP_TS_GRADIENT_QUAD_SHIFT)  /**< Gradient quad bitmask - TS. */
#define QAPI_MTP_TS_TRIM1_DEFAULT_SHIFT                 (12)      /**< Trim1 default shift - TS. */
#define QAPI_MTP_TS_TRIM1_DEFAULT_MASK                  (0x000F)  /**< Trim1 default mask - TS. */
#define QAPI_MTP_TS_TRIM1_DEFAULT_BITMASK               (QAPI_MTP_TS_TRIM1_DEFAULT_MASK << QAPI_MTP_TS_TRIM1_DEFAULT_SHIFT)  /**< Trim1 default bitmask - TS. */

/* OTP Fields. These fields can be accessed using the APIs in qapi_fuse.h. Note
   these APIs require 32-bit alignment. */
/* OEM MRC HASH. */
#define QAPI_OTP_OEM_MRC_HASH_ADDRESS                   (0x500408F8)  /**< OEM mrc hash address - OTP. */
#define QAPI_OTP_OEM_MRC_HASH_SIZE                      (64)          /**< OEM mrc hash size - OTP. */

/* Debug Disable Vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_ADDRESS           (0x50040938)  /**< Address - Debug disable vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_SIZE              (2)           /**< Size - Debug disable vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_MASK              (0xFFFF)      /**< Mask - Debug disable vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_SHIFT             (0)           /**< Shift - Debug disable vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_BITMASK           (QAPI_OTP_DEBUG_DISABLE_VECTOR_MASK << QAPI_OTP_DEBUG_DISABLE_VECTOR_SHIFT)  /**< Bitmask - Debug disable vector. */
#define QAPI_OTP_DEBUG_DISABLE_VECTOR_WDOG_BITE_SOC_RESET_ENABLE_BITMASK      (1 << 12)  /**< Wdog bit soc reset enable bitmask - Debug disable vector. */

/* OEM ID. */
#define QAPI_OTP_OEM_ID_ADDRESS                         (0x50040938)  /**< Address - OTP OEM id. */
#define QAPI_OTP_OEM_ID_SIZE                            (2)           /**< Size - OTP OEM id. */
#define QAPI_OTP_OEM_ID_MASK                            (0xFFFF)      /**< Mask - OTP OEM id. */
#define QAPI_OTP_OEM_ID_SHIFT                           (16)          /**< Shift - OTP OEM id. */
#define QAPI_OTP_OEM_ID_BITMASK                         (QAPI_OTP_OEM_ID_MASK << QAPI_OTP_OEM_ID_SHIFT)  /**< Bitmask - OTP OEM id. */

/* OEM Product ID (read only). */
#define QAPI_OTP_OEM_PRODUCT_ID_ADDRESS                 (0x5004093C)  /**< Address - OTP OEM product id. */
#define QAPI_OTP_OEM_PRODUCT_ID_SIZE                    (2)           /**< Size - OTP OEM product id. */
#define QAPI_OTP_OEM_PRODUCT_ID_MASK                    (0xFFFF)      /**< Mask - OTP OEM product id. */
#define QAPI_OTP_OEM_PRODUCT_ID_SHIFT                   (16)          /**< Shift - OTP OEM product id. */
#define QAPI_OTP_OEM_PRODUCT_ID_BITMASK                 (QAPI_OTP_OEM_PRODUCT_ID_MASK << QAPI_OTP_OEM_PRODUCT_ID_SHIFT)  /**< Bitmask - OTP OEM product id. */

/* Chip Unique ID (read only). */
#define QAPI_OTP_CHIP_UNIQUE_ID_ADDRESS                 (0x50040940)  /**< Address - OTP chip unique id. */
#define QAPI_OTP_CHIP_UNIQUE_ID_SIZE                    (8)           /**< Size - OTP chip unique id. */

/* OEM Security Policy. */
#define QAPI_OTP_OEM_SECURITY_POLICY_ADDRESS            (0x5004093C)  /**< Address - OTP OEM security policy. */
#define QAPI_OTP_OEM_SECURITY_POLICY_SIZE               (1)           /**< Size - OTP OEM security policy. */
#define QAPI_OTP_OEM_SECURITY_POLICY_MASK               (0xFF)        /**< Mask - OTP OEM security policy. */
#define QAPI_OTP_OEM_SECURITY_POLICY_SHIFT              (16)          /**< Shift - OTP OEM security policy. */
#define QAPI_OTP_OEM_SECURITY_POLICY_BITMASK            (QAPI_OTP_OEM_SECURITY_POLICY_MASK << QAPI_OTP_OEM_SECURITY_POLICY_SHIFT)  /**< Bitmask - OTP OEM security policy. */

/* OEM Product Seed (write only). */
#define QAPI_OTP_OEM_PRODUCT_SEED_ADDRESS               (0x50040988)  /**< Address - OTP OEM product seed. */
#define QAPI_OTP_OEM_PRODUCT_SEED_SIZE                  (16)          /**< Size - OTP OEM product seed. */

/* OEM Batch Secret (write only. */
#define QAPI_OTP_OEM_BATCH_SECRET_ADDRESS               (0x50040998)  /**< Address - OTP OEM batch secret. */
#define QAPI_OTP_OEM_BATCH_SECRET_SIZE                  (16)          /**< Size - OTP OEM batch secret. */

/* OEM Life Cycle State. */
#define QAPI_OTP_OEM_LIFE_CYCLE_STATE_ADDRESS           (0x500409A8)  /**< Address - OTP OEM life cycle state. */
#define QAPI_OTP_OEM_LIFE_CYCLE_STATE_SIZE              (1)           /**< Size - OTP OEM life cycle state. */
#define QAPI_OTP_OEM_LIFE_CYCLE_STATE_MASK              (0xFF)        /**< Mask - OTP OEM life cycle state. */
#define QAPI_OTP_OEM_LIFE_CYCLE_STATE_SHIFT             (0)           /**< Shift - OTP OEM life cycle state. */
#define QAPI_OTP_OEM_LIFE_CYCLE_STATE_BITMASK           (QAPI_OTP_OEM_LIFE_CYCLE_STATE_MASK << QAPI_OTP_OEM_LIFE_CYCLE_STATE_SHIFT)  /**< Bitmask - OTP OEM life cycle state. */

/* BD_ADDR stored in BTSS MTP. */
#define QAPI_BTSS_MTP_BD_ADDR_ADDRESS                   (0x50040AB8)  /**< Address - BTSS MTP BD address. */
#define QAPI_BTSS_MTP_BD_ADDR_SIZE                      (6)           /**< Size - BTSS MTP BD address. */
#define QAPI_BTSS_MTP_BD_ADDR_OFFSET                    (0)           /**< Offset - BTSS MTP BD address. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Structure representing the APSS RO MTP region. */
typedef struct qapi_MTP_APSS_RO_s
{
   uint16_t AuxCtrl0Set0;                  /**< AuxCtrl0Set0. */
   uint16_t AuxCtrl0Set1;                  /**< AuxCtrl0Set1. */
   uint16_t AuxCtrl1Set0_Ctrl5Set0;        /**< AuxCtrl1Set0 and Ctrl5Set0. */
   uint16_t AuxCtrl1Set1_Ctrl5Set1;        /**< AuxCtrl1Set1 and Ctrl5Set1. */

   uint16_t AuxCtrl2;                      /**< AuxCtrl2. */
   uint16_t AuxDrv;                        /**< AuxDrv. */
   uint16_t AuxCtrl6_Ctrl7;                /**< AuxCtrl6 and Ctrl7. */
   uint16_t AuxCtrl8;                      /**< AuxCtrl8. */

   uint32_t AuxDrvCtrl_Ctrl9;              /**< AuxDrvCtrl and Ctrl9. */
   uint32_t AuxGhmiehr_TmuxCtrl0;          /**< AuxGhmiehr and TmuxCtrl0. */

   uint16_t BistAdcLow;                    /**< BistAdcLow. */
   uint16_t BistAdcHigh;                   /**< BistAdcHigh. */
   uint16_t BistMux10k;                    /**< BistMux10k. */
   uint16_t BistMux100k;                   /**< BistMux100k. */

   uint32_t SmpsClkDiv;                    /**< SmpsClkDiv. */
   uint8_t  SmpsSelTon[3];                 /**< SmpsSelTon[3]. */
   uint8_t  LdoDigOffset;                  /**< LdoDigOffset. */

   uint16_t TsCalTemperature;              /**< TsCalTemperature. */
   uint16_t TsGradient;                    /**< TsGradient. */
   uint16_t TsGradientQuad_Trim1Default;   /**< TsGradientQuad and Trim1Default. */
   uint16_t TxTrim0Default;                /**< TxTrim0Default. */

   uint16_t VbatLoadCell1;                 /**< VbatLoadCell1. */
   uint16_t VbatLoadCell2;                 /**< VbatLoadCell2. */
   uint16_t Xtal32kItFac;                  /**< Xtal32kItFac. */
   uint8_t  Xtal32kTemp[2];                /**< Xtal32kTemp[2]. */

   uint16_t BistAdc0v6Ref;                 /**< BistAdc0v6Ref. */
   uint8_t  VbatSenseRatio;                /**< VbatSenseRatio. */
} qapi_MTP_APSS_RO_t;

/** Structure representing the APSS RW MTP region. */
typedef struct qapi_MTP_APSS_RW_s
{
   uint8_t  BdAddr[6];                     /**< BdAddr[6]. */
   uint16_t Xtal32kCfg_LdoVmaSelPt;        /**< Xtal32kCfg and LdoVmaSelPt. */
   uint16_t AuxCtrl3;                      /**< AuxCtrl3. */
   uint16_t AuxDrvT1;                      /**< AuxDrvT1. */
   uint16_t AuxCtrl4Set0;                  /**< AuxCtrl4Set0. */
   uint16_t AuxCtrl4Set1;                  /**< AuxCtrl4Set1. */
   uint16_t AuxDrvT3;                      /**< AuxDrvT3. */
   uint16_t AuxDrvT4;                      /**< AuxDrvT4. */
   uint16_t GpioCfg[26];                   /**< GpioCfg[26]. */
   uint32_t GpioOe;                        /**< GpioOe. */
   uint32_t GpioOut;                       /**< GpioOut. */
   uint8_t  Xtal32kDelay;                  /**< Xtal32kDelay. */
   int8_t   Xtal32kCycleCountTemperature;  /**< Xtal32kCycleCountTemperature. */
   uint16_t Xtal32kCycleCount;             /**< Xtal32kCycleCount. */
   uint32_t _reserved[3];                  /**< _reserved[3]. */
   uint32_t OEM_Data[8];                   /**< OEM_Data[8]. */
} qapi_MTP_APSS_RW_t;

/* APSS MTP structure pointer.   */
#define QAPI_MTP_APSS_RO_PTR           ((const qapi_MTP_APSS_RO_t *)QAPI_MTP_APSS_RO_START_ADDRESS)  /**< APSS MTP read only start address pointer structure. */
#define QAPI_MTP_APSS_RW_PTR           ((const qapi_MTP_APSS_RW_t *)QAPI_MTP_APSS_RW_START_ADDRESS)  /**< APSS MTP read/write start address pointer structure. */

/** @} */ /* end_addtogroup qapi_platform_mtp */

#endif
