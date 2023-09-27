/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef __CALLBACKH__
#define __CALLBACKH__

#include <stdint.h>
#include <stdbool.h>

typedef struct _tagCallbackInfo_t
{
   uint16_t FileID;
   uint16_t CallbackID;
   uintptr_t CallbackKey;
   void *AppFunction;
   uint32_t AppParam;
} CallbackInfo_t;

#define CALLBACKINFO_SIZE                                   sizeof(CallbackInfo_t)

/**
   Definition of a function which handles parsing the callback.

   @param Handle         Handle of the callback info.
   @param CallbackInfo   Information for the callback function.
   @param BufferLength   Length of the packed data.
   @param Buffer         Buffer of the packed data for the callback.
*/

typedef void (*CallbackHandler_t)(uint32_t Handle, CallbackInfo_t *CallbackInfo, uint16_t BufferLength, uint8_t *Buffer);

/**
   Initiializes the callback module.

   @return the status result of the parser initialization.
*/
int Callback_Initialize(void);

/**
   Shuts down the callback module.
*/
void Callback_Shutdown(void);

/**
   Registers a callback function with the provided information.

   @param CallbackHandle Pointer to where the callback handle will be stored upon
                         successful return.
   @param CallbackParser Function that will handle parsing the callback.
   @param CallbackInfo   Information for the callback to be registered.  The
                         ModuleID, FileID, CallbackID, and AppFunction must all be valid.

   @return Zero if the callback was registered successfully or a negative
           value if there was an error.
*/
int Callback_Register(uint32_t *CallbackHandle, CallbackHandler_t CallbackHandler, const CallbackInfo_t *CallbackInfo, bool AllowDuplicates);

/**
   Updates the callback key for a registered callback function.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackKey    The new value for the callback key.

   @return Zero if the callback was found successfully or a negative value
           if there was an error.
*/
int Callback_UpdateKey(uint32_t CallbackHandle, uintptr_t CallbackKey);

/**
   Retrieves the callback info for the specified handle.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackInfo   Information for the callback.

   @return Zero if the callback was found successfully or a negative value
           if there was an error.
*/
int Callback_Retrieve(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo);

/**
   Unregisters a callback function based on the callback key and identifiers.

   @param FileID      ID of the callback's file to unregister.
   @param CallbackID  ID of the callback's type to unregister.
   @param CallbackKey Key specific to the callback to unregister.
*/
void Callback_UnregisterByKey(uint16_t FileID, uint16_t CallbackID, uintptr_t CallbackKey);

/**
   Unregisters a callback function based on the CallbackHandle returned from
   Callback_Register().

   @param CallbackHandle Handle of the callback to unregister.
*/
void Callback_UnregisterByHandle(uint32_t CallbackHandle);

/**
   Sets callback info at a specific Callback Handle. This is mainly useful for restoring saved callbacks.

   @param[in] CallbackHandle The handle to set the Callback Info for.
   @param[in] CallbackHandler The function to handle callbacks.
   @param[in] CallbackInfo Information for the callback.

   @return Zero if the callback was registered successfully or a negative
           value if there was an error.
*/
int Callback_SetByHandle(uint32_t CallbackHandle, CallbackHandler_t CallbackHandler, const CallbackInfo_t *CallbackInfo);

/**
   Processes callback data received from a remote device. It will invoke the
   correct parser for the callback function.

   @param FileID       ID of the callback's file.
   @param EventID      ID of the callback's event.
   @param BufferLength Length of the buffer that was received.
   @param Buffer       Data that was received.  Note that it is expected that
                       the callback ID is packed into the begining of this
                       buffer.
*/
void Callback_Process(uint16_t FileID, uint16_t EventID, uint32_t BufferLength, uint8_t *Buffer);

/**
    Allows a callback to be flagged as persistent across clear operations (unless forced).
    This gives registrees the ability to register callbacks that may still be functional
    even if the BluetoothStack is invalidated (i.e. entering BTSS Low Power Mode).

    @param CallbackHandle   Callback handle returned from a successful registration
    @param Persist          Indicates of the callback should persists across soft clears
*/
void Callback_SetPersist(uint32_t CallbackHandle, bool Persist);

/**
   Erases all registered callbacks.

   @param force     Erases all callbacks regardless of their "persist" status
*/
void Callback_ClearAll(bool Force);

#endif /* __CALLBACKH__ */
