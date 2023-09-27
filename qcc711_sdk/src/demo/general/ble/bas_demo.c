/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "ble_demo.h"
#include "bas_demo.h"

#include "qcli_api.h"
#include "qcli_util.h"
#include "qcli_pal.h"

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_task.h"

#include "qapi_ble_bas.h"

/* Macros to pack alligned data. */
#define ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(_x, _y) (((uint16_t *)(_x))[0] = (uint16_t)(_y))

/* Structure represents the BAS demo context information. */
typedef struct BLE_Demo_Context_s
{
   QCLI_Group_Handle_t                QCLI_Handle;       /*< QCLI handle for the BAS demo. */
   uint32_t                           InstanceID;        /*< Battery service instances ID. */
   uint8_t                            BatteryLevel;      /*< Battery level. */
   qapi_BLE_BAS_Client_Information_t  BASClientInfo;
   qapi_BLE_BAS_Server_Information_t  BASServerInfo;
} BAS_Demo_Context_t;

/* The BAS demo context. */
static BAS_Demo_Context_t BAS_Demo_Context;

/* BAS demo command functions. */
static QCLI_Command_Status_t cmd_BAS_RegisterService(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_UnRegisterService(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_DiscoverBAS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_ConfigureRemoteBAS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_GetBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_SetBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_NotifyBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_GetBatteryPresentationFormat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_BAS_SetBatteryPresentationFormat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/* BAS help function. */
static void BASPopulateHandles(qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceDiscoveryData);
static qbool_t IsBatteryLevelHandle(uint16_t Handle);
static qbool_t IsBatteryLevelPresentationFormatHandle(uint16_t Handle);
static qbool_t IsBASClientConfigurationHandle(uint16_t Handle);

/* Callback functions. */
void BAS_EventCallback(uint32_t BluetoothStackID, qapi_BLE_BAS_Event_Data_t *BAS_Event_Data, unsigned long CallbackParameter);
void BAS_GATT_Service_Discovery_EventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data, unsigned long CallbackParameter);
void BAS_GATT_Client_EventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data, unsigned long CallbackParameter);

/* Command list for the main BLE demo. */
const QCLI_Command_t BAS_CMD_List[] =
{
   /* cmd_function                        cmd_string                      usage_string                                         description */
   {cmd_BAS_RegisterService,              "RegisterService",              "",                                                   "Register BAS service."},
   {cmd_BAS_UnRegisterService,            "UnRegisterService",            "",                                                   "Unregister a BAS service."},
   {cmd_BAS_DiscoverBAS,                  "DiscoverBAS",                  "",                                                   "Discover BAS."},
   {cmd_BAS_ConfigureRemoteBAS,           "ConfigureRemoteBAS",           "[Battery Level Notification(0=disable,1=enable)] ",  "Configure Remote BAS."},
   {cmd_BAS_GetBatteryLevel,              "GetBatteryLevel",              "",                                                   "Get the battery level."},
   {cmd_BAS_SetBatteryLevel,              "SetBatteryLevel",              "[Level(0-100)]",                                     "Set the battery level."},
   {cmd_BAS_NotifyBatteryLevel,           "NotifyBatteryLevel",           "",                                                   "Notify Battery Level."},
   {cmd_BAS_GetBatteryPresentationFormat, "GetBatteryPresentationFormat", "",                                                   "Get Battery Presentation Format."},
   {cmd_BAS_SetBatteryPresentationFormat, "SetBatteryPresentationFormat", "[Namespace(0x00-0xFF)][Description(0x0000-0xFFFF)]", "Set Battery Presentation Format."},
};

static const QCLI_Command_Group_t BAS_CMD_Group = {"BAS", sizeof(BAS_CMD_List) / sizeof(QCLI_Command_t), BAS_CMD_List};

