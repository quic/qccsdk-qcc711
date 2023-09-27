/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include "qapi_task.h"
#include "qapi_i2c.h"
#include "qup_api.h"
#include "qapi_timer.h"


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define I2C_TRANSFER_CTXT_NUM_MAX       4

#define I2C_POLL_TIME_DEFAULT_US    40960000    /* FIXME */
#define I2C_POLL_INTERVAL_US        5

#define I2C_SERIAL_CLOCK_KHZ        19200

/** Bus speeds supported by the master implementation. */
#define I2C_STANDARD_MODE_FREQ_KHZ          100     /**< I2C stadard speed 100 KHz. */
#define I2C_FAST_MODE_FREQ_KHZ              400     /**< I2C fast mode speed 400 KHz. */
#define I2C_FAST_MODE_PLUS_FREQ_KHZ         1000    /**< I2C fast mode plus speed 1 MHz */

#define I2C_TX_PACKING_CFG0_VAL 0x7F8FE
#define I2C_TX_PACKING_CFG1_VAL 0xFFEFE
#define I2C_RX_PACKING_CFG0_VAL 0x7F8FE
#define I2C_RX_PACKING_CFG1_VAL 0xFFEFE

/**I2C Error code Mapping*/
#define I2C_SUCCESS(x)  (x == QAPI_OK)
#define I2C_ERROR(x)    (x != QAPI_OK)

#define I2CM_ErrorMap(Status)           (Status == QAPI_OK) ? QAPI_OK : __QAPI_ERROR(QAPI_MOD_I2C, Status)

/** HWIO register definitions */

#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_PRE_CMD_DELAY_BMSK                                0x1
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_PRE_CMD_DELAY_SHFT                                0x0
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_STRETCH_BMSK                                      0x4
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_STRETCH_SHFT                                      0x2
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_POST_CMD_DELAY_BMSK                               0x10
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_POST_CMD_DELAY_SHFT                               0x4
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_IGNORE_ADDRESS_NACK_BMSK                          0x40
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_IGNORE_ADDRESS_NACK_SHFT                          0x6
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_READ_FINISH_WITH_ACK_BMSK                         0x80
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_READ_FINISH_WITH_ACK_SHFT                         0x7
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_BYPASS_ADDRESS_PHASE_BMSK                         0x100
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_BYPASS_ADDRESS_PHASE_SHFT                         0x8
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_SLAVE_ADDRESS_BMSK                                0xFE00
#define HWIO_PERIPH_SE0_GENI_M_CMD0_I2C_SLAVE_ADDRESS_SHFT                                0x9


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum 
{
    I2C_TRANSFER_IDLE_E = 0,
    I2C_TRANSFER_IN_PROGRESS_E,
    I2C_TRANSFER_QUEUED_E,
    I2C_TRANSFER_OUTPUT_DONE_E,
    I2C_TRANSFER_INPUT_DONE_E,
    I2C_TRANSFER_DONE_E,
    I2C_TRANSFER_CANCELED_E,
    I2C_TRANSFER_TIMED_OUT_E
}I2C_transfer_State_t;

typedef enum
{
    I2C_CMD_INVALID_E = 0,
    I2C_CMD_WRITE_E,
    I2C_CMD_READ_E,
    I2C_CMD_WRITE_THEN_READ_E,
    I2C_CMD_ADDRESS_ONLY_E,
    I2C_CMD_BUS_CLEAR_E,
    I2C_CMD_STOP_ON_BUS_E
} I2C_Cmd_Opcode_t;

typedef struct I2C_TransferCtxt_s
{
    qapi_I2CM_Transfer_Config_t  *Config;
    qapi_I2CM_Descriptor_t       *Descriptor;
    uint32_t                     NumDescriptors;

    uint32_t                     TransferCount;
    I2C_transfer_State_t         TransferState;
    qapi_Status_t                TransferStatus;

    qapi_I2CM_Transfer_CB_t      CFn;
    void                         *CCtxt;
    struct I2C_TransferCtxt_s    *Next;
}I2C_TransferCtxt_t;

typedef struct I2C_HwCtxt_s
{
    uint8_t                      Instance;
    uint8_t                      Blocking;
    uint8_t                      XferMode;            
    uint8_t                      TransferCtxtNum;
    I2C_TransferCtxt_t           *TransferCtxtHead;
    QUP_XferCtxt_t               *XferCtxt;
    I2C_TransferCtxt_t           TransferArray[I2C_TRANSFER_CTXT_NUM_MAX];
    qapi_I2CM_Transfer_CB_t      CFn;
    void                         *CCtxt;
} I2C_HwCtxt_t;

