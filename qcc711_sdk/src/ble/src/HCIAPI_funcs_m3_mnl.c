/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_hci.h"
#include "HCIAPI_params.h"
#include "HCIAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Send_Raw_Command(uint32_t BluetoothStackID, uint8_t Command_OGF, uint16_t Command_OCF, uint8_t Command_Length, uint8_t Command_Data[], uint8_t *StatusResult, uint8_t *LengthResult, uint8_t *BufferResult, boolean_t WaitForResponse)
{
    HCI_Send_Raw_Command_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint8_t InputLength;
    uint32_t MessageSize;

    InputLength = (LengthResult == NULL)? 0 : *LengthResult;
    MessageSize = ALIGN32(HCI_SEND_RAW_COMMAND_PARAMS_SIZE) + ALIGN32((sizeof(uint8_t) * Command_Length)) + ALIGN32(sizeof(uint8_t)) + ALIGN32(sizeof(uint8_t)) + ALIGN32((sizeof(uint8_t) * InputLength));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(HCI_SEND_RAW_COMMAND_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->Command_OGF = Command_OGF;
        Params->Command_OCF = Command_OCF;
        Params->Command_Length = Command_Length;
        if(Command_Data != NULL)
        {
            Params->Command_Data = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * Command_Length));
            memscpy(Params->Command_Data, (sizeof(uint8_t) * Command_Length), Command_Data, (sizeof(uint8_t) * Command_Length));
        }
        else
        {
            Params->Command_Data = NULL;
        }
        if(StatusResult != NULL)
        {
            Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
        }
        else
        {
            Params->StatusResult = NULL;
        }
        if(LengthResult != NULL)
        {
            Params->LengthResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + sizeof(uint8_t));
            memscpy(Params->LengthResult, sizeof(uint8_t), LengthResult, sizeof(uint8_t));
        }
        else
        {
            Params->LengthResult = NULL;
        }
        if(BufferResult != NULL)
        {
            Params->BufferResult = (uint8_t *)(((uint8_t *)Params) + Offset);
            Offset = ALIGN32(Offset + (sizeof(uint8_t) * InputLength));
        }
        else
        {
            Params->BufferResult = NULL;
        }
        Params->WaitForResponse = *((boolean_t *)&WaitForResponse);

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_SEND_RAW_COMMAND, MessageSize, (uint8_t *)Params);

        if(StatusResult)
            *StatusResult = *Params->StatusResult;

        if(LengthResult)
            *LengthResult = *Params->LengthResult;

        if(BufferResult && LengthResult)
            memscpy(BufferResult, (sizeof(uint8_t) * (*LengthResult)), Params->BufferResult, (sizeof(uint8_t) * (*LengthResult)));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}
