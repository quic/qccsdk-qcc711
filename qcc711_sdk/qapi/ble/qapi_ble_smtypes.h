/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_SM_TYPES_H__
#define __QAPI_BLE_SM_TYPES_H__

#include "qapi_ble_bttypes.h"            /* Bluetooth Type Definitions. */
#include "qapi_ble_l2cap.h"              /* Bluetooth L2CAP Type        */
                                         /* Definitions.                */

   /* The following constant defines the L2CAP Fixed Channel ID that is */
   /* used for the Security Manager (SM).                               */
#define QAPI_BLE_SM_SECURITY_MANAGER_FIXED_CHANNEL_ID                            (L2CAP_CHANNEL_IDENTIFIER_SECURITY_MANAGER_CHANNEL)

   /* The following type declaration represents the structure of a      */
   /* Security Manager Confirm value as defined by the Bluetooth        */
   /* Specification.                                                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Confirm_Value_s
{
   qapi_BLE_NonAlignedByte_t Confirm_Value0;
   qapi_BLE_NonAlignedByte_t Confirm_Value1;
   qapi_BLE_NonAlignedByte_t Confirm_Value2;
   qapi_BLE_NonAlignedByte_t Confirm_Value3;
   qapi_BLE_NonAlignedByte_t Confirm_Value4;
   qapi_BLE_NonAlignedByte_t Confirm_Value5;
   qapi_BLE_NonAlignedByte_t Confirm_Value6;
   qapi_BLE_NonAlignedByte_t Confirm_Value7;
   qapi_BLE_NonAlignedByte_t Confirm_Value8;
   qapi_BLE_NonAlignedByte_t Confirm_Value9;
   qapi_BLE_NonAlignedByte_t Confirm_Value10;
   qapi_BLE_NonAlignedByte_t Confirm_Value11;
   qapi_BLE_NonAlignedByte_t Confirm_Value12;
   qapi_BLE_NonAlignedByte_t Confirm_Value13;
   qapi_BLE_NonAlignedByte_t Confirm_Value14;
   qapi_BLE_NonAlignedByte_t Confirm_Value15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Confirm_Value_t;

#define QAPI_BLE_SM_CONFIRM_VALUE_SIZE                                           (sizeof(qapi_BLE_SM_Confirm_Value_t))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* comparison of two qapi_BLE_SM_Confirm_Value_t variable. This MACRO*/
   /* only returns whether or not the two qapi_BLE_SM_Confirm_Value_t   */
   /* variables are equal (MACRO returns Boolean result) NOT less than  */
   /* or greater than. The two parameters to this macro are of type     */
   /* qapi_BLE_SM_Confirm_Value_t and represent the Confirm Values to   */
   /* compare.                                                          */
