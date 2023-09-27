/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_flash.h
   @brief Flash Services Interface definition.
   
      This module provides flash operation APIs.
   
*/

/** @addtogroup qapi_peripherals_flash

  The QSPI Flash module provides flash operation APIs.

  qapi_FLASH_Init() initializes the flash module and must be called
  before any other function in this module. The input parameter - Config -
  must be set based on the specific flash used.

  Flash read/write/erase/writereg operations cannot be performed simultaneously.
  There can be only one operation ongoing at a time.

  Flash read/write/erase/writereg support both blocking and non-blocking
  operations.

  For a blocking operation, the related function returns until the
  required number of data/status are read/written/erased successfully, or
  there is an error. If the required number is large, the related function
  may take some time to return. It should be taken into consideration if
  the product is power and time sensitive.

  For a non-blocking operation, the related function returns immediately
  after the read/program/erase/writereg command is transmitted with a status
  #QAPI_FLASH_STATUS_PENDING, or there is an error. 
  
  A return status #QAPI_FLASH_STATUS_PENDING, indicates that the operation is
  still ongoing in the background. It releases the CPU, and gives other tasks
  an opportunity to run.

  After the operation is finished, the user registered callback function is
  called to inform the completion. All other applications that must
  run after a flash read/write/erase/writereg operation, should not be performed
  before the callback function is invoked.

  During non-blocking flash read/write, an input buffer is used to store
  the data to be read or written. While the qapi_FLASH_Write() or
  qapi_FLASH_Read() is waiting to be returned, the buffer is used for read/write
  operations in the background. Therefore, the buffer should not be in a stack,
  or freed, before the operation completes. The buffer should be in heap, or a
  static buffer.

  @note1hang Before using module APIs, qapi_PWR_Set_Module_State
             (#QAPI_PWR_MODULE_PERIPHERAL_E, #QAPI_PWR_STATE_ACTIVE_E,
             #QAPI_PWR_STATE_ACTIVE_E) must be called.
*/

#ifndef __QAPI_FLASH_H__
#define __QAPI_FLASH_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h"

/** @addtogroup qapi_peripherals_flash
@{ */

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/** Flash non-blocking operation is ongoing. */
#define QAPI_FLASH_STATUS_PENDING      ((qapi_Status_t)(1))

/** Flash read/write mode: SDR, single mode. */
#define QAPI_FLASH_RW_MODE_SDR_SINGLE  1

/** Flash read/write mode: SDR, dual mode. */
#define QAPI_FLASH_RW_MODE_SDR_DUAL    2

/** Flash read/write mode: SDR, quad mode. */
#define QAPI_FLASH_RW_MODE_SDR_QUAD    3

/** Flash read/write mode: DDR, quad mode. */
#define QAPI_FLASH_RW_MODE_DDR_QUAD    7


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of flash erase types.
*/
typedef enum
{
    QAPI_FLASH_BLOCK_ERASE_E, /**< Block erase. Block size is 4&nbsp;KB. */
    QAPI_FLASH_BULK_ERASE_E,  /**< Bulk erase. Bulk size is n*4&nbsp;Kb, for
                                   example 32&nbsp;Kb, 64&nbsp;Kb, and so on.
                                   It depends on the specific flash type. */
    QAPI_FLASH_CHIP_ERASE_E   /**< Chip erase. */
} qapi_FLASH_Erase_Type_t;

