/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_ots.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Object Transfer Service
 * (GATT based) API Type Definitions, Constants, and
 * Prototypes.
 *
 * @details
 * The Object Transfer Service (OTS) programming interface defines the
 * protocols and procedures to be used to implement the Object Transfer Service
 * capabilities.
 */

#ifndef __QAPI_BLE_OTS_H__
#define __QAPI_BLE_OTS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_l2cap.h"     /* Bluetooth L2CAP Definitions/Constants.   */
#include "./qapi_ble_gatt.h"      /* QAPI GATT prototypes.                    */
#include "./qapi_ble_otstypes.h"  /* QAPI OTS prototypes.                     */

/** @addtogroup qapi_ble_services_ots
@{
*/

   /* Error Return Codes.                                               */

   /* Error Codes that are smaller than these (less than -1000) are     */
   /* related to the Bluetooth Protocol Stack itself (see               */
   /* qapi_ble_errors.h).                                               */
#define QAPI_BLE_OTS_ERROR_INVALID_PARAMETER                      (-1000)
/**< Invalid parameter. */
#define QAPI_BLE_OTS_ERROR_INVALID_BLUETOOTH_STACK_ID             (-1001)
/**< Invalid Bluetooth Stack ID. */
#define QAPI_BLE_OTS_ERROR_INSUFFICIENT_RESOURCES                 (-1002)
/**< Insufficient resources. */
#define QAPI_BLE_OTS_ERROR_INSUFFICIENT_BUFFER_SPACE              (-1003)
/**< Insufficent buffer space. */
#define QAPI_BLE_OTS_ERROR_SERVICE_ALREADY_REGISTERED             (-1004)
/**< Service is already registered. */
#define QAPI_BLE_OTS_ERROR_INVALID_INSTANCE_ID                    (-1005)
/**< Invalid service instance ID. */
#define QAPI_BLE_OTS_ERROR_MALFORMATTED_DATA                      (-1006)
/**< Malformatted data. */

   /* OTS API Specific error codes.                                     */
#define QAPI_BLE_OTS_ERROR_INDICATION_OUTSTANDING                 (-1007)
/**< Indication is outstanding. */
#define QAPI_BLE_OTS_ERROR_INVALID_CHARACTERISTIC_FLAG            (-1008)
/**< Invalid characteristic flag. */
#define QAPI_BLE_OTS_ERROR_INVALID_ATTRIBUTE_HANDLE               (-1009)
/**< Invalid attribute handle. */
#define QAPI_BLE_OTS_ERROR_INVALID_CCCD_CHARACTERISTIC_TYPE       (-1010)
/**< Invalid CCCD characteristic type. */
#define QAPI_BLE_OTS_ERROR_INVALID_OBJECT_METADATA_TYPE           (-1011)
/**< Invalid object metadata type. */
#define QAPI_BLE_OTS_ERROR_INVALID_OACP_RESULT_CODE               (-1012)
/**< Invalid OACP result code. */
#define QAPI_BLE_OTS_ERROR_INVALID_OLCP_RESULT_CODE               (-1013)
/**< Invalid OCLP result code. */
#define QAPI_BLE_OTS_ERROR_INVALID_OBJECT_LIST_FILTER_INSTANCE    (-1014)
/**< Invalid object list filter instance. */
#define QAPI_BLE_OTS_ERROR_INVALID_OBJECT_LIST_FILTER_TYPE        (-1015)
/**< Invalid object list filter type. */
#define QAPI_BLE_OTS_ERROR_INVALID_OBJECT_TYPE_UUID_SIZE          (-1016)
/**< Invalid object type UUID size. */
#define QAPI_BLE_OTS_ERROR_INVALID_WRITE_MODE_TYPE                (-1017)
/**< Invalid write mode type. */
#define QAPI_BLE_OTS_ERROR_INVALID_LIST_SORT_ORDER_TYPE           (-1018)
/**< Invalid list sort order type. */

   /* Object Transfer Channel (OTC) API specific error codes.           */
#define QAPI_BLE_OTS_ERROR_NO_GATT_CONNECTION                     (-1019)
/**< A GATT connection does not exist. */
#define QAPI_BLE_OTS_ERROR_NO_CONNECTION_INFORMATION              (-1020)
/**< No connection information. */
#define QAPI_BLE_OTS_ERROR_INVALID_CONNECTION_TYPE                (-1021)
/**< Invalid connection type. */
#define QAPI_BLE_OTS_ERROR_INVALID_CONNECTION_STATE               (-1022)
/**< Invalid connection state. */
#define QAPI_BLE_OTS_ERROR_INVALID_CONNECTION_MODE                (-1023)
/**< Invalid connection mode. */

/**
 * Structure that contains the attribute handles that will need to be
 * cached by an OTS client in order to only do service discovery once.
 */
typedef struct qapi_BLE_OTS_Client_Information_s
{
   /**
    * OTS Feature attribute handle.
    */
   uint16_t OTS_Feature;

   /**
    * Object Name attribute handle.
    */
   uint16_t Object_Name;

   /**
    * Object Type attribute handle.
    */
   uint16_t Object_Type;

   /**
    * Object Size attribute handle.
    */
   uint16_t Object_Size;

   /**
    * Object First Created attribute handle.
    */
   uint16_t Object_First_Created;

   /**
    * Object Last Modified attribute handle.
    */
   uint16_t Object_Last_Modified;

   /**
    * Object ID attribute handle.
    */
   uint16_t Object_ID;

   /**
    * Object Properties attribute handle.
    */
   uint16_t Object_Properties;

   /**
    * Object Action Control Point attribute handle.
    */
   uint16_t Object_Action_Control_Point;

   /**
    * Object Action Control Point Client Characteristic
    * Configuration Descriptor (CCCD) attribute handle.
    */
   uint16_t Object_Action_Control_Point_CCCD;

   /**
    * Object List Control Point attribute handle.
    */
   uint16_t Object_List_Control_Point;

   /**
    * Object List Control Point CCCD attribute handle.
    */
   uint16_t Object_List_Control_Point_CCCD;

   /**
    * Object List Filter attribute handles.
    */
   uint16_t Object_List_Filter[3];

   /**
    * Object Changed attribute handles.
    */
   uint16_t Object_Changed;

   /**
    * Object Changed CCCD attribute handle.
    */
   uint16_t Object_Changed_CCCD;
} qapi_BLE_OTS_Client_Information_t;

#define QAPI_BLE_OTS_CLIENT_INFORMATION_DATA_SIZE                 (sizeof(qapi_BLE_OTS_Client_Information_t))
/**<
 * Size of the #qapi_BLE_OTS_Client_Information_t structure.
 */

/**
 * Structure that contains all of the per client data that will need to
 * be stored by an OTS server.
 */
typedef struct qapi_BLE_OTS_Server_Information_s
{
   /**
    * Object Action Control Point CCCD.
    */
   uint16_t Object_Action_Control_Point_Configuration;

   /**
    * Object List Control Point CCCD.
    */
   uint16_t Object_List_Control_Point_Configuration;

   /**
    * Object Changed CCCD.
    */
   uint16_t Object_Changed_Configuration;
} qapi_BLE_OTS_Server_Information_t;

#define QAPI_BLE_OTS_SERVER_INFORMATION_DATA_SIZE                 (sizeof(qapi_BLE_OTS_Server_Information_t))
/**<
 * Size of the #qapi_BLE_OTS_Server_Information_t structure.
 */

/**
 * Structure that represents the format for the OTS Feature
 * Characteristic.
 *
 * The OACP_Features and OLCP_Features fields specify the global
 * (affects all clients) supported features of the OTS server.
 *
 * The OACP_Features field is a bitmask that has the form
 * QAPI_BLE_OTS_FEATURE_OACP_XXX and can be found in qapi_ble_otstypes.h.
 *
 * The OLCP_Features field is a bitmask that has the form
 * QAPI_BLE_OTS_FEATURE_OLCP_XXX and can be found in qapi_ble_otstypes.h.
 */
typedef struct qapi_BLE_OTS_Feature_Data_s
{
   /**
    * Supported features for the Object Action Control Point
    * (OACP).
    */
   uint32_t OACP_Features;

   /**
    * Supported features for the OLCP.
    */
   uint32_t OLCP_Features;
} qapi_BLE_OTS_Feature_Data_t;

#define QAPI_BLE_OTS_FEATURE_DATA_SIZE                            (sizeof(qapi_BLE_OTS_Feature_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Feature_Data_t structure.
 */

/**
 * Structure that represents the format of the OTS Object Name Metadata
 * Characteristic.
 *
 * The Buffer_Length field may not exceed the
 * QAPI_BLE_OTS_MAXIMUM_OBJECT_NAME_LENGTH found in qapi_ble_otstypes.h.
 */
typedef struct qapi_BLE_OTS_Name_Data_s
{
   /**
    * Pointer to the buffer that contains the OTS Object Name.
    */
   uint8_t *Buffer;

   /**
    * Length of the buffer that contains the OTS Object Name.
    */
   uint8_t  Buffer_Length;
} qapi_BLE_OTS_Name_Data_t;

#define QAPI_BLE_OTS_OBJECT_NAME_DATA_SIZE                        (sizeof(qapi_BLE_OTS_Name_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Name_Data_t structure.
 */

/**
 * Structure that represents the format for the OTS Object
 * Size Metadata Characteristic.
 *
 * The Current_Size field represents the actual size of the OTS Object.
 * This field must be less than or equal to the value of the
 * Allocated_Size field.
 *
 * The Allocated_Size field represents the number of octets
 * that have been allocated by the OTS server for the OTS Object's
 * contents.
 */
typedef struct qapi_BLE_OTS_Object_Size_Data_s
{
   /**
    * Current size of the OTS Object.
    */
   uint32_t Current_Size;

   /**
    * Allocated size of the OTS Object.
    */
   uint32_t Allocated_Size;
} qapi_BLE_OTS_Object_Size_Data_t;

#define QAPI_BLE_OTS_OBJECT_SIZE_DATA_SIZE                        (sizeof(qapi_BLE_OTS_Object_Size_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Object_Size_Data_t structure.
 */

/**
 * Structure that represents the Date/Time data for OTS.
 */
typedef struct qapi_BLE_OTS_Date_Time_Data_s
{
   /**
    * Year.
    */
   uint16_t Year;

   /**
    * Month.
    */
   uint8_t  Month;

   /**
    * Day.
    */
   uint8_t  Day;

   /**
    * Hours.
    */
   uint8_t  Hours;

   /**
    * Minutes.
    */
   uint8_t  Minutes;

   /**
    * Seconds.
    */
   uint8_t  Seconds;
} qapi_BLE_OTS_Date_Time_Data_t;

#define QAPI_BLE_OTS_DATE_TIME_DATA_SIZE                          (sizeof(qapi_BLE_OTS_Date_Time_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Date_Time_Data_t structure.
 */

#define QAPI_BLE_OTS_DATE_TIME_VALID(_x)                          ((QAPI_BLE_GATT_DATE_TIME_VALID_YEAR(((_x)).Year)) && (QAPI_BLE_GATT_DATE_TIME_VALID_MONTH(((_x)).Month)) && (QAPI_BLE_GATT_DATE_TIME_VALID_DAY(((_x)).Day)) && (QAPI_BLE_GATT_DATE_TIME_VALID_HOURS(((_x)).Hours)) && (QAPI_BLE_GATT_DATE_TIME_VALID_MINUTES(((_x)).Minutes)) && (QAPI_BLE_GATT_DATE_TIME_VALID_SECONDS(((_x)).Seconds)))
/**<
 * This macro is a utility macro that exists to validate that a specified
 * Date/Time is valid. The only parameter to this function is the
 * #qapi_BLE_OTS_Date_Time_Data_t structure to validate. This macro
 * returns TRUE if the Date Time is valid or FALSE otherwise.
 *
 * This macro may not be used if the OTS Date Time is invalid. If the
 * OACP Create Procedure is used, the OTS Date Time will be invalid
 * (all fields zero).
 */

#define QAPI_BLE_OTS_DATE_TIME_INVALID(_x)                        (((_x).Year == 0) && ((_x).Month == 0) && ((_x).Day == 0) && ((_x).Hours == 0) && ((_x).Minutes == 0) && ((_x).Seconds == 0))
/**<
 * This macro is a utility macro that exists to validate that a specified
 * Date/Time is invalid. The only parameter to this function is the
 * #qapi_BLE_OTS_Date_Time_Data_t structure to validate. This macro
 * returns TRUE if the Date Time is valid or FALSE otherwise.
 *
 * This macro may be used to determine if an OTS Date Time is invalid. If
 * the OACP Create Procedure is used, the OTS Date Time will be
 * invalid (all fields zero).
 */

/**
 * Structure that represents the format for the UINT48 data
 * type.
 *
 * This data type will be used for the OTS Object ID Metadata
 * Characteristic.
 *
 * The Lower field represents the first least significant 32 bits and the
 * Upper field represents the most significant 16 bits of the 48-bit
 * data type.
 */
typedef struct qapi_BLE_OTS_UINT48_Data_s
{
   /**
    * Lower bits of the UINT48 data type.
    */
   uint32_t Lower;

   /**
    * Upper bits of the UINT48 data type.
    */
   uint16_t Upper;
} qapi_BLE_OTS_UINT48_Data_t;

#define QAPI_BLE_OTS_UINT48_DATA_SIZE                             (sizeof(qapi_BLE_OTS_UINT48_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_UINT48_Data_t structure.
 */

/**
 * Structure that represents the format for an OTS Object. This
 * structure contains the OTS Object Metadata Characteristics that are
 * exposed for each OTS Object.
 *
 * The OTS Directory Listing Object's (a specific OTS Object) contents
 * are comprised of OTS Object Records (including one for itself), which
 * includes OTS Object Metadata about each OTS Object on the OTS server.
 * Each OTS Object Record will be handled internally by the
 * qapi_BLE_OTS_Format_Directory_Listing_Object_Contents() and
 * qapi_BLE_OTS_Decode_Directory_Listing_Object_Contents() functions.
 * Some Metadata included in the OTS Object Record is optional
 * and is controlled by the Flags field in this structure. It
 * is included here to centralize what optional fields of an OTS
 * Object's Metadata will be included for each OTS Object Record
 * when the OTS Directory Listing Object's contents are
 * formatted.
 *
 * The Flags field is a bitmask that is used to control the optional
 * fields of an OTS Object's Metadata that will be included for each OTS
 * Object Record. Valid values have the form
 * QAPI_BLE_OTS_OBJECT_RECORD_FLAGS_XXX and can be found in
 * qapi_ble_otstypes.h.
 *
 * The OTS Object for the OTS Directory Listing Object has requirements
 * for some of the fields included in this structure. See the notes
 * below for information about fields for the OTS Directory Listing
 * Object.
 *
 * If this is the OTS Directory Listing Object, the Name field
 * should be reflective of its purpose (i.e., Directory).
 *
 * The Type field is for the OTS Object Type Metadata Characteristic.
 * Types may only be defined by a 16-bit UUID or a 128-bit UUID. The
 * Flags field must be set to
 * QAPI_BLE_OTS_OBJECT_RECORD_FLAGS_TYPE_UUID_SIZE_128 for a 128-bit
 * UUID. Otherwise, it should be excluded to indicate a 16-bit UUID.
 *
 * The Size field is optional for an the OTS Object Record and may be
 * included if specified by the Flags field. This field must be updated
 * for the OTS Directory Listing Object before an OTS client may read
 * the OTS Directory Listing Object's contents via the Object Transfer
 * Channel (OTC). The current size and allocated size should be the
 * same for the OTS Directory Listing Object and may be determined via
 * the qapi_BLE_OTS_Format_Directory_Listing_Object_Contents() function.
 * See this function for more information.
 *
 * The First_Created and Last_Modified fields have no meaning for the
 * OTS Directory Listing Object and may be defined by a higher level
 * specification. These fields are optional for an OTS Object Record
 * and may be included if specified by the Flags field.
 *
 * The ID Field is for the OTS Object ID Metadata Characteristic. If
 * this is the OTS Directory Listing Object, the ID field
 * must be 0. This field is mandatory for an OTS Object Record.
 *
 * The Properties field is for the OTS Object Properties Metadata
 * Characteristic. If this is the OTS Directory Listing Object,
 * the Properties field must specify reading of the OTS
 * Directory Listing Object. The Properties field must also not allow
 * modification or deletion of the OTS Directory Listing
 * Object. This field is optional for the OTS Object Record and
 * may be included if specfied by the Flags field.
 */
