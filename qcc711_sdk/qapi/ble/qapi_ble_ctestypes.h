/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_CTES_TYPES_H__
#define __QAPI_BLE_CTES_TYPES_H__

#include "./qapi_ble_bttypes.h" /* Bluetooth Type Definitions.                */

/** @addtogroup qapi_ble_services_ctes
@{ */

   /* The following defines the CTES Error Codes.                       */
#define QAPI_BLE_CTES_ERROR_CODE_SUCCESS                          0x00

   /* The following MACRO is a utility MACRO that assigns the CTE       */
   /* Service 16 bit UUID to the specified qapi_BLE_UUID_16_t variable. */
   /* This MACRO accepts one parameter which is the qapi_BLE_UUID_16_t  */
   /* variable that is to receive the CTE UUID Constant value.          */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_CTES_SERVICE_UUID_16(_x)             QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x18, 0x4A)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Service UUID in UUID16 form. This MACRO*/
   /* only returns whether the qapi_BLE_UUID_16_t variable is equal to  */
   /* the CTE Service UUID (MACRO returns boolean result) NOT less      */
   /* than/greater than. The first parameter is the qapi_BLE_UUID_16_t  */
   /* variable to compare to the CTE Service UUID.                      */
#define QAPI_BLE_CTES_COMPARE_CTES_SERVICE_UUID_TO_UUID_16(_x)    QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x18, 0x4A)

   /* The following defines the CTE Service UUID that is used           */
   /* when building the CTE Service Table.                              */
#define QAPI_BLE_CTES_SERVICE_BLUETOOTH_UUID_CONSTANT             { 0x4A, 0x18 }

   /* The following MACRO is a utility MACRO that assigns the CTE Enable*/
   /* Characteristic 16 bit UUID to the specified qapi_BLE_UUID_16_t    */
   /* variable. This MACRO accepts one parameter which is the           */
   /* qapi_BLE_UUID_16_t variable that is to receive the CTE Enable UUID*/
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_CTE_ENABLE_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xAD)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Constant Tone Extension Enable         */
   /* Characteristics UUID in UUID16 form. This MACRO only returns      */
   /* whether the qapi_BLE_UUID_16_t variable is equal to the Constant  */
   /* Tone Extension Enable Characteristics UUID (MACRO returns boolean */
   /* result) NOT less than/greater than. The first parameter is the    */
   /* qapi_BLE_UUID_16_t variable to compare to the CTE Enbale UUID.    */
#define QAPI_BLE_CTES_COMPARE_CTE_ENABLE_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xAD)

   /* The following defines the CTE Enable Characteristic UUID          */
   /* that is used when building the CTE Service Table.                 */
#define QAPI_BLE_CTES_CTE_ENABLE_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xAD, 0x2B }

   /* The following MACRO is a utility MACRO that assigns the CTE       */
   /* Minimum Length Characteristic 16 bit UUID to the specified        */
   /* qapi_BLE_UUID_16_t variable. This MACRO accepts one parameter     */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* CTE Minimum Length UUID Constant value.                           */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_CTE_MINIMUM_LENGTH_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xAE)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Minimum Length Characteristics UUID in */
   /* UUID16 form. This MACRO only returns whether the                  */
   /* qapi_BLE_UUID_16_t variable is equal to the CTE Minimum Length    */
   /* Characteristics UUID (MACRO returns boolean result) NOT less      */
   /* than/greater than. The first parameter is the qapi_BLE_UUID_16_t  */
   /* variable to compare to the CTE Minimum Length UUID.               */
#define QAPI_BLE_CTES_COMPARE_CTE_MINIMUM_LENGTH_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xAE)

   /* The following defines the CTE Minimum Length Characteristic UUID  */
   /* that is used when building the CTE Service Table.                 */
#define QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xAE, 0x2B }

   /* The following MACRO is a utility MACRO that assigns the CTE       */
   /* Transmit Duration Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable. This MACRO accepts one parameter     */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* CTE Transmit Duration UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xAF)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Transmit Duration Characteristics UUID */
   /* in UUID16 form. This MACRO only returns whether the               */
   /* qapi_BLE_UUID_16_t variable is equal to the CTE Transmit Duration */
   /* Characteristics UUID (MACRO returns boolean result) NOT less      */
   /* than/greater than. The first parameter is the qapi_BLE_UUID_16_t  */
   /* variable to compare to the CTE Transmit Duaration UUID.           */
