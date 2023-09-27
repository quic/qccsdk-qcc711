/*
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file TmeFusePlatformApis.h
   @brief Fuse (OTP & MTP) related APIs and definitions.

   This module provides OTP & MTP related platform specific interfaces.
*/

#ifndef __TME_FUSE_PLATFORM_APIS_H__
#define __TME_FUSE_PLATFORM_APIS_H__

/*-------------------------------------------------------------------------
 * Include Files
 *-----------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "qapi_status.h"
#include "TmeErrorCodes.h"

/** @addtogroup tme_fuse_interfaces
@{
*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/
#define OTP_MTP_OFFSET_MASK                  (0x000007FF)
#define OTP_MTP_OFFSET_TO_ROW_IDX(offset)    ((offset) >> 3)

#define OTP_ROW_START                        0x0
#define OTP_ROW_END                          0x3F
#define MTP_TME_ROW_START                    0x40
#define MTP_TME_ROW_END                      0x4F
#define MTP_BTSS_ROW_START                   0x50
#define MTP_BTSS_ROW_END                     0x5F
#define MTP_APSS_RO_ROW_START                0x60
#define MTP_APSS_RO_ROW_END                  0x6F
#define MTP_APSS_RW_ROW_START                0x70
#define MTP_APSS_RW_ROW_END                  0x7F
#define MTP_REG_RESTORE_ROW_START            0x80
#define MTP_REG_RESTORE_ROW_END              0xFF

#define OTP_MTP_ROW_HI_WORD_ADDR_MASK        0x7
#define OTP_MTP_ADDR_ALIGN_MASK              0x3
#define FUSE_ADDR_UNALIGN(addr)              ((addr) & OTP_MTP_ADDR_ALIGN_MASK)

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/
typedef enum TmeFuseOpType_s{
  TME_FUSE_OP_READ    = 0,
  TME_FUSE_OP_WRITE   = 1,
}TmeFuseOpType_t;

typedef enum TmeFuseOpAccessType_s{
  TME_FUSE_OP_DISALLOWED = 0,
  TME_FUSE_OP_VIA_IPC    = 1,
  TME_FUSE_OP_DIRECTLY   = 2,
}TmeFuseOpAccessType_t;

/* Structure to store fuse call back data */
typedef struct TmeFuseCallBackData_s
{
  void  *cbApi;                               /**< QAPI callback   */
  void  *cbUserData;                          /**< QAPI user data  */
  qapi_Fuse_Operation_Event_Data_t eventData; /**< QAPI event data */
}TmeFuseCallBackData_t;

/*-------------------------------------------------------------------------
 * Static Inline Function Definitions
 *-----------------------------------------------------------------------*/
static inline bool isApssRwMtp(uint32_t  fuseAddr)
{
  uint32_t rowIdx = OTP_MTP_OFFSET_TO_ROW_IDX(fuseAddr & OTP_MTP_OFFSET_MASK);
  if ((rowIdx >= MTP_APSS_RW_ROW_START) && (rowIdx <= MTP_APSS_RW_ROW_END)) {
    return true;
  }
  return false;
}

static inline bool isApssRoMtp(uint32_t  fuseAddr)
{
  uint32_t rowIdx = OTP_MTP_OFFSET_TO_ROW_IDX(fuseAddr & OTP_MTP_OFFSET_MASK);
  if ((rowIdx >= MTP_APSS_RO_ROW_START) && (rowIdx <= MTP_APSS_RO_ROW_END)) {
    return true;
  }
  return false;
}

static inline bool isBtssMtp(uint32_t  fuseAddr)
{
  uint32_t rowIdx = OTP_MTP_OFFSET_TO_ROW_IDX(fuseAddr & OTP_MTP_OFFSET_MASK);
  if ((rowIdx >= MTP_BTSS_ROW_START) && (rowIdx <= MTP_BTSS_ROW_END)) {
    return true;
  }
  return false;
}

static inline bool isTmeMtp(uint32_t  fuseAddr)
{
  uint32_t rowIdx = OTP_MTP_OFFSET_TO_ROW_IDX(fuseAddr & OTP_MTP_OFFSET_MASK);
  if ((rowIdx >= MTP_TME_ROW_START) && (rowIdx <= MTP_TME_ROW_END)) {
    return true;
  }
  return false;
}

static inline bool isOtp(uint32_t  fuseAddr)
{
  uint32_t rowIdx = OTP_MTP_OFFSET_TO_ROW_IDX(fuseAddr & OTP_MTP_OFFSET_MASK);
  if ((rowIdx >= OTP_ROW_START) && (rowIdx <= OTP_ROW_END)) {
    return true;
  }
  return false;
}

/*-------------------------------------------------------------------------
 * Function Declarations
 *-----------------------------------------------------------------------*/

/**
   @brief Get access type for an operation on OTP/MTP.

   @param [in]     fuseAddr     OTP/MTP address.
   @param [in ]    opType       Operation type from TmeFuseOpType_t.

   @return
           - Access type allowed for the fuse operation.
*/
TmeFuseOpAccessType_t TmeFuseGetAccessType(uint32_t fuseAddr,
                                           TmeFuseOpType_t opType);

/**
   @brief Wrapper api for NVM Operation - request write.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmRequestWrite(void);

/**
   @brief Wrapper api for NVM Operation - release write.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmReleaseWrite(void);

/**
   @brief Wrapper api for NVM Operation - write.

   @param[in] addr   NVM address to write to.
   @param[in] buf    Data to write to NVM.
   @param[in] len    Length of the data to write to NVM.

   @return - TME_SUCCESS for success, TME_ERROR_GENERIC for failure.
*/
TME_ERROR TmeFuseNvmWrite(const void *addr, const void *buf, uint32_t len);

/**
   @brief Fuse IPC call back handler. Based on OS environment call user call back
          to notify about completion of fuse operation.

   @param[in] cbData   Fuse Call back Data.
   @param[in] status   Return value of fuse operation.

   @return - None.
*/
void TmeFuseOsHandleCallBack(TmeFuseCallBackData_t *cbData, qapi_Status_t status);

/** @} */

#endif //__TME_FUSE_PLATFORM_APIS_H__

