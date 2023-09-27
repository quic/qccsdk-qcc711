/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include <string.h>
#include <stdbool.h>
#include "ipc.h"
#include "ipc_types.h"
#include "callback.h"
#include "qipc.h"
#include "qapi_task.h"
#include "qapi_power.h"
#include "stringl.h"
#include "ram.h"

extern uint32_t __IPC_MessageStart;
extern uint32_t __IPC_MessageEnd;

#define IPC_WAKEUP_PRIORITY QAPI_PWR_SHUTDOWN_CALLBACK_PRIORITY_DEFAULT

#define IPC_MESSAGE_RAM_START ((uint8_t *)&__IPC_MessageStart)
#define IPC_MESSAGE_RAM_END   ((uint8_t *)&__IPC_MessageEnd - 1)

#define MAX_CALLBACK_QUEUE_ENTRIES 32

#define SEND_FUNCTION_CALL_TIMEOUT 5000

typedef enum
{
    IPC_PACKET_STATE_HEADER,
    IPC_PACKET_STATE_DATA,
    IPC_PACKET_STATE_DROP_UNKNOWN
} IPC_Packet_State_t;

typedef struct IPC_Callback_Queue_Entry_s
{
    uint16_t FileID;
    uint16_t CallbackID;
    uint32_t ParamDataLength;
    uint8_t *ParamData;
} IPC_Callback_Queue_Entry_t;

/**
 * The global context of the Bluetopia IPC layer.
 */
typedef struct IPC_Context_s
{
    IPC_Packet_State_t PacketState;
    uint16_t PacketLength;
    uint16_t PendingCommandFile;
    uint16_t PendingCommandFunction;
    bool CommandAck;
    IPC_Callback_Queue_Entry_t CallbackQueue[MAX_CALLBACK_QUEUE_ENTRIES];
    uint8_t CallbackWriteIndex;
    uint8_t CallbackReadIndex;
    qapi_TSK_Handle_t CallbackTaskHandle;
    bool MessageAllocated;
    union
    {
        uint8_t HeaderBuffer[sizeof(IPC_Packet_Header_t)];
        IPC_Packet_Header_t Header;
        IPC_Command_Packet_t Command;
        IPC_Function_Response_Packet_t FunctionResponse;
        IPC_Error_Packet_t Error;
    } MessageData;
} IPC_Context_t;

typedef struct IPC_RetnContext_s
{
    bool Initialized;
    IPC_Error_Callback_t ErrorCallback;
    void *ErrorCallbackParameter;
    void *ShutdownCBHandle;
    uint32_t SharedRAMBlocks;
    qapi_PWR_Ballot_t Ballot;
} IPC_RetnContext_t;

#define IPC_CONTEXT_CALLBACK_QUEUE_EMPTY(_context)  (_context.CallbackReadIndex == _context.CallbackWriteIndex)
#define IPC_CONTEXT_CALLBACK_QUEUE_FULL(_context)   ((_context.CallbackReadIndex == 0) ? (_context.CallbackWriteIndex == MAX_CALLBACK_QUEUE_ENTRIES - 1 ) : (_context.CallbackWriteIndex == _context.CallbackReadIndex - 1))

static IPC_Context_t IPCContext;
static IPC_RetnContext_t IPCRetnContext __attribute__((section (".bss.retain")));

static qbool_t IPC_Shutdown_CB(void *UserParam);
static void IPC_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam);
static uint32_t IPC_Callback_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);
static void QIPC_Callback(const QIPC_Event_t *Event, void *UserParam);
static void IPC_ProcessRxData(bool StopOnResponse);

static qbool_t IPC_Shutdown_CB(void *UserParam)
{
    return true;
}

static void IPC_AckCallback(uint16_t FileID, uint16_t CallbackID, void *ParamData)
{
    int32_t                         Result;
    IPC_Callback_Response_Packet_t  Response;
    uint32_t                        Sent;

    Response.Header.Type = IPC_MESSAGE_TYPE_CALLBACK | IPC_MESSAGE_TYPE_RESPONSE_MASK;
    Response.Header.PacketLength = sizeof(IPC_Callback_Response_Packet_t) - sizeof(IPC_Packet_Header_t);
    Response.Header.FileID = FileID;
    Response.Header.FunctionID = CallbackID;
    Response.CallbackParamData = ParamData;

    Sent = 0;

    do
    {
        Result = QIPC_Send(((const uint8_t *)&Response) + Sent, sizeof(IPC_Callback_Response_Packet_t) - Sent);
        if(Result >= 0)
        {
            Sent += (uint32_t)Result;
        }
    } while((Result >= 0) && (Sent < sizeof(IPC_Callback_Response_Packet_t)));
}

