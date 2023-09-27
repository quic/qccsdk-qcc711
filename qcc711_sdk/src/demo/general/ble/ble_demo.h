/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __BLE_DEMO_H__
#define __BLE_DEMO_H__

#include "qcli_api.h"
#include "qapi_ble_hcitypes.h"
#include "qapi_ble_gap.h"
#include "qapi_ble_gatt.h"

/* User to represent a structure to hold a BD_ADDR return from BD_ADDRToStr. */
typedef char BoardStr_t[16];

/* Flags for device state. */
#define DEVICE_INFO_FLAGS_LTK_VALID                         0x01
#define DEVICE_INFO_FLAGS_SPPLE_SERVER                      0x02
#define DEVICE_INFO_FLAGS_SPPLE_CLIENT                      0x04
#define DEVICE_INFO_FLAGS_SERVICE_DISCOVERY_OUTSTANDING     0x08

/* Flags for the supported GATT profiles on a device. */
#define SUPPORTED_GATT_PROFILE_BAS                          0x01

/* Structure represents the information will be stored on a Discovered GAP */
/* Service. */
typedef struct _tagGAPS_Client_Info_t
{
   uint16_t DeviceNameHandle;
   uint16_t DeviceAppearanceHandle;
} GAPS_Client_Info_t;

/* Structure represents the information will be stored on a discovered custom */
/* service. */
typedef struct _tagCustom_Client_Info_t
{
   uint16_t ReadHandle;
} Custom_Client_Info_t;

/* Structure represnets generic device info. */
typedef struct Generic_Device_Info_s
{
   uint8_t                         Flags;               /* Flags indicate the current states of device. */
   uint8_t                         GATTProfileFlags;    /* Flags indicate the supporited GATT profiles on device. */
   uint32_t                        ConnectionID;        /* The ID of the connection with a remote device. */
   qbool_t                         LocalDeviceIsMaster; /* Flag indicates if the local device is master. */
   qapi_BLE_GAP_LE_Address_Type_t  DeviceAddressType;   /* The address type of the remote device. */
   qapi_BLE_BD_ADDR_t              DeviceAddress;       /* The address of the remote device. */
   GAPS_Client_Info_t              GAPSClientInfo;      /* GAPS client info. */
   Custom_Client_Info_t            CustomClientInfo;    /* Custom client info. */
   uint8_t                         EncryptionKeySize;
   qapi_BLE_Long_Term_Key_t        LTK;
   qapi_BLE_Encryption_Key_t       IRK;
   qapi_BLE_Random_Number_t        Rand;
   uint16_t                        EDIV;
   struct Generic_Device_Info_s   *NextDevice;
}  Generic_Device_Info_t;

/**
   @brief Initializes the BLE demo application.

   @param[in] HCI_DriverInformation  HCI driver information for inititializing
                                     the bluetooth stack.
*/
void Initialize_BLE_Demo(qapi_BLE_HCI_DriverInformation_t *HCI_DriverInformation);

/**
   @brief Cleans up resources used by the BLE demo application.
*/
void Cleanup_BLE_Demo(void);

/**
   @brief Converts the bluetooth address in QAPI format to string format.

   @param Board_Address is the BD address in QAPI format.
   @param BoardStr      is the converted BD address in string format.
*/
void BD_ADDRToStr(qapi_BLE_BD_ADDR_t Board_Address, BoardStr_t BoardStr);

/**
   @brief Converts the bluetooth address in string format to QAPI format.

   @param BoardStr      is the BD address in string format.
   @param Board_Address is the converted BD address in QAPI format.
*/
void StrToBD_ADDR(char *BoardStr, qapi_BLE_BD_ADDR_t *Board_Address);

/**
   @brief Function to get the QCLI handle for the BLE demo.

   @return The QCLI handled used by the BLE demo.
*/
QCLI_Group_Handle_t GetBLEQCLIHandle(void);

/**
   @brief Function to get Bluetooth stack ID.

   @return Bluetooth stack ID.
*/
uint32_t GetBluetoothStackID(void);

/**
   @brief Function to get the ID of the current connection.

   @return The ID of the current connection.
*/
uint32_t GetActiveConnectionID(void);

/**
   @brief Function to get the BDADDR of the currently connected device.

   @return The BDADDR of the currently connected device.
*/
qapi_BLE_BD_ADDR_t GetActiveConnectionBDADDR(void);

/**
   @brief Function to get the device info by conncetion ID.

   @return The pointer to device info or NULL.
*/
Generic_Device_Info_t *GetDeviceInfoByConnectionID(uint32_t ConnectionID);

/**
   @brief Function to get the device info by BD_ADDR.

   @return The pointer to device info or NULL.
*/
Generic_Device_Info_t *GetDeviceInfoByBDADDR(qapi_BLE_BD_ADDR_t BDADDR);

/**
   @brief Function to display the received UUID.

   @return The pointer to device info or NULL.
*/
void DisplayUUID(QCLI_Group_Handle_t QCLI_Handle, qapi_BLE_GATT_UUID_t *UUID);

#endif

