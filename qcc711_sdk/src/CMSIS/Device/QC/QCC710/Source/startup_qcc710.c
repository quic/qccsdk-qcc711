/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

/******************************************************************************
 * @file     startup_Device.c
 * @brief    CMSIS-Core(M) Device Startup File for QCC710
 * @version  V2.0.0
 * @date     20. May 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
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

#include "qcc710.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void __NO_RETURN Default_Handler(void);
void __NO_RETURN Reset_Handler  (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void AON_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void TME_Lite_IntHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void BTSS_IPC_IntHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void NVM_Error_IntHandler   (void) __attribute__ ((weak, alias("Default_Handler")));
void NVM_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void GPIO_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void GTMR_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void WDogBark_IntHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void QSPI_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FTC0_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FTC1_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FTC2_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void FTC3_IntHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void SE0_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SE1_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SE2_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SE3_IntHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void APPI2C_IntHandler      (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const pFunc __VECTOR_TABLE[240];
       const pFunc __VECTOR_TABLE[240] __VECTOR_TABLE_ATTRIBUTE = {
  (pFunc)(&__INITIAL_SP),                   /*      Initial Stack Pointer */
  Reset_Handler,                            /*      Reset Handler */
  NMI_Handler,                              /* -14  NMI Handler */
  HardFault_Handler,                        /* -13  Hard Fault Handler */
  MemManage_Handler,                        /* -12  MPU Fault Handler */
  BusFault_Handler,                         /* -11  Bus Fault Handler */
  UsageFault_Handler,                       /* -10  Usage Fault Handler */
  0,                                        /*      Reserved */
  0,                                        /*      Reserved */
  0,                                        /*      Reserved */
  0,                                        /*      Reserved */
  SVC_Handler,                              /*  -5  SVCall Handler */
  DebugMon_Handler,                         /*  -4  Debug Monitor Handler */
  0,                                        /*      Reserved */
  PendSV_Handler,                           /*  -2  PendSV Handler */
  SysTick_Handler,                          /*  -1  SysTick Handler */

  /* Interrupts */
  AON_IntHandler,                           /*   0  AON Module Interrupt Handler */
  TME_Lite_IntHandler,                      /*   1  TME-Lite Interrupt Handler */
  BTSS_IPC_IntHandler,                      /*   2  BTSS IPC Interrupt Handler */
  0,                                        /*      Reserved */
  NVM_Error_IntHandler,                     /*   4  NVM Error Interrupt Handler */
  NVM_IntHandler,                           /*   5  NVM Write Complete Interrupt Handler */
  0,                                        /*      Reserved */
  GPIO_IntHandler,                          /*   7  GPIO Interrupt Handler */
  0,                                        /*      Reserved */
  GTMR_IntHandler,                          /*   9  Global Timer Interrupt Handler */
  WDogBark_IntHandler,                      /*   10 Watch-Dog Bark Interrupt Handler */
  0,                                        /*      Reserved */
  QSPI_IntHandler,                          /*   12 QSPI Interrupt Handler */
  0,                                        /*      Reserved */
  FTC0_IntHandler,                          /*   14 FTC 0 Interrupt Handler */
  FTC1_IntHandler,                          /*   15 FTC 1 Interrupt Handler */
  FTC2_IntHandler,                          /*   16 FTC 2 Interrupt Handler */
  FTC3_IntHandler,                          /*   17 FTC 3 Interrupt Handler */
  SE0_IntHandler,                           /*   18 SE Interrupt 0 Handler */
  SE1_IntHandler,                           /*   19 SE Interrupt 1 Handler */
  SE2_IntHandler,                           /*   20 SE Interrupt 2 Handler */
  SE3_IntHandler,                           /*   21 SE Interrupt 3 Handler */
  APPI2C_IntHandler,                        /*   22 APPI2C Interrupt Handler */
};

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  SystemInit();                             /* CMSIS System Initialization */
  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}
