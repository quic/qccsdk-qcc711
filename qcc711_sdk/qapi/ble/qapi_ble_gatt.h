/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_gatt.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack Generic Attribute
 * Profile (GATT) using the Attribute Protocol (ATT) Type
 * Definitions, Constants, and Prototypes.
 *
 * @details
 * The Generic Attribute Profile programming interface defines the
 * protocols and procedures to be used to implement the defined
 * Bluetooth Attribute protocol capabilities.
 */

#ifndef __QAPI_BLE_GATT_APIH__
#define __QAPI_BLE_GATT_APIH__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gatttype.h"  /* GATT Type Definitions/Constants.         */
#include "./qapi_ble_atttypes.h"  /* ATT Type Definitions/Constants.          */

/** @addtogroup qapi_ble_profiles_gatt
@{ */

   /* Error Return Codes. */

   /* Error Codes that are smaller than these (less than -1000) are */
   /* related to the Bluetooth Protocol Stack itself (see */
   /* qapi_ble_errors.h). */

/** Invalid parameter. */
#define QAPI_BLE_GATT_ERROR_INVALID_PARAMETER                    (-1000)

/** GATT is not initialized. */
#define QAPI_BLE_GATT_ERROR_NOT_INITIALIZED                      (-1001)

/** GATT context already exists. */
#define QAPI_BLE_GATT_ERROR_CONTEXT_ALREADY_EXISTS               (-1002)

/** Invalid Bluetooth Stack ID. */
#define QAPI_BLE_GATT_ERROR_INVALID_BLUETOOTH_STACK_ID           (-1004)

/** Insufficient resources. */
#define QAPI_BLE_GATT_ERROR_INSUFFICIENT_RESOURCES               (-1005)

/** Invalid response. */
#define QAPI_BLE_GATT_ERROR_INVALID_RESPONSE                     (-1006)

/** Invalid operation. */
#define QAPI_BLE_GATT_ERROR_INVALID_OPERATION                    (-1007)

/** Invalid handle value. */
#define QAPI_BLE_GATT_ERROR_INVALID_HANDLE_VALUE                 (-1008)

/** Invalid connection ID. */
#define QAPI_BLE_GATT_ERROR_INVALID_CONNECTION_ID                (-1009)

/** Outstanding request exists. */
#define QAPI_BLE_GATT_ERROR_OUTSTANDING_REQUEST_EXISTS           (-1010)

/** Invalid service table format. */
#define QAPI_BLE_GATT_ERROR_INVALID_SERVICE_TABLE_FORMAT         (-1011)

/** Invalid transaction ID. */
#define QAPI_BLE_GATT_ERROR_INVALID_TRANSACTION_ID               (-1012)

/** Insufficient attribute handles. */
#define QAPI_BLE_GATT_ERROR_INSUFFICIENT_HANDLES                 (-1013)

   /* The following constants represent the defined flag bit-mask values */
   /* that can be passed to the GATT_Initialize() function. */

/** Initialize GATT to support LE. */
#define QAPI_BLE_GATT_INITIALIZATION_FLAGS_SUPPORT_LE                               0x00000001L

   /* The following flag can be passed to qapi_BLE_GATT_Initialize() to */
   /* disable the Service Changed Characteristic at run-time, if this */
   /* option has been enabled in the compile time configuration. If */
   /* disabled, the remote device will assume that the GATT service */
   /* table of this device is constant (and will never change). */

/** Disable the Service Changed Characteristic when GATT is intialized. */
#define QAPI_BLE_GATT_INITIALIZATION_FLAGS_DISABLE_SERVICE_CHANGED_CHARACTERISTIC   0x00000004L

/* The following flag can be passed to GATT_Initialize() to enable   */
/* the Database Hash Characteristic at run-time, if this option has  */
/* been enabled in the compile time configuration.                   */

/** Enable the Database Hash Characteristic when GATT is intialized. */
#define QAPI_BLE_GATT_INITIALIZATION_FLAGS_ENABLE_DATABASE_HASH_CHARACTERISTIC      0x00000008L

   /* The following bit masks define that allowable flags that may be   */
   /* specified in the Attribute_Flags member of the                    */
   /* qapi_BLE_GATT_Service_Attribute_Entry_t structure.                */

/** GATT attribute is readable. */
#define QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE                              0x01

/** GATT attribute is writable. */
#define QAPI_BLE_GATT_ATTRIBUTE_FLAGS_WRITABLE                              0x02

/** GATT attribute is hidden. */
#define QAPI_BLE_GATT_ATTRIBUTE_FLAGS_HIDDEN                                0x04

/** GATT attribute is readable and writable. */
#define QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE_WRITABLE                     (QAPI_BLE_GATT_ATTRIBUTE_FLAGS_READABLE|QAPI_BLE_GATT_ATTRIBUTE_FLAGS_WRITABLE)


   /* The following bit-masks define the allowable flags that may be    */
   /* specified in the Service_Flags parameter of the                   */
   /* qapi_BLE_GATT_Register_Service() function.                        */

/** Initialize GATT service to support LE. */
#define QAPI_BLE_GATT_SERVICE_FLAGS_LE_SERVICE                              0x01

   /* The following constants represent the execute write confirmation  */
   /* values that are possible in the GATT execute write confirmation   */
   /* event data information.                                           */

/** No error has occured for the Execute Write. */
#define QAPI_BLE_GATT_EXECUTE_WRITE_CONFIRMATION_STATUS_NO_ERROR            0x00

/** An error has occured for the Execute Write. */
#define QAPI_BLE_GATT_EXECUTE_WRITE_CONFIRMATION_STATUS_ERROR               0x01

   /* The following constants represent the server confirmation status  */
   /* values that are possible in the GATT server confirmation event    */
   /* data information.                                                 */

/** GATT confirmation was successful. */
#define QAPI_BLE_GATT_CONFIRMATION_STATUS_SUCCESS                           0x00

/** GATT confirmation timed out. */
#define QAPI_BLE_GATT_CONFIRMATION_STATUS_TIMEOUT                           0x01

   /* The following defines the default maximum supported GATT MTU. */

/** The maximum supported GATT MTU. */
#define QAPI_BLE_GATT_DEFAULT_MAXIMUM_SUPPORTED_STACK_MTU                   (517)

/**
 * Enumeration that represents the supported BR/EDR incoming connection
 * modes.
 */
typedef enum
{
   QAPI_BLE_GIM_AUTOMATIC_ACCEPT_E, /**< Auto accept connection requests. */
   QAPI_BLE_GIM_AUTOMATIC_REJECT_E, /**< Auto reject connection requests. */
   QAPI_BLE_GIM_MANUAL_ACCEPT_E     /**< Accept/reject on a per connection basis. */
} qapi_BLE_GATT_Incoming_Connection_Mode_t;

/**
 * Enumeration that represents the different connection types that are
 * supported by GATT.
 */
typedef enum
{
   QAPI_BLE_GCT_LE_E,    /**< LE connection. */
   QAPI_BLE_GCT_BR_EDR_E /**< BR/EDR connection. */
} qapi_BLE_GATT_Connection_Type_t;

/**
 * Enumeration that represents the different types of service definitions
 * that GATT supports.
 */
typedef enum
{
   QAPI_BLE_ST_SECONDARY_E, /**< Secondary. */
   QAPI_BLE_ST_PRIMARY_E    /**< Primary. */
} qapi_BLE_GATT_Service_Type_t;

/**
 * Enumeration that represents the different types of request errors.
 */
typedef enum
{
   QAPI_BLE_RET_ERROR_RESPONSE_E,             /**< Error response. */
   QAPI_BLE_RET_PROTOCOL_TIMEOUT_E,           /**< Protocol Timeout. */
   QAPI_BLE_RET_PREPARE_WRITE_DATA_MISMATCH_E /**< Prepare Write data mismatch. */
} qapi_BLE_GATT_Request_Error_Type_t;

/**
 * Enumeration that represents the different UUID types that are
 * allowable as attribute types and attribute values.
 */
typedef enum
{
   QAPI_BLE_GU_UUID_16_E,  /**< 16-bit UUID. */
   QAPI_BLE_GU_UUID_128_E, /**< 128-bit UUID. */
   QAPI_BLE_GU_UUID_32_E   /**< 32-bit UUID. */
} qapi_BLE_GATT_UUID_Type_t;

/**
 * Structure that represents a GATT UUID.
 */
typedef struct qapi_BLE_GATT_UUID_s
{
   /**
    * UUID type.
    */
   qapi_BLE_GATT_UUID_Type_t UUID_Type;
   union
   {
      /**
       * 16-bit UUID data. Valid if the UUID_Type is
       * #QAPI_BLE_GU_UUID_16_E.
       */
      qapi_BLE_UUID_16_t  UUID_16;

      /**
       * 32-bit UUID data. Valid if the UUID_Type is
       * #QAPI_BLE_GU_UUID_32_E.
       */
      qapi_BLE_UUID_32_t  UUID_32;

      /**
       * 128-bit UUID data. Valid if the UUID_Type is
       * #QAPI_BLE_GU_UUID_128_E.
       */
      qapi_BLE_UUID_128_t UUID_128;
   }
   /**
    * UUID data.
    */
   UUID;
} qapi_BLE_GATT_UUID_t;

/** Size of the #qapi_BLE_GATT_UUID_t structure. */
#define QAPI_BLE_GATT_UUID_DATA_SIZE                              (sizeof(qapi_BLE_GATT_UUID_t))

/**
 * Enumeration that represents the different types of attributes that may
 * be placed in a qapi_BLE_GATT_Service_Attribute_Entry_t structure.
 */
typedef enum
{
   QAPI_BLE_AET_PRIMARY_SERVICE_16_E,
   /**< Primary service declaration with 16-bit UUID. */
   QAPI_BLE_AET_PRIMARY_SERVICE_128_E,
   /**< Primary service declaration with 128-bit UUID. */
   QAPI_BLE_AET_SECONDARY_SERVICE_16_E,
   /**< Secondary service declaration with 16-bit UUID. */
   QAPI_BLE_AET_SECONDARY_SERVICE_128_E,
   /**< Secondary service declaration with 128-bit UUID. */
   QAPI_BLE_AET_INCLUDE_DEFINITION_E,
   /**< Include definition. */
   QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_16_E,
   /**< Characteristic Declaration with 16-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E,
   /**< Characteristic Declaration with 128-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E,
   /**< Characteristic Value with 16-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E,
   /**< Characteristic Value with 128-bitu87i9 UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E,
   /**< Characteristic Descriptor with 16-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E,
   /**< Characteristic Descriptor with 128-bit UUID. */
   QAPI_BLE_AET_PRIMARY_SERVICE_32_E,
   /**< Primary service declaration with 32-bit UUID. */
   QAPI_BLE_AET_SECONDARY_SERVICE_32_E,
   /**< Secondary service declaration with 32-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_32_E,
   /**< Characteristic declaration with 32-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E,
   /**< Characteristic Value with 32-bit UUID. */
   QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E
   /**< Characteristic Descriptor with 32-bit UUID. */
} qapi_BLE_GATT_Service_Attribute_Entry_Type_t;

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_PRIMARY_SERVICE_16_E.
 */
typedef struct qapi_BLE_GATT_Primary_Service_16_Entry_s
{
   /**
    * 16-bit service UUID.
    */
   qapi_BLE_UUID_16_t Service_UUID;
} qapi_BLE_GATT_Primary_Service_16_Entry_t;

/** Size of the #qapi_BLE_GATT_Primary_Service_16_Entry_t structure. */
#define QAPI_BLE_GATT_PRIMARY_SERVICE_16_ENTRY_DATA_SIZE          (sizeof(qapi_BLE_GATT_Primary_Service_16_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_PRIMARY_SERVICE_32_E.
 */
typedef struct qapi_BLE_GATT_Primary_Service_32_Entry_s
{
   /**
    * 32-bit service UUID.
    */
   qapi_BLE_UUID_32_t Service_UUID;
} qapi_BLE_GATT_Primary_Service_32_Entry_t;

/** Size of the #qapi_BLE_GATT_Primary_Service_32_Entry_t structure. */
#define QAPI_BLE_GATT_PRIMARY_SERVICE_32_ENTRY_DATA_SIZE          (sizeof(qapi_BLE_GATT_Primary_Service_32_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_PRIMARY_SERVICE_128_E.
 */
typedef struct qapi_BLE_GATT_Primary_Service_128_Entry_s
{
   /**
    * 128-bit service UUID.
    */
   qapi_BLE_UUID_128_t Service_UUID;
} qapi_BLE_GATT_Primary_Service_128_Entry_t;

/** Size of the #qapi_BLE_GATT_Primary_Service_128_Entry_t structure. */
#define QAPI_BLE_GATT_PRIMARY_SERVICE_128_ENTRY_DATA_SIZE         (sizeof(qapi_BLE_GATT_Primary_Service_128_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_SECONDARY_SERVICE_16_E.
 */
typedef struct qapi_BLE_GATT_Secondary_Service_16_Entry_s
{
   /**
    * 16-bit service UUID.
    */
   qapi_BLE_UUID_16_t Service_UUID;
} qapi_BLE_GATT_Secondary_Service_16_Entry_t;

/** Size of the #qapi_BLE_GATT_Secondary_Service_16_Entry_t structure. */
#define QAPI_BLE_GATT_SECONDARY_SERVICE_16_ENTRY_DATA_SIZE        (sizeof(qapi_BLE_GATT_Secondary_Service_16_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_SECONDARY_SERVICE_32_E.
 */
typedef struct qapi_BLE_GATT_Secondary_Service_32_Entry_s
{
   /**
    * 32-bit service UUID.
    */
   qapi_BLE_UUID_32_t Service_UUID;
} qapi_BLE_GATT_Secondary_Service_32_Entry_t;

/** Size of the #qapi_BLE_GATT_Secondary_Service_32_Entry_t structure. */
#define QAPI_BLE_GATT_SECONDARY_SERVICE_32_ENTRY_DATA_SIZE        (sizeof(qapi_BLE_GATT_Secondary_Service_32_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_SECONDARY_SERVICE_128_E.
 */
typedef struct qapi_BLE_GATT_Secondary_Service_128_Entry_s
{
   /**
    * 128-bit service UUID.
    */
   qapi_BLE_UUID_128_t Service_UUID;
} qapi_BLE_GATT_Secondary_Service_128_Entry_t;

/** Size of the #qapi_BLE_GATT_Secondary_Service_128_Entry_t structure. */
#define QAPI_BLE_GATT_SECONDARY_SERVICE_128_ENTRY_DATA_SIZE       (sizeof(qapi_BLE_GATT_Secondary_Service_128_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_INCLUDE_DEFINITION_E. The ServiceID must be the
 * return value from the qapi_BLE_GATT_Register_Service() function (used to
 * register the included service).
 */
typedef struct qapi_BLE_GATT_Include_Definition_Entry_s
{
   /**
    * Included service ID.
    */
   uint32_t ServiceID;
} qapi_BLE_GATT_Include_Definition_Entry_t;

