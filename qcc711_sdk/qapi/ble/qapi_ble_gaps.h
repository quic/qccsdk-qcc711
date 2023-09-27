/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_gaps.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Generic Access Profile
 * (GATT based) API Type Definitions, Constants, and
 * Prototypes.
 *
 * @details
 * The Generic Access Profile Service programming interface
 * defines the protocols and procedures to be used to
 * implement Generic Access Profile Service capabilities.
 */

#ifndef __QAPI_BLE_GAPS_H__
#define __QAPI_BLE_GAPS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gatt.h"      /* qapi GATT prototypes.                    */
#include "./qapi_ble_gapstypes.h" /* QAPI GAPS prototypes.                    */

/** @addtogroup qapi_ble_services_gaps
@{ */

   /* Error Return Codes. */

   /* Error Codes that are smaller than these (less than -1000) are */
   /* related to the Bluetooth Protocol Stack itself (see */
   /* qapi_ble_errors.h). */

/** Invalid parameter. */
#define QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER                     (-1000)

/** Invalid Bluetooth Stack ID. */
#define QAPI_BLE_GAPS_ERROR_INVALID_BLUETOOTH_STACK_ID            (-1001)

/** Invalid resources. */
#define QAPI_BLE_GAPS_ERROR_INSUFFICIENT_RESOURCES                (-1002)

/** Service is already registered. */
#define QAPI_BLE_GAPS_ERROR_SERVICE_ALREADY_REGISTERED            (-1003)

/** Invalid instance ID. */
#define QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID                   (-1004)

/** Malformatted data. */
#define QAPI_BLE_GAPS_ERROR_MALFORMATTED_DATA                     (-1005)

/** Unknown error. */
#define QAPI_BLE_GAPS_ERROR_UNKNOWN_ERROR                         (-1006)

/**
 * Structure that represents the Peripheral Preferred Connection
 * Parameters. This is used to inform a remote Master device of the
 * local device's preferred connection parameters.
 *
 * With the exception of the Slave_Latency member, which is specified
 * in Connection Events, all other members of this structure are
 * specified in milliseconds.
 *
 * With the exception of the Slave_Latency member, all other members may
 * be set to
 * QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_NO_
 * SPECIFIC_PREFERRED to indicate that the local device does not have
 * any preference for the specified parameter.
 *
 * The Minimum_Connection_Interval must satisfy the
 * following equation (with definitions from qapi_ble_gap.h):
 *
 *   Connection_Interval_Min >=
 *         #QAPI_BLE_MINIMUM_MINIMUM_CONNECTION_INTERVAL \n
 *   AND \n
 *   Connection_Interval_Min <=
 *         #QAPI_BLE_MAXIMUM_MINIMUM_CONNECTION_INTERVAL \n
 *   OR \n
 *   Connection_Interval_Min ==
 * QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_
 * NO_SPECIFIC_PREFERRED
 *
 * The Maximum_Connection_Interval must satisfy the
 * following equation (with definitions from qapi_ble_gap.h).
 *
 *   Connection_Interval_Max >=
 *         #QAPI_BLE_MINIMUM_MAXIMUM_CONNECTION_INTERVAL \n
 *   AND \n
 *   Connection_Interval_Max <=
 *         #QAPI_BLE_MAXIMUM_MAXIMUM_CONNECTION_INTERVAL \n
 *   OR \n
 *          Connection_Interval_Max ==
 * QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_
 * NO_SPECIFIC_PREFERRED
 *
 * The Slave_Latency must satisfy the following equation
 * (with definitions from qapi_ble_gap.h):
 *
 *   Slave_Latency >=
 *         #QAPI_BLE_MINIMUM_SLAVE_LATENCY \n
 *   AND \n
 *   Slave_Latency <=
 *         #QAPI_BLE_MAXIMUM_SLAVE_LATENCY
 *
 * The Supervision_Timeout must satisfy the following
 * equation (with definitions from qapi_ble_gap.h):
 *
 *   Supervision_Timeout >=
 *         #QAPI_BLE_MINIMUM_LINK_SUPERVISION_TIMEOUT \n
 *   AND \n
 *   Supervision_Timeout <=
 *         #QAPI_BLE_MAXIMUM_LINK_SUPERVISION_TIMEOUT \n
 *   OR \n
 *   Supervision_Timeout ==
 * QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_
 * NO_SPECIFIC_PREFERRED
 */
typedef struct qapi_BLE_GAP_Preferred_Connection_Parameters_s
{
   /**
    * Minimum connection interval.
    */
   uint16_t Minimum_Connection_Interval;

   /**
    * Maximum connection interval.
    */
   uint16_t Maximum_Connection_Interval;

   /**
    * Slave latency.
    */
   uint16_t Slave_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t Supervision_Timeout;
} qapi_BLE_GAP_Preferred_Connection_Parameters_t;