typedef struct I2C_ClkCfg_s {
    uint32_t ClkFreqOut;
    uint8_t  ClkDiv;
    uint8_t  THigh;
    uint8_t  TLow;
    uint8_t  TCycle;
}I2C_ClkCfg_t;

/*-------------------------------------------------------------------------
 * Variables
 *-----------------------------------------------------------------------*/
static I2C_ClkCfg_t I2C_ClkMap[] = {
    {I2C_STANDARD_MODE_FREQ_KHZ,  8, 14, 18, 40},
    {I2C_FAST_MODE_FREQ_KHZ,      4,  3, 11, 20},
    {I2C_FAST_MODE_PLUS_FREQ_KHZ, 2, 3,  6, 15}
};

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

static void I2C_GeniCallback(uint32_t Status, void *CallbackCtxt);
static I2C_TransferCtxt_t *I2C_GetXferQueueHead(I2C_HwCtxt_t *HwCtxt);
static void I2C_FlushXferQueue(uint32_t Status, I2C_HwCtxt_t *HwCtxt);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

static void I2C_CancelTransfer(I2C_HwCtxt_t *HwCtxt)
{
    I2C_TransferCtxt_t *Transfer = I2C_GetXferQueueHead(HwCtxt);

    QUP_BusMCancelSync((QUP_Instance_t)HwCtxt->Instance);
    if (!HwCtxt->Blocking)
    {
        I2C_FlushXferQueue(QUP_ERROR_TRANSFER_FORCE_TERMINATED, HwCtxt);
    }
}

static qapi_Status_t I2C_TransferCheck(qapi_I2CM_Instance_t Instance, qapi_I2CM_Transfer_Config_t *Config, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc, qapi_I2CM_Transfer_CB_t Func, void *Ctxt)
{
    uint32_t i;
    //uint8_t NoiseRejectLevel;	
    uint8_t HasStart, HasRead, HasWrite;
    //uint8_t HasStop;
    qbool_t DirectionChange = true;
    I2C_HwCtxt_t *HwCtxt = QUP_BusPrivGet((QUP_Instance_t)Instance);

    if ((HwCtxt == NULL) || (Config == NULL) || (NumDesc == 0))
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    /* validate descriptors */
    for (i = 0; i < NumDesc; i++)
    {  
        if ((NumDesc == 1) && (Desc->Flags == QAPI_I2C_FLAG_START))
        {
            break;
        }
        
        if ((Desc == NULL) || (Desc->Buffer == NULL) || (Desc->Length == 0))
        {
            return QAPI_I2CM_ERROR_INVALID_PARAM;
        }

        if ((Desc->Length == 0) && (NumDesc == 1))
        {
            break;
        }

        HasStart   = Desc->Flags & QAPI_I2C_FLAG_START;
        //HasStop    = Desc->Flags & QAPI_I2C_FLAG_STOP;
        HasWrite   = Desc->Flags & QAPI_I2C_FLAG_WRITE;
        HasRead    = Desc->Flags & QAPI_I2C_FLAG_READ;

        if ((!(HasRead || HasWrite))  ||
            (DirectionChange && !HasStart))
        {
            return QAPI_I2CM_ERROR_INVALID_PARAM;
        }

        if (i < (NumDesc - 1))
        {
            Desc++;
            /* note that here you are checking the next transfer */
            if (((Desc->Flags & QAPI_I2C_FLAG_WRITE) == HasWrite) || 
                ((Desc->Flags & QAPI_I2C_FLAG_READ)  == HasRead))
            {
                DirectionChange = false;
            }
            else
            {
                DirectionChange = true;
            }
        }
    }

    if ((Config->BusFreqKHz != I2C_STANDARD_MODE_FREQ_KHZ)   &&
        (Config->BusFreqKHz != I2C_FAST_MODE_FREQ_KHZ)       &&
        (Config->BusFreqKHz != I2C_FAST_MODE_PLUS_FREQ_KHZ))
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    /* TODO validate noise config */
    
    return QAPI_OK;
}