/** Size of the #qapi_BLE_GATT_Include_Definition_Entry_t structure. */
#define QAPI_BLE_GATT_INCLUDE_DEFINITION_ENTRY_DATA_SIZE          (sizeof(qapi_BLE_GATT_Include_Definition_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_16_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Declaration_16_Entry_s
{
   /**
    * GATT characteristic properties.
    */
   uint8_t            Properties;

   /**
    * GATT characteristic value 16-bit UUID.
    */
   qapi_BLE_UUID_16_t Characteristic_Value_UUID;
} qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_16_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_32_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Declaration_32_Entry_s
{
   /**
    * GATT characteristic properties.
    */
   uint8_t             Properties;

   /**
    * GATT characteristic value 32-bit UUID.
    */
   qapi_BLE_UUID_32_t  Characteristic_Value_UUID;
} qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_32_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Declaration_128_Entry_s
{
   /**
    * GATT characteristic properties.
    */
   uint8_t              Properties;

   /**
    * GATT characteristic value 128-bit UUID.
    */
   qapi_BLE_UUID_128_t  Characteristic_Value_UUID;
} qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_128_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Value_16_Entry_s
{
   /**
    * GATT characteristic value 16-bit UUID.
    */
   qapi_BLE_UUID_16_t  Characteristic_Value_UUID;

   /**
    * GATT characteristic value length.
    */
   uint32_t            Characteristic_Value_Length;

   /**
    * Pointer to the GATT characteristic value.
    */
   uint8_t            *Characteristic_Value;
} qapi_BLE_GATT_Characteristic_Value_16_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Value_16_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_VALUE_16_ENTRY_DATA_SIZE     (sizeof(qapi_BLE_GATT_Characteristic_Value_16_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Value_32_Entry_s
{
   /**
    * GATT characteristic value 32-bit UUID.
    */
   qapi_BLE_UUID_32_t  Characteristic_Value_UUID;

   /**
    * GATT characteristic value length.
    */
   uint32_t            Characteristic_Value_Length;

   /**
    * Pointer to the GATT characteristic value.
    */
   uint8_t            *Characteristic_Value;
} qapi_BLE_GATT_Characteristic_Value_32_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Value_32_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_VALUE_32_ENTRY_DATA_SIZE     (sizeof(qapi_BLE_GATT_Characteristic_Value_32_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Value_128_Entry_s
{
   /**
    * GATT characteristic value 128-bit UUID.
    */
   qapi_BLE_UUID_128_t  Characteristic_Value_UUID;

   /**
    * GATT characteristic value length.
    */
   uint32_t             Characteristic_Value_Length;

   /**
    * Pointer to the GATT characteristic value.
    */
   uint8_t             *Characteristic_Value;
} qapi_BLE_GATT_Characteristic_Value_128_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Value_128_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_VALUE_128_ENTRY_DATA_SIZE    (sizeof(qapi_BLE_GATT_Characteristic_Value_128_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_s
{
   /**
    * GATT Characteristic Descriptor 16-bit UUID.
    */
   qapi_BLE_UUID_16_t  Characteristic_Descriptor_UUID;

   /**
    * GATT Characteristic Descriptor length.
    */
   uint32_t            Characteristic_Descriptor_Length;

   /**
    * Pointer to the GATT Characteristic Descriptor.
    */
   uint8_t            *Characteristic_Descriptor;
} qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_16_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_s
{
   /**
    * GATT Characteristic Descriptor 32-bit UUID.
    */
   qapi_BLE_UUID_32_t  Characteristic_Descriptor_UUID;

   /**
    * GATT Characteristic Descriptor length.
    */
   uint32_t            Characteristic_Descriptor_Length;

   /**
    * Pointer to the GATT Characteristic Descriptor.
    */
   uint8_t            *Characteristic_Descriptor;
} qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_32_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t))

/**
 * Structure that represents the structure of the data that must be
 * specified for a qapi_BLE_GATT_Service_Attribute_Entry_t of type
 * #QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_s
{
   /**
    * GATT Characteristic Descriptor 128-bit UUID.
    */
   qapi_BLE_UUID_128_t  Characteristic_Descriptor_UUID;

   /**
    * GATT Characteristic Descriptor length.
    */
   uint32_t             Characteristic_Descriptor_Length;

   /**
    * Pointer to the GATT Characteristic Descriptor.
    */
   uint8_t             *Characteristic_Descriptor;
} qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_128_ENTRY_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t))


/**
 * Structure that represents the format of an attribute entry for a GATT
 * Service.
 *
 * By specifying GATT_ATTRIBUTE_FLAGS_HIDDEN in the Attribute_Flags
 * member, GATT will allocate a handle for the attribute, but the
 * attribute will not appear on any discovery requests, and all attempts
 * to read or write to the attribute will fail.
 *
 * Since the qapi_BLE_GATT_Register_Service() function takes a pointer
 * to an array of these structures, the Attribute_Flags member may be
 * modified after a sucessful call to the
 * qapi_BLE_GATT_Register_Service() function, however locking should be
 * performed to prevent modifying it while GATT is reading it.
 *
 * The Attribute_Value member must point to the correct data type based
 * on the correct entry type. The corresponding attribute value for each
 * supported attribute entry type is as follows:
 *
 *   @li QAPI_BLE_AET_PRIMARY_SERVICE_16_E
 *         qapi_BLE_GATT_Primary_Service_16_Entry_t
 *   @li QAPI_BLE_AET_PRIMARY_SERVICE_32_E
 *         qapi_BLE_GATT_Primary_Service_32_Entry_t
 *   @li QAPI_BLE_AET_PRIMARY_SERVICE_128_E
 *          qapi_BLE_GATT_Primary_Service_128_Entry_t
 *   @li QAPI_BLE_AET_SECONDARY_SERVICE_16_E
 *          qapi_BLE_GATT_Secondary_Service_16_Entry_t
 *   @li QAPI_BLE_AET_SECONDARY_SERVICE_32_E
 *          qapi_BLE_GATT_Secondary_Service_32_Entry_t
 *   @li QAPI_BLE_AET_SECONDARY_SERVICE_128_E
 *          qapi_BLE_GATT_Secondary_Service_128_Entry_t
 *   @li QAPI_BLE_AET_INCLUDE_DEFINITION_E
 *          qapi_BLE_GATT_Include_Definition_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_16_E
 *          qapi_BLE_GATT_Characteristic_Declaration_16_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_32_E
 *          qapi_BLE_GATT_Characteristic_Declaration_32_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DECLARATION_128_E
 *          qapi_BLE_GATT_Characteristic_Declaration_128_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_VALUE_16_E
 *          qapi_BLE_GATT_Characteristic_Value_16_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_VALUE_32_E
 *          qapi_BLE_GATT_Characteristic_Value_32_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_VALUE_128_E
 *          qapi_BLE_GATT_Characteristic_Value_128_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_16_E
 *          qapi_BLE_GATT_Characteristic_Descriptor_16_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_32_E
 *          qapi_BLE_GATT_Characteristic_Descriptor_32_Entry_t
 *   @li QAPI_BLE_AET_CHARACTERISTIC_DESCRIPTOR_128_E
 *          qapi_BLE_GATT_Characteristic_Descriptor_128_Entry_t
 */
typedef struct qapi_BLE_GATT_Service_Attribute_Entry_s
{
   /**
    * GATT attribute flags.
    */
   uint8_t                                       Attribute_Flags;

   /**
    * GATT attribute entry type.
    */
   qapi_BLE_GATT_Service_Attribute_Entry_Type_t  Attribute_Entry_Type;

   /**
    * Pointer to the GATT attribute value.
    */
   void                                         *Attribute_Value;
} qapi_BLE_GATT_Service_Attribute_Entry_t;

/** Size of the #qapi_BLE_GATT_Service_Attribute_Entry_t structure. */
#define QAPI_BLE_GATT_SERVICE_ATTRIBUTE_ENTRY_DATA_SIZE           (sizeof(qapi_BLE_GATT_Service_Attribute_Entry_t))

/**
 * Structure that represents GATT attribute handle group.
 */
typedef struct qapi_BLE_GATT_Attribute_Handle_Group_s
{
   /**
    * Starting attribute randle.
    */
   uint16_t Starting_Handle;

   /**
    * Ending attribute randle.
    */
   uint16_t Ending_Handle;
} qapi_BLE_GATT_Attribute_Handle_Group_t;

/** Size of the #qapi_BLE_GATT_Attribute_Handle_Group_t structure. */
#define QAPI_BLE_GATT_ATTRIBUTE_HANDLE_GROUP_DATA_SIZE            (sizeof(qapi_BLE_GATT_Attribute_Handle_Group_t))

/**
 * Structure that represents the information that is returned about a
 * GATT Service from a GATT service discovery procedure.
 */
typedef struct qapi_BLE_GATT_Service_Information_s
{
   /**
    * Starting attribute handle of the service.
    */
   uint16_t             Service_Handle;

   /**
    * Last attribute handle of the service.
    */
   uint16_t             End_Group_Handle;

   /**
    * Service GATT UUID.
    */
   qapi_BLE_GATT_UUID_t UUID;
} qapi_BLE_GATT_Service_Information_t;

/** Size of the #qapi_BLE_GATT_Service_Information_t structure. */
#define QAPI_BLE_GATT_SERVICE_INFORMATION_DATA_SIZE               (sizeof(qapi_BLE_GATT_Service_Information_t))

/**
 * Structure that represents the information that is returned about a
 * GATT service from a GATT service  discovery procedure.
 */
typedef struct qapi_BLE_GATT_Service_Information_By_UUID_s
{
   /**
    * Starting attribute handle of the service.
    */
   uint16_t Service_Handle;

   /**
    * Last attribute handle of the service.
    */
   uint16_t End_Group_Handle;
} qapi_BLE_GATT_Service_Information_By_UUID_t;

/** Size of the #qapi_BLE_GATT_Service_Information_By_UUID_t structure. */
#define QAPI_BLE_GATT_SERVICE_INFORMATION_BY_UUID_DATA_SIZE       (sizeof(qapi_BLE_GATT_Service_Information_By_UUID_t))

/**
 * Structure that represents the structure of information that is
 * returned about a GATT included service declaration from a GATT find
 * included services procedure.
 *
 * The UUID member is only valid for a included service if the
 * UUID_Valid member is TRUE. Otherwise it is invalid and should be
 * ignored.
 */
typedef struct qapi_BLE_GATT_Include_Information_s
{
   /**
    * Attribute handle for the include service.
    */
   uint16_t             Include_Attribute_Handle;

   /**
    * Included service starting attribute handle.
    */
   uint16_t             Included_Service_Handle;

   /**
    * Included service ending attribute handle.
    */
   uint16_t             Included_Service_End_Group_Handle;

   /**
    * Flags if the GATT UUID is valid.
    */
   boolean_t            UUID_Valid;

   /**
    * GATT UUID of the included service.
    */
   qapi_BLE_GATT_UUID_t UUID;
} qapi_BLE_GATT_Include_Information_t;

/** Size of the #qapi_BLE_GATT_Include_Information_t structure. */
#define QAPI_BLE_GATT_INCLUDE_INFORMATION_DATA_SIZE               (sizeof(qapi_BLE_GATT_Include_Information_t))

/**
 * For the LE Only GATT build we will define this data type to be a
 * void pointer since qapi_ble_sdp.h is not included for a Single Mode
 * Stack.                                                          .
 */
typedef void * qapi_BLE_SDP_UUID_Entry_t;

/**
 * Structure that represents a BR/EDR SDP service record.
 *
 * Not used for single mode stack, but required to build.
 */
typedef struct qapi_BLE_GATT_SDP_Service_Record_s
{
   /**
    * Number of service class UUIDs.
    */
   uint32_t                   NumberServiceClassUUID;

   /**
    * List of UUID entries.
    */
   qapi_BLE_SDP_UUID_Entry_t *SDPUUIDEntries;
} qapi_BLE_GATT_SDP_Service_Record_t;

/** Size of the #qapi_BLE_GATT_SDP_Service_Record_t structure. */
#define QAPI_BLE_GATT_SDP_SERVICE_RECORD_SIZE                    (sizeof(qapi_BLE_GATT_SDP_Service_Record_t))

/**
 * Structure that represents the structure of the Service Changed
 * characteristic value.
 */
typedef struct qapi_BLE_GATT_Service_Changed_Data_s
{
   /**
    * First attribute handle that has been affected by the addition
    * and/or removal of a GATT service.
    */
   uint16_t  Affected_Start_Handle;

   /**
    * Last attribute handle that has been affected by the addition
    * and/or removal of a GATT service.
    */
   uint16_t  Affected_End_Handle;
} qapi_BLE_GATT_Service_Changed_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Changed_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_CHANGED_DATA_SIZE                   (sizeof(qapi_BLE_GATT_Service_Changed_Data_t))

   /* GATT Service Discovery types. */

/**
 * Structure that represents the information that is returned about a
 * discovered GATT Characteristic Descriptor.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_Information_s
{
   /**
    * GATT Characteristic Descriptor attribute handle.
    */
   uint16_t             Characteristic_Descriptor_Handle;

   /**
    * GATT Characteristic Descriptor UUID.
    */
   qapi_BLE_GATT_UUID_t Characteristic_Descriptor_UUID;
} qapi_BLE_GATT_Characteristic_Descriptor_Information_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_Information_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_INFORMATION_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Descriptor_Information_t))

/**
 * Structure that represents the information that is returned about a
 * discovered GATT Characteristic.
 */
typedef struct qapi_BLE_GATT_Characteristic_Information_s
{
   /**
    * GATT Characteristic UUID.
    */
   qapi_BLE_GATT_UUID_t                                   Characteristic_UUID;

   /**
    * GATT Characteristic attribute handle.
    */
   uint16_t                                               Characteristic_Handle;

   /**
    * GATT Characteristic properties.
    */
   uint8_t                                                Characteristic_Properties;

   /**
    * Number of Descriptors that are included for the GATT
    * Characteristic.
    */
   uint32_t                                               NumberOfDescriptors;

   /**
    * Pointer to the list of Descriptors that are included for the
    * GATT Characteristic.
    */
   qapi_BLE_GATT_Characteristic_Descriptor_Information_t *DescriptorList;
} qapi_BLE_GATT_Characteristic_Information_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Information_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_INFORMATION_DATA_SIZE            (sizeof(qapi_BLE_GATT_Characteristic_Information_t))

/**
 * Structure that represents the structure of data, stored
 * persistently for bonded client, that GATT will request be provided
 * by the upper layer.
 *
 * This is not all of the data that should be stored
 * persistently for bonded devices, just the data that GATT
 * needs access to internally.
 */
typedef struct qapi_BLE_GATT_Bonded_Client_Data_s
{
   /**
    * Indicates the valid structure fields.
    */
   unsigned long              Flags;

   /**
    * Length of the client supported features array.
    */
   uint32_t                   Client_Supported_Features_Length;

   /**
    * Client supported features array.
    */
   uint8_t                   *Client_Supported_Features;

   /**
    * Database hash value.
    */
   qapi_BLE_Encrypted_Data_t  Database_Hash;
} qapi_BLE_GATT_Bonded_Client_Data_t;
/**<
 * Size of the #qapi_BLE_GATT_Bonded_Client_Data_t structure.
 */

/** Client supported features field is valid. */
#define GATT_BONDED_CLIENT_DATA_FLAGS_CLIENT_SUPPORTED_FEATURES_VALID   0x00000001L

/** Database hash field is valid. */
#define GATT_BONDED_CLIENT_DATA_FLAGS_DATABASE_HASH_VALID               0x00000002L

   /* GATT Event API Types. */

/**
 * These events are issued to the application via callbacks registered to
 * receive connection events.
 *
 * The following event types are no longer valid but left in
 * the enumerated list for legacy purposes. Therefore, they do not need
 * to be handled by the upper layer application.
 *
 *   @li QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E
 *   @li QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_CONFIRMATION_E
 */
typedef enum
{
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E,
   /**< GATT device connection request event. */
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_E,
   /**< GATT device connection open request event. */
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_CONFIRMATION_E,
   /**< GATT device connection confirmation event. */
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_DISCONNECTION_E,
   /**< GATT device disconnection event. */
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_MTU_UPDATE_E,
   /**< GATT device MTU update event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVER_INDICATION_E,
   /**< GATT server indication event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E,
   /**< GATT server notification event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVICE_DATABASE_UPDATE_E,
   /**< GATT service database updated event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_READ_REQUEST_E,
   /**< GATT Service Changed read request event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CONFIRMATION_E,
   /**< GATT Service Changed confirmation event. */
   QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E,
   /**< GATT device buffer empty event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_READ_REQUEST_E,
   /**< GATT Service Changed CCCD read request event. */
   QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_UPDATE_E,
   /**< GATT Service Changed CCCD write request event. */
   QAPI_BLE_ET_GATT_CONNECTION_CLIENT_SUPPORTED_FEATURES_UPDATE_E,
   /**< GATT clinet supported features update event. */
   QAPI_BLE_ET_GATT_CONNECTION_BONDED_CLIENT_DATA_REQUEST_E,
   /**< GATT bonded client data request event. */
   QAPI_BLE_ET_GATT_CONNECTION_REMOTE_DATABASE_UPDATED_E,
   /**< GATT remote database updated event. */
} qapi_BLE_GATT_Connection_Event_Type_t;

/**
 * These events are issued to the application via the callback registered
 * when the application registers a local GATT service on the local
 * device.
 */
