/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
   RAM application for programming NVM via GDB.

   Non-static functions in this file are invoked directly by the programming
   tool. Parameters are provided via ParameterBuffer and the result is
   returned via the ResultBuffer.
*/

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "qcc710.h"
#include "qapi_power.h"
#include "qapi_fuse.h"
#include "qapi_nvm.h"
#include "qapi_types.h"
#include "qapi_rot.h"
#include "qapi_firmware_update.h"
#include "qapi_timer.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/

/* General purpose breakpoint to give control back to the script. */
#if defined(__ICCARM__)
   #define BKPT()          asm("bkpt #0")
#else
   #define BKPT()          __asm__("bkpt #0")
#endif

#define PARAMETER_BUFFER_SIZE                               (8)    /**< Size of the buffer used to provide parameters to the functions. */
#define RESULT_BUFFER_SIZE                                  (8)    /**< Size of the buffer used to return a result to the scipt. */
#define DATA_BUFFER_SIZE                                    (4096) /**< Size of the buffer used to hold the data to be written to NVM. */

#define RESULT_SUCCESS                                      (0)    /**< Return value indicating a flash operation was successful. */
#define RESULT_FAILED                                       (1)    /**< Return value indicating a flash operation failed. */
#define RESULT_INVALID_ADDRESS                              (2)    /**< Return value indicating an invalid address was provided. */
#define RESULT_BUSY                                         (3)    /**< Return value indicating an operation is busy. */
#define RESULT_VERIFICATION_AUTH_FAILURE                    (4)    /**< Return value indicating an update package authentication failure. */
#define RESULT_VERIFICATION_INVALID_INPUT                   (5)    /**< Return value indicating the update package is invalid. */
#define RESULT_VERIFICATION_IMAGE_OVERLAP                   (6)    /**< Return value indicating the update package overlaps image. */

#define OTP_BUFFER_SIZE                                     (256)

/**
   Struture representation of the access registers for one block of NVM.
*/
typedef struct AccessReg_s
{
   uint32_t Register[3];
} AccessReg_t;

/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

/** CRC32 lookup table. */
static const uint32_t CRC32_Table[256] =
{
   0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
   0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
   0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
   0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
   0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
   0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
   0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
   0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
   0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
   0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
   0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
   0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
   0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
   0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
   0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
   0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
   0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
   0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
   0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
   0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
   0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
   0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
   0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
   0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
   0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
   0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
   0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
   0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
   0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
   0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
   0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
   0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/* Buffer for parameters to the NVM programmer functions. */
static volatile uint32_t ParameterBuffer[PARAMETER_BUFFER_SIZE];

/* Buffer for the data to be written to NVM. */
static volatile uint8_t  DataBuffer[DATA_BUFFER_SIZE];

/* Buffer for the result from the NVM rogrammer functions. */
static volatile uint32_t ResultBuffer[RESULT_BUFFER_SIZE];

uint32_t FuseAddr;
uint32_t FuseVal;
volatile uint32_t FuseSize;
qapi_Fuse_t FuseArray[64] = {{0, 0}};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

void Initialize(void);
void Cleanup(void);
void Write(void);
void Checksum(void);
void OtpWrite(void);
void OtpSecureWrite(void);
void OtpRead(void);

/**
   @brief Initializes the programming application.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void Initialize(void)
{
   qapi_Status_t Result;

   /* Set the vector table location. */
    SCB->VTOR = 0x20014000;

   Result = qapi_PWR_Initialize(NULL);

   if(Result == QAPI_OK)
   {
      Result = qapi_TMR_Init();
      if(Result == QAPI_OK)
      {
         /* Start a ROT sessiona and request access to the NVM write registers. */
         Result = qapi_ROT_Session_Start();
      }
   }

   ResultBuffer[0] = (Result == QAPI_OK) ? RESULT_SUCCESS : RESULT_FAILED;
}

