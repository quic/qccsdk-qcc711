/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_ctes.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Constant Tone Extension Service
 * (GATT based) API Type Definitions, Constants, and
 * Prototypes.
 *
 * @details
 * The Constant Tone Extension Service (CTES) programming interface
 * defines the protocols and procedures to be used to implement
 * CTES capabilities for both Server and Client services.
 */

#ifndef __QAPI_BLE_CTES_H__
#define __QAPI_BLE_CTES_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gap.h"       /* QAPI GAP prototypes.                     */
#include "./qapi_ble_gatt.h"      /* QAPI GATT prototypes.                    */
#include "./qapi_ble_ctestypes.h" /* QAPI CTES prototypes.                    */

/** @addtogroup qapi_ble_services_ctes
@{ */

/** @name Error Return Codes

      Error codes that are smaller than these (less than -1000) are
      related to the Bluetooth Protocol Stack itself (see
      qapi_ble_errors.h).
      @{ */

/** Invalid parameter. */
#define QAPI_BLE_CTES_ERROR_INVALID_PARAMETER                     (-1000)

/** Invalid Bluetooth stack ID. */
#define QAPI_BLE_CTES_ERROR_INVALID_BLUETOOTH_STACK_ID            (-1001)

/** Insufficient resources. */
#define QAPI_BLE_CTES_ERROR_INSUFFICIENT_RESOURCES                (-1002)

/** Service is already registered. */
#define QAPI_BLE_CTES_ERROR_SERVICE_ALREADY_REGISTERED            (-1003)

/** Invalid service instance ID. */
#define QAPI_BLE_CTES_ERROR_INVALID_INSTANCE_ID                   (-1004)

/** Malformatted data. */
#define QAPI_BLE_CTES_ERROR_MALFORMATTED_DATA                     (-1005)

/** Insufficient buffer space. */
#define QAPI_BLE_CTES_ERROR_INSUFFICIENT_BUFFER_SPACE             (-1006)

/** @} */ /* end namegroup */

/**
 * Structure that represents the CTES event data.
 */
typedef enum /** @cond */ qapi_BLE_CTES_Event_Type_s /** @endcond */
{
   QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_ENABLE_REQUEST_E, /**< Write CTE enable request event. */
   QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_MINIMUM_LENGTH_REQUEST_E, /**< Write CTE minimum length request event. */
   QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_E, /**< Write Advertising CTE minimum transmit count request event. */
   QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_E, /**< Write Advertising CTE transmit duration request event. */
   QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_E, /**< Write Advertising CTE interval request event. */
   QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_PHY_REQUEST_E, /**< Write Advertising CTE PHY request event. */
} qapi_BLE_CTES_Event_Type_t;

/**
 * Structure that holds the QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_ENABLE_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_CTE_Enable_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   uint8_t                         CTE_Enable; /**< Indicates the CTEs to enable. */
} qapi_BLE_CTES_CTE_Enable_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_CTE_Enable_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_CTE_ENABLE_CHARACTERISTIC_DATA_SIZE             (sizeof(qapi_BLE_CTES_CTE_Enable_Characteristic_Data_t));

/**
 * Structure that holds the QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_MINIMUM_LENGTH_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_CTE_Minimum_Length_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   uint8_t                         MinimumLength; /**< Indicates the minimum length of a CTE. */
} qapi_BLE_CTES_CTE_Minimum_Length_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_CTE_Minimum_Length_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_CHARACTERISTIC_DATA_SIZE     (sizeof(qapi_BLE_CTES_CTE_Minimum_Length_Characteristic_Data_t));

/**
 * Structure that holds the 
 * QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_Advertising_CTE_Minimum_Transmit_Count_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   uint8_t                         MinimumTransmitCount; /**< Indicates the minimum number of
                                                              CTEs to transmit in an advertising PDU. */
} qapi_BLE_CTES_Advertising_CTE_Minimum_Transmit_Count_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_Advertising_CTE_Minimum_Transmit_Count_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_CHARACTERISTIC_DATA_SIZE  (sizeof(qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_t));

/**
 * Structure that holds the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   uint8_t                         TransmitDuration; /**< Indicates the CTE transmit duration for an advertising PDU. */
} qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_CHARACTERISTIC_DATA_SIZE  (sizeof(qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_t));

