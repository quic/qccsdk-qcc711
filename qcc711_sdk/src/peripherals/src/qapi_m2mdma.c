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
#include "qapi_m2mdma.h"
#include "qup_api.h"

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
 * Static & global Variable Declarations
 *-----------------------------------------------------------------------*/
qapi_M2MDMA_CB_t M2MDMA_Callback;

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/
static qapi_Status_t M2MDMA_Convert_Status(QUP_Status_t status);
static void M2MDMA_Geni_Callback(uint32_t Status, void *CallbackCtxt);

/*-------------------------------------------------------------------------
 * Function Definitions
 *-----------------------------------------------------------------------*/

/**
   @brief Initializes the M2M DMA Chan.

   This function initializes internal data structures along with associated
   static data. In any operating mode, this function should be called before
   calling any other DMA Chan API.

   @param[in] Chan        DMA Chan specified by #qapi_M2MDMA_Chan_t.
   @param[in] Callback    Callback function if none-blocking mode. For
                          blocking mode, this should be set to NULL.

   @return
   - QAPI_OK                  --  Module was initialized successfully.
   - QAPI_ERR_INVALID_PARAM   --  Invalid Chan or handle parameter.
   - QAPI_ERR_NO_MEMORY       --  Could not allocate space for driver structures.
*/
qapi_Status_t qapi_M2MDMA_Chan_Open(qapi_M2MDMA_Chan_t Chan, qapi_M2MDMA_CB_t Callback)
{
    QUP_Status_t Status = QUP_SUCCESS;
    QUP_BusConfig_t M2mDmaConfig;
    QUP_Instance_t QUP_Chan;
    QUP_XferCtxt_t *XferCtxt;

    if (Chan < QAPI_M2MDMA_CHAN_SE2_E || Chan > QAPI_M2MDMA_CHAN_SE3_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    M2mDmaConfig.BusType = QUP_BUS_M2MDMA;
    if (!Callback)
         M2mDmaConfig.Blocking = 1;
    else
         M2mDmaConfig.Blocking = 0;
    M2mDmaConfig.XferMode = QUP_XFER_DMA;
    M2mDmaConfig.ExtraData = NULL;
    QUP_Chan = (QUP_Instance_t)Chan;

    Status = QUP_BusOpen(QUP_Chan, &M2mDmaConfig, 0);

    if (Status == QUP_SUCCESS) {
        XferCtxt = QUP_XferCtxtGet(QUP_Chan);
        if (XferCtxt)
        {
            memset(XferCtxt, 0, sizeof (*XferCtxt));
            XferCtxt->CFn = M2MDMA_Geni_Callback;
            M2MDMA_Callback = Callback;
        }
        else
        {
            Status = QUP_ERROR;
        }
    }

    return M2MDMA_Convert_Status(Status);
}

/**
   @brief Performs a data copy over the DMA Chan.

   This function performs transfer over the DMA Chan.
   If the callback is set, it will be invoked when transfer
   completion.

   @param[in]  Chan        The Chan enabled by qapi_M2MDMA_ChanOpen().
   @param[out] Dst         Pointer to the M2M DMA destiona address
   @param[in]  Src         Pointer to the M2M DMA source address
   @param[in]  Length      the length of DMA buffer copy. the length
                           should be multiple of 4 bytes
   @param[in]  UserParam   User specific data passed by application.

   @return
   QAPI_OK                      --  M2M DMA copy successfully.
   - QAPI_ERROR                 --  DMA copy failed.
   - QAPI_ERR_INVALID_PARAM     --  One ore more parameters are invalid.
   - QAPI_ERR_TRANSFER_BUSY     --  DMA Chan is busy.
   - QAPI_ERR_TRANSFER_TIMEOUT  --  Copy timed out.
*/
qapi_Status_t qapi_M2MDMA_Copy(qapi_M2MDMA_Chan_t Chan, void *Dst, const void *Src, size_t Length, void* UserParam)

{
    QUP_XferCtxt_t *XferCtxt;
    QUP_Status_t Status = QUP_SUCCESS;
    QUP_Instance_t QUP_Chan = (QUP_Instance_t)Chan;
    QUP_BusCtxt_t *QUP_Bus = QUP_BusCxtGet(QUP_Chan);

    /* Invalid buffers */
    if (!Src || !Dst|| !Length || (Length % 4))
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    if (QUP_Bus->BusType != QUP_BUS_M2MDMA)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    XferCtxt = QUP_XferCtxtGet(QUP_Chan);

    if (!XferCtxt)
    {
        return QAPI_ERROR;
    }

    if (XferCtxt->Busy)
    {
        return QAPI_ERR_BUSY;
    }

    XferCtxt->TxBuf = (uint8_t*)Src;
    XferCtxt->RxBuf = (uint8_t*)Dst;
    XferCtxt->TxLen = Length;
    XferCtxt->RxLen = Length;
    XferCtxt->CCtxt = UserParam;

    Status = QUP_BusTransfer(QUP_Chan, XferCtxt);

    return M2MDMA_Convert_Status(Status);
}


/**
   @brief Closes the M2M DMA Chan.

   This function frees all internal data structures and closes the M2M DMA Chan.
   The handle returned by qapi_M2MDMA_ChanOpen() is rendered invalid. Any pending
   operation will be canceled with close function call.

   @param[in] Chan  The Chan opened by qapqapi_M2MDMA_ChanOpen().

   @return
   - QAPI_OK                    --  M2M DAM chan driver was closed successfully.
   - QAPI_ERR_INVALID_PARAM     --  Invalid Chan parameter.
*/
qapi_Status_t qapi_M2MDMA_Chan_Close(qapi_M2MDMA_Chan_t Chan)
{
    QUP_Status_t Status = QUP_SUCCESS;
    //QUP_Instance_t QUP_Chan;

    if (Chan < QAPI_M2MDMA_CHAN_SE2_E || Chan > QAPI_M2MDMA_CHAN_SE3_E)
    {
        return QAPI_ERR_INVALID_PARAM;
    }

    Status = QUP_BusClose((QUP_Instance_t)Chan);

    return M2MDMA_Convert_Status(Status);
}

static qapi_Status_t M2MDMA_Convert_Status(QUP_Status_t Status)
{
   switch (Status)
   {
      case QUP_SUCCESS:
         return QAPI_OK;
      case QUP_ERROR_INVALID_PARAM:
         return QAPI_ERR_INVALID_PARAM;
      case QUP_ERROR_MEM_ALLOC:
         return QAPI_ERR_NO_MEMORY;
      case QUP_ERROR_TRANSFER_BUSY:
         return QAPI_ERR_BUSY;
      case QUP_ERROR_TRANSFER_TIMEOUT:
         return QAPI_ERR_TIMEOUT;
      default:
         return QAPI_ERROR;
   }
}

static void M2MDMA_Geni_Callback(uint32_t Status, void *CallbackCtxt)
{
    uint32_t Result = M2MDMA_Convert_Status((QUP_Status_t)Status);

    M2MDMA_Callback(Result, CallbackCtxt);
}

