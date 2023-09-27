/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * NOT A CONTRIBUTION
 */

/******************************************************************************
 * @file     gcc_arm.ld
 * @brief    GNU Linker Script for Cortex-M based device
 * @version  V2.0.0
 * @date     21. May 2019
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

/*
;-------- <<< Use Configuration Wizard in Context Menu >>> -------------------
*/

/*--------------------- ROM Configuration ----------------------------------
; <h> ROM Configuration
;   <o0> ROM Base Address <0x0-0xFFFFFFFF:8>
;   <o1> ROM Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
 -----------------------------------------------------------------------------*/
__ROM_BASE = 0x10210000;
__ROM_SIZE = 0x00068000;

/*--------------------- Embedded RAM Configuration ---------------------------
; <h> RAM Configuration
;   <o0> RAM Base Address    <0x0-0xFFFFFFFF:8>
;   <o1> RAM Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
 -----------------------------------------------------------------------------*/
__RAM_BASE = 0x20010000;
__RAM_SIZE = 0x00010000;
__RETN_RAM_BASE = __RAM_BASE;
__RETN_RAM_SIZE = 0x00004000;
__IPC_INFO_RAM_SIZE = 0x00000010;
__IPC_APSS_INFO_RAM_BASE = 0x2000FFF0;
__IPC_BTSS_INFO_RAM_BASE = 0x2001FFF0;
__IPC_SHARED_RAM_SIZE = 0x00000800;
__IPC_SHARED_RAM_BASE = __RAM_BASE + __RAM_SIZE - __IPC_SHARED_RAM_SIZE;
__IPC_RING_RAM_SIZE = 0x00000100;
__IPC_MESSAGE_RAM_SIZE = __IPC_SHARED_RAM_SIZE - __IPC_RING_RAM_SIZE;
__IPC_MESSAGE_RAM_BASE = __IPC_SHARED_RAM_BASE;
__MAIN_RAM_BASE = __RETN_RAM_BASE + __RETN_RAM_SIZE;
__MAIN_RAM_SIZE = __RAM_SIZE - __RETN_RAM_SIZE - __IPC_SHARED_RAM_SIZE;

/*--------------------- Stack / Heap Configuration ---------------------------
; <h> Stack / Heap Configuration
;   <o0> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;   <o1> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
 -----------------------------------------------------------------------------*/
__STACK_SIZE = 0x00000600;
__HEAP_SIZE  = 0x00000C00;
__MAIN_HEAP_SIZE  = 0x00002400;

/*
;-------------------- <<< end of configuration section >>> --------------------
*/

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions ROM and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __RetnBssStart
 *   __RetnBssEnd
 *   __RetnHeapStart
 *   __RetnHeapEnd
 *   __MainHeapStart
 *   __MainHeapEnd
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)