/**
   @brief Executes the "RegisterService" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_RegisterService(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                   Ret_Val;
   qapi_Status_t                           Result;
   uint32_t                                BluetoothStackID;
   uint32_t                                ConnectionID;

   BluetoothStackID = GetBluetoothStackID();
   ConnectionID     = GetActiveConnectionID();

   /* Check if the Bluetooth stack has been initialized. */
   if(BluetoothStackID)
   {
      /* Check if there is an exisiting connection. */
      if(!ConnectionID)
      {
         if(!(BAS_Demo_Context.InstanceID))
         {
            /* Available instance space is found, try to register the BAS
               service with it.*/
            Result = qapi_BLE_BAS_Initialize_Service(BluetoothStackID, BAS_EventCallback, 0, &(BAS_Demo_Context.InstanceID));

            if((Result > 0) && (BAS_Demo_Context.InstanceID))
            {
               /* Save the BAS instance ID. */
               BAS_Demo_Context.InstanceID = Result;

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS service has been registered successfully.\r\n");

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Instance ID: %d.\r\n", BAS_Demo_Context.InstanceID);

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to register BAS service.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS has already been regisered.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS service will be registered when there is no exisiting connection.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "UnRegisterService" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_UnRegisterService(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   uint32_t               BluetoothStackID;
   uint32_t               ConnectionID;
   Generic_Device_Info_t *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();

   /* Check if the Bluetooth stack has been initialized. */
   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID)
      {
         ConnectionID = GetActiveConnectionID();

         /* Disconnect the device if connected. */
         if(ConnectionID)
         {
            DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);

            if(DeviceInfo != NULL)
            {
               /* Try to disconnect remote device. */
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Disconnecting remote device...\r\n");

               Result = qapi_BLE_GAP_LE_Disconnect(BluetoothStackID, DeviceInfo->DeviceAddress);

               /* Inform the user the result of BLE operation. */
               QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_GAP_LE_Disconnect", Result);
            }
         }

         /* Unregister the specified BAS service. */
         Result = qapi_BLE_BAS_Cleanup_Service(BluetoothStackID, BAS_Demo_Context.InstanceID);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Cleanup_Service", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS service has been unregistered successfully.\r\n");

            /* Mark the BAS service is unregistered. */
            BAS_Demo_Context.InstanceID = 0;

            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to unregister BAS service.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* Invalid instance ID provided. */
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "The BAS service has not been registered.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "DiscoverBAS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_DiscoverBAS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   uint32_t               BluetoothStackID;
   uint32_t               ConnectionID;
   qapi_BLE_GATT_UUID_t   GATTUUID;
   Generic_Device_Info_t *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();
   ConnectionID     = GetActiveConnectionID();

   /* Check if the Bluetooth stack has been initialized. */
   if(BluetoothStackID)
   {
      /* Check if there is an exisiting connection. */
      if(ConnectionID)
      {
         DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);
         if(DeviceInfo != NULL)
         {
            if(!(DeviceInfo->Flags & DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING))
            {
               GATTUUID.UUID_Type = QAPI_BLE_GU_UUID_16_E;
               QAPI_BLE_BAS_ASSIGN_BAS_SERVICE_UUID_16(&(GATTUUID.UUID.UUID_16));

               Result = qapi_BLE_GATT_Start_Service_Discovery(BluetoothStackID, ConnectionID, 1, &GATTUUID, BAS_GATT_Service_Discovery_EventCallback, 0);

               /* Inform the user the result of BLE operation. */
               QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_GATT_Start_Service_Discovery", Result);

               if(Result == QAPI_OK)
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS service discovery request is sent successfully.\r\n");

                  DeviceInfo->Flags |= DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING;

                  Ret_Val = QCLI_STATUS_SUCCESS_E;
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to send BAS service discovery request.\r\n");

                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Another service discovery is in process.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to find the device info of the connected device.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "ConfigureRemoteBAS" command.

   Parameter_List[0] (0-2) is a flag indicates if the BAS service should be
                     enabled on remote device.
                     set.
                     0 = Disable
                     1 = Eabale

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_ConfigureRemoteBAS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t      Ret_Val;
   qapi_Status_t              Result;
   uint32_t                   BluetoothStackID;
   uint32_t                   ConnectionID;
   uint16_t                   NotifyEnable;
   qapi_BLE_NonAlignedWord_t  AttributeValue;
   Generic_Device_Info_t     *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();
   /* Check if the Bluetooth stack has been initialized. */
   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID == 0)
      {
         ConnectionID = GetActiveConnectionID();
         if(ConnectionID)
         {
            /* Try to find the device info. */
            DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);
            if(DeviceInfo != NULL)
            {
               /*The local device is the BAS client. */
               if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 1)))
               {
                  if(Parameter_List[0].Integer_Value == 0)
                  {
                     NotifyEnable = 0;
                  }
                  else
                  {
                     NotifyEnable = QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_NOTIFY_ENABLE;
                  }

                  /* Pack NotifyEnable into the attribute value. */
                  ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&AttributeValue, NotifyEnable);

                  if(BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration)
                  {
                     /* Send the configuration request via raw GATT write request. */
                     Result = qapi_BLE_GATT_Write_Request(BluetoothStackID, ConnectionID, BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration, sizeof(AttributeValue), &AttributeValue, BAS_GATT_Client_EventCallback, BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration);

                     if(Result)
                     {
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Configuration remote BAS request is sent successfully.\r\n");

                        Ret_Val = QCLI_STATUS_SUCCESS_E;
                     }
                     else
                     {
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to send configuration remote BAS request.\r\n");

                        Ret_Val = QCLI_STATUS_ERROR_E;
                     }
                  }
                  else
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS client info is not available.\r\n");

                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  Ret_Val = QCLI_STATUS_USAGE_E;
               }
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to find the device info of the connected device.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Local device is BAS server.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "GetBatteryLevel" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_GetBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   uint32_t               BluetoothStackID;
   uint32_t               ConnectionID;
   Generic_Device_Info_t *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();
   ConnectionID     = GetActiveConnectionID();

   /* Check if the Bluetooth stack has been initialized. */
   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID)
      {
         /* Local device is BAS server. */
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery Level: %d.\r\n", BAS_Demo_Context.BatteryLevel);

         Ret_Val = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         /* Local device is BAS client. */
         if(ConnectionID)
         {
            DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);
            if(DeviceInfo != NULL)
            {
               if(BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration)
               {
                  Result = qapi_BLE_GATT_Read_Value_Request(BluetoothStackID, ConnectionID, BAS_Demo_Context.BASClientInfo.Battery_Level, BAS_GATT_Client_EventCallback, BAS_Demo_Context.BASClientInfo.Battery_Level);

                  if(Result)
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Read remote BAS request is sent successfully.\r\n");

                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to send read remote BAS request.\r\n");

                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS client info is not available.\r\n");

                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to find the device info of the connected device.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetBatteryLevel" command.

   Parameter_List[0] (0-100) is the battery level.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_SetBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t Ret_Val;
   uint32_t              BluetoothStackID;

   BluetoothStackID = GetBluetoothStackID();

   if(BluetoothStackID)
   {
      if((Parameter_Count >= 1) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 100)))
      {
         if(BAS_Demo_Context.InstanceID)
         {
            /* Set the battery level. */
            BAS_Demo_Context.BatteryLevel = (uint8_t)(Parameter_List[0].Integer_Value);

            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery level is set on BAS server successfully.\r\n");
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery level could only be set on BAS server.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         Ret_Val = QCLI_STATUS_USAGE_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "NotifyBatteryLevel" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_NotifyBatteryLevel(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  Ret_Val;
   qapi_Status_t          Result;
   uint32_t               BluetoothStackID;
   uint32_t               ConnectionID;
   Generic_Device_Info_t *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();
   ConnectionID     = GetActiveConnectionID();

   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID)
      {
         if(ConnectionID)
         {
            DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);
            if(DeviceInfo != NULL)
            {
               if((BAS_Demo_Context.BASServerInfo.Battery_Level_Client_Configuration) & (QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_NOTIFY_ENABLE))
               {
                  Result = qapi_BLE_BAS_Notify_Battery_Level(BluetoothStackID, BAS_Demo_Context.InstanceID, ConnectionID, BAS_Demo_Context.BatteryLevel);

                  /* Inform the user the result of BLE operation. */
                  QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Notify_Battery_Level", Result);

                  if(Result == QAPI_OK)
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery level has been notified successfully.\r\n");
                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to notify battery level.\r\n");
                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS server info is not available.\r\n");

                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to find the device info of the connected device.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Only BAS server could notify battery level.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "GetBatteryPresentationFormat" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_GetBatteryPresentationFormat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                    Ret_Val;
   qapi_Status_t                            Result;
   uint32_t                                 BluetoothStackID;
   uint32_t                                 ConnectionID;
   qapi_BLE_BAS_Presentation_Format_Data_t  PresentationFormat;
   Generic_Device_Info_t                   *DeviceInfo;

   BluetoothStackID = GetBluetoothStackID();
   ConnectionID     = GetActiveConnectionID();

   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID)
      {
         /* The local device is BAS server. */
         Result = qapi_BLE_BAS_Query_Characteristic_Presentation_Format(BluetoothStackID, BAS_Demo_Context.InstanceID, &PresentationFormat);

         /* Inform the user the result of BLE operation. */
         QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Query_Characteristic_Presentation_Format", Result);

         if(Result == QAPI_OK)
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery level presentation format:\r\n");
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, " Format:      %d.\r\n", PresentationFormat.Format);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, " Exponent:    %d.\r\n", PresentationFormat.Exponent);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, " Unit:        %d.\r\n", PresentationFormat.Unit);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, " NameSpace:   0x%02X.\r\n", PresentationFormat.NameSpace);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, " Description: 0x%04X.\r\n", PresentationFormat.Description);
            Ret_Val = QCLI_STATUS_SUCCESS_E;
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to get battery presentation format.\r\n");
            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
      else
      {
         /* The local device is BAS client. */
         if(ConnectionID)
         {
            DeviceInfo = GetDeviceInfoByConnectionID(ConnectionID);
            if(DeviceInfo != NULL)
            {
               if(BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration)
               {
                  Result = qapi_BLE_GATT_Read_Value_Request(BluetoothStackID, ConnectionID, BAS_Demo_Context.BASClientInfo.Battery_Level_Presentation_Format, BAS_GATT_Client_EventCallback, BAS_Demo_Context.BASClientInfo.Battery_Level_Presentation_Format);

                  if(Result)
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Read remote BAS presentation format request is sent successfully.\r\n");

                     Ret_Val = QCLI_STATUS_SUCCESS_E;
                  }
                  else
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to send read remote BAS presentation format request.\r\n");

                     Ret_Val = QCLI_STATUS_ERROR_E;
                  }
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS client info is not available.\r\n");

                  Ret_Val = QCLI_STATUS_ERROR_E;
               }
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to find the device info of the connected device.\r\n");

               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "There is no connected remote device.\r\n");

            Ret_Val = QCLI_STATUS_ERROR_E;
         }
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Executes the "SetBatteryPresentationFormat" command.

   Parameter_List[0] (0x00-0xFF)     is the namespace.
   Parameter_List[1] (0x0000-0xFFFF) is the description.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E   indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E   indicates there is usage error associated with this
                            command.
*/
static QCLI_Command_Status_t cmd_BAS_SetBatteryPresentationFormat(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t                   Ret_Val;
   qapi_Status_t                           Result;
   uint32_t                                BluetoothStackID;
   qapi_BLE_BAS_Presentation_Format_Data_t PresentationFormat;

   BluetoothStackID = GetBluetoothStackID();

   if(BluetoothStackID)
   {
      if(BAS_Demo_Context.InstanceID)
      {
         if((Parameter_Count >= 2) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 0xFF)) && (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0,0xFFFF)))
         {
            PresentationFormat.Format      = 0;
            PresentationFormat.Exponent    = 0;
            PresentationFormat.Unit        = 0;
            PresentationFormat.NameSpace   = (uint8_t)(Parameter_List[0].Integer_Value);
            PresentationFormat.Description = (uint16_t)(Parameter_List[1].Integer_Value);

            Result = qapi_BLE_BAS_Set_Characteristic_Presentation_Format(BluetoothStackID, BAS_Demo_Context.InstanceID, &PresentationFormat);

            /* Inform the user the result of BLE operation. */
            QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Set_Characteristic_Presentation_Format", Result);

            if(Result == QAPI_OK)
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery presentation format has been set successfully.\r\n");

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Failed to set battery presentation format.\r\n");
               Ret_Val = QCLI_STATUS_ERROR_E;
            }
         }
         else
         {
            Ret_Val = QCLI_STATUS_USAGE_E;
         }
      }
      else
      {
         /* No valid Bluetooth Stack ID exists. */
         QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS client could not set battery presentation format on itself.\r\n");
         Ret_Val = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists. */
      QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BT stack has not been initialized.\r\n");
      Ret_Val = QCLI_STATUS_ERROR_E;
   }

   return(Ret_Val);
}

