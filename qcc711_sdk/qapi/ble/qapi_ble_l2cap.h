/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_l2cap.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack L2CAP API Type
 * Definitions, Constants, and Prototypes.
 *
 * @details
 * L2CAP provides connection-oriented and connectionless data
 * services to upper layer protocols with protocol multiplexing
 * capability, segmentation and reassembly operation, and group
 * abstractions.  L2CAP permits higher level protocols and applications
 * to transmit and receive L2CAP data packets up to 64 kilobytes
 * in length.
 */

#ifndef __QAPI_BLE_L2CAP_H__
#define __QAPI_BLE_L2CAP_H__

#include "./qapi_ble_btapityp.h"    /* Bluetooth API Type Definitions.        */
#include "./qapi_ble_bttypes.h"     /* Bluetooth Type Definitions/Constants.  */

/** @addtogroup qapi_ble_core_l2cap
@{ */

/** Maximum L2CAP MTU size. */
#define QAPI_BLE_L2CAP_MAXIMUM_SUPPORTED_STACK_MTU                          (QAPI_BLE_HCI_PACKET_TYPE_3_DH5_MAXIMUM_PAYLOAD_SIZE - (QAPI_BLE_NON_ALIGNED_WORD_SIZE*2))

/** Minimum timer for the amount of time in seconds that an L2CAP
    signalling request can go unacknowledged before some action is
    taken. */
#define QAPI_BLE_L2CAP_RTX_TIMER_MINIMUM_VALUE                               1

/** Maximum timer for the amount of time in seconds that an L2CAP
    signalling request can go unacknowledged before some action is
    taken. */
#define QAPI_BLE_L2CAP_RTX_TIMER_MAXIMUM_VALUE                              60

/** Default timer for the amount of time in seconds that an L2CAP
    signalling request can go unacknowledged before some action is
    taken. */
#define QAPI_BLE_L2CAP_RTX_TIMER_DEFAULT_VALUE                              15

/** Minimum amount of time in seconds that a multi-segmented L2CAP packet
    segment may be outstanding on the receive end. If the next segment is
    not received in the amount of time specified, the partial received
    message will be discarded. */
#define QAPI_BLE_L2CAP_RECEIVE_TIMER_MINIMUM_VALUE                           1

/** Maximum amount of time in seconds that a multi-segmented L2CAP packet
    segment may be outstanding on the receive end. If the next segment is
    not received in the amount of time specified, the partial received
    message will be discarded. */
#define QAPI_BLE_L2CAP_RECEIVE_TIMER_MAXIMUM_VALUE                          60

/** Default amount of time in seconds that a multi-segmented L2CAP packet
    segment may be outstanding on the receive end. If the next segment is
    not received in the amount of time specified, the partial received
    message will be discarded.  */
#define QAPI_BLE_L2CAP_RECEIVE_TIMER_DEFAULT_VALUE                          60

/** LE credit based connection successfully created. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_SUCCESSFUL                               0x0000

/** LE credit based connection rejected due to specified LE PSM not being registered. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_LE_PSM_NOT_REGISTERED            0x0002

/** LE credit based connection rejected due to insufficient resources to satisfy the request. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_NO_RESOURCES                     0x0004

/** LE credit based connection rejected due to insufficient authentication. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_AUTHENTICATION      0x0005

/** LE credit based connection rejected due to insufficient authorization. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_AUTHORIZATION       0x0006

/** LE credit based connection rejected due to insufficient encryption key size. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_ENCRYPTION_KEY_SIZE 0x0007

/** LE credit based connection rejected due to insufficient encryption. */
#define QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_ENCRYPTION          0x0008

/**
* Enumeration that represents the various Controller Types that
* are supported.
*/
typedef enum
{
   QAPI_BLE_CT_BR_EDR_E,
   /**< BR/EDR controller. */

   QAPI_BLE_CT_LE_E
   /**< LE controller. */
} qapi_BLE_L2CA_Controller_Type_t;

/**
 * Structure that represents the information that is used to control the
 * handling of data packets at the L2CAP Layer.
 *
 * The units of QueueLimit and LowThreshold are in packets.
 */
typedef struct qapi_BLE_L2CA_Queueing_Parameters_s
{
   /**
    * Bitmask that specifies the options that can be used when sending
    * data.
    *
    * Valid values have the form QAPI_BLE_L2CA_QUEUEING_FLAG_XXX and can
    * be found in qapi_ble_l2cap.h.
    */
   uint32_t Flags;

   /**
    * Indicates the upper limit at which the channel is considered full.
    */
   uint32_t QueueLimit;

   /**
    * Indicates the limit at which the channel is unlocked and data can
    * once again be sent on the channel.
    */
   uint32_t LowThreshold;
} qapi_BLE_L2CA_Queueing_Parameters_t;

/** Size of the #qapi_BLE_L2CA_Queueing_Parameters_s structure. */
#define QAPI_BLE_L2CA_QUEUEING_PARAMETERS_SIZE                    (sizeof(qapi_BLE_L2CA_Queueing_Parameters_t))

/** Bit flag for Flags member of qapi_BLE_L2CA_Queueing_Parmeters_s structure to
    indicate that queueing is done in terms of number of packets. */
#define QAPI_BLE_L2CA_QUEUEING_FLAG_LIMIT_BY_PACKETS              0x00000000L

/** Bit flag for Flags member of qapi_BLE_L2CA_Queueing_Parmeters_s structure to
    indicate that queueing is done in terms of queued bytes (no longer supported). */
#define QAPI_BLE_L2CA_QUEUEING_FLAG_LIMIT_BY_SIZE                 0x00000001L

