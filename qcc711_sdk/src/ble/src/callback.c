/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include <string.h>
#include "stringl.h"
#include "qapi_heap.h"
#include "callback.h"

#define CALLBACK_LIST_INITIAL_SIZE                                      (16)

typedef struct CallbackListEntry_s
{
    CallbackHandler_t Handler;
    CallbackInfo_t   Info;
    bool Persist;
} CallbackListEntry_t;

typedef struct CallbackContext_s
{
    CallbackListEntry_t *CallbackList;
    uint32_t             CallbackListSize;
} CallbackContext_t;

#define CALLBACK_LIST_ALLOC_SIZE(__size__)   (sizeof(CallbackListEntry_t) * (__size__))

static CallbackContext_t *CallbackContext;

static int Callback_ResizeCallbackList(void);

/**
  Resizes the parser callback list.

  @return the status result for resizing the list.
  */
static int Callback_ResizeCallbackList(void)
{
    uint32_t             NewSize;
    int          ret_val;
    CallbackListEntry_t *NewList;

    /* Double the size of the callback list. */
    NewSize = CallbackContext->CallbackListSize * 2;

    NewList = qapi_Malloc(CALLBACK_LIST_ALLOC_SIZE(NewSize));

    if(NewList != NULL)
    {
        /* Copy the old list.*/
        memscpy(NewList, CALLBACK_LIST_ALLOC_SIZE(NewSize), CallbackContext->CallbackList, CALLBACK_LIST_ALLOC_SIZE(CallbackContext->CallbackListSize));

        /* Initialize the new portion of the list. */
        memset(NewList + CallbackContext->CallbackListSize, 0, CALLBACK_LIST_ALLOC_SIZE(NewSize - CallbackContext->CallbackListSize));

        /* Free the old list. */
        qapi_Free(CallbackContext->CallbackList);

        /* Point to the new list and update the size. */
        CallbackContext->CallbackList     = NewList;
        CallbackContext->CallbackListSize = NewSize;

        ret_val = 0;
    }
    else
    {
        ret_val = -1;
    }

    return(ret_val);
}

/**
   Initiializes the callback module.

   @return the status result of the parser initialization.
*/
int Callback_Initialize(void)
{
    int ret_val = -1;

    if(CallbackContext == NULL)
    {
        if((CallbackContext = qapi_Malloc(sizeof(CallbackContext_t))) != NULL)
        {
            /* Allocate the initial callback list. */
            CallbackContext->CallbackListSize = CALLBACK_LIST_INITIAL_SIZE;
            CallbackContext->CallbackList     = (CallbackListEntry_t *)qapi_Malloc(CALLBACK_LIST_ALLOC_SIZE(CallbackContext->CallbackListSize));

            if(CallbackContext->CallbackList != NULL)
            {
                /* Initialize the callback list. */
                memset(CallbackContext->CallbackList, 0, CALLBACK_LIST_ALLOC_SIZE(CallbackContext->CallbackListSize));

                ret_val = 0;
            }
        }

        if(ret_val < 0)
        {
            Callback_Shutdown();
        }
    }

    return(ret_val);
}

/**
   Shuts down the callback module.
*/
void Callback_Shutdown(void)
{
    if(CallbackContext != NULL)
    {
        qapi_Free(CallbackContext->CallbackList);
        qapi_Free(CallbackContext);

        CallbackContext = NULL;
    }
}

#define CALLBACK_INFO_MATCH(_cb1, _cb2) ( ((_cb1)->FileID == (_cb2)->FileID) && \
                                          ((_cb1)->CallbackID == (_cb2)->CallbackID) && \
                                          ((_cb1)->AppFunction == (_cb2)->AppFunction) && \
                                          ((_cb1)->AppParam == (_cb2)->AppParam) && \
                                          ((_cb1)->CallbackKey == (_cb2)->CallbackKey) )
