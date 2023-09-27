/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QCLI_API_H__  // [
#define __QCLI_API_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include "qapi_types.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/**
   Enumeration representing the valid error codes that can be returned by the
   command functions.
*/
typedef enum
{
   QCLI_STATUS_SUCCESS_E, /**< Indicates the command executed successfully. */
   QCLI_STATUS_ERROR_E,   /**< Indicates there was an error parsing the command. */
   QCLI_STATUS_USAGE_E    /**< Indicates there was a usage error with one of the command's arguments. */
} QCLI_Command_Status_t;

/**
   Type representing a group handle.
*/
typedef void *QCLI_Group_Handle_t;

/**
   Information for a single parameter entered into the command line.
*/
typedef struct QCLI_Parameter_s
{
   char    *String_Value;     /**< String value entered into the command line. */
   int32_t  Integer_Value;    /**< Integer value of the command line argument if the string value could be
                                   successfully converted. */
   qbool_t  Integer_Is_Valid; /**< Flag indicating if the integer value is valid. */
} QCLI_Parameter_t;

/**
   @brief Type definition of a function which processes commands from the
          command line.

   @param[in] Parameter_Count  Number of parameters that were entered into the
                               command line.
   @param[in] Parameter_List   List of paramters entered into the command line.

   @return
    - QCLI_STATUS_SUCCESS_E if the command executed successfully.
    - QCLI_STATUS_ERROR_E if the command encounted a general error. Note
      that the CLI currently doesn't take any action for this error.
    - QCLI_STATUS_USAGE_E indicates that the parameters passed to the CLI
      were not correct for the command.  When this error code is returned,
      the CLI will display the usage message for the command.
*/
typedef QCLI_Command_Status_t (*QCLI_Command_Function_t)(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

/**
   Information for a single command in a command list.
*/
typedef struct QCLI_Command_s
{
   QCLI_Command_Function_t  Command_Function; /**< Function that will be called when the command is executed from the CLI. */
   const char              *Command_String;   /**< String representation of the command. */
   const char              *Usage_String;     /**< Usage string for the command. */
   const char              *Description;      /**< Description string for the commmand. */
} QCLI_Command_t;

/**
   Information for a command group that can be registered with the command line
   interface.
*/
typedef struct QCLI_Command_Group_s
{
   const char           *Group_String;  /** String representation of the group. */
   uint32_t              Command_Count; /** Number of commands in the group. */
   const QCLI_Command_t *Command_List;  /** List of commands for the group. */
} QCLI_Command_Group_t;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 *-----------------------------------------------------------------------*/

/**
   @brief Registers a command group with the command line interface.

   NOTE: This function assumes the command group information will be constant
   and simply stores a pointer to the data.  If the group and its associated
   information is not constant, its memory must be retained until the group is
   unregistered.

   @param[in] Parent_Group   Group which this group should be registered under
                             as a subgroup.  If NULL, the group will be
                             registered at the top level.
   @param[in] Command_Group  Command group to be registered.

   @return
    - The handle for the group that was added.
    - NULL if there was an error registering the group.
*/
QCLI_Group_Handle_t QCLI_Register_Command_Group(QCLI_Group_Handle_t Parent_Group, const QCLI_Command_Group_t *Command_Group);

/**
   @brief Unregisters a command group from the command line interface.

   If the specified group has subgroups, they will be unregistered as well.

   @param[in] Group_Handle  Handle of the group to unregister.
*/
void QCLI_Unregister_Command_Group(QCLI_Group_Handle_t Group_Handle);

/**
   @brief Prints the prompt to the console.

   This function provides a means to re-display the prompt after printing data
   to the console from an asynchronous function such as a callback.
*/
void QCLI_Display_Prompt(void);

/**
   @brief Prints a formated string to the CLI.

   This function will also replace newline characters ('\n') with the string
   specified by PAL_OUTPUT_END_OF_LINE_STRING.

   @param[in] QCLI_Handle   Handle of the QCLI group that is printing the
                            string.
   @param[in] Format        Formated string to be printed.
   @param[in] ...           Variatic parameter for the format string.
*/
void QCLI_Printf(QCLI_Group_Handle_t Group_Handle, const char *format, ...);

#endif   // ] #ifndef __QCLI_API_H__

