/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qspi_map.h
   @brief qspi memory map Services Interface definition.

   This module provide QSPI memory map APIs, types, and definitions.
*/
 
#ifndef __QSPI_MAP_H__
#define __QSPI_MAP_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup peripherals_qspi_map
@{
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Structure representing QSPI memory mapping configurations.
*/
typedef struct QSPI_MAP_MemMapConfig_s
{
    uint8_t CmdMode;       /**< Flash read command mode, 1: SDR_SINGLE, 5: DDR_SINGLE, 7: DDR_QUAD,
                                other values are invalid. */
    uint8_t AddrMode;      /**< Flash read address mode, 1: SDR_SINGLE, 5: DDR_SINGLE, 7: DDR_QUAD,
                                other values are invalid. */
    uint8_t DataMode;      /**< Flash read data mode, 1: SDR_SINGLE, 5: DDR_SINGLE, 7: DDR_QUAD,
                                other values are invalid. */
    uint8_t ReadOpcode;    /**< Read opcode. */
    uint8_t AddrBytes;     /**< Flash address bytes, 3 bytes or 4 bytes. */
    uint8_t DummyCycles;   /**< Flash read dummy cycles. */
} QSPI_MAP_MemMapConfig_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Map part of flash memory to a specific part of system memory.

   This function allows QUP DMA to directly read flash contents from specific
   system address which is mapped with flash memory.

   To use this feature, the flash read mode should be single mode or quad
   mode. Dual read mode is not supported.
   It allows at most 3 different parts of flash memory to be mapped, while
   each part can support up to 16M bytes. The different parts of flash memory
   can not be overlaped with each other on block.

   @param[in]  Address     Flash start address to be mapped.
   @param[in]  Size        The size of flash memory to be mapped.
   @param[in]  Config      Memory map module configurations
   @param[out] MapHandle   The memory map handle.

   @return QAPI_OK if mapping was successful, or a negative value if there
           was an error.
*/
qapi_Status_t QSPI_MAP_MemoryMap(uint32_t Address, uint32_t Size, QSPI_MAP_MemMapConfig_t *Config, void **MapHandle);

/**
   @brief Unmap the part of flash memory from system memory.

   @param[in] MapHandle  The memory map handle.

   @return QAPI_OK if unmapping was successful, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_MemoryUnmap(void *MapHandle);

/**
   @brief Get the mapped system address of a specific flash address.

   @param[in]  Address        Flash physical address.
   @param[out] MappedAddress  The mapped system address.

   @return QAPI_OK if getting address successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_GetMappedAddress(uint32_t Address, uint32_t *MappedAddress);

/**
   @brief Set flash program/erase ongoing state.

   @param[in] Ongoing  true: program/earse is ongoing, false: not ongoing.

   @return QAPI_OK if setting was successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_SetProgramEraseState(qbool_t Ongoing);

/**
   @brief Configure flash suspend/resume.

   @param[in] SuspendDelay   Delay needed for suspend in-progress operation.
   @param[in] SuspendOpcode  Suspend opcode.
   @param[in] ResumeDelay    Delay needed after sending resume opcode.
   @param[in] ResumeOpcode   Resume opcode.

   @return QAPI_OK if configuration was successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_ConfigSuspendResume(uint16_t SuspendDelay, uint8_t SuspendOpcode, uint16_t ResumeDelay, uint8_t ResumeOpcode);

/** @} */

#endif

