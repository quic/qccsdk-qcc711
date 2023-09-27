/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QAPI_BLE_BTAPITYP_H__
#define __QAPI_BLE_BTAPITYP_H__

   /* The following definition defines the API Calling Convention for   */
   /* ALL the exported Bluetoth API Functions.                          */
#ifndef QAPI_BLE_BTPSAPI

   #define QAPI_BLE_BTPSAPI

#endif

   /* The following conditional declaration controls the specific       */
   /* linkage that may/may not be required to specify Bluetooth API     */
   /* functions.                                                        */
#ifndef QAPI_BLE_DECLARATION

   #define QAPI_BLE_DECLARATION

#endif

   /* This define (BTPSCONST) is used to conditionally support the use  */
   /* of the const modifier.                                            */
   /* * NOTE * This is only provided for older platforms that do not    */
   /*          support the const modifier.                              */
#ifndef QAPI_BLE_CONST

   #define QAPI_BLE_CONST const

#endif

   /* In case the compiler does not support exception handling, define  */
   /* the exception handling to do nothing.                             */
#ifndef __QAPI_BLE_TRY

   #define __QAPI_BLE_TRY

#endif

#ifndef __QAPI_BLE_EXCEPT

   #define __QAPI_BLE_EXCEPT(_x)    if(0)

#endif

   /* The following MACRO is a utility MACRO that exists to calculate   */
   /* the offset position of a particular structure member from the     */
   /* start of the structure. This MACRO accepts as the first parameter,*/
   /* the physical name of the structure (the type name, NOT the        */
   /* variable name). The second parameter to this MACRO represents the */
   /* actual structure member that the offset is to be determined. This */
   /* MACRO returns an unsigned integer that represents the offset (in  */
   /* bytes) of the structure member.                                   */
#define QAPI_BLE_BTPS_STRUCTURE_OFFSET(_x, _y)           ((uintptr_t)&(((_x *)0)->_y))

#endif
