/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_hci.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack HCI API Type
 * Definitions, Constants, and Prototypes.
 *
 * @details
 * The Host Controller Interface (HCI) layer API of the Bluetooth
 * Protocol Stack provides software  access to the HCI command
 * interface to the baseband controller and link manager.  This
 * allows access to hardware status and control registers.  This
 * API provides a uniform method of accessing the Bluetooth baseband
 * capabilities.
 */

#ifndef __QAPI_BLE_HCI_H__
#define __QAPI_BLE_HCI_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_hcitypes.h"  /* Bluetooth HCI Type Definitions/Constants.*/

/** @addtogroup qapi_ble_core_hci
@{ */

/**
*   Enumerated type that is used with the
*   qapi_BLE_HCI_Version_Supported() function. These values represent
*   the HCI Layer Specification that the HCI API Layer supports.
*   Notice that the version definition for later versions of the
*   Bluetooth HCI Specification are defined as values having a larger
*   numerical value. This allows a simple comparison logic (greater
*   than/less than/equal to/etc. logic) to be performed.
*/

typedef enum
{
   QAPI_BLE_HV_SPECIFICATION_1_0B_E,
   /**< HCI Specification 1.0B. */

   QAPI_BLE_HV_SPECIFICATION_1_1_E,
   /**< HCI Specification 1.1. */

   QAPI_BLE_HV_SPECIFICATION_1_2_E,
   /**< HCI Specification 1.2. */

   QAPI_BLE_HV_SPECIFICATION_2_0_E,
   /**< HCI Specification 2.0. */

   QAPI_BLE_HV_SPECIFICATION_2_1_E,
   /**< HCI Specification 2.1 + EDR. */

   QAPI_BLE_HV_SPECIFICATION_3_0_E,
   /**< HCI Specification 3.0 + HS. */

   QAPI_BLE_HV_SPECIFICATION_4_0_E,
   /**< HCI Specification 4.0. */

   QAPI_BLE_HV_SPECIFICATION_4_1_E,
   /**< HCI Specification 4.1. */

   QAPI_BLE_HV_SPECIFICATION_4_2_E,
   /**< HCI Specification 4.2. */

   QAPI_BLE_HV_SPECIFICATION_5_0_E,
   /**< HCI Specification 5.0. */

   QAPI_BLE_HV_SPECIFICATION_5_1_E,
   /**< HCI Specification 5.1. */

   QAPI_BLE_HV_SPECIFICATION_5_2_E,
   /**< HCI Specification 5.2. */

   QAPI_BLE_HV_SPECIFICATION_5_3_E
   /**< HCI Specification 5.3. */
} qapi_BLE_HCI_Version_t;

/** @cond */
/**
 * Structure that is used with the
 * qapi_BLE_HCI_Host_Number_Of_Completed_Packets() function, and
 * represents a single Connection Handle/Host Number of Completed Packets
 * Pair that is required by this function.
 */
typedef struct qapi_BLE_HCI_Host_Completed_Packets_Info_s
{
   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Number of completed host packets.
    */
   uint16_t Host_Num_Of_Completed_Packets;
} qapi_BLE_HCI_Host_Completed_Packets_Info_t;
/** @endcond */

/** @cond */
/** Size of the #qapi_BLE_HCI_Host_Completed_Packets_Info_t structure. */
#define QAPI_BLE_HCI_HOST_COMPLETED_PACKETS_INFO_SIZE            (sizeof(qapi_BLE_HCI_Host_Completed_Packets_Info_t))
/** @endcond */

/**
 * Structure that is used to hold information on a specified MWS
 * Transport.
 *
 * The To_MWS_Baud_Rate and From_MWS_Baud_Rate members are arrays of
 * NumberOfBaudRates entries.
 */
typedef struct qapi_BLE_HCI_MWS_Transport_Info_s
{
   /**
    * Transport layer.
    */
   uint8_t   TransportLayer;

   /**
    * Number of baud rates.
    */
   uint8_t   NumberOfBaudRates;

   /**
    * Pointer to the MWS Baud Rate (to).
    */
   uint32_t *To_MWS_Baud_Rate;

   /**
    * Pointer to the MWS Baud Rate (from).
    */
   uint32_t *From_MWS_Baud_Rate;
} qapi_BLE_HCI_MWS_Transport_Info_t;

/** Size of the #qapi_BLE_HCI_MWS_Transport_Info_t structure. */
#define QAPI_BLE_HCI_MWS_TRANSPORT_INFO_SIZE                         (sizeof(qapi_BLE_HCI_MWS_Transport_Info_t))

/** @cond */
/**
 * Structure that is used with the the
 * qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration() command for the
 * HCI return result.
 *
 * The TransportLayerInfo parameter is an array of NumberOfTransports
 * entries.
 */
typedef struct qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_s
{
   /**
    * Number of transports.
    */
   uint8_t                            NumberOfTransports;

   /**
    * Pointer to the transport information.
    */
   qapi_BLE_HCI_MWS_Transport_Info_t *TransportLayerInfo;
} qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t;
/** @endcond */

/** @cond */
/** Size of the #qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t
    structure. */
#define QAPI_BLE_HCI_MWS_TRANSPORT_LAYER_CONFIGURATION_INFO_SIZE     (sizeof(qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t))
/** @endcond */

/** @cond */
/**
 * Structure that is used with the qapi_BLE_HCI_Set_MWS_Signaling()
 * command for the command parameters.
 */
typedef struct qapi_BLE_HCI_Set_MWS_Signaling_Parameters_s
{
   /**
    * RX Assert Offset.
    */
   uint16_t MWS_RX_Assert_Offset;

   /**
    * RX Assert Jitter.
    */
   uint16_t MWS_RX_Assert_Jitter;

   /**
    * RX Deassert Offset.
    */
   uint16_t MWS_RX_Deassert_Offset;

   /**
    * RX Deassert Jitter.
    */
   uint16_t MWS_RX_Deassert_Jitter;

   /**
    * TX Assert Offset.
    */
   uint16_t MWS_TX_Assert_Offset;

   /**
    * TX Assert Jitter.
    */
   uint16_t MWS_TX_Assert_Jitter;

   /**
    * TX Deassert Offset.
    */
   uint16_t MWS_TX_Deassert_Offset;

   /**
    * TX Deassert Jitter.
    */
   uint16_t MWS_TX_Deassert_Jitter;

   /**
    * Pattern Assert Offset.
    */
   uint16_t MWS_Pattern_Assert_Offset;

   /**
    * Pattern Assert Jitter.
    */
   uint16_t MWS_Pattern_Assert_Jitter;

   /**
    * Inactivity Duration Assert Offset.
    */
   uint16_t MWS_Inactivity_Duration_Assert_Offset;

   /**
    * Inactivity Duration Assert Jitter.
    */
   uint16_t MWS_Inactivity_Duration_Assert_Jitter;

   /**
    * Scan Frequency Assert Offset.
    */
   uint16_t MWS_Scan_Frequency_Assert_Offset;

   /**
    * Scan Frequency Assert Jitter.
    */
   uint16_t MWS_Scan_Frequency_Assert_Jitter;

   /**
    * Priority Assert Offset Request.
    */
   uint16_t MWS_Priority_Assert_Offset_Request;
} qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t;
/** @endcond */

/** @cond */
/** Size of the #qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t structure. */
#define QAPI_BLE_HCI_SET_MWS_SIGNALING_PARAMETERS_SIZE               (sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t))
/** @endcond */

/** @cond */
/**
 * Structure that is used with the qapi_BLE_HCI_Set_MWS_Signaling()
 * command for the command Result.
 */
typedef struct qapi_BLE_HCI_Set_MWS_Signaling_Result_s
{
   /**
    * Bluetooth RX Priority Assert Offset.
    */
   uint16_t Bluetooth_RX_Priority_Assert_Offset;

   /**
    * Bluetooth RX Priority Assert Jitter.
    */
   uint16_t Bluetooth_RX_Priority_Assert_Jitter;

   /**
    * Bluetooth RX Priority Deassert Offset.
    */
   uint16_t Bluetooth_RX_Priority_Deassert_Offset;

   /**
    * Bluetooth RX Priority Deassert Jitter.
    */
   uint16_t Bluetooth_RX_Priority_Deassert_Jitter;

   /**
    * 802 RX Priority Assert Offset.
    */
   uint16_t _802_RX_Priority_Assert_Offset;

   /**
    * 802 RX Priority Assert Jitter.
    */
   uint16_t _802_RX_Priority_Assert_Jitter;

   /**
    * 802 RX Priority Deassert Offset.
    */
   uint16_t _802_RX_Priority_Deassert_Offset;

   /**
    * 802 RX Priority Deassert Jitter.
    */
   uint16_t _802_RX_Priority_Deassert_Jitter;

   /**
    * Bluetooth TX On Assert Offset.
    */
   uint16_t Bluetooth_TX_On_Assert_Offset;

   /**
    * Bluetooth TX On Assert Jitter.
    */
   uint16_t Bluetooth_TX_On_Assert_Jitter;

   /**
    * Bluetooth TX On Deassert Offset.
    */
   uint16_t Bluetooth_TX_On_Deassert_Offset;

   /**
    * Bluetooth TX On Deassert Jitter.
    */
   uint16_t Bluetooth_TX_On_Deassert_Jitter;

   /**
    * 802 TX On Assert Offset.
    */
   uint16_t _802_TX_On_Assert_Offset;

   /**
    * 802 TX On Assert Jitter.
    */
   uint16_t _802_TX_On_Assert_Jitter;

   /**
    * 802 TX On Deassert Offset.
    */
   uint16_t _802_TX_On_Deassert_Offset;

   /**
    * 802 TX On Deassert Jitter.
    */
   uint16_t _802_TX_On_Deassert_Jitter;
} qapi_BLE_HCI_Set_MWS_Signaling_Result_t;
/** @endcond */

/** @cond */
/** Size of the #qapi_BLE_HCI_Set_MWS_Signaling_Result_t structure. */
#define QAPI_BLE_HCI_SET_MWS_SIGNALING_RESULT_SIZE                   (sizeof(qapi_BLE_HCI_Set_MWS_Signaling_Result_t))
/** @endcond */

/**
 *  HCI Event API Types.
 */
typedef enum
{
   QAPI_BLE_ET_DISCONNECTION_COMPLETE_EVENT_E = 4,
   /**< HCI Disconnection Complete event. */

   QAPI_BLE_ET_ENCRYPTION_CHANGE_EVENT_E = 7,
   /**< HCI Encryption Change event. */

   QAPI_BLE_ET_READ_REMOTE_VERSION_INFORMATION_COMPLETE_EVENT_E = 11,
   /**< HCI Read Remote Version Information Complete event. */

   QAPI_BLE_ET_HARDWARE_ERROR_EVENT_E = 13,
   /**< HCI Hardware Error event. */

   QAPI_BLE_ET_NUMBER_OF_COMPLETED_PACKETS_EVENT_E = 16,
   /**< HCI Number of Completed Packets event. */

   QAPI_BLE_ET_DATA_BUFFER_OVERFLOW_EVENT_E = 23,
   /**< HCI Data Buffer Overflow event. */

   QAPI_BLE_ET_VENDOR_SPECIFIC_DEBUG_EVENT_E = 31,
   /**< HCI Vendor Specific Debug event. */

   QAPI_BLE_ET_DEVICE_RESET_EVENT_E = 32,
   /**< Device Reset event. */

   QAPI_BLE_ET_ENCRYPTION_KEY_REFRESH_COMPLETE_EVENT_E = 40,
   /**< HCI Encryption Key Refresh Complete event. */

   QAPI_BLE_ET_LE_META_EVENT_E = 66,
   /**< HCI LE Meta event. */

   QAPI_BLE_ET_PLATFORM_SPECIFIC_EVENT_E = 67,
   /**< Platform Specific Event event. */

   QAPI_BLE_ET_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT_E = 77
   /**< HCI Authenticated Payload Timeout Expired event. */
} qapi_BLE_HCI_Event_Type_t;

/**
*   LE Meta Event Subevent Types.  (Version 4.0 + LE).
*/
typedef enum
{
   QAPI_BLE_ME_CONNECTION_COMPLETE_EVENT_E,
   /**< LE Connection Complete LE Meta subevent. */

   QAPI_BLE_ME_ADVERTISING_REPORT_EVENT_E,
   /**< LE Advertising Report LE Meta subevent. */

   QAPI_BLE_ME_CONNECTION_UPDATE_COMPLETE_EVENT_E,
   /**< LE Connection Update Complete LE Meta subevent. */

   QAPI_BLE_ME_READ_REMOTE_USED_FEATURES_COMPLETE_EVENT_E,
   /**< LE Read Remote Used Features Complete LE Meta subevent. */

   QAPI_BLE_ME_LONG_TERM_KEY_REQUEST_EVENT_E,
   /**< LE Long Term Key Request LE Meta subevent. */

   QAPI_BLE_ME_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT_E,
   /**< LE Remote Connection Parameter Request LE Meta subevent. */

   QAPI_BLE_ME_DATA_LENGTH_CHANGE_EVENT_E,
   /**< LE Data Length Change LE Meta subevent. */

   QAPI_BLE_ME_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT_E,
   /**< LE Read Local P-256 Public Key Complete LE Meta subevent. */

   QAPI_BLE_ME_GENERATE_DHKEY_COMPLETE_EVENT_E,
   /**< LE DH-Key Complete LE Meta subevent. */

   QAPI_BLE_ME_ENHANCED_CONNECTION_COMPLETE_EVENT_E,
   /**< LE Enhanced Connection Complete LE Meta subevent. */

   QAPI_BLE_ME_DIRECT_ADVERTISING_REPORT_EVENT_E,
   /**< LE Direct Advertising Report LE Meta subevent. */

   QAPI_BLE_ME_PHY_UPDATE_COMPLETE_EVENT_E,
   /**< LE PHY Update LE Meta subevent. */

   QAPI_BLE_ME_EXTENDED_ADVERTISING_REPORT_EVENT_E,
   /**< LE Extended Advertising Report LE Meta subevent. */

   QAPI_BLE_ME_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_EVENT_E,
   /**< LE Periodic Advertising Sync Established LE Meta subevent. */

   QAPI_BLE_ME_PERIODIC_ADVERTISING_REPORT_EVENT_E,
   /**< LE Periodic Advertising Report LE Meta subevent. */

   QAPI_BLE_ME_PERIODIC_ADVERTISING_SYNC_LOST_EVENT_E,
   /**< LE Periodic Advertising Sync Lost LE Meta subevent. */

   QAPI_BLE_ME_SCAN_TIMEOUT_EVENT_E,
   /**< LE Periodic Advertising Sync Lost LE Meta subevent. */

   QAPI_BLE_ME_ADVERTISING_SET_TERMINATED_EVENT_E,
   /**< LE Periodic Advertising Set Terminated LE Meta subevent. */

   QAPI_BLE_ME_SCAN_REQUEST_RECEIVED_EVENT_E,
   /**< LE Scan Request Received LE Meta subevent. */

   QAPI_BLE_ME_CHANNEL_SELECTION_ALGORITHM_EVENT_E,
   /**< LE Channel Selection Algorithm LE Meta subevent. */

   QAPI_BLE_ME_CONNECTIONLESS_IQ_REPORT_EVENT_E,
   /**< LE Connectionless IQ Report LE Meta subevent. */

   QAPI_BLE_ME_CONNECTION_IQ_REPORT_EVENT_E,
   /**< LE Connection IQ Report LE Meta subevent. */

   QAPI_BLE_ME_CTE_REQUEST_FAILED_EVENT_E,
   /**< LE CTE Request Failed LE Meta subevent. */

   QAPI_BLE_ME_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_EVENT_E
   /**< LE Periodic Advertising Sync Transfer Received LE Meta subevent. */
} qapi_BLE_HCI_LE_Meta_Event_Type_t;

/**
 * Structure that represents the Data that is associated with the HCI
 * Disconnection Complete Event.
 */
