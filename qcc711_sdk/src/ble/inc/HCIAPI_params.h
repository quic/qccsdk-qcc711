/*
 * Copyright (c) 2020 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __HCIAPI_PARAMS_H__
#define __HCIAPI_PARAMS_H__

#include "qapi_ble_hci.h"
typedef struct _tagHCI_Version_Supported_Params_t
{
    uint32_t BluetoothStackID;
    qapi_BLE_HCI_Version_t *HCI_Version;
} HCI_Version_Supported_Params_t;

#define HCI_VERSION_SUPPORTED_PARAMS_SIZE sizeof(HCI_Version_Supported_Params_t)

typedef struct _tagHCI_Register_Event_Callback_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} HCI_Register_Event_Callback_Params_t;

#define HCI_REGISTER_EVENT_CALLBACK_PARAMS_SIZE sizeof(HCI_Register_Event_Callback_Params_t)

typedef struct _tagHCI_Register_ACL_Data_Callback_Params_t
{
    uint32_t BluetoothStackID;
    unsigned long CallbackParameter;
} HCI_Register_ACL_Data_Callback_Params_t;

#define HCI_REGISTER_ACL_DATA_CALLBACK_PARAMS_SIZE sizeof(HCI_Register_ACL_Data_Callback_Params_t)

typedef struct _tagHCI_Un_Register_Callback_Params_t
{
    uint32_t BluetoothStackID;
    uint32_t CallbackID;
} HCI_Un_Register_Callback_Params_t;

#define HCI_UN_REGISTER_CALLBACK_PARAMS_SIZE sizeof(HCI_Un_Register_Callback_Params_t)

typedef struct _tagHCI_Send_ACL_Data_Params_t
{
    uint32_t BluetoothStackID;
    uint16_t Connection_Handle;
    uint16_t Flags;
    uint16_t ACLDataLength;
    uint8_t *ACLData;
} HCI_Send_ACL_Data_Params_t;

#define HCI_SEND_ACL_DATA_PARAMS_SIZE sizeof(HCI_Send_ACL_Data_Params_t)

typedef struct _tagHCI_Send_Raw_Command_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t Command_OGF;
    uint16_t Command_OCF;
    uint8_t Command_Length;
    uint8_t *Command_Data;
    uint8_t *StatusResult;
    uint8_t *LengthResult;
    uint8_t *BufferResult;
    boolean_t WaitForResponse;
} HCI_Send_Raw_Command_Params_t;

#define HCI_SEND_RAW_COMMAND_PARAMS_SIZE sizeof(HCI_Send_Raw_Command_Params_t)

typedef struct _tagHCI_Reset_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t *StatusResult;
} HCI_Reset_Params_t;

#define HCI_RESET_PARAMS_SIZE sizeof(HCI_Reset_Params_t)

typedef struct _tagHCI_LE_Receiver_Test_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t RX_Frequency;
    uint8_t *StatusResult;
} HCI_LE_Receiver_Test_Params_t;

#define HCI_LE_RECEIVER_TEST_PARAMS_SIZE sizeof(HCI_LE_Receiver_Test_Params_t)

typedef struct _tagHCI_LE_Transmitter_Test_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t TX_Frequency;
    uint8_t Length_Of_Test_Data;
    uint8_t Packet_Payload;
    uint8_t *StatusResult;
} HCI_LE_Transmitter_Test_Params_t;

#define HCI_LE_TRANSMITTER_TEST_PARAMS_SIZE sizeof(HCI_LE_Transmitter_Test_Params_t)

typedef struct _tagHCI_LE_Test_End_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t *StatusResult;
    uint16_t *Number_Of_PacketsResult;
} HCI_LE_Test_End_Params_t;

#define HCI_LE_TEST_END_PARAMS_SIZE sizeof(HCI_LE_Test_End_Params_t)

typedef struct _tagHCI_LE_Enhanced_Receiver_Test_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t RX_Channel;
    uint8_t PHY;
    uint8_t Modulation_Index;
    uint8_t *StatusResult;
} HCI_LE_Enhanced_Receiver_Test_Params_t;

#define HCI_LE_ENHANCED_RECEIVER_TEST_PARAMS_SIZE sizeof(HCI_LE_Enhanced_Receiver_Test_Params_t)

typedef struct _tagHCI_LE_Enhanced_Transmitter_Test_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t TX_Channel;
    uint8_t Length_Of_Test_Data;
    uint8_t Packet_Payload;
    uint8_t PHY;
    uint8_t *StatusResult;
} HCI_LE_Enhanced_Transmitter_Test_Params_t;

#define HCI_LE_ENHANCED_TRANSMITTER_TEST_PARAMS_SIZE sizeof(HCI_LE_Enhanced_Transmitter_Test_Params_t)

typedef struct _tagHCI_LE_Receiver_Test_V3_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t RX_Channel;
    uint8_t PHY;
    uint8_t Modulation_Index;
    uint8_t Expected_CTE_Length;
    uint8_t Expected_CTE_Type;
    uint8_t Slot_Durations;
    uint8_t Length_Of_Switching_Pattern;
    uint8_t *Antenna_IDs;
    uint8_t *StatusResult;
} HCI_LE_Receiver_Test_V3_Params_t;

#define HCI_LE_RECEIVER_TEST_V3_PARAMS_SIZE sizeof(HCI_LE_Receiver_Test_V3_Params_t)

typedef struct _tagHCI_LE_Transmitter_Test_V3_Params_t
{
    uint32_t BluetoothStackID;
    uint8_t TX_Channel;
    uint8_t Length_Of_Test_Data;
    uint8_t Packet_Payload;
    uint8_t PHY;
    uint8_t CTE_Length;
    uint8_t CTE_Type;
    uint8_t Length_Of_Switching_Pattern;
    uint8_t *Antenna_IDs;
    uint8_t *StatusResult;
} HCI_LE_Transmitter_Test_V3_Params_t;

#define HCI_LE_TRANSMITTER_TEST_V3_PARAMS_SIZE sizeof(HCI_LE_Transmitter_Test_V3_Params_t)


#endif /* __HCIAPI_PARAMS_H__ */
