/*
 * Copyright (c) 2015-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "qapi_types.h"

#include "qcli_util.h"
#include "qcli_pal.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Variables and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Definitions
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
int32_t QCLI_Memcmpi(const void *Source1, const void *Source2, uint32_t Size)
{
   int32_t  Ret_Val;
   uint8_t  Byte1;
   uint8_t  Byte2;
   uint32_t Index;

   Ret_Val = 0;

   /* Simply loop through each byte pointed to by each pointer and check to see
      if they are equal. */
   for(Index = 0; (Index < Size) && (!Ret_Val); Index ++)
   {
      /* Note each Byte that we are going to compare. */
      Byte1 = ((uint8_t *)Source1)[Index];
      Byte2 = ((uint8_t *)Source2)[Index];

      /* If the Byte in the first array is lower case, go ahead and make it
         upper case (for comparisons below). */
      if((Byte1 >= 'a') && (Byte1 <= 'z'))
      {
         Byte1 = Byte1 - ('a' - 'A');
      }

      /* If the Byte in the second array is lower case, go ahead and make it
         upper case (for comparisons below). */
      if((Byte2 >= 'a') && (Byte2 <= 'z'))
      {
         Byte2 = Byte2 - ('a' - 'A');
      }

      /* If the two Bytes are equal then there is nothing to do. */
      if(Byte1 != Byte2)
      {
         /* Bytes are not equal, so set the return value accordingly. */
         if(Byte1 < Byte2)
         {
            Ret_Val = -1;
         }
         else
         {
            Ret_Val = 1;
         }
      }
   }

   /* Simply return the result of the above comparison(s). */
   return(Ret_Val);
}

