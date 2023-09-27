/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_ATT_TYPES_H__
#define __QAPI_BLE_ATT_TYPES_H__

#include "./qapi_ble_bttypes.h" /* Bluetooth Type Definitions.                */

   /* The following Constants represent the Service Discovery Protocol  */
   /* Protocol Service Multiplexor (PSM) values when Attribute Protocol */
   /* runs over the L2CAP Protocol (the other defined mechanism is Low  */
   /* Energy (LE) and in which case it has it's own fixed channel).     */
#define QAPI_BLE_ATT_PROTOCOL_SERVICE_MUTIPLEXOR                             (0x001F)

   /* The following constants represent the minimum and maximum         */
   /* (respectively) MTU values that are allowable for the Attribute    */
   /* Protocol.                                                         */
#define QAPI_BLE_ATT_PROTOCOL_MTU_MINIMUM_LE                                 23
#define QAPI_BLE_ATT_PROTOCOL_MTU_MINIMUM_BR_EDR                             48
#define QAPI_BLE_ATT_PROTOCOL_MTU_MAXIMUM                                    517

   /* The following constants represent the minimum and maximum values  */
   /* of Attribute Handles that are supported by the Attribute Protocol.*/
#define QAPI_BLE_ATT_PROTOCOL_HANDLE_MINIMUM_VALUE                           0x0001
#define QAPI_BLE_ATT_PROTOCOL_HANDLE_MAXIMUM_VALUE                           0xFFFF

   /* The following constant represents the largest possible length that*/
   /* an Attribute Value can occupy (specified in bytes).               */
#define QAPI_BLE_ATT_PROTOCOL_VALUE_MAXIMUM_LENGTH                           512

   /* The following constants represent the minimum and maximum values  */
   /* that are allowed for Attribute OpCodes.                           */
#define QAPI_BLE_ATT_PROTOCOL_OPCODE_MINIMUM_VALUE                           0x01
#define QAPI_BLE_ATT_PROTOCOL_OPCODE_MAXIMUM_VALUE                           0x7F

   /* The following constants represent the bit-mask values that are    */
   /* applied to the Attribute OpCodes to parse the various fields that */
   /* are present in the OpCode.                                        */
#define QAPI_BLE_ATT_PROTOCOL_OPCODE_COMMAND_FLAG_MASK                       0x40
#define QAPI_BLE_ATT_PROTOCOL_OPCODE_AUTHENTICATION_SIGNATURE_MASK           0x80

   /* The following constants represent the defined Attribute Protocol  */
   /* Command Codes.                                                    */
