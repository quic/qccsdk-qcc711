/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QCLI_UTIL_H__ // [
#define __QCLI_UTIL_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include "qapi_types.h"
#include "qapi_status.h"
#include "qcli_api.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 *-----------------------------------------------------------------------*/

/**
   @brief Performs a case-insensitive comparison of two buffers.

   @param[in] Source1 First string to be compared.
   @param[in] Source2 Second string to be compared.
   @param[in] Size    Amount of data to compare.

   @return
    - 0  if the two strings are equivalent up to the specified Size.
    - -1 if Source1 is "less than" Source2.
    - 1  if Source1 is "greater than" Source2.
*/
int32_t QCLI_Memcmpi(const void *Source1, const void *Source2, uint32_t Size);

/**
   @brief Converts a hex character to an integer.

   @param[in]  Nibble  Hex character to be converted.
   @param[out] Output  Pointer to where the converted number will be stored upon
                       a successful return.

   @return
    - true if the nibble was converted successfully.
    - false if there was an error.
*/
qbool_t QCLI_Hex_Nibble_To_Int(uint8_t Nibble, uint8_t *Output);

/**
   @brief Attempts to convert a string to an integer.

   This function supports strings in either a decimal or hexadecimal format.
   The string will be treated as a hexadecimal number if it starts with "0x",
   otherwise it will be treated as a decimal number.

   @param[in]  String  NULL terminated string to be converted.
   @param[out] Output  Pointer to where the integer value will be stored upon
                       successful return.

   @return
    - true if the conversion was successful.
    - false if the conversion was not successful.
*/
qbool_t QCLI_String_To_Integer(const char *String, int32_t *Output);

/**
   @brief Attempts to convert a string hex digits to an Unsigned 64-bit integer.
          A leading '0x' is optional.

   @param[in]  String  NULL terminated string to be converted.
   @param[out] Output  Pointer to where the integer value will be stored upon
                       successful return.

   @return
    - true if the string was converted successfully.
    - false if there was an error.
*/
qbool_t QCLI_Hex_String_To_ULL(char *String, uint64_t *Output);

/**
   @brief Parses a string as an arbitrary length hex value.

   The output will be an array of the nibbles in Big Endian format. A leading
   '0x' is optional.

   @param[in]     String      NULL terminated string to be converted.
   @param[in,out] OutputSize  Size of the output buffer.  Upon successful
                              return, this value will be set to the number of
                              bytes filled.
   @param[out]    Output      Pointer to where the value will be stored upon
                              successful return.

   @return
    - true if the string was converted successfully.
    - false if there was an error.
*/
qbool_t QCLI_Hex_String_To_Array(char *String, uint32_t *OutputSize, uint8_t *Output);

/**
   @brief Verifies if a given command line parameter is a valid integer in the
          specified range.

   @param[in] Parameter  Command line parameter to verify.
   @param[in] MinValue   Minimum acceptable value for the parameter.
   @param[in] MaxValue   Maximum acceptable value for the parameter.

   @return
    - true  if the parameter is valid.
    - false if the parameter is not valid.
*/
qbool_t QCLI_Verify_Integer_Parameter(QCLI_Parameter_t *Parameter, int32_t MinValue, int32_t MaxValue);

/**
   @brief Verifies if a given command line parameter is a valid unsigned integer
          in the specified range.

   This function is similar to Verify_Integer_Parameter() but is able to
   verify parameters that will be treated as unsigned 32-bit integers.

   @param[in] Parameter  Command line parameter to verify.
   @param[in] MinValue   Minimum acceptable value for the parameter.
   @param[in] MaxValue   Maximum acceptable value for the parameter.

   @return
    - true  if the parameter is valid.
    - false if the parameter is not valid.
*/
qbool_t QCLI_Verify_Unsigned_Integer_Parameter(QCLI_Parameter_t *Parameter, uint32_t MinValue, uint32_t MaxValue);

/**
   @brief Displays a message indicating the status result of a function.

   @param[in] QCLI_Handle   Handle of the QCLI group that is displaying the
                            message.
   @param[in] Function_Name Name of the function to be displayed.
   @param[in] Result        Return code from the function call.
*/
void QCLI_Display_Function_Status(QCLI_Group_Handle_t QCLI_Handle, char *Function_Name, qapi_Status_t Result);

/**
   @brief Outputs a buffer containing raw binary data (i.e., not characters) to
          the console.

   @param[in] QCLI_Handle   Handle of the QCLI group that is displaying the
                            message.
   @param[in] Prefix        String prefixed to each line printed. This is
                            usually the leading whitespace for the line.
   @param[in] Length        Length of the data to be displayed.
   @param[in] Buffer        Buffer containing the data to be displayed.
*/
void QCLI_Dump_Data(QCLI_Group_Handle_t QCLI_Handle, const char *Prefix, uint16_t Length, const uint8_t *Buffer);

#endif // ] #ifndef __QCLI_UTIL_H__

