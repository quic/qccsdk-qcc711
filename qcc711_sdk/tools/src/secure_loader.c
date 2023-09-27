/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
   Authenticated APSS Loader Demo used for load encrypted customer image to NVM.
*/

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "qcc710.h"

#include "qapi_types.h"
#include "qapi_heap.h"
#include "qapi_task.h"
#include "qapi_uart.h"
#include "qapi_power.h"
#include "qapi_timer.h"
#include "qapi_nvm.h"
#include "qapi_crypto.h"
#include "qapi_gpio.h"
#include "qapi_firmware_update.h"
#include "qapi_mtp.h"
#include "qapi_fuse.h"
#include "qapi_rot.h"
#include "qapi_ble_bsc.h"
#include "qapi_ble_hci.h"
#include "qapi_ble_hcitypes.h"

#include "ipc.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions, Constants, and Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum
{
    LOADER_MSG_ACK_E,
    /* CTRL MSG TYPE */
    LOADER_MSG_HELLO_E,
    LOADER_MSG_VERIFY_E,
    LOADER_MSG_APPLY_E,
    /* END CTRL MSG TYPE */
    /* DATA MSG TYPE */
    LOADER_MSG_MISCCTRL_E,
    LOADER_MSG_RCV_HEADER_E,
    LOADER_MSG_RCV_BLOCK_E,
    LOADER_MSG_RCV_TAG_E,
    /* END DATA MSG TYPE */
    LOADER_MSG_MAX,
} Loader_Msg_Type_t;

typedef enum
{
    LOADER_ACK_OK_E,
    LOADER_ACK_ERROR_MSG_NULL_E,
    LOADER_ACK_ERROR_CRC_E,
    LOADER_ACK_ERROR_MAGIC_E,
    LOADER_ACK_ERROR_RCV_HEADER_NO_MEMORY_E,
    LOADER_ACK_ERROR_RCV_HEADER_DERIVE_KEY_E,
    LOADER_ACK_ERROR_RCV_HEADER_NVM_WRITE_E,
    LOADER_ACK_ERROR_RCV_TAG_DECRYPTION_E,
    LOADER_ACK_ERROR_RCV_TAG_NVM_WRITE_E,
    LOADER_ACK_ERROR_RCV_TAG_CLEAR_KEY_E,
    LOADER_ACK_ERROR_RCV_TAG_NVM_RELEASE_E,
    LOADER_ACK_ERROR_VERIFY_UPDATE_E,
    LOADER_ACK_ERROR_VERIFY_BASE_E,
    LOADER_ACK_ERROR_VERIFY_AUTH_FAILURE_E,
    LOADER_ACK_ERROR_VERIFY_INVALID_INPUT_E,
    LOADER_ACK_ERROR_VERIFY_IMAGE_OVERLAP_E,
    LOADER_ACK_ERROR_APPLY_E,
    LOADER_ACK_MAX,
} Loader_ACK_Type_t;

typedef enum
{
    LOADER_KEY_DERIVED_E,
    LOADER_KEY_STATIC_E,
    LOADER_KEY_MAX,
} Loader_KEY_Type_t;

#define LOADER_UART_INSTANCE                        QAPI_UART_INSTANCE_SE2_E
#define LOADER_INPUT_BUFFER_SIZE                    (512)

#define LOADER_MSG_MAGIC                            0x4d4f4351       /* "QCOM" */

#define LOADER_SEND_HELLO_MAX_RETRY_TIMES           (3)
#define LOADER_SEND_HELLO_DELAY                     (1000000)        /* delay 1 second if doesn't receive hello msg */
#define LOADER_TSK_EVENT_UART_RX                    (1)
#define LOADER_TSK_EVENT_TIMER                      (2)
#define LOADER_ACK_MSG_SIZE                         (11)
#define LOADER_CHECK_SUM_SIZE                       (2)
#define LOADER_CTRL_MSG_HEADER_SIZE                 (8)
#define LOADER_DATA_MSG_HEADER_SIZE                 (8)
#define LOADER_IMAGE_DEFAULT_BLOCK_SIZE             (4096)
#define LOADER_IMAGE_DEFAULT_TAG_SIZE               (4)
#define LOADER_IMAGE_HEADER_SIZE_WITH_STATIC_KEY    (26)
#define LOADER_IMAGE_HEADER_SIZE_WITH_DERIVED_KEY   (86)
#define LOADER_MSG_RCV_HEADER_SIZE_WITH_STATIC_KEY  (LOADER_IMAGE_HEADER_SIZE_WITH_STATIC_KEY + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE)


/*#define TO1_SUPPORT                                 1*/

/* Utility macros */
#define A_SWAB32(_x) ((uint32_t)( \
        (((uint32_t)(_x) & (uint32_t)0x000000ffUL) << 24) | \
        (((uint32_t)(_x) & (uint32_t)0x0000ff00UL) <<  8) | \
        (((uint32_t)(_x) & (uint32_t)0x00ff0000UL) >>  8) | \
        (((uint32_t)(_x) & (uint32_t)0xff000000UL) >> 24)))

/**
   Context information for the Loader module.
*/

