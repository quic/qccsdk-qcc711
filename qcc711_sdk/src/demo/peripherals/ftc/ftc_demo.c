/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
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
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_spi.h"
#include "qapi_ftc.h"
#include "qapi_led.h"
#include "qapi_flash.h"
#include "qapi_timer.h"
 
#include "qcli_pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "ftc_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define FTC_DBG
#ifdef FTC_DBG
#define FTC_PRINTF(...)     QCLI_Printf(QCLI_Ftc_Handle, __VA_ARGS__)
#else
#define FTC_PRINTF(x, ...)
#endif

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Ftc_Handle;
qapi_FTC_Config_t   QCLI_Ftc_Config[QAPI_FTC_INSTANCE_CASCADED_E+1];
uint8_t             QCLI_Led_Spi_Instance = 0xFF;
#ifdef ENABLE_PERIPHERAL_SPI
#define             QCLI_LED_SPI_FLASH_SEQUENCE_NUM     3
typedef struct LED_SPI_FLASH_INFO_s
{
    uint32_t Offset;
    uint32_t Freq;
    uint32_t NewFreq;
    uint32_t DataLen;
    uint32_t NewDataLen;
    uint32_t FlashMapAddress;
    qapi_FLASH_Map_Handle_t FlashMapHandle;
} LED_SPI_FLASH_INFO_t;
LED_SPI_FLASH_INFO_t    QCLI_LED_SPI_FLASH_INFO[QCLI_LED_SPI_FLASH_SEQUENCE_NUM];

