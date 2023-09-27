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
#include "qapi_types.h"
#include "qapi_fuse.h"
#include "qapi_rot.h"
#include "qapi_timer.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/

/* General purpose breakpoint to give control back to the script. */
#if   defined(__ICCARM__)
   #define BKPT()          asm("bkpt #0")
#else
   #define BKPT()          __asm__("bkpt #0")
#endif

#define APSS_ID                                             (1)    /**< The APSS ID. */

#define PARAMETER_BUFFER_SIZE                               (8)    /**< Size of the buffer used to provide parameters to the functions. */
#define RESULT_BUFFER_SIZE                                  (8)    /**< Size of the buffer used to return a result to the scipt. */
#define DATA_BUFFER_SIZE                                    (256) /**< Size of the buffer used to hold the data to be written to NVM. */

#define RESULT_SUCCESS                                      (0)    /**< Return value indicating a flash/otp operation was successful. */
#define RESULT_FAILED                                       (1)    /**< Return value indicating a flash/otp operation failed. */
#define RESULT_INVALID_ADDRESS                              (2)    /**< Return value indicating an invalid address was provided. */

#define OTP_BUFFER_SIZE                                     (256)


/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

/* Buffer for the result from the NVM rogrammer functions. */
volatile int8_t ResultBuffer[RESULT_BUFFER_SIZE];

uint32_t FuseAddr;
uint32_t FuseVal;
volatile uint32_t FuseSize;
qapi_Fuse_t FuseArray[64] = {{0, 0}};
int rot_status = -1;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
void OtpWrite(void);
void OtpSecureWrite(void);
void OtpRead(void);

/**
   @brief Initializes the OTP programming application.

   ResultBuffer[0]: Status result of the operation.
      - RESULT_SUCCESS indicates the operation has been done successfully.
      - RESULT_FAILED  indicates the operation has failed.
*/
void Initialize(void)
{
    qapi_Status_t ret;

   /* Set the vector table location. */
    SCB->VTOR = 0x20014000;

    ret = qapi_PWR_Initialize(NULL);
    if(ret == QAPI_OK)
    {
        ret = qapi_TMR_Init();
        if(ret == QAPI_OK)
        {
            ret = qapi_ROT_Session_Start();
        }
    }

    ResultBuffer[0] = (ret == QAPI_OK) ? RESULT_SUCCESS : RESULT_FAILED;
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

    while(1) {}
}

