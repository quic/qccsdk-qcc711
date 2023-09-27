/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_bsc.h"
#include "BSCAPI_params.h"
#include "BSCAPI_cb_m3.h"
#include "BSCAPI_mnl_util.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"
#include "qapi_power.h"
#include "qapi_sense.h"
#include "qapi_heap.h"
#include "qapi_ble_errors.h"
#include "qapi_ble_hci.h"
#include "qapi_version.h"
#include "qapi_task.h"

   /* Constants for querying the version information.                   */
#define QAPI_BLE_HCI_VS_READ_VERSION_INFO_OCF            0x001E

#define QAPI_BLE_HCI_VS_READ_VERSION_STATUS_INDEX        0
#define QAPI_BLE_HCI_VS_READ_VERSION_ROM_VERSION_INDEX   1
#define QAPI_BLE_HCI_VS_READ_VERSION_RAM_VERSION_INDEX   5
#define QAPI_BLE_HCI_VS_READ_VERSION_CHIP_VERSION_INDEX  9
#define QAPI_BLE_HCI_VS_READ_VERSION_NVM_VERSION_INDEX   13

#define QAPI_BLE_BSC_INITIALIZE_LFXTAL_TIMEOUT                3000

int QAPI_BLE_BTPSAPI qapi_BLE_BSC_Initialize(qapi_BLE_HCI_DriverInformation_t *HCI_DriverInformation, unsigned long Flags)
{
    BSC_Initialize_Params_t *Params;
    int ret_val = QAPI_BLE_BTPS_ERROR_STACK_INITIALIZATION_ERROR;
    int32_t Temperature;
    uint32_t Offset;
    uint32_t MessageSize;
    qapi_Status_t Result;
    uint32_t StartTime;

    MessageSize = ALIGN32(BSC_INITIALIZE_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_HCI_DriverInformation_t)) + ALIGN32(sizeof(ApssVersionInfo_t));

    if(IPC_Initialize() == 0)
    {
        if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
        {
            Offset = ALIGN32(BSC_INITIALIZE_PARAMS_SIZE);
            if(HCI_DriverInformation != NULL)
            {
                Params->HCI_DriverInformation = (qapi_BLE_HCI_DriverInformation_t *)(((uint8_t *)Params) + Offset);
                memscpy(Params->HCI_DriverInformation, sizeof(qapi_BLE_HCI_DriverInformation_t), HCI_DriverInformation, sizeof(qapi_BLE_HCI_DriverInformation_t));
            }
            else
            {
                Params->HCI_DriverInformation = NULL;
            }
            Params->Flags = Flags;

            /* Populate the message with APSS Chip and Build versions. */
            Offset = Offset + ALIGN32(sizeof(qapi_BLE_HCI_DriverInformation_t));
            ((ApssVersionInfo_t *)(((uint8_t *)Params) + Offset))->ChipVersion = QAPI_CHIP_VERSION;
            ((ApssVersionInfo_t *)(((uint8_t *)Params) + Offset))->BuildVersion = QAPI_BUILD_VERSION;

            /* LFXTAL enablement requires temperature reading.         */
            Result = qapi_SENS_Get_Temp(&Temperature);
            if(Result == QAPI_OK)
            {
                /* Enable LFXTAL and guarantee settling before         */
                /* initializing the Bluetooth Subsystem.               */
                Result = qapi_PWR_Set_LFCLK_Source(QAPI_PWR_LFCLK_SOURCE_LFXTAL, Temperature, NULL, NULL);
                if(Result == QAPI_ERR_BUSY)
                {
                    /* wait for the LFXTAL to finish starting. */
                    Result = QAPI_OK;
                    StartTime = qapi_TSK_Get_Tick_Count();
                    while(qapi_PWR_Get_LFCLK_Source() != QAPI_PWR_LFCLK_SOURCE_LFXTAL)
                    {
                        if((qapi_TSK_Get_Tick_Count() - StartTime) > QAPI_BLE_BSC_INITIALIZE_LFXTAL_TIMEOUT)
                        {
                            /* XTAL hasn't started so time out the     */
                            /* initialization.                         */
                            Result = QAPI_ERR_TIMEOUT;
                            break;
                        }
                    }
                }

                if((Result == QAPI_OK) || (Result == QAPI_ERR_EXISTS))
                {
                    /* Enable the 32M XTAL.                            */
                    qapi_PWR_Set_HFCLK_Source(TRUE);

                    ret_val = (int)IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_INITIALIZE, MessageSize, (uint8_t *)Params);
                    if(ret_val <= 0)
                    {
                        /* Disable the 32K and 32M XTAL.               */
                        qapi_PWR_Set_LFCLK_Source(QAPI_PWR_LFCLK_SOURCE_SOSC, 0, NULL, NULL);
                        qapi_PWR_Set_HFCLK_Source(FALSE);
                    }
                }
            }

            if(ret_val <= 0)
            {
                IPC_FreeSharedMemory(Params);
            }
        }

        if(ret_val <= 0)
        {
            IPC_Cleanup();
        }
    }

    return(ret_val);
}

