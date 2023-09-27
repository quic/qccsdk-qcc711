/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_DIS_TYPES_H__
#define __QAPI_BLE_DIS_TYPES_H__

#include "./qapi_ble_bttypes.h" /* Bluetooth Type Definitions.                */

   /* The following MACRO is a utility MACRO that assigns the Device    */
   /* Information Service 16 bit UUID to the specified                  */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is a pointer to a qapi_BLE_UUID_16_t variable that is to    */
   /* receive the DIS UUID Constant value.                              */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_DIS_SERVICE_UUID_16(_x)                           QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16(*((qapi_BLE_UUID_16_t *)(_x)), 0x18, 0x0A)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Service UUID in UUID16 form.  This     */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the DIS Service UUID (MACRO returns boolean result) NOT  */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Service UUID.   */
#define QAPI_BLE_DIS_COMPARE_DIS_SERVICE_UUID_TO_UUID_16(_x)                  QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x18, 0x0A)

   /* The following defines the Device Information Service UUID that is */
   /* used when building the DIS Service Table.                         */
#define QAPI_BLE_DIS_SERVICE_BLUETOOTH_UUID_CONSTANT                          { 0x0A, 0x18 }

   /* The following MACRO is a utility MACRO that assigns the DIS       */
   /* Manufacturer Name Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Manufacturer Name UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_MANUFACTURER_NAME_UUID_16(_x)                     QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x29)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Manufacturer Name UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Manufacturer Name UUID (MACRO returns boolean result)*/
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Manufacturer    */
   /* Name UUID.                                                        */
#define QAPI_BLE_DIS_COMPARE_DIS_MANUFACTURER_NAME_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x29)

   /* The following defines the DIS Manufacturer Name Characteristic    */
   /* UUID that is used when building the DIS Service Table.            */
#define QAPI_BLE_DIS_MANUFACTURER_NAME_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x29, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS Model */
   /* Number Characteristic 16 bit UUID to the specified                */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Model Number UUID Constant value.                             */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_MODEL_NUMBER_UUID_16(_x)                          QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x24)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Model Number UUID in UUID16 form.  This*/
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the Model Number UUID (MACRO returns boolean result) NOT */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Model Number    */
   /* UUID.                                                             */
#define QAPI_BLE_DIS_COMPARE_DIS_MODEL_NUMBER_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x24)

   /* The following defines the DIS Model Number Characteristic UUID    */
   /* that is used when building the DIS Service Table.                 */
#define QAPI_BLE_DIS_MODEL_NUMBER_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT      { 0x24, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS Serial*/
   /* Number Characteristic 16 bit UUID to the specified                */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Serial Number UUID Constant value.                            */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_SERIAL_NUMBER_UUID_16(_x)                         QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x25)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Serial Number UUID in UUID16 form.     */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Serial Number UUID (MACRO returns boolean result) NOT*/
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Serial Number   */
   /* UUID.                                                             */
#define QAPI_BLE_DIS_COMPARE_DIS_SERIAL_NUMBER_UUID_TO_UUID_16(_x)            QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x25)

   /* The following defines the DIS Serial Number Characteristic UUID   */
   /* that is used when building the DIS Service Table.                 */
#define QAPI_BLE_DIS_SERIAL_NUMBER_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT     { 0x25, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS       */
   /* Hardware Revision Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Hardware Revision UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_HARDWARE_REVISION_UUID_16(_x)                     QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x27)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Hardware Revision UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Hardware Revision UUID (MACRO returns boolean result)*/
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Hardware        */
   /* Revision UUID.                                                    */
#define QAPI_BLE_DIS_COMPARE_DIS_HARDWARE_REVISION_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x27)

   /* The following defines the DIS Hardware Revision Characteristic    */
   /* UUID that is used when building the DIS Service Table.            */
#define QAPI_BLE_DIS_HARDWARE_REVISION_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x27, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS       */
   /* Firmware Revision Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Firmware Revision UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_FIRMWARE_REVISION_UUID_16(_x)                     QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x26)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Firmware Revision UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Firmware Revision UUID (MACRO returns boolean result)*/
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Firmware        */
   /* Revision UUID.                                                    */
#define QAPI_BLE_DIS_COMPARE_DIS_FIRMWARE_REVISION_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x26)

   /* The following defines the DIS Firmware Revision Characteristic    */
   /* UUID that is used when building the DIS Service Table.            */
#define QAPI_BLE_DIS_FIRMWARE_REVISION_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x26, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS       */
   /* Software Revision Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS Software Revision UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_SOFTWARE_REVISION_UUID_16(_x)                     QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x28)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS Software Revision UUID in UUID16 form. */
   /* This MACRO only returns whether the qapi_BLE_UUID_16_t variable is*/
   /* equal to the Software Revision UUID (MACRO returns boolean result)*/
   /* NOT less than/greater than.  The first parameter is the           */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS Software        */
   /* Revision UUID.                                                    */
#define QAPI_BLE_DIS_COMPARE_DIS_SOFTWARE_REVISION_UUID_TO_UUID_16(_x)        QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x28)

   /* The following defines the DIS Software Revision Characteristic    */
   /* UUID that is used when building the DIS Service Table.            */