typedef enum
{
   QAPI_BLE_ET_GATT_SERVER_DEVICE_CONNECTION_E,
   /**< GATT server connection event. */
   QAPI_BLE_ET_GATT_SERVER_DEVICE_DISCONNECTION_E,
   /**< GATT server disconnection event. */
   QAPI_BLE_ET_GATT_SERVER_READ_REQUEST_E,
   /**< GATT server read request event. */
   QAPI_BLE_ET_GATT_SERVER_WRITE_REQUEST_E,
   /**< GATT server write request event. */
   QAPI_BLE_ET_GATT_SERVER_SIGNED_WRITE_REQUEST_E,
   /**< GATT server signed write request event. */
   QAPI_BLE_ET_GATT_SERVER_EXECUTE_WRITE_REQUEST_E,
   /**< GATT server execute write request event. */
   QAPI_BLE_ET_GATT_SERVER_EXECUTE_WRITE_CONFIRMATION_E,
   /**< GATT server execute write confirmation event. */
   QAPI_BLE_ET_GATT_SERVER_CONFIRMATION_RESPONSE_E,
   /**< GATT server confirmation response event. */
   QAPI_BLE_ET_GATT_SERVER_DEVICE_CONNECTION_MTU_UPDATE_E,
   /**< GATT server connection MTU update event. */
   QAPI_BLE_ET_GATT_SERVER_DEVICE_BUFFER_EMPTY_E
   /**< GATT server device buffer empty. */
} qapi_BLE_GATT_Server_Event_Type_t;

/**
 * Enumeration that represents all the allowable GATT client Event Data
 * Types that will be returned in the GATT client Callback Function.
 */
typedef enum
{
   QAPI_BLE_ET_GATT_CLIENT_ERROR_RESPONSE_E,
   /**< GATT client error response event. */
   QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_RESPONSE_E,
   /**< GATT client service discovery response event. */
   QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_BY_UUID_RESPONSE_E,
   /**< GATT client service discovery by UUID response event. */
   QAPI_BLE_ET_GATT_CLIENT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_E,
   /**< GATT client include services discovery response event. */
   QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DISCOVERY_RESPONSE_E,
   /**< GATT client Characteristic discovery response event. */
   QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_DISCOVERY_RESPONSE_E,
   /**<
    * GATT client Characteristic Descriptor discovery response
    * event.
    */
   QAPI_BLE_ET_GATT_CLIENT_READ_RESPONSE_E,
   /**< GATT client read response event. */
   QAPI_BLE_ET_GATT_CLIENT_READ_LONG_RESPONSE_E,
   /**< GATT client read long response event. */
   QAPI_BLE_ET_GATT_CLIENT_READ_BY_UUID_RESPONSE_E,
   /**< GATT client read by UUID response event. */
   QAPI_BLE_ET_GATT_CLIENT_READ_MULTIPLE_RESPONSE_E,
   /**< GATT client read multiple response event. */
   QAPI_BLE_ET_GATT_CLIENT_WRITE_RESPONSE_E,
   /**< GATT client write response event. */
   QAPI_BLE_ET_GATT_CLIENT_PREPARE_WRITE_RESPONSE_E,
   /**< GATT client prepare write response event. */
   QAPI_BLE_ET_GATT_CLIENT_EXECUTE_WRITE_RESPONSE_E,
   /**< GATT client execute write response event. */
   QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E
   /**< GATT client exchanged MTU response event. */
} qapi_BLE_GATT_Client_Event_Type_t;

/**
 * Enumeration that represents all the allowable GATT Service Discovery
 * Event Data Types that will be returned in the GATT Service Discovery
 * Callback Function.
 */
typedef enum
{
   QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E,
   /**< GATT client service discovery indication event. */
   QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E
   /**< GATT client service discovery complete event. */
} qapi_BLE_GATT_Service_Discovery_Event_Type_t;

   /* GATT Connection Events. */

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E event.
 */