static void IPC_Wakeup_CB(qbool_t ShutdownAborted, void *UserParam)
{
    if((!ShutdownAborted) && (IPCRetnContext.Initialized))
    {
        if(Callback_Initialize() == 0)
        {
            IPCContext.CallbackTaskHandle = qapi_TSK_Create_Task(IPC_Callback_Task, NULL);

            /* Re-share the blocks needed. */
            RAM_Share(RAM_SUBSYSTEM_BTSS_E, IPCRetnContext.SharedRAMBlocks, RAM_PERM_READ_WRITE_E);

            if(IPCContext.CallbackTaskHandle == NULL)
            {
                Callback_Shutdown();
                IPCRetnContext.Initialized = false;
            }
        }
        else
        {
            IPCRetnContext.Initialized = false;
        }
    }
}

static uint32_t IPC_Callback_Task(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    IPC_Callback_Queue_Entry_t     *Entry;

    while(!IPC_CONTEXT_CALLBACK_QUEUE_EMPTY(IPCContext))
    {
        Entry = &IPCContext.CallbackQueue[IPCContext.CallbackReadIndex];

        Callback_Process(Entry->FileID, Entry->CallbackID, Entry->ParamDataLength, Entry->ParamData);

        /* If there's parameter data, credit it back. */
        if(Entry->ParamData)
        {
            IPC_AckCallback(Entry->FileID, Entry->CallbackID, Entry->ParamData);
        }

        /* Advance the queue. */
        ++IPCContext.CallbackReadIndex;

        if(IPCContext.CallbackReadIndex == MAX_CALLBACK_QUEUE_ENTRIES)
        {
            IPCContext.CallbackReadIndex = 0;
        }
    }
    return QAPI_TSK_INFINITE_WAIT;
}

static void QIPC_Callback(const QIPC_Event_t *Event, void *UserParam)
{
    switch(Event->Type)
    {
        case QIPC_EVENT_TYPE_RECEIVED_E:
            /* We should only be in the callback context if we are not blocked on a command response,
             * thus we can simply drop any responses. */
            IPC_ProcessRxData(false);
            break;
        case QIPC_EVENT_TYPE_SENT_E:
            break;
    }
}

