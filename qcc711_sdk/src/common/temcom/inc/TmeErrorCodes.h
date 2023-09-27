/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef TME_ERROR_CODES_H
#define TME_ERROR_CODES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*=============================================================================
                         MACRO DECLARATIONS
=============================================================================*/
/**
 * Type definition for TME error status
*/
typedef uint32_t TME_ERROR;

#define TME_SUCCESS                  (0x0U) ///<! Everything is going well
#define TME_ERROR_GENERIC            (0x1U) ///<! Generic failure code if error is unknown
#define TME_ERROR_NOT_SUPPORTED      (0x2U) ///<! The API or operation requested  not supported/implemented
#define TME_ERROR_BAD_PARAMETER      (0x3U) ///<! At least one of the parameters/settings is not correct
#define TME_ERROR_BAD_MESSAGE        (0x4U) ///<! Bad and/or malformed message
#define TME_ERROR_TMECOM_FAILURE     (0x5U) ///<! Error from Tmecom/communication layer
#define TME_ERROR_TME_BUSY           (0x6U) ///<! When TME busy & can't take a new request from client.
#define TME_ERROR_BAD_ADDRESS        (0x7U) ///<! NULL or out of range memory address


/**
 * Fuse specific TME error status codes
*/
#define TME_ERROR_FUSE_BASE                         0x000D0000U
#define TME_ERROR_FUSE_OP                          (TME_ERROR_FUSE_BASE + 1)
#define TME_ERROR_FUSE_ACCESS_CONTROL              (TME_ERROR_FUSE_BASE + 2)
#define TME_ERROR_FUSE_ADDR_INVALID                (TME_ERROR_FUSE_BASE + 3)
#define TME_ERROR_FUSE_NOT_READABLE                (TME_ERROR_FUSE_BASE + 4)
#define TME_ERROR_FUSE_NOT_WRITEABLE               (TME_ERROR_FUSE_BASE + 5)
#define TME_ERROR_FUSE_ECC                         (TME_ERROR_FUSE_BASE + 6)

/*--------------------------------------------------------------------------*
 * ONLY ERROR CODE AND DESCRIPTION, DO NOT ADD ANY OTHER THINGS HERE
 *--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif /* TME_ERROR_CODES_H */
