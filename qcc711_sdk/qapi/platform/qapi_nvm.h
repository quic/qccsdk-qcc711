/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_nvm.h
   @brief NVM related APIs and definitions.

   This module provides NVM related APIs and definitions.
*/

#ifndef __QAPI_NVM_H__
#define __QAPI_NVM_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/** @addtogroup qapi_platform_nvm
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define QAPI_NVM_WRITE_FAILURE               (__QAPI_ERROR(QAPI_MOD_NVM, 1)) /**< NVM error indicating a general write failure. */
#define QAPI_NVM_ACCESS_CONTROL_ERROR        (__QAPI_ERROR(QAPI_MOD_NVM, 2)) /**< NVM error indicating an access control violation. */


/* Definitions for the address ranges of NVM. */
#define QAPI_NVM_APSS_START                  ((void *)0x10210000) /**< Start address of APSS NVM. */
#define QAPI_NVM_APSS_SIZE                   (0x00068000)         /**< Size of the APSS NVM. */
#define QAPI_NVM_APSS_END                    ((void *)0x10277FFF) /**< End address of APSS NVM. */

#define QAPI_NVM_APSS_INFO_START             ((void *)0x50040B00) /**< Starting address of APSS INFO NVM. */
#define QAPI_NVM_APSS_INFO_SIZE              (0x00000100)         /**< Size of the APSS INFO NVM. */
#define QAPI_NVM_APSS_INFO_END               ((void *)0x50040BFF) /**< Ending address of APSS INFO NVM. */

#define QAPI_NVM_BLOCK_SIZE                  (0x00008000)         /**< Size of each NVM block. */
#define QAPI_NVM_BLOCK_OFFSET                (2)                  /**< Offset of the first block of APSS NVM. */
#define QAPI_NVM_BLOCK_COUNT                 (13)                 /**< Number of NVM blocks. */


/* Definition of blocks. */
#define QAPI_NVM_APSS_BLOCK_00_START          ((void *)0x10210000) /**< Start address of APSS NVM block 0. */
#define QAPI_NVM_APSS_BLOCK_00_END            ((void *)0x10217FFF) /**< End address of APSS NVM block 0. */
#define QAPI_NVM_APSS_BLOCK_01_START          ((void *)0x10218000) /**< Start address of APSS NVM block 1. */
#define QAPI_NVM_APSS_BLOCK_01_END            ((void *)0x1021FFFF) /**< End address of APSS NVM block 1. */
#define QAPI_NVM_APSS_BLOCK_02_START          ((void *)0x10220000) /**< Start address of APSS NVM block 2. */
#define QAPI_NVM_APSS_BLOCK_02_END            ((void *)0x10227FFF) /**< End address of APSS NVM block 2. */
#define QAPI_NVM_APSS_BLOCK_03_START          ((void *)0x10228000) /**< Start address of APSS NVM block 3. */
#define QAPI_NVM_APSS_BLOCK_03_END            ((void *)0x1022FFFF) /**< End address of APSS NVM block 3. */
#define QAPI_NVM_APSS_BLOCK_04_START          ((void *)0x10230000) /**< Start address of APSS NVM block 4. */
#define QAPI_NVM_APSS_BLOCK_04_END            ((void *)0x10237FFF) /**< End address of APSS NVM block 4. */
#define QAPI_NVM_APSS_BLOCK_05_START          ((void *)0x10238000) /**< Start address of APSS NVM block 5. */
#define QAPI_NVM_APSS_BLOCK_05_END            ((void *)0x1023FFFF) /**< End address of APSS NVM block 5. */
#define QAPI_NVM_APSS_BLOCK_06_START          ((void *)0x10240000) /**< Start address of APSS NVM block 6. */
#define QAPI_NVM_APSS_BLOCK_06_END            ((void *)0x10247FFF) /**< End address of APSS NVM block 6. */
#define QAPI_NVM_APSS_BLOCK_07_START          ((void *)0x10248000) /**< Start address of APSS NVM block 7. */
#define QAPI_NVM_APSS_BLOCK_07_END            ((void *)0x1024FFFF) /**< End address of APSS NVM block 7. */
#define QAPI_NVM_APSS_BLOCK_08_START          ((void *)0x10250000) /**< Start address of APSS NVM block 8. */
#define QAPI_NVM_APSS_BLOCK_08_END            ((void *)0x10257FFF) /**< End address of APSS NVM block 8. */
#define QAPI_NVM_APSS_BLOCK_09_START          ((void *)0x10258000) /**< Start address of APSS NVM block 9. */
#define QAPI_NVM_APSS_BLOCK_09_END            ((void *)0x1025FFFF) /**< End address of APSS NVM block 9. */
#define QAPI_NVM_APSS_BLOCK_10_START          ((void *)0x10260000) /**< Start address of APSS NVM block 10. */
#define QAPI_NVM_APSS_BLOCK_10_END            ((void *)0x10267FFF) /**< End address of APSS NVM block 10. */
#define QAPI_NVM_APSS_BLOCK_11_START          ((void *)0x10268000) /**< Start address of APSS NVM block 11. */
#define QAPI_NVM_APSS_BLOCK_11_END            ((void *)0x1026FFFF) /**< End address of APSS NVM block 11. */
#define QAPI_NVM_APSS_BLOCK_12_START          ((void *)0x10270000) /**< Start address of APSS NVM block 12. */
#define QAPI_NVM_APSS_BLOCK_12_END            ((void *)0x10277FFF) /**< End address of APSS NVM block 12. */

