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
#include "qapi_wdog.h"
#include "qapi_mfg.h"
#include "qapi_power.h"
#include "qapi_sense.h"
#include "qapi_rot.h"
#include "qapi_fuse.h"
#include "qapi_mtp.h"
 
#include "qcli_pal.h"
#include "qcli.h"
#include <qcli_api.h>

#include "wdog_demo.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define WDOG_DBG
#ifdef WDOG_DBG
#define WDOG_PRINTF(...)     QCLI_Printf(QCLI_Wdog_Handle, __VA_ARGS__)
#else
#define WDOG_PRINTF(x, ...)
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
QCLI_Group_Handle_t QCLI_Wdog_Handle;
static qbool_t QCLI_Wdog_Bite_Reset_Enabled = 0;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static QCLI_Command_Status_t cmd_WDOG_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_WDOG_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_WDOG_Is_Bite_Reset_Enabled(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_WDOG_Pet(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_WDOG_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_WDOG_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 
static QCLI_Command_Status_t cmd_WDOG_Get_Interrupt_Status(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List); 

const QCLI_Command_t WDOG_CMD_List[] =
{
    /* cmd_function                  cmd_string            usage_string       description */
    {cmd_WDOG_Enable,                "EnableWdog",         "[time]",          "Enable Wdog and set the bark time"},
    {cmd_WDOG_Disable,               "DisableWdog",        "",                "Disable Wdog function"},
    {cmd_WDOG_Is_Bite_Reset_Enabled, "IsBiteResetEnabled", "",                "Checks if the OTP is set to enable the Wdog bite reset"},
    {cmd_WDOG_Pet,                   "PetWdog",            "",                "Pet the Wdog"},
    {cmd_WDOG_Interrupt_Enable,      "EnableInterrupt",    "",                "Enable Wdog bark interrupt"},
    {cmd_WDOG_Interrupt_Disable,     "DisableInterrupt",   "",                "Disable Wdog bark interrupt"},
    {cmd_WDOG_Get_Interrupt_Status,  "GetInterruptStatus", "",                "Get Wdog interrupt status"}
};

const QCLI_Command_Group_t WDOG_CMD_Group =
{
    "WDOG",
    (sizeof(WDOG_CMD_List) / sizeof(WDOG_CMD_List[0])),
    WDOG_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the watchdog demo application.
*/
void Initialize_WDOG_Demo(void)
{
    /* Attempt to reqister the Command Groups with the qcli framework.*/
    QCLI_Wdog_Handle = QCLI_Register_Command_Group(NULL, &WDOG_CMD_Group);
    if (QCLI_Wdog_Handle)
    {
        WDOG_PRINTF("Wdog Registered \n");
    }
}

/**
   @brief Enable Watchdog function and set the Bark time.

   @param[in] Time        Bark time, unit:100ms.(Bite time is time*2)

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Status;
    uint32_t              Time;

    if (Parameter_Count != 1 || !Parameter_List)
    {
        WDOG_PRINTF("EnableWdog [time] \n");
        return QCLI_STATUS_ERROR_E;
    }

    Time = Parameter_List[0].Integer_Value;
    if ((Time == 0) || (Time > 0xFF))
    {
        WDOG_PRINTF("EnableWdog paramters error. Bark time need larger than 0 and small than 128, 12.8 seconds.\n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_WDOG_Configure((uint8_t)Time);

    if (Status == QAPI_OK)
    {
        Retval = QCLI_STATUS_SUCCESS_E;
        WDOG_PRINTF("EnableWdog success, bark time=%d ms, bite time =%d ms.\n",
                    Time*100, Time*200);
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        WDOG_PRINTF("EnableWdog function error, Bark time need small than 128, 12.8 seconds.\n");
    }
    
    return Retval;
}

/**
   @brief Disable Watchdog function.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Status;

    if (Parameter_Count != 0)
    {
        WDOG_PRINTF("DisableWdog \n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_WDOG_Configure(0);

    if (Status == QAPI_OK)
    {
        Retval = QCLI_STATUS_SUCCESS_E;
        WDOG_PRINTF("DisableWdog success.\n");
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        WDOG_PRINTF("DisableWdog function error.\n");
    }
    
    return Retval;
}

/**
   @brief Determines if the watchdog bite reset is enabled.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Is_Bite_Reset_Enabled(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Result;
    qbool_t               RotSessionStarted;
    uint32_t              FuseVal;

    RotSessionStarted = (qbool_t)(qapi_ROT_Session_Start() == QAPI_OK);

    Result = qapi_Fuse_Read(QAPI_OTP_DEBUG_DISABLE_VECTOR_ADDRESS, &FuseVal);
    if(Result == QAPI_OK)
    {
        if(FuseVal & QAPI_OTP_DEBUG_DISABLE_VECTOR_WDOG_BITE_SOC_RESET_ENABLE_BITMASK)
        {
            WDOG_PRINTF("Watchdog bite reset enabled.\n");
            QCLI_Wdog_Bite_Reset_Enabled = true;
        }
        else
        {
            WDOG_PRINTF("Watchdog bite reset not enabled.\n");
            QCLI_Wdog_Bite_Reset_Enabled = false;
        }

        Retval = QCLI_STATUS_SUCCESS_E;
    }
    else
    {
        WDOG_PRINTF("Failed to reset debug_disable_vector OTP.\n");
        Retval = QCLI_STATUS_ERROR_E;
    }

    if(RotSessionStarted)
    {
        qapi_ROT_Session_End();
    }

    return Retval;
}

/**
   @brief Pet the watchdog.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Pet(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    if (Parameter_Count != 0)
    {
        WDOG_PRINTF("PetWdog \n");
        return QCLI_STATUS_ERROR_E;
    }

    qapi_WDOG_Pet();
    
    WDOG_PRINTF("PetWdog success.\n");

    return  QCLI_STATUS_SUCCESS_E;;
}

/**
   @brief Enable Watchdog Interrupt function.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Interrupt_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Status;

    if (Parameter_Count != 0)
    {
        WDOG_PRINTF("EnableInterrupt \n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_WDOG_EnableIRQ(1);

    if (Status == QAPI_OK)
    {
        Retval = QCLI_STATUS_SUCCESS_E;
        WDOG_PRINTF("EnableInterrupt success.\n");
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        WDOG_PRINTF("EnableInterrupt function error.\n");
    }
    
    return Retval;
}

/**
   @brief Disable Watchdog Interrupt function.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Interrupt_Disable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t Retval;
    qapi_Status_t         Status;

    if (Parameter_Count != 0)
    {
        WDOG_PRINTF("DisableInterrupt \n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_WDOG_EnableIRQ(0);

    if (Status == QAPI_OK)
    {
        Retval = QCLI_STATUS_SUCCESS_E;
        WDOG_PRINTF("DisableInterrupt success.\n");
    }
    else
    {
        Retval = QCLI_STATUS_ERROR_E;
        WDOG_PRINTF("DisableInterrupt function error.\n");
    }
    
    return Retval;
}

/**
   @brief Get watchdog interrupt status.

   @return
    - 0 if the help was displayed correctly.
    - A positive value indicating the depth of the error if a paramter was
      invalid.
*/
static QCLI_Command_Status_t cmd_WDOG_Get_Interrupt_Status(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qbool_t               Status;

    if (Parameter_Count != 0)
    {
        WDOG_PRINTF("GetInterruptStatus \n");
        return QCLI_STATUS_ERROR_E;
    }

    Status = qapi_WDOG_GetIRQStatus();
    WDOG_PRINTF("Wdog interrupt status:%x\n", Status);

    return QCLI_STATUS_SUCCESS_E;
}
 
void WDogBark_IntHandler(void)
{
    qbool_t Status;

    Status = qapi_WDOG_GetIRQStatus();
    WDOG_PRINTF("Wdog interrupt handle function -- status:%x\n", Status);
    if (QCLI_Wdog_Bite_Reset_Enabled == false)
    {
        qapi_PWR_Reset(QAPI_PWR_RESET_TYPE_SOC_COLD_RESET_E);
    }
}