typedef struct Loader_MsgHeader_s
{
    uint32_t    Magic;
    uint16_t    MsgType;
    uint16_t    DataLen;
}Loader_MsgHeader_t;

typedef struct Loader_MsgCtrl_s
{
    uint32_t    Magic;
    uint16_t    MsgType;
    uint16_t    DataLen;
    uint16_t    CheckSum;
}Loader_MsgCtrl_t;

typedef struct __attribute__((packed)) Loader_MsgMiscCtrl_s
{
    uint32_t    ImageApplyAddr;
    qbool_t     LockDebug;
} Loader_MsgMiscCtrl_t;


typedef struct __attribute__((packed)) Loader_MsgACK_s
{
    uint32_t    Magic;
    uint16_t    MsgType;
    uint16_t    DataLen;
    uint8_t     Data;
    uint16_t    CheckSum;
} Loader_MsgACK_t;

typedef struct __attribute__((packed)) Loader_ImgHeader_s
{
    uint32_t    ImageSize;
    uint16_t    ImageBlockSize;
    uint8_t     KeyAlgo;
    uint8_t     BlockTagSize;
    uint8_t     IvLen;
    uint8_t     IvBlob[12];
    uint8_t     KeyType;
    union
    {
       uint8_t     NonceLabel[64];
       uint32_t    KeyID;
    }Key;
}Loader_ImgHeader_t;

typedef struct Loader_Context_s
{
   volatile qbool_t      Running;                               /**< Flag indicating the application is still running. */
   uint8_t               TimerComparator;
   uint16_t              HelloRetryTimes;                       /**< Send hello msg times. */
   qapi_TSK_Handle_t     LoaderTask;                            /**< Task for Loader demo. */
   uint16_t              ExpectRcvMsg;                          /**< The msg loader demo waiting for */
   uint16_t              ExpectRcvMsgSize;

   qapi_UART_Instance_t  LoaderUART;
   volatile qbool_t      LoaderReady;
   uint8_t               InputBuffer[LOADER_INPUT_BUFFER_SIZE]; /**< Buffer for data read from uart. */
   volatile uint32_t     InputByteCount;                        /**< Current number of bytes in the input buffer. */
   Loader_ImgHeader_t*   ImageHeader;
   uint8_t*              MsgRcvedData;                          /**< Buffer for every message, size shouble be Max msg size*/
   uint8_t*              MsgRcvedBlockTag;
   uint16_t              MsgRcvedDataMaxSize;                   /**< Max msg size, the size of MsgRcvedData */
   uint16_t              MsgRcvedLen;                           /**< received data leng for  MsgRcvedData or MsgRcvedBlockTag */
   uint16_t              ImageRcvedBlockNum;
   uint32_t              ImageSize;
   uint16_t              ImageHeaderSize;
   uint16_t              ImageBlockSize;
   uint16_t              ImageTagSize;
   uint16_t              ImageLastBlockSize;
   uint16_t              ImageTotalBlockNum;
   uint32_t              LoaderSecureImageAddr;
   qbool_t               LoaderImageLockDebug;
   uint32_t              LoaderImageNvmAddr;
} Loader_Context_t;

typedef struct Loader_Static_Key_s
{
    uint8_t key[16];
}Loader_Static_Key_t;


/*-------------------------------------------------------------------------
 * Global Variables
 *-----------------------------------------------------------------------*/

Loader_MsgACK_t MsgAck;
Loader_MsgCtrl_t MsgCtrl;
Loader_Context_t LoaderContext;
qapi_CRPT_Import_Key_Params_t ImportKeyParams;
qapi_CRPT_Derive_Key_Params_t DeriveKeyParams;
uint32_t Apply_Image_size=0;


static uint8_t ImageHeaderTable[sizeof(Loader_ImgHeader_t)];
static uint8_t ImageBlockTable[LOADER_IMAGE_DEFAULT_BLOCK_SIZE +
                            LOADER_DATA_MSG_HEADER_SIZE  +
                            LOADER_CHECK_SUM_SIZE +
                            LOADER_IMAGE_DEFAULT_TAG_SIZE];

static uint8_t ImageTagTable[LOADER_IMAGE_DEFAULT_TAG_SIZE +
                            LOADER_DATA_MSG_HEADER_SIZE  +
                            LOADER_CHECK_SUM_SIZE];

/* customer may fill this table or write the static key to OTP
 * this depends on customers.
 */
#ifndef TO1_SUPPORT
static Loader_Static_Key_t StaticKey[4] = {
    {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0,
     0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0},
     {0}, {0}, {0}};
#endif

uint8_t GlobalNonceLabel[65];