/**
   Registers a callback function with the provided information.

   @param CallbackHandle Pointer to where the callback handle will be stored upon
                         successful return.
   @param CallbackParser Function that will handle parsing the callback.
   @param CallbackInfo   Information for the callback to be registered.  The
                         ModuleID, FileID, CallbackID, and AppFunction must all be valid.

   @return ssSuccess if the callback was registered successfully or a negative
           value if there was an error.
*/
int Callback_Register(uint32_t *CallbackHandle, CallbackHandler_t CallbackHandler, const CallbackInfo_t *CallbackInfo, bool AllowDuplicates)
{
    uint32_t             Index;
    uint32_t             CallbackIndex;
    int                  ret_val = 0;
    CallbackListEntry_t *Entry;
    CallbackListEntry_t *MatchEntry;
    CallbackListEntry_t *NullEntry;

    /* Initialize the module if it hasn't been initialized yet. */
    if (CallbackContext == NULL)
        Callback_Initialize();

    /* Verify the module is initialized and the parameters are valid. */
    if((CallbackContext != NULL) && (CallbackHandle != NULL) && (CallbackHandler != NULL) && (CallbackInfo != NULL) && (CallbackInfo->AppFunction != NULL))
    {
        MatchEntry    = NULL;
        NullEntry     = NULL;
        CallbackIndex = CallbackContext->CallbackListSize;

        /* Search for an available entry in the callback list. */
        for(Index = 0; Index < CallbackContext->CallbackListSize; Index ++)
        {
            Entry = &(CallbackContext->CallbackList[Index]);

            if(AllowDuplicates && CALLBACK_INFO_MATCH(&Entry->Info, CallbackInfo))
            {
                MatchEntry    = Entry;
                CallbackIndex = Index;
                break;
            }

            /* If a callback entry is available or it matches the current callback configuration. */
            if((Entry->Handler == NULL) && (NullEntry == NULL))
            {
               NullEntry     = Entry;
               CallbackIndex = Index;

               if(!AllowDuplicates)
                   break;
            }
        }

        if(AllowDuplicates && MatchEntry)
            Entry = MatchEntry;
        else
            Entry = NullEntry;

        if(Entry)
        {
            /* Store the callback entry. */
            Entry->Handler = CallbackHandler;
            memscpy(&(Entry->Info), sizeof(CallbackInfo_t), CallbackInfo, sizeof(CallbackInfo_t));
            Entry->Persist = false;

            /* Return the handle to the caller. */
            *CallbackHandle = CallbackIndex;
        }
        else
        {
            /* If we could not add the callback entry because the list is full. */
            Index = CallbackContext->CallbackListSize;

            /* Resize the list so we can add the callback entry. */
            ret_val = Callback_ResizeCallbackList();

            /* If an error has not occured. */
            if(ret_val == 0)
            {
                /* Store the callback entry. */
                CallbackContext->CallbackList[Index].Handler = CallbackHandler;
                memscpy(&(CallbackContext->CallbackList[Index].Info), sizeof(CallbackInfo_t), CallbackInfo, sizeof(CallbackInfo_t));
                CallbackContext->CallbackList[Index].Persist = false;

                /* Return the handle to the caller. */
                *CallbackHandle = Index;
            }
        }
    }
    else
    {
        ret_val = -1;
    }

    return(ret_val);
}

/**
   Sets callback info at a specific Callback Handle. This is mainly useful for restoring saved callbacks.

   @param[in] CallbackHandle The handle to set the Callback Info for.
   @param[in] CallbackHandler The function to handle callbacks.
   @param[in] CallbackInfo Information for the callback.

   @return Zero if the callback was registered successfully or a negative
           value if there was an error.
*/
int Callback_SetByHandle(uint32_t CallbackHandle, CallbackHandler_t CallbackHandler, const CallbackInfo_t *CallbackInfo)
{
    int ret_val = -1;
    uint32_t             NewSize;
    CallbackListEntry_t *NewList;

    if(CallbackContext != NULL)
    {
        if(CallbackContext->CallbackListSize < CallbackHandle)
        {
            /* Resize the list to fit the handle value. */
            NewSize = CallbackHandle + 1;

            NewList = qapi_Malloc(CALLBACK_LIST_ALLOC_SIZE(NewSize));

            if(NewList != NULL)
            {
                /* Copy the old list.*/
                memscpy(NewList, CALLBACK_LIST_ALLOC_SIZE(NewSize), CallbackContext->CallbackList, CALLBACK_LIST_ALLOC_SIZE(CallbackContext->CallbackListSize));

                /* Initialize the new portion of the list. */
                memset(NewList + CallbackContext->CallbackListSize, 0, CALLBACK_LIST_ALLOC_SIZE(NewSize - CallbackContext->CallbackListSize));

                /* Free the old list. */
                qapi_Free(CallbackContext->CallbackList);

                /* Point to the new list and update the size. */
                CallbackContext->CallbackList     = NewList;
                CallbackContext->CallbackListSize = NewSize;
            }
            else
            {
                return -1;
            }
        }

        CallbackContext->CallbackList[CallbackHandle].Handler = CallbackHandler;
        memscpy(&CallbackContext->CallbackList[CallbackHandle].Info, sizeof(CallbackInfo_t), CallbackInfo, sizeof(CallbackInfo_t));

        ret_val = 0;
    }

    return ret_val;
}

/**
   Updates the callback key for a registered callback function.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackKey    The new value for the callback key.

   @return ssSuccess if the callback was found successfully or a negative value
           if there was an error.
*/
int Callback_UpdateKey(uint32_t CallbackHandle, uintptr_t CallbackKey)
{
    int ret_val;

    /* Verify the module is initialized and the parameters are valid. */
    if((CallbackContext != NULL) && (CallbackHandle < CallbackContext->CallbackListSize))
    {
        /* Make sure the callback ID is in use. */
        if(CallbackContext->CallbackList[CallbackHandle].Handler != NULL)
        {
            CallbackContext->CallbackList[CallbackHandle].Info.CallbackKey = CallbackKey;

            ret_val = 0;
        }
        else
        {
            ret_val = -1;
        }
    }
    else
    {
        ret_val = -1;
    }

    return(ret_val);
}

