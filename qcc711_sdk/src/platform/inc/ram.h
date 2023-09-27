/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __SHARED_RAM_H__
#define __SHARED_RAM_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define RAM_MAX_SHARED_BLOCK_SETS                                       (4) /**< Maximum number of sets of RAM blocks (i.e., calls to RAM_StartSharing()),
                                                                                 that can be outstanding at the same time. */

/* Definitions for the RAM address ranges. */
#define RAM_START                                                       ((void *)0x20000000) /**< Start address of RAM. */
#define RAM_END                                                         ((void *)0x2001FFFF) /**< End address of RAM. */
#define RAM_SIZE                                                        (0x00020000)         /**< Overall size of RAM. */
#define RAM_BLOCK_SIZE                                                  (0x00002000)         /**< Size of a single RAM block. */
#define RAM_SUBBLOCK_SIZE                                               (0x00000400)         /**< Size of a single RAM subblock. */

#define RAM_BTSS_START                                                  ((void *)0x20000000) /**< Start address of BTSS RAM. */
#define RAM_BTSS_END                                                    ((void *)0x2000FFFF) /**< End address of BTSS RAM. */
#define RAM_BTSS_SIZE                                                   (0x00010000)         /**< Size of the BTSS RAM. */

#define RAM_APSS_START                                                  ((void *)0x20010000) /**< Start address of APSS RAM. */
#define RAM_APSS_END                                                    ((void *)0x2001FFFF) /**< End address of APSS RAM. */
#define RAM_APSS_SIZE                                                   (0x00010000)         /**< Size of the APSS RAM. */

/* Definitions for the address ranges of the RAM blocks that can be shared. */
#define RAM_BTSS_BLOCK_0_START                                          ((void *)0x20000000) /**< Start address of BTSS RAM block 0.  This block can be retained. */
#define RAM_BTSS_BLOCK_0_END                                            ((void *)0x20001FFF) /**< End address of BTSS RAM block 0. */
#define RAM_BTSS_BLOCK_1_START                                          ((void *)0x20002000) /**< Start address of BTSS RAM block 1.  This block can be retained. */
#define RAM_BTSS_BLOCK_1_END                                            ((void *)0x20003FFF) /**< End address of BTSS RAM block 1. */
#define RAM_BTSS_BLOCK_2_START                                          ((void *)0x20004000) /**< Start address of BTSS RAM block 2. */
#define RAM_BTSS_BLOCK_2_END                                            ((void *)0x20005FFF) /**< End address of BTSS RAM block 2. */
#define RAM_BTSS_BLOCK_3_START                                          ((void *)0x20006000) /**< Start address of BTSS RAM block 3. */
#define RAM_BTSS_BLOCK_3_END                                            ((void *)0x20007FFF) /**< End address of BTSS RAM block 3. */
#define RAM_BTSS_BLOCK_4_START                                          ((void *)0x20008000) /**< Start address of BTSS RAM block 4. */
#define RAM_BTSS_BLOCK_4_END                                            ((void *)0x20009FFF) /**< End address of BTSS RAM block 4. */
#define RAM_BTSS_BLOCK_5_START                                          ((void *)0x2000A000) /**< Start address of BTSS RAM block 5. */
#define RAM_BTSS_BLOCK_5_END                                            ((void *)0x2000BFFF) /**< End address of BTSS RAM block 5. */
#define RAM_BTSS_BLOCK_6_START                                          ((void *)0x2000C000) /**< Start address of BTSS RAM block 6. */
#define RAM_BTSS_BLOCK_6_END                                            ((void *)0x2000DFFF) /**< End address of BTSS RAM block 6. */
#define RAM_BTSS_BLOCK_7_START                                          ((void *)0x2000E000) /**< Start address of BTSS RAM block 7. This block can be subdivided into
                                                                                                  subblocks for sharing. */
#define RAM_BTSS_BLOCK_7_END                                            ((void *)0x2001FFFF) /**< End address of BTSS RAM block 7. */

