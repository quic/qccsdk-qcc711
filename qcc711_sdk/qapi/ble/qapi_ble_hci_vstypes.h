/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_HCI_VSTYPES_H__
#define __QAPI_BLE_HCI_VSTYPES_H__

#include "qapi_ble_btapityp.h"
#include "qapi_ble_bttypes.h"   /* Bluetooth Type Definitions.                */

   /* HCI VS Prod Test OCF codes.                                       */
#define QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_CODE_OCF       0x0004

   /* HCI VS Prod Test Sub op-codes.                                    */
#define QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_STOP             0x03
#define QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_LE_TX_CONTINUOUS 0x15
#define QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_LE_TX_BURST      0x1C

   /* Device transmit channel number range.                             */
#define QAPI_BLE_HCI_VS_PROD_TEST_CHANNEL_INDEX_MINIMUM            0x00
#define QAPI_BLE_HCI_VS_PROD_TEST_CHANNEL_INDEX_MAXIMUM            0x27

   /* Transmit output power range.                                      */
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MINIMUM    0x00
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MAXIMUM    0x09

   /* Transmit types.                                                   */
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_CARRIER_ONLY       0x24
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_1M_PRBS9        0x25
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_1M_PRBS15       0x26
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_1M_PATTERN      0x27
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_2M_PRBS9        0x28
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_2M_PRBS15       0x29
#define QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_2M_PATTERN      0x2A

   /* Packet length range.                                              */
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_LENGTH_MINIMUM            0x00
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_LENGTH_MAXIMUM            0x20

   /* Bit pattern range (for each octet up to 4).                       */
#define QAPI_BLE_HCI_VS_PROD_TEST_BIT_PATTERN_MINIMUM              0x01
#define QAPI_BLE_HCI_VS_PROD_TEST_BIT_PATTERN_MAXIMUM              0xFF

   /* Payload length range.                                             */
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_LENGTH_MINIMUM           0x0000
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_LENGTH_MAXIMUM           0x03FD

   /* Payload type range.                                               */
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_PRBS9                      0x00
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_NIBBLES          0x01
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_BITS             0x02
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_PRBS15                     0x03
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALL_1                      0x05
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALL_0                      0x06
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_NIBBLES_REVERSE  0x07
#define QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_BITS_REVERSE     0x08

   /* Packet type range.                                                */
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_1M             0x01
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_2M             0x02
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_CODED_125K     0x03
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_CODED_500K     0x04
#define QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_SIMULTANEOUS_SCAN 0x05

   /* HCI VS Prod Test command structures.                              */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_Stop_Command_s
{
   qapi_BLE_NonAlignedByte_t  Sub_Op_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_Stop_Command_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_STOP_COMMAND_SIZE      (sizeof(qapi_BLE_HCI_VS_Prod_Test_Stop_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_s
{
   qapi_BLE_NonAlignedByte_t  Sub_Op_Code;
   qapi_BLE_NonAlignedByte_t  Channel_Index;
   qapi_BLE_NonAlignedByte_t  Transmit_Output_Power;
   qapi_BLE_NonAlignedByte_t  Transmit_Type;
   qapi_BLE_NonAlignedByte_t  Packet_Length;
   qapi_BLE_NonAlignedDWord_t Bit_Pattern;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_CONTINUOUS_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_s
{
   qapi_BLE_NonAlignedByte_t Sub_Op_Code;
   qapi_BLE_NonAlignedByte_t Hop_Channels;
   qapi_BLE_NonAlignedWord_t Payload_Length;
   qapi_BLE_NonAlignedByte_t Payload_Type;
   qapi_BLE_NonAlignedByte_t Packet_Type;
   qapi_BLE_NonAlignedByte_t Transmit_Output_Power;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_BURST_COMMAND_SIZE  (sizeof(qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_t))

   /* HCI VS Prod Test command complete events.                         */

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_Stop_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_Stop_Command_Complete_Event_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_STOP_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_VS_Prod_Test_Stop_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_Complete_Event_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_CONTINUOUS_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_Complete_Event_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_Complete_Event_s
{
   qapi_BLE_HCI_Command_Complete_Event_Header_t HCI_Command_Complete_Event_Header;
   qapi_BLE_NonAlignedByte_t                    Status;
   qapi_BLE_NonAlignedByte_t                    Sub_Op_Code;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_Complete_Event_t;

#define QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_BURST_COMMAND_COMPLETE_EVENT_SIZE  (sizeof(qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_Complete_Event_t))

#endif
