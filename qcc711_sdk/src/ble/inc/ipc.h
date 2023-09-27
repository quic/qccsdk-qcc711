/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __IPCH__
#define __IPCH__

#include <stdint.h>
#include <stdbool.h>

#define ALIGN32(_offset) ((((_offset) & 0x03) == 0) ? (_offset) : (((_offset) & ~(0x3)) + 4))

/**
 * Enumeration which defined which type of IPC Error Event is received.
 */
typedef enum
{
    IPC_ERROR_TYPE_MEMORY_ALLOCATION_E, /**< Indicates the remote processor failed to allocate shared memory for an IPC event. */
    IPC_ERROR_TYPE_CALLBACK_DROPPED_E /**< Indicates that an asynchronous callback was dropped do to the processing queue being full . */
} IPC_Error_Event_Type_t;

/**
 * Structure of the data returned in an IPC Memory Allocation Error event.
 */
typedef struct IPC_Memory_Allocation_Error_Event_Data_s
{
    uint16_t FailedFileID;      /**< Indicates the FileID of the message that failed to allocate. */
    uint16_t FailedFunctionID;  /**< Indicated the Function/CallbackID of the message that failed to allocate. */
} IPC_Memory_Allocation_Error_Event_Data_t;

/**
 * Structure of the data returned in an IPC Callback Dropped Error event.
 */
typedef struct IPC_Callback_Dropped_Error_Event_Data_s
{
    uint16_t FailedFileID;      /**< Indicates the FileID of the message that failed to allocate. */
    uint16_t FailedCallbackID;  /**< Indicated the Callback/CallbackID of the message that failed to allocate. */
} IPC_Callback_Dropped_Error_Event_Data_t;

/**
 * Structure of the data returned in an IPC Error event.
 */
typedef struct IPC_Error_Event_Data_s
{
    IPC_Error_Event_Type_t ErrorEventType; /**< The type of IPC Error received. */
    union {
        IPC_Memory_Allocation_Error_Event_Data_t MemoryAllocationErrorData;
        IPC_Callback_Dropped_Error_Event_Data_t CallbackDroppedErrorData;
    } EventData; /**< The data associated with individual event. */
} IPC_Error_Event_Data_t;

/**
 * @brief Callback prototype for an IPC Error Callback function.
 *
 * @param[in] EventData         The data associated with the IPC Error Event.
 * @param[in] CallbackParameter The parameter given by the application when the callback was registered.
 */
typedef void (* IPC_Error_Callback_t)(const IPC_Error_Event_Data_t *EventData, void *CallbackParameter);

/**
 * @brief Initialize the IPC layer.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Initialize(void);

/**
 * @brief Clean up the IPC layer.
 */
void IPC_Cleanup(void);

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
uint32_t IPC_SendFunctionCall(uint16_t FileID, uint16_t FunctionID, uint32_t ParameterSize, uint8_t *Parameters);

/**
 * @brief Obtain a memory buffer which is shared with the remote processor.
 *
 * @return A pointer to the shared memory buffer or NULL if one could not be acquired.
 */
void *IPC_GetSharedMemory(uint32_t Size);

/**
 * @brief Free a previously allocated shared memory buffer.
 */
void IPC_FreeSharedMemory(void *Memory);

/**
 * @brief Registers a callback with the IPC module to be notified when an IPC Error occurs.
 *
 * @param[in] ErrorCallback     Function pointer to receive callbacks when an IPC error occurs
 * @param[in] CallbackParameter Parameter to be passed to the Error Callback.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Register_Error_Callback(IPC_Error_Callback_t ErrorCallback, void *CallbackParameter);

/**
 * @brief Vote/un-vote for Shutdown of the processor
 *
 * @param[in] Shutdown Indicates whether to vote to allow shutdown.
 *
 * @return Zero if successful or a negative value if there was an error.
 */
int IPC_Vote_Shutdown(bool Shutdown);
#endif /* __IPCH__ */


