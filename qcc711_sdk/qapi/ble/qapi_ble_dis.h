/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_dis.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Device Information Service
 * (GATT based) API Type Definitions, Constants, and
 * Prototypes.
 *
 * @details
 * The Device Information Service (DIS) programming interface
 * defines the protocols and procedures to be used to implement
 * DIS capabilities for both Server and Client services.
 */

#ifndef __QAPI_BLE_DIS_H__
#define __QAPI_BLE_DIS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gatt.h"      /* QAPI GATT prototypes.                    */
#include "./qapi_ble_distypes.h"  /* QAPI DIS prototypes.                     */

/** @addtogroup qapi_ble_services_dis
@{ */

   /* Error Return Codes.                                               */

   /* Error Codes that are smaller than these (less than -1000) are     */
   /* related to the Bluetooth Protocol Stack itself (see               */
   /* qapi_ble_errors.H).                                               */

/** Invalid parameter. */
#define QAPI_BLE_DIS_ERROR_INVALID_PARAMETER                      (-1000)

/** Insufficient resources. */
#define QAPI_BLE_DIS_ERROR_INSUFFICIENT_RESOURCES                 (-1001)

/** Service is already registered. */
#define QAPI_BLE_DIS_ERROR_SERVICE_ALREADY_REGISTERED             (-1003)

/** Invalid instance ID. */
#define QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID                    (-1004)

/** Malformatted data. */
#define QAPI_BLE_DIS_ERROR_MALFORMATTED_DATA                      (-1005)

/** Unknown error. */
#define QAPI_BLE_DIS_ERROR_UNKNOWN_ERROR                          (-1006)


   /* The following controls the maximum length of a static string.     */

/** Maximum support DIS string length. */
#define QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING                     (248)


/**
 * Structure that represents all the data contained in the DIS PNP ID
 * value.
 */
typedef struct qapi_BLE_DIS_PNP_ID_Data_s
{
   /**
    * Vendor ID source.
    *
    * Valid values have the form QAPI_BLE_DIS_PNP_ID_VENDOR_SOURCE_XXX
    * and can be found in qapi_ble_distypes.h.
    */
   uint8_t  VendorID_Source;

   /**
    * Vendor ID.
    */
   uint16_t VendorID;

   /**
    * Product ID.
    */
   uint16_t ProductID;

   /**
    * Product version.
    */
   uint16_t ProductVersion;
} qapi_BLE_DIS_PNP_ID_Data_t;

/** Size of the #qapi_BLE_DIS_PNP_ID_Data_t structure. */
#define QAPI_BLE_DIS_PNP_ID_DATA_SIZE                             (sizeof(qapi_BLE_DIS_PNP_ID_Data_t))

   /* DIS Server API.                                                   */

/**
 * @brief
 * Opens a DIS server on a specified Bluetooth Stack.
 *
 * @details
 * Only one DIS server may be open at a time, per the Bluetooth Stack ID.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_DIS_Initialize_Service().
 *
 * @param[out]  ServiceID           Unique GATT service ID of the
 *                                  registered DIS service returned from the
 *                                  qapi_BLE_GATT_Register_Service() API.
 *
 * @return
 * Positive, nonzero -- If successful. The return value will
 *              be the Service Instance ID of DIS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_DIS_ERROR_MAXIMUM_NUMBER_OF_INSTANCES_REACHED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Initialize_Service(uint32_t BluetoothStackID, uint32_t *ServiceID);

/**
 * @brief
 * Opens a DIS server on a specified Bluetooth Stack with
 * the ability to control the location of the service in the GATT database.
 *
 * @details
 * Only one DIS server may be open at a time, per the Bluetooth Stack ID.
 *
 * @param[in]      BluetoothStackID      Unique identifier assigned to
 *                                       this Bluetooth Protocol Stack
 *                                       via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[out]     ServiceID             Unique GATT Service ID of the
 *                                       registered service returned
 *                                       from
 *                                       qapi_BLE_GATT_Register_Service()
 *                                       API.
 *
 * @param[in,out]  ServiceHandleRange    Pointer to a Service Handle
 *                                       Range structure that, on input,
 *                                       can be used to control the
 *                                       location of the service in the
 *                                       GATT databasee, and on output,
 *                                       returns the handle range that
 *                                       the service is using in the GATT
 *                                       databasee.
 *
 * @return
 * Positive, nonzero -- If successful. The return value will
 *              be the Service Instance ID of DIS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_DIS_ERROR_MAXIMUM_NUMBER_OF_INSTANCES_REACHED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with a Device Information Service Instance.
 *
 * @details
 * After this function is called, no other Device Information Service
 * function can be called until after a successful call to the
 * qapi_BLE_DIS_Initialize_Service() function is performed.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queryies the number of attributes
 * that are contained in the DIS service that is registered with a
 * call to qapi_BLE_DIS_Initialize_Service() or
 * qapi_BLE_DIS_Initialize_Service_Handle_Range().
 *
 * @return
 * Positive, nonzero number -- Of attributes that would be
 *           registered by a DIS service instance.\n
 * Zero -- On failure.
 */