#define QAPI_BLE_DIS_SOFTWARE_REVISION_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x28, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS System*/
   /* ID Characteristic 16 bit UUID to the specified qapi_BLE_UUID_16_t */
   /* variable.  This MACRO accepts one parameter which is the          */
   /* qapi_BLE_UUID_16_t variable that is to receive the DIS System ID  */
   /* UUID Constant value.                                              */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_SYSTEM_ID_UUID_16(_x)                             QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x23)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS System ID UUID in UUID16 form.  This   */
   /* MACRO only returns whether the qapi_BLE_UUID_16_t variable is     */
   /* equal to the System ID UUID (MACRO returns boolean result) NOT    */
   /* less than/greater than.  The first parameter is the               */
   /* qapi_BLE_UUID_16_t variable to compare to the DIS System ID UUID. */
#define QAPI_BLE_DIS_COMPARE_DIS_SYSTEM_ID_UUID_TO_UUID_16(_x)                QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x23)

   /* The following defines the DIS System ID Characteristic UUID that  */
   /* is used when building the DIS Service Table.                      */
#define QAPI_BLE_DIS_SYSTEM_ID_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT         { 0x23, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS IEEE  */
   /* Certification Data Characteristic 16 bit UUID to the specified    */
   /* qapi_BLE_UUID_16_t variable.  This MACRO accepts one parameter    */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* DIS IEEE Certification Data UUID Constant value.                  */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_IEEE_CERTIFICATION_DATA_UUID_16(_x)               QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x2A)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS IEEE Certification Data UUID in UUID16 */
   /* form.  This MACRO only returns whether the qapi_BLE_UUID_16_t     */
   /* variable is equal to the IEEE Certification Data UUID (MACRO      */
   /* returns boolean result) NOT less than/greater than.  The first    */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the DIS*/
   /* IEEE Certification Data UUID.                                     */
#define QAPI_BLE_DIS_COMPARE_DIS_IEEE_CERTIFICATION_DATA_UUID_TO_UUID_16(_x)  QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x2A)

   /* The following defines the DIS IEEE Certification Data             */
   /* Characteristic UUID that is used when building the DIS Service    */
   /* Table.                                                            */
#define QAPI_BLE_DIS_IEEE_CERTIFICATION_DATA_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT { 0x2A, 0x2A }

   /* The following MACRO is a utility MACRO that assigns the DIS PnP ID*/
   /* Characteristic 16 bit UUID to the specified qapi_BLE_UUID_16_t    */
   /* variable.  This MACRO accepts one parameter which is the          */
   /* qapi_BLE_UUID_16_t variable that is to receive the DIS PnP ID UUID*/
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_DIS_ASSIGN_PNP_ID_UUID_16(_x)                                QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2A, 0x50)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined DIS PnP ID UUID in UUID16 form.  This MACRO*/
   /* only returns whether the qapi_BLE_UUID_16_t variable is equal to  */
   /* the PnP ID UUID (MACRO returns boolean result) NOT less           */
   /* than/greater than.  The first parameter is the qapi_BLE_UUID_16_t */
   /* variable to compare to the PnP ID Data UUID.                      */
#define QAPI_BLE_DIS_COMPARE_DIS_PNP_ID_UUID_TO_UUID_16(_x)                   QAPI_BLE_COMPARE_BLUETOOTH_UUID_16_TO_CONSTANT((_x), 0x2A, 0x50)

   /* The following defines the DIS PnP ID Characteristic UUID that is  */
   /* used when building the DIS Service Table.                         */
#define QAPI_BLE_DIS_PNP_ID_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT            { 0x50, 0x2A }

   /* The following structure defines the format of the System ID       */
   /* characteristic value.  The OUI is the IEEE defined                */
   /* Organizationally Unique Identifier.  The Manufacturer Identifier  */
   /* is a manufacturer defined value.  Both fields are Little-Endian.  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_DIS_System_ID_Value_s
{
   qapi_BLE_NonAlignedByte_t Manufacturer_Identifier[5];
   qapi_BLE_NonAlignedByte_t Organizationally_Unique_Identifier[3];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_DIS_System_ID_Value_t;

#define QAPI_BLE_DIS_SYSTEM_ID_VALUE_DATA_SIZE                          (sizeof(qapi_BLE_DIS_System_ID_Value_t))

   /* The following structure defines the format of the PNP ID          */
   /* characteristic value.  The VendorID Source is a value that        */
   /* describes who assigned the following VendorID.  The VendorID      */
   /* identifies the vendor from the source described in the VendorID   */
   /* Source.  The ProductID is a vendor maintained product ID.  The    */
   /* ProductVersion is a vendor mainted product version.               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_DIS_PNP_ID_Value_s
{
   qapi_BLE_NonAlignedByte_t VendorID_Source;
   qapi_BLE_NonAlignedWord_t VendorID;
   qapi_BLE_NonAlignedWord_t ProductID;
   qapi_BLE_NonAlignedWord_t ProductVersion;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_DIS_PNP_ID_Value_t;

#define QAPI_BLE_DIS_PNP_ID_VALUE_DATA_SIZE                             (sizeof(qapi_BLE_DIS_PNP_ID_Value_t))

   /* The following values define the valid values that the Vendor ID   */
   /* Source field of the DIS PNP characteristic may contain.           */
#define QAPI_BLE_DIS_PNP_ID_VENDOR_SOURCE_BLUETOOTH_SIG                 0x01
#define QAPI_BLE_DIS_PNP_ID_VENDOR_SOURCE_USB_IMPLEMENTORS_FORUM        0x02

#endif
