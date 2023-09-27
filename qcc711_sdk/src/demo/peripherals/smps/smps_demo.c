/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "stdbool.h"

#include "smps_demo.h"
#include "qcli_api.h"
#include "qcli_util.h"

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_mfg.h"
#include "qapi_power.h"
#include "qapi_sense.h"

static QCLI_Group_Handle_t SMPS_QCLI_Handle;

static QCLI_Command_Status_t cmd_SMPS_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_SMPS_Calibrate(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_SMPS_SetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_SMPS_GetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Internal help functions. */
static QCLI_Command_Status_t CalibrateSMPS(bool Start);

const QCLI_Command_t SMPS_Cmd_List[] =
{
   /* cmd_function      cmd_string   usage_string  description */
   {cmd_SMPS_Enable,    "Enable",    "",           "Enable the SMPS"},
   {cmd_SMPS_Calibrate, "Calibrate", "",           "Calibrate the SMPS"},
   {cmd_SMPS_SetVLP,    "SetVLP",    "[Voltage]",  "Set the VLP voltage"},
   {cmd_SMPS_GetVLP,    "GetVLP",    "",           "Get the VLP voltage"}
};

static const QCLI_Command_Group_t SMPS_Cmd_Group = {"SMPS", sizeof(SMPS_Cmd_List) / sizeof(QCLI_Command_t), SMPS_Cmd_List};

/**
   @brief Executes the "EnableSMPS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_SMPS_Enable(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   return(CalibrateSMPS(true));
}

/**
   @brief Executes the "CalibrateSMPS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_SMPS_Calibrate(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    return(CalibrateSMPS(false));
}

/**
   @brief Calibrate and optionally start the SMPS.
*/
static QCLI_Command_Status_t CalibrateSMPS(bool Start)
{
   QCLI_Command_Status_t Ret_Val = QCLI_STATUS_ERROR_E;
   qapi_Status_t         Result;
   uint32_t              Voltage;
   int32_t               Temperature;

   if((Result = qapi_SENS_Get_Temp(&Temperature)) == QAPI_OK)
   {
      if((Result = qapi_SENS_Voltage_Sensor_Enable(true)) == QAPI_OK)
      {
         if((Result = qapi_SENS_Vbat_Monitor_Enable(true)) == QAPI_OK)
         {
            if((Result = qapi_SENS_Get_Voltage(QAPI_SENS_VOLTAGE_SOURCE_VBAT_E, &Voltage)) == QAPI_OK)
            {
               if(Start)
               {
                  qapi_PWR_Enable_SMPS(Temperature, Voltage);

                  QCLI_Printf(SMPS_QCLI_Handle, "SMPS has been calibrated and enabled successfully.\n");
               }
               else
               {
                  qapi_PWR_Calibrate_SMPS(Temperature, Voltage);

                  QCLI_Printf(SMPS_QCLI_Handle, "SMPS has been calibrated successfully.\n");
               }

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Get_Voltage", Result);
            }

            if((Result = qapi_SENS_Vbat_Monitor_Enable(false)) != QAPI_OK)
            {
               Ret_Val = QCLI_STATUS_ERROR_E;
               QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Vbat_Monitor_Enable(false)", Result);
            }
         }
         else
         {
            QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Vbat_Monitor_Enable(true)", Result);
         }

         if((Result = qapi_SENS_Voltage_Sensor_Enable(false)) != QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
            QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Voltage_Sensor_Enable(false)", Result);
         }
      }
      else
      {
         QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Voltage_Sensor_Enable(true)", Result);
      }
   }
   else
   {
      QCLI_Display_Function_Status(SMPS_QCLI_Handle, "qapi_SENS_Get_Temp", Result);
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetVLP" command.

   Parameter_List[0] is the voltage for the VLP.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_SMPS_SetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   uint32_t              Voltage;

   if((Parameter_Count >= 1) &&
      (Parameter_List[0].Integer_Is_Valid))
   {
      Voltage = (uint32_t)(Parameter_List[0].Integer_Value);

      if(qapi_PWR_Set_VLP_Voltage(Voltage))
      {
         QCLI_Printf(SMPS_QCLI_Handle, "qapi_PWR_Set_VLP_Voltage() success.\n");

         RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Printf(SMPS_QCLI_Handle, "qapi_PWR_Set_VLP_Voltage() failed.\n");

         RetVal = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "GetVLP" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_SMPS_GetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   uint32_t Voltage;

   Voltage = qapi_PWR_Get_VLP_Voltage();

   QCLI_Printf(SMPS_QCLI_Handle, "VLP Voltage: %dmV\n", Voltage);

   return(QCLI_STATUS_SUCCESS_E);
}

/**
   @brief Initializes the SMPS demo application.
*/
qbool_t Initialize_SMPS_Demo(void)
{
   qbool_t RetVal;

   /* Register the command group. */
   SMPS_QCLI_Handle = QCLI_Register_Command_Group(NULL, &SMPS_Cmd_Group);
   if(SMPS_QCLI_Handle != NULL)
   {
      RetVal = true;
   }
   else
   {
      QCLI_Printf(SMPS_QCLI_Handle, "Failed to register SMPS command group.\n");
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Cleans up the Manufacturing demo application.
*/
void Cleanup_SMPS_Demo(void)
{
   QCLI_Unregister_Command_Group(SMPS_QCLI_Handle);
}