/**
   Structure representing the flash configuration table.
   This must be configured based on the specific flash type.
*/
typedef struct qapi_FLASH_Config_s
{
    uint8_t  PowerUpOpcode;            /**< Power up opcode. Some parts do not support this command; set it to 0. */
    uint8_t  AddrBytes;                /**< 3&nbsp;Bytes or 4&nbsp;Bytes addressing mode. */
    uint8_t  ReadCmdMode;              /**< Read operation command mode, QAPI_FLASH_RW_MODE_XXX. QUP access only supports single and quad mode. */
    uint8_t  ReadAddrMode;             /**< Read operation address mode, QAPI_FLASH_RW_MODE_XXX. QUP access only supports single and quad mode. */
    uint8_t  ReadDataMode;             /**< Read operation data mode, QAPI_FLASH_RW_MODE_XXX. QUP access only supports single and quad mode. */
    uint8_t  ReadOpcode;               /**< Read opcode. */
    uint8_t  ReadWaitState;            /**< Read wait state is the total dummy cycles to wait. */
    uint8_t  WriteCmdMode;             /**< Write operation address mode, QAPI_FLASH_RW_MODE_XXX. */
    uint8_t  WriteAddrMode;            /**< Write operation address mode, QAPI_FLASH_RW_MODE_XXX. */
    uint8_t  WriteDataMode;            /**< Write operation data mode, QAPI_FLASH_RW_MODE_XXX. */                                        
    uint8_t  WriteOpcode;              /**< Opcode used for write. */
    uint8_t  Erase4kbOpcode;           /**< Opcode used for 4&nbsp;KB block erase. */
    uint8_t  BulkEraseSizeIn4KB;       /**< Bulk erase size. Unit is 4&nbsp;KB. */
    uint8_t  BulkEraseOpcode;          /**< The opcode for the supported bulk erase size (larger than a 4&nbsp;KB block erase). If bulk erase is not supported, set to 0. */
    uint8_t  ChipEraseOpcode;          /**< Opcode used for chip erase. */
    uint8_t  QuadEnableMode;           /**< Quad Enable Requirements (QER) as defined in the JEDEC Standard No. 216A Document. */
    uint8_t  SuspendEraseOpcode;       /**< Instruction to suspend an in-progress erase. */
    uint8_t  SuspendProgramOpcode;     /**< Instruction to suspend an in-progress program. */
    uint8_t  ResumeEraseOpcode;        /**< Instruction to resume an erase operation. */
    uint8_t  ResumeProgramOpcode;      /**< Instruction to resume a program operation. */
    uint8_t  EraseErrBmsk;             /**< Status BIT(s) in the EraseErrStatusReg register; indicating if there is an erase error condition. */
    uint8_t  EraseErrStatusReg;        /**< Register address used for polling the erase status. */
    uint8_t  WriteErrBmsk;             /**< Status BIT(s) in the WriteErrStatusReg register; indicating if there is a write error condition. */
    uint8_t  WriteErrStatusReg;        /**< Register address used for polling the write status. */
    uint8_t  HighPerformanceModeBmask; /**< High Performance Bit(s). Non-Macronix parts set to 0. This field is used to
                                            enable High Performance mode supported on some Macronix parts. */
    uint8_t  PowerOnDelayIn100us;      /**< Power On Reset delay in 100&nbsp;us units. */
    uint16_t SuspendEraseDelayInUs;    /**< Delay needed after suspending an in-progress erase; see JEDEC Standard No. 216A for a definition. */
    uint16_t SuspendProgramDelayInUs;  /**< Delay needed after suspending an in-progress program; see JEDEC Standard No. 216A for a definition. */
    uint16_t ResumeEraseDelayInUs;     /**< Delay needed after sending a resume erase; see JEDEC Standard No. 216A for a definition. */
    uint16_t ResumeProgramDelayInUs;   /**< Delay needed after sending a resume program; see JEDEC Standard No. 216A for a definition. */
    uint32_t DensityInBlocks;          /**< Device density in unit of Blocks. */
    uint32_t DeviceId;                 /**< Device ID when querying with a Device Read ID command 0x9F. */
    uint32_t WriteProtectBmask;        /**< Write Block Protection Mask. */
} qapi_FLASH_Config_t;

/**
   @brief Prototype for a function called after a non-blocking flash
          read/write/erase/writereg operation is complete.

   This function is called from a flash operation task.

   @param[in] Status     Flash operation result.
   @param[in] UserParam  User-specified parameter provided when the callback
                         is registered.
*/
typedef void (*qapi_FLASH_Operation_CB_t)(qapi_Status_t Status, void *UserParam);