typedef struct qapi_BLE_OTS_Object_Data_s
{
   /**
    * Indicates the features of the OTS Object and the optional fields
    * that are included for the OTS Object data.
    */
   uint8_t                         Flags;

   /**
    * OTS Object Name.
    */
   qapi_BLE_OTS_Name_Data_t        Name;

   /**
    * OTS Object Type.
    */
   qapi_BLE_GATT_UUID_t            Type;

   /**
    * OTS Object Size.
    */
   qapi_BLE_OTS_Object_Size_Data_t Size;

   /**
    * OTS Object's First Created Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t   First_Created;

   /**
    * OTS Object's Last Modified Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t   Last_Modified;

   /**
    * Unique ID that identifies the OTS Object.
    */
   qapi_BLE_OTS_UINT48_Data_t      ID;

   /**
    * Properties of the OTS Object.
    */
   uint32_t                        Properties;

   /**
    * Flags if the OTS Object has been marked.
    */
   boolean_t                       Marked;
} qapi_BLE_OTS_Object_Data_t;

#define QAPI_BLE_OTS_OBJECT_DATA_SIZE                             (sizeof(qapi_BLE_OTS_Object_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Object_Data_t structure.
 */

/**
 * Enumeration that represents the Object Action Control Point (OACP)
 * Procedures that may be set for the Request_Op_Code field of the
 * #qapi_BLE_OTS_OACP_Request_Data_t and #qapi_BLE_OTS_OACP_Response_Data_t
 * structures.
 */
typedef enum
{
   QAPI_BLE_OTS_OAOC_CREATE_E             = QAPI_BLE_OTS_OACP_OP_CODE_CREATE,
   /**< OACP Create Procedure op code. */
   QAPI_BLE_OTS_OAOC_DELETE_E             = QAPI_BLE_OTS_OACP_OP_CODE_DELETE,
   /**< OACP Delete Procedure op code. */
   QAPI_BLE_OTS_OAOC_CALCULATE_CHECKSUM_E = QAPI_BLE_OTS_OACP_OP_CODE_CALCULATE_CHECKSUM,
   /**< OACP Calculate Checksum Procedure op code. */
   QAPI_BLE_OTS_OAOC_EXECUTE_E            = QAPI_BLE_OTS_OACP_OP_CODE_EXECUTE,
   /**< OACP Execute Procedure op code. */
   QAPI_BLE_OTS_OAOC_READ_E               = QAPI_BLE_OTS_OACP_OP_CODE_READ,
   /**< OACP Read Procedure op code. */
   QAPI_BLE_OTS_OAOC_WRITE_E              = QAPI_BLE_OTS_OACP_OP_CODE_WRITE,
   /**< OACP Write Procedure op code. */
   QAPI_BLE_OTS_OAOC_ABORT_E              = QAPI_BLE_OTS_OACP_OP_CODE_ABORT
   /**< OACP Abort Procedure op code. */
} qapi_BLE_OTS_OACP_Request_Type_t;

/**
 * Structure that represents the parameters that are required for an
 * OACP Create procedure request.
 */
typedef struct qapi_BLE_OTS_OACP_Create_Request_Data_s
{
   /**
    * Allocated size for the OTS Object.
    */
   uint32_t             Size;

   /**
    * OTS Object Type for the OTS Object.
    */
   qapi_BLE_GATT_UUID_t UUID;
} qapi_BLE_OTS_OACP_Create_Request_Data_t;

/**
 * Structure that represents the parameters that are required for an
 * OACP Calculate Checksum procedure request.
 */
typedef struct qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_s
{
   /**
    * Starting offset of the OTS Object's contents.
    */
   uint32_t Offset;

   /**
    * Length of data from the starting offset that the procedure will
    * use for calculating the checksum over the OTS Object's contents.
    */
   uint32_t Length;
} qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t;

/**
 * Structure that represents the parameters that are required for an
 * OACP Execute procedure request.
 *
 * This is defined by a higher level specification. It is the
 * application's responsibility to make sure that data in the
 * buffer is formatted properly.
 */
typedef struct qapi_BLE_OTS_OACP_Execute_Request_Data_s
{
   /**
    * Length of the buffer.
    */
   uint16_t  Buffer_Length;

   /**
    * Pointer to the buffer that contains the data that will be sent in
    * the request.
    */
   uint8_t  *Buffer;
} qapi_BLE_OTS_OACP_Execute_Request_Data_t;

/**
 * Structure that represents the parameters that are required for an
 * OACP Read procedure request.
 *
 * It is worth noting that the OTS client must read the OTS Directory
 * Listing Object's Size Metadata Characteristic prior to issuing an OACP
 * Read Procedure request to read the OTS directory Listing Object's
 * contents. The OTS client must read the entire OTS Directory Listing
 * Object's contents. Otherwise, it cannot be decoded via the
 * OTS_Decode_Directory_Listing_Object_Contents() function when received.
 * For the OACP Read Procedure, the Offset must be set to zero and the
 * Length must be set to to the received value in the read response for
 * the OTS Directory Listing Object's Size Metadata Characteristic, which
 * represents the size of the OTS Directory Listing Object's contents.
 */
typedef struct qapi_BLE_OTS_OACP_Read_Request_Data_s
{
   /**
    * Starting offset of the OTS Object's contents.
    */
   uint32_t Offset;

   /**
    * Length of data from the starting offset that the procedure will
    * use for reading the OTS Object's contents.
    */
   uint32_t Length;
} qapi_BLE_OTS_OACP_Read_Request_Data_t;

/**
 * Enumeration that represents the valid values that may be set for the
 * Mode field of the #qapi_BLE_OTS_OACP_Write_Request_Data_t structure.
 */
typedef enum
{
   QAPI_BLE_OTS_WMT_NONE_E     = QAPI_BLE_OTS_OACP_WRITE_MODE_NONE,
   /**< No write mode specified. */
   QAPI_BLE_OTS_WMT_TRUNCATE_E = QAPI_BLE_OTS_OACP_WRITE_MODE_TRUNCATE
   /**< Truncate mode. */
} qapi_BLE_OTS_Write_Mode_Type_t;

/**
 * Structure that represents the parameters that are required for a
 * OACP Write procedure request.
 */
typedef struct qapi_BLE_OTS_OACP_Write_Request_Data_s
{
   /**
    * Starting offset of the OTS Object's contents.
    */
   uint32_t                       Offset;

   /**
    * Length of data from the starting offset that the procedure
    * will use for writing the OTS Object's contents.
    */
   uint32_t                       Length;

   /**
    * Mode that is used for writing the OTS Object's contents.
    */
   qapi_BLE_OTS_Write_Mode_Type_t Mode;
} qapi_BLE_OTS_OACP_Write_Request_Data_t;

/**
 * Structure that represents the format for the OTS OACP request.
 *
 * The Request_Op_Code field of this structure
 * specifies which Parameter field is valid. Currently, the following
 * fields are valid for the following values of the Request_Op_Code
 * field:
 *
 * @li QAPI_BLE_OTS_OAOC_CREATE_E             -- Create_Data
 * @li QAPI_BLE_OTS_OAOC_CALCULATE_CHECKSUM_E -- Calculate_Checksum_Data
 * @li QAPI_BLE_OTS_OAOC_EXECUTE_E            -- Execute_Data
 * @li QAPI_BLE_OTS_OAOC_READ_E               -- Read_Data
 * @li QAPI_BLE_OTS_OAOC_WRITE_E              -- Write_Data
 *
 */
typedef struct qapi_BLE_OTS_OACP_Request_Data_s
{
   /**
    * Op code for the OACP request.
    */
   qapi_BLE_OTS_OACP_Request_Type_t Request_Op_Code;
   union
   {
      /**
       * OACP Create procedure data.
       */
      qapi_BLE_OTS_OACP_Create_Request_Data_t             Create_Data;

      /**
       * OACP Calculate Checksum procedure data.
       */
      qapi_BLE_OTS_OACP_Calculate_Checksum_Request_Data_t Calculate_Checksum_Data;

      /**
       * OACP Execute procedure data.
       */
      qapi_BLE_OTS_OACP_Execute_Request_Data_t            Execute_Data;

      /**
       * OACP Read procedure data.
       */
      qapi_BLE_OTS_OACP_Read_Request_Data_t               Read_Data;

      /**
       * OACP Write procedure data.
       */
      qapi_BLE_OTS_OACP_Write_Request_Data_t              Write_Data;
   }
   /**
    * Optional parameter that must be included for certain OACP
    * request op codes. @newpagetable
    */
   Parameter;
} qapi_BLE_OTS_OACP_Request_Data_t;

#define QAPI_BLE_OTS_OACP_REQUEST_DATA_SIZE                       (sizeof(qapi_BLE_OTS_OACP_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_OACP_Request_Data_t structure.
 */

/**
 * Enumeration that represents the OACP Result types that may be set for
 * the Result_Code field of the #qapi_BLE_OTS_OACP_Response_Data_t
 * structure.
 */
typedef enum
{
   QAPI_BLE_OTS_OARC_SUCCESS_E                 = QAPI_BLE_OTS_OACP_RESULT_CODE_SUCCESS,
   /**< Success result code. */
   QAPI_BLE_OTS_OARC_OPCODE_NOT_SUPPORTED_E    = QAPI_BLE_OTS_OACP_RESULT_CODE_OPCODE_NOT_SUPPORTED,
   /**< Op code not supported result code. */
   QAPI_BLE_OTS_OARC_INVALID_PARAMETER_E       = QAPI_BLE_OTS_OACP_RESULT_CODE_INVALID_PARAMETER,
   /**< Invalid parameter result code. */
   QAPI_BLE_OTS_OARC_INSUFFICIENT_RESOURCES_E  = QAPI_BLE_OTS_OACP_RESULT_CODE_INSUFFICIENT_RESOURCES,
   /**< Insufficient resources result code. */
   QAPI_BLE_OTS_OARC_INVALID_OBJECT_E          = QAPI_BLE_OTS_OACP_RESULT_CODE_INVALID_OBJECT,
   /**< Invalid object result code. */
   QAPI_BLE_OTS_OARC_CHANNEL_UNAVAILABLE_E     = QAPI_BLE_OTS_OACP_RESULT_CODE_CHANNEL_UNAVAILABLE,
   /**< Channel unavailable result code. */
   QAPI_BLE_OTS_OARC_UNSUPPORTED_TYPE_E        = QAPI_BLE_OTS_OACP_RESULT_CODE_UNSUPPORTED_TYPE,
   /**< Unsupported object type result code. */
   QAPI_BLE_OTS_OARC_PROCEDURE_NOT_PERMITTED_E = QAPI_BLE_OTS_OACP_RESULT_CODE_PROCEDURE_NOT_PERMITTED,
   /**< Procedure not permitted result code. */
   QAPI_BLE_OTS_OARC_OBJECT_LOCKED_E           = QAPI_BLE_OTS_OACP_RESULT_CODE_OBJECT_LOCKED,
   /**< Object locked result code. */
   QAPI_BLE_OTS_OARC_OPERATION_FAILED_E        = QAPI_BLE_OTS_OACP_RESULT_CODE_OPERATION_FAILED
   /**< Operation failed result code. */
} qapi_BLE_OTS_OACP_Result_Type_t;

/**
 * Structure that represents the data that is required for an
 * OACP Execute procedure response.
 *
 * This is defined by a higher level specification. It is the
 * application's responsibility to make sure that data in the buffer is
 * formatted properly.
 */
typedef struct qapi_BLE_OTS_OACP_Execute_Response_Data_s
{
   /**
    * Length of the buffer.
    */
   uint16_t Buffer_Length;

   /**
    * Pointer to the buffer that contains the data that will be sent in
    * the response.
    */
   uint8_t *Buffer;
} qapi_BLE_OTS_OACP_Execute_Response_Data_t;

/**
 * Structure that represents the format for the OTS OACP
 * response. The Request_Op_Code field of this structure
 * specifies which Parameter field is valid. Currently, the following
 * fields are valid for the following values of the Request_Op_Code
 * field:
 *
 * @li QAPI_BLE_OTS_OAOC_CALCULATE_CHECKSUM_E - Checksum
 * @li QAPI_BLE_OTS_OAOC_EXECUTE_E            - Execute_Data
 *
 * The Parameter field is only valid if the Result_Code is
 * QAPI_BLE_OTS_OARC_SUCCESS_E.
 */
typedef struct qapi_BLE_OTS_OACP_Response_Data_s
{
   /**
    * Op code for the OACP request.
    */
   qapi_BLE_OTS_OACP_Request_Type_t Request_Op_Code;

   /**
    * Result code for the OACP procedure.
    */
   qapi_BLE_OTS_OACP_Result_Type_t  Result_Code;
   union
   {
      /**
       * Checksum calculated during the OACP Calculate Checksum
       * procedure.
       */
      uint32_t                                  Checksum;

      /**
       * Execute response data from the OACP Execute
       * procedure.
       */
      qapi_BLE_OTS_OACP_Execute_Response_Data_t Execute_Data;
   }
   /**
    * Optional parameter that must be included for certain OACP
    * request op codes.
    */
   Parameter;
} qapi_BLE_OTS_OACP_Response_Data_t;

#define QAPI_BLE_OTS_OACP_RESPONSE_DATA_SIZE                      (sizeof(qapi_BLE_OTS_OACP_Response_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_OACP_Response_Data_t structure.
 */


/**
 * Enumeration that represents the OLCP Procedures that may be set for
 * the Request_Op_Code field of #qapi_BLE_OTS_OLCP_Request_Data_t and
   #qapi_BLE_OTS_OLCP_Response_Data_t structures.
 */
typedef enum
{
   QAPI_BLE_OTS_OLOC_FIRST_E                     = QAPI_BLE_OTS_OLCP_OP_CODE_FIRST,
   /**< OLCP First procedure op code. */
   QAPI_BLE_OTS_OLOC_LAST_E                      = QAPI_BLE_OTS_OLCP_OP_CODE_LAST,
   /**< OLCP Last procedure op code. */
   QAPI_BLE_OTS_OLOC_PREVIOUS_E                  = QAPI_BLE_OTS_OLCP_OP_CODE_PREVIOUS,
   /**< OLCP Previous procedure op code. */
   QAPI_BLE_OTS_OLOC_NEXT_E                      = QAPI_BLE_OTS_OLCP_OP_CODE_NEXT,
   /**< OLCP Next procedure op code. */
   QAPI_BLE_OTS_OLOC_GOTO_E                      = QAPI_BLE_OTS_OLCP_OP_CODE_GO_TO,
   /**< OLCP Go-To procedure op code. */
   QAPI_BLE_OTS_OLOC_ORDER_E                     = QAPI_BLE_OTS_OLCP_OP_CODE_ORDER,
   /**< OLCP Order procedure op code. */
   QAPI_BLE_OTS_OLOC_REQUEST_NUMBER_OF_OBJECTS_E = QAPI_BLE_OTS_OLCP_OP_CODE_REQUEST_NUMBER_OF_OBJECTS,
   /**< OLCP Request Number of Objects procedure op code. */
   QAPI_BLE_OTS_OLOC_CLEAR_MARKING_E             = QAPI_BLE_OTS_OLCP_OP_CODE_CLEAR_MARKING
   /**< OLCP Clear Marking procedure op code. */
} qapi_BLE_OTS_OLCP_Request_Type_t;