#define QAPI_BLE_SM_COMPARE_CONFIRM_VALUES(_x,_y)                                (((_x).Confirm_Value0  == (_y).Confirm_Value0) && ((_x).Confirm_Value1  == (_y).Confirm_Value1)  && ((_x).Confirm_Value2  == (_y).Confirm_Value2) && ((_x).Confirm_Value3  == (_y).Confirm_Value3) && ((_x).Confirm_Value4  == (_y).Confirm_Value4) && ((_x).Confirm_Value5  == (_y).Confirm_Value5) && ((_x).Confirm_Value6  == (_y).Confirm_Value6)  && ((_x).Confirm_Value7  == (_y).Confirm_Value7) && ((_x).Confirm_Value8  == (_y).Confirm_Value8) && ((_x).Confirm_Value9  == (_y).Confirm_Value9) && ((_x).Confirm_Value10 == (_y).Confirm_Value10) && ((_x).Confirm_Value11 == (_y).Confirm_Value11) && ((_x).Confirm_Value12 == (_y).Confirm_Value12) && ((_x).Confirm_Value13 == (_y).Confirm_Value13) && ((_x).Confirm_Value14 == (_y).Confirm_Value14) && ((_x).Confirm_Value15 == (_y).Confirm_Value15))

   /* The following type declaration represents the structure of a DH   */
   /* Key Check value as defined by the Bluetooth Specification (Version*/
   /* 4.2).                                                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_DHKey_Check_Value_s
{
   qapi_BLE_NonAlignedByte_t DHKey_Check0;
   qapi_BLE_NonAlignedByte_t DHKey_Check1;
   qapi_BLE_NonAlignedByte_t DHKey_Check2;
   qapi_BLE_NonAlignedByte_t DHKey_Check3;
   qapi_BLE_NonAlignedByte_t DHKey_Check4;
   qapi_BLE_NonAlignedByte_t DHKey_Check5;
   qapi_BLE_NonAlignedByte_t DHKey_Check6;
   qapi_BLE_NonAlignedByte_t DHKey_Check7;
   qapi_BLE_NonAlignedByte_t DHKey_Check8;
   qapi_BLE_NonAlignedByte_t DHKey_Check9;
   qapi_BLE_NonAlignedByte_t DHKey_Check10;
   qapi_BLE_NonAlignedByte_t DHKey_Check11;
   qapi_BLE_NonAlignedByte_t DHKey_Check12;
   qapi_BLE_NonAlignedByte_t DHKey_Check13;
   qapi_BLE_NonAlignedByte_t DHKey_Check14;
   qapi_BLE_NonAlignedByte_t DHKey_Check15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_DHKey_Check_Value_t;

#define QAPI_BLE_SM_DHKEY_CHECK_VALUE_SIZE                                       (sizeof(qapi_BLE_SM_DHKey_Check_Value_t))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* comparison of two qapi_BLE_SM_DHKey_Check_Value_t variable. This  */
   /* MACRO only returns whether or not the two                         */
   /* qapi_BLE_SM_DHKey_Check_Value_t variables are equal (MACRO returns*/
   /* Boolean result) NOT less than or greater than. The two parameters */
   /* to this macro are of type qapi_BLE_SM_Confirm_Value_t and         */
   /* represent the Confirm Values to compare.                          */
#define QAPI_BLE_SM_COMPARE_DH_KEY_CHECK_VALUES(_x,_y)                           (((_x).DHKey_Check0  == (_y).DHKey_Check0) && ((_x).DHKey_Check1  == (_y).DHKey_Check1)  && ((_x).DHKey_Check2  == (_y).DHKey_Check2) && ((_x).DHKey_Check3  == (_y).DHKey_Check3) && ((_x).DHKey_Check4  == (_y).DHKey_Check4) && ((_x).DHKey_Check5  == (_y).DHKey_Check5) && ((_x).DHKey_Check6  == (_y).DHKey_Check6)  && ((_x).DHKey_Check7  == (_y).DHKey_Check7) && ((_x).DHKey_Check8  == (_y).DHKey_Check8) && ((_x).DHKey_Check9  == (_y).DHKey_Check9) && ((_x).DHKey_Check10 == (_y).DHKey_Check10) && ((_x).DHKey_Check11 == (_y).DHKey_Check11) && ((_x).DHKey_Check12 == (_y).DHKey_Check12) && ((_x).DHKey_Check13 == (_y).DHKey_Check13) && ((_x).DHKey_Check14 == (_y).DHKey_Check14) && ((_x).DHKey_Check15 == (_y).DHKey_Check15))

   /* The following type declaration represents the structure of a      */
   /* Security Manager (SM) Random Value as defined by the Bluetooth    */
   /* Specification.                                                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Random_Value_s
{
   qapi_BLE_NonAlignedByte_t Random_Number0;
   qapi_BLE_NonAlignedByte_t Random_Number1;
   qapi_BLE_NonAlignedByte_t Random_Number2;
   qapi_BLE_NonAlignedByte_t Random_Number3;
   qapi_BLE_NonAlignedByte_t Random_Number4;
   qapi_BLE_NonAlignedByte_t Random_Number5;
   qapi_BLE_NonAlignedByte_t Random_Number6;
   qapi_BLE_NonAlignedByte_t Random_Number7;
   qapi_BLE_NonAlignedByte_t Random_Number8;
   qapi_BLE_NonAlignedByte_t Random_Number9;
   qapi_BLE_NonAlignedByte_t Random_Number10;
   qapi_BLE_NonAlignedByte_t Random_Number11;
   qapi_BLE_NonAlignedByte_t Random_Number12;
   qapi_BLE_NonAlignedByte_t Random_Number13;
   qapi_BLE_NonAlignedByte_t Random_Number14;
   qapi_BLE_NonAlignedByte_t Random_Number15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Random_Value_t;

#define QAPI_BLE_SM_RANDOM_VALUE_SIZE                                            (sizeof(qapi_BLE_SM_Random_Value_t))

   /* Security Manager (SM) Protocol Data Unit Identifiers (PDU ID's).  */