uint8_t             *QCLI_Led_Spi_Buf = NULL;
qapi_SPI_Transfer_t Transfer;
#endif
static uint32_t Ftc_Timer_Interrupt_Number = 0;
static uint32_t test_FTC_In_Tmr_Count = 0;
static uint32_t test_FTC_In_Tmr_Count_Max = 0;
static qapi_TMR_Comp_Instance_t *pTest_FTC_In_TMR_CompInst = NULL;
static qapi_TSK_Handle_t  test_FTC_In_Tmr_Task_Handle = NULL;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_FTC_Config_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FTC_ClockConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_FTC_InputConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FTC_PWMConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_FTC_Start(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_FTC_Stop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 

static QCLI_Command_Status_t cmd_FTC_Timer_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FTC_Timer_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Brightness_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Short_interval_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Long_interval_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Input_Source_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Clear(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
#ifdef ENABLE_PERIPHERAL_SPI
static QCLI_Command_Status_t cmd_LED_Set_Flash_Code(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Flash_Code_Transmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Flash_Code_Show(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_LED_Ram_Code_Transmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
#endif
static QCLI_Command_Status_t cmd_FTC_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FTC_In_Tmr_Init(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FTC_In_Tmr_Deinit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t FTC_CMD_List[] =
{
    /* cmd_function                  cmd_string          usage_string                            description */
    {cmd_FTC_Config_Enable,        "EnableConfig",       "[id] [enable]",                        "Enable/Disable FTC configuration"},
    {cmd_FTC_ClockConfig_Set,      "SetClockConfig",     "[id] [scale] [cycle]",                 "Set clock configuration"},
    {cmd_FTC_InputConfig_Set,      "SetInputConfig",     "[id] [input] [edge]",                  "Set input signal configuration"},
    {cmd_FTC_PWMConfig_Set,        "SetPWMConfig",       "[id] [channel] [freq] [pulse]",        "Set output PWM signal configuration"},
    {cmd_FTC_Start,                "StartFTC",           "[id]",                                 "Start FTC function"},
    {cmd_FTC_Stop,                 "StopFTC",            "[id]",                                 "Stop FTC function"},

    {cmd_FTC_Timer_Enable,         "EnableTimer",        "[id] [scale] [time] [number]",         "Enable timer"},
    {cmd_FTC_Timer_Disable,        "DisableTimer",       "[id]",                                 "Disable timer"},
    {cmd_LED_Brightness_Set,       "SetBrightness",      "[ledid] [scale] [freq] [pulse]",       "Set LED brightness"},
    {cmd_LED_Short_interval_Set,   "SetShortInterval",   "[iswhite]  [scale][freq] [pulse]",     "Set RGBW LED short interval"},
    {cmd_LED_Long_interval_Set,    "SetLongInterval",    "[iswhite] [scale] [freq] [pulse]",     "Set RGBW LED long interval"},
    {cmd_LED_Input_Source_Set,     "SetInputSource",     "[sourceid] [spimode]",                 "Choose input signal for LED3"},
    {cmd_LED_Enable,               "EnableLED",          "[ledid]",                              "Enable/Disable LED represent by bit"},
    {cmd_LED_Clear,                "ClearLED",           "",                                     "Clear LED configuration"},
#ifdef ENABLE_PERIPHERAL_SPI
    {cmd_LED_Set_Flash_Code,       "SetFlashCode",       "[id] [freq] [offset] [length] [data]", "Set ram code to flash"},
    {cmd_LED_Flash_Code_Transmit,  "TransmitFlashCode",  "[id] [times]",                         "Transmit flash code from SPI to LED"},
    {cmd_LED_Flash_Code_Show,      "ShowFlashCode",      "[id]",                                 "Show SPI LED Sequences stored in flash"},
    {cmd_LED_Ram_Code_Transmit,    "TransmitRamCode",    "[freq] [length] [data]",               "Transmit ram code from SPI to LED"},
#endif
    {cmd_FTC_Get_Interrupt_Number, "GetInterruptNumber", "",                                     "Get interrupt number"},
    {cmd_FTC_In_Tmr_Init,         "EnableFTCInInterrupt",      "[period (ms)] [repeat count]",   "Test the case that process FTC in ISR"},
    {cmd_FTC_In_Tmr_Deinit,      "DisableFTCInInterrupt",        "",                                         "release resource after the test is done"},
};

const QCLI_Command_Group_t FTC_CMD_Group =
{
    "FTC",
    (sizeof(FTC_CMD_List) / sizeof(FTC_CMD_List[0])),
    FTC_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

void Initialize_FTC_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Ftc_Handle = QCLI_Register_Command_Group(NULL, &FTC_CMD_Group);
    if (QCLI_Ftc_Handle)
    {
        FTC_PRINTF("FTC Registered \n");
    }
}

/**
   @brief Enable/Disable the configuration of FTC instance.

   @param[in] id    FTC instance ID.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Config_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_FTC_Instance_t Inst_ID;
    qbool_t             Enable;

    if (Parameter_Count != 2 || !Parameter_List) 
    {
        FTC_PRINTF("EnableConfig [id] [enable] \n");
        return QCLI_STATUS_ERROR_E;
    }

     if (((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value 
         > QAPI_FTC_INSTANCE_CASCADED_E) 
         || (Parameter_List[1].Integer_Value > 1))
    {
        FTC_PRINTF("EnableConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;
    Enable = Parameter_List[1].Integer_Value;

    if (Enable == 1)
    {
        Status = qapi_FTC_Initialize(Inst_ID, &QCLI_Ftc_Config[Inst_ID]);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("EnableConfig function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
    }
    else
    {
        Status = qapi_FTC_Uninitialize(Inst_ID);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("DisableConfig function error.\n");
            return QCLI_STATUS_ERROR_E;
        }

        memset(&QCLI_Ftc_Config[Inst_ID], 0, sizeof(qapi_FTC_Config_t));
    }

    FTC_PRINTF("EnableConfig success.\n");
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Set the configuration when count clock signal.

   @param[in] id        FTC instance ID.
   @param[in] scale     prescale value.
   @param[in] cycle     repeat times.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_ClockConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_FTC_Instance_t Inst_ID;
    int8_t              Scale;
    uint8_t             Num_cycles;

    if (Parameter_Count != 3 || !Parameter_List)
    {
        FTC_PRINTF("SetClockConfig [id] [scale] [cycle] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value 
        > QAPI_FTC_INSTANCE_CASCADED_E)
    {
        FTC_PRINTF("SetClockConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[1].Integer_Value > 15) 
     || (Parameter_List[1].Integer_Value < -1))
    {
        FTC_PRINTF("SetClockConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[2].Integer_Value > 0xFF) 
     || (Parameter_List[2].Integer_Value < 0))
    {
        FTC_PRINTF("SetClockConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;
    Scale = Parameter_List[1].Integer_Value;
    Num_cycles = Parameter_List[2].Integer_Value;

    QCLI_Ftc_Config[Inst_ID].Scale = Scale;
    QCLI_Ftc_Config[Inst_ID].NumCycles = Num_cycles;
    QCLI_Ftc_Config[Inst_ID].InputEnable = 0;
    
    FTC_PRINTF("SetClockConfig success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Set the configuration when count input signal.

   @param[in] id        FTC instance ID.
   @param[in] input     choose input port.
   @param[in] edge      count edge type.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_InputConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_FTC_Instance_t     Inst_ID;
    qapi_FTC_Input_t        Ftc_input;
    qapi_FTC_Input_Edge_t   Edge;

    if (Parameter_Count != 3 || !Parameter_List)
    {
        FTC_PRINTF("SetInputConfig [id] [input] [edge] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if (((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value 
        > QAPI_FTC_INSTANCE_CASCADED_E) 
        || ((qapi_FTC_Input_t)Parameter_List[1].Integer_Value
        > QAPI_FTC_INPUT3_E) 
        || ((qapi_FTC_Input_Edge_t)Parameter_List[2].Integer_Value
        > QAPI_FTC_INPUT_EDGE_BOTH_E))
    {
        FTC_PRINTF("SetInputConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;
    Ftc_input = (qapi_FTC_Input_t)Parameter_List[1].Integer_Value;
    Edge = (qapi_FTC_Input_Edge_t)Parameter_List[2].Integer_Value;

    QCLI_Ftc_Config[Inst_ID].InputConfig.FtcInput = Ftc_input;
	QCLI_Ftc_Config[Inst_ID].InputConfig.SmpNum = 0;
    QCLI_Ftc_Config[Inst_ID].InputConfig.Edge = Edge;
    QCLI_Ftc_Config[Inst_ID].InputEnable = 1;

    FTC_PRINTF("SetInputConfig success.\n");
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Set the configuration when output PWM signal.

   @param[in] id        FTC instance ID.
   @param[in] channel   FTC channel ID.
   @param[in] freq      Period of the PWM.
   @param[in] pulse     Pulse width of the PWM.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_PWMConfig_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_FTC_Instance_t Inst_ID;
    uint8_t Channel_ID;
    uint32_t Freq;
    uint16_t Pulse;

    if (Parameter_Count != 4 || !Parameter_List)
    {
        FTC_PRINTF("SetPWMConfig [id] [channel] [freq] [pulse] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if (((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value 
        >= QAPI_FTC_INSTANCE_CASCADED_E) 
        || (Parameter_List[1].Integer_Value > QAPI_FTC_CHANNEL_2_E))
    {
        FTC_PRINTF("SetPWMConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[2].Integer_Value < 2) 
        || (Parameter_List[3].Integer_Value 
        >= Parameter_List[2].Integer_Value) 
        || (Parameter_List[3].Integer_Value < 1))
    {
        FTC_PRINTF("SetPWMConfig paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;
    Channel_ID = Parameter_List[1].Integer_Value;
    Freq = Parameter_List[2].Integer_Value;
    Pulse = Parameter_List[3].Integer_Value;

    QCLI_Ftc_Config[Inst_ID].OutputEnable[Channel_ID] = 1;
    QCLI_Ftc_Config[Inst_ID].Period = Freq;
    QCLI_Ftc_Config[Inst_ID].Pulse[Channel_ID] = Freq - Pulse;

    FTC_PRINTF("SetPWMConfig success.\n");
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Start FTC function according ot the configuration.

   @param[in] id        FTC instance ID.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Start(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_FTC_Instance_t Inst_ID;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        FTC_PRINTF("StartFTC [id] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value
        > QAPI_FTC_INSTANCE_CASCADED_E)
    {
        FTC_PRINTF("StartFTC paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;

    Status = qapi_FTC_Enable(Inst_ID, 1);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("StartFTC function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    else
    {
        FTC_PRINTF("StartFTC success.\n");
        return QCLI_STATUS_SUCCESS_E;
    }   
}

/**
   @brief Stop FTC function.

   @param[in] id        FTC instance ID.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Stop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_FTC_Instance_t Inst_ID;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        FTC_PRINTF("StopFTC [id] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value
        > QAPI_FTC_INSTANCE_CASCADED_E)
    {
        FTC_PRINTF("StopFTC paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;

    Status = qapi_FTC_Enable(Inst_ID, 0);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("StopFTC function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    else
    {
        FTC_PRINTF("StopFTC success.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
}

/**
   @brief The General Timer callback function.

   @param[in] id    FTC instance ID.

   @return
    - None
*/
static void Ftc_Timer_Callback(qapi_FTC_Instance_t Inst_ID)
{
    Ftc_Timer_Interrupt_Number++;
}

/**
   @brief start the General Timer.

   @param[in] id        FTC instance ID.
   @param[in] time      The time value.
   @param[in] number    The number of timer, 0 is period timer.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Timer_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_FTC_Instance_t     Inst_ID;
    int8_t                  Scale;
    uint8_t                 Num_cycles;
    uint32_t                Period;
    
    if (Parameter_Count != 4 || !Parameter_List)
    {
        FTC_PRINTF("EnableTimer [id] [scale] [time] [number] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value
        > QAPI_FTC_INSTANCE_CASCADED_E)
    {
        FTC_PRINTF("EnableTimer paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[1].Integer_Value > 15) 
        || (Parameter_List[1].Integer_Value < -1))
    {
        FTC_PRINTF("EnableTimer paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[3].Integer_Value > 0xFF) 
     || (Parameter_List[3].Integer_Value < 0))
    {
        FTC_PRINTF("EnableTimer paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;
    Scale = Parameter_List[1].Integer_Value;
    Period = Parameter_List[2].Integer_Value;
    Num_cycles = Parameter_List[3].Integer_Value;

    memset(&QCLI_Ftc_Config[Inst_ID], 0, sizeof(qapi_FTC_Config_t));
    QCLI_Ftc_Config[Inst_ID].Scale = Scale;
    QCLI_Ftc_Config[Inst_ID].NumCycles = Num_cycles;
    QCLI_Ftc_Config[Inst_ID].Period = Period;

    Status = qapi_FTC_Initialize(Inst_ID, &QCLI_Ftc_Config[Inst_ID]);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("EnableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_FTC_Register_Interrupt(Inst_ID, Ftc_Timer_Callback);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("EnableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_FTC_Enable(Inst_ID, 1);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("EnableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    FTC_PRINTF("EnableTimer success.\n");
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief stop the General Timer.

   @param[in] id  FTC instance ID.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Timer_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_FTC_Instance_t             Inst_ID;
    qapi_Status_t                   Status;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        FTC_PRINTF("DisableTimer [id] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_FTC_Instance_t)Parameter_List[0].Integer_Value
        > QAPI_FTC_INSTANCE_CASCADED_E)
    {
        FTC_PRINTF("DisableTimer paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Inst_ID = (qapi_FTC_Instance_t)Parameter_List[0].Integer_Value;

    Status = qapi_FTC_Unregister_Interrupt(Inst_ID);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("DisableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_FTC_Enable(Inst_ID, 0);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("DisableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    Status = qapi_FTC_Uninitialize(Inst_ID);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("DisableTimer function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    memset(&QCLI_Ftc_Config[Inst_ID], 0, sizeof(qapi_FTC_Config_t));

    FTC_PRINTF("DisableTimer success.\n");
    Ftc_Timer_Interrupt_Number = 0;
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief set the brightness of LED.

   @param[in] ledid  LED instance ID.
   @param[in] freq   Period of the PWM in terms of count clock cycles.
   @param[in] pulse  Pulse width of the PWM in terms of count clock cycles.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Brightness_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t                   Status;
    qapi_LED_Instance_t             Led_ID;
    int8_t                          Scale;
    qapi_FTC_Channel_t              Channel_ID;
    uint16_t                        Freq;
    uint16_t                        Pulse;

    if (Parameter_Count != 4 || !Parameter_List)
    {
        FTC_PRINTF("SetBrightness [ledid] [scale] [freq] [pulse] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((qapi_LED_Instance_t)Parameter_List[0].Integer_Value
        > QAPI_LED_INSTANCE_3_E)
    {
        FTC_PRINTF("SetBrightness paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[1].Integer_Value > 15) 
        || (Parameter_List[1].Integer_Value < -1))
    {
        FTC_PRINTF("SetBrightness paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    if ((Parameter_List[2].Integer_Value < 2) 
        || (Parameter_List[3].Integer_Value 
        >= Parameter_List[2].Integer_Value) 
        || (Parameter_List[3].Integer_Value < 1))
    {
        FTC_PRINTF("SetBrightness paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Led_ID = (qapi_LED_Instance_t)Parameter_List[0].Integer_Value;
    Scale = Parameter_List[1].Integer_Value;
    Freq = Parameter_List[2].Integer_Value;
    Pulse = Parameter_List[3].Integer_Value;

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E], 0, sizeof(qapi_FTC_Config_t));
    if (Led_ID == QAPI_LED_INSTANCE_3_E)
    {
        Channel_ID = QAPI_FTC_CHANNEL_0_E;
    }
    else
    {
        Channel_ID = (qapi_FTC_Channel_t)Led_ID;
    }

    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Scale = Scale;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].OutputEnable[Channel_ID] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Period = Freq;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Pulse[Channel_ID] = Pulse;

	Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_0_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E]);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("SetBrightness function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    else
    {
        FTC_PRINTF("SetBrightness success.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
}

/**
   @brief set the short interval for LED.

   @param[in] iswhite   indicate if it is white LED.
   @param[in] freq      Period of the PWM in terms of count clock cycles.
   @param[in] pulse     Pulse width of the PWM in terms of count clock cycles.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Short_interval_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t                   Status;
    qapi_FTC_Channel_t              Channel_ID;
    qbool_t                         Iswhite;
    int8_t                          Scale;
    uint16_t                        Freq;
    uint16_t                        Pulse;

    if (Parameter_Count != 4 || !Parameter_List)
    {
        FTC_PRINTF("SetShortInterval [iswhite] [scale] [freq] [pulse] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value > 1)
    {
        FTC_PRINTF("SetShortInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[1].Integer_Value > 15) 
        || (Parameter_List[1].Integer_Value < -1))
    {
        FTC_PRINTF("SetShortInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[2].Integer_Value < 2) 
        || (Parameter_List[3].Integer_Value 
        >= Parameter_List[2].Integer_Value) 
        || (Parameter_List[3].Integer_Value < 1))
    {
        FTC_PRINTF("SetShortInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Iswhite = Parameter_List[0].Integer_Value;
    Scale = Parameter_List[1].Integer_Value;
    Freq = Parameter_List[2].Integer_Value;
    Pulse = Parameter_List[3].Integer_Value;

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E], 0, sizeof(qapi_FTC_Config_t));
    if (Iswhite == 1)
    {
        Channel_ID = QAPI_FTC_CHANNEL_1_E;
    }
    else
    {
        Channel_ID = QAPI_FTC_CHANNEL_0_E;
    }

    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Scale = Scale;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].OutputEnable[Channel_ID] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Period = Freq;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Pulse[Channel_ID] = Pulse;

	Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_1_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E]);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("SetShortInterval function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    else
    {
        FTC_PRINTF("SetShortInterval success.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
}

/**
   @brief set the long interval for LED.

   @param[in] iswhite   indicate if it is white LED.
   @param[in] freq      Period of the PWM in terms of count clock cycles.
   @param[in] pulse     Pulse width of the PWM in terms of count clock cycles.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Long_interval_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t                   Status;
    qapi_FTC_Channel_t              Channel_ID;
    qbool_t                         Iswhite;
    int8_t                          Scale;
    uint16_t                        Freq;
    uint16_t                        Pulse;

    if (Parameter_Count != 4 || !Parameter_List )
    {
        FTC_PRINTF("SetLongInterval [iswhite] [scale] [freq] [pulse] \n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value > 1)
    {
        FTC_PRINTF("SetLongInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[1].Integer_Value > 15) 
        || (Parameter_List[1].Integer_Value < -1))
    {
        FTC_PRINTF("SetLongInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    if ((Parameter_List[2].Integer_Value < 2) 
        || (Parameter_List[3].Integer_Value 
        >= Parameter_List[2].Integer_Value) 
        || (Parameter_List[3].Integer_Value < 1))
    {
        FTC_PRINTF("SetLongInterval paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Iswhite = Parameter_List[0].Integer_Value;
    Scale = Parameter_List[1].Integer_Value;
    Freq = Parameter_List[2].Integer_Value;
    Pulse = Parameter_List[3].Integer_Value;

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E], 0, sizeof(qapi_FTC_Config_t));
    if (Iswhite == 1)
    {
      Channel_ID = QAPI_FTC_CHANNEL_1_E;
    }
    else
    {
      Channel_ID = QAPI_FTC_CHANNEL_0_E;
    }

    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Scale = Scale;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].OutputEnable[Channel_ID] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Period = Freq;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Pulse[Channel_ID] = Pulse;

	Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_2_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E]);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("SetLongInterval function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    else
    {
        FTC_PRINTF("SetLongInterval success.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
}

/**
   @brief choose the input signal for white LED.

   @param[in] sourceid  0:FTC input, 1:SE0 SPI MOSI, 2:SE1 SPI MOSI
   @param[in] spimode   0:FIFO-RAM, 1:DMA-RAM 2:DMA-FLASH

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Input_Source_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_LED_Source_t       Source;
#ifdef ENABLE_PERIPHERAL_SPI
    uint8_t                 SpiMode;
    qapi_SPI_Instance_t     Instance;
    qapi_SPI_Config_t       Config;
    char *SpiModeString[3] = {"FIFO-RAM", "DMA-RAM", "DMA-FLASH"};
#endif
    
    if (Parameter_Count != 2 || !Parameter_List)
    {
        FTC_PRINTF("SetInputSource [sourceid] [spimode]\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (((qapi_LED_Source_t)Parameter_List[0].Integer_Value 
        > QAPI_LED_SOURCE_SE1_E) 
        || (Parameter_List[1].Integer_Value > 2)) /* SPI only support SE0 SE1 */
    {
        FTC_PRINTF("SetInputSource paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Source = (qapi_LED_Source_t)Parameter_List[0].Integer_Value;
#ifdef ENABLE_PERIPHERAL_SPI
    SpiMode = Parameter_List[1].Integer_Value;
#endif

    Status = qapi_LED3_CodedData_Source_Select(Source);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("SetInputSource function error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
#ifdef ENABLE_PERIPHERAL_SPI
    if (QCLI_Led_Spi_Instance != 0xFF)
    {
        qapi_SPI_Close((qapi_SPI_Instance_t)QCLI_Led_Spi_Instance);
    }
#endif
    
    if (Source == QAPI_LED_SOURCE_FTC_E)
    {
        QCLI_Led_Spi_Instance = 0xFF;
        
        Status = qapi_FTC_LED_Enable(1);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("SetInputSource function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
        
        FTC_PRINTF("SetInputSource FTC success.\n");
    }
    else
    {
        
        Status = qapi_FTC_Enable(QAPI_FTC_INSTANCE_0_E, 1);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("SetInputSource function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
        
#ifdef ENABLE_PERIPHERAL_SPI
        Instance = (qapi_SPI_Instance_t)(Source - 1);
        memset(&Config, 0, sizeof(Config));
        Config.Mode = QAPI_SPI_MODE_MASTER_E;
        Config.Blocking = 0;
        Config.NoMuxPriority = 1;
        Config.Dma = SpiMode;
         Status = qapi_SPI_Open(Instance, &Config);
        QCLI_Led_Spi_Instance = Source - 1;


        FTC_PRINTF("SetInputSource SPI SE%d mode %s %s.\n", Source-1, SpiModeString[SpiMode], ((Status == QAPI_OK) ? "success" : "failed"));
#endif
    }
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief start output LED signal.

   @param[in] id        LED intance, represent by bit[3:0].
   @param[in] enable    Enable/Disable LED.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    uint32_t                Flag;
    int                     i;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        FTC_PRINTF("EnableLED [ledid]\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value > 0xF)
    {
        FTC_PRINTF("EnableLED paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Flag = Parameter_List[0].Integer_Value;

    for (i=0; i<=QAPI_LED_INSTANCE_3_E; i++)
    {
        if (Flag & (0x01 << i))
        {
            Status = qapi_LED_Enable((qapi_LED_Instance_t)i, 1);
            if (Status != QAPI_OK)
            {
                FTC_PRINTF("EnableLED function error.\n");
                return QCLI_STATUS_ERROR_E;
            }
            FTC_PRINTF("Enable LED%d success.\n", i);
        }
        else
        {
            Status = qapi_LED_Enable((qapi_LED_Instance_t)i, 0);
            if (Status != QAPI_OK)
            {
                FTC_PRINTF("DisableLED function error.\n");
                return QCLI_STATUS_ERROR_E;
            }
            FTC_PRINTF("Disable LED%d success.\n", i);
        }
    }
    
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Clear LED configuration.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Clear(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    int                     i;
    
    if (Parameter_Count != 0)
    {
        FTC_PRINTF("ClearLED\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    if (QCLI_Led_Spi_Instance == 0xFF)
    {
        Status = qapi_FTC_LED_Enable(0);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("ClearLED function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
        
        memset(&QCLI_Ftc_Config[0], 0, sizeof(qapi_FTC_Config_t) * 3);
    }
    else
    {
        Status = qapi_FTC_Enable(QAPI_FTC_INSTANCE_0_E, 0);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("ClearLED function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
    #ifdef ENABLE_PERIPHERAL_SPI
        qapi_SPI_Close((qapi_SPI_Instance_t)QCLI_Led_Spi_Instance);
        QCLI_Led_Spi_Instance = 0xFF;
    #endif
    }
    
    for (i=0; i<=QAPI_LED_INSTANCE_3_E; i++)
    {
        Status = qapi_LED_Enable((qapi_LED_Instance_t)i, 0);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("ClearLED function error.\n");
            return QCLI_STATUS_ERROR_E;
        }
    }
    
    Status = qapi_LED3_CodedData_Source_Select(QAPI_LED_SOURCE_FTC_E);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("ClearLED error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    FTC_PRINTF("ClearLED success.\n");
    
    return QCLI_STATUS_SUCCESS_E;
}

#ifdef ENABLE_PERIPHERAL_SPI
static QCLI_Command_Status_t cmd_LED_Set_Flash_Code(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t   Status;
    uint8_t         Id;
    uint32_t        Freq;
    uint32_t        Offset;
    uint32_t        DataLen;
    uint8_t         Data;
    uint8_t         *QCLI_Led_Spi_Buf_New;
    uint32_t        NewDataLen;
    uint32_t        Scale;
    uint32_t        EraseStart;
    uint32_t        EraseCnt;

    if (Parameter_Count != 5 || !Parameter_List)
    {
        FTC_PRINTF("SetFlashCode [id] [freq] [offset] [length] [data]\n");
        return QCLI_STATUS_ERROR_E;
    }

    Id = Parameter_List[0].Integer_Value;
    Freq = Parameter_List[1].Integer_Value;
    Offset = Parameter_List[2].Integer_Value;
    DataLen = Parameter_List[3].Integer_Value;
    Data = Parameter_List[4].Integer_Value;

    if (Id >= QCLI_LED_SPI_FLASH_SEQUENCE_NUM)
    {
        FTC_PRINTF("Error, only support %d SPI LED sequences in FLASH\n", QCLI_LED_SPI_FLASH_SEQUENCE_NUM);
        return QCLI_STATUS_ERROR_E;
    }

    if (Freq == 0) //clear flash 
    {
        if (QCLI_LED_SPI_FLASH_INFO[Id].Freq == 0)
        {
            FTC_PRINTF("Id %d already be cleared.\n", Id);
            return QCLI_STATUS_SUCCESS_E;
        }
        else
        {
            qapi_FLASH_Memory_Unmap(QCLI_LED_SPI_FLASH_INFO[Id].FlashMapHandle);
            QCLI_LED_SPI_FLASH_INFO[Id].FlashMapHandle = NULL;
            memset(&QCLI_LED_SPI_FLASH_INFO[Id], 0, sizeof(QCLI_LED_SPI_FLASH_INFO[Id]));
            FTC_PRINTF("Id %d has be cleared successful.\n", Id);
            return QCLI_STATUS_SUCCESS_E;
        }
    }
    else
    {
        if (QCLI_LED_SPI_FLASH_INFO[Id].Freq != 0)
        {
            FTC_PRINTF("Index %d already exist a sequence, please delete it first.\n", Id);
            return QCLI_STATUS_SUCCESS_E;
        }
    }

    QCLI_Led_Spi_Buf = qapi_Malloc(DataLen);
    if (!QCLI_Led_Spi_Buf)
    {
        FTC_PRINTF("Error, no enough memory for SPI buffer\n");
        return QCLI_STATUS_ERROR_E;
    }
    memset(QCLI_Led_Spi_Buf, Data, DataLen);

    Scale = (Freq == 1 ? 64 : (Freq < 4 ? 32 : (Freq < 65 ? 16 : 1)));
    if (Scale != 1)
    {
        int i, j, k, Step;
        uint8_t *OrigData;
        uint16_t *NewData;

        NewDataLen = DataLen * Scale;
        QCLI_Led_Spi_Buf_New = qapi_Malloc(NewDataLen);
        if (!QCLI_Led_Spi_Buf_New)
        {
            FTC_PRINTF("Error, no enough memory for SPI buffer\n");
            qapi_Free(QCLI_Led_Spi_Buf);
            return QCLI_STATUS_ERROR_E;
        }
        memset(QCLI_Led_Spi_Buf_New, 0, NewDataLen);
        OrigData = (uint8_t *)QCLI_Led_Spi_Buf;
        NewData = (uint16_t *)QCLI_Led_Spi_Buf_New;
        
        Step = (Scale == 64 ? 4 : (Scale == 32 ? 2 : 1));
        for (i = 0, k = 0; i <DataLen; i++)
        {
            uint8_t Tmp = OrigData[i];
            
            for (j = 0; j < 8; j++)
            {
                if (Tmp & 0x80)
                {
                    switch (Step)
                    {
                        case 4:
                            NewData[k + 3] = ~0;
                            NewData[k + 2] = ~0;
                        case 2:
                            NewData[k + 1] = ~0;
                        case 1:
                            NewData[k + 0] = ~0;
                            break;
                    }
                }
                
                k += Step;
                Tmp <<= 1;
            }
        }
        
        qapi_Free(QCLI_Led_Spi_Buf);
    }
    else
    {
        NewDataLen = DataLen;
        QCLI_Led_Spi_Buf_New = QCLI_Led_Spi_Buf;
    }

    Status = qapi_FLASH_Init(NULL);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("Error, Flash uninitialized, please set Flash first in Flash menu\n");
        goto CMD_LED_SET_FLASH_CODE_ERROR;
    }

    EraseStart = Offset / 4096;
    EraseCnt = (Offset + NewDataLen) / 4096 - EraseStart + 1;
    Status = qapi_FLASH_Erase(QAPI_FLASH_BLOCK_ERASE_E, EraseStart, EraseCnt, NULL, NULL);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("Flash erase failed, error: %d\n", Status);
        goto CMD_LED_SET_FLASH_CODE_ERROR;
    }

    Status = qapi_FLASH_Write(Offset, NewDataLen, (uint8_t *)QCLI_Led_Spi_Buf_New, NULL, NULL);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("Flash write failed, error: %d\n", Status);
        goto CMD_LED_SET_FLASH_CODE_ERROR;
    }

    Status = qapi_FLASH_Memory_Map(Offset, NewDataLen, &QCLI_LED_SPI_FLASH_INFO[Id].FlashMapHandle);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("Flash memory mapping failed, error: %d\n", Status);
        goto CMD_LED_SET_FLASH_CODE_ERROR;
    }

    Status = qapi_FLASH_Get_Mapped_Address(Offset, &QCLI_LED_SPI_FLASH_INFO[Id].FlashMapAddress);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("Flash get mapping address failed, error: %d\n", Status);
        qapi_FLASH_Memory_Unmap(QCLI_LED_SPI_FLASH_INFO[Id].FlashMapHandle);
        QCLI_LED_SPI_FLASH_INFO[Id].FlashMapHandle = NULL;
        goto CMD_LED_SET_FLASH_CODE_ERROR;
    }

    QCLI_LED_SPI_FLASH_INFO[Id].Freq = Freq;
    QCLI_LED_SPI_FLASH_INFO[Id].NewFreq = Freq * Scale;
    QCLI_LED_SPI_FLASH_INFO[Id].Offset = Offset;
    QCLI_LED_SPI_FLASH_INFO[Id].DataLen = DataLen;
    QCLI_LED_SPI_FLASH_INFO[Id].NewDataLen = NewDataLen;
    qapi_Free(QCLI_Led_Spi_Buf_New);

    FTC_PRINTF("SetFlashCode %d success.\n", Id);

    return QCLI_STATUS_SUCCESS_E;

CMD_LED_SET_FLASH_CODE_ERROR:
    qapi_Free(QCLI_Led_Spi_Buf_New);
    return QCLI_STATUS_ERROR_E;
}

static void Led_Spi_Flash_Interrupt_Callback(uint32_t Status, void *CallbackCtxt)
{
    FTC_PRINTF("LED SPI Flash transfer callback, Status=%x\n", Status);
}

/**
   @brief Transmit Flash data from SPI to White LED.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Flash_Code_Transmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t   Status;
    uint32_t        Id;
    uint32_t        Times; 
    uint32_t        i;

    if (Parameter_Count != 2 || !Parameter_List)
    {
        FTC_PRINTF("TransmitFlashCode [id] [times]\n");
        return QCLI_STATUS_ERROR_E;
    }

    Id = Parameter_List[0].Integer_Value;
    Times = Parameter_List[1].Integer_Value;
    if (Id >= QCLI_LED_SPI_FLASH_SEQUENCE_NUM)
    {
        FTC_PRINTF("Error, only support %d SPI LED sequences in FLASH\n", QCLI_LED_SPI_FLASH_SEQUENCE_NUM);
        return QCLI_STATUS_ERROR_E;
    }
    if (QCLI_LED_SPI_FLASH_INFO[Id].Freq == 0)
    {
        FTC_PRINTF("Error, It does not include %d SPI LED sequences in FLASH\n", Id);
        return QCLI_STATUS_ERROR_E;
    }

    for (i=0; i<Times; i++)
    {
        Transfer.TxLen = QCLI_LED_SPI_FLASH_INFO[Id].NewDataLen;
        Transfer.TxBuf = (void *)QCLI_LED_SPI_FLASH_INFO[Id].FlashMapAddress;
        Transfer.XferInfo.Master.BitsPerWord = 8;
        Transfer.XferInfo.Master.FreqHz = QCLI_LED_SPI_FLASH_INFO[Id].NewFreq;
        Transfer.XferInfo.Master.Flags &= ~QAPI_SPI_XFER_LOW_RATE;
        Transfer.CallbackFn = Led_Spi_Flash_Interrupt_Callback;
        Transfer.CallbackCtxt = NULL;
        Status = qapi_SPI_Transfer((qapi_SPI_Instance_t)QCLI_Led_Spi_Instance, &Transfer);
        if (Status != QAPI_OK)
        {
            FTC_PRINTF("TransmitFlashCode error.\n");
            return QCLI_STATUS_ERROR_E;
        }
    }

    FTC_PRINTF("TransmitFlashCode success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Show SPI LED Sequences stored in flash.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Flash_Code_Show(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    uint32_t        Id;
    
    if (Parameter_Count != 1 || !Parameter_List)
    {
        FTC_PRINTF("ShowFlashCOde [id]\n");
        return QCLI_STATUS_ERROR_E;
    }

    Id = Parameter_List[0].Integer_Value;
    if (Id >= QCLI_LED_SPI_FLASH_SEQUENCE_NUM)
    {
        FTC_PRINTF("Error, only support %d SPI LED sequences in FLASH\n", QCLI_LED_SPI_FLASH_SEQUENCE_NUM);
        return QCLI_STATUS_ERROR_E;
    }

    FTC_PRINTF("Flash Code Info:\n");
    FTC_PRINTF("Id      :%d\n", Id);
    FTC_PRINTF("Offset  :0x%x\n", QCLI_LED_SPI_FLASH_INFO[Id].Offset);
    FTC_PRINTF("Freq    :%d\n", QCLI_LED_SPI_FLASH_INFO[Id].Freq);
    FTC_PRINTF("DataLen :%d\n", QCLI_LED_SPI_FLASH_INFO[Id].DataLen);
    FTC_PRINTF("FlashMapAddress:0x%x\n", QCLI_LED_SPI_FLASH_INFO[Id].FlashMapAddress);

    return QCLI_STATUS_SUCCESS_E;
}

static void Led_Spi_Ram_Interrupt_Callback(uint32_t Status, void *CallbackCtxt)
{
    FTC_PRINTF("LED SPI Ram transfer callback, Status=%x\n", Status);
    qapi_Free(QCLI_Led_Spi_Buf);
}

/**
   @brief Transmit Ram data from SPI to White LED.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_LED_Ram_Code_Transmit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t   Status;
    uint32_t        Freq;
    uint32_t        DataLen;
    uint8_t         Data;

    if (Parameter_Count != 3 || !Parameter_List)
    {
        FTC_PRINTF("TransmitRamCode [freq] [datalen] [data]\n");
        return QCLI_STATUS_ERROR_E;
    }

    Freq = Parameter_List[0].Integer_Value;
    DataLen = Parameter_List[1].Integer_Value;
    Data = Parameter_List[2].Integer_Value;

    if (QCLI_Led_Spi_Instance == 0xFF)
    {
        FTC_PRINTF("Not suppport transmit code when input source is FTC\n");
        return QCLI_STATUS_ERROR_E;
    }

    QCLI_Led_Spi_Buf = qapi_Malloc(DataLen);
    if (!QCLI_Led_Spi_Buf)
    {
        FTC_PRINTF("Error, no enough memory for SPI buffer\n");
        return QCLI_STATUS_ERROR_E;
    }
    memset(QCLI_Led_Spi_Buf, Data, DataLen);
    Transfer.TxLen = DataLen;
    Transfer.TxBuf = QCLI_Led_Spi_Buf;
    Transfer.XferInfo.Master.BitsPerWord = 8;
    Transfer.XferInfo.Master.FreqHz = Freq;
    Transfer.XferInfo.Master.Flags |= QAPI_SPI_XFER_LOW_RATE;
    Transfer.CallbackFn = (qapi_SPI_CB_t)Led_Spi_Ram_Interrupt_Callback;
    Transfer.CallbackCtxt = NULL;
    Status = qapi_SPI_Transfer((qapi_SPI_Instance_t)QCLI_Led_Spi_Instance, &Transfer);
    if (Status != QAPI_OK)
    {
        FTC_PRINTF("TransmitRamCode error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    FTC_PRINTF("TransmitRamCode success.\n");

    return QCLI_STATUS_SUCCESS_E;
}
#endif

/**
   @brief Get FTC interrupt trigger number value.

   FTC interrupt trigger number value is clear to 0 when disable interrupt.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    FTC_PRINTF("Ftc_Timer_Interrupt_Number=%d\n", Ftc_Timer_Interrupt_Number);

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Disable FTC LED function.

   @return
    - qapi_Status_t.
*/
qapi_Status_t test_FTC_Disable(void)
{
    qapi_Status_t      Status;
    int                     i;
        
    if (QCLI_Led_Spi_Instance == 0xFF)
    {
        Status = qapi_FTC_LED_Enable(0);
        if (Status != QAPI_OK)
        {
            return Status;
        }
        
        memset(&QCLI_Ftc_Config[0], 0, sizeof(qapi_FTC_Config_t) * 3);
    }
    else
    {
        Status = qapi_FTC_Enable(QAPI_FTC_INSTANCE_0_E, 0);
        if (Status != QAPI_OK)
        {
            return Status;
        }
    }
    
    for (i=0; i<=QAPI_LED_INSTANCE_3_E; i++)
    {
        Status = qapi_LED_Enable((qapi_LED_Instance_t)i, 0);
        if (Status != QAPI_OK)
        {
            return Status;
        }
    }
    
    Status = qapi_LED3_CodedData_Source_Select(QAPI_LED_SOURCE_FTC_E);        
    return Status;
}

/**
   @brief One case that will be called in timer isr, only for test purpose.

   @return
    - QAPI_OK, ...
*/
qapi_Status_t test_FTC_Case_Sel(int Case_Sel)
{
    qapi_Status_t Status;

    test_FTC_Disable();

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E], 0, sizeof(qapi_FTC_Config_t));
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Scale = 7;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].OutputEnable[QAPI_FTC_CHANNEL_0_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].OutputEnable[QAPI_FTC_CHANNEL_1_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].OutputEnable[QAPI_FTC_CHANNEL_2_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Period = 125;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Pulse[QAPI_FTC_CHANNEL_0_E] = 5;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Pulse[QAPI_FTC_CHANNEL_1_E] = 5;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E].Pulse[QAPI_FTC_CHANNEL_2_E] = 5;

    Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_0_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_0_E]);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E], 0, sizeof(qapi_FTC_Config_t));
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Scale = 13;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].OutputEnable[QAPI_FTC_CHANNEL_0_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].OutputEnable[QAPI_FTC_CHANNEL_1_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Period = 586;
    if(!Case_Sel)
    {
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Pulse[QAPI_FTC_CHANNEL_0_E] = 195;
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Pulse[QAPI_FTC_CHANNEL_1_E] = 390;
    }
    else
    {
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Pulse[QAPI_FTC_CHANNEL_0_E] = 390;
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E].Pulse[QAPI_FTC_CHANNEL_1_E] = 195;
    }
    Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_1_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_1_E]);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    memset(&QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E], 0, sizeof(qapi_FTC_Config_t));
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Scale = 15;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].InputEnable = 0;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].OutputEnable[QAPI_FTC_CHANNEL_0_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].OutputEnable[QAPI_FTC_CHANNEL_1_E] = 1;
    QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Period = 1465;
    if(!Case_Sel)
    {
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Pulse[QAPI_FTC_CHANNEL_0_E] = 488;
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Pulse[QAPI_FTC_CHANNEL_1_E] = 976;
    }
    else
    {
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Pulse[QAPI_FTC_CHANNEL_0_E] = 976;
        QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E].Pulse[QAPI_FTC_CHANNEL_1_E] = 488;
    }
	
    Status = qapi_FTC_Initialize(QAPI_FTC_INSTANCE_2_E, &QCLI_Ftc_Config[QAPI_FTC_INSTANCE_2_E]);
    if (Status != QAPI_OK)
    {
        return Status;
    }


    Status = qapi_LED3_CodedData_Source_Select(QAPI_LED_SOURCE_FTC_E);
    if (Status != QAPI_OK)
    {
        return Status;
    }

    QCLI_Led_Spi_Instance = 0xFF;
        
    Status = qapi_FTC_LED_Enable(1);
    if (Status != QAPI_OK)
    {
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_LED_Enable(QAPI_LED_INSTANCE_0_E, 1);
    Status += qapi_LED_Enable(QAPI_LED_INSTANCE_1_E, 1);
    Status += qapi_LED_Enable(QAPI_LED_INSTANCE_2_E, 1);
    Status += qapi_LED_Enable(QAPI_LED_INSTANCE_3_E, 1);

    return Status;
}