SECTIONS
{
   .text __ROM_BASE :
   {
      __RomStart = .;
      __VectorTableStart = .;
      KEEP(*(.vectors))
      __VectorTableEnd = .;
      *(.text*)

      KEEP(*(.init))
      KEEP(*(.fini))

      /* .ctors */
      *crtbegin.o(.ctors)
      *crtbegin?.o(.ctors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
      *(SORT(.ctors.*))
      *(.ctors)

      /* .dtors */
      *crtbegin.o(.dtors)
      *crtbegin?.o(.dtors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
      *(SORT(.dtors.*))
      *(.dtors)

      *(.rodata*)

      KEEP(*(.eh_frame*))
   }

   .ARM.extab :
   {
      *(.ARM.extab* .gnu.linkonce.armextab.*)
   }

   __exidx_start = .;
   .ARM.exidx :
   {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
   }
   __exidx_end = .;

   /* Location counter can end up 2byte aligned with narrow Thumb code but
      __etext is assumed by startup code to be the LMA of a section in RAM
      which must be 4byte aligned */
   __rtext = ALIGN (4);

    __RomEnd = .;

   .vtor __RETN_RAM_BASE : AT(__RETN_RAM_BASE)
   {
      __RetnRAMStart = .;
      . = ALIGN(128);
      . = . + (__VectorTableEnd - __VectorTableStart);
   }

   .text.retain : AT(__rtext)
   {
      . = ALIGN(4);
      __RetnTextStart = .;
      *(.retained.text)
      . = ALIGN(4);
      __RetnTextEnd = .;
   }
   __etext = __rtext + __RetnTextEnd - __RetnTextStart;

   // __bss_retain_load = .;
   .bss.retain : AT(.)
   {
      . = ALIGN(4);
      __RetnBssStart = .;
      *(.bss.retain)
      . = ALIGN(4);
      __RetnBssEnd = .;
   }

   .retain_heap :
   {
      . = ALIGN(4);
      __RetnHeapStart = .;
      PROVIDE(end = .);
      . = . + __HEAP_SIZE;
      . = ALIGN(4);
      __RetnHeapEnd = .;
      __RetnRAMEnd = .;
   }

   .data __MAIN_RAM_BASE : AT(__etext)
   {
      . = ALIGN(4);
      __data_start__ = .;
      *(vtable)
      *(.data)
      *(.data.*)

      . = ALIGN(4);
      /* preinit data */
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP(*(.preinit_array))
      PROVIDE_HIDDEN (__preinit_array_end = .);

      . = ALIGN(4);
      /* init data */
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP(*(SORT(.init_array.*)))
      KEEP(*(.init_array))
      PROVIDE_HIDDEN (__init_array_end = .);


      . = ALIGN(4);
      /* finit data */
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP(*(SORT(.fini_array.*)))
      KEEP(*(.fini_array))
      PROVIDE_HIDDEN (__fini_array_end = .);

      KEEP(*(.jcr*))
      . = ALIGN(4);
      /* All data end */
      __data_end__ = .;
   }
   PROVIDE(__data_size__ = (__data_end__ - __data_start__));

   .bss : AT(.)
   {
      . = ALIGN(4);
      __bss_start__ = .;
      *(.bss)
      *(.bss.*)
      *(COMMON)
      . = ALIGN(4);
      __bss_end__ = .;
   }
   PROVIDE(__bss_size__ = (__bss_end__ - __bss_start__));

   .main_heap :
   {
    . = ALIGN(4);
      __end__ = .;
      __MainHeapStart = .;
      PROVIDE(end = .);
      . = . + __MAIN_HEAP_SIZE;
      . = ALIGN(4);
      __MainHeapEnd = .;
      __HeapLimit = .;
   }

   .stack :
   {
    . = __RAM_BASE + __RAM_SIZE - __STACK_SIZE - __IPC_SHARED_RAM_SIZE;
    . = ALIGN(4);
    __StackLimit = .;
    . = . + __STACK_SIZE;
    . = ALIGN(4);
    __StackTop = .;
   }
   PROVIDE(__stack = __StackTop);

   .shared __IPC_MESSAGE_RAM_BASE :
   {
    . = ALIGN(4);
    __IPC_MessageStart = .;
    . = . + __IPC_MESSAGE_RAM_SIZE;
    __IPC_MessageEnd = .;
    __IPC_SharedStart = .;
    . = . + __IPC_RING_RAM_SIZE - __IPC_INFO_RAM_SIZE;
    __IPC_APSS_InfoStart = .;
    . = . + __IPC_INFO_RAM_SIZE;
    . = ALIGN(4);
    __IPC_APSS_InfoEnd = .;
    __IPC_SharedEnd = .;
   }

   PROVIDE(QIPC_TxData = __IPC_BTSS_INFO_RAM_BASE);
   PROVIDE(QIPC_RxData = __IPC_APSS_INFO_RAM_BASE);

   /* Check if retention RAM overflowed. */
   ASSERT(__RetnRAMEnd <= (__RETN_RAM_BASE + __RETN_RAM_SIZE), "region RETN_RAM overflowed")
   /* Check if data + heap + stack exceeds RAM limit */
   ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
   /* Check if .text + .data section exceeds ROM limit */
   ASSERT((__etext + __data_size__) <= (__ROM_BASE + __ROM_SIZE), "region ROM overflowed")
}
