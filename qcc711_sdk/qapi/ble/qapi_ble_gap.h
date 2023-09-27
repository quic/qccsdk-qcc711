/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
 * @file qapi_ble_gap.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Stack Generic Access
 * Profile API Type Definitions, Constants, and Prototypes.
 *
 * @details
 * The GAP (Generic Access Protocol) programming interface
 * provides features related to:  (1) discovery of other
 * Bluetooth devices, (2) link management aspects of
 * connecting to those devices, and (3) using different
 * levels of security.
 */

#ifndef __QAPI_BLE_GAP_H__
#define __QAPI_BLE_GAP_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_hcitypes.h"  /* Bluetooth HCI Type Definitions/Constants.*/

/** @addtogroup qapi_ble_core_gaple
@{ */

/**
*   Enumeration of the valid GAP discoverability modes.
*/
typedef enum
{
   QAPI_BLE_DM_NON_DISCOVERABLE_MODE_E,
   /**< Indicates the GAP Nondiscoverable mode. */

   QAPI_BLE_DM_LIMITED_DISCOVERABLE_MODE_E,
   /**< Indicates the GAP Limited-discoverable mode. */

   QAPI_BLE_DM_GENERAL_DISCOVERABLE_MODE_E
   /**< Indicates the GAP General-discoverable mode. */
} qapi_BLE_GAP_Discoverability_Mode_t;

/**
*   Enumeration of the valid GAP encryption modes for a connection.
*/
typedef enum
{
   QAPI_BLE_EM_DISABLED_E,
   /**< Indicates the link is not encrypted. */

   QAPI_BLE_EM_ENABLED_E
   /**< Indicates the link encryption is enabled. */
} qapi_BLE_GAP_Encryption_Mode_t;

   /* GAP Low Energy (LE) type definitions and constants. */

/** Minimum allowable LE scan interval (in milliseconds) that can be used
    with the qapi_BLE_GAP_LE_Perform_Scan() function. */
#define QAPI_BLE_MINIMUM_LE_SCAN_INTERVAL                                          3

/** Maximum allowable LE scan interval (in milliseconds) that can be used
    with the qapi_BLE_GAP_LE_Perform_Scan() function. */
#define QAPI_BLE_MAXIMUM_LE_SCAN_INTERVAL                                      10240

/** Minimum allowable LE scan window (in milliseconds) that can be used
    with the qapi_BLE_GAP_LE_Perform_Scan() function. */
#define QAPI_BLE_MINIMUM_LE_SCAN_WINDOW                                            3

/** Maximum allowable LE scan window (in milliseconds) that can be used
    with the qapi_BLE_GAP_LE_Perform_Scan() function. */
#define QAPI_BLE_MAXIMUM_LE_SCAN_WINDOW                                        10240

/** Minimum allowable scan length (in seconds) for limited discoverable mode
    scans. */
#define QAPI_BLE_MINIMUM_LIMITED_DISCOVERABLE_SCAN_LENGTH                         11

/** Minimum allowable scan length (in seconds) for general discoverable mode
    scans. */
#define QAPI_BLE_MINIMUM_GENERAL_DISCOVERABLE_SCAN_LENGTH                         11

/** Minimum allowable advertising interval. */
#define QAPI_BLE_MINIMUM_ADVERTISING_INTERVAL                                     20

/** Maximum allowable advertising interval. */
#define QAPI_BLE_MAXIMUM_ADVERTISING_INTERVAL                                  10240

/** Minimum allowable advertising interval if nonconnectable advertising
    is being used. */
#define QAPI_BLE_MINIMUM_NONCONNECTABLE_ADVERTISING_INTERVAL                     100

/** Minimum primary advertising interval value that may be used with extended
    advertising. */
#define QAPI_BLE_MINIMUM_PRIMARY_ADVERTISING_INTERVAL                            20

/** Maximum primary advertising interval value that may be used with extended
    advertising. */
#define QAPI_BLE_MAXIMUM_PRIMARY_ADVERTISING_INTERVAL                      10485759

/** Minimum periodic advertising interval value that may be used with periodic
    advertising. */
#define QAPI_BLE_MINIMUM_PERIODIC_ADVERTISING_INTERVAL                            8

/** Maximum periodic advertising interval value that may be used with periodic
    advertising. */
#define QAPI_BLE_MAXIMUM_PERIODIC_ADVERTISING_INTERVAL                        81919

/** Minimum advertising handle that may be specified with the extended
    advertising API's. */
#define QAPI_BLE_MINIMUM_ADVERTISING_HANDLE                                       0

/** Maximum advertising handle that may be specified with the extended
    advertising API's. */
#define QAPI_BLE_MAXIMUM_ADVERTISING_HANDLE                                    0xEF

/** Minimum extended scan interval. This is specified in
    milli-seconds. */
#define QAPI_BLE_MINIMUM_EXTENDED_SCAN_INTERVAL                                   3

/** Maximum extended scan interval. This is specified in
    milli-seconds. */
#define QAPI_BLE_MAXIMUM_EXTENDED_SCAN_INTERVAL                               40959

/** Minimum extended scan window. This is specified in
    milli-seconds. */
#define QAPI_BLE_MINIMUM_EXTENDED_SCAN_WINDOW                                     3

/** Maximum extended scan window. This is specified in
    milli-seconds. */
#define QAPI_BLE_MAXIMUM_EXTENDED_SCAN_WINDOW                                 40959

/** Minimum extended advertising duration. This is specified in
    milli-seconds. */
#define QAPI_BLE_MINIMUM_EXTENDED_ADVERTISING_DURATION                            0

/** Maximum extended advertising duration. This is specified in
    milli-seconds. */
#define QAPI_BLE_MAXIMUM_EXTENDED_ADVERTISING_DURATION                       655350

/** Minimum extended scan duration. This is specified in
    milli-seconds. */
#define QAPI_BLE_MINIMUM_EXTENDED_SCAN_DURATION                                  10

/** Maximum extended scan duration. This is specified in
    milli-seconds. */
#define QAPI_BLE_MAXIMUM_EXTENDED_SCAN_DURATION                              655350

/** Minimum extended scan period. This is specified in
    milli-seconds. */
#define QAPI_BLE_MINIMUM_EXTENDED_SCAN_PERIOD                                  1280

/** Maximum extended scan period. This is specified in
    milli-seconds. */
#define QAPI_BLE_MAXIMUM_EXTENDED_SCAN_PERIOD                              83884800

/** Minimum allowable connection interval (min) that may be specified
    (in milliseconds). */
#define QAPI_BLE_MINIMUM_MINIMUM_CONNECTION_INTERVAL                               8

/** Maximum allowable connection interval (min) that may be specified
    (in milliseconds). */
#define QAPI_BLE_MAXIMUM_MINIMUM_CONNECTION_INTERVAL                            4000

/** Minimum allowable connection interval (max) that may be specified
    (in milliseconds). */
#define QAPI_BLE_MINIMUM_MAXIMUM_CONNECTION_INTERVAL                               8

/** Maximum allowable connection interval (max) that may be specified
    (in milliseconds). */
#define QAPI_BLE_MAXIMUM_MAXIMUM_CONNECTION_INTERVAL                            4000

/** Bit flag that indicates that advertising channel 37 is enabled for advertising. */
#define QAPI_BLE_GAP_LE_ADVERTISING_CHANNEL_MAP_USE_CHANNEL_37                     (QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_37)

/** Bit flag that indicates that advertising channel 38 is enabled for advertising. */
#define QAPI_BLE_GAP_LE_ADVERTISING_CHANNEL_MAP_USE_CHANNEL_38                     (QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_38)

/** Bit flag that indicates that advertising channel 39 is enabled for advertising. */
#define QAPI_BLE_GAP_LE_ADVERTISING_CHANNEL_MAP_USE_CHANNEL_39                     (QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_CHANNEL_39)

/** Bit flag that indicates that all advertising channels are enabled for advertising. */
#define QAPI_BLE_GAP_LE_ADVERTISING_CHANNEL_MAP_USE_ALL_CHANNELS                   (QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_ENABLE_ALL_CHANNELS)

/** Minimum allowable slave latency for a BLE connection (in connection events). */
#define QAPI_BLE_MINIMUM_SLAVE_LATENCY                                             0

/** Maximum allowable slave latency for a BLE connection (in connection events). */
#define QAPI_BLE_MAXIMUM_SLAVE_LATENCY                                           500

/** Minimum allowable link supervision timeout (in milliseconds). */
#define QAPI_BLE_MINIMUM_LINK_SUPERVISION_TIMEOUT                                100

/** Maximum allowable link supervision timeout (in milliseconds). */
#define QAPI_BLE_MAXIMUM_LINK_SUPERVISION_TIMEOUT                              32000

/** Minimum allowable connection event length (in milliseconds). */
#define QAPI_BLE_MINIMUM_CONNECTION_EVENT_LENGTH                             0

/** Maximum allowable connection event length (in milliseconds). */
#define QAPI_BLE_MAXIMUM_CONNECTION_EVENT_LENGTH                         40959

/** Maximum number of extended advertising sets that may be pased to the
    qapi_BLE_GAP_LE_Enable_Extended_Advertising() function when
    enabling/disabling extended advertising. */
#define MAXIMUM_ENABLE_DISABLE_EXTENDED_ADVERTISING_SETS              0x3F

/** Minimum synchronization timeout. This value is specified in
    milli-seconds. */
#define MINIMUM_SYNCHRONIZATION_TIMEOUT                                100

/** Maximum synchronization timeout. This value is specified in
    milli-seconds. */
#define MAXIMUM_SYNCHRONIZATION_TIMEOUT                             163840

/** Minimum allowable resolvable private address timeout that may be specified
    in call to qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout() (in seconds). */
#define QAPI_BLE_MINIMUM_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT                   1

/** Maximum allowable resolvable private address timeout that may be specified
    in call to qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout() (in seconds). */
#define QAPI_BLE_MAXIMUM_RESOLVABLE_PRIVATE_ADDRESS_TIMEOUT              0xA1B8

/** Minimum allowable encryption key size that can be passed to
    qapi_BLE_GAP_LE_Pair_Remote_Device() and
    qapi_BLE_GAP_LE_Authentication_Response() functions. */
#define QAPI_BLE_GAP_LE_MINIMUM_ENCRYPTION_KEY_SIZE                       7

/** Maximum allowable encryption key size that can be passed to
    qapi_BLE_GAP_LE_Pair_Remote_Device() and
    qapi_BLE_GAP_LE_Authentication_Response() functions. */
#define QAPI_BLE_GAP_LE_MAXIMUM_ENCRYPTION_KEY_SIZE                      16

/** This macro verifies that the encryption key size input is valid. */
#define QAPI_BLE_GAP_LE_ENCRYPTION_KEY_SIZE_VALID(_x)   (((_x) >= QAPI_BLE_GAP_LE_MINIMUM_ENCRYPTION_KEY_SIZE) && ((_x) <= QAPI_BLE_GAP_LE_MAXIMUM_ENCRYPTION_KEY_SIZE))

/** This macro tests if a random address is a static random address. */
#define QAPI_BLE_GAP_LE_TEST_STATIC_ADDRESS_BITS(_x)    \
   ((((_x).BD_ADDR5) & (1 << 6)) && (((_x).BD_ADDR5) & (1 << 7)))

/** This macro tests if a random address is a non-resolvable random address. */
#define QAPI_BLE_GAP_LE_TEST_NONRESOLVABLE_ADDRESS_BITS(_x)    \
   ((!(((_x).BD_ADDR5) & (1 << 6))) && (!(((_x).BD_ADDR5) & (1 << 7))))

/** This macro tests if a random address is a resolvable private address. */
#define QAPI_BLE_GAP_LE_TEST_RESOLVABLE_ADDRESS_BITS(_x)    \
   ((((_x).BD_ADDR5) & (1 << 6)) && (!(((_x).BD_ADDR5) & (1 << 7))))

/** Maximum number of digits that may be entered as an LE passkey. */
#define QAPI_BLE_GAP_LE_PASSKEY_MAXIMUM_NUMBER_OF_DIGITS                           6

/**
*  Enumeration of the valid types of scans that may be
*  started via a call to qapi_BLE_GAP_LE_Perform_Scan().
*/
typedef enum
{
   QAPI_BLE_ST_PASSIVE_E,
   /**< Indicates that a passive scan (receive only) should be started. */

   QAPI_BLE_ST_ACTIVE_E
   /**< Indicates that a active scan (transmit/receive) should be started. */
} qapi_BLE_GAP_LE_Scan_Type_t;

/**
*  Enumeration of the valid GAP filter policies that may be configured.
*  Note #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E and #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
*  may only be used with a Bluetooth 4.2 or grather controller and may only
*  be used with the qapi_BLE_GAP_LE_Perform_Scan() API.
*/
typedef enum
{
   QAPI_BLE_FP_NO_FILTER_E,
   /**< Indicates that no filtering should be done. */

   QAPI_BLE_FP_WHITE_LIST_E,
   /**< Indicates that filtering should be done based on the white list. */

   QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E,
   /**< Indicates that no filtering should be done and that directed advertisements
        containing a resolvable private addresses (RPA) should be allowed. */

   QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
   /**< Indicates that filtering should be done based on the white list and
        that directed advertisements containing an RPA should be allowed. */
} qapi_BLE_GAP_LE_Filter_Policy_t;

/**
*  Enumeration of the valid GAP periodic filter policies.
*/
typedef enum
{
   QAPI_BLE_PFP_NO_FILTER_E,
   /**< Use the specified advertising SID, remote device address type, and remote device address. */

   QAPI_BLE_PFP_PERIODIC_ADVERTISER_LIST_E
   /**< Use the periodic advertisers list.  */
} qapi_BLE_GAP_LE_Periodic_Filter_Policy_t;

/**
*  Enumeration of the valid advertising report types.
*/
typedef enum
{
   QAPI_BLE_RT_CONNECTABLE_UNDIRECTED_E,
   /**< Indicates an undirected connectable report. */

   QAPI_BLE_RT_CONNECTABLE_DIRECTED_E,
   /**< Indicates a directed connectable report. */

   QAPI_BLE_RT_SCANNABLE_UNDIRECTED_E,
   /**< Indicates an undirected scannable report. */

   QAPI_BLE_RT_NON_CONNECTABLE_UNDIRECTED_E,
   /**< Indicates a non-connectable undirected report. */

   QAPI_BLE_RT_SCAN_RESPONSE_E
   /**< Indicates a scan response report. */
} qapi_BLE_GAP_LE_Advertising_Report_Type_t;

/**
*  Enumeration of the GAP LE connectability
*  mode that may be used.
*/
typedef enum
{
   QAPI_BLE_LCM_NON_CONNECTABLE_E,
   /**< Indicates non-connectable mode. */

   QAPI_BLE_LCM_CONNECTABLE_E,
   /**< Indicates connectable mode. */

   QAPI_BLE_LCM_DIRECT_CONNECTABLE_E,
   /**< Indicates directed connectable mode. */

   QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E
   /**< Indicates low duty cycle directed connectable mode. */
} qapi_BLE_GAP_LE_Connectability_Mode_t;

/**
*  Enumeration of the GAP LE pairability mode. These types
*  are used with the qapi_BLE_GAP_LE_Set_Pairability_Mode() and the
*  qapi_BLE_GAP_LE_Query_Pairability_Mode() functions. If the
*  QAPI_BLE_LPM_PAIRABLE_MODE_ENABLE_EXTENDED_EVENTS_E is used,
*  the following events must be handled by the application:
*  - QAPI_BLE_LAT_KEYPRESS_NOTIFICATION_E
*  - QAPI_BLE_LAT_EXTENDED_PAIRING_REQUEST_E
*  - QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E
*  - QAPI_BLE_LAT_EXTENDED_OUT_OF_BAND_INFORMATION_E
*/
typedef enum
{
   QAPI_BLE_LPM_NON_PAIRABLEMODE_E,
   /**< Indicates Nonpairable mode.  */

   QAPI_BLE_LPM_PAIRABLE_MODE_E,
   /**< Indicates Pairable mode.  */

   QAPI_BLE_LPM_PAIRABLE_MODE_ENABLE_EXTENDED_EVENTS_E
   /**< Indicates Pairable mode with enabling of extended events. */
} qapi_BLE_GAP_LE_Pairability_Mode_t;

/**
* The following enumerated type represents the different IO
* Capabilities an LE device may have (used during pairing
* procedure).
*/
typedef enum
{
   QAPI_BLE_LIC_DISPLAY_ONLY_E,
   /**< Indicates device can only display a value. */

   QAPI_BLE_LIC_DISPLAY_YES_NO_E,
   /**< Indicates device can only display a value and ask
        a yes/no confirmation. */

   QAPI_BLE_LIC_KEYBOARD_ONLY_E,
   /**< Indicates device can only input a value. */

   QAPI_BLE_LIC_NO_INPUT_NO_OUTPUT_E,
   /**< Indicates device has no input and no output capability. */

   QAPI_BLE_LIC_KEYBOARD_DISPLAY_E
   /**< Indicates device can both input and display a value. */
} qapi_BLE_GAP_LE_IO_Capability_t;

/** The following enumerated type represents currently defined
*   Keypress actions that can be specified with the
*   authentication events.  This is only used to drive a display
*   that shows the status of a passkey input.
*/
typedef enum
{
   QAPI_BLE_LKP_ENTRY_STARTED_E,
   /**< Indicates passkey input has started. */

   QAPI_BLE_LKP_DIGIT_ENTERED_E,
   /**< Indicates a digit has been entered. */

   QAPI_BLE_LKP_DIGIT_ERASED_E,
   /**< Indicates a digit has been erased. */

   QAPI_BLE_LKP_CLEARED_E,
   /**< Indicates that passkey has been cleared. */

   QAPI_BLE_LKP_ENTRY_COMPLETED_E
   /**< Indicates passkey input has completed. */
} qapi_BLE_GAP_LE_Keypress_t;

/**  The following enumerated type represents the different Bonding
*    types that an LE device may set.
*/
typedef enum
{
   QAPI_BLE_LBT_NO_BONDING_E,
   /**< Indicates no bonding type. */

   QAPI_BLE_LBT_BONDING_E
   /**< Indicates bonding type. */
} qapi_BLE_GAP_LE_Bonding_Type_t;

/** Enumerated type that represents the different LE
*   Address Types. The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and
*   QAPI_BLE_LAT_RANDOM_IDENTITY_E types are only valid
*   to be used or returned from a v4.2 or greater
*   Bluetooth controller.
*   Only the #QAPI_BLE_LAT_PUBLIC_E and #QAPI_BLE_LAT_RANDOM_E
*   types may be used to API calls where the local Bluetooth
*   device is a 4.0 or 4.1 version chipset.
*   The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and
*   #QAPI_BLE_LAT_RANDOM_IDENTITY_E are both valid to be
*   returned in LE Events dispatched from a 4.2 or greater
*   Bluetooth controller. These types may also be used in
*   API calls that take this enumerated type for the Peer's
*   Address Type (not for the Local Address Type) if the
*   local Bluetooth controller is a version 4.2 or greater
*   controller. The #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E
*   and #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E are only
*   valid to be used for the Local Address Type parameter to the
*   qapi_BLE_GAP_LE_Advertising_Enable(),
*   qapi_BLE_GAP_LE_Create_Connection() and
*   qapi_BLE_GAP_LE_Perform_Scan() APIs.
*/
typedef enum
{
   QAPI_BLE_LAT_PUBLIC_E,
   /**< Indicates a public address. */

   QAPI_BLE_LAT_RANDOM_E,
   /**< Indicates a random address. */

   QAPI_BLE_LAT_PUBLIC_IDENTITY_E,
   /**< Indicates a public identity address. */

   QAPI_BLE_LAT_RANDOM_IDENTITY_E,
   /**< Indicates a random identity address. */

   QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E,
   /**< Indicates the local use of a resolvable private address with the fallback
        of using the devices public address. */

   QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E,
   /**< Indicates the local use of a resolvable private address with the fallback
        of using currently configured random address. */

   QAPI_BLE_LAT_ANONYMOUS_E
   /**< Indicates that address is that of anonymous device (address not present
        in advertising packet. */
} qapi_BLE_GAP_LE_Address_Type_t;

/**
 * Structure that represents the type of connectability parameters that
 * may be passed into the qapi_BLE_GAP_LE_Advertising_Enable() function.
 *
 * The Direct_Address_Type and Direct_Address fields are only used if the
 * Connectability_Mode field is set to QAPI_BLE_LCM_DIRECT_CONNECTABLE_E
 * or #QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E.
 *
 * The following enumerated types may be used with the Own_Address_Type
 * member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E
 *   @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E
 *
 * The last two types (QAPI_BLE_LAT_RESOLVABLE_FALLBACK_XXX) indicate
 * that the controller should generate a Resolvable Private Address
 * based on the local IRK from the controller's resolving list. If no
 * local IRK is found for the specified device, the controller will
 * fall back to using either the Public Address
 * (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E) or using the random
 * address that has been set via the
 * qapi_BLE_GAP_LE_Set_Random_Address() API function
 * (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E).
 *
 * If either of the #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E or
 * #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E types are specified with
 * the Own_Address_Type member, the Direct_Address_Type and
 * Direct_Address members must be specified and must correspond to the
 * Peer's Address Type and Address that can be used by the controller to
 * search the resolving list.
 *
 * The following enumerated types may be used with the
 * Direct_Address_Type member:
 *
 *   @li  QAPI_BLE_LAT_PUBLIC_E
 *   @li  QAPI_BLE_LAT_RANDOM_E
 *   @li  QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li  QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * indicate that the Direct_Address member is an identity address (a
 * semipermanent address that can be used to refer to the device) that
 * was received from the remote device (along with the remote device's
 * IRK) during a successful LE Pairing process.
 *
 * If the local Bluetooth Controller is a version 4.0 or a version 4.1
 * compliant controller, for both the Own_Address_Type and
 * Direct_Address_Type member's, the only valid enumerated types are the
 * #QAPI_BLE_LAT_PUBLIC_E and QAPI_BLE_LAT_RANDOM_E enumerated types.
 */
typedef struct qapi_BLE_GAP_LE_Connectability_Parameters_s
{
   /**
    * Connectability mode to use for LE advertising.
    */
   qapi_BLE_GAP_LE_Connectability_Mode_t Connectability_Mode;

   /**
    * Address type of the local device.
    */
   qapi_BLE_GAP_LE_Address_Type_t        Own_Address_Type;

   /**
    * Direct address type of the remote device.
    */
   qapi_BLE_GAP_LE_Address_Type_t        Direct_Address_Type;

   /**
    * Direct address of the remote device.
    */
   qapi_BLE_BD_ADDR_t                    Direct_Address;
} qapi_BLE_GAP_LE_Connectability_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Connectability_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTABILITY_PARAMETERS_SIZE                     (sizeof(qapi_BLE_GAP_LE_Connectability_Parameters_t))

/**
 * Structure that represents the type of advertising parameters.
 *
 *  The following types may not be used with the Scan_Request_Filter and
 *  Connect_Request_Filter members of the following structure:
 *
 *   @li QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 *   @li QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Parameters_s
{
   /**
    * Minimum advertising interval in milliseconds.
    */
   uint16_t                        Advertising_Interval_Min;

   /**
    * Maximum advertising interval in milliseconds.
    */
   uint16_t                        Advertising_Interval_Max;

   /**
    * Bitmask that controls the advertising channels that are used for
    * advertising.
    */
   uint8_t                         Advertising_Channel_Map;

   /**
    * Scan request filter.
    */
   qapi_BLE_GAP_LE_Filter_Policy_t Scan_Request_Filter;

   /**
    * Connection request filter.
    */
   qapi_BLE_GAP_LE_Filter_Policy_t Connect_Request_Filter;
} qapi_BLE_GAP_LE_Advertising_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_PARAMETERS_SIZE                        (sizeof(qapi_BLE_GAP_LE_Advertising_Parameters_t))

/**
 * Structure that represents the type of connection parameters that may
 * be passed into the qapi_BLE_GAP_LE_Create_Connection() function.
 *
 * All members of this structure are specified in milliseconds, except
 * Slave_Latency, which is specified by the number of connection events.
 */
typedef struct qapi_BLE_GAP_LE_Connection_Parameters_s
{
   /**
    * Maximum connection interval.
    */
   uint16_t Connection_Interval_Min;

   /**
    * Minimum connection interval.
    */
   uint16_t Connection_Interval_Max;

   /**
    * Slave latency.
    */
   uint16_t Slave_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t Supervision_Timeout;

   /**
    * Minimum connection length.
    */
   uint16_t Minimum_Connection_Length;

   /**
    * Maximum connection length.
    */
   uint16_t Maximum_Connection_Length;
} qapi_BLE_GAP_LE_Connection_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_PARAMETERS_SIZE                         (sizeof(qapi_BLE_GAP_LE_Connection_Parameters_t))

/**
 * This structure is a container structure for all connection parameters
 * that are present for all LE connections.
 *
 * All members of this structure are specified in milliseconds except
 * Slave_Latency, which is specified by the number of connection
 * intervals.
 */
typedef struct qapi_BLE_GAP_LE_Current_Connection_Parameters_s
{
   /**
    * Connection interval.
    */
   uint16_t Connection_Interval;

   /**
    * Slave latency.
    */
   uint16_t Slave_Latency;

   /**
    * Supervision timeout.
    */
   uint16_t Supervision_Timeout;
} qapi_BLE_GAP_LE_Current_Connection_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Current_Connection_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_CURRENT_CONNECTION_PARAMETERS_SIZE                 (sizeof(qapi_BLE_GAP_LE_Current_Connection_Parameters_t))

/**
 * Structure that represents the data that
 * may be passed into the qapi_BLE_GAP_LE_AES_CCM_Decrypt() function.
 *
 */
typedef struct qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_s
{
   /**
    * Key to use for decryption.
    */
   qapi_BLE_Encryption_Key_t        Decryption_Key;

   /**
    * Length of the Nonce, specified by the Nonce pointer (7-13 bytes in length).
    */
   uint8_t                          Nonce_Length;

    /**
    * Pointer to the Nonce to use when decrypting.
    */
   uint8_t                         *Nonce;

   /**
    * Length of the data to be decrypted.
    */
   uint32_t                         Encrypted_Data_Length;

   /**
    * Length of the plaintext data that was decrypted (out).
    */
   uint32_t                         Plaintext_Data_Length;

    /**
    * Pointer to the data to be decrypted (must be Encrypted Data + MIC, that is
    * MIC must be last 4 bytes of the data).   Data will be decrypted in
    * place.
    */
   uint8_t                         *Encrypted_Data;
} qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_t;

/**  Size of the #qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_AES_CCM_DECRYPTION_PARAMETERS_SIZE    (sizeof(qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_t))

/**
 * Structure that represents the data that
 * may be passed into the qapi_BLE_GAP_LE_AES_CCM_Encrypt() function.
 */
typedef struct qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_s
{
   /**
    * Key to use for encryption.
    */
   qapi_BLE_Encryption_Key_t        Encryption_Key;

   /**
    * Length of the Nonce, specified by the Nonce pointer (7-13 bytes in length).
    */
   uint8_t                          Nonce_Length;

    /**
    * Pointer to the Nonce to use when Encrypting.
    */
   uint8_t                         *Nonce;

   /**
    * Length of the data to be Encrypted.
    */
   uint32_t                         Plaintext_Data_Length;

   /**
    * Length of the encrypted data (out).
    */
   uint32_t                         Encrypted_Data_Length;

    /**
    * Pointer to the data to be Encrypted (must be large enough to contain the 4 byte MIC
    * at the end of the plaintext data, that is Plaintext_Data_Length + 4). Data will be
    * encrypted in place and MIC added to the end of the plaintext data.
    */
   uint8_t                         *Plaintext_Data;
} qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_t;

/**  Size of the #qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_AES_CCM_ENCRYPTION_PARAMETERS_SIZE    (sizeof(qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_t))

/**
 * This structure is a container structure for a pair of LE device
 * addresses.
*
 * The following enumerated types may be set with the
 * Local_Address_Type member:
 *
 * @li QAPI_BLE_LAT_PUBLIC_E
 * @li QAPI_BLE_LAT_RANDOM_E
 *
 * The following enumerated types may be set with the
 * Remote_Address_Type member:
 *
 * @li QAPI_BLE_LAT_PUBLIC_E
 * @li QAPI_BLE_LAT_RANDOM_E
 * @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 * @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 */
typedef struct qapi_BLE_GAP_LE_Address_Pair_s
{
   /**
    * Local address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Local_Address_Type;

   /**
    * Remote address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Remote_Address_Type;

   /**
    * Local address.
    */
   qapi_BLE_BD_ADDR_t             Local_Address;

   /**
    * Remote address.
    */
   qapi_BLE_BD_ADDR_t             Remote_Address;
} qapi_BLE_GAP_LE_Address_Pair_t;

/** Size of the #qapi_BLE_GAP_LE_Address_Pair_t structure. */
#define QAPI_BLE_GAP_LE_ADDRESS_PAIR_SIZE                                  (sizeof(qapi_BLE_GAP_LE_Address_Pair_t))

/**
 * Structure that represents the data structure for a White List entry
 * that is used with the White List Management functions in this module.
 *
 * The following enumerated types may be used with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * indicate that the Address member is an identity address (a
 * semipermanent address that can be used to refer to the device) that
 * was received from the remote device (along with the remote device's
 * IRK) during a successful LE Pairing process.
 */