static qapi_GPIO_Alt_Config_t Alternative_GPIO_Config[QAPI_GPIO_MAX_ID_E] =
{
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO0  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO1  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO2  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO3  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO4  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO5  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO6  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO7  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO8  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO9  */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO10 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO11 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO12 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO13 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO14 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO15 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO16 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO17 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO18 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO19 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO20 */
    {2, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO21 */
    {2, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO22 */
    {2, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO23 */
    {2, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO24 */
    {0, QAPI_GPIO_INPUT_E, QAPI_GPIO_NO_PULL_E, QAPI_GPIO_FAST_2MA_E, SE_PORT_DEFAULT}, /* PIO25 */
};


/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

qbool_t InitializeLoaderDemo();
qbool_t LoderUartInit(uint32_t Instance);
void LoderUartWrite(uint32_t Length, const uint8_t *Buffer);
qbool_t LoaderWriteToNVM(uint8_t *Buffer, uint32_t BufferLen);
void LoderUartRxCallback(uint32_t Status, uint32_t Length, void *CbCtxt);
void LoaderProcessMsg(uint32_t Length, uint8_t *Buffer);
void LoaderUartReplyAckMsg(Loader_ACK_Type_t AckValue);

uint32_t LoderUartTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/
qapi_Status_t LoaderImportKey()
{
    qapi_Status_t status = QAPI_ERROR;
    int index;


    memset(&ImportKeyParams, 0, sizeof(ImportKeyParams));
    memset(&DeriveKeyParams, 0, sizeof(DeriveKeyParams));

    if (LoaderContext.ImageHeader->KeyType == LOADER_KEY_STATIC_E) {
        /* Special comments: if customer wants to use their own static key, please set
           ImportKeyParams.Key to the key used. for TO1.0, Key pointer set to NULL will
           not import key acutally. so ImportKeyParams.KeyHandle will be 0. when decryption
           is executed, KeyHandle 0 will be passed to qapi_CRPT_AES_Decryption,
           qapi_CRPT_AES_Decryption will try to get static key from OTP if KeyHandle is 0.
         */

#ifdef TO1_SUPPORT
       ImportKeyParams.Key = NULL;
#else
        /*for local test, can point to TestKey*/
        if (LoaderContext.ImageHeader->Key.KeyID >= 1 &&
            LoaderContext.ImageHeader->Key.KeyID <= 4 )
            ImportKeyParams.Key =
            (uint8_t*)(StaticKey[LoaderContext.ImageHeader->Key.KeyID -1].key);
        else
            return status;
#endif
        ImportKeyParams.KeyAlgo = QAPI_CRPT_KEY_ALGO_AES_GCM_128_E;
        ImportKeyParams.KeyLen = 16;
        /*status will not be QAPI_OK if Key is NULL but it doesn't matter for 1.0*/
        status = qapi_CRPT_Import_Key(&ImportKeyParams, NULL, NULL);
    } else {
        DeriveKeyParams.BaseKeyHandle = BATCH_SECRET_HANDLE; /*this will be replaced with a constant*/
        DeriveKeyParams.KeyAlgo = QAPI_CRPT_KEY_ALGO_AES_GCM_128_E;
        for (index = 0; index < 64; index ++){
            GlobalNonceLabel[index] = LoaderContext.ImageHeader->Key.NonceLabel[index];
        }
        GlobalNonceLabel[64] = 0;
        DeriveKeyParams.Label = (char*)(&(GlobalNonceLabel[32]));
        DeriveKeyParams.Nonce = (uint8_t*)(&(GlobalNonceLabel[0]));
        DeriveKeyParams.NonceLen = 32;
        status = qapi_CRPT_Derive_Key(&DeriveKeyParams, NULL, NULL);
    }
    return status;
}

qbool_t InitializeLoaderDemo()
{
    uint8_t RetVal;
    uint16_t RcvedDataMaxSize = 0;

    RetVal = LoderUartInit(LOADER_UART_INSTANCE);

    if(RetVal)
    {
        LoaderContext.ImageHeader = (Loader_ImgHeader_t*)ImageHeaderTable;
        RcvedDataMaxSize = LOADER_IMAGE_DEFAULT_BLOCK_SIZE +
                            LOADER_DATA_MSG_HEADER_SIZE  +
                            LOADER_CHECK_SUM_SIZE +
                            LOADER_IMAGE_DEFAULT_TAG_SIZE;
        LoaderContext.MsgRcvedDataMaxSize = RcvedDataMaxSize;
        LoaderContext.MsgRcvedData = ImageBlockTable;

        /* alloc buffer for image block tag, used for image block deencrypt */
        LoaderContext.MsgRcvedBlockTag = ImageTagTable;

    }
    return(RetVal);
}

void LoderUartRxCallback(uint32_t Status, uint32_t Length, void *CbCtxt)
{
    qapi_TSK_Signal_Task(LoaderContext.LoaderTask, LOADER_TSK_EVENT_UART_RX);
}

/**
   @brief Initialize the UART used by the demo.

   @return true if the UART was initailized successfully or false if there was
           an error.
*/

qbool_t LoderUartInit(uint32_t Instance)
{
   qapi_UART_Config_t  Uart_Config;
   uint8_t             Ret_Val;

   Uart_Config.Dma            = true;
   Uart_Config.BaudRate       = 115200;
   Uart_Config.ParityMode     = QAPI_UART_NO_PARITY_E;
   Uart_Config.NumStopBits    = QAPI_UART_1_0_STOP_BITS_E;
   Uart_Config.BitsPerChar    = QAPI_UART_8_BITS_PER_CHAR_E;
   Uart_Config.EnableLoopback = false;
   Uart_Config.EnableFlowCtrl = false;
   Uart_Config.RxBufSize = Uart_Config.TxBufSize = 1024;
   Uart_Config.RxStaleCnt     = 10;
   Uart_Config.TxInvert       = false;
   Uart_Config.TxCbFunc       = NULL;
   Uart_Config.RxCbFunc       = LoderUartRxCallback;
   LoaderContext.LoaderUART   = (qapi_UART_Instance_t)Instance;

   if(qapi_UART_Open(LoaderContext.LoaderUART, &Uart_Config) == QAPI_OK)
   {
      Ret_Val = true;
   }
   else
   {
      Ret_Val = false;
   }

   return(Ret_Val);
}

/**
   @brief Writes a buffer to the Loader Uart.

   @param Length[in]  Length of the data to be written.
   @param Buffer[in]  Buffer to be written to the console.
*/
void LoderUartWrite(uint32_t Length, const uint8_t *Buffer)
{
   uint32_t Remain = 0, Sent = 0, Offset = 0;

   if((Length != 0) && (Buffer != NULL))
   {
      Remain = Length;
      do
      {
         /* Transmit the data. */
         if(qapi_UART_Transmit(LoaderContext.LoaderUART, (char *)(Buffer + Offset), Remain, &Sent) == QAPI_OK)
         {
            Remain = Remain - Sent;
            Offset += Sent;
         }
      }while(Remain);
   }
}

uint16_t LoaderCrc16Ccitt(uint8_t *Buf, uint16_t Len)
{
    uint8_t i;
    uint16_t Crc = 0xffff;
    while(Len--)
    {
        Crc ^= (uint16_t)(*Buf++) << 8;
        for (i = 0; i < 8; ++i)
        {
            if ( Crc & 0x8000 )
                Crc = (Crc << 1) ^ 0x1021;
            else
                Crc <<= 1;
        }
    }
    return Crc;
}

qbool_t LoaderDataIsValidated(uint8_t *Buf, uint16_t Len, uint16_t Crc)
{
    uint16_t CrcCacl;
    uint8_t RetVal = true;

    CrcCacl = LoaderCrc16Ccitt(Buf, Len);

    if(CrcCacl != Crc)
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_CRC_E);
        RetVal = false;
    }

    return RetVal;
}

void LoaderUartSendHello()
{
    MsgCtrl.Magic = LOADER_MSG_MAGIC;
    MsgCtrl.MsgType = LOADER_MSG_HELLO_E;
    MsgCtrl.DataLen = LOADER_CHECK_SUM_SIZE;
    MsgCtrl.CheckSum = LoaderCrc16Ccitt((uint8_t*)(&MsgCtrl), LOADER_CTRL_MSG_HEADER_SIZE);

    LoderUartWrite(LOADER_CTRL_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE, (uint8_t*)(&MsgCtrl));

    LoaderContext.ExpectRcvMsg = LOADER_MSG_HELLO_E;            //waiting hello from Tool
    LoaderContext.ExpectRcvMsgSize = LOADER_CTRL_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
}

void LoaderUartReplyAckMsg(Loader_ACK_Type_t AckValue)
{
    MsgAck.Magic = LOADER_MSG_MAGIC;
    MsgAck.MsgType = LOADER_MSG_ACK_E;
    MsgAck.DataLen = 3;
    MsgAck.Data = AckValue;

    MsgAck.CheckSum = LoaderCrc16Ccitt((uint8_t*)(&MsgAck), (LOADER_ACK_MSG_SIZE - LOADER_CHECK_SUM_SIZE));

    LoderUartWrite(LOADER_ACK_MSG_SIZE, (uint8_t*)(&MsgAck));
}

void LoaderProcessHello(uint32_t MsgSize, uint8_t *Msg)
{
    if((MsgSize == 0) || (Msg == NULL))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    LoaderContext.LoaderReady = true;
    LoaderContext.ExpectRcvMsg = LOADER_MSG_MISCCTRL_E;
    LoaderContext.ExpectRcvMsgSize = sizeof(Loader_MsgMiscCtrl_t) + LOADER_CHECK_SUM_SIZE + LOADER_DATA_MSG_HEADER_SIZE;
    LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
}


void LoaderProcessMiscCtrl(uint32_t MsgSize, uint8_t *Msg)
{
    if((MsgSize == 0) || (Msg == NULL))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    Loader_MsgMiscCtrl_t *ApplyInfoPtr;

    ApplyInfoPtr = (Loader_MsgMiscCtrl_t*)(Msg + LOADER_DATA_MSG_HEADER_SIZE);

    LoaderContext.LoaderSecureImageAddr = ApplyInfoPtr->ImageApplyAddr;
    LoaderContext.LoaderImageLockDebug = ApplyInfoPtr->LockDebug;
    LoaderContext.LoaderImageNvmAddr = ApplyInfoPtr->ImageApplyAddr;
    LoaderContext.ExpectRcvMsg = LOADER_MSG_RCV_HEADER_E;
    LoaderContext.ExpectRcvMsgSize = sizeof(Loader_ImgHeader_t) + LOADER_CHECK_SUM_SIZE + LOADER_DATA_MSG_HEADER_SIZE;
    LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
}

void LoaderProcessImageHeader(uint32_t MsgSize, uint8_t *Msg)
{
    Loader_ImgHeader_t* HeaderPtr;
    uint16_t TempBlockNum, LastBlockSize;
    uint8_t TagSize=0;
    qapi_Status_t Status;

    if((MsgSize == 0) || (Msg == NULL))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    /* keep image header infomation */
    HeaderPtr = (Loader_ImgHeader_t*)(Msg + LOADER_DATA_MSG_HEADER_SIZE);
    LoaderContext.ImageSize = HeaderPtr->ImageSize;
    LoaderContext.ImageBlockSize = HeaderPtr->ImageBlockSize;

    TagSize = HeaderPtr->BlockTagSize;
    LoaderContext.ImageTagSize = TagSize;

    TempBlockNum = LoaderContext.ImageSize/(LoaderContext.ImageBlockSize + TagSize);
    if (LoaderContext.ImageSize%(LoaderContext.ImageBlockSize + TagSize)) {
        LastBlockSize = (LoaderContext.ImageSize%(LoaderContext.ImageBlockSize + TagSize) - TagSize);
        TempBlockNum += 1;
    }
    else
        LastBlockSize = LoaderContext.ImageBlockSize;

    LoaderContext.ImageTotalBlockNum = TempBlockNum;
    LoaderContext.ImageLastBlockSize = LastBlockSize;

    if(HeaderPtr->KeyType == LOADER_KEY_STATIC_E)
    {
        /* Static key, just have the KeyId in header */
        LoaderContext.ImageHeaderSize = LOADER_IMAGE_HEADER_SIZE_WITH_STATIC_KEY;
    }
    else
    {
        /* Derived (OEMBatchSecret), have Nonce and Label in header */
        LoaderContext.ImageHeaderSize = LOADER_IMAGE_HEADER_SIZE_WITH_DERIVED_KEY;
    }

    /* image header info is needed during the whole image processing */
    memcpy(LoaderContext.ImageHeader, (Msg + LOADER_DATA_MSG_HEADER_SIZE), LoaderContext.ImageHeaderSize);

    /* realloc data buffer if image block size is not same with default block size */
    if(LoaderContext.ImageBlockSize != LOADER_IMAGE_DEFAULT_BLOCK_SIZE)
    {
        LoaderContext.MsgRcvedData = NULL;
        LoaderContext.MsgRcvedDataMaxSize = LoaderContext.ImageBlockSize +
            LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE + LoaderContext.ImageTagSize;
        if(!(LoaderContext.MsgRcvedData = qapi_Malloc(LoaderContext.MsgRcvedDataMaxSize)))
        {
            LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_HEADER_NO_MEMORY_E);
            return;
        }

    }
    /* realloc data buffer if image block size is not same with default block size */
    if(LoaderContext.ImageTagSize != LOADER_IMAGE_DEFAULT_TAG_SIZE)
    {
        uint32_t MsgTagSize = 0;
        LoaderContext.MsgRcvedBlockTag = NULL;
        MsgTagSize = LoaderContext.ImageTagSize +
            LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
        if(!(LoaderContext.MsgRcvedBlockTag = qapi_Malloc(MsgTagSize)))
        {
            LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_HEADER_NO_MEMORY_E);
            return;
        }

    }
    LoaderContext.ExpectRcvMsg = LOADER_MSG_RCV_BLOCK_E;
    if (LoaderContext.ImageSize < (LoaderContext.ImageBlockSize + TagSize))
        LoaderContext.ExpectRcvMsgSize = (LoaderContext.ImageSize-TagSize + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE);
    else
        LoaderContext.ExpectRcvMsgSize = (LoaderContext.ImageBlockSize + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE);
    Status = LoaderImportKey();
    if (Status != QAPI_OK)
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_HEADER_DERIVE_KEY_E);
        return;
    }
    Status = qapi_NVM_Request_Write();
    if (Status != QAPI_OK)
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_HEADER_NVM_WRITE_E);
        return;
    }

    LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
}

