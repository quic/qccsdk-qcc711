 /*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __ROT_DEMO_UTILS_H__
#define __ROT_DEMO_UTILS_H__

#include <stdio.h>

/** Maximum length for input string in bytes. */
#define ROT_MAX_INPUT_LENGTH (1024)

/** Helper macro to free allocated memory. */
#define FREE_IF(ptr)       \
    if (ptr != NULL)       \
    {                      \
        qapi_Free(ptr);    \
    }

/**
   @brief Convert Hex string to byte array.
   Caller is responsible to free the allocated memory returned by this function.

   @param[in] InputString     Input string.
   @param[in] Len             Input Length.
   @param[in] QcliGroupHandle Qcli group handle.

   @return Byte array converted from hex string on success, or NULL on failure.
*/
uint8_t *GetArrayFromHexString(char *InputString, uint32_t Len, QCLI_Group_Handle_t QcliGroupHandle);

/**
   @brief Convert Qapi status to Qcli status.

   @param[in] Status Qapi status.

   @return Qcli command status.
*/
QCLI_Command_Status_t GetQcliStatusFromQapiStatus(qapi_Status_t Status);

#endif // __ROT_DEMO_UTILS_H__