static void I2C_AddToXferQueueTail(I2C_HwCtxt_t *HwCtxt, I2C_TransferCtxt_t *Transfer)
{
    I2C_TransferCtxt_t *CtxtHead;

    CtxtHead = HwCtxt->TransferCtxtHead;
    if (!CtxtHead)
    {
        HwCtxt->TransferCtxtHead = Transfer;
        HwCtxt->TransferCtxtNum = 1;
    }
    else
    {
        while (CtxtHead->Next)
        {
            CtxtHead = CtxtHead->Next;
        }
        CtxtHead->Next = Transfer;
        HwCtxt->TransferCtxtNum++;
    }
    Transfer->TransferState = I2C_TRANSFER_QUEUED_E;
}

static I2C_TransferCtxt_t *I2C_GetTransferIdleNode(I2C_HwCtxt_t *HwCtxt)
{
    int i;
    for (i=0; i<=QAPI_I2C_INSTANCE_SE3_E; i++)
    {
        if (HwCtxt->TransferArray[i].TransferState == I2C_TRANSFER_IDLE_E)
        {
            return &(HwCtxt->TransferArray[i]);
        }
    
    }
    return NULL;
}

static I2C_TransferCtxt_t *I2C_GetXferQueueHead(I2C_HwCtxt_t *HwCtxt)
{
    return HwCtxt->TransferCtxtHead;
}

static I2C_TransferCtxt_t *I2C_DelFromXferQueueHead(uint32_t Status, I2C_HwCtxt_t *HwCtxt)
{
    I2C_TransferCtxt_t *CtxtHead = HwCtxt->TransferCtxtHead;
    I2C_TransferCtxt_t *Transfer;

    HwCtxt->TransferCtxtHead = CtxtHead->Next;
    HwCtxt->TransferCtxtNum--;
    Transfer = CtxtHead;
    Transfer->TransferState = I2C_TRANSFER_IDLE_E;
    HwCtxt->CFn(I2CM_ErrorMap(Status), HwCtxt->CCtxt);
    
    return Transfer;
}

static void I2C_FlushXferQueue(uint32_t Status, I2C_HwCtxt_t *HwCtxt)
{
    I2C_TransferCtxt_t *Transfer;

    while (HwCtxt->TransferCtxtNum)
    {
        Transfer = I2C_DelFromXferQueueHead(Status, HwCtxt);
        Transfer->CFn(I2CM_ErrorMap(Status), Transfer->CCtxt);
    }
}

static const I2C_ClkCfg_t* I2C_GetClkCfg(uint32_t Freq)
{
    uint32_t i;
    const I2C_ClkCfg_t *ClkCfg;
    uint32_t ClkCfgNum = sizeof(I2C_ClkMap)/sizeof(I2C_ClkMap[0]);

    for (i=0, ClkCfg=I2C_ClkMap; i<ClkCfgNum; i++, ClkCfg++)
    {
        if (ClkCfg->ClkFreqOut == Freq)
        {
            return ClkCfg;
        }
    }
    
    return &I2C_ClkMap[0];
}

static void I2C_UpdateDescWithXferCtxt(qapi_I2CM_Descriptor_t *Descriptor, QUP_XferCtxt_t *XferCtxt)
{
    if (Descriptor)
    {   
        Descriptor->Transferred = (Descriptor->Flags&QAPI_I2C_FLAG_WRITE)?XferCtxt->TxCnt:XferCtxt->RxCnt;
    }
}