typedef struct qapi_BLE_HCI_Disconnection_Complete_Event_Data_s
{
   /**
    * Status of the disconnection.
    */
   uint8_t  Status;

   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Reason for the disconnection.
    */
   uint8_t  Reason;
} qapi_BLE_HCI_Disconnection_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Disconnection_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_DISCONNECTION_COMPLETE_EVENT_DATA_SIZE      (sizeof(qapi_BLE_HCI_Disconnection_Complete_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Encryption Change Event.
 */
typedef struct qapi_BLE_HCI_Encryption_Change_Event_Data_s
{
   /**
    * Status of the encryption change.
    */
   uint8_t  Status;

   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Encryption state.
    */
   uint8_t  Encryption_Enable;
} qapi_BLE_HCI_Encryption_Change_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Encryption_Change_Event_Data_t structure. */
#define QAPI_BLE_HCI_ENCRYPTION_CHANGE_EVENT_DATA_SIZE           (sizeof(qapi_BLE_HCI_Encryption_Change_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Read Remote Version Information Complete Event.
 */
typedef struct qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_Data_s
{
   /**
    * Status of the remote version information request.
    */
   uint8_t  Status;

   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * LMP version.
    */
   uint8_t  LMP_Version;

   /**
    * Manufacturer name.
    */
   uint16_t Manufacturer_Name;

   /**
    * LMP Subversion.
    */
   uint16_t LMP_Subversion;
} qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE_EVENT_DATA_SIZE (sizeof(qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Hardware Error Event.
 */
typedef struct qapi_BLE_HCI_Hardware_Error_Event_Data_s
{
   /**
    * Hardware error code.
    */
   uint8_t Hardware_Code;
} qapi_BLE_HCI_Hardware_Error_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Hardware_Error_Event_Data_t structure. */
#define QAPI_BLE_HCI_HARDWARE_ERROR_EVENT_DATA_SIZE              (sizeof(qapi_BLE_HCI_Hardware_Error_Event_Data_t))

/**
 * Structure that is used with the HCI Number of Completed Packets Event,
 * and represents a single Connection Handle/Host Number of Completed
 * Packets Pair that is required by this Event.
 *
 * Structure that represents an individual entry and a HCI Number of
 * Completed Packets Event will contain a variable number of these
 * structures.
 */
typedef struct qapi_BLE_HCI_Number_Of_Completed_Packets_Data_s
{
   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Number of completed HC packets.
    */
   uint16_t HC_Num_Of_Completed_Packets;
} qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t;

/** Size of the #qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t structure. */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_DATA_SIZE       (sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Number Of Completed Packets Event.
 *
 * The HCI_Number_Of_Completed_Packets_Data
 * member represents a variable array that can contain 0 or more entries.
 * The number of Entries in this array is given by the Number_of_Handles
 * member.
 *
 * A utility macro,
 * #QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_DATA_SIZE, is provided
 * to aid in the calculation of the Number of Bytes that are occupied by
 * the structure given a specified number of Handles.
 */
typedef struct qapi_BLE_HCI_Number_Of_Completed_Packets_Event_Data_s
{
   /**
    * Number of handles.
    */
   uint8_t                                         Number_of_Handles;

   /**
    * Number of completed packets data.
    */
   qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t HCI_Number_Of_Completed_Packets_Data[1];
} qapi_BLE_HCI_Number_Of_Completed_Packets_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code */
   /* readability to Determine the size (in Bytes) of an */
   /* HCI Number of Completed Packets Event Data Structure based on */
   /* the number of HCI Number of Completed Packets Event Data Entries */
   /* associated with the Event.  The first parameter to this MACRO is */
   /* the number of HCI Number of Completed Packets Entries. */

/** Size of the #qapi_BLE_HCI_Number_Of_Completed_Packets_Event_Data_t structure. */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_DATA_SIZE(_x)     ((sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Event_Data_t) - sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t)) + (((uint8_t)(_x))*sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t)))

/** Maximum number of completed packet entries. */
#define QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_MAX_DATA_ENTRIES  ((((sizeof(uint8_t))*256)-QAPI_BLE_HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_DATA_SIZE(0))/sizeof(qapi_BLE_HCI_Number_Of_Completed_Packets_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Data Buffer Overflow Event.
 */
typedef struct qapi_BLE_HCI_Data_Buffer_Overflow_Event_Data_s
{
   /**
    * Link type.
    */
   uint8_t Link_Type;
} qapi_BLE_HCI_Data_Buffer_Overflow_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Data_Buffer_Overflow_Event_Data_t structure. */
#define QAPI_BLE_HCI_DATA_BUFFER_OVERFLOW_EVENT_DATA_SIZE        (sizeof(qapi_BLE_HCI_Data_Buffer_Overflow_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Encryption Key Refresh Event (Version 2.1 + EDR).
 */
typedef struct qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_Data_s
{
   /**
    * Status of the encryption key refresh.
    */
   uint8_t  Status;

   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;
} qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_ENCRYPTION_KEY_REFRESH_COMPLETE_EVENT_DATA_SIZE          (sizeof(qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Connection Complete Event. (Version 4.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Connection_Complete_Event_Data_s
{
   /**
    * Status of the connection.
    */
   uint8_t            Status;

   /**
    * Connection handle.
    */
   uint16_t           Connection_Handle;

   /**
    * Connection role.
    */
   uint8_t            Role;

   /**
    * Peer address type.
    */
   uint8_t            Peer_Address_Type;

   /**
    * Peer address.
    */
   qapi_BLE_BD_ADDR_t Peer_Address;

   /**
    * Connection interval.
    */
   uint16_t           Conn_Interval;

   /**
    * Connection latency.
    */
   uint16_t           Conn_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t           Supervision_Timeout;

   /**
    * Master clock accuracy.
    */
   uint8_t            Master_Clock_Accuracy;
} qapi_BLE_HCI_LE_Connection_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Connection_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CONNECTION_COMPLETE_EVENT_DATA_SIZE                   (sizeof(qapi_BLE_HCI_LE_Connection_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Avertising Report Event.
 *
 * Structure that represents an individual entry, and the
 * qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t structure will contain
 * an array of these structures (based on the number of responses).
 * (Version 4.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Advertising_Report_Data_s
{
   /**
    * Event type.
    */
   uint8_t                     Event_Type;

   /**
    * Remote address type.
    */
   uint8_t                     Address_Type;

   /**
    * Remote address.
    */
   qapi_BLE_BD_ADDR_t          Address;

   /**
    * Advertising data length.
    */
   uint8_t                     Data_Length;

   /**
    * Advertising data.
    */
   qapi_BLE_Advertising_Data_t Data;

   /**
    * Remote Signal Strength Indicator (RSSI).
    */
   int8_t                      RSSI;
} qapi_BLE_HCI_LE_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Advertising_Report_Data_t structure. */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_DATA_SIZE                                (sizeof(qapi_BLE_HCI_LE_Advertising_Report_Data_t))

/**
 * Structure that represents the data that is associated with the HCI LE
 * Meta Event with Subevent LE Avertising Report Event.
 *
 * The HCI_LE_Advertising_Report_Data member represents a variable array
 * that can contain 0 or more entries. The Number of Entries in this
 * array is given by the Num_Responses member.
 *
 * A utility macro, #QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE,
 * is provided to aid in the calculation of the Number of Bytes that are
 * occupied by the structure given a specified number of responses.
 * (Version 4.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Advertising_Report_Event_Data_s
{
   /**
    * Number of responses.
    */
   uint8_t                                   Num_Responses;

   /**
    * Advertising report data.
    */
   qapi_BLE_HCI_LE_Advertising_Report_Data_t HCI_LE_Advertising_Report_Data[1];
} qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code */
   /* readability to Determine the size (in Bytes) of a qapi BLE HCI LE */
   /* Advertising Report Event Data Structure that must be allocated to */
   /* store the number of HCI LE Advertising Report Event Entries */
   /* associated with the Event.  The first parameter to this MACRO is */
   /* the number of HCI LE Advertising Event Entries (Version 4.0 + LE).*/

/** Size of the #qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t structure of the specified number of reports. */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE(_x)                      ((sizeof(qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t) - sizeof(qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t)) + (((uint32_t)(_x))*sizeof(qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t)))

/** Maximum number of advertising report entries. */
#define QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_MAX_DATA_ENTRIES                   ((((sizeof(uint8_t))*256)-QAPI_BLE_HCI_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE(0))/sizeof(qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Connection Update Complete Event (Version 4.0 +
 * LE).
 */
typedef struct qapi_BLE_HCI_LE_Connection_Update_Complete_Event_Data_s
{
   /**
    * Status of the connection update.
    */
   uint8_t  Status;

   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Connection interval.
    */
   uint16_t Conn_Interval;

   /**
    * Connection latency.
    */
   uint16_t Conn_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t Supervision_Timeout;
} qapi_BLE_HCI_LE_Connection_Update_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Connection_Update_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CONNECTION_UPDATE_COMPLETE_EVENT_DATA_SIZE                  (sizeof(qapi_BLE_HCI_LE_Connection_Update_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Read Remote Used Features Complete Event
 * (Version 4.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_s
{
   /**
    * Status of the remote used features request.
    */
   uint8_t                Status;

   /**
    * Connection handle.
    */
   uint16_t               Connection_Handle;

   /**
    * LE Features.
    */
   qapi_BLE_LE_Features_t LE_Features;
} qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_READ_REMOTE_USED_FEATURES_COMPLETE_EVENT_DATA_SIZE          (sizeof(qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Long Term Key Request Event (Version 4.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_Data_s
{
   /**
    * Connection handle.
    */
   uint16_t                 Connection_Handle;

   /**
    * Random number.
    */
   qapi_BLE_Random_Number_t Random_Number;

   /**
    * Encryption diversifier.
    */
   uint16_t                 Encrypted_Diversifier;
} qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_LONG_TERM_KEY_REQUEST_EVENT_DATA_SIZE                       (sizeof(qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
   HCI LE Meta Event with Subevent LE Remote Connection Parameter
   Request Event (Version 4.1).
 */
typedef struct qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_Data_s
{
   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Maximum connection interval.
    */
   uint16_t Conn_Interval_Min;

   /**
    * Minimum connection interval.
    */
   uint16_t Conn_Interval_Max;

   /**
    * Connection latency.
    */
   uint16_t Conn_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t Supervision_Timeout;
} qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT_DATA_SIZE         (sizeof(qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
 * HCI LE Meta Event with Subevent LE Data Length Change Event
 * (Version 4.2).
 */
typedef struct qapi_BLE_HCI_LE_Data_Length_Change_Event_Data_s
{
   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;

   /**
    * Maximum transmit octets.
    */
   uint16_t MaxTxOctets;

   /**
    * Maximum transmit time.
    */
   uint16_t MaxTxTime;

   /**
    * Maximum receive octets.
    */
   uint16_t MaxRxOctets;

   /**
    * Maximum receive time.
    */
   uint16_t MaxRxTime;
} qapi_BLE_HCI_LE_Data_Length_Change_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Data_Length_Change_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_DATA_LENGTH_CHANGE_EVENT_DATA_SIZE                          (sizeof(qapi_BLE_HCI_LE_Data_Length_Change_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
 * HCI LE Meta Event with Subevent LE Read Local P256 Public Key
 * Complete Event (Version 4.2).
 */
typedef struct qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data_s
{
   /**
    * Status of reading the local P256 Public key.
    */
   uint8_t                    Status;

   /**
    * P256 Public key.
    */
   qapi_BLE_P256_Public_Key_t P256_Public_Key;
} qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT_DATA_SIZE         (sizeof(qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Generate DHKey Complete Event (Version 4.2).
 */
typedef struct qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_Data_s
{
   /**
    * Status of generating the Deffie Hellman key.
    */
   uint8_t                       Status;

   /**
    * Deffie Hellman key.
    */
   qapi_BLE_Diffie_Hellman_Key_t DHKey;
} qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_GENERATE_DHKEY_COMPLETE_EVENT_DATA_SIZE                     (sizeof(qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
 * HCI LE Meta Event with Subevent LE Enhanced Connection Complete
 * Event (Version 4.2).
 *
 * The Local and Peer Resolvable Private Address fields are intentionally
 * put at the end of this structure (whereas they are not returned in
 * this order by the controller) in order to allow the upper layer code
 * to be shared with the traditional LE Connection Complete event.
 */
typedef struct qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_Data_s
{
   /**
    * Status of the connection.
    */
   uint8_t            Status;

   /**
    * Connection handle.
    */
   uint16_t           Connection_Handle;

   /**
    * Connection role.
    */
   uint8_t            Role;

   /**
    * Peer address type.
    */
   uint8_t            Peer_Address_Type;

   /**
    * Peer address.
    */
   qapi_BLE_BD_ADDR_t Peer_Address;

   /**
    * Connection interval.
    */
   uint16_t           Conn_Interval;

   /**
    * Connection latency.
    */
   uint16_t           Conn_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t           Supervision_Timeout;

   /**
    * Master clock accuracy.
    */
   uint8_t            Master_Clock_Accuracy;

   /**
    * Local resolvable private address.
    */
   qapi_BLE_BD_ADDR_t Local_Resolvable_Private_Address;

   /**
    * Peer resolvable private address.
    */
   qapi_BLE_BD_ADDR_t Peer_Resolvable_Private_Address;
} qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_ENHANCED_CONNECTION_COMPLETE_EVENT_DATA_SIZE                (sizeof(qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Direct Avertising Report Event. This structure
 * represents an individual entry, and the
 * qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_t structure will
 * contain an array of these structures (based on the number of
 * responses).  (Version 4.2).
 */
typedef struct qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_s
{
   /**
    * Event type.
    */
   uint8_t             Event_Type;

   /**
    * Direct address type.
    */
   uint8_t             Direct_Address_Type;

   /**
    * Address type.
    */
   qapi_BLE_BD_ADDR_t  Direct_Address;

   /**
    * Remote address type.
    */
   uint8_t             Address_Type;

   /**
    * Remote address.
    */
   qapi_BLE_BD_ADDR_t  Address;

   /**
    * Remote Signal Strength Indicator (RSSI).
    */
   int8_t              RSSI;
} qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t structure. */
#define QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_DATA_SIZE                         (sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t))

/**
 * Structure that represents the data that is associated with the HCI LE
 * Meta Event with Subevent LE Direct Avertising Report Event.
 *
 * The
 * HCI_LE_Direct_Advertising_Report_Data member represents a variable
 * array that can contain 0 or more entries. The Number of Entries in
 * this array is given by the Num_Responses member.
 *
 * A utility macro,
 * #QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_EVENT_DATA_SIZE, is
 * provided to aid in the calculation of the Number of Bytes that are
 * occupied by the structure given a specified number of Responses.
 * (Version 4.2).
 */
typedef struct qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_s
{
   /**
    * Number of responses.
    */
   uint8_t                                           Num_Responses;

   /**
    * Direct advertising report data.
    */
   qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t  HCI_LE_Direct_Advertising_Report_Data[1];
} qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code */
   /* readability to Determine the size (in Bytes) of an HCI LE */
   /* Advertising Report Event Data Structure that must be allocated to */
   /* store the number of HCI LE Advertising Report Event Entries */
   /* associated with the Event. The first parameter to this MACRO is */
   /* the number of HCI LE Advertising Event Entries (Version 4.0 + LE).*/

/** Size of the #qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_t 
    for the specified number of direct advertising reports. */
#define QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_EVENT_DATA_SIZE(_x)               ((sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_t) - sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t)) + (((uint32_t)(_x))*sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t)))

/** Maximum number of direct advertising reports. */
#define QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_EVENT_MAX_DATA_ENTRIES            ((((sizeof(uint8_t))*256)-QAPI_BLE_HCI_LE_DIRECT_ADVERTISING_REPORT_EVENT_DATA_SIZE(0))/sizeof(qapi_BLE_HCI_LE_Direct_Advertising_Report_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE PHY Update Complete Event.  (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_PHY_Update_Complete_Event_Data_s
{
   /**
    * Status of the PHY update.
    */
   uint8_t  Status;

   /**
    * Connection handle that identifies the connection associated
    * with the Tx/Rx PHY values.
    */
   uint16_t Connection_Handle;

   /**
    * Current Tx PHY for the specified connection.
    */
   uint8_t  TX_PHY;

   /**
    * Current Rx PHY for the specified connection.
    */
   uint8_t  RX_PHY;
} qapi_BLE_HCI_LE_PHY_Update_Complete_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_PHY_Update_Complete_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_PHY_UPDATE_COMPLETE_EVENT_DATA_SIZE                         (sizeof(qapi_BLE_HCI_LE_PHY_Update_Complete_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Extended Avertising Report Event. This
 * structure represents an individual entry, and the HCI LE Advertising
 * Report Event structure will contain an array of these structures
 * (based on the number of responses). (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_s
{
   /**
    * Extended Advertising event type.
    */
   uint16_t                             Event_Type;

   /**
    * Address type of the advertiser.
    */
   uint8_t                              Address_Type;

   /**
    * Address of the advertiser.
    */
   qapi_BLE_BD_ADDR_t                   Address;

   /**
    * Primary channel PHY.
    */
   uint8_t                              Primary_PHY;

   /**
    * Secondary channel PHY.
    */
   uint8_t                              Secondary_PHY;

   /**
    * Advertising SID.
    */
   uint8_t                              Advertising_SID;

   /**
    * Transmit power.
    */
   uint8_t                              TX_Power;

   /**
    * Remote signal strength indicator (RSSI).
    */
   uint8_t                              RSSI;

   /**
    * Periodic advertising interval.
    */
   uint16_t                             Periodic_Advertising_Interval;

   /**
    * Direct address type.
    */
   uint8_t                              Direct_Address_Type;

   /**
    * Direct address.
    */
   qapi_BLE_BD_ADDR_t                   Direct_Address;

   /**
    * Length of Extended Advertising data.
    */
   uint8_t                              Data_Length;

   /**
    * Extended Advertising data.
    */
   qapi_BLE_Extended_Advertising_Data_t Data;
} qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t structure. */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_DATA_SIZE                       (sizeof(qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t))

/**
 * Structure that represents the data that is associated with the HCI LE
 * Meta Event with Subevent LE Avertising Report Event. The
 * qapi_BLE_HCI_LE_Extended_Advertising_Report_Data member represents a
 * variable array that can contain 0 or more entries. The Number of
 * Entries in this array is given by the Num_Reports member. A utility
 * MACRO is provided to aid in the calculation of the Number of Bytes
 * that are occupied by the structure given a specified number of
 * responses. (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_Data_s
{
   /**
    * Number of extended advertising reports.
    */
   uint8_t                                            Num_Reports;

   /**
    * Extended advertising reports.
    */
   qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t HCI_LE_Extended_Advertising_Report_Data[1];
} qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code */
   /* readability to Determine the size (in Bytes) of an HCI LE Extended*/
   /* Advertising Report Event Data Structure that must be allocated to */
   /* store the number of HCI LE Extended Advertising Report Event */
   /* Entries associated with the Event. The first parameter to this */
   /* MACRO is the number of HCI LE Extended Advertising Event Entries */
   /* (Version 5.0 + LE). */

/** Size of the #qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_Data_t
    structure for the specified number of extended advertising reports. */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_DATA_SIZE(_x)             ((sizeof(qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_Data_t) - sizeof(qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t)) + (((unsigned int)(_x))*sizeof(qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t)))

/** Maximum number of extended advertising reports in one event. */
#define QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_MAX_DATA_ENTRIES          ((((sizeof(uint8_t))*256)-QAPI_BLE_HCI_LE_EXTENDED_ADVERTISING_REPORT_EVENT_DATA_SIZE(0))/sizeof(qapi_BLE_HCI_LE_Extended_Advertising_Report_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Avertising Set Terminated Event (Version 5.0 +
 * LE).
 */
typedef struct qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_Data_s
{
   /**
    * Status of the advertising set termination.
    */
   uint8_t  Status;

   /**
    * Advertising handle that identifies the advertising set that
    * has been terminated.
    */
   uint8_t  Advertising_Handle;

   /**
    * Connection handle for the connection that is associated with
    * the advertising set.
    */
   uint16_t Connection_Handle;

   /**
    * Number of completed Extended Advertising events before the
    * advertising set was terminated.
    */
   uint8_t  Num_Completed_Extended_Advertising_Events;
} qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_ADVERTISING_SET_TERMINATED_EVENT_DATA_SIZE                  (sizeof(qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
   HCI LE Meta Event with Subevent LE Periodic Advertising Sync
   Established Event (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_Data_s
{
   /**
    * Status for the synchronization.
    */
   uint8_t            Status;

   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t           Sync_Handle;

   /**
    * Identifies the advertiser's advertising set.
    */
   uint8_t            Advertising_SID;

   /**
    * Advertiser's address type.
    */
   uint8_t            Advertiser_Address_Type;

   /**
    * Advertisers address.
    */
   qapi_BLE_BD_ADDR_t Advertiser_Address;

   /**
    * PHY used by the advertiser for the periodic advertisements.
    */
   uint8_t            Advertiser_PHY;

   /**
    * Advertising interval.
    */
   uint16_t           Periodic_Advertising_Interval;

   /**
    * Advertiser's clock accuracy.
    */
   uint8_t            Advertiser_Clock_Accuracy;
} qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_EVENT_DATA_SIZE       (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_Data_t))

/**
 * Structure that represents the data that is returned in a
   HCI LE Meta Event with Subevent LE Periodic Avertising Report
   Event (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_Data_s
{
   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t                             Sync_Handle;

   /**
    * Advertiser's transmit power.
    */
   int8_t                               TX_Power;

   /**
    * Remote signal strength Indicator.
    */
   int8_t                               RSSI;

   /**
    * Contant tone extension type.
    */
   uint8_t                              CTE_Type;

   /**
    * Advertising data status.
    */
   uint8_t                              Data_Status;

   /**
    * Advertising data length.
    */
   uint8_t                              Data_Length;

   /**
    * Advertising data.
    */
   qapi_BLE_Periodic_Advertising_Data_t Data;
} qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_REPORT_EVENT_DATA_SIZE                 (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_Data_t))

   /** The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Periodic Avertising Sync Lost   */
   /* Event (Version 5.0 + LE).                                          */
typedef struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data_s
{
   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t Sync_Handle;
} qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT_DATA_SIZE              (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Scan Request Received Event (Version 5.0 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Scan_Request_Received_Event_Data_s
{
   /**
    * Advertising handle that identifies the advertising set that
    * has received a scan request.
    */
   uint8_t            Advertising_Handle;

   /**
    * Scanner address type.
    */
   uint16_t           Scanner_Address_Type;

   /**
    * Scanner address.
    */
   qapi_BLE_BD_ADDR_t Scanner_Address;
} qapi_BLE_HCI_LE_Scan_Request_Received_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Scan_Request_Received_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_SCAN_REQUEST_RECEIVED_EVENT_DATA_SIZE                       (sizeof(qapi_BLE_HCI_LE_Scan_Request_Received_Event_Data_t))

/**
 * Structure that represents the data that is returned in a HCI LE Meta
 * Event with Subevent LE Channel Selection Algorithm Event (Version 5.0
 * + LE).
 */
typedef struct qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_Data_s
{
   /**
    * Connection handle for the connection.
    */
   uint16_t Connection_Handle;

   /**
    * Channel selection algorithm that is selected.
    */
   uint8_t  Channel_Selection_Algorithm;
} qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CHANNEL_SELECTION_ALGORITHM_EVENT_DATA_SIZE                 (sizeof(qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_Data_t))

/**
 * Structure that represents the data that is returned in the
 * #QAPI_BLE_ME_CONNECTIONLESS_IQ_REPORT_EVENT_E Event (Version 5.1 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Connectionless_IQ_Report_Event_Data_s
{
   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t  Sync_Handle;

   /**
    * Advertising channel index.
    */
   uint8_t   Channel_Index;

   /**
    * Remote signal strength indicator.
    */
   int16_t   RSSI;

   /**
    * Antenna used for the RSSI.
    */
   uint8_t   RSSI_Antenna_ID;

   /**
    * Contant tone extension type.
    */
   uint8_t   CTE_Type;

   /**
    * Slot durations used for the CTE.
    */
   uint8_t   Slot_Durations;

   /**
    * Status of the packet.
    */
   uint8_t   Packet_Status;

   /**
    * Periodic advertising event counter.
    */
   uint16_t  Pa_Event_Counter;

   /**
    * Number of IQ samples taken.
    */
   uint8_t   Sample_Count;

   /**
    * List of I samples.
    */
   int8_t   *I_Sample;

   /**
    * List of Q samples.
    */
   int8_t   *Q_Sample;
} qapi_BLE_HCI_LE_Connectionless_IQ_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to calculated */
   /* the size of the HCI_LE_Connectionless_IQ_Report_Event_Data_t */
   /* structure. The first parameter is the Sample_Count field. */

/** Size of the #qapi_BLE_HCI_LE_Connectionless_IQ_Report_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CONNECTIONLESS_IQ_REPORT_EVENT_DATA_SIZE(_x)                ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Connectionless_IQ_Report_Event_Data_t, I_Sample) + ((_x) * sizeof(qapi_BLE_NonAlignedWord_t))))

/**
 * Structure that represents the data that is returned in the
 * #QAPI_BLE_ME_CONNECTION_IQ_REPORT_EVENT_E Event (Version 5.1 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Connection_IQ_Report_Event_Data_s
{
   /**
    * Identifies the connection with the remote device that sent the CTE
    * request response.
    */
   uint16_t  Connection_Handle;

   /**
    * PHY used for the CTE request response.
    */
   uint8_t   RX_PHY;

   /**
    * Data channel index.
    */
   uint8_t   Data_Channel_Index;

   /**
    * Remote signal strength indicator.
    */
   int16_t   RSSI;

   /**
    * Antenna used for the RSSI.
    */
   uint8_t   RSSI_Antenna_ID;

   /**
    * Contant tone extension type.
    */
   uint8_t   CTE_Type;

   /**
    * Slot durations used for the CTE.
    */
   uint8_t   Slot_Durations;

   /**
    * Status of the packet.
    */
   uint8_t   Packet_Status;

   /**
    * Connection event counter.
    */
   uint16_t  Conn_Event_Counter;

   /**
    * Number of IQ samples taken.
    */
   uint8_t   Sample_Count;

   /**
    * List of I samples.
    */
   int8_t   *I_Sample;

   /**
    * List of Q samples.
    */
   int8_t   *Q_Sample;
} qapi_BLE_HCI_LE_Connection_IQ_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to calculated */
   /* the size of the HCI_LE_Connection_IQ_Report_Event_Data_t */
   /* structure. The first parameter is the Sample_Count field. */

/** Size of the #qapi_BLE_HCI_LE_Connection_IQ_Report_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CONNECTION_IQ_REPORT_EVENT_DATA_SIZE(_x)                    ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_HCI_LE_Connection_IQ_Report_Event_Data_t, I_Sample) + ((_x) * sizeof(qapi_BLE_NonAlignedWord_t))))


   /* The following structure represents the data that is returned in */
   /* the meCTE_Request_Failed_Event event. Event (Version 5.1 + LE). */

/**
 * Structure that represents the data that is returned in the
 * #QAPI_BLE_ME_CTE_REQUEST_FAILED_EVENT_E Event (Version 5.1 + LE).
 */
typedef struct qapi_BLE_HCI_LE_CTE_Request_Failed_Event_Data_s
{
   /**
    * Reason for the failure.
    */
   uint8_t Status;

   /**
    * Identifies the connection with the remote device that sent the CTE
    * request response.
    */
   uint16_t Connection_Handle;
} qapi_BLE_HCI_LE_CTE_Request_Failed_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_CTE_Request_Failed_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_CTE_REQUEST_FAILED_EVENT_DATA_SIZE                          (sizeof(qapi_BLE_HCI_LE_CTE_Request_Failed_Event_Data_t))

/**
 * Structure that represents the data that is returned in the
 * #QAPI_BLE_ME_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_EVENT_E Event (Version 5.1 + LE).
 */
typedef struct qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_s
{
   /**
    * Indicates the status.
    */
   uint8_t            Status;

   /**
    * Identifies the remote device that transfered the periodic
    * advertising sync information.
    */
   uint16_t           Connection_Handle;

   /**
    * Host specific information sent by the remote device.
    */
   uint16_t           Service_Data;

   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t           Sync_Handle;

   /**
    * Identifies the advertiser's advertising set.
    */
   uint8_t            Advertising_SID;

   /**
    * Advertiser's address type.
    */
   uint8_t            Advertiser_Address_Type;

   /**
    * Advertisers address.
    */
   qapi_BLE_BD_ADDR_t Advertiser_Address;

   /**
    * PHY used by the advertiser for the periodic advertisements.
    */
   uint8_t            Advertiser_PHY;

   /**
    * Advertising interval.
    */
   uint16_t           Periodic_Advertising_Interval;

   /**
    * Advertiser's clock accuracy.
    */
   uint8_t            Advertiser_Clock_Accuracy;
} qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_EVENT_DATA_SIZE  (sizeof(qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t))

/**
 * Structure that represents the container structure for holding all the
 * HCI Metadata event data.
 */
typedef struct qapi_BLE_HCI_LE_Meta_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_HCI_LE_Meta_Event_Type_t LE_Event_Data_Type;
   union
   {
      /**
       * HCI LE Connection Complete event data.
       */
      qapi_BLE_HCI_LE_Connection_Complete_Event_Data_t                            HCI_LE_Connection_Complete_Event_Data;

      /**
       * HCI LE Advertising Report event data.
       */
      qapi_BLE_HCI_LE_Advertising_Report_Event_Data_t                             HCI_LE_Advertising_Report_Event_Data;

      /**
       * HCI LE Connection Update Complete event data.
       */
      qapi_BLE_HCI_LE_Connection_Update_Complete_Event_Data_t                     HCI_LE_Connection_Update_Complete_Event_Data;

      /**
       * HCI LE Read Remote Used Features Complete event data.
       */
      qapi_BLE_HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t             HCI_LE_Read_Remote_Used_Features_Complete_Event_Data;

      /**
       * HCI LE Long Term Key Request event data.
       */
      qapi_BLE_HCI_LE_Long_Term_Key_Request_Event_Data_t                          HCI_LE_Long_Term_Key_Request_Event_Data;

      /**
       * HCI LE Remote Connection Parameter Request event data.
       */
      qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Event_Data_t            HCI_LE_Remote_Connection_Parameter_Request_Event_Data;

      /**
       * HCI LE Data Length Change event.
       */
      qapi_BLE_HCI_LE_Data_Length_Change_Event_Data_t                             HCI_LE_Data_Length_Change_Event_Data;

      /**
       * HCI LE Read Local P256 Public Key Complete event data.
       */
      qapi_BLE_HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data_t            HCI_LE_Read_Local_P256_Public_Key_Complete_Event_Data;

      /**
       * HCI LE Generate Deffie Hellman Key Complete event data.
       */
      qapi_BLE_HCI_LE_Generate_DHKey_Complete_Event_Data_t                        HCI_LE_Generate_DHKey_Complete_Event_Data;

      /**
       * HCI LE Enhanced Connection Complete event data.
       */
      qapi_BLE_HCI_LE_Enhanced_Connection_Complete_Event_Data_t                   HCI_LE_Enhanced_Connection_Complete_Event_Data;

      /**
       * HCI LE Direct Advertising Report event data.
       */
      qapi_BLE_HCI_LE_Direct_Advertising_Report_Event_Data_t                      HCI_LE_Direct_Advertising_Report_Event_Data;

      /**
       * HCI LE PHY Update Complete event data.
       */
      qapi_BLE_HCI_LE_PHY_Update_Complete_Event_Data_t                            HCI_LE_PHY_Update_Complete_Event_Data;

      /**
       * HCI LE Extended Advertising Report event data.
       */
      qapi_BLE_HCI_LE_Extended_Advertising_Report_Event_Data_t                    HCI_LE_Extended_Advertising_Report_Event_Data;

      /**
       * HCI LE Periodic Advertising Sync Established event data.
       */
      qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Established_Event_Data_t          HCI_LE_Periodic_Advertising_Sync_Established_Event_Data;

      /**
       * HCI LE Periodic Advertising Report event data.
       */
      qapi_BLE_HCI_LE_Periodic_Advertising_Report_Event_Data_t                    HCI_LE_Periodic_Advertising_Report_Event_Data;

      /**
       * HCI LE Periodic Advertising Sync Lost event data.
       */
      qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data_t                 HCI_LE_Periodic_Advertising_Sync_Lost_Event_Data;

      /**
       * HCI LE Advertising Set Terminated event data.
       */
      qapi_BLE_HCI_LE_Advertising_Set_Terminated_Event_Data_t                     HCI_LE_Advertising_Set_Terminated_Event_Data;

      /**
       * HCI LE Scan Request Received event data.
       */
      qapi_BLE_HCI_LE_Scan_Request_Received_Event_Data_t                          HCI_LE_Scan_Request_Received_Event_Data;

      /**
       * HCI LE Channel Selection Algorithm event data.
       */
      qapi_BLE_HCI_LE_Channel_Selection_Algorithm_Event_Data_t                    HCI_LE_Channel_Selection_Algorithm_Event_Data;

      /**
       * HCI LE Connectionless IQ Report event data.
       */
      qapi_BLE_HCI_LE_Connectionless_IQ_Report_Event_Data_t                       HCI_LE_Connectionless_IQ_Report_Event_Data;

      /**
       * HCI LE Connection IQ Report event data.
       */
      qapi_BLE_HCI_LE_Connection_IQ_Report_Event_Data_t                           HCI_LE_Connection_IQ_Report_Event_Data;

      /**
       * HCI LE CTE Request Failed event data.
       */
      qapi_BLE_HCI_LE_CTE_Request_Failed_Event_Data_t                             HCI_LE_CTE_Request_Failed_Event_Data;

      /**
       * HCI LE Periodic Advertising Sync Transfer Received event data.
       */
      qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t    HCI_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data;
   }
   /**
    * Event data. @newpagetable
    */
   Event_Data;
} qapi_BLE_HCI_LE_Meta_Event_Data_t;

/** Size of the #qapi_BLE_HCI_LE_Meta_Event_Data_t structure. */
#define QAPI_BLE_HCI_LE_META_EVENT_DATA_SIZE                                        (sizeof(qapi_BLE_HCI_LE_Meta_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Platform Specific.
 */
typedef struct qapi_BLE_HCI_Platform_Specific_Event_Data_s
{
   /**
    * Platform event type.
    */
   uint32_t  Platform_Event_Type;

   /**
    * Pointer to the platform event data.
    */
   void     *Platform_Event_Data;
} qapi_BLE_HCI_Platform_Specific_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Platform_Specific_Event_Data_t structure. */
#define QAPI_BLE_HCI_PLATFORM_SPECIFIC_EVENT_DATA_SIZE                              (sizeof(qapi_BLE_HCI_Platform_Specific_Event_Data_t))

/**
 * Structure that represents the data that is associated with the HCI
 * Authenticated Payload Timeout Expired Event.
 */
typedef struct qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_Data_s
{
   /**
    * Connection handle.
    */
   uint16_t Connection_Handle;
} qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_Data_t structure. */
#define QAPI_BLE_HCI_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT_DATA_SIZE          (sizeof(qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_Data_t))

/**
 * Structure that represents the container structure for holding all the
 * HCI event data.
 */
typedef struct qapi_BLE_HCI_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_HCI_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event. @newpagetable
    */
   uint16_t                  Event_Data_Size;
   union
   {
      /**
       * HCI Disconnection Complete event data.
       */
      qapi_BLE_HCI_Disconnection_Complete_Event_Data_t                      *HCI_Disconnection_Complete_Event_Data;

      /**
       * HCI Encryption Change event data.
       */
      qapi_BLE_HCI_Encryption_Change_Event_Data_t                           *HCI_Encryption_Change_Event_Data;

      /**
       * HCI Read Remote Version Information Complete event data.
       */
      qapi_BLE_HCI_Read_Remote_Version_Information_Complete_Event_Data_t    *HCI_Read_Remote_Version_Information_Complete_Event_Data;

      /**
       * HCI Hardware Error event data.
       */
      qapi_BLE_HCI_Hardware_Error_Event_Data_t                              *HCI_Hardware_Error_Event_Data;

      /**
       * HCI Number of Completed Packets event data.
       */
      qapi_BLE_HCI_Number_Of_Completed_Packets_Event_Data_t                 *HCI_Number_Of_Completed_Packets_Event_Data;

      /**
       * HCI Data Buffer Overflow event data.
       */
      qapi_BLE_HCI_Data_Buffer_Overflow_Event_Data_t                        *HCI_Data_Buffer_Overflow_Event_Data;

      /**
       * HCI Encryption Key Refresh Complete event data.
       */
      qapi_BLE_HCI_Encryption_Key_Refresh_Complete_Event_Data_t             *HCI_Encryption_Key_Refresh_Complete_Event_Data;

      /**
       * HCI LE Meta event data.
       */
      qapi_BLE_HCI_LE_Meta_Event_Data_t                                     *HCI_LE_Meta_Event_Data;

      /**
       * HCI Platform Specfic event data.
       */
      qapi_BLE_HCI_Platform_Specific_Event_Data_t                           *HCI_Platform_Specific_Event_Data;

      /**
       * HCI Authenticated Payload Timeout Expired event data.
       */
      qapi_BLE_HCI_Authenticated_Payload_Timeout_Expired_Event_Data_t       *HCI_Authenticated_Payload_Timeout_Expired_Event_Data;

      /**
       * Unknown HCI event data.
       */
      void                                                                  *HCI_Unknown_Event_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_HCI_Event_Data_t;

/** Size of the #qapi_BLE_HCI_Event_Data_t structure. */
#define QAPI_BLE_HCI_EVENT_DATA_SIZE                                                (sizeof(qapi_BLE_HCI_Event_Data_t))

/**
 * @brief
 * This declared type represents the Prototype Function for
 * an HCI Event Receive Data Callback. This function will be called
 * whenever a complete HCI Event Packet has been received by the HCI
 * Layer that is associated with the specified Bluetooth Stack ID.
 *
 * @details
 * The caller should use the contents of the HCI Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (that is, this
 * function does not have be reentrant). It should be noted however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another HCI Event Packet will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving HCI Event Packets. A Deadlock will occur
 * because no HCI Event Receive callbacks will be issued while this
 * function is currently outstanding.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  HCI_Event_Data      Structure that contains a union
 *                                 of all event data structures
 *                                 possible.
 *
 * @param[in]  CallbackParameter   User-defined parameter (e.g.,
 *                                 tag value) that was defined in
 *                                 the callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_HCI_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * This declared type represents the Prototype Function for
 * an ACL Data Receive Data Callback. This function will be called
 * whenever a complete ACL Data Packet has been received by the HCI
 * Layer that is associated with the specified Bluetooth Stack ID.
 *
 * @details
 * The caller should use the contents of the ACL Data Contents
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
 * anyway because another ACL Data Packet will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving HCI Event Packets. A Deadlock will occur
 * because no HCI Event Receive callbacks will be issued while this
 * function is outstanding.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Connection_Handle   Unique identifier for the connection
 *                                 returned in a Connection Complete
 *                                 event.
 *
 * @param[in]  Flags               ACL Packet Flags.
 *
 * @param[in]  ACLDataLength       Number of octets returned in the
 *                                 array pointed to by ACLData.
 *
 * @param[in]  ACLData             Pointer to the ACL data.
 *
 * @param[in]  CallbackParameter   User-defined parameter (e.g.,
 *                                 tag value) that was defined in
 *                                 the callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_HCI_ACL_Data_Callback_t)(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Flags, uint16_t ACLDataLength, uint8_t *ACLData, unsigned long CallbackParameter);

   /* HCI API's. */

/**
 * @brief
 * Provides a simple mechanism
 * for determining the HCI version that is supported by the HCI API
 * Layer present for the specified Bluetooth Protocol Stack.
 *
 * @details-paragraph
 * Call this function to determine the supported HCI Specification Version.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  HCI_Version         Returned enumerated type, where
 *                                  higher levels of the Bluetooth
 *                                  specification revisions are assured
 *                                  of having a higher ordinal value
 *                                  in the enumeration.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Version_Supported(uint32_t BluetoothStackID, qapi_BLE_HCI_Version_t *HCI_Version);

/**
 * @brief
 * Provides a simple mechanism
 * for determining if a specific HCI function is supported by the HCI
 * API Layer present for the specified Bluetooth Protocol Stack.
 *
 * @details-paragraph
 * Call this function to determine if a specified HCI command is
 * supported by the local Bluetooth device.
 *
 * The final parameter to this function should be a constant from
 * qapi_ble_hcitypes.h for the supported HCI Commands (that is, of
 * the format QAPI_BLE_HCI_SUPPORTED_COMMAND_XXX_BIT_NUMBER,
 * where XXX varies depending on the command being tested).
 *
 * @param[in]  BluetoothStackID            Unique identifier assigned to this
 *                                         Bluetooth Protocol Stack via a
 *                                         call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  SupportedCommandBitNumber   Supported HCI Command bit number
 *                                         (defined in HCITypes.h) for the
 *                                         specified HCI command that is to
 *                                         be tested.
 *
 * @return
 * Positive, nonzero value -- If the HCI command is supported.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Command_Supported(uint32_t BluetoothStackID, uint32_t SupportedCommandBitNumber);

/**
 * @brief
 * Registers the specified
 * HCI Event Callback Function with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * The HCI_EventCallback parameter is a pointer to the Callback
 * Function and is not optional.
 *
 * On success, this return value can be used as an argument to
 * qapi_BLE_HCI_Un_Register_Callback() to remove the Registered Callback
 * from the associated Bluetooth Stack.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  HCI_EventCallback   User-supplied callback function.
 *
 * @param[in]  CallbackParameter   User-defined parameter (e.g.,
 *                                 a tag value) that will be passed
 *                                 back to the user in the callback
 *                                 function with each packet.
 *
 * @return
 * Positive, nonzero value -- If successful. This is the
 *              CallbackID which is used to unregister the callback.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_EVENT_CALLBACK
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Register_Event_Callback(uint32_t BluetoothStackID, qapi_BLE_HCI_Event_Callback_t HCI_EventCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Registers the specified
 * HCI ACL Data Callback Function with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * The HCI_ACLDataCallback parameter is a pointer to the Callback
 * Function and is not optional.
 *
 * Upon success, this return value can be used as an argument to
 * qapi_BLE_HCI_Un_Register_Callback() to remove the Registered Callback
 * from the associated Bluetooth Stack.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  HCI_ACLDataCallback   User-supplied callback function.
 *
 * @param[in]  CallbackParameter     User-defined parameter (e.g.,
 *                                   a tag value) that will be passed
 *                                   back to the user in the callback
 *                                   function with each packet.
 *
 * @return
 * Positive, nonzero value -- If successful. This is the
 *              CallbackID which is used to unregister the callback.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_EVENT_CALLBACK
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Register_ACL_Data_Callback(uint32_t BluetoothStackID, qapi_BLE_HCI_ACL_Data_Callback_t HCI_ACLDataCallback, unsigned long CallbackParameter);

/**
 * @brief
 * Removes a previously
 * installed HCI callback (either HCI Event, HCI ACL Data, or HCI SCO
 * Data) for the Bluetooth Protocol Stack specified by the BluetoothStackID
 * parameter.
 *
 * @details
 * The CallbackID parameter is  obtained via a successful call to either the
 * qapi_BLE_HCI_Register_Event_Callback() function, or the
 * qapi_BLE_HCI_Register_ACL_Data_Callback() function.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this
 *                                Bluetooth Protocol Stack via a
 *                                call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CallbackID         Identifier assigned via one of the
 *                                callback registration functions.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Un_Register_Callback(uint32_t BluetoothStackID, uint32_t CallbackID);

/**
 * @brief
 * Sends HCI ACL Packets to
 * the Bluetooth device specifed by the BluetoothStackID Parameter.
 *
 * @details
 * This function will format an HCI ACL Data Packet in the correct
 * format and submit it to the Bluetooth device that is specified.
 *
 * The caller is not responsible for submitting an HCI ACL Data Packet.
 *
 * Possible values for the Flags parameter are:
 *
 * <b>Bluetooth Version 1.1</b>
 *
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_CONTINUE_PACKET \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET_AUTO_FLUSHABLE
 *
 * <b>Bluetooth Version 2.1</b>
 *
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_FIRST_PACKET_NON_FLUSHABLE \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BOUNDARY_COMPLETE_L2CAP_PDU_AUTO_FLUSHABLE
 *
 * **These definitions are for Packets from Host to Host Controller.**
 *
 * <b>Bluetooth Version 1.1</b>
 *
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_NO_BROADCAST \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_BROADCAST \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PICONET_BROADCAST
 *
 * <b>Bluetooth Version 1.2</b>
 *
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_SLAVE_BROADCAST \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PARKED_SLAVE_BROADCAST
 *
 * **These definitions are for Packets from Host Controller to Host.**
 *
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_POINT_TO_POINT \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_ACTIVE_SLAVE \n
 *    QAPI_BLE_HCI_ACL_FLAGS_PACKET_BROADCAST_PARKED_SLAVE
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Connection_Handle   Unique identifier for the connection
 *                                 returned in a Connection Complete
 *                                 event.
 *
 * @param[in]  Flags               Used along with the Connection_Handle
 *                                 to define the header of the HCI ACL
 *                                 Data Packet.
 *
 * @param[in]  ACLDataLength       The length of data pointed to by
 *                                 ACLData.
 *
 * @param[in]  ACLData             Pointer to the ACL data to be sent.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Send_ACL_Data(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Flags, uint16_t ACLDataLength, uint8_t *ACLData);

   /* HCI Command API's (Generic). */

/**
 * @brief
 * Issues a Raw HCI Command to the Bluetooth
 * Device that is associated with the Bluetooth Protocol Stack specified
 * by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]       BluetoothStackID   Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]       Command_OGF        Opcode Group Field value; the upper
 *                                     6 bits of the opcode field (e.g.,
 *                                     0x01 for Link Control commands).
 *
 * @param[in]       Command_OCF        Opcode Command Field value;
 *                                     the lower 10 bits of the opcode.
 *
 * @param[in]       Command_Length     Length of the valid data in
 *                                     Command_Data.
 *
 * @param[in]       Command_Data       Array of bytes that make up the
 *                                     command.
 *
 * @param[out]      StatusResult       Pointer to a byte to receive a
 *                                     returned status.
 *
 * @param[in,out]   LengthResult       This parameter is both an input
 *                                     and output parameter. On input,
 *                                     this parameter should contain the
 *                                     total length (in bytes) of the
 *                                     buffer that is pointed to by the
 *                                     BufferResult parameter. On
 *                                     successful return from this
 *                                     function, this will contain the
 *                                     length of the valid data returned
 *                                     in the BufferResult.
 *
 * @param[out]      BufferResult       Pointer to an array of bytes for
 *                                     the command result.
 *
 * @param[in]       WaitForResponse    TRUE if the function should wait
 *                                     for the result, FALSE otherwise.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Send_Raw_Command(uint32_t BluetoothStackID, uint8_t Command_OGF, uint16_t Command_OCF, uint8_t Command_Length, uint8_t Command_Data[], uint8_t *StatusResult, uint8_t *LengthResult, uint8_t *BufferResult, boolean_t WaitForResponse);

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief
 * Issues the appropriate call to an HCI driver
 * to perform a reconfiguration operation with the specified
 * reconfiguration information.
 *
 * @note1hang
 * This function should only be used if the caller has explicit
 * knowledge of the reconfiguration process being requested.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ResetStateMachines      Flag that is passed to the drivers
 *                                     that specify whether the HCI driver
 *                                     internal state machines (for example,
 *                                     BCSP and/or packet building state
 *                                     machines) should be reset (TRUE)
 *                                     or not (FALSE).
 *
 * @param[in]  DriverReconfigureData   HCI Driver Reconfiguration
 *                                     information.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Reconfigure_Driver(uint32_t BluetoothStackID, boolean_t ResetStateMachines, qapi_BLE_HCI_Driver_Reconfigure_Data_t *DriverReconfigureData);

/**
 * @brief
 * Enables and disabels the
 * handling of Controller to Host Flow Control by this module.
 *
 * @details
 * Once this function is called to enable Controller to Host Flow
 * Control, all the handling of this mechanism will be handled
 * internally.
 *
 * The final two parameters to this function specify the Number of ACL
 * and SCO Data Packets that the Controller can send to the Host without
 * the Host sending credits back to the controller.
 *
 * If the NumberOfACLPackets and NumberOfSCOPackets are both set to
 * zero, the Controller to Host Flow Control will be disabled.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  NumberOfACLPackets   Number of ACL packets the
 *                                  Controller can send to the Host
 *                                  without receiving credits back.
 *
 * @param[in]  NumberOfSCOPackets   Number of SCO packets the
 *                                  Controller can send to the Host
 *                                  without receiving credits back.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_Host_Flow_Control(uint32_t BluetoothStackID, uint16_t NumberOfACLPackets, uint16_t NumberOfSCOPackets);

/**
 * @brief
 * Queries the Controller to
 * Host Flow Control Configuration of this Module.
 *
 * @details
 * The final two parameters to this function specify pointers to return
 * the Number of ACL and SCO Data Packets that the Controller can send
 * to the Host without the Host sending credits back to the controller.
 *
 * The NumberOfSCOPackets parameter will always be set to zero on a
 * successfull call to this function.
 *
 * If NumberOfACLPackets is set to zero on a successfull call to this
 * function, then Controller to Host Flow Control will be disabled.
 *
 * @param[in]   BluetoothStackID     Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  NumberOfACLPackets   Pointer to return the number of
 *                                   ACL packets the Controller can
 *                                   send to the Host without receiving
 *                                   credits back.
 *
 * @param[out]  NumberOfSCOPackets   Pointer to return the number of
 *                                   SCO packets the Controller can
 *                                   send to the Host without
 *                                   receiving credits back.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Query_Host_Flow_Control(uint32_t BluetoothStackID, uint16_t *NumberOfACLPackets, uint16_t *NumberOfSCOPackets);

   /* HCI Command API's (Link Control). */

/**
 * @brief
 * Issues the HCI_Disconnect Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a
 * response from the Bluetooth device.
 *
 * The possible values for the Reason parameter may be:
 *
 *   QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_USER_ENDED \n
 *   QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_LOW_RESOURCES \n
 *   QAPI_BLE_HCI_ERROR_CODE_OTHER_END_TERMINATED_CONNECTION_ABOUT_TO_PWR_OFF \n
 *   QAPI_BLE_HCI_ERROR_CODE_UNSUPPORTED_REMOTE_FEATURE
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Unique identifier for the
 *                                  connection returned in a Connection
 *                                  Complete event.
 *
 * @param[in]   Reason              Reason for ending the connection.
 *                                  Subset of HCI Status Codes.
 *
 * @param[out]  StatusResult        Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Disconnect(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Reason, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Read_Remote_Version_Information
 * command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Unique identifier for the
 *                                  connection returned in a Connection
 *                                  Complete event.
 *
 * @param[out]  StatusResult        Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Remote_Version_Information(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult);

   /* HCI Command API's (Host Controller and Baseband). */

/**
 * @brief
 * Issues the HCI_Set_Event_Mask Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * The Event_Mask (bitmask) is constructed via the following API
 * macros:
 *
 *   QAPI_BLE_SET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_RESET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_TEST_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_HCI_ENABLE_ALL_HCI_EVENTS_IN_EVENT_MASK(Mask) \n
 *   QAPI_BLE_HCI_DISABLE_ALL_HCI_EVENTS_IN_EVENT_MASK(Mask)
 *
 * **The bit number constants defined in the API for use with these macros are:**
 *
 * <b>Bluetooth Version 1.1</b>
 *
 *    QAPI_BLE_HCI_EVENT_MASK_INQUIRY_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_CONNECTION_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_CONNECTION_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_AUTHENTICAITION_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_REMOTE_NAME_REQUEST_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_CHANGE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_CHANGE_CONNECTION_LINK_KEY_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_MASTER_LINK_KEY_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_VERSION_INFORMATION_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_QOS_SETUP_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_COMMAND_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_STATUS_COMMAND_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_HARDWARE_ERROR_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_FLUSH_OCCURRED_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_ROLE_CHANGE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_PACKETS_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_MODE_CHANGE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_RETURN_LINK_KEYS_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_PIN_CODE_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_LINK_KEY_NOTIFICATION_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_LOOPBACK_COMMAND_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_DATA_BUFFER_OVERFLOW_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_MAX_SLOTS_CHANGE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_READ_CLOCK_OFFSET_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_CONNECTION_PACKET_TYPE_CHANGED_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_QOS_VIOLATION_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_MODE_CHANGE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_PAGE_SCAN_REPETITION_MODE_CHANGE_BIT_NUMBER
 *
 * <b>Bluetooth Version 1.2</b>
 *
 *    QAPI_BLE_HCI_EVENT_MASK_FLOW_SPECIFICATION_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_INQUIRY_RESULT_WITH_RSSI_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_SYNCHRONOUS_CONNECTION_CHANGED_BIT_NUMBER
 *
 * <b>Bluetooth Version 2.1</b>
 *
 *    QAPI_BLE_HCI_EVENT_MASK_SNIFF_SUBRATING_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_EXTENDED_INQUIRY_RESULT_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_ENCRYPTION_REFRESH_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_IO_CAPABILITY_REQUEST_REPLY_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_USER_CONFIRMATION_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_REMOTE_OOB_DATA_REQUEST_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_SIMPLE_PAIRING_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_LINK_SUPERVISION_TIMEOUT_CHANGED_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_ENHANCED_FLUSH_COMPLETE_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_USER_PASSKEY_NOTIFICATION_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_USER_KEYPRESS_NOTIFICATION_BIT_NUMBER \n
 *    QAPI_BLE_HCI_EVENT_MASK_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_ \n
 *    QAPI_BLE_BIT_NUMBER
 *
 * <b>Bluetooth Version 4.0</b>
 *
 *    QAPI_BLE_HCI_EVENT_MASK_LE_META_BIT_NUMBER
 *
 * In addition, to aid in quickly enabling all events, the API provides
 * the following macro that enables all events:
 *
 *    QAPI_BLE_HCI_ENABLE_ALL_HCI_EVENTS_IN_EVENT_MASK(Mask)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Event_Mask         Event mask to set for the Host.
 *                                 See above for possible values.
 *
 * @param[out]  StatusResult       Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_Event_Mask(uint32_t BluetoothStackID, qapi_BLE_Event_Mask_t Event_Mask, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Reset Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack specified
 * by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_VS_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Reset(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Read_Transmit_Power_Level Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * The possible values for the Type parameter are:
 *
 *   QAPI_BLE_HCI_TRANSMIT_POWER_LEVEL_TYPE_CURRENT \n
 *   QAPI_BLE_HCI_TRANSMIT_POWER_LEVEL_TYPE_MAXIMUM
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle            Unique identifier for the connection
 *                                           returned in a Connection Complete
 *                                           event.
 *
 * @param[in]   Type                         Flag to indicate whether to read the
 *                                           current or maximum power level.
 *
 * @param[out]  StatusResult                 Returned HCI status code.
 *
 * @param[out]  Connection_HandleResult      Unique identifier for the connection
 *                                           handle for which the operation was
 *                                           done.
 *
 * @param[out]  Transmit_Power_LevelResult   The current/maximum power level
 *                                           in the range of -30 dBm to +20
 *                                           dBm.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Transmit_Power_Level(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Type, uint8_t *StatusResult, uint16_t *Connection_HandleResult, int8_t *Transmit_Power_LevelResult);

/**
 * @brief
 * Issues the HCI_Set_Event_Mask_Page_2 command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * The purpose of this command is to control which events are generated
 * by the HCI for the host.
 *
 * <b>The Event_Mask (bitmask) is constructed via the following API
 * macros:</b>
 *
 *   QAPI_BLE_SET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_RESET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_TEST_EVENT_MASK_BIT(Mask, BitNumber) \n
 *   QAPI_BLE_HCI_ENABLE_ALL_HCI_EVENTS_IN_EVENT_MASK_PAGE_2(Mask) \n
 *   QAPI_BLE_HCI_DISABLE_ALL_HCI_EVENTS_IN_EVENT_MASK_PAGE_2(Mask)
 *
 * <b>The bit number constants defined in the API for use with these macros
 * are:</b>
 *
 *   QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_CHANNEL_SELECTED_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_PHYSICAL_LINK_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_LOSS_EARLY_WARNING_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_PHYSICAL_LINK_RECOVERY_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_LOGICAL_LINK_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_DISCONNECTION_LOGICAL_LINK_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_FLOW_SPEC_MODIFY_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_NUMBER_OF_COMPLETED_DATA_BLOCKS_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_AMP_START_TEST_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_AMP_TEST_END_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_AMP_RECEIVER_REPORT_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_SHORT_RANGE_MODE_CHANGE_COMPLETE_BIT_NUMBER \n
 *   QAPI_BLE_HCI_EVENT_MASK_AMP_STATUS_CHANGE_BIT_NUMBER
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Event_Mask         Event mask to set for the Host.
 *                                 See above for possible values.
 *
 * @param[out]  StatusResult       Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_Event_Mask_Page_2(uint32_t BluetoothStackID, qapi_BLE_Event_Mask_t Event_Mask, uint8_t *StatusResult);

   /* HCI Command API's (Host Controller and Baseband - Version 4.0 + */
   /* CSA3). */

/**
 * @brief
 * Issues the HCI_Set_MWS_Channel_Parameters
 * command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * The possible values for the MWS_Channel_Enable parameter are:
 *
 *   QAPI_BLE_HCI_MWS_CHANNEL_ENABLE_CHANNEL_DISABLE \n
 *   QAPI_BLE_HCI_MWS_CHANNEL_ENABLE_CHANNEL_ENABLED
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID           Unique identifier assigned to this
 *                                         Bluetooth Protocol Stack via a
 *                                         call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   MWS_Channel_Enable         Used to set the LE supported feature
 *                                         bit on the host device. See above for
 *                                         possible values.
 *
 * @param[in]   MWS_RX_Center_Frequency    Used to indicate the center frequency
 *                                         of the MWS device's uplink (TX) and
 *                                         downlink (RX) channels.
 *
 * @param[in]   MWS_TX_Center_Frequency    Used to indicate the center frequency
 *                                         of the MWS device's uplink (TX) and
 *                                         downlink (RX) channels.
 *
 * @param[in]   MWS_RX_Channel_Bandwidth   Used to indicate the bandwidth, in
 *                                         kHz, of the MWS device's uplink and
 *                                         downlink channels.
 *
 * @param[in]   MWS_TX_Channel_Bandwidth   Used to indicate the bandwidth, in
 *                                         kHz, of the MWS device's uplink
 *                                         and downlink channels.
 *
 * @param[in]   MWS_Channel_Type           Describes the type of channel.
 *
 * @param[out]  StatusResult               Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_MWS_Channel_Parameters(uint32_t BluetoothStackID, uint8_t MWS_Channel_Enable, uint16_t MWS_RX_Center_Frequency, uint16_t MWS_TX_Center_Frequency, uint16_t MWS_RX_Channel_Bandwidth, uint16_t MWS_TX_Channel_Bandwidth, uint8_t MWS_Channel_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Set_External_Frame_Configuration
 * command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter followed
 * by the Host supported LE parameters.
 *
 * @details
 * The possible values for the Period_Type parameter are:
 *
 *    QAPI_BLE_HCI_MWS_PERIOD_TYPE_DOWNLINK \n
 *    QAPI_BLE_HCI_MWS_PERIOD_TYPE_UPLINK \n
 *    QAPI_BLE_HCI_MWS_PERIOD_TYPE_BIDIRECTIONAL \n
 *    QAPI_BLE_HCI_MWS_PERIOD_TYPE_GUARD_PERIOD
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * Both Period_Duration and Period_Type must be arrays of
 * Ext_Num_Periods entries.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned to this
 *                                             Bluetooth Protocol Stack via a
 *                                             call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Ext_Frame_Duration             Sum of all Period_Duration[i]
 *                                             parameters shall be equal to the
 *                                             Ext_Frame_Duration parameter.
 *
 * @param[in]   Ext_Frame_Sync_Assert_Offset   Start of the external frame
 *                                             structure is defined as an offset
 *                                             from an external frame
 *                                             synchronization signal. This offset
 *                                             is defined by the
 *                                             Ext_Frame_Sync_Assert_Offset parameter.
 *
 * @param[in]   Ext_Frame_Sync_Assert_Jitter   External frame sync jitter in
 *                                             microseconds.
 *
 * @param[in]   Ext_Num_Periods                Has arrays of Period_Duration and
 *                                             Period_Type.
 *
 * @param[in]   Period_Duration                Array of Ext_Num_Periods.
 *
 * @param[in]   Period_Type                    Array of Ext_Num_Periods. See above
 *                                             for possible values.
 *
 * @param[out]  StatusResult                   Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_External_Frame_Configuration(uint32_t BluetoothStackID, uint16_t Ext_Frame_Duration, uint16_t Ext_Frame_Sync_Assert_Offset, uint16_t Ext_Frame_Sync_Assert_Jitter, uint8_t Ext_Num_Periods, uint16_t *Period_Duration, uint8_t *Period_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Set_MWS_Signaling command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned to this
 *                                             Bluetooth Protocol Stack via a
 *                                             call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Set_MWS_Signaling_Parameters   Will contain parameters for
 *                                             MWS_Signaling.
 *
 * @param[out]  StatusResult                   Returned HCI status code.
 *
 * @param[out]  Set_MWS_Signaling_Result       Will contain the return values
 *                                             returned from the Bluetooth
 *                                             device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_MWS_Signaling(uint32_t BluetoothStackID, qapi_BLE_HCI_Set_MWS_Signaling_Parameters_t *Set_MWS_Signaling_Parameters, uint8_t *StatusResult, qapi_BLE_HCI_Set_MWS_Signaling_Result_t *Set_MWS_Signaling_Result);

/**
 * @brief
 * Issues the HCI_Set_MWS_Transport_Layer command
 * to the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID     Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Transport_Layer      Layer through which commands are sent.
 *
 * @param[in]   To_MWS_Baud_Rate     Baud rate in the Bluetooth to MWS
 *                                   direction in Baud.
 *
 * @param[in]   From_MWS_Baud_Rate   Baud rate in the MWS to Bluetooth
 *                                   direction in Baud.
 *
 * @param[out]  StatusResult         Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_MWS_Transport_Layer(uint32_t BluetoothStackID, uint8_t Transport_Layer, uint32_t To_MWS_Baud_Rate, uint32_t From_MWS_Baud_Rate, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Set_MWS_Scan_Frequency_Table
 * command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * Both Scan_Frequency_Low and Scan_Frequency_High are arrays of
 * Num_Scan_Frequencies entries.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Num_Scan_Frequencies   Both Scan_Frequency_Low and
 *                                     Scan_Frequency_High are arrays
 *                                     of Num_Scan_Frequencies entries.
 *
 * @param[in]   Scan_Frequency_Low     Array of Num_Scan_Frequencies.
 *
 * @param[in]   Scan_Frequency_High    Array of Num_Scan_Frequencies.
 *
 * @param[out]  StatusResult           Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_MWS_Scan_Frequency_Table(uint32_t BluetoothStackID, uint8_t Num_Scan_Frequencies, uint16_t *Scan_Frequency_Low, uint16_t *Scan_Frequency_High, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_Set_MWS_PATTERN_Configuration
 * command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * Possible values for the MWS_PATTERN_IntervalType are:
 *
 *    QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_RX_NOT_ALLOWED \n
 *    QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_ALLOWED \n
 *    QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_RX_ALLOWED \n
 *    QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_TX_RX_ALLOWED \n
 *    QAPI_BLE_HCI_MWS_PATTERN_INTERVAL_TYPE_INTERVAL_FOR_MWS_FRAME
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * Both MWS_PATTERN_IntervalDuration and MWS_PATTERN_IntervalType are
 * arrays of MWS_PATTERN_NumIntervals entries.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned to this
 *                                             Bluetooth Protocol Stack via a
 *                                             call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   MWS_PATTERN_Index              Index of the MWS_PATTERN instance to
 *                                             be configured.Range is 0-2.
 *
 * @param[in]   MWS_PATTERN_NumIntervals       Both MWS_PATTERN_IntervalDuration
 *                                             and MWS_PATTERN_IntervalType are
 *                                             arrays of MWS_PATTERN_NumIntervals entries.
 *
 * @param[in]   MWS_PATTERN_IntervalDuration   Array of MWS_PATTERN_NumIntervals.
 *
 * @param[in]   MWS_PATTERN_IntervalType       Defines the interval type. See above
 *                                             for possible values.
 *
 * @param[out]  StatusResult                   Returned HCI status code.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Set_MWS_PATTERN_Configuration(uint32_t BluetoothStackID, uint8_t MWS_PATTERN_Index, uint8_t MWS_PATTERN_NumIntervals, uint16_t *MWS_PATTERN_IntervalDuration, uint8_t *MWS_PATTERN_IntervalType, uint8_t *StatusResult);

   /* HCI Command API's (Host Controller and Baseband - Version 4.1). */

/**
 * @brief
 * Issues the HCI_Read_Authenticated_Payload_Timeout
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID                      Unique identifier assigned to this
 *                                                    Bluetooth Protocol Stack via a
 *                                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle                     Returned from the Bluetooth device.
 *
 * @param[out]  StatusResult                          Returned HCI status code.
 *
 * @param[out]  Connection_HandleResult               Will contain the Connection Handle
 *                                                    returned from the Bluetooth device.
 *
 * @param[out]  Authenticated_Payload_TimeoutResult   Will contain the Authenticated
 *                                                    Payload Timeout returned from
 *                                                    the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult, uint16_t *Connection_HandleResult, uint16_t *Authenticated_Payload_TimeoutResult);

/**
 * @brief
 * Issues the
 * HCI_Write_Authenticated_Payload_Timeout Command to the Bluetooth device
 * that is associated with the Bluetooth Protocol Stack specified by the
 * BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID                Unique identifier assigned to this
 *                                              Bluetooth Protocol Stack via a
 *                                              call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle               Returned from the Bluetooth device.
 *
 * @param[in]   Authenticated_Payload_Timeout   Returned from the Bluetooth device.
 *
 * @param[out]  StatusResult                    Returned HCI status code.
 *
 * @param[out]  Connection_HandleResult         Will contain the Connection Handle
 *                                              returned from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Write_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Authenticated_Payload_Timeout, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

   /* HCI Command API's (Informational Parameters). */

/**
 * @brief
 * Issues the HCI_Read_Local_Version_Information
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * <b>Possible values for the HCI_VersionResult parameter are:</b>
 *
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_1_0B \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_1_1 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_1_2 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_2_0 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_2_1 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_3_0 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_4_0 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_4_1 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_4_2 \n
 *    QAPI_BLE_HCI_VERSION_SPECIFICATION_5_0
 *
 * <b>Possible values for the LMP_VersionResult parameter are:</b>
 *
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_0 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_1 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_1_2 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_2_0 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_2_1 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_3_0 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_0 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_1 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_4_2 \n
 *    QAPI_BLE_HCI_LMP_VERSION_BLUETOOTH_5_0
 *
 * Possible values for the Manufacturer_NameResult can be found
 * in qapi_ble_hcitypes.h since there are too many to list here.
 * These values have the form
 * QAPI_BLE_HCI_LMP_COMPID_MANUFACTURER_NAME_XXX, where 'XXX'
 * indicates the name of the manufacturer.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult              Returned HCI status code.
 *
 * @param[out]  HCI_VersionResult         Major version for the Bluetooth hardware.
 *                                        Corresponds to changes in the released
 *                                        specifications only. See above for
 *                                        possible values.
 *
 * @param[out]  HCI_RevisionResult        HCI revision number.
 *
 * @param[out]  LMP_VersionResult         Link Manager Protocol version number.
 *                                        See above for possible values.
 *
 * @param[out]  Manufacturer_NameResult   Manufacturer code. See above for possible
 *                                        values.
 *
 * @param[out]  LMP_SubversionResult      LMP subversion number. These are
 *                                        defined by each manufacturer.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Local_Version_Information(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *HCI_VersionResult, uint16_t *HCI_RevisionResult, uint8_t *LMP_VersionResult, uint16_t *Manufacturer_NameResult, uint16_t *LMP_SubversionResult);

/**
 * @brief
 * Issues the HCI_Read_Local_Supported_Features
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * Possible values for the LMP_FeaturesResult can be found
 * in qapi_ble_hcitypes.h since there are too many to list here.
 * These values have the form
 * QAPI_BLE_HCI_LMP_FEATURE_XXX, where 'XXX'
 * indicates the feature.
 *
 * Useful macros defined for manipulation of LMP Features are:
 *
 *    QAPI_BLE_COMPARE_LMP_FEATURES( feats1, feats2) \n
 *    QAPI_BLE_ASSIGN_LMP_FEATURES( feats, MSByte, ... LSByte) \n
 *    QAPI_BLE_SET_FEATURES_BIT( feats, bitnum) \n
 *    QAPI_BLE_RESET_FEATURES_BIT( feats, bitnum) \n
 *    QAPI_BLE_TEST_FEATURES_BIT( feats, bitnum)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID     Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult         Returned HCI status code.
 *
 * @param[out]  LMP_FeaturesResult   Bitmask list of supported features
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Local_Supported_Features(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_LMP_Features_t *LMP_FeaturesResult);

/**
 * @brief
 * Issues the HCI_Read_BD_ADDR Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       Returned HCI status code.
 *
 * @param[out]  BD_ADDRResult      The local device's address/identifier.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_BD_ADDR(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_BD_ADDR_t *BD_ADDRResult);

   /* HCI Command API's (Informational Parameters - Version 1.2). */

/**
 * @brief
 * Issues the HCI_Read_Local_Supported_Commands
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * Possible values for the Supported_CommandsResult can be found
 * in qapi_ble_hcitypes.h since there are too many to list here.
 * These values have the form
 * QAPI_BLE_HCI_SUPPORTED_COMMAND_XXX, where XXX
 * indicates the supported command.
 *
 * Useful macros defined for manipulation of Supported Commands are:
 *
 *    QAPI_BLE_COMPARE_SUPPORTED_COMMANDS( cmd1, cmd2) \n
 *    QAPI_BLE_SET_SUPPORTED_COMMANDS_BIT( cmd, bitnum) \n
 *    QAPI_BLE_RESET_SUPPORTED_COMMANDS_BIT( cmd, bitnum) \n
 *    QAPI_BLE_TEST_SUPPORTED_COMMANDS_BIT( cmd, bitnum)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID           Unique identifier assigned to this
 *                                         Bluetooth Protocol Stack via a
 *                                         call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult               Returned HCI status code.
 *
 * @param[out]  Supported_CommandsResult   Bitmask for each HCI supported
 *                                         command. See above for possible
 *                                         values.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_Local_Supported_Commands(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_Supported_Commands_t *Supported_CommandsResult);

   /* HCI Command API's (Status Parameters). */

/**
 * @brief
 * Issues the HCI_Read_RSSI Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Unique identifier for the connection
 *                                        returned in a Connection Complete
 *                                        event.
 *
 * @param[out]  StatusResult              Returned HCI status code.
 *
 * @param[out]  Connection_HandleResult   Unique identifier for the connection
 *                                        handle for which the operation was
 *                                        done.
 *
 * @param[out]  RSSIResult                Difference between the measured RSSI
 *                                        and the limits of the Golden Receive
 *                                        Power Range.  This value may range from
 *                                        -128 to +127 dB
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_RESPONSE_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Read_RSSI(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult, uint16_t *Connection_HandleResult, int8_t *RSSIResult);

   /* HCI Command API's (Status Parameters - Version 4.0 + CSA3). */

/**
 * @brief
 * Issues the
 * HCI_Get_MWS_Transport_Layer_Configuration Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack specified
 * by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @note1hang
 * The qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration() function
 * must be called after a successful return from this function to free
 * the memory allocated by this call. See below.
 *
 * @param[in]   BluetoothStackID                      Unique identifier assigned to this
 *                                                    Bluetooth Protocol Stack via a
 *                                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                          Returned HCI status code.
 *
 * @param[out]  Transport_Layer_ConfigurationResult   Will contain the Transport Layer 
 *                                                    Configuration retruned from the
 *                                                    Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *Transport_Layer_ConfigurationResult);

/**
 * @brief
 * Frees the memory allocated by a successful call
 * to the qapi_BLE_HCI_Get_MWS_Transport_Layer_Configuration() function.
 *
 * @details
 * None.
 *
 * @param[in]  Transport_Layer_Configuration   Will contain the Transport Layer
 *                                             Configuration returned from the
 *                                             Bluetooth device.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_HCI_Free_MWS_Transport_Layer_Configuration(qapi_BLE_HCI_MWS_Transport_Layer_Configuration_Info_t *Transport_Layer_Configuration);

   /* HCI Command API's (LE Commands - Version 4.0 + LE). */

/**
 * @brief
 * Issues the HCI_LE_Set_Event_Mask Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter followed by the LE Event
 * Mask to set.
 *
 * @details
 * This function is used to control which LE events are generated by
 * the controller for the host.
 *
 * The LE_Event_Mask (bitmask) is constructed via the following API
 * macros:
 *
 *    QAPI_BLE_SET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *    QAPI_BLE_RESET_EVENT_MASK_BIT(Mask, BitNumber) \n
 *    QAPI_BLE_TEST_EVENT_MASK_BIT(Mask, BitNumber) \n
 *    QAPI_BLE_HCI_ENABLE_ALL_LE_EVENTS_IN_EVENT_MASK(Mask) \n
 *    QAPI_BLE_HCI_DISABLE_ALL_LE_EVENTS_IN_EVENT_MASK(Mask)
 *
 * The bit number constants defined in the API for use with these
 * macros can be found in qapi_ble_hcitypes.h since there are too
 * many to list here. These values have the form
 * QAPI_BLE_HCI_LE_EVENT_MASK_XXX, where XXX indicates the LE
 * Event.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   LE_Event_Mask      Event mask to set for the Host.
 *                                 See above for possible values.
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Event_Mask(uint32_t BluetoothStackID, qapi_BLE_Event_Mask_t LE_Event_Mask, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Buffer_Size Command to
 * the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function returns the maximum size of the data field of an LE ACL
 * packet as well as the maximum number of packets the controller can
 * hold.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID                   Unique identifier assigned to this
 *                                                 Bluetooth Protocol Stack via a
 *                                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                       If the function returns zero (success),
 *                                                 this variable will contain the
 *                                                 Status Result returned from the
 *                                                 Bluetooth device.
 *
 * @param[out]  HC_LE_ACL_Data_Packet_Length       Contains the returned maximum length
 *                                                 of ACL data packet.
 *
 * @param[out]  HC_Total_Num_LE_ACL_Data_Packets   Contains the returned total number
 *                                                 of data packets the can be stored
 *                                                 in the buffers.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Buffer_Size(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *HC_LE_ACL_Data_Packet_Length, uint8_t *HC_Total_Num_LE_ACL_Data_Packets);

/**
 * @brief
 * Issues the HCI_LE_Read_Local_Supported_Features
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter
 *
 * @details
 * This function fetches a list of LE features that a device supports.
 *
 * Possible values for the LE_FeaturesResult parameter can be found
 * in qapi_ble_hcitypes.h since there are too many to list here.
 * These values have the form
 * QAPI_BLE_HCI_LE_FEATURE_LE_XXX, where XXX
 * indicates the supported LE feature.
 *
 * Useful macros defined for manipulation of LE Features are:
 *
 *    QAPI_BLE_COMPARE_LE_FEATURES( feats1, feats2) \n
 *    QAPI_BLE_ASSIGN_LE_FEATURES( feats, MSByte, ... LSByte) \n
 *    QAPI_BLE_SET_FEATURES_BIT( feats, bitnum) \n
 *    QAPI_BLE_RESET_FEATURES_BIT( feats, bitnum) \n
 *    QAPI_BLE_TEST_FEATURES_BIT( feats, bitnum)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero (success),
 *                                  this variable will contain the
 *                                  Status Result returned from the
 *                                  Bluetooth device.
 *
 * @param[out]  LE_FeaturesResult   Bitmask list of supported features.
 *                                  See above for possible values.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Local_Supported_Features(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_LE_Features_t *LE_FeaturesResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Random_Address Command
 * to the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR            Random address to use.
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Random_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Advertising_Parameters
 * to the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function allows the host to set the parameters that determine how
 * the controller advertises.
 *
 * The range for the Advertising_Interval_Min and Advertising_Interval_Max
 * parameters are:
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_INTERVAL_MINIMUM \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_INTERVAL_MAXIMUM
 *
 * Both intervals follow the rule:
 *
 *   Time = N * 0.625 ms
 *
 * <b>Possible values for the Advertising_Type parameter are:</b>
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_UNDIRECTED \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_DIRECTED \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_TYPE_SCANNABLE_UNDIRECTED \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_TYPE_NON_CONNECTABLE_UNDIRECTED
 *
 * <b>Bluetooth Version 4.1</b>
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_TYPE_CONNECTABLE_LOW_DUTY_CYCLE_DIRECTED
 *
 * <b>Possible values for the Own_Address_Type or Direct_Address_Type v4.0
 * (Deprecated for 4.2) parameters are:</b>
 *
 *    QAPI_BLE_HCI_LE_ADDRESS_TYPE_PUBLIC \n
 *    QAPI_BLE_HCI_LE_ADDRESS_TYPE_RANDOM
 *
 * <b>Bluetooth Version 4.2</b>
 *
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_PUBLIC \n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RANDOM \n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_PUBLIC \n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_RANDOM
 *
 * <b>Possible values for the Advertising_Channel_Map parameter are:</b>
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_37 \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_38 \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_39
 *
 * <b>Additionally, the following constant can be used to specify all Advertising
 * channels:</b>
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_ALL_CHANNELS
 *
 * <b>Possible values for the Advertising_Filter_Policy parameter are:</b>
 *
 *    QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_ANY_CONNECT_ANY \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_WHITE_LIST_CONNECT_ANY \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_ANY_CONNECT_WHITE_LIST \n
 *    QAPI_BLE_HCI_LE_ADVERTISING_FILTER_POLICY_SCAN_WHITE_LIST_CONNECT_WHITE_LIST
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID            Unique identifier assigned to this
 *                                          Bluetooth Protocol Stack via a
 *                                          call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Interval_Min    Mininum interval to advertise. Should
 *                                          be in terms of baseband slots
 *                                          (0.625 ms). See above for possible
 *                                          values.
 *
 * @param[in]   Advertising_Interval_Max    Should be greater than or equal to
 *                                          Advertising_Interval_Min, should be
 *                                          in terms of baseband slots
 *                                          (0.625 ms). See above for possible
 *                                          values.
 *
 * @param[in]   Advertising_Type            Type of advertising to use. See above
 *                                          for possible values.
 *
 * @param[in]   Own_Address_Type            Address type of local device's address.
 *                                          See above for possible values.
 *
 * @param[in]   Direct_Address_Type         Type of direct advertising to use.
 *                                          See above for possible values.
 *
 * @param[in]   Direct_Address              Address of directed device (if
 *                                          directed advertising).
 *
 * @param[in]   Advertising_Channel_Map     Indicates which advertising channels
 *                                          to use. See above for possible values.
 *
 * @param[in]   Advertising_Filter_Policy   Policy of which devices to allow requests
 *                                          from. See above for possible values.
 *
 * @param[out]  StatusResult                If the function returns zero (success),
 *                                          this variable will contain the
 *                                          Status Result returned from the
 *                                          Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Advertising_Parameters(uint32_t BluetoothStackID, uint16_t Advertising_Interval_Min, uint16_t Advertising_Interval_Max, uint8_t Advertising_Type, uint8_t Own_Address_Type, uint8_t Direct_Address_Type, qapi_BLE_BD_ADDR_t Direct_Address, uint8_t Advertising_Channel_Map, uint8_t Advertising_Filter_Policy, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Advertising_Channel_Tx_Power
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function allows the host to read the power level that is used for
 * the transmission of advertising packets.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                 If the function returns zero (success),
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @param[out]  Transmit_Power_LevelResult   Contains the returned transmit power
 *                                           level.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Advertising_Channel_Tx_Power(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *Transmit_Power_LevelResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Advertising_Data to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * Allows a device to set the data it transmits in advertising packets
 * that allows data.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Data_Length   Length of advertising data.
 *
 * @param[in]   Advertising_Data          Actual advertising data.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Advertising_Data(uint32_t BluetoothStackID, uint8_t Advertising_Data_Length, qapi_BLE_Advertising_Data_t *Advertising_Data, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Scan_Response_Data to
 * the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function allows a device to specify the data used in scanning
 * packet responses that allow data.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID            Unique identifier assigned to this
 *                                          Bluetooth Protocol Stack via a
 *                                          call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Scan_Response_Data_Length   Length of scan response data.
 *
 * @param[in]   Scan_Response_Data          Actual scan response data.
 *
 * @param[out]  StatusResult                If the function returns zero (success),
 *                                          this variable will contain the
 *                                          Status Result returned from the
 *                                          Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Scan_Response_Data(uint32_t BluetoothStackID, uint8_t Scan_Response_Data_Length, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Advertise_Enable to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID     Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Enable   Intended value to set. Possible values
 *                                   are: \n
 *                                   #QAPI_BLE_HCI_LE_ADVERTISING_DISABLE \n
 *                                   #QAPI_BLE_HCI_LE_ADVERTISING_ENABLE
 *
 * @param[out]  StatusResult         If the function returns zero (success),
 *                                   this variable will contain the
 *                                   Status Result returned from the
 *                                   Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Advertise_Enable(uint32_t BluetoothStackID, uint8_t Advertising_Enable, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Scan_Parameters to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * <b>Possible values for the Own_Address_Type v4.0 (Deprecated for
 * 4.2) parameters are:</b>
 *
 *    QAPI_BLE_HCI_LE_ADDRESS_TYPE_PUBLIC \n
 *    QAPI_BLE_HCI_LE_ADDRESS_TYPE_RANDOM
 *
 * <b>Bluetooth Version 4.2</b>
 *
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_PUBLIC \n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RANDOM \n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_PUBLIC\n
 *    QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_RANDOM
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID         Unique identifier assigned to this
 *                                       Bluetooth Protocol Stack via a
 *                                       call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   LE_Scan_Type             Type of scan to perform. Possible
 *                                       values are: \n
 *                                       #QAPI_BLE_HCI_LE_SCAN_TYPE_PASSIVE \n
 *                                       #QAPI_BLE_HCI_LE_SCAN_TYPE_ACTIVE
 *
 *
 * @param[in]   LE_Scan_Interval         Defined as number of baseband slots
 *                                       (0.625 ms). Should be within the
 *                                       range: \n
 *                                       #QAPI_BLE_HCI_LE_SCAN_INTERVAL_MINIMUM \n
 *                                       #QAPI_BLE_HCI_LE_SCAN_INTERVAL_MAXIMUM
 *
 * @param[in]   LE_Scan_Window           Value to set duration of an LE scan.
 *                                       Should be defined as the number of baseband
 *                                       slots (0.625 ms), less than or equal
 *                                       to scan window, and within the range
 *                                       as scan window. \n
 *                                       Both intervals follow the rule: \n
 *                                          Time = N * 0.625 ms
 *
 * @param[in]   Own_Address_Type         Address type of local device's address.
 *                                       See above for possible values.
 *
 * @param[in]   Scanning_Filter_Policy   Determines which advertising packets to
 *                                       accept. Possible values are: \n
 *                                       v4.0 \n
 *                                       #QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_ALL \n
 *                                       #QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_WHITE_LIST_ONLY \n
 *                                       v4.2 Added for Privacy 1.2 feature \n
 *                                       #QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_UNDIRECTED_DIRECTED_RPA \n
 *                                       #QAPI_BLE_HCI_LE_SCANNING_FILTER_POLICY_ACCEPT_WHITE_LIST_DIRECTED_RPA
 *
 * @param[out]  StatusResult             If the function returns zero (success),
 *                                       this variable will contain the
 *                                       Status Result returned from the
 *                                       Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Scan_Parameters(uint32_t BluetoothStackID, uint8_t LE_Scan_Type, uint16_t LE_Scan_Interval, uint16_t LE_Scan_Window, uint8_t Own_Address_Type, uint8_t Scanning_Filter_Policy, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Scan_Enable to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function allows a device to enable or disable scanning for
 * advertisering devices.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   LE_Scan_Enable      Enable or disable scanning. Possible
 *                                  values are: \n
 *                                  #QAPI_BLE_HCI_LE_SCAN_ENABLE \n
 *                                  #QAPI_BLE_HCI_LE_SCAN_DISABLE
 *
 * @param[in]   Filter_Duplicates   Specifies whether duplicate reports
 *                                  should be filtered out. Possible
 *                                  values are: \n
 *                                  #QAPI_BLE_HCI_LE_SCAN_FILTER_DUPLICATES_DISABLED \n
 *                                  #QAPI_BLE_HCI_LE_SCAN_FILTER_DUPLICATES_ENABLED
 *
 * @param[out]  StatusResult        If the function returns zero (success),
 *                                  this variable will contain the
 *                                  Status Result returned from the
 *                                  Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Scan_Enable(uint32_t BluetoothStackID, uint8_t LE_Scan_Enable, uint8_t Filter_Duplicates, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Create_Connection Command to
 * the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function allows a device to open a connection to a connectable
 * advertising device.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   LE_Scan_Interval          Defined as number of baseband slots
 *                                        (0.625 ms). Should be within the
 *                                        range: \n
 *                                        #QAPI_BLE_HCI_LE_SCAN_INTERVAL_MINIMUM \n
 *                                        #QAPI_BLE_HCI_LE_SCAN_INTERVAL_MAXIMUM
 *
 * @param[in]   LE_Scan_Window            Value to set duration of an LE scan.
 *                                        Should be defined as number of baseband
 *                                        slots (0.625 ms), less than or equal
 *                                        to scan window, and within the range
 *                                        as scan window. \n
 *                                        Both intervals follow the rule: \n
 *                                           Time = N * 0.625 ms
 *
 * @param[in]   Initiator_Filter_Policy   Determines whether to use a white list.
 *                                        Possible values are: \n
 *                                        #QAPI_BLE_HCI_LE_INITIATOR_FILTER_POLICY_WHITE_LIST_NOT_USED \n
 *                                        #QAPI_BLE_HCI_LE_INITIATOR_FILTER_POLICY_WHITE_LIST_IS_USED
 *
 * @param[in]   Peer_Address_Type         Type of peer address. Possible values
 *                                        are: \n
 *                                        v4.0 \n
 *                                          #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                          #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM
 *                                        v4.2 LE Enhanced 1.2 Privacy Feature \n
 *                                          #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY_ADDRESS \n
 *                                          #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_STATIC_RANDOM_IDENTITY_ADDRESS
 *
 * @param[in]   Peer_Address              Address of advertiser to connect if white
 *                                        list is not enabled.
 *
 * @param[in]   Own_Address_Type          Address type of local device's address.
 *                                        Possible values are: \n
 *                                        v4.0 \n
 *                                          #QAPI_BLE_HCI_LE_ADDRESS_TYPE_PUBLIC \n
 *                                          #QAPI_BLE_HCI_LE_ADDRESS_TYPE_RANDOM
 *                                        v4.2 \n
 *                                          #QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_PUBLIC \n
 *                                          #QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RANDOM \n
 *                                          #QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_PUBLIC \n
 *                                          #QAPI_BLE_HCI_LE_OWN_ADDRESS_TYPE_RPA_CONTROLLER_GENERATED_FALLBACK_RANDOM
 *
 * @param[in]   Conn_Interval_Min         Minimum value for the the connection
 *                                        interval. This should fall within
 *                                        the range: \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Interval_Max         Maximum value for the the connection
 *                                        interval. This should fall within
 *                                        the range: \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Latency              Slave latency for connection. This
 *                                        should be in range: \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MINIMUM \n
 *                                          QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MAXIMUM
 *
 * @param[in]   Supervision_Timeout       Supervision timeout for LE link.
 *                                        This should be in range: \n
 *                                          QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MINIMUM \n
 *                                          QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MAXIMUM \n
 *                                        The Supervision_Timeout follows the rule: \n
 *                                           Time = N * 10 ms
 *
 * @param[in]   Minimum_CE_Length         Information about minimum length
 *                                        of LE connection. This should
 *                                        be in range: \n
 *                                          #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                          #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                        The CE Length follows the rule: \n
 *                                           Time = N * 0.625 ms
 *
 * @param[in]   Maximum_CE_Length         Information about minimum length
 *                                        of LE connection. This should
 *                                        be in range: \n
 *                                          #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                          #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                        The CE Length follows the rule: \n
 *                                           Time = N * 0.625 ms
 *
 * @param[out]  StatusResult              If the function returns zero (success)
 *                                        this variable will contain the,
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Create_Connection(uint32_t BluetoothStackID, uint16_t LE_Scan_Interval, uint16_t LE_Scan_Window, uint8_t Initiator_Filter_Policy, uint8_t Peer_Address_Type, qapi_BLE_BD_ADDR_t Peer_Address, uint8_t Own_Address_Type, uint16_t Conn_Interval_Min, uint16_t Conn_Interval_Max, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint16_t Minimum_CE_Length, uint16_t Maximum_CE_Length, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Create_Connection_Cancel
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Create_Connection_Cancel(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_White_List_Size Command
 * to the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult            If the function returns zero (success),
 *                                      this variable will contain the
 *                                      Status Result returned from the
 *                                      Bluetooth device.
 *
 * @param[out]  White_List_SizeResult   Contains the returned size of the
 *                                      white list (specified in number
 *                                      of devices).
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_White_List_Size(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *White_List_SizeResult);

/**
 * @brief
 * Issues the HCI_LE_Clear_White_List Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Clear_White_List(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Add_Device_To_White_List
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Address_Type       Type of address being added. Possible
 *                                 values are: \n
 *                                 v4.0 \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM \n
 *                                 v4.2 LE Enhanced 1.2 Privacy Feature \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY_ADDRESS \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_STATIC_RANDOM_IDENTITY_ADDRESS
 *
 * @param[in]   Address            Address to of device to add to the
 *                                 white list.
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Add_Device_To_White_List(uint32_t BluetoothStackID, uint8_t Address_Type, qapi_BLE_BD_ADDR_t Address, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Remove_Device_From_White_List
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Address_Type       Type of address being added. Possible
 *                                 values are: \n
 *                                 v4.0 \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM \n
 *                                 v4.2 LE Enhanced 1.2 Privacy Feature \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC_IDENTITY_ADDRESS \n
 *                                    #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_STATIC_RANDOM_IDENTITY_ADDRESS
 *
 * @param[in]   Address            Address to of device to add to the
 *                                 white list.
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remove_Device_From_White_List(uint32_t BluetoothStackID, uint8_t Address_Type, qapi_BLE_BD_ADDR_t Address, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Connection_Update Command to
 * the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle     Handle to the connection desired
 *                                    to be updated.
 *
 * @param[in]   Conn_Interval_Min     Minimum value for the the connection
 *                                    interval. This should fall within
 *                                    the range: \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Interval_Max     Maximum value for the the connection
 *                                    interval. This should fall within
 *                                    the range: \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Latency          Slave latency for connection. This
 *                                    should be in range: \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MINIMUM \n
 *                                       QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MAXIMUM
 *
 * @param[in]   Supervision_Timeout   Supervision timeout for LE link.
 *                                    This should be in range: \n
 *                                       QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MINIMUM \n
 *                                       QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MAXIMUM \n
 *                                    The Supervision_Timeout follows the rule: \n
 *                                       Time = N * 10 ms
 *
 * @param[in]   Minimum_CE_Length     Information about minimum length
 *                                    of LE connection. This should
 *                                    be in range: \n
 *                                       #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                       #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                    The CE Length follows the rule: \n
 *                                       Time = N * 0.625 ms
 *
 * @param[in]   Maximum_CE_Length     Information about minimum length
 *                                    of LE connection. This should
 *                                    be in range: \n
 *                                       #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                       #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                    The CE Length follows the rule: \n
 *                                       Time = N * 0.625 ms
 *
 * @param[out]  StatusResult          If the function returns zero (success),
 *                                    this variable will contain the
 *                                    Status Result returned from the
 *                                    Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Connection_Update(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Conn_Interval_Min, uint16_t Conn_Interval_Max, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint16_t Minimum_CE_Length, uint16_t Maximum_CE_Length, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Host_Channel_Classification
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * Useful macros defined for manipulation of LE Channel Maps are:
 *
 *    QAPI_BLE_COMPARE_LE_CHANNEL_MAP(map1, map2) \n
 *    QAPI_BLE_ASSIGN_LE_CHANNEL_MAP(map, MSByte, ..., LSByte) \n
 *    QAPI_BLE_SET_LE_CHANNEL_MAP_CHANNEL(map, channum) \n
 *    QAPI_BLE_RESET_LE_CHANNEL_MAP_CHANNEL(map, channum) \n
 *    QAPI_BLE_TEST_LE_CHANNEL_MAP_CHANNEL(map, channum)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Channel_Map           New channel map to set. It is
 *                                    a 37-bit field where the nth bit
 *                                    represents channel index n. A
 *                                    value of 0 represents the channel
 *                                    is bad (not used). A value of 1
 *                                    represents the channel is unkown.
 *                                    At least one channel should be
 *                                    marked as unknown.
 *
 * @param[out]  StatusResult          If the function returns zero (success),
 *                                    this variable will contain the
 *                                    Status Result returned from the
 *                                    Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Host_Channel_Classification(uint32_t BluetoothStackID, qapi_BLE_LE_Channel_Map_t Channel_Map, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Channel_Map Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * Useful macros defined for manipulation of LE Channel Maps are:
 *
 *    QAPI_BLE_COMPARE_LE_CHANNEL_MAP(map1, map2) \n
 *    QAPI_BLE_ASSIGN_LE_CHANNEL_MAP(map, MSByte, ..., LSByte) \n
 *    QAPI_BLE_SET_LE_CHANNEL_MAP_CHANNEL(map, channum) \n
 *    QAPI_BLE_RESET_LE_CHANNEL_MAP_CHANNEL(map, channum) \n
 *    QAPI_BLE_TEST_LE_CHANNEL_MAP_CHANNEL(map, channum)
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle that identifies the desired
 *                                        connection.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Connection handle returned from
 *                                        Bluetooth device.
 *
 * @param[out]  Channel_MapResult         Returned channel map. It is a
 *                                        37-bit field where the nth bit
 *                                        represents channel index n.
 *                                        A value of 0 represents the
 *                                        channel is bad (not used).
 *                                        A value of 1 represents the
 *                                        channel is unknown.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Channel_Map(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult, uint16_t *Connection_HandleResult, qapi_BLE_LE_Channel_Map_t *Channel_MapResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Remote_Used_Features
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Handle that identifies the intended
 *                                  connection.
 *
 * @param[out]  StatusResult        If the function returns zero (success),
 *                                  this variable will contain the
 *                                  Status Result returned from the
 *                                  Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Remote_Used_Features(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Encrypt Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Key                    128-bit encryption key.
 *
 * @param[in]   Plain_Text_Data        128-bit data block to be encrypted.
 *
 * @param[out]  StatusResult           If the function returns zero (success),
 *                                     this variable will contain the
 *                                     Status Result returned from the
 *                                     Bluetooth device.
 *
 * @param[out]  Encrypted_DataResult   128-bit encrypted data block.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Encrypt(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t Key, qapi_BLE_Plain_Text_Data_t Plain_Text_Data, uint8_t *StatusResult, qapi_BLE_Encrypted_Data_t *Encrypted_DataResult);

/**
 * @brief
 * Issues the HCI_LE_Rand Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a
 *                                    call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult          If the function returns zero (success),
 *                                    this variable will contain the
 *                                    Status Result returned from the
 *                                    Bluetooth device.
 *
 * @param[out]  Random_NumberResult   64-bit random number generated
 *                                    from the controller.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Rand(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_Random_Number_t *Random_NumberResult);

/**
 * @brief
 * Issues the HCI_LE_Start_Encryption Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this
 *                                      Bluetooth Protocol Stack via a
 *                                      call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle       Handle used to identify the desired
 *                                      connection.
 *
 * @param[in]   Random_Number           64-bit random number to use during
 *                                      the encryption process.
 *
 * @param[in]   Encrypted_Diversifier   16-bit encrypted diversifier.
 *
 * @param[in]   Long_Term_Key           128-bit long term key.
 *
 * @param[out]  StatusResult            If the function returns zero (success),
 *                                      this variable will contain the
 *                                      Status Result returned from the
 *                                      Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Start_Encryption(uint32_t BluetoothStackID, uint16_t Connection_Handle, qapi_BLE_Random_Number_t Random_Number, uint16_t Encrypted_Diversifier, qapi_BLE_Long_Term_Key_t Long_Term_Key, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Long_Term_Key_Request_Reply
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle used to identify the desired
 *                                        connection.
 *
 * @param[in]   Long_Term_Key             128-bit long term key.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Returned connection handle.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Long_Term_Key_Request_Reply(uint32_t BluetoothStackID, uint16_t Connection_Handle, qapi_BLE_Long_Term_Key_t Long_Term_Key, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Long_Term_Key_Request_Negative_Reply Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle used to identify the desired
 *                                        connection.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Returned connection handle.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Long_Term_Key_Request_Negative_Reply(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Supported_States
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * The following macros can be used to manipulate the LE states
 * bitmask:
 *
 *    QAPI_BLE_ASSIGN_LE_STATES(Mask, MSByte, ..., LSByte) \n
 *    QAPI_BLE_COMPARE_LE_STATES(Mask1, Mask2) \n
 *    QAPI_BLE_SET_LE_STATES_BIT (Mask, BitNumber) \n
 *    QAPI_BLE_RESET_LE_STATES_BIT (Mask, BitNumber) \n
 *    QAPI_BLE_TEST_LE_STATES_BIT(Mask, BitNumber)
 *
 * The bit number constants defined in the API for use with
 * these macros can be found in qapi_ble_hcitypes.h since
 * there are too many to list here. These values have the form
 * QAPI_BLE_HCI_LE_STATES_XXX, where XXX
 * indicates the possible states.
 *
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  LE_StatesResult           Returned supported LE states.
 *                                        These states are represented
 *                                        as a bitmask. See above for
 *                                        possible values.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Supported_States(uint32_t BluetoothStackID, uint8_t *StatusResult, qapi_BLE_LE_States_t *LE_StatesResult);

/**
 * @brief
 * Issues the HCI_LE_Receiver_Test Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   RX_Frequency       Frequency to receive packets, Where
 *                                 N (RX_Frequency) = (F -2402) / 2.
 *                                 This value should be in the range: \n
 *                                   #QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM \n
 *                                   #QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Receiver_Test(uint32_t BluetoothStackID, uint8_t RX_Frequency, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Transmitter_Test Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a
 *                                   call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TX_Frequency          Frequency to receive packets, Where
 *                                   N (TX_Frequency) = (F -2402) / 2.
 *                                   This value should be in the range: \n
 *                                      #QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM \n
 *                                      #QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM
 *
 * @param[in]  Length_Of_Test_Data   Length in bytes of payload data in
 *                                   each packet. This value should
 *                                   be in the range: \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MINIMUM_LENGTH \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MAXIMUM_LENGTH
 *
 * @param[in]  Packet_Payload        Description of the transmitted
 *                                   test pattern. The possible
 *                                   values are: \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_9 \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0xF0 \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0xAA \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_15 \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALL_1_BITS \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALL_0_BITS \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x0F \n
 *                                      #QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x55
 *
 * @param[out]  StatusResult         If the function returns zero (success),
 *                                   this variable will contain the
 *                                   Status Result returned from the
 *                                   Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Transmitter_Test(uint32_t BluetoothStackID, uint8_t TX_Frequency, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Test_End Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Number_Of_PacketsResult   Number of packets received
 *                                        (0x0000 for a transmitter
 *                                        test).
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Test_End(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *Number_Of_PacketsResult);

   /* HCI Command API's (LE Commands - Version 4.1). */

/**
 * @brief
 * Issues the
 * HCI_LE_Remote_Connection_Parameter_Request_Reply Command to the Bluetooth
 * Device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle to the connection desired
 *                                        to be updated.
 *
 * @param[in]   Conn_Interval_Min         Minimum value for the the connection
 *                                        interval. This should fall within
 *                                        the range: \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Interval_Max         Maximum value for the the connection
 *                                        interval. This should fall within
 *                                        the range: \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]   Conn_Latency              Slave latency for connection. This
 *                                        should be in range: \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MINIMUM \n
 *                                           QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MAXIMUM
 *
 * @param[in]   Supervision_Timeout       Supervision timeout for LE link.
 *                                        This should be in range: \n
 *                                           QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MINIMUM \n
 *                                           QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MAXIMUM \n
 *                                        The Supervision_Timeout follows the rule: \n
 *                                           Time = N * 10 msec
 *
 * @param[in]   Minimum_CE_Length         Information about minimum length
 *                                        of LE connection. This should
 *                                        be in range: \n
 *                                           #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                           #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                        The CE Length follows the rule: \n
 *                                           Time = N * 0.625 ms
 *
 * @param[in]   Maximum_CE_Length         Information about minimum length
 *                                        of LE connection. This should
 *                                        be in range: \n
 *                                           #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MINIMUM \n
 *                                           #QAPI_BLE_HCI_LE_LENGTH_OF_CONNECTION_MAXIMUM \n
 *                                        The CE Length follows the rule: \n
 *                                           Time = N * 0.625 ms
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Will contain the Connection Handle
 *                                        returned from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Reply(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Conn_Interval_Min, uint16_t Conn_Interval_Max, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint16_t Minimum_CE_Length, uint16_t Maximum_CE_Length, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle to the connection desired
 *                                        to be updated.
 *
 * @param[in]   Reason                    Reason that the connection parameter
 *                                        request was rejected.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Will contain the Connection Handle
 *                                        returned from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Reason, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

   /* HCI Command API's (LE Commands - Version 4.2). */

/**
 * @brief
 * Issues the HCI_LE_Set_Data_Length Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned to this
 *                                        Bluetooth Protocol Stack via a
 *                                        call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle         Handle to the connection desired
 *                                        to be updated.
 *
 * @param[in]   TxOctets                  Suggested number of transit
 *                                        octets for the new connection.
 *
 * @param[in]   Txtime                    Suggested transmit time
 *                                        for the new connection.
 *
 * @param[out]  StatusResult              If the function returns zero (success),
 *                                        this variable will contain the
 *                                        Status Result returned from the
 *                                        Bluetooth device.
 *
 * @param[out]  Connection_HandleResult   Will contain the Connection Handle
 *                                        returned from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Data_Length(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t TxOctets, uint16_t Txtime, uint8_t *StatusResult, uint16_t *Connection_HandleResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Data_Length Command
 * to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                 If the function returns zero (success),
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @param[out]  SuggestedMaxTxOctetsResult   Will contain the suggested number
 *                                           of transmit octets for the new
 *                                           connection.
 *
 * @param[out]  SuggestedMaxTxTimeResult     Will contain the suggested transmit
 *                                           time for the new connection.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Suggested_Default_Data_Length(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *SuggestedMaxTxOctetsResult, uint16_t *SuggestedMaxTxTimeResult);

/**
 * @brief
 * Issues the HCI_LE_Write_Suggested_Default_Data_Length
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a
 *                                     call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   SuggestedMaxTxOctets   Suggested number of transit
 *                                     octets for the new connection.
 *
 * @param[in]   SuggestedMaxTxTime     Suggested transmit time
 *                                     for the new connection.
 *
 * @param[out]  StatusResult           If the function returns zero (success),
 *                                     this variable will contain the
 *                                     Status Result returned from the
 *                                     Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Write_Suggested_Default_Data_Length(uint32_t BluetoothStackID, uint16_t SuggestedMaxTxOctets, uint16_t SuggestedMaxTxTime, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Local_P256_Public_Key
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Local_P256_Public_Key(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Generate_DHKey Command to the
 * Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID         Unique identifier assigned to this
 *                                       Bluetooth Protocol Stack via a
 *                                       call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Remote_P256_Public_Key   Remote P256 Key.
 *
 * @param[out]  StatusResult             If the function returns zero (success),
 *                                       this variable will contain the
 *                                       Status Result returned from the
 *                                       Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Generate_DHKey(uint32_t BluetoothStackID, qapi_BLE_P256_Public_Key_t *Remote_P256_Public_Key, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Add_Device_To_Resolving_List
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Peer_Identity_Address_Type   Type of peer identity address. Possible
 *                                           values are: \n
 *                                              #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                              #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM
 *
 * @param[in]   Peer_Identity_Address        Peer identify address.
 *
 * @param[in]   Peer_IRK                     Peer's identity resolving key.
 *
 * @param[in]   Local_IRK                    Local device's identity
 *                                           resolving key.
 *
 * @param[out]  StatusResult                 If the function returns zero (success),
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Add_Device_To_Resolving_List(uint32_t BluetoothStackID, uint8_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, qapi_BLE_Encryption_Key_t Peer_IRK, qapi_BLE_Encryption_Key_t Local_IRK, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Remove_Device_From_Resolving_List Command to the Bluetooth
 * Device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Peer_Identity_Address_Type   Type of peer identity address. Possible
 *                                           values are: \n
 *                                              #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                              #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM
 *
 * @param[in]   Peer_Identity_Address        Peer identify address.
 *
 * @param[out]  StatusResult                 If the function returns zero (success),
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remove_Device_From_Resolving_List(uint32_t BluetoothStackID, uint8_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Clear_Resolving_List Command
 * to the Bluetooth device that is associated with the Bluetooth Protocol
 * Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Clear_Resolving_List(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Resolving_List_Size
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID            Unique identifier assigned to this
 *                                          Bluetooth Protocol Stack via a
 *                                          call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                If the function returns zero (success),
 *                                          this variable will contain the
 *                                          Status Result returned from the
 *                                          Bluetooth device.
 *
 * @param[out]  Resolving_List_SizeResult   Will contain the resolving list size.
 *                                          This is returned in the number of
 *                                          entries not bytes.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Resolving_List_Size(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *Resolving_List_SizeResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Peer_Resolvable_Address
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID                Unique identifier assigned to this
 *                                              Bluetooth Protocol Stack via a
 *                                              call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Peer_Identity_Address_Type      Type of peer identity address. Possible
 *                                              values are: \n
 *                                                 #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                                 #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM
 *
 * @param[in]   Peer_Identity_Address           Peer identify address.
 *
 * @param[out]  StatusResult                    If the function returns zero (success),
 *                                              this variable will contain the
 *                                              Status Result returned from the
 *                                              Bluetooth device.
 *
 * @param[out]  Peer_Resolvable_AddressResult   Will contain the peer's resolvable
 *                                              address.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Peer_Resolvable_Address(uint32_t BluetoothStackID, uint8_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, uint8_t *StatusResult, qapi_BLE_BD_ADDR_t *Peer_Resolvable_AddressResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Local_Resolvable_Address
 * Command to the Bluetooth device that is associated with the
 * Bluetooth Protocol Stack specified by the BluetoothStackID
 * parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID                 Unique identifier assigned to this
 *                                               Bluetooth Protocol Stack via a
 *                                               call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Peer_Identity_Address_Type       Type of peer identity address. Possible
 *                                               values are: \n
 *                                                  #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_PUBLIC \n
 *                                                  #QAPI_BLE_HCI_LE_PEER_ADDRESS_TYPE_RANDOM
 *
 * @param[in]   Peer_Identity_Address            Peer identify address.
 *
 * @param[out]  StatusResult                     If the function returns zero (success),
 *                                               this variable will contain the
 *                                               Status Result returned from the
 *                                               Bluetooth device.
 *
 * @param[out]  Local_Resolvable_AddressResult   Will contain the local resolvable
 *                                               address.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Local_Resolvable_Address(uint32_t BluetoothStackID, uint8_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, uint8_t *StatusResult, qapi_BLE_BD_ADDR_t *Local_Resolvable_AddressResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Address_Resolution_Enable
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID           Unique identifier assigned to this
 *                                         Bluetooth Protocol Stack via a
 *                                         call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Address_Resolution_Enable   Boolean flag that will enable/disable
 *                                         address resolution. Possible values are: \n
 *                                           #QAPI_BLE_HCI_LE_CONTROLLER_ADDRESS_RESOLUTION_DISABLED \n
 *                                           #QAPI_BLE_HCI_LE_CONTROLLER_ADDRESS_RESOLUTION_ENABLED
 *
 * @param[out]  StatusResult               If the function returns zero (success),
 *                                         this variable will contain the
 *                                         Status Result returned from the
 *                                         Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Address_Resolution_Enable(uint32_t BluetoothStackID, uint8_t Address_Resolution_Enable, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Resolvable_Private_Address_Timeout Command to the Bluetooth
 * Device that is associated with the Bluetooth Protocol Stack specified
 * by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   RPA_Timeout        Resolvable private addresss
 *                                 timeout.
 *
 * @param[out]  StatusResult       If the function returns zero (success),
 *                                 this variable will contain the
 *                                 Status Result returned from the
 *                                 Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Resolvable_Private_Address_Timeout(uint32_t BluetoothStackID, uint16_t RPA_Timeout, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Read_Maximum_Data_Length
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult                 If the function returns zero (success),
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @param[out]  SupportedMaxTxOctetsResult   Will contain the number of supported
 *                                           transmit octets.
 *
 * @param[out]  SupportedMaxTxTimeResult     Will contain the supported transmit
 *                                           time.
 *
 * @param[out]  SupportedMaxRxOctetsResult   Will contain the number of supported
 *                                           receive octets.
 *
 * @param[out]  SupportedMaxRxTimeResult     Will contain the supported receive
 *                                           time.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Maximum_Data_Length(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *SupportedMaxTxOctetsResult, uint16_t *SupportedMaxTxTimeResult, uint16_t *SupportedMaxRxOctetsResult, uint16_t *SupportedMaxRxTimeResult);

   /* HCI Command API's (LE Commands - Version 5.0). */

/**
 * @brief
 * Issues the HCI_LE_Read_PHY
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the bluetooth device.
 *
 * @param[in]   BluetoothStackID             Unique identifier assigned to this
 *                                           Bluetooth Protocol Stack via a
 *                                           call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle            Connection handle for
 *                                           the connection whose PHY is
 *                                           being read.
 *
 * @param[out]  StatusResult                 If the function returns zero (success)
 *                                           this variable will contain the
 *                                           Status Result returned from the
 *                                           Bluetooth device.
 *
 * @param[out]  Connection_HandleResult      Will contain the connection handle for
 *                                           the connection whose PHY is
 *                                           has been.
 *
 * @param[out]  TX_PHYResult                 Will contain the Tx PHY.
 *
 * @param[out]  RX_PHYResult                 Will contain the Rx PHY.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX, which
 *               can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_PHY(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t *StatusResult, uint16_t *Connection_HandleResult, uint8_t *TX_PHYResult, uint8_t *RX_PHYResult);

/**
 * @brief
 * Issues the HCI_LE_Set_Default_PHY
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to
 *                                  this Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   ALL_PHYS            Specifies if the host has no
 *                                  preference for the default Tx/Rx
 *                                  PHYs.
 *
 * @param[in]   TX_PHYS             Host's preferred Tx PHY.
 *
 * @param[in]   RX_PHYS             Host's preferred Rx PHY.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Default_PHY(uint32_t BluetoothStackID, uint8_t ALL_PHYS, uint8_t TX_PHYS, uint8_t RX_PHYS, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Set_PHY
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to
 *                                  this Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Connection handle for
 *                                  the connection whose PHY is
 *                                  being set.
 *
 * @param[in]   ALL_PHYS            Specifies if the host has no
 *                                  preference for the Tx/Rx PHYs.
 *
 * @param[in]   TX_PHYS             Host's preferred Tx PHY.
 *
 * @param[in]   RX_PHYS             Host's preferred Rx PHY.
 *
 * @param[in]   PHY_Options         Host's preference when
 *                                  transmitting on the LE Coded PHY.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_PHY(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t ALL_PHYS, uint8_t TX_PHYS, uint8_t RX_PHYS, uint16_t PHY_Options, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Enhanced_Receiver_Test
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to
 *                                  this Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   RX_Channel          Rx Channel.
 *
 * @param[in]   PHY                 Receiver PHY to use for the
 *                                  test.
 *
 * @param[in]   Modulation_Index    Modulation index.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Enhanced_Receiver_Test(uint32_t BluetoothStackID, uint8_t RX_Channel, uint8_t PHY, uint8_t Modulation_Index, uint8_t *StatusResult);

/**
 * @brief
 * Issues the HCI_LE_Enhanced_Transmitter_Test
 * Command to the Bluetooth device that is associated with the Bluetooth
 * Protocol Stack specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to
 *                                  this Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   TX_Channel          Tx Channel.
 *
 * @param[in]   Length_Of_Test_Data Length of the test data.
 *
 * @param[in]   Packet_Payload      Format for the test data.
 *
 * @param[in]   PHY                 Transmitter PHY to use for
 *                                  the test.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(uint32_t BluetoothStackID, uint8_t TX_Channel, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t PHY, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Advertising_Set_Random_Address Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Advertising handle
 *                                  that identifies the advertising
 *                                  set.
 *
 * @param[in]   Advertising_Random_Address  Random address
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Advertising_Set_Random_Address(uint32_t BluetoothStackID, uint8_t Advertising_Handle, qapi_BLE_BD_ADDR_t *Advertising_Random_Address, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Advertising_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Advertising handle
 *                                  that identifies the advertising
 *                                  set.
 *
 * @param[in]   Advertising_Event_Properties  Advertising event
 *                                            properties that control
 *                                            the type of advertising
 *                                            and optional features.
 *
 * @param[in]   Primary_Advertising_Interval_Min  Primary
 *                                                advertising interval
 *                                                minimum.
 *
 * @param[in]   Primary_Advertising_Interval_Max  Primary
 *                                                advertising interval
 *                                                maximum.
 *
 * @param[in]   Primary_Advertising_Channel_Map  Primary
 *                                               advertising channels.
 *
 * @param[in]   Own_Address_Type    Local device address type.
 *
 * @param[in]   Peer_Address_Type   Peer address type.
 *
 * @param[in]   Peer_Address        Peer address.
 *
 * @param[in]   Advertising_Filter_Policy  The advertising filter
 *                                         policy.
 *
 * @param[in]   Advertising_TX_Power  Host's preference for the
 *                                    transmit power for
 *                                    advertisements.
 *
 * @param[in]   Primary_Advertising_PHY  Primary advertising PHY
 *                                       to use for
 *                                       advertisements.
 *
 * @param[in]   Secondary_Advertising_Max_Skip  Number of
 *                                              advertising events the
 *                                              controller may skip
 *                                              before sending the
 *                                              AUX_ADV_IND PDU.
 *
 * @param[in]   Secondary_Advertising_PHY  Secondary advertising
 *                                         PHY to use for
 *                                         advertisements.
 *
 * @param[in]   Advertising_SID            Advertising SID to
 *                                         use for
 *                                         advertisements.
 *
 * @param[in]   Scan_Request_Notification_Enable  Enables scan requests
 *                                                for the
 *                                                advertisements.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Selected_TX_PowerResult  Transmit power the
 *                                       controller will use for the
 *                                       advertising set. This will be
 *                                       less than or equal to the
 *                                       Advertising_TX_Power
 *                                       parameter.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint16_t Advertising_Event_Properties, uint32_t Primary_Advertising_Interval_Min, uint32_t Primary_Advertising_Interval_Max, uint8_t Primary_Advertising_Channel_Map, uint8_t Own_Address_Type, uint8_t Peer_Address_Type, qapi_BLE_BD_ADDR_t *Peer_Address, uint8_t Advertising_Filter_Policy, int8_t Advertising_TX_Power, uint8_t Primary_Advertising_PHY, uint8_t Secondary_Advertising_Max_Skip, uint8_t Secondary_Advertising_PHY, uint8_t Advertising_SID, uint8_t Scan_Request_Notification_Enable, uint8_t *StatusResult, int8_t *Selected_TX_PowerResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Advertising_Data Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Advertising handle
 *                                  that identifies the advertising
 *                                  set.
 *
 * @param[in]   Operation           Allows the host to set
 *                                  the advertising data in one or more
 *                                  operations.
 *
 * @param[in]   Fragment_Preference  A hint to the controller on whether
 *                                   the advertising data should be
 *                                   fragmented.
 *
 * @param[in]   Advertising_Data_Length  Advertising data
 *                                       length.
 *
 * @param[in]   Advertising_Data    Pointer to the advertising
 *                                  data.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Advertising_Data(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t Operation, uint8_t Fragment_Preference, uint8_t Advertising_Data_Length, uint8_t *Advertising_Data, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Scan_Response_Data Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Advertising handle
 *                                  that identifies the advertising
 *                                  set.
 *
 * @param[in]   Operation           Allows the host to set
 *                                  the scan response data in one or
 *                                  more operations.
 *
 * @param[in]   Fragment_Preference  A hint to the controller on whether
 *                                   the scan response data should be
 *                                   fragmented.
 *
 * @param[in]   Scan_Response_Data_Length  Length of the scan
 *                                         response data.
 *
 * @param[in]   Scan_Response_Data  Pointer to the scan response
 *                                  data.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Scan_Response_Data(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t Operation, uint8_t Fragment_Preference, uint8_t Scan_Response_Data_Length, uint8_t *Scan_Response_Data, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Advertising_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable              Enables/Disabled the advertising
 *                                  set.
 *
 * @param[in]   Number_of_Sets      Number of advertising sets
 *                                  to enable/disable. This can
 *                                  be zero if advertising is
 *                                  disabled to disable all
 *                                  advertising sets.
 *
 * @param[in]   Advertising_Handle  Pointer to an array of
 *                                  advertising handles for each
 *                                  advertising set.
 *
 * @param[in]   Duration            Pointer to an array for each
 *                                  advertising set's duration before
 *                                  advertising is disabled.
 *
 * @param[in]   Max_Extended_Advertising_Events  Pointer to an
 *                                               array for each
 *                                               advertising
 *                                               set's maximum
 *                                               number of
 *                                               events that can
 *                                               be sent before
 *                                               advertising is
 *                                               disabled.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Advertising_Enable(uint32_t BluetoothStackID, uint8_t Enable, uint8_t Number_of_Sets, uint8_t *Advertising_Handle, uint16_t *Duration, uint8_t *Max_Extended_Advertising_Events, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_Maximum_Advertising_Data_Length Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Maximum_Advertising_Data_Length  If the StatusResult
 *                                               is zero (success) this
 *                                               variable will contain
 *                                               the maximum
 *                                               advertising data l
 *                                               ength returned from
 *                                               the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Maximum_Advertising_Data_Length(uint32_t BluetoothStackID, uint8_t *StatusResult, uint16_t *Maximum_Advertising_Data_Length);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_Number_Of_Supported_Advertising_Sets Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Num_Supported_Advertising_Sets  If the StatusResult is
 *                                              zero (success) this
 *                                              variable will contain
 *                                              the number of supported
 *                                              advertising sets
 *                                              returned from the
 *                                              Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Number_Of_Supported_Advertising_Sets(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *Num_Supported_Advertising_Sets);

/**
 * @brief
 * Issues the
 * HCI_LE_Remove_Advertising_Set Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Advertising handle
 *                                  that identifies the advertising
 *                                  set.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remove_Advertising_Set(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Clear_Advertising_Sets Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Clear_Advertising_Sets(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Periodic_Advertising_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Identifies the advertising
 *                                  set.
 *
 * @param[in]   Periodic_Advertising_Interval_Min  Minimum periodic advertising
 *                                                 interval.
 *
 * @param[in]   Periodic_Advertising_Interval_Max  Maximum periodic advertising
 *                                                 interval.
 *
 * @param[in]   Periodic_Advertising_Properties  Properties.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Periodic_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint16_t Periodic_Advertising_Interval_Min, uint16_t Periodic_Advertising_Interval_Max, uint16_t Periodic_Advertising_Properties, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Periodic_Advertising_Data Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Identifies the advertising
 *                                  set.
 *
 * @param[in]   Operation           Indicates how the advertising data
 *                                  is going to be formatted.
 *
 * @param[in]   Advertising_Data_Length  Length of advertising data.
 *
 * @param[in]   Advertising_Data  Properties.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Periodic_Advertising_Data(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t Operation, uint8_t Advertising_Data_Length, uint8_t *Advertising_Data, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Periodic_Advertising_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable              Enables/disables advertising.
 *
 * @param[in]   Advertising_Handle  Identifies the advertising
 *                                  set.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Periodic_Advertising_Enable(uint32_t BluetoothStackID, uint8_t Enable, uint8_t Advertising_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Scan_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Own_Address_Type    Local device address type.
 *
 * @param[in]   Scanning_Filter_Policy  Scanner filter policy.
 *
 * @param[in]   Scanning_PHYS       PHYs to use for scanning.
 *
 * @param[in]   Scan_Type           Pointer to an array based on the
 *                                  number of PHYs used for scanning.
 *                                  Indicates the type of scanning for
 *                                  each PHY.
 *
 * @param[in]   Scan_Interval       Pointer to an array based on the
 *                                  number of PHYs used for scanning.
 *                                  Indicates the scan interval for
 *                                  each PHY.
 *
 * @param[in]   Scan_Window         Pointer to an array based on the
 *                                  number of PHYs used for scanning.
 *                                  Indicates the scan window for
 *                                  each PHY.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Scan_Parameters(uint32_t BluetoothStackID, uint8_t Own_Address_Type, uint8_t Scanning_Filter_Policy, uint8_t Scanning_PHYS, uint8_t *Scan_Type, uint16_t *Scan_Interval, uint16_t *Scan_Window, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Extended_Scan_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable              Enables/Disables scanning.
 *
 * @param[in]   Filter_Duplicates   Specifies whether duplicate
 *                                  advertisements should be filtered.
 *
 * @param[in]   Duration            Amount of time to scan
 *                                  before scanning is disable.
 *
 * @param[in]   Period              Scan period. Must be greater
 *                                  than the Duration parameter.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Extended_Scan_Enable(uint32_t BluetoothStackID, uint8_t Enable, uint8_t Filter_Duplicates, uint16_t Duration, uint16_t Period, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Extended_Create_Connection Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Initiating_Filter_Policy  The initiator filter policy
 *                                        for connectable
 *                                        advertisements.
 *
 * @param[in]   Own_Address_Type    Local device address type.
 *
 * @param[in]   Peer_Address_Type   Peer address type.
 *
 * @param[in]   Peer_Address        Peer address.
 *
 * @param[in]   Initiating_PHYS     PHYs to use for scanning
 *                                  connectable advertisements.
 *
 * @param[in]   Scan_Interval       Pointer an array based on the
 *                                  number of Initiating_PHYS. This
 *                                  indicates the scan interval for
 *                                  each PHY.
 *
 * @param[in]   Scan_Window         Pointer an array based on the
 *                                  number of Initiating_PHYS. This
 *                                  indicates the scan window for each
 *                                  PHY.
 *
 * @param[in]   Conn_Interval_Min   Pointer an array based on the
 *                                  number of Initiating_PHYS. This
 *                                  indicates the minimum connection
 *                                  interval for each PHY.
 *
 * @param[in]   Conn_Interval_Max   Pointer an array based on the
 *                                  number of Initiating_PHYS. This
 *                                  indicates the maximum connection
 *                                  interval for each PHY.
 *
 * @param[in]   Conn_Latency        Pointer an array based on the
 *                                  number of Initiating_PHYS. This
 *                                  indicates the connection
 *                                  latency for each PHY.
 *
 * @param[in]   Supervision_Timeout  Pointer an array based on the
 *                                   number of Initiating_PHYS. This
 *                                   indicates the supervision timeout
 *                                   for each PHY.
 *
 * @param[in]   Minimum_CE_Length  Pointer an array based on the
 *                                 number of Initiating_PHYS. This
 *                                 indicates the minimum connection
 *                                 length for each PHY.
 *
 * @param[in]   Maximum_CE_Length  Pointer an array based on the
 *                                 number of Initiating_PHYS. This
 *                                 indicates the maximum connection
 *                                 length for each PHY.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Extended_Create_Connection(uint32_t BluetoothStackID, uint8_t Initiating_Filter_Policy, uint8_t Own_Address_Type, uint8_t Peer_Address_Type, qapi_BLE_BD_ADDR_t *Peer_Address, uint8_t Initiating_PHYS, uint16_t *Scan_Interval, uint16_t *Scan_Window, uint16_t *Conn_Interval_Min, uint16_t *Conn_Interval_Max, uint16_t *Conn_Latency, uint16_t *Supervision_Timeout, uint16_t *Minimum_CE_Length, uint16_t *Maximum_CE_Length, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Periodic_Advertising_Create_Sync Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Options             Sync options.
 *
 * @param[in]   Advertising_SID     Identifies the advertising set.
 *
 * @param[in]   Advertiser_Address_Type  Advertiser's address type.
 *
 * @param[in]   Advertiser_Address  Advertiser's address.
 *
 * @param[in]   Skip                Number of periodic advertisements
 *                                  that may be skipped.
 *
 * @param[in]   Sync_Timeout        Time until the sync is considered
 *                                  lost.
 *
 * @param[in]   Sync_CTE_Type       Filters periodic advertisements
 *                                  that will be synchronized based on
 *                                  the CTE type.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync(uint32_t BluetoothStackID, uint8_t Options, uint8_t Advertising_SID, uint8_t Advertiser_Address_Type, qapi_BLE_BD_ADDR_t *Advertiser_Address, uint16_t Skip, uint16_t Sync_Timeout, uint8_t Sync_CTE_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Periodic_Advertising_Create_Sync_Cancel Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Periodic_Advertising_Create_Sync_Cancel(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Periodic_Advertising_Terminate_Sync Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Sync_Handle         Identifies the periodic advertising
 *                                  train.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Periodic_Advertising_Terminate_Sync(uint32_t BluetoothStackID, uint16_t Sync_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Add_Device_To_Periodic_Advertiser_List Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertiser_Address_Type  Advertiser's address type.
 *
 * @param[in]   Advertiser_Address  Advertiser's address.
 *
 * @param[in]   Advertising_SID     Identifies the advertising set.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Add_Device_To_Periodic_Advertiser_List(uint32_t BluetoothStackID, uint8_t Advertiser_Address_Type, qapi_BLE_BD_ADDR_t *Advertiser_Address, uint8_t Advertising_SID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Remove_Device_From_Periodic_Advertiser_List Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertiser_Address_Type  Advertiser's address type.
 *
 * @param[in]   Advertiser_Address  Advertiser's address.
 *
 * @param[in]   Advertising_SID     Identifies the advertising set.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Remove_Device_From_Periodic_Advertiser_List(uint32_t BluetoothStackID, uint8_t Advertiser_Address_Type, qapi_BLE_BD_ADDR_t *Advertiser_Address, uint8_t Advertising_SID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Clear_Periodic_Advertiser_List Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Clear_Periodic_Advertiser_List(uint32_t BluetoothStackID, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_Periodic_Advertiser_List_Size Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Periodic_Advertiser_List_Size  If the function returns zero
 *                                             (success) this variable will
 *                                             hold the size of the periodic
 *                                             advertisers list.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Periodic_Advertiser_List_Size(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *Periodic_Advertiser_List_Size);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_Transmit_Power Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Min_TX_Power        If the StatusResult is zero
 *                                  (success) this variable will contain
 *                                  the minimum transmit power returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Max_TX_Power        If the StatusResult is zero
 *                                  (success) this variable will contain
 *                                  the maximum transmit power returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Transmit_Power(uint32_t BluetoothStackID, uint8_t *StatusResult, int8_t *Min_TX_Power, int8_t *Max_TX_Power);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_RF_Path_Compensation Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  RF_TX_Path_Compensation_Value  If the StatusResult is zero
 *                                             (success) this variable
 *                                             will contain the RF
 *                                             transmit path
 *                                             compensation value
 *                                             returned from the
 *                                             Bluetooth device.
 *
 * @param[out]  RF_RX_Path_Compensation_Value  If the StatusResult is
 *                                             zero (success) this
 *                                             variable will contain the
 *                                             RF receive path
 *                                             compensation value
 *                                             returned from the
 *                                             Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_RF_Path_Compensation(uint32_t BluetoothStackID, uint8_t *StatusResult, int16_t *RF_TX_Path_Compensation_Value, int16_t *RF_RX_Path_Compensation_Value);

/**
 * @brief
 * Issues the
 * HCI_LE_Write_RF_Path_Compensation Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   RF_TX_Path_Compensation_Value  RF transmit path
 *                                             compensation value.
 *
 * @param[in]   RF_RX_Path_Compensation_Value  RF receive path
 *                                             compensation value.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Write_RF_Path_Compensation(uint32_t BluetoothStackID, int16_t RF_TX_Path_Compensation_Value, int16_t RF_RX_Path_Compensation_Value, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Privacy_Mode Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Peer_Identity_Address_Type  Peer identity
 *                                          address type.
 *
 * @param[in]   Peer_Identity_Address  Peer identity address.
 *
 * @param[in]   Privacy_Mode           Specifies the privacy mode.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Privacy_Mode(uint32_t BluetoothStackID, uint8_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t *Peer_Identity_Address, uint8_t Privacy_Mode, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Receiver_Test_V3 Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   RX_Channel          Receive channel.
 *
 * @param[in]   PHY                 Specifies the PHY used for the test.
 *
 * @param[in]   Modulation_Index    Modulation index.
 *
 * @param[in]   Expected_CTE_Length Specifies the length of the CTE.
 *
 * @param[in]   Expected_CTE_Type   Specifies CTE type.
 *
 * @param[in]   Slot_Durations      Slot durations used for the CTE.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Receiver_Test_V3(uint32_t BluetoothStackID, uint8_t RX_Channel, uint8_t PHY, uint8_t Modulation_Index, uint8_t Expected_CTE_Length, uint8_t Expected_CTE_Type, uint8_t Slot_Durations, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Transmitter_Test_V3 Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   TX_Channel          Transmit channel.
 *
 * @param[in]   Length_Of_Test_Data  Length of test data.
 *
 * @param[in]   Packet_Payload      The type of data that will be tested.
 *
 * @param[in]   PHY                 Specifies the PHY used for the test.
 *
 * @param[in]   CTE_Length          Specifies the length of the CTE.
 *
 * @param[in]   CTE_Type            Specifies CTE type.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Transmitter_Test_V3(uint32_t BluetoothStackID, uint8_t TX_Channel, uint8_t Length_Of_Test_Data, uint8_t Packet_Payload, uint8_t PHY, uint8_t CTE_Length, uint8_t CTE_Type, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Connectionless_CTE_Transmit_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Identifies the advertising set.
 *
 * @param[in]   CTE_Length          Length of a CTE.
 *
 * @param[in]   CTE_Type            CTE type.
 *
 * @param[in]   CTE_Count           Number of CTEs to transmit.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Connectionless_CTE_Transmit_Parameters(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t CTE_Length, uint8_t CTE_Type, uint8_t CTE_Count, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Connectionless_CTE_Transmit_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Advertising_Handle  Identifies the advertising set.
 *
 * @param[in]   CTE_Enable          Enables/disables CTEs that are included
 *                                  in the enabled advertising set's periodic
 *                                  advertisements.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Connectionless_CTE_Transmit_Enable(uint32_t BluetoothStackID, uint8_t Advertising_Handle, uint8_t CTE_Enable, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Connectionless_IQ_Sampling_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Sync_Handle         Identifies the periodic advertising train.
 *
 * @param[in]   Sampling_Enable     Enables/disables IQ sampling for CTEs included
 *                                  in received periodic advertisements.
 *
 * @param[in]   Slot_Durations      Slot durations for a CTE.
 *
 * @param[in]   Max_Sampled_CTEs    Maximum number of sample CTEs.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Connectionless_IQ_Sampling_Enable(uint32_t BluetoothStackID, uint16_t Sync_Handle, uint8_t Sampling_Enable, uint8_t Slot_Durations, uint8_t Max_Sampled_CTEs, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Connection_CTE_Receive_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   Sampling_Enable     Enables/disables IQ sampling.
 *
 * @param[in]   Slot_Durations      Slot durations for a CTE.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Connection_CTE_Receive_Parameters(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Sampling_Enable, uint8_t Slot_Durations, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Connection_CTE_Transmit_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   CTE_Types           Specifies the CTEs that will be included in
 *                                  the CTE request response.
 *
 * @param[in]   Length_Of_Switching_Pattern  List of antenna IDs.
 *
 * @param[in]   Antenna_IDs         Antenna IDs.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Connection_CTE_Transmit_Parameters(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t CTE_Types, uint8_t Length_Of_Switching_Pattern, uint8_t *Antenna_IDs, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Connection_CTE_Request_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   Enable              Enables/disables CTE requests.
 *
 * @param[in]   CTE_Request_Interval  CTE request interval.
 *
 * @param[in]   Requested_CTE_Length  Requested CTE length.
 *
 * @param[in]   Requested_CTE_Type  Requested CTE type.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Connection_CTE_Request_Enable(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Enable, uint16_t CTE_Request_Interval, uint8_t Requested_CTE_Length, uint8_t Requested_CTE_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Connection_CTE_Response_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   Enable              Enables/disables CTE responses.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Connection_CTE_Response_Enable(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Enable, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Read_Antenna_Information Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @param[out]  Supported_Switching_Sampling_Rates  If the function returns zero
 *                                                  (success) this variable will
 *                                                  hold the supported switching
 *                                                  sampling rates.
 *
 * @param[out]  Number_Of_Antennae  If the function returns zero
 *                                  (success) this variable will
 *                                  hold the number of antennae in
 *                                  the antenna array.
 *
 * @param[out]  Max_Length_Of_Switching_Pattern  If the function returns zero
 *                                               (success) this variable will
 *                                               hold the maximum length of
 *                                               the switching pattern.
 *
 * @param[out]  Max_CTE_Length      If the function returns zero
 *                                  (success) this variable will
 *                                  hold the maximum CTE length.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Read_Antenna_Information(uint32_t BluetoothStackID, uint8_t *StatusResult, uint8_t *Supported_Switching_Sampling_Rates, uint8_t *Number_Of_Antennae, uint8_t *Max_Length_Of_Switching_Pattern, uint8_t *Max_CTE_Length);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Periodic_Advertising_Receive_Enable Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Sync_Handle         Identifies the periodic advertising train.
 *
 * @param[in]   Enable              Enables/disables periodic advertising reports
 *                                  from the controller to the host.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Periodic_Advertising_Receive_Enable(uint32_t BluetoothStackID, uint16_t Sync_Handle, uint8_t Enable, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Periodic_Advertising_Sync_Transfer Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   Service_Data        Host specified value that will be included in
 *                                  the transfer.
 *
 * @param[in]   Sync_Handle         Identifies the periodic advertising train.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Periodic_Advertising_Sync_Transfer(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Service_Data, uint16_t Sync_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Periodic_Advertising_Set_Info_Transfer Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connectedremote device.
 *
 * @param[in]   Service_Data        Host specified value that will be included in
 *                                  the transfer.
 *
 * @param[in]   Advertising_Handle  Identifies the advertising set.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Periodic_Advertising_Set_Info_Transfer(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint16_t Service_Data, uint8_t Advertising_Handle, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle   Identifies the connected remote device.
 *
 * @param[in]   Mode                Sets the behaviour for when periodic
 *                                  advertising information has been
 *                                  received.
 *
 * @param[in]   Skip                Number of periodic advertising reports
 *                                  that may be skipped.
 *
 * @param[in]   Sync_Timeout        Timeout until the sync is considered lost.
 *
 * @param[in]   CTE_Type            Filter periodic advertising synchronization
 *                                  based on the CTE type.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, uint16_t Connection_Handle, uint8_t Mode, uint16_t Skip, uint16_t Sync_Timeout, uint8_t CTE_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters
 * Command to the Bluetooth device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Mode                Sets the behaviour for when periodic
 *                                  advertising information has been
 *                                  received.
 *
 * @param[in]   Skip                Number of periodic advertising reports
 *                                  that may be skipped.
 *
 * @param[in]   Sync_Timeout        Timeout until the sync is considered lost.
 *
 * @param[in]   CTE_Type            Filter periodic advertising synchronization
 *                                  based on the CTE type.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, uint8_t Mode, uint16_t Skip, uint16_t Sync_Timeout, uint8_t CTE_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Generate_DHKey_V2 Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Remote_P256_Public_Key  Remote device's P256 public key.
 *
 * @param[in]   Key_Type            Type of P256 public key.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Generate_DHKey_V2(uint32_t BluetoothStackID, qapi_BLE_P256_Public_Key_t *Remote_P256_Public_Key, uint8_t Key_Type, uint8_t *StatusResult);

/**
 * @brief
 * Issues the
 * HCI_LE_Modify_Sleep_Clock_Accuracy Command to the Bluetooth
 * device that is associated with the Bluetooth Protocol Stack
 * specified by the BluetoothStackID parameter.
 *
 * @details
 * This function blocks until either a result is returned from the
 * Bluetooth device or the function times out waiting for a response
 * from the Bluetooth device.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a call
 *                                  to qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Action              Specifies the accuracy of the clock.
 *
 * @param[out]  StatusResult        If the function returns zero
 *                                  (success) this variable will
 *                                  contain the Status Result returned
 *                                  from the Bluetooth device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- Of the form QAPI_BLE_BTPS_ERROR_XXX,
 *               which can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_HCI_LE_Modify_Sleep_Clock_Accuracy(uint32_t BluetoothStackID, uint8_t Action, uint8_t *StatusResult);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/** @} */ /* end_addtogroup qapi_ble_core_hci */

#endif