/**
 * Structure that holds the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_Advertising_CTE_Interval_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   uint16_t                        Interval; /**< Indicates the CTE interval for an advertising PDU. */
} qapi_BLE_CTES_Advertising_CTE_Interval_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_Advertising_CTE_Interval_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_CHARACTERISTIC_DATA_SIZE  (sizeof(qapi_BLE_CTES_Advertising_CTE_Interval_Characteristic_Data_t));

/**
 * Structure that holds the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_PHY_REQUEST_E
 * event data.
 */
typedef struct qapi_BLE_CTES_Advertising_CTE_PHY_Characteristic_Data_s
{
   uint32_t                        InstanceID; /**< Identifies the CTES instance. */
   uint32_t                        ConnectionID; /**< Identifies the GATT connection. */
   qapi_BLE_GATT_Connection_Type_t ConnectionType; /**< Identifies the GATT connection type. */
   uint32_t                        TransactionID; /**< Identifies the GATT transaction. */
   qapi_BLE_BD_ADDR_t              RemoteDevice; /**< Identifies the remote device. */
   qapi_BLE_GAP_LE_PHY_Type_t      PHY_Type; /**< Indicates the PHY to use for advertising CTEs. */
} qapi_BLE_CTES_Advertising_CTE_PHY_Characteristic_Data_t;

/** Size of the #qapi_BLE_CTES_Advertising_CTE_PHY_Characteristic_Data_t structure. */
#define QAPI_BLE_CTES_ADVERTISING_CTE_PHY_CHARACTERISTIC_DATA_SIZE  (sizeof(qapi_BLE_CTES_Advertising_CTE_PHY_Characteristic_Data_t));

/**
 * Structure that holds all CTES event data.
 */
typedef struct qapi_BLE_CTES_Event_Data_s
{
   qapi_BLE_CTES_Event_Type_t Event_Type; /**< Identifies the event. */
   uint16_t                   Event_Data_Size; /**< Indicates the size of the union member. */
   union
   {
      qapi_BLE_CTES_CTE_Enable_Characteristic_Data_t                             *CTES_CTE_Enable_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_ENABLE_REQUEST_E event. */
      qapi_BLE_CTES_CTE_Minimum_Length_Characteristic_Data_t                     *CTES_CTE_Minimum_Length_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_MINIMUM_LENGTH_REQUEST_E event. */
      qapi_BLE_CTES_Advertising_CTE_Minimum_Transmit_Count_Characteristic_Data_t *CTES_Advertising_CTE_Minimum_Transmit_Count_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_E event. */
      qapi_BLE_CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data_t      *CTES_Advertising_CTE_Transmit_Duration_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_E event. */
      qapi_BLE_CTES_Advertising_CTE_Interval_Characteristic_Data_t               *CTES_Advertising_CTE_Interval_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_E event. */
      qapi_BLE_CTES_Advertising_CTE_PHY_Characteristic_Data_t                    *CTES_Advertising_CTE_PHY_Characteristic_Data; /**< Data for the QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_PHY_REQUEST_E event. */
   } Event_Data; /**< Holds all event data. */
} qapi_BLE_CTES_Event_Data_t;

/** Size of the #qapi_BLE_CTES_Event_Data_t structure. */
#define QAPI_BLE_CTES_EVENT_DATA_SIZE                             (sizeof(qapi_BLE_CTES_Event_Data_t))

/**
 * @brief
 * This declared type represents the prototype function for an
 * CTES instance event callback. This function is called
 * whenever a CTES instance event occurs that is associated with the
 * specified Bluetooth stack ID.

 * @details
 * The caller should use the contents of the CTES instance event data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have to be reentrant). It should be noted, however,
 * that if the same event callback is installed more than once, the
 * event callbacks will be called serially. Because of this, the
 * processing in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the thread
 * context of a thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another CTES instance event will not be processed while
 * this function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for CTES instance events that can
 * only be satisfied by receiving other Bluetooth Protocol Stack events.
 * A Deadlock will occur because other event callbacks will not be issued
 * while this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack on which the
 *                                   event occurred.
 *
 * @param[in]  CTES_Event_Data        Pointer to a structure that contains
 *                                   information about the event that has
 *                                   occurred.
 *
 * @param[in]  CallbackParameter     User-defined value that was supplied
 *                                   as an input parameter when the CTES
 *                                   instance event callback was
 *                                   installed.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_CTES_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_CTES_Event_Data_t *CTES_Event_Data, unsigned long CallbackParameter);

   /* CTES API.                                                         */