/**
   Type representing the flash memory map handle.
*/
typedef void* qapi_FLASH_Map_Handle_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize the flash module.

   This function must be called before any other flash functions.

   @param[in] Config  Configuration data for the flash device.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_FLASH_Init(const qapi_FLASH_Config_t *Config);

/**
   @brief Read data from the flash.

   This function, if:
   - Blocking -- returns when the read is done
   - Non-blocking -- returns with #QAPI_FLASH_STATUS_PENDING,
   indicating that the read is performed in the background

   A callback function indicates when the non-blocking operation
   is complete. Because read is ongoing after this function returns,
   the input buffer for storing read data should not be freed. All
   other operations that must run after flash read, should not be performed
   before the callback function is called.

   @param[in]  Address    The flash address to start to read from.
   @param[in]  ByteCnt    Number of bytes to read.
   @param[out] Buffer     Data buffer for a flash read operation; it should be
                          in heap, or a static buffer for a non-blocking read.
   @param[in]  ReadCB     Flash read callback function for a non-blocking
                          read. After a read is done, the ReadCB is
                          called to inform about the completion; it should
                          be NULL for a blocking read.
   @param[in]  UserParam  The user-specified parameter for the callback
                          function.

   @return
   QAPI_OK -- If a blocking read completed successfully. \n
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking read is ongoing. \n
   Negative value -- If there is an error.
*/
qapi_Status_t qapi_FLASH_Read(uint32_t Address, uint32_t ByteCnt, uint8_t *Buffer, qapi_FLASH_Operation_CB_t ReadCB, void *UserParam);

/**
   @brief Write data to the flash.

   This function, if:
   - Blocking -- returns when the write is done
   - Non-blocking -- returns with #QAPI_FLASH_STATUS_PENDING,
   indicating that the write is performed in the background

   A callback function indicates when the non-blocking operation
   is complete. Because write is ongoing after this function returns,
   the input buffer for storing write data should not be freed. All
   other operations that must run after flash write, should not be performed
   before the callback function is called.

   @param[in] Address    The flash address to start to write to.
   @param[in] ByteCnt    Number of bytes to write.
   @param[in] Buffer     Data buffer containing data to be written; it should be
                         in heap, or a static buffer for a non-blocking write.
   @param[in] WriteCB    Flash write callback function for non-blocking
                         write. After write is done, the WriteCB is
                         called to inform about the completion; it should
                         be NULL for a blocking write.
   @param[in] UserParam  The user-specified parameter for the callback function.

   @return
   QAPI_OK -- If blocking write completed successfully. \n
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking write is ongoing. \n
   Negative value -- If there is an error.
*/
qapi_Status_t qapi_FLASH_Write(uint32_t Address, uint32_t ByteCnt, uint8_t *Buffer, qapi_FLASH_Operation_CB_t WriteCB, void *UserParam);

/**
   @brief Erase the given flash blocks or bulks, or the whole chip.

   This function, if:
   - Blocking -- returns when the erase is done
   - Non-blocking -- returns with #QAPI_FLASH_STATUS_PENDING,
   indicating that the erase is performed in the background

   A callback function indicates when the non-blocking operation
   is complete. Because erase is ongoing after this function returns,
   other operations that must run after flash erase, should not be performed
   before the callback function is called.

   @param[in] EraseType  Specify the erase type.
   @param[in] Start      For block erase - the starting block of a
                         number of blocks to erase.
                         For bulk erase - the starting bulk of a number
                         of bulks to erase.
                         For chip erase, it should be 0.
   @param[in] Cnt        For block erase - the number of blocks to erase.
                         For bulk erase - the number of bulks to erase.
                         For chip erase, it should be 1.
   @param[in] EraseCB    Flash erase callback function for non-blocking
                         erase. After erase is done, the EraseCB is
                         called to inform about the completion; it should be
                         NULL for a blocking erase.
   @param[in] UserParam  The user-specified parameter for the callback function.

   @return
   QAPI_OK -- If blocking erase completed successfully. \n
   QAPI_FLASH_STATUS_PENDING -- Indicating a non-blocking erase is ongoing. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_FLASH_Erase(qapi_FLASH_Erase_Type_t EraseType, uint32_t Start, uint32_t Cnt, qapi_FLASH_Operation_CB_t EraseCB, void *UserParam);

/**
   @brief Read flash registers.

   @param[in]  RegOpcode  Operation code.
   @param[in]  Len        The length of register value to be read.
   @param[out] RegValue   The read out value.

   @return
   QAPI_OK -- On success. \n
   Error code -- On failure.
*/
qapi_Status_t qapi_FLASH_Read_Reg(uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue);

