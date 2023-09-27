/*
 * Copyright (c) 2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <string.h>
#include "stringl.h"

#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_ble_errors.h"
#include "qapi_ble_bsc.h"
#include "qapi_ble_dtm.h"
#include "qapi_ble_hci.h"
#include "qapi_ble_hcicommt.h"
#include "qapi_ble_hcitypes.h"

#define HCI_CMD_HEADER_LENGTH       3
#define HCI_ACL_HEADER_LENGTH       4
#define HCI_SCO_HEADER_LENGTH       3

#define HCI_PACKET_TYPE_OFFSET               (0)
#define HCI_PACKET_HEADER_OFFSET             (1)
#define HCI_PACKET_COMMAND_DATA_OFFSET       (HCI_PACKET_HEADER_OFFSET + QAPI_BLE_HCI_COMMAND_HEADER_SIZE)
#define HCI_PACKET_LENGTH_OFFSET             (3)

typedef enum
{
   rsTYPE,
   rsHEADER,
   rsDATA
} RxState_t;

typedef struct BLE_DTM_Context_s
{
   unsigned int            BluetoothStackID;
   qapi_BLE_DTM_Callback_t Callback;
   unsigned long           CallbackParameter;

   RxState_t               RxState;
   uint32_t                RxIndex;
   uint32_t                RxLength;
   uint8_t                 RxBuffer[1 + QAPI_BLE_HCI_COMMAND_MAX_SIZE];
} BLE_DTM_Context_t;

static BLE_DTM_Context_t *BLE_DTM_Context;

   /* List of OGFs for which all opcodes are allowed. */
static const uint8_t BLE_DTM_Allowed_OGF_List[] =
{
   QAPI_BLE_HCI_COMMAND_CODE_INFORMATIONAL_PARAMETERS_OGF,
   QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF
};

#define BLE_DTM_ALLOWED_OGF_LIST_SIZE     (sizeof(BLE_DTM_Allowed_OGF_List) / sizeof(uint8_t))

   /* List of opcodes to allow. */
static const uint16_t BLE_DTM_Allowed_Opcode_List[] =
{
   QAPI_BLE_HCI_COMMAND_OPCODE_RESET,
   QAPI_BLE_HCI_COMMAND_OPCODE_SET_EVENT_MASK,
   QAPI_BLE_HCI_COMMAND_OPCODE_SET_EVENT_MASK_PAGE_2,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_SET_EVENT_MASK,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_RECEIVER_TEST,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_TEST_END,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENHANCED_RECEIVER_TEST,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_ENHANCED_TRANSMITTER_TEST,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_RECEIVER_TEST_V3,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST_V3,
   QAPI_BLE_HCI_COMMAND_OPCODE_LE_TRANSMITTER_TEST_V4
};

#define BLE_DTM_ALLOWED_OPCODE_LIST_SIZE     (sizeof(BLE_DTM_Allowed_Opcode_List) / sizeof(uint16_t))

static int DTM_Process_Packet(void);
static void QAPI_BLE_BTPSAPI DTM_Debug_Callback(uint32_t BluetoothStackID, boolean_t PacketSent, qapi_BLE_HCI_Packet_t *HCIPacket, unsigned long CallbackParameter);

/**
 * @brief
 * Applies op-code filter and processes the command in the receive buffer.
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an Error occurred. Possible values are:
 */
