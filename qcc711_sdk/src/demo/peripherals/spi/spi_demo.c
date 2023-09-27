/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <string.h>

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_spi.h"
#include "qapi_flash.h"
#include "qcli_pal.h"
#include "qcli.h"
#include "qcli_api.h"
#include "spi_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define SPI_DBG
#ifdef SPI_DBG
#define SPI_PRINTF(...)     QCLI_Printf(QCLI_Spi_Handle, __VA_ARGS__)
#else
#define SPI_PRINTF(x, ...)
#endif

#define SPI_CMD_CONSTDATA(Num)      Num, Num, Num, Num, Num, Num, Num, Num, Num, Num, Num, Num

#define SPI_CMD_BUFLEN_MIN          1
#define SPI_CMD_BUFLEN_MAX          1728
#define SPI_CMD_PATTERN             0xA5
#define SPI_CMD_COMPLETE_EVENT      0x1
#define SPI_CMD_DUMP                0

#define FLASH_BLOCK_SIZE_IN_BYTES   4096

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum
{
    SPI_CMD_DATA_FROM_SRAM,
    SPI_CMD_DATA_FROM_RRAM,
    SPI_CMD_DATA_FROM_FLASHMEM
} SPI_CMD_DataSource_t;

typedef enum
{
    SPI_CMD_TEST_MODE_HW_LOOPBACK,  /* Master mode only, hardware loopback */
    SPI_CMD_TEST_MODE_SW_LOOPBACK,  /* Software loopback: between local Master and Slave */
    SPI_CMD_TEST_MODE_NORMAL,       /* non-loopback test */
} SPI_CMD_TestMode_t;

typedef enum
{
    SPI_CMD_DIR_MASTER_TO_SLAVE,
    SPI_CMD_DIR_SLAVE_TO_MASTER,
    SPI_CMD_DIR_DUPLEX,
} SPI_CMD_Direction_t;

typedef struct SPI_CMD_Info_s
{
    uint8_t Busy;
    uint8_t SwLoopbackDone;
    SPI_CMD_Direction_t Direction;
    SPI_CMD_DataSource_t DataSource;
    SPI_CMD_TestMode_t TestMode;
    uint32_t TestCount;
    uint32_t TestIndex;
    uint32_t SuccessCount;
    uint32_t FailureCount;
} SPI_CMD_Info_t;

typedef struct SPI_CMD_Device_s
{
    uint8_t Initialized;
    uint8_t IsMaster;
    uint8_t Blocking;
    uint8_t Dma;
    uint8_t Pattern;
    qapi_SPI_Instance_t Instance;
    qapi_SPI_Transfer_t Transfer;
    uint32_t TransferStatus;
    qapi_TSK_Handle_t Task;
    uint32_t FlashOffset;
    qapi_FLASH_Map_Handle_t FlashMapHandle;
    void *FlashMapAddress;
} SPI_CMD_Device_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Spi_Handle;

/**
   SPI QCLI command device.
*/
SPI_CMD_Device_t SPI_CMD_Master;
SPI_CMD_Device_t SPI_CMD_Slave;

/**
   SPI QCLI command status.
*/
SPI_CMD_Info_t SPI_CMD_Info;