#define RAM_APSS_BLOCK_0_START                                          ((void *)0x20010000) /**< Start address of APSS RAM block 0.  This block can be retained. */
#define RAM_APSS_BLOCK_0_END                                            ((void *)0x20011FFF) /**< End address of APSS RAM block 0. */
#define RAM_APSS_BLOCK_1_START                                          ((void *)0x20012000) /**< Start address of APSS RAM block 1.  This block can be retained. */
#define RAM_APSS_BLOCK_1_END                                            ((void *)0x20013FFF) /**< End address of APSS RAM block 1. */
#define RAM_APSS_BLOCK_2_START                                          ((void *)0x20014000) /**< Start address of APSS RAM block 2. */
#define RAM_APSS_BLOCK_2_END                                            ((void *)0x20015FFF) /**< End address of APSS RAM block 2. */
#define RAM_APSS_BLOCK_3_START                                          ((void *)0x20016000) /**< Start address of APSS RAM block 3. */
#define RAM_APSS_BLOCK_3_END                                            ((void *)0x20017FFF) /**< End address of APSS RAM block 3. */
#define RAM_APSS_BLOCK_4_START                                          ((void *)0x20018000) /**< Start address of APSS RAM block 4. */
#define RAM_APSS_BLOCK_4_END                                            ((void *)0x20019FFF) /**< End address of APSS RAM block 4. */
#define RAM_APSS_BLOCK_5_START                                          ((void *)0x2001A000) /**< Start address of APSS RAM block 5. */
#define RAM_APSS_BLOCK_5_END                                            ((void *)0x2001BFFF) /**< End address of APSS RAM block 5. */
#define RAM_APSS_BLOCK_6_START                                          ((void *)0x2001C000) /**< Start address of APSS RAM block 6. */
#define RAM_APSS_BLOCK_6_END                                            ((void *)0x2001DFFF) /**< End address of APSS RAM block 6. */
#define RAM_APSS_BLOCK_7_START                                          ((void *)0x2001E000) /**< Start address of APSS RAM block 7. This block can be subdivided into
                                                                                                  subblocks for sharing. */
#define RAM_APSS_BLOCK_7_END                                            ((void *)0x2001FFFF) /**< End address of APSS RAM block 7. */

/* Definitions for the address ranges of the RAM subblocks that can be shared. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_0_START                               ((void *)0x2000E000) /**< Start address of BTSS RAM block 7, subblock 0. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_0_END                                 ((void *)0x2000E3FF) /**< End address of BTSS RAM block 7, subblock 0. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_1_START                               ((void *)0x2000E400) /**< Start address of BTSS RAM block 7, subblock 1. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_1_END                                 ((void *)0x2000E7FF) /**< End address of BTSS RAM block 7, subblock 1. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_2_START                               ((void *)0x2000E800) /**< Start address of BTSS RAM block 7, subblock 2. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_2_END                                 ((void *)0x2000EBFF) /**< End address of BTSS RAM block 7, subblock 2. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_3_START                               ((void *)0x2000EC00) /**< Start address of BTSS RAM block 7, subblock 3. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_3_END                                 ((void *)0x2000EFFF) /**< End address of BTSS RAM block 7, subblock 3. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_4_START                               ((void *)0x2000F000) /**< Start address of BTSS RAM block 7, subblock 4. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_4_END                                 ((void *)0x2000F3FF) /**< End address of BTSS RAM block 7, subblock 4. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_5_START                               ((void *)0x2000F400) /**< Start address of BTSS RAM block 7, subblock 5. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_5_END                                 ((void *)0x2000F7FF) /**< End address of BTSS RAM block 7, subblock 5. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_6_START                               ((void *)0x2000F800) /**< Start address of BTSS RAM block 7, subblock 6. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_6_END                                 ((void *)0x2000FBFF) /**< End address of BTSS RAM block 7, subblock 6. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_7_START                               ((void *)0x2000FC00) /**< Start address of BTSS RAM block 7, subblock 7. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_7_END                                 ((void *)0x2000FFFF) /**< End address of BTSS RAM block 7, subblock 7. */

