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
#include "qapi_i2c.h"
#include "qapi_gpio.h"
#include "qcli_pal.h"
#include "qapi_timer.h"
#include "qcli.h"
#include "qcli_api.h"
#include "i2c_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define I2C_DBG
#ifdef I2C_DBG
#define I2CM_PRINTF(...)     QCLI_Printf(QCLI_I2CM_Handle, __VA_ARGS__)
#else
#define I2CM_PRINTF(x, ...)
#endif

/** Bus speeds supported by the master implementation. */
#define I2C_STANDARD_MODE_FREQ_KHZ          100     /**< I2C stadard speed 100 KHz. */
#define I2C_FAST_MODE_FREQ_KHZ              400     /**< I2C fast mode speed 400 KHz. */
#define I2C_FAST_MODE_PLUS_FREQ_KHZ         1000    /**< I2C fast mode plus speed 1 MHz */

#define I2C_FLAGS_START_WIRTE               QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_WRITE;
#define I2C_FLAGS_START_READ                QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_READ;
#define I2C_FLAGS_START_WIRTE_STOP          QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_WRITE | QAPI_I2C_FLAG_STOP;
#define I2C_FLAGS_START_READ_STOP           QAPI_I2C_FLAG_START | QAPI_I2C_FLAG_READ | QAPI_I2C_FLAG_STOP;

#define I2C_MAX_TRANSFER_NUMBER             4

#define I2C_MAX_TRANSFER_DATA_LENGTH        128      /*Max Data Length since memory limitation */
#define I2C_SLAVE_MAX_TRANSFER_DATA_LENGTH  256      /*Max Data Length since memory limitation for i2c slave demo */

/** EEPROM memory size */
#define I2C_SLAVE_EEPROM_MEMORY_SIZE        4096
#define I2C_SLAVE_EEPROM_PAGE_SIZE          32

/** NFC Tag NT3H2111 specific definitions */
#define NT3H2111_I2C_ADDRESS            (0xAA>>1)

/** NFC PIO */
#define NFC_VDD_PIO                     QAPI_GPIO_ID7_E

/** NT3H2111 I2C registers */
#define REG_CAPABILITY_CONTAINER        (0x00)
#define REG_START_BLOCK                 (0x01)
#define REG_CONFIG                      (0x7A)
#define REG_SESSION                     (0xFE)

#define BYTES_PER_I2C_BLOCK             (0x10)
#define WORDS_PER_I2C_BLOCK             (BYTES_PER_I2C_BLOCK >> 1)

/** NDEF definition */
#define NDEF_MAX_SIZE                   (0x20)
#define NFC_TAG_PHONE_NUM_LEN           (12)

#define NDEF_MSG_TLV                    (0x3)
#define NDEF_TERMINATOR_TLV             (0xFE)

/** NDEF MSG URI ID Code */
#define URI_HTTP_WWW_ABBR_ID            (0x01) // http://www.
#define URI_HTTPS_WWW_ABBR_ID           (0x02) // https://www.

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum
{
    I2C_MASTER_INSTANCE_CLOSED,
    I2C_MASTER_INSTANCE_READY,
    I2C_MASTER_INSTANCE_TRANSFER_QUEUE_FULL,
} I2CM_Ctxt_State_t;

typedef enum
{
    I2C_MASTER_TRANSFER_WRITE,
    I2C_MASTER_TRANSFER_READ,
    I2C_MASTER_TRANSFER_WRITE_READ,
} I2CM_OpCode_t;

typedef struct I2CM_Transfer_s
{
    qapi_I2CM_Transfer_Config_t Config;
    I2CM_OpCode_t OpCode;
    uint32_t NumDesc;
    qapi_I2CM_Descriptor_t *Desc; 
    qapi_I2CM_Transfer_CB_t CBFunction;
    void *CBParameter;
    I2CM_Ctxt_State_t State;
    struct I2CM_Transfer_s *Next;
} I2CM_Transfer_t;

typedef enum
{
    I2C_SlAVE_TYPE_EEPROM,
	I2C_SlAVE_TYPE_NFC,		
	I2C_SlAVE_TYPE_RAWSLAVE,
} I2C_Slave_Type_t;

typedef struct I2CM_Ctxt_s
{   I2C_Slave_Type_t SlaveType;
    qapi_I2CM_Config_t Config;
    I2CM_Ctxt_State_t State;
    I2CM_Transfer_t *Transfer;
    uint32_t TransferNum;
} I2C_Master_Context_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_I2CM_Handle;