typedef struct qapi_BLE_GATT_Device_Connection_Request_Data_s
{
   /**
    * GATT Connection type.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;
} qapi_BLE_GATT_Device_Connection_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Connection_Request_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_CONNECTION_REQUEST_DATA_SIZE         (sizeof(qapi_BLE_GATT_Device_Connection_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_E event.
 *
 * GATT Connection ID is unique and is used to identity a connection
 * with a remote device.
 */
typedef struct qapi_BLE_GATT_Device_Connection_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Maximum Transmission Unit (MTU) for the connection.
    */
   uint16_t                         MTU;
} qapi_BLE_GATT_Device_Connection_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Connection_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_CONNECTION_DATA_SIZE                 (sizeof(qapi_BLE_GATT_Device_Connection_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_CONFIRMATION_E event.
 */
typedef struct qapi_BLE_GATT_Device_Connection_Confirmation_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * The status of the GATT connection.
    */
   uint32_t                         ConnectionStatus;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Maximum Transmission Unit (MTU) for the connection.
    */
   uint16_t                         MTU;
} qapi_BLE_GATT_Device_Connection_Confirmation_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Connection_Confirmation_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_CONNECTION_CONFIRMATION_DATA_SIZE    (sizeof(qapi_BLE_GATT_Device_Connection_Confirmation_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_DISCONNECTION_E event.
 */
typedef struct qapi_BLE_GATT_Device_Disconnection_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
   * Indicates if the database hash is valid.
   */
   boolean_t                        Database_Hash_Valid;

   /**
   * Database hash value.
   */
   qapi_BLE_Encrypted_Data_t        Database_Hash;
} qapi_BLE_GATT_Device_Disconnection_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Disconnection_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_DISCONNECTION_DATA_SIZE              (sizeof(qapi_BLE_GATT_Device_Disconnection_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E event.
 */
typedef struct qapi_BLE_GATT_Device_Buffer_Empty_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;
} qapi_BLE_GATT_Device_Buffer_Empty_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Buffer_Empty_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_BUFFER_EMPTY_DATA_SIZE               (sizeof(qapi_BLE_GATT_Device_Buffer_Empty_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E event.
 */
typedef struct qapi_BLE_GATT_Server_Notification_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Attribute handle.
    */
   uint16_t                         AttributeHandle;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;
} qapi_BLE_GATT_Server_Notification_Data_t;

/** Size of the #qapi_BLE_GATT_Server_Notification_Data_t structure. */
#define QAPI_BLE_GATT_SERVER_NOTIFICATION_DATA_SIZE               (sizeof(qapi_BLE_GATT_Server_Notification_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E event.
 */
typedef struct qapi_BLE_GATT_Server_Indication_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Attribute handle.
    */
   uint16_t                         AttributeHandle;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;
} qapi_BLE_GATT_Server_Indication_Data_t;

/** Size of the #qapi_BLE_GATT_Server_Indication_Data_t structure. */
#define QAPI_BLE_GATT_SERVER_INDICATION_DATA_SIZE                 (sizeof(qapi_BLE_GATT_Server_Indication_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_MTU_UPDATE_E event.
 */
typedef struct qapi_BLE_GATT_Device_Connection_MTU_Update_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Maximum transmission unit (MTU).
    */
   uint16_t                         MTU;
} qapi_BLE_GATT_Device_Connection_MTU_Update_Data_t;

/** Size of the #qapi_BLE_GATT_Device_Connection_MTU_Update_Data_t structure. */
#define QAPI_BLE_GATT_DEVICE_CONNECTION_MTU_UPDATE_DATA_SIZE      (sizeof(qapi_BLE_GATT_Device_Connection_MTU_Update_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_DATABASE_UPDATE_E event.
 */
typedef struct qapi_BLE_GATT_Connection_Service_Database_Update_Data_s
{
   boolean_t                             ServiceAdded;
    /**<
    * Flags if the GATT database has changed due to the addition of a
    * GATT service. If FALSE, this means that a service has been
    * removed from the GATT database.
    */

   qapi_BLE_GATT_Service_Changed_Data_t  ServiceChangedData;
    /**<
    * Handle range of the region of the GATT database that has been
    * affected.
    */
} qapi_BLE_GATT_Connection_Service_Database_Update_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Service_Database_Update_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_SERVICE_DATABASE_UPDATE_DATA_SIZE (sizeof(qapi_BLE_GATT_Connection_Service_Database_Update_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_READ_REQUEST_E event.
 *
 * It is the responsibility of the application that receives this event
 * to respond with the correct data for each client.
 */
typedef struct qapi_BLE_GATT_Connection_Service_Changed_Read_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;
} qapi_BLE_GATT_Connection_Service_Changed_Read_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Service_Changed_Read_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_SERVICE_CHANGED_READ_DATA_SIZE   (sizeof(qapi_BLE_GATT_Connection_Service_Changed_Read_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CONFIRMATION_E event.
 *
 * If the Status is not equal to
 * #QAPI_BLE_GATT_CONFIRMATION_STATUS_SUCCESS, the Service Changed
 * Indication should be considered to have failed.
 */
typedef struct qapi_BLE_GATT_Connection_Service_Changed_Confirmation_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Status of service changed indication.
    */
   uint8_t                          Status;
} qapi_BLE_GATT_Connection_Service_Changed_Confirmation_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Service_Changed_Confirmation_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_SERVICE_CHANGED_CONFIRMATION_DATA_SIZE (sizeof(qapi_BLE_GATT_Connection_Service_Changed_Confirmation_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_READ_REQUEST_E
 * event.
 *
 * It is the responsibility of the application that receives this event
 * to respond with the correct data for each client.
 */
typedef struct qapi_BLE_GATT_Connection_Service_Changed_CCCD_Read_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;
} qapi_BLE_GATT_Connection_Service_Changed_CCCD_Read_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Service_Changed_CCCD_Read_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_SERVICE_CHANGED_CCCD_READ_DATA_SIZE    (sizeof(qapi_BLE_GATT_Connection_Service_Changed_CCCD_Read_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_UPDATE_E
 * event.
 *
 * It is the responsibility of the application that receives this event
 * to store this value persistently for bonded devices.
 */
typedef struct qapi_BLE_GATT_Connection_Service_Changed_CCCD_Update_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * CCCD value that has been requested to be written.
    */
   uint16_t                         ClientConfigurationValue;
} qapi_BLE_GATT_Connection_Service_Changed_CCCD_Update_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Service_Changed_CCCD_Update_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_SERVICE_CHANGED_CCCD_UPDATE_DATA_SIZE  (sizeof(qapi_BLE_GATT_Connection_Service_Changed_CCCD_Update_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_CLIENT_SUPPORTED_FEATURES_UPDATE_E
 * event.
 *
 * It is the responsibility of the application that receives
 * this event to store this value persistently for bonded
 * devices.
 */
typedef struct qapi_BLE_GATT_Connection_Client_Supported_Features_Update_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Length of the client supported features array.
    */
   uint32_t                         Client_Supported_Features_Length;

   /**
    * Client supported features array.
    */
   uint8_t                         *Client_Supported_Features;
} qapi_BLE_GATT_Connection_Client_Supported_Features_Update_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Client_Supported_Features_Update_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_CLIENT_SUPPORTED_FEATURES_UPDATE_DATA_SIZE  (sizeof(qapi_BLE_GATT_Connection_Client_Supported_Features_Update_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_BONDED_CLIENT_DATA_REQUEST_E
 * event.
 *
 * If data for the specified client exists the upper layer
 * should respond to this event ASAP (at time of reception
 * of this event if possible) with the requested data.
 */
typedef struct qapi_BLE_GATT_Connection_Bonded_Client_Data_Request_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;
} qapi_BLE_GATT_Connection_Bonded_Client_Data_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Bonded_Client_Data_Request_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_BONDED_CLIENT_DATA_REQUEST_DATA_SIZE  (sizeof(qapi_BLE_GATT_Connection_Bonded_Client_Data_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CONNECTION_REMOTE_DATABASE_UPDATED_E
 * event.
 */
typedef struct qapi_BLE_GATT_Connection_Remote_Database_Updated_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;
} qapi_BLE_GATT_Connection_Remote_Database_Updated_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Remote_Database_Updated_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_REMOTE_DATABASE_UPDATED_DATA_SIZE  (sizeof(qapi_BLE_GATT_Connection_Remote_Database_Updated_Data_t))

/**
 * Structure that represents the container structure for holding all the
 * GATT connection event data.
 */
typedef struct qapi_BLE_GATT_Connection_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_GATT_Connection_Event_Type_t  Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                               Event_Data_Size;
   union
   {
      /**
       * GATT device connection request data.
       */
      qapi_BLE_GATT_Device_Connection_Request_Data_t                   *GATT_Device_Connection_Request_Data;

      /**
       * GATT device connection data.
       */
      qapi_BLE_GATT_Device_Connection_Data_t                           *GATT_Device_Connection_Data;

      /**
       * GATT device connection confirmation data.
       */
      qapi_BLE_GATT_Device_Connection_Confirmation_Data_t              *GATT_Device_Connection_Confirmation_Data;

      /**
       * GATT device disconnection data.
       */
      qapi_BLE_GATT_Device_Disconnection_Data_t                        *GATT_Device_Disconnection_Data;

      /**
       * GATT device buffer empty data.
       */
      qapi_BLE_GATT_Device_Buffer_Empty_Data_t                         *GATT_Device_Buffer_Empty_Data;

      /**
       * GATT server notification data.
       */
      qapi_BLE_GATT_Server_Notification_Data_t                         *GATT_Server_Notification_Data;

      /**
       * GATT server indication data.
       */
      qapi_BLE_GATT_Server_Indication_Data_t                           *GATT_Server_Indication_Data;

      /**
       * GATT device connection MTU update data.
       */
      qapi_BLE_GATT_Device_Connection_MTU_Update_Data_t                *GATT_Device_Connection_MTU_Update_Data;

      /**
       * GATT connection service database update data.
       */
      qapi_BLE_GATT_Connection_Service_Database_Update_Data_t          *GATT_Connection_Service_Database_Update_Data;

      /**
       * GATT connection service changed read data.
       */
      qapi_BLE_GATT_Connection_Service_Changed_Read_Data_t             *GATT_Connection_Service_Changed_Read_Data;

      /**
       * GATT connection service changed confirmation data.
       */
      qapi_BLE_GATT_Connection_Service_Changed_Confirmation_Data_t     *GATT_Connection_Service_Changed_Confirmation_Data;

      /**
       * GATT connection service changed CCCD read data.
       */
      qapi_BLE_GATT_Connection_Service_Changed_CCCD_Read_Data_t        *GATT_Connection_Service_Changed_CCCD_Read_Data;

      /**
       * GATT connection service changed CCCD update data.
       */
      qapi_BLE_GATT_Connection_Service_Changed_CCCD_Update_Data_t      *GATT_Connection_Service_Changed_CCCD_Update_Data;

      /**
       * GATT connection service changed CCCD update data.
       */
      qapi_BLE_GATT_Connection_Client_Supported_Features_Update_Data_t *GATT_Connection_Client_Supported_Features_Update_Data;

      /**
       * GATT connection service changed CCCD update data.
       */
      qapi_BLE_GATT_Connection_Bonded_Client_Data_Request_Data_t       *GATT_Connection_Bonded_Client_Data_Request_Data;

      /**
       * GATT connection service changed CCCD update data.
       */
      qapi_BLE_GATT_Connection_Remote_Database_Updated_Data_t          *GATT_Connection_Remote_Database_Updated_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_GATT_Connection_Event_Data_t;

/** Size of the #qapi_BLE_GATT_Connection_Event_Data_t structure. */
#define QAPI_BLE_GATT_CONNECTION_EVENT_DATA_SIZE                  (sizeof(qapi_BLE_GATT_Connection_Event_Data_t))

   /* GATT Server Events. */

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_READ_REQUEST_E event.
 */
typedef struct qapi_BLE_GATT_Read_Request_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * GATT service ID.
    */
   uint32_t                         ServiceID;

   /**
    * Attribute offset.
    */
   uint16_t                         AttributeOffset;

   /**
    * Attribute value offset.
    */
   uint16_t                         AttributeValueOffset;
} qapi_BLE_GATT_Read_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Read_Request_Data_t structure. */
#define QAPI_BLE_GATT_READ_REQUEST_DATA_SIZE                      (sizeof(qapi_BLE_GATT_Read_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_WRITE_REQUEST_E event.
 */
typedef struct qapi_BLE_GATT_Write_Request_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * GATT service ID.
    */
   uint32_t                         ServiceID;

   /**
    * Attribute offset.
    */
   uint16_t                         AttributeOffset;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Attribute value offset.
    */
   uint16_t                         AttributeValueOffset;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;

   /**
    * Flags if this is a GATT write long value request.
    */
   boolean_t                        DelayWrite;
} qapi_BLE_GATT_Write_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Write_Request_Data_t structure. */
#define QAPI_BLE_GATT_WRITE_REQUEST_DATA_SIZE                     (sizeof(qapi_BLE_GATT_Write_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_SIGNED_WRITE_REQUEST_E event.
 */
typedef struct qapi_BLE_GATT_Signed_Write_Request_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                                 ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                                 TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t          ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                       RemoteDevice;

   /**
    * GATT service ID.
    */
   uint32_t                                 ServiceID;

   /**
    * Attribute offset.
    */
   uint16_t                                 AttributeOffset;

   /**
    * Attribute value length.
    */
   uint16_t                                 AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                                 *AttributeValue;

   /**
    * Authentication signature data.
    */
   qapi_BLE_ATT_Authentication_Signature_t  AuthenticationSignature;
} qapi_BLE_GATT_Signed_Write_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Signed_Write_Request_Data_t structure. */
#define QAPI_BLE_GATT_SIGNED_WRITE_REQUEST_DATA_SIZE              (sizeof(qapi_BLE_GATT_Signed_Write_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_EXECUTE_WRITE_REQUEST_E event.
 *
 * No queued writes for the specified GATT client should be committed
 * into the database until the GATT execture write confirmation event is
 * received with the status set to
 * #QAPI_BLE_GATT_EXECUTE_WRITE_CONFIRMATION_STATUS_NO_ERROR.
 *
 * If CancelWrite is TRUE, all pending writes received from the
 * specified GATT client should be discarded.
 */
typedef struct qapi_BLE_GATT_Execute_Write_Request_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * GATT service ID.
    */
   uint32_t                         ServiceID;

   /**
    * Flags if the prepared writes will be written or canceled.
    */
   boolean_t                        CancelWrite;
} qapi_BLE_GATT_Execute_Write_Request_Data_t;

/** Size of the #qapi_BLE_GATT_Execute_Write_Request_Data_t structure. */
#define QAPI_BLE_GATT_EXECUTE_WRITE_REQUEST_DATA_SIZE             (sizeof(qapi_BLE_GATT_Execute_Write_Request_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_EXECUTE_WRITE_CONFIRMATION_E event.
 */
typedef struct qapi_BLE_GATT_Execute_Write_Confirmation_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * GATT service ID.
    */
   uint32_t                         ServiceID;

   /**
    * Status of the GATT Execute Write request indication.
    */
   uint8_t                          Status;
} qapi_BLE_GATT_Execute_Write_Confirmation_Data_t;

/** Size of the #qapi_BLE_GATT_Execute_Write_Confirmation_Data_t structure. */
#define QAPI_BLE_GATT_EXECUTE_WRITE_CONFIRMATION_DATA_SIZE        (sizeof(qapi_BLE_GATT_Execute_Write_Confirmation_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVER_CONFIRMATION_RESPONSE_E event.
 *
 * If the Status is not equal to
 * #QAPI_BLE_GATT_CONFIRMATION_STATUS_SUCCESS, the Handle/Value
 * indication should be considered to have failed.
 *
 * If the Status is equal to QAPI_BLE_GATT_CONFIRMATION_STATUS_SUCCESS
 * then the BytesWritten member will contain the number of data bytes
 * that were actually indicated.
 */
typedef struct qapi_BLE_GATT_Confirmation_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Status of the outstanding indication.
    */
   uint8_t                          Status;

   /**
    * Number of bytes successfully indicated.
    */
   uint16_t                         BytesWritten;
} qapi_BLE_GATT_Confirmation_Data_t;

/** Size of the #qapi_BLE_GATT_Confirmation_Data_t structure. */
#define QAPI_BLE_GATT_CONFIRMATION_DATA_SIZE                      (sizeof(qapi_BLE_GATT_Confirmation_Data_t))

/**
 * Structure that represents the container structure for holding all the
 * GATT server event data.
 */
typedef struct qapi_BLE_GATT_Server_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_GATT_Server_Event_Type_t  Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                           Event_Data_Size;
   union
   {
      /**
       * GATT device connection data.
       */
      qapi_BLE_GATT_Device_Connection_Data_t            *GATT_Device_Connection_Data;

      /**
       * GATT device disconnection data.
       */
      qapi_BLE_GATT_Device_Disconnection_Data_t         *GATT_Device_Disconnection_Data;

      /**
       * GATT device buffer empty data.
       */
      qapi_BLE_GATT_Device_Buffer_Empty_Data_t          *GATT_Device_Buffer_Empty_Data;

      /**
       * GATT device connection MTU update data.
       */
      qapi_BLE_GATT_Device_Connection_MTU_Update_Data_t *GATT_Device_Connection_MTU_Update_Data;

      /**
       * GATT read request data.
       */
      qapi_BLE_GATT_Read_Request_Data_t                 *GATT_Read_Request_Data;

      /**
       * GATT write request data.
       */
      qapi_BLE_GATT_Write_Request_Data_t                *GATT_Write_Request_Data;

      /**
       * GATT signed write request data.
       */
      qapi_BLE_GATT_Signed_Write_Request_Data_t         *GATT_Signed_Write_Request_Data;

      /**
       * GATT execute write request data.
       */
      qapi_BLE_GATT_Execute_Write_Request_Data_t        *GATT_Execute_Write_Request_Data;

      /**
       * GATT execute write request confirmation data.
       */
      qapi_BLE_GATT_Execute_Write_Confirmation_Data_t   *GATT_Execute_Write_Confirmation_Data;

      /**
       * GATT confirmation data.
       */
      qapi_BLE_GATT_Confirmation_Data_t                 *GATT_Confirmation_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_GATT_Server_Event_Data_t;

/** Size of the #qapi_BLE_GATT_Server_Event_Data_t structure. */
#define QAPI_BLE_GATT_SERVER_EVENT_DATA_SIZE                      (sizeof(qapi_BLE_GATT_Server_Event_Data_t))

   /* GATT Client Event types. */

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_ERROR_RESPONSE_E event.
 *
 * The RequestHandle and ErrorCode members are valid only if the
 * Error_Type member is QAPI_BLE_RET_ERROR_RESPONSE_E.
 */
typedef struct qapi_BLE_GATT_Request_Error_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                            ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                            TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t     ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                  RemoteDevice;

   /**
    * Error type that has occured.
    */
   qapi_BLE_GATT_Request_Error_Type_t  ErrorType;

   /**
    * Op code for the request that caused the error.
    */
   uint8_t                             RequestOpCode;

   /**
    * Attribute handle for the request that caused the error.
    */
   uint16_t                            RequestHandle;

   /**
    * Error that occured.
    */
   uint8_t                             ErrorCode;
} qapi_BLE_GATT_Request_Error_Data_t;

/** Size of the #qapi_BLE_GATT_Request_Error_Data_t structure. */
#define QAPI_BLE_GATT_REQUEST_ERROR_DATA_SIZE                     (sizeof(qapi_BLE_GATT_Request_Error_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Service_Discovery_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                             ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                             TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t      ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                   RemoteDevice;

   /**
    * Number of services discovered.
    */
   uint16_t                             NumberOfServices;

   /**
    * Pointer to the service information list.
    */
   qapi_BLE_GATT_Service_Information_t *ServiceInformationList;
} qapi_BLE_GATT_Service_Discovery_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Discovery_Response_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_RESPONSE_DATA_SIZE        (sizeof(qapi_BLE_GATT_Service_Discovery_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_BY_UUID_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Service_Discovery_By_UUID_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                                     ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                                     TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t              ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                           RemoteDevice;

   /**
    * Number of services discovered.
    */
   uint16_t                                     NumberOfServices;

   /**
    * Pointer to the service information list.
    */
   qapi_BLE_GATT_Service_Information_By_UUID_t *ServiceInformationList;
} qapi_BLE_GATT_Service_Discovery_By_UUID_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Discovery_By_UUID_Response_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_BY_UUID_RESPONSE_DATA_SIZE (sizeof(qapi_BLE_GATT_Service_Discovery_By_UUID_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Included_Services_Discovery_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                             ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                             TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t      ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                   RemoteDevice;

   /**
    * Number of included services.
    */
   uint16_t                             NumberOfIncludes;

   /**
    * Pointer to the included service information list.
    */
   qapi_BLE_GATT_Include_Information_t *IncludeInformationList;
} qapi_BLE_GATT_Included_Services_Discovery_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Included_Services_Discovery_Response_Data_t structure. */
#define QAPI_BLE_GATT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_DATA_SIZE (sizeof(qapi_BLE_GATT_Included_Services_Discovery_Response_Data_t))

/**
 * Structure that represents the data that is in a characteristic
 * declaration value entry.
 */
typedef struct qapi_BLE_GATT_Characteristic_Value_s
{
   /**
    * GATT Characteristic properties.
    */
   uint8_t               CharacteristicProperties;

   /**
    * GATT Characteristic attribute handle.
    */
   uint16_t              CharacteristicValueHandle;

   /**
    * GATT Characteristic UUID.
    */
   qapi_BLE_GATT_UUID_t  CharacteristicUUID;
} qapi_BLE_GATT_Characteristic_Value_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Value_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_VALUE_SIZE                   (sizeof(qapi_BLE_GATT_Characteristic_Value_t))

/**
 * Structure that represents the data that is contained in a
 * characteristic entry.
 */
typedef struct qapi_BLE_GATT_Characteristic_Entry_s
{
   /**
    * GATT Characteristic declaration attribute handle.
    */
   uint16_t                              DeclarationHandle;

   /**
    * GATT Characteristic information.
    */
   qapi_BLE_GATT_Characteristic_Value_t  CharacteristicValue;
} qapi_BLE_GATT_Characteristic_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_ENTRY_SIZE                   (sizeof(qapi_BLE_GATT_Characteristic_Entry_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DISCOVERY_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Characteristic_Discovery_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                              ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                              TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t       ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                    RemoteDevice;

   /**
    * Number of GATT Characteristics.
    */
   uint16_t                              NumberOfCharacteristics;

   /**
    * Pointer to the GATT Characteristic entry list.
    */
   qapi_BLE_GATT_Characteristic_Entry_t *CharacteristicEntryList;
} qapi_BLE_GATT_Characteristic_Discovery_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Discovery_Response_Data_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DISCOVERY_RESPONSE_DATA_SIZE (sizeof(qapi_BLE_GATT_Characteristic_Discovery_Response_Data_t))

/**
 * Structure that represents the data that is in a characteristic
 * descriptor discovery event entry.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_Entry_s
{
   /**
    * GATT Characteristic Descriptor attribute handle.
    */
   uint16_t              Handle;

   /**
    * GATT Characteristic Descriptor UUID.
    */
   qapi_BLE_GATT_UUID_t  UUID;
} qapi_BLE_GATT_Characteristic_Descriptor_Entry_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_Entry_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_ENTRY_SIZE        (sizeof(qapi_BLE_GATT_Characteristic_Descriptor_Entry_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_DISCOVERY_RESPONSE_E
 * event.
 */
typedef struct qapi_BLE_GATT_Characteristic_Descriptor_Discovery_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t                  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                               RemoteDevice;

   /**
    * Number of GATT Characteristic Descriptors.
    */
   uint16_t                                         NumberOfCharacteristicDescriptors;

   /**
    * Pointer to the GATT Characteristic Descriptor entry list.
    */
   qapi_BLE_GATT_Characteristic_Descriptor_Entry_t *CharacteristicDescriptorEntryList;
} qapi_BLE_GATT_Characteristic_Descriptor_Discovery_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Characteristic_Descriptor_Discovery_Response_Data_t structure. */
#define QAPI_BLE_GATT_CHARACTERISTIC_DESCRIPTOR_DISCOVERY_RESPONSE_DATA_SIZE (sizeof(QAPI_BLE_GATT_Characteristic_Descriptor_Discovery_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_READ_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Read_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;
} qapi_BLE_GATT_Read_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Read_Response_Data_t structure. */
#define QAPI_BLE_GATT_READ_RESPONSE_DATA_SIZE                     (sizeof(qapi_BLE_GATT_Read_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_READ_LONG_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Read_Long_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;
} qapi_BLE_GATT_Read_Long_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Read_Long_Response_Data_t structure. */
#define QAPI_BLE_GATT_READ_LONG_RESPONSE_DATA_SIZE                (sizeof(qapi_BLE_GATT_Read_Long_Response_Data_t))

/**
 * Structure that represents the structure of a GATT read response event
 * entry.
 */
typedef struct qapi_BLE_GATT_Read_Event_Entry_s
{
   /**
    * GATT attribute handle.
    */
   uint16_t  AttributeHandle;

   /**
    * GATT attribute value length.
    */
   uint16_t  AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t  *AttributeValue;
} qapi_BLE_GATT_Read_Event_Entry_t;

/** Size of the #qapi_BLE_GATT_Read_Event_Entry_t structure. */
#define QAPI_BLE_GATT_READ_EVENT_ENTRY_SIZE                       (sizeof(qapi_BLE_GATT_Read_Event_Entry_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_READ_BY_UUID_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Read_By_UUID_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                          ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                          TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t   ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                RemoteDevice;

   /**
    * Number of GATT attributes.
    */
   uint16_t                          NumberOfAttributes;

   /**
    * Pointer to the GATT attribute entry list.
    */
   qapi_BLE_GATT_Read_Event_Entry_t *AttributeList;
} qapi_BLE_GATT_Read_By_UUID_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Read_By_UUID_Response_Data_t structure. */
#define QAPI_BLE_GATT_READ_BY_UUID_RESPONSE_DATA_SIZE             (sizeof(qapi_BLE_GATT_Read_By_UUID_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_READ_MULTIPLE_RESPONSE_E event.
 *
 * The AttributeValuesLength is the TOTAL length (in bytes) of ALL
 * attribute values, not the length of an individual attribute value.
 */
typedef struct qapi_BLE_GATT_Read_Multiple_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValuesLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValues;
} qapi_BLE_GATT_Read_Multiple_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Read_Multiple_Response_Data_t structure. */
#define QAPI_BLE_GATT_READ_MULTIPLE_RESPONSE_DATA_SIZE            (sizeof(qapi_BLE_GATT_Read_Multiple_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_WRITE_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Write_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Number of bytes successfully written.
    */
   uint32_t                         BytesWritten;
} qapi_BLE_GATT_Write_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Write_Response_Data_t structure. */
#define QAPI_BLE_GATT_WRITE_RESPONSE_DATA_SIZE                    (sizeof(qapi_BLE_GATT_Write_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_PREPARE_WRITE_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Prepare_Write_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                         TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * Number of bytes successfully written.
    */
   uint32_t                         BytesWritten;

   /**
    * Attribute handle.
    */
   uint16_t                         AttributeHandle;

   /**
    * Attribute value offset.
    */
   uint16_t                         AttributeValueOffset;

   /**
    * Attribute value length.
    */
   uint16_t                         AttributeValueLength;

   /**
    * Pointer to the attribute value.
    */
   uint8_t                         *AttributeValue;
} qapi_BLE_GATT_Prepare_Write_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Prepare_Write_Response_Data_t structure. */
#define QAPI_BLE_GATT_PREPARE_WRITE_RESPONSE_DATA_SIZE            (sizeof(qapi_BLE_GATT_Prepare_Write_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_EXECUTE_WRITE_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Execute_Write_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                        ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                        TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;
} qapi_BLE_GATT_Execute_Write_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Execute_Write_Response_Data_t structure. */
#define QAPI_BLE_GATT_EXECUTE_WRITE_RESPONSE_DATA_SIZE            (sizeof(qapi_BLE_GATT_Execute_Write_Response_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E event.
 */
typedef struct qapi_BLE_GATT_Exchange_MTU_Response_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                        ConnectionID;

   /**
    * GATT transaction ID.
    */
   uint32_t                        TransactionID;

   /**
    * GATT connection type.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;

   /**
    * GATT server maximum transmission unit (MTU).
    */
   uint16_t                        ServerMTU;
} qapi_BLE_GATT_Exchange_MTU_Response_Data_t;

/** Size of the #qapi_BLE_GATT_Exchange_MTU_Response_Data_t structure.*/
#define QAPI_BLE_GATT_EXCHANGE_MTU_RESPONSE_DATA_SIZE      (sizeof(qapi_BLE_GATT_Exchange_MTU_Response_Data_t))

/**
 * Structure that represents the container structure for holding all the
 * GATT client event data.
 */