#define QAPI_NVM_APSS_BLOCKS_BITMASK          (0x7FFC) /**< Bitmask of all APSS NVM blocks. */
#define QAPI_NVM_APSS_BLOCK_00_BITMASK        (0x0004) /**< Bitmask representing APSS block 0. */
#define QAPI_NVM_APSS_BLOCK_01_BITMASK        (0x0008) /**< Bitmask representing APSS block 1. */
#define QAPI_NVM_APSS_BLOCK_02_BITMASK        (0x0010) /**< Bitmask representing APSS block 2. */
#define QAPI_NVM_APSS_BLOCK_03_BITMASK        (0x0020) /**< Bitmask representing APSS block 3. */
#define QAPI_NVM_APSS_BLOCK_04_BITMASK        (0x0040) /**< Bitmask representing APSS block 4. */
#define QAPI_NVM_APSS_BLOCK_05_BITMASK        (0x0080) /**< Bitmask representing APSS block 5. */
#define QAPI_NVM_APSS_BLOCK_06_BITMASK        (0x0100) /**< Bitmask representing APSS block 6. */
#define QAPI_NVM_APSS_BLOCK_07_BITMASK        (0x0200) /**< Bitmask representing APSS block 7. */
#define QAPI_NVM_APSS_BLOCK_08_BITMASK        (0x0400) /**< Bitmask representing APSS block 8. */
#define QAPI_NVM_APSS_BLOCK_09_BITMASK        (0x0800) /**< Bitmask representing APSS block 9. */
#define QAPI_NVM_APSS_BLOCK_10_BITMASK        (0x1000) /**< Bitmask representing APSS block 10. */
#define QAPI_NVM_APSS_BLOCK_11_BITMASK        (0x2000) /**< Bitmask representing APSS block 11. */
#define QAPI_NVM_APSS_BLOCK_12_BITMASK        (0x4000) /**< Bitmask representing APSS block 12. */


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Enumeration of subsystems that NVM can be shared with. */
typedef enum
{
   QAPI_NVM_SUBSYSTEM_ROT_E,  /**< Root of trust. */
   QAPI_NVM_SUBSYSTEM_BTSS_E  /**< Bluetooth subsystem. */
} qapi_NVM_Subsystem_t;

/** Enumeration of permissions for a section of NVM. */
typedef enum
{
   QAPI_NVM_PERMISSIONS_NONE_E,               /**< No permissions. */
   QAPI_NVM_PERMISSIONS_READ_ONLY_E,          /**< Read only permissions. */
   QAPI_NVM_PERMISSIONS_READ_WRITE_E,         /**< Read and write permissions. */
   QAPI_NVM_PERMISSIONS_READ_EXECUTE_E,       /**< Read and execute permissions. */
   QAPI_NVM_PERMISSIONS_READ_WRITE_EXECUTE_E  /**< Read, write, and execute permissions. */
} qapi_NVM_Permissions_t;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Converts an address range to a bitmask of blocks.

   @param[in] Start Start of the address range to check.
   @param[in] End   End of the address range to check.

   @return
   Bitmask of blocks covered by the provided address range.
*/
uint16_t qapi_NVM_Address_Range_To_Blocks(const void *Start, const void *End);

/**
   @brief Sets the permissions for a section of NVM.

   @param[in] BlockMask    Bitmask of blocks to set permissions on.
   @param[in] Permissions  Permissions to set.

   @return
   Bitmask of blocks whose permissions were set.
*/
uint16_t qapi_NVM_Set_Permissions(uint16_t BlockMask, qapi_NVM_Permissions_t Permissions);

/**
   @brief Gets the permissions for an address in NVM.

   @param[in] Address  Address to get permissions for.

   @return
   Permission level of the selected address.
*/
qapi_NVM_Permissions_t qapi_NVM_Get_Permissions(const void *Address);

/**
   @brief Shares a section of NVM with another subsystem.

   The remote subsystem will be provided read-only permissions to this section
   of NVM.

   @param[in] BlockMask  Bitmask of blocks to set permissions on.
   @param[in] Subsystem  Subsystems to set permissions for.
   @param[in] Share      Flag that indicates the block(s) should be shared
                         (TRUE) or not shared (FALSE).

   @return
   Bitmask of blocks whose permissions were set.
*/
uint16_t qapi_NVM_Share(uint16_t BlockMask, qapi_NVM_Subsystem_t Subsystem, qbool_t Share);

/**
   @brief Requests permissions to write to NVM.

   This must be called before any calls to qapi_NVM_Write().

   @return
   QAPI_OK -- If permissions were granted. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Request_Write(void);

/**
   @brief Releases a request for NVM write permissions.

   This allows other cores to write to NVM as needed and should be called once
   all outstanding NVM writes are complete.  Not calling this API might cause
   errors from other APIs that require another core to write to NVM.

   @return
   QAPI_OK -- If successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Release_Write(void);

/**
   @brief Writes the provided buffer to the specified address in NVM (RRAM).

   Writes to NVM will block NVM reads so this function blocks until the NVM
   write has completed.

   Also, the caller should be aware that writing to RRAM can block other cores
   (namely BTSS) and very long writes may affect performance.

   @param[in] Address  NVM address to write to.
   @param[in] Buffer   Data to write to NVM.
   @param[in] Length   Length of the data to write to NVM.

   @return
   QAPI_OK -- If the data was successfully written to NVM. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Write(const void *Address, const void *Buffer, uint32_t Length);

/**
   @brief Erases a section of NVM (RRAM).

   Writes to NVM will block NVM reads so this function blocks until the NVM
   write has completed.

   Also, the caller should be aware that writing to RRAM can block other cores
   (namely BTSS) and very long writes may affect performance.

   @param[in] Address  NVM address to erase.
   @param[in] Length   Length of the data to erase.

   @return
   QAPI_OK -- If the data was successfully erased.\n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_NVM_Erase(const void *Address, uint32_t Length);

/** @} */ /* end_addtogroup qapi_platform_nvm */

#endif

