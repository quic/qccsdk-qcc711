/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_BTTYPES_H__
#define __QAPI_BLE_BTTYPES_H__

   /* Miscellaneous defined type declarations.                          */

   /* Definitions for compilers that required structure to be explicitly*/
   /* declared as packed.                                               */

   /* Check for ARM Real View.                                          */
#if defined(__ARMCC_VERSION)

   #define __QAPI_BLE_PACKED_STRUCT_BEGIN__   __packed

   #define __QAPI_BLE_PACKED_STRUCT_END__

   /* Check for GCC.                                                    */
#elif defined(__GNUC__)

   #define __QAPI_BLE_PACKED_STRUCT_BEGIN__

   #define __QAPI_BLE_PACKED_STRUCT_END__     __attribute__ ((packed))

  /* Check for IAR.                                                     */
#elif defined(__ICCARM__)

   #define __QAPI_BLE_PACKED_STRUCT_BEGIN__    __packed

   #define __QAPI_BLE_PACKED_STRUCT_END__

   /* Must be handled some other way.                                   */
#else

   #define __QAPI_BLE_PACKED_STRUCT_BEGIN__

   #define __QAPI_BLE_PACKED_STRUCT_END__

#endif

#define __QAPI_BLE_BTTYPESH_INC__

   /* Force ALL Structure Declarations to be Byte Packed (noting the    */
   /* current Structure Packing).                                       */

#include "qapi_ble_basetypes.h"
#include "qapi_ble_btbtypes.h"

   /* Restore Structure Packing.                                        */

#undef __QAPI_BLE_BTTYPESH_INC__

#endif
