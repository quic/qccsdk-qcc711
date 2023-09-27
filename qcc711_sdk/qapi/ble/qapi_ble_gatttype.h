/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_GATT_TYPE_H__
#define __QAPI_BLE_GATT_TYPE_H__

#include "./qapi_ble_bttypes.h" /* Bluetooth Type Definitions.                */

   /* UUID Comparison Utility Macros.                                   */

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_UUID_16_t variables.  This MACRO only  */
   /* returns whether the two qapi_BLE_UUID_16_t variables are equal    */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter the the qapi_BLE_UUID_16_t variable.  The next two*/
   /* are the individual byte values to do the comparison with.  The    */
   /* bytes are NOT in Little Endian Format.                            */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT(_x, _a, _b) \
(                                                         \
   ((_x).UUID_Byte1 == (_a)) && ((_x).UUID_Byte0 == (_b)) \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_UUID_128_t variables.  This MACRO only */
   /* returns whether the two qapi_BLE_UUID_128_t variables are equal   */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter this MACRO is of type qapi_BLE_UUID_128_t         */
   /* represents the qapi_BLE_UUID_128_t variable to compare.  The next */
   /* parameters are the constant UUID bytes to do the comparison with. */
   /* The individual bytes are NOT in Little Endian Format.             */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT(_x, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
(                                                                                                                  \
   ((_x).UUID_Byte0  == (_p)) && ((_x).UUID_Byte1  == (_o)) && ((_x).UUID_Byte2  == (_n)) &&                       \
   ((_x).UUID_Byte3  == (_m)) && ((_x).UUID_Byte4  == (_l)) && ((_x).UUID_Byte5  == (_k)) &&                       \
   ((_x).UUID_Byte6  == (_j)) && ((_x).UUID_Byte7  == (_i)) && ((_x).UUID_Byte8  == (_h)) &&                       \
   ((_x).UUID_Byte9  == (_g)) && ((_x).UUID_Byte10 == (_f)) && ((_x).UUID_Byte11 == (_e)) &&                       \
   ((_x).UUID_Byte12 == (_d)) && ((_x).UUID_Byte13 == (_c)) && ((_x).UUID_Byte14 == (_b)) &&                       \
   ((_x).UUID_Byte15 == (_a))                                                                                      \
)

   /* GATT BASE_UUID.                                                   */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Bluetooth Base Universally Unique Identifier (BASE_UUID) to the   */
   /* specified qapi_BLE_UUID_128_t variable.  This MACRO accepts one   */
   /* parameter which is the qapi_BLE_UUID_128_t variable that is       */
   /* receive the BASE_UUID Constant value.                             */
#define QAPI_BLE_GATT_ASSIGN_BASE_UUID(_x)                                                QAPI_BLE_ASSIGN_BLUETOOTH_UUID_128((_x), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* GATT Utility Macros.                                              */

   /* The following MACRO is a utility MACRO that exists to compare a   */
   /* qapi_BLE_UUID_16_t type constant to a qapi_BLE_UUID_128_t         */
   /* variable.  The first is the qapi_BLE_UUID_128_t variable to do the*/
   /* comparison with.  The next parameters are the individual bytes of */
   /* the qapi_BLE_UUID_16_t constant to compare to the                 */
   /* qapi_BLE_UUID_128_t variable.  This MACRO only returns whether or */
   /* not the two UUIDs are equal (MACRO returns Boolean result) NOT    */
   /* less than/greater than.                                           */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_16_CONSTANT(_x, _a, _b)               QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), 0x00, 0x00, _a, _b, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following MACRO is a utility MACRO that exists to compare a   */
   /* qapi_BLE_UUID_16_t variable to a qapi_BLE_UUID_128_t variable.    */
   /* The first is the qapi_BLE_UUID_128_t variable to do the comparison*/
   /* with.  The next parameter is the qapi_BLE_UUID_16_t variable.     */
   /* This MACRO only returns whether or not the two UUIDs are equal    */
   /* (MACRO returns Boolean result) NOT less than/greater than.        */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_BLUETOOTH_UUID_16(_x, _y)                  QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), 0x00, 0x00, (_y).UUID_Byte1, (_y).UUID_Byte0, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following MACRO is a utility MACRO that exists to compare a   */
   /* qapi_BLE_UUID_32_t type constant to a qapi_BLE_UUID_128_t         */
   /* variable.  The first is the qapi_BLE_UUID_128_t variable to do the*/
   /* comparison with.  The next parameters are the individual bytes of */
   /* the qapi_BLE_UUID_32_t constant to compare to the                 */
   /* qapi_BLE_UUID_128_t variable.  This MACRO only returns whether or */
   /* not the two UUIDs are equal (MACRO returns Boolean result) NOT    */
   /* less than/greater than.                                           */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_32_CONSTANT(_x, _a, _b, _c, _d)       QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), _a, _b, _c, _d, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following MACRO is a utility MACRO that exists to compare a   */
   /* qapi_BLE_UUID_32_t variable to a qapi_BLE_UUID_128_t variable.    */
   /* The first is the qapi_BLE_UUID_128_t variable to do the comparison*/
   /* with.  The next parameter is the qapi_BLE_UUID_32_t variable.     */
   /* This MACRO only returns whether or not the two UUIDs are equal    */
   /* (MACRO returns Boolean result) NOT less than/greater than.        */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_BLUETOOTH_UUID_32(_x, _y)                  QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), (_y).UUID_Byte3, (_y).UUID_Byte2, (_y).UUID_Byte1, (_y).UUID_Byte0, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following MACRO is a utility MACRO that exists to compare a   */
   /* qapi_BLE_UUID_128_t variable to the Bluetooth Base UUID.  The     */
   /* first is the qapi_BLE_UUID_128_t variable to do the comparison    */
   /* with.  This MACRO only returns whether or not the two UUIDs are   */
   /* equal (MACRO returns Boolean result) NOT less than/greater than.  */
