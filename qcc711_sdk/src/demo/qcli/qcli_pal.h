/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QCLI_PAL_H__
#define __QCLI_PAL_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qapi_status.h"
#include "stringl.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/**
   Character that is inpretted as an end of line for inputs from the console.
*/
#define PAL_INPUT_END_OF_LINE_CHARACTER                     ('\r')

/**
   String that is used as the end of line for outputs to the console.
*/
#define PAL_OUTPUT_END_OF_LINE_STRING                       ("\r\n")

/**
   Indicates received characters should be echoed to the console.
*/
#define PAL_ECHO_CHARACTERS                                 (true)


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 *-----------------------------------------------------------------------*/

/**
   @brief Initialize the UART used by the demo.

   @return true if the UART was initailized successfully or false if there was
           an error.
*/
qbool_t PAL_Uart_Init(uint32_t id);

/**
   @brief Initializing the individual sample applications.
*/
void Initialize_Samples(void);

/**
   @brief Cleanup the individual sample applications before exitting.
*/
void Cleanup_Samples(void);

/**
   @brief Get the Instance of the UART used for the console.

   @return The instance identifier of the UART used by the console.
*/
int32_t PAL_Uart_Instance_Get(void);

/**
   @brief Turns off the UART used by the demo.

   @return true if the UART was deinitailized successfully or false if there was
           an error.
*/
qbool_t PAL_Uart_Deinit(void);


/**
   @brief Writes a buffer to the console.

   All data from this buffer will be written to the console or buffered locally
   before this function returns.

   @param Length[in]  Length of the data to be wr itten.
   @param Buffer[in]  Buffer to be written to the console.
*/
void PAL_Console_Write(uint32_t Length, const char *Buffer);

/**
   @brief Allocates a block of memory from the heap.

   @param[in] Size  Minimum size of the memory block to allocate.

   @return A pointer to the allocated memory or NULL if there was an error.
*/
void *PAL_Malloc(size_t Length);

/**
   @brief Frees a block of memory from the heap.

   @param[in] Pointer  Block to free as returned by a call to PAL_Malloc().
*/
void PAL_Free(void *Pointer);

/**
   @brief Takes a lock for re-entrancy protection for the QCLI module.

   This module expects the lock to behave like a mutex. It should support
   recursively taking the lock and, for threaded platforms, block until the lock
   can be taken as applicable.

   @return
    - true if the lock was taken successfully
    - false if the lock was not taken successfully
*/
qbool_t PAL_Take_Lock(void);

/**
   @brief Releases a lock taken with PAL_Take_Lock().
*/
void PAL_Release_Lock(void);

/**
   @brief Votes for local power state using PAL ballot.

   This state is entered the next time a WFI is executed. If the vote is
   shutdown (EnableShutdown is true), the WakeTime indicate when the
   caller needs the subsystem to wake.

   @param[in] EnableShutdown  TRUE if shutdown should be enabled, FALSE if shutdown
                              should be disabled.
   @param[in] WakeTime  Time that the voter requires the system to wake in
                        milliseconds relative to the current time. Use
                        #QAPI_PWR_NO_WAKE if this time is not to be used to set
                        a wakeup. If SleepTime is greater than
                        #QAPI_PWR_MAX_WAKE_TIME, #QAPI_PWR_MAX_WAKE_TIME is
                        used instead.

   @return QAPI_OK if the vote was cast successfully, or a negative value if
           there was an error.
*/
qapi_Status_t PAL_Vote_Local_Power_State(qbool_t EnableShutdown, uint32_t WakeTime);

#endif