/**
 * Enumeration that represents the valid values that controls how the OTS
 * Objects may be sorted on the OTS server if the olcpOrder is set for
 * the Request_Op_Code field of the #qapi_BLE_OTS_OLCP_Request_Data_t
 * structure.
 */
typedef enum
{
   QAPI_BLE_OTS_LSOT_ASCENDING_BY_NAME_E                  = QAPI_BLE_OTS_LIST_SORT_ORDER_ASCENDING_OBJECT_NAME,
   /**< Sort by ascending name. */
   QAPI_BLE_OTS_LSOT_ASCENDING_BY_OBJECT_TYPE_E           = QAPI_BLE_OTS_LIST_SORT_ORDER_ASCENDING_OBJECT_TYPE,
   /**< Sort by ascending object type. */
   QAPI_BLE_OTS_LSOT_ASCENDING_BY_OBJECT_CURRENT_SIZE_E   = QAPI_BLE_OTS_LIST_SORT_ORDER_ASCENDING_OBJECT_CURRENT_SIZE,
   /**< Sort by ascending current size. */
   QAPI_BLE_OTS_LSOT_ASCENDING_BY_OBJECT_FIRST_CREATED_E  = QAPI_BLE_OTS_LIST_SORT_ORDER_ASCENDING_OBJECT_FIRST_CREATED,
   /**< Sort by ascending first created date. */
   QAPI_BLE_OTS_LSOT_ASCENDING_BY_OBJECT_LAST_MODIFIED_E  = QAPI_BLE_OTS_LIST_SORT_ORDER_ASCENDING_OBJECT_LAST_MODIFIED,
   /**< Sort by ascending last modified date. */
   QAPI_BLE_OTS_LSOT_DESCENDING_BY_NAME_E                 = QAPI_BLE_OTS_LIST_SORT_ORDER_DESCENDING_OBJECT_NAME,
   /**< Sort by descending name. */
   QAPI_BLE_OTS_LSOT_DESCENDING_BY_OBJECT_TYPE_E          = QAPI_BLE_OTS_LIST_SORT_ORDER_DESCENDING_OBJECT_TYPE,
   /**< Sort by descending object type. */
   QAPI_BLE_OTS_LSOT_DESCENDING_BY_OBJECT_CURRENT_SIZE_E  = QAPI_BLE_OTS_LIST_SORT_ORDER_DESCENDING_OBJECT_CURRENT_SIZE,
   /**< Sort by descending current size. */
   QAPI_BLE_OTS_LSOT_DESCENDING_BY_OBJECT_FIRST_CREATED_E = QAPI_BLE_OTS_LIST_SORT_ORDER_DESCENDING_OBJECT_FIRST_CREATED,
   /**< Sort by descending first created date. */
   QAPI_BLE_OTS_LSOT_DESCENDING_BY_OBJECT_LAST_MODIFIED_E = QAPI_BLE_OTS_LIST_SORT_ORDER_DESCENDING_OBJECT_LAST_MODIFIED
   /**< Sort by descending last modified date. */
} qapi_BLE_OTS_List_Sort_Order_Type_t;

/**
 * Structure that represents the format for the OTS Object List Control
 * Point (OLCP) request. The Request_Op_Code field of this structure
 * specifies which Parameter field is valid. Currently, the following
 * fields are valid for the following values of the Request_Op_Code
 * field:
 *
 * @li QAPI_BLE_OTS_OLOC_GOTO_E  - Object_ID
 * @li QAPI_BLE_OTS_OLOC_ORDER_E - List_Sort_Order
 *
 */
typedef struct qapi_BLE_OTS_OLCP_Request_Data_s
{
   /**
    * Op code for the OLCP request.
    */
   qapi_BLE_OTS_OLCP_Request_Type_t Request_Op_Code;
   union
   {
      /**
       * OLCP GoTo procedure data.
       */
      qapi_BLE_OTS_UINT48_Data_t          Object_ID;

      /**
       * OLCP Order procedure data.
       */
      qapi_BLE_OTS_List_Sort_Order_Type_t List_Sort_Order;
   }
   /**
    * Optional parameter that must be included for certain OLCP
    * request op codes.
    */
   Parameter;
} qapi_BLE_OTS_OLCP_Request_Data_t;

#define QAPI_BLE_OTS_OLCP_REQUEST_DATA_SIZE                       (sizeof(qapi_BLE_OTS_OLCP_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_OLCP_Request_Data_t structure.
 */

/**
 * Enumeration that represents the OLCP Result types that may be set for
 * the Result_Code field of the #qapi_BLE_OTS_OLCP_Response_Data_t
 * structure.
 */
typedef enum
{
   QAPI_BLE_OTS_OLRC_SUCCESS_E              = QAPI_BLE_OTS_OLCP_RESULT_CODE_SUCCESS,
   /**< Success result code. */
   QAPI_BLE_OTS_OLRC_OPCODE_NOT_SUPPORTED_E = QAPI_BLE_OTS_OLCP_RESULT_CODE_OPCODE_NOT_SUPPORTED,
   /**< Op code not supported result code. */
   QAPI_BLE_OTS_OLRC_INVALID_PARAMETER_E    = QAPI_BLE_OTS_OLCP_RESULT_CODE_INVALID_PARAMETER,
   /**< Invalid parameter result code. */
   QAPI_BLE_OTS_OLRC_OPERATION_FAILED_E     = QAPI_BLE_OTS_OLCP_RESULT_CODE_OPERATION_FAILED,
   /**< Operation failed result code. */
   QAPI_BLE_OTS_OLRC_OUT_OF_BOUNDS_E        = QAPI_BLE_OTS_OLCP_RESULT_CODE_OUT_OF_BOUNDS,
   /**< Out of bounds result code. */
   QAPI_BLE_OTS_OLRC_TOO_MANY_OBJECTS_E     = QAPI_BLE_OTS_OLCP_RESULT_CODE_TOO_MANY_OBJECTS,
   /**< Too many objects result code. */
   QAPI_BLE_OTS_OLRC_NO_OBJECT_E            = QAPI_BLE_OTS_OLCP_RESULT_CODE_NO_OBJECT,
   /**< No object result code. */
   QAPI_BLE_OTS_OLRC_OBJECT_ID_NOT_FOUND_E  = QAPI_BLE_OTS_OLCP_RESULT_CODE_OBJECT_ID_NOT_FOUND,
   /**< Object ID not found result code. */
} qapi_BLE_OTS_OLCP_Result_Type_t;

/**
 * Structure that represents the format for the OLCP
 * response. The Request_Op_Code field of this structure
 * specifies which Parameter field is valid. Currently, the following
 * fields are valid for the following values of the Request_Op_Code
 * field:
 *
 * @li QAPI_BLE_OTS_OLOC_REQUEST_NUMBER_OF_OBJECTS_E - Total_Number_Of_Objects
 *
 * The Parameter field is only valid if the Result_Code is
 * QAPI_BLE_OTS_OLRC_SUCCESS_E.
 */
typedef struct qapi_BLE_OTS_OLCP_Response_Data_s
{
   /**
    * Op code for the OLCP request.
    */
   qapi_BLE_OTS_OLCP_Request_Type_t Request_Op_Code;

   /**
    * Result code for the OLCP procedure.
    */
   qapi_BLE_OTS_OLCP_Result_Type_t  Result_Code;
   union
   {
      /**
       * Total number of OTS Objects for the OLCP Request Number of
       * Objects procedure.
       */
      uint32_t Total_Number_Of_Objects;
   }
   /**
    * Optional parameter that must be included for certain OLCP
    * request op codes.
    */
   Parameter;
} qapi_BLE_OTS_OLCP_Response_Data_t;

#define QAPI_BLE_OTS_OLCP_RESPONSE_DATA_SIZE                      (sizeof(qapi_BLE_OTS_OLCP_Response_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_OLCP_Response_Data_t structure.
 */

/**
 * Enumeration that represents the OTS Object Metadata types.
 *
 * Enumeration that is used to make sure the proper data type is accessed
 * for the #qapi_BLE_OTS_Object_Metadata_Data_t union.
 */
typedef enum
{
   QAPI_BLE_OTS_OMT_OBJECT_NAME_E,
   /**< Object name. */
   QAPI_BLE_OTS_OMT_OBJECT_TYPE_E,
   /**< Object type. */
   QAPI_BLE_OTS_OMT_OBJECT_SIZE_E,
   /**< Object size. */
   QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E,
   /**< Object First Created. */
   QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E,
   /**< Object Last Modified. */
   QAPI_BLE_OTS_OMT_OBJECT_ID_E,
   /**< Object ID. */
   QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E
   /**< Object properties. */
} qapi_BLE_OTS_Object_Metadata_Type_t;

/**
 * Union that represents the OTS Object Metadata that may be received for
 * an QAPI_BLE_OTS_ET_SERVER_WRITE_OBJECT_METADATA_REQUEST_E event or
 * sent for an QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_METADATA_REQUEST_E
 * event response.
 */
typedef union
{
   /**
    * OTS Object Name.
    */
   qapi_BLE_OTS_Name_Data_t        Name;

   /**
    * OTS Object Type.
    */
   qapi_BLE_GATT_UUID_t            Type;

   /**
    * OTS Object Size.
    */
   qapi_BLE_OTS_Object_Size_Data_t Size;

   /**
    * OTS Object First Created Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t   First_Created;

   /**
    * OTS Object Last Modified Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t   Last_Modified;

   /**
    * OTS Object ID.
    */
   qapi_BLE_OTS_UINT48_Data_t      ID;

   /**
    * OTS Object Properties.
    */
   uint32_t                        Properties;
} qapi_BLE_OTS_Object_Metadata_Data_t;

/**
 * Structure that represents the Date/Time Range data type that may be
 * used for the #qapi_BLE_OTS_Object_List_Filter_Data_t structure.
 */
typedef struct qapi_BLE_OTS_Date_Time_Range_Data_s
{
   /**
    * Minimum OTS Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t Minimum;

   /**
    * Naximum OTS Date/Time.
    */
   qapi_BLE_OTS_Date_Time_Data_t Maximum;
} qapi_BLE_OTS_Date_Time_Range_Data_t;

#define QAPI_BLE_OTS_DATE_TIME_RANGE_DATA_SIZE                    (sizeof(qapi_BLE_OTS_Date_Time_Range_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Date_Time_Range_Data_t structure.
 */

/**
 * Structure that represents the Size Range data type that may be used
 * for the #qapi_BLE_OTS_Object_List_Filter_Data_t structure.
 */
typedef struct qapi_BLE_OTS_Size_Range_Data_s
{
   /**
    * Minimum OTS size.
    */
   uint32_t Minimum;

   /**
    * Maximum OTS size.
    */
   uint32_t Maximum;
} qapi_BLE_OTS_Size_Range_Data_t;

#define QAPI_BLE_OTS_SIZE_RANGE_DATA_SIZE                         (sizeof(qapi_BLE_OTS_Size_Range_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Size_Range_Data_t structure.
 */

/**
 * Enumeration that represents the Object List Filter instances.
 *
 * This enumeratation directly corresponds to
 * QAPI_BLE_OTS_MAXIMUM_SUPPORTED_OBJECT_LIST_FILTERS, found in
 * qapi_ble_otstypes.h, that must be present if the OTS Object List
 * Filter is supported by the OTS server.
 */
typedef enum
{
   QAPI_BLE_OTS_LFI_ONE_E,  /**< List filter instance one. */
   QAPI_BLE_OTS_LFI_TWO_E,  /**< List filter instance two. */
   QAPI_BLE_OTS_LFI_THREE_E /**< List filter instance three. */
} qapi_BLE_OTS_Object_List_Filter_Instance_t;

/**
 * Enumeration that represents the Object List Filter types that may be
 * set for the Type field of the #qapi_BLE_OTS_Object_List_Filter_Data_t
 * structure.
 */
typedef enum
{
   QAPI_BLE_OTS_LFT_NO_FILTER_E              = QAPI_BLE_OTS_OBJECT_LIST_FILTER_NO_FILTER,
   /**< No filter. */
   QAPI_BLE_OTS_LFT_NAME_STARTS_WITH_E       = QAPI_BLE_OTS_OBJECT_LIST_FILTER_NAME_STARTS_WITH,
   /**< Name starts with filter. */
   QAPI_BLE_OTS_LFT_NAME_ENDS_WITH_E         = QAPI_BLE_OTS_OBJECT_LIST_FILTER_NAME_ENDS_WITH,
   /**< Name ends with filter. */
   QAPI_BLE_OTS_LFT_NAME_CONTAINS_E          = QAPI_BLE_OTS_OBJECT_LIST_FILTER_NAME_CONTAINS,
   /**< Name contains filter. */
   QAPI_BLE_OTS_LFT_NAME_IS_EXACTLY_E        = QAPI_BLE_OTS_OBJECT_LIST_FILTER_NAME_IS_EXACTLY,
   /**< Name is filter. */
   QAPI_BLE_OTS_LFT_OBJECT_TYPE_E            = QAPI_BLE_OTS_OBJECT_LIST_FILTER_OBJECT_TYPE,
   /**< Object type filter. */
   QAPI_BLE_OTS_LFT_CREATED_BETWEEN_E        = QAPI_BLE_OTS_OBJECT_LIST_FILTER_CREATED_BETWEEN,
   /**< Created between filter. */
   QAPI_BLE_OTS_LFT_MODIFIED_BETWEEN_E       = QAPI_BLE_OTS_OBJECT_LIST_FILTER_MODIFIED_BETWEEN,
   /**< Modified between filter. */
   QAPI_BLE_OTS_LFT_CURRENT_SIZE_BETWEEN_E   = QAPI_BLE_OTS_OBJECT_LIST_FILTER_CURRENT_SIZE_BETWEEN,
   /**< Current size between filter. */
   QAPI_BLE_OTS_LFT_ALLOCATED_SIZE_BETWEEN_E = QAPI_BLE_OTS_OBJECT_LIST_FILTER_ALLOCATED_SIZE_BETWEEN,
   /**< Allocated size between filter. */
   QAPI_BLE_OTS_LFT_MARKED_OBJECTS_E         = QAPI_BLE_OTS_OBJECT_LIST_FILTER_MARKED_OBJECTS,
   /**< Marked objects filter. */
} qapi_BLE_OTS_Object_List_Filter_Type_t;

