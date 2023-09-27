/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_flash.h"
#include "qapi_task.h"
#include "qapi_timer.h"
#include "qapi_heap.h"
#include "qcli_api.h"
#include "qcli_util.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define FLASH_DBG
#ifdef FLASH_DBG
#define FLASH_PRINTF(...)         QCLI_Printf(QCLI_Flash_Handle, __VA_ARGS__)
#else
#define FLASH_PRINTF(x, ...)
#endif

#define BLOCK_SIZE_IN_BYTES       4096
#define TOTAL_OPERATION_TYPES     5
#define MAX_BUFFER_SIZE           4096
#define MAX_MAP_REGIONS           3

#define MIN(__a__, __b__)         (((__a__) > (__b__)) ? (__b__) : (__a__))

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of flash operation types.
*/
typedef enum
{
    FLASH_READ,          /**< Flash read. */
    FLASH_WRITE,         /**< Flash write. */
    FLASH_ERASE,         /**< Flash erase. */
    FLASH_READ_REG,      /**< Flash read register. */
    FLASH_WRITE_REG      /**< Flash write register. */
} FLASH_OperationType_t;

/**
   Structure representing the flash multiple operation parameters.
*/
typedef struct FLASH_MultiOperateParam_s
{
    uint32_t              BufferSize;      /**< Flash Operation buffer size. */
    uint32_t              CurAddress;      /**< Flash Operation current address. */
    uint32_t              CurSize;         /**< Flash Operation current size. */
    uint32_t              TriedSize;       /**< Last operation tried size. */
    uint64_t              EraseEndTime;    /**< Flash Erase end time. */
    uint64_t              WriteEndTime;    /**< Flash write end time. */
    uint64_t              ReadEndTime;     /**< Flash read end time. */
} FLASH_MultiOperateParam_t;

/**
   Structure representing the flash cmd operation parameters.
*/
typedef struct 
{
    FLASH_OperationType_t      Operation;       /**< Flash Operation type. */
    uint32_t                   StartAddress;    /**< Flash Operation start address. */
    uint32_t                   Size;            /**< Flash Operation size. */
    uint8_t                   *Buffer;          /**< Flash Operation buffer. */
    FLASH_MultiOperateParam_t *MultiOpParam;    /**< Flash multiple operations parameters. */
    uint64_t                   StartTime;       /**< Flash Operation start time. */
} FLASH_CmdParam_t;

/**
   Structure representing flash erase information.
   A part of flash can be erased using block_erase + bulk_erase + block_erase.
*/
typedef struct FLASH_EraseInfo_s
{
    uint32_t BlockStart;       /**< Pre block erase: start block number. */
    uint32_t BlockPreCnt;      /**< Pre block erase: number of blocks . */
    uint32_t BulkStart;        /**< Bulk erase: start bulk number. */
    uint32_t BulkCnt;          /**< Bulk erase: number of bulks. */
    uint32_t BlockEndStart;    /**< End block erase: start block number. */
    uint32_t BlockEndCnt;      /**< End block erase: number of blocks. */
} FLASH_EraseInfo_t;

/**
   Structure representing flash nor device information.
*/
typedef struct FLASH_DeviceInfo_s
{
    char                *ProductNumber; /**< Product number. */
    qapi_FLASH_Config_t  Config;        /**< Flash configurations. */
} FLASH_DeviceInfo_t;

/**
   Structure representing context for flash demo.
*/
typedef struct FLASH_DemoContext_s
{
    uint8_t ValidDeviceID; /**< Valid flash device ID */
    qbool_t InitDone;      /**< Flag representing flash init is done or not. */
} FLASH_DemoContext_t;

/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