/**
   Retrieves the callback info for the specified handle.

   @param CallbackHandle Callback handle returned from successful registration.
   @param CallbackInfo   Information for the callback.

   @return ssSuccess if the callback was found successfully or a negative value
           if there was an error.
*/
int Callback_Retrieve(uint32_t CallbackHandle, CallbackInfo_t *CallbackInfo)
{
    int ret_val;

    /* Verify the module is initialized and the parameters are valid. */
    if((CallbackContext != NULL) && (CallbackHandle < CallbackContext->CallbackListSize))
    {
        /* Make sure the callback ID is in use. */
        if(CallbackContext->CallbackList[CallbackHandle].Handler != NULL)
        {
            /* Copy the callback info. */
            memscpy(CallbackInfo, sizeof(CallbackInfo_t), &(CallbackContext->CallbackList[CallbackHandle].Info), sizeof(CallbackInfo_t));
            ret_val = 0;
        }
        else
        {
            ret_val = -1;
        }
    }
    else
    {
        ret_val = -1;
    }

    return(ret_val);
}

/**
   Unregisters a callback function based on the callback key and identifiers.

   @param FileID      ID of the callback's file to unregister.
   @param CallbackID  ID of the callback's type to unregister.
   @param CallbackKey Key specific to the callback to unregister.
*/
void Callback_UnregisterByKey(uint16_t FileID, uint16_t CallbackID, uintptr_t CallbackKey)
{
    uint32_t Index;

    /* Verify the module is initialized and the parameters are valid. */
    if(CallbackContext != NULL)
    {
        /* Search for the entry in the callback list. */
        for(Index = 0; Index < CallbackContext->CallbackListSize; Index ++)
        {
            /* Match to the given parameters. */
            if((CallbackContext->CallbackList[Index].Info.FileID == FileID) && (CallbackContext->CallbackList[Index].Info.CallbackID == CallbackID) && (CallbackContext->CallbackList[Index].Info.CallbackKey == CallbackKey))
            {
                /* Found an available entry. */
                break;
            }
        }

        if(Index < CallbackContext->CallbackListSize)
        {
            /* Memset the entry to unregister it. */
            memset(&(CallbackContext->CallbackList[Index]), 0, sizeof(CallbackListEntry_t));
        }
    }
}

/**
   Unregisters a callback function based on the CallbackHandle returned from
   Callback_Register().

   @param CallbackHandle Handle of the callback to unregister.
*/
void Callback_UnregisterByHandle(uint32_t CallbackHandle)
{
    /* Verify the module is initialized and the parameters are valid. */
    if((CallbackContext != NULL) && (CallbackHandle < CallbackContext->CallbackListSize))
    {
        /* Entry found, memset it to unregister it. */
        memset(&(CallbackContext->CallbackList[CallbackHandle]), 0, sizeof(CallbackListEntry_t));
    }
}

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
void Callback_Process(uint16_t FileID, uint16_t EventID, uint32_t BufferLength, uint8_t *Buffer)
{
    uint32_t Index;

    if(CallbackContext != NULL)
    {
        for(Index = 0; Index < CallbackContext->CallbackListSize; Index++)
        {
            if((CallbackContext->CallbackList[Index].Info.FileID == FileID) && (CallbackContext->CallbackList[Index].Info.CallbackID == EventID) && (CallbackContext->CallbackList[Index].Handler != NULL))
            {
                CallbackContext->CallbackList[Index].Handler(Index, &(CallbackContext->CallbackList[Index].Info), BufferLength, Buffer);
                break;
            }
        }
    }
}

void Callback_SetPersist(uint32_t CallbackHandle, bool Persist)
{
    if(CallbackContext != NULL && CallbackHandle < CallbackContext->CallbackListSize)
    {
        CallbackContext->CallbackList[CallbackHandle].Persist = Persist;
    }
}

/**
   Erases all registered callbacks.

   @param force     Erases all callbacks regardless of their "persist" status
*/
void Callback_ClearAll(bool Force)
{
    uint32_t Index;

    if(CallbackContext != NULL && CallbackContext->CallbackList != NULL)
    {
        if(Force)
        {
            /* Simply memset the list to remove all registrations. We'll keep the list itself around until Shutdown. */
            memset(CallbackContext->CallbackList, 0, CallbackContext->CallbackListSize * sizeof(CallbackListEntry_t));
        }
        else
        {
            for(Index = 0; Index < CallbackContext->CallbackListSize; ++Index)
            {
                if(!CallbackContext->CallbackList[Index].Persist)
                {
                    memset(&CallbackContext->CallbackList[Index], 0, sizeof(CallbackListEntry_t));
                }
            }
        }
    }
}
