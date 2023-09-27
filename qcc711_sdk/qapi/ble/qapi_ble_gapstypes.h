/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_GAPS_TYPE_H__
#define __QAPI_BLE_GAPS_TYPE_H__

#include "./qapi_ble_bttypes.h"      /* Bluetooth Type Definitions.     */

   /* The following defines the maximum allowable GAP Device Name.      */
#define QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH                                     (248)

   /* The following MACRO is a utility MACRO that assigns the Generic   */
   /* Access Profile Service 16 bit UUID to the specified               */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* GAP UUID Constant value.                                          */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_GAP_SERVICE_UUID_16(_x)                                 QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x18, 0x00)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Service UUID in UUID16 form.  This     */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the GAP Service UUID (MACRO returns boolean result) NOT  */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the GAP Service UUID.   */
#define QAPI_BLE_GAP_COMPARE_GAP_SERVICE_UUID_TO_UUID_16(_x)                        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x18, 0x00)

   /* The following defines the GAP Service UUID that is used when      */
   /* building the GAPS Service Table.                                  */
#define QAPI_BLE_GAP_SERVICE_BLUETOOTH_UUID_CONSTANT                                { 0x00, 0x18 }

   /* The following MACRO is a utility MACRO that assigns the GAP Device*/
   /* Name Characteristic 16 bit UUID to the specified                  */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* GAP Device Name UUID Constant value.                              */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_DEVICE_NAME_UUID16(_x)                                  QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x00)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Device Name UUID in UUID16 form.  This */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the GAP Device Name UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GAP Device Name     */
   /* UUID.                                                             */
#define QAPI_BLE_GAP_COMPARE_GAP_DEVICE_NAME_UUID_TO_UUID_16(_x)                    QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x00)

   /* The following defines the GAP Device Name Characteristic UUID that*/
   /* is used when building the GAP Service Table.                      */
