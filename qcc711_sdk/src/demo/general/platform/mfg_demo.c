/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "stdbool.h"

#include "ble_demo.h"
#include "mfg_demo.h"
#include "qcli_api.h"
#include "qcli_util.h"

#include "qapi_types.h"
#include "qapi_status.h"
#include "qapi_mfg.h"
#include "qapi_power.h"
#include "qapi_sense.h"

#include "qapi_ble_hci_vs.h"
#include "qapi_ble_hci.h"

static QCLI_Group_Handle_t Mfg_QCLI_Handle;

static QCLI_Command_Status_t cmd_Mfg_OutputClock(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_CoarseTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_FineTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_StoreTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Enable32K(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Get32KSource(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static void cmd_Mfg_LFXTAL_Enabled_CB(qapi_Status_t Result, void *UserParam);
static QCLI_Command_Status_t cmd_Mfg_EnableSMPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_CalibrateSMPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_SetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_GetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

static QCLI_Command_Status_t cmd_Mfg_VS_Test_Stop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_VS_Test_LE_Continuous(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_VS_Test_LE_Burst(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);

static QCLI_Command_Status_t cmd_Mfg_Test_LE_Receiver(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Enhanced_Receiver(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Transmitter(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Enhanced_Transmitter(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);
static QCLI_Command_Status_t cmd_Mfg_Test_LE_End(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List);


/* Internal help functions. */
static QCLI_Command_Status_t CalibrateSMPS(bool Start);

const QCLI_Command_t Mfg_Cmd_List[] =
{
   /* cmd_function         cmd_string       usage_string                           description */
   {cmd_Mfg_OutputClock,   "OutputClock",   "[Clock: 0=LF, 1=HF] [Enable]",        "Enable or disable the clock output."},
   {cmd_Mfg_CoarseTrim,    "CoarseTrim",    "[Clock: 0=LF, 1=HF] [Trim]",          "Update the coarse trim for a clock."},
   {cmd_Mfg_FineTrim,      "FineTrim",      "[Trim]",                              "Update the fine trim for the HFCLK."},
   {cmd_Mfg_StoreTrim,     "StoreTrim",     "[Clock: 0=LF, 1=HF] [Coarse] [Fine]", "Store the trim values for a clock."},
   {cmd_Mfg_Enable32K,     "Enable32K",     "[Enable]",                            "Enable the 32K XTAL."},
   {cmd_Mfg_Get32KSource,  "Get32KSource",  "",                                    "Get the LFCLK's current source configuration."},
   {cmd_Mfg_EnableSMPS,    "EnableSMPS",    "",                                    "Enable the SMPS"},
   {cmd_Mfg_CalibrateSMPS, "CalibrateSMPS", "",                                    "Calibrate the SMPS"},
   {cmd_Mfg_SetVLP,        "SetVLP",        "[Voltage]",                           "Set the VLP voltage"},
   {cmd_Mfg_GetVLP,        "GetVLP",        "",                                    "Get the VLP voltage"},

   {cmd_Mfg_VS_Test_Stop,          "VSTestStop",         "",                                                                                      "Issues the stop production test command."},
   {cmd_Mfg_VS_Test_LE_Continuous, "VSTestLEContinuous", "[Channel_Index] [Transmit_Output_Power] [Transmit_Type] [Packet_Length] [Bit_Pattern]", "Issues the LE continuous production test command."},
   {cmd_Mfg_VS_Test_LE_Burst,      "VSTestLEBurst",      "[Hop_Channels] [Payload_Length] [Payload_Type] [Packet_Type] [Transmit_Output_Power]",  "Issues the LE burst production test command."},

   {cmd_Mfg_Test_LE_Receiver,             "TestLEReceiver",            "[RX_Frequency]",                                       "Issues the LE receiver test command."},
   {cmd_Mfg_Test_LE_Enhanced_Receiver,    "TestLEEnhancedReceiver",    "[RX_Frequency] [PHY] [Modulation Index]",              "Issues the LE enhanced receiver test command."},
   {cmd_Mfg_Test_LE_Transmitter,          "TestLETransmitter",         "[TX_Frequency] [Payload_Length] [Payload_Type]",       "Issues the LE transmitter test command."},
   {cmd_Mfg_Test_LE_Enhanced_Transmitter, "TestLEEnhancedTransmitter", "[TX_Frequency] [Payload_Length] [Payload_Type] [PHY]", "Issues the LE enhanced transmitter test command."},
   {cmd_Mfg_Test_LE_End,                  "TestLEEnd",                 "",                                                     "Issues the LE end test command."},
};

static const QCLI_Command_Group_t Mfg_Cmd_Group = {"Mfg", sizeof(Mfg_Cmd_List) / sizeof(QCLI_Command_t), Mfg_Cmd_List};

/**
   @brief Executes the "OutputClock" command.

   Parameter_List[0] is the clock to enable or disable.
   Parameter_List[1] is a flag to indicate if the clock should be enabled or
                     disabled.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_OutputClock(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qapi_MFG_Clock_t      Clock;
   qbool_t               Enable;

   if((Parameter_Count >= 2) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_MFG_CLOCK_LFCLK_E, QAPI_MFG_CLOCK_HFCLK_E)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], 0, 1)))
   {
      Clock = (qapi_MFG_Clock_t)(Parameter_List[0].Integer_Value);
      Enable = (qbool_t)(Parameter_List[1].Integer_Value != 0);

      Result = qapi_MFG_Enable_CLK_Output(Clock, Enable);
      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_MFG_Enable_CLK_Output", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "CoarseTrim" command.

   Parameter_List[0] is the clock to configure.
   Parameter_List[1] is the coarse trim value for the clock.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_CoarseTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qapi_MFG_Clock_t      Clock;
   uint16_t              Trim;

   if((Parameter_Count >= 2) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_MFG_CLOCK_LFCLK_E, QAPI_MFG_CLOCK_HFCLK_E)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], 0, 0xFFFF)))
   {
      Clock = (qapi_MFG_Clock_t)(Parameter_List[0].Integer_Value);
      Trim = (uint16_t)(Parameter_List[1].Integer_Value);

      Result = qapi_MFG_Update_CLK_Coarse_Trim(Clock, Trim);
      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_MFG_Update_CLK_Coarse_Trim", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "FineTrim" command.

   Parameter_List[0] is the fine trim value for the HFCLK.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_FineTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   int16_t               Trim;

   if((Parameter_Count >= 1) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 0xFFFF)))
   {
      Trim = (int16_t)(Parameter_List[0].Integer_Value);

      Result = qapi_MFG_Update_CLK_Fine_Trim(QAPI_MFG_CLOCK_HFCLK_E, Trim);
      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_MFG_Update_CLK_Fine_Trim", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "StoreTrim" command.

   Parameter_List[0] is the clock to configure.
   Parameter_List[1] is the coarse trim value for the clock.
   Parameter_List[2] is the fine trim value for the clock.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_StoreTrim(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qapi_MFG_Clock_t      Clock;
   uint16_t              Coarse;
   int16_t               Fine;

   if((Parameter_Count >= 3) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_MFG_CLOCK_LFCLK_E, QAPI_MFG_CLOCK_HFCLK_E)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], 0, 0xFFFF)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], 0, 0xFFFF)))
   {
      Clock = (qapi_MFG_Clock_t)(Parameter_List[0].Integer_Value);
      Coarse = (uint16_t)(Parameter_List[1].Integer_Value);
      Fine = (int16_t)(Parameter_List[2].Integer_Value);

      Result = qapi_MFG_Store_CLK_Trim(Clock, Coarse, Fine);
      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_MFG_Store_CLK_Trim", Result);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "Enable32K" command.

   Parameter_List[0] is a flag to indicate if the XTAL should be enabled or
                     disabled.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Enable32K(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   qbool_t               Enable;
   int32_t               Temperature;

   if((Parameter_Count >= 1) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], 0, 1)))
   {
      Enable = (qbool_t)(Parameter_List[0].Integer_Value != 0);
      Result = qapi_SENS_Get_Temp(&Temperature);

      if(Result == QAPI_OK)
      {
         Result = qapi_PWR_Set_LFCLK_Source(Enable ? QAPI_PWR_LFCLK_SOURCE_LFXTAL : QAPI_PWR_LFCLK_SOURCE_SOSC, Temperature, cmd_Mfg_LFXTAL_Enabled_CB, NULL);
         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_PWR_Set_LFCLK_Source", Result);
      }
      else
      {
         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Get_Temp", Result);
      }

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      RetVal = QCLI_STATUS_USAGE_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "Get32KSource" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Get32KSource(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   qapi_PWR_LFCLK_Source_t  Source;
   char                    *Source_String;

   Source = qapi_PWR_Get_LFCLK_Source();

   switch(Source)
   {
      case QAPI_PWR_LFCLK_SOURCE_SOSC:
         Source_String = "SOSC";
         break;

      case QAPI_PWR_LFCLK_SOURCE_LFXTAL:
         Source_String = "LFXTAL";
         break;

      case QAPI_PWR_LFCLK_SOURCE_GPIO:
         Source_String = "GPIO";
         break;
     
      default:
         Source_String = "Unknown";
   }

   QCLI_Printf(Mfg_QCLI_Handle, "LFCLK Source: %s\n", Source_String);

   return(QCLI_STATUS_SUCCESS_E);
}

/**
   @brief Callback indicating the LFXTAL has been enabled.

   @param[in] Result     Result of the LFXTAL start operation. QAPI_OK if the
                         process succeeded or a negative value if there was an
                         error.
   @param[in] UserParam  Pointer to the user-specified parameter provided when
                         the callback is registered.
*/
static void cmd_Mfg_LFXTAL_Enabled_CB(qapi_Status_t Result, void *UserParam)
{
   QCLI_Display_Function_Status(Mfg_QCLI_Handle, "32K XTAL Enable", Result);
   QCLI_Display_Prompt();
}

/**
   @brief Executes the "EnableSMPS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_EnableSMPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   return(CalibrateSMPS(true));
}

/**
   @brief Executes the "CalibrateSMPS" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_CalibrateSMPS(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
    return(CalibrateSMPS(false));
}

/**
   @brief Executes the "SetVLP" command.

   Parameter_List[0] is the voltage for the VLP.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_SetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   uint32_t              Voltage;

   if((Parameter_Count >= 1) &&
      (Parameter_List[0].Integer_Is_Valid))
   {
      Voltage = (uint32_t)(Parameter_List[0].Integer_Value);

      if(qapi_PWR_Set_VLP_Voltage(Voltage))
      {
         QCLI_Printf(Mfg_QCLI_Handle, "qapi_PWR_Set_VLP_Voltage() success.\n");

         RetVal = QCLI_STATUS_SUCCESS_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "qapi_PWR_Set_VLP_Voltage() failed.\n");

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
   @brief Executes the "GetVLP" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_GetVLP(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   uint32_t Voltage;

   Voltage = qapi_PWR_Get_VLP_Voltage();

   QCLI_Printf(Mfg_QCLI_Handle, "VLP Voltage: %dmV\n", Voltage);

   return(QCLI_STATUS_SUCCESS_E);
}

/**
   @brief Executes the "VSTestStop" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_VS_Test_Stop(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               Status;

   BluetoothStackID = GetBluetoothStackID();

   if(BluetoothStackID)
   {
      Result = qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_Stop(BluetoothStackID, &Status);

      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_Stop", Result);

      QCLI_Printf(Mfg_QCLI_Handle, "   Status:  0x%02X\r\n", Status);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

      RetVal = QCLI_STATUS_ERROR_E;
   }

   return(RetVal);
}

/**
   @brief Executes the "VSTestLEContinuous" command.

   Parameter_List[0] is the channel index.
   Parameter_List[1] is the transmit output power.
   Parameter_List[2] is the transmit type.
   Parameter_List[3] is the packet length.
   Parameter_List[4] is the bit pattern.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_VS_Test_LE_Continuous(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               Channel_Index;
   uint8_t               Transmit_Output_Power;
   uint8_t               Transmit_Type;
   uint8_t               Packet_Length;
   uint32_t              Bit_Pattern;
   uint8_t               Status;

   if((Parameter_Count >= 5) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_HCI_VS_PROD_TEST_CHANNEL_INDEX_MINIMUM, QAPI_BLE_HCI_VS_PROD_TEST_CHANNEL_INDEX_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MINIMUM, QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_CARRIER_ONLY, QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_2M_PATTERN)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_HCI_VS_PROD_TEST_PACKET_LENGTH_MINIMUM, QAPI_BLE_HCI_VS_PROD_TEST_PACKET_LENGTH_MAXIMUM)) &&
      (Parameter_List[4].Integer_Is_Valid))
   {
      Channel_Index         = (uint8_t)(Parameter_List[0].Integer_Value);
      Transmit_Output_Power = (uint8_t)(Parameter_List[1].Integer_Value);
      Transmit_Type         = (uint8_t)(Parameter_List[2].Integer_Value);
      Packet_Length         = (uint8_t)(Parameter_List[3].Integer_Value);
      Bit_Pattern           = (uint32_t)(Parameter_List[4].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Continuous(BluetoothStackID,
                                                                               Channel_Index,
                                                                               Transmit_Output_Power,
                                                                               Transmit_Type,
                                                                               Packet_Length,
                                                                               Bit_Pattern,
                                                                               &Status);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Continuous", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:  0x%02X\r\n", Status);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "VSTestLEBurst" command.

   Parameter_List[0] is the hop channels.
   Parameter_List[1] is the payload length.
   Parameter_List[2] is the payload type.
   Parameter_List[3] is the packet type.
   Parameter_List[4] is the transmit output power.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_VS_Test_LE_Burst(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               Hop_Channels;
   uint16_t              Payload_Length;
   uint8_t               Payload_Type;
   uint8_t               Packet_Type;
   uint8_t               Transmit_Output_Power;
   uint8_t               Status;
   uint8_t               SubOpCode;

   if((Parameter_Count >= 5) &&
      (Parameter_List[0].Integer_Is_Valid) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_LENGTH_MINIMUM, QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_LENGTH_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_PRBS9, QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_BITS_REVERSE)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_1M, QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_SIMULTANEOUS_SCAN)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[4], QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MINIMUM, QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MAXIMUM)))
   {
      Hop_Channels          = (uint8_t)(Parameter_List[0].Integer_Value);
      Payload_Length        = (uint16_t)(Parameter_List[1].Integer_Value);
      Payload_Type          = (uint8_t)(Parameter_List[2].Integer_Value);
      Packet_Type           = (uint8_t)(Parameter_List[3].Integer_Value);
      Transmit_Output_Power = (uint8_t)(Parameter_List[4].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Burst(BluetoothStackID,
                                                                          Hop_Channels,
                                                                          Payload_Length,
                                                                          Payload_Type,
                                                                          Packet_Type,
                                                                          Transmit_Output_Power,
                                                                          &Status,
                                                                          &SubOpCode);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Burst", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:     0x%02X\r\n", Status);
         QCLI_Printf(Mfg_QCLI_Handle, "   SubopCode:  0x%02X\r\n", SubOpCode);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "TestLEReceiver" command.

   Parameter_List[0] is the RX Frequency.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Receiver(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               RX_Frequency;
   uint8_t               Status;

   if((Parameter_Count >= 1) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM, QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM)))
   {
      RX_Frequency = (uint8_t)(Parameter_List[0].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_LE_Receiver_Test(BluetoothStackID, RX_Frequency, &Status);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_LE_Receiver_Test", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:     0x%02X\r\n", Status);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "TestLEEnhancedReceiver" command.

   Parameter_List[0] is the RX Frequency.
   Parameter_List[1] is the PHY to be used.
   Parameter_List[2] is the modulation index.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Enhanced_Receiver(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               RX_Frequency;
   uint8_t               PHY;
   uint8_t               Modulation_Index;
   uint8_t               Status;

   if((Parameter_Count >= 3) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM, QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_1M, QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_CODED_S2)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_HCI_LE_TRANSMITTER_MODULATION_INDEX_STANDARD, QAPI_BLE_HCI_LE_TRANSMITTER_MODULATION_INDEX_STABLE)))
   {
      RX_Frequency     = (uint8_t)(Parameter_List[0].Integer_Value);
      PHY              = (uint8_t)(Parameter_List[1].Integer_Value);
      Modulation_Index = (uint8_t)(Parameter_List[2].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_LE_Enhanced_Receiver_Test(BluetoothStackID, RX_Frequency, PHY, Modulation_Index, &Status);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_LE_Enhanced_Receiver_Test", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:     0x%02X\r\n", Status);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "TestLETransmitter" command.

   Parameter_List[0] is the TX Frequency.
   Parameter_List[1] is the length (in bytes) of payload data in each packet.
   Parameter_List[2] is the payload type.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Transmitter(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               TX_Frequency;
   uint8_t               Payload_Length;
   uint8_t               Payload_Type;
   uint8_t               Status;

   if((Parameter_Count >= 3) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM, QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MINIMUM_LENGTH, QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MAXIMUM_LENGTH)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_9, QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x55)))
   {
      TX_Frequency   = (uint8_t)(Parameter_List[0].Integer_Value);
      Payload_Length = (uint8_t)(Parameter_List[1].Integer_Value);
      Payload_Type   = (uint8_t)(Parameter_List[2].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_LE_Transmitter_Test(BluetoothStackID, TX_Frequency, Payload_Length, Payload_Type, &Status);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_LE_Transmitter_Test", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:     0x%02X\r\n", Status);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "TestLEEnhancedTransmitter" command.

   Parameter_List[0] is the TX Frequency.
   Parameter_List[1] is the length (in bytes) of payload data in each packet.
   Parameter_List[2] is the payload type.
   Parameter_List[3] is the PHY to be used.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Test_LE_Enhanced_Transmitter(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               TX_Frequency;
   uint8_t               Payload_Length;
   uint8_t               Payload_Type;
   uint8_t               PHY;
   uint8_t               Status;

   if((Parameter_Count >= 4) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[0], QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MINIMUM, QAPI_BLE_HCI_LE_RECEIVER_TRANSMITTER_TEST_FREQUENCY_MAXIMUM)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[1], QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MINIMUM_LENGTH, QAPI_BLE_HCI_LE_TRANSMITTER_TEST_LENGTH_OF_TEST_DATA_MAXIMUM_LENGTH)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[2], QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PSEUDO_RANDOM_BIT_SEQUENCE_9, QAPI_BLE_HCI_LE_TRANSMITTER_TEST_PAYLOAD_PATTERN_ALTERNATING_BITS_0x55)) &&
      (QCLI_Verify_Integer_Parameter(&Parameter_List[3], QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_1M, QAPI_BLE_HCI_LE_ENHANCED_TRANSMITTER_TEST_PHY_CODED_S2)))
   {
      TX_Frequency   = (uint8_t)(Parameter_List[0].Integer_Value);
      Payload_Length = (uint8_t)(Parameter_List[1].Integer_Value);
      Payload_Type   = (uint8_t)(Parameter_List[2].Integer_Value);
      PHY            = (uint8_t)(Parameter_List[3].Integer_Value);

      BluetoothStackID = GetBluetoothStackID();

      if(BluetoothStackID)
      {
         Result = qapi_BLE_HCI_LE_Enhanced_Transmitter_Test(BluetoothStackID, TX_Frequency, Payload_Length, Payload_Type, PHY, &Status);

         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_LE_Enhanced_Transmitter_Test", Result);

         QCLI_Printf(Mfg_QCLI_Handle, "   Status:     0x%02X\r\n", Status);

         RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
      }
      else
      {
         QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

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
   @brief Executes the "TestLEEnd" command.

   @param Parameter_Count is number of elements in Parameter_List.
   @param Parameter_List is list of parsed arguments associate with this
          command.

   @return
    - QCLI_STATUS_SUCCESS_E indicates the command is executed successfully.
    - QCLI_STATUS_ERROR_E indicates the command is failed to execute.
    - QCLI_STATUS_USAGE_E indicates there is usage error associated with this
      command.
*/
static QCLI_Command_Status_t cmd_Mfg_Test_LE_End(uint32_t Parameter_Count, QCLI_Parameter_t *Parameter_List)
{
   QCLI_Command_Status_t RetVal;
   qapi_Status_t         Result;
   uint32_t              BluetoothStackID;
   uint8_t               Status;
   uint16_t              Number_Of_PacketsResult;

   BluetoothStackID = GetBluetoothStackID();

   if(BluetoothStackID)
   {
      Result = qapi_BLE_HCI_LE_Test_End(BluetoothStackID, &Status, &Number_Of_PacketsResult);

      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_BLE_HCI_LE_Test_End", Result);

      QCLI_Printf(Mfg_QCLI_Handle, "   Status:        0x%02X\r\n", Status);
      QCLI_Printf(Mfg_QCLI_Handle, "   Num. Packets:  0x%02X\r\n", Number_Of_PacketsResult);

      RetVal = (Result == QAPI_OK) ? QCLI_STATUS_SUCCESS_E : QCLI_STATUS_ERROR_E;
   }
   else
   {
      QCLI_Printf(Mfg_QCLI_Handle, "BT stack has not been initialized.\r\n");

      RetVal = QCLI_STATUS_ERROR_E;
   }
   return(RetVal);
}

/**
   @brief Calibrate and optionally start the SMPS.
*/
static QCLI_Command_Status_t CalibrateSMPS(bool Start)
{
   QCLI_Command_Status_t Ret_Val = QCLI_STATUS_ERROR_E;
   qapi_Status_t         Result;
   uint32_t              Voltage;
   int32_t               Temperature;

   if((Result = qapi_SENS_Get_Temp(&Temperature)) == QAPI_OK)
   {
      if((Result = qapi_SENS_Voltage_Sensor_Enable(true)) == QAPI_OK)
      {
         if((Result = qapi_SENS_Vbat_Monitor_Enable(true)) == QAPI_OK)
         {
            if((Result = qapi_SENS_Get_Voltage(QAPI_SENS_VOLTAGE_SOURCE_VBAT_E, &Voltage)) == QAPI_OK)
            {
               if(Start)
               {
                  qapi_PWR_Enable_SMPS(Temperature, Voltage);

                  QCLI_Printf(Mfg_QCLI_Handle, "SMPS has been calibrated and enabled successfully.\n");
               }
               else
               {
                  qapi_PWR_Calibrate_SMPS(Temperature, Voltage);

                  QCLI_Printf(Mfg_QCLI_Handle, "SMPS has been calibrated successfully.\n");
               }

               Ret_Val = QCLI_STATUS_SUCCESS_E;
            }
            else
            {
               QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Get_Voltage", Result);
            }

            if((Result = qapi_SENS_Vbat_Monitor_Enable(false)) != QAPI_OK)
            {
               Ret_Val = QCLI_STATUS_ERROR_E;
               QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Vbat_Monitor_Enable(false)", Result);
            }
         }
         else
         {
            QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Vbat_Monitor_Enable(true)", Result);
         }

         if((Result = qapi_SENS_Voltage_Sensor_Enable(false)) != QAPI_OK)
         {
            Ret_Val = QCLI_STATUS_ERROR_E;
            QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Voltage_Sensor_Enable(false)", Result);
         }
      }
      else
      {
         QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Voltage_Sensor_Enable(true)", Result);
      }
   }
   else
   {
      QCLI_Display_Function_Status(Mfg_QCLI_Handle, "qapi_SENS_Get_Temp", Result);
   }

   return(Ret_Val);
}

/**
   @brief Initializes the Manufacturing demo application.

   @param[in] Parent_Group  QCLI handle for the parent group.
*/
qbool_t Initialize_Mfg_Demo(QCLI_Group_Handle_t Parent_Group)
{
   qbool_t RetVal;

   /* Register the command group. */
   Mfg_QCLI_Handle = QCLI_Register_Command_Group(Parent_Group, &Mfg_Cmd_Group);
   if(Mfg_QCLI_Handle != NULL)
   {
      RetVal = true;
   }
   else
   {
      QCLI_Printf(Mfg_QCLI_Handle, "Failed to register Manufacturing command group.\n");
      RetVal = false;
   }

   return(RetVal);
}

/**
   @brief Cleans up the Manufacturing demo application.
*/
void Cleanup_Mfg_Demo(void)
{
   QCLI_Unregister_Command_Group(Mfg_QCLI_Handle);
}
