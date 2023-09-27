/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_BTTYPESH_INC__
#error "qapi_ble_basetypes.h should never be used directly.  Include qapi_ble_bttypes.h, instead."
#endif

#ifndef __QAPI_BLE_BASETYPES_H__
#define __QAPI_BLE_BASETYPES_H__

#include <stdint.h>

   /* Miscellaneous defined type declarations.                          */

   /* Simply BOOLEAN type.                                              */
typedef char boolean_t;

   /* Miscellaneous Type definitions that should already be defined,    */
   /* but are necessary.                                                */
#ifndef NULL
   #define NULL ((void *)0)
#endif

#ifndef TRUE
   #define TRUE (1 == 1)
#endif

#ifndef FALSE
   #define FALSE (0 == 1)
#endif

   /* Unaligned Unsigned basic types.                                   */
typedef uint8_t qapi_BLE_NonAlignedByte_t;      /* Unaligned Generic 8 Bit    */
                                                /* Container.                 */

#define QAPI_BLE_NON_ALIGNED_BYTE_SIZE                   (sizeof(qapi_BLE_NonAlignedByte_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedWord_s     /* Unaligned Generic 16 Bit   */
{                                                                             /* Container.                 */
   uint8_t NonAlignedWord0;
   uint8_t NonAlignedWord1;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedWord_t;

#define QAPI_BLE_NON_ALIGNED_WORD_SIZE                   (sizeof(qapi_BLE_NonAlignedWord_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedDWord_s    /* Unaligned Generic 32 Bit   */
{                                                                             /* Container.                 */
   uint8_t NonAlignedDWord0;
   uint8_t NonAlignedDWord1;
   uint8_t NonAlignedDWord2;
   uint8_t NonAlignedDWord3;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedDWord_t;

#define QAPI_BLE_NON_ALIGNED_DWORD_SIZE                  (sizeof(qapi_BLE_NonAlignedDWord_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedQWord_s    /* Unaligned Generic 64 Bit   */
{                                                                             /* Container.                 */
   uint8_t NonAlignedQWord0;
   uint8_t NonAlignedQWord1;
   uint8_t NonAlignedQWord2;
   uint8_t NonAlignedQWord3;
   uint8_t NonAlignedQWord4;
   uint8_t NonAlignedQWord5;
   uint8_t NonAlignedQWord6;
   uint8_t NonAlignedQWord7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedQWord_t;

#define QAPI_BLE_NON_ALIGNED_QWORD_SIZE                  (sizeof(qapi_BLE_NonAlignedQWord_t))

   /* Unaligned Signed basic types.                                     */
typedef int8_t qapi_BLE_NonAlignedSByte_t;      /* Unaligned Signed 8 bit     */
                                                /* Container.                 */

#define QAPI_BLE_NON_ALIGNED_SBYTE_SIZE                  (sizeof(qapi_BLE_NonAlignedSByte_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedSWord_s    /* Unaligned Signed 16 Bit    */
{                                                                             /* Container.                 */
   int8_t NonAlignedSWord0;
   int8_t NonAlignedSWord1;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedSWord_t;

#define QAPI_BLE_NON_ALIGNED_SWORD_SIZE                  (sizeof(qapi_BLE_NonAlignedSWord_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedSDWord_s   /* Unaligned Signed 32 Bit    */
{                                                                             /* Container.                 */
   int8_t NonAlignedSDWord0;
   int8_t NonAlignedSDWord1;
   int8_t NonAlignedSDWord2;
   int8_t NonAlignedSDWord3;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedSDWord_t;

#define QAPI_BLE_NON_ALIGNED_SDWORD_SIZE                 (sizeof(qapi_BLE_NonAlignedSDWord_t))

typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_NonAlignedSQWord_s   /* Unaligned Signed 64 Bit    */
{                                                                             /* Container.                 */
   int8_t NonAlignedSQWord0;
   int8_t NonAlignedSQWord1;
   int8_t NonAlignedSQWord2;
   int8_t NonAlignedSQWord3;
   int8_t NonAlignedSQWord4;
   int8_t NonAlignedSQWord5;
   int8_t NonAlignedSQWord6;
   int8_t NonAlignedSQWord7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_NonAlignedSQWord_t;

#define QAPI_BLE_NON_ALIGNED_SQWORD_SIZE                 (sizeof(qapi_BLE_NonAlignedSQWord_t))

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* Uint8_t to an unaligned Memory Address.  This MACRO accepts as    */
   /* it's first parameter the Memory Address to store the specified    */
   /* Little Endian Uint8_t into.  The second parameter is the actual   */
   /* Uint8_t value to store into the specified Memory Location.        */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(_x, _y) \
{                                                                         \
  ((uint8_t *)(_x))[0] = ((uint8_t)(_y));                                 \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* Uint16_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified    */
   /* Little Endian Uint16_t into.  The second parameter is the actual  */
   /* Uint16_t value to store into the specified Memory Location.       */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(_x, _y) \
{                                                                         \
  ((uint8_t *)(_x))[0] = ((uint8_t)(((uint16_t)(_y)) & 0xFF));            \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint16_t)(_y)) >> 8) & 0xFF));     \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint32_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified    */
   /* Little Endian uint32_t into.  The second parameter is the actual  */
   /* uint32_t value to store into the specified Memory Location.       */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_DWORD_TO_LITTLE_ENDIAN_UNALIGNED_DWORD(_x, _y) \
{                                                                           \
  ((uint8_t *)(_x))[0] = ((uint8_t)(((uint32_t)(_y)) & 0xFF));              \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint32_t)(_y)) >> 8) & 0xFF));       \
  ((uint8_t *)(_x))[2] = ((uint8_t)((((uint32_t)(_y)) >> 16) & 0xFF));      \
  ((uint8_t *)(_x))[3] = ((uint8_t)((((uint32_t)(_y)) >> 24) & 0xFF));      \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint64_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified    */
   /* Little Endian uint64_t into.  The second parameter is the actual  */
   /* uint64_t value to store into the specified Memory Location.       */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_QWORD_TO_LITTLE_ENDIAN_UNALIGNED_QWORD(_x, _y) \
{                                                                           \
  ((uint8_t *)(_x))[0] = ((uint8_t)(((uint64_t)(_y)) & 0xFF));              \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint64_t)(_y)) >> 8) & 0xFF));       \
  ((uint8_t *)(_x))[2] = ((uint8_t)((((uint64_t)(_y)) >> 16) & 0xFF));      \
  ((uint8_t *)(_x))[3] = ((uint8_t)((((uint64_t)(_y)) >> 24) & 0xFF));      \
  ((uint8_t *)(_x))[4] = ((uint8_t)((((uint64_t)(_y)) >> 32) & 0xFF));      \
  ((uint8_t *)(_x))[5] = ((uint8_t)((((uint64_t)(_y)) >> 40) & 0xFF));      \
  ((uint8_t *)(_x))[6] = ((uint8_t)((((uint64_t)(_y)) >> 48) & 0xFF));      \
  ((uint8_t *)(_x))[7] = ((uint8_t)((((uint64_t)(_y)) >> 56) & 0xFF));      \
}

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Little Endian Byte_t from a specifed Memory Address.  This MACRO  */
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Little Endian Byte_t to read.  This function returns a Byte_t */
   /* (in the Endian-ness of the Native Host Processor).                */
