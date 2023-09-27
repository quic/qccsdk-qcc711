/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __IPCTYPESH__
#define __IPCTYPESH__

#include <stdint.h>

#define IPC_MESSAGE_TYPE_TYPE_MASK      0x7FFF
#define IPC_MESSAGE_TYPE_RESPONSE_MASK  0x8000
#define IPC_MESSAGE_TYPE_FUNCTION       0x0001
#define IPC_MESSAGE_TYPE_CALLBACK       0x0002
#define IPC_MESSAGE_TYPE_ERROR          0x0003

#define IPC_MESSAGE_ERROR_CODE_MEMORY_ALLOCATION    0x00000001

/**
 * Structure of the header data common to all IPC packets.
 */
typedef struct IPC_Packet_Header_s
{
    uint16_t Type; /**< The type of message. Indicates whether it is a function/callback w/ a bit to denote a response message. */
    uint16_t FileID; /**< File ID associated with the IPC call. */
    uint16_t FunctionID; /**< The FunctionID/CallbackID associated with the File */
    uint16_t PacketLength;
} IPC_Packet_Header_t;

#define IPC_PACKET_HEADER_SIZE  (sizeof(IPC_Packet_Header_t))

/**
 * Structure of the message data specific to a Function/Callback packet (non-response)
 */
typedef struct IPC_Command_Packet_s
{
    IPC_Packet_Header_t Header;
    uint32_t ParamDataLength; /**< Indicates the amount of extra parameter data located in shared memory. */
    uint8_t *ParamData; /**< Indicates the location of extra parameter data in shared memory, or NULL if there is none. */
} IPC_Command_Packet_t;

#define IPC_COMMAND_PACKET_SIZE (sizeof(IPC_Command_Packet_t))

/**
 * Structure of the message data specific to a response message to a function command.
 */
typedef struct IPC_Function_Response_Packet_s
{
    IPC_Packet_Header_t Header;
    uint32_t Return; /**< The return value of the function. Ignored if the function is void. */
} IPC_Function_Response_Packet_t;

#define IPC_FUNCTION_RESPONSE_PACKET_SIZE (sizeof(IPC_Function_Response_Packet_t))

/**
 * Structure of the message data specific to a response message to an asynchronous callback message.
 */
typedef struct IPC_Callback_Response_Packet_s
{
    IPC_Packet_Header_t Header;
    uint8_t *CallbackParamData; /**< A pointer ot the parameter data returned in the event. (Credits the buffer back). */
} IPC_Callback_Response_Packet_t;

#define IPC_CALLBACK_RESPONSE_PACKET_SIZE (sizeof(IPC_Callback_Response_Packet_t))

typedef struct IPC_Error_Packet_s
{
    IPC_Packet_Header_t Header;
    uint32_t ErrorCode;
    uint32_t ErrorDataLength;
    uint8_t ErrorData[1];
} IPC_Error_Packet_t;

#define IPC_ERROR_PACKET_SIZE(_ExtraLen)    ((sizeof(IPC_Error_Packet_t) - 1) + (_ExtraLen))

#endif /* __IPCTYPESH__ */