QAPI_BLE_DECLARATION uint32_t QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Number_Attributes(void);

/**
 * @brief
 * Sets the Manufacturer Name
 * characteristic on the specified Device Information Service instance.
 *
 * @details
 * The Manufacturer Name parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  ManufacturerName    Value to be entered as the
 *                                 Manufacturer Name for the specified
 *                                 DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Manufacturer_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName);

/**
 * @brief
 * Queries the current Manufacturer
 * Name characteristic value on the specified DIS instance.
 *
 * @details
 * The Manufacturer Name parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  ManufacturerName    Pointer to return the current
 *                                  Manufacturer Name for the specified
 *                                  DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Manufacturer_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *ManufacturerName);

/**
 * @brief
 * Sets the Model Number characteristic
 * on the specified Device Information Service instance.
 *
 * @details
 * The Model Number parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  ModelNumber         Value to be entered as the Model
 *                                 Number for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Model_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber);

/**
 * @brief
 * Queries the current Model Number
 * characteristic value on the specified DIS instance.
 *
 * @details
 * The Model Number parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  ModelNumber         Pointer to return the current Model
 *                                  Number for the specified DIS
 *                                  Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Model_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *ModelNumber);

/**
 * @brief
 * Sets the Serial Number characteristic
 * on the specified Device Information Service instance.
 *
 * @details
 * The Serial Number parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  SerialNumber        Value to be entered as the Serial
 *                                 Number for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Serial_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber);

/**
 * @brief
 * Queries the current Serial Number
 * characteristic value on the specified DIS instance.
 *
 * @details
 * The Serial Number parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  SerialNumber        Pointer to return the current
 *                                  Serial Number for the specified DIS
 *                                  Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Serial_Number(uint32_t BluetoothStackID, uint32_t InstanceID, char *SerialNumber);

/**
 * @brief
 * Sets the Hardware Revision characteristic
 * on the specified Device Information Service instance.
 *
 * @details
 * The Hardware_Revision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID           Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[in]  Hardware_Revision    Value to be entered as the
 *                                  Hardware Revision for the specified
 *                                  DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Hardware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision);

/**
 * @brief
 * Queries the current Hardware Revision
 * characteristic value on the specified DIS instance.
 *
 * @details
 * The Hardware_Revision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID     Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID           Service instance ID to close.
 *                                   This is the value that was returned
 *                                   from the qapi_BLE_DIS_Initialize_Service()
 *                                   function.
 *
 * @param[out]  Hardware_Revision    Pointer to return the current
 *                                   Hardware Revision for the specified
 *                                   DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Hardware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *Hardware_Revision);

/**
 * @brief
 * Sets the Firmware Revision
 * characteristic on the specified Device Information Service instance.
 *
 * @details
 * The FirmwareRevision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  FirmwareRevision    Value to be entered as the
 *                                 Firmware Revision for the specified
 *                                 DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Firmware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision);

/**
 * @brief
 * Queries the current Firmware Revision
 * characteristic value on the specified DIS instance.
 *
 * @details
 * The FirmwareRevision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  FirmwareRevision    Pointer to return the current
 *                                  Firmware Revision for the specified
 *                                  DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Firmware_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *FirmwareRevision);

/**
 * @brief
 * Sets the Software Revison
 * characteristic on the specified Device Information Service instance.
 *
 * @details
 * The SoftwareRevision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  SoftwareRevision    Value to be entered as the
 *                                 Software Revision for the specified
 *                                 DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_Software_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision);

/**
 * @brief
 * Queries the current Software Revision
 * characteristic value on the specified DIS instance.
 *
 * @details
 * The SoftwareRevision parameter must be a pointer to a NULL-terminated
 * ASCII string of at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING
 * (not counting the trailing NULL terminator) in length.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  SoftwareRevision    Pointer to return the current
 *                                  Software Revision for the specified
 *                                  DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_Software_Revision(uint32_t BluetoothStackID, uint32_t InstanceID, char *SoftwareRevision);

/**
 * @brief
 * Sets the System ID characteristic
 * on the specified Device Information Service instance.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  SystemID            Value to be entered as the System
 *                                 ID for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_System_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID);

/**
 * @brief
 * Queries the current System ID
 * characteristic value on the specified DIS instance.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  SystemID            Pointer to return the current
 *                                  System ID for the specified DIS
 *                                  Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_System_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_System_ID_Value_t *SystemID);

/**
 * @brief
 * Sets the IEEE Certificastion Data
 * characteristic on the specified Device Information Service instance.
 *
 * @details
 * The IEEE Certification Data parameter must be a pointer to a array of
 * at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING characters.
 *
 * @param[in]  BluetoothStackID           Unique identifier assigned to
 *                                        this Bluetooth Protocol Stack
 *                                        via a call to
 *                                        qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID                 Service instance ID to
 *                                        close. This is the value that
 *                                        was returned from the
 *                                        qapi_BLE_DIS_Initialize_Service()
 *                                        function.
 *
 * @param[in]  Length                     Length of the
 *                                        IEEE_Certification_Data.
 *
 * @param[in]  IEEE_Certification_Data    Value to be entered as the
 *                                        IEEE Certification data for the
 *                                        specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_IEEE_Certification_Data(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t Length, uint8_t *IEEE_Certification_Data);

/**
 * @brief
 * Queries the current IEEE Certification
 * Data characterisitc value on the specified DIS instance.
 *
 * @details
 * The IEEE Certification Data parameter must be a pointer to a array of
 * at most QAPI_BLE_DIS_MAXIMUM_SUPPORTED_STRING characters.
 *
 * @param[in]   BluetoothStackID           Unique identifier assigned to
 *                                         this Bluetooth Protocol Stack
 *                                         via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID                 Service instance ID to
 *                                         close. This is the value that
 *                                         was returned from the
 *                                         qapi_BLE_DIS_Initialize_Service()
 *                                         function.
 *
 * @param[out]  IEEE_Certification_Data    Pointer to return the
 *                                         current IEEE Certification for
 *                                         the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_IEEE_Certification_Data(uint32_t BluetoothStackID, uint32_t InstanceID, uint8_t *IEEE_Certification_Data);

/**
 * @brief
 * Sets the Plug and Play (PnP)
 * ID characteristic on the specified Device Information Service instance.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_DIS_Initialize_Service()
 *                                  function.
 *
 * @param[in]  PNP_ID_Data          Value to be entered as the PNP ID
 *                                  Data for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Set_PNP_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);

/**
 * @brief
 * Queries the current PnP ID Data
 * charctertisic value on the specified DIS instance.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_DIS_Initialize_Service()
 *                                 function.
 *
 * @param[out]  PNP_ID_Data        Pointer to return the current PNP
 *                                 ID Data for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_DIS_ERROR_INVALID_INSTANCE_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Query_PNP_ID(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);

   /* DIS Client API.                                                   */

/**
 * @brief
 * Parses a PnP ID value
 * received from a remote DIS server.
 *
 * @param[in]   ValueLength    Specifies the length of the Device
 *                             Information value returned by the remote
 *                             DIS server.
 *
 * @param[in]   Value          Value is a pointer to the Device
 *                             Information data returned by the remote
 *                             DIS server.
 *
 * @param[out]  PNP_ID_Data    Pointer to store the parsed PNP ID Data
 *                             for the specified DIS Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_DIS_ERROR_MALFORMATTED_DATA \n
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_DIS_Decode_PNP_ID(uint32_t ValueLength, uint8_t *Value, qapi_BLE_DIS_PNP_ID_Data_t *PNP_ID_Data);

/** @} */ /* end_addtogroup qapi_ble_services_dis */

#endif

