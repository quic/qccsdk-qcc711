; Copyright (c) 2021 Qualcomm Technologies, Inc.
; All Rights Reserved.
; Confidential and Proprietary - Qualcomm Technologies, Inc.
; NOT A CONTRIBUTION

;---------------------------------
;
; Copyright (c) 2008 IAR Systems
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;
; $Revision: 117855 $
;
; Functions accessed by the debugger to perform a flash download.
; All public symbols and the function FlashBreak() are looked up and called by the debugger.
;
;---------------------------------

#define _CORTEX_  ((__CORE__ == __ARM6M__) || (__CORE__ == __ARM6SM__) || (__CORE__ == __ARM7M__) \
|| (__CORE__ == __ARM7EM__) || (__CORE__ == __ARM8M__) || (__CORE__ == __ARM8M_BASELINE__)        \
|| (__CORE__ == __ARM8M_MAINLINE__) || (__CORE__ == __ARM8EM_MAINLINE__))

        PUBLIC FlashInitEntry
        PUBLIC FlashWriteEntry
        PUBLIC FlashEraseWriteEntry
        PUBLIC FlashChecksumEntry
        PUBLIC FlashSignoffEntry
        PUBLIC FlashBufferStart
        PUBLIC FlashBufferEnd

        EXTERN FlashBreak
        EXTERN Fl2FlashInitEntry
        EXTERN Fl2FlashWriteEntry
        EXTERN Fl2FlashEraseWriteEntry
        EXTERN Fl2FlashChecksumEntry
        EXTERN Fl2FlashSignoffEntry

        SECTION CSTACK:DATA:NOROOT(3)


;---------------------------------
;
; FlashInitEntry()
; Debugger interface function
;
;---------------------------------
        SECTION .text:CODE:ROOT(2)
#if !_CORTEX_
        ARM
#else
        THUMB
#endif

FlashInitEntry:
#if !_CORTEX_
        ;; Set up the normal stack pointer.
        LDR     sp, =SFE(CSTACK)        ; End of CSTACK
#endif
        BL       Fl2FlashInitEntry
        BL       FlashBreak


;---------------------------------
;
; FlashWriteEntry()
; Debugger interface function
;
;---------------------------------
        SECTION .text:CODE:ROOT(2)
#if !_CORTEX_
        ARM
#else
        THUMB
#endif

FlashWriteEntry:
        BL       Fl2FlashWriteEntry
        BL       FlashBreak


;---------------------------------
;
; FlashEraseWriteEntry
; Debugger interface function
;
;---------------------------------
        SECTION .text:CODE:ROOT(2)
#if !_CORTEX_
        ARM
#else
        THUMB
#endif

FlashEraseWriteEntry:
        BL       Fl2FlashEraseWriteEntry
        BL       FlashBreak


;---------------------------------
;
; FlashChecksumEntry
; Debugger interface function
;
;---------------------------------
        SECTION .text:CODE:NOROOT(2)
#if !_CORTEX_
        ARM
#else
        THUMB
#endif

FlashChecksumEntry:
        BL       Fl2FlashChecksumEntry
        BL       FlashBreak


;---------------------------------
;
; FlashSignoffEntry
; Debugger interface function
;
;---------------------------------
        SECTION .text:CODE:NOROOT(2)
#if !_CORTEX_
        ARM
#else
        THUMB
#endif

FlashSignoffEntry:
        BL       Fl2FlashSignoffEntry
        BL       FlashBreak


;---------------------------------
;
; Flash buffer and Cortex stack
;
;---------------------------------
        SECTION LOWEND:DATA(8)
        DATA
FlashBufferStart:

        SECTION HIGHSTART:DATA
        DATA
FlashBufferEnd:


#if _CORTEX_
        PUBLIC __vector_table

        SECTION .intvec:CODE:ROOT(2)
        DATA

__vector_table:
        DC32    SFE(CSTACK)
        DC32    FlashInitEntry
        DC32    NMI_Handler
        DC32    HardFault_Handler
        DC32    MemManage_Handler
        DC32    BusFault_Handler
        DC32    UsageFault_Handler
        DC32    0
        DC32    0
        DC32    0
        DC32    0
        DC32    SVC_Handler
        DC32    DebugMon_Handler
        DC32    0
        DC32    PendSV_Handler
        DC32    SysTick_Handler

        ; External Interrupts
        DC32    AON_IntHandler
        DC32    TME_Lite_IntHandler
        DC32    BTSS_IPC_IntHandler
        DC32    0
        DC32    NVM_Error_IntHandler
        DC32    NVM_IntHandler
        DC32    0
        DC32    GPIO_IntHandler
        DC32    0
        DC32    GTMR_IntHandler
        DC32    WDogBark_IntHandler
        DC32    0
        DC32    QSPI_IntHandler
        DC32    0
        DC32    FTC0_IntHandler
        DC32    FTC1_IntHandler
        DC32    FTC2_IntHandler
        DC32    FTC3_IntHandler
        DC32    SE0_IntHandler
        DC32    SE1_IntHandler
        DC32    SE2_IntHandler
        DC32    SE3_IntHandler
        DC32    APPI2C_IntHandler


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

#endif

        END
