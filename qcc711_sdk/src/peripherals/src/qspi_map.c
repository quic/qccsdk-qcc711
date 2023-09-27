/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qspi_map.h"
#include "qapi_heap.h"
#include "HALhwio.h"
#include "hwio_periph.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define MEMORY_MAP_MODULE_ENABLE            0x1
#define SUSPEND_ENABLE                      0x1
#define RESUME_ENABLE                       0x1

#define MAX_MEMORY_MAP_REGIONS              3           /**< Max supported memory map regions. */
#define MEMORY_MAP_REGION_BMSK              0x7

#define MEMORY_MAP_START_ADDRESS            0x55000000  /**< Start address of system memory that is mappable. */
#define MEMORY_MAP_REGION_SIZE              0x1000000   /**< Region size of system memory that is mappable. */
#define MEMORY_MAP_REGION_SIZE_IN_BLOCKS    0x1000      /**< Region size in 4kB size. */

#define SINGLE_MODE                         0x1  /**< QSPI IO single mode. */
#define QUAD_MODE                           0x3  /**< QSPI IO quad mode. */
#define IO_MODE_MASK                        0x3  /**< QSPI IO mode mask. */
#define DDR_SUPPORT                         0x4  /**< QSPI DDR support. */

#define AHB_CLK_FREQ                        0x40  /**< AHB clock frequency 64MHz. */

#define BLOCK_SIZE_IN_BYTES                 4096  /**< Block size. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Structure representing context for QSPI memory map module.
*/
typedef struct QSPI_MAP_Context_s
{
    uint32_t RegionEnableBits;                       /**< Memory map region enable bits. */
    uint32_t RegionSize[MAX_MEMORY_MAP_REGIONS];     /**< Memory map region size. */
    uint32_t RegionBaseAddr[MAX_MEMORY_MAP_REGIONS]; /**< Memory map region base address. */
} QSPI_MAP_Context_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

static QSPI_MAP_Context_t QSPI_MAP_Context;
static qbool_t MemMapInitDone = false;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Check read mode.

   @param[in]  Mode        Read command/address/data mode.
   @param[out] DdrSupport  Read mode is DDR or SDR, 1: DDR, 0: SDR.
   @param[out] BusWidth    Read mode bus width, 1: quad mode, 0: single mode.

   @return QAPI_OK if success, or a negative value if there was an error.
*/
static qapi_Status_t QSPI_MAP_CheckReadMode(uint8_t Mode, uint32_t *DdrSupport, uint32_t *BusWidth)
{
    uint8_t IoMode = (Mode & IO_MODE_MASK);

    if (DdrSupport == NULL || BusWidth == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }
    
    *DdrSupport = (Mode & DDR_SUPPORT) ? 1 : 0;

    if (IoMode == SINGLE_MODE)
    {
        *BusWidth = 0;
        if (*DdrSupport)
        {
            return QAPI_ERR_NOT_SUPPORTED;
        }
    }
    else if (IoMode == QUAD_MODE)
    {
        *BusWidth = 1;
    }
    else
    {
        return QAPI_ERR_NOT_SUPPORTED;
    }

    return QAPI_OK;
}