/**
 * Structure that represents the format for the OTS Object List Filter
 * Characteristic instance. The Type field of this structure specifies
 * which data field is valid. Currently the following fields are valid
 * for the following values of the Type field:
 *
 * @li QAPI_BLE_OTS_LFT_NAME_STARTS_WITH_E       -- Name
 * @li QAPI_BLE_OTS_LFT_NAME_ENDS_WITH_E         -- Name
 * @li QAPI_BLE_OTS_LFT_NAME_CONTAINS_E          -- Name
 * @li QAPI_BLE_OTS_LFT_NAME_IS_EXACTLY_E        -- Name
 * @li QAPI_BLE_OTS_LFT_OBJECT_TYPE_E            -- Type
 * @li QAPI_BLE_OTS_LFT_CREATED_BETWEEN_E        -- Time_Range
 * @li QAPI_BLE_OTS_LFT_MODIFIED_BETWEEN_E       -- Time_Range
 * @li QAPI_BLE_OTS_LFT_ALLOCATED_SIZE_BETWEEN_E -- Size_Range
 * @li QAPI_BLE_OTS_LFT_CURRENT_SIZE_BETWEEN_E   -- Size_Range
 *
 */
typedef struct qapi_BLE_OTS_Object_List_Filter_Data_s
{
   /**
    * OTS Object List Filter type.
    */
   qapi_BLE_OTS_Object_List_Filter_Type_t Type;
   union
   {
      /**
       * OTS Object Name.
       */
      qapi_BLE_OTS_Name_Data_t            Name;

      /**
       * OTS Object Type.
       */
      qapi_BLE_GATT_UUID_t                Type;

      /**
       * OTS Object Date/Time range.
       */
      qapi_BLE_OTS_Date_Time_Range_Data_t Time_Range;

      /**
       * OTS Object Size range.
       */
      qapi_BLE_OTS_Size_Range_Data_t      Size_Range;
   }
   /**
    * Optional parameter that must be included for certain OTS Object
    * List Filter types.
    */
   Data;
} qapi_BLE_OTS_Object_List_Filter_Data_t;

#define QAPI_BLE_OTS_OBJECT_LIST_FILTER_DATA_SIZE                 (sizeof(qapi_BLE_OTS_List_Filter_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Object_List_Filter_Data_t structure.
 */

/**
 * Structure that represents the format for the OTS Object Changed
 * Characteristic.
 *
 * The Flags parameter is a bit mask that has the form
 * QAPI_BLE_OTS_OBJECT_CHANGED_FLAGS_XXX and can be found in
 * qapi_ble_otstypes.h.
 */
typedef struct qapi_BLE_OTS_Object_Changed_Data_s
{
   /**
    * Flags that indicate the changes for the OTS Object specified
    * by the OTS Object ID.
    */
   uint8_t                     Flags;

   /**
    * OTS Object ID of the OTS Object that changed.
    */
   qapi_BLE_OTS_UINT48_Data_t  Object_ID;
} qapi_BLE_OTS_Object_Changed_Data_t;

#define QAPI_BLE_OTS_OBJECT_CHANGED_DATA_SIZE                     (sizeof(qapi_BLE_OTS_Object_Changed_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Object_Changed_Data_t structure.
 */

/**
 * Enumeration that represents the OTS characteristic types that contain
 * a CCCD. This type
 * will indicate the CCCD that has been requested for the
 * QAPI_BLE_OTS_ET_SERVER_READ_CCCD_REQUEST_E AND
 * QAPI_BLE_OTS_ET_SERVER_WRITE_CCCD_REQUEST_E events.
 *
 * For each event, it is up to the application to return (or write) the
 * correct CCCD based on this value.
 */
typedef enum
{
   QAPI_BLE_OTS_CCT_OACP_E,          /**< OACP. */
   QAPI_BLE_OTS_CCT_OLCP_E,          /**< OLCP. */
   QAPI_BLE_OTS_CCT_OBJECT_CHANGED_E /**< Object Changed. */
} qapi_BLE_OTS_CCCD_Characteristic_Type_t;

/**
 * Enumeration that represents all the events generated by the OTS
 * service. These are used to determine the type of each event generated,
 * and to ensure the proper union element is accessed for the
 * #qapi_BLE_OTS_Event_Data_t structure.
 */
typedef enum
{
   QAPI_BLE_OTS_ET_SERVER_READ_OTS_FEATURE_REQUEST_E,
   /**< Read Feature request event. */
   QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_METADATA_REQUEST_E,
   /**< Read Object Metadata request event. */
   QAPI_BLE_OTS_ET_SERVER_WRITE_OBJECT_METADATA_REQUEST_E,
   /**< Write Object Metadata request event. */
   QAPI_BLE_OTS_ET_SERVER_WRITE_OACP_REQUEST_E,
   /**< Write OACP request event. */
   QAPI_BLE_OTS_ET_SERVER_WRITE_OLCP_REQUEST_E,
   /**< Write OLCP request event. */
   QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_LIST_FILTER_REQUEST_E,
   /**< Read Object List Filter request event. */
   QAPI_BLE_OTS_ET_SERVER_WRITE_OBJECT_LIST_FILTER_REQUEST_E,
   /**< Write Object List Filter request event. */
   QAPI_BLE_OTS_ET_SERVER_READ_CCCD_REQUEST_E,
   /**< Read CCCD request event. */
   QAPI_BLE_OTS_ET_SERVER_WRITE_CCCD_REQUEST_E,
   /**< Write CCCD request event. */
   QAPI_BLE_OTS_ET_SERVER_PREPARE_WRITE_REQUEST_E,
   /**< Prepare write request event. */
   QAPI_BLE_OTS_ET_SERVER_CONFIRMATION_DATA_E
   /**< Confirmation event. */
} qapi_BLE_OTS_Event_Type_t;

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to read the
 * OTS Feature Characteristic.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Read_OTS_Feature_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Read_OTS_Feature_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                        InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                        ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                        TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;
} qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t;

#define QAPI_BLE_OTS_READ_OTS_FEATURE_REQUEST_DATA_SIZE           (sizeof(qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to read an OTS
 * Object's Metadata Characteristic.
 *
 * The Offset field will be zero for the GATT Read Value request, which
 * is always sent first to read the OTS Object Name. However, if the
 * entire OTS Object Name cannot fit in the GATT Read Value response due
 * to the GATT Maximum Transmission Unit (MTU) constraints, the OTS
 * client must issue GATT Read Long Value requests until the entire OTS
 * Object Name has been read. If a GATT Read Long Value request has been
 * sent, the Offset field will be nonzero.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Read_Object_Metadata_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Read_Object_Metadata_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                            InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                            ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t     ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                            TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                  RemoteDevice;

   /**
    * OTS Object Metadata Characteristic that has been requested to
    * be read.
    */
   qapi_BLE_OTS_Object_Metadata_Type_t Type;

   /**
    * Offset field is used if the Type field is set to
    * QAPI_BLE_OTS_OMT_OBJECT_NAME_E and is used to index the starting
    * offset for reading the OTS Object Name.
    */
   uint8_t                             Offset;
} qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t;

#define QAPI_BLE_OTS_READ_OBJECT_METADATA_REQUEST_DATA_SIZE       (sizeof(qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t
 * structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to write an OTS
 * Object's Metadata Characteristic.
 *
 * The Type field identifies the OTS Object Metadata
 * Characteristic that is being written. The following OTS Object
 * Metadata Characteristics may be written (if they are supported by the
 * OTS server). For each listed OTS Object Metadata Characteristic the
 * union element of the Metadata field will be valid.
 *
 * @li QAPI_BLE_OTS_OMT_OBJECT_NAME_E          -- Name
 * @li QAPI_BLE_OTS_OMT_OBJECT_FIRST_CREATED_E -- First_Created
 * @li QAPI_BLE_OTS_OMT_OBJECT_LAST_MODIFIED_E -- Last_Modified
 * @li QAPI_BLE_OTS_OMT_OBJECT_PROPERTIES_E    -- Object_Properties
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Write_Object_Metadata_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Write_Object_Metadata_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                            InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                            ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t     ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                            TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                  RemoteDevice;

   /**
    * OTS Object Metadata Characteristic that has been requested to
    * be written. Not all OTS Object Metadata Characteristics may be
    * written.
    */
   qapi_BLE_OTS_Object_Metadata_Type_t Type;

   /**
    * OTS Object Metadata Characteristic data that has been requested
    * to be written. The union element depends on the value of the Type
    * field.
    */
   qapi_BLE_OTS_Object_Metadata_Data_t Metadata;
} qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t;

#define QAPI_BLE_OTS_WRITE_OBJECT_METADATA_REQUEST_DATA_SIZE      (sizeof(qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t
 * structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to write the
 * OTS Object Action Control Point (OACP) Characteristic.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Write_OACP_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Write_OACP_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                         InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                         TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * The OACP request data.
    */
   qapi_BLE_OTS_OACP_Request_Data_t RequestData;
} qapi_BLE_OTS_Write_OACP_Request_Data_t;

#define QAPI_BLE_OTS_WRITE_OACP_REQUEST_DATA_SIZE                 (sizeof(qapi_BLE_OTS_Write_OACP_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Write_OACP_Request_Data_t structure.
 */


/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to write the
 * OTS OLCP Characteristic.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Write_OLCP_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Write_OLCP_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                         InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                         ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t  ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                         TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t               RemoteDevice;

   /**
    * OLCP request data.
    */
   qapi_BLE_OTS_OLCP_Request_Data_t RequestData;
} qapi_BLE_OTS_Write_OLCP_Request_Data_t;

#define QAPI_BLE_OTS_WRITE_OLCP_REQUEST_DATA_SIZE                 (sizeof(qapi_BLE_OTS_Write_OLCP_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Write_OLCP_Request_Data_t structure.
 */


/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to read an OTS
 * Object List Filter Characteristic instance.
 *
 * The Offset field will be zero for the GATT Read Value request, which
 * is always sent first to read the OTS Object List Filter instance.
 * However, if the OTS Object List Filter instance is set to any of the
 * following:
 *
 * @li QAPI_BLE_OTS_LFT_NAME_STARTS_WITH_E
 * @li QAPI_BLE_OTS_LFT_NAME_ENDS_WITH_E
 * @li QAPI_BLE_OTS_LFT_NAME_CONTAINS_E
 * @li QAPI_BLE_OTS_LFT_NAME_IS_EXACTLY_E
 *
 * and the OTS Object Name response parameter cannot fit in the GATT
 * Read Value response due to the GATT Maximum Transmission Unit (MTU)
 * constraints, the OTS client must issue GATT Read Long Value
 * requests until the entire OTS Object Name used for the OTS Object List
 * Filter instance has been read. If a GATT Read Long Value request has
 * been sent, the Offset field will be nonzero.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Read_Object_List_Filter_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                                   InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                                   ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t            ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                                   TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                         RemoteDevice;

   /**
    * OTS Object List Filter instance that has been requested to be
    * read.
    */
   qapi_BLE_OTS_Object_List_Filter_Instance_t Instance;

   /**
    * Offset field is used to index the starting
    * offset for the OTS Object List Filter instance's OTS Object Name
    * data. This field is only used for certain OTS Object List Filter
    * instance types.
    */
   uint8_t                                    Offset;
} qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t;

#define QAPI_BLE_OTS_READ_OBJECT_LIST_FILTER_REQUEST_DATA_SIZE    (sizeof(qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t
 * structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to write an
 * OTS Object List Filter Characteristic instance.
 *
 * The application is responsible for copying the Name data of the
 * ListFilterData field when the event is received if the Type field of
 * the qapi_BLE_OTS_Object_List_Filter_Data_t structure is set to:
 *
 * @li QAPI_BLE_OTS_LFT_NAME_STARTS_WITH_E
 * @li QAPI_BLE_OTS_LFT_NAME_ENDS_WITH_E
 * @li QAPI_BLE_OTS_LFT_NAME_CONTAINS_E
 * @li QAPI_BLE_OTS_LFT_NAME_IS_EXACTLY_E
 *
 * Otherwise, the data will be lost when the callback returns.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Write_Object_List_Filter_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                                   InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                                   ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t            ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                                   TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                         RemoteDevice;

   /**
    * OTS Object List Filter instance that has been requested to be
    * written.
    */
   qapi_BLE_OTS_Object_List_Filter_Instance_t Instance;

   /**
    * OTS Object List Filter instance data that has been requested
    * to be written.
    */
   qapi_BLE_OTS_Object_List_Filter_Data_t     ListFilterData;
} qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t;

#define QAPI_BLE_OTS_WRITE_OBJECT_LIST_FILTER_REQUEST_DATA_SIZE   (sizeof(qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t
 * structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to read an
 * OTS characteristic's CCCD.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Read_CCCD_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Read_CCCD_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                                InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                                ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t         ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                                TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                      RemoteDevice;

   /**
    * Identifies the requested CCCD based on the OTS characteristic
    * type.
    */
   qapi_BLE_OTS_CCCD_Characteristic_Type_t Type;
} qapi_BLE_OTS_Read_CCCD_Request_Data_t;

#define QAPI_BLE_OTS_READ_CCCD_REQUEST_DATA_SIZE                  (sizeof(qapi_BLE_OTS_Read_CCCD_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Read_CCCD_Request_Data_t structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to read an
 * OTS characteristic's CCCD.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Write_CCCD_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Write_CCCD_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                                InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                                ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t         ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                                TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                      RemoteDevice;

   /**
    * Identifies the requested CCCD based on the OTS characteristic
    * type.
    */
   qapi_BLE_OTS_CCCD_Characteristic_Type_t Type;

   /**
    * CCCD value that has been requested to be written.
    */
   uint16_t                                Configuration;
} qapi_BLE_OTS_Write_CCCD_Request_Data_t;

#define QAPI_BLE_OTS_WRITE_CCCD_REQUEST_DATA_SIZE                 (sizeof(qapi_BLE_OTS_Write_CCCD_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Write_CCCD_Request_Data_t structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an OTS server when an OTS client has sent a request to prepare data
 * for an OTS characteristic write request.
 *
 * This event is primarily provided to reject a GATT Prepare Write
 * request for optional security reasons, such as the OTS client has
 * insufficient authentication, authorization, or encryption. We will
 * not pass the prepared data up to the application until the the GATT
 * Execute Write request has been received by the OTS server, and the
 * prepared writes are not cancelled. If the prepared data is written,
 * the appropriate OTS event will be dispatched to the application.
 * Otherwise, the prepared data will be cleared.
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_OTS_Prepare_Write_Request_Response() function.
 */
typedef struct qapi_BLE_OTS_Prepare_Write_Request_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                        InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                        ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                        TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;
} qapi_BLE_OTS_Prepare_Write_Request_Data_t;

#define QAPI_BLE_OTS_PREPARE_WRITE_REQUEST_DATA_SIZE              (sizeof(qapi_BLE_OTS_Prepare_Write_Request_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Prepare_Write_Request_Data_t structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to the OTS server when an OTS client has responded to an outstanding
 * indication that was previously sent by the OTS server.
 */
typedef struct qapi_BLE_OTS_Confirmation_Data_s
{
   /**
    * OTS instance that dispatched the event.
    */
   uint32_t                        InstanceID;

   /**
    * GATT connection ID for the connection with the OTS client
    * that made the request.
    */
   uint32_t                        ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the OTS client.
    */
   qapi_BLE_GATT_Connection_Type_t ConnectionType;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                        TransactionID;

   /**
    * Bluetooth address of the OTS client that made the request.
    */
   qapi_BLE_BD_ADDR_t              RemoteDevice;

   /**
    * Status of the outstanding indication. Values will be of the
    * form QAPI_BLE_GATT_CONFIRMATION_STATUS_XXX and can be found in
    * qapi_ble_gatt.h.
    */
   uint8_t                         Status;

   /**
    * Number of bytes successfully indicated.
    */
   uint16_t                        BytesWritten;
} qapi_BLE_OTS_Confirmation_Data_t;

#define QAPI_BLE_OTS_CONFIRMATION_DATA_SIZE                       (sizeof(qapi_BLE_OTS_Confirmation_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Confirmation_Data_t structure.
 */