#define QAPI_BLE_CTES_COMPARE_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xAF)

   /* The following defines the CTE Transmit Duration Characteristic    */
   /* UUID that is used when building the CTE Service Table.            */
#define QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xAF, 0x2B }

   /* The following MACRO is a utility MACRO that assigns the CTE       */
   /* Transmit Duration Characteristic 16 bit UUID to the specified     */
   /* qapi_BLE_UUID_16_t variable. This MACRO accepts one parameter     */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* CTE Transmit Duration UUID Constant value.                        */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_ADVERTISING_CTE_TRANSMIT_DURATION_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xB0)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Transmit Duration Characteristics UUID */
   /* in UUID16 form. This MACRO only returns whether the               */
   /* qapi_BLE_UUID_16_t variable is equal to the CTE Transmit Duration */
   /* Characteristics UUID (MACRO returns boolean result) NOT less      */
   /* than/greater than. The first parameter is the qapi_BLE_UUID_16_t  */
   /* variable to compare to the CTE Transmit Duaration UUID.           */
#define QAPI_BLE_CTES_COMPARE_ADVERTISING_CTE_TRANSMIT_DURATION_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xB0)

   /* The following defines the CTE Transmit Duration Characteristic    */
   /* UUID that is used when building the CTE Service Table.            */
#define QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xB0, 0x2B }

   /* The following MACRO is a utility MACRO that assigns the CTE       */
   /* Interval Characteristic 16 bit UUID to the specified              */
   /* qapi_BLE_UUID_16_t variable. This MACRO accepts one parameter     */
   /* which is the qapi_BLE_UUID_16_t variable that is to receive the   */
   /* CTE Interval UUID Constant value.                                 */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_ADVERTISING_CTE_INTERVAL_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xB1)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE Interval Characteristics UUID in UUID16*/
   /* form. This MACRO only returns whether the qapi_BLE_UUID_16_t      */
   /* variable is equal to the CTE Interval Characteristics UUID (MACRO */
   /* returns boolean result) NOT less than/greater than. The first     */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the CTE*/
   /* Interval UUID.                                                    */
#define QAPI_BLE_CTES_COMPARE_ADVERTISING_CTE_INTERVAL_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xB1)

   /* The following defines the CTE Interval Characteristic             */
   /* UUID that is used when building the CTE Service Table.            */
#define QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xB1, 0x2B }

   /* The following MACRO is a utility MACRO that assigns the CTE PHY   */
   /* Characteristic 16 bit UUID to the specified qapi_BLE_UUID_16_t    */
   /* variable. This MACRO accepts one parameter which is the           */
   /* qapi_BLE_UUID_16_t variable that is to receive the CTE PHY UUID   */
   /* Constant value.                                                   */
   /* * NOTE * The UUID will be assigned into the qapi_BLE_UUID_16_t    */
   /*          variable in Little-Endian format.                        */
#define QAPI_BLE_CTES_ASSIGN_ADVERTISING_CTE_PHY_UUID_16(_x)                      QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16((_x), 0x2B, 0xB2)

   /* The following MACRO is a utility MACRO that exist to compare a    */
   /* UUID 16 to the defined CTE PHY Characteristics UUID in UUID16     */
   /* form. This MACRO only returns whether the qapi_BLE_UUID_16_t      */
   /* variable is equal to the CTE PHY Characteristics UUID (MACRO      */
   /* returns boolean result) NOT less than/greater than. The first     */
   /* parameter is the qapi_BLE_UUID_16_t variable to compare to the CTE*/
   /* PHY UUID.                                                         */
#define QAPI_BLE_CTES_COMPARE_ADVERTISING_CTE_PHY_UUID_TO_UUID_16(_x)             QAPI_BLE_COMPARE_BLUETOOTH_qapi_BLE_UUID_16_tO_CONSTANT((_x), 0x2B, 0xB2)

   /* The following defines the CTE PHY Characteristic                  */
   /* UUID that is used when building the CTE Service Table.            */
#define QAPI_BLE_CTES_ADVERTISING_CTE_PHY_CHARACTERISTIC_BLUETOOTH_UUID_CONSTANT  { 0xB2, 0x2B }

   /* The following defines the valid CTE Enable bit mask values that   */
   /* may be set as the value for the CTE Enable characteristic value.  */