/**
   Handle for flash QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Flash_Handle;

static FLASH_DemoContext_t FLASH_DemoContext;

static FLASH_DeviceInfo_t FLASH_DeviceInfo[] = 
{
    {   /* Macronix, MX25U51245G */
        .ProductNumber = "MX25U51245G",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 4,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0xEC,  /**< 4 I/O Fast read. */
            .ReadWaitState            = 6,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x3E,
            .Erase4kbOpcode           = 0x21,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xDC,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 2,
            .SuspendEraseOpcode       = 0xB0,
            .SuspendProgramOpcode     = 0xB0,
            .ResumeEraseOpcode        = 0x30,
            .ResumeProgramOpcode      = 0x30,
            .EraseErrBmsk             = 0x40, /* Error bit will be automatically cleared if next operation succeeds. */
            .EraseErrStatusReg        = 0x2B,
            .WriteErrBmsk             = 0x20, /* Error bit will be automatically cleared if next operation succeeds. */
            .WriteErrStatusReg        = 0x2B,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 15,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 360,
            .ResumeProgramDelayInUs   = 128,
            .DensityInBlocks          = 16384,
            .DeviceId                 = 0x003A25C2,
            .WriteProtectBmask        = 0xBC,
        },
    },
    {   /* WINBOND, W25Q16JW-IQ */
        .ProductNumber = "W25Q16JW",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 3,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0xEB,  /**< Fast read quad I/O. */
            .ReadWaitState            = 6,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x32,
            .Erase4kbOpcode           = 0x20,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xD8,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 5, 
            .SuspendEraseOpcode       = 0x75,
            .SuspendProgramOpcode     = 0x75,
            .ResumeEraseOpcode        = 0x7A,
            .ResumeProgramOpcode      = 0x7A,
            .EraseErrBmsk             = 0,
            .EraseErrStatusReg        = 0,
            .WriteErrBmsk             = 0,
            .WriteErrStatusReg        = 0,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 50,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 300,
            .ResumeProgramDelayInUs   = 100,
            .DensityInBlocks          = 512,
            .DeviceId                 = 0x001560EF,
            .WriteProtectBmask        = 0x0441FC,
        },
        
    },
    {   /* Macronix, MX25UM51245GXDI00 */
        .ProductNumber = "MX25UM51245G",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 4,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadOpcode               = 0x0C,  /**< Fast read. */
            .ReadWaitState            = 8,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteOpcode              = 0x12,
            .Erase4kbOpcode           = 0x21,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xdc,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 0, /**< Don't support quad mode. */
            .SuspendEraseOpcode       = 0xB0,
            .SuspendProgramOpcode     = 0xB0,
            .ResumeEraseOpcode        = 0x30,
            .ResumeProgramOpcode      = 0x30,
            .EraseErrBmsk             = 0x40,
            .EraseErrStatusReg        = 0x2B,
            .WriteErrBmsk             = 0x20,
            .WriteErrStatusReg        = 0x2B,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 15,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 360,
            .ResumeProgramDelayInUs   = 128,
            .DensityInBlocks          = 16384,
            .DeviceId                 = 0x003A80C2,
            .WriteProtectBmask        = 0xBC,
        },
    },
    {   /* ISSI, IS25LP016D-JNLE */
        .ProductNumber = "IS25LP016D",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 3,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0x6B,
            .ReadWaitState            = 8,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x32,
            .Erase4kbOpcode           = 0x20,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xD8,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 2,
            .SuspendEraseOpcode       = 0x75,
            .SuspendProgramOpcode     = 0x75,
            .ResumeEraseOpcode        = 0x7A,
            .ResumeProgramOpcode      = 0x7A,
            .EraseErrBmsk             = 0x08, /* Error bit must be cleared through CMD CLERP(82h). */
            .EraseErrStatusReg        = 0x81,
            .WriteErrBmsk             = 0x04, /* Error bit must be cleared through CMD CLERP(82h). */
            .WriteErrStatusReg        = 0x81,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 8,
            .SuspendEraseDelayInUs    = 100,
            .SuspendProgramDelayInUs  = 100,
            .ResumeEraseDelayInUs     = 400,
            .ResumeProgramDelayInUs   = 400,
            .DensityInBlocks          = 512,
            .DeviceId                 = 0x0015609D,
            .WriteProtectBmask        = 0xBC,
        },
    },
    {   /* WINBOND, W25Q16JV-IQ */
        .ProductNumber = "W25Q16JV",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 3,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0xEB,  /**< Fast read quad I/O. */
            .ReadWaitState            = 6,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x32,
            .Erase4kbOpcode           = 0x20,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xD8,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 5, 
            .SuspendEraseOpcode       = 0x75,
            .SuspendProgramOpcode     = 0x75,
            .ResumeEraseOpcode        = 0x7A,
            .ResumeProgramOpcode      = 0x7A,
            .EraseErrBmsk             = 0,
            .EraseErrStatusReg        = 0,
            .WriteErrBmsk             = 0,
            .WriteErrStatusReg        = 0,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 50,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 300,
            .ResumeProgramDelayInUs   = 100,
            .DensityInBlocks          = 512,
            .DeviceId                 = 0x001540EF,
            .WriteProtectBmask        = 0x0441FC,
        },
    },
    {   /* WINBOND, W25Q16JLSIG */
        .ProductNumber = "W25Q16JL",
        {
            .PowerUpOpcode            = 0xAB,
            .AddrBytes                = 3,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0xEB,  /**< Fast read quad I/O. */
            .ReadWaitState            = 6,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x32,
            .Erase4kbOpcode           = 0x20,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xD8,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 5, 
            .SuspendEraseOpcode       = 0x75,
            .SuspendProgramOpcode     = 0x75,
            .ResumeEraseOpcode        = 0x7A,
            .ResumeProgramOpcode      = 0x7A,
            .EraseErrBmsk             = 0,
            .EraseErrStatusReg        = 0,
            .WriteErrBmsk             = 0,
            .WriteErrStatusReg        = 0,
            .HighPerformanceModeBmask = 0,
            .PowerOnDelayIn100us      = 50,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 300,
            .ResumeProgramDelayInUs   = 100,
            .DensityInBlocks          = 512,
            .DeviceId                 = 0x001540EF,
            .WriteProtectBmask        = 0x0441FC,
        },
    },
    {   /* Macronix, MX25R3235FM1IL0 */
        .ProductNumber = "MX25R3235F",
        {
            .PowerUpOpcode            = 0,
            .AddrBytes                = 3,
            .ReadCmdMode              = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .ReadAddrMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadDataMode             = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .ReadOpcode               = 0xEB,  /**< 4 I/O Fast read. */
            .ReadWaitState            = 6,
            .WriteCmdMode             = QAPI_FLASH_RW_MODE_SDR_SINGLE,
            .WriteAddrMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteDataMode            = QAPI_FLASH_RW_MODE_SDR_QUAD,
            .WriteOpcode              = 0x38,
            .Erase4kbOpcode           = 0x20,
            .BulkEraseSizeIn4KB       = 16,
            .BulkEraseOpcode          = 0xD8,
            .ChipEraseOpcode          = 0x60,
            .QuadEnableMode           = 2,
            .SuspendEraseOpcode       = 0xB0,
            .SuspendProgramOpcode     = 0xB0,
            .ResumeEraseOpcode        = 0x30,
            .ResumeProgramOpcode      = 0x30,
            .EraseErrBmsk             = 0x40, /* Error bit will be automatically cleared if next operation succeeds. */
            .EraseErrStatusReg        = 0x2B,
            .WriteErrBmsk             = 0x20, /* Error bit will be automatically cleared if next operation succeeds. */
            .WriteErrStatusReg        = 0x2B,
            .HighPerformanceModeBmask = 0x2,
            .PowerOnDelayIn100us      = 8,
            .SuspendEraseDelayInUs    = 80,
            .SuspendProgramDelayInUs  = 80,
            .ResumeEraseDelayInUs     = 360,
            .ResumeProgramDelayInUs   = 128,
            .DensityInBlocks          = 1024,
            .DeviceId                 = 0x001628C2,
            .WriteProtectBmask        = 0xBC,
        },
    },
};

static const char *FLASH_OpContens[TOTAL_OPERATION_TYPES] = {"Read", "Write", "Erase", "Read reg", "Write reg"};

static uint8_t FLASH_Buffer[MAX_BUFFER_SIZE];