void ReqWriteNvm(void)
{
   qapi_Status_t Result;
   uint16_t      BlockMask;

   Result = qapi_NVM_Request_Write();
   if(Result == QAPI_OK)
   {
      /* Set permissiosn for all of APSS NVM to read/write. */
      BlockMask = qapi_NVM_Set_Permissions(QAPI_NVM_APSS_BLOCKS_BITMASK, QAPI_NVM_PERMISSIONS_READ_WRITE_E);

      if(BlockMask != QAPI_NVM_APSS_BLOCKS_BITMASK)
      {
         Result = QAPI_ERROR;
      }
   }
   ResultBuffer[0] = (Result == QAPI_OK) ? RESULT_SUCCESS : RESULT_FAILED;
}

void RelWriteNvm(void)
{
   qapi_NVM_Release_Write();
   ResultBuffer[0] = RESULT_SUCCESS;
}

/**
   @brief Cleans up after NVM programming is done.
*/
void Cleanup(void)
{
   /* Return the control of read write registers to ROT. */
   qapi_NVM_Release_Write();
   qapi_ROT_Session_End();
   ResultBuffer[0] = RESULT_SUCCESS;
}

/**
   @brief Writes data to NVM.

   ParameterBuffer[0] Address of the write opeation.
   ParameterBuffer[1] Number of bytes to write.

   ResultBuffer[0]: Status result of the operation.
       - RESULT_SUCCESS indicates the operation has been done successfully.
       - RESULT_FAILED  indicates the operation has failed.
       - RESULT_INVALID_ADDRESS indicates the address is invalid.
*/
void Write(void)
{
   qapi_Status_t  Result;
   uint32_t       Length;
   void          *Source;
   void          *DstAddress;

   DstAddress = (void *)ParameterBuffer[0];
   Length     = ParameterBuffer[1];
   Source     = (void *)DataBuffer;

   Result = qapi_NVM_Write(DstAddress, Source, Length);

   if(Result == QAPI_OK)
   {
      ResultBuffer[0] = RESULT_SUCCESS;
   }
   else if(Result == QAPI_ERR_BOUNDS)
   {
      ResultBuffer[0] = RESULT_INVALID_ADDRESS;
   }
   else
   {
      ResultBuffer[0] = RESULT_FAILED;
   }
}

/**
   @brief Calculates the CRC32 checksum for a section of memory.

   ParameterBuffer[0] Address of data to verify.
   ParameterBuffer[1] Number of bytes to be verified.

   ResultBuffer[0]: Status result of the operation.
       - RESULT_SUCCESS indicates the operation has been done successfully.
       - RESULT_FAILED  indicates the operation has failed.
*/
void Checksum(void)
{
   uint32_t  Length;
   uint32_t  Result;
   uint8_t  *Address;

   Result  = 0xFFFFFFFF;
   Address = (uint8_t *)ParameterBuffer[0];
   Length  = ParameterBuffer[1];

   while(Length != 0)
   {
      Result = CRC32_Table[(Result ^ *Address) & 0xFF] ^ (Result >> 8);
      Address ++;
      Length --;
   }

   ResultBuffer[0] = RESULT_SUCCESS;
   ResultBuffer[1] = Result ^ 0xFFFFFFFF;
}

/**
   @brief Verify the secure programmer image.

   ParameterBuffer[0] The location of the update image in NVM.
   ParameterBuffer[1] Package size.

   ResultBuffer[0]: Status result of the operation.
       - RESULT_SUCCESS indicates the operation has been done successfully.
       - RESULT_FAILED  indicates the operation has failed.
       - RESULT_INVALID_ADDRESS indicates the address is invalid.
*/
void VerifyUpdate(void)
{
   qapi_Status_t                     Result;
   qapi_FWUP_Verify_Update_Package_t VerifyUpdateParam;

   VerifyUpdateParam.Location        = ParameterBuffer[0];
   VerifyUpdateParam.Size            = ParameterBuffer[1];
   VerifyUpdateParam.VerifyAllImages = (qbool_t)ParameterBuffer[2];

   Result = qapi_FWUP_Verify_Update_Package(&VerifyUpdateParam, NULL, NULL);

   if(Result == QAPI_OK)
   {
      switch(VerifyUpdateParam.VerificationStatus)
      {
         case QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E:
            ResultBuffer[0] = RESULT_SUCCESS;
            break;

         case QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E:
            ResultBuffer[0] = RESULT_VERIFICATION_AUTH_FAILURE;
            break;

         case QAPI_FWUP_VERIFICATION_INVALID_INPUT_E:
            ResultBuffer[0] = RESULT_VERIFICATION_INVALID_INPUT;
            break;

         case QAPI_FWUP_VERIFICATION_IMAGE_OVERLAP_E:
            ResultBuffer[0] = RESULT_VERIFICATION_IMAGE_OVERLAP;
            break;

         default:
            ResultBuffer[0] = RESULT_FAILED;
            break;
      }
   }
   else if(Result == QAPI_ERR_BUSY)
   {
      ResultBuffer[0] = RESULT_BUSY;
   }
   else
   {
      ResultBuffer[0] = RESULT_FAILED;
   }
}