void QAPI_BLE_BTPSAPI qapi_BLE_BSC_Shutdown(uint32_t BluetoothStackID)
{
    BSC_Shutdown_Params_t *Params;

    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(BSC_SHUTDOWN_PARAMS_SIZE))))
    {
        Params->BluetoothStackID = BluetoothStackID;

        IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_SHUTDOWN, BSC_SHUTDOWN_PARAMS_SIZE, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);

        /* Take out our vote for the 32K and 32M XTALs.                 */
        qapi_PWR_Set_LFCLK_Source(QAPI_PWR_LFCLK_SOURCE_SOSC, 0, NULL, NULL);
        qapi_PWR_Set_HFCLK_Source(FALSE);
    }

    IPC_Cleanup();
}

/**
 * @brief
 * Utility function that queries the version information.
 *
 * @details
 * Opaque lists and list entries are a schema that allows any data
 * structure to be added to a list (of like structures).
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a call
 *                                to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  VersionInformation   Holds the version information
 *                                   if this function is successful.
 *
 * @return       Zero if successful.
 *
 * @return       Negative if an Error occurred. Possible values are:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
int QAPI_BLE_BTPSAPI qapi_BLE_BSC_Query_Version_Information(uint32_t BluetoothStackID, qapi_BLE_BSC_Version_Information_t *VersionInformation)
{
   int32_t ret_val;
   uint8_t StatusResult;
   uint8_t ResponseBuffer[17];
   uint8_t ResponseBufferLength;

   /* Make sure the input parameters are valid.                         */
   if((BluetoothStackID) && (VersionInformation))
   {
      /* Format command.                                                */
      ResponseBufferLength = sizeof(ResponseBuffer);

      ret_val = qapi_BLE_HCI_Send_Raw_Command(BluetoothStackID,
                                              QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF,
                                              QAPI_BLE_HCI_VS_READ_VERSION_INFO_OCF,
                                              0,
                                              NULL,
                                              &StatusResult,
                                              &ResponseBufferLength,
                                              ResponseBuffer,
                                              TRUE);

      if((!ret_val) && (!StatusResult))
      {

         if(ResponseBufferLength == sizeof(ResponseBuffer))
         {
            VersionInformation->ROM_Version    = *((uint32_t *)&(ResponseBuffer[QAPI_BLE_HCI_VS_READ_VERSION_ROM_VERSION_INDEX]));
            VersionInformation->Patch_Version  = *((uint32_t *)&(ResponseBuffer[QAPI_BLE_HCI_VS_READ_VERSION_RAM_VERSION_INDEX]));
            VersionInformation->Config_Version = *((uint32_t *)&(ResponseBuffer[QAPI_BLE_HCI_VS_READ_VERSION_NVM_VERSION_INDEX]));
         }
         else
         {
            ret_val = QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES;
         }

      }
      else
      {
         if(StatusResult)
            ret_val = QAPI_BLE_BTPS_ERROR_CODE_HCI_STATUS_BASE - ret_val;
      }
   }
   else
   {
      ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }

   return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BSC_QueryStatistics(uint32_t BluetoothStackID, qapi_BLE_BSC_Statistics_t *Statistics)
{
    BSC_QueryStatistics_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BSC_QUERYSTATISTICS_PARAMS_SIZE) + ALIGN32(sizeof(qapi_BLE_BSC_Statistics_t));

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Offset = ALIGN32(BSC_QUERYSTATISTICS_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        if(Statistics != NULL)
        {
            Params->Statistics = (qapi_BLE_BSC_Statistics_t *)(((uint8_t *)Params) + Offset);
        }
        else
        {
            Params->Statistics = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_QUERYSTATISTICS, MessageSize, (uint8_t *)Params);

        if(ret_val == QAPI_OK)
           memscpy(Statistics, sizeof(qapi_BLE_BSC_Statistics_t), Params->Statistics, sizeof(qapi_BLE_BSC_Statistics_t));

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_BSC_ClearStatistics(uint32_t BluetoothStackID, uint32_t Flags)
{
    BSC_ClearStatistics_Params_t *Params;
    int ret_val = -1;
    uint32_t MessageSize;

    MessageSize = ALIGN32(BSC_CLEARSTATISTICS_PARAMS_SIZE);

    if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
    {
        Params->BluetoothStackID = BluetoothStackID;
        Params->Flags = Flags;

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_BSCAPI, FUNCTION_ID_BSC_CLEARSTATISTICS, MessageSize, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