/**
   SPI const Tx test data in RRAM,  1728 = 12^3.
*/
const uint8_t SPI_CMD_RramTxBuf[SPI_CMD_BUFLEN_MAX] = {SPI_CMD_CONSTDATA(SPI_CMD_CONSTDATA(SPI_CMD_CONSTDATA(SPI_CMD_PATTERN)))};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_Spi_MasterConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Spi_SlaveConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Spi_ShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Spi_SpiTest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Spi_SpiReset(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t SPI_CMD_TransferStart(SPI_CMD_Device_t *Device);

const QCLI_Command_t SPI_CMD_List[] =
{
    /* cmd_function        cmd_string      usage_string                       description */
    {cmd_Spi_MasterConfig, "MasterConfig", "<Instance> <Blocking> <Dma> ...", "Config SPI as master mode"},
    {cmd_Spi_SlaveConfig,  "SlaveConfig",  "<Instance> <Blocking> <Dma> ...", "Config SPI as slave mode"},
    {cmd_Spi_ShowConfig,   "ShowConfig",   "",                                "Show current configurations"},
    {cmd_Spi_SpiTest,      "SpiTest",      "<TestMode> <DataLen> ...",        "Run SPI test"},
    {cmd_Spi_SpiReset,     "SpiReset",     "",                                "Reset SPI test"}
};

const QCLI_Command_Group_t SPI_CMD_Group =
{
    "SPI",
    (sizeof(SPI_CMD_List) / sizeof(SPI_CMD_List[0])),
    SPI_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
void Initialize_Spi_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Spi_Handle = QCLI_Register_Command_Group(NULL, &SPI_CMD_Group);
    if (QCLI_Spi_Handle)
    {
        SPI_PRINTF("SPI Registered \n");
    }
}

static void SPI_CMD_SlaveConfigHelp(void)
{
    SPI_PRINTF("Usage:\tSlaveConfig  <Instance> <Blocking> <Dma> <FlashOffset> <Pattern> <BitsPerWord>\n");
    SPI_PRINTF("Options:\n");
    SPI_PRINTF("\tInstance      : 0: First instance, 1: Second instance\n");
    SPI_PRINTF("\tBlocking      : 0: Nonblocking mode, 1: Blocking mode\n");
    SPI_PRINTF("\tDma           : 0: FIFO mode, 1: DMA mode\n");
    SPI_PRINTF("\tFlashOffset   : Flash address, 4-byte aligned\n");
    SPI_PRINTF("\tPattern       : Only valid when DataSource is SRAM, otherwise hard coded as 0xA5\n");
    SPI_PRINTF("\tBitsPerWord   : 4~32 bits of the data length\n");
    SPI_PRINTF("\tExample:\n");
    SPI_PRINTF("\tSlaveConfig 0 0 0 0 0xa5 8\n");
}

static void SPI_CMD_MasterConfigHelp(void)
{
    SPI_PRINTF("Usage:\tMasterConfig  <Instance> <Blocking> <Dma> <FlashOffset> <Pattern> <BitsPerWord> "
                "<CsLine> <FreqHz> <Cpol> <Cpha> <CsPolarity> <CsToggle> <CsClkDelay> <InterWordDelay>\n" );
    SPI_PRINTF("Options:\n");
    SPI_PRINTF("\tInstance      : 0: First instance, 1: Second instance\n");
    SPI_PRINTF("\tBlocking      : 0: Nonblocking mode, 1: Blocking mode\n");
    SPI_PRINTF("\tDma           : 0: FIFO mode, 1: DMA mode\n");
    SPI_PRINTF("\tFlashOffset   : Flash address, 4-byte aligned\n");
    SPI_PRINTF("\tPattern       : Only valid when DataSource is SRAM, otherwise hard coded as 0xA5\n");
    SPI_PRINTF("\tBitsPerWord   : 4~32, bits of the data length\n");
    SPI_PRINTF("\tCsLine        : chip select line, up to 2 slaves\n");
    SPI_PRINTF("\tFreqHz        : 1~16000000Hz, clock rate\n");
    SPI_PRINTF("\tCpol          : 0: CPOL=0, 1: CPOL=1\n");
    SPI_PRINTF("\tCpha          : 0: CPHA=0, 1: CPHA=1\n");
    SPI_PRINTF("\tCsPolarity    : 0: CS active low, 1: CS active high\n");
    SPI_PRINTF("\tCsToggle      : 0: CS will stay low duration of the transfer, 1: CS will toggle between consecutive data frames\n");
    SPI_PRINTF("\tCsClkDelay    : Num of clk cycles to wait after asserting CS before starting transfer\n");
    SPI_PRINTF("\tInterWordDelay: Num of clk cycles to wait between SPI words\n");
    SPI_PRINTF("\tExample:\n");
    SPI_PRINTF("\tMasterConfig 0 0 0 0 0xa5 8 0 2000000 0 0 0 0 0 0\n");
}

static void SPI_CMD_SpiTestHelp(void)
{
    SPI_PRINTF("Usage:\tSpiTest <TestMode=0> <DataLen> <TestCount> <DataSource>\n");
    SPI_PRINTF("Usage:\tSpiTest <TestMode=1> <DataLen> <TestCount> <DataSource> <Direction>\n");
    SPI_PRINTF("Usage:\tSpiTest <TestMode=2> <DataLen> <TestCount=1> <DataSource> <Direction> <Slave>\n");
    SPI_PRINTF("Options:\n");
    SPI_PRINTF("\tTestMode      : 0: HW loopback, Master only, 1: SW loopback, between local Master and Slave, 2: non-loopback test\n");
    SPI_PRINTF("\tDataLen       : 0: 1~1728, the length of the test data\n");
    SPI_PRINTF("\tTestCount     : Non-zero number, it should be 1 when TestMode=2\n");
    SPI_PRINTF("\tDataSource    : 0: Data from SRAM, 1: Data from RRAM, 2: Data from FLASHMEM, DMA only.\n");
    SPI_PRINTF("\tSlave         : 0: Master mode, 1: Slave mode, only valid when TestMode=2\n");
    SPI_PRINTF("\tDirection     : 0: Master sends data to Slave, 1: Slave sends data to Master, 2: Duplex\n");
    SPI_PRINTF("\tExamples:\n");
    SPI_PRINTF("\tSpiTest 0 128 5 0\n");
    SPI_PRINTF("\tSpiTest 1 128 5 0 0\n");
    SPI_PRINTF("\tSpiTest 2 128 1 0 0 0\n");
}

static void SPI_CMD_ShowConfig(SPI_CMD_Device_t *Device)
{
    SPI_PRINTF("SPI %s configurations:\n", Device->IsMaster ? "Master" : "Slave");
    SPI_PRINTF("\tInitialized:%d\n"
               "\tInstance:%d\n"
               "\tBlocking:%d\n"
               "\tDma:%d\n"
               "\tFlashOffset:0x%x\n"
               "\tPattern:0x%x\n",
               Device->Initialized, Device->Instance, Device->Blocking, Device->Dma, Device->FlashOffset, Device->Pattern);

    if (Device->IsMaster)
    {
        qapi_SPI_MXferInfo_t *XferInfo;

        XferInfo = &Device->Transfer.XferInfo.Master;

        SPI_PRINTF("\tCpol:%d\n"
                   "\tCpha:%d\n"
                   "\tCsPolarity:%d\n"
                   "\tCsToggle:%d\n"
                   "\tCsLine:%d\n"
                   "\tCsClkDelay:%d\n"
                   "\tInterWordDelay:%d\n"
                   "\tBitsPerWord:%d\n"
                   "\tFreqHz:%uHz\n",
                   !!(XferInfo->Flags & QAPI_SPI_XFER_CPOL), !!(XferInfo->Flags & QAPI_SPI_XFER_CPHA),
                   !!(XferInfo->Flags & QAPI_SPI_XFER_CSPOLARITY), !!(XferInfo->Flags & QAPI_SPI_XFER_CSTOGGLE),
                   XferInfo->CsLine, XferInfo->CsClkDelay, XferInfo->InterWordDelay, XferInfo->BitsPerWord,
                   XferInfo->FreqHz);
    }
    else
    {
        SPI_PRINTF("\tBitsPerWord:%d\n", Device->Transfer.XferInfo.Slave.BitsPerWord);
    }
}


/**
   @brief Set configurations for SPI slave.

   @param[0] Instance          SPI controller instance.
   @param[1] Blocking          Blocking mode or not.
   @param[2] Dma               DMA or FIFO mode.
   @param[3] FlashOffset       Flash address.
   @param[4] Pattern           Pattern.
   @param[5] BitsPerWord       Data frame length.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Config successfully.
*/
static QCLI_Command_Status_t cmd_Spi_SlaveConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_SPI_Instance_t Instance;
    qapi_SPI_SXferInfo_t *XferInfo;
    uint32_t FlashAddr;

    if(Parameter_Count != 6 || !Parameter_List)
    {
        goto err1;
    }

    Instance = (qapi_SPI_Instance_t)Parameter_List[0].Integer_Value;
    if (Instance >= QAPI_SPI_INSTANCE_MAX_E)
    {
        SPI_PRINTF("Invalid Instance: %d\n", Instance);
        goto err1;
    }

    if (SPI_CMD_Info.Busy)
    {
        SPI_PRINTF("Slave config failed, device is busy\n");
        goto err2;
    }

    if (SPI_CMD_Master.Initialized && SPI_CMD_Master.Instance == Instance)
    {
        SPI_PRINTF("Error, SE%d is already set to Master\n", Instance);
        goto err1;
    }

    FlashAddr = Parameter_List[3].Integer_Value;
    if (FlashAddr & 0x3)
    {
        SPI_PRINTF("Invalid Flash address, it should be 4-byte aligned\n");
        goto err1;
    }

    memset(&SPI_CMD_Slave, 0 , sizeof(SPI_CMD_Slave));

    XferInfo = &SPI_CMD_Slave.Transfer.XferInfo.Slave;
    XferInfo->BitsPerWord = Parameter_List[5].Integer_Value;
    if (XferInfo->BitsPerWord < QAPI_SPI_BITSPERWORD_MIN ||
        XferInfo->BitsPerWord > QAPI_SPI_BITSPERWORD_MAX)
    {
        SPI_PRINTF("Invalid BitsPerWord: %d\n", XferInfo->BitsPerWord);
        goto err1;
    }

    SPI_CMD_Slave.Blocking = !!Parameter_List[1].Integer_Value;
    SPI_CMD_Slave.Dma = !!Parameter_List[2].Integer_Value;
    SPI_CMD_Slave.FlashOffset = FlashAddr;
    SPI_CMD_Slave.Pattern = Parameter_List[4].Integer_Value;
    SPI_CMD_Slave.Instance = Instance;
    SPI_CMD_Slave.Initialized = 1;

    SPI_PRINTF("Set SE%d to SPI Slave mode successfully\n", Instance);

    return QCLI_STATUS_SUCCESS_E;

err1:
    SPI_CMD_SlaveConfigHelp();
err2:
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Set configurations for SPI master.

   @param[0]  Instance          SPI controller instance.
   @param[1]  Blocking          Blocking mode or not.
   @param[2]  Dma               DMA or FIFO mode.
   @param[3]  FlashOffset       Flash address.
   @param[4]  Pattern           Pattern.
   @param[5]  BitsPerWord       Data frame length.
   @param[6]  CsLine            Chip select line.
   @param[7]  FreqHz            Clock rate.
   @param[8]  Cpol              Clock polarity.
   @param[9]  Cpha              Clock pulses.
   @param[10] CsPolarity        CS polarity.
   @param[11] CsToggle          CS toggle.
   @param[12] CsClkDelay        CS clock delay.
   @param[13] InterWordDelay    Interword delay.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Config successfully.
*/
static QCLI_Command_Status_t cmd_Spi_MasterConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_SPI_Instance_t Instance;
    qapi_SPI_MXferInfo_t *XferInfo;
    uint32_t FlashAddr;

    if(Parameter_Count != 14 || !Parameter_List)
    {
        goto err1;
    }

    Instance = (qapi_SPI_Instance_t)Parameter_List[0].Integer_Value;
    if (Instance >= QAPI_SPI_INSTANCE_MAX_E)
    {
        SPI_PRINTF("Invalid Instance: %d\n", Instance);
        goto err1;
    }

    if (SPI_CMD_Info.Busy)
    {
        SPI_PRINTF("Master config failed, device is busy\n");
        goto err2;
    }

    if (SPI_CMD_Slave.Initialized && SPI_CMD_Slave.Instance == Instance)
    {
        SPI_PRINTF("Error, SE%d is already set to Slave\n", Instance);
        goto err1;
    }

    FlashAddr = Parameter_List[3].Integer_Value;
    if (FlashAddr & 0x3)
    {
        SPI_PRINTF("Invalid Flash address, it should be 4-byte aligned\n");
        goto err1;
    }

    memset(&SPI_CMD_Master, 0 , sizeof(SPI_CMD_Master));

    XferInfo = &SPI_CMD_Master.Transfer.XferInfo.Master;
    XferInfo->BitsPerWord = Parameter_List[5].Integer_Value;
    XferInfo->CsLine = Parameter_List[6].Integer_Value;
    XferInfo->FreqHz = Parameter_List[7].Integer_Value;
    if (XferInfo->BitsPerWord < QAPI_SPI_BITSPERWORD_MIN ||
        XferInfo->BitsPerWord > QAPI_SPI_BITSPERWORD_MAX ||
        XferInfo->CsLine > 1 || XferInfo->FreqHz < QAPI_SPI_FREQ_MIN ||
        XferInfo->FreqHz > QAPI_SPI_FREQ_MAX)
    {
        goto err1;
    }

    XferInfo->Flags |= Parameter_List[8].Integer_Value ? QAPI_SPI_XFER_CPOL : 0;
    XferInfo->Flags |= Parameter_List[9].Integer_Value ? QAPI_SPI_XFER_CPHA : 0;
    XferInfo->Flags |= Parameter_List[10].Integer_Value ? QAPI_SPI_XFER_CSPOLARITY : 0;
    XferInfo->Flags |= Parameter_List[11].Integer_Value ? QAPI_SPI_XFER_CSTOGGLE : 0;
    XferInfo->CsClkDelay = Parameter_List[12].Integer_Value;
    XferInfo->InterWordDelay = Parameter_List[13].Integer_Value;

    SPI_CMD_Master.Blocking = !!Parameter_List[1].Integer_Value;
    SPI_CMD_Master.Dma = !!Parameter_List[2].Integer_Value;
    SPI_CMD_Master.FlashOffset = FlashAddr;
    SPI_CMD_Master.Pattern = Parameter_List[4].Integer_Value;
    SPI_CMD_Master.Instance = Instance;
    SPI_CMD_Master.IsMaster = 1;
    SPI_CMD_Master.Initialized = 1;

    SPI_PRINTF("Set SE%d to SPI Master mode successfully\n", Instance);

    return QCLI_STATUS_SUCCESS_E;

err1:
    SPI_CMD_MasterConfigHelp();
err2:
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Display current SPI configurations.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Display successfully.
*/
static QCLI_Command_Status_t cmd_Spi_ShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{

    SPI_CMD_ShowConfig(&SPI_CMD_Master);
    SPI_CMD_ShowConfig(&SPI_CMD_Slave);

    return QCLI_STATUS_SUCCESS_E;
}

static void *SPI_CMD_GetTxBuf(qapi_SPI_Transfer_t *Transfer)
{
    if (SPI_CMD_Info.DataSource == SPI_CMD_DATA_FROM_SRAM)
    {
        return Transfer->TxBuf;
    }
    else
    {
        return (void *)SPI_CMD_RramTxBuf;
    }
}

static void SPI_CMD_LoopbackResult(void *TxBuf, void *RxBuf, uint32_t Len, const char *SpiMode, const char *XferMode)
{
    if (SPI_CMD_Info.TestMode == SPI_CMD_TEST_MODE_SW_LOOPBACK)
    {
        if (!memcmp(RxBuf, TxBuf, Len))
        {
            SPI_PRINTF("Master/Slave %s test%d passed\n", XferMode, SPI_CMD_Info.TestIndex);
            SPI_CMD_Info.SuccessCount++;
        }
        else
        {
            SPI_PRINTF("Master/Slave %s test%d failed\n", XferMode, SPI_CMD_Info.TestIndex);
            SPI_CMD_Info.FailureCount++;
        }
    }
    else
    {
        if (!memcmp(RxBuf, TxBuf, Len))
        {
            SPI_PRINTF("%s %s test%d passed\n", SpiMode, XferMode, SPI_CMD_Info.TestIndex);
            SPI_CMD_Info.SuccessCount++;
        }
        else
        {
            SPI_PRINTF("%s %s test%d failed\n", SpiMode, XferMode, SPI_CMD_Info.TestIndex);
            SPI_CMD_Info.FailureCount++;
        }
    }
}

static void SPI_CMD_DumpTransferBuf(unsigned char *Buf, uint32_t BufLen)
{
    int i;

    for (i = 0; i < BufLen; i++)
    {
        SPI_PRINTF("%02x", Buf[i]);
    }
    SPI_PRINTF("\n");
}

static qbool_t SPI_CMD_TestComplete(SPI_CMD_Device_t *Device, qapi_SPI_Transfer_t *Transfer,
                                    const char *SpiMode, const char *XferMode)
{
    void *TxBuf, *RxBuf;
    uint32_t BufLen;
    qbool_t Status = true;

    switch(SPI_CMD_Info.TestMode)
    {
        case SPI_CMD_TEST_MODE_HW_LOOPBACK:
            TxBuf = SPI_CMD_GetTxBuf(Transfer);
            SPI_CMD_LoopbackResult(TxBuf, Transfer->RxBuf, Transfer->RxLen, SpiMode, XferMode);
            break;
        case SPI_CMD_TEST_MODE_SW_LOOPBACK:
            if (SPI_CMD_Info.Direction == SPI_CMD_DIR_MASTER_TO_SLAVE)
            {
                TxBuf = SPI_CMD_GetTxBuf(&SPI_CMD_Master.Transfer);
                RxBuf = SPI_CMD_Slave.Transfer.RxBuf;
                BufLen = SPI_CMD_Slave.Transfer.RxLen;

                if (!Device->IsMaster)
                {
            	    SPI_PRINTF("Slave %s RX complete %d successfully\n", XferMode, SPI_CMD_Info.TestIndex);
#if SPI_CMD_DUMP
                    SPI_CMD_DumpTransferBuf((unsigned char *)Transfer->RxBuf, Transfer->RxLen);
#endif
                }
            }
            else if (SPI_CMD_Info.Direction == SPI_CMD_DIR_SLAVE_TO_MASTER)
            {
                TxBuf = SPI_CMD_GetTxBuf(&SPI_CMD_Slave.Transfer);
                RxBuf = SPI_CMD_Master.Transfer.RxBuf;
                BufLen = SPI_CMD_Master.Transfer.RxLen;

                if (Device->IsMaster)
                {
            	    SPI_PRINTF("Master %s RX complete %d successfully\n", XferMode, SPI_CMD_Info.TestIndex);
#if SPI_CMD_DUMP
                    SPI_CMD_DumpTransferBuf((unsigned char *)Transfer->RxBuf, Transfer->RxLen);
#endif
                }
            }
            else
            {
                TxBuf = SPI_CMD_Slave.Transfer.RxBuf;
                RxBuf = SPI_CMD_Master.Transfer.RxBuf;
                BufLen = SPI_CMD_Master.Transfer.TxLen;
            }

            if (++SPI_CMD_Info.SwLoopbackDone != 2)
            {
                Status = false;
            }
            else
            {
                SPI_CMD_LoopbackResult(TxBuf, RxBuf, BufLen, SpiMode, XferMode);
            }
            break;
        case SPI_CMD_TEST_MODE_NORMAL:
            if (Transfer->RxBuf)
            {
                SPI_PRINTF("%s %s RX complete successfully\n", SpiMode, XferMode);
                SPI_CMD_DumpTransferBuf((unsigned char *)Transfer->RxBuf, Transfer->RxLen);
            }

            if (Transfer->TxBuf && SPI_CMD_Info.Direction != SPI_CMD_DIR_DUPLEX)
            {
                SPI_PRINTF("%s %s TX complete successfully\n", SpiMode, XferMode);
            }
            break;
    }

    return Status;
}

static void SPI_CMD_SpiTestCleanup(SPI_CMD_Device_t *Device)
{
    qapi_SPI_Transfer_t *Transfer;
    SPI_CMD_Info_t *Info = &SPI_CMD_Info;

    qapi_SPI_Close(Device->Instance);

    if (Device->Task)
    {
        qapi_TSK_Delete_Task(Device->Task);
        Device->Task = NULL;
    }

    Transfer = &Device->Transfer;

    if (Transfer->TxBuf && Info->DataSource == SPI_CMD_DATA_FROM_SRAM)
    {
        qapi_Free(Transfer->TxBuf);
        Transfer->TxBuf = NULL;
    }

    if (Transfer->RxBuf)
    {
        qapi_Free(Transfer->RxBuf);
        Transfer->RxBuf = NULL;
    }

    if (Info->DataSource == SPI_CMD_DATA_FROM_FLASHMEM && Device->FlashMapHandle)
    {
        qapi_FLASH_Memory_Unmap(Device->FlashMapHandle);
        Device->FlashMapHandle = NULL;
    }
}

static void SPI_CMD_SpiTestCallback(uint32_t Status, void *CallbackCtxt)
{
    SPI_CMD_Device_t *Device = CallbackCtxt;

    Device->TransferStatus = Status;
    qapi_TSK_Signal_Task(Device->Task, SPI_CMD_COMPLETE_EVENT);
}

static void *SPI_CMD_FlashMemGet(SPI_CMD_Device_t *Device, uint32_t DataLen)
{
    qapi_Status_t Status;
    uint32_t MappedAddress;
    uint32_t EraseStart;
    uint32_t EraseCnt;

    Status = qapi_FLASH_Init(NULL);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Error, Flash uninitialized, please set Flash first in Flash menu\n");
        return NULL;
    }

    EraseStart = Device->FlashOffset / FLASH_BLOCK_SIZE_IN_BYTES;
    EraseCnt = (Device->FlashOffset + DataLen) / FLASH_BLOCK_SIZE_IN_BYTES - EraseStart + 1;
    Status = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseStart, EraseCnt, NULL, NULL);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Flash erase failed, error: %d\n", Status);
        return NULL;
    }

    Status = qapi_FLASH_Write(Device->FlashOffset, DataLen, (uint8_t *)SPI_CMD_RramTxBuf, NULL, NULL);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Flash write failed, error: %d\n", Status);
        return NULL;
    }

    Status = qapi_FLASH_Memory_Map(Device->FlashOffset, DataLen, &Device->FlashMapHandle);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Flash memory mapping failed, error: %d\n", Status);
        return NULL;
    }

    Status = qapi_FLASH_Get_Mapped_Address(Device->FlashOffset, &MappedAddress);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Flash get mapping address failed, error: %d\n", Status);
        qapi_FLASH_Memory_Unmap(Device->FlashMapHandle);
        Device->FlashMapHandle = NULL;
        return NULL;
    }

    Device->FlashMapAddress = (void *)MappedAddress;

    return (void *)MappedAddress;
}

