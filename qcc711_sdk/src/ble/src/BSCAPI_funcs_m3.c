/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_bsc.h"
#include "BSCAPI_params.h"
#include "BSCAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

int QAPI_BLE_BTPSAPI qapi_BLE_BSC_RegisterDebugCallback(uint32_t BluetoothStackID, qapi_BLE_BSC_Debug_Callback_t BSC_DebugCallback, unsigned long CallbackParameter)
{
    BSC_RegisterDebugCallback_Params_t *Params;
    int ret_val = -1;
    CallbackInfo_t CBInfo;
    uint32_t CBHandle = 0;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BSC_REGISTERDEBUGCALLBACK_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->CallbackParameter = CallbackParameter;

        if(BSC_DebugCallback != NULL)
        {
            CBInfo.FileID = FILE_ID_BSCAPI;
            CBInfo.CallbackID = CALLBACK_ID_BSC_DEBUG_CALLBACK_T;
            CBInfo.CallbackKey = 0;
            CBInfo.AppFunction = (void *)BSC_DebugCallback;
            CBInfo.AppParam = CallbackParameter;
        }

        if((BSC_DebugCallback == NULL) || (Callback_Register(&CBHandle, BSC_Debug_Callback_Handler, (const CallbackInfo_t *)&CBInfo, false) == 0))
        {
            Params->CallbackParameter = (unsigned long)CBHandle;
            ret_val = (int)IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_REGISTERDEBUGCALLBACK, MessageSize, (uint8_t *)Params);

            if(BSC_DebugCallback != NULL)
            {
                if(!(ret_val > 0))
                {
                    Callback_UnregisterByHandle(CBHandle);
                }
            }
        }
        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

void QAPI_BLE_BTPSAPI qapi_BLE_BSC_UnRegisterDebugCallback(uint32_t BluetoothStackID)
{
    BSC_UnRegisterDebugCallback_Params_t *Params;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BSC_UNREGISTERDEBUGCALLBACK_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;

        IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_UNREGISTERDEBUGCALLBACK, MessageSize, (uint8_t *)Params);

        Callback_UnregisterByKey(FILE_ID_BSCAPI, CALLBACK_ID_BSC_DEBUG_CALLBACK_T, 0);

        IPC_FreeSharedMemory(Params);
    }
}