/**
 * Structure that represents the container structure for holding all the
 * OTS server event data for an OTS instance.
 */
typedef struct qapi_BLE_OTS_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_OTS_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                  Event_Data_Size;

   union
   {
      /**
       * OTS Read CCCD event data.
       */
      qapi_BLE_OTS_Read_CCCD_Request_Data_t                *OTS_Read_CCCD_Request_Data;

      /**
       * OTS Write CCCD event data.
       */
      qapi_BLE_OTS_Write_CCCD_Request_Data_t               *OTS_Write_CCCD_Request_Data;

      /**
       * OTS Read Feature event data.
       */
      qapi_BLE_OTS_Read_OTS_Feature_Request_Data_t         *OTS_Read_OTS_Feature_Request_Data;

      /**
       * OTS Read Object Metadata event data.
       */
      qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t     *OTS_Read_Object_Metadata_Request_Data;

      /**
       * OTS Write Object Metadata event data.
       */
      qapi_BLE_OTS_Write_Object_Metadata_Request_Data_t    *OTS_Write_Object_Metadata_Request_Data;

      /**
       * OTS Write OACP event data.
       */
      qapi_BLE_OTS_Write_OACP_Request_Data_t               *OTS_Write_OACP_Request_Data;

      /**
       * OTS Write OLCP event data.
       */
      qapi_BLE_OTS_Write_OLCP_Request_Data_t               *OTS_Write_OLCP_Request_Data;

      /**
       * OTS Read Object List Filter instance event data.
       */
      qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t  *OTS_Read_Object_List_Filter_Request_Data;

      /**
       * OTS Write Object List Filter instance event data.
       */
      qapi_BLE_OTS_Write_Object_List_Filter_Request_Data_t *OTS_Write_Object_List_Filter_Request_Data;

      /**
       * OTS Prepared Write event data.
       */
      qapi_BLE_OTS_Prepare_Write_Request_Data_t            *OTS_Prepare_Write_Request_Data;

      /**
       * OTS Confirmation event data.
       */
      qapi_BLE_OTS_Confirmation_Data_t                     *OTS_Confirmation_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_OTS_Event_Data_t;

#define QAPI_BLE_OTS_EVENT_DATA_SIZE                              (sizeof(qapi_BLE_OTS_Event_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Event_Data_t structure.
 */

   /* Object Transfer Channel (OTC) enumerations, constants, structures */
   /* and events.                                                       */

/**
 * Enumeration that represents the supported connection roles for the
 * Object Transfer Channel (OTC).
 */
typedef enum
{
   QAPI_BLE_OTS_CR_CLIENT_E, /**< Client role. */
   QAPI_BLE_OTS_CR_SERVER_E  /**< Server role. */
} qapi_BLE_OTS_Channel_Connection_Role_t;

/**
 * Enumeration that represents the Object Transfer Channel (OTC)
 * connection types.
 */
typedef enum
{
   QAPI_BLE_OTS_OCT_LE_E,     /**< LE connection. */
   QAPI_BLE_OTS_OCT_BR_EDR_E  /**< BR/EDR connection. */
} qapi_BLE_OTS_Channel_Connection_Type_t;

/**
 * Enumeration that represents the supported
 * OTC connection modes supported by an OTS server.
 *
 * The QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E allows the OTS server to
 * explicitly authorize OTC connections from OTS clients. The
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_REQUEST_INDICATION_E event will be
 * received if this mode is set and the
 * qapi_BLE_OTS_Channel_Open_Connection_Request_Response() function must
 * be used to explicitly accept/reject the connection request.
 */
typedef enum
{
   QAPI_BLE_OTS_CCM_AUTOMATIC_ACCEPT_E, /**< Auto accept. */
   QAPI_BLE_OTS_CCM_AUTOMATIC_REJECT_E, /**< Auto reject. */
   QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E     /**< Manual accept. */
} qapi_BLE_OTS_Channel_Connection_Mode_t;

/**
 * Enumeration that represents all events generated for the OTC.
 * These are used to determine the type of
 * each event generated, and to ensure the proper union element is
 * accessed for the qapi_BLE_OTS_Channel_Event_Data_t structure.
 */
typedef enum
{
   QAPI_BLE_OTS_CHANNEL_ET_OPEN_INDICATION_E,
   /**< Connection open indication event. */
   QAPI_BLE_OTS_CHANNEL_ET_OPEN_REQUEST_INDICATION_E,
   /**< Connection open request indication event. */
   QAPI_BLE_OTS_CHANNEL_ET_OPEN_CONFIRMATION_E,
   /**< Connection open confirmation event. */
   QAPI_BLE_OTS_CHANNEL_ET_CLOSE_INDICATION_E,
   /**< Connection close indication event. */
   QAPI_BLE_OTS_CHANNEL_ET_DATA_INDICATION_E,
   /**< Data indication event. */
   QAPI_BLE_OTS_CHANNEL_ET_DATA_ERROR_INDICATION_E,
   /**< Data error indication event. */
   QAPI_BLE_OTS_CHANNEL_ET_BUFFER_EMPTY_INDICATION_E
   /**< Buffer empty indication event. */
} qapi_BLE_OTS_Channel_Event_Type_t;

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_INDICATION_E event. This event may only
 * be received if the OTC mode is set to
 * QAPI_BLE_OTS_CCM_AUTOMATIC_ACCEPT_E.
 *
 * The OTS server must store the MaxSDUSize, which is represents maximum
 * Service Data Unit (SDU) that the OTS server may send over the OTC
 * It is the application's responsibility to make
 * sure that this size is not exceeded for the Data_Length parameter of
 * the qapi_BLE_OTS_Channel_Send_Data() function.
 *
 * The OTS server must store the CID, which is required for OTC
 * OTC functions that specify a OTC.
 *
 * The Role field will always be set to QAPI_BLE_OTS_CR_SERVER_E for this
 * event, since it is always received by the OTS server.
 *
 * The InitialCredits field is only valid if the Type field is set to
 * QAPI_BLE_OTS_OCT_LE_E, since only LE OTS Channel connections support
 * the LE based credit mode.
 */
typedef struct qapi_BLE_OTS_Channel_Open_Indication_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Maximum SDU. This reprents the maximum
    * amount of data that may sent in an SDU.
    */
   uint16_t                               MaxSDUSize;

   /**
    * Initial LE credits for the OTC connection.
    */
   uint16_t                               InitialCredits;
} qapi_BLE_OTS_Channel_Open_Indication_Data_t;

#define QAPI_BLE_OTS_CHANNEL_OPEN_INDICATION_DATA_SIZE            (sizeof(qapi_BLE_OTS_Channel_Open_Indication_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Open_Indication_Data_t structure.
 */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_REQUEST_INDICATION_E event. This event
 * may only be received if the OTC mode is set
 * to QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E.
 *
 * The OTS server must store the MaxSDUSize, which is represents the maximum
 * SDU that the OTS server may send over the OTC
 * It is the application's responsibility to make
 * sure that this size is not exceeded for the Data_Length parameter of
 * the qapi_BLE_OTS_Channel_Send_Data() function.
 *
 * The OTS server must store the CID, which is required for OTC
 * OTC functions that specify an OTC.
 *
 * The Role field will always be set to QAPI_BLE_OTS_CR_SERVER_E for this
 * event, since it is always received by the OTS server.
 *
 * The qapi_BLE_OTS_Channel_Open_Connection_Request_Response() function
 * must be called after this event is received to send the response for
 * the OTC connection request.
 *
 * The MaxSDUSize and InitialCredits fields are only valid if the Type
 * field is set to QAPI_BLE_OTS_OCT_LE_E, since BR/EDR OTS Channel
 * connections will dispatch the
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_INDICATION_E event if the connection
 * request is accepted. If the Type field is set to
 * QAPI_BLE_OTS_OCT_BR_EDR_E, these fields will be received in
 * the QAPI_BLE_OTS_CHANNEL_ET_OPEN_INDICATION_E event.
 */
typedef struct qapi_BLE_OTS_Channel_Open_Request_Indication_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Maximum SDU. This reprents the maximum
    * amount of data that may sent in an SDU.
    */
   uint16_t                               MaxSDUSize;

   /**
    * Initial LE credits for the OTC connection.
    */
   uint16_t                               InitialCredits;
} qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t;

#define QAPI_BLE_OTS_CHANNEL_OPEN_REQUEST_INDICATION_DATA_SIZE    (sizeof(qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t
 * structure.
 */

   /* The following constants represent the valid values that are       */
   /* possible to received for the Status field of the                  */
   /* QAPI_BLE_OTS_CHANNEL_ET_OPEN_CONFIRMATION_E event.                */
#define QAPI_BLE_OTS_CHANNEL_OPEN_STATUS_SUCCESS                  (0x0000)
/**< Connection succesfully opened. */
#define QAPI_BLE_OTS_CHANNEL_OPEN_STATUS_CONNECTION_TIMEOUT       (0x0001)
/**< Connection timed out. */
#define QAPI_BLE_OTS_CHANNEL_OPEN_STATUS_CONNECTION_REFUSED       (0x0002)
/**< Connection was refused. */
#define QAPI_BLE_OTS_CHANNEL_OPEN_STATUS_UNKNOWN_ERROR            (0x0003)
/**< Connection failed due to an unknown error. */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_CONFIRMATION_E event. This event may only
 * be received if the OTC connection procedure
 * has completed.
 *
 * The OTS server must store the MaxSDUSize, which is represents maximum
 * SDU that the OTS server may send over the OTC.
 * It is the application's responsibility to make
 * sure that this size is not exceeded for the Data_Length parameter of
 * the qapi_BLE_OTS_Channel_Send_Data() function.
 *
 * The OTS server must store the CID, which is required for OTC
 * functions that specify an OTC.
 *
 * The Role field will always be set to QAPI_BLE_OTS_CR_CLIENT_E for this
 * event, since it is always received by the OTS client.
 *
 * The InitialCredits field is only valid if the Type field is set to
 * QAPI_BLE_OTS_OCT_LE_E, since only LE OTS Channel connections support
 * the LE based credit mode.
 */
typedef struct qapi_BLE_OTS_Channel_Open_Confirmation_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Status of the OTC connection.
    */
   uint16_t                               Status;

   /**
    * Maximum SDU. This reprents the maximum
    * amount of data that may sent in an SDU.
    */
   uint16_t                               MaxSDUSize;

   /**
    * Initial LE credits for the OTC connection.
    */
   uint16_t                               InitialCredits;
} qapi_BLE_OTS_Channel_Open_Confirmation_Data_t;

#define QAPI_BLE_OTS_CHANNEL_OPEN_CONFIRMATION_DATA_SIZE          (sizeof(qapi_BLE_OTS_Channel_Open_Confirmation_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Open_Confirmation_Data_t structure.
 */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_CLOSE_INDICATION_E event. This event may only
 * be received if the OTC connection procedure
 * has completed.
 *
 * Under normal circumstances, the OTS server will receive this event
 * from the OTS client (OTS client normally disconnects the OTC).
 * However, if an error occurs on the OTS server, the OTS server may
 * disconnect the channel.
 */
typedef struct qapi_BLE_OTS_Channel_Close_Indication_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Reason for the disconnection.
    */
   uint8_t                                Reason;
} qapi_BLE_OTS_Channel_Close_Indication_Data_t;

#define QAPI_BLE_OTS_CHANNEL_CLOSE_INDICATION_DATA_SIZE           (sizeof(qapi_BLE_OTS_Channel_Close_Indication_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Close_Indication_Data_t structure.
 */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_DATA_INDICATION_E event.
 *
 * The CreditsConsumed field is only valid if the Type field is set to
 * QAPI_BLE_OTS_OCT_LE_E, since only LE Connections support the LE based
 * credit mode.
 */
typedef struct qapi_BLE_OTS_Channel_Data_Indication_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Length of data received in the data indication.
    */
   uint16_t                               DataLength;

   /**
    * Pointer to the data received in the data indication.
    */
   uint8_t                               *Data;

   /**
    * Number of LE credits that were consumed for the data
    * indication.
    */
   uint16_t                               CreditsConsumed;
} qapi_BLE_OTS_Channel_Data_Indication_Data_t;

#define QAPI_BLE_OTS_CHANNEL_DATA_INDICATION_DATA_SIZE            (sizeof(qapi_BLE_OTS_Channel_Data_Indication_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Data_Indication_Data_t structure.
 */

   /* The following constants represent the possible values that may be */
   /* received for the Error field of the                               */
   /* qapi_BLE_OTS_Channel_Data_Error_Indication_t structure below.     */
#define QAPI_BLE_OTS_DATA_ERROR_MTU_EXCEEDED                      (QAPI_BLE_L2CAP_DATA_READ_STATUS_MTU_EXCEEDED)
/**< MTU exceeded data error. */
#define QAPI_BLE_OTS_DATA_ERROR_PDU_TIMEOUT                       (QAPI_BLE_L2CAP_DATA_READ_STATUS_RECEIVE_TIMEOUT)
/**< PDU timeout data error. */
#define QAPI_BLE_OTS_DATA_ERROR_PDU_LOST                          (QAPI_BLE_L2CAP_DATA_READ_STATUS_LOST_PACKET_ERROR)
/**< PDU lost data error. */
#define QAPI_BLE_OTS_DATA_ERROR_INVALID_SDU_SIZE                  (QAPI_BLE_L2CAP_DATA_READ_STATUS_SIZE_ERROR)
/**< Invalid SDU size data error. */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_DATA_ERROR_INDICATION_E event.
 *
 * This event will only be received if the Type field is set to
 * QAPI_BLE_OTS_OCT_BR_EDR_E, since BR/EDR OTS Channel connections must
 * use the Enhanced Retransmission Mode (ERTM).
 *
 * If the QAPI_BLE_OTS_DATA_ERROR_MTU_EXCEEDED or
 * QAPI_BLE_OTS_DATA_ERROR_INVALID_SDU_SIZE is set for the Error field,
 * the local device should assume the transfer has failed and
 * disconnect the channel. These should not be received, since these
 * error codes indicate an internal error.
 *
 * Since this event is only for BR/EDR OTS Channel connections using
 * ERTM, the OTS_DATA_ERROR_PDU_TIMEOUT and OTS_DATA_ERROR_PDU_LOST
 * errors are only meant to inform the application that a PDU has not
 * been received. Error recovery will be attempted to recover the PDUs
 * that have not been received, since ERTM is used, however, it is worth
 * noting that if the maximum number of transmit attempts has been
 * reached for the PDU that was not received, the OTS Channel will
 * be disconnected.
 */
typedef struct qapi_BLE_OTS_Channel_Data_Error_Indication_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;

   /**
    * Error that occured.
    */
   uint16_t                               Error;
} qapi_BLE_OTS_Channel_Data_Error_Indication_t;

#define QAPI_BLE_OTS_CHANNEL_DATA_ERROR_INDICATION_DATA_SIZE      (sizeof(qapi_BLE_OTS_Channel_Data_Error_Indication_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Data_Error_Indication_t structure.
 */

/**
 * Structure that represents the event data that is received for the
 * QAPI_BLE_OTS_CHANNEL_ET_BUFFER_EMPTY_INDICATION_E event.
 */
typedef struct qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_s
{
   /**
    * Bluetooth address of the OTS client that sent the connection
    * request.
    */
   qapi_BLE_BD_ADDR_t                     RemoteDevice;

   /**
    * Local device's role for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Role_t Role;

   /**
    * Transport that is being used for the OTC connection.
    */
   qapi_BLE_OTS_Channel_Connection_Type_t Type;

   /**
    * Channel identifier for the OTC connection.
    */
   uint16_t                               CID;
} qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t;

