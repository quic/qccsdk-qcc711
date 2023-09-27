/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "qapi_heap.h"
#include "qcli_api.h"
#include "qapi_status.h"
#include "rot_demo_utils.h"
#include "qcli_util.h"

/**
   @brief Convert Hex string to byte array.
   Caller is responsible to free the allocated memory returned by this function.

   @param[in] InputString     Input string.
   @param[in] Len             Input Length.
   @param[in] QcliGroupHandle Qcli group handle.

   @return Byte array converted from hex string on success, or NULL on failure.
*/
uint8_t *GetArrayFromHexString(char *InputString, uint32_t Len, QCLI_Group_Handle_t QcliGroupHandle)
{
    uint8_t *Buffer = NULL;
    uint32_t RequiredLen;
    qbool_t  ConvertResult;

    if (Len > ROT_MAX_INPUT_LENGTH)
    {
        QCLI_Printf(QcliGroupHandle, "ERROR: Provided string length is too big, maximum supported length is %d bytes\n",
                                      ROT_MAX_INPUT_LENGTH);
        return NULL;
    }

    if (strlen(InputString) != Len * 2)
    {
        QCLI_Printf(QcliGroupHandle, "ERROR: String length does not match with provided length\n");
        return NULL;
    }

    Buffer  = qapi_Malloc(Len);
    if (Buffer == NULL)
    {
        QCLI_Printf(QcliGroupHandle, "ERROR: No enough memory.\n");
        return NULL;
    }
    memset(Buffer, 0, Len);

    RequiredLen = Len;
    ConvertResult = QCLI_Hex_String_To_Array(InputString, &RequiredLen, Buffer);

    if (!ConvertResult || RequiredLen != Len)
    {
        qapi_Free(Buffer);
        QCLI_Printf(QcliGroupHandle, "ERROR: Hex String to array conversion failed.\n");
        return NULL;
    }

    return Buffer;
}

/**
   @brief Convert Qapi status to Qcli status.

   @param[in] Status Qapi status.

   @return Qcli command status.
*/
QCLI_Command_Status_t GetQcliStatusFromQapiStatus(qapi_Status_t Status)
{
    QCLI_Command_Status_t CmdStatus;
    switch(Status)
    {
        case QAPI_OK:
            CmdStatus = QCLI_STATUS_SUCCESS_E;
            break;
        case QAPI_ERR_INVALID_PARAM:
            CmdStatus = QCLI_STATUS_USAGE_E;
            break;
        default:
            CmdStatus = QCLI_STATUS_ERROR_E;
    }
    return CmdStatus;
}