#define QAPI_BLE_READ_UNALIGNED_BYTE_LITTLE_ENDIAN(_x)   (((uint8_t *)(_x))[0])

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Little Endian Uint16_t from a specifed Memory Address.  This MACRO*/
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Little Endian Uint16_t to read.  This function returns a      */
   /* Uint16_t (in the Endian-ness of the Native Host Processor).       */
#define QAPI_BLE_READ_UNALIGNED_WORD_LITTLE_ENDIAN(_x)   ((uint16_t)((((uint16_t)(((uint8_t *)(_x))[1])) << 8) | ((uint16_t)(((uint8_t *)(_x))[0]))))

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Little Endian uint32_t from a specifed Memory Address.  This MACRO*/
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Little Endian uint32_t to read.  This function returns a      */
   /* uint32_t (in the Endian-ness of the Native Host Processor).       */
#define QAPI_BLE_READ_UNALIGNED_DWORD_LITTLE_ENDIAN(_x)  ((uint32_t)((((uint32_t)(((uint8_t *)(_x))[3])) << 24) | (((uint32_t)(((uint8_t *)(_x))[2])) << 16) | (((uint32_t)(((uint8_t *)(_x))[1])) << 8) | ((uint32_t)(((uint8_t *)(_x))[0]))))

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Little Endian QUint16_t from a specifed Memory Address.  This     */
   /* MACRO accepts as it's first parameter the unaligned Memory Address*/
   /* of the Little Endian QUint16_t to read.  This function returns a  */
   /* QUint16_t (in the Endian-ness of the Native Host Processor).      */