#define QAPI_BLE_GAP_DEVICE_NAME_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT             { 0x00, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Service Device Appearance Characteristic 16 bit UUID to the       */
   /* specified qapi_BLE_UUID_16_t variable.  This MACRO accepts one    */
   /* parameter accepts one parameter which is the qapi_BLE_UUID_16_t   */
   /* variable that is to receive the GAP Characteristic UUID Constant  */
   /* value.                                                            */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_DEVICE_APPEARANCE_UUID16(_x)                            QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x01)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Device Appearance UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the GAP Device Appearance UUID (MACRO returns boolean    */
   /* result) NOT less than/greater than.  The first parameter is the   */
   /* qapi_BLE_UUID_16_t variable to compare to the GAP Device          */
   /* Appearance UUID.                                                  */
#define QAPI_BLE_GAP_COMPARE_GAP_DEVICE_APPEARANCE_UUID_TO_UUID_16(_x)              QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x01)

   /* The following defines the GAP Device Appearance Characteristic    */
   /* UUID that is used when building the GAP Service Table.            */
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT       { 0x01, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Peripheral Privacy Flag Characteristic 16 bit UUID to the         */
   /* specified qapi_BLE_UUID_16_t variable.  This MACRO accepts one    */
   /* parameter accepts one parameter which is the qapi_BLE_UUID_16_t   */
   /* variable that is to receive the GAP Peripheral Privacy Flag UUID  */
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_PERIPHERAL_PRIVACY_FLAG_UUID16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x02)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Peripheral Privacy Flag UUID in UUID16 */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the GAP Peripheral Privacy Flag UUID (MACRO  */
   /* returns boolean result) NOT less than/greater than.  The first    */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the GAP*/
   /* Peripheral Privacy Flag UUID.                                     */
#define QAPI_BLE_GAP_COMPARE_GAP_PERIPHERAL_PRIVACY_FLAG_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x02)

   /* The following defines the GAP Peripheral Privacy Flag             */
   /* Characteristic UUID that is used when building the GAP Service    */
   /* Table.                                                            */
#define QAPI_BLE_GAP_PERIPHERAL_PRIVACY_FLAG_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x02, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Service Reconnection Address Characteristic 16 bit UUID to the    */
   /* specified qapi_BLE_UUID_16_t variable.  This MACRO accepts one    */
   /* parameter accepts one parameter which is the qapi_BLE_UUID_16_t   */
   /* variable that is to receive the GAP Reconnection Address UUID     */
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_RECONNECTION_ADDRESS_UUID16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x03)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Reconnection Address UUID in UUID16    */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the GAP Reconnection Address UUID (MACRO     */
   /* returns boolean result) NOT less than/greater than.  The first    */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the GAP*/
   /* Reconnection Address UUID.                                        */
#define QAPI_BLE_GAP_COMPARE_GAP_RECONNECTION_ADDRESS_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x03)

   /* The following defines the GAP Reconnection Address Characteristic */
   /* UUID that is used when building the GAP Service Table.            */
#define QAPI_BLE_GAP_RECONNECTION_ADDRESS_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x03, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Peripheral Preferred Connection Parameters Characteristic 16 bit  */
   /* UUID to the specified qapi_BLE_UUID_16_t variable.  This MACRO    */
   /* accepts one parameter which is the qapi_BLE_UUID_16_t variable    */
   /* that is to receive the GAP Peripheral Preferred Connection        */
   /* Parameters UUID Constant value.                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID16(_x)               QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x04)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Peripheral Preferred Connection        */
   /* Parameters UUID in UUID16 form.  This MACRO only returns whether  */
   /* the qapi_BLE_UUID_16_t variable is equal to the GAP Peripheral    */
   /* Preferred Connection Parameters UUID (MACRO returns boolean       */
   /* result) NOT less than/greater than.  The first parameter is the   */
   /* qapi_BLE_UUID_16_t variable to compare to the GAP Peripheral      */
   /* Preferred Connection Parameters UUID.                             */
#define QAPI_BLE_GAP_COMPARE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_UUID_TO_UUID_16(_x) QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x04)

   /* The following defines the GAP Peripheral Preferred Connection     */
   /* Parameters UUID that is used when building the GAP Service Table. */
#define QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x04, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Central Address Resolution Characteristic 16 bit UUID to the      */
   /* specified qapi_BLE_UUID_16_t variable.  This MACRO accepts one    */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the GAP Central Address Resolution UUID Constant value.   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_CENTRAL_ADDRESS_RESOLUTION_UUID16(_x) QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0xA6)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Central Address Resolution UUID in     */
   /* UUID16 form.  This MACRO only returns whether the                 */
   /* qapi_BLE_UUID_16_t variable is equal to the GAP Central Address   */
   /* Resolution UUID (MACRO returns boolean result) NOT less           */
   /* than/greater than.  The first parameter is the qapi_BLE_UUID_16_t */
   /* variable to compare to the GAP Central Address Resolution UUID.   */
#define QAPI_BLE_GAP_COMPARE_GAP_CENTRAL_ADDRESS_RESOLUTION_UUID_TO_UUID_16(_x) QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0xA6)

   /* The following defines the GAP Central Address Resolution UUID that*/
   /* is used when building the GAP Service Table.                      */
#define QAPI_BLE_GAP_CENTRAL_ADDRESS_RESOLUTION_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0xA6, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the GAP       */
   /* Resolvable Private Address only Characteristic 16 bit UUID to the */
   /* specified qapi_BLE_UUID_16_t variable. This MACRO accepts one     */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the GAP Resolvable Private Address UUID Constant value.   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_GAP_ASSIGN_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID16(_x) QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0xC9)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GAP Resolvable Private Address UUID in     */
   /* UUID16 form. This MACRO only returns whether the                  */
   /* qapi_BLE_UUID_16_t variable is equal to the GAP Resolvable Private*/
   /* Address UUID (MACRO returns boolean result) NOT less than/greater */
   /* than. The first parameter is the qapi_BLE_UUID_16_t variable to   */
   /* compare to the GAP Central Address Resolution UUID.               */
#define QAPI_BLE_GAP_COMPARE_GAP_RESOLVABLE_PRIVATE_ADDRESS_ONLY_UUID_TO_UUID_16(_x) QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0xC9)

   /* The following defines the GAP Resolvable Private Address UUID that*/
   /* is used when building the GAP Service Table.                      */
#define QAPI_BLE_GAP_RESOLVABLE_PRIVATE_ADDRESS_ONLY_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0xC9, 0x2A }

   /* The following MACRO is a utility MACRO that is used to validate   */
   /* the length of a Write into the Device Name Characteristic (if it  */
   /* is writable).  The only parameter to this MACRO is the length of  */
   /* the Value that is being written.                                  */
