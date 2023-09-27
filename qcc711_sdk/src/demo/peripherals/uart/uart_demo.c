/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_task.h"
#include "qapi_heap.h"
#include "qapi_uart.h"

#include "qcli_pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "uart_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define UART_DBG
#ifdef UART_DBG
#define UART_PRINTF(...)     QCLI_Printf(QCLI_Uart_Handle, __VA_ARGS__)
#else
#define UART_PRINTF(x, ...)
#endif

#define UART_TSK_EVENT_INIT        (1) /**< Task event init */
#define UART_TSK_EVENT_RX          (2) /**< Task event indicating the UART rx event */

#define UART_INSTANCE_VAVLID(instance) (instance >=0 && instance != ConsoleUartInstance && instance < QAPI_UART_INSTANCE_MAX)

#define INSTANCE_2_UART(instance) (UART_INSTANCE_VAVLID(instance)? & GUartCtrl[instance] : NULL)

#define IN_RANGE(val, min, max) (val >=min && val <= max)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define UART_INPUT_9BIT_IS_1_CHARACTER                     ("1\1")
#define UART_INPUT_9BIT_IS_0_CHARACTER                     ("0\0")

#define UART_CMD_CONSTDATA(Num)      Num, Num, Num, Num, Num, Num, Num, Num, Num, Num
#define UART_CMD_BUFLEN_MIN          1
#define UART_CMD_BUFLEN_MAX          1000
#define UART_CMD_PATTERN             0x76

#define UART_TASK_TIMEOUT            5

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

typedef enum{
    WORK_MODE_ECHO,
    WORK_MODE_9BITS_HW_M,
    WORK_MODE_9BITS_HW_S,
    WORK_MODE_9BITS_SW_M,
    WORK_MODE_9BITS_SW_S,
    WORK_MODE_9BITS_SW_DUAL,
    WORK_MODE_9BITS_HW_DUAL,
    WORK_MODE_TX_INVERT,
    WORK_MODE_IDLE
}WORK_MODE_E;

typedef struct UART_s
{
    qapi_UART_Instance_t      Instance;
    qbool_t                   Enabled;
    WORK_MODE_E               WorkMode;

    qapi_TSK_Handle_t         UartTask;
    uint32_t                  BaudRate;
    qapi_UART_Parity_Mode_t   ParityMode;
    qapi_UART_Num_Stop_Bits_t NumStopBits;
    qapi_UART_Bits_Per_Char_t BitsPerChar;
    qbool_t                   EnableLoopback;
    qbool_t                   EnableFlowCtrl;
    qbool_t                   DmaEnable;
    qbool_t                   TxInvert;
    uint32_t                  BufferSize;
    uint32_t                  RxBufferSize;
    uint8_t                   TransmitAddr;

    char*                     UartBuf;          /*< app buffer size keep same with  driver buffer size */
    uint32_t                  StrLen;           /*< used for 9 bit work mode */
    uint64_t                  TxBytes;
    uint64_t                  RxBytes;
} UART_t;

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

QCLI_Group_Handle_t QCLI_Uart_Handle;  /* Handle for our QCLI Command Group. */
UART_t GUartCtrl[QAPI_UART_INSTANCE_MAX];
int32_t ConsoleUartInstance = -1;

uint32_t BaudRateSet[] = {2400, 4800, 9600, 19200, 28800, 38400, 57600, 76800,
                          115200, 125000, 250000, 500000, 1000000, 2000000
                          };

 /**
    UART const Tx test data in RRAM,  1000 = 10^3.
 */
 const char UartRramTxBuf[UART_CMD_BUFLEN_MAX] = {UART_CMD_CONSTDATA(UART_CMD_CONSTDATA(UART_CMD_CONSTDATA(UART_CMD_PATTERN)))};

 /*-------------------------------------------------------------------------
 * Function declaration
 *-----------------------------------------------------------------------*/