#define QAPI_BLE_READ_UNALIGNED_QWORD_LITTLE_ENDIAN(_x)  ((uint64_t)((((uint64_t)(((uint8_t *)(_x))[7])) << 56) | (((uint64_t)(((uint8_t *)(_x))[6])) << 48) | (((uint64_t)(((uint8_t *)(_x))[5])) << 40) | (((uint64_t)(((uint8_t *)(_x))[4])) << 32) | (((uint64_t)(((uint8_t *)(_x))[3])) << 24) | (((uint64_t)(((uint8_t *)(_x))[2])) << 16) | (((uint64_t)(((uint8_t *)(_x))[1])) << 8) | ((uint64_t)(((uint8_t *)(_x))[0]))))

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint8_t to an unaligned Memory Address.  This MACRO accepts as    */
   /* it's first parameter the Memory Address to store the specified Big*/
   /* Endian uint8_t into.  The second parameter is the actual uint8_t  */
   /* value to store into the specified Memory Location.                */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_BYTE_TO_BIG_ENDIAN_UNALIGNED_BYTE(_x, _y) \
{                                                                      \
  ((uint8_t *)(_x))[0] = ((uint8_t)(_y));                              \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint16_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified Big*/
   /* Endian uint16_t into.  The second parameter is the actual Uint16_t*/
   /* value to store into the specified Memory Location.                */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_WORD_TO_BIG_ENDIAN_UNALIGNED_WORD(_x, _y)  \
{                                                                       \
  ((uint8_t *)(_x))[1] = ((uint8_t)(((uint16_t)(_y)) & 0xFF));          \
  ((uint8_t *)(_x))[0] = ((uint8_t)((((uint16_t)(_y)) >> 8) & 0xFF));   \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint32_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified Big*/
   /* Endian uint32_t into.  The second parameter is the actual uint32_t*/
   /* value to store into the specified Memory Location.                */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_DWORD_TO_BIG_ENDIAN_UNALIGNED_DWORD(_x, _y)  \
{                                                                         \
  ((uint8_t *)(_x))[3] = ((uint8_t)(((uint32_t)(_y)) & 0xFF));            \
  ((uint8_t *)(_x))[2] = ((uint8_t)((((uint32_t)(_y)) >> 8) & 0xFF));     \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint32_t)(_y)) >> 16) & 0xFF));    \
  ((uint8_t *)(_x))[0] = ((uint8_t)((((uint32_t)(_y)) >> 24) & 0xFF));    \
}

   /* The following is a utility MACRO that exists to Assign a specified*/
   /* uint64_t to an unaligned Memory Address.  This MACRO accepts as   */
   /* it's first parameter the Memory Address to store the specified Big*/
   /* Endian uint64_t into.  The second parameter is the actual uint64_t*/
   /* value to store into the specified Memory Location.                */
   /* * NOTE * The second parameter needs to be stored in the Endian    */
   /*          format of the Native Host's processor.                   */
