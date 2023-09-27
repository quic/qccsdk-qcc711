/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
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
#include "qapi_appi2c.h"
#include "qcli_pal.h"
#include "qcli.h"
#include "qcli_api.h"
#include "appi2c_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define APPI2C_DBG
#ifdef APPI2C_DBG
#define APPI2C_PRINTF(...)     QCLI_Printf(QCLI_APPI2C_Handle, __VA_ARGS__)
#else
#define APPI2C_PRINTF(x, ...)
#endif

#define APPI2C_MASK_IS_SET(mode, mask, value)  ((value) == ((mask) & (mode)))
#define APPI2C_TRANS_BUF_SIZE (256)
#define APPI2C_BUF_PATTERN_ALTERNATE_VALUE (0xAA)

#define APPI2C_GNCALL_RESET				(0x06)
#define APPI2C_GNCALL_WRITE_PROGRAMM	(0x04)
/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum
{
	APPI2C_MASTER,
	APPI2C_SLAVE
} APPI2C_Role_t;

typedef enum
{
	APPI2C_BLOCKING,
	APPI2C_INTERRUPT
} APPI2C_Mode_t;

typedef enum
{
	PatternTypeZeros      = 0,  /** All Zeros pattern */
	PatternTypeOnes       = 1,  /** All Ones pattern */
	PatternTypeIncrement  = 2,  /** Incrementing data (0x00 to 0xFF) */
	PatternTypeDecrement  = 3,  /** Decrementing data (0xFF to 0x00) */
	PatternTypeAlternate  = 4,  /** Alternate 1 and 0 data (0xAA, 0x55, ...) */
	PatternTypeMax = PatternTypeAlternate 
} APPI2C_BufPatternType_t;

typedef struct
{
	APPI2C_Role_t Role;
	APPI2C_Mode_t Mode;
	uint32_t Freq;	
	uint32_t SlaveAddr;
	qapi_APPI2C_Addr_t AddrMode;	
	qapi_APPI2C_Status_t Status;
	APPI2C_BufPatternType_t Pattern;
} APPI2C_DemoConfig_t;

typedef struct
{
	uint32_t Index;
	uint32_t Remain;
	uint8_t *   Buf;
} APPI2C_Buf_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_APPI2C_Handle;


uint8_t *G_APPI2C_Buf;

APPI2C_DemoConfig_t G_Config;