typedef struct qapi_BLE_GATT_Client_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_GATT_Client_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                          Event_Data_Size;
   union
   {
      /**
       * GATT request error data.
       */
      qapi_BLE_GATT_Request_Error_Data_t                                *GATT_Request_Error_Data;

      /**
       * GATT service discovery response data.
       */
      qapi_BLE_GATT_Service_Discovery_Response_Data_t                   *GATT_Service_Discovery_Response_Data;

      /**
       * GATT service discovery by UUID response data.
       */
      qapi_BLE_GATT_Service_Discovery_By_UUID_Response_Data_t           *GATT_Service_Discovery_By_UUID_Response_Data;

      /**
       * GATT included service discovery response data.
       */
      qapi_BLE_GATT_Included_Services_Discovery_Response_Data_t         *GATT_Included_Services_Discovery_Response_Data;

      /**
       * GATT Characteristic discovery response data.
       */
      qapi_BLE_GATT_Characteristic_Discovery_Response_Data_t            *GATT_Characteristic_Discovery_Response_Data;

      /**
       * GATT Characteristic Descriptor discovery response data.
       */
      qapi_BLE_GATT_Characteristic_Descriptor_Discovery_Response_Data_t *GATT_Characteristic_Descriptor_Discovery_Response_Data;

      /**
       * GATT Read response data.
       */
      qapi_BLE_GATT_Read_Response_Data_t                                *GATT_Read_Response_Data;

      /**
       * GATT Read by UUID response data.
       */
      qapi_BLE_GATT_Read_By_UUID_Response_Data_t                        *GATT_Read_By_UUID_Response_Data;

      /**
       * GATT Read Long response data.
       */
      qapi_BLE_GATT_Read_Long_Response_Data_t                           *GATT_Read_Long_Response_Data;

      /**
       * GATT Read Multiple response data.
       */
      qapi_BLE_GATT_Read_Multiple_Response_Data_t                       *GATT_Read_Multiple_Response_Data;

      /**
       * GATT Write response data.
       */
      qapi_BLE_GATT_Write_Response_Data_t                               *GATT_Write_Response_Data;

      /**
       * GATT Prepare Write response data.
       */
      qapi_BLE_GATT_Prepare_Write_Response_Data_t                       *GATT_Prepare_Write_Response_Data;

      /**
       * GATT Execute Write response data.
       */
      qapi_BLE_GATT_Execute_Write_Response_Data_t                       *GATT_Execute_Write_Response_Data;

      /**
       * GATT Exchange MTU response data.
       */
      qapi_BLE_GATT_Exchange_MTU_Response_Data_t                        *GATT_Exchange_MTU_Response_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_GATT_Client_Event_Data_t;

/** Size of the #qapi_BLE_GATT_Client_Event_Data_t structure. */
#define QAPI_BLE_GATT_CLIENT_EVENT_DATA_SIZE                      (sizeof(qapi_BLE_GATT_Client_Event_Data_t))

   /* GATT Service Discovery Event types. */

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E event.
 */
typedef struct qapi_BLE_GATT_Service_Discovery_Indication_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                                    ConnectionID;

   /**
    * GATT service information.
    */
   qapi_BLE_GATT_Service_Information_t         ServiceInformation;

   /**
    * Number of included services.
    */
   uint32_t                                    NumberOfIncludedService;

   /**
    * Pointer to the included service information.
    */
   qapi_BLE_GATT_Service_Information_t        *IncludedServiceList;

   /**
    * Number of GATT Characteristics for the service.
    */
   uint32_t                                    NumberOfCharacteristics;

   /**
    * Pointer to the GATT Characteristic information list.
    */
   qapi_BLE_GATT_Characteristic_Information_t *CharacteristicInformationList;
} qapi_BLE_GATT_Service_Discovery_Indication_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Discovery_Indication_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_INDICATION_DATA_SIZE      (sizeof(qapi_BLE_GATT_Service_Discovery_Indication_Data_t))

/**
 * Structure that represents the data returned in a GATT
 * #QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E event.
 */
typedef struct qapi_BLE_GATT_Service_Discovery_Complete_Data_s
{
   /**
    * GATT connection ID.
    */
   uint32_t                  ConnectionID;

   /**
    * Status of the GATT service discovery procedure.
    */
   uint8_t                   Status;

   /**
    * Indicates if the database hash is valid.
    */
   boolean_t                 Database_Hash_Valid;

   /**
    * Database hash.
    */
   qapi_BLE_Encrypted_Data_t Database_Hash;
} qapi_BLE_GATT_Service_Discovery_Complete_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Discovery_Complete_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_COMPLETE_DATA_SIZE        (sizeof(qapi_BLE_GATT_Service_Discovery_Complete_Data_t))

   /* The following define the valid values that the Status member of */
   /* the qapi_BLE_GATT_Service_Discovery_Complete_Data_t may be set to.*/

/** GATT service discovery succeeded. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_STATUS_SUCCESS             0x00

/** GATT service discovery failed for the response. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_STATUS_RESPONSE_ERROR      0x01

/** GATT service discovery timed out. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_STATUS_RESPONSE_TIMEOUT    0x02

/** GATT service discovery failed for an unknown reason. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_STATUS_UNKNOWN_ERROR       0x03


/**
 * Structure that represents the container structure for holding all the
 * GATT service discovery event data.
 */
