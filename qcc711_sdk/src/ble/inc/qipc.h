/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file QIPC.h
   @brief Basic IPC interface.

   This module provides standard a simple interface for interrocessor
   communication.
*/

#ifndef __QIPC_H__
#define __QIPC_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration of events that can be generated by the QIPC module.
*/
typedef enum
{
   QIPC_EVENT_TYPE_RECEIVED_E, /**< Indicates data was received. */
   QIPC_EVENT_TYPE_SENT_E      /**< Indicates data was sent. */
} QIPC_EventType_t;

/**
   Information for a QIPC_EVENT_TYPE_SENT_E event.
*/
typedef struct QIPC_Sent_s
{
   uint16_t BytesFree; /**< Space available in the transmit buffer when the callback function was
                            called. */
} QIPC_Sent_t;

/**
   Information for a QIPC event.
*/
typedef struct QIPC_Event_s
{
   QIPC_EventType_t Type;       /**< Type of event.  This value can be used to determine which member of the
                                     Data union is applicable. */
   union
   {
      QIPC_Sent_t     Sent;     /**< Information for a QIPC_EVENT_TYPE_SENT_E event. */
   } Data;                      /**< Information for the event. The applicable member is determined by the value
                                     of the EventType. */
} QIPC_Event_t;

/**
   @brief Prototype for a function called to signal a QIPC event.

   @param[in] Event      Information for the event.
   @param[in] UserParam  User specified callback parameter.
*/
typedef void (*QIPC_Callback_t)(const QIPC_Event_t *Event, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Opens the IPC interface.

   @param[in] Callback   Function called to signal a QIPC event.
   @param[in] UserParam  User specified callback parameter.

   @return QAPI_OK if the module was initialized successfully or a negative
           value if there was an error.
*/
qapi_Status_t QIPC_Open(QIPC_Callback_t Callback, void *UserParam);

/**
   @brief Closes the IPC interface.
*/
void QIPC_Close(void);

/**
   @brief Sends data over the IPC interface.

   @param[in] Buffer  Pointer to the data to be sent.
   @param[in] Length  Amount of data to be sent.

   @return The amount of data that was sent if successfulor a negative
           value if there was an error.
*/
int32_t QIPC_Send(const uint8_t *Buffer, uint16_t Length);

/**
   @brief Polls the IPC interface for data, allowing for blocking use
          of the transport

   @param[in] Buffer  Pointer to a buffer to receive data into.
   @param[in/out] Length  The length of the receive buffer on input and the length of the copied data on output.

   @return QAPI_OK if the module was initialized successfully or a negative
           value if there was an error.
*/
qapi_Status_t QIPC_Receive(uint8_t *Buffer, uint16_t *Length);


#endif

