/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_BAS_TYPES_H__
#define __QAPI_BLE_BAS_TYPES_H__

#include "./qapi_ble_bttypes.h" /* Bluetooth Type Definitions.                */

   /* The following MACRO is a utility MACRO that assigns the Battery   */
   /* Service 16 bit UUID to the specified qapi_BLE_UUID_16_t variable. */
   /* This MACRO accepts one parameter which is a pointer to a          */
   /* qapi_BLE_UUID_16_t variable that is to receive the BAS UUID       */
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_BAS_ASSIGN_BAS_SERVICE_UUID_16(_x)               QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16(*((qapi_BLE_UUID_16_t *)(_x)), 0x18, 0x0F)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined BAS Service UUID in UUID16 form.  This     */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the BAS Service UUID (MACRO returns boolean result) NOT  */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the BAS Service UUID.   */
#define QAPI_BLE_BAS_COMPARE_BAS_SERVICE_UUID_TO_UUID_16(_x)      QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x18, 0x0F)

   /* The following defines the Battery Service UUID that is used       */
   /* when building the BAS Service Table.                              */
#define QAPI_BLE_BAS_SERVICE_BLUETOOTH_UUID_CONSTANT              { 0x0F, 0x18 }

   /* The following MACRO is a utility MACRO that assigns the BAS       */
   /* Battery Level Characteristic 16 bit UUID to the specified         */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* BAS Battery Level UUID Constant value.                            */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_BAS_ASSIGN_BATTERY_LEVEL_UUID_16(_x)                       QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x19)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined BAS Battery Level UUID in UUID16 form.     */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Battery Level UUID (MACRO returns boolean result) NOT*/
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the BAS Battery Level   */
   /* UUID.                                                             */
#define QAPI_BLE_BAS_COMPARE_BATTERY_LEVEL_UUID_TO_UUID_16(_x)              QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x19)

   /* The following defines the BAS Battery Level Characteristic UUID   */
   /* that is used when building the BAS Service Table.                 */
#define QAPI_BLE_BAS_BATTERY_LEVEL_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT   { 0x19, 0x2A }

   /* The following defines the valid range of Battery Level values that*/
   /* may be set as the value range for the Batter Level                */
   /* characteristic value.                                             */
#define QAPI_BLE_BAS_BATTERY_LEVEL_MIN_VALUE                      (0)
#define QAPI_BLE_BAS_BATTERY_LEVEL_MAX_VALUE                      (100)

   /* The following MACRO is a utility MACRO that exists to validate    */
   /* the specified Battery Level value is valid or not.The only        */
   /* parameter to this MACRO is the Battery Level to validate.         */
   /* This MACRO returns TRUE if the Battery Level is valid or FALSE    */
   /* otherwise.                                                        */
#define QAPI_BLE_BAS_VALID_BATTERY_LEVEL(_x)                      (((_x) >= QAPI_BLE_BAS_BATTERY_LEVEL_MIN_VALUE) && ((_x) <= QAPI_BLE_BAS_BATTERY_LEVEL_MAX_VALUE))

   /* The following defines the length of the Battery Level             */
   /* characteristic value.                                             */
#define QAPI_BLE_BAS_BATTERY_LEVEL_VALUE_LENGTH                   (sizeof(uint8_t))

   /* The following defines the BAS GATT Service Flags MASK that should */
   /* be passed into GATT_Register_Service when the BAS Service is      */
   /* registered.                                                       */
#define QAPI_BLE_BAS_SERVICE_FLAGS                                (QAPI_BLE_GATT_SERVICE_FLAGS_LE_SERVICE)

   /* The Characteristic Presentation Format descriptor defines the     */
   /* format of the Characteristic Value.  The Format field determines  */
   /* how a single value contained in the Characteristic Value is       */
   /* formatted.  The Exponent field is used with interger data types to*/
   /* determine how the Characteristic Value is furhter formatted.  The */
   /* actual value = Characteristic Value * 10^Exponent.  Unit specifies*/
   /* Unit of this attribute UUID The Name Space field is used to       */
   /* indentify the organization that is responsible for defining the   */
   /* enumerations for the description field.  The Description is an    */
   /* enumerated value from the organization identified by the Name     */
   /* Space field.                                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_BAS_Presentation_Format_s
{
  qapi_BLE_NonAlignedByte_t Format;
  qapi_BLE_NonAlignedByte_t Exponent;
  qapi_BLE_NonAlignedWord_t Unit;
  qapi_BLE_NonAlignedByte_t NameSpace;
  qapi_BLE_NonAlignedWord_t Description;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_BAS_Presentation_Format_t;

#define QAPI_BLE_BAS_PRESENTATION_FORMAT_SIZE                             (sizeof(qapi_BLE_BAS_Presentation_Format_t))

#endif