void LoaderProcessImageBlock(uint32_t MsgSize, uint8_t *Msg)
{
    if((MsgSize == 0) || (Msg == NULL))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    LoaderContext.ImageRcvedBlockNum ++;

    /* waiting the incoming block tag to decrypt image block */
    LoaderContext.ExpectRcvMsg = LOADER_MSG_RCV_TAG_E;
    LoaderContext.ExpectRcvMsgSize = LoaderContext.ImageTagSize + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;;

    LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
}

void LoaderProcessImageTag(uint32_t MsgSize, uint8_t *Msg)
{
    uint8_t* BlockTag;

    qapi_Status_t status = QAPI_ERROR;
    uint8_t TempIV[12];
    qapi_CRPT_AES_Decryption_Params_t AESDecryptionParams;
    qapi_CRPT_Clear_Key_Params_t ClearkeyParams;

    if((MsgSize == 0) || (Msg == NULL))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    BlockTag = (uint8_t*)(Msg + LOADER_DATA_MSG_HEADER_SIZE);

    /*encrypt and decrypt image block */
    AESDecryptionParams.Algo = (qapi_CRPT_AES_Algo_t)LoaderContext.ImageHeader->KeyAlgo;
    AESDecryptionParams.EncryptedData    = (uint8_t *)(LoaderContext.MsgRcvedData + LOADER_DATA_MSG_HEADER_SIZE);
    if(LoaderContext.ImageRcvedBlockNum < LoaderContext.ImageTotalBlockNum && LoaderContext.ImageLastBlockSize!=0)
    {
        AESDecryptionParams.EncryptedDataLen = LoaderContext.ImageBlockSize;
        AESDecryptionParams.Tag = (uint8_t*)(LoaderContext.MsgRcvedData +
                LOADER_DATA_MSG_HEADER_SIZE + LoaderContext.ImageBlockSize);
    }
    else
    {
        AESDecryptionParams.EncryptedDataLen = LoaderContext.ImageLastBlockSize;
        AESDecryptionParams.Tag = (uint8_t*)(LoaderContext.MsgRcvedData +
                LOADER_DATA_MSG_HEADER_SIZE + LoaderContext.ImageLastBlockSize);
    }
    AESDecryptionParams.AADLen = 0;
    AESDecryptionParams.AAD = NULL;

    AESDecryptionParams.TagLen = LoaderContext.ImageHeader->BlockTagSize;
    memcpy(AESDecryptionParams.Tag, BlockTag, AESDecryptionParams.TagLen);
    /*Computing IV for decryption */
    memcpy(TempIV, LoaderContext.ImageHeader->IvBlob, 12);
    if (LoaderContext.ImageRcvedBlockNum != 1) {
        (*(uint32_t*)&TempIV[8]) = (LoaderContext.ImageRcvedBlockNum-1) * (LoaderContext.ImageBlockSize/16+1);
        (*(uint32_t*)&TempIV[8]) = A_SWAB32(*(uint32_t*)&TempIV[8]);
        AESDecryptionParams.IV = TempIV;
    } else {
        AESDecryptionParams.IV = LoaderContext.ImageHeader->IvBlob;
    }
    AESDecryptionParams.IVLen = LoaderContext.ImageHeader->IvLen;

    /*decyrpton QAPI supports FULL mode in ES1, so set PlainText to EncryptedData*/
    AESDecryptionParams.PlainText = AESDecryptionParams.EncryptedData;
    AESDecryptionParams.PlainTextLen= AESDecryptionParams.EncryptedDataLen;
    if (LoaderContext.ImageHeader->KeyType == LOADER_KEY_STATIC_E) {
        AESDecryptionParams.KeyHandle = ImportKeyParams.KeyHandle;
    } else {
        AESDecryptionParams.KeyHandle = DeriveKeyParams.DerivedKeyHandle;
    }

    status = qapi_CRPT_AES_Decryption(&AESDecryptionParams, NULL, NULL);

    if (status != QAPI_OK) {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_TAG_DECRYPTION_E);
        return;
    }
    /* write decoded image data to NVM*/
    if(false == LoaderWriteToNVM(AESDecryptionParams.PlainText, AESDecryptionParams.PlainTextLenUsed))
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_TAG_NVM_WRITE_E);
        return;
    }

    if(LoaderContext.ImageLastBlockSize!=0 && (LoaderContext.ImageRcvedBlockNum == (LoaderContext.ImageTotalBlockNum-1)))
    {
        LoaderContext.ExpectRcvMsg = LOADER_MSG_RCV_BLOCK_E;
        LoaderContext.ExpectRcvMsgSize = LoaderContext.ImageLastBlockSize + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
    }
    else if(LoaderContext.ImageRcvedBlockNum < LoaderContext.ImageTotalBlockNum)
    {
        LoaderContext.ExpectRcvMsg = LOADER_MSG_RCV_BLOCK_E;
        LoaderContext.ExpectRcvMsgSize = LoaderContext.ImageBlockSize + LOADER_DATA_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
    }
    else
    {
        /* received all image data, expect apply msg */
        LoaderContext.ExpectRcvMsg = LOADER_MSG_VERIFY_E;
        LoaderContext.ExpectRcvMsgSize = LOADER_CTRL_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
        /*Release the key after all of the image is decrypted*/
        if (LoaderContext.ImageHeader->KeyType == LOADER_KEY_STATIC_E) {
            ClearkeyParams.KeyHandle = ImportKeyParams.KeyHandle;
            /*for 1.0, this may not return QAPI_OK, it doesn't matter*/
            status = qapi_CRPT_Clear_Key(&ClearkeyParams, NULL, NULL);
        } else {
            ClearkeyParams.KeyHandle = DeriveKeyParams.DerivedKeyHandle;
            status = qapi_CRPT_Clear_Key(&ClearkeyParams, NULL, NULL);
        }
        if (status != QAPI_OK)
        {
            LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_TAG_CLEAR_KEY_E);
            return;
        }
		status = qapi_NVM_Release_Write();
        if (status != QAPI_OK)
        {
            LoaderUartReplyAckMsg(LOADER_ACK_ERROR_RCV_TAG_NVM_RELEASE_E);
            return;
        }
    }

    LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
}