typedef struct qapi_BLE_GAP_LE_White_List_Entry_s
{
   /**
    * Remote address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t             Address;
} qapi_BLE_GAP_LE_White_List_Entry_t;

/** Size of the #qapi_BLE_GAP_LE_White_List_Entry_t structure. */
#define QAPI_BLE_GAP_LE_WHITE_LIST_ENTRY_SIZE                              (sizeof(qapi_BLE_GAP_LE_White_List_Entry_t))

/**
 * Structure that represents the data structure for a Resolving List
 * entry that is used with the Resolving List Management functions in
 * this module.
 *
 * The following enumerated types may be used with the
 * Peer_Identity_Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * Note that for this structure, #QAPI_BLE_LAT_PUBLIC_E means the same
 * thing as QAPI_BLE_LAT_PUBLIC_IDENTITY_E (and #QAPI_BLE_LAT_RANDOM_E
 * and API_BLE_LAT_RANDOM_IDENTITY_E are equivalent). Both types are
 * allowed with this structure, since the specification is not consistent
 * when it comes to address types and some legacy structures will return
 * #QAPI_BLE_LAT_PUBLIC_E/QAPI_BLE_LAT_RANDOM_E for the peer's identity
 * address (see the #qapi_BLE_GAP_LE_Identity_Information_t structure).
 * So we allow this to be flexible.
 *
 * The Peer_Identity_Address member must be the address
 * received (along with the Peer_Identity_Address_Type and the Peer_IRK)
 * from the remote device during a successful LE Pairing Process.
 *
 * The APIs that use this structure are only valid to be called if the
 * local controller is a 4.2 controller.
 */
typedef struct qapi_BLE_GAP_LE_Resolving_List_Entry_s
{
   /**
    * Peer identity address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t  Peer_Identity_Address_Type;

   /**
    * Peer identity address.
    */
   qapi_BLE_BD_ADDR_t              Peer_Identity_Address;

   /**
    * Peer Identity Resolving Key (IRK).
    */
   qapi_BLE_Encryption_Key_t       Peer_IRK;

   /**
    * Local Identity Resolving Key (IRK).
    */
   qapi_BLE_Encryption_Key_t       Local_IRK;
} qapi_BLE_GAP_LE_Resolving_List_Entry_t;

/** Size of the #qapi_BLE_GAP_LE_Resolving_List_Entry_t structure. */
#define QAPI_BLE_GAP_LE_RESOLVING_LIST_ENTRY_SIZE                          (sizeof(qapi_BLE_GAP_LE_Resolving_List_Entry_t))

/**
 * Enumeration of the valid valid privacy modes that may be set
 * for a resolving list entry via the
 * qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode() API (5.0 or greater
 * controller).  All devices in resolving list default to network privacy
 * (only RPAs accepted for devices in resolving list with non-zero Peer
 * IRK's).
 */
typedef enum
{
   QAPI_BLE_PM_NETWORK_PRIVACY_E,
   /**< Network privacy mode.  */

   QAPI_BLE_PM_DEVICE_PRIVACY_E
   /**< Device privacy mode.  */
} qapi_BLE_GAP_LE_Privacy_Mode_t;

/**
 * Structure that represents the data structure that is the
 * structure that represents the data for an individual Periodic
 * Advertising List entry that is used with the Periodic Advertising
 * List Management functions in this module.
 *
 * The following enumerated types may be used with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * Note that for this structure, #QAPI_BLE_LAT_PUBLIC_E means the same
 * thing as QAPI_BLE_LAT_PUBLIC_IDENTITY_E (and #QAPI_BLE_LAT_RANDOM_E
 * and API_BLE_LAT_RANDOM_IDENTITY_E are equivalent). Both types are
 * allowed with this structure, since the specification is not consistent
 * when it comes to address types and some legacy structures will return
 * #QAPI_BLE_LAT_PUBLIC_E/QAPI_BLE_LAT_RANDOM_E for the peer's identity
 * address (see the #qapi_BLE_GAP_LE_Identity_Information_t structure).
 * So we allow this to be flexible.
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_s
{
   /**
    * Address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Address_Type;

   /**
    * Address.
    */
   qapi_BLE_BD_ADDR_t             Address;

   /**
    * Identifies the advertising set.
    */
   uint8_t                        AdvertisingSID;
} qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t structure. */
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_LIST_ENTRY_SIZE               (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t))

/** Enumeration of the possible
*   transmitter/receiver PHY values.
*/
typedef enum
{
   QAPI_BLE_LPT_PHY_LE_1M_E,
   /**< Indicates the LE 1 megabit PHY. */

   QAPI_BLE_LPT_PHY_LE_2M_E,
   /**< Indicates the LE 2 megabit PHY. */

   QAPI_BLE_LPT_PHY_LE_CODED_E
   /**< Indicates the LE coded PHY. */
} qapi_BLE_GAP_LE_PHY_Type_t;

/** Indicates no PHY preference to qapi_BLE_GAP_LE_Set_Connection_PHY() and
    qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_NO_PHY_PREFERENCE                0x00000000

/** Indicates preference for LE 1 megabit PHY to qapi_BLE_GAP_LE_Set_Connection_PHY()
    and qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_1M_PHY                           0x00000001

/** Indicates preference for LE 2 megabit PHY to qapi_BLE_GAP_LE_Set_Connection_PHY()
    and qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_2M_PHY                           0x00000002

/** Indicates preference for LE coded PHY to qapi_BLE_GAP_LE_Set_Connection_PHY()
    and qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_CODED_PHY                        0x00000004

/** Indicates preference for LE coded PHY S2 coding to qapi_BLE_GAP_LE_Set_Connection_PHY()
    and qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_CODED_PHY_TX_S2_CODING           0x00000010

/** Indicates preference for LE coded PHY S8 coding to qapi_BLE_GAP_LE_Set_Connection_PHY()
    and qapi_BLE_GAP_LE_Query_Connection_PHY() APIs for the TxPHYSPreference
    and RxPHYSPreference bit mask parameters. */
#define QAPI_BLE_GAP_LE_PHY_PREFERENCE_CODED_PHY_TX_S8_CODING           0x00000020

/**
 * Structure that represents the parameters that may be set when
 * configuring an advertising set.
 *
 * If the
 * #QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_USE_LEGACY_PDUS
 * bit is NOT set in the Advertising_Event_Properties member then the
 * advertising may not be both connectable and scannable. That is, either the
 * #QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_CONNECTABLE bit
 * may be set or the
 * #QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_SCANNABLE bit
 * may be set, but not both. In addition high duty cycle directed
 * advertising is not allowed in this mode.
 *
 * Primary_Advertising_Interval_Min and Primary_Advertising_Interval_Max
 * are specified in milliseconds.  Primary_Advertising_Interval_Min must
 * be less than or equal to Primary_Advertising_Interval_Max and should
 * be less than Primary_Advertising_Interval_Max to allow the controller
 * flexibility in scheduling.  Both must be in range: [
 * #QAPI_BLE_MINIMUM_PRIMARY_ADVERTISING_INTERVAL,
 * #QAPI_BLE_MAXIMUM_PRIMARY_ADVERTISING_INTERVAL ].
 *
 * If directed advertising is selected the Peer_Address_Type and
 * Peer_Address members must be valid.   This specifies the device that
 * the advertising packets will be directed towards.
 *
 * If either of the #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E or
 * #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E types are specified with
 * the Own_Address_Type member then the Peer_Address_Type and
 * Peer_Address members MUST specified and must correspond to the Peer's
 * Address Type and Address that can be used by the controller to search
 * the resolving list.
 *
 * The following enumerated types may be used with the Peer_Address_Type
 * member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The latPublicIdentity and latRandomIdentity indicate that the Address
 * member is an identity address (a semi-permanent address that can be
 * used to refer to the device) that was received from the remote device
 * (along with the remote device's IRK) during a successful LE Pairing
 * process.
 *
 * For the Primary Advertising PHY, only the #QAPI_BLE_LPT_PHY_LE_1M_E and
 * #QAPI_BLE_LPT_PHY_LE_CODED_E types may be specified.  In addition if
 * legacy advertising PDUs are specified then only the
 * #QAPI_BLE_LPT_PHY_LE_1M_E is valid.
 *
 * The following types may NOT be used with the Scan_Request_Filter and
 * Connect_Request_Filter members of the following structure:
 *
 *   @li QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 *   @li QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
 *
 */
typedef struct qapi_BLE_GAP_LE_Extended_Advertising_Parameters_s
{
   /**
    * Bit mask that represents the properties for extended advertising.
    * Valid values have the form
    * QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_XXX.
    */
   uint16_t                        Advertising_Event_Properties;

   /**
    * Minimum primary advertising interval.
    */
   uint32_t                        Primary_Advertising_Interval_Min;

   /**
    * Maximum primary advertising interval.
    */
   uint32_t                        Primary_Advertising_Interval_Max;

   /**
    * Bit mask that specifies the primary advertising channels to use
    * for extended advertising. Valid values have the form
    * QAPI_BLE_HCI_LE_ADVERTISING_CHANNEL_MAP_XXX.
    */
   uint8_t                         Primary_Advertising_Channel_Map;

   /**
    * Local device's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t  Own_Address_Type;

   /**
    * Peer's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t  Peer_Address_Type;

   /**
    * Peer's address.
    */
   qapi_BLE_BD_ADDR_t              Peer_Address;

   /**
    * Scan request filter.
    */
   qapi_BLE_GAP_LE_Filter_Policy_t Scan_Request_Filter;

   /**
    * Connection request filter.
    */
   qapi_BLE_GAP_LE_Filter_Policy_t Connect_Request_Filter;

   /**
    * Advertising Tx Power to use for extended advertising. The
    * controller choose to use a smaller value.
    */
   int8_t                          Advertising_Tx_Power;

   /**
    * Primary advertising PHY.
    */
   qapi_BLE_GAP_LE_PHY_Type_t      Primary_Advertising_PHY;

   /**
    * Defines when the controller shall send the AUX_ADV_IND PDU.
    */
   uint8_t                         Secondary_Advertising_Max_Skip;

   /**
    * Secondary advertising PHY.
    */
   qapi_BLE_GAP_LE_PHY_Type_t      Secondary_Advertising_PHY;

   /**
    * Advertising SID.
    */
   uint8_t                         Advertising_SID;

   /**
    * Enables scan request notifications.
    */
   boolean_t                       Scan_Request_Notifications_Enable;
} qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t
    structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_PARAMETERS_SIZE                  (sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t))

/** Indicates the host has no preference on the Tx Power to use for
    with the advertising set. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_ADVERTISING_TX_POWER_NO_PREFERENCE        127

/** Flags that the extended advertisement is connectable. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_CONNECTABLE              0x0001

/** Flags that the extended advertisement is scannable. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_SCANNABLE                0x0002

/** Flags that the extended advertisement is directed. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_DIRECTED                 0x0004

/** Flags that the extended advertisement is high duty cycle
    directed. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_HIGH_DUTY_CYCLE_DIRECTED 0x0008

/** Flags that legacy advertising is used. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_USE_LEGACY_PDUS          0x0010

/** Flags that the extended advertisement is using anonymouse
    advertising. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_ANONYMOUS_ADVERTISING    0x0020

/** Flags that the extended advertisement will include the Tx Power. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_PROPERTIES_INCLUDE_TX_POWER         0x0040

/**
 * Structure that represents the parameters that may be set
 * when configuring periodic advertising for an advertising set.
 *
 * Periodic_Advertising_Interval_Min and
 * Periodic_Advertising_Interval_Max are specified in
 * milliseconds.  Periodic_Advertising_Interval_Min must be
 * less than or equal to Periodic_Advertising_Interval_Max
 * and should be less than Periodic_Advertising_Interval_Max
 * to allow the controller flexibility in scheduling.  Both
 * must be in range:
 *
 * @li MINIMUM_PERIODIC_ADVERTISING_INTERVAL
 * @li MAXIMUM_PERIODIC_ADVERTISING_INTERVAL
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_s
{
   uint16_t  Advertising_Event_Properties;       /**< Advertising event properties. */
   uint32_t  Periodic_Advertising_Interval_Min;  /**< Minimum periodic advertising interval (in ms). Must be less than or equal to Periodic_Advertising_Interval_Max. Must be in range MINIMUM_PERIODIC_ADVERTISING_INTERVAL to MAXIMUM_PERIODIC_ADVERTISING_INTERVAL. */
   uint32_t  Periodic_Advertising_Interval_Max;  /**< Maximum periodic advertising interval (in ms). Must be greater than or equal to Periodic_Advertising_Interval_Min. Must be in range MINIMUM_PERIODIC_ADVERTISING_INTERVAL to MAXIMUM_PERIODIC_ADVERTISING_INTERVAL. */
} qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t structure. */
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_PARAMETERS_SIZE                  (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t))

/** Flags that the periodic advertisement will include the Tx Power. */
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_EVENT_PROPERTIES_INCLUDE_TX_POWER         0x0040

/** CTE minimum length. */
#define QAPI_BLE_GAP_LE_CTE_LENGTH_MINIMUM                                    (QAPI_BLE_HCI_LE_CTE_LENGTH_MINIMUM)

/** CTE maximum length. */
#define QAPI_BLE_GAP_LE_CTE_LENGTH_MAXIMUM                                    (QAPI_BLE_HCI_LE_CTE_LENGTH_MAXIMUM)

/**
 *  Constant tone extension types.
 */
typedef enum
{
   QAPI_BLE_CTE_AOA_E,
   /**< Angle of arrival CTE. */

   QAPI_BLE_CTE_AOD_1_E,
   /**< Angle of departure 1us duration slots. */

   QAPI_BLE_CTE_AOD_2_E,
   /**< Angle of departure 2us duration slots. */
} qapi_BLE_GAP_LE_CTE_Type_t;

/** No CTE request interval. */
#define QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_NONE                             (QAPI_BLE_HCI_LE_CTE_REQUEST_INTERVAL_NONE)

/** Minimum CTE request interval. */
#define QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_MINIMUM                          (QAPI_BLE_HCI_LE_CTE_REQUEST_INTERVAL_MINIMUM)

/** Maximum CTE request interval. */
#define QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_MAXIMUM                          (QAPI_BLE_HCI_LE_CTE_REQUEST_INTERVAL_MAXIMUM)

/** Angle of arrival CTE. */
#define QAPI_BLE_GAP_LE_CTE_TYPES_AOA                                         (QAPI_BLE_HCI_LE_CTE_TYPES_AOA)

/** Angle of departure 1us duration slots. */
#define QAPI_BLE_GAP_LE_CTE_TYPES_AOD_1                                       (QAPI_BLE_HCI_LE_CTE_TYPES_AOD_1)

/** Angle of departure 2us duration slots. */
#define QAPI_BLE_GAP_LE_CTE_TYPES_AOD_2                                       (QAPI_BLE_HCI_LE_CTE_TYPES_AOD_2)

/**
 *  CTE Slot duration types.
 */
typedef enum
{
   QAPI_BLE_SDT_SLOT_DURATION_1_E,
   /**< 1 us slot durations. */

   QAPI_BLE_SDT_SLOT_DURATIon_2_E,
   /**< 2 us slot durations. */
} qapi_BLE_GAP_LE_Slot_Durations_Type_t;

/** Minimum CTE count. */
#define QAPI_BLE_GAP_LE_CTE_COUNT_MINIMUM                                     (QAPI_BLE_HCI_LE_CTE_COUNT_MINIMUM)

/** Maximum CTE count. */
#define QAPI_BLE_GAP_LE_CTE_COUNT_MAXIMUM                                     (QAPI_BLE_HCI_LE_CTE_COUNT_MAXIMUM)

/** Minimum antenna switching pattern length. */
#define QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM                   (QAPI_BLE_HCI_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM)

/** Maximum antenna switching pattern length. */
#define QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM                   (QAPI_BLE_HCI_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM)

/** Sample all CTEs. */
#define QAPI_BLE_GAP_LE_CTE_SAMPLE_ALL                                        (QAPI_BLE_HCI_LE_CTE_SAMPLE_ALL)

/** Minimum number of CTEs to sample. */
#define QAPI_BLE_GAP_LE_CTE_SAMPLE_MINIMUM                                    (QAPI_BLE_HCI_LE_CTE_SAMPLE_MINIMUM)

/** Maximum number of CTEs to sample. */
#define QAPI_BLE_GAP_LE_CTE_SAMPLE_MAXIMUM                                    (QAPI_BLE_HCI_LE_CTE_SAMPLE_MAXIMUM)

/** AoD Tx Switching supported. */
#define QAPI_BLE_GAP_LE_SSSR_SWITCHING_FOR_AOD_TX                             (QAPI_BLE_HCI_LE_SSSR_SWITCHING_AOD_TX)

/** AoD Rx Sampling supported. */
#define QAPI_BLE_GAP_LE_SSSR_SAMPLING_FOR_AOD_RX                              (QAPI_BLE_HCI_LE_SSSR_SAMPLING_AOD_RX)

/** AoA Rx Switching and Sampling supported. */
#define QAPI_BLE_GAP_LE_SSSR_SWITCHING_AND_SAMPLING_FOR_AOA_RX                (QAPI_BLE_HCI_LE_SSSR_SWITCHING_AND_SAMPLING_AOA_RX)

/**
 * Structure that holds the information returned by the
 * qapi_BLE_GAP_LE_Query_Antenna_Information() function.
 *
 * 2 micro-second switching/sampling is mandatory for all
 * CTE types. The Supported_Switching_Sampling_Rates field
 * is a bit mask that can be used to determine if 1
 * micro-second switching/sampling is supported for a CTE
 * type.
 */
typedef struct qapi_BLE_GAP_LE_Antenna_Information_s
{
   uint8_t Supported_Switching_Sampling_Rates;
   /**< Bit mask for the Supported switching/sampling rates. */

   uint8_t Number_Of_Antennae;
   /**< Number of antennae. */

   uint8_t Max_Length_Of_Switching_Pattern;
   /**< Maximum length of switching pattern. */

   uint8_t Max_CTE_Length;
   /**< Maximum CTE Length. */
} qapi_BLE_GAP_LE_Antenna_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Antenna_Information_t structure. */
#define QAPI_BLE_GAP_LE_ANTENNA_INFORMATION_SIZE                              (sizeof(qapi_BLE_GAP_LE_Antenna_Information_t))

/**
 *  Periodic advertising sync transfer mode.
 *
 * If the mode is set to QAPI_BLE_STM_NO_SYNC_E, then no attempt is made
 * to synchronize to the periodic advertisements. The
 * qapi_BLE_GAP_LE_Create_Periodic_Advertising_Synchronization()
 * function MUST be explicity called to synchronize to the
 * periodic advertisements.
 *
 * If the mode is set to QAPI_BLE_STM_AUTO_SYNC_NO_REPORTS_E, then the
 * local device will automatically synchronize to the
 * periodic advertisements
 * (#QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_E event
 * will be dispatched), however
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_REPORT_E events received by the
 * controller will not be dispatched to the host. The
 * qapi_BLE_GAP_LE_Set_Periodic_Advertising_Receive_Enable() function
 * may be used to have the controller dispatch the
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_REPORT_E events.
 *
 * If the mode is set to QAPI_BLE_STM_AUTO_SYNC_REPORTS_E, then the local
 * device will automatically synchronize to the periodic
 * advertisements
 * (#QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_E event
 * will be dispatched), and etLE_Periodic_Advertising_Report
 * events received by the controller will be dispatched to
 * the host.
 */
typedef enum
{
   QAPI_BLE_STM_NO_SYNC_E,
   /**< No synchronization. */

   QAPI_BLE_STM_AUTO_SYNC_NO_REPORTS_E,
   /**< Synchronization with reporting disabled. */

   QAPI_BLE_STM_AUTO_SYNC_REPORTS_E,
   /**< Synchronization with reporting enabled. */
} qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t;

/** Do not synchronize to periodic advertisements with an AoA CTE. */
#define QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_WITH_AOA                             (QAPI_BLE_HCI_LE_CTE_TYPE_NO_SYNC_WITH_AOA)

/** Do not synchronize to periodic advertisements with a AoD CTE (1us slots). */
#define QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_WITH_AOD_1                           (QAPI_BLE_HCI_LE_CTE_TYPE_NO_SYNC_WITH_AOD_1)

/** Do not synchronize to periodic advertisements with a AoD CTE (2us slots). */
#define QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_WITH_AOD_2                           (QAPI_BLE_HCI_LE_CTE_TYPE_NO_SYNC_WITH_AOD_2)

/** Do not synchronize to periodic advertisements without a CTE. */
#define QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_WITHOUT_CTE                          (QAPI_BLE_HCI_LE_CTE_TYPE_NO_SYNC_WITHOUT_CTE)

/**
 * Enumeration of the different operations that may be done
 * when setting extended advertising or scan response data.
 */
typedef enum
{
   QAPI_BLE_AOT_SET_DATA_E,
   /**< Set data.  */

   QAPI_BLE_AOT_UPDATE_DID_E
   /**< Updated DID.  */
} qapi_BLE_GAP_LE_Advertising_Operation_Type_t;

/**
 * Enumeration of the fragmentation preference the host may
 * request when setting extended advertising or scan response data.
 */
typedef enum
{
   QAPI_BLE_PT_FRAGMENTATION_ALLOWED_E,
   /**< Fragmentation allowed.  */

   QAPI_BLE_PT_NO_FRAGMENTATION_ALLOWED_E
   /**< No fragmentation.  */
} qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t;

/**
 * Structure that represents the parameters that are used when scanning
 * for a particular PHY.
 *
 * The Scan_Interval and Scan_Window (specified in milli-seconds) must
 * satisify the following equation: Scan_Window <= Scan_Interval if
 * Scan_Window == Scan_Interval, LE Scanning will be performed
 * continuously.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_s
{
   /** PHY to use for scanning.  */
   qapi_BLE_GAP_LE_PHY_Type_t  Scan_PHY;

   /** Scan type. */
   qapi_BLE_GAP_LE_Scan_Type_t Scan_Type;

   /** Scan interval. */
   uint32_t                    Scan_Interval;

   /** Scan window. */
   uint32_t                    Scan_Window;
} qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t
    structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_SCANNING_PHY_PARAMETERS_SIZE                 (sizeof(qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t))

/**
 * Enumeration of the different values for duplicate filter
 * that can be enabled with extended scanning.
 */
typedef enum
{
   QAPI_BLE_FD_DISABLED_E,
   /**< Disabled.  */

   QAPI_BLE_FD_ENABLED_E,
   /**< Enabled.  */

   QAPI_BLE_FD_ENABLED_RESET_EACH_SCAN_PERIOD_E
   /**< Enabled and reset each scan period.  */
} qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t;

/**
 * Structure that represents a container structure for all the connection
 * parameters passed into the
 * qapi_BLE_GAP_LE_Extended_Create_Connection() function.
 *
 * All members of this structure are specified in milli-seconds EXCEPT
 * Slave_Latency which is specified in number of connection events.
 *
 * The Scan_Interval and Scan_Window (specified in milli-seconds) must
 * satisify the following equation: Scan_Window <= Scan_Interval if
 * Scan_Window == Scan_Interval, LE Scanning will be performed
 * continuously.
 *
 * If the LE 2M PHY is specified in this structure the Scan
 * Interval/Window values are not used.  However the other parameters
 * will be used for any connection created with the 2M PHY.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Connection_Parameters_s
{
   /** Initiating PHY. */
   qapi_BLE_GAP_LE_PHY_Type_t Initiating_PHY;

   /** Scan interval. */
   uint32_t                   Scan_Interval;

   /** Scan window. */
   uint32_t                   Scan_Window;

   /** Minimum connection interval. */
   uint16_t                   Connection_Interval_Min;

   /** Maximum connection interval. */
   uint16_t                   Connection_Interval_Max;

   /** Slave latency. */
   uint16_t                   Slave_Latency;

   /** Supervision timeout. */
   uint16_t                   Supervision_Timeout;

   /** Minimum connection length. */
   uint16_t                   Minimum_Connection_Length;

   /** Maximum connection length. */
   uint16_t                   Maximum_Connection_Length;
} qapi_BLE_GAP_LE_Extended_Connection_Parameters_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Connection_Parameters_t
    structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_CONNECTION_PARAMETERS_SIZE                (sizeof(qapi_BLE_GAP_LE_Extended_Connection_Parameters_t))

/**
 * Structure that represents the GAP LE Remote Features Response Event
 * Data that is returned from the qapi_BLE_GAP_LE_Read_Remote_Features()
 * function in the QAPI_BLE_ET_LE_REMOTE_FEATURES_E GAP LE Event.
 */
typedef struct qapi_BLE_GAP_LE_Remote_Features_Event_Data_s
{
   /**
    * Status.
    */
   uint8_t                Status;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t     BD_ADDR;

   /**
    * LE features.
    */
   qapi_BLE_LE_Features_t LE_Features;
} qapi_BLE_GAP_LE_Remote_Features_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Remote_Features_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_REMOTE_FEATURES_EVENT_DATA_SIZE                    (sizeof(qapi_BLE_GAP_LE_Remote_Features_Event_Data_t))

/**
 * Structure that represents the Initiator and Responder Key Distribution
 * fields in the #qapi_BLE_GAP_LE_Pairing_Capabilities_t structure.
 */
typedef struct qapi_BLE_GAP_LE_Key_Distribution_s
{
   /**
    * Flags if the encryption is exchanged.
    */
   boolean_t Encryption_Key;

   /**
    * Flags if the identification key is exchanged.
    */
   boolean_t Identification_Key;

   /**
    * Flags if the signing key is exchanged.
    */
   boolean_t Signing_Key;
} qapi_BLE_GAP_LE_Key_Distribution_t;

/** Size of the #qapi_BLE_GAP_LE_Key_Distribution_t structure. */
#define QAPI_BLE_GAP_LE_KEY_DISTRIBUTION_SIZE                              (sizeof(qapi_BLE_GAP_LE_Key_Distribution_t))

/**
 * Structure that represents the extended Initiator and Responder Key
 * Distribution fields in the
 * #qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t structure.
 *
 * The Link_Key member is a field that indicates the device would like
 * to derive the BR/EDR from the LE LTK. This is only valid if the
 * local device supports LE Secure Connections.
 *
 * The Link_Key member is only valid with Dual Mode stacks and will be
 * ignored in Single Mode configurations.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Key_Distribution_s
{
   /**
    * Flags if the encryption is exchanged.
    */
   boolean_t Encryption_Key;

   /**
    * Flags if the identification key is exchanged.
    */
   boolean_t Identification_Key;

   /**
    * Flags if the signing key is exchanged.
    */
   boolean_t Signing_Key;

   /**
    * Flags if the link key is exchanged.
    */
   boolean_t Link_Key;
} qapi_BLE_GAP_LE_Extended_Key_Distribution_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Key_Distribution_t structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_KEY_DISTRIBUTION_SIZE                     (sizeof(qapi_BLE_GAP_LE_Extended_Key_Distribution_t))

/**
 * Structure that represents the structure of data that is used to
 * specify the Secure Connections Out Of Band Information when pairing
 * (Version 4.2).
  */
typedef struct qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_s
{
   /**
    * Bitmask that flags if OOB information.
    *
    * Valid values have the form
    * QAPI_BLE_GAP_LE_SECURE_CONNECTIONS_OOB_DATA_FLAGS_XXX and can be
    * found in qapi_ble_gap.h.
    */
   unsigned long                              Flags;

   /**
    * Confirmation.
    */
   qapi_BLE_Secure_Connections_Confirmation_t Confirmation;

   /**
    * Randomizer.
    */
   qapi_BLE_Secure_Connections_Randomizer_t   Randomizer;
} qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t structure. */
#define QAPI_BLE_GAP_LE_SECURE_CONNECTIONS_OOB_DATA_SIZE                   (sizeof(qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t))

/** Flag that may be set in Flags member of #qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t
    structure. */
#define QAPI_BLE_GAP_LE_SECURE_CONNECTIONS_OOB_DATA_FLAGS_OOB_NOT_RECEIVED 0x00000001

/**
* Indicates the public/private key pair that will be used for LE
* SC pairing.
*/
typedef enum
{
   /**
    * Generate key pair in host or controller.
    */
   QAPI_BLE_DM_USE_GENERATED_KEY_E,

   /**
    * Use debug key pair from host or controller.
    */
   QAPI_BLE_DM_USE_DEBUG_KEY_E
} qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t;

/**
 * Structure that represents the information that is requested in a
 * #QAPI_BLE_LAT_PAIRING_REQUEST_E of the #QAPI_BLE_ET_LE_AUTHENTICATION_E
 * event.
 *
 * The Receiving_Keys structure represents the keys that the local
 * device is requesting from the remote device. The Sending_Keys
 * structure represents the keys that the local device is requesting to
 * send to the remote device.
*/
typedef struct qapi_BLE_GAP_LE_Pairing_Capabilities_s
{
   /**
    * IO Capability.
    */
   qapi_BLE_GAP_LE_IO_Capability_t    IO_Capability;

   /**
    * Flags if OOB is present.
    */
   boolean_t                          OOB_Present;

   /**
    * Bonding type.
    */
   qapi_BLE_GAP_LE_Bonding_Type_t     Bonding_Type;

   /**
    * Flags if Man in the Middle (MITM) protection is required.
    */
   boolean_t                          MITM;

   /**
    * Maximum encryption key size.
    */
   uint8_t                            Maximum_Encryption_Key_Size;

   /**
    * Receiving distribution keys.
    */
   qapi_BLE_GAP_LE_Key_Distribution_t Receiving_Keys;

   /**
    * Sending distribution keys.
    */
   qapi_BLE_GAP_LE_Key_Distribution_t Sending_Keys;
} qapi_BLE_GAP_LE_Pairing_Capabilities_t;

/** Size of the #qapi_BLE_GAP_LE_Pairing_Capabilities_t structure. */
#define QAPI_BLE_GAP_LE_PAIRING_CAPABILITIES_SIZE                          (sizeof(qapi_BLE_GAP_LE_Pairing_Capabilities_t))

/**
 * Structure that represents the information that is requested in a
 * #QAPI_BLE_LAT_EXTENDED_PAIRING_REQUEST_E of the
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when Secure Connections support
 * has been enabled.
 *
 * The Receiving_Keys structure represents the keys that the local
 * device is requesting from the remote device. The Sending_Keys
 * structure represents the keys that the local device is requesting to
 * send to the remote device.
 *
 * The Secure Connections pairability mode must be enabled by setting
 * the pairability mode to
   QAPI_BLE_LPM_PAIRABLE_MODE_E_SecureConnections via the
 * qapi_BLE_GAP_LE_Set_Pairability_Mode() API prior to requesting Secure
 * Connections pairing via this API.
 *
 * Secure Connections pairing to multiple devices simultaneously is not
 * allowed by this module.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_s
{
   /**
    * Bitmask that indicates pairing capabilites and security
    * requirements.
    *
    * Valid values have the form
    * QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_XXX and can be
    * found in qapi_ble_gap.h.
    */
   unsigned long                               Flags;

   /**
    * IO Capability.
    */
   qapi_BLE_GAP_LE_IO_Capability_t             IO_Capability;

   /**
    * Bonding type.
    */
   qapi_BLE_GAP_LE_Bonding_Type_t              Bonding_Type;

   /**
    * Maximum encryption key size.
    */
   uint8_t                                     Maximum_Encryption_Key_Size;

   /**
    * Receiving distribution keys.
    */
   qapi_BLE_GAP_LE_Extended_Key_Distribution_t Receiving_Keys;

   /**
    * Sending distribution keys.
    */
   qapi_BLE_GAP_LE_Extended_Key_Distribution_t Sending_Keys;

   /**
    * Secure Connections OOB Data.
    */
   qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t LocalOOBData;
} qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_SIZE                          (sizeof(qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t))

/** Indicates capability of sending keypress notifications. */
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_KEYPRESS_NOTIFICATIONS  0x00000001

