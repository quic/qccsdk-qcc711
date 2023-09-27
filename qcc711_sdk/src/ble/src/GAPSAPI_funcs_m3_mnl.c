/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#include "qapi_ble_gaps.h"
#include "qapi_ble_gapstypes.h"
#include "GAPSAPI_params.h"
#include "GAPSAPI_cb_m3.h"
#include "qapi_ble_gap.h"
#include "qapi_ble_errors.h"
#include "qapi_ble_hci.h"
#include "qapi_radio.h"
#include "GAPAPI_mnl_util.h"
#include "ipc.h"
#include "callback.h"
#include "id_list.h"
#include <string.h>
#include "stringl.h"

   /* AES-CCM related defines.                                          */
#define GAP_LE_AES_CCM_MIC_SIZE                   4
#define GAP_LE_AES_CCM_MIN_NONCE_LENGTH           7
#define GAP_LE_AES_CCM_MAX_NONCE_LENGTH           13

   /* HCI VS Command definitions.                                       */
#define HCI_VS_ESL_OCF                            0x28
#define HCI_VS_ESL_SUBOPCODE_AES_CCM_OPERATION    0x13
#define HCI_VS_ESL_AES_CCM_OP_DECRYPT             0x00
#define HCI_VS_ESL_AES_CCM_OP_ENCRYPT             0x01

#define HCI_VS_ESL_SUBOPCODE_OFFSET                        (0)
#define HCI_VS_ESL_AES_CCM_OP_ENCRYPT_DECRYPT_POS          (HCI_VS_ESL_SUBOPCODE_OFFSET + sizeof(uint8_t))
#define HCI_VS_ESL_AES_CCM_OP_KEY_POS                      (HCI_VS_ESL_AES_CCM_OP_ENCRYPT_DECRYPT_POS + sizeof(uint8_t))
#define HCI_VS_ESL_AES_CCM_OP_NONCE_LEN_POS                (HCI_VS_ESL_AES_CCM_OP_KEY_POS + sizeof(qapi_BLE_Encryption_Key_t))
#define HCI_VS_ESL_AES_CCM_OP_DATA_LEN_POS                 (HCI_VS_ESL_AES_CCM_OP_NONCE_LEN_POS + sizeof(uint8_t))
#define HCI_VS_ESL_AES_CCM_OP_NONCE_POS                    (HCI_VS_ESL_AES_CCM_OP_DATA_LEN_POS + sizeof(uint32_t))
#define HCI_VS_ESL_AES_CCM_OP_DATA_PTR_POS                 (HCI_VS_ESL_AES_CCM_OP_NONCE_POS + GAP_LE_AES_CCM_MAX_NONCE_LENGTH)
#define HCI_VS_ESL_AES_CCM_OP_COMMAND_LENGTH               (HCI_VS_ESL_AES_CCM_OP_DATA_PTR_POS + sizeof(uint32_t))

#define HCI_VS_ESL_RESPONSE_STATUS_OFFSET                  (0)
#define HCI_VS_ESL_RESPONSE_SUBOPCODE_OFFSET               (HCI_VS_ESL_RESPONSE_STATUS_OFFSET + sizeof(uint8_t))
#define HCI_VS_ESL_RESPONSE_LENGTH                         (HCI_VS_ESL_RESPONSE_SUBOPCODE_OFFSET + sizeof(uint8_t))

   /* The following is a utility MACRO that exists to Assign a          */
   /* specified DWord_t to an unaligned Memory Address.  This MACRO     */
   /* accepts as it's first parameter the Memory Address to store the   */
   /* specified Little Endian DWord_t into.  The second parameter is the*/
   /* actual DWord_t value to store into the specified Memory Location. */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD(_x, _y)  \
{                                                                   \
  ((uint8_t *)(_x))[0] = ((uint8_t)(((uint32_t)(_y)) & 0xFF));         \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint32_t)(_y)) >> 8) & 0xFF));  \
  ((uint8_t *)(_x))[2] = ((uint8_t)((((uint32_t)(_y)) >> 16) & 0xFF)); \
  ((uint8_t *)(_x))[3] = ((uint8_t)((((uint32_t)(_y)) >> 24) & 0xFF)); \
}


   /* As an internal function no check is done on the internal          */
   /* parameters.                                                       */