/**
   @brief Write flash registers.

   This function, if:
   - Blocking -- returns when the writereg is done
   - Non-blocking -- it returns with #QAPI_FLASH_STATUS_PENDING,
   indicating that the writereg is performed in the background

   A callback function indicates when the non-blocking operation
   is complete. Because writereg is ongoing after this function returns,
   other operations that must run after flash writereg, should not be performed
   before the callback function is called.

   @param[in] RegOpcode   Operation code.
   @param[in] Len         The length of register value to be written.
   @param[in] RegValue    The written value.
   @param[in] WriteRegCB  Flash writereg callback function for a non-blocking
                          writereg. After writereg is done, the WriteRegCB
                          is called to inform about the completion; it
                          should be NULL for a blocking operation.
   @param[in] UserParam   The user-specified parameter for the callback
                          function.

   @return
   QAPI_OK -- If blocking writereg completed successfully. \n
   QAPI_FLASH_STATUS_PENDING -- Indicating non-blocking writereg is ongoing. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_FLASH_Write_Reg(uint8_t RegOpcode, uint8_t Len, uint8_t *RegValue, qapi_FLASH_Operation_CB_t WriteRegCB, void *UserParam);

/**
   @brief Map part of flash memory to a specific part of system memory.

   This function allows QUP DMA to directly read flash contents from a specific
   system address which is mapped with flash memory.
   
   To use this feature, the flash read mode should be single-mode or quad-mode.
   Dual-read mode is not supported. It allows at most 3 different parts of
   flash memory to be mapped to 3 different parts of system memory; while each
   part can support up to 16&nbsp;Mbytes. The different parts of flash memory
   cannot be overlapped with each other on the block.

   @param[in]  Address    Flash start address to be mapped.
   @param[in]  Size       The size of flash memory to be mapped.
   @param[out] MapHandle  Handle to flash mapped memory.

   @return
   QAPI_OK -- If mapping was successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_FLASH_Memory_Map(uint32_t Address, uint32_t Size, qapi_FLASH_Map_Handle_t *MapHandle);

/**
   @brief Unmap the part of flash memory from system memory.

   This function disallows QUP DMA to directly read flash contents from a
   system address.

   @param[in] MapHandle  Handle to flash mapped memory.

   @return
   QAPI_OK -- If unmapping was successful. \n
   Negative value -- If there was an error.
*/
qapi_Status_t qapi_FLASH_Memory_Unmap(qapi_FLASH_Map_Handle_t MapHandle);

/**
   @brief Get the mapped system address of a specific flash address.

   This function must be called before QUP DMA reading from flash. It converts
   the flash address to its mapped system address. QUP DMA can then directly
   read flash contents from the system address.

   @param[in]  Address        Flash physical address.
   @param[out] MappedAddress  The mapped system address.

   @return
   QAPI_OK -- If the address is obtained successfully. \n
   Negative value -- If there is an error.
*/
qapi_Status_t qapi_FLASH_Get_Mapped_Address(uint32_t Address, uint32_t *MappedAddress);

/** @} */ /* end_addtogroup qapi_peripherals_flash */

#endif