#define RAM_APSS_BLOCK_7_SUBBLOCK_0_START                               ((void *)0x2001E000) /**< Start address of APSS RAM block 7, subblock 0. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_0_END                                 ((void *)0x2001E3FF) /**< End address of APSS RAM block 7, subblock 0. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_1_START                               ((void *)0x2001E400) /**< Start address of APSS RAM block 7, subblock 1. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_1_END                                 ((void *)0x2001E7FF) /**< End address of APSS RAM block 7, subblock 1. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_2_START                               ((void *)0x2001E800) /**< Start address of APSS RAM block 7, subblock 2. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_2_END                                 ((void *)0x2001EBFF) /**< End address of APSS RAM block 7, subblock 2. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_3_START                               ((void *)0x2001EC00) /**< Start address of APSS RAM block 7, subblock 3. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_3_END                                 ((void *)0x2001EFFF) /**< End address of APSS RAM block 7, subblock 3. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_4_START                               ((void *)0x2001F000) /**< Start address of APSS RAM block 7, subblock 4. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_4_END                                 ((void *)0x2001F3FF) /**< End address of APSS RAM block 7, subblock 4. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_5_START                               ((void *)0x2001F400) /**< Start address of APSS RAM block 7, subblock 5. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_5_END                                 ((void *)0x2001F7FF) /**< End address of APSS RAM block 7, subblock 5. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_6_START                               ((void *)0x2001F800) /**< Start address of APSS RAM block 7, subblock 6. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_6_END                                 ((void *)0x2001FBFF) /**< End address of APSS RAM block 7, subblock 6. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_7_START                               ((void *)0x2001FC00) /**< Start address of APSS RAM block 7, subblock 7. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_7_END                                 ((void *)0x2001FFFF) /**< End address of APSS RAM block 7, subblock 7. */

#define RAM_BTSS_BLOCKS_BITMASK                                         (0x000000FF) /**< Bitmask of all BTSS RAM blocks. */
#define RAM_BTSS_BLOCK_0_BITMASK                                        (0x00000001) /**< Bitmask representing BTSS RAM block 0. */
#define RAM_BTSS_BLOCK_1_BITMASK                                        (0x00000002) /**< Bitmask representing BTSS RAM block 1. */
#define RAM_BTSS_BLOCK_2_BITMASK                                        (0x00000004) /**< Bitmask representing BTSS RAM block 2. */
#define RAM_BTSS_BLOCK_3_BITMASK                                        (0x00000008) /**< Bitmask representing BTSS RAM block 3. */
#define RAM_BTSS_BLOCK_4_BITMASK                                        (0x00000010) /**< Bitmask representing BTSS RAM block 4. */
#define RAM_BTSS_BLOCK_5_BITMASK                                        (0x00000020) /**< Bitmask representing BTSS RAM block 5. */
#define RAM_BTSS_BLOCK_6_BITMASK                                        (0x00000040) /**< Bitmask representing BTSS RAM block 6. */
#define RAM_BTSS_BLOCK_7_BITMASK                                        (0x00000080) /**< Bitmask representing BTSS RAM block 7. */
#define RAM_APSS_BLOCKS_BITMASK                                         (0x0000FF00) /**< Bitmask of all APSS RAM blocks. */
#define RAM_APSS_BLOCK_0_BITMASK                                        (0x00000100) /**< Bitmask representing APSS RAM block 0. */
#define RAM_APSS_BLOCK_1_BITMASK                                        (0x00000200) /**< Bitmask representing APSS RAM block 1. */
#define RAM_APSS_BLOCK_2_BITMASK                                        (0x00000400) /**< Bitmask representing APSS RAM block 2. */
#define RAM_APSS_BLOCK_3_BITMASK                                        (0x00000800) /**< Bitmask representing APSS RAM block 3. */
#define RAM_APSS_BLOCK_4_BITMASK                                        (0x00001000) /**< Bitmask representing APSS RAM block 4. */
#define RAM_APSS_BLOCK_5_BITMASK                                        (0x00002000) /**< Bitmask representing APSS RAM block 5. */
#define RAM_APSS_BLOCK_6_BITMASK                                        (0x00004000) /**< Bitmask representing APSS RAM block 6. */
#define RAM_APSS_BLOCK_7_BITMASK                                        (0x00008000) /**< Bitmask representing APSS RAM block 7. */
#define RAM_BTSS_BLOCK_7_SUBBLOCKS_BITMASK                              (0x00FF0000) /**< Bitmask of all BTSS RAM blocks. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_0_BITMASK                             (0x00010000) /**< Bitmask representing BTSS RAM block 7, subblock 0. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_1_BITMASK                             (0x00020000) /**< Bitmask representing BTSS RAM block 7, subblock 1. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_2_BITMASK                             (0x00040000) /**< Bitmask representing BTSS RAM block 7, subblock 2. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_3_BITMASK                             (0x00080000) /**< Bitmask representing BTSS RAM block 7, subblock 3. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_4_BITMASK                             (0x00100000) /**< Bitmask representing BTSS RAM block 7, subblock 4. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_5_BITMASK                             (0x00200000) /**< Bitmask representing BTSS RAM block 7, subblock 5. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_6_BITMASK                             (0x00400000) /**< Bitmask representing BTSS RAM block 7, subblock 6. */
#define RAM_BTSS_BLOCK_7_SUBBLOCK_7_BITMASK                             (0x00800000) /**< Bitmask representing BTSS RAM block 7, subblock 7. */
#define RAM_APSS_BLOCK_7_SUBBLOCKS_BITMASK                              (0xFF000000) /**< Bitmask of all BTSS RAM blocks. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_0_BITMASK                             (0x01000000) /**< Bitmask representing APSS RAM block 7, subblock 0. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_1_BITMASK                             (0x02000000) /**< Bitmask representing APSS RAM block 7, subblock 1. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_2_BITMASK                             (0x04000000) /**< Bitmask representing APSS RAM block 7, subblock 2. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_3_BITMASK                             (0x08000000) /**< Bitmask representing APSS RAM block 7, subblock 3. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_4_BITMASK                             (0x10000000) /**< Bitmask representing APSS RAM block 7, subblock 4. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_5_BITMASK                             (0x20000000) /**< Bitmask representing APSS RAM block 7, subblock 5. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_6_BITMASK                             (0x40000000) /**< Bitmask representing APSS RAM block 7, subblock 6. */
#define RAM_APSS_BLOCK_7_SUBBLOCK_7_BITMASK                             (0x80000000) /**< Bitmask representing APSS RAM block 7, subblock 7. */


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** Enumeration of subsystems. */
typedef enum
{
   RAM_SUBSYSTEM_UNKNOWN_E, /**< Unknown subsystem. This is used as an error value for applicable APIs and
                                 is not expected to be provided as a parameter. */
   RAM_SUBSYSTEM_ROT_E,     /**< Root of trust. */
   RAM_SUBSYSTEM_BTSS_E,    /**< Bluetooth subsystem. */
   RAM_SUBSYSTEM_APSS_E     /**< Application subsystem. */
} RAM_Subsystem_t;