static int SendHCIVSAESCCMOperation(uint32_t BluetoothStackID, uint8_t Operation, qapi_BLE_Encryption_Key_t *Key, uint8_t NonceLength, uint8_t *Nonce, uint32_t DataLength, uint8_t *Data)
{
   int     ret_val;
   uint8_t Status;
   uint8_t LengthResult;
   uint8_t CommandBuffer[HCI_VS_ESL_AES_CCM_OP_COMMAND_LENGTH];
   uint8_t ReturnBuffer[HCI_VS_ESL_RESPONSE_LENGTH];

   /* Cap the nonce.                                                    */
   if(NonceLength > GAP_LE_AES_CCM_MAX_NONCE_LENGTH)
      NonceLength = GAP_LE_AES_CCM_MAX_NONCE_LENGTH;

   /* Format the command.                                               */
   memset(CommandBuffer, 0, HCI_VS_ESL_AES_CCM_OP_COMMAND_LENGTH);

   CommandBuffer[HCI_VS_ESL_SUBOPCODE_OFFSET]               = HCI_VS_ESL_SUBOPCODE_AES_CCM_OPERATION;
   CommandBuffer[HCI_VS_ESL_AES_CCM_OP_ENCRYPT_DECRYPT_POS] = Operation;

   memcpy(&(CommandBuffer[HCI_VS_ESL_AES_CCM_OP_KEY_POS]), Key, sizeof(qapi_BLE_Encryption_Key_t));

   CommandBuffer[HCI_VS_ESL_AES_CCM_OP_NONCE_LEN_POS]       = NonceLength;

   ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD(&(CommandBuffer[HCI_VS_ESL_AES_CCM_OP_DATA_LEN_POS]), DataLength);

   memcpy(&(CommandBuffer[HCI_VS_ESL_AES_CCM_OP_NONCE_POS]), Nonce, NonceLength);

   ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD(&(CommandBuffer[HCI_VS_ESL_AES_CCM_OP_DATA_PTR_POS]), (uint32_t)Data);

   /* Send the command.                                                 */
   memset(ReturnBuffer, 0, sizeof(ReturnBuffer));

   Status       = 0;
   LengthResult = sizeof(ReturnBuffer);

   ret_val = qapi_BLE_HCI_Send_Raw_Command(BluetoothStackID, QAPI_BLE_HCI_COMMAND_CODE_VENDOR_SPECIFIC_DEBUG_OGF, HCI_VS_ESL_OCF, sizeof(CommandBuffer), CommandBuffer, &Status, &LengthResult, ReturnBuffer, TRUE);
   if((ret_val == 0) && (Status == 0))
   {
      if((LengthResult >= HCI_VS_ESL_RESPONSE_LENGTH) && (ReturnBuffer[HCI_VS_ESL_RESPONSE_STATUS_OFFSET] == QAPI_BLE_HCI_ERROR_CODE_NO_ERROR) && (ReturnBuffer[HCI_VS_ESL_RESPONSE_SUBOPCODE_OFFSET] == HCI_VS_ESL_SUBOPCODE_AES_CCM_OPERATION))
         ret_val = 0;
      else
         ret_val = QAPI_BLE_BTPS_ERROR_VS_HCI_ERROR;
   }
   else
      ret_val = QAPI_BLE_BTPS_ERROR_DEVICE_HCI_ERROR;

   return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Set_Device_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *DeviceName)
{
    GAPS_Set_Device_Name_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t NameLength;

    if(DeviceName != NULL)
    {
        NameLength = strlen(DeviceName);
    }
    else
        NameLength = 0;

    if(NameLength > QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH)
    {
        /* Truncate a string that is too long here rather than sending the whole thing over IPC. */
        NameLength = QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH;
    }


    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(GAPS_SET_DEVICE_NAME_PARAMS_SIZE) + NameLength + 1)))
    {
        Offset = ALIGN32(GAPS_SET_DEVICE_NAME_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(DeviceName != NULL)
        {
            Params->DeviceName = (char *)(((uint8_t *)Params) + Offset);
            Offset += NameLength + 1;
            memscpy(Params->DeviceName, NameLength, DeviceName, NameLength);

            /* Ensure it is null-terminated. */
            Params->DeviceName[NameLength] = 0;
        }
        else
        {
            Params->DeviceName = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_SET_DEVICE_NAME, Offset, (uint8_t *)Params);

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_BLE_GAPS_Query_Device_Name(uint32_t BluetoothStackID, uint32_t InstanceID, char *NameBuffer)
{
    GAPS_Query_Device_Name_Params_t *Params;
    int ret_val = -1;
    uint32_t Offset;
    uint32_t NameLength;

    if(NULL != (Params = IPC_GetSharedMemory(ALIGN32(GAPS_QUERY_DEVICE_NAME_PARAMS_SIZE) + QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH)))
    {
        Offset = ALIGN32(GAPS_QUERY_DEVICE_NAME_PARAMS_SIZE);
        Params->BluetoothStackID = BluetoothStackID;
        Params->InstanceID = InstanceID;
        if(NameBuffer != NULL)
        {
            Params->NameBuffer = (char *)(((uint8_t *)Params) + Offset);
            Offset += QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH;
        }
        else
        {
            Params->NameBuffer = NULL;
        }

        ret_val = (int)IPC_SendFunctionCall(FILE_ID_GAPSAPI, FUNCTION_ID_GAPS_QUERY_DEVICE_NAME, Offset, (uint8_t *)Params);

        if(ret_val == 0)
        {
            NameLength = strlen(Params->NameBuffer);

            /* The stack should never give us a string too long, but just to be sure. */
            if(NameLength > QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH)
            {
                NameLength = QAPI_BLE_GAP_MAXIMUM_DEVICE_NAME_LENGTH;
            }

            memscpy(NameBuffer, NameLength, Params->NameBuffer, NameLength);

            /* Ensure the string is null-terminated. */
            NameBuffer[NameLength] = 0;
        }

        IPC_FreeSharedMemory(Params);
    }

    return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_ble_GAP_LE_AES_CCM_Decrypt(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_AES_CCM_Decryption_Parameters_t *DecryptionParameters)
{
   int ret_val;

   /* Verify the input parameters.                                      */
   if((DecryptionParameters != NULL) && (DecryptionParameters->Nonce_Length >= GAP_LE_AES_CCM_MIN_NONCE_LENGTH) && (DecryptionParameters->Nonce_Length <= GAP_LE_AES_CCM_MAX_NONCE_LENGTH) && (DecryptionParameters->Nonce != NULL))
   {
      /* Verify that we have enough data to have valid decryption.      */
      if((DecryptionParameters->Encrypted_Data_Length > GAP_LE_AES_CCM_MIC_SIZE) && (DecryptionParameters->Encrypted_Data != NULL))
      {
         /* Attempt to enable memory access to M0 for this memory blob. */
         ret_val = APSS_Buffer_Allow_Access_For_BTSS(DecryptionParameters->Encrypted_Data_Length,  DecryptionParameters->Encrypted_Data, TRUE);
         if(ret_val == GAP_ERROR_BUFFER_STATUS_OK)
         {
            /* Suspend the radio.                                       */
            if(qapi_Radio_Suspend(BluetoothStackID) == QAPI_OK)
            {
               /* Send the command to do the decryption.                */
               ret_val = SendHCIVSAESCCMOperation(BluetoothStackID, HCI_VS_ESL_AES_CCM_OP_DECRYPT, &(DecryptionParameters->Decryption_Key), DecryptionParameters->Nonce_Length, DecryptionParameters->Nonce, DecryptionParameters->Encrypted_Data_Length, DecryptionParameters->Encrypted_Data);
               if(!ret_val)
               {
                  /* Adjust plaintext length since the encrypted data   */
                  /* length includes a MIC added to the end.            */
                  DecryptionParameters->Plaintext_Data_Length = DecryptionParameters->Encrypted_Data_Length - GAP_LE_AES_CCM_MIC_SIZE;
               }

               /* Operation is complete go ahead and resume the radio.  */
               qapi_Radio_Resume(BluetoothStackID);
            }
            else
               ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

            /* Regardless or return result, revoke access to APSS memory*/
            /* for this block.                                          */
            APSS_Buffer_Revoke_Access_From_BTSS(DecryptionParameters->Encrypted_Data_Length,  DecryptionParameters->Encrypted_Data);
         }
      }
      else
         ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }
   else
      ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

   return(ret_val);
}

int QAPI_BLE_BTPSAPI qapi_ble_GAP_LE_AES_CCM_Encrypt(uint32_t BluetoothStackID, qapi_BLE_GAP_LE_AES_CCM_Encryption_Parameters_t *EncryptionParameters)
{
   int ret_val;

   /* Verify the input parameters.                                      */
   if((EncryptionParameters != NULL) && (EncryptionParameters->Nonce_Length >= GAP_LE_AES_CCM_MIN_NONCE_LENGTH) && (EncryptionParameters->Nonce_Length <= GAP_LE_AES_CCM_MAX_NONCE_LENGTH) && (EncryptionParameters->Nonce != NULL))
   {
      /* Verify that we have enough data to have valid decryption.      */
      if((EncryptionParameters->Plaintext_Data_Length > 0) && (EncryptionParameters->Plaintext_Data != NULL))
      {
         /* Attempt to enable memory access to M0 for this memory blob. */
         /* Make sure we enable access to the MIC that will be at the   */
         /* end of the encrypted data (which is encrypted inline).      */
         ret_val = APSS_Buffer_Allow_Access_For_BTSS((EncryptionParameters->Plaintext_Data_Length + GAP_LE_AES_CCM_MIC_SIZE),  EncryptionParameters->Plaintext_Data, TRUE);
         if(ret_val == GAP_ERROR_BUFFER_STATUS_OK)
         {
            /* Suspend the radio.                                       */
            if(qapi_Radio_Suspend(BluetoothStackID) == QAPI_OK)
            {
               /* Send the command to do the decryption.                */
               ret_val = SendHCIVSAESCCMOperation(BluetoothStackID, HCI_VS_ESL_AES_CCM_OP_ENCRYPT, &(EncryptionParameters->Encryption_Key), EncryptionParameters->Nonce_Length, EncryptionParameters->Nonce, EncryptionParameters->Plaintext_Data_Length, EncryptionParameters->Plaintext_Data);
               if(!ret_val)
               {
                  /* Adjust encrypted data length since it no includes  */
                  /* the MIC.                                           */
                  EncryptionParameters->Encrypted_Data_Length = EncryptionParameters->Plaintext_Data_Length + GAP_LE_AES_CCM_MIC_SIZE;
               }

               /* Operation is complete go ahead and resume the radio.  */
               qapi_Radio_Resume(BluetoothStackID);
            }
            else
               ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

            /* Regardless or return result, revoke access to APSS memory*/
            /* for this block.                                          */
            APSS_Buffer_Revoke_Access_From_BTSS((EncryptionParameters->Plaintext_Data_Length + GAP_LE_AES_CCM_MIC_SIZE),  EncryptionParameters->Plaintext_Data);
         }
      }
      else
         ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;
   }
   else
      ret_val = QAPI_BLE_BTPS_ERROR_INVALID_PARAMETER;

   return(ret_val);
}

