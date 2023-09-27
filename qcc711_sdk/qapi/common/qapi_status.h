/*
 * Copyright (c) 2011-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
   @file qapi_status.h

   @brief QAPI status definitions

   @details This file defines the QAPI status type and common status values. It
            also defines the module IDs that can be used by modules to add
            additional status codes.
*/

#ifndef __QAPI_STATUS_H__ // [
#define __QAPI_STATUS_H__

#include "qapi_types.h"

/** @addtogroup qapi_status
@{ */

/** Status of an operation. */
typedef int32_t qapi_Status_t;

/**
   @name Error Code Formats

   The following definitions are used to format error codes based on their
   module. Error codes that use these macros will be a negative value of
   the format -((10000 * \<Module ID>) + \<Status Code>).
   @{
*/
#define __QAPI_ERR_MOD_OFFSET                (10000)                                                                  /**< Module offset - error code format. */
#define __QAPI_ERR_ENCAP_MOD_ID(__mod_id__)  ((__mod_id__) * __QAPI_ERR_MOD_OFFSET)                                   /**< Module offset and module id - error code format. */
#define __QAPI_ERROR(__mod_id__, __err__)    ((qapi_Status_t)(0 - (__QAPI_ERR_ENCAP_MOD_ID(__mod_id__) + (__err__)))) /**< Module offset, module id, and status code - error code format. */
/** @} */ /* end namegroup */

/**
   @name Module IDs

   The following definitions represent the IDs for the various modules of
   the QAPI.

   If you are an OEM that wants to add your own module IDs, Qualcomm@reg
   recommend starting IDs from 100. This will avoid possible conflicts
   with future module updates and additions to the QAPI.
   @{
*/
#define QAPI_MOD_BASE                    (0)  /**< Base module - module id. */
#define QAPI_MOD_BT                      (1)  /**< BT module - module id. */
#define QAPI_MOD_UART                    (2)  /**< UART module - module id. */
#define QAPI_MOD_I2C                     (3)  /**< I2C module - module id. */
#define QAPI_MOD_SPI                     (4)  /**< SPI module - module id. */
#define QAPI_MOD_GPIO                    (5)  /**< GPIO module - module id. */
#define QAPI_MOD_FTC                     (6)  /**< FTC module - module id. */
#define QAPI_MOD_M2MDMA                  (7)  /**< M2MDMA module - module id. */
#define QAPI_MOD_TMR                     (8)  /**< TMR module - module id. */
#define QAPI_MOD_CRYPTO                  (9)  /**< CRYPTO module - module id. */
#define QAPI_MOD_LIC                     (10)  /**< LIC module - module id. */
#define QAPI_MOD_FWUP                    (11)  /**< FWUP module - module id. */
#define QAPI_MOD_NVM                     (12)  /**< NVM module - module id. */
#define QAPI_MOD_APPI2C                  (13)  /**< APPI2C module - module id. */

/** @} */ /* end namegroup */

/**
   @name Common Status Codes

   The following definitions represent status codes common to all 
   QAPI modules.
   @{
*/
#define QAPI_OK                              ((qapi_Status_t)(0))              /**< Success.                   */
#define QAPI_ERROR                           (__QAPI_ERROR(QAPI_MOD_BASE,  1)) /**< General error.             */
#define QAPI_ERR_INVALID_PARAM               (__QAPI_ERROR(QAPI_MOD_BASE,  2)) /**< Invalid parameter.         */
#define QAPI_ERR_NO_MEMORY                   (__QAPI_ERROR(QAPI_MOD_BASE,  3)) /**< Memory allocation error.   */
#define QAPI_ERR_NO_RESOURCE                 (__QAPI_ERROR(QAPI_MOD_BASE,  4)) /**< Resource allocation error. */
#define QAPI_ERR_BUSY                        (__QAPI_ERROR(QAPI_MOD_BASE,  6)) /**< Operation is busy.         */
#define QAPI_ERR_NO_ENTRY                    (__QAPI_ERROR(QAPI_MOD_BASE,  7)) /**< Entry was not found.       */
#define QAPI_ERR_NOT_SUPPORTED               (__QAPI_ERROR(QAPI_MOD_BASE,  8)) /**< Feature is not supported.  */
#define QAPI_ERR_TIMEOUT                     (__QAPI_ERROR(QAPI_MOD_BASE,  9)) /**< Operation timed out.       */
#define QAPI_ERR_BOUNDS                      (__QAPI_ERROR(QAPI_MOD_BASE, 10)) /**< Out of bounds.             */
#define QAPI_ERR_BAD_PAYLOAD                 (__QAPI_ERROR(QAPI_MOD_BASE, 11)) /**< Bad payload.               */
#define QAPI_ERR_EXISTS                      (__QAPI_ERROR(QAPI_MOD_BASE, 12)) /**< Entry already exists.      */
/** @} */ /* end namegroup */

/** @} */
#endif // ] #ifndef __QAPI_STATUS_H__

