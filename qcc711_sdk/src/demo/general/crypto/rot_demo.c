/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "qcli_api.h"
#include "qapi_rot.h"
#include "qapi_types.h"
#include "qapi_status.h"
#include "crypto_demo.h"
#include "fwup_demo.h"

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for RoT Command Group.
*/
static QCLI_Group_Handle_t RoT_QCLI_Handle;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
/* ROT session operation functions. */
static QCLI_Command_Status_t cmd_Start_RoT_Session(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_End_RoT_Session(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Get_RoT_Patch_Version(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* Command list for the ROT demo. */
const QCLI_Command_t RoT_CMD_List[] =
{
   /* cmd_function               cmd_string        usage_string    description                  */
   { cmd_Start_RoT_Session,     "RoTStartSession",  NULL,         "Starts a new RoT session."  },
   { cmd_End_RoT_Session,       "RoTEndSession",    NULL,         "Closes existing RoT session"},
   { cmd_Get_RoT_Patch_Version, "RoTPatchVersion",  NULL,         "Get RoT patch version"}
};

static const QCLI_Command_Group_t RoT_CMD_Group = 
{
   "ROT", 
   (sizeof(RoT_CMD_List) / sizeof(RoT_CMD_List[0])), 
   RoT_CMD_List
};

/**
    @brief Execute RoTStartSession command.

    RoTStartSession command takes 0 parameter.

    @param[in] Parameter_Count  Parameter count.
    @param[in] Parameter_List   Parameter list.

    @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
*/
static QCLI_Command_Status_t cmd_Start_RoT_Session(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_SUCCESS_E;

    if (qapi_ROT_Session_Start() != QAPI_OK)
    {
        QCLI_Printf(RoT_QCLI_Handle, "Failed to create new RoT session\n");
        CmdStatus = QCLI_STATUS_ERROR_E;
    }
    return CmdStatus;
}

/**
    @brief Execute RoTEndSession command.

    RoTEndSession takes 0 parameter.

    @param[in] Parameter_Count  Parameter count.
    @param[in] Parameter_List   Parameter list.

    @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
*/
static QCLI_Command_Status_t cmd_End_RoT_Session(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_SUCCESS_E;

    if (qapi_ROT_Session_End() != QAPI_OK)
    {
        QCLI_Printf(RoT_QCLI_Handle, "Failed to end existing RoT session\n");
        CmdStatus = QCLI_STATUS_ERROR_E;
    }
    return CmdStatus;
}

/**
    @brief Execute RoTPatchVersion command.

    RoTPatchVersion takes 0 parameter.

    @param[in] Parameter_Count  Parameter count.
    @param[in] Parameter_List   Parameter list.

    @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
*/
static QCLI_Command_Status_t cmd_Get_RoT_Patch_Version(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_SUCCESS_E;
    
    uint8_t PatchVersionBuf[QAPI_ROT_PATCH_VERSION_LEN] = {0};
    qapi_ROT_Get_Patch_Version_Params_t GetPatchVersionParams;
    GetPatchVersionParams.PatchVersion = PatchVersionBuf;
    GetPatchVersionParams.PatchVersionLen = QAPI_ROT_PATCH_VERSION_LEN;
    
    if (qapi_ROT_Get_Patch_Version(&GetPatchVersionParams, NULL, NULL) == QAPI_OK)
    {
        QCLI_Printf(RoT_QCLI_Handle, "Patch Version: %s\n", PatchVersionBuf);
    }
    else
    {
        QCLI_Printf(RoT_QCLI_Handle, "Get patch version failed.\n");
        CmdStatus = QCLI_STATUS_ERROR_E;
    }
    return CmdStatus;
}

/**
   @brief Initializes the RoT demo application.

   @return true if RoT demo initialized successfully or false on failure.
*/
qbool_t Initialize_RoT_Demo(void)
{
   qbool_t RetVal = true;

   /* Register the command group. */
   RoT_QCLI_Handle = QCLI_Register_Command_Group(NULL, &RoT_CMD_Group);

   if (RoT_QCLI_Handle != NULL)
   {
      Initialize_Crypto_Demo(RoT_QCLI_Handle);
      Initialize_FWUP_Demo(RoT_QCLI_Handle);
   } else
   {
      QCLI_Printf(RoT_QCLI_Handle, "Failed to register RoT command group.\n");
      RetVal = false;
   }

   return RetVal;
}

/**
   @brief Cleans up the RoT demo application.
*/
void Cleanup_RoT_Demo(void)
{
   Cleanup_Crypto_Demo();
   Cleanup_FWUP_Demo();
   QCLI_Unregister_Command_Group(RoT_QCLI_Handle);
}