/**
   @brief Compartor callback function.

   @param[in] UserParam  User specified parameter provided when the callback
                         is registered.
*/
static void test_FTC_In_Tmr_CompCallback(void *UserParam)
{
    if(!test_FTC_In_Tmr_Count_Max)
        return;

    test_FTC_Case_Sel(test_FTC_In_Tmr_Count&1);
    test_FTC_In_Tmr_Count++;
    if(test_FTC_In_Tmr_Count >= test_FTC_In_Tmr_Count_Max)
    {
        test_FTC_Disable();
        test_FTC_In_Tmr_Count_Max = 0;
        test_FTC_In_Tmr_Count = 0;
        qapi_TSK_Signal_Task(test_FTC_In_Tmr_Task_Handle, 1);
    }
}

/**
   @brief Stop FTC timer.

   @return qapi_Status_t
*/
static qapi_Status_t test_FTC_In_Tmr_Stop(void)
{
    qapi_Status_t Status;

    /* if timer is not initialized or the ftc is still running. */
    if(!pTest_FTC_In_TMR_CompInst)
    {
        return QAPI_ERROR;
    }

    Status = qapi_TMR_Comp_Stop(*pTest_FTC_In_TMR_CompInst);
    if (Status == QAPI_OK)
    {
        FTC_PRINTF("Comparator %d stopped successfully\n", *pTest_FTC_In_TMR_CompInst);
    }
    Status = qapi_TMR_Comp_Deinit(*pTest_FTC_In_TMR_CompInst);
    if (Status == QAPI_OK)
    {
        FTC_PRINTF("Comparator %d deinit successfully\n", *pTest_FTC_In_TMR_CompInst);
    }

    qapi_Free(pTest_FTC_In_TMR_CompInst);
    pTest_FTC_In_TMR_CompInst = NULL;
    return Status;
}