#define QAPI_BLE_COMPARE_BLUETOOTH_UUID_TO_BLUETOOTH_BASE_UUID(_x)                        QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_CONSTANT((_x), (_x).UUID_Byte15, (_x).UUID_Byte14, (_x).UUID_Byte13, (_x).UUID_Byte12, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* GATT Attribute Types.                                             */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Primary Service Attribute Type.  This MACRO accepts one   */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO*/
   /* assigns the GATT Service UUID 16.                                 */
#define QAPI_BLE_GATT_ASSIGN_PRIMARY_SERVICE_ATTRIBUTE_TYPE(_x)                           QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x28, 0x00)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Primary Service UUID in UUID16 form.*/
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_PRIMARY_SERVICE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)     QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x28, 0x00)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Primary Service UUID in UUID16 form.*/
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_PRIMARY_SERVICE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_128(_x)    QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_16_CONSTANT((_x), 0x28, 0x00)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Secondary Service Attribute Type.  This MACRO accepts one */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO*/
   /* assigns the GATT Service UUID 16.                                 */
#define QAPI_BLE_GATT_ASSIGN_SECONDARY_SERVICE_ATTRIBUTE_TYPE(_x)                         QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x28, 0x01)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Secondary Service UUID in UUID16    */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the Primary Service UUID (MACRO returns      */
   /* boolean result) NOT less than/greater than.  The first parameter  */
   /* is the qapi_BLE_UUID_16_t variable to compare to the GATT Primary */
   /* Service UUID.                                                     */
#define QAPI_BLE_GATT_COMPARE_SECONDARY_SERVICE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)   QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x28, 0x01)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Secondary Service UUID in UUID16    */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the Primary Service UUID (MACRO returns      */
   /* boolean result) NOT less than/greater than.  The first parameter  */
   /* is the qapi_BLE_UUID_16_t variable to compare to the GATT Primary */
   /* Service UUID.                                                     */
#define QAPI_BLE_GATT_COMPARE_SECONDARY_SERVICE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_128(_x)  QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_16_CONSTANT((_x), 0x28, 0x01)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Include Attribute Type.  This MACRO accepts one parameter */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO assigns the*/
   /* GATT Service UUID 16.                                             */
#define QAPI_BLE_GATT_ASSIGN_INCLUDE_ATTRIBUTE_TYPE(_x)                                   QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x28, 0x02)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Include UUID in UUID16 form.  This  */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_INCLUDE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x28, 0x02)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Include UUID in UUID16 form.  This  */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_INCLUDE_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_128(_x)            QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_16_CONSTANT((_x), 0x28, 0x02)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Characteristic Attribute Type.  This MACRO accepts one    */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO*/
   /* assigns the GATT Service UUID 16.                                 */