static void SPI_CMD_TaskProcess(SPI_CMD_Device_t *Device)
{
    qapi_SPI_Transfer_t *Transfer;
    uint32_t Status = Device->TransferStatus;
    SPI_CMD_Info_t *Info = &SPI_CMD_Info;
    const char *SpiMode = Device->IsMaster ? "Master" : "Slave";
    const char *XferMode = Device->Dma ? "DMA nonblocking" : "FIFO nonblocking";

    if (Status != QAPI_OK)
    {
        SPI_PRINTF("%s %s transfer failed, error:%d\n", SpiMode, XferMode, Status);
        goto out;
    }

    Transfer = &Device->Transfer;

    if (!SPI_CMD_TestComplete(Device, Transfer, SpiMode, XferMode))
    {
        return;
    }

    if (++Info->TestIndex < Info->TestCount)
    {
        if (Info->TestMode == SPI_CMD_TEST_MODE_SW_LOOPBACK)
        {
            SPI_CMD_Info.SwLoopbackDone = 0;

            if (SPI_CMD_Info.Direction == SPI_CMD_DIR_MASTER_TO_SLAVE)
            {
                memset(SPI_CMD_Slave.Transfer.RxBuf, 0, SPI_CMD_Slave.Transfer.RxLen);
            }
            else if (SPI_CMD_Info.Direction == SPI_CMD_DIR_SLAVE_TO_MASTER)
            {
                memset(SPI_CMD_Master.Transfer.RxBuf, 0, SPI_CMD_Master.Transfer.RxLen);
            }
            else
            {
                memset(SPI_CMD_Slave.Transfer.RxBuf, 0, SPI_CMD_Slave.Transfer.RxLen);
                memset(SPI_CMD_Master.Transfer.RxBuf, 0, SPI_CMD_Master.Transfer.RxLen);
            }

            if (SPI_CMD_TransferStart(&SPI_CMD_Slave) || SPI_CMD_TransferStart(&SPI_CMD_Master))
            {
                goto out;
            }
        }
        else
        {
            if (Info->TestMode == SPI_CMD_TEST_MODE_HW_LOOPBACK)
            {
                memset(Transfer->RxBuf, 0, Transfer->RxLen);
            }

            if (SPI_CMD_TransferStart(Device))
            {
                goto out;
            }
        }

        return;
    }

out:
    if (Info->TestMode != SPI_CMD_TEST_MODE_NORMAL)
    {
        SPI_PRINTF("Test complete total:%d success:%d failure:%d\n",
                    SPI_CMD_Info.TestCount,
                    SPI_CMD_Info.SuccessCount,
                    SPI_CMD_Info.FailureCount);
    }

    if (Info->TestMode == SPI_CMD_TEST_MODE_SW_LOOPBACK)
    {
        if (Device->IsMaster)
        {
            SPI_CMD_SpiTestCleanup(&SPI_CMD_Slave);
        }
        else
        {
            SPI_CMD_SpiTestCleanup(&SPI_CMD_Master);
        }
    }

    SPI_CMD_SpiTestCleanup(Device);
    SPI_CMD_Info.Busy = 0;
}