/** Enumeration of permissions for a section of memory. */
typedef enum
{
   RAM_PERM_NO_ACCESS_E,  /**< No access to memory. */
   RAM_PERM_READ_ONLY_E,  /**< Memory is read only.  */
   RAM_PERM_READ_WRITE_E  /**< Memory is readable and writable. */
} RAM_Permission_t;


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Converts an address range to a bitmask of blocks.

   @param[in] Start         Start of the address range to check.
   @param[in] End           End of the address range to check.

   @return Bitmask of blocks covered by the provided address range.
*/
uint32_t RAM_AddressRangeToBlocks(const void *Start, const void *End);

/**
   @brief Provides the owner for a region of RAM.

   @param[in] Address  Address to read the owner of.

   @return Subsystem that owns the specified address or RAM_SUBYSTEM_UNKNOWN_E
           if the owner could not be determined.
*/
RAM_Subsystem_t RAM_GetOwner(const void *Address);

/**
   @brief Shares RAM address blocks with another subsystem.

   Sharing is done in blocks and this API will affect all blocks covered by the
   provided address range.

   @param[in] Subsystem   Subsystem the memory is shared with.
   @param[in] BlockMask   Bitmask of blocks to share.
   @param[in] Permission  Permissions the subsystem will have to the shared
                          memory.

   @return QAPI_OK if the RAM was shared correctly or a negative value if
           there was an error.
*/
qapi_Status_t RAM_Share(RAM_Subsystem_t Subsystem, uint32_t BlockMask, RAM_Permission_t Permission);

#endif

