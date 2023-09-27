/*
 * Copyright (c) 2016-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/** @file qapi_ble_btbtypes.h */

#ifndef __QAPI_BLE_BTTYPESH_INC__
#error "qapi_ble_btbtypes.h should never be used directly.  Include qapi_ble_bttypes.h, instead."
#endif

#ifndef __QAPI_BLE_BTBTYPES_H__
#define __QAPI_BLE_BTBTYPES_H__

/** @addtogroup qapi_ble_core_hci
@{ */

   /** Represents the structure of a single Bluetooth Board Address. */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_BD_ADDR_s
{
   uint8_t BD_ADDR0;  /**< Byte 1 of the Bluetooth device address. */
   uint8_t BD_ADDR1;  /**< Byte 2 of the Bluetooth device address. */
   uint8_t BD_ADDR2;  /**< Byte 3 of the Bluetooth device address. */
   uint8_t BD_ADDR3;  /**< Byte 4 of the Bluetooth device address. */
   uint8_t BD_ADDR4;  /**< Byte 5 of the Bluetooth device address. */
   uint8_t BD_ADDR5;  /**< Byte 6 of the Bluetooth device address. */
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_BD_ADDR_t;

/** @} */ /* end_addtogroup qapi_ble_core_hci */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define QAPI_BLE_BD_ADDR_SIZE                            (sizeof(qapi_BLE_BD_ADDR_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified BD_ADDR variable.  The  */
   /* Bytes are NOT in Little Endian Format, however, they are assigned */
   /* to the BD_ADDR variable in Little Endian Format.  The first       */
   /* parameter is the BD_ADDR variable (of type qapi_BLE_BD_ADDR_t) to */
   /* assign, and the next six parameters are the Individual BD_ADDR    */
   /* Byte values to assign to the variable.                            */
#define QAPI_BLE_ASSIGN_BD_ADDR(_dest, _a, _b, _c, _d, _e, _f) \
{                                                     \
   (_dest).BD_ADDR0 = (_f);                           \
   (_dest).BD_ADDR1 = (_e);                           \
   (_dest).BD_ADDR2 = (_d);                           \
   (_dest).BD_ADDR3 = (_c);                           \
   (_dest).BD_ADDR4 = (_b);                           \
   (_dest).BD_ADDR5 = (_a);                           \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_BD_ADDR_t variables.  This MACRO only  */
   /* returns whether the two qapi_BLE_BD_ADDR_t variables are equal    */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_BD_ADDR_t  */
   /* and represent the qapi_BLE_BD_ADDR_t variables to compare.        */
#define QAPI_BLE_COMPARE_BD_ADDR(_x, _y) (((_x).BD_ADDR0 == (_y).BD_ADDR0) && ((_x).BD_ADDR1 == (_y).BD_ADDR1) && ((_x).BD_ADDR2 == (_y).BD_ADDR2) && ((_x).BD_ADDR3 == (_y).BD_ADDR3) && ((_x).BD_ADDR4 == (_y).BD_ADDR4) && ((_x).BD_ADDR5 == (_y).BD_ADDR5))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of a qapi_BLE_BD_ADDR_t variables to the NULL BD_ADDR. */
   /* This MACRO only returns whether the the qapi_BLE_BD_ADDR_t        */
   /* variable is equal to the NULL BD_ADDR (MACRO returns boolean      */
   /* result) NOT less than/greater than.  The parameter to this MACRO  */
   /* is the qapi_BLE_BD_ADDR_t structure to compare to the NULL        */
   /* BD_ADDR.                                                          */
#define QAPI_BLE_COMPARE_NULL_BD_ADDR(_x) (((_x).BD_ADDR0 == 0x00) && ((_x).BD_ADDR1 == 0x00) && ((_x).BD_ADDR2 == 0x00) && ((_x).BD_ADDR3 == 0x00) && ((_x).BD_ADDR4 == 0x00) && ((_x).BD_ADDR5 == 0x00))

   /* The following type declaration represents the structure of a      */
   /* single LAP (Lower Address Part).                                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_LAP_s
{
   uint8_t LAP0;
   uint8_t LAP1;
   uint8_t LAP2;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_LAP_t;

#define QAPI_BLE_LAP_SIZE                                (sizeof(qapi_BLE_LAP_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified LAP variable.  The Bytes*/
   /* are NOT in Little Endian Format, however, they are assigned to the*/
   /* LAP variable in Little Endian Format.  The first parameter is the */
   /* LAP variable (of type qapi_BLE_LAP_t) to assign, and the next     */
   /* three parameters are the Individual LAP values to assign to the   */
   /* variable.                                                         */
#define QAPI_BLE_ASSIGN_LAP(_dest, _x, _y, _z) \
{                                     \
   (_dest).LAP0 = (_z);               \
   (_dest).LAP1 = (_y);               \
   (_dest).LAP2 = (_x);               \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_LAP_t variables.  This MACRO only      */
   /* returns whether the two qapi_BLE_LAP_t variables are equal (MACRO */
   /* returns boolean result) NOT less than/greater than.  The two      */
   /* parameters to this MACRO are both of type qapi_BLE_LAP_t and      */
   /* represent the qapi_BLE_LAP_t variables to compare.                */
#define QAPI_BLE_COMPARE_LAP(_x, _y) (((_x).LAP0 == (_y).LAP0) && ((_x).LAP1 == (_y).LAP1) && ((_x).LAP2 == (_y).LAP2))

   /* The following type declaration represents the structure of a      */
   /* single Link Key.                                                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Link_Key_s
{
   uint8_t Link_Key0;
   uint8_t Link_Key1;
   uint8_t Link_Key2;
   uint8_t Link_Key3;
   uint8_t Link_Key4;
   uint8_t Link_Key5;
   uint8_t Link_Key6;
   uint8_t Link_Key7;
   uint8_t Link_Key8;
   uint8_t Link_Key9;
   uint8_t Link_Key10;
   uint8_t Link_Key11;
   uint8_t Link_Key12;
   uint8_t Link_Key13;
   uint8_t Link_Key14;
   uint8_t Link_Key15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Link_Key_t;

#define QAPI_BLE_LINK_KEY_SIZE                           (sizeof(qapi_BLE_Link_Key_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Link Key variable.  The */
   /* Bytes are NOT in Little Endian Format, however, they are assigned */
   /* to the Link Key variable in Little Endian Format.  The first      */
   /* parameter is the Link Key variable (of type qapi_BLE_Link_Key_t)  */
   /* to assign, and the next 16 parameters are the Individual Link Key */
   /* Byte values to assign to the Link Key variable.                   */
#define QAPI_BLE_ASSIGN_LINK_KEY(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                              \
   (_dest).Link_Key0  = (_p); (_dest).Link_Key1  = (_o); (_dest).Link_Key2  = (_n);            \
   (_dest).Link_Key3  = (_m); (_dest).Link_Key4  = (_l); (_dest).Link_Key5  = (_k);            \
   (_dest).Link_Key6  = (_j); (_dest).Link_Key7  = (_i); (_dest).Link_Key8  = (_h);            \
   (_dest).Link_Key9  = (_g); (_dest).Link_Key10 = (_f); (_dest).Link_Key11 = (_e);            \
   (_dest).Link_Key12 = (_d); (_dest).Link_Key13 = (_c); (_dest).Link_Key14 = (_b);            \
   (_dest).Link_Key15 = (_a);                                                                  \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Link_Key_t variables.  This MACRO only */
   /* returns whether the two qapi_BLE_Link_Key_t variables are equal   */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_Link_Key_t */
   /* and represent the qapi_BLE_Link_Key_t variables to compare.       */
#define QAPI_BLE_COMPARE_LINK_KEY(_x, _y)                                                                                           \
(                                                                                                                          \
   ((_x).Link_Key0  == (_y).Link_Key0)  && ((_x).Link_Key1  == (_y).Link_Key1)  && ((_x).Link_Key2  == (_y).Link_Key2)  && \
   ((_x).Link_Key3  == (_y).Link_Key3)  && ((_x).Link_Key4  == (_y).Link_Key4)  && ((_x).Link_Key5  == (_y).Link_Key5)  && \
   ((_x).Link_Key6  == (_y).Link_Key6)  && ((_x).Link_Key7  == (_y).Link_Key7)  && ((_x).Link_Key8  == (_y).Link_Key8)  && \
   ((_x).Link_Key9  == (_y).Link_Key9)  && ((_x).Link_Key10 == (_y).Link_Key10) && ((_x).Link_Key11 == (_y).Link_Key11) && \
   ((_x).Link_Key12 == (_y).Link_Key12) && ((_x).Link_Key13 == (_y).Link_Key13) && ((_x).Link_Key14 == (_y).Link_Key14) && \
   ((_x).Link_Key15 == (_y).Link_Key15)                                                                                    \
)

   /* The following type declaration represents the structure of a      */
   /* single PIN Code.                                                  */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_PIN_Code_s
{
   uint8_t PIN_Code0;
   uint8_t PIN_Code1;
   uint8_t PIN_Code2;
   uint8_t PIN_Code3;
   uint8_t PIN_Code4;
   uint8_t PIN_Code5;
   uint8_t PIN_Code6;
   uint8_t PIN_Code7;
   uint8_t PIN_Code8;
   uint8_t PIN_Code9;
   uint8_t PIN_Code10;
   uint8_t PIN_Code11;
   uint8_t PIN_Code12;
   uint8_t PIN_Code13;
   uint8_t PIN_Code14;
   uint8_t PIN_Code15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_PIN_Code_t;

#define QAPI_BLE_PIN_CODE_SIZE                           (sizeof(qapi_BLE_PIN_Code_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified PIN Code variable.  The */
   /* Bytes are NOT in Little Endian Format, and they are NOT assigned  */
   /* to the PIN Code variable in Little Endian Format.  The first      */
   /* parameter is the PIN Code variable (of type qapi_BLE_PIN_Code_t)  */
   /* to assign, and the next 16 parameters are the Individual PIN Code */
   /* Byte values to assign to the PIN Code variable.                   */
#define QAPI_BLE_ASSIGN_PIN_CODE(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                              \
   (_dest).PIN_Code0  = (_a); (_dest).PIN_Code1  = (_b); (_dest).PIN_Code2  = (_c);            \
   (_dest).PIN_Code3  = (_d); (_dest).PIN_Code4  = (_e); (_dest).PIN_Code5  = (_f);            \
   (_dest).PIN_Code6  = (_g); (_dest).PIN_Code7  = (_h); (_dest).PIN_Code8  = (_i);            \
   (_dest).PIN_Code9  = (_j); (_dest).PIN_Code10 = (_k); (_dest).PIN_Code11 = (_l);            \
   (_dest).PIN_Code12 = (_m); (_dest).PIN_Code13 = (_n); (_dest).PIN_Code14 = (_o);            \
   (_dest).PIN_Code15 = (_p);                                                                  \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_PIN_Code_t variables.  This MACRO only */
   /* returns whether the two qapi_BLE_PIN_Code_t variables are equal   */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_PIN_Code_t */
   /* and represent the qapi_BLE_PIN_Code_t variables to compare.       */
#define QAPI_BLE_COMPARE_PIN_CODE(_x, _y)                                                                                           \
(                                                                                                                          \
   ((_x).PIN_Code0  == (_y).PIN_Code0)  && ((_x).PIN_Code1  == (_y).PIN_Code1)  && ((_x).PIN_Code2  == (_y).PIN_Code2)  && \
   ((_x).PIN_Code3  == (_y).PIN_Code3)  && ((_x).PIN_Code4  == (_y).PIN_Code4)  && ((_x).PIN_Code5  == (_y).PIN_Code5)  && \
   ((_x).PIN_Code6  == (_y).PIN_Code6)  && ((_x).PIN_Code7  == (_y).PIN_Code7)  && ((_x).PIN_Code8  == (_y).PIN_Code8)  && \
   ((_x).PIN_Code9  == (_y).PIN_Code9)  && ((_x).PIN_Code10 == (_y).PIN_Code10) && ((_x).PIN_Code11 == (_y).PIN_Code11) && \
   ((_x).PIN_Code12 == (_y).PIN_Code12) && ((_x).PIN_Code13 == (_y).PIN_Code13) && ((_x).PIN_Code14 == (_y).PIN_Code14) && \
   ((_x).PIN_Code15 == (_y).PIN_Code15)                                                                                    \
)

   /* The following type declaration represents the structure of an     */
   /* Event Mask.                                                       */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Event_Mask_s
{
   uint8_t Event_Mask0;
   uint8_t Event_Mask1;
   uint8_t Event_Mask2;
   uint8_t Event_Mask3;
   uint8_t Event_Mask4;
   uint8_t Event_Mask5;
   uint8_t Event_Mask6;
   uint8_t Event_Mask7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Event_Mask_t;

#define QAPI_BLE_EVENT_MASK_SIZE                         (sizeof(qapi_BLE_Event_Mask_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Event Mask variable.    */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the Event Mask variable in Little Endian Format.  The */
   /* first parameter is the Event Mask variable (of type               */
   /* qapi_BLE_Event_Mask_t) to assign, and the next eight parameters   */
   /* are the Individual Event Mask Byte values to assign to the        */
   /* variable.                                                         */
#define QAPI_BLE_ASSIGN_EVENT_MASK(_dest, _a, _b, _c, _d, _e, _f, _g, _h) \
{                                                                \
   (_dest).Event_Mask0 = (_h);                                   \
   (_dest).Event_Mask1 = (_g);                                   \
   (_dest).Event_Mask2 = (_f);                                   \
   (_dest).Event_Mask3 = (_e);                                   \
   (_dest).Event_Mask4 = (_d);                                   \
   (_dest).Event_Mask5 = (_c);                                   \
   (_dest).Event_Mask6 = (_b);                                   \
   (_dest).Event_Mask7 = (_a);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Event_Mask_t variables.  This MACRO    */
   /* only returns whether the two qapi_BLE_Event_Mask_t variables are  */
   /* equal (MACRO returns boolean result) NOT less than/greater than.  */
   /* The two parameters to this MACRO are both of type                 */
   /* qapi_BLE_Event_Mask_t and represent the qapi_BLE_Event_Mask_t     */
   /* variables to compare.                                             */
#define QAPI_BLE_COMPARE_EVENT_MASK(_x, _y)                                                                                                 \
(                                                                                                                                  \
   ((_x).Event_Mask0 == (_y).Event_Mask0) && ((_x).Event_Mask1 == (_y).Event_Mask1) && ((_x).Event_Mask2  == (_y).Event_Mask2)  && \
   ((_x).Event_Mask3 == (_y).Event_Mask3) && ((_x).Event_Mask4 == (_y).Event_Mask4) && ((_x).Event_Mask5  == (_y).Event_Mask5)  && \
   ((_x).Event_Mask6 == (_y).Event_Mask6) && ((_x).Event_Mask7 == (_y).Event_Mask7)                                                \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of Event Bits in the Event Mask.  This MACRO accepts as   */
   /* input the Event Mask variable (of type qapi_BLE_Event_Mask_t) as  */
   /* the first parameter, and the bit number to set (LSB is bit number */
   /* 0).  This MACRO sets the bits in Little Endian Format (so bit 0 is*/
   /* physically bit 0 of the first byte of the Event Mask structure).  */
#define QAPI_BLE_SET_EVENT_MASK_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of Event Bits in the Event Mask.  This MACRO accepts as  */
   /* input the Event Mask variable (of type qapi_BLE_Event_Mask_t) as  */
   /* the first parameter, and the bit number to clear (LSB is bit      */
   /* number 0).  This MACRO clears the bits in Little Endian Format (so*/
   /* bit 0 is physically bit 0 of the first byte of the Event Mask     */
   /* structure).                                                       */
#define QAPI_BLE_CLEAR_EVENT_MASK_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of Event Bits in the Event Mask.  This MACRO accepts as   */
   /* input the Event Mask variable (of type qapi_BLE_Event_Mask_t) as  */
   /* the first parameter, and the bit number to test (LSB is bit number*/
   /* 0).  This MACRO tests the bits in Little Endian Format (so bit 0  */
   /* is physically bit 0 of the first byte of the Event Mask           */
   /* structure).  This MACRO returns a boolean result as the test      */
   /* result.                                                           */
#define QAPI_BLE_TEST_EVENT_MASK_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following type declaration represents the structure of a      */
   /* Device Class Type.                                                */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Class_of_Device_s
{
   uint8_t Class_of_Device0;
   uint8_t Class_of_Device1;
   uint8_t Class_of_Device2;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Class_of_Device_t;

#define QAPI_BLE_CLASS_OF_DEVICE_SIZE                    (sizeof(qapi_BLE_Class_of_Device_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified                         */
   /* qapi_BLE_Class_of_Device_t variable.  The Bytes are NOT in Little */
   /* Endian Format, however, they are assigned to the Class_of_Device  */
   /* variable in Little Endian Format.  The first parameter is the     */
   /* Class_of_Device variable (of type qapi_BLE_Class_of_Device_t) to  */
   /* assign, and the next three parameters are the Individual          */
   /* qapi_BLE_Class_of_Device_t values to assign to the variable.      */
#define QAPI_BLE_ASSIGN_CLASS_OF_DEVICE(_dest, _x, _y, _z) \
{                                                 \
   (_dest).Class_of_Device0 = (_z);               \
   (_dest).Class_of_Device1 = (_y);               \
   (_dest).Class_of_Device2 = (_x);               \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Class_of_Device_t variables.  This     */
   /* MACRO only returns whether the two qapi_BLE_Class_of_Device_t     */
   /* variables are equal (MACRO returns boolean result) NOT less       */
   /* than/greater than.  The two parameters to this MACRO are both of  */
   /* type qapi_BLE_Class_of_Device_t and represent the                 */
   /* qapi_BLE_Class_of_Device_t variables to compare.                  */
#define QAPI_BLE_COMPARE_CLASS_OF_DEVICE(_x, _y) (((_x).Class_of_Device0 == (_y).Class_of_Device0) && ((_x).Class_of_Device1 == (_y).Class_of_Device1) && ((_x).Class_of_Device2 == (_y).Class_of_Device2))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of Class of Device Bits in the Class of Device Type.  This*/
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter, and the bit   */
   /* number to set (LSB is bit number 0).  This MACRO sets the bits in */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the Class of Device structure).                           */
#define QAPI_BLE_SET_CLASS_OF_DEVICE_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of Class of Device Bits in the Class of Device Type.     */
   /* This MACRO accepts as input the Class of Device variable (of type */
   /* qapi_BLE_Class_of_Device_t) as the first parameter, and the bit   */
   /* number to clear (LSB is bit number 0).  This MACRO clears the bits*/
   /* in Little Endian Format (so bit 0 is physically bit 0 of the first*/
   /* byte of the Class of Device structure).                           */
#define QAPI_BLE_CLEAR_CLASS_OF_DEVICE_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of Class of Device Bits in the Class of Device Type.  This*/
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter, and the bit   */
   /* number to test (LSB is bit number 0).  This MACRO tests the bits  */
   /* in Little Endian Format (so bit 0 is physically bit 0 of the first*/
   /* byte of the Class of Device structure).  This MACRO returns a     */
   /* boolean result ast he test result.                                */
#define QAPI_BLE_TEST_CLASS_OF_DEVICE_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* reading of the Class of Device Format Type Field.  This MACRO     */
   /* accepts as input the Class of Device variable (of type            */
   /* qapi_BLE_Class_of_Device_t) as the first parameter.  This MACRO   */
   /* returns the Class of Device Format Type Value which is Right      */
   /* Justisfied (Bit-wise) and is of type uint8_t (Note the value      */
   /* returned will at most only have the lowest two bits set because   */
   /* this is the` size of the Format Type Field.                       */
#define QAPI_BLE_GET_CLASS_OF_DEVICE_FORMAT_TYPE(_x)                     \
   ((uint8_t)((_x).Class_of_Device0 & 0x03))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of the Class of Device Format Type Field.  This MACRO     */
   /* accepts as input the Class of Device variable (of type            */
   /* qapi_BLE_Class_of_Device_t) as the first parameter and the Format */
   /* Type Right Justified (Bit-Wise) to set (Note only the lower two   */
   /* bits of the Format Type are used when setting the Format Type).   */
#define QAPI_BLE_SET_CLASS_OF_DEVICE_FORMAT_TYPE(_x, _y)                 \
   ((_x).Class_of_Device0 = ((_x).Class_of_Device0 & 0xFC) | ((_y) & 0x03))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* reading of the Class of Device Major Service Class Field.  This   */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter.  This MACRO   */
   /* returns the Class of Device Major Service Class Field Value which */
   /* is Right Justisfied (Bit-wise) and is of type uint16_t (Note the  */
   /* value returned will at most only have the lowest eleven bits set  */
   /* because this is the size of the Major Service Class Field.        */
#define QAPI_BLE_GET_MAJOR_SERVICE_CLASS(_x)                                   \
  ((uint16_t)(((_x).Class_of_Device2 << 0x03) | ((_x).Class_of_Device1 >> 0x05)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of the Class of Device Major Service Class Field.  This   */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter and the Major  */
   /* Service Class Right Justified (Bit-Wise) to set (Note only the    */
   /* lower eleven bits of the Major Service Class are used when setting*/
   /* the Major Service Class).                                         */
#define QAPI_BLE_SET_MAJOR_SERVICE_CLASS(_x, _y)                       \
{                                                                      \
   (_x).Class_of_Device2  = (uint8_t)(((_y) & 0x7FF) >> 0x03);         \
   (_x).Class_of_Device1 &= (uint8_t)0x1F;                             \
   (_x).Class_of_Device1 |= (uint8_t)((((_y) & 0xFF) << 0x05) & 0xFF); \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* reading of the Class of Device Major Device Class Field.  This    */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter.  This MACRO   */
   /* returns the Class of Device Major Device Class Field Value which  */
   /* is Right Justisfied (Bit-wise) and is of type uint8_t (Note the   */
   /* value returned will at most only have the lowest five bits set    */
   /* because this is the size of the Major Device Class Field.         */
#define QAPI_BLE_GET_MAJOR_DEVICE_CLASS(_x)                            \
   ((uint8_t)((_x).Class_of_Device1 & 0x1F))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of the Class of Device Major Device Class Field.  This    */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter and the Major  */
   /* Device Class Right Justified (Bit-Wise) to set (Note only the     */
   /* lower five bits of the Major Device Class are used when setting   */
   /* the Major Device Class).                                          */
#define QAPI_BLE_SET_MAJOR_DEVICE_CLASS(_x, _y)                        \
{                                                                      \
   (_x).Class_of_Device1 &= 0xE0;                                      \
   (_x).Class_of_Device1 |= (uint8_t)((_y) & 0x1F);                    \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* reading of the Class of Device Minor Device Class Field.  This    */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter.  This MACRO   */
   /* returns the Class of Device Minor Device Class Field Value which  */
   /* is Right Justisfied (Bit-wise) and is of type uint8_t (Note the   */
   /* value returned will at most only have the lowest six bits set     */
   /* because this is the size of the Minor Device Class Field.         */
#define QAPI_BLE_GET_MINOR_DEVICE_CLASS(_x)                            \
   ((uint8_t)((_x).Class_of_Device0 >> 0x02))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of the Class of Device Minor Device Class Field.  This    */
   /* MACRO accepts as input the Class of Device variable (of type      */
   /* qapi_BLE_Class_of_Device_t) as the first parameter and the Minor  */
   /* Device Class Right Justified (Bit-Wise) to set (Note only the     */
   /* lower six bits of the Minor Device Class are used when setting the*/
   /* Minor Device Class).                                              */
#define QAPI_BLE_SET_MINOR_DEVICE_CLASS(_x, _y)                        \
{                                                                      \
   (_x).Class_of_Device0 &= (uint8_t)0x03;                             \
   (_x).Class_of_Device0 |= (uint8_t)(((_y) << 0x02) & 0xFC);          \
}

   /* The following type declaration represents the structure of a      */
   /* Supported Commands Type (Version 1.2).                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Supported_Commands_s
{
   uint8_t Supported_Commands0;
   uint8_t Supported_Commands1;
   uint8_t Supported_Commands2;
   uint8_t Supported_Commands3;
   uint8_t Supported_Commands4;
   uint8_t Supported_Commands5;
   uint8_t Supported_Commands6;
   uint8_t Supported_Commands7;
   uint8_t Supported_Commands8;
   uint8_t Supported_Commands9;
   uint8_t Supported_Commands10;
   uint8_t Supported_Commands11;
   uint8_t Supported_Commands12;
   uint8_t Supported_Commands13;
   uint8_t Supported_Commands14;
   uint8_t Supported_Commands15;
   uint8_t Supported_Commands16;
   uint8_t Supported_Commands17;
   uint8_t Supported_Commands18;
   uint8_t Supported_Commands19;
   uint8_t Supported_Commands20;
   uint8_t Supported_Commands21;
   uint8_t Supported_Commands22;
   uint8_t Supported_Commands23;
   uint8_t Supported_Commands24;
   uint8_t Supported_Commands25;
   uint8_t Supported_Commands26;
   uint8_t Supported_Commands27;
   uint8_t Supported_Commands28;
   uint8_t Supported_Commands29;
   uint8_t Supported_Commands30;
   uint8_t Supported_Commands31;
   uint8_t Supported_Commands32;
   uint8_t Supported_Commands33;
   uint8_t Supported_Commands34;
   uint8_t Supported_Commands35;
   uint8_t Supported_Commands36;
   uint8_t Supported_Commands37;
   uint8_t Supported_Commands38;
   uint8_t Supported_Commands39;
   uint8_t Supported_Commands40;
   uint8_t Supported_Commands41;
   uint8_t Supported_Commands42;
   uint8_t Supported_Commands43;
   uint8_t Supported_Commands44;
   uint8_t Supported_Commands45;
   uint8_t Supported_Commands46;
   uint8_t Supported_Commands47;
   uint8_t Supported_Commands48;
   uint8_t Supported_Commands49;
   uint8_t Supported_Commands50;
   uint8_t Supported_Commands51;
   uint8_t Supported_Commands52;
   uint8_t Supported_Commands53;
   uint8_t Supported_Commands54;
   uint8_t Supported_Commands55;
   uint8_t Supported_Commands56;
   uint8_t Supported_Commands57;
   uint8_t Supported_Commands58;
   uint8_t Supported_Commands59;
   uint8_t Supported_Commands60;
   uint8_t Supported_Commands61;
   uint8_t Supported_Commands62;
   uint8_t Supported_Commands63;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Supported_Commands_t;

#define QAPI_BLE_SUPPORTED_COMMANDS_SIZE                 (sizeof(qapi_BLE_Supported_Commands_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Supported_Commands      */
   /* variable.  The Bytes are NOT in Little Endian Format, however,    */
   /* they are assigned to the Supported_Commands variable in Little    */
   /* Endian Format.  The first parameter is the Supported_Commands     */
   /* variable (of type qapi_BLE_Supported_Commands_t) to assign, and   */
   /* the next sixty-four parameters are the Individual                 */
   /* Supported_Commands Byte values to assign to the variable.         */
#define QAPI_BLE_ASSIGN_SUPPORTED_COMMANDS(_dest, _a0, _b0, _c0, _d0, _e0, _f0, _g0, _h0, _a1, _b1, _c1, _d1, _e1, _f1, _g1, _h1, _a2, _b2, _c2, _d2, _e2, _f2, _g2, _h2, _a3, _b3, _c3, _d3, _e3, _f3, _g3, _h3, _a4, _b4, _c4, _d4, _e4, _f4, _g4, _h4, _a5, _b5, _c5, _d5, _e5, _f5, _g5, _h5, _a6, _b6, _c6, _d6, _e6, _f6, _g6, _h6, _a7, _b7, _c7, _d7, _e7, _f7, _g7, _h7) \
{                                                                  \
   (_dest).Supported_Commands0  = (_h7);                                   \
   (_dest).Supported_Commands1  = (_g7);                                   \
   (_dest).Supported_Commands2  = (_f7);                                   \
   (_dest).Supported_Commands3  = (_e7);                                   \
   (_dest).Supported_Commands4  = (_d7);                                   \
   (_dest).Supported_Commands5  = (_c7);                                   \
   (_dest).Supported_Commands6  = (_b7);                                   \
   (_dest).Supported_Commands7  = (_a7);                                   \
   (_dest).Supported_Commands8  = (_h6);                                   \
   (_dest).Supported_Commands9  = (_g6);                                   \
   (_dest).Supported_Commands10 = (_f6);                                   \
   (_dest).Supported_Commands11 = (_e6);                                   \
   (_dest).Supported_Commands12 = (_d6);                                   \
   (_dest).Supported_Commands13 = (_c6);                                   \
   (_dest).Supported_Commands14 = (_b6);                                   \
   (_dest).Supported_Commands15 = (_a6);                                   \
   (_dest).Supported_Commands16 = (_h5);                                   \
   (_dest).Supported_Commands17 = (_g5);                                   \
   (_dest).Supported_Commands18 = (_f5);                                   \
   (_dest).Supported_Commands19 = (_e5);                                   \
   (_dest).Supported_Commands20 = (_d5);                                   \
   (_dest).Supported_Commands21 = (_c5);                                   \
   (_dest).Supported_Commands22 = (_b5);                                   \
   (_dest).Supported_Commands23 = (_a5);                                   \
   (_dest).Supported_Commands24 = (_h4);                                   \
   (_dest).Supported_Commands25 = (_g4);                                   \
   (_dest).Supported_Commands26 = (_f4);                                   \
   (_dest).Supported_Commands27 = (_e4);                                   \
   (_dest).Supported_Commands28 = (_d4);                                   \
   (_dest).Supported_Commands29 = (_c4);                                   \
   (_dest).Supported_Commands30 = (_b4);                                   \
   (_dest).Supported_Commands31 = (_a4);                                   \
   (_dest).Supported_Commands32 = (_h3);                                   \
   (_dest).Supported_Commands33 = (_g3);                                   \
   (_dest).Supported_Commands34 = (_f3);                                   \
   (_dest).Supported_Commands35 = (_e3);                                   \
   (_dest).Supported_Commands36 = (_d3);                                   \
   (_dest).Supported_Commands37 = (_c3);                                   \
   (_dest).Supported_Commands38 = (_b3);                                   \
   (_dest).Supported_Commands39 = (_a3);                                   \
   (_dest).Supported_Commands40 = (_h2);                                   \
   (_dest).Supported_Commands41 = (_g2);                                   \
   (_dest).Supported_Commands42 = (_f2);                                   \
   (_dest).Supported_Commands43 = (_e2);                                   \
   (_dest).Supported_Commands44 = (_d2);                                   \
   (_dest).Supported_Commands45 = (_c2);                                   \
   (_dest).Supported_Commands46 = (_b2);                                   \
   (_dest).Supported_Commands47 = (_a2);                                   \
   (_dest).Supported_Commands48 = (_h1);                                   \
   (_dest).Supported_Commands49 = (_g1);                                   \
   (_dest).Supported_Commands50 = (_f1);                                   \
   (_dest).Supported_Commands51 = (_e1);                                   \
   (_dest).Supported_Commands52 = (_d1);                                   \
   (_dest).Supported_Commands53 = (_c1);                                   \
   (_dest).Supported_Commands54 = (_b1);                                   \
   (_dest).Supported_Commands55 = (_a1);                                   \
   (_dest).Supported_Commands56 = (_h0);                                   \
   (_dest).Supported_Commands57 = (_g0);                                   \
   (_dest).Supported_Commands58 = (_f0);                                   \
   (_dest).Supported_Commands59 = (_e0);                                   \
   (_dest).Supported_Commands60 = (_d0);                                   \
   (_dest).Supported_Commands61 = (_c0);                                   \
   (_dest).Supported_Commands62 = (_b0);                                   \
   (_dest).Supported_Commands63 = (_a0);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Supported_Commands_t variables.  This  */
   /* MACRO only returns whether the two qapi_BLE_Supported_Commands_t  */
   /* variables are equal (MACRO returns boolean result) NOT less       */
   /* than/greater than.  The two parameters to this MACRO are both of  */
   /* type qapi_BLE_Supported_Commands_t and represent the              */
   /* qapi_BLE_Supported_Commands_t variables to compare.               */
   /* * NOTE * Due to the size of the data types involved, it will      */
   /*          generate far less code to simply perform a Memory        */
   /*          Comparison instead of using this MACRO.                  */
#define QAPI_BLE_COMPARE_SUPPORTED_COMMANDS(_x, _y)                                                                                                                                             \
(                                                                                                                                                                                      \
   ((_x).Supported_Commands0  == (_y).Supported_Commands0)  && ((_x).Supported_Commands1  == (_y).Supported_Commands1)  && ((_x).Supported_Commands2  == (_y).Supported_Commands2)  && \
   ((_x).Supported_Commands3  == (_y).Supported_Commands3)  && ((_x).Supported_Commands4  == (_y).Supported_Commands4)  && ((_x).Supported_Commands5  == (_y).Supported_Commands5)  && \
   ((_x).Supported_Commands6  == (_y).Supported_Commands6)  && ((_x).Supported_Commands7  == (_y).Supported_Commands7)                                                              && \
   ((_x).Supported_Commands8  == (_y).Supported_Commands8)  && ((_x).Supported_Commands9  == (_y).Supported_Commands9)  && ((_x).Supported_Commands10 == (_y).Supported_Commands10) && \
   ((_x).Supported_Commands11 == (_y).Supported_Commands11) && ((_x).Supported_Commands12 == (_y).Supported_Commands12) && ((_x).Supported_Commands13 == (_y).Supported_Commands13) && \
   ((_x).Supported_Commands14 == (_y).Supported_Commands14) && ((_x).Supported_Commands15 == (_y).Supported_Commands15)                                                             && \
   ((_x).Supported_Commands16 == (_y).Supported_Commands16) && ((_x).Supported_Commands17 == (_y).Supported_Commands17) && ((_x).Supported_Commands18 == (_y).Supported_Commands18) && \
   ((_x).Supported_Commands19 == (_y).Supported_Commands19) && ((_x).Supported_Commands20 == (_y).Supported_Commands20) && ((_x).Supported_Commands21 == (_y).Supported_Commands21) && \
   ((_x).Supported_Commands22 == (_y).Supported_Commands22) && ((_x).Supported_Commands23 == (_y).Supported_Commands23)                                                             && \
   ((_x).Supported_Commands24 == (_y).Supported_Commands24) && ((_x).Supported_Commands25 == (_y).Supported_Commands25) && ((_x).Supported_Commands26 == (_y).Supported_Commands26) && \
   ((_x).Supported_Commands27 == (_y).Supported_Commands27) && ((_x).Supported_Commands28 == (_y).Supported_Commands28) && ((_x).Supported_Commands29 == (_y).Supported_Commands29) && \
   ((_x).Supported_Commands30 == (_y).Supported_Commands30) && ((_x).Supported_Commands31 == (_y).Supported_Commands31)                                                             && \
   ((_x).Supported_Commands32 == (_y).Supported_Commands32) && ((_x).Supported_Commands33 == (_y).Supported_Commands33) && ((_x).Supported_Commands34 == (_y).Supported_Commands34) && \
   ((_x).Supported_Commands35 == (_y).Supported_Commands35) && ((_x).Supported_Commands36 == (_y).Supported_Commands36) && ((_x).Supported_Commands37 == (_y).Supported_Commands37) && \
   ((_x).Supported_Commands38 == (_y).Supported_Commands38) && ((_x).Supported_Commands39 == (_y).Supported_Commands39)                                                             && \
   ((_x).Supported_Commands40 == (_y).Supported_Commands40) && ((_x).Supported_Commands41 == (_y).Supported_Commands41) && ((_x).Supported_Commands42 == (_y).Supported_Commands42) && \
   ((_x).Supported_Commands43 == (_y).Supported_Commands43) && ((_x).Supported_Commands44 == (_y).Supported_Commands44) && ((_x).Supported_Commands45 == (_y).Supported_Commands45) && \
   ((_x).Supported_Commands46 == (_y).Supported_Commands46) && ((_x).Supported_Commands47 == (_y).Supported_Commands47)                                                             && \
   ((_x).Supported_Commands48 == (_y).Supported_Commands48) && ((_x).Supported_Commands49 == (_y).Supported_Commands49) && ((_x).Supported_Commands50 == (_y).Supported_Commands50) && \
   ((_x).Supported_Commands51 == (_y).Supported_Commands51) && ((_x).Supported_Commands52 == (_y).Supported_Commands52) && ((_x).Supported_Commands53 == (_y).Supported_Commands53) && \
   ((_x).Supported_Commands54 == (_y).Supported_Commands54) && ((_x).Supported_Commands55 == (_y).Supported_Commands55)                                                             && \
   ((_x).Supported_Commands56 == (_y).Supported_Commands56) && ((_x).Supported_Commands57 == (_y).Supported_Commands57) && ((_x).Supported_Commands58 == (_y).Supported_Commands58) && \
   ((_x).Supported_Commands59 == (_y).Supported_Commands59) && ((_x).Supported_Commands60 == (_y).Supported_Commands60) && ((_x).Supported_Commands61 == (_y).Supported_Commands61) && \
   ((_x).Supported_Commands62 == (_y).Supported_Commands62) && ((_x).Supported_Commands63 == (_y).Supported_Commands63)                                                                \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of Supported Commands Bits in the Supported Commands Mask.*/
   /* This MACRO accepts as input the Supported Commands Mask variable  */
   /* (of type qapi_BLE_Supported_Commands_t) as the first parameter,   */
   /* and the bit number to set (LSB is bit number 0).  This MACRO sets */
   /* the bits in Little Endian Format (so bit 0 is physically bit 0 of */
   /* the first byte of the Supported Commands Mask structure).         */
#define QAPI_BLE_SET_SUPPORTED_COMMANDS_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of Supported Commands Bits in the Supported Commands     */
   /* Mask.  This MACRO accepts as input the Supported Commands Mask    */
   /* variable (of type qapi_BLE_Supported_Commands_t) as the first     */
   /* parameter, and the bit number to clear (LSB is bit number 0).     */
   /* This MACRO clears the bits in Little Endian Format (so bit 0 is   */
   /* physically bit 0 of the first byte of the Supported Commands Mask */
   /* structure).                                                       */
#define QAPI_BLE_CLEAR_SUPPORTED_COMMANDS_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of Supported Commands Bits in the Supported Commands Mask.*/
   /* This MACRO accepts as input the Supported Commands Mask variable  */
   /* (of type qapi_BLE_Supported_Commands_t) as the first parameter,   */
   /* and the bit number to test (LSB is bit number 0).  This MACRO     */
   /* tests the bits in Little Endian Format (so bit 0 is physically bit*/
   /* 0 of the first byte of the Supported Commands Mask structure).    */
   /* This MACRO returns a boolean result as the test result.           */
#define QAPI_BLE_TEST_SUPPORTED_COMMANDS_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following type declaration represents the structure of a      */
   /* LMP Feature Type.                                                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_LMP_Features_s
{
   uint8_t LMP_Features0;
   uint8_t LMP_Features1;
   uint8_t LMP_Features2;
   uint8_t LMP_Features3;
   uint8_t LMP_Features4;
   uint8_t LMP_Features5;
   uint8_t LMP_Features6;
   uint8_t LMP_Features7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_LMP_Features_t;

#define QAPI_BLE_LMP_FEATURES_SIZE                       (sizeof(qapi_BLE_LMP_Features_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified LMP_Features variable.  */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the LMP_Features variable in Little Endian Format.    */
   /* The first parameter is the LMP_Features variable (of type         */
   /* qapi_BLE_LMP_Features_t) to assign, and the next eight parameters */
   /* are the Individual LMP_Features Byte values to assign to the      */
   /* variable.                                                         */
#define QAPI_BLE_ASSIGN_LMP_FEATURES(_dest, _a, _b, _c, _d, _e, _f, _g, _h) \
{                                                                  \
   (_dest).LMP_Features0 = (_h);                                   \
   (_dest).LMP_Features1 = (_g);                                   \
   (_dest).LMP_Features2 = (_f);                                   \
   (_dest).LMP_Features3 = (_e);                                   \
   (_dest).LMP_Features4 = (_d);                                   \
   (_dest).LMP_Features5 = (_c);                                   \
   (_dest).LMP_Features6 = (_b);                                   \
   (_dest).LMP_Features7 = (_a);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_LMP_Features_t variables.  This MACRO  */
   /* only returns whether the two qapi_BLE_LMP_Features_t variables are*/
   /* equal (MACRO returns boolean result) NOT less than/greater than.  */
   /* The two parameters to this MACRO are both of type                 */
   /* qapi_BLE_LMP_Features_t and represent the qapi_BLE_LMP_Features_t */
   /* variables to compare.                                             */
#define QAPI_BLE_COMPARE_LMP_FEATURES(_x, _y)                                                                                                           \
(                                                                                                                                              \
   ((_x).LMP_Features0 == (_y).LMP_Features0) && ((_x).LMP_Features1 == (_y).LMP_Features1) && ((_x).LMP_Features2  == (_y).LMP_Features2)  && \
   ((_x).LMP_Features3 == (_y).LMP_Features3) && ((_x).LMP_Features4 == (_y).LMP_Features4) && ((_x).LMP_Features5  == (_y).LMP_Features5)  && \
   ((_x).LMP_Features6 == (_y).LMP_Features6) && ((_x).LMP_Features7 == (_y).LMP_Features7)                                                    \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of LMP Features Bits in the LMP Features Mask.  This MACRO*/
   /* accepts as input the LMP Features Mask variable (of type          */
   /* qapi_BLE_LMP_Features_t) as the first parameter, and the bit      */
   /* number to set (LSB is bit number 0).  This MACRO sets the bits in */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the LMP Features Mask structure).                         */
#define QAPI_BLE_SET_FEATURES_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of LMP Features Bits in the LMP Features Mask.  This     */
   /* MACRO accepts as input the LMP Features Mask variable (of type    */
   /* qapi_BLE_LMP_Features_t) as the first parameter, and the bit      */
   /* number to clear (LSB is bit number 0).  This MACRO clears the bits*/
   /* in Little Endian Format (so bit 0 is physically bit 0 of the first*/
   /* byte of the LMP Features Mask structure).                         */
#define QAPI_BLE_CLEAR_FEATURES_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of LMP Features Bits in the LMP Features Mask.  This MACRO*/
   /* accepts as input the LMP Features Mask variable (of type          */
   /* qapi_BLE_LMP_Features_t) as the first parameter, and the bit      */
   /* number to test (LSB is bit number 0).  This MACRO tests the bits  */
   /* in Little Endian Format (so bit 0 is physically bit 0 of the first*/
   /* byte of the LMP Features Mask structure).  This MACRO returns a   */
   /* boolean result as the test result.                                */
#define QAPI_BLE_TEST_FEATURES_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following structure represents the format of the Inquiry      */
   /* Result Filter Type, Class of Device Condition Condition.  This    */
   /* Type is used with the qapi_BLE_Condition_t type declared below.   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Inquiry_Result_Filter_Type_Class_of_Device_Condition_s
{
   qapi_BLE_Class_of_Device_t Class_of_Device;
   qapi_BLE_Class_of_Device_t Class_of_Device_Mask;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Inquiry_Result_Filter_Type_Class_of_Device_Condition_t;

#define QAPI_BLE_INQUIRY_RESULT_FILTER_TYPE_CLASS_OF_DEVICE_CONDITION_SIZE       (sizeof(qapi_BLE_Inquiry_Result_Filter_Type_Class_of_Device_Condition_t))

   /* The following structure represents the format of the Inquiry      */
   /* Result Filter Type, BD_ADDR Condition Condition.  This Type is    */
   /* used with the qapi_BLE_Condition_t type declared below.           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Inquiry_Result_Filter_Type_BD_ADDR_Condition_s
{
   qapi_BLE_BD_ADDR_t BD_ADDR;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Inquiry_Result_Filter_Type_BD_ADDR_Condition_t;

#define QAPI_BLE_INQUIRY_RESULT_FILTER_TYPE_BD_ADDR_CONDITION_SIZE               (sizeof(qapi_BLE_Inquiry_Result_Filter_Type_BD_ADDR_Condition_t))

   /* The following structure represents the format of the Connection   */
   /* Setup Filter Type, All Devices Condition Condition.  This Type is */
   /* used with the qapi_BLE_Condition_t type declared below.           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Connection_Setup_Filter_Type_All_Devices_Condition_s
{
   uint8_t  Auto_Accept_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Connection_Setup_Filter_Type_All_Devices_Condition_t;

#define QAPI_BLE_CONNECTION_SETUP_FILTER_TYPE_ALL_DEVICES_CONDITION_SIZE         (sizeof(qapi_BLE_Connection_Setup_Filter_Type_All_Devices_Condition_t))

   /* The following structure represents the format of the Connection   */
   /* Setup Filter Type, Class of Device Condition Condition.  This Type*/
   /* is used with the qapi_BLE_Condition_t type declared below.        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Connection_Setup_Filter_Type_Class_of_Device_Condition_s
{
   qapi_BLE_Class_of_Device_t Class_of_Device;
   qapi_BLE_Class_of_Device_t Class_of_Device_Mask;
   uint8_t                    Auto_Accept_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Connection_Setup_Filter_Type_Class_of_Device_Condition_t;

#define QAPI_BLE_CONNECTION_SETUP_FILTER_TYPE_CLASS_OF_DEVICE_CONDITION_SIZE     (sizeof(qapi_BLE_Connection_Setup_Filter_Type_Class_of_Device_Condition_t))

   /* The following structure represents the format of the Connection   */
   /* Setup Filter Type, BD_ADDR Condition Condition.  This Type is used*/
   /* with the qapi_BLE_Condition_t type declared below.                */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Connection_Setup_Filter_Type_BD_ADDR_Condition_s
{
   qapi_BLE_BD_ADDR_t BD_ADDR;
   uint8_t            Auto_Accept_Flag;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Connection_Setup_Filter_Type_BD_ADDR_Condition_t;

#define QAPI_BLE_CONNECTION_SETUP_FILTER_TYPE_BD_ADDR_CONDITION_SIZE             (sizeof(qapi_BLE_Connection_Setup_Filter_Type_BD_ADDR_Condition_t))

   /* The following structure represents the format of the RAW Data     */
   /* Bytes contained in a qapi_BLE_Condition_t type variable.          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Raw_Condition_Bytes_s
{
   uint8_t Condition0;
   uint8_t Condition1;
   uint8_t Condition2;
   uint8_t Condition3;
   uint8_t Condition4;
   uint8_t Condition5;
   uint8_t Condition6;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Raw_Condition_Bytes_t;

#define QAPI_BLE_RAW_CONDITION_SIZE                                              (sizeof(qapi_BLE_Raw_Condition_Bytes_t))

   /* The following type declaration represents the structure of a      */
   /* Filter Condition.                                                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Condition_s
{
   __QAPI_BLE_PACKED_STRUCT_BEGIN__ union
   {
      qapi_BLE_Inquiry_Result_Filter_Type_Class_of_Device_Condition_t   Inquiry_Result_Filter_Type_Class_of_Device_Condition;
      qapi_BLE_Inquiry_Result_Filter_Type_BD_ADDR_Condition_t           Inquiry_Result_Filter_Type_BD_ADDR_Condition;

      qapi_BLE_Connection_Setup_Filter_Type_All_Devices_Condition_t     Connection_Setup_Filter_Type_All_Devices_Condition;
      qapi_BLE_Connection_Setup_Filter_Type_Class_of_Device_Condition_t Connection_Setup_Filter_Type_Class_of_Device_Condition;
      qapi_BLE_Connection_Setup_Filter_Type_BD_ADDR_Condition_t         Connection_Setup_Filter_Type_BD_ADDR_Condition;

      qapi_BLE_Raw_Condition_Bytes_t                                    Raw_Condition_Bytes;
   } __QAPI_BLE_PACKED_STRUCT_END__ Condition;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Condition_t;

#define QAPI_BLE_MAX_CONDITION_SIZE                      (sizeof(qapi_BLE_Condition_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Condition variable.  The*/
   /* Bytes are NOT in Little Endian Format, however, they are assigned */
   /* to the Condition variable in Little Endian Format.  The first     */
   /* parameter is the Condition variable (of type qapi_BLE_Condition_t)*/
   /* to assign, and the next seven parameters are the Individual       */
   /* Condition Byte values to assign to the variable.                  */
   /* * NOTE * This MACRO Only assigns RAW Condition Byte values to the */
   /*          specified Condition.                                     */
#define QAPI_BLE_ASSIGN_RAW_CONDITION(_dest, _a, _b, _c, _d, _e, _f, _g) \
{                                                               \
   (_dest).Condition.Raw_Condition_Bytes.Condition0 = (_g);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition1 = (_f);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition2 = (_e);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition3 = (_d);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition4 = (_c);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition5 = (_b);     \
   (_dest).Condition.Raw_Condition_Bytes.Condition6 = (_a);     \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Condition_t variables.  This MACRO only*/
   /* returns whether the two qapi_BLE_Condition_t variables are equal  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_Condition_t*/
   /* and represent the qapi_BLE_Condition_t variables to compare.      */
   /* * NOTE * This MACRO ONLY Compares the RAW Condition Bytes, so ALL */
   /*          Bytes MUST Match.                                        */
#define QAPI_BLE_COMPARE_RAW_CONDITION(_x, _y)                                                         \
(                                                                                                      \
   ((_x).Condition.Raw_Condition_Bytes.Condition0 == (_y).Condition.Raw_Condition_Bytes.Condition0) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition1 == (_y).Condition.Raw_Condition_Bytes.Condition1) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition2 == (_y).Condition.Raw_Condition_Bytes.Condition2) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition3 == (_y).Condition.Raw_Condition_Bytes.Condition3) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition4 == (_y).Condition.Raw_Condition_Bytes.Condition4) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition5 == (_y).ondition.Raw_Condition_Bytes.CCondition5) && \
   ((_x).Condition.Raw_Condition_Bytes.Condition6 == (_y).Condition.Raw_Condition_Bytes.Condition6)    \
)

   /* The following type declaration represents the structure of a AFH  */
   /* Channel Map Type (Version 1.2).                                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_AFH_Channel_Map_s
{
   uint8_t AFH_Channel_Map0;
   uint8_t AFH_Channel_Map1;
   uint8_t AFH_Channel_Map2;
   uint8_t AFH_Channel_Map3;
   uint8_t AFH_Channel_Map4;
   uint8_t AFH_Channel_Map5;
   uint8_t AFH_Channel_Map6;
   uint8_t AFH_Channel_Map7;
   uint8_t AFH_Channel_Map8;
   uint8_t AFH_Channel_Map9;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_AFH_Channel_Map_t;

#define QAPI_BLE_AFH_CHANNEL_MAP_SIZE                    (sizeof(qapi_BLE_AFH_Channel_Map_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified AFH_Channel_Map         */
   /* variable.  The Bytes specified are written directly into the AFH  */
   /* Channel Map in the order they are listed.  The first parameter is */
   /* the AFH_Channel_Map variable (of type qapi_BLE_AFH_Channel_Map_t) */
   /* to assign, and the next ten parameters are the Individual         */
   /* AFH_Channel_Map Byte values to assign to the variable.            */
#define QAPI_BLE_ASSIGN_AFH_CHANNEL_MAP(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j) \
{                                                                             \
   (_dest).AFH_Channel_Map0 = (_j);                                           \
   (_dest).AFH_Channel_Map1 = (_i);                                           \
   (_dest).AFH_Channel_Map2 = (_h);                                           \
   (_dest).AFH_Channel_Map3 = (_g);                                           \
   (_dest).AFH_Channel_Map4 = (_f);                                           \
   (_dest).AFH_Channel_Map5 = (_e);                                           \
   (_dest).AFH_Channel_Map6 = (_d);                                           \
   (_dest).AFH_Channel_Map7 = (_c);                                           \
   (_dest).AFH_Channel_Map8 = (_b);                                           \
   (_dest).AFH_Channel_Map9 = (_a);                                           \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_AFH_Channel_Map_t variables.  This     */
   /* MACRO only returns whether the two qapi_BLE_AFH_Channel_Map_t     */
   /* variables are equal (MACRO returns boolean result) NOT less       */
   /* than/greater than.  The two parameters to this MACRO are both of  */
   /* type qapi_BLE_AFH_Channel_Map_t and represent the                 */
   /* qapi_BLE_AFH_Channel_Map_t variables to compare.                  */
#define QAPI_BLE_COMPARE_AFH_CHANNEL_MAP(_x, _y)                                                                                                                        \
(                                                                                                                                                              \
   ((_x).AFH_Channel_Map0 == (_y).AFH_Channel_Map0) && ((_x).AFH_Channel_Map1 == (_y).AFH_Channel_Map1) && ((_x).AFH_Channel_Map2 == (_y).AFH_Channel_Map2) && \
   ((_x).AFH_Channel_Map3 == (_y).AFH_Channel_Map3) && ((_x).AFH_Channel_Map4 == (_y).AFH_Channel_Map4) && ((_x).AFH_Channel_Map5 == (_y).AFH_Channel_Map5) && \
   ((_x).AFH_Channel_Map6 == (_y).AFH_Channel_Map6) && ((_x).AFH_Channel_Map7 == (_y).AFH_Channel_Map7) && ((_x).AFH_Channel_Map8 == (_y).AFH_Channel_Map8) && \
   ((_x).AFH_Channel_Map9 == (_y).AFH_Channel_Map9)                                                                                                            \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of AFH Channel Map Channel in the AFH Channel Map.  This  */
   /* MACRO accepts as input the AFH Channel Map variable (of type      */
   /* qapi_BLE_AFH_Channel_Map_t) as the first parameter, and the       */
   /* Channel Number to set.                                            */
#define QAPI_BLE_SET_AFH_CHANNEL_MAP_CHANNEL(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of AFH Channel Map Channel in the AFH Channel Map.  This */
   /* MACRO accepts as input the AFH Channel Map variable (of type      */
   /* qapi_BLE_AFH_Channel_Map_t) as the first parameter, and the       */
   /* Channel Number to clear.                                          */
#define QAPI_BLE_CLEAR_AFH_CHANNEL_MAP_CHANNEL(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of AFH Channel Map Channel in the AFH Channel Map.  This  */
   /* MACRO accepts as input the AFH Channel Map variable (of type      */
   /* qapi_BLE_AFH_Channel_Map_t) as the first parameter, and the       */
   /* Channel Number to test.                                           */
#define QAPI_BLE_TEST_AFH_CHANNEL_MAP_CHANNEL(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following constant represents the Maximum Number of Bytes     */
   /* that a Name variable an occupy.  It should be noted that for      */
   /* Names that have lengths less than this maximum, a NULL terminating*/
   /* character should be used and IS counted as part of the Length.    */
   /* For a Name of 248 Bytes, there is NO NULL terminating character   */
   /* at the end of the Name Data.                                      */
#define QAPI_BLE_MAX_NAME_LENGTH                                              248

   /* The following type declaration represents the structure of a      */
   /* Bluetooth Name Type.                                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Bluetooth_Name_s
{
   uint8_t Name[QAPI_BLE_MAX_NAME_LENGTH];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Bluetooth_Name_t;

#define QAPI_BLE_BLUETOOTH_NAME_SIZE                     (sizeof(qapi_BLE_Bluetooth_Name_t))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the extended inquiry response returned by the      */
   /* local device.  The size of this buffer is always fixed.           */
#define QAPI_BLE_EXTENDED_INQUIRY_RESPONSE_DATA_MAXIMUM_SIZE                  240

   /* The following type defines the buffer that is used to write or    */
   /* read the extended inquiry response data to be returned by the     */
   /* local device.  The size of this buffer is always fixed.           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Extended_Inquiry_Response_Data_s
{
   uint8_t Extended_Inquiry_Response_Data[QAPI_BLE_EXTENDED_INQUIRY_RESPONSE_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Extended_Inquiry_Response_Data_t;

#define QAPI_BLE_EXTENDED_INQUIRY_RESPONSE_DATA_SIZE     (sizeof(qapi_BLE_Extended_Inquiry_Response_Data_t))

   /* This structure defines what each individual element within the    */
   /* Extended Inquiry Response Data looks like.  The first octet is the*/
   /* length of the of the data element, followed by the data type, and */
   /* finally the data itself.  See the Bluetooth Specification 2.1 +   */
   /* EDR, Volume 3, Part C, Section 8 for more information.            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Extended_Inquiry_Response_Data_Structure_Data_s
{
   uint8_t Length;
   uint8_t Data_Type;
   uint8_t Variable_Data[1];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Extended_Inquiry_Response_Data_Structure_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an individual     */
   /* Extended Inquiry Response Data Structure Element based upon the   */
   /* lenght (in Bytes) of the variable data portion.  The first        */
   /* parameter to this MACRO is the Length (in Bytes) of the variable  */
   /* data contained in the individual Extended Inquiry Response Data   */
   /* Structure record.                                                 */
#define QAPI_BLE_EXTENDED_INQUIRY_RESPONSE_DATA_STRUCTURE_DATA_SIZE(_x)       ((sizeof(qapi_BLE_Extended_Inquiry_Response_Data_Structure_Data_t) - sizeof(uint8_t)) + ((uint32_t)(_x)))

   /* The following type declaration represents the structure of an     */
   /* L2CAP Extended Event Mask.  In Memory, the structure will         */
   /* represent a 32 bit (4 octet) value that assigns Bit 0 to Bit 31   */
   /* from left to right.                                               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_L2CAP_Extended_Feature_Mask_s
{
   uint8_t Extended_Feature_Mask0;
   uint8_t Extended_Feature_Mask1;
   uint8_t Extended_Feature_Mask2;
   uint8_t Extended_Feature_Mask3;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_L2CAP_Extended_Feature_Mask_t;

#define QAPI_BLE_L2CAP_EXTENDED_FEATURE_MASK_SIZE        (sizeof(qapi_BLE_L2CAP_Extended_Feature_Mask_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Extended Feature Mask   */
   /* variable.  Extreme care must be taken when using this function to */
   /* manually assign values to this structure.  The data is saved in a */
   /* format where Mask 0 corresponds to octet 0 and Mask 3 corresponds */
   /* to octet 3.  Each octet is arranged so that the left most bit of  */
   /* the octet contains the LSB of the value.  The first parameter is  */
   /* the Extended Feature Mask variable (of type                       */
   /* qapi_BLE_L2CAP_Extended_Feature_Mask_t) to assign, and the next   */
   /* four parameters are the Individual Extended Feature Mask Byte     */
   /* values to assign to the variable.                                 */
#define QAPI_BLE_ASSIGN_L2CAP_EXTENDED_FEATURE_MASK(_dest, _a, _b, _c, _d) \
{                                                                 \
   (_dest).Extended_Feature_Mask0 = (_a);                         \
   (_dest).Extended_Feature_Mask1 = (_b);                         \
   (_dest).Extended_Feature_Mask2 = (_c);                         \
   (_dest).Extended_Feature_Mask3 = (_d);                         \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two Extended_Feature_Mask_t variables.  This MACRO  */
   /* only returns whether the two Extended_Feature_Mask_t variables are*/
   /* equal (MACRO returns boolean result) NOT less than/greater than.  */
   /* The two parameters to this MACRO are both of type                 */
   /* qapi_BLE_L2CAP_Extended_Feature_Mask_t and represent the          */
   /* Extended_Feature_Mask_t variables to compare.                     */
#define QAPI_BLE_COMPARE_L2CAP_EXTENDED_FEATURE_MASK(_x, _y)                \
(                                                                  \
   ((_x).Extended_Feature_Mask0 == (_y).Extended_Feature_Mask0) && \
   ((_x).Extended_Feature_Mask1 == (_y).Extended_Feature_Mask1) && \
   ((_x).Extended_Feature_Mask2 == (_y).Extended_Feature_Mask2) && \
   ((_x).Extended_Feature_Mask3 == (_y).Extended_Feature_Mask3)    \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of L2CAP Extended Feature Bits in the Extended Feature    */
   /* Mask.  This MACRO accepts as input the Extended Feature Mask      */
   /* variable (of type qapi_BLE_L2CAP_Extended_Feature_Mask_t) as the  */
   /* first parameter, and the bit number to set.  Valid bit numbers    */
   /* range from 0 to 31 and it is the users responsibility to ensure   */
   /* that the value provided is valid.                                 */
#define QAPI_BLE_SET_L2CAP_EXTENDED_FEATURE_MASK_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* resetting of L2CAP Extended Feature Bits in the Extended Feature  */
   /* Mask.  This MACRO accepts as input the Extended Feature Mask      */
   /* variable (of type qapi_BLE_L2CAP_Extended_Feature_Mask_t) as the  */
   /* first parameter, and the bit number to reset.  Valid bit numbers  */
   /* range from 0 to 31 and it is the users responsibility to ensure   */
   /* that the value provided is valid.                                 */
#define QAPI_BLE_CLEAR_L2CAP_EXTENDED_FEATURE_MASK_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing the state of L2CAP Extended Feature Bits in the Extended  */
   /* Feature Mask.  This MACRO accepts as input the Extended Feature   */
   /* Mask variable (of type qapi_BLE_L2CAP_Extended_Feature_Mask_t) as */
   /* the first parameter, and the bit number to test.  Valid bit       */
   /* numbers range from 0 to 31 and it is the users responsibility to  */
   /* ensure that the value provided is valid.  This MACRO returns a    */
   /* boolean result as the test result.                                */
#define QAPI_BLE_TEST_L2CAP_EXTENDED_FEATURE_MASK_BIT(_x, _y) \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following type declaration represents the structure of an     */
   /* L2CAP Fixed Channels Supported Event Mask.  In Memory, the        */
   /* structure will represent a 64 bit (8 octet) value that assigns Bit*/
   /* 0 to Bit 63 from left to right.                                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_L2CAP_Fixed_Channels_Supported_Mask_s
{
   uint8_t Fixed_Channels_Supported_Mask0;
   uint8_t Fixed_Channels_Supported_Mask1;
   uint8_t Fixed_Channels_Supported_Mask2;
   uint8_t Fixed_Channels_Supported_Mask3;
   uint8_t Fixed_Channels_Supported_Mask4;
   uint8_t Fixed_Channels_Supported_Mask5;
   uint8_t Fixed_Channels_Supported_Mask6;
   uint8_t Fixed_Channels_Supported_Mask7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_L2CAP_Fixed_Channels_Supported_Mask_t;

#define QAPI_BLE_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK_SIZE     (sizeof(qapi_BLE_L2CAP_Fixed_Channels_Supported_Mask_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified L2CAP Fixed Channels    */
   /* Supported Mask variable.  Extreme care must be taken when using   */
   /* this function to manually assign values to this structure.  The   */
   /* data is saved in a format where Mask 0 corresponds to octet 0 and */
   /* Mask 7 corresponds to octet 7.  Each octet is arranged so that the*/
   /* left most bit of the octet contains the LSB of the value.  The    */
   /* first parameter is the Supported Channels Mask variable (of type  */
   /* Fixed_Channels_Supported_Mask_t) to assign, and the next eight    */
   /* parameters are the Individual Supported Channel Mask Byte values  */
   /* to assign to the variable.                                        */
#define QAPI_BLE_ASSIGN_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK(_dest, _a, _b, _c, _d, _e, _f, _g, _h)  \
{                                                                                          \
   (_dest).Fixed_Channels_Supported_Mask0 = (_h);                                          \
   (_dest).Fixed_Channels_Supported_Mask1 = (_g);                                          \
   (_dest).Fixed_Channels_Supported_Mask2 = (_f);                                          \
   (_dest).Fixed_Channels_Supported_Mask3 = (_e);                                          \
   (_dest).Fixed_Channels_Supported_Mask4 = (_d);                                          \
   (_dest).Fixed_Channels_Supported_Mask5 = (_c);                                          \
   (_dest).Fixed_Channels_Supported_Mask6 = (_b);                                          \
   (_dest).Fixed_Channels_Supported_Mask7 = (_a);                                          \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_L2CAP_Fixed_Channels_Supported_t       */
   /* variables.  This MACRO only returns whether the two variables are */
   /* equal (MACRO returns boolean result) NOT less than/greater than.  */
#define QAPI_BLE_COMPARE_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK(_x, _y)                        \
(                                                                                  \
   ((_x).Fixed_Channels_Supported_Mask0 == (_y).Fixed_Channels_Supported_Mask0) && \
   ((_x).Fixed_Channels_Supported_Mask1 == (_y).Fixed_Channels_Supported_Mask1) && \
   ((_x).Fixed_Channels_Supported_Mask2 == (_y).Fixed_Channels_Supported_Mask2) && \
   ((_x).Fixed_Channels_Supported_Mask3 == (_y).Fixed_Channels_Supported_Mask3) && \
   ((_x).Fixed_Channels_Supported_Mask4 == (_y).Fixed_Channels_Supported_Mask4) && \
   ((_x).Fixed_Channels_Supported_Mask5 == (_y).Fixed_Channels_Supported_Mask5) && \
   ((_x).Fixed_Channels_Supported_Mask6 == (_y).Fixed_Channels_Supported_Mask6) && \
   ((_x).Fixed_Channels_Supported_Mask7 == (_y).Fixed_Channels_Supported_Mask7)    \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of Bits in the qapi_BLE_L2CAP_Fixed_Channels_Supported_t  */
   /* Mask.  This MACRO accepts as input the Supported Channels Mask    */
   /* variable (of type L2CAP_Fixed_Channels_Supported_t) as the first  */
   /* parameter, and the bit number to set.  Valid bit numbers range    */
   /* from 0 to 63 and it is the users responsibility to ensure that the*/
   /* value provided is valid.                                          */
#define QAPI_BLE_SET_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* resetting of L2CAP Extended Feature Bits in the L2CAP Extended    */
   /* Feature Mask.  This MACRO accepts as input the L2CAP Extended     */
   /* Feature Mask variable (of type                                    */
   /* qapi_BLE_L2CAP_Extended_Feature_Mask_t) as the first parameter,   */
   /* and the bit number to reset.  Valid bit numbers range from 0 to 31*/
   /* and it is the users responsibility to ensure that the value       */
   /* provided is valid.                                                */
#define QAPI_BLE_CLEAR_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= ~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing the state of L2CAP Extended Feature Bits in the L2CAP     */
   /* Extended Feature Mask.  This MACRO accepts as input the L2CAP     */
   /* Extended Feature Mask variable (of type                           */
   /* qapi_BLE_L2CAP_Extended_Feature_Mask_t) as the first parameter,   */
   /* and the bit number to test.  Valid bit numbers range from 0 to 31 */
   /* and it is the users responsibility to ensure that the value       */
   /* provided is valid.  This MACRO returns a boolean result as the    */
   /* test result.                                                      */
#define QAPI_BLE_TEST_L2CAP_FIXED_CHANNELS_SUPPORTED_MASK_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (1 << ((_y)%(sizeof(uint8_t)*8))))

   /* UUID Types/MACRO definitions.                                     */
   /* * NOTE * Two types of UUID MACRO's exist: - SDP UUID Types -      */
   /*          Bluetooth UUID Types The differences between the two are */
   /*          the way they are stored in the type itself.  The SDP UUID*/
   /*          Type MACRO's store the actual UUID value in Big Endian   */
   /*          format, whereas the Bluetooth UUID Type MACRO's store the*/
   /*          actual UUID value in Little Endian format.  The same     */
   /*          container type is used for both (qapi_BLE_UUID_128_t,    */
   /*          qapi_BLE_UUID_16_t, or qapi_BLE_UUID_32_t), however.     */
   /* * NOTE * Earlier versions of Bluetopia ONLY stored the UUID types */
   /*          in Big Endian format and used undecorated MACRO names.   */
   /*          These MACRO's were named: ASSIGN_UUID_128()              */
   /*          ASSIGN_UUID_16() ASSIGN_UUID_32()                        */
   /*          ASSIGN_UUID_16_TO_UUID_128() ASSIGN_UUID_32_TO_UUID_128()*/
   /*          All of the above MACRO's have been deprecated and        */
   /*          replaced with a MACRO that specified either SDP or       */
   /*          BLUETOOTH in the name (e.g.  ASSIGN_UUID_128() has been  */
   /*          replaced with QAPI_BLE_ASSIGN_SDP_UUID_128() or          */
   /*          QAPI_BLE_ASSIGN_BLUETOOTH_UUID_128()) for consistency.   */

   /* The following type declaration represents the structure of a      */
   /* single 128 Bit Universally Unique Identifier (UUID).              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_UUID_128_s
{
   uint8_t UUID_Byte0;
   uint8_t UUID_Byte1;
   uint8_t UUID_Byte2;
   uint8_t UUID_Byte3;
   uint8_t UUID_Byte4;
   uint8_t UUID_Byte5;
   uint8_t UUID_Byte6;
   uint8_t UUID_Byte7;
   uint8_t UUID_Byte8;
   uint8_t UUID_Byte9;
   uint8_t UUID_Byte10;
   uint8_t UUID_Byte11;
   uint8_t UUID_Byte12;
   uint8_t UUID_Byte13;
   uint8_t UUID_Byte14;
   uint8_t UUID_Byte15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_UUID_128_t;

#define QAPI_BLE_UUID_128_SIZE                           (sizeof(qapi_BLE_UUID_128_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, and they are NOT assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_128_t) to assign, and */
   /* the next 16 parameters are the Individual UUID Byte values to     */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_SDP_UUID_128(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                                  \
   (_dest).UUID_Byte0  = (_a); (_dest).UUID_Byte1  = (_b); (_dest).UUID_Byte2  = (_c);             \
   (_dest).UUID_Byte3  = (_d); (_dest).UUID_Byte4  = (_e); (_dest).UUID_Byte5  = (_f);             \
   (_dest).UUID_Byte6  = (_g); (_dest).UUID_Byte7  = (_h); (_dest).UUID_Byte8  = (_i);             \
   (_dest).UUID_Byte9  = (_j); (_dest).UUID_Byte10 = (_k); (_dest).UUID_Byte11 = (_l);             \
   (_dest).UUID_Byte12 = (_m); (_dest).UUID_Byte13 = (_n); (_dest).UUID_Byte14 = (_o);             \
   (_dest).UUID_Byte15 = (_p);                                                                     \
}

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, however they ARE assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_128_t) to assign, and */
   /* the next 16 parameters are the Individual UUID Byte values to     */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_BLUETOOTH_UUID_128(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                                        \
   (_dest).UUID_Byte0  = (_p); (_dest).UUID_Byte1  = (_o); (_dest).UUID_Byte2  = (_n);                   \
   (_dest).UUID_Byte3  = (_m); (_dest).UUID_Byte4  = (_l); (_dest).UUID_Byte5  = (_k);                   \
   (_dest).UUID_Byte6  = (_j); (_dest).UUID_Byte7  = (_i); (_dest).UUID_Byte8  = (_h);                   \
   (_dest).UUID_Byte9  = (_g); (_dest).UUID_Byte10 = (_f); (_dest).UUID_Byte11 = (_e);                   \
   (_dest).UUID_Byte12 = (_d); (_dest).UUID_Byte13 = (_c); (_dest).UUID_Byte14 = (_b);                   \
   (_dest).UUID_Byte15 = (_a);                                                                           \
}

   /* The following MACRO is a utility MACRO that exists to convert an  */
   /* SDP 128 bit UUID (of type qapi_BLE_UUID_128_t) to a Bluetooth 128 */
   /* bit UUID (of type qapi_BLE_UUID_128_t).  The first parameter of   */
   /* this MACRO is the 128 bit Bluetooth UUID variable (of type        */
   /* qapi_BLE_UUID_128_t) that will receive the converted value.  The  */
   /* second parameter is the 128 bit SDP UUID variable (of type        */
   /* qapi_BLE_UUID_128_t) to convert.                                  */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_SDP_UUID_128_TO_BLUETOOTH_UUID_128(_dest, _src)                                                                  \
{                                                                                                                                \
   (_dest).UUID_Byte0  = (_src).UUID_Byte15; (_dest).UUID_Byte1  = (_src).UUID_Byte14; (_dest).UUID_Byte2  = (_src).UUID_Byte13; \
   (_dest).UUID_Byte3  = (_src).UUID_Byte12; (_dest).UUID_Byte4  = (_src).UUID_Byte11; (_dest).UUID_Byte5  = (_src).UUID_Byte10; \
   (_dest).UUID_Byte6  = (_src).UUID_Byte9;  (_dest).UUID_Byte7  = (_src).UUID_Byte8;  (_dest).UUID_Byte8  = (_src).UUID_Byte7;  \
   (_dest).UUID_Byte9  = (_src).UUID_Byte6;  (_dest).UUID_Byte10 = (_src).UUID_Byte5;  (_dest).UUID_Byte11 = (_src).UUID_Byte4;  \
   (_dest).UUID_Byte12 = (_src).UUID_Byte3;  (_dest).UUID_Byte13 = (_src).UUID_Byte2;  (_dest).UUID_Byte14 = (_src).UUID_Byte1;  \
   (_dest).UUID_Byte15 = (_src).UUID_Byte0;                                                                                      \
}

   /* The following MACRO is a utility MACRO that exists to convert a   */
   /* Bluetooth 128 bit UUID (of type qapi_BLE_UUID_128_t) to an SDP 128*/
   /* bit UUID (of type qapi_BLE_UUID_128_t).  The first parameter of   */
   /* this MACRO is the 128 bit SDP UUID variable (of type              */
   /* qapi_BLE_UUID_128_t) that will receive the converted value.  The  */
   /* second parameter is the 128 bit Bluetooth UUID (of type           */
   /* qapi_BLE_UUID_128_t) to convert.                                  */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_BLUETOOTH_UUID_128_TO_SDP_UUID_128(_dest, _src)                                                                  \
{                                                                                                                                \
   (_dest).UUID_Byte0  = (_src).UUID_Byte15; (_dest).UUID_Byte1  = (_src).UUID_Byte14; (_dest).UUID_Byte2  = (_src).UUID_Byte13; \
   (_dest).UUID_Byte3  = (_src).UUID_Byte12; (_dest).UUID_Byte4  = (_src).UUID_Byte11; (_dest).UUID_Byte5  = (_src).UUID_Byte10; \
   (_dest).UUID_Byte6  = (_src).UUID_Byte9;  (_dest).UUID_Byte7  = (_src).UUID_Byte8;  (_dest).UUID_Byte8  = (_src).UUID_Byte7;  \
   (_dest).UUID_Byte9  = (_src).UUID_Byte6;  (_dest).UUID_Byte10 = (_src).UUID_Byte5;  (_dest).UUID_Byte11 = (_src).UUID_Byte4;  \
   (_dest).UUID_Byte12 = (_src).UUID_Byte3;  (_dest).UUID_Byte13 = (_src).UUID_Byte2;  (_dest).UUID_Byte14 = (_src).UUID_Byte1;  \
   (_dest).UUID_Byte15 = (_src).UUID_Byte0;                                                                                      \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_UUID_128_t variables.  This MACRO only */
   /* returns whether the two qapi_BLE_UUID_128_t variables are equal   */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_UUID_128_t */
   /* and represent the qapi_BLE_UUID_128_t variables to compare.       */
#define QAPI_BLE_COMPARE_UUID_128(_x, _y)                                                                                                 \
(                                                                                                                                \
   ((_x).UUID_Byte0  == (_y).UUID_Byte0)  && ((_x).UUID_Byte1  == (_y).UUID_Byte1)  && ((_x).UUID_Byte2  == (_y).UUID_Byte2)  && \
   ((_x).UUID_Byte3  == (_y).UUID_Byte3)  && ((_x).UUID_Byte4  == (_y).UUID_Byte4)  && ((_x).UUID_Byte5  == (_y).UUID_Byte5)  && \
   ((_x).UUID_Byte6  == (_y).UUID_Byte6)  && ((_x).UUID_Byte7  == (_y).UUID_Byte7)  && ((_x).UUID_Byte8  == (_y).UUID_Byte8)  && \
   ((_x).UUID_Byte9  == (_y).UUID_Byte9)  && ((_x).UUID_Byte10 == (_y).UUID_Byte10) && ((_x).UUID_Byte11 == (_y).UUID_Byte11) && \
   ((_x).UUID_Byte12 == (_y).UUID_Byte12) && ((_x).UUID_Byte13 == (_y).UUID_Byte13) && ((_x).UUID_Byte14 == (_y).UUID_Byte14) && \
   ((_x).UUID_Byte15 == (_y).UUID_Byte15)                                                                                        \
)

   /* The following type declaration represents the structure of a      */
   /* single 16 Bit Universally Unique Identifier (UUID).               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_UUID_16_s
{
   uint8_t UUID_Byte0;
   uint8_t UUID_Byte1;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_UUID_16_t;

#define QAPI_BLE_UUID_16_SIZE                            (sizeof(qapi_BLE_UUID_16_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, and they are NOT assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_16_t) to assign, and  */
   /* the next 2 parameters are the Individual UUID Byte values to      */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_SDP_UUID_16(_dest, _a, _b)                  \
{                                                          \
   (_dest).UUID_Byte0  = (_a); (_dest).UUID_Byte1  = (_b); \
}

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, however they ARE assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_16_t) to assign, and  */
   /* the next 2 parameters are the Individual UUID Byte values to      */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16(_dest, _a, _b)            \
{                                                          \
   (_dest).UUID_Byte0  = (_b); (_dest).UUID_Byte1  = (_a); \
}

   /* The following MACRO is a utility MACRO that exists to assign a 16 */
   /* Bit UUID to the specified 128 BIT UUID.  The 16 Bit UUID is first */
   /* expanded to a 32 Bit UUID, then the Most Significant 32 Bits of   */
   /* the specified 128 Bit UUID are changed to the newly defined 32 Bit*/
   /* UUID.  The Bytes in the 128 Bit UUID are NOT in Little Endian     */
   /* Format.  The first parameter is the 128 Bit UUID variable (of type*/
   /* qapi_BLE_UUID_128_t) to receive the 16 to 32 Bit UUID Value into, */
   /* and the second parameter is the 16 Bit UUID variable (of type     */
   /* qapi_BLE_UUID_16_t) to extend to a 32 Bit UUID, and then assign to*/
   /* the specified 128 Bit UUID.                                       */
#define QAPI_BLE_ASSIGN_SDP_UUID_16_TO_SDP_UUID_128(_dest, _src)                             \
{                                                                                   \
   (_dest).UUID_Byte0 = 0;                  (_dest).UUID_Byte1 = 0;                 \
   (_dest).UUID_Byte2 = (_src).UUID_Byte0;  (_dest).UUID_Byte3 = (_src).UUID_Byte1; \
}

   /* The following MACRO is a utility MACRO that exists to assign a 16 */
   /* Bit UUID to the specified 128 BIT UUID.  The 16 Bit UUID is first */
   /* expanded to a 32 Bit UUID, then the Least Significant 32 Bits of  */
   /* the specified 128 Bit UUID are changed to the newly defined 32 Bit*/
   /* UUID.  The Bytes in the 128 Bit UUID ARE in Little Endian Format. */
   /* The first parameter is the 128 Bit UUID variable (of type         */
   /* qapi_BLE_UUID_128_t) to receive the 16 to 32 Bit UUID Value into, */
   /* and the second parameter is the 16 Bit UUID variable (of type     */
   /* qapi_BLE_UUID_16_t) to extend to a 32 Bit UUID, and then assign to*/
   /* the specified 128 Bit UUID.                                       */
#define QAPI_BLE_ASSIGN_BLUETOOTH_UUID_16_TO_BLUETOOTH_UUID_128(_dest, _src)                   \
{                                                                                     \
   (_dest).UUID_Byte12 = (_src).UUID_Byte0;  (_dest).UUID_Byte13 = (_src).UUID_Byte1; \
   (_dest).UUID_Byte14 = 0;                  (_dest).UUID_Byte15 = 0;                 \
}

   /* The following MACRO is a utility MACRO that exists to convert an  */
   /* SDP 16 bit UUID (of type qapi_BLE_UUID_16_t) to a Bluetooth 16 bit*/
   /* UUID (of type qapi_BLE_UUID_16_t).  The first parameter of this   */
   /* MACRO is the 16 bit Bluetooth UUID variable (of type              */
   /* qapi_BLE_UUID_16_t) that will receive the converted value.  The   */
   /* second parameter is the 16 bit SDP UUID (of type                  */
   /* qapi_BLE_UUID_16_t) to convert.                                   */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_SDP_UUID_16_TO_BLUETOOTH_UUID_16(_dest, _src)                      \
{                                                                                  \
   (_dest).UUID_Byte0 = (_src).UUID_Byte1; (_dest).UUID_Byte1 = (_src).UUID_Byte0; \
}

   /* The following MACRO is a utility MACRO that exists to convert a   */
   /* Bluetooth 16 bit UUID (of type qapi_BLE_UUID_16_t) to an SDP 16   */
   /* bit UUID (of type qapi_BLE_UUID_16_t).  The first parameter of    */
   /* this MACRO is the 16 bit SDP UUID variable (of type               */
   /* qapi_BLE_UUID_16_t) that will receive the converted value.  The   */
   /* second parameter is the 16 bit Bluetooth UUID (of type            */
   /* qapi_BLE_UUID_16_t) to convert.                                   */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_BLUETOOTH_UUID_16_TO_SDP_UUID_16(_dest, _src)                      \
{                                                                                  \
   (_dest).UUID_Byte0 = (_src).UUID_Byte1; (_dest).UUID_Byte1 = (_src).UUID_Byte0; \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_UUID_16_t variables.  This MACRO only  */
   /* returns whether the two qapi_BLE_UUID_16_t variables are equal    */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_UUID_16_t  */
   /* and represent the qapi_BLE_UUID_16_t variables to compare.        */
#define QAPI_BLE_COMPARE_UUID_16(_x, _y)                                                    \
(                                                                                  \
   ((_x).UUID_Byte0  == (_y).UUID_Byte0)  && ((_x).UUID_Byte1  == (_y).UUID_Byte1) \
)

   /* The following type declaration represents the structure of a      */
   /* single 32 Bit Universally Unique Identifier (UUID).               */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_UUID_32_s
{
   uint8_t UUID_Byte0;
   uint8_t UUID_Byte1;
   uint8_t UUID_Byte2;
   uint8_t UUID_Byte3;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_UUID_32_t;

#define QAPI_BLE_UUID_32_SIZE                            (sizeof(qapi_BLE_UUID_32_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, and they are NOT assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_32_t) to assign, and  */
   /* the next 4 parameters are the Individual UUID Byte values to      */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_SDP_UUID_32(_dest, _a, _b, _c, _d)         \
{                                                         \
   (_dest).UUID_Byte0  = (_a); (_dest).UUID_Byte1 = (_b); \
   (_dest).UUID_Byte2  = (_c); (_dest).UUID_Byte3 = (_d); \
}

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified UUID variable.  The     */
   /* Bytes are NOT in Little Endian Format, however they ARE assigned  */
   /* to the UUID variable in Little Endian Format.  The first parameter*/
   /* is the UUID variable (of type qapi_BLE_UUID_32_t) to assign, and  */
   /* the next 4 parameters are the Individual UUID Byte values to      */
   /* assign to the UUID variable.                                      */
#define QAPI_BLE_ASSIGN_BLUETOOTH_UUID_32(_dest, _a, _b, _c, _d)   \
{                                                         \
   (_dest).UUID_Byte0  = (_d); (_dest).UUID_Byte1 = (_c); \
   (_dest).UUID_Byte2  = (_b); (_dest).UUID_Byte3 = (_a); \
}

   /* The following MACRO is a utility MACRO that exists to assign a 32 */
   /* Bit UUID to the specified 128 BIT UUID.  The 32 Bit UUID is       */
   /* assigned to the Most Significant 32 Bits of the specified 128 Bit */
   /* UUID.  The Bytes in the 128 Bit UUID are NOT in Little Endian     */
   /* Format.  The first parameter is the 128 Bit UUID variable (of type*/
   /* qapi_BLE_UUID_128_t) to receive the 32 Bit UUID Value into, and   */
   /* the second parameter is the 32 Bit UUID variable (of type         */
   /* qapi_BLE_UUID_32_t) to assign to the specified 128 Bit UUID.      */
#define QAPI_BLE_ASSIGN_SDP_UUID_32_TO_SDP_UUID_128(_dest, _src)                             \
{                                                                                   \
   (_dest).UUID_Byte0 = (_src).UUID_Byte0;  (_dest).UUID_Byte1 = (_src).UUID_Byte1; \
   (_dest).UUID_Byte2 = (_src).UUID_Byte2;  (_dest).UUID_Byte3 = (_src).UUID_Byte3; \
}

   /* The following MACRO is a utility MACRO that exists to assign a 32 */
   /* Bit UUID to the specified 128 BIT UUID.  The 32 Bit UUID is       */
   /* assigned to the Least Significant 32 Bits of the specified 128 Bit*/
   /* UUID.  The Bytes in the 128 Bit UUID ARE in Little Endian Format. */
   /* The first parameter is the 128 Bit UUID variable (of type         */
   /* qapi_BLE_UUID_128_t) to receive the 32 Bit UUID Value into, and   */
   /* the second parameter is the 32 Bit UUID variable (of type         */
   /* qapi_BLE_UUID_32_t) to assign to the specified 128 Bit UUID.      */
#define QAPI_BLE_ASSIGN_BLUETOOTH_UUID_32_TO_BLUETOOTH_UUID_128(_dest, _src)                 \
{                                                                                   \
   (_dest).UUID_Byte0 = (_src).UUID_Byte0;  (_dest).UUID_Byte1 = (_src).UUID_Byte1; \
   (_dest).UUID_Byte2 = (_src).UUID_Byte2;  (_dest).UUID_Byte3 = (_src).UUID_Byte3; \
}

   /* The following MACRO is a utility MACRO that exists to convert an  */
   /* SDP 32 bit UUID (of type qapi_BLE_UUID_32_t) to a Bluetooth 32 bit*/
   /* UUID (of type qapi_BLE_UUID_32_t).  The first parameter of this   */
   /* MACRO is the 32 bit Bluetooth UUID variable (of type              */
   /* qapi_BLE_UUID_32_t) that will receive the converted value.  The   */
   /* second parameter is the 32 bit SDP UUID (of type                  */
   /* qapi_BLE_UUID_32_t) to convert.                                   */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_SDP_UUID_32_TO_BLUETOOTH_UUID_32(_dest, _src)                      \
{                                                                                  \
   (_dest).UUID_Byte0 = (_src).UUID_Byte3; (_dest).UUID_Byte1 = (_src).UUID_Byte2; \
   (_dest).UUID_Byte2 = (_src).UUID_Byte1; (_dest).UUID_Byte3 = (_src).UUID_Byte0; \
}

   /* The following MACRO is a utility MACRO that exists to convert a   */
   /* Bluetooth 32 bit UUID (of type qapi_BLE_UUID_32_t) to an SDP 32   */
   /* bit UUID (of type qapi_BLE_UUID_32_t).  The first parameter of    */
   /* this MACRO is the 32 bit SDP UUID (of type qapi_BLE_UUID_32_t)    */
   /* that will receive the converted value.  The second parameter is   */
   /* the 32 bit Bluetooth UUID variable (of type qapi_BLE_UUID_32_t) to*/
   /* convert.                                                          */
   /* * NOTE * See Notes above about the difference between SDP and     */
   /*          Bluetooth UUID's (the endian-ness of each type).         */
#define QAPI_BLE_CONVERT_BLUETOOTH_UUID_32_TO_SDP_UUID_32(_dest, _src)                      \
{                                                                                  \
   (_dest).UUID_Byte0 = (_src).UUID_Byte3; (_dest).UUID_Byte1 = (_src).UUID_Byte2; \
   (_dest).UUID_Byte2 = (_src).UUID_Byte1; (_dest).UUID_Byte3 = (_src).UUID_Byte0; \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_UUID_32_t variables.  This MACRO only  */
   /* returns whether the two qapi_BLE_UUID_32_t variables are equal    */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_UUID_32_t  */
   /* and represent the qapi_BLE_UUID_32_t variables to compare.        */
#define QAPI_BLE_COMPARE_UUID_32(_x, _y)                                                       \
(                                                                                     \
   ((_x).UUID_Byte0  == (_y).UUID_Byte0)  && ((_x).UUID_Byte1  == (_y).UUID_Byte1) && \
   ((_x).UUID_Byte2  == (_y).UUID_Byte2)  && ((_x).UUID_Byte3  == (_y).UUID_Byte3)    \
)

   /* The following type declaration represents the structure of a      */
   /* single Simple Pairing Hash, C used for OOB mechanism of Secure    */
   /* Simple Pairing (Version 2.1).                                     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Simple_Pairing_Hash_s
{
   uint8_t Pairing_Hash0;
   uint8_t Pairing_Hash1;
   uint8_t Pairing_Hash2;
   uint8_t Pairing_Hash3;
   uint8_t Pairing_Hash4;
   uint8_t Pairing_Hash5;
   uint8_t Pairing_Hash6;
   uint8_t Pairing_Hash7;
   uint8_t Pairing_Hash8;
   uint8_t Pairing_Hash9;
   uint8_t Pairing_Hash10;
   uint8_t Pairing_Hash11;
   uint8_t Pairing_Hash12;
   uint8_t Pairing_Hash13;
   uint8_t Pairing_Hash14;
   uint8_t Pairing_Hash15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Simple_Pairing_Hash_t;

#define QAPI_BLE_SIMPLE_PAIRING_HASH_SIZE                (sizeof(qapi_BLE_Simple_Pairing_Hash_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Pairing Hash, C,        */
   /* variable.  The Bytes are NOT in Little Endian Format, however,    */
   /* they are assigned to the Pairing Hash variable in Little Endian   */
   /* Format.  The first parameter is the Simple Pairing Hash variable  */
   /* (of type qapi_BLE_Simple_Pairing_Hash_t) to assign, and the next  */
   /* 16 parameters are the Individual Pairing Hash Byte values to      */
   /* assign to the Pairing variable.                                   */
#define QAPI_BLE_ASSIGN_PAIRING_HASH(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                              \
   (_dest).Pairing_Hash0  = (_p); (_dest).Pairing_Hash1  = (_o); (_dest).Pairing_Hash2  = (_n);            \
   (_dest).Pairing_Hash3  = (_m); (_dest).Pairing_Hash4  = (_l); (_dest).Pairing_Hash5  = (_k);            \
   (_dest).Pairing_Hash6  = (_j); (_dest).Pairing_Hash7  = (_i); (_dest).Pairing_Hash8  = (_h);            \
   (_dest).Pairing_Hash9  = (_g); (_dest).Pairing_Hash10 = (_f); (_dest).Pairing_Hash11 = (_e);            \
   (_dest).Pairing_Hash12 = (_d); (_dest).Pairing_Hash13 = (_c); (_dest).Pairing_Hash14 = (_b);            \
   (_dest).Pairing_Hash15 = (_a);                                                                  \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Simple_Pairing_Hash_t variables.  This */
   /* MACRO only returns whether the two qapi_BLE_Simple_Pairing_Hash_t */
   /* variables are equal (MACRO returns boolean result) NOT less       */
   /* than/greater than.  The two parameters to this MACRO are both of  */
   /* type qapi_BLE_Simple_Pairing_Hash_t and represent the             */
   /* qapi_BLE_Simple_Pairing_Hash_t variables to compare.              */
#define QAPI_BLE_COMPARE_PAIRING_HASH(_x, _y)                                                                                           \
(                                                                                                                          \
   ((_x).Pairing_Hash0  == (_y).Pairing_Hash0)  && ((_x).Pairing_Hash1  == (_y).Pairing_Hash1)  && ((_x).Pairing_Hash2  == (_y).Pairing_Hash2)  && \
   ((_x).Pairing_Hash3  == (_y).Pairing_Hash3)  && ((_x).Pairing_Hash4  == (_y).Pairing_Hash4)  && ((_x).Pairing_Hash5  == (_y).Pairing_Hash5)  && \
   ((_x).Pairing_Hash6  == (_y).Pairing_Hash6)  && ((_x).Pairing_Hash7  == (_y).Pairing_Hash7)  && ((_x).Pairing_Hash8  == (_y).Pairing_Hash8)  && \
   ((_x).Pairing_Hash9  == (_y).Pairing_Hash9)  && ((_x).Pairing_Hash10 == (_y).Pairing_Hash10) && ((_x).Pairing_Hash11 == (_y).Pairing_Hash11) && \
   ((_x).Pairing_Hash12 == (_y).Pairing_Hash12) && ((_x).Pairing_Hash13 == (_y).Pairing_Hash13) && ((_x).Pairing_Hash14 == (_y).Pairing_Hash14) && \
   ((_x).Pairing_Hash15 == (_y).Pairing_Hash15)                                                                                    \
)

   /* The following type declaration represents the structure of a      */
   /* single Simple Pairing Randomizer, R used for OOB mechanism of     */
   /* Secure Simple Pairing (Version 2.1).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Simple_Pairing_Randomizer_s
{
   uint8_t Pairing_Randomizer0;
   uint8_t Pairing_Randomizer1;
   uint8_t Pairing_Randomizer2;
   uint8_t Pairing_Randomizer3;
   uint8_t Pairing_Randomizer4;
   uint8_t Pairing_Randomizer5;
   uint8_t Pairing_Randomizer6;
   uint8_t Pairing_Randomizer7;
   uint8_t Pairing_Randomizer8;
   uint8_t Pairing_Randomizer9;
   uint8_t Pairing_Randomizer10;
   uint8_t Pairing_Randomizer11;
   uint8_t Pairing_Randomizer12;
   uint8_t Pairing_Randomizer13;
   uint8_t Pairing_Randomizer14;
   uint8_t Pairing_Randomizer15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Simple_Pairing_Randomizer_t;

#define QAPI_BLE_SIMPLE_PAIRING_RANDOMIZER_SIZE          (sizeof(qapi_BLE_Simple_Pairing_Randomizer_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Pairing Randomizer, R,  */
   /* variable.  The Bytes are NOT in Little Endian Format, however,    */
   /* they are assigned to the Pairing Randomizer Key variable in Little*/
   /* Endian Format.  The first parameter is the Pairing Randomizer     */
   /* variable (of type qapi_BLE_Simple_Pairing_Randomizer_t) to assign,*/
   /* and the next 16 parameters are the Individual Pairing Randomizer  */
   /* Byte values to assign to the Pairing Randomizer variable.         */
#define QAPI_BLE_ASSIGN_PAIRING_RANDOMIZER(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                              \
   (_dest).Pairing_Randomizer0  = (_p); (_dest).Pairing_Randomizer1  = (_o); (_dest).Pairing_Randomizer2  = (_n);            \
   (_dest).Pairing_Randomizer3  = (_m); (_dest).Pairing_Randomizer4  = (_l); (_dest).Pairing_Randomizer5  = (_k);            \
   (_dest).Pairing_Randomizer6  = (_j); (_dest).Pairing_Randomizer7  = (_i); (_dest).Pairing_Randomizer8  = (_h);            \
   (_dest).Pairing_Randomizer9  = (_g); (_dest).Pairing_Randomizer10 = (_f); (_dest).Pairing_Randomizer11 = (_e);            \
   (_dest).Pairing_Randomizer12 = (_d); (_dest).Pairing_Randomizer13 = (_c); (_dest).Pairing_Randomizer14 = (_b);            \
   (_dest).Pairing_Randomizer15 = (_a);                                                                  \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Simple_Pairing_Randomizer_t variables. */
   /* This MACRO only returns whether the two                           */
   /* qapi_BLE_Simple_Pairing_Randomizer_t variables are equal (MACRO   */
   /* returns boolean result) NOT less than/ greater than.  The two     */
   /* parameters to this MACRO are both of type                         */
   /* qapi_BLE_Simple_Pairing_Randomizer_t and represent the            */
   /* qapi_BLE_Simple_Pairing_Randomizer_t variables to compare.        */
#define QAPI_BLE_COMPARE_PAIRING_RANDOMIZER(_x, _y)                                                                                           \
(                                                                                                                          \
   ((_x).Pairing_Randomizer0  == (_y).Pairing_Randomizer0)  && ((_x).Pairing_Randomizer1  == (_y).Pairing_Randomizer1)  && ((_x).Pairing_Randomizer2  == (_y).Pairing_Randomizer2)  && \
   ((_x).Pairing_Randomizer3  == (_y).Pairing_Randomizer3)  && ((_x).Pairing_Randomizer4  == (_y).Pairing_Randomizer4)  && ((_x).Pairing_Randomizer5  == (_y).Pairing_Randomizer5)  && \
   ((_x).Pairing_Randomizer6  == (_y).Pairing_Randomizer6)  && ((_x).Pairing_Randomizer7  == (_y).Pairing_Randomizer7)  && ((_x).Pairing_Randomizer8  == (_y).Pairing_Randomizer8)  && \
   ((_x).Pairing_Randomizer9  == (_y).Pairing_Randomizer9)  && ((_x).Pairing_Randomizer10 == (_y).Pairing_Randomizer10) && ((_x).Pairing_Randomizer11 == (_y).Pairing_Randomizer11) && \
   ((_x).Pairing_Randomizer12 == (_y).Pairing_Randomizer12) && ((_x).Pairing_Randomizer13 == (_y).Pairing_Randomizer13) && ((_x).Pairing_Randomizer14 == (_y).Pairing_Randomizer14) && \
   ((_x).Pairing_Randomizer15 == (_y).Pairing_Randomizer15)                                                                                    \
)

   /* The following type declaration represents the structure of a LE   */
   /* Features Type (Version 4.0 + LE).                                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_LE_Features_s
{
   uint8_t LE_Features0;
   uint8_t LE_Features1;
   uint8_t LE_Features2;
   uint8_t LE_Features3;
   uint8_t LE_Features4;
   uint8_t LE_Features5;
   uint8_t LE_Features6;
   uint8_t LE_Features7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_LE_Features_t;

#define QAPI_BLE_LE_FEATURES_SIZE                        (sizeof(qapi_BLE_LE_Features_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified LE_Features variable.   */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the LE_Features variable in Little Endian Format.  The*/
   /* first parameter is the LE_Features variable (of type              */
   /* qapi_BLE_LE_Features_t) to assign, and the next eight parameters  */
   /* are the Individual LE_Features Byte values to assign to the       */
   /* variable.                                                         */
#define QAPI_BLE_ASSIGN_LE_FEATURES(_dest, _a, _b, _c, _d, _e, _f, _g, _h) \
{                                                                 \
   (_dest).LE_Features0 = (_h);                                   \
   (_dest).LE_Features1 = (_g);                                   \
   (_dest).LE_Features2 = (_f);                                   \
   (_dest).LE_Features3 = (_e);                                   \
   (_dest).LE_Features4 = (_d);                                   \
   (_dest).LE_Features5 = (_c);                                   \
   (_dest).LE_Features6 = (_b);                                   \
   (_dest).LE_Features7 = (_a);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_LE_Features_t variables.  This MACRO   */
   /* only returns whether the two qapi_BLE_LE_Features_t variables are */
   /* equal (MACRO returns boolean result) NOT less than/greater than.  */
   /* The two parameters to this MACRO are both of type                 */
   /* qapi_BLE_LE_Features_t and represent the qapi_BLE_LE_Features_t   */
   /* variables to compare.                                             */
#define QAPI_BLE_COMPARE_LE_FEATURES(_x, _y)                                                                                                      \
(                                                                                                                                        \
   ((_x).LE_Features0 == (_y).LE_Features0) && ((_x).LE_Features1 == (_y).LE_Features1) && ((_x).LE_Features2  == (_y).LE_Features2)  && \
   ((_x).LE_Features3 == (_y).LE_Features3) && ((_x).LE_Features4 == (_y).LE_Features4) && ((_x).LE_Features5  == (_y).LE_Features5)  && \
   ((_x).LE_Features6 == (_y).LE_Features6) && ((_x).LE_Features7 == (_y).LE_Features7)                                                  \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of LE Features Bits in the LE Features Mask.  This MACRO  */
   /* accepts as input the LE Features Mask variable (of type           */
   /* qapi_BLE_LE_Features_t) as the first parameter, and the bit number*/
   /* to set (LSB is bit number 0).  This MACRO sets the bits in Little */
   /* Endian Format (so bit 0 is physically bit 0 of the first byte of  */
   /* the LE Features Mask structure).                                  */
#define QAPI_BLE_SET_LE_FEATURES_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of LE Features Bits in the LE Features Mask.  This MACRO */
   /* accepts as input the LE Features Mask variable (of type           */
   /* qapi_BLE_LE_Features_t) as the first parameter, and the bit number*/
   /* to clear (LSB is bit number 0).  This MACRO clears the bits in    */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the LE Features Mask structure).                          */
#define QAPI_BLE_CLEAR_LE_FEATURES_BIT(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of LE Features Bits in the LE Features Mask.  This MACRO  */
   /* accepts as input the LE Features Mask variable (of type           */
   /* qapi_BLE_LE_Features_t) as the first parameter, and the bit number*/
   /* to test (LSB is bit number 0).  This MACRO tests the bits in      */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the LE Features Mask structure).  This MACRO returns a    */
   /* boolean result as the test result.                                */
#define QAPI_BLE_TEST_LE_FEATURES_BIT(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the Advertising Data that can be sent/received in  */
   /* advertising packets for a device.                                 */
#define QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE                                31

   /* The following type defines the buffer that is used to write or    */
   /* read the advertising data to be advertised by the local device    */
   /* (Version 4.0 + LE).  The size of this buffer is always fixed.     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Advertising_Data_s
{
   uint8_t Advertising_Data[QAPI_BLE_ADVERTISING_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Advertising_Data_t;

#define QAPI_BLE_ADVERTISING_DATA_SIZE                   (sizeof(qapi_BLE_Advertising_Data_t))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the Extended Advertising Data that can be          */
   /* sent/received in advertising packets for a device.                */
#define QAPI_BLE_EXTENDED_ADVERTISING_DATA_MAXIMUM_SIZE                       252

   /* The following type defines the buffer that is used to write or    */
   /* read the extended advertising data to be advertised by the local  */
   /* device (Version 5.0 + LE). The size of this buffer is always      */
   /* fixed.                                                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Extended_Advertising_Data_s
{
   uint8_t Advertising_Data[QAPI_BLE_EXTENDED_ADVERTISING_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Extended_Advertising_Data_t;

#define QAPI_BLE_EXTENDED_ADVERTISING_DATA_SIZE          (sizeof(qapi_BLE_Extended_Advertising_Data_t))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the Periodic Advertising Data that can be          */
   /* sent/received in advertising packets for a device.                */
#define QAPI_BLE_PERIODIC_ADVERTISING_DATA_MAXIMUM_SIZE                       253

   /* The following type defines the buffer that is used to write or    */
   /* read the periodic advertising data to be advertised by the local  */
   /* device (Version 5.0 + LE). The size of this buffer is always      */
   /* fixed.                                                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Periodic_Advertising_Data_s
{
   uint8_t Advertising_Data[QAPI_BLE_PERIODIC_ADVERTISING_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Periodic_Advertising_Data_t;

#define QAPI_BLE_PERIODIC_ADVERTISING_DATA_SIZE          (sizeof(qapi_BLE_Periodic_Advertising_Data_t))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the Scan Response Data that can be sent/received in*/
   /* scanning packets for a device.                                    */
#define QAPI_BLE_SCAN_RESPONSE_DATA_MAXIMUM_SIZE                              31

   /* The following type defines the buffer that is used to write or    */
   /* read the scan response data to be advertised by the local device  */
   /* (Version 4.0 + LE).  The size of this buffer is always fixed.     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Scan_Response_Data_s
{
   uint8_t Scan_Response_Data[QAPI_BLE_SCAN_RESPONSE_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Scan_Response_Data_t;

#define QAPI_BLE_SCAN_RESPONSE_DATA_SIZE                 (sizeof(qapi_BLE_Scan_Response_Data_t))

   /* The following define determines the maximum fixed size that is    */
   /* used to define the Extended Scan Response Data that can be        */
   /* sent/received in scanning packets for a device.                   */
#define QAPI_BLE_EXTENDED_SCAN_RESPONSE_DATA_MAXIMUM_SIZE                     252

   /* The following type defines the buffer that is used to write or    */
   /* read the Extended scan response data to be advertised by the local*/
   /* device (Version 5.0 + LE). The size of this buffer is always      */
   /* fixed.                                                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Extended_Scan_Response_Data_s
{
   uint8_t Scan_Response_Data[QAPI_BLE_EXTENDED_SCAN_RESPONSE_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Extended_Scan_Response_Data_t;

#define QAPI_BLE_EXTENDED_SCAN_RESPONSE_DATA_SIZE        (sizeof(qapi_BLE_Extended_Scan_Response_Data_t))

   /* The following type declaration represents the structure of an LE  */
   /* Channel Map Type (Version 4.0 + LE).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_LE_Channel_Map_s
{
   qapi_BLE_NonAlignedByte_t LE_Channel_Map0;
   qapi_BLE_NonAlignedByte_t LE_Channel_Map1;
   qapi_BLE_NonAlignedByte_t LE_Channel_Map2;
   qapi_BLE_NonAlignedByte_t LE_Channel_Map3;
   qapi_BLE_NonAlignedByte_t LE_Channel_Map4;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_LE_Channel_Map_t;

#define QAPI_BLE_LE_CHANNEL_MAP_SIZE                     (sizeof(qapi_BLE_LE_Channel_Map_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified LE_Channel_Map variable.*/
   /* The Bytes specified are written directly into the AFH Channel Map */
   /* in the order they are listed.  The first parameter is the         */
   /* LE_Channel_Map variable (of type qapi_BLE_LE_Channel_Map_t) to    */
   /* assign, and the next five parameters are the Individual           */
   /* LE_Channel_Map Byte values to assign to the variable.             */
#define QAPI_BLE_ASSIGN_LE_CHANNEL_MAP(_dest, _a, _b, _c, _d, _e) \
{                                                        \
   (_dest).LE_Channel_Map0 = (_e);                       \
   (_dest).LE_Channel_Map1 = (_d);                       \
   (_dest).LE_Channel_Map2 = (_c);                       \
   (_dest).LE_Channel_Map3 = (_b);                       \
   (_dest).LE_Channel_Map4 = (_a);                       \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_LE_Channel_Map_t variables.  This MACRO*/
   /* only returns whether the two qapi_BLE_LE_Channel_Map_t variables  */
   /* are equal (MACRO returns boolean result) NOT less than/greater    */
   /* than.  The two parameters to this MACRO are both of type          */
   /* qapi_BLE_LE_Channel_Map_t and represent the                       */
   /* qapi_BLE_LE_Channel_Map_t variables to compare.                   */
#define QAPI_BLE_COMPARE_LE_CHANNEL_MAP(_x, _y)                                                                 \
(                                                                                                      \
   ((_x).LE_Channel_Map0 == (_y).LE_Channel_Map0) && ((_x).LE_Channel_Map1 == (_y).LE_Channel_Map1) && \
   ((_x).LE_Channel_Map2 == (_y).LE_Channel_Map2) && ((_x).LE_Channel_Map3 == (_y).LE_Channel_Map3) && \
   ((_x).LE_Channel_Map4 == (_y).LE_Channel_Map4)                                                      \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of LE Channel Map Channel in the LE Channel Map.  This    */
   /* MACRO accepts as input the LE Channel Map variable (of type       */
   /* qapi_BLE_LE_Channel_Map_t) as the first parameter, and the Channel*/
   /* Number to set.                                                    */
#define QAPI_BLE_SET_LE_CHANNEL_MAP_CHANNEL(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of LE Channel Map Channel in the LE Channel Map.  This   */
   /* MACRO accepts as input the LE Channel Map variable (of type       */
   /* qapi_BLE_LE_Channel_Map_t) as the first parameter, and the Channel*/
   /* Number to clear.                                                  */
#define QAPI_BLE_CLEAR_LE_CHANNEL_MAP_CHANNEL(_x, _y) \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of LE Channel Map Channel in the LE Channel Map.  This    */
   /* MACRO accepts as input the LE Channel Map variable (of type       */
   /* qapi_BLE_LE_Channel_Map_t) as the first parameter, and the Channel*/
   /* Number to test.                                                   */
#define QAPI_BLE_TEST_LE_CHANNEL_MAP_CHANNEL(_x, _y)  \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following type declaration represents the structure of a      */
   /* single Encryption Key (Version 4.0 + LE).                         */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Encryption_Key_s
{
   uint8_t Encryption_Key0;
   uint8_t Encryption_Key1;
   uint8_t Encryption_Key2;
   uint8_t Encryption_Key3;
   uint8_t Encryption_Key4;
   uint8_t Encryption_Key5;
   uint8_t Encryption_Key6;
   uint8_t Encryption_Key7;
   uint8_t Encryption_Key8;
   uint8_t Encryption_Key9;
   uint8_t Encryption_Key10;
   uint8_t Encryption_Key11;
   uint8_t Encryption_Key12;
   uint8_t Encryption_Key13;
   uint8_t Encryption_Key14;
   uint8_t Encryption_Key15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Encryption_Key_t;

#define QAPI_BLE_ENCRYPTION_KEY_SIZE                     (sizeof(qapi_BLE_Encryption_Key_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Encryption Key variable.*/
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the Encryption Key variable in Little Endian Format.  */
   /* The first parameter is the Encryption Key variable (of type       */
   /* qapi_BLE_Encryption_Key_t) to assign, and the next 16 parameters  */
   /* are the Individual Encryption Key Byte values to assign to the    */
   /* Encryption Key variable.                                          */
#define QAPI_BLE_ASSIGN_ENCRYPTION_KEY(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p)   \
{                                                                                                      \
   (_dest).Encryption_Key0  = (_p); (_dest).Encryption_Key1  = (_o); (_dest).Encryption_Key2  = (_n);  \
   (_dest).Encryption_Key3  = (_m); (_dest).Encryption_Key4  = (_l); (_dest).Encryption_Key5  = (_k);  \
   (_dest).Encryption_Key6  = (_j); (_dest).Encryption_Key7  = (_i); (_dest).Encryption_Key8  = (_h);  \
   (_dest).Encryption_Key9  = (_g); (_dest).Encryption_Key10 = (_f); (_dest).Encryption_Key11 = (_e);  \
   (_dest).Encryption_Key12 = (_d); (_dest).Encryption_Key13 = (_c); (_dest).Encryption_Key14 = (_b);  \
   (_dest).Encryption_Key15 = (_a);                                                                    \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Encryption_Key_t variables.  This MACRO*/
   /* only returns whether the two qapi_BLE_Encryption_Key_t variables  */
   /* are equal (MACRO returns boolean result) NOT less than/greater    */
   /* than.  The two parameters to this MACRO are both of type          */
   /* qapi_BLE_Encryption_Key_t and represent the                       */
   /* qapi_BLE_Encryption_Key_t variables to compare.                   */
#define QAPI_BLE_COMPARE_ENCRYPTION_KEY(_x, _y)                                                                                                                         \
(                                                                                                                                                              \
   ((_x).Encryption_Key0  == (_y).Encryption_Key0)  && ((_x).Encryption_Key1  == (_y).Encryption_Key1)  && ((_x).Encryption_Key2  == (_y).Encryption_Key2)  && \
   ((_x).Encryption_Key3  == (_y).Encryption_Key3)  && ((_x).Encryption_Key4  == (_y).Encryption_Key4)  && ((_x).Encryption_Key5  == (_y).Encryption_Key5)  && \
   ((_x).Encryption_Key6  == (_y).Encryption_Key6)  && ((_x).Encryption_Key7  == (_y).Encryption_Key7)  && ((_x).Encryption_Key8  == (_y).Encryption_Key8)  && \
   ((_x).Encryption_Key9  == (_y).Encryption_Key9)  && ((_x).Encryption_Key10 == (_y).Encryption_Key10) && ((_x).Encryption_Key11 == (_y).Encryption_Key11) && \
   ((_x).Encryption_Key12 == (_y).Encryption_Key12) && ((_x).Encryption_Key13 == (_y).Encryption_Key13) && ((_x).Encryption_Key14 == (_y).Encryption_Key14) && \
   ((_x).Encryption_Key15 == (_y).Encryption_Key15)                                                                                                            \
)

   /* The following define determines the maximum fixed size that is    */
   /* used for Plain-text data that used as input to the LE encryption  */
   /* schema.                                                           */
#define QAPI_BLE_PLAIN_TEXT_DATA_MAXIMUM_SIZE                                 16

   /* The following type defines the buffer that is used to format      */
   /* Plain-text data that is to be used for input to the LE encryption */
   /* schema (Version 4.0 + LE).  The size of this buffer is always     */
   /* fixed.                                                            */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Plain_Text_Data_s
{
   uint8_t Plain_Text_Data[QAPI_BLE_PLAIN_TEXT_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Plain_Text_Data_t;

#define QAPI_BLE_PLAIN_TEXT_DATA_SIZE                    (sizeof(qapi_BLE_Plain_Text_Data_t))

   /* The following define determines the maximum fixed size that is    */
   /* output from the LE encryption schema.                             */
#define QAPI_BLE_ENCRYPTED_DATA_MAXIMUM_SIZE                                  16

   /* The following type defines the buffer that is output from the LE  */
   /* encryption schema (Version 4.0 + LE).  The size of this buffer is */
   /* always fixed.                                                     */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Encrypted_Data_s
{
   uint8_t Encrypted_Data[QAPI_BLE_ENCRYPTED_DATA_MAXIMUM_SIZE];
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Encrypted_Data_t;

#define QAPI_BLE_ENCRYPTED_DATA_SIZE                     (sizeof(qapi_BLE_Encrypted_Data_t))

   /* The following represents the structure of a Random Number that is */
   /* used during Encryption (Version 4.0 + LE).                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Random_Number_s
{
   qapi_BLE_NonAlignedByte_t Random_Number0;
   qapi_BLE_NonAlignedByte_t Random_Number1;
   qapi_BLE_NonAlignedByte_t Random_Number2;
   qapi_BLE_NonAlignedByte_t Random_Number3;
   qapi_BLE_NonAlignedByte_t Random_Number4;
   qapi_BLE_NonAlignedByte_t Random_Number5;
   qapi_BLE_NonAlignedByte_t Random_Number6;
   qapi_BLE_NonAlignedByte_t Random_Number7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Random_Number_t;

#define QAPI_BLE_RANDOM_NUMBER_DATA_SIZE                 (sizeof(qapi_BLE_Random_Number_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Random Number variable. */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the Random Number variable in Little Endian Format.   */
   /* The first parameter is the Random Number variable (of type        */
   /* qapi_BLE_Random_Number_t) to assign, and the next eight parameters*/
   /* are the Individual Random Number Byte values to assign to the     */
   /* variable.                                                         */
#define QAPI_BLE_ASSIGN_RANDOM_NUMBER(_dest, _a, _b, _c, _d, _e, _f, _g, _h) \
{                                                                   \
   (_dest).Random_Number0 = (_h);                                   \
   (_dest).Random_Number1 = (_g);                                   \
   (_dest).Random_Number2 = (_f);                                   \
   (_dest).Random_Number3 = (_e);                                   \
   (_dest).Random_Number4 = (_d);                                   \
   (_dest).Random_Number5 = (_c);                                   \
   (_dest).Random_Number6 = (_b);                                   \
   (_dest).Random_Number7 = (_a);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Random_Number_t variables to each      */
   /* other.  This MACRO only returns whether the the                   */
   /* qapi_BLE_Random_Number_t variables are equal to each other (MACRO */
   /* returns boolean result) NOT less than/greater than.  The          */
   /* parameters to this MACRO is the qapi_BLE_Random_Number_t          */
   /* structures to compare.                                            */
#define QAPI_BLE_COMPARE_RANDOM_NUMBER(_x, _y)                                                                                                               \
(                                                                                                                                                   \
   ((_x).Random_Number0 == (_y).Random_Number0) && ((_x).Random_Number1 == (_y).Random_Number1) && ((_x).Random_Number2  == (_y).Random_Number2) && \
   ((_x).Random_Number3 == (_y).Random_Number3) && ((_x).Random_Number4 == (_y).Random_Number4) && ((_x).Random_Number5  == (_y).Random_Number5) && \
   ((_x).Random_Number6 == (_y).Random_Number6) && ((_x).Random_Number7 == (_y).Random_Number7)                                                     \
)

   /* The following type declaration represents the structure of a      */
   /* single Long Term Key (Version 4.0 + LE).                          */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Long_Term_Key_s
{
   uint8_t Long_Term_Key0;
   uint8_t Long_Term_Key1;
   uint8_t Long_Term_Key2;
   uint8_t Long_Term_Key3;
   uint8_t Long_Term_Key4;
   uint8_t Long_Term_Key5;
   uint8_t Long_Term_Key6;
   uint8_t Long_Term_Key7;
   uint8_t Long_Term_Key8;
   uint8_t Long_Term_Key9;
   uint8_t Long_Term_Key10;
   uint8_t Long_Term_Key11;
   uint8_t Long_Term_Key12;
   uint8_t Long_Term_Key13;
   uint8_t Long_Term_Key14;
   uint8_t Long_Term_Key15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Long_Term_Key_t;

#define QAPI_BLE_LONG_TERM_KEY_SIZE                      (sizeof(qapi_BLE_Long_Term_Key_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified Long Term Key variable. */
   /* The Bytes are NOT in Little Endian Format, however, they are      */
   /* assigned to the Long Term Key variable in Little Endian Format.   */
   /* The first parameter is the Long Term Key variable (of type        */
   /* qapi_BLE_Long_Term_Key_t) to assign, and the next 16 parameters   */
   /* are the Individual Long Term Key Byte values to assign to the Long*/
   /* Term Key variable.                                                */
#define QAPI_BLE_ASSIGN_LONG_TERM_KEY(_dest, _a, _b, _c, _d, _e, _f, _g, _h, _i, _j, _k, _l, _m, _n, _o, _p) \
{                                                                                                   \
   (_dest).Long_Term_Key0  = (_p); (_dest).Long_Term_Key1  = (_o); (_dest).Long_Term_Key2  = (_n);  \
   (_dest).Long_Term_Key3  = (_m); (_dest).Long_Term_Key4  = (_l); (_dest).Long_Term_Key5  = (_k);  \
   (_dest).Long_Term_Key6  = (_j); (_dest).Long_Term_Key7  = (_i); (_dest).Long_Term_Key8  = (_h);  \
   (_dest).Long_Term_Key9  = (_g); (_dest).Long_Term_Key10 = (_f); (_dest).Long_Term_Key11 = (_e);  \
   (_dest).Long_Term_Key12 = (_d); (_dest).Long_Term_Key13 = (_c); (_dest).Long_Term_Key14 = (_b);  \
   (_dest).Long_Term_Key15 = (_a);                                                                  \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Long_Term_Key_t variables.  This MACRO */
   /* only returns whether the two qapi_BLE_Long_Term_Key_t variables   */
   /* are equal (MACRO returns boolean result) NOT less than/greater    */
   /* than.  The two parameters to this MACRO are both of type          */
   /* qapi_BLE_Long_Term_Key_t and represent the                        */
   /* qapi_BLE_Long_Term_Key_t variables to compare.                    */
#define QAPI_BLE_COMPARE_LONG_TERM_KEY(_x, _y)                                                                                                                    \
(                                                                                                                                                        \
   ((_x).Long_Term_Key0  == (_y).Long_Term_Key0)  && ((_x).Long_Term_Key1  == (_y).Long_Term_Key1)  && ((_x).Long_Term_Key2  == (_y).Long_Term_Key2)  && \
   ((_x).Long_Term_Key3  == (_y).Long_Term_Key3)  && ((_x).Long_Term_Key4  == (_y).Long_Term_Key4)  && ((_x).Long_Term_Key5  == (_y).Long_Term_Key5)  && \
   ((_x).Long_Term_Key6  == (_y).Long_Term_Key6)  && ((_x).Long_Term_Key7  == (_y).Long_Term_Key7)  && ((_x).Long_Term_Key8  == (_y).Long_Term_Key8)  && \
   ((_x).Long_Term_Key9  == (_y).Long_Term_Key9)  && ((_x).Long_Term_Key10 == (_y).Long_Term_Key10) && ((_x).Long_Term_Key11 == (_y).Long_Term_Key11) && \
   ((_x).Long_Term_Key12 == (_y).Long_Term_Key12) && ((_x).Long_Term_Key13 == (_y).Long_Term_Key13) && ((_x).Long_Term_Key14 == (_y).Long_Term_Key14) && \
   ((_x).Long_Term_Key15 == (_y).Long_Term_Key15)                                                                                                        \
)

   /* The following type declaration represents the structure of a      */
   /* LE States Type (Version 4.0 + LE).                                */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_LE_States_s
{
   uint8_t LE_States0;
   uint8_t LE_States1;
   uint8_t LE_States2;
   uint8_t LE_States3;
   uint8_t LE_States4;
   uint8_t LE_States5;
   uint8_t LE_States6;
   uint8_t LE_States7;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_LE_States_t;

#define QAPI_BLE_LE_STATES_SIZE                          (sizeof(qapi_BLE_LE_States_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual Byte values into the specified LE States variable.  The*/
   /* Bytes are NOT in Little Endian Format, however, they are assigned */
   /* to the LE States variable in Little Endian Format.  The first     */
   /* parameter is the LE States variable (of type qapi_BLE_LE_States_t)*/
   /* to assign, and the next eight parameters are the Individual LE    */
   /* States Byte values to assign to the variable.                     */
#define QAPI_BLE_ASSIGN_LE_STATES(_dest, _a, _b, _c, _d, _e, _f, _g, _h) \
{                                                               \
   (_dest).LE_States0 = (_h);                                   \
   (_dest).LE_States1 = (_g);                                   \
   (_dest).LE_States2 = (_f);                                   \
   (_dest).LE_States3 = (_e);                                   \
   (_dest).LE_States4 = (_d);                                   \
   (_dest).LE_States5 = (_c);                                   \
   (_dest).LE_States6 = (_b);                                   \
   (_dest).LE_States7 = (_a);                                   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_LE_States_t variables.  This MACRO only*/
   /* returns whether the two qapi_BLE_LE_States_t variables are equal  */
   /* (MACRO returns boolean result) NOT less than/greater than.  The   */
   /* two parameters to this MACRO are both of type qapi_BLE_LE_States_t*/
   /* and represent the qapi_BLE_LE_States_t variables to compare.      */
#define QAPI_BLE_COMPARE_LE_STATES(_x, _y)                                                                                           \
(                                                                                                                           \
   ((_x).LE_States0 == (_y).LE_States0) && ((_x).LE_States1 == (_y).LE_States1) && ((_x).LE_States2  == (_y).LE_States2) && \
   ((_x).LE_States3 == (_y).LE_States3) && ((_x).LE_States4 == (_y).LE_States4) && ((_x).LE_States5  == (_y).LE_States5) && \
   ((_x).LE_States6 == (_y).LE_States6) && ((_x).LE_States7 == (_y).LE_States7)                                             \
)

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* setting of LE States Bits in the LE States variable.  This MACRO  */
   /* accepts as input the LE States variable (of type                  */
   /* qapi_BLE_LE_States_t) as the first parameter, and the bit number  */
   /* to set (LSB is bit number 0).  This MACRO sets the bits in Little */
   /* Endian Format (so bit 0 is physically bit 0 of the first byte of  */
   /* the LE States structure).                                         */
#define QAPI_BLE_SET_LE_STATES_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] |= (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* clearing of LE States Bits in the LE States variable.  This MACRO */
   /* accepts as input the LE States variable (of type                  */
   /* qapi_BLE_LE_States_t) as the first parameter, and the bit number  */
   /* to clear (LSB is bit number 0).  This MACRO clears the bits in    */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the LE States structure).                                 */
#define QAPI_BLE_CLEAR_LE_STATES_BIT(_x, _y)   \
   ((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] &= (uint8_t)~(1 << ((_y)%(sizeof(uint8_t)*8)))

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* testing of LE States Bits in the LE States variable.  This MACRO  */
   /* accepts as input the LE States variable (of type                  */
   /* qapi_BLE_LE_States_t) as the first parameter, and the bit number  */
   /* to test (LSB is bit number 0).  This MACRO tests the bits in      */
   /* Little Endian Format (so bit 0 is physically bit 0 of the first   */
   /* byte of the LE States structure).  This MACRO returns a boolean   */
   /* result as the test result.                                        */
#define QAPI_BLE_TEST_LE_STATES_BIT(_x, _y)   \
   (((uint8_t *)&(_x))[(_y)/(sizeof(uint8_t)*8)] & (uint8_t)(1 << ((_y)%(sizeof(uint8_t)*8))))

   /* The following type declaration represents the structure of a      */
   /* Vendor Specific Codec field (Version 4.0 + CSA2).                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Vendor_Specific_Codec_s
{
   qapi_BLE_NonAlignedWord_t CompanyID;
   qapi_BLE_NonAlignedWord_t VendorCodecID;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Vendor_Specific_Codec_t;

#define QAPI_BLE_VENDOR_SPECIFIC_CODEC_SIZE                             (sizeof(qapi_BLE_Vendor_Specific_Codec_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual values into the specified Vendor Specific Codec        */
   /* variable.  The values are NOT in Little Endian Format, however,   */
   /* they are assigned to the Vendor Specific Codec variable in Little */
   /* Endian Format.  The first parameter is the Vendor Specific Codec  */
   /* variable (of type qapi_BLE_Vendor_Specific_Codec_t) to assign, the*/
   /* next parameter is the Company ID and the final parameter is the   */
   /* Vendor Specific Codec ID.                                         */
#define QAPI_BLE_ASSIGN_VENDOR_SPECIFIC_CODEC(_dest, _CompanyID, _VendorCodecID)                            \
{                                                                                                  \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&((_dest).CompanyID), (_CompanyID));           \
   ASSIGN_HOST_WORD_TO_LITTLE_ENDIAN_UNALIGNED_WORD(&((_dest).VendorCodecID), (_VendorCodecID));   \
}

   /* The following MACRO is a utility MACRO that exists to aid in the  */
   /* Comparison of two qapi_BLE_Vendor_Specific_Codec_t variables.     */
   /* This MACRO only returns whether the two                           */
   /* qapi_BLE_Vendor_Specific_Codec_t variables are equal (MACRO       */
   /* returns boolean result) NOT less than/greater than.  The two      */
   /* parameters to this MACRO are both of type                         */
   /* qapi_BLE_Vendor_Specific_Codec_t and represent the                */
   /* qapi_BLE_Vendor_Specific_Codec_t variables to compare.            */
#define QAPI_BLE_COMPARE_VENDOR_SPECIFIC_CODEC(_x, _y)                                                                              \
(                                                                                                                          \
   (READ_UNALIGNED_WORD_LITTLE_ENDIAN(&((_x).CompanyID)) == READ_UNALIGNED_WORD_LITTLE_ENDIAN(&((_y).CompanyID))) &&       \
   (READ_UNALIGNED_WORD_LITTLE_ENDIAN(&((_x).VendorCodecID)) == READ_UNALIGNED_WORD_LITTLE_ENDIAN(&((_y).VendorCodecID)))  \
)

   /* The following type declaration represents the structure of a SCO  */
   /* Coding Format field (Version 4.0 + CSA2).                         */
   /* * NOTE * The VendorSpecificCodec field is ignored unless the      */
   /*          Coding_Format is set to                                  */
   /*          QAPI_BLE_HCI_ENHANCED_SYNCHRONOUS_CODING_FORMAT_VENDOR_..*/
   /*          ...SPECIFIC.                                             */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_SCO_Coding_Format_s
{
   qapi_BLE_NonAlignedByte_t Coding_Format;
   qapi_BLE_Vendor_Specific_Codec_t   VendorSpecificCodec;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_SCO_Coding_Format_t;

#define QAPI_BLE_SCO_CODING_FORMAT_SIZE                                 (sizeof(qapi_BLE_SCO_Coding_Format_t))

   /* The following MACRO is a utility MACRO that exists to assign the  */
   /* individual values into the specified SCO Coding Format variable.  */
   /* The first parameter is the Coding Format variable (of type        */
   /* Coding_Format_t) to assign, the next parameter is the Coding      */
   /* Format, followed by the Company ID and the final parameter is the */
   /* Vendor Specific Codec ID.                                         */
#define QAPI_BLE_ASSIGN_SCO_CODING_FORMAT(_dest, _CodingFormat, _CompanyID, _VendorCodecID)                \
{                                                                                                 \
   ASSIGN_HOST_BYTE_TO_LITTLE_ENDIAN_UNALIGNED_BYTE(&((_dest).Coding_Format), (_CodingFormat));   \
   QAPI_BLE_ASSIGN_VENDOR_SPECIFIC_CODEC(((_dest).VendorSpecificCodec), (_CompanyID), (_VendorCodecID));   \
}

   /* The following type declaration represents the structure of a      */
   /* Diffie Hellman Key (Version 4.2).                                 */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Diffie_Hellman_Key_s
{
   uint8_t Diffie_Hellman_Key0;
   uint8_t Diffie_Hellman_Key1;
   uint8_t Diffie_Hellman_Key2;
   uint8_t Diffie_Hellman_Key3;
   uint8_t Diffie_Hellman_Key4;
   uint8_t Diffie_Hellman_Key5;
   uint8_t Diffie_Hellman_Key6;
   uint8_t Diffie_Hellman_Key7;
   uint8_t Diffie_Hellman_Key8;
   uint8_t Diffie_Hellman_Key9;
   uint8_t Diffie_Hellman_Key10;
   uint8_t Diffie_Hellman_Key11;
   uint8_t Diffie_Hellman_Key12;
   uint8_t Diffie_Hellman_Key13;
   uint8_t Diffie_Hellman_Key14;
   uint8_t Diffie_Hellman_Key15;
   uint8_t Diffie_Hellman_Key16;
   uint8_t Diffie_Hellman_Key17;
   uint8_t Diffie_Hellman_Key18;
   uint8_t Diffie_Hellman_Key19;
   uint8_t Diffie_Hellman_Key20;
   uint8_t Diffie_Hellman_Key21;
   uint8_t Diffie_Hellman_Key22;
   uint8_t Diffie_Hellman_Key23;
   uint8_t Diffie_Hellman_Key24;
   uint8_t Diffie_Hellman_Key25;
   uint8_t Diffie_Hellman_Key26;
   uint8_t Diffie_Hellman_Key27;
   uint8_t Diffie_Hellman_Key28;
   uint8_t Diffie_Hellman_Key29;
   uint8_t Diffie_Hellman_Key30;
   uint8_t Diffie_Hellman_Key31;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Diffie_Hellman_Key_t;

#define QAPI_BLE_DIFFIE_HELLMAN_KEY_SIZE                       (sizeof(qapi_BLE_Diffie_Hellman_Key_t))

   /* The following type declaration represents the structure of a      */
   /* Public Key Coordinate (Version 4.2).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Public_Key_Coordinate_s
{
   uint8_t Public_Key_Coordinate0;
   uint8_t Public_Key_Coordinate1;
   uint8_t Public_Key_Coordinate2;
   uint8_t Public_Key_Coordinate3;
   uint8_t Public_Key_Coordinate4;
   uint8_t Public_Key_Coordinate5;
   uint8_t Public_Key_Coordinate6;
   uint8_t Public_Key_Coordinate7;
   uint8_t Public_Key_Coordinate8;
   uint8_t Public_Key_Coordinate9;
   uint8_t Public_Key_Coordinate10;
   uint8_t Public_Key_Coordinate11;
   uint8_t Public_Key_Coordinate12;
   uint8_t Public_Key_Coordinate13;
   uint8_t Public_Key_Coordinate14;
   uint8_t Public_Key_Coordinate15;
   uint8_t Public_Key_Coordinate16;
   uint8_t Public_Key_Coordinate17;
   uint8_t Public_Key_Coordinate18;
   uint8_t Public_Key_Coordinate19;
   uint8_t Public_Key_Coordinate20;
   uint8_t Public_Key_Coordinate21;
   uint8_t Public_Key_Coordinate22;
   uint8_t Public_Key_Coordinate23;
   uint8_t Public_Key_Coordinate24;
   uint8_t Public_Key_Coordinate25;
   uint8_t Public_Key_Coordinate26;
   uint8_t Public_Key_Coordinate27;
   uint8_t Public_Key_Coordinate28;
   uint8_t Public_Key_Coordinate29;
   uint8_t Public_Key_Coordinate30;
   uint8_t Public_Key_Coordinate31;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Public_Key_Coordinate_t;

#define QAPI_BLE_PUBLIC_KEY_COORDINATE_SIZE                    (sizeof(qapi_BLE_Public_Key_Coordinate_t))

   /* The following type declaration represents the structure of a      */
   /* P-256 Public Key (Version 4.2).                                   */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_P256_Public_Key_s
{
   qapi_BLE_Public_Key_Coordinate_t X;
   qapi_BLE_Public_Key_Coordinate_t Y;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_P256_Public_Key_t;

#define QAPI_BLE_P256_PUBLIC_KEY_SIZE                          (sizeof(qapi_BLE_P256_Public_Key_t))

   /* The following type declaration represents the structure of a P256 */
   /* Private Key (Version 4.2).                                        */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_P256_Private_Key_s
{
   uint8_t Private_Key_Byte0;
   uint8_t Private_Key_Byte1;
   uint8_t Private_Key_Byte2;
   uint8_t Private_Key_Byte3;
   uint8_t Private_Key_Byte4;
   uint8_t Private_Key_Byte5;
   uint8_t Private_Key_Byte6;
   uint8_t Private_Key_Byte7;
   uint8_t Private_Key_Byte8;
   uint8_t Private_Key_Byte9;
   uint8_t Private_Key_Byte10;
   uint8_t Private_Key_Byte11;
   uint8_t Private_Key_Byte12;
   uint8_t Private_Key_Byte13;
   uint8_t Private_Key_Byte14;
   uint8_t Private_Key_Byte15;
   uint8_t Private_Key_Byte16;
   uint8_t Private_Key_Byte17;
   uint8_t Private_Key_Byte18;
   uint8_t Private_Key_Byte19;
   uint8_t Private_Key_Byte20;
   uint8_t Private_Key_Byte21;
   uint8_t Private_Key_Byte22;
   uint8_t Private_Key_Byte23;
   uint8_t Private_Key_Byte24;
   uint8_t Private_Key_Byte25;
   uint8_t Private_Key_Byte26;
   uint8_t Private_Key_Byte27;
   uint8_t Private_Key_Byte28;
   uint8_t Private_Key_Byte29;
   uint8_t Private_Key_Byte30;
   uint8_t Private_Key_Byte31;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_P256_Private_Key_t;

#define QAPI_BLE_P256_PRIVATE_KEY_SIZE                         (sizeof(qapi_BLE_P256_Private_Key_t))

   /* The following type declaration represents the structure of a      */
   /* single Secure Connections Confirmation, C used for OOB mechanism  */
   /* of LE Secure Connections (Version 4.2).                           */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Secure_Connections_Confirmation_s
{
   uint8_t Confirmation0;
   uint8_t Confirmation1;
   uint8_t Confirmation2;
   uint8_t Confirmation3;
   uint8_t Confirmation4;
   uint8_t Confirmation5;
   uint8_t Confirmation6;
   uint8_t Confirmation7;
   uint8_t Confirmation8;
   uint8_t Confirmation9;
   uint8_t Confirmation10;
   uint8_t Confirmation11;
   uint8_t Confirmation12;
   uint8_t Confirmation13;
   uint8_t Confirmation14;
   uint8_t Confirmation15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Secure_Connections_Confirmation_t;

#define QAPI_BLE_SECURE_CONNECTIONS_CONFIRMATION_SIZE          (sizeof(qapi_BLE_Secure_Connections_Confirmation_t))

   /* The following type declaration represents the structure of a      */
   /* single Secure Connections Randomizer, R used for OOB mechanism of */
   /* LE Secure Connections (Version 4.2).                              */
typedef __QAPI_BLE_PACKED_STRUCT_BEGIN__ struct qapi_BLE_Secure_Connections_Randomizer_s
{
   uint8_t Randomizer0;
   uint8_t Randomizer1;
   uint8_t Randomizer2;
   uint8_t Randomizer3;
   uint8_t Randomizer4;
   uint8_t Randomizer5;
   uint8_t Randomizer6;
   uint8_t Randomizer7;
   uint8_t Randomizer8;
   uint8_t Randomizer9;
   uint8_t Randomizer10;
   uint8_t Randomizer11;
   uint8_t Randomizer12;
   uint8_t Randomizer13;
   uint8_t Randomizer14;
   uint8_t Randomizer15;
} __QAPI_BLE_PACKED_STRUCT_END__ qapi_BLE_Secure_Connections_Randomizer_t;

#define QAPI_BLE_SECURE_CONNECTIONS_RANDOMIZER_SIZE            (sizeof(qapi_BLE_Secure_Connections_Randomizer_t))

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#endif