/** Size of the #qapi_BLE_GAP_Preferred_Connection_Parameters_t structure. */
#define QAPI_BLE_GAP_PREFERRED_CONNECTION_PARAMETERS_DATA_SIZE    (sizeof(qapi_BLE_GAP_Preferred_Connection_Parameters_t))

/**
 * Enuration that represents the different Central Address Resolution
 * values that can be specified.
 */
typedef enum
{
   QAPI_BLE_GAR_DISABLED_E, /**< Disabled. */
   QAPI_BLE_GAR_ENABLED_E   /**< Enabled. */
} qapi_BLE_GAP_Central_Address_Resolution_t;

   /* GAPS Server API.                                                  */

/**
 * @brief
 * Opens a GAPS Server on a specified Bluetooth Stack.
 *
 * @details
 * Only one GAPS Server may be open at a time, per the Bluetooth Stack ID.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_GAPS_Initialize_Service().
 *
 * @param[out]  ServiceID           Unique GATT service ID of the
 *                                  registered GAPS service returned from the
 *                                  qapi_BLE_GATT_Register_Service() API.
 *
 * @return
 * Positive, nonzero -- If successful. The return value will
 *              be the Service Instance ID of GAPS Server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_GAPS_ERROR_MAXIMUM_NUMBER_OF_INSTANCES_REACHED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Initialize_Service(uint32_t BluetoothStackID, uint32_t *ServiceID);

/**
 * @brief
 * Opens a GAPS server on a specified Bluetooth Stack with
 * the ability to control the location of the service in the GATT database.
 *
 * @details
 * Only one GAPS Server may be open at a time, per the Bluetooth Stack ID.
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
 *              be the Service Instance ID of GAPS Server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_GAPS_ERROR_MAXIMUM_NUMBER_OF_INSTANCES_REACHED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with a Device Information Service Instance.
 *
 * @details
 * After this function is called, no other GAPS
 * function can be called until after a successful call to the
 * qapi_BLE_GAPS_Initialize_Service() function is performed.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_GAPS_Initialize_Service()
 *                                 function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queries the number of attributes
 * that are contained in the GAPS service that is registered with a
 * call to qapi_BLE_GAPS_Initialize_Service() or
 * qapi_BLE_GAPS_Initialize_Service_Handle_Range().
 *
 * @return
 * Positive, nonzero number -- Of attributes that can be
 *           registered by a GAPS service instance.\n
 * Zero -- On failure.
 */
QAPI_BLE_DECLARATION uint32_t QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Number_Attributes(void);

