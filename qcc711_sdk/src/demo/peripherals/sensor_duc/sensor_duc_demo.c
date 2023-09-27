/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_sense.h"
#include "qapi_duc.h"
#include "qapi_gpio.h"
#include "qcli_api.h"
#include "qcli_util.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

#define SENS_DUC_DBG
#ifdef SENS_DUC_DBG
#define SENS_DUC_PRINTF(...)                       QCLI_Printf(QCLI_Sens_Duc_Handle, __VA_ARGS__)
#else
#define SENS_DUC_PRINTF(x, ...)
#endif

#define VOLT_SENSE_INTERNAL_SUPPLY                 1800   /**< Unit is mV. */

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/

/**
   Handle for sensor and duc QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_Sens_Duc_Handle;

/*-------------------------------------------------------------------------
 * Private Function Declarations
 *-----------------------------------------------------------------------*/

static QCLI_Command_Status_t cmd_Sens_Duc_GetTemp(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_GetPioVolt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_VoltSenseEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_LoadCellEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_VbatMonEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_GetVbat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Sens_Duc_GetOut(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t SENS_DUC_CMD_List[] =
{
    /* cmd_function                cmd_string    usage_string               description */
    {cmd_Sens_Duc_GetTemp,         "GetTemp",    "",                        "Get temperature"},
    {cmd_Sens_Duc_GetPioVolt,      "GetPioVolt", "<Source>",                "Get pio voltage"},
    {cmd_Sens_Duc_VoltSenseEnable, "VoltSensEn", "<Enable>",                "Volt sensor enable/disable"},
    {cmd_Sens_Duc_LoadCellEnable,  "LoadCellEn", "<Load> <Enable>",         "Load cell enable/disable"},
    {cmd_Sens_Duc_VbatMonEnable,   "VbatMonEn",  "<Enable>",                "vbat monitor enable/disable"},
    {cmd_Sens_Duc_GetVbat,         "GetVbat",    "",                        "Get vbat"},
    {cmd_Sens_Duc_Enable,          "DucEnable",  "<Threshold> <IntEnable>", "Enable Duc"},
    {cmd_Sens_Duc_Disable,         "DucDisable", "",                        "Disable Duc"},
    {cmd_Sens_Duc_GetOut,          "DucOut",     "",                        "Get Duc out value"}
};

const QCLI_Command_Group_t SENS_DUC_CMD_Group =
{
    "SENSOR_DUC",
    (sizeof(SENS_DUC_CMD_List) / sizeof(SENS_DUC_CMD_List[0])),
    SENS_DUC_CMD_List
};

static const char*Sensor_EnInfo[2] = {"disable", "enable"};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief initialize sensor and duc demo.
*/
void Initialize_Sensor_Duc_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Sens_Duc_Handle = QCLI_Register_Command_Group(NULL, &SENS_DUC_CMD_Group);
    if(QCLI_Sens_Duc_Handle)
    {
        SENS_DUC_PRINTF("Sensor and Duc Registered \n");
    }
}

/**
   @brief Get temperature test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_GetTemp(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    int32_t       Temp;

    if (Parameter_Count != 0)
    {
        SENS_DUC_PRINTF("GetTemp\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Get_Temp(&Temp);
    if (Status == QAPI_OK)
    {
        SENS_DUC_PRINTF("Temp is %d\n", Temp);
        return QCLI_STATUS_SUCCESS_E;
    }

    SENS_DUC_PRINTF("Get temp failed %d\n", Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Get pio voltage test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_GetPioVolt(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;
    qapi_Status_t         Status;
    uint32_t              Voltage;
    uint32_t              InternalResist;
    uint32_t              ExternalLoad;
    qapi_GPIO_Config_t    Config;
    uint8_t               PioId;
    qapi_SENS_PIO_Source_t Source;
    
    if (Parameter_Count != 1 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid)
    {
        SENS_DUC_PRINTF("GetPioVolt <Source>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Source = (qapi_SENS_PIO_Source_t)Parameter_List[0].Integer_Value;

    if (Source <= QAPI_SENS_PIO_SOURCE_PIO3_DIVIDE_BY2_E)
    {
        PioId = Source - QAPI_SENS_PIO_SOURCE_PIO0_DIVIDE_BY2_E;
    }
    else if (Source <= QAPI_SENS_PIO_SOURCE_PIO2_NO_DIVIDE_E)
    {
        PioId = Source - QAPI_SENS_PIO_SOURCE_PIO0_NO_DIVIDE_E;
    }
    else if (Source <= QAPI_SENS_PIO_SOURCE_PIO2_PULLUP_10K_E)
    {
        PioId = (Source - QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E) / 2;
    }
    else
    {
        PioId = 0;
    }

    /* Config the GPIO as input, pull disabled. */
    Config.PIOFunc = 0;
    Config.Dir = QAPI_GPIO_INPUT_E;
    Config.Pull = QAPI_GPIO_NO_PULL_E;
    Config.Drive = QAPI_GPIO_FAST_2MA_E;

    qapi_GPIO_Config((qapi_GPIO_Id_t)(QAPI_GPIO_ID22_E + PioId), &Config);

    Status = qapi_SENS_Voltage_Sensor_Enable(true);
    if (Status != QAPI_OK)
    {
        SENS_DUC_PRINTF("Sensor enable failed %d\n", Status);
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Pio_Switch_Enable(Source, true);
    if (Status != QAPI_OK)
    {
        SENS_DUC_PRINTF("Pio switch enable failed %d\n", Status);
        goto GET_VOLT_END2;
    }

    Status = qapi_SENS_Get_Voltage((qapi_SENS_Voltage_Source_t)(QAPI_SENS_VOLTAGE_SOURCE_PIO0_E + PioId), &Voltage);
    if (Status != QAPI_OK)
    {
        SENS_DUC_PRINTF("Get voltage failed %d\n", Status);
        goto GET_VOLT_END1;
    }

    SENS_DUC_PRINTF("Voltage is %duV\n", Voltage);

    if (Source >= QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E)
    {
        Status = qapi_SENS_Get_Pullup_Resistance((qapi_SENS_Pullup_Resistor_t)((Source - QAPI_SENS_PIO_SOURCE_PIO0_PULLUP_100K_E) % 2), &InternalResist);
        if (Status != QAPI_OK)
        {
            SENS_DUC_PRINTF("Get internal resistor failed %d\n", Status);
            goto GET_VOLT_END1;
        }

        ExternalLoad = UINT32_MAX;
        /* Convert voltage to mV. */
        Voltage /= 1000;
        if (Voltage < VOLT_SENSE_INTERNAL_SUPPLY)
        {
            ExternalLoad = Voltage * InternalResist / (VOLT_SENSE_INTERNAL_SUPPLY - Voltage);
        }

        SENS_DUC_PRINTF("Internal Resist is %dOhm, External Load is %dOhm\n", InternalResist, ExternalLoad);
    }

    CmdStatus = QCLI_STATUS_SUCCESS_E;

GET_VOLT_END1:
    qapi_SENS_Pio_Switch_Enable(Source, false);
    
GET_VOLT_END2:
    qapi_SENS_Voltage_Sensor_Enable(false);
    return CmdStatus;
}

/**
   @brief Enable or disable voltage sensor test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_VoltSenseEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    
    if (Parameter_Count != 1 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid)
    {
        SENS_DUC_PRINTF("VoltSensEn <Enable>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Voltage_Sensor_Enable(Parameter_List[0].Integer_Value);
    if (Status == QAPI_OK)
    {
        SENS_DUC_PRINTF("Sensor %s success\n", Sensor_EnInfo[(Parameter_List[0].Integer_Value ? 1 : 0)]);
        return QCLI_STATUS_SUCCESS_E;
    }

    SENS_DUC_PRINTF("Sensor %s failed %d\n", Sensor_EnInfo[(Parameter_List[0].Integer_Value ? 1 : 0)], Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Enable or disable load cell test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_LoadCellEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    uint32_t      Load;
    
    if (Parameter_Count != 2 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid || !Parameter_List[1].Integer_Is_Valid)
    {
        SENS_DUC_PRINTF("LoadCellEn <Load> <Enable>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Vbat_Load_Cell_Enable((qapi_SENS_Vbat_Load_t)Parameter_List[0].Integer_Value, Parameter_List[1].Integer_Value, &Load);
    if (Status == QAPI_OK)
    {
        SENS_DUC_PRINTF("Load cell %s success, load is %dOhm\n", Sensor_EnInfo[(Parameter_List[1].Integer_Value ? 1 : 0)], Load);
        return QCLI_STATUS_SUCCESS_E;
    }

    SENS_DUC_PRINTF("Load cell %s failed %d\n", Sensor_EnInfo[(Parameter_List[1].Integer_Value ? 1 : 0)], Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Enable or disable vbat monitor test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_VbatMonEnable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    
    if (Parameter_Count != 1 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid)
    {
        SENS_DUC_PRINTF("VbatMonEn <Enable>\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Vbat_Monitor_Enable(Parameter_List[0].Integer_Value);
    if (Status == QAPI_OK)
    {
        SENS_DUC_PRINTF("Vbat monitor %s success\n", Sensor_EnInfo[(Parameter_List[0].Integer_Value ? 1 : 0)]);
        return QCLI_STATUS_SUCCESS_E;
    }

    SENS_DUC_PRINTF("Vbat monitor %s failed %d\n", Sensor_EnInfo[(Parameter_List[0].Integer_Value ? 1 : 0)], Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief Get vbat test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_GetVbat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    uint32_t      Voltage;
    
    if (Parameter_Count != 0)
    {
        SENS_DUC_PRINTF("GetVbat\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_SENS_Get_Voltage(QAPI_SENS_VOLTAGE_SOURCE_VBAT_E, &Voltage);
    if (Status == QAPI_OK)
    {
        SENS_DUC_PRINTF("Vbat is %duv\n", Voltage);
        return QCLI_STATUS_SUCCESS_E;
    }

    SENS_DUC_PRINTF("Get vbat failed %d\n", Status);
    return QCLI_STATUS_ERROR_E;
}

/**
   @brief DUC interrupt callback function.

   @param[in] UserParam  User specified parameter for the callback function.
*/
static void Duc_IntCallback(void *UserParam)
{
    qapi_DUC_Disable();
    SENS_DUC_PRINTF("DUC IRQ\n");
}

/**
   @brief Duc enable test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t Status;
    uint8_t       Threshold;
    qapi_DUC_CB_t Callback;

    
    if (Parameter_Count != 2 || Parameter_List == NULL || !Parameter_List[0].Integer_Is_Valid || !Parameter_List[1].Integer_Is_Valid)
    {
        SENS_DUC_PRINTF("DucEnable <Threshold> <IntEnable>\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[0].Integer_Value < 0)
    {
        SENS_DUC_PRINTF("Duc threshold should not be negative value\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Parameter_List[1].Integer_Value < 0 || Parameter_List[1].Integer_Value > 1)
    {
        SENS_DUC_PRINTF("It should be 1 or 0 to enable or disable interrupt\n");
        return QCLI_STATUS_ERROR_E;
    }

    Threshold = Parameter_List[0].Integer_Value;
    
    if (Parameter_List[1].Integer_Value)
    {
        Callback = Duc_IntCallback;
    }
    else
    {
        Callback = NULL;
    }

    Status = qapi_DUC_Enable((qapi_DUC_Threshold_t)Threshold, Callback, NULL);
    if (Status != QAPI_OK)
    {
        SENS_DUC_PRINTF("Duc enable failed %d\n", Status);
        return QCLI_STATUS_ERROR_E; 
    }

    SENS_DUC_PRINTF("Duc enable successfully\n");
    return QCLI_STATUS_SUCCESS_E;
}

/**
   @brief Duc disable test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    if (Parameter_Count != 0)
    {
        SENS_DUC_PRINTF("DucDisable\n");
        return QCLI_STATUS_ERROR_E;
    }

    qapi_DUC_Disable();

    SENS_DUC_PRINTF("Duc disable successfully\n");
    return QCLI_STATUS_SUCCESS_E; 
}

/**
   @brief Duc disable test.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t cmd_Sens_Duc_GetOut(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qbool_t Out;
    
    if (Parameter_Count != 0)
    {
        SENS_DUC_PRINTF("DucOut\n");
        return QCLI_STATUS_ERROR_E;
    }

    Out = qapi_DUC_Is_Below_Threshold();
    SENS_DUC_PRINTF("DUC out value is %d", Out);

    return QCLI_STATUS_SUCCESS_E;
}


