/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 *
 * All Rights Reserved
 * Qualcomm Technologies Inc Confidential and Proprietary.
 * Notifications and licenses are retained for attribution purposes only
 */
// clang-format off
/*! \file tme_types.h
 * @brief The definitions of constants, enums and structures to be used 
 * across TME-FW.
 */
#ifndef TME_TYPES_H
#define TME_TYPES_H

#include "packed.h"

#ifdef __linux__
#include <stdint.h>
#endif /* __linux__ */

/** Primitive Type - Byte */
typedef int8_t INT8;
/** Primitive Type - Short */
typedef int16_t INT16;
/** Primitive Type - Integer */
typedef int32_t INT32;
/** Primitive Type - Unsigned Byte */
typedef uint8_t UINT8;
/** Primitive Type - Unsigned Short */
typedef uint16_t UINT16;
/** Primitive Type - Unsigned Integer */
typedef uint32_t UINT32;

/*!
 * @enum TMEStatus
 * @brief Indicates the status returned by the TME-FW subsystems.
 */

typedef enum tme_status_e
{
    TME_STATUS_SUCCESS,             /*!< Success */
    TME_STATUS_FAILURE,             /*!< Generic Failure */
    TME_STATUS_INVALID_INPUT,       /*!< Invalid Input */
    TME_STATUS_MALFORMED_TOKEN,     /*!< Token is malformed */
    TME_STATUS_NOT_IMPLEMENTED,     /*!< Not Supported/Implemented */
    TME_STATUS_INVALID_MEMORY,      /*!< Invalid Memory Location */
    TME_STATUS_SMALL_OUTPUT_BUFFER, /*!< Length of output buffer is smaller 
                                         than expected */
    TME_STATUS_NOT_READY,           /*!< FW is not ready or set. */
    TME_STATUS_ME_DATA_UNAVAILABLE, /*!< Expected ME Data is not available */
    TME_STATUS_UNKNOWN = 0xFFFFFFFF /*!< Unknown */
} TMEStatus;

/*!
 * @struct TMECBuffer
 * @brief Represents a generic byte array based buffer of given length.
 */

typedef struct PACKED_PREFIX tme_cbuffer_s
{
    UINT8 *pData;      /*!< Pointer to the buffer */
    UINT32 length;     /*!< Length of the buffer */
} TMECBuffer;

/*!
 * @struct TMEResponseCBuffer
 * @brief Represents a generic byte array based buffer of given length.
 */

typedef struct PACKED_PREFIX tme_response_cbuffer_s
{
    UINT8 *pData;      /*!< Pointer to the buffer */
    UINT32 length;     /*!< Length of the buffer */
    UINT32 lengthUsed; /*!< Actual length of the buffer used */
} TMEResponseCBuffer;
// clang-format on
#endif /* TME_TYPES_H */