void LoaderImageVerify()
{
    qapi_Status_t status = QAPI_ERROR;

    qapi_FWUP_Verify_Update_Package_t VerifyUpdateParam;

    VerifyUpdateParam.Location      = LoaderContext.LoaderSecureImageAddr;
    VerifyUpdateParam.Size          = Apply_Image_size;
    VerifyUpdateParam.VerifyAllImages = 1;
    VerifyUpdateParam.VerificationStatus = QAPI_FWUP_VERIFICATION_AUTH_FAILURE_E;
    status = qapi_FWUP_Verify_Update_Package(&VerifyUpdateParam, NULL, NULL);
    if (status == QAPI_OK)
    {
        if (VerifyUpdateParam.VerificationStatus == QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E)
        {
            LoaderContext.ExpectRcvMsg = LOADER_MSG_APPLY_E;
            LoaderContext.ExpectRcvMsgSize = LOADER_CTRL_MSG_HEADER_SIZE + LOADER_CHECK_SUM_SIZE;
            LoaderUartReplyAckMsg(LOADER_ACK_OK_E);
        }
        else
        {
            LoaderUartReplyAckMsg((Loader_ACK_Type_t)(VerifyUpdateParam.VerificationStatus - QAPI_FWUP_VERIFICATION_AUTH_SUCCESS_E + LOADER_ACK_ERROR_VERIFY_BASE_E));
        }
    }
    else
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_VERIFY_UPDATE_E);
    }
}