#define QAPI_BLE_GATT_ASSIGN_CHARACTERISTIC_ATTRIBUTE_TYPE(_x)                            QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x28, 0x03)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)      QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x28, 0x03)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Primary Service UUID (MACRO returns boolean result)  */
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Primary Service*/
   /* UUID.                                                             */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_128(_x)     QAPI_BLE_COMPARE_BLUETOOTH_UUID_128_TO_UUID_16_CONSTANT((_x), 0x28, 0x03)

   /* GATT Characteristic Descriptor Attribute Types.                   */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Characteristic Extended Properties Attribute Type.  This  */
   /* MACRO accepts one parameter which is the qapi_BLE_UUID_16_t       */
   /* variable that is to receive the ATTRIBUTE_PROTOCOL_UUID_16        */
   /* Constant value.  This MACRO assigns the GATT Service UUID 16.     */
#define QAPI_BLE_GATT_ASSIGN_CHARACTERISTIC_EXTENDED_PROPERTIES_ATTRIBUTE_TYPE(_x)        QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x00)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic Extended Properties  */
   /* UUID in UUID16 form.  This MACRO only returns whether the         */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter is the qapi_BLE_UUID_16_t variable to compare to  */
   /* the GATT Primary Service UUID.                                    */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_EXTENDED_PROPERTIES_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)    QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x00)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Characteristic User Description Attribute Type.  This     */
   /* MACRO accepts one parameter which is the qapi_BLE_UUID_16_t       */
   /* variable that is to receive the ATTRIBUTE_PROTOCOL_UUID_16        */
   /* Constant value.  This MACRO assigns the GATT Service UUID 16.     */
#define QAPI_BLE_GATT_ASSIGN_CHARACTERISTIC_USER_DESCRIPTION_ATTRIBUTE_TYPE(_x)           QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x01)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic User Description UUID*/
   /* in UUID16 form.  This MACRO only returns whether the              */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter is the qapi_BLE_UUID_16_t variable to compare to  */
   /* the GATT Primary Service UUID.                                    */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_USER_DESCRIPTION_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)       QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x01)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Client Characteristic Configuration Attribute Type.  This */
   /* MACRO accepts one parameter which is the qapi_BLE_UUID_16_t       */
   /* variable that is to receive the ATTRIBUTE_PROTOCOL_UUID_16        */
   /* Constant value.  This MACRO assigns the GATT Service UUID 16.     */
#define QAPI_BLE_GATT_ASSIGN_CLIENT_CHARACTERISTIC_CONFIGURATION_ATTRIBUTE_TYPE(_x)       QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x02)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Client Characteristic Configuration */
   /* UUID in UUID16 form.  This MACRO only returns whether the         */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter is the qapi_BLE_UUID_16_t variable to compare to  */
   /* the GATT Primary Service UUID.                                    */
#define QAPI_BLE_GATT_COMPARE_CLIENT_CHARACTERISTIC_CONFIGURATION_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)   QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x02)

   /* The following defines the GATT Client Characteristic Configuration*/
   /* UUID that is used when building the service tables.               */
#define QAPI_BLE_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_BLUETOOTH_UUID_CONSTANT         { 0x02, 0x29 }

   /* The following defines the valid length of the GATT Client         */
   /* Characteristic Configuration descriptor.                          */
#define QAPI_BLE_GATT_CLIENT_CHARACTERISTIC_CONFIGURATION_LENGTH  (QAPI_BLE_NON_ALIGNED_WORD_SIZE)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Server Characteristic Configuration Attribute Type.  This */
   /* MACRO accepts one parameter which is the qapi_BLE_UUID_16_t       */
   /* variable that is to receive the ATTRIBUTE_PROTOCOL_UUID_16        */
   /* Constant value.  This MACRO assigns the GATT Service UUID 16.     */
#define QAPI_BLE_GATT_ASSIGN_SERVER_CHARACTERISTIC_CONFIGURATION_ATTRIBUTE_TYPE(_x)       QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x03)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Server Characteristic Configuration */
   /* UUID in UUID16 form.  This MACRO only returns whether the         */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter is the qapi_BLE_UUID_16_t variable to compare to  */
   /* the GATT Primary Service UUID.                                    */
#define QAPI_BLE_GATT_COMPARE_SERVER_CHARACTERISTIC_CONFIGURATION_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)   QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x03)

   /* The following defines the GATT Server Characteristic Configuration*/
   /* UUID that is used when building the service tables.               */