static uint32_t SPI_Cmd_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    SPI_CMD_Device_t *Device = UserParam;

    if (EventMask & SPI_CMD_COMPLETE_EVENT)
    {
        SPI_CMD_TaskProcess(Device);
    }

    return QAPI_TSK_INFINITE_WAIT;
}

static QCLI_Command_Status_t SPI_CMD_TransferBufPrepare(SPI_CMD_Device_t *Device, qapi_SPI_Transfer_t *Transfer,
                                                        uint32_t DataLen, uint32_t DataSource, qbool_t Tx, qbool_t Rx)
{
    /* Prepare Tx buffer */
    if (Tx)
    {
        switch (DataSource)
        {
            case SPI_CMD_DATA_FROM_RRAM:
                Transfer->TxBuf = (void *)SPI_CMD_RramTxBuf;
                break;
            case SPI_CMD_DATA_FROM_FLASHMEM:
                Transfer->TxBuf = SPI_CMD_FlashMemGet(Device, DataLen);
                if (!Transfer->TxBuf)
                {
                    goto err;
                }
                break;
            case SPI_CMD_DATA_FROM_SRAM:
                Transfer->TxBuf = qapi_Malloc(DataLen);
                if (!Transfer->TxBuf)
                {
                    SPI_PRINTF("Test failed, no enough memory for Tx buffer\n");
                    goto err;
                }
                memset(Transfer->TxBuf, Device->Pattern, DataLen);
                break;
            default:
                goto err;
        }

        Transfer->TxLen = DataLen;
    }
    else
    {
        Transfer->TxBuf = NULL;
        Transfer->TxLen = 0;
    }

    /* Prepare Rx buffer */
    if (Rx)
    {
        Transfer->RxBuf = qapi_Malloc(DataLen);
        if (!Transfer->RxBuf)
        {
            SPI_PRINTF("Test failed, no enough memory for Rx buffer\n");

            if (DataSource == SPI_CMD_DATA_FROM_SRAM && Transfer->TxBuf)
            {
                qapi_Free(Transfer->TxBuf);
                Transfer->TxBuf = NULL;
                Transfer->TxLen = 0;
            }
            goto err;
        }

        Transfer->RxLen = DataLen;
        memset(Transfer->RxBuf, 0, Transfer->RxLen);
    }
    else
    {
        Transfer->RxBuf = NULL;
        Transfer->RxLen = 0;
    }

    return QCLI_STATUS_SUCCESS_E;
err:
    return QCLI_STATUS_ERROR_E;
}