void LoaderImagegApply()
{
    qapi_FWUP_Apply_Update_Package_t UpdateParam;

    UpdateParam.Location       = LoaderContext.LoaderSecureImageAddr;
    UpdateParam.Size           = Apply_Image_size;
    UpdateParam.LockDebug      = LoaderContext.LoaderImageLockDebug;

    qapi_FWUP_Apply_Update_Package(&UpdateParam);
}

qbool_t LoaderWriteToNVM(uint8_t *Buffer, uint32_t BufferLen)
{
    qapi_Status_t status = QAPI_ERROR;
    status = qapi_NVM_Write((void*)LoaderContext.LoaderImageNvmAddr, Buffer, BufferLen);
    if(status != QAPI_OK)
    {
        return false;
    }
    LoaderContext.LoaderImageNvmAddr += BufferLen;
    Apply_Image_size += BufferLen;

    return true;
}

void LoaderProcessMsg(uint32_t MsgSize, uint8_t *Msg)
{
    Loader_MsgHeader_t* MsgHeader = NULL;
    uint32_t MsgTagSize = 0;
    uint16_t Crc = 0;

    if(MsgSize < LOADER_CTRL_MSG_HEADER_SIZE || Msg == NULL)
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MSG_NULL_E);
        return;
    }

    /* check message is valid with CRC16-CCITT */
    Crc = *(uint16_t*)(Msg + (MsgSize - LOADER_CHECK_SUM_SIZE));
    if(LoaderDataIsValidated(Msg, (MsgSize - LOADER_CHECK_SUM_SIZE), Crc) == false)
    {
        return;
    }

    MsgHeader = (Loader_MsgHeader_t*)Msg;

    if (MsgHeader->Magic != LOADER_MSG_MAGIC)
    {
        LoaderUartReplyAckMsg(LOADER_ACK_ERROR_MAGIC_E);
        return;
    }

    switch (MsgHeader->MsgType)
    {
        case LOADER_MSG_HELLO_E:
            LoaderProcessHello(MsgSize, Msg);
            break;
        case LOADER_MSG_MISCCTRL_E:
            LoaderProcessMiscCtrl(MsgSize, Msg);
            break;
        case LOADER_MSG_RCV_HEADER_E:
            LoaderProcessImageHeader(MsgSize, Msg);
            break;
        case LOADER_MSG_RCV_BLOCK_E:
            LoaderProcessImageBlock(MsgSize, Msg);
            break;
         case LOADER_MSG_RCV_TAG_E:
            LoaderProcessImageTag(MsgSize, Msg);
            break;
        case LOADER_MSG_VERIFY_E:
            LoaderImageVerify();
            break;
        case LOADER_MSG_APPLY_E:
            LoaderImagegApply();
            break;
        default:
            break;
    }

    LoaderContext.MsgRcvedLen = 0;
    if(MsgHeader->MsgType != LOADER_MSG_RCV_BLOCK_E)
    {
        memset(LoaderContext.MsgRcvedData, 0, LoaderContext.MsgRcvedDataMaxSize);
    }

    if(MsgHeader->MsgType == LOADER_MSG_RCV_TAG_E)
    {
        MsgTagSize = LoaderContext.ImageTagSize + LOADER_DATA_MSG_HEADER_SIZE
            + LOADER_CHECK_SUM_SIZE;
        memset(LoaderContext.MsgRcvedBlockTag, 0, MsgTagSize);
    }
}