#define QAPI_BLE_ATT_PROTOCOL_CODE_ERROR_RESPONSE                            0x01
#define QAPI_BLE_ATT_PROTOCOL_CODE_EXCHANGE_MTU_REQUEST                      0x02
#define QAPI_BLE_ATT_PROTOCOL_CODE_EXCHANGE_MTU_RESPONSE                     0x03
#define QAPI_BLE_ATT_PROTOCOL_CODE_FIND_INFORMATION_REQUEST                  0x04
#define QAPI_BLE_ATT_PROTOCOL_CODE_FIND_INFORMATION_RESPONSE                 0x05
#define QAPI_BLE_ATT_PROTOCOL_CODE_FIND_BY_TYPE_VALUE_REQUEST                0x06
#define QAPI_BLE_ATT_PROTOCOL_CODE_FIND_BY_TYPE_VALUE_RESPONSE               0x07
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BY_TYPE_REQUEST                      0x08
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BY_TYPE_RESPONSE                     0x09
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_REQUEST                              0x0A
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_RESPONSE                             0x0B
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BLOB_REQUEST                         0x0C
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BLOB_RESPONSE                        0x0D
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_MULTIPLE_REQUEST                     0x0E
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_MULTIPLE_RESPONSE                    0x0F
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BY_GROUP_TYPE_REQUEST                0x10
#define QAPI_BLE_ATT_PROTOCOL_CODE_READ_BY_GROUP_TYPE_RESPONSE               0x11
#define QAPI_BLE_ATT_PROTOCOL_CODE_WRITE_REQUEST                             0x12
#define QAPI_BLE_ATT_PROTOCOL_CODE_WRITE_RESPONSE                            0x13
#define QAPI_BLE_ATT_PROTOCOL_CODE_WRITE_COMMAND                             0x52
#define QAPI_BLE_ATT_PROTOCOL_CODE_PREPARE_WRITE_REQUEST                     0x16
#define QAPI_BLE_ATT_PROTOCOL_CODE_PREPARE_WRITE_RESPONSE                    0x17
#define QAPI_BLE_ATT_PROTOCOL_CODE_EXECUTE_WRITE_REQUEST                     0x18
#define QAPI_BLE_ATT_PROTOCOL_CODE_EXECUTE_WRITE_RESPONSE                    0x19
#define QAPI_BLE_ATT_PROTOCOL_CODE_HANDLE_VALUE_NOTIFICATION                 0x1B
#define QAPI_BLE_ATT_PROTOCOL_CODE_HANDLE_VALUE_INDICATION                   0x1D
#define QAPI_BLE_ATT_PROTOCOL_CODE_HANDLE_VALUE_CONFIRMATION                 0x1E
#define QAPI_BLE_ATT_PROTOCOL_CODE_SIGNED_WRITE_COMMAND                      0xD2

   /* The following constants represent the defined Attribute Protocol  */
   /* Error Codes that are defined by the protocol itself.              */
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_HANDLE                      0x01
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_READ_NOT_PERMITTED                  0x02
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_WRITE_NOT_PERMITTED                 0x03
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_PDU                         0x04
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_AUTHENTICATION         0x05
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_REQUEST_NOT_SUPPORTED               0x06
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_OFFSET                      0x07
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_AUTHORIZATION          0x08
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_PREPARE_QUEUE_FULL                  0x09
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_ATTRIBUTE_NOT_FOUND                 0x0A
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_ATTRIBUTE_NOT_LONG                  0x0B
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_ENCRYPTION_KEY_SIZE    0x0C
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INVALID_ATTRIBUTE_VALUE_LENGTH      0x0D
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_UNLIKELY_ERROR                      0x0E
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_ENCRYPTION             0x0F
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_UNSUPPORTED_GROUP_TYPE              0x10
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_INSUFFICIENT_RESOURCES              0x11

   /* The following constants represent the defined Attribute Protocol  */
   /* Error Codes that are defined as Common Profile and Service Error  */
   /* Codes in CSS v2 Part B.                                           */
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_CCCD_IMPROPERLY_CONFIGURED          0xFD
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_PROCEDURE_ALREADY_IN_PROGRESS       0xFE
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_OUT_OF_RANGE                        0xFF

   /* The following constants represent the starting and ending values  */
   /* that can be used by application profiles to define error codes    */
   /* (for specific use by that application profile).                   */
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_APPLICATION_ERROR_START             0x80
#define QAPI_BLE_ATT_PROTOCOL_ERROR_CODE_APPLICATION_ERROR_END               0xFC

   /* The following constant represents the timeout (in seconds) that is*/
   /* to be applied to Attribute Protocol Transactions.  If a           */
   /* transaction takes longer than this value then the transaction is  */
   /* considered failed.                                                */
#define QAPI_BLE_ATT_PROTOCOL_TRANSACTION_TIMEOUT_VALUE                      30

   /* The following structure defines the container structure that will */
   /* hold the Authentication Signature data (if present in an Attribute*/
   /* Protocol PDU).                                                    */
   /* * NOTE * The actual contents (and generation) of this signature   */
   /*          are defined in the Bluetooth Security Manager            */
   /*          Specification.                                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Authentication_Signature_s
{
   qapi_BLE_NonAlignedByte_t Authentication_Signature0;
   qapi_BLE_NonAlignedByte_t Authentication_Signature1;
   qapi_BLE_NonAlignedByte_t Authentication_Signature2;
   qapi_BLE_NonAlignedByte_t Authentication_Signature3;
   qapi_BLE_NonAlignedByte_t Authentication_Signature4;
   qapi_BLE_NonAlignedByte_t Authentication_Signature5;
   qapi_BLE_NonAlignedByte_t Authentication_Signature6;
   qapi_BLE_NonAlignedByte_t Authentication_Signature7;
   qapi_BLE_NonAlignedByte_t Authentication_Signature8;
   qapi_BLE_NonAlignedByte_t Authentication_Signature9;
   qapi_BLE_NonAlignedByte_t Authentication_Signature10;
   qapi_BLE_NonAlignedByte_t Authentication_Signature11;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Authentication_Signature_t;

#define QAPI_BLE_ATT_AUTHENTICATION_SIGNATURE_DATA_SIZE                      (sizeof(qapi_BLE_ATT_Authentication_Signature_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Attribute Authentication*/
   /* Signature variable.  The Bytes are NOT in Little Endian Format,   */
   /* however, they are assigned to the Authentication Signature        */
   /* Variable in Little Endian Format.  The first parameter is the     */
   /* Authentication Signature Variable (of type                        */
   /* qapi_BLE_ATT_Authentication_Signature_t) to assign, and the next  */
   /* 12 parameters are the Individual Authentication Signature Byte    */
   /* values to assign to the Authentication Signature Variable.        */
