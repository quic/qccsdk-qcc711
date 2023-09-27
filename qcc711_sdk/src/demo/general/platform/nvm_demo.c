/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "nvm_demo.h"
#include "qapi_nvm.h"
#include "qapi_rot.h"
#include "qcli_util.h"

static QCLI_Group_Handle_t Nvm_QCLI_Handle;

static QCLI_Command_Status_t cmd_Nvm_SetPermissions(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_GetPermissions(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_RequestWrite(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_ReleaseWrite(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_Write(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_Erase(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Nvm_Read(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);


const QCLI_Command_t Nvm_Cmd_List[] =
{
   /* cmd_function          cmd_string        usage_string                                   description */
   {cmd_Nvm_SetPermissions, "SetPermissions", "[Start_Address] [End_Address] [Permissions]", "Set the permissions for an address in NVM."},
   {cmd_Nvm_GetPermissions, "GetPermissions", "[Address]",                                   "Get the permissions for an address in NVM."},
   {cmd_Nvm_RequestWrite,   "RequestWrite",   "",                                            "Request permission to write to NVM."},
   {cmd_Nvm_ReleaseWrite,   "ReleaseWrite",   "",                                            "Release permission to write to NVM."},
   {cmd_Nvm_Write,          "Write",          "[Address] [Buffer]",                          "Writes the provided buffer to an address in NVM."},
   {cmd_Nvm_Erase,          "Erase",          "[Address] [Length]",                          "Erase a section of NVM of specified length."},
   {cmd_Nvm_Read,           "Read",           "[Address] [Length]",                          "Read a section of NVM of specified length."},
};


static const QCLI_Command_Group_t Nvm_Cmd_Group = {"Nvm", sizeof(Nvm_Cmd_List) / sizeof(QCLI_Command_t), Nvm_Cmd_List};

/**
   @brief Executes the "SetPermissions" command.

   Parameter_List[0] is the starting memory address.
   Parameter_List[1] is the length of memory.
   Parameter_List[2] is the permission to set.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_SetPermissions(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t   RetVal;
   void                   *Start_Address;
   void                   *End_Address;
   qapi_NVM_Permissions_t  Permissions;
   uint16_t                Block_Mask;
   uint16_t                Output_Block_Mask;

   if((Parameter_Count >= 3) &&
      (Parameter_List[0].Integer_Is_Valid) &&
      (Parameter_List[1].Integer_Is_Valid) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_NVM_PERMISSIONS_NONE_E, QAPI_NVM_PERMISSIONS_READ_WRITE_EXECUTE_E)))
   {
      Start_Address = (void *)(Parameter_List[0].Integer_Value);
      End_Address   = (void *)(Parameter_List[1].Integer_Value);
      Permissions   = (qapi_NVM_Permissions_t)(Parameter_List[2].Integer_Value);

      /* Convert input addresses to blocks */
      Block_Mask = qapi_NVM_Address_Range_To_Blocks(Start_Address, End_Address);

      if (Block_Mask != 0)
      {
         Output_Block_Mask = qapi_NVM_Set_Permissions(Block_Mask, Permissions);
         QCLI_Printf(Nvm_QCLI_Handle, "Set permissions for blocks: 0x%04X.\n", Output_Block_Mask);
         RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Printf(Nvm_QCLI_Handle, "Incorrect address range.\n");
         RetVal = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "GetPermissions" command.

   Parameter_List[0] is the memory address of interest.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_GetPermissions(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t   RetVal;
   void                   *Address;
   qapi_NVM_Permissions_t  Permissions;

   if((Parameter_Count >= 1) &&
      (Parameter_List[0].Integer_Is_Valid))
   {
      Address = (void *)(Parameter_List[0].Integer_Value);

      Permissions = qapi_NVM_Get_Permissions(Address);
      QCLI_Printf(Nvm_QCLI_Handle, "Permissions: %d.\n", Permissions);

      RetVal = QCLI_STATUS_SUCCESS_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "RequestWrite" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_RequestWrite(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;

   Result = qapi_ROT_Session_Start();

   if (Result == QAPI_OK)
   {
      Result = qapi_NVM_Request_Write();
      QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_NVM_Request_Write", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_ROT_Session_Start", Result);
      RetVal = QCLI_STATUS_ERROR_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "ReleaseWrite" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_ReleaseWrite(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;

   Result = qapi_NVM_Release_Write();

   if (Result == QAPI_OK)
   {
      Result = qapi_ROT_Session_End();
      QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_ROT_Session_End", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_NVM_Release_Write", Result);
      RetVal = QCLI_STATUS_ERROR_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "Write" command.

   Parameter_List[0] is the target memory address.
   Parameter_List[1] is the buffer to be written.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_Write(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  RetVal;
   qapi_Status_t          Result;
   void                  *Address;
   char                  *Buffer;
   uint32_t               Length;

   if((Parameter_Count >= 2) &&
      (Parameter_List[0].Integer_Is_Valid))
   {
      Address = (void *)(Parameter_List[0].Integer_Value);
      Buffer  = (char *)(Parameter_List[1].String_Value);
      Length  = strlen(Buffer);

      Result = qapi_NVM_Write(Address, Buffer, Length);

      if(Result == QAPI_OK)
      {
         QCLI_Printf(Nvm_QCLI_Handle, "Wrote %d bytes to 0x%08X.\n", Length, Address);
         RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_NVM_Write", Result);
         RetVal = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "Erase" command.

   Parameter_List[0] is the target memory address.
   Parameter_List[1] is length of memory to be erased.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_Erase(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  RetVal;
   qapi_Status_t          Result;
   void                  *Address;
   uint32_t               Length;

   if((Parameter_Count >= 2) &&
      (Parameter_List[0].Integer_Is_Valid) &&
      (Parameter_List[1].Integer_Is_Valid))
   {
      Address = (void *)(Parameter_List[0].Integer_Value);
      Length  = (uint32_t)(Parameter_List[1].Integer_Value);

      Result = qapi_NVM_Erase(Address, Length);

      if(Result == QAPI_OK)
      {
         QCLI_Printf(Nvm_QCLI_Handle, "Erase %d bytes from 0x%08X.\n", Length, Address);
         RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Display_Function_Status(Nvm_QCLI_Handle, "qapi_NVM_Erase", Result);
         RetVal = QCLI_STATUS_ERROR_E;
      }
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "Read" command.

   Parameter_List[0] is the target memory address.
   Parameter_List[1] is length of memory to be read.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Nvm_Read(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t  RetVal;
   const void             *Address;
   uint32_t               Length;
   uint32_t               index;

   if((Parameter_Count >= 2) &&
      (Parameter_List[0].Integer_Is_Valid) &&
      (Parameter_List[1].Integer_Is_Valid))
   {
      Address = (void *)(Parameter_List[0].Integer_Value);
      Length  = (uint32_t)(Parameter_List[1].Integer_Value);
      uint8_t *dst = (uint8_t*)Address;

      if (((uint32_t)(Address) >= (uint32_t)QAPI_NVM_APSS_START) && 
           (((uint32_t)(Address) + Length) <= (uint32_t)QAPI_NVM_APSS_END) && 
           (((uint32_t)(Address) <= (uint32_t)QAPI_NVM_APSS_END)))
      {
          QCLI_Printf(Nvm_QCLI_Handle,"Read %d bytes from 0x%08X.\n", Length, Address);

          for (index = 0; index < Length; index++) {
              if ((index != 0) && (index%16 ==0)) {
                   QCLI_Printf(Nvm_QCLI_Handle,"\n");
              }
              QCLI_Printf(Nvm_QCLI_Handle,"0x%02x,", dst[index]);

          }
          RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
          QCLI_Printf(Nvm_QCLI_Handle,"Nvm Read out of range\n");

      }

   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}


/**
   @brief Initializes the Nvm demo application.

   @param[in] Parent_Group QCLI handle for the parent group.
*/
qbool_t Initialize_Nvm_Demo(QCLI_Group_Handle_t Parent_Group)
{
   qbool_t RetVal;

   /* Register the command group. */
   Nvm_QCLI_Handle = QCLI_Register_Command_Group(Parent_Group, &Nvm_Cmd_Group);
   if(Nvm_QCLI_Handle != NULL)
   {
      RetVal = true;
   }
   else
   {
      QCLI_Printf(Nvm_QCLI_Handle, "Failed to register Nvm command group.\n");
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Cleans up the Manufacturing demo application.
*/
void Cleanup_Nvm_Demo(void)
{
   QCLI_Unregister_Command_Group(Nvm_QCLI_Handle);
}