APPI2C_Buf_t G_APPI2C_ContinueBuf;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_APPI2C_Open(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_APPI2C_SlaveTransmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_APPI2C_SlaveReceive(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_APPI2C_Close(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_APPI2C_ShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void APPI2C_S_TransCallBack(qapi_APPI2C_Status_t Status, qapi_APPI2C_UserCallBackParam_t UserParam);
static void APPI2C_ClearBuf(uint8_t *Buf, uint32_t Size);
static void APPI2C_FillBufByPattern(APPI2C_BufPatternType_t Pattern, uint8_t *Buf, uint32_t Size);
static void APPI2C_ReleaseSource(void);
qbool_t APPI2C_CheckPatternInBuffer(APPI2C_BufPatternType_t Pattern, uint8_t *Buf, uint32_t Size);

const QCLI_Command_t APPI2C_CMD_List[] =
{
    /* cmd_function             cmd_string   usage_string                                   description */
    { cmd_APPI2C_Open,          "Open",      "<Role> <Mode> <Freq> [SlaveAddr] [AddrMode]", "Open the App APPI2C controller"  },
    { cmd_APPI2C_Close,         "Close",     " ",                                           "close the app APPI2C controller" },
    { cmd_APPI2C_SlaveTransmit, "SSend",     "<Len> <Pattern> [mode]",                      "Send Len bytes data from slave to master" },
    { cmd_APPI2C_SlaveReceive,  "SReceive",  "<Len> <Pattern>",                             "Receive Len bytes data from master to slave"},
    { cmd_APPI2C_ShowConfig,    "Show",      "",                                            "Show the configuration of i2c slave"}
};
        
const QCLI_Command_Group_t APPI2C_CMD_Group =
{
    "APPI2C",
    (sizeof(APPI2C_CMD_List) / sizeof(APPI2C_CMD_List[0])),
    APPI2C_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
void Initialize_APPI2C_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_APPI2C_Handle = QCLI_Register_Command_Group(NULL, &APPI2C_CMD_Group);
    if (QCLI_APPI2C_Handle)
    {
        APPI2C_PRINTF("App APPI2C Registered \n");
    }
}


/**
   @brief Open APPI2C Master Instance.

   @param[1] Role			   0-master, 1-slave
   @param[2] Mode			   0-Blocking mode, 1-non-blocking mode
   @param[3] Freq              I2c frequency
   @param[3] SlaveAddr         I2c slave address
   @param[3] AddrMode          0-7bit mode, 1-10bit mode

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_APPI2C_Open(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	qapi_Status_t Status;
	qapi_APPI2C_Config_t Config;

    if (!((Parameter_Count == 3 && Parameter_List[0].Integer_Value == 0)
		|| (Parameter_Count == 5))) {
		APPI2C_PRINTF("Wrong usage!:\n"
					"open <Role> <Mode> <Freq> [SlaveAddr] [AddrMode]\n\t"
					"Role: 0->master, 1->slave\n\t"
					"Mode: 0->blocking, 1->non-blocking\n\t"
					"Freq: 0~100kpbs(standard mode), 0~400kpbs(fast mode), or 0~1Mpbs(fast plus mode)\n\t"
					"SlaveAddr: the slave address\n\t"
					"AddrMode: 0->7bit mode, 1-<10bit mode\n");
        return QCLI_STATUS_ERROR_E;
    }

	uint32_t Mode = 0;
	Config.AddrMode = QAPI_APPI2C_ADDR_7BIT_E;
	Mode = (Parameter_List[0].Integer_Value == 0)? (Mode | QAPI_APPI2C_MODE_MASTER):(Mode | QAPI_APPI2C_MODE_SLAVE);
	Mode = (Parameter_List[1].Integer_Value == 0) ? (Mode | QAPI_APPI2C_MODE_BLOCKING) : (Mode | QAPI_APPI2C_MODE_INTERRUPT);
	Config.Mode = Mode;
	Config.FreqHz = Parameter_List[2].Integer_Value;
	if ((Parameter_Count == 5)
		&& ((Mode & QAPI_APPI2C_MODE_ROLE_MASK) == QAPI_APPI2C_MODE_SLAVE))
	{
		Config.SlaveAddr = Parameter_List[3].Integer_Value;
		Config.AddrMode = (Parameter_List[4].Integer_Value == 0) ? (QAPI_APPI2C_ADDR_7BIT_E) : (QAPI_APPI2C_ADDR_10BIT_E);
	}

	G_APPI2C_Buf = qapi_Malloc(APPI2C_TRANS_BUF_SIZE);
	if (!G_APPI2C_Buf)
	{
		APPI2C_PRINTF("Malloc fail!\n");
		return QCLI_STATUS_ERROR_E;
	}

	Status = qapi_APPI2C_Open(&Config);
	if (QAPI_OK != Status)
	{
		qapi_Free(G_APPI2C_Buf);
		APPI2C_PRINTF("App I2c open fail!, errno: %d\n", Status);			
		return QCLI_STATUS_ERROR_E;
	}

	G_Config.Role =	(Parameter_List[0].Integer_Value == 0)? (APPI2C_MASTER):(APPI2C_SLAVE);
	G_Config.Mode = (Parameter_List[1].Integer_Value == 0)? (APPI2C_BLOCKING):(APPI2C_INTERRUPT);
	G_Config.Freq = Config.FreqHz;
	G_Config.SlaveAddr = Config.SlaveAddr;
	G_Config.AddrMode = (qapi_APPI2C_Addr_t)Config.AddrMode;
	G_Config.Status = QAPI_APPI2C_STATUS_IDEL_E;

	APPI2C_PRINTF("APPI2C %s open success.\n", G_Config.Role == APPI2C_MASTER ? "master":"slave");

	return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Perform an APPI2C slave transmission.

   @param[1]  Len          Bytes of transfer
   
   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - set successfully.
*/

static QCLI_Command_Status_t cmd_APPI2C_SlaveTransmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	uint32_t Len, ActualLen=0;
	APPI2C_BufPatternType_t Pattern;
	qapi_Status_t Res;

	if (G_Config.Role == APPI2C_MASTER)
	{
		APPI2C_PRINTF("Master shouldn't use this command!\n");
		return QCLI_STATUS_ERROR_E;	
	}

    if (!(Parameter_Count == 2 || Parameter_Count == 3))
	{
		APPI2C_PRINTF("Wrong usage!:\n"
					"ssend <Len> <Pattern> [mode]\n"
					"\tLen: Buffer size to transfer\n"
					"\tPattern: Buffer pattern, from 0 to 4\n"
					"\tMode(option): Continue mode enable, 1->enable\n");
        return QCLI_STATUS_ERROR_E;
    }

	
	Len = Parameter_List[0].Integer_Value;
	if (Len > APPI2C_TRANS_BUF_SIZE)
	{
		APPI2C_PRINTF("Required transfer len %d exceed the maximum value %d !\n", Len, APPI2C_TRANS_BUF_SIZE);
		return QCLI_STATUS_ERROR_E;
	}
	Pattern = (APPI2C_BufPatternType_t)Parameter_List[1].Integer_Value;
	if (PatternTypeMax  < Pattern)
	{
		APPI2C_PRINTF("Required buf pattern type %d exceed the maximum value %d!\n", Pattern, PatternTypeMax);
        return QCLI_STATUS_ERROR_E;
	}

	if (Parameter_Count == 3 && Parameter_List[2].Integer_Value==1)
   	{
		if (G_Config.Mode == APPI2C_BLOCKING) 
		{
			APPI2C_PRINTF("Continue mode require non-blocking mode.\n");
			return QCLI_STATUS_ERROR_E;
		}
		G_APPI2C_ContinueBuf.Index=0;
		G_APPI2C_ContinueBuf.Remain=Len;
		G_APPI2C_ContinueBuf.Buf=G_APPI2C_Buf;
	}

	if (G_APPI2C_Buf == NULL)
	{
		return QCLI_STATUS_ERROR_E;
	}

	APPI2C_ClearBuf(G_APPI2C_Buf, Len);
	APPI2C_FillBufByPattern(Pattern, G_APPI2C_Buf, Len);
	ActualLen = Len;

	G_Config.Pattern = Pattern;
	G_Config.Status = QAPI_APPI2C_STATUS_TRANSMITING_E;
	if (G_Config.Mode == APPI2C_BLOCKING)
	{
		APPI2C_PRINTF("start sending %d bytes!\n", ActualLen);
		Res = qapi_APPI2C_SlaveTransmit(G_APPI2C_Buf, &ActualLen, NULL);
		if (QAPI_APPI2C_ERROR_READWRITE_CORRUPT == Res)
		{
			APPI2C_PRINTF("Receive a write signal, retry on the master side!\n");
			return QCLI_STATUS_ERROR_E;
		}
		if ((QAPI_OK != Res)
			&& (ActualLen != Len))
		{
			APPI2C_PRINTF("Slave transmission abort, has transfer %d bytes, abort reason: %d\n", ActualLen, Res);
			return QCLI_STATUS_ERROR_E;
		}
		APPI2C_PRINTF("Finish slave transmission, please check the content on the master side!\n");
	}
	else
	{
		Res = qapi_APPI2C_SlaveTransmit(G_APPI2C_Buf, &ActualLen, APPI2C_S_TransCallBack);
		if (QAPI_OK != Res)
		{
			APPI2C_PRINTF("Slave transmission error, has transfer %d bytes, errno: %d\n", ActualLen, Res);
			return QCLI_STATUS_ERROR_E;
		}
		APPI2C_PRINTF("Start interrupt transmission, wait for finish...\n");
	}

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Perform an APPI2C slave receive.

   @param[1]  Len          Bytes of transfer

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_APPI2C_SlaveReceive(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	uint32_t Len, ActualLen=0;
	APPI2C_BufPatternType_t Pattern;
	qapi_Status_t Res;
	QCLI_Command_Status_t Ret = QCLI_STATUS_SUCCESS_E;
	qbool_t Check, NeedCheck=false;

	if (G_Config.Role == APPI2C_MASTER)
	{
		APPI2C_PRINTF("Master shouldn't use this command!\n");
		return QCLI_STATUS_ERROR_E;	
	}

    if (Parameter_Count != 2)
	{
		APPI2C_PRINTF("Wrong usage!:\n"
					"sreceive <Len> <Pattern>\n"
					"\tLen: Buffer size to transfer\n"
					"\tPattern: Buffer pattern, from 0 to 4\n");
        return QCLI_STATUS_ERROR_E;
    }
	
	Len = Parameter_List[0].Integer_Value;
	if (Len > APPI2C_TRANS_BUF_SIZE)
	{
		APPI2C_PRINTF("Required transfer len %d exceed the maximum value %d !\n", Len, APPI2C_TRANS_BUF_SIZE);
		return QCLI_STATUS_ERROR_E;
	}
	Pattern = (APPI2C_BufPatternType_t)Parameter_List[1].Integer_Value;
	if (PatternTypeMax  < Pattern)
	{
		APPI2C_PRINTF("Required buf pattern type %d exceed the maximum value %d!\n", Pattern, PatternTypeMax);
		return QCLI_STATUS_ERROR_E;
	}

	if (G_APPI2C_Buf == NULL)
	{
		return QCLI_STATUS_ERROR_E;
	}
	
	APPI2C_ClearBuf(G_APPI2C_Buf, Len);
	ActualLen = Len;

	G_Config.Pattern = Pattern;
	G_Config.Status = QAPI_APPI2C_STATUS_RECEIVING_E;
	if (G_Config.Mode == APPI2C_BLOCKING)
	{
		Res = qapi_APPI2C_SlaveReceive(G_APPI2C_Buf, &ActualLen, NULL);
		if (QAPI_APPI2C_ERROR_READWRITE_CORRUPT == Res)
		{
			APPI2C_PRINTF("Receive a read signal, retry on the master side!\n");
			return QCLI_STATUS_ERROR_E;
		}
		if ((QAPI_OK == Res)
			|| (ActualLen == Len))
		{
			APPI2C_PRINTF("Finish receiving %d bytes, user size:%d, start checking the content...\n", ActualLen, Len);
			Ret = QCLI_STATUS_SUCCESS_E;
			NeedCheck = true;
		}
		else if (QAPI_APPI2C_ERROR_TRANSFER_GNCALL == Res)
		{
			APPI2C_PRINTF("Receiving general call!, the subcommand is %x!\n", G_APPI2C_Buf[0]);
			NeedCheck = false;
		}
		else
		{
			APPI2C_PRINTF("Slave receiving abort, has transfer %d bytes, abort reason: %d\n", ActualLen, Res);
			Ret = QCLI_STATUS_ERROR_E;
			NeedCheck = true;
		}

		if (NeedCheck)
		{
			Check = APPI2C_CheckPatternInBuffer(Pattern, G_APPI2C_Buf, ActualLen);
			APPI2C_PRINTF("Check %s\n!", Check ? "pass":"fail");

			APPI2C_PRINTF("Actual receive buf:\n");
			for (int i=0; i<ActualLen; i++)
			{
				APPI2C_PRINTF("%x, ", G_APPI2C_Buf[i]);
			}
		}
	} 
	else 
	{
		Res = qapi_APPI2C_SlaveReceive(G_APPI2C_Buf, &ActualLen, APPI2C_S_TransCallBack);
		if (QAPI_OK != Res)
		{
			APPI2C_PRINTF("Slave receiving error, has transfer %d bytes, errno: %d\n", ActualLen, Res);
			Ret = QCLI_STATUS_ERROR_E;
		}
		else
		{
			APPI2C_PRINTF("Start interrupt receiving, wait for finish...\n");
			Ret = QCLI_STATUS_ERROR_E;
		}
	}

    return Ret;
}

/**
   @brief Close APPI2C controller.

   @return
   QCLI_STATUS_ERROR_E   - Invalid input paramters.
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_APPI2C_Close(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	qapi_Status_t Res;

	Res = qapi_APPI2C_Close();
	if (QAPI_OK != Res)
	{
		APPI2C_PRINTF("AppI2c close fail! errno: %d\n", Res);
		return QCLI_STATUS_ERROR_E;
	}

	APPI2C_ReleaseSource();
	APPI2C_PRINTF("AppI2c close done!\n");
	G_Config.Status = QAPI_APPI2C_STATUS_IDEL_E;

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Show APPI2C configuration.

   @return
   QCLI_STATUS_SUCCESS_E - Open successfully.
*/
static QCLI_Command_Status_t cmd_APPI2C_ShowConfig(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
	APPI2C_PRINTF("Show the i2c configuration:\n");

	APPI2C_PRINTF("\tRole: %s\n", (G_Config.Role == APPI2C_MASTER) ? "master":"slave");
	APPI2C_PRINTF("\tMode: %s\n", (G_Config.Mode == APPI2C_BLOCKING) ? "blocking":"interrupt");

	if (APPI2C_SLAVE == G_Config.Role)
	{
		APPI2C_PRINTF("\tFreq: %d\n", G_Config.Freq);
		APPI2C_PRINTF("\tSlave Addr: %x\n", G_Config.SlaveAddr);
		APPI2C_PRINTF("\tAddrMode: %s\n", (G_Config.AddrMode == QAPI_APPI2C_ADDR_7BIT_E) ? "7bit":"10bit");
	}

    return QCLI_STATUS_SUCCESS_E;
}

qbool_t APPI2C_CheckPatternInBuffer(APPI2C_BufPatternType_t Pattern, uint8_t *Buf, uint32_t Size)
{
    uint32_t Idx;
    uint8_t  ChkVal;
    qbool_t  RetVal = false;

    if (!Buf || Size == 0)
        return false;

    switch (Pattern) {
        case PatternTypeZeros:
        case PatternTypeOnes:
        {
            ChkVal = (PatternTypeZeros == Pattern) ? (0x00) : (0xFF);
            for (Idx = 0; Idx < Size; Idx++) {
                if (Buf[Idx] != ChkVal)
                    break;
            }
        }
        break;

        case PatternTypeIncrement:
        {
            for (Idx = 0; Idx < Size; Idx++) {
                if (Buf[Idx] != (Idx & 0xFF))
                    break;
            }
        }
        break;

        case PatternTypeDecrement:
        {
            for (Idx = 0; Idx < Size; Idx++) {
                if (Buf[Idx] != (0xFF - (Idx & 0xFF)))
                    break;
            }
        }
        break;

        case PatternTypeAlternate:
        {
            ChkVal = APPI2C_BUF_PATTERN_ALTERNATE_VALUE;
            for (Idx = 0; Idx < Size; Idx++) {
                if (Buf[Idx] != ChkVal) {
                    break;
                }
                ChkVal = ~ChkVal;
            }
        }
        break;

        default:
        {
            /* Force Failure for unknown pattern. */
            Idx = 0;
        }
    }

    if (Idx == Size)
        RetVal = true;

    return RetVal;
}

static void APPI2C_S_TransCallBack(qapi_APPI2C_Status_t Status, qapi_APPI2C_UserCallBackParam_t UserParam)
{
	char *Str1 = (G_Config.Status == QAPI_APPI2C_STATUS_TRANSMITING_E)?("transmission"):("receiving");
	char *Str2 = (G_Config.Status == QAPI_APPI2C_STATUS_TRANSMITING_E)?("Please checking contents on master side"):("Checking contents");
	qbool_t Check;
	switch(Status) 
	{
		case QAPI_APPI2C_STATUS_DONE_E:
			APPI2C_PRINTF("%s done!, transfer size:%d\n", Str1, UserParam.ActualSize);
			break;
		case QAPI_APPI2C_STATUS_ABORT_E:
			if (UserParam.ActualSize == UserParam.UserSize)
			{
				APPI2C_PRINTF("%s done!, size: %d\n", Str1, UserParam.UserSize);
			}
			else
			{
				if (G_APPI2C_ContinueBuf.Buf != NULL) 
				{
					qapi_Status_t Res;
					uint32_t SendLen;
					G_APPI2C_ContinueBuf.Index += UserParam.ActualSize;
					G_APPI2C_ContinueBuf.Remain -= UserParam.ActualSize;
					APPI2C_PRINTF("%s done!, has transfer:%d, remain:%d\n", Str1, G_APPI2C_ContinueBuf.Index, G_APPI2C_ContinueBuf.Remain);

					SendLen=G_APPI2C_ContinueBuf.Remain;
					if (G_APPI2C_ContinueBuf.Remain > 0) 
					{
						Res = qapi_APPI2C_SlaveTransmit(G_APPI2C_ContinueBuf.Buf + G_APPI2C_ContinueBuf.Index, &SendLen, APPI2C_S_TransCallBack);
						if (QAPI_OK != Res) {
							APPI2C_PRINTF("Slave transmission error, has transfer %d bytes, errno: %d\n", SendLen, Res);
							break;
						}
						APPI2C_PRINTF("Start interrupt transmission, wait for finish...\n");
					}
				} else {
					APPI2C_PRINTF("%s abort! actual size: %d, total size: %d\n", Str1, UserParam.ActualSize, UserParam.UserSize);
				}
				
			}
			break;
		case QAPI_APPI2C_STATUS_TIMEOUT:
			APPI2C_PRINTF("%s timeout!\n", Str1);
			break;
		case QAPI_APPI2C_STATUS_GNCALL_E:
			APPI2C_PRINTF("Receive general call!\n");
			APPI2C_PRINTF("\tGeneral command byte: %x\n", *(UserParam.Buf));
			break;
		default: 
			/* This shouldn't happen */
			APPI2C_PRINTF("Error Status! status id: %d\n", Status);
			break;
	}

	if (G_Config.Status == QAPI_APPI2C_STATUS_RECEIVING_E
		&& Status != QAPI_APPI2C_STATUS_GNCALL_E)	
	{
		APPI2C_PRINTF("Transfer user size: %d, actual size: %d, %s...\n", \
						UserParam.UserSize, UserParam.ActualSize, Str2);
		Check = APPI2C_CheckPatternInBuffer(G_Config.Pattern, UserParam.Buf, UserParam.ActualSize);
		APPI2C_PRINTF("Contents check %s!\n", Check?"pass":"fail");

		APPI2C_PRINTF("Actual receive buf:\n");
		for (int i=0; i<UserParam.ActualSize; i++)
		{
			APPI2C_PRINTF("%x, ", G_APPI2C_Buf[i]);
		}
	}
	else if	(Status == QAPI_APPI2C_STATUS_GNCALL_E)
	{
		switch (UserParam.Buf[0]) 
		{
			case APPI2C_GNCALL_RESET:
				APPI2C_PRINTF("Receive general call reset!\n");
				break;
			case APPI2C_GNCALL_WRITE_PROGRAMM:
				APPI2C_PRINTF("Receive general call wrtite programmable!\n");
				break;
			default:
				APPI2C_PRINTF("Receive general call with command: %x!\n", UserParam.Buf[0]);
		}
	}
}

static void APPI2C_ReleaseSource(void)
{
	if (G_APPI2C_Buf)
	{
		qapi_Free(G_APPI2C_Buf);
	}
}

static void APPI2C_ClearBuf(uint8_t *Buf, uint32_t Size)
{
	if (Buf != NULL)
	{
		memset(Buf, 0, Size);
	}
}

static void APPI2C_FillBufByPattern(APPI2C_BufPatternType_t Pattern, uint8_t *Buf, uint32_t Size)
{
    uint32_t Idx;
    uint8_t  FillVal;

    if (!Buf)
	{
		return;
	}

    switch (Pattern) {
        case PatternTypeZeros:
        case PatternTypeOnes:
        {
            FillVal = (PatternTypeZeros == Pattern) ? (0x00) : (0xFF);
            memset(Buf, FillVal, Size);
        }
        break;

        case PatternTypeIncrement:
        {
            for (Idx = 0; Idx < Size; Idx++) 
			{
                Buf[Idx] = (Idx & 0xFF);
            }
        }
        break;

        case PatternTypeDecrement:
        {
            for (Idx = 0; Idx < Size; Idx++) 
			{
                Buf[Idx] = 0xFF - (Idx & 0xFF);
            }
        }
        break;

        case PatternTypeAlternate:
        {
            FillVal = APPI2C_BUF_PATTERN_ALTERNATE_VALUE;
            for (Idx = 0; Idx < Size; Idx++) 
			{
                Buf[Idx] = FillVal;
                FillVal = ~FillVal;
            }
        }
        break;

        default:
        {
            /* Do nothing here. */
        }
    }
}
