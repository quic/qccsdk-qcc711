;/*
; * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
; * All Rights Reserved.
; * Confidential and Proprietary - Qualcomm Technologies, Inc.
; * NOT A CONTRIBUTION
; */

;/**************************************************************************//**
; * @file     startup_qcc710.s
; * @brief    CMSIS Cortex-M# Core Device Startup File for
; *           Device QCC710
; * @version  V1.0.0
; * @date     09. July 2018
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

                MODULE   ?cstartup

                ;; Forward declaration of sections.
                SECTION  CSTACK:DATA:NOROOT(3)

                SECTION  .intvec:CODE:NOROOT(2)

                EXTERN   __iar_program_start
                EXTERN   SystemInit
                PUBLIC   __vector_table
                PUBLIC   __vector_table_0x1c
                PUBLIC   __Vectors
                PUBLIC   __Vectors_End
                PUBLIC   __Vectors_Size

                DATA

__vector_table
                DCD      sfe(CSTACK)                         ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      MemManage_Handler                   ; -12 MPU Fault Handler
                DCD      BusFault_Handler                    ; -11 Bus Fault Handler
                DCD      UsageFault_Handler                  ; -10 Usage Fault Handler
__vector_table_0x1c
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      DebugMon_Handler                    ;  -4 Debug Monitor Handler
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

        ; External Interrupts
                DCD      AON_IntHandler                      ;   0  AON Module Interrupt Handler
                DCD      TME_Lite_IntHandler                 ;   1  TME- Lite Interrupt Handler
                DCD      BTSS_IPC_IntHandler                 ;   2  BTSS  IPC Interrupt Handler
                DCD      0                                   ;      Reserved
                DCD      NVM_Error_IntHandler                ;   4  NVM Error Interrupt Handler
                DCD      NVM_IntHandler                      ;   5  NVM Write Complete Interrupt Handler
                DCD      0                                   ;      Reserved
                DCD      GPIO_IntHandler                     ;   7  GPIO Interrupt Handler
                DCD      0                                   ;      Reserved
                DCD      GTMR_IntHandler                     ;   9  Global Timer Interrupt Handler
                DCD      WDogBark_IntHandler                 ;   10 Watch-Dog Bark Interrupt Handler
                DCD      0                                   ;      Reserved
                DCD      QSPI_IntHandler                     ;   12 QSPI Interrupt Handler
                DCD      0                                   ;      Reserved
                DCD      FTC0_IntHandler                     ;   14 FTC 0 Interrupt Handle
                DCD      FTC1_IntHandler                     ;   15 FTC 1 Interrupt Handler
                DCD      FTC2_IntHandler                     ;   16 FTC 2 Interrupt Handler
                DCD      FTC3_IntHandler                     ;   17 FTC 3 Interrupt Handler
                DCD      SE0_IntHandler                      ;   18 SE Interrupt 0 Handler
                DCD      SE1_IntHandler                      ;   19 SE Interrupt 1 Handler
                DCD      SE2_IntHandler                      ;   20 SE Interrupt 2 Handler
                DCD      SE3_IntHandler                      ;   21 SE Interrupt 3 Handler
                DCD      APPI2C_IntHandler                   ;   22 APPI2C Interrupt Handler
__Vectors_End

__Vectors       EQU      __vector_table
__Vectors_Size  EQU      __Vectors_End - __Vectors


                THUMB

; Reset Handler

                PUBWEAK  Reset_Handler
                SECTION  .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__iar_program_start
                BX       R0


                PUBWEAK NMI_Handler
                PUBWEAK HardFault_Handler
                PUBWEAK MemManage_Handler
                PUBWEAK BusFault_Handler
                PUBWEAK UsageFault_Handler
                PUBWEAK SVC_Handler
                PUBWEAK DebugMon_Handler
                PUBWEAK PendSV_Handler
                PUBWEAK SysTick_Handler

                PUBWEAK AON_IntHandler
                PUBWEAK TME_Lite_IntHandler
                PUBWEAK BTSS_IPC_IntHandler
                PUBWEAK NVM_Error_IntHandler
                PUBWEAK NVM_IntHandler
                PUBWEAK GPIO_IntHandler
                PUBWEAK GTMR_IntHandler
                PUBWEAK WDogBark_IntHandler
                PUBWEAK QSPI_IntHandler
                PUBWEAK FTC0_IntHandler
                PUBWEAK FTC1_IntHandler
                PUBWEAK FTC2_IntHandler
                PUBWEAK FTC3_IntHandler
                PUBWEAK SE0_IntHandler
                PUBWEAK SE1_IntHandler
                PUBWEAK SE2_IntHandler
                PUBWEAK SE3_IntHandler
                PUBWEAK APPI2C_IntHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler

AON_IntHandler
TME_Lite_IntHandler
BTSS_IPC_IntHandler
NVM_Error_IntHandler
NVM_IntHandler
GPIO_IntHandler
GTMR_IntHandler
WDogBark_IntHandler
QSPI_IntHandler
FTC0_IntHandler
FTC1_IntHandler
FTC2_IntHandler
FTC3_IntHandler
SE0_IntHandler
SE1_IntHandler
SE2_IntHandler
SE3_IntHandler
APPI2C_IntHandler
Default_Handler
                B        .


                END