static void IPC_ProcessRxData(bool StopOnResponse)
{
    bool RxDone = false;
    uint16_t RxLength;
    qapi_Status_t Status;
    uint8_t DropBuffer[16];
    IPC_Error_Event_Data_t ErrorEventData;

    while(!RxDone)
    {
        switch(IPCContext.PacketState)
        {
            case IPC_PACKET_STATE_HEADER:
                RxLength = sizeof(IPC_Packet_Header_t) - IPCContext.PacketLength;

                Status = QIPC_Receive(&(IPCContext.MessageData.HeaderBuffer[IPCContext.PacketLength]), &RxLength);

                if(Status == QAPI_OK && RxLength > 0)
                {
                    IPCContext.PacketLength += RxLength;
                    if(IPCContext.PacketLength >= sizeof(IPC_Packet_Header_t))
                    {
                        switch(((IPC_Packet_Header_t *)IPCContext.MessageData.HeaderBuffer)->Type)
                        {
                            case IPC_MESSAGE_TYPE_FUNCTION | IPC_MESSAGE_TYPE_RESPONSE_MASK:
                                RxLength = sizeof(IPC_Function_Response_Packet_t);
                                break;
                            case IPC_MESSAGE_TYPE_CALLBACK:
                                RxLength = sizeof(IPC_Command_Packet_t);
                                break;
                            case IPC_MESSAGE_TYPE_ERROR:
                                RxLength = IPC_ERROR_PACKET_SIZE(0);
                                break;
                            default:
                                IPCContext.PacketState = IPC_PACKET_STATE_DROP_UNKNOWN;
                                break;
                        }

                        if(IPCContext.PacketState != IPC_PACKET_STATE_DROP_UNKNOWN)
                        {
                            if(RxLength <= IPCContext.MessageData.Header.PacketLength + sizeof(IPC_Packet_Header_t))
                            {
                                /* Packet looks valid, so start parsing the payload data. */
                                IPCContext.PacketState = IPC_PACKET_STATE_DATA;
                            }
                            else
                            {
                                /* Packet Length is invalid for the type, so drop the packet. */
                                IPCContext.PacketState = IPC_PACKET_STATE_DROP_UNKNOWN;
                            }
                        }
                    }
                }
                else
                    RxDone = true;

                break;
            case IPC_PACKET_STATE_DATA:
                RxLength = IPCContext.MessageData.Header.PacketLength - IPCContext.PacketLength + sizeof(IPC_Packet_Header_t);

                Status = QIPC_Receive(&(((uint8_t *)IPCContext.MessageData.HeaderBuffer)[IPCContext.PacketLength]), &RxLength);

                if(Status == QAPI_OK && RxLength > 0)
                {
                    IPCContext.PacketLength += RxLength;

                    if(IPCContext.PacketLength >= IPCContext.MessageData.Header.PacketLength + sizeof(IPC_Packet_Header_t))
                    {
                        switch(IPCContext.MessageData.Header.Type & IPC_MESSAGE_TYPE_TYPE_MASK)
                        {
                            case IPC_MESSAGE_TYPE_FUNCTION:
                                /* NOTE: The header check of the packet verified that this is also a RESPONSE message. */
                                if(StopOnResponse
                                    && (IPCContext.PendingCommandFile == IPCContext.MessageData.Header.FileID)
                                    && (IPCContext.PendingCommandFunction == IPCContext.MessageData.Header.FunctionID))
                                {
                                    RxDone = true;
                                    IPCContext.CommandAck = true;
                                }
                                break;
                            case IPC_MESSAGE_TYPE_CALLBACK:
                                if(!IPC_CONTEXT_CALLBACK_QUEUE_FULL(IPCContext))
                                {
                                    /* Copy the the packet data into the queue. */
                                    IPCContext.CallbackQueue[IPCContext.CallbackWriteIndex].FileID = IPCContext.MessageData.Command.Header.FileID;
                                    IPCContext.CallbackQueue[IPCContext.CallbackWriteIndex].CallbackID = IPCContext.MessageData.Command.Header.FunctionID;
                                    IPCContext.CallbackQueue[IPCContext.CallbackWriteIndex].ParamDataLength = IPCContext.MessageData.Command.ParamDataLength;
                                    IPCContext.CallbackQueue[IPCContext.CallbackWriteIndex].ParamData = IPCContext.MessageData.Command.ParamData;

                                    /* Advance the queue index. */
                                    ++IPCContext.CallbackWriteIndex;

                                    if(IPCContext.CallbackWriteIndex == MAX_CALLBACK_QUEUE_ENTRIES)
                                    {
                                        IPCContext.CallbackWriteIndex = 0;
                                    }

                                    /* Signal the Callback Task to process the new queue entry. */
                                    qapi_TSK_Signal_Task(IPCContext.CallbackTaskHandle, 1);
                                }
                                else
                                {
                                    if(IPCRetnContext.ErrorCallback)
                                    {
                                        ErrorEventData.ErrorEventType = IPC_ERROR_TYPE_CALLBACK_DROPPED_E;
                                        ErrorEventData.EventData.CallbackDroppedErrorData.FailedFileID = IPCContext.MessageData.Header.FileID;
                                        ErrorEventData.EventData.CallbackDroppedErrorData.FailedCallbackID = IPCContext.MessageData.Header.FunctionID;

                                        (*IPCRetnContext.ErrorCallback)(&ErrorEventData, IPCRetnContext.ErrorCallbackParameter);
                                    }

                                    if(IPCContext.MessageData.Command.ParamData)
                                    {
                                        IPC_AckCallback(IPCContext.MessageData.Header.FileID, IPCContext.MessageData.Header.FunctionID, IPCContext.MessageData.Command.ParamData);
                                    }
                                }
                                break;
                            case IPC_MESSAGE_TYPE_ERROR:
                                if((IPCContext.MessageData.Header.PacketLength >= IPC_ERROR_PACKET_SIZE(IPCContext.MessageData.Error.ErrorDataLength) - sizeof(IPC_Packet_Header_t)) && (IPCRetnContext.ErrorCallback != NULL))
                                {
                                    switch(IPCContext.MessageData.Error.ErrorCode)
                                    {
                                        case IPC_MESSAGE_ERROR_CODE_MEMORY_ALLOCATION:
                                            ErrorEventData.ErrorEventType = IPC_ERROR_TYPE_MEMORY_ALLOCATION_E;
                                            ErrorEventData.EventData.MemoryAllocationErrorData.FailedFileID = IPCContext.MessageData.Header.FileID;
                                            ErrorEventData.EventData.MemoryAllocationErrorData.FailedFunctionID = IPCContext.MessageData.Header.FunctionID;

                                            (*IPCRetnContext.ErrorCallback)(&ErrorEventData, IPCRetnContext.ErrorCallbackParameter);
                                            break;
                                    }
                                }
                                break;
                        }

                        IPCContext.PacketState = IPC_PACKET_STATE_HEADER;
                        IPCContext.PacketLength = 0;
                    }
                }
                else
                    RxDone = true;

                break;
            case IPC_PACKET_STATE_DROP_UNKNOWN:
                RxLength = sizeof(DropBuffer);

                Status = QIPC_Receive(DropBuffer, &RxLength);

                if(Status == QAPI_OK && RxLength > 0)
                {
                    IPCContext.PacketLength += RxLength;
                    if(IPCContext.PacketLength >= IPCContext.MessageData.Header.PacketLength + sizeof(IPC_Packet_Header_t))
                    {
                        IPCContext.PacketState = IPC_PACKET_STATE_HEADER;
                        IPCContext.PacketLength = 0;
                    }
                }
                else
                    RxDone = true;

                break;
        }
    }
}