static QCLI_Command_Status_t SPI_CMD_TransferSetup(SPI_CMD_Device_t *Device, uint32_t DataLen,
                                                   uint32_t TestCount, uint32_t DataSource,
                                                   qbool_t Tx, qbool_t Rx)
{
    SPI_CMD_Info_t *Info = &SPI_CMD_Info;
    qapi_SPI_Config_t Config;
    qapi_SPI_Transfer_t *Transfer = &Device->Transfer;
    qapi_Status_t Status;

    if (!Device->Initialized)
    {
        SPI_PRINTF("Error, Device is not initialized\n");
        goto err;
    }

    if (DataSource == SPI_CMD_DATA_FROM_FLASHMEM && !Device->Dma)
    {
        SPI_PRINTF("Error, Data source from flash only works in DMA mode\n");
        goto err;
    }

    if (SPI_CMD_TransferBufPrepare(Device, Transfer, DataLen, DataSource, Tx, Rx))
    {
        goto err;
    }

    Config.Mode = Device->IsMaster ? QAPI_SPI_MODE_MASTER_E : QAPI_SPI_MODE_SLAVE_E;
    Config.Blocking = Device->Blocking;
    Config.Dma = Device->Dma;
    Config.NoMuxPriority = 0;
    Status = qapi_SPI_Open(Device->Instance, &Config);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Open SPI device %d failed, error: %d\n", Device->Instance, Status);
        goto err;
    }

    if (!Device->Blocking)
    {
        Device->Task = qapi_TSK_Create_Task(SPI_Cmd_Task, Device);
        if (!Device->Task)
        {
            goto err;
        }
        Transfer->CallbackFn = (qapi_SPI_CB_t)SPI_CMD_SpiTestCallback;
        Transfer->CallbackCtxt = Device;
    }
    else
    {
        Transfer->CallbackFn = NULL;
        Transfer->CallbackCtxt = NULL;
    }

    Info->DataSource = (SPI_CMD_DataSource_t)DataSource;
    Info->TestCount = !TestCount ? 1 : TestCount;
    Info->TestIndex = 0;
    Info->SuccessCount = 0;
    Info->FailureCount = 0;
    Info->Busy = 1;
    Info->SwLoopbackDone = 0;

    return QCLI_STATUS_SUCCESS_E;