#define QAPI_BLE_SM_CODE_PAIRING_REQUEST                                         0x01
#define QAPI_BLE_SM_CODE_PAIRING_RESPONSE                                        0x02
#define QAPI_BLE_SM_CODE_PAIRING_CONFIRM                                         0x03
#define QAPI_BLE_SM_CODE_PAIRING_RANDOM                                          0x04
#define QAPI_BLE_SM_CODE_PAIRING_FAILED                                          0x05
#define QAPI_BLE_SM_CODE_ENCRYPTION_INFORMATION                                  0x06
#define QAPI_BLE_SM_CODE_MASTER_IDENTIFICATION                                   0x07
#define QAPI_BLE_SM_CODE_IDENTITY_INFORMATION                                    0x08
#define QAPI_BLE_SM_CODE_IDENTITY_ADDRESS_INFORMATION                            0x09
#define QAPI_BLE_SM_CODE_SIGNING_INFORMATION                                     0x0A
#define QAPI_BLE_SM_CODE_SECURITY_REQUEST                                        0x0B

   /* Security Manager (SM) Protocol Data Unit Identifiers (PDU ID's)   */
   /* added in Version 4.2 (LE Secure Connections feature).             */
#define QAPI_BLE_SM_CODE_PAIRING_PUBLIC_KEY                                      0x0C
#define QAPI_BLE_SM_CODE_PAIRING_DHKEY_CHECK                                     0x0D
#define QAPI_BLE_SM_CODE_KEYPRESS_NOTIFICATION                                   0x0E

   /* Security Manager (SM) Protocol Data Unit Pairing Failed Reason    */
   /* Codes.                                                            */
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_PASSKEY_ENTRY_FAILED                   0x01
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_OOB_NOT_AVAILABLE                      0x02
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_AUTHENTICATION_REQUIREMENTS            0x03
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_CONFIRM_VALUE_FAILED                   0x04
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_PAIRING_NOT_SUPPORTED                  0x05
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_ENCRYPTION_KEY_SIZE                    0x06
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_COMMAND_NOT_SUPPORTED                  0x07
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_UNSPECIFIED_REASON                     0x08
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_REPEATED_ATTEMPTS                      0x09
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_INVALID_PARAMETERS                     0x0A

   /* Security Manager (SM) Protocol Data Unit Pairing Failed Reason    */
   /* Codes added in Version 4.2 (LE Secure Connections feature).       */
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_DHKEY_CHECK_FAILED                           0x0B
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_NUMERIC_COMPARISON_FAILED                    0x0C
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_BR_EDR_PAIRING_IN_PROGRESS                   0x0D
#define QAPI_BLE_SM_PAIRING_FAILED_REASON_CROSS_TRANSPORT_KEY_DERIVATION_NOT_ALLOWED   0x0E

   /* The following type declaration represents the structure of the    */
   /* Header of an Security Manager (SM) Protocol Data Packet.  This    */
   /* Header Information is contained in Every Defined Security Manager */
   /* Protocol Packet.  This structure forms the basis of additional    */
   /* defined Security Manager Protocol Packets.  Since this structure  */
   /* is present at the begining of Every Defined Security Manager      */
   /* Protocol Packet, this structure will be the first element of Every*/
   /* Defined Security Manager Protocol Packet in this file.            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Data_Unit_Header_s
{
   qapi_BLE_NonAlignedByte_t Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Data_Unit_Header_t;

#define QAPI_BLE_SM_PROTOCOL_DATA_UNIT_HEADER_SIZE                               (sizeof(qapi_BLE_SM_Data_Unit_Header_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Request PDU.                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Request_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      IO_Capability;
   qapi_BLE_NonAlignedByte_t      OOB_Data_Flag;
   qapi_BLE_NonAlignedByte_t      Auth_Req;
   qapi_BLE_NonAlignedByte_t      Maximimum_Encryption_Key_Size;
   qapi_BLE_NonAlignedByte_t      Initiator_Key_Distribution;
   qapi_BLE_NonAlignedByte_t      Responder_Key_Distribution;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Request_t;

#define QAPI_BLE_SM_PAIRING_REQUEST_SIZE                                         (sizeof(qapi_BLE_SM_Pairing_Request_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Response PDU.                       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Response_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      IO_Capability;
   qapi_BLE_NonAlignedByte_t      OOB_Data_Flag;
   qapi_BLE_NonAlignedByte_t      Auth_Req;
   qapi_BLE_NonAlignedByte_t      Maximimum_Encryption_Key_Size;
   qapi_BLE_NonAlignedByte_t      Initiator_Key_Distribution;
   qapi_BLE_NonAlignedByte_t      Responder_Key_Distribution;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Response_t;

#define QAPI_BLE_SM_PAIRING_RESPONSE_SIZE                                        (sizeof(qapi_BLE_SM_Pairing_Response_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Confirm PDU.                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Confirm_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_SM_Confirm_Value_t    Confirm_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Confirm_t;

#define QAPI_BLE_SM_PAIRING_CONFIRM_SIZE                                         (sizeof(qapi_BLE_SM_Pairing_Confirm_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Random PDU.                         */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Random_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_SM_Random_Value_t     Random_Value;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Random_t;