void LoaderRecvingMsg(uint32_t Length, uint8_t *Buffer)
{
    uint8_t * Ptr;
    Loader_MsgHeader_t* MsgHeader = NULL;

    if((Length != 0) && (Buffer != NULL))
    {
        if(LoaderContext.ExpectRcvMsg != LOADER_MSG_RCV_TAG_E)
        {
            Ptr = LoaderContext.MsgRcvedData;
        }
        else
        {
            Ptr = LoaderContext.MsgRcvedBlockTag;
        }

        memcpy((Ptr + LoaderContext.MsgRcvedLen), Buffer, Length);
        LoaderContext.MsgRcvedLen += Length;
        if(LoaderContext.MsgRcvedLen == LoaderContext.ExpectRcvMsgSize)
        {
            LoaderProcessMsg(LoaderContext.MsgRcvedLen, Ptr);
        }
        else if(LoaderContext.MsgRcvedLen == LOADER_MSG_RCV_HEADER_SIZE_WITH_STATIC_KEY)
        {
            /* for MSG_HEADER, two message length*/
            MsgHeader = (Loader_MsgHeader_t*)Ptr;
            if (MsgHeader->Magic == LOADER_MSG_MAGIC && MsgHeader->MsgType == LOADER_MSG_RCV_HEADER_E)
            {
               LoaderProcessMsg(LoaderContext.MsgRcvedLen, Ptr);
            }
        }
    }
}