static int DTM_Process_Packet(void)
{
   int       RetVal;
   uint16_t  Opcode;
   uint8_t   OGF;
   uint16_t  OCF;
   uint8_t   Length;
   uint8_t  *Data;
   uint32_t  Index;
   qbool_t   AllowCommand;

   /* Only process command packets. */
   if(BLE_DTM_Context->RxBuffer[HCI_PACKET_TYPE_OFFSET] == QAPI_BLE_HCI_COMMAND_PACKET_E)
   {
      /* Parse the packet header. */
      Opcode = QAPI_BLE_READ_UNALIGNED_WORD_LITTLE_ENDIAN(&(BLE_DTM_Context->RxBuffer[HCI_PACKET_HEADER_OFFSET]));
      OGF    = (uint8_t)(Opcode >> 10);
      OCF    = Opcode & 0x3FF;
      Length = QAPI_BLE_READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(BLE_DTM_Context->RxBuffer[HCI_PACKET_LENGTH_OFFSET]));
      Data   = &(BLE_DTM_Context->RxBuffer[HCI_PACKET_COMMAND_DATA_OFFSET]);

      /* Sanity check the length (this should never fail). */
      if((HCI_PACKET_COMMAND_DATA_OFFSET + Length) == BLE_DTM_Context->RxLength)
      {
         /* Apply the OGF/OCF filter. */
         AllowCommand = false;
         /* See if the comamnd's OGF is allowed. */
         for(Index = 0; Index < BLE_DTM_ALLOWED_OGF_LIST_SIZE; Index++)
         {
            if(OGF == BLE_DTM_Allowed_OGF_List[Index])
            {
               AllowCommand = true;
               break;
            }
         }

         if(!AllowCommand)
         {
            /* OGF wasn't found so see if the opcode is allowed. */
            for(Index = 0; Index < BLE_DTM_ALLOWED_OPCODE_LIST_SIZE; Index++)
            {
               if(Opcode == BLE_DTM_Allowed_Opcode_List[Index])
               {
                  AllowCommand = true;
                  break;
               }
            }
         }

         if(AllowCommand)
         {
            /* Command allowed. */
            RetVal = qapi_BLE_HCI_Send_Raw_Command(BLE_DTM_Context->BluetoothStackID, OGF, OCF, Length, Data, NULL, NULL, NULL, false);
         }
         else
         {
            /* Filtered packet, treat it as a success. */
            RetVal = QAPI_OK;
         }
      }
      else
      {
         RetVal = QAPI_ERROR;
      }
   }
   else
   {
      RetVal = QAPI_BLE_BTPS_ERROR_ACTION_NOT_ALLOWED;
   }

   return RetVal;
}

/**
 * @brief
 * Debug callback for DTM related HCI events.
 *
 * @param[in]  BluetoothStackID   Bluetooth Stack ID of the stack that the HCI
 *                                packet was sent from.
 *
 * @param[in]  PacketSent         Boolean value that indicates TRUE if the
 *                                packet was sent or FALSE if it was received.
 *
 * @param[in]  HCIPacket          Pointer to the packet contents.
 *
 * @param[in]  CallbackParameter  User-defined parameter (e.g., tag value) that
 *                                was defined in the callback registration.
 *
 * @return
 * None.
 */
static void QAPI_BLE_BTPSAPI DTM_Debug_Callback(uint32_t BluetoothStackID, boolean_t PacketSent, qapi_BLE_HCI_Packet_t *HCIPacket, unsigned long CallbackParameter)
{
   qapi_BLE_DTM_Callback_t LocalCallback;
   unsigned long           LocalCallbackParameter;
   uint8_t                 Type;

   if(HCIPacket->HCIPacketType == QAPI_BLE_HCI_EVENT_PACKET_E)
   {
      qapi_TSK_Enter_Critical();
      if(BLE_DTM_Context != NULL)
      {
         LocalCallback          = BLE_DTM_Context->Callback;
         LocalCallbackParameter = BLE_DTM_Context->CallbackParameter;
      }
      else
      {
         LocalCallback = NULL;
         LocalCallbackParameter = 0;
      }
      qapi_TSK_Exit_Critical();

      if(LocalCallback != NULL)
      {
         Type = (uint8_t)QAPI_BLE_HCI_EVENT_PACKET_E;
         (*LocalCallback)(sizeof(Type), &Type, LocalCallbackParameter);
         (*LocalCallback)(HCIPacket->HCIPacketLength, (uint8_t *)(HCIPacket->HCIPacketData), LocalCallbackParameter);
      }
   }
}

/**
 * @brief
 * Initializes the Bluetooth Protocol Stack in BLE Direct Test Mode.
 *
 * As this module initializes the Bluetooth stack, it must not already be
 * initialized when this API is called.
 *
 * @param[in] Callback           Function called when event data needs to be
 *                               sent.
 *
 * @param[in] CallbackParameter  User-defined parameter passed to the callback
 *                               function.
 *
 * @return
 * Zero -- if initialization was successful.
 * Negative value -- That is an ErrorCode. Possible values are:
 *             @par
 *                 QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_DRIVER_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTPS_ERROR_HCI_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_GAP_INITIALIZATION_ERROR \n
 *                 QAPI_BLE_BTPS_ERROR_L2CAP_INITIALIZATION_ERROR
 */
