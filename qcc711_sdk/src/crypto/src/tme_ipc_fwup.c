/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
// QAPI headers
#include "qapi_status.h"
#include "qapi_heap.h"
#include "qapi_firmware_update.h"

 // TME utility headers
#include "tme_types.h"
#include "tme_ipc_utils.h"
#include "tme_ipc_callback_utils.h"
#include "tme_ipc_nvm_utils.h"

// TME interface headers
#include "tme_update_interface.h"

/*-------------------------------------------------------------------------
 * Macro Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Static global function definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Function to convert TME verification status to QAPI verification status.

   @param [in]  TMEUpdateVerificationStatus      TME Manifest verification status
   @param [out] qapi_FWUP_Verification_Status_t  Corresponding QAPI manifest verification
                                                 status.
 */
static qapi_FWUP_Verification_Status_t Qapi_Verification_Status_Mapping
                                               (TMEUpdateVerificationStatus TmeVerificationStatus)
{
   qapi_FWUP_Verification_Status_t QapiVerificationStatus = QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E;
   switch(TmeVerificationStatus)
   {
   case TME_VERIFICATION_SUCCESS:
     QapiVerificationStatus = QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E;
     break;
   case TME_VERIFICATION_INVALID_INPUT:
     QapiVerificationStatus = QAPI_FWUP_VERIFICATION_INVALID_INPUT_E;
     break;
   case TME_VERIFICATION_IMAGE_OVERLAP:
     QapiVerificationStatus = QAPI_FWUP_VERIFICATION_IMAGE_OVERLAP_E;
     break;
   default:
     QapiVerificationStatus = QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E;
   }
   return QapiVerificationStatus;
}

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Validate QAPI parameters and create corresponding apply firmware update IPC message.

   @param[in]      QapiFwupParams   QAPI apply firmware update parameters.
   @param[in, out] TMEIPCMsg        TME apply firmware update IPC message.
   @param[in, out] TMEIPCMsgLength  TME apply firmware update IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Firmware_Update_Apply_IPC_Msg(void *QapiFwupParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength)
{
    qapi_FWUP_Apply_Update_Package_t *UpdateParam = (qapi_FWUP_Apply_Update_Package_t*)QapiFwupParams;
    // Validate the address range falls within NVM Address Range along with size
    if (NULL == UpdateParam || UpdateParam->LockDebug > 1 || UpdateParam->Location == 0 ||
        UpdateParam->Size == 0 || 
        Validate_FW_Update_Address_Range(UpdateParam->Location, UpdateParam->Size) != QAPI_OK)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    *TmeIPCMsgLength = sizeof(TMEApplyUpdateMessage);
    *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
    if (*TmeIPCMsg == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    TMEApplyUpdateMessage *FwupIPCMsg = (TMEApplyUpdateMessage*)(*TmeIPCMsg);
    FwupIPCMsg->input.address = UpdateParam->Location;
    FwupIPCMsg->input.size = UpdateParam->Size;
    FwupIPCMsg->input.debug = UpdateParam->LockDebug;
    // Give TME access of complete NVM block
    return Give_TME_Access_Of_NVM();
}

/**
   @brief Validate apply firmware update IPC message response. Create event data for non-blocking call.

   @param[in] QapiFwupParams  QAPI apply firmware update parameters.
   @param[in] TMEIPCMsg       TME apply firmware update IPC message.
   @param[in] Status          Tmecom return status.
   @param[in] CallBack        QAPI callback function.
   @param[in] UserData        Placeholder for user data.

   @return It will only return some error value of type qapi_Status_t.
*/
qapi_Status_t Process_Firmware_Update_Apply_IPC_Msg_Response(void *QapiFwupParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *CallBack,
                                              void *UserData)
{
    TMEApplyUpdateMessage *FwupIPCMsg = (TMEApplyUpdateMessage*)(TMEIPCMsg);
    // Remove the access of TME from NVM blocks
    Revoke_TME_Access_Of_NVM();
    if(Status == QAPI_OK)
    {
        Status = qapi_Convert_Tme_Status(FwupIPCMsg->output.status);
    }
    return Status;
}

/**
   @brief Validate QAPI parameters and create corresponding verify firmware update IPC message.

   @param[in]      QapiFwupParams   QAPI verify firmware update parameters.
   @param[in, out] TMEIPCMsg        TME verify firmware update IPC message.
   @param[in, out] TMEIPCMsgLength  TME verify firmware update IPC message length.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Validate_And_Create_Firmware_Update_Verify_IPC_Msg(void *QapiFwupParams,
                                                 void **TmeIPCMsg,
                                                 uint32_t *TmeIPCMsgLength)
{
    qapi_FWUP_Verify_Update_Package_t *VerifyParam = (qapi_FWUP_Verify_Update_Package_t*)QapiFwupParams;
    // Validate the address range falls within NVM Address Range along with size
    if (NULL == VerifyParam || VerifyParam->Location == 0 || VerifyParam->Size == 0 ||
        Validate_FW_Update_Address_Range(VerifyParam->Location, VerifyParam->Size) != QAPI_OK)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    *TmeIPCMsgLength = sizeof(TMEVerifyUpdateMessage);
    *TmeIPCMsg = qapi_Malloc(*TmeIPCMsgLength);
    if (*TmeIPCMsg == NULL)
    {
        return QAPI_ERR_NO_MEMORY;
    }

    TMEVerifyUpdateMessage *FwupIPCMsg = (TMEVerifyUpdateMessage*)(*TmeIPCMsg);
    FwupIPCMsg->input.address = VerifyParam->Location;
    FwupIPCMsg->input.size = VerifyParam->Size;
    FwupIPCMsg->input.verifyAll = VerifyParam->VerifyAllImages;
    // Give TME access of complete NVM block
    return Give_TME_Access_Of_NVM();
}

/**
   @brief Validate verify firmware update IPC message response. Create event data for non-blocking call.

   @param[in] QapiFwupParams  QAPI verify firmware update parameters.
   @param[in] TMEIPCMsg       TME verify firmware update IPC message.
   @param[in] Status          Tmecom return status.
   @param[in] CallBack        QAPI callback function.
   @param[in] UserData        Placeholder for user data.

   @return QAPI_OK if completed successfully, or a negative value if there was an error.
*/
qapi_Status_t Process_Firmware_Update_Verify_IPC_Msg_Response(void *QapiFwupParams,
                                              void *TMEIPCMsg,
                                              qapi_Status_t Status,
                                              void *CallBack,
                                              void *UserData)
{
    TMEVerifyUpdateMessage *FwupIPCMsg = (TMEVerifyUpdateMessage*)(TMEIPCMsg);
    qapi_FWUP_Verify_Update_Package_t *VerifyParam = (qapi_FWUP_Verify_Update_Package_t*)QapiFwupParams;

    // Remove the access of TME from NVM block
    Revoke_TME_Access_Of_NVM();

    VerifyParam->VerificationStatus  = Qapi_Verification_Status_Mapping(FwupIPCMsg->output.verificationStatus);

    if(Status == QAPI_OK)
    {
        Status = qapi_Convert_Tme_Status(FwupIPCMsg->output.status);
    }

    // Only executed for Non blocking call, when callback is not null.
    if (CallBack != NULL)
    {
        qapi_FWUP_Operation_Event_Data_t *EventData;
        EventData = qapi_Malloc(sizeof(qapi_FWUP_Operation_Event_Data_t));
        if(EventData == NULL)
        {
          Status = QAPI_ERR_NO_MEMORY;
        }
        else
        {
          EventData->Operation = QAPI_FWUP_VERIFY_UPDATE_PACKAGE_E;
          EventData->Data.VerifyUpdateParams = VerifyParam;
          Status = Process_TME_Callback(Status, FIRMWARE_EVENT_DATA, EventData, UserData, CallBack);
        }
    }
    return Status;
}