err:
    return QCLI_STATUS_ERROR_E;
}

static QCLI_Command_Status_t SPI_CMD_TransferStartBlocking(SPI_CMD_Device_t *Device,
                                                           qapi_SPI_Transfer_t *Transfer)
{
    qapi_Status_t Status;
    SPI_CMD_Info_t *Info = &SPI_CMD_Info;
    const char *SpiMode = Device->IsMaster ? "Master" : "Slave";
    const char *XferMode = Device->Dma ? "DMA blocking" : "FIFO blocking";

    while (Info->TestIndex < Info->TestCount)
    {
        Status = qapi_SPI_Transfer(Device->Instance, Transfer);
        if (Status != QAPI_OK)
        {
            SPI_PRINTF("Start blocking transfer failed, error: %d\n", Status);
            break;
        }

        SPI_CMD_TestComplete(Device, Transfer, SpiMode, XferMode);
        Info->TestIndex++;
    }

    if (Info->TestMode != SPI_CMD_TEST_MODE_NORMAL)
    {
        SPI_PRINTF("Test complete total:%d success:%d failure:%d\n",
                SPI_CMD_Info.TestCount,
                SPI_CMD_Info.SuccessCount,
                SPI_CMD_Info.FailureCount);
    }

    SPI_CMD_SpiTestCleanup(Device);
    SPI_CMD_Info.Busy = 0;

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t SPI_CMD_TransferStartNonBlocking(SPI_CMD_Device_t *Device,
                                                              qapi_SPI_Transfer_t *Transfer)
{
    qapi_Status_t Status;

    Status = qapi_SPI_Transfer(Device->Instance, Transfer);
    if (Status != QAPI_OK)
    {
        SPI_PRINTF("Start nonblocking transfer failed, error: %d\n", Status);
        return QCLI_STATUS_ERROR_E;
    }

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t SPI_CMD_TransferStart(SPI_CMD_Device_t *Device)
{
    qapi_SPI_Transfer_t *Transfer = &Device->Transfer;

    if (Device->Blocking)
    {
        return SPI_CMD_TransferStartBlocking(Device, Transfer);
    }
    else
    {
        return SPI_CMD_TransferStartNonBlocking(Device, Transfer);
    }
}

static QCLI_Command_Status_t SPI_CMD_HwLoopbackTest(uint32_t DataLen, uint32_t TestCount, uint32_t DataSource)
{
    SPI_CMD_Device_t *Device = &SPI_CMD_Master;

    if (SPI_CMD_TransferSetup(Device, DataLen, TestCount, DataSource, true, true))
    {
        goto err;
    }

    if (SPI_CMD_TransferStart(Device))
    {
        goto err;
    }

    return QCLI_STATUS_SUCCESS_E;
err:
    SPI_CMD_SpiTestCleanup(Device);
    SPI_CMD_Info.Busy = 0;

    return QCLI_STATUS_ERROR_E;
}

static QCLI_Command_Status_t SPI_CMD_NormalTest(uint32_t DataLen, uint32_t TestCount, uint32_t DataSource, uint32_t Direction, uint32_t Slave)
{
    SPI_CMD_Device_t *Device = Slave ? &SPI_CMD_Slave : &SPI_CMD_Master;

    if (TestCount != 1)
    {
        SPI_PRINTF("Error, TestCount should be 1 in non-loopback test mode\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Direction > SPI_CMD_DIR_DUPLEX)
    {
        SPI_PRINTF("Error, invalid direction %d\n", Direction);
        return QCLI_STATUS_ERROR_E;
    }

    if (Direction == SPI_CMD_DIR_DUPLEX)
    {
        if (SPI_CMD_TransferSetup(Device, DataLen, TestCount, DataSource, true, true))
        {
            goto err;
        }
    }
    else if (((Direction == SPI_CMD_DIR_MASTER_TO_SLAVE) && !Slave) ||
             ((Direction == SPI_CMD_DIR_SLAVE_TO_MASTER) && Slave))
    {
        if (SPI_CMD_TransferSetup(Device, DataLen, TestCount, DataSource, true, false))
        {
            goto err;
        }
    }
    else
    {
        if (SPI_CMD_TransferSetup(Device, DataLen, TestCount, DataSource, false, true))
        {
            goto err;
        }
    }

    SPI_CMD_Info.Direction = (SPI_CMD_Direction_t)Direction;

    if (SPI_CMD_TransferStart(Device))
    {
        goto err;
    }

    return QCLI_STATUS_SUCCESS_E;
err:
    SPI_CMD_SpiTestCleanup(Device);
    SPI_CMD_Info.Busy = 0;

    return QCLI_STATUS_ERROR_E;
}

static QCLI_Command_Status_t SPI_CMD_SwLoopbackTest(uint32_t DataLen, uint32_t TestCount, uint32_t DataSource, uint32_t Direction)
{
    SPI_CMD_Device_t *Master = &SPI_CMD_Master;
    SPI_CMD_Device_t *Slave = &SPI_CMD_Slave;

    /* Loopback from one local serial engine to another */
    if (Master->Blocking || Slave->Blocking)
    {
        SPI_PRINTF("Error, SW loopback doesn't support blocking mode\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Direction > SPI_CMD_DIR_DUPLEX)
    {
        SPI_PRINTF("Error, invalid direction %d\n", Direction);
        return QCLI_STATUS_ERROR_E;
    }

    if (Direction == SPI_CMD_DIR_MASTER_TO_SLAVE)
    {
        if (SPI_CMD_TransferSetup(Master, DataLen, TestCount, DataSource, true, false) ||
            SPI_CMD_TransferSetup(Slave, DataLen, TestCount, DataSource, false, true))
        {
            goto err;
        }
    }
    else if (Direction == SPI_CMD_DIR_SLAVE_TO_MASTER)
    {
        if (SPI_CMD_TransferSetup(Master, DataLen, TestCount, DataSource, false, true) ||
            SPI_CMD_TransferSetup(Slave, DataLen, TestCount, DataSource, true, false))
        {
            goto err;
        }
    }
    else
    {
        if (SPI_CMD_TransferSetup(Master, DataLen, TestCount, DataSource, true, true) ||
            SPI_CMD_TransferSetup(Slave, DataLen, TestCount, DataSource, true, true))
        {
            goto err;
        }
    }

    SPI_CMD_Info.Direction = (SPI_CMD_Direction_t)Direction;

    if (SPI_CMD_TransferStart(Slave) || SPI_CMD_TransferStart(Master))
    {
        goto err;
    }

    return QCLI_STATUS_SUCCESS_E;
err:
    SPI_CMD_SpiTestCleanup(Master);
    SPI_CMD_SpiTestCleanup(Slave);
    SPI_CMD_Info.Busy = 0;

    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Run SPI test.

   @param[0] TestMode         #SPI_CMD_TestMode_t.
   @param[1] DataLen          The length of the test data.
   ...

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Test successfully.
*/
static QCLI_Command_Status_t cmd_Spi_SpiTest(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t DataLen;

    if (SPI_CMD_Info.Busy)
    {
        SPI_PRINTF("Test failed, device is busy\n");
        return QCLI_STATUS_ERROR_E;
    }

    if(Parameter_Count < 3 || !Parameter_List)
    {
        goto err;
    }

    DataLen = Parameter_List[1].Integer_Value;
    if (DataLen < SPI_CMD_BUFLEN_MIN || DataLen > SPI_CMD_BUFLEN_MAX)
    {
        SPI_PRINTF("Test failed, invalid data length\n");
        goto err;
    }

    SPI_CMD_Master.Transfer.XferInfo.Master.Flags &= ~QAPI_SPI_XFER_LOOPBACK;

    SPI_CMD_Info.TestMode = (SPI_CMD_TestMode_t)Parameter_List[0].Integer_Value;
    switch (SPI_CMD_Info.TestMode)
    {
        case SPI_CMD_TEST_MODE_HW_LOOPBACK:
            /* <TestMode=0> <DataLen> <TestCount> <DataSource> */
            if (Parameter_Count != 4)
            {
                goto err;
            }

            SPI_CMD_Master.Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_LOOPBACK;
            return SPI_CMD_HwLoopbackTest(Parameter_List[1].Integer_Value,
                                          Parameter_List[2].Integer_Value,
                                          Parameter_List[3].Integer_Value);
        case SPI_CMD_TEST_MODE_SW_LOOPBACK:
            /* <TestMode=1> <DataLen> <TestCount> <DataSource> <Direction> */
            if (Parameter_Count != 5)
            {
                goto err;
            }

            return SPI_CMD_SwLoopbackTest(Parameter_List[1].Integer_Value,
                                          Parameter_List[2].Integer_Value,
                                          Parameter_List[3].Integer_Value,
                                          Parameter_List[4].Integer_Value);
        case SPI_CMD_TEST_MODE_NORMAL:
            /* <TestMode=2> <DataLen> <TestCount> <DataSource> <Direction> <Slave> */
            if (Parameter_Count != 6)
            {
                goto err;
            }

            return SPI_CMD_NormalTest(Parameter_List[1].Integer_Value,
                                      Parameter_List[2].Integer_Value,
                                      Parameter_List[3].Integer_Value,
                                      Parameter_List[4].Integer_Value,
                                      Parameter_List[5].Integer_Value);
        default:
            SPI_PRINTF("Invalid TestMode: %d\n", SPI_CMD_Info.TestMode);
            return QCLI_STATUS_ERROR_E;
    }

err:
    SPI_CMD_SpiTestHelp();
    return QCLI_STATUS_ERROR_E;
}

static QCLI_Command_Status_t cmd_Spi_SpiReset(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    SPI_CMD_Info_t *Info = &SPI_CMD_Info;
    uint32_t Master_TransferStatus;
    uint32_t Slave_TransferStatus;

    SPI_CMD_SpiTestCleanup(&SPI_CMD_Master);
    SPI_CMD_SpiTestCleanup(&SPI_CMD_Slave);

    Master_TransferStatus = SPI_CMD_Master.TransferStatus;
    Slave_TransferStatus = SPI_CMD_Slave.TransferStatus;
    memset(Info, 0, sizeof *Info);
    memset(&SPI_CMD_Master, 0, sizeof SPI_CMD_Master);
    memset(&SPI_CMD_Slave, 0, sizeof SPI_CMD_Slave);
    SPI_CMD_Master.TransferStatus = Master_TransferStatus;
    SPI_CMD_Slave.TransferStatus = Slave_TransferStatus;

    SPI_PRINTF("Reset successfully!\n");

    return QCLI_STATUS_SUCCESS_E;
}