/**
 * @brief
 * Initializes a CTES instance (CTES server) on a specified
 * Bluetooth Protocol Stack.
 *
 * @details
 * Only one CTES instance may be initialized at a time, as per the Bluetooth
 * Protocol Stack ID.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallback       CTES event callback that
 *                                 receives CTES instance events.
 *
 * @param[in]  CallbackParameter   User-defined value that is
 *                                 received with the specified
 *                                 EventCallback parameter.
 *
 * @param[out] ServiceID           Unique GATT service ID of the
 *                                 registered CTES instance returned from
 *                                 the qapi_BLE_GATT_Register_Service()
 *                                 function.
 *
 * @return
 * Positive, nonzero -- If successful. The return value is
 *              the CTES instance ID of the CTES server that is
 *              successfully initialized for the specified Bluetooth
 *              Protocol Stack ID. This is the value that should be used
 *              in all subsequent function calls that require the CTES
 *              Instance ID.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX), or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Initialize_Service(uint32_t BluetoothStackID, qapi_BLE_CTES_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID);

/**
 * @brief
 * Initializes a CTES instance (CTES server) on a specified
 * Bluetooth Protocol Stack.
 *
 * Unlike qapi_BLE_CTES_Initialize_Service(), this function allows the
 * application to select a attribute handle range in GATT to store the
 * service.
 *
 * @details
 * Only one CTES instance may be initialized at a time, as per the Bluetooth
 * Protocol Stack ID.
 *
 * If the application wants GATT to select the attribute handle range for
 * the service, all fields of the ServiceHandleRange parameter must
 * be initialized to zero. The qapi_BLE_CTES_Query_Number_Attributes()
 * function may be used to determine
 * the attribute handle range for the CTES instance.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack using a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallback       CTES event callback that
 *                                 receives CTES instance events.
 *
 * @param[in]  CallbackParameter   User-defined value that is
 *                                 received with the specified
 *                                 EventCallback parameter.
 *
 * @param[out] ServiceID           Unique GATT service ID of the
 *                                 registered CTES instance returned from
 *                                 the qapi_BLE_GATT_Register_Service()
 *                                 function.
 *
 * @param[in,out]  ServiceHandleRange   Pointer that, on input, holds
 *                                      the handle range to store the
 *                                      service in GATT, and on output,
 *                                      contains the handle range for
 *                                      where the service is stored in
 *                                      GATT.
 *
 * @return
 * Positive, nonzero -- If successful. The return value is
 *              the CTES Instance ID of the CTES server that is
 *              successfully initialized for the specified Bluetooth
 *              Protocol Stack ID. This is the value that should be used
 *              in all subsequent function calls that require the CTES
 *              instance ID.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, qapi_BLE_CTES_Event_Callback_t EventCallback, unsigned long CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with a CTES Instance (CTES server).
 *
 * @details
 * After this function is called, no other CTES
 * function can be called until after a successful call to either of the
 * qapi_BLE_CTES_Initialize_XXX() functions.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queries the number of attributes
 * that are contained in a CTES instance.
 *
 * @return
 * Positive, nonzero number -- Of attributes for the
 *           registered CTES instance.\n
 * Zero -- On failure.
 */
QAPI_BLE_DECLARATION uint32_t QAPI_BLE_BTPSAPI CTES_Query_Number_Attributes(void);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_ENABLE_REQUEST_E event that
 * has been received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack using a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_CTE_Enable_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_CTE_MINIMUM_LENGTH_REQUEST_E event that
 * has been received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack using a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_CTE_Minimum_Length_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_REQUEST_E
 * event that is received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_Advertising_CTE_Minimum_Transmit_Count_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_TRANSMIT_DURATION_REQUEST_E
 * event that is received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_Advertising_CTE_Transmit_Duration_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_INTERVAL_REQUEST_E
 * event that is received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_Advertising_CTE_Interval_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Responds to a QAPI_BLE_ET_CTES_SERVER_WRITE_ADVERTISING_CTE_PHY_REQUEST_E
 * event that has been received.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_ctestypes.h
 * (CTES_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the CTES instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. CTES error codes can be
 *              found in qapi_ble_ctes.h (QAPI_BLE_CTES_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI CTES_Write_Advertising_CTE_PHY_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/** @} */ /* end_addtogroup qapi_ble_services_ctes */

#endif