static void I2C_PrepareGeniXferCtxt(I2C_HwCtxt_t *HwCtxt, I2C_TransferCtxt_t *Transfer,
                                  QUP_XferCtxt_t *XferCtxt)
{
    qapi_I2CM_Transfer_Config_t *Config = Transfer->Config;
    qapi_I2CM_Descriptor_t     *Descriptor = Transfer->Descriptor + Transfer->TransferCount;
    qapi_I2CM_Descriptor_t *DescNext;
    QUP_I2cXferInfo_t          *I2cXferCtxt = &(XferCtxt->XferInfo.I2c);
    const I2C_ClkCfg_t *ClkCfg = NULL;
    uint32_t DescFlags = Descriptor->Flags;
    uint32_t CmdOpCode = I2C_CMD_BUS_CLEAR_E;
    uint32_t CmdParams = 0;
    
    memset(XferCtxt, 0, sizeof (*XferCtxt));

    if (Descriptor->Length == 0)
    {
        if ((DescFlags & QAPI_I2C_FLAG_START) == QAPI_I2C_FLAG_START)
        {
            CmdOpCode = I2C_CMD_ADDRESS_ONLY_E;
        }
        else if ((DescFlags & QAPI_I2C_FLAG_STOP) == QAPI_I2C_FLAG_STOP)
        {
            CmdOpCode = I2C_CMD_STOP_ON_BUS_E;
        }
        else if (DescFlags == 0)
        {
            CmdOpCode = I2C_CMD_BUS_CLEAR_E;
        }
   }
   else
   {
       if (DescFlags & QAPI_I2C_FLAG_WRITE)
       {
           CmdOpCode = I2C_CMD_WRITE_E; 
       }
       
       if (DescFlags & QAPI_I2C_FLAG_READ ) 
       { 
           CmdOpCode = I2C_CMD_READ_E; 
       }
   }
   XferCtxt->CmdOpcode = CmdOpCode;

   if (DescFlags & QAPI_I2C_FLAG_READ)
   {
       if ((Transfer->TransferCount < (Transfer->NumDescriptors - 1)) &&
            (!(DescFlags & QAPI_I2C_FLAG_STOP)))
       {
           DescNext = Descriptor + 1;
           if ((DescNext->Flags & QAPI_I2C_FLAG_READ) &&
               !(DescNext->Flags & QAPI_I2C_FLAG_START))
           {
               CmdParams = CmdParams | FLD_SET(SE0_GENI_M_CMD0, I2C_READ_FINISH_WITH_ACK, 1);
           }
       }
   }

   CmdParams = CmdParams | FLD_SET(SE0_GENI_M_CMD0, I2C_SLAVE_ADDRESS, Config->SlaveAddress);

   if ((Config->Delay) && (DescFlags & QAPI_I2C_FLAG_WRITE) && (DescFlags & QAPI_I2C_FLAG_STOP))
   {
       CmdParams = CmdParams | FLD_SET(SE0_GENI_M_CMD0, I2C_POST_CMD_DELAY, 1);
   }

   if (Descriptor->Length != 0)
   {
       if (!(DescFlags & QAPI_I2C_FLAG_STOP))
       {
           CmdParams = CmdParams | FLD_SET(SE0_GENI_M_CMD0, I2C_STRETCH, 1);
       }

       if (!(DescFlags & QAPI_I2C_FLAG_START))
       {
           CmdParams = CmdParams | FLD_SET(SE0_GENI_M_CMD0, I2C_BYPASS_ADDRESS_PHASE, 1);
       }
   }
   XferCtxt->CmdParam = CmdParams;

   if (Descriptor->Flags & QAPI_I2C_FLAG_READ)
   {
       XferCtxt->RxBuf = Descriptor->Buffer;
       XferCtxt->RxLen = Descriptor->Length;
   }
   else if (Descriptor->Flags & QAPI_I2C_FLAG_WRITE)
   {
       XferCtxt->TxBuf = Descriptor->Buffer;
       XferCtxt->TxLen = Descriptor->Length;
   }
   I2cXferCtxt->DescFlags = DescFlags;

   ClkCfg = I2C_GetClkCfg(Config->BusFreqKHz);
   I2cXferCtxt->ClkDiv = ClkCfg->ClkDiv;
   I2cXferCtxt->THigh = ClkCfg->THigh;
   I2cXferCtxt->TLow = ClkCfg->TLow;
   I2cXferCtxt->TCycle = ClkCfg->TCycle;
   I2cXferCtxt->SlaveAddress = Config->SlaveAddress;
   I2cXferCtxt->SlaveMaxClockStretchUs = Config->SlaveMaxClockStretchUs;
   I2cXferCtxt->NoiseReject = Config->NoiseReject;
   I2cXferCtxt->Delay = Config->Delay;
   
   I2cXferCtxt->TxPackingCfg0 = I2C_TX_PACKING_CFG0_VAL;
   I2cXferCtxt->TxPackingCfg1 = I2C_TX_PACKING_CFG1_VAL;
   I2cXferCtxt->RxPackingCfg0 = I2C_RX_PACKING_CFG0_VAL;
   I2cXferCtxt->RxPackingCfg1 = I2C_RX_PACKING_CFG1_VAL;

   XferCtxt->TxWaterMark = 1;
   XferCtxt->RxWaterMark = 0;
    
   Transfer->TransferState = I2C_TRANSFER_IN_PROGRESS_E;

   if (!HwCtxt->Blocking)
   {
       HwCtxt->CFn = Transfer->CFn;
       HwCtxt->CCtxt = Transfer->CCtxt;
       XferCtxt->CFn = I2C_GeniCallback;
       XferCtxt->CCtxt = HwCtxt;
   }
}