#define QAPI_BLE_GATT_SERVER_CHARACTERISTIC_CONFIGURATION_BLUETOOTH_UUID_CONSTANT         { 0x03, 0x29 }

   /* The following defines the valid length of the GATT Server         */
   /* Characteristic Configuration descriptor.                          */
#define QAPI_BLE_GATT_SERVER_CHARACTERISTIC_CONFIGURATION_LENGTH  (QAPI_BLE_NON_ALIGNED_WORD_SIZE)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Characteristic Format Attribute Type.  This MACRO accepts */
   /* one parameter which is the qapi_BLE_UUID_16_t variable that is to */
   /* receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO*/
   /* assigns the GATT Service UUID 16.                                 */
#define QAPI_BLE_GATT_ASSIGN_CHARACTERISTIC_PRESENTATION_FORMAT_ATTRIBUTE_TYPE(_x) QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x04)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic Format UUID UUID in  */
   /* UUID16 form.  This MACRO only returns whether the                 */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* first parameter is the qapi_BLE_UUID_16_t variable to compare to  */
   /* the GATT Primary Service UUID.                                    */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_PRESENTATION_FORMAT_ATTRIBUTE_TYPE_TO_UUID_16(_x) QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x04)

   /* The following defines the GATT Characteristic Presentation Format */
   /* Descriptor UUID that is used when building the service tables.    */
   /* * NOTE * The UUID MUST be assigned in Little-Endian format here.  */
#define QAPI_BLE_GATT_CHARACTERISTIC_PRESENTATION_FORMAT_BLUETOOTH_UUID_CONSTANT { 0x04, 0x29 }

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Characteristic Aggregate Format Attribute Type. This      */
   /* MACRO accepts one parameter which is the qapi_BLE_UUID_16_t variable that  */
   /* is to receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value. This */
   /* MACRO assigns the GATT Service UUID 16.                           */
#define QAPI_BLE_GATT_ASSIGN_CHARACTERISTIC_AGGREGATE_FORMAT_ATTRIBUTE_TYPE(_x)           QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x29, 0x05)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Characteristic Aggregate Format UUID*/
   /* UUID in UUID16 form. This MACRO only returns whether the          */
   /* qapi_BLE_UUID_16_t variable is equal to the Primary Service UUID (MACRO    */
   /* returns boolean result) NOT less than/greater than. The first     */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the GATT        */
   /* Primary Service UUID.                                             */
#define QAPI_BLE_GATT_COMPARE_CHARACTERISTIC_AGGREGATE_FORMAT_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)       QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x29, 0x05)

   /* GATT Service Types. (defined Service UUIDs).                      */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Service UUID.  This MACRO accepts one parameter which is the      */
   /* qapi_BLE_UUID_16_t variable that is to receive the GATT Service UUID.  This*/
   /* MACRO assigns the GATT Service UUID 16.                           */
#define QAPI_BLE_GATT_ASSIGN_GATT_SERVICE_UUID(_x)                                        QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x18, 0x01)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined GATT Service UUID in UUID16 form.  This    */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the NWAS Service UUID (MACRO returns boolean result) NOT */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the GATT Service UUID.  */
#define QAPI_BLE_GATT_COMPARE_GATT_SERVICE_UUID_TO_BLUETOOTH_UUID_16(_x)                  QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x18, 0x01)

   /* The following defines the GATT Service UUID that is used when     */
   /* building the GATT Service Table.                                  */
#define QAPI_BLE_GATT_SERVICE_BLUETOOTH_UUID_CONSTANT                                     { 0x01, 0x18 }

   /* GATT SDP UUID Types.                                              */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Service UUID (for use with SDP, which is Big Endian).  This MACRO */
   /* accepts one parameter which is the qapi_BLE_UUID_16_t variable    */
   /* that is to receive the GATT Service UUID (for SDP).  This MACRO   */
   /* assigns the GATT Service UUID 16 (in Big Endian format).          */
#define QAPI_BLE_SDP_ASSIGN_GATT_UUID_16(_x)                                              QAPI_BLE_ASSIGN_SDP_UUID_16((_x), 0x18, 0x01)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Service UUID (for use with SDP, which is Big Endian).  This MACRO */
   /* accepts one parameter which is the qapi_BLE_UUID_32_t variable    */
   /* that is to receive the GATT Service UUID (for SDP).  This MACRO   */
   /* assigns the GATT Service UUID 32 (in Big Endian format).          */