int QAPI_BLE_BTPSAPI qapi_BLE_DTM_Initialize(qapi_BLE_DTM_Callback_t Callback, unsigned long CallbackParameter)
{
   int                              RetVal;
   qapi_BLE_HCI_DriverInformation_t HCI_DriverInformation;

   QAPI_BLE_HCI_DRIVER_SET_COMM_INFORMATION(&HCI_DriverInformation, 0, 0, QAPI_BLE_COMM_PROTOCOL_UART_E);

   if(BLE_DTM_Context == NULL)
   {
      BLE_DTM_Context = qapi_Malloc(sizeof(BLE_DTM_Context_t));
      if(BLE_DTM_Context != NULL)
      {
         memset(BLE_DTM_Context, 0, sizeof(BLE_DTM_Context_t));
         BLE_DTM_Context->Callback          = Callback;
         BLE_DTM_Context->CallbackParameter = CallbackParameter;

         RetVal = qapi_BLE_BSC_Initialize(&HCI_DriverInformation, 0);
         if(RetVal > 0)
         {
            BLE_DTM_Context->BluetoothStackID = (unsigned int)RetVal;

            RetVal = qapi_BLE_BSC_RegisterDebugCallback(BLE_DTM_Context->BluetoothStackID, DTM_Debug_Callback, 0);

            if(RetVal > 0)
            {
               RetVal = QAPI_OK;
            }
            else
            {
               /* Error registering the debug callback. */
               qapi_BLE_BSC_Shutdown(BLE_DTM_Context->BluetoothStackID);
               qapi_Free(BLE_DTM_Context);
            }
         }
         else
         {
            qapi_Free(BLE_DTM_Context);
         }
      }
      else
      {
         RetVal = QAPI_BLE_BTPS_ERROR_MEMORY_ALLOCATION_ERROR;
      }
   }
   else
   {
      RetVal = QAPI_BLE_BTPS_ERROR_INVALID_STATE;
   }

   return RetVal;
}

/**
 * @brief
 * Exits Direct Test Mode and Shuts down the Bluetooth Protocol Stack.
 *
 * @return
 * None.
 */
void QAPI_BLE_BTPSAPI qapi_BLE_DTM_Shutdown(void)
{
   BLE_DTM_Context_t *Local_Context;

   if(BLE_DTM_Context != NULL)
   {
      Local_Context = BLE_DTM_Context;
      BLE_DTM_Context = NULL;

      qapi_BLE_BSC_UnRegisterDebugCallback(Local_Context->BluetoothStackID);
      qapi_BLE_BSC_Shutdown(Local_Context->BluetoothStackID);
      qapi_Free(Local_Context);
   }
}

/**
 * @brief
 * Pass recieved data into the DTM module.
 *
 * @param[in]  Length  Length of the data received.
 *
 * @param[in]  Data    Pointer to the recieved data.
 *
 * @return
 * Zero -- If successful.\n
 * Negative -- If an Error occurred. Possible values are:
 */