static void I2C_GeniCallback(uint32_t Status, void *CallbackCtxt)
{
    I2C_HwCtxt_t *HwCtxt = (I2C_HwCtxt_t *)CallbackCtxt;
    QUP_XferCtxt_t *XferCtxt = HwCtxt->XferCtxt;
    I2C_TransferCtxt_t *Transfer;
    qapi_I2CM_Descriptor_t *Descriptor;
    
    Transfer = I2C_GetXferQueueHead(HwCtxt);
    if (Transfer == NULL)
    {
        return;
    }
    Descriptor = Transfer->Descriptor + Transfer->TransferCount;    
    I2C_UpdateDescWithXferCtxt(Descriptor, XferCtxt);
    if (Status != QUP_SUCCESS)
    {
I2C_BUS_CANCEL:
        QUP_BusMCancelSync((QUP_Instance_t)HwCtxt->Instance);        
        I2C_FlushXferQueue(QUP_ERROR_TRANSFER_FORCE_TERMINATED, HwCtxt);
        return;
    }
    
    /*
     * check the all the descriptor done.if yes, I2C_DelFromXferQueueHead(HwCtxt)
     */
    Transfer->TransferCount++;
    if (Transfer->TransferCount < Transfer->NumDescriptors)
    {
        I2C_PrepareGeniXferCtxt(HwCtxt, Transfer, HwCtxt->XferCtxt);
        Status = QUP_BusTransfer((QUP_Instance_t)HwCtxt->Instance, HwCtxt->XferCtxt);
        if (Status)
        {
            goto I2C_BUS_CANCEL;
        }
        return;
    }
    else
    {
        I2C_DelFromXferQueueHead(Status, HwCtxt);
    }

    if (HwCtxt->TransferCtxtNum)
    {      
        Transfer = I2C_GetXferQueueHead(HwCtxt);
        I2C_PrepareGeniXferCtxt(HwCtxt, Transfer, HwCtxt->XferCtxt);
        Status = QUP_BusTransfer((QUP_Instance_t)HwCtxt->Instance, HwCtxt->XferCtxt);
        if (Status)
        {
            goto I2C_BUS_CANCEL;
        }
    }
}


/**
   @brief Initialize the respective I2C instance.

   The API allocates resources for use by the client handle and the I2C
   instance, and enables power to the I2C HW instance.

   @param[in] Instance  I2C instance that the client intends to initialize.

   @param[in] Config    I2C config.

   @return
   - QAPI_OK                             --  Module was initialized successfully.
   - QAPI_I2CM_ERROR_INVALID_PARAM       --  Invalid instance or handle parameter.
   - QAPI_I2CM_ERROR_MEM_ALLOC           --  Could not allocate space for driver structures.
   - QAPI_I2CM_ERROR_INTERRUPT_REGISTER  --  Could not register for an interrupt.
*/
qapi_Status_t qapi_I2CM_Open(qapi_I2CM_Instance_t Instance, qapi_I2CM_Config_t *Config)
{
    uint32_t Status;
    QUP_BusConfig_t I2CConfig;
    QUP_Instance_t QUP_Instance;

    if (!Config || Instance > QAPI_I2C_INSTANCE_SE3_E)
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    QUP_Instance = (QUP_Instance_t)Instance;
    I2CConfig.BusType = QUP_BUS_I2C_MASTER;
    I2CConfig.Blocking = !!Config->Blocking;
    I2CConfig.XferMode = (QUP_XferMode_t)!!Config->Dma;
    I2CConfig.ExtraData = NULL;

    Status = QUP_BusOpen(QUP_Instance, &I2CConfig, sizeof(I2C_HwCtxt_t));
    if (!Status)
    {
        I2C_HwCtxt_t *HwCtxt;

        HwCtxt = QUP_BusPrivGet(QUP_Instance);
        if (HwCtxt == NULL)
        {
            QUP_BusClose(QUP_Instance);
            return QAPI_I2CM_ERROR;
        }
        HwCtxt->Instance = Instance;
        HwCtxt->Blocking = Config->Blocking;
        HwCtxt->XferMode = I2CConfig.XferMode;
        HwCtxt->XferCtxt = QUP_XferCtxtGet(QUP_Instance);
    }

    return I2CM_ErrorMap(Status);

}

