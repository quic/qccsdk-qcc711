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
#include "qapi_power.h"
 
#include "qcli_pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "mfp_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define MFP_DBG
#ifdef MFP_DBG
#define MFP_PRINTF(...)     QCLI_Printf(QCLI_Mfp_Handle, __VA_ARGS__)
#else
#define MFP_PRINTF(x, ...)
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
QCLI_Group_Handle_t QCLI_Mfp_Handle;

static uint32_t MFP_Short_Press_Interrupt_Number = 0;
static uint32_t MFP_Edge_Detect_Interrupt_Number = 0;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static QCLI_Command_Status_t cmd_MFP_Short_Press_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_MFP_Edge_Detect_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_MFP_Long_Press_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_MFP_Config_show(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_MFP_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t MFP_CMD_List[] =
{
    /* cmd_function                cmd_string            usage_string  description */
    {cmd_MFP_Short_Press_Enable,   "EnableShortPress",   "[enable]",   "Enable/Disable short press indication interupt"},
    {cmd_MFP_Edge_Detect_Enable,   "EnableEdgeDetect",   "[type]",     "Enable/Disable edge detect interrupt"},
    {cmd_MFP_Long_Press_Enable,    "EnableLongPress",    "[enable]",   "Enable/Disable long press code reset"},
    {cmd_MFP_Config_show,          "ShowMFPConfig",      "",           "show MFP configuration"},
    {cmd_MFP_Get_Interrupt_Number, "GetInterruptNumber", "",           "Get interrupt number"}
};

const QCLI_Command_Group_t MFP_CMD_Group =
{
    "MFP",
    (sizeof(MFP_CMD_List) / sizeof(MFP_CMD_List[0])),
    MFP_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
void Initialize_MFP_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Mfp_Handle = QCLI_Register_Command_Group(NULL, &MFP_CMD_Group);
    if (QCLI_Mfp_Handle)
    {
        MFP_PRINTF("Mfp Registered \n");
    }
}

/**
   @brief MFP short press interrupt handler.
*/
static void MFP_Short_Press_IntHandler(uint32_t Interrupt, void *UserParam)
{
    MFP_Short_Press_Interrupt_Number++;
}

/**
   @brief Enable short press indication interupt.

   @param[in] enable    Enable/Disable short press indication interrupt.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_MFP_Short_Press_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t   Retval;
    qbool_t                 Enable;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        MFP_PRINTF("EnableShortPress [enable] \n");
        return QCLI_STATUS_ERROR_E;
    }

    Enable = Parameter_List[0].Integer_Value;
    if (Enable > 1)
    {
        MFP_PRINTF("EnableShortPress paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    if (Enable)
    {
        qapi_PWR_Register_AON_Interrupt(QAPI_PWR_AON_INT_MFB_SHORT, MFP_Short_Press_IntHandler, NULL);
        MFP_PRINTF("EnableShortPress success.\n");
    }
    else
    {
        qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_MFB_SHORT);
        MFP_PRINTF("DisableShortPress success.\n");
        MFP_Short_Press_Interrupt_Number = 0;
    }

    Retval = QCLI_STATUS_SUCCESS_E;

    return Retval;
}

/**
   @brief MFP edge detect interrupt handler.
*/
static void MFP_Edge_Detect_IntHandler(uint32_t Interrupt, void *UserParam)
{
    MFP_Edge_Detect_Interrupt_Number++;
}

/**
   @brief Enable edge detect interupt.

   @param[in] type      QAPI_PWR_MFP_EDGE_DETECT_NONE_E  disable edge detection
                        QAPI_PWR_MFP_EDGE_DETECT_BOTH_E  enable dual-edge detection

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_MFP_Edge_Detect_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Status;
    qapi_PWR_MFP_Config_t Config;
    qapi_PWR_Mfp_Edge_Detect_type_t EdgeDetectType;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        MFP_PRINTF("EnableEdgeDetect [type] \n");
        return QCLI_STATUS_ERROR_E;
    }

    EdgeDetectType = (qapi_PWR_Mfp_Edge_Detect_type_t)Parameter_List[0].Integer_Value;
    if (EdgeDetectType > QAPI_PWR_MFP_EDGE_DETECT_BOTH_E)
    {
        MFP_PRINTF("EnableEdgeDetect paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }
    Config.EdgeDetectType = EdgeDetectType;
    Config.LongPressEnable = false;
    
    Status = qapi_PWR_Set_MFP(&Config);
    if (Status == QAPI_OK)
    {
        if (EdgeDetectType == QAPI_PWR_MFP_EDGE_DETECT_NONE_E)
        {
            qapi_PWR_Unregister_AON_Interrupt(QAPI_PWR_AON_INT_MFB_EDGE);
            MFP_Edge_Detect_Interrupt_Number = 0;
        }
        else
        {
            qapi_PWR_Register_AON_Interrupt(QAPI_PWR_AON_INT_MFB_EDGE, MFP_Edge_Detect_IntHandler, NULL);
        }

        Retval = QCLI_STATUS_SUCCESS_E;
        MFP_PRINTF("EnableEdgeDetect success.\n");
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        MFP_PRINTF("EnableEdgeDetect error.\n");
    }

    return Retval;
}

/**
   @brief Enable long press cold reset.

   @param[in] enable    Enable/Disable long press cold reset.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_MFP_Long_Press_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t   Retval;
    qapi_Status_t           Status;
    qbool_t                 Enable;
    qapi_PWR_MFP_Config_t   Config;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        MFP_PRINTF("EnableLongPress [enable] \n");
        return QCLI_STATUS_ERROR_E;
    }

    Enable = Parameter_List[0].Integer_Value;
    if (Enable > 1)
    {
        MFP_PRINTF("EnableLongPress paramters error.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Config.LongPressEnable = Enable;
    Config.EdgeDetectType = QAPI_PWR_MFP_EDGE_DETECT_NONE_E;

    Status = qapi_PWR_Set_MFP(&Config);
    if (Status == QAPI_OK)
    {
        Retval = QCLI_STATUS_SUCCESS_E;
        MFP_PRINTF("EnableLongPress success.\n");
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        MFP_PRINTF("EnableLongPress error.\n");
    }

    return Retval;
}

/**
   @brief Enable long press cold reset.

   @param[in] enable    Enable/Disable long press cold reset.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_MFP_Config_show(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t   Retval;
    qapi_Status_t           Status;
    qapi_PWR_MFP_Config_t   Config;

    if (Parameter_Count != 0)
    {
        MFP_PRINTF("ShowMFPConfig \n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_PWR_Get_MFP(&Config);
    if (Status == QAPI_OK)
    {
        if (Config.EdgeDetectType == QAPI_PWR_MFP_EDGE_DETECT_NONE_E)
        {
            MFP_PRINTF("short edge detect disabled\n");
        }
        else if (Config.EdgeDetectType == QAPI_PWR_MFP_EDGE_DETECT_POS_E)
        {
            MFP_PRINTF("short edge detect enabled, type is rising-edge.\n");
        }
        else if (Config.EdgeDetectType == QAPI_PWR_MFP_EDGE_DETECT_NEG_E)
        {
            MFP_PRINTF("short edge detect enabled, type is falling-edge.\n");
        }
        else
        {
            MFP_PRINTF("short edge detect enabled, type is dual-edge.\n");
        }
        
        if (Config.LongPressEnable == false)
        {
            MFP_PRINTF("long press cold reset disabled\n");
        }
        else
        {
            MFP_PRINTF("long press cold reset enabled\n");
        }
        
        Retval = QCLI_STATUS_SUCCESS_E;
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        MFP_PRINTF("ShowMFPConfig error.\n");
    }

    return Retval;
}

/**
   @brief Get MFP interrupt trigger number value.

   MFP interrupt trigger number value is clear to 0 when disable interrupt.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_MFP_Get_Interrupt_Number(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    MFP_PRINTF("MFP_Short_Press_Interrupt_Number=%d\n", MFP_Short_Press_Interrupt_Number);
    MFP_PRINTF("MFP_Edge_Detect_Interrupt_Number=%d\n", MFP_Edge_Detect_Interrupt_Number);

    return QCLI_STATUS_SUCCESS_E;
}

