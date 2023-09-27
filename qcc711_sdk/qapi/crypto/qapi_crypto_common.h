/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/**
*  @file qapi_crypto_common.h
*  @brief Crypto common types and definitions.

    This file defines the common data types used across crypto module and various sub modules.
*/

#ifndef __QAPI_CRYPTO_COMMON_H__
#define __QAPI_CRYPTO_COMMON_H__


/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Type Declarations
 *-----------------------------------------------------------------------*/

/** @ingroup qapi_platform_crypto
    Type representing a key handle for the particular key. Key handle acquired via
    qapi_CRPT_Import_Key() can be used with any applicable crypto QAPI. */
typedef uint32_t qapi_CRPT_Key_Handle_t;


#endif