typedef struct qapi_BLE_GATT_Service_Discovery_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_GATT_Service_Discovery_Event_Type_t  Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                                      Event_Data_Size;
   union
   {
      /**
       * GATT service discovery indication data.
       */
      qapi_BLE_GATT_Service_Discovery_Indication_Data_t *GATT_Service_Discovery_Indication_Data;

      /**
       * GATT service discovery complete data.
       */
      qapi_BLE_GATT_Service_Discovery_Complete_Data_t   *GATT_Service_Discovery_Complete_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_GATT_Service_Discovery_Event_Data_t;

/** Size of the #qapi_BLE_GATT_Service_Discovery_Event_Data_t structure. */
#define QAPI_BLE_GATT_SERVICE_DISCOVERY_EVENT_DATA_SIZE           (sizeof(qapi_BLE_GATT_Service_Discovery_Event_Data_t))

/**
 * @brief
 * This declared type represents the prototype function for
 * a GATT connection event callback. This function will be called
 * whenever a GATT connection event occurs that is associated with the
 * specified Bluetooth stack ID.

 * @details
 * The caller should use the contents of the GATT Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, then the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have be reentrant). . It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another GATT Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID              Unique identifier assigned
 *                                           to this Bluetooth Protocol
 *                                           Stack on which the event
 *                                           occurred.
 *
 * @param[in]  GATT_Connection_Event_Data    Pointer to a structure that
 *                                           contains information about
 *                                           the event that has occurred.
 *
 * @param[in]  CallbackParameter             User-defined value that was
 *                                           supplied as an input
 *                                           parameter from a prior GATT
 *                                           request.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_GATT_Connection_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Event_Data_t *GATT_Connection_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the prototype function for
 * GATT server event callback. This function will be called whenever
 * a GATT server event occurs that is associated with the specified
 * Bluetooth stack ID.
 *
 * @details
 * The caller should use the contents of the GATT Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have be reentrant). It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another GATT Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID          Unique identifier assigned to
 *                                       this Bluetooth Protocol Stack on
 *                                       which the event occurred.
 *
 * @param[in]  GATT_Server_Event_Data    Pointer to a structure that
 *                                       contains information about the
 *                                       event that has occurred.
 *
 * @param[in]  CallbackParameter         User-defined value that was
 *                                       supplied as an input parameter
 *                                       from a prior GATT request.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_GATT_Server_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_GATT_Server_Event_Data_t *GATT_Server_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the prototype function for a
 * GATT client event callback. This function will be called whenever
 * a GATT server event occurs that is associated with the specified
 * Bluetooth stack ID.
 *
 * @details
 * The caller should use the contents of the GATT Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have be reentrant). It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another GATT Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID          Unique identifier assigned to
 *                                       this Bluetooth Protocol Stack on
 *                                       which the event occurred.
 *
 * @param[in]  GATT_Client_Event_Data    Pointer to a structure that
 *                                       contains information about the
 *                                       event that has occurred.
 *
 * @param[in]  CallbackParameter         User-defined value that was
 *                                       supplied as an input parameter
 *                                       from a prior GATT request.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_GATT_Client_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_GATT_Client_Event_Data_t *GATT_Client_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the prototype function for
 * GATT Service Discovery Event data callback. This function will be
 * called whenever a GATT server event occurs that is associated with
 * the specified Bluetooth stack ID.
 *
 * @details
 * The caller should use the contents of the GATT Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have be reentrant). It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another GATT Service Discovery Event will not be processed
 * while this function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID                     Unique identifier
 *                                                  assigned to this
 *                                                  Bluetooth Protocol
 *                                                  Stack on which the
 *                                                  event occurred.
 *
 * @param[in]  GATT_Service_Discovery_Event_Data    Pointer to a
 *                                                  structure that
 *                                                  contains information
 *                                                  about the event that
 *                                                  has occurred.
 *
 * @param[in]  CallbackParameter                    User-defined value that
 *                                                  was supplied as an
 *                                                  input parameter from
 *                                                  a prior GATT request.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_GATT_Service_Discovery_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_GATT_Service_Discovery_Event_Data_t *GATT_Service_Discovery_Event_Data, unsigned long CallbackParameter);

   /* GATT General API. */

/**
 * @brief
 * Initializes the GATT.
 *
 * @details
 * This function must be called before any other GATT profile function
 * may be called. This function can only be called once per stack
 * instance.
 *
 * The Flags parameter must be made up of bitmasks of the form
 * QAPI_BLE_GATT_INITIALIZATION_FLAGS_SUPPORT_XXX AND cannot be ZERO.
 *
 * The specified callback will receive all the of the defined
 * connection events. This is in contrast to the callback registered
 * with the qapi_BLE_GATT_Register_Connection_Events() function, which
 * will receive all connection events except:
 *
 *    QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E
 *
 * It should be noted that the connection request event
 * is only applicable to BR/EDR devices (that is, not to LE
 * devices).
 *
 * @param[in]  BluetoothStackID           Unique identifier assigned to
 *                                        this Bluetooth Protocol Stack
 *                                        via a call to
 *                                        qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Flags                      Initialization flags bitmask.
 *                                        This value must be one (or
 *                                        more) of the following bitmask
 *                                           constant flags: \n
 *                                           #QAPI_BLE_GATT_INITIALIZATION_FLAGS_SUPPORT_LE
 *                                           \n
 *                                           QAPI_BLE_GATT_INITIALIZATION_FLAGS_SUPPORT_BR_EDR
 *
 * @param[in]  ConnectionEventCallback    Callback function that is
 *                                        registered to receive
 *                                        connection events.
 *
 *
 * @param[in]  CallbackParameter          User-defined parameter (e.g.,
 *                                        a tag value) that will be
 *                                        passed back to the user in the
 *                                        callback function with each
 *                                        connection event.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_CONTEXT_ALREADY_EXISTS \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Initialize(uint32_t BluetoothStackID, unsigned long Flags, qapi_BLE_GATT_Connection_Event_Callback_t ConnectionEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Cleans up a previously initialized GATT instance.
 *
 * @details
 * After calling this function, qapi_BLE_GATT_Initialize() must be
 * called for the GATT using the specified Bluetooth stack again before
 * any other GATT function can be called.
 *
 * Possible events:
 *
 *  @li  QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E
 *  @li  QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_E
 *  @li  QAPI_BLE_ET_GATT_CONNECTION_DEVICE_DISCONNECTION_E
 *  @li  QAPI_BLE_ET_GATT_CONNECTION_SERVER_INDICATION_E
 *  @li  QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Cleanup(uint32_t BluetoothStackID);

   /* GATT Connection API. */

/**
 * @brief
 * Registers
 * an event callback to monitor device connection and server indication
 * events.
 *
 * @details
 * A successful return value from this function represents
 * the Event Callback ID. This value can be passed to the
 * qapi_BLE_GATT_Un_Register_Connection_Events() function to un-register
 * this callback.
 *
 * The specified callback will receive all of the defined connection
 * events except:
 *
 *  @li QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_REQUEST_E
 *  @li QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_READ_REQUEST_E
 *
 *  * Possible events:
 *
 *   @li QAPI_BLE_ET_GATT_CONNECTION_DEVICE_CONNECTION_E
 *   @li QAPI_BLE_ET_GATT_CONNECTION_DEVICE_DISCONNECTION_E
 *   @li QAPI_BLE_ET_GATT_CONNECTION_SERVER_INDICATION_E
 *   @li QAPI_BLE_ET_GATT_CONNECTION_SERVER_NOTIFICATION_E
 *
 * @param[in]  BluetoothStackID           Unique identifier assigned to
 *                                        this Bluetooth Protocol Stack
 *                                        via a call to
 *                                        qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionEventCallback    Callback function that is
 *                                        registered to receive
 *                                        connection events.
 *
 * @param[in]  CallbackParameter          User-defined parameter (e.g.,
 *                                        a tag value) that will be
 *                                        passed back to the user in the
 *                                        callback function with each
 *                                        connection event.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the event connection callback ID value that can be passed to
 *              the connection event un-registration function to un-register
 *              the callback.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Register_Connection_Events(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Event_Callback_t ConnectionEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Unregisterd a previously registered connect event callback (registered
 * via a successful call to the qapi_BLE_GATT_Register_Connection_Events()
 * function).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallbackID     Event callback ID of the event
 *                                 callback to unregister. This value
 *                                 was obtained via the successful return
 *                                 value from calling the
 *                                 qapi_BLE_GATT_Register_Connection_Events()
 *                                 function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Un_Register_Connection_Events(uint32_t BluetoothStackID, uint32_t EventCallbackID);

   /* GATT Server API. */

/**
 * @brief
 * Registers a GATT service with the local GATT server.
 *
 * @details
 * This function registers a service with the specified service
 * attributes with the local GATT server. This function will return
 * the unique service ID which is used to identify the service as well
 * as the starting and ending attribute handles of the service in the
 * local GATT service.
 *
 * The first entry in the array pointed to by service will be allocated
 * with the starting handle specified in the ServiceHandleGroupResult
 * structure. The second entry will be allocated at the starting
 * Handle + 1, and so on.
 *
 * ServiceFlags is a bitmask that is made up of bitmasks of
 * the form QAPI_BLE_GATT_SERVICE_FLAGS_XXX. The ServicesFlags
 * may not be zero, that is, at least one
 * QAPI_BLE_GATT_SERVICE_FLAGS_XXX must be set for this call
 * to succeed.
 *
 * The ServiceHandleGroupResult parameter is both an input and an
 * output parameter. If the following test is TRUE (and Starting_Handle
 * and Ending_Handle members are greater than zero), the GATT
 * layer will attempt to assign the service into the specified
 * location in the service table:
 *
 *             ServiceHandleGroupResult->Ending_Handle ==
 *               (ServiceHandleGroupResult->Starting_Handle +
 *               (NumberOfServiceAttributeEntries - 1))
 *
 * If the specified location is not available, this function will
 * return the error code QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_HANDLES.
 *
 * The Service Table passed to this function is stored as a
 * reference and as such its associated memory must be maintained
 * by the application until the service has been removed via a call
 * to qapi_BLE_GATT_Un_Register_Service().
 *
 * @param[in]  BluetoothStackID                   Unique identifier
 *                                                assigned to this
 *                                                Bluetooth Protocol
 *                                                Stack via a call to
 *                                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceFlags                       Specifies the current
 *                                                service flags to apply
 *                                                to the registered
 *                                                service. The value of
 *                                                this parameter is a
 *                                                bitmask of zero or
 *                                                more of the
 *                                                following values: \n
 *                                                #QAPI_BLE_GATT_SERVICE_FLAGS_LE_SERVICE
 *                                                \n
 *                                                QAPI_BLE_GATT_SERVICE_FLAGS_BR_EDR_SERVICE
 *
 * @param[in]  NumberOfServiceAttributeEntries    Specifies the total
 *                                                number of service
 *                                                attribute entries that
 *                                                are contained in the
 *                                                ServiceTable parameter.
 *
 * @param[in]  ServiceTable                       Pointer to an array of
 *                                                service attribute
 *                                                entries that specify
 *                                                all of the service
 *                                                attributes for the
 *                                                registered service.
 *
 * @param[in,out]  ServiceHandleGroupResult       This parameter is both
 *                                                an input and output
 *                                                parameter. On input,
 *                                                this parameter can be
 *                                                used to request that
 *                                                GATT place the service
 *                                                at a specific handle
 *                                                range in the GATT
 *                                                database. This is
 *                                                accomplished by setting
 *                                                the Starting_Handle and
 *                                                Ending_Handle members
 *                                                of this structure to
 *                                                the requested handle
 *                                                range in the GATT
 *                                                database. If these
 *                                                members are zero, or
 *                                                otherwise invalid on
 *                                                input, the GATT
 *                                                layer will place the
 *                                                service in the first
 *                                                available region in the
 *                                                GATT database. On
 *                                                output, GATT will return
 *                                                the handle range of the
 *                                                registered service if
 *                                                this function returns
 *                                                success.
 *
 * @param[in]  ServerEventCallback                Callback function that
 *                                                is registered to
 *                                                receive events that are
 *                                                associated with the
 *                                                specified service.
 *
 * @param[in]  CallbackParameter                  User-defined
 *                                                parameter (e.g., a tag
 *                                                value) that will be
 *                                                passed back to the user
 *                                                in the callback
 *                                                function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents the
 *              service ID that uniquely identifies the service in the local GATT
 *              database.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Register_Service(uint32_t BluetoothStackID, uint8_t ServiceFlags, uint32_t NumberOfServiceAttributeEntries, qapi_BLE_GATT_Service_Attribute_Entry_t *ServiceTable, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroupResult, qapi_BLE_GATT_Server_Event_Callback_t ServerEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Unregisters a previously registered
 * GATT service that was registered via a successful call to
 * the qapi_BLE_GATT_Register_Service() function.
 *
 * @details
 * This function will free all resources that are being utilized by the
 * service being removed from the GATT database.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceID           Specifies the service ID of the
 *                                 service that is to be removed. This
 *                                 value is the successful return value
 *                                 from the call to
 *                                 GATT_Register_Service.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_GATT_Un_Register_Service(uint32_t BluetoothStackID, uint32_t ServiceID);

/**
 * @brief
 * Responds
 * with a successful response to a received
 * #QAPI_BLE_ET_GATT_SERVER_READ_REQUEST_E event.
 *
 * @details
 * This function only allows a successful response to be sent. If an
 * error response is required, the qapi_BLE_GATT_Error_Response()
 * function should be used to respond with the error information.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the
 *                                 original read request. This
 *                                 value was received in the
 *                                 etGATT_Server_Read_Request
 *                                 event.
 *
 * @param[in]  DataLength          Specifies the amount of data to
 *                                 return. This is the amount of data (in
 *                                 bytes) pointed to by the Data
 *                                 parameter.
 *
 * @param[in]  Data                Specifies the buffer that contains the
 *                                 data to return in the read response.
 *                                 This buffer must point to a buffer that
 *                                 contains (at least) as many bytes as
 *                                 specified by the DataLength parameter.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint32_t DataLength, uint8_t *Data);

/**
 * @brief
 * Provides a mechanism for a service handler to
 * successfully respond to a received GATT/ATT write request
 *(QAPI_BLE_ET_GATT_SERVER_WRITE_REQUEST_E) event.
 *
 * @details
 * This function only allows a successful response to be sent. If an
 * error response is required, then the qapi_BLE_GATT_Error_Response()
 * function should be used to respond with the error information.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the
 *                                 original read request. This
 *                                 value was received in the
 *                                 etGATT_Server_Read_Request
 *                                 event.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Response(uint32_t BluetoothStackID, uint32_t TransactionID);

/**
 * @brief
 * Provides a mechanism for a service handler to
 * successfully respond to a received GATT/ATT execute write request
 * (#QAPI_BLE_ET_GATT_SERVER_EXECUTE_WRITE_REQUEST_E) event.
 *
 * @details
 * This function only allows a successful response to be sent. If an
 * error response is required, then the qapi_BLE_GATT_Error_Response()
 * function should be used to respond with the error information.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the
 *                                 original read request. This
 *                                 value was received in the
 *                                 etGATT_Server_Read_Request
 *                                 event.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Execute_Write_Response(uint32_t BluetoothStackID, uint32_t TransactionID);

/**
 * @brief
 * Provides a mechanism for a service handler
 * to respond to a received GATT/ATT request with an error response.
 *
 * @details
 * The AttributeOffset parameter must be less than or equal to the
 * last index in the service table that was registered in the call
 * to the qapi_BLE_GATT_Register_Service() function.
 *
 * The ErrorCode variable should be one of the
 * QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX values.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the
 *                                 original read request. This
 *                                 value was received in the
 *                                 etGATT_Server_Read_Request
 *                                 event.
 *
 * @param[in]  AttributeOffset     Attribute offset of the first
 *                                 attribute that causes the error.
 *                                 This value will be greater than
 *                                 or equal to zero (specifies the
 *                                 very first attribute in the
 *                                 service) and less than the maximum
 *                                 number of attributes contained in
 *                                 the service.
 *
 * @param[in]  ErrorCode           Error code to return as a response
 *                                 to the request. This may be one of
 *                                 the following values: \n
 *                                 QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX,
 *                                 where XXX indicates the error.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Error_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint16_t AttributeOffset, uint8_t ErrorCode);

/**
 * @brief
 * Provides a mechanism for a service handler
 * to send a GATT attribute handle/value indication to a remote,
 * connected, GATT client.
 *
 * @details
 * Indications require the client to acknowledge that the indication was
 * received. This will be signified by the reception of the
 * etGATT_Server_Confirmation_Response event, which will also include
 * the total number of bytes that were indicated.
 *
 * The ServiceID parameter must have been returned from a successful
 * call to the qapi_BLE_GATT_Register_Service() function.
 *
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the Indication.
 *
 * A QAPI_BLE_ET_GATT_SERVER_CONFIRMATION_RESPONSE_E event will
 * be dispatched to the registered service event callback when
 * the indication is acknowledged by the remote device.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceID               Service ID of the service that is
 *                                     sending the indication. Returned in
 *                                     a successfull call to
 *                                     qapi_BLE_GATT_Register_Service().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote client device to
 *                                     send the handle/value indication.
 *
 * @param[in]  AttributeOffset         Attribute offset of the first
 *                                     attribute that causes the error.
 *                                     This value will be greater than
 *                                     or equal to zero (specifies the
 *                                     very first attribute in the
 *                                     service) and less than the maximum
 *                                     number of attributes contained in
 *                                     the service.
 *
 * @param[in]  AttributeValueLength    Length (in bytes) of the attribute
 *                                     value data that is to be indicated.
 *
 * @param[in]  AttributeValue          Buffer that contains the value
 *                                     data to be indicated. This buffer
 *                                     must contain (at least) the number
 *                                     of bytes specified by the
 *                                     AttributeValueLength parameter.
 *
 * @return
 * Positive, nonzero value -- If successful. This value
 *              represents the transaction ID of the handle/value
 *              indication transaction. This value can be passed
 *              to the qapi_BLE_GATT_Cancel_Transaction() function to
 *              cancel the indication (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Indication(uint32_t BluetoothStackID, uint32_t ServiceID, uint32_t ConnectionID, uint16_t AttributeOffset, uint16_t AttributeValueLength, uint8_t *AttributeValue);

/**
 * @brief
 * Provides a mechanism for a service handler
 * to send a GATT attribute handle/value indication to a remote,
 * connected, GATT client.
 *
 * @details
 * Notifications do not require the client to acknowledge that the
 * notification was received.
 *
 * The ServiceID parameter must have been returned from a successful
 * call to the qapi_BLE_GATT_Register_Service() function.
 *
 * If a successful return value is returned, it will be greater
 * than zero and less than or equal to AttributeValueLength
 * parameter.
 *
 * If this function returns the Error Code
 * QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE, this is a
 * signal that the queueing limits have been exceeded for the
 * specified connection. The caller must then wait for the
 * #QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E event before
 * sending any unacknowledged packets to the specified device.
 * See the qapi_BLE_GATT_Set_Queuing_Parameters() function for
 * more information.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceID               Service ID of the service that is
 *                                     sending the indication. Returned in
 *                                     a successfull call to
 *                                     qapi_BLE_GATT_Register_Service().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote client device to
 *                                     send the handle/value indication.
 *
 * @param[in]  AttributeOffset         Attribute offset of the first
 *                                     attribute that causes the error.
 *                                     This value will be greater than
 *                                     or equal to zero (specifies the
 *                                     very first attribute in the
 *                                     service) and less than the maximum
 *                                     number of attributes contained in
 *                                     the service.
 *
 * @param[in]  AttributeValueLength    Length (in bytes) of the attribute
 *                                     value data that is to be indicated.
 *
 * @param[in]  AttributeValue          Buffer that contains the value
 *                                     data to be indicated. This buffer
 *                                     must contain (at least) the number
 *                                     of bytes specified by the
 *                                     AttributeValueLength parameter.
 *
 * @return
 * Positive, nonzero value -- If successful. This value
 *              represents the number of attribute value bytes that
 *              will be sent in the notification.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Notification(uint32_t BluetoothStackID, uint32_t ServiceID, uint32_t ConnectionID, uint16_t AttributeOffset, uint16_t AttributeValueLength, uint8_t *AttributeValue);

/**
 * @brief
 * Provides a mechanism for a service handler to
 * verify whether the data received in a signed write request
 * (#QAPI_BLE_ET_GATT_SERVER_SIGNED_WRITE_REQUEST_E event) is correctly signed.
 *
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceID               Service ID of the service that is
 *                                     sending the indication. Returned in
 *                                     a successfull call to
 *                                     qapi_BLE_GATT_Register_Service().
 *
 * @param[in]  AttributeOffset         Attribute offset of the first
 *                                     attribute that causes the error.
 *                                     This value will be greater than
 *                                     or equal to zero (specifies the
 *                                     very first attribute in the
 *                                     service) and less than the maximum
 *                                     number of attributes contained in
 *                                     the service.
 *
 * @param[in]  AttributeValueLength    Length (in bytes) of the attribute
 *                                     value data that is to be indicated.
 *
 * @param[in]  AttributeValue          Buffer that contains the value
 *                                     data to be indicated. This buffer
 *                                     must contain (at least) the number
 *                                     of bytes specified by the
 *                                     AttributeValueLength parameter.
 *
 * @param[in]  ReceivedSignature       Pointer to the GATT/ATT signature
 *                                     that was received in the write
 *                                     request event.
 *
 * @param[in]  CSRK                    Pointer to the connection
 *                                     signature resolving key (CSRK)
 *                                     that is to be used to verify the
 *                                     received signature.
 *
 * @return
 * TRUE -- If the verification was successful.\n
 * FALSE -- If the verification was not successful,
 *              or unable to be performed.
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GATT_Verify_Signature(uint32_t BluetoothStackID, uint32_t ServiceID, uint16_t AttributeOffset, uint32_t AttributeValueLength, uint8_t *AttributeValue, qapi_BLE_ATT_Authentication_Signature_t *ReceivedSignature, qapi_BLE_Encryption_Key_t *CSRK);

   /* GATT Service Changed API. */

/**
 * @brief
 * Provides a mechanism for a connection handler
 * to successfully respond to a received GATT Service Changed read request
 * (#QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_READ_REQUEST_E) event.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID           Transaction ID of the original
 *                                     Service Changed read request. This
 *                                     value was received in the
 *                                     #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_READ_REQUEST_E
 *                                     event.
 *
 * @param[in]  Service_Changed_Data    Specifies a pointer to the data to
 *                                     respond to the Service Changed
 *                                     Read Request with.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data);

/**
 * @brief
 * Provides a mechanism for a connection handler
 * to successfully respond to a received GATT Service Changed read
 * request (#QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_READ_REQUEST_E)
 * event.
 *
 * Each client must have a unique value for this descriptor.
 *
 * It is the application's responsibility to store this persistently
 * for each bonded device.
 *
 * @details
 * This function only allows a successful response to be sent. If an
 * error response is required, then the qapi_BLE_GATT_Error_Response()
 * function should be used to respond with the error information.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the original Service
 *                                 Changed read request. This value was
 *                                 received in the
 *                                 #QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CCCD_READ_REQUEST_E
 *                                 event.
 *
 * @param[in]  CCCD                Value of the client's CCCD for the
 *                                 Service Changed characteristic to
 *                                 respond to the request with.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_CCCD_Read_Response(uint32_t BluetoothStackID, uint32_t TransactionID, uint16_t CCCD);

/**
 * @brief
 * Provides a mechanism for a connection
 * handler to send a GATT Service Changed Indication to a remote,
 * connected, GATT client.
 *
 * @details
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the Indication
 *
 * A QAPI_BLE_ET_GATT_CONNECTION_SERVICE_CHANGED_CONFIRMATION_E event
 * will be dispatched to the registered GATT Connection Callbacks
 * when the indication is acknowledged by the remote device.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote client device to
 *                                     send the Service Changed
 *                                     indication.
 *
 * @param[in]  Service_Changed_Data    Specifies a pointer to the Service
 *                                     Changed data to indicate.
 *
 * @return
 * Positive, nonzero value -- If successful. This value
 *              represents the transaction ID of the Service Changed
 *              indication transaction. This value can be passed to
 *              the qapi_BLE_GATT_Cancel_Transaction() function to
 *              cancel the indication (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Service_Changed_Indication(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Service_Changed_Data_t *Service_Changed_Data);

   /* GATT Robust Caching Support APIs. */

/**
 * @brief
 * Provides a mechanism to responsd to a bonded client data request that
 * has been received from a connected remote device.
 *
 * @details
 * This function is required to be called if the
 * #QAPI_BLE_ET_GATT_CONNECTION_BONDED_CLIENT_DATA_REQUEST_E event has
 * been received.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID            Identifies the connection with
 *                                     the remote device.
 *
 * @param[in]  Bonded_Client_Data      Bonded client data.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Bonded_Client_Data_Request_Response(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Bonded_Client_Data_t *Bonded_Client_Data);

/**
 * @brief
 * Provides a mechanism to query the database hash for the
 * specified connection.
 *
 * @details
 * This is the database hash value that the specified remote
 * device is aware of.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   ConnectionID            Identifies the connection with
 *                                      the remote device.
 *
 * @param[out]  Database_Hash           Holds the database hash if this
 *                                      function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_Database_Hash(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_Encrypted_Data_t *Database_Hash);

/**
 * @brief
 * Provides a mechanism to query the database hash for local
 * GATT database.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  Database_Hash           Holds the database hash if this
 *                                      function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Database_Hash(uint32_t BluetoothStackID, qapi_BLE_Encrypted_Data_t *Database_Hash);

/**
 * @brief
 * Provides a mechanism to lock the GATT database to prevent operations
 * on the database in other threads.
 *
 * @details
 * Since the function locks the underlying Bluetooth Stack,
 * the database must be locked for a short amount of time.
 *
 * Multiple calls to this function are possible, however
 * there must be a corresponding call to the
 * qapi_BLE_GATT_UnLock_Database() function for each successful call
 * that is made to this function.  Failure to call the
 * qapi_BLE_GATT_UnLock_Database() function the same amount of times
 * will yield the Bluetooth Stack unusable.
 *
 * This functionality is intended to be used to locked the
 * GATT database when multiple services are being
 * added/removed to/from the GATT database.  In a normal
 * case each addition/removal of a service requires
 * recalculating the database hash.  Locking the database
 * prevents the recalculation of the database hash until the
 * qapi_BLE_GATT_UnLock_Database() API is called.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Lock_Database(uint32_t BluetoothStackID);

/**
 * @brief
 * Provides a mechanism to unlock the GATT database and enable operations
 * on the database in other threads.
 *
 * @details
 * The database hash of the local database will be updated
 * by this call prior to unlocking the database if any
 * services were added/removed while the database was
 * locked.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_UnLock_Database(uint32_t BluetoothStackID);

   /* GATT Client API. */

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * request a change in the ATT MTU for a connected LE device. This
 * function accepts the MTU to request from the remote connected LE device.
 *
 * This function is only applicable to LE connections.
 *
 * @details
 * The #QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E event will signal
 * when a response is received from the remote GATT server. The new
 * MTU will be the smaller of the RequestedMTU specified in this
 * function and the MTU received in the
 * #QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E event.
 *
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_EXCHANGE_MTU_RESPONSE_E
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote GATT server
 *                                     device.
 *
 * @param[in]  RequestedMTU            The MTU to request from the
 *                                     remote, connected, LE device. This
 *                                     value must be between the
 *                                     following values: \n
 *                                     QAPI_BLE_ATT_PROTOCOL_MTU_MINIMUM_LE + 1 \n
 *                                     and \n
 *                                     QAPI_BLE_GATT_MAXIMUM_SUPPORTED_STACK_MTU
 *
 * @param[in]  ClientEventCallback     Callback function that is
 *                                     registered to receive the exchange
 *                                     MTU response event.
 *
 * @param[in]  CallbackParameter       User-defined parameter (e.g., a
 *                                     tag value) that will be passed
 *                                     back to the user in the callback
 *                                     function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Exchange_MTU_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t RequestedMTU, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to discover
 * the services on a remote, connected GATT server. This function accepts
 * the starting and ending handle ranges to search for services on.
 *
 * @details
 * To discover all services on a remote GATT server, this function should be
 * called with the starting and ending handles set to:
 *
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * respectively.
 *
 * The #QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DISCOVERY_RESPONSE_E
 * event will specify the services found in the specified range. The client
 * can then call this function again with the starting handle set to one
 * greater than the ending handle returned in the event. This process should
 * be repeated to discover all services on a remote GATT server.
 *
 * If successful, the return value will contain the Transaction ID that
 * can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_RESPONSE_E
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote GATT server
 *                                     device.
 *
 * @param[in]  StartingHandle          Starting attribute handle to use
 *                                     to begin the search range. This
 *                                     value must be between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  EndingHandle            Ending attribute handle to use to
 *                                     end the search range. This value
 *                                     must be between (and at least one
 *                                     value larger than the starting
 *                                     attribute handle): \n
 *                                        QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                        and \n
 *                                        QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback     Callback function that is
 *                                     registered to receive the discover
 *                                     services response event.
 *
 * @param[in]  CallbackParameter       A user-defined parameter (e.g., a
 *                                     tag value) that will be passed
 *                                     back to the user in the callback
 *                                     function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Services(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t StartingHandle, uint16_t EndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * discover the services on a remote, connected GATT server that match
 * the specified UUID. This function accepts the starting and ending
 * handle ranges to search for services on. This function enables
 * searches for a specific service instead of searching for
 * all services.
 *
 * @details
 * To discover a service on a remote GATT server, this function should
 * be called with the starting and ending handles set to:
 *
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * respectively.
 *
 * The #QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_BY_UUID_RESPONSE_E
 * event will specify if the service was found in the
 * specified range. The client can then call this function
 * again with the starting handle set to one greater than the
 * ending handle returned in the event. This process should be
 * repeated to discover all service of the specified type on a
 * remote GATT server.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_SERVICE_DISCOVERY_BY_UUID_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  StartingHandle         Starting attribute handle to use to
 *                                    begin the search range. This value
 *                                    must be between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  EndingHandle           Ending attribute handle to use to
 *                                    end the search range. This value
 *                                    must be between (and at least one
 *                                    value larger than the starting
 *                                    attribute handle): \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  UUID                   Contains the service UUID to search for.
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the discover
 *                                    services response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Services_By_UUID(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t StartingHandle, uint16_t EndingHandle, qapi_BLE_GATT_UUID_t *UUID, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client
 * to discover any included services for a specific service on a
 * remote, connected GATT server. This function accepts the starting
 * and ending handle range of the service to search.
 *
 * @details
 * The starting and ending handle values that are passed to this
 * function should specify the starting and ending handles of a
 * single service. This will allow the ability to discern which
 * services are included with the specific service referenced
 * by the starting and ending handles.
 *
 * To discover all included services on a remote GATT database with
 * the specified UUID, the first call to this function should have
 * the starting and ending handle set to:
 *
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE
 *    QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * The #QAPI_BLE_ET_GATT_CLIENT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_E
 * event will signal when the service discovery event started by the
 * call to this function has completed. To discover all services of
 * the specified UUID, this function should be called again with the
 * starting handle set to one greater than the last end group handle
 * returned in the GATT_Service_Information_List of the
 * #QAPI_BLE_ET_GATT_CLIENT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_E
 * Event.
 *
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_INCLUDED_SERVICES_DISCOVERY_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  ServiceStartingHandle  Starting attribute handle to use to
 *                                    begin the search range. This value
 *                                    must be between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ServiceEndingHandle    Ending attribute handle to use to
 *                                    end the search range. This value
 *                                    must be between (and at least one
 *                                    value larger than the starting
 *                                    attribute handle): \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the discover
 *                                    included services response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Included_Services(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t ServiceStartingHandle, uint16_t ServiceEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * discover any characteristics of a specific service on a remote,
 * connected GATT server. This function accepts the starting and
 * ending handle range of the service to search.
 *
 * @details
 * The starting and ending handle values that are passed to this
 * function should specify the starting and ending handles of a
 * single service. This will enable the user to discern which
 * characteristics are included with the specific service referenced
 * by the starting and ending handles.
 *
 * The QAPI_BLE_ETGATT_CLIENT_CHARACTERISTIC_DISCOVERY_RESPONSE_E
 * event will signal that this function may be called again with
 * the starting handle set to one greater than the last characteristic
 * declaration handle specified in the
 * GATT_Characteristic_Discovery_Entry_List list.
 *
 * If successful, the return value will contain the
 * Transaction ID that can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ETGATT_CLIENT_CHARACTERISTIC_DISCOVERY_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  ServiceStartingHandle  Starting attribute handle to use to
 *                                    begin the search range. This value
 *                                    must be between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ServiceEndingHandle    Ending attribute handle to use to
 *                                    end the search range. This value
 *                                    must be between (and at least one
 *                                    value larger than the starting
 *                                    attribute handle): \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the discover
 *                                    characteristics response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Characteristics(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t ServiceStartingHandle, uint16_t ServiceEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * discover any characteristic descriptors of a specific characteristic
 * of a specific service on a remote, connected GATT server. This
 * function accepts the starting and ending handle range of the
 * characteristic to search.
 *
 * @details
 * The starting and ending handle values that are passed to this
 * function should specify the starting and ending handles of a
 * single service. This will enable the user to discern which
 * characteristics are included with the specific service referenced
 * by the starting and ending handles.
 *
 * The #QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_DISCOVERY_RESPONSE_E
 * event will signal that this function may be called again with
 * the starting handle set to one greater than the last characteristic
 * declaration handle specified in the
 * GATT_Characteristic_Discovery_Entry_List list.
 *
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_DISCOVERY_RESPONSE_E
 *
 * @param[in]  BluetoothStackID                Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID                    Connection ID of the
 *                                             currently connected remote
 *                                             GATT server device.
 *
 * @param[in]  CharacteristicStartingHandle    Starting attribute handle
 *                                             to use to begin the search
 *                                             range. This value must be
 *                                                between: \n
 *                                                QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                                and \n
 *                                                QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  CharacteristicEndingHandle      Ending attribute handle to
 *                                             use to end the search
 *                                             range. This value must be
 *                                             between (and at least one
 *                                             value larger than the
 *                                                starting attribute
 *                                                handle): \n
 *                                                QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                                and \n
 *                                                QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback             Callback function that is
 *                                             registered to receive the
 *                                             discover characteristic
 *                                             descriptors response
 *                                             event.
 *
 * @param[in]  CallbackParameter               User-defined parameter
 *                                             (e.g., a tag value) that
 *                                             will be passed back to the
 *                                             user in the callback
 *                                             function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Discover_Characteristic_Descriptors(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t CharacteristicStartingHandle, uint16_t CharacteristicEndingHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs a
 * read request on a remote device for a specific attribute value.
 *
 * @details
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_READ_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  AttributeHandle        Attribute handle of the attribute
 *                                    that is to be read. This value must
 *                                    be between: \n
 *                                      QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                      and \n
 *                                      QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the read
 *                                    value response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Value_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs a
 * read long request on a remote device for a specific attribute
 * value.
 *
 * @details
 * The #QAPI_BLE_ET_GATT_CLIENT_READ_LONG_RESPONSE_E event indicates
 * that a read long request issued by this function has completed.
 * If the event is successful, the attribute offset should be
 * increased by the attribute value length that is returned in the
 * response. The next call to the qapi_BLE_GATT_Read_Long_Value_Request()
 * function should specify this new offset. This can be done
 * until the entire attribute value has been read.
 *
 * If successful, the return value will contain the Transaction ID
 * that can be used to cancel the request.
 *
 *  Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_READ_LONG_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  AttributeHandle        Attribute handle of the attribute
 *                                    that is to be read. This value must
 *                                    be between: \n
 *                                      QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                      and \n
 *                                      QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  AttributeOffset        Starting offset (in bytes) of the
 *                                    attribute value data to read.
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the read long
 *                                    value response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Long_Value_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeOffset, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs a
 * read by UUID request on a remote device for a specific attribute value
 * based on the specified UUID.
 *
 * @details
 * The starting and ending handle values that are passed to this function
 * should specify the starting and ending handles of a single service.
 * This will enable the user to discern which attribute value is
 * associated with the specific service referenced by the starting
 * and ending handles.
 *
 * If successful, the return value will contain the Transaction ID that
 * can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_READ_BY_UUID_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  AttributeUUID         Contains the attribute UUID to search for.
 *
 * @param[in]  ServiceStartHandle     Starting attribute handle to use to
 *                                    begin the search range. This value
 *                                    must be between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ServiceEndHandle       Ending attribute handle to use to
 *                                    end the search range. This value
 *                                    must be between (and at least one
 *                                    value larger than the starting
 *                                    attribute handle): \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the read
 *                                    value by UUID response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Value_By_UUID_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_UUID_t *AttributeUUID, uint16_t ServiceStartHandle, uint16_t ServiceEndHandle, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs
 * a read multiple request on a remote device for multiple  attributes.
 *
 * @details
 * If successful, the return value will contain the Transaction ID that
 * can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_READ_MULTIPLE_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  NumberOfHandles        Specifies the total number of
 *                                    attribute handle entries that are
 *                                    contained in the
 *                                    AttributeHandleList parameter.
 *
 * @param[in]  AttributeHandleList    Pointer to an array of attribute
 *                                    handle entries that specify all of
 *                                    the attributes that should be read.
 *                                    Each member in this array must be
 *                                    between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the read
 *                                    multiple value response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Read_Multiple_Values_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t NumberOfHandles, uint16_t *AttributeHandleList, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs
 * a write request to a remote device for a specified attribute.
 *
 * @details
 * This function will not write an attribute value with a length
 * greater than the current MTU - 3. To write a longer attribute
 * value, use the qapi_BLE_GATT_Prepare_Write_Request() function
 * instead.
 *
 * This function may write less than the number of requested bytes.
 * This can happen if the number of bytes to write is less than
 * what can fit in the MTU for the specified connection. The data
 * in the #QAPI_BLE_ET_GATT_CLIENT_WRITE_RESPONSE_E that is dispatched
 * if the remote device accepts the request indicates the number of
 * bytes that were written to the remote device.
 *
 * If successful, the return value will contain the Transaction ID that
 * can be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_WRITE_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  AttributeHandle        Attribute handle of the attribute
 *                                    to write. This value must be
 *                                    between: \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                       and \n
 *                                       QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  AttributeLength        Length (in bytes) of the actual
 *                                    attribute value data to write to
 *                                    the specified attribute.
 *
 * @param[in]  AttributeValue         Buffer that contains (at least) as
 *                                    many bytes a specified by the
 *                                    AttributeLength parameter.
 *
 * @param[in]  ClientEventCallback     Callback function that is
 *                                     registered to receive the write
 *                                     response event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, non-zero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, void *AttributeValue, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs a
 * write without response request to a remote device for a specified
 * attribute.
 *
 * @details
 * This function will not write a value with a length greater than the
 * current MTU minus 3. It is possible that this function can write less
 * data than specified (due to the MTU and packet header overhead). The
 * return value will indicate the total number of bytes that will be
 * written.
 *
 * No response is issued by the remote GATT server to this command.
 * Therefore there is no guarantee of whether the remote GATT server
 * actually performed the write or rejected it due to some error
 * condition.
 *
 * If this function returns the Error Code
 *
 *    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE,
 *
 * this is a signal that the queueing limits have been exceeded for
 * the specified connection. The caller must then wait for the
 *
 *    QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E
 *
 * event before sending any unacknowledged packets to the specified
 * device. See the qapi_BLE_GATT_Set_Queuing_Parameters() function
 * for more information.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID        Connection ID of the currently
 *                                 connected remote GATT server device.
 *
 * @param[in]  AttributeHandle     Attribute handle of the attribute to
 *                                 write. This value must be between: \n
 *                                    QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                    and \n
 *                                    QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  AttributeLength     Length (in bytes) of the actual
 *                                 attribute value data to write to the
 *                                 specified attribute.
 *
 * @param[in]  AttributeValue      Buffer that contains (at least) as
 *                                 many bytes a specified by the
 *                                 AttributeLength parameter.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the amount of data that will be written to the remote device.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Write_Without_Response_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, void *AttributeValue);

/**
 * @brief
 * Performs a
 * signed write without response request to remote device for a specified
 * attribute.
 *
 * @details
 * This function will not write a value with a length greater than the
 * current MTU minus 3. It is possible that this function can write less
 * data than specified (due to the MTU and packet header overhead). The
 * return value will indicate the total number of bytes that will be
 * written.
 *
 * No response is issued by the remote GATT server to this command.
 * Therefore there is no guarantee of whether the remote GATT server
 * actually performed the write or rejected it due to some error
 * condition.
 *
 * If this function returns the Error Code
 *
 *    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE,
 *
 * this is a signal that the queueing limits have been exceeded for
 * the specified connection. The caller must then wait for the
 *
 *    QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E
 *
 * event before sending any unacknowledged packets to the specified
 * device. See the qapi_BLE_GATT_Set_Queuing_Parameters() function
 * for more information.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CONNECTION_DEVICE_BUFFER_EMPTY_E
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID        Connection ID of the currently
 *                                 connected remote GATT server device.
 *
 * @param[in]  AttributeHandle     Attribute handle of the attribute to
 *                                 write. This value must be between: \n
 *                                    QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                    and \n
 *                                    QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  SignCounter         Sign counter.
 *
 * @param[in]  AttributeLength     Length (in bytes) of the actual
 *                                 attribute value data to write to the
 *                                 specified attribute.
 *
 * @param[in]  AttributeValue      Buffer that contains (at least) as
 *                                 many bytes a specified by the
 *                                 AttributeLength parameter.
 *
 * @param[in]  CSRK                Pointer to the connection signature
 *                                 resolving key (CSRK) that will be used
 *                                 to sign the data that is to be sent.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the amount of data that will be written to the remote device.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Signed_Write_Without_Response(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint32_t SignCounter, uint16_t AttributeLength, void *AttributeValue, qapi_BLE_Encryption_Key_t *CSRK);

/**
 * @brief
 * Performs a
 * prepare write request to a remote device for a specific attribute.
 *
 * This function can be used to write a long attribute value as well as
 * to perform a reliable write to a regular attribute.
 *
 * @details
 * This function differs from the qapi_BLE_GATT_Write_Request() function in
 * that this function can be used to write values that span multiple PDUs.
 * Once all of the data has been prepared (that is, sent successfully) the
 * client can issue the qapi_BLE_GATT_Execute_Write_Request() function to
 * commit the value data in a single, atomic, transaction (and receive a
 * status response).
 *
 * The response event (#QAPI_BLE_ET_GATT_CLIENT_PREPARE_WRITE_RESPONSE_E) will
 * signify to the client how much data was sent. The client can then use this data to
 * determine the new offset of data to write and call this function again. This
 * process should be repeated until either all of the data has been sent or an
 * error occurred.
 *
 * The qapi_BLE_GATT_Execute_Write_Request() function can be called to actually
 * write/commit the data to the remote GATT server after all of the data value
 * has been transmitted successfully.
 *
 * This function may write less than the number of requested bytes. This can
 * happen if the number of bytes to write is less than what can fit in the
 * MTU for the specified connection. The data in the
 * #QAPI_BLE_ET_GATT_CLIENT_PREPARE_WRITE_RESPONSE_E that is dispatched if
 * the remote device accepts the request indicates the number of bytes that
 * were written to the remote device.
 *
 * If successful, the return value will contain the Transaction ID that can
 * be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_PREPARE_WRITE_RESPONSE_E
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID            Connection ID of the currently
 *                                     connected remote GATT server
 *                                     device.
 *
 * @param[in]  AttributeHandle         Attribute handle of the attribute
 *                                     to write. This value must be
 *                                     between: \n
 *                                        QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE \n
 *                                        and \n
 *                                        QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE
 *
 * @param[in]  AttributeLength         Total length (in bytes) of the
 *                                     actual attribute value data to
 *                                     write to the specified attribute.
 *
 * @param[in]  AttributeValueOffset    Offset (in bytes) of the attribute
 *                                     value to write. This value must be
 *                                     smaller than the AttributeLength
 *                                     parameter.
 *
 * @param[in]  AttributeValue          Buffer that contains (at least) as
 *                                     many bytes a specified by the
 *                                     AttributeLength parameter minus
 *                                     the AttributeValueOffset
 *                                     parameter.
 *
 * @param[in]  ClientEventCallback     Callback function that is
 *                                     registered to receive the included
 *                                     the prepare write value response
 *                                     event.
 *
 * @param[in]  CallbackParameter       User-defined parameter (e.g., a
 *                                     tag value) that will be passed
 *                                     back to the user in the callback
 *                                     function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_HANDLE_VALUE \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Prepare_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t AttributeHandle, uint16_t AttributeLength, uint16_t AttributeValueOffset, void *AttributeValue, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * issue an execute write long value request for a specific attribute to
 * a connected remote GATT server.
 *
 * The write that is to be executed must
 * have been prepared by calling the qapi_BLE_GATT_Prepare_Write_Request() function
 * one or more times.
 *
 * @details
 * This function should be called once all of the value
 * data has been prepared (that is, sent successfully). The client can then issue
 * this function to commit the value data in a single, atomic, transaction
 * (and receive a status response).
 *
 * This function can also be used to cancel any prior writes that were
 * issued via one or more successful calls to the qapi_BLE_GATT_Prepare_Write_Request()
 * function. The qapi_BLE_GATT_Execute_Write_Request() function can be called to
 * actually write/commit the data to the remote GATT server after all of the data
 * value has been transmitted successfully. See the qapi_BLE_GATT_Prepare_Write_Request()
 * function for more information.
 *
 * If the Write parameter is FALSE, all prepared writes set up through prior
 * calls to that qapi_BLE_GATT_Prepare_Write_Request() function that have not been
 * executed with calls to the qapi_BLE_GATT_Execute_Write_Request() function
 * will be canceled.
 *
 * If successful, the return value will contain the Transaction ID that can
 * be used to cancel the request.
 *
 * Possible events:
 *
 *    QAPI_BLE_ET_GATT_CLIENT_EXECUTE_WRITE_RESPONSE_E
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID           Connection ID of the currently
 *                                    connected remote GATT server
 *                                    device.
 *
 * @param[in]  CancelWrite            Boolean flag that specifies whether
 *                                    to cancel (TRUE) the
 *                                    prepared write requests, or to
 *                                    commit/execute the prepared write
 *                                    requests (FALSE).
 *
 * @param[in]  ClientEventCallback    Callback function that is
 *                                    registered to receive the included
 *                                    the prepare write value response
 *                                    event.
 *
 * @param[in]  CallbackParameter      User-defined parameter (e.g., a
 *                                    tag value) that will be passed back
 *                                    to the user in the callback
 *                                    function.
 *
 * @return
 * Positive, nonzero value -- If successful. This value represents
 *              the transaction ID of the exchange MTU request transaction.
 *              This value can be passed to the
 *              qapi_BLE_GATT_Cancel_Transaction() function to cancel the
 *              transaction (if required).\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Execute_Write_Request(uint32_t BluetoothStackID, uint32_t ConnectionID, boolean_t CancelWrite, qapi_BLE_GATT_Client_Event_Callback_t ClientEventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a mechanism for a GATT client to issue an
 * acknowledgement for a received handle/value indication event
 * (#QAPI_BLE_ET_GATT_CONNECTION_SERVER_INDICATION_E).
 *
 * @details
 * Note that this event is dispatched via either the callback registered with
 * the qapi_BLE_GATT_Initialize() function or a callback registered via the
 * qapi_BLE_GATT_Register_Connection_Events() function.
 *
 * The connection ID and transaction ID values that are passed to this
 * function should be the values that were contained in the handle/value
 * indication event (#QAPI_BLE_ET_GATT_CONNECTION_SERVER_INDICATION_E).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID        Connection ID of the currently
 *                                 connected remote GATT server device.
 *
 * @param[in]  TransactionID       Transaction ID of the received
 *                                 handle/value indication that is being
 *                                 acknowledged.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Handle_Value_Confirmation(uint32_t BluetoothStackID, uint32_t ConnectionID, uint32_t TransactionID);

   /* GATT Service Discovery API. */

/**
 * @brief
 * Performs a service discovery
 * operation that will automatically discover all included services,
 * characteristics, and characteristic descriptors for either all services
 * supported by a remote device or all services of a specified UUID that
 * are supported by a remote device.
 *
 * This function is provided to simplify the GATT service discovery
 * process.
 *
 * @details
 * The NumberOfUUID and UUIDList parameters are optional and may be set to
 * 0 and NULL respectively. If these parameters are not specified, all
 * services on the specified remote device will be discovered.
 *
 * Only one service discovery operation per remote device can be outstanding
 * at a time.
 *
 * Possible events:
 *
 *  @li  QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E
 *  @li  QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E
 *
 * @param[in]  BluetoothStackID            Unique identifier assigned to
 *                                         this Bluetooth Protocol Stack
 *                                         via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID                Connection ID of the currently
 *                                         connected remote GATT server
 *                                         device.
 *
 * @param[in]  NumberOfUUID                Option parameter that, if
 *                                         specified, contains the number
 *                                         of UUIDs that are contained in
 *                                         the UUIDList parameter.
 *
 * @param[in]  UUIDList                    Optional list of Service UUIDs
 *                                         to attempt to discover on the
 *                                         specified remote device.
 *
 * @param[in]  ServiceDiscoveryCallback    Callback function that will be
 *                                         called with the result of the
 *                                         service discovery operation.
 *
 * @param[in]  CallbackParameter           Callback parameter that will
 *                                         be passed to the specified
 *                                         ServiceDiscoveryCallback when
 *                                         called with the result of the
 *                                         service discovery operation.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_OUTSTANDING_REQUESTS_EXISTS \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Start_Service_Discovery(uint32_t BluetoothStackID, uint32_t ConnectionID, uint32_t NumberOfUUID, qapi_BLE_GATT_UUID_t *UUIDList, qapi_BLE_GATT_Service_Discovery_Event_Callback_t ServiceDiscoveryCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Performs a service discovery
 * operation that will automatically discover all included services,
 * characteristics, and characteristic descriptors for either all services
 * supported by a remote device or all services of a specified UUID that
 * are supported by a remote device in a specific handle range of the
 * remote GATT database.
 *
 * This function is provided to simplify the GATT service discovery
 * process.
 *
 * @details
 * The DiscoveryHandleRange parameter is optional. However, if it is specified,
 * the handle range must be valid (that is, Start and End Handle must be nonzero
 * and Start Handle must be less than or equal to End Handle).
 *
 * The NumberOfUUID and UUIDList parameters are optional and may be set to 0
 * and NULL respectively. If these parameters are not specified then all services
 * on the specified remote device will be discovered.
 *
 * Only one service discovery operation per remote device can be outstanding at
 * a time.
 *
 * Possible events:
 *
 *  @li  QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_INDICATION_E
 *  @li  QAPI_BLE_ET_GATT_SERVICE_DISCOVERY_COMPLETE_E
 *
 * @param[in]  BluetoothStackID            Unique identifier assigned to
 *                                         this Bluetooth Protocol Stack
 *                                         via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID                Connection ID of the currently
 *                                         connected remote GATT server
 *                                         device.
 *
 * @param[in]  DiscoveryHandleRange        Handle range of the GATT
 *                                         database on the remote device
 *                                         to perform the discovery
 *                                         procedure on.
 *
 * @param[in]  NumberOfUUID                Option parameter that, if
 *                                         specified, contains the number
 *                                         of UUIDs that are contained in
 *                                         the UUIDList parameter.
 *
 * @param[in]  UUIDList                    Optional list of Service UUIDs
 *                                         to attempt to discover on the
 *                                         specified remote device.
 *
 * @param[in]  ServiceDiscoveryCallback    Callback function that will be
 *                                         called with the result of the
 *                                         service discovery operation.
 *
 * @param[in]  CallbackParameter           Callback parameter that will
 *                                         be passed to the specified
 *                                         ServiceDiscoveryCallback when
 *                                         called with the result of the
 *                                         service discovery operation.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Start_Service_Discovery_Handle_Range(uint32_t BluetoothStackID, uint32_t ConnectionID, qapi_BLE_GATT_Attribute_Handle_Group_t *DiscoveryHandleRange, uint32_t NumberOfUUID, qapi_BLE_GATT_UUID_t *UUIDList, qapi_BLE_GATT_Service_Discovery_Event_Callback_t ServiceDiscoveryCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Stops a service discovery
 * operation that was previously started using the
 * qapi_BLE_GATT_Start_Service_Discovery() or
 * qapi_BLE_GATT_Start_Service_Discovery_Handle_Range() APIs.
 *
 * @details
 * This function will cancel any service discovery operations that are
 * currently in progress and release all request information in the
 * queue that are waiting to be executed.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ConnectionID        Connection ID of the currently
 *                                 connected remote GATT server device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_CONNECTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Stop_Service_Discovery(uint32_t BluetoothStackID, uint32_t ConnectionID);

   /* GATT shared Server/Client API. */

/**
 * @brief
 * Provides a mechanism for a GATT client to
 * cancel a currently queued transaction.
 *
 * @details
 * If the transaction ID specifies a transaction that has already been
 * sent to the remote device, there is really way no way to cancel
 * the transaction as it cannot be purged from the queue.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TransactionID       Transaction ID of the transaction
 *                                 that is to be cancelled.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Cancel_Transaction(uint32_t BluetoothStackID, uint32_t TransactionID);

/**
 * @brief
 * Queries the maximum supported GATT MTU of the GATT layer.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  MTU                 Pointer to return the maximum
 *                                  supported MTU.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Maximum_Supported_MTU(uint32_t BluetoothStackID, uint16_t *MTU);

/**
 * @brief
 * Changes the maximum supported GATT MTU of the GATT layer.
 *
 * @details
 * The MTU value passed to this function must follow the following
 * formula:
 *
 *    QAPI_BLE_ATT_PROTOCOL_MTU_MINIMUM_LE <= MTU
 *                <= QAPI_BLE_ATT_PROTOCOL_MTU_MAXIMUM
 *
 *
 * This API can only be used if there are no active GATT connections.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  MTU                 MTU to configure as the maximum
 *                                 supported for the GATT layer.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Change_Maximum_Supported_MTU(uint32_t BluetoothStackID, uint16_t MTU);

/**
 * @brief
 * Queries the MTU of a specified connection.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   ConnectionID        Connection ID of the currently
 *                                  connected remote GATT server device.
 *
 * @param[out]  MTU                 Pointer to return the
 *                                  MTU for the connection.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_MTU(uint32_t BluetoothStackID, uint32_t ConnectionID, uint16_t *MTU);

/**
 * @brief
 * Queries the connection identifier of a specified connection.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   ConnectionType      Identifies the type of connection
 *                                  to query the Connection ID. This
 *                                  value must be one of the following: \n
 *                                     #QAPI_BLE_GCT_LE_E \n
 *                                     #QAPI_BLE_GCT_BR_EDR_E
 *
 * @param[in]   BD_ADDR             Specifies the address of the remote
 *                                  Bluetooth device to query the
 *                                  Connection ID for.
 *
 * @param[out]  ConnectionID        Connection ID of the currently
 *                                  connected remote GATT server device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Connection_ID(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Type_t ConnectionType, qapi_BLE_BD_ADDR_t BD_ADDR, uint32_t *ConnectionID);

/**
 * @brief
 * Queries the Attribute Protocol Opcode of a specified transaction.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   TransactionID       Transaction ID of the transaction to
 *                                  query the Attribute Protocol Opcode
 *                                  for.
 *
 * @param[out]  Opcode              Pointer to return the Opcode for the
 *                                  specified transaction
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Transaction_Opcode(uint32_t BluetoothStackID, uint32_t TransactionID, uint8_t *Opcode);

/**
 * @brief
 * Sets the queuing
 * parameters that are used to limit the number of unacknowledged packets
 * that are queued internally.
 *
 * @details
 * These parameters are used to control aspects of the amount of data
 * packets that can be queued into the lower level (per individual
 * device connection).
 *
 * Setting both the MaximumNumberDataPackets and
 * QueuedDataPacketsThreshold parameters to zero will disable the queuing
 * mechanism. This means that the amount of queued packets will only be
 * limited by the amount of available RAM.
 *
 * Only unacknowledged transactions are affected by the queueing.
 * Acknowledged GATT transactions are never affected by this queueing
 * mechanism. The APIs that this will affect are the following:
 *
 *  @li  qapi_BLE_GATT_Write_Without_Response_Request()
 *  @li  qapi_BLE_GATT_Signed_Write_Without_Response()
 *  @li  qapi_BLE_GATT_Handle_Value_Notification()
 *
 * @param[in]  BluetoothStackID              Unique identifier assigned
 *                                           to this Bluetooth Protocol
 *                                           Stack via a call to
 *                                           qapi_BLE_BSC_Initialize().
 *
 * @param[in]  MaximumNumberDataPackets      Maximum number of
 *                                           unacknowledged packets that
 *                                           may be queued internally.
 *
 * @param[in]  QueuedDataPacketsThreshold    The lower threshold limit
 *                                           that the lower layer should
 *                                           call back to signify that it
 *                                           can queue more data packets
 *                                           for transmission.
 *
 * @param[in]  DiscardOldest                 Boolean that specifies whether
 *                                           the oldest packets should be
 *                                           discarded when a buffer full
 *                                           condition occurs (if TRUE).
 *                                           If FALSE, no packets will be
 *                                           discarded when the buffer is
 *                                           full. This can be useful to
 *                                           isochronous-like
 *                                           applications.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Set_Queuing_Parameters(uint32_t BluetoothStackID, uint32_t MaximumNumberDataPackets, uint32_t QueuedDataPacketsThreshold, boolean_t DiscardOldest);

/**
 * @brief
 * Gets the queuing
 * parameters that are currently being used to limit the number of
 * unacknowledged packets that are queued internally.
 *
 * @details
 * See the qapi_BLE_GATT_Set_Queuing_Parameters() function for more
 * information.
 *
 * @param[in]  BluetoothStackID               Unique identifier assigned
 *                                            to this Bluetooth Protocol
 *                                            Stack via a call to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[out]  MaximumNumberDataPackets      Pointer to the maximum
 *                                            number of unacknowledged
 *                                            packets that may be queued
 *                                            internally.
 *
 * @param[out]  QueuedDataPacketsThreshold    Pointer to the lower
 *                                            threshold limit that the
 *                                            lower layer should call
 *                                            back to signify that it can
 *                                            queue more data packets for
 *                                            transmission.
 *
 * @param[out]  DiscardOldest                 Pointer to return the
 *                                            boolean that specifies whether
 *                                            the oldest packets should
 *                                            be discarded when a buffer
 *                                            full condition occurs (if
 *                                            TRUE). If FALSE, no packets
 *                                            will be discarded when the
 *                                            buffer is full. This can be
 *                                            useful to isochronous-like
 *                                            applications.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_TRANSACTION_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GATT_Get_Queuing_Parameters(uint32_t BluetoothStackID, uint32_t *MaximumNumberDataPackets, uint32_t *QueuedDataPacketsThreshold, boolean_t *DiscardOldest);

/**
 * @brief
 * Determines whether a
 * specified handle range is available in the GATT database for a
 * service to be registered in.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  ServiceHandleGroup    Pointer to a structure containing
 *                                    the start and end handle of a region
 *                                    in the GATT database to determine the
 *                                    availability of.
 *
 * @return
 * TRUE -- If the specified handle range in the GATT database
 *               is available (that is, no other service is using any handles
 *               in the specified range).\n
 * FALSE -- If the specified region of the GATT database is not
 *               available.
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GATT_Query_Service_Range_Availability(uint32_t BluetoothStackID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleGroup);

/** @} */ /* end_addtogroup qapi_ble_profiles_gatt */

#endif

