/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_errors.h"
#include "qapi_ble_hci.h"
#include "qapi_ble_hci_vs.h"
#include "HCIAPI_params.h"
#include "HCIAPI_cb_m3.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"
#include "qapi_heap.h"
#include "qapi_status.h"

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_Stop(uint32_t BluetoothStackID, uint8_t *StatusResult)
{
   int                 ret_val = -1;
   HCI_Reset_Params_t *Params;
   uint32_t            Offset;
   uint32_t            MessageSize;

   MessageSize = ALIGN32(HCI_RESET_PARAMS_SIZE) + ALIGN32(sizeof(uint8_t));

   if(NULL != (Params = IPC_GetSharedMemory(MessageSize)))
   {
      Offset = ALIGN32(HCI_RESET_PARAMS_SIZE);
      Params->BluetoothStackID = BluetoothStackID;

      if(StatusResult != NULL)
      {
         Params->StatusResult = (uint8_t *)(((uint8_t *)Params) + Offset);
         Offset = ALIGN32(Offset + sizeof(uint8_t));
      }
      else
      {
         Params->StatusResult = NULL;
      }

      ret_val = (int)IPC_SendFunctionCall(FILE_ID_HCIAPI, FUNCTION_ID_HCI_RESET, MessageSize, (uint8_t *)Params);

      if(StatusResult)
         *StatusResult = *Params->StatusResult;

      IPC_FreeSharedMemory(Params);
   }

   return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Continuous(uint32_t BluetoothStackID, uint8_t Channel_Index, uint8_t Transmit_Output_Power, uint8_t Transmit_Type, uint8_t Packet_Length, uint32_t Bit_Pattern, uint8_t *StatusResult)
{
   int32_t                                                             ret_val;
   qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_t                CommandBuffer;
   qapi_BLE_HCI_VS_Prod_Test_LE_TX_Continuous_Command_Complete_Event_t ResponseBuffer;
   uint8_t                                                             ResponseBufferLength;

   /* Make sure the input parameters are valid.                         */
   /* * NOTE * QHS transmit types are not supported for Ziggy so that   */
   /*          have been excluded.                                      */
   if((BluetoothStackID) &&
      (Channel_Index <= QAPI_BLE_HCI_VS_PROD_TEST_CHANNEL_INDEX_MAXIMUM) &&
      (Transmit_Output_Power <= QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MAXIMUM) &&
      ((Transmit_Type >= QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_CARRIER_ONLY) && (Transmit_Type <= QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_TYPE_LE_2M_PATTERN)) &&
      (Packet_Length <= QAPI_BLE_HCI_VS_PROD_TEST_PACKET_LENGTH_MAXIMUM) &&
      (StatusResult))
   {
      /* Format command.                                                */
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Sub_Op_Code), QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_LE_TX_CONTINUOUS);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Channel_Index), Channel_Index);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Transmit_Output_Power), Transmit_Output_Power);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Transmit_Type), Transmit_Type);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Packet_Length), Packet_Length);
      memscpy(&((&CommandBuffer)->Bit_Pattern), QAPI_BLE_NON_ALIGNED_DWORD_SIZE, &Bit_Pattern, sizeof(Bit_Pattern));

      /* This function requires a response buffer if we are waiting for */
      /* a response, even if we are not using it.                       */
      /* * NOTE * The Status field is decoded by the function so we     */
      /*          don't have to decode it.                              */
      ResponseBufferLength = (QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_CONTINUOUS_COMMAND_COMPLETE_EVENT_SIZE - QAPI_BLE_HCI_COMMAND_COMPLETE_EVENT_HEADER_SIZE);

      ret_val = qapi_BLE_HCI_Send_Raw_Command(BluetoothStackID,
                                              QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF,
                                              QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_CODE_OCF,
                                              QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_CONTINUOUS_COMMAND_SIZE,
                                              (uint8_t *)&CommandBuffer,
                                              StatusResult,
                                              &ResponseBufferLength,
                                              (uint8_t *)&(ResponseBuffer.Status),
                                              TRUE);
   }
   else
   {
      ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }

   return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_HCI_VS_Prod_Test_Command_Prod_Test_LE_TX_Burst(uint32_t BluetoothStackID, uint8_t Hop_Channels, uint16_t Payload_Length, uint8_t Payload_Type, uint8_t Packet_Type, uint8_t Transmit_Output_Power, uint8_t *StatusResult, uint8_t *SubOpCode)
{
   int32_t                                                        ret_val;
   qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_t                CommandBuffer;
   qapi_BLE_HCI_VS_Prod_Test_LE_TX_Burst_Command_Complete_Event_t ResponseBuffer;
   uint8_t                                                        ResponseBufferLength;

   /* Make sure the input parameters are valid.                         */
   /* * NOTE * QHS packet types are not supported for Ziggy so that have*/
   /*          been excluded.                                           */
   if((BluetoothStackID) &&
      (Payload_Length <= QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_LENGTH_MAXIMUM) &&
      (Payload_Type <= QAPI_BLE_HCI_VS_PROD_TEST_PAYLOAD_TYPE_ALTERNATE_BITS_REVERSE) &&
      ((Packet_Type >= QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_LE_1M) && (Packet_Type <= QAPI_BLE_HCI_VS_PROD_TEST_PACKET_TYPE_SIMULTANEOUS_SCAN)) &&
      (Transmit_Output_Power <= QAPI_BLE_HCI_VS_PROD_TEST_TRANSMIT_OUTPUT_POWER_MAXIMUM) &&
      (StatusResult) &&
      (SubOpCode))
   {
      /* Format command.                                                */
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Sub_Op_Code), QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_LE_TX_BURST);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Hop_Channels), Hop_Channels);
      QAPI_BLE_ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&((&CommandBuffer)->Payload_Length), Payload_Length);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Payload_Type), Payload_Type);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Packet_Type), Packet_Type);
      QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((&CommandBuffer)->Transmit_Output_Power), Transmit_Output_Power);

      /* This function requires a response buffer if we are waiting for */
      /* a response, even if we are not using it.                       */
      /* * NOTE * The Status field is decoded by the function so we     */
      /*          don't have to decode it.                              */
      ResponseBufferLength = (QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_BURST_COMMAND_COMPLETE_EVENT_SIZE - QAPI_BLE_HCI_COMMAND_COMPLETE_EVENT_HEADER_SIZE);

      ret_val = qapi_BLE_HCI_Send_Raw_Command(BluetoothStackID,
                                              QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF,
                                              QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_CODE_OCF,
                                              QAPI_BLE_HCI_VS_PROD_TEST_LE_TX_BURST_COMMAND_SIZE,
                                              (uint8_t *)&CommandBuffer,
                                              StatusResult,
                                              &ResponseBufferLength,
                                              (uint8_t *)&(ResponseBuffer.Status),
                                              TRUE);

      /* Small optimization here. Since we only issue one command at a  */
      /* time the SubOpCode will always be the same as the SubOpCode    */
      /* that is passed to the controller.                              */
      *SubOpCode = QAPI_BLE_HCI_VS_PROD_TEST_COMMAND_SUB_OP_CODE_LE_TX_BURST;
   }
   else
   {
      ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }

   return(ret_val);
}