/**
 * @brief
 * Sets the device name characteristic
 * of a generic device on the specified GAP Service Instance.
 *
 * @details
 * The Name parameter must be a pointer to a NULL-terminated ASCII String
 * of at most QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH (not counting
 * the trailing NULL terminator).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_GAPS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  DeviceName          Device Name to set as the current
 *                                 Device Name for the specified GAP Service
 *                                 Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID \n
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Device_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *DeviceName);

/**
 * @brief
 * Queryies the current device name
 * characteristic of a generic device from the specified GAP Service Instance.
 *
 * @details
 * The Name parameter must be a pointer to a NULL-terminated ASCII String
 * of at most QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH (not counting
 * the trailing NULL terminator).
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_GAPS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  NameBuffer          Pointer to a structure to return
 *                                  the current Device for the specified
 *                                  GAPS Service Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Device_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *NameBuffer);

/**
 * @brief
 * Sets the Device Appearance
 * characteristic of a generic device on the specified GAP Service Instance.
 *
 * @details
 * The DeviceAppearance is an enumeration, which should be of the form
 * QAPI_BLE_GAP_DEVICE_APPEARENCE_VALUE_XXX.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from the qapi_BLE_GAPS_Initialize_Service()
 *                                 function.
 *
 * @param[in]  DeviceAppearance    Device Appearance is to be set as
 *                                 the current Device Appearance for the
 *                                 specified GAP Service Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Device_Appearance(uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t DeviceAppearance);

/**
 * @brief
 * Queryies the current device appearance
 * characteristic of generic device from the specified GAP Service Instance.
 *
 * @details
 * The DeviceAppearance is an enumeration, which should be of the form
 * QAPI_BLE_GAP_DEVICE_APPEARENCE_VALUE_XXX.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID          Service instance ID to close.
 *                                  This is the value that was returned
 *                                  from the qapi_BLE_GAPS_Initialize_Service()
 *                                  function.
 *
 * @param[out]  DeviceAppearance    Pointer to store the current Device
 *                                  Appearance for the specified GAP
 *                                  Service Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Device_Appearance(uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t *DeviceAppearance);

/**
 * @brief
 * Sets the Peripheral Preferred
 * Connection Parameter characteristic of generic device on the
 * specified GAP Service instance.
 *
 * @param[in]  BluetoothStackID                 Unique identifier
 *                                              assigned to this
 *                                              Bluetooth Protocol Stack
 *                                              via a call to
 *                                              qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID                       Service instance ID
 *                                              to close. This is the
 *                                              value that was returned
 *                                              from the
 *                                              qapi_BLE_GAPS_Initialize_Service()
 *                                              function.
 *
 * @param[in]  PreferredConnectionParameters    Preferred Connection
 *                                              Parameters to set as the
 *                                              current Peripheral
 *                                              Preferred Connection
 *                                              Parameters for the
 *                                              specified GAP Service
 *                                              Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Preferred_Connection_Parameters(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

/**
 * @brief
 * Queries the Peripheral Preferred Connection
 * Parameter characteristic of generic device from the specified GAP Service
 * instance.
 *
 * @param[in]   BluetoothStackID                 Unique identifier
 *                                               assigned to this
 *                                               Bluetooth Protocol Stack
 *                                               via a call to
 *                                               qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID                       Service instance ID
 *                                               to close. This is the
 *                                               value that was returned
 *                                               from the
 *                                               qapi_BLE_GAPS_Initialize_Service()
 *                                               function.
 *
 * @param[out]  PreferredConnectionParameters    Pointer to a structure
 *                                               to store the current
 *                                               Peripheral Preferred
 *                                               Connection Parameters
 *                                               for the specified GAP
 *                                               Service Instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Preferred_Connection_Parameters(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

/**
 * @brief
 * Sets the Central Address
 * Resolution characteristic on the specified GAP Service instance.
 *
 * @param[in]  BluetoothStackID            Unique identifier assigned to
 *                                         this Bluetooth Protocol Stack
 *                                         via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID                  Service instance ID to
 *                                         close. This is the value that
 *                                         was returned from the
 *                                         qapi_BLE_GAPS_Initialize_Service()
 *                                         function.
 *
 * @param[in]  CentralAddressResolution   Central Address Resolution to set.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                 #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Central_Address_Resolution(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t CentralAddressResolution);

/**
 * @brief
 * Queries the Central Address
 * Resolution characteristic on the specified GAP Service instance.
 *
 * @param[in]   BluetoothStackID            Unique identifier assigned to
 *                                          this Bluetooth Protocol Stack
 *                                          via a call to
 *                                          qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InstanceID                  Service instance ID to
 *                                          close. This is the value that
 *                                          was returned from the
 *                                          qapi_BLE_GAPS_Initialize_Service()
 *                                          function.
 *
 * @param[out]  CentralAddressResolution    Pointer to the Central
 *                                          Address Resolution that will
 *                                          be set if this function is
 *                                          successful.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Central_Address_Resolution(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution);

   /* GAPS Client API.                                                  */

/**
 * @brief
 * Decodes a Peripheral Preferred
 * Connection Parameter characteristic value that was received from a
 * remote device.
 *
 * @param[in]   ValueLength                      Specifies the length of
 *                                               the Preferred Connection
 *                                               Parameter value returned
 *                                               by the remote GAPS
 *                                               Server.
 *
 * @param[in]   Value                            Pointer to
 *                                               the Preferred Connection
 *                                               Parameter data returned
 *                                               by the remote GAPS
 *                                               Server.
 *
 * @param[out]  PreferredConnectionParameters    Pointer to a structure
 *                                               to store the decoded
 *                                               Peripheral Preferred
 *                                               Connection Parameters
 *                                               value that was received
 *                                               from the remote device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_GAPS_ERROR_MALFORMATTED_DATA \n
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Decode_Preferred_Connection_Parameters(uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Preferred_Connection_Parameters_t *PreferredConnectionParameters);

/**
 * @brief
 * Decodes a Central Address
 * Resolution characteristic value that was received from a remote device.
 *
 * @param[in]   ValueLength                 Specifies the length of the
 *                                          Central Address Resolution
 *                                          value returned by the remote
 *                                          GAPS Server.
 *
 * @param[in]   Value                       Pointer to the
 *                                          Central Address Resolution
 *                                          data returned by the remote
 *                                          GAPS Server.
 *
 * @param[out]  CentralAddressResolution    Pointer to the Central
 *                                          Address Resolution that holds
 *                                          the decoded value.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_PARAMETER \n
 *                  #QAPI_BLE_GAPS_ERROR_MALFORMATTED_DATA \n
 *                  #QAPI_BLE_GAPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Decode_Central_Address_Resolution(uint32_t ValueLength, uint8_t *Value, qapi_BLE_GAP_Central_Address_Resolution_t *CentralAddressResolution);

/** @} */ /* end_addtogroup qapi_ble_services_gaps */

#endif