/** Indicates support for Secure Connections Pairing. */
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_SECURE_CONNECTIONS      0x00000002

/** Indicates request for Man in the Middle protection. */
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_MITM_REQUESTED          0x00000004

/** Indicates that out of band data is present for other device. */
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_OOB_DATA_PRESENT        0x00000008

/** Indicates if LocalOOBData member of
    #qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t structure is valid.*/
#define QAPI_BLE_GAP_LE_EXTENDED_PAIRING_CAPABILITIES_FLAGS_LOCAL_OOB_DATA_VALID    0x00000010


/**
 * Structure that represents the structure of data that is used to
 * specify the Out Of Band Information when pairing.
 */
typedef struct qapi_BLE_GAP_LE_OOB_Data_s
{
   /**
    * OOB key.
    */
   qapi_BLE_Encryption_Key_t OOB_Key;
} qapi_BLE_GAP_LE_OOB_Data_t;

/** Size of the #qapi_BLE_GAP_LE_OOB_Data_t structure. */
#define QAPI_BLE_GAP_LE_OOB_DATA_SIZE                                      (sizeof(qapi_BLE_GAP_LE_OOB_Data_t))

/**
 * Structure that represents the structure of data that is used to
 * specify the current encryption information.
 */
typedef struct qapi_BLE_GAP_LE_Encryption_Information_s
{
   /**
    * Encryption key size.
    */
   uint8_t                  Encryption_Key_Size;

   /**
    * Long Term Key (LTK).
    */
   qapi_BLE_Long_Term_Key_t LTK;

   /**
    * Encryption diversifier.
    */
   uint16_t                 EDIV;

   /**
    * Random number.
    */
   qapi_BLE_Random_Number_t Rand;
} qapi_BLE_GAP_LE_Encryption_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Encryption_Information_t structure. */
#define QAPI_BLE_GAP_LE_ENCRYPTION_INFORMATION_DATA_SIZE                   (sizeof(qapi_BLE_GAP_LE_Encryption_Information_t))

/**
 * Structure that represents the structure of data that is used to
 * specify the current identity information.
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *
 * For this structure, #QAPI_BLE_LAT_PUBLIC_E means the same thing as
 * #QAPI_BLE_LAT_PUBLIC_IDENTITY_E (and #QAPI_BLE_LAT_RANDOM_E and
 * #QAPI_BLE_LAT_RANDOM_IDENTITY_E are equivalent). For legacy reasons we
 * always return either QAPI_BLE_LAT_PUBLIC_E/QAPI_BLE_LAT_RANDOM_E here
 * even though the address returned in this structure is an Identity
 * Address.
 */
typedef struct qapi_BLE_GAP_LE_Identity_Information_s
{
   /**
    * Identity Resolving Key (IRK).
    */
   qapi_BLE_Encryption_Key_t      IRK;

   /**
    * Identity address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Address_Type;

   /**
    * Identity address.
    */
   qapi_BLE_BD_ADDR_t             Address;
} qapi_BLE_GAP_LE_Identity_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Identity_Information_t structure. */
#define QAPI_BLE_GAP_LE_IDENTITY_INFORMATION_DATA_SIZE                     (sizeof(qapi_BLE_GAP_LE_Identity_Information_t))

/**
 * Structure that represents the structure of data that is used to
 * specify the current signing information.
 */
typedef struct qapi_BLE_GAP_LE_Signing_Information_s
{
   /**
    * Signing key.
    */
   qapi_BLE_Encryption_Key_t CSRK;
} qapi_BLE_GAP_LE_Signing_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Signing_Information_t structure. */
#define QAPI_BLE_GAP_LE_SIGNING_INFORMATION_DATA_SIZE                      (sizeof(qapi_BLE_GAP_LE_Signing_Information_t))

/**
 * Structure that represents the structure of data that is used to
 * specify the LTK and key size.
 */
typedef struct qapi_BLE_GAP_LE_Long_Term_Key_Information_s
{
   /**
    * Encryption key size.
    */
   uint8_t                  Encryption_Key_Size;

   /**
    * Long term key.
    */
   qapi_BLE_Long_Term_Key_t Long_Term_Key;
} qapi_BLE_GAP_LE_Long_Term_Key_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Long_Term_Key_Information_t structure. */
#define QAPI_BLE_GAP_LE_LONG_TERM_KEY_INFORMATION_DATA_SIZE               (sizeof(qapi_BLE_GAP_LE_Long_Term_Key_Information_t))


 /**
 *   Enumerated type that represents the different
 *   Authentication Methods that can be used. These values
 *   are used when responding with an Authentication Response.
 */
typedef enum
{
   QAPI_BLE_LAR_LONG_TERM_KEY_E,
   /**< Indicates the long term key authentication response. */

   QAPI_BLE_LAR_OUT_OF_BAND_DATA_E,
   /**< Indicates the out of band data authentication response. */

   QAPI_BLE_LAR_PAIRING_CAPABILITIES_E,
   /**< Indicates the pairing capabilities authentication response. */

   QAPI_BLE_LAR_PASSKEY_E,
   /**< Indicates the passkey authentication response. */

   QAPI_BLE_LAR_CONFIRMATION_E,
   /**< Indicates the confirmation authentication response. */

   QAPI_BLE_LAR_ERROR_E,
   /**< Indicates the error authentication response. */

   QAPI_BLE_LAR_ENCRYPTION_INFORMATION_E,
   /**< Indicates the encryption information authentication response. */

   QAPI_BLE_LAR_IDENTITY_INFORMATION_E,
   /**< Indicates the identity information authentication response. */

   QAPI_BLE_LAR_SIGNING_INFORMATION_E,
   /**< Indicates the signing information authentication response. */

   QAPI_BLE_LAR_KEY_PRESS_E
   /**< Indicates the keypress authentication response. */
} qapi_BLE_GAP_LE_Authentication_Response_Type_t;

/**
 * Structure that represents the GAP Authentication response information.
 *
 * For GAP Authentication Response Types that are rejections, the
 * Authentication_Data_Length member is set to zero and All Data Members
 * can be ignored (since none are valid).
 *
 * The Authentication_Data_Length must be set correctly according to the
 * union member that is valid. Specifically for
 * #QAPI_BLE_LAR_PAIRING_CAPABILITIES_E and
 * #QAPI_BLE_LAR_OUT_OF_BAND_DATA_E the Authentication_Data_Length field
 * is used to differentiate between whether the Pairing_Capabilities,
   Extended_Pairing_Capabilities and Out_Of_Band_Data,
 * Secure_Connections_OOB_Data structures respectively are valid.
 */
typedef struct qapi_BLE_GAP_LE_Authentication_Response_Information_s
{
   /**
    * Authentication response type.
    */
   qapi_BLE_GAP_LE_Authentication_Response_Type_t     GAP_LE_Authentication_Type;

   /**
    * Total authentication response data length.
    */
   uint8_t                                            Authentication_Data_Length;
   union
   {
      /**
       * GAP LE LTK information.
       */
      qapi_BLE_GAP_LE_Long_Term_Key_Information_t     Long_Term_Key_Information;

      /**
       * GAP LE Pairing Capabilities.
       */
      qapi_BLE_GAP_LE_Pairing_Capabilities_t          Pairing_Capabilities;

      /**
       * GAP LE Extended Pairing Capabilities.
       */
      qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t Extended_Pairing_Capabilities;

      /**
       * GAP LE OOB data.
       */
      qapi_BLE_GAP_LE_OOB_Data_t                      Out_Of_Band_Data;

      /**
       * GAP LE Secure Connections OOB data.
       */
      qapi_BLE_GAP_LE_Secure_Connections_OOB_Data_t   Secure_Connections_OOB_Data;

      /**
       * GAP LE Passkey.
       */
      uint32_t                                        Passkey;

      /**
       * GAP LE Authentication Response Error Code.
       */
      uint8_t                                         Error_Code;

      /**
       * GAP LE Encryption information.
       */
      qapi_BLE_GAP_LE_Encryption_Information_t        Encryption_Information;

      /**
       * GAP LE Identity information.
       */
      qapi_BLE_GAP_LE_Identity_Information_t          Identity_Information;

      /**
       * GAP LE Signing information.
       */
      qapi_BLE_GAP_LE_Signing_Information_t           Signing_Information;

      /**
       * GAP LE Keypress.
       */
      qapi_BLE_GAP_LE_Keypress_t                      Keypress;
   }
   /**
    * Union for the authentication response data that is set based on
    * the value of the GAP_LE_Authentication_Type field.
    */
   Authentication_Data;
} qapi_BLE_GAP_LE_Authentication_Response_Information_t;

/** Size of the 
    #qapi_BLE_GAP_LE_Authentication_Response_Information_t structure. */
#define QAPI_BLE_GAP_LE_AUTHENTICATION_RESPONSE_INFORMATION_SIZE           (sizeof(qapi_BLE_GAP_LE_Authentication_Response_Information_t))

/**
 * Type declaration that represents the structure of
 * information stored in the qapi_BLE_GAP_LE_Security_Information_t
 * structure which is passed to the
 * qapi_BLE_GAP_LE_Reestablish_Security() function when the local
 * device is the slave of the specified connection.
 */
typedef struct qapi_BLE_GAP_LE_Slave_Security_Information_s
{
   /**
    * Bonding type.
    */
   qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type;

   /**
    * Man in the Middle (MITM) protection.
    */
   boolean_t                      MITM;
} qapi_BLE_GAP_LE_Slave_Security_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Slave_Security_Information_t structure. */
#define QAPI_BLE_GAP_LE_SLAVE_SECURITY_INFORMATION_SIZE                    (sizeof(qapi_BLE_GAP_LE_Slave_Security_Information_t))

/**
 * Type declaration that represents the structure of
 * information stored in the qapi_BLE_GAP_LE_Security_Information_t
 * structure which is passed to the
 * qapi_BLE_GAP_LE_Reestablish_Security() function when we the local
 * device is the master of the specified connection.
 */
typedef struct qapi_BLE_GAP_LE_Master_Security_Information_s
{
   /**
    * Encryption key size.
    */
   uint8_t                  Encryption_Key_Size;

   /**
    * Long term key.
    */
   qapi_BLE_Long_Term_Key_t LTK;

   /**
    * Encryption diversifier.
    */
   uint16_t                 EDIV;

   /**
    * Random number.
    */
   qapi_BLE_Random_Number_t Rand;
} qapi_BLE_GAP_LE_Master_Security_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Master_Security_Information_t structure. */
#define QAPI_BLE_GAP_LE_MASTER_SECURITY_INFORMATION_SIZE                   (sizeof(qapi_BLE_GAP_LE_Master_Security_Information_t))

/**
 * Structure that represents a container structure that contains the data
 * passed to the qapi_BLE_GAP_LE_Reestablish_Security() function, which
 * takes different data parameters based on the local device role.
 */
typedef struct qapi_BLE_GAP_LE_Security_Information_s
{
   /**
    * Flags if the local device is the master of the connection.
    */
   boolean_t Local_Device_Is_Master;
   union
   {
      /**
       * Slave's security information.
       */
      qapi_BLE_GAP_LE_Slave_Security_Information_t  Slave_Information;

      /**
       * Master's security information.
       */
      qapi_BLE_GAP_LE_Master_Security_Information_t Master_Information;
   }
   /**
    * Union that stores the security information based on whether the
    * local device is the master or the slave.
    */
   Security_Information;
} qapi_BLE_GAP_LE_Security_Information_t;

/** Size of the #qapi_BLE_GAP_LE_Security_Information_t structure. */
#define QAPI_BLE_GAP_LE_SECURITY_INFORMATION_DATA_SIZE                     (sizeof(qapi_BLE_GAP_LE_Security_Information_t))

/**
 * Enumerated type that represents the GAP LE Event Reason
 * (and valid Data) and is used with the GAP Event Callback.
 *
 * #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E is deprecated and replaced with
 * #QAPI_BLE_ET_LE_DIRECTED_ADVERTISING_REPORT_E. The event name was changed
 * between versions 4.2 and 5.0 of the Bluetooth specificiations.
 */
typedef enum
{
   QAPI_BLE_ET_LE_REMOTE_FEATURES_RESULT_E,
   /**< Indicates an LE remote features result event. */

   QAPI_BLE_ET_LE_ADVERTISING_REPORT_E,
   /**< Indicates an LE advertising report event. */

   QAPI_BLE_ET_LE_CONNECTION_COMPLETE_E,
   /**< Indicates an LE connection complete event. */

   QAPI_BLE_ET_LE_DISCONNECTION_COMPLETE_E,
   /**< Indicates an LE disconnection complete event. */

   QAPI_BLE_ET_LE_ENCRYPTION_CHANGE_E,
   /**< Indicates an LE encryption change event. */

   QAPI_BLE_ET_LE_ENCRYPTION_REFRESH_COMPLETE_E,
   /**< Indicates an LE encryption refresh event. */

   QAPI_BLE_ET_LE_AUTHENTICATION_E,
   /**< Indicates an LE authentication event (which will have sub-events). */

   QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_E,
   /**< Indicates an LE connection parameter update request event. */

   QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_E,
   /**< Indicates an LE connection parameter update response event. */

   QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATED_E,
   /**< Indicates an LE connection parameter updated event. */

   QAPI_BLE_ET_LE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_E,
   /**< Indicates that the LE Authenticated Payload Timeout expired
        for the specified connection. */

   QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E,
   /**< Indicates an LE direct advertising report event. */

   QAPI_BLE_ET_LE_DIRECTED_ADVERTISING_REPORT_E = QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E,
   /**< Indicates an LE directed advertising report event. */

   QAPI_BLE_ET_LE_DATA_LENGTH_CHANGE_E,
   /**< Indicates an LE data length change event. */

   QAPI_BLE_ET_LE_LOCAL_P256_PUBLIC_KEY_UPDATE_COMPLETE_E,
   /**< Indicates an LE P256 public/private key pair generation has completed. */

   QAPI_BLE_ET_LE_PHY_UPDATE_COMPLETE_E,
   /**< Indicates an LE PHY update complete event. */

   QAPI_BLE_ET_LE_EXTENDED_ADVERTISING_REPORT_E,
   /**< Indicates an LE extended advertising report event. */

   QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_E,
   /**< Indicates an LE peridic advertising sync established event. */

   QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_REPORT_E,
   /**< Indicates an LE peridic advertising report event. */

   QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_LOST_E,
   /**< Indicates an LE peridic advertising sync list event. */

   QAPI_BLE_ET_LE_SCAN_TIMEOUT_E,
   /**< Indicates an LE scan timeout event. */

   QAPI_BLE_ET_LE_ADVERTISING_SET_TERMINATED_E,
   /**< Indicates an LE advertising set has been terminated. */

   QAPI_BLE_ET_LE_SCAN_REQUEST_RECEIVED_E,
   /**< Indicates an LE extended advertising report event. */

   QAPI_BLE_ET_LE_CHANNEL_SELECTION_ALGORITHM_UPDATE_E,
   /**< Indicates an LE channel selection algorithm update event. */

   QAPI_BLE_ET_LE_CONNECTIONLESS_IQ_REPORT_E,
   /**< Indicates an LE connectionless IQ report event. */

   QAPI_BLE_ET_LE_CONNECTION_IQ_REPORT_E,
   /**< Indicates an LE connection IQ report event. */

   QAPI_BLE_ET_LE_CTE_REQUEST_FAILED_E,
   /**< Indicates an LE CTE request failed event. */

   QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_E,
   /**< Indicates an LE periodic advertising sync transfer received event. */
} qapi_BLE_GAP_LE_Event_Type_t;

/**
 * Structure that represents an individual Advertising Report Structure
 * Entry that is present in an LE Advertising Report.
 *
 * This structure is used with the
 * qapi_BLE_GAP_LE_Advertising_Report_Data_t container structure so that
 * individual entries can be accessed in a convenient, array-like, form.
 *
 * The AD_Type member is defined in the specification to be variable
 * length. The current specification does not use this member in
 * this way (they are all defined to be a single octet, currently).
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Data_Entry_s
{
   /**
    * Advertising data type.
    */
   uint32_t  AD_Type;

   /**
    * Advertising data length.
    */
   uint8_t   AD_Data_Length;

   /**
    * Advertising data buffer.
    */
   uint8_t  *AD_Data_Buffer;
} qapi_BLE_GAP_LE_Advertising_Data_Entry_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Data_Entry_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_DATA_ENTRY_SIZE                        (sizeof(qapi_BLE_GAP_LE_Advertising_Data_Entry_t))

/**
 * Structure that represents a container structure that is used to
 * represent all the entries in an Advertising Data Structure.
 *
 * This structure is used so that all fields are easy to parse and access
 * (that is, there are no macros required to access variable length
 * records).
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Data_s
{
   /**
    * Number of individual advertising report entries that are
    * contained in the Data_Entries field.
    */
   uint32_t                                  Number_Data_Entries;

   /**
    * Pointer to the list of the advertising report entries.
    */
   qapi_BLE_GAP_LE_Advertising_Data_Entry_t *Data_Entries;
} qapi_BLE_GAP_LE_Advertising_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Data_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_DATA_SIZE                              (sizeof(qapi_BLE_GAP_LE_Advertising_Data_t))

/**
 * Structure that represents a container structure that is used to
 * represent all the entries in an LE Advertising Report data field.
 *
 * This structure is used so that all fields are easy to parse and access
 * (that is, there are no macros required to access variable length
 * records).
 *
 * The Advertising_Data member contains the the actual parsed data for
 * the report (either a Scan Response or Advertising report - specified
 * by the qapi_BLE_GAP_LE_Advertising_Report_Type member).
 *
 * The Raw_Report_Length and Raw_Report_Data members contain the length (in
 * bytes) of the actual report received, as well as a pointer to the
 * actual bytes present in the report, respectively.
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Report_Data_s
{
   /**
    * Advertising report type.
    */
   qapi_BLE_GAP_LE_Advertising_Report_Type_t  Advertising_Report_Type;

   /**
    * Remote device address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t             Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                         BD_ADDR;

   /**
    * Remote Signal Strength Indicator (RSSI).
    */
   int8_t                                     RSSI;

   /**
    * Pointer to the advertising data.
    */
   qapi_BLE_GAP_LE_Advertising_Data_t         Advertising_Data;

   /**
    * Raw advertising report data length.
    */
   uint8_t                                    Raw_Report_Length;

   /**
    * Pointer to the raw report data.
    */
   uint8_t                                   *Raw_Report_Data;
} qapi_BLE_GAP_LE_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Report_Data_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_REPORT_DATA_SIZE                       (sizeof(qapi_BLE_GAP_LE_Advertising_Report_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_ADVERTISING_REPORT_E event. The structure is used to
 * return Advertising Reports returned from multiple devices.
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Report_Event_Data_s
{
   /**
    * Number of remote device entries.
    */
   uint32_t                                   Number_Device_Entries;

   /**
    * Pointer to the advertising data returned from multiple devices.
    */
   qapi_BLE_GAP_LE_Advertising_Report_Data_t *Advertising_Data;
} qapi_BLE_GAP_LE_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Report_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE                 (sizeof(qapi_BLE_GAP_LE_Advertising_Report_Event_Data_t))

/**
 * This structure is a container that is used to represent all
 * the entries in a LE Direct Advertising Report data field.
 *
 * This structure is used so that all fields are easy to parse and access
 * (that is, there are no macros required to access variable length
 * records).
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 *
 * The Direct_Address_Type and Direct_BD_ADDR correspond to the address
 * of the device these advertisements are directed towards. Note that
 * Direct_Address_Type will always be set to:
 *
 *   @li QAPI_BLE_LAT_RANDOM_E
 *
 * (since this event is only set to the host by the controller when the
 * directed address is a Resolvable Private Address).
 *
 * This event will only be sent if the local Bluetooth controller is a
 * 4.2 or greater compliant controller.
 */
typedef struct qapi_BLE_GAP_LE_Direct_Advertising_Report_Data_s
{
   /**
    * Remote device address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t             BD_ADDR;

   /**
    * Direct address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Direct_Address_Type;

   /**
    * Direct address.
    */
   qapi_BLE_BD_ADDR_t             Direct_BD_ADDR;

   /**
    * Remote Signal Strength Indicator (RSSI).
    */
   int8_t                         RSSI;
} qapi_BLE_GAP_LE_Direct_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Direct_Advertising_Report_Data_t structure. */
#define QAPI_BLE_GAP_LE_DIRECT_ADVERTISING_REPORT_DATA_SIZE                (sizeof(qapi_BLE_GAP_LE_Direct_Advertising_Report_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E event.
 *
 * This structure is used to return Advertising Reports returned from
 * multiple devices.
 */
typedef struct qapi_BLE_GAP_LE_Direct_Advertising_Report_Event_Data_s
{
   /**
    * Number of remote device entries.
    */
   uint32_t                                          Number_Device_Entries;

   /**
    * Pointer to the direct advertising report data.
    */
   qapi_BLE_GAP_LE_Direct_Advertising_Report_Data_t *Direct_Advertising_Data;
} qapi_BLE_GAP_LE_Direct_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Direct_Advertising_Report_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_DIRECT_ADVERTISING_REPORT_EVENT_DATA_SIZE          (sizeof(qapi_BLE_GAP_LE_Direct_Advertising_Report_Event_Data_t))

/**
 * This structure is a container that is used to represent all
 * the entries in a LE Direct Advertising Report data field.
 *
 * This structure is used so that all fields are easy to parse and access
 * (that is, there are no macros required to access variable length
 * records).
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 *
 * The Direct_Address_Type and Direct_BD_ADDR correspond to the address
 * of the device these advertisements are directed towards. Note that
 * Direct_Address_Type will always be set to:
 *
 *   @li QAPI_BLE_LAT_RANDOM_E
 *
 * (since this event is only set to the host by the controller when the
 * directed address is a Resolvable Private Address).
 *
 * This event will only be sent if the local Bluetooth controller is a
 * 4.2 or greater compliant controller.
 */
typedef struct qapi_BLE_GAP_LE_Directed_Advertising_Report_Data_s
{
   /**
    * Remote device address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t             BD_ADDR;

   /**
    * Direct address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Direct_Address_Type;

   /**
    * Direct address.
    */
   qapi_BLE_BD_ADDR_t             Direct_BD_ADDR;

   /**
    * Remote Signal Strength Indicator (RSSI).
    */
   int8_t                         RSSI;
} qapi_BLE_GAP_LE_Directed_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Directed_Advertising_Report_Data_t structure. */
#define QAPI_BLE_GAP_LE_DIRECTED_ADVERTISING_REPORT_DATA_SIZE                (sizeof(qapi_BLE_GAP_LE_Directed_Advertising_Report_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E event.
 *
 * This structure is used to return Advertising Reports returned from
 * multiple devices.
 */
typedef struct qapi_BLE_GAP_LE_Directed_Advertising_Report_Event_Data_s
{
   /**
    * Number of remote device entries.
    */
   uint32_t                                            Number_Device_Entries;

   /**
    * Pointer to the direct advertising report data.
    */
   qapi_BLE_GAP_LE_Directed_Advertising_Report_Data_t *Direct_Advertising_Data;
} qapi_BLE_GAP_LE_Directed_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Directed_Advertising_Report_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_DIRECTED_ADVERTISING_REPORT_EVENT_DATA_SIZE          (sizeof(qapi_BLE_GAP_LE_Directed_Advertising_Report_Event_Data_t))

/**
 * Enumeration of the different status values that may be
 * received in an QAPI_BLE_ET_LE_EXTENDED_ADVERTISING_REPORT_E event.
 */
typedef enum
{
   QAPI_BLE_DS_COMPLETE_E,
   /**< Complete.  */

   QAPI_BLE_DS_INCOMPLETE_DATA_PENDING_E,
   /**< Data Pending.  */

   QAPI_BLE_DS_INCOMPLETE_DATA_TRUNCATED_E
   /**< Data Truncated.  */
} qapi_BLE_GAP_LE_Advertising_Data_Status_t;

/**
 * Structure that represents a container structure that is used to
 * represent all the entries in an LE Extended Advertising Report Data
 * Field This structure is used so that all fields are easy to parse and
 * access (that is  there are no MACRO's required to access variable length
 * records).
 *
 * The Raw_Report_Length and Raw_Report_Data members contain the length
 * (in bytes) of the actual report received, as well as a pointer to the
 * actual bytes present in the report, respectively.
 *
 * If the Data_Status member is set to
 * #QAPI_BLE_DS_INCOMPLETE_DATA_PENDING_E then more advertising reports
 * will be received with additional data from the advertiser.  If the
 * Data_Status member is set to dsIncomplete_DataTruncated then the data
 * received is not all of the data advertised, however no more events are
 * pending for this advertiser.
 *
 * The following enumerated types may be returned with the Address_Type
 * member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 *
 * The Periodic_Advertising_Interval member is specified in milliseconds.
 *
 * The Direct_Address_Type and Direct_BD_ADDR members are only valid if
 * the QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_DIRECTED bit is
 * set in the Event_Type_Flags member.
 *
 * The Secondary_PHY member is only valid if
 * the QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SECONDARY_PHY_VALID
 * bit is set in the Event_Type_Flags.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_s
{
   /**
    * Bit mask that indicates the extended advertising report type.
    * Valid values have the form
    * QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_XXX.
    */
   unsigned long                              Event_Type_Flags;

   /** Advertising data status. */
   qapi_BLE_GAP_LE_Advertising_Data_Status_t  Data_Status;

   /** Advertiser address type. */
   qapi_BLE_GAP_LE_Address_Type_t             Address_Type;

   /** Advertiser address. */
   qapi_BLE_BD_ADDR_t                         BD_ADDR;

   /** Primary PHY used for the advertising report. */
   qapi_BLE_GAP_LE_PHY_Type_t                 Primary_PHY;

   /** Secondary PHY used for the advertising report. */
   qapi_BLE_GAP_LE_PHY_Type_t                 Secondary_PHY;

   /** Advertising SID.  */
   uint8_t                                    Advertising_SID;

   /** Tx Power at the time the advertisng report was sent. */
   int8_t                                     Tx_Power;

   /** Remote Signal Strength Indicator (RSSI). */
   int8_t                                     RSSI;

   /** Periodic advertising interval. */
   uint32_t                                   Periodic_Advertising_Interval;

   /** Direct address type. */
   qapi_BLE_GAP_LE_Address_Type_t             Direct_Address_Type;

   /** Direct address. */
   qapi_BLE_BD_ADDR_t                         Direct_BD_ADDR;

   /** Raw report length. */
   uint8_t                                    Raw_Report_Length;

   /** Raw report data. */
   uint8_t                                   *Raw_Report_Data;
} qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t
    structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_REPORT_DATA_SIZE              (sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t))

/** Flags that the received advertising report is connectable. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_CONNECTABLE         0x00000001

/** Flags that the received advertising report is scannable. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SCANNABLE           0x00000002

/** Flags that the received advertising report is directed. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_DIRECTED            0x00000004

/** Flags that the received advertising report is a scan response. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SCAN_RESPONSE       0x00000008

/** Flags that the received advertising report is a legacy PDU. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_LEGACY_PDU          0x00000010

/** Flags that the received advertising report's secondary PHY is
    valid. */
#define GAP_LE_EXTENDED_ADVERTISING_EVENT_TYPE_SECONDARY_PHY_VALID 0x80000000

/** Structure that represents the data returned in a GAP
    QAPI_BLE_ET_LE_EXTENDED_ADVERTISING_REPORT_E event.  The
    structure is used to return Extended_Advertising Reports returned
    from multiple devices. */
typedef struct qapi_BLE_AP_LE_Extended_Advertising_Report_Event_Data_s
{
   /** Number of extended advertising reports that have been receive
       for each remote device. */
   uint32_t                                            Number_Device_Entries;

   /** The extended advertising reports. */
   qapi_BLE_GAP_LE_Extended_Advertising_Report_Data_t *Extended_Advertising_Data;
} qapi_BLE_GAP_LE_Extended_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Extended_Advertising_Report_Event_Data_t
    structure. */