/**
   @brief De-initialize the I2C Master instance.

   The API releases any resources allocated by the qapi_I2CM_Open() API, and
   disable the power to the instance. In this API the transfers which have 
   not been completed will be cancelled and also the transfer call back function
   will be called.

   @param[in] Instance  The I2C Master instance to be closed.
   
   @return
   - QAPI_OK                        --  I2C Master driver was closed successfully.
   - QAPI_I2CM_ERROR_INVALID_PARAM  --  Invalid instance parameter.
*/
qapi_Status_t qapi_I2CM_Close(qapi_I2CM_Instance_t Instance)
{
    qapi_Status_t Status = QAPI_OK;
    I2C_HwCtxt_t *HwCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    if (Instance > QAPI_I2C_INSTANCE_SE3_E)
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (!HwCtxt)
    {
        return QAPI_OK;
    }

    if (HwCtxt->TransferCtxtNum > 0)
    {
        I2C_CancelTransfer(HwCtxt);
    }

    Status = QUP_BusClose((QUP_Instance_t)Instance);

    return I2CM_ErrorMap(Status);

 }

/**
   @brief Perform an I2C transfer.

   In case a transfer is already in progress by another client, this call 
   queues the transfer. If the transfer returns a failure, the transfer
   has not been queued and no callback will occur. If the transfer returns
   QAPI_OK, the transfer has been queued and a further status of the 
   transfer can only be obtained when the callback is called in non-blocking
   mode.
   
   @note
   In general, if the client wishes to queue mutliple transfers, it could
   use an array of descriptors of type qapi_I2CM_Descriptor_t instead of 
   calling the API multiple times. Although I2C Master driver support 
   queueing mutiple transfers in non-blocking mode.

   @param[in] Instance     The I2CM instance.
   @param[in] Config       Transfer configuration.
   @param[in] Desc         I2C transfer descriptor. This can be an array
                           of descriptors.
   @param[in] NumDesc      Number of descriptors in the descriptor array.
   @param[in]  CBFunction   The callback function that is called at the
                            completion of the transfer occurs in non-blocking
                            mode.The call must do minimal processing and must
                            not call any API defined in this file. It should 
                            be NULL in blocking mode.
   @param[in]  CBParameter  The context that the client passes here is
                            returned as is in the callback function. It should
                            be NULL in blocking mode.

   @return
   - QAPI_OK                                    --  I2C master transfer successfully.
   - QAPI_I2CM_ERROR_INVALID_PARAM              --  One ore more parameters are invalid.
   - QAPI_I2CM_ERROR_TRANSFER_BUSY              --  I2C core is busy.
   - QAPI_I2CM_ERROR_TRANSFER_TIMEOUT           --  Transfer timed out.
   - QAPI_I2CM_ERROR_INPUT_FIFO_UNDER_RUN       --  SW reads from an empty RX FIFO.
   - QAPI_I2CM_ERROR_INPUT_FIFO_OVER_RUN        --  HW writes to a full RX FIFO.
   - QAPI_I2CM_ERROR_OUTPUT_FIFO_UNDER_RUN      --  SW reads a new word from an empty TX FIFO.
   - QAPI_I2CM_ERROR_OUTPUT_FIFO_OVER_RUN       --  SW writes a new word into a full TX FIFO.
   - QAPI_I2CM_ERROR_COMMAND_OVER_RUN           --  A new command is initialized before the previous one done.
   - QAPI_I2CM_ERROR_TRANSFER_FORCE_TERMINATED  --  Command abort or cancel request by SW.
   - QAPI_I2CM_ERROR_COMMAND_ILLEGAL            --  Command with illegal opcode.
   - QAPI_I2CM_ERROR_COMMAND_FAIL               --  Command execution has been completed with failure.
   - QAPI_I2CM_ERROR_DMA_TX_BUS_ERROR           --  Bus error during DMA Tx transaction.
   - QAPI_I2CM_ERROR_DMA_RX_BUS_ERROR           --  Bus error during DMA Rx transaction.
*/
qapi_Status_t qapi_I2CM_Transfer(qapi_I2CM_Instance_t Instance, qapi_I2CM_Transfer_Config_t *Config, qapi_I2CM_Descriptor_t *Desc, uint32_t NumDesc, qapi_I2CM_Transfer_CB_t CBFunction, void *CBParameter)
{
    I2C_HwCtxt_t *HwCtxt;
    I2C_TransferCtxt_t *TransferCtxt;
    QUP_XferCtxt_t *XferCtxt;
    QUP_Status_t Status = QUP_SUCCESS;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (!HwCtxt)
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    if (I2C_TransferCheck(Instance, Config, Desc, NumDesc, CBFunction, CBParameter))
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    if ((!HwCtxt->Blocking) && (HwCtxt->TransferCtxtNum >= I2C_TRANSFER_CTXT_NUM_MAX))
    {
        return QAPI_I2CM_ERROR_TRANSFER_BUSY;
    }

    XferCtxt = HwCtxt->XferCtxt;

    TransferCtxt = I2C_GetTransferIdleNode(HwCtxt);
    if (!TransferCtxt)
    {
        return QAPI_I2CM_ERROR_TRANSFER_BUSY;
    }
    memset(TransferCtxt, 0, sizeof(I2C_TransferCtxt_t));
    TransferCtxt->Config = Config;
    TransferCtxt->Descriptor = Desc;
    TransferCtxt->NumDescriptors = NumDesc;
    TransferCtxt->CFn = CBFunction;
    TransferCtxt->CCtxt = CBParameter;

    /* Non-blocking mode */
    if (!HwCtxt->Blocking)
    {
        I2C_AddToXferQueueTail(HwCtxt, TransferCtxt);
        if (HwCtxt->TransferCtxtNum == 1)
        {
            I2C_PrepareGeniXferCtxt(HwCtxt, TransferCtxt, XferCtxt);
            Status = QUP_BusTransfer(QUP_Instance, XferCtxt);
            if (Status == QAPI_OK)
            {
                TransferCtxt->TransferState = I2C_TRANSFER_IN_PROGRESS_E;
            }
            else
            {
                memset(TransferCtxt, 0, sizeof(I2C_TransferCtxt_t));
            }
        } 
        return I2CM_ErrorMap(Status);
    }

    /* Blocking mode */  
    while(I2C_SUCCESS(Status) && (TransferCtxt->TransferCount < TransferCtxt->NumDescriptors))
    {     
        I2C_PrepareGeniXferCtxt(HwCtxt, TransferCtxt, XferCtxt);
        Status = QUP_BusTransfer(QUP_Instance, XferCtxt);        
        I2C_UpdateDescWithXferCtxt(Desc, XferCtxt);
        TransferCtxt->TransferCount++;        
        Desc++;
    }
    memset(TransferCtxt, 0, sizeof(I2C_TransferCtxt_t));
    return I2CM_ErrorMap(Status);
}

