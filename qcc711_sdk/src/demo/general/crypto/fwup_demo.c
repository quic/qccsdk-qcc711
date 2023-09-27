/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdlib.h>
#include <limits.h>
#include "qapi_firmware_update.h"
#include "qcli_api.h"
#include "qcli_util.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
/**
   By default, using blocking operation for all FWUP command execution.
   For non-blocking execution of FWUP QAPI, set this macro to false.
*/
#define FWUP_BLOCKING_OPERATION_DEFAULT_VALUE true

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/

/**
   Handle for our QCLI Command Group.
*/
QCLI_Group_Handle_t QCLI_FWUP_Handle;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/* Internal helper function. */
static const char* FWUP_Verification_Status_String(qapi_FWUP_Verification_Status_t Status);

/* Callback function. */
static void FWUP_CmdOperationCB(qapi_Status_t Status, qapi_FWUP_Operation_Event_Data_t *EventData, void *UserParam);

/* Internal result printing functions. */
static QCLI_Command_Status_t FWUP_Print_Verify_Update_Package_Result(qapi_Status_t Status, qapi_FWUP_Verify_Update_Package_t *VerifyUpdateParam);

/* firmware update operation functions. */
static QCLI_Command_Status_t cmd_FWUP_Apply_Update(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_FWUP_Verify_Update_Package(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);


/* Command list for the crypto demo. */
const QCLI_Command_t FWUP_CMD_List[] =
{
    /* cmd_function                     cmd_string          usage_string                                                description */
    { cmd_FWUP_Apply_Update,            "UpdateApply",      "<ImageSize> <ImageLocationOnNVM> <DebugEnable>",           "Perform Image Update"},
    { cmd_FWUP_Verify_Update_Package,   "UpdateVerify",     "<PackageSize> <PackageLocationOnNVM> <VerifyAllImages>",   "Verify Update Package"}

};

const QCLI_Command_Group_t FWUP_CMD_Group =
{
    "FirmwareUpdate",
    (sizeof(FWUP_CMD_List) / sizeof(FWUP_CMD_List[0])),
    FWUP_CMD_List
};

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
 * @brief Converts qapi_FWUP_Verification_Status_t enum members to string.
 *
 * @param[in] Status Firmware update operation status.
 * @return qapi_FWUP_Verification_Status_t member in string format.
*/
static const char* FWUP_Verification_Status_String(qapi_FWUP_Verification_Status_t Status)
{
    switch (Status)
    {
        case QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E:
            return "Authentication success.";
        case QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E:
            return "Authentication failure.";
        case QAPI_FWUP_VERIFICATION_IMAGE_OVERLAP_E:
            return "Image overlap.";
        case QAPI_FWUP_VERIFICATION_INVALID_INPUT_E:
            return "Invalid input.";
        default:
            break;
    }

    return "Error unknown.";
}

/**
   @brief Print verify update result.

   @param[in] Status           Verify update package status.
   @param[in] VerifyUpdateParam  Verify update package params.
   @return QCLI_STATUS_SUCCESS_E on success or QCLI_STATUS_ERROR_E on failure.
*/
static QCLI_Command_Status_t FWUP_Print_Verify_Update_Package_Result(qapi_Status_t Status, qapi_FWUP_Verify_Update_Package_t *VerifyUpdateParam)
{
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;
    if (Status == QAPI_OK)
    {
        QCLI_Printf(QCLI_FWUP_Handle, "Verify update package status: %s.\n", FWUP_Verification_Status_String(VerifyUpdateParam->VerificationStatus));
        CmdStatus = QCLI_STATUS_SUCCESS_E;
    }
    else
    {
        QCLI_Printf(QCLI_FWUP_Handle, "Verify update package failed.\n");
    }

    return CmdStatus;
}

/**
    @brief FWUP command non-blocking operation callback.

    This callback will be used only for non-blocking command execution. By default, all command
    execution are blocking call. To use callback for non-blocking execution set CRYPTO_BLOCKING_OPERATION_DEFAULT_VALUE
    to false.

    @param[in] Status     fwup operation status.
    @param[in] EventData  data specific to token operation.
    @param[in] UserParam  User specified parameter for the callback function.
*/
static void FWUP_CmdOperationCB(qapi_Status_t Status, qapi_FWUP_Operation_Event_Data_t *EventData, void *UserParam)
{
    switch (EventData->Operation)
    {
        case QAPI_FWUP_VERIFY_UPDATE_PACKAGE_E:
            (void)FWUP_Print_Verify_Update_Package_Result(Status, EventData->Data.VerifyUpdateParams);
            break;
        default:
            break;
    }
}

/**
   @brief Executes ApplyUpdate command.

   ApplyUpdate command uses three parameters.
   Parameter_List[0] Image size on NVM in bytes.
   Parameter_List[1] Image location on NVM.
   Parameter_List[2] If 1 then OEM M3 debugging capability will be locked

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_FWUP_Apply_Update(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qapi_Status_t         Status;
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;

    qapi_FWUP_Apply_Update_Package_t UpdateParam;

    if ((Parameter_Count != 3) || (Parameter_List == NULL) ||
        !QCLI_Verify_Unsigned_Integer_Parameter(&Parameter_List[2], 0, 1))
    {
        return QCLI_STATUS_USAGE_E;
    }

    UpdateParam.Size = Parameter_List[0].Integer_Value;
    if (false == QCLI_String_To_Integer(Parameter_List[1].String_Value, (int32_t*)&UpdateParam.Location))
    {
        return QCLI_STATUS_ERROR_E;
    }
    UpdateParam.LockDebug = (qbool_t)Parameter_List[2].Integer_Value;

    Status = qapi_FWUP_Apply_Update_Package(&UpdateParam);
    if (Status != QAPI_OK)
    {
        QCLI_Printf(QCLI_FWUP_Handle, "Failed to apply firmware update.\n");
    }
    else
    {
        CmdStatus = QCLI_STATUS_SUCCESS_E;
    }

    return CmdStatus;
}

/**
   @brief Executes VerifyUpdate command.

   VerifyUpdate command uses two parameters.
   Parameter_List[0] Package size on NVM in bytes.
   Parameter_List[1] Update package location on NVM.

   @param[in] Parameter_Count  Parameter count.
   @param[in] Parameter_List   Parameter list.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this command.
*/
static QCLI_Command_Status_t cmd_FWUP_Verify_Update_Package(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    qbool_t               IsBlocking = FWUP_BLOCKING_OPERATION_DEFAULT_VALUE;
    qapi_Status_t         Status;
    QCLI_Command_Status_t CmdStatus = QCLI_STATUS_ERROR_E;

    // Use static or heap allocation of params for non-blocking execution.
    qapi_FWUP_Verify_Update_Package_t VerifyUpdateParam;

    if ((Parameter_Count != 3) || (Parameter_List == NULL) ||
        !QCLI_Verify_Unsigned_Integer_Parameter(&Parameter_List[2], 0, 1))
    {
        return QCLI_STATUS_USAGE_E;
    }

    VerifyUpdateParam.Size = Parameter_List[0].Integer_Value;
    if (false == QCLI_String_To_Integer(Parameter_List[1].String_Value, (int32_t*)&VerifyUpdateParam.Location))
    {
        return QCLI_STATUS_ERROR_E;
    }

    VerifyUpdateParam.VerifyAllImages = (qbool_t)Parameter_List[2].Integer_Value;

    if (IsBlocking)
    {
        Status = qapi_FWUP_Verify_Update_Package(&VerifyUpdateParam, NULL, NULL);
        CmdStatus = FWUP_Print_Verify_Update_Package_Result(Status, &VerifyUpdateParam);
    }
    else
    {
        Status = qapi_FWUP_Verify_Update_Package(&VerifyUpdateParam, FWUP_CmdOperationCB, NULL);
        if (Status == QAPI_OK)
        {
            CmdStatus = QCLI_STATUS_SUCCESS_E;
        } else
        {
            QCLI_Printf(QCLI_FWUP_Handle, "Failed to verify firmware update package.\n");
        }
    }

    return CmdStatus;
}

/**
   @brief Cleans up resources used by the FWUP demo.
*/
void Cleanup_FWUP_Demo(void)
{
    if (QCLI_FWUP_Handle)
    {
        QCLI_Unregister_Command_Group(QCLI_FWUP_Handle);
        QCLI_FWUP_Handle = NULL;
    }
}

/**
   @brief Initialize FWUP demo.

   @param[in] Parent_Group Parent group handle.
*/
void Initialize_FWUP_Demo(QCLI_Group_Handle_t Parent_Group)
{
    /* Attempt to register the Command Groups with the qcli framework.*/
    QCLI_FWUP_Handle = QCLI_Register_Command_Group(Parent_Group, &FWUP_CMD_Group);
    if (QCLI_FWUP_Handle)
    {
        QCLI_Printf(QCLI_FWUP_Handle, "Firmware update demo registered.\n");
    }
}