/** Bit flag for Flags member of qapi_BLE_L2CA_Queueing_Parmeters_s structure to
    indicate that when queue limit is exceeded that the oldest packets should
    be discarded to make room for new packets. */
#define QAPI_BLE_L2CA_QUEUEING_FLAG_DISCARD_OLDEST                0x00000002L

/**
 * Structure that represents the structure of the L2CAP LE Credit Based
 * Channel data.
 *
 * Max SDU Size denotes the maximum Service Data Units that the local
 * device is capable of receiving from the remote device.
 *
 * The Max PDU Size (MPS) denotes the maximum L2CAP Packets (LE-Frame)
 * that the local device is capable of receiving from the remote device.
 * If Max SDU Size is larger than Max PDU Size, the SDU will
 * be split into multiple LE-Frames before being sent to the remote
 * device.
 *
 * The Maximum Credits denotes the maximum number of credits (in
 * LE-Frames) to grant to the remote device. The remote device will only
 * be able to send this many LE-Frames (of at most MaxPDUSize bytes)
 * without the local device granting credits back.
 *
 * The PDUQueueDepth directly affects the throughput for
 * this channel and for other channels. With a large value for
 * PDUQueueDepth the channel will have a larger share of the bandwidth at
 * the expense of other channels.
 *
 * The Credit Threshold controls when credits will be granted back to the
 * remote device. When the number of credits that we may grant back to
 * the remote device (that is, the initial credit count minus the number of
 * uncredited packets we have received) is greater than or equal to this
 * number, we will grant credits back to the remote device (so a
 * value of 2 says that we will send credits back to the remote device on
 * every second packet). Thus, CreditThreshold must be less than or equal
 * to InitialCredits.
 */
typedef struct qapi_BLE_L2CA_LE_Channel_Parameters_s
{
   /**
    * Bitmask that allows additional channel options to be configured.
    *
    * Valid values have the form
    * QAPI_BLE_L2CA_LE_CHANNEL_PARAMETER_FLAGS_XXX and can be found in
    * qapi_ble_l2cap.h.
    */
   uint16_t ChannelFlags;

   /**
    * Maximum Service Data Unit (SDU).
    */
   uint16_t MaxSDUSize;

   /**
    * Maximum Protocol Data Unit (PDU).
    */
   uint16_t MaxPDUSize;

   /**
    * PDU queue depth.
    */
   uint16_t PDUQueueDepth;

   /**
    * Maximum LE transmit credits.
    */
   uint16_t MaximumCredits;
} qapi_BLE_L2CA_LE_Channel_Parameters_t;

/** Size of the #qapi_BLE_L2CA_LE_Channel_Parameters_t structure. */
#define QAPI_BLE_L2CA_LE_CHANNEL_PARAMETERS_SIZE                     (sizeof(qapi_BLE_L2CA_LE_Channel_Parameters_t))

/** Bit flag for ChannelFlags member of #qapi_BLE_L2CA_LE_Channel_Parameters_t
    structure to indicate that application will handle granting of credits
    for the channel. */
#define QAPI_BLE_L2CA_LE_CHANNEL_PARAMETER_FLAGS_MANUAL_CREDIT_MODE  0x0001

/**
*   Type Declaration that defines the L2CA Event Callback
*   Data Types. These types are used with the
*   #qapi_BLE_L2CA_Event_Data_t structure to determine the type of Data
*   the L2CAP Event Callback structure contains.
*/
typedef enum
{
   QAPI_BLE_ET_CONNECTION_PARAMETER_UPDATE_INDICATION_E = 14,
   /**< L2CAP Connection Parameter Update Indication event. */

   QAPI_BLE_ET_CONNECTION_PARAMETER_UPDATE_CONFIRMATION_E,
   /**< L2CAP Connection Parameter Update Confirmation event. */

   QAPI_BLE_ET_FIXED_CHANNEL_CONNECT_INDICATION_E,
   /**< L2CAP Fixed Channel Connect Indication event. */

   QAPI_BLE_ET_FIXED_CHANNEL_DISCONNECT_INDICATION_E,
   /**< L2CAP Fixed Channel Disconnect Indication event. */

   QAPI_BLE_ET_FIXED_CHANNEL_DATA_INDICATION_E,
   /**< L2CAP Fixed Channel Data Indication event. */

   QAPI_BLE_ET_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_E,
   /**< L2CAP Fixed Channel Buffer Empty Indication event. */

   QAPI_BLE_ET_LE_CONNECT_INDICATION_E,
   /**< L2CAP LE Connection Oriented Channel Connect Indication event. */

   QAPI_BLE_ET_LE_CONNECT_CONFIRMATION_E,
   /**< L2CAP LE Connection Oriented Channel Connect Confirmation event. */

   QAPI_BLE_ET_LE_DISCONNECT_INDICATION_E,
   /**< L2CAP LE Connection Oriented Channel Disconnect Indication event. */

   QAPI_BLE_ET_LE_DISCONNECT_CONFIRMATION_E,
   /**< L2CAP LE Connection Oriented Channel Disconnect Confirmation event. */

   QAPI_BLE_ET_LE_DATA_INDICATION_E,
   /**< L2CAP LE Connection Oriented Channel Data Indication event. */

   QAPI_BLE_ET_LE_CHANNEL_BUFFER_EMPTY_INDICATION_E
   /**< L2CAP LE Connection Oriented Channel Buffer Empty Indication event. */
} qapi_BLE_L2CA_Event_Type_t;