/**
   @brief Populate the BAS handle.

   @param ServiceDiscoveryData is the service discovery data.
*/
static void BASPopulateHandles(qapi_BLE_GATT_Service_Discovery_Indication_Data_t *ServiceDiscoveryData)
{
   uint32_t                                               Index1;
   uint32_t                                               Index2;
   qapi_BLE_GATT_Characteristic_Information_t            *CurrentCharacteristic;
   qapi_BLE_GATT_Characteristic_Descriptor_Information_t *CurrentDescriptor;

   /* Verify that the input parameters are semi-valid.                  */
   if((ServiceDiscoveryData) && (ServiceDiscoveryData->ServiceInformation.UUID.UUID_Type == QAPI_BLE_GU_UUID_16_E) && (QAPI_BLE_BAS_COMPARE_BAS_SERVICE_UUID_TO_UUID_16(ServiceDiscoveryData->ServiceInformation.UUID.UUID.UUID_16)))
   {
      /* Loop through all characteristics discovered in the service     */
      /* and populate the correct entry.                                */
      CurrentCharacteristic = ServiceDiscoveryData->CharacteristicInformationList;
      if(CurrentCharacteristic)
      {
         for(Index1 = 0; Index1 < ServiceDiscoveryData->NumberOfCharacteristics; Index1++, CurrentCharacteristic++)
         {
            if(QAPI_BLE_BAS_COMPARE_BATTERY_LEVEL_UUID_TO_UUID_16(CurrentCharacteristic->Characteristic_UUID.UUID.UUID_16))
            {
               /* All BAS UUIDs are defined to be 16 bit UUIDs.         */
               if(CurrentCharacteristic->Characteristic_UUID.UUID_Type == QAPI_BLE_GU_UUID_16_E)
               {
                  BAS_Demo_Context.BASClientInfo.Battery_Level = CurrentCharacteristic->Characteristic_Handle;

                  /* Loop through the Descriptor List.                  */
                  CurrentDescriptor = CurrentCharacteristic->DescriptorList;
                  for(Index2 = 0; Index2 < CurrentCharacteristic->NumberOfDescriptors; Index2++)
                  {
                     if(CurrentDescriptor->Characteristic_Descriptor_UUID.UUID_Type == QAPI_BLE_GU_UUID_16_E)
                     {
                        if(QAPI_BLE_GATT_COMPARE_CLIENT_CHARACTERISTIC_CONFIGURATION_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(CurrentCharacteristic->DescriptorList[Index2].Characteristic_Descriptor_UUID.UUID.UUID_16))
                        {
                           BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration = CurrentCharacteristic->DescriptorList[Index2].Characteristic_Descriptor_Handle;
                        }
                        else
                        {
                           if(QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_PRESENTATION_FORMAT_ATTRIBUTE_TYPE_TO_UUID_16(CurrentCharacteristic->DescriptorList[Index2].Characteristic_Descriptor_UUID.UUID.UUID_16))
                           {
                              BAS_Demo_Context.BASClientInfo.Battery_Level_Presentation_Format = CurrentCharacteristic->DescriptorList[Index2].Characteristic_Descriptor_Handle;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

/**
   @brief Veirfy if the received handle is battery level.

   @param Handle is the recevied handle.

   @return
    - true  indicates the handle is battery level.
    - false indicates the handle is not battery level.
*/
static qbool_t IsBatteryLevelHandle(uint16_t Handle)
{
   qbool_t Ret_Val;

   if(Handle == BAS_Demo_Context.BASClientInfo.Battery_Level)
   {
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Veirfy if the received handle is presentation format.

   @param Handle is the recevied handle.

   @return
    - true  indicates the handle is presentation format.
    - false indicates the handle is not presentation format.
*/
static qbool_t IsBatteryLevelPresentationFormatHandle(uint16_t Handle)
{
   qbool_t Ret_Val;

   if(Handle == BAS_Demo_Context.BASClientInfo.Battery_Level_Presentation_Format)
   {
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Veirfy if the received handle is configuration handle.

   @param Handle is the recevied handle.

   @return
    - true  indicates the handle is configuration handle.
    - false indicates the handle is not configuration handle.
*/
static qbool_t IsBASClientConfigurationHandle(uint16_t Handle)
{
   qbool_t Ret_Val;

   if(Handle == BAS_Demo_Context.BASClientInfo.Battery_Level_Client_Configuration)
   {
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}


/**
   @brief BAS event callbcak.

   @param BluetoothStackID  is the Bluetooth stack ID.
   @param BAS_Event_Data    is the event data.
   @param CallbackParameter is the callback parameter.

*/
void BAS_EventCallback(uint32_t BluetoothStackID, qapi_BLE_BAS_Event_Data_t *BAS_Event_Data, unsigned long CallbackParameter)
{
   qapi_Status_t          Result;
   BoardStr_t             BoardStr;
   uint32_t               InstanceID;
   uint32_t               TransactionID;
   uint32_t               ConnectionID;
   Generic_Device_Info_t *DeviceInfo;

   /* Verify that all parameters to this callback are Semi-Valid.       */
   if((BluetoothStackID == GetBluetoothStackID()) && (BAS_Event_Data))
   {
      ConnectionID = GetActiveConnectionID();
      DeviceInfo   = GetDeviceInfoByConnectionID(ConnectionID);

      if(DeviceInfo != NULL)
      {
         switch(BAS_Event_Data->Event_Data_Type)
         {
            case QAPI_BLE_ET_BAS_SERVER_READ_CLIENT_CONFIGURATION_REQUEST_E:
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS Server Read Client Configuration Request with size: %d.\r\n", BAS_Event_Data->Event_Data_Size);

               if(BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data)
               {
                  BD_ADDRToStr(BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->RemoteDevice, BoardStr);
                  InstanceID = BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->InstanceID;

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Instance ID:      %u.\r\n", InstanceID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection ID:    %u.\r\n", BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->ConnectionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Transaction ID:   %u.\r\n", BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->TransactionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection Type:  %s.\r\n", ((BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR"));
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Remote Device:    %s.\r\n", BoardStr);

                  switch(BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->ClientConfigurationType)
                  {
                     case QAPI_BLE_CT_BATTERY_LEVEL_E:
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Config Type: ctBatteryLevel.\r\n");
                        Result = qapi_BLE_BAS_Read_Client_Configuration_Response(BluetoothStackID, InstanceID, BAS_Event_Data->Event_Data.BAS_Read_Client_Configuration_Data->TransactionID, BAS_Demo_Context.BASServerInfo.Battery_Level_Client_Configuration);

                        /* Inform the user the result of BLE operation. */
                        QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Read_Client_Configuration_Response", Result);
                        break;

                     default:
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Config Type: Unknown.\n");
                        break;
                  }

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               }
               break;

            case QAPI_BLE_ET_BAS_SERVER_CLIENT_CONFIGURATION_UPDATE_E:
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS Server Client Configuration Update with size %d.\r\n", BAS_Event_Data->Event_Data_Size);

               if(BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data)
               {
                  BD_ADDRToStr(BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->RemoteDevice, BoardStr);
                  InstanceID = BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->InstanceID;

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Instance ID:      %u.\r\n", InstanceID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection ID:    %u.\r\n", BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->ConnectionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection Type:  %s.\r\n", ((BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR"));
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Remote Device:    %s.\r\n", BoardStr);

                  switch(BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->ClientConfigurationType)
                  {
                     case QAPI_BLE_CT_BATTERY_LEVEL_E:
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Config Type: ctBatteryLevel.\r\n");
                        if(BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->Notify)
                        {
                           BAS_Demo_Context.BASServerInfo.Battery_Level_Client_Configuration |= QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_NOTIFY_ENABLE;
                        }
                        else
                        {
                           BAS_Demo_Context.BASServerInfo.Battery_Level_Client_Configuration &= ~QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_NOTIFY_ENABLE;
                        }
                        break;

                     default:
                        QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Config Type: Unknown.\r\n");
                        break;
                  }

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Value: 0x%04X.\n", (uint16_t)BAS_Event_Data->Event_Data.BAS_Client_Configuration_Update_Data->Notify);

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               }
               break;

            case QAPI_BLE_ET_BAS_SERVER_READ_BATTERY_LEVEL_REQUEST_E:
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS Server Read Battery Level Request Event received.\r\n");

               InstanceID    = BAS_Event_Data->Event_Data.BAS_Read_Battery_Level_Data->InstanceID;
               TransactionID = BAS_Event_Data->Event_Data.BAS_Read_Battery_Level_Data->TransactionID;

               Result = qapi_BLE_BAS_Battery_Level_Read_Request_Response(BluetoothStackID, TransactionID, BAS_Demo_Context.BatteryLevel);

               /* Inform the user the result of BLE operation. */
               QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Battery_Level_Read_Request_Response", Result);

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               break;

            default:
               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Unknown BAS Event.\r\n");

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               break;
         }
      }
   }
}

/**
   @brief GATT service discovery callback function for BAS.

   @param BluetoothStackID                  is the Bluetooth stack ID.
   @param GATT_Service_Discovery_Event_Data is the event data.
   @param CallbackParameter                 is the callback parameter.

*/
void BAS_GATT_Service_Discovery_EventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data, unsigned long CallbackParameter)
{
   Generic_Device_Info_t *DeviceInfo;
   uint32_t               ConnectionID;
   uint8_t                Status;

   if((BluetoothStackID == GetBluetoothStackID()) && (GATT_Service_Discovery_Event_Data))
   {
      ConnectionID = GetActiveConnectionID();
      DeviceInfo   = GetDeviceInfoByConnectionID(ConnectionID);

      if(DeviceInfo != NULL)
      {
         switch(GATT_Service_Discovery_Event_Data->Event_Data_Type)
         {
          case QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E:
               /* Verify the event data.                                */
               if(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data)
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Service 0x%04X - 0x%04X, UUID: ", GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.Service_Handle, GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.End_Group_Handle);
                  DisplayUUID(BAS_Demo_Context.QCLI_Handle, &(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data->ServiceInformation.UUID));

                  /* Attempt to populate BAS handles.                   */
                  BASPopulateHandles(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Indication_Data);

                  /* Flag that no service discovery operation is        */
                  /* outstanding for this device.                       */
                  DeviceInfo->Flags &= ~DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING;
               }
               break;

            case QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E:
               /* Verify the event data.                                */
               if(GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Complete_Data)
               {
                  Status = GATT_Service_Discovery_Event_Data->Event_Data.GATT_Service_Discovery_Complete_Data->Status;

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Service Discovery Operation Complete, Status 0x%02X.\r\n", Status);

                  if(Status == QAPI_OK)
                  {
                     /* Mark the device supports BAS. */
                     DeviceInfo->GATTProfileFlags |= SUPPORTED_GATT_PROFILE_BAS;
                  }

                  /* Flag that no service discovery operation is        */
                  /* outstanding for this device.                       */
                  DeviceInfo->Flags &= ~DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING;
               }
               break;

          default:
             QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Unhandled GATT service discovery type: %d.\r\n", GATT_Service_Discovery_Event_Data->Event_Data_Type);
             break;
         }
      }
   }
}

/**
   @brief BAS GATT service discovery callback function.

   @param BluetoothStackID       is the Bluetooth stack ID.
   @param GATT_Client_Event_Data is the event data.
   @param CallbackParameter      is the callback parameter.

*/
void BAS_GATT_Client_EventCallback(uint32_t BluetoothStackID, qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data, unsigned long CallbackParameter)
{
   qapi_Status_t                            Result;
   uint32_t                                 ConnectionID;
   uint8_t                                  BatteryLevel;
   uint16_t                                 ValueLength;
   BoardStr_t                               BoardStr;
   Generic_Device_Info_t                   *DeviceInfo;
   qapi_BLE_BAS_Presentation_Format_Data_t  BatteryLevelFormatData;

   /* Verify this is the callback function to BAS demo. */
   if((BluetoothStackID == GetBluetoothStackID()) && (GATT_Client_Event_Data))
   {
      ConnectionID = GetActiveConnectionID();
      DeviceInfo   = GetDeviceInfoByConnectionID(ConnectionID);

      if(DeviceInfo != NULL)
      {
         /* Determine the event that occurred.                             */
         switch(GATT_Client_Event_Data->Event_Data_Type)
         {
            case QAPI_BLE_ET_GATT_CLIENT_READ_RESPONSE_E:
               if(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data)
               {
                  BD_ADDRToStr(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->RemoteDevice, BoardStr);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS Read Response.\r\n");
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection ID:   %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->ConnectionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Transaction ID:  %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->TransactionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection Type: %s.\r\n", (GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR");
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BD_ADDR:         %s.\r\n", BoardStr);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Data Length:     %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength);

                  /* If we know about this device and a callback parameter */
                  /* exists, then check if we know what read response this */
                  /* is.                                                   */
                  ValueLength = GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength;
                  if(ValueLength != 0)
                  {
                     if(IsBatteryLevelHandle((uint16_t)CallbackParameter))
                     {
                        if(ValueLength == QAPI_BLE_BAS_BATTERY_LEVEL_VALUE_LENGTH)
                        {
                           BatteryLevel = GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValue[0];
                           if(BatteryLevel <= QAPI_BLE_BAS_BATTERY_LEVEL_MAX_VALUE)
                           {
                              QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery Level: %u%%.\r\n", (uint16_t)BatteryLevel);
                           }
                           else
                           {
                              QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery Level has been corrupted.\r\n", BatteryLevel);
                           }
                        }
                        else
                        {
                           QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid length for Battery Level response.\r\n", ValueLength);
                        }
                     }
                     else
                     {
                        if(IsBatteryLevelPresentationFormatHandle((uint16_t)CallbackParameter))
                        {
                           if(ValueLength == QAPI_BLE_BAS_PRESENTATION_FORMAT_SIZE)
                           {
                              Result = qapi_BLE_BAS_Decode_Characteristic_Presentation_Format(GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValueLength, GATT_Client_Event_Data->Event_Data.GATT_Read_Response_Data->AttributeValue, &BatteryLevelFormatData);

                              /* Inform the user the result of BLE operation. */
                              QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Decode_Characteristic_Presentation_Format", Result);

                              if(Result == QAPI_OK)
                              {
                                 QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Format: %u.\r\n",      BatteryLevelFormatData.Format);
                                 QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Exponent: %u.\r\n",    BatteryLevelFormatData.Exponent);
                                 QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Unit: %u.\r\n",        BatteryLevelFormatData.Unit);
                                 QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "NameSpace: %u.\r\n",   BatteryLevelFormatData.NameSpace);
                                 QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Description: %u.\r\n", BatteryLevelFormatData.Description);
                              }
                           }
                           else
                           {
                              QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid length for Battery Level Presentation Format response.\r\n");
                           }
                        }
                        else
                        {
                           QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Could not find matching descriptor.\r\n");
                        }
                     }
                  }
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid BAS client read response Data.\r\n");
               }

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               break;

            case QAPI_BLE_ET_GATT_CLIENT_WRITE_RESPONSE_E:
               if(GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data)
               {
                  BD_ADDRToStr(GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data->RemoteDevice, BoardStr);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BAS Write Response:\r\n");
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection ID:   %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data->ConnectionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Transaction ID:  %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data->TransactionID);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Connection Type: %s.\r\n", (GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data->ConnectionType == QAPI_BLE_GCT_LE_E)?"LE":"BR/EDR");
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "BD_ADDR:         %s.\r\n", BoardStr);
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Bytes Written:   %u.\r\n", GATT_Client_Event_Data->Event_Data.GATT_Write_Response_Data->BytesWritten);

                  if(IsBASClientConfigurationHandle((uint16_t)CallbackParameter))
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Write Battery Level CC Compete.\r\n");
                  }
                  else
                  {
                     QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid BAS client configuration handle.\r\n");
                  }
               }
               else
               {
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid BAS write response data.\r\n");
               }

               QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               break;

            default:
                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Unhandled BAS client event %d.\r\n", GATT_Client_Event_Data->Event_Data_Type);

                  QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "\r\n");
               break;
         }
      }
   }
}

/**
   @brief Initializes the BAS demo application.

   @param[in] BLE_QCLI_Handle is the parent QCLI handle for the BAS demo.
*/
qbool_t Initialize_BAS_Demo(QCLI_Group_Handle_t BLE_QCLI_Handle)
{
   qbool_t Ret_Val;

   /* Register BAS command group. */
   BAS_Demo_Context.QCLI_Handle = QCLI_Register_Command_Group(BLE_QCLI_Handle, &BAS_CMD_Group);
   if(BAS_Demo_Context.QCLI_Handle != NULL)
   {
      Ret_Val = true;
   }
   else
   {
      QCLI_Printf(BLE_QCLI_Handle, "Failed to register BAS command group.\n");
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Initializes the BAS demo application.

   @param[in] BLE_QCLI_Handle is the parent QCLI handle for the BAS demo.
*/
void Cleanup_BAS_Demo(void)
{
   qapi_Status_t Result;

   if(BAS_Demo_Context.InstanceID)
   {
      /*Unregister the BAS service. */
      Result = qapi_BLE_BAS_Cleanup_Service(GetBluetoothStackID(), BAS_Demo_Context.InstanceID);

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Cleanup_Service", Result);

      BAS_Demo_Context.InstanceID = 0;
   }

   QCLI_Unregister_Command_Group(BAS_Demo_Context.QCLI_Handle);
}

/**
   @brief Frees any resources allocated that aren't valid when stack is shutdown
          without shutting down the QCLI interface for the BAS demo.
*/
void Shutdown_BAS_Demo(void)
{
   qapi_Status_t Result;

   if(BAS_Demo_Context.InstanceID)
   {
      /*Unregister the BAS service. */
      Result = qapi_BLE_BAS_Cleanup_Service(GetBluetoothStackID(), BAS_Demo_Context.InstanceID);

      /* Inform the user the result of BLE operation. */
      QCLI_Display_Function_Status(BAS_Demo_Context.QCLI_Handle, "qapi_BLE_BAS_Cleanup_Service", Result);

      BAS_Demo_Context.InstanceID = 0;
   }
}

/**
   @brief Handle the bas notification event.

   @param[in] GATT_Server_Notification_Data is the notitication data.
*/
void Handle_BAS_Notification(qapi_BLE_GATT_Server_Notification_Data_t *GATT_Server_Notification_Data)
{
   BoardStr_t BoardStr;

   if(GATT_Server_Notification_Data != NULL)
   {
      if(GATT_Server_Notification_Data->AttributeHandle == BAS_Demo_Context.BASClientInfo.Battery_Level)
      {
         if(GATT_Server_Notification_Data->AttributeValueLength >= (uint16_t)(QAPI_BLE_BAS_BATTERY_LEVEL_VALUE_LENGTH))
         {
            BD_ADDRToStr(GATT_Server_Notification_Data->RemoteDevice, BoardStr);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery level notification from: %s.\r\n", BoardStr);
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Battery Level:  %u%%.\n", *(GATT_Server_Notification_Data->AttributeValue));
         }
         else
         {
            QCLI_Printf(BAS_Demo_Context.QCLI_Handle, "Invalid battery level notification data.\r\n");
         }
      }
   }
}