/**
   I2CM Client.
*/
I2C_Master_Context_t I2CM_Ctxt[4];


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_I2CM_Open(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_I2CM_Transfer(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_I2CM_Cancel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_I2CM_Close(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void cmd_I2CM_TransCallback(uint32_t Status, void *CallbackCtxt);

const QCLI_Command_t I2CM_CMD_List[] =
{
    /* cmd_function     cmd_string   usage_string                                                                                description */
    {cmd_I2CM_Open,     "Open",      "<Instance> <Blocking> <Dma>",                                                              "Open the I2C Master instance"},
    {cmd_I2CM_Transfer, "Transfer",  "<SlaveType> <Operation> <Instance> <SlaveAddress> <Frequency> <Address> <DataLen> <Data>", "perform an I2C transfer"},
    {cmd_I2CM_Cancel,   "Cancel",    "<Instance",                                                                                "Cancel the I2C transfers"},
    {cmd_I2CM_Close,    "Close",     "<Instance>",                                                                               "Close the I2C Master instance"}
};
        
const QCLI_Command_Group_t I2CM_CMD_Group =
{
    "I2CM",
    (sizeof(I2CM_CMD_List) / sizeof(I2CM_CMD_List[0])),
    I2CM_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
void Initialize_I2CM_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_I2CM_Handle = QCLI_Register_Command_Group(NULL, &I2CM_CMD_Group);
    if (QCLI_I2CM_Handle)
    {
        I2CM_PRINTF("I2C Master Registered \n");
    }
}

static void cmd_I2CM_OpenHelp(void)
{
    I2CM_PRINTF("Usage:\tOpen <Instance> <Blocking> <Dma>\n");
    I2CM_PRINTF("Options:\n");
    I2CM_PRINTF("\tInstance      : 0~3 I2C Master instance\n");
    I2CM_PRINTF("\tBlocking      : 0: Nonblocking mode, 1: Blocking mode\n");
    I2CM_PRINTF("\tDma           : 0: FIFO mode, 1: DMA mode\n");
    I2CM_PRINTF("\tExample:\n");
    I2CM_PRINTF("\tOpen 0 0 0\n");
}

static void cmd_I2CM_TransferHelp(void)
{
    I2CM_PRINTF("Usage:\ttransfer <SlaveType> <Operation> <Instance> <SlaveAddress> <Frequency> <Address> <DataLen> <Data>\n");
    I2CM_PRINTF("Options:\n");
    I2CM_PRINTF("\tSlaveType     : support 'eeprom' and 'rawslave'\n");
    I2CM_PRINTF("\tOperation     : 'w','r' and 'wr'. w: write, r: read, wr: write and read in one transfer\n");
    I2CM_PRINTF("\tInstance      : 0~3 I2C Master instance\n");
    I2CM_PRINTF("\tSlaveAddress  : 7 bit I2C Slave address\n");
    I2CM_PRINTF("\tFrequency     : 100/400/1000 kHz\n");
    I2CM_PRINTF("\tAddress       : The address which the data to be written to or read from, for rawslave this will be ignore\n");
    I2CM_PRINTF("\tDataLen       : The Length of data to be written or read\n");
    I2CM_PRINTF("\tData          : Data to be written, only used when write operation\n");
    I2CM_PRINTF("\t                In rawslave mode, make sure the length of written is smaller than the flash heart's\n");
    I2CM_PRINTF("\tExample:\n");
    I2CM_PRINTF("\ttransfer eeprom w 0 0x50 400 0 8 aabbccdd\n");
}

static void cmd_I2CM_CancelHelp(void)
{
    I2CM_PRINTF("Usage:\tCancel <Instance>\n");
    I2CM_PRINTF("Options:\n");
    I2CM_PRINTF("\tInstance      : 0~3 I2C Master instance\n");
    I2CM_PRINTF("\tExample:\n");
    I2CM_PRINTF("\tcancel 0\n");
}

static void cmd_I2CM_CloseHelp(void)
{
    I2CM_PRINTF("Usage:\tClose <Instance>\n");
    I2CM_PRINTF("Options:\n");
    I2CM_PRINTF("\tInstance      : 0~3 I2C Master instance\n");
    I2CM_PRINTF("\tExample:\n");
    I2CM_PRINTF("\tclose 0\n");
}

static uint32_t I2CM_GetDescNum(I2C_Slave_Type_t SlaveType, I2CM_OpCode_t Op, uint32_t DataAddr, uint32_t DataLen)
{
    uint8_t NumDesc = 0;
    uint8_t Offset;

	if (SlaveType == I2C_SlAVE_TYPE_RAWSLAVE)
	{
		/* the raw i2c slave demo only need one Descriptor per time */
		NumDesc = 1;
		return NumDesc;
	}

	if (Op == I2C_MASTER_TRANSFER_READ)
	{
		/** one data address descriptor + one read descriptor*/
		NumDesc = 2;
		return NumDesc;
	}

    if (SlaveType == I2C_SlAVE_TYPE_EEPROM)
    {
        Offset = I2C_SLAVE_EEPROM_PAGE_SIZE - DataAddr%I2C_SLAVE_EEPROM_PAGE_SIZE;
        if ((Offset > 0) && (DataLen >= Offset))
        {
            NumDesc++;
            DataLen -= Offset;
        }

        NumDesc += DataLen/I2C_SLAVE_EEPROM_PAGE_SIZE;

        if (DataLen%I2C_SLAVE_EEPROM_PAGE_SIZE > 0)
        {
           NumDesc++; 
        }

        if (Op == I2C_MASTER_TRANSFER_WRITE_READ)
        {
            /** write Numdesc +  read Numdesc*/
            NumDesc = NumDesc + 2;
        }
    }
	else if (SlaveType == I2C_SlAVE_TYPE_NFC)
    {
        NumDesc = 1;
    }
	//TODO for i2cslave type NumDesc = 1
    
    return NumDesc;
}

static void I2CM_InitEepromDescriptors(I2CM_OpCode_t OpCode, uint32_t Address, uint8_t *Data, uint32_t DataLen, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc)
{
    int i;
    uint8_t  *Buffer;
    uint32_t BufferOffset=0;
    uint32_t DescIdx = 0;
    uint32_t DataOffset=0;
    uint32_t WriteLen=0;    
    uint32_t StartPageSize=0;
    uint32_t AddressOffset=0;
    static uint32_t Idx = 0;
    
    Buffer = (uint8_t*)Desc+sizeof(qapi_I2CM_Descriptor_t)*NumDesc;
    /*If Datatype is string, Print it directly at the customer call back function*/
    if (OpCode == I2C_MASTER_TRANSFER_WRITE_READ)
    {
        Data = Buffer;
        Idx = Idx%10;
        Idx++;
        memset(Data, Idx+0x30, NumDesc*2+DataLen);
    }
   
    if (OpCode == I2C_MASTER_TRANSFER_READ)
    {
I2C_EEPROM_READ:  
        /*Init Read Descriptor*/
        Desc[DescIdx].Flags= I2C_FLAGS_START_WIRTE;
        Desc[DescIdx].Length = 2; 
        Desc[DescIdx].Buffer = Buffer+BufferOffset;
        Desc[DescIdx].Buffer[0] = (Address&0xFF00)>>8;
        Desc[DescIdx].Buffer[1] = Address&0xFF;

        BufferOffset += 2;
        Desc[DescIdx+1].Flags= I2C_FLAGS_START_READ_STOP;
        Desc[DescIdx+1].Length = DataLen; 
        Desc[DescIdx+1].Buffer = Buffer+BufferOffset;
        return;
    }

    if (OpCode == I2C_MASTER_TRANSFER_WRITE_READ)
    {
        /** The Write Descriptor Number = Total Descriptor Number - Read Descriptor Number*/
        NumDesc -= 2;
    }

    /*Init Write Descriptor*/
    for (i=0; i<NumDesc; i++)
    {
        Desc[i].Flags = I2C_FLAGS_START_WIRTE_STOP;            
        if (i == 0)
        {
            /*EEPROM only write one page at one time*/
            StartPageSize = I2C_SLAVE_EEPROM_PAGE_SIZE - Address%I2C_SLAVE_EEPROM_PAGE_SIZE;                    
            WriteLen = (DataLen > StartPageSize?StartPageSize:DataLen);
        }
        else if (i == NumDesc -1)
        {
            WriteLen = DataLen-DataOffset;
        }
        else
        {
            WriteLen = I2C_SLAVE_EEPROM_PAGE_SIZE;
        }
    
        /*Data address descriptor*/
        Desc[i].Buffer = Buffer + BufferOffset;
        Desc[i].Buffer[0] = ((Address+AddressOffset)&0xFF00)>>8;
        Desc[i].Buffer[1] = (Address+AddressOffset)&0xFF;
        Desc[i].Length = WriteLen + 2;
        if (OpCode == I2C_MASTER_TRANSFER_WRITE)
        {
            memcpy(&(Desc[i].Buffer[2]), Data+DataOffset, WriteLen);
        }
		DataOffset += WriteLen;
        BufferOffset += Desc[i].Length;
        AddressOffset += WriteLen;
    }

    if (OpCode == I2C_MASTER_TRANSFER_WRITE_READ)
    {
        /** The last two descriptor is for read operation*/
        DescIdx = i;
        goto I2C_EEPROM_READ;
    }        
    
}

static void I2CM_InitNfcDescriptors(I2CM_OpCode_t OpCode, uint32_t Address, uint8_t *Data, uint32_t DataLen, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc)
{
    uint8_t  *Buffer;
    uint32_t BufferOffset=0;
    
    Buffer = (uint8_t*)Desc+sizeof(qapi_I2CM_Descriptor_t)*NumDesc;

    if (OpCode == I2C_MASTER_TRANSFER_READ)
    {
        /*Init Read Descriptor*/
        Desc[0].Flags= I2C_FLAGS_START_WIRTE_STOP;
        Desc[0].Length = 1; 
        Desc[0].Buffer = Buffer;
        Desc[0].Buffer[0] = Address&0xFF;

        BufferOffset += 1;
        Desc[1].Flags= I2C_FLAGS_START_READ_STOP;
        Desc[1].Length = DataLen; 
        Desc[1].Buffer = Buffer+BufferOffset;
    }
    else if (OpCode == I2C_MASTER_TRANSFER_WRITE)
    {
        /*Init Write Descriptor*/
		Desc[0].Flags= I2C_FLAGS_START_WIRTE_STOP;
        Desc[0].Length = 1+DataLen; 
        Desc[0].Buffer = Buffer;
        Desc[0].Buffer[0] = Address&0xFF;
        memcpy(&(Desc[0].Buffer[1]), Data, DataLen);
    }
}

static void I2CM_InitRawSlaveDescriptors(I2CM_OpCode_t OpCode, uint8_t *Data, uint32_t DataLen, qapi_I2CM_Descriptor_t *Desc)
{
    uint8_t  *Buffer;
    
    Buffer = (uint8_t*)Desc+sizeof(qapi_I2CM_Descriptor_t);

	Desc->Length = DataLen; 
	Desc->Buffer = Buffer;

    if (OpCode == I2C_MASTER_TRANSFER_READ)
    {
        /*Init Read Descriptor*/
        Desc->Flags= I2C_FLAGS_START_READ_STOP;
    }
    else if (OpCode == I2C_MASTER_TRANSFER_WRITE)
    {
        /*Init Write Descriptor*/
		Desc->Flags= I2C_FLAGS_START_WIRTE_STOP;
        memcpy(Buffer, Data, DataLen);
    }

}

static void I2CM_InitDescriptors(I2C_Slave_Type_t SlaveType, I2CM_OpCode_t OpCode, uint32_t Address, uint8_t *Data, uint32_t DataLen, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc)
{
    if (SlaveType == I2C_SlAVE_TYPE_EEPROM)
    {
        I2CM_InitEepromDescriptors(OpCode, Address, Data, DataLen, Desc, NumDesc);
    }
	else if (SlaveType == I2C_SlAVE_TYPE_NFC)
    {
        I2CM_InitNfcDescriptors(OpCode, Address, Data, DataLen, Desc, NumDesc);
    }
	else if (SlaveType == I2C_SlAVE_TYPE_RAWSLAVE)
	{
		/* The raw i2c slave will ignore the Address parameter and only has one descriptor */
        I2CM_InitRawSlaveDescriptors(OpCode, Data, DataLen, Desc);
	}
}

static void I2CM_TransferEnqueue(I2C_Master_Context_t *I2CM_Ctxt, I2CM_Transfer_t *Transfer)
{
    I2CM_Transfer_t *TempTransfer;
    
    if (I2CM_Ctxt->Transfer == NULL)
    {
        I2CM_Ctxt->Transfer = Transfer;       
    }
    else
    {
        TempTransfer = I2CM_Ctxt->Transfer;
        while (TempTransfer->Next != NULL)
        {
            TempTransfer = TempTransfer->Next;
        }
        TempTransfer->Next = Transfer;
    }
    I2CM_Ctxt->TransferNum++;
}

static I2CM_Transfer_t * I2CM_TransferDequeue(I2C_Master_Context_t *I2CM_Ctxt)
{
    I2CM_Transfer_t *TempTransfer = NULL;
    
    if (I2CM_Ctxt->Transfer != NULL)
    {
        TempTransfer = I2CM_Ctxt->Transfer;
        I2CM_Ctxt->Transfer = TempTransfer->Next;
        I2CM_Ctxt->TransferNum--;        
    }
    return TempTransfer;
}

static void I2CM_PrintTransferResult(uint32_t Status, I2CM_Transfer_t *Transfer)
{
    int i;
    I2CM_OpCode_t OpCode;
    qapi_I2CM_Descriptor_t *Desc;
    uint32_t NumDesc;
    uint32_t SucNumDesc = 0;
    uint8_t  *Data = NULL;
    uint32_t DataLen = 0;
    char *OpStr = "Read";
    char *StaStr;
    uint32_t SlaveAddress;
    uint32_t BusFreqKHz;
    int DataOffSet = 0;
    
    OpCode = Transfer->OpCode;
    Desc = Transfer->Desc;
    NumDesc = Transfer->NumDesc;
    SlaveAddress = Transfer->Config.SlaveAddress;
    BusFreqKHz = Transfer->Config.BusFreqKHz;
    if ((Status == QAPI_OK) || (OpCode == I2C_MASTER_TRANSFER_WRITE))
    {
        if (OpCode == I2C_MASTER_TRANSFER_WRITE)
        {
            Data = Desc[0].Buffer;
            DataLen = 0;
            for (i=0; i<NumDesc; i++)
            {
                if (Desc[i].Transferred > 0)
                {
                    DataLen += Desc[i].Transferred;
                    SucNumDesc++;
                }
            }
            /** Minus the length of EEPROM Address*/
            DataLen -= SucNumDesc*2;
            OpStr = "Write";
        }
        else if (OpCode == I2C_MASTER_TRANSFER_READ)
        {    
            Data = Desc[1].Buffer;
            DataLen = Desc[1].Transferred; 
            OpStr = "Read";
        }
        else if (OpCode == I2C_MASTER_TRANSFER_WRITE_READ)
        {    
            Data = Desc[NumDesc-1].Buffer;
            DataLen = Desc[NumDesc-1].Transferred; 
            OpStr = "WriteRead";
            for (i=0; i<NumDesc-2; i++)
            {
                if (memcmp(Desc[i].Buffer+2, Data+DataOffSet, Desc[i].Length-2))
                {
                    Status = QAPI_ERROR;
                    break;
                }
                DataOffSet += Desc[i].Length-2;
            }
        }        
    }
    StaStr = (Status == QAPI_OK)? "Suc":"Fail";

    I2CM_PRINTF("I2C SLV 0x%02X Freq %d Khz %s %s Err %d.\r\n ", SlaveAddress, BusFreqKHz, OpStr, StaStr, Status);

    if (DataLen > 0)
    {
        I2CM_PRINTF("%s Data Length %d.\r\n", OpStr, DataLen);
        if (OpCode == I2C_MASTER_TRANSFER_READ)
        {
            I2CM_PRINTF("Data: ");
            for(i=0; i<DataLen; i++)
            {
                I2CM_PRINTF("%c", Data[i]);
            }
            I2CM_PRINTF("\r\n");
        }
    }
}

static void I2CM_PrintRawSlaveTransferResult(uint32_t Status, I2CM_Transfer_t *Transfer)
{
    int i;
    char *OpStr = "Read";
    char *StaStr;
    uint32_t SlaveAddress;
    uint32_t BusFreqKHz;
    uint32_t DataLen = 0;
    uint8_t  *Data = NULL;
    qapi_I2CM_Descriptor_t *Desc;
    I2CM_OpCode_t OpCode;

    OpCode = Transfer->OpCode;
    SlaveAddress = Transfer->Config.SlaveAddress;
    BusFreqKHz = Transfer->Config.BusFreqKHz;
    Desc = Transfer->Desc;

    StaStr = (Status == QAPI_OK)? "Suc":"Fail";
	OpStr = (OpCode == I2C_MASTER_TRANSFER_WRITE)?"Write":"Read";

	Data = Desc->Buffer;
	DataLen = 0;

	if (Desc->Transferred > 0)
	{
		DataLen += Desc->Transferred;
	}

    I2CM_PRINTF("I2C SLV 0x%02X Freq %d Khz %s byte %s Err %d.\r\n ", SlaveAddress, BusFreqKHz, OpStr, StaStr, Status);

    if (DataLen > 0)
    {
        I2CM_PRINTF("%s Data Length %d.\r\n", OpStr, DataLen);
        if (OpCode == I2C_MASTER_TRANSFER_READ)
        {
            I2CM_PRINTF("Data: ");
            for(i=0; i<DataLen; i++)
            {
                I2CM_PRINTF("%x ", Data[i]);
            }
            I2CM_PRINTF("\r\n");
        }
    }
}

static QCLI_Command_Status_t I2CM_CheckTransferParameters(uint32_t Instance, uint32_t Frequency, I2C_Slave_Type_t SlaveType, uint16_t Address, uint32_t DataLen)
{
    if(Instance > QAPI_I2C_INSTANCE_SE3_E)
    {
        I2CM_PRINTF("Instance should be 0~3.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    if (I2CM_Ctxt[Instance].State == I2C_MASTER_INSTANCE_CLOSED)
    {
        I2CM_PRINTF("Please open I2C Master Instance %d at first.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    if (I2CM_Ctxt[Instance].State == I2C_MASTER_INSTANCE_TRANSFER_QUEUE_FULL)
    {
        I2CM_PRINTF("Transfer queue is full, please try it later.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((Frequency != I2C_STANDARD_MODE_FREQ_KHZ) 
        && (Frequency != I2C_FAST_MODE_FREQ_KHZ)
        && (Frequency != I2C_FAST_MODE_PLUS_FREQ_KHZ))
    {
        I2CM_PRINTF("The Frequency only support 100/400/1000 kHz.\n");
        return QCLI_STATUS_ERROR_E;
    } 

    if ((SlaveType == I2C_SlAVE_TYPE_EEPROM) && (Address+DataLen> I2C_SLAVE_EEPROM_MEMORY_SIZE))
    {
        I2CM_PRINTF("The size of EEPROM is %d, please reduce the Address or DataLen.\n", I2C_SLAVE_EEPROM_MEMORY_SIZE);
        return QCLI_STATUS_ERROR_E;
    }

    return QCLI_STATUS_SUCCESS_E;
}

static I2CM_Transfer_t* I2CM_PrepareTransferCtxt(qapi_I2CM_Instance_t Instance, I2CM_OpCode_t OpCode, uint32_t Address, uint32_t DataLen, uint8_t *Data)
{
    qapi_I2CM_Descriptor_t *Desc = NULL;
    I2CM_Transfer_t *Transfer = NULL;    
    I2C_Slave_Type_t SlaveType;
    uint8_t *Buffer = NULL;
    uint32_t BufferLen;
    uint32_t NumDesc;

    SlaveType = I2CM_Ctxt[Instance].SlaveType;
    NumDesc = I2CM_GetDescNum(SlaveType, OpCode, Address, DataLen);
    BufferLen = sizeof(I2CM_Transfer_t) + sizeof(qapi_I2CM_Descriptor_t)*NumDesc + DataLen; /*transfer struct: descriptor*NumDesc: DataLen*/
	if (SlaveType == I2C_SlAVE_TYPE_EEPROM)
	{
		if (OpCode == I2C_MASTER_TRANSFER_WRITE)
		{
			BufferLen += NumDesc*2; /*Each EEPROM Page write need 2 bytes address space*/
		}
		else if (OpCode == I2C_MASTER_TRANSFER_READ)
		{
			BufferLen += 2;  /* eeprom: 2 bytes address,  nfc: 1 byte address */
		} 
		else if (OpCode == I2C_MASTER_TRANSFER_WRITE_READ)
		{
			BufferLen += NumDesc*2 + 2 + DataLen;  /* write page address + read address + read buffer lenght*/
		}
	}

    Buffer = (uint8_t *)qapi_Malloc(BufferLen);
    if (Buffer == NULL)
    {
        I2CM_PRINTF("I2C Master transfer failed, No enough memory.\n");
        return NULL;
    }
    memset(Buffer, 0, BufferLen);
    Transfer = (I2CM_Transfer_t*)Buffer;
    Desc = (qapi_I2CM_Descriptor_t *)(Buffer + sizeof(I2CM_Transfer_t));
    I2CM_InitDescriptors(SlaveType, OpCode, Address, Data, DataLen, Desc, NumDesc);
    Transfer->OpCode = OpCode;
    Transfer->NumDesc = NumDesc;
    Transfer->Desc = Desc;
    
    return Transfer;
}

static QCLI_Command_Status_t I2CM_TransferHandler(qapi_I2CM_Instance_t Instance, uint32_t SlaveAddress, uint32_t Frequency, I2CM_OpCode_t OpCode, uint32_t Address, uint32_t DataLen, uint8_t *Data)
{
    qapi_I2CM_Transfer_Config_t *Config;
    I2CM_Transfer_t *Transfer = NULL;    
    qapi_Status_t Status;
   
    Transfer = I2CM_PrepareTransferCtxt(Instance, OpCode, Address, DataLen, Data);
    if (Transfer == NULL)
    {
        return QCLI_STATUS_ERROR_E;        
    }
    
    Config = &Transfer->Config;
    Config->SlaveAddress = SlaveAddress;
    Config->BusFreqKHz = Frequency;
    if ((I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_EEPROM) || (I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_NFC) || (I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_RAWSLAVE))
    {
        Config->Delay = 5;
    }
    
    if (!I2CM_Ctxt[Instance].Config.Blocking)
    {
        I2CM_TransferEnqueue(&I2CM_Ctxt[Instance], Transfer);
        Status = qapi_I2CM_Transfer(Instance, Config, Transfer->Desc, Transfer->NumDesc, cmd_I2CM_TransCallback, (void*)&I2CM_Ctxt[Instance]);        
        if (Status != QAPI_OK)
        {
            if (Status == QAPI_I2CM_ERROR_TRANSFER_BUSY)
            {
                I2CM_Ctxt[Instance].State = I2C_MASTER_INSTANCE_TRANSFER_QUEUE_FULL;
                //I2CM_PRINTF("Transfer queue is full, please try it later.\n");
            }
            else
            {
                I2CM_PRINTF("Error code %d, please cancel or close this I2C Master client.\n", Status);
            }
            return QCLI_STATUS_ERROR_E;        
        }
    }
    else
    {
        Status = qapi_I2CM_Transfer(Instance, Config, Transfer->Desc, Transfer->NumDesc, NULL, NULL); 
        if ((I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_NFC) && (Status == QAPI_OK) && (OpCode == I2C_MASTER_TRANSFER_READ))
        {
            memcpy(Data, Transfer->Desc[1].Buffer, Transfer->Desc[1].Transferred);
        }
        if (I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_EEPROM)
        {
            I2CM_PrintTransferResult(Status, Transfer);        
        }
		else if (I2CM_Ctxt[Instance].SlaveType == I2C_SlAVE_TYPE_RAWSLAVE)
		{
			I2CM_PrintRawSlaveTransferResult(Status, Transfer);
		}

        qapi_Free(Transfer);
        I2CM_Ctxt[Instance].Transfer = NULL;
    }

    I2CM_Ctxt[Instance].State = I2C_MASTER_INSTANCE_READY;

    return QCLI_STATUS_SUCCESS_E;
}

static qapi_Status_t NFC_ReadCapabilityContainer(qapi_I2CM_Instance_t Instance)
{
    int i ;
    uint16_t Data[WORDS_PER_I2C_BLOCK] = {0};
    qapi_Status_t Status;

    Status = I2CM_TransferHandler(Instance, NT3H2111_I2C_ADDRESS, I2C_FAST_MODE_FREQ_KHZ, I2C_MASTER_TRANSFER_READ, REG_CAPABILITY_CONTAINER, BYTES_PER_I2C_BLOCK, (uint8_t*)Data);

    I2CM_PRINTF("Read CC: %d\r\n", Status);
    if (QAPI_OK == Status)
    {
        for(i=0; i<WORDS_PER_I2C_BLOCK; i++)
        {
            I2CM_PRINTF("0x%04x, ", Data[i]);
        }
        I2CM_PRINTF("\r\n");
        
        /* initialize CC if needed */
        if ((Data[WORDS_PER_I2C_BLOCK-1] == 0) && (Data[WORDS_PER_I2C_BLOCK-2] == 0))
        {
            I2CM_PRINTF("Initialize CC ");
            
            /* MUST write back I2C slave address */
            Data[0] = 0x00aa;
            /* content of CC */
            Data[WORDS_PER_I2C_BLOCK-2] = 0x10e1;
            Data[WORDS_PER_I2C_BLOCK-1] = 0x006f;
			Status = I2CM_TransferHandler(Instance, NT3H2111_I2C_ADDRESS, I2C_FAST_MODE_FREQ_KHZ, I2C_MASTER_TRANSFER_WRITE, REG_CAPABILITY_CONTAINER, BYTES_PER_I2C_BLOCK, (uint8_t*)Data);
            if (QAPI_OK == Status)
            {
                I2CM_PRINTF("successfully\r\n");
            }
            else
            {
                I2CM_PRINTF("failed: %d\r\n", Status);
            }
            //NT3H2111_DelayMs(5);
        }
    }
    else
    {
        I2CM_PRINTF("Failed to read CC: %d!!\r\n", Status);
    }
    
    return Status;
}

qapi_Status_t NFCTag_Init(qapi_I2CM_Instance_t Instance)
{
    qapi_Status_t Ret = QAPI_OK;
    
    /* initialize PIO configuration of NFC Tag */
    //nfcTag_pio_init();
    
    qapi_GPIO_Config_t  config;
    memset(&config, 0, sizeof(qapi_GPIO_Config_t));
    config.Dir = QAPI_GPIO_OUTPUT_E;
    Ret = qapi_GPIO_Config(NFC_VDD_PIO, &config);
    if (Ret != QAPI_OK)
    {
        I2CM_PRINTF("Config error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    
    /* power on NFC Tag */
    //nfcTag_power_on();
    Ret = qapi_GPIO_Set(NFC_VDD_PIO, QAPI_GPIO_HIGH_VALUE_E);
    if (Ret != QAPI_OK)
    {
        I2CM_PRINTF("Config error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    Ret = NFC_ReadCapabilityContainer(Instance);
    
    return Ret;
}

qapi_Status_t NfcTag_WritePhoneNumber(qapi_I2CM_Instance_t Instance, uint8_t* Number, uint8_t NumberLen)
{
    qapi_Status_t Status = QAPI_ERROR;
    uint8_t MsgLenCnt = 0;
    uint8_t NDEF_Buffer[NDEF_MAX_SIZE] = {0};
    int Count = 0;
    int i;


    if(NumberLen != NFC_TAG_PHONE_NUM_LEN)
    {
        return Status;
    }

    /* NDEF message Tag */
    NDEF_Buffer[MsgLenCnt++] = NDEF_MSG_TLV;
    /* Length field, fill out later */
    NDEF_Buffer[MsgLenCnt++] = 0;
    /* SR = 1; Short Record
     * TNF = 1; NFC well-known type
     * ME = 1; message end
     * MB = 1; message begin
     */
    NDEF_Buffer[MsgLenCnt++] = 0xD1;
    /* length of the record type */
    NDEF_Buffer[MsgLenCnt++] = 0x01;
    /* length of the payload */
    NDEF_Buffer[MsgLenCnt++] = 1 + NumberLen;
    /* URI record type, ("U") */
    NDEF_Buffer[MsgLenCnt++] = 0x55;
    /* URI identifier, ("https://www.") */
    NDEF_Buffer[MsgLenCnt++] = 0x05;
    /* URL content */
    memcpy(NDEF_Buffer+MsgLenCnt, Number, NumberLen);
    MsgLenCnt += NumberLen;
    /* terminator */
    NDEF_Buffer[MsgLenCnt++] = NDEF_TERMINATOR_TLV;
    /* update the NDEF length field, deduct Tag, Length, and Terminator fields */
    NDEF_Buffer[1] = MsgLenCnt - 3;

    /* need to write a block (16 bytes) at once */
    Count = (MsgLenCnt >> 4) + 1;

    for(i = 0; i < Count; i++)
    {
        Status = I2CM_TransferHandler(Instance, NT3H2111_I2C_ADDRESS, I2C_FAST_MODE_FREQ_KHZ, I2C_MASTER_TRANSFER_WRITE, REG_START_BLOCK+i, BYTES_PER_I2C_BLOCK, &NDEF_Buffer[BYTES_PER_I2C_BLOCK*i]);
        if(QAPI_OK == Status)
        {
            // wait for a while, can poll session register later
            qapi_TMR_Delay_Us(5);
        }
        else
        {
            I2CM_PRINTF("Failed to write phone number to (%d): %d!!\r\n", REG_START_BLOCK+i, Status);
            break;
        }
    }

    if(QAPI_OK == Status)
    {
        I2CM_PRINTF("Successful to write phone number: ");
        for (i=0; i<NumberLen; i++)
        {
            I2CM_PRINTF("%c", *(Number+i));
        }		
        I2CM_PRINTF("\r\n");
    }
    return Status;
}

static QCLI_Command_Status_t nfc_Demo(qapi_I2CM_Instance_t Instance)
{
    uint8_t default_num[] = {0x2b, 0x31, 0x33, 0x36, 0x30, 0x33, 0x38, 0x38, 0x36, 0x37, 0x32, 0x38};

    I2CM_Ctxt[Instance].SlaveType = I2C_SlAVE_TYPE_NFC;       
    NFCTag_Init(Instance);
    NfcTag_WritePhoneNumber(Instance, default_num, sizeof(default_num));

    return QCLI_STATUS_SUCCESS_E;
}


/**
   @brief Open I2C Master Instance.

   @param[1] Instance          I2C Master instance.
   @param[2] Blocking          Blocking mode or not.
   @param[3] Dma               DMA or FIFO mode.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_I2CM_Open(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_I2CM_Config_t *Config;
    qapi_I2CM_Instance_t Instance;
     
    if ((Parameter_Count != 3)
        || (!Parameter_List)
        || (Parameter_List[0].Integer_Value > QAPI_I2C_INSTANCE_SE3_E) 
        || (Parameter_List[1].Integer_Value > 1)
        || (Parameter_List[2].Integer_Value > 1))
    {
        I2CM_PRINTF("Invalid Parameter.\n");
        cmd_I2CM_OpenHelp();
        return QCLI_STATUS_ERROR_E;       
    }
    
    Instance = (qapi_I2CM_Instance_t)Parameter_List[0].Integer_Value;
    if (I2CM_Ctxt[Instance].State != I2C_MASTER_INSTANCE_CLOSED)
    {
        I2CM_PRINTF("I2C Master Instance %d has been opened.\n", Instance);
        return QCLI_STATUS_SUCCESS_E;
    }
    Config = &I2CM_Ctxt[Instance].Config;
    Config->Blocking = Parameter_List[1].Integer_Value;
    Config->Dma = Parameter_List[2].Integer_Value;

   if (qapi_I2CM_Open(Instance, Config) != QCLI_STATUS_SUCCESS_E)
   {
       I2CM_PRINTF("I2C Master open failed.\n");
       return QCLI_STATUS_ERROR_E;       
   }

   I2CM_Ctxt[Instance].State = I2C_MASTER_INSTANCE_READY;
      
   I2CM_PRINTF("I2C Master open success.\n");

   return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Perform an I2C Master transfer.

   @param[1]  SlaveType         I2C Slave type.
   @param[2]  Operation         Transfer operattion, "w": write, "r": read, "wr": write and then read in one transfer.
   @param[3]  Instance          I2C Master instance.
   @param[4]  SlaveAddress      7-bit I2C Slave address.
   @param[5]  Frequency         I2C Master bus speed in kHz, only support 100/400/1000.
   @param[6]  Address           The address in slave device to be written to or read from .
   @param[7]  DataLen           The Length of data in bytes.
   @param[8]  Data              Data to be written, only used when write operation.
   
   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - set successfully.
*/
static QCLI_Command_Status_t cmd_I2CM_Transfer(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_I2CM_Instance_t Instance;
    I2C_Slave_Type_t SlaveType;
    uint32_t SlaveAddress;
    uint32_t Frequency;
    uint32_t Address;
    uint32_t DataLen;
    I2CM_OpCode_t OpCode;
    char *Data;

    if ((Parameter_List) && (!strcmp(Parameter_List[0].String_Value, "nfc")))
    {
        if (Parameter_Count < 2)
        {            
            I2CM_PRINTF("Usage:\ttransfer nfc <Instance>\n");
            I2CM_PRINTF("Options:\n");
            I2CM_PRINTF("\tInstance      : 0~3 I2C Master instance\n");
            I2CM_PRINTF("Example: transfer nfc 1\n");
            goto err2; 
        }
		
        Instance = (qapi_I2CM_Instance_t)Parameter_List[1].Integer_Value;
        nfc_Demo(Instance);
        return QCLI_STATUS_SUCCESS_E;
    }

    if((Parameter_Count < 7) || (!Parameter_List))
    {
        goto err1;
    }
    
    if (!strcmp(Parameter_List[0].String_Value, "eeprom"))
    {
        SlaveType = I2C_SlAVE_TYPE_EEPROM;
    }
    else if (!strcmp(Parameter_List[0].String_Value, "rawslave"))
	{
        SlaveType = I2C_SlAVE_TYPE_RAWSLAVE;
	}
	else
    {
        I2CM_PRINTF("Invalid slave type.\n");  
        goto err2;
    }
    
    if (!strcmp(Parameter_List[1].String_Value, "w"))
    {
        if (Parameter_Count != 8)
        {
            goto err1; 
        }
        OpCode = I2C_MASTER_TRANSFER_WRITE;
    }
    else if (!strcmp(Parameter_List[1].String_Value, "r"))
    {
        if (Parameter_Count != 7)
        {
            goto err1;
        }
        OpCode = I2C_MASTER_TRANSFER_READ;
    }
    else if (!strcmp(Parameter_List[1].String_Value, "wr"))
    {
		if (SlaveType != I2C_SlAVE_TYPE_EEPROM)
		{
			I2CM_PRINTF("Invalid slave operation type, 'wr' only support eeprom\n");  
			goto err2;
		}
        if (Parameter_Count != 7)
        {
            goto err1;
        }
        OpCode = I2C_MASTER_TRANSFER_WRITE_READ;
    }
    else
    {
        I2CM_PRINTF("Invalid operation, only support 'w' ,'r' and 'wr'.\n");  
        goto err2;
    }
    
    Instance = (qapi_I2CM_Instance_t)Parameter_List[2].Integer_Value;
    if (I2CM_Ctxt[Instance].TransferNum >= I2C_MAX_TRANSFER_NUMBER)
    {
        I2CM_Ctxt[Instance].State = I2C_MASTER_INSTANCE_TRANSFER_QUEUE_FULL;
        I2CM_PRINTF("Transfer queue is full, please try it later.\n");
        goto err2;
    }
    
    DataLen = Parameter_List[6].Integer_Value;
    if ((DataLen > I2C_MAX_TRANSFER_DATA_LENGTH) && (I2C_SlAVE_TYPE_EEPROM == SlaveType)
		|| (DataLen > I2C_SLAVE_MAX_TRANSFER_DATA_LENGTH) && (I2C_SlAVE_TYPE_RAWSLAVE == SlaveType))
    {
        I2CM_PRINTF("The Max Transfer Data Lenght is %d.\n", SlaveType == I2C_SlAVE_TYPE_EEPROM ?I2C_MAX_TRANSFER_DATA_LENGTH:I2C_SLAVE_MAX_TRANSFER_DATA_LENGTH);
        goto err2;
    }
        
    SlaveAddress = Parameter_List[3].Integer_Value;
    Frequency = Parameter_List[4].Integer_Value;
    Address = Parameter_List[5].Integer_Value;
	if (OpCode != I2C_MASTER_TRANSFER_READ)
	{
		Data = Parameter_List[7].String_Value;
	}

    if ((OpCode == I2C_MASTER_TRANSFER_WRITE) && (strlen(Data) != DataLen))
    {
        I2CM_PRINTF("The lenght of Data is not same as DataLen.\n");
        goto err2;
    }
	
    if (I2CM_CheckTransferParameters(Instance, Frequency, SlaveType, Address, DataLen) != QCLI_STATUS_SUCCESS_E)
    {
        goto err2;
    }
    I2CM_Ctxt[Instance].SlaveType = SlaveType;
    return I2CM_TransferHandler(Instance, SlaveAddress, Frequency, OpCode, Address, DataLen, (uint8_t*)Data);
err1:
    I2CM_PRINTF("Invalid parameter.\n");   
    cmd_I2CM_TransferHelp();
err2: 
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Cancel I2C Master Transfer.

   @param[1] Instance      I2C Master instance.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_I2CM_Cancel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_I2CM_Instance_t Instance;
     
    if ((Parameter_Count != 1)
        || (!Parameter_List)
        || (Parameter_List[0].Integer_Value > QAPI_I2C_INSTANCE_SE3_E))
    {
        I2CM_PRINTF("Invalid Parameter.\n");
        cmd_I2CM_CancelHelp();
        return QCLI_STATUS_ERROR_E;       
    }
    
    Instance = (qapi_I2CM_Instance_t)Parameter_List[0].Integer_Value;
    if (I2CM_Ctxt[Instance].State == I2C_MASTER_INSTANCE_CLOSED)
    {
        I2CM_PRINTF("Cannot cancel I2C Master Instance %d since it has  not been opened.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }
        
    if (qapi_I2CM_Cancel_Transfer(Instance) != QAPI_OK)
    {
        I2CM_PRINTF("Cancel I2C Master Instance %d failed.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }
    I2CM_Ctxt[Instance].State = I2C_MASTER_INSTANCE_READY;
      
    I2CM_PRINTF("I2C Master Instance %d Cancel successfully.\n", Instance);

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Close I2C Master Instance.

   @param[1] Instance      I2C Master instance.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_I2CM_Close(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_I2CM_Instance_t Instance;
     
    if ((Parameter_Count != 1)
        || (!Parameter_List)
        || (Parameter_List[0].Integer_Value > QAPI_I2C_INSTANCE_SE3_E))
    {
        I2CM_PRINTF("Invalid Parameter.\n");
        cmd_I2CM_CloseHelp();
        return QCLI_STATUS_ERROR_E;       
    }
    
    Instance = (qapi_I2CM_Instance_t)Parameter_List[0].Integer_Value;
    if (I2CM_Ctxt[Instance].State == I2C_MASTER_INSTANCE_CLOSED)
    {
        I2CM_PRINTF("I2C Master Instance %d has been Closed.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }
  
    if (qapi_I2CM_Close(Instance) != QAPI_OK)
    {
        I2CM_PRINTF("Close I2C Master Instance %d failed.\n", Instance);
        return QCLI_STATUS_ERROR_E;        
    }

    memset(&I2CM_Ctxt[Instance], 0, sizeof(I2C_Master_Context_t));
      
    I2CM_PRINTF("I2C Master Instance %d Close successfully.\n", Instance);

    return QCLI_STATUS_SUCCESS_E;
}

static void cmd_I2CM_TransCallback(uint32_t Status, void *CallbackCtxt)
{
    I2CM_Transfer_t *Transfer;
    I2C_Master_Context_t *I2CMCLientCtxt = (I2C_Master_Context_t*)CallbackCtxt;
    
    Transfer = I2CM_TransferDequeue(I2CMCLientCtxt);
    if (Transfer)
    {
        if (I2CMCLientCtxt->SlaveType == I2C_SlAVE_TYPE_EEPROM)
        {
            I2CM_PrintTransferResult(Status, Transfer);
        }
		else if (I2CMCLientCtxt->SlaveType == I2C_SlAVE_TYPE_RAWSLAVE)
		{
			I2CM_PrintRawSlaveTransferResult(Status, Transfer);
		}
        qapi_Free(Transfer);
    }
    
    if (I2CMCLientCtxt->State == I2C_MASTER_INSTANCE_TRANSFER_QUEUE_FULL)
    {
        I2CMCLientCtxt->State = I2C_MASTER_INSTANCE_READY;
    }
}