#define QAPI_BLE_SDP_ASSIGN_GATT_UUID_32(_x)                                              QAPI_BLE_ASSIGN_SDP_UUID_32((_x), 0x00, 0x00, 0x18, 0x01)

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Service UUID (for use with SDP, which is Big Endian).  This MACRO */
   /* accepts one parameter which is the qapi_BLE_UUID_128_t variable   */
   /* that is to receive the GATT Service UUID (for SDP).  This MACRO   */
   /* assigns the GATT Service UUID 128 (in Big Endian format).         */
#define QAPI_BLE_SDP_ASSIGN_GATT_UUID_128(_x)                                             QAPI_BLE_ASSIGN_SDP_UUID_128((_x), 0x00, 0x00, 0x18, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following MACRO is a utility MACRO that assigns the Attribute */
   /* Protocol UUID (for use with SDP, which is Big Endian).  This MACRO*/
   /* accepts one parameter which is the qapi_BLE_UUID_16_t variable    */
   /* that is to receive the Attribute Protocol UUID (for SDP).  This   */
   /* MACRO assigns the Attribute Protocol UUID 16 (in Big Endian       */
   /* format).                                                          */
#define QAPI_BLE_SDP_ASSIGN_ATT_UUID_16(_x)                                               QAPI_BLE_ASSIGN_SDP_UUID_16((_x), 0x00, 0x07)

   /* The following MACRO is a utility MACRO that assigns the Attribute */
   /* Protocol UUID (for use with SDP, which is Big Endian).  This MACRO*/
   /* accepts one parameter which is the qapi_BLE_UUID_32_t variable    */
   /* that is to receive the Attribute Protocol UUID (for SDP).  This   */
   /* MACRO assigns the Attribute Protocol UUID 32 (in Big Endian       */
   /* format).                                                          */
#define QAPI_BLE_SDP_ASSIGN_ATT_UUID_32(_x)                                               QAPI_BLE_ASSIGN_SDP_UUID_32((_x), 0x00, 0x00, 0x00, 0x07)

   /* The following MACRO is a utility MACRO that assigns the Attribute */
   /* Protocol UUID (for use with SDP, which is Big Endian).  This MACRO*/
   /* accepts one parameter which is the qapi_BLE_UUID_128_t variable   */
   /* that is to receive the Attribute Protocol UUID (for SDP).  This   */
   /* MACRO assigns the Attribute Protocol UUID 128 (in Big Endian      */
   /* format).                                                          */
#define QAPI_BLE_SDP_ASSIGN_ATT_UUID_128(_x)                                              QAPI_BLE_ASSIGN_SDP_UUID_128((_x), 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* GATT Characteristic Types. (defined Characteristic Value UUIDs).  */

   /* The following MACRO is a utility MACRO that assigns the GATT      */
   /* Profile Service Changed Attribute Type.  This MACRO accepts one   */
   /* parameter which is the qapi_BLE_UUID_16_t variable that is to     */
   /* receive the ATTRIBUTE_PROTOCOL_UUID_16 Constant value.  This MACRO*/
   /* assigns the GATT Service UUID 16.                                 */