/**
   @brief Verify the secure programmer image.

   ParameterBuffer[0] The location of the update image in NVM.
   ParameterBuffer[1] Package size.
   ParameterBuffer[2] Flag indicates if debug should be locked.

   ResultBuffer[0]: Status result of the operation.
       - RESULT_SUCCESS indicates the operation has been done successfully.
       - RESULT_FAILED  indicates the operation has failed.
       - RESULT_INVALID_ADDRESS indicates the address is invalid.
*/
void ApplyUpdate(void)
{
    qapi_FWUP_Apply_Update_Package_t UpdateParam;

    UpdateParam.Location  = ParameterBuffer[0];
    UpdateParam.Size      = ParameterBuffer[1];
    UpdateParam.LockDebug = (qbool_t)ParameterBuffer[2];

    qapi_FWUP_Apply_Update_Package(&UpdateParam);

    /* qapi_FWUP_Apply_Update should not return. */
    ResultBuffer[0] = RESULT_FAILED;
}

/**
   @brief Perform an OTP Secure write.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void OtpSecureWrite(void)
{
    qapi_Status_t ret = QAPI_ERROR;

    ret = qapi_Fuse_Write_Secure_Fuse((uint8_t*)FuseArray, FuseSize, NULL, NULL);
    if (ret == QAPI_OK)
        ResultBuffer[0] = RESULT_SUCCESS;
    else
        ResultBuffer[0] = RESULT_FAILED;
}

/**
   @brief Read an OTP field.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void OtpRead()
{
    qapi_Status_t ret = QAPI_ERROR;

    ret = qapi_Fuse_Read(FuseAddr, &FuseVal);

    if (ret == QAPI_OK)
        ResultBuffer[0] = RESULT_SUCCESS;
    else
        ResultBuffer[0] = RESULT_FAILED;
}

/**
   @brief Write to an OTP field.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void OtpWrite()
{
    qapi_Status_t ret = QAPI_ERROR;

    ret = qapi_Fuse_Write(FuseAddr, FuseVal);

    if (ret == QAPI_OK)
        ResultBuffer[0] = RESULT_SUCCESS;
    else
        ResultBuffer[0] = RESULT_FAILED;
}

/**
   @brief Read multiple OTP fields.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void OtpReadMultiple()
{
    qapi_Status_t ret = QAPI_ERROR;

    ret = qapi_Fuse_Read_Multiple(FuseArray, FuseSize, NULL, NULL);

    if (ret == QAPI_OK)
        ResultBuffer[0] = RESULT_SUCCESS;
    else
        ResultBuffer[0] = RESULT_FAILED;
}

/**
   @brief Write to multiple OTP fields.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void OtpWriteMultiple()
{
    qapi_Status_t ret = QAPI_ERROR;

    ret = qapi_Fuse_Write_Multiple(FuseArray, FuseSize, NULL, NULL);

    if (ret == QAPI_OK)
        ResultBuffer[0] = RESULT_SUCCESS;
    else
        ResultBuffer[0] = RESULT_FAILED;
}

/**
   Main entry point.
*/
int main(void)
{
   BKPT();

   /* Call each function to make sure it is referenced. */
   Initialize();
   OtpWrite();
   OtpRead();
   OtpReadMultiple();
   OtpWriteMultiple();
   OtpSecureWrite();
   ReqWriteNvm();
   Write();
   Checksum();
   RelWriteNvm();
   Cleanup();
   VerifyUpdate();
   ApplyUpdate();

   while(1) {}
}