/**
   @brief Converts a hex character to an integer.

   @param[in]  Nibble  Hex character to be converted.
   @param[out] Output  Pointer to where the converted number will be stored upon
                       a successful return.

   @return
    - true if the nibble was converted successfully.
    - false if there was an error.
*/
qbool_t QCLI_Hex_Nibble_To_Int(uint8_t Nibble, uint8_t *Output)
{
   qbool_t Ret_Val;

   /* Convert the number to lower case to simplify the check for
      characters 'a' through 'f'. */
   Nibble |= 0x20;

   if((Nibble >= '0') && (Nibble <= '9'))
   {
      *Output = Nibble - '0';
      Ret_Val = true;
   }
   else if((Nibble >= 'a') && (Nibble <= 'f'))
   {
      *Output = Nibble - 'a' + 10;
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

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
qbool_t QCLI_String_To_Integer(const char *String, int32_t *Output)
{
   qbool_t  Ret_Val;
   uint8_t  Temp_Val;
   uint32_t Base;
   uint32_t Number;
   uint32_t Previous_Number;
   qbool_t  Number_Is_Negative;

   Ret_Val = true;
   Number  = 0;

   /* Determine if the number is negative and consume the first character of the
      string ('-') if it is. */
   if(String[0] == '-')
   {
      Number_Is_Negative = true;
      String ++;
   }
   else
   {
      Number_Is_Negative = false;
   }

   /* Determine if the number is decimal or hexadecimal.  Note that the second
      character is converted to lower case to make the check simpler. */
   if((String[0] == '0') && ((String[1] | 0x20) == 'x'))
   {
      /* Number will be in hexadecimal.  Consume the first two characters
         ("0x"). */
      Base                = 0x10;
      String             += 2;
   }
   else
   {
      /* Number will be in decimal. */
      Base               = 10;
   }

   /* Loop until the end of the string is reached or the number is flagged as
      invalid. */
   while((String[0] != '\0') && (Ret_Val))
   {
      Ret_Val = QCLI_Hex_Nibble_To_Int(String[0], &Temp_Val);

      if(Ret_Val)
      {
         /* Make sure that the value is correct for the number base. */
         if(Temp_Val < Base)
         {
            String ++;
            Previous_Number = Number;
            Number          = (Number * Base) + Temp_Val;

            /* Make sure that the number has not overflowed.  Signed overflow will
               checked at the end. */
            Ret_Val = (qbool_t)(Number >= Previous_Number);
         }
         else
         {
            Ret_Val = false;
         }
      }
   }

   /* For signed values (decimal or explicitly negative entires), make sure the
      number isn't already negative. */
   if((Ret_Val) && ((Base == 10) || (Number_Is_Negative)))
   {
      Ret_Val = (qbool_t)(((int32_t)Number) >= 0);
   }

   if(Ret_Val)
   {
      /* If the number is valid and negative, invert it now. */
      if(Number_Is_Negative)
      {
         *Output = 0 - (int32_t)Number;
      }
      else
      {
         *Output = (int32_t)Number;
      }
   }
   else
   {
      /* If the conversion failed, zero out the integer value. */
      *Output = 0;
   }

   return(Ret_Val);
}

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
qbool_t QCLI_Hex_String_To_ULL(char *String, uint64_t *Output)
{
   qbool_t  Ret_Val;
   uint8_t  Temp_Val;
   uint64_t Previous_Number;

   /* Strip off the leading "0x" if present. */
   if((String[0] == '0') && ((String[1] | 0x20) == 'x'))
   {
      String += 2;
   }

   Ret_Val = true;
   *Output = 0;

   /* Loop until the end of the string is reached or the number is flagged as
      invalid. */
   while((String[0] != '\0') && (Ret_Val))
   {
      Ret_Val = QCLI_Hex_Nibble_To_Int(String[0], &Temp_Val);

      if(Ret_Val)
      {
         String ++;
         Previous_Number = *Output;
         *Output         = (*Output * 0x10) + Temp_Val;

         /* Make sure the value hasn't overflowed. */
         Ret_Val = (qbool_t)(*Output >= Previous_Number);
      }
   }

   /* If the conversion failed, zero out the integer value. */
   if(!Ret_Val)
   {
      *Output = 0;
   }

   return(Ret_Val);
}

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
qbool_t QCLI_Hex_String_To_Array(char *String, uint32_t *OutputSize, uint8_t *Output)
{
   qbool_t  Ret_Val;
   uint8_t  Temp_Val1;
   uint8_t  Temp_Val2;
   uint32_t InputSize;

   /* Strip off the leading "0x" if present. */
   if((String[0] == '0') && ((String[1] | 0x20) == 'x'))
   {
      String += 2;
   }

   memset(Output, 0, *OutputSize);
   InputSize = 0;
   Ret_Val   = true;

   /* Loop until the end of the string is reached or the number is flagged as
      invalid. */
   while((String[0] != '\0') && (Ret_Val) && (InputSize < *OutputSize))
   {
      /* Make sure the next Nibble is also not NULL. */
      if(String[1] != '\0')
      {
         Ret_Val = QCLI_Hex_Nibble_To_Int(String[0], &Temp_Val1) && QCLI_Hex_Nibble_To_Int(String[1], &Temp_Val2);
         if(Ret_Val)
         {
            *Output = (Temp_Val1 << 4) | Temp_Val2;

            Output ++;
            InputSize ++;
            String += 2;
         }
      }
      else
      {
         Ret_Val = false;
      }
   }

   if(Ret_Val)
   {
      *OutputSize = InputSize;
   }

   return(Ret_Val);
}

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
qbool_t QCLI_Verify_Integer_Parameter(QCLI_Parameter_t *Parameter, int32_t MinValue, int32_t MaxValue)
{
   qbool_t Ret_Val;

   Ret_Val = (qbool_t)((Parameter->Integer_Is_Valid) && (Parameter->Integer_Value >= MinValue) && (Parameter->Integer_Value <= MaxValue));

   return(Ret_Val);
}

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
qbool_t QCLI_Verify_Unsigned_Integer_Parameter(QCLI_Parameter_t *Parameter, uint32_t MinValue, uint32_t MaxValue)
{
   qbool_t Ret_Val;

   Ret_Val = (qbool_t)((Parameter->Integer_Is_Valid) && ((uint32_t)(Parameter->Integer_Value) >= MinValue) && ((uint32_t)(Parameter->Integer_Value) <= MaxValue));

   return(Ret_Val);
}

/**
   @brief Displays a message indicating the status result of a function.

   @param[in] QCLI_Handle   Handle of the QCLI group that is displaying the
                            message.
   @param[in] Function_Name Name of the function to be displayed.
   @param[in] Result        Return code from the function call.
*/
void QCLI_Display_Function_Status(QCLI_Group_Handle_t QCLI_Handle, char *Function_Name, qapi_Status_t Result)
{
   if(Function_Name != NULL)
   {
      if(Result == QAPI_OK)
      {
         QCLI_Printf(QCLI_Handle, "%s() success.\n", Function_Name);
      }
      else
      {
         QCLI_Printf(QCLI_Handle, "%s returned %d\n", Function_Name, Result);
      }
   }
}

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
void QCLI_Dump_Data(QCLI_Group_Handle_t QCLI_Handle, const char *Prefix, uint16_t Length, const uint8_t *Buffer)
{
   uint16_t DataOffset;
   uint32_t LineOffset;
   uint32_t Index;
   uint8_t  LineBuffer[(3 * 16) + 1];
   uint8_t  AsciiBuffer[17];

   if((Prefix != NULL) && (Length > 0) && (Buffer != NULL))
   {
      DataOffset = 0;
      while(Length > 0)
      {
         /* Print out all the bytes for the line. */
         memset(LineBuffer, ' ', sizeof(LineBuffer));
         LineOffset = 0;
         for(Index = 0; (Index < 16) && (Length > 0); Index ++)
         {
            LineOffset += snprintf((char *)(&(LineBuffer[LineOffset])), sizeof(LineBuffer) - LineOffset, "%02X ", *Buffer);
            if(LineOffset > sizeof(LineBuffer))
            {
               LineOffset = sizeof(LineBuffer);
            }

            /* Put the character in the AsciiBuffer if it is printable. */
            if((*Buffer >= ' ') && (*Buffer <= '~'))
            {
               AsciiBuffer[Index] = *Buffer;
            }
            else
            {
               AsciiBuffer[Index] = '.';
            }

            Length --;
            Buffer ++;
         }

         /* Handle the case if the buffer was empty before the line was
            complete. */
         LineBuffer[LineOffset] = ' ';
         LineBuffer[sizeof(LineBuffer) - 1] = '\0';

         /* Null terminate the AsciiBuffer. */
         AsciiBuffer[Index] = '\0';

         /* Display the line. */
         QCLI_Printf(QCLI_Handle, "%s%04X %s  %s\n", Prefix, DataOffset, LineBuffer, AsciiBuffer);

         DataOffset += 16;
      }
   }
}