/**
   @brief The task process the event from timer interrupt to disable the FTC function.

   @param[in] TaskHandle  Handle of the task.
   @param[in] EventMask   Mask of all events that triggered since last
                          call to this function.
   @param[in] UserParam   User specified parameter for the task function.

   @return The time in milliseconds before this function needs to be called again.
*/
static uint32_t test_FTC_In_Tmr_Task(qapi_TSK_Handle_t Handle, uint32_t EventMask, void *Param)
{
    uint64_t CurTime;
    qapi_TMR_Comp_Instance_t i;

    if(pTest_FTC_In_TMR_CompInst)
    {
        i = *pTest_FTC_In_TMR_CompInst;
        if (EventMask & 1)
        {
            CurTime = qapi_TMR_Get_Current_Time();
            test_FTC_In_Tmr_Stop();
            FTC_PRINTF("Comparator %d time out at %lluus\n", i, CurTime);
        }
    }

    return QAPI_TSK_INFINITE_WAIT;
}

/**
   @brief a demo that process the FTC in interrupt, 
             we start a repeated timer to simulate some certain interrupt which will call the FTC relate QAPIs.
             it's a stand alone test case, 
             do not combine with the cmd_FTC_xxx  or cmd_LED_xxx. 
             eg: startFTCInInterrupt 3000 8

   @param[in] period        FTC instance ID.
   @param[in] repeat count        FTC instance ID.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_In_Tmr_Init(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_TMR_Comp_Instance_t  Comp;
    qapi_Status_t             Status;
    uint64_t Timeout;
    uint64_t CurTime;

    if (Parameter_Count != 2)
    {
        FTC_PRINTF("param: [period (ms)] [repeat count]\n");
        return QCLI_STATUS_ERROR_E;
    }

    if ((Parameter_Count == 2) 
        && (Parameter_List[0].Integer_Is_Valid && (Parameter_List[0].Integer_Value > 0))
        &&  (Parameter_List[1].Integer_Is_Valid))
    {
        Timeout = 1000 * Parameter_List[0].Integer_Value;
    }
    else
    {
        return QCLI_STATUS_ERROR_E;
    }

    /* if timer is not initialized or the ftc is still running. */
    if(test_FTC_In_Tmr_Count_Max)
    {
        FTC_PRINTF("Comparator %d is running. Please wait...\n", *pTest_FTC_In_TMR_CompInst);
        return QCLI_STATUS_ERROR_E;
    }

    if(pTest_FTC_In_TMR_CompInst)
    {
        test_FTC_In_Tmr_Stop();
    }
    pTest_FTC_In_TMR_CompInst = qapi_Malloc(sizeof(qapi_TMR_Comp_Instance_t));
    if (pTest_FTC_In_TMR_CompInst == NULL)
    {
        FTC_PRINTF("ERROR: No enough memory\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_TMR_Comp_Init(&Comp, test_FTC_In_Tmr_CompCallback, pTest_FTC_In_TMR_CompInst, false);
    if (Status == QAPI_OK)
    {
        *pTest_FTC_In_TMR_CompInst = Comp;
        FTC_PRINTF("Comparator %d (%s) Init successfully\n", Comp, "non-deferrable");

        if(!test_FTC_In_Tmr_Task_Handle)
            test_FTC_In_Tmr_Task_Handle = qapi_TSK_Create_Task(test_FTC_In_Tmr_Task, NULL);

        test_FTC_In_Tmr_Count_Max = Parameter_List[1].Integer_Value;
        Status = qapi_TMR_Comp_Start(Comp, Timeout, 1);
        CurTime = qapi_TMR_Get_Current_Time();
        FTC_PRINTF("Comparator %d started successfully at %lluus\n", Comp, CurTime);

        return QCLI_STATUS_SUCCESS_E;
    }
    qapi_Free(pTest_FTC_In_TMR_CompInst);
    pTest_FTC_In_TMR_CompInst = NULL;
    FTC_PRINTF("Comp init failed %d\n", Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Delete the task after the FTC timer is stopped.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_FTC_In_Tmr_Deinit(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    if(test_FTC_In_Tmr_Count_Max)
    {
        FTC_PRINTF("FTC is still running...\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (test_FTC_In_Tmr_Task_Handle)
    {
        qapi_TSK_Delete_Task(test_FTC_In_Tmr_Task_Handle);
        test_FTC_In_Tmr_Task_Handle = NULL;
        FTC_PRINTF("Deinit successfully.\n");
        return QCLI_STATUS_SUCCESS_E;
    }
    else
        return QCLI_STATUS_ERROR_E;
}