void LoaderTimerCallBack(void *UserParam)
{
    if(LoaderContext.LoaderReady || LoaderContext.HelloRetryTimes >= LOADER_SEND_HELLO_MAX_RETRY_TIMES)
    {
        qapi_TMR_Comp_Deinit(LoaderContext.TimerComparator);
        LoaderContext.TimerComparator = 0xFF; 				//NO_TIMER_COMPARATOR
    }
    else
    {
        qapi_TSK_Signal_Task(LoaderContext.LoaderTask, LOADER_TSK_EVENT_TIMER);
    }
}

uint32_t LoderStartHelloTimer()
{
    qapi_Status_t            Status = QAPI_OK;
    qapi_TMR_Comp_Instance_t Comp;

    Status = qapi_TMR_Comp_Init(&Comp, LoaderTimerCallBack, NULL, false);

    if (Status == QAPI_OK)
    {
        LoaderContext.TimerComparator = Comp;
        Status = qapi_TMR_Comp_Start(Comp, LOADER_SEND_HELLO_DELAY, true);
    }
    return Status;
}

static uint32_t LoderUartTask(qapi_TSK_Handle_t TaskHandle, uint32_t EventMask, void *UserParam)
{
    uint32_t Length, Remain = 0;

    if(EventMask & QAPI_TSK_EVENT_INIT)
    {
        /* Initialize the platform. */
        if(InitializeLoaderDemo())
        {
            LoaderUartSendHello();
            LoderStartHelloTimer();
        }

    }

    if(EventMask == LOADER_TSK_EVENT_UART_RX)
    {
        do
        {
            Length = LOADER_INPUT_BUFFER_SIZE;
            qapi_UART_Receive(LoaderContext.LoaderUART, (char*)LoaderContext.InputBuffer, &Length, &Remain);
            LoaderContext.InputByteCount = Length;

            LoaderRecvingMsg(LoaderContext.InputByteCount, LoaderContext.InputBuffer);
        }while(Remain);
    }

    if(EventMask == LOADER_TSK_EVENT_TIMER)
    {
        LoaderUartSendHello();
        LoaderContext.HelloRetryTimes++;
    }

    return(QAPI_TSK_INFINITE_WAIT);
}

/**
   Main entry point.
*/
int main(void)
{
    uint32_t WaitTime;
    qbool_t IsColdBoot;

    /* Initialize the qapi_task module. */
    qapi_TSK_Init(NULL, NULL);
    qapi_PWR_Initialize(&IsColdBoot);
    qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_PERIPHERAL_E, QAPI_PWR_STATE_ACTIVE_E);
    qapi_PWR_Set_Module_State(QAPI_PWR_MODULE_GPIO_E, QAPI_PWR_STATE_ACTIVE_E);
    qapi_PWR_Set_HFCLK_Source(1);
    qapi_TMR_Init();

    qapi_GPIO_Initialize(Alternative_GPIO_Config);
    qapi_NVM_Set_Permissions(0xFFFF, QAPI_NVM_PERMISSIONS_READ_WRITE_E);
    memset(&LoaderContext, 0, sizeof(LoaderContext));
    LoaderContext.LoaderTask = qapi_TSK_Create_Task(LoderUartTask, NULL);

    qapi_ROT_Session_Start();

    qapi_TSK_Signal_Task(LoaderContext.LoaderTask, QAPI_TSK_EVENT_INIT);
    LoaderContext.Running = true;
    WaitTime = 0;
    while(LoaderContext.Running)
    {
        if(WaitTime != 0)
        {
            //xxx
        }

        WaitTime = qapi_TSK_Process_Scheduler();
    }

    /* Delete the task and run the scheduler one last time to give it an
      opportunity to clean up. */
    qapi_TSK_Delete_Task(LoaderContext.LoaderTask);
    qapi_TSK_Process_Scheduler();

    return(0);
}