/**
   @brief Initialize QSPI memory mapping module.

   @param[in] Config  Specify the memory mapping configurations.

   @return QAPI_OK if success, or a negative value if there was an error.
*/
static qapi_Status_t QSPI_MAP_Init(QSPI_MAP_MemMapConfig_t *Config)
{
    uint32_t      DdrSupport;
    uint32_t      QuadBusWidth;
    qapi_Status_t Status;

    if (Config == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }
    
    HWIO_PERIPH_QSPI_XIP_GENERAL_CFG_OUT(PERIPH_QSPI_REG_BASE, 
                                         (HWIO_PERIPH_QSPI_XIP_GENERAL_CFG_BYPASS_DISABLE_BMSK | HWIO_PERIPH_QSPI_XIP_GENERAL_CFG_GENERATE_PATTERN_UPON_ACCESS_ERR_BMSK));
    
    /* Configure instruction phase. */
    Status = QSPI_MAP_CheckReadMode(Config->CmdMode, &DdrSupport, &QuadBusWidth);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                             (HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_LINEAR_BURST_INST_OPCODE_BMSK |
                                             HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_DDR_SDR_SELECTOR_BMSK |
                                             HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK),
                                             (((((uint32_t)(Config->ReadOpcode)) << HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_LINEAR_BURST_INST_OPCODE_SHFT) &
                                             HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_LINEAR_BURST_INST_OPCODE_BMSK) |
                                             (DdrSupport << HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_DDR_SDR_SELECTOR_SHFT) |
                                             (QuadBusWidth << HWIO_PERIPH_QSPI_XIP_INST_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT)));

    /* Configure address phase. */
    Status =  QSPI_MAP_CheckReadMode(Config->AddrMode, &DdrSupport, &QuadBusWidth);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                             (HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_ADDRESS_LENGTH_BMSK |
                                             HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_DDR_SDR_SELECTOR_BMSK |
                                             HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK),
                                             (((((uint32_t)(Config->AddrBytes)) << HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_ADDRESS_LENGTH_SHFT) &
                                             HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_ADDRESS_LENGTH_BMSK) |
                                             (DdrSupport << HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_DDR_SDR_SELECTOR_SHFT) |
                                             (QuadBusWidth << HWIO_PERIPH_QSPI_XIP_ADDR_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT)));
    
    /* Disable mode bits. */
    HWIO_PERIPH_QSPI_XIP_MODE_PH_CONFIG_OUT(PERIPH_QSPI_REG_BASE, 0);
    
    /* Configure dummy phase. */
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_ADDR(x)  ((x) + 0x0000021C)
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_IN(x)      \
        in_dword(HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_ADDR(x))
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_ADDR(x),m,v,HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_IN(x))
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DRIVE_BUS_DUMMY_PH_BMSK 0x10000000
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DRIVE_BUS_DUMMY_PH_SHFT 0x1C
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_BUS_VALUE_DUMMY_PH_BMSK 0xF000000
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_BUS_VALUE_DUMMY_PH_SHFT 0x18
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DUMMY_LENGTH_BMSK       0xFF00
#define HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DUMMY_LENGTH_SHFT       0x8

    HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                              HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DUMMY_LENGTH_BMSK,
                                              (((uint32_t)(Config->DummyCycles)) << HWIO_PERIPH_QSPI_XIP_DUMMY_PH_CONFIG_DUMMY_LENGTH_SHFT));
    
    /* Configure data phase. */
    Status = QSPI_MAP_CheckReadMode(Config->DataMode, &DdrSupport, &QuadBusWidth);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    HWIO_PERIPH_QSPI_XIP_DATA_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                             (HWIO_PERIPH_QSPI_XIP_DATA_PH_CONFIG_DDR_SDR_SELECTOR_BMSK |
                                             HWIO_PERIPH_QSPI_XIP_DATA_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK),
                                             ((DdrSupport << HWIO_PERIPH_QSPI_XIP_DATA_PH_CONFIG_DDR_SDR_SELECTOR_SHFT) |
                                             (QuadBusWidth << HWIO_PERIPH_QSPI_XIP_DATA_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT)));
    
    /* Configure suspend phase. */
    HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                                (HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_DDR_SDR_SELECTOR_BMSK |
                                                HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK),
                                                ((0 << HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_DDR_SDR_SELECTOR_SHFT) |
                                                (0 << HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT)));

    /* Configure resume phase. */
    HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                               (HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_DDR_SDR_SELECTOR_BMSK |
                                               HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_BUS_WIDTH_SELECTOR_BMSK),
                                               ((0 << HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_DDR_SDR_SELECTOR_SHFT) |
                                               (0 << HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_BUS_WIDTH_SELECTOR_SHFT)));

    /* Enable module. */
    HWIO_PERIPH_QSPI_XIP_MASTER_CFG_OUTM(PERIPH_QSPI_REG_BASE,
                                         (HWIO_PERIPH_QSPI_XIP_MASTER_CFG_AHBCLK_FREQ_BMSK |
                                         HWIO_PERIPH_QSPI_XIP_MASTER_CFG_XIP_ENABLE_BMSK),
                                         ((AHB_CLK_FREQ << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_AHBCLK_FREQ_SHFT) |
                                         (MEMORY_MAP_MODULE_ENABLE << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_XIP_ENABLE_SHFT)));

    MemMapInitDone = true;
    return QAPI_OK;  
}

