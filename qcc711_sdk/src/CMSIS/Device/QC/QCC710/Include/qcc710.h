/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

/**************************************************************************//**
 * @file     qcc710.h
 * @brief    CMSIS Cortex-M# Core Peripheral Access Layer Header File for
 *           Device QCC710
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef QCC710_H
#define QCC710_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup QC
  * @{
  */


/** @addtogroup QCC710
  * @{
  */


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
/* =======================================  ARM Cortex-M# Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  MemoryManagement_IRQn     = -12,              /*!< -12  Memory Management, MPU mismatch, including Access Violation
                                                          and No Match                                                         */
  BusFault_IRQn             = -11,              /*!< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                          related Fault                                                        */
  UsageFault_IRQn           = -10,              /*!< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
  SVCall_IRQn               =  -5,              /*!< -5   System Service Call via SVC instruction                              */
  DebugMonitor_IRQn         =  -4,              /*!< -4   Debug Monitor                                                        */
  PendSV_IRQn               =  -2,              /*!< -2   Pendable request for system service                                  */
  SysTick_IRQn              =  -1,              /*!< -1   System Tick Timer                                                    */

/* ===========================================  QCC710 Specific Interrupt Numbers  ========================================= */
  Aon_IRQn                  = 0,                 /*!< 0   AON Module Interrupt                                               */
  TME_Lite_IRQn             = 1,                 /*!< 1   TME-Lite Interrupt                                                 */
  BTSS_IPC_IRQn             = 2,                 /*!< 2   BTSS IPC Interrupt                                                 */
  NVM_Error_IRQn            = 4,                 /*!< 4   NVM Error Interrupt                                                */
  Nvm_IRQn                  = 5,                 /*!< 5   NVM Write Complete Interrupt                                       */
  GPIO_IRQn                 = 7,                 /*!< 7   GPIO Interrupt                                                     */
  GTMR_IRQn                 = 9,                 /*!< 9   Global Timer Interrupt                                             */
  WDogBark_IRQn             = 10,                /*!< 10  Watch-Dog Bark Interrupt                                           */
  QSPI_IRQn                 = 12,                /*!< 12  QSPI Interrupt                                                     */
  FTC0_IRQn                 = 14,                /*!< 14  FTC 0 Interrupt                                                    */
  FTC1_IRQn                 = 15,                /*!< 15  FTC 1 Interrupt                                                    */
  FTC2_IRQn                 = 16,                /*!< 16  FTC 2 Interrupt                                                    */
  FTC3_IRQn                 = 17,                /*!< 17  FTC 3 Interrupt                                                    */
  SE0_IRQn                  = 18,                /*!< 18  SE 0 Interrupt                                                     */
  SE1_IRQn                  = 19,                /*!< 19  SE 1 Interrupt                                                     */
  SE2_IRQn                  = 20,                /*!< 20  SE 2 Interrupt                                                     */
  SE3_IRQn                  = 21,                /*!< 21  SE 3 Interrupt                                                     */
  APPI2C_IRQn				= 22,                /*!< 22 APPI2C Interrupt Handler											 */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Arm Cortex-M4 Processor and Core Peripherals  =========================== */
#define __CM3_REV                 0x0201    /*!< Core Revision r2p1 */
/* ToDo: define the correct core features for the QCC710 */
#define __MPU_PRESENT             0         /*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT            1         /*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0         /*!< Set to 1 if FPU is present */
#define __FPU_DP                  0         /*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT          0         /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0         /*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT            0         /*!< Set to 1 if DTCM is present */


/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                         /*!< Arm Cortex-M3 processor and core peripherals */
#include "system_qcc710.h"                    /*!< QCC710 System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

/* =========================================================================================================================== */
/* ================                                            TMR                                            ================ */
/* =========================================================================================================================== */

/*@}*/ /* end of group QCC710_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

/** @} */ /* End of group QCC710 */

/** @} */ /* End of group QC */

#ifdef __cplusplus
}
#endif

#endif  /* QCC710_H */
