/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "plat_demo.h"
#include "mfg_demo.h"
#include "nvm_demo.h"
#include "qcli_api.h"
#include "qcli_util.h"

#include "qapi_types.h"
#include "qapi_status.h"

#include "qapi_debug.h"
#include "qapi_heap.h"
#include "qapi_power.h"

static QCLI_Group_Handle_t Plat_QCLI_Handle;

static QCLI_Command_Status_t cmd_Plat_DebuggerAttached(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Plat_GetHeapStats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Plat_SetMFP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Plat_GetMFP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Plat_GetModuleState(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Plat_SubsystemOff(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

const QCLI_Command_t Plat_Cmd_List[] =
{
   /* cmd_function             cmd_string          usage_string                          description */
   {cmd_Plat_DebuggerAttached, "DebuggerAttached", "",                                   "Determines if a debugger is currently attached."},
   {cmd_Plat_GetHeapStats,     "GetHeapStats",     "",                                   "Get heap statistics."},
   {cmd_Plat_SetMFP,           "SetMFP",           "[LongPressEnable] [EdgeDetectType]", "Set the MFP configuration."},
   {cmd_Plat_GetMFP,           "GetMFP",           "",                                   "Get the MFP current configuration."},
   {cmd_Plat_GetModuleState,   "GetModuleState",   "[Module]",                           "Get the power state of a subsystem or module."},
   {cmd_Plat_SubsystemOff,     "SubsystemOff",     "[Time]",                             "Turn off APSS for a period."}
};

static const QCLI_Command_Group_t Plat_CMD_Group = {"Platform", sizeof(Plat_Cmd_List) / sizeof(QCLI_Command_t), Plat_Cmd_List};

/**
   @brief Executes the "DebuggerAttached" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_DebuggerAttached(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qbool_t Result;

   Result = qapi_DBG_Debugger_Attached();

   QCLI_Printf(Plat_QCLI_Handle, "Debugger is %sattached\n", Result ? "" : "not ");

   return(QCLI_STATUS_SUCCESS_E);
}

/**
   @brief Executes the "GetHeapStats" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_GetHeapStats(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  RetVal;
   qapi_Status_t          Result;
   qapi_Heap_Statistics_t MainHeapStats;
   qapi_Heap_Statistics_t RetnHeapStats;

   Result = qapi_Get_Heap_Statistics(&MainHeapStats, &RetnHeapStats);

   if(Result == QAPI_OK)
   {
      /* Display main heap stats */
      QCLI_Printf(Plat_QCLI_Handle, "Main heap stats\n");
      QCLI_Printf(Plat_QCLI_Handle, "   Heap Size:             %d\n", MainHeapStats.HeapSize);
      QCLI_Printf(Plat_QCLI_Handle, "   Current Heap Used:     %d\n", MainHeapStats.CurrentHeapUsed);
      QCLI_Printf(Plat_QCLI_Handle, "   Maximum Heap Used:     %d\n", MainHeapStats.MaximumHeapUsed);
      QCLI_Printf(Plat_QCLI_Handle, "   Allocated Block Count: %d\n", MainHeapStats.AllocatedBlockCount);
      QCLI_Printf(Plat_QCLI_Handle, "   Free Block Count:      %d\n", MainHeapStats.FreeBlockCount);
      QCLI_Printf(Plat_QCLI_Handle, "   Largest Free Block:    %d\n\n", MainHeapStats.LargestFreeBlock);

      /* Display retained heap stats */
      QCLI_Printf(Plat_QCLI_Handle, "Retained heap stats\n");
      QCLI_Printf(Plat_QCLI_Handle, "   Heap Size:             %d\n", RetnHeapStats.HeapSize);
      QCLI_Printf(Plat_QCLI_Handle, "   Current Heap Used:     %d\n", RetnHeapStats.CurrentHeapUsed);
      QCLI_Printf(Plat_QCLI_Handle, "   Maximum Heap Used:     %d\n", RetnHeapStats.MaximumHeapUsed);
      QCLI_Printf(Plat_QCLI_Handle, "   Allocated Block Count: %d\n", RetnHeapStats.AllocatedBlockCount);
      QCLI_Printf(Plat_QCLI_Handle, "   Free Block Count:      %d\n", RetnHeapStats.FreeBlockCount);
      QCLI_Printf(Plat_QCLI_Handle, "   Largest Free Block:    %d\n", RetnHeapStats.LargestFreeBlock);

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      QCLI_Display_Function_Status(Plat_QCLI_Handle, "qapi_Get_Heap_Statistics", Result);
      RetVal = QCLI_STATUS_ERROR_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "SetMFP" command.

   Parameter_List[0] indicates if long press cold resets should be
                     enabled or disabled for APSS.
                     0=Disabled
                     1=Enabled
   Parameter_List[1] is the edge detect type for APSS.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_SetMFP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qapi_PWR_MFP_Config_t Config;

   if((Parameter_Count >= 2) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 1)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_PWR_MFP_EDGE_DETECT_NONE_E, QAPI_PWR_MFP_EDGE_DETECT_BOTH_E)))
   {
      Config.LongPressEnable = (qbool_t)(Parameter_List[0].Integer_Value != 0);
      Config.EdgeDetectType  = (qapi_PWR_Mfp_Edge_Detect_type_t)(Parameter_List[1].Integer_Value);

      Result = qapi_PWR_Set_MFP(&Config);
      QCLI_Display_Function_Status(Plat_QCLI_Handle, "qapi_PWR_Set_MFP", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "GetMFP" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_GetMFP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qapi_PWR_MFP_Config_t Config;

   Result = qapi_PWR_Get_MFP(&Config);
   QCLI_Display_Function_Status(Plat_QCLI_Handle, "qapi_PWR_Get_MFP", Result);

   if(Result == QAPI_OK)
   {
      QCLI_Printf(Plat_QCLI_Handle, "Long Press Enable: %d\n", Config.LongPressEnable);
      QCLI_Printf(Plat_QCLI_Handle, "Edge Detect Type:  %d\n", Config.EdgeDetectType);

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      RetVal = QCLI_STATUS_ERROR_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "GetModuleState" command.

   Parameter_List[0] is the module of interest.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_GetModuleState(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_PWR_Module_t     Module;
   qapi_PWR_State_t      State;

   if((Parameter_Count >= 1) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_PWR_MODULE_BTSS_E, QAPI_PWR_MODULE_GPIO_E)))
   {
      Module = (qapi_PWR_Module_t)(Parameter_List[0].Integer_Value);

      State = qapi_PWR_Get_Module_State(Module);
      QCLI_Printf(Plat_QCLI_Handle, "Module state is %d.\n", State);

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "SubsystemOff" command.

   Parameter_List[0] is the time to sleep.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Plat_SubsystemOff(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   uint32_t              Time;

   if((Parameter_Count >= 1) &&
      (Parameter_List[0].Integer_Is_Valid))
   {
      Time = (uint32_t)(Parameter_List[0].Integer_Value);

      qapi_PWR_Subsystem_Off(Time);
      QCLI_Printf(Plat_QCLI_Handle, "qapi_PWR_Subsystem_Off() returned.\n");

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Initializes the Platform demo application.
*/
qbool_t Initialize_Plat_Demo(void)
{
   qbool_t Ret_Val;

   /* Register the command group. */
   Plat_QCLI_Handle = QCLI_Register_Command_Group(NULL, &Plat_CMD_Group);
   if(Plat_QCLI_Handle != NULL)
   {
      Ret_Val = Initialize_Mfg_Demo(Plat_QCLI_Handle) &&
                Initialize_Nvm_Demo(Plat_QCLI_Handle);
   }
   else
   {
      QCLI_Printf(Plat_QCLI_Handle, "Failed to register Platform command group.\n");
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Initializes the Platform demo application.
*/
void Cleanup_Plat_Demo(void)
{
   Cleanup_Mfg_Demo();
   Cleanup_Nvm_Demo();
   QCLI_Unregister_Command_Group(Plat_QCLI_Handle);
}