#define QAPI_BLE_ASSIGN_ATT_AUTHENTICATION_SIGNATURE(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l)                         \
{                                                                                                                                   \
   (_dest).Authentication_Signature0  = (_l); (_dest).Authentication_Signature1  = (_k); (_dest).Authentication_Signature2  = (_j); \
   (_dest).Authentication_Signature3  = (_i); (_dest).Authentication_Signature4  = (_h); (_dest).Authentication_Signature5  = (_g); \
   (_dest).Authentication_Signature6  = (_f); (_dest).Authentication_Signature7  = (_e); (_dest).Authentication_Signature8  = (_d); \
   (_dest).Authentication_Signature9  = (_c); (_dest).Authentication_Signature10 = (_b); (_dest).Authentication_Signature11 = (_a); \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_ATT_Authentication_Signature_t         */
   /* variables.  This MACRO only returns whether the two               */
   /* qapi_BLE_ATT_Authentication_Signature_t variables are equal (MACRO*/
   /* returns boolean result) NOT less than/greater than.  The two      */
   /* parameters to this MACRO are both of type                         */
   /* qapi_BLE_ATT_Authentication_Signature_t * and represent the       */
   /* qapi_BLE_ATT_Authentication_Signature_t variables to compare.     */
#define QAPI_BLE_COMPARE_ATT_AUTHENTICATION_SIGNATURE(_x, _y)                                                                                                                                                                    \
(                                                                                                                                                                                                                                \
   ((_x)->Authentication_Signature0  == (_y)->Authentication_Signature0)  && ((_x)->Authentication_Signature1  == (_y)->Authentication_Signature1)  && ((_x)->Authentication_Signature2  == (_y)->Authentication_Signature2)  && \
   ((_x)->Authentication_Signature3  == (_y)->Authentication_Signature3)  && ((_x)->Authentication_Signature4  == (_y)->Authentication_Signature4)  && ((_x)->Authentication_Signature5  == (_y)->Authentication_Signature5)  && \
   ((_x)->Authentication_Signature6  == (_y)->Authentication_Signature6)  && ((_x)->Authentication_Signature7  == (_y)->Authentication_Signature7)  && ((_x)->Authentication_Signature8  == (_y)->Authentication_Signature8)  && \
   ((_x)->Authentication_Signature9  == (_y)->Authentication_Signature9)  && ((_x)->Authentication_Signature10 == (_y)->Authentication_Signature10) && ((_x)->Authentication_Signature11 == (_y)->Authentication_Signature11)    \
)

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigning a Sign Counter into an Authentication Signature.  The   */
   /* Sign Counter is stored in the first 4 bytes of the Authentication */
   /* Signature.  The parameters to this MACRO are a pointer to the     */
   /* qapi_BLE_ATT_Authentication_Signature_t to assign the sign counter*/
   /* into, and the Sign Counter (uint32_t).                            */
#define QAPI_BLE_ASSIGN_ATT_AUTHENTICATION_SIGNATURE_SIGN_COUNTER(_x, _y)  ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD((_x), (_y))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* reading the Sign Counter from an Authentication Signature that was*/
   /* received from a Remote ATT Client.  The Sign Counter is stored in */
   /* the first 4 bytes of the Authentication Signature.  The only      */
   /* parameter to this MACRO is the                                    */
   /* qapi_BLE_ATT_Authentication_Signature_t to read the sign counter  */
   /* from.                                                             */
#define QAPI_BLE_READ_ATT_AUTHENTICATION_SIGNATURE_SIGN_COUNTER(_x)                 READ_UNALIGNED_DWORD_LITTLE_ENDIAN((_x))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* assigning a CMAC into an Authentication Signature.  The CMAC is   */
   /* stored in the last 8 bytes of the Authentication Signature.  The  */
   /* parameters to this MACRO are a pointer to the                     */
   /* qapi_BLE_ATT_Authentication_Signature_t to assign the CMAC into,  */
   /* and the CMAC (SM_MAC_t).                                          */
#define QAPI_BLE_ASSIGN_ATT_AUTHENTICATION_SIGNATURE_CMAC(_x, _y)          ASSIGN_UNALIGNED_GENERIC_TYPE(((SM_MAC_t *)&(((uint8_t *)(_x))[sizeof(uint32_t)])), (_y))

   /* The following MACRO is a utility MACRO that exists to aid in      */
   /* reading the CMAC from an Authentication Signature that was        */
   /* received from a Remote ATT Client.  The CMAC is stored in the last*/
   /* 8 bytes of the Authentication Signature.  The only parameter to   */
   /* this MACRO is the qapi_BLE_ATT_Authentication_Signature_t to read */
   /* the CMAC from.                                                    */
#define QAPI_BLE_READ_ATT_AUTHENTICATION_SIGNATURE_CMAC(_x)                         READ_UNALIGNED_GENERIC_TYPE((SM_MAC_t *)&(((uint8_t *)(_x))[sizeof(uint32_t)]))

   /* The following structure represents the format of the Attribute PDU*/
   /* header that is present in ALL Attribute PDU's.                    */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_PDU_Header_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_PDU_Header_t;

#define QAPI_BLE_ATT_PDU_HEADER_SIZE                              (sizeof(qapi_BLE_ATT_PDU_Header_t))

   /* The following type definition defines the structure of an Handle  */
   /* Range structure.                                                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Handle_Range_s
{
   qapi_BLE_NonAlignedWord_t StartingHandle;
   qapi_BLE_NonAlignedWord_t EndingHandle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Handle_Range_t;

#define QAPI_BLE_ATT_HANDLE_RANGE_SIZE                            (sizeof(qapi_BLE_ATT_Handle_Range_t))

   /* Attribute PDU definitions.                                        */
   /* * NOTE * All PDU definitions are defined to NOT include an        */
   /*          Authentication Signature member.  If an Authentication   */
   /*          Signature is required, it will have to be added to the   */
   /*          end of the defined PDU structure (if the PDU can         */
   /*          actually support a Signature).                           */

   /* The following type definition defines the structure of an         */
   /* Attribute Error Response PDU.                                     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Error_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t  Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t  RequestOpCodeInError;
   qapi_BLE_NonAlignedWord_t  AttributeHandleInError;
   qapi_BLE_NonAlignedByte_t  ErrorCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Error_Response_PDU_t;

#define QAPI_BLE_ATT_ERROR_RESPONSE_PDU_SIZE                      (sizeof(qapi_BLE_ATT_Error_Response_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Exchange MTU Request PDU.                               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Exchange_MTU_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t  Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t  ClientRxMTU;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Exchange_MTU_Request_PDU_t;

#define QAPI_BLE_ATT_EXCHANGE_MTU_REQUEST_PDU_SIZE                (sizeof(qapi_BLE_ATT_Exchange_MTU_Request_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Exchange MTU Response PDU.                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Exchange_MTU_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t  Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t  ServerRxMTU;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Exchange_MTU_Response_PDU_t;

#define QAPI_BLE_ATT_EXCHANGE_MTU_RESPONSE_PDU_SIZE               (sizeof(qapi_BLE_ATT_Exchange_MTU_Response_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Find Information Request PDU.                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Find_Information_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t  Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t  StartingHandle;
   qapi_BLE_NonAlignedWord_t  EndingHandle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Find_Information_Request_PDU_t;

#define QAPI_BLE_ATT_FIND_INFORMATION_REQUEST_PDU_SIZE            (sizeof(qapi_BLE_ATT_Find_Information_Request_PDU_t))

   /* The following constants represent the defined values that are     */
   /* allowable for the Format member of the                            */
   /* qapi_BLE_ATT_Find_Information_Response_PDU_t PDU.                 */
#define QAPI_BLE_ATT_FIND_INFORMATION_RESPONSE_FORMAT_HANDLE_16_BIT_UUID         0x01
#define QAPI_BLE_ATT_FIND_INFORMATION_RESPONSE_FORMAT_HANDLE_128_BIT_UUID        0x02

   /* The following type definition defines the structure of an         */
   /* Attribute Find Information Response PDU.                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Find_Information_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t Format;
   qapi_BLE_NonAlignedByte_t InformationData[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Find_Information_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Find Information Response PDU.  The*/
   /* input parameter specifies the length of the Information Data (in  */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_FIND_INFORMATION_RESPONSE_PDU_SIZE(_x)       (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Find_Information_Response_PDU_t, InformationData) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Find By Type Request PDU.                               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Find_By_Type_Value_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t StartingHandle;
   qapi_BLE_NonAlignedWord_t EndingHandle;
   qapi_BLE_UUID_16_t        AttributeType;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Find_By_Type_Value_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Find By Type Request PDU.  The     */
   /* input parameter specifies the length of the Value data (in bytes).*/
   /* This MACRO calculates the total size required (in bytes) to hold  */
   /* the entire PDU.                                                   */
#define QAPI_BLE_ATT_FIND_BY_TYPE_VALUE_REQUEST_PDU_SIZE(_x)      (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Find_By_Type_Value_Request_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Find By Type Response PDU.                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Find_By_Type_Value_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t HandleInformation[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Find_By_Type_Value_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Find By Type Response PDU.  The    */
   /* input parameter specifies the number of Handles Information       */
   /* Entries (not bytes) that are to be present in the PDU.  This MACRO*/
   /* calculates the total size required (in bytes) to hold the entire  */
   /* PDU.                                                              */
#define QAPI_BLE_ATT_FIND_BY_TYPE_VALUE_RESPONSE_PDU_SIZE(_x)     (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Find_By_Type_Value_Response_PDU_t, HandleInformation) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Request PDU.                                       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t  Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t  AttributeHandle;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Request_PDU_t;

#define QAPI_BLE_ATT_READ_REQUEST_PDU_SIZE                        (sizeof(qapi_BLE_ATT_Read_Request_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Response PDU.                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read Response PDU.  The input      */
   /* parameter specifies the length of the Attribute data (in bytes).  */
   /* This MACRO calculates the total size required (in bytes) to hold  */
   /* the entire PDU.                                                   */
#define QAPI_BLE_ATT_READ_RESPONSE_PDU_SIZE(_x)                   (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_Response_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read By Type Request PDU.                               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_By_Type_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t StartingHandle;
   qapi_BLE_NonAlignedWord_t EndingHandle;
   qapi_BLE_NonAlignedByte_t AttributeType[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_By_Type_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read By Type Response PDU.  The    */
   /* input parameter specifies the length of the Attribute Type (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_READ_BY_TYPE_REQUEST_PDU_SIZE(_x)            (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_By_Type_Request_PDU_t, AttributeType) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read By Type Response PDU.                              */
   /* * NOTE * The Lenght member does not specify the total size of the */
   /*          AttributeData member, rather it specifies the actual     */
   /*          size (in bytes) of each Attribute Handle/Value Pair (of  */
   /*          which there could more than one).                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_By_Type_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t Length;
   qapi_BLE_NonAlignedByte_t AttributeDataList[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_By_Type_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read By Type Response PDU.  The    */
   /* input parameter _x specifies the size in bytes of the Attribute   */
   /* Value.  The input parameter _y specifies the number of Attribute  */
   /* Information Entries that are present in the PDU.  This MACRO      */
   /* calculates the total size required (in bytes) to hold the entire  */
   /* PDU.                                                              */
#define QAPI_BLE_ATT_READ_BY_TYPE_RESPONSE_PDU_SIZE(_x, _y)       (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_By_Type_Response_PDU_t, AttributeDataList) + (((_x) * sizeof(uint8_t)) * (_y)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Blob Request PDU.                                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Blob_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedWord_t ValueOffset;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Blob_Request_PDU_t;

#define QAPI_BLE_ATT_READ_BLOB_REQUEST_PDU_SIZE                   (sizeof(qapi_BLE_ATT_Read_Blob_Request_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Blob Response PDU.                                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Blob_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t PartAttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Blob_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read Blob Response PDU.  The input */
   /* parameter specifies the length of the Part Attribute data (in     */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_READ_BLOB_RESPONSE_PDU_SIZE(_x)              (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_Blob_Response_PDU_t, PartAttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Multiple Request PDU.                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Multiple_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t SetOfHandles[2];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Multiple_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read Multiple Request PDU.  The    */
   /* input parameter specifies the number of Handles that are present  */
   /* in the PDU (not bytes).  This MACRO calculates the total size     */
   /* required (in bytes) to hold the entire PDU.                       */
#define QAPI_BLE_ATT_READ_MULTIPLE_REQUEST_PDU_SIZE(_x)           (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_Multiple_Request_PDU_t, SetOfHandles) + ((_x)*sizeof(uint16_t)))

   /* The following constants represent the minimum and maximum         */
   /* (respectively) number of Handles that can be specified in an      */
   /* Attribute Read Multiple Request PDU.                              */
#define QAPI_BLE_ATT_READ_MULTIPLE_REQUEST_MINIMUM_HANDLES        2
#define QAPI_BLE_ATT_READ_MULTIPLE_REQUEST_MAXIMUM_HANDLES        ((ATT_MTU_MAXIMUM - QAPI_BLE_ATT_READ_MULTIPLE_REQUEST_PDU_SIZE(0))/sizeof(uint16_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Read Multiple Response PDU.                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_Multiple_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t AttributeValues[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_Multiple_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read Response PDU.  The input      */
   /* parameter specifies the length of the Attribute data (in bytes).  */
   /* This MACRO calculates the total size required (in bytes) to hold  */
   /* the entire PDU.                                                   */
#define QAPI_BLE_ATT_READ_MULTIPLE_RESPONSE_PDU_SIZE(_x)          (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_Multiple_Response_PDU_t, AttributeValues) + ((_x)*sizeof(uint8_t)))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_By_Group_Type_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t StartingHandle;
   qapi_BLE_NonAlignedWord_t EndingHandle;
   qapi_BLE_NonAlignedByte_t AttributeGroupType[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_By_Group_Type_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read By Group Type Request PDU.    */
   /* The input parameter specifies the length of the Attribute Type    */
   /* (in bytes).  This MACRO calculates the total size required        */
   /* (in bytes) to hold the entire PDU.                                */
#define QAPI_BLE_ATT_READ_BY_GROUP_TYPE_REQUEST_PDU_SIZE(_x)      (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_By_Group_Type_Request_PDU_t, AttributeGroupType) + ((_x) * sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Read By Group Type Response PDU.                        */
   /* * NOTE * The Length member does not specify the total size of the */
   /*          AttributeDataList member, rather it specifies the actual */
   /*          size (in bytes) of each Attribute Handle/End Group Handle*/
   /*          /Value tuple (of which there could more than one).       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Read_By_Group_Type_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t Length;
   qapi_BLE_NonAlignedByte_t AttributeDataList[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Read_By_Group_Type_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Read By Group Type Response PDU.   */
   /* The 'x' input parameter specifies the length of the Attribute     */
   /* Group Value (in bytes).  The 'y' attribute specified the number of*/
   /* values in the structure.  This MACRO calculates the total size    */
   /* required (in bytes) to hold the entire PDU.                       */
#define QAPI_BLE_ATT_READ_BY_GROUP_TYPE_RESPONSE_PDU_SIZE(_x, _y) (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Read_By_Group_Type_Response_PDU_t, AttributeDataList) + (((_x) * sizeof(uint8_t)) * (_y)))

   /* The following type definition defines the structure of an         */
   /* Attribute Write Request PDU.                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Write_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Write_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Write Request PDU.  The input      */
   /* parameter specifies the length of the Attribute data (in bytes).  */
   /* This MACRO calculates the total size required (in bytes) to hold  */
   /* the entire PDU.                                                   */
#define QAPI_BLE_ATT_WRITE_REQUEST_PDU_SIZE(_x)                   (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Write_Request_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Write Response PDU.                                     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Write_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Write_Response_PDU_t;

#define QAPI_BLE_ATT_WRITE_RESPONSE_PDU_SIZE                      (sizeof(qapi_BLE_ATT_Write_Response_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Write Command PDU.                                      */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Write_Command_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Write_Command_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Write Command PDU.  The input      */
   /* parameter specifies the length of the Attribute data (in bytes).  */
   /* This MACRO calculates the total size required (in bytes) to hold  */
   /* the entire PDU.                                                   */
#define QAPI_BLE_ATT_WRITE_COMMAND_PDU_SIZE(_x)                   (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Write_Command_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Signed Write Command PDU.                               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Signed_Write_Command_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Signed_Write_Command_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Signed Write Command PDU.  The     */
   /* input parameter specifies the length of the Attribute data (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
   /* * NOTE * That the Attribute Authentication Signature is appended  */
   /*          to the end of this PDU. Therefore we must take into      */
   /*          account the size of the structure.                       */
#define QAPI_BLE_ATT_SIGNED_WRITE_COMMAND_PDU_SIZE(_x)            (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Signed_Write_Command_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)) + QAPI_BLE_ATT_AUTHENTICATION_SIGNATURE_DATA_SIZE)

   /* The following type definition defines the structure of an         */
   /* Attribute Prepare Write Request PDU.                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Prepare_Write_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedWord_t ValueOffset;
   qapi_BLE_NonAlignedByte_t PartAttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Prepare_Write_Request_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Prepare Write Request PDU.  The    */
   /* input parameter specifies the length of the Attribute data (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_PREPARE_WRITE_REQUEST_PDU_SIZE(_x)           (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Prepare_Write_Request_PDU_t, PartAttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Prepare Write Response PDU.                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Prepare_Write_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedWord_t ValueOffset;
   qapi_BLE_NonAlignedByte_t PartAttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Prepare_Write_Response_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Prepare Write Response PDU.  The   */
   /* input parameter specifies the length of the Attribute data (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_PREPARE_WRITE_RESPONSE_PDU_SIZE(_x)          (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Prepare_Write_Response_PDU_t, PartAttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Execute Write Request PDU.                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Execute_Write_Request_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedByte_t Flags;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Execute_Write_Request_PDU_t;

#define QAPI_BLE_ATT_EXECUTE_WRITE_REQUEST_PDU_SIZE               (sizeof(qapi_BLE_ATT_Execute_Write_Request_PDU_t))

   /* The following constants are used with the Flags member of the     */
   /* qapi_BLE_ATT_Execute_Write_Request_PDU_t PDU to specify the action*/
   /* that should be taken for all previously prepared writes.          */
#define QAPI_BLE_ATT_EXECUTE_WRITE_REQUEST_FLAGS_CANCEL_ALL        0x00
#define QAPI_BLE_ATT_EXECUTE_WRITE_REQUEST_FLAGS_IMMEDIATELY_WRITE 0x01

   /* The following type definition defines the structure of an         */
   /* Attribute Execute Write Response PDU.                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Execute_Write_Response_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Execute_Write_Response_PDU_t;

#define QAPI_BLE_ATT_EXECUTE_WRITE_RESPONSE_PDU_SIZE              (sizeof(qapi_BLE_ATT_Execute_Write_Response_PDU_t))

   /* The following type definition defines the structure of an         */
   /* Attribute Handle Value Notification PDU.                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Handle_Value_Notification_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Handle_Value_Notification_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Handle Value Notification PDU.  The*/
   /* input parameter specifies the length of the Attribute data (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_HANDLE_VALUE_NOTIFICATION_PDU_SIZE(_x)       (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Handle_Value_Notification_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Handle Value Indication PDU.                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Handle_Value_Indication_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
   qapi_BLE_NonAlignedWord_t AttributeHandle;
   qapi_BLE_NonAlignedByte_t AttributeValue[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Handle_Value_Indication_PDU_t;

   /* The following is a utility MACRO provided to determine how much   */
   /* memory is required to format a Handle Value Indication PDU.  The  */
   /* input parameter specifies the length of the Attribute data (in    */
   /* bytes).  This MACRO calculates the total size required (in bytes) */
   /* to hold the entire PDU.                                           */
#define QAPI_BLE_ATT_HANDLE_VALUE_INDICATION_PDU_SIZE(_x)         (QAPI_BLE_BTPS_STRUCTURE_OFFSET(qapi_BLE_ATT_Handle_Value_Indication_PDU_t, AttributeValue) + ((_x)*sizeof(uint8_t)))

   /* The following type definition defines the structure of an         */
   /* Attribute Handle Value Confirmation PDU.                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_ATT_Handle_Value_Confirmation_PDU_s
{
   qapi_BLE_NonAlignedByte_t Attribute_OpCode;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_ATT_Handle_Value_Confirmation_PDU_t;

#define QAPI_BLE_ATT_HANDLE_VALUE_CONFIRMATION_PDU_SIZE           (sizeof(qapi_BLE_ATT_Handle_Value_Confirmation_PDU_t))

#endif