/**
   @brief Map flash address to system memory region.

   @param[in]  Address     Flash start address to be mapped.
   @param[in]  Size        Flash size to be mapped.
   @param[out] RegionBits  The mapped system memory region bits.

   @return QAPI_OK if success, or a negative value if there was an error.
*/
static qapi_Status_t QSPI_MAP_RegionMap(uint32_t Address, uint32_t Size, uint32_t *RegionBits)
{
    uint32_t StartBlock;
    uint32_t BlockCnt;
    uint32_t EndBlock;
    uint8_t  i;
    uint32_t AvailableSize = 0;
    uint32_t MapSize;

    if (RegionBits == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    StartBlock = Address / BLOCK_SIZE_IN_BYTES;
    EndBlock = (Address + Size - 1) / BLOCK_SIZE_IN_BYTES;
    BlockCnt = EndBlock - StartBlock + 1;

    for (i = 0; i < MAX_MEMORY_MAP_REGIONS; i++)
    {
        if (QSPI_MAP_Context.RegionSize[i] > 0)
        {
            if ((Address >= QSPI_MAP_Context.RegionBaseAddr[i] && 
                Address < (QSPI_MAP_Context.RegionBaseAddr[i] + QSPI_MAP_Context.RegionSize[i])) ||
                ((Address + Size) >= QSPI_MAP_Context.RegionBaseAddr[i] && 
                (Address + Size) < (QSPI_MAP_Context.RegionBaseAddr[i] + QSPI_MAP_Context.RegionSize[i])))
            {
                return QAPI_ERR_INVALID_PARAM;
            }
        }
    }

    for (i = 0; i < MAX_MEMORY_MAP_REGIONS; i++)
    {
        AvailableSize += (QSPI_MAP_Context.RegionSize[i] > 0 ? 0 : MEMORY_MAP_REGION_SIZE_IN_BLOCKS);
    }

    if (BlockCnt > AvailableSize)
    {
        return QAPI_ERR_NO_RESOURCE;
    }

    *RegionBits = 0;

    for (i = 0; i < MAX_MEMORY_MAP_REGIONS; i++)
    {
        if (QSPI_MAP_Context.RegionSize[i] == 0)
        {
            QSPI_MAP_Context.RegionBaseAddr[i] = StartBlock * BLOCK_SIZE_IN_BYTES;
            MapSize = (BlockCnt > MEMORY_MAP_REGION_SIZE_IN_BLOCKS ? MEMORY_MAP_REGION_SIZE_IN_BLOCKS : BlockCnt);
            QSPI_MAP_Context.RegionSize[i] = MapSize * BLOCK_SIZE_IN_BYTES;
            *RegionBits |= (1 << i);
            
            HWIO_PERIPH_QSPI_XIP_REGION_n_SIZE_OUTI(PERIPH_QSPI_REG_BASE, i + 1, 
                                                    (MapSize << HWIO_PERIPH_QSPI_XIP_REGION_n_SIZE_REGION_SIZE_SHFT));

            HWIO_PERIPH_QSPI_XIP_REGION_n_SPI_BASE_OUTI(PERIPH_QSPI_REG_BASE, i + 1,
                                                        (StartBlock << HWIO_PERIPH_QSPI_XIP_REGION_n_SPI_BASE_REGION_SPI_BASE_SHFT));
            
            StartBlock += MapSize;
            BlockCnt -= MapSize;

            if (BlockCnt == 0)
            {
                break;
            }
        }
    }
    return QAPI_OK;
}

/**
   @brief Enable or disable mapped system memory regions.

   @param[in] RegionBits  The region bits to be enabled or disabled.
   @param[in] Enable      true: enable, false: disable.

   @return QAPI_OK if success, or a negative value if there was an error.
*/
static qapi_Status_t QSPI_MAP_RegionEnable(uint32_t RegionBits, qbool_t Enable)
{
    uint32_t ModuleEnable;

    if (RegionBits & (~MEMORY_MAP_REGION_BMSK))
    {
        return QAPI_ERR_INVALID_PARAM;
    }
    
    /* Check module state. */
    if (!MemMapInitDone)
    {
        return QAPI_ERROR;
    }

    if (Enable)
    {
        QSPI_MAP_Context.RegionEnableBits |= RegionBits;
    }
    else
    {
        QSPI_MAP_Context.RegionEnableBits &= ~RegionBits;
    }

    if (QSPI_MAP_Context.RegionEnableBits == 0)
    {
        ModuleEnable = 0;
    }
    else
    {
        ModuleEnable = 1;
    }

    HWIO_PERIPH_QSPI_XIP_MASTER_CFG_OUTM(PERIPH_QSPI_REG_BASE,
                                        (HWIO_PERIPH_QSPI_XIP_MASTER_CFG_XIP_ENABLE_BMSK |
                                        (MEMORY_MAP_REGION_BMSK << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_1_SHFT)),
                                        ((ModuleEnable << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_XIP_ENABLE_SHFT) |
                                        (QSPI_MAP_Context.RegionEnableBits << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_ADDRESS_TRANSLATION_EN_REGION_1_SHFT)));
    return QAPI_OK;
    
}

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
qapi_Status_t QSPI_MAP_MemoryMap(uint32_t Address, uint32_t Size, QSPI_MAP_MemMapConfig_t *Config, void **MapHandle)
{
    qapi_Status_t Status;
    uint32_t     *RegionBits;

    if (Config == NULL || MapHandle == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    RegionBits = qapi_Malloc(sizeof(uint32_t));
    if (RegionBits == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    /* Module init. */
    if (!MemMapInitDone)
    {
        Status = QSPI_MAP_Init(Config);
        if (Status != QAPI_OK)
        {
            goto MEM_MAP_END;
        }
    }

    /* Set region and region size. */
    Status = QSPI_MAP_RegionMap(Address, Size, RegionBits);
    if (Status != QAPI_OK)
    {
        goto MEM_MAP_END;
    }

    /* Enable Region. */
    Status = QSPI_MAP_RegionEnable(*RegionBits, true);
    if (Status != QAPI_OK)
    {
        goto MEM_MAP_END;
    }

    *MapHandle = RegionBits;

 MEM_MAP_END:
    if (Status != QAPI_OK)
    {
        qapi_Free(RegionBits);
    }
    return Status;
}

/**
   @brief Unmap the part of flash memory from system memory.

   @param[in] MapHandle  The memory map handle.

   @return QAPI_OK if unmapping was successful, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_MemoryUnmap(void *MapHandle)
{
    qapi_Status_t Status;
    uint8_t       i;
    uint32_t      RegionBits = 0;
    
    /* Check module state. */
    if (!MemMapInitDone)
    {
        return QAPI_ERROR;
    }

    if (MapHandle == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    RegionBits = *(uint32_t *)MapHandle;

    if ((QSPI_MAP_Context.RegionEnableBits & RegionBits) == 0)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Status = QSPI_MAP_RegionEnable(RegionBits, false);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    for (i = 0; i < MAX_MEMORY_MAP_REGIONS; i++)
    {
        if (RegionBits & (1 << i))
        {
            QSPI_MAP_Context.RegionSize[i] = 0;
            QSPI_MAP_Context.RegionBaseAddr[i] = 0;
        }
    }

    qapi_Free(MapHandle);
    MapHandle = NULL;

    return Status;
}

/**
   @brief Get the mapped system address of a specific flash address.

   @param[in]  Address        Flash physical address.
   @param[out] MappedAddress  The mapped system address.

   @return QAPI_OK if getting address successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_GetMappedAddress(uint32_t Address, uint32_t *MappedAddress)
{
    uint8_t i;

    /* Check module state. */
    if (!MemMapInitDone)
    {
        return QAPI_ERROR;
    }

    if (MappedAddress == NULL)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    for (i = 0; i < MAX_MEMORY_MAP_REGIONS; i++)
    {
        if ((QSPI_MAP_Context.RegionEnableBits & (1 << i)) && QSPI_MAP_Context.RegionBaseAddr[i] <= Address &&
            (QSPI_MAP_Context.RegionBaseAddr[i] + QSPI_MAP_Context.RegionSize[i]) > Address)
        {
            *MappedAddress = (MEMORY_MAP_START_ADDRESS + i * MEMORY_MAP_REGION_SIZE + (Address - QSPI_MAP_Context.RegionBaseAddr[i]));
            return QAPI_OK;
        }
    }

    return QAPI_ERROR;
}

/**
   @brief Set flash program/erase ongoing state.

   @param[in] Ongoing  true: program/earse is ongoing, false: not ongoing.

   @return QAPI_OK if setting was successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_SetProgramEraseState(qbool_t Ongoing)
{
    uint32_t PeOngoing;
    
    /* Check module state. */
    if (!MemMapInitDone)
    {
        return QAPI_ERROR;
    }

    PeOngoing = Ongoing ? 1 : 0;
    HWIO_PERIPH_QSPI_XIP_MASTER_CFG_OUTM(PERIPH_QSPI_REG_BASE,
                                         HWIO_PERIPH_QSPI_XIP_MASTER_CFG_PROGRAM_ERASE_ONGOING_BMSK,
                                         (PeOngoing << HWIO_PERIPH_QSPI_XIP_MASTER_CFG_PROGRAM_ERASE_ONGOING_SHFT));

    return QAPI_OK;
}

/**
   @brief Configure flash suspend/resume.

   @param[in] SuspendDelay   Delay needed for suspend in-progress operation.
   @param[in] SuspendOpcode  Suspend opcode.
   @param[in] ResumeDelay    Delay needed after sending resume opcode.
   @param[in] ResumeOpcode   Resume opcode.

   @return QAPI_OK if configuration was successfully, or a negative value if
           there was an error.
*/
qapi_Status_t QSPI_MAP_ConfigSuspendResume(uint16_t SuspendDelay, uint8_t SuspendOpcode, uint16_t ResumeDelay, uint8_t ResumeOpcode)
{
    /* Check module state. */
    if (!MemMapInitDone)
    {
        return QAPI_ERROR;
    }
    
    /* Configure suspend phase. */
    HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                                (HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_OP_CODE_BMSK |
                                                HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_T_SUSPEND_PROG_DELAY_BMSK |
                                                HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_ENABLE_BMSK),
                                                (((((uint32_t)SuspendOpcode) << HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_OP_CODE_SHFT) &
                                                HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_OP_CODE_BMSK) |
                                                ((((uint32_t)SuspendDelay) << HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_T_SUSPEND_PROG_DELAY_SHFT) &
                                                HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_T_SUSPEND_PROG_DELAY_BMSK) |
                                                (SUSPEND_ENABLE << HWIO_PERIPH_QSPI_XIP_SUSPEND_PH_CONFIG_SUSPEND_ENABLE_SHFT)));

    /* Configure resume phase. */
    HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_OUTM(PERIPH_QSPI_REG_BASE,
                                               (HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_RESUME_OP_CODE_BMSK |
                                               HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_T_RESUME_PROG_DELAY_BMSK |
                                               HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_RESUME_ENABLE_BMSK),
                                               (((((uint32_t)ResumeOpcode) << HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_RESUME_OP_CODE_SHFT) &
                                               HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_RESUME_OP_CODE_BMSK) |
                                               ((((uint32_t)ResumeDelay) << HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_T_RESUME_PROG_DELAY_SHFT) &
                                               HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_T_RESUME_PROG_DELAY_BMSK) |
                                               (RESUME_ENABLE << HWIO_PERIPH_QSPI_XIP_RESUME_PH_CONFIG_RESUME_ENABLE_SHFT)));

    return QAPI_OK;
}
 