/**
 * @brief Initialize the IPC layer.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Initialize(void)
{
    int ret_val = -1;

    if(!IPCRetnContext.Initialized)
    {
        IPCRetnContext.ShutdownCBHandle = qapi_PWR_Register_Shutdown_Callbacks(IPC_Shutdown_CB, IPC_Wakeup_CB, IPC_WAKEUP_PRIORITY, NULL);

        if(IPCRetnContext.ShutdownCBHandle != NULL)
        {
            IPCRetnContext.Ballot = qapi_PWR_Acquire_Ballot();
            if(IPCRetnContext.Ballot != 0)
            {
                /* Keep the core active while IPC is open, unless otherwise specified via IPC_Vote_Shutdown. */
                qapi_PWR_Vote_Local_State(IPCRetnContext.Ballot, QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);

                if(Callback_Initialize() == 0)
                {
                    if(QIPC_Open(QIPC_Callback, NULL) == QAPI_OK)
                    {
                        IPCContext.CallbackTaskHandle = qapi_TSK_Create_Task(IPC_Callback_Task, NULL);

                        if(IPCContext.CallbackTaskHandle != NULL)
                        {
                            IPCRetnContext.SharedRAMBlocks = RAM_AddressRangeToBlocks(IPC_MESSAGE_RAM_START, IPC_MESSAGE_RAM_END);
                            if(RAM_Share(RAM_SUBSYSTEM_BTSS_E, IPCRetnContext.SharedRAMBlocks, RAM_PERM_READ_WRITE_E) == QAPI_OK)
                            {
                                IPCRetnContext.Initialized = true;
                                ret_val = 0;
                            }
                            else
                            {
                                qapi_TSK_Delete_Task(IPCContext.CallbackTaskHandle);
                                QIPC_Close();
                            }
                        }
                        else
                        {
                            QIPC_Close();
                        }
                    }
                }
            }

            if(ret_val < 0)
            {
                Callback_Shutdown();
                qapi_PWR_Unregister_Callback(IPCRetnContext.ShutdownCBHandle);

                if(IPCRetnContext.Ballot != 0)
                {
                    qapi_PWR_Release_Ballot(IPCRetnContext.Ballot);
                }
            }
        }
    }

    return(ret_val);
}

/**
 * @brief Clean up the IPC layer.
 */
void IPC_Cleanup(void)
{
    if(IPCRetnContext.Initialized)
    {
        qapi_PWR_Unregister_Callback(IPCRetnContext.ShutdownCBHandle);
        qapi_PWR_Release_Ballot(IPCRetnContext.Ballot);
        qapi_TSK_Delete_Task(IPCContext.CallbackTaskHandle);
        Callback_Shutdown();
        QIPC_Close();

        memset(&IPCContext, 0, sizeof(IPC_Context_t));
        memset(&IPCRetnContext, 0, sizeof(IPC_RetnContext_t));
    }
}

/**
 * @brief Send a remote function call across the IPC Channel. This function will block until it receives a response
 *        from the remote processor.
 *
 * @param[in] FileID        The FileID of the remote function to call.
 * @param[in] FunctionID    The FunctionID within the file of the remote function to call.
 * @param[in] ParameterSize The length of any parameters to be sent along with the function call.
 * @param[in] Parameters    The parameters to send along with the function call.
 *
 * @return The value returned by the remote function, casted to a uint32.
 */