#define QAPI_BLE_OTS_CHANNEL_BUFFER_EMPTY_INDICATION_DATA_SIZE    (sizeof(qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t
 * structure.
 */

/**
 * Structure that represents the container structure for holding all the
 * OTC event data.
 */
typedef struct qapi_BLE_OTS_Channel_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_OTS_Channel_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint8_t                           Event_Data_Size;
   union
   {
      /**
       * OTS Channel Open Indication event data.
       */
      qapi_BLE_OTS_Channel_Open_Indication_Data_t         *OTS_Channel_Open_Indication_Data;

      /**
       * OTS Channel Open Request event data.
       */
      qapi_BLE_OTS_Channel_Open_Request_Indication_Data_t *OTS_Channel_Open_Request_Indication_Data;

      /**
       * OTS Channel Open Confirmation event data.
       */
      qapi_BLE_OTS_Channel_Open_Confirmation_Data_t       *OTS_Channel_Open_Confirmation_Data;

      /**
       * OTS Channel Close Indication event data.
       */
      qapi_BLE_OTS_Channel_Close_Indication_Data_t        *OTS_Channel_Close_Indication_Data;

      /**
       * OTS Channel Data Indication event data.
       */
      qapi_BLE_OTS_Channel_Data_Indication_Data_t         *OTS_Channel_Data_Indication_Data;

      /**
       * OTS Channel Data Error Indication event data.
       */
      qapi_BLE_OTS_Channel_Data_Error_Indication_t        *OTS_Channel_Data_Error_Indication_Data;

      /**
       * OTS Channel Buffer Empty Indication event data.
       */
      qapi_BLE_OTS_Channel_Buffer_Empty_Indication_Data_t *OTS_Channel_Buffer_Empty_Indication_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_OTS_Channel_Event_Data_t;

#define QAPI_BLE_OTS_CHANNEL_EVENT_DATA_SIZE                      (sizeof(qapi_BLE_OTS_Channel_Event_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Channel_Event_Data_t structure.
 */

   /* OTS and OTS Channel Event Callbacks.                          */

/**
 * @brief
 * This declared type represents the prototype function for an
 * OTS instance event callback. This function will be called
 * whenever an OTS instance event occurs that is associated with the
 * specified Bluetooth stack ID.

 * @details
 * The caller should use the contents of the OTS instance event data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (i.e., this
 * function does not have be reentrant). It should be noted, however,
 * that if the same event callback is installed more than once, the
 * event callbacks will be called serially. Because of this, the
 * processing in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the thread
 * context of a thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another OTS instance event will not be processed while
 * this function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for OTS instance events that can
 * only be satisfied by receiving other Bluetooth Protocol Stack events.
 * A Deadlock will occur because other event callbacks will not be issued
 * while this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack on which the
 *                                   event occurred.
 *
 * @param[in]  OTS_Event_Data        Pointer to a structure that contains
 *                                   information about the event that has
 *                                   occurred.
 *
 * @param[in]  CallbackParameter     User-defined value that was supplied
 *                                   as an input parameter when the OTS
 *                                   instance event callback was
 *                                   installed.
 *
 * @return None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_OTS_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_OTS_Event_Data_t *OTS_Event_Data, uint32_t CallbackParameter);

/**
 * @brief
 * This declared type represents the prototype function for an
 * OTC event callback. This function will
 * be called whenever an OTC event occurs
 * that is associated with the specified Bluetooth stack ID.

 * @details
 * The caller should use the contents of the OTC
 * event data only in the context of this callback. If
 * the caller requires the data for a longer period of time, the
 * callback function must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (i.e., this
 * function does not have be reentrant). It should be noted, however,
 * that if the same event callback is installed more than once, the
 * event callbacks will be called serially. Because of this, the
 * processing in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the thread
 * context of a thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another OTS Object Transfer Channel (OTC) event will
 * not be processed while this function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for OTC
 * events that can only be satisfied by receiving other Bluetooth
 * Protocol Stack events. A Deadlock will occur because other event
 * callbacks will not be issued while this function is currently
 * outstanding.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack on which the
 *                                   event occurred.
 *
 * @param[in]  OTS_Channel_Event_Data   Pointer to a structure that
 *                                      contains information about the
 *                                      event that has occurred.
 *
 * @param[in]  CallbackParameter     User-defined value that was supplied
 *                                   as an input parameter when the OTC
 *                                   event callback was installed.
 *
 * @return None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_OTS_Channel_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_OTS_Channel_Event_Data_t *OTS_Channel_Event_Data, uint32_t CallbackParameter);

   /* The OTS server Initialization constants and structures.           */
   /* * NOTE * These will be used by the                                */
   /*          qapi_BLE_OTS_Initialize_Service() and                    */
   /*          qapi_BLE_OTS_Initialize_Service_Handle_Range() functions */
   /*          to configure the OTS server.                             */

   /* The following defines the OTS characteristic Flags, which is a bit*/
   /* mask that controls what optional OTS characteristics are supported*/
   /* by the OTS server.                                                */
   /* * NOTE * If the OTS server is capable of storing multiple objects */
   /*          (The Multiple_Objects_Supported field of the             */
   /*          qapi_BLE_OTS_Initialize_Data_t structure must be TRUE),  */
   /*          then the                                                 */
   /*          QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_LIST_FILTER flag*/
   /*          may be specified. Otherwise it must be excluded.         */
   /* * NOTE * If the                                                   */
   /*          QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_LIST_FILTER is  */
   /*          specified and valid, then three instances will be        */
   /*          included in the service.                                 */
#define QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_FIRST_CREATED    0x01
/**<
 * The optional OTS Object First Created Characteristic is supported.
 */
#define QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_LAST_MODIFIED    0x02
/**<
 * The optional OTS Object Last Modified Characteristic is supported.
 */
#define QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_LIST_FILTER      0x04
/**<
 * The optional OTS Object List Filter Characteristic is supported.
 */
#define QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_CHANGED          0x08
/**<
 * The optional OTS Object Changed Characteristic is supported.
 */

   /* The following defines the OTS characteristic Optional Property    */
   /* Flags, which is a bit mask that controls what optional OTS        */
   /* Characteristic properties are supported by the OTS server.        */
   /* * NOTE * If the OACP Create Op Code is supported by the OTS server*/
   /*          (The OACP_Create_Procedure_Supported field of the        */
   /*          qapi_BLE_OTS_Initialize_Data_t structure is TRUE), then  */
   /*          the OTS Object Name and OTS First Created (If the OTS    */
   /*          First Created is supported) will be writeable. Otherwise */
   /*          the following flags may be specified to make ths OTS     */
   /*          Object Name and OTS First Created writeable.             */
#define QAPI_BLE_OTS_PROPERTY_FLAGS_OBJECT_NAME_ENABLE_WRITE           0x01
/**<
 * The optional OTS Object Name Characteristic is writable.
 */
#define QAPI_BLE_OTS_PROPERTY_FLAGS_OBJECT_FIRST_CREATED_ENABLE_WRITE  0x02
/**<
 * The optional OTS Object First Created Characteristic is writable.
 */

/**
 * Structure that represents the data that is required to initialize the
 * Object Transfer Service (a parameter for the
 * qapi_BLE_OTS_Initialize_Service() and
 * qapi_BLE_OTS_Initialize_Service_Handle_Range() functions).
 *
 * The OTS_Property_Flags field is a bitmask that controls the optional
 * properties that may be included for supported OTS characteristics.
 * These bitmask values have the form QAPI_BLE_OTS_PROPERTY_FLAGS_XXX
 * can can be found above this structure. This field is dependent on the
 * OACP_Create_Procedure_Supported field and is only valid if the
 * OACP_Create_Procedure_Supported is FALSE.
 *
 * If the OACP_Create_Procedure_Supported is TRUE, the Object Name
 * Characteristic and Object First Created will be writeable and must be
 * supported by the OTS server. The Object First Created is an optional
 * OTS characteristic and must be specified by the
 * OTS_Characteristic_Flags field to be writeable. If FALSE, the
 * OTS_Property_Flags may be used to make the Object Name and Object
 * First-Created Characteristics writeable.
 *
 * If the Multiple_Objects_Supported field is TRUE, the Object ID
 * Characteristic and Object List Control Point Characteristic will be
 * included automatically. Otherwise, they will not be supported by the
 * service.
 *
 * If the Multiple_Objects_Supported field is TRUE, the Object List
 * Filter Characteristic is optional and the
 * QAPI_BLE_OTS_CHARACTERISTIC_FLAGS_OBJECT_LIST_FILTER may be specified
 * for the OTS_Characteristic_Flags field.
 *
 * If the Multiple_Objects_Supported field is FALSE, the Object ID,
 * Object List Control Point, and Object List Filter Characteristics will
 * not be supported by the service.
 *
 * If the Multiple_Objects_Supported is FALSE, the Directory Listing
 * Object will not be supported.
 *
 * If the Real_Time_Clock_Supported field is TRUE, the Object
 * Last-Modified Characteristic will not be writeable. If FALSE, the
 * Object-Last Modified Characteristic will be writeable.
 *
 * The Connection_Mode field will allow the application to specify the
 * default connection mode for the OTC. If the
 * OTS server does not support the OACP Read/Write/Abort Procedures,
 * the Connection_Mode field should be set to
 * QAPI_BLE_OTS_CCM_AUTOMATIC_REJECT_E. Otherwise, the Connection_Mode
 * field may be set to QAPI_BLE_OTS_CCM_AUTOMATIC_ACCEPT_E or
 * QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E. The QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E
 * will allow the OTS server to explicitly authorize connection requests.
 * It is worth noting this may be updated later for future connections
 * via the qapi_BLE_OTS_Channel_Set_Connection_Mode() function.
 *
 * The Default_LE_Channel_Parameters field contains the default OTS
 * Channel parameters to use for the OTS server when an OTS Channel
 * connection request is received from an OTS client over the LE
 * transport.
 *
 * The EventCallback field is the event callback that will receive all
 * dispatched OTS Channel (Object Transfer Channel) events for the
 * user-specified CallbackParameter field.
 */
typedef struct qapi_BLE_OTS_Initialize_Data_s
{
   /**
    * Controls the mandatory/optional OTS characteristics that are
    * included for the OTS instance based on the needs of the OTS server.
    */
   uint8_t                                OTS_Characteristic_Flags;

   /**
    * Controls the optional properties for OTS characteristics that are
    * included for the OTS instance.
    */
   uint8_t                                OTS_Property_Flags;

   /**
    * Controls if the OTS Object Action Control Point (OACP) Create
    * Procedure is supported by the OTS instance.
    */
   boolean_t                              OACP_Create_Procedure_Supported;

   /**
    * Controls if the multiple OTS Objects are supported by the OTS
    * instance.
    */
   boolean_t                              Multiple_Objects_Supported;

   /**
    * Controls if a real time clock is supported by the OTS instance.
    */
   boolean_t                              Real_Time_Clock_Supported;

   /**
    * Sets the default OTC connection mode for the
    * OTS instance.
    */
   qapi_BLE_OTS_Channel_Connection_Mode_t Connection_Mode;

   /**
    * Sets the default LE Channel parameters for OTC
    * connections established over the LE transport.
    */
   qapi_BLE_L2CA_LE_Channel_Parameters_t  Default_LE_Channel_Parameters;

   /**
    * OTC event callback for the OTS
    * instance.
    */
   qapi_BLE_OTS_Channel_Event_Callback_t  EventCallback;

   /**
    * User-defined value that will be passed with OTCr
    * events received for this OTS instance.
    */
   uint32_t                               CallbackParameter;
} qapi_BLE_OTS_Initialize_Data_t;

#define QAPI_BLE_OTS_INITIALIZE_DATA_SIZE                         (sizeof(qapi_BLE_OTS_Initialize_Data_t))
/**<
 * Size of the #qapi_BLE_OTS_Initialize_Data_t structure.
 */

   /* OTS server API.                                                   */

/**
 * @brief
 * Initializes an OTS instance (OTS server) on a specified
 * Bluetooth Protocol Stack.
 *
 * @details
 * Only one OTS instance may be initialized at a time, per the Bluetooth
 * Protocol Stack ID.
 *
 * See the #qapi_BLE_OTS_Initialize_Data_t structure for more
 * information about the InitializeData parameter. If this
 * parameter is not configured correctly, an OTS error will be returned.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceFlags        Flags that are used to
 *                                 register OTS for the specified
 *                                 transport. These flags can be found
 *                                 in qapi_ble_gatt.h and have the form
 *                                 QAPI_BLE_GATT_SERVICE_FLAGS_XXX.
 *
 * @param[in]  InitializeData      Pointer to the data that is used to
 *                                 configure the OTS server.
 *
 * @param[in]  EventCallback       OTS event callback that will
 *                                 receive OTS instance events.
 *
 * @param[in]  CallbackParameter   User-defined value that will be
 *                                 received with the specified
 *                                 EventCallback parameter.
 *
 * @param[out] ServiceID           Unique GATT service ID of the
 *                                 registered OTS instance returned from
 *                                 the qapi_BLE_GATT_Register_Service()
 *                                 function.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the OTS instance ID of the OTS server that was
 *              successfully initialized for the specified Bluetooth
 *              Protocol Stack ID. This is the value that should be used
 *              in all subsequent function calls that require the OTS
 *              Instance ID.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Initialize_Service(uint32_t BluetoothStackID, uint8_t ServiceFlags, qapi_BLE_OTS_Initialize_Data_t *InitializeData, qapi_BLE_OTS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

/**
 * @brief
 * Initializes an OTS instance (OTS server) on a specified
 * Bluetooth Protocol Stack.
 *
 * Unlike qapi_BLE_OTS_Initialize_Service(), this function allows the
 * application to select a attribute handle range in GATT to store the
 * service.
 *
 * @details
 * Only one OTS instance may be initialized at a time, per the Bluetooth
 * Protocol Stack ID.
 *
 * See the #qapi_BLE_OTS_Initialize_Data_t structure for more
 * information about the InitializeData parameter. If this
 * parameter is not configured correctly, an OTS error will be returned.
 *
 * If the application wants GATT to select the attribute handle range for
 * the service, all fields of the ServiceHandleRange parameter must
 * be initialized to zero. The qapi_BLE_OTS_Query_Number_Attributes()
 * function may be used after initializing an OTS instance to determine
 * the attribute handle range for the OTS instance.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ServiceFlags        Flags that are used to
 *                                 register OTS for the specified
 *                                 transport. These flags can be found
 *                                 in qapi_ble_gatt.h and have the form
 *                                 QAPI_BLE_GATT_SERVICE_FLAGS_XXX.
 *
 * @param[in]  InitializeData      Pointer to the data that is used to
 *                                 configure the OTS server.
 *
 * @param[in]  EventCallback       OTS event callback that will
 *                                 receive OTS instance events.
 *
 * @param[in]  CallbackParameter   User-defined value that will be
 *                                 received with the specified
 *                                 EventCallback parameter.
 *
 * @param[out] ServiceID           Unique GATT service ID of the
 *                                 registered OTS instance returned from
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
 * @return      Positive, nonzero if successful. The return value will
 *              be the OTS Instance ID of the OTS server that was
 *              successfully initialized for the specified Bluetooth
 *              Protocol Stack ID. This is the value that should be used
 *              in all subsequent function calls that require the OTS
 *              instance ID.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, uint8_t ServiceFlags, qapi_BLE_OTS_Initialize_Data_t *InitializeData, qapi_BLE_OTS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with an OTS Instance (OTS server).
 *
 * @details
 * After this function is called, no other OTS
 * function can be called until after a successful call to either of the
 * qapi_BLE_OTS_Initialize_XXX() functions.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that will
 *                                 be cleaned up.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queries the number of attributes
 * that are contained in an OTS instance that is registered with a call
 * to either of the qapi_BLE_OTS_Initialize_XXX() functions.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance.
 *
 * @return   Positive, nonzero, number of attributes for the
 *           registered OTS instance.
 *
 * @return   Zero on failure.
 */
QAPI_BLE_DECLARATION unsigned int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Query_Number_Attributes(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Responds to a read request
 * received from an OTS client for an OTS characteristic's CCCD.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * If the request is rejected, the Configuration parameter will be
 * ignored.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Type                Identifies the CCCD.
 *
 * @param[in]  Configuration       CCCD that
 *                                 will be sent if the request is
 *                                 accepted.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Read_CCCD_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_CCCD_Characteristic_Type_t Type, uint16_t Configuration);

/**
 * @brief
 * Responds to a write request,
 * received from an OTS client for an OTS characteristic's CCCD.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Type                Identifies the CCCD.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Write_CCCD_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_CCCD_Characteristic_Type_t Type);

/**
 * @brief
 * Responds to a read request
 * received from an OTS client for the OTS Feature Characteristic.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * If the request is rejected, the OTSFeature parameter may be excluded
 * (NULL).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  OTSFeature          Pointer to the OTS Feature that
 *                                 will be sent if the request is
 *                                 accepted.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Read_OTS_Feature_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_Feature_Data_t *OTSFeature);

/**
 * @brief
 * Responds to a read request
 * received from an OTS client for an OTS Object's Metadata
 * Characteristic.
 *
 * @details
 * The Offset parameter is received with
 * the QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_METADATA_REQUEST_E event. See
 * the #qapi_BLE_OTS_Read_Object_Metadata_Request_Data_t structure for
 * more information about this parameter.
 *
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * If the request is rejected, the Metadata parameter may be excluded
 * (NULL) and the Offset parameter will be ignored.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates wheter the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Type                Identifies the OTS Object Metadata
 *                                 Characteristic.
 *
 * @param[in]  Metadata            Pointer to the OTS Object Metadata
 *                                 that will be sent if the request is
 *                                 accepted.
 *
 * @param[in]  Offset              Specifies the starting offset if
 *                                 OTS Object Name Metadata
 *                                 Characteristic is read.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Read_Object_Metadata_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_Object_Metadata_Type_t Type, qapi_BLE_OTS_Object_Metadata_Data_t *Metadata, uint8_t Offset);

/**
 * @brief
 * Responds to a write request
 * received from an OTS client for an OTS Object's Metadata
 * Characteristic.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Type                Identifies the OTS Object Metadata
 *                                 Characteristic.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Write_Object_Metadata_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_Object_Metadata_Type_t Type);

/**
 * @brief
 * Responds to a write request
 * received from an OTS client for an OTS OACP Characteristic.
 *
 * This function does not indicate the result of the OACP Procedure. If
 * the request is accepted, it indicates that the OACP Procedure has
 * started. An indication must be sent by the OTS server once the OACP
 * Procedure has completed. The
 * qapi_BLE_OTS_Indicate_OACP_Response() function must be used to
 * indicate the result of the OACP Procedure.
 *
 * @details
 * This function is primarily provided to allow a way to reject the OACP
 * write request when the OACP CCCD has not been configured for indications, the OTS
 * client does not have proper Authentication, Authorization, or
 * Encryption to write to the OACP, or an OACP request is already in
 * progress. All other reasons should return
 * QAPI_BLE_OTS_ERROR_CODE_SUCCESS for the ErrorCode and then call the
 * qapi_BLE_OTS_Indicate_OACP_Response() to indicate the response once
 * the OACP procedure has completed.
 *
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Write_OACP_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Indicates the OACP procedure result to an OTS client.
 *
 * @details
 * This function sends an indication, which provides a guarantee that the
 * OTS client will receive the value, since the OTS client must confirm
 * that it has been received.
 *
 * @note1hang
 * It is the application's responsibilty to make sure that the OACP
 * CCCD has been
 * previously configured for indications. An OTS client must have written
 * the OTS OACP Characteristic's CCCD to enable indications.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  ConnectionID        GATT connection ID for the
 *                                 connection with the OTS client.
 *
 * @param[in]  ResponseData        Pointer to the OACP response data
 *                                 that will be sent in the indication.
 *
 * @return      Positive nonzero if successful (represents the
 *              GATT Transaction ID for the indication).
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Indicate_OACP_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_OTS_OACP_Response_Data_t *ResponseData);

/**
 * @brief
 * Responds to a write request
 * received from an OTS client for an OTS Object List Control Point
 * (OLCP) Characteristic.
 *
 * This function does not indicate the result of the OLCP Procedure. If
 * the request is accepted, it indicates that the OLCP Procedure has
 * started. An indication must be sent by the OTS server once the OLCP
 * Procedure has completed. The
 * qapi_BLE_OTS_Indicate_OLCP_Response() function must be used to
 * indicate the result of the OLCP Procedure.
 *
 * @details
 * This function is primarily provided to allow a way to reject the OLCP
 * write request when the OLCP CCCD
 * has not been configured for indications, the OTS
 * client does not have proper Authentication, Authorization, or
 * Encryption to write to the OLCP, or an OLCP request is already in
 * progress. All other reasons should return
 * QAPI_BLE_OTS_ERROR_CODE_SUCCESS for the ErrorCode and then call the
 * qapi_BLE_OTS_Indicate_OLCP_Response() to indicate the response once
 * the OLCP procedure has completed.
 *
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Write_OLCP_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Indicate the OLCP procedure result to an OTS client.
 *
 * @details
 * This function sends an indication, which provides a guarantee that the
 * OTS client will receive the value, since the OTS client must confirm
 * that it has been received.
 *
 * @note1hang
 * It is the application's responsibilty to make sure that the OLCP
 * CCCD has been
 * previously configured for indications. An OTS client must have written
 * the OTS OLCP Characteristic's CCCD to enable indications.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  ConnectionID        GATT connection ID for the
 *                                 connection with the OTS client.
 *
 * @param[in]  ResponseData        Pointer to the OLCP response data
 *                                 that will be sent in the indication.
 *
 * @return      Positive nonzero if successful (represents the
 *              GATT Transaction ID for the indication).
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Indicate_OLCP_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_OTS_OLCP_Response_Data_t *ResponseData);

/**
 * @brief
 * Responds to a read request
 * received from an OTS client for an OTS Object List Filter
 * Characteristic instance.
 *
 * @details
 * The Offset parameter is received with
 * the QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_LIST_FILTER_REQUEST_E event. See
 * the #qapi_BLE_OTS_Read_Object_List_Filter_Request_Data_t structure for
 * more information about this parameter.
 *
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * If the request is rejected, the ListFilterData parameter may be excluded
 * (NULL) and the Offset parameter will be ignored.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Instance            Identifies the OTS Object List Filter
 *                                 Characteristic instance.
 *
 * @param[in]  ListFilterData      Pointer to the OTS Object List
 *                                 Filter data that will be sent if the
 *                                 request is accepted.
 *
 * @param[in]  Offset              Specifies the starting offset if
 *                                 OTS Object Name Metadata
 *                                 Characteristic is read.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Read_Object_List_Filter_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_Object_List_Filter_Instance_t Instance, qapi_BLE_OTS_Object_List_Filter_Data_t *ListFilterData, uint8_t Offset);

/**
 * @brief
 * Responds to a read request
 * received from an OTS client for an OTS Object List Filter
 * Characteristic instance.
 *
 * @details
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @param[in]  Instance            Identifies the OTS Object List Filter
 *                                 Characteristic instance.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Write_Object_List_Filter_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode, qapi_BLE_OTS_Object_List_Filter_Instance_t Instance);

/**
 * @brief
 * Responds to a prepared write
 * request received from an OTS client for an OTS characteristic.
 *
 * @details
 * This function is primarily provided to reject a GATT Prepare Write
 * request for optional security reasons, such as the OTS client has
 * insufficient authentication, authorization, or encryption. We will
 * not pass the prepared data up to the application until the the GATT
 * Execute Write request has been received by the OTS server, and the
 * prepared writes are not cancelled. If the prepared data is written,
 * the appropriate OTS event will be dispatched to the application.
 * Otherwise the prepared data will be cleared.
 *
 * The ErrorCode parameter must be a valid value from qapi_ble_otstypes.h
 * (OTS_ERROR_CODE_XXX) or qapi_ble_atttypes.h
 * (QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_XXX).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  TransactionID       GATT transaction ID.
 *
 * @param[in]  ErrorCode           Indicates whether the request was
 *                                 accepted or rejected.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Prepare_Write_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint8_t ErrorCode);

/**
 * @brief
 * Indicates that an OTS Object has
 * changed to an OTS client.
 *
 * @details
 * This function sends an indication, which provides a guarantee that the
 * OTS client will receive the value, since the OTS client must confirm
 * that it has been received.
 *
 * @note1hang
 * It is the application's responsibilty to make sure that the OTS Object
 * Changed's CCCD has
 * been previously configured for indications. An OTS client must have
 * written the OTS Object Changed Characteristic's CCCD to enable
 * indications.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Identifies the OTS instance that
 *                                 received the request.
 *
 * @param[in]  ConnectionID        GATT connection ID for the
 *                                 connection with the OTS client.
 *
 * @param[in]  ObjectChangedData   Pointer to the Object Changed data
 *                                 that will be sent in the indication.
 *
 * @return      Positive nonzero if successful (represents the
 *              GATT Transaction ID for the indication).
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_gatt.h
 *              (QAPI_BLE_GATT_ERROR_XXX) or qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Indicate_Object_Changed(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, qapi_BLE_OTS_Object_Changed_Data_t *ObjectChangedData);

/**
 * @brief
 * Calculates an ISO/IEC 3309 compliant
 * 32-bit CRC for a specified number of octets.
 *
 * @details
 * This function may be used to calculate the checksum for the OACP
 * Calculate Checksum procedure.
 *
 * @param[in]  BufferLength        Length of data that will be
 *                                 used for the CRC calculation.
 *
 * @param[in]  Buffer              Pointer to the data that will be
 *                                 used for the CRC calculation.
 *
 * @param[out]  Checksum           Pointer that will hold the
 *                                 calculated Checksum if this function
 *                                 is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Calculate_CRC_32(uint32_t BufferLength, uint8_t *Buffer, uint32_t *Checksum);

   /* OTS client API.                                                   */

/**
 * @brief
 * Parses a value received in a read
 * response from a remote OTS server, interpreting it as the OTS Feature
 * Characteristic.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[out]  OTSFeature   Pointer that will hold the OTS Feature if
 *                           this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_OTS_Feature(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_Feature_Data_t *OTSFeature);

/**
 * @brief
 * Formats an OTS Object
 * Metadata Characteristic into a user-specified buffer for a GATT Write
 * request that will be sent to the OTS server.
 *
 * This function may also be used to determine the size of the buffer to
 * hold the formatted data (see details).
 *
 * @details
 * This function will not format the OTS Object Name. The OTS Object
 * Name should already be formatted.
 *
 * If the OTS Object Metadata type is omtObjectType, this function
 * expects that the 16 or 128 bit UUID has already been formatted in
 * Little-Endian.
 *
 * If the BufferLength parameter is 0, the Buffer parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the size of the buffer needed to hold the
 * formatted data. The OTS client may use this size to allocate a buffer
 * necessary to hold the formatted data.
 *
 * @param[in]  Type           Identifies the OTS Object Metadata
 *                            Characteristic.
 *
 * @param[in]  Metadata       Pointer to the OTS Object Metadata
 *                            Chararacteristic.
 *
 * @param[in]  BufferLength   Length of the user specified buffer.
 *
 * @param[out]  Buffer        The user specified buffer.
 *
 * @return      If this function is used to format the user-specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the size of the
 *              user specified buffer to hold the formatted data, a
 *              positive nonzero value will be returned for success,
 *              which represents the minimum length required for the user
 *              specified buffer to hold the formatted data.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Format_Object_Metadata(qapi_BLE_OTS_Object_Metadata_Type_t Type, qapi_BLE_OTS_Object_Metadata_Data_t *Metadata, uint16_t BufferLength, uint8_t *Buffer);

/**
 * @brief
 * Parses a value received in a read
 * response from a remote OTS server, interpreting it as an OTS Object
 * Metadata Characteristic.
 *
 * @details
 * The Type parameter identifies the OTS Object Metadata Characteristic
 * that will be decoded. The OTS client should store the OTS Object
 * Metadata type when the request was dispatched so that the response can
 * be decoded. Since the OTS Object Metadata type was used to format the
 * buffer for the request using the qapi_BLE_OTS_Format_Object_Metadata()
 * function, it should be known to the OTS client.
 *
 * If the OTS Object Metadata type is QAPI_BLE_OTS_OMT_OBJECT_TYPE_E, this
 * function will return the 16- or 128-bit UUID in Little-Endian.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[in]  Type          Identifies the OTS Object Metadata
 *                           Characteristic that is contained by the
 *                           Value parameter.
 *
 * @param[out]  Metadata     Pointer that will hold the OTS Object
 *                           Metadata if this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_Object_Metadata(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_Object_Metadata_Type_t Type, qapi_BLE_OTS_Object_Metadata_Data_t *Metadata);

/**
 * @brief
 * Formats OACP Characteristic request data into a user-specified
 * buffer for a GATT Write request that will be sent to the OTS server.
 *
 * This function may also be used to determine the size of the buffer to
 * hold the formatted data (see details).
 *
 * @details
 * If the BufferLength parameter is 0, the Buffer parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the size of the buffer needed to hold the
 * formatted data. The OTS client may use this size to allocate a buffer
 * necessary to hold the formatted data.
 *
 * @param[in]  RequestData    Pointer to the OACP request data.
 *
 * @param[in]  BufferLength   Length of the user specified buffer.
 *
 * @param[out]  Buffer        User-specified buffer.
 *
 * @return      If this function is used to format the user specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the size of the
 *              user specified buffer to hold the formatted data, a
 *              positive nonzero value will be returned for success,
 *              which represents the minimum length required for the user
 *              specified buffer to hold the formatted data.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Format_OACP_Request(qapi_BLE_OTS_OACP_Request_Data_t *RequestData, uint16_t BufferLength, uint8_t *Buffer);

/**
 * @brief
 * Parses a value received in
 * an indication from a remote OTS server interpreting it as the
 * OACP procedure result.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[out]  ResponseData   Pointer that will hold the OTS Object
 *                             Action Control Point (OACP) response
 *                             data if this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_OACP_Response(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_OACP_Response_Data_t *ResponseData);

/**
 * @brief
 * Formats OTS OLCP
 * characteristic request data into a user-specified
 * buffer for a GATT Write request that will be sent to the OTS server.
 *
 * This function may also be used to determine the size of the buffer to
 * hold the formatted data.
 *
 * @details
 * If the BufferLength parameter is 0, the Buffer parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the size of the buffer needed to hold the
 * formatted data. The OTS client may use this size to allocate a buffer
 * necessary to hold the formatted data.
 *
 * @param[in]  RequestData   Pointer to the OLCP request data.
 *
 * @param[in]  BufferLength  Length of the user specified buffer.
 *
 * @param[out]  Buffer       User-specified buffer.
 *
 * @return      If this function is used to format the user-specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the size of the
 *              user-specified buffer to hold the formatted data, a
 *              positive nonzero value will be returned for success,
 *              which represents the minimum length required for the user
 *              specified buffer to hold the formatted data.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Format_OLCP_Request(qapi_BLE_OTS_OLCP_Request_Data_t *RequestData, uint16_t BufferLength, uint8_t *Buffer);

/**
 * @brief
 * Parses a value received in
 * an indication from a remote OTS server interpreting it as the
 * OLCP procedure result.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[out]  ResponseData   Pointer that will hold the OTS
 *                             OLCP response
 *                             data if this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_OLCP_Response(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_OLCP_Response_Data_t *ResponseData);

/**
 * @brief
 * Formats the OTS Object
 * List Filter Characteristic into a user-specified buffer for a GATT
 * Write request that will be sent to the OTS server.
 *
 * This function may also be used to determine the size of the buffer to
 * hold the formatted data (see details).
 *
 * @details
 * If the BufferLength parameter is 0, the Buffer parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the size of the buffer needed to hold the
 * formatted data. The OTS client may use this size to allocate a buffer
 * necessary to hold the formatted data.
 *
 * @param[in]  ListFilterData   Pointer to the OTS Object List Filter
 *                              data.
 *
 * @param[in]  BufferLength     Length of the user-specified buffer.
 *
 * @param[out]  Buffer          User-specified buffer.
 *
 * @return      If this function is used to format the user specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the size of the
 *              user specified buffer to hold the formatted data, a
 *              positive nonzero value will be returned for success,
 *              which represents the minimum length required for the user
 *              specified buffer to hold the formatted data.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Format_Object_List_Filter_Data(qapi_BLE_OTS_Object_List_Filter_Data_t *ListFilterData, uint16_t BufferLength, uint8_t *Buffer);

/**
 * @brief
 * Parses a value received in a read
 * response from a remote OTS server, interpreting it as an OTS Object
 * List Filter Characteristic instance.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[out]  ListFilterData   Pointer that will hold the OTS Object
 *                               List Filter Characteristic instance data
 *                               if this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_Object_List_Filter_Data(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_Object_List_Filter_Data_t *ListFilterData);

/**
 * @brief
 * Parses a value received in
 * an indication from a remote OTS server interpreting it as the OTS
 * Object Changed Characteristic.
 *
 * @param[in]  ValueLength   Length of the value received from the
 *                           OTS server.
 *
 * @param[in]  Value         Value received from the
 *                           OTS server.
 *
 * @param[out]  ObjectChangedData   Pointer that will hold the OTS
 *                                  Object Changed data if this function
 *                                  is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_Object_Changed_Data(uint32_t ValueLength, uint8_t *Value, qapi_BLE_OTS_Object_Changed_Data_t *ObjectChangedData);

   /* Object Transfer Channel (OTC) Server API.                         */

/**
 * @brief
 * Responds to a request from
 * an OTS client to open the OTC.
 *
 * @details
 * This function is used to respond to the
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_REQUEST_INDICATION_E event. In order to
 * receive this event, the OTS server must have its OTC Connection Mode
 * set to QAPI_BLE_OTS_CCM_MANUAL_ACCEPT_E. Otherwise, OTC connections
 * will automatically be accepted/rejected by the OTS server and this
 * event will not be received.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID         Identifies the OTS instance.
 *
 * @param[in]  CID                Identifies the OTC.
 *
 * @param[in]  AcceptConnection   Controls whether the connection request is
 *                                accepted or rejected.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Open_Connection_Request_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint16_t CID, boolean_t AcceptConnection);

/**
 * @brief
 * Queries the OTC Connection Mode for the OTS server.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID         Identifies the OTS instance.
 *
 * @param[out]  ConnectionMode    Holds the OTS OTC
 *                                connection mode if this function
 *                                is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Get_Connection_Mode(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_OTS_Channel_Connection_Mode_t *ConnectionMode);

/**
 * @brief
 * Queries the OTC Connection Mode for the OTS server.
 *
 * @details
 * The new Connection Mode will only apply to future connection requests
 * received by the OTS server.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID         Identifies the OTS instance.
 *
 * @param[in]  ConnectionMode     OTS OTC connection mode.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Set_Connection_Mode(uint32_t BluetoothStackID, uint32_t InstanceID, qapi_BLE_OTS_Channel_Connection_Mode_t ConnectionMode);

/**
 * @brief
 * Formats the OTS Directory
 * Listing Object's contents into a user-specified buffer so that the
 * OTS server may send the OTS Directory Listing Object's contents over
 * the OTC to an OTS client.
 *
 * This function must be used to set the OTS Directory Listing Object's
 * Size Metadata Characteristic when an OTS client has sent a request
 * (QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_METADATA_REQUEST_E) to read the
 * OTS Direct Listing Object's Size Metadata Characteristic.
 *
 * @details
 * The OTS Directory Listing Object's contents are made up of OTS Object
 * Records (handled internally).
 *
 * If this function is used to calculate the OTS Directory Listing
 * Object's Size Metadata Chararacteristic, the positive nonzero
 * value returned by this function will represent the OTS Directory
 * Listing Object's Size Metadata Characteristic (Current size =
 * Allocated Size = returned value). This may vary each time this
 * function is called.
 *
 * If the BufferLength parameter is 0, the Buffer parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the size of the buffer needed to hold the
 * formatted data. The OTS server may use this size to allocate a buffer
 * necessary to hold the formatted data. the formatted data.
 *
 * @note1hang
 * This function must be called to calculate the size of the OTS
 * Directory Listing Object's Size Metadata Characteristic when the OTS
 * client has sent a request to read the OTS Directory Listing Object's
 * Size Metadata Characteristic
 * (QAPI_BLE_OTS_ET_SERVER_READ_OBJECT_METADATA_REQUEST_E). This is
 * because the OTS Direct Listing Object's contents may vary due to
 * changes to OTS Objects by OTS clients. The OTS server should update
 * the OTS Object Size Metadata Characteristic for the OTS Directory
 * Listing Object before responding with the
 * qapi_BLE_OTS_Read_Object_Metadata_Request_Response() function.
 *
 * Since the OTS Directory Listing Object's Size Metadata
 * Characteristic may change after the OTS client has read the OTS
 * Directory Listing Object's Size Metadata Characteristic and when an
 * OACP Read Procedure request is received to request the OTS Directory
 * Listing Object's contents be sent over the OTC, the OTS server must
 * call this function to recalculate the OTS Directory Listing Object's
 * Size Metadata Characteristic and compare it with the current value. If
 * the OTS Directory Listing Object Size Metadata Characteristic does not
 * match the current value, the OACP Read Procedure should be
 * indicated with the qapi_BLE_OTS_Indicate_OACP_Response() function with
 * the result code set to QAPI_BLE_OTS_OARC_OPERATION_FAILED_E. This will
 * prevent a case where the OTS client has allocated a buffer that is too
 * small to hold the OTS Directory Listing Object's contents. If the
 * values are the same, the OTS Object's may be formatted into the
 * buffer. The OTS server may start the transfer once the
 * qapi_BLE_OTS_Indicate_OACP_Response() function been used to indicate
 * success for the OACP Read Procedure to the OTS client.
 *
 * @param[in]  NumberOfObjects   Number of OTS Objects that makeup
 *                               the OTS Directory Listing Object's
 *                               contents.
 *
 * @param[in]  ObjectData        Pointer to an array of OTS Objects
 *                               that makeup the OTS Directory Listing
 *                               Object's contents.
 *
 * @param[in]  BufferLength      Length of the user-specified buffer.
 *
 * @param[out]  Buffer           User-specified buffer.
 *
 * @return      If this function is used to format the user specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the size of the
 *              user specified buffer to hold the formatted data, a
 *              positive nonzero value will be returned for success,
 *              which represents the minimum length required for the user
 *              specified buffer to hold the formatted data.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Format_Directory_Listing_Object_Contents(uint32_t NumberOfObjects, qapi_BLE_OTS_Object_Data_t *ObjectData, uint32_t BufferLength, uint8_t *Buffer);

   /* Object Transfer Channel (OTC) Client API.                         */

/**
 * @brief
 * Requess the creation of
 * an OTC connection to an OTS server.
 *
 * @details
 * The ChannelParameters is required if the GATT connection type (Type)
 * is QAPI_BLE_OTS_OCT_LE_E, Otherwise, it may be excluded (NULL).
 *
 * Once a connection is established, it can only be closed via a call to
 * the qapi_BLE_OTS_Channel_Close_Connection() function. Under normal
 * circumstances (sn error has not occured on the OTS server), the OTS
 * client should close the OTC once a procedure has completed.
 *
 * A positive return value does not mean that the OTC connection has been
 * established, only that the OTC connection request has been
 * successfully submitted.
 *
 * The GATT connection to the OTS server must already exist before
 * calling this function.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Type               Transport used for the GATT
 *                                connection with the OTS server.
 *
 * @param[in]  BD_ADDR            Bluetooth address of the OTS
 *                                server.
 *
 * @param[in]  EventCallback       OTS OTC
 *                                 event callback that will receive
 *                                 events.
 *
 * @param[in]  CallbackParameter   User-defined value that will be
 *                                 received with the specified
 *                                 EventCallback parameter.
 *
 * @param[in]  ChannelParameters   Channel parameters to use for an
 *                                 OTS OTC
 *                                 connection over the LE transport.
 *
 * @return      Positive, nonzero, if successful, which represents the
 *              channel identifier (CID).
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Connect_Request(uint32_t BluetoothStackID, qapi_BLE_GATT_Connection_Type_t Type, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_OTS_Channel_Event_Callback_t EventCallback, uint32_t CallbackParameter, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters);

/**
 * @brief
 * Parses a buffer received
 * from the OTS server over the OTC,
 * interpreting it as the OTS Directory Listing Object's contents.
 *
 * This function must be used to determine the number of OTS oObjects
 * that are contained in the user-specified buffer before each OTS
 * object's data may be decoded from the OTS Directory Listing
 * Object's contents contained in the user-specified buffer.
 *
 * @details
 * The OTS Directory Listing Object's contents are made up of OTS Object
 * Records (handled internally).
 *
 * If the NumberOfObjects parameter is 0, the ObjectData parameter may be
 * excluded (NULL), and this function will return a positive nonzero
 * value, which represents the number of OTS objects contained in the
 * buffer. The OTS client may use this returned value to allocate enough
 * OTS objects to hold each OTS object's data that is decoded from the
 * OTS Directory Listing Object's contents.
 *
 * @note1hang
 * The OTS client must read the OTS Directory
 * List Object's Size Metadata Characteristic before the OTS client may
 * use the OACP Read Procedure to read the OTS Directory Listing Object's
 * contents over the OTC. Since the OTS Directory Listing Object's
 * contents may be fragmented over multiple
 * QAPI_BLE_OTS_CHANNEL_ET_DATA_INDICATION_E events, the OTS client must
 * allocate a buffer to hold the entire OTS Directory Listing Object's
 * contents received over the OTC.
 *
 * The OTS Directory Listing Object's contents may vary due to changes to
 * the OTS objects by OTS clients. Therefore, the user-specified buffer
 * to receive the OTS Directory Listing Object's contents will also vary
 * each time the OTS Directory Listing Object's Size Metadata
 * Characteristic is read.
 *
 * @param[in]  BufferLength   Length of the buffer that holds all the
 *                            data received over the OTC.
 *
 * @param[in]  Buffer         Buffer that holds all the data received
 *                            over the OTC.
 *
 * @param[in]  NumberOfObjects   Number of OTS objects that will
 *                               be decoded from the buffer.
 *
 * @param[out]  ObjectData       A pointer to the OTS Objects that will
 *                               hold each OTS Object's information
 *                               associated with the OTS Directory
 *                               Listing Object's contents if this
 *                               function is successful.
 *
 * @return      If this function is used to decode the user-specified
 *              buffer, zero will be returned for success.
 *
 * @return      If this function is used to determine the number of OTS
 *              objects contained in the user-specified buffer, a
 *              positive nonzero value will be returned for success,
 *              which represents the number of OTS Objects contained in
 *              the buffer.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX).
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Decode_Directory_Listing_Object_Contents(uint32_t BufferLength, uint8_t *Buffer, uint32_t NumberOfObjects, qapi_BLE_OTS_Object_Data_t *ObjectData);

   /* Object Transfer Channel (OTC) Common API.                         */

/**
 * @brief
 * Requests the termination
 * of the OTC connection.
 *
 * @details
 * Under normal circumstances (an error has not occured on the OTS
 * server), the OTS client should close the OTC.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CID                Identifies the OTS OTC.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Close_Connection(uint32_t BluetoothStackID, uint16_t CID);

/**
 * @brief
 * Sends data over the
 * established OTC connection to the specified
 * OTC remote device. This function provides additional functionality to
 * control the amount of buffer usage for the OTC connection.
 *
 * @details
 * If the total amount of data to be sent exceeds the Service Data Unit
 * (SDU) size, multiple SDU packets must be sent. Multiple SDUs may
 * be queued at once using the QueueingParameters. Otherwise, only one SDU
 * may be queued at a time.
 *
 * The SDU size must be used to index the rest of the data that has not
 * been sent for the next call to qapi_BLE_OTS_Channel_Send_Data().
 *
 * If this function returns the Error Code
 * QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE, this is a signal to
 * the caller that the requested data could not be sent because the
 * requested data could not be queued for the OTC connection. The caller
 * must then wait for the
 * QAPI_BLE_OTS_CHANNEL_ET_BUFFER_EMPTY_INDICATION_E event before more
 * SDUs may be queued.
 *
 * @note1hang
 * The caller will need the SDU size that was
 * received by the QAPI_BLE_OTS_CHANNEL_ET_OPEN_INDICATION_E,
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_REQUEST_INDICATION_E, and
 * QAPI_BLE_OTS_CHANNEL_ET_OPEN_CONFIRMATION_E.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CID                Identifies the OTS OTC.
 *
 * @param[in]  QueueingParameters   Allows multiple SDUs to be queued by
 *                                  the local device. This parameter is
 *                                  optional and may be excluded (NULL).
 *
 * @param[in]  Data_Length          Length of data that will be sent
 *                                  over the OTS OTC.
 *
 * @param[in]  Data                 Data that will be sent
 *                                  over the OTS OTC.
 *
 * @return      If this function is used with no QueueingParameters
 *              (NULL), zero will be returned for success.
 *
 * @return      If this function is used with QueueingParameters
 *              (non-NULL), a positive, nonzero, value will be
 *              returned, which represents the number of SDUs currently
 *              queued for the OTC connection at the time this function
 *              returns.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Send_Data(uint32_t BluetoothStackID, uint16_t CID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data);

/**
 * @brief
 * Grants the
 * specified amount of credits for the OTC
 * connection over the LE transport.
 *
 * @details
 * This function may only be used for an OTC connection that has been
 * established over the LE transport and is using the Manual LE Based
 * Credit Mode.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CID                Identifies the OTS OTC.
 *
 * @param[in]  Credits            Number of credits to grant to the
 *                                remote device.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative. OTS error codes can be
 *              found in qapi_ble_ots.h (QAPI_BLE_OTS_ERROR_XXX). Other
 *              error codes from qapi_ble_errors.h
 *              (QAPI_BLE_BTPS_ERROR_XXX) may also be returned if an
 *              internal error has occured.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_OTS_Channel_Grant_Credits(uint32_t BluetoothStackID, uint16_t CID, uint16_t Credits);

/**
 *  @}
 */

#endif

