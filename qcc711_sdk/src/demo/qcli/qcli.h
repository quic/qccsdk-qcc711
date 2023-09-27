/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QCLI_H__  // [
#define __QCLI_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"
#include "qcli_api.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/**
   Determines the size of the input buffer for CLI commands. It effectively
   controls the maximum length of a command and its parameters.
*/
#define QCLI_MAXIMUM_QCLI_COMMAND_STRING_LENGTH    (2048)

/**
   Determines the maximum number of parameters that can be provided. Note that
   this may also include parameters used to navigate into groups.
*/
#define QCLI_MAXIMUM_NUMBER_OF_PARAMETERS          (17)

/**
   Determines the size of the buffer used for formatted messages to the console
   when using QCLI_Printf.
*/
#define QCLI_MAXIMUM_PRINTF_LENGTH                 (2048)

/**
   Index for the first command in a command list.
*/
#define QCLI_COMMAND_START_INDEX                   (1)


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the QCLI module.

   This function must be called before any other QCLI functions.

   @param[in] Command_Group  Group of commands for the platform.  This can be
                             NULL if no platform commands are required.
                             Note that this function assumes the command group
                             information will be constant and simply stores a
                             pointer to the data.  If the group and its
                             associated information is not constant, its memory
                             must be retained.

   @return QCLI group handle that can be used for the platform abstraction to
           print to the console.
*/
QCLI_Group_Handle_t QCLI_Initialize(const QCLI_Command_Group_t *Command_Group);

/**
   @brief Passes characters input from the command line to the QCLI module for
          processing.

   @param[in] Length  Number of bytes in the provided buffer.
   @param[in] Buffer  Buffer containing the inputted data.

   @return
    - true if QCLI was initialized successfully.
    - false if initialization failed.
*/
void QCLI_Process_Input_Data(uint32_t Length, char *Buffer);

/**
   @brief Displays the current command list.

   It is intended to provide a means for the initial command list to be
   displayed once platform initialization is complete.
*/
void QCLI_Display_Command_List(void);

#endif // ] #ifndef __QCLI_H__