#define QAPI_BLE_GATT_ASSIGN_SERVICE_CHANGED_ATTRIBUTE_TYPE(_x)                           QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x05)

   /* The following MACRO is a utility MACRO that exist to compare an   */
   /* Attribute Type to the defined Service Changed UUID UUID in UUID16 */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the Primary Service UUID (MACRO returns      */
   /* boolean result) NOT less than/greater than.  The first parameter  */
   /* is the qapi_BLE_UUID_16_t variable to compare to the GATT Primary */
   /* Service UUID.                                                     */
#define QAPI_BLE_GATT_COMPARE_SERVICE_CHANGED_ATTRIBUTE_TYPE_TO_BLUETOOTH_UUID_16(_x)     QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x05)

   /* The following defines the GATT Service Changed UUID that is used  */
   /* when building the GATT Service Table.                             */
#define QAPI_BLE_GATT_SERVICE_CHANGED_BLUETOOTH_UUID_CONSTANT                             { 0x05, 0x2A }

   /* GATT Characteristic Properties Definitions.                       */
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_BROADCAST                      0x01
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_READ                           0x02
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_WRITE_WITHOUT_RESPONSE         0x04
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_WRITE                          0x08
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_NOTIFY                         0x10
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_INDICATE                       0x20
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_AUTHENTICATED_SIGNED_WRITES    0x40
#define QAPI_BLE_GATT_CHARACTERISTIC_PROPERTIES_EXTENDED_PROPERTIES            0x80

   /* GATT Characteristic Extended Properties Definitions.              */
#define QAPI_BLE_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES_RELIABLE_WRITE        0x0001
#define QAPI_BLE_GATT_CHARACTERISTIC_EXTENDED_PROPERTIES_WRITABLE_AUXILARIES   0x0002

   /* GATT Client Configuration Characteristic Definitions.             */
#define QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_NOTIFY_ENABLE        0x0001
#define QAPI_BLE_GATT_CLIENT_CONFIGURATION_CHARACTERISTIC_INDICATE_ENABLE      0x0002

   /* GATT Server Configuration Characteristic Definitions.             */
#define QAPI_BLE_GATT_SERVER_CONFIGURATION_CHARACTERISTIC_BROADCAST_ENABLE     0x0001

   /* The following type definition defines the structure of the GATT   */
   /* Group Attribute Data structure.  This is used to map the          */
   /* AttributeDataList parameter data of the                           */
   /* qapi_BLE_ATT_Read_By_Group_Type_Response_PDU_t.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Group_Attribute_Data_s
{
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedWord_t EndGroupHandle;
   uint8_t           ServiceUUID[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Group_Attribute_Data_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a GATT Group Attribute Data structure.  The input        */
   /* parameter specifies the size in bytes of the UUID Value           */
#define QAPI_BLE_GATT_GROUP_ATTRIBUTE_DATA_SIZE(_x)               (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Group_Attribute_Data_t, ServiceUUID) + ((_x) * sizeof(uint8_t)))

   /* The following is a container structure that is used with the      */
   /* AttributeData member to specify an individual Attribute           */
   /* Handle/Value pair.                                                */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Handle_Value_Information_s
{
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   uint8_t                   AttributeData[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Handle_Value_Information_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format an individual Handle/Value Pair      */
   /* entry.  The input parameter specifies the length of the Attribute */
   /* Data (in bytes).  This MACRO calculates the total size required   */
   /* (in bytes) to hold the entire entry.                              */
#define QAPI_BLE_GATT_HANDLE_VALUE_INFORMATION_DATA_SIZE(_x)      (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Handle_Value_Information_t, AttributeData) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of the GATT   */
   /* Handle Information structure.  This is used to map the            */
   /* HandleInformation parameter data of the                           */
   /* qapi_BLE_ATT_Find_By_Type_Value_Response_PDU_t.                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Primary_Service_By_UUID_Entry_s
{
   qapi_BLE_NonAlignedWord_t StartingHandle;
   qapi_BLE_NonAlignedWord_t EndingHandle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Primary_Service_By_UUID_Entry_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a Primary Service Infromation structure.  The input      */
   /* parameter specifies the size in bytes of the UUID Value           */
#define QAPI_BLE_GATT_PRIMARY_SERVICE_BY_UUID_ENTRY_DATA_SIZE      (sizeof(qapi_BLE_GATT_Primary_Service_By_UUID_Entry_t))

   /* The following type definition defines the structure of the        */
   /* Included Service Information structure.  This is used to map the  */
   /* AttributeDataList parameter data of the                           */
   /* qapi_BLE_ATT_Read_By_Type_Response_PDU_t.                         */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Included_Service_Info_s
{
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedWord_t IncludedServiceHandle;
   qapi_BLE_NonAlignedWord_t EndGroupHandle;
   uint8_t                   ServiceUUID[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Included_Service_Info_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a Included Service Infromation structure.  The input     */
   /* parameter specifies the size in bytes of the UUID Value           */
#define QAPI_BLE_GATT_INCLUDED_SERVICE_INFO_DATA_SIZE(_x)         (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Included_Service_Info_t, ServiceUUID) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of the        */
   /* Included Service Value.                                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Included_Service_Value_s
{
   qapi_BLE_NonAlignedWord_t IncludedServiceHandle;
   qapi_BLE_NonAlignedWord_t EndGroupHandle;
   uint8_t                   ServiceUUID[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Included_Service_Value_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a Included Service Infromation structure.  The input     */
   /* parameter specifies the size in bytes of the UUID Value           */
#define QAPI_BLE_GATT_INCLUDED_SERVICE_VALUE_DATA_SIZE(_x)         (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Included_Service_Value_t, ServiceUUID) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of the        */
   /* Characteristic Value structure.                                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Characteristic_Declaration_Value_Field_s
{
   qapi_BLE_NonAlignedByte_t Properties;
   qapi_BLE_NonAlignedWord_t CharacteristicHandle;
   qapi_BLE_NonAlignedByte_t UUID[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Characteristic_Declaration_Value_Field_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a Characteristic Information structure.  The input       */
   /* parameter specifies the size in bytes of the UUID Value           */
#define QAPI_BLE_GATT_CHARACTERISTIC_DECLARATION_VALUE_FIELD_DATA_SIZE(_x) (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Characteristic_Declaration_Value_Field_t, UUID) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of the        */
   /* Characteristic Information structure.  This is used to map the    */
   /* AttributeDataList parameter data of the                           */
   /* qapi_BLE_ATT_Read_By_Type_Response_PDU_t.                         */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Characteristic_Info_s
{
   qapi_BLE_NonAlignedWord_t DeclarationHandle;
   qapi_BLE_NonAlignedByte_t Properties;
   qapi_BLE_NonAlignedWord_t CharacteristicHandle;
   qapi_BLE_NonAlignedByte_t UUID[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Characteristic_Info_t;

   /* The following is a utility MACRO provided to determine number of  */
   /* bytes of a Characteristic Infromation structure.  The input       */
   /* parameter specifies the size in bytes of the UUID Value           */
#define GATT_QAPI_BLE_CHARACTERISTIC_INFO_DATA_SIZE(_x)           (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_GATT_Characteristic_Info_t, UUID) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of the GATT   */
   /* Service Changed characteristic value.                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Service_Changed_Characteristic_Value_s
{
   qapi_BLE_NonAlignedWord_t Start_Handle;
   qapi_BLE_NonAlignedWord_t End_Handle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Service_Changed_Characteristic_Value_t;

#define QAPI_BLE_GATT_SERVICE_CHANGED_CHARACTERISTIC_VALUE_DATA_SIZE (sizeof(qapi_BLE_GATT_Service_Changed_Characteristic_Value_t))

   /* The following type definition defines the structure of the GATT   */
   /* Data Time Characteristic value.                                   */
   /* * NOTE * The assigned number for this format is 0x2A08.           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_GATT_Date_Time_Characteristic_s
{
   qapi_BLE_NonAlignedWord_t Year;
   qapi_BLE_NonAlignedByte_t Month;
   qapi_BLE_NonAlignedByte_t Day;
   qapi_BLE_NonAlignedByte_t Hours;
   qapi_BLE_NonAlignedByte_t Minutes;
   qapi_BLE_NonAlignedByte_t Seconds;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_GATT_Date_Time_Characteristic_t;

#define QAPI_BLE_GATT_DATE_TIME_CHARACTERISTIC_DATA_SIZE          (sizeof(qapi_BLE_GATT_Date_Time_Characteristic_t))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Year into a                             */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first    */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to assign the year from. */
   /* The second parameter is the Year to assign.                       */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_YEAR(_x, _y)               ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Year), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Year from a                            */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Year that was read from the structure.     */
#define QAPI_BLE_GATT_DATE_TIME_READ_YEAR(_x)                     READ_UNALIGNED_WORD_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Year))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Year value in a */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.  The */
   /* first parameter to this MACRO is the Year value to verify.  This  */
   /* MACRO returns a boolean value based upon whether or not the       */
   /* specified Year value is valid.  This MACRO returns a boolean TRUE */
   /* if the specified Year is valid, or a boolean FALSE if the         */
   /* specified Year value is invalid.                                  */
#define QAPI_BLE_GATT_DATE_TIME_VALID_YEAR(_x)                    ((!(_x))  || (((_x) >= 1582) && ((_x) <= 9999)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Month into a                            */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first    */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to assign the year from. */
   /* The second parameter is the Month to assign.                      */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_MONTH(_x, _y)               ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Month), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Month from a                           */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Month that was read from the structure.    */
#define QAPI_BLE_GATT_DATE_TIME_READ_MONTH(_x)                    READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Month))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Month value in a*/
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.  The */
   /* first parameter to this MACRO is the Month value to verify.  This */
   /* MACRO returns a boolean value based upon whether or not the       */
   /* specified Month value is valid.  This MACRO returns a boolean TRUE*/
   /* if the specified Month is valid, or a boolean FALSE if the        */
   /* specified Month value is invalid.                                 */
#define QAPI_BLE_GATT_DATE_TIME_VALID_MONTH(_x)                   ((!(_x))  || (((_x) >= 1) && ((_x) <= 12)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Day into a                              */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first    */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to assign the year from. */
   /* The second parameter is the Day to assign.                        */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_DAY(_x, _y)               ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Day), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Day from a                             */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Day that was read from the structure.      */
#define QAPI_BLE_GATT_DATE_TIME_READ_DAY(_x)                    READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Day))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Day value in a  */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.  The */
   /* first parameter to this MACRO is the Day value to verify.  This   */
   /* MACRO returns a boolean value based upon whether or not the       */
   /* specified Day value is valid.  This MACRO returns a boolean TRUE  */
   /* if the specified Day is valid, or a boolean FALSE if the specified*/
   /* Day value is invalid.                                             */
#define QAPI_BLE_GATT_DATE_TIME_VALID_DAY(_x)                     ((!(_x))  || (((_x) >= 1) && ((_x) <= 31)))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Hours into a                            */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first    */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to assign the year from. */
   /* The second parameter is the Hours to assign.                      */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_HOURS(_x, _y)              ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Hours), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Hours from a                           */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Hours that was read from the structure.    */
#define QAPI_BLE_GATT_DATE_TIME_READ_HOURS(_x)                    READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Hours))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Hours value in a*/
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.  The */
   /* first parameter to this MACRO is the Hours value to verify.  This */
   /* MACRO returns a boolean value based upon whether or not the       */
   /* specified Hours value is valid.  This MACRO returns a boolean TRUE*/
   /* if the specified Hours is valid, or a boolean FALSE if the        */
   /* specified Hours value is invalid.                                 */
#define QAPI_BLE_GATT_DATE_TIME_VALID_HOURS(_x)                   (((_x) >= 0) && ((_x) <= 23))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Minutes into a                          */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first parameter to*/
   /* this MACRO is a pointer to the qapi_BLE_GATT_Date_Time_Characteristic_t to */
   /* assign the year from.  The second parameter is the Minutes to     */
   /* assign.                                                           */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_MINUTES(_x, _y)            ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Minutes), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Minutes from a                         */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Minutes that was read from the structure.  */
#define QAPI_BLE_GATT_DATE_TIME_READ_MINUTES(_x)                  READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Minutes))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Minutes value in*/
   /* a qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.    */
   /* The first parameter to this MACRO is the Minutes value to verify. */
   /* This MACRO returns a boolean value based upon whether or not the  */
   /* specified Minutes value is valid.  This MACRO returns a boolean   */
   /* TRUE if the specified Minutes is valid, or a boolean FALSE if the */
   /* specified Minutes value is invalid.                               */
#define QAPI_BLE_GATT_DATE_TIME_VALID_MINUTES(_x)                 (((_x) >= 0) && ((_x) <= 59))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of assign the Seconds into a                          */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The first    */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to assign the year from. */
   /* The second parameter is the Seconds to assign.                    */
#define QAPI_BLE_GATT_DATE_TIME_ASSIGN_SECONDS(_x, _y)            ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Seconds), (_y))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of reading the Seconds from a                         */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t structure.  The only     */
   /* parameter to this MACRO is a pointer to the                       */
   /* qapi_BLE_GATT_Date_Time_Characteristic_t to read the year from.   */
   /* This MACRO returns the Seconds that was read from the structure.  */
#define QAPI_BLE_GATT_DATE_TIME_READ_SECONDS(_x)                  READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(((qapi_BLE_GATT_Date_Time_Characteristic_t *)(_x))->Seconds))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified Seconds value in*/
   /* a qapi_BLE_GATT_Date_Time_Characteristic_t structure is valid.    */
   /* The first parameter to this MACRO is the Seconds value to verify. */
   /* This MACRO returns a boolean value based upon whether or not the  */
   /* specified Seconds value is valid.  This MACRO returns a boolean   */
   /* TRUE if the specified Seconds is valid, or a boolean FALSE if the */
   /* specified Seconds value is invalid.                               */
#define QAPI_BLE_GATT_DATE_TIME_VALID_SECONDS(_x)                 (((_x) >= 0) && ((_x) <= 59))

#endif