/**
 * Structure that represents the
 * #QAPI_BLE_ET_CONNECTION_PARAMETER_UPDATE_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_Connection_Parameter_Update_Indication_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t           FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Minimum interval.
    */
   uint16_t           IntervalMin;

   /**
    * Maximum interval.
    */
   uint16_t           IntervalMax;

   /**
    * Slave latency.
    */
   uint16_t           SlaveLatency;

   /**
    * Timeout multiplier.
    */
   uint16_t           TimeoutMultiplier;
} qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t;

/** Size of the #qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t structure. */
#define QAPI_BLE_L2CA_CONNECTION_PARAMETER_UPDATE_INDICATION_SIZE   (sizeof(qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_CONNECTION_PARAMETER_UPDATE_CONFIRMATION_E event data.
 */
typedef struct qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t           FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Result of the connection parameter update procedure.
    */
   uint16_t           Result;
} qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t;

/** Size of the #qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t structure. */
#define QAPI_BLE_L2CA_CONNECTION_PARAMETER_UPDATE_CONFIRMATION_SIZE (sizeof(qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_FIXED_CHANNEL_CONNECT_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t                        FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t              BD_ADDR;

   /**
    * L2CAP controller type. @newpagetable
    */
   qapi_BLE_L2CA_Controller_Type_t ControllerType;
} qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t;

/** Size of the #qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t structure. */
#define QAPI_BLE_L2CA_FIXED_CHANNEL_CONNECT_INDICATION_SIZE         (sizeof(qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_FIXED_CHANNEL_DISCONNECT_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t                        FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t              BD_ADDR;

   /**
    * L2CAP controller type.
    */
   qapi_BLE_L2CA_Controller_Type_t ControllerType;
} qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t;

/** Size of the #qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t structure. */
#define QAPI_BLE_L2CA_FIXED_CHANNEL_DISCONNECT_INDICATION_SIZE      (sizeof(qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_FIXED_CHANNEL_DATA_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_Fixed_Channel_Data_Indication_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t           FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Data length.
    */
   uint16_t           Data_Length;

   /**
    * Pointer to the data.
    */
   uint8_t           *Variable_Data;
} qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t;

/** Size of the #qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t structure. */
#define QAPI_BLE_L2CA_FIXED_CHANNEL_DATA_INDICATION_SIZE            (sizeof(qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_E event data.
 *
 * This event is only dispatched when the caller has tried to write data
 * and the Fixed Channel Buffers are full. See the
 * qapi_BLE_L2CA_Enhanced_Fixed_Channel_Data_Write() function for more
 * information.
 */