#define QAPI_BLE_GAP_DEVICE_NAME_VALID_LENGTH(_x)                 ((((uint16_t)(_x)) >= 0) && (((uint16_t)(_x)) <= QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH))

   /* The following defines the valid Device Appearance Characteristic  */
   /* Value Length.                                                     */
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_LENGTH               (sizeof(uint16_t))

   /* The following define the value GAP Device Appearance Values.      */
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_UNKNOWN                                                        0
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_PHONE                                                  64
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_COMPUTER                                               128
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_WATCH                                                  192
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_SPORTS_WATCH                                                   193
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_CLOCK                                                  256
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_DISPLAY                                                320
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_GENERIC_REMOTE_CONTROL                                 384
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_EYE_GLASSES                                            448
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_TAG                                                    512
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_KEYRING                                                576
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_MEDIA_PLAYER                                           640
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_BARCODE_SCANNER                                        704
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_THERMOMETER                                            768
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_THERMOMETER_EAR                                                769
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_HEART_RATE_SENSOR                                      832
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BELT_HEART_RATE_SENSOR                                         833
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_BLOOD_PRESSURE                                         896
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BLOOD_PRESSURE_ARM                                             897
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_BLOOD_PRESSURE_WRIST                                           898
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HUMAN_INTERFACE_DEVICE                                         960
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_KEYBOARD                                                   961
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_MOUSE                                                      962
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_JOYSTICK                                                   963
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_GAMEPAD                                                    964
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_DIGITIZER_TABLET                                           965
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_CARD_READER                                                966
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_DIGITAL_PEN                                                967
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_HID_BARCODE_SCANNER                                            968
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_GLUCOSE_METER                                          1024
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_RUNNING_WALKING_SENSOR                                 1088
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_RUNNING_WALKING_SENSOR_IN_SHOE                                 1089
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_RUNNING_WALKING_SENSOR_ON_SHOE                                 1090
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_RUNNING_WALKING_SENSOR_ON_HIP                                  1091
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_CYCLING                                                1152
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_CYCLING_CYCLING_COMPUTER                                       1153
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_CYCLING_SPEED_SENSOR                                           1154
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_CYCLING_CADENCE_SENSOR                                         1155
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_CYCLING_POWER_SENSOR                                           1156
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_CYCLING_SPEED_AND_CADENCE_SENSOR                               1157
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_PULSE_OXIMETER                                         3136
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_PULSE_OXIMETER_FINGERTIP                                       3137
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_PULSE_OXIMETER_WRIST_WORN                                      3138
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_WEIGHT_SCALE                                           3200
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_GENERIC_OUTDOOR_SPORTS_ACTIVITY                                5184
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_OUTDOOR_SPORTS_ACTIVITY_LOCATION_DISPLAY_DEVICE                5185
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_OUTDOOR_SPORTS_ACTIVITY_LOCATION_AND_NAVIGATION_DISPLAY_DEVICE 5186
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_OUTDOOR_SPORTS_ACTIVITY_LOCATION_POD                           5187
#define QAPI_BLE_GAP_DEVICE_APPEARANCE_VALUE_OUTDOOR_SPORTS_ACTIVITY_LOCATION_AND_NAVIGATION_POD            5188

   /* The following define the valid values for the Central Address     */
   /* Resolution characteristic (it is not a bit mask).                 */
#define QAPI_BLE_GAP_CENTRAL_ADDRESS_RESOLUTION_VALUE_ADDRESS_RESOLUTION_NOT_SUPPORTED    0x00
#define QAPI_BLE_GAP_CENTRAL_ADDRESS_RESOLUTION_VALUE_ADDRESS_RESOLUTION_SUPPORTED        0x01

   /* The following define the valid values for the Resolvable Private  */
   /* Address Only characteristic (it is not a bit mask).               */
#define QAPI_BLE_GAP_RESOLVABLE_PRIVATE_ADDRESS_ONLY                                      0x00

   /* The following structure represents the format of the GAP          */
   /* Peripheral Preferred Connection Parameters characteristic.        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GAP_Peripheral_Preferred_Connection_Parameters_s
{
   qapi_BLE_NonAlignedWord_t Minimum_Connection_Interval;
   qapi_BLE_NonAlignedWord_t Maximum_Connection_Interval;
   qapi_BLE_NonAlignedWord_t Slave_Latency;
   qapi_BLE_NonAlignedWord_t Supervision_Timeout_Multiplier;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GAP_Peripheral_Preferred_Connection_Parameters_t;

#define QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_DATA_SIZE   (sizeof(qapi_BLE_GAP_Peripheral_Preferred_Connection_Parameters_t))

#define QAPI_BLE_GAP_PERIPHERAL_PREFERRED_CONNECTION_PARAMETERS_NO_SPECIFIC_PREFERRED  0xFFFF

#endif
