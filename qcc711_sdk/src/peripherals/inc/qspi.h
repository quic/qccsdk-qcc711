/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qspi.h
   @brief qspi Services Interface definition.

   This module provide quad serial peripheral interface APIs, types, and
   definitions.
*/
 
#ifndef __QSPI_H__
#define __QSPI_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_status.h" 

/** @addtogroup peripherals_qspi
@{
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define QSPI_PBL_CLOCK_FREQUENCY           16000000    /**< QSPI clock frequency in PBL mode. */
#define QSPI_SBL_CLOCK_FREQUENCY           8000000     /**< QSPI clock frequency in SBL mode. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of QSPI DDR mode and multi IO mode.
*/
typedef enum
{
    QSPI_SDR_1BIT_E = 1,   /**< Single SPI, SDR mode. */
    QSPI_SDR_2BIT_E,       /**< Dual SPI, SDR mode. */
    QSPI_SDR_4BIT_E,       /**< Quad SPI, SDR mode. */
    QSPI_DDR_1BIT_E = 5,   /**< Single SPI, DDR mode. */
    QSPI_DDR_2BIT_E,       /**< Dual SPI, DDR mode. */
    QSPI_DDR_4BIT_E        /**< Quad SPI, DDR mode. */
} QSPI_Mode_t;

/**
   Enumeration of QSPI transfer mode.
*/
typedef enum
{
    QSPI_PIO_MODE_E,       /**< PIO mode. */
    QSPI_DMA_POLL_MODE_E,  /**< DMA polling mode. */
    QSPI_DMA_INT_MODE_E    /**< DMA interrupt mode. */
} QSPI_TransferMode_t;

/**
   Structur representing the QSPI cmd configurations.
*/
typedef struct QSPI_Cmd_s
{
    uint8_t     Opcode;      /**< The instruction for the command. */
    uint8_t     AddrBytes;   /**< The address bytes for the command, 3 bytes or 4 bytes,
                                  depend on the connected flash type. */
    uint8_t     DummyClocks; /**< The dummy clock cycles for the command. */
    QSPI_Mode_t CmdMode;     /**< The instruction mode. */
    QSPI_Mode_t AddrMode;    /**< The address mode. */
    QSPI_Mode_t DataMode;    /**< The data mode. */
    qbool_t     Write;       /**< Read or write operation, TRUE: write, FALSE: read. */
} QSPI_Cmd_t;

/**
   @brief Prototype for a function called when interrupt is triggered.

   @param[in] Status     The interrupt status.
   @param[in] UserParam  User specified parameter provided when the callback is registered.
*/
typedef void (*QSPI_Isr_CB_t)(uint32_t Status, void *UserParam);

/**
   Structur representing the QSPI master configurations.
*/
typedef struct QSPI_MasterConfig_s
{
    uint8_t       ChipSelect;    /**< Chip select to assert during transaction (0 or 1). */
    qbool_t       ClkPolarity;   /**< Clock polarity. */
    qbool_t       ClkPhase;      /**< Clock phase. */
    uint32_t      ClkFreq;       /**< Bus clock frequency. */
    QSPI_Isr_CB_t IsrCB;         /**< User registered isr callback. It should do minimal processing. */
    void         *UserParam;     /**< User specified parameter for the callback function. */
} QSPI_MasterConfig_t;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize the QSPI and the HW it depends on (clocks, GPIOs).

   This function can be called between transfers to change the bus clock
   frequency, chip select, etc.

   @param[in] Config  The QSPI master configurations.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_Init(QSPI_MasterConfig_t *Config);

/**
   @brief Set QSPI command parameters.

   @param[in] Cmd          Pointer to the command.
   @param[in] Opcode       The instruction code.
   @param[in] AddrBytes    The address bytes.
   @param[in] DummyClocks  The dummy clock cycles.
   @param[in] CmdMode      The instruction mode.
   @param[in] AddrMode     The address mode.
   @param[in] DataMode     The data mode.
   @param[in] Write        Read or Write, true: write, false: read.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_SetCmd(QSPI_Cmd_t *Cmd, uint8_t Opcode, uint8_t AddrBytes, uint8_t DummyClocks, QSPI_Mode_t CmdMode, QSPI_Mode_t AddrMode, QSPI_Mode_t DataMode, qbool_t Write);

/**
   @brief Send QSPI command

   @param[in]    Cmd        The command configuration.
   @param[in]    Addr       The address for the command.
   @param[inout] Data       The data buffer containing data to write,
                            or as buffer for reading data.
   @param[in]    DataBytes  The number of data to write or read.
   @param[in]    EnableDma  The command transfer mode.

   @return TRUE on success or FALSE on failure.
*/
qbool_t QSPI_Cmd(QSPI_Cmd_t *Cmd, uint32_t Addr, uint8_t *Data, uint32_t DataBytes, QSPI_TransferMode_t EnableDma);

/** @} */

#endif