static qapi_FLASH_Map_Handle_t FLASH_MapHandle[MAX_MAP_REGIONS];

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static QCLI_Command_Status_t cmd_Flash_Init(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_Read(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_Write(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_Erase(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_ReadReg(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_WriteReg(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_MultiOperate(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void Flash_MultipleOperationCB(qapi_Status_t Status, void *UserParam);
static QCLI_Command_Status_t cmd_Flash_MemMap(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_MemUnmap(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Flash_GetMapAddr(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t FLASH_CMD_List[] =
{
    /* cmd_function          cmd_string    usage_string                                                                                                 description */
    {cmd_Flash_Init,         "Init",       "<Product> [RCmd] [RCmdMode] [RAddrMode] [RDataMode] [ReadDummy] [WCmd] [WCmdMode] [WAddrMode] [WDataMode]", "Init flash module"},
    {cmd_Flash_Read,         "Read",       "<Addr> <Cnt> <IsBlocking>",                                                                                 "Read data from flash"},
    {cmd_Flash_Write,        "Write",      "<Addr> <Cnt> <valueString> <IsBlocking>",                                                                   "Write data to flash"},
    {cmd_Flash_Erase,        "Erase",      "<Type> <Start> <Cnt> <IsBlocking>",                                                                         "Erase flash"},
    {cmd_Flash_ReadReg,      "ReadReg",    "<Opcode> <Len>",                                                                                            "Read flash registers"},
    {cmd_Flash_WriteReg,     "WriteReg",   "<Opcode> <Len] [ValueString] <IsBlocking>",                                                                 "Write flash registers"},
    {cmd_Flash_MultiOperate, "MultiOp",    "<Addr> <Cnt> <BufferSize> <IsBlocking>",                                                                    "Erase, Write and Read data"},
    {cmd_Flash_MemMap,       "MemMap",     "<Addr> <Size>",                                                                                             "Map flash address to system memory"},
    {cmd_Flash_MemUnmap,     "MemUnmap",   "<Region>",                                                                                                  "Unmap flash from system memory"},
    {cmd_Flash_GetMapAddr,   "GetMapAddr", "<Addr>",                                                                                                    "Get the mapped system address of flash"}
};

const QCLI_Command_Group_t FLASH_CMD_Group =
{
    "FLASH",
    (sizeof(FLASH_CMD_List) / sizeof(FLASH_CMD_List[0])),
    FLASH_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize flash demo.
*/
void Initialize_Flash_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Flash_Handle = QCLI_Register_Command_Group(NULL, &FLASH_CMD_Group);
    if(QCLI_Flash_Handle)
    {
        FLASH_PRINTF("FLASH Registered \n");
    }
}

/**
   @brief Check if the parameters which should be integer are valid integer.

   @param[in] Start_Count      Parameter start count to be checked.
   @param[in] Parameter_Count  Parameter count to be checked.
   @param[in] Parameter_List   Parameter list.

   @return true on success or false on failure.
*/
static qbool_t Flash_CheckValidIntParam(uint32_t Start_Count, uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t i;
    
    for (i = Start_Count; i < Start_Count + Parameter_Count; i++)
    {
        if (!Parameter_List[i].Integer_Is_Valid)
        {
            FLASH_PRINTF("Parameter %d should be valid integer\n", i);
            return false;
        }
    }

    return true;
}

/**
   @brief Flash init.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_Init(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    uint32_t      TotalProducts;
    uint32_t      i;

    if (FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash was already inited\n");
        return QCLI_STATUS_SUCCESS_E;
    }

    if ((Parameter_Count != 10 && Parameter_Count != 1) || Parameter_List == NULL)
    {
        FLASH_PRINTF("Init <Product> [RCmd] [RCmdMode] [RAddrMode] [RDataMode] [ReadDummy] [WCmd] [WCmdMode] [WAddrMode] [WDataMode]\n");
        FLASH_PRINTF("Parameter number should be 1 or 10\n");
        return QCLI_STATUS_ERROR_E;
    }

    TotalProducts = (sizeof(FLASH_DeviceInfo) / sizeof(FLASH_DeviceInfo[0]));

    for (i = 0; i < TotalProducts; i++)
    {
        if (!strcmp(Parameter_List[0].String_Value, FLASH_DeviceInfo[i].ProductNumber))
        {
            if (Parameter_Count == 10)
            {
                if (!Flash_CheckValidIntParam(1, 9, Parameter_List))
                {
                    return QCLI_STATUS_ERROR_E;
                }
                
                FLASH_DeviceInfo[i].Config.ReadOpcode = Parameter_List[1].Integer_Value;
                FLASH_DeviceInfo[i].Config.ReadCmdMode = Parameter_List[2].Integer_Value;
                FLASH_DeviceInfo[i].Config.ReadAddrMode = Parameter_List[3].Integer_Value;
                FLASH_DeviceInfo[i].Config.ReadDataMode = Parameter_List[4].Integer_Value;
                FLASH_DeviceInfo[i].Config.ReadWaitState = Parameter_List[5].Integer_Value;
                FLASH_DeviceInfo[i].Config.WriteOpcode = Parameter_List[6].Integer_Value;
                FLASH_DeviceInfo[i].Config.WriteCmdMode = Parameter_List[7].Integer_Value;
                FLASH_DeviceInfo[i].Config.WriteAddrMode = Parameter_List[8].Integer_Value;
                FLASH_DeviceInfo[i].Config.WriteDataMode = Parameter_List[9].Integer_Value;
            }
            
            Status = qapi_FLASH_Init(&FLASH_DeviceInfo[i].Config);
            if (Status != QAPI_OK)
            {
                FLASH_PRINTF("ERROR: Init failed %d\n", Status);
                return QCLI_STATUS_ERROR_E;
            }
            else
            {
                FLASH_DemoContext.ValidDeviceID = i;
                FLASH_DemoContext.InitDone = true;
                FLASH_PRINTF("Init success\n");
                return QCLI_STATUS_SUCCESS_E;
            }
        }
    }

    FLASH_PRINTF("ERROR: Wrong product number\n");
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Print result.

   @param[in] Status      Flash operation status.
   @param[in] Operation   Flash operation type.
   @param[in] Buffer      Buffer for read or write.
   @param[in] Len         Data length.
   @param[in] StartTime   Operation start time.
   @param[in] FlashParam  Cmd paramters.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t Flash_PrintResult(qapi_Status_t Status, FLASH_OperationType_t Operation, uint8_t *Buffer, uint32_t Len, uint64_t StartTime, FLASH_CmdParam_t *FlashParam)
{
    uint64_t              EndTime;
    uint32_t              i;
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;

    if (Status == QAPI_OK)
    {
        EndTime = qapi_TMR_Get_Current_Time();

        if (Operation == FLASH_READ || Operation == FLASH_READ_REG)
        {
            for (i = 0; i< Len; i++)
            {
                FLASH_PRINTF("%02x", Buffer[i]);
            }
        }
        
        FLASH_PRINTF("\n%s success, %lluus\n", FLASH_OpContens[Operation], (EndTime - StartTime));
    }
    else if (Status != QAPI_FLASH_STATUS_PENDING)
    {
        FLASH_PRINTF("%s failed %d\n", FLASH_OpContens[Operation], Status);
    }

    if (Status != QAPI_FLASH_STATUS_PENDING)
    {
        if (Buffer != NULL)
        {
            qapi_Free(Buffer);
        }
        
        if (FlashParam != NULL)
        {
            if (FlashParam->MultiOpParam != NULL)
            {
                qapi_Free(FlashParam->MultiOpParam);
            }
            qapi_Free(FlashParam);
        }
    }

    if (Status == QAPI_OK || Status == QAPI_FLASH_STATUS_PENDING)
    {
        CmdStatus = QCLI_STATUS_SUCCESS_E;
    }

    return CmdStatus;
}

/**
   @brief Initialize flash cmd paramters.

   @param[in] Opearation  Current operation.
   @param[in] Buffer      Buffer for read or write.
   @param[in] Len         Data length.
   @param[in] StartTime   Operation start time.

   @return Pointer pointed to the cmd parameters.
*/
static FLASH_CmdParam_t *Flash_InitParam(FLASH_OperationType_t Opearation, uint8_t *Buffer, uint32_t Len, uint64_t StartTime)
{
    FLASH_CmdParam_t *FlashParam = NULL;
    
    FlashParam = qapi_Malloc(sizeof(FLASH_CmdParam_t));
    if (FlashParam == NULL)
    {
        FLASH_PRINTF("ERROR: No enough memory\n");
        if (Buffer != NULL)
        {
            qapi_Free(Buffer);
        }
        return NULL;
    }
    memset(FlashParam, 0, sizeof(FLASH_CmdParam_t));
    FlashParam->Operation = Opearation;
    FlashParam->Buffer = Buffer;
    FlashParam->Size = Len;
    FlashParam->StartTime = StartTime;

    return FlashParam;
}

/**
   @brief Get written data.

   @param[in] InputString  Input string.
   @param[in] Len          Input Length.

   @return Allocated buffer that stores written data.
*/
static uint8_t *Flash_GetWriteData(char *InputString, uint32_t Len)
{
    uint8_t *Buffer = NULL;
    uint32_t RequiredLen;
    qbool_t  ConvertResult;
    
    if (strlen(InputString) != Len * 2)
    {
        FLASH_PRINTF("ERROR: ValueString length does not match with Cnt\n");
        return NULL;
    }

    Buffer = qapi_Malloc(Len);
    if (Buffer == NULL)
    {
        FLASH_PRINTF("ERROR: No enough momory\n");
        return NULL;
    }
    memset(Buffer, 0, Len);

    RequiredLen = Len;
    ConvertResult = QCLI_Hex_String_To_Array(InputString, &RequiredLen, Buffer);
    
    if (!ConvertResult || RequiredLen != Len)
    {
        qapi_Free(Buffer);
        FLASH_PRINTF("ERROR: Valid value length does not match with Cnt\n");
        return NULL;
    }

    return Buffer;
}

/**
   @brief Flash command non-blocking operation callback.

   @param[in] Status     Flash operation status.
   @param[in] UserParam  User specified paramter for the callback function.
*/
static void Flash_CmdOperationCB(qapi_Status_t Status, void *UserParam)
{
    FLASH_CmdParam_t *FlashParam = (FLASH_CmdParam_t *)UserParam;

    (void)Flash_PrintResult(Status, FlashParam->Operation, FlashParam->Buffer, FlashParam->Size, FlashParam->StartTime, FlashParam);
}

/**
   @brief Flash read test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_Read(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t              Address;
    uint32_t              ByteCnt;
    qbool_t               IsBlocking;
    uint8_t              *Buffer = NULL;
    uint64_t              StartTime;
    FLASH_CmdParam_t     *FlashParam = NULL;
    qapi_Status_t         FlashStatus;
    QCLI_Command_Status_t CmdStatus;

    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 3 || Parameter_List == NULL || 
        Parameter_List[0].Integer_Value < 0 || Parameter_List[1].Integer_Value <= 0 ||
        (Parameter_List[2].Integer_Value != 0 && Parameter_List[2].Integer_Value != 1))
    {
        FLASH_PRINTF("Read <Addr> <Cnt> <IsBlocking>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 3, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Address = Parameter_List[0].Integer_Value;
    ByteCnt = Parameter_List[1].Integer_Value;
    IsBlocking = Parameter_List[2].Integer_Value;

    Buffer = qapi_Malloc(ByteCnt);
    if (Buffer == NULL)
    {
        FLASH_PRINTF("ERROR: No enough memory\n");
        return QCLI_STATUS_ERROR_E;
    }
    memset(Buffer, 0, ByteCnt);

    StartTime = qapi_TMR_Get_Current_Time();
    
    if (IsBlocking)
    {
        FlashStatus = qapi_FLASH_Read(Address, ByteCnt, Buffer, NULL, NULL);
    }
    else
    {
        FlashParam = Flash_InitParam(FLASH_READ, Buffer, ByteCnt, StartTime);
        if (FlashParam == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }
        
        FlashStatus = qapi_FLASH_Read(Address, ByteCnt, Buffer, Flash_CmdOperationCB, (void *)FlashParam);
    }

    CmdStatus = Flash_PrintResult(FlashStatus, FLASH_READ, Buffer, ByteCnt, StartTime, FlashParam);
    return CmdStatus;
}

/**
   @brief Flash write test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_Write(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t              Address;
    uint32_t              ByteCnt;
    qbool_t               IsBlocking;
    uint8_t              *Buffer = NULL;
    uint64_t              StartTime;
    qapi_Status_t         FlashStatus;
    FLASH_CmdParam_t     *FlashParam = NULL;
    QCLI_Command_Status_t CmdStatus;
    
    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 4 || Parameter_List == NULL || 
        Parameter_List[0].Integer_Value < 0 || Parameter_List[1].Integer_Value <= 0 ||
        (Parameter_List[3].Integer_Value != 0 && Parameter_List[3].Integer_Value != 1))
    {
        FLASH_PRINTF("Write <Addr> <Cnt> <ValueString> <IsBlocking>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 2, Parameter_List) || !Flash_CheckValidIntParam(3, 1, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Address = Parameter_List[0].Integer_Value;
    ByteCnt = Parameter_List[1].Integer_Value;
    IsBlocking = Parameter_List[3].Integer_Value;

    Buffer = Flash_GetWriteData(Parameter_List[2].String_Value, ByteCnt);
    if (Buffer == NULL)
    {
        return QCLI_STATUS_ERROR_E;
    }
        
    StartTime = qapi_TMR_Get_Current_Time();
    
    if (IsBlocking)
    {
        FlashStatus = qapi_FLASH_Write(Address, ByteCnt, Buffer, NULL, NULL);
    }
    else 
    {
        FlashParam = Flash_InitParam(FLASH_WRITE, Buffer, ByteCnt, StartTime);
        if (FlashParam == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }

        FlashStatus = qapi_FLASH_Write(Address, ByteCnt, Buffer, Flash_CmdOperationCB, (void *)FlashParam);
    }

    CmdStatus = Flash_PrintResult(FlashStatus, FLASH_WRITE, Buffer, ByteCnt, StartTime, FlashParam);
    return CmdStatus;
}

/**
   @brief Flash erase test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_Erase(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_FLASH_Erase_Type_t EraseType;
    uint32_t                Start;
    uint32_t                Cnt;
    qbool_t                 IsBlocking;
    uint64_t                StartTime;
    FLASH_CmdParam_t       *FlashParam = NULL;
    qapi_Status_t           FlashStatus;
    QCLI_Command_Status_t   CmdStatus;
    
    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 4 || Parameter_List == NULL || Parameter_List[0].Integer_Value < 0 || 
        Parameter_List[1].Integer_Value < 0 || Parameter_List[2].Integer_Value <= 0 || 
        (Parameter_List[3].Integer_Value != 0 && Parameter_List[3].Integer_Value != 1))
    {
        FLASH_PRINTF("Erase <Type> <Start> <Cnt> <IsBlocking>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 4, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    EraseType = (qapi_FLASH_Erase_Type_t)Parameter_List[0].Integer_Value;
    Start = Parameter_List[1].Integer_Value;
    Cnt = Parameter_List[2].Integer_Value;
    IsBlocking = Parameter_List[3].Integer_Value;

    StartTime = qapi_TMR_Get_Current_Time();
    if (IsBlocking)
    {
        FlashStatus = qapi_FLASH_Erase(EraseType, Start, Cnt, NULL, NULL);
    }
    else
    {
        FlashParam = Flash_InitParam(FLASH_ERASE, NULL, 0, StartTime);
        if (FlashParam == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }

        FlashStatus = qapi_FLASH_Erase(EraseType, Start, Cnt, Flash_CmdOperationCB, (void *)FlashParam);
    }

    CmdStatus = Flash_PrintResult(FlashStatus, FLASH_ERASE, NULL, 0, StartTime, FlashParam);
    return CmdStatus;
}

/**
   @brief Flash read register test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_ReadReg(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint8_t               Opcode;
    uint8_t               Len;
    uint8_t              *RegValue = NULL;
    uint64_t              StartTime;
    qapi_Status_t         FlashStatus;
    QCLI_Command_Status_t CmdStatus;

    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 2 || Parameter_List == NULL || Parameter_List[1].Integer_Value < 0)
    {
        FLASH_PRINTF("ReadReg <Opcode> <Len>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 2, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Opcode = Parameter_List[0].Integer_Value;
    Len = Parameter_List[1].Integer_Value;

    if (Len > 0)
    {
        RegValue = qapi_Malloc(Len);
        if (RegValue == NULL)
        {
            FLASH_PRINTF("ERROR: No enough memory\n");
            return QCLI_STATUS_ERROR_E;
        }
        memset(RegValue, 0, Len);
    }

    StartTime = qapi_TMR_Get_Current_Time();
    FlashStatus = qapi_FLASH_Read_Reg(Opcode, Len, RegValue);
    
    CmdStatus = Flash_PrintResult(FlashStatus, FLASH_READ_REG, RegValue, Len, StartTime, NULL);
    return CmdStatus;
}

/**
   @brief Flash write register test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_WriteReg(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint8_t               Opcode;
    uint8_t               Len;
    uint8_t              *RegValue = NULL;
    qbool_t               IsBlocking;
    uint64_t              StartTime;
    FLASH_CmdParam_t     *FlashParam = NULL;
    qapi_Status_t         FlashStatus;
    QCLI_Command_Status_t CmdStatus;

    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count < 3 || Parameter_List == NULL || Parameter_List[1].Integer_Value < 0 ||
        (Parameter_List[1].Integer_Value == 0 && Parameter_Count != 3) ||
        (Parameter_List[1].Integer_Value > 0 && Parameter_Count != 4))
    {
        FLASH_PRINTF("WriteReg <Opcode> <Len> [ValueString] <IsBlocking>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 2, Parameter_List) || (Parameter_Count == 3 && !Flash_CheckValidIntParam(2, 1, Parameter_List)) ||
        (Parameter_Count == 4 && !Flash_CheckValidIntParam(3, 1, Parameter_List)))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Opcode = Parameter_List[0].Integer_Value;
    Len = Parameter_List[1].Integer_Value;

    if (Len > 0)
    {
        RegValue = Flash_GetWriteData(Parameter_List[2].String_Value, Len);
        if (RegValue == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }

        IsBlocking = Parameter_List[3].Integer_Value;
    }
    else
    {
        IsBlocking = Parameter_List[2].Integer_Value;
    }

    StartTime = qapi_TMR_Get_Current_Time();
    
    if (IsBlocking)
    {
        FlashStatus = qapi_FLASH_Write_Reg(Opcode, Len, RegValue, NULL, NULL);
    }
    else 
    {
        FlashParam = Flash_InitParam(FLASH_WRITE_REG, RegValue, Len, StartTime);
        if (FlashParam == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }

        FlashStatus = qapi_FLASH_Write_Reg(Opcode, Len, RegValue, Flash_CmdOperationCB, (void*)FlashParam);
    }
    
    CmdStatus = Flash_PrintResult(FlashStatus, FLASH_WRITE_REG, RegValue, Len, StartTime, FlashParam);
    return CmdStatus;
}

/**
   @brief Flash unit test non-blocking read.

   @param[in] FlashParam  Flash operation parameters.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t Flash_MultiOperateRead(FLASH_CmdParam_t *FlashParam)
{
    uint32_t      i;
    qapi_Status_t FlashStatus;
    
    if (FlashParam->MultiOpParam->CurSize == 0)
    {
        FlashParam->MultiOpParam->CurSize = FlashParam->Size;
        FlashParam->MultiOpParam->CurAddress = FlashParam->StartAddress;
        FlashParam->MultiOpParam->TriedSize = (FlashParam->Size > FlashParam->MultiOpParam->BufferSize) ? FlashParam->MultiOpParam->BufferSize : FlashParam->Size;
    }
    else
    {
        for (i = 0; i< FlashParam->MultiOpParam->TriedSize; i++)
        {
            if (FLASH_Buffer[i] != (i & 0xFF))
            {
                FLASH_PRINTF("ERROR: Read data did not match with written data\n");
                return QAPI_ERROR;;
            }
        }
        
        FlashParam->MultiOpParam->CurAddress += FlashParam->MultiOpParam->TriedSize;
        FlashParam->MultiOpParam->CurSize -= FlashParam->MultiOpParam->TriedSize;

        if (FlashParam->MultiOpParam->CurSize > 0)
        {
            FlashParam->MultiOpParam->TriedSize = (FlashParam->MultiOpParam->CurSize > FlashParam->MultiOpParam->BufferSize) ? FlashParam->MultiOpParam->BufferSize : FlashParam->MultiOpParam->CurSize;
        }
        else
        {
            FlashParam->MultiOpParam->ReadEndTime = qapi_TMR_Get_Current_Time();
            /* Finish. */
            FLASH_PRINTF("Unit test success, erase %lluus, write %lluus, read %lluus\n", (FlashParam->MultiOpParam->EraseEndTime - FlashParam->StartTime), (FlashParam->MultiOpParam->WriteEndTime - FlashParam->MultiOpParam->EraseEndTime), (FlashParam->MultiOpParam->ReadEndTime - FlashParam->MultiOpParam->WriteEndTime));
            /* Free memory. */
            qapi_Free(FlashParam->MultiOpParam);
            qapi_Free(FlashParam);
            return QAPI_OK;
        }
    }

    memset(FLASH_Buffer, 0, FlashParam->MultiOpParam->TriedSize);
    FlashStatus = qapi_FLASH_Read(FlashParam->MultiOpParam->CurAddress, FlashParam->MultiOpParam->TriedSize, FLASH_Buffer, Flash_MultipleOperationCB, (void *)FlashParam);

    return FlashStatus;
}

/**
   @brief Flash unit test non-blocking write.

   @param[in] FlashParam  Flash operation parameters.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t Flash_MultiOperateWrite(FLASH_CmdParam_t *FlashParam)
{
    qapi_Status_t FlashStatus;
    uint32_t      i;

    if (FlashParam->MultiOpParam->CurSize == 0)
    {
        FlashParam->MultiOpParam->CurSize = FlashParam->Size;
        FlashParam->MultiOpParam->CurAddress = FlashParam->StartAddress;
        FlashParam->MultiOpParam->TriedSize = (FlashParam->Size > FlashParam->MultiOpParam->BufferSize) ? FlashParam->MultiOpParam->BufferSize : FlashParam->Size;
        
        for (i = 0; i < FlashParam->MultiOpParam->BufferSize; i++)
        {
            FLASH_Buffer[i] = (i & 0xFF);
        }
    }
    else
    {
        FlashParam->MultiOpParam->CurAddress += FlashParam->MultiOpParam->TriedSize;
        FlashParam->MultiOpParam->CurSize -= FlashParam->MultiOpParam->TriedSize;

        if (FlashParam->MultiOpParam->CurSize > 0)
        {
            FlashParam->MultiOpParam->TriedSize = (FlashParam->MultiOpParam->CurSize > FlashParam->MultiOpParam->BufferSize) ? FlashParam->MultiOpParam->BufferSize : FlashParam->MultiOpParam->CurSize;
        }
        else
        {
            FlashParam->MultiOpParam->WriteEndTime = qapi_TMR_Get_Current_Time();
            FlashParam->Operation = FLASH_READ;
            return QAPI_OK;
        }
    }

    FlashStatus = qapi_FLASH_Write(FlashParam->MultiOpParam->CurAddress, FlashParam->MultiOpParam->TriedSize, FLASH_Buffer, Flash_MultipleOperationCB, FlashParam);
    return FlashStatus;
}

/**
   @brief Flash unit test non-blocking erase.

   @param[in]  StartAddress  Flash erase start address.
   @param[in]  Cnt           Flash erase count.
   @param[out] EraseInfo     Flash erase information.
*/
static void Flash_GetEraseInfo(uint32_t StartAddress, uint32_t Cnt, FLASH_EraseInfo_t *EraseInfo)
{
    uint32_t BulkEnd = 0;
    
    if (EraseInfo == NULL)
    {
        return;
    }

    memset(EraseInfo, 0, sizeof(FLASH_EraseInfo_t));

    EraseInfo->BlockStart = StartAddress / BLOCK_SIZE_IN_BYTES;
    if (FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB > 0 && Cnt >= (BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB))
    {
        EraseInfo->BulkStart = StartAddress / (BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB);
        if (EraseInfo->BulkStart * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB < EraseInfo->BlockStart)
        {
            EraseInfo->BulkStart += 1;
        }

        BulkEnd = (StartAddress + Cnt - 1) / (BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB);
        if ((StartAddress + Cnt) % (BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB))
        {
            BulkEnd -= 1;
        }

        if (BulkEnd >= EraseInfo->BulkStart)
        {
            EraseInfo->BulkCnt = BulkEnd - EraseInfo->BulkStart + 1;
        }
    }

    if (EraseInfo->BulkCnt > 0)
    {
        EraseInfo->BlockPreCnt = EraseInfo->BulkStart * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB - EraseInfo->BlockStart;
    
        EraseInfo->BlockEndStart = (EraseInfo->BulkStart + EraseInfo->BulkCnt) * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB;
        if (EraseInfo->BlockEndStart <= ((StartAddress + Cnt - 1) / BLOCK_SIZE_IN_BYTES))
        {
            EraseInfo->BlockEndCnt = (StartAddress + Cnt - 1) / BLOCK_SIZE_IN_BYTES - EraseInfo->BlockEndStart + 1;
        }
        
    }
    else
    {
        EraseInfo->BlockPreCnt = (StartAddress + Cnt - 1) / BLOCK_SIZE_IN_BYTES - EraseInfo->BlockStart + 1;
    }
}

/**
   @brief Flash unit test non-blocking erase.

   @param[in] FlashParam  Flash operation parameters.

   @return QAPI_OK on success or an error code on failure.
*/
static qapi_Status_t Flash_MultiOperateErase(FLASH_CmdParam_t *FlashParam)
{
    FLASH_EraseInfo_t EraseInfo;
    qapi_Status_t     FlashStatus = QAPI_OK;

    FlashParam->MultiOpParam->CurAddress += FlashParam->MultiOpParam->TriedSize;
    FlashParam->MultiOpParam->CurSize -= FlashParam->MultiOpParam->TriedSize;

    if (FlashParam->MultiOpParam->CurSize > 0)
    {
        Flash_GetEraseInfo(FlashParam->MultiOpParam->CurAddress, FlashParam->MultiOpParam->CurSize, &EraseInfo);
        if (EraseInfo.BlockPreCnt > 0)
        {
            FlashParam->MultiOpParam->TriedSize = MIN(EraseInfo.BlockPreCnt * BLOCK_SIZE_IN_BYTES, FlashParam->MultiOpParam->CurSize);
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseInfo.BlockStart, EraseInfo.BlockPreCnt, Flash_MultipleOperationCB, FlashParam);
        }
        else
        {
            FlashParam->MultiOpParam->TriedSize = MIN(EraseInfo.BulkCnt * BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB, FlashParam->MultiOpParam->CurSize);
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BULK_ERASE_E, EraseInfo.BulkStart, EraseInfo.BulkCnt, Flash_MultipleOperationCB, FlashParam);
        }
    }
    else
    {
        FlashParam->MultiOpParam->EraseEndTime = qapi_TMR_Get_Current_Time();
        FlashParam->Operation = FLASH_WRITE;
    }

    return FlashStatus;
}

/**
   @brief Flash unit test non-blocking operation callback.

   @param[in] Status     Flash operation status.
   @param[in] UserParam  User specified paramter for the callback function.
*/
static void Flash_MultipleOperationCB(qapi_Status_t Status, void *UserParam)
{
    FLASH_CmdParam_t *FlashParam = (FLASH_CmdParam_t *)UserParam;

    if (Status == QAPI_OK)
    {
        if (FlashParam->Operation == FLASH_ERASE)
        {
            Status = Flash_MultiOperateErase(FlashParam);
        }

        if (FlashParam->Operation == FLASH_WRITE)
        {
            Status = Flash_MultiOperateWrite(FlashParam);
        }

        if (FlashParam->Operation == FLASH_READ)
        {
            Status = Flash_MultiOperateRead(FlashParam);
        }
    }

    if (Status != QAPI_OK)
    {
        (void)Flash_PrintResult(Status, FlashParam->Operation, FlashParam->Buffer, FlashParam->Size, FlashParam->StartTime, FlashParam);
    }
}

/**
   @brief Flash multioperation test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_MultiOperate(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t              StartAddress;
    uint32_t              Cnt;
    uint32_t              BufferSize;
    qbool_t               IsBlocking;
    uint32_t              TotalRwSize;
    uint32_t              StartRwAddress;
    uint32_t              RwSize;
    uint32_t              i;
    uint64_t              StartTime;
    uint64_t              EraseEndTime;
    uint64_t              WriteEndTime;
    uint64_t              ReadEndTime;
    FLASH_CmdParam_t     *FlashCmd = NULL;
    FLASH_EraseInfo_t     EraseInfo;
    FLASH_OperationType_t Operation;
    qapi_Status_t         FlashStatus;
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;

    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    if (Parameter_Count != 4 || Parameter_List == NULL || Parameter_List[0].Integer_Value < 0 ||
        Parameter_List[1].Integer_Value <= 0 || Parameter_List[2].Integer_Value <= 0 || Parameter_List[2].Integer_Value > MAX_BUFFER_SIZE ||
        (Parameter_List[3].Integer_Value != 0 && Parameter_List[3].Integer_Value != 1))
    {
        FLASH_PRINTF("MultiOp <Addr> <Cnt> <BufferSize> <IsBlocking>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 4, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    StartAddress = Parameter_List[0].Integer_Value;
    Cnt = Parameter_List[1].Integer_Value;
    BufferSize = Parameter_List[2].Integer_Value;
    IsBlocking = Parameter_List[3].Integer_Value;

    BufferSize = (BufferSize > Cnt) ? Cnt : BufferSize;
    StartTime = qapi_TMR_Get_Current_Time();
    
    if (IsBlocking)
    {
        Operation = FLASH_ERASE;
        Flash_GetEraseInfo(StartAddress, Cnt, &EraseInfo);

        if (EraseInfo.BlockPreCnt > 0)
        {
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseInfo.BlockStart, EraseInfo.BlockPreCnt, NULL, NULL);
            if (FlashStatus != QAPI_OK)
            {
                goto CMD_UINT_TEST_END;
            }
        }

        if (EraseInfo.BulkCnt > 0)
        {
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BULK_ERASE_E, EraseInfo.BulkStart, EraseInfo.BulkCnt, NULL, NULL);
            if (FlashStatus != QAPI_OK)
            {
                goto CMD_UINT_TEST_END;
            }
        }

        if (EraseInfo.BlockEndCnt > 0)
        {
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseInfo.BlockEndStart, EraseInfo.BlockEndCnt, NULL, NULL);
            if (FlashStatus != QAPI_OK)
            {
                goto CMD_UINT_TEST_END;
            }
        }

        EraseEndTime = qapi_TMR_Get_Current_Time();

        Operation = FLASH_WRITE;
        TotalRwSize = Cnt;
        StartRwAddress = StartAddress;
        for (i = 0; i < BufferSize; i++)
        {
            FLASH_Buffer[i] = (i & 0xFF);
        }
        
        while (TotalRwSize)
        {
            RwSize = TotalRwSize > BufferSize ? BufferSize : TotalRwSize;

            FlashStatus = qapi_FLASH_Write(StartRwAddress, RwSize, FLASH_Buffer, NULL, NULL);
            if (FlashStatus != QAPI_OK)
            {
                goto CMD_UINT_TEST_END;
            }

            TotalRwSize -= RwSize;
            StartRwAddress += RwSize;
        }
        
        WriteEndTime = qapi_TMR_Get_Current_Time();

        Operation = FLASH_READ;
        TotalRwSize = Cnt;
        StartRwAddress = StartAddress;
        while (TotalRwSize)
        {
            RwSize = TotalRwSize > BufferSize ? BufferSize : TotalRwSize;
            memset(FLASH_Buffer, 0, RwSize);

            FlashStatus = qapi_FLASH_Read(StartRwAddress, RwSize, FLASH_Buffer, NULL, NULL);
            if (FlashStatus != QAPI_OK)
            {
                goto CMD_UINT_TEST_END;
            }

            for (i = 0; i < RwSize; i++)
            {
                if (FLASH_Buffer[i] != (i & 0xFF))
                {
                    FLASH_PRINTF("ERROR: Read data did not match with written data\n");
                    FlashStatus = QAPI_ERROR;
                    goto CMD_UINT_TEST_END;
                }
            }

            TotalRwSize -= RwSize;
            StartRwAddress += RwSize;
        }
        
        ReadEndTime = qapi_TMR_Get_Current_Time();
        FLASH_PRINTF("Unit test success, erase %lluus, write %lluus, read %lluus\n", (EraseEndTime - StartTime), (WriteEndTime - EraseEndTime), (ReadEndTime - WriteEndTime));
        return QCLI_STATUS_SUCCESS_E;
    }
    else
    {
        FlashCmd = Flash_InitParam(FLASH_ERASE, NULL, Cnt, StartTime);
        if (FlashCmd == NULL)
        {
            return QCLI_STATUS_ERROR_E;
        }
        
        FlashCmd->MultiOpParam= qapi_Malloc(sizeof(FLASH_MultiOperateParam_t));
        if (FlashCmd->MultiOpParam == NULL)
        {
            FLASH_PRINTF("ERROR: No enough momory\n");
            qapi_Free(FlashCmd);
            return QCLI_STATUS_ERROR_E;
        }
        memset(FlashCmd->MultiOpParam, 0, sizeof(FLASH_MultiOperateParam_t));
        FlashCmd->StartAddress = StartAddress;
        FlashCmd->MultiOpParam->CurAddress = StartAddress;
        FlashCmd->MultiOpParam->CurSize = Cnt;
        FlashCmd->MultiOpParam->BufferSize = BufferSize;

        Operation = FLASH_ERASE;
        Flash_GetEraseInfo(StartAddress, Cnt, &EraseInfo);
        
        if (EraseInfo.BlockPreCnt > 0)
        {
            FlashCmd->MultiOpParam->TriedSize = MIN(EraseInfo.BlockPreCnt * BLOCK_SIZE_IN_BYTES, FlashCmd->MultiOpParam->CurSize);
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseInfo.BlockStart, EraseInfo.BlockPreCnt, Flash_MultipleOperationCB, (void *)FlashCmd);
        }
        else
        {
            FlashCmd->MultiOpParam->TriedSize = MIN(EraseInfo.BulkCnt * BLOCK_SIZE_IN_BYTES * FLASH_DeviceInfo[FLASH_DemoContext.ValidDeviceID].Config.BulkEraseSizeIn4KB, FlashCmd->MultiOpParam->CurSize);
            FlashStatus = qapi_FLASH_Erase(QAPI_FLASH_BULK_ERASE_E, EraseInfo.BulkStart, EraseInfo.BulkCnt, Flash_MultipleOperationCB, (void *)FlashCmd);
        }
    }

CMD_UINT_TEST_END:
    CmdStatus = Flash_PrintResult(FlashStatus, Operation, NULL, Cnt, StartTime, FlashCmd);
    return CmdStatus;
}

/**
   @brief Flash memory map test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_MemMap(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint8_t                 i;
    uint32_t                Address;
    uint32_t                Size;
    qapi_Status_t           FlashStatus;
    qapi_FLASH_Map_Handle_t MapHandle = NULL;
    
    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 2 || Parameter_List == NULL || Parameter_List[0].Integer_Value < 0 || Parameter_List[1].Integer_Value <= 0)
    {
        FLASH_PRINTF("MemMap <Addr> <Size>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 2, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Address = Parameter_List[0].Integer_Value;
    Size = Parameter_List[1].Integer_Value;

    FlashStatus = qapi_FLASH_Memory_Map(Address, Size, &MapHandle);
    
    if (QAPI_OK == FlashStatus)
    {
        for (i = 0; i < MAX_MAP_REGIONS; i++)
        {
            if ((*(uint32_t *)MapHandle) & (1 << i))
            {
                FLASH_MapHandle[i] = MapHandle;
                break;
            }
        }
            
        FLASH_PRINTF("MemMap to region %d successfully", i);
        return QCLI_STATUS_SUCCESS_E;
    }
    
    FLASH_PRINTF("MemMap failed %d", FlashStatus);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Flash memory unmap test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_MemUnmap(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t      Region;
    qapi_Status_t FlashStatus;
    
    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 1 || Parameter_List == NULL || Parameter_List[0].Integer_Value < 0 || Parameter_List[0].Integer_Value >= MAX_MAP_REGIONS)
    {
        FLASH_PRINTF("MemUnmap <Region>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 1, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Region = Parameter_List[0].Integer_Value;

    FlashStatus = qapi_FLASH_Memory_Unmap(FLASH_MapHandle[Region]);
    
    if (QAPI_OK == FlashStatus)
    {
        FLASH_MapHandle[Region] = NULL;
        FLASH_PRINTF("MemUnmap region %d successfully", Region);
        return QCLI_STATUS_SUCCESS_E;
    }
    
    FLASH_PRINTF("MemUmapMap failed %d", FlashStatus);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Get mapped flash address test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Flash_GetMapAddr(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t      Address;
    uint32_t      MapAddress;
    qapi_Status_t FlashStatus;
    
    if (!FLASH_DemoContext.InitDone)
    {
        FLASH_PRINTF("Flash is not inited\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_Count != 1 || Parameter_List == NULL || Parameter_List[0].Integer_Value < 0)
    {
        FLASH_PRINTF("GetMapAddr <Addr>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (!Flash_CheckValidIntParam(0, 1, Parameter_List))
    {
        return QCLI_STATUS_ERROR_E;
    }

    Address = Parameter_List[0].Integer_Value;

    FlashStatus = qapi_FLASH_Get_Mapped_Address(Address, &MapAddress);

    if (QAPI_OK == FlashStatus)
    {
        FLASH_PRINTF("The Mapped address is 0x%x", MapAddress);
        return QCLI_STATUS_SUCCESS_E;
    }
    
    FLASH_PRINTF("GetMapAddr failed %d", FlashStatus);
    return QCLI_STATUS_ERROR_E;
}

