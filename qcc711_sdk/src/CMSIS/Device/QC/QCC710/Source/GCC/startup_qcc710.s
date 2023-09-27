/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

/**************************************************************************//**
 * @file     startup_qcc710.S
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

                .syntax  unified
                .arch    armv7-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*      Top of Stack */
                .long    Reset_Handler                      /*      Reset Handler */
                .long    NMI_Handler                        /* -14  NMI Handler */
                .long    HardFault_Handler                  /* -13  Hard Fault Handler */
                .long    MemManage_Handler                  /* -12  MPU Fault Handler */
                .long    BusFault_Handler                   /* -11  Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10  Usage Fault Handler */
                .long    0                                  /*      Reserved */
                .long    0                                  /*      Reserved */
                .long    0                                  /*      Reserved */
                .long    0                                  /*      Reserved */
                .long    SVC_Handler                        /*  -5  SVCall Handler */
                .long    DebugMon_Handler                   /*  -4  Debug Monitor Handler */
                .long    0                                  /*      Reserved */
                .long    PendSV_Handler                     /*  -2  PendSV Handler */
                .long    SysTick_Handler                    /*  -1  SysTick Handler */

                /* Interrupts */
                .long    AON_IntHandler                     /*   0  AON Module Interrupt Handler */
                .long    TME_Lite_IntHandler                /*   1  TME-Lite Interrupt Handler */
                .long    BTSS_IPC_IntHandler                /*   2  BTSS IPC Interrupt Handler */
                .long    0                                  /*      Reserved */
                .long    NVM_Error_IntHandler               /*   4  NVM Error Interrupt Handler */
                .long    NVM_IntHandler                     /*   5  NVM Write Complete Interrupt Handler */
                .long    0                                  /*      Reserved */
                .long    GPIO_IntHandler                    /*   7  GPIO Interrupt Handler */
                .long    0                                  /*      Reserved */
                .long    GTMR_IntHandler                    /*   9  Global Timer Interrupt Handler */
                .long    WDogBark_IntHandler                /*   10 Watch-Dog Bark Interrupt Handler */
                .long    0                                  /*      Reserved */
                .long    QSPI_IntHandler                    /*   12 QSPI Interrupt Handler */
                .long    0                                  /*      Reserved */
                .long    FTC0_IntHandler                    /*   14 FTC 0 Interrupt Handler */
                .long    FTC1_IntHandler                    /*   15 FTC 1 Interrupt Handler */
                .long    FTC2_IntHandler                    /*   16 FTC 2 Interrupt Handler */
                .long    FTC3_IntHandler                    /*   17 FTC 3 Interrupt Handler */
                .long    SE0_IntHandler                     /*   18 SE Interrupt 0 Handler */
                .long    SE1_IntHandler                     /*   19 SE Interrupt 1 Handler */
                .long    SE2_IntHandler                     /*   20 SE Interrupt 2 Handler */
                .long    SE3_IntHandler                     /*   21 SE Interrupt 3 Handler */
                .long    APPI2C_IntHandler                  /*   22 APPI2C Interrupt Handler */
__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
Reset_Handler:
                bl       SystemInit

/* .data initialization */
                ldr      r1, =__etext
                ldr      r2, =__data_start__
                ldr      r3, =__data_size__

.L_loop0:
                subs     r3, #4
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0

/* .bss initialization */
                ldr      r1, =__bss_start__
                ldr      r2, =__bss_size__
                movs     r0, 0

.L_loop2:
                subs     r2, #4
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2

/* Jump to main */
                bl       main

                .size    Reset_Handler, . - Reset_Handler


                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
Default_Handler:
                b        .
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  AON_IntHandler
                Set_Default_Handler  TME_Lite_IntHandler
                Set_Default_Handler  BTSS_IPC_IntHandler
                Set_Default_Handler  NVM_Error_IntHandler
                Set_Default_Handler  NVM_IntHandler
                Set_Default_Handler  GPIO_IntHandler
                Set_Default_Handler  GTMR_IntHandler
                Set_Default_Handler  WDogBark_IntHandler
                Set_Default_Handler  QSPI_IntHandler
                Set_Default_Handler  FTC0_IntHandler
                Set_Default_Handler  FTC1_IntHandler
                Set_Default_Handler  FTC2_IntHandler
                Set_Default_Handler  FTC3_IntHandler
                Set_Default_Handler  SE0_IntHandler
                Set_Default_Handler  SE1_IntHandler
                Set_Default_Handler  SE2_IntHandler
                Set_Default_Handler  SE3_IntHandler
                Set_Default_Handler  APPI2C_IntHandler

                .end