#define QAPI_BLE_CTES_CTE_ENABLE_AOA                              (0x01)
#define QAPI_BLE_CTES_CTE_ENABLE_AOD                              (0x02)

   /* The following defines the valid range of CTE minimum length values*/
   /* that may be set as the value range for the CTE minimum length     */
   /* characteristic value.                                             */
#define QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_MIN_VALUE                (2)
#define QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_MAX_VALUE                (20)

   /* The following MACRO is a utility MACRO that exists to validate    */
   /* the specified CTE minimum length is valid or not. The only        */
   /* parameter to this MACRO is the CTE minimum length to validate.    */
   /* This MACRO returns TRUE if the CTE minimum length is valid or     */
   /* FALSE otherwise.                                                  */
#define QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_VALID(_x)                (((_x) >=  QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_MIN_VALUE) && ((_x) <=  QAPI_BLE_CTES_CTE_MINIMUM_LENGTH_MAX_VALUE))

   /* The following defines the valid range of CTE minimum transmit     */
   /* count values that may be set as the value range for the CTE       */
   /* mininum transmit count characteristic value.                      */
#define QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_MIN_VALUE  (1)
#define QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_MAX_VALUE  (15)

   /* The following MACRO is a utility MACRO that exists to validate the*/
   /* specified CTE minimum transmit count is valid or not. The only    */
   /* parameter to this MACRO is the CTE transmit duration to validate. */
   /* This MACRO returns TRUE if the CTE transmit duration is valid or  */
   /* FALSE otherwise.                                                  */
#define QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_VALID(_x)  (((_x) >=  QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_MIN_VALUE) && ((_x) <=  QAPI_BLE_CTES_ADVERTISING_CTE_MINIMUM_TRANSMIT_COUNT_MAX_VALUE))

   /* The following defines the valid range of CTE transmit duration    */
   /* values that may be set as the value range for the CTE transmit    */
   /* duration characteristic value.                                    */
#define QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_MIN_VALUE  (0)
#define QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_MAX_VALUE  (255)

   /* The following MACRO is a utility MACRO that exists to validate    */
   /* the specified CTE transmit duration is valid or not. The only     */
   /* parameter to this MACRO is the CTE transmit duration to validate. */
   /* This MACRO returns TRUE if the CTE transmit duration is valid or  */
   /* FALSE otherwise.                                                  */
#define QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_VALID(_x)  (((_x) >=  QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_MIN_VALUE) && ((_x) <=  QAPI_BLE_CTES_ADVERTISING_CTE_TRANSMIT_DURATION_MAX_VALUE))

   /* The following defines the valid range of CTE interval values that */
   /* may be set as the value range for the CTE interval characteristic */
   /* value.                                                            */
#define QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_MIN_VALUE          (0x0006)
#define QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_MAX_VALUE          (0xFFFF)

   /* The following MACRO is a utility MACRO that exists to validate    */
   /* the specified CTE interval is valid or not. The only parameter to */
   /* this MACRO is the CTE interval to validate. This MACRO returns    */
   /* TRUE if the CTE interval is valid or FALSE otherwise.             */
#define QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_VALID(_x)          (((_x) >=  QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_MIN_VALUE) && ((_x) <=  QAPI_BLE_CTES_ADVERTISING_CTE_INTERVAL_MAX_VALUE))

   /* The following defines the valid CTE PHY values that               */
   /* may be set as the value for the CTE PHY characteristic value.     */
#define QAPI_BLE_CTES_ADVERTISING_CTE_PHY_LE_1M_VALUE             (0)
#define QAPI_BLE_CTES_ADVERTISING_CTE_PHY_LE_2M_VALUE             (1)

   /* The following MACRO is a utility MACRO that exists to validate    */
   /* the specified CTE PHY is valid or not. The only parameter to      */
   /* this MACRO is the CTE PHY to validate. This MACRO returns         */
   /* TRUE if the CTE PHY is valid or FALSE otherwise.                  */
#define QAPI_BLE_CTES_ADVERTISING_CTE_PHY_VALID(_x)               (((_x) >=  QAPI_BLE_CTES_ADVERTISING_CTE_PHY_LE_1M_VALUE) || ((_x) <=  QAPI_BLE_CTES_ADVERTISING_CTE_PHY_LE_2M_VALUE))

/** @} */ /* end_addtogroup qapi_ble_services_ctes */

#endif