#define QAPI_BLE_SM_PAIRING_RANDOM_SIZE                                          (sizeof(qapi_BLE_SM_Pairing_Random_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Random PDU.                         */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Failed_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      Reason;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Failed_t;

#define QAPI_BLE_SM_PAIRING_FAILED_SIZE                                          (sizeof(qapi_BLE_SM_Pairing_Failed_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing Public Key PDU (Version 4.2).       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_Public_Key_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   P256_Public_Key_t     Public_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_Public_Key_t;

#define QAPI_BLE_SM_PAIRING_PUBLIC_KEY_SIZE                                      (sizeof(qapi_BLE_SM_Pairing_Public_Key_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Pairing DHKey Check PDU (Version 4.2).      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Pairing_DHKey_Check_s
{
   qapi_BLE_SM_Data_Unit_Header_t  SM_Data_Unit_Header;
   qapi_BLE_SM_DHKey_Check_Value_t DHKey_Check;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Pairing_DHKey_Check_t;

#define QAPI_BLE_SM_PAIRING_DHKEY_CHECK_SIZE                                     (sizeof(qapi_BLE_SM_Pairing_DHKey_Check_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Keypress Notification PDU (Version 4.2).    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Keypress_Notification_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      Notification_Type;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Keypress_Notification_t;

#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_SIZE                                   (sizeof(qapi_BLE_SM_Keypress_Notification_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Encryption Information PDU.                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Encryption_Information_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   Long_Term_Key_t                Long_Term_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Encryption_Information_t;

#define QAPI_BLE_SM_ENCRYPTION_INFORMATION_SIZE                                  (sizeof(qapi_BLE_SM_Encryption_Information_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Master Identification PDU.                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Master_Identification_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedWord_t      EDIV;
   Random_Number_t                Rand;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Master_Identification_t;

#define QAPI_BLE_SM_MASTER_INDENTIFICATION_SIZE                                  (sizeof(qapi_BLE_SM_Master_Identification_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Identity Information PDU.                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Identity_Information_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   Encryption_Key_t               Identity_Resolving_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Identity_Information_t;

#define QAPI_BLE_SM_IDENTITY_INFORMATION_SIZE                                    (sizeof(qapi_BLE_SM_Identity_Information_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Identity Address Information PDU.           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Identity_Address_Information_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      AddrType;
   qapi_BLE_BD_ADDR_t             BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Identity_Address_Information_t;

#define QAPI_BLE_SM_IDENTITY_ADDRESS_INFORMATION_SIZE                            (sizeof(qapi_BLE_SM_Identity_Address_Information_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Signing Information PDU.                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Signing_Information_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   Encryption_Key_t               Signature_Key;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Signing_Information_t;

#define QAPI_BLE_SM_SIGNING_INFORMATION_SIZE                                     (sizeof(qapi_BLE_SM_Signing_Information_t))

   /* The following type declaration represents the structure of the    */
   /* Security Manager (SM) Security Request PDU.                       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_Security_Request_s
{
   qapi_BLE_SM_Data_Unit_Header_t SM_Data_Unit_Header;
   qapi_BLE_NonAlignedByte_t      Auth_Req;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_Security_Request_t;

#define QAPI_BLE_SM_SECURITY_REQUEST_SIZE                                        (sizeof(qapi_BLE_SM_Security_Request_t))

   /* The following define the acceptable values in the IO Capability   */
   /* field of the Pairing Request and Pairing Response SMP Commands.   */
#define QAPI_BLE_SM_IO_CAPABILITY_DISPLAY_ONLY                                   0x00
#define QAPI_BLE_SM_IO_CAPABILITY_DISPLAY_YES_NO                                 0x01
#define QAPI_BLE_SM_IO_CAPABILITY_DISPLAY_KEYBOARD_ONLY                          0x02
#define QAPI_BLE_SM_IO_CAPABILITY_DISPLAY_NO_INPUT_NO_OUTPUT                     0x03
#define QAPI_BLE_SM_IO_CAPABILITY_DISPLAY_KEYBOARD_DISPLAY                       0x04

   /* The following define the acceptable values in the OOB Data Flag   */
   /* Field of the Pairing Request and Pairing Response SMP Commands.   */
#define QAPI_BLE_SM_OOB_DATA_FLAG_OOB_DATA_NOT_PRESENT                           0x00
#define QAPI_BLE_SM_OOB_DATA_FLAG_OOB_DATA_PRESENT                               0x01

   /* The following Bit Numbers define the format of the Auth_Req field */
   /* accepted by some commands. (Pairing Request, Pairing Response,    */
   /* Security Request).                                                */
#define QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_BONDING_BIT_NUMBER               0x00
#define QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_MITM_BIT_NUMBER                  0x02

   /* The following Bit Numbers define the format of the Auth_Req field */
   /* accepted by some commands.  (Pairing Request, Pairing Response,   */
   /* Security Request) added in Version 4.2 (LE Secure Connections).   */
#define QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_SECURE_CONNECTIONS_BIT_NUMBER    0x03
#define QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_KEYPRESS_NOTIFICATION_BIT_NUMBER 0x04

   /* The following Bit Numbers define the format of the Auth_Req field */
   /* accepted by some commands.  (Pairing Request, Pairing Response,   */
   /* Security Request) added in Version 5.0 .                          */
#define QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_CT2_BIT_NUMBER                   0x05

   /* The following defines represent the Bit Numbers for the Initiator */
   /* and Responder Key Distribution fields. These fields are included  */
   /* in both the Pairing Request and Pairing Response PDUs and         */
   /* represent the Keys that each side of a remote connection is       */
   /* requesting to send and receive.                                   */
#define QAPI_BLE_SM_KEY_DISTRIBUTION_ENCRYPTION_KEY_BIT_NUMBER                   0x00
#define QAPI_BLE_SM_KEY_DISTRIBUTION_IDENTITY_KEY_BIT_NUMBER                     0x01
#define QAPI_BLE_SM_KEY_DISTRIBUTION_SIGNING_KEY_BIT_NUMBER                      0x02

   /* The following defines represent the Bit Numbers for the Initiator */
   /* and Responder Key Distribution fields.  These fields are included */
   /* in both the Pairing Request and Pairing Response PDUs and         */
   /* represent the Keys that each side of a remote connection is       */
   /* requesting to send and receive added in Version 4.2 (LE Secure    */
   /* Connections).                                                     */
#define QAPI_BLE_SM_KEY_DISTRIBUTION_LINK_KEY_BIT_NUMBER                         0x03

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns Bonding Requirements into this field.*/
   /* The first parameter to this MACRO should be a uint8_t variable.   */
#define QAPI_BLE_SM_ASSIGN_BONDING_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) |= ((0x01) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_BONDING_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns No Bonding Requirements into this    */
   /* field. The first parameter to this MACRO should be a uint8_t      */
   /* variable.                                                         */
#define QAPI_BLE_SM_ASSIGN_NO_BONDING_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) &= (~((0x11) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_BONDING_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* testing if the Bonding Bits are set in the Auth_Req fields.       */
   /* This MACRO returns TRUE if Bonding is requested or FALSE if it is */
   /* not.                                                              */
#define QAPI_BLE_SM_TEST_BONDING_AUTHENTICATION_REQUIREMENTS(_x) \
   ((((uint8_t *)(_x))[0]) & ((0x01) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_BONDING_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns MITM protection into this field. The */
   /* first parameter to this MACRO should be a uint8_t variable.       */
#define QAPI_BLE_SM_ASSIGN_MITM_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) |= ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_MITM_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns No MITM protection into this field.  */
   /* The first parameter to this MACRO should be a uint8_t variable.   */
#define QAPI_BLE_SM_ASSIGN_NO_MITM_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) &= ~((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_MITM_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* testing if the MITM bit is set in the Auth_Req field. This MACRO  */
   /* returns TRUE if MITM is set or FALSE otherwise.                   */
#define QAPI_BLE_SM_TEST_MITM_AUTHENTICATION_REQUIREMENTS(_x) \
   ((((uint8_t *)(_x))[0]) & ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_MITM_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns Secure Connections protection into   */
   /* this field. The first parameter to this MACRO should be a uint8_t */
   /* variable.                                                         */
#define QAPI_BLE_SM_ASSIGN_SECURE_CONNECTIONS_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) |= ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_SECURE_CONNECTIONS_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns No Secure Connections protection into*/
   /* this field. The first parameter to this MACRO should be a uint8_t */
   /* variable.                                                         */
#define QAPI_BLE_SM_ASSIGN_NO_SECURE_CONNECTIONS_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) &= ~((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_SECURE_CONNECTIONS_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* testing if the Secure Connections bit is set in the Auth_Req      */
   /* field.  This MACRO returns TRUE if Secure Connections is set or   */
   /* FALSE otherwise.                                                  */
#define QAPI_BLE_SM_TEST_SECURE_CONNECTIONS_AUTHENTICATION_REQUIREMENTS(_x) \
   ((((uint8_t *)(_x))[0]) & ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_SECURE_CONNECTIONS_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns Keypress Notifications into this     */
   /* field. The first parameter to this MACRO should be a uint8_t      */
   /* variable.                                                         */
#define QAPI_BLE_SM_ASSIGN_KEYPRESS_NOTIFICATION_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) |= ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_KEYPRESS_NOTIFICATION_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns No Keypress Notifications protection */
   /* into this field. The first parameter to this MACRO should be a    */
   /* uint8_t variable.                                                 */
#define QAPI_BLE_SM_ASSIGN_NO_KEYPRESS_NOTIFICATION_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) &= ~((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_KEYPRESS_NOTIFICATION_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* testing if the Secure Connections bit is set in the Auth_Req      */
   /* field.  This MACRO returns TRUE if Keypress Notifications is set  */
   /* or FALSE otherwise.                                               */
#define QAPI_BLE_SM_TEST_KEYPRESS_NOTIFICATION_AUTHENTICATION_REQUIREMENTS(_x) \
   ((((uint8_t *)(_x))[0]) & ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_KEYPRESS_NOTIFICATION_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns CT2 into this field. The first       */
   /* parameter to this MACRO should be a uint8_t variable.             */
#define QAPI_BLE_SM_ASSIGN_CT2_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) |= ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_CT2_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigned variables into the Auth_Req field that some PDUs have.   */
   /* (Pairing Request, Pairing Response, Security Request). This field */
   /* is a bit field. This assigns No CT2 protection into this field.   */
   /* The first parameter to this MACRO should be a uint8_t variable.   */
#define QAPI_BLE_SM_ASSIGN_NO_CT2_AUTHENTICATION_REQUIREMENTS(_x) \
   (((uint8_t *)(_x))[0]) &= ~((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_CT2_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* testing if the Secure Connections bit is set in the Auth_Req      */
   /* field.  This MACRO returns TRUE if CT2 is set or FALSE otherwise. */
#define QAPI_BLE_SM_TEST_CT2_AUTHENTICATION_REQUIREMENTS(_x) \
   ((((uint8_t *)(_x))[0]) & ((0x1) << (QAPI_BLE_SM_AUTHENTICATION_REQUIREMENTS_CT2_BIT_NUMBER % (QAPI_BLE_BYTE_SIZE*8))))

   /* The following MACRO is a utiltity MACRO that exists to aid code   */
   /* readability in assigning into the Initiator and Responder Key     */
   /* Distribution Fields. The following MACRO is used to set a bit. The*/
   /* first parameter to this MACRO is a uint8_t variable that the bit  */
   /* will be SET in. The next is the bit to set (should be of the form */
   /* QAPI_BLE_SM_KEY_DISTRIBUTION_xxx_KEY_BIT_NUMBER where 'xxx' is the*/
   /* Key Bit Position to set.                                          */
#define QAPI_BLE_SM_SET_KEY_DISTRIBUTION_BIT(_x, _y)  \
   ((uint8_t *)(_x))[0] |= (uint8_t)(1 << ((_y)%(QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utiltity MACRO that exists to aid code   */
   /* readability in assigning into the Initiator and Responder Key     */
   /* Distribution Fields. The following MACRO is used to clear a bit.  */
   /* The first parameter to this MACRO is a uint8_t variable that the  */
   /* bit will be CLEARED in. The next is the bit to set (should be of  */
   /* the form QAPI_BLE_SM_KEY_DISTRIBUTION_xxx_KEY_BIT_NUMBER where    */
   /* 'xxx' is the Key Bit Position to set.                             */
#define QAPI_BLE_SM_RESET_KEY_DISTRIBUTION_BIT(_x, _y)  \
   ((uint8_t *)(_x))[0] &= (uint8_t)~(1 << ((_y)%(QAPI_BLE_BYTE_SIZE*8)))

   /* The following MACRO is a utiltity MACRO that exists to aid code   */
   /* readability in assigning into the Initiator and Responder Key     */
   /* Distribution Fields. The following MACRO is used to test a bit.   */
   /* The first parameter to this MACRO is a uint8_t variable that the  */
   /* bit will be tested. The next is the bit to be tested (should be of*/
   /* the form QAPI_BLE_SM_KEY_DISTRIBUTION_xxx_KEY_BIT_NUMBER where    */
   /* 'xxx' is the Key Bit Position to set.                             */
#define QAPI_BLE_SM_TEST_KEY_DISTRIBUTION_BIT(_x, _y)  \
   ((((uint8_t *)(_x))[0]) & (uint8_t)(1 << ((_y)%(QAPI_BLE_BYTE_SIZE*8))))

   /* The following defines are the definitions for the possible values */
   /* of the Notification_Type field of the SMP Keypress Notification   */
   /* PDU (Version 4.2).                                                */
#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_ENTRY_STARTED             0x00
#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_DIGIT_ENTERED             0x01
#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_DIGIT_ERASED              0x02
#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_CLEARED                   0x03
#define QAPI_BLE_SM_KEYPRESS_NOTIFICATION_TYPE_PASSKEY_ENTRY_COMPLETED           0x04

   /* The following structure defines the content of a Security Manager */
   /* (SM) Message Authentication Code (MAC) which is defined to be 64  */
   /* bits in Length.                                                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SM_MAC_s
{
  qapi_BLE_NonAlignedByte_t MAC0;
  qapi_BLE_NonAlignedByte_t MAC1;
  qapi_BLE_NonAlignedByte_t MAC2;
  qapi_BLE_NonAlignedByte_t MAC3;
  qapi_BLE_NonAlignedByte_t MAC4;
  qapi_BLE_NonAlignedByte_t MAC5;
  qapi_BLE_NonAlignedByte_t MAC6;
  qapi_BLE_NonAlignedByte_t MAC7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SM_MAC_t;

#define QAPI_BLE_SM_MAC_DATA_SIZE                                                (sizeof(qapi_BLE_SM_MAC_t))

#endif