/**
   @brief Cancels a transfer.

   A transfer that has been initiated successfully by calling qapi_I2CM_Transfer()
   may be canceled. Based on the internal state of the transfer, this function
   will either immediately cancel the transfer or end the transfer at a later time.

   @param[in] Instance  The I2C instance.
   
   @return
   - QAPI_OK                                    --  Transfer is canceled successfully.
   - QAPI_I2CM_ERROR_INVALID_PARAM              --  One ore more parameters are invalid.
   - QAPI_I2CM_CANCEL_TRANSFER_INVALID          --  No transfer to be canceled.
   - QAPI_I2CM_ERROR_TRANSFER_FORCE_TERMINATED  --  Transfer aborted on the bus.
*/
qapi_Status_t qapi_I2CM_Cancel_Transfer(qapi_I2CM_Instance_t Instance)
{
    I2C_HwCtxt_t *HwCtxt;
    QUP_Instance_t QUP_Instance = (QUP_Instance_t)Instance;

    HwCtxt = QUP_BusPrivGet(QUP_Instance);
    if (!HwCtxt)
    {
        return QAPI_I2CM_ERROR_INVALID_PARAM;
    }

    if (HwCtxt->TransferCtxtNum == 0)
    {
        return QAPI_OK;
    }
    I2C_CancelTransfer(HwCtxt);

    return QAPI_OK;
 }