/* Uart demo command functions. */
static QCLI_Command_Status_t cmd_Uart_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_Set9bitsParams(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_StartWorking(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_StopWorking(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_ConsoleSwitch(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_GetInfo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Uart_ClearStats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Internal help functions. */
static void UartTaskStart(qapi_UART_Instance_t Instance);
static uint32_t UartTasks(qapi_TSK_Handle_t Handle, uint32_t EventMask, void *Param);
static qbool_t UartEnabled(qapi_UART_Instance_t Instance);
static void UartEnableHelp(void);
static qbool_t UARTCheckBaudRate(uint32_t BaudRate);

static qapi_Status_t UartInit(qapi_UART_Instance_t Instance, uint32_t BaudRate, qapi_UART_Parity_Mode_t ParityMode,
    qapi_UART_Num_Stop_Bits_t NumStopBits, qapi_UART_Bits_Per_Char_t BitsPerChar, qbool_t EnableLoopback,
    qbool_t EnableFlowCtrl, qbool_t DmaEnable, uint32_t BufferSize, uint32_t RxStaleCnt, qbool_t TxInvert);
static qapi_Status_t UartDeinit(qapi_UART_Instance_t Instance);
static qapi_Status_t UartWrite(qapi_UART_Instance_t Instance, uint32_t length, const char *buffer);
static qapi_Status_t UartClearStats(qapi_UART_Instance_t Instance);
static qapi_Status_t UartGetParam(qapi_UART_Instance_t Instance, uint32_t *BaudRate, qapi_UART_Parity_Mode_t *ParityMode,
    qapi_UART_Num_Stop_Bits_t *NumStopBits, qapi_UART_Bits_Per_Char_t *BitsPerChar, qbool_t *EnableLoopback,
	qbool_t *EnableFlowCtrl, qbool_t *DmaEnable, uint32_t *BufferSize);
static qapi_Status_t UartGetStats(qapi_UART_Instance_t Instance, uint64_t *TxBytes, uint64_t *RxBytes);
static void UartConstructDataFor9bitSwMode(char* OutBuffer, uint8_t Addr, char* Buffer, uint32_t Len);

/* Callback functions. */
static void UartRxCbCommon(unsigned int Instance, uint32_t Status, unsigned int Length, void *CbCtxt);

const QCLI_Command_t UART_CMD_List[] =
{
    /* cmd_function            cmd_string       usage_string                        description */
    { cmd_Uart_Enable,         "Enable",        "",                                 "Enable Uart instance"},
    { cmd_Uart_Disable,        "Disable",       "[instance]",                       "Disable Uart instance"},
    { cmd_Uart_Set9bitsParams, "9BitsParam",    "[instance] [addr] [string] [len]", "Set 9bits mode params"},
    { cmd_Uart_StartWorking,   "StartWork",     "[instance] [mode]",                "Start testing"},
    { cmd_Uart_StopWorking,    "StopWork",      "[instance]",                       "Stop testing"},
    { cmd_Uart_ConsoleSwitch,  "SwitchConsole", "[instance]",                       "Switch console uart instance"},
    { cmd_Uart_GetInfo,        "GetInfo",       "[instance]",                       "Get information of uart instance."},
    { cmd_Uart_ClearStats,     "ClearStats",    "[instance]",                       "Clear UART and stats."}
};

const QCLI_Command_Group_t UART_CMD_Group =
{
    "UART",
    (sizeof(UART_CMD_List) / sizeof(UART_CMD_List[0])),
    UART_CMD_List
};

/*-------------------------------------------------------------------------
 * Function defination
 *-----------------------------------------------------------------------*/
void Initialize_Uart_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Uart_Handle = QCLI_Register_Command_Group(NULL, &UART_CMD_Group);
    if(QCLI_Uart_Handle)
    {
        UART_PRINTF("UART Registered \n");
    }
    ConsoleUartInstance = PAL_Uart_Instance_Get();
}

static QCLI_Command_Status_t cmd_Uart_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Ret_Val = QCLI_STATUS_SUCCESS_E;
    qapi_UART_Instance_t Instance;
    qapi_Status_t Result;
    uint32_t BaudRate, BufferSize, RxStaleCount;
    qapi_UART_Parity_Mode_t ParityMode;
    qapi_UART_Num_Stop_Bits_t NumStopBits;
    qapi_UART_Bits_Per_Char_t BitsPerChar;
    qbool_t EnableLoopback, EnableFlowCtrl;
    qbool_t DmaEnable, TxInvert = false;
    uint32_t ReceiveAddr;

    if(Parameter_Count < 10 || !Parameter_List)
    {
        UartEnableHelp();
        return QCLI_STATUS_SUCCESS_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;

    if (UartEnabled(Instance))
    {
        UART_PRINTF("Uart instace %d is already enabled\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    BaudRate = Parameter_List[1].Integer_Value;
    ParityMode = (qapi_UART_Parity_Mode_t)Parameter_List[2].Integer_Value;
    NumStopBits = (qapi_UART_Num_Stop_Bits_t)Parameter_List[3].Integer_Value;
    BitsPerChar = (qapi_UART_Bits_Per_Char_t)Parameter_List[4].Integer_Value;
    EnableLoopback = Parameter_List[5].Integer_Value ? true : false;
    EnableFlowCtrl = Parameter_List[6].Integer_Value ? true : false;
    DmaEnable = Parameter_List[7].Integer_Value ? true : false;
    BufferSize = Parameter_List[8].Integer_Value;
    RxStaleCount = Parameter_List[9].Integer_Value;

    if (!UARTCheckBaudRate(BaudRate))
    {
        UART_PRINTF("Baud rate(%d) invalid.\n", BaudRate);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(ParityMode, QAPI_UART_NO_PARITY_E, QAPI_UART_MARK_PARITY_E))
    {
        UART_PRINTF("Parity mode(%d) invalid.\n", ParityMode);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(NumStopBits, QAPI_UART_1_0_STOP_BITS_E, QAPI_UART_3_0_STOP_BITS_E)){
        UART_PRINTF("Num of stop bits(%d) invalid.\n", NumStopBits);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(BitsPerChar, QAPI_UART_5_BITS_PER_CHAR_E, QAPI_UART_9_BITS_PER_CHAR_HW_E)){
        UART_PRINTF("Bits of per charater(%d) invalid.\n", BitsPerChar);
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(BufferSize, 64, 1024)){
        UART_PRINTF("Buffer size(%d) should be in rang 64Bytes ~ 1024Bytes.\n", BufferSize);
        return QCLI_STATUS_ERROR_E;
    }
    if(!IN_RANGE(Parameter_List[5].Integer_Value, 0, 1) ||
       !IN_RANGE(Parameter_List[6].Integer_Value, 0, 1) ||
       !IN_RANGE(Parameter_List[7].Integer_Value, 0, 1))
    {
        UART_PRINTF("Invalid parameter: 0 - disable,  1 - enable.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if (!IN_RANGE(RxStaleCount, 1, 1023)){
        UART_PRINTF("Rx Stale count(%d) should be in rang 1 ~ 1023.\n", RxStaleCount);
        return QCLI_STATUS_ERROR_E;
    }

    if(BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_HW_E)
    {
        if(Parameter_Count != 11)
        {
            UART_PRINTF("Missing parameter in UART 9-bit hw mdoe.\n", RxStaleCount);
            return QCLI_STATUS_ERROR_E;
        }

        ReceiveAddr = Parameter_List[10].Integer_Value;
        if(!IN_RANGE(ReceiveAddr, 1, 255))
        {
            UART_PRINTF("ReceiveAddr(%d) should be in rang 1 ~ 255.\n", ReceiveAddr);
            return QCLI_STATUS_ERROR_E;
        }
    }

    if(Parameter_Count == 11 && BitsPerChar == QAPI_UART_8_BITS_PER_CHAR_E)
    {
        TxInvert = Parameter_List[10].Integer_Value ? true : false;
    }

    UART_PRINTF("Open uart instance %d\n", Instance);
    Result = UartInit(Instance, BaudRate, ParityMode, NumStopBits, BitsPerChar, EnableLoopback,
        EnableFlowCtrl, DmaEnable, BufferSize, RxStaleCount, TxInvert);

    if (Result != QAPI_OK)
    {
        UART_PRINTF("Enable uart instance failed.");
        Ret_Val = QCLI_STATUS_ERROR_E;
    }
    if(BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_HW_E)
    {
        Result = qapi_UART_Set_TRAddress(Instance, QAPI_UART_RA_E, (uint8_t)ReceiveAddr);

        if (Result != QAPI_OK)
        {
            Ret_Val = QCLI_STATUS_ERROR_E;
        }
    }

    return Ret_Val;
}

static QCLI_Command_Status_t cmd_Uart_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;
    QCLI_Command_Status_t Ret_Val = QCLI_STATUS_SUCCESS_E;
    qapi_Status_t Result;
    UART_t *Uart = NULL;

    if(Parameter_Count < 1)
    {
        UART_PRINTF("Missing parameters: Disable <instance>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    if (!UartEnabled(Instance))
    {
        UART_PRINTF("ERROR: UART %d is not enabled.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    Uart = INSTANCE_2_UART(Instance);
    if (!Uart)
    {
        return QCLI_STATUS_ERROR_E;
    }

    if(Uart->WorkMode != WORK_MODE_IDLE)
    {
        UART_PRINTF("ERROR: UART %d is in task, need stop task firstly.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    UART_PRINTF("Close uart instance %d\n", Instance);
    Result = UartDeinit(Instance);
    if (Result != QAPI_OK)
    {
        UART_PRINTF("Uart deinit failed.");
        Ret_Val = QCLI_STATUS_ERROR_E;
    }

    return Ret_Val;
}

static QCLI_Command_Status_t cmd_Uart_Set9bitsParams(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;
    qapi_Status_t Result;
    uint8_t  TransmitAddr;
    uint32_t Len = 0, TxLenOf9BitSw = 0;

    if(Parameter_Count < 3)
    {
        UART_PRINTF("Missing parameters: 9BitsParam <instance> <addr> <string> [len]\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    TransmitAddr = Parameter_List[1].Integer_Value;

    if (!UartEnabled(Instance))
    {
        UART_PRINTF("ERROR: UART %d is not enabled.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    if(GUartCtrl[Instance].BitsPerChar < QAPI_UART_9_BITS_PER_CHAR_SW_E)
    {
        UART_PRINTF("ERROR: UART %d is not in 9-bit mode.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    GUartCtrl[Instance].TransmitAddr = TransmitAddr;

    if(Parameter_List[2].String_Value != NULL)
    {
        GUartCtrl[Instance].StrLen = strlen(Parameter_List[2].String_Value);
        memscpy(GUartCtrl[Instance].UartBuf, GUartCtrl[Instance].BufferSize, Parameter_List[2].String_Value, GUartCtrl[Instance].StrLen);
    }
    else
    {
        UART_PRINTF("Please set the transmit string.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if(Parameter_Count == 4)
    {
        Len = Parameter_List[3].Integer_Value;

        if (!IN_RANGE(Len, UART_CMD_BUFLEN_MIN, UART_CMD_BUFLEN_MAX))
        {
            UART_PRINTF("Test size should be in rang 1Bytes ~ 1000Bytes.\n", Len);
            return QCLI_STATUS_ERROR_E;
        }
    }

    if(GUartCtrl[Instance].BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_HW_E)
    {
        Result = qapi_UART_Set_TRAddress(Instance, QAPI_UART_TA_E, TransmitAddr);

        if (Result != QAPI_OK)
        {
            return QCLI_STATUS_ERROR_E;
        }
        if(Len)
        {
            UartWrite(Instance, Len, UartRramTxBuf);
        }
        else
        {
            memscpy(GUartCtrl[Instance].UartBuf, GUartCtrl[Instance].BufferSize, Parameter_List[2].String_Value, GUartCtrl[Instance].StrLen);
            UartWrite(Instance, GUartCtrl[Instance].StrLen, GUartCtrl[Instance].UartBuf);
        }
    }
    else if(GUartCtrl[Instance].BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_SW_E)
    {
        TxLenOf9BitSw = GUartCtrl[Instance].StrLen * 2 + 2;
        if(TxLenOf9BitSw > GUartCtrl[Instance].RxBufferSize)
        {
            UART_PRINTF("9-bit SW Tx size should not bigger than buffer size.\n", Len);
            return QCLI_STATUS_ERROR_E;
        }
        UartConstructDataFor9bitSwMode(GUartCtrl[Instance].UartBuf, TransmitAddr, Parameter_List[2].String_Value, GUartCtrl[Instance].StrLen);
        UartWrite(Instance, TxLenOf9BitSw, GUartCtrl[Instance].UartBuf);
    }

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Uart_StartWorking(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;
    WORK_MODE_E WorkMode;

    if(Parameter_Count < 2)
    {
        UART_PRINTF("Missing parameters: StartWork <instance> <mode>.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    WorkMode = (WORK_MODE_E)Parameter_List[1].Integer_Value;

    if (!UartEnabled(Instance))
    {
        UART_PRINTF("ERROR: UART %d is not enabled.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    if (!IN_RANGE(WorkMode, WORK_MODE_ECHO, WORK_MODE_TX_INVERT))
    {
        UART_PRINTF("ERROR: work mode is invalid.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if(WorkMode == WORK_MODE_TX_INVERT )//&& GUartCtrl[Instance].TxInvert)
    {
        //UartWrite(Instance, 21, "UART TX REVERT TEST!!");
        UartWrite(Instance, 4, "TEST");
        return QCLI_STATUS_SUCCESS_E;
    }

    if(WorkMode == WORK_MODE_9BITS_SW_DUAL && GUartCtrl[Instance].BitsPerChar != QAPI_UART_9_BITS_PER_CHAR_SW_E)
    {
        UART_PRINTF("ERROR: work mode is not correct.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if(WorkMode == WORK_MODE_9BITS_HW_DUAL && GUartCtrl[Instance].BitsPerChar != QAPI_UART_9_BITS_PER_CHAR_HW_E)
    {
        UART_PRINTF("ERROR: work mode is not correct.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (GUartCtrl[Instance].WorkMode != WORK_MODE_IDLE)
    {
        UART_PRINTF("ERROR: ECHO/9BITS task on UART %d need to be stopped firstly.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    UART_PRINTF("Start uart %d task...\n", Instance);
    GUartCtrl[Instance].WorkMode = WorkMode;
    UartTaskStart(Instance);

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Uart_StopWorking(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;

    if(Parameter_Count < 1)
    {
        UART_PRINTF("Missing parameters: StopWork <instance>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    if (!UartEnabled(Instance))
    {
        UART_PRINTF("ERROR: UART %d is not enabled.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    if (GUartCtrl[Instance].WorkMode == WORK_MODE_IDLE)
    {
        UART_PRINTF("ERROR: Uart %d is in idle status.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    UART_PRINTF("Stop task and disable UART %d.\n", Instance);
    GUartCtrl[Instance].WorkMode = WORK_MODE_IDLE;
    qapi_TSK_Delete_Task(GUartCtrl[Instance].UartTask);
    GUartCtrl[Instance].UartTask = NULL;
    UartDeinit(Instance);

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Uart_ConsoleSwitch(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;

    if(Parameter_Count < 1)
    {
        UART_PRINTF("Missing parameters: SwitchConsole <instance>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    if (UartEnabled(Instance))
    {
        UART_PRINTF("New console instance(%d) needs to be disabled before switch.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }
    UART_PRINTF("Switch console uart instance: %d->%d\n", ConsoleUartInstance, Instance);
    ConsoleUartInstance = Instance;

    PAL_Uart_Deinit();
    PAL_Uart_Init(Instance);

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Uart_GetInfo(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;
    uint64_t TxBytes;
    uint64_t RxBytes;
    qbool_t Enabled;
    qapi_Status_t Result;
    uint32_t BaudRate, BufferSize, TxRemainBytes, RxStaleCnt;
    qapi_UART_Parity_Mode_t ParityMode;
    qapi_UART_Num_Stop_Bits_t NumStopBits;
    qapi_UART_Bits_Per_Char_t BitsPerChar;
    qbool_t EnableLoopback;
    qbool_t EnableFlowCtrl;
    qbool_t DmaEnable;

    if(Parameter_Count < 1)
    {
        UART_PRINTF("Missing parameters: GetInfo <instance>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    Enabled = UartEnabled(Instance);

    UART_PRINTF("UART %d: %s\n", Instance, Enabled ? "Enabled" : "Disabled");
    //UART_PRINTF("CTS/RTS supported: %s\n", QAPI_UART_HS_PORT_E == uart_id ? "Yes":"No");
    if (!Enabled)
    {
        return QCLI_STATUS_SUCCESS_E;
    }

    Result = UartGetStats(Instance, &TxBytes, &RxBytes);
    if (QAPI_OK != Result)
    {
        UART_PRINTF("ERROR: Failed to get uart stats.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Result = UartGetParam(Instance, &BaudRate, &ParityMode, &NumStopBits, &BitsPerChar, &EnableLoopback,
        &EnableFlowCtrl, &DmaEnable, &BufferSize);

    if (QAPI_OK != Result)
    {
        UART_PRINTF("ERROR: Failed to get uart param.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if(Instance == QAPI_UART_INSTANCE_SE0_E)
    {
       RxStaleCnt = *((volatile uint32_t *)(0x51080294));
    }
    else if(Instance == QAPI_UART_INSTANCE_SE1_E)
    {
        RxStaleCnt = *((volatile uint32_t *)(0x51084294));
    }
    else
    {
        RxStaleCnt = *((volatile uint32_t *)(0x51088294));
    }
    
    TxRemainBytes = qapi_UART_Get_Tx_Remaining(Instance);

    UART_PRINTF("BaudRate %d, Parity %s, StopBits %s, BitsPerChar %d, Loopback %s, FlowCtrl %s, DmaEnable %s, BufferSize %d, RxStaleCnt %d, WorkMode %s\n",
            BaudRate,
            (ParityMode == QAPI_UART_NO_PARITY_E) ? "No"
                :(ParityMode == QAPI_UART_EVEN_PARITY_E) ? "Even"
                :(ParityMode == QAPI_UART_ODD_PARITY_E) ? "Odd"
                :(ParityMode == QAPI_UART_SPACE_PARITY_E) ? "Space"
                :(ParityMode == QAPI_UART_MARK_PARITY_E) ? "Mark":"Invalid",
            (NumStopBits == QAPI_UART_1_0_STOP_BITS_E) ? "1.0"
                :(NumStopBits == QAPI_UART_1_5_STOP_BITS_E) ? "1.5"
                :(NumStopBits == QAPI_UART_2_0_STOP_BITS_E) ? "2.0"
                :(NumStopBits == QAPI_UART_2_5_STOP_BITS_E) ? "2.5"
                :(NumStopBits == QAPI_UART_3_0_STOP_BITS_E) ? "3.0":"invalid",
            (BitsPerChar == QAPI_UART_5_BITS_PER_CHAR_E) ? 5
                :(BitsPerChar == QAPI_UART_6_BITS_PER_CHAR_E) ? 6
                :(BitsPerChar == QAPI_UART_7_BITS_PER_CHAR_E) ? 7
                :(BitsPerChar == QAPI_UART_8_BITS_PER_CHAR_E) ? 8
                :(BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_SW_E) ? 9
                :(BitsPerChar == QAPI_UART_9_BITS_PER_CHAR_HW_E) ? 9 :-1,
            EnableLoopback ? "on":"off",
            EnableFlowCtrl ? "on":"off",
            DmaEnable ? "DMA" : "FIFO",
            BufferSize,
            RxStaleCnt,
            (GUartCtrl[Instance].WorkMode == WORK_MODE_ECHO) ? "Echo"
                :(GUartCtrl[Instance].WorkMode == WORK_MODE_9BITS_HW_M) ? "9BITS HW MASTER"
                :(GUartCtrl[Instance].WorkMode == WORK_MODE_9BITS_HW_S) ? "9BITS HW SLAVE"
                :(GUartCtrl[Instance].WorkMode == WORK_MODE_9BITS_SW_M) ? "9BITS SW MASTER"
                :(GUartCtrl[Instance].WorkMode == WORK_MODE_9BITS_SW_S) ? "9BITS SW SLAVE"
                :(GUartCtrl[Instance].WorkMode == WORK_MODE_IDLE) ? "Idle":"invalid"
            );

    UART_PRINTF("UART tx: %llu Bytes, UART tx remaining: %u Bytes\n", TxBytes, TxRemainBytes);
    UART_PRINTF("UART rx: %llu Bytes\n", RxBytes);

    return QCLI_STATUS_SUCCESS_E;
}

static QCLI_Command_Status_t cmd_Uart_ClearStats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_UART_Instance_t Instance;
    qapi_Status_t Result;

    if(Parameter_Count < 1)
    {
        UART_PRINTF("Missing parameters: ClearStats <instance>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Instance = (qapi_UART_Instance_t)Parameter_List[0].Integer_Value;
    if (!UartEnabled(Instance))
    {
        UART_PRINTF("ERROR: UART %d is not enabled.\n", Instance);
        return QCLI_STATUS_ERROR_E;
    }

    Result = UartClearStats(Instance);
    if (QAPI_OK == Result)
    {
        UART_PRINTF("Cleared.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
    else
    {
        UART_PRINTF("Clear failed.\n");
        return QCLI_STATUS_ERROR_E;
    }
}

static void UartRxCbCommon(unsigned int Instance, uint32_t Status, unsigned int Length, void *CbCtxt)
{
    if(GUartCtrl[Instance].UartTask)
    {
        qapi_TSK_Signal_Task(GUartCtrl[Instance].UartTask, UART_TSK_EVENT_RX);
    }
}

static void UartRxCb0(uint32_t Status, uint32_t Length, void *CbCtxt)
{
    UartRxCbCommon(0, Status, Length, CbCtxt);
}

static void UartRxCb1(uint32_t Status, unsigned int Length, void *CbCtxt)
{
    UartRxCbCommon(1, Status, Length, CbCtxt);
}

static void UartRxCb2(uint32_t Status, unsigned int Length, void *CbCtxt)
{
    UartRxCbCommon(2, Status, Length, CbCtxt);
}

static void UartEnableHelp(void)
{
    int32_t I;

    UART_PRINTF("enable <Instance> <BaudRate> <Parity> <StopBits> <BitsPerChar> <Loopback> <FlowCtrl> <DmaEnable> <BufSize> <RxStaleCnt> [ReceiveAddr/TxInvert]\n");
    UART_PRINTF("\tBaudRate   : ");

    for (I = 0; I < ARRAY_SIZE(BaudRateSet); I++)
    {
        if (0 == BaudRateSet[I])
        {
            continue;
        }
        UART_PRINTF("%d ", BaudRateSet[I]);
    }

    UART_PRINTF("\n");
    UART_PRINTF("\tParity     : 0 - No Parity, 1 - Even, 2 - Odd, 3 - Space, 4 - Mark\n");
    UART_PRINTF("\tStopBits   : 0 - 1 bit, 1 - 1.5 bits, 2 - 2 bits, 3 - 2.5 bits, 4 - 3 bits\n");
    UART_PRINTF("\tBitsPerChar: 5 - 5 bits, 6 - 6 bits, 7 - 7 bits, 8 - 8 bits, 9 - 9-bit");
    UART_PRINTF(" SW mode, 10 - 9-bit HW mode\n");
    UART_PRINTF("\tLoopback   : 0 - disable, 1 - enable\n");
    UART_PRINTF("\tFlowCtrl   : 0 - disable, 1 - enable\n");
    UART_PRINTF("\tDmaEnable  : 0 - disable, FIFO, 1 - enable, DMA\n");
    UART_PRINTF("\tBufferSize : 64Bytes ~ 1024Bytes\n");
    UART_PRINTF("\tRxStaleCnt : 1 ~ 1023\n");
    UART_PRINTF("\tReceiveAddr : 0 ~ 255, only valid in 9-bit HW mode\n");
    UART_PRINTF("\tTxInvert : 0 - legacy mode 1 - Tx invert mode, only valid in 8-bit mode\n");
    UART_PRINTF("\tExample: \n");
    UART_PRINTF("\tenable 1 115200 0 0 8 0 0 1 512 10 [1]\n");

    return;
}

static qbool_t UARTCheckBaudRate(uint32_t BaudRate)
{
    int32_t i;

    for (i = 0; i < ARRAY_SIZE(BaudRateSet); i++)
    {
        if (BaudRateSet[i] == BaudRate)
        {
            return true;
        }
    }

    return false;
}

static void UartConstructDataFor9bitSwMode(char* OutBuffer, uint8_t Addr, char* Buffer, uint32_t Len)
{
    uint16_t Index = 0;
    OutBuffer[0] = Addr;
    OutBuffer[1] = 1;

    for(Index = 0; Index < Len; Index++)
    {
        OutBuffer[2 + 2*Index] = Buffer[Index];
        OutBuffer[2 + (2*Index+1)] = 0;
    }
}

static void UartWriteByteFor9bitMode(qapi_UART_Instance_t Instance, char* Buffer, uint32_t Len)
{
    int I = 0;
    uint32_t Sent = 0;
    for(I = 0; I < Len; I++)
    {
        if(I%2)
        {
            if(Buffer[I] == '\1')
            {
                qapi_UART_Transmit(Instance, (Buffer + I -1), 2, &Sent);
                qapi_UART_Transmit(Instance, UART_INPUT_9BIT_IS_1_CHARACTER, 2, &Sent);
            }
            else if(Buffer[I] == '\0')
            {
                qapi_UART_Transmit(Instance, (Buffer + I -1), 2, &Sent);
                qapi_UART_Transmit(Instance, UART_INPUT_9BIT_IS_0_CHARACTER, 2, &Sent);
            }
        }
    }
}

static uint32_t UartTasks(qapi_TSK_Handle_t Handle, uint32_t EventMask, void *Param)
{
    uint32_t Task_Instance;
    qapi_UART_Instance_t Instance;
    uint32_t Len, RemainLen = 0, Count1Time = 0;
    int32_t Result;
    UART_t *Uart;

    Task_Instance = (uint32_t)Param;
    Instance = (qapi_UART_Instance_t)Task_Instance;
    Uart = INSTANCE_2_UART(Instance);

    if (NULL == Uart)
    {
        /*assert*/
        UART_PRINTF("UART Instance %d does not exist.\n", Instance);
        goto exit1;
    }

    if(EventMask == UART_TSK_EVENT_RX || EventMask == QAPI_TSK_EVENT_TIMEOUT)
    {
        /* Receive data from UART */
        do
        {
            Len = Uart->RxBufferSize;
            Result = qapi_UART_Receive(Uart->Instance, Uart->UartBuf, &Len, &RemainLen);

            if(Result != 0)
            {
                goto exit1;
            }

            Uart->RxBytes += Len;
            Count1Time += Len;
            if(Uart->WorkMode == WORK_MODE_ECHO)
            {
                UartWrite(Uart->Instance, Len, Uart->UartBuf);
            }
            else if(Uart->WorkMode == WORK_MODE_9BITS_HW_M || Uart->WorkMode == WORK_MODE_9BITS_HW_S)
            {
                /* send out 9bits data */
                UartWrite(Uart->Instance, Len, Uart->UartBuf);
            }
            else if(Uart->WorkMode == WORK_MODE_9BITS_SW_M || Uart->WorkMode == WORK_MODE_9BITS_SW_S)
            {
                if(Len < 20)
                {
                    UartWriteByteFor9bitMode(Uart->Instance, Uart->UartBuf, Len);
                }
            }
            else if(Uart->WorkMode == WORK_MODE_9BITS_HW_DUAL)
            {
                PAL_Console_Write(Len, Uart->UartBuf);
            }
            else if(Uart->WorkMode == WORK_MODE_9BITS_SW_DUAL)
            {
                UartWriteByteFor9bitMode((qapi_UART_Instance_t)ConsoleUartInstance, Uart->UartBuf, Len);
            }

            if(Count1Time >= Uart->BufferSize)
            {
                if(RemainLen)
                    goto exit0;
                else
                    goto exit1;
            }
        }while(RemainLen);
    }
    else if(EventMask == QAPI_TSK_EVENT_INIT)
    {
        if(Uart->WorkMode != WORK_MODE_ECHO)
        {
            /* 9-bit UART could be only loopback on FPGA, have to transmit data firstly */
            Len = Uart->StrLen;
            Uart->TxBytes += Len;
            if(Uart->WorkMode == WORK_MODE_9BITS_HW_M || Uart->WorkMode == WORK_MODE_9BITS_HW_S)
            {
                /* send out 9bits data */
                qapi_UART_Set_TRAddress(Uart->Instance, QAPI_UART_TA_E, Uart->TransmitAddr);
                UartWrite(Uart->Instance, Len, Uart->UartBuf);
            }
            else if(Uart->WorkMode == WORK_MODE_9BITS_SW_M || Uart->WorkMode == WORK_MODE_9BITS_SW_S)
            {
                UartWrite(Uart->Instance, Len, Uart->UartBuf);
            }
        }
        else
        {
            do
            {
                Len = Uart->RxBufferSize;
                Result = qapi_UART_Receive(Uart->Instance, Uart->UartBuf, &Len, &RemainLen);

                if(Result != 0)
                {
                    goto exit1;
                }

                Uart->RxBytes += Len;
                if(Uart->WorkMode == WORK_MODE_ECHO)
                {
                    UartWrite(Uart->Instance, Len, Uart->UartBuf);
                }
            }while(RemainLen);
        }
    }
    else if(EventMask == QAPI_TSK_EVENT_DELETE)
    {
        UART_PRINTF("UART %d echo task quit.\n", Instance);
    }

exit0:
    return(UART_TASK_TIMEOUT);

exit1:
    return(QAPI_TSK_INFINITE_WAIT);
}

static void UartTaskStart(qapi_UART_Instance_t Instance)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return;
    }
    Uart->UartTask = qapi_TSK_Create_Task(UartTasks, (void*)Instance);
}

static qapi_Status_t UartInit(qapi_UART_Instance_t Instance, uint32_t BaudRate, qapi_UART_Parity_Mode_t ParityMode,
    qapi_UART_Num_Stop_Bits_t NumStopBits, qapi_UART_Bits_Per_Char_t BitsPerChar, qbool_t EnableLoopback, qbool_t EnableFlowCtrl,
    qbool_t DmaEnable, uint32_t BufferSize, uint32_t RxStaleCnt, qbool_t TxInvert)
{
    UART_t *Uart = NULL;
    qapi_UART_Config_t Config;
    qapi_Status_t Result;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (Uart->Enabled)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    memset(Uart, 0, sizeof(UART_t));

    Uart->Instance= Instance;

    if(DmaEnable)
    {
        Uart->RxBufferSize = BufferSize>>1;
    }
    else
    {
        Uart->RxBufferSize = BufferSize;
    }

    if((Uart->UartBuf = qapi_Malloc(Uart->RxBufferSize)) == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    memset(&Config, 0, sizeof(qapi_UART_Config_t));
    Config.Dma            = Uart->DmaEnable = DmaEnable;
    Config.BaudRate       = Uart->BaudRate = BaudRate;
    Config.ParityMode     = Uart->ParityMode = ParityMode;
    Config.NumStopBits    = Uart->NumStopBits = NumStopBits;
    Config.BitsPerChar    = Uart->BitsPerChar = BitsPerChar;
    Config.EnableLoopback = Uart->EnableLoopback = EnableLoopback;
    Config.EnableFlowCtrl = Uart->EnableFlowCtrl = EnableFlowCtrl;
    Config.RxBufSize = Config.TxBufSize = Uart->BufferSize = BufferSize;
    Config.RxStaleCnt = RxStaleCnt;
    Config.TxInvert = Uart->TxInvert = TxInvert;

    if(Instance == QAPI_UART_INSTANCE_SE0_E)
    {
        Config.RxCbFunc = UartRxCb0;
    }
    else if(Instance == QAPI_UART_INSTANCE_SE1_E)
    {
        Config.RxCbFunc = UartRxCb1;
    }
    else
    {
        Config.RxCbFunc = UartRxCb2;
    }

    Result = qapi_UART_Open(Uart->Instance, &Config);
    if (Result != QAPI_OK)
    {
        goto fail;
    }

    Uart->Enabled = true;
    Uart->WorkMode = WORK_MODE_IDLE;
    return QAPI_OK;

fail:
    return Result;
}

static qapi_Status_t UartDeinit(qapi_UART_Instance_t Instance)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (!Uart->Enabled)
    {
        return QAPI_OK;
    }

    if(Uart->UartBuf)
    {
        qapi_Free(Uart->UartBuf);
    }
    memset(Uart, 0, sizeof(UART_t));
    return(qapi_UART_Close(Instance));
}

static qbool_t UartEnabled(qapi_UART_Instance_t Instance)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return false;
    }

    return Uart->Enabled;
}

static qapi_Status_t UartWrite(qapi_UART_Instance_t Instance, uint32_t Length, const char *Buffer)
{
    uint32_t Remain = 0, Sent = 0, Offset = 0;

    if((Length != 0) && (Buffer != NULL))
    {
        Remain = Length;
        do
        {
            /* Transmit the data. */
            if(qapi_UART_Transmit(Instance, (char *)(Buffer + Offset), Remain, &Sent) == QAPI_OK)
            {
                Remain = Remain - Sent;
                Offset += Sent;
                GUartCtrl[Instance].TxBytes += Sent;
            }
            else
            {
                //uart transmit error
            }
        }while(Remain);
    }

    return QAPI_OK;
}

static qapi_Status_t UartGetStats(qapi_UART_Instance_t Instance, uint64_t *TxBytes, uint64_t *RxBytes)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (NULL == TxBytes || NULL == RxBytes)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    *TxBytes = Uart->TxBytes;
    *RxBytes = Uart->RxBytes;

    return QAPI_OK;
}

static qapi_Status_t UartClearStats(qapi_UART_Instance_t Instance)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Uart->TxBytes = 0;
    Uart->RxBytes = 0;

    return QAPI_OK;
}

static qapi_Status_t UartGetParam(qapi_UART_Instance_t Instance, uint32_t *BaudRate, qapi_UART_Parity_Mode_t *ParityMode,
    qapi_UART_Num_Stop_Bits_t *NumStopBits,qapi_UART_Bits_Per_Char_t *BitsPerChar, qbool_t *EnableLoopback, qbool_t *EnableFlowCtrl,
    qbool_t *DmaEnable, uint32_t *BufferSize)
{
    UART_t *Uart = NULL;

    Uart = INSTANCE_2_UART(Instance);
    if (NULL == Uart)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (NULL == BaudRate || NULL == ParityMode ||
        NULL == NumStopBits || NULL == BitsPerChar ||
        NULL == EnableLoopback || NULL == EnableFlowCtrl ||
        NULL == EnableFlowCtrl || NULL == DmaEnable ||
        NULL == BufferSize)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    *BaudRate = Uart->BaudRate;
    *ParityMode = Uart->ParityMode;
    *NumStopBits = Uart->NumStopBits;
    *BitsPerChar = Uart->BitsPerChar;
    *EnableLoopback= Uart->EnableLoopback;
    *EnableFlowCtrl = Uart->EnableFlowCtrl;
    *DmaEnable = Uart->DmaEnable;
    *BufferSize = Uart->BufferSize;

    return QAPI_OK;
}
