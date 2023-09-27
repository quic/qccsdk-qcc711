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
#include "qapi_task.h"
#include "qapi_gpio.h"
#include "qapi_power.h"
#include "qapi_rot.h"
 
#include "qcli_pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "gpio_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define GPIO_DBG
#ifdef GPIO_DBG
#define GPIO_PRINTF(...)     QCLI_Printf(QCLI_Gpio_Handle, __VA_ARGS__)
#else
#define GPIO_PRINTF(x, ...)
#endif

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
static uint32_t Gpio_Interrupt_Number = 0;

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Gpio_Handle;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_Gpio_Config(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Get(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Port_Mapping(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Sleep_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Sleep_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Get_Sleep_Interrupt_Status(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Debugger_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Set_MTP_Configuration(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Gpio_Get_MTP_Configuration(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t GPIO_CMD_List[] =
{
    /* cmd_Function                        cmd_string                  usage_string                                 description */
    {cmd_Gpio_Config,                      "Config",                   "[pin] [Func] [Dir] [Pull] [Drive]",         "Config GPIO"},
    {cmd_Gpio_Set,                         "Set",                      "[pin] [value]",                             "Output GPIO value"},
    {cmd_Gpio_Get,                         "Get",                      "[pin]",                                     "Get GPIO input value"},
    {cmd_Gpio_Port_Mapping,                "Mapping",                  "[seid] [pin] [port]",                       "Mapping SE from pin to output id"},
    {cmd_Gpio_Interrupt_Enable,            "EnableInterrupt",          "[pin] [trigger]",                           "Enable GPIO interrupt"},
    {cmd_Gpio_Interrupt_Disable,           "DisableInterrupt",         "[pin]",                                     "Disable GPIO interrupt"},
    {cmd_Gpio_Sleep_Interrupt_Enable,      "EnableSleepInterrupt",     "[pin] ",                                    "Enable GPIO sleep interrupt"},
    {cmd_Gpio_Sleep_Interrupt_Disable,     "DisableSleepInterrupt",    "[pin]",                                     "Disable GPIO sleep interrupt"},
    {cmd_Gpio_Get_Sleep_Interrupt_Status,  "GetSleepInterruptStatus",  "[pin]",                                     "Get sleep interrupt Status and clear it"},
    {cmd_Gpio_Get_Interrupt_Number,        "GetInterruptNumber",       "",                                          "Get interrupt number"},
    {cmd_Gpio_Debugger_Enable,             "EnableDebugger",           "[enable]",                                  "Enable/Disbale debugger function"},
    {cmd_Gpio_Set_MTP_Configuration,       "SetMtpConfiguration",      "[pin] [Func] [Dir] [Pull] [Drive] [value]", "Set MTP Configuration"},
    {cmd_Gpio_Get_MTP_Configuration,       "GetMtpConfiguration",      "[pin]",                                     "Get MTP Configuration"}
};

const QCLI_Command_Group_t GPIO_CMD_Group =
{
    "GPIO",
    (sizeof(GPIO_CMD_List) / sizeof(GPIO_CMD_List[0])),
    GPIO_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
void Initialize_GPIO_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Gpio_Handle = QCLI_Register_Command_Group(NULL, &GPIO_CMD_Group);
    if (QCLI_Gpio_Handle)
    {
        GPIO_PRINTF("GPIO Registered \n");
    }
}

/**
   @brief Changes the SoC pin configuration.

   @param[in] pin    Physical pin number.
   @param[in] Func   Pin Function select.
   @param[in] Dir    Direction (input or output).
   @param[in] Pull   Pull value.
   @param[in] Drive  Drive strength.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Config(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_GPIO_Id_t      GPIO_ID;
    qapi_GPIO_Config_t  config;

    if (Parameter_Count != 5 || !Parameter_List) 
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;
    config.PIOFunc = Parameter_List[1].Integer_Value;
    config.Dir = (qapi_GPIO_Direction_t)Parameter_List[2].Integer_Value;
    config.Pull = (qapi_GPIO_Pull_t)Parameter_List[3].Integer_Value;
    config.Drive = (qapi_GPIO_Drive_t)Parameter_List[4].Integer_Value;

    Status = qapi_GPIO_Config(GPIO_ID, &config);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("Config error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("Config success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Sets the state of an SoC pin configured as an output GPIO.

   @param[in] pin    Physical pin number.
   @param[in] value  Output value.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Set(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_GPIO_Id_t      GPIO_ID;
    qapi_GPIO_Value_t   value;

    if (Parameter_Count != 2 || !Parameter_List) 
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;
    value = (qapi_GPIO_Value_t)Parameter_List[1].Integer_Value;

    Status = qapi_GPIO_Set(GPIO_ID, value);
    if (Status != QAPI_OK) 
    {
        GPIO_PRINTF("Set error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("Set success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Reads the state of an SoC pin configured as an input GPIO.

   @param[in] pin    Physical pin number.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Get(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_GPIO_Id_t      GPIO_ID;
    qapi_GPIO_Value_t   value;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Get(GPIO_ID, &value);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("Get error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    GPIO_PRINTF("Get success. GPIO PIN: %d, Value Get %d.\n", GPIO_ID, value);

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Reads the state of an SoC pin configured as an input GPIO.

   @param[in] seid   Serial engine number 0-3.
   @param[in] pin    Physical pin number.
   @param[in] Port   SE output number. 0:deafult; 1-5 map to port0-4

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Port_Mapping(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    uint8_t             Seid;
    qapi_GPIO_Id_t      GPIO_ID;
    SE_PORT_t		Port;

    if (Parameter_Count != 3 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    Seid = Parameter_List[0].Integer_Value;
    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[1].Integer_Value;
    Port = (SE_PORT_t)Parameter_List[2].Integer_Value;
    
    Status = qapi_GPIO_Port_Mapping(Seid, GPIO_ID, Port);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("Mapping error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    GPIO_PRINTF("Mapping success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

static void Gpio_Interrupt_Callback(qapi_GPIO_CB_Data_t data)
{
    Gpio_Interrupt_Number++;
}

/**
   @brief Enable interrupt on GPIO.

   @param[in] pin   Physical pin number.
   @param[in] trigger  Interrupt trigger type.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_GPIO_Id_t          GPIO_ID;
    qapi_GPIO_Trigger_t     Trigger;

    if (Parameter_Count != 2 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;
    Trigger = (qapi_GPIO_Trigger_t)Parameter_List[1].Integer_Value;

    Status = qapi_GPIO_Enable_Interrupt(GPIO_ID, Trigger, Gpio_Interrupt_Callback, GPIO_ID);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("EnableInterrupt error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("EnableInterrupt success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Disable interrupt on GPIO.

   @param[in] pin  Physical pin number.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_GPIO_Id_t          GPIO_ID;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Disable_Interrupt(GPIO_ID);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("DisableInterrupt error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("DisableInterrupt success.\n");
    Gpio_Interrupt_Number = 0;

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief GPIO wake up from lower power mode callback.
*/
static void GPIO_WakeUp_IntHandler(uint32_t Interrupt, void *UserParam)
{
    GPIO_PRINTF("GPIO wake up callback\n");     /* may not print successful, because CLI engine did not initial */
}

/**
   @brief Enable interrupt on GPIO in deep sleep mode.

   @param[in] pin  Physical pin number.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Sleep_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_GPIO_Id_t          GPIO_ID;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Enable_Sleep_Interrupt(GPIO_ID);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("EnableSleepInterrupt error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_PWR_Register_AON_Interrupt(QAPI_PWR_AON_INT_PIO, GPIO_WakeUp_IntHandler, NULL);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("EnableSleepInterrupt error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    
    GPIO_PRINTF("EnableSleepInterrupt success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Disable interrupt on GPIO in deep sleep mode.

   @param[in] pin  Physical pin number.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Sleep_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t           Status;
    qapi_GPIO_Id_t          GPIO_ID;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_PIO);

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Disable_Sleep_Interrupt(GPIO_ID);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("DisableSleepInterrupt error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("DisableSleepInterrupt success.\n");

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Get sleep interrupt Status and clear it.

   @param[in] pin  Physical pin number.
   
   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Get_Sleep_Interrupt_Status(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t             Status;
    qapi_GPIO_Id_t          GPIO_ID;
    qapi_GPIO_Sleep_Trigger_t Trigger_Status;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Get_Sleep_Interrupt_Status(GPIO_ID, &Trigger_Status);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("GetSleepInterruptStatus error.\n");
    }
    else
    {
        GPIO_PRINTF("GetSleepInterruptStatus success. status=%x.\n", Trigger_Status);
    }

    Status = qapi_GPIO_Clear_Sleep_Interrupt_Status(GPIO_ID);
    if (Status != QAPI_OK)
    {
        return QCLI_STATUS_ERROR_E;
    }

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Get GPIO interrupt trigger number value.

   GPIO interrupt trigger number value is clear to 0 when disable interrupt.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    GPIO_PRINTF("Gpio_Interrupt_number=%d\n", Gpio_Interrupt_Number);

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Enable/Disble debugger function.

   If enable debugger function, GPIO9-12 used as JTAG/SWD function.
   If disable debugger function, GPIO9-12 used as alternate functions.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Debugger_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t  Status;
    qbool_t        Enable;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    if ((Parameter_List[0].Integer_Value > 1) || (Parameter_List[0].Integer_Value<0))
    {
        GPIO_PRINTF("EnableDebugger error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Enable = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;

    Status = qapi_GPIO_Debugger_Enable(Enable);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("EnableDebugger error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Enable)
    {
        GPIO_PRINTF("EnableDebugger success.\n");
    }
    else
    {
        GPIO_PRINTF("DisableDebugger success.\n");
    }

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Set GPIO configuration to MTP.

   @param[in] pin    Physical pin number.
   @param[in] Func   Pin Function select.
   @param[in] Dir    Direction (input or output).
   @param[in] Pull   Pull value.
   @param[in] Drive  Drive strength.
   @param[in] value  Output value.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Set_MTP_Configuration(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_GPIO_Id_t      GPIO_ID;
    qapi_GPIO_Config_t  config;
    qapi_GPIO_Value_t   value;

    if (Parameter_Count != 6 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;
    config.PIOFunc = Parameter_List[1].Integer_Value;
    config.Dir = (qapi_GPIO_Direction_t)Parameter_List[2].Integer_Value;
    config.Pull = (qapi_GPIO_Pull_t)Parameter_List[3].Integer_Value;
    config.Drive = (qapi_GPIO_Drive_t)Parameter_List[4].Integer_Value;
    value = (qapi_GPIO_Value_t)Parameter_List[5].Integer_Value;
	qapi_ROT_Session_Start();

    Status = qapi_GPIO_Set_MTP_Config(GPIO_ID, &config, value);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("SetMtpConfiguration error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    GPIO_PRINTF("SetMtpConfiguration success.\n");
	qapi_ROT_Session_End();

    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Get GPIO configuration to MTP.

   @param[in] pin    Physical pin number.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_Gpio_Get_MTP_Configuration(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t       Status;
    qapi_GPIO_Id_t      GPIO_ID;
    qapi_GPIO_Config_t  config;
    qapi_GPIO_Value_t   value;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        return QCLI_STATUS_USAGE_E;
    }

    GPIO_ID = (qapi_GPIO_Id_t)Parameter_List[0].Integer_Value;
    Status = qapi_GPIO_Get_MTP_Config(GPIO_ID, &config, &value);
    if (Status != QAPI_OK)
    {
        GPIO_PRINTF("GetMtpConfiguration error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    
    GPIO_PRINTF("GetMtpConfiguration success.\n");
    GPIO_PRINTF("GPIO ID:%d:\n", GPIO_ID);
    GPIO_PRINTF("   Function value :%d\n", config.PIOFunc);
    GPIO_PRINTF("   Direction      :%d\n", config.Dir);
    GPIO_PRINTF("   Pull type      :%d\n", config.Pull);
    GPIO_PRINTF("   Drive          :%d\n", config.Drive);
    GPIO_PRINTF("   Value          :%d\n", value);

    return QCLI_STATUS_SUCCESS_E;
}