#define QAPI_BLE_ASSIGN_HOST_QWORD_TO_BIG_ENDIAN_UNALIGNED_QWORD(_x, _y)  \
{                                                                         \
  ((uint8_t *)(_x))[7] = ((uint8_t)(((uint64_t)(_y)) & 0xFF));            \
  ((uint8_t *)(_x))[6] = ((uint8_t)((((uint64_t)(_y)) >> 8) & 0xFF));     \
  ((uint8_t *)(_x))[5] = ((uint8_t)((((uint64_t)(_y)) >> 16) & 0xFF));    \
  ((uint8_t *)(_x))[4] = ((uint8_t)((((uint64_t)(_y)) >> 24) & 0xFF));    \
  ((uint8_t *)(_x))[3] = ((uint8_t)((((uint64_t)(_y)) >> 32) & 0xFF));    \
  ((uint8_t *)(_x))[2] = ((uint8_t)((((uint64_t)(_y)) >> 40) & 0xFF));    \
  ((uint8_t *)(_x))[1] = ((uint8_t)((((uint64_t)(_y)) >> 48) & 0xFF));    \
  ((uint8_t *)(_x))[0] = ((uint8_t)((((uint64_t)(_y)) >> 56) & 0xFF));    \
}

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Big Endian Uint8_t from a specifed Memory Address.  This MACRO    */
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Big Endian Uint8_t to read.  This function returns a Uint8_t  */
   /* (in the Endian-ness of the Native Host Processor).                */
#define QAPI_BLE_READ_UNALIGNED_BYTE_BIG_ENDIAN(_x)      (((uint8_t *)(_x))[0])

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Big Endian Uint16_t from a specifed Memory Address.  This MACRO   */
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Big Endian Uint16_t to read.  This function returns a Uint16_t*/
   /* (in the Endian-ness of the Native Host Processor).                */
#define QAPI_BLE_READ_UNALIGNED_WORD_BIG_ENDIAN(_x)      ((uint16_t)((((uint16_t)(((uint8_t *)(_x))[0])) << 8) | ((uint16_t)(((uint8_t *)(_x))[1]))))

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Big Endian uint32_t from a specifed Memory Address.  This MACRO   */
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Big Endian uint32_t to read.  This function returns a uint32_t*/
   /* (in the Endian-ness of the Native Host Processor).                */
#define QAPI_BLE_READ_UNALIGNED_DWORD_BIG_ENDIAN(_x)     ((uint32_t)((((uint32_t)(((uint8_t *)(_x))[0])) << 24) | (((uint32_t)(((uint8_t *)(_x))[1])) << 16) | (((uint32_t)(((uint8_t *)(_x))[2])) << 8) | ((uint32_t)(((uint8_t *)(_x))[3]))))

   /* The following is a utility MACRO that exists to Read an unaligned */
   /* Big Endian uint64_t from a specifed Memory Address.  This MACRO   */
   /* accepts as it's first parameter the unaligned Memory Address of   */
   /* the Big Endian uint64_t to read.  This function returns a uint64_t*/
   /* (in the Endian-ness of the Native Host Processor).                */
#define QAPI_BLE_READ_UNALIGNED_QWORD_BIG_ENDIAN(_x)     ((uint64_t)((((uint64_t)(((uint8_t *)(_x))[0])) << 56) | (((uint64_t)(((uint8_t *)(_x))[1])) << 48) | (((uint64_t)(((uint8_t *)(_x))[2])) << 40) | (((uint64_t)(((uint8_t *)(_x))[3])) << 32) | (((uint32_t)(((uint8_t *)(_x))[4])) << 24) | (((uint32_t)(((uint8_t *)(_x))[5])) << 16) | (((uint32_t)(((uint8_t *)(_x))[6])) << 8) | ((uint32_t)(((uint8_t *)(_x))[7]))))

#endif