#define QAPI_BLE_GAP_LE_EXTENDED_ADVERTISING_REPORT_EVENT_DATA_SIZE        (sizeof(qapi_BLE_GAP_LE_Extended_Advertising_Report_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_CONNECTION_COMPLETE_E event.
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Connection_Complete_Event_Data_s
{
   /**
    * Status of the connection.
    */
   uint8_t                                         Status;

   /**
    * Flags if the local device is the master of the connection.
    */
   boolean_t                                       Master;

   /**
    * Remote device address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t                  Peer_Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                              Peer_Address;

   /**
    * Current connection parameters.
    */
   qapi_BLE_GAP_LE_Current_Connection_Parameters_t Current_Connection_Parameters;
} qapi_BLE_GAP_LE_Connection_Complete_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_Complete_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_COMPLETE_EVENT_DATA_SIZE                (sizeof(qapi_BLE_GAP_LE_Connection_Complete_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_DISCONNECTION_COMPLETE_E event.
 *
 * The following enumerated types may be returned with the
 * Address_Type member:
 *
 *   @li QAPI_BLE_LAT_PUBLIC_E
 *   @li QAPI_BLE_LAT_RANDOM_E
 *   @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *   @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_s
{
   /**
    * Status of the disconnection.
    */
   uint8_t                        Status;

   /**
    * Reason for the disconnection.
    */
   uint8_t                        Reason;

   /**
    * Remote address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Peer_Address_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t             Peer_Address;
} qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_DISCONNECTION_COMPLETE_EVENT_DATA_SIZE             (sizeof(qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_ENCRYPTION_CHANGE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Encryption_Change_Event_Data_s
{
   /**
    * Bluetooth address for the encryption change.
    */
   qapi_BLE_BD_ADDR_t             BD_ADDR;

   /**
    * Encryption change status.
    */
   uint8_t                        Encryption_Change_Status;

   /**
    * Encryption mode.
    */
   qapi_BLE_GAP_Encryption_Mode_t Encryption_Mode;
} qapi_BLE_GAP_LE_Encryption_Change_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Encryption_Change_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_ENCRYPTION_CHANGE_EVENT_DATA_SIZE                  (sizeof(qapi_BLE_GAP_LE_Encryption_Change_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_ENCRYPTION_REFRESH_COMPLETE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_s
{
   /**
    * Bluetooth address for the encryption refresh.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Status of the encryption refresh.
    */
   uint8_t            Status;
} qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_ENCRYPTION_REFRESH_COMPLETE_EVENT_DATA_SIZE        (sizeof(qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_t))

 /**
 *   Enumerated type that represents the different
 *   Authentication Requests that can be specified.
 */
typedef enum
{
   QAPI_BLE_LAT_LONG_TERM_KEY_REQUEST_E,
   /**< Indicates a long term key request authentication event. */

   QAPI_BLE_LAT_SECURITY_REQUEST_E,
   /**< Indicates a security request authentication event. */

   QAPI_BLE_LAT_PAIRING_REQUEST_E,
   /**< Indicates a pairing request authentication event. */

   QAPI_BLE_LAT_CONFIRMATION_REQUEST_E,
   /**< Indicates a confirmation request authentication event. */

   QAPI_BLE_LAT_PAIRING_STATUS_E,
   /**< Indicates a pairing status authentication event. */

   QAPI_BLE_LAT_ENCRYPTION_INFORMATION_REQUEST_E,
   /**< Indicates an encryption information request authentication event. */

   QAPI_BLE_LAT_IDENTITY_INFORMATION_REQUEST_E,
   /**< Indicates an identity information request authentication event. */

   QAPI_BLE_LAT_SIGNING_INFORMATION_REQUEST_E,
   /**< Indicates a signing information request authentication event. */

   QAPI_BLE_LAT_ENCRYPTION_INFORMATION_E,
   /**< Indicates an encryption information authentication event. */

   QAPI_BLE_LAT_IDENTITY_INFORMATION_E,
   /**< Indicates an identity information authentication event. */

   QAPI_BLE_LAT_SIGNING_INFORMATION_E,
   /**< Indicates a signing information authentication event. */

   QAPI_BLE_LAT_SECURITY_ESTABLISHMENT_COMPLETE_E,
   /**< Indicates a security establishment complete authentication event. */

   QAPI_BLE_LAT_KEYPRESS_NOTIFICATION_E,
   /**< Indicates a keypress notification authentication event. */

   QAPI_BLE_LAT_EXTENDED_PAIRING_REQUEST_E,
   /**< Indicates an extended pairing request authentication event. */

   QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E,
   /**< Indicates an extended confirmation request authentication event. */

   QAPI_BLE_LAT_EXTENDED_OUT_OF_BAND_INFORMATION_E
   /**< Indicates an extended out of band information request authentication event. */
} qapi_BLE_GAP_LE_Authentication_Event_Type_t;

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_LONG_TERM_KEY_REQUEST_E.
 */
typedef struct qapi_BLE_GAP_LE_Key_Request_Info_s
{
   /**
    * Random number.
    */
   qapi_BLE_Random_Number_t Rand;

   /**
    * Encryption diversifier.
    */
   uint16_t                 EDIV;
} qapi_BLE_GAP_LE_Key_Request_Info_t;

/** Size of the #QAPI_BLE_GAP_LE_KEY_REQUEST_INFO_DATA_SIZE structure. */
#define QAPI_BLE_GAP_LE_KEY_REQUEST_INFO_DATA_SIZE                         (sizeof(GAP_LE_Link_Key_Request_Info_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_SECURITY_REQUEST_E.
 */
typedef struct qapi_BLE_GAP_LE_Security_Request_s
{
   /**
    * Bonding type.
    */
   qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type;

   /**
    * Man in the Middle (MITM) protection.
    */
   boolean_t                      MITM;
} qapi_BLE_GAP_LE_Security_Request_t;

/** Size of the #qapi_BLE_GAP_LE_Security_Request_t structure. */
#define QAPI_BLE_GAP_LE_SECURITY_REQUEST_DATA_SIZE                         (sizeof(qapi_BLE_GAP_LE_Security_Request_t))

/**
* Enumeration of the different types of confirmation requests
* that may be generated.
*
* The #QAPI_BLE_CRT_NONE_E type means that * "Just Works" pairing
* method is being used.
*
* The #QAPI_BLE_CRT_DISPLAY_YES_NO_E and
* #QAPI_BLE_CRT_OOB_SECURE_CONNECTIONS_E types will only been seen
* when Secure Connections has been enabled and when Secure
* Connections pairing with a remote device is taking place (in a
* #QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E event).
*/
typedef enum
{
   QAPI_BLE_CRT_NONE_E,
   /**< Indicates a request for just works confirmation request. */

   QAPI_BLE_CRT_PASSKEY_E,
   /**< Indicates a request for passkey input. */

   QAPI_BLE_CRT_DISPLAY_E,
   /**< Indicates a request for passkey display. */

   QAPI_BLE_CRT_OOB_E,
   /**< Indicates a request for Out of Band data. */

   QAPI_BLE_CRT_DISPLAY_YES_NO_E,
   /**< Indicates a request for displaying a passkey and
        answering yes/no of user. */

   QAPI_BLE_CRT_OOB_SECURE_CONNECTIONS_E
   /**< Indicates a request for secure connections Out of Band data. */
} qapi_BLE_GAP_LE_Confirmation_Request_Type_t;

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_CONFIRMATION_REQUEST_E.
 *
 * The DisplayPasskey member is only valid when RequestType is
 * #QAPI_BLE_CRT_DISPLAY_E, and this member should be display to the user
 * to allow the remote device to enter it.
 *
 * The DisplayPasskey member is between 000,000 and 999,999 and all
 * digits must be displayed, including leading zeros.
 */
typedef struct qapi_BLE_GAP_LE_Confirmation_Request_s
{
   /**
    * Confirmation request type.
    */
   qapi_BLE_GAP_LE_Confirmation_Request_Type_t Request_Type;

   /**
    * Passkey that must be displayed to the user.
    */
   uint32_t                                    Display_Passkey;

   /**
    * Negotiated encryption key size.
    */
   uint8_t                                     Negotiated_Encryption_Key_Size;
} qapi_BLE_GAP_LE_Confirmation_Request_t;

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E.
 *
 * The DisplayPasskey member is only valid when RequestType is
 * #QAPI_BLE_CRT_DISPLAY_E OR QAPI_BLE_CRT_DISPLAY_YES_NO_E, and this
 * member should be display to the user to allow the remote device to
 * enter it (#QAPI_BLE_CRT_DISPLAY_E) or to compare with the corresponding
 * value on the remote device (#QAPI_BLE_CRT_DISPLAY_YES_NO_E) .
 *
 * The DisplayPasskey member is between 000,000 and 999,999 and all
 * digits must be displayed, including leading zeroes.
 *
 * If the QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_
 * SECURE_CONNECTIONS flag is set in the Flags member, this indicates
 * that secure connections pairing (Version 4.2) is taking place.
 *
 * If the QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_
 * KEYPRESS_NOTIFICATIONS_REQUESTED flag is set in the Flags member
 * this indicates that both sides have indicated support for keypress
 * notifications and the local device shall send keypress notification
 * while the passkey is being entered.
 *
 * All Requests types must be responded to with the correct type via the
 * qapi_BLE_GAP_LE_Authentication_Response() API. this includes
 * #QAPI_BLE_CRT_DISPLAY_E, which did not need to be responded to with the
 * LEGACY QAPI_BLE_LAT_CONFIRMATION_REQUEST_E event.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Confirmation_Request_s
{
   /**
    * Confirmation request type.
    */
   qapi_BLE_GAP_LE_Confirmation_Request_Type_t Request_Type;

   /**
    * Passkey that must be displayed to the user.
    */
   uint32_t                                    Display_Passkey;

   /**
    * Negotiated encryption key size.
    */
   uint8_t                                     Negotiated_Encryption_Key_Size;

   /**
    * Bitmask for the extended confirmation request flags.
    *
    * Valid values have the form
    * QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_XXX.
    */
   unsigned long                               Flags;
} qapi_BLE_GAP_LE_Extended_Confirmation_Request_t;

/** Bit flag for the Flags field of the
    #qapi_BLE_GAP_LE_Extended_Confirmation_Request_t structure.
    Indicates that Secure Connections pairing is taking place.*/
#define QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_SECURE_CONNECTIONS               0x00000001

/** Bit flag for the Flags field of the
    #qapi_BLE_GAP_LE_Extended_Confirmation_Request_t structure.
    Indicates that key press notifications are requested of the application.*/
#define QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_KEYPRESS_NOTIFICATIONS_REQUESTED 0x00000002

/** Bit flag for the Flags field of the
    #qapi_BLE_GAP_LE_Extended_Confirmation_Request_t structure.
    Indicates that just works pairing is taking place.*/
#define QAPI_BLE_GAP_LE_EXTENDED_CONFIRMATION_REQUEST_FLAGS_JUST_WORKS_PAIRING               0x00000004

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_EXTENDED_OUT_OF_BAND_INFORMATION_E.
 *
 * This information represents the information that is to be transmitted
 * over the OOB interface to the remote device.
 */
typedef struct qapi_BLE_GAP_LE_Extended_Out_Of_Band_Information_s
{
   /**
    * Bluetooth address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t             AddressType;

   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t                         BD_ADDR;

   /**
    * Confirmation value.
    */
   qapi_BLE_Secure_Connections_Confirmation_t ConfirmationValue;

   /**
    * Random number.
    */
   qapi_BLE_Secure_Connections_Randomizer_t   RandomNumber;
} qapi_BLE_GAP_LE_Extended_Out_Of_Band_Information_t;

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * #qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_PAIRING_STATUS_E.
 */
typedef struct qapi_BLE_GAP_LE_Pairing_Status_s
{
   /**
    * Flags if the the encryption key is authenticated.
    */
   boolean_t  Authenticated_Encryption_Key;

   /**
    * Pairing status.
    */
   uint8_t    Status;

   /**
    * Negotiated encryption key size.
    */
   uint8_t    Negotiated_Encryption_Key_Size;
} qapi_BLE_GAP_LE_Pairing_Status_t;

/** Size of the #qapi_BLE_GAP_LE_Pairing_Status_t structure. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_DATA_SIZE                           (sizeof(qapi_BLE_GAP_LE_Pairing_Status_t))

/** Indicates that LE pairing was successfull. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_NO_ERROR                                   0x00

/** Indicates that LE pairing failed due to a disconnection of the LE link. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_DISCONNECTED                               0x01

/** Indicates that LE pairing failed due to a local failure to allocate
    required resources. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_LOCAL_RESOURCES                            0x02

/** Indicates that LE pairing failed due to a protocol timeout. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_PROTOCOL_TIMEOUT                           0x03

/** Indicates that LE pairing failed due to a passkey entry failure. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_PASSKEY_ENTRY_FAILED                       0x04

/** Indicates that LE pairing failed due to out of band data not being
    available. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_OOB_NOT_AVAILABLE                          0x05

/** Indicates that LE pairing failed due to authentication requirements no
    being met. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_AUTHENTICATION_REQUIREMENTS                0x06

/** Indicates that LE pairing failed due to the confirmation value not
    matching the expected value. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_CONFIRM_VALUE_FAILED                       0x07

/** Indicates that LE pairing failed due to pairing not being supported. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_PAIRING_NOT_SUPPORTED                      0x08

/** Indicates that LE pairing failed due to an unsupported encryption
     key size. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_QAPI_BLE_ENCRYPTION_KEY_SIZE               0x09

/** Indicates that LE pairing failed due to command not being supported. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_COMMAND_NOT_SUPPORTED                      0x0A

/** Indicates that LE pairing failed due to an unspecified reason. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_UNSPECIFIED_REASON                         0x0B

/** Indicates that LE pairing failed due to multiple failed pairing
    attempts. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_REPEATED_ATTEMPTS                          0x0C

/** Indicates that LE pairing failed due to an invalid parameter. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_INVALID_PARAMETERS                         0x0D

/** Indicates that LE pairing failed due to Diffie Hellman Key
    Check failure. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_DHKEY_CHECK_FAILED                         0x0E

/** Indicates that LE pairing failed due to a failed numeric
    comparison. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_NUMERIC_COMPARISON_FAILED                  0x0F

/** Indicates that LE pairing failed due to classic pairing being in
    progess. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_CLASSIC_PAIRING_IN_PROGRESS                0x10

/** Indicates that LE pairing failed due to cross transport key
    generation not being allowed. */
#define QAPI_BLE_GAP_LE_PAIRING_STATUS_CROSS_TRANSPORT_KEY_GENERATION_NOT_ALLOWED 0x11

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_ENCRYPTION_INFORMATION_E.
 */
typedef struct qapi_BLE_GAP_LE_Encryption_Request_Information_s
{
   /**
    * Encryption key size.
    */
   uint8_t Encryption_Key_Size;
} qapi_BLE_GAP_LE_Encryption_Request_Information_t;

/** Size of the
    #qapi_BLE_GAP_LE_Encryption_Request_Information_t structure. */
#define QAPI_BLE_GAP_LE_ENCRYPTION_REQUEST_INFORMATION_DATA_SIZE           (sizeof(qapi_BLE_GAP_LE_Encryption_Request_Information_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATION_E event when the
 * GAP_LE_Authentication_Event_Type of the
 * qapi_BLE_GAP_LE_Authentication_Event_Data_t structure is set to
 * #QAPI_BLE_LAT_SECURITY_ESTABLISHMENT_COMPLETE_E.
 */
typedef struct qapi_BLE_GAP_LE_Security_Establishment_Complete_s
{
   /**
    * Security re-establishment status.
    */
   uint8_t Status;
} qapi_BLE_GAP_LE_Security_Establishment_Complete_t;

/** Size of the
    #qapi_BLE_GAP_LE_Security_Establishment_Complete_t structure. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_COMPLETE_DATA_SIZE          (sizeof(qapi_BLE_GAP_LE_Security_Establishment_Complete_t))

/** Indicates that LE secure establishment was successful. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_NO_ERROR                 0x00

/** Indicates that LE secure establishment failed due to a Long Term Key
    failure. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_LONG_TERM_KEY_ERROR      0x01

/** Indicates that LE secure establishment failed due to an invalid EDIV or
    RAND value. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_EDIV_RAND_INVALID        0x02

/** Indicates that LE secure establishment failed due to the remote device
    attempting to re-pair. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_DEVICE_TRIED_TO_REPAIR   0x03

/** Indicates that LE secure establishment failed due to the link
    disconnecting. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_LINK_DISCONNECTED        0x04

/** Indicates that LE secure establishment failed due to a timeout. */
#define QAPI_BLE_GAP_LE_SECURITY_ESTABLISHMENT_STATUS_CODE_TIMEOUT                  0x05

/**
 * Structure that represents the data that can be returned in the GAP LE
 * Authentication Callback.
 */
typedef struct qapi_BLE_GAP_LE_Authentication_Event_Data_s
{
   /**
    * Authentication event type. This field is also used to indicate
    * the member that is access of the Authentication_Event_Data field.
    */
   qapi_BLE_GAP_LE_Authentication_Event_Type_t           GAP_LE_Authentication_Event_Type;

   /**
    * Remote device address.
    */
   qapi_BLE_BD_ADDR_t                                    BD_ADDR;
   union
   {
      /**
       * Long Term Key (LTK) request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_LONG_TERM_KEY_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Key_Request_Info_t                 Long_Term_Key_Request;

      /**
       * Pairing request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_PAIRING_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Pairing_Capabilities_t             Pairing_Request;

      /**
       * Extended pairing request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_EXTENDED_PAIRING_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t    Extended_Pairing_Request;

      /**
       * Security request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_SECURITY_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Security_Request_t                 Security_Request;

      /**
       * Confirmation request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_CONFIRMATION_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Confirmation_Request_t             Confirmation_Request;

      /**
       * Extended confirmation request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_EXTENDED_CONFIRMATION_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Extended_Confirmation_Request_t    Extended_Confirmation_Request;

      /**
       * Extended out of band information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_EXTENDED_OUT_OF_BAND_INFORMATION_E.
       */
      qapi_BLE_GAP_LE_Extended_Out_Of_Band_Information_t Extended_Out_Of_Band_Information;

      /**
       * Pairing status information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_PAIRING_STATUS_E.
       */
      qapi_BLE_GAP_LE_Pairing_Status_t                   Pairing_Status;

      /**
       * Keypress notification. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_KEYPRESS_NOTIFICATION_E.
       */
      qapi_BLE_GAP_LE_Keypress_t                         Keypress_Notification;

      /**
       * Encryption request information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_ENCRYPTION_INFORMATION_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Encryption_Request_Information_t   Encryption_Request_Information;

      /**
       * Encryption information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_ENCRYPTION_INFORMATION_E.
       */
      qapi_BLE_GAP_LE_Encryption_Information_t           Encryption_Information;

      /**
       * Identity information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_IDENTITY_INFORMATION_E.
       */
      qapi_BLE_GAP_LE_Identity_Information_t             Identity_Information;

      /**
       * Signing information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_SIGNING_INFORMATION_E.
       */
      qapi_BLE_GAP_LE_Signing_Information_t              Signing_Information;

      /**
       * Security restablishment complete information. Valid if the
       * GAP_LE_Authentication_Event_Type is
       * #QAPI_BLE_LAT_SECURITY_ESTABLISHMENT_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Security_Establishment_Complete_t  Security_Establishment_Complete;
   }
   /**
    * Authentication event data.
    */
   Authentication_Event_Data;
} qapi_BLE_GAP_LE_Authentication_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Authentication_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_AUTHENTICATION_EVENT_DATA_SIZE                     (sizeof(qapi_BLE_GAP_LE_Authentication_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_E event.
 *
 * All members of this structure are specified in milliseconds except
 * Slave_Latency, which is specified in the number of connection events.
 */
typedef struct qapi_BLE_GAP_LE_Connection_Parameter_Update_Request_Event_Data_s
{
   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Minimum connection interval.
    */
   uint16_t           Conn_Interval_Min;

   /**
    * Maximum connection interval.
    */
   uint16_t           Conn_Interval_Max;

   /**
    * Slave latency.
    */
   uint16_t           Slave_Latency;

   /**
    * Supervision timeout for the connection.
    */
   uint16_t           Conn_Supervision_Timeout;
} qapi_BLE_GAP_LE_Connection_Parameter_Update_Request_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_Parameter_Update_Request_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_EVENT_DATA_SIZE   (sizeof(qapi_BLE_GAP_LE_Connection_Parameter_Update_Request_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Connection_Parameter_Update_Response_Event_Data_s
{
   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Flags whether the master of the connection has accepted or
    * rejected the connection parameter update request.
    */
   boolean_t          Accepted;
} qapi_BLE_GAP_LE_Connection_Parameter_Update_Response_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_Parameter_Update_Response_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_EVENT_DATA_SIZE (sizeof(qapi_BLE_GAP_LE_Connection_Parameter_Update_Response_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATED_E event.
 */
typedef struct qapi_BLE_GAP_LE_Connection_Parameter_Updated_Event_Data_s
{
   /**
    * Status of the connection parameter update.
    */
   uint8_t                                         Status;

   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t                              BD_ADDR;

   /**
    * Current connection parameters.
    */
   qapi_BLE_GAP_LE_Current_Connection_Parameters_t Current_Connection_Parameters;
} qapi_BLE_GAP_LE_Connection_Parameter_Updated_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_Parameter_Updated_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_PARAMETER_UPDATED_EVENT_DATA_SIZE (sizeof(qapi_BLE_GAP_LE_Connection_Parameter_Updated_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_E event.
 */
typedef struct qapi_BLE_GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data_s
{
   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;
} qapi_BLE_GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_EVENT_DATA_SIZE (sizeof(qapi_BLE_GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_DATA_LENGTH_CHANGE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Data_Length_Change_Event_Data_s
{
   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t BD_ADDR;

   /**
    * Maximum octets that can be transmitted.
    */
   uint16_t           MaxTxOctets;

   /**
    * Maximum transmit time.
    */
   uint16_t           MaxTxTime;

   /**
    * Maximum octets that can be received.
    */
   uint16_t           MaxRxOctets;

   /**
    * Maximum receiving time.
    */
   uint16_t           MaxRxTime;
} qapi_BLE_GAP_LE_Data_Length_Change_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Data_Length_Change_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_DATA_LENGTH_CHANGE_EVENT_DATA_SIZE                 (sizeof(qapi_BLE_GAP_LE_Data_Length_Change_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_LOCAL_P256_PUBLIC_KEY_UPDATE_COMPLETE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_s
{
   /**
    * Status.
    */
   uint8_t Status;
} qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_LOCAL_P256_PUBLIC_KEY_UPDATE_COMPLETE_EVENT_DATA_SIZE  (sizeof(qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_t))

/**
 * Structure that represents the data returned in a GAP LE
 * #QAPI_BLE_ET_LE_PHY_UPDATE_COMPLETE_E event.
 */
typedef struct qapi_BLE_GAP_LE_Phy_Update_Complete_Event_Data_s
{
   /**
    * Status of the PHY Update Complete Event.
    */
   uint8_t                    Status;

   /**
    * Bluetooth address.
    */
   qapi_BLE_BD_ADDR_t         BD_ADDR;

   /**
    * Current Tx PHY of the connection if the Status field
    * indicates success.
    */
   qapi_BLE_GAP_LE_PHY_Type_t TX_PHY;

   /**
    * Current Rx PHY of the connection if the Status field
    * indicates success.
    */
   qapi_BLE_GAP_LE_PHY_Type_t RX_PHY;
} qapi_BLE_GAP_LE_Phy_Update_Complete_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Phy_Update_Complete_Event_Data_t structure.*/
#define QAPI_BLE_GAP_LE_PHY_UPDATE_COMPLETE_EVENT_DATA_SIZE                (sizeof(qapi_BLE_GAP_LE_Phy_Update_Complete_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_E event that is sent
 * by the controller to indicate that the local device is synchronized to a
 * periodic advertising train.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 *
 * The Periodic_Advertising_Interval member is specified in milli-seconds.
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Established_Event_Data_s
{
   /**
    * Status for the synchronization.
    */
   uint8_t                        Status;

   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t                       Sync_Handle;

   /**
    * Identifies the advertiser's advertising set.
    */
   uint8_t                        Advertising_SID;

   /**
    * Advertiser's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Advertiser_Address_Type;

   /**
    * Advertisers address.
    */
   qapi_BLE_BD_ADDR_t             Advertiser_Address;

   /**
    * PHY used by the advertiser for the periodic advertisements.
    */
   qapi_BLE_GAP_LE_PHY_Type_t     Advertiser_PHY;

   /**
    * Advertising interval.
    */
   uint32_t                       Periodic_Advertising_Interval;

   /**
    * Advertiser's clock accuracy.
    */
   uint8_t                        Advertiser_Clock_Accuracy;
} qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Established_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Established_Event_Data_t structure.*/
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_EVENT_DATA_SIZE (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Established_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_REPORT_E event that is sent by the
 * controller to indicate that a periodic advertising report has been
 * received.
 *
 * The Sync_Handle will previously have been dispatched in a
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_E to indicate
 * the periodic advertiser.
 *
 * The Raw_Report_Length and Raw_Report_Data members contain
 * the length (in bytes) of the actual report received, as
 * well as a pointer to the actual bytes present in the
 * report, respectively.
 *
 * If the Data_Status member is set to
 * #QAPI_BLE_DS_INCOMPLETE_DATA_PENDING_E then more advertising reports
 * will be received with additional data from the
 * advertiser. If the Data_Status member is set to
 * #QAPI_BLE_DS_INCOMPLETE_DATA_TRUNCATED_E then the data received is not
 * all of the data advertised, however no more events are
 * pending for this advertiser.
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_Report_Event_Data_s
{
   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t                                   Sync_Handle;

   /**
    * Advertiser's transmit power.
    */
   int8_t                                     Tx_Power;

   /**
    * Remote signal strength Indicator.
    */
   int8_t                                     RSSI;

   /**
    * Contant tone extension type.
    */
   uint8_t                                    CTE_Type;

   /**
    * Advertising data status.
    */
   qapi_BLE_GAP_LE_Advertising_Data_Status_t  Data_Status;

   /**
    * Advertising data Length.
    */
   uint8_t                                    Raw_Report_Length;

   /**
    * Advertising data.
    */
   uint8_t                                   *Raw_Report_Data;
} qapi_BLE_GAP_LE_Periodic_Advertising_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_Report_Event_Data_t structure.*/
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_REPORT_EVENT_DATA_SIZE        (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Report_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_LOST_E event that is sent by the
 * controller to indicate that the synchronization to the periodic advertising
 * train has been lost.
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data_s
{
   uint16_t Sync_Handle;  /**< Handle for periodic advertising synchronization lost event data. */
} qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data_t structure.*/
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT_DATA_SIZE     (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_ADVERTISING_SET_TERMINATED_E event that is sent by the
 * controller to indicate that advertising for the specified
 * advertising set has terminated.
 *
 * If Status is set to QAPI_BLE_HCI_ERROR_CODE_SUCCESS the set was
 * terminated due to a connection being created.  If not the error code
 * indicates what caused the set to be terminated.
 *
 * Connection_Address_Type and Connection_Address indicate the address
 * type and address of the device whose connection request caused the set
 * to be terminated. These fields are only valid if the Status member is
 * set to QAPI_BLE_HCI_ERROR_CODE_SUCCESS.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_s
{
   /** Status. */
   uint8_t                        Status;

   /** Advertising handle. */
   uint8_t                        Advertising_Handle;

   /** Number of completed extended advertising events. */
   uint8_t                        Num_Completed_Ext_Advertising_Events;

   /** Connection address type. */
   qapi_BLE_GAP_LE_Address_Type_t Connection_Address_Type;

   /** Connection address. */
   qapi_BLE_BD_ADDR_t             Connection_Address;
} qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_ADVERTISING_SET_TERMINATED_EVENT_DATA_SIZE         (sizeof(qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_SCAN_REQUEST_RECEIVED_E event that is sent by the
 * controller to indicate that a scan request has been received.  This
 * event will only received if a scan response is received and the
 * advertising set it is received for requested these events.
 *
 * The following enumerated types may be returned with the
 * Scanner_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Scan_Request_Received_Event_Data_s
{
   /** Advertising handle. */
   uint8_t                        Advertising_Handle;

   /** Scanner address type. */
   qapi_BLE_GAP_LE_Address_Type_t Scanner_Address_Type;

   /** Scanner Address. */
   qapi_BLE_BD_ADDR_t             Scanner_Address;
} qapi_BLE_GAP_LE_Scan_Request_Received_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Scan_Request_Received_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_SCAN_REQUEST_RECEIVED_EVENT_DATA_SIZE              (sizeof(qapi_BLE_GAP_LE_Scan_Request_Received_Event_Data_t))

/**
 * Enumeration of the channel selection algorithms that may
 * be used to determine the hopping frequencies for an LE Data
 * Connection.
 */
typedef enum
{
   QAPI_BLE_SA_ALGORITHM_NUM1_E,
   /**< Channel selection algorithm 1. */

   QAPI_BLE_SA_ALGORITHM_NUM2_E
   /**< Channel selection algorithm 2. */
} qapi_BLE_GAP_LE_Channel_Selection_Algorithm_t;

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_CHANNEL_SELECTION_ALGORITHM_UPDATE_E event that is sent
 * by the controller to indicate that the channel selection algorithm
 * used for a data connection.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_s
{
   qapi_BLE_GAP_LE_Channel_Selection_Algorithm_t Channel_Selection_Algorithm; /**< Channel selection algorithm. */
   qapi_BLE_GAP_LE_Address_Type_t                Connection_Address_Type;     /**< Connection address type. */
   qapi_BLE_BD_ADDR_t                            Connection_Address;          /**< Connection address. */
} qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CHANNEL_SELECTION_ALGORITHM_UPDATE_EVENT_DATA_SIZE  (sizeof(qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_t))

/**
 * Enumeration for valid IQ report packet status types.
 */
typedef enum
{
   QAPI_BLE_IRPT_VALID_CRC_E,
   /**<  CRC is valid.   */

   QAPI_BLE_IRPT_INVALID_CRC_PACKET_FIELD_METHOD_E,
   /**< Invalid CRC packet and field method was used to determine length. */

   QAPI_BLE_IRPT_INVALID_CRC_OTHER_METHOD_E,
   /**< Invalid CRC packet and other method was used to determine length. */

   QAPI_BLE_IRPT_INSUFFICIENT_RESOURCES_E
   /**< Insufficient resources to process IQ samples. */
} qapi_BLE_GAP_LE_IQ_Report_PS_Type_t;

/**
 * Structure that represents an IQ sample pair.
 */
typedef struct qapi_BLE_GAP_LE_CTE_IQ_Sample_s
{
   int8_t I_Sample;
   /**<  I sample. */

   int8_t Q_Sample;
   /**<  Q sample. */
} qapi_BLE_GAP_LE_CTE_IQ_Sample_t;

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_CONNECTIONLESS_IQ_REPORT_E event that is sent by the
 * controller to indicate that IQs have been sampled from a CTE in a
 * periodic advertisement.
 *
 * The controller is NOT required to generate this event if
 * the Packet_Status field is QAPI_BLE_IRPT_VALID_CRC_E.
 */
typedef struct qapi_BLE_GAP_LE_Connectionless_IQ_Report_Event_Data_s
{
   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t                               Sync_Handle;

   /**
    * Advertising channel index.
    */
   uint8_t                                Channel_Index;

   /**
    * Remote signal strength indicator.
    */
   int16_t                                RSSI;

   /**
    * Antenna used for the RSSI.
    */
   uint8_t                                RSSI_Antenna_ID;

   /**
    * Contant tone extension type.
    */
   qapi_BLE_GAP_LE_CTE_Type_t             CTE_Type;

   /**
    * Slot durations used for the CTE.
    */
   qapi_BLE_GAP_LE_Slot_Durations_Type_t  Slot_Durations;

   /**
    * Status of the packet.
    */
   qapi_BLE_GAP_LE_IQ_Report_PS_Type_t    Packet_Status;

   /**
    * Periodic advertising event counter.
    */
   uint16_t                               Pa_Event_Counter;

   /**
    * Number of IQ samples taken.
    */
   uint8_t                                Sample_Count;

   /**
    * List of IQ samples.
    */
   qapi_BLE_GAP_LE_CTE_IQ_Sample_t       *IQ_Samples;
} qapi_BLE_GAP_LE_Connectionless_IQ_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connectionless_IQ_Report_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTIONLESS_IQ_REPORT_EVENT_DATA_SIZE(_x)       ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GAP_LE_Connectionless_IQ_Report_Event_Data_t, IQ_Samples) + ((_x) * sizeof(qapi_BLE_GAP_LE_CTE_IQ_Sample_t))))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_CONNECTION_IQ_REPORT_E event that is sent by the controller
 * to indicate that IQs have been sampled from a CTE in a CTE request
 * response.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 *
 * The controller is NOT required to generate this event if
 * the Packet_Status field is QAPI_BLE_IRPT_VALID_CRC_E.
 */
typedef struct qapi_BLE_GAP_LE_Connection_IQ_Report_Event_Data_s
{
   /**
    * Remote device's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t         Connection_Address_Type;

   /**
    * Remote device's address.
    */
   qapi_BLE_BD_ADDR_t                     Connection_Address;

   /**
    * PHY used for the CTE request response.
    */
   qapi_BLE_GAP_LE_PHY_Type_t             RX_PHY;

   /**
    * Data channel index.
    */
   uint8_t                                Data_Channel_Index;

   /**
    * Remote signal strength indicator.
    */
   int16_t                                RSSI;

   /**
    * Antenna used for the RSSI.
    */
   uint8_t                                RSSI_Antenna_ID;

   /**
    * Contant tone extension type.
    */
   qapi_BLE_GAP_LE_CTE_Type_t             CTE_Type;

   /**
    * Slot durations used for the CTE.
    */
   qapi_BLE_GAP_LE_Slot_Durations_Type_t  Slot_Durations;

   /**
    * Status of the packet.
    */
   qapi_BLE_GAP_LE_IQ_Report_PS_Type_t    Packet_Status;

   /**
    * Connection event counter.
    */
   uint16_t                               Conn_Event_Counter;

   /**
    * Number of IQ samples taken.
    */
   uint8_t                                Sample_Count;

   /**
    * List of IQ samples.
    */
   qapi_BLE_GAP_LE_CTE_IQ_Sample_t       *IQ_Samples;
} qapi_BLE_GAP_LE_Connection_IQ_Report_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Connection_IQ_Report_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CONNECTION_IQ_REPORT_EVENT_DATA_SIZE(_x)           ((QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GAP_LE_Connection_IQ_Report_Event_Data_t, IQ_Samples) + ((_x) * sizeof(qapi_BLE_GAP_LE_CTE_IQ_Sample_t))))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_CTE_REQUEST_FAILED_E event that is sent by the controller
 * to indicate that a CTE request has failed.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_CTE_Request_Failed_Event_Data_s
{
   /**
    * Reason for the failure.
    */
   uint8_t                        Status;

   /**
    * Remote device's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Connection_Address_Type;

   /**
    * Remote device's address type.
    */
   qapi_BLE_BD_ADDR_t             Connection_Address;
} qapi_BLE_GAP_LE_CTE_Request_Failed_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_CTE_Request_Failed_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_CTE_REQUEST_FAILED_EVENT_DATA_SIZE                 (sizeof(qapi_BLE_GAP_LE_CTE_Request_Failed_Event_Data_t))

/**
 * Structure that represents the information returned in an
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_E event
 * that is sent by the controller to indicate that periodic advertising
 * sync information has been received from a connected remote device and
 * the local device has synchronized to the periodic advertising.
 *
 * The following enumerated types may be returned with the
 * Connection_Address_Type member:
 *
 *    @li QAPI_BLE_LAT_PUBLIC_E
 *    @li QAPI_BLE_LAT_RANDOM_E
 *    @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 *    @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and #QAPI_BLE_LAT_RANDOM_IDENTITY_E
 * types will only be returned if the address resolution in the
 * controller has been enabled via the
 * qapi_BLE_GAP_LE_Set_Address_Resolution_Enable() function. These two
 * identity types, when returned, indicate that the controller has
 * resolved an address received in an advertising packet to the
 * specified identity address (that must have been added to the
 * resolving list via the qapi_BLE_GAP_LE_Add_Device_To_Resolving_List()
 * API function).
 */
typedef struct qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_s
{
   /**
    * Status of the synchronization.
    */
   uint8_t                        Status;

   /**
    * Remote device's address type.
    */
   qapi_BLE_GAP_LE_Address_Type_t Connection_Address_Type;

   /**
    * Remote device's address type.
    */
   qapi_BLE_BD_ADDR_t             Connection_Address;

   /**
    * Host specific information sent by the remote device.
    */
   uint16_t                       Service_Data;

   /**
    * Identifies the synchronized periodic advertising train.
    */
   uint16_t                       Sync_Handle;

   /**
    * Identifies the advertiser's advertising set.
    */
   uint8_t                        Advertising_SID;

   /**
    * Advertiser's address type.
    */
   uint8_t                        Advertiser_Address_Type;

   /**
    * Advertisers address.
    */
   qapi_BLE_BD_ADDR_t             Advertiser_Address;

   /**
    * PHY used by the advertiser for the periodic advertisements.
    */
   qapi_BLE_GAP_LE_PHY_Type_t     Advertiser_PHY;

   /**
    * Advertising interval.
    */
   uint16_t                       Periodic_Advertising_Interval;

   /**
    * Advertiser's clock accuracy.
    */
   uint8_t                        Advertiser_Clock_Accuracy;
} qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_EVENT_DATA_SIZE  (sizeof(qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t))

/**
 * This structure is a container structure that holds all GAP LE Event
 * Data.
 */
typedef struct qapi_BLE_GAP_LE_Event_Data_s
{
   /**
    * Event data type. This field is also used to indicate the member
    * of the Event_Data field.
    *
    * The #QAPI_BLE_ET_LE_SCAN_TIMEOUT_E contains no data.
    */
   qapi_BLE_GAP_LE_Event_Type_t Event_Data_Type;

   /**
    * Total event data size.
    */
   uint16_t                     Event_Data_Size;
   union
   {
      /**
       * Remote features event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_REMOTE_FEATURES_RESULT_E.
       */
      qapi_BLE_GAP_LE_Remote_Features_Event_Data_t                             *GAP_LE_Remote_Features_Event_Data;

      /**
       * Advertising report event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_ADVERTISING_REPORT_E.
       */
      qapi_BLE_GAP_LE_Advertising_Report_Event_Data_t                          *GAP_LE_Advertising_Report_Event_Data;

      /**
       * Direct advertising report event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E.
       */
      qapi_BLE_GAP_LE_Direct_Advertising_Report_Event_Data_t                   *GAP_LE_Direct_Advertising_Report_Event_Data;

      /**
       * Connection complete event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_CONNECTION_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Connection_Complete_Event_Data_t                         *GAP_LE_Connection_Complete_Event_Data;

      /**
       * Disconnection complete event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_DISCONNECTION_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Disconnection_Complete_Event_Data_t                      *GAP_LE_Disconnection_Complete_Event_Data;

      /**
       * Encryption change event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_ENCRYPTION_CHANGE_E.
       */
      qapi_BLE_GAP_LE_Encryption_Change_Event_Data_t                           *GAP_LE_Encryption_Change_Event_Data;

      /**
       * Encryption change refresh event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_ENCRYPTION_REFRESH_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Encryption_Refresh_Complete_Event_Data_t                 *GAP_LE_Encryption_Refresh_Complete_Event_Data;

      /**
       * Authentication event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_AUTHENTICATION_E.
       */
      qapi_BLE_GAP_LE_Authentication_Event_Data_t                              *GAP_LE_Authentication_Event_Data;

      /**
       * Connection parameter update response event data. This is
       * valid if the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_REQUEST_E.
       */
      qapi_BLE_GAP_LE_Connection_Parameter_Update_Request_Event_Data_t         *GAP_LE_Connection_Parameter_Update_Request_Event_Data;

      /**
       * Connection parameter update request event data. This is
       * valid if the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_E.
       */
      qapi_BLE_GAP_LE_Connection_Parameter_Update_Response_Event_Data_t        *GAP_LE_Connection_Parameter_Update_Response_Event_Data;

      /**
       * Connection parameter updated event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATED_E.
       */
      qapi_BLE_GAP_LE_Connection_Parameter_Updated_Event_Data_t                *GAP_LE_Connection_Parameter_Updated_Event_Data;

      /**
       * Authenticated payload timeout event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_E.
       */
      qapi_BLE_GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data_t       *GAP_LE_Authenticated_Payload_Timeout_Expired_Event_Data;

      /**
       * Authenticated payload timeout event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_DATA_LENGTH_CHANGE_E.
       */
      qapi_BLE_GAP_LE_Data_Length_Change_Event_Data_t                          *GAP_LE_Data_Length_Change_Event_Data;

      /**
       * P256 public/private key pair generation complete event data.
       * This is valid if the Event_Data_Type is
       * #QAPI_BLE_ET_LE_LOCAL_P256_PUBLIC_KEY_UPDATE_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data_t       *GAP_LE_Local_P256_Public_Key_Update_Complete_Event_Data;

      /**
       * PHY Update complete event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_PHY_UPDATE_COMPLETE_E.
       */
      qapi_BLE_GAP_LE_Phy_Update_Complete_Event_Data_t                         *GAP_LE_Phy_Update_Complete_Event_Data;

      /**
       * Extended advertising report event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_EXTENDED_ADVERTISING_REPORT_E.
       */
      qapi_BLE_GAP_LE_Extended_Advertising_Report_Event_Data_t                 *GAP_LE_Extended_Advertising_Report_Event_Data;

      /**
       * Periodic advertising sync established event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_E.
       */
      qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Established_Event_Data_t       *GAP_LE_Periodic_Advertising_Sync_Established_Event_Data;

      /**
       * Periodic advertising report event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_REPORT_E.
       */
      qapi_BLE_GAP_LE_Periodic_Advertising_Report_Event_Data_t                 *GAP_LE_Periodic_Advertising_Report_Event_Data;

      /**
       * Periodic advertising sync lost event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_LOST_E.
       */
      qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data_t              *GAP_LE_Periodic_Advertising_Sync_Lost_Event_Data;

      /**
       * Extended advertising set terminated event data. This is
       * valid if the Event_Data_Type is
       * #QAPI_BLE_ET_LE_ADVERTISING_SET_TERMINATED_E.
       */
      qapi_BLE_GAP_LE_Advertising_Set_Terminated_Event_Data_t                  *GAP_LE_Advertising_Set_Terminated_Event_Data;

      /**
       * Scan request received event data. This is valid if the
       * Event_Data_Type is QAPI_BLE_ET_LE_SCAN_REQUEST_RECEIVED_E.
       */
      qapi_BLE_GAP_LE_Scan_Request_Received_Event_Data_t                       *GAP_LE_Scan_Request_Received_Event_Data;

      /**
       * Channel selection algorithm update event data. This is valid
       * if the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CHANNEL_SELECTION_ALGORITHM_UPDATE_E.
       */
      qapi_BLE_GAP_LE_Channel_Selection_Algorithm_Update_Event_Data_t          *GAP_LE_Channel_Selection_Algorithm_Update_Event_Data;

      /**
       * Connectionless IQ report event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CONNECTIONLESS_IQ_REPORT_E.
       */
      qapi_BLE_GAP_LE_Connectionless_IQ_Report_Event_Data_t                    *GAP_LE_Connectionless_IQ_Report_Event_Data;

      /**
       * Connection IQ report event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CONNECTION_IQ_REPORT_E.
       */
      qapi_BLE_GAP_LE_Connection_IQ_Report_Event_Data_t                        *GAP_LE_Connection_IQ_Report_Event_Data;

      /**
       * CTE request failed event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_CTE_REQUEST_FAILED_E.
       */
      qapi_BLE_GAP_LE_CTE_Request_Failed_Event_Data_t                          *GAP_LE_CTE_Request_Failed_Event_Data;

      /**
       * Periodic advertising sync transfer received event data. This is valid if
       * the Event_Data_Type is
       * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_E.
       */
      qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data_t *GAP_LE_Periodic_Advertising_Sync_Transfer_Received_Event_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_GAP_LE_Event_Data_t;

/** Size of the #qapi_BLE_GAP_LE_Event_Data_t structure. */
#define QAPI_BLE_GAP_LE_EVENT_DATA_SIZE                                    (sizeof(qapi_BLE_GAP_LE_Event_Data_t))

/**
 * @brief
 * Declared type that represents the Prototype Function for the
 * GAP LE event callback.
 *
 * @details
 * This function is called whenever a callback has been registered
 * for the specified GAP LE action that is associated with the specified
 * Bluetooth Stack ID. This function passes to the caller the Bluetooth
 * Stack ID, the GAP LE event data of the specified event, and the GAP LE
 * event callback parameter that was specified when this callback was
 * installed.
 *
 * The caller should use the contents of the GAP LE event
 * data only in the context of this callback. If the caller requires the
 * data for a longer period of time, the callback function must copy
 * the data into another data buffer.
 *
 * This function is guaranteed not to
 * be invoked more than once simultaneously for the specified installed
 * callback (that is, this function does not have be reentrant). It should
 * be noted, however, that if the same callback is installed more than
 * once, then the callbacks will be called serially. Because of this,
 * the processing in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the thread
 * context of a thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because other GAP LE events will not be processed while this
 * function call is outstanding).
 *
 * This function must not block and wait for events that can only
 * be satisfied by receiving other GAP LE events. A deadlock will occur
 * because no GAP LE event callbacks will be issued while this function
 * is currently outstanding
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack via a call
 *                                   to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  GAP_LE_Event_Data     Pointer to the passed GAP LE Event
 *                                   data.
 *
 * @param[in]  CallbackParameter     User-defined parameter (e.g., tag
 *                                   value) that was defined in the
 *                                   callback registration.
 *
 * @return
 * None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_GAP_LE_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Event_Data_t *GAP_LE_Event_Data, unsigned long CallbackParameter);

/**
 * @brief
 * Queries (and reports) the device
 * address of the local Bluetooth device.
 *
 * @details
 * If this function is successful, this function returns zero, and
 * the buffer that BD_ADDR points to will be filled with the Board
 * Address read from the Local Device. If this function returns a
 * negative value, the BD_ADDR of the Local Device was not able
 * to be queried (error condition).
 *
 * @param[in]      BluetoothStackID   Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a call
 *                                    to BSC_Initialize.
 *
 * @param[in,out]  BD_ADDR            Pointer to memory in which to receive
 *                                    the local device address.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *                  @par
 *                    QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                    QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_Query_Local_BD_ADDR(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *BD_ADDR);

/**
 * @brief
 * Enables the local host to
 * create a connection to a remote device using the Bluetooth LE radio.
 *
 * @details
 * This function is provided to establish an LE master
 * connection to a remote device. To establish an LE slave
 * connection to a remote device the
 * qapi_BLE_GAP_LE_Advertising_Enable() function should be used to
 * put the local Bluetooth device in a connectable mode.
 *
 * This function allows the use of the Bluetooth white-list and can be used
 * to specify a specific set of devices to which to connect.
 *
 * This function is asynchronous in nature and the caller is
 * informed when the connection is established using the
 * qapi_BLE_GAP_LE_Event_Callback() function.
 *
 * If the InitatorFilterPolicy parameter is set to
 * #QAPI_BLE_FP_WHITE_LIST_E, the RemoteAddressType and
 * RemoteDevice parameter are not used and NULL values may
 * be passed in for them.
 *
 * If the local Bluetooth controller is a version 4.0 or 4.1
 * compliant controller, only the following types may be
 * used for the RemoteAddressType and the LocalAddressType
 * parameters:
 *
 *  QAPI_BLE_LAT_PUBLIC_E \n
 *  QAPI_BLE_LAT_RANDOM_E
 *
 * The #QAPI_BLE_LAT_PUBLIC_IDENTITY_E and
 * #QAPI_BLE_LAT_RANDOM_IDENTITY_E indicate that
 * the RemoteDevice parameter is an identity address (a
 * semipermanent address that can be used to refer to the
 * device) that was received from the remote device (along
 * with the remote device's IRK) during a successful
 * LE Pairing process. Note that these two types are only valid
 * for this API if the local controller is a version 4.2 or
 * greater Bluetooth controller.
 *
 * Note that if the final two enumerated types are specified
 * (QAPI_BLE_LAT_RESOLVABLE_FALLBACK_XXX), the
 * RemoteAddressType and RemoteAddress parameters must be
 * specified and valid, as they will be used to search the
 * Resolving List to find the local IRK to use when creating
 * the connection. Also note that these two types are only valid for
 * this API if the local controller is a version 4.2 or
 * greater Bluetooth controller.
 *
 * Types may be specified for the RemoteAddressType and the
 * LocalAddressType parameters.
 *
 * The following types may not be used with the
 * InitatorFilterPolicy parameter:
 *
 *   QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 *   QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E \n
 *
 * These values may only be used with the
 * qapi_BLE_GAP_LE_Perform_Scan() function.
 *
 * @param[in]  BluetoothStackID          Unique identifier assigned to this Bluetooth
 *                                       Protocol Stack via a call to BSC_Initialize.
 *
 * @param[in]  ScanInterval              Scan interval to use when scanning for the device(s)
 *                                       to connect.  This value is specified in milliseconds.
 *                                       This value must be within the range: \n
 *                                       #QAPI_BLE_MINIMUM_LE_SCAN_INTERVAL \n
 *                                       #QAPI_BLE_MAXIMUM_LE_SCAN_INTERVAL
 *
 * @param[in]  ScanWindow                Scan window to use when scanning for the device(s)
 *                                       to connect. This value is specified in milliseconds.
 *                                       This value must be within the range: \n
 *                                       #QAPI_BLE_MINIMUM_LE_SCAN_WINDOW \n
 *                                       QPAI_BLE_MAXIMUM_LE_SCAN_WINDOW
 *
 * @param[in]  InitatorFilterPolicy      Filter policy to apply when scanning. Valid values
 *                                       are: \n
 *                                       #QAPI_BLE_FP_NO_FILTER_E \n
 *                                       #QAPI_BLE_FP_WHITE_LIST_E \n
 *                                       If the white-list filter is specified, the
 *                                       remote device address (and address type) are ignored.
 *
 * @param[in]  RemoteAddressType         Specifies the type of the remote device address to connect
 *                                       with (if not using white-list filter). Valid values are: \n
 *                                       #QAPI_BLE_LAT_PUBLIC_E \n
 *                                       #QAPI_BLE_LAT_RANDOM_E \n
 *                                       #QAPI_BLE_LAT_PUBLIC_IDENTITY_E \n
 *                                       #QAPI_BLE_LAT_RANDOM_IDENTITY_E \n
 *                                       The last two types are only valid for Bluetooth 4.2.
 *                                       See above.
 *
 * @param[in]  RemoteDevice              Specifies the remote device address to connect with.
 *                                       This value is required if no filter is specified as
 *                                       the filter policy.
 *
 * @param[in]  LocalAddressType          Specifies the type of the address the local device is
 *                                       to use when connecting to the remote device. Valid
 *                                       values are: \n
 *                                       #QAPI_BLE_LAT_PUBLIC_E \n
 *                                       #QAPI_BLE_LAT_RANDOM_E \n
 *                                       #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E \n
 *                                       #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E \n
 *                                       The last two types are only valid for Bluetooth 4.2.
 *                                       See above.
 *
 * @param[in]  ConnectionParameters      Specifies the parameters to use when actually establishing
 *                                       the connection to the remote device.
 *
 * @param[in]  GAP_LE_Event_Callback     Pointer to a callback function to be used by the GAP
 *                                       layer to dispatch GAP LE Event information for this
 *                                       request.
 *
 * @param[in]  CallbackParameter         User-defined value to be used by the GAP layer as an
 *                                       input parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                QAPI_BLE_BTPS_ERROR_INVALID_CONNECTION_PARAMETERS \n
 *                QAPI_BLE_BTPS_ERROR_RANDOM_ADDRESS_IN_USE \n
 *                QAPI_BLE_BTPS_ERROR_CREATE_CONNECTION_OUTSTANDING \n
 *                QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Create_Connection(uint32_t BluetoothStackID, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Provides a means of canceling a
 * connection establishment procedure that was started via a call
 * to the qapi_BLE_GAP_LE_Create_Connection() function.
 *
 * @details
 * This function does not disconnect a connected device, it merely stops
 * the connection process (scanning and connecting). This function will
 * return zero if successful, or a negative return error code if there
 * was an error condition.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Create_Connection(uint32_t BluetoothStackID);

/**
 * @brief
 * Enables the local host
 * to disconnect a currently connected LE device.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR            Specifies the remote device address of the
 *                                currently connected device to disconnect.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Disconnect(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR);

/**
 * @brief
 * Provides a means of reading the
 * remote used features from a remote device over a previously
 * established LE connection.
 *
 * @details
 * This function can only be called if the local
 * Bluetooth device is acting in the master role for the
 * connection specified by the device address on 4.0
 * chipsets. On 4.1 and later chipsets, both the master and
 * slave may call this function.
 *
 * This function will not create an LE ACL connection to the
 * specified device. The LE ACL connection to the specified
 * remote device must already exist before calling this
 * function.
 *
 * This function is asynchronous and the user will be
 * notified via the Callback Function specified in the the
 * call to qapi_BLE_GAP_LE_Create_Connection() that was used
 * to establish this connection.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR            Specifies the remote device address of the
 *                                currently connected device to disconnect.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Remote_Features(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR);

/**
 * @brief
 *  Starts an LE scan procedure.
 *
 * @details
 * Only ONE scan can be performed at any given time.
 * Calling this function while an outstanding scan is in
 * progress will fail. The caller can call the
 * qapi_BLE_GAP_LE_Cancel_Scan() function to cancel a
 * currently executing scanning procedure.
 *
 * The ScanInterval and ScanWindow parameters (specified in
 * milliseconds) must satisify the following equation:
 *
 *              ScanWindow <= ScanInterval
 *
 * If ScanWindow == ScanInterval, LE Scanning will be performed
 * continuously.
 *
 * All scan period time parameters are specified in seconds
 *
 * If the local Bluetooth controller is a version 4.0 or 4.1
 * compliant controller then only the:
 *
 *   QAPI_BLE_LAT_PUBLIC_E \n
 *   QAPI_BLE_LAT_RANDOM_E
 *
 * Note that if the final two enumerated types are specified
 * (QAPI_BLE_LAT_RESOLVABLE_FALLBACK_XXX), the
 * controller will attempt to generate a Resolvable Private
 * Address to place in the scan request packets if the
 * advertiser is in the resolving list. If the device is
 * not in the resolving list, the controller will use
 * either the public address
 * (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E) or the random
 * address set via qapi_BLE_GAP_LE_Set_Random_Address()
 * (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E). Note that these
 * two types are only valid for this API if the local
 * controller is a version 4.2 or greater Bluetoot
 * controller.
 *
 * Note that for the #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E and
 * #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E types, they may only
 * be used if the local controller is a 4.2 or greater compliant
 * controller.
 *
 * If either of the #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 * or #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E types is
 * specified for the FilterPolicy, the application can expect
 * to receive the #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E
 * event when a directed advertisement that is directed
 * towards a resolvable private address is received by the
 * controller.
 *
 * If the #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E type is
 * used for the FilterPolicy parameter, the device can
 * expect to receive advertising reports based on the
 * following criteria:
 *
 *   - All undirected advertising packets
 *   - All directed advertising packets where the initiator
 *     address (the device for whom the packets are
 *     intended) is a resolvable private address
 *   - All directed advertising packets address to the
 *     local device
 *
 * When this type is used, the application can expect to
 * receive QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E events
 * when directed advertising packets where the iniator
 * address is a resolvable private address. The application
 * can then use the local IRK(s) to determine if the
 * directed advertisement is intended to be received by the
 * local device and then can make an application decision on
 * whether to connect to the device.
 *
 * If the #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E type is used
 * for the ilterPolicy parameter, the device can expect
 * to receive advertising reports based on the following criteria:
 *
 *   - All undirected advertising packets from devices
 *     where the advertiser's address is stored in the
 *     white list
 *   - All directed advertising packets where the initiator
 *     address (the device for whom the packets are
 *     intended) is a resolvable private address
 *   - All directed advertising packets addressed to the
 *     local device
 *
 * When this type is used, the application can expect to
 * receive QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E events
 * when directed advertising packets where the iniator
 * address is a resolvable private address. The application
 * can then use the local IRK(s) to determine if the
 * directed advertisement is intended to be received by the
 * local device and then can make an application decision on
 * whether to connect to the device.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this
 *                                     Bluetooth Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  ScanType                Specifies the type of scan to perform.
 *                                     This value must be one of the following: \n
 *                                     #QAPI_BLE_ST_PASSIVE_E \n
 *                                     #QAPI_BLE_ST_ACTIVE_E
 *
 * @param[in]  ScanInterval            Specifies interval to use while scanning. This
 *                                     value must be be between (and satisfy the equation
 *                                     listed above): \n
  *                                    #QAPI_BLE_MINIMUM_LE_SCAN_INTERVAL \n
 *                                     #QAPI_BLE_MAXIMUM_LE_SCAN_INTERVAL
 *
 * @param[in]  ScanWindow              Specifies window to use while scanning. This value
 *                                     must be be between (and satisfy the equation listed
 *                                     above): \n
 *                                     #QAPI_BLE_MINIMUM_LE_SCAN_WINDOW \n
 *                                     #QAPI_BLE_MAXIMUM_LE_SCAN_WINDOW
 *
 * @param[in]  LocalAddressType        Specifies the type of the address the local device is
 *                                     to use when connecting to the remote device. Valid
 *                                     values are: \n
 *                                     #QAPI_BLE_LAT_PUBLIC_E \n
 *                                     #QAPI_BLE_LAT_RANDOM_E \n
 *                                     #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E \n
 *                                     #QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E \n
 *                                     The last two types may only be used for Bluetooth 4.2.
 *                                     See above for more information.
 *
 * @param[in]  FilterPolicy            Filter policy to apply when scanning. Valid values are: \n
 *                                     #QAPI_BLE_FP_NO_FILTER_E   \n
 *                                     #QAPI_BLE_FP_WHITE_LIST_E \n
 *                                     #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E \n
 *                                     #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E \n
 *                                     The last two types may only be used for Bluetooth 4.2.
 *                                     See above for more information.
 *
 * @param[in]  FilterDuplicates        Specifies whether or not the host controller is to filter
 *                                     duplicate scan responses.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by the GAP layer
 *                                     to dispatch GAP LE Event information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP layer as an input
 *                                     parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_SCAN_ACTIVE \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Perform_Scan(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Scan_Type_t ScanType, uint32_t ScanInterval, uint32_t ScanWindow, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, boolean_t FilterDuplicates, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Cancels a scan process that was started via a successful call to the
 * qapi_BLE_GAP_LE_Perform_Scan() function.
 *
 * @details
 * If this function returns success, the GAP LE callback that was
 * installed with the qapi_BLE_GAP_LE_Perform_Scan() function will
 * not be called.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Scan(uint32_t BluetoothStackID);

/**
 * @brief
 * Sets the advertising data that is used during the advertising procedure
 * (started via the qapi_BLE_GAP_LE_Advertising_Enable() function).
 *
 * @details
 * Advertising data consists of zero or more tuples that consist of:
 *
 *   Length (bytes) \n
 *   Type (bytes) \n
 *   Data (zero or more bytes)
 *
 * Also note that the advertising data itself is a fixed length. If the
 * list of the tuples of the advertising data is not long enough to fill
 * the required advertising length, the bytes containing the binary value
 * zero (0x00) should be used to pad the data (until the end of the required
 * advertising data size).
 *
 * The Length and Advertising_Data parameters are optional.
 * If the intention is to set advertising data whose length is
 * zero, the Length and Advertising_Data parameters may
 * be set to 0 and NULL respectively.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Length             Number of significant advertising data bytes
 *                                contained in the advertising data.
 *
 * @param[in]  Advertising_Data   Pointer to a buffer that contains the advertising data.
 *                                This buffer must be at least:
 *                                   QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE
 *                                bytes long. Note that the length parameter specifies the
 *                                actual number of bytes that are valid. The remaining bytes
 *                                should be padded with zeroes.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Advertising_Data(uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Advertising_Data_t *Advertising_Data);

/**
 * @brief
 * Converts a #qapi_BLE_GAP_LE_Advertising_Data_t structure to the raw
 * qapi_BLE_Advertising_Data_t representation.
 *
 * @details
 * This second parameter must point to the maximum sized Advertising Data
 * Buffer size (QAPI_BLE_ADVERTISING_DATA_SIZE). This function will return
 * the number of successfully converted items (zero or more), or a
 * negative error code if there was an error.
 *
 * This function will populate the entire qapi_BLE_Advertising_Data_t buffer
 * (all QAPI_BLE_ADVERTISING_DATA_SIZE bytes). If the specified information
 * is smaller than the full Advertising Data size, the resulting buffer will
 * be padded with zeros.
 *
 * @param[in]   GAP_LE_Advertising_Data   Pointer to the parsed advertising data that is to
 *                                        be converted.
 *
 * @param[out]  Advertising_Data          Buffer that is to receive the actual advertising data
 *                                        from the parsed advertising data. This buffer must be
 *                                        at least  QAPI_BLE_ADVERTISING_DATA_SIZE bytes in length.
 *
 * @return
   Non-negative -- If successful. This value represents the number of
 *               valid advertising data fields that were successfully parsed.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Convert_Advertising_Data(qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Advertising_Data_t *Advertising_Data);

/**
 * @brief
 * Utility function that exists to parse
 * the specified qapi_BLE_Advertising_Data_t information into a
 * #qapi_BLE_GAP_LE_Advertising_Data_t structure (for ease
 * of parsing).
 *
 * @details
 * If this function is called with a NULL passed as the final parameter,
 * this function will simply calculate the number of Advertising Data
 * Information Entries that will be required to hold the parsed information.
 * If the final parameter is not NULL, it must contain the maximum number
 * of entries that can be supported (specified via the Number_Data_Entries
 * member) and the Data_Entries member must point to memory that contains
 * (at least) that many members.
 *
 * This function returns QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE if
 * there was not enough Data Entries specified (via the Number_Data_Entries
 * member) to satisfy the parsing of the actual Advertising Data.
 *
 * @param[in]  Advertising_Data          Buffer that contains the actual advertising data that is
 *                                       to be parsed. This buffer must be at least
 *                                       QPAI_BLE_ADVERTISING_DATA_SIZE bytes long. \n
 *                                       Note that if the advertising occupies less
 *                                       data bytes, the data should be padded with zero bytes
 *                                       (0x00).
 *
 * @param[in]  GAP_LE_Advertising_Data   Pointer to the parsed advertising data that has been parsed.
 *                                       Note that if this parameter is not NULL, the
 *                                       Number_Data_Entries member must contain the number of data
 *                                       entries that the Data_Entries member points to (to receive
 *                                       the parsed data information).
 *
 * @return
   Non-negative -- If successful. This value represents the number of
 *               valid advertising data fields that were successfully parsed.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Parse_Advertising_Data(qapi_BLE_Advertising_Data_t *Advertising_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data);

/**
 * @brief
 * Enables the local host to
 * set the scan response data that is used during the advertising procedure
 * (started via the qapi_BLE_GAP_LE_Advertising_Enable() function).
 *
 * @details
 * The Length and Scan_Response_Data parameters are optional. If the
 * intention is to scan response data whose length is zero, the
 * Length and Scan_Response_Data parameters may be set to 0 and NULL
 * respectively.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this Bluetooth
 *                                  Protocol Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Length               Number of significant advertising data bytes
 *                                  contained in the advertising data.
 *
 * @param[in]  Scan_Response_Data   Pointer to a buffer that contains the response
 *                                  data. This buffer must be at least
 *                                  QAPI_BLE_SCAN_RESPONSE_DATA_MAXIMUM_SIZE
 *                                  bytes long. \n
 *                                  Note that the length parameter
 *                                  specifies the actual number of bytes that
 *                                  are valid. The remaining bytes should be
 *                                  padded with zeros.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Scan_Response_Data(uint32_t BluetoothStackID, uint32_t Length, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data);

/**
 * @brief
 * Converts a #qapi_BLE_GAP_LE_Advertising_Data_t structure to the raw
 * qapi_BLE_Scan_Response_Data_t representation.
 *
 * @details
 * This second parameter must point to the maximum sized Scan
 * Response Buffer size (QAPI_BLE_SCAN_RESPONSE_DATA_SIZE).
 *
 * This function returns QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE if
 * there was not enough Data Entries specified (via the Number_Data_Entries
 * member) to satisfy the parsing of the actual Advertising Data.
 *
 * This function will populate the entire qapi_BLE_Scan_Response_Data_t
 * buffer (all QAPI_BLE_SCAN_RESPONSE_DATA_SIZE bytes). If the specified
 * information is smaller than the full Scan Response size, the resulting
 * buffer will be padded with zeros.
 *
 * @param[in]   GAP_LE_Advertising_Data   Pointer to the parsed advertising data
 *                                        that is to be converted.
 *
 * @param[out]  Scan_Response_Data        Buffer that is to receive the actual scan
 *                                        response data from the parsed advertising data.
 *                                        This buffer must be at least
 *                                        QAPI_BLE_SCAN_RESPONSE_DATA_SIZE
 *                                        bytes in length.
 *
 * @return
 * Non-negative -- If successful. This value represents the number
 *               of valid advertising data fields that were successfully parsed.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Convert_Scan_Response_Data(qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data, qapi_BLE_Scan_Response_Data_t *Scan_Response_Data);

/**
 * @brief
 * Utility function to parse the
 * specified qapi_BLE_Scan_Response_Data_t information into a
 * #qapi_BLE_GAP_LE_Advertising_Data_t structure (for ease of parsing).
 *
 * @details
 * If this function is called with a NULL passed as the final parameter,
 * this function will simply calculate the number of Advertising
 * Data Information Entries that will be required to hold the parsed
 * information. If the final parameter is not NULL, it must contain
 * the maximum number of entries that can be supported (specified via
 * the Number_Data_Entries member) and the Data_Entries member must
 * point to memory that contains (at least) that many members.
 *
 * This function returns QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE if
 * there was not enough Data Entries specified (via the Number_Data_Entries
 * member) to satisfy the parsing of the actual Scan Response Data.
 *
 * @param[in]   Scan_Response_Data        Buffer that contains the actual scan
 *                                        response data that is to be parsed.
 *                                        This buffer must be at least
 *                                        QAPI_BLE_SCAN_RESPONSE_DATA_SIZE
 *                                        bytes long.\n
 *                                        Note that if the scan
 *                                        response occupies less data bytes,
 *                                        the data should be padded with
 *                                        zero bytes (0x00).
 *
 * @param[out]  GAP_LE_Advertising_Data   Pointer to the parsed scan response
 *                                        data that has been parsed. Note that
 *                                        if this parameter is not NULL, the
 *                                        Number_Data_Entries member must contain
 *                                        the number of data entries that the
 *                                        Data_Entries member points to (to
 *                                        receive the parsed data information.
 *
 * @return
 * Non-negative -- If successful. This value represents the number of
 *               valid advertising data fields that were successfully parsed.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Parse_Scan_Response_Data(qapi_BLE_Scan_Response_Data_t *Scan_Response_Data, qapi_BLE_GAP_LE_Advertising_Data_t *GAP_LE_Advertising_Data);

/**
 * @brief
 * The following function is provided to allow the local host the ability
 * to begin an advertising procedure.  An advertising procedure is required
 * to allow a remote Bluetooth LE device to connect with the local device.
 *
 * @details
 * Enables advertising
 * using the data written using qapi_BLE_GAP_LE_Set_Advertising_Data().
 *
 * The #QAPI_BLE_LCM_LOW_DUTY_CYCLE_DIRECT_CONNECTABLE_E connectable mode
 * is only valid to be passed to this device if the local Bluetooth device
 * is a 4.1 or greater chipset.
 *
 * @param[in]  BluetoothStackID                   Unique identifier assigned to this Bluetooth
 *                                                Protocol Stack via a call to
 *                                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EnableScanResponse                 Flag that specifies whether or not the device
 *                                                should send scan response data in response to
 *                                                a scan request.
 *
 * @param[in]  GAP_LE_Advertising_Parameters      Pointer to advertising parameters that control
 *                                                how the advertising is performed.
 *
 * @param[in]  GAP_LE_Connectability_Parameters   Specifies the connectability parameters to use
 *                                                while advertising.
 *
 * @param[in]  GAP_LE_Event_Callback              Pointer to a callback function to be used by the
 *                                                GAP layer to dispatch GAP LE event information
 *                                                for this request.
 *
 * @param[in]  CallbackParameter                  User-defined value to be used by the GAP layer
 *                                                as an input parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Advertising_Enable(uint32_t BluetoothStackID, boolean_t EnableScanResponse, qapi_BLE_GAP_LE_Advertising_Parameters_t *GAP_LE_Advertising_Parameters, qapi_BLE_GAP_LE_Connectability_Parameters_t *GAP_LE_Connectability_Parameters, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Disables LE advertising that was enabled via a previously successful call
 * to the qapi_BLE_GAP_LE_Advertising_Enable() function.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR \n
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Advertising_Disable(uint32_t BluetoothStackID);

/**
 * @brief
 * Configures if the Wake On BLE functionality should be to
 * wake on a received scan request (if advertising was enabled
 * prioring to entering suspend mode).
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 *
 * @param[in]  WakeOnScanRequestEnabled   TRUE if Wake on BLE
 *                                should trigger for received scan request.
 *                                FALSE if not.
 *
 * @return
 * Zero -- If the flag was set.\n
 * FALSE -- If the flag was not set.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Wake_On_Scan_Request(uint32_t BluetoothStackID, boolean_t WakeOnScanRequestEnabled);

/**
 * @brief
 * Generates a nonresolvable random device address.
 *
 * @details
 * This device address can be used as a random address by calling
 * qapi_BLE_GAP_LE_Set_Random_Address().
 *
 * @param[in]  BluetoothStackID               Unique identifier assigned to this Bluetooth
 *                                            Protocol Stack via a call to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[out]  NonResolvableAddress_Result   Buffer that will receive the generated nonresolvable
 *                                            address upon successful execution
 *                                            of this function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Non_Resolvable_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *NonResolvableAddress_Result);

/**
 * @brief
 * Generates a static random device address.
 *
 * @details
 * This device address can then be used as a random address by call
 * qapi_BLE_GAP_LE_Set_Random_Address().
 *
 * The Bluetooth Specification has defined that the Static Address should
 * only change once per power cycle, therefore, it is the requirement of
 * the application that this function is only used to generate a new Static
 * Address once per power cycle.
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[out]  StaticAddress_Result   Buffer that will receive the generated static
 *                                     address upon successful execution of this
 *                                     function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Static_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t *StaticAddress_Result);

/**
 * @brief
 * Generates a resolvable random device address.
 *
 * @details
 * This device address can then be used as a random address by call to
 * the qapi_BLE_GAP_LE_Set_Random_Address() function.
 *
 * @param[in]   BluetoothStackID           Unique identifier assigned to this Bluetooth
 *                                         Protocol Stack via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 * @param[in]   IRK                        Identity resolving key (IRK) that is used to
 *                                         generate the resolvable address.
 *
 * @param[out]  ResolvableAddress_Result   Buffer that will receive a generated resolvable
 *                                         address upon successful execution of this
 *                                         function.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Resolvable_Address(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t *ResolvableAddress_Result);

/**
 * @brief
 * Resolves a resolvable random device address.
 *
 * @details
 * The following function allows the user to resolve the resolvable address at
 * the software level. If the local controller is a version 4.2 or
 * greater Bluetooth controller, this may be done automatically at
 * the hardware level using the resolving list. This increases
 * efficiency.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  IRK                 Identity resolving key (IRK) that is used to
 *                                 resolve the resolvable address.
 *
 * @param[in]  ResolvableAddress   Bluetooth address that represents the resolvable
 *                                 address that is attempting to be resolved (using
 *                                 the specified IRK).
 *
 * @return
 * TRUE -- If the resolvable address was successfully resolved.\n
 * FALSE -- If the resolvable address was not able to be resolved.
 */
QAPI_BLE_DECLARATION boolean_t QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Resolve_Address(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *IRK, qapi_BLE_BD_ADDR_t ResolvableAddress);

/**
 * @brief
 * Writes a random address to the Bluetooth device.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]  RandomAddress      Actual random address value to set in the local device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_RANDOM_ADDRESS_IN_USE \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Random_Address(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t RandomAddress);

/**
 * @brief
 * Manages the
 * white list that is stored in the Bluetooth device, which is specified
 * by the first parameter.
 *
 * @details
 * This function will attempt to add as many devices as possible (from
 * the specified list) and will return the number of devices added.
 * The qapi_BLE_GAP_LE_Read_White_List_Size() function can be used to
 * determine how many devices the local device supports in the white
 * list (simultaneously).
 *
 * The white list cannot be changed while a scan or connection is in
 * progress. If this function is called while a scan or connection
 * is active, the following error code will be returned:
 *
 *    BTPS_ERROR_WHITE_LIST_IN_USE
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DeviceCount        Total number of device list entries that are
 *                                 pointed to by the WhiteListEntries buffer.
 *
 * @param[in]   WhiteListEntries   Buffer that contains one or more individual
 *                                 white list device entries to write to the
 *                                 local device. This buffer must point to (at
 *                                 least) DeviceCount entries.
 *
 * @param[out]  AddedDeviceCount   Upon successful execution, this function
 *                                 contains the total number of white list
 *                                 entries that were successfully written to
 *                                 the device white list.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_RANDOM_ADDRESS_IN_USE \n
 *                 QAPI_BLE_BTPS_ERROR_WHITE_LIST_IN_USE \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_White_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *AddedDeviceCount);

/**
 * @brief
 * Removes one (or more) devices from the white list maintained by the
 * local device.
 *
 * @details
 * This function will attempt to delete as many devices as possible (from
 * the specified list) and will return the number of devices deleted.
 * The qapi_BLE_GAP_LE_Read_White_List_Size() function can be used to
 * determine how many devices the local device supports in the white
 * list (simultaneously).
 *
 * @param[in]    BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                   Protocol Stack via a call to
 *                                   qapi_BLE_BSC_Initialize().
 *
 * @param[in]    DeviceCount         Total number of device list entries that are
 *                                   pointed to by the WhiteListEntries buffer. If
 *                                   this value is specified as zero, the next
 *                                   parameter is ignored and all devices are
 *                                   removed from the white list.
 *
 * @param[in]   WhiteListEntries     Buffer that contains one or more individual
 *                                   white list device entries to remove from the
 *                                   local device. This buffer must point to (at
 *                                   least) DeviceCount entries.
 *
 * @param[out]  RemovedDeviceCount   Upon successful execution, this function
 *                                   contains the total number of white list entries
 *                                   that were successfully removed from the device
 *                                   white list.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_WHITE_LIST_IN_USE \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_White_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_White_List_Entry_t *WhiteListEntries, uint32_t *RemovedDeviceCount);

/**
 * @brief
 * Determines the total number of devices that can be be present in the
 * white list (simultaneously) on the local device.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  WhiteListSize       Total number of device list entries are
 *                                 supported by the local device. This
 *                                 value is the number of entries, not the
 *                                 number of white list entry buffer size
 *                                 in bytes.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_White_List_Size(uint32_t BluetoothStackID, uint32_t *WhiteListSize);

/**
 * @brief
 * Changes the pairability mode of the Bluetooth device.
 *
 * @details
 * If the pairability mode is QAPI_BLE_LPM_NON_PAIRABLEMODE_E, the
 * final two parameters are not used and may be ignored.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  PairableMode        Pairability mode to set. Possible values: \n
                                   #QAPI_BLE_LPM_NON_PAIRABLEMODE_E \n
 *                                 #QAPI_BLE_LPM_PAIRABLE_MODE_E
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Pairability_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Pairability_Mode_t PairableMode);

/**
 * @brief
 * Registers a
 * GAP LE event Callback to accept remote authentication requests.
 *
 * @details
 * A remote authentication event is defined as an authentication event
 * that was not requested by the local device (that is, a pairing or
 * authentication request issued from a remote device to the local device).
 *
 * It should be noted that only one remote authentication callback can
 * be installed per Bluetooth device. The caller can unregister the
 * remote authentication callback that was registered with this function
 * (if successful) by calling the
 * qapi_BLE_GAP_LE_Un_Register_Remote_Authentication() function.
 *
 * This function can be called by the master or the slave.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Register_Remote_Authentication(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Unregisters
 * a previously registered GAP LE event callback for remote authentication
 * events.
 *
 * @details
 * This function can be called by the master or the slave.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Un_Register_Remote_Authentication(uint32_t BluetoothStackID);

/**
 * @brief
 * Pairs to a remote device.
 *
 * @details
 * This function can only be issued by the master of the connection (the
 * initiator of the connection). The reason is that a slave can only
 * request a security procedure, it cannot initiate a security procedure.
 *
 * This function will not create an LE ACL connection to the specified device.
 * The LE ACL connection to the specified remote device must already exist
 * before calling this function.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth device address of the connected
 *                                     device to pair with.
 *
 * @param[in]  Capabilities            Pointer to a buffer that holds the pairing
 *                                     capabilities of the local host.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Pair_Remote_Device(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Pairing_Capabilities_t *Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Pairs to a remote device with extended pairing capabilities.
 *
 * @details
 * This function can only be issued by a master because the
 * slave device is not allowed to perform security processes, the
 * slave can only request them).
 *
 * This function will not create an LE ACL connection to the specified
 * device. The LE ACL connection to the specified remote device must
 * already exist before calling this function.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth device address of the connected
 *                                     device to pair with.
 *
 * @param[in]  Extended_Capabilities   Pointer to a buffer that holds the extended
 *                                     pairing capabilities of the local host.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Pair_Remote_Device(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *Extended_Capabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows a mechanism for the local
 * device to respond to GAP LE authentication events.
 *
 * @details
 * This function should be called to respond to authentication requests that
 * were received via any of the installed callbacks:
 *
 *  - Pairing callback
 *  - Remote authentication callback
 *
 * This function can be issued by the master or the slave in response to
 * an authentication/pairing event.
 *
 * @param[in]  BluetoothStackID                    Unique identifier assigned to this Bluetooth
 *                                                 Protocol Stack via a call to
 *                                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                             Device address of the Bluetooth device that
 *                                                 is being authenticated.
 *
 * @param[in]  GAP_LE_Authentication_Information   Pointer to a structure that holds
 *                                                 authentication information.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_PAIRING_NOT_ACTIVE \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Authentication_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Authentication_Response_Information_t *GAP_LE_Authentication_Information);

/**
 * @brief
 * Requests a
 * security reestablishment using information transferred from a previous
 * pairing process (during a previous connection) to the device specified
 * by the BD_ADDR parameter.
 *
 * @details
 * This function performs differently depending upon if the local device
 * is a master or a slave to the device specified. If the local device
 * is a master, this function will process the specified security
 * parameters and attempt to reauthenticate the device. If the local
 * device is a slave, this function will request the master to
 * reestablish the security. The reason for the differing behavior is
 * that the slave can only request security be initiated, it cannot
 * initate the security process itself.
 *
 * This function can be called by either a master or slave (of the
 * connected device). The parameters that are used are taken from
 * the SecurityInformation parameter (which contains parameters
 * for both master and slave).
 *
 * This function will not create an LE ACL connection to the specified
 * device. The LE ACL connection to the specified remote device must
 * already exist before calling this function.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth device address of the connected
 *                                     device to re-establish security with.
 *
 * @param[in]  SecurityInformation     Pointer to a buffer that holds the security
 *                                     information required to re-establish the security.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Reestablish_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Security_Information_t *SecurityInformation, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Requests
 * that the remote device begin a security process (either pairing or
 * reestablishing a previously established security).
 *
 * @details
 * This function can only be called by a slave device. The reason for
 * this is that the slave can only request security be initiated, it
 * cannot initate the security process itself.
 *
 * This function will not create an LE ACL connection to the specified
 * device. The LE ACL connection to the specified remote device must
 * already exist before calling this function.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth device address of the connected
 *                                     device to request security from.
 *
 * @param[in]  Bonding_Type            Required bonding type for the security
 *                                     being requested.  This value is one of the
 *                                     following: \n
 *                                     #QAPI_BLE_LBT_NO_BONDING_E \n
 *                                     #QAPI_BLE_LBT_BONDING_E
 *
 * @param[in]  MITM                    Flag that specifies whether man in the middle
 *                                    (MITM) protection is required.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Request_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Bonding_Type_t Bonding_Type, boolean_t MITM, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Requests that
 * the remote device begin a security process with extended parameters
 * (either pairing or reestablishing a previously established security).
 *
 * @details
 * This function can only be called by a slave device. The reason for
 * this is that the slave can only request security be initiated, it
 * cannot initate the security process itself.
 *
 * This function will not create an LE ACL connection to the specified
 * device. The LE ACL connection to the specified remote device must
 * already exist before calling this function.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth device address of the connected
 *                                     device to request security from.
 *
 * @param[in]  ExtendedCapabilities    Pointer to a buffer that holds the extended
 *                                     pairing capabilities of the slave.
 *
 * @param[in]  GAP_LE_Event_Callback   Pointer to a callback function to be used by
 *                                     the GAP layer to dispatch GAP LE event
 *                                     information for this request.
 *
 * @param[in]  CallbackParameter       User-defined value to be used by the GAP
 *                                     layer as an input parameter for the specified
 *                                     callback.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Request_Security(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Extended_Pairing_Capabilities_t *ExtendedCapabilities, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Configured a fixed Display
 * Passkey to be used during the pairing process.
 *
 * @details
 * A Fixed Display Passkey will only be used if the local device is chosen
 * to display the passkey based on the local I/O Capabilities and the
 * remote I/O Capabilities.
 *
 * If successful, this function will set the Passkey that will be used in
 * all future pairing processes where the local device is chosen to display
 * the passkey used during the pairing process.
 *
 * @param[in]  BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  Fixed_Display_Passkey   Optional pointer to the fixed display passkey to use.
 *                                     If this parameter is NULL, a fixed display passkey
 *                                     that was previously set using this function is no longer
 *                                     used. If this parameter is non-NULL, the passkey
 *                                     that it points to is used for all future pairing
 *                                     operations where the local Bluetooth device displays
 *                                     the passkey.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Fixed_Passkey(uint32_t BluetoothStackID, uint32_t *Fixed_Display_Passkey);

/**
 * @brief
 * Utility function provided to allow
 * the application to force this module to update the local P-256
 * Public/Private Key Pair that is used for LE Secure Connections pairing
 *(Version 4.2).
 *
 * @details
 * This function may not be called when pairing is in progress.
 *
 * @param[in]  BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                Protocol Stack via a call to
 *                                qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Update_Local_P256_Public_Key(uint32_t BluetoothStackID);

/**
 * @brief
 * Sets the LE SC debug mode.
 *
 * @details
 * The LE SC debug mode indicates if the P256 private/public key pair
 * is generated by the controller or host, or whether the debug P256 private/public
 * key pair is used. The debug private/public key pair may be stored by the controller
 * or the host.
 *
 * This function may not be called while pairing is in progress or if
 * qapi_BLE_GAP_LE_Update_Local_P256_Public_Key() function is called since
 * key generation may be in progress.
 *
 * @param[in]  BluetoothStackID  Unique identifier assigned to this Bluetooth
 *                               Protocol Stack via a call to
 *                               qapi_BLE_BSC_Initialize().
 *
 * @param[in]  DebugMode         Holds the LE SC debug mode.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Write_Secure_Connections_Debug_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t DebugMode);

/**
 * @brief
 * Queries the LE SC debug mode.
 *
 * @details
 * The LE SC debug mode indicates if the P256 private/public key pair
 * is generated by the controller or host, or whether the debug P256 private/public
 * key pair is used. The debug private/public key pair may be stored by the controller
 * or the host.
 *
 * This function may be called while pairing is in progress.
 *
 * @param[in]  BluetoothStackID  Unique identifier assigned to this Bluetooth
 *                               Protocol Stack via a call to
 *                               qapi_BLE_BSC_Initialize().
 *
 * @param[out]  DebugMode        Pointer to a value that will hold the
 *                               LE SC debug mode if this function
 *                               is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Secure_Connections_Debug_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Secure_Connections_Debug_Mode_t *DebugMode);

/**
 * @brief
 * Queries the current Encryption Mode.
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                    Protocol Stack via a call to
 *                                    qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                Bluetooth device address of the connected
 *                                    device to query the link encryption mode.
 *
 * @param[out]  GAP_Encryption_Mode   Pointer to store the link encryption mode.
 *                                    This parameter is not optional, and cannot
 *                                    be NULL. If this function returns success,
 *                                    this will point to one of the following
 *                                    values: \n
 *                                    #QAPI_BLE_EM_DISABLED_E \n
 *                                    #QAPI_BLE_EM_ENABLED_E
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Encryption_Mode(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_Encryption_Mode_t *GAP_Encryption_Mode);

/**
 * @brief
 * Queries the LE
 * Connection Handle of a connection to a remote Bluetooth Low Energy
 * Device.
 *
 * @details
 * If a connection exists to the remote device specified, the LE
 * connection handle is returned in the buffer passed to this function.
 *
 * This function is only for LE connections. This function will not
 * return connection handles for Bluetooth BR/EDR connections.
 *
 * If this function returns with an error, a negative value, the value
 * returned in the Connection_Handle variable should be considered
 * invalid.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this Bluetooth
 *                                    Protocol Stack via a call to
 *                                    qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR               Address of the Bluetooth Low Energy device of
 *                                    which to query the connection handle.
 *
 * @param[out]  Connection_Handle     Pointer to a variable that will receive the
 *                                    connection handle associated with the
 *                                    specified Bluetooth device address.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Handle(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *Connection_Handle);

/**
 * @brief
 * Queries the local/remote Bluetooth board addresses which were used to
 * establish the specified LE connection.
 *
 * @details
 * If this function returns with an error, negative value,
 * the value returned in the Addresses variable should be
 * considered invalid.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Connection_Handle  Identifies the connection.
 *
 * @param[out]  Addresses          Pointer to a structure that will hold
 *                                 the LE address pair for the specified
 *                                 connection.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Addresses(uint32_t BluetoothStackID, uint16_t Connection_Handle, qapi_BLE_GAP_LE_Address_Pair_t *Addresses);

/**
 * @brief
 * Queries the LE
 * Connection Parameters of a connection to a remote Bluetooth Low Energy
 * Device.
 *
 * @details
 * If a connection exists to the remote device specified, the current
 * LE connection parameters are returned in the structure passed to
 * this function.
 *
 * This function is only for LE connections. This function will not
 * return connection handles for Bluetooth BR/EDR connections.
 *
 * If this function returns with an error, a negative value, the value
 * returned in the Current_Connection_Parameters structure should be
 * considered invalid.
 *
 * @param[in]   BluetoothStackID                Unique identifier assigned to this Bluetooth
 *                                              Protocol Stack via a call to
 *                                              qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                         Address of the Bluetooth Low Energy device of
 *                                              which to query the connection parameters.
 *
 * @param[out]  Current_Connection_Parameters   Pointer to a structure that will receive
 *                                              the connection parameters for the connection
 *                                              to the specified device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Current_Connection_Parameters_t *Current_Connection_Parameters);

/**
 * @brief
 * Creates a new Long Term Key (LTK).
 *
 * @details
 * This function accepts the diversifying hiding key (DHK) and the encryption
 * root key (ERK). Using these inputs, this function generates the LTK,
 * the diversifier (DIV), and the encrypted diversifier (EDIV)
 * values.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DHK                Diversifying hiding key used as input to
 *                                 generate the LTK.
 *
 * @param[in]   ER                 ERK used with the
 *                                 DHK to generate the LTK.
 *
 * @param[out]  LTK_Result         Pointer to a buffer that will receive
 *                                 the generated LTK.
 *
 * @param[out]  DIV_Result         Pointer to a buffer that will receive
 *                                 the diversifier that was used to
 *                                 generate the LTK.
 *
 * @param[out]  EDIV_Result        Pointer to a buffer that will receive
 *                                 the EDIV that
 *                                 was used to generate the LTK.
 *
 * @param[out]  Rand_Result        Pointer to a buffer that will receive
 *                                 the random number that was used to
 *                                 generate the LTK.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Generate_Long_Term_Key(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, qapi_BLE_Long_Term_Key_t *LTK_Result, uint16_t *DIV_Result, uint16_t *EDIV_Result, qapi_BLE_Random_Number_t *Rand_Result);

/**
 * @brief
 * Provides a means of dynamically
 * regenerating an LTK that was previously generated
 * with a call to the qapi_BLE_GAP_LE_Generate_Long_Term_Key() function.
 *
 * @details
 * This function accepts the DHK, the
 * ERK, the EDIV,
 * and a random number. Using these inputs, this function
 * regenerates an LTK.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DHK                Diversifying hiding key used as input to
 *                                 generate the LTK.
 *
 * @param[in]   ER                 ERK used with the
 *                                 DHK to generate the LTK.
 *
 * @param[in]   EDIV               EDIV that will
 *                                 be used to regenerate the LTK.
 *
 * @param[in]   Rand               Random number that will be used to
 *                                 during the regeneration process.
 *
 * @param[out]  LTK_Result         Pointer to a buffer that will receive
 *                                 the regenerated LTK.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Regenerate_Long_Term_Key(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *DHK, qapi_BLE_Encryption_Key_t *ER, uint16_t EDIV, qapi_BLE_Random_Number_t *Rand, qapi_BLE_Long_Term_Key_t *LTK_Result);

/**
 * @brief
 * Performs the Diversify Function, d1, as specified in Volume 3, Part H, Section
 * 5.2.2.1 of the Core specification.
 *
 * @param[in]   BluetoothStackID   Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Key                Encryption key used as input to the diversify
 *                                 function.
 *
 * @param[in]   DIn                D value used as input to the diversify function.
 *
 * @param[in]   RIn                R value used as input to the diversify function.
 *
 * @param[out]  Result             Pointer to a buffer that will receive the
 *                                 generated encryption key.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Diversify_Function(uint32_t BluetoothStackID, qapi_BLE_Encryption_Key_t *Key, uint16_t DIn, uint16_t RIn, qapi_BLE_Encryption_Key_t *Result);

/**
 * @brief
 * Requests a connection parameter update for an LE connection.
 *
 * @details
 * This function is asynchronous in nature; the caller will receive an
 * #QAPI_BLE_ET_LE_CONNECTION_PARAMETER_UPDATE_RESPONSE_E event through
 * the GAP LE event callback installed for this connection when the
 * process has completed.
 *
 * Connection_Interval_Min, Connection_Interval_Max and
 * Connection_Supervision_Timeout must be specified in milliseconds.
 *
 * Connection_Interval_Min must satisfy the following equation:
 *
 *      Connection_Interval_Min >=
 *         #QAPI_BLE_MINIMUM_MINIMUM_CONNECTION_INTERVAL
 *
 *            AND
 *
 *      Connection_Interval_Min <=
 *         #QAPI_BLE_MAXIMUM_MINIMUM_CONNECTION_INTERVAL
 *
 * Connection_Interval_Min must satisfy the following equation:
 *
 *      Connection_Interval_Min >=
 *         #QAPI_BLE_MINIMUM_MAXIMUM_CONNECTION_INTERVAL
 *
 *            AND
 *
 *      Connection_Interval_Min <=
 *         #QAPI_BLE_MAXIMUM_MAXIMUM_CONNECTION_INTERVAL
 *
 * Slave_Latency must satisfy the following equation:
 *
 *      Slave_Latency >=
 *         #QAPI_BLE_MINIMUM_SLAVE_LATENCY
 *
 *            AND
 *
 *      Slave_Latency <=
 *         #QAPI_BLE_MAXIMUM_SLAVE_LATENCY
 *
 * Connection_Supervision_Timeout must satisfy the following
 * equation:
 *
 *      Connection_Supervision_Timeout >=
 *         #QAPI_BLE_MINIMUM_LINK_SUPERVISION_TIMEOUT
 *
 *            AND
 *
 *      Connection_Supervision_Timeout <=
 *         #QAPI_BLE_MAXIMUM_LINK_SUPERVISION_TIMEOUT
 *
 * @param[in]   BluetoothStackID         Unique identifier assigned to this Bluetooth
 *                                       Protocol Stack via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                   Device address of the connected device that
 *                                       the local device is requesting the connection
 *                                       parameter update of.
 *
 * @param[in]  Connection_Interval_Min   Minimum requested connection interval.
 *                                       This value is specified in milliseconds.
 *
 * @param[in]  Connection_Interval_Max   Maximum requested connection interval.
 *                                       This value is specified in milliseconds.
 *
 * @param[in]  Slave_Latency             Requested slave latency. This value is
 *                                       specified in number of milliseconds
 *                                       events. The default slave latency is
 *                                       defined by the constant:
 *                                       DEFAULT_SLAVE_LATENCY
 *
 * @param[in]  Supervision_Timeout       Requested supervision timeout.
 *                                       This value is specified in
 *                                       milliseconds
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE \n
 *                 QAPI_BLE_BTPS_ERROR_CONNECTION_UPDATE_PROCEDURE_OUTSTANDING
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_Parameter_Update_Request(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t Connection_Interval_Min, uint16_t Connection_Interval_Max, uint16_t Slave_Latency, uint16_t Supervision_Timeout);

/**
 * @brief
 * Provides a means of either accepting
 * or rejecting a connection parameter update request that was received
 * from a remote device.
 *
 * @details
 * If the connection parameters are accepted:
 *
 *   The remote device is notified of the connection parameters that were accepted. \n
 *   The new connection parameters are applied to the connection.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this Bluetooth
 *                                    Protocol Stack via a call to
 *                                    qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                Device address of the connected device that
 *                                    the local device is responding to the
 *                                    connection parameter update of.
 *
 * @param[in]  Accept                 Flag that specifies whether the slave requested
 *                                    parameters were accepted. If this value is FALSE,
 *                                    the next parameter is ignored. If TRUE,
 *                                    the next parameter specifies the new connection
 *                                    parameters.
 *
 * @param[in]  ConnectionParameters   Specifies the new, accepted, connection parameters
 *                                    of the connection to the remote device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_Parameter_Update_Response(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Accept, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters);

/**
 * @brief
 * Allows a mechanism to attempt
 * to update the connection parameters for an LE connection.
 *
 * @details
 * Connection_Interval_Min, Connection_Interval_Max and
 * Connection_Supervision_Timeout must be specified in milliseconds.
 *
 * Connection_Interval_Min must satisfy the following equation:
 *
 *      Connection_Interval_Min >=
 *         #QAPI_BLE_MINIMUM_MINIMUM_CONNECTION_INTERVAL
 *
 *            AND
 *
 *      Connection_Interval_Min <=
 *         #QAPI_BLE_MAXIMUM_MINIMUM_CONNECTION_INTERVAL
 *
 * Connection_Interval_Min must satisfy the following equation:
 *
 *      Connection_Interval_Min >=
 *         #QAPI_BLE_MINIMUM_MAXIMUM_CONNECTION_INTERVAL
 *
 *            AND
 *
 *      Connection_Interval_Min <=
 *         #QAPI_BLE_MAXIMUM_MAXIMUM_CONNECTION_INTERVAL
 *
 * Slave_Latency must satisfy the following equation:
 *
 *      Slave_Latency >=
 *         #QAPI_BLE_MINIMUM_SLAVE_LATENCY
 *
 *            AND
 *
 *      Slave_Latency <=
 *         #QAPI_BLE_MAXIMUM_SLAVE_LATENCY
 *
 * Connection_Supervision_Timeout must satisfy the following
 * equation:
 *
 *      Connection_Supervision_Timeout >=
 *         #QAPI_BLE_MINIMUM_LINK_SUPERVISION_TIMEOUT
 *
 *            AND
 *
 *      Connection_Supervision_Timeout <=
 *         #QAPI_BLE_MAXIMUM_LINK_SUPERVISION_TIMEOUT
 *
 * This function can only be issued by the master of the connection on
 * 4.0 chipsets. On 4.1 and greater Bluetooth devices both the Master
 * and Slave may call this function.
 *
 * @param[in]  BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                    Protocol Stack via a call to
 *                                    qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                Device address of the connected device that
 *                                    the local device is responding to the
 *                                    connection parameter update of.
 *
 * @param[in]  ConnectionParameters   Specifies the new connection parameters to
 *                                    attempt to apply to the connection to the
 *                                    remote device.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_LOCAL_CONTROLLER_DOES_NOT_SUPPORT_LE \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_DEVICE_ROLE_MODE
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Update_Connection_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_Connection_Parameters_t *ConnectionParameters);

/**
 * @brief
 * Sets the
 * Authenticated Payload Timeout of an LE connection to a remote Bluetooth
 * Device.
 *
 * @details
 * The AuthenticatedPayloadTimeout parameter represents the authenticated
 * payload timeout value that is to be set (in milliseconds). This parameter
 * is defined as the maximum amount of time that is allowed between packets
 * received with a valid MIC from a remote LE device if the link is encrypted
 *
 * If this function returns QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED, a
 * connection to the specified Bluetooth Board Address does not exist.
 *
 * This function can only be called if the local Bluetooth device is a
 * 4.1 or greater chipset.
 *
 * The AuthenticatedPayloadTimeout parameter is specified in
 * milliseconds.
 *
 * The AuthenticatedPayloadTimeout parameter must adhere to the following
 * rule:
 *
 *       AuthenticatedPayloadTimeout >=
 *                 ConnectionInterval * (1 + SlaveLatency)
 *
 * If the Authenticated Payload Timeout is the time between valid packets
 * received with MICs on an encrypted link. The
 * #QAPI_BLE_ET_LE_AUTHENTICATED_PAYLOAD_TIMEOUT_EXPIRED_E event will be
 * dispatched to the GAP LE event callback nstalled for this connection
 * if the timeout expires with no valid MIC received from the remote
 * device.
 *
 * This function will only set the Authenticated Payload Timeout for an
 * LE connections. For BR/EDR connections, the
 * qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout() function must
 * be called.
 *
 * @param[in]  BluetoothStackID              Unique identifier assigned to this Bluetooth
 *                                           Protocol Stack via a call to
 *                                           qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                       Bluetooth address of the remote LE device to
 *                                           set the authenticated payload for.
 *
 * @param[in]  AuthenticatedPayloadTimeout   Value to set for the authenticated payload
 *                                           timeout for the specified connection.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_NOT_CONNECTED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t AuthenticatedPayloadTimeout);

/**
 * @brief
 * Queries the
 * Authenticated Payload Timeout of an LE connection to a remote Bluetooth
 * Device.
 *
 * @details
 * This parameter is defined as the maximum amount of time that is allowed
 * between packets received with a valid MIC from a remote LE device if the
 * link is encrypted.
 *
 * If this function returns with an error, a negative value, the value
 * returned in the AuthenticatedPayloadTimeout variable should be
 * considered invalid.
 *
 * If this function returns QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED, a
 * connection to the specified Bluetooth Board Address does not exist.
 *
 * This function can only be called if the local Bluetooth device is a
 * 4.1 or greater chipset.
 *
 * The AuthenticatedPayloadTimeout parameter is returned in
 * milliseconds
 *
 * This function will only query the Authenticated Payload Timeout for
 * LE connections. For BR/EDR connections, the
 * qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout() function must be
 * called.
 *
 * @param[in]   BluetoothStackID              Unique identifier assigned to this Bluetooth
 *                                            Protocol Stack via a call to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                       Bluetooth address of the remote LE device to
 *                                            query the authenticated payload for.
 *
 * @param[out]  AuthenticatedPayloadTimeout   Pointer to location to store the queried
 *                                            authenticated payload timeout.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_NOT_CONNECTED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Authenticated_Payload_Timeout(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t *AuthenticatedPayloadTimeout);

/**
 * @brief
 * Sets the
 * resolvable private address (RPA) timeout for RPA addresses.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * When the controller is generating RPA addresses for use in over-the-air
 * (OTA) transactions, the timeout defines the amount of time an RPA will
 * be used until the controller autonomously generates a new one.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                 Protocol Stack via a call to
 *                                 qapi_BLE_BSC_Initialize().
 *
 * @param[in]  RPA_Timeout         Defines the amount of time an RPA will
 *                                 be used until the controller autonomously
 *                                 generates a new one. In seconds.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Resolvable_Private_Address_Timeout(uint32_t BluetoothStackID, uint32_t RPA_Timeout);

/**
 * @brief
 * Enables or disables the address resolution feature of the controller.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * If the local Bluetooth device is a 4.1 or older chipset, the
 * address resolution must be resolved at the software level with a
 * call to qapi_BLE_GAP_LE_Resolve_Address().
 *
 * @param[in]  BluetoothStackID          Unique identifier assigned to this Bluetooth
 *                                       Protocol Stack via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EnableAddressResolution   Boolean value to enable address resolution in the
 *                                       controller.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Address_Resolution_Enable(uint32_t BluetoothStackID, boolean_t EnableAddressResolution);

/**
 * @brief
 * Adds one (or more) devices to the resolving list.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * @param[in]   BluetoothStackID         Unique identifier assigned to this Bluetooth
 *                                       Protocol Stack via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DeviceCount              Number of devices to add to the resolving
 *                                       list (one or more). Must be less than or equal
 *                                       to the number of entries in
 *                                       ResolvingListEntries parameter.
 *
 * @param[in]   ResolvingListEntries     Pointer to an array of resolving list members
 *                                      (of at least DeviceCount entries) that specify
 *                                       the device(s) to add to the resolving list.
 *
 * @param[out]  AddedDeviceCount         Pointer to a buffer that will contain the
 *                                       number of devices in the ResolvingListEntries
 *                                       array that were successfully added to the
 *                                       Bluetooth Controller's resolving List (on
 *                                       return from this function).
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_Resolving_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *AddedDeviceCount);

/**
 * @brief
 * Removes devices from the resolving list.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * Specifying a DeviceCount of zero instructs the module to delete all
 * members from the resolving list (that is, clear the resolving list).
 *
 * The Peer_IRK and Local_IRK members of the
 * qapi_BLE_GAP_LE_Resolving_List_Entry_t structure are not used by
 * this function.
 *
 * @param[in]   BluetoothStackID         Unique identifier assigned to this Bluetooth
 *                                       Protocol Stack via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DeviceCount              Number of devices to remove from the resolving
 *                                       list (one or more). must be less than or equal
 *                                       to the number of entries in
 *                                       ResolvingListEntries parameter.
 *
 * @param[in]   ResolvingListEntries     Pointer to an array of resolving list members
 *                                      (of at least DeviceCount entries) that specify
 *                                       the device(s) to remove from the resolving list.
 *
 * @param[out]  RemovedDeviceCount       Pointer to a buffer that will contain the
 *                                       number of devices in the ResolvingListEntries
 *                                       array that were successfully removed from the
 *                                       Bluetooth Controller's resolving List (on
 *                                       return from this function).
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *              @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_Resolving_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Resolving_List_Entry_t *ResolvingListEntries, uint32_t *RemovedDeviceCount);

/**
 * @brief
 * Reads the resolving list size
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * The returned resolving list size is returned in terms of the number
 * of device entries it may hold (not individual bytes).
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to this Bluetooth
 *                                  Protocol Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[out]  ResolvingListSize   Pointer to an integer where the resolving List
 *                                  size will be returned if this function returns
 *                                  success.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Resolving_List_Size(uint32_t BluetoothStackID, uint32_t *ResolvingListSize);

/**
   @brief
   Sets the privacy mode for an entry in the resolving list.

   @details
   This function can only be called if the local Bluetooth device is a
   5.0 or greater chipset.

   The returned resolving list size is returned in terms of the number
   of device entries it may hold (not individual bytes).

   @param[in]   BluetoothStackID             Unique identifier assigned
                                             to this Bluetooth Protocol
                                             Stack via a call to
                                             qapi_BLE_BSC_Initialize().

   @param[in]   Peer_Identity_Address_Type   Peer's identity address
                                             type.

   @param[in]   Peer_Identity_Address        Peer's identity address.

   @param[in]   PrivacyMode                  Privacy mode.

 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Resolving_List_Privacy_Mode(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t Peer_Identity_Address_Type, qapi_BLE_BD_ADDR_t Peer_Identity_Address, qapi_BLE_GAP_LE_Privacy_Mode_t PrivacyMode);

/**
 * @brief
 * Suggests a maximum
 * Tx packet size and time for the specified connection to
 * the specified device.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * If this function returns QAPI_BLE_BTPS_ERROR_DEVICE_NOT_CONNECTED,
 * a connection to the specified Bluetooth Board Address does not
 * exist.
 *
 * This function is only used to make suggestions to the controller
 * for the specified connection. The controller is allowed to
 * make its own decision on the maximum packet size/time based
 * on other factors.
 *
 * The #QAPI_BLE_ET_LE_DATA_LENGTH_CHANGE_E event is dispatched to
 * the application any time the data lengths used for a connection
 * have changed (this can happen any time, even if this API is not
 * used).
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Bluetooth Board Address of the Remote LE
 *                                     Bluetooth Device which is connected, for the
 *                                     Suggested Tx Packet Size and Time.
 *
 * @param[in]  SuggestedTxPacketSize   Suggested packet size.
 *
 * @param[in]  SuggestedTxPacketTime   Suggested packet time.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                  QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                  QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                  QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                  QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Data_Length(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime);

/**
 * @brief
 * Suggests a maximum Tx Packet size and time for a new LE connection.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * This function is only used to make suggestions to the controller
 * for the new connections. The controller is allowed to
 * make its own decision on the maximum packet size/time based
 * on other factors.
 *
 * The #QAPI_BLE_ET_LE_DATA_LENGTH_CHANGE_E event is dispatched to
 * the application any time the data lengths used for a connection
 * have changed (this can happen any time, even if this API is not
 * used).
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  SuggestedTxPacketSize   Suggested packet size.
 *
 * @param[in]  SuggestedTxPacketTime   Suggested packet time.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Data_Length(uint32_t BluetoothStackID, uint16_t SuggestedTxPacketSize, uint16_t SuggestedTxPacketTime);

/**
 * @brief
 * Queries the
 * suggested maximum Tx Packet Size and Time for new LE connections from
 * the controller.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 4.2 or greater chipset.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                      Protocol Stack via a call to
 *                                      qapi_BLE_BSC_Initialize().
 *
 * @param[out]  SuggestedTxPacketSize   Pointer to the suggested packet size that
 *                                      will be returned if this function returns
 *                                      success.
 *
 * @param[out]  SuggestedTxPacketTime   Pointer to the suggested packet time that
 *                                      will be returned if this function returns
 *                                      success.
 *
 * @return
 * Zero -- If successful.\n
 * Error code -- If negative; one of the following values:
 *               @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_NOT_INITIALIZED \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_ERROR
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Default_Data_Length(uint32_t BluetoothStackID, uint16_t *SuggestedTxPacketSize, uint16_t *SuggestedTxPacketTime);

/**
 * @brief
 * Sets the default transmitter/receiver PHYs for future LE connections.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The valid bits that may be set in the TxPHYSPreference and RxPHYSPreference
 * parameter are defined in the form QAPI_BLE_GAP_LE_PHY_PREFERENCE_XXX.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to this Bluetooth
 *                                      Protocol Stack via a call to
 *                                      qapi_BLE_BSC_Initialize().
 *
 * @param[in]  TxPHYSPreference         Bit mask containing the applications preferences
 *                                      for the local transmitting PHY.
 *
 * @param[in]  RxPHYSPreference         Bit mask containing the applications preferences
 *                                      for the local receiving PHY.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Connection_PHY(uint32_t BluetoothStackID, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference);

/**
 * @brief
 * Sets the transmitter/receiver PHYs for the specified LE
 * connection.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The #QAPI_BLE_ET_LE_PHY_UPDATE_COMPLETE_E event will be received if this
 * function is successful, to inform the host of transmitter and receiver PHYs
 * for the specified LE connection.
 *
 * The valid bits that may be set in the TxPHYSPreference and RxPHYSPreference
 * parameter are defined in the form QAPI_BLE_GAP_LE_PHY_PREFERENCE_XXX.
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Address of the remote LE Device.
 *
 * @param[in]  TxPHYSPreference        Bit mask containing the applications preferences
 *                                     for the local transmitting PHY.
 *
 * @param[in]  RxPHYSPreference        Bit mask containing the applications preferences
 *                                     for the local receiving PHY.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_PHY(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint32_t TxPHYSPreference, uint32_t RxPHYSPreference);

/**
 * @brief
 * Queries the current transmitter/receiver PHYs for the specified LE connection.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID       Unique identifier assigned to this Bluetooth
 *                                     Protocol Stack via a call to
 *                                     qapi_BLE_BSC_Initialize().
 *
 * @param[in]  BD_ADDR                 Address of the remote LE Device.
 *
 * @param[out]  TxPHY                  Pointer to return the current Tx PHY for the
 *                                     specified connection if this function is
 *                                     successful.
 *
 * @param[out]  RxPHY                  Pointer to return the current Rx PHY for the
 *                                     specified connection if this function is
 *                                     successful.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Connection_PHY(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_PHY_Type_t *TxPHY, qapi_BLE_GAP_LE_PHY_Type_t *RxPHY);

/**
 * @brief
 * Queries the maximum allowable length of advertising data (in bytes) that may
 * be set for use as advertising (including periodic advertising) or
 * scan response data.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[out]  MaximumAdvertisingDataLength   Holds the maximum
 *                                             advertising data length.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length(uint32_t BluetoothStackID, uint32_t *MaximumAdvertisingDataLength);

/**
 * @brief
 * Queries the number of advertising sets supported by the local controller.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID      Unique identifier assigned to this
 *                                    Bluetooth Protocol Stack via a call
 *                                    to qapi_BLE_BSC_Initialize().
 *
 * @param[out]  NumberSupportedSets   Holds the number of supported
 *                                    advertising sets.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Number_Of_Advertising_Sets(uint32_t BluetoothStackID, uint32_t *NumberSupportedSets);

/**
 * @brief
 * Sets mimimum supported LE encryption key size to be allowed via pairing.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a call
 *                                 to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EncryptionKeySize   Holds the minimum encryption key size
 *                                 to set in range [QAPI_BLE_GAP_LE_MINIMUM_ENCRYPTION_KEY_SIZE,
 *                                 GAP_LE_MAXIMUM_ENCRYPTION_KEY_SIZE].
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Minimum_Encryption_Key_Size(uint32_t BluetoothStackID, uint8_t EncryptionKeySize);

/**
 * @brief
 * Sets the advertising parameters for an advertising set.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The AdvertisingHandle must be a handle for a previously
 * defined set or it will be used to identify the set
 * created by this API call.  The AdvertisingHandle is
 * defined by the upper layer.  It must be in range: [
 * QAPI_BLE_MINIMUM_ADVERITISING_HANDLE,
 * QAPI_BLE_MAXIMUM_ADVERITISING_HANDLE ].
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to
 *                                      this Bluetooth Protocol Stack via
 *                                      a call to
 *                                      qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle       Identifies the advertising set.
 *
 * @param[in]   AdvertisingParameters   Extended advertising
 *                                      parameters for the advertising
 *                                      set.
 *
 * @param[out]  SelectedTxPower         Holds the transmit power.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Extended_Advertising_Parameters_t *AdvertisingParameters, int8_t *SelectedTxPower);

/**
 * @brief
 * Writes a random address to the Bluetooth device for use when advertising
 * packets from the specified set.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned to
 *                                  this Bluetooth Protocol Stack via
 *                                  a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle   Identifies the advertising set.
 *
 * @param[in]   RandomAddress       Random address.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Random_Address(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_BD_ADDR_t RandomAddress);

/**
 * @brief
 * Writes the extended advertising data for a specified advertising set
 * that will be advertised.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The Length and Advertising_Data parameters are optional.If Length and
 * Advertising_Data parameters are zero and NULL and the Operation is set
 * to QAPI_BLE_AOT_UPDATE_DID_E then this will just update the DID value
 * for the set in the controller.  If the operation is set to
 * #QAPI_BLE_AOT_SET_DATA_E in this case the advertising data will be
 * cleared for the specified set.
 *
 * If advertising data is specified via the Length and Advertising_Data
 * parameters then the it must be less than or equeal to the length
 * returned via the
 * qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length() API.
 *
 * @param[in]   BluetoothStackID          Unique identifier assigned
 *                                        to this Bluetooth Protocol
 *                                        Stack via a call to
 *                                        qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle         Identifies the advertising set.
 *
 * @param[in]   Operation                 Operation to performed.
 *
 * @param[in]   FragmentationPreference   Fragment preference
 *                                        that is requested of
 *                                        the controller.
 *
 * @param[in]   Length                    Length of the advertising data.
 *
 * @param[in]   Advertising_Data          Advertising data.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Advertising_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Operation_Type_t Operation, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Advertising_Data);

/**
 *  @brief
 *  Writes the extended Scan Response data for a specified Scan
 *  Response set that will be advertised.
 *
 *  @details
 *  This function can only be called if the local Bluetooth device is a
 *  5.0 or greater chipset.
 *
 *  The Length and Scan_Response_Data parameters are
 *  optional.  If Length and Scan_Response_Data parameters
 *  are zero and NULL the Scan Response data will be cleared
 *  for the specified set.
 *
 *  If advertising data is specified via the Length and
 *  Scan_Response_Data parameters then the it must be less
 *  than or equeal to the length returned via the
 *  qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length() API.
 *
 *  @param[in]   BluetoothStackID          Unique identifier assigned
 *                                         to this Bluetooth Protocol
 *                                         Stack via a call to
 *                                         qapi_BLE_BSC_Initialize().
 *
 *  @param[in]   AdvertisingHandle         Identifies the advertising set.
 *
 *  @param[in]   FragmentationPreference   Fragment preference that is
 *                                         requested of the controller.
 *
 *  @param[in]   Length                    Length of the scan response
 *                                         data.
 *
 *  @param[in]   Scan_Response_Data        Scan respone data.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Scan_Response_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Advertising_Fragment_Preference_t FragmentationPreference, uint32_t Length, uint8_t *Scan_Response_Data);

/**
 * @brief
 * Alows enabling or disabling extended advertising for a list of advertising sets.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * If Enable is FALSE then NumberOfSets may be set to 0 (and the rest of
 * the parameters passed as NULL).  In this case extended advertising
 * will be disabled for all advertising sets.
 *
 * NumberOfSets may not exceed
 * QAPI_BLE_MAXIMUM_ENABLE_DISABLE_EXTENDED_ADVERTISING_SETS.
 *
 * The Duration list entries are specified in units of
 * milliseconds.  This list will also be modified by this
 * function and should not be expected to retain its value.
 *
 * The maximum allowable duration is specified by
 * #QAPI_BLE_MAXIMUM_EXTENDED_ADVERTISING_DURATION (in milliseconds).
 *
 * @param[in]   BluetoothStackID                  Unique identifier
 *                                                assigned to this
 *                                                Bluetooth Protocol
 *                                                Stack via a call to
 *                                                qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable                            Enables/Disables the
 *                                                specified advertising
 *                                                set(s).
 *
 * @param[in]   NumberOfSets                      Number of advertising
 *                                                sets.
 *
 * @param[in]   AdvertisingHandleList             Advertising handle
 *                                                for each specified
 *                                                advertising set.
 *
 * @param[in]   DurationList                      Duration for each
 *                                                specified advertising
 *                                                set.
 *
 * @param[in]   MaxExtendedAdvertisingEventList   Maximum number of
 *                                                extended advertisements
 *                                                for each advertising
 *                                                set.
 *
 * @param[in]  GAP_LE_Event_Callback              Pointer to a callback
 *                                                function to be used by
 *                                                the GAP layer to
 *                                                dispatch GAP LE event
 *                                                information for this
 *                                                request.
 *
 * @param[in]  CallbackParameter                  User defined value to
 *                                                be used by the GAP
 *                                                layer as an input
 *                                                parameter for the
 *                                                callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Extended_Advertising(uint32_t BluetoothStackID, boolean_t Enable, uint8_t NumberOfSets, uint8_t *AdvertisingHandleList, uint32_t *DurationList, uint8_t *MaxExtendedAdvertisingEventList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Removes advertising sets from the local Bluetooth controller.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The NumberAdvertisingSetHandles and AdvertisingHandles parameters are
 * optional.  If they are not specified (0 and NULL) all existing
 * Advertising Sets in the controller will be removed (in which case the
 * RemovedSetCount parameter will not be used to return the number of
 * removed sets).
 *
 * @param[in]   BluetoothStackID              Unique identifier
 *                                            assigned to this Bluetooth
 *                                            Protocol Stack via a call
 *                                            to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]   NumberAdvertisingSetHandles   Number of
 *                                            advertising set handles.
 *
 * @param[in]   AdvertisingHandles            List of advertising set
 *                                            handles.
 *
 * @param[out]  RemovedSetCount               Holds the number of
 *                                            advertising sets that have
 *                                            been removed.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Advertising_Sets(uint32_t BluetoothStackID, uint32_t NumberAdvertisingSetHandles, uint8_t *AdvertisingHandles, uint32_t *RemovedSetCount);

/**
 * @brief
 * Sets the periodic advertising parameters for the specified
 * advertising set.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The periodic advertising parameters must be set before periodic
 * advertising can be enabled for the specified advertising set.
 *
 * @param[in]   BluetoothStackID              Unique identifier
 *                                            assigned to this Bluetooth
 *                                            Protocol Stack via a call
 *                                            to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle             Identifies the advertising
 *                                            set.
 *
 * @param[in]   PeriodicAdvertisingParameters Periodic advertising
 *                                            parameters.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, qapi_BLE_GAP_LE_Periodic_Advertising_Parameters_t *PeriodicAdvertisingParameters);

/**
 * @brief
 * Sets the periodic advertising data for the specified
 * advertising set.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The Length and Advertising_Data parameters are optional.
 * If Length and Advertising_Data parameters are zero and
 * NULL the periodic advertising data will be cleared for
 * the specified set.
 *
 * If advertising data is specified via the Length and
 * Advertising_Data parameters then the it must be less than
 * or equal to the length returned via the
 * qapi_BLE_GAP_LE_Query_Maximum_Advertising_Data_Length() API.
 *
 * The periodic advertising data must be set before periodic
 * advertising can be enabled for the specified advertising set.
 *
 * @param[in]   BluetoothStackID              Unique identifier
 *                                            assigned to this Bluetooth
 *                                            Protocol Stack via a call
 *                                            to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle             Identifies the advertising
 *                                            set.
 *
 * @param[in]   Length                        Length of advertising data.
 *
 * @param[in]   Advertising_Data              Advertising data.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Data(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, uint32_t Length, uint8_t *Advertising_Data);

/**
 * @brief
 * Enables/disables periodic advertising for the specified
 * advertising set.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID              Unique identifier
 *                                            assigned to this Bluetooth
 *                                            Protocol Stack via a call
 *                                            to
 *                                            qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable                        Enables/disables periodic
 *                                            advertising.
 *
 * @param[in]   AdvertisingHandle             Identifies the advertising
 *                                            set.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Periodic_Advertising(uint32_t BluetoothStackID, boolean_t Enable, uint8_t AdvertisingHandle);

/**
 * @brief
 * Sets the parameters to be used with a future Extended LE
 * Scanning operation.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The following enumerated types may be used with the
 * LocalAddressType member:
 *
 * @li QAPI_BLE_LAT_PUBLIC_E
 * @li QAPI_BLE_LAT_RANDOM_E
 * @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E
 * @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E
 *
 * Note if the final two enumerated types are specified
 * (QAPI_BLE_LAT_RESOLVABLE_FALLBACK_XXX) then the controller will
 * attempt to generate a Resolvable Private Address to place
 * in the scan request packets if the advertiser is in the
 * resolving list.  If the device is not in the resolving
 * list then the controller will use either the public
 * address (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E) or the random
 * address set via qapi_BLE_GAP_LE_Set_Random_Address()
 * (#QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E).
 *
 * The following enumerated types may be used with the
 * FilterPolicy parameter:
 *
 * @li QAPI_BLE_FP_NO_FILTER_E
 * @li QAPI_BLE_FP_WHITE_LIST_E
 * @li QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 * @li QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
 *
 * If either of the #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E or
 * #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E types are specified for the
 * FilterPolicy, the application can expect to receive the
 * #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E event when a directed
 * advertisement that is directed towards a resolvable private address is
 * received by the controller.
 *
 * If the #QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E type is used for the
 * FilterPolicy parameter then the device can expect to
 * receive advertising reports based on the following
 * criteria:
 *
 * @li all un-directed advertising packets
 * @li all directed advertising packets where the initiator
 *     address (the device for whom the packets are intended) is a
 *     resolvable private address
 * @li all directed advertising packets address to the
 *     local device
 *
 * When this type is used the application can expect to
 * receive #QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E events when
 * directed advertising packets where the iniator address is
 * a resolvable private address.  The application can then
 * use the local IRK(s) to determine if the directed
 * advertisement is intended to be received by the local
 * device and then can make an application decision on
 * whether to connect to the device.
 *
 * If the #QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E type is used for the
 * FilterPolicy parameter then the device can expect to
 * receive advertising reports based on the following
 * criteria:
 *
 * @li all un-directed advertising packets from devices
 *     where the advertiser's address is stored in the
 *     white list
 * @li all directed advertising packets where the initiator address (the
 *     device for whom the packets are intended) is a resolvable private
 *     address
 * @li all directed advertising packets address to the local device
 *
 * When this type is used the application can expect to
 * receive QAPI_BLE_ET_LE_DIRECT_ADVERTISING_REPORT_E events when
 * directed advertising packets where the iniator address is
 * a resolvable private address.  The application can then
 * use the local IRK(s) to determine if the directed
 * advertisement is intended to be received by the local
 * device and then can make an application decision on
 * whether to connect to the device.
 *
 * Scanning may only be performed on the LE 1M and LE Coded
 * PHYs.  The LE 2M PHY is not a valid PHY to be specified
 * to this function.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to
 *                                      this Bluetooth Protocol Stack via
 *                                      a call to
 *                                      qapi_BLE_BSC_Initialize().
 *
 * @param[in]   LocalAddressType        Local device's address type.
 *
 * @param[in]   FilterPolicy            Scanning filter policy.
 *
 * @param[in]   NumberScanningPHYs      Number of PHYs used for scanning.
 *                                      One PHY MUST be specified.
 *
 * @param[in]   ScanningParameterList   List of the scanning
 *                                      parameters for each PHY that is
 *                                      used for scanning.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Extended_Scan_Parameters(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, qapi_BLE_GAP_LE_Filter_Policy_t FilterPolicy, uint32_t NumberScanningPHYs, qapi_BLE_GAP_LE_Extended_Scanning_PHY_Parameters_t *ScanningParameterList);

/**
 * @brief
 * Allows enabling or disabling extended scanning.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * The Duration parameter, if non-zero, must be in the
 * following range (in milliseconds): [
 * #QAPI_BLE_MINIMUM_EXTENDED_SCAN_DURATION,
 * #QAPI_BLE_MAXIMUM_EXTENDED_SCAN_DURATION ].
 *
 * The Period parameter, if non-zero, must be in the
 * following range  (in milliseconds): [
 * #QAPI_BLE_MINIMUM_EXTENDED_SCAN_PERIOD,
 * #QAPI_BLE_MAXIMUM_EXTENDED_SCAN_PERIOD ].
 *
 * The callback function and parameter are not used when
 * Enable = FLASE and may be set to NULL and 0 respectively.
 *
 * @param[in]   BluetoothStackID        Unique identifier assigned to
 *                                      this Bluetooth Protocol Stack via
 *                                      a call to
 *                                      qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Enable                  Enables/disables extended
 *                                      scanning.
 *
 * @param[in]   FilterDuplicates        Controls whether the controller
 *                                      should filter duplicate
 *                                      advertising packets.
 *
 * @param[in]   Duration                If non-zero, specifies the length
 *                                      of time (ms) that extended
 *                                      scanning should last before being
 *                                      terminated by the controller.
 *                                      Otherwise scanning will remain
 *                                      continue until explicitly
 *                                      terminated.
 *
 * @param[in]   Period                  Specifies the period of the
 *                                      periodic extended scanning
 *                                      operation.
 *
 * @param[in]   GAP_LE_Event_Callback   Pointer to a callback function to
 *                                      be used by the GAP layer to
 *                                      dispatch GAP LE event information
 *                                      for this request.
 *
 * @param[in]  CallbackParameter        User defined value to be used by
 *                                      the GAP layer as an input
 *                                      parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Enable_Extended_Scan(uint32_t BluetoothStackID, boolean_t Enable, qapi_BLE_GAP_LE_Extended_Scan_Filter_Duplicates_Type_t FilterDuplicates, uint32_t Duration, uint32_t Period, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows establishing an LE master connection to a remote device.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * This function is asynchronous in nature and the caller is
 * informed when the connection is established via the
 * GAP_LE_Event_Callback function.
 *
 * If the InitatorFilterPolicy parameter is set to
 * #QAPI_BLE_FP_WHITE_LIST_E then the RemoteAddressType and RemoteDevice
 * parameter are not used and NULL values may be passed in
 * for them.
 *
 * The following enumerated types may be set with the
 * RemoteAddressType member:
 *
 * @li QAPI_BLE_LAT_PUBLIC_E
 * @li QAPI_BLE_LAT_RANDOM_E
 * @li QAPI_BLE_LAT_PUBLIC_IDENTITY_E
 * @li QAPI_BLE_LAT_RANDOM_IDENTITY_E
 *
 * The latPublicIdentity and latRandomIdentity indicate that
 * the RemoteDevice parameter is an identity address (a
 * semi-permanent address that can be used to refer to the
 * device) that was received from the remote device (along
 * with the remote device's IRK) during a successful
 * LE Pairing process.
 *
 * The following enumerated types may be returned with the
 * LocalAddressType member:
 *
 * @li QAPI_BLE_LAT_PUBLIC_E
 * @li QAPI_BLE_LAT_RANDOM_E
 * @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PUBLIC_E
 * @li QAPI_BLE_LAT_RESOLVABLE_FALLBACK_PRIVATE_E
 *
 * Note if the final two enumerated types are specified
 * (QAPI_BLE_LAT_RESOLVABLE_FALLBACK_XXX) then the RemoteAddressType
 * and RemoteAddress parameters must be specified and valid as
 * they will be used to search the Resolving List to find
 * the local IRK to use when creating the connection.
 *
 * The following types may NOT be used with the
 * InitatorFilterPolicy parameter:
 *
 * @li QAPI_BLE_FP_NO_WHITE_LIST_DIRECTED_RPA_E
 * @li QAPI_BLE_FP_WHITE_LIST_DIRECTED_RPA_E
 *
 * At least one set of PHY parametes must be specified with the
 * NumberOfConnectionParameters and ConnectionParameterList parameters.
 * At least one of the PHYs specified in this list must be either
 * #QAPI_BLE_LPT_PHY_LE_1M_E or #QAPI_BLE_LPT_PHY_LE_CODED_E.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   InitatorFilterPolicy           Initiator filter
 *                                             policy.
 *
 * @param[in]   RemoteAddressType              Remote address type.
 *
 * @param[in]   RemoteDevice                   Remote device address.
 *
 * @param[in]   LocalAddressType               Local device address type.
 *
 * @param[in]   NumberOfConnectionParameters   Number of connection
 *                                             parameters.
 *
 * @param[in]   ConnectionParameterList        List of connection
 *                                             parameters for each PHY
 *                                             that is used to create the
 *                                             connection.
 *
 * @param[in]   GAP_LE_Event_Callback          Pointer to a callback
 *                                             function to be used by the
 *                                             GAP layer to dispatch GAP
 *                                             LE event information for
 *                                             this request.
 *
 * @param[in]  CallbackParameter               User defined value to be
 *                                             used by the GAP layer as
 *                                             an input parameter for the
 *                                             callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Extended_Create_Connection(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Filter_Policy_t InitatorFilterPolicy, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, qapi_BLE_GAP_LE_Address_Type_t LocalAddressType, uint32_t NumberOfConnectionParameters, qapi_BLE_GAP_LE_Extended_Connection_Parameters_t *ConnectionParameterList, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows a mechanism of synchronizing to a periodic advertising train.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * If the local Bluetooth device is not 5.1 or greater
 * chipset, then the CTE Type parameter will be ignored.
 *
 * This function is asynchronous in nature and the caller is
 * informed when the synchronization is established via the
 * GAP_LE_Event_Callback function.
 *
 * If the FilterPolicy is set to fpPeriodicAdvertiserList
 * then the AdvertisingSID, RemoteAddressType and
 * RemoteDevice parameters are not used and may be ignored.
 *
 * The maximum value PeriodicSkipCount may contain is
 * QAPI_BLE_MAXIMUM_PERIODIC_ADVERTISING_SKIP_COUNT.
 *
 * The SyncTimeout value must be in range (in ms): [
 * QAPI_BLE_MINIMUM_SYNCHRONIZATION_TIMEOUT,
 * QAPI_BLE_MAXIMUM_SYNCHRONIZATION_TIMEOUT ]
 *
 * If this function is successful, then the
 * synchronization is considered pending until the
 * #QAPI_BLE_ET_LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_E event has been
 * received or the qapi_BLE_GAP_LE_Cancel_Create_Periodic_Synchronization()
 * function is called to cancel the synchronization.
 *
 * The CTE_Type parameter may be used to restrict the
 * synchronization of periodic advertisements based on the
 * CTE type. Otherwise, the CTE_Type parameter should be
 * zero. The CTE_Type parameter uses bit mask values
 * (QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_XXX).
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   FilterPolicy                   Indicates how to synchronize to
 *                                             the periodic advertising train.
 *
 * @param[in]   ReportingEnabled               Indicates if periodic advertising
 *                                             reports are reported from the controller
 *                                             to the host.
 *
 * @param[in]   AdvertisingSID                 Identifies the advertising set.
 *
 * @param[in]   RemoteAddressType              Remote device's address type.
 *
 * @param[in]   RemoteDevice                   Remote device's address.
 *
 * @param[in]   PeriodicSkipCount              Number of periodic advertising
 *                                             reports that may be skipped.
 *
 * @param[in]   SyncTimeout                    Time until the sync is considered
 *                                             lost.
 *
 * @param[in]   CTE_Type                       Filters periodic advertisements
 *                                             that will be synchronized based on
 *                                             the CTE type.
 *
 * @param[in]   GAP_LE_Event_Callback          Pointer to a callback
 *                                             function to be used by the
 *                                             GAP layer to dispatch GAP
 *                                             LE event information for
 *                                             this request.
 *
 * @param[in]  CallbackParameter               User defined value to be
 *                                             used by the GAP layer as
 *                                             an input parameter for the
 *                                             callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Create_Periodic_Advertising_Synchronization(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Periodic_Filter_Policy_t FilterPolicy, boolean_t ReportingEnabled, uint8_t AdvertisingSID, qapi_BLE_GAP_LE_Address_Type_t RemoteAddressType, qapi_BLE_BD_ADDR_t *RemoteDevice, uint16_t PeriodicSkipCount, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows a mechanism of canceling pending synchronization to a
 * periodic advertising train.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cancel_Create_Periodic_Synchronization(uint32_t BluetoothStackID);

/**
 * @brief
 * Allows a mechanism of terminating synchronization to a
 * periodic advertising train.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   SyncHandle                     Identifies the synchronization
 *                                             to the periodic advertising train.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Terminate_Periodic_Synchronization(uint32_t BluetoothStackID, uint16_t SyncHandle);

/**
 * @brief
 * Allows a mechanism of adding one or more entries to the periodic
 * advertisers list.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DeviceCount                    Number of entries to add the periodic
 *                                             advertisers list.
 *
 * @param[in]   PeriodicAdvertisingListEntries List of periodic advertising list entries.
 *
 * @param[out]  AddedDeviceCount               Holds the number of added entries if this
 *                                             function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Add_Device_To_Periodic_Advertising_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries, uint32_t *AddedDeviceCount);

/**
 * @brief
 * Allows a mechanism of removing one or more entries from the periodic
 * advertisers list.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   DeviceCount                    Number of entries to remove from the
 *                                             periodic advertisers list.
 *
 * @param[in]   PeriodicAdvertisingListEntries List of periodic advertising list entries.
 *
 * @param[out]  RemovedDeviceCount             Holds the number of removed entries if this
 *                                             function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Remove_Device_From_Periodic_Advertising_List(uint32_t BluetoothStackID, uint32_t DeviceCount, qapi_BLE_GAP_LE_Periodic_Advertising_List_Entry_t *PeriodicAdvertisingListEntries, uint32_t *RemovedDeviceCount);

/**
 * @brief
 * Allows a mechanixm of reading the number of entries that may be stored for the
 * periodic advertisers list.
 *
 * @details
 * This function can only be called if the local Bluetooth device is a
 * 5.0 or greater chipset.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[out]  PeriodicAdvertisingListSize    Holds the number of entries that
 *                                             may be stored in the periodic advertisers
 *                                             list If this function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Read_Periodic_Advertising_List_Size(uint32_t BluetoothStackID, uint32_t *PeriodicAdvertisingListSize);

/**
 * @brief
 * Allows a mechanism of generating LE Secure Connections Out of Band data
 * to be sent out of band (that is not over LE) to a remote device.
 *
 * @details
 * If this function successfully returns out of band data and the data is
 * exchanged out of band, the caller must pass the data back to the stack
 * as part of its Extended Pairing Capabilities in a call to either
 * qapi_BLE_GAP_LE_Extended_Pair_Remote_Device() or qapi_BLE_GAP_LE_Authentication_Response().
 *
 * Calling the qapi_BLE_GAP_LE_Update_Local_P256_Public_Key()
 * API wil invalidate the data returned by this function.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[out]  Randomizer                     Pointer to return calculated
 *                                             randomizer value.
 *
 * @param[out]  Confirmation                   Pointer to return calculated
 *                                             confirmation value.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Local_Secure_Connections_OOB_Data(uint32_t BluetoothStackID, qapi_BLE_Secure_Connections_Randomizer_t *Randomizer, qapi_BLE_Secure_Connections_Confirmation_t *Confirmation);

/**
 * @brief
 * Allows configuring CTE transmit parameters for CTEs that will
 * be included in the specified advertising set's periodic advertisements.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * If connectionless CTE transmit has already been enabled,
 * via the qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Enable()
 * function then this function MUST NOT be called until it
 * has been disabled.
 *
 * The CTE_Length parameter MUST be in the range
 * [QAPI_BLE_GAP_LE_CTE_LENGTH_MINIMUM - QAPI_BLE_GAP_LE_CTE_LENGTH_MAXIMUM]
 * and CANNOT exceed the maximum value supported by the
 * controller.
 *
 * If the CTE_Type parameter is set to ctAoA, then the
 * LengthOfSwitchingPattern and Antenna_IDs parameters will
 * be ignored since AoA CTEs do not use antenna switching
 * for transmission.
 *
 * The CTE_Count parameter MUST be in the range
 * [QAPI_BLE_GAP_LE_CTE_COUNT_MINIMUM - QAPI_BLE_GAP_LE_CTE_COUNT_MAXIMUM].
 *
 * The LengthOfSwitchingPattern parameter MUST be in the
 * range [QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM -
 * #QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM] and CANNOT
 * exceed the maximum value supported by the controller.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle              Identifies the advertising set.
 *
 * @param[in]   CTE_Length                     Length of the CTE.
 *
 * @param[in]   CTE_Type                       Type of CTE.
 *
 * @param[in]   CTE_Count                      Number of CTEs.
 *
 * @param[in]   LengthOfSwitchingPattern       Number of antennas in the
 *                                             switching pattern.
 *
 * @param[in]   Antenna_IDs                    List of antenna IDs.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Parameters(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, uint8_t CTE_Length, qapi_BLE_GAP_LE_CTE_Type_t CTE_Type, uint8_t CTE_Count, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs);

/**
 * @brief
 * Allows enabling/disabling CTEs in the specified
 * advertising set's periodic advertisements.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Parameters()
 * function MUST be called before this function may be used.
 *
 * This function will NOT enable periodic advertising. The
 * qapi_BLE_GAP_LE_Enable_Periodic_Advertising() function MUST be
 * used to enable periodic advertising. This function may be
 * called, while periodic advertising is enabled/disabled
 * for the specified advertising set.
 *
 * If the advertising set is using the coded PHY for
 * periodic advertising then this function CANNOT be used
 * since the coded PHY does not support CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   AdvertisingHandle              Identifies the advertising set.
 *
 * @param[in]   CTE_Enable                     Enables/disables.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Enable(uint32_t BluetoothStackID, uint8_t AdvertisingHandle, boolean_t CTE_Enable);

/**
 * @brief
 * Allows sampling CTEs that are included in received periodic
 * advertisements.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * If IQ sampling is disabled, then the remaining parameters
 * are ignored.
 *
 * If the Max_Sampled_CTEs parameter is set to
 * #QAPI_BLE_GAP_LE_CTE_SAMPLE_ALL, then all available CTEs will be
 * sampled. Otherwise, the parameter MUST be in range
 * [QAPI_BLE_GAP_LE_CTE_SAMPLE_MINIMUM - QAPI_BLE_GAP_LE_CTE_SAMPLE_MAXIMUM].
 * The controller is NOT required to sample CTEs up to the
 * specified number.
 *
 * The LengthOfSwitchingPattern parameter MUST be in the
 * range [QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM -
 * #QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM] and CANNOT
 * exceed the maximum value supported by the controller.
 *
 * If this function is successful, and IQ sampling is
 * enabled, then QAPI_BLE_ET_LE_CONNECTIONLESS_IQ_REPORT_E events will
 * be received when a CTE is received in a periodic
 * advertisement.
 *
 * The SlotDurationsType, LengthOfSwitchingPattern, and
 * Antenna_IDs parameters are only used when receiving AoA
 * CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   SyncHandle                     Identifies the synchronized
 *                                             periodic advertising train.
 *
 * @param[in]   SamplingEnable                 Enables/disables IQ sampling.
 *
 * @param[in]   SlotDurationsType              Identifies the type of slot
 *                                             durations used for CTEs being sampled.
 *
 * @param[in]   Max_Sampled_CTEs               Maximum number of CTEs to sample.
*
 * @param[in]   LengthOfSwitchingPattern       Number of antennas in the
 *                                             switching pattern.
 *
 * @param[in]   Antenna_IDs                    List of antenna IDs.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connectionless_IQ_Sampling_Enable(uint32_t BluetoothStackID, uint16_t SyncHandle, boolean_t SamplingEnable, qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType, uint8_t Max_Sampled_CTEs, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs);

/**
 * @brief
 * Allows configuring CTE receive parameters for CTEs that
 * are received over the specified connection.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * If IQ sampling is disabled, then the remaining parameters
 * are ignored.
 *
 * The LengthOfSwitchingPattern parameter MUST be in the
 * range [QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM -
 * #QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM] and CANNOT
 * exceed the maximum value supported by the controller.
 *
 * The SlotDurationsType, LengthOfSwitchingPattern, and
 * Antenna_IDs parameters are only used when receiving AoA
 * CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device address.
 *
 * @param[in]   SamplingEnable                 Enables/disables IQ sampling.
 *
 * @param[in]   SlotDurationsType              Identifies the type of slot
 *                                             durations used for CTEs being sampled.
 *
 * @param[in]   LengthOfSwitchingPattern       Number of antennas in the
 *                                             switching pattern.
 *
 * @param[in]   Antenna_IDs                    List of antenna IDs.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_CTE_Receive_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t SamplingEnable, qapi_BLE_GAP_LE_Slot_Durations_Type_t SlotDurationsType, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs);

/**
 * @brief
 * Allows enabling/disabling CTE requests over the specified
 * connection.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * The qapi_BLE_GAP_LE_Set_Connection_CTE_Receive_Parameters()
 * function MUST be called at least once for the specified
 * connection before this function may be used and may be
 * called while CTE requests are enabled. If IQ sampling is
 * enabled by the
 * qapi_BLE_GAP_LE_Set_Connection_CTE_Receive_Parameters() function,
 * then QAPI_BLE_ET_LE_CONNECTION_IQ_REPORT_E events will be generated
 * when a CTE is received over the specified connection.
 *
 * If CTE requests are disabled, then the remaining
 * parameters are ignored.
 *
 * The CTE_Request_Interval parameter may only be set to the
 * following:
 *
 *  @li QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_NONE - One request ONLY.
 *
 *  @li [QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_MINIMUM - QAPI_BLE_GAP_LE_CTE_REQUEST_INTERVAL_MAXIMUM]
 *
 * The CTE_Length parameter MUST be in the range
 * [QAPI_BLE_GAP_LE_CTE_LENGTH_MINIMUM - QAPI_BLE_GAP_LE_CTE_LENGTH_MAXIMUM]
 * and CANNOT exceed the maximum value supported by the
 * controller.
 *
 * If the coded PHY is currently being used for the
 * connection with the remote device, then this function
 * CANNOT be used since the coded PHY does not support CTEs.
 * If CTE requests are enabled, and the PHY for the
 * connection with the remote device changes to the coded
 * PHY, then CTE requests will be disabled.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device address.
 *
 * @param[in]   Enable                         Enables/disables CTE requests
 *                                             over the specified connection.
 *
 * @param[in]   CTE_Request_Interval           Requested CTE interval.
 *
 * @param[in]   Requested_CTE_Length           Requested CTE length.
 *
 * @param[in]   Requested_CTE_Type             Requested CTE type.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_CTE_Request_Enable(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Enable, uint16_t CTE_Request_Interval, uint8_t Requested_CTE_Length, qapi_BLE_GAP_LE_CTE_Type_t Requested_CTE_Type);

/**
 * @brief
 * Allows configuring CTE transmit parameters for CTEs that
 * are requested over the specified connection.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * The CTE_Types parameter uses the bit mask values
 * (QAPI_BLE_GAP_LE_CTE_TYPES_XXX).
 *
 * The LengthOfSwitchingPattern parameter MUST be in the
 * range [QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MINIMUM -
 * #QAPI_BLE_GAP_LE_LENGTH_OF_SWITCHING_PATTERN_MAXIMUM] and CANNOT
 * exceed the maximum value supported by the controller.
 *
 * The LengthOfSwitchingPattern and Antenna_IDs parameters
 * are only used for transmitting AoD CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device address.
 *
 * @param[in]   CTE_Types                      CTE types that may be requested
 *                                             to transmit.
 *
 * @param[in]   LengthOfSwitchingPattern       Number of antennas in the
 *                                             switching pattern.
 *
 * @param[in]   Antenna_IDs                    List of antenna IDs.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Connection_CTE_Transmit_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint8_t CTE_Types, uint8_t LengthOfSwitchingPattern, uint8_t *Antenna_IDs);

/**
 * @brief
 * Allows enabling/disabling CTE responses that
 * may be requested over the specified connection.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Set_Connectionless_CTE_Transmit_Parameters()
 * function MUST be called before this function may be used.
 *
 * This function will NOT enable periodic advertising. The
 * qapi_BLE_GAP_LE_Enable_Periodic_Advertising() function MUST be
 * used to enable periodic advertising. This function may be
 * called, while periodic advertising is enabled/disabled
 * for the specified advertising set.
 *
 * If the advertising set is using the coded PHY for
 * periodic advertising then this function CANNOT be used
 * since the coded PHY does not support CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device address.
 *
 * @param[in]   Enable                         Enables/disables CTE responses
 *                                             over the specified connection.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Connection_CTE_Response_Enable(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, boolean_t Enable);

/**
 * @brief
 * Allows mechanism of querying the antenna information.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * This function is primarily intended to allow the local
 * device to determine the optional and supported features for CTEs.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[out]  AntennaInfo                    Holds information about the antenna
 *                                             array if this function is successful.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Query_Antenna_Information(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_Antenna_Information_t *AntennaInfo);

/**
 * @brief
 * Allows enabling/disabling periodic advertising reporting from
 * the controller to host for the specified synchronized periodic
 * advertising train.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * @param[in] BluetoothStackID  Unique identifier assigned to this Bluetooth
 *                              Protocol Stack via a call to 
 *                              qapi_BLE_BSC_Initialize().
 * @param[in]   SyncHandle      Identifies the synchronization
 *                              to the periodic advertising train.
 * @param[in] Enable            Enables/disables CTE responses over the
 *                              specified connection.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Receive_Enable(uint32_t BluetoothStackID, uint16_t SyncHandle, boolean_t Enable);

/**
 * @brief
 * Allows the local device that is synchronized to a periodic
 * advertising train to transfer synchronization information to a
 * connected remote device.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * This function is primarily intendeded to be called if the
 * local device is synchronized to periodic advertisements.
 * The connected remote device may be connected or
 * un-connected to the advertiser.
 *
 * If the local device is transmitting the periodic
 * advertisements, then the
 * qapi_BLE_GAP_LE_Periodic_Advertising_Set_Info_Transfer() function
 * MUST be used.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device's address.
 *
 * @param[in]   ServiceData                    A host specified value that will be
 *                                             sent along with the synchronization
 *                                             information to the connected remote
 *                                             device.
 *
 * @param[in]   SyncHandle                     Identifies the periodic advertising
 *                                             train.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t ServiceData, uint16_t SyncHandle);

/**
 * @brief
 * Allows the local device that is advertising the periodic
 * advertisements to transfer synchronization information to a
 * connected remote device.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * This function is primarily intendeded to be called if the
 * local device is transmitting periodic advertisements for
 * the specified advertising set.
 *
 * If the local device is synchronized to the periodic
 * advertisements, then the
 * qapi_BLE_GAP_LE_Periodic_Advertising_Sync_Transfer() function MUST
 * be used.
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device's address.
 *
 * @param[in]   ServiceData                    A host specified value that will be
 *                                             sent along with the synchronization
 *                                             information to the connected remote
 *                                             device.
 *
 * @param[in]   AdvertisingHandle              Identifies the advertising set.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Periodic_Advertising_Set_Info_Transfer(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, uint16_t ServiceData, uint8_t AdvertisingHandle);

/**
 * @brief
 * Allows configuring the default behaviour when periodic advertising sync
 * information has been received from future connected remote devices.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * If the Mode parameter is set to QAPI_BLE_STM_NO_SYNC_E, then the
 * remaining parameters are ignored.
 *
 * If the Mode parameter is set to QAPI_BLE_STM_AUTO_SYNC_NO_REPORTS_E or
 * #QAPI_BLE_STM_AUTO_SYNC_REPORTS_E, then the CTE_Type parameter may be
 * used to restrict the automatic synchronization of
 * periodic advertisements based on the CTE type. Otherwise,
 * the CTE_Type parameter should be zero. The CTE_Type
 * parameter uses bit mask values
 * (QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_XXX).
 *
 * The Skip parameter MUST be in the range [0 -
 * QAPI_BLE_MAXIMUM_PERIODIC_ADVERTISING_SKIP_COUNT].
 *
 * The SyncTimeout parameter MUST be in the range
 * [QAPI_BLE_MINIMUM_SYNCHRONIZATION_TIMEOUT -
 * QAPI_BLE_MAXIMUM_SYNCHRONIZATION_TIMEOUT].
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   BD_ADDR                        Connected remote device's address.
 *
 * @param[in]   Mode                           Specifies the behaviour when periodic
 *                                             advertising sync information has been
 *                                             received from a connected remote device.
 *
 * @param[in]   Skip                           Number of periodic advertising reports
 *                                             that may be skipped.
 *
 * @param[in]   SyncTimeout                    Timeout until the sync is considered lost.
 *
 * @param[in]   CTE_Type                       Filter periodic advertising synchronization
 *                                             based on the CTE type.
 *
 * @param[in]   GAP_LE_Event_Callback          Pointer to a callback function to be
 *                                             used by the GAP layer to dispatch GAP LE
 *                                             Event information for this request.
 *
 * @param[in]   CallbackParameter              User-defined value to be used by the GAP
 *                                             layer as an input
 *                                             parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, qapi_BLE_BD_ADDR_t BD_ADDR, qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode, uint16_t Skip, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows configuring the behaviour when periodic advertising sync
 * information has been received from the connected remote device.
 *
 * @details
 * This function can only be called if the local Bluetooth
 * device is a 5.1 or greater chipset.
 *
 * The qapi_BLE_GAP_LE_Query_Antenna_Information() function MUST be
 * called prior to using this function. See the
 * qapi_BLE_GAP_LE_Antenna_Information_t structure for more
 * information.
 *
 * If the Mode parameter is set to QAPI_BLE_STM_NO_SYNC_E, then the
 * remaining parameters are ignored.
 *
 * If the Mode parameter is set to QAPI_BLE_STM_AUTO_SYNC_NO_REPORTS_E or
 * #QAPI_BLE_STM_AUTO_SYNC_REPORTS_E, then the CTE_Type parameter may be
 * used to restrict the automatic synchronization of
 * periodic advertisements based on the CTE type. Otherwise,
 * the CTE_Type parameter should be zero. The CTE_Type
 * parameter uses bit mask values
 * (QAPI_BLE_GAP_LE_CTE_TYPE_NO_SYNC_XXX).
 *
 * The Skip parameter MUST be in the range [0 -
 * QAPI_BLE_MAXIMUM_PERIODIC_ADVERTISING_SKIP_COUNT].
 *
 * The SyncTimeout parameter MUST be in the range
 * [QAPI_BLE_MINIMUM_SYNCHRONIZATION_TIMEOUT -
 * QAPI_BLE_MAXIMUM_SYNCHRONIZATION_TIMEOUT].
 *
 * @param[in]   BluetoothStackID               Unique identifier assigned
 *                                             to this Bluetooth Protocol
 *                                             Stack via a call to
 *                                             qapi_BLE_BSC_Initialize().
 *
 * @param[in]   Mode                           Specifies the behaviour when periodic
 *                                             advertising sync information has been
 *                                             received from a connected remote device.
 *
 * @param[in]   Skip                           Number of periodic advertising reports
 *                                             that may be skipped.
 *
 * @param[in]   SyncTimeout                    Timeout until the sync is considered lost.
 *
 * @param[in]   CTE_Type                       Filter periodic advertising synchronization
 *                                             based on the CTE type.
 *
 * @param[in]   GAP_LE_Event_Callback          Pointer to a callback function to be used
 *                                             by the GAP layer to dispatch GAP LE Event
 *                                             information for this request.
 *
 * @param[in]   CallbackParameter              User-defined value to be used by the
 *                                             GAP layer as an input
 *                                             parameter for the callback.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_PA_Sync_Transfer_Mode_t Mode, uint16_t Skip, uint32_t SyncTimeout, uint8_t CTE_Type, qapi_BLE_GAP_LE_Event_Callback_t GAP_LE_Event_Callback, unsigned long CallbackParameter);

/**
 * @brief
 * Allows for initializing an AES-CMAC context for use when calculating
 * the AES CMAC hash of a blob.
 *
 * @param[in] Key            Pointer to the key used to calculate the AES-CMAC
 *                           operation.
 * @param[in] MessageLength  Total number of bytes of the blob used to
  *                          calculate the AES-CMAC value over.
 *
 * @detdesc
 * This function returns a pointer to a context. If this function
 * returns a valid (non-NULL) pointer then the
 * qapi_BLE_GAP_LE_Cleanup_AES_CMAC_Operation() API must be called
 * to free the memory associated with the context.
 *
 * @return
 * Valid (Non-NULL) pointer -- To AES-CMAC context
 *              structure that must be used for further calls to AES
 *              CMAC.
 */
QAPI_BLE_DECLARATION void *QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Initialize_AES_CMAC_Operation(qapi_BLE_Encryption_Key_t *Key, uint32_t MessageLength);

/**
 * @brief
 * Allows for cleaning up an AES-CMAC context after an AES-CMAC operation
 * has completed.
 *
 * @details
 * The context passed to this function must have been returned via a
 * successful call to qapi_BLE_GAP_LE_Initialize_AES_CMAC_Operation().
 *
 * @param[in]   GapleAesCmacContext     Pointer to the AES-CMAC context.
 *
 * @return
 * None.
 */
QAPI_BLE_DECLARATION void QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Cleanup_AES_CMAC_Operation(void *GapleAesCmacContext);

/**
 * @brief
 * Performs an AES-CMAC operation over the given blob.
 *
 * @details
 * The following function is provided to do a block-by-block
 * calculation of the AES-CMAC according to RFC-4493 over a given
 * message of arbitrary length.
 *
 * Depending on the total message length specified when
 * qapi_BLE_GAP_LE_Initialize_AES_CMAC_Operation() and the number
 * of bytes passed to here, this function may need to be called
 * several times until the entire message has been processed and
 * the final AES-CMAC result is available.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned
 *                                  to this Bluetooth Protocol
 *                                  Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in]   GapleAesCmacContext Pointer to the AES-CMAC context.
 *
 * @param[in]   BlockLength         Number of bytes pointed to by
 *                                  BlockData pointer.
 *
 * @param[in]   BlockData           Pointer to message data to
 *                                  process.
 *
 * @param[out]   MACResult          Pointer to return the AES-CMAC
 *                                  result (check return value to
 *                                  see if result is available).
 *
 * @return
 * ret_val > 0 -- Success, MACResult contains the
 *                AES-CMAC result.\n
 * ret_val = 0 -- Success, more data needed before
 *                final value is available.\n
 * ret_val < 0 -- Failure
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_GAP_LE_Perform_AES_CMAC_Operation(uint32_t BluetoothStackID, void *GapleAesCmacContext, uint32_t BlockLength, uint8_t *BlockData, qapi_BLE_Encryption_Key_t *MACResult);

/**
 * @brief
 * Decrypts a given encrypted message.
 *
 * @details
 * The following function decrypts the specified encrypted message
 * in place using AES-128-CCM.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned
 *                                  to this Bluetooth Protocol
 *                                  Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in,out] DecryptionParameters Pointer to the data needed for decryption.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_ble_GAP_LE_AES_CCM_Decrypt(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_t *DecryptionParameters);

/**
 * @brief
 * Encrypts a given plaintext message.
 *
 * @details
 * The following function encrypts the specified plaintext message
 * in place using AES-128-CCM.
 *
 * @param[in]   BluetoothStackID    Unique identifier assigned
 *                                  to this Bluetooth Protocol
 *                                  Stack via a call to
 *                                  qapi_BLE_BSC_Initialize().
 *
 * @param[in,out] EncryptionParameters Pointer to the data needed for encryption.
 *
 * @return
 * Zero -- If successful.\n
 * Bluetopia Error code -- If negative; a Bluetopia
                error code (QAPI_BLE_BTPS_ERROR_XXX) is returned.
                Bluetopia error codes can be found in qapi_ble_errors.h.
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_ble_GAP_LE_AES_CCM_Encrypt(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_t *EncryptionParameters);

/** @} */ /* end_addtogroup qapi_ble_core_gaple */

#endif