uint32_t IPC_SendFunctionCall(uint16_t FileID, uint16_t FunctionID, uint32_t ParameterSize, uint8_t *Parameters)
{
    uint32_t             ret_val;
    int32_t              Result;
    IPC_Command_Packet_t Command;
    uint32_t             Sent;
    uint32_t             Ticks;

    Command.Header.Type = IPC_MESSAGE_TYPE_FUNCTION;
    Command.Header.FileID = FileID;
    Command.Header.FunctionID = FunctionID;
    Command.Header.PacketLength = sizeof(IPC_Command_Packet_t) - sizeof(IPC_Packet_Header_t);
    Command.ParamData = Parameters;
    Command.ParamDataLength = ParameterSize;

    IPCContext.PendingCommandFile = FileID;
    IPCContext.PendingCommandFunction = FunctionID;
    IPCContext.CommandAck = false;

    Sent = 0;
    Ticks = qapi_TSK_Get_Tick_Count();

    do
    {
        Result = QIPC_Send(((const uint8_t *)&Command) + Sent, sizeof(IPC_Command_Packet_t) - Sent);
        if(Result >= 0)
        {
            Sent += (uint32_t)Result;
        }
    } while((Result >= 0) && (Sent < sizeof(IPC_Command_Packet_t) && (qapi_TSK_Get_Tick_Count() - Ticks < SEND_FUNCTION_CALL_TIMEOUT)));

    /* Poll receiving data over IPC into the command is acknowledged. */
    while((Result >= 0) && (!IPCContext.CommandAck && qapi_TSK_Get_Tick_Count() - Ticks < SEND_FUNCTION_CALL_TIMEOUT))
    {
        /* TODO: We could potentially make use of a WFI to allow less spinning. */
        IPC_ProcessRxData(true);
    }

    if(!IPCContext.CommandAck)
        ret_val = (uint32_t)QAPI_ERROR;
    else
        ret_val = IPCContext.MessageData.FunctionResponse.Return;

    return ret_val;
}

/**
 * @brief Obtain a memory buffer which is shared with the remote processor.
 *
 * @return A pointer to the shared memory buffer or NULL if one could not be acquired.
 */
void *IPC_GetSharedMemory(uint32_t Size)
{
    /* Ensure the message will fit in shared RAM. */
    if(IPC_MESSAGE_RAM_START + Size <= IPC_MESSAGE_RAM_END && !IPCContext.MessageAllocated)
    {
        /* Since the APSS IPC module only allocated shared message RAM for Function calls,
         * and there can only be a singled APSS->BTSS Function call outstanding at a time,
         * we can simply use the entire shared region for each message. */
        return(IPC_MESSAGE_RAM_START);
    }
    return NULL;
}

/**
 * @brief Free a previously allocated shared memory buffer.
 */
void IPC_FreeSharedMemory(void *Memory)
{
    IPCContext.MessageAllocated = false;
}

/**
 * @brief Registers a callback with the IPC module to be notified when an IPC Error occurs.
 *
 * @param[in] ErrorCallback     Function pointer to receive callbacks when an IPC error occurs
 * @param[in] CallbackParameter Parameter to be passed to the Error Callback.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Register_Error_Callback(IPC_Error_Callback_t ErrorCallback, void *CallbackParameter)
{
    int ret_val;

    if(ErrorCallback)
    {
        if(IPCRetnContext.ErrorCallback)
        {
            ret_val = -1;
        }
        else
        {
            ret_val = 0;
            IPCRetnContext.ErrorCallback = ErrorCallback;
            IPCRetnContext.ErrorCallbackParameter = CallbackParameter;
        }
    }
    else
    {
        IPCRetnContext.ErrorCallback = NULL;
        IPCRetnContext.ErrorCallbackParameter = NULL;
        ret_val = 0;
    }

    return ret_val;
}

/**
 * @brief Vote/un-vote for Shutdown of the processor
 *
 * @param[in] Shutdown Indicates whether to vote to allow shutdown.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Vote_Shutdown(bool Shutdown)
{
    return qapi_PWR_Vote_Local_State(IPCRetnContext.Ballot, Shutdown?QAPI_PWR_STATE_SHUTDOWN_E:QAPI_PWR_STATE_ACTIVE_E, QAPI_PWR_NO_WAKE);
}