int QAPI_BLE_BTPSAPI qapi_BLE_DTM_Receive(uint32_t Length, uint8_t *Data)
{
   int      RetVal;
   uint32_t Consumed;

   if((Length != 0) && (Data != NULL))
   {
      if(BLE_DTM_Context != NULL)
      {
         RetVal = QAPI_OK;

         /* Packetize the data. */
         while(Length > 0)
         {
            switch(BLE_DTM_Context->RxState)
            {
               case rsTYPE:
                  /* Receive the packet type. */
                  BLE_DTM_Context->RxBuffer[0] = *Data;
                  BLE_DTM_Context->RxIndex = 1;
                  Consumed = 1;
                  BLE_DTM_Context->RxState = rsHEADER;

                  if(*Data == QAPI_BLE_HCI_COMMAND_PACKET_E)
                  {
                     BLE_DTM_Context->RxLength = 1 + HCI_CMD_HEADER_LENGTH;
                  }
                  else if(*Data == QAPI_BLE_HCI_ACL_DATA_PACKET_E)
                  {
                     BLE_DTM_Context->RxLength = 1 + HCI_ACL_HEADER_LENGTH;
                  }
                  else if(*Data == QAPI_BLE_HCI_SCO_DATA_PACKET_E)
                  {
                     BLE_DTM_Context->RxLength = 1 + HCI_SCO_HEADER_LENGTH;
                  }
                  else
                  {
                     /* Unknown packet type. */
                     BLE_DTM_Context->RxState = rsTYPE;
                  }
                  break;

               case rsHEADER:
                  /* Receive the full header. */
                  Consumed = BLE_DTM_Context->RxLength - BLE_DTM_Context->RxIndex;
                  if(Consumed > Length)
                  {
                     Consumed = Length;
                  }

                  memscpy(&(BLE_DTM_Context->RxBuffer[BLE_DTM_Context->RxIndex]), QAPI_BLE_HCI_COMMAND_MAX_SIZE - BLE_DTM_Context->RxIndex, Data, Consumed);
                  BLE_DTM_Context->RxIndex += Consumed;

                  if(BLE_DTM_Context->RxIndex == BLE_DTM_Context->RxLength)
                  {
                     /* Entire header has been received. */
                     if((BLE_DTM_Context->RxBuffer[0] == QAPI_BLE_HCI_COMMAND_PACKET_E) || (BLE_DTM_Context->RxBuffer[0] == QAPI_BLE_HCI_SCO_DATA_PACKET_E))
                     {
                        BLE_DTM_Context->RxLength += QAPI_BLE_READ_UNALIGNED_BYTE_LITTLE_ENDIAN(&(BLE_DTM_Context->RxBuffer[HCI_PACKET_LENGTH_OFFSET]));
                     }
                     else
                     {
                        BLE_DTM_Context->RxLength += QAPI_BLE_READ_UNALIGNED_WORD_LITTLE_ENDIAN(&(BLE_DTM_Context->RxBuffer[HCI_PACKET_LENGTH_OFFSET]));
                     }

                     if(BLE_DTM_Context->RxIndex == BLE_DTM_Context->RxLength)
                     {
                        /* Zero length payload so just process the packet. */
                        RetVal = DTM_Process_Packet();
                        BLE_DTM_Context->RxState = rsTYPE;
                     }
                     else
                     {
                        /* Change the state to receive the data. */
                        BLE_DTM_Context->RxState = rsDATA;
                     }
                  }
                  break;

               case rsDATA:
                  /* Receive the data. */
                  Consumed = BLE_DTM_Context->RxLength - BLE_DTM_Context->RxIndex;
                  if(Consumed > Length)
                  {
                     Consumed = Length;
                  }

                  if(BLE_DTM_Context->RxBuffer[0] == QAPI_BLE_HCI_COMMAND_PACKET_E)
                  {
                     /* Only care about the data in the HCI case.  Note the HCI
                        length in an HCI packet is only 1 byte so it can't
                        overflow the buffer. */
                     memscpy(&(BLE_DTM_Context->RxBuffer[BLE_DTM_Context->RxIndex]), QAPI_BLE_HCI_COMMAND_MAX_SIZE - BLE_DTM_Context->RxIndex, Data, Consumed);
                  }

                  BLE_DTM_Context->RxIndex += Consumed;

                  if(BLE_DTM_Context->RxIndex == BLE_DTM_Context->RxLength)
                  {
                     /* All data has been received so process the packet. */
                     RetVal = DTM_Process_Packet();
                     BLE_DTM_Context->RxState = rsTYPE;
                  }
                  break;

               default:
                  /* Invalid state. */
                  BLE_DTM_Context->RxState = rsTYPE;
                  Consumed = 0;
                  break;
            }

            Length -= Consumed;
            Data   += Consumed;
         }
      }
      else
      {
         RetVal = QAPI_BLE_BTPS_ERROR_INVALID_STATE;
      }
   }
   else
   {
      RetVal = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }

   return RetVal;
}