typedef struct qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_s
{
   /**
    * Fixed channel identifier.
    */
   uint16_t           FCID;

   /**
    * Bluetooth address of the remote device.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;
} qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t;

/** Size of the #qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t structure. */
#define QAPI_BLE_L2CA_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_SIZE  (sizeof(qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_CONNECT_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_LE_Connect_Indication_s
{
   /**
    * Protocol Service Multiplexer (PSM).
    */
   uint16_t           PSM;

   /**
    * Local channel identifier.
    */
   uint16_t           LCID;

   /**
    * Channel identifier.
    */
   uint8_t            Identifier;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

  /**
    * Maximum Service Data Unit (SDU).
    */
   uint16_t           MaxSDUSize;

   /**
    * Maximum Protocol Data Unit (PDU).
    */
   uint16_t           MaxPDUSize;

   /**
    * Number of initialize credits.
    */
   uint16_t           InitialCredits;
} qapi_BLE_L2CA_LE_Connect_Indication_t;

/** Size of the #qapi_BLE_L2CA_LE_Connect_Indication_t structure. */
#define QAPI_BLE_L2CA_LE_CONNECT_INDICATION_SIZE                  (sizeof(qapi_BLE_L2CA_LE_Connect_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_CONNECT_CONFIRMATION_E event data.
 */
typedef struct qapi_BLE_L2CA_LE_Connect_Confirmation_s
{
   /**
    * Local channel identifier.
    */
   uint16_t LCID;

   /**
    * Result of the connection.
    */
   uint16_t Result;

   /**
    * Maximum Service Data Unit (SDU).
    */
   uint16_t MaxSDUSize;

   /**
    * Maximum Protocol Data Unit (PDU).
    */
   uint16_t MaxPDUSize;

   /**
    * Number of initialize credits.
    */
   uint16_t InitialCredits;
} qapi_BLE_L2CA_LE_Connect_Confirmation_t;

/** Size of the #qapi_BLE_L2CA_LE_Connect_Confirmation_t structure. */
#define QAPI_BLE_L2CA_LE_CONNECT_CONFIRMATION_SIZE                (sizeof(qapi_BLE_L2CA_LE_Connect_Confirmation_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_DISCONNECT_INDICATION_E event data.
 */
typedef struct qapi_BLE_L2CA_LE_Disconnect_Indication_s
{
   /**
    * Local channel identifier.
    */
   uint16_t LCID;

   /**
    * Reason for the disconnection.
    */
   uint8_t  Reason;
} qapi_BLE_L2CA_LE_Disconnect_Indication_t;

/** Size of the #qapi_BLE_L2CA_LE_Disconnect_Indication_t structure. */
#define QAPI_BLE_L2CA_LE_DISCONNECT_INDICATION_SIZE               (sizeof(qapi_BLE_L2CA_LE_Disconnect_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_DISCONNECT_CONFIRMATION_E event data.
 */
typedef struct qapi_BLE_L2CA_LE_Disconnect_Confirmation_s
{
   /**
    * Local channel identifier.
    */
   uint16_t LCID;

   /**
    * Result of the disconnection.
    */
   uint16_t Result;
} qapi_BLE_L2CA_LE_Disconnect_Confirmation_t;

/** Size of the #qapi_BLE_L2CA_LE_Disconnect_Confirmation_t structure. */
#define QAPI_BLE_L2CA_LE_DISCONNECT_CONFIRMATION_SIZE             (sizeof(qapi_BLE_L2CA_LE_Disconnect_Confirmation_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_DATA_INDICATION_E event data.
 *
 * The CreditsConsumed member of this event indicates the number of
 * credits that were consumed by the remote device to send this packet.
 * When in manual-credit mode (that is, the
 * #QAPI_BLE_L2CA_LE_CHANNEL_PARAMETER_FLAGS_MANUAL_CREDIT_MODE flag was
 * set in the ChannelFlags member of the
 * #qapi_BLE_L2CA_LE_Channel_Parameters_t structure that was passed to
 * either the qapi_BLE_L2CA_LE_Connect_Request() or
 * qapi_BLE_L2CA_LE_Connect_Response() API calls that created or accepted
 * this LE channel respectively), the application should call
 * qapi_BLE_L2CA_LE_Grant_Credits(), passing the CreditsConsumed member to
 * inform the L2CA Layer that the SDU has been consumed and we can grant
 * credits back.
 *
 * This CreditsConsumed member is additive, so the application may add the
 * CreditsConsumed from multiple events into one call to the
 * qapi_BLE_L2CA_LE_Grant_Credits(). However, the application should
 * grant credits as soon as a SDU is consumed rather than waiting for
 * multiple data indication events.
 */
typedef struct qapi_BLE_L2CA_LE_Data_Indication_s
{
   /**
    * Channel identifier.
    */
   uint16_t  CID;

   /**
    * Number of credits consumed.
    */
   uint16_t  CreditsConsumed;

   /**
    * Data length.
    */
   uint16_t  Data_Length;

   /**
    * Pointer to the variable data.
    */
   uint8_t  *Variable_Data;
} qapi_BLE_L2CA_LE_Data_Indication_t;

/** Size of the #qapi_BLE_L2CA_LE_Data_Indication_t structure. */
#define QAPI_BLE_L2CA_LE_DATA_INDICATION_SIZE                     (sizeof(qapi_BLE_L2CA_LE_Data_Indication_t))

/**
 * Structure that represents the
 * #QAPI_BLE_ET_LE_DATA_INDICATION_E event data.
 *
 * This event is only dispatched when the caller has tried to write data
 * and the Channel Buffers are full. See the
 * qapi_BLE_L2CA_Enhanced_Dynamic_Channel_Data_Write() function for more
 * information.
 */
typedef struct qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_s
{
   /**
    * Channel identifier.
    */
   uint16_t CID;
} qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t;

/** Size of the #qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t structure. */
#define QAPI_BLE_L2CA_LE_CHANNEL_BUFFER_EMPTY_INDICATION_SIZE     (sizeof(qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t))

/**
 * Structure that represents the container structure for holding all the
 * L2CAP event data.
 */
typedef struct qapi_BLE_L2CA_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_L2CA_Event_Type_t L2CA_Event_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint32_t                   Event_Data_Length;
   union
   {
      /**
       * L2CAP Connection Parameter Update Indication event data.
       */
      qapi_BLE_L2CA_Connection_Parameter_Update_Indication_t   *L2CA_Connection_Parameter_Update_Indication;

      /**
       * L2CAP Connection Parameter Update Confirmation event data.
       */
      qapi_BLE_L2CA_Connection_Parameter_Update_Confirmation_t *L2CA_Connection_Parameter_Update_Confirmation;

      /**
       * L2CAP Fixed Channel Connect Indication event data.
       */
      qapi_BLE_L2CA_Fixed_Channel_Connect_Indication_t         *L2CA_Fixed_Channel_Connect_Indication;

      /**
       * L2CAP Fixed Channel Disconnect Indication event data.
       */
      qapi_BLE_L2CA_Fixed_Channel_Disconnect_Indication_t      *L2CA_Fixed_Channel_Disconnect_Indication;

      /**
       * L2CAP Fixed Channel Data Indication event data.
       */
      qapi_BLE_L2CA_Fixed_Channel_Data_Indication_t            *L2CA_Fixed_Channel_Data_Indication;

      /**
       * L2CAP Fixed Channel Buffer Empty Indication event data.
       */
      qapi_BLE_L2CA_Fixed_Channel_Buffer_Empty_Indication_t    *L2CA_Fixed_Channel_Buffer_Empty_Indication;

      /**
       * L2CAP LE Connect Indication event data.
       */
      qapi_BLE_L2CA_LE_Connect_Indication_t                    *L2CA_LE_Connect_Indication;

      /**
       * L2CAP LE Connection Confirmation event data.
       */
      qapi_BLE_L2CA_LE_Connect_Confirmation_t                  *L2CA_LE_Connect_Confirmation;

      /**
       * L2CAP LE Disconnect Indication event data.
       */
      qapi_BLE_L2CA_LE_Disconnect_Indication_t                 *L2CA_LE_Disconnect_Indication;

      /**
       * L2CAP LE Disconnect Confirmation event data.
       */
      qapi_BLE_L2CA_LE_Disconnect_Confirmation_t               *L2CA_LE_Disconnect_Confirmation;

      /**
       * L2CAP LE Data Indication event data.
       */
      qapi_BLE_L2CA_LE_Data_Indication_t                       *L2CA_LE_Data_Indication;

      /**
       * L2CAP LE Channel Buffer Empty Indication event data.
       */
      qapi_BLE_L2CA_LE_Channel_Buffer_Empty_Indication_t       *L2CA_LE_Channel_Buffer_Empty_Indication;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_L2CA_Event_Data_t;

/** Size of the #qapi_BLE_L2CA_Event_Data_t structure. */
#define QAPI_BLE_L2CA_EVENT_DATA_SIZE                            (sizeof(qapi_BLE_L2CA_Event_Data_t))

/**
 * @brief
 * This declared type represents the Prototype Function for an
 * L2CAP Event Callback. This function will be called whenever a define
 * L2CAP Action occurs within the Bluetooth Protocol Stack that is
 * specified with the specified Bluetooth Stack ID.
 *
 * @details
 * The event information is passed to the user in the
 * #qapi_BLE_L2CA_Event_Data_t structure. This structure contains all the
 * information about the event that occurred.
 *
 * The caller should use the contents of the L2CAP Event Data
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
 * anyway because another L2CAP Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack on which the
 *                                  event occurred.
 *
 * @param[in]  L2CA_Event_Data      Pointer to a structure that contains
 *                                  information about the event that has
 *                                  occurred.
 *
 * @param[in]  CallbackParameter    User-defined value to was supplied as
 *                                  an input parameter from a prior L2CAP
 *                                  request.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_L2CA_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_L2CA_Event_Data_t *L2CA_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * Registers an L2CAP Callback
 * function with the L2CAP Layer associated with the specified Bluetooth
 * Stack ID to handle incoming L2CAP Events destined for the specified
 * LE PSM Number.
 *
 * @details
 * The caller can use the positive return value from this function as the L2CAP_PSMID
 * parameter for the qapi_BLE_L2CA_Un_Register_LE_PSM() function, when the caller
 * wants to unregister the callback.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this Bluetooth
 *                                   Protocol Stack via a call to
 *                                   qapi_BLE_BSC_Initialize().
 *
 * @param[in]  LE_PSM                LE Protocol/Service Multiplexer value to
 *                                   which this callback is to be registered.
 *
 * @param[in]  L2CA_Event_Callback   Function pointer to be used by the L2CAP
 *                                   layer to notify higher layers of L2CAP
 *                                   events.
 *
 * @param[in]  CallbackParameter     User-defined value to be supplied as
 *                                   an input parameter for all event callbacks.
 *
 * @return
 * Positive -- If the function is successful. A positive return value
 *              represents a L2CAP_PSMID that uniquely identifies the callback.
 *              This value is used in the qapi_BLE_L2CA_Un_Register_LE_PSM()
 *              function.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_PSM \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Register_LE_PSM(uint32_t BluetoothStackID, uint16_t LE_PSM, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Unregisters an L2CAP
 * Callback function that was previously registered via a successful
 * call to the qapi_BLE_L2CA_Register_LE_PSM() function.
 *
 * @details
 * If this function completes successfully, the specified Callback
 * will no longer be called when an L2CAP Event occurs for the PSM
 * Number that was associated with the specified L2CAP Callback
 * function.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  L2CAP_PSMID        PSMID value that uniquely identifies the
 *                                callback function for a PSM value.
 *                                The L2CAP_PSMID supplied is the return
 *                                value of a successful call to the
 *                                qapi_BLE_L2CA_Register_LE_PSM() function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                QAPI_BLE_BTPS_ERROR_UNABLE_TO_UNREGISTER_PSM \n
 *                QAPI_BLE_BTPS_ERROR_PSM_NOT_REGISTERED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Un_Register_LE_PSM(uint32_t BluetoothStackID, uint32_t L2CAP_PSMID);

/**
 * @brief
 * Registers an L2CAP Callback
 * function with the L2CAP Layer associated with the specified Bluetooth
 * Stack ID to handle incoming L2CAP Events destined for the specified
 * Fixed Channel.
 *
 * @details
 * The caller can use the return value from this function as the FCID
 * parameter for the qapi_BLE_L2CA_Un_Register_Fixed_Channel() and the
 * qapi_BLE_L2CA_Fixed_Channel_Data_Write() functions when the caller
 * wants to unregister the callback or send fixed channel data
 * (respectively).
 *
 * The ChannelParameters parameter is a placeholder for channel-
 * specific information. At this time, there are no specific
 * parameters assigned for any fixed channel.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this Bluetooth
 *                                   Protocol Stack via a call to
 *                                   qapi_BLE_BSC_Initialize().
 *
 * @param[in]  FixedChannel          L2CAP fixed channel number to register.
 *                                   This value must be greater than: \n
 *                                   QAPI_BLE_L2CAP_CHANNEL_IDENTIFIER_CONNECTIONLESS_CHANNEL \n
 *                                   and less than: \n
 *                                   QAPI_BLE_L2CAP_CHANNEL_IDENTIFIER_MINIMUM_CHANNEL_IDENTIFIER
 *
 * @param[in]  ChannelParameters     Pointer to a channel specific parameter information. Currently,
 *                                   this value is not used and should be passed as NULL.
 *
 * @param[in]  L2CA_Event_Callback   Function pointer to be used by the L2CAP
 *                                   layer to notify higher layers of L2CAP
 *                                   events.
 *
 * @param[in]  CallbackParameter     User-defined value to be supplied as
 *                                   an input parameter for all event callbacks.
 *
 * @return
 * Positive -- If the function is successful. A positive return
 *              value represents an FCID that uniquely identifies the
 *              callback. This value is used in the
 *              qapi_BLE_L2CA_Un_Register_Fixed_Channel() function.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                QAPI_BLE_BTPS_ERROR_UNABLE_TO_REGISTER_EVENT_CALLBACK \n
 *                QAPI_BLE_BTPS_ERROR_ADDING_CALLBACK_INFORMATION \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Register_Fixed_Channel(uint32_t BluetoothStackID, uint16_t FixedChannel, void *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Unregisters an L2CAP
 * callback function that was previously registered via a successful
 * call to the qapi_BLE_L2CA_Register_Fixed_Channel() function.
 *
 * @details
 * If this function completes successfully, the specified
 * vallback will no longer be called when an L2CAP Event occurs
 * for the Channel that was associated with the specified L2CAP
 * Callback function.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  FCID               Fixed channel ID value that uniquely identifies
 *                                the callback function for a fixed channel.
 *                                The FCID supplied value is the return value of a
 *                                successful call to the
 *                                qapi_BLE_L2CA_Register_Fixed_Channel() function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                QAPI_BLE_BTPS_ERROR_NO_CALLBACK_REGISTERED \n
 *                QAPI_BLE_BTPS_ERROR_PSM_NOT_REGISTERED \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Un_Register_Fixed_Channel(uint32_t BluetoothStackID, uint16_t FCID);

/**
 * @brief
 * Requests the creation of
 * a Dynamic LE L2CAP Channel with the specified Bluetooth Board
 * Address.
 *
 * @details
 * If this function is successful, all further Status and Event
 * Notifications will occur through the Callback Function that is
 * specified with this function.
 *
 * A positive return value (LCID) does not mean that a connection
 * already exists, only that the Connection Request has been successfully
 * submitted.
 *
 * The ACL connection to the remote device must already exist before
 * calling this function.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this Bluetooth
 *                                   Protocol Stack via a call to
 *                                   qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR               Device address of the Bluetooth device to
 *                                   which an L2CAP LE logical channel is to
 *                                   be established.
 *
 * @param[in]  LE_PSM                LE Protocol/Service Multiplexer identifier of
 *                                   the service on the remote device to which the
 *                                   logical channel connection is to be made.
 *
 * @param[in]  ChannelParameters     Local device's channel parameters to use
 *                                   with the channel.
 *
 * @param[in]  L2CA_Event_Callback   Function pointer to be used by the L2CAP
 *                                   layer to notify higher layers of L2CAP
 *                                   events.
 *
 * @param[in]  CallbackParameter     User-defined value to be supplied as
 *                                   an input parameter for all event callbacks.
 *
 * @return
 * Positive, nonzero -- Local Channel Identifier (LCID) if
 *              the L2CAP Connection Request was issued successfully.\n
 * Negative -- If an error occurred and the LE Connection Request
 *              was not submitted.  Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_IDENTIFIER_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Connect_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t LE_PSM, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters, qapi_BLE_L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Responds to a L2CAP LE Connect Indication Event.
 *
 * @details
 * This function allows the recipient of the L2CAP Event the option
 * of responding to the Connection Indication with a Positive Accept, or
 * a Negative Accept.
 *
 * This function should be called only upon receipt
 * of an L2CAP LE ConnectIndication Event Callback.
 *
 * A successful return value (zero) does not mean that the connection
 * response was sent, only that the Connection Response has been
 * successfully submitted to the L2CAP Layer associated with the
 * Local Bluetooth Protocol Stack.
 *
 * The ChannelParameters parameter is only required when the Result
 * is set to QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_SUCCESSFUL
 * (that is, the connection is being accepted).
 *
 * Valid values for the Result parameter are:
 *
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_SUCCESSFUL \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_LE_PSM_NOT_REGISTERED \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_NO_RESOURCES \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_AUTHENTICATION \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_AUTHORIZATION \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_ENCRYPTION_KEY_SIZE \n
 *   QAPI_BLE_L2CAP_LE_CONNECT_RESULT_CONNECTION_REFUSED_INSUFFICIENT_ENCRYPTION
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR             Device address of the Bluetooth device to
 *                                 which an L2CAP LE logical channel is
 *                                 already established.
 *
 * @param[in]  Identifier          L2CAP Identifier (this value was passed
 *                                 to the caller in the L2CAP Connect Indication
 *                                 Event).
 *
 * @param[in]  LCID                L2CAP Channel Identifier (this value
 *                                 was passed to the caller in the L2CAP
 *                                 Connect Indication Event).
 *
 * @param[in]  Result              L2CAP LE Connection request result (see
 *                                 above for valid values).
 *
 * @param[in]  ChannelParameters   Local device's channel parameters to
 *                                 use with the channel (if the connection
 *                                 request is being accepted).
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the LE Connection Response
 *              was not submitted. Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Connect_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t Identifier, uint16_t LCID, uint16_t Result, qapi_BLE_L2CA_LE_Channel_Parameters_t *ChannelParameters);

/**
 * @brief
 * Requests the disconnection
 * of a logical L2CAP LE Connection that has previously been established
 * (either created or accepted).
 *
 * @details
 * If this function completes successfully, an L2CAP LE Disconnect
 * Indication will be sent to the L2CAP Callback Function that was
 * handling the L2CAP Events for this connection.
 *
 * It should be noted that, after this function is called (if it
 * completes successfully), the LCID can no longer be
 * used (that is, Logical Connection is terminated).
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  LCID                L2CAP Channel Identifier (this value
 *                                 was passed to the caller in the L2CAP
 *                                 Connect Indication/Confirmation Event)
 *                                 for the channel that will be disconnected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the LE Disconnection Request
 *              was not submitted. Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_CHANNEL_NOT_IN_OPEN_STATE \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_IDENTIFIER_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Disconnect_Request(uint32_t BluetoothStackID, uint16_t LCID);

/**
 * @brief
 * Responds to an L2CAP LE
 * Disconnect Indication Event.
 *
 * @details
 * This function allows the recipient of the L2CAP Event the option
 * of responding to the Disconnection Indication. There is no option
 * provided to reject or deny the request.
 *
 * This function should be called only upon receipt of an L2CAP
 * Disconnect Indication Event Callback.
 *
 * A successful return value (zero) does not mean that the disconnection
 * response was sent, only that the Disconnection Response has been
 * successfully submitted to the L2CAP Layer associated with the Local
 * Bluetooth Protocol Stack. Any further use of the specified CID will
 * be rejected by the stack.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  LCID                L2CAP Channel Identifier (this value
 *                                 was passed to the caller in the L2CAP
 *                                 Connect Indication/Confirmation Event)
 *                                 for the channel that will be disconnected.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the LE Disconnection Response
 *              was not submitted.  Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CONNECTION_STATE \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Disconnect_Response(uint32_t BluetoothStackID, uint16_t LCID);

/**
 * @brief
 * Sends L2CAP Data to
 * the specified L2CAP Connection over a specified Fixed Channel.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR            Bluetooth device address of the device to
 *                                send the specified fixed channel data.
 *
 * @param[in]  FCID               Fixed channel ID that represents the fixed
 *                                channel to send the data. This value is
 *                                not the actual fixed channel itself,
 *                                rather this a value that was returned
 *                                from a successful call to the
 *                                qapi_BLE_L2CA_Register_Fixed_Channel()
 *                                function.
 *
 * @param[in]  Data_Length        Number of octets to be sent over the
 *                                fixed channel.
 *
 * @param[in]  Data               Pointer to a buffer of data to be sent
 *                                over the fixed channel.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the data was not submitted.
 *              Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED \n
 *                    QAPI_BLE_BTPS_ERROR_WRITING_DATA_TO_DEVICE \n
 *                    QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Fixed_Channel_Data_Write(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, uint16_t Data_Length, uint8_t *Data);

/**
 * @brief
 * Sends L2CAP data to
 * the specified L2CAP Connection over a specified Fixed Channel.
 *
 * @details
 * This function is similar to the qapi_BLE_L2CA_Fixed_Channel_Data_Write()
 * function except that this function allows the ability to specify
 * optional queuing parameters. These queuing parameters can specify
 * the following:
 *   - How deep the queue should be (by number of queued packets)
 * This function provides two mechanisms when the (optional) queue
 * thresholds are reached:
 *   - Discard the oldest packet in the queue (and queue the specified
 *     packet)
 *   - Do not queue the packet and inform the caller via a specific
 *     return value
 *
 * If this function returns the Error Code:
 *
 *   QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE,
 *
 * this is a signal to the caller that the requested data
 * could not be sent because the requested data could not be queued
 * in the Outgoing L2CAP Queue. The caller then, must wait for the:
 *
 *   QAPI_BLE_ET_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_E
 *
 * Event before trying to send any more data.
 *
 * If this function is called with QueueingParameters set to NULL,
 * this function operates like the legacy
 * qapi_BLE_L2CA_Fixed_Channel_Data_Write() function.
 *
 * If this function is called with a non-NULL QueueingParameters,
 * the data is queued conditionally. If successful, the
 * return value will indicate the number of packets that are
 * currently queued on the specified channel at the time the
 * function returns.
 *
 * If the L2CA_QUEUEING_FLAG_DISCARD_OLDEST is specified,
 * this function will discard the oldest packet in the queue
 * if the queue threshold criteria is satisfied. This allows
 * a streaming-like mechanism to be implemented (that is, the data
 * will not back up, it will just be discarded).
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this Bluetooth
 *                                  Protocol Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR              Bluetooth device address of the device to
 *                                  send the specified fixed channel data.
 *
 * @param[in]  FCID                 Fixed channel ID that represents the fixed
 *                                  channel to send the data. This value is
 *                                  not the actual fixed channel itself,
 *                                  rather this is a value that was returned
 *                                  from a successful call to the
 *                                  qapi_BLE_L2CA_Register_Fixed_Channel()
 *                                  function.
 *
 * @param[in]  QueueingParameters   Optional pointer to a structure which
 *                                  describes the parameters that dictate
 *                                  how the packet is queued.
 *
 * @param[in]  Data_Length        Number of octets to be sent over the
 *                                fixed channel.
 *
 * @param[in]  Data               Pointer to a buffer of data to be sent
 *                                over the fixed channel.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the data was not submitted.
 *              Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID_TYPE \n
 *                    QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED \n
 *                    QAPI_BLE_BTPS_ERROR_WRITING_DATA_TO_DEVICE \n
 *                    QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR \n
 *                    QAPI_BLE_BTPS_ERROR_NEGOTIATED_MTU_EXCEEDED \n
 *                    QAPI_BLE_BTPS_ERROR_CHANNEL_NOT_IN_OPEN_STATE \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Enhanced_Fixed_Channel_Data_Write(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t FCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data);

/**
 * @brief
 * Sends L2CAP Data to the
 * specified L2CAP LE Connection Oriented channel. This function provides
 * additional functionallity to control the amount of buffer usage for
 * each data channel.
 *
 * @details
 * If this function returns the Error Code
 *
 *   QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE,
 *
 * this is a signal to the caller that the requested data
 * could not be sent because the requested data could not be queued
 * in the Outgoing L2CAP Queue. The caller then, must wait for the
 *
 *   QAPI_BLE_ET_LE_CHANNEL_BUFFER_EMPTY_INDICATION_E
 *
 * Event before trying to send any more data.
 *
 * If this function is called with a non-NULL QueueingParameters,
 * the data is queued conditionally. If successful, the
 * return value will indicate the number of packets/bytes that are
 * currently queued on the specified channel at the time the
 * function returns.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this Bluetooth
 *                                  Protocol Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in]  LCID                 Local CID value used by the L2CAP layer to
 *                                  reference the logical LE channel on which
 *                                  to send the data.
 *
 * @param[in]  QueueingParameters   Optional pointer to a structure which
 *                                  describes the parameters that dictate
 *                                  how the packet is queued.
 *
 * @param[in]  Data_Length          Number of octets to be sent over the
 *                                  logical LE channel.
 *
 * @param[in]  Data                 Pointer to a buffer of data to be sent
 *                                  over the logical LE channel.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative and the data was not submitted.
 *              Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID_TYPE \n
 *                    QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED \n
 *                    QAPI_BLE_BTPS_ERROR_WRITING_DATA_TO_DEVICE \n
 *                    QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR \n
 *                    QAPI_BLE_BTPS_ERROR_NEGOTIATED_MTU_EXCEEDED \n
 *                    QAPI_BLE_BTPS_ERROR_CHANNEL_NOT_IN_OPEN_STATE \n
 *                    QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Enhanced_Dynamic_Channel_Data_Write(uint32_t BluetoothStackID, uint16_t LCID, qapi_BLE_L2CA_Queueing_Parameters_t *QueueingParameters, uint16_t Data_Length, uint8_t *Data);

/**
 * @brief
 * Flushes all data that is
 * current queued for transmission for the specified LE CID.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CID                Local CID value referencing the logical
 *                                channel to flush the queue for.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Flush_Channel_Data(uint32_t BluetoothStackID, uint16_t CID);

/**
 * @brief
 * Provides a mechanism for
 * granting the specified amount of credits for the specified LE CID.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  CID                Local CID value referencing the logical
 *                                channel to grant credits for.
 *
 * @param[in]  CreditsToGrant     Total amount of credits to grant.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative. Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                    QAPI_BLE_BTPS_ERROR_FEATURE_NOT_AVAILABLE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_LE_Grant_Credits(uint32_t BluetoothStackID, uint16_t CID, uint16_t CreditsToGrant);

/**
 * @brief
 * Initiates a request to
 * Update Connection Parameters.
 *
 * @details
 * This function should only be called from an LE Slave, and the local host
 * must have registered for the fixed channel
 * QAPI_BLE_L2CAP_CHANNEL_IDENTIFIER_LE_SIGNALLING_CHANNEL.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR             Device address of the Bluetooth device to
 *                                 which an L2CAP logical channel is already
 *                                 established.
 *
 * @param[in]  IntervalMin         Minimum value for the the connection interval.
 *                                 This should fall within the range: \n
 *                                 QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM  \n
 *                                 QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM
 *
 * @param[in]  IntervalMax         This should be greater than or equal to
 *                                 Conn_Interval_Min and must fall within the range: \n
 *                                 QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MINIMUM \n
 *                                 QAPI_BLE_HCI_LE_CONNECTION_INTERVAL_MAXIMUM \n
 *                                 Both intervals follow the rule: \n
 *                                    Time = N * 1.25 ms
 *
 * @param[in]  SlaveLatency        Slave latency for the connection. This should be in the range: \n
  *                                QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MINIMUM \n
 *                                 QAPI_BLE_HCI_LE_CONNECTION_LATENCY_MAXIMUM
 *
 * @param[in]  TimeoutMultiplier   Supervision timeout multiplier for the LE link. This should
 *                                 be in the range: \n
 *                                 QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MINIMUM \n
 *                                 QAPI_BLE_HCI_LE_SUPERVISION_TIMEOUT_MAXIMUM \n
 *                                 The Supervision_Timeout follows the rule: \n
 *                                    Time = N * 10 ms
 *
 * @return
 * Positive, nonzero value -- If successful submitting the Connection
 *              Parameter Update Request.\n
 * Negative -- If an error occurred and the Connection Parameter Update
 *              Request was not submitted.  Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_ACTION_NOT_ALLOWED \n
 *                    QAPI_BLE_BTPS_ERROR_NO_CALLBACK_REGISTERED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_IDENTIFIER_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_CID_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Connection_Parameter_Update_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t IntervalMin, uint16_t IntervalMax, uint16_t SlaveLatency, uint16_t TimeoutMultiplier);

/**
 * @brief
 * Initiates an L2CAP response
 * to an Update Connection Parameters request.
 *
 * @details
 * This function can only be issued by an LE master, and the local host
 * must have registered for the fixed channel
 * QAPI_BLE_L2CAP_CHANNEL_IDENTIFIER_LE_SIGNALLING_CHANNEL
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR            Device address of the Bluetooth device to
 *                                which an L2CAP logical channel is already
 *                                established.
 * @param[in]  Result             Result of the connection parameter update
 *                                request. This will be one of the following
 *                                values: \n
 *                                L2CAP_CONNECTION_PARAMETER_UPDATE_RESPONSE_RESULT_ACCEPTED \n
 *                                L2CAP_CONNECTION_PARAMETER_UPDATE_RESPONSE_RESULT_REJECTED
 *
 * @return
 * Positive, nonzero value -- If successful submitting the Connection
 *              Parameter Update Response.\n
 * Negative -- If an error occurred and the Connection Parameter Update
 *              Response was not submitted.  Possible values are:
 *              @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_L2CAP_NOT_INITIALIZED \n
 *                    QAPI_BLE_BTPS_ERROR_ACTION_NOT_ALLOWED \n
 *                    QAPI_BLE_BTPS_ERROR_NO_CALLBACK_REGISTERED \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_CID \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_IDENTIFIER_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_ADDING_CID_INFORMATION \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_L2CA_Connection_Parameter_Update_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Result);

/** @} */ /* end_addtogroup qapi_ble_core_l2cap */